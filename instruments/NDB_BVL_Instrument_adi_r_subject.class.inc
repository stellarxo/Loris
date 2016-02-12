<?php

require_once("Utility.class.inc");
require_once("ProjectUtility.class.inc");
require_once('NDB_BVL_Instrument_adi_r.class.inc');

class NDB_BVL_Instrument_adi_r_subject extends NDB_BVL_Instrument_adi_r
{
/*
These SQL's are for testing purposes only and do not represent actual database values

INSERT INTO test_names VALUES ('', 'adi_r_subject', 'ADI-R (Subject)', '0', '1');

INSERT INTO instrument_subtests VALUES('', 'adi_r_subject', 'adi_r_subject_page1', 'Background', 1);
INSERT INTO instrument_subtests VALUES('', 'adi_r_subject', 'adi_r_subject_page2', 'Early Development', 2);
INSERT INTO instrument_subtests VALUES('', 'adi_r_subject', 'adi_r_subject_page3', 'Acquisition/Loss of Language', 3);
INSERT INTO instrument_subtests VALUES('', 'adi_r_subject', 'adi_r_subject_page4', 'General Loss of Skills', 4);
INSERT INTO instrument_subtests VALUES('', 'adi_r_subject', 'adi_r_subject_page5', 'Language and Communication Functioning - Page 1', 5);
INSERT INTO instrument_subtests VALUES('', 'adi_r_subject', 'adi_r_subject_page6', 'Language and Communication Functioning - Page 2', 6);
INSERT INTO instrument_subtests VALUES('', 'adi_r_subject', 'adi_r_subject_page7', 'Social Development and Play - Page 1', 7);
INSERT INTO instrument_subtests VALUES('', 'adi_r_subject', 'adi_r_subject_page8', 'Social Development and Play - Page 2', 8);
INSERT INTO instrument_subtests VALUES('', 'adi_r_subject', 'adi_r_subject_page9', 'Interests and Behaviours', 9);
INSERT INTO instrument_subtests VALUES('', 'adi_r_subject', 'adi_r_subject_page10', 'General Behaviours', 10);
INSERT INTO instrument_subtests VALUES('', 'adi_r_subject', 'adi_r_subject_page11', 'Special Isolated Skills', 11);

INSERT INTO test_battery VALUES ('', 'adi_r_subject', '1050', '1140', 'Y', 'Visit', '3');

DoB subject should be somewhere in the candidate table.  For now, we'll just make it a form entry.  Will need quite a large range of dates as subjects may be quite old.

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
        // set the object properties
        $this->testName = "adi_r_subject";           // test_names.Test_name
        $this->table = 'adi_r_subject';              // name of database table corresponding to instrument

        // setup the form
        $this->_setup($commentID, $page);

    }
    
    function score() {
        
        $db =& Database::singleton();

        //skip scoring if all data has not yet been entered.
        if($this->_determineDataEntryCompletionStatus() == "Incomplete") {
        	return;
        }
        
        $this->_getAge();
        
		// call the subclass scoring method
        $this->_score();
        ProjectUtility::SetSupplementalGrantStatus($this->getSessionID());
    }
    
    function _getAge() {
        $db =& Database::singleton();

        // Get the subject DoB for scoring
        if($this->getSessionID() != NULL) { //quickform_parser doesn't use any specific session
            $timepoint =& TimePoint::singleton($this->getSessionID());
            $dob = $timepoint->getEffectiveDateOfBirth();
        }
        
        // Get the Date of administration
        $query = "SELECT Date_taken from $this->testName WHERE CommentID = '".$this->getCommentID()."'";
        $Date_taken = $db->selectOne($query);

        if(empty($dob) || empty($Date_taken)) {
            $age = -1;
        } else { 
            $age = Utility::calculateAge($dob, $Date_taken); 
        }
        

        //Diagnostic algorithm uses age in years.
//		$this->respondentAgeMonths = $age['year'] * 12 + $age['$mon'];
        $this->respondentAgeYears = $age['year'] + ($age['mon'] / 12) + ($age['day'] / 30 / 12);
        
    }
}
?>
