<?php
class NDB_BVL_Instrument_cbcl extends NDB_BVL_Instrument
{
    /**
    * sets up basic data, such as the HTML_Quickform object, and so on.
    *
    * @param string $commentID  the CommentID identifying the data to load
    * @param string $page       if a multipage form, the page to show
    * @return void
    * @access public
    */
    function setup($commentID, $page)
    {
        $this->form = new HTML_Quickform('test_form');
        $this->page = $page;            // page label (number or
        // string - used by
        // user-defined child classes)
        
        // set the object properties
        $this->testName = "cbcl";           // test_names.Test_name
        $this->table = 'cbcl';              // name of table containing
        // data keyed by commentID
        $this->commentID = $commentID;
        
        // Set the required fields array
        $this->_requiredElements=array("Date_taken","Examiner","File_prof");

        // setup the form
        $this->_setupForm();
    }
    
    
    
    
    /**
    * method to build the HTML_Quickform object into a complete handedness form
    *
    * @return void
    * @access private
    */
    function _setupForm()
    {
        
        // display test name
        $this->form->addElement('header', 'instrument_title', $this->getFullName());
        $this->form->updateAttributes(array('action'=>'main.php?test_name='.$_REQUEST['test_name'].'&candID='.$_REQUEST['candID'].'&sessionID='.$_REQUEST['sessionID'].'&commentID='.$this->getCommentID()));
        
        // add examiner & date of administration
        $this->_addMetadataFields();
        
        $this->form->addElement('file', 'cbclProfTxtFile', 'Upload the Prof Export cbcl file (.txt)');
        $this->form->addElement('file', 'cbclRawTxtFile', 'Upload the Raw Export cbcl file (.txt)');
        
        $this->form->addElement('static', "File_prof", "Uploaded Prof Export File (.txt)");
        $this->form->addElement('static', "File_raw", "Uploaded Raw Export File (.txt)");
        $this->form->addElement('static', "Sc1Name", "Sc1Name");
        $this->form->addElement('static', "Sc2Name", "Sc2Name");
        $this->form->addElement('static', "Sc3Name", "Sc3Name");
        $this->form->addElement('static', "Sc4Name", "Sc4Name");
        $this->form->addElement('static', "BPItems", "BPItems");
       
        // add rules
        if($this->getFieldValue("File_prof")===false){
            $this->form->addRule("cbclProfTxtFile", "profexport file is required.", 'required');
        }
        if($this->getFieldValue("File_raw")===false){
            $this->form->addRule("cbclRawTxtFile", "rawexport file is required.", 'required');
        }
        
    } // end function _setupForm
    
    
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
        }
        
        require_once "File_Upload.class.inc";
        $file=new File_Upload;
        
        //pass the existing form ($form) by reference to File_Upload, and register the file_upload field names being used.
        $file->registerForm($this->form);
        
        //Tell File_Upload what file handlers to use.
        $file->setFileHandler("cbclProfTxtFile", &$this, array("import"=>"importProfFile"));
        $file->setFileHandler("cbclRawTxtFile", &$this, array("import"=>"importRawFile"));
        
        //Set the target directory that you want files moved into once they are validated and processed.
        $file->setBaseUploadDirectory("./uploads");
        
        //Set the prefix to prepend to the filenames
        $file->setFilenamePrefix($timepoint->getVisitLabel()."-".$this->testName."-");
        
        //set the the IDs to the handler functions.
        $file->setHandlerArgs(array("CommentID"=>$this->getCommentID(),
                                    "candID"=>$candidate->getCandID(),
                                    "PSCID"=>$candidate->getPSCID(),
                                    "visitLabel"=>$timepoint->getVisitLabel(),
                                    "username"=>$_SESSION['State']->getUsername(),
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
        unset($values['candID'], $values['sessionID'], $values['commentID'], $values['test_name'], $values['page'], $values['fire_away'], $values['subtest'], $values['MAX_FILE_SIZE'], $values['cbclProfTxtFile'],$values['cbclRawTxtFile']);
        $this->_save($values);
    }
    
    
    
    /**
    * isValid checks the validity of the file.  It processes both Raw and Prof since the steps are mostly the same.
    *
    * @param     array  $args An array of arguments passed to the method by File_Upload.
    *
    * @return    bool    $success		if operation succeeded
    * @access    public
    */
    function isValid(&$file, $args){
        $fileInfo=$file->fileInfo;
        $fileType=$file->fieldName;
        if($fileType=="cbclProfTxtFile"){
            if((strtolower(substr($fileInfo['name'], -4))!=".txt") || (strpos($fileInfo['name'], '_profexport')===FALSE)){
                $errors[]="Incorrect Filename:  Filename should end in '_profexport.txt'";
                return $errors;
            }
        } else if ($fileType=="cbclRawTxtFile"){
            if((strtolower(substr($fileInfo['name'], -4))!=".txt") || (strpos($fileInfo['name'], '_rawexport')===FALSE)){
                $errors[]="Incorrect Filename:  Filename should  end in '_rawexport.txt'";
                return $errors;
            }
        } 
        
        $data = $this->getRelevantDataRow($fileInfo['tmp_name'], $args['candID'], $args['PSCID'], $args['visitLabel']);
        $rowCount=count($data);

        if(count($data)==0){
            $errors[]="Invalid File Format: ".$fileInfo['name']." must be exported such that fields are separated by commas (,) and enclosed by double quotes (\").  Please reexport and resend this data.";
            return $errors;
        }
        if(count($data)==1){
            $errors[]="Incorrect Identifiers:  Candidate ID and/or PSCID do not match  expected values.  Please correct IDs on this dataset, reexport and try again.";
            return $errors;
        }
        
        if($fileType=="cbclProfTxtFile"){ //Test Prof export Row count
            if($rowCount!=221 && $rowCount!=237 && $rowCount!=249){
                $errors[]="Invalid File Format: ".$fileInfo['name']." may be an unsuported version.  Versions supported are 2.0 - 4.0.  Please reexport and resend this data.";
                return $errors;
            }
        } else if ($fileType=="cbclRawTxtFile"){ //Test Raw export Row count
            if($rowCount!=59 && $rowCount!=65 && $rowCount!=69){
                $errors[]="Invalid File Format: ".$fileInfo['name']." may be an unsuported version.  Versions supported are 2.0 - 4.0.  Please reexport and resend this data.";
                return $errors;
            }
        }
        
        if($args['values']['Date_taken'] != $this->convertDate($data[15]) || $this->convertDate($data[15]) == '0000-00-00') {
            $errors[]="Date of administration in the file does not match the date of administration entered.";
            return $errors;
        }

        //NIHPD SPECIFIC!
        if(!($data[13]=='CBC' || $data[13]=='C15' || $data[13]=='YAS')){
            $errors[]="Unupported Test Type: Test type '$data[13]' not recognized";
        }
        
        
        if(empty($errors)){
            return true;
        } else {
            return $errors;
        }
    }
    
    
   /**
    * importProfFile imports the Prof file into the database.
    *
    * @param     array  $args An array of arguments passed to the method by File_Upload.
    *
    * @return    bool    $success		if operation succeeded
    * @access    public
    */
    
    function importProfFile(&$file, $args){

        $db =& Database::singleton();

        $fileInfo=$file->fileInfo;
        $data=$this->getRelevantDataRow($fileInfo['tmp_name'], $args['candID'], $args['PSCID'], $args['visitLabel']);
        //Get Version number
        switch(count($data)){
            case "248":
            $version=4;
            break;
            
            case "237":
            $version=3;
            break;
            
            case "221":
            $version=2;
            break;
        }
        
        //Assign the field values to the columns
        $values=array(
        'UserID'     => $args['username'],
        'Status'     => 'assembly',
        'File_type'  => 'cbcl',
        'File_name'  => $file->getDestinationFilename(),
        'Date_taken' => $this->convertDate($data[15]),
        'File_prof'  => $file->getDestinationFilename(),
        'Data_dir'   => $file->getDestinationDirectory(),
        
        'Formver'    => $data[9],
        'Dataver'    => $data[10],
        'Formno'     => $data[11],
        'Formid'     => $data[12],
        'Type'       => $data[13],
        'Enterdate'  => $this->convertDate($data[14]),
        'DFO'        => $this->convertDate($data[15]),
        'Age'        => $data[16],
        'Agemonths'  => $data[17],
        'Educcode'   => $data[18],
        'FOBcode'    => $data[19],
        'FOBgender'  => $data[20],
        'FParentses' => $data[21],
        'FSubjectses'=> $data[22],
        'FSpouseses' => $data[23],
        'Agencycode' => $data[24],
        'Clincode'   => $data[25],
        );
        
        //These fields have a variable index because the 4.0 file format includes 4 extra 'SubUse' fields.
        $x=26;  //The index of the first of the following data fields, which then follow sequentially.
        for($i=1;$i<=15;$i++){
            $values['Sc'.$i.'Name']=$data[$x];$x++;
            $values['Sc'.$i.'Raw']=$data[$x];$x++;
            $values['Sc'.$i.'t']=$data[$x];$x++;
            $values['Sc'.$i.'Clint']=$data[$x];$x++;
            $values['Sc'.$i.'Pct']=$data[$x];$x++;
        }
        for($i=1;$i<=8;$i++){
            $values['Icc'.$i]=$data[$x];$x++;
            $values['Icc'.$i.'Sig']=$data[$x];$x++;
        }
        for($i=1;$i<=4;$i++){
            $values['Comp'.$i.'Name']=$data[$x];$x++;
            $values['Comp'.$i.'Raw']=$data[$x];$x++;
            $values['Comp'.$i.'t']=$data[$x];$x++;
            $values['Comp'.$i.'Pct']=$data[$x];$x++;
        }
        for($i=1;$i<=6;$i++){
            $values['Adap'.$i.'Name']=$data[$x];$x++;
            $values['Adap'.$i.'Raw']=$data[$x];$x++;
            $values['Adap'.$i.'t']=$data[$x];$x++;
            $values['Adap'.$i.'Pct']=$data[$x];$x++;
        }
        for($i=1;$i<=4;$i++){
            if($version>=4){ // Fields only present in version 4 and up
            $values['Sub'.$i.'Name']=$data[$x];$x++;
            }
            $values['SubUse'.$i.'Raw']=$data[$x];$x++;
            $values['SubUse'.$i.'t']=$data[$x];$x++;
            $values['SubUse'.$i.'Pct']=$data[$x];$x++;
        }
        for($i=1;$i<=6;$i++){
            $values['CompAct'.$i]=$data[$x];$x++;
        }
        for($i=1;$i<=6;$i++){
            $values['CompSoc'.$i]=$data[$x];$x++;
        }
        for($i=1;$i<=4;$i++){
            $values['CompSch'.$i]=$data[$x];$x++;
        }
        for($i=1;$i<=8;$i++){
            $values['DSM'.$i.'Name']=$data[$x];$x++;
            $values['DSM'.$i.'Raw']=$data[$x];$x++;
            $values['DSM'.$i.'t']=$data[$x];$x++;
            $values['DSM'.$i.'Pct']=$data[$x];$x++;
        }
        
        $values['LDSal']=$data[$x]; $x++;
        $values['LDSalpct']=$data[$x]; $x++;
        $values['LDSvc']=$data[$x]; $x++;
        $values['LDSvcpct']=$data[$x]; $x++;
        
        if($version>=3){
            $values['Origin']=$data[$x]; $x++;
            $values['FUdefcode1']=$data[$x]; $x++;
            $values['FUdefcode2']=$data[$x]; $x++;
            $values['SUdefcode1']=$data[$x]; $x++;
            $values['Interviewr']=$data[$x]; $x++;
            $values['Rater']=$data[$x]; $x++;
            $values['Early']=$data[$x]; $x++;
            $values['WeeksEarly']=$data[$x]; $x++;
            $values['Weight']=$data[$x]; $x++;
            $values['Lb_Gram']=$data[$x]; $x++;
            $values['Infections']=$data[$x]; $x++;
            $values['NonEnglish']=$data[$x]; $x++;
            $values['SlowTalk']=$data[$x]; $x++;
            $values['Worried']=$data[$x]; $x++;
            $values['Spontan']=$data[$x]; $x++;
            $values['Combines']=$data[$x]; $x++;
        }
        if($version>=4){
            //Fields present in the 4.0 file format.
            $values['FacilityCo']=$data[$x]; $x++;
            $values['SchoolCode']=$data[$x]; $x++;
            $values['CTimeCode']=$data[$x]; $x++;
            $values['CTypeCode']=$data[$x]; $x++;
            $values['FStatus']=$data[$x]; $x++;
            $values['UserText']=$data[$x]; $x++;
            $values['SParentSES']=$data[$x]; $x++;
            $values['SSubjSES']=$data[$x]; $x++;
        }

        // find all the values = 9999, and set them to null
        foreach($values AS $key=>$val)
            if($val == 9999) $values[$key] = null;

        $result = $db->update('cbcl', $values, array('CommentID'=>$args['CommentID']));
        if($this->isError($result)) {
            print $result->getMessage();
            return $this->raiseError('Could not save to database');
        }
        
        return true;
    }
    
     /**
    * importRawFile imports the Raw file into the database.
    *
    * @param     array  $args An array of arguments passed to the method by File_Upload.
    *
    * @return    bool    $success		if operation succeeded
    * @access    public
    */
    
    function importRawFile(&$file, $args){
        
        $db =& Database::singleton();
        
        $fileInfo=$file->fileInfo;
        $data=$this->getRelevantDataRow($fileInfo['tmp_name'], $args['candID'], $args['PSCID'], $args['visitLabel']);
        
        //Get Version number
        switch(count($data)){
            case "69":
            $version=4;
            break;
            
            case "65":
            $version=3;
            break;
            
            case "59":
            $version=2;
            break;
        }

        $values=array(
            'UserID'    => $args['username'],
            'Status'    => 'assembly',
            'File_type' => 'cbcl',
            'File_raw'  => $file->getDestinationFilename(),
            'Data_dir'  => $file->getDestinationDirectory(),
            
            'Date_taken' => $this->convertDate($data[15]),
            'Formver' => $data[9],
            'Dataver' => $data[10],
            'Formno' => $data[11],
            'Formid' => $data[12],
            'Type' => $data[13],
            'Enterdate' => $this->convertDate($data[14]),
            'Dfo' => $this->convertDate($data[15]),
            'Age' => $data[16],
            'Agemonths' => $data[17],
            'Educcode' => $data[18],
            'Fobcode' => $data[19],
            'Fobgender' => $data[20],
            'FParentses' => $data[21],
            'FSubjectses' => $data[22],
            'FSpouseses' => $data[23],
            'Agencycode' => $data[24],
            'Clincode' => $data[25],
            'BPItems' => $data[26],
            'CompItems' => $data[27],
            'AFItems' => $data[28],
            'OtherItems' => $data[29],
            'Experience' => $data[30],
            'ScafItems' => $data[31],
            'FacilityCo' => $data[32],
            'NumChild' => $data[33],
            'Hours' => $data[34],
            'Months' => $data[35],
            'SchoolName' => $data[36],
            'SchoolCode' => $data[37],
            'Tobacco' => $data[38],
            'Drunk' => $data[39],
            'Drugs' => $data[40],
            'CTimeCode' => $data[41],
            'CTypeCode' => $data[42],
            'Early' => $data[43],
            'WeeksEarly' => $data[44],
            'Weight' => $data[45],
            'Lb_Gram' => $data[46],
            'Ounces' => $data[47],
            'Infections' => $data[48],
            'NonEnglish' => $data[49],
            'SlowTalk' => $data[50],
            'Worried' => $data[51],
            'Spontan' => $data[52],
            'Combines' => $data[53],
            'MLP' => $data[54],
            'Words162' => $data[55],
            'Words310' => $data[56],
            'OtherWords' => $data[57],
            'TotWords' => $data[58]
            );
            
        if($version>=3){
            $values['Origin'] = $data[59];
            $values['FUdefcode1'] = $data[60];
            $values['FUdefcode2'] = $data[61];
            $values['SUdefcode1'] = $data[62];
            $values['Interviewr'] = $data[63];
            $values['Rater'] = $data[64];
        }
        
        if($version>=4){
            $values['FStatus'] = $data[65];
            $values['UserText'] = $data[66];
            $values['SParentSES'] = $data[67];
            $values['SSubjSES'] = $data[68];
        }

        // find all the values = 9999, and set them to null
        foreach($values AS $key=>$val)
            if($val == 9999) $values[$key] = null;

        $result = $db->update('cbcl', $values, array('CommentID'=>$args['CommentID']));
        if($this->isError($result)) {
            print $result->getMessage();
            //return $this->raiseError('Could not save to database');
        }
               
        return true;
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
    
    
    /**
    * getRelevantDataRow retrieves the row from the CSV file which contains the right IDs
    *
    * @param     string  $filename The file to parse.
    * @param     string  $candID   Candidate ID.
    * @param     string  $PSCID    PSCID.
    * @param     string  $visitLabel  Visit Number.
    *
    * @return    array  The parsed row of $data
    * @access    public
    */
    function getRelevantDataRow($filename, $candID, $PSCID, $visitLabel){
        $fp=fopen($filename, "r");
        $data = array();
        while($row = fgetcsv($fp, 10000, ",", "\"")){
            $data[0]=1;
            if($row[1]==$candID && strtolower($row[2])==strtolower($PSCID) &&
               (strtolower($row[12])==strtolower($visitLabel))){
                $data=$row;
                break;
            }
        }
        fclose($fp);
        return $data;
    }
    
    /**
    * getFullADMTestName retrieves the full test name from the abbreviation
    *
    * @param     string  $abbrev    The abbreviated test name.
    *
    * @return    string  The full test name
    * @access    public
    */
    function getFullADMTestName($abbrev){
        $testTypes=array('T15'      => 'Caregiver Teacher Report (1:6-5:0)',
        'cbcl_15'  => 'Child Behaviour Checklist (1:6-5:0)',
        'C15'      => 'Child Behaviour Checklist (1:6-5:0)',
        'cbcl_418' => 'Child Behaviour Checklist (6y-18y)',
        'CBC'      => 'Child Behaviour Checklist (6y-18y)',
        'SIA'      => 'Semistructured Clinical Interview (6y-18y)',
        'TRF'      => 'Teacher\'s Report (6:0-18:0)',
        'YAB'      => 'Young Adult Behaviour Checklist',
        'cbcl_1821'=> 'Young Adult Self-Report',
        'YAS'      => 'Young Adult Self-Report',
        'YSR'      => 'Youth Self-Report',
        'T25'      => 'Caregiver Teacher Report (2:0-5:0)',
        'C23'      => 'Child behaviour Checklist (2:0-3:0)'
        );
        if(!empty($testTypes[$abbrev])){
            return $testTypes[$abbrev];
        } else {
            return "Unknown";
        }
    }


    /**
     * converts the date format in the CBCL data file to a YYYY-MM-DD format
     * @param  string   $fileDate   The date in the file.
     * @return string   The YYYY-MM-DD formatted date.
     */
    function convertDate($fileDate) {
        $bits = explode('/', $fileDate);
        $formattedFileDate = sprintf("%04d-%02d-%02d", $bits[2], $bits[0], $bits[1]);
        return $formattedFileDate;
    }

    /**
    * derives/lookups up scores supplied by the imported 'prof' file
    * @throws PEAR:Error
    */
    function score()
    {

        $db =& Database::singleton();

        $record = array();
        $query  = "SELECT
                   Sc1Name,Sc1Raw,Sc1t,Sc1Clint,Sc1Pct,Sc2Name,Sc2Raw,Sc2t,Sc2Clint,Sc2Pct,Sc3Name,Sc3Raw,Sc3t,Sc3Clint,Sc3Pct,Sc4Name,Sc4Raw,Sc4t,Sc4Clint,Sc4Pct,Sc5Name,Sc5Raw,Sc5t,Sc5Clint,Sc5Pct,Sc6Name,Sc6Raw,Sc6t,Sc6Clint,Sc6Pct,Sc7Name,Sc7Raw,Sc7t,Sc7Clint,Sc7Pct,Sc8Name,Sc8Raw,Sc8t,Sc8Clint,Sc8Pct,Sc9Name,Sc9Raw,Sc9t,Sc9Clint,Sc9Pct,Sc10Name,Sc10Raw,Sc10t,Sc10Clint,Sc10Pct,Sc11Name,Sc11Raw,Sc11t,Sc11Clint,Sc11Pct,Sc12Name,Sc12Raw,Sc12t,Sc12Clint,Sc12Pct,Sc13Name,Sc13Raw,Sc13t,Sc13Clint,Sc13Pct,Sc14Name,Sc14Raw,Sc14t,Sc14Clint,Sc14Pct,Sc15Name,Sc15Raw,Sc15t,Sc15Clint,Sc15Pct,
                   Comp1Name,Comp1Raw,Comp1t,Comp1Pct,Comp2Name,Comp2Raw,Comp2t,Comp2Pct,Comp3Name,Comp3Raw,Comp3t,Comp3Pct,Comp4Name,Comp4Raw,Comp4t,Comp4Pct,
                   Adap1Name,Adap1Raw,Adap1t,Adap1Pct,Adap2Name,Adap2Raw,Adap2t,Adap2Pct,Adap3Name,Adap3Raw,Adap3t,Adap3Pct,Adap4Name,Adap4Raw,Adap4t,Adap4Pct,Adap5Name,Adap5Raw,Adap5t,Adap5Pct,Adap6Name,Adap6Raw,Adap6t,Adap6Pct,
                   DSM1Name,DSM1Raw,DSM1T,DSM1Pct,DSM2Name,DSM2Raw,DSM2T,DSM2Pct,DSM3Name,DSM3Raw,DSM3T,DSM3Pct,DSM4Name,DSM4Raw,DSM4T,DSM4Pct,DSM5Name,DSM5Raw,DSM5T,DSM5Pct,DSM6Name,DSM6Raw,DSM6T,DSM6Pct,DSM7Name,DSM7Raw,DSM7T,DSM7Pct,DSM8Name,DSM8Raw,DSM8T,DSM8Pct
                   FROM cbcl WHERE CommentID = '".$this->commentID."'";
        $db->selectRow($query, $record);
        if (PEAR::isError($record)) {
            return PEAR::raiseError("Score(): DBError:".$record->getMessage());
        }

        // only score if Sc1Name is filled (ie, a prof file has been uploaded)
        if(empty($record['Sc1Name'])) return false;
        
        $setArray=array();

        // get SC Scores
        for($i=1; $i<=15; $i++) {

            if (empty($record["Sc".$i."Name"])) continue;

            // map section names
            if (Utility::in_array_insensitive($record["Sc".$i."Name"],array('AnxDep','AnxiousDepressed'))) {
                $section = 'anxiousdepressed';
            }
            elseif (Utility::in_array_insensitive($record["Sc".$i."Name"],array('Attention','AttentionProbs'))) {
                $section = 'attention';
            }
            else {
                // all other section don't have variations
                $section = strtolower($record["Sc".$i."Name"]);
            }

            $setArray["SC_".$section."_raw"] = $record["Sc".$i."Raw"];
            $setArray["SC_".$section."_t"] = $record["Sc".$i."t"];
            $setArray["SC_".$section."_clint"] = $record["Sc".$i."Clint"];
            $setArray["SC_".$section."_pct"] = $record["Sc".$i."Pct"];
        }

        // get COMP Scores
        for($i=1; $i<=4; $i++) {

            if (empty($record["Comp".$i."Name"])) continue;

            $section = strtolower($record["Comp".$i."Name"]);
            $setArray["COMP_".$section."_raw"] = $record["Comp".$i."Raw"];
            $setArray["COMP_".$section."_t"] = $record["Comp".$i."t"];
            $setArray["COMP_".$section."_pct"] = $record["Comp".$i."Pct"];
        }

        // get ADAPT Scores
        for($i=1; $i<=6; $i++) {

            if (empty($record["Adap".$i."Name"])) continue;

            $section = str_replace(' ','_',strtolower($record["Adap".$i."Name"]));
            $setArray["ADAPT_".$section."_raw"] = $record["Adap".$i."Raw"];
            $setArray["ADAPT_".$section."_t"] = $record["Adap".$i."t"];
            $setArray["ADAPT_".$section."_pct"] = $record["Adap".$i."Pct"];
        }

        // get DSM Scores
        for($i=1; $i<=8; $i++) {

            if (empty($record["DSM".$i."Name"])) continue;

            // map section names
            if (Utility::in_array_insensitive($record["DSM".$i."Name"],array('AffDisord','AffectiveDisorder'))) {
                $section = 'affective_disorder';
            }
            elseif (Utility::in_array_insensitive($record["DSM".$i."Name"],array('AnxDisord','AnxietyDisorder'))) {
                $section = 'anxiety_disorder';
            }
            elseif (Utility::in_array_insensitive($record["DSM".$i."Name"],array('Somaticpr'))) {
                $section = 'somatic_pr';
            }
            elseif (Utility::in_array_insensitive($record["DSM".$i."Name"],array('PervDev','PervasiveDevelopmental'))) {
                $section = 'pervasive_developmental';
            }
            elseif (Utility::in_array_insensitive($record["DSM".$i."Name"],array('Opposit','Oppositional'))) {
                $section = 'oppositional';
            }
            else {
                // adhd & conduct sections
                $section = strtolower($record["DSM".$i."Name"]);
            }

            $setArray["DSM_".$section."_raw"] = $record["DSM".$i."Raw"];
            $setArray["DSM_".$section."_t"] = $record["DSM".$i."T"];
            $setArray["DSM_".$section."_pct"] = $record["DSM".$i."Pct"];
        }

        if (count($setArray)>0) {
            $success = $db->update('cbcl', $setArray, array('CommentID'=>$this->commentID));
            if (PEAR::isError($success)) {
                return PEAR::raiseError("score_prof(): DB Update Error:".$success->getMessage());
            }
        }
        return true;
    } // end function
}
?>