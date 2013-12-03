<?php
require_once "NDB_Form.class.inc";
require_once "Utility.class.inc";

/**
 * Candidate Parameter form
 * @package main
 */
class NDB_Form_candidate_parameters extends NDB_Form
{
    var $relationType =  array(null=>'','full_sibling'=>'Full Sibling',
                               'half_sibling'=>'Half Sibling','1st_cousin'=>'First Cousin');
    var $indent = "&nbsp;&nbsp;&nbsp;&nbsp;";

    function _hasAccess()
    {
        // create user object
        $user =& User::singleton();
        if(Utility::isErrorX($user)) {
            return PEAR::raiseError("User Error: ".$user->getMessage());
        }

        // check that the $candID is passed b/c the profile needs to be opened
        if ($this->identifier != $_REQUEST['candID']) {
            return PEAR::raiseError("NDB_Form_candidate_parameters::_access: Candidate Profile Error (".$_REQUEST['candID']."): ");
        }

        $candidate =& Candidate::singleton($this->identifier);
        if (Utility::isErrorX($candidate)) {
            return PEAR::raiseError("Candidate Error ($this->identifier): ".$candidate->getMessage());
        }

        // check user permissions
    	return ($user->hasPermission('data_entry') && $user->getData('CenterID') == $candidate->getData('CenterID') && $user->hasPermission('unsend_to_dcc'));
    }

    function _getDefaults()
    {
  		$DB =& Database::singleton();
        //Get the default values
        $DB->select("SELECT ParameterTypeID, Value FROM parameter_candidate WHERE CandID='".$this->identifier."'", $value_results);
        foreach($value_results AS $vresult){
        	$cand_info["PTID_".$vresult['ParameterTypeID']]=$vresult['Value'];
        }
        $cand_info['CandidateGUID'] = $DB->pselectOne("SELECT CandidateGUID FROM candidate WHERE CandID=:CandidateID", array('CandidateID' => $this->identifier));
        $defaults['ProbandGUID'] = $DB->pselectOne("SELECT ProbandGUID FROM candidate WHERE CandID=:CandidateID", array('CandidateID' => $this->identifier));
        $defaults['ProbandDoB'] = $DB->pselectOne("SELECT ProbandDoB FROM candidate WHERE CandID=:CandidateID", array('CandidateID' => $this->identifier));
        if( $defaults['ProbandDoB']=== '0000-00-00') {
            $defaults['ProbandDoB'] = '';
        }
        $defaults['ProbandDoB2']= $defaults['ProbandDoB'];
        $defaults['ProbandGender'] = $DB->pselectOne("SELECT ProbandGender FROM candidate WHERE CandID=:CandidateID", array('CandidateID' => $this->identifier));
        $candidate_dob = $DB->pselectOne("SELECT DoB FROM candidate WHERE CandID=:CandidateID", array('CandidateID' => $this->identifier));

        $age = Utility::calculateAge($defaults['ProbandDoB'],$candidate_dob ); 
        if(Utility::isErrorX($age)) {
            $defaults['Age_Difference'] = 'Could not calculate age';
        } else {
            $defaults['Age_Difference'] = $age['year']*12 + $age['mon']+ round($age['day']/30,2);
        }
        $familyid = $DB->pselectOne("SELECT FamilyID from family where CandID=:CandidateID",array('CandidateID'=>$this->identifier));
        if(Utility::isErrorX($familyid)){
            $relations = $DB->pselect("SELECT Relation_CandID, Relation_code from family WHERE CandID=:CandidateID",array('CandidateID'=> $this->identifier));

        } else {
            $this->tpl_data['familyID'] = $familyid;
            $relations = $DB->pselect("SELECT CandID, Relationship_type from family WHERE FamilyID=:fam_id
                                       AND CandID <> '$this->identifier'" ,array('fam_id'=> $familyid));

        }
        $this->tpl_data['sibling_list'] = array();
        foreach($relations as $relation)
        {
            $relation['Relationship_type'] = $this->relationType[$relation['Relationship_type']];
            $this->tpl_data['sibling_list'][]= $relation;
        }
       
        $cand_info['flagged_caveatemptor'] = $DB->pselectOne("SELECT flagged_caveatemptor FROM candidate 
                                             WHERE CandID=:CandidateID",
                                             array('CandidateID' => $this->identifier));
        $desc = $DB->pselectOne("SELECT Description AS Reason FROM candidate c join caveat_options o on 
                (o.ID = c.flagged_reason) WHERE CandID=:CandidateID",array('CandidateID' => $this->identifier));
        if(!empty($desc)) {
           $cand_info['flagged_reason'] = $desc;
           if($cand_info['flagged_reason'] == 'Other') {
               $cand_info['flagged_other'] = $DB->pselectOne("SELECT flagged_other FROM candidate 
                       WHERE CandID=:CandidateID",array('CandidateID' => $this->identifier));
           }
        }
        
        $this->tpl_data['params_list'] = $cand_info;
       
       // Getting participant status default values
        $ps_info = $DB->pselectRow("SELECT study_consent,study_consent_date,study_consent_withdrawal,
                                    ndar_consent,ndar_consent_date,ndar_consent_withdrawal 
                                    FROM participant_status WHERE CandID = :cid", 
                                    array('cid'=>$this->identifier));

        if(empty($ps_info)) {
            //set candidate to active by default
          $this->tpl_data['pstat'] = $DB->pselectOne("SELECT ID FROM participant_status_options WHERE 
                                                        Description=:desc", array('desc'=>'Active')); 

        }
        foreach($ps_info as $key => &$val) {
         
            if($val === '0000-00-00') {
                $val = '';
            }
            if(!empty($ps_info[$key])) {
                $consent_info[$key] = $val;
            }
        }
        $config =& NDB_Config::singleton();
        $consent = $config->getSetting('ConsentModule');
        $this->tpl_data['display_consent'] = $consent['useConsent'];  
        $this->tpl_data['consent_info'] = $consent_info;
        $result = $DB->pselect("SELECT participant_status, entry_staff, data_entry_date FROM participant_status_history
                                WHERE CandID=:cid", array('cid'=>$this->identifier));
        for($i=0; $i < sizeof($result); $i++) {
            $row = $result[$i];
            $desc = $DB->pselectOne("SELECT Description FROM participant_status_options WHERE ID=:pid",
                                     array('pid'=>$row['participant_status']));
            $this->participant_history["status".$i] = $desc;
            $this->participant_history["staff".$i]  = $row['entry_staff'];
            $this->participant_history["timestamp".$i] = $row['data_entry_date'];
        }
        $defaults['entry_staff'] = $DB->pselectOne("SELECT entry_staff from participant_status WHERE CandID=:cid",
                                                    array('cid'=>$this->identifier));
        $defaults['data_entry_date'] = $DB->pselectOne("SELECT data_entry_date from participant_status WHERE CandID=:cid",
                                                    array('cid'=>$this->identifier));
        return $defaults;
    }

    function _process($values)
    {   
        if(!is_array($values) || count($values) ==0) {
        	return true;
        }
        $DB =& Database::singleton();
        $values['CandID'] = $this->identifier;
        unset($values['ProbandDoB2']);
        $config =& NDB_Config::singleton();
        $consent = $config->getSetting('ConsentModule');
        if ($consent['useConsent'] === 'true') {

            foreach (Utility::asArray($consent['Consent']) as $question) {
                unset($values[$question['name'].'_date2']);
                unset($values[$question['name'].'_withdrawal2']);
            }
        }
        if (!(is_null($_SESSION['State']))) {
            $currentUser =& User::singleton($_SESSION['State']->getUsername());
            $id = $currentUser->getData("UserID");
            $values['entry_staff'] = $id;
        }
        //delete old values
        $DB->delete("parameter_candidate", array("CandID"=>$this->identifier));

        //insert new values
        while(list($key, $value)=each($values)){
        	$set="";
            if(strpos($key, "PTID_") === 0) {
                $set['ParameterTypeID']=str_replace("PTID_","",$key);
                $set['CandID']=$this->identifier;
                $set['Value']=$value;
                $set['InsertTime']=time();
                $DB->insert("parameter_candidate", $set);
            } else if($key == 'CandidateGUID' || $key == "ProbandGUID" || $key == 'ProbandDoB' || $key == 'ProbandGender'
                      || $key =='flagged_caveatemptor' || $key == 'flagged_reason' || $key == 'flagged_other'
                      || $key == 'flagged_other_status') {
                if($key == 'ProbandDoB') {
                    $value = $this->_getDatabaseDate($value);
                }
                $DB->update("candidate", array($key => $value), array('CandID' => $this->identifier));

                if ($key == 'ProbandDoB') {
                    $tests = $DB->pselect(
                        "SELECT f.CommentID, f.Test_name 
                        FROM flag f JOIN session s ON (f.SessionID=s.ID)
                        JOIN candidate c ON (c.CandID=s.CandID)
                        WHERE
                        c.CandID=:CaID AND f.Test_name LIKE '%proband'
                        ", array('CaID' => $this->identifier)
                    );
                    foreach ($tests as $test) {
                        $inst = NDB_BVL_Instrument::factory($test['Test_name'], $test['CommentID'], null, false);
                        $setValue = array('Date_taken' => $inst->getFieldValue('Date_taken'));
                        $inst->_saveCandidateAge($setValue);
                        $DB->update($test['Test_name'], $setValue, array('CommentID' => $test['CommentID']));
                    }

                }
            }
           
        }

       if(isset($values['SiblingID'])) { 
           $fid = $DB->pselectOne("SELECT FamilyID from family where CandID=:CaID",array('CaID' => $this->identifier));
           if (Utility::isErrorX($fid)) {
               return PEAR::raiseError("Could not family id: ".$fid->getMessage());
           }
           if(empty($fid)){
               $famID = $DB->pselectOne("SELECT max(FamilyID) from family");
               if (Utility::isErrorX($famID)) {
                   return PEAR::raiseError("Could not family id: ".$famID->getMessage());
               }
               if(empty($famID)) {
                   $famID = 0;
               }
               $fid = $famID+1;
               $success = $DB->insert('family',array('CandID'=>$this->identifier,'FamilyID'=>$fid,
                           'Relationship_type'=>$values['relation_type']));
               if (Utility::isErrorX($success)) {
                   return PEAR::raiseError("DB Error: ".$success->getMessage());
               }

           }

           $value = $values['SiblingID'];
           $success = $DB->insert('family',array('CandID'=>$value,'FamilyID'=>$fid,
                                                 'Relationship_type'=>$values['relation_type']));
           if (Utility::isErrorX($success)) {
               return PEAR::raiseError("DB Error: ".$success->getMessage());
           }
          
       }
       if(isset($values['participant_status']) || isset($values['study_consent_date'])
          || isset($values['study_consent_withdrawal']) || isset($values['ndar_consent_date'])
          || isset($values['ndar_consent_withdrawal']) || isset($values['study_consent'])
          || isset($values['ndar_consent']) || isset($values['reason_specify'])
          || isset($values['reason_specify_status'])) {
           $participant_vals = array();
           $participant_vals['participant_status'] = $values['participant_status'];
           $sub_reasonID = $DB->pselectOne("SELECT ID FROM participant_status_options WHERE Description=:sub_desc", 
                   array('sub_desc' =>$values['participant_suboptions']));
           if(empty($sub_reasonID)) {
               $participant_vals['participant_suboptions'] = NULL;
           } else {
               $participant_vals['participant_suboptions'] = $sub_reasonID;
           }
           $participant_vals['study_consent'] = $values['study_consent'];
           $participant_vals['ndar_consent'] = $values['ndar_consent'];
           $participant_vals['entry_staff'] = $id;
           $participant_vals['reason_specify']= $values['reason_specify'];
           $participant_vals['reason_specify_status']= $values['reason_specify_status'];
           $participant_vals['CandID'] = $values['CandID'];
           $consent_dates = array('study_consent_date','study_consent_withdrawal','ndar_consent_date',
                                  'ndar_consent_withdrawal');
           foreach($consent_dates as $field) {
               $value = $this->_getDatabaseDate($values[$field]);
               if($value === '--') {
                   $value = '';
               }
               $participant_vals[$field] = $value;  
           }
           //print_r($participant_vals);
                    // save the values
           //if it exists update it
           $ParticipantCount = $DB->pselectOne(
                   "SELECT COUNT(*) FROM participant_status WHERE CandID = :cid", 
                   array("cid"=>$values['CandID'])
                   );
           if ($ParticipantCount > 0) {
               $success = $DB->update(
                       "participant_status", 
                       $participant_vals,
                       array("CandID"=>$values['CandID'])
                       );
           } else {
               //insert it
               $success = $DB->insert("participant_status",$participant_vals);
           }

           if (Utility::isErrorX($success)) {
               return PEAR::raiseError(
                       "NDB_Form_candidate_parameters::_process: ".$success->getMessage()
                       );
           }

           $current_status = $DB->pselectOne("SELECT participant_status FROM participant_status_history
                                              WHERE CandID = :cid ORDER BY data_entry_date DESC", 
                                              array("cid"=>$values['CandID']) );
           if($current_status != $participant_vals['participant_status']) {
               $success = $DB->insert("participant_status_history", 
                          array('participant_status'=>$participant_vals['participant_status'], 
                                'participant_suboptions'=>$participant_vals['participant_suboptions'],
                                'entry_staff'=>$participant_vals['entry_staff'],
                                'CandID' => $participant_vals['CandID'],
                                'reason_specify'=>$participant_vals['reason_specify'],
                                'reason_specify_status'=>$participant_vals['reason_specify_status']));
               if (Utility::isErrorX($success)) {
                   return PEAR::raiseError(
                           "NDB_Form_candidate_parameters::_process: ".$success->getMessage()
                           );
               }

           }
       }
        $this->tpl_data['success'] = true;

        // freeze it, just in case
        $this->form->freeze();
    }


    function _getInstrumentInfo($instrument, $param) {
        $DB =& Database::singleton();

        $ret = $DB->selectOne("SELECT t.$param FROM flag f JOIN $instrument t ON (t.CommentID=f.CommentID) JOIN session s ON (f.SessionID=s.ID) WHERE s.CandID=" . $DB->quote($this->identifier) . ' AND f.test_name=' . $DB->quote($instrument) . ' AND t.CommentID NOT LIKE \'DDE_%\'');
        if($ret == array()) {
            return;
        }
        return $ret;
    }

    function _getTSIinfo($param) {
        return $this->_getInstrumentInfo('tsi', $param);
    }

    function _getADIRinfo($param) {
        return $this->_getInstrumentInfo('adi_r_proband', $param);
    }
    function candidate_parameters()
    {
        $DB =& Database::singleton();
        $config =& NDB_Config::singleton();

        $ethnicityList = array(null=>'');
        $success = Utility::getEthnicityList();
        if (Utility::isErrorX($success)) {
        	return PEAR::raiseError("Utility::getEthnicityList error: ".$success->getMessage());
        }
        $ethnicityList = array_merge($ethnicityList,$success);
        unset($success);
        
        $candidate =& Candidate::singleton($this->identifier);
        if (Utility::isErrorX($candidate)) {
            return PEAR::raiseError("Candidate Error ($this->identifier): ".$candidate->getMessage());
        }

        // candID
        $this->tpl_data['candID'] = $candidate->getData('CandID');
 		//Extract the fields from the parameter_type table
        $DB->select("SELECT pt.ParameterTypeID, pt.Name, pt.Type, Description FROM parameter_type as pt, parameter_type_category as ptc, parameter_type_category_rel as ptcr WHERE pt.ParameterTypeID=ptcr.ParameterTypeID AND ptcr.ParameterTypeCategoryID=ptc.ParameterTypeCategoryID AND ptc.Name='Candidate Parameters' ORDER BY pt.ParameterTypeID, pt.name ASC", $field_results);
        //If there are no defined fields pritn a message to that effect
        if(empty($field_results)){
        	$this->form->addElement('static', "static", "No candidate parameters have been defined for this study");
        	return;
        }
        
        //Loop through the fields and add them appropriately
        foreach($field_results AS $fresult) {
        	switch(substr($fresult['Type'],0,3)) {
        		case "enu":
        			$options=substr($fresult['Type'],4);
        			$options=trim($options,"()");
        			$options=Utility::explodeEncapsulated(",", "'", $options);
                    $elOptions = array('' => '');
                    foreach($options as $option) {
                        $elOptions[$option] = $option;
                    }
        			$this->form->addElement('select', "PTID_".$fresult['ParameterTypeID'], $fresult['Description'], $elOptions);
        		break;
        		
        		case "dat":
        			$this->form->addElement('date', "PTID_".$fresult['ParameterTypeID'], $fresult['Description'], $dateOptions);
        		break;
        		
        		case "int":
        		case "var":
        		case "tex":
            default:
        			$this->form->addElement('textarea', "PTID_".$fresult['ParameterTypeID'], $fresult['Description']);
        		
        	}
        	$this->tpl_data['elements_list'][]="PTID_".$fresult['ParameterTypeID'];
        }

        $DoB_ADI_R = $this->_getADIRinfo("DoB_proband");
        $DoB_Vineland = $this->_getInstrumentInfo("vineland_proband", "BIRTH_DATE");
        if($DoB_ADI_R != $DoB_Vineland) {
            $this->form->addElement('static', 'dob_error', 'Date of Birth from Vineland and ADI-R do not match');
        }
        $this->form->addElement('text', 'CandidateGUID', 'Candidate GUID:');
        $this->form->addElement('text', 'ProbandGUID', 'Proband GUID:');
        
        $config =& NDB_Config::singleton();
        $probandDateOptions = array(
            'language' => 'en',
            'format'   => 'YMd',
            'minYear'  => $config->getSetting('startYear') - 20, //allows for proband siblings up to 20 years older than candidate
            'maxYear'  => $config->getSetting('endYear'),
            'addEmptyOption' => true,
            'emptyOptionValue' => null
        );

        $this->form->addElement('date', 'ProbandDoB', 'DoB Proband:', $probandDateOptions);
        $this->form->addElement('date', 'ProbandDoB2', 'Confirm DoB Proband:', $probandDateOptions);
        $this->form->addElement('select', 'ProbandGender', 'Proband gender:', array('' => '','Male' => 'Male', 'Female' => 'Female') );
        $this->form->addElement('static', 'dob_proband_adi_r', 'DoB of Proband (ADI-R):', $DoB_ADI_R);
        $this->form->addElement('static', 'dob_proband_vineland', 'DoB of Proband (Vineland):', $DoB_Vineland);
        $this->form->addElement('static', 'Age_Difference','Age Difference between candidate and proband (in months):');
        $this->form->addElement('static', 'mother_race', 'Mother\'s Race:', $this->_getTSIinfo("mother_race"));
        $this->form->addElement('static', 'father_race', 'Father\'s Race:', $this->_getTSIinfo("father_race"));
        $this->form->addElement('static', 'birth_city', 'City of Birth:', $this->_getTSIinfo("city_of_birth"));
        $this->form->addElement('static', 'home_lang', 'Primary Language At Home:', $this->_getTSIinfo("primary_language"));
        $this->form->addElement('static','SiblingcID','Sibling ID:'); 
        $this->form->addElement('static','relation_type','Relationship:');
        //participant status 

        //entry staff info
        $this->addScoreColumn('entry_staff', 'Data Entry Staff');
        $this->addScoreColumn('data_entry_date', 'Date of last Data entry');

        $pscid = $DB->pselectone(
                'SELECT PSCID FROM candidate where CandID = :candid',
                array('candid'=>$this->identifier)
                );

        $this->addScoreColumn('pscid', 'PSCID');
        $this->tpl_data['pscid'] = $pscid;

        $options = $this->getParticipantStatusOptions();
        $options = array('') + $options;
        $this->tpl_data['pstatus_options'] = $options;
        $this->tpl_data['pstat'] = $_REQUEST['participant_status'];
        $this->addTextAreaGroup('reason_specify',"Comments",array(null=>'','not_answered'=>'Not Answered'));
        
        //Consent Information
        $result = $DB->pselect("SELECT po.Description, entry_staff, data_entry_date,reason_specify
                FROM participant_status_history p join participant_status_options po on (po.ID = p.participant_status)
                WHERE CandID=:cid", array('cid'=>$this->identifier));
        for($i = 0; $i< sizeof($result); $i++) {
            if($result[$i]['Description']=='Active' && empty($result[$i]['entry_staff']))
            {
                $result[$i]['entry_staff'] = 'Enrollment';
            }

        }
        $this->tpl_data['history_list'] = $result;
        
        $study_consent = $DB->pselect("SELECT study_consent,study_consent_date,study_consent_withdrawal FROM 
                                consent_info_history WHERE CandID=:cid", array('cid'=>$this->identifier));
        $ndar_consent = $DB->pselect("SELECT ndar_consent,ndar_consent_date,ndar_consent_withdrawal FROM 
                                consent_info_history WHERE CandID=:cid", array('cid'=>$this->identifier));
        $this->tpl_data['study_consent_history'] = $study_consent;
        $this->tpl_data['ndar_consent_history'] = $ndar_consent;
        
        $this->form->addFormRule(array(&$this,'_validate'));
    }

    /* This is taken from NDB_BVL_Instrument. It should be moved to NDB_Page once NDB_Page is merged. */

    function _getDatabaseDate($formDateValue) {
        if(!empty($formDateValue)){
            // check if it's already formatted correctly
            if(is_string($formDateValue) && preg_match("/^[\d]{4}-[\d]{2}-[\d]{2}$/", $formDateValue)) {
                return $formDateValue;
            }
            if(count($formDateValue)==2) {
                $databaseValue = "$formDateValue[H]:$formDateValue[i]";  //handle time (HH:MM:SS)
            } else {
                $databaseValue = "$formDateValue[Y]-$formDateValue[M]-$formDateValue[d]";  //handle date (YYYY/MM/DD)
            }
        }
        return $databaseValue;
    }

    function add_family(){
        
        $this->form->addElement('text','SiblingID','Sibling ID:');
        $this->form->addElement('select','relation_type','Relation Type', $this->relationType);
        $this->form->addFormRule(array(&$this, '_validate_add_family'));
        $this->tpl_data['candID'] = $this->identifier; 


    }

    function update_participant_status() { 
        
        $DB =& Database::singleton();
        $pscid = $DB->pselectone(
                'SELECT PSCID FROM candidate where CandID = :candid',
                array('candid'=>$this->identifier)
                );
        $this->addScoreColumn('pscid', 'PSCID');
        $this->tpl_data['candID'] = $this->identifier;

        $this->tpl_data['pscid'] = $pscid;

        $options = $this->getParticipantStatusOptions();
        $options = array('') + $options;
        $this->tpl_data['pstatus_options'] = $options;
        //$this->tpl_data['pstat'] = $_REQUEST['participant_status'];
        $this->addTextAreaGroup('reason_specify',"Comments",array(null=>'','not_answered'=>'Not Answered'));

    } 

    function update_candidate_info() {
        
        $DB =& Database::singleton();
        $pscid = $DB->pselectone(
                'SELECT PSCID FROM candidate where CandID = :candid',
                array('candid'=>$this->identifier)
                );
        $this->addScoreColumn('pscid', 'PSCID');
        $this->tpl_data['candID'] = $this->identifier;

        $this->tpl_data['pscid'] = $pscid;

        $caveat_options = array(''=>null);
        $options = $DB->pselect("SELECT ID, Description FROM caveat_options");
        foreach($options as $row) {
            $caveat_options[$row['ID']] = $row['Description'];
        }
        $this->form->addElement('select','flagged_caveatemptor','Caveat Emptor flag for candidate', 
                                 array(''=>'','true'=>'True','false'=>'False'));
        $this->form->addElement('select','flagged_reason',$this->indent.'Reason for Cavear Emptor flag',
                                $caveat_options);
        $this->addTextAreaGroup('flagged_other',$this->indent.'If Other, please specify',
                                          array(null=>'','not_answered'=>'Not Answered'));
        
        $this->form->addFormRule(array(&$this,'_validate'));

    }

    function update_consent_info() {
        $DB =& Database::singleton();
        $pscid = $DB->pselectone(
                'SELECT PSCID FROM candidate where CandID = :candid',
                array('candid'=>$this->identifier)
                );
        $this->addScoreColumn('pscid', 'PSCID');
        $this->tpl_data['candID'] = $this->identifier;

        $this->tpl_data['pscid'] = $pscid;
       
       // Add questions about consent
        $config =& NDB_Config::singleton();
        $consent = $config->getSetting('ConsentModule');
        if ($consent['useConsent'] === 'true') {
            $config =& NDB_Config::singleton();
            $dateOptions = array(
                    'language' => 'en',
                    'format'   => 'YMd',
                    'minYear'  => $config->getSetting('startYear'),
                    'maxYear'  => $config->getSetting('endYear'),
                    'addEmptyOption' => true,
                    'emptyOptionValue' => null
                    );

            $consentQuestions = array();
            foreach (Utility::asArray($consent['Consent']) as $question) {
                $yesno = $this->addSelect($question['name'], $question['label'], 
                        array('' => '',
                            'yes' => 'yes',
                            'no' => 'no')
                        ); 
                $withdrew = $this->addBasicDate($question['name'] . '_date', 
                        "Date of $question[label] (required)", $dateOptions);
                $withdrew2 = $this->addBasicDate($question['name'] . '_date2', 
                        "Confirmation Date of $question[label] (required)", $dateOptions);

                $withdrew = $this->addBasicDate($question['name'] . '_withdrawal', 
                        "Date of withdrawal of $question[label] (optional)", $dateOptions);
                $withdrew2 = $this->addBasicDate($question['name'] . '_withdrawal2', 
                        "Confirmation Date of withdrawal of $question[label] (optional)", $dateOptions);
                $consentQuestions[] = array(
                        $question['name'],
                        $question['name'] . '_date',
                        $question['name'] . '_date2',
                        $question['name'] . '_withdrawal',
                        $question['name'] . '_withdrawal2'
                        );
            }
            $this->tpl_data['consent'] = $consentQuestions;
        }
        $this->form->addFormRule(array(&$this,'_validate'));

    }
    
    function participant_status_history(){
        
        $this->tpl_data['candID'] = $_REQUEST['candID'];
        $this->addHeader('Paricipant Status History for Candidate');
        $DB =& Database::singleton();
        $pscid = $DB->pselectone(
                'SELECT PSCID FROM candidate where CandID = :candid',
                array('candid'=>$this->identifier)
                );

        $this->tpl_data['pscid'] = $pscid;


        $result = $DB->pselect("SELECT po.Description, entry_staff, data_entry_date,reason_specify
                  FROM participant_status_history p join participant_status_options po on (po.ID = p.participant_status)
                  WHERE CandID=:cid", array('cid'=>$this->identifier));
        for($i = 0; $i< sizeof($result); $i++) {
            if($result[$i]['Description']=='Active' && empty($result[$i]['entry_staff']))
            {
                $result[$i]['entry_staff'] = 'Enrollment';
            }    
            
        }  
        $this->tpl_data['history_list'] = $result;

    }

    function _validate_add_family($values)
    {   
        if(!is_array($values) || count($values) ==0) {
            return true;
        }
        $cand = $values['SiblingID'];
        $DB =& Database::singleton();
        $errors = array();
        $results = $DB->pselect("SELECT CandID from candidate where Active='Y'" ,array());
        $activeCandidates = array();
        foreach($results as $row) {
            $activeCandidates[] = $row['CandID'];
        }
        if(!in_array($cand, $activeCandidates)){
            $errors['SiblingID']= 'Candidate should be part of study. Please enter correct CandID';
        }
        $familyID = $DB->pselectOne("SELECT FamilyID from family WHERE CandID=:cid",array('cid'=>$this->identifier));
        $relatives = $DB->pselect("SELECT CandID from family WHERE FamilyID=:fid",array('fid'=>$familyID));
        $active_family = array();
        foreach($relatives as $relative){
            $active_family[] = $relative['CandID'];    
        }
        if(in_array($cand, $active_family)){
            $errors['SiblingID'] = 'CandID already entered as Sibling';    
        }
        if(empty($values['relation_type'])) {
            $errors['relation_type'] = 'Please specify relationship type';    
        }
        if(empty($values['SiblingID'])) {
            $errors['relation_type'] = 'Please specify relationship type';    
        }
        return $errors;
    }
    

    /** 
     * This function is for validation of user input, depending on
     * the questions answered.
     *
     * @param array $fields The list of input to the form submitted by
     *                      smarty.
     *
     * @return array An array of elements with errors. An empty array if
     *               all elements are valid.
     */
    function _validate($fields)
    { 
        $config =& NDB_Config::singleton();
        $errors=array();
        $options = $this->getParticipantStatusOptionsVerbose();

        $DB =& Database::singleton();
        if($fields['ProbandDoB']['M'] != $fields['ProbandDoB2']['M'] ||
                $fields['ProbandDoB']['d'] != $fields['ProbandDoB2']['d'] ||
                $fields['ProbandDoB']['Y'] != $fields['ProbandDoB2']['Y'])
        { 
            $errors['ProbandDoB'] = 'Date of Birth Proband fields must match.';
        }

             // consent requirements
        $consent = $config->getSetting('ConsentModule');
        if ($consent['useConsent'] === 'true') {
            foreach (Utility::asArray($consent['Consent']) as $consenttype) {
                $fieldname = $consenttype['name'];
                $consentVal = $fields[$fieldname];
                $consentDate = $fields[$fieldname . '_date'];
                $consentWithdrawal = $fields[$fieldname . '_withdrawal'];
                $consent = date_create();
                $today = date('Y-m-d'); 
                $consent->setDate($consentDate['Y'], $consentDate['M'], $consentDate['d']);
                $consent = $consent->format('Y-m-d'); 
                if ($consent > $today) {
                    $errors[$fieldname.'_date'] = 'Cannot be later than today';

                }

                if (
                        $consentVal === 'yes' && (
                            empty($consentDate)
                            || empty($consentDate['Y'])
                            || empty($consentDate['M'])
                            || empty($consentDate['d'])
                            )
                   ) {
                    $errors[$fieldname . '_date'] = 'Required';
                }
                if (
                        !empty($consentWithdrawal['Y'])
                        && !empty($consentWithdrawal['M'])
                        && !empty($consentWithdrawal['d'])
                   ) {
                    $withdrawal = date_create();

                    $withdrawal->setDate($consentWithdrawal['Y'], $consentWithdrawal['M'], $consentWithdrawal['d']);
                    $withdrawal = $withdrawal->format('Y-m-d'); 
                    $diff = date_diff($withdrawal, $consent);                   
                    if ($withdrawal < $consent) {
                        $errors[$fieldname . '_withdrawal'] = 'Must be after date of consent';
                    } else if ($withdrawal > $today) {
                        $errors[$fieldname . '_withdrawal'] = 'Cannot be later than today';

                    } 
                }
                if($fields[$fieldname.'_withdrawal']['M'] != $fields[$fieldname.'_withdrawal2']['M'] ||
                        $fields[$fieldname.'_withdrawal']['d'] != $fields[$fieldname.'_withdrawal2']['d'] ||
                        $fields[$fieldname.'_withdrawal']['Y'] != $fields[$fieldname.'_withdrawal2']['Y'])
                {
                    $errors[$fieldname.'_withdrawal'] = 'Date of withdrawal fields must match.';
                }
                if($fields[$fieldname.'_date']['M'] != $fields[$fieldname.'_date2']['M'] ||
                        $fields[$fieldname.'_date']['d'] != $fields[$fieldname.'_date2']['d'] ||
                        $fields[$fieldname.'_date']['Y'] != $fields[$fieldname.'_date2']['Y'])
                {
                    $errors[$fieldname.'_date'] = 'Date of consent fields must match.';
                }


            }
        }
        if($fields['flagged_caveatemptor']=='true' && empty($fields['flagged_reason'])){
            $errors['flagged_reason'] = 'Please provide additional information for flagging candidate as Caveat Emptor';    
        }
        $fields['flagged_other'] =trim($fields['flagged_other']);
        if($fields['flagged_reason']== 3 && empty($fields['flagged_other'])){
            $errors['flagged_other_group'] = 'If Other, please specify details for cavear emptor';
        }

        if ($options[$fields['participant_status']]['Required'] == true) {
            $fields['participant_suboptions'] = trim($fields['participant_suboptions']);
            if(empty($fields['participant_suboptions'])) {
                $errors['participant_suboptions'] = "Please specify the status";
            }        
        }
        return $errors;
    }

    /**
     * Gets the participant_status options from participant_status_options
     * getParticipantStatusOptions()
     *
     * @return array Options array suitable for use in QuickForm select
     *               element
     */
    function getParticipantStatusOptions()
    {
        $DB =& Database::singleton();
        $options = $DB->pselect(
                "SELECT ID,Description FROM participant_status_options WHERE parentID IS NULL",
                array()
                );
        $option_array = array();
        foreach ($options as $option) {
            $option_array[$option['ID']] = $option['Description'];
        }
        return $option_array;
    }

    /**
     * Get the participant_status options as an array, where each row
     * is an array
     *
     * @return array An array of options, where each row is an array containing
     *               the entire row from participant_status_options instead of
     *               only the description
     */
    function getParticipantStatusOptionsVerbose()
    {
        $DB =& Database::singleton();
        $options = $DB->pselect(
                "SELECT * FROM participant_status_options",
                array()
                );

        $option_array = array();
        foreach ($options as $option) {
            $ID = $option['ID'];
            unset($option['ID']);
            $option_array[$ID] = $option;
        }
        return $option_array;
    }


}
?>
