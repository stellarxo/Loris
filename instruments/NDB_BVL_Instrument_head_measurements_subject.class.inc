<?php

require_once('NDB_BVL_Instrument_head_measurements.class.inc');

class NDB_BVL_Instrument_head_measurements_subject extends NDB_BVL_Instrument_head_measurements
{
/*
INSERT INTO test_names VALUES ('', 'head_measurements_subject', 'Head Measurements (Subject)', '0', '1');
INSERT INTO test_battery VALUES ('', 'head_measurements_subject', '1050', '1140', 'Y', 'Visit', '3');
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
        $this->testName = "head_measurements_subject";           // test_names.Test_name
        $this->table = 'head_measurements_subject';              // name of database table corresponding to instrument
        
        $this->_setup($commentID, $page);
    }   
}
?>