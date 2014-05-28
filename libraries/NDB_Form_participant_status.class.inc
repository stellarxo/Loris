<?php
/**
 * This form contains the code for the participant status module of Loris.
 * The module allows you to save the status of a candidate (ie. 
 * active/withdrawn/etc) on a candidate level. The valid options for statuses
 * are in the table participant_status_options, as well as whether or not
 * that status requires a reason to be specified.
 *
 * PHP Version 5
 *
 *  @category Behavioural 
 *  @package  Main
 *  @author   Zia Mohadesz <zia.mohades@gmail.com>
 *  @license  Loris License
 *  @link     https://github.com/aces/Loris-Trunk
 */
require_once "NDB_Form.class.inc";

/**
 * The form for the participant status module.
 *
 * @category Behavioural 
 * @package  Main
 * @author   Zia Mohadesz <zia.mohades@gmail.com>
 * @license  Loris License
 * @link     https://github.com/aces/Loris-Trunk
 */
class NDB_Form_participant_status extends NDB_Form
{
    var $indent = "&nbsp;&nbsp;&nbsp;&nbsp;";

    /**
     * Determine if the user should have access to this page.
     * Currently tied to data_entry permission.
     *
     * @return boolean True if the user should have access
     */
    function _hasAccess()
    {
        // create user object
        $user =& User::singleton();
        if (Utility::isErrorX($user)) {
            return PEAR::raiseError("User Error: ".$user->getMessage());
        }

        // check that the $candID is passed b/c the profile needs to be opened
        if ($this->identifier != $_REQUEST['candID']) {
            return PEAR::raiseError(
                "NDB_Form_participant_status::_access: " 
                . "Candidate Profile Error ($this->identifier)"
            );
        }
        // check user permissions
        return ($user->hasPermission('data_entry'));
    }

    /**
     * Gets default options for smarty to fill in.
     * This comes from the participant status table
     *
     * @return array Currently saved entries in database
     */
    function _getDefaults()
    {

        $DB =& Database::singleton();
        $defaults = $DB->pselectRow(
            "SELECT * FROM participant_status WHERE CandID = :cid", 
            array('cid'=>$this->identifier)
        );
        foreach($defaults as $key => &$val) {
            if($val === '0000-00-00') {
                $val = '';
            }
        }
        return $defaults;
    }

    /**
     * Process the submitted values, called after validation.
     *
     * @param array $values The values submitted by the user 
     *                      to the form.
     *
     * @return boolean True on success
     */
    function _process($values)
    {
        if (!is_array($values) || count($values) === 0) {
            return true;
        }
        $DB =& Database::singleton();

        $values['CandID'] = $this->identifier;

        if (!(is_null($_SESSION['State']))) {
            $currentUser =& User::singleton($_SESSION['State']->getUsername());
            $id = $currentUser->getData("UserID");
            $values['entry_staff'] = $id;
        }

        foreach($values as $key => &$val) {
            if(strrpos($key, "consent_date") !== FALSE || strrpos($key, "consent_withdrawal") !== FALSE) {
                $val = $this->_getDatabaseDate($val);
                if($val === '--') {
                    $val = '';
                }
            }
        }


        // save the values
        //if it exists update it
        $ParticipantCount = $DB->pselectOne(
            "SELECT COUNT(*) FROM participant_status WHERE CandID = :cid", 
            array("cid"=>$values['CandID'])
        );
        if ($ParticipantCount > 0) {
            $success = $DB->update(
                "participant_status", 
                $values,
                array("CandID"=>$values['CandID'])
            );
        } else {
            //insert it
            $success = $DB->insert("participant_status", $values);
        }

        if (Utility::isErrorX($success)) {
            return PEAR::raiseError(
                "NDB_Form_participant_status::_process: ".$success->getMessage()
            );
        }

        $this->tpl_data['success'] = true;
        $this->form->freeze();
    }

    /**
     * Constructor called by loris to setup the tpl_data
     * array
     *
     * @return null
     */
    function participant_status()
    {

        $this->tpl_data['candID'] = $this->identifier;

        $config =& NDB_Config::singleton();
        $DB =& Database::singleton();

        //entry staff info
        $this->addScoreColumn('entry_staff', 'Data Entry Staff');
        $this->addScoreColumn('data_entry_date', 'Date of last Data entry');

        $pscid = $DB->pselectone(
            'SELECT PSCID FROM candidate where CandID = :candid',
            array('candid'=>$this->identifier)
        );
        $this->addScoreColumn('pscid', 'PSCID');
        $this->tpl_data['pscid'] = $pscid;

        // Selections array (standard template for questions selections)
        $notAns4 = array(
            "dnk"            => "Don't know", 
            "not_applicable" => "Not applicable",
            "refusal"        => "Refusal",
            "not_answered"   => "Not Answered"
        );


        $options = $this->getParticipantStatusOptions();

        $this->addSelect(
            'participant_status', 
            "Participant Status", 
            array('') + $options + $notAns4
        );

        $this->addTextAreaGroup(
            'reason_specify', 
            $this->indent . 'Please specify reason for status',
            array(null => null) + $notAns4
        );


        // withdrawal
        $options = array(
            null                     => '', 
            "1_voluntary_withdrawal" => "1. Voluntary withdrawal", 
            "2_lost_follow_up"       => "2. Lost to follow up", 
            "3_other"               => "3. Other"
        );
        $this->addSelect(
            'withdrawal_reasons',
            "If withdrawal, provide the reason",
            $options
        );
        $this->addTextAreaGroup(
            'withdrawal_reasons_other_specify', 
            $this->indent . 'Please specify other reason for drop out ',
            array(null => null) + $notAns4
        );

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

        $reasonID = $fields['participant_status'];


        if ($options[$reasonID]['Required'] == true) {

            if (($options[$reasonID]['Description'])=='withdrawal') {
                if (empty($fields['withdrawal_reasons'])) {
                    $errors['withdrawal_reasons'] = "required";
                } else if ($fields['withdrawal_reasons'] == '3_other') {
                    if (empty($fields['withdrawal_reasons_other_specify'])
                        && empty($fields['withdrawal_reasons_other_specify_status'])
                    ) {
                        $errors['withdrawal_reasons_other_specify_group']
                            = "required";
                    }
                }
            } else {
                if (empty($fields['reason_specify'])
                    && empty($fields['reason_specify_status'])
                ) {
                    $errors['reason_specify_group'] = "Must specify when status is "
                        . $options[$reasonID]['Description'];
                }
            }
        }

        // Not withdrawal

        if ((!empty($fields['withdrawal_reasons'])) 
            && (($options[$reasonID]['Description'])!='withdrawal')
        ) {
            $errors['withdrawal_reasons'] = 'Only specify if withdrawal';
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
            "SELECT ID,Description FROM participant_status_options",
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

}
?>