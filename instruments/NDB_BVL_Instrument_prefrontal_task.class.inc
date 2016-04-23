<?php

require_once 'HTML/QuickForm.php';
require_once 'HTML/QuickForm/Renderer/Array.php';

class NDB_BVL_Instrument_prefrontal_task extends NDB_BVL_Instrument
{
    var $ValidityEnabled = false;
    var $ValidityRequired = false;

/*
INSERT INTO test_names VALUES ('', 'prefrontal_task', 'Prefrontal Task', '0', '1');
INSERT INTO instrument_subtests VALUES('', 'prefrontal_task', 'prefrontal_task_page1', 'Responses', 1);
INSERT INTO test_battery VALUES ('', 'prefrontal_task', '300', '780', 'Y', 'Visit', '3');
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
        $this->testName = "prefrontal_task";           // test_names.Test_name
        $this->table = 'prefrontal_task';              // name of database table corresponding to instrument
        // data keyed by commentID
        $this->commentID = $commentID;
        
        //The array of dates/timestamps to convert to database dates/timestamps
        //Any HTML_Quickform date elements must be listed here
        $this->dateTimeFields=array("Date_taken");
            
        //The array of selects with multiple answers allowed
        //Any HTML_Quickform multiple selects must be listed here
        $this->_selectMultipleElements = array();

        // required fields for data entry completion status
        $this->_requiredElements = array('Examiner', 'start_side');
        
        $this->localDefaults = array_merge($this->localDefaults, array("trial"=>"Trial", "outcome"=>"Outcome", "correct"=>"# Correct", "trials"=>"# Trials"));
	/**
	 * Array of column names to be ignored by the double data entry conflict detector.
	 */
	$this->_doubleDataEntryDiffIgnoreColumns = array('CommentID', 'UserID', 'Testdate',  'Window_Difference', 'Candidate_Age',
							 'invalidity_comment',
							 'invalidity_comment_status');
	

        // setup the form
        $this->_setupForm();

    }
    
    /**
    * method to build the HTML_Quickform object into a paged form
    *
    * @return void
    * @access private
    */
    function _setupForm(){
        if(preg_match("/prefrontal_task(_page[0-9]+)/",$this->page,$matches)){
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
        $this->form->addElement('header', 'instrument_title', "Prefrontal (A not B) Task");
        
        // automatically adds examiner & date of administration
        $this->_addMetadataFields();
        
        $this->form->addElement('header', null, 'Training');
        $this->form->addElement('select', 'training', "Did the child PASS or FAIL training?", array(null=>"", "pass"=>"PASS", "fail"=>"FAIL", 'not_answered'=>"Not Answered"));
        $this->form->addElement('static', null, "Training Trials (check all that apply)");
        $this->form->addElement('advcheckbox', "training_finds_partially_covered", $this->indent . "Finds partially covered", null, null, array("FALSE", "TRUE"));
        $this->form->addElement('advcheckbox', "training_finds_fully_covered", $this->indent . "Finds fully covered", null, null, array("FALSE", "TRUE"));
        
		$RL = array("R", "L");
		foreach($RL as $side) {
	        $this->form->addElement('advcheckbox', "training_retrieves_{$side}_well", $this->indent . "Retrives from {$side} well on trial", null, null, array("FALSE", "TRUE"));
	        $this->form->addElement('text', "training_retrieves_{$side}_well_trial", "");
	        $this->form->addElement('static', null, $this->indent . $this->indent . "of");
	        $this->form->addElement('text', "training_retrieves_{$side}_well_trial_of", "");
	        $this->XINRegisterRule("training_retrieves_{$side}_well_trial", array("training_retrieves_{$side}_well{@}=={@}TRUE"), "The trial number is required if Retrieves from {$side} well was checked.");
	        $this->XINRegisterRule("training_retrieves_{$side}_well_trial_of", array("training_retrieves_{$side}_well{@}=={@}TRUE"), "The of trial number is required if Retrieves from {$side} well was checked.");
		}
		
    }

    function _page1(){
    	
    	$this->form->addElement('header', null, "Responses");
    	$this->form->addElement('select', "start_side", "Start Side", array(null=>"", "left"=>"Left", "right"=>"Right", "not_answered"=>"Not Answered"));
        
    	//For both left and right answer columns
//    	$group[]=&$this->form->createElement('static', "left");
//    	$group[]=&$this->form->createElement('static', "right");
//    	$this->form->addGroup($group, "testers_group", "Tester's", $this->_GUIDelimiter, false);
//    	unset($group);
//    	foreach(range(1, 24) as $th) {
//			$group[] = &$this->form->createElement('select', "trial_{$th}_left", $th, array(null=>"", "correct"=>"&#10003;", "incorrect"=>"&#10008;", "no_reach_response"=>"No Reach/Response", "not_answered"=>"Not Answered"));
//			$group[] = &$this->form->createElement('select', "trial_{$th}_right", $th, array(null=>"", "correct"=>"&#10003;", "incorrect"=>"&#10008;", "no_reach_response"=>"No Reach/Response", "not_answered"=>"Not Answered"));
//			$this->form->addGroup($group, "trial_{$th}_group", $th, $this->_GUIDelimiter, false);
//			unset($group);
//        }

        //Column labels
        $this->form->addElement("static", "outcome", "Trial");
        
    	foreach(range(1, 24) as $th) {
            $this->form->addElement('select', "trial_{$th}", $th, array(null=>"", "0_incorrect"=>"0 = Incorrect", "1_correct"=>"1 = Correct", "9_missing_no_trial"=>"9 = Missing / No Trial"));
    	}
    	
		$this->form->addElement('header', null, "Reversals");
		$oneToFour = array("first"=>"First", "second"=>"Second", "third"=>"Third", "fourth"=>"Fourth");
		foreach($oneToFour as $thItem=>$thItemLabel) {
            $this->form->addElement("select", "{$thItem}_reversal", $thItemLabel . " Reversal Item #", array_merge(array(null=>""), range(1, 24), array('not_answered'=>"Not Answered"))); 
		}
		
		$this->form->addElement('header', null, "Validity");
		$answerArray = array(null=>"", "1_valid"=>"1 = Data is valid", "2_question_validity"=>"2 = Question validity", "3_invalid_data"=>"3 = Invalid data", "not_answered"=>"Not Answered");
		$this->form->addElement("select", "validity_of_data", "Validity of data", $answerArray);
		
		$answerArray = array(null=>"", "a_infant_not_attending"=>"a. Infant not able to attend/participate", "b_examiner_error"=>"b. Examiner Error", "c_parent_error"=>"c. Parent Error");

		$this->form->addElement("select", "invalidity_reason", "Select one invalidity reason", $answerArray);

		$this->XINRegisterRule("invalidity_reason", array("validity_of_data{@}=={@}2_question_validity|3_invalid_data"), "Please select one reason for invalidity");
		$this->addTextAreaElement("invalidity_comment", $this->indent . "Comments:", array("validity_of_data{@}=={@}2_question_validity|3_invalid_data"), "Please describe the reason below");

		$this->form->addElement('header', null, "Overall");
		$group[] = $this->form->createElement('static', "correct", null);
		$group[] = $this->form->createElement('static', "trials", null);
		$this->form->addGroup($group, "static_group", null, $this->_GUIDelimiter, false);
		unset($group);
		
		$answerArray = array(null=>'') + range(0, 24) + array('not_answered'=>"Not Answered"); 
		$questionArray = array("5sec_overall"=>"5 sec - overall",
		                       "5sec_reversals"=>"5 sec - reversals",
		                       "12sec_overall"=>"12 sec - overall",
		                       "12sec_reversals"=>"12 sec - reversals");
		foreach ($questionArray as $field=>$label) {
    		$group[]=&$this->form->createElement("select", $field . "_correct", null, $answerArray);
    		$group[]=&$this->form->createElement("select", $field . "_trials", null, $answerArray);
    		$this->form->addGroup($group, "{$field}_group", $label, $this->_GUIDelimiter, false);
    		unset($group);
		}
    }
}
?>
