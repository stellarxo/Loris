<?php
class NDB_BVL_Instrument_csbs extends NDB_BVL_Instrument
{
/*
INSERT INTO instrument_subtests VALUES('', 'csbs', 'csbs_page1', 'Scoring Worksheet', 1);
INSERT INTO instrument_subtests VALUES('', 'csbs', 'csbs_page2', 'Symbolic Behaviour Scales', 2);
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
        $this->localDefaults = array_merge($this->localDefaults, array("h_1"=>"1", "h_2"=>"2", "h_3"=>"3", "h_4"=>"4", "h_5"=>"5", "h_6"=>"6",
                                            "wind_up_toy"=>"Wind-up toy", "balloon"=>"Balloon", "bubbles"=>"Bubbles", "jar"=>"Jar",
                                            "books"=>"Books" . $this->indent . $this->indent . $this->indent . $this->indent . $this->indent . $this->indent . $this->indent,
                                            "play"=>"Play",
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

        $this->addTextElement("filled_out_by", "Filled out by:");
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
    
    function _page1(){
        
        // Setting up the scoring grid
        for($int = 1; $int <= 6; $int++) {
            $group[]= &$this->form->createElement("static", "h_" . $int, null);
        }
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
        
        //line break
        $this->form->addElement("static", null, $this->indent);
        
        //Emotion and Eye Gaze
        $this->form->addElement("header", null, "Emotion and Eye Gaze");
        for($int = 1; $int <= 6; $int++) {
            $group[] = &$this->form->createElement("advcheckbox", "q_1_gaze_shifts_" . $int, null, null, null, array("checked", "unchecked"));
        }
        $this->form->addGroup($group, null, "1. Gaze shifts", $this->_GUIDelimiter, false);
        unset($group);
        
        for($int = 1; $int <= 6; $int++) {
            $group[] = &$this->form->createElement("advcheckbox", "q_2_shared_positive_affect_" . $int, null, null, null, array("checked", "unchecked"));
        }
        $this->form->addGroup($group, null, "2. Shared positive affect", $this->_GUIDelimiter, false);
        unset($group);
        
        $group[] = &$this->form->createElement("static", null, null);
        $group[] = &$this->form->createElement("advcheckbox", "q_3_gaze_point_following_2" . $int, null, null, null, array("checked", "unchecked"));
        $group[] = &$this->form->createElement("static", null, null);
        $group[] = &$this->form->createElement("static", null, null);
        $group[] = &$this->form->createElement("advcheckbox", "q_3_gaze_point_following_5" . $int, null, null, null, array("checked", "unchecked"));
        
        $this->form->addGroup($group, null, "3. Gaze/point following", $this->_GUIDelimiter, false);
        unset($group);
        
        //Communication
        $this->form->addElement("header", null, "Communication");
        for($int = 1; $int <=6; $int++) {
            $group[] = &$this->form->createElement("select", "q_4_rate_of_communicating_" . $int, "", array(null=>"", "not_answered"=>"N/A", "0"=>"0", "1"=>"1", "2"=>"2", "3"=>"3+"));
        }
        $this->form->addGroup($group, null, "4. Rate of communication", $this->_GUIDelimiter, false);
        unset($group);
        
        for($int = 1; $int <= 6; $int++) {
            $group[] = &$this->form->createElement("advcheckbox", "q_5_behaviour_regulation_" . $int, null, null, null, array("checked", "unchecked"));
        }
        $this->form->addGroup($group, null, "5. Behaviour regulation", $this->_GUIDelimiter, false);
        unset($group);

        for($int = 1; $int <= 6; $int++) {
            $group[] = &$this->form->createElement("advcheckbox", "q_6_social_interaction_" . $int, null, null, null, array("checked", "unchecked"));
        }
        $this->form->addGroup($group, null, "6. Social interaction", $this->_GUIDelimiter, false);
        unset($group);
        
        for($int = 1; $int <= 6; $int++) {
            $group[] = &$this->form->createElement("advcheckbox", "q_7_joint_attention_" . $int, null, null, null, array("checked", "unchecked"));
        }
        $this->form->addGroup($group, null, "7. Joint attention", $this->_GUIDelimiter, false);
        unset($group);
        
        //Gestures
        $this->form->addElement("header", null, "Gestures");
        $group[] = &$this->form->createElement("advcheckbox", "q_8_conventional_gestures_gives", null, "gives", null, array("checked", "unchecked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_8_conventional_gestures_shows", null, "shows", null, array("checked", "unchecked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_8_conventional_gestures_pushes_pulls", null, "pushes/pulls", null, array("checked", "unchecked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_8_conventional_gestures_reaches", null, "reaches", null, array("checked", "unchecked"));
        $this->form->addGroup($group, null, "8. Inventory of conventional gestures", $this->_GUIDelimiter, false);
        unset($group);
        $group[] = &$this->form->createElement("advcheckbox", "q_8_conventional_gestures_points", null, "points", null, array("checked", "unchecked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_8_conventional_gestures_waves", null, "waves", null, array("checked", "unchecked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_8_conventional_gestures_nods_head", null, "nods head", null, array("checked", "unchecked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_8_conventional_gestures_shakes_head", null, "shakes head", null, array("checked", "unchecked"));
        $this->form->addGroup($group, null, null, $this->_GUIDelimiter, false);
        unset($group);

        for($int = 1; $int <=6; $int++) {
            $group[] = &$this->form->createElement("advcheckbox", "q_9_distal_gestures_" . $int, null, null, null, array("checked", "unchecked"));
        }
        $this->form->addGroup($group, null, "9. Distal gestures", $this->_GUIDelimiter, false);
        unset($group);
        
        //Sounds
        $this->form->addElement("header", null, "Sounds");
        for($int = 1; $int <=6; $int++) {
            $group[] = &$this->form->createElement("advcheckbox", "q_10_syllables_consonants_" . $int, null, null, null, array("checked", "unchecked"));
        }
        $this->form->addGroup($group, null, "10. Syllables with consonants", $this->_GUIDelimiter, false);
        unset($group);
        
        $group[] = &$this->form->createElement("advcheckbox", "q_11_inventory_of_consonants_m", null, "/m/", null, array("checked", "unchecked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_11_inventory_of_consonants_n", null, "/n/", null, array("checked", "unchecked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_11_inventory_of_consonants_b_p", null, "/b|p/", null, array("checked", "unchecked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_11_inventory_of_consonants_d_t", null, "/d|t/", null, array("checked", "unchecked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_11_inventory_of_consonants_g_k", null, "/g|k/", null, array("checked", "unchecked"));
        $this->form->addGroup($group, null, "11. Inventory of consonants", $this->_GUIDelimiter, false);
        unset($group);
        
        $group[] = &$this->form->createElement("advcheckbox", "q_11_inventory_of_consonants_w", null, "/w/", null, array("checked", "unchecked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_11_inventory_of_consonants_l", null, "/l/", null, array("checked", "unchecked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_11_inventory_of_consonants_y", null, "/y/", null, array("checked", "unchecked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_11_inventory_of_consonants_s", null, "/s/", null, array("checked", "unchecked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_11_inventory_of_consonants_sh", null, "/sh/", null, array("checked", "unchecked"));
        $this->form->addGroup($group, null, null, $this->_GUIDelimiter, false);
        unset($group);
        
        //Words
        $this->form->addElement("header", null, "Words");
        for($int = 1; $int <=6; $int++) {
            $group[] = &$this->form->createElement("advcheckbox", "q_12_words_" . $int, null, null, null, array("checked", "unchecked"));
        }
        $this->form->addGroup($group, null, "12. Words", $this->_GUIDelimiter, false);
        unset($group);
        
        for($row = 0; $row <= 3; $row++) {
            for($col = 1; $col <= 4; $col++) {
                $group[] = &$this->form->createElement("text", "q_13_words_" . ($col + ($row * 4)) );
            }
            if ($row == 0) {$label = "13. Inventory of words";} else {$label = null;}
            $this->form->addGroup($group, "q_13_words_{$row}_group", $label, $this->_GUIDelimiter, false);
            unset($group);
            for($int = 1; $int <= 16; $int++) {
               $this->XINRegisterRule("q_13_words_" . $int, array("q_13_words_" . $int . "{@}=={@}NEVER_REQUIRED"), null, "q_13_words_" . intval($int / 4) . "_group");
            }
        }

        for($int = 1; $int <=6; $int++) {
            $group[] = &$this->form->createElement("advcheckbox", "q_14_word_combos_" . $int, null, null, null, array("checked", "unchecked"));
        }
        $this->form->addGroup($group, null, "14. Word combinations", $this->_GUIDelimiter, false);
        unset($group);
        
        for($row = 0; $row <= 3; $row++) {
            for($col = 1; $col <= 2; $col++) {
                $group[] = &$this->form->createElement("text", "q_15_word_combos_" . ($col + ($row * 2)) );
            }
            if ($row == 0) {$label = "15. Inventory of word combos";} else {$label = null;}
            $this->form->addGroup($group, "q_15_word_combos_{$row}_group", $label, $this->_GUIDelimiter, false);
            unset($group);
            for($int = 1; $int <= 8; $int++) {
               $this->XINRegisterRule("q_15_word_combos_" . $int, array("q_15_word_combos_" . $int . "{@}=={@}NEVER_REQUIRED"), null, "q_15_word_combos_" . intval($int / 2) . "_group");
            }
        }
    }
    
    function _page2() {
        // Setting up the 6 column grid
        for($int = 1; $int <= 6; $int++) {
            $group[]= &$this->form->createElement("static", null, $this->indent);
        }
        $this->form->addGroup($group, null, null, $this->_GUIDelimiter, false);
        unset($group);
        
        //Understanding
        $this->form->addElement("header", null, "Understanding");
        $group[] = &$this->form->createElement("static", "object_names", null);
        for($col = 1; $col <= 4; $col++) {
            $group[] = &$this->form->createElement("text", "q_16_language_comp_objects_" . $col);
            $this->XINRegisterRule("q_16_language_comp_objects_" . $col, array("q_16_language_comp_objects_" . $col . "{@}=={@}NEVER_REQUIRED"), null, "q_16_language_comp_objects_group");
        }
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
        $this->form->addGroup($group, "q_16_language_comp_body_parts_group", null, $this->_GUIDelimiter, false);
        unset($group);

        //Object Use
        $this->form->addElement("header", null, "Object Use");
        $group[] = &$this->form->createElement("advcheckbox", "q_17_action_schemes_puts_in", null, "puts in(1)", null, array("checked", "unchecked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_17_action_schemes_puts_on", null, "puts on(2)", null, array("checked", "unchecked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_17_action_schemes_drinks_with_bottle", null, "drinks with bottle(3)", null, array("checked", "unchecked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_17_action_schemes_drinks_with_cup", null, "drinks with cup(4)", null, array("checked", "unchecked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_17_action_schemes_hugs", null, "hugs(5)", null, array("checked", "unchecked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_17_action_schemes_kisses", null, "kisses(6)", null, array("checked", "unchecked"));
        $this->form->addGroup($group, null, "17. Inventory of action schemes", $this->_GUIDelimiter, false);
        unset($group);

        $group[] = &$this->form->createElement("advcheckbox", "q_17_action_schemes_feeds_with_utensil", null, "feeds with utensil(7)", null, array("checked", "unchecked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_17_action_schemes_feeds_with_bowl", null, "feeds with bowl(8)", null, array("checked", "unchecked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_17_action_schemes_stirs", null, "stirs(9)", null, array("checked", "unchecked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_17_action_schemes_scoops", null, "scoops(10)", null, array("checked", "unchecked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_17_action_schemes_pours", null, "pours(11)", null, array("checked", "unchecked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_17_action_schemes_other", null, "other(12)", null, array("checked", "unchecked"));
        $group[] = &$this->form->createElement("text", "q_17_action_schemes_other_specify");
        $this->form->addGroup($group, "q_17_action_schemes_group_2", null, $this->_GUIDelimiter, false);
        $this->XINRegisterRule("q_17_action_schemes_other_specify", array("q_17_action_schemes_other_specify{@}=={@}NEVER_REQUIRED"), null, "q_17_action_schemes_group_2");
        unset($group);
        
        //Action schemes towards other
        for($int = 1; $int <= 6; $int++) {
            $group[] = &$this->form->createElement("text", "q_18_actions_towards_other_" . $int, null);
        }
        $this->form->addGroup($group, "q_18_actions_towards_other_group", "18. Action schemes towards other", $this->_GUIDelimiter, false);
        unset($group);
        for($int = 1; $int <= 6; $int++) {
            $this->XINRegisterRule("q_18_actions_towards_other_" . $int, array("q_18_actions_towards_other_" . $int . "{@}=={@}NEVER_REQUIRED"), null, "q_18_actions_towards_other_group");
        }
        
        //Sequence action schemes
        for($int = 1; $int <= 6; $int++) {
            $group[] = &$this->form->createElement("text", "q_19_sequence_action_schemes_" . $int, null);
        }
        $this->form->addGroup($group, "q_19_sequence_action_schemes_group", "19. Sequence action schemes", $this->_GUIDelimiter, false);
        unset($group);
        for($int = 1; $int <= 6; $int++) {
            $this->XINRegisterRule("q_19_sequence_action_schemes_" . $int, array("q_19_sequence_action_schemes_" . $int . "{@}=={@}NEVER_REQUIRED"), null, "q_19_sequence_action_schemes_group");
        }
        
        //Stacks tower of blocks
        $this->form->addElement("select", "q_20_stacks_tower", "20. Stacks tower of blocks", array(null=>"", "0_refuses"=>"0 - Refuses",
                                "1_tries_but_fails"=>"1 - Tries but fails",
                                "2_stacks"=>"Stacks 2",
                                "3_stacks"=>"Stacks 3",
                                "4_stacks"=>"Stacks 4",
                                "5_stacks"=>"Stacks 5",
                                "not_answered"=>"Not Answered"));

    }
    
}
?>