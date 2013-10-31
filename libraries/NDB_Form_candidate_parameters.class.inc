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
        	$defaults["PTID_".$vresult['ParameterTypeID']]=$vresult['Value'];
        }
        $defaults['CandidateGUID'] = $DB->pselectOne("SELECT CandidateGUID FROM candidate WHERE CandID=:CandidateID", array('CandidateID' => $this->identifier));
        $defaults['ProbandGUID'] = $DB->pselectOne("SELECT ProbandGUID FROM candidate WHERE CandID=:CandidateID", array('CandidateID' => $this->identifier));
        $defaults['ProbandDoB'] = $DB->pselectOne("SELECT ProbandDoB FROM candidate WHERE CandID=:CandidateID", array('CandidateID' => $this->identifier));
        if( $defaults['ProbandDoB']=== '0000-00-00') {
            $defaults['ProbandDoB'] = '';
        }
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
        $defaults['flagged_caveatemptor'] = $DB->pselectOne("SELECT flagged_caveatemptor FROM candidate WHERE CandID=:CandidateID", array('CandidateID' => $this->identifier));
        $defaults['flagged_info'] = $DB->pselectOne("SELECT flagged_info FROM candidate WHERE CandID=:CandidateID", array('CandidateID' => $this->identifier));

        // Getting participant status default values

        $ps_info = $DB->pselectRow("SELECT * FROM participant_status WHERE CandID = :cid", 
                                    array('cid'=>$this->identifier));
        foreach($ps_info as $key => &$val) {
            if($key == 'participant_subOptions') {
                $defaults[$key] = $DB->pselectOne("SELECT Description from participant_status_options WHERE ID = :pid",
                        array('pid'=>$val));

            }
            if($val === '0000-00-00') {
                $val = '';
            }
            $defaults[$key] = $val;
        }
        return $defaults;
    }

    function _process($values)
    {   
        if(!is_array($values) || count($values) ==0) {
        	return true;
        }
        
        $DB =& Database::singleton();
        $values['CandID'] = $this->identifier;

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
                      || $key =='flagged_caveatemptor' || $key == 'flagged_info') {
                if($key == 'ProbandDoB') {
                    $value = $this->_getQuickformDate($value);
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
            if(strrpos($key, "consent_date") !== FALSE || strrpos($key, "consent_withdrawal") !== FALSE || 
               strrpos($key,"_consent") !== FALSE ) {
               
                if(strrpos($key, "consent_date") !== FALSE || strrpos($key, "consent_withdrawal") !== FALSE) {
                $value = $this->_getDatabaseDate($value);
                    if($value === '--') {
                        $value = '';
                    }
                } 
                $DB->update("participant_status", array($key =>$value), array('CandID' => $this->identifier));    
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
       if(isset($values['participant_statusID'])) {
           $participant_vals = array();
           $participant_vals['participant_statusID'] = $values['participant_statusID'];
           $sub_reasonID = $DB->pselectOne("SELECT ID FROM participant_status_options WHERE Description=:sub_desc", 
                   array('sub_desc' =>$values['participant_subOptions']));

           $participant_vals['participant_subOptions'] = $sub_reasonID;
           $participant_vals['reason_specify'] = $values['reason_specify'];
           $participant_vals['reason_specify_status'] = $values['reason_specify_status'];
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
               $success = $DB->insert("participant_status", $participant_vals);
           }

           if (Utility::isErrorX($success)) {
               return PEAR::raiseError(
                       "NDB_Form_candidate_parameters::_process: ".$success->getMessage()
                       );
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
        $this->form->addElement('select', 'ProbandGender', 'Proband gender:', array('' => '','Male' => 'Male', 'Female' => 'Female') );
        $this->form->addElement('static', 'dob_proband_adi_r', 'DoB of Proband (ADI-R):', $DoB_ADI_R);
        $this->form->addElement('static', 'dob_proband_vineland', 'DoB of Proband (Vineland):', $DoB_Vineland);
        $this->form->addElement('static', 'Age_Difference','Age Difference (in months):');
        $this->form->addElement('static', 'mother_race', 'Mother\'s Race:', $this->_getTSIinfo("mother_race"));
        $this->form->addElement('static', 'father_race', 'Father\'s Race:', $this->_getTSIinfo("father_race"));
        $this->form->addElement('static', 'birth_city', 'City of Birth:', $this->_getTSIinfo("city_of_birth"));
        $this->form->addElement('static', 'home_lang', 'Primary Language At Home:', $this->_getTSIinfo("primary_language"));
        $this->form->addElement('static','SiblingcID','Sibling ID:'); 
        $this->form->addElement('select','flagged_caveatemptor','Candidate flagged for Caveat Emptor', 
                                 array(''=>'','true'=>'True','false'=>'False'));
        $this->form->addElement('select','flagged_info',$this->indent.'Please provide additional information',
                                 array(''=>'','older_sibling_autism'=>'Older Sibling diagnosed with autism. Child moved from LR to HR', 'family_excluded'=>'Family met exclusionary criteria after enrollment in study'));

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
        $this->tpl_data['pstat'] = $_REQUEST['participant_statusID'];

        $this->addTextAreaGroup('reason_specify', $this->indent.'Other Comments',
                array(null=>null,'not_answered'=>'Not Answered')); 
        // Add questions about consent
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
                $withdrew = $this->addBasicDate($question['name'] . '_withdrawal', 
                        "Date of withdrawal of $question[label] (optional)", $dateOptions);
                $consentQuestions[] = array(
                        $question['name'],
                        $question['name'] . '_date',
                        $question['name'] . '_withdrawal'
                        );
            }
            $this->tpl_data['consent'] = $consentQuestions;
        }

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
        $this->tpl_data['candID'] = $_REQUEST['candID']; 


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
//print_r($fields);
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

            }
        }
        if($fields['flagged_caveatemptor']=='true' && empty($fields['flagged_info'])){
            $errors['flagged_info'] = 'Please provide additional information for flagging candidate as Caveat Emptor';    
        }
        if ($options[$fields['participant_statusID']]['Required'] == true) {
            $fields['participant_subOptions'] = trim($fields['participant_subOptions']);
            if(empty($fields['participant_subOptions'])) {
                $errors['reason_specify'] = "Please specify the status";
            }        
        }


//print_r($errors); 
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
/*
    function _getDatabaseDate($formDateValue){
        if(!empty($formDateValue)){
            // check if it's already formatted correctly
            if(is_string($formDateValue) && preg_match("/^[\d]{4}-[\d]{2}-[\d]{2}$/", $formDateValue)) {
                return $formDateValue;
            }
            if(count($formDateValue)==2){
                $databaseValue = "$formDateValue[H]:$formDateValue[i]";  //handle time (HH:MM:SS)
            } else {
                $databaseValue = "$formDateValue[Y]-$formDateValue[M]-$formDateValue[d]";  //handle     date (YYYY/MM/DD)
            }
        }
        return $databaseValue;
    }

 */
    /**
     * Convert a database date or timestamp into a QuickForm acceptable date or time
     *
     * @param string  $databaseValue        the date or timestamp from the database
     * @return array   $formDateValue       the quickform date/timestamp array
     * @access private
     */
    function _getQuickformDate($databaseValue){
        $formDateValue = null;
        if(!empty($databaseValue)){
            if(strstr($databaseValue,":")){
                $formDateValue=explode(":",$databaseValue);
                $formDateValue=array("H"=>$formDateValue[0],"i"=>$formDateValue[1]);  //handle time
            } else {
                // split mysql Date_taken field into array
                $formDateValue = explode('-', $databaseValue);
                $formDateValue = array('Y'=>$formDateValue[0], 'M'=>$formDateValue[1], 'd'=>$formDateValue[2]);  //handle date
            }
        }
        return $formDateValue;
    }

}
?>
