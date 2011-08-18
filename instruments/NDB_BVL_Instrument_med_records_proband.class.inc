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
								 'diagnositic_setting_result_status',
								 'clinician_background_specify',
								 'clinician_background_specify_status',
								 'age_diagnosis_months',
								 'age_diagnosis_months_status',
								 'other_diagnoses_specify',
								 'other_genetic_tests_completed_specify',
								 'other_genetic_tests_completed_specify_status');
	       

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
