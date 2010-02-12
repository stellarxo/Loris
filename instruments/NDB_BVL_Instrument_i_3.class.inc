<?php

class NDB_BVL_Instrument_i_3 extends NDB_BVL_Instrument {



 var $columnHeaders = array("presence_header",
    "relative_header",
    "other_relative_header");
    var $yesNo = array('0_no'=>"0. No", "1_yes"=>"1. Yes", "not_answered"=>"Not Answered");


        // Column headers
        $this->localDefaults = array_merge($this->localDefaults, array("list_interest"=>"List AND describe Interest",
        "age_onset"=>"Age of Onset",
        "intensity"=>"Intensity", "peculiarity"=>"Peculiarity", "persistent"=>"Persistent"));


	
							   
    /**
    * sets up basic data, such as the HTML_Quickform object, and so on.
    *
    * @param string $commentID  the CommentID identifying the data to load
    * @param string $page       if a multipage form, the page to show
    * @return void
    * @access public
    */
    function setup($commentID, $page)
    {
        $this->formType="XIN";
        $this->form = new HTML_Quickform('test_form');
        $this->page = $page;            // page label (number or
        // string - used by
        // user-defined child classes)
        
        // set the object properties
        $this->testName = "i_3";           // test_names.Test_name
        $this->table = 'i_3';              // name of table containing
        // data keyed by commentID
        $this->commentID = $commentID;
        
        //The array of dates/timestamps to convert to database dates/timestamps
        $this->dateTimeFields=array("Date_taken");
        
        // setup the form
        $this->_setupForm();
        // required fields for data entry completion status
        $this->_requiredElements = array('Examiner', 'q_1', 'q_32', 'q_90', 'q_149', 'q_174');
        
        //
        $scoreHeader = array("scale"=>"Score");
        $this->localDefaults = array_merge($this->localDefaults, $scoreHeader);
    } 
    
    /**
    * method to build the HTML_Quickform object into a paged form
    *
    * @return void
    * @access private
    */
    function _setupForm()
    {
    	$this->answer_options=array(NULL=>'', '1'=>'1', '2'=>'2', '3'=>'3', '4'=>'4', '5'=>'5', '6'=>'6', '7'=>'7', 'does_not_apply'=>'Does not apply', 'not_answered'=>'Not Answered');
    	
    	if(ereg("(_page[0-9])", $this->page, $matches)) {
    		call_user_method($matches[1], &$this);
    	} else {
    		$this->_main();
    	}
    	
    	$this->form->addFormRule(array(&$this,'XINValidate'));
    }
    
    function _main(){
            // display test name
            $this->form->addElement('header', 'instrument_title', "Infant Behavior Questionnaire - Revised (IBQ-R)");
            
            // add examiner & date of administration
            $this->_addMetadataFields();
            
            $this->form->addElement('header', null, 'Calculate Scores');
            
            //score headers
            $this->form->addElement('static', "scale", "Scale");
            
            //score columns
            foreach($this->scoreLabels as $field=>$label) {
            	$this->form->addElement('static', $field, $label);
            }
    	//calculate subscales
    
        }
        
    function score(){
    	if($this->_determineDataEntryCompletionStatus() == "Incomplete") {
    		return;
    	}
    	
    	//null scores
		$this->_nullScores($this->scoreLabels);

		//get the saved scores
    	$db =& Database::singleton();
    	if(PEAR::isError($db)) {
			return PEAR::raiseError ("Could not connect to database".$db->getMessage());
    	}
    	
    	$query = "SELECT * FROM $this->table WHERE CommentID = '$this->commentID'";
    	$record = array();
    	$db->selectRow($query, $record);
    	if (PEAR::isError($record)) {
    		return PEAR::raiseError("Could not retrieve scores: " . $record->getMessage());
    	}
    	
    	//do the math...
    	$reverseItems = array(1, 14, 117,
    							11, 16, 19, 76,
    							163,
    							176, 179, 182, 185, 188, 191,
    							22, 24, 26, 29, 120, 121,
    							7, 105, 108, 124, 125, 127, 128, 130, 132,
    							89, 173);
    	//restrict to numerical scores
    	foreach ($record as $field=>$value) {
    		if(is_numeric($value)) {
    			$record[$field] = intval($value);
    		} else {
    			$record[$field] = null;
    		}
	    	//reverse as needed
    		if (in_array(ereg_replace("q_", "", $field), $reverseItems) && !is_null($record[$field])) {
    			$record[$field] = 8 - $record[$field];
    		}
    	}

    	
    	//calculate subscales
	   	$subScales = array("activity_level"=>array(1, 2, 3, 12, 13, 14, 32, 33, 38, 39, 111, 112, 115, 116, 117),
							"distress_to_limitations"=>array_merge(array(11), range(15, 20), array(41, 44, 75, 76, 93, 109, 113, 114, 118)),
							"fear"=>array_merge(array(90, 94, 99), range(150, 158), range(161, 164)),
							"duration_of_orienting"=>array_merge(range(46, 51), array(54, 55, 91, 92, 100, 101)),
							"smiling_and_laughter"=>array(34, 36, 37, 40, 43, 53, 56, 57, 110, 149),
							"high_pleasure"=>array_merge(array(58, 65, 66, 67), range(77, 82), array(165)),
							"low_pleasure"=>array_merge(range(59, 64), range(68, 74)),
							"soothability"=>range(174, 191),
							"falling_reactivity"=>array_merge(range(21, 29), range(119, 122)),
							"cuddliness"=>array_merge(array(5, 6, 7, 105, 106, 107, 108), range(123, 132)),
							"perceptual_sensitivity"=>array_merge(array(4, 83, 84, 95, 96), range(133, 139)),
							"sadness"=>array_merge(array(30, 31), range(140, 145), range(166, 171)),
							"approach"=>array_merge(range(85, 89), array(97, 98, 104, 159, 160, 172, 173)),
							"vocal_reactivity"=>array(8, 9, 10, 35, 42, 45, 52, 102, 103, 146, 147, 148)
						   );
		
		foreach($subScales as $field=>$array) {
			$numericalResponses = 0;
			foreach($array as $question) {
				$scores[$field] += $record["q_".$question];
				if($record["q_".$question]) {
					$numericalResponses++;
				}
			}
			//take average of numerical responses
			if ($numericalResponses == 0) {
				$scores[$field] = null;
			} else {
				$scores[$field] = round($scores[$field] / $numericalResponses, 2);
			}
		}
		
    	//save scores
		$result = $db->update($this->table, $scores, array("CommentID"=>$this->getCommentID()));
		if($db->isError($result)) {
			return PEAR::raiseError("Could not save total score: ". $result->getMessage());
		}
		
    }    
        
    function _page1(){
        
	$this->form->addElement('header', null, "INTENSE INTERESTS INVENTORY (I-3)");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


        //Column headers
        $group[] = $this->form->createElement("static", "list_interest");
        $group[] = $this->form->createElement("static", "age_onset");
        $group[] = $this->form->createElement("static", "intensity");
        $group[] = $this->form->createElement("static", "peculiarity");
        $group[] = $this->form->createElement("static", "persistent");

        $this->form->addGroup($group, null, "Disorder", $this->_GUIDelimiter, FALSE);
        unset($group);

        foreach($questionArray as $field=>$label) {
        $group[] = $this->form->createElement("text", "{$field}_who_other", null);
        $group[] = $this->form->createElement("select", "{$field}_who_other_status", null, array(null=>"", "not_answered"=>"Not Answered")); 
        $group[] = $this->form->createElement("select", $field, $label, array("1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26");
        $group[] = $this->form->createElement("select", $field, $label, array("1", "2", "3", "4", "5");
        $group[] = $this->form->createElement("select", $field, $label, array("1", "2", "3", "4", "5");
        $group[] = $this->form->createElement("select", $field, $label, array(NULL=>"", "Yes", "No", "Not applicable to candidate", "Not Answered"));
        $this->form->addGroup($group, "{$field}_group", $label, $this->_GUIDelimiter, FALSE);
	}
}
