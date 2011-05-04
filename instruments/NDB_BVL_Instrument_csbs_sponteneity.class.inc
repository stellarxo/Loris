<?php

class NDB_BVL_Instrument_csbs_sponteneity extends NDB_BVL_Instrument
{

/*
INSERT INTO test_names VALUES('', 'csbs_sponteneity', 'CSBS Sponeneity Coding Sheet', 0, 1, NULL);

INSERT INTO test_battery VALUES ('', 'csbs_sponteneity', '0', '420', 'Y', 'Visit', '1', NULL);

INSERT INTO instrument_subtests VALUES('', 'csbs_sponteneity', 'csbs_sponteneity_page1', 'Child Approach / Structured Communication Activities', 1);
INSERT INTO instrument_subtests VALUES('', 'csbs_sponteneity', 'csbs_sponteneity_page2', 'Free Play', 2);
*/
/*
    	var $scoreLabels = array("q_1_gaze_shifts_raw_score",
        "q_2_shared_positive_affect_raw_score",
        "q_3_gaze_point_following_raw_score",
        "q_4_rate_of_communicating_raw_score",
        "q_5_behaviour_regulation_raw_score",
        "q_6_social_interaction_raw_score",
        "q_7_joint_attention_raw_score",
        "q_8_conventional_gestures_raw_score",
        "q_9_distal_gestures_raw_score",
        "q_10_syllables_consonants_raw_score",
        "q_11_inventory_of_consonants_raw_score",
        "q_12_words_raw_score",
        "q_13_words_raw_score",
        "q_14_word_combos_raw_score",
        "q_15_word_combos_raw_score",
        "q_16_language_comp_raw_score",
        "q_17_action_schemes_raw_score",
        "q_18_actions_towards_other_raw_score",
        "q_19_sequence_action_schemes_raw_score",
        "q_20_stacks_tower_raw_score",
        "emotion_eye_gaze_weighted",
        "communication_weighted",
        "gestures_weighted",
        "sounds_weighted",
        "words_weighted",
        "understanding_weighted",
        "object_use_weighted");
*/


	var $yesNo = array(null=>"", "yes"=>"Yes", "no"=>"No", "not_answered"=>"Not Answered");

	var $dateOptions = array(NULL=>"", "2007"=>"2007", "2008"=>"2008", "2009"=>"2009", "2010"=>"2010", "2011"=>"2011", "2012"=>"2012");

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
        $this->testName = "csbs_sponteneity";           // test_names.Test_name
        $this->table = 'csbs_sponteneity';              // name of database table corresponding to instrument
        // data keyed by commentID
        $this->commentID = $commentID;
        
        //The array of dates/timestamps to convert to database dates/timestamps
        //Any HTML_Quickform date elements must be listed here
        $this->dateTimeFields=array("Date_taken");
            
        //The array of selects with multiple answers allowed
        //Any HTML_Quickform multiple selects must be listed here
        $this->_selectMultipleElements = array();

        // required fields for data entry completion status
        $this->_requiredElements = array('Examiner', "q_1_orientation", "prompta_1");

        //Column headers
        $this->localDefaults = array_merge($this->localDefaults, array("h_1"=>"1", "h_2"=>"2", "h_3"=>"3", "h_4"=>"4", "h_5"=>"5", "h_6"=>"6", "raw_score"=>"Raw Score",
                                            "wind_up_toy"=>"Wind-up toy", "balloon"=>"Balloon", "bubbles"=>"Bubbles", "jar"=>"Jar",
                                            "books"=>"Books" . $this->indent . $this->indent . $this->indent . $this->indent . $this->indent . $this->indent . $this->indent,
                                            "play"=>"Play" . $this->indent . $this->indent . $this->indent . $this->indent . $this->indent . $this->indent . $this->indent,
                                            "object_names"=>"object names:", "person_names"=>"person names:", "body_parts"=>"body parts:", "subscale"=>"Subscale", "raw_weighted"=>"Weighted Raw Score", 						    "standard_score"=>"Standard Score","percentile_rank"=>"Percentile Rank", "prompt_header"=>"Prompt level", "response_header"=>"Quality of response", "prompt_header2"=>"Type of prompt", "amount_header"=>"Amount of prompting", "other_header"=>"Other - specify"));


    /**
     * Array of column names to be ignored by the double data entry conflict detector.
     */
    $this->_doubleDataEntryDiffIgnoreColumns = array('CommentID', 'UserID', 'Testdate',
						     'relationship_to_child',
						     'relationship_to_child_status',
						     'comments',
						     'comments_status',
						   'q_13_words_1',
						   'q_13_words_2',
						   'q_13_words_3',
						   'q_13_words_4',
						   'q_13_words_5',
						   'q_13_words_6',
						   'q_13_words_7',
						   'q_13_words_8',
						   'q_13_words_9',
						   'q_13_words_10',
						   'q_13_words_11',
						   'q_13_words_12',
						   'q_13_words_13',
						   'q_13_words_14',
						   'q_13_words_15',
						   'q_13_words_16', 
						   'q_15_word_combos_1',
						   'q_15_word_combos_2',
						   'q_15_word_combos_3',
						   'q_15_word_combos_4',
						   'q_15_word_combos_5',
						   'q_15_word_combos_6',
						   'q_15_word_combos_7',
						   'q_15_word_combos_8',
						   'q_16_language_comp_objects_1',
						   'q_16_language_comp_objects_2',
						   'q_16_language_comp_objects_3',
						   'q_16_language_comp_objects_4',
						   'q_16_language_comp_person_1',
						   'q_16_language_comp_person_2',
						   'q_16_language_comp_person_3',
						   'q_16_language_comp_body_parts_1',
						   'q_16_language_comp_body_parts_2',
						   'q_16_language_comp_body_parts_3',
						   'q_16_language_comp_body_parts_4',
						   'q_18_actions_towards_other_1',
						   'q_18_actions_towards_other_2',
						   'q_18_actions_towards_other_3',
						   'q_18_actions_towards_other_4',
						   'q_18_actions_towards_other_5',
						   'q_18_actions_towards_other_6',
						   'q_19_sequence_action_schemes_1',
						   'q_19_sequence_action_schemes_2',
						   'q_19_sequence_action_schemes_3',
						   'q_19_sequence_action_schemes_4',
						   'q_19_sequence_action_schemes_5',
						   'q_19_sequence_action_schemes_6');



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
        if(ereg("csbs_sponteneity(_page[0-9]+)",$this->page,$matches)){
            call_user_method($matches[1], &$this);
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
        //display test name
        $this->form->addElement('header', null, "Communication and Symbolic Behaviour Scales - Sponteneity Coding Sheet");
        $this->form->addElement('static', null, "<br />");
        $this->form->addElement('static', null, "<br />");

        
        // automatically adds examiner & date of administration
	$this->form->addElement('static', null, "The following two fields refer to Date and Examiner for the CSBS");
        $this->_addMetadataFields();
	$this->form->addElement("static", null, "<br/>");		

	$this->form->addElement('static', null, "The following two fields refer to Date and Coder for the CSBS Sponteneity");
	$this->addDateElement("date_coded", "Date of Coding:"); 
	$this->addTextElement("coder", "Coder:"); 

	$this->form->addElement("static", null, "<br/>");		


/*
	
	$this->form->addElement("header",null,"Summary Scores:");
	$group[]= &$this->form->createElement("static", "raw_weighted", null);
        $group[]= &$this->form->createElement("static", "standard_score", null);
        $group[]= &$this->form->createElement("static", "percentile_rank", null);
  	$this->form->addGroup($group, null, Subscale, $this->_GUIDelimiter, false);
        unset($group);
	

	$group[]= &$this->form->createElement("static", emotion_eye_gaze_weighted, null);
        $group[]= &$this->form->createElement("static", emotion_eye_gaze_standard, null);
        $group[]= &$this->form->createElement("static", emotion_eye_gaze_percentile, null);
  	$this->form->addGroup($group, null, "Emotion and Eye Gaze", $this->_GUIDelimiter, false);
        unset($group);


	$group[]= &$this->form->createElement("static", communication_weighted, null);
        $group[]= &$this->form->createElement("static", communication_standard, null);
        $group[]= &$this->form->createElement("static", communication_percentile, null);
  	$this->form->addGroup($group, null, "Communication", $this->_GUIDelimiter, false);
        unset($group);


	$group[]= &$this->form->createElement("static", gestures_weighted, null);
        $group[]= &$this->form->createElement("static", gestures_standard, null);
        $group[]= &$this->form->createElement("static", gestures_percentile, null);
  	$this->form->addGroup($group, null, "Gestures", $this->_GUIDelimiter, false);
        unset($group);


	$group[]= &$this->form->createElement("static", sounds_weighted, null);
        $group[]= &$this->form->createElement("static", sounds_standard, null);
        $group[]= &$this->form->createElement("static", sounds_percentile, null);
  	$this->form->addGroup($group, null, "Sounds", $this->_GUIDelimiter, false);
        unset($group);


	$group[]= &$this->form->createElement("static", words_weighted, null);
        $group[]= &$this->form->createElement("static", words_standard, null);
        $group[]= &$this->form->createElement("static", words_percentile, null);
  	$this->form->addGroup($group, null, "Words", $this->_GUIDelimiter, false);
        unset($group);


	$group[]= &$this->form->createElement("static", understanding_weighted, null);
        $group[]= &$this->form->createElement("static", understanding_standard, null);
        $group[]= &$this->form->createElement("static", understanding_percentile, null);
  	$this->form->addGroup($group, null, "Understanding", $this->_GUIDelimiter, false);
        unset($group);
 

	$group[]= &$this->form->createElement("static", object_use_weighted, null);
        $group[]= &$this->form->createElement("static", object_use_standard, null);
        $group[]= &$this->form->createElement("static", object_use_percentile, null);
  	$this->form->addGroup($group, null, "Object Use", $this->_GUIDelimiter, false);
        unset($group);


	$group[]= &$this->form->createElement("static", social_composite_score, null);
        $group[]= &$this->form->createElement("static", social_composite_standard, null);
        $group[]= &$this->form->createElement("static", social_composite_percentile, null);
  	$this->form->addGroup($group, null, "Social Composite", $this->_GUIDelimiter, false);
        unset($group);


	$group[]= &$this->form->createElement("static", speech_composite_score, null);
        $group[]= &$this->form->createElement("static", speech_composite_standard, null);
        $group[]= &$this->form->createElement("static", speech_composite_percentile, null);
  	$this->form->addGroup($group, null, "Speech Composite", $this->_GUIDelimiter, false);
        unset($group);


	$group[]= &$this->form->createElement("static", symbolic_composite_score, null);
        $group[]= &$this->form->createElement("static", symbolic_composite_standard, null);
        $group[]= &$this->form->createElement("static", symbolic_composite_percentile, null);
  	$this->form->addGroup($group, null, "Symbolic Composite", $this->_GUIDelimiter, false);
        unset($group);


	$group[]= &$this->form->createElement("static", total_weighted_raw_score, null);
        $group[]= &$this->form->createElement("static", total_standard, null);
        $group[]= &$this->form->createElement("static", total_percentile, null);
  	$this->form->addGroup($group, null, "Total", $this->_GUIDelimiter, false);
        unset($group);

*/
    }
 /*   
    function score(){
    	if($this->_determineDataEntryCompletionStatus() == "Incomplete") {
    		return;
    	}

        //null scores
		$this->_nullScores($this->scoreLabels);
		
        //get the saved scores
    	$db =& Database::singleton();
    	if(PEAR::isError($db)) {
			return PEAR::raiseError ("Could not connect to database".$db->getMessage());
    	}
  	
	
    	$query = "SELECT * FROM $this->table WHERE CommentID = '$this->commentID'";
    	$record = array();
    	$db->selectRow($query, $record);
    	if (PEAR::isError($record)) {
    		return PEAR::raiseError("Could not retrieve scores: " . $record->getMessage());
    	}
   
 	
       // Get the subject age in months for scoring
        $timepoint =& TimePoint::singleton($this->getSessionID());
        $dob = $timepoint->getEffectiveDateOfBirth();
        
		$age = Utility::calculateAge($dob, $record["Date_taken"]);
       		$age_months = $age['year'] * 12 + $age['mon'];
        if($this->isError($age)) {
            return $this->raiseError("Could not compute age");
        }  


  	//calculate raw scores
        $scores["q_1_gaze_shifts_raw_score"] = $this->_countChecked($record, "q_1_gaze_shifts_");
        $scores["q_2_shared_positive_affect_raw_score"] = $this->_countChecked($record, "q_2_shared_positive_affect_");
        $scores["q_3_gaze_point_following_raw_score"] = $this->_countChecked($record, "q_3_gaze_point_following_");

        foreach($record as $field=>$value) {
            if(ereg("q_4_rate_of_communicating", $field)) {
                $score += $value;
            }
        }
        $scores["q_4_rate_of_communicating_raw_score"] = $score;

        $scores["q_5_behaviour_regulation_raw_score"] = $this->_countChecked($record, "q_5_behaviour_regulation");
        $scores["q_6_social_interaction_raw_score"] = $this->_countChecked($record, "q_6_social_interaction");
        $scores["q_7_joint_attention_raw_score"] = $this->_countChecked($record, "q_7_joint_attention");
        $scores["q_8_conventional_gestures_raw_score"] = $this->_countChecked($record, "q_8_conventional_gestures_");
        $scores["q_9_distal_gestures_raw_score"] = $this->_countChecked($record, "q_9_distal_gestures_");
        $scores["q_10_syllables_consonants_raw_score"] = $this->_countChecked($record, "q_10_syllables_consonants_"); 
        $scores["q_11_inventory_of_consonants_raw_score"] = $this->_countChecked($record, "q_11_inventory_of_consonants_");
        $scores["q_12_words_raw_score"] = $this->_countChecked($record, "q_12_words_");
        
        $scores["q_13_words_raw_score"] = $this->_countWords($record, "q_13_words_");
        $scores["q_14_word_combos_raw_score"] = $this->_countChecked($record, "q_14_word_combos_");
        $scores["q_15_word_combos_raw_score"] = $this->_countWords($record, "q_15_word_combos_");
        $scores["q_16_language_comp_raw_score"] = $this->_countWords($record, "q_16_language_");

        $scores["q_17_action_schemes_raw_score"] = $this->_countChecked($record, "q_17_action_schemes_");
        $scores["q_18_actions_towards_other_raw_score"] = $this->_countWords($record, "q_18_actions_towards_other_");
        $scores["q_19_sequence_action_schemes_raw_score"] = $this->_countWords($record, "q_19_sequence_action_schemes_");
        if (is_int(intval(substr($record["q_20_stacks_tower"], 0, 1)))) {
            $scores["q_20_stacks_tower_raw_score"] = intval(substr($record["q_20_stacks_tower"], 0, 1));
        } else {
            $scores["q_20_stacks_tower_raw_score"] = 0;
        }
    	
    	//calculate subscales
        $scores["emotion_eye_gaze_weighted"] = $scores["q_1_gaze_shifts_raw_score"] +
        $scores["q_2_shared_positive_affect_raw_score"] +
        3 * $scores["q_3_gaze_point_following_raw_score"];

        $scores["communication_weighted"] = round($scores["q_4_rate_of_communicating_raw_score"] / 3) +
 	$scores["q_5_behaviour_regulation_raw_score"] +
        $scores["q_6_social_interaction_raw_score"] +
        $scores["q_7_joint_attention_raw_score"];

        $scores["gestures_weighted"] = $scores["q_8_conventional_gestures_raw_score"] * 2 + 
        $scores["q_9_distal_gestures_raw_score"];

        $scores["sounds_weighted"] = $scores["q_10_syllables_consonants_raw_score"] +
        2 * $scores["q_11_inventory_of_consonants_raw_score"];

        $scores["words_weighted"] = $scores["q_12_words_raw_score"] + round($scores["q_13_words_raw_score"] / 2) +  
        $scores["q_14_word_combos_raw_score"] +
        $scores["q_15_word_combos_raw_score"];

        $q_16_language_comp_objects = $this->_countWords($record, "q_16_language_comp_objects_");
        $q_16_language_comp_person = $this->_countWords($record, "q_16_language_comp_person_");
        $q_16_language_comp_body_parts = $this->_countWords($record, "q_16_language_comp_body_parts_");
        
        //enforce cutoffs
        if ($q_16_language_comp_objects > 3) $q_16_language_comp_objects = 3;
        if ($q_16_language_comp_person > 2) $q_16_language_comp_person = 2;
        if ($q_16_language_comp_body_parts > 3) $q_16_language_comp_body_parts = 3;

        $scores["understanding_weighted"] = $q_16_language_comp_objects * 3 +
        $q_16_language_comp_person * 3 +
        $q_16_language_comp_body_parts * 3;
        
        $scores["object_use_weighted"] = $scores["q_17_action_schemes_raw_score"] +
        $scores["q_18_actions_towards_other_raw_score"] +
        $scores["q_19_sequence_action_schemes_raw_score"] +
        $scores["q_20_stacks_tower_raw_score"];


	//calculate weighted raw composite scores
	$scores["social_composite_score"] = $scores["emotion_eye_gaze_weighted"] +
        $scores["communication_weighted"] +
        $scores["gestures_weighted"];


	$scores["speech_composite_score"] = $scores["sounds_weighted"] +
        $scores["words_weighted"];


	$scores["symbolic_composite_score"] = $scores["understanding_weighted"] +
        $scores["object_use_weighted"];


	//calculate weighted total scores
	$scores["total_weighted_raw_score"] = $scores["social_composite_score"] +
        $scores["speech_composite_score"] +
        $scores["symbolic_composite_score"];


	//establish standard scores and percentile rank for Emotion Eye Gaze
	$query_scores1 = "SELECT * FROM csbs_lookup WHERE age_months=".$age_months. " AND score_weighted=".$scores['emotion_eye_gaze_weighted']." AND subscale='emotion_eye_gaze_weighted'";
    	$record_1 = array();
	$db->selectRow($query_scores1, $record_1);
    	if (PEAR::isError($record_1)) {
    		return PEAR::raiseError("Could not retrieve scores: " . $record_1->getMessage());
    	}
	$scores['emotion_eye_gaze_standard']=($record_1['score_standard']);
	$scores['emotion_eye_gaze_percentile']=($record_1['score_percentile']);


	$query_scores2 = "SELECT * FROM csbs_lookup WHERE age_months=".$age_months. " AND score_weighted=".$scores['communication_weighted']." AND subscale='communication_weighted'";
    	$record_2 = array();
	$db->selectRow($query_scores2, $record_2);
    	if (PEAR::isError($record_2)) {
    		return PEAR::raiseError("Could not retrieve scores: " . $record_2->getMessage());
    	}
	$scores['communication_standard']=($record_2['score_standard']);
	$scores['communication_percentile']=($record_2['score_percentile']);


	$query_scores3 = "SELECT * FROM csbs_lookup WHERE age_months=".$age_months. " AND score_weighted=".$scores['gestures_weighted']." AND subscale='gestures_weighted'";
    	$record_3 = array();
	$db->selectRow($query_scores3, $record_3);
    	if (PEAR::isError($record_3)) {
    		return PEAR::raiseError("Could not retrieve scores: " . $record_3->getMessage());
    	}
	$scores['gestures_standard']=($record_3['score_standard']);
	$scores['gestures_percentile']=($record_3['score_percentile']);


	$query_scores4 = "SELECT * FROM csbs_lookup WHERE age_months=".$age_months. " AND score_weighted=".$scores['sounds_weighted']." AND subscale='sounds_weighted'";
    	$record_4 = array();
	$db->selectRow($query_scores4, $record_4);
    	if (PEAR::isError($record_4)) {
    		return PEAR::raiseError("Could not retrieve scores: " . $record_4->getMessage());
    	}
	$scores['sounds_standard']=($record_4['score_standard']);
	$scores['sounds_percentile']=($record_4['score_percentile']);


	$query_scores5 = "SELECT * FROM csbs_lookup WHERE age_months=".$age_months. " AND score_weighted=".$scores['words_weighted']." AND subscale='words_weighted'";
    	$record_5 = array();
	$db->selectRow($query_scores5, $record_5);
    	if (PEAR::isError($record_5)) {
    		return PEAR::raiseError("Could not retrieve scores: " . $record_5->getMessage());
    	}
	$scores['words_standard']=($record_5['score_standard']);
	$scores['words_percentile']=($record_5['score_percentile']);



	$query_scores6 = "SELECT * FROM csbs_lookup WHERE age_months=".$age_months. " AND score_weighted=".$scores['understanding_weighted']." AND subscale='understanding_weighted'";
    	$record_6 = array();
	$db->selectRow($query_scores6, $record_6);
    	if (PEAR::isError($record_6)) {
    		return PEAR::raiseError("Could not retrieve scores: " . $record_6->getMessage());
    	}
	$scores['understanding_standard']=($record_6['score_standard']);
	$scores['understanding_percentile']=($record_6['score_percentile']);



	$query_scores7 = "SELECT * FROM csbs_lookup WHERE age_months=".$age_months. " AND score_weighted=".$scores['object_use_weighted']." AND subscale='object_use_weighted'";
    	$record_7 = array();
	$db->selectRow($query_scores7, $record_7);
    	if (PEAR::isError($record_7)) {
    		return PEAR::raiseError("Could not retrieve scores: " . $record_7->getMessage());
    	}
	$scores['object_use_standard']=($record_7['score_standard']);
	$scores['object_use_percentile']=($record_7['score_percentile']);


	$query_scores8 = "SELECT * FROM csbs_lookup WHERE age_months=".$age_months. " AND score_weighted=".$scores['social_composite_score']." AND subscale='social_composite_score'";
    	$record_8 = array();
	$db->selectRow($query_scores8, $record_8);
    	if (PEAR::isError($record_8)) {
    		return PEAR::raiseError("Could not retrieve scores: " . $record_8->getMessage());
    	}
	$scores['social_composite_standard']=($record_8['score_standard']);
	$scores['social_composite_percentile']=($record_8['score_percentile']);



	$query_scores9 = "SELECT * FROM csbs_lookup WHERE age_months=".$age_months. " AND score_weighted=".$scores['speech_composite_score']." AND subscale='speech_composite_score'";
    	$record_9 = array();
	$db->selectRow($query_scores9, $record_9);
    	if (PEAR::isError($record_9)) {
    		return PEAR::raiseError("Could not retrieve scores: " . $record_9->getMessage());
    	}
	$scores['speech_composite_standard']=($record_9['score_standard']);
	$scores['speech_composite_percentile']=($record_9['score_percentile']);



	$query_scores10 = "SELECT * FROM csbs_lookup WHERE age_months=".$age_months. " AND score_weighted=".$scores['symbolic_composite_score']." AND subscale='symbolic_composite_score'";
    	$record_10 = array();
	$db->selectRow($query_scores10, $record_10);
    	if (PEAR::isError($record_10)) {
    		return PEAR::raiseError("Could not retrieve scores: " . $record_10->getMessage());
    	}
	$scores['symbolic_composite_standard']=($record_10['score_standard']);
	$scores['symbolic_composite_percentile']=($record_10['score_percentile']);



	$query_scores11 = "SELECT * FROM csbs_lookup WHERE age_months=".$age_months. " AND score_weighted=".$scores['total_weighted_raw_score']." AND subscale='total_weighted_raw_score'";
    	$record_11 = array();
	$db->selectRow($query_scores11, $record_11);
    	if (PEAR::isError($record_11)) {
    		return PEAR::raiseError("Could not retrieve scores: " . $record_11->getMessage());
    	}
	$scores['total_standard']=($record_11['score_standard']);
	$scores['total_percentile']=($record_11['score_percentile']);


	// save scores
	$result = $db->update($this->table, $scores, array("CommentID"=>$this->getCommentID()));
	if($db->isError($result)) {
		return PEAR::raiseError("Could not save total score: ". $result->getMessage());
	}
		
    }    // end score function
*/

    function _page1(){


        $this->form->addElement('header', null, "<br/>Child Approach");
	$this->form->addElement("static", null, "<br/>");		

        $this->form->addElement("select", "q_1_orientation", "1. Orientation to Examiner", array(null=>"", "1_constantly_avoids"=>"1. Constantly avoids", "2_typically_avoids"=>"2. Typically avoids", "3_occasionaly_avoids"=>"3. Occasionally avoids", "4_moderately_responds"=>"4. Moderately responds", "5_high_responsiveness"=>"5. High responsiveness",  "not_answered"=>"Not Answered"));

        $this->form->addElement("select", "q_2_duration_attention", "2. Duration Attention to Task", array(null=>"", "1_never"=>"1. Never attends", "2_generally_inattentive"=>"2. Generally inattentive", "3_somewhat"=>"3. Attends as often as does not", "4_stays_with"=>"4. \"Stays with\" activities", "5_attends"=>"5. Constantly attends",  "not_answered"=>"Not Answered"));

        $this->form->addElement("select", "q_2_capturing_interest", "3. Capturing Initial Interest", array(null=>"", "1_not_attend"=>"1. Does not attend", "2_uninterested"=>"2. Typically un-interested", "3_somewhat"=>"3. Interested in half of activities", "4_typically_interested"=>"4. Typically interested", "5_attends"=>"5. Almost always attends",  "not_answered"=>"Not Answered"));
        
        $this->addTextAreaElement("comments", "Comments:");    
	$this->form->addElement("static", null, "<br/>");		

        //Emotion and Eye Gaze
	$this->form->addElement("header", null, "Structured Communication Activities");
	$this->form->addElement("static", null, "<br/>");		


	$promptLevel = array(null=>"", "0"=>"0", "1"=>"1", "2"=>"2", "3"=>"3", "8_not_codeable"=>"8 Not Codeable", "no_communication"=>"No Communication", "not_administered"=>"Not Administered");
	$qualityResponse = array(null=>"", "dop"=>"DOP", "doa"=>"DOA", "fda"=>"FDA", "mon"=>"MON", "fnc"=>"FNC", "rp"=>"RP", "wp"=>"WP", "nr"=>"NR", "other"=>"Other", "no_communication"=>"No Communication");

	$headers = array("", "1. Wind up Toy (& bag)", "2. Balloon (& bag)", "3. Bubbles (& bag)", "4. Jar (& bag)");

	

	for ($i = 1; $i <5; $i++)
	{

		$this->form->addElement("static", null, "<b>$headers[$i]</b>");

		for ($j = 1; $j<3; $j++)
		{
	
        		$group[] =&$this->form->createElement("static", "prompt_header", "Prompt Level");
        		$group[] =&$this->form->createElement("static", "response_header", "Quality of Response");
        		$group[] =&$this->form->createElement("static", "other_header", "Other - specify");
        		$this->form->addGroup($group, "wind_up_headers", "", $this->_GUIDelimiter, false);
        		unset($group);

        		$group[] = &$this->form->createElement("select", "wind_up_ph{$j}_$i", null, $promptLevel);
        		$group[] = &$this->form->createElement("select", "wind_up_ph{$j}_response_$i", null, $qualityResponse);
			$group[] = &$this->form->createElement("text", "wind_up_ph{$j}_other_$i", null);

			if ($j == 1)	
        			$this->form->addGroup($group, null, "a. PH $j", $this->_GUIDelimiter, false);
			else				
        			$this->form->addGroup($group, null, "b. PH $j", $this->_GUIDelimiter, false);
			
                	$this->addTextAreaElement("ph{$j}_notes", $this->indent . "Notes:");
        		unset($group);
       		}
        	

		$this->form->addElement("select", "wind_up_additional_communication_$i", "c. Additional non-prompted communication", $this->yesNo);
        	$this->form->addElement("select", "wind_up_spontaneous_communication_$i", "d. Spontaneous communication not presented by clinician", $this->yesNo);
		$this->form->addElement("static", null, "<br/>");		
		$this->form->addElement("static", null, "<br/>");		
 	}

/*
        //Gestures
        $this->form->addElement("header", null, "Gestures");
        $this->_printHeaderCols();

        $group[] = &$this->form->createElement("advcheckbox", "q_8_conventional_gestures_gives", null, "gives", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_8_conventional_gestures_shows", null, "shows", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_8_conventional_gestures_pushes_pulls", null, "pushes/pulls", null, array("unchecked", "checked"));
        $group[] = &$this->form->addElement('static', null);
        $group[] = &$this->form->createElement("advcheckbox", "q_8_conventional_gestures_reaches", null, "reaches", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("static", null, null);
        $group[] = &$this->form->createElement("static", null, null);
        $group[] = &$this->form->createElement("static", "q_8_conventional_gestures_raw_score");
        $this->form->addGroup($group, null, "8. Inventory of conventional gestures", $this->_GUIDelimiter, false);
        unset($group);
        $group[] = &$this->form->createElement("advcheckbox", "q_8_conventional_gestures_points", null, "points", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_8_conventional_gestures_waves", null, "waves", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_8_conventional_gestures_nods_head", null, "nods head", null, array("unchecked", "checked"));
        $group[] = &$this->form->addElement('static', null);
        $group[] = &$this->form->createElement("advcheckbox", "q_8_conventional_gestures_shakes_head", null, "shakes head", null, array("unchecked", "checked"));
        $this->form->addGroup($group, null, null, $this->_GUIDelimiter, false);
        unset($group);

        for($int = 1; $int <=6; $int++) {
            $group[] = &$this->form->createElement("advcheckbox", "q_9_distal_gestures_" . $int, null, null, null, array("unchecked", "checked"));
        }
        $group[] = &$this->form->createElement("static", "q_9_distal_gestures_raw_score");
        $this->form->addGroup($group, null, "9. Distal gestures", $this->_GUIDelimiter, false);
        unset($group);
        
        $this->form->addElement("static", "gestures_weighted", "Gestures Weighted:");
*/
    }
    
    function _page2() 
	{
	
	$this->form->addElement("header", null, "Free Play Activities");

        $promptType = array(null=>"", "verbal"=>"V", "gesture"=>"G", "verbal_and_gesture"=>"V+G", "independent"=>"I", "nc"=>"No Communication");
        $promptAmount = array(null=>"", "0_initiates_prior_prompt"=>"0", "1"=>"1", "2"=>"2", "3"=>"3", "4"=>"4", "5"=>"5", "nc"=>"No Communication");

        $headers = array("", "1. Books", "2. Play");
	$options = array("a", "b", "c");

        for ($i = 1; $i <3; $i++)
        {
                $this->form->addElement("static", null, "<b>$headers[$i]</b>");

		for ($j = 0; $j < 3; $j++)
		{
                	$group[] =&$this->form->createElement("static", "prompt_header2", "Prompt Level");
                	$group[] =&$this->form->createElement("static", "amount_header", "Quality of Response");
                	$this->form->addGroup($group, "communication_headers_{$i}_$options[$j]", "", $this->_GUIDelimiter, false);
                	unset($group);

                	$group[] = &$this->form->createElement("select", "prompt_{$i}_$options[$j]", null, $promptType);
                	$group[] = &$this->form->createElement("select", "prompt_amount_{$i}_$options[$j]", null, $promptAmount);
                	$this->form->addGroup($group, null, "$options[$j]. ", $this->_GUIDelimiter, false);
                	$this->addTextAreaElement("prompt{$i}_$options[$j]_notes", $this->indent . "Notes:");
        		unset($group);
                	unset($group);
		}

                $this->form->addElement("select", "free_play_additional_communication_$i", "d. Additional non-prompted communication", $this->yesNo);
                $this->form->addElement("select", "free_play_spontaneous_communication_$i", "e. Spontaneous communication not presented by clinician", $this->yesNo);
                $this->form->addElement("static", null, "<br/>");
                $this->form->addElement("static", null, "<br/>");
        }


//	$this->form->addElement("select", "validity_score", "<b>3. Validity Score</b>", array("null"=>"", "0_valid"=>"0 Valid", "1_questionable"=>"1 Questionable Validity", "2_invalid"=>"2 Invalid"));
        $this->addTextAreaElement("validity_notes", "Notes on validity score:");
//	$this->XINRegisterRule("validity_notes", array("validity_score{@}=={@}1_questionable|2_invalid"), "Required if validity score is 1 or 2", "validity_notes_group");
        $this->form->addElement("static", null, "<br/>");

	/*
        // Setting up the 6 column grid
        for($int = 1; $int <= 6; $int++) {
            $group[]= &$this->form->createElement("static", null, $this->indent);
        }
        $group[] = &$this->form->createElement("static", null, null);
        $group[]= &$this->form->createElement("static", "raw_score", null);
        $this->form->addGroup($group, null, null, $this->_GUIDelimiter, false);
        unset($group);
        
        //Understanding
        $this->form->addElement("header", null, "Understanding");
        $group[] = &$this->form->createElement("static", "object_names", null);
        for($col = 1; $col <= 4; $col++) {
            $group[] = &$this->form->createElement("text", "q_16_language_comp_objects_" . $col);
            $this->XINRegisterRule("q_16_language_comp_objects_" . $col, array("q_16_language_comp_objects_" . $col . "{@}=={@}NEVER_REQUIRED"), null, "q_16_language_comp_objects_group");
        }
        $group[] = &$this->form->createElement("static", null, null);
        $group[] = &$this->form->createElement("static", null, null);
        $group[] = &$this->form->createElement("static", "q_16_language_comp_raw_score");
        $this->form->addGroup($group, "q_16_language_comp_objects_group", "16. Language comprehension" . $this->indent, $this->_GUIDelimiter, false);
        unset($group);
        
        $group[] = &$this->form->createElement("static", "person_names", null);
        for($col = 1; $col <= 3; $col++) {
            $group[] = &$this->form->createElement("text", "q_16_language_comp_person_" . $col);
            $this->XINRegisterRule("q_16_language_comp_person_" . $col, array("q_16_language_comp_person_" . $col . "{@}=={@}NEVER_REQUIRED"), null, "q_16_language_comp_person_group");
        }
        $this->form->addGroup($group, "q_16_language_comp_person_group", null, $this->_GUIDelimiter, false);
        unset($group);

        $group[] = &$this->form->createElement("static", "body_parts", null);
        for($col = 1; $col <= 4; $col++) {
            $group[] = &$this->form->createElement("text", "q_16_language_comp_body_parts_" . $col);
            $this->XINRegisterRule("q_16_language_comp_body_parts_" . $col, array("q_16_language_comp_body_parts_" . $col . "{@}=={@}NEVER_REQUIRED"), null, "q_16_language_comp_body_parts_group");
        }
        $group[] = &$this->form->createElement("static", "q_16_language_comp_body_parts_raw_score");
        $this->form->addGroup($group, "q_16_language_comp_body_parts_group", null, $this->_GUIDelimiter, false);
        unset($group);

        $this->form->addElement("static", "understanding_weighted", "Understanding Weighted:");
        
        //Object Use
        $this->form->addElement("header", null, "Object Use");
        $group[] = &$this->form->createElement("advcheckbox", "q_17_action_schemes_puts_in", null, "puts in(1)", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_17_action_schemes_puts_on", null, "puts on(2)", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_17_action_schemes_drinks_with_bottle", null, "drinks with bottle(3)", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_17_action_schemes_drinks_with_cup", null, "drinks with cup(4)", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_17_action_schemes_hugs", null, "hugs(5)", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_17_action_schemes_kisses", null, "kisses(6)", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("static", null, null);
        $group[] = &$this->form->createElement("static", "q_17_action_schemes_raw_score");
        $this->form->addGroup($group, null, "17. Inventory of action schemes", $this->_GUIDelimiter, false);
        unset($group);

        $group[] = &$this->form->createElement("advcheckbox", "q_17_action_schemes_feeds_with_utensil", null, "feeds with utensil(7)", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_17_action_schemes_feeds_with_bowl", null, "feeds with bowl(8)", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_17_action_schemes_stirs", null, "stirs(9)", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_17_action_schemes_scoops", null, "scoops(10)", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_17_action_schemes_pours", null, "pours(11)", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_17_action_schemes_other", null, "other(12)", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("text", "q_17_action_schemes_other_specify");
        $this->form->addGroup($group, "q_17_action_schemes_group_2", null, $this->_GUIDelimiter, false);
        $this->XINRegisterRule("q_17_action_schemes_other_specify", array("q_17_action_schemes_other_specify{@}=={@}NEVER_REQUIRED"), null, "q_17_action_schemes_group_2");
        unset($group);
        
        
        //Stacks tower of blocks
        $group[] = &$this->form->createElement("select", "q_20_stacks_tower", "20. Stacks tower of blocks", array(null=>"", "0_refuses"=>"0 - Refuses",
                                "1_tries_but_fails"=>"1 - Tries but fails",
                                "2_stacks"=>"Stacks 2",
                                "3_stacks"=>"Stacks 3",
                                "4_stacks"=>"Stacks 4",
                                "5_stacks"=>"Stacks 5",
                                "not_answered"=>"Not Answered"));
        $group[] = &$this->form->createElement("static", null, null);
        $group[] = &$this->form->createElement("static", null, null);
        $group[] = &$this->form->createElement("static", null, null);
        $group[] = &$this->form->createElement("static", null, null);
        $group[] = &$this->form->createElement("static", null, null);
        $group[] = &$this->form->createElement("static", null, null);
        $group[] = &$this->form->createElement("static", "q_20_stacks_tower_raw_score");
        $this->form->addGroup($group, "q_20_stacks_tower_group", "20. Stacks tower of blocks", $this->_GUIDelimiter, false);
        unset($group); 

        $this->form->addElement("static", "object_use_weighted", "Object Use Weighted:");

    }
    
    function _countChecked($record, $genericLabel) {
        foreach ($record as $field=>$value) {
            if (ereg($genericLabel, $field)) {
                $score += ($value == "checked");
            }
        }
        return $score;
    }

    function _countWords($record, $genericLabel) {
        foreach($record as $field=>$value) {
            if(ereg($genericLabel, $field) && !is_null($value)) {
                $score++; 
            }
        }
        return $score;
    }
    
    function _printHeaderCols() {
        // Setting up the scoring grid
        for($int = 1; $int <= 6; $int++) {
            $group[]= &$this->form->createElement("static", "h_" . $int, null);
        }
        $group[]= &$this->form->createElement("static", "raw_score", null);
        $this->form->addGroup($group, "number_headers", "Sampling Opportunity", $this->_GUIDelimiter, false);
        unset($group);

        $group[]= &$this->form->createElement("static", "wind_up_toy", null);
        $group[]= &$this->form->createElement("static", "balloon", null);
        $group[]= &$this->form->createElement("static", "bubbles", null);
        $group[]= &$this->form->createElement("static", "jar", null);
        $group[]= &$this->form->createElement("static", "books", null);
        $group[]= &$this->form->createElement("static", "play", null);
        $this->form->addGroup($group, null, "Toy", $this->_GUIDelimiter, false);
        unset($group);
	*/

    }

}
?>
