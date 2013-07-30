<?php

require_once('NDB_BVL_Instrument_head_measurements.class.inc');

class NDB_BVL_Instrument_head_measurements_proband extends NDB_BVL_Instrument_head_measurements
{
/*
INSERT INTO test_names VALUES ('', 'head_measurements_proband', 'Head Measurements (Proband)', '0', '1');
INSERT INTO test_battery VALUES ('', 'head_measurements_proband', '1050', '1140', 'Y', 'Visit', '3');
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
        $this->testName = "head_measurements_proband";           // test_names.Test_name
        $this->table = 'head_measurements_proband';              // name of database table corresponding to instrument
        $this->_doubleDataEntryDiffIgnoreColumns = array('CommentID', 'UserID', 'Testdate', 'Window_Difference', 
                                                         'Candidate_Age','Data_entry_completion_status', 
                                                         'head_circumference1_status','head_circumference2_status',
                                                         'length1_status','length2_status','weight1_status',
                                                         'weight2_status');        
        $this->_setup($commentID, $page);
    }   
}
?>
