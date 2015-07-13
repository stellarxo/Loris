<?php

require_once('NDB_BVL_Instrument_vineland.class.inc');

class NDB_BVL_Instrument_vineland_proband extends NDB_BVL_Instrument_vineland
{
/*
-- INSERT INTO test_names VALUES ('', 'vineland_proband', 'Vineland II ABS (Proband)', '0', '1');

INSERT INTO instrument_subtests VALUES('', 'vineland_proband', 'vineland_proband_page1', 'Communication Domain - Receptive', 1);
INSERT INTO instrument_subtests VALUES('', 'vineland_proband', 'vineland_proband_page2', 'Communication Domain - Expressive', 2);
INSERT INTO instrument_subtests VALUES('', 'vineland_proband', 'vineland_proband_page3', 'Communication Domain - Written', 3);
INSERT INTO instrument_subtests VALUES('', 'vineland_proband', 'vineland_proband_page4', 'Daily Living Skills Domain - Personal', 4);
INSERT INTO instrument_subtests VALUES('', 'vineland_proband', 'vineland_proband_page5', 'Daily Living Skills Domain - Domestic', 5);
INSERT INTO instrument_subtests VALUES('', 'vineland_proband', 'vineland_proband_page6', 'Daily Living Skills Domain - Community', 6);
INSERT INTO instrument_subtests VALUES('', 'vineland_proband', 'vineland_proband_page7', 'Socialization Domain - Interpersonal Relationships', 7);
INSERT INTO instrument_subtests VALUES('', 'vineland_proband', 'vineland_proband_page8', 'Socialization Domain - Play and Leisure Time', 8);
INSERT INTO instrument_subtests VALUES('', 'vineland_proband', 'vineland_proband_page9', 'Socialization Domain - Coping Skills', 9);
INSERT INTO instrument_subtests VALUES('', 'vineland_proband', 'vineland_proband_page10', 'Motor Skills Domain - Gross', 10);
INSERT INTO instrument_subtests VALUES('', 'vineland_proband', 'vineland_proband_page11', 'Motor Skills Domain - Fine', 11);
INSERT INTO instrument_subtests VALUES('', 'vineland_proband', 'vineland_proband_page12', 'Maladaptive Behaviour Index - Internalizing/Externalizing', 12);
INSERT INTO instrument_subtests VALUES('', 'vineland_proband', 'vineland_proband_page13', 'Maladaptive Behaviour Index - Other', 13);
INSERT INTO instrument_subtests VALUES('', 'vineland_proband', 'vineland_proband_page14', 'Maladaptive Behaviour Index - Critical Items', 14);
INSERT INTO instrument_subtests VALUES('', 'vineland_proband', 'vineland_proband_page15', 'About the Interview', 15);

-- INSERT INTO test_battery VALUES ('', 'vineland_proband', '1050', '1140', 'Y', 'Visit', '3');
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
        $this->testName = "vineland_proband";           // test_names.Test_name
        $this->table = 'vineland_proband';              // name of database table corresponding to instrument
    
        $this->_setup($commentID, $page);
    }
    
}
?>