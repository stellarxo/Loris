<?php
class NDB_BVL_Instrument_m_chat extends NDB_BVL_Instrument
{
	/*
	INSERT INTO test_names VALUES ('', 'm_chat', 'M-CHAT', '0', '1');

	INSERT INTO instrument_subtests VALUES('', 'm_chat', 'm_chat_page1', 'Questions', 1);

	INSERT INTO test_battery VALUES ('', 'm_chat', '1050', '1140', 'Y', 'Visit', '3');
	CHANGE FOR ZAPHOD!!!
	*/

	var $scoreCols = array("score", "critical_fails", "item_fails");

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
		$this->testName = "m_chat";           // test_names.Test_name
		$this->table = 'm_chat';              // name of database table corresponding to instrument
		// data keyed by commentID
		$this->commentID = $commentID;

		//The array of dates/timestamps to convert to database dates/timestamps
		//Any HTML_Quickform date elements must be listed here
		$this->dateTimeFields=array("Date_taken");

		//The array of selects with multiple answers allowed
		//Any HTML_Quickform multiple selects must be listed here
		$this->_selectMultipleElements = array();

		// required fields for data entry completion status
		$this->_requiredElements = array('Examiner', "1_swung_on_knee");

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
		if(ereg("m_chat(_page[0-9]+)",$this->page,$matches)){
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
		$this->form->addElement('header', 'instrument_title', "M-CHAT");

		// automatically adds examiner & date of administration
		$this->_addMetadataFields();

		$this->form->addElement('static', "item_fails", "Item Fails: ");
		$this->form->addElement('static', "critical_fails", "Critical Fails: ");
		$this->form->addElement('static', "score", "Score: ");

		$this->form->addElement('header', null, "Does your child...");

		//        $this->form->addElement();
		$questionArray = array("1_swung_on_knee"=>"1. Does your child enjoy being swung, bounced on your knee, etc.?",
		"2_interest_other_children"=>"2. Does your child take an interest in other children?",
		"3_climbing"=>"3. Does your child like climbing on things, such as up stairs?",
		"4_peek_a_boo"=>"4. Does your child enjoy playing peek-a-boo/hide-and-seek?",
		"5_pretends"=>"5. Does your child ever pretend, for example, to talk on the phone or take care of a doll or pretend other things?",
		"6_index_point"=>"6. Does your child ever use his/her index finger to point, to ask for something?",
		"7_index_interest"=>"7. Does your child ever use his/her index finger to point, to indicate interest in something?",
		"8_play_properly"=>"8. Can your child play properly with small toys (e.g. cars or bricks) without just mouthing, fiddling, or dropping them?",
		"9_bring_objects"=>"9. Does your child ever bring objects over to you (parent) to show you something?",
		"10_look_eye"=>"10. Does your child look you in the eye for more than a second or two?",
		"11_oversensitive"=>"11. Does your child ever seem oversensitive to noise? (e.g., plugging ears)",
		"12_smile_to_face"=>"12. Does your child smile in response to your face or your smile?",
		"13_imitate_you"=>"13. Does your child imitate you? (e.g., you make a face-will your child imitate it?)",
		"14_respond_to_name"=>"14. Does your child respond to his/her name when you call?",
		"15_point_and_look"=>"15. If you point at a toy across the room, does your child look at it?",
		"16_walk"=>"16. Does your child walk?",
		"17_look_at_similar"=>"17. Does your child look at things you are looking at?",
		"18_unusual_finger"=>"18. Does your child make unusual finger movements near his/her face?",
		"19_try_to_attract"=>"19. Does your child try to attract your attention to his/her own activity?",
		"20_wondered_deaf"=>"20. Have you ever wondered if your child is deaf?",
		"21_understand_speach"=>"21. Does your child understand what people say?",
		"22_stare_no_purpose"=>"22. Does your child sometimes stare at nothing or wander with no purpose?",
		"23_look_at_face"=>"23. Does your child look at your face to check your reaction when faced with something unfamiliar?");
		foreach ($questionArray as $field=>$label) {
			$this->form->addElement("select", $field, $label, array(null=>"", "yes"=>"Yes", "no"=>"No", "not_answered"=>"Not Answered"));
		}
	}

	function score() {
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

		//take only question fields, not metadata
		foreach ($record as $field=>$value) {
			if (intval($field) == 0) {
				continue;  //not a question field
			} else {
				$scores[$field] = $value;
			}
		}

		//Questions deemed as critical
		$critical = array("2_interest_other_children",
		"7_index_interest",
		"9_bring_objects",
		"13_imitate_you",
		"14_respond_to_name",
		"15_point_and_look");

		//Questions that take a "no" response to pass
		$noQuestions = array("11_oversensitive",
		"18_unusual_finger",
		"20_wondered_deaf",
		"22_stare_no_purpose");

		//Check correctness of all questions
		//"not_answered" questions are, for now, considered as passes.
		foreach ($scores as $question=>$answer) {
			$correctAnswer = in_array($question, $noQuestions) ? "no" : "yes";
			if ($answer == $correctAnswer) {
				continue;
			}
			else {
				if (in_array($question, $critical)) {
					//count critical failures
					$calculatedScores["critical_fails"]++;
				} else {
					//count item failures
					$calculatedScores["item_fails"]++;
				}
			}
		}

		//enforce failure cutoffs
		$calculatedScores["score"] = ($calculatedScores["critical_fails"] >= 2 || $calculatedScores["item_fails"] >=3) ? "Fail" : "Pass";

		// save the resultant total
		$result = $db->update($this->table, $calculatedScores, array('CommentID'=>$this->getCommentID()));
		if($db->isError($result)) {
			return PEAR::raiseError("Could not save total score: ".$result->getMessage());
		}
	}

}
?>