<?php


require_once('RequiredIfGroup.inc');
require_once('RequiredIf.inc');
require_once 'HTML/QuickForm.php';
require_once 'HTML/QuickForm/Renderer/Array.php';

class NDB_BVL_Instrument_RSMS extends NDB_BVL_Instrument{
    var $ValidityEnabled = false;
    var $ValidityRequired = false;

	var $yesNo = array(null=>"", "Yes" =>"Yes", "No" =>"No", 333 => "Unknown", 999 =>"NA");	
	var $rate_rsm_array = array(null => "", 0 => "0", 1=>"1", 2 => "2", 3 =>"3+", "NA" => "NA");
    
    var $scoreCols = array ( 'q1_score', 'q2_score', 'q1_2_score', 'q3_score', 'q4_score', 'q3_4_score');

	/*
	INSERT INTO test_names VALUES ('', 'RSMS', 'Repetitive and Stereotyped Movement Scales: Scoring Worksheet', '0', '1');
	INSERT INTO instrument_subtests VALUES('', 'RSMS', 'RSMS_page1', 'Repetitive and Stereotyped Movement Scales', 1);
	INSERT INTO test_battery VALUES ('', 'RSMS', '120', '1440', 'Y', 'Visit', '1');

	*/

	/**
	 * Array of column names to be ignored by the double data entry conflict detector.
	 */
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
		$this->testName = "RSMS";           // test_names.Test_name
		$this->table = 'RSMS';              // name of database table corresponding to instrument
		// data keyed by commentID
		$this->commentID = $commentID;

		//The array of dates/timestamps to convert to database dates/timestamps
		//Any HTML_Quickform date elements must be listed here
		$this->dateTimeFields=array("Date_taken");

		// required fields for data entry completion status
		$this->_requiredElements = array('Examiner', 'Date_taken');
        $this->_doubleDataEntryDiffIgnoreColumns = array('CommentID', 'UserID', 'Testdate', 'Window_Difference',
                                                        'Candidate_Age','Data_entry_completion_status', 'q1_score',
                                                         'q1_score_weighted',
                                                         'q2_score',
                                                         'q1_2_score',
                                                         'q3_score',
                                                         'q3_score_weighted',
                                                         'q4_score',
                                                         'q3_4_score',
                                                         'q1_3_score');	
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
	       if(preg_match("/RSMS(_page[0-9]+)/",$this->page,$matches)){
                call_user_method($matches[1], $this);
            } else {
                $this->_main();
            }

		//Defines the call back function for HTML Quickform to use when validating the form.
		$this->form->addFormRule(array(&$this,'XINValidate'));
    
	}

    /**
    * generates an array of numbers from min to max, with 
    * a blank and an N/A option suitable for passing to a 
    * quickform select dropdown
    *
    * @return array
    * @access private
    */
    function _generateNumbers($min, $max) {
        $options = array('' => null);
        foreach (range($min, $max) as $i) {
            if($i == ($max)) {
                $options[$i] = $i + '+';
            } else {
                $options[$i] = $i;
            }
        }
        $options['NA'] = 'NA';
        return $options;

    }
	/**
    * generates the main page of the form.
    *
    * @return void
    * @access private
    *
    */
	function _main(){
		// display test name
		$this->form->addElement('header', 'instrument_title', "Repetitive and Stereotyped Movement Scales: Scoring Worksheet");

		// automatically adds examiner & date of administration
		$this->_addMetadataFields();
		
    	$config =& NDB_Config::singleton();
        
        $this->dateOptions = array(
            'language' => 'en',
            'format'   => 'YMd',
            'minYear'  => $config->getSetting('startYear') -80, //allows for siblings up to 20 years older than candidate
            'maxYear'  => $config->getSetting('endYear'),
            'addEmptyOption' => true,
            'emptyOptionValue' => null
    	);

        $this->form->addElement('select', 'total_time_assessment', 'Total time of assessment in minutes', $this->_generateNumbers(5, 60));
        $this->form->addElement('select', 'total_play_time', 'Total play time (item 6) in minutes', $this->_generateNumbers(1, 15));
        $this->form->addElement('select', 'toys_displayed', 'Toys displayed during play time (item 6)', array(null => '', 'half' => 'Half set of toys', 'full' => 'Full set of toys'));
   
    }
        
    function _page1(){
    
    
     	$this->form->addElement ( "static", null, "<b>Repetitive and Stereotyped Movements <br>(score during opportunities 1 to 6)<b>" );
	    $this->form->addElement ( "static", null, "<BR>" ); //line space
    
    	
        $sample_num = array (1 => "1", 2 => "2", 3 => "3", 4 => "4", 5 => "5", 6 => "6");
        
        $activities = array("windup" => "Windup Toy", "balloon" => "Balloon", "bubbles" => "Bubbles","jar" => "Jar", "books" => "Books", "play" => "Play");
        $yesNo = array(null => "", "0" => "No", "1" => "Yes", "NA"=>"NA" );
        $sample_choices = array(null=> "", "Sample Taken", "NA" => "NA" );
        $this->form->addElement("static", null, "Repetitive Movements or Posturing of Body, <br> Arms, Hands, or Fingers (RSM with Body)<br>");

        if (isset($_REQUEST['commentID'])) { 
            for($int=1; $int<=6; $int++){
                $group[] = &$this->form->createElement("static", "sample_body_static" . $int, "", $int);    
                if($int > 1){
                    $group[] = $this->form->createElement("static", null, $this->indent);
                }  
            }
        }
        
        $this->form->addGroup($group, null, "Sampling Opportunity", $this->_GUIDelimiter, false);
        unset($group);
        
        reset($activities);  
        
        $int =1;
        while ( list ( $field, $label ) = each ( $activities ) ) {
            $group[] = &$this->form->createElement("static", "sample_body_static" . $int, null, $label);
            if($int > 1){
                $group[] = $this->form->createElement("static", null, $this->indent);
            }
            $int++;
        }
        
        $this->form->addGroup($group, null, "", $this->_GUIDelimiter, false);
        unset($group);
        
 
        // Generate array of 0-20
        $options = $this->_generateNumbers(0, 20);

        $group[]=&$this->form->createElement("select", "q1_rate_body_1", null, $options);
        $group[]=&$this->form->createElement("select", "q1_rate_body_2", null, $options);
        $group[] = $this->form->createElement("static", null, $this->indent);
        $group[]=&$this->form->createElement("select", "q1_rate_body_3", null, $options);
        $group[] = $this->form->createElement("static", null, $this->indent);
        $group[]=&$this->form->createElement("select", "q1_rate_body_4", null, $options);
        $group[] = $this->form->createElement("static", null, $this->indent);
        $group[]=&$this->form->createElement("select", "q1_rate_body_5", null, $options);
        $group[] = $this->form->createElement("static", null, $this->indent);
        $group[]=&$this->form->createElement("select", "q1_rate_body_6", null, $options);
               
        $this->form->addGroup($group, "1_rate_body_group", "1. Rate of RSM with Body", $this->_GUIDelimiter, false);
               
        $this->XINRegisterRule("q1_rate_body_1", array("q1_rate_body_1{@}=={@}"), "Required", '1_rate_body_group');               
        $this->XINRegisterRule("q1_rate_body_2", array("q1_rate_body_2{@}=={@}"), "Required", '1_rate_body_group');
        $this->XINRegisterRule("q1_rate_body_3", array("q1_rate_body_3{@}=={@}"), "Required", '1_rate_body_group');
        $this->XINRegisterRule("q1_rate_body_4", array("q1_rate_body_4{@}=={@}"), "Required", '1_rate_body_group');
        $this->XINRegisterRule("q1_rate_body_5", array("q1_rate_body_5{@}=={@}"), "Required", '1_rate_body_group');
        $this->XINRegisterRule("q1_rate_body_6", array("q1_rate_body_6{@}=={@}"), "Required", '1_rate_body_group');
               
        unset($group);

       $this->XINRegisterRule ( "q1_score", array ("q1_score{@}=={@}never_required"), "Not required" );
            
       $this->form->addElement("static", null, "2. Inventory of RSM with Body<br> (check all that apply)");
       
       $options40 = $this->_generateNumbers(0, 40);
       $group[] = &$this->form->createElement("advcheckbox", "q2_inv_body_flaps", null, null, null, array("no", "yes"));
       $group[] = &$this->form->createElement("select", "q2_inv_body_flaps_number", "Number of times", $options40);
       $this->XINRegisterRule ("q2_inv_body_flaps", array ("q2_inv_body_flaps{@}=={@}never_required"), "Not required" );
       $this->XINRegisterRule ("q2_inv_body_flaps_number", array ("q2_inv_body_flaps_number{@}=={@}never_required"), "Not required" );
       $this->form->addGroup($group, null, "Flaps arms or hands", $this->_GUIDelimiter, false);  
       unset($group);
       
       $group[] = &$this->form->createElement("advcheckbox", "q2_inv_body_pats", null, null, null, array("no", "yes"));
       $group[] = &$this->form->createElement("select", "q2_inv_body_pats_number", "Number of times", $options40);
       $this->XINRegisterRule ("q2_inv_body_pats", array ("q2_inv_body_pats{@}=={@}never_required"), "Not required" );
       $this->XINRegisterRule ("q2_inv_body_pats_number", array ("q2_inv_body_pats_number{@}=={@}never_required"), "Not required" );
       $this->form->addGroup($group, null, "Pats, taps or presses body part", $this->_GUIDelimiter, false);
       unset($group);
       
       $group[] = &$this->form->createElement("advcheckbox", "q2_inv_body_rubs", null, null, null, array("no", "yes"));
       $group[] = &$this->form->createElement("select", "q2_inv_body_rubs_number", "Number of times", $options40);
       $this->XINRegisterRule ("q2_inv_body_rubs", array ("q2_inv_body_rubs{@}=={@}never_required"), "Not required" );
       $this->XINRegisterRule ("q2_inv_body_rubs_number", array ("q2_inv_body_rubs_number{@}=={@}never_required"), "Not required" );
       $this->form->addGroup($group, null, "Rubs body part", $this->_GUIDelimiter, false);
       unset($group);
       
       $group[] = &$this->form->createElement("advcheckbox", "q2_inv_body_stiffens", null, null, null, array("no", "yes"));
       $group[] = &$this->form->createElement("select", "q2_inv_body_stiffens_number", "Number of times", $options40);
       $this->XINRegisterRule ("q2_inv_body_stiffens", array ("q2_inv_body_stiffens{@}=={@}never_required"), "Not required" );  
       $this->XINRegisterRule ("q2_inv_body_stiffens_number", array ("q2_inv_body_stiffens_number{@}=={@}never_required"), "Not required" );
       $this->form->addGroup($group, null, "Stiffens fingers, hands, or arms", $this->_GUIDelimiter, false);
       unset($group);
        
       $this->form->addElement ( 'static', null, "<BR><b>Weighted Raw Score</b>");
     
       $this->form->addElement("static", "q1_score_weighted", "Scale 1 &divide 3", array('size'=> 2));
       $this->XINRegisterRule ( "q1_score_weighted", array ("q1_score_weighted{@}=={@}never_required"), "Not required" );
     
       $this->form->addElement("static", "q2_score", "Scale 2", array('size'=> 2));
   	   $this->XINRegisterRule ( "q2_score", array ("q2_score{@}=={@}never_required"), "Not required" );
       
       $this->form->addElement("static", "q1_2_score", "Total", array('size'=> 2));
       $this->XINRegisterRule ( "q1_2_score", array ("q1_2_score{@}=={@}never_required"), "Not required" );
        
        /* repetitive or Stereotyped Movements with Objects (RS< with Objects) */     
     
        $this->form->addElement("static", null, "<BR><b>Repetitive or Stereotyped Movements <br> with Objects (RSM with Objects)");
                
        for($int=1; $int<=6; $int++){
            $group[] = &$this->form->createElement("static", "q3_rate_object_static" . $int, "", "$int");
            if($int > 1){
                $group[] = &$this->form->createElement("static", null, $this->indent);
            }      
        }
           
        $this->form->addGroup($group, null, "<br>Sampling Opportunity", $this->_GUIDelimiter, false);
        unset($group);
        
        
        $int=1;
        reset($activities);  
        while ( list ( $field, $label ) = each ( $activities ) ) {
            ///fix me!
            $group[] = $this->form->createElement("static", null, "q3_rate_object_static" . $int, $label); 
            if($int > 1){
                $group[] = $this->form->createElement("static", null, $this->indent);
            }
            $int++;
        }
        
        $this->form->addGroup($group, "rate_object_static", "", $this->_GUIDelimiter, false);
        unset($group);
        
        
        $rate_object = "q3_rate_object_";
        $int= 1;
          
        $group[]=&$this->form->createElement("select", "q3_rate_object_1", null,$options);
        $group[]=&$this->form->createElement("select", "q3_rate_object_2", null, $options);
        $group[] = $this->form->createElement("static", null, $this->indent);
        $group[]=&$this->form->createElement("select", "q3_rate_object_3", null,$options);
        $group[] = $this->form->createElement("static", null, $this->indent);
        $group[]=&$this->form->createElement("select", "q3_rate_object_4", null,$options);
        $group[] = $this->form->createElement("static", null, $this->indent);
        $group[]=&$this->form->createElement("select", "q3_rate_object_5", null,$options);
        $group[] = $this->form->createElement("static", null, $this->indent);
        $group[]=&$this->form->createElement("select", "q3_rate_object_6", null,$options);

        $this->form->addGroup($group, "3_rate_object_group", "3. Rate of RSM with Objects", $this->_GUIDelimiter, false); 
        $this->XINRegisterRule("q3_rate_object_1", array("q3_rate_object_1{@}=={@}"), "Required", '3_rate_object_group');               
        $this->XINRegisterRule("q3_rate_object_2", array("q3_rate_object_2{@}=={@}"), "Required", '3_rate_object_group');
        $this->XINRegisterRule("q3_rate_object_3", array("q3_rate_object_3{@}=={@}"), "Required", '3_rate_object_group');
        $this->XINRegisterRule("q3_rate_object_4", array("q3_rate_object_4{@}=={@}"), "Required", '3_rate_object_group');
        $this->XINRegisterRule("q3_rate_object_5", array("q3_rate_object_5{@}=={@}"), "Required", '3_rate_object_group');
        $this->XINRegisterRule("q3_rate_object_6", array("q3_rate_object_6{@}=={@}"), "Required", '3_rate_object_group');

        unset($group);  
                             

        $this->form->addElement("static", null, "4. Inventory of RSM with Objects<br> (check all that apply)");
        
        $this->form->addElement("static", null, "<br/>4a. Restricted: Preoccupation in Intensity <br/> or Focus with Restricted Interest<br/>");
       
       $options40 = $this->_generateNumbers(0, 40);
        $group[] = &$this->form->createElement("advcheckbox", "q4a_inv_object_swipes", null, null, null, array("no", "yes"));
        $group[] = &$this->form->createElement("select", "q4a_inv_object_swipes_number", "Number of times", $options40);
        $this->XINRegisterRule ("q4a_inv_object_swipes_number", array ("q4a_inv_object_swipes_number{@}=={@}never_required"), "Not required" );  
        $this->XINRegisterRule ("q4a_inv_object_swipes", array ("q4a_inv_object_swipes{@}=={@}never_required"), "Not required" );  
        $this->form->addGroup($group, null, "Swipes object away", $this->_GUIDelimiter, false);
        unset($group);

        $group[] = &$this->form->createElement("advcheckbox", "q4a_inv_object_rubs", null, null, null, array("no", "yes"));
        $group[] = &$this->form->createElement("select", "q4a_inv_object_rubs_number", "Number of times", $options40);
        $this->XINRegisterRule ("q4a_inv_object_rubs_number", array ("q4a_inv_object_rubs_number{@}=={@}never_required"), "Not required" );  
        $this->XINRegisterRule ("q4a_inv_object_rubs", array ("q4a_inv_object_rubs{@}=={@}never_required"), "Not required" );  
        $this->form->addGroup($group, null, "Rubs or squeezes object", $this->_GUIDelimiter, false);
        unset($group);

        $group[] = &$this->form->createElement("advcheckbox", "q4a_inv_object_rolls", null, null, null, array("no", "yes"));
        $group[] = &$this->form->createElement("select", "q4a_inv_object_rolls_number", "Number of times", $options40);
        $this->XINRegisterRule ("q4a_inv_object_rolls_number", array ("q4a_inv_object_rolls_number{@}=={@}never_required"), "Not required" );  
        $this->XINRegisterRule ("q4a_inv_object_rolls", array ("q4a_inv_object_rolls{@}=={@}never_required"), "Not required" );  
        $this->form->addGroup($group, null, "Rolls or knocks over object", $this->_GUIDelimiter, false);
        unset($group);

        $group[] = &$this->form->createElement("advcheckbox", "q4a_inv_object_rocks", null, null, null, array("no", "yes"));
        $group[] = &$this->form->createElement("select", "q4a_inv_object_rocks_number", "Number of times", $options40);
        $this->XINRegisterRule ("q4a_inv_object_rocks_number", array ("q4a_inv_object_rocks_number{@}=={@}never_required"), "Not required" );  
        $this->XINRegisterRule ("q4a_inv_object_rocks", array ("q4a_inv_object_rocks{@}=={@}never_required"), "Not required" );  
        $this->form->addGroup($group, null, "Rocks, flips, turns over, or flicks object", $this->_GUIDelimiter, false);
        unset($group);

        $group[] = &$this->form->createElement("advcheckbox", "q4a_inv_object_spins", null, null, null, array("no", "yes"));
        $group[] = &$this->form->createElement("select", "q4a_inv_object_spins_number", "Number of times", $options40);
        $this->XINRegisterRule ("q4a_inv_object_spins_number", array ("q4a_inv_object_spins_number{@}=={@}never_required"), "Not required" );  
        $this->XINRegisterRule ("q4a_inv_object_spins", array ("q4a_inv_object_spins{@}=={@}never_required"), "Not required" );  
        $this->form->addGroup($group, null, "Spins or wobbles object", $this->_GUIDelimiter, false);
        unset($group);
         
        $this->form->addElement("static", null, "<br/>4b. Sameness: Insistence on Sameness <br/> or Difficulty with Change in Activity<br/>");
        
        $group[] = &$this->form->createElement("advcheckbox", "q4b_inv_object_collects", null, null, null, array("no", "yes"));
        $group[] = &$this->form->createElement("select", "q4b_inv_object_collects_number", "Number of times", $options40);
        $this->XINRegisterRule ("q4b_inv_object_collects_number", array ("q4b_inv_object_collects_number{@}=={@}never_required"), "Not required" );  
        $this->XINRegisterRule ("q4b_inv_object_collects", array ("q4b_inv_object_collects{@}=={@}never_required"), "Not required" );  
        $this->form->addGroup($group, null, "Collects objects", $this->_GUIDelimiter, false);
        unset($group);

        $group[] = &$this->form->createElement("advcheckbox", "q4b_inv_object_moves", null, null, null, array("no", "yes"));
        $this->XINRegisterRule ("q4b_inv_object_moves", array ("q4b_inv_object_moves{@}=={@}never_required"), "Not required" );  
        $group[] = &$this->form->createElement("select", "q4b_inv_object_moves_number", "Number of times", $options40);
        $this->XINRegisterRule ("q4b_inv_object_moves_number", array ("q4b_inv_object_moves_number{@}=={@}never_required"), "Not required" );  
        $this->form->addGroup($group, null, "Moves or places objects to one location", $this->_GUIDelimiter, false);
        unset($group);

        $group[] = &$this->form->createElement("advcheckbox", "q4b_inv_object_lines", null, null, null, array("no", "yes"));
        $this->XINRegisterRule ("q4b_inv_object_lines", array ("q4b_inv_object_lines{@}=={@}never_required"), "Not required" );  
        $group[] = &$this->form->createElement("select", "q4b_inv_object_lines_number", "Number of times", $options40);
        $this->XINRegisterRule ("q4b_inv_object_lines_number", array ("q4b_inv_object_lines_number{@}=={@}never_required"), "Not required" );  
        $this->form->addGroup($group, null, "Lines up or stacks objects", $this->_GUIDelimiter, false);
        unset($group);

        $group[] = &$this->form->createElement("advcheckbox", "q4b_inv_object_clutches", null, null, null, array("no", "yes"));
        $this->XINRegisterRule ("q4b_inv_object_clutches", array ("q4b_inv_object_clutches{@}=={@}never_required"), "Not required" );  
        $group[] = &$this->form->createElement("select", "q4b_inv_object_clutches_number", "Number of times", $options40);
        $this->XINRegisterRule ("q4b_inv_object_clutches_number", array ("q4b_inv_object_clutches_number{@}=={@}never_required"), "Not required" );  
        $this->form->addGroup($group, null, "Clutches object<BR><BR>", $this->_GUIDelimiter, false);
        unset($group);


        $this->form->addElement ( 'static', null, "<BR><b>Weighted Raw Score</b>");

       $this->form->addElement("static", "q3_score_weighted", "Scale 3 &divide 3", array('size'=> 2));
       $this->XINRegisterRule ( "q3_score", array ("q3_score{@}=={@}never_required"), "Not required" );

       $this->form->addElement("static", "q4_score", "Scale 4", array('size'=> 2));
       $this->XINRegisterRule ( "q4_score", array ("q4_score{@}=={@}never_required"), "Not required" );

       $this->form->addElement("static", "q3_4_score", "Total", array('size'=> 2));
       $this->XINRegisterRule ( "q3_4_score", array ("q3_4_score{@}=={@}never_required"), "Not required" );
        
        $this->form->addElement ('static', null, "<BR><b>Total Scores</b>");
        $this->form->addElement("static", "q1_score", "Total RSM With Body"); 
        $this->form->addElement("static", "q3_score", "Total RSM With Objects");
        $this->form->addElement("static", "q1_3_score", "Total RSM");
        }
    
        
        function score() {
            if($this->_determineDataEntryCompletionStatus() == "Incomplete") {
                return;
            }
            $this->_nullScores($this->scoreCols);

   
            // Get the item scores
            $array_of_conversion=array();

            $db =& Database::singleton();

            $query = "SELECT * FROM ".$this->table." WHERE CommentID='".$this->getCommentID()."'";

            //select the row with the commentID of the row where the information is being taken
            $db->selectRow($query, $result);

                        
            $score1 =0;
            $score1_weighted = 0;
            for($int = 1; $int <= 6; $int ++){
                $field = $result['q1_rate_body_'.$int];
                 if($field!="NA"){
                     $score1 = $score1 + $field;
                     if($field <= 3) {
                        $score1_weighted = $score1_weighted + $field;
                     } else {
                        $score1_weighted += 3;
                     }
                 }
            }
           
            
            $newValues["q1_score"] = $score1;
            $newValues["q1_score_weighted"] = round($score1_weighted/3, 2);
            
                    
            $score2 = 0;
            if($result["q2_inv_body_flaps"] == "yes"){
                $score2++;
            }
            if($result["q2_inv_body_pats"]=="yes"){
                $score2++;
            }
            if($result["q2_inv_body_rubs"]=="yes"){
                $score2++;
            }
            if($result["q2_inv_body_stiffens"]=="yes"){
                $score2++;
            }
            
            $newValues["q2_score"] = $score2;
            
            $newValues["q1_2_score"] = $newValues["q1_score_weighted"] + $score2;
            
            
            $score3=0;
            $score3_weighted=0;
            for($int = 1; $int <= 6; $int ++){
                 $field = $result['q3_rate_object_'.$int];
                 if($field!="NA"){
                    $score3 = $score3 + $field;
                     if($field <= 3) {
                        $score3_weighted = $score3_weighted + $field;
                     } else {
                        $score3_weighted += 3;
                     }
                 }
            }
            
            
            $newValues["q3_score"] = round($score3, 2);
            $newValues["q3_score_weighted"] = round($score3_weighted/3, 2);
            $newValues["q1_3_score"] = $score1 + $score3;
            
            $score4a =0;
                    
            if($result["q4a_inv_object_swipes"] == "yes"){
                $score4a++;
            }            
            
            if($result["q4a_inv_object_rubs"] == "yes"){
                $score4a++;
            }
            
            if($result["q4a_inv_object_rolls"] == "yes"){
                $score4a++;
            }
            
           if($result["q4a_inv_object_rocks"]=="yes"){
               $score4a++;
           }
           
           if($result["q4a_inv_object_spins"]=="yes"){
               $score4a++;
           }
            
       
           $score4b=0;
           
           if($result["q4b_inv_object_collects"]=="yes"){
                $score4b++;
                
            }
            if($result["q4b_inv_object_moves"]=="yes"){
                $score4b++;
            }
            
            if($result["q4b_inv_object_lines"]=="yes"){
                $score4b++;
            }
            
            if($result["q4b_inv_object_clutches"]=="yes"){
                $score4b++;
            }
            
            $newValues["q4_score"] = $score4a + $score4b;   
            
            $newValues["q3_4_score"] = $newValues["q3_score_weighted"] + $score4a + $score4b;     
        
             $result = $db->update($this->table, $newValues, array('CommentID' => $this->getCommentID()));
                
        }

    	
    }
