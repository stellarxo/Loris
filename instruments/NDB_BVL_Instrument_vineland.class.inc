<?php

require_once 'HTML/QuickForm.php';
require_once 'HTML/QuickForm/Renderer/Array.php';

class NDB_BVL_Instrument_vineland extends NDB_BVL_Instrument
{
    /**
    * sets up basic data, such as the HTML_Quickform object, and so on.
    *
    * @param string $commentID  the CommentID identifying the data to load
    * @param string $page       if a multipage form, the page to show
    * @return void
    * @access public
    */
    function _setup($commentID, $page){
        $this->formType="XIN";
        $this->form = new HTML_Quickform('test_form');
        $this->page = $page;            // page label (number or
        // string - used by
        // user-defined child classes)

        //         object properties now set in subclasses
        //        $this->testName = "vineland";           // test_names.Test_name
        //        $this->table = 'vineland';              // name of database table corresponding to instrument

        // data keyed by commentID
        $this->commentID = $commentID;

        //The array of dates/timestamps to convert to database dates/timestamps
        //Any HTML_Quickform date elements must be listed here
        $this->dateTimeFields=array("Date_taken");

        //The array of selects with multiple answers allowed
        //Any HTML_Quickform multiple selects must be listed here
        $this->_selectMultipleElements = array();

        // required fields for data entry completion status
        $this->_requiredElements = array('Date_taken', 'Examiner', 'File_name');

        // setup the form
        $this->_setupForm();

    }

    //If the instrument is not paged, remove the switch from the _setupForm method and add all the form Elements in this function.

     /**
     * method to build the HTML_Quickform object into a paged form
     *
     * @return void
     * @access private
     */
     function _setupForm(){
         if(preg_match("/" . $this->testName . "(_page[0-9]+)/",$this->page,$matches)){
             call_user_method($matches[1], $this);
         } else {
             $this->_main();
         }

         //Defines the call back function for HTML Quickform to use when validating the form.
         $this->form->addFormRule(array(&$this,'XINValidate'));
     }
    
    //If the instrument is not paged, remove the switch from the _setupForm method and add all the form Elements in this function.

     /**
     * method to build the HTML_Quickform object into a paged form
     *
     * @return void
     * @access private
     */
     
    function _main(){

         // display test name
         $this->form->addElement('header', 'instrument_title', $this->getFullName());
         $testName = isset($_REQUEST['test_name']) ? $_REQUEST['test_name'] : '';
         $candID = isset($_REQUEST['candID']) ? $_REQUEST['candID'] : '';
         $sessionID = isset($_REQUEST['sessionID']) ? $_REQUEST['sessionID'] : '';
         $this->form->updateAttributes(
             array(
                 'action' =>"main.php?test_name=$testName&candID=$candID&sessionID=$sessionID&commentID=".$this->getCommentID()
             )
         );

         // add examiner & date of administration
         //$this->form->addElement('static', 'Date_taken_display', 'Date of Administration');
         
         // Get the item scores
         $record=array();

         $db =& Database::singleton();
         
         $query = "SELECT * FROM ".$this->table." WHERE CommentID='".$this->getCommentID()."'";
         $db->selectRow($query, $record);
         

         $this->_addMetadataFields();
         $this->form->addElement("advcheckbox", "dde_check", "Performed in-software double data entry:", null, null, array(false, true));
         $this->form->addRule('dde_check', 'Double data entry must be preformed in software.', 'required');

         $this->form->addElement('file', 'vineland_file', 'Upload the vineland file');

         $this->form->addElement('static', "File_name", "Uploaded File");
         
         
         // This used to be null, but it throws off the quickform parser,
         // so I changed it to 95% for now - Dave
         $percentile = "95%";
          if(!empty($record["ABC_85%_CI"])){
             $percentile = "85%";   
          } else if(!empty($record["ABC_90%_CI"])){
             $percentile = "90%";     
          }else if(!empty($record["ABC_95%_CI"])){
             $percentile = "95%";                  
          }
         
          $this->form->addElement('header', null, "Adaptive Behaviour");
         
         
         //scoring column headers
           $group[] = $this->form->createElement('static', "RAW");
           $group[] = $this->form->createElement('static', "VSCALE");
           $group[] = $this->form->createElement('static', "STD_SCORE");
           $group[] = $this->form->createElement('static', $percentile . "_CI");
           $group[] = $this->form->createElement('static', "%ILE_RANK");
           $group[] = $this->form->createElement('static', "ADAPT_LEVEL");
           $group[] = $this->form->createElement('static', "AGE_EQUIV");
           $group[] = $this->form->createElement('static', "STANINE");
           $group[] = $this->form->createElement('static', "SW");
           $group[] = $this->form->createElement('static', "STATUS");
           $this->form->addGroup($group, 'score_header_group', "<strong>Domain/Subdomain</strong>", $this->_GUIDelimiter, FALSE);
           unset($group);


           //score fields
           $domains = array("REC"=>"Receptive", "EXP"=>"Expressive", "WRN"=>"Written", "COM"=>"<strong>Communication</strong>",
                           "PER"=>"Personal", "DOM"=>"Domestic", "CMM"=>"Community", "DLS"=>"<strong>Daily Living Skills</strong>",
                           "IPR"=>"Interpersonal Relationships", "PL"=>"Play and Leisure Time", "CS"=>"Coping Skills", "SOC"=>"<strong>Socialization</strong>",
                           "GMS"=>"Gross Motor Skills", "FMS"=>"Fine Motor Skills", "MS"=>"<strong>Motor Skills</strong>", "ABC" => "<strong>Adaptive Behaviour Composite</strong>");
           $columnHeaders = array("RAW" => "<strong>Raw Score</strong>", "VSCALE" => "<strong>v-Scale</strong>", "STD_SCORE" => "<strong>Standard Score</strong>", 
                           $percentile . "_CI" => "<strong>" . $percentile . " Confidence Interval</strong>", "%ILE_RANK" => "<strong>%ile Rank</strong>",
                           "ADAPT_LEVEL" => "<strong>Adaptive Level</strong>", "AGE_EQUIV" => "<strong>Age Equivalent</strong>", "STANINE" => "<strong>Stanine</strong>",
                           "SW" => "<strong>Strength/Weakness</strong>", "STATUS" => "<strong>Status</strong>");
           
           foreach($columnHeaders as $field=>$label) {
               $columnHeaders[$field] .= $this->indent;
           }
             $this->localDefaults = array_merge($this->localDefaults, $columnHeaders);

           foreach($domains as $field=>$label) {
               foreach($columnHeaders as $scoreField=>$scoreLabel) {
                  
                  // Domain scores and ABC don't have AGE_EQUIV, but add a blank column to keep the table aligned
                  if(($field == "COM" || $field == "DLS" || $field == "SOC" || $field == "MS" || $field == "ABC") && $scoreField == "AGE_EQUIV"){
                      $group[] = $this->form->createElement('static', null, "&nbsp;");
                      continue;
                  }
                  // Subdomains don't have STD_SCORE, %ILE_RANK, or STANINE, but again add a blank column to keep the table aligned
                  if(($field == 'REC' || $field == 'EXP' || $field == 'WRN' ||  // Communication subdomains
                      $field == 'PER' || $field == 'DOM' || $field == 'CMM' ||  // Daily Living Skills subdomains
                      $field == 'IPR' || $field == 'PL'  || $field == 'CS'  ||  // Socialization subdomains
                      $field == 'GMS' || $field == 'FMS') &&                    // Motor skills subdomains
                      ($scoreField == 'STD_SCORE' || $scoreField == '%ILE_RANK' || $scoreField == 'STANINE')
                      ) {
                      $group[] = $this->form->createElement('static', null, "&nbsp;");
                      continue;

                  }

                  if(($field == "COM" || $field == "DLS" || $field == "SOC" || $field == "MS") && $scoreField == "VSCALE"){
                     $scoreField = "SUM_VSCALES_FOR_DOMAIN";
                  }
                  if($field == "ABC" && $scoreField == "RAW"){
                     $scoreField = "SUM_ALL_DOM_STD_SCORES";
                  }
                  $group[] = $this->form->createElement('static', "{$field}_{$scoreField}");
               }
               $this->form->addGroup($group, "{$label}_group", $label, $this->_GUIDelimiter, FALSE);
               unset($group);
           }         
         
         $this->localDefaults = array_merge($this->localDefaults, array("MAL_TABLE_LEVEL" => "<strong>Level</strong>"));
                  
         $this->form->addElement('header', null, "Maladaptive Behaviour Index");
         //scoring column headers
           $group[] = $this->form->createElement('static', "RAW");
           $group[] = $this->form->createElement('static', "VSCALE");
           $group[] = $this->form->createElement('static', $percentile . "_CI");
           $group[] = $this->form->createElement('static', "MAL_TABLE_LEVEL");
           $group[] = $this->form->createElement('static', "STATUS");
           $this->form->addGroup($group, 'score_header_group', null, $this->_GUIDelimiter, FALSE);
           unset($group);


           //score fields
           $domains = array("MBI"=> "<strong>Maladaptive Behaviour Index</strong>", "INT"=>"Internal", "EXT"=>"External", "OTH" => "Other");
           $columnHeaders = array("RAW" => "<strong>Raw Score</strong>", "VSCALE" => "<strong>v-Scale</strong>", 
           $percentile . "_CI" => "<strong>" . $percentile . " Confidence Interval</strong>", "ADAPT_LEVEL" => "<strong>Level</strong>", "STATUS" => "<strong>Status</strong>");
           
           foreach($columnHeaders as $field=>$label) {
                 $columnHeaders[$field] .= $this->indent;
             }
             
             
           foreach($domains as $field=>$label) {
               foreach($columnHeaders as $scoreField=>$scoreLabel) {
                  $group[] = $this->form->createElement('static', "{$field}_{$scoreField}");
               }
               $this->form->addGroup($group, "{$label}_group", $label, $this->_GUIDelimiter, FALSE);
               unset($group);
           }
         
         
      
         // add rules
         // parent report question
         if($this->getFieldValue("File_name")===false){
             $this->form->addRule("vineland_file", "Vineland file is required.", 'required', null, 'server');
         }
         // handedness questions

	   $this->form->addElement('static', null, "<br /><br />");
       $this->form->addElement("textarea", "other_comments", "Comments about Validity:", array('cols'=>25, 'rows'=>4));
       $this->XINRegisterRule("other_comments", array("{other_comments}{@}=={@}NEVER_REQUIRED"));


     } // end function _main
    
      function _page1(){
         $this->form->addElement('header', null, "Communication Domain Raw Data");
         $this->form->addElement('header', null, "Receptive");
         $this->form->addElement('header', null, "(2 = Usually, 1 = Sometimes, 0 = Never, D = Don't Know, N = No Opportunity)");

         for($i = 1; $i <= 20; $i++){
            $this->form->addElement('static', 'REC_ITEM_' . $i, '<strong>Question ' . $i . ':</strong>');
            $this->form->addElement('static', 'REC_CORRECTED_ITEM_' . $i, 'Corrected Value:');
         }
      }
    
      function _page2(){
         $this->form->addElement('header', null, "Communication Domain Raw Data");
         $this->form->addElement('header', null, "Expressive");
         $this->form->addElement('header', null, "(2 = Usually, 1 = Sometimes, 0 = Never, D = Don't Know, N = No Opportunity)");

         for($i = 1; $i <= 54; $i++){
            $this->form->addElement('static', 'EXP_ITEM_' . $i, '<strong>Question ' . $i . ':</strong>');
            $this->form->addElement('static', 'EXP_CORRECTED_ITEM_' . $i, 'Corrected Value:');
         }
      }
    
      function _page3(){
         $this->form->addElement('header', null, "Communication Domain Raw Data");
         $this->form->addElement('header', null, "Written");
         $this->form->addElement('header', null, "(2 = Usually, 1 = Sometimes, 0 = Never, D = Don't Know, N = No Opportunity)");

         for($i = 1; $i <= 25; $i++){
            $this->form->addElement('static', 'WRN_ITEM_' . $i, '<strong>Question ' . $i . ':</strong>');
            $this->form->addElement('static', 'WRN_CORRECTED_ITEM_' . $i, 'Corrected Value:');
         }
      }
    
      function _page4(){
         $this->form->addElement('header', null, "Daily Living Skills Domain Raw Data");
         $this->form->addElement('header', null, "Personal");
         $this->form->addElement('header', null, "(2 = Usually, 1 = Sometimes, 0 = Never, D = Don't Know, N = No Opportunity)");

         for($i = 1; $i <= 41; $i++){
            $this->form->addElement('static', 'PER_ITEM_' . $i, '<strong>Question ' . $i . ':</strong>');
            $this->form->addElement('static', 'PER_CORRECTED_ITEM_' . $i, 'Corrected Value:');
         }
      }
    
      function _page5(){
         $this->form->addElement('header', null, "Daily Living Skills Domain Raw Data");
         $this->form->addElement('header', null, "Domestic");
         $this->form->addElement('header', null, "(2 = Usually, 1 = Sometimes, 0 = Never, D = Don't Know, N = No Opportunity)");

         for($i = 1; $i <= 24; $i++){
            $this->form->addElement('static', 'DOM_ITEM_' . $i, '<strong>Question ' . $i . ':</strong>');
            $this->form->addElement('static', 'DOM_CORRECTED_ITEM_' . $i, 'Corrected Value:');
         }
      }
      
      function _page6(){
         $this->form->addElement('header', null, "Daily Living Skills Domain Raw Data");
         $this->form->addElement('header', null, "Community");
         $this->form->addElement('header', null, "(2 = Usually, 1 = Sometimes, 0 = Never, D = Don't Know, N = No Opportunity)");

         for($i = 1; $i <= 44; $i++){
            $this->form->addElement('static', 'CMM_ITEM_' . $i, '<strong>Question ' . $i . ':</strong>');
            $this->form->addElement('static', 'CMM_CORRECTED_ITEM_' . $i, 'Corrected Value:');
         }
      }
      
      function _page7(){
         $this->form->addElement('header', null, "Socialization Domain Raw Data");
         $this->form->addElement('header', null, "Interpersonal Relationships");
         $this->form->addElement('header', null, "(2 = Usually, 1 = Sometimes, 0 = Never, D = Don't Know, N = No Opportunity)");

         for($i = 1; $i <= 38; $i++){
            $this->form->addElement('static', 'IPR_ITEM_' . $i, '<strong>Question ' . $i . ':</strong>');
            $this->form->addElement('static', 'IPR_CORRECTED_ITEM_' . $i, 'Corrected Value:');
         }
      }
      
      function _page8(){
         $this->form->addElement('header', null, "Socialization Domain Raw Data");
         $this->form->addElement('header', null, "Play and Leisure Time");
         $this->form->addElement('header', null, "(2 = Usually, 1 = Sometimes, 0 = Never, D = Don't Know, N = No Opportunity)");

         for($i = 1; $i <= 31; $i++){
            $this->form->addElement('static', 'PL_ITEM_' . $i, '<strong>Question ' . $i . ':</strong>');
            $this->form->addElement('static', 'PL_CORRECTED_ITEM_' . $i, 'Corrected Value:');
         }
      }
      
      function _page9(){
         $this->form->addElement('header', null, "Socialization Domain Raw Data");
         $this->form->addElement('header', null, "Coping Skills");
         $this->form->addElement('header', null, "(2 = Usually, 1 = Sometimes, 0 = Never, D = Don't Know, N = No Opportunity)");

         for($i = 1; $i <= 30; $i++){
            $this->form->addElement('static', 'CS_ITEM_' . $i, '<strong>Question ' . $i . ':</strong>');
            $this->form->addElement('static', 'CS_CORRECTED_ITEM_' . $i, 'Corrected Value:');
         }
      }
      
      function _page10(){
         $this->form->addElement('header', null, "Motor Skills Domain Raw Data");
         $this->form->addElement('header', null, "Gross");
         $this->form->addElement('header', null, "(2 = Usually, 1 = Sometimes, 0 = Never, D = Don't Know, N = No Opportunity)");

         for($i = 1; $i <= 40; $i++){
            $this->form->addElement('static', 'GMS_ITEM_' . $i, '<strong>Question ' . $i . ':</strong>');
            $this->form->addElement('static', 'GMS_CORRECTED_ITEM_' . $i, 'Corrected Value:');
         }
      }
      
      function _page11(){
         $this->form->addElement('header', null, "Motor Skills Domain Raw Data");
         $this->form->addElement('header', null, "Fine");
         $this->form->addElement('header', null, "(2 = Usually, 1 = Sometimes, 0 = Never, D = Don't Know, N = No Opportunity)");

         for($i = 1; $i <= 36; $i++){
            $this->form->addElement('static', 'FMS_ITEM_' . $i, '<strong>Question ' . $i . ':</strong>');
            $this->form->addElement('static', 'FMS_CORRECTED_ITEM_' . $i, 'Corrected Value:');
         }
      }
      
      function _page12(){
         $this->form->addElement('header', null, "Maladaptive Behaviour Index Raw Data");
         $this->form->addElement('header', null, "Internalizing");
         $this->form->addElement('header', null, "(2 = Usually, 1 = Sometimes, 0 = Never)");

         for($i = 1; $i <= 11; $i++){
            $this->form->addElement('static', 'INT_ITEM_' . $i, '<strong>Question ' . $i . ':</strong>');
            $this->form->addElement('static', 'INT_CORRECTED_ITEM_' . $i, 'Corrected Value:');
         }
         
         $this->form->addElement('header', null, "Externalizing");
         $this->form->addElement('header', null, "(2 = Usually, 1 = Sometimes, 0 = Never)");
         for($i = 1; $i <= 10; $i++){
            $this->form->addElement('static', 'EXT_ITEM_' . $i, '<strong>Question ' . $i . ':</strong>');
            $this->form->addElement('static', 'EXT_CORRECTED_ITEM_' . $i, 'Corrected Value:');
         }
      }
      
      function _page13(){
         $this->form->addElement('header', null, "Maladaptive Behaviour Index Raw Data");
         $this->form->addElement('header', null, "Other");
         $this->form->addElement('header', null, "(2 = Usually, 1 = Sometimes, 0 = Never)");

         for($i = 1; $i <= 15; $i++){
            $this->form->addElement('static', 'OTH_ITEM_' . $i, '<strong>Question ' . $i . ':</strong>');
            $this->form->addElement('static', 'OTH_CORRECTED_ITEM_' . $i, 'Corrected Value:');
         }
      }
      
      function _page14(){
         $this->form->addElement('header', null, "Maladaptive Behaviour Index Raw Data");
         $this->form->addElement('header', null, "Critical Items");
         $this->form->addElement('header', null, "(2 = Usually, 1 = Sometimes, 0 = Never, S = Severe, M = Moderate)");

         for($i = 1; $i <= 14; $i++){
            $this->form->addElement('static', 'CRIT_ITEM_' . $i, '<strong>Question ' . $i . ':</strong>');
            $this->form->addElement('static', 'CRIT_SEVERITY_ITEM_' . $i, 'Severity:');
         }
      }
      
      function _page15(){
         $this->form->addElement('header', null, "General Information");
         $this->form->addElement('header', null, "Candidate Information");
         $this->form->addElement('static', "ETHNICITY", '<strong>Ethnicity:</strong>');
         $this->form->addElement('static', "IN_SCHOOL", '<strong>In School?:</strong>');
         $this->form->addElement('static', "SCHOOL", '<strong>School/Facility:</strong>');
         $this->form->addElement('static', "GRADE", '<strong>Grade:</strong>');
         $this->form->addElement('static', "DIAGNOSIS", '<strong>Diagnosis:</strong>');
         
         $this->form->addElement('header', null, "Respondent Information");
         $this->form->addElement('static', "RESPONDENT_SEX", '<strong>Sex:</strong>');
         $this->form->addElement('static', "RELATIONSHIP", '<strong>Relationship to Candidate:</strong>');
         
         $this->form->addElement('header', null, "Intelligence Test");
         $this->form->addElement('static', "INTEL_TEST_NAME", '<strong>Test Name:</strong>');
         $this->form->addElement('static', "INTEL_TEST_DATE", '<strong>Test Date:</strong>');
         $this->form->addElement('static', "INTEL_TEST_SCORE", '<strong>Test Score:</strong>');
      }
      
    
     // methods available to all children
      /**
       * preprocesses the array of values to be saved into the database
       * (such as to rearrange date fields)
       *
       * @param array $values      the array of values ready to be passed to
       * an Database::update call as the set array
       * @return void
       * @access private
       */
      function _saveValues($values)
      {
          $timepoint =& TimePoint::singleton($this->getSessionID());
          $candidate =& Candidate::singleton($timepoint->getCandID());

          if(isset($values['Date_taken'])) {
              $Date_taken = $values['Date_taken'];
              $values['Date_taken'] = sprintf("%04d-%02d-%02d", $Date_taken['Y'], $Date_taken['M'], $Date_taken['d']);
              $this->_saveCandidateAge($values);
          }

          require_once "File_Upload.class.inc";
          $file=new File_Upload;

          //pass the existing form ($form) by reference to File_Upload, and register the file_upload field names being used.
          $file->registerForm($this->form);

          //Tell File_Upload what file handlers to use.
          $file->setFileHandler("vineland_file", $this);
                    
          //Set the target directory that you want files moved into once they are validated and processed.
          $config = NDB_Config::singleton();
          $dir = $config->getSetting("UploadDir");
          if(empty($dir)) {
            $dir = ".";
          };
          $file->setBaseUploadDirectory($dir . "/vineland/");

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
          unset($values['candID'], $values['sessionID'], $values['commentID'], $values['test_name'], $values['page'], $values['fire_away'], $values['subtest'], $values['MAX_FILE_SIZE'], $values['vineland_file']);
          $this->_save($values);
      }

      /**
      * isValid checks the validity of the file.
      *
      * @param     string  $file    The full filename including directory.
      *
      * @return    bool    $success		if operation succeeded
      * @access    public
      */
      function isValid(&$file, $args){
         $correct_filename = strtolower($this->testName .'_'. $args['candID'] .'_'. $args['PSCID'] .'_'. $args['visitLabel'] . ".txt"); 
         if(strtolower($file->fileInfo['name']) != $correct_filename){
               $errors[]="Incorrect Filename: Filename should be: " . $correct_filename;
               return $errors;
           }

           $fp=fopen($file->fileInfo['tmp_name'], "r");
           $contents=fread($fp,filesize($file->fileInfo['tmp_name']));
           fclose($fp);
           
           $lines=explode("\n",$contents);
            $keys = explode("\t", $lines[0]);
            $vals = explode("\t", $lines[1]);
            for($i = 0; $i < count($keys); $i++){
                if (!empty($keys[$i]) && !preg_match("/^\s+$/", $keys[$i])){
                  $values[$keys[$i]] = $vals[$i];   
                }
             }

         if(count($values) != 1025){
            $errors[]="Incorrect number of columns in file: should be 1025, is " . count($values);
             return $errors;
         }
          
         $lname_value = strtolower($values['INDIVIDUAL_L']);
         if($lname_value == 'candidate'){
            $lname_value = 'subject';
         }
         if('vineland_' . $lname_value != $this->testName){
            $errors[]="Last name must be set to '" . substr($this->testName, -7, 7). "', was set to '" . $values['INDIVIDUAL_L'] . "'";
             return $errors;
         }
         
         $fname_value = strtolower($values['INDIVIDUAL_F']);
         $site = strtolower(substr($args['PSCID'], 0, 3));
         if($fname_value != $site){
            $errors[]="First name must be set to '" . $site . "', was set to '" . $fname_value . "'";
             return $errors;
         }
         
         $visit = strtolower($args['visitLabel']);
         if($visit == "6mo"){
            $visit = "v06";
         }else if($visit == "12m"){
            $visit = "v12";
         }else if($visit == "24m"){
            $visit = "v24";
         }else if($visit == "36m"){
             $visit = "v36";
         }else if($visit == "v37plus"){
              $visit = "v37";
         }
         
         $correct_id = $args['candID'] .'-'. substr($args['PSCID'], -4, 4) .'-'. substr($visit, -2, 2);
         if($values['INDIVIDUAL_ID'] != $correct_id){
            $errors[]="Id must be set to '" . $correct_id . "', was set to '" . $values['INDIVIDUAL_ID'] . "'";
             return $errors;
         }
            
         $values['TEST_DATE'] = $this->formatDate($values['TEST_DATE']);

         if(!empty($args['values']['Date_taken']) && !empty($values['TEST_DATE']) && ($args['values']['Date_taken'] != $values['TEST_DATE'])){
             $errors[]="Date of administration in the file ({$values['TEST_DATE']}) does not match the date of administration entered ({$args['values']['Date_taken']})." ;
             return $errors;
           }
           
           //Subdomains with base and ceiling some, but not all items must be filled in
           // $subdomains = array("REC"=>"Receptive", "EXP"=>"Expressive", "WRN"=>"Written",
           //                              "PER"=>"Personal", "DOM"=>"Domestic", "CMM"=>"Community",
           //                              "IPR"=>"Interpersonal Relationships", "PL"=>"Play and Leisure Time", "CS"=>"Coping Skills", 
           //                              "GMS"=>"Gross Motor Skills", "FMS"=>"Fine Motor Skills");
           //            $numQuestions = array("REC"=>20, "EXP"=>54, "WRN"=>25,
           //                                "PER"=> 41, "DOM"=>24, "CMM"=> 44,
           //                                "IPR"=>38, "PL"=>31, "CS"=>30, 
           //                                "GMS"=>40, "FMS"=>36);
           //          
           //          foreach($subdomains as $key=>$value){
           //             $no_entries = true;
           //             for($i = 1; $i <= $numQuestions[$key]; $i++){
           //                $item = $values[$key . '_ITEM_' . $i];
           //                if($item != null && $item != "" && $item != ' ' && $item != '-'  && $item != '_'){
           //                   $no_entries = false;
           //                }
           //             }
           //             if($no_entries){
           //                $errors[]="Individual items for subdomain '{$subdomains[$key]}' have not been filled out." ;
           //                return $errors;
           //             }
           //          }
           //          
           //          //Maladaptive domain: all items must be filled in (no base or ceiling)
           //          
           //          $subdomains = array("INT" => "Maladaptive Internalizing","EXT" => "Maladaptive Externalizing", 
           //                               "OTH" => "Maladaptive Other", "CRIT" => "Maladaptive Critical Items");
           //          $numQuestions = array("INT" => 11, "EXT" => 10, "OTH" => 15, "CRIT" => 14);
           //          
           //          foreach($subdomains as $key=>$value){
           //             for($i = 1; $i <= $numQuestions[$key]; $i++){
           //                $item = $values[$key . '_ITEM_' . $i];
           //                if($item == null || $item == "" || $item == ' ' || $item == '-' || $item == '_'){
           //                   $errors[]="Individual items for subdomain '{$subdomains[$key]}' have not been completed in full." ;
           //                   return $errors;
           //                }
           //             }
           //          }
           //          
           //          for($i = 1; $i <= 14; $i++){
           //             $item = $values['CRIT_SEVERITY_ITEM_' . $i];
           //             if($item == null || $item == ""  || $item == ' ' || $item == '-' || $item == '_'){
           //                $errors[]="Severity items for 'Maladaptive Critical Items' have not been completed in full." ;
           //                return $errors;
           //             }
           //          }
          return true;
      }

      /**
      * importFile imports the vineland file into the database.
      *
      * @param     object       $file    A reference to the file object (passed automatically by callFileHandler)
      * @param     assoc_array  $args    The arguments passed to the function they must be:
      *   -
      *
      * @return    bool    $success		if operation succeeded
      * @access    public
      */
      function importFile(&$file, $args){
          $fp=fopen($file->fileInfo['tmp_name'], "r");
          $contents=fread($fp,filesize($file->fileInfo['tmp_name']));
          fclose($fp);

          $values=array(
              'UserID'    =>$args['username'],
              'Status'    =>'assembly',
              'File_type' =>'vineland',
              'File_name' =>$file->getDestinationFilename(),
              'Data_dir'  =>$file->getDestinationDirectory()
          );


          //Cycle through the lines and extract the data
          $lines=explode("\n",$contents);
          $keys = explode("\t", $lines[0]);
          $vals = explode("\t", $lines[1]);
          for($i = 0; $i < count($keys); $i++){
             if (!empty($keys[$i]) && !preg_match("/^\s+$/", $keys[$i])){
               $values[$keys[$i]] = $vals[$i];   
             }
          }
          
          if(empty($values['ABC_95%_CI'])){
             $values['ABC_95%_CI'] = '';
          }
          
          if(empty($values['ABC_90%_CI'])){
              $values['ABC_90%_CI'] = '';
           }
           
           if(empty($values['ABC_85%_CI'])){
                $values['ABC_85%_CI'] = '';
            }
                    
          $values['TEST_DATE'] = $this->formatDate($values['TEST_DATE']);
          $values['BIRTH_DATE'] = $this->formatDate($values['BIRTH_DATE']);
          $values['INTEL_TEST_DATE'] = $this->formatDate($values['INTEL_TEST_DATE']);
                    
          unset($values['EXAMINER']);
          unset($values['TEST_DATE']);
          
          $db=& Database::singleton();

///Setting trackchanges to false because getting error messages
$db->_trackChanges = false;
////////////////////////////////////////////////////////////////

          $result = $db->update($this->testName, $values, array('CommentID'=>$args['CommentID']));
          return true;
      }

      function formatDate($date){
         if(empty($date)){
            return null;
         }
         $dateBits = explode('/', $date);
         return sprintf("%04d-%02d-%02d", $dateBits[2], $dateBits[0], $dateBits[1]); 
      }

      /**
      * getTargetDirectory retrieves info about where the file should be stored.
      *
      * The returned directory is ADDED to the baseUploadDirectory proprety.  It should have a trailing slash.
      *
      * @param     string  $file    The full filename including directory.
      *
      * @return    bool    $success		if operation succeeded
      * @access    public
      */
      function getTargetDirectory(&$file, $args){
          $output=$args['candID']."/";
          return $output;
      }

      function _setDefaultsArray($vals) {
          $vals['Date_taken_display'] = $vals['Date_taken'];
          return parent::_setDefaultsArray($vals);
      }
    /**
    * Constructs a section (page) of the instrument in a uniform fashion.
    *
    * @param string $prefix Prefix used to identify this section.
    * @param array $questionArray 0-based array containing the text of all section questions.
    * @param array $ageBreaks Suggested age-based start points. 
    * @param array $noOpp Questions where a `No Opportunity` option is presented.
    * @param array $not1 Questions that don't allow the `1) Sometimes` option.
    */
    function _generateSection($prefix, $questionArray, $ageBreaks, $noOpp, $not1) {
        foreach($questionArray as $number=>$label) {
            $answerArray = array(""=>NULL, "2_usually"=>"2) Usually", "1_sometimes"=>"1) Sometimes", "0_never"=>"0) Never", "dont_know"=>"Don't know", "not_answered"=>"Not Answered");
            //$questionArray is 0-indexed, so we add 1 to get the true question number
            if (array_key_exists($number + 1, $ageBreaks)) {
                $this->form->addElement("header", null, $ageBreaks[$number + 1] . " ->");
            }
            if(in_array($number + 1, $noOpp)) {
                $answerArray += array("no_opportunity"=>"No Opportunity");
            }
            if(in_array($number + 1, $not1)) {
                unset($answerArray["1_sometimes"]);
            }
            $this->form->addElement("select", $prefix . ($number + 1), $this->indent . $label, $answerArray);
            
            //Due to age of child, most questions will go unanswered.
            //For now, no question after the first page (except section comments) is required.
            $this->XINRegisterRule($prefix . ($number + 1), array("Examiner{@}=={@}Pee Wee Herman"));
        }

        $this->form->addElement("static", null, "&nbsp;");

        $group[]=&$this->form->createElement("textarea", "{$prefix}comments", null, array('cols'=>60, 'rows'=>6));
        $group[]=&$this->form->createElement("select", "{$prefix}comments" . "_status", "", array(NULL=>'', 'not_answered'=>'Not Answered'));
        $this->form->addGroup($group, "{$prefix}comments" . '_group', "Comments", null, false);
        unset($group);
        $rules_array=array("{$prefix}comments" . '_status{@}=={@}');
        $this->XINRegisterRule("{$prefix}comments", $rules_array, "Please record this section's comments, or mark it as 'Not Answered'.", "{$prefix}comments" . '_group');
    }

    // Based on Mia's vineland_NDAR script from Redmine ticket #2558, this
    // updates the ..._NDAR fields
    function setValueScore($item, $corritem) {
        $db =& Database::singleton();

        $ndar_item = $item . "_NDAR";
        $commentid = $this->getCommentID();

        $record = $db->pSelectRow("select $item, $corritem from " . $this->table . " WHERE CommentID=:cid", array('cid' => $commentid));

        if($record[$corritem] == "") {
            $setvalue = $record[$item];
            $success = $db->update($this->table, array($ndar_item=> $setvalue),
                array('CommentID' => $commentid)
            );
        } else {
            $setvalue = $record[$corritem];
        }
    }

    function scoreNDARGroup($qprefix, $qcorrprefix, $numq) {
        for($i = 1; $i < $numq; $i++) {
            $this->setValueScore($qprefix . $i, $qcorrprefix . $i);
        }
    }

    function score() {
        $sections = array(
            array('Name' => "REC", 'Items' => 21),
            array('Name' => "EXP", 'Items' => 55),
            array('Name' => "WRN", 'Items' => 26),
            array('Name' => "PER", 'Items' => 42),
            array('Name' => "DOM", 'Items' => 25),
            array('Name' => "CMM", 'Items' => 45),
            array('Name' => "IPR", 'Items' => 39),
            array('Name' => "PL", 'Items' => 32),
            array('Name' => "CS", 'Items' => 31),
            array('Name' => "GMS", 'Items' => 41),
            array('Name' => "FMS", 'Items' => 37),
            array('Name' => "INT", 'Items' => 12),
            array('Name' => "EXT", 'Items' => 11),
            array('Name' => "OTH", 'Items' => 16)
        );
        foreach($sections as $section) {
            $this->scoreNDARGroup($section['Name'] . "_ITEM_", 
                $section['Name'] . "_CORRECTED_ITEM_", 
                $section['Items']
            );
        }
    }
}
?>
