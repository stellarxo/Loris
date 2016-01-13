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
//$vals = array('participant_status'=>3,'reason_specify'=>'Half sib with autism.  No full sib.','reason_specify_status'=>NULL,'participant_subOptions'=>NULL);
//$vals = array('participant_status'=>5,'participant_subOptions'=>10,'study_consent'=>'yes','study_consent_date'=>'2009-04-13','reason_specify'=>'Candidate did not want to keep coming in because they could not get 2 hotel nights guaranteed.');
//$vals = array('participant_status'=>2,'reason_specify'=>'Unresponsive about scheduling FIGS');
$vals = array('study_consent'=>'yes','ndar_consent'=>'no','study_consent_date'=>'2010-11-30');
$Where = array('CandID'=>694335);
//print_r($Where);
//save scores
   $result = $db->update('participant_status', $vals, $Where);
//   $result1 = $db->update('consent_info_history', $vals1, $Where);
    if ($db->isError($result)) {
        print "Could not save total score: ". $result->getMessage();
//        exit(3);
    }
/*
$result = $db->pselect("SELECT study_consent,CandID FROM consent_info_history WHERE study_consent IS NULL order by ID desc limit 1", array());
print_r($result);
foreach($result as $row) {
print "####".$row['CandID'];
    $value = $db->pselect("SELECT participant_status,participant_suboptions,reason_specify FROM participant_status_history WHERE CandID=:cid order by ID desc limit 1", array('cid'=>$row['CandID']));
    foreach($value as $one) {
    
    $Where = array('CandID'=>$row['CandID']);
    $results = $db->update('participant_status', array('participant_status'=>$one['participant_status'], 'participant_suboptions'=>$one['participant_suboptions'],'reason_specify'=>$one['reason_specify']), $Where);
     if ($db->isError($results)) {
        print "Could not save total score: ". $results->getMessage();
//        exit(3);
    }
   }
}
*/
?>
