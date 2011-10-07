<?php

class NDB_BVL_Instrument_csbs_sponteneity extends NDB_BVL_Instrument
{

/*
INSERT INTO test_names VALUES('', 'csbs_sponteneity', 'CSBS Sponeneity Coding Sheet', 0, 1, NULL);

INSERT INTO test_battery VALUES ('', 'csbs_sponteneity', '0', '420', 'Y', 'Visit', '1', NULL);

INSERT INTO instrument_subtests VALUES('', 'csbs_sponteneity', 'csbs_sponteneity_page1', 'Child Approach / Structured Communication Activities', 1);
INSERT INTO instrument_subtests VALUES('', 'csbs_sponteneity', 'csbs_sponteneity_page2', 'Free Play', 2);
*/
	var $yesNo = array(null=>"", "yes"=>"Yes", "no"=>"No", "not_answered"=>"Not Answered");


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
            "object_names"=>"object names:", "person_names"=>"person names:", "body_parts"=>"body parts:", "subscale"=>"Subscale", 
            "raw_weighted"=>"Weighted Raw Score", "standard_score"=>"Standard Score","percentile_rank"=>"Percentile Rank", 
            "prompt_header"=>"Prompt level", "response_header"=>"Quality of response", "prompt_header2"=>"Type of prompt", 
            "amount_header"=>"Amount of prompting", "other_header"=>"Other - specify"));

        //Array of column names to be ignored by the double data entry conflict detector.
        $this->_doubleDataEntryDiffIgnoreColumns = array('CommentID', 'UserID', 'Testdate', 'Window_Difference', 'Candidate_Age',
            'relationship_to_child', 'relationship_to_child_status', 'comments', 'comments_status',
			'q_13_words_1', 'q_13_words_2', 'q_13_words_3', 'q_13_words_4', 'q_13_words_5', 'q_13_words_6',
            'q_13_words_7', 'q_13_words_8', 'q_13_words_9', 'q_13_words_10', 'q_13_words_11', 'q_13_words_12',
            'q_13_words_13', 'q_13_words_14', 'q_13_words_15', 'q_13_words_16', 'q_15_word_combos_1', 'q_15_word_combos_2',
            'q_15_word_combos_3', 'q_15_word_combos_4', 'q_15_word_combos_5', 'q_15_word_combos_6', 'q_15_word_combos_7', 'q_15_word_combos_8',
            'q_16_language_comp_objects_1', 'q_16_language_comp_objects_2', 'q_16_language_comp_objects_3', 'q_16_language_comp_objects_4',
            'q_16_language_comp_person_1', 'q_16_language_comp_person_2', 'q_16_language_comp_person_3', 'q_16_language_comp_body_parts_1',
            'q_16_language_comp_body_parts_2', 'q_16_language_comp_body_parts_3', 'q_16_language_comp_body_parts_4', 'q_18_actions_towards_other_1',
            'q_18_actions_towards_other_2', 'q_18_actions_towards_other_3', 'q_18_actions_towards_other_4', 'q_18_actions_towards_other_5', 
            'q_18_actions_towards_other_6', 'q_19_sequence_action_schemes_1', 'q_19_sequence_action_schemes_2', 'q_19_sequence_action_schemes_3',
            'q_19_sequence_action_schemes_4', 'q_19_sequence_action_schemes_5', 'q_19_sequence_action_schemes_6');

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
    }

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

        for ($i = 1; $i <5; $i++) {
            $this->form->addElement("static", null, "<b>$headers[$i]</b>");
            for ($j = 1; $j<3; $j++) {
                /*
                $group[] =&$this->form->createElement("static", "prompt_header", "Prompt Level");
                $group[] =&$this->form->createElement("static", "response_header", "Quality of Response");
                $group[] =&$this->form->createElement("static", "other_header", "Other - specify");
                */
                $group[] =&$this->form->createElement("static", null, "Prompt Level");
                $group[] =&$this->form->createElement("static", null, "Quality of Response");
                $group[] =&$this->form->createElement("static", null, "Other - specify");
                $this->form->addGroup($group, "wind_up_headers_$j" . "_$i", "", $this->_GUIDelimiter, false);
                unset($group);

                $group[] = &$this->form->createElement("select", "wind_up_ph{$j}_$i", null, $promptLevel);
                $group[] = &$this->form->createElement("select", "wind_up_ph{$j}_response_$i", null, $qualityResponse);
                $group[] = &$this->form->createElement("text", "wind_up_ph{$j}_other_$i", null);
                        $this->XINRegisterRule("wind_up_ph{$j}_$i", array("wind_up_ph{$j}_$i{@}=={@}NEVER_REQUIRED"));
                        $this->XINRegisterRule("wind_up_ph{$j}_response_$i", array("wind_up_ph{$j}_response_$i{@}=={@}NEVER_REQUIRED"));
                        $this->XINRegisterRule("wind_up_ph{$j}_other_$i", array("wind_up_ph{$j}_other_$i{@}=={@}NEVER_REQUIRED"));


                if ($j == 1) {
                    $this->form->addGroup($group, null, "a. PH $j", $this->_GUIDelimiter, false);
                } else {
                    $this->form->addGroup($group, null, "b. PH $j", $this->_GUIDelimiter, false);
                }
            
                $this->addTextAreaElement("ph{$j}_notes", $this->indent . "Notes:");
                unset($group);
            }

            $this->form->addElement("select", "wind_up_additional_communication_$i", "c. Additional non-prompted communication", $this->yesNo);
            $this->form->addElement("select", "wind_up_spontaneous_communication_$i", "d. Spontaneous communication not presented by clinician", $this->yesNo);
            $this->form->addElement("static", null, "<br/>");		
            $this->form->addElement("static", null, "<br/>");		
        }

    }
    
    function _page2() {
	
        $this->form->addElement("header", null, "Free Play Activities");

        $promptType = array(null=>"", "verbal"=>"V", "gesture"=>"G", "verbal_and_gesture"=>"V+G", "independent"=>"I", "nc"=>"No Communication");
        $promptAmount = array(null=>"", "0_initiates_prior_prompt"=>"0", "1"=>"1", "2"=>"2", "3"=>"3", "4"=>"4", "5"=>"5", "nc"=>"No Communication");

        $headers = array("", "1. Books", "2. Play");
        $options = array("a", "b", "c");

        for ($i = 1; $i <3; $i++) {
            $this->form->addElement("static", null, "<b>$headers[$i]</b>");

            for ($j = 0; $j < 3; $j++) {
                $group[] =&$this->form->createElement("static", "prompt_header2", "Prompt Level");
                $group[] =&$this->form->createElement("static", "amount_header", "Quality of Response");
                $this->form->addGroup($group, "communication_headers_{$i}_$options[$j]", "", $this->_GUIDelimiter, false);
                unset($group);

                $group[] = &$this->form->createElement("select", "prompt_{$i}_$options[$j]", null, $promptType);
                $group[] = &$this->form->createElement("select", "prompt_amount_{$i}_$options[$j]", null, $promptAmount);
                $this->form->addGroup($group, null, "$options[$j]. ", $this->_GUIDelimiter, false);
                $this->addTextAreaElement("prompt{$i}_$options[$j]_notes", $this->indent . "Notes:");
                unset($group);
            }

            $this->form->addElement("select", "free_play_additional_communication_$i", "d. Additional non-prompted communication", $this->yesNo);
            $this->form->addElement("select", "free_play_spontaneous_communication_$i", "e. Spontaneous communication not presented by clinician", $this->yesNo);
            $this->form->addElement("static", null, "<br/>");
            $this->form->addElement("static", null, "<br/>");
        }

        $this->addTextAreaElement("validity_notes", "Notes on validity score:");
        $this->form->addElement("static", null, "<br/>");
    }

}
?>
