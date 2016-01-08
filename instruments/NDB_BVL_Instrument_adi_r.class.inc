<?php

require_once 'HTML/QuickForm.php';
require_once 'HTML/QuickForm/Renderer/Array.php'; 

class NDB_BVL_Instrument_adi_r extends NDB_BVL_Instrument
{
	//Commonly used level of indentation;
	var $indent = "&nbsp;&nbsp;&nbsp;&nbsp;";
	
	var $yesNoNA = array(''=>NULL, '0_no'=>"0. No", '1_yes'=>"1. Yes", 'not_answered'=>"Not answered");
	
	var $respondentAgeYears;
	
    /**
    * array of scoring fields
    */
    var $scoreCols = array("Total_A1", "Total_A2", "Total_A3", "Total_A4", "A_Total",
    						"Total_B1", "Total_B4", "Total_B2V", "Total_B3V", "BV_Total", "BNV_Total",
    						"Total_C1", "Total_C2", "Total_C3", "Total_C4", "C_Total", "D_Total",
                            "social_affect","repeat_restrict_behavior","imitation","reciprocal_interaction",
                            "2012alg_research_diag","2012alg_clinical_diag","2012alg_range_concern","summary_diagnosis");
    						
    // Holds the algorithm score conversions
    var $scores = array();

    //abstract function setup($commentID, $page);
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
        $this->dateTimeFields=array("Date_taken", 'DoB_proband'); //remove DoB_proband
            
        //The array of selects with multiple answers allowed
        //Any HTML_Quickform multiple selects must be listed here
        $this->_selectMultipleElements = array();

        // required fields for data entry completion status
        $this->_requiredElements = array('Examiner', "q_11_loss_of_language", "q_20_loss_of_skills_code", "q_30_overall_level_of_language",
        								"q_41_cur_comm_speech_current_code", "q_50_direct_gaze_current_code",
        								"q_60_init_activities_current_code", "q_67_unusual_preoccupations_current_code",
        								"q_80_gait_current_code", "q_88_visuospatial_ability_current_code");
        $this->_doubleDataEntryDiffIgnoreColumns = array_merge(array('CommentID', 'UserID', 'Testdate', 'Window_Difference', 'Candidate_Age','Data_entry_completion_status','A_total','BNV_total','BV_total','C_total','D_total'), $this->scoreCols);
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
        
        $this->_getAge();
        
        //populate default answers for questions outside of age range.
        //4-5
        $underFourDefaults = array("q_29_compreh_simple_most_abnormal"=>"8_NA",
                            "q_32_artic_pronun_current_code"=>"8_NA",
                            "q_42_point_express_inter_most_abnormal_code"=>"8_NA",
                            "q_43_nodding_most_abnormal_code"=>"8_NA",
                            "q_44_head_shaking_most_abnormal_code"=>"8_NA",
                            "q_45_conventional_instr_gests_most_abnormal_code"=>"8_NA",
                            "q_46_attent_voice_most_abnormal_code"=>"8_NA",
                            "q_47_spont_imit_most_abnormal_code"=>"8_NA",
                            "q_48_imag_play_most_abnormal_code"=>"8_NA",
                            "q_49_imag_play_peers_current_code"=>"8_NA",
                            "q_49_imag_play_peers"=>"8_NA",
                            "q_50_direct_gaze_most_abnormal_code"=>"8_NA",
                            "q_51_social_smiling_most_abnormal_code"=>"8_NA",
                            "q_52_show_direct_atten_most_abnormal_code"=>"8_NA",
                            "q_53_offer_share_most_abnormal_code"=>"8_NA",
                            "q_54_seek_share_enjoy_most_abnormal_code"=>"8_NA",
                            "q_55_offer_comf_most_abnormal_code"=>"8_NA",
                            "q_56_qual_social_overts_most_abnormal_code"=>"8_NA",
                            "q_57_range_facial_expr_most_abnormal_code"=>"8_NA",
                            "q_59_appropriat_resp_most_abnormal_code"=>"8_NA",
                            "q_60_init_activities_most_abnormal_code"=>"8_NA",
                            "q_61_imit_soc_play_most_abnormal_code"=>"8_NA",
                            "q_62_inter_children_most_abnormal_code"=>"8_NA",
                            "q_63_resp_approaches_most_abnormal_code"=>"8_NA",
                            "q_64_group_play_peers_most_abnormal_code"=>"8_NA",
                            "q_65_friendships_most_abnormal_code"=>"8_NA",
                            "q_66_soc_disinhibit_current_code"=>"8_NA",
                            "q_66_soc_disinhibit_most_abnormal_code"=>"8_NA",
                            "q_80_gait_most_abnormal_code"=>"8_NA");


        $atOlderThanFiveDefaults = array(
                            "q_32_artic_pronun_5years_code"=>"8_NA",
                            "q_41_cur_comm_speech_at5_code"=>"8_NA",
                            "q_65_friendships_current_code"=>"8_NA",
                            );
        
        $db =& Database::singleton();

        // Get the item scores
        $query = "SELECT * FROM $this->table WHERE CommentID='".$this->getCommentID()."'";
        $record=array();
        $db->selectRow($query, $record);
        
        //Fill in `Most abnormal 4.0-5.0` defaults for respondents under 4
        if($this->respondentAgeYears < 4) {
            foreach($underFourDefaults as $field=>$value) {
                //Defaults apply only to empty database fields
                if(isset($record[$field]) && $record[$field] == null) {
                    $this->localDefaults[$field] = $value;
                }
            }
        }
        //Fill in values for repondents under 5
        if($this->respondentAgeYears < 5) {
            foreach($atOlderThanFiveDefaults as $field=>$value) {
                //Defaults apply only to empty database fields
                if(!isset($record[$field]) || $record[$field] == null) {
                    $this->localDefaults[$field] = $value;
                }
            }
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
        $this->form->addElement('header', 'instrument_title', "ADI-R");
	$this->form->addElement('static', null, "<br /><br />");
        
        // automatically adds examiner & date of administration
        $this->_addMetadataFields();
        
//        $this->form->addElement("text", "informant_relation", "Informant relation to subject:");
        $this->form->addElement("select", "informant_relation", "Informant relation to subject:", array(null=>"", "0_mom"=>"0 Mom", "1_dad"=>"1 Dad", "2_other_caregiver"=>"2 Other Caregiver", "3_combination"=>"3 Combination", "4_sibling"=>"4 Sibling", "5_other"=>"5 Other", "9_missing_value"=>"9 Missing Value", "not_answered"=>"Not Answered"));
        
        $config =& NDB_Config::singleton();
        $dateOptions = array(
        'language' => 'en',
        'format'   => 'YMd',
        'minYear'  => $config->getSetting('startYear') - 20, //allows for proband siblings up to 20 years older than candidate
        'maxYear'  => $config->getSetting('endYear'),
        'addEmptyOption' => true,
        'emptyOptionValue' => null
        );

        if (preg_match("/proband/", $this->testName)) {
            $this->form->addElement('date', 'DoB_proband', 'DoB Proband', $dateOptions);
        }
        
        $this->form->addElement("header", null, "Scores based on Original Algorithm");
//        $this->form->addElement("static", null, "This scoring algorithm is currently in the testing phase.");
//        $this->form->addElement("static", null, "Please inform the DCC of any oopsy daisies.");
        $this->form->addElement("static", null, "<BR>");
        
		$scoreLabels = array("Total_A1"=>"Total A1",
							"Total_A2"=>"Total A2",
							"Total_A3"=>"Total A3",
							"Total_A4"=>"Total A4",
							"A_Total"=>"A Total (cutoff = 10)",
							"Total_B1"=>"Total B1",
							"Total_B4"=>"Total B4",
							"Total_B2V"=>"Total B2(V)",
							"Total_B3V"=>"Total B3V",
							"BV_Total"=>"B(V) Total (cutoff = 8)",
							"BNV_Total"=>"B(NV) Total (cutoff = 7)",
							"Total_C1"=>"Total C1",
							"Total_C2"=>"Total C2",
							"Total_C3"=>"Total C3",
							"Total_C4"=>"Total C4",
							"C_Total"=>"C Total (cutoff = 3)",
							"D_Total"=>"D Total (cutoff = 1)",
							"summary_diagnosis"=>"Summary Diagnosis"
                            );
		foreach ($scoreLabels as $field=>$label) {
			if(in_array($field, array("A_Total", "BV_Total", "BNV_Total", "C_Total", "D_Total")) == TRUE) {
				$label = $this->indent . $this->indent . $label;
			}
	        $this->form->addElement("static", $field, $label);
		}
		$this->form->addElement('static', null, "<br /><br />");
        $this->form->addElement("header", null, "Scores based on 2012 Algorithm");
        $this->form->addElement("static", null, "<BR>");
        $scoreLabels_2012alg = array("social_affect" => "Social Affect",
                                     "repeat_restrict_behavior" => "Repetitive & Restricted Behavior",
                                     "imitation" => "Imitation, Gestures & Play Imitation",
                                     "reciprocal_interaction" => "Reciprocal and Peer Interaction",
                                     "2012alg_research_diag"  => "Research diagnosis",
                                     "2012alg_clinical_diag"  => "Clinical diagnosis",
                                     "2012alg_range_concern" => "Ranges of Concern"
                                     );

        foreach ($scoreLabels_2012alg as $field=>$label) {
            $this->form->addElement("static", $field, $label);
        }

	   $this->form->addElement('static', null, "<br /><br />");
       $this->form->addElement("textarea", "other_comments", "Comments about Validity:", array('cols'=>25, 'rows'=>4));
       $this->XINRegisterRule("other_comments", array("{other_comments}{@}=={@}NEVER_REQUIRED"));

    }

    function _score() {
        
        $db =& Database::singleton();

        // skip scoring if proband DoB was not entered, i.e. data entry is not completed
        if(empty($this->respondentAgeYears)){
            return;
        }
        
        // null scores
        $this->_nullScores($this->scoreCols);
        // Get the item scores
        $query = "SELECT * FROM $this->table WHERE CommentID='".$this->getCommentID()."'";
        $record=array();
        $db->selectRow($query, $record);
        //convert items codes to algorithm scores
        $conversion = array(0=>0, 1=>1, 2=>2, 3=>2, 7=>0, 8=>0, 9=>0);
        foreach ($record as $field=>$code) {
            //Exceptions: Retain some values as months, not scores.
            if(!in_array($field, array("q_2_age_first_noticed_code", "q_9_first_single_words_code", "q_10_first_phrases_code", "q_87_interviewers_judgment",
                //Exceptions: Does not follow the code to algorithm score conversion
                "q_86_age_when_abnormality_first_evident"))){
            	$this->scores[$field] = substr($code, 0, 1);
            	if(is_numeric($this->scores[$field])) {
            	    $intval = intval($this->scores[$field]);
            		$this->scores[$field] = $conversion[$intval];
            	} else {
            		$this->scores[$field] = 0;  //for 'not_answered'
            	}
            }
        }
        //Clean up values stored as months (not scores) to ensure only digits remain.
        $this->scores["q_2_age_first_noticed_code"] = $this->_cleanToDigits($record["q_2_age_first_noticed_code"]);
        $this->scores["q_9_first_single_words_code"] = $this->_cleanToDigits($record["q_9_first_single_words_code"]);
		$this->scores["q_10_first_phrases_code"] = $this->_cleanToDigits($record["q_10_first_phrases_code"]);
        $this->scores["q_87_interviewers_judgment"]	= $this->_cleanToDigits($record["q_87_interviewers_judgment"]);
        $this->scores["q_86_age_when_abnormality_first_evident"]	= $this->_cleanToDigits($record["q_86_age_when_abnormality_first_evident"]);
		//Age 2 years, 0 months through 3 years, 11 months.
        if ($this->respondentAgeYears < 1.75) {
            $scoreCols["A_Total"] = "Respondent too young to score";
        //Diagnostic Algorithm, 2y -> 3y11m
        } elseif ($this->respondentAgeYears >= 1.75 && $this->respondentAgeYears < 4) {
            //Qualitative Abnormalities in Reciprocal Social Interaction
	        $scoreCols["Total_A1"] = $this->scores["q_50_direct_gaze_current_code"] + $this->scores["q_51_social_smiling_current_code"] 
									+ $this->scores["q_57_range_facial_expr_current_code"];
			$scoreCols["Total_A2"] = $this->scores["q_62_inter_children_current_code"] + $this->scores["q_63_resp_approaches_current_code"];
			$scoreCols["Total_A3"] = $this->scores["q_52_show_direct_atten_current_code"] + $this->scores["q_53_offer_share_current_code"]
									+ $this->scores["q_54_seek_share_enjoy_current_code"];
			$scoreCols["Total_A4"] = $this->scores["q_31_use_of_others_body_ever_code"] + $this->scores["q_55_offer_comf_current_code"]
									+ $this->scores["q_56_qual_social_overts_current_code"] + $this->scores["q_58_inappropriate_facial_ever_code"]
									+ $this->scores["q_59_appropriat_resp_current_code"];
			$scoreCols["A_Total"] = $scoreCols["Total_A1"] + $scoreCols["Total_A2"] + $scoreCols["Total_A3"] + $scoreCols["Total_A4"];
        
			//Qualitative Abnormalities in Communication
			$scoreCols["Total_B1"] = $this->scores["q_42_point_express_interest_current_code"] + $this->scores["q_43_nodding_current_code"]
									+ $this->scores["q_44_head_shaking_current_code"] + $this->scores["q_45_conventional_instr_gests_current_code"];
			$scoreCols["Total_B4"] = $this->scores["q_47_spont_imit_current_code"] + $this->scores["q_48_imag_play_current_code"]
									+ $this->scores["q_61_imit_soc_play_current_code"];
			if($this->scores["q_30_overall_level_of_language"] == 0) { //verbal subject
				$scoreCols["Total_B2V"] = $this->scores["q_34_social_verb_chat_current_code"] + $this->scores["q_35_recipr_convers_current_code"];
				$scoreCols["Total_B3V"] = $this->scores["q_33_stereotyped_utterances_ever_code"] + $this->scores["q_36_inappropriate_qs_ever_code"]
										+ $this->scores["q_37_prenominal_reversal_ever_code"] + $this->scores["q_38_neologisms_ever_code"];
			} else {
				$scoreCols["Total_B2V"] = "Nonverbal";
				$scoreCols["Total_B3V"] = "Nonverbal";
			}
			if($this->scores["q_30_overall_level_of_language"] == 0 ) { //verbal subject
    			$scoreCols["BV_Total"] = $scoreCols["Total_B1"] + $scoreCols["Total_B4"] + $scoreCols["Total_B2V"] + $scoreCols["Total_B3V"];
    			$scoreCols["BNV_Total"] = "Verbal";
			} else {
			    $scoreCols["BV_Total"] = "Nonverbal";
			    $scoreCols["BNV_Total"] = $scoreCols["Total_B1"] + $scoreCols["Total_B4"];
			}
				
			//Restrcited, Repetitive and Stereotyped Patterns of Behaviour
			$scoreCols["Total_C1"] = $this->scores["q_67_unusual_preoccupations_ever_code"] + $this->scores["q_68_circumscr_ints_ever_code"];
			$scoreCols["Total_C2"] = ($this->scores["q_30_overall_level_of_language"] == 0 ? $this->scores["q_39_verbal_rituals_ever_code"] : 0) 
			                         + $this->scores["q_70_compulsions_rituals_ever_code"];
			$scoreCols["Total_C3"] = max($this->scores["q_77_hands_finger_manners_ever_code"], $this->scores["q_78_oth_complex_manners_ever_code"]);
			$scoreCols["Total_C4"] = max($this->scores["q_69_repet_use_objects_ever_code"], $this->scores["q_71_unusual_sens_ints_ever_code"]);
			$scoreCols["C_Total"] = $scoreCols["Total_C1"] + $scoreCols["Total_C2"] + $scoreCols["Total_C3"] + $scoreCols["Total_C4"];
			
			//Abnormality of Development Evident at or Before 36 Months
			//See the "ADI-R Scoring Algorithm - Addendum" document for directions and details regarding this section.
			//Age Parents First Noticed
			$scoreCols["D_Total"] = 0; //initialize
			if(in_array($this->scores["q_2_age_first_noticed_code"], array('991', '992', '996'))) {
        		$scoreCols["D_Total"] += 1;
			} elseif ($this->scores["q_2_age_first_noticed_code"] < 36 && !is_null($this->scores["q_2_age_first_noticed_code"])) {
        		$scoreCols["D_Total"] += 1;
			}
			//Age of First Single Words
			if (($this->respondentAgeYears*12.0) > 24 && in_array($this->scores["q_9_first_single_words_code"], array(993, 994, 997))){
			    $scoreCols["D_Total"] += 1;
			} elseif (($this->scores["q_9_first_single_words_code"]) > 24 && $this->scores["q_9_first_single_words_code"] < 990) {
			    $scoreCols["D_Total"] += 1;
			}
			//Age of First Phrases
			if (($this->respondentAgeYears*12.0) > 33 && in_array($this->scores["q_10_first_phrases_code"], array(993, 994, 997))){
			    $scoreCols["D_Total"] += 1;
			} elseif (($this->scores["q_10_first_phrases_code"]) > 33 && $this->scores["q_10_first_phrases_code"] < 990) {
			    $scoreCols["D_Total"] += 1;
			}
            //Age When Abnormality First Evident
			if(in_array($this->scores["q_86_age_when_abnormality_first_evident"], array(3, 4))) {
			     $scoreCols["D_Total"] += 1;
			}
			//Interviewers's Judgement
			if (($this->scores["q_87_interviewers_judgment"]) < 36 && !is_null($this->scores["q_87_interviewers_judgment"])) {
			     $scoreCols["D_Total"] += 1;
			}
			
	    //Diagnostic Algorithm, 4y+
        } elseif ($this->respondentAgeYears >= 4){
            //Qualitative Abnormalities in Reciprocal Social Interaction
	        $scoreCols["Total_A1"] = $this->scores["q_50_direct_gaze_most_abnormal_code"] + $this->scores["q_51_social_smiling_most_abnormal_code"] 
									+ $this->scores["q_57_range_facial_expr_most_abnormal_code"];
			$scoreCols["Total_A2"] = $this->scores["q_49_imag_play_peers_most_abnormal_code"] + $this->scores["q_62_inter_children_most_abnormal_code"] + $this->scores["q_63_resp_approaches_most_abnormal_code"];
			$scoreCols["Total_A2"] += $this->respondentAgeYears < 10 ? $this->scores["q_64_group_play_peers_most_abnormal_code"] : $this->scores["q_65_friendships_most_abnormal_code"];
			$scoreCols["Total_A3"] = $this->scores["q_52_show_direct_atten_most_abnormal_code"] + $this->scores["q_53_offer_share_most_abnormal_code"]
									+ $this->scores["q_54_seek_share_enjoy_most_abnormal_code"];
			$scoreCols["Total_A4"] = $this->scores["q_31_use_of_others_body_ever_code"] + $this->scores["q_55_offer_comf_most_abnormal_code"]
									+ $this->scores["q_56_qual_social_overts_most_abnormal_code"] + $this->scores["q_58_inappropriate_facial_ever_code"]
									+ $this->scores["q_59_appropriat_resp_most_abnormal_code"];
			$scoreCols["A_Total"] = $scoreCols["Total_A1"] + $scoreCols["Total_A2"] + $scoreCols["Total_A3"] + $scoreCols["Total_A4"];
        
			//Qualitative Abnormalities in Communication
			$scoreCols["Total_B1"] = $this->scores["q_42_point_express_inter_most_abnormal_code"] + $this->scores["q_43_nodding_most_abnormal_code"]
									+ $this->scores["q_44_head_shaking_most_abnormal_code"] + $this->scores["q_45_conventional_instr_gests_most_abnormal_code"];
			$scoreCols["Total_B4"] = $this->scores["q_47_spont_imit_most_abnormal_code"] + $this->scores["q_48_imag_play_most_abnormal_code"]
									+ $this->scores["q_61_imit_soc_play_most_abnormal_code"];
			if($this->scores["q_30_overall_level_of_language"] == 0) { //verbal subject
				$scoreCols["Total_B2V"] = $this->scores["q_34_social_verb_chat_ever_code"] + $this->scores["q_35_recipr_convers_ever_code"];
				$scoreCols["Total_B3V"] = $this->scores["q_33_stereotyped_utterances_ever_code"] + $this->scores["q_36_inappropriate_qs_ever_code"]
										+ $this->scores["q_37_prenominal_reversal_ever_code"] + $this->scores["q_38_neologisms_ever_code"];
			} else {
				$scoreCols["Total_B2V"] = "Nonverbal";
				$scoreCols["Total_B3V"] = "Nonverbal";
			}
			if($this->scores["q_30_overall_level_of_language"] == 0 ) { //verbal subject
			    //Check what happens when integers are added to text...
    			$scoreCols["BV_Total"] = $scoreCols["Total_B1"] + $scoreCols["Total_B4"] + $scoreCols["Total_B2V"] + $scoreCols["Total_B3V"];
    			$scoreCols["BNV_Total"] = "Verbal";
			} else {
    			$scoreCols["BV_Total"] = "Nonverbal";
    			$scoreCols["BNV_Total"] = $scoreCols["Total_B1"] + $scoreCols["Total_B4"];
			}					
			//Restrcited, Repetitive and Stereotyped Patterns of Behaviour
			$scoreCols["Total_C1"] = $this->scores["q_67_unusual_preoccupations_ever_code"] + $this->scores["q_68_circumscr_ints_ever_code"];
			$scoreCols["Total_C2"] = ($this->scores["q_30_overall_level_of_language"] == 0 ? $this->scores["q_39_verbal_rituals_ever_code"] : 0) 
			                         + $this->scores["q_70_compulsions_rituals_ever_code"];
			$scoreCols["Total_C3"] = max($this->scores["q_77_hands_finger_manners_ever_code"], $this->scores["q_78_oth_complex_manners_ever_code"]);
			$scoreCols["Total_C4"] = max($this->scores["q_69_repet_use_objects_ever_code"], $this->scores["q_71_unusual_sens_ints_ever_code"]);
			$scoreCols["C_Total"] = $scoreCols["Total_C1"] + $scoreCols["Total_C2"] + $scoreCols["Total_C3"] + $scoreCols["Total_C4"];
			
			//Abnormality of Development Evident at or Before 36 Months
			//See the "ADI-R Scoring Algorithm - Addendum" document for directions and details regarding this section.
			//Age Parents First Noticed
			$scoreCols["D_Total"] = 0; //initialize
			if(in_array($this->scores["q_2_age_first_noticed_code"], array('991', '992', '996'))) {
        		$scoreCols["D_Total"] += 1;
			} elseif ($this->scores["q_2_age_first_noticed_code"] < 36 && !is_null($this->scores["q_2_age_first_noticed_code"])) {
        		$scoreCols["D_Total"] += 1;
			}
			//Age of First Single Words
			if (($this->respondentAgeYears*12) > 24 && in_array($this->scores["q_9_first_single_words_code"], array(993, 994, 997))){
			    $scoreCols["D_Total"] += 1;
			} elseif ($this->scores["q_9_first_single_words_code"] > 24 && $this->scores["q_9_first_single_words_code"] < 990) {
			    $scoreCols["D_Total"] += 1;
			}
			//Age of First Phrases
			if (($this->respondentAgeYears*12) > 33 && in_array($this->scores["q_10_first_phrases_code"], array(993, 994, 997))){
			    $scoreCols["D_Total"] += 1;
			} elseif ($this->scores["q_10_first_phrases_code"] > 33 && $this->scores["q_10_first_phrases_code"] < 990) {
			    $scoreCols["D_Total"] += 1;
			}
            //Age When Abnormality First Evident
			if(in_array($this->scores["q_86_age_when_abnormality_first_evident"], array(3, 4))) {
			     $scoreCols["D_Total"] += 1;
			}
			//Interviewers's Judgement
			if (($this->scores["q_87_interviewers_judgment"]) < 36 && !is_null($this->scores["q_87_interviewers_judgment"])) {
			     $scoreCols["D_Total"] += 1;
			}
        }
        $respondentAgeMonths = intval($this->respondentAgeYears*12);

        if($respondentAgeMonths < 12 ){
            $scoreCols["social_affect"] =" Respondent too young to score";
            $scoreCols["repeat_restrict_behavior"] =" Respondent too young to score";
            $scoreCols["imitation"] =" Respondent too young to score";
            $scoreCols["reciprocal_interaction"] ="Respondent too young to score";

        }elseif( $respondentAgeMonths > 47){
            $scoreCols["social_affect"] =" Respondent too old to score";
            $scoreCols["repeat_restrict_behavior"] =" Respondent too old to score";
            $scoreCols["imitation"] =" Respondent too old to score";
            $scoreCols["reciprocal_interaction"] ="Respondent too old to score";

        } elseif( ($respondentAgeMonths >=12 && $respondentAgeMonths <= 20 ) || 
             ($respondentAgeMonths >=21 && $respondentAgeMonths <= 47 && ($this->scores["q_30_overall_level_of_language"] == 2)) 
            ) {
           $alg_type = 1;       
           $scoreCols["social_affect"]           =  $this->scores["q_46_attent_voice_current_code"] + 
                                                    $this->scores["q_50_direct_gaze_current_code"]+ 
                                                    $this->scores["q_51_social_smiling_current_code"] + 
                                                    $this->scores["q_54_seek_share_enjoy_current_code"]+
                                                    $this->scores["q_57_range_facial_expr_current_code"] +
                                                    $this->scores["q_58_inappropriate_facial_current_code"] + 
                                                    $this->scores["q_59_appropriat_resp_current_code"] + 
                                                    $this->scores["q_62_inter_children_current_code"]+ 
                                                    $this->scores["q_63_resp_approaches_current_code"];

           $scoreCols["repeat_restrict_behavior"] = $this->scores["q_69_repet_use_objects_ever_code"]+ 
                                                    $this->scores["q_77_hands_finger_manners_ever_code"]+
                                                    $this->scores["q_78_oth_complex_manners_ever_code"]+ 
                                                    $this->scores["q_71_unusual_sens_ints_ever_code"];

           $scoreCols["imitation"]                = $this->scores["q_42_point_express_interest_current_code"]+ 
                                                    $this->scores["q_45_conventional_instr_gests_current_code"]+
                                                    $this->scores["q_47_spont_imit_current_code"]+
                                                    $this->scores["q_53_offer_share_current_code"]+
                                                    $this->scores["q_48_imag_play_current_code"] + 
                                                    $this->scores["q_52_show_direct_atten_current_code"];
            
            $scoreCols["reciprocal_interaction"] ="N/A";
        
        } elseif ($respondentAgeMonths >=21 && $respondentAgeMonths <= 47 && ($this->scores["q_30_overall_level_of_language"] == 1) ){
         $alg_type = 2;       
            $scoreCols["social_affect"]           = $this->scores["q_46_attent_voice_current_code"] + 
                                                    $this->scores["q_50_direct_gaze_current_code"]+ 
                                                    $this->scores["q_51_social_smiling_current_code"] +
                                                    $this->scores["q_54_seek_share_enjoy_current_code"]+
                                                    $this->scores["q_57_range_facial_expr_current_code"] +
                                                    $this->scores["q_58_inappropriate_facial_current_code"] +
                                                    $this->scores["q_59_appropriat_resp_current_code"] +
                                                    $this->scores["q_62_inter_children_current_code"]+
                                                    $this->scores["q_63_resp_approaches_current_code"]+ 
                                                    $this->scores["q_56_qual_social_overts_current_code"] ;

           $scoreCols["repeat_restrict_behavior"] = $this->scores["q_69_repet_use_objects_ever_code"]+
                                                    $this->scores["q_77_hands_finger_manners_ever_code"]+
                                                    $this->scores["q_78_oth_complex_manners_ever_code"]+
                                                    $this->scores["q_71_unusual_sens_ints_ever_code"]+ 
                                                    $this->scores["q_67_unusual_preoccupations_ever_code"]+
                                                    $this->scores["q_70_compulsions_rituals_ever_code"];

            $scoreCols["imitation"]               = $this->scores["q_42_point_express_interest_current_code"]+
                                                    $this->scores["q_45_conventional_instr_gests_current_code"]+
                                                    $this->scores["q_47_spont_imit_current_code"]+
                                                    $this->scores["q_53_offer_share_current_code"]+
                                                    $this->scores["q_48_imag_play_current_code"] ;

            $scoreCols["reciprocal_interaction"] ="N/A";
      
      } elseif ($respondentAgeMonths >=21 && $respondentAgeMonths <= 47 && ($this->scores["q_30_overall_level_of_language"] == 0) ){
            $alg_type = 3;       
            $scoreCols["social_affect"]           = $this->scores["q_46_attent_voice_current_code"] + 
                                                    $this->scores["q_50_direct_gaze_current_code"]+ 
                                                    $this->scores["q_43_nodding_current_code"] +
                                                    $this->scores["q_54_seek_share_enjoy_current_code"]+
                                                    $this->scores["q_57_range_facial_expr_current_code"] +
                                                    $this->scores["q_55_offer_comf_current_code"]+
                                                    $this->scores["q_42_point_express_interest_current_code"]+
                                                    $this->scores["q_52_show_direct_atten_current_code"]+
                                                    $this->scores["q_56_qual_social_overts_current_code"]+
                                                    $this->scores["q_34_social_verb_chat_current_code"]+
                                                    $this->scores["q_31_use_of_others_body_ever_code"];

           $scoreCols["repeat_restrict_behavior"] = $this->scores["q_33_stereotyped_utterances_current_code"]+
                                                    $this->scores["q_77_hands_finger_manners_ever_code"]+
                                                    $this->scores["q_78_oth_complex_manners_ever_code"]+
                                                    $this->scores["q_71_unusual_sens_ints_ever_code"]+ 
                                                    $this->scores["q_67_unusual_preoccupations_ever_code"]+
                                                    $this->scores["q_70_compulsions_rituals_ever_code"];

            $scoreCols["reciprocal_interaction"] =  $this->scores["q_59_appropriat_resp_current_code"]+
                                                    $this->scores["q_62_inter_children_current_code"]+
                                                    $this->scores["q_63_resp_approaches_current_code"];
           

            $scoreCols["imitation"] ="N/A";
             }
//			if(substr($record["q_30_overall_level_of_language"], 0, 1) == 0) { //verbal subject
        //Summary Diagnosis
        if (is_string($scoreCols["A_Total"])) {
            $scoreCols["summary_diagnosis"] = "Respondent too young to score";
        } elseif ($scoreCols["A_Total"] >= 10 && ($scoreCols["BV_Total"] >= 8 || $scoreCols["BNV_Total"] >= 7) && $scoreCols["C_Total"] >=3 && $scoreCols["D_Total"] >= 1) {
            $scoreCols["summary_diagnosis"] = "ASD+";
        } else {
            $scoreCols["summary_diagnosis"] = "ASD-";
        }
        $alg_total = 0; 
        //Summary Diagnosis 2012alg
        if( is_string($scoreCols["social_affect"])) {
            $scoreCols["2012alg_research_diag"] = "Unable to diagnose";
            $scoreCols["2012alg_clinical_diag"] = "Unable to diagnose";
            $scoreCols["2012alg_range_concern"] = "Unable to diagnose";
        } else {
            $alg_total = $scoreCols["social_affect"]+ $scoreCols["repeat_restrict_behavior"] ;
            if($alg_type == 1){ 
                if($alg_total <= 10 && $alg_total >=0){
                    $scoreCols["2012alg_range_concern"] = "Little-to-no concern";   
                } elseif ($alg_total <=13 && $alg_total >=11){
                    $scoreCols["2012alg_range_concern"] = "Mild-to-Moderate concern";   
                } elseif ($alg_total >=14){
                    $scoreCols["2012alg_range_concern"] = "Moderate-to-Severe concern";   
                }
                if($alg_total >= 13){
                   $scoreCols["2012alg_research_diag"] = "ASD+";    
                } else {
                   $scoreCols["2012alg_research_diag"] = "ASD-";    
                }
                if($alg_total >= 11){
                   $scoreCols["2012alg_clinical_diag"] = "ASD+";    
                } else {
                   $scoreCols["2012alg_clinical_diag"] = "ASD-";    
                }
            }
            if($alg_type == 2){ 
                if($alg_total <=7  && $alg_total >=0){
                    $scoreCols["2012alg_range_concern"] = "Little-to-no concern";   
                } elseif ($alg_total <=13 && $alg_total >=8){
                    $scoreCols["2012alg_range_concern"] = "Mild-to-Moderate concern";   
                } elseif ($alg_total >=14){
                    $scoreCols["2012alg_range_concern"] = "Moderate-to-Severe concern";   
                }
                if($alg_total >= 13){
                   $scoreCols["2012alg_research_diag"] = "ASD+";    
                } else {
                   $scoreCols["2012alg_research_diag"] = "ASD-";    
                }
                if($alg_total >= 8){
                   $scoreCols["2012alg_clinical_diag"] = "ASD+";    
                } else {
                   $scoreCols["2012alg_clinical_diag"] = "ASD-";    
                }
            }
            if($alg_type == 3){ 
                $alg_total += $scoreCols["reciprocal_interaction"];
                if($alg_total <= 12 && $alg_total >=0){
                    $scoreCols["2012alg_range_concern"] = "Little-to-no concern";   
                } elseif ($alg_total <=16 && $alg_total >=13){
                    $scoreCols["2012alg_range_concern"] = "Mild-to-Moderate concern";   
                } elseif ($alg_total >=17){
                    $scoreCols["2012alg_range_concern"] = "Moderate-to-Severe concern";   
                }
                if($alg_total >= 16){
                   $scoreCols["2012alg_research_diag"] = "ASD+";    
                } else {
                   $scoreCols["2012alg_research_diag"] = "ASD-";    
                }
                if($alg_total >= 13){
                   $scoreCols["2012alg_clinical_diag"] = "ASD+";    
                } else {
                   $scoreCols["2012alg_clinical_diag"] = "ASD-";    
                }
            }
        }
        // save the resultant total
        $result = $db->update($this->table, $scoreCols, array('CommentID'=>$this->getCommentID()));
		
    }
    
    function _page1(){
        
//        $this->form->addElement("header", null, "BACKGROUND");
//        //$this->addLargeTextAreaElement("background_family_members", "Family Members");
//        //$this->addLargeTextAreaElement("background_education", "Subject's Education");
//        //$this->addLargeTextAreaElement("background_personalized_timing", "Personalized Timing");
//        //$this->addLargeTextAreaElement("background_diagnosis", "Diagnosis");
//        //$this->addLargeTextAreaElement("background_medication", "Medication");
//
//        //$this->addLargeTextAreaElement("introductory_questions", "Introductory Questions");
//        //$this->addLargeTextAreaElement("q_1_current_concerns", "1. Current Concerns");
    }
    
    function _page2() {
	
    		$this->form->addElement("header", null, "EARLY DEVELOPMENT");
		$this->form->addElement('static', null, "<br /><br />");

        	$this->addNumericElement("q_2_age_first_noticed_code", "2. Age (in months) when parents first noticed that something was not quite right...");
		$this->XINRegisterRule("q_2_age_first_noticed_code", array("q_2_age_first_noticed_code_status{@}=={@}"), "Required");
		$this->form->addElement('static', null, "<br />");

        	$this->addTextElement("q_3_first_symptoms_text", "3. First symptoms to arouse parental concern");
        	$this->form->addElement('static', NULL, "<br />"); //blank line
    	
    		$this->addNumericElement("q_4_onset_as_perceived_code", "4. Onset as perceived with hindsight");
    		$this->addLargeTextAreaElement("q_4_onset_as_perceived_text");
    	
		$this->form->addElement('static', null, "<br />");

    		$this->addNumericElement("q_5_first_walked_code", "5. First walked unaided");
		$this->addLargeTextAreaElement("q_5_first_walked_text");

		$this->form->addElement('static', null, "<br />");
		
		$this->addNumericElement("q_6_bladder_daytime_code", "6. Acquisition of bladder control: daytime");
		$this->addLargeTextAreaElement("q_6_bladder_daytime_text");

		$this->form->addElement('static', null, "<br />");
		
		$this->addNumericElement("q_7_bladder_nighttime_code", "7. Acquisition of bladder control: nighttime");
		$this->addLargeTextAreaElement("q_7_bladder_nighttime_text");

                $this->form->addElement('static', null, "<br />");


 		$this->addNumericElement("q_8_bowel_control_code", "8. Acquisition of bowel control");

                $this->form->addElement('static', null, "<br />");

		$this->form->addElement('static', null, "<br /><br />");
		$this->addLargeTextAreaElement("q_8_bowel_control_text");

    }
		
	function _page3() {
		$this->form->addElement("header", null, "ACQUISITION AND LOSS OF LANGUAGE/OTHER SKILLS");
		$this->form->addElement('static', null, "<br /><br />");
	
		$this->addNumericElement("q_9_first_single_words_code", "9. Age of first single words");
		$this->addLargeTextAreaElement("q_9_first_single_words_text");


                $this->form->addElement('static', null, "<br />");

	
		$this->addNumericElement("q_10_first_phrases_code", "10. Age of first phrases (if ever used)");
		$this->addLargeTextAreaElement("q_10_first_phrases_text");


                $this->form->addElement('static', null, "<br />");

		
		$this->form->addElement("select", "q_11_loss_of_language", "11. Loss of language skills after acquisition", $this->yesNoNA);
                $this->form->addElement('static', null, "<br />");
		
		$answerArray = array(""=>NULL, "0_daily"=>"0. Daily", "1_occasional"=>"1. Occasional", "2_upon_request"=>"2. Produced upon request", "3_spontaneous_imitations"=>"3. Spontaneous imitations", "8_no_change_or_loss"=>"8. No change or loss", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("select", "q_12_level_before_loss_code", "12. Level of communicative language before loss", $answerArray);
		$this->XINRegisterRule("q_12_level_before_loss_code", array("q_11_loss_of_language{@}=={@}1_yes"), "This is required if language was lost (answered 'yes' to question 11)");
                $this->form->addElement('static', null, "<br />");
		//$this->addLargeTextAreaElement("q_12_level_before_loss_text", $this->indent . "Describe:", array("q_11_loss_of_language{@}=={@}1_yes"), "This is required if language was lost (answered 'yes' to question 11)");
		
		$answerArray = array(""=>NULL, "0_no_loss"=>"0. No definite loss", "1_probable_loss"=>"1. Probable loss", "2_definite_loss"=>"2. Definite Loss", "8_insufficient"=>"8. Insufficient", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$questionArray = array("q_13_loss_of_spontaneous_use"=>"13. Loss of spontaneous use",
								"q_14_loss_of_intent"=>"14. Loss of communicative intent",
								"q_15_loss_of_syntactical"=>"15. Loss of syntactical skills",
								"q_16_loss_of_articulation"=>"16. Loss of articulation");
		foreach($questionArray as $field=>$label) {
			$this->form->addElement("select", $field . "_code", $label, $answerArray);
			$this->XINRegisterRule($field . "_code", array("q_11_loss_of_language{@}=={@}1_yes"), "This is required if language was lost (answered 'yes' to question 11)");
//			$this->addTextAreaElement($field . "_text", $this->indent . "Describe:");
			$this->XINRegisterRule($field . "_text", array("q_11_loss_of_language{@}=={@}1_yes"), "This is required if language was lost (answered 'yes' to question 11)");
                	$this->form->addElement('static', null, "<br />");
		}
		
		$this->addNumericElement("q_17_main_loss_apparent_code", "17. Age when main loss of language skills first apparent", array("q_11_loss_of_language{@}=={@}1_yes"), "This is required if language was lost (answered 'yes' to question 11)");
		$this->addLargeTextAreaElement("q_17_main_loss_apparent_text", $this->indent . "Describe:", array("q_11_loss_of_language{@}=={@}1_yes"), "This is required if language was lost (answered 'yes' to question 11)");
	
                $this->form->addElement('static', null, "<br />");


		$answerArray = array(""=>NULL, "0_loss_no_relevance"=>"0. Loss no possible relevance", "1_loss_illness"=>"1. Loss from illness", "2_loss_impaired"=>"2. Loss from impaired consciousness", "8_no_loss"=>"8. No loss", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("select", "q_18_loss_due_to_illness", "18. Association of loss of language with physical illness", $answerArray);
		$this->XINRegisterRule("q_18_loss_due_to_illness", array("q_11_loss_of_language{@}=={@}1_yes"), "This is required if language was lost (answered 'yes' to question 11)");
                $this->form->addElement('static', null, "<br />");
		//$this->addLargeTextAreaElement("q_18_loss_due_to_illness_text", $this->indent . "Describe:", array("q_11_loss_of_language{@}=={@}1_yes"), "This is required if language was lost (answered 'yes' to question 11)");
	

		$this->addNumericElement("q_19_duration_of_loss_code", "19. Duration of loss of language skills", array("q_11_loss_of_language{@}=={@}1_yes"), "This is required if language was lost (answered 'yes' to question 11)");
		$this->addLargeTextAreaElement("q_19_duration_of_loss_text", $this->indent . "Describe:", array("q_11_loss_of_language{@}=={@}1_yes"), "This is required if language was lost (answered 'yes' to question 11)");
		
                $this->form->addElement('static', null, "<br />"); 

	}
	
	function _page4() {

		$this->form->addElement("header", null, "GENERAL LOSS OF SKILLS");
		$this->form->addElement('static', null, "<br /><br />");
		$answerArray = array(""=>NULL, "0_no_consistent_loss"=>"0. No consistent loss", "1_probable_loss"=>"1. Probable loss", "2_account_definite_loss"=>"2. Account of definite loss", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("select", "q_20_loss_of_skills_code", "20. Loss of skills (for at least 3 months)", $answerArray);
                $this->form->addElement('static', null, "<br />"); 
		//$this->addLargeTextAreaElement("q_20_loss_of_skills_text");
		
		$questionArray = array("q_21_puposive_hand_movements"=>"21. Purposive hand movements",
		"q_22_motor_skills"=>"22. Motor skills",
		"q_23_self_help_skills"=>"23. Self-help skills",
		"q_24_constructive_play"=>"24. Constructive or imaginative play",
		"q_25_social_engagement"=>"25. Social engagement and responsiveness");
		$answerArray = array(""=>NULL, "0_none"=>"0. None", "1_possible"=>"1. Possible", "2_definite"=>"2. Definite", "not_answered"=>"Not Answered");
		foreach ($questionArray as $field=>$label) {
			$this->form->addElement("select", $field . "_code", $label, $answerArray);
                	$this->form->addElement('static', null, "<br />"); 
//			$this->addTextAreaElement($field . "_text", $this->indent . "Describe:");
		}		
		
		$this->XINRegisterRule("q_21_purposive_hand_movements", array("q_20_loss_of_skills_code{@}=={@}01_yes"), "This is required if skills were lost (answered 'yes' to question 20)");

		$this->addNumericElement("q_26_loss_first_apparent_code", "26. Age when main loss of skill first apparent");
                $this->form->addElement('static', null, "<br />");

	
		$answerArray = array(""=>NULL, "0_no_relevance"=>"0. No possible relevance", "1_definite_illness"=>"1. Definite illness", "2_impaired_consciousness"=>"2. Impaired consciousness", "8_no_loss"=>"8. No loss", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("select", "q_27_physical_illness_code", "27. Association of loss of skills with physical illness", $answerArray);
                $this->form->addElement('static', null, "<br />");
		//$this->addLargeTextAreaElement("q_27_physical_illness_text");
		
		$this->addNumericElement("q_28_duration_of_loss_code", "28. Duration of loss of skills");


		$this->form->addElement('static', null, "<br /><br />");
		$this->addLargeTextAreaElement("q_28_duration_of_loss_text", $this->indent . "Describe:");
	}

	function _page5() {

		$this->form->addElement("header", null, "LANGUAGE AND COMMUNICATION FUNCTIONING");
		$this->form->addElement('static', null, "<br /><br />");
		
		$answerArray = array(""=>NULL, "0_perform_unexpected"=>"0. Perform an unexpected", "1_get_an_object"=>"1. Get an object", "2_understand_many_words"=>"2. Understand many words", "3_understand_fewer_than_50"=>"3. Understand fewer than 50", "4_little_or_no"=>"4. Little or no comprehension of words", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("static", null, "29. Comprehension of simple language");
		$this->form->addElement("select", "q_29_compreh_simple_current",  $this->indent . "Current", $answerArray);
		$this->form->addElement("select", "q_29_compreh_simple_most_abnormal",  $this->indent . "Most Abnormal (4.0-5.0)", $answerArray);
		//$this->addLargeTextAreaElement("q_29_compreh_simple_text");
		
		$this->form->addElement('static', null, "<br />");
		$answerArray = array(""=>NULL, "0_fuctional"=>"0. Functional", "1_no_functional"=>"1. No functional use", "2_fewer_than_5"=>"2. Fewer than five", "not_answered"=>"Not Answered");
		$this->form->addElement("select", "q_30_overall_level_of_language", "30. Overall level of language", $answerArray);
		$this->form->addElement('static', null, "<br />");
		
		$answerArray = array(""=>NULL, "0_no_use"=>"0. No use", "1_occasional_point"=>"1. Occasional to point", "2_occasional_for"=>"2. Occasional 'for'", "3_regular"=>"3. Regular 'for'", "8_little"=>"8. Little", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("static", null, "31. Use of other's body to communicate");
		$this->form->addElement("select", "q_31_use_of_others_body_current_code", $this->indent . "Current:", $answerArray);
		$this->form->addElement("select", "q_31_use_of_others_body_ever_code", $this->indent . "Ever:", $answerArray);
		//$this->addLargeTextAreaElement("q_31_use_of_others_body_text");
		
		$answerArray = array(""=>NULL, "0_anybody"=>"0. Anybody", "1_family"=>"1. Family", "2_difficulties"=>"2. Difficulties", "3_strangers"=>"3. Strangers", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("static", null, "32. Articulation/pronunciation");
		$this->form->addElement("select", "q_32_artic_pronun_current_code", $this->indent . "Current:", $answerArray);
		$this->form->addElement("select", "q_32_artic_pronun_5years_code", $this->indent . "At 5.0 Years:", $answerArray);
		//$this->addLargeTextAreaElement("q_32_artic_pronun_text");
		
		$answerArray = array(""=>NULL, "0_rarely"=>"0. Rarely", "1_more_repetitive"=>"1. More repetitive", "2_often_stereotyped"=>"2. Often stereotyped utterances", "3_exclusively_stereotyped"=>"3. Exclusively stereotyped utterances", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("static", null, "33. Stereotyped utterances and delayed echolalia");
		$this->form->addElement("select", "q_33_stereotyped_utterances_current_code", $this->indent . "Current:", $answerArray);
		$this->form->addElement("select", "q_33_stereotyped_utterances_ever_code", $this->indent . "Ever:", $answerArray);
		//$this->addLargeTextAreaElement("q_33_stereotyped_utterances_text");
		
		$answerArray = array(""=>NULL, "0_verbalizes"=>"0. Verbalizes", "1_some_response"=>"1. Some response", "2_some_alert"=>"2. Some alert", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("static", null, "34. Social verbalization/chat");
		$this->form->addElement("select", "q_34_social_verb_chat_current_code", $this->indent . "Current:", $answerArray);
		$this->form->addElement("select", "q_34_social_verb_chat_ever_code", $this->indent . "Ever:", $answerArray);
		//$this->addLargeTextAreaElement("q_34_social_verb_chat_text");

		$answerArray = array(""=>NULL, "0_conversational"=>"0. Conversational flows", "1_occasional"=>"1. Occasional", "2_little_or_not"=>"2. Little of no", "3_very_little"=>"3. Very little", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("static", null, "35. Reciprocal conversation (within subject's level of language)");
		$this->form->addElement("select", "q_35_recipr_convers_current_code", $this->indent . "Current:", $answerArray);
		$this->form->addElement("select", "q_35_recipr_convers_ever_code", $this->indent . "Ever:", $answerArray);
		//$this->addLargeTextAreaElement("q_35_recipr_convers_text");
		
		$answerArray = array(""=>NULL, "0_none_or_rare"=>"0. No or very rare", "1_some_questions"=>"1. Use of some questions", "2_frequent"=>"2. Frequent", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("static", null, "36. Inappropriate questions or statements");
		$this->form->addElement("select", "q_36_inappropriate_qs_current_code", $this->indent . "Current:", $answerArray);
		$this->form->addElement("select", "q_36_inappropriate_qs_ever_code", $this->indent . "Ever:", $answerArray);
		//$this->addLargeTextAreaElement("q_36_inappropriate_qs_text");

		$answerArray = array(""=>NULL, "0_no_confusion"=>"0. No confusion", "1_refers"=>"1. Refers", "2_you_I_confusion"=>"2. You/I confusion", "3_pronominal"=>"3. Pronominal", "7_other_types"=>"7. Other types of pronominal", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("static", null, "37. Prenominal reversal");
		$this->form->addElement("select", "q_37_prenominal_reversal_current_code", $this->indent . "Current:", $answerArray);
		$this->form->addElement("select", "q_37_prenominal_reversal_ever_code", $this->indent . "Ever:", $answerArray);
		//$this->addLargeTextAreaElement("q_37_prenominal_reversal_text");

		$answerArray = array(""=>NULL, "0_no_use"=>"0. No use", "1_occasional"=>"1. Occasional", "2_regular"=>"2. Regular", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("static", null, "38. Neologisms/Idiosyncratic language");
		$this->form->addElement("select", "q_38_neologisms_current_code", $this->indent . "Current:", $answerArray);
		$this->form->addElement("select", "q_38_neologisms_ever_code", $this->indent . "Ever:", $answerArray);
		//$this->addLargeTextAreaElement("q_38_neologisms_text");

		$answerArray = array(""=>NULL, "0_no_rituals"=>"0. No rituals", "1_tendency"=>"1. Tendency", "2_special_way"=>"2. Special way", "3_as_for2_with_difficulty"=>"3. As for '2', with difficulty", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("static", null, "39. Verbal rituals");
		$this->form->addElement("select", "q_39_verbal_rituals_current_code", $this->indent . "Current:", $answerArray);
		$this->form->addElement("select", "q_39_verbal_rituals_ever_code", $this->indent . "Ever:", $answerArray);
		//$this->addLargeTextAreaElement("q_39_verbal_rituals_text");

		$answerArray = array(""=>NULL, "0_normal"=>"0. Normal", "1_shows_abnormalities"=>"1. Shows abnormalities", "2_clearly_abnormal"=>"2. Clearly abnormal", "3_frequetly_peculiar"=>"3. Frequently peculiar", "7_stutter"=>"7. Stutter", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("static", null, "40. Intonation/volume/rhythm/rate");
		$this->form->addElement("select", "q_40_inton_vol_rhythm_rate_current_code", $this->indent . "Current:", $answerArray);
		$this->form->addElement("select", "q_40_inton_vol_rhythm_rate_ever_code", $this->indent . "Ever:", $answerArray);
		//$this->addLargeTextAreaElement("q_40_inton_vol_rhythm_rate_text");
		$this->form->addElement('static', null, "<br /><br />");
	
	}
	
	function _page6() {

		$this->form->addElement("header", null, "LANGUAGE AND COMMUNICATION FUNCTIONING (Continued)");
		$this->form->addElement('static', null, "<br /><br />");

		$answerArray = array(""=>NULL, "0_speech_used_frequently"=>"0. Speech used frequently", "1_some_communication"=>"1. Some communication", "2_some_spontaneous"=>"2. Some spontaneous", "3_lillte_or_no"=>"3. Little or no", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("static", null, "41. Current communicative speech");
		$this->form->addElement("select", "q_41_cur_comm_speech_current_code", $this->indent . "Current:", $answerArray);
		$this->form->addElement("select", "q_41_cur_comm_speech_at5_code", $this->indent . "At 5.0 years:", $answerArray);
		//$this->addLargeTextAreaElement("q_41_cur_comm_speech_text");
		
		$answerArray = array(""=>NULL, "0_spontaneously"=>"0. Spontaneously points", "1_limited_attempt"=>"1. Limited attempt", "2_little_or_no"=>"2. Little or no", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("static", null, "42. Pointing to express interest");
		$this->form->addElement("select", "q_42_point_express_interest_current_code", $this->indent . "Current:", $answerArray);
		$this->form->addElement("select", "q_42_point_express_inter_most_abnormal_code", $this->indent . "Most abnormal 4.0-5.0 years:", $answerArray);
		//$this->addLargeTextAreaElement("q_42_pointing_to_express_interest_text");
		
		$answerArray = array(""=>NULL, "0_consistently"=>"0. Consistently", "1_sometimes"=>"1. Sometimes", "2_never"=>"2. Never", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_43_nodding";
		$label = "43. Nodding";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);
		
		$answerArray = array(""=>NULL, "0_consistently"=>"0. Consistently", "1_sometimes"=>"1. Sometimes", "2_never"=>"2. Never", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_44_head_shaking";
		$label = "44. Head shaking";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);
		
		$answerArray = array(""=>NULL, "0_appripriate"=>"0. Appropriate", "1_spontaneous"=>"1. Spontaneous", "2_inconsistent"=>"2. Inconsistent", "3_no_use"=>"3. No use", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_45_conventional_instr_gests";
		$label = "45. Conventional/instrumental gestures";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);
		
		$answerArray = array(""=>NULL, "0_usually"=>"0. Usually", "1_not_consistently"=>"1. Not consistently", "2_usually_does_not"=>"2. Usually does not", "3_rarely"=>"3. Rarely", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_46_attent_voice";
		$label = "46. Attention to voice";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);
		
		$answerArray = array(""=>NULL, "0_spontaneous"=>"0. Spontaneous", "1_some"=>"1. Some", "2_limited"=>"2. Limited", "3_very_rare"=>"3. Very rare", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_47_spont_imit";
		$label = "47. Spontaneous imitation of actions";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);
		
		$answerArray = array(""=>NULL, "0_variety"=>"0. Variety", "1_some"=>"1. Some", "2_occasional"=>"2. Occasional", "3_no_pretend"=>"3. No pretend", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_48_imag_play";
		$label = "48. Imaginative play";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);
		
		$answerArray = array(""=>NULL, "0_imaginative"=>"0. Imaginative",  "1_some_participation"=>"1. Some participation",  "2_some_play"=>"2. Some play",  "3_no_play"=>"3. No play", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_49_imag_play_peers";
		$label = "49. Imaginative play with peers";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);
		$this->form->addElement('static', null, "<br /><br />");

	}
	
	function _page7() {

		$this->form->addElement("header", null, "SOCIAL DEVELOPMENT AND PLAY");
		$this->form->addElement('static', null, "<br /><br />");

		$answerArray = array(""=>NULL, "0_normal"=>"0. Normal", "1_definite"=>"1. Definite", "2_uncertain"=>"2. Uncertain", "3_unusual"=>"3. Unusual", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_50_direct_gaze";
		$label = "50. Direct gaze";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_regularly"=>"0. Regularly", "1_some_reciprocal"=>"1. Some reciprocal", "2_some_smiling"=>"2. Some smiling", "3_little_or_no"=>"3. Little or no", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_51_social_smiling";
		$label = "51. Social smiling";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_regular"=>"0. Regular", "1_possible"=>"1. Possible", "2_some"=>"2. Some", "3_rare"=>"3. Rare", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_52_show_direct_atten";
		$label = "52. Showing and directing attention";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);
		
		$answerArray = array(""=>NULL, "0_frequent"=>"0. Frequent", "1_some"=>"1. Some", "2_sometimes"=>"2. Sometimes", "3_no_sharing"=>"3. No sharing", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_53_offer_share";
		$label = "53. Offering to share";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_frequent"=>"0. Frequent", "1_some"=>"1. Some", "2_few"=>"2. Few", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_54_seek_share_enjoy";
		$label = "54. Seeking to share her/his enjoyment with others";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_frequently"=>"0. Frequently", "1_partial"=>"1. Partial", "2_rarely"=>"2. Rarely", "3_never"=>"3. Never", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_55_offer_comf";
		$label = "55. Offerings comfort";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_consistently"=>"0. Consistently", "1_may"=>"1. May", "2_rarely"=>"2. Rarely", "3_shows_no"=>"3. Shows no", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_56_qual_social_overts";
		$label = "56. Quality of social overtures";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_full"=>"0. Full", "1_somewhat"=>"1. Somewhat", "2_markedly"=>"2. Markedly", "3_little_or_no"=>"3. Little or no", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_57_range_facial_expr";
		$label = "57. Range of facial expressions used to communicate";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_almost_always"=>"0. Almost always", "1_slightly"=>"1. Slightly", "2_obviously"=>"2. Obviously", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("static", null, "58. Inappropriate facial expressions");
		$this->form->addElement("select", "q_58_inappropriate_facial_current_code", $this->indent . "Current:", $answerArray);
		$this->form->addElement("select", "q_58_inappropriate_facial_ever_code", $this->indent . "Ever:", $answerArray);
		//$this->addLargeTextAreaElement("q_58_inappropriate_facial_text");
		
		$answerArray = array(""=>NULL, "0_appropriate"=>"0. Appropriate", "1_some"=>"1. Some", "2_responds"=>"2. Responds", "3_little_or_no"=>"3. Little or no", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_59_appropriat_resp";
		$label = "59. Appropriateness of social responses";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);
		$this->form->addElement('static', null, "<br /><br />");
		
		//$this->addLargeTextAreaElement("q_60_favourite_activities", "Favourite Activities");
		//$this->addLargeTextAreaElement("q_60_favourite_toys_objects", "Favourite Toys / Objects");
	}
	
	function _page8() {
		$this->form->addElement('static', null, "<br /><br />");
		$answerArray = array(""=>NULL, "0_range"=>"0. Range", "1_initiates"=>"1. Initiates", "2_passive"=>"2. Passive", "3_no_active"=>"3. No active", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_60_init_activities";
		$label = "60. Initiation of appropriate activities";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_normal"=>"0. Normal", "1_some"=>"1. Some", "2_little"=>"2. Little", "3_no_evidence"=>"3. No evidence", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_61_imit_soc_play";
		$label = "61. Imitative social play";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_often"=>"0. Often", "1_usually"=>"1. Usually", "2_occasionaly"=>"2. Occasionaly", "3_shows_no"=>"3. Shows no", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_62_inter_children";
		$label = "62. Interest in children";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_generally"=>"0. Generally", "1_sometimes"=>"1. Sometimes", "2_rarely"=>"2. Rarely", "3_consistently"=>"3. Consistently", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_63_resp_approaches";
		$label = "63. Response to approaches of other children";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_actively"=>"0. Actively", "1_some"=>"1. Some", "2_enjoys"=>"2. Enjoys", "3_seeks_no"=>"3. Seeks no", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_64_group_play_peers";
		$label = "64. Group play peers";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0"=>"0. One or more, same age group", "1"=>"1. One or more, limited", "2"=>"2. Only in group situation", "3_no_peer"=>"3. No peer", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_65_friendships";
		$label = "65. Friendships";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_normal"=>"0. Normal", "1_occasional"=>"1. Occasional", "2_lack"=>"2. Lack", "3_marked"=>"3. Marked", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_66_soc_disinhibit";
		$label = "66. Social disinhibition";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);
		$this->form->addElement('static', null, "<br /><br />");
	}
	
	function _page9() {
		$this->form->addElement("header", null, "INTERESTS AND BEHAVIOURS");
		$this->form->addElement('static', null, "<br /><br />");

		$answerArray = array(""=>NULL, "0_no_unusual"=>"0. No unusual", "1_unusual"=>"1. Unusual", "2_definite_intrudes"=>"2. Definite intrudes", "3_definite_interferes"=>"3. Definite Interferes", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_67_unusual_preoccupations";
		$label = "67. Unusual preoccupations";
		$this->_addCurrentEver($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_no"=>"0. No", "1_special"=>"1. Special", "2_definite_no_interfere"=>"2. Definite no interfere", "3_definite_impairment"=>"3. Definite impairment", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_68_circumscr_ints";
		$label = "68. Circumscribed interests";
		$this->_addCurrentEver($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_little_or_no"=>"0. Little or no", "1_some"=>"1. Some", "2_does_not_constrain"=>"2. Does not constrain", "3_prevents"=>"3. Prevents", "7_infant_toys"=>"7. Infant toys", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_69_repet_use_objects";
		$label = "69. Repetitive use of objects or interest in parts of objects";
		$this->_addCurrentEver($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_no"=>"0. No", "1_some"=>"1. Some", "2_one_or_more"=>"2. One or more", "3_marked"=>"3. Marked", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_70_compulsions_rituals";
		$label = "70. Compulsions/rituals";
		$this->_addCurrentEver($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_no_unusual"=>"0. No unusual", "1_one_or_two"=>"1. One or two", "2_has"=>"2. Has interest", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_71_unusual_sens_ints";
		$label = "71. Unusual sensory interests";
		$this->_addCurrentEver($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_no_general"=>"0. No general", "1_slight"=>"1. Slight", "2_definite_not_distressing"=>"2. Definite not distressing", "3_definite_interferes"=>"3. Definite interferes", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_72_undo_gen_sens_noise";
		$label = "72. Undo general sensitivity to noise";
		$this->_addCurrentEver($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_no"=>"0. No", "1_mild"=>"1. Mild", "2_occasional"=>"2. Occasional", "3_substantial"=>"3. Substantial", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_73_idiosyncratic";
		$label = "73. Abnormal, idiosyncratic, negative response to specific sensory stimuli";
		$this->_addCurrentEver($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_no"=>"0. No", "1_unusually"=>"1. Unusually", "2_resistance"=>"2. Resistance", "3_substantial"=>"3. Substantial", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_74_diff_minor_changes";
		$label = "74. Difficulties with minor changes in subjects own routines or personal environment";
		$this->_addCurrentEver($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_none"=>"0. None", "1_unusually"=>"1. Unusually", "2_avoid"=>"2. Avoid", "3_substantial"=>"3. Substantial", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_75_resist_trivial_chng";
		$label = "75. Resistance to trivial changes in the environment";
		$this->_addCurrentEver($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_no"=>"0. No", "1_some"=>"1. Some", "2_significant"=>"2. Significant", "3_intrusive"=>"3. Intrusive", "6_beyond_5"=>"6. Beyond age 5", "7_series"=>"7. Series", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_76_unus_attach_objects";
		$label = "76. Unusual attachments to objects";
		$this->_addCurrentEver($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_no"=>"0. No", "1_occasional"=>"1. Occasional", "2_definite"=>"2. Definite", "3_marked"=>"3. Marked", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_77_hands_finger_manners";
		$label = "77. Hands and finger mannerisms";
		$this->_addCurrentEver($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_no"=>"0. No", "1_only"=>"1. Only", "2_definite"=>"2. Definite", "3_marked"=>"3. Marked", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_78_oth_complex_manners";
		$label = "78. Other complex mannerisms or stereotyped body movements";
		$this->_addCurrentEver($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_no"=>"0. No", "1_occasional"=>"1. Occasional", "2_definite"=>"2. Definite", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_79_midline_hand_moves";
		$label = "79. Midline hand movements";
		$this->_addCurrentEver($field, $label, $answerArray);
		$this->form->addElement('static', null, "<br /><br />");

	}
	
	function _page10() {

		$this->form->addElement("header", null, "GENERAL BEHAVIOURS");
		$this->form->addElement('static', null, "<br /><br />");
	
		$answerArray = array(""=>NULL, "0_normal"=>"0. Normal", "1_somewhat"=>"1. Somewhat", "2_defnitely"=>"2. Definitely", "3_gait_odd"=>"3. Gait odd", "7_gait_neurological"=>"7. Gait neurological", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_80_gait";
		$label = "80. Gait";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_no"=>"0. No", "1_mild"=>"1. Mild", "2_definite"=>"2. Definite", "3_violence"=>"3. Violence", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_81_aggress_caregivers";
		$label = "81. Aggression towards caregivers or family members";
		$this->_addCurrentEver($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_rare"=>"0. Rare", "1_mild"=>"1. Mild", "2_definite"=>"2. Definite", "3_violence"=>"3. Violence", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_82_aggress_noncaregivers";
		$label = "82. Aggression toward noncaregivers or nonfamily members";
		$this->_addCurrentEver($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_no"=>"0. No", "1_slight"=>"1. Slight", "2_definitely"=>"2. Definitely", "3_serious"=>"3. Serious", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_83_self_injury";
		$label = "83. Self-injury";
		$this->_addCurrentEver($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_no"=>"0. No", "1_occasional"=>"1. Occasional", "2_frequent"=>"2. Frequent", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_84_hyperventilation";
		$label = "84. Hyperventilation";
		$this->_addCurrentEver($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_no"=>"0. No", "1_history"=>"1. History", "2_definite"=>"2. Definite", "7_febrile"=>"7. Febrile", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_85_faints_fits_blackouts";
		$label = "85. Faints/fits/blackouts";
		$this->_addCurrentEver($field, $label, $answerArray);
		$this->form->addElement('static', null, "<br />");

		$answerArray = array(""=>NULL, "0"=>"0. Normal first 3 yrs", "1"=>"1. Within normal first 3", "2"=>"2. Probably abnormal by 3", "3"=>"3. Definitely abnormal by 3", "4"=>"4. Definitely abnormal by 3, indicative of autism", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("select", "q_86_age_when_abnormality_first_evident", "86. Age when abnormality first evident", $answerArray);
		$this->form->addElement('static', null, "<br />");
		//$this->addLargeTextAreaElement("q_86_age_when_abnormality_first_evident_text");

		$this->addNumericElement("q_87_interviewers_judgment", "87. Interviewers judgment on age when developmental abnormalities probably first manifest");
		$this->form->addElement('static', null, "<br /><br />");
		
	}
	
	function _page11(){
		$this->form->addElement("header", null, "SPECIAL ISOLATED SKILLS");
		$this->form->addElement('static', null, "<br /><br />");
		
		//$this->addLargeTextAreaElement("special_isolated_skills", "Special isolated skills");

		$answerArray = array(""=>NULL, "0_no"=>"0. No", "1_above_subject"=>"1. Above subject", "2_above_population"=>"2. Above population", "7_meaningful"=>"7. Meaningful", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$questionArray = array("q_88_visuospatial_ability"=>"88. Visuospatial ability",
								"q_89_memory_still"=>"89. Memory still",
								"q_90_musical_ability"=>"90. Musical ability",
								"q_91_drawings_skill"=>"91. Drawings skill",
								"q_92_reading_ability"=>"92. Reading ability",
								"q_93_computational_ability"=>"93. Computational ability");
		foreach($questionArray as $field=>$label) {
			$this->form->addElement("static", null, $label);
			$this->form->addElement("select", $field . "_current_code", $this->indent . "Current:", $answerArray);
			$this->form->addElement("select", $field . "_ever_code", $this->indent . "Ever:", $answerArray);
			$this->form->addElement('static', null, "<br /><br />");
		}
		
//		$this->form->addElement("header", null, "CONCLUDING COMMENTS");
//		$questionArray = array("overall_assessment"=>"Overall assessment",
//								"interviewers_impressions_and_circumstances"=>"Interviewers impressions and circumstances of interview",
//								"summary_of_discrepancies"=>"Summary of discrepancies between informant description and observer information");
//		foreach($questionArray as $field=>$label) {
			//$this->addLargeTextAreaElement($field, $label);
//		}	

	}

/* Below are proposed changes to questions 2,4,5,6,7,8,9,10,17,19,26 and 28 to better reflect the paper version of the questionnaire. The drop-down menus in the status field for these questions include all options presented. 
  
--question2 

//             $this->form->addElement('text', 'q_2_age_first_noticed_code', "2. Age (in months) when parents first noticed that something was not quite right...");             

//		 $this->form->addElement('select', 'q_2_age_first_noticed_code_status', '', array(null=>"", "991"=>"991. Parents not concerned", "992"=>"992. Parents worried since birth", "996"=>"996. Before 3 years", "997"=>"997. After 3 years", "998"=>"998. N/A", "999"=>"999. Not asked", "not_answered"=>"Not Answered"));


--question4
               //$this->form->addElement('select', 'q_4_onset_as_perceived_code', "4. Onset as perceived with hindsi
ght", array(null=>"", "0"=>"0. Problems in first 12 months", "1"=>"1. Before 2nd birthday", "2"=>"2. Before 3rd birt
hday", "3"=>"3. Before 4th birthday", "4"=>"4. Before 5th birthday", "5"=>"5. Before 6th birthday", "6"=>"6. At a later date (specify)", "7"=>"7. Child always different", "8"=>"8. No problems noted by parents", "9"=>"9. Not asked", "not_answered"=>"Not Answered"));
                // $this->addTextElement('q_4_specify', "If you selected '6. At a later date', please specify:");                //$this->XINRegisterRule("q_4_specify", array("q_4_onset_as_perceived_code{@}=={@}6"), "This is require
d if onset was at a later date (answered '6. At a later date') above");


--question5
                // $this->form->addElement('text', 'q_5_first_walked_code', "5. First walked unaided");
                // $this->form->addElement('select', 'q_5_first_walked_code_status', '', array(null=>"", "995"=>"995. Still not reached", "996"=>"996. N/K, apparently normal", "997"=>"997. N/K, apparently delayed", "998"=>"998. N/A"
, "999"=>"999. Not asked", "not_answered"=>"Not Answered"));                //$this->XINRegisterRule("q_5_first_walked_code", array("q_5_first_walked_code_status{@}=={@}"), "Required");


--question6

                //  $this->form->addElement('text', 'q_6_bladder_daytime_code', "6. Acquisition of bladder control: 
daytime");
                //$this->form->addElement('select', 'q_6_bladder_daytime_code_status', '', array(null=>"", "993"=>"993. Successful for 12 months, but relapsed", "994"=>"994. Never achieved", "995"=>"995. Less than 12 months", "996"=
>"996. N/K, apparently normal", "997"=>"997. N/K, apparently delayed", "998"=>"998. N/A", "999"=>"999. Not asked", "not_answered"=>"Not Answered"));                //$this->XINRegisterRule("q_6_bladder_daytime_code", array("q_6_bladder_daytime_code_status{@}=={@}"), "Required");

--question7

               // $this->form->addElement('text', 'q_7_bladder_nighttime_code', "7. Acquisition of bladder control: nighttime");
               // $this->form->addElement('select', 'q_7_bladder_nighttime_code_status', '', array(null=>"", "993"=>"993. Successful for 12 months, but relapsed", "994"=>"994. Never achieved", "995"=>"995. Less than 12 months", "996"=>"996. N/K, apparently normal", "997"=>"997. N/K, apparently delayed", "998"=>"998. N/A", "999"=>"999. Not asked", "not_answered"=>"Not Answered"));
        //      $this->XINRegisterRule("q_7_bladder_nighttime_code", array("q_7_bladder_nighttime_code_status{@}=={@}"), "Required");


--question8

            //    $this->form->addElement('text', 'q_8_bowel_control_code', "8. Acquisition of bowel control");
          //      $this->form->addElement('select', 'q_8_bowel_control_code_status', '', array(null=>"", "993"=>"993. Successful for 12 months, but relapsed", "994"=>"994. Never achieved", "995"=>"995. Less than 12 months", "996"=>"996. N/K, apparently normal", "997"=>"997. N/K, apparently delayed", "998"=>"998. N/A", "999"=>"999. Not asked", "not_answered"=>"Not Answered"));
        //      $this->XINRegisterRule("q_8_bowel_control_code", array("q_8_bowel_control_code_status{@}=={@}"), "Required");


--question9

             //   $this->form->addElement('text', 'q_9_first_single_words_code', "9. Age of first single words");
             //   $this->form->addElement('select', 'q_9_first_single_words_code_status', '', array(null=>"", "993"=>"993. Some words, then lost", "994"=>"994. Not achieved", "996"=>"996. N/K, apparently normal", "997"=>"997. N/K, apparently delayed", "999"=>"999. Not asked", "not_answered"=>"Not Answered"));
        //      $this->XINRegisterRule("q_9_first_single_words_code", array("q_9_first_single_words_code_status{@}=={@}"), "Required");


--question10

               // $this->form->addElement('text', 'q_10_first_phrases_code', "10. Age of first phrases (if ever used)");
               // $this->form->addElement('select', 'q_10_first_phrases_code_status', '', array(null=>"", "993"=>"993. Some phrases, then lost", "994"=>"994. Not achieved", "996"=>"996. N/K, apparently normal", "997"=>"997. N/K, apparently delayed", "999"=>"999. Not asked", "not_answered"=>"Not Answered"));
        //      $this->XINRegisterRule("q_10_first_phrases_code", array("q_10_first_phrases_code_status{@}=={@}"), "Required");


--question17

             // $this->form->addElement('text', 'q_17_main_loss_apparent_code', "17. Age when main loss of languag
e skills first apparent");               // $this->form->addElement('select', 'q_17_main_loss_apparent_code_status', '', array(null=>"", "998"
=>"998. No loss", "999"=>"999. Not asked", "not_answered"=>"Not Answered"));                //$this->XINRegisterRule("q_17_main_loss_apparent_code", array("q_11_loss_of_language{@}=={@}1_yes", "q_17_main_loss_apparent_code_status{@}=={@}"), "This is required if language was lost (answered 'yes' to question 
11)");


--question19

               // $this->form->addElement('text', 'q_19_duration_of_loss_code', "19. Duration of loss of language skills");
               // $this->form->addElement('select', 'q_19_duration_of_loss_code_status', '', array(null=>"", "993"=>"993. Loss still present", "994"=>"994. Progressive deterioration continuing", "998"=>"998. No loss", "999"=>"999. Not asked", "not_answered"=>"Not Answered"));
               // $this->XINRegisterRule("q_19_duration_of_loss_code", array("q_11_loss_of_language{@}=={@}1_yes", "q_19_duration_of_loss_code_status{@}=={@}"), "This is required if language was lost (answered 'yes' to question 11)");


--question26

//              $this->addTextAreaElement("q_26_loss_first_apparent_text", $this->indent . "Describe:");

//                $this->form->addElement('text', 'q_26_loss_first_apparent_code', "26. Age when main loss of skill first apparent");
  //              $this->form->addElement('select', 'q_26_loss_first_apparent_code_status', '', array(null=>"", "998"=>"998. No loss at either '1' or '2' level of skills", "999"=>"999. Not asked", "not_answered"=>"Not Answered"));
    //            $this->XINRegisterRule("q_26_loss_first_apparent_code", array("q_26_loss_first_apparent_code_status{@}=={@}"), "Required");


--question28

//              $this->addTextAreaElement("q_26_loss_first_apparent_text", $this->indent . "Describe:");

//                $this->form->addElement('text', 'q_26_loss_first_apparent_code', "26. Age when main loss of skill first apparent");
  //              $this->form->addElement('select', 'q_26_loss_first_apparent_code_status', '', array(null=>"", "998"=>"998. No loss at either '1' or '2' level of skills", "999"=>"999. Not asked", "not_answered"=>"Not Answered"));
    //            $this->XINRegisterRule("q_26_loss_first_apparent_code", array("q_26_loss_first_apparent_code_status{@}=={@}"), "Required");



*/

	
/*	
		$answerArray = array(""=>NULL, ""=>"", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = ;
		$label = ;
		$this->_addCurrentEver($field, $label, $answerArray);

		$answerArray = array(""=>NULL, ""=>"", "not_answered"=>"Not Answered");
		$this->form->addElement("static", null, "");
		$this->form->addElement("select", );
		$this->addTextElement("_code", );
		//$this->addLargeTextAreaElement("_text");
		$this->XINRegisterRule(, array("q_11_loss_of_language{@}=={@}1_yes"), "This is required if language was lost (answered 'yes' to question 11)");
*/

    /**
    * Wrapper to create a large text area field, with an accompanying status field.  Modified from the base class function addTextAreaElement
    * @param    string    $field    The database field in which the response will be stored
    * @param    string    $label    The question text to display
    * @param    array    $rules    {@} delimited rules
    * @param    string    $rule_message    rule message to display upon rule violation
    */
    function addLargeTextAreaElement($field, $label = "&nbsp;&nbsp;&nbsp;&nbsp;Describe:", $rules=array(), $rule_message='This field must be completed or marked as not answered.') {
        return;  //removed all free form comment text boxes.
        $group[]=&$this->form->createElement("textarea", $field, null, array('cols'=>60, 'rows'=>6));
        $group[]=&$this->form->createElement("select", $field."_status", "", array(NULL=>'', 'not_answered'=>'Not Answered'));
        $this->form->addGroup($group, $field.'_group', $label, null, false);
        unset($group);
        $rules_array=array_merge(array($field.'_status{@}=={@}'),$rules);
        $this->XINRegisterRule($field, $rules_array, $rule_message, $field.'_group');
    }
    
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
	
	function _cleanToDigits($string) {
	   $string = preg_replace("/[^0-9]/", "", $string);
	   if(is_numeric($string)) {
            return intval($string);
	   } else return null;
	   
	}

    // Special case for certification module, since
    // both adi_r_subject and proband are treated
    // as one.
    //
    function _getExaminerNames()
    {
        $db =& Database::singleton();

        $centerID = $db->pselectOne("SELECT session.CenterID FROM session, flag WHERE session.ID=flag.SessionID and flag.CommentID=:cmnt_id", array('cmnt_id'=>$this->getCommentID()));
        if($centerID == array()) {
            $centerID = null;
        }

        //get examiner certifications for profiles part of IBIS2
        $candID = isset($_REQUEST['candID']) ? $_REQUEST['candID'] : '';
        $project = $db->pselectOne("SELECT ProjectID from candidate where CandID =:cnd_id", array('cnd_id'=>$candID));

        list($CertificationEnabled, $CertificationProjects, $CertificationInstruments) = $this->_getCertificationConfig();
        if ($CertificationEnabled && in_array($project, $CertificationProjects)
        ) {
            // Don't include check against config file for instrument, because it's stored
            // in the config as 'ADI-R' not $testName
            //&& in_array($this->testName, $CertificationInstruments)) {
            // Just use the testID for proband, because that's the one that's saved.
            $test_id = $db->pselectOne("SELECT ID FROM test_names WHERE Test_name =:tst_name", array('tst_name'=>'adi_r_proband'));
            $results = $db->pselect("SELECT certification.examinerID, full_name FROM certification JOIN examiners ON (certification.examinerID=examiners.examinerID) WHERE testID =:tid AND pass =:cert_id AND centerID =:cid ORDER BY full_name",array('tid'=>$test_id,'cert_id'=>'certified','cid'=>$centerID));
        } else {
            $results = $db->pselect("SELECT examinerID, full_name FROM examiners WHERE centerID=:centID ORDER BY full_name", array('centID' => $centerID));
        }
        
        $examiners = array(''=>'');
        if(is_array($results) && !empty($results)) {
            foreach($results AS $row) {
                $examiners[$row['examinerID']] = $row['full_name'];
            }
        }
        return $examiners;
    }

}
?>
