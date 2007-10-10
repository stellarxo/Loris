<?php

require_once('NDB_BVL_Instrument_scq.class.inc');

class NDB_BVL_Instrument_scq_proband extends NDB_BVL_Instrument_scq
{
/*
INSERT INTO test_names VALUES ('', 'scq_proband', 'SCQ (Proband)', '0', '1');

INSERT INTO instrument_subtests VALUES('', 'scq_proband', 'scq_proband_page1', 'Page 1', 1);

INSERT INTO test_battery VALUES ('', 'scq_proband', '1050', '1140', 'Y', 'Visit', '3');

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
        $this->testName = "scq_proband";           // test_names.Test_name
        $this->table = 'scq_proband';              // name of database table corresponding to instrument

        $this->_setup($commentID, $page);
    }
}
?>
