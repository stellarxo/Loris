<?php
require_once 'NDB_Menu_Filter.class.inc';

/**
 * The menu for the reliability checking
 * @package mri
 * @subpackage NIHPD
 */

function map_cIDs($array){
    $new_array;
    for($i = 0; $i < count($array); $i++){
      $element = $array[$i];
      $new_array[$element['CommentID']] = $element['reliability_center_id'];
    }
    return $new_array;
}

function find_cID($cID, $array){
  if(empty($array)){
    return false;
  }
  foreach($array as $key=>$value){
    if($key == $cID){
      return true;
    }
  }
  return false;
}

function array_remove($item, $array){
  $index = array_search($item, $array);
  if($index === false){
    return $array;
  }else{
    unset($array[$index]);
    return array_values($array); 
  }
}
 
class NDB_Menu_Filter_reliability extends NDB_Menu_Filter
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
        $query = " FROM candidate, session, flag, reliability WHERE reliability.CommentID=flag.CommentID AND candidate.CandID=session.CandID AND session.ID=flag.SessionID";

        // only view their own profiles, unless they have permission to see all
        if (!($user->hasPermission('reliability_edit_all') || $user->hasPermission('access_all_profiles'))) {
            $query .= " AND candidate.centerID = '" . $user->getData('CenterID') . "' "; 
        }

        // set the class variables
        $this->columns = array('reliability.CommentID', 'candidate.PSCID', 'reliability.reliability_center_id AS Site', 'session.SubprojectID as Cohort', 'session.CandID AS DCCID', 'candidate.Gender', 'session.Visit_label', 'reliability.Instrument', 'reliability.Reliability_score', 'session.Current_stage', 'reliability.invalid');

        $this->query = $query;
        $this->group_by = '';
        $this->order_by = 'reliability.Instrument, session.CandID, session.Visit_label';
        $this->headers = array('PSCID', 'reliability_center_id','Cohort', 'DCCID', 'Gender', 'Visit_label', 'Instrument', 'reliability_score', 'Reliable');
        $this->validFilters = array('reliability.CommentID', 'reliability.reliability_center_id', 'session.SubprojectID', 'candidate.CenterID', 'session.CandID', 'candidate.PSCID', 'candidate.Gender', 'session.Visit_label', 'reliability.Instrument', 'reliability.Reliability_score', 'session.Current_stage');

        $this->formToFilter = array(
                                    'CommentID' => 'reliability.CommentID',
                                    'Cohort' => 'session.SubprojectID',
                                    'CenterID' => 'candidate.CenterID',
                                    'reliability_center_id'=> 'reliability.reliability_center_id',
                                    'DCCID' => 'candidate.CandID',
                                    'PSCID' => 'candidate.PSCID',
                                    'Gender' => 'candidate.Gender',
                                    'Visit_label' => 'session.Visit_label',
				                            'Instrument' => 'reliability.Instrument',
                                    'reliability_score'=>'reliability.Reliability_score',
                                    'Current_stage'=>'session.Current_stage',
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

        $threshold = array("adi_r_proband" => 90, "adi_r_subject" => 90, "adi_r" => 90, 'aosi' => 78.9, 'csbs' => 80, 'ados_module1' => 80, 'ados_module2' => 80);
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
            foreach ($item as $key => $val) {

                // Confused about this line
                if ($key =='Tracking_log_ID') continue;
                if ($key == 'CommentID') continue;
                if ($key == 'Current_stage') continue;
                if ($key == 'invalid') continue;
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
                }
                if ($key == 'Site')
                {
                   $this->tpl_data['items'][$x][$i]['value'] = $this->centerIDMap[$item['Site']];
                }
                if($key == 'Reliability_score'){
                  $this->tpl_data['items'][$x][$i+1]['name'] = 'Reliability';
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
    
    function _populate_reliability_table()
    { 
       $db =& Database::singleton();
       $db->select("SELECT CommentID, reliability_center_id FROM reliability", $this->reliability_table);
       
       
       $this->reliability_table = map_cIDs($this->reliability_table);
       
       // WITHIN SITE
       $site_list = array('SEA', 'PHI', 'STL', 'UNC');
        
        foreach($site_list as $site){
          $this->within_site_flagging("adi_r_subject", 0.1, $site, $db);
          $this->within_site_flagging("adi_r_proband", 0.15, $site, $db);
          $this->within_site_flagging("aosi", 0.1, $site, $db);
          $this->within_site_flagging("ados_module1", 0.1, $site, $db);
          $this->within_site_flagging("ados_module2", 0.1, $site, $db);
          $this->within_site_flagging("csbs", 0.1, $site, $db);
        }    
        
        foreach($site_list as $site){
          $this->cross_site_flagging("adi_r_subject", $site, array_remove($site, $site_list), $db);
//          $this->cross_site_flagging("adi_r_proband", $site, array_remove($site, $site_list), $db);
          $this->cross_site_flagging("aosi", $site, array("UofA"), $db);
          $this->cross_site_flagging("ados_module1", $site, array_remove($site, $site_list), $db);
          $this->cross_site_flagging("ados_module2", $site, array_remove($site, $site_list), $db);
          $this->cross_site_flagging("csbs", $site, array_remove($site, $site_list), $db);
        }            
        
    }
    
    function within_site_flagging($instrument, $ratio, $current_site, $db){
        if($current_site == "PHI"){
          $phi_site_clause = " AND Date_taken >= 2009-11-11 ";
        }
      
        $db->select("SELECT i.CommentID FROM {$instrument} as i, flag as f, session as s WHERE i.CommentID=f.CommentID AND f.sessionID=s.ID AND s.Current_stage<>'Recycling Bin' AND f.Data_entry='Complete' AND i.CommentID LIKE '%{$current_site}%' AND s.visit_label<>'v18' AND i.CommentID NOT LIKE 'DDE%' {$phi_site_clause} ORDER BY i.CommentID", $instrument_records);
        
        
        #$current_count = $db->selectOne("SELECT count(*) FROM reliability WHERE CommentID LIKE '%{$current_site}%' AND Instrument='{$instrument}' AND reliability_center_id={$this->site_id[$current_site]}");
        $current_count = $db->selectOne("SELECT count(*) FROM (SELECT DISTINCT r.CommentID FROM reliability as r, flag as f, session as s  WHERE r.CommentID LIKE '%{$current_site}%' AND r.Instrument='{$instrument}' AND r.reliability_center_id={$this->site_id[$current_site]} AND r.invalid = 'no' AND r.CommentID=f.CommentID AND f.sessionID=s.ID AND s.Current_stage<>'Recycling Bin') as t");
        $total_count = count($instrument_records);
        $max = floor($ratio * $total_count);
        // 
        // echo("Site: {$current_site} <BR>");
        // echo($current_count . " --- " . $total_count . "<BR>");
        // echo("Max (ratio: {$ratio}/jump: {$jump_step}): {$max} <BR><BR>")
        
       for($i = 0; $i < count($instrument_records) && $current_count + 1 <= $max; $i += 2){
          $commentID = $instrument_records[$i]["CommentID"];
          if(!find_cID($commentID, $this->reliability_table)){
            $db->insert('reliability', array('CommentID' => $instrument_records[$i]["CommentID"],
                                              'reliability_center_id' => $this->site_id[$current_site],
                                              'Instrument' => $instrument
                                              ));
            $this->reliability_table[$instrument_records[$i]["CommentID"]] = $this->site_id[$current_site];
            $current_count++;
          }                  
       }
    }
    
    function cross_site_flagging($instrument, $current_site, $reliability_sites, $db){
        $ratio = 0.1;
        $reliability_site_index = 0; 
        
        if($instrument == "adi_r_subject"){
          $query_extra = " AND (s.visit_label='v24' OR s.visit_label='v36')";
        }
        
        if($current_site == "PHI"){
          $phi_site_clause = " AND Date_taken >= 2009-11-11";
        }
          
        $db->select("SELECT i.CommentID FROM {$instrument} as i, flag as f, session as s WHERE i.CommentID=f.CommentID AND f.sessionID=s.ID AND s.Current_stage<>'Recycling Bin' AND f.Data_entry='Complete' AND i.CommentID LIKE '%{$current_site}%' AND s.visit_label<>'v18'{$query_extra} AND i.CommentID NOT LIKE 'DDE%' {$phi_site_clause} ORDER BY i.CommentID", $instrument_records);
        
        //$current_count = $db->selectOne("SELECT count(*) FROM reliability WHERE CommentID LIKE '%{$current_site}%' AND Instrument='{$instrument}' AND reliability_center_id<>{$this->site_id[$current_site]}");
         $current_count = $db->selectOne("SELECT count(*) FROM (SELECT DISTINCT r.CommentID FROM reliability as r, flag as f, session as s  WHERE r.CommentID LIKE '%{$current_site}%' AND r.Instrument='{$instrument}' AND r.reliability_center_id<>{$this->site_id[$current_site]} AND r.invalid = 'no'  r.CommentID=f.CommentID AND f.sessionID=s.ID AND s.Current_stage<>'Recycling Bin') as t");
        $total_count = count($instrument_records);
        $max = floor($ratio * $total_count);
        // 
        // echo("Site: {$current_site} <BR>");
        // echo($current_count . " --- " . $total_count . "<BR>");
        // echo("Max (ratio: {$ratio}/jump: {$jump_step}): {$max} <BR><BR>");
        
       for($i = 0; $i < count($instrument_records) && $current_count + 1 <= $max; $i += 2){
          $commentID = $instrument_records[$i]["CommentID"];
          if(!find_cID($commentID, $this->reliability_table)){
            $db->insert('reliability', array('CommentID' => $instrument_records[$i]["CommentID"],
                                              'reliability_center_id' => $this->site_id[$reliability_sites[$reliability_site_index]],
                                              'Instrument' => $instrument
                                              ));
            $this->reliability_table[$instrument_records[$i]["CommentID"]] = $this->site_id[$current_site];
            $current_count++;
          }
          $reliability_site_index = ($reliability_site_index + 1) % count($reliability_sites);                  
       }
    }
    
    function get_current_index($instrument, $current_site, $reliability_sites, $db){
      $site_name = array_flip($this->site_id);
      $last_site = $db->selectOne("SELECT reliability_center_id FROM reliability where ID=(select max(ID) FROM reliability WHERE CommentID LIKE '%{$current_site}%' AND Instrument='{$instrument}' AND reliability_center_id<>{$this->site_id[$current_site]})");
      if(empty($last_site)){
        return 0;
      }
      else{
        return (array_search($site_name[$last_site], $reliability_sites) + 1) % count($reliability_sites);
      }
    }
}
?>