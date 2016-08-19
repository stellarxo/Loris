<?php
/**
 * This file contains the NDB_Form_candidate_parameters class
 *
 * PHP Version 5
 *
 * @category Module
 * @package  Candidate Parameter
 * @author   MOB <mob@gmail.com>
 * @license  http://www.gnu.org/licenses/gpl-3.0.txt GPLv3
 * @link     https://www.github.com/aces/Loris/
 */

require_once 'NDB_Form.class.inc';

/**
 * Main class for candidate_parameters module corresponding to /candidate_parameters/ URL
 * Child or Clinical section of the LorisMenu.
 *
 * Displays a list of candidate_parameters files and control panel to search them and upload
 * new ones.
 *
 * PHP Version 5
 *
 * @category Module
 * @package  Candidate Parameter
 * @author   MOB <mob@gmail.com>
 * @license  http://www.gnu.org/licenses/gpl-3.0.txt GPLv3
 * @link     https://www.github.com/aces/Loris/
 */
class NDB_Form_candidate_parameters extends NDB_Form
{
    public $hasWritePermission = false;

    /**
     * Check user permissions
     *
     * @return bool
     * @throws ConfigurationException
     */
    function _hasAccess()
    {
        //create user object
        $user =& User::singleton();

        // Set global permission to control access to different modules of candidate_parameters page
        $this->hasWritePermission = $user->hasPermission('candidate_parameter_edit');

<<<<<<< HEAD
        return $user->hasPermission('candidate_parameter_view');
=======
        $this->tpl_data['candidate_parameter_edit'] = $user->hasPermission('candidate_parameter_edit');

        // check user permissions
        return (($user->hasPermission('access_all_profiles') ||
        $user->getData('CenterID') == $candidate->getData('CenterID')) &&
            ($user->hasPermission('candidate_parameter_edit')||
                $user->hasPermission('candidate_parameter_view'))
        );
    }
     /**
      * Returns default values for all candidate parameters
      *
      * @return default array
      */
    function _getDefaults()
    {
        $DB     =& Database::singleton();
        $config =& NDB_Config::singleton();
        //Get the default values
        $value_results = $DB->pselect("SELECT ParameterTypeID, Value FROM 
                         parameter_candidate WHERE CandID=:CaID", 
                         array('CaID' => $this->identifier));
        $candidate_dob = $DB->pselectOne("SELECT DoB FROM candidate 
                                         WHERE CandID=:CandidateID", 
                                         array('CandidateID' => $this->identifier));

        if ($config->getSetting('useProband') === 'true') {
            $proband_info = $DB->pselectRow("SELECT ProbandDoB,ProbandGender FROM
                    candidate WHERE CandID=:CandidateID",
                    array('CandidateID' => $this->identifier));
            if ($proband_info['ProbandDoB']=== '0000-00-00') {
                $proband_info['ProbandDoB'] = '';
            }
            if (!empty($proband_info['ProbandDoB']) & !empty($candidate_dob) ) {
                $age = Utility::calculateAge($proband_info['ProbandDoB'],
                                             $candidate_dob);
                $defaults['Age_Difference'] = $age['year']*12 + $age['mon'] + 
                        round($age['day']/30, 2);
            } else {
                $defaults['Age_Difference'] = 'Could not calculate age';
            }
            $this->tpl_data['proband_info'] = $proband_info;
            foreach ($proband_info as $key=>$val) {
                $defaults[$key] = $val;
                if ($key == 'ProbandDoB') {
                    $defaults[$key."2"] = $proband_info[$key];
                }
            }
        }

        $familyid = $DB->pselectOne("SELECT FamilyID from family WHERE 
                                    CandID=:CandidateID",
                                    array('CandidateID'=>$this->identifier));
        $this->tpl_data['familyID'] = $familyid;
        $relations                  = $DB->pselect("SELECT CandID, Relationship_type 
            FROM family WHERE FamilyID=:fam_id AND 
            CandID <> '$this->identifier'",
            array('fam_id'=> $familyid));

        $this->tpl_data['sibling_list'] = array();
        foreach ($relations as $relation) {
            $relation['Relationship_type']    = $this->relationType[$relation['Relationship_type']];
            $this->tpl_data['sibling_list'][] = $relation;
        }
       
        $emptor_info = $DB->pselectRow("SELECT flagged_caveatemptor,flagged_reason,flagged_other
                                        FROM candidate WHERE CandID=:CandidateID",
                                        array('CandidateID' => $this->identifier));
        foreach ($emptor_info as $key=>$val) {
            if ($key == 'flagged_reason') {
                $reason = $DB->pselectOne("SELECT Description AS Reason FROM candidate c 
                                           JOIN caveat_options o ON (o.ID = c.flagged_reason) 
                                           WHERE CandID=:CandidateID",
                                           array('CandidateID' => $this->identifier));
                if (!empty($reason)) {
                   $cand_info['flagged_reason'] = $reason; 
                }
            } else {
                $cand_info[$key]= $val;
            }
         
         }

        $value_results = $DB->pselect("SELECT ParameterTypeID, Value FROM parameter_candidate 
                     WHERE CandID=:cid",
                array('cid' => $this->identifier)
            );
        foreach ($value_results AS $vresult) {
            if (!empty($vresult['Value'])) {
                $cand_info["PTID_".$vresult['ParameterTypeID']] = $vresult['Value'];
            }
        }
        $this->tpl_data['params_list'] = $cand_info;
        foreach ($cand_info as $key=>$val) {
            if ($key == 'flagged_reason') {
                $defaults[$key] = $emptor_info[$key];
            } else {
                $defaults[$key] = $val;
            }
        }
 
       // Getting participant status default values
        $ps_info = $DB->pselectRow("SELECT study_consent,study_consent_date,study_consent_withdrawal,
                                    reason_specify,participant_status,participant_suboptions
                                    FROM participant_status
                                    WHERE CandID = :cid", array('cid'=>$this->identifier));
        if (empty ($ps_info['participant_status'])) {
            //set candidate to active by default
          $this->tpl_data['pstat'] = $DB->pselectOne("SELECT ID FROM participant_status_options WHERE
                                                        Description=:desc", array('desc'=>'Active'));

        } else {
           $this->tpl_data['pstat']     = $ps_info['participant_status'];
           $this->tpl_data['pstat_sub'] = $ps_info['participant_suboptions'];
        }
        foreach ($ps_info as $key => &$val) {

            if ($val === '0000-00-00') {
                $val = '';
            }
            if (!empty($ps_info[$key])) {
                $consent_info[$key] = $val;
            }
        }
 
	foreach ($consent_info as $key=>$val) {
		$defaults[$key] = $val;
		if(strpos($key,"_date") !== FALSE || strpos($key,"_withdrawal") !== FALSE) {
			$defaults[$key."2"] = $consent_info[$key];
		}
	}

        $consent                           = $config->getSetting('ConsentModule');
        $this->tpl_data['display_consent'] = false;
        if ($consent['useConsent'] === 'true') {
            $this->tpl_data['display_consent'] = true;
        }
        $this->tpl_data['display_proband'] = false;
        if ($config->getSetting('useProband') === 'true') {
            $this->tpl_data['display_proband'] = true;
        }
        $this->tpl_data['display_family'] = false;
        if ($config->getSetting('useFamilyID') === 'true') {
            $this->tpl_data['display_family'] = true;
        }
        $this->tpl_data['consent_info'] = $consent_info;
        $result                         = $DB->pselect("SELECT participant_status, entry_staff, 
                                          data_entry_date FROM participant_status_history
                                          WHERE CandID=:cid", array('cid'=>$this->identifier));
        for ($i=0; $i < sizeof($result); $i++) {
            $row                                       = $result[$i];
            $desc                                      = $DB->pselectOne("SELECT Description FROM participant_status_options 
                                                         WHERE ID=:pid", array('pid'=>$row['participant_status']));
            $this->participant_history["status".$i]    = $desc;
            $this->participant_history["staff".$i]     = $row['entry_staff'];
            $this->participant_history["timestamp".$i] = $row['data_entry_date'];
        }
        return $defaults;
    }

    function _process($values)
    {
        if(!is_array($values) || count($values) ==0) {
        	return true;
        }
        $DB               =& Database::singleton();
        $values['CandID'] = $this->identifier;
        unset($values['ProbandDoB2']);
 
        $config  =& NDB_Config::singleton();
        $consent = $config->getSetting('ConsentModule');
        if ($consent['useConsent'] === 'true') {
            foreach (Utility::asArray($consent['Consent']) as $question) {
                unset($values[$question['name'].'_date2']);
                unset($values[$question['name'].'_withdrawal2']);
            }
        }
        if (!(is_null($_SESSION['State']))) {
            $currentUser           =& User::singleton($_SESSION['State']->getUsername());
            $id                    = $currentUser->getData("UserID");
            $values['entry_staff'] = $id;
        }

        while (list($key, $value) = each($values)) {
        	$set="";
            if (strpos($key, "PTID_") === 0) {
                $set['ParameterTypeID'] = str_replace("PTID_","",$key);
                $set['CandID']          = $this->identifier;
                $set['Value']           = $value;
                $set['InsertTime']      = time();
                
                //delete old values
                $DB->delete("parameter_candidate", array("CandID"=>$this->identifier,
                            "ParameterTypeID"=>$set['ParameterTypeID']));
                //insert new values
                $DB->insert("parameter_candidate", $set);
            } else if($key == 'ProbandDoB' || $key == 'ProbandGender'
                      || $key =='flagged_caveatemptor' || $key == 'flagged_reason' || $key == 'flagged_other'
                      || $key == 'flagged_other_status') {
                if($key == 'ProbandDoB') {
                    $value = $this->_getDatabaseDate($value);
                }
                if(!empty($value)) {
                    $DB->update("candidate", array($key => $value), array('CandID' => $this->identifier));
                }
                if ($key == 'ProbandDoB') {
                    $tests = $DB->pselect(
                        "SELECT f.CommentID, f.Test_name 
                        FROM flag f JOIN session s ON (f.SessionID=s.ID)
                        JOIN candidate c ON (c.CandID=s.CandID)
                        WHERE
                        c.CandID=:CaID AND f.Test_name LIKE '%proband'", array('CaID' => $this->identifier)
                    );
                    foreach ($tests as $test) {
                        $inst     = NDB_BVL_Instrument::factory($test['Test_name'], $test['CommentID'], null, false);
                        $setValue = array('Date_taken' => $inst->getFieldValue('Date_taken'));
                        $inst->_saveCandidateAge($setValue);
                        $DB->update($test['Test_name'], $setValue, array('CommentID' => $test['CommentID']));
                    }

                }
            }
           
        }

       if (isset($values['FamilyMemberID'])) { 
           $fid = $DB->pselectOne("SELECT FamilyID FROM family WHERE CandID=:CaID", array('CaID' => $this->identifier));
           if (empty($fid)) {
               $famID = $DB->pselectOne("SELECT max(FamilyID) from family");
               if (empty($famID)) {
                   $famID = 0;
               }
               $fid = $famID+1;
               $success = $DB->insert('family', array('CandID'=>$this->identifier, 'FamilyID'=>$fid,
                           'Relationship_type'=>$values['relation_type']));

           }

           $value   = $values['FamilyMemberID'];
           $success = $DB->insert('family', array('CandID'=>$value,'FamilyID'=>$fid,
                                  'Relationship_type'=>$values['relation_type']));
          
       }
       // updating participant status
        if (isset($values['participant_status']) || isset($values['reason_specify'])
            || isset($values['reason_specify_status']) || isset($values['participant_suboptions'])) {
            $participant_vals                       = array();
            $participant_vals['participant_status'] = $values['participant_status'];

            //Due to the AJAX call for dydnamic suboptions dropdown generation,
            //the vavlue of $values['participant_suboptions'] could be either
            //numeric (if coming from a previously "inactive" option or a string
            //this if statement deals with the case

            if (!is_numeric($values['participant_suboptions']))
            {
                $values['participant_suboptions']  = $DB->pselectOne("
                                  SELECT ID
                                  FROM participant_status_options
                                  WHERE Description=:sub_desc",
                    array('sub_desc' =>$values['participant_suboptions']));
            }
            /*if (empty($sub_reasonID)) {
                $participant_vals['participant_suboptions'] = NULL;
            } else {
                $participant_vals['participant_suboptions'] = $sub_reasonID;
            }
             */
           $participant_vals['participant_suboptions']= $values['participant_suboptions'];
           $participant_vals['entry_staff']           = $id;
           $participant_vals['reason_specify']        = $values['reason_specify'];
           $participant_vals['reason_specify_status'] = $values['reason_specify_status'];
           $participant_vals['CandID']                = $values['CandID'];
          
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

           $current_status = $DB->pselectRow("SELECT * FROM participant_status_history
                                              WHERE CandID = :cid ORDER BY data_entry_date DESC", 
                                              array("cid"=>$values['CandID']) );

           if($current_status['participant_status'] != $participant_vals['participant_status'] ||
               $current_status['entry_staff'] != $participant_vals['entry_staff'] ||
               $current_status['reason_specify'] != $participant_vals['reason_specify'] ||
               $current_status['participant_subOptions'] != $sub_reasonID) {
               $success = $DB->insert("participant_status_history", 
                          array('participant_status'=>$participant_vals['participant_status'], 
                                'participant_subOptions'=>$participant_vals['participant_suboptions'],
                                'entry_staff'=>$participant_vals['entry_staff'],
                                'CandID' => $participant_vals['CandID'],
                                'reason_specify'=>$participant_vals['reason_specify'],
                                'reason_specify_status'=>$participant_vals['reason_specify_status']));
           }
          
       }

       //updating consent information
       $config  =& NDB_Config::singleton();
       $consent = $config->getSetting('ConsentModule');
       if ($consent['useConsent'] === 'true') {

           $participant_vals = array();
           foreach (Utility::toArray($consent['Consent']) as $question) {
               $participant_vals[$question['name']] = $values[$question['name']];
               $consent_dates = array($question['name'].'_date',$question['name'].'_withdrawal');
               foreach($consent_dates as $field) {
                   $value = $this->_getDatabaseDate($values[$field]);
                   if($value === '--') {
                       $value = '';
                   }
                   $participant_vals[$field] = $value;  
               }
           }
           $participant_vals['entry_staff'] = $id;
           $participant_vals['CandID']      = $values['CandID'];
           //if it exists update it
           $ParticipantCount = $DB->pselectOne(
                   "SELECT COUNT(*) FROM participant_status WHERE CandID = :cid", 
                   array("cid"=>$values['CandID'])
                   );

           // Insert to consent_info_history table first, before participant_status
           // because else{} below adds a column specific to participant_status table
           $success = $DB->insert("consent_info_history", $participant_vals); 

           if ($ParticipantCount > 0) {
               $success = $DB->update(
                       "participant_status", 
                       $participant_vals,
                       array("CandID"=>$values['CandID'])
                       );
           } else {
               //insert it
               $participant_vals['participant_status'] = 1; // 1 is Active which should be default
               $success = $DB->insert("participant_status",$participant_vals);
           }

       }
       $this->tpl_data['success'] = true;

        // freeze it, just in case
        $this->form->freeze();
    }


    function _getInstrumentInfo($instrument, $param) {
        $DB  =& Database::singleton();

        $ret = $DB->pselectOne("SELECT t.$param FROM flag f JOIN $instrument t ON (t.CommentID=f.CommentID) 
                               JOIN session s ON (f.SessionID=s.ID) WHERE 
                               s.CandID=" . $DB->quote($this->identifier) . ' 
                               AND f.test_name=' . $DB->quote($instrument) . ' 
                               AND t.CommentID NOT LIKE \'DDE_%\'',
            array()
        );
        if ($ret == array()) {
            return;
        }
        return $ret;
>>>>>>> e557c55559613286506e9db9b75c9ba6a952effb
    }

    /**
     * @throws DatabaseException
     */
    function candidate_parameters()
    {
        $DB =& Database::singleton();
        $config =& NDB_Config::singleton();

        $candidate =& Candidate::singleton($this->identifier);

        // candID
        $this->tpl_data['candID'] = $candidate->getData('CandID');

<<<<<<< HEAD
        // consent
=======
        $this->addScoreColumn('flagged_caveatemptor','Caveat Emptor flag for Candidate');
        $this->addScoreColumn('flagged_reason',$this->indent.'Reason for Caveat Emptor flag');
        $this->addScoreColumn('flagged_other', $this->indent.'Additional Comments for flag');

 		//Extract the fields from the parameter_type table
        $field_results = $DB->pselect("SELECT pt.ParameterTypeID, pt.Name, pt.Type, Description 
                     FROM parameter_type as pt, parameter_type_category as ptc, parameter_type_category_rel as ptcr 
                     WHERE pt.ParameterTypeID=ptcr.ParameterTypeID AND ptcr.ParameterTypeCategoryID=ptc.ParameterTypeCategoryID 
                     AND ptc.Name='Candidate Parameters' ORDER BY pt.ParameterTypeID, pt.name ASC",
            array()
        );
        //If there are no defined fields print a message to that effect
        if (empty($field_results)) {
            $this->addScoreColumn("static", "No candidate parameters have been defined for this study");
            return;
        }
        
        //Loop through the fields and add them appropriately
        foreach ($field_results AS $fresult) {
            $this->addScoreColumn("PTID_".$fresult['ParameterTypeID'], $fresult['Description']);
        }
        
        $this->addScoreColumn('ProbandDoB', 'DoB Proband:');
        $this->addScoreColumn('ProbandGender', 'Proband gender:');
        $this->addScoreColumn('Age_Difference','Age Difference between candidate<BR> and proband (in months):');

        $this->addScoreColumn('SiblingcID','Family Member ID:'); 
        $this->addScoreColumn('relation_type','Relationship:');
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

        $options = self::getParticipantStatusOptions();
        $options = array('') + $options;
        $this->tpl_data['pstatus_options'] = $options;
        $this->tpl_data['pstat'] = $_REQUEST['participant_status'];
        $this->addTextAreaGroup('reason_specify',"Comments",array(null=>'','not_answered'=>'Not Answered'));
        
        //Consent Information
        $result = $DB->pselect("SELECT po.Description,ps.Description as Details, entry_staff, data_entry_date,reason_specify
                FROM participant_status_history p join participant_status_options po on (po.ID = p.participant_status)
                left join participant_status_options ps on (ps.ID = p.participant_subOptions)
                WHERE CandID=:cid", array('cid'=>$this->identifier));
        for ($i = 0; $i< sizeof($result); $i++) {
            if($result[$i]['Description'] =='Active' && empty($result[$i]['entry_staff']))
            {
                $result[$i]['entry_staff'] = 'Enrollment';
            }

        }
        $this->tpl_data['history_list'] = $result;
        $config                         =& NDB_Config::singleton();
        $consent                        = $config->getSetting('ConsentModule');
        if ($consent['useConsent'] === 'true') {
            foreach (Utility::toArray($consent['Consent']) as $question) {
                $consentQuestion = array($question['name']=> $question['label'],
                                         $question['name'] . '_date' => "Date of <BR> $question[label]",
                                         $question['name'] . '_withdrawal' => "Date of withdrawal <BR> of $question[label]",
                                         'entry_staff'=>'Data Entry Staff',
                                         'data_entry_date' =>'Date Updated',
                                        );
                $fields = $question['name'].', '.$question['name'] . '_date, '.$question['name'] . '_withdrawal, ';
                $study_consent = $DB->pselect("SELECT $fields entry_staff,data_entry_date
                                               FROM consent_info_history WHERE CandID=:cid", 
                                               array('cid'=>$this->identifier));
               $study_consent_hist = array();
                for ($i=0; $i<sizeof($study_consent); $i++ ) {
                    foreach($consentQuestion as $key => $column_title) {
                          if ($key == $question['name'] && empty($study_consent[$i][$question['name']])) {
                              break;
                          }

                         if (!empty($study_consent[$i][$question['name']])) {
                             $study_consent_hist[$i][$key] = $study_consent[$i][$key];
                         }
                    }
                }

            $this->tpl_data['consent_list'][$question['name']] = array('label'=>$consentQuestion,
                                                                       'history'=>$study_consent_hist);
            }
        }
        $this->form->addFormRule(array(&$this,'_validate'));
    }

    /* This is taken from NDB_BVL_Instrument. It should be moved to NDB_Page once NDB_Page is merged. */

    function _getDatabaseDate ($formDateValue) {
        if (!empty($formDateValue)) {
            // check if it's already formatted correctly
            if (is_string($formDateValue) && preg_match("/^[\d]{4}-[\d]{2}-[\d]{2}$/", $formDateValue)) {
                return $formDateValue;
            }
            if (count($formDateValue)==2) {
                $databaseValue = "$formDateValue[H]:$formDateValue[i]";  //handle time (HH:MM:SS)
            } else {
                $databaseValue = "$formDateValue[Y]-$formDateValue[M]-$formDateValue[d]";  //handle date (YYYY/MM/DD)
            }
        }
        return $databaseValue;
    }

    function add_family() {
        $DB =& Database::singleton();

        $pscid = $DB->pselectone(
                'SELECT PSCID FROM candidate where CandID = :candid',
                array('candid'=>$this->identifier)
                );
        $this->addScoreColumn('pscid', 'PSCID');
        $this->tpl_data['candID'] = $this->identifier;

        $this->tpl_data['pscid']  = $pscid;

        $this->addBasicText('FamilyMemberID','Family Member ID:<BR/> (Enter DCCID)' );
        $this->addSelect('relation_type','Relation Type', $this->relationType);
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
        $parentID = $DB->pselectOne('SELECT participant_status FROM participant_status Where CandID = :candid',
                                     array('candid'=>$this->identifier));
        $sub_options = self::getParticipantStatusSubOptions($parentID);
        $sub_options = array('') + $sub_options;
        $options = self::getParticipantStatusOptions();
      //  $options = array('') + $options;
        $this->tpl_data['pstatus_options'] = $options;
        $this->tpl_data['pstatus_suboptions'] = $sub_options;
        //$this->tpl_data['pstat'] = $_REQUEST['participant_status'];
        $this->addSelect('participant_status', "Participant Status", $options);
        $this->addSelect('participant_suboptions', "Specify Reason for status<BR>(Required only for status Inactive/Incomplete)", $sub_options);
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
        $this->addSelect('flagged_caveatemptor','Caveat Emptor flag for candidate', 
                                 array(''=>'','true'=>'True','false'=>'False'));
        $this->addSelect('flagged_reason',$this->indent.'Reason for Caveat Emptor flag',
                                $caveat_options);
        $this->addTextAreaGroup('flagged_other',$this->indent.'If Other, please specify',
                                          array(null=>'','not_answered'=>'Not Answered'));
        //Extract the fields from the parameter_type table
        $field_results = $DB->pselect("SELECT pt.ParameterTypeID, pt.Name, pt.Type, Description FROM parameter_type as pt, 
                     parameter_type_category as ptc, parameter_type_category_rel as ptcr 
                     WHERE pt.ParameterTypeID=ptcr.ParameterTypeID AND ptcr.ParameterTypeCategoryID=ptc.ParameterTypeCategoryID 
                     AND ptc.Name='Candidate Parameters' ORDER BY pt.ParameterTypeID, pt.name ASC",
            array()
        );
        //If there are no defined fields pritn a message to that effect
        if (empty($field_results)) {
        	$this->addScoreColumn("static", "No candidate parameters have been defined for this study");
        	return;
        }
        
        //Loop through the fields and add them appropriately
        foreach ($field_results AS $fresult) {
        	switch(substr($fresult['Type'],0,3)) {
        		case "enu":
        			$options = substr($fresult['Type'],4);
        			$options = trim($options,"()");
        			$options = Utility::explodeEncapsulated(",", "'", $options);
                    $elOptions = array('' => '');
                    foreach ($options as $option) {
                        $elOptions[$option] = $option;
                    }
        			$this->addSelect("PTID_".$fresult['ParameterTypeID'], $fresult['Description'], $elOptions);
        		break;
        		
        		case "dat":
        			$this->addBasicDate("PTID_".$fresult['ParameterTypeID'], $fresult['Description'], $dateOptions);
        		break;
        		
        		case "int":
        		case "var":
        		case "tex":
            default:
        			$this->addBasicTextArea("PTID_".$fresult['ParameterTypeID'], $fresult['Description']);
        		
        	}
        	$this->tpl_data['elements_list'][]="PTID_".$fresult['ParameterTypeID'];
        }
        $this->form->addFormRule(array(&$this,'_validate'));

    }
 
    function update_proband_info() {

        $DB =& Database::singleton();
        $pscid = $DB->pselectone(
                'SELECT PSCID FROM candidate where CandID = :candid',
                array('candid'=>$this->identifier)
                );
        $this->addScoreColumn('pscid', 'PSCID');
        $this->tpl_data['candID'] = $this->identifier;

        $this->tpl_data['pscid'] = $pscid;
        
        $config             =& NDB_Config::singleton();
        $probandDateOptions = array(
            'language' => 'en',
            'format'   => 'YMd',
            'minYear'  => $config->getSetting('startYear') - 20, //allows for proband siblings up to 20 years older than candidate
            'maxYear'  => $config->getSetting('endYear'),
            'addEmptyOption' => true,
            'emptyOptionValue' => null
        );

        $this->addBasicDate('ProbandDoB', 'DoB Proband:', $probandDateOptions);
        $this->addBasicDate('ProbandDoB2', 'Confirm DoB Proband:', $probandDateOptions);
        $this->addSelect('ProbandGender', 'Proband gender:', array('' => '','Male' => 'Male', 'Female' => 'Female') );
        
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

        $this->tpl_data['pscid']  = $pscid;
       
       // Add questions about consent
        $config =& NDB_Config::singleton();
>>>>>>> e557c55559613286506e9db9b75c9ba6a952effb
        $consent = $config->getSetting('ConsentModule');
        $this->tpl_data['useConsent'] = $consent['useConsent'];
    }

    /**
     * Include additional CSS files:
     *  1. candidate_parameters.css
     *
     * @return array of css to be inserted
     */
    function getCSSDependencies()
    {
        $factory = NDB_Factory::singleton();
        $baseURL = $factory->settings()->getBaseURL();
        $deps    = parent::getCSSDependencies();
        return array_merge(
            $deps,
            [$baseURL . "/candidate_parameters/css/candidate_parameters.css"]
        );
    }

    /**
     * Include the column formatter required to display the feedback link colours
     * in the candidate_list menu
     *  1. candidateInfo.js
     *  2. probandInfo.js
     *  3. familyInfo.js
     *  4. participantStatus.js
     *  5. consentStatus.js
     *
     * @return array of javascript to be inserted
     */
    function getJSDependencies()
    {
        $factory = NDB_Factory::singleton();
        $baseURL = $factory->settings()->getBaseURL();
        $deps = parent::getJSDependencies();
        return array_merge(
            $deps,
            array(
                $baseURL . "/candidate_parameters/js/candidateInfo.js",
                $baseURL . "/candidate_parameters/js/probandInfo.js",
                $baseURL . "/candidate_parameters/js/familyInfo.js",
                $baseURL . "/candidate_parameters/js/participantStatus.js",
                $baseURL . "/candidate_parameters/js/consentStatus.js"
            )
        );
    }
}
