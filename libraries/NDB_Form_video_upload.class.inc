<?php
require_once "NDB_Form.class.inc";

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
        if ($site->isStudySite()) {
            return $user->hasPermission('data_entry');
        }
        return false;
    }

    function _process($values)
    {
        // set up the arguments to Candidate::createNew
         
        //------------------------------------------------------------
        
        if($this->_saveFile($values)){
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
         
        $db->select("SELECT PSCID FROM candidate WHERE PSCID LIKE '{$site->getCenterName()}%' ORDER BY PSCID", $candidates);


        $candidates = hash_it($candidates, "PSCID");
        
        $this->form->addElement("select", "Instrument", "Instrument", $instruments);
        $this->form->addElement("select", "PSCID", "PSCID", $candidates);
        $this->form->addElement("select", "visitLabel", "visitLabel", array("v06" => "v06", "v12" => "v12", "v24" => "v24", "v36" => "v36"));
        $this->form->addElement("select", "For_site", "For_site", array(null, "DCC", "SEA", "PHI", "STL", "UNC"));
        $this->form->addElement("textarea", "comments", "comments");
        
        $this->form->addElement('file', 'video_file', 'Upload a video');
        $this->form->addRule('PSCID', 'PSCID required.', 'required');
        $this->form->addRule('Instrument', 'Instrument is required.', 'required');
        $this->form->addRule('visitLabel', 'Visit Label is required.', 'required');
        $this->form->addRule('video_file', 'No file selected.', 'required');

        $this->form->addFormRule(array(&$this, '_validate'));
    }

    function _validate($values)
    {
        $errors = array();


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
      
      function isValid(&$file, $args){
        $correct_filename = $args['values']['PSCID'] .'_'. $args['values']['visitLabel'] .'_'. $args['values']['Instrument']; 
         if(!preg_match("/^{$correct_filename}/i", $file->fileInfo['name']) ){
               $errors[]="Incorrect Filename: Filename begin with: " . $correct_filename;
               return $errors;
           }
        
        return true;
      }

      function importFile(&$file, $args){
        $values=array(
            'File_type' =>'video_file',
            'File_name' =>$file->getDestinationFilename(),
            'Data_dir'  =>$file->getDestinationDirectory(),
            'Instrument'=>$args['values']['Instrument'],
            'PSCID'=>$args['values']['PSCID'],
            'uploaded_by' => $args['user_id'],
            'For_site' => $args['values']['For_site'],
            'visitLabel' => $args['values']['visitLabel'],
            'comments' => $args['values']['comments']
        );
        
        $db=& Database::singleton();
        
        $db->selectRow("SELECT * FROM videos WHERE Instrument = '{$values['Instrument']}' AND PSCID = '{$values['PSCID']}' AND visitLabel = '{$values['visitLabel']}'", $row);
          if (PEAR::isError($row)) {
              return PEAR::raiseError("DB Error: ".$row->getMessage());
          }

          if (empty($row)) {
            
            // insert the event
            $result = $db->insert('videos', $values);
  
        } else {
            // update the event
            $result = $db->update('videos', $values, array('PSCID'=>$args['values']['PSCID'], 'Instrument'=>$args['values']['Instrument'], 'visitLabel' => $args['values']['visitLabel']));
        }

        $result = $db->update('videos', $values, array('PSCID'=>$args['values']['PSCID'], 'Instrument'=>$args['values']['Instrument'], 'visitLabel' => $args['values']['visitLabel']));
        if($this->isError($result)) {
            print $result->getMessage();
            return $this->raiseError('Could not save to database');
        }
        return true;
      }
}
?>