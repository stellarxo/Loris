<?php
set_include_path(get_include_path().":../libraries:../../php/libraries:");
require_once "NDB_Client.class.inc";
require_once "Utility.class.inc";
require_once "Database.class.inc";
//require_once "../../tools/generic_includes.php";
$client = new NDB_Client();
$client->makeCommandLine();
$client->initialize('../config.xml');


$db        =& Database::singleton();
if (Utility::isErrorX($db)) {
        print "Could not connect to database: " . $db->getMessage();
            exit(1);
}
$project = array(1=>'IBIS1',2=>'IBIS2');
$query = "SELECT distinct c.IBISID,c.PSCID,c.CandID as DCCID,  c.CandidateGUID,s.CenterID as Site, s.SubprojectID , c.ProbandGUID,  c.ProbandGender,c.ProjectID from candidate c 
          join session s ON s.CandID = c.CandID 
          join participant_status ps on ps.CandID = c.CandID
          WHERE COALESCE(s.Current_stage, '') <> 'Recycling Bin' AND COALESCE(s.Visit, '') NOT IN ('Failure', 'Withdrawal') 
          AND COALESCE(s.Screening, '') NOT IN ('Failure', 'Withdrawal')
         AND s.CenterID IN (2, 3, 4, 5) AND ( ps.study_consent = 'yes' AND ps.study_consent_withdrawal IS NULL ) AND (ps.ndar_consent = 'yes' AND ps.ndar_consent_withdrawal IS NULL ) AND COALESCE(c.CandidateGUID, '') <> '' ORDER BY c.ProjectID";
print $query;
$record = array();
$record = $db->pselect($query, array());
if (Utility::isErrorX($record)) {
        print "Query has failed to select: ".$record->getMessage();
        //        exit(2);
}
 $filename = "ndar_subject_IDs.csv";
  $fd = fopen($filename, 'w+');
  if ($fd === FALSE) {
    exit(-1);
  }
$headers = array('IBISID','PSCID','DCCID','CandidateGUID','Site','SubprojectID','ProbandGUID','ProbandGender','ProjectID');
 fputcsv($fd, $headers);
foreach($record as $candidate) {
fputcsv($fd, $candidate);
}
?>
