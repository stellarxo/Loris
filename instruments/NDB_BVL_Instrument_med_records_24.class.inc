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
		$this->_doubleDataEntryDiffIgnoreColumns = array('CommentID', 'UserID', 'Testdate',  'Window_Difference', 'Candidate_Age',
								 'significant_injuries_or_illnesses_specify',
								 'significant_injuries_or_illnesses_specify_status',
								 'other_genetic_tests_completed_specify',
								 'other_genetic_tests_completed_specify_status',
								 'other_significant_events_or_diagnosis_specify',
								 'other_significant_events_or_diagnosis_specify_status',
								 'developmental_concerns_other_specify',
								 'developmental_concerns_other_specify_status',
								 'developmental_concerns_age_months_status',
								 'developmental_concerns_age_months',
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
                                 'thirtyfive_head_percentage',
                                 'hearing_screening_date_status',
                                 'comments_status',
                                 'Data_entry_completion_status');
		
	



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
        $this->form->addElement('textarea', 'comments', 'General comments:');
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
    function _linkParagraph() {
        $db = Database::singleton();
        $RecruitsEntry= $db->pselectRow("SELECT mrr.CommentID, s2.ID as sessionID, CandID FROM flag mr24 JOIN session s ON (s.ID=mr24.SessionID) LEFT JOIN candidate USING (CandID) LEFT JOIN session s2 USING (CandID) LEFT JOIN flag mrr on (s2.ID=mrr.SessionID AND mrr.Test_name='med_records_recruit') WHERE  mr24.CommentID=:CID AND mrr.CommentID IS NOT NULL AND mrr.CommentID NOT LIKE 'DDE%'", array("CID" => $this->getCommentID()));
        $this->form->addElement("static", null, "<br>");
        $this->form->addElement("static", null, "<b>Please note that previous measurements from medical records are saved in the Medical Records form for new recruits. They can be found by following: <a href=\"?test_name=med_records_recruit&commentID=$RecruitsEntry[CommentID]&sessionID=$RecruitsEntry[sessionID]&candID=$RecruitsEntry[CandID]&subtest=med_records_recruit_page2\" ><u>this link</u></a></b>.");
    }

    function _page4(){
        $this->form->addElement('header', null, 'Audiology');

        $this->form->addElement('header', 'instrument_title', "Audiology Evaluation Results");

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
        $this->XINRegisterRule("hearing_screening_date", array("hearing_screening_date_status{@}=={@}", "not_completed{@}!={@}not_complete"), "Please specify date of hearing");

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
}

?>
