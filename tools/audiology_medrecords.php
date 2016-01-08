<?php
set_include_path(get_include_path().":../libraries:../../php/libraries:");
require_once "NDB_Menu_statistics.class.inc";
require_once "NDB_Client.class.inc";
require_once "Utility.class.inc";
require_once "Database.class.inc";
//require_once "../../tools/generic_includes.php";
$client = new NDB_Client();
$client->makeCommandLine();
$client->initialize('../config.xml');


$CommentID = $argv[1];
$db        =& Database::singleton();
if (Utility::isErrorX($db)) {
        print "Could not connect to database: " . $db->getMessage();
            exit(1);
}
$query         = "SELECT distinct(s.ID),c.CandID, a.CommentID from audiology a JOIN flag f on (f.CommentID = a.CommentID) 
                  JOIN session s on (s.ID = f.SessionID) join candidate c on (c.CandID = s.CandID ) 
                  WHERE c.CenterID <> 1";
$record        = array();
$record        = $db->pselect($query);
if (Utility::isErrorX($record)) {
        print "Query has failed to select: ".$record->getMessage();
            exit(2);
}
foreach($record as $row){

    $cid = $row['CandID'];
    $session = $row['ID'];
    print "SESSION $session \n";
    $aud_commentid = $row['CommentID'];
    $query_med = "SELECT m.CommentID from med_records_24 m join flag f on f.CommentID = m.CommentID 
                  WHERE f.sessionID = :sid"; 
    $where = array('sid'=> $session);
    $result_med = $db->pselectRow($query_med, $where); 
    if (Utility::isErrorX($result_med)) {
                print "Query has failed to select: ".$record->getMessage();
       //                     exit(2);
    }
    print_r($result_med);
    $med_commentid = $result_med['CommentID'];
    $query_aud = "SELECT * from audiology where CommentID= :cmid";
    $where_p   = array('cmid' => $aud_commentid);
    $record_aud = $db->pselectRow($query_aud, $where_p);
    if (Utility::isErrorX($record)) {
            print "Query has failed to select: ".$record->getMessage();
     //           exit(2);
    }
    $fieldstoupdate = array(1=>'not_completed',2=>'not_completed_other_specify',3=>'not_completed_other_specify_status',4=>'hearing_screening_date',5=>'hearing_screening_date_status',6=>'vra',7=>'oae',8=>'tympanometry',9=>'other_method',10=>'other_method_specify',11=>'other_method_specify_status',12=>'test_results',13=>'test_results_ear',14=>'test_results_severity',15=>'equivocal_evaluation_results_specify',16=>'equivocal_evaluation_results_specify_status');
    $addData = array();
    foreach($fieldstoupdate as $num=>$val){
        if($val == 'not_completed'){
            if($record_aud[$val] == 'non-asd'){
                $addData[$val] = 'not_complete'; 
            } else {
                $addData[$val] = $record_aud[$val];
            }
        }else {
            $addData[$val] = $record_aud[$val];
        }
    }
    $WhereCriteria = array('CommentID'=> $med_commentid);
    if($addData != null & $WhereCriteria != null){
        $result = $db->update('med_records_24', $addData, $WhereCriteria);
    }

}




?>
