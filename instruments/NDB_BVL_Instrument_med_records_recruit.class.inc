<?php

require_once('NDB_BVL_Instrument_med_records.class.inc');

class NDB_BVL_Instrument_med_records_recruit extends NDB_BVL_Instrument_med_records {
	/*
	 INSERT INTO test_names VALUES('', 'med_records_recruit', 'Medical Records Data Extraction: New Recruit', '0', '1');
	 INSERT INTO instrument_subtests VALUES('', 'med_records_recruit', 'med_records_recruit_page1', '1. Possible Exclusionary Criteria', 1);
	 INSERT INTO instrument_subtests VALUES('', 'med_records_recruit', 'med_records_recruit_page2', '2. Growth Chart Information', 2);
	 INSERT INTO test_battery VALUES ('', 'med_records_recruit', '150', '270', 'Y', 'Visit', '1'); -- 6month recruit
	 INSERT INTO test_battery VALUES ('', 'med_records_recruit', '300', '420', 'Y', 'Visit', '2'); -- 12month recruit
	 INSERT INTO test_battery VALUES ('', 'med_records_recruit', '150', '270', 'Y', 'Visit', '3'); -- controls
	*/
        var $developmental_concerns = array (''=>NULL,'language' => "language", 'social' => "social", 'motor' => "motor",
                                         'other' => "other",'not_answered'=>'Not Answered');
	
	
	
	/**
	 * sets up basic data, such as the HTML_Quickform object, and so on.
	 *
	 * @param string $commentID  the CommentID identifying the data to load
	 * @param string $page       if a multipage form, the page to show
	 * @return void
	 * @access public
	 */
	function setup($commentID, $page) {
		// set the object properties
		$this->testName = "med_records_recruit"; // test_names.Test_name
		$this->table = 'med_records_recruit'; // name of database table corresponding to instrument
                $this->_selectMultipleElements = array('developmental_concerns_specify');
	
		$this->_doubleDataEntryDiffIgnoreColumns = array('CommentID', 'UserID', 'Testdate',  'Window_Difference', 'Candidate_Age','Data_entry_completion_status',
								 'sig_notes_during_pregnancy_or_delivery_specify',
								 'significant_injuries_or_illnesses_specify',
								 'history_of_psychiatric_problems_specify',
								 'other_genetic_tests_completed_specify',
								 'other_significant_events_or_diagnosis_specify',
                                 'first_percentage_length',
                                 'first_weight_percentage',
                                 'first_head_percentage',
                                 'second_percentage_length',
                                 'second_weight_percentage',
                                 'second_head_percentage',
                                 'third_percentage_length',
                                 'third_weight_percentage',
                                 'third_head_percentage',
                                 'fourth_percentage_length',
                                 'fourth_weight_percentage',
                                 'fourth_head_percentage',
                                 'fifth_percentage_length',
                                 'fifth_weight_percentage',
                                 'fifth_head_percentage',
                                 'sixth_percentage_length',
                                 'sixth_weight_percentage',
                                 'sixth_head_percentage',
                                 'seventh_percentage_length',
                                 'seventh_weight_percentage',
                                 'seventh_head_percentage',
                                 'eighth_percentage_length',
                                 'eighth_weight_percentage',
                                 'eighth_head_percentage',
                                 'ninth_percentage_length',
                                 'ninth_weight_percentage',
                                 'ninth_head_percentage',
                                 'tenth_percentage_length',
                                 'tenth_weight_percentage',
                                 'tenth_head_percentage',
                                 'eleventh_percentage_length',
                                 'eleventh_weight_percentage',
                                 'eleventh_head_percentage',
                                 'twelfth_percentage_length',
                                 'twelfth_weight_percentage',
                                 'twelfth_head_percentage',
                                 'thirteenth_percentage_length',
                                 'thirteenth_weight_percentage',
                                 'thirteenth_head_percentage',
                                 'fourteenth_percentage_length',
                                 'fourteenth_weight_percentage',
                                 'fourteenth_head_percentage',
                                 'fifteenth_percentage_length',
                                 'fifteenth_weight_percentage',
                                 'fifteenth_head_percentage',
                                 'sixteenth_percentage_length',
                                 'sixteenth_weight_percentage',
                                 'sixteenth_head_percentage',
                                 'seventeenth_percentage_length',
                                 'seventeenth_weight_percentage'
                                 );
								 
		// setup the form
		$this->_setup ( $commentID, $page );
	}
	
	/**
	 * generates the main page of the form.
	 *
	 * @return void
	 * @access private
	 *
	 */
	function _main() {
		// display test name
		$this->form->addElement ( 'header', 'instrument_title', "Medical Records Data Extraction: New Recruit" );
		
		// automatically adds examiner & date of administration
		$this->_addMetadataFields ();
        $this->form->addElement('textarea', 'comments', 'General comments:');
        $this->XINRegisterRule('comments', array("comments{@}=={@}NEVER_REQUIRED"));
        $this->addDateElement('Lastupdated', 'Date last updated:', $this->dateOptions);
        $this->form->addFormRule(array(&$this, 'Med_Rules'));


	}
	
	function _page1() {
                $this->addDateElement('Lastupdated_exclusionary', 'Date this form was last updated:', $this->dateOptions);
                $this->form->addElement ( "static", null, "<BR>" );

		$this->form->addElement ( "select", "significant_notes_during_pregnancy_or_delivery", "Anything significant noted during pregnancy or delivery?", $this->yesNo );
		$this->addTextElement ( "sig_notes_during_pregnancy_or_delivery_specify", $this->indent . "If yes, specify:", array ("significant_notes_during_pregnancy_or_delivery{@}=={@}yes" ), "This field is required." );
		$this->form->addElement ( "static", null, "<BR>" ); //line space
		

		$this->form->addElement ( "select", "significant_injuries_or_illnesses", "Has the infant had any significant injuries or illnesses (e.g., head injury, high fevers, seizures)?", $this->yesNo );
		//$this->addTextElement ( "significant_injuries_or_illnesses_specify", $this->indent . "If yes, specify:", array ("significant_injuries_or_illnesses{@}=={@}yes" ), "This field is required." );
                $this->addTextElement ( "significant_injuries_or_illnesses_specify", $this->indent . "1. Specify first injury/illness:", array ("significant_injuries_or_illnesses{@}=={@}yes" ), "This field is required." );
                $group[] = $this->form->createElement("date", "date_injury_illness", null, $this->dateOptions);
                $this->dateTimeFields[] = "date_injury_illness"; //add to array of dates and times.
                $group[] = $this->form->createElement("select","date_injury_illness_status", null, array(NULL=>"", 'not_answered'=>"Not Answered"));
                $this->form->addGroup($group, "date_injury_illness_group", $this->indent.$this->indent."Date of first injury/illness", $this->_GUIDelimiter, FALSE);
                unset($group);
                $status = "date_injury_illness_status";
                $this->XINRegisterRule("date_injury_illness", array("$status{@}=={@}", "significant_injuries_or_illnesses_specify{@}!={@}"), "A Date, not answered is required", "date_injury_illness".$i."_group");
                $this->dateTimeFields[] = 'date_injury_illness';
                $mapping = array(2=>'second',3=>'third',4=>'fourth',5=>'fifth');
		for($i=2; $i<=5; $i++) {
			$this->addTextElement ( "significant_injuries_or_illnesses_specify".$i, $this->indent . "$i. Specify $mapping[$i] injury/illness:", array ("significant_injuries_or_illnesses_specify$i{@}=={@}NEVER_REQUIRED"));
			$group[] = $this->form->createElement("date", "date_injury_illness".$i, null, $this->dateOptions);
			$this->dateTimeFields[] = "date_injury_illness".$i; //add to array of dates and times.
			$group[] = $this->form->createElement("select","date_injury_illness".$i."_status", null, array(NULL=>"", 'not_answered'=>"Not Answered"));
			$this->form->addGroup($group, "date_injury_illness".$i."_group", $this->indent.$this->indent."Date of $mapping[$i] injury/illness", $this->_GUIDelimiter, FALSE);
			unset($group);
			$status = "date_injury_illness".$i."_status";
			$this->XINRegisterRule("date_injury_illness".$i, array("$status{@}=={@}", "significant_injuries_or_illnesses_specify$i{@}!={@}"), "A Date, not answered is required", "date_injury_illness".$i."_group");

		}
		$this->form->addElement ( "static", null, "<BR>" ); //line space
		

		$this->form->addElement ( "select", "history_of_psychiatric_problems", "Any history of relatives with Schizophrenia, Bipolar Disorder, Intellectual Disability or Psychosis?", $this->yesNo );
		$this->addTextElement ( "history_of_psychiatric_problems_specify", $this->indent . "If yes, specify:", array ("history_of_psychiatric_problems{@}=={@}yes" ), "This field is required." );
		$this->form->addElement ( "static", null, "<BR>" ); //line space
		
		$this->_possibleExclusionaryCriteria();

		$this->form->addElement ( "select", "other_significant_events_or_diagnosis", "Other significant events or medical diagnoses?", $this->yesNo );
	//	$this->addTextElement ( "other_significant_events_or_diagnosis_specify", $this->indent . "If yes, specify:", array ("other_significant_events_or_diagnosis{@}=={@}yes" ), "This field is required." );
                $this->addTextElement ( "other_significant_events_or_diagnosis_specify", $this->indent . "1. Specify first significant event/medical diagnosis", array ("other_significant_events_or_diagnosis{@}=={@}yes" ), "This field is required." );
                $group[] = $this->form->createElement("date", "date_event_medicaldiagnoses", null, $this->dateOptions);
                $this->dateTimeFields[] = "date_event_medicaldiagnoses"; //add to array of dates and times.
                $group[] = $this->form->createElement("select","date_event_medicaldiagnoses_status", null, array(NULL=>"", 'not_answered'=>"Not Answered"));
                $this->form->addGroup($group, "date_event_medicaldiagnoses_group", $this->indent.$this->indent."Date of first significant event/medical diagnosis", $this->_GUIDelimiter, FALSE);
                unset($group);
                $status = "date_event_medicaldiagnoses_status";
                $this->XINRegisterRule("date_event_medicaldiagnoses", array("$status{@}=={@}", "other_significant_events_or_diagnosis_specify{@}!={@}"), "A Date, not answered is required", "date_event_medicaldiagnoses_group");

                for ($i=2; $i<=5; $i++) {
                       $this->addTextElement ("other_significant_events_or_diagnosis_specify".$i, $this->indent . "$i. Specify $mapping[$i] significant event/medical diagnosis", array("other_significant_events_or_diagnosis_specify$i{@}=={@}NEVER_REQUIRED"));
                        $group[] = $this->form->createElement("date", "date_event_medicaldiagnoses".$i, null, $this->dateOptions);
                        $this->dateTimeFields[] = "date_event_medicaldiagnoses".$i; //add to array of dates and times.
                        $group[] = $this->form->createElement("select","date_event_medicaldiagnoses".$i."_status", null, array(NULL=>"", 'not_answered'=>"Not Answered"));
                        $this->form->addGroup($group, "date_event_medicaldiagnoses".$i."_group", $this->indent.$this->indent."Date of $mapping[$i] significant event/medical diagnosis", $this->_GUIDelimiter, FALSE);
                        unset($group);
                        $status = "date_event_medicaldiagnoses".$i."_status";
                        $this->XINRegisterRule("date_event_medicaldiagnoses".$i, array("$status{@}=={@}", "other_significant_events_or_diagnosis_specify$i{@}!={@}"), "A Date, not answered is required", "date_event_medicaldiagnoses".$i."_group");


               }

	       $this->form->addElement ( "static", null, "<BR>" ); //line space

                $this->form->addElement ( "select", "developmental_concerns", "Are there any developmental concerns?", $this->yesNo );
                $this->addSelect( "developmental_concerns_specify", $this->indent . "1. If there were developmental concerns pleases specify first concern:", $this->developmental_concerns,"multiple size='5'" );
                $this->XINRegisterRule("developmental_concerns_specify",array("developmental_concerns{@}=={@}yes" ),
                                       "Please specify developmental concern");
                $this->addTextElement ( "developmental_concerns_other_specify", $this->indent .$this->indent. "If other is selected, specify:", array ("developmental_concerns{@}=={@}yes", "developmental_concerns_specify{@}=={@}other" ), "This field is required." );

                $mapping = array(2=>'second',3=>'third',4=>'fourth',5=>'fifth');

                $this->addNumericElement ( "developmental_concerns_age_months", $this->indent .$this->indent. "If there were developmental concerns, please specify the age <BR>".$this->indent. $this->indent."of the child in months when these were noted:" );
                $this->XINRegisterRule("developmental_concerns_age_months", array ("developmental_concerns{@}=={@}yes" ), "Please specify age in months","developmental_concerns_age_months_group");

                $group[] = $this->form->createElement("date", "date_development_concern", null, $this->dateOptions);
                $this->dateTimeFields[] = "date_development_concern"; //add to array of dates and times.
                $group[] = $this->form->createElement("select","date_development_concern_status", null, array(NULL=>"", 'not_answered'=>"Not Answered"));
                $this->form->addGroup($group, "date_development_concern_group", $this->indent.$this->indent."Date of first developmental concern:", $this->_GUIDelimiter, FALSE);
                unset($group);
                $status = "date_development_concern_status";
                $this->XINRegisterRule("date_development_concern", array("$status{@}=={@}",
                                       "developmental_concerns_specify{@}!={@}"),
                                       "A Date, not answered is required", "date_development_concern_group");

                 for ($i=2;$i <=5;$i++) {
                   $this->addSelect( "developmental_concerns_specify".$i, $this->indent . "$i. If there were developmental concerns please specify $mapping[$i] concern:", $this->developmental_concerns,"multiple size='5'" );
                   $this->_selectMultipleElements[]= "developmental_concerns_specify".$i;
                   $this->XINRegisterRule("developmental_concerns_specify$i", array("developmental_concerns_specify$i{@}=={@}NEVER_REQUIRED"));
                   $this->addTextElement ( "developmental_concerns_other_specify".$i, $this->indent .$this->indent. "If other is selected, specify:",array("developmental_concerns_specify$i{@}=={@}other"));
                   $this->addNumericElement ( "developmental_concerns_age_months".$i, $this->indent .$this->indent. "If there were developmental concerns, please specify the age <BR>".$this->indent. $this->indent."of the child in months when these were noted:");
                   $this->XINRegisterRule("developmental_concerns_age_months".$i, array("developmental_concerns_specify$i{@}!={@}"), "Please specify age in months", "developmental_concerns_age_months".$i."_group");
                   $group[] = $this->form->createElement("date", "date_development_concern".$i, null, $this->dateOptions);
                   $this->dateTimeFields[] = "date_development_concern".$i; //add to array of dates and times.
                   $group[] = $this->form->createElement("select","date_development_concern".$i."_status", null, array(NULL=>"", 'not_answered'=>"Not Answered"));
                   $this->form->addGroup($group, "date_development_concern".$i."_group", $this->indent.$this->indent."Date of $mapping[$i] developmental concern:", $this->_GUIDelimiter, FALSE);
                   unset($group);
                   $status = "date_development_concern".$i."_status";
                   $this->XINRegisterRule("date_development_concern".$i, array("$status{@}=={@}", "developmental_concerns_specify$i{@}!={@}"), "A Date, not answered is required", "date_development_concern".$i."_group");

                }
                $this->form->addFormRule(array(&$this, 'Med_Rules'));

	}
        function _page4(){
       
        $this->form->addElement('header', null, 'Audiology');

        $this->form->addElement('header', 'instrument_title', "Audiology Evaluation Results");
        $this->addDateElement('Lastupdated_audiology', 'Date this form was last updated:', $this->dateOptions);

        $this->form->addElement ( "static", null, "<BR>" );
        $this->form->addElement("select", "not_completed", "For this participant an audiology evaluation was", array(null=>"", "complete"=>"Completed","not_complete"=>"Not Completed", "other"=>"Not Answered"));

        $config =& NDB_Config::singleton();
        $this->dateOptions = array(
                'language' => 'en',
                'format'   => 'YMd',
                'minYear'  => $config->getSetting('startYear'),
                'maxYear'  => $config->getSetting('endYear'),
                'addEmptyOption' => true,
                'emptyOptionValue' => null
                );
                $this->form->addElement ( "static", null, "<BR>" ); //line space
        $this->form->addElement("static",null,"If an audiology evaluation was completed, please provide the following information:");
        $this->addDateElement('hearing_screening', "Date of audiology evaluation:");
        $this->XINRegisterRule("hearing_screening", array("hearing_screening_date_status{@}=={@}", "not_completed{@}!={@}not_complete"), "Please specify date of hearing");

        $this->form->addElement("static", null);
        $this->form->addElement("header", null, "Methods used: (check all that apply)");
        $this->form->addElement("advcheckbox", "vra", "Visual Reinforcement Audiometry", null, null, array("unused", "used"));
        $this->form->addElement("advcheckbox", "oae", "Otoacoustic Emission Testing", null, null, array("unused", "used"));
        $this->form->addElement("advcheckbox", "tympanometry", "Tympanometry", null, null, array("unused", "used"));
        $this->form->addElement("advcheckbox", "other_method", "Other", null, null, array("unused", "used"));
        $this->addTextElement("other_method_specify", $this->indent . "Please specify", array("other_method{@}=={@}used"), "Please specify");

        $this->form->addElement("static", null);
        $this->form->addElement("header", null, "Test Results:");
        $this->form->addElement("select", "test_results", "Result", array(null=>"", "normal_hearing"=>"Normal hearing", "temporary_hearing_difficulty"=>"Temporary hearing difficulty", "equivocal_evaluation_results"=>"Equivocal evaluation results", "permanent_abnormal_hearing"=>"Permanent abnormal hearing", "not_answered"=>"Not Answered"));
        $this->XINRegisterRule("test_results", array("not_completed{@}!={@}not_complete"), "Required");
        $this->form->addElement("select", "test_results_ear", $this->indent . "Ear", array(null=>"", "left_ear"=>"Left Ear", "right_ear"=>"Right Ear", "bilateral"=>"Bilateral", "not_answered"=>"Not answered"));
        $this->XINRegisterRule("test_results_ear", array("test_results{@}!={@}normal_hearing", "not_completed{@}!={@}not_complete"), "Please specify and ear");
        $this->form->addElement("select", "test_results_severity", $this->indent . "Severity", array(null=>"", "partial"=>"Partial", "total"=>"Total", "not_answered"=>"Not Answered"));
        $this->XINRegisterRule("test_results_severity", array("test_results{@}=={@}temporary_hearing_difficulty|permanent_abnormal_hearing"), "Please indicate a severity");
        $this->addTextAreaElement("equivocal_evaluation_results_specify", $this->indent . $this->indent . "Equivocal evaluation results specify", array("test_results{@}=={@}equivocal_evaluation_results"), "This field is required for equivocal results");



    }

        function _possibleExclusionaryCriteria() {
		$this->form->addElement ( 'header', null, "Possible Exclusionary Criteria:" );
		$this->form->addElement ( "static", null, "<BR>" ); //line space
		

		$this->form->addElement ( "select", "tested_of_fragile_x", "Tested for Fragile X?", $this->yesNo );
		$this->form->addElement ( "select", "tested_of_fragile_x_result", $this->indent . "If yes, result was:", $this->normal_abnormal_FX );
		$this->XINRegisterRule ( "tested_of_fragile_x_result", array ("tested_of_fragile_x{@}=={@}yes" ), "Please indicate the Fragile X result." );
		$this->form->addElement ( "static", null, "<BR>" ); //line space
		

		$this->form->addElement ( "select", "tested_for_tuberous_sclerosis", "Tested for Tuberous Sclerosis?", $this->yesNo );
		$this->form->addElement ( "select", "tested_for_tuberous_sclerosis_result", $this->indent . "If yes, result was:", $this->normal_abnormal_TS );
		$this->XINRegisterRule ( "tested_for_tuberous_sclerosis_result", array ("tested_for_tuberous_sclerosis{@}=={@}yes" ), "Please indicate the Tuberous Sclerosis result." );
		$this->form->addElement ( "static", null, "<BR>" ); //line space
		

		$this->form->addElement ( "select", "tested_for_neurofibromatosis", "Tested for Neurofibromatosis?", $this->yesNo );
		$this->form->addElement ( "select", "tested_for_neurofibromatosis_result", $this->indent . "If yes, result was:", $this->normal_abnormal_NF );
		$this->XINRegisterRule ( "tested_for_neurofibromatosis_result", array ("tested_for_neurofibromatosis{@}=={@}yes" ), "Please indicate the Neurofibromatosis result." );
		$this->form->addElement ( "static", null, "<BR>" ); //line space
		

		$this->form->addElement ( "select", "other_genetic_tests_completed", "Other genetic tests completed?", $this->yesNo );
                $this->addTextElement ( "other_genetic_tests_completed_specify", $this->indent . "1. Specify first genetic test:", array ("other_genetic_tests_completed{@}=={@}yes" ), "This field is required." );
                $this->addTextElement ( "other_genetic_result_completed_specify", $this->indent .$this->indent . "Specify first genetic test result:", array ("other_genetic_tests_completed{@}=={@}yes" ), "This field is required." );
                $group[] = $this->form->createElement("date", "date_genetic_test", null, $this->dateOptions);
                $this->dateTimeFields[] = "date_genetic_test"; //add to array of dates and times.
                $group[] = $this->form->createElement("select","date_genetic_test_status", null, array(NULL=>"", 'not_answered'=>"Not Answered"));
                $this->form->addGroup($group, "date_genetic_test_group", $this->indent.$this->indent."Date of first genetic test", $this->_GUIDelimiter, FALSE);
                unset($group);
                $status = "date_genetic_test_status";
                $this->XINRegisterRule("date_genetic_test", array("$status{@}=={@}", "other_genetic_tests_completed_specify{@}!={@}"), "A Date, not answered is required", "date_genetic_test_group");

                $mapping = array(2=>'second',3=>'third',4=>'fourth',5=>'fifth');
                for($i=2; $i<=5; $i++) {
                        $this->addTextElement ( "other_genetic_tests_completed_specify".$i, $this->indent . "$i. Specify $mapping[$i] genetic test:", array ("other_genetic_tests_completed_specify$i{@}=={@}NEVER_REQUIRED"));
                        $this->addTextElement ( "other_genetic_result_completed_specify".$i, $this->indent .$this->indent . "Specify $mapping[$i] genetic test result:", array ("other_genetic_tests_completed_specify$i{@}=={@}NEVER_REQUIRED"));
                        $group[] = $this->form->createElement("date", "date_genetic_test".$i, null, $this->dateOptions);
                        $this->dateTimeFields[] = "date_genetic_test".$i; //add to array of dates and times.
                        $group[] = $this->form->createElement("select","date_genetic_test".$i."_status", null, array(NULL=>"", 'not_answered'=>"Not Answered"));
                        $this->form->addGroup($group, "date_genetic_test".$i."_group", $this->indent.$this->indent."Date of $mapping[$i] genetic test", $this->_GUIDelimiter, FALSE);
                        unset($group);
                        $status = "date_genetic_test".$i."_status";
                        $this->XINRegisterRule("date_genetic_test".$i, array("$status{@}=={@}", "other_genetic_tests_completed_specify$i{@}!={@}"), "A Date, not answered is required", "date_genetic_test".$i."_group");

                }


		$this->form->addElement ( "static", null, "<BR>" ); //line space
        }
	function Med_Rules($values) {
		$errors = array();
	       if(isset($values['Lastupdated_date']) && empty($values['Lastupdated_date_status'] ) ) {
         	if($values['Lastupdated_date'] < $values['Date_taken']) {
			$errors['Lastupdated_date_group'] = 'The date should be on or after Date of Administration';
		}
               }
               if($values['developmental_concerns'] == 'yes' && empty($values['developmental_concerns_specify'])) {
                        $errors['developmental_concerns_specify'] = 'Please specify the developmental concerns';
               }
		return $errors;
	}
}

?>
