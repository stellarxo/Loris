<?php

require_once 'HTML/QuickForm.php';
require_once 'HTML/QuickForm/Renderer/Array.php';

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
        "q_16_language_comp_body_parts_raw_score",
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

        var $dateOptions = array(
                'language' => 'en',
                'format'   => 'YMd',
                'minYear'  =>  '2006',
                'maxYear'  => '2017',
                'addEmptyOption' => true,
                'emptyOptionValue' => null);


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
                                            "play"=>"Play" . $this->indent . $this->indent . $this->indent . $this->indent . $this->indent . $this->indent . $this->indent,
                                            "object_names"=>"object names:", "person_names"=>"person names:", "body_parts"=>"body parts:", "subscale"=>"Subscale", "raw_weighted"=>"Weighted Raw Score", 						    "standard_score"=>"Standard Score","percentile_rank"=>"Percentile Rank"));



    /**
     * Array of column names to be ignored by the double data entry conflict detector.
     */
    $this->_doubleDataEntryDiffIgnoreColumns = array('CommentID', 'UserID', 'Testdate', 'Window_Difference', 'Candidate_Age',
						     'relationship_to_child_specify',
						     'relationship_to_child_specify_status',
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
						   'q_19_sequence_action_schemes_6',
                           'symbolic_composite_percentile',
                           'symbolic_composite_standard',
                           'total_percentile',
                           'total_standard',
                           'total_weighted_raw_score',
                           'understanding_percentile',
                           'understanding_standard',
                           'speech_composite_percentile',
                           'speech_composite_score',
                           'speech_composite_standard',
                           'words_percentile',
                           'words_standard',
                           'communication_percentile',
                           'communication_standard',
                           'object_use_percentile',
                           'object_use_standard',
                           'social_composite_percentile',
                           'social_composite_standard',
                           'sounds_percentile',
                           'sounds_standard',
                           'object_use_weighted',
                           'social_composite_score',
                           'speech_composite_score',
                           'symbolic_composite_score',
                           'total_weighted_raw_score',
                           'emotion_eye_gaze_standard',
                           'emotion_eye_gaze_percentile',
                           'communication_standard',
                           'communication_percentile',
                           'gestures_standard',
                           'gestures_percentile',
                           'q_20_stacks_tower_raw_score',
                           'q_19_sequence_action_schemes_raw_score',
                           'q_18_actions_towards_other_raw_score',
                           'q_17_action_schemes_raw_score',
                           'understanding_weighted',
                           'q_16_language_comp_body_parts_raw_score',
                           'q_16c_language_comp_body_parts_raw_score',
                           'q_16b_language_comp_person_name_raw_score',
                           'q_16a_language_comp_object_raw_score',
                           'q_16_language_comp_raw_score',
                           'words_weighted',
                           'q_15_word_combos_raw_score',
                           'q_14_word_combos_raw_score',
                           'q_13_words_raw_score',
                           'q_12_words_raw_score',
                           'sounds_weighted',
                           'q_11_inventory_of_consonants_raw_score',
                           'q_10_syllables_consonants_raw_score',
                           'gestures_weighted',
                           'q_9_distal_gestures_raw_score',
                           'q_8_conventional_gestures_raw_score',
                           'communication_weighted',
                           'q_7_joint_attention_raw_score',
                           'q_6_social_interaction_raw_score',
                           'q_5_behaviour_regulation_raw_score',
                           'q_4_rate_of_communicating_raw_score',
                           'emotion_eye_gaze_weighted',
                           'q_3_gaze_point_following_raw_score',
                           'q_2_shared_positive_affect_raw_score',
                           'q_1_gaze_shifts_raw_score',
                           'Data_entry_completion_status');


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
        if(preg_match("/csbs(_page[0-9]+)/",$this->page,$matches)){
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
        //display test name
        $this->form->addElement('header', 'instrument_title', "Communication and Symbolic Behaviour Scales - Development Profile");
        
        // automatically adds examiner & date of administration
        $this->_addMetadataFields();

        $this->form->addElement("static", null, "<br/>");

        $this->form->addElement('static', null, "The following two fields refer to Date and Coder for the CSBS");
        $this->addDateElement("date_coded", "Date of Coding:", $this->dateOptions);
        $this->addTextElement("coder", "Coder:");

        $this->form->addElement("static", null, "<br/>");

//        $this->addTextElement("filled_out_by", "Filled out by:");
        $this->form->addElement("select", "relationship_to_child", "Relationship to child:", array(null=>"", "1_Mother"=>"1. Mother", "2_Father"=>"2. Father", "3_Other"=>"3. Other (Specify)", "not_answered"=>"Not Answered"));
        $this->addTextElement("relationship_to_child_specify", $this->indent . "If other is selected, specify:", array("relationship_to_child{@}=={@}3_Other"), "Please specify.");

        $this->form->addElement("static", null, "<br/>");
        
        $this->form->addElement("static", null, "Circle the response that comes closest to your observations.");
        
        $this->form->addElement("select", "q_1_alertness", "1. Alertness", array(null=>"", "1_less_than_usual"=>"1. less than usual/sleepy", "2_typical"=>"2. typical", "3_very_alert_greater"=>"3. very alert / greater than usual", "not_answered"=>"Not Answered"));
        $this->XINRegisterRule("q_1_alertness", array("q_1_alertness{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement("select", "q_2_emotional_reaction", "2. Emotional reaction", array(null=>"", "1_more_negative"=>"1. more negative than usual", "2_typical"=>"2. typical", "3_more_positive"=>"3. more positive than usual", "not_answered"=>"Not Answered"));
        $this->XINRegisterRule("q_2_emotional_reaction", array("q_2_emotional_reaction{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement("select", "q_3_level_of_interest", "3. Level of interest and attention", array(null=>"", "1_less_interest"=>"1. less interest than usual", "2_typical"=>"2. typical", "3_greater"=>"3. greater interest / greater attention", "not_answered"=>"Not Answered"));
        $this->XINRegisterRule("q_3_level_of_interest", array("q_3_level_of_interest{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement("select", "q_4_comfort_level", "4. Comfort level", array(null=>"", "1_more_cautious"=>"1. more cautious", "2_typical"=>"2. typical", "3_more_comfortable"=>"3. more confortable", "not_answered"=>"Not Answered"));
        $this->XINRegisterRule("q_4_comfort_level", array("q_4_comfort_level{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement("select", "q_5_level_of_activity", "5. Level of activity", array(null=>"", "1_less_active"=>"1. less active than usual", "2_typical"=>"2. typical", "3_more_active"=>"3. more active than usual", "not_answered"=>"Not Answered"));
        $this->XINRegisterRule("q_5_level_of_activity", array("q_5_level_of_activity{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement("select", "q_6_level_of_communication", "6. Overall level of communication", array(null=>"", "1_less_than_usual"=>"1. less than usual", "2_typical"=>"2. typical", "3_greater_than_usual"=>"3. greater than usual", "not_answered"=>"Not Answered"));
        $this->XINRegisterRule("q_6_level_of_communication", array("q_6_level_of_communication{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement("select", "q_7_play_behaviour", "7. Play behavior", array(null=>"", "1_less_organized"=>"1. less organized", "2_typical"=>"2. typical", "3_more_organized"=>"3. more organized", "not_answered"=>"Not Answered"));
        $this->XINRegisterRule("q_7_play_behaviour", array("q_7_play_behaviour{@}=={@}NEVER_REQUIRED"));
//        $this->form->addElement("select", "q_", "", array(null=>"", "1_"=>"1. ", "2_typical"=>"2. typical", "3_"=>"3. ", "not_answered"=>"Not Answered"));
        if (isset($_REQUEST['commentID'])) { 

        $this->addTextAreaElement("comments", "Comments:");

	$this->form->addElement("header",null,"Summary Scores:");
	
		$this->form->addElement("static",null,"</br>");
	$this->form->addElement("header","score_validity",null);
	$this->form->addElement("static",null,"</br>");
	
	$group[]= &$this->form->createElement("static", "raw_weighted", null);
        $group[]= &$this->form->createElement("static", "standard_score", null);
        $group[]= &$this->form->createElement("static", "percentile_rank", null);
  	$this->form->addGroup($group, null, 'Subscale', $this->_GUIDelimiter, false);
        unset($group);
	

	$group[]= &$this->form->createElement("static", "emotion_eye_gaze_weighted", null);
        $group[]= &$this->form->createElement("static", "emotion_eye_gaze_standard", null);
        $group[]= &$this->form->createElement("static", "emotion_eye_gaze_percentile", null);
  	$this->form->addGroup($group, null, "Emotion and Eye Gaze", $this->_GUIDelimiter, false);
        unset($group);

	

        $group[]= &$this->form->createElement("static", "communication_weighted", null);
        $group[]= &$this->form->createElement("static", "communication_standard", null);
        $group[]= &$this->form->createElement("static", "communication_percentile", null);
  	$this->form->addGroup($group, null, "Communication", $this->_GUIDelimiter, false);
        unset($group);


	$group[]= &$this->form->createElement("static", "gestures_weighted", null);
        $group[]= &$this->form->createElement("static", "gestures_standard", null);
        $group[]= &$this->form->createElement("static", "gestures_percentile", null);
  	$this->form->addGroup($group, null, "Gestures", $this->_GUIDelimiter, false);
        unset($group);


	$group[]= &$this->form->createElement("static", "sounds_weighted", null);
        $group[]= &$this->form->createElement("static", "sounds_standard", null);
        $group[]= &$this->form->createElement("static", "sounds_percentile", null);
  	$this->form->addGroup($group, null, "Sounds", $this->_GUIDelimiter, false);
        unset($group);

	$group[]= &$this->form->createElement("static", "words_weighted", null);
        $group[]= &$this->form->createElement("static", "words_standard", null);
        $group[]= &$this->form->createElement("static", "words_percentile", null);
  	$this->form->addGroup($group, null, "Words", $this->_GUIDelimiter, false);
        unset($group);


	$group[]= &$this->form->createElement("static", "understanding_weighted", null);
        $group[]= &$this->form->createElement("static", "understanding_standard", null);
        $group[]= &$this->form->createElement("static", "understanding_percentile", null);
  	$this->form->addGroup($group, null, "Understanding", $this->_GUIDelimiter, false);
        unset($group);
 

        $group[]= &$this->form->createElement("static", "object_use_weighted", null);
        $group[]= &$this->form->createElement("static", "object_use_standard", null);
        $group[]= &$this->form->createElement("static", "object_use_percentile", null);
        $this->form->addGroup($group, null, "Object Use", $this->_GUIDelimiter, false);
        unset($group);


        $group[]= &$this->form->createElement("static", "social_composite_score", null);
        $group[]= &$this->form->createElement("static", "social_composite_standard", null);
        $group[]= &$this->form->createElement("static", "social_composite_percentile", null);
        $this->form->addGroup($group, null, "Social Composite", $this->_GUIDelimiter, false);
        unset($group);


        $group[]= &$this->form->createElement("static", "speech_composite_score", null);
        $group[]= &$this->form->createElement("static", "speech_composite_standard", null);
        $group[]= &$this->form->createElement("static", "speech_composite_percentile", null);
        $this->form->addGroup($group, null, "Speech Composite", $this->_GUIDelimiter, false);
        unset($group);


        $group[]= &$this->form->createElement("static", "symbolic_composite_score", null);
        $group[]= &$this->form->createElement("static", "symbolic_composite_standard", null);
        $group[]= &$this->form->createElement("static", "symbolic_composite_percentile", null);
        $this->form->addGroup($group, null, "Symbolic Composite", $this->_GUIDelimiter, false);
        unset($group);


	$group[]= &$this->form->createElement("static", "total_weighted_raw_score", null);
        $group[]= &$this->form->createElement("static", "total_standard", null);
        $group[]= &$this->form->createElement("static", "total_percentile", null);
  	$this->form->addGroup($group, null, "Total", $this->_GUIDelimiter, false);
        unset($group);
      }
    }
    
    function score(){
    	if($this->_determineDataEntryCompletionStatus() == "Incomplete") {
    		return;
    	}

        //null scores
		$this->_nullScores($this->scoreLabels);
		
        //get the saved scores
    	$db =& Database::singleton();
  	
	
    	$query = "SELECT * FROM $this->table WHERE CommentID = '$this->commentID'";
    	$record = array();
    	$db->selectRow($query, $record);
       $scores['score_validity'] = "";	
       // Get the subject age in months for scoring
        $timepoint =& TimePoint::singleton($this->getSessionID());
        $dob = $timepoint->getEffectiveDateOfBirth();
        
		$age = Utility::calculateAge($dob, $record["Date_taken"]);
       		$age_months = $age['year'] * 12 + $age['mon'] + ($age['day']/30);

	if ($age_months >= 11.75 && $age_months < 12)
		$age_months = 12;
		
	elseif ($age_months <= 24.75 && $age_months > 24)
		$age_months = 24;

	elseif ($age_months > 24.75) {
		$age_months = 24;
        $scores['score_validity'] = "<span class=\"error\">CANDIDATE'S AGE IS OUT OF RANGE. STANDARD SCORES ARE INVALID.</span>";
    }
    $age_months = round($age_months);


  	//calculate raw scores
        $scores["q_1_gaze_shifts_raw_score"] = $this->_countChecked($record, "q_1_gaze_shifts_");
        $scores["q_2_shared_positive_affect_raw_score"] = $this->_countChecked($record, "q_2_shared_positive_affect_");
        $scores["q_3_gaze_point_following_raw_score"] = $this->_countChecked($record, "q_3_gaze_point_following_");

        foreach($record as $field=>$value) {
            if(preg_match("/q_4_rate_of_communicating/", $field)) {
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
        if(empty($scores["q_13_words_raw_score"])){
            $scores["q_13_words_raw_score"]  = 0;   
        }
        $scores["q_14_word_combos_raw_score"] = $this->_countChecked($record, "q_14_word_combos_");
        $scores["q_15_word_combos_raw_score"] = $this->_countWords($record, "q_15_word_combos_");
        if(empty($scores["q_15_word_combos_raw_score"])){
            $scores["q_15_word_combos_raw_score"]  = 0;   
        }

        $scores["q_17_action_schemes_raw_score"] = $this->_countCheckedNone($record, "q_17_action_schemes_", "q_17_action_schemes_none");
       // $scores["q_17_action_schemes_raw_score"] = $this->_countChecked($record, "q_17_action_schemes_");
        $scores["q_18_actions_towards_other_raw_score"] = $this->_countActionTowardsOther($record, 6);
        $scores["q_19_sequence_action_schemes_raw_score"] = $this->_countAction1($record, 6);
        if (is_numeric(intval(substr($record["q_20_stacks_tower"], 0, 1)))) {
            $scores["q_20_stacks_tower_raw_score"] = intval(substr($record["q_20_stacks_tower"], 0, 1));
        } else {
            $scores["q_20_stacks_tower_raw_score"] = 0;
        }
    	
        // Do q16 specially
        // If 2 scores in a category are 0, the rest should be 0 too.
        // Minimum of 2 scores required. Otherwise, "Unable to score"
        // Otherwise, score is: best 3 objects*3 + best 2 persons * 3 + best 3 body * 3
        $q_16_BestObject = null;
        $q_16_BestPerson = null;
        $q_16_BestBody = null;

        if( ($record["q_16_language_comp_objects_1"] === "0" || $record["q_16_language_comp_objects_1"] === 0) &&
            ($record["q_16_language_comp_objects_2"] === "0" || $record["q_16_language_comp_objects_2"] === 0) ) {
            $q_16_BestObject = 0;
        } else {
            $q_16_BestObject = $this->_sumBestRows($record, "objects", 3, 4);
        }
        if( ($record["q_16_language_comp_person_1"] === "0" || $record["q_16_language_comp_person_1"] === 0) &&
            ($record["q_16_language_comp_person_2"] === "0" || $record["q_16_language_comp_person_2"] === 0) ) {
            $q_16_BestPerson = 0;
        } else {
            $q_16_BestPerson = $this->_sumBestRows($record, "person", 2, 3);
        }
        if( ($record["q_16_language_comp_body_parts_1"] === "0" || $record["q_16_language_comp_body_parts_1"] === 0) &&
            ($record["q_16_language_comp_body_parts_2"] === "0" || $record["q_16_language_comp_body_parts_2"] === 0) ) {
            $q_16_BestBody= 0;
        } else {
            $q_16_BestBody= $this->_sumBestRows($record, "body_parts", 3, 4);
        }

    $scores["q_16a_language_comp_object_raw_score"] = $q_16_BestObject;
    $scores["q_16b_language_comp_person_name_raw_score"] = $q_16_BestPerson;
    $scores["q_16c_language_comp_body_parts_raw_score"] = $q_16_BestBody;

	$scores["q_16_language_comp_body_parts_raw_score"] = $q_16_BestObject + $q_16_BestPerson + $q_16_BestBody;

        $scores["understanding_weighted"] = ($q_16_BestObject + $q_16_BestPerson + $q_16_BestBody) * 3;
        // At least two answers are required. The >= is different for person because there's
        // only 3 opportunities for that table column
        if($this->_countUnanswered($record, "objects", 4) >= 3 ||
            $this->_countUnanswered($record, "person", 3) >= 2 ||
            $this->_countUnanswered($record, "body_parts", 4) >= 3) {
            $scores["understanding_weighted"] = "Unable to score";

        }

    	//calculate subscales
        $scores["emotion_eye_gaze_weighted"] = $scores["q_1_gaze_shifts_raw_score"] +
        $scores["q_2_shared_positive_affect_raw_score"] +
        3 * $scores["q_3_gaze_point_following_raw_score"];

        $scores["communication_weighted"] = number_format(($scores["q_4_rate_of_communicating_raw_score"]/3), 0) +
 	$scores["q_5_behaviour_regulation_raw_score"] +
        $scores["q_6_social_interaction_raw_score"] +
        $scores["q_7_joint_attention_raw_score"];

        $scores["gestures_weighted"] = $scores["q_8_conventional_gestures_raw_score"] * 2 + 
        $scores["q_9_distal_gestures_raw_score"];

        $scores["sounds_weighted"] = $scores["q_10_syllables_consonants_raw_score"] +
        2 * $scores["q_11_inventory_of_consonants_raw_score"];
        
        $scores["words_weighted"] = number_format(($scores["q_12_words_raw_score"] + 
                                        ($scores["q_13_words_raw_score"]/2) +  
                                        $scores["q_14_word_combos_raw_score"] +
                                        $scores["q_15_word_combos_raw_score"]), 0);
        
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
	$scores['emotion_eye_gaze_standard']=($record_1['score_standard']);
	$scores['emotion_eye_gaze_percentile']=($record_1['score_percentile']);


	$query_scores2 = "SELECT * FROM csbs_lookup WHERE age_months=".$age_months. " AND score_weighted=".$scores['communication_weighted']." AND subscale='communication_weighted'";
    	$record_2 = array();
	$db->selectRow($query_scores2, $record_2);
	$scores['communication_standard']=($record_2['score_standard']);
	$scores['communication_percentile']=($record_2['score_percentile']);


	$query_scores3 = "SELECT * FROM csbs_lookup WHERE age_months=".$age_months. " AND score_weighted=".$scores['gestures_weighted']." AND subscale='gestures_weighted'";
    	$record_3 = array();
	$db->selectRow($query_scores3, $record_3);
	$scores['gestures_standard']=($record_3['score_standard']);
	$scores['gestures_percentile']=($record_3['score_percentile']);


	$query_scores4 = "SELECT * FROM csbs_lookup WHERE age_months=".$age_months. " AND score_weighted=".$scores['sounds_weighted']." AND subscale='sounds_weighted'";
    	$record_4 = array();
	$db->selectRow($query_scores4, $record_4);
	$scores['sounds_standard']=($record_4['score_standard']);
	$scores['sounds_percentile']=($record_4['score_percentile']);


	$query_scores5 = "SELECT * FROM csbs_lookup WHERE age_months=".$age_months. " AND score_weighted=".$scores['words_weighted']." AND subscale='words_weighted'";
    	$record_5 = array();
	$db->selectRow($query_scores5, $record_5);
	$scores['words_standard']=($record_5['score_standard']);
	$scores['words_percentile']=($record_5['score_percentile']);



    if($scores['understanding_weighted'] !== "Unable to score") {
        $query_scores6 = "SELECT * FROM csbs_lookup WHERE age_months=".$age_months. " AND score_weighted=".$scores['understanding_weighted']." AND subscale='understanding_weighted'";
        $record_6 = array();
        $db->selectRow($query_scores6, $record_6);
        $scores['understanding_standard']=($record_6['score_standard']);
        $scores['understanding_percentile']=($record_6['score_percentile']);
    } else {
        $scores['understanding_standard']= 'Unable to score';
        $scores['understanding_percentile']= 'Unable to score';
    }



	$query_scores7 = "SELECT * FROM csbs_lookup WHERE age_months=".$age_months. " AND score_weighted=".$scores['object_use_weighted']." AND subscale='object_use_weighted'";
    	$record_7 = array();
	$db->selectRow($query_scores7, $record_7);
	$scores['object_use_standard']=($record_7['score_standard']);
	$scores['object_use_percentile']=($record_7['score_percentile']);


	$query_scores8 = "SELECT * FROM csbs_lookup WHERE age_months=".$age_months. " AND score_weighted=".$scores['social_composite_score']." AND subscale='social_composite_score'";
    	$record_8 = array();
	$db->selectRow($query_scores8, $record_8);
	$scores['social_composite_standard']=($record_8['score_standard']);
	$scores['social_composite_percentile']=($record_8['score_percentile']);



	$query_scores9 = "SELECT * FROM csbs_lookup WHERE age_months=".$age_months. " AND score_weighted=".$scores['speech_composite_score']." AND subscale='speech_composite_score'";
    	$record_9 = array();
	$db->selectRow($query_scores9, $record_9);
	$scores['speech_composite_standard']=($record_9['score_standard']);
	$scores['speech_composite_percentile']=($record_9['score_percentile']);



	$query_scores10 = "SELECT * FROM csbs_lookup WHERE age_months=".$age_months. " AND score_weighted=".$scores['symbolic_composite_score']." AND subscale='symbolic_composite_score'";
    	$record_10 = array();
	$db->selectRow($query_scores10, $record_10);
	$scores['symbolic_composite_standard']=($record_10['score_standard']);
	$scores['symbolic_composite_percentile']=($record_10['score_percentile']);



	$query_scores11 = "SELECT * FROM csbs_lookup WHERE age_months=".$age_months. " AND score_weighted=".$scores['total_weighted_raw_score']." AND subscale='total_weighted_raw_score'";
    	$record_11 = array();
	$db->selectRow($query_scores11, $record_11);
	$scores['total_standard']=($record_11['score_standard']);
	$scores['total_percentile']=($record_11['score_percentile']);
/*
	$query_scores_OUTOFRANGE = "SELECT * FROM csbs_lookup WHERE age_months = '24' AND score_weighted = ".$scores['total_weighted_raw_score']." AND subscale='total_weighted_raw_score'";
	$record_OUTOFRANGE = array();
	$db->selectRow($query_scores_OUTOFRANGE, $record_OUTOFRANGE);
	
*/

	// save scores
	$result = $db->update($this->table, $scores, array("CommentID"=>$this->getCommentID()));
		
    }    // end score function


    function _page1(){
	//Administration
        $this->form->addElement("header", null, "Administration of activities");
        $this->form->addElement("select", "wind_up_admin", "1. Wind-up toy", array(null=>"", "fully_admin"=>"Fully Administered", "partially_admin"=>"Partially Administered (please specify)", "not_admin"=>"Not Administered"));
        $this->form->addElement("select", "balloon_admin", "2. Balloon", array(null=>"", "fully_admin"=>"Fully Administered", "partially_admin"=>"Partially Administered (please specify)", "not_admin"=>"Not Administered"));
        $this->form->addElement("select", "bubbles_admin", "3. Bubbles", array(null=>"", "fully_admin"=>"Fully Administered", "partially_admin"=>"Partially Administered (please specify)", "not_admin"=>"Not Administered"));
        $this->form->addElement("select", "jar_admin", "4. Jar", array(null=>"", "fully_admin"=>"Fully Administered", "partially_admin"=>"Partially Administered (please specify)", "not_admin"=>"Not Administered"));
        $this->form->addElement("select", "books_admin", "5. Books", array(null=>"", "fully_admin"=>"Fully Administered", "partially_admin"=>"Partially Administered (please specify)", "not_admin"=>"Not Administered"));
        $this->form->addElement("select", "play_admin", "6. Play", array(null=>"", "fully_admin"=>"Fully Administered", "partially_admin"=>"Partially Administered (please specify)", "not_admin"=>"Not Administered"));
        $this->form->addElement("header", null, "If you selected 'Partially Administered' for any of the items above, please specify in the comments box on the top page.");
        $this->form->addElement("static", null, "</br>");
        $this->form->addElement("static", null, "</br>");


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
        $group[] = &$this->form->createElement("static", "q_8_conventional_gestures_raw_score");
        $this->form->addGroup($group, null, "8. Inventory of conventional gestures", $this->_GUIDelimiter, false);
        unset($group);
        $group[] = &$this->form->createElement("advcheckbox", "q_8_conventional_gestures_points", null, "points", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_8_conventional_gestures_waves", null, "waves", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_8_conventional_gestures_nods_head", null, "nods head", null, array("unchecked", "checked"));
        $group[] = &$this->form->addElement('static', null);
        $group[] = &$this->form->createElement("advcheckbox", "q_8_conventional_gestures_shakes_head", null, "shakes head", null, array("unchecked", "checked"));
        $this->form->addGroup($group, null, null, $this->_GUIDelimiter, false);
        $this->form->addElement('static', '', '<br />');
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
        $this->form->addElement('static', '', '<br />');
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
    
    function _sumBestRows($values, $name, $bestrows, $numrows) {
        $BestSoFar = array();
        for($row = 1; $row <= $numrows; $row++) {
            if(!is_numeric($values["q_16_language_comp_{$name}_{$row}"])) {
                continue;
            }

            if(count($BestSoFar) == $bestrows) {
                // If we've already found n numbers, check if this one's better than
                // one of the previous ones
                for($i = 0; $i < count($BestSoFar); $i++) {
                    if($BestSoFar[$i] < $values["q_16_language_comp_{$name}_{$row}"]) {
                        $BestSoFar[$i] = $values["q_16_language_comp_{$name}_{$row}"];
                        break;
                    }
                }
            } else {
                // Otherwise, just take this row since we haven't even found n
                // yet
                $BestSoFar[] = $values["q_16_language_comp_{$name}_{$row}"];
            }
        }
        return array_sum($BestSoFar);
    }

    // For scoring q_16
    function _countUnanswered($values, $name, $rows) {
        $number = 0;
        for($row = 1; $row <= $rows; $row++) {
            if($values["q_16_language_comp_{$name}_{$row}"] === null || $values["q_16_language_comp_{$name}_{$row}"] === '' ||
                $values["q_16_language_comp_{$name}_{$row}"] === 'NA') {
                $number++;
            }
        }
        return $number;
    }
    // For scoring q_18
    function _countActionTowardsOther($values, $rows) {
        $number = 0;
        for($row = 1; $row <= $rows; $row++) {
            if($values["q_18_action_towards_other_{$row}"] !== '' && 
                    $values["q_18_action_towards_other_{$row}"] !== 'none' && !is_null($values["q_18_action_towards_other_{$row}"])) {
                $number++;
            }
        }
        return $number;
    }
    // For scoring q_19
    function _countAction1($values, $rows) {
        $number = 0;
        for($row = 1; $row <= $rows; $row++) {
            if($values["q_19_sequence_action_schemes_{$row}_action1"] !== '' && 
                    $values["q_19_sequence_action_schemes_{$row}_action1"] !== 'none' && !is_null($values["q_19_sequence_action_schemes_{$row}_action1"])) {
                $number++;
            }
        }
        return $number;
    }

    function _countTableZeros($values, $name, $rows) {
        $number = 0;
        for($row = 1; $row <= $rows; $row++) {
            // Use === to ensure that null isn't interpreted as 0.
            // Always getting a string, since we're getting values from a form.
            // But add or === to 0 too, just in case somehow the data gets converted
            // to an int (ie when pulling from the database)
            if($values["q_16_language_comp_{$name}_{$row}"] === "0" || $values["q_16_language_comp_{$name}_{$row}"] === 0) {
                $number++;
            }
        }
        return $number;
    }

    function _addTableRow($desc, $name, $rows) {
        for($row = 1; $row <= $rows; $row++) {
            $groupname = "q_16_language_comp_" . $name . "_" . $row . "_group";
            $elname = "q_16_language_comp_{$name}_{$row}_name";
            $scorename = "q_16_language_comp_{$name}_{$row}";
           
            $group[] =& $this->form->createElement('static', null, null, "$desc #$row");
            $group[] =& $this->form->createElement("text", $elname);
            $group[] =& $this->form->createElement("select", $scorename, null, array('' => '', 0 => 0, 1 => 1, 'NA' => 'Not Administered'));
            // Require score

            $this->XINRegisterRule($scorename, array("$elname{@}!={@}NULL"), "Score required.", $groupname);
            $this->XINRegisterRule($elname, array("$elname{@}=={@}NEVER_REQUIRED"), "Name required.", $groupname);
            $this->form->addGroup($group, $groupname, null, $this->_GUIDelimiter, false);
            unset($group);
        }
    }

    function _addNoActionsPerformed($element, $actions_array, $row=1) {
        if($row == 1) {
            return $this->form->createElement("select", $element, null, array_merge($actions_array, array('none' => "No actions performed")));
        }
        return $this->form->createElement("select", $element, null, array_merge($actions_array, array('none' => "No more actions performed")));
    }
    function _page2() {
        // Setting up the 6 column grid
        for($int = 1; $int <= 6; $int++) {
            $group[]= &$this->form->createElement("static", null, $this->indent);
        }
        $group[]= &$this->form->createElement("static", "raw_score", null);
        $this->form->addGroup($group, null, null, $this->_GUIDelimiter, false);
        unset($group);
        
        //Understanding
        $this->form->addElement("header", null, "Understanding");

        $group[] = &$this->form->createElement("static", null, null, "Item");
        $group[] = &$this->form->createElement("static", null, null, "Name");
        $group[] = &$this->form->createElement("static", null, null, "Score");
        $group[] =& $this->form->createElement("static", null, null, null);
        $group[] =& $this->form->createElement("static", null, null, null);
        $group[] =& $this->form->createElement("static", null, null, null);

        $this->form->addGroup($group, "q_16_language_comp_objects_headers", "16. Language comprehension" . $this->indent, $this->_GUIDelimiter, false);
        unset($group);

        $this->_addTableRow("Object", "objects", 4);
        $group[] =& $this->form->createElement('static', null, null, "&nbsp;");
        $this->form->addElement('static', '', '<br />');
        $this->form->addElement("static", "q_16a_language_comp_object_raw_score","Object Raw Score:" );
        $this->form->addGroup($group, null, null, $this->_GUIDelimiter, false);
        unset($group);
        $this->_addTableRow("Person Name", "person", 3);
        $group[] =& $this->form->createElement('static', null, null, "&nbsp;");
        $this->form->addElement('static', '', '<br />');
        $this->form->addElement("static", "q_16b_language_comp_person_name_raw_score","Person Name Raw Score:" );
        $this->form->addGroup($group, null, null, $this->_GUIDelimiter, false);
        unset($group);
        $this->_addTableRow("Body Parts", "body_parts", 4);
        $this->form->addElement('static', '', '<br />');
        $this->form->addElement('static', '', '<br />');
        $this->form->addElement("static", "q_16c_language_comp_body_parts_raw_score","Body Parts Raw Score:" );
      $this->form->addGroup($group, null, null, $this->_GUIDelimiter, false);
        unset($group);
 
       $this->form->addElement("static", "understanding_weighted", "Weighted Raw Score for Scale 16 - Understanding:");
       

        //Object Use
        $this->form->addElement("header", null, "Object Use");
        $group[] = &$this->form->createElement("advcheckbox", "q_17_action_schemes_puts_in", null, "puts in(1)", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_17_action_schemes_puts_on", null, "puts on(2)", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_17_action_schemes_drinks_with_bottle", null, "drinks with bottle(3)", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_17_action_schemes_drinks_with_cup", null, "drinks with cup(4)", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_17_action_schemes_hugs", null, "hugs(5)", null, array("unchecked", "checked"));

        $this->form->addGroup($group, "q_17_action_schemes_group_1", "17. Inventory of action schemes", $this->_GUIDelimiter, false);
        unset($group);
        $group[] = &$this->form->createElement("advcheckbox", "q_17_action_schemes_kisses", null, "kisses(6)", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_17_action_schemes_feeds_with_utensil", null, "feeds with utensil(7)", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_17_action_schemes_feeds_with_bowl", null, "feeds with bowl(8)", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_17_action_schemes_stirs", null, "stirs(9)", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_17_action_schemes_scoops", null, "scoops(10)", null, array("unchecked", "checked"));

        $this->form->addGroup($group, "q_17_action_schemes_group_2", null, $this->_GUIDelimiter, false);
        unset($group);
        //$group[] = &$this->form->createElement("static", null, null);
        $group[] = &$this->form->createElement("advcheckbox", "q_17_action_schemes_pours", null, "pours(11)", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_17_action_schemes_other", null, "other(12)", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("text", "q_17_action_schemes_other_specify");
        $group[] =& $this->form->createElement("advcheckbox", "q_17_action_schemes_none", null, "none", null, array("unchecked", "checked"));
        $group[] =& $this->form->createElement("static", null, null, null);
        $group[] =& $this->form->createElement("static", null, null, null);
        $this->form->addGroup($group, null, null, $this->_GUIDelimiter, false);
        unset($group);

        $this->XINRegisterRule("q_17_action_schemes_other_specify", array("q_17_action_schemes_other{@}=={@}checked"), "Must specify other", "q_17_action_schemes_group_2");
        $this->form->addGroup($group, "q_17_action_schemes_group_2", null, $this->_GUIDelimiter, false);
        $this->form->addElement('static', '', '<br />');
        $this->form->addElement("static","q_17_action_schemes_raw_score","Object Use Raw Score:" );
        unset($group);
        
        //Action schemes towards other
        $this->form->addElement('static', '', '<br />');

        $group[] = &$this->form->createElement("static", null, null, "Action");
        $group[] = &$this->form->createElement("static", null, null, "Agent");
        $group[] = &$this->form->createElement("static", null, null, "Other Agent");
        $group[] = &$this->form->createElement("static", null, null, null);
        $group[] = &$this->form->createElement("static", null, null, null);
        $group[] = &$this->form->createElement("static", null, null, null);

        $this->form->addGroup($group, "q_18_actions_towards_other_headers", "18. Action schemes towards other" . $this->indent, $this->_GUIDelimiter, false);
        unset($group);
        $actions_array = array(
            '' => '',
            'puts_in' => '1. Puts in',
            'puts_on' => '2. Puts on',
            'drinks_with_bottle' => '3. Drinks with bottle',
            'drinks_with_cup' => '4. Drinks with cup',
            'hugs' => '5. Hugs',
            'kisses' => '6. Kisses',
            'feeds_with_utensil' => '7. Feeds with utensil',
            'feeds_with_bowl' => '8. Feeds with bowl',
            'stirs' => '9. Stirs',
            'scoops' => '10. Scoops',
            'pours' => '11. Pours',
            'other' => '12. Other'
        );
        for($i = 1; $i <= 6; $i++) {
            $group[] =& $this->_addNoActionsPerformed("q_18_action_towards_other_{$i}", $actions_array, $i);
            $group[] =& $this->form->createElement("select", "q_18_action_towards_other_{$i}_agent", null, array(
                '' => '',
                'parent' => 'Parent',
                'clinician' => 'Clinician',
                'toy' => 'Toy',
                'other' => 'Other (Specify)'
            ));
            $group[] =& $this->form->createElement("text", "q_18_action_towards_other_{$i}_agent_specify");
            $this->XINRegisterRule("q_18_action_towards_other_{$i}_agent_specify", array("q_18_action_towards_other_{$i}_agent{@}=={@}other"), "Specify agent required.", "q_18_action_towards_other_group{$i}");
            // Require the first dropdown. Even though XIN rules requires things by default, we explicitly require it
            // to make sure the error message shows up, since it's part of a group.
            if($i == 1) {
                $this->XINRegisterRule("q_18_action_towards_other_{$i}", array("q_18_action_towards_other_{$i}{@}=={@}"), "Required.", "q_18_action_towards_other_group{$i}");
            } else {
                // Require dropdown n if n-1 is answered and not 'No (more) actions performed'
                $this->XINRegisterRule("q_18_action_towards_other_{$i}", array("q_18_action_towards_other_" . ($i-1) . "{@}!={@}none", "q_18_action_towards_other_" . ($i-1) . "{@}!={@}"), "Required.", "q_18_action_towards_other_group{$i}");
            }
            // Require the second dropdown if the first one is answered
            $this->XINRegisterRule("q_18_action_towards_other_{$i}_agent", array("q_18_action_towards_other_{$i}{@}!={@}", "q_18_action_towards_other_{$i}{@}!={@}none"), "Agent required.", "q_18_action_towards_other_group{$i}");
            $this->form->addGroup($group, "q_18_action_towards_other_group{$i}", null, $this->_GUIDelimiter, false);
            unset($group);
        }
        $this->form->addElement('static', '', '<br />');

        $this->form->addElement("static","q_18_actions_towards_other_raw_score","Actions Towards Other Raw Score:" );
        $this->form->addElement('static', '', '<br />');

        $group[] = &$this->form->createElement("static", null, null, "1st Action");
        $group[] = &$this->form->createElement("static", null, null, "2nd Action");
        $group[] = &$this->form->createElement("static", null, null, null);
        $group[] = &$this->form->createElement("static", null, null, null);
        $group[] = &$this->form->createElement("static", null, null, null);
        $group[] = &$this->form->createElement("static", null, null, null);

        //Sequence action schemes
        $this->form->addGroup($group, "q_19_sequence_action_schemes_headers", "19. Sequence action schemes" . $this->indent, $this->_GUIDelimiter, false);
        unset($group);
        for($i = 1; $i <= 6; $i++) {
            $group[] = $this->_addNoActionsPerformed("q_19_sequence_action_schemes_{$i}_action1", $actions_array, $i);
            $group[] = $this->form->createElement("select", "q_19_sequence_action_schemes_$i" . "_action2", null, $actions_array);
            // Require the first dropdown. Even though XIN rules requires things by default, we explicitly require it
            // to make sure the error message shows up, since it's part of a group.
            if($i == 1) {
                $this->XINRegisterRule("q_19_sequence_action_schemes_{$i}_action1", array("q_19_sequence_action_schemes_{$i}_action1{@}=={@}"), "Required.", "q_19_sequence_action_schemes_group{$i}");
            } else {
                // Require dropdown n if n-1 is answered and not 'No (more) actions performed'
                $this->XINRegisterRule("q_19_sequence_action_schemes_{$i}_action1", array("q_19_sequence_action_schemes_" . ($i-1) . "_action1{@}!={@}none", "q_19_sequence_action_schemes_" . ($i-1) . "_action1{@}!={@}"), "Required.", "q_19_sequence_action_schemes_group{$i}");
            }
            $this->XINRegisterRule("q_19_sequence_action_schemes_{$i}_action2", array("q_19_sequence_action_schemes_{$i}_action1{@}!={@}none", "q_19_sequence_action_schemes_{$i}_action1{@}!={@}"), "Action 2 Required.", "q_19_sequence_action_schemes_group{$i}");
            $this->form->addGroup($group, "q_19_sequence_action_schemes_group{$i}", null, $this->_GUIDelimiter, false);
            unset($group);
        }
        $this->form->addElement('static', '', '<br />');
        $this->form->addElement("static","q_19_sequence_action_schemes_raw_score","Sequence Action Schemes Raw Score:" );

        $this->form->addElement('static', '', '<br />');

        //Stacks tower of blocks
        $group[] = &$this->form->createElement("select", "q_20_stacks_tower", "20. Stacks tower of blocks", array(null=>"", "0_refuses"=>"0 - Refuses",
                                "1_tries_but_fails"=>"1 - Tries but fails",
                                "2_stacks"=>"Stacks 2",
                                "3_stacks"=>"Stacks 3",
                                "4_stacks"=>"Stacks 4",
                                "5_stacks"=>"Stacks 5",
                                "not_administered"=>"Not Administered"));
        $group[] =& $this->form->createElement("static", null, null, null);
        $group[] =& $this->form->createElement("static", null, null, null);
        $group[] =& $this->form->createElement("static", null, null, null);
        $group[] =& $this->form->createElement("static", null, null, null);
        $group[] =& $this->form->createElement("static", null, null, null);
        $this->XINRegisterRule("q_20_stacks_tower", array("q_20_stacks_tower{@}=={@}"), "Required.", "q_20_stacks_tower_group");
        $this->form->addGroup($group, "q_20_stacks_tower_group", "20. Stacks tower of blocks", $this->_GUIDelimiter, false);
        unset($group); 
        $this->form->addElement('static', '', '<br />');
        $this->form->addElement("static","q_20_stacks_tower_raw_score","Stacks Tower Raw Score:" );

        $this->form->addElement("static", null, "<br />");
        $this->form->addElement("static", "object_use_weighted", "Weighted Raw Scores for Scales 17, 18, 19, and 20 - Object Use:");

    }
    
    function _countChecked($record, $genericLabel) {
        foreach ($record as $field=>$value) {
            if (preg_match("/$genericLabel/", $field)) {
                $score += ($value == "checked");
            }
        }
        return $score;
    }

    function _countCheckedNone($record, $genericLabel, $option)
    {
	foreach ($record as $field=>$value)
	{
        	if (preg_match("/$genericLabel/", $field) && $field != $option)
		{
                	$score += ($value == "checked");
		}
	}
	return $score;
    }


    function _countWords($record, $genericLabel, $excludedWords = array()) {
        foreach($record as $field=>$value) {
            if(preg_match("/$genericLabel/", $field) && !is_null($value) && $value !== '') {
                if(!in_array($value, $excludedWords)) {
                    $score++; 
                }
            }
        }
        return $score;
    }
    
    function _printHeaderCols() {
        // Setting up the scoring grid
        for($int = 1; $int <= 6; $int++) {
            $group[]= &$this->form->createElement("static", "h_" . $int, null);
        }
       // $group[]= &$this->form->createElement("static", "raw_score", null);
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
