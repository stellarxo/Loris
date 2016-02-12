<?php

require_once 'HTML/QuickForm.php';
require_once 'HTML/QuickForm/Renderer/Array.php';

class NDB_BVL_Instrument_scq extends NDB_BVL_Instrument
{

	var $yesNo = array(null=>"", "yes"=>"Yes", "no"=>"No", "not_answered"=>"Not Answered");
    var $onlyYesNo = array(null=>"","yes"=>"Yes","no"=>"No");
	var $scoreCols = array("score", "scq_diagnosis");
	
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
		$this->dateTimeFields=array("Date_taken");

		//The array of selects with multiple answers allowed
		//Any HTML_Quickform multiple selects must be listed here
		$this->_selectMultipleElements = array();

		// required fields for data entry completion status
		$this->_requiredElements = array('Examiner', "q1_talk_short_phrases");
        
        $this->_doubleDataEntryDiffIgnoreColumns = array('CommentID', 'UserID', 'Testdate', 'Window_Difference', 'Candidate_Age','Data_entry_completion_status','score','scq_diagnosis');
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
		if(preg_match("/(_page[0-9]+)/",$this->page,$matches)){
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
		$this->form->addElement('header', 'instrument_title', "Social Communication Questionnaire - Lifetime");
		$this->form->addElement('static', null, "Lifetime and Current versions of this questionnaire are effectively identical.");
		$this->form->addElement('static', null, "Please fill in one as though it were the other.");
		

		// automatically adds examiner & date of administration
		$this->_addMetadataFields();
		$this->form->addElement("static", "score", "Score: ");
		$this->form->addElement("static", "scq_diagnosis", "SCQ Diagnosis: ");

        $this->form->addElement("select", "scq_version", "Version of SCQ Questionaire used:", 
            array("" => "", "current" => "Current", "lifetime" => "Lifetime")
        );
		$this->form->addElement("header", null, "Capable of phrase speech");
		$this->form->addElement("select", "q1_talk_short_phrases", "1. Is she/he now able to talk using short phrases...", $this->onlyYesNo);

		//Phrase speech
		$this->form->addElement("header", null, "Phrase speech");
		$this->form->addElement("select", "q2_to_and_fro", "2. Can you have a to and fro conversation...", $this->yesNo);
		$this->form->addElement("static", null, "Has she/he ever...");
		$questionArray = array("q3_odd_phrases"=>"3. ...used odd phrases or said the same thing over and over...",
		"q4_socially_inappropriate"=>"4. ...used socially inappropriate questions...",
		"q5_pronouns_mixed"=>"5. ...got her/his pronouns mixed up...",
		"q6_words_invented"=>"6. ...used words that she/he seemed to have invented...",
		"q7_said_same_thing"=>"7. ...said the same thing over and over...");
		foreach($questionArray as $field=>$label) {
			$this->form->addElement("select", $field, $this->indent . $label, $this->yesNo);
			$this->XINRegisterRule($field, array("q1_talk_short_phrases{@}=={@}yes"), "This field is required if she/he is capable of phrase speech");
		}

		//Non-phrase speech questions
		$this->form->addElement("header", null, "Non-phrase speech questions");
		$this->form->addElement("static", null, "Has she/he ever...");
		$questionArray = array("q8_particular_way"=>"8. ...had things that she/he seemed to have to do in a very particular way...",
		"q9_facial_expressions"=>"9. Has his/her facial expressions usually seemed...",
		"q10_hand_like_tool"=>"10. ...used your hand like a tool...",
		"q11_interests_that_preoccupy"=>"11. ...had any interests that preoccupy...",
		"q12_interested_in_parts"=>"12. ...seemed to be more interested in parts...",
		"q13_intense_interests"=>"13. ...had any special interests that were unusual in their intensity...",
		"q14_sight_feel_sound"=>"14. ...seemed to be unusually interested in the sight...",
		"q15_mannerisms"=>"15. ...had any mannerisms or odd ways of moving...",
		"q16_complicated_movements"=>"16. ...had any complicated movements...",
		"q17_deliberate_injury"=>"17. ...injured her/himself deliberately...",
		"q18_carry_objects"=>"18. ...had any objects that she/he had to carry around...",
		"q19_particular_friends"=>"19. Does she/he have any particular friends or a best friend...");
		foreach ($questionArray as $field=>$label) {
			$this->form->addElement("select", $field, $this->indent . $label, $this->yesNo);
		}

		//Questions 20-40
		$this->form->addElement("header", null, "Between ages 4 and 5");
		$this->form->addElement("static", null, "When she/he was 4 to 5 did she/he...");
		$questionArray = array("q20_talk_friendly"=>"20. ...ever talk with you just to be friendly...",
		"q21_spontaneously_copy"=>"21. ...ever spontaneously copy you...",
		"q22_spontaneously_point"=>"22. ...ever spontaneously point at things around...",
		"q23_gestures"=>"23. ...ever use gestures other than pointing or pulling...",
		"q24_nod_yes"=>"24. ...nod her/his head to mean yes?",
		"q25_shake_no"=>"25. ...shake her/his head to mean no?",
		"q26_look_directly"=>"26. ...usually look at you directly in the face...",
		"q27_smile_back"=>"27. ...smile back if someone smiled...",
		"q28_show_things"=>"28. ...ever show you things that interested her/him...",
		"q29_offer_share"=>"29. ...offer to share things other than food...",
		"q30_join_enjoyment"=>"30. ...ever seem to want you to join in her/his enjoyment...",
		"q31_comfort"=>"31. ...ever try to comfort you if you were sad...",
		"q32_wanted_something"=>"32. when she/he wanted something or wanted help...",
		"q33_facial_expressions"=>"33. ...show a normal range of facial expressions?",
		"q34_spontaneously_join"=>"34. ...ever spontaneously join in and try to copy...",
		"q35_play_pretend"=>"35. ...play pretend or make-believe games?",
		"q36_seem_interested"=>"36. ...seem interested in other children...",
		"q37_respond_positively"=>"37. ...respond positively when another child...",
		"q38_came_into_room"=>"38. ...if you came into a room and started talking...",
		"q39_play_imaginative"=>"39. ...ever play imaginative games with another...",
		"q40_play_cooperatively"=>"40. ...play cooperatively in games that required...");
		foreach($questionArray as $field=>$label) {
			$this->form->addElement("select", $field, $this->indent . $label, $this->yesNo);
		}
        $this->_addAdditionalComments(); 

	}

	function score() {
		//skip scoring if all data has not yet been entered.
		if($this->_determineDataEntryCompletionStatus() == "Incomplete") {
			return;
		}

		$db =& Database::singleton();

		// null scores
		$this->_nullScores($this->scoreCols);

		// Get the item scores
		$query = "SELECT * FROM $this->table WHERE CommentID='".$this->getCommentID()."'";
		$record=array();
		$db->selectRow($query, $record);

		//take only question fields, not metadata
		foreach ($record as $field=>$value) {
            // This was written this way before -- added substr to strip off the "q"
			if (intval(substr($field, 1)) == 0) {
				continue;  //not a question field
			} else {
				$scores[intval(substr($field, 1))] = $value;
			}
		}

		//check if phrase speech questions (#2-#7) need to be scored
		if($scores[1] == "no") {
			for ($i = 2; $i <= 7; $i++){
				unset($scores[$i]);
			}
		}
		
		//remove question 1, which is never scored...
		unset($scores[1]);

		//Questions where `yes` scores 1, otherwise `no` scores 1
		$yesIs1 = array_diff(range(2, 19), array(2, 9, 19));
		
		$calculatedScores = array("score"=>0);
		//Sum point value of all questions
		foreach ($scores as $question=>$answer) {
			//Currently, "not_answered" questions count as 0 towards the score
			if ((in_array($question, $yesIs1) && $answer == "yes")
				|| (!in_array($question, $yesIs1) && $answer == "no")) {
				$calculatedScores["score"]++;
			}
		}

		//enforce ASD diagnosis cutoff
		$calculatedScores["scq_diagnosis"] = $calculatedScores["score"] >= 11 ? "ASD Positive" : "ASD Negative";

		//save the resultant total
		$result = $db->update($this->table, $calculatedScores, array('CommentID'=>$this->getCommentID()));
	}
    function _addAdditionalComments() {
    }
}
?>
