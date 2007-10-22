<?php
class NDB_BVL_Instrument_prefrontal_task extends NDB_BVL_Instrument
{
/*
INSERT INTO test_names VALUES ('', 'prefrontal_task', 'Prefrontal Task', '0', '1');
INSERT INTO instrument_subtests VALUES('', 'prefrontal_task', 'prefrontal_task_page1', 'Responses', 1);
INSERT INTO test_battery VALUES ('', 'prefrontal_task', '300', '780', 'Y', 'Visit', '3');
*/

/*
This was a kinda wacky form.  Its sections may warrant some rearranging.  Not quite clear if there is scoring or not...
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
        $this->_requiredElements = array('Examiner', '<FIRST QUESTION OF EACH PAGE>');
        
        $this->localDefaults = array_merge($this->localDefaults, array("left"=>"Left", "right"=>"Right", "correct"=>"# Correct", "trials"=>"# Trials"));

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
        if(ereg("prefrontal_task(_page[0-9]+)",$this->page,$matches)){
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
        
    	$group[]=&$this->form->createElement('static', "left");
    	$group[]=&$this->form->createElement('static', "right");
    	$this->form->addGroup($group, "testers_group", "Tester's", $this->_GUIDelimiter, false);
    	unset($group);
    	foreach(range(1, 24) as $th) {
			$group[] = &$this->form->createElement('select', "trial_{$th}_left", $th, array(null=>"", "correct"=>"&#10003;", "incorrect"=>"&#10008;", "no_reach_response"=>"No Reach/Response", "not_answered"=>"Not Answered"));
			$group[] = &$this->form->createElement('select', "trial_{$th}_right", $th, array(null=>"", "correct"=>"&#10003;", "incorrect"=>"&#10008;", "no_reach_response"=>"No Reach/Response", "not_answered"=>"Not Answered"));
			$this->form->addGroup($group, "trial_{$th}_group", $th, $this->_GUIDelimiter, false);
			unset($group);
        }
    	
		$this->form->addElement('header', null, "Reversals");
		$oneToFour = array("first"=>"First", "second"=>"Second", "third"=>"Third", "fourth"=>"Fourth");
		foreach($oneToFour as $thItem=>$thItemLabel) {
			$this->addTextElement($thItem, $thItemLabel . " Reversal Item #");
		}
		
		$this->form->addElement('header', null, "Validity");
		$answerArray = array(null=>"", "1_valid"=>"1 = Data is valid", "2_question_validity"=>"2 = Question validity", "3_invalid_data"=>"3 = Invalid data", "not_answered"=>"Not Answered");
		$this->form->addElement("select", 'validity_of_data', "Validity of data", $answerArray);
		$this->form->addElement("advcheckbox", "validity_not_motivated", null, "a. Not motivated by reinforcers", null, array("FALSE", "TRUE"));
		$this->form->addElement("advcheckbox", "validity_noncompliant", null, "b. Noncompliant", null, array("FALSE", "TRUE"));
		$this->form->addElement("advcheckbox", "validity_intention_errors", null, "c. Intentionally making errors", null, array("FALSE", "TRUE"));
		$this->addTextAreaElement("validity_comment", $this->indent . "Comments:");
		
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