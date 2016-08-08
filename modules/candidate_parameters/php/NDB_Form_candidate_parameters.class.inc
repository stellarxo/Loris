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

        return $user->hasPermission('candidate_parameter_view');
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

//        $this->addScoreColumn('flagged_caveatemptor', 'Caveat Emptor flag for Candidate');
//        $this->addScoreColumn('flagged_reason', $this->indent . 'Reason for Caveat Emptor flag');
//        $this->addScoreColumn('flagged_other', $this->indent . 'Additional Comments for flag');

        //Extract the fields from the parameter_type table
        $DB->select("SELECT pt.ParameterTypeID, pt.Name, pt.Type, Description 
                     FROM parameter_type as pt, parameter_type_category as ptc, parameter_type_category_rel as ptcr 
                     WHERE pt.ParameterTypeID=ptcr.ParameterTypeID AND ptcr.ParameterTypeCategoryID=ptc.ParameterTypeCategoryID 
                     AND ptc.Name='Candidate Parameters' ORDER BY pt.ParameterTypeID, pt.name ASC", $field_results);
        //If there are no defined fields print a message to that effect
        if (empty($field_results)) {
            $this->addScoreColumn("static", "No candidate parameters have been defined for this study");
            return;
        }

        //Loop through the fields and add them appropriately
        foreach ($field_results AS $fresult) {
            $this->addScoreColumn("PTID_" . $fresult['ParameterTypeID'], $fresult['Description']);
        }

        $this->addScoreColumn('ProbandDoB', 'DoB Proband:');
        $this->addScoreColumn('ProbandGender', 'Proband gender:');
        $this->addScoreColumn('Age_Difference', 'Age Difference between candidate<BR> and proband (in months):');

        $this->addScoreColumn('SiblingcID', 'Family Member ID:');
        $this->addScoreColumn('relation_type', 'Relationship:');
        //participant status

        //entry staff info
        $this->addScoreColumn('entry_staff', 'Data Entry Staff');
        $this->addScoreColumn('data_entry_date', 'Date of last Data entry');

        $pscid = $DB->pselectone(
            'SELECT PSCID FROM candidate where CandID = :candid',
            array('candid' => $this->identifier)
        );

        $this->addScoreColumn('pscid', 'PSCID');
        $this->tpl_data['pscid'] = $pscid;

        $options = self::getParticipantStatusOptions();
        $options = array('') + $options;
        $this->tpl_data['pstatus_options'] = $options;
        $this->tpl_data['pstat'] = $_REQUEST['participant_status'];
        $this->addTextAreaGroup('reason_specify', "Comments", array(null => '', 'not_answered' => 'Not Answered'));

        //Consent Information
        $result = $DB->pselect("SELECT po.Description,ps.Description as Details, entry_staff, data_entry_date,reason_specify
                FROM participant_status_history p join participant_status_options po on (po.ID = p.participant_status)
                left join participant_status_options ps on (ps.ID = p.participant_subOptions)
                WHERE CandID=:cid", array('cid' => $this->identifier));
        for ($i = 0; $i < sizeof($result); $i++) {
            if ($result[$i]['Description'] == 'Active' && empty($result[$i]['entry_staff'])) {
                $result[$i]['entry_staff'] = 'Enrollment';
            }

        }
        $this->tpl_data['history_list'] = $result;
        $config =& NDB_Config::singleton();
        $consent = $config->getSetting('ConsentModule');
        if ($consent['useConsent'] === 'true') {
            foreach (Utility::toArray($consent['Consent']) as $question) {
                $consentQuestion = array($question['name'] => $question['label'],
                    $question['name'] . '_date' => "Date of <BR> $question[label]",
                    $question['name'] . '_withdrawal' => "Date of withdrawal <BR> of $question[label]",
                    'entry_staff' => 'Data Entry Staff',
                    'data_entry_date' => 'Date Updated',
                );
                $fields = $question['name'] . ', ' . $question['name'] . '_date, ' . $question['name'] . '_withdrawal, ';
                $study_consent = $DB->pselect("SELECT $fields entry_staff,data_entry_date
                                               FROM consent_info_history WHERE CandID=:cid",
                    array('cid' => $this->identifier));
                $study_consent_hist = array();
                for ($i = 0; $i < sizeof($study_consent); $i++) {
                    foreach ($consentQuestion as $key => $column_title) {
                        if ($key == $question['name'] && empty($study_consent[$i][$question['name']])) {
                            break;
                        }

                        if (!empty($study_consent[$i][$question['name']])) {
                            $study_consent_hist[$i][$key] = $study_consent[$i][$key];
                        }
                    }
                }

                $this->tpl_data['consent_list'][$question['name']] = array('label' => $consentQuestion,
                    'history' => $study_consent_hist);
            }
        }
        $this->form->addFormRule(array(&$this, '_validate'));

    }


    function update_proband_info()
    {

        $DB =& Database::singleton();
        $pscid = $DB->pselectone(
            'SELECT PSCID FROM candidate where CandID = :candid',
            array('candid' => $this->identifier)
        );
//        $this->addScoreColumn('pscid', 'PSCID');
        $this->tpl_data['candID'] = $this->identifier;

        $this->tpl_data['pscid'] = $pscid;

        $config =& NDB_Config::singleton();
        $probandDateOptions = array(
            'language' => 'en',
            'format' => 'YMd',
            'minYear' => $config->getSetting('startYear') - 20, //allows for proband siblings up to 20 years older than candidate
            'maxYear' => $config->getSetting('endYear'),
            'addEmptyOption' => true,
            'emptyOptionValue' => null
        );

        $this->addBasicDate('ProbandDoB', 'DoB Proband:', $probandDateOptions);
        $this->addBasicDate('ProbandDoB2', 'Confirm DoB Proband:', $probandDateOptions);
        $this->addSelect('ProbandGender', 'Proband gender:', array('' => '', 'Male' => 'Male', 'Female' => 'Female'));

        $this->form->addFormRule(array(&$this, '_validate'));
    }

    function update_consent_info()
    {
        $DB =& Database::singleton();
        $pscid = $DB->pselectone(
            'SELECT PSCID FROM candidate where CandID = :candid',
            array('candid' => $this->identifier)
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
                'format' => 'YMd',
                'minYear' => $config->getSetting('startYear'),
                'maxYear' => $config->getSetting('endYear'),
                'addEmptyOption' => true,
                'emptyOptionValue' => null
            );

            $consentQuestions = array();
            foreach (Utility::toArray($consent['Consent']) as $question) {
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
        $this->form->addFormRule(array(&$this, '_validate'));

    }

    function _validate_add_family($values)
    {
        if (!is_array($values) || count($values) == 0) {
            return true;
        }
        $cand = $values['FamilyMemberID'];
        $DB =& Database::singleton();
        $errors = array();
        $results = $DB->pselect("SELECT CandID from candidate where Active='Y'", array());
        $activeCandidates = array();
        foreach ($results as $row) {
            $activeCandidates[] = $row['CandID'];
        }
        if (!in_array($cand, $activeCandidates)) {
            $errors['FamilyMemberID'] = 'Candidate should be part of study. Please enter correct CandID';
        }
        $familyID = $DB->pselectOne("SELECT FamilyID from family WHERE CandID=:cid", array('cid' => $this->identifier));
        $relatives = $DB->pselect("SELECT CandID from family WHERE FamilyID=:fid", array('fid' => $familyID));
        $active_family = array();
        foreach ($relatives as $relative) {
            $active_family[] = $relative['CandID'];
        }
        if (in_array($cand, $active_family)) {
            $errors['FamilyMemberID'] = 'CandID already entered as sibling';
        }
        $CandID = $this->identifier;
        if ($CandID == $cand) {
            $errors['FamilyMemberID'] = 'Cannot enter candidate as own sibling';
        }
        if (empty($values['relation_type'])) {
            $errors['relation_type'] = 'Please specify relationship type';
        }
        if (empty($values['FamilyMemberID'])) {
            $errors['relation_type'] = 'Please specify DCCID of family member';
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
        $errors = array();
        $options = self::getParticipantStatusOptionsVerbose();

        $DB =& Database::singleton();
        if ($fields['ProbandDoB']['M'] != $fields['ProbandDoB2']['M'] ||
            $fields['ProbandDoB']['d'] != $fields['ProbandDoB2']['d'] ||
            $fields['ProbandDoB']['Y'] != $fields['ProbandDoB2']['Y']
        ) {
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
                    $errors[$fieldname . '_date'] = 'Cannot be later than today';

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
                if ($fields[$fieldname . '_withdrawal']['M'] != $fields[$fieldname . '_withdrawal2']['M'] ||
                    $fields[$fieldname . '_withdrawal']['d'] != $fields[$fieldname . '_withdrawal2']['d'] ||
                    $fields[$fieldname . '_withdrawal']['Y'] != $fields[$fieldname . '_withdrawal2']['Y']
                ) {
                    $errors[$fieldname . '_withdrawal'] = 'Date of withdrawal fields must match.';
                }
                if ($fields[$fieldname . '_date']['M'] != $fields[$fieldname . '_date2']['M'] ||
                    $fields[$fieldname . '_date']['d'] != $fields[$fieldname . '_date2']['d'] ||
                    $fields[$fieldname . '_date']['Y'] != $fields[$fieldname . '_date2']['Y']
                ) {
                    $errors[$fieldname . '_date'] = 'Date of consent fields must match.';
                }


            }
        }
        if ($fields['flagged_caveatemptor'] == 'true' && empty($fields['flagged_reason'])) {
            $errors['flagged_reason'] = 'Please provide additional information for 
                                         flagging candidate as Caveat Emptor';
        }
        $fields['flagged_other'] = trim($fields['flagged_other']);
        if ($fields['flagged_reason'] == 3 && empty($fields['flagged_other'])) {
            $errors['flagged_other_group'] = 'If Other, please specify details for cavear emptor';
        }

        if ($options[$fields['participant_status']]['Required'] == true) {
            $fields['participant_suboptions'] = trim($fields['participant_suboptions']);
            if (empty($fields['participant_suboptions'])) {
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
    static function getParticipantStatusOptions()
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
    static function getParticipantStatusOptionsVerbose()
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

    /**
     * Gets the participant_status options suboptions from participant_status_options
     * getParticipantStatusSubOptions()
     *
     * @return array Options array suitable for use in QuickForm select
     *               element
     */
    static function getParticipantStatusSubOptions($parentID)
    {
        $DB =& Database::singleton();
        $options = $DB->pselect(
            "SELECT ID,Description FROM participant_status_options WHERE parentID=:pid",
            array('pid' => $parentID)
        );
        $option_array = array();
        foreach ($options as $option) {
            $option_array[$option['ID']] = $option['Description'];
        }
        return $option_array;
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