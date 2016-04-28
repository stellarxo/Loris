<?php

require_once 'HTML/QuickForm.php';
require_once 'HTML/QuickForm/Renderer/Array.php';

class NDB_BVL_Instrument_ados_module1 extends NDB_BVL_Instrument
{
/*
    INSERT INTO test_names VALUES ('', 'ados_module1', 'ADOS Module 1', '0', '1');

    INSERT INTO instrument_subtests VALUES('', 'ados_module1', 'ados_module1_page1', 'Sections A-B', 1);
    INSERT INTO instrument_subtests VALUES('', 'ados_module1', 'ados_module1_page2', 'Sections C-E', 2);

    INSERT INTO test_battery (Test_name,AgeMinDays,AgeMaxDays, Active, Stage, SubprojectID) VALUES ("ados_module1", "660", "780","Y","Visit","1");
    INSERT INTO test_battery (Test_name,AgeMinDays,AgeMaxDays, Active, Stage, SubprojectID) VALUES ("ados_module1", "660", "780","Y","Visit","2");
    INSERT INTO test_battery (Test_name,AgeMinDays,AgeMaxDays, Active, Stage, SubprojectID) VALUES ("ados_module1", "660", "780","Y","Visit","3");
*/
    var $option01238 = array(""=>NULL, 0=>0, 1=>1, 2=>2, 3=>3, 8=>8, "not_answered"=>"Not Answered");
    var $option0128 = array(""=>NULL, 0=>0, 1=>1, 2=>2, 8=>8, "not_answered"=>"Not Answered");
    var $option0123 = array(""=>NULL, 0=>0, 1=>1, 2=>2, 3=>3, "not_answered"=>"Not Answered");
    var $option02 = array(""=>NULL, 0=>0, 2=>2, "not_answered"=>"Not Answered");
    var $option012 = array(""=>NULL, 0=>0, 1=>1, 2=>2, "not_answered"=>"Not Answered");
    var $option0127 = array(""=>NULL, 0=>0, 1=>1, 2=>2, 7=>7, "not_answered"=>"Not Answered");

    var $scoreCols = array("social_affect_total", "restricted_repetitive_behavior_total", "social_affect_restricted_repetitive_behavior_total", "ADOS_classification",
                             'a2_weighted',
                             'a3_weighted',
                             'a8_weighted',
                             'b1_weighted',
                             'b3_weighted',
                             'b4_weighted',
                             'b5_weighted',
                             'b9_weighted',
                             'b10_weighted',
                             'b11_weighted',
                             'b12_weighted',
                             'd1_weighted',
                             'd2_weighted',
                             'd4_weighted',
                             'social_affect_gotham_weighted',
                             'restricted_repetitive_gotham_weighted',
                             'gotham_weighted_score',
                             'severity_score_lookup');
 

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
        $this->testName = "ados_module1";           // test_names.Test_name
        $this->table = 'ados_module1';              // name of database table corresponding to instrument
        // data keyed by commentID
        $this->commentID = $commentID;

        //The array of dates/timestamps to convert to database dates/timestamps
        //Any HTML_Quickform date elements must be listed here
        $this->dateTimeFields=array("Date_taken");

       //The array of selects with multiple answers allowed
        //Any HTML_Quickform multiple selects must be listed here
        $this->_selectMultipleElements = array();

        // required fields for data entry completion status
        $this->_requiredElements = array('Examiner', "a1", "c1");

	    $this->_doubleDataEntryDiffIgnoreColumns = array('CommentID', 'UserID', 'Testdate', 'Window_Difference', 'Candidate_Age',
			// Text entry columns
			'd1_specify',
			'd2_specify',
			'd4_specify',
			'other_comments',
			// Scored columns
            "ADOS_classification",
            "social_affect_total",
            "restricted_repetitive_behavior_total",
            "social_affect_restricted_repetitive_behavior_total",
            'a2_weighted',
            'a3_weighted',
            'a8_weighted',
            'b1_weighted',
            'b3_weighted',
            'b4_weighted',
            'b5_weighted',
            'b9_weighted',
            'b10_weighted',
            'b11_weighted',
            'b12_weighted',
            'd1_weighted',
            'd2_weighted',
            'd4_weighted',
            'social_affect_gotham_weighted',
            'restricted_repetitive_gotham_weighted',
            'gotham_weighted_score',
            'severity_score_lookup',
            'Data_entry_completion_status'
        );

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

       if(preg_match("/ados_module1(_page[0-9]+)/",$this->page,$matches)){
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
        // display test name
        $this->form->addElement('header', 'instrument_title', "ADOS Module 1");

        // automatically adds examiner & date of administration
        $this->_addMetadataFields();


    	$this->form->addElement("header",null,"SUMMARY SCORES:");
    
    	$this->form->addElement('static', "social_affect_total", "Social Affect Total:");
    
    	$this->form->addElement('static', "restricted_repetitive_behavior_total", "Restricted and Repetitive Behavior Total:");
    
    	$this->form->addElement('static', "social_affect_restricted_repetitive_behavior_total", "Social Affect and Restricted and Repetitive Behavior Total:");
    
    	$this->form->addElement('static', "ADOS_classification", "ADOS Classification:");

        $this->form->addElement('header', null, 'Severity Scores:');
        $this->form->addElement('static', 'gotham_weighted_score', 'Weighted Score:');
        $this->form->addElement('static', 'severity_score_lookup', 'Severity Score:');
        /*
    	$group[]= &$this->form->createElement("static", "gotham_weighted_score", null);
     	$this->form->addGroup($group, null, "ADOS Classification:", $this->_GUIDelimiter, false);
        unset($group);

    	$group[]= &$this->form->createElement("static", "ADOS_classification", null);
     	$this->form->addGroup($group, null, "ADOS Classification:", $this->_GUIDelimiter, false);
        unset($group);

    	$this->form->addElement("static",null,null);
    	$this->form->addElement("static",null,null);
        */
        $this->form->addElement("textarea", "other_comments", "Comments about Validity:", array('cols'=>25, 'rows'=>4));
        $this->XINRegisterRule("other_comments", array("{other_comments}{@}=={@}NEVER_REQUIRED"));

    }
    
/*	
	//They decided not to use this section - it was only partially implemented.
	//Section A: Observation
	//Question #1 - Free Play
        $this->form->addElement('header', null, "OBSERVATION:");
        

        $group[] =&$this->form->createElement('textarea', 'obs_q_1', null, "Communication Sample");
        $group[] =&$this->form->createElement('advcheckbox', 'obs_q_1_check', null, "Not Answered");
        $this->form->addGroup($group, 'obs_q_1_group', '1. Free Play', false);
        unset($group);

        

        $group[] =&$this->form->createElement('textarea', 'obs_q_1_notes', null, "Notes");
        $group[] =&$this->form->createElement('advcheckbox', 'obs_q_1_notes_check', null, "Not Answered");
        $this->form->addGroup($group, 'obs_q_1_notes_group', null, false);
        unset($group);

	//Rules for Question #1:
        $reqIfSettings = array('controller'=>"obs_q_1_check", 'operator'=>'!=', 'value'=>'1');
        $this->form->addRule("obs_q_1_group", 'Communication Sample is Required', 'requiredIfGroup', array_merge($reqIfSettings, array('element'=>"obs_q_1")));

        $reqIfSettings = array('controller'=>"obs_q_1_notes_check", 'operator'=>'!=', 'value'=>'1');
        $this->form->addRule("obs_q_1_notes_group", 'Notes are Required', 'requiredIfGroup', array_merge($reqIfSettings, array('element'=>"obs_q_1_notes")));



	//Question #2 - Response to Name
        

        $group[] =&$this->form->createElement('textarea', 'obs_q_2_notes', null, "Notes");
        $group[] =&$this->form->createElement('advcheckbox', 'obs_q_2_notes_check', null, "Not Answered");
        $this->form->addGroup($group, 'obs_q_2_notes_group', '2. Response to Name', false);
        unset($group);

	//Rules for Question #2:
        $reqIfSettings = array('controller'=>"obs_q_2_notes_check", 'operator'=>'!=', 'value'=>'1');
        $this->form->addRule("obs_q_2_notes_group", 'Notes are Required', 'requiredIfGroup', array_merge($reqIfSettings, array('element'=>"obs_q_2_notes")));



	//Question #3 - Response to Joint Attention
        

        $group[] =&$this->form->createElement('textarea', 'obs_q_3_notes', null, "Notes");
        $group[] =&$this->form->createElement('advcheckbox', 'obs_q_3_notes_check', null, "Not Answered");
        $this->form->addGroup($group, 'obs_q_3_notes_group', '3. Response to Joint Attention', false);
        unset($group);

	//Rules for Question #3:
        $reqIfSettings = array('controller'=>"obs_q_3_notes_check", 'operator'=>'!=', 'value'=>'1');
        $this->form->addRule("obs_q_3_notes_group", 'Notes are Required', 'requiredIfGroup', array_merge($reqIfSettings, array('element'=>"obs_q_3_notes")));



	//Question #4 - Bubble Play
        

        $group[] =&$this->form->createElement('textarea', 'obs_q_4_notes', null, "Notes");
        $group[] =&$this->form->createElement('advcheckbox', 'obs_q_4_notes_check', null, "Not Answered");
        $this->form->addGroup($group, 'obs_q_3_notes_group', '4. Bubble Play', false);
        unset($group);

	//Rules for Question #4:
        $reqIfSettings = array('controller'=>"obs_q_4_notes_check", 'operator'=>'!=', 'value'=>'1');
        $this->form->addRule("obs_q_4_notes_group", 'Notes are Required', 'requiredIfGroup', array_merge($reqIfSettings, array('element'=>"obs_q_4_notes")));



	//Question #5 - Anticipation of a Routine with Objects
        

        $group[] =&$this->form->createElement('textarea', 'obs_q_5_notes', null, "Notes");
        $group[] =&$this->form->createElement('advcheckbox', 'obs_q_5_notes_check', null, "Not Answered");
        $this->form->addGroup($group, 'obs_q_3_notes_group', '5. Anticipation of a Routine with Objects', false);
        unset($group);

	//Rules for Question #4:
        $reqIfSettings = array('controller'=>"obs_q_5_notes_check", 'operator'=>'!=', 'value'=>'1');
        $this->form->addRule("obs_q_5_notes_group", 'Notes are Required', 'requiredIfGroup', array_merge($reqIfSettings, array('element'=>"obs_q_5_notes")));

*/


    function _page1(){
    	//CODING
    	//Section A: Language and Communication
        $this->form->addElement('header', null, "CODING:");

        $this->form->addElement('header', null, "Section A: Language and Communication");
        $this->form->addElement('select', 'a1', '1. Overall Level of Non-Echoed Language', $this->option01238);
        $this->form->addElement('select', 'a2', '2. Frequency of Vocalization Directed to Others', $this->option0123);
        
        $this->form->addElement('select', 'a3', '3. Intonation of Vocalizations or Verbalization', $this->option0128);
        
        $this->form->addElement('select', 'a4', '4. Immediate Echolalia', $this->option01238);
        
        $this->form->addElement('select', 'a5', '5. Stereotyped/Idiosyncratic Use of Words or Phrases', $this->option01238);
        
        $this->form->addElement('select', 'a6', '6. Use of Others Body to Communicate', $this->option0128);
        
        $this->form->addElement('select', 'a7', '7. Pointing', $this->option0123);
        
        $this->form->addElement('select', 'a8', '8. Gestures', $this->option0128);

        
        


	   //Section B: Reciprocal Social Interaction
        $this->form->addElement('header', null, "Section B: Reciprocal Social Interaction");
        
        

        $this->form->addElement('select', 'b1', '1. Unusual Eye Contact', $this->option02);
        
        $this->form->addElement('select', 'b2', '2. Responsive Social Smile', $this->option0123);
        
        $this->form->addElement('select', 'b3', '3. Facial Expressions Directed to Others', $this->option012);
        
        $this->form->addElement('select', 'b4', '4. Integration of Gaze and Other Behaviors During Social Overtures', $this->option0123);
        
        $this->form->addElement('select', 'b5', '5. Shared Enjoyment in Interaction', $this->option012);
        
        $this->form->addElement('select', 'b6', '6. Response to Name', $this->option0123);
        
        $this->form->addElement('select', 'b7', '7. Requesting', $this->option0123);
        
        $this->form->addElement('select', 'b8', '8. Giving', $this->option012);
        
        $this->form->addElement('select', 'b9', '9. Showing', $this->option012);
        
        $this->form->addElement('select', 'b10', '10. Spontaneous Initiation of Joint Attention', $this->option012);
        
        $this->form->addElement('select', 'b11', '11. Response to Joint Attention', $this->option0123);
        
        $this->form->addElement('select', 'b12', '12. Quality of Social Overtures', $this->option0123);
        

        
        
    }
    
    function _page2(){
    	//Section C: Play
        $this->form->addElement('header', null, "Section C: Play");
        
        
        $this->form->addElement('select', 'c1', '1. Functional Play with Objects', $this->option0123);
        
        $this->form->addElement('select', 'c2', '2. Imagination/Creativity', $this->option0123);

        
        

    	//Section D: Stereotyped Behaviors and Restricted Interests
        $this->form->addElement('header', null, "Section D: Stereotyped Behaviors and Restricted Interests");
        
        
        $this->form->addElement('select', 'd1', '1. Unusual Sensory Interest in Play Material/Person', $this->option012);
        
     	$this->addTextAreaElement('d1_specify', $this->indent . "Please specify:");
        
        $this->form->addElement('select', 'd2', '2. Hand and Finger and Other Complex Mannerisms', $this->option012);
        
    	$this->addTextAreaElement('d2_specify', $this->indent . "Please specify:");
        
        $this->form->addElement('select', 'd3', '3. Self-Injurious Behavior', $this->option012);
        
        $this->form->addElement('select', 'd4', '4. Unusually Repetitive Interests or Stereotyped Behaviors', $this->option0123);
        
    	$this->addTextAreaElement('d4_specify', $this->indent . "Please specify unusual preoccupations, rituals, repetitive behaviors:");

        
        

    	//Section E: Other Abnormal Behaviors
        $this->form->addElement('header', null, "Section E: Other Abnormal Behaviors");
        
        
        $this->form->addElement('select', 'e1', '1. Overactivity', $this->option0127);
        
        $this->form->addElement('select', 'e2', '2. Tantrums, Aggression, Negative or Disruptive Behavior', $this->option012);
        
        $this->form->addElement('select', 'e3', '3. Anxiety', $this->option012);

        
        

    } // End Form

    function score(){
    	if ($this->_determineDataEntryCompletionStatus() == "Incomplete") {
    		return;
    	}
	
        // null scores
        $this->_nullScores($this->scoreCols);

        //get the saved scores
    	$db =& Database::singleton();
  	
    	$query = "SELECT * FROM $this->table WHERE CommentID = '$this->commentID'";
    	$record = array();
    	$db->selectRow($query, $record);
 	
        //Convert the entered scores to countable scores:
        //"Convert scores of 3 on the protocol to 2, and treat all other scores other than 0-3 as 0."
        $scores = array(); //holds converted scores
        foreach($record as $field=>$value) {
            if($value == 0) {
                $scores[$field] = 0;
            } elseif ($value == 1) {
                $scores[$field] = 1;
            } elseif ($value == 2) {
                $scores[$field] = 2;
            } elseif ($value == 3) {
                $scores[$field] = 2;
            } elseif ($value >= 4) {
                $scores[$field] = 0;
            } elseif ($value == "not_answered") {
                $scores[$field] = 0;
            }
        }

	    $module = '';
        
        // NO WORDS scoring
        if($record["a1"] == 3 || $record["a1"] == 8) {
            $module = '1-NoWords'; 

    		$scoreCols["social_affect_total"] = $scores["a2"] + $scores["a8"] + $scores["b1"] + $scores["b3"] + $scores["b4"] + $scores["b5"] + $scores["b9"] + $scores["b10"] + $scores["b11"] + $scores["b12"];
    		$scoreCols["restricted_repetitive_behavior_total"] = $scores["a3"] + $scores["d1"] + $scores["d2"] + $scores["d4"];
    		$scoreCols["social_affect_restricted_repetitive_behavior_total"] = $scoreCols["social_affect_total"] + $scoreCols["restricted_repetitive_behavior_total"];
    
    		if($scoreCols["social_affect_restricted_repetitive_behavior_total"] >= 11 && $scoreCols["social_affect_restricted_repetitive_behavior_total"] <= 15){
    			$scoreCols["ADOS_classification"] = "autism spectrum";
    		} elseif ($scoreCols["social_affect_restricted_repetitive_behavior_total"] >= 16) {
    			$scoreCols["ADOS_classification"] = "autism";
    		} else {
           		$scoreCols["ADOS_classification"] = "none";
    		}

            // Weightings from Gotham, Risi, Pickles and Lord 2007 Table 2
            // Put in the same order as the paper, which happens to be different than
            // how Loris orders it, which is why this looks a little weird
            // Social Affect
            $scoreCols['b1_weighted'] = $scores['b1'] * 0.64; // Unusual Eye Contact
            $scoreCols['b4_weighted'] = $scores['b4'] * 0.76; // Gaze and Other
            $scoreCols['b3_weighted'] = $scores['b3'] * 0.85; // Facial Expressions
            $scoreCols['a2_weighted'] = $scores['a2'] * 0.69; // Frequency of vocalization
            $scoreCols['b5_weighted'] = $scores['b5'] * 0.71; // Shared Enjoyment
            $scoreCols['b12_weighted'] = $scores['b12'] * 0.74; // Quality of Social Overtures
            $scoreCols['b11_weighted'] = $scores['b11'] * 0.60;// Response to Joint Attention
            $scoreCols['a8_weighted'] = $scores['a8'] * 0.73; // Gestures
            $scoreCols['b9_weighted'] = $scores['b9'] * 0.69; // Showing
            $scoreCols['b10_weighted'] = $scores['b10'] * 0.77;// Initiation of Joint Attention
    		$scoreCols["social_affect_gotham_weighted"] = $scoreCols["a2_weighted"] + $scoreCols["a8_weighted"] + $scoreCols["b1_weighted"] + $scoreCols["b3_weighted"] + $scoreCols["b4_weighted"] + $scoreCols["b5_weighted"] + $scoreCols["b9_weighted"] + $scoreCols["b10_weighted"] + $scoreCols["b11_weighted"] + $scoreCols["b12_weighted"];
            // Restricted Repetitive Behaviours 
            $scoreCols['a3_weighted'] = $scores['a3'] * 0.44; // Intonation
            $scoreCols['d1_weighted'] = $scores['d1'] * 0.78; // Unusual Sensory Interest 
            $scoreCols['d4_weighted'] = $scores['d4'] * 0.44; // Repetitive Interests
            $scoreCols['d2_weighted'] = $scores['d2'] * 0.66; // Hand Mannerisms
            $scoreCols['restricted_repetitive_gotham_weighted'] = $scoreCols['a3_weighted'] + $scoreCols['d1_weighted'] + $scoreCols['d2_weighted'] + $scoreCols['d4_weighted'];

            $scoreCols['gotham_weighted_score'] = $scoreCols['social_affect_gotham_weighted'] + $scoreCols['restricted_repetitive_gotham_weighted'];

    	}

    	//SOME WORDS Scoring
        if($record["a1"] == 0 || $record["a1"] == 1 || $record["a1"] == 2) {
            $module = '1-Words';

        	$scoreCols["social_affect_total"] = $scores["a2"] + $scores["a7"] + $scores["a8"] + $scores["b1"] + $scores["b3"] + $scores["b4"] + $scores["b5"] + $scores["b9"] + $scores["b10"] + $scores["b12"];
        	$scoreCols["restricted_repetitive_behavior_total"] = $scores["a5"] + $scores["d1"] + $scores["d2"] + $scores["d4"];
        	$scoreCols["social_affect_restricted_repetitive_behavior_total"] = $scoreCols["social_affect_total"] + $scoreCols["restricted_repetitive_behavior_total"];
        
        	if($scoreCols["social_affect_restricted_repetitive_behavior_total"] >= 8 && $scoreCols["social_affect_restricted_repetitive_behavior_total"] <= 11){
        		$scoreCols["ADOS_classification"] = "autism spectrum";
        	} elseif ($scoreCols["social_affect_restricted_repetitive_behavior_total"] >= 12) {
        		$scoreCols["ADOS_classification"] = "autism";
        	} else {
        		$scoreCols["ADOS_classification"] = "none";
        	}
        }

        //Determine Severity score from ados_lookup table 
	    //Requires age in months:  
        $db->selectRow("SELECT * FROM $this->table WHERE CommentID='".$this->getCommentID()."'", $Answers);
	    $age_months = 0;
        if($this->getSessionID() != NULL) { //quickform_parser doesn't use any specific session
            $timepoint =& TimePoint::singleton($this->getSessionID());
            $dob = $timepoint->getEffectiveDateOfBirth();
        }

        if(!empty($dob) && !empty($Answers['Date_taken'])) {
            $age = Utility::calculateAge($dob, $Answers["Date_taken"]);
            if(is_array($age)) {
                $age_months = $age['year'] * 12 + $age['mon'];
	        }
        }
        //Severity score lookup:  column limits for age (min, max), raw score (min, max) 
        // ados_lookup table columns : sevscore module minagemos maxagemos minraw maxraw   
	    if ( $module != '' && $age_months != 0) {  
	       $query_severity_lookup = "SELECT sevscore FROM ados_lookup WHERE module = :modname AND minagemos <= :agemonths AND maxagemos >= :agemonths AND minraw <= :rawscore AND maxraw >= :rawscore";
        	$record_lookup = array();
	        $sevscore = $db->pselectOne($query_severity_lookup, array(
                'modname' => $module,
                'agemonths' => $age_months,
                'rawscore' => $scoreCols['social_affect_restricted_repetitive_behavior_total']
            ));
            if(empty($sevscore)) {
                $scoreCols['severity_score_lookup']= "N/A";
            } else {
                $scoreCols['severity_score_lookup']=$sevscore;
            }

	    }

        // save scores to database
 	    $result = $db->update($this->table, $scoreCols, array("CommentID"=>$this->getCommentID()));
    }    // end score function
}
?>
