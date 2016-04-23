<?php
set_include_path(get_include_path().":../libraries:../../php/libraries:");
require_once "NDB_Client.class.inc";
require_once "Utility.class.inc";
require_once "Database.class.inc";
//require_once "../../tools/generic_includes.php";
$client = new NDB_Client();
$client->makeCommandLine();
$client->initialize('../config.xml');


//$CommentID = $argv[1];
$db        =& Database::singleton();
if (Utility::isErrorX($db)) {
        print "Could not connect to database: " . $db->getMessage();
            exit(1);
}
$result = $db->pselect("SELECT CandID from candidate WHERE CenterID IN (2,3,4) ", array());
$status = $db->pselect("SELECT CandID from participant_status", array());
$candid = array();
foreach($status as $row) {
$candid[] = $row['CandID'];
/*
$result_ps = $db->insert('participant_status_history', array('participant_status'=>$row['participant_status'],
                                                             'participant_subOptions'=>$row['participant_suboptions'],
                                                             'CandID'=>$row['CandID']) );
if (Utility::isErrorX($result_ps)) {
        print "Query has failed to insert: ".$result_ps->getMessage();
        //        exit(2);
}

$consent = $db->insert('consent_info_history', array('CandID'=>$row['CandID'],
                                                      'study_consent'=>$row['study_consent'],
                                                       'study_consent_date'=>$row['study_consent_date'],
                                                       'study_consent_withdrawal'=>$row['study_consent_withdrawal'],
                                                       'ndar_consent'=>$row['ndar_consent'],
                                                       'ndar_consent_date'=>$row['ndar_consent_date'],
                                                       'ndar_consent_withdrawal'=>$row['ndar_consent_withdrawal']));

if (Utility::isErrorX($consent)) {
        print "Query has failed to insert: ".$consent->getMessage();
        //        exit(2);
}  
*/
   
}
foreach($result as $row) {
 if(!in_array($row['CandID'], $candid)) {
   $result = $db->insert('participant_status', array('CandID'=>$row['CandID'],
                                                     'participant_status'=>1));
   if (Utility::isErrorX($result)) {
        print "Query has failed to insert: ".$result->getMessage();
        //        exit(2);
   }
   $result1 = $db->insert('participant_status_history', array('CandID'=>$row['CandID'],
                                                              'participant_status'=>1));
   if (Utility::isErrorX($result1)) {
        print "Query has failed to insert: ".$result1->getMessage();
        //        exit(2);
   }


}

}

?>
