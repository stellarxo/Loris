<?php

require_once('NDB_BVL_Instrument_med_records.class.inc');

class NDB_BVL_Instrument_med_records_proband extends NDB_BVL_Instrument_med_records {
	/*
    INSERT INTO test_names VALUES('', 'med_records_proband', 'Medical Records Data Extraction: Proband', '0', '1');
    INSERT INTO instrument_subtests VALUES('', 'med_records_proband', 'med_records_proband_page1', '1. Possible Exclusionary Criteria', 1);
    INSERT INTO instrument_subtests VALUES('', 'med_records_proband', 'med_records_proband_page2', '2. Growth Chart Information', 2);
    INSERT INTO test_battery VALUES ('', 'med_records_proband', '150', '270', 'Y', 'Visit', '1'); -- 6month recruit
    INSERT INTO test_battery VALUES ('', 'med_records_proband', '300', '420', 'Y', 'Visit', '2'); -- 12month recruit
    */
	
	//instrument specific variables
	var $yesNoNA = array (null => "", 'yes' => "Yes", 'no' => "No", 'not_answered' => "Not Answered" );
	var $clinician = array (null => "", "pediatrician" => "Pediatrician", "neurologist" => "Neurologist", "psychologist" => "Psychologist", "teacher" => "Teacher", 'specialist' => "Specialist", "other" => "Other", 'not_answered' => "Not Answered" );
	var $diagnosis = array (null => "", 'autism' => "Autism", 'asd' => "ASD", 'pdd_nos' => "PDD-NOS", 'aspergers' => "Asperger's Disorder", 'not_answered' => "Not Answered" );
	var $known = array (null => "", 'unknown' => "unknown" );
	var $diagnosticSetting = array (null => "", 'medical_center' => "Medical Center", 'multidisciplinary' => "Multidisciplinary", 'birth_to_three' => "Birth to Three", 'schools' => "Schools", 'other' => "Other", 'not_answered' => "Not Answered" );
	
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
		$this->testName = "med_records_proband"; // test_names.Test_name
		$this->table = 'med_records_proband'; // name of database table corresponding to instrument
		
		$this->_doubleDataEntryDiffIgnoreColumns = array('CommentID', 'UserID', 'Testdate',  'Window_Difference', 'Candidate_Age',
								 'diagnositic_setting_result',
								 'clinician_background_specify',
								 'age_diagnosis_months',
								 'other_diagnoses_specify',
								 'other_genetic_tests_completed_specify'
                                 'Data_entry_completion_status',
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
		$this->form->addElement ( 'header', 'instrument_title', "Medical Records Data Extraction: Proband" );
		
		// automatically adds examiner & date of administration
		$this->_addMetadataFields ();
		$this->form->addElement ( 'textarea', 'comments', "General comments:" );
	}
	
	function _page1() {
		$this->form->addElement ( "select", "confirmed_diagnosis", "1. Confirmation of Diagnosis", $this->diagnosis );
		$this->form->addRule ( "confirmed_diagnosis", "This field is required.", 'required' );
		$this->form->addElement ( "static", null, "<BR>" ); //line space
		

		$this->form->addElement ( "select", "diagnostic_setting", "2. Diagnostic setting:", $this->diagnosticSetting );
		$this->addTextElement ( "diagnositic_setting_result", $this->indent . "If other is selected please specify:", array ("diagnostic_setting{@}=={@}other" ), "This field is required." );
		$this->form->addElement ( "static", null, "<BR>" ); //line space
		

		$this->form->addElement ( "select", "clinician_background", "3. Diagnosing Clinician Background:", $this->clinician );
		$this->addTextElement ( "clinician_background_specify", $this->indent . "If other, specify:", array ("clinician_background{@}=={@}other" ), "This field is required." );
		$this->form->addElement ( "static", null, "<BR>" ); //line space
		

		$this->form->addElement ( "select", "age_diagnoses", "4. Age at diagnosis known?", $this->yesNo );
		
		$this->form->addElement ( "static", null, "<BR>" );
		
		$this->addTextElement ( "age_diagnosis_months", $this->indent . "Please specify the age of the child in months when the diagnosis was made:", array ("age_diagnoses{@}=={@}yes" ), "This field is required otherwise select not answered." );
		
		$this->form->addElement ( "static", null, "<BR>" );
		
		$this->form->addElement ( "select", "other_diagnoses", "5. Other diagnoses received?", $this->yesNo );
		$this->form->addElement ( "text", "other_diagnoses_specify", $this->indent . "If yes, specify what test and result:" );
		$this->XINRegisterRule ( "other_diagnoses_specify", array ("other_diagnoses{@}=={@}yes" ), "Please specify the other diagnoses." );
		
		$this->_possibleExclusionaryCriteria();
	}
}

?>
