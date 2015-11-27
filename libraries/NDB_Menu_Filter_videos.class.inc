<?php
require_once 'NDB_Menu_Filter.class.inc';

/**
 * The menu for the reliability checking
 * @package mri
 * @subpackage NIHPD
 */


function array_remove($item, $array){
  $index = array_search($item, $array);
  if($index === false){
    return $array;
  }else{
    unset($array[$index]);
    return array_values($array); 
  }
}
 
class NDB_Menu_Filter_videos extends NDB_Menu_Filter
{

    var $centerIDMap;
    
    var $site_id = array('SEA' => 2, 'PHI' => 3, 'STL' => 4, 'UNC' => 5, 'UofA' => 6);
    
    var $reliability_table;

    function _hasAccess()
    {
        
    	//create user object
    	$user =& User::singleton();
        if($user->hasPermission('earli_videos')) {
            return true;
        }
    	return $user->hasPermission('video_upload');
    	    	
    }

    function _isEARLIUser() {
        $user =& User::singleton();
        return $user->hasPermission('earli_videos') && !$user->hasPermission('data_entry');
    }

    // Function to check if the user is working with EARLI videos or not. Save into a cookie,
    // so that filters work properly.
    function _viewingEARLI() {
        if(isset($_REQUEST['showEARLI'])) {
            $_SESSION['showEARLI'] = $_REQUEST['showEARLI'];
            $earli = $_REQUEST['showEARLI'];
        } else if(isset($_SESSION['showEARLI'])) {
            $earli = $_SESSION['showEARLI'];
        } else {
            $earli = '';
        }
        return !empty($earli);
    }



    function _setupVariables()
    {
        $user =& User::singleton();

        // create the centerID map
        $db =& Database::singleton();
        $pscRows = array();
        $db->select("SELECT CenterID, Name FROM psc", $pscRows);
        foreach($pscRows AS $row) {
            $this->centerIDMap[$row['CenterID']] = $row['Name'];
        }
        
        // the base query
        $query = " FROM videos v"; // left join candidate c using(pscid) ";
        if($this->_isEARLIUser() || ($this->_viewingEARLI() && $user->hasPermission('earli_videos'))) {
            $query .= " WHERE v.EARLI=True";
        } else {
            $query .= " WHERE (v.EARLI IS NULL OR v.EARLI = False)";
        }
        $query .= " AND (v.hide_video=false OR v.hide_video IS NULL)";

        // set the class variables
        $this->columns = array('v.record_id', 'v.File_name', 'v.File_size', 'v.uploaded_by', 'v.Instrument', 'v.PSCID', 'v.visitLabel', 'v.Date_taken', 'v.For_site', 'substring(v.comments, 1, 50) as comments', 'v.Data_dir', 'v.Date_uploaded');

        $this->query = $query;
        $this->group_by = '';
        $this->order_by = 'v.Instrument';
        $this->headers = array('File_name','uploaded_by', 'Instrument', 'PSCID', 'visitLabel', 'Date_Taken', 'For_site', 'comments', 'Date_uploaded', 'Edit Metadata');
        $this->validFilters = array('v.PSCID', 'v.Instrument', 'v.Data_dir', 'v.For_site', 'v.visitLabel', 'v.uploaded_by');

        $this->formToFilter = array(
                                    'File_name' => 'v.File_name',
                                    'Data_dir'  => 'v.Data_dir',
                                    'Instrument' => 'v.Instrument',
                                    'PSCID' => 'v.PSCID',
                                    'For_site' => 'v.For_site',
                                    'uploaded_by' => 'v.uploaded_by',
                                    'visitLabel' => 'v.visitLabel',
                                    'Date_uploaded' => 'v.Date_uploaded',
                                    'comments' => 'comments'
                                    // 'Lock_record' => 'session.Lock_record'
                                    );
        return true;
    }


    function _setFilterForm()
    {
    	// create user object
        $user =& User::singleton();

        $list_of_sites = Utility::getSiteList(false);
           // allow to view all sites data through filter
        if ($user->hasPermission('access_all_profiles') || $user->hasPermission('reliability_edit_all')) {
            // get the list of study sites - to be replaced by the Site object
            if(is_array($list_of_sites)) $list_of_sites = array('' => 'Any') + $list_of_sites;
        }
        else {
            // allow only to view own site data
            $site =& Site::singleton($user->getData('CenterID'));
            if ($site->isStudySite()) {
                $list_of_sites = array($user->getData('CenterID') => $user->getData('Site'));
            }
        }
        
        /// hack for Visit Labels... maybe get all the real visit labels from DB?
        $list_of_visit_labels = array(null=>'Any','V06'=>'V06','V12'=>'V12','V24'=>'V24','V36'=>'V36');
        $subproject_options = Utility::getSubprojectList();
        $subproject_options = array(null=>'Any') + $subproject_options;
        $DB = Database::singleton();
        $list_of_instruments_q = $DB->pselect("SELECT DISTINCT Instrument FROM videos", array());
        $list_of_instruments = array(null => 'Any');
        foreach ($list_of_instruments_q as $instrument) {
            $list_of_instruments[$instrument['Instrument']] = $instrument['Instrument'];
        }
        $lock_options = array(null=>'','Locked'=>'Locked','Unlocked'=>'Unlocked');

        // Form Elements
        $this->addBasicText('PSCID', 'PSCID:', array("size"=>9, "maxlength"=>7));
        $this->addSelect('Instrument', 'Instrument:', $list_of_instruments);
        $this->addSelect('visitLabel', 'Visit Label:', $list_of_visit_labels);
        $this->addSelect('For_site', 'For Site:', $list_of_sites);
        $this->addBasicText('uploaded_by', 'Uploaded By');
       
        return true;
    }

    function _setDataTableRows($count)
    {
        // This is a hack. It shouldn't be required, and it certainly shouldn't be here.
    	$user =& User::singleton();
        $this->tpl_data['Normal_Perm'] = ($user->hasPermission('video_upload') || $user->hasPermission('data_entry'));
        $this->tpl_data['EARLI_Perm'] = $user->hasPermission('earli_videos');
        // end hack

        $site_names = Utility::getSiteList(false); //array(null, "DCC", "SEA", "PHI", "STL", "UNC", "UofA");
        // print out
        $x = 0;
        foreach ($this->list as $item) {
            //count column
            $this->tpl_data['items'][$x][0]['value'] = $x + $count;

            //print out data rows
            $i = 1;
            // $identifier = $item['Tracking_log_ID'];
            $Data_dir = $item['Data_dir'];
            $record_id = $item['record_id'];
            $File_size = $item['File_size'];
            foreach ($item as $key => $val) {

                // Confused about this line
                if ($key =='Tracking_log_ID') continue;
                if ($key == 'Data_dir') continue;
                if ($key == 'record_id') continue;
                if ($key == 'File_size') continue;
                // {
                //                    $this->tpl_data['items'][$x][$i]['CommentID'] = $item['CommentID'];
                //               $this->tpl_data['items'][$x][$i]['Instrument'] = $item['Instrument'];
                //                   }
                $this->tpl_data['items'][$x][$i]['name'] = $key;
                
                if ($key == 'For_site'){
                    if(isset($site_names[$val])) {
                        $this->tpl_data['items'][$x][$i]['value'] = $site_names[$val];
                    } else {
                        $this->tpl_data['items'][$x][$i]['value'] = '';
                    }
                }else{
                  $this->tpl_data['items'][$x][$i]['value'] = $val;
                }
                
                if ($key == 'File_name'){
                   $this->tpl_data['items'][$x][$i]['Data_dir'] = $Data_dir;
                   $this->tpl_data['items'][$x][$i]['File_size'] = $this->format_size($File_size);
                }
                
                if ($key == 'Date_uploaded'){
                   $this->tpl_data['items'][$x][$i+1]['name'] = 'record_id';
                   $this->tpl_data['items'][$x][$i+1]['value'] = $record_id;
                }
                
               $i++;
            }
            $x++;
        }
        return true;
    }
    
    function format_size($value){
      if(is_null($value)){
        return null;
      }
      
      if($value >= 1000000000){
        $value = floor($value/1000000000);
        return "{$value} GB";
      }
      if($value >= 1000000){
        $value = floor($value/1000000);
        return "{$value} MB";
      }
      if($value >= 1000){
        $value = floor($value/1000);
        return "{$value} KB";
      }
      
      return "{$value} bytes";
      
    }
}
?>
