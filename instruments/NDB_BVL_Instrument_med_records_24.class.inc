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
        $this->form->addElement("static", null, "<b>Please note that previous measurements from medical records are saved in the Medical Records form for new recruits. They can be found by following <a href=\"?test_name=med_records_recruit&commentID=$RecruitsEntry[CommentID]&sessionID=$RecruitsEntry[sessionID]&candID=$RecruitsEntry[CandID]&subtest=med_records_recruit_page2\">this link</a></b>.");
    }

    function _page4(){
        $this->form->addElement('header', null, 'Audiology');

        $this->form->addElement('header', 'instrument_title', "Audiology Evaluation Results");

        $this->form->addElement("select", "not_completed", "Status of audiology evaluation for this participant", array(null=>"", "complete"=>"Completed","not_complete"=>"Not Completed", "other"=>"Other (please specify)"));
        $this->XINRegisterRule("not_completed", array("not_completed{@}=={@}NEVER_REQUIRED"));
        $this->addTextElement("not_completed_other_specify", $this->indent . "If other, please specify", array("not_completed{@}=={@}other"), "Please specify.");

        $config =& NDB_Config::singleton();
        $this->dateOptions = array(
                'language' => 'en',
                'format'   => 'YMd',
                'minYear'  => $config->getSetting('startYear'),
                'maxYear'  => $config->getSetting('endYear'),
                'addEmptyOption' => true,
                'emptyOptionValue' => null
                );
        $this->addDateElement('hearing_screening', "Date of audiology evaluation:");
        $this->XINRegisterRule("hearing_screening_date", array("hearing_screening_date_status{@}=={@}", "not_completed{@}!={@}non-asd"), "Please specify date of hearing");

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
        $this->XINRegisterRule("test_results", array("not_completed{@}!={@}non-asd"), "Required");
        $this->form->addElement("select", "test_results_ear", $this->indent . "Ear", array(null=>"", "left_ear"=>"Left Ear", "right_ear"=>"Right Ear", "bilateral"=>"Bilateral", "not_answered"=>"Not answered"));
        $this->XINRegisterRule("test_results_ear", array("test_results{@}!={@}normal_hearing", "not_completed{@}!={@}non-asd"), "Please specify and ear");
        $this->form->addElement("select", "test_results_severity", $this->indent . "Severity", array(null=>"", "partial"=>"Partial", "total"=>"Total", "not_answered"=>"Not Answered"));
        $this->XINRegisterRule("test_results_severity", array("test_results{@}=={@}temporary_hearing_difficulty|permanent_abnormal_hearing"), "Please indicate a severity");
        $this->addTextAreaElement("equivocal_evaluation_results_specify", $this->indent . $this->indent . "Equivocal evaluation results specify", array("test_results{@}=={@}equivocal_evaluation_results"), "This field is required for equivocal results");



    }
}

?>
