<?php
require_once "NDB_Form.class.inc";
require_once "Utility.class.inc";
/**
 * The forms for the new profile menu
 * @package main
 */
 
function hash_it($array, $item){
  $new_array = array();
  foreach($array as $key => $value){
    $new_array[$array[$key][$item]]=$array[$key][$item];
  }
  return $new_array;
}

 
class NDB_Form_video_upload extends NDB_Form
{
    function _hasAccess()
    {
        // create user object
        $user =& User::singleton();
        if(PEAR::isError($user)) {
            return PEAR::raiseError("User Error: ".$user->getMessage());
        }

        $site =& Site::singleton($user->getData('CenterID'));
        if (PEAR::isError($site)) {
            return PEAR::raiseError("Unable to construct the list_of_sites array: ".$site->getMessage());
        }
        if ($user->hasPermission('earli_videos')) {
            return true;
        }
        if ($site->isStudySite()) {
            return $user->hasPermission('data_entry');
        }
        return false;
    }
    function _isEARLIUser() {
        $user =& User::singleton();
        return $user->hasPermission('earli_videos') && !$user->hasPermission('data_entry');
    }

    function _process($values)
    {
        if($values['hide_video'] || $values['hide_video_confirm']) {
            // Validate should have already checked this, but double check
            if($values['hide_video'] && $values['hide_video_confirm']) {
                $DB =& Database::singleton();
                $DB->update("videos", array('hide_video' => true), array('record_id' => $this->identifier));
                $this->tpl_data['message'] = "Video successfully deleted";
            }
        }
        // set up the arguments to Candidate::createNew
         
        //------------------------------------------------------------
        
        elseif($this->_saveFile($values)){
          $this->tpl_data['success'] = true; 

          // freeze it, just in case
          $this->form->freeze();
        }
        
    }

    function video_upload()
    {
        // create user object
        $user =& User::singleton();
        if(PEAR::isError($user)) {
            return PEAR::raiseError("User Error: ".$user->getMessage());
        }
        
        $site =& Site::singleton($user->getData('CenterID'));
        if (PEAR::isError($site)) {
            return PEAR::raiseError("Unable to construct the list_of_sites array: ".$site->getMessage());
        }
      
        $config =& NDB_Config::singleton();
        $db =& Database::singleton();
         if(PEAR::isError($db)) {
             return PEAR::raiseError ("Could not connect to database: ".$db->getMessage());
         }
         
        $db->select("SELECT test_name FROM test_names ORDER BY test_name", $instruments);
         
         
        $instruments = hash_it($instruments, "test_name");
        unset($instruments['EARLI_interview_PART_1']);
        unset($instruments['EARLI_interview_PART_2']);
        unset($instruments['EARLI_interview_PART_3']);
        unset($instruments['EARLI_interview_PART_4']);
        unset($instruments['EARLI_interview_revised']);
        if($this->_isEARLIUser()) {
            $instruments = array ('aosi' => 'AOSI'); // add others here
        }
        if($user->hasPermission('earli_videos')) {
            $instruments = array_merge($instruments, array('EARLI' => 'EARLI Questionaire'));
        }
         
        $db->select("SELECT PSCID FROM candidate WHERE PSCID LIKE '{$site->getCenterName()}%' ORDER BY PSCID", $candidates);
        $db->select("SELECT PSCID FROM candidate WHERE PSCID NOT LIKE '{$site->getCenterName()}%' ORDER BY PSCID", $candidates2);

        $candidates = hash_it($candidates + $candidates2, "PSCID");
        
        $this->form->addElement("select", "Instrument", "Instrument", $instruments);
        if($this->_isEARLIUser()) {
            $this->form->addElement("text", "PSCID", "PSCID");
        } else {
            $this->form->addElement("select", "PSCID", "PSCID", $candidates);
        }
        $visit_list = Utility::getVisitList();
        $this->form->addElement("select", "visitLabel", "Visit Label", $visit_list);
        $dateOptions = array(
                             'language' => 'en',
                             'format'   => 'YMd',
                             'minYear'  => $config->getSetting('startYear'),
                             'maxYear'  => $config->getSetting('endYear'),
                             'addEmptyOption' => true,
                             'emptyOptionValue' => null
                             );

        $this->form->addElement('date', 'Date_taken', 'Date of Administration', $dateOptions);
        //$this->form->addElement("select", "For_site", "Site This File is Being Uploaded For", array(null, "DCC", "SEA", "PHI", "STL", "UNC", "UofA"));
        $this->form->addElement("select", "For_site", "Site This File is Being Uploaded For", Utility::getSiteList(false));
        $this->form->addElement("select", "multipart", "Is this upload split into multiple parts?", array("Yes" => "Yes", "No" => "No"));
        $this->form->addElement("select", "EARLI", "Is this an EARLI collaboration video?", array('' => '', "1" => "Yes", "0" => "No"));
        $this->form->addElement("textarea", "comments", "Comments (optional)", array ('rows' => 5, 'cols' => 50));
        if($this->identifier){
          $this->form->addElement('static', 'File_name', 'File name');
        }else{
          $this->form->addElement('file', 'video_file', 'File to Upload');
          $this->form->addRule('video_file', 'No file selected.', 'required');
        }
        
        $this->form->addRule('PSCID', 'PSCID required.', 'required');
        $this->form->addRule('Instrument', 'Instrument is required.', 'required');
        $this->form->addRule('visitLabel', 'Visit Label is required.', 'required');

        $this->form->addElement("checkbox", "hide_video", "Delete video");
        $this->form->addElement("checkbox", "hide_video_confirm", "Delete video (Confirmation)");
        

        $uploaded_by = $db->pselectOne("SELECT uploaded_by FROM videos WHERE record_id=:identifier", array(':identifier' => $this->identifier));
        if($uploaded_by == $user->getUsername()) {
            $this->tpl_data['has_delete_permission'] = true;
        }
       
        $this->form->addFormRule(array(&$this, '_validate'));
    }

    function _validate($values)
    {
        $errors = array();
        if($values['hide_video'] || $values['hide_video_confirm']) {
            if(empty($values['hide_video']) || empty($values['hide_video_confirm'])) {
                $errors['hide_video'] = "Must check BOTH boxes to delete";
            }
        }
        if($values['EARLI'] == '' || !isset($values['EARLI'])) {
                $errors['EARLI'] = "EARLI collaboration video flag required.";
        }


        // if (empty($values['gender'])) {
        //         $errors['gender'] = 'Gender is required';
        //     }    
        return $errors;
    }
    
    /**
    * getTargetDirectory retrieves info about where the file should be stored.
    *
    * The returned directory is ADDED to the baseUploadDirectory property.  It should have a trailing slash.
    *
    * @param     string  $file    The full filename including directory.
    *
    * @return    bool    $success		if operation succeeded
    * @access    public
    */
    function getTargetDirectory(&$file, $args){
        $output="{$args["user_id"]}/";
        return $output;
    }
    
    // methods available to all children
      /**
       * Save the file to the DataBase
       *
       * @param array $values      the array of values from the form
       * @return true on success, false othewise
       * @access private
       */
      function _saveFile($values)
      {
          if(isset($values['Date_taken'])) {
              $Date_taken = $values['Date_taken'];
              $values['Date_taken'] = sprintf("%04d-%02d-%02d", $Date_taken['Y'], $Date_taken['M'], $Date_taken['d']);
          }
          
          if(!empty($this->identifier)){
            $db=& Database::singleton();
            $result = $db->update('videos', $values, array('record_id'=>$this->identifier));
            if($this->isError($result)) {
                print $result->getMessage();
                return $this->raiseError('Could not save to database');
            }
            return true;
          }else{
            require_once "File_Upload.class.inc";
            $file=new File_Upload;

            //pass the existing form ($form) by reference to File_Upload, and register the file_upload field names being used.
            $file->registerForm($this->form);

            //Tell File_Upload what file handlers to use.
            $file->setFileHandler("video_file", &$this);
            $file->overwriteMode="overwrite";

            //Set the target directory that you want files moved into once they are validated and processed.
            $file->setBaseUploadDirectory("./videos");

            //Set the prefix to prepend to the filenames
            //$file->setFilenamePrefix($timepoint->getVisitLabel()."-".$this->testName."-");

            $user =& User::singleton();
            if(PEAR::isError($user)) {
                return PEAR::raiseError("User Error: ".$user->getMessage());
            }

            //set the the IDs to the handler functions.
            $file->setHandlerArgs(array("user_id" => $user->getUsername(), "values"=>$values));

            //If the form is validated, call File_Upload::processFiles() which loops through the files and 
            //proccesses them (including verify, move, and import steps)
            $file->processFiles();

            //echo error messages
            if(!empty($file->errorLog)){
               while(list($fileType,$fileErrors)=each($file->errorLog)){
                   foreach($fileErrors AS $error){
                        echo "<span style='color:red'><b>Upload Error</b> $fileType: $error</span><br>";
                   }
               }
               return false;
            } 
            return true;
          }

      }
      
      function _getDefaults()
      {
          // Default to "No" for multipart, so that the behaviour doesn't
          // change
          $defaults = array('multipart' => 'No', 'EARLI' => 'No');

          if (!empty($this->identifier)) {
            $db=& Database::singleton();

            $db->selectRow("SELECT * FROM videos WHERE record_id = '{$this->identifier}'", $row);
            if (PEAR::isError($row)) {
              return PEAR::raiseError("DB Error: ".$row->getMessage());
            }

              // get the user defaults
  	        $defaults = $row;
          }
          return $defaults;
      }
      
      function isValid(&$file, $args){
        $errors = array();

        $correct_filename = $args['values']['PSCID'] .'_'. $args['values']['visitLabel'] .'_'. $args['values']['Instrument']; 

        $Stmt = "SELECT count(*) as Total FROM videos WHERE Instrument = '{$args['values']['Instrument']}' AND PSCID = '{$args['values']['PSCID']}' AND visitLabel = '{$args['values']['visitLabel']}'";

        $db=& Database::singleton();
        $db->selectRow($Stmt, $CountFiles);
        if($CountFiles['Total'] > 1 && $_REQUEST['multipart'] != 'Yes') {
            $errors[]="Incorrect value for split file selected.";
        }

         if(!preg_match("/^{$correct_filename}/i", $file->fileInfo['name']) ){
               $errors[]="Incorrect Filename: Filename begin with: " . $correct_filename;
           }

        if(count($errors) > 0) 
            return $errors;
        
        return true;
      }

      function importFile(&$file, $args){
        $filename = $file->getDestinationFileName();
        $values=array(
            'File_type' =>'video_file',
            'File_name' =>$filename,
            'Data_dir'  =>$file->getDestinationDirectory(),
            'File_size' => $file->fileInfo['size'],
            'Instrument'=>$args['values']['Instrument'],
            'PSCID'=>$args['values']['PSCID'],
            'uploaded_by' => $args['user_id'],
            'For_site' => $args['values']['For_site'],
            'visitLabel' => $args['values']['visitLabel'],
            'Date_taken' => $args['values']['Date_taken'],
            'comments' => $args['values']['comments'],
            'EARLI' => $args['values']['EARLI']
        );
        
        $db=& Database::singleton();
        
        // SQL to run to check if the file's already 
        $Stmt = "SELECT * FROM videos WHERE Instrument = '{$values['Instrument']}' AND PSCID = '{$values['PSCID']}' AND visitLabel = '{$values['visitLabel']}'";

        if($_REQUEST['multipart'] == 'Yes') {
            $Stmt .= " AND File_name=" . $db->quote($filename);
        }

        $db->selectRow($Stmt, $row);
          if (PEAR::isError($row)) {
              return PEAR::raiseError("DB Error: ".$row->getMessage());
          }

          if (empty($row)) {
            
            // insert the event
            $result = $db->insert('videos', $values);
  
        } else {
            // update the event
            $WhereCriteria = array('PSCID'=>$args['values']['PSCID'], 
                        'Instrument'=>$args['values']['Instrument'], 
                        'visitLabel' => $args['values']['visitLabel']);

            // Using this if statement makes duplicates appear if a
            // multipart file was already uploaded, and they forget
            // to change the dropdown for the second upload. So for
            // now the filename is always part of the criteria.
            if($_REQUEST['multipart'] == 'Yes') {
                $WhereCriteria['File_name'] = $filename;
            }
           
            $values['hide_video'] = false;
            $result = $db->update('videos', $values, $WhereCriteria);
        }

        //$result = $db->update('videos', $values, array('PSCID'=>$args['values']['PSCID'], 'Instrument'=>$args['values']['Instrument'], 'visitLabel' => $args['values']['visitLabel']));
        if($this->isError($result)) {
            print $result->getMessage();
            return $this->raiseError('Could not save to database');
        }
        return true;
      }
}
?>