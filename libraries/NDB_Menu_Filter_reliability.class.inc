<?php
require_once 'NDB_Menu_Filter.class.inc';

/**
 * The menu for the reliability checking
 * @package mri
 * @subpackage NIHPD
 */
class NDB_Menu_Filter_reliability extends NDB_Menu_Filter
{

    var $centerIDMap;

    function _setupVariables()
    {
        $user =& User::singleton();
        if(PEAR::isError($user)) {
            return PEAR::raiseError("User Error: ".$user->getMessage());
        }

        // create the centerID map
        $db =& Database::singleton();
        $pscRows = array();
        $db->select("SELECT CenterID, Name FROM psc", $pscRows);
        foreach($pscRows AS $row) {
            $this->centerIDMap[$row['CenterID']] = $row['Name'];
        }

        // the base query
        $query = " FROM candidate, session, flag, reliability WHERE reliability.CommentID=flag.CommentID AND candidate.CandID=session.CandID AND session.ID=flag.SessionID";

        // only view their own profiles, unless they have permission to see all
        if (!($user->hasPermission('reliability_edit_all') || $user->hasPermission('access_all_profiles'))) {
            $query .= " AND candidate.centerID = '" . $user->getData('CenterID') . "' "; 
        }

        // set the class variables
        $this->columns = array('reliability.CommentID', 'session.SubprojectID as Cohort', 'IF(session.ID is null, candidate.CenterID, session.CenterID) AS Site', 'session.CandID AS DCCID', 'candidate.PSCID', 'candidate.Gender', 'session.Visit_label', 'reliability.Instrument', 'reliability.Reliability_score');

        $this->query = $query;
        $this->group_by = '';
        $this->order_by = 'session.CandID, session.Visit_label';
        $this->headers = array('CommentID','Cohort', 'Site', 'DCCID', 'PSCID', 'Gender', 'Visit_label', 'Instrument', 'reliability_score');
        $this->validFilters = array('reliability.CommentID','session.SubprojectID', 'candidate.CenterID', 'session.CandID', 'candidate.PSCID', 'candidate.Gender', 'session.Visit_label', 'reliability.Instrument', 'reliability.Reliability_score');

        $this->formToFilter = array(
                                    'CommentID' => 'reliability.CommentID',
                                    'Cohort' => 'session.SubprojectID',
                                    'CenterID' => 'candidate.CenterID',
                                    'DCCID' => 'candidate.CandID',
                                    'PSCID' => 'candidate.PSCID',
                                    'Gender' => 'candidate.Gender',
                                    'Visit_label' => 'session.Visit_label',
				    'Instrument' => 'reliability.Instrument',
                                    'reliability_score'=>'reliability.Reliability_score',
                                    // 'Lock_record' => 'session.Lock_record'
                                    );
        return true;
    }


    function _setFilterForm()
    {
    	// create user object
        $user =& User::singleton();
        if(PEAR::isError($user)) {
            return PEAR::raiseError("User Error: ".$user->getMessage());
        }

           // allow to view all sites data through filter
        if ($user->hasPermission('access_all_profiles') || $user->hasPermission('reliability_edit_all')) {
            // get the list of study sites - to be replaced by the Site object
            $list_of_sites = Utility::getSiteList();
            if(PEAR::isError($list_of_sites)) {
                return PEAR::raiseError("DB Error: ".$list_of_sites->getMessage());
            }
            if(is_array($list_of_sites)) $list_of_sites = array('' => 'Any') + $list_of_sites;
        }
        else {
            // allow only to view own site data
            $site =& Site::singleton($user->getData('CenterID'));
            if (PEAR::isError($site)) {
                return PEAR::raiseError("DB Error: ".$site->getMessage());
            }
            if ($site->isStudySite()) {
                $list_of_sites = array($user->getData('CenterID') => $user->getData('Site'));
            }
        }
        
        /// hack for Visit Labels... maybe get all the real visit labels from DB?
        $list_of_visit_labels = array(null=>'Any','V06'=>'V06','V12'=>'V12','V24'=>'V24','V36'=>'V36');
        $subproject_options = Utility::getSubprojectList();
        $subproject_options = array(null=>'Any') + $subproject_options;
        $gender_options = array(null=>'All', 'Male'=>'Male', 'Female'=>'Female');
        $list_of_instruments = array(null=>'Any', 'csbs'=>'CSBS', 'adi_r'=>'ADI-R', 'ados'=>'ADOS');
        $lock_options = array(null=>'','Locked'=>'Locked','Unlocked'=>'Unlocked');

        // Form Elements
        $this->form->addElement('select', 'CommentID', 'CommentID:', $subproject_options);
        $this->form->addElement('select', 'Objective', 'Objective:', $subproject_options);
        $this->form->addElement('select', 'CenterID', 'Site:', $list_of_sites);
        $this->form->addElement('text', 'DCCID', 'DCCID::', array("size"=>9, "maxlength"=>6));
        $this->form->addElement('text', 'PSCID', 'PSCID:', array("size"=>9, "maxlength"=>7));
        $this->form->addElement('select', 'Gender', 'Gender:', $gender_options);
        $this->form->addElement('select', 'Visit_label', 'Visit Label:', $list_of_visit_labels);
        $this->form->addElement('select', 'Instrument', 'Instrument:', $list_of_instruments);
	 // $this->form->addElement('select', 'Lock_record', 'Lock_record:', $lock_options);
       
        return true;
    }

    function _setDataTableRows($count)
    {

        // print out
        $x = 0;
        foreach ($this->list as $item) {
            //count column
            $this->tpl_data['items'][$x][0]['value'] = $x + $count;

            //print out data rows
            $i = 1;
            // $identifier = $item['Tracking_log_ID'];
            foreach ($item as $key => $val) {

                // Confused about this line
                if ($key =='Tracking_log_ID') continue;
                if ($key == 'CommentID') {
                    $this->tpl_data['items'][$x][$i]['CommentID'] = $item['CommentID'];
	            $this->tpl_data['items'][$x][$i]['Instrument'] = $item['Instrument'];
	                }
                $this->tpl_data['items'][$x][$i]['name'] = $key;
                $this->tpl_data['items'][$x][$i]['value'] = $val;
                if ($key == 'Site') {
                    $this->tpl_data['items'][$x][$i]['value'] = $this->centerIDMap[$item['Site']];
                }
                $i++;
            }
            $x++;
        }

        return true;
    }
}
?>