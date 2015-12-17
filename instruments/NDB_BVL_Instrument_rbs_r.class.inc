<?php

require_once 'HTML/QuickForm.php';
require_once 'HTML/QuickForm/Renderer/Array.php';

class NDB_BVL_Instrument_rbs_r extends NDB_BVL_Instrument
{
    var $ValidityEnabled = false;
    var $ValidityRequired = false;

/*
INSERT INTO test_names VALUES ('', 'rbs_r', 'Repetitive Behaviour Scale - Revised', '0', '1');
INSERT INTO instrument_subtests VALUES('', 'rbs_r', 'rbs_r_page1', 'Subscales', 1);
-- INSERT INTO test_battery VALUES ('', 'rbs_r', '1050', '1140', 'Y', 'Visit', '3');
*/

    /* These are used without the _score and _endorsed prefix by the instrument.
       Unfortunately, that confuses the nullScores function and GetScoreLabels
       used by Scatterplots. */
	var $scoreCols = array('I_stereotyped'=>"I. Stereotyped Behavior",
	'II_self_injurious'=>"II. Self-injurious Behavior",
	'III_compulsive'=>"III. Compulsive Behavior",
	'IV_ritualistic'=>"IV. Ritualistic Behavior",
	'V_sameness'=>"V. Sameness Behavior",
	'VI_restricted'=>"VI. Restricted Behavior");
    /* getScoreColsForInstrument happens to check for "scoreLabels" before
       "scoreCols". So we just set scoreLabels explicitly to the field for 
       the scatterplots to work and leave the above so the instrument doesn't 
       need to be changed.
     */
    var $scoreLabels = array('I_stereotyped_score', 'I_stereotyped_endorsed',
        'II_self_injurious_score', 'II_self_injurious_endorsed',
        'III_compulsive_score', 'III_compulsive_endorsed',
        'IV_ritualistic_score', 'IV_ritualistic_endorsed',
        'V_sameness_score', 'V_sameness_endorsed',
        'VI_restricted_score', 'VI_restricted_endorsed'
    );

	var $questionArray = array(//I. Stereotyped Behavior Subscale
	'q1_whole_body'=>'1. WHOLE BODY',
	'q2_head'=>'2. HEAD',
	'q3_hand_finger'=>'3. HAND/FINGER',
	'q4_locomotion'=>'4. LOCOMOTION',
	'q5_object_usage'=>'5. OBJECT USAGE',
	'q6_sensory'=>'6. SENSORY',
	//II. Self-Injurious Behavior Subscale
	'q7_hits_self_body_part'=>'7. HITS SELF WITH BODY PART',
	'q8_hits_self_against_surface'=>'8. HITS SELF AGAINST SURFACE OR OBJECT',
	'q9_hits_self_with_object'=>'9. HITS SELF WITH OBJECT',
	'q10_bites_self'=>'10. BITES SELF',
	'q11_pulls'=>'11. PULLS',
	'q12_rubs_or_scratches'=>'12. RUBS OR SCRATCHES SELF',
	'q13_inserts_finger_or_object'=>'13. INSERTS FINGER OR OBJECT',
	'q14_skin_picking'=>'14. SKIN PICKING',
	//III. Compulsive Behavior Subscale
	'q15_arranging_ordering'=>'15. ARRANGING / ORDERING',
	'q16_completeness'=>'16. COMPLETENESS',
	'q17_washing_cleaning'=>'17. WASHING / CLEANING',
	'q18_checking'=>'18. CHECKING',
	'q19_counting'=>'19. COUNTING',
	'q20_hoarding_saving'=>'20. HOARDING/SAVING',
	'q21_repeating'=>'21. REPEATING',
	'q22_touch_tap'=>'22. TOUCH / TAP',
	//IV. Ritualistic Behavior Subscale
	'q23_eating_mealtime'=>'23. EATING / MEALTIME',
	'q24_sleeping_bedtime'=>'24. SLEEPING / BEDTIME',
	'q25_self_care'=>'25. SELF-CARE - BATHROOM AND DRESSING',
	'q26_travel_transportation'=>'26. TRAVEL / TRANSPORTATION',
	'q27_play_leisure'=>'27. PLAY / LEISURE',
	'q28_communication'=>'28. COMMUNICATION / SOCIAL INTERACTIONS',
	//V. Sameness Behavior Subscale
	'q29_insists_things_remain'=>'29. Insists that things remain in the same place(s)',
	'q30_objects_to_visiting'=>'30. Objects to visiting new places',
	'q31_upset_if_interrupted'=>'31. Becomes upset if interrupted in what he/she is doing',
	'q32_walking_in_a_pattern'=>'32. Insists on walking in a particular pattern',
	'q33_insists_on_sitting_at_same_place'=>'33. Insists on sitting at the same place',
	'q34_dislikes_change'=>'34. Dislikes changes in appearance or behavior of the people around him/her',
	'q35_insists_on_particular_door'=>'35. Insists on using a particular door',
	'q36_likes_same_cd'=>'36. Likes the same CD, tape, record or piece of music played continually',
	'q37_resists_changing_activities'=>'37. Resists changing activities; Difficulty with transitions',
	'q38_insists_on_same_routine'=>'38. Insists on same routine, household, school or work schedule everyday',
	'q39_insists_that_specific'=>'39. Insists that specific things take place at specific times',
	//VI. Restricted Behavior Subscale
	'q40_fascination_preoccupation'=>'40. Fascination, preoccupation with one subject or activity',
	'q41_strongly_attached'=>'41. Strongly attached to one specific object',
	'q42_preoccupation_with_parts'=>'42. Preoccupation with part(s) of object rather than the whole object',
	'q43_fascination_with_movement'=>'43. Fascination, preoccupation with movement / things that move');

	//holder for the score calculations
    var $calculatedScores = array();

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
		$this->testName = "rbs_r";           // test_names.Test_name
		$this->table = 'rbs_r';              // name of database table corresponding to instrument
		// data keyed by commentID
		$this->commentID = $commentID;

		//The array of dates/timestamps to convert to database dates/timestamps
		//Any HTML_Quickform date elements must be listed here
		$this->dateTimeFields=array("Date_taken");

		//The array of selects with multiple answers allowed
		//Any HTML_Quickform multiple selects must be listed here
		$this->_selectMultipleElements = array();

		// required fields for data entry completion status
		$this->_requiredElements = array('Examiner', 'q1_whole_body');

		// setup the form
		$this->_setupForm();

		$this->localDefaults = array_merge($this->localDefaults, array('endorsed'=>"Number endorsed", 'total_score'=>"Subscale score"));

        $this->_doubleDataEntryDiffIgnoreColumns = array('CommentID', 'UserID', 'Testdate', 'Window_Difference',
                'Candidate_Age',
                'Data_entry_completion_status',
                'I_stereotyped_score', 'I_stereotyped_endorsed',
                'II_self_injurious_score', 'II_self_injurious_endorsed',
                'III_compulsive_score', 'III_compulsive_endorsed',
                'IV_ritualistic_score', 'IV_ritualistic_endorsed',
                'V_sameness_score', 'V_sameness_endorsed',
                'VI_restricted_score', 'VI_restricted_endorsed',
                'respondent_specify',
                'overall_endorsed',
                'overall_score');


	}

	//If the instrument is not paged, remove the switch from the _setupForm method and add all the form Elements in this function.

	/**
    * method to build the HTML_Quickform object into a paged form
    *
    * @return void
    * @access private
    */
	function _setupForm(){
		if(preg_match("/rbs_r(_page[0-9]+)/",$this->page,$matches)){
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
		$this->form->addElement('header', 'instrument_title', "Repetitive Behaviour Scale - Revised (RBS-R)");

		// automatically adds examiner & date of administration
		$this->_addMetadataFields();
        $this->form->addElement('select', 'respondent', 'Respondent',array('' => '', 'mother' => 'Mother', 'father' => 'Father', 'other' => 'Other'));
        $this->form->addElement('text', 'respondent_specify', 'If other, specify:');
        
        $this->XINRegisterRule('respondent_specify', array('respondent{@}=={@}other'), 'Required if other');

		//Overall scores...
		$this->form->addElement('header', null, "Total scores");
		$this->form->addElement('static', 'overall_endorsed', "Overall number of items endorsed");
		$this->form->addElement('static', 'overall_score', "Overall score");

		//Subscale scores...
		$this->form->addElement('header', null, "Subscale scores");
		//scoring columns
		$group[] = $this->form->createElement('static', 'endorsed');
		$group[] = $this->form->createElement('static', 'total_score');
		$this->form->addGroup($group, 'score_headers_group', "Subscale", $this->_GUIDelimiter, false);
		unset($group);

		foreach($this->scoreCols as $field=>$label) {
			$group[] = $this->form->createElement('static', $field . '_endorsed');
			$group[] = $this->form->createElement('static', $field . '_score');
			$this->form->addGroup($group, $field . '_group', $label, $this->_GUIDelimiter, false);
			unset($group);
		}
	}

	function _page1(){

		//The only answer choices available in the entire form.
		$answerOptions = array(null=>'',
		'0_does_not_occur'=>"0 = behavior does not occur",
		'1_mild_problems'=>"1 = behavior occurs and is a mild problem",
		'2_moderate_problem'=>"2 = behavior occurs and is a moderate problem",
		'3_severe_problem'=>"3 = behavior occurs and is a severe problem",
		'not_answered'=>"Not Answered");

		//The first question of each section...
		$sectionStarts = array('q1_whole_body'=>"I. Stereotyped Behavior Subscale",
		'q7_hits_self_body_part'=>"II. Self-Injurious Behavior Subscale",
		'q15_arranging_ordering'=>"III. Compulsive Behavior Subscale",
		'q23_eating_mealtime'=>"IV. Ritualistic Behavior Subscale",
		'q29_insists_things_remain'=>"V. Sameness Behavior Subscale",
		'q40_fascination_preoccupation'=>"VI. Restricted Behavior Subscale");

		//The questions themselves
		foreach($this->questionArray as $field=>$label) {
			if(array_key_exists($field, $sectionStarts)) {
				$this->form->addElement('header', null, $sectionStarts[$field]);
			}

			$this->form->addElement('select', $field, $label, $answerOptions);
		}

	}

	function score() {
		//skip scoring if all data has not yet been entered.
		if($this->_determineDataEntryCompletionStatus() == "Incomplete") {
			return;
		}

		$db =& Database::singleton();


		// null scores ...not currently doing anything...  Don't have an array of scores to nullify.
//		$this->_nullScores($this->scoreCols);
		//Initially reset all values to 0
		$this->calculatedScores['overall_endorsed'] = 0;
		$this->calculatedScores['overall_score'] = 0;
		foreach($this->scoreCols as $field=>$label) {
    		$this->calculatedScores[$field . "_endorsed"] = 0;
    		$this->calculatedScores[$field . "_score"] = 0;
		}
		
		// Get the item scores
		$query = "SELECT * FROM $this->table WHERE CommentID='".$this->getCommentID()."'";
		$record=array();
		$db->selectRow($query, $record);

		//convert answers to numerical scores
		foreach ($record as $field=>$value) {
			$scores[$field] = intval(substr($value, 0, 1));
		}

		foreach($scores as $key=>$value) {

			//convert textual question labels to just numbers 
            if($key[0] == 'q') {
                $questionNum = intval(substr($key, 1));
            }
			//print "key: $key Q num: " . $questionNum;
			//only work with the numbered subscale questions...
			if($questionNum == 0) continue;
			//Only count the non-zero answers in both the number endorsed and the subscale scores
			if($value == 0) continue;
			//Overall score and number endorsed...
			$this->calculatedScores['overall_endorsed']++;
			$this->calculatedScores['overall_score'] += $value;

			//subscale number endorsed and score totals
			if ($questionNum >= 1 && $questionNum <= 6) {
				$this->calculatedScores['I_stereotyped_endorsed']++;
				$this->calculatedScores['I_stereotyped_score'] += $value;
			} elseif ($questionNum >= 7 && $questionNum <= 14) {
				$this->calculatedScores['II_self_injurious_endorsed']++;
				$this->calculatedScores['II_self_injurious_score'] += $value;
			} elseif ($questionNum >= 15 && $questionNum <= 22) {
				$this->calculatedScores['III_compulsive_endorsed']++;
				$this->calculatedScores['III_compulsive_score'] += $value;
			} elseif ($questionNum >= 23 && $questionNum <= 28) {
				$this->calculatedScores['IV_ritualistic_endorsed']++;
				$this->calculatedScores['IV_ritualistic_score'] += $value;
			} elseif ($questionNum >= 29 && $questionNum <= 39) {
				$this->calculatedScores['V_sameness_endorsed']++;
				$this->calculatedScores['V_sameness_score'] += $value;
			} elseif ($questionNum >= 40 && $questionNum <= 43) {
				$this->calculatedScores['VI_restricted_endorsed']++;
				$this->calculatedScores['VI_restricted_score'] += $value;
			}
		}
		
		// save the resultant total
		$result = $db->update($this->table, $this->calculatedScores, array('CommentID'=>$this->getCommentID()));

	}

}
?>
