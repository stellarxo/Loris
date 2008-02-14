<?php
class NDB_BVL_Instrument_adi_r extends NDB_BVL_Instrument
{
/*
DoB Proband should be somewhere in the candidate table.  For now, we'll just make it a form entry.  Will need quite a large range of dates as probands may be quite old.

*/

	//Commonly used level of indentation;
	var $indent = "&nbsp;&nbsp;&nbsp;&nbsp;";
	
	var $yesNoNA = array(''=>NULL, '0_no'=>"0. No", '1_yes'=>"1. Yes", 'not_answered'=>"Not answered");
	
	var $respondentAgeMonths;
	
    /**
    * array of scoring fields
    */
    var $scoreCols = array("Total_A1", "Total_A2", "Total_A3", "Total_A4", "A_Total",
    						"Total_B1", "Total_B4", "Total_B2V", "Total_B3V", "BV_Total", "BNV_Total",
    						"Total_C1", "Total_C2", "Total_C3", "Total_C4", "C_Total");

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
        
        // data keyed by commentID
        $this->commentID = $commentID;
        
        //The array of dates/timestamps to convert to database dates/timestamps
        //Any HTML_Quickform date elements must be listed here
        $this->dateTimeFields=array("Date_taken", 'DoB_proband'); //remove DoB_proband
            
        //The array of selects with multiple answers allowed
        //Any HTML_Quickform multiple selects must be listed here
        $this->_selectMultipleElements = array();

        // required fields for data entry completion status
        $this->_requiredElements = array('Examiner', "q_11_loss_of_language", "q_20_loss_of_skills_code", "q_30_overall_level_of_language",
        								"q_41_current_communicative_speech_current_code", "q_50_direct_gaze_current_code",
        								"q_60_initiation_of_activities_current_code", "q_67_unusual_preoccupations_current_code",
        								"q_80_gait_current_code", "q_88_visuospatial_ability_current_code");

		//For testing purposes only...
        $this->respondentAgeMonths = 121;

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
        if(ereg("(_page[0-9]+)",$this->page,$matches)){
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
        // display test name
        $this->form->addElement('header', 'instrument_title', "ADI-R");
        
        // automatically adds examiner & date of administration
        $this->_addMetadataFields();
        
        $this->form->addElement("text", "informant_relation", "Informant relation to subject:");
        
        $config =& NDB_Config::singleton();
        $dateOptions = array(
        'language' => 'en',
        'format'   => 'YMd',
        'minYear'  => $config->getSetting('startYear') - 20, //allows for proband siblings up to 20 years older than candidate
        'maxYear'  => $config->getSetting('endYear'),
        'addEmptyOption' => true,
        'emptyOptionValue' => null
        );

        if (ereg("proband", $this->testName)) {
            $this->form->addElement('date', 'DoB_proband', 'DoB Proband', $dateOptions);
        }
        
        $this->form->addElement("header", null, "Scores");
		$scoreLabels = array("Total_A1"=>"Total A1",
							"Total_A2"=>"Total A2",
							"Total_A3"=>"Total A3",
							"Total_A4"=>"Total A4",
							"A_Total"=>"A Total",
							"Total_B1"=>"Total B1",
							"Total_B4"=>"Total B4",
							"Total_B2V"=>"Total B2(V)",
							"Total_B3V"=>"Total B3V",
							"BV_Total"=>"B(V) Total",
							"BNV_Total"=>"B(NV) Total",
							"Total_C1"=>"Total C1",
							"Total_C2"=>"Total C2",
							"Total_C3"=>"Total C3",
							"Total_C4"=>"Total C4",
							"C_Total"=>"C Total");
		foreach ($scoreLabels as $field=>$label) {
			if(in_array($field, array("A_Total", "BV_Total", "BNV_Total", "C_Total")) == TRUE) {
				$label = $this->indent . $this->indent . $label;
			}
	        $this->form->addElement("static", $field, $label);
		}

    }

    function _score() {
        // skip scoring if proband DoB was not entered, i.e. data entry is not completed
        if(empty($this->respondentAgeMonths)){
            return;
        }
        
        //skip scoring if all data has not yet been entered.
        if($this->_determineDataEntryCompletionStatus() == "Incomplete") {
        	return;
        }
        
        $db =& Database::singleton();
        if(PEAR::isError($db)) {
            return PEAR::raiseError ("Could not connect to database: ".$db->getMessage());
        }

        // null scores
        $this->_nullScores($this->scoreCols);

        // Get the item scores
        $query = "SELECT * FROM $this->table WHERE CommentID='".$this->getCommentID()."'";
        $record=array();
        $db->selectRow($query, $record);
        if (PEAR::isError($record)) {
            return PEAR::raiseError("Could not get scores: ".$record->getMessage());
        }
        
        // Get the age
//        $age = $record["DoB_proband"];  //don't use it quite yet
    	
        //convert items codes to algorithm scores
        $conversion = array(0=>0, 1=>1, 2=>2, 3=>2, 7=>0, 8=>0, 9=>0);
        foreach ($record as $field=>$code) {
        	$scores[$field] = substr($code, 0, 1);
        	if(is_numeric($scores[$field])) {
        		$scores[$field] = $conversion[$scores[$field]];
        	} else {
        		$scores[$field] = 0;  //for 'not_answered'
        	}
        }
        
        //perform the score calculations
        if($this->respondentAgeMonths >= 24 && $this->respondentAgeMonths <= 47) {
	        //Age 2 Years to 3 Years, 11 Months => 24months...47months
	        $scoreCols["Total_A1"] = $scores["q_50_direct_gaze_current_code"] + $scores["q_51_social_smiling_current_code"] 
									+ $scores["q_57_range_of_racial_expressions_current_code"];
			$scoreCols["Total_A2"] = $scores["q_62_interest_in_children_current_code"] + $scores["q_63_response_to_approaches_current_code"];
			$scoreCols["Total_A3"] = $scores["q_52_showing_and_directing_attention_current_code"] + $scores["q_53_offering_to_share_current_code"]
									+ $scores["q_54_seeking_to_share_enjoyment_current_code"];
			$scoreCols["Total_A4"] = $scores["q_31_use_of_others_body_current_code"] + $scores["q_55_offerings_comfort_current_code"]
									+ $scores["q_56_quality_of_social_overtures_current_code"] + $scores["q_58_inappropriate_facial_current_code"]
									+ $scores["q_59_appropriateness_of_responses_current_code"];
			$scoreCols["A_Total"] = $scoreCols["Total_A1"] + $scoreCols["Total_A2"] + $scoreCols["Total_A3"] + $scoreCols["Total_A4"];
	
			$scoreCols["Total_B1"] = $scores["q_42_pointing_to_express_interest_current_code"] + $scores["q_43_nodding_current_code"]
									+ $scores["q_44_head_shaking_current_code"] + $scores["q_45_conventional_instrumental_gestures_current_code"];
			$scoreCols["Total_B4"] = $scores["q_47_spontaneous_imitation_current_code"] + $scores["q_48_imaginative_play_current_code"]
									+ $scores["q_61_imitative_social_play_current_code"];
	
			if(substr($record["q_30_overall_level_of_language"], 0, 1) == 0) { //verbal subject
				$scoreCols["Total_B2V"] = $scores["q_34_social_verbalization_chat_current_code"] + $scores["q_35_reciprocal_conversation_current_code"];
				$scoreCols["Total_B3V"] = $scores["q_33_stereotyped_utterances_current_code"] + $scores["q_36_inappropriate_questions_current_code"]
										+ $scores["q_37_prenominal_reversal_current_code"] + $scores["q_38_neologisms_current_code"];
			} else {
				$scoreCols["Total_B2V"] = "Nonverbal";
				$scoreCols["Total_B3V"] = "Nonverbal";
			}
			$scoreCols["BV_Total"] = $scoreCols["Total_B1"] + $scoreCols["Total_B4"] + $scoreCols["Total_B2V"] + $scoreCols["Total_B3V"]; 
			$scoreCols["BNV_Total"] = $scoreCols["Total_B1"] + $scoreCols["Total_B4"];
			
			$scoreCols["Total_C1"] = $scores["q_67_unusual_preoccupations_current_code"] + $scores["q_68_circumscribed_interests_current_code"];
			$scoreCols["Total_C2"] = $scores["q_39_verbal_rituals_current_code"] + $scores["q_70_compulsions_rituals_current_code"];
			$scoreCols["Total_C3"] = $scores["q_77_hands_and_finger_mannerisms_current_code"] + $scores["q_78_other_complex_mannerisms_current_code"];
			$scoreCols["Total_C4"] = $scores["q_69_repetitive_use_of_objects_current_code"] + $scores["q_71_unusual_sensory_interests_current_code"];
			$scoreCols["C_Total"] = $scoreCols["Total_C1"] + $scoreCols["Total_C2"] + $scoreCols["Total_C3"] + $scoreCols["Total_C4"];
        } elseif($this->respondentAgeMonths >= 48 && $this->respondentAgeMonths <= 119) {
			//Age 4 years to 9 years, 11 months => 48months...119months
	        $scoreCols["Total_A1"] = $scores["q_50_direct_gaze_current_code"] + $scores["q_51_social_smiling_current_code"] 
									+ $scores["q_57_range_of_racial_expressions_current_code"];
			$scoreCols["Total_A2"] = $scores["q_49_imaginative_play_with_peers_current_code"] + $scores["q_62_interest_in_children_current_code"] + $scores["q_63_response_to_approaches_current_code"] + $scores["q_64_group_play_peers_current_code"];
			$scoreCols["Total_A3"] = $scores["q_52_showing_and_directing_attention_current_code"] + $scores["q_53_offering_to_share_current_code"]
									+ $scores["q_54_seeking_to_share_enjoyment_current_code"];
			$scoreCols["Total_A4"] = $scores["q_31_use_of_others_body_current_code"] + $scores["q_55_offerings_comfort_current_code"]
									+ $scores["q_56_quality_of_social_overtures_current_code"] + $scores["q_58_inappropriate_facial_current_code"]
									+ $scores["q_59_appropriateness_of_responses_current_code"];
			$scoreCols["A_Total"] = $scoreCols["Total_A1"] + $scoreCols["Total_A2"] + $scoreCols["Total_A3"] + $scoreCols["Total_A4"];
	
			$scoreCols["Total_B1"] = $scores["q_42_pointing_to_express_interest_current_code"] + $scores["q_43_nodding_current_code"]
									+ $scores["q_44_head_shaking_current_code"] + $scores["q_45_conventional_instrumental_gestures_current_code"];
			$scoreCols["Total_B4"] = $scores["q_47_spontaneous_imitation_current_code"] + $scores["q_48_imaginative_play_current_code"]
									+ $scores["q_61_imitative_social_play_current_code"];
	
			if(substr($record["q_30_overall_level_of_language"], 0, 1) == 0) { //verbal subject
				$scoreCols["Total_B2V"] = $scores["q_34_social_verbalization_chat_current_code"] + $scores["q_35_reciprocal_conversation_current_code"];
				$scoreCols["Total_B3V"] = $scores["q_33_stereotyped_utterances_current_code"] + $scores["q_36_inappropriate_questions_current_code"]
										+ $scores["q_37_prenominal_reversal_current_code"] + $scores["q_38_neologisms_current_code"];
			} else {
				$scoreCols["Total_B2V"] = "Nonverbal";
				$scoreCols["Total_B3V"] = "Nonverbal";
			}
	
			$scoreCols["BV_Total"] = $scoreCols["Total_B1"] + $scoreCols["Total_B4"] + $scoreCols["Total_B2V"] + $scoreCols["Total_B3V"]; 
			$scoreCols["BNV_Total"] = $scoreCols["Total_B1"] + $scoreCols["Total_B4"];
	
			
			$scoreCols["Total_C1"] = $scores["q_67_unusual_preoccupations_current_code"] + $scores["q_68_circumscribed_interests_current_code"];
			$scoreCols["Total_C2"] = $scores["q_39_verbal_rituals_current_code"] + $scores["q_70_compulsions_rituals_current_code"];
			$scoreCols["Total_C3"] = $scores["q_77_hands_and_finger_mannerisms_current_code"] + $scores["q_78_other_complex_mannerisms_current_code"];
			$scoreCols["Total_C4"] = $scores["q_69_repetitive_use_of_objects_current_code"] + $scores["q_71_unusual_sensory_interests_current_code"];
			$scoreCols["C_Total"] = $scoreCols["Total_C1"] + $scoreCols["Total_C2"] + $scoreCols["Total_C3"] + $scoreCols["Total_C4"];
        } elseif($this->respondentAgeMonths >= 120) {
			//Age 10 years and older => 120months...  Only applicable to verbal subjects
			if(substr($record["q_30_overall_level_of_language"], 0, 1) != 0) { //non-verbal subject
				$scoreCols["A_Total"] = "Error - cannot score nonverbal subjects";
			} else {
	            $scoreCols["Total_A1"] = $scores["q_51_social_smiling_current_code"] 
										+ $scores["q_57_range_of_racial_expressions_current_code"];
				$scoreCols["Total_A2"] = $scores["q_65_friendships_current_code"];
				$scoreCols["Total_A3"] = $scores["q_52_showing_and_directing_attention_current_code"] + $scores["q_53_offering_to_share_current_code"]
										+ $scores["q_54_seeking_to_share_enjoyment_current_code"];
				$scoreCols["Total_A4"] = $scores["q_31_use_of_others_body_current_code"] + $scores["q_55_offerings_comfort_current_code"]
										+ $scores["q_56_quality_of_social_overtures_current_code"] + $scores["q_58_inappropriate_facial_current_code"]
										+ $scores["q_59_appropriateness_of_responses_current_code"];
				$scoreCols["A_Total"] = $scoreCols["Total_A1"] + $scoreCols["Total_A2"] + $scoreCols["Total_A3"] + $scoreCols["Total_A4"];
		
				$scoreCols["Total_B1"] = $scores["q_42_pointing_to_express_interest_current_code"] + $scores["q_43_nodding_current_code"]
										+ $scores["q_44_head_shaking_current_code"] + $scores["q_45_conventional_instrumental_gestures_current_code"];
		
				$scoreCols["Total_B2V"] = $scores["q_34_social_verbalization_chat_current_code"] + $scores["q_35_reciprocal_conversation_current_code"];
				$scoreCols["Total_B3V"] = $scores["q_33_stereotyped_utterances_current_code"] + $scores["q_36_inappropriate_questions_current_code"]
										+ $scores["q_37_prenominal_reversal_current_code"] + $scores["q_38_neologisms_current_code"];
				$scoreCols["Total_B4"] = "Not Applicable";
				$scoreCols["BV_Total"] = $scoreCols["Total_B1"] + $scoreCols["Total_B2V"] + $scoreCols["Total_B3V"]; 
				$scoreCols["BNV_Total"] = "Not Applicable";
			
				$scoreCols["Total_C1"] = $scores["q_67_unusual_preoccupations_current_code"] + $scores["q_68_circumscribed_interests_current_code"];
				$scoreCols["Total_C2"] = $scores["q_39_verbal_rituals_current_code"] + $scores["q_70_compulsions_rituals_current_code"];
				$scoreCols["Total_C3"] = $scores["q_77_hands_and_finger_mannerisms_current_code"] + $scores["q_78_other_complex_mannerisms_current_code"];
				$scoreCols["Total_C4"] = $scores["q_69_repetitive_use_of_objects_current_code"] + $scores["q_71_unusual_sensory_interests_current_code"];
				$scoreCols["C_Total"] = $scoreCols["Total_C1"] + $scoreCols["Total_C2"] + $scoreCols["Total_C3"] + $scoreCols["Total_C4"];
			}
        } else {
        	$scoreCols["A_Total"] = "Error with the Age - cannot score";
        }		

        // save the resultant total
        $result = $db->update($this->table, $scoreCols, array('CommentID'=>$this->getCommentID()));
        if($db->isError($result)) {
            return PEAR::raiseError("Could not save total score: ".$result->getMessage());
        }
		
    }
    
    function _page1(){
        
        $this->form->addElement("header", null, "BACKGROUND");
        $this->addLargeTextAreaElement("background_family_members", "Family Members");
        $this->addLargeTextAreaElement("background_education", "Subject's Education");
        $this->addLargeTextAreaElement("background_personalized_timing", "Personalized Timing");
        $this->addLargeTextAreaElement("background_diagnosis", "Diagnosis");
        $this->addLargeTextAreaElement("background_medication", "Medication");

        $this->addLargeTextAreaElement("introductory_questions", "Introductory Questions");
        $this->addLargeTextAreaElement("q_1_current_concerns", "1. Current Concerns");
    }
    
    function _page2() {
    	$this->form->addElement("header", null, "EARLY DEVELOPMENT");
    	$this->addTextElement("q_2_age_first_noticed_code", "2. Age (in months) when parents first noticed that something was not quite right...");
    	$this->addLargeTextAreaElement("q_2_age_first_noticed_text");
    
    	$this->addLargeTextAreaElement("q_3_first_symptoms_text", "3. First symptoms to arouse parental concern");
    	
    	$this->addTextElement("q_4_onset_as_perceived_code", "4. Onset as perceived with hindsight");
    	$this->addLargeTextAreaElement("q_4_onset_as_perceived_text");
    	
    	$this->addTextElement("q_5_first_walked_code", "5. First walked unaided");
		$this->addLargeTextAreaElement("q_5_first_walked_text");
		
		$this->addTextElement("q_6_bladder_daytime_code", "6. Acquisition of bladder control: daytime");
		$this->addLargeTextAreaElement("q_6_bladder_daytime_text");
		
		$this->addTextElement("q_7_bladder_nighttime_code", "7. Acquisition of bladder control: nighttime");
		$this->addLargeTextAreaElement("q_7_bladder_nighttime_text");

		$this->addTextElement("q_8_bowel_control_code", "8. Acquisition of bowel control");
		$this->addLargeTextAreaElement("q_8_bowel_control_text");

    }
		
//		"q_8_bowel_control", "8. Acquisition of bowel control"
	function _page3() {
	
		$this->form->addElement("header", null, "ACQUISITION AND LOSS OF LANGUAGE/OTHER SKILLS");
	
		$this->addTextElement("q_9_first_single_words_code", "9. Age of first single words");
		$this->addLargeTextAreaElement("q_9_first_single_words_text");
	
		$this->addTextElement("q_10_first_phrases_code", "10. Age of first phrases (if ever used)");
		$this->addLargeTextAreaElement("q_10_first_phrases_text");
		
		$this->form->addElement("select", "q_11_loss_of_language", "11. Loss of language skills after acquisition", $this->yesNoNA);
		
		$answerArray = array(""=>NULL, "0_daily"=>"0. Daily", "1_occasional"=>"1. Occasional", "2_upon_request"=>"2. Produced upon request", "3_spontaneous_imitations"=>"3. Spontaneous imitations", "8_no_change"=>"8. No change", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("select", "q_12_level_before_loss_code", "12. Level of communicative language before loss", $answerArray);
		$this->XINRegisterRule("q_12_level_before_loss_code", array("q_11_loss_of_language{@}=={@}1_yes"), "This is required if language was lost (answered 'yes' to question 11)");
		$this->addLargeTextAreaElement("q_12_level_before_loss_text", $this->indent . "Describe:", array("q_11_loss_of_language{@}=={@}1_yes"), "This is required if language was lost (answered 'yes' to question 11)");
		
		$answerArray = array(""=>NULL, "0_no_loss"=>"0. No definite loss", "1_probable_loss"=>"1. Probable loss", "2_definite_loss"=>"2. Definite Loss", "8_insufficient"=>"8. Insufficient", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$questionArray = array("13_loss_of_spontaneous_use"=>"13. Loss of spontaneous use",
								"14_loss_of_intent"=>"14. Loss of communicative intent",
								"15_loss_of_syntactical"=>"15. Loss of syntactical skills",
								"16_loss_of_articulation"=>"16. Loss of articulation");
		foreach($questionArray as $field=>$label) {
			$this->form->addElement("select", $field . "_code", $label, $answerArray);
			$this->XINRegisterRule($field . "_code", array("q_11_loss_of_language{@}=={@}1_yes"), "This is required if language was lost (answered 'yes' to question 11)");
			$this->addTextAreaElement($field . "_text", $this->indent . "Describe:");
			$this->XINRegisterRule($field . "_text", array("q_11_loss_of_language{@}=={@}1_yes"), "This is required if language was lost (answered 'yes' to question 11)");
		}
		
		$this->addTextElement("q_17_main_loss_apparent_code", "17. Age when main loss of language skills first apparent", array("q_11_loss_of_language{@}=={@}1_yes"), "This is required if language was lost (answered 'yes' to question 11)");
		$this->addLargeTextAreaElement("q_17_main_loss_apparent_text", $this->indent . "Describe:", array("q_11_loss_of_language{@}=={@}1_yes"), "This is required if language was lost (answered 'yes' to question 11)");
	
		$answerArray = array(""=>NULL, "0_loss_no_relevance"=>"0. Loss no possible relevance", "1_loss_illness"=>"1. Loss from illness", "2_loss_impaired"=>"2. Loss from impaired consciousness", "8_no_loss"=>"8. No loss", "9_not_asked"=>"9. Not asked", "not_anwered"=>"Not Answered");
		$this->form->addElement("select", "q_18_loss_due_to_illness", "18. Association of loss of language with physical illness", $answerArray);
		$this->XINRegisterRule("q_18_loss_due_to_illness_code", array("q_11_loss_of_language{@}=={@}1_yes"), "This is required if language was lost (answered 'yes' to question 11)");
		$this->addLargeTextAreaElement("q_18_loss_due_to_illness_text", $this->indent . "Describe:", array("q_11_loss_of_language{@}=={@}1_yes"), "This is required if language was lost (answered 'yes' to question 11)");
	
		$this->addTextElement("q_19_duration_of_loss_code", "19. Duration of loss of language skills", array("q_11_loss_of_language{@}=={@}1_yes"), "This is required if language was lost (answered 'yes' to question 11)");
		$this->addLargeTextAreaElement("q_19_duration_of_loss_text", $this->indent . "Describe:", array("q_11_loss_of_language{@}=={@}1_yes"), "This is required if language was lost (answered 'yes' to question 11)");
		
	}
	
	function _page4() {

		$this->form->addElement("header", null, "GENERAL LOSS OF SKILLS");
		$answerArray = array(""=>NULL, "0_no_consistent_loss"=>"0. No consistent loss", "1_probable_loss"=>"1. Probable loss", "2_account_definite_loss"=>"2. Account of definite loss", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("select", "q_20_loss_of_skills_code", "20. Loss of skills (for at least 3 months)", $answerArray);
		$this->addLargeTextAreaElement("q_20_loss_of_skills_text");
		
		$questionArray = array("q_21_puposive_hand_movements"=>"21. Purposive hand movements",
		"q_22_motor_skills"=>"22. Motor skills",
		"q_23_self_help_skills"=>"23. Self-help skills",
		"q_24_constructive_play"=>"24. Constructive or imaginative play",
		"q_25_social_engagement"=>"25. Social engagement and responsiveness");
		$answerArray = array(""=>NULL, "0_none"=>"0. None", "1_possible"=>"1. Possible", "2_definite"=>"2. Definite", "not_answered"=>"Not Answered");
		foreach ($questionArray as $field=>$label) {
			$this->form->addElement("select", $field . "_code", $label, $answerArray);
			$this->addTextAreaElement($field . "_text", $this->indent . "Describe:");
		}		
		
		$this->addTextElement("q_26_loss_first_apparent_code", "26. Age when main loss of skill first apparent");
		$this->addTextAreaElement("q_26_loss_first_apparent_text", $this->indent . "Describe:");
		
		$answerArray = array(""=>NULL, "0_no_relevance"=>"0. No possibly relevance", "1_definite_illness"=>"1. Definite illness", "2_impaired_consciousness"=>"2. Impaired consciousness", "8_no_loss"=>"8. No loss", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("select", "q_27_physical_illness_code", "27. Association of loss of skills with physical illness", $answerArray);
		$this->addLargeTextAreaElement("q_27_physical_illness_text");
		
		$this->addTextElement("q_28_duration_of_loss_code", "28. Duration of loss of skills");
		$this->addLargeTextAreaElement("q_28_duration_of_loss_text", $this->indent . "Describe:");
	}

	function _page5() {
		$this->form->addElement("header", null, "LANGUAGE AND COMMUNICATION FUNCTIONING");
		
		$answerArray = array(""=>NULL, "0_perform_unexpected"=>"0. Perform an unexpected", "1_get_an_object"=>"1. Get an object", "2_understand_many_words"=>"2. Understand many words", "3_understand_fewer_than_50"=>"3. Understand fewer than 50", "4_little_or_no"=>"4. Little or no comprehension of words", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("static", null, "29. Comprehension of simple language");
		$this->form->addElement("select", "q_29_comprehension_of_simple_current",  $this->indent . "Current", $answerArray);
		$this->form->addElement("select", "q_29_comprehension_of_simple_most_abnormal",  $this->indent . "Most Abnormal (4.0-5.0)", $answerArray);
		$this->addLargeTextAreaElement("q_29_comprehension_of_simple_text");
		
		$answerArray = array(""=>NULL, "0_fuctional"=>"0. Functional", "1_no_functional"=>"1. No functional use", "2_fewer_than_5"=>"2. Fewer than five", "not_answered"=>"Not Answered");
		$this->form->addElement("select", "q_30_overall_level_of_language", "30. Overall level of language", $answerArray);
		
		$answerArray = array(""=>NULL, "0_no_use"=>"0. No use", "1_occasional_point"=>"1. Occasional to point", "2_occasional_for"=>"2. Occasional 'for'", "3_regular"=>"3. Regular", "8_little"=>"8. Little", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("static", null, "31. Use of other's body to communicate");
		$this->form->addElement("select", "q_31_use_of_others_body_current_code", $this->indent . "Current:", $answerArray);
		$this->form->addElement("select", "q_31_use_of_others_body_ever_code", $this->indent . "Ever:", $answerArray);
		$this->addLargeTextAreaElement("q_31_use_of_others_body_text");
		
		$answerArray = array(""=>NULL, "0_anybody"=>"0. Anybody", "1_family"=>"1. Family", "2_difficulties"=>"2. Difficulties", "3_strangers"=>"3. Strangers", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("static", null, "32. Articulation/pronunciation");
		$this->form->addElement("select", "q_32_articulation_pronunciation_current_code", $this->indent . "Current:", $answerArray);
		$this->form->addElement("select", "q_32_articulation_pronunciation_5years_code", $this->indent . "At 5.0 Years:", $answerArray);
		$this->addLargeTextAreaElement("q_32_articulation_pronunciation_text");
		
		$answerArray = array(""=>NULL, "0_rarely"=>"0. Rarely", "1_more_repetitive"=>"1. More repetitive", "2_often_stereotyped"=>"2. Often stereotyped utterances", "3_exclusively_stereotyped"=>"3. Exclusively stereotyped utterances", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("static", null, "33. Stereotyped utterances and delayed echolalia");
		$this->form->addElement("select", "q_33_stereotyped_utterances_current_code", $this->indent . "Current:", $answerArray);
		$this->form->addElement("select", "q_33_stereotyped_utterances_ever_code", $this->indent . "Ever:", $answerArray);
		$this->addLargeTextAreaElement("q_33_stereotyped_utterances_text");
		
		$answerArray = array(""=>NULL, "0_verbalizes"=>"0. Verbalizes", "1_some_response"=>"1. Some response", "2_some_alert"=>"2. Some alert", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("static", null, "34. Social verbalization/chat");
		$this->form->addElement("select", "q_34_social_verbalization_chat_current_code", $this->indent . "Current:", $answerArray);
		$this->form->addElement("select", "q_34_social_verbalization_chat_ever_code", $this->indent . "Ever:", $answerArray);
		$this->addLargeTextAreaElement("q_34_social_verbalization_chat_text");

		$answerArray = array(""=>NULL, "0_conversational"=>"0. Conversational flows", "1_occasional"=>"1. Occasional", "2_little_or_not"=>"2. Little of no", "3_very_little"=>"3. Very little", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("static", null, "35. Reciprocal conversation (within subject's level of language)");
		$this->form->addElement("select", "q_35_reciprocal_conversation_current_code", $this->indent . "Current:", $answerArray);
		$this->form->addElement("select", "q_35_reciprocal_conversation_ever_code", $this->indent . "Ever:", $answerArray);
		$this->addLargeTextAreaElement("q_35_reciprocal_conversation_text");
		
		$answerArray = array(""=>NULL, "0_none_or_rare"=>"0. No or very rare", "1_some_questions"=>"1. Use of some questions", "2_frequent"=>"2. Frequent", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("static", null, "36. Inappropriate questions or statements");
		$this->form->addElement("select", "q_36_inappropriate_questions_current_code", $this->indent . "Current:", $answerArray);
		$this->form->addElement("select", "q_36_inappropriate_questions_ever_code", $this->indent . "Ever:", $answerArray);
		$this->addLargeTextAreaElement("q_36_inappropriate_questions_text");

		$answerArray = array(""=>NULL, "0_no_confusion"=>"0. No confusion", "1_refers"=>"1. Refers", "2_you_I_confusion"=>"2. You/I confusion", "3_pronominal"=>"3. Pronominal", "7_other_types"=>"7. Other types of pronominal", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("static", null, "37. Prenominal reversal");
		$this->form->addElement("select", "q_37_prenominal_reversal_current_code", $this->indent . "Current:", $answerArray);
		$this->form->addElement("select", "q_37_prenominal_reversal_ever_code", $this->indent . "Ever:", $answerArray);
		$this->addLargeTextAreaElement("q_37_prenominal_reversal_text");

		$answerArray = array(""=>NULL, "0_no_use"=>"0. No use", "1_occasional"=>"1. Occasional", "2_regular"=>"2. Regular", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("static", null, "38. Neologisms/Idiosyncratic language");
		$this->form->addElement("select", "q_38_neologisms_current_code", $this->indent . "Current:", $answerArray);
		$this->form->addElement("select", "q_38_neologisms_ever_code", $this->indent . "Ever:", $answerArray);
		$this->addLargeTextAreaElement("q_38_neologisms_text");

		$answerArray = array(""=>NULL, "0_no_rituals"=>"0. No rituals", "1_tendency"=>"1. Tendency", "2_special_way"=>"2. Special way", "3_as_for2_with_difficulty"=>"3. As for '2', with difficulty", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("static", null, "39. Verbal rituals");
		$this->form->addElement("select", "q_39_verbal_rituals_current_code", $this->indent . "Current:", $answerArray);
		$this->form->addElement("select", "q_39_verbal_rituals_ever_code", $this->indent . "Ever:", $answerArray);
		$this->addLargeTextAreaElement("q_39_verbal_rituals_text");

		$answerArray = array(""=>NULL, "0_normal"=>"0. Normal", "1_shows_abnormalities"=>"1. Shows abnormalities", "2_clearly_abnormal"=>"2. Clearly abnormal", "3_frequetly_peculiar"=>"3. Frequently peculiar", "7_stutter"=>"7. Stutter", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("static", null, "40. Intonation/volume/rhythm/rate");
		$this->form->addElement("select", "q_40_intonation_volume_rhythm_rate_current_code", $this->indent . "Current:", $answerArray);
		$this->form->addElement("select", "q_40_intonation_volume_rhythm_rate_ever_code", $this->indent . "Ever:", $answerArray);
		$this->addLargeTextAreaElement("q_40_intonation_volume_rhythm_rate_text");
	
	}
	
	function _page6() {
		$this->form->addElement("header", null, "LANGUAGE AND COMMUNICATION FUNCTIONING (Continued)");

		$answerArray = array(""=>NULL, "0_speech_used_frequently"=>"0. Speech used frequently", "1_some_communication"=>"1. Some communication", "2_some_spontaneous"=>"2. Some spontaneous", "3_lillte_or_no"=>"3. Little or no", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("static", null, "41. Current communicative speech");
		$this->form->addElement("select", "q_41_current_communicative_speech_current_code", $this->indent . "Current:", $answerArray);
		$this->form->addElement("select", "q_41_current_communicative_speech_at5_code", $this->indent . "At 5.0 years:", $answerArray);
		$this->addLargeTextAreaElement("q_41_current_communicative_speech_text");
		
		$answerArray = array(""=>NULL, "0_spontaneously"=>"0. Spontaneously points", "1_limited_attempt"=>"1. Limited attempt", "2_little_or_no"=>"2. Little or no", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("static", null, "42. Pointing to express interest");
		$this->form->addElement("select", "q_42_pointing_to_express_interest_current_code", $this->indent . "Current:", $answerArray);
		$this->form->addElement("select", "q_42_pointing_to_express_interest_most_abnormal_code", $this->indent . "Most abnormal 4.0-5.0 years:", $answerArray);
		$this->addLargeTextAreaElement("q_42_pointing_to_express_interest_text");
		
		$answerArray = array(""=>NULL, "0_consistently"=>"0. Consistently", "1_sometimes"=>"1. Sometimes", "2_never"=>"2. Never", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_43_nodding";
		$label = "43. Nodding";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);
		
		$answerArray = array(""=>NULL, "0_consistently"=>"0. Consistently", "1_sometimes"=>"1. Sometimes", "2_never"=>"2. Never", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_44_head_shaking";
		$label = "44. Head shaking";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);
		
		$answerArray = array(""=>NULL, "0_appripriate"=>"0. Appropriate", "1_spontaneous"=>"1. Spontaneous", "2_inconsistent"=>"2_inconsistent", "3_no_use"=>"3. No use", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_45_conventional_instrumental_gestures";
		$label = "45. Conventional/instrumental gestures";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);
		
		$answerArray = array(""=>NULL, "0_usually"=>"0. Usually", "1_not_consistently"=>"1. Not consistently", "2_usually_does_not"=>"2. Usually does not", "3_rarely"=>"3. Rarely", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_46_attention_to_voice";
		$label = "46. Attention to voice";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);
		
		$answerArray = array(""=>NULL, "0_spontaneous"=>"0. Spontaneous", "1_some"=>"1. Some", "2_limited"=>"2. Limited", "3_very_rare"=>"3. Very rare", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_47_spontaneous_imitation";
		$label = "47. Spontaneous imitation of actions";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);
		
		$answerArray = array(""=>NULL, "0_variety"=>"0. Variety", "1_some"=>"1. Some", "2_occasional"=>"2. Occasional", "3_no_pretend"=>"3. No pretend", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_48_imaginative_play";
		$label = "48. Imaginative play";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);
		
		$answerArray = array(""=>NULL, "0_imaginative"=>"0. Imaginative",  "1_some_participation"=>"1. Some participation",  "2_some_play"=>"2. Some play",  "3_no_play"=>"3. No play", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_49_imaginative_play_with_peers";
		$label = "49. Imaginative play with peers";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);

	}
	
	function _page7() {
		$this->form->addElement("header", null, "SOCIAL DEVELOPMENT AND PLAY");

		$answerArray = array(""=>NULL, "0_normal"=>"0. Normal", "1_definite"=>"1. Definite", "2_uncertain"=>"2. Uncertain", "3_unusual"=>"3. Unusual", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_50_direct_gaze";
		$label = "50. Direct gaze";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_regularly"=>"0. Regularly", "1_some_reciprocal"=>"1. Some reciprocal", "2_some_smiling"=>"2. Some smiling", "3_little_or_no"=>"3. Little or no", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_51_social_smiling";
		$label = "51. Social smiling";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_regular"=>"0. Regular", "1_possible"=>"1. Possible", "2_some"=>"2. Some", "3_rare"=>"3. Rare", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_52_showing_and_directing_attention";
		$label = "52. Showing and directing attention";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);
		
		$answerArray = array(""=>NULL, "0_frequent"=>"0. Frequent", "1_some"=>"1. Some", "2_sometimes"=>"2. Sometimes", "3_no_sharing"=>"3. No sharing", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_53_offering_to_share";
		$label = "53. Offering to share";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_frequent"=>"0. Frequent", "1_some"=>"1. Some", "2_few"=>"2. Few", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_54_seeking_to_share_enjoyment";
		$label = "54. Seeking to share her/his enjoyment with others";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_frequently"=>"0. Frequently", "1_partial"=>"1. Partial", "2_rarely"=>"2. Rarely", "3_never"=>"3. Never", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_55_offerings_comfort";
		$label = "55. Offerings comfort";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_consistently"=>"0. Consistently", "1_may"=>"1. May", "2_rarely"=>"2. Rarely", "3_shows_no"=>"3. Shows no", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_56_quality_of_social_overtures";
		$label = "56. Quality of social overtures";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_full"=>"0. Full", "1_somewhat"=>"1. Somewhat", "2_markedly"=>"2. Markedly", "3_little_or_no"=>"3. Little or no", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_57_range_of_racial_expressions";
		$label = "57. Range of racial expressions used to communicate";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_almost_always"=>"0. Almost always", "1_slightly"=>"1. Slightly", "2_obviously"=>"2. Obviously", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("static", null, "58. Inappropriate facial expressions");
		$this->form->addElement("select", "q_58_inappropriate_facial_current_code", $this->indent . "Current:", $answerArray);
		$this->form->addElement("select", "q_58_inappropriate_facial_ever_code", $this->indent . "Ever:", $answerArray);
		$this->addLargeTextAreaElement("q_58_inappropriate_facial_text");
		
		$answerArray = array(""=>NULL, "0_appropriate"=>"0. Appropriate", "1_some"=>"1. Some", "2_responds"=>"2. Responds", "3_little_or_no"=>"3. Little or no", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_59_appropriateness_of_responses";
		$label = "59. Appropriateness of social responses";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);
		
		$this->addLargeTextAreaElement("q_60_favourite_activities", "Favourite Activities");
		$this->addLargeTextAreaElement("q_60_favourite_toys_objects", "Favourite Toys / Objects");
	}
	
	function _page8() {
		$answerArray = array(""=>NULL, "0_range"=>"0. Range", "1_initiates"=>"1. Initiates", "2_passive"=>"2. Passive", "3_no_active"=>"3. No active", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_60_initiation_of_activities";
		$label = "60. Initiation of appropriate activities";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_normal"=>"0. Normal", "1_some"=>"1. Some", "2_little"=>"2. Little", "3_no_evidence"=>"3. No evidence", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_61_imitative_social_play";
		$label = "61. Imitative social play";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_often"=>"0. Often", "1_usually"=>"1. Usually", "2_occasionaly"=>"2. Occasionaly", "3_shows_no"=>"3. Shows no", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_62_interest_in_children";
		$label = "62. Interest in children";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_generally"=>"0. Generally", "1_sometimes"=>"1. Sometimes", "2_rarely"=>"2. Rarely", "3_consistently"=>"3. Consistently", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_63_response_to_approaches";
		$label = "63. Response to approaches of other children";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_actively"=>"0. Actively", "1_some"=>"1. Some", "2_enjoys"=>"2. Enjoys", "3_seeks_no"=>"3. Seeks no", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_64_group_play_peers";
		$label = "64. Group play peers";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0"=>"0", "1"=>"1", "2"=>"2", "3_no_peer"=>"3. No peer", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_65_friendships";
		$label = "65. Friendships";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_normal"=>"0. Normal", "1_occasional"=>"1. Occasional", "2_lack"=>"2. Lack", "3_marked"=>"3. Marked", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_66_social_disinhibition";
		$label = "66. Social disinhibition";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);
	}
	
	function _page9() {
		$this->form->addElement("header", null, "INTERESTS AND BEHAVIOURS");

		$answerArray = array(""=>NULL, "0_no_unusual"=>"0. No unusual", "1_unusual"=>"1. Unusual", "2_definite_intrudes"=>"2. Definite intrudes", "3_definite_interferes"=>"3. Definite Interferes", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_67_unusual_preoccupations";
		$label = "67. Unusual preoccupations";
		$this->_addCurrentEver($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_no"=>"0. No", "1_special"=>"1. Special", "2_definite_no_interfere"=>"2. Definite no interfere", "3_definite_impairment"=>"3. Definite impairment", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_68_circumscribed_interests";
		$label = "68. Circumscribed interests";
		$this->_addCurrentEver($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_little_or_no"=>"0. Little or no", "1_some"=>"1. Some", "2_does_not_constrain"=>"2. Does not constrain", "3_prevents"=>"3. Prevents", "7_infant_toys"=>"7. Infant toys", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_69_repetitive_use_of_objects";
		$label = "69. Repetitive use of objects or interest in parts of objects";
		$this->_addCurrentEver($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_no"=>"0. No", "1_some"=>"1. Some", "2_one_or_more"=>"2. One or more", "3_marked"=>"3. Marked", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_70_compulsions_rituals";
		$label = "70. Compulsions/rituals";
		$this->_addCurrentEver($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_no_unusual"=>"0. No unusual", "1_one_or_two"=>"1. One or two", "2_has"=>"2. Has", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_71_unusual_sensory_interests";
		$label = "71. Unusual sensory interests";
		$this->_addCurrentEver($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_no_general"=>"0. No general", "1_slight"=>"1. Slight", "2_definite_not_distressing"=>"2. Definite not distressing", "3_definite_interferes"=>"3. Definite interferes", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_72_undo_general_sensitivity_to_noise";
		$label = "72. Undo general sensitivity to noise";
		$this->_addCurrentEver($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_no"=>"0. No", "1_mild"=>"1. Mild", "2_occasional"=>"2. Occasional", "3_substantial"=>"3. Substantial", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_73_idiosyncratic";
		$label = "73. Abnormal, idiosyncratic, negative response to specific sensory stimuli";
		$this->_addCurrentEver($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_no"=>"0. No", "1_unusually"=>"1. Unusually", "2_resistance"=>"2. Resistance", "3_substantial"=>"3. Substantial", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_74_difficulties_with_minor_changes";
		$label = "74. Difficulties with minor changes in subjects own routines or personal environment";
		$this->_addCurrentEver($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_none"=>"0. None", "1_unusually"=>"1. Unusually", "2_avoid"=>"2. Avoid", "3_substantial"=>"3. Substantial", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_75_resistance_to_trivial_changes";
		$label = "75. Resistance to trivial changes in the environment";
		$this->_addCurrentEver($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_no"=>"0. No", "1_some"=>"1. Some", "2_significant"=>"2. Significant", "3_intrusive"=>"3. Intrusive", "6_beyond_5"=>"6. Beyond age 5", "7_series"=>"7. Series", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_76_unusual_attachments_to_objects";
		$label = "76. Unusual attachments to objects";
		$this->_addCurrentEver($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_no"=>"0. No", "1_occasional"=>"1. Occasional", "2_definite"=>"2. Definite", "3_marked"=>"3. Marked", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_77_hands_and_finger_mannerisms";
		$label = "77. Hands and finger mannerisms";
		$this->_addCurrentEver($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_no"=>"0. No", "1_only"=>"1. Only", "2_definite"=>"2. Definite", "3_marked"=>"3. Marked", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_78_other_complex_mannerisms";
		$label = "78. Other complex mannerisms or stereotyped body movements";
		$this->_addCurrentEver($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_no"=>"0. No", "1_occasional"=>"1. Occasional", "2_definite"=>"2. Definite", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_79_midline_hand_movements";
		$label = "79. Midline hand movements";
		$this->_addCurrentEver($field, $label, $answerArray);

	}
	
	function _page10() {
		$this->form->addElement("header", null, "GENERAL BEHAVIOURS");
	
		$answerArray = array(""=>NULL, "0_normal"=>"0. Normal", "1_somewhat"=>"1. Somewhat", "2_defnitely"=>"2. Definitely", "3_gait_odd"=>"3. Gait odd", "7_gait_neurological"=>"7. Gait neurological", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_80_gait";
		$label = "80. Gait";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_no"=>"0. No", "1_mild"=>"1. Mild", "2_definite"=>"2. Definite", "3_violence"=>"3. Violence", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_81_aggression_towards_caregivers";
		$label = "81. Aggression towards caregivers or family members";
		$this->_addCurrentEver($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_rare"=>"0. Rare", "1_mild"=>"1. Mild", "2_definite"=>"2. Definite", "3_violence"=>"3. Violence", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_82_aggression_toward_noncaregivers";
		$label = "82. Aggression toward noncaregivers or nonfamily members";
		$this->_addCurrentEver($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_no"=>"0. No", "1_slight"=>"1. Slight", "2_definitely"=>"2. Definitely", "3_serious"=>"3. Serious", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_83_self-injury";
		$label = "83. Self-injury";
		$this->_addCurrentEver($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_no"=>"0. No", "1_occasional"=>"1. Occasional", "2_frequent"=>"2. Frequent", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_84_hyperventilation";
		$label = "84. Hyperventilation";
		$this->_addCurrentEver($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_no"=>"0. No", "1_history"=>"1. History", "2_definite"=>"2. Definite", "7_febrile"=>"7. Febrile", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_85_faints_fits_blackouts";
		$label = "85. Faints/fits/blackouts";
		$this->_addCurrentEver($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0"=>"0", "1"=>"1", "2"=>"2", "3"=>"3", "4"=>"4", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("select", "q_86_age_when_abnormality_first_evident", "86. Age when abnormality first evident", $answerArray);
		$this->addLargeTextAreaElement("q_86_age_when_abnormality_first_evident_text");

		$this->addTextElement("q_87_interviewers_judgment", "87. Interviewers judgment on age when developmental abnormalities probably first manifest");
		
	}
	
	function _page11(){
		$this->form->addElement("header", null, "SPECIAL ISOLATED SKILLS");
		
		$this->addLargeTextAreaElement("special_isolated_skills", "Special isolated skills");

		$answerArray = array(""=>NULL, "0_no"=>"0. No", "1_above_subject"=>"1. Above subject", "2_above_population"=>"2. Above population", "7_meaningful"=>"7. Meaningful", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$questionArray = array("q_88_visuospatial_ability"=>"88. Visuospatial ability",
								"q_89_memory_still"=>"89. Memory still",
								"q_90_musical_ability"=>"90. Musical ability",
								"q_91_drawings_skill"=>"91. Drawings skill",
								"q_92_reading_ability"=>"92. Reading ability",
								"q_93_computational_ability"=>"93. Computational ability");
		foreach($questionArray as $field=>$label) {
			$this->form->addElement("static", null, $label);
			$this->form->addElement("select", $field . "_current_code", $this->indent . "Current:", $answerArray);
			$this->form->addElement("select", $field . "_ever_code", $this->indent . "Ever:", $answerArray);
		}
		
		$this->form->addElement("header", null, "CONCLUDING COMMENTS");
		$questionArray = array("overall_assessment"=>"Overall assessment",
								"interviewers_impressions_and_circumstances"=>"Interviewers impressions and circumstances of interview",
								"summary_of_discrepancies"=>"Summary of discrepancies between informant description and observer information");
		foreach($questionArray as $field=>$label) {
			$this->addLargeTextAreaElement($field, $label);
		}	

	}
	
/*	
		$answerArray = array(""=>NULL, ""=>"", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = ;
		$label = ;
		$this->_addCurrentEver($field, $label, $answerArray);

		$answerArray = array(""=>NULL, ""=>"", "not_answered"=>"Not Answered");
		$this->form->addElement("static", null, "");
		$this->form->addElement("select", );
		$this->addTextElement("_code", );
		$this->addLargeTextAreaElement("_text");
		$this->XINRegisterRule(, array("q_11_loss_of_language{@}=={@}1_yes"), "This is required if language was lost (answered 'yes' to question 11)");
*/

    /**
    * Wrapper to create a large text area field, with an accompanying status field.  Modified from the base class function addTextAreaElement
    * @param    string    $field    The database field in which the response will be stored
    * @param    string    $label    The question text to display
    * @param    array    $rules    {@} delimited rules
    * @param    string    $rule_message    rule message to display upon rule violation
    */
    function addLargeTextAreaElement($field, $label = "&nbsp;&nbsp;&nbsp;&nbsp;Describe:", $rules=array(), $rule_message='This field must be completed or marked as not answered.') {
        $group[]=&$this->form->createElement("textarea", $field, null, array('cols'=>60, 'rows'=>6));
        $group[]=&$this->form->createElement("select", $field."_status", "", array(NULL=>'', 'not_answered'=>'Not Answered'));
        $this->form->addGroup($group, $field.'_group', $label, null, false);
        unset($group);
        $rules_array=array_merge(array($field.'_status{@}=={@}'),$rules);
        $this->XINRegisterRule($field, $rules_array, $rule_message, $field.'_group');
    }
    
	function _addCurrentMostAbnormal($field, $label, $answerArray) { 
		$this->form->addElement("static", null, $label);
		$this->form->addElement("select", $field . "_current_code", $this->indent . "Current:", $answerArray);
		$this->form->addElement("select", $field . "_most_abnormal_code", $this->indent . "Most abnormal 4.0-5.0 years:", $answerArray);
		$this->addLargeTextAreaElement($field . "_text");
	}

	function _addCurrentEver($field, $label, $answerArray) { 
		$this->form->addElement("static", null, $label);
		$this->form->addElement("select", $field . "_current_code", $this->indent . "Current:", $answerArray);
		$this->form->addElement("select", $field . "_ever_code", $this->indent . "Ever:", $answerArray);
		$this->addLargeTextAreaElement($field . "_text");
	}
}
?>