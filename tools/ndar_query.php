<?php
set_include_path(get_include_path().":../libraries:../../php/libraries:");
require_once "NDB_Client.class.inc";
$client = new NDB_Client();
$client->makeCommandLine();
$client->initialize('../config.xml');
require_once "Database.class.inc";
require_once "Utility.class.inc";
require_once "NDAR_Release_2015.class.inc";
$db        =& Database::singleton();
if (Utility::isErrorX($db)) {
        print "Could not connect to database: " . $db->getMessage();
            exit(1);
}
$IBIS = array('m_chat_proband');
/*$IBIS = array ('adi_r_proband', 'aosi','aosi','csbs','edi','fyi','ibq_r','m_chat_proband','macarthur_words_gestures','mullen','prefrontal_task','rbs_r',
               'scq_proband','scq_subject','seq','vineland_proband','vineland_subject','charge');*/
foreach($IBIS as $instrument) {
    $run = new NDAR_Release_2015 ($instrument, 1);
    $run->run();
}
/*
$IBIS2 = array('adi_r_proband','aosi','csbs','head_measurements_subject','ibq_r','macarthur_words_gestures','m_chat_proband','scq_proband','mullen',
               'rbs_r','vineland_proband', 'charge');
*/
$IBIS2 = array('m_chat_proband');
foreach($IBIS2 as $instrument) {
    $run = new NDAR_Release_2015 ($instrument, 2);
    $run->run();

}
?>
