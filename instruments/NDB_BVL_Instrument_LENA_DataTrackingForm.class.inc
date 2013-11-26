<?php
class NDB_BVL_Instrument_LENA_DataTrackingForm extends NDB_BVL_Instrument
{
    var $ValidityEnabled = false;
    var $ValidityRequired = false;
    var $participate = array(""=>null,'yes'=>'YES. If yes, skip to Section C.','no'=>'NO. If no, complete Section B only.');
    var $session = array(""=>null,'1'=>'1','2'=>'2','3'=>'3','4'=>'4');
    var $duration = array(""=>null,'full_day'=>'Full day(16 hrs)','less_16hrs'=>'<16hrs','notused_del'=>'Recording not used or deleted');
    var $reasons_decline = array("issues_related_to_privacy"=>"Issues related to privacy","time_consuming_or_burdensome"=>"Time consuming or burdensome","spouse_not_participate"=>"Spouse or partner of consenting parent or caregiver does not want to participate","lena_not_seen_as_beneficial"=>"LENA not seen as beneficial","just_not_interested"=>"Just not interested","other"=>"Other"); 
    /**
    * sets up basic data, such as the HTML_Quickform object, and so on.
    *
    * @param string $commentID  the CommentID identifying the data to load
    * @param string $page       if a multipage form, the page to show
    * @return void
    * @access public
    */
    function setup($commentID, $page){

        $this->formType="XIN";
        $this->form = new HTML_Quickform('test_form');
        $this->page = $page;            // page label (number or
        // string - used by
        // user-defined child classes)

        // set the object properties
        $this->testName = "LENA_DataTrackingForm";           // test_names.Test_name
        $this->table = 'LENA_DataTrackingForm';             // name of table containing

        // data keyed by commentID
        $this->commentID = $commentID;

        //The array of dates/timestamps to convert to database dates/timestamps
        //Any HTML_Quickform date elements must be listed here
        $this->dateTimeFields=array("datecompleted");

        $this->_selectMultipleElements = array("reasonsdecline");

        $config =& NDB_Config::singleton();
        $this->dateOptions = array(
        'language' => 'en',
        'format'   => 'YMd',
        'minYear'  => $config->getSetting('startYear'),
        'maxYear'  => $config->getSetting('endYear'),
        'addEmptyOption' => true,
        'emptyOptionValue' => null
        );
        
        $db =& Database::singleton();
        if(Utility::isErrorX($db)) {
            return PEAR::raiseError ("Could not connect to database: ".$db->getMessage());
        }
        $record = $db->pselectRow("SELECT * FROM ".$this->table." WHERE CommentID=:cid", 
                                  array('cid' =>$this->getCommentID()));

        if (Utility::isErrorX($record)) {
            $record = array();
        }
        $record2 = $db->pselectRow("SELECT * FROM LENA_DataTrackingForm2  WHERE CommentID=:cid", 
                                   array('cid'=>$this->getCommentID()));

        if (Utility::isErrorX($record2)) {
            $record2 = array();
        }

      /*   $fields = array("Type","DLP","ProcessingFile","Timestamp","Duration","Meaningful","Distant","TV","Noise","Silence","CTC_Actual","CVC_Actual","AVA_StdScore","AVA_StdScore_Pct");*/
       $fields = array('Type','ChildKey','Id','DLP','ProcessingFile','Timestamp','Duration','Meaningful','Distant','TV','TV_Pct','Noise','Silence','AWC_Actual','AWC_Proj','AWC_Pct','CTC_Actual','CTC_Proj','CTC_Pct','CVC_Actual','CVC_Proj','CVC_Pct','AVA_StdScore','AVA_StdScore_Pct');

        for($i = 1; $i <= 32; $i++) {
            foreach($fields as $field) {
              $key = $field."_".$i;
              $this->localDefaults[$key] = $record[$key];
              if($this->localDefaults[$key] == "AVA_StdScore_Pct" || 
                 $this->localDefaults[$key] == "TV_Pct" ||
                 $this->localDefaults[$key] == "AWC_Pct" ||
                 $this->localDefaults[$key] == "CTC_Pct" ||
                 $this->localDefaults[$key] == "CVC_Pct") {
                   $this->localDefaults[$key] = $record[$key]."%";
              }
            }
        }
        for($i = 33; $i <= 64; $i++) {
            foreach($fields as $field) {
              $key = $field."_".$i;
              $this->localDefaults[$key] = $record2[$key];
              if($this->localDefaults[$key] == "AVA_StdScore_Pct" || 
                 $this->localDefaults[$key] == "TV_Pct" ||
                 $this->localDefaults[$key] == "AWC_Pct" || 
                 $this->localDefaults[$key] == "CTC_Pct" ||
                 $this->localDefaults[$key] == "CVC_Pct") {
                     $this->localDefaults[$key] = $record2[$key]."%";
              }
            }
        }
        // setup the form
        $this->_setupForm();

    }
    /**
     * method to build the HTML_Quickform object into a paged form
     *
     * @return void
     * @access private
     */
    function _setupForm(){
        if(preg_match("/LENA_DataTrackingForm(_page[0-9]+)/",$this->page,$matches)){
            call_user_method($matches[1], $this);
        } else {
            $this->_main();
        }

        //Defines the call back function for HTML Quickform to use when validating the form.
        $this->form->addFormRule(array(&$this,'XINValidate'));

    }
    /**
     * generates the main page of the form.
     *
     * @return void
     * @access private
     *
     */
    function _main(){
       
        $this->addHeader("LENA Data Tracking Form");    
        $this->addLabel("<BR><strong>Section A. Data Submission</strong>");
        $this->addBasicDate("datecompleted","Date Form Completed:", $this->dateOptions);
        $this->addSelect("family_participate", "<BR>Did family agree to participate?",$this->participate); 
        $this->addLabel("<BR><strong>Section B. Reason(s) for Decline</strong>");
        $this->form->addElement("select","reasonsdecline","Check All That Apply", $this->reasons_decline, "multiple");
        $this->XINRegisterRule("reasonsdecline",array("family_participate{@}=={@}no"));

        $this->addLabel("<BR><strong>Section C. DLP Tracking Information</strong>");
        $this->addSelect("number_session","Number of Recording sessions:", $this->session);
        $this->XINRegisterRule("number_session",array("family_participate{@}=={@}yes"));
        
        $this->addLabel("<BR> Duration of recording session:");
        $this->addSelect("duration_session1","Recording Session 1", $this->duration);
        $this->XINRegisterRule("duration_session1",array("number_session{@}=={@}1|2|3|4"));
        $this->addTextAreaElement("comments_session1","Comments(e.g., did DLP malfunction?)",
                                   array("number_session{@}=={@}1|2|3|4"));
        
        $this->addSelect("duration_session2","Recording Session 2", $this->duration);
        $this->XINRegisterRule("duration_session2",array("number_session{@}=={@}2|3|4"));
        
        $this->addTextAreaElement("comments_session2","Comments(e.g., did DLP malfunction?)",
                                   array("number_session{@}=={@}2|3|4"));
       
        $this->addSelect("duration_session3","Recording Session 3", $this->duration);
        $this->XINRegisterRule("duration_session3",array("number_session{@}=={@}3|4"));
        $this->addTextAreaElement("comments_session3","Comments(e.g., did DLP malfunction?)",
                                   array("number_session{@}=={@}3|4"));

       
        $this->addSelect("duration_session4","Recording Session 4", $this->duration);
        $this->XINRegisterRule("duration_session4",array("number_session{@}=={@}4"));
        $this->addTextAreaElement("comments_session4","Comments(e.g., did DLP malfunction?)",
                                   array("number_session{@}=={@}4"));
        $this->form->addElement('file', 'recording_file', 'Upload the export file');

    }

    function _page1() {
        
        $fields = array("Type","DLP","ProcessingFile","Timestamp","Duration","Meaningful","Distant","TV","Noise","Silence","CTC_Actual","CVC_Actual","AVA_StdScore","AVA_StdScore_Pct");
        foreach($fields as $field) {
            $group[] = &$this->form->createElement("static", null, null, $field);
            $group[] = &$this->form->createElement("static", null, null, null);
        }
        $this->form->addGroup($group, 'header_group', "", $this->_GUIDelimiter, FALSE);
        unset($group);


        for($i=1; $i <= 64; $i++){
            foreach($fields as $field) {
               //$this->form->addElement('static', $field."_".$i, "Values {$i}:");
               $group[] = $this->form->createElement('static', $field."_".$i);
               $group[] = &$this->form->createElement("static", null, null, null);
            }
            $this->form->addGroup($group, $i.'_group', "", $this->_GUIDelimiter, FALSE);
            unset($group);

        }

        
    }
   
    /**
     * isValid checks the validity of the file.
     *
     * @param     string  $file    The full filename including directory.
     *
     * @return    bool    $success     if operation succeeded
     * @access    public
     */
    function isValid(&$file, $args){
         $correct_filename = $args['PSCID'] .'_'. $args['candID'] .'_'. $args['visitLabel'];
 
        if(!preg_match("/^{$correct_filename}/i", $file->fileInfo['name']) ){
            $errors[]="Incorrect Filename: Filename begin with: " . $correct_filename;
            return $errors;
        }

        return true;

    }

    function _saveValues ($values)
    {
        $timepoint =& TimePoint::singleton($this->getSessionID());
        $candidate =& Candidate::singleton($timepoint->getCandID());

        if(isset($values['datecompleted'])) {
            $date = $values['datecompleted'];
            if(!empty($date['Y']) && !empty($date['M']) && !empty($date['d'])) {
                $values['datecompleted'] = $this->_getDatabaseDate($date); 
             //   $this->_saveCandidateAge($values);
            }  else {
                unset($values['datecompleted']);
            }
        }

        if(!empty($this->_selectMultipleElements)){
            foreach($this->_selectMultipleElements AS $elname){
                if(isset($values[$elname]) && is_array($values[$elname])){
                    $values[$elname]=implode("{@}",$values[$elname]);
                }
            }
        }


        require_once "File_Upload.class.inc";
        $file=new File_Upload;

        //pass the existing form ($form) by reference to File_Upload, and register the file_upload field names being used.
        $file->registerForm($this->form);

        //Tell File_Upload what file handlers to use.
        $file->setFileHandler("recording_file", $this);

        //Set the target directory that you want files moved into once they are validated and processed.
        $config = NDB_Config::singleton();
        $dir = $config->getSetting("UploadDir");
        if(empty($dir)) {
            $dir = ".";
        };
        $file->setBaseUploadDirectory($dir . "/LENA/");

        //Set the prefix to prepend to the filenames
        //$file->setFilenamePrefix($timepoint->getVisitLabel()."-".$this->testName."-");

        //set the the IDs to the handler functions.
        $user =& User::singleton();
        $file->setHandlerArgs(array("CommentID"=>$this->getCommentID(),
                    "candID"=>$candidate->getCandID(),
                    "PSCID"=>$candidate->getPSCID(),
                    "visitLabel"=>$timepoint->getVisitLabel(),
                    "username"=>$user->getUsername(),
                    "values"=>$values)
                );



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
        }
        unset($values['candID'], $values['sessionID'], $values['commentID'], $values['test_name'], $values['page'], $values['fire_away'], $values['subtest'], $values['MAX_FILE_SIZE'], $values['recording_file']);
        $this->_save($values);



    }

    function importFile(&$file, $args) {
        $fp=fopen($file->fileInfo['tmp_name'], "r");
        $contents=fread($fp,filesize($file->fileInfo['tmp_name']));
        fclose($fp);

        $values=array(
                'UserID'    =>$args['username'],
                'Status'    =>'assembly',
                'File_type' =>'recording',
                'File_name' =>$file->getDestinationFilename(),
                'Data_dir'  =>$file->getDestinationDirectory()
                );

         $upload_values = array(); //uploading values to LENA_DataTrackingForm table
         $upload_values2 = array(); //uploading values to LENA_DataTrackingForm table
         $fields = array("Type","DLP","ProcessingFile","Timestamp","Duration","Meaningful","Distant","TV","Noise","Silence","CTC.Actual","CVC.Actual","AVA_StdScore","AVA_StdScore_Pct");//removed TV.Pct, AWC.Actual for testing purposes
        //Cycle through the lines and extract the data
        $lines=explode("\n",$contents);
        $keys = explode("\t", $lines[0]);
        $vals = explode("\t", $lines[1]);
        $header = explode(",",$keys[0]);
        for($i=1; $i< sizeof($lines); $i++) {
            foreach($header as $id=>$value) {
                $newline = explode("\t",$lines[$i]);
                $data = explode(",", $newline[0]);
                if(in_array($value, $fields)) {
                    $value = str_replace('.','_',$value);
                    $field = $value."_".$i;
                    $data[$id] = preg_replace('/\s+/','',$data[$id]);
                    if($i <=32) {
                        $upload_values[$field] = $data[$id];
                    } else {
                        $upload_values2[$field] = $data[$id];

                    }
                }
            }   
        }
        $upload_values2['CommentID'] = $args['CommentID'];
        $db=& Database::singleton();

        ///Setting trackchanges to false because getting error messages
        $db->_trackChanges = false;
        ////////////////////////////////////////////////////////////////
//print_r($upload_values);
        $result = $db->update($this->testName, $upload_values, array('CommentID'=>$args['CommentID']));
        if(Utility::isErrorX($result)) {
            print $result->getMessage();
            return $this->raiseError('Could not save to database');
        }
        $ok = $db->insert("LENA_DataTrackingForm2", $upload_values2);
        return true;

    }
    /**
     * getTargetDirectory retrieves info about where the file should be stored.
     *
     * The returned directory is ADDED to the baseUploadDirectory proprety.  It should have a trailing slash.
     *
     * @param     string  $file    The full filename including directory.
     *
     * @return    bool    $success     if operation succeeded
     * @access    public
     */
    function getTargetDirectory(&$file, $args){
        $output=$args['candID']."/";
        return $output;
    }

}
       
?>
