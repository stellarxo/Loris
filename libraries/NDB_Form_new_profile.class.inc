<?php
/**
 * OVERWRITTEN SO ADD IBIS2 PLAN SUPPORT AND CHANGE PSCID
 * START NUMBER FOR IBIS2
 */
require_once "NDB_Form.class.inc";

/**
 * The forms for the new profile menu
 * @package main
 */
class NDB_Form_new_profile extends NDB_Form
{
    function _hasAccess()
    {
        // create user object
        $user =& User::singleton();

        $site =& Site::singleton($user->getData('CenterID'));
        if ($site->isStudySite()) {
            return $user->hasPermission('data_entry');
        }

        return false;
    }

    function _process($values)
    {
        // set up the arguments to Candidate::createNew
        $user =& User::singleton();
        $config =& NDB_Config::singleton();
        $dob = sprintf("%04d-%02d-%02d", $values['dob1']['Y'], $values['dob1']['M'], $values['dob1']['d']);
        
        if($config->getSetting('useEDC') == "true"){
            $edc = sprintf("%04d-%02d-%02d", $values['edc1']['Y'], $values['edc1']['M'], $values['edc1']['d']);
            if($edc == '0000-00-00') {
                $edc = NULL;
            }
        }

        // create the candidate
        $startNum = 0;
        if($values['ProjectID'] == 2) {
            $startNum = 1000;
        }
        $candID = Candidate::createNew($user->getData('CenterID'), $dob, $edc, $values['gender'], $values['PSCID'], $startNum);

        // get the candidate
        $candidate =& Candidate::singleton($candID);

        if($config->getSetting('useProjects') == "true") {
            $candidate->setData('ProjectID', $values['ProjectID']);

        }

        $db = Database::singleton(); 
	if( $values['ProjectID'] == '2'){
		$PTID = $db->pselectOne("SELECT ParameterTypeID FROM parameter_type WHERE Name='candidate_plan'", array());
		if(!is_numeric($PTID)) {
			throw new LorisException("Missing ParameterTypeID for candidate_plan");
		}
		$db->insert("parameter_candidate", array('ParameterTypeID' => $PTID,
					'CandID' => $candID,
					'Value' => $values['candidate_plan']
					));
	}
        //------------------------------------------------------------

        $this->tpl_data['success'] = true;
        $this->tpl_data['candID'] = $candID;
        $this->tpl_data['PSCID'] = $candidate->getPSCID();

        // freeze it, just in case
        $this->form->freeze();
    }

    function new_profile()
    {
        $config =& NDB_Config::singleton();
        $study = $config->getSetting('study');
        $dateOptions = array(
                             'language'        => 'en',
                             'format'          => 'YMd',
                             'addEmptyOption'  => true,
                             'minYear'         => $study['startYear'] - $study['ageMax'],
                             'maxYear'         => $study['endYear'] - $study['ageMin']
                             );

        // add date of birth
        $this->addBasicDate('dob1', 'Date of Birth', $dateOptions);
        $this->addBasicDate('dob2', 'Confirm Date of Birth', $dateOptions);
    
        // date of birth rules
        $this->form->addGroupRule('dob1', 'Date of Birth is required', 'required');
        $this->form->addGroupRule('dob2', 'Date of Birth confirmation is required', 'required');

        if($config->getSetting('useEDC') == "true"){
            // add expected date of confinement
            $this->addBasicDate('edc1', 'Expected Date of Confinement', $dateOptions);
            $this->addBasicDate('edc2', 'Confirm EDC', $dateOptions);

            // expected date of confinement rules
            $this->form->addRule(array('edc1', 'edc2'), 'EDC fields must match', 'compare');
        }

        if($config->getSetting("useProjects") == "true") {
            $projects = Utility::getProjectList();
            $projList = array('' => '');
            foreach($projects as $projectID => $projectName) {
                $projList[$projectID] = $projectName;
            }
            $this->addSelect('ProjectID', 'Project', $projList);
        }

        // add gender
        $genderOptions = array('' => '', 'Male' => 'Male', 'Female' => 'Female');
        $this->addSelect('gender', 'Gender', $genderOptions);
    
        // gender rules
        $this->form->addRule('gender', 'Gender is required', 'required');
        $this->addSelect("candidate_plan", 'Candidate Plan', 
            array(
                ''         => '',
                '3m_plan1' => '3m_plan1',
                '3m_plan2' => '3m_plan2',
                '3m_plan3' => '3m_plan3',
                '3m_plan4' => '3m_plan4',
                '6m_plan1' => '6m_plan1',
                '6m_plan2' => '6m_plan2',
                '6m_plan3' => '6m_plan3'
            )
        );
        $PSCIDsettings = $config->getSetting('PSCID');
        if($PSCIDsettings['generation'] == 'user') {
            $this->addBasicText('PSCID', 'PSCID');
        }
        $this->form->addFormRule(array(&$this, '_validate'));
    }
    function _validate($values)
    {
        $errors = array();

        $config =& NDB_Config::singleton();

        if($values['dob1']['M'] != $values['dob2']['M'] ||
                $values['dob1']['d'] != $values['dob2']['d'] ||
                $values['dob1']['Y'] != $values['dob2']['Y'])
        {
            $errors['dob1'] = 'Date of Birth fields must match.';
        }
        if($config->getSetting('useEDC') == "true") {
            if (strlen(implode($values['edc1'])) > 2 && !_checkDate($values['edc1'])) {
                $errors['edc1'] = 'EDC is not a valid date';
            }
            if($values['edc1']['M'] != $values['edc2']['M'] ||
                    $values['edc1']['d'] != $values['edc2']['d'] ||
                    $values['edc1']['Y'] != $values['edc2']['Y'])
            {
                $errors['edc1'] = 'Estimated Due date fields must match.';
            }

        }

        if (empty($values['gender'])) {
            $errors['gender'] = 'Gender is required.';
        } 
    
        $PSCIDsettings = $config->getSetting('PSCID');
        if($PSCIDsettings['generation'] == 'user') {
            $db =& Database::singleton();
            $user =& User::singleton();
            $centerID = $user->getData('CenterID');
            $site =& Site::singleton($centerID);

            if(empty($values['PSCID'])) $errors['PSCID'] = 'PSCID must be specified';
            elseif(!Candidate::validatePSCID($values['PSCID'], $site->getSiteAlias())) $errors['PSCID'] = 'PSCID does not match the required structure';
            elseif($db->selectOne("SELECT count(PSCID) FROM candidate WHERE PSCID='$values[PSCID]'") > 0) $errors['PSCID'] = 'PSCID has already been registered';
        }
        $useProjects = $config->getSetting('useProjects');
        if($useProjects === "true" && empty($values['ProjectID'])) {
            $errors['ProjectID'] = "Project is required";
        }

        if(empty($values['candidate_plan']) && $values['ProjectID'] == '2') {
            $errors['candidate_plan'] = 'Plan is required for IBIS2';
        }
        elseif(!empty($values['candidate_plan']) && $values['ProjectID'] != '2') {
            $errors['candidate_plan'] = 'Candidate Plan is not required for non-IBIS2 candidates';
        }
        //$this->form->addRule('candidate_plan', 'Plan is required', 'required');
        return $errors;
    }

}
?>
