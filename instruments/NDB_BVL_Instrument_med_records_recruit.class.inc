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
		
		$this->_doubleDataEntryDiffIgnoreColumns = array('CommentID', 'UserID', 'Testdate',  'Window_Difference', 'Candidate_Age','Data_entry_completion_status',
								 'sig_notes_during_pregnancy_or_delivery_specify',
								 'sig_notes_during_pregnancy_or_delivery_specify_status',
								 'significant_injuries_or_illnesses_specify',
								 'significant_injuries_or_illnesses_specify_status',
								 'history_of_psychiatric_problems_specify',
								 'history_of_psychiatric_problems_specify_status',
								 'other_genetic_tests_completed_specify',
								 'other_genetic_tests_completed_specify_status',
								 'other_significant_events_or_diagnosis_specify',
								 'other_significant_events_or_diagnosis_specify_status',
                                 'first_measurement_date_status',
                                 'first_measurement_length_units_stat',
                                 'first_percentage_length',
                                 'first_measurement_weight_units_stat',
                                 'first_weight_percentage',
                                 'first_measurement_head_units_stat',
                                 'first_head_percentage',
                                 'second_measurement_date_status',
                                 'second_measurement_length_units_stat',
                                 'second_percentage_length',
                                 'second_measurement_weight_units_stat',
                                 'second_weight_percentage',
                                 'second_measurement_head_units_stat',
                                 'second_head_percentage',
                                 'third_measurement_date_status',
                                 'third_measurement_length_units_stat',
                                 'third_percentage_length',
                                 'third_measurement_weight_units_stat',
                                 'third_weight_percentage',
                                 'third_measurement_head_units_stat',
                                 'third_head_percentage',
                                 'fourth_measurement_date_status',
                                 'fourth_measurement_length_units_stat',
                                 'fourth_percentage_length',
                                 'fourth_measurement_weight_units_stat',
                                 'fourth_weight_percentage',
                                 'fourth_measurement_head_units_stat',
                                 'fourth_head_percentage',
                                 'fifth_measurement_date_status',
                                 'fifth_measurement_length_units_stat',
                                 'fifth_percentage_length',
                                 'fifth_measurement_weight_units_stat',
                                 'fifth_weight_percentage',
                                 'fifth_measurement_head_units_stat',
                                 'fifth_head_percentage',
                                 'sixth_measurement_date_status',
                                 'sixth_measurement_length_units_stat',
                                 'sixth_percentage_length',
                                 'sixth_measurement_weight_units_stat',
                                 'sixth_weight_percentage',
                                 'sixth_measurement_head_units_stat',
                                 'sixth_head_percentage',
                                 'seventh_measurement_date_status',
                                 'seventh_measurement_length_units_stat',
                                 'seventh_percentage_length',
                                 'seventh_measurement_weight_units_stat',
                                 'seventh_weight_percentage',
                                 'seventh_measurement_head_units_stat',
                                 'seventh_head_percentage',
                                 'eighth_measurement_date_status',
                                 'eighth_measurement_length_units_stat',
                                 'eighth_percentage_length',
                                 'eighth_measurement_weight_units_stat',
                                 'eighth_weight_percentage',
                                 'eighth_measurement_head_units_stat',
                                 'eighth_head_percentage',
                                 'ninth_measurement_date_status',
                                 'ninth_measurement_length_units_stat',
                                 'ninth_percentage_length',
                                 'ninth_measurement_weight_units_stat',
                                 'ninth_weight_percentage',
                                 'ninth_measurement_head_units_stat',
                                 'ninth_head_percentage',
                                 'tenth_measurement_date_status',
                                 'tenth_measurement_length_units_stat',
                                 'tenth_percentage_length',
                                 'tenth_measurement_weight_units_stat',
                                 'tenth_weight_percentage',
                                 'tenth_measurement_head_units_stat',
                                 'tenth_head_percentage',
                                 'eleventh_measurement_date_status',
                                 'eleventh_measurement_length_units_stat',
                                 'eleventh_percentage_length',
                                 'eleventh_measurement_weight_units_stat',
                                 'eleventh_weight_percentage',
                                 'eleventh_measurement_head_units_stat',
                                 'eleventh_head_percentage',
                                 'twelfth_measurement_date_status',
                                 'twelfth_measurement_length_units_stat',
                                 'twelfth_percentage_length',
                                 'twelfth_measurement_weight_units_stat',
                                 'twelfth_weight_percentage',
                                 'twelfth_measurement_head_units_stat',
                                 'twelfth_head_percentage',
                                 'thirteenth_measurement_date_status',
                                 'thirteenth_measurement_length_units_stat',
                                 'thirteenth_percentage_length',
                                 'thirteenth_measurement_weight_units_stat',
                                 'thirteenth_weight_percentage',
                                 'thirteenth_measurement_head_units_stat',
                                 'thirteenth_head_percentage',
                                 'fourteenth_measurement_date_status',
                                 'fourteenth_measurement_length_units_stat',
                                 'fourteenth_percentage_length',
                                 'fourteenth_measurement_weight_units_stat',
                                 'fourteenth_weight_percentage',
                                 'fourteenth_measurement_head_units_stat',
                                 'fourteenth_head_percentage',
                                 'fifteenth_measurement_date_status',
                                 'fifteenth_measurement_length_units_stat',
                                 'fifteenth_percentage_length',
                                 'fifteenth_measurement_weight_units_stat',
                                 'fifteenth_weight_percentage',
                                 'fifteenth_measurement_head_units_stat',
                                 'fifteenth_head_percentage',
                                 'sixteenth_measurement_date_status',
                                 'sixteenth_measurement_length_units_stat',
                                 'sixteenth_percentage_length',
                                 'sixteenth_measurement_weight_units_stat',
                                 'sixteenth_weight_percentage',
                                 'sixteenth_measurement_head_units_stat',
                                 'sixteenth_head_percentage',
                                 'seventeenth_measurement_date_status',
                                 'seventeenth_measurement_length_units_stat',
                                 'seventeenth_percentage_length',
                                 'seventeenth_measurement_weight_units_stat',
                                 'seventeenth_weight_percentage',
                                 'seventeenth_measurement_head_units_stat',
                                 'seventeenth_head_percentage',
                                 'eighteenth_measurement_date_status',
                                 'eighteenth_measurement_length_units_stat',
                                 'eighteenth_percentage_length',
                                 'eighteenth_measurement_weight_units_stat',
                                 'eighteenth_weight_percentage',
                                 'eighteenth_measurement_head_units_stat',
                                 'eighteenth_head_percentage',
                                 'nineteenth_measurement_date_status',
                                 'nineteenth_measurement_length_units_stat',
                                 'nineteenth_percentage_length',
                                 'nineteenth_measurement_weight_units_stat',
                                 'nineteenth_weight_percentage',
                                 'nineteenth_measurement_head_units_stat',
                                 'nineteenth_head_percentage',
                                 'twenty_measurement_date_status',
                                 'twenty_measurement_length_units_stat',
                                 'twenty_percentage_length',
                                 'twenty_measurement_weight_units_stat',
                                 'twenty_weight_percentage',
                                 'twenty_measurement_head_units_stat',
                                 'twenty_head_percentage',
                                 'twentyone_measurement_date_status',
                                 'twentyone_measurement_length_units_stat',
                                 'twentyone_percentage_length',
                                 'twentyone_measurement_weight_units_stat',
                                 'twentyone_weight_percentage',
                                 'twentyone_measurement_head_units_stat',
                                 'twentyone_head_percentage',
                                 'twentytwo_measurement_date_status',
                                 'twentytwo_measurement_length_units_stat',
                                 'twentytwo_percentage_length',
                                 'twentytwo_measurement_weight_units_stat',
                                 'twentytwo_weight_percentage',
                                 'twentytwo_measurement_head_units_stat',
                                 'twentytwo_head_percentage',
                                 'twentythree_measurement_date_status',
                                 'twentythree_measurement_length_units_stat',
                                 'twentythree_percentage_length',
                                 'twentythree_measurement_weight_units_stat',
                                 'twentythree_weight_percentage',
                                 'twentythree_measurement_head_units_stat',
                                 'twentythree_head_percentage',
                                 'twentyfour_measurement_date_status',
                                 'twentyfour_measurement_length_units_stat',
                                 'twentyfour_percentage_length',
                                 'twentyfour_measurement_weight_units_stat',
                                 'twentyfour_weight_percentage',
                                 'twentyfour_measurement_head_units_stat',
                                 'twentyfour_head_percentage',
                                 'twentyfive_measurement_date_status',
                                 'twentyfive_measurement_length_units_stat',
                                 'twentyfive_percentage_length',
                                 'twentyfive_measurement_weight_units_stat',
                                 'twentyfive_weight_percentage',
                                 'twentyfive_measurement_head_units_stat',
                                 'twentyfive_head_percentage',
                                 'twentysix_measurement_date_status',
                                 'twentysix_measurement_length_units_stat',
                                 'twentysix_percentage_length',
                                 'twentysix_measurement_weight_units_stat',
                                 'twentysix_weight_percentage',
                                 'twentysix_measurement_head_units_stat',
                                 'twentysix_head_percentage',
                                 'twentyseven_measurement_date_status',
                                 'twentyseven_measurement_length_units_stat',
                                 'twentyseven_percentage_length',
                                 'twentyseven_measurement_weight_units_stat',
                                 'twentyseven_weight_percentage',
                                 'twentyseven_measurement_head_units_stat',
                                 'twentyseven_head_percentage',
                                 'twentyeight_measurement_date_status',
                                 'twentyeight_measurement_length_units_stat',
                                 'twentyeight_percentage_length',
                                 'twentyeight_measurement_weight_units_stat',
                                 'twentyeight_weight_percentage',
                                 'twentyeight_measurement_head_units_stat',
                                 'twentyeight_head_percentage',
                                 'twentynine_measurement_date_status',
                                 'twentynine_measurement_length_units_stat',
                                 'twentynine_percentage_length',
                                 'twentynine_measurement_weight_units_stat',
                                 'twentynine_weight_percentage',
                                 'twentynine_measurement_head_units_stat',
                                 'twentynine_head_percentage',
                                 'thirty_measurement_date_status',
                                 'thirty_measurement_length_units_stat',
                                 'thirty_percentage_length',
                                 'thirty_measurement_weight_units_stat',
                                 'thirty_weight_percentage',
                                 'thirty_measurement_head_units_stat',
                                 'thirty_head_percentage',
                                 'thirtyone_measurement_date_status',
                                 'thirtyone_measurement_length_units_stat',
                                 'thirtyone_percentage_length',
                                 'thirtyone_measurement_weight_units_stat',
                                 'thirtyone_weight_percentage',
                                 'thirtyone_measurement_head_units_stat',
                                 'thirtyone_head_percentage',
                                 'thirtytwo_measurement_date_status',
                                 'thirtytwo_measurement_length_units_stat',
                                 'thirtytwo_percentage_length',
                                 'thirtytwo_measurement_weight_units_stat',
                                 'thirtytwo_weight_percentage',
                                 'thirtytwo_measurement_head_units_stat',
                                 'thirtytwo_head_percentage',
                                 'thirtythree_measurement_date_status',
                                 'thirtythree_measurement_length_units_stat',
                                 'thirtythree_percentage_length',
                                 'thirtythree_measurement_weight_units_stat',
                                 'thirtythree_weight_percentage',
                                 'thirtythree_measurement_head_units_stat',
                                 'thirtythree_head_percentage',
                                 'thirtyfour_measurement_date_status',
                                 'thirtyfour_measurement_length_units_stat',
                                 'thirtyfour_percentage_length',
                                 'thirtyfour_measurement_weight_units_stat',
                                 'thirtyfour_weight_percentage',
                                 'thirtyfour_measurement_head_units_stat',
                                 'thirtyfour_head_percentage',
                                 'thirtyfive_measurement_date_status',
                                 'thirtyfive_measurement_length_units_stat',
                                 'thirtyfive_percentage_length',
                                 'thirtyfive_measurement_weight_units_stat',
                                 'thirtyfive_weight_percentage',
                                 'thirtyfive_measurement_head_units_stat',
                                 'thirtyfive_head_percentage');
								 
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
	}
	
	function _page1() {
		$this->form->addElement ( "select", "significant_notes_during_pregnancy_or_delivery", "Anything significant noted during pregnancy or delivery?", $this->yesNo );
		$this->addTextElement ( "sig_notes_during_pregnancy_or_delivery_specify", $this->indent . "If yes, specify:", array ("significant_notes_during_pregnancy_or_delivery{@}=={@}yes" ), "This field is required." );
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
