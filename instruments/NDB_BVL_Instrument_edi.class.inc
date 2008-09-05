<?php
class NDB_BVL_Instrument_edi extends NDB_BVL_Instrument
{
	
/*
INSERT INTO test_names VALUES ('', 'edi', 'EDI', '0', '1');
INSERT INTO instrument_subtests VALUES('', 'edi', 'edi_page1', 'Probes', 1);
INSERT INTO instrument_subtests VALUES('', 'edi', 'edi_page2', 'Other Events', 2);
INSERT INTO test_battery VALUES ('', 'edi', '1050', '1140', 'Y', 'Visit', '2');
*/
	//Commonly used level of indentation;
	var $indent = "&nbsp;&nbsp;&nbsp;&nbsp;";
	
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
        $this->_requiredElements = array('Examiner', 'EDI1', 'EDIbir');

        //Scoring column headers
        foreach($this->columnHeaders as $field=>$label) {
            $this->columnHeaders[$field] .= $this->indent;
        }
        $this->localDefaults = array_merge($this->localDefaults, $this->columnHeaders);
        
        //combine all scorable fields into one, savable array
        $this->scores = $this->total_symptomAnchors;
        $this->scores = array_merge($this->scores, $this->regulatoryAnchors);
        $this->scores = array_merge($this->scores, $this->socialAnchors);
        $this->scores = array_merge($this->scores, $this->communicationAnchors);
        $this->scores = array_merge($this->scores, $this->repetitive_behaviourAnchors);
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
        switch($this->page) {
            case "edi_page1":
            $this->_page1();
            break;
            
            case "edi_page2":
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
        $this->form->addElement('header', 'instrument_title', "Early Development Interview");
        
        // automatically adds examiner & date of administration
        $this->_addMetadataFields();
        
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
    }
    
    function _page1(){

    	//answers used for all questions
    	$answerArray = array(""=>NULL, "0_no"=>"0. No", "1_possible"=>"1. Possible", "2_definite"=>"2. Definite", "not_answered"=>"Not Answered");

    	$questionArray = array("1. Difficult to hold, cuddle?",
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

		$qNum = 1; //question number counter
		$otherQuestions = array(8, 19, 33, 45, 58, 70, 82, 96);
		$anchorPoints = array(1=>"0-3", 9=>"4-6", 20=>"7-9", 34=>"10-12", 46=>"13-15", 59=>"16-18", 71=>"19-21", 83=>"22-24");
		foreach($questionArray as $label) {
			if(array_key_exists($qNum, $anchorPoints) == TRUE) {
				$this->form->addElement("header", null, $anchorPoints[$qNum] . " months");
			}
			$this->form->addElement("select", "EDI" . $qNum , $label, $answerArray);
			if(in_array($qNum, $otherQuestions) == TRUE) {
				$this->addTextAreaElement("EDI" . $qNum . "ot", $this->indent . "Write in...");
			} 
			$qNum++;
		}
    }

    function _page2() {
		$answerArray = array(""=>NULL, "0_no"=>"0. No", "1_possible"=>"1. Possible", "2_definite"=>"2. Definite", "not_answered"=>"Not Answered");

		$this->form->addElement("header", null, "Family Changes");
		$questionArray = array("bir"=>"Birth of sibling",
								"dea"=>"Death of familiar family member",
								"div"=>"Divorce of parents",
								"mar"=>"Marriage of a parent",
								"mov"=>"Move to a new home",
								"tem"=>"Temporary absence of a family member",
								"per"=>"Permanent absence of a family member",
								"chc"=>"Changes in caretakers",
								"chs"=>"Changes in schedule/work");
	
		foreach($questionArray as $field=>$label) {
			$this->form->addElement("select", "EDI" . $field, $label, $answerArray);
		}							

		$this->form->addElement("header", null, "Child Medical Events");
		$questionArray = array("sei"=>"Seizure",
								"hea"=>"Head injury",
								"othi"=>"Other injuries and minor physical traumas",
								"hifv"=>"High fever",
								"hosp"=>"Hospitalization",
								"mill"=>"Minor illness");
		foreach($questionArray as $field=>$label) {
			$this->form->addElement("select", "EDI" . $field, $label, $answerArray);
		}
		
		$this->form->addElement("header", null, "Stressful Event");
		$questionArray = array("inj"=>"Injury/illness to relatives or friends",
								"dear"=>"Death of relative/friend",
								"conf"=>"Conflict in relationship with spouse/partner",
								"legl"=>"Legal matters for self or partner",
								"emp"=>"Employment/financial problems for self or partner",
								"crim"=>"Criminal matters for self, partner, or family");
		foreach($questionArray as $field=>$label) {
			$this->form->addElement("static", null, $label);
			$this->form->addElement("select", $field, $this->indent . "Code", $answerArray);
			$this->addTextElement($field . "_month" , $this->indent . "Month of pregnancy", array("$field{@}=={@}1_possible|2_definite"), "This is required if you answered 1. Possible or 2. Definite");
		}

		//`Other` questions
        for($field = 1; $field <= 2; $field++) {
    		$this->addTextElement("other_{$field}", "Other:");
    		$this->form->addElement("select", "other_{$field}", $this->indent . "Code", $answerArray);
    		$this->XINRegisterRule("other_{$field}", array("other_{$field}_status{@}=={@}"), "Please indicate a code, or mark the `Other` question as Not Answered");
    		$this->addTextElement("other_{$field}" . "_month" , $this->indent . "Month of pregnancy", array("$field{@}=={@}1_possible|2_definite"), "This is required if you answered 1. Possible or 2. Definite");
		}		
		$this->addTextAreaElement("EDIcomnt", "Comments:");
    }

    function score() {
        if($this->_determineDataEntryCompletionStatus() == "Incomplete") {
                return;
        }
	
	// Get the item scores
        $score_record=array();
        
        $db =& Database::singleton();
        if(PEAR::isError($db)) {
            return PEAR::raiseError ("Could not connect to database: ".$db->getMessage());
        }

        // null scores
        $this->_nullScores($this->regulatoryAnchors);
        $this->_nullScores($this->socialAnchors);
        $this->_nullScores($this->communicationAnchors);
        $this->_nullScores($this->repetitive_behaviourAnchors);

        $query = "SELECT * FROM ".$this->table." WHERE CommentID='".$this->getCommentID()."'";
        $db->selectRow($query, $score_record);
        if (PEAR::isError($score_record)) {
            return PEAR::raiseError("Could not get scores: ".$score_record->getMessage());
        }
        
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
            if($db->isError($result)) {
                return PEAR::raiseError("Could not save total score: ".$result->getMessage());
            }
        }

    }
}
?>
