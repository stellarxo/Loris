<?php

require_once('NDB_BVL_Instrument_adi_r.class.inc');

class NDB_BVL_Instrument_adi_r_subject extends NDB_BVL_Instrument_adi_r
{
/*
INSERT INTO test_names VALUES ('', 'adi_r_subject', 'ADI-R (Subject)', '0', '1');

INSERT INTO instrument_subtests VALUES('', 'adi_r_subject', 'adi_r_subject_page1', 'Page 1', 1);

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

//         Get the proband DoB for scoring
//        $query = "SELECT DoB_proband from adir WHERE CommentID = '".$this->getCommentID()."'";
//        $result = $db->selectOne($query);
//        if(PEAR::isError($result)){
//            return PEAR::raiseError("Query has failed to select Starting Age in Months: ".$result->getMessage());
//        }
//        $probandDoB=$result;
//        
//        Get the Date of administration
//        $query = "SELECT Date_taken from adir WHERE CommentID = '".$this->getCommentID()."'";
//        $Date_taken = $db->selectOne($query);

		//For testing purposes only...
        $this->probandAgeMonths = 121;

        // setup the form
        $this->_setup($commentID, $page);

    }
    
}
?>