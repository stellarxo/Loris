<?php

require_once('NDB_BVL_Instrument_vineland.class.inc');

class NDB_BVL_Instrument_vineland_subject extends NDB_BVL_Instrument_vineland
{
/*
INSERT INTO test_names VALUES ('', 'vineland_subject', 'Vineland II ABS (Subject)', '0', '1');
INSERT INTO test_battery VALUES ('', 'vineland_subject', '1050', '1140', 'Y', 'Visit', '3');
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
        $this->testName = "vineland_subject";           // test_names.Test_name
        $this->table = 'vineland_subject';              // name of database table corresponding to instrument
    
        $this->_setup($commentID, $page);
    }
    
}
?>