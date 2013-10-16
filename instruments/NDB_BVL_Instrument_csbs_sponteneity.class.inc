<?php

class NDB_BVL_Instrument_csbs_sponteneity extends NDB_BVL_Instrument
{

/*
INSERT INTO test_names VALUES('', 'csbs_sponteneity', 'CSBS Sponeneity Coding Sheet', 0, 1, NULL);

INSERT INTO test_battery VALUES ('', 'csbs_sponteneity', '0', '420', 'Y', 'Visit', '1', NULL);

INSERT INTO instrument_subtests VALUES('', 'csbs_sponteneity', 'csbs_sponteneity_page1', 'Child Approach / Structured Communication Activities', 1);
INSERT INTO instrument_subtests VALUES('', 'csbs_sponteneity', 'csbs_sponteneity_page2', 'Free Play', 2);
*/

	var $scoreLabels = array(
        "free_total_NC",
        "free_response_to_prompt",
        "free_SC_yes",
        "free_non_prompted_yes",
    	"free_average_prompt",
        "free_total_prompts",
        "structured_total_NC",
        "structured_response_to_prompt",
        "structured_SC_yes",
        "structured_non_prompted_yes",
        "structured_average_prompt",
 	"structured_total_prompts",
	"overall_total_prompts",
	"overall_average_prompts",
	"overall_yes_NP",
	"overall_yes_SC", 
	"overall_NC"
	);


	var $yesNo = array(null=>"", "yes"=>"Yes", "no"=>"No", "not_answered"=>"Not Answered");

	var $deteOptions = array(NULL=>"", "2007"=>"2007", "2008"=>"2008", "2009"=>"2009", "2010"=>"2010", "2011"=>"2011", "2012"=>"2012");

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
        $this->testName = "csbs_sponteneity";           // test_names.Test_name
        $this->table = 'csbs_sponteneity';              // name of database table corresponding to instrument
        // data keyed by commentID
        $this->commentID = $commentID;
        
        //The array of dates/timestamps to convert to database dates/timestamps
        //Any HTML_Quickform date elements must be listed here
        $this->dateTimeFields=array("Date_taken", "date_coded");
            
        //The array of selects with multiple answers allowed
        //Any HTML_Quickform multiple selects must be listed here
        $this->_selectMultipleElements = array();

        // required fields for data entry completion status
        $this->_requiredElements = array('Examiner', "q_1_orientation", "prompt_1_a");

        //Column headers
        $this->localDefaults = array_merge($this->localDefaults, array("h_1"=>"1", "h_2"=>"2", "h_3"=>"3", "h_4"=>"4", "h_5"=>"5", "h_6"=>"6", "raw_score"=>"Raw Score",
                                            "wind_up_toy"=>"Wind-up toy", "balloon"=>"Balloon", "bubbles"=>"Bubbles", "jar"=>"Jar",
                                            "books"=>"Books" . $this->indent . $this->indent . $this->indent . $this->indent . $this->indent . $this->indent . $this->indent,
                                            "play"=>"Play" . $this->indent . $this->indent . $this->indent . $this->indent . $this->indent . $this->indent . $this->indent,
                                            "object_names"=>"object names:", "person_names"=>"person names:", "body_parts"=>"body parts:", "subscale"=>"Subscale", "raw_weighted"=>"Weighted Raw Score", 						    "standard_score"=>"Standard Score","percentile_rank"=>"Percentile Rank", "prompt_header"=>"Prompt level", "response_header"=>"Quality of response", "prompt_header2"=>"Type of prompt", "amount_header"=>"Amount of prompting", "other_header"=>"Other - specify"));


    /**
     * Array of column names to be ignored by the double data entry conflict detector.
     */
        $this->_doubleDataEntryDiffIgnoreColumns = array('CommentID', 'UserID', 'Testdate', 'Window_Difference',
                'Candidate_Age',
                'relationship_to_child',
                'relationship_to_child_status',
                'comments',
                'comments_status',
                'q_19_sequence_action_schemes_6',
                'free_total_NC',
                'free_response_to_prompt',
                'free_SC_yes',
                'free_non_prompted_yes',
                'free_average_prompt',
                'free_total_prompts',
                'structured_total_NC',
                'structured_response_to_prompt',
                'structured_SC_yes',
                'structured_non_prompted_yes',
                'structured_average_prompt',
                'structured_total_prompts',
                'overall_total_prompts',
                'overall_average_prompts',
                'overall_yes_NP',
                'overall_yes_SC',
                'overall_NC');

             //date formats

                $config =& NDB_Config::singleton();
                $this->dateOptions = array(
                'language' => 'en',      
                'format'   => 'YMd',
                'minYear'  => $config->getSetting('startYear'), //allows for proband siblings up to 20 years older than candidate
                'maxYear'  => $config->getSetting('endYear'),
                'addEmptyOption' => true,
                'emptyOptionValue' => null
                );



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
        if(preg_match("/csbs_sponteneity(_page[0-9]+)/",$this->page,$matches)){
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
        //display test name
        $this->form->addElement('header', null, "Communication and Symbolic Behaviour Scales - Sponteneity Coding Sheet");
        $this->form->addElement('static', null, "<br />");
        $this->form->addElement('static', null, "<br />");

        // automatically adds examiner & date of administration
        $this->form->addElement('static', null, "The following two fields refer to Date and Examiner for the CSBS");
        $this->_addMetadataFields();
	$this->form->addElement("static", null, "<br/>");		

	$this->form->addElement('static', null, "The following two fields refer to Date and Coder for the CSBS Sponteneity");
	$this->addDateElement("date_coded", "Date of Coding:");
	$this->addTextElement("coder", "Coder:"); 

	$this->form->addElement("static", null, "<br/>");		

        $this->form->addElement('static', "overall_total_prompts", "Total prompts:");
        $this->form->addElement('static', "overall_average_prompts", "Average prompt level:");
        $this->form->addElement('static', "overall_yes_NP", "Total # of 'yes' for non-prompted communication:");
        $this->form->addElement('static', "overall_yes_SC", "Total # of 'yes' for spontaneous communication:");
        $this->form->addElement('static', "overall_NC", "Total # of 'NC':");

	$this->form->addElement("static", null, "<br/>");		
    }

    function _page1(){
        $this->form->addElement('header', null, "<br/>Child Approach");
        $this->form->addElement("static", null, "<br/>");		

        $this->form->addElement("select", "q_1_orientation", "1. Orientation to Examiner", array(null=>"", "1_constantly_avoids"=>"1. Constantly avoids", "2_typically_avoids"=>"2. Typically avoids", "3_occasionaly_avoids"=>"3. Occasionally avoids", "4_moderately_responds"=>"4. Moderately responds", "5_high_responsiveness"=>"5. High responsiveness",  "not_answered"=>"Not Answered"));

        $this->form->addElement("select", "q_2_duration_attention", "2. Duration Attention to Task", array(null=>"", "1_never"=>"1. Never attends", "2_generally_inattentive"=>"2. Generally inattentive", "3_somewhat"=>"3. Attends as often as does not", "4_stays_with"=>"4. \"Stays with\" activities", "5_attends"=>"5. Constantly attends",  "not_answered"=>"Not Answered"));

        $this->form->addElement("select", "q_2_capturing_interest", "3. Capturing Initial Interest", array(null=>"", "1_not_attend"=>"1. Does not attend", "2_uninterested"=>"2. Typically un-interested", "3_somewhat"=>"3. Interested in half of activities", "4_typically_interested"=>"4. Typically interested", "5_attends"=>"5. Almost always attends",  "not_answered"=>"Not Answered"));
        
        $this->addTextAreaElement("comments", "Comments:", array("comments{@}=={@}NEVER_REQUIRED"), "comments_group");    
	$this->form->addElement("static", null, "<br/>");		

        //Emotion and Eye Gaze
	$this->form->addElement("header", null, "Structured Communication Activities");
	$this->form->addElement("static", null, "<br/>");		


	$promptLevel = array(null=>"", "0"=>"0", "1"=>"1", "2"=>"2", "3"=>"3", "8_not_codeable"=>"8 Not Codeable", "no_communication"=>"No Communication", "not_administered"=>"Not Administered");
	$qualityResponse = array(null=>"", "dop"=>"DOP", "doa"=>"DOA", "fda"=>"FDA", "mon"=>"MON", "fnc"=>"FNC", "rp"=>"RP", "wp"=>"WP", "nr"=>"NR", "other"=>"Other", "no_communication"=>"No Communication");

	$headers = array("", "1. Wind up Toy (& bag)", "2. Balloon (& bag)", "3. Bubbles (& bag)", "4. Jar (& bag)");

	

	for ($i = 1; $i <5; $i++)
	{

		$this->form->addElement("static", null, "<b>$headers[$i]</b>");

		for ($j = 1; $j<3; $j++)
		{
	
        		$group[] =&$this->form->createElement("static", "prompt_header", "Prompt Level");
        		$group[] =&$this->form->createElement("static", "response_header", "Quality of Response");
        		$group[] =&$this->form->createElement("static", "other_header", "Other - specify");
        		$this->form->addGroup($group, "wind_up_headers", "", $this->_GUIDelimiter, false);
        		unset($group);

        		$group[] = &$this->form->createElement("select", "wind_up_ph{$j}_$i", null, $promptLevel);
        		$group[] = &$this->form->createElement("select", "wind_up_ph{$j}_response_$i", null, $qualityResponse);
			$group[] = &$this->form->createElement("text", "wind_up_ph{$j}_other_$i", null);

			if ($j == 1)	
        			$this->form->addGroup($group, "PH$j", "a. PH $j", $this->_GUIDelimiter, false);
			else	
        			$this->form->addGroup($group, "PH$j", "b. PH $j", $this->_GUIDelimiter, false);

        		unset($group);
			$this->XINRegisterRule("wind_up_ph{$j}_$i", array("wind_up_ph{$j}_$i{@}=={@}"), "Prompt level and quality are both required", "PH$j");
			$this->XINRegisterRule("wind_up_ph{$j}_response_$i", array("wind_up_ph{$j}_response_$i{@}=={@}"), "Prompt level and quality are both required", "PH$j");
			$this->XINRegisterRule("wind_up_ph{$j}_other_$i", array("wind_up_ph{$j}_other_$i{@}=={@}NEVER_REQUIRED"), "PH$j");

                	$this->addTextAreaElement("ph{$j}_{$i}_notes", $this->indent . "Notes:");
                        $this->XINRegisterRule("ph{$j}_{$i}_notes", array("ph{$j}_{$i}_notes{@}=={@}NEVER_REQUIRED"), "ph{$j}_{$i}_notes_group");
       		}
        	

		$this->form->addElement("select", "wind_up_additional_communication_$i", "c. Additional non-prompted communication", $this->yesNo);
        	$this->form->addElement("select", "wind_up_spontaneous_communication_$i", "d. Spontaneous communication not presented by clinician", $this->yesNo);
		$this->form->addElement("static", null, "<br/>");		
		$this->form->addElement("static", null, "<br/>");		
 	}

                $this->form->addElement("text", "structured_play_score", "Structured Play Score: ");
                $this->form->addElement("static", "structured_total_prompts", "Total prompts: ");
                $this->form->addElement("static", "structured_average_prompt", "Average prompt level: ");
                $this->form->addElement("static", "structured_non_prompted_yes", "Total # of 'yes' for non-prompted communication: ");
                $this->form->addElement("static", "structured_SC_yes", "Total # of 'yes' for spontaneous communication: ");
                $this->form->addElement("static", "structured_response_to_prompt", "Response to prompts: ");
		$this->form->addElement("static", "structured_total_NC", "Total # of 'NC': ");

		$this->form->addElement("static", null, "<br/>");		
		$this->form->addElement("static", null, "<br/>");		

    }
    
    function _page2() {
	
        $this->form->addElement("header", null, "Free Play Activities");

        $promptType = array(null=>"", "verbal"=>"V", "gesture"=>"G", "verbal_and_gesture"=>"V+G", "independent"=>"I", "nc"=>"No Communication");
        $promptAmount = array(null=>"", "0_initiates_prior_prompt"=>"0", "1"=>"1", "2"=>"2", "3"=>"3", "4"=>"4", "5"=>"5", "nc"=>"No Communication");

        $headers = array("", "1. Books", "2. Play");
	$options = array("a", "b", "c");

        for ($i = 1; $i <3; $i++)
        {
                $this->form->addElement("static", null, "<b>$headers[$i]</b>");

		for ($j = 0; $j < 3; $j++)
		{
                	$group[] =&$this->form->createElement("static", "prompt_header2", "Prompt Level");
                	$group[] =&$this->form->createElement("static", "amount_header", "Quality of Response");
                	$this->form->addGroup($group, "communication_headers_{$i}_$options[$j]", "", $this->_GUIDelimiter, false);
                	unset($group);

                	$group[] = &$this->form->createElement("select", "prompt_{$i}_$options[$j]", null, $promptType);
                	$group[] = &$this->form->createElement("select", "prompt_amount_{$i}_$options[$j]", null, $promptAmount);
                	$this->form->addGroup($group, null, "$options[$j]. ", $this->_GUIDelimiter, false);
                	$this->addTextAreaElement("prompt{$i}_$options[$j]_notes", $this->indent . "Notes:", array("prompt{$i}_$options[$j]_notes{@}=={@}NEVER_REQUIRED"));
        		unset($group);
                	unset($group);
		}

                $this->form->addElement("select", "free_play_additional_communication_$i", "d. Additional non-prompted communication", $this->yesNo);
                $this->form->addElement("select", "free_play_spontaneous_communication_$i", "e. Spontaneous communication not presented by clinician", $this->yesNo);
                $this->form->addElement("static", null, "<br/>");
                $this->form->addElement("static", null, "<br/>");
        }



//	$this->form->addElement("select", "validity_score", "<b>3. Validity Score</b>", array("null"=>"", "0_valid"=>"0 Valid", "1_questionable"=>"1 Questionable Validity", "2_invalid"=>"2 Invalid"));
        $this->addTextAreaElement("validity_notes", "Notes on validity score:", array("validity_notes{@}=={@}NEVER_REQUIRED"));
//	$this->XINRegisterRule("validity_notes", array("validity_score{@}=={@}1_questionable|2_invalid"), "Required if validity score is 1 or 2", "validity_notes_group");
        $this->form->addElement("static", null, "<br/>");


        $this->form->addElement("text", "free_play_score", "Free Play Score: ");
        $this->form->addElement("static", "free_total_prompts", "Total prompts: ");
        $this->form->addElement("static", "free_average_prompt", "Average prompt level: ");
        $this->form->addElement("static", "free_non_prompted_yes", "Total # of 'yes' for non-prompted communication: ");
        $this->form->addElement("static", "free_SC_yes", "Total # of 'yes' for spontaneous communication: ");
        $this->form->addElement("static", "free_total_NC", "Total # of 'NC': ");                

	$this->form->addElement("static", null, "<br/>");		
	$this->form->addElement("static", null, "<br/>");		

    }


       function countNC($record)
       {
            	$NC = 0;
            	foreach($record as $field=>$value){
			if ($value == 'no_communication' || $value == 'nc')
				$NC++;
		}
		return $NC;
        }

	function count_strucPlay($record)
	{
		$count = 0;
		foreach($record as $field=>$value)
		{
			if ($value == 1|2|3)
				$count += $value;

		}
	return $count;
	}

	function countResponse($record)
	{
		$count = 0;
		foreach($record as $field=>$value)
		{
			if ($value == 'dop')
				$count+=2;
			elseif ($value == 'doa')
				$count+=3;
			elseif($value == 'rp'||$value == 'wp'||$value == 'nr')
				$count+=1;
		}
	return $count;
	}

        function count_yes($record)
	{
                $yeses = 0;
                foreach($record as $field=>$value)
		{                        
			if ($value == 'yes')
                                $yeses++;
                }
    	return ($yeses);
        }



   	function countPrompts($record) 
	{
		$prompts = 0;

        	foreach($record as $field=>$value) {
	          /*  if($value == 'verbal' || $value == 'gesture') 
        	        $prompts++; 
        
		elseif($value == 'verbal_and_gesture')
			$prompts+=2;
*/
		if($value >= 1 && $value <= 5)
			$prompts+=$value;
		}
        		return $prompts;
	}


	function score()
	{

//       if($this->_determineDataEntryCompletionStatus() == "Incomplete") 
  //              return;


        //null scores
                $this->_nullScores($this->scoreLabels);
                
        //get the saved scores
        $db =& Database::singleton();
        if(PEAR::isError($db)) {
                        return PEAR::raiseError ("Could not connect to database".$db->getMessage());
        }


  	$query_structured_prompts = "SELECT wind_up_ph1_1, wind_up_ph2_1, wind_up_ph1_2, wind_up_ph2_2, wind_up_ph1_3, wind_up_ph2_3, wind_up_ph1_4, wind_up_ph2_4 FROM $this->table WHERE CommentID = '$this->commentID'";
        $record_structured_prompts = array();
        $db->selectRow($query_structured_prompts, $record_structured_prompts);
        if (PEAR::isError($record_structured_prompts)) {
                return PEAR::raiseError("Could not retrieve scores: " . $record->getMessage());
	}

  	$query_structured_response = "SELECT wind_up_ph1_response_1, wind_up_ph2_response_1, wind_up_ph1_response_2, wind_up_ph2_response_2, wind_up_ph1_response_3, wind_up_ph2_response_3, wind_up_ph1_response_4, wind_up_ph2_response_4 FROM $this->table WHERE CommentID = '$this->commentID'";
        $record_structured_response = array();
        $db->selectRow($query_structured_response, $record_structured_response);
        if (PEAR::isError($record_structured_response)) {
                return PEAR::raiseError("Could not retrieve scores: " . $record->getMessage());
	}

        $querySC_yes = "SELECT wind_up_spontaneous_communication_1, wind_up_spontaneous_communication_2, wind_up_spontaneous_communication_3, wind_up_spontaneous_communication_4 FROM $this->table WHERE CommentID = '$this->commentID'";
        $recordSC_yes = array();
        $db->selectRow($querySC_yes, $recordSC_yes);
        if (PEAR::isError($recordSC_yes)) {
                return PEAR::raiseError("Could not retrieve scores: " . $record->getMessage());
        }

        $queryNP_yes = "SELECT wind_up_additional_communication_1, wind_up_additional_communication_2, wind_up_additional_communication_3, wind_up_additional_communication_4 FROM $this->table WHERE CommentID = '$this->commentID'"; 
        $recordNP_yes = array();
        $db->selectRow($queryNP_yes, $recordNP_yes);
        if (PEAR::isError($recordNP_yes)) {
                return PEAR::raiseError("Could not retrieve scores: " . $record->getMessage());
        }

	$query_numPrompts = "SELECT prompt_1_a, prompt_1_b, prompt_1_c, prompt_2_a, prompt_2_b, prompt_2_c, prompt_amount_1_a, prompt_amount_1_b, prompt_amount_1_c, prompt_amount_2_a, prompt_amount_2_b, prompt_amount_2_c FROM $this->table WHERE CommentID = '$this->commentID'";
	$record_numPrompts = array();
	$db->selectRow($query_numPrompts, $record_numPrompts);
        if (PEAR::isError($record_numPrompts)) {
                return PEAR::raiseError("Could not retrieve scores: " . $record->getMessage());
        }

	$query_typePrompts = "SELECT prompt_1_a, prompt_1_b, prompt_1_c, prompt_2_a, prompt_2_b, prompt_2_c FROM $this->table WHERE CommentID = '$this->commentID'";
	$record_typePrompts = array();
	$db->selectRow($query_typePrompts, $record_typePrompts);
        if (PEAR::isError($record_typePrompts)) {
                return PEAR::raiseError("Could not retrieve scores: " . $record->getMessage());
        }

        $querySC_yes2 = "SELECT free_play_spontaneous_communication_1, free_play_spontaneous_communication_2 FROM $this->table WHERE CommentID = '$this->commentID'";
        $recordSC_yes2 = array();
        $db->selectRow($querySC_yes2, $recordSC_yes2);
        if (PEAR::isError($recordSC_yes2)) {
        	return PEARR::raiseError("Could not retrieve scores: " . $record->getMessage());
        }

  	$queryNP_yes2 = "SELECT free_play_additional_communication_1, free_play_additional_communication_2 FROM $this->table WHERE CommentID = '$this->commentID'";
        $recordNP_yes2 = array();
        $db->selectRow($queryNP_yes2, $recordNP_yes2);
        if (PEAR::isError($recordNP_yes2)) {
                return PEAR::raiseError("Could not retrieve scores: " . $record->getMessage());
        }

//  	$structured_total = $this->count_strucPlay($record_structured_prompts); 
//  	$structured_average = number_format(($structured_total / (8 - $NC)), 2);
//      	$structured_NP_yes = $this->count_yes($recordNP_yes);
  //      $structured_SC_yes = $this->count_yes($recordSC_yes);
//      	$NC = $this->countNC($record_structured_prompts);
/*
	$free_prompts = $this->countPrompts($record_amountPrompts);
	$NC_free_amount = $this->countNC($record_amountPrompts);
	$SC_yes_free = $this->count_yes($recordSC_yes2);
    	$NP_yes_free = $this->count_yes($recordNP_yes2);
	$NC_free = $this->countNC($record_numPrompts);
*/

      	$structured_NC = $this->countNC($record_structured_prompts);
	$free_NC = $this->countNC($record_typePrompts);

        $scores["structured_total_prompts"] = $this->count_strucPlay($record_structured_prompts);
        $scores["structured_average_prompt"] = number_format(($scores["structured_total_prompts"] / (8 - $structured_NC)), 2);
        $scores["structured_response_to_prompt"] = $this->countResponse($record_structured_response);
        $scores["structured_non_prompted_yes"] = $this->count_yes($recordNP_yes); 
   	$scores["structured_SC_yes"] = $this->count_yes($recordSC_yes);
        $scores["structured_total_NC"] = $structured_NC;

 	$scores["free_total_prompts"] = $this->countPrompts($record_numPrompts);
    	$scores["free_average_prompt"] = number_format(($scores["free_total_prompts"] / (6 - $free_NC)), 2);
        $scores["free_non_prompted_yes"] = $this->count_yes($recordNP_yes2);
        $scores["free_SC_yes"] = $this->count_yes($recordSC_yes2);
        $scores["free_total_NC"] = $free_NC;

	$scores["overall_total_prompts"] = $scores["structured_total_prompts"] + $scores["free_total_prompts"];
	$scores["overall_average_prompts"] = number_format(($scores["overall_total_prompts"] / (14 - ($structured_NC + $free_NC))), 2);
	$scores["overall_yes_NP"] = $scores["structured_non_prompted_yes"] + $scores["free_non_prompted_yes"];
	$scores["overall_yes_SC"] = $scores["structured_SC_yes"] + $scores["free_SC_yes"];
	$scores["overall_NC"] = $structured_NC + $free_NC;;


        // save scores
        $resultScores = $db->update($this->table, $scores, array("CommentID"=>$this->getCommentID()));
	if($db->isError($resultScores)) {
                return PEAR::raiseError("Could not save total score: ". $resultScores->getMessage());
		}
	}
}

?>
