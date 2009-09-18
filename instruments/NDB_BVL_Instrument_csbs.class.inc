<?php
class NDB_BVL_Instrument_csbs extends NDB_BVL_Instrument
{
/*
INSERT INTO instrument_subtests VALUES('', 'csbs', 'csbs_page1', 'Scoring Worksheet', 1);
INSERT INTO instrument_subtests VALUES('', 'csbs', 'csbs_page2', 'Symbolic Behaviour Scales', 2);
*/
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
        $this->testName = "csbs";           // test_names.Test_name
        $this->table = 'csbs';              // name of database table corresponding to instrument
        // data keyed by commentID
        $this->commentID = $commentID;
        
        //The array of dates/timestamps to convert to database dates/timestamps
        //Any HTML_Quickform date elements must be listed here
        $this->dateTimeFields=array("Date_taken");
            
        //The array of selects with multiple answers allowed
        //Any HTML_Quickform multiple selects must be listed here
        $this->_selectMultipleElements = array();

        // required fields for data entry completion status
        $this->_requiredElements = array('Examiner', "q_4_rate_of_communicating_1", "q_20_stacks_tower");

        //Column headers
        $this->localDefaults = array_merge($this->localDefaults, array("h_1"=>"1", "h_2"=>"2", "h_3"=>"3", "h_4"=>"4", "h_5"=>"5", "h_6"=>"6", "raw_score"=>"Raw Score",
                                            "wind_up_toy"=>"Wind-up toy", "balloon"=>"Balloon", "bubbles"=>"Bubbles", "jar"=>"Jar",
                                            "books"=>"Books" . $this->indent . $this->indent . $this->indent . $this->indent . $this->indent . $this->indent . $this->indent,
                                            "play"=>"Play" . $this->indent . $this->indent . $this->indent . $this->indent . $this->indent . $this->indent . $this->indent,
                                            "object_names"=>"object names:", "person_names"=>"person names:", "body_parts"=>"body parts:"));

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
        if(ereg("csbs(_page[0-9]+)",$this->page,$matches)){
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
        $this->form->addElement('header', 'instrument_title', "Communication and Symbolic Behaviour Scales - Development Profile");
        
        // automatically adds examiner & date of administration
        $this->_addMetadataFields();

//        $this->addTextElement("filled_out_by", "Filled out by:");
        $this->addTextElement("relationship_to_child", "Relationship to child:");
        
        $this->form->addElement("static", null, "Circle the response that comes closest to your observations.");
        
        $this->form->addElement("select", "q_1_alertness", "1. Alertness", array(null=>"", "1_less_than_usual"=>"1. less than usual/sleepy", "2_typical"=>"2. typical", "3_very_alert_greater"=>"3. very alert / greater than usual", "not_answered"=>"Not Answered"));
        $this->form->addElement("select", "q_2_emotional_reaction", "2. Emotional reaction", array(null=>"", "1_more_negative"=>"1. more negative than usual", "2_typical"=>"2. typical", "3_more_positive"=>"3. more positive than usual", "not_answered"=>"Not Answered"));
        $this->form->addElement("select", "q_3_level_of_interest", "3. Level of interest and attention", array(null=>"", "1_less_interest"=>"1. less interest than usual", "2_typical"=>"2. typical", "3_greater"=>"3. greater interest / greater attention", "not_answered"=>"Not Answered"));
        $this->form->addElement("select", "q_4_comfort_level", "4. Comfort level", array(null=>"", "1_more_cautious"=>"1. more cautious", "2_typical"=>"2. typical", "3_more_comfortable"=>"3. more confortable", "not_answered"=>"Not Answered"));
        $this->form->addElement("select", "q_5_level_of_activity", "5. Level of activity", array(null=>"", "1_less_active"=>"1. less active than usual", "2_typical"=>"2. typical", "3_more_active"=>"3. more active than usual", "not_answered"=>"Not Answered"));
        $this->form->addElement("select", "q_6_level_of_communication", "6. Overall level of communication", array(null=>"", "1_less_than_usual"=>"1. less than usual", "2_typical"=>"2. typical", "3_greater_than_usual"=>"3. greater than usual", "not_answered"=>"Not Answered"));
        $this->form->addElement("select", "q_7_play_behaviour", "7. Play behavior", array(null=>"", "1_less_organized"=>"1. less organized", "2_typical"=>"2. typical", "3_more_organized"=>"3. more organized", "not_answered"=>"Not Answered"));
//        $this->form->addElement("select", "q_", "", array(null=>"", "1_"=>"1. ", "2_typical"=>"2. typical", "3_"=>"3. ", "not_answered"=>"Not Answered"));

        $this->addTextAreaElement("comments", "Comments:");    
    }
    
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

        $scores["communication_weighted"] = $scores["q_4_rate_of_communicating_raw_score"] / 3 +
        $scores["q_5_behaviour_regulation_raw_score"] +
        $scores["q_6_social_interaction_raw_score"] +
        $scores["q_7_joint_attention_raw_score"];

        $scores["gestures_weighted"] = $scores["q_8_conventional_gestures_raw_score"] * 2 + 
        $scores["q_9_distal_gestures_raw_score"];

        $scores["sounds_weighted"] = $scores["q_10_syllables_consonants_raw_score"] +
        2 * $scores["q_11_inventory_of_consonants_raw_score"];

        $scores["words_weighted"] = $scores["q_12_words_raw_score"] +
        $scores["q_13_words_raw_score"] / 2 +  
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

        //save scores
		$result = $db->update($this->table, $scores, array("CommentID"=>$this->getCommentID()));
		if($db->isError($result)) {
			return PEAR::raiseError("Could not save total score: ". $result->getMessage());
		}
		
    }    

    function _page1(){
        //Emotion and Eye Gaze
        $this->form->addElement("header", null, "Emotion and Eye Gaze");
        $this->_printHeaderCols();
        for($int = 1; $int <= 6; $int++) {
            $group[] = &$this->form->createElement("advcheckbox", "q_1_gaze_shifts_" . $int, null, null, null, array("unchecked", "checked"));
        }
        $group[] = &$this->form->createElement("static", "q_1_gaze_shifts_raw_score");
        $this->form->addGroup($group, null, "1. Gaze shifts", $this->_GUIDelimiter, false);
        unset($group);
        
        for($int = 1; $int <= 6; $int++) {
            $group[] = &$this->form->createElement("advcheckbox", "q_2_shared_positive_affect_" . $int, null, null, null, array("unchecked", "checked"));
        }
        $group[] = &$this->form->createElement("static", "q_2_shared_positive_affect_raw_score");
        $this->form->addGroup($group, null, "2. Shared positive affect", $this->_GUIDelimiter, false);
        unset($group);
        
        $group[] = &$this->form->createElement("static", null, null);
        $group[] = &$this->form->createElement("advcheckbox", "q_3_gaze_point_following_2", null, null, null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("static", null, null);
        $group[] = &$this->form->createElement("static", null, null);
        $group[] = &$this->form->createElement("advcheckbox", "q_3_gaze_point_following_5", null, null, null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("static", null, null);
        $group[] = &$this->form->createElement("static", "q_3_gaze_point_following_raw_score");

        $this->form->addGroup($group, null, "3. Gaze/point following", $this->_GUIDelimiter, false);
        unset($group);
        
        $this->form->addElement("static", "emotion_eye_gaze_weighted", "Emotion and Eye Gaze Weighted:");
        
        //Communication
        $this->form->addElement("header", null, "Communication");
        $this->_printHeaderCols();
        for($int = 1; $int <=6; $int++) {
            $group[] = &$this->form->createElement("select", "q_4_rate_of_communicating_" . $int, "", array(null=>"", "not_answered"=>"N/A", "0"=>"0", "1"=>"1", "2"=>"2", "3"=>"3+"));
            $this->XINRegisterRule("q_4_rate_of_communicating_" . $int, array("q_4_rate_of_communicating_" . $int . "{@}=={@}"), "Responses are required for each sampling opportunity.", "q_4_rate_of_communicating_group");
        }
        $group[] = &$this->form->createElement("static", "q_4_rate_of_communicating_raw_score");
        $this->form->addGroup($group, "q_4_rate_of_communicating_group", "4. Rate of communication", $this->_GUIDelimiter, false);
        unset($group);
        
        for($int = 1; $int <= 6; $int++) {
            $group[] = &$this->form->createElement("advcheckbox", "q_5_behaviour_regulation_" . $int, null, null, null, array("unchecked", "checked"));
        }
        $group[] = &$this->form->createElement("static", "q_5_behaviour_regulation_raw_score");
        $this->form->addGroup($group, null, "5. Behaviour regulation", $this->_GUIDelimiter, false);
        unset($group);

        for($int = 1; $int <= 6; $int++) {
            $group[] = &$this->form->createElement("advcheckbox", "q_6_social_interaction_" . $int, null, null, null, array("unchecked", "checked"));
        }
        $group[] = &$this->form->createElement("static", "q_6_social_interaction_raw_score");
        $this->form->addGroup($group, null, "6. Social interaction", $this->_GUIDelimiter, false);
        unset($group);
        
        for($int = 1; $int <= 6; $int++) {
            $group[] = &$this->form->createElement("advcheckbox", "q_7_joint_attention_" . $int, null, null, null, array("unchecked", "checked"));
        }
        $group[] = &$this->form->createElement("static", "q_7_joint_attention_raw_score");
        $this->form->addGroup($group, null, "7. Joint attention", $this->_GUIDelimiter, false);
        unset($group);
        
        $this->form->addElement("static", "communication_weighted", "Communication Weighted:");

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

        //Sounds
        $this->form->addElement("header", null, "Sounds");
        $this->_printHeaderCols();

        for($int = 1; $int <=6; $int++) {
            $group[] = &$this->form->createElement("advcheckbox", "q_10_syllables_consonants_" . $int, null, null, null, array("unchecked", "checked"));
        }
        $group[] = &$this->form->createElement("static", "q_10_syllables_consonants_raw_score");
        $this->form->addGroup($group, null, "10. Syllables with consonants", $this->_GUIDelimiter, false);
        unset($group);
        
        $group[] = &$this->form->createElement("advcheckbox", "q_11_inventory_of_consonants_m", null, "/m/", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_11_inventory_of_consonants_n", null, "/n/", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_11_inventory_of_consonants_b_p", null, "/b|p/", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_11_inventory_of_consonants_d_t", null, "/d|t/", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_11_inventory_of_consonants_g_k", null, "/g|k/", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("static", null, null);
        $group[] = &$this->form->createElement("static", "q_11_inventory_of_consonants_raw_score");
        $this->form->addGroup($group, null, "11. Inventory of consonants", $this->_GUIDelimiter, false);
        unset($group);
        
        $group[] = &$this->form->createElement("advcheckbox", "q_11_inventory_of_consonants_w", null, "/w/", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_11_inventory_of_consonants_l", null, "/l/", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_11_inventory_of_consonants_y", null, "/y/", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_11_inventory_of_consonants_s", null, "/s/", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_11_inventory_of_consonants_sh", null, "/sh/", null, array("unchecked", "checked"));
        $this->form->addGroup($group, null, null, $this->_GUIDelimiter, false);
        unset($group);

        $this->form->addElement("static", "sounds_weighted", "Sounds Weighted:");

        //Words
        $this->form->addElement("header", null, "Words");
        $this->_printHeaderCols();

        for($int = 1; $int <=6; $int++) {
            $group[] = &$this->form->createElement("advcheckbox", "q_12_words_" . $int, null, null, null, array("unchecked", "checked"));
        }
        $group[] = &$this->form->createElement("static", "q_12_words_raw_score");
        $this->form->addGroup($group, null, "12. Words", $this->_GUIDelimiter, false);
        unset($group);
        
        for($row = 0; $row <= 3; $row++) {
            for($col = 1; $col <= 4; $col++) {
                $group[] = &$this->form->createElement("text", "q_13_words_" . ($col + ($row * 4)) );
            }
            if ($row == 0) {
                $label = "13. Inventory of words";
                $group[] = &$this->form->createElement("static", null, null);
                $group[] = &$this->form->createElement("static", null, null);
                $group[] = &$this->form->createElement("static", "q_13_words_raw_score");
            } else {$label = null;}
            $this->form->addGroup($group, "q_13_words_{$row}_group", $label, $this->_GUIDelimiter, false);
            unset($group);
            for($int = 1; $int <= 16; $int++) {
               $this->XINRegisterRule("q_13_words_" . $int, array("q_13_words_" . $int . "{@}=={@}NEVER_REQUIRED"), null, "q_13_words_" . intval($int / 4) . "_group");
            }
        }

        for($int = 1; $int <=6; $int++) {
            $group[] = &$this->form->createElement("advcheckbox", "q_14_word_combos_" . $int, null, null, null, array("unchecked", "checked"));
        }
        $group[] = &$this->form->createElement("static", "q_14_word_combos_raw_score");
        $this->form->addGroup($group, null, "14. Word combinations", $this->_GUIDelimiter, false);
        unset($group);
        
        for($row = 0; $row <= 3; $row++) {
            for($col = 1; $col <= 2; $col++) {
                $group[] = &$this->form->createElement("text", "q_15_word_combos_" . ($col + ($row * 2)) );
            }
            if ($row == 0) {$label = "15. Inventory of word combos";
                $group[] = &$this->form->createElement("static", null, null);
                $group[] = &$this->form->createElement("static", null, null);
                $group[] = &$this->form->createElement("static", null, null);
                $group[] = &$this->form->createElement("static", null, null);
                $group[] = &$this->form->createElement("static", "q_15_word_combos_raw_score");
            } else {$label = null;}
            $this->form->addGroup($group, "q_15_word_combos_{$row}_group", $label, $this->_GUIDelimiter, false);
            unset($group);
            for($int = 1; $int <= 8; $int++) {
               $this->XINRegisterRule("q_15_word_combos_" . $int, array("q_15_word_combos_" . $int . "{@}=={@}NEVER_REQUIRED"), null, "q_15_word_combos_" . intval($int / 2) . "_group");
            }
        }
        $this->form->addElement("static", "words_weighted", "Words Weighted:");

    }
    
    function _page2() {
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
        
        //Action schemes towards other
        for($int = 1; $int <= 6; $int++) {
            $group[] = &$this->form->createElement("text", "q_18_actions_towards_other_" . $int, null);
        }
        $group[] = &$this->form->createElement("static", null, null);
        $group[] = &$this->form->createElement("static", "q_18_actions_towards_other_raw_score");
        $this->form->addGroup($group, "q_18_actions_towards_other_group", "18. Action schemes towards other", $this->_GUIDelimiter, false);
        unset($group);
        for($int = 1; $int <= 6; $int++) {
            $this->XINRegisterRule("q_18_actions_towards_other_" . $int, array("q_18_actions_towards_other_" . $int . "{@}=={@}NEVER_REQUIRED"), null, "q_18_actions_towards_other_group");
        }
        
        //Sequence action schemes
        for($int = 1; $int <= 6; $int++) {
            $group[] = &$this->form->createElement("text", "q_19_sequence_action_schemes_" . $int, null);
        }
        $group[] = &$this->form->createElement("static", null, null);
        $group[] = &$this->form->createElement("static", "q_19_sequence_action_schemes_raw_score");
        $this->form->addGroup($group, "q_19_sequence_action_schemes_group", "19. Sequence action schemes", $this->_GUIDelimiter, false);
        unset($group);
        for($int = 1; $int <= 6; $int++) {
            $this->XINRegisterRule("q_19_sequence_action_schemes_" . $int, array("q_19_sequence_action_schemes_" . $int . "{@}=={@}NEVER_REQUIRED"), null, "q_19_sequence_action_schemes_group");
        }
        
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
    }

}
?>