<?php
require_once "NDB_Reliability.class.inc";
//require_once "NDB_BVL_Instrument.class.inc";

/**
 * The forms for the tracking log menu
 * @package mri
 * @subpackage NIHPD
 */
class NDB_Reliability_aosi_reliability extends NDB_Reliability

{
    // Can be either "reliability" or "blind_coding".. this is the suffix
    // attached to the table name
    var $codingtype = "reliability";

// function _hasAccess()
//     {
//         // create user object
//         $user =& User::singleton();

//         $DB =& Database::singleton();
       
//         if(!empty($this->identifier)) {
//             $query = "SELECT psc.CenterID FROM tracking_logs, candidate, psc WHERE tracking_logs.CandID=candidate.CandID AND candidate.CenterID=psc.CenterID AND tracking_logs.Tracking_log_ID='$this->identifier'";
//             $recordCenterID = $DB->selectOne($query);
            
//             return ($user->hasPermission('tracking_logs')
//                     && ($user->hasPermission('tracking_logs_edit_all')
//                         || ($user->getData('CenterID') == $recordCenterID)));

//         } else {
//             return ($user->hasPermission('tracking_logs'));
//         }
//     }

    function _getDefaults()
    {
        $DB =& Database::singleton();
               
        $initial_table = preg_replace('/_reliability/', '', $this->name);

        //print_r($this->identifier);
       
            
            // set the aosi_reliability values 
            $DB->selectRow("SELECT * FROM aosi_$this->codingtype WHERE CommentID = '$this->identifier' AND reliability_center_id = '$this->reliability_center_id'", $row);
     
            // Set the defaults
            // print_r($row['CommentID']);
          if (!empty($row)) { 
            $sites = array(1 => 'DCC', 2 => 'SEA', 3 => 'PHI', 4 => 'STL', 5 => 'UNC');
            $defaults['reliability_center'] = $sites[$this->reliability_center_id];
            $defaults['Examiner'] = $row['Examiner'];
            
            foreach($row as $field=>$value) {
               $defaults[$field] = $value;
            }

            // Set the date
            //  $date = explode('-', $row['aMRI_date']);
            //  $defaults['aMRI_date']['Y'] = $date[0];
            //  $defaults['aMRI_date']['M'] = $date[1];
            //  $defaults['aMRI_date']['d'] = $date[2];

        }

        $defaults['CommentID'] = "<a href=\"main.php?test_name=reliability_breakdown&instrument=$initial_table&CommentID=$row[CommentID]\">" . $row['CommentID'] . "</a>";
        return $defaults;
    }

   
    function score(){

        //holds raw question values
        $candidate_record = array();
        $reliability_record = array();
       
        //holds calculated
        $db =& Database::singleton();

        // null scores
        //$this->_nullScores();
       
        //Get values from both tables of aosi (reliability and original)

        $db->selectRow("SELECT * FROM aosi WHERE CommentID='{$this->identifier}'", $candidate_record);
        
        $db->selectRow("SELECT * FROM aosi_$this->codingtype WHERE CommentID='{$this->identifier}' AND reliability_center_id = '$this->reliability_center_id'", $reliability_record);
                   
         $denominator = 0;
         $reliability_count_raw = 0;
         $denominator_scored = 0;
         $reliability_count_scored = 0;
         $questions_checked = array();
        
     
          $scored_questions = array('1_visual_tracking_score', "2_disengagement_of_attention_score", "3_orients_to_name_score", "4_differential_response_to_facial_emotion_score",
                              "5_anticipatory_response_score", "6_imitation_of_actions_score", "7_social_babbling", "8_eye_contact", "9_reciprocal_social_smile",
                              "10_coordination_of_eye_gaze_and_action", "11_reactivity", "14_social_interest", "15_transitions", "16_motor_control_and_behaviour",
                              "17_atypical_motor", "18_atypical_sensory", "19_engagement_of_attention", "20_insistence_on_particular_objects", 
                              "21_social_referencing");
           
           foreach($scored_questions as $key){
              $denominator++;
              if($candidate_record['q' . $key] != $reliability_record[$key]){
                 $reliability_count_raw++;
              }
           }

            // Score the reliability
            print $denominator;
            print $reliability_count_raw;
            $reliability['Reliability_score']= (($denominator-$reliability_count_raw)/$denominator*100);
           
          
        
         // print_r($this->identifier);
      
        // Do the update here for the relibaility scores - saving the scores
		$result = $db->update("aosi_$this->codingtype", $reliability, array("CommentID"=>$this->identifier, "reliability_center_id" => $this->reliability_center_id));
		$result = $db->update($this->codingtype, $reliability, array("CommentID"=>$this->identifier, "Instrument" => 'aosi', "reliability_center_id" => $this->reliability_center_id));
    
/*	 // Update the main relibaility table with the overall reliability score 
                $result1 = $db->update("reliability", $reliability['reliability_score'], array("CommentID"=>$this->identifier));
*/

    } // end function score
           
    function _nullScores()
    {
        $db=& Database::singleton();
        
        // set the scores to NULL
        foreach ($this->scores as $val) {
            $scores[$val]=null;
        }

        // update the scores
        $success = $db->update("aosi_$this->codingtype",$scores,array("CommentID"=>$this->identifier, "reliability_center_id"=>$this->reliability_center_id));
        return;
    }    


    function aosi_reliability()
    {
       $this->_addMetadataFields();
       if($_REQUEST['blind'] == 1) {
           $this->codingtype = "blind_coding";
           $this->tpl_data['blind'] = 1;
       }
       $this->form->addElement("static", "reliability_center", "Site of Reliability Test:");
       
         //Scoring header
         $this->form->addElement('header', 'instrument_title', "Scoring:");
         $this->form->addElement("static", "reliability_score", "Reliability Score (%):");
          $this->form->addElement("static", "CommentID", "CommentID:");

         $GoldStandardArray = array(""=>NULL, "Gold_standard"=>"Gold standard", "Initial_entry"=>"Initial Entry");
         //$this->form->addElement("select", "Gold_standard", "Compare against:", $GoldStandardArray);
         //$this->form->addRule('Gold_standard', 'Gold standard is required', 'required');
         
         $this->form->addElement('header', 'instrument_title', "AOSI");


          $this->form->addElement('select', "examiner_location", "(Circle One)", array(null=>'', 'examiner'=>'Examiner', "in_room_observer"=>"In-Room Observer", "behind_mirror"=>"Behind Mirror", "videotape"=>"Videotape", "not_answered"=>"Not Answered"));
          $this->form->addElement('static', "total_score_1_18", "Total Score (items 1-18)");
          $this->form->addELement('static', "number_of_markers", "Number of Markers (non-zero items, 1-18)");
          
          ///PAGE 1

          $this->form->addElement("header", null, "Item Administration");

            //Question 1
            $this->form->addElement("static", null, "1. Visual Tracking");
            for($press = 1; $press <=3; $press++) {
                $this->form->addElement('select', "1_visual_tracking_press_$press", "Press #$press", array(null=>"", 0=>"0 = Pass", 1=>"1 = Delayed/Interupted", 2=>"2 = Partial or No Tracking", 8=>"8 = Not Applicable", "not_answered"=>"Not Answered"));
            }

            $this->form->addElement("select", "1_visual_tracking_score_override", "Override score calculation (optional):", array(null=>'', 0=>"0 = Smoothly tracks", 1=>"1 = Delayed or interrupted", 2=>"2 = Partial", 8=>"8 = Not applicable"));
            $this->XINRegisterRule("1_visual_tracking_score_override", array("1_visual_tracking_score{@}=={@}purely_optional_question"));

            $this->form->addElement("static", "1_visual_tracking_score", "Score:");

            $this->addTextAreaElement("1_visual_tracking_notes", "Notes:");

            //Question 2
            $this->form->addElement("static", null, "2. Disengagement of Attention");
            for($press = 1; $press <= 3; $press++) {
                $this->form->addElement('select', "2_disengagement_of_attention_press_$press", "Press #$press", array(null=>"", 0=>"0 = Pass (<1 sec)", 1=>"1 = Delayed (1-2 sec)", 2=>"2 = Stuck (>2 sec)", 8=>"8 = Not Applicable", "not_answered"=>"Not Answered"));
            }

            $this->form->addElement("select", "2_disengagement_of_attention_score_override", "Override score calculation (optional):", array(null=>'', 0=>"0 = Immediately moves attention", 1=>"1 = Delayed movement of attention", 2=>"2 = Fails to move attention", 8=>"8 = Not applicable"));
            $this->XINRegisterRule("2_disengagement_of_attention_score_override", array("2_disengagement_of_attention_score{@}=={@})purely_optional_question"));

            $this->form->addElement("static", "2_disengagement_of_attention_score", "Score:");
            $this->addTextAreaElement("2_disengagement_of_attention_notes", "Notes:");

            $this->addTextAreaElement("free_play_period_1_notes", "Free Play Period 1 Notes:");

            //Question 3
            $this->form->addElement("static", null, "3. Orients to Name");
            for($press = 1; $press <= 3; $press++) {
                for($trial = 1; $trial <= 2; $trial++) {
                    $parents = $press != 3 ? "" : " (parents)";
                $this->form->addElement('select', "3_orients_to_name_press_{$press}_trial_{$trial}", "Press #$press, Trial #$trial $parents", array(null=>"", "orients_with_eye_contact"=>"Orients with eye contact", "orients_without_eye_contact"=>"Orients without eye contact", "fail_to_orient"=>"Fail to orient", "not_applicable"=>"Not Applicable", "not_answered"=>"Not Answered"));
                }
            }
            $this->form->addElement("select", "3_orients_to_name_score_override", "Override score calculation (optional):", array(null=>'', 0=>"0 = Orients", 1=>"1 = Inconsistent orienting", 2=>"2 = Does not orient", 8=>"8 = Not applicable"));
            $this->XINRegisterRule("3_orients_to_name_score_override", array("3_orients_to_name_score{@}=={@})purely_optional_question"));

            $this->form->addElement("static", "3_orients_to_name_score", "Score:");
            $this->addTextAreaElement("3_orients_to_name_notes", "Notes:");

            //Question 4
            $this->form->addElement("static", null, "4. Differential response to facial emotion");
            $this->form->addElement('select', "4_differential_response_to_facial_emotion", "Score: ", array(null=>"", 0=>"0 = Clear change", 1=>"1 = Questionable change", 2=>"2 = Does not show change", 8=>"8 = Not Applicable", "not_answered"=>"Not Answered"));
            $this->form->addElement("static", "4_differential_response_to_facial_emotion_score", "Score:");
            $this->addTextAreaElement("4_differential_response_to_facial_emotion_notes", "Notes:");

            //Question 5
            $this->form->addElement("static", null, "5. Anticipatory Response");
            $this->form->addElement("select", "5_anticipatory_response", "Score: ", array(null=>"", 0=>"0 = Clear anticipatory response", 1=>"1 = Subtle/Questionable response", 2=>"2 = Only during game or routine", 3=>"3 = Does not show response", 8=>"8 = Not Applicable", "not_answered"=>"Not Answered"));
            $this->form->addElement("static", "5_anticipatory_response_score", "Score:");
            $this->addTextAreaElement("5_anticipatory_response_notes", "Notes:");

            //Question 6
            $this->form->addElement("static", null, "6. Imitation of Actions");
            for($activity = 1; $activity <= 3; $activity++) {
                $group[] = $this->form->createElement("text", "6_imitation_of_actions_activity_{$activity}", null);
                for($attempt = 1; $attempt <= 3; $attempt++) {
                    $group[] = $this->form->createElement('select', "6_imitation_of_actions_act_{$activity}_att_{$attempt}", "", array(null=>"", 0=>"0 = Clear imitation", 1=>"1 = Equivocal imitation", 2=>"2 = Does not imitate", 8=>"8 = Not Applicable", "not_answered"=>"Not Answered"));
                    $this->XINRegisterRule("6_imitation_of_actions_act_{$activity}_att_{$attempt}", array("6_imitation_of_actions_act_{$activity}_att_{$attempt}{@}=={@}"), "An outcome is required.", "6_imitation_of_actions_activity_{$activity}_group");
                }
                $this->form->addGroup($group, "6_imitation_of_actions_activity_{$activity}_group", "Activity $activity", null, false);
                unset($group);
                $this->XINRegisterRule("6_imitation_of_actions_activity_{$activity}", array("6_imitation_of_actions_activity_{$activity}{@}=={@}"), "An activity name is required.", "6_imitation_of_actions_activity_{$activity}_group");
            }
            $this->form->addElement("select", "6_imitation_of_actions_score_override", "Override score calculation (optional):", array(null=>'', 0=>"0 = Clear imitation", 1=>"1 = Equivocal imitation", 2=>"2 = Does not imitate", 8=>"8 = Not applicable"));
            $this->XINRegisterRule("6_imitation_of_actions_score_override", array("6_imitation_of_actions_score{@}=={@})purely_optional_question"));

            $this->form->addElement("static", "6_imitation_of_actions_score", "Score:");
            $this->addTextAreaElement("6_imitation_of_actions_notes", "Notes: ");

            $this->addTextAreaElement("free_play_period_2_notes", "Free Play Period 2 Notes:");

        //PAGE 2
        $this->form->addElement("header", null, "General Observations");

          //array of questions
          $questions = array("7_social_babbling"=>"7. Social babbling",
                              "8_eye_contact"=>"8. Eye contact",
                              "9_reciprocal_social_smile"=>"9.Reciprocal social smile",
                              "10_coordination_of_eye_gaze_and_action"=>"10. Coordination of eye gaze and action",
                              "11_reactivity"=>"11. Reactivity",
                              "14_social_interest"=>"14. Social interest and shared affect",
                              "15_transitions"=>"15. Transitions",
                              "16_motor_control_and_behaviour"=>"16. Motor control and behaviour",
                              "17_atypical_motor"=>"17. Atypical motor behaviours",
                              "18_atypical_sensory"=>"18. Atypical sensory behaviours",
                              "19_engagement_of_attention"=>"19. Engagement of attention",
                              "20_insistence_on_particular_objects"=>"20. Insistence on having or playing with particular objects",
                              "21_social_referencing"=>"21. Social Referencing");
          //answer arrays
          $zeroOneTwoThree = array(null=>"", 0=>"0", 1=>"1", 2=>"2", 3=>"3", 8=>"8 = Not Applicable", "not_answered"=>"Not Answered");
          $zeroTwo = array(null=>"", 0=>"0", 2=>"2", 8=>"8 = Not Applicable", "not_answered"=>"Not Answered");
          $zeroOneTwo = array(null=>"", 0=>"0", 1=>"1", 2=>"2", 8=>"8 = Not Applicable", "not_answered"=>"Not Answered");

          $_0123 = array("7_social_babbling",
                          "9_reciprocal_social_smile",
                          "10_coordination_of_eye_gaze_and_action",
                          "11_reactivity",
                          "14_social_interest"); 
          $_02 = array("8_eye_contact",
                          "17_atypical_motor",
                          "18_atypical_sensory");
          $_012 = array("15_transitions",
                          "16_motor_control_and_behaviour",
                          "19_engagement_of_attention",
                          "20_insistence_on_particular_objects",
                          "21_social_referencing");

          foreach($questions as $field=>$label) {
              if(in_array($field, $_0123)) {
                  $answerArray = $zeroOneTwoThree;}
              elseif(in_array($field, $_02)) {
                  $answerArray = $zeroTwo;}
              else $answerArray = $zeroOneTwo;
              $this->form->addElement("select", $field, $label, $answerArray);
              $this->addTextAreaElement("{$field}_notes", "Notes: ");

          }

        $this->redirect = "test_name=$this->name"; // what does this do?
        
        //------------------------------------------------------------
       
       //  //Take this out
//         // put this into aosi_reliability function
//         $renderer =& new HTML_QuickForm_Renderer_Default();
//         $renderer->setFormTemplate("<form{attributes}><table class=\"instrument\">{content}</table></form>");
//         $renderer->setElementTemplate("<tr><td class=\"lab\"><!-- BEGIN required --><span style=\"color: #ff0000\">*</span><!-- END required -->{label}</td><td class=\"ele\"><!-- BEGIN error --><span style=\"color: #ff0000\">{error}</span><br /><!-- END error -->{element}</td></tr>");
//         $renderer->setElementTemplate("<tr><td class=\"lab\"><i>{label}</i></td><td class=\"ele\">\t<i>{element}</i></td></tr>", "static");
//         $renderer->setHeaderTemplate("<tr><th colspan=\"2\"><br><b>{header}</b></th></tr>");
//         $this->form->accept($renderer);
//         $this->tpl_data['tempFormHTML'] = $renderer->toHtml();

//         // My get defaults function sets $defaults array
//         $localDefaults = $this->_getDefaults();
//         if(!is_array($localDefaults)) { $localDefaults = array(); }


//         $this->form->setDefaults($this->defaults);
//     	$this->form->applyFilter('__ALL__', 'trim');


    } // End function 

   
    
	function _addCurrentMostAbnormal($field, $label, $answerArray) { 
		$this->form->addElement("static", null, $label);
		$this->form->addElement("select", $field . "_current_code", $this->indent . "Current:", $answerArray);
		$this->form->addElement("select", $field . "_most_abnormal_code", $this->indent . "Most abnormal 4.0-5.0 years:", $answerArray);
		//$this->addLargeTextAreaElement($field . "_text");
	}

	function _addCurrentEver($field, $label, $answerArray) { 
		$this->form->addElement("static", null, $label);
		$this->form->addElement("select", $field . "_current_code", $this->indent . "Current:", $answerArray);
		$this->form->addElement("select", $field . "_ever_code", $this->indent . "Ever:", $answerArray);
		//$this->addLargeTextAreaElement($field . "_text");
	}
	
	function _cleanTo3Digits($string) {
	   return ereg_replace("[^0-9]", "", substr($string, 0, 3));
	}

 function _process($values)
    {
        $DB =& Database::singleton();

        $user =& User::singleton();
        // if(!$user->hasPermission('tracking_logs_edit_all')) {
        //    $values['Lock_record'] = 'Locked';
        // }
        
        $values['Date_taken'] = $this->_getDatabaseDate($values['Date_taken']);
        
        ////////////////////////////////
        //Set score values
        ////////////////////////////////
        
        //Question 1
        //override
        if($values["1_visual_tracking_score_override"] != null) {
            $values["1_visual_tracking_score"] = $values["1_visual_tracking_score_override"];
        } else {
        //calculate
            //8
            if($values["1_visual_tracking_press_1"] == 8 || $values["1_visual_tracking_press_2"] == 8) {      
                $values["1_visual_tracking_score"] = 8;}
            //2
            elseif($values["1_visual_tracking_press_1"] == 2 || $values["1_visual_tracking_press_2"] == 2) {
                $values["1_visual_tracking_score"] = 2;}
            //1
            elseif($values["1_visual_tracking_press_1"] == 1 || $values["1_visual_tracking_press_2"] == 1) {
                $values["1_visual_tracking_score"] = 1;}
            //0
            elseif($values["1_visual_tracking_press_1"] == 0 && $values["1_visual_tracking_press_2"] == 0) {
                $values["1_visual_tracking_score"] = 0;}
            //Wacky answers
            else {
                $values["1_visual_tracking_score"] = "Scoring Error";
            }
        }
        //Question 2
        //override
        if($values["2_disengagement_of_attention_score_override"] != null) {
            $values["2_disengagement_of_attention_score"] = $values["2_disengagement_of_attention_score_override"];
        } else {
        //calculate
            //8
            if($values["2_disengagement_of_attention_press_1"] == 8 || $values["2_disengagement_of_attention_press_2"] == 8 || $values["2_disengagement_of_attention_press_3"] == 8) {      
                $values["2_disengagement_of_attention_score"] = 8;}
            //2
            elseif($values["2_disengagement_of_attention_press_1"] == 2 || $values["2_disengagement_of_attention_press_2"] == 2 || $values["2_disengagement_of_attention_press_3"] == 2) {
                $values["2_disengagement_of_attention_score"] = 2;}
            //1 = Two 1 scores recorded
            elseif(($values["2_disengagement_of_attention_press_1"] == 1 && $values["2_disengagement_of_attention_press_2"] == 1) || ($values["2_disengagement_of_attention_press_1"] == 1 && $values["2_disengagement_of_attention_press_3"] == 1) || ($values["2_disengagement_of_attention_press_2"] == 1 && $values["2_disengagement_of_attention_press_3"] == 1)) {
                $values["2_disengagement_of_attention_score"] = 1;}
            //0 = Two 0 scores recorded
            elseif(($values["2_disengagement_of_attention_press_1"] == 0 && $values["2_disengagement_of_attention_press_2"] == 0) || ($values["2_disengagement_of_attention_press_1"] == 0 && $values["2_disengagement_of_attention_press_3"] == 0) || ($values["2_disengagement_of_attention_press_2"] == 0 && $values["2_disengagement_of_attention_press_3"] == 0)) {
                $values["2_disengagement_of_attention_score"] = 0;}
            //Wacky answers
            else {
                $values["2_disengagement_of_attention_score"] = "Scoring Error";
            }
        }

        //Question 3
        //override
        if($values["3_orients_to_name_score_override"] != null) {
            $values["3_orients_to_name_score"] = $values["3_orients_to_name_score_override"];
        } else {
        //calculate
            //2
            if($values["3_orients_to_name_press_1_trial_1"] == "fail_to_orient" && 
            $values["3_orients_to_name_press_1_trial_2"] == "fail_to_orient" && 
            $values["3_orients_to_name_press_2_trial_1"] == "fail_to_orient" && 
            $values["3_orients_to_name_press_2_trial_2"] == "fail_to_orient") {
                $values["3_orients_to_name_score"] = 2;
            }
            //0
            elseif(
            ($values["3_orients_to_name_press_1_trial_1"] == "orients_with_eye_contact" || $values["3_orients_to_name_press_1_trial_2"] == "orients_with_eye_contact") && 
            ($values["3_orients_to_name_press_2_trial_1"] == "orients_with_eye_contact" || $values["3_orients_to_name_press_2_trial_2"] == "orients_with_eye_contact") && 
            ($values["3_orients_to_name_press_1_trial_1"] == "orients_with_eye_contact" || $values["3_orients_to_name_press_2_trial_1"] == "orients_with_eye_contact")) {
                $values["3_orients_to_name_score"] = 0;
            }
            //8
            elseif($values["3_orients_to_name_press_1_trial_1"] == "not_applicable" || 
            $values["3_orients_to_name_press_1_trial_1"] == "not_answered" || 
            $values["3_orients_to_name_press_2_trial_1"] == "not_applicable" || 
            $values["3_orients_to_name_press_2_trial_1"] == "not_answered") {
                $values["3_orients_to_name_score"] = 8;
            }
            //1
            elseif(
            $values["3_orients_to_name_press_1_trial_1"] == "orients_with_eye_contact" ||
            $values["3_orients_to_name_press_1_trial_2"] == "orients_with_eye_contact" || 
            $values["3_orients_to_name_press_2_trial_1"] == "orients_with_eye_contact" || 
            $values["3_orients_to_name_press_2_trial_2"] == "orients_with_eye_contact") {
                $values["3_orients_to_name_score"] = 1;
            }
            //wacky
            else {
                $values["3_orients_to_name_score"] = "Scoring Error";
            }
        }
        //Question 4
        $values["4_differential_response_to_facial_emotion_score"] = $values["4_differential_response_to_facial_emotion"];

        //Question 5
        $values["5_anticipatory_response_score"] = $values["5_anticipatory_response"];

        //Question 6
        //override
        if($values["6_imitation_of_actions_score_override"] != null) {
            $values["6_imitation_of_actions_score"] = $values["6_imitation_of_actions_score_override"];
        } else {
        //calculate
            $values["6_imitation_of_actions_score"] = 8; //start with worst score possible
            for($activity = 1; $activity <= 3; $activity++) {
                for($attempt = 1; $attempt <= 3; $attempt++) {
                	//take the lowest/best score possible
                    $values["6_imitation_of_actions_score"] =  $values["6_imitation_of_actions_act_{$activity}_att_{$attempt}"] < $values["6_imitation_of_actions_score"] ? $values["6_imitation_of_actions_act_{$activity}_att_{$attempt}"] : $values["6_imitation_of_actions_score"]; 
                }
            }
        }
           
        $DB->selectRow("SELECT * FROM aosi_$this->codingtype WHERE CommentID = '$this->identifier' AND reliability_center_id = $this->reliability_center_id", $row);
          
          $invalid = $values['invalid'];
          $DB->update("$this->codingtype", array('invalid' => $invalid), array("CommentID"=>$this->identifier, "Instrument" => 'aosi', "reliability_center_id" => $this->reliability_center_id));
          unset($values['invalid']);
          
          if($invalid == "yes"){
            $this->form->freeze();
            $this->tpl_data['success'] = true;
            return;
          }
          
          if (empty($row)) {
            
            // insert the event
            $values['CommentID'] = $this->identifier;
            $success = $DB->insert("aosi_$this->codingtype", $values);
        } else {
            // update the event
            $success = $DB->update("aosi_$this->codingtype", $values,          
                                   array('CommentID'=>$this->identifier, "reliability_center_id"=>$this->reliability_center_id)
                                   ); 
        }
        
        $scoreResult = $this->score();
        
        $this->form->freeze();
        $this->tpl_data['success'] = true;
    }
 
 function _validate($values)
 {
     $DB =& Database::singleton();
     $query = "SELECT count(*) AS counter FROM candidate WHERE CandID='$values[CandID]' and PSCID='$values[PSCID]'";
     $recordsFound = $DB->selectOne($query);
     $errors = array();
     
     if($recordsFound < 1) {
         $errors['CandID'] = "Specified DCCID and PSCID do not exist or do not match.";
     }
     
     return $errors;
 }   
 
    function display()
    {
        if($_REQUEST['blind'] == '1') {
            $this->form->addElement('hidden', 'blind', $_REQUEST['blind']);
        }
        if(!$this->form->isFrozen()) {
            // hidden values
            $this->form->addElement('hidden', 'test_name', $this->name);
            $this->form->addElement('hidden', 'subtest', $this->page);
            $this->form->addElement('hidden', 'identifier', $this->identifier);
            $this->form->addElement('hidden', 'reliability_center_id', $this->reliability_center_id);
            $this->form->addElement('submit', 'fire_away', 'Save Data', 'class=button');
        }
        
        // get the defaults
        $localDefaults = $this->_getDefaults();
        if(!is_array($localDefaults)) { $localDefaults = array(); }
        // set the quickform object defaults
        $this->form->setDefaults(array_merge($this->defaults, $localDefaults));
        
        // trim all values
        $this->form->applyFilter('__ALL__', 'trim');
        
        // display the HTML_Quickform object
        $smarty = new Smarty_neurodb;
        
        // display the HTML_Quickform object
        return $this->form->toHTML();
        
    } // end function display
 

}
?>
