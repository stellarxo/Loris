<?php

require_once 'HTML/QuickForm.php';
require_once 'HTML/QuickForm/Renderer/Array.php';

class NDB_BVL_Instrument_edi extends NDB_BVL_Instrument
{
	
/*
INSERT INTO test_names VALUES ('', 'edi', 'EDI', '0', '1');

INSERT INTO instrument_subtests VALUES('', 'edi', 'edi_page1', '6month Probes', 1);
INSERT INTO instrument_subtests VALUES('', 'edi', 'edi_page2', '12month Probes', 2);
INSERT INTO instrument_subtests VALUES('', 'edi', 'edi_page3', '24month Probes', 3);
INSERT INTO instrument_subtests VALUES('', 'edi', 'edi_page4', 'Childhood Events, 0-6 months', 4);
INSERT INTO instrument_subtests VALUES('', 'edi', 'edi_page5', 'Pregnancy Events', 5);
INSERT INTO instrument_subtests VALUES('', 'edi', 'edi_page6', 'Childhood Events, 7-12 months', 6);
INSERT INTO instrument_subtests VALUES('', 'edi', 'edi_page7', 'Childhood Events, 13-24 months', 7);

INSERT INTO test_battery VALUES ('', 'edi', '1050', '1140', 'Y', 'Visit', '2');
*/
	
	var $total_symptomAnchors = array("score_0_3_total_symptoms"=>"",
                                "score_4_6_total_symptoms"=>"",
                                "score_7_9_total_symptoms"=>"",
                                "score_10_12_total_symptoms"=>"",
                                "score_13_15_total_symptoms"=>"",
                                "score_16_18_total_symptoms"=>"",
                                "score_19_21_total_symptoms"=>"",
                                "score_22_24_total_symptoms"=>"");	

	var $regulatoryAnchors = array("score_0_3_regulatory"=>"",
                                "score_4_6_regulatory"=>"",
                                "score_7_9_regulatory"=>"",
                                "score_10_12_regulatory"=>"",
                                "score_13_15_regulatory"=>"",
                                "score_16_18_regulatory"=>"",
                                "score_19_21_regulatory"=>"",
                                "score_22_24_regulatory"=>"");	

	
	var $socialAnchors = array("score_4_6_social"=>"",
                                "score_7_9_social"=>"",
                                "score_10_12_social"=>"",
                                "score_13_15_social"=>"",
                                "score_16_18_social"=>"",
                                "score_19_21_social"=>"",
                                "score_22_24_social"=>"");
                                
    var $communicationAnchors = array("score_7_9_communication"=>"",
                                "score_10_12_communication"=>"",
                                "score_13_15_communication"=>"",
                                "score_16_18_communication"=>"",
                                "score_19_21_communication"=>"",
                                "score_22_24_communication"=>"");
                                
    var $repetitive_behaviourAnchors = array("score_10_12_repetitive_behaviour"=>"",
                                "score_13_15_repetitive_behaviour"=>"",
                                "score_16_18_repetitive_behaviour"=>"",
                                "score_19_21_repetitive_behaviour"=>"",
                                "score_22_24_repetitive_behaviour"=>"");
                                
    //questionnaire sections
    
    var $questionArray = array("1. Difficult to hold, cuddle?",
                                "2. Exceptionally fussy, difficult to soothe?",
                                "3. Exceptionally easy baby, content doing own thing?",
                                "4. Overly sensitive/lack of sensitivity to noise, tactile input?",
                                "5. Sleeping problems?",
                                "6. Feeding problems?",
                                "7. Oddities in muscle tone?",
                                "8. Anything else that gave you concern? (write in)",
                                "9. Difficult to hold, cuddle?",
                                "10. Exceptionally fussy, difficult to soothe?",
                                "11. Exceptionally easy baby?",
                                "12. Overly sensitive/lack of sensitivity to noise, tactile input?",
                                "13. Sleeping problems?",
                                "14. Feeding problems?",
                                "15. Oddities in muscle tone?",
                                "16. Lack of smiling at people?",
                                "17. Exceptionally long attention span for nonsocial things?",
                                "18. Exceptionally long attention span for social things?",
                                "19. Anything else that gave you concern? (write in)",
                                "20. Difficult to hold, cuddle?",
                                "21. Exceptionally fussy, difficult to soothe?",
                                "22. Exceptionally easy baby?",
                                "23. Overly sensitive/lack of sensitivity to noise, tactile input?",
                                "24. Sleeping problems?",
                                "25. Feeding problems?",
                                "26. Oddities in muscle tone?",
                                "27. Lack of smiling at people?",
                                "28. Difficult to catch his/her eye?",
                                "29. Lack of orienting to name?",
                                "30. Failure to use vocalizations socially?",
                                "31. Exceptionally long attention span for nonsocial things?",
                                "32. Exceptionally long attention span for social things?",
                                "33. Anything else that gave you concern? (write in)",
                                "34. Overly sensitive/lack of sensitivity to noise...?",
                                "35. Sleeping problems?",
                                "36. Oddities in muscle tone?",
                                "37. Repetitive/stereotyped motor movements?",
                                "38. Excessive mouthing?",
                                "39. Lack of smiling at people?",
                                "40. Lack of orienting to name?",
                                "41. Poor eye contact, difficult to catch his/her eye?",
                                "42. Failure to follow point?",
                                "43. Lack of babbling?",
                                "44. Failure to use vocalizations socially/lack of imitative babbling?",
                                "45. Anything else that gave you concern? (write in)",
                                "46. Overly sensitive/lack of sensitivity to noise...?",
                                "47. Sleeping problems?",
                                "48. Oddities in muscle tone?",
                                "49. Repetitive/stereotyped motor movements?",
                                "50. Lack of orienting to name?",
                                "51. Poor eye contact, difficult to catch his/her eye?",
                                "52. Lack of interest in interactive baby games?",
                                "53. Failure to initiate simple, ritualized social interaction?",
                                "54. Failure to follow point?",
                                "55. Failure to show objects?",
                                "56. Lack of pointing to express interest?",
                                "57. Failure to use words meaningfully?",
                                "58. Anything else that gave you concern? (write in)",
                                "59. Overly sensitive/lack of sensitivity to noise...?",
                                "60. Repetitive/stereotyped motor movements?",
                                "61. Lack of orienting to name?",
                                "62. Poor eye contact, difficult to catch his/her eye?",
                                "63. Failure to follow point?",
                                "64. Lack of pointing to express interest?",
                                "65. Failure to initiate simple, ritualized social interaction?",
                                "66. Failure to increase vocabulary/language from previous timepoint?",
                                "67. Failure to imitate actions on objects?",
                                "68. Failure to use formal gestures?",
                                "69. Placed adult?s hand on desired objects/moved adult?s hand?",
                                "70. Anything else that gave you concern? (write in)",
                                "71. Overly sensitive/lack of sensitivity to noise...?",
                                "72. Repetitive/stereotyped motor movements?",
                                "73. Lack of orienting to name?",
                                "74. Poor eye contact, difficult to catch his/her eye?",
                                "75. Failure to follow point/gaze?",
                                "76. Lack of pointing to express interest?",
                                "77. Failure to initiate simple, ritualized social interaction?",
                                "78. Failure to increase vocabulary/language from previous timepoint?",
                                "79. Failure to use formal gestures?",
                                "80. Failure to imitate actions on objects?",
                                "81. Placed adult?s hand on desired objects/moved adult?s hand?",
                                "82. Anything else that gave you concern? (write in)",
                                "83. Overly sensitive/lack of sensitivity to noise...?",
                                "84. Repetitive/stereotyped motor movements?",
                                "85. Lack of orienting name?",
                                "86. Poor eye contact, difficult to catch his/her eye?",
                                "87. Failure to follow point/gaze?",
                                "88. Lack of pointing to express interest?",
                                "89. Failure to initiate simple, ritualized social interaction?",
                                "90. Failure to use increase language/vocabulary from previous timepoint?",
                                "91. Failure to combine words?",
                                "92. Failure to use formal gestures?",
                                "93. Placed adult?s hand on desired objects/moved adult?s hand?",
                                "94. Had routines/rituals?",
                                "95. Had unusual attachments to objects?",
                                "96. Anything else that gave you concern? (write in)");

    var $familyChanges = array("bir"=>"Birth of sibling",
								"dea"=>"Death of familiar family member",
								"div"=>"Divorce of parents",
								"mar"=>"Marriage of a parent",
								"mov"=>"Move to a new home",
								"tem"=>"Temporary absence of a family member",
								"per"=>"Permanent absence of a family member",
								"chc"=>"Changes in caretakers",
								"chs"=>"Changes in schedule/work");
	
	var $childMedicalEvents = array("sei"=>"Seizure",
								"hea"=>"Head injury",
								"othi"=>"Other injuries and minor physical traumas",
								"hifv"=>"High fever",
								"hosp"=>"Hospitalization",
								"mill"=>"Minor illness");
								
	var $stressfulEvent = array("inj"=>"Injury/illness to relatives or friends",
								"dear"=>"Death of relative/friend",
								"conf"=>"Conflict in relationship with spouse/partner",
								"legl"=>"Legal matters for self or partner",
								"emp"=>"Employment/financial problems for self or partner",
								"crim"=>"Criminal matters for self, partner, or family");
								
    var $columnHeaders = array("total_symptoms"=>"Total Symptoms", "regulatory"=>"Regulatory", "social"=>"Social",
            "communication"=>"Communication", "repetitive_behaviour"=>"Repetitive Behaviour");

    //combined array to hold the calculated scores
    var $scores = array();

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
        $this->testName = "edi";           // test_names.Test_name
        $this->table = 'edi';              // name of database table corresponding to instrument
        // data keyed by commentID
        $this->commentID = $commentID;
        
        //The array of dates/timestamps to convert to database dates/timestamps
        //Any HTML_Quickform date elements must be listed here
        $this->dateTimeFields=array("Date_taken");
            
        //The array of selects with multiple answers allowed
        //Any HTML_Quickform multiple selects must be listed here
        $this->_selectMultipleElements = array();

        // required fields for data entry completion status
        $this->_requiredElements = array('Examiner');

        // Find the Date_taken
        $db =& Database::singleton();
        
        $query = "SELECT Date_taken from " . $this->testName . " WHERE CommentID = '".$this->getCommentID()."'";
        $result = $db->selectOne($query);
        $this->Date_taken=$result;

        //Scoring column headers
        foreach($this->columnHeaders as $field=>$label) {
            $this->columnHeaders[$field] .= $this->indent;
        }
        $this->localDefaults = array_merge($this->localDefaults, $this->columnHeaders);


        //combine all scorable fields into one, savable array
        $this->scores = array_merge($this->total_symptomAnchors, $this->regulatoryAnchors, $this->socialAnchors, $this->communicationAnchors, $this->repetitive_behaviourAnchors);

/**
     * Array of column names to be ignored by the double data entry conflict detector.
     
    $this->_doubleDataEntryDiffIgnoreColumns = array('CommentID', 'UserID', 'Testdate', 'EDI8ot', 'EDI19ot','Window_Difference', 'Candidate_Age',
                                                   'EDI45ot', 'EDI58ot', 'EDI70ot', 'EDI82ot', 'EDI96ot', 'inj_month',
                                                   'dear_month', 'conf_month', 'legl_month', 'emp_month', 'crim_month',
                                                   'other_1_month', 'other_2_month', 'comnt');
*/
        //combine all scorable fields into one, savable array
        $this->scores = array_merge($this->total_symptomAnchors, $this->regulatoryAnchors, $this->socialAnchors, $this->communicationAnchors, $this->repetitive_behaviourAnchors);

/**
     * Array of column names to be ignored by the double data entry conflict detector.
     */
    $this->_doubleDataEntryDiffIgnoreColumns = array('CommentID', 'UserID', 'Testdate',   'Window_Difference', 'Candidate_Age',
						     'EDI8ot', 
						     'EDI19ot', 
						     'EDI45ot', 
						     'EDI58ot', 
						     'EDI70ot', 
						     'EDI82ot', 
						     'EDI96ot', 
						     'inj_month',
						     'dear_month', 
						     'conf_month', 
						     'legl_month', 
						     'emp_month', 
						     'crim_month',
						     'other_1_month', 
						     'other_2_month', 
						     'comnt',
						     'EDI8ot_status', 
						     'EDI19ot_status', 
						     'EDIT33ot_status',
						     'EDI45ot_status', 
						     'EDI58ot_status', 
						     'EDI70ot_status', 
						     'EDI82ot_status', 
						     'EDI96ot_status', 
						     'inj_month_status',
						     'dear_month_status', 
						     'conf_month_status', 
						     'legl_month_status', 
						     'emp_month_status', 
						     'crim_month_status',
						     'other_1_month_status', 
						     'other_2_month_status', 
						     'comnt_status',
                             'other_1', 'other_2',
                             'EDI33ot_status',
                             'score_0_3_total_symptoms',
                             'score_0_3_regulatory',
                             'score_4_6_total_symptoms',
                             'score_4_6_regulatory',
                             'score_4_6_social',
                             'score_7_9_total_symptoms',
                             'score_7_9_regulatory',
                             'score_7_9_social',
                             'score_7_9_communication',
                             'score_10_12_total_symptoms',
                             'score_10_12_regulatory',
                             'score_10_12_social',
                             'score_10_12_communication',
                             'score_10_12_repetitive_behaviour',
                             'score_13_15_total_symptoms',
                             'score_13_15_regulatory',
                             'score_13_15_social',
                             'score_13_15_communication',
                             'score_13_15_repetitive_behaviour',
                             'score_16_18_total_symptoms',
                             'score_16_18_regulatory',
                             'score_16_18_social',
                             'score_16_18_communication',
                             'score_16_18_repetitive_behaviour',
                             'score_19_21_total_symptoms',
                             'score_19_21_regulatory',
                             'score_19_21_social',
                             'score_19_21_communication',
                             'score_19_21_repetitive_behaviour',
                             'score_22_24_total_symptoms',
                             'score_22_24_regulatory',
                             'score_22_24_social',
                             'score_22_24_communication',
                             'score_22_24_repetitive_behaviour',
                             'Data_entry_completion_status');


        // setup the form
        $this->_setupForm();

    }
    
    function _determineDataEntryCompletionStatus(){
    
        // If Date_taken has not yet been set, then don't run any of the following code.
        if(is_null($this->Date_taken)){
            return 'Incomplete';
        }
        
        //get DoB
        $db =& Database::singleton();

        // Get the subject DoB for scoring
        $timepoint =& TimePoint::singleton($this->getSessionID());
        $dob = $timepoint->getEffectiveDateOfBirth();
        
		$age = Utility::calculateAge($dob, $this->Date_taken);

        //determine subProjectID
        $subProjectID = $timepoint->getSubprojectID();
        //determine required questions
        $this->_determineRequiredQuestions($age, $subProjectID);
        
        if(empty($this->_requiredElements)) return 'Complete';

        $db =& Database::singleton();
        $query = "SELECT ".join(',', $this->_requiredElements)." FROM $this->table WHERE CommentID='".$this->getCommentID()."'";
        $success = $db->selectRow($query, $dataFields);

        //compare
        return parent::_determineDataEntryCompletionStatus();
    }
    
    function _determineRequiredQuestions($age, $subProjectID){
        //get age in days, to more easily compare with the test_battery;
        $ageDays = $age['year'] * 365 + $age['mon'] * 30.5 + $age['day'];

        // 6month visit
        if($ageDays <= 270 && $subProjectID == 1) {
            //6m recruit,
            if($subProjectID == 1) {
                $this->_requiredElements = array_merge($this->_requiredElements, array("EDI1", "EDI9", "bir_0_6months", "sei_0_6months", "inj"));}
        }
        
        // 12month visit
        elseif($ageDays >= 300 && $ageDays <= 420) {
            //6m recruit
            if($subProjectID == 1) {
                $this->_requiredElements = array_merge($this->_requiredElements, array("EDI20", "EDI34", "bir_7_12months", "sei_7_12months"));
            }

            //12m recruit
            elseif($subProjectID == 2) {
                $this->_requiredElements = array_merge($this->_requiredElements, array("EDI1", "EDI9", "EDI20", "EDI34", "bir_0_6months", "sei_0_6months", "inj", "bir_7_12months", "sei_7_12months"));
            }
        } 
        // 18 month visit
        elseif($ageDays >= 510 && $ageDays <= 570) {
            $this->_requiredElements = array_merge($this->_requiredElements, array("EDI46", "EDI59", "bir_13_18months", "sei_13_18months"));
        }
        // 24month visit
        elseif($ageDays >= 660 && $ageDays <= 780) {
            $this->_requiredElements = array_merge($this->_requiredElements, array("EDI71", "EDI83", "bir_19_24months", "sei_19_24months"));
        }            
    }
    
    /**
    * method to build the HTML_Quickform object into a paged form
    *
    * @return void
    * @access private
    */
    function _setupForm(){
        //If trying to start anywhere but the _main page...
        if(!empty($this->page) && empty($this->Date_taken)){
            $this->form->addElement("header", null, "<p><b style='color:red'>Please return to the Top page and enter the subjects age details.</b>");
            //$this->form->freeze();
            //return;
        }

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
        $this->form->addElement('header', 'instrument_title', "Early Development Interview");
        
        // automatically adds examiner & date of administration
        $this->_addMetadataFields();
        
        $this->form->addElement('static', null, "You need only complete the time-appropriate pages.");
        $this->form->addElement('static', null, "Any unasked pages may be left completely blank.");

        $this->form->addElement('static', null, null);
        $this->form->addElement('header', null, "Scores");

        //scoring column headers
        $group[] = $this->form->createElement('static', "total_symptoms");
        $group[] = $this->form->createElement('static', "regulatory");
        $group[] = $this->form->createElement('static', "social");
        $group[] = $this->form->createElement('static', "communication");
        $group[] = $this->form->createElement('static', "repetitive_behaviour");
        $this->form->addGroup($group, 'score_header_group', "Anchor Point (months)", $this->_GUIDelimiter, FALSE);
        unset($group);
        
        //score fields
        $anchorPoints = array("0_3"=>"0-3", "4_6"=>"4-6", "7_9"=>"7-9", "10_12"=>"10-12", "13_15"=>"13-15", "16_18"=>"16-18", "19_21"=>"19-21", "22_24"=>"22-24");
        
        foreach($anchorPoints as $field=>$label) {
            foreach($this->columnHeaders as $scoreField=>$scoreLabel) {
                if(array_key_exists("score_{$field}_{$scoreField}", $this->scores)) //not all subscales apply at all ages
                    $group[] = $this->form->createElement('static', "score_{$field}_{$scoreField}");
            }
            $this->form->addGroup($group, "{$label}_group", $label, $this->_GUIDelimiter, FALSE);
            unset($group);
        }
        $this->form->addElement('static',null,'<br>');
        $this->form->addElement("textarea", "other_comments", "Comments about Validity:", array('cols'=>25, 'rows'=>4));
        $this->XINRegisterRule("other_comments", array("{other_comments}{@}=={@}NEVER_REQUIRED"));

    }
    
    function _page1(){
        $this->generateQuestions(1, 19);
    }
    
    function _page2(){
        $this->generateQuestions(20, 26);
    }
  
    function _page3() {
	$this->generateQuestions(46, 25);
    }

    function _page4() {  
//    function _page3() {
        $this->generateQuestions(71, 1000);
    }
    
  
    function _page5() {  
 //   function _page5(){
		$answerArray = array(""=>NULL, "0_no"=>"0. No", "1_possible"=>"1. Possible", "2_definite"=>"2. Definite", "not_answered"=>"Not Answered");

		$this->form->addElement("header", null, "Stressful Events During Pregnancy");
		$this->form->addElement('static', null, "<br/>");
		$questionArray = $this->stressfulEvent;
		
		foreach($questionArray as $field=>$label) {
			$this->form->addElement("static", null, $label);
			$this->form->addElement("select", $field, $this->indent . "Code", $answerArray);
			$this->addTextElement($field . "_month" , $this->indent . "Month of pregnancy", array("$field{@}=={@}1_possible|2_definite"), "This is required if you answered 1. Possible or 2. Definite");
		}
		//`Other` questions
        for($field = 1; $field <= 2; $field++) {
    		$this->addTextElement("other_{$field}", "Other:");
    		$this->form->addElement("select", "other_{$field}_code", $this->indent . "Code", $answerArray);
    		$this->XINRegisterRule("other_{$field}_code", array("other_{$field}_status{@}=={@}"), "Please indicate a code, or mark the `Other` question as Not Answered");
    		$this->addTextElement("other_{$field}_month" , $this->indent . "Month of pregnancy", array("other_{$field}_code{@}=={@}1_possible|2_definite"), "This is required if you answered 1. Possible or 2. Definite");
		}		
		$this->addTextAreaElement("comnt", "Comments:");
		$this->form->addElement('static', null, "<br/>");
    }


    function _page6() {  

//    function _page4() {
		$answerArray = array(""=>NULL, "0_no"=>"0. No", "1_possible"=>"1. Possible", "2_definite"=>"2. Definite", "not_answered"=>"Not Answered");

		$this->form->addElement("header", null, "Family Changes, 0-6 months");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "</br>");
		$questionArray = $this->familyChanges;
		
		foreach($questionArray as $field=>$label) {
			$this->form->addElement("select", $field . "_0_6months", $label, $answerArray);
		}							

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("header", null, "Child Medical Events, 0-6 months");
		$this->form->addElement('static', null, "<br/>");
		$questionArray = $this->childMedicalEvents;
		
		foreach($questionArray as $field=>$label) {
			$this->form->addElement("select", $field . "_0_6months", $label, $answerArray);
		}

		$this->form->addElement('static', null, "<br/>");
    }


    function _page7() {  

//    function _page6() {
		$answerArray = array(""=>NULL, "0_no"=>"0. No", "1_possible"=>"1. Possible", "2_definite"=>"2. Definite", "not_answered"=>"Not Answered");

		$this->form->addElement("header", null, "Family Changes, 7-12 months");
		$this->form->addElement('static', null, "<br/>");
		$questionArray = $this->familyChanges;
		
		foreach($questionArray as $field=>$label) {
			$this->form->addElement("select", $field . "_7_12months", $label, $answerArray);
		}							

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("header", null, "Child Medical Events, 7-12 months");
		$questionArray = $this->childMedicalEvents;
		
		foreach($questionArray as $field=>$label) {
			$this->form->addElement("select", $field . "_7_12months", $label, $answerArray);
		}

		$this->form->addElement('static', null, "<br/>");
    }
    

    function _page8() {  

//    function _page7() {
		$answerArray = array(""=>NULL, "0_no"=>"0. No", "1_possible"=>"1. Possible", "2_definite"=>"2. Definite", "not_answered"=>"Not Answered");

		$this->form->addElement("header", null, "Family Changes, 13-24 months");
		$this->form->addElement('static', null, "<br/>");
		$questionArray = $this->familyChanges;
		
		foreach($questionArray as $field=>$label) {
			$this->form->addElement("select", $field . "_13_24months", $label, $answerArray);
		}							

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("header", null, "Child Medical Events, 13-24 months");
		$this->form->addElement('static', null, "<br/>");
		$questionArray = $this->childMedicalEvents;
		
		foreach($questionArray as $field=>$label) {
			$this->form->addElement("select", $field . "_13_24months", $label, $answerArray);
		}

		$this->form->addElement('static', null, "<br/>");
    }
    
    function _page9() {

//    function _page7() {
                $answerArray = array(""=>NULL, "0_no"=>"0. No", "1_possible"=>"1. Possible", "2_definite"=>"2. Definite", "not_answered"=>"Not Answered");

                $this->form->addElement("header", null, "Family Changes, 13-18 months");
		$this->form->addElement('static', null, "<br/>");
                $questionArray = $this->familyChanges;

                foreach($questionArray as $field=>$label) {
                        $this->form->addElement("select", $field . "_13_18months", $label, $answerArray);
                }

		$this->form->addElement('static', null, "<br/>");
                $this->form->addElement("header", null, "Child Medical Events, 13-18 months");
		$this->form->addElement('static', null, "<br/>");
                $questionArray = $this->childMedicalEvents;

                foreach($questionArray as $field=>$label) {
                        $this->form->addElement("select", $field . "_13_18months", $label, $answerArray);
                }

		$this->form->addElement('static', null, "<br/>");
    }

    function _page10() {

//    function _page7() {
                $answerArray = array(""=>NULL, "0_no"=>"0. No", "1_possible"=>"1. Possible", "2_definite"=>"2. Definite", "not_answered"=>"Not Answered");

                $this->form->addElement("header", null, "Family Changes, 19-24 months");
		$this->form->addElement('static', null, "<br/>");
                $questionArray = $this->familyChanges;

                foreach($questionArray as $field=>$label) {
                        $this->form->addElement("select", $field . "_19_24months", $label, $answerArray);
                }

		$this->form->addElement('static', null, "<br/>");
                $this->form->addElement("header", null, "Child Medical Events, 19-24 months");
		$this->form->addElement('static', null, "<br/>");
                $questionArray = $this->childMedicalEvents;

                foreach($questionArray as $field=>$label) {
                        $this->form->addElement("select", $field . "_19_24months", $label, $answerArray);
		}

		$this->form->addElement('static', null, "<br/>");
    }


    function generateQuestions($qNum, $questionCount) {
    	//answers used for all questions
    	$answerArray = array(""=>NULL, "0_no"=>"0. No", "1_possible"=>"1. Possible", "2_definite"=>"2. Definite", "not_answered"=>"Not Answered");

		$otherQuestions = array(8, 19, 33, 45, 58, 70, 82, 96);
		$anchorPoints = array(1=>"0-3", 9=>"4-6", 20=>"7-9", 34=>"10-12", 46=>"13-15", 59=>"16-18", 71=>"19-21", 83=>"22-24");
		$questionArray = array_slice($this->questionArray, $qNum - 1, $questionCount);
		foreach($questionArray as $label) {
			if(array_key_exists($qNum, $anchorPoints) == TRUE) {
				$this->form->addElement('static', null, "<br/>");
				$this->form->addElement("header", null, $anchorPoints[$qNum] . " months");
				$this->form->addElement('static', null, "<br/>");
			}
			$this->form->addElement("select", "EDI" . $qNum , $label, $answerArray);
			if(in_array($qNum, $otherQuestions) == TRUE) {
				$this->addTextAreaElement("EDI" . $qNum . "ot", $this->indent . "Write in...");
			} 
			$qNum++;
		}
				$this->form->addElement('static', null, "<br/>");
    }

    function score() {
        if($this->_determineDataEntryCompletionStatus() == "Incomplete") {
                return;
        }

        // Get the item scores
        $score_record=array();
        
        $db =& Database::singleton();

        // null scores
        $this->_nullScores($this->regulatoryAnchors);
        $this->_nullScores($this->socialAnchors);
        $this->_nullScores($this->communicationAnchors);
        $this->_nullScores($this->repetitive_behaviourAnchors);

        $query = "SELECT * FROM ".$this->table." WHERE CommentID='".$this->getCommentID()."'";
        $db->selectRow($query, $score_record);
        
        //convert answers to numbers only
        foreach($score_record as $field=>$score) {
            $score_record[$field] = intval(substr($score, 0, 1)); //only take integer values, not the 'n' of not_answered
        }
        
        //average scores
        $decimalPlaces = 4;
        $totalApplicableQuestions = array("score_0_3_total_symptoms"=>range(1,8),
                                "score_4_6_total_symptoms"=>range(9,19),
                                "score_7_9_total_symptoms"=>range(20, 33),
                                "score_10_12_total_symptoms"=>range(34, 45),
                                "score_13_15_total_symptoms"=>range(46, 58),
                                "score_16_18_total_symptoms"=>range(59, 70),
                                "score_19_21_total_symptoms"=>range(71, 82),
                                "score_22_24_total_symptoms"=>range(83, 96));
        foreach($totalApplicableQuestions as $field=>$numbers) {
            foreach($numbers as $number) {
                $this->scores[$field] += $score_record["EDI{$number}"];
            }
            $this->scores[$field] = round($this->scores[$field] / count($numbers), $decimalPlaces);
        }
        
        $regulatoryApplicableQuestions = array("score_0_3_regulatory"=>array(1,2,3,4,5,6), 
                                                "score_4_6_regulatory"=>array(9, 10, 11, 12, 13, 14),
                                                "score_7_9_regulatory"=>array(20, 21, 22, 23, 24, 25),
                                                "score_10_12_regulatory"=>array(34, 35, 36),
                                                "score_13_15_regulatory"=>array(46, 47, 48),
                                                "score_16_18_regulatory"=>array(59),
                                                "score_19_21_regulatory"=>array(71),
                                                "score_22_24_regulatory"=>array(83));
        foreach($regulatoryApplicableQuestions as $field=>$numbers) {
            foreach($numbers as $number) {
                $this->scores[$field] += $score_record["EDI{$number}"];
            }
            $this->scores[$field] = round($this->scores[$field] / count($numbers), $decimalPlaces);
        }	

        $socialApplicableQuestions = array("score_4_6_social"=>array(16, 17),
                                "score_7_9_social"=>array(27, 28, 29, 31),
                                "score_10_12_social"=>array(39, 40, 41, 42),
                                "score_13_15_social"=>array(50, 51, 52, 53, 54, 55, 56),
                                "score_16_18_social"=>array(61, 62, 63, 64, 65, 67),
                                "score_19_21_social"=>array(73, 74, 75, 76, 77, 80),
                                "score_22_24_social"=>array(85, 86, 87, 88, 89));
        foreach($socialApplicableQuestions as $field=>$numbers) {
            foreach($numbers as $number) {
                $this->scores[$field] += $score_record["EDI{$number}"];
            }
            $this->scores[$field] = round($this->scores[$field] / count($numbers), $decimalPlaces);
        }	
        
        $communicationApplicableQuestions = array("score_7_9_communication"=>array(30),
                                "score_10_12_communication"=>array(43, 44),
                                "score_13_15_communication"=>array(57),
                                "score_16_18_communication"=>array(66, 68, 69),
                                "score_19_21_communication"=>array(78, 79, 81),
                                "score_22_24_communication"=>array(90, 91, 92, 93));
        foreach($communicationApplicableQuestions as $field=>$numbers) {
            foreach($numbers as $number) {
                $this->scores[$field] += $score_record["EDI{$number}"];
            }
            $this->scores[$field] = round($this->scores[$field] / count($numbers), $decimalPlaces);
        }	
        
        $repetitive_behaviourApplicableQuestions = array("score_10_12_repetitive_behaviour"=>array(37),
                                "score_13_15_repetitive_behaviour"=>array(49),
                                "score_16_18_repetitive_behaviour"=>array(60),
                                "score_19_21_repetitive_behaviour"=>array(72),
                                "score_22_24_repetitive_behaviour"=>array(84, 94, 95));                                
        foreach($repetitive_behaviourApplicableQuestions as $field=>$numbers) {
            foreach($numbers as $number) {
                $this->scores[$field] += $score_record["EDI{$number}"];
            }
            $this->scores[$field] = round($this->scores[$field] / count($numbers), $decimalPlaces);
        }	
       
        // update if any scores
        if (is_array($this->scores) && count($this->scores)>0) {
            $result = $db->update($this->table, $this->scores, array('CommentID'=>$this->getCommentID()));
        }

    }
}
?>
