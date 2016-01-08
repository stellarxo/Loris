<?php

require_once 'HTML/QuickForm.php';
require_once 'HTML/QuickForm/Renderer/Array.php';
require_once 'NDB_BVL_Instrument_m_chat.class.inc';

class NDB_BVL_Instrument_m_chat_subject extends NDB_BVL_Instrument_m_chat
{
	/*
	INSERT INTO test_names VALUES ('', 'm_chat_subject', 'M-CHAT (Subject)', '0', '1');

	INSERT INTO instrument_subtests VALUES('', 'm_chat_subject', 'm_chat_page1', 'Questions', 1);

	INSERT INTO test_battery VALUES ('', 'm_chat_subject', '1050', '1140', 'Y', 'Visit', '3');
	CHANGE FOR ZAPHOD!!!
	*/

	/**
    * sets up basic data, such as the HTML_Quickform object, and so on.
    *
    * @param string $commentID  the CommentID identifying the data to load
    * @param string $page       if a multipage form, the page to show
    * @return void
    * @access public
    */
	function setup($commentID, $page){
		$this->formType="XIN";
		$this->form = new HTML_Quickform('test_form');
		$this->page = $page;            // page label (number or
		// string - used by
		// user-defined child classes)

		// set the object properties
		$this->testName = "m_chat_subject";           // test_names.Test_name
		$this->table = 'm_chat_subject';              // name of database table corresponding to instrument
		// data keyed by commentID
		$this->commentID = $commentID;

		//The array of dates/timestamps to convert to database dates/timestamps
		//Any HTML_Quickform date elements must be listed here
		$this->dateTimeFields=array("Date_taken");

		//The array of selects with multiple answers allowed
		//Any HTML_Quickform multiple selects must be listed here
		$this->_selectMultipleElements = array();

		// required fields for data entry completion status
		$this->_requiredElements = array('Examiner', "q1_swung_on_knee");
        
        $this->_doubleDataEntryDiffIgnoreColumns = array('CommentID', 'UserID', 'Testdate', 'Window_Difference', 'Candidate_Age','Data_entry_completion_status','total_item_fails','total_critical_fails','score');

		// setup the form
		$this->_setupForm();

	}

}
?>
