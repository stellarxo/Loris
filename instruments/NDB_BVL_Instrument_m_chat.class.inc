<?php
class NDB_BVL_Instrument_m_chat extends NDB_BVL_Instrument
{
    var $ValidityEnabled = false;
    var $ValidityRequired = false;

	/*
	INSERT INTO test_names VALUES ('', 'm_chat', 'M-CHAT', '0', '1');

	INSERT INTO instrument_subtests VALUES('', 'm_chat', 'm_chat_page1', 'Questions', 1);

	INSERT INTO test_battery VALUES ('', 'm_chat', '1050', '1140', 'Y', 'Visit', '3');
	CHANGE FOR ZAPHOD!!!
	*/

	var $scoreCols = array("score", "total_critical_fails", "total_item_fails");

	//If the instrument is not paged, remove the switch from the _setupForm method and add all the form Elements in this function.

	/**
    * method to build the HTML_Quickform object into a paged form
    *
    * @return void
    * @access private
    */
	function _setupForm(){
		if(preg_match("/m_chat(_page[0-9]+)/",$this->page,$matches)){
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
		$this->form->addElement('header', 'instrument_title', "M-CHAT");

		// automatically adds examiner & date of administration
		$this->_addMetadataFields();

		$this->form->addElement('static', "total_item_fails", "Total Number of Fails: ");
		$this->form->addElement('static', "total_critical_fails", "Critical Fails: ");
		$this->form->addElement('static', "score", "Score: ");

		$this->form->addElement('header', null, "Does your child...");

		//        $this->form->addElement();
		$questionArray = array("q1_swung_on_knee"=>"1. Does your child enjoy being swung, bounced on your knee, etc.?",
		"q2_interest_other_children"=>"2. Does your child take an interest in other children?",
		"q3_climbing"=>"3. Does your child like climbing on things, such as up stairs?",
		"q4_peek_a_boo"=>"4. Does your child enjoy playing peek-a-boo/hide-and-seek?",
		"q5_pretends"=>"5. Does your child ever pretend, for example, to talk on the phone or take care of a doll or pretend other things?",
		"q6_index_point"=>"6. Does your child ever use his/her index finger to point, to ask for something?",
		"q7_index_interest"=>"7. Does your child ever use his/her index finger to point, to indicate interest in something?",
		"q8_play_properly"=>"8. Can your child play properly with small toys (e.g. cars or bricks) without just mouthing, fiddling, or dropping them?",
		"q9_bring_objects"=>"9. Does your child ever bring objects over to you (parent) to show you something?",
		"q10_look_eye"=>"10. Does your child look you in the eye for more than a second or two?",
		"q11_oversensitive"=>"11. Does your child ever seem oversensitive to noise? (e.g., plugging ears)",
		"q12_smile_to_face"=>"12. Does your child smile in response to your face or your smile?",
		"q13_imitate_you"=>"13. Does your child imitate you? (e.g., you make a face-will your child imitate it?)",
		"q14_respond_to_name"=>"14. Does your child respond to his/her name when you call?",
		"q15_point_and_look"=>"15. If you point at a toy across the room, does your child look at it?",
		"q16_walk"=>"16. Does your child walk?",
		"q17_look_at_similar"=>"17. Does your child look at things you are looking at?",
		"q18_unusual_finger"=>"18. Does your child make unusual finger movements near his/her face?",
		"q19_try_to_attract"=>"19. Does your child try to attract your attention to his/her own activity?",
		"q20_wondered_deaf"=>"20. Have you ever wondered if your child is deaf?",
		"q21_understand_speach"=>"21. Does your child understand what people say?",
		"q22_stare_no_purpose"=>"22. Does your child sometimes stare at nothing or wander with no purpose?",
		"q23_look_at_face"=>"23. Does your child look at your face to check your reaction when faced with something unfamiliar?");
		foreach ($questionArray as $field=>$label) {
			$this->form->addElement("select", $field, $label, array(null=>"", "yes"=>"Yes", "no"=>"No", "not_answered"=>"Not Answered"));
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
        $scores = array();
		foreach ($record as $field=>$value) {
			//if (intval(substr($field, 1)) == 0) {
            // This is a better way of checking, now that the fields are named properly..
            if($field[0] !== 'q') {
				continue;  //not a question field
			} else {
				$scores[$field] = $value;
			}
		}

		//Questions deemed as critical
		$critical = array("q2_interest_other_children",
		"q7_index_interest",
		"q9_bring_objects",
		"q13_imitate_you",
		"q14_respond_to_name",
		"q15_point_and_look");

		//Questions that take a "no" response to pass
		$noQuestions = array("q11_oversensitive",
		"q18_unusual_finger",
		"q20_wondered_deaf",
		"q22_stare_no_purpose");

		//Check correctness of all questions
		//"not_answered" questions are, for now, considered as passes.
        $notAnswered = array('total_unanswered' => 0, 'critical_unanswered' => 0);
		$calculatedScores["total_item_fails"] = 0 ;
        $calculatedScores["total_critical_fails"] = 0;
        foreach ($scores as $question=>$answer) {
			$correctAnswer = in_array($question, $noQuestions) ? "no" : "yes";
            if($answer == 'not_answered') {
                $notAnswered['total_unanswered']++;
                if(in_array($question, $critical)) {
                    $notAnswered['critical_unanswered']++;
                }
            }

			if ($answer == $correctAnswer) {
				continue;
			}
			else {
				//count total item failures
				$calculatedScores["total_item_fails"]++;
				if (in_array($question, $critical)) {
					//count critical failures
					$calculatedScores["total_critical_fails"]++;
				}
			}
		}

		//enforce failure cutoffs
		$calculatedScores["score"] = ($calculatedScores["total_critical_fails"] >= 2 || $calculatedScores["total_item_fails"] >=3) ? "Fail" : "Pass";
        // Need confirmation on if this should be done or not. According to Redmine ticket #1512 "we might" need to change the scoring to not be valid if 
        // 2 critical failures or three total are unanswered
		$calculatedScores["score"] .= ($notAnswered["critical_unanswered"] >= 2 || $notAnswered["total_unanswered"] >=3) ? "-Invalid" : '';
        

		// save the resultant total
		$result = $db->update($this->table, $calculatedScores, array('CommentID'=>$this->getCommentID()));

	}
    function _addAdditionalComments() {
    }
}

?>
