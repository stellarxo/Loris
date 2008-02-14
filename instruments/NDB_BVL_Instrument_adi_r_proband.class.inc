<?php

require_once('NDB_BVL_Instrument_adi_r.class.inc');

class NDB_BVL_Instrument_adi_r_proband extends NDB_BVL_Instrument_adi_r
{
/*
These SQL's are for testing purposes only and do not represent actual database values

INSERT INTO test_names VALUES ('', 'adi_r_proband', 'ADI-R (Proband)', '0', '1');

INSERT INTO instrument_subtests VALUES('', 'adi_r_proband', 'adi_r_proband_page1', 'Background', 1);
INSERT INTO instrument_subtests VALUES('', 'adi_r_proband', 'adi_r_proband_page2', 'Early Development', 2);
INSERT INTO instrument_subtests VALUES('', 'adi_r_proband', 'adi_r_proband_page3', 'Acquisition/Loss of Language', 3);
INSERT INTO instrument_subtests VALUES('', 'adi_r_proband', 'adi_r_proband_page4', 'General Loss of Skills', 4);
INSERT INTO instrument_subtests VALUES('', 'adi_r_proband', 'adi_r_proband_page5', 'Language and Communication Functioning - Page 1', 5);
INSERT INTO instrument_subtests VALUES('', 'adi_r_proband', 'adi_r_proband_page6', 'Language and Communication Functioning - Page 2', 6);
INSERT INTO instrument_subtests VALUES('', 'adi_r_proband', 'adi_r_proband_page7', 'Social Development and Play - Page 1', 7);
INSERT INTO instrument_subtests VALUES('', 'adi_r_proband', 'adi_r_proband_page8', 'Social Development and Play - Page 2', 8);
INSERT INTO instrument_subtests VALUES('', 'adi_r_proband', 'adi_r_proband_page9', 'Interests and Behaviours', 9);
INSERT INTO instrument_subtests VALUES('', 'adi_r_proband', 'adi_r_proband_page10', 'General Behaviours', 10);
INSERT INTO instrument_subtests VALUES('', 'adi_r_proband', 'adi_r_proband_page11', 'Special Isolated Skills', 11);

INSERT INTO test_battery VALUES ('', 'adi_r_proband', '1050', '1140', 'Y', 'Visit', '3');

DoB Proband should be somewhere in the candidate table.  For now, we'll just make it a form entry.  Will need quite a large range of dates as probands may be quite old.

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
        $this->testName = "adi_r_proband";           // test_names.Test_name
        $this->table = 'adi_r_proband';              // name of database table corresponding to instrument


        // setup the form
        $this->_setup($commentID, $page);

    }
    
    function score() {
                
        $db =& Database::singleton();
        if(PEAR::isError($db)) {
            return PEAR::raiseError ("Could not connect to database: ".$db->getMessage());
        }

        // Get the proband DoB from the field in the form for age-dependent scoring
        $query = "SELECT DoB_proband from $this->testName WHERE CommentID = '".$this->getCommentID()."'";
        $DoB_proband = $db->selectOne($query);
        if(PEAR::isError($DoB_proband)){
            return PEAR::raiseError("Query has failed to select Starting Age in Months: ".$result->getMessage());
        }
        
        // Get the Date of administration
        $query = "SELECT Date_taken from $this->testName WHERE CommentID = '".$this->getCommentID()."'";
        $Date_taken = $db->selectOne($query);
        if(PEAR::isError($Date_taken)){
            return PEAR::raiseError("Query has failed to select the Date of Administration: ".$result->getMessage());
        }

		$age = Utility::calculateAge($DoB_proband, $Date_taken);
        if($this->isError($age)) {
            return $this->raiseError("Could not compute age");
        }

		$this->respondentAgeMonths = $age['year'] * 12 + $age['$mon'];

		//For testing purposes only...
//		$this->respondentAgeMonths = 121;
        
		// call the subclass scoring method
        $this->_score();
    }
}
?>