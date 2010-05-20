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
    	if (PEAR::isError($user)){
    		
    		return PEAR::raiseError("User error: " . $user->getMessage());
    	}
    	
    	return $user->hasPermission('video_upload');
    	    	
    }



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
        $query = " FROM videos";

        // only view their own profiles, unless they have permission to see all
        if (!($user->hasPermission('reliability_edit_all') || $user->hasPermission('access_all_profiles'))) {
            $query .= " AND candidate.centerID = '" . $user->getData('CenterID') . "' "; 
        }

        // set the class variables
        $this->columns = array('videos.record_id', 'videos.File_name', 'videos.File_size', 'videos.uploaded_by', 'videos.Instrument', 'videos.PSCID', 'videos.visitLabel', 'videos.Date_taken', 'videos.For_site', 'substring(videos.comments, 1, 50) as comments', 'videos.Data_dir', 'videos.Date_uploaded');

        $this->query = $query;
        $this->group_by = '';
        $this->order_by = 'videos.Instrument';
        $this->headers = array('File_name','uploaded_by', 'Instrument', 'PSCID', 'visitLabel', 'Date_Taken', 'For_site', 'comments', 'Date_uploaded', 'Edit Metadata');
        $this->validFilters = array('videos.PSCID', 'videos.Instrument', 'videos.Data_dir', 'videos.For_site', 'videos.visitLabel');

        $this->formToFilter = array(
                                    'File_name' => 'videos.File_name',
                                    'Data_dir'  => 'videos.Data_dir',
                                    'Instrument' => 'videos.Instrument',
                                    'PSCID' => 'videos.PSCID',
                                    'For_site' => 'videos.For_site',
                                    'uploaded_by' => 'videos.uploaded_by',
                                    'visitLabel' => 'videos.visitLabel',
                                    'Date_uploaded' => 'videos.Date_uploaded',
                                    'comments' => 'comments'
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
        $this->form->addElement('text', 'PSCID', 'PSCID:', array("size"=>9, "maxlength"=>7));
        $this->form->addElement('select', 'Instrument', 'Instrument:', $list_of_instruments);
	 // $this->form->addElement('select', 'Lock_record', 'Lock_record:', $lock_options);
       
        return true;
    }

    function _setDataTableRows($count)
    {
        $site_names =array(null, "DCC", "SEA", "PHI", "STL", "UNC");
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
                    $this->tpl_data['items'][$x][$i]['value'] = $site_names[$val];
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
