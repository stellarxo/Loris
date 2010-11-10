<?php
function TrialName($press, $trial) {
	return "3_orients_to_name_press_" . $press . 
	"_trial_" . $trial;
}
class NDB_BVL_Instrument_aosi extends NDB_BVL_Instrument
{
/**
INSERT INTO test_names VALUES ('', 'aosi', 'AOSI', '0', '1');
INSERT INTO instrument_subtests VALUES('', 'aosi', 'aosi_page1', 'Item Adminstration', 1);
INSERT INTO instrument_subtests VALUES('', 'aosi', 'aosi_page2', 'General Observations', 2);
-- INSERT INTO test_battery VALUES ('', 'aosi', '1050', '1140', 'Y', 'Visit', '2');
**/

    var $scores = array("total_score_1_18"=>"", 
                        "total_score_1_18_override" => "",
                        "number_of_markers"=>"",
                        "number_of_markers_override"=>"",
                        "1_visual_tracking_score"=>"",
                        "2_disengagement_of_attention_score"=>"",
                        "3_orients_to_name_score"=>"",
                        "4_differential_response_to_facial_emotion_score"=>"",
                        "5_anticipatory_response_score"=>"",
                        "6_imitation_of_actions_score"=>"");


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
        $this->testName = "aosi";           // test_names.Test_name
        $this->table = 'aosi';              // name of database table corresponding to instrument
        // data keyed by commentID
        $this->commentID = $commentID;
        
        //The array of dates/timestamps to convert to database dates/timestamps
        //Any HTML_Quickform date elements must be listed here
        $this->dateTimeFields=array("Date_taken");
            
        //The array of selects with multiple answers allowed
        //Any HTML_Quickform multiple selects must be listed here
        $this->_selectMultipleElements = array();

        // required fields for data entry completion status
        $this->_requiredElements = array('Examiner', 'examiner_location', "1_visual_tracking_press_1", "7_social_babbling");


	/**
	 * Array of column names to be ignored by the double data entry conflict detector.
	 */
	$this->_doubleDataEntryDiffIgnoreColumns = array('CommentID', 'UserID', 'Testdate',
						       '1_visual_tracking_notes',
						       '2_disengagement_of_attention_notes',
						       'free_play_period_1_notes',
						       '3_orients_to_name_notes',
						       '4_differential_response_to_facial_emotion_notes',
						       '5_anticipatory_response_notes',
						       '6_imitation_of_actions_activity_1',
						       '6_imitation_of_actions_activity_2',
						       '6_imitation_of_actions_activity_3',
						       '6_imitation_of_actions_notes',
						       'free_play_period_2_notes',
						       '7_social_babbling_notes',
						       '8_eye_contact_notes',
						       '9_reciprocal_social_smile_notes',
						       '10_coordination_of_eye_gaze_and_action_notes',
						       '11_reactivity_notes',
						       '14_social_interest_notes',
						       '15_transitions_notes',
						       '16_motor_control_and_behaviour_notes',
						       '17_atypical_motor_notes',
						       '18_atypical_sensory_notes',
						       '19_engagement_of_attention_notes',
						       '20_insistence_on_particular_objects_notes',
						       '21_social_referencing_notes',
							 '1_visual_tracking_notes',
							 '1_visual_tracking_notes_status',
							 '2_disengagement_of_attention_notes',
							 '2_disengagement_of_attention_notes_status',						       
							 'free_play_period_1_notes',
							 'free_play_period_1_notes_status',
							 '3_orients_to_name_notes',
							 '3_orients_to_name_notes_status',
							 '4_differential_response_to_facial_emotion_notes',
							 '4_differential_response_to_facial_emotion_notes_status',
							 '5_anticipatory_response_notes',
							 '5_anticipatory_response_notes_status',
							 '6_imitation_of_actions_activity_1',
							 '6_imitation_of_actions_activity_1_status',
							 '6_imitation_of_actions_activity_2',
							 '6_imitation_of_actions_activity_2_status',
							 '6_imitation_of_actions_activity_3',
							 '6_imitation_of_actions_activity_3_status',
							 '6_imitation_of_actions_notes',
							 '6_imitation_of_actions_notes_status',
							 'free_play_period_2_notes',
							 'free_play_period_2_notes_status',
							 '7_social_babbling_notes',
							 '7_social_babbling_notes_status',						       
							 '8_eye_contact_notes',
							 '8_eye_contact_notes_status',							
							 '9_reciprocal_social_smile_notes',
							 '9_reciprocal_social_smile_notes_status',
							 '10_coordination_of_eye_gaze_and_action_notes',
							 '10_coordination_of_eye_gaze_and_action_notes_status',
							 '11_reactivity_notes',
							 '11_reactivity_notes_status',
							 '14_social_interest_notes',
							 '14_social_interest_notes_status',
							 '15_transitions_notes',
							 '15_transitions_notes_status',
							 '16_motor_control_and_behaviour_notes',
							 '16_motor_control_and_behaviour_notes_status',
							 '17_atypical_motor_notes',
							 '17_atypical_motor_notes_status',
							 '18_atypical_sensory_notes',
							 '18_atypical_sensory_notes_status',
							 '19_engagement_of_attention_notes',
							 '19_engagement_of_attention_notes_status',
							 '20_insistence_on_particular_objects_notes',
							 '20_insistence_on_particular_objects_notes_status',
							 '21_social_referencing_notes',
							 '21_social_referencing_notes_status');

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
        switch($this->page) {
            case "aosi_page1":
            $this->_page1();
            break;
            
            case "aosi_page2":
            $this->_page2();
            break;
            
            default:
            $this->_main();
            break;
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
        $this->form->addElement('header', 'instrument_title', "AOSI");
        
        // automatically adds examiner & date of administration
        $this->_addMetadataFields();
        
        $this->form->addElement('select', "examiner_location", "(Circle One)", array(null=>'', 'examiner'=>'Examiner', "in_room_observer"=>"In-Room Observer", "behind_mirror"=>"Behind Mirror", "videotape"=>"Videotape", "not_answered"=>"Not Answered"));
        $this->form->addElement('static', "total_score_1_18", "Total Score (Calculated) (items 1-18)");
        $this->form->addElement('static', "total_score_1_18_override", "Total Score (Using Overrides) (items 1-18)");
        $this->form->addELement('static', "number_of_markers", "Number of Markers (Calculated) (non-zero items, 1-18)");
        $this->form->addELement('static', "number_of_markers_override", "Number of Markers (Using Overrides) (non-zero items, 1-18)");
    }
   
    function _page1(){
        $this->form->addElement("header", null, "Item Administration");
        
        $this->form->addElement("static", null, "Please replace all Not Applicable entries in presses for items 1, 2, 3, and 6.");
        $this->form->addElement("static", null, "They are invalid entries and will be removed.");
        $this->form->addElement("static", null, "Not Applicable <i>is</i> valid for the override score.");
        $this->form->addElement("static", null, "<br><br>");

        //Question 1
        $this->form->addElement("static", null, "1. Visual Tracking");
        for($press = 1; $press <=3; $press++) {
            $this->form->addElement('select', "1_visual_tracking_press_$press", "Press #$press", array(null=>"", 0=>"0 = Pass", 1=>"1 = Delayed/Interupted", 2=>"2 = Partial or No Tracking", "not_answered"=>"Not Answered"));
        }

        $this->form->addElement("select", "1_visual_tracking_score_override", "Override score (required):", array(null=>'', 0=>"0 = Smoothly tracks", 1=>"1 = Delayed or interrupted", 2=>"2 = Partial", 8=>"8 = Not applicable"));
        //$this->XINRegisterRule("1_visual_tracking_score_override", array("1_visual_tracking_score{@}=={@}purely_optional_question"));

        $this->form->addElement("static", "1_visual_tracking_score", "Score (Calculated):");
        
        $this->addTextAreaElement("1_visual_tracking_notes", "Notes:");
        
        //Question 2
        $this->form->addElement("static", null, "2. Disengagement of Attention");
        for($press = 1; $press <= 3; $press++) {
            $this->form->addElement('select', "2_disengagement_of_attention_press_$press", "Press #$press", array(null=>"", 0=>"0 = Pass (<1 sec)", 1=>"1 = Delayed (1-2 sec)", 2=>"2 = Stuck (>2 sec)", "not_answered"=>"Not Answered"));
        }
        
        $this->form->addElement("select", "2_disengagement_of_attention_score_override", "Override score (required):", array(null=>'', 0=>"0 = Immediately moves attention", 1=>"1 = Delayed movement of attention", 2=>"2 = Fails to move attention", 8=>"8 = Not applicable"));
        //$this->XINRegisterRule("2_disengagement_of_attention_score_override", array("2_disengagement_of_attention_score{@}=={@})purely_optional_question"));
        
        $this->form->addElement("static", "2_disengagement_of_attention_score", "Score (Calculated):");
        $this->addTextAreaElement("2_disengagement_of_attention_notes", "Notes:");
        
        $this->addTextAreaElement("free_play_period_1_notes", "Free Play Period 1 Notes:");
        
        //Question 3
        $this->form->addElement("static", null, "3. Orients to Name");
        for($press = 1; $press <= 3; $press++) {
            for($trial = 1; $trial <= 2; $trial++) {
                $parents = $press != 3 ? "" : " (parents)";
            $this->form->addElement('select', "3_orients_to_name_press_{$press}_trial_{$trial}", "Press #$press, Trial #$trial $parents", array(null=>"", "orients_with_eye_contact"=>"Orients with eye contact", "orients_without_eye_contact"=>"Orients without eye contact", "fail_to_orient"=>"Fail to orient", "not_answered"=>"Not Answered"));
            }
        }
        $this->form->addElement("select", "3_orients_to_name_score_override", "Override score (required):", array(null=>'', 0=>"0 = Orients", 1=>"1 = Inconsistent orienting", 2=>"2 = Does not orient", 8=>"8 = Not applicable"));
        //$this->XINRegisterRule("3_orients_to_name_score_override", array("3_orients_to_name_score{@}=={@})purely_optional_question"));
                
        $this->form->addElement("static", "3_orients_to_name_score", "Score (Calculated):");
        $this->addTextAreaElement("3_orients_to_name_notes", "Notes:");
        
        //Question 4
        $this->form->addElement("static", null, "4. Differential response to facial emotion");
        $this->form->addElement('select', "4_differential_response_to_facial_emotion", "Score: ", array(null=>"", 0=>"0 = Clear change", 1=>"1 = Questionable change", 2=>"2 = Does not show change", 8=>"8 = Not Applicable", "not_answered"=>"Not Answered"));
        $this->form->addElement("static", "4_differential_response_to_facial_emotion_score", "Score:");
        $this->addTextAreaElement("4_differential_response_to_facial_emotion_notes", "Notes:");
        
        //Question 5
        $this->form->addElement("static", null, "5. Anticipatory Response");
        $this->form->addElement("select", "5_anticipatory_response", "Score: ", array(null=>"", 0=>"0 = Clear anticipatory response", 1=>"1 = Subtle/Questionable response", 2=>"2 = Only during game or routine", 3=>"3 = Does not show response", 8=>"8 = Not Applicable", "not_answered"=>"Not Answered"));
        $this->form->addElement("static", "5_anticipatory_response_score", "Score:");
        $this->addTextAreaElement("5_anticipatory_response_notes", "Notes:");

        //Question 6
        $this->form->addElement("static", null, "6. Imitation of Actions");
        for($activity = 1; $activity <= 3; $activity++) {
            $group[] = $this->form->createElement("text", "6_imitation_of_actions_activity_{$activity}", null);
            for($attempt = 1; $attempt <= 3; $attempt++) {
                $group[] = $this->form->createElement('select', "6_imitation_of_actions_act_{$activity}_att_{$attempt}", "", array(null=>"", 0=>"0 = Clear imitation", 1=>"1 = Equivocal imitation", 2=>"2 = Does not imitate", "not_answered"=>"Not Answered"));
                $this->XINRegisterRule("6_imitation_of_actions_act_{$activity}_att_{$attempt}", array("6_imitation_of_actions_act_{$activity}_att_{$attempt}{@}=={@}"), "An outcome is required.", "6_imitation_of_actions_activity_{$activity}_group");
//		$this->XINRegisterRule("6_imitation_of_actions_act_{$activity}_att_{$attempt}", array("6_imitation_of_actions_act_{$activity}_att_{$attempt}{@}=={@}
            }
            $this->form->addGroup($group, "6_imitation_of_actions_activity_{$activity}_group", "Activity $activity", null, false);
            unset($group);
            $this->XINRegisterRule("6_imitation_of_actions_activity_{$activity}", array("6_imitation_of_actions_activity_{$activity}{@}=={@}"), "An activity name is required.", "6_imitation_of_actions_activity_{$activity}_group");
        }
        $this->form->addElement("select", "6_imitation_of_actions_score_override", "Override score (required):", array(null=>'', 0=>"0 = Clear imitation", 1=>"1 = Equivocal imitation", 2=>"2 = Does not imitate", 8=>"8 = Not applicable"));
        //$this->XINRegisterRule("6_imitation_of_actions_score_override", array("6_imitation_of_actions_score{@}=={@})purely_optional_question"));
                
        $this->form->addElement("static", "6_imitation_of_actions_score", "Score (calculated):");
        $this->addTextAreaElement("6_imitation_of_actions_notes", "Notes: ");

        $this->addTextAreaElement("free_play_period_2_notes", "Free Play Period 2 Notes:");

    }

    function _page2() {
        $this->form->addElement("header", null, "General Observations");
        
        //array of questions
        $questions = array("7_social_babbling"=>"7. Social babbling",
                            "8_eye_contact"=>"8. Eye contact",
                            "9_reciprocal_social_smile"=>"9.Reciprocal social smile",
                            "10_coordination_of_eye_gaze_and_action"=>"10. Coordination of eye gaze and action",
                            "11_reactivity"=>"11. Reactivity",
                            "14_social_interest"=>"14. Social interest and shared affect",
                            "15_transitions"=>"15. Transitions",
                            "16_motor_control_and_behaviour"=>"16. Motor control and behaviour",
                            "17_atypical_motor"=>"17. Atypical motor behaviours",
                            "18_atypical_sensory"=>"18. Atypical sensory behaviours",
                            "19_engagement_of_attention"=>"19. Engagement of attention",
                            "20_insistence_on_particular_objects"=>"20. Insistence on having or playing with particular objects",
                            "21_social_referencing"=>"21. Social Referencing");
        //answer arrays
        $zeroOneTwoThree = array(null=>"", 0=>"0", 1=>"1", 2=>"2", 3=>"3", 8=>"8 = Not Applicable", "not_answered"=>"Not Answered");
        $zeroTwo = array(null=>"", 0=>"0", 2=>"2", 8=>"8 = Not Applicable", "not_answered"=>"Not Answered");
        $zeroOneTwo = array(null=>"", 0=>"0", 1=>"1", 2=>"2", 8=>"8 = Not Applicable", "not_answered"=>"Not Answered");
        
        $_0123 = array("7_social_babbling",
                        "9_reciprocal_social_smile",
                        "10_coordination_of_eye_gaze_and_action",
                        "11_reactivity",
                        "14_social_interest"); 
        $_02 = array("8_eye_contact",
                        "17_atypical_motor",
                        "18_atypical_sensory");
        $_012 = array("15_transitions",
                        "16_motor_control_and_behaviour",
                        "19_engagement_of_attention",
                        "20_insistence_on_particular_objects",
                        "21_social_referencing");
        
        foreach($questions as $field=>$label) {
            if(in_array($field, $_0123)) {
                $answerArray = $zeroOneTwoThree;}
            elseif(in_array($field, $_02)) {
                $answerArray = $zeroTwo;}
            else $answerArray = $zeroOneTwo;
            $this->form->addElement("select", $field, $label, $answerArray);
            $this->addTextAreaElement("{$field}_notes", "Notes: ");
            
        }
    }

    
    function score() {
        
        //holds raw question values
        $score_record = array();
        
        //holds calculated
        $db =& Database::singleton();
        if(PEAR::isError($db)) {
            return PEAR::raiseError ("Could not connect to database: ".$db->getMessage());
        }

        // null scores
        $this->_nullScores();

        //Get raw questions point values
        $query = "SELECT * FROM ".$this->table." WHERE CommentID='".$this->getCommentID()."'";
        $db->selectRow($query, $score_record);
        if (PEAR::isError($score_record)) {
            return PEAR::raiseError("Could not get scores: ".$score_record->getMessage());
        }
        
        //Calculate first 6 item scores from their input grids
        
        //Question 1
        //calculate
            //2
            if($score_record["1_visual_tracking_press_1"] == 2 || $score_record["1_visual_tracking_press_2"] == 2) {
                $this->scores["1_visual_tracking_score"] = 2;}
            //1
            elseif($score_record["1_visual_tracking_press_1"] == 1 || $score_record["1_visual_tracking_press_2"] == 1) {
                $this->scores["1_visual_tracking_score"] = 1;}
            //0
            elseif($score_record["1_visual_tracking_press_1"] == '0' && $score_record["1_visual_tracking_press_2"] == '0') {
                $this->scores["1_visual_tracking_score"] = 0;}
            //Wacky answers
            else {
                $this->scores["1_visual_tracking_score"] = "Unable to score";
            }
//        }

        //Question 2
        //calculate
            //2
            if($score_record["2_disengagement_of_attention_press_1"] == 'not_answered' || $score_record["2_disengagement_of_attention_press_2"] == 'not_answered' || $score_record["2_disengagement_of_attention_press_3"] == 'not_answered') {
                $this->scores["2_disengagement_of_attention_score"] = "Unable to score";
            } elseif($score_record["2_disengagement_of_attention_press_1"] == 2 || $score_record["2_disengagement_of_attention_press_2"] == 2 || $score_record["2_disengagement_of_attention_press_3"] == 2) {
                $this->scores["2_disengagement_of_attention_score"] = 2;
            //1 = Two 1 scores recorded
            } elseif(($score_record["2_disengagement_of_attention_press_1"] == 1 && $score_record["2_disengagement_of_attention_press_2"] == 1) 
                    || ($score_record["2_disengagement_of_attention_press_1"] == 1 && $score_record["2_disengagement_of_attention_press_3"] == 1) 
                    || ($score_record["2_disengagement_of_attention_press_2"] == 1 && $score_record["2_disengagement_of_attention_press_3"] == 1)) {
                $this->scores["2_disengagement_of_attention_score"] = 1;
            //0 = Two 0 scores recorded
            } elseif(($score_record["2_disengagement_of_attention_press_1"] == '0' && $score_record["2_disengagement_of_attention_press_2"] == '0') 
                    || ($score_record["2_disengagement_of_attention_press_1"] == '0' && $score_record["2_disengagement_of_attention_press_3"] == '0') 
                    || ($score_record["2_disengagement_of_attention_press_2"] == '0' && $score_record["2_disengagement_of_attention_press_3"] == '0')) 
            {
                $this->scores["2_disengagement_of_attention_score"] = 0;
            }
            //Wacky answers
            else {
                $this->scores["2_disengagement_of_attention_score"] = "Unable to score";
            }
        
        //Question 3
        //calculate
            //2
            if($score_record[TrialName(1,1)] == "not_answered" ||
                $score_record[TrialName(2,1)] == "not_answered") {
                $this->scores["3_orients_to_name_score"] = "Unable to score";
            } elseif($score_record["3_orients_to_name_press_1_trial_1"] != "orients_with_eye_contact" && 
            $score_record["3_orients_to_name_press_1_trial_2"] != "orients_with_eye_contact" && 
            $score_record["3_orients_to_name_press_2_trial_1"] != "orients_with_eye_contact" && 
            $score_record["3_orients_to_name_press_2_trial_2"] != "orients_with_eye_contact") {
                $this->scores["3_orients_to_name_score"] = 2;
            }
            //0
            elseif(
            ($score_record["3_orients_to_name_press_1_trial_1"] == "orients_with_eye_contact" || $score_record["3_orients_to_name_press_1_trial_2"] == "orients_with_eye_contact") && 
            ($score_record["3_orients_to_name_press_2_trial_1"] == "orients_with_eye_contact" || $score_record["3_orients_to_name_press_2_trial_2"] == "orients_with_eye_contact") && 
            ($score_record["3_orients_to_name_press_1_trial_1"] == "orients_with_eye_contact" || $score_record["3_orients_to_name_press_2_trial_1"] == "orients_with_eye_contact")) {
                $this->scores["3_orients_to_name_score"] = 0;
            }
            //1
            elseif(
            $score_record["3_orients_to_name_press_1_trial_1"] == "orients_with_eye_contact" ||
            $score_record["3_orients_to_name_press_1_trial_2"] == "orients_with_eye_contact" || 
            $score_record["3_orients_to_name_press_2_trial_1"] == "orients_with_eye_contact" || 
            $score_record["3_orients_to_name_press_2_trial_2"] == "orients_with_eye_contact") {
                $this->scores["3_orients_to_name_score"] = 1;
            }
            //wacky
            else {
                $this->scores["3_orients_to_name_score"] = "Scoring error";
            }
//        }
        
        //Question 4
        $this->scores["4_differential_response_to_facial_emotion_score"] = $score_record["4_differential_response_to_facial_emotion"];

        //Question 5
        $this->scores["5_anticipatory_response_score"] = $score_record["5_anticipatory_response"];

        //Question 6
        //calculate
        $this->scores["6_imitation_of_actions_score"] = "Unable to score"; //start with worst score possible
        for($activity = 1; $activity <= 3; $activity++) {
            for($attempt = 1; $attempt <= 3; $attempt++) {
                //take the lowest/best score possible.
                $field = "6_imitation_of_actions_act_{$activity}_att_{$attempt}";

                //Ignore if not_answered
                if($score_record[$field] == "not_answered") {
                    continue;
                }
                // If it's lower, or haven't been set yet, take this one
                if(($score_record[$field] < $this->scores["6_imitation_of_actions_score"]) || ($this->scores["6_imitation_of_actions_score"] == "Unable to score")) {
                    $this->scores["6_imitation_of_actions_score"] = $score_record[$field];
                }
            }
        }
    
        //Summary scores
        //build array of all scorable fields
        $overrideables = array("1_visual_tracking_score",
                               "2_disengagement_of_attention_score",
                               "3_orients_to_name_score",
                               "6_imitation_of_actions_score"
        );

        $scorables = array(
            '1_visual_tracking_score'
                => $this->scores["1_visual_tracking_score"],
            '2_disengagement_of_attention_score'
                => $this->scores["2_disengagement_of_attention_score"],
            '3_orients_to_name_score'
                => $this->scores["3_orients_to_name_score"],
            '4_differential_response_to_facial_emotion_score' 
                => $this->scores["4_differential_response_to_facial_emotion_score"],
            '5_anticipatory_response_score' 
                => $this->scores["5_anticipatory_response_score"],
            '6_imitation_of_actions_score' 
                => $this->scores["6_imitation_of_actions_score"],
            '7_social_babbling'
                => $score_record["7_social_babbling"],
            '8_eye_contact'
                => $score_record["8_eye_contact"],
            '9_reciprocal_social_smile'
                => $score_record["9_reciprocal_social_smile"],
            '10_coordination_of_eye_gaze_and_action'
                => $score_record["10_coordination_of_eye_gaze_and_action"],
            '11_reactivity'      => $score_record["11_reactivity"],
            '14_social_interest' => $score_record["14_social_interest"],
            '15_transitions'     => $score_record["15_transitions"],
            '16_motor_control_and_behaviour'
                => $score_record["16_motor_control_and_behaviour"],
            '17_atypical_motor'  => $score_record["17_atypical_motor"],
            '18_atypical_sensory'=> $score_record["18_atypical_sensory"]
        );        

        $this->scores["number_of_markers"] = 0;  //initialize
        $this->scores["number_of_markers_override"] = 0;  //initialize
        foreach($scorables as $key =>$value) {
            //change 8's to 0's for scoring purposes

            if($value == 8) $value = 0;
            //Calculate final score values
            if(in_array($key, $overrideables)) {
                $ov = $score_record[$key . "_override"];
                if($ov == 8) {
                    $ov = 0;
                }
            } else {
                $ov = $value;
            }
            $this->scores['total_score_1_18_override'] += $ov;
            $this->scores["total_score_1_18"] += $value;
            //increment markers count if non-zero
            if($ov != 0) $this->scores["number_of_markers_override"]++;
            if($value != 0) $this->scores["number_of_markers"]++;
        }
        
        // update if any scores
        if (is_array($this->scores) && count($this->scores)>0) {
            $result = $db->update($this->table, $this->scores, array('CommentID'=>$this->getCommentID()));
            if($db->isError($result)) {
                return PEAR::raiseError("Could not save total score: ".$result->getMessage());
            }
        }
        
    }
    
    /**
    * nulls all scores for the record identified by CommentID
    * @param array list of scoring fields to null
    * @see $this->getCommentID()
    * @return mixed
    * @throws PEAR::error
    */
    function _nullScores()
    {
        $db=& Database::singleton();
        if (PEAR::isError($db)) {
            return PEAR::raiseError("Could not connect to database: ".$db->getMessage()."\n");
        }
        
        // set the scores to NULL
        foreach ($this->scores as $key => $val) {
            $scores[$key]=null;
        }

        // update the scores
        $success = $db->update($this->table,$scores,array('CommentID'=>$this->getCommentID()));
        if (PEAR::isError($success)) {
            return PEAR::raiseError("DB Error, fail null the scores:\n".$success->getMessage()."\n");
        }
        return;
    }    
    
}
?>
