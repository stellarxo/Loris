<?php

require_once('NDB_BVL_Instrument_med_records.class.inc');

class NDB_BVL_Instrument_med_records_24 extends NDB_BVL_Instrument_med_records {
	/*
    INSERT INTO test_names VALUES('', 'med_records_24', 'Medical Records Data Extraction: 24 months', '0', '1');
    INSERT INTO instrument_subtests VALUES('', 'med_records_24', 'med_records_24_page1', '1. Possible Exclusionary Criteria', 1);
    INSERT INTO instrument_subtests VALUES('', 'med_records_24', 'med_records_24_page2', '2. Growth Chart Information', 2);
    INSERT INTO test_battery VALUES ('', 'med_records_24', '660', '780', 'Y', 'Visit', '1'); -- 6month recruits
    INSERT INTO test_battery VALUES ('', 'med_records_24', '660', '780', 'Y', 'Visit', '2'); -- 12month recruits
 	INSERT INTO test_battery VALUES ('', 'med_records_24', '660', '780', 'Y', 'Visit', '3'); -- controls
	*/
	
	//instrument specific variables
	var $developmental_concerns = array (null => "", 'language' => "language", 'social' => "social", 'motor' => "motor", 'other' => "other" );



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
		$this->testName = "med_records_24"; // test_names.Test_name
		$this->table = 'med_records_24'; // name of database table corresponding to instrument
		
		/**
		 * Array of column names to be ignored by the double data entry conflict detector.
		 */
		$this->_doubleDataEntryDiffIgnoreColumns = array('CommentID', 'UserID', 'Testdate',
								 'significant_injuries_or_illnesses_specify',
								 'significant_injuries_or_illnesses_specify_status',
								 'other_genetic_tests_completed_specify',
								 'other_genetic_tests_completed_specify_status',
								 'other_significant_events_or_diagnosis_specify',
								 'other_significant_events_or_diagnosis_specify_status',
								 'developmental_concerns_other_specify',
								 'developmental_concerns_other_specify_status',
								 'developmental_concerns_age_months_status',
								 'developmental_concerns_age_months');
		
	



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
		$this->form->addElement ( 'header', 'instrument_title', "Medical Records Data Extraction: 24 months" );
		
        // automatically adds examiner & date of administration
        $this->_addMetadataFields();
	}
	
	function _page1() {
		$this->form->addElement ( "select", "significant_injuries_or_illnesses", "Has the infant had any significant injuries or illnesses (e.g., head injury, high fevers, seizures)?", $this->yesNo );
		$this->addTextElement ( "significant_injuries_or_illnesses_specify", $this->indent . "If yes, specify:", array ("significant_injuries_or_illnesses{@}=={@}yes" ), "This field is required." );
		$this->form->addElement ( "static", null, "<BR>" ); //line space
		
		$this->_possibleExclusionaryCriteria();
		
		$this->form->addElement ( "select", "other_significant_events_or_diagnosis", "Other significant events or medical diagnoses?", $this->yesNo );
		$this->addTextElement ( "other_significant_events_or_diagnosis_specify", $this->indent . "If yes, specify:", array ("other_significant_events_or_diagnosis{@}=={@}yes" ), "This field is required." );
		$this->form->addElement ( "static", null, "<BR>" ); //line space

		$this->form->addElement ( "select", "developmental_concerns", "Are there any developmental concerns?", $this->yesNo );
		$this->form->addElement ( "select", "developmental_concerns_specify", $this->indent . "If there were developmental concerns please specify them:", $this->developmental_concerns );
		
		$this->XINRegisterRule ( "developmental_concerns_specify", array ("developmental_concerns{@}=={@}yes" ), "Please specify the developmental concerns:" );
		
		$this->form->addElement ( "static", null, "<BR>" ); //line space
		

		$this->addTextElement ( "developmental_concerns_other_specify", $this->indent . "If other is selected, specify:", array ("developmental_concerns{@}=={@}yes", "developmental_concerns_specify{@}=={@}other" ), "This field is required." );
		
		$this->form->addelement ( "static", null, "<BR>" );
		
		$this->addTextElement ( "developmental_concerns_age_months", $this->indent . "If there were developmental concerns, please specify the age of the child in months when these were noted:", array ("developmental_concerns{@}=={@}yes" ), "This field is required." );
		
		$this->form->addElement ( "static", null, "$this->double_indent <BR/>" ); //line space
		

		$this->form->addElement ( "static", null, "<BR>" ); //line space
	}
}

?>
