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

        $pscid = $DB->pselectone(
            'SELECT PSCID FROM candidate where CandID = :candid',
            array('candid' => $this->identifier)
        );

        $this->tpl_data['pscid'] = $pscid;

/*
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

        //participant status

        //entry staff info
        $this->addScoreColumn('entry_staff', 'Data Entry Staff');
        $this->addScoreColumn('data_entry_date', 'Date of last Data entry');

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

*/
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