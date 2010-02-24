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
		
		$this->_doubleDataEntryDiffIgnoreColumns = array('CommentID', 'UserID', 'Testdate',
								 'significant_notes_during_pregnancy_or_delivery_specify',
								 'significant_notes_during_pregnancy_or_delivery_specify_status',
								 'significant_injuries_or_illnesses_specify',
								 'significant_injuries_or_illnesses_specify_status',
								 'history_of_psychiatric_problems_specify',
								 'history_of_psychiatric_problems_specify_status',
								 'other_genetic_tests_completed_specify',
								 'other_genetic_tests_completed_specify_status',
								 'other_significant_events_or_diagnosis_specify',
								 'other_significant_events_or_diagnosis_specify_status',
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
	}
	
	function _page1() {
		$this->form->addElement ( "select", "significant_notes_during_pregnancy_or_delivery", "Anything significant noted during pregnancy or delivery?", $this->yesNo );
		$this->addTextElement ( "significant_notes_during_pregnancy_or_delivery_specify", $this->indent . "If yes, specify:", array ("significant_notes_during_pregnancy_or_delivery{@}=={@}yes" ), "This field is required." );
		$this->form->addElement ( "static", null, "<BR>" ); //line space
		

		$this->form->addElement ( "select", "significant_injuries_or_illnesses", "Has the infant had any significant injuries or illnesses (e.g., head injury, high fevers, seizures)?", $this->yesNo );
		$this->addTextElement ( "significant_injuries_or_illnesses_specify", $this->indent . "If yes, specify:", array ("significant_injuries_or_illnesses{@}=={@}yes" ), "This field is required." );
		$this->form->addElement ( "static", null, "<BR>" ); //line space
		

		$this->form->addElement ( "select", "history_of_psychiatric_problems", "Any history of relatives with Schizophrenia, Bipolar Disorder, Intellectual Disability or Psychosis?", $this->yesNo );
		$this->addTextElement ( "history_of_psychiatric_problems_specify", $this->indent . "If yes, specify:", array ("history_of_psychiatric_problems{@}=={@}yes" ), "This field is required." );
		$this->form->addElement ( "static", null, "<BR>" ); //line space
		
		$this->_possibleExclusionaryCriteria();

		$this->form->addElement ( "select", "other_significant_events_or_diagnosis", "Other significant events or medical diagnoses?", $this->yesNo );
		$this->addTextElement ( "other_significant_events_or_diagnosis_specify", $this->indent . "If yes, specify:", array ("other_significant_events_or_diagnosis{@}=={@}yes" ), "This field is required." );
		$this->form->addElement ( "static", null, "<BR>" ); //line space
	}
}

?>
