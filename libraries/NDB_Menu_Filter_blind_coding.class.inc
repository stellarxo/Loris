<?php
require_once 'NDB_Menu_Filter.class.inc';

/**
 * The menu for the blind coding scoring checking
 * @package mri
 * @subpackage NIHPD
 */

class NDB_Menu_Filter_blind_coding extends NDB_Menu_Filter
{

    var $centerIDMap;
    
    var $site_id = array('SEA' => 2, 'PHI' => 3, 'STL' => 4, 'UNC' => 5, 'UofA' => 6);
    
    var $reliability_table;

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
        
        $this->_populate_reliability_table();

        // the base query
        $query = " FROM candidate c JOIN session s ON (s.CandID=c.CandID) JOIN flag f ON (f.SessionID=s.ID) JOIN blind_coding b ON (b.CommentID=f.CommentID)";

        // only view their own profiles, unless they have permission to see all
        if (!($user->hasPermission('blind_edit_all') || $user->hasPermission('access_all_profiles'))) {
            $query .= " AND c.centerID = '" . $user->getData('CenterID') . "' "; 
        }

        // set the class variables
        $this->columns = array('b.CommentID', 'c.PSCID', 'b.CodingCenterID AS Site', 's.SubprojectID as Cohort', 's.CandID AS DCCID', 'c.Gender', 's.Visit_label', 'b.Instrument', 'b.Blind_score', 's.Current_stage', 'b.Invalid';

        $this->query = $query;
        $this->group_by = '';
        $this->order_by = 'b.Instrument, s.CandID, s.Visit_label';
        $this->headers = array('PSCID', 'reliability_center_id','Cohort', 'DCCID', 'Gender', 'Visit_label', 'Instrument', 'Blind_score', 'Reliable');
        $this->validFilters = array('b.CommentID', 'b.CodingCenterID', 's.SubprojectID', 'c.CenterID', 's.CandID', 'c.PSCID', 'c.Gender', 's.Visit_label', 'b.Instrument', 'b.Blind_score', 's.Current_stage', 'b.invalid');

        $this->formToFilter = array(
                                    'CommentID' => 'b.CommentID',
                                    'Cohort' => 's.SubprojectID',
                                    'CenterID' => 'c.CenterID',
                                    'CodingCenterID'=> 'b.CodingCenterID',
                                    'DCCID' => 'c.CandID',
                                    'PSCID' => 'c.PSCID',
                                    'Gender' => 'c.Gender',
                                    'Visit_label' => 's.Visit_label',
				                    'Instrument' => 'b.Instrument',
                                    'Blind_score'=>'b.Blind_score',
                                    'Current_stage'=>'s.Current_stage',
                                    'Invalid' => 'b.invalid'
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
        if ($user->hasPermission('access_all_profiles') || $user->hasPermission('blind_edit_all')) {
            // get the list of study sites - to be replaced by the Site object
            $list_of_sites = Utility::getSiteList(false);
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
        $list_of_visit_labels_only = array('V06'=>'V06','V12'=>'V12','V24'=>'V24','V36'=>'V36');
        $subproject_options = Utility::getSubprojectList();
        $subproject_options = array(null=>'Any') + $subproject_options;
        $gender_options = array(null=>'Any', 'Male'=>'Male', 'Female'=>'Female');
        $list_of_instruments = array(null=>'Any', 'csbs'=>'CSBS', 'adi_r'=>'ADI-R', 'ados'=>'ADOS', 'aosi' => 'AOSI');
        $list_of_instruments_only = array('csbs'=>'CSBS', 'adi_r_proband'=>'ADI-R (Proband)', 'adi_r_subject' => 'ADI-R (Subject)', 'ados_module1'=>'ADOS (Module 1)', 'ados_module2' => 'ADOS (Module 2)', 'aosi' => 'AOSI');
        $lock_options = array(null=>'','Locked'=>'Locked','Unlocked'=>'Unlocked');

        // Form Elements
        $this->form->addElement('select', 'CommentID', 'CommentID:', $subproject_options);
        $this->form->addElement('select', 'Objective', 'Objective:', $subproject_options);
        $this->form->addElement('select', 'CenterID', 'Site:', $list_of_sites);
        $this->form->addElement('select', 'CodingCenterID', 'Site of Reliability:', $list_of_sites);
        $this->form->addElement('text', 'DCCID', 'DCCID::', array("size"=>9, "maxlength"=>6));
        $this->form->addElement('text', 'PSCID', 'PSCID:', array("size"=>9, "maxlength"=>7));
        $this->form->addElement('select', 'Gender', 'Gender:', $gender_options);
        $this->form->addElement('select', 'Visit_label', 'Visit Label:', $list_of_visit_labels);
        $this->form->addElement('select', 'Instrument', 'Instrument:', $list_of_instruments);
        $this->form->addElement('select', 'Invalid', 'Invalid Candidate:', array('' => '', 'yes' => 'Yes', 'no' => 'No'));
	 // $this->form->addElement('select', 'Lock_record', 'Lock_record:', $lock_options);
       
       // For swapping candidates
       /*
        if ($user->hasPermission('reliability_swap_candidates')) {
            $this->tpl_data['reliability_swap_candidates'] = true;
            $this->form->addElement('select', 'Cand1Visit_label', 'Visit Label:', $list_of_visit_labels_only);
            $this->form->addElement('text', 'Cand1PSCID', 'PSCID:');
            $this->form->addElement('select', 'Cand2Visit_label', 'Visit Label:', $list_of_visit_labels_only);
            $this->form->addElement('text', 'Cand2PSCID', 'PSCID:');
            $this->form->addElement('select', 'SwapInstrument', 'Instrument:', $list_of_instruments_only);
        } else {
            $this->tpl_data['reliability_swap_candidates'] = false;
        }

        if ($user->hasPermission('EARLI_Reliability')) {
            $this->tpl_data['EARLI_Reliability'] = true;
            $this->form->addElement('text', 'AddPSCID', 'PSCID:');
            $this->form->addElement('select', 'AddVisit_label', 'Visit Label:', array_merge(array('' => 'Any'), $list_of_visit_labels_only));
            $this->form->addElement('select', 'AddReliabilityCenter', 'Site of Reliability:', $list_of_sites);
            $this->form->addElement('select', 'AddInstrument', 'Instrument:', array_merge(array('' => 'Any'), $list_of_instruments_only));
        } else {
            $this->tpl_data['EARLI_Reliability'] = false;
        }

        // Doing this here is a hack. Since this is a menu filter and not a Form, there's no 
        // _process/_save functions automagically called. There should probably be something like
        // a Menu_Filter_Form base class for instances like this or the conflict resolver, but as
        // things stand you either need to work with the $_POST array/DB directly in a Menu_Filter,
        // or rewrite/imitate the Menu_Filter in an NDB_Form. -- Dave
        if($_POST['swap'] == 'Swap Candidates' || $_POST['swap'] == 'swap') {
            $message = $this->_swap_candidates();
            if(isset($message['error'])) {
                $this->form->addElement('static', 'error', $message['error']);
            }
            if(isset($message['message'])) {
                $this->form->addElement('static', 'message', $message['message']);
            }
        } else if($_POST['swap'] == "Add Candidate" || $_POST['swap'] == 'addnew') {
            $message = $this->_addCandidate();
            if(isset($message['error'])) {
                $this->form->addElement('static', 'error', $message['error']);
            }
            if(isset($message['message'])) {
                $this->form->addElement('static', 'message', $message['message']);
            }
        }
        */
        return true;
    }

    // This is used both by setDataTableRows, and reliability statistics
    function getThreshholds() {
        //return array("adi_r_proband" => 90, "adi_r_subject" => 90, "adi_r" => 90, 'aosi' => 78.9, 'csbs' => 80, 'ados_module1' => 80, 'ados_module2' => 80);
        return array("adi_r_proband" => 89.5, "adi_r_subject" => 89.5, "adi_r" => 89.5, 'aosi' => 78.0, 'csbs' => 79.5, 'ados_module1' => 79.5, 'ados_module2' => 79.5);
    }
    function _setDataTableRows($count)
    {

        $threshold = $this->getThreshholds();
        // print out
        $x = 0;
        foreach ($this->list as $item) {
            //count column
            $this->tpl_data['items'][$x][0]['value'] = $x + $count;

            //print out data rows
            $i = 1;
            // $identifier = $item['Tracking_log_ID'];
            $comment_id = $item['CommentID'];
            $site_id = $item['Site'];
            $current_stage = $item['Current_stage'];
            $invalid = $item['invalid'];
            $manual= $item['Manual_Swap'];
            if($item['Manual_Swap'] == 'yes' && $item['invalid'] == 'yes') {
                continue;
            }
            foreach ($item as $key => $val) {

                // Confused about this line
                if ($key =='Tracking_log_ID') continue;
                if ($key == 'CommentID') continue;
                if ($key == 'Current_stage') continue;
                if ($key == 'invalid') continue;
                if ($key == 'Manual_Swap') continue;
                // {
                //                    $this->tpl_data['items'][$x][$i]['CommentID'] = $item['CommentID'];
                //               $this->tpl_data['items'][$x][$i]['Instrument'] = $item['Instrument'];
                //                   }
                $this->tpl_data['items'][$x][$i]['name'] = $key;
                $this->tpl_data['items'][$x][$i]['value'] = $val;
                if ($key == 'PSCID'){
                   $this->tpl_data['items'][$x][$i]['CommentID'] = $comment_id;
                   $this->tpl_data['items'][$x][$i]['SiteID'] = $item['Site'];
                   $this->tpl_data['items'][$x][$i]['Instrument'] = $item['Instrument'];
                   $this->tpl_data['items'][$x][$i]['Current_stage'] = $current_stage;
                   $this->tpl_data['items'][$x][$i]['invalid'] = $invalid;
                   $this->tpl_data['items'][$x][$i]['manual'] = $manual;
                }
                if ($key == 'Site')
                {
                   $this->tpl_data['items'][$x][$i]['value'] = $this->centerIDMap[$item['Site']];
                }
                if($key == 'Blind_score'){
                  $this->tpl_data['items'][$x][$i+1]['name'] = 'score';
                  if(is_null($val))
                    $reliable = null;
                  else if($val >= $threshold[$item['Instrument']])
                    $reliable = 'Yes';
                  else
                    $reliable = 'No';
                  $this->tpl_data['items'][$x][$i+1]['value'] = $reliable;
                }
                
               $i++;
            }
            $x++;
        }

        return true;
    }
    
    function _swap_candidates() {
        $user =& User::singleton();
        if(PEAR::isError($user)) {
            return PEAR::raiseError("User Error: ".$user->getMessage());
        }
        if (!($user->hasPermission('reliability_swap_candidates'))) {
            return array("error" => "You do not have permission to swap candidates");
        }
        $DB =& Database::singleton();
        $PSCID = $_POST['Cand1PSCID'];
        $PSCID_V = $_POST['Cand1Visit_label'];
        $PSCID_Replace= $_POST['Cand2PSCID'];
        $PSCID_Replace_V = $_POST['Cand2Visit_label'];
        $Instrument = $_POST['SwapInstrument'];

        $query="SELECT reliability.CommentID as OldID, reliability.reliability_center_id as CenterID, reliability.Reliability_score as Score, candidate.CenterID as OldCenterID, reliability.EARLI_Candidate AS EARLI_Candidate  FROM candidate, session, flag, reliability WHERE reliability.CommentID=flag.CommentID AND candidate.CandID=session.CandID AND session.ID=flag.SessionID AND candidate.PSCID='$PSCID' AND reliability.Instrument='$Instrument' and session.Visit_label='$PSCID_V' and flag.Data_entry IS NOT NULL and flag.Data_entry <> 'None' ";

        $DB->selectRow($query, $CommentID);
        if(!$CommentID) {
            return array("error" => "$PSCID/$PSCID_V is not in reliability coding for $Instrument. Cannot swap candidates.");
        }

        $query="SELECT f.CommentID as NewID, c.CenterID as NewCenterID FROM session s join flag f ON (f.SessionID=s.ID) JOIN candidate c ON (c.CandID=s.CandID)  WHERE f.Test_name='$Instrument' and c.PSCID='$PSCID_Replace' AND s.Visit_label='$PSCID_Replace_V' AND f.Data_entry IS NOT NULL and f.Data_entry <> 'None'";
        $DB->selectRow($query, $newCommentID);
        if(!$newCommentID) {
            return array('error' => "$PSCID_Replace/$PSCID_Replace_V did not complete $Instrument or data not entered. Cannot swap candidates.");
        }
        if($newCommentID['NewCenterID'] !== $CommentID['OldCenterID']) {
            return array('error' => "Candidates are not from the same site. Cannot swap candidates across sites.");
        }
        elseif($user->getCenterID() != $newCommentID['NewCenterID']) {
            return array('error' => "$PSCID_Replace/$PSCID_Replace_V is from a different site than you. Can only swap candidates from the same site.");
        }
        elseif($user->getCenterID() != $CommentID['OldCenterID']) {
            return array('error' => "$PSCID/$PSCID_V is from a different site than you. Can only swap candidates from the same site.");
        }
        $NewID = $newCommentID['NewID'];
        $DB->selectRow("SELECT CommentID FROM reliability WHERE CommentID='$NewID'", $replacementCheck);
        if(!empty($replacementCheck)) {
            return array("error" => "$PSCID_Replace/$PSCID_Replace_V already in reliability. Cannot swap $PSCID/$PSCID_V for it.");
        }

        $CenterID = $CommentID['CenterID'];
        $EARLI_Cand= $CommentID['EARLI_Candidate'];
        if(!empty($CommentID['Score'])) {
            return array( "error" => "Reliability score already exists for $PSCID/$PSCID_V. Can not swap candidate.");
        }
        $DB->run("UPDATE reliability SET invalid='yes', manual_swap='yes' WHERE CommentID='$CommentID[OldID]' AND Instrument='$Instrument'");
        $DB->run("INSERT INTO reliability (CommentID, reliability_center_id, Instrument, Manual_Swap, EARLI_Candidate) VALUES ('$newCommentID[NewID]', $CenterID, '$Instrument', 'yes', '$EARLI_Cand')");

        return array("message" => "Swapped candidate $PSCID for $PSCID_Replace");
    }

    function _addCandidate() {
        $user =& User::singleton();
        $DB =& Database::singleton();
        if(PEAR::isError($user)) {
            return PEAR::raiseError("User Error: ".$user->getMessage());
        }
        if (!($user->hasPermission('EARLI_Reliability'))) {
            return array("error" => "You do not have permission to add EARLI candidates");
        }
        $Instrument = $_POST['AddInstrument'];
        $CenterID = $_POST['AddReliabilityCenter'];
        $Visit_label= $_POST['AddVisit_label'];
        if(!$Visit_label) {
            return array("error" => "You must specify a visit label");
        }

        if(!$Instrument) {
            return array("error" => "You must specify an instrument");
        } 
        if(!$CenterID) {
            return array("error" => "You must specify a center for reliability testing");
        }

        $PSCID = $_POST['AddPSCID'];
        $CommentID = $DB->selectOne("SELECT CommentID FROM flag f JOIN session s ON (s.ID=f.SessionID) JOIN candidate c USING (CandID) WHERE f.Test_name='$Instrument' AND c.PSCID='$PSCID' AND s.Visit_label='$Visit_label'");
        if(!$CommentID) {
            return array("error" => "$PSCID/$Visit_label does not have data entered for $Instrument");

        }
        $DB->run("INSERT INTO reliability (CommentID, reliability_center_id, Instrument, Manual_Swap, EARLI_Candidate) VALUES ('$CommentID', $CenterID, '$Instrument', 'no', 'yes')");
        return array("message" => "Inserted new reliability candidate $PSCID/$Visit_label for EARLI collaboration");
    }
}
?>
