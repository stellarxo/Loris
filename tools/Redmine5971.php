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
$result = $db->pselect("SELECT t.CommentID, s.Visit_label, s.CandID from neuro_screen t join flag f ON f.CommentID = t.CommentID join session s on s.ID = f.SessionID WHERE f.Data_entry='Complete' AND t.CommentID LIKE 'DDE_%' and s.CenterID<>1", array());
foreach($result as $row) { 
$vl = $row['Visit_label'];
$candID = $row['CandID'];
//print "Neuro - ". $row['CommentID'];
$head_id = $db->pselectOne("SELECT t.CommentID from head_measurements_subject t join flag f ON f.CommentID = t.CommentID join session s on s.ID = f.SessionID WHERE f.Data_entry='Complete' AND t.CommentID LIKE 'DDE_%' AND s.CandID = $candID AND s.Visit_label='$vl' AND s.CenterID <> 1", array());
if(!empty($head_id)) {
    $cid = $row['CommentID'];
    $neuro = $db->pselectRow("SELECT q22_child_hc_cm,q22_child_hc_cm_status,q22_mother_hc_cm,q22_mother_hc_cm_status,q22_father_hc_cm,q22_father_hc_cm_status,q22_mother_height_cm,q22_mother_height_cm_status,q22_father_height_cm,q22_father_height_cm_status,q22_mother_weight_kg,q22_mother_weight_kg_status,q22_father_weight_kg,q22_father_weight_kg_status FROM neuro_screen Where CommentID = '$cid'", array());
//print_r($neuro); 
$vals = array('head_circumference_unit'=>'cm','head_circumference1'=>$neuro['q22_child_hc_cm'],'head_circumference1_status'=>$neuro['q22_child_hc_cm_status'],'head_circumference_unit_mother'=>'cm','head_circumference1_mother'=>$neuro['q22_mother_hc_cm'],'head_circumference1_mother_status'=>$neuro['q22_mother_hc_cm_status'],'head_circumference_unit_father'=>'cm','head_circumference1_father'=>$neuro['q22_father_hc_cm'],'head_circumference1_father_status'=>$neuro['q22_father_hc_cm_status'],'length1_mother'=>$neuro['q22_mother_height_cm'],'length1_mother_status'=>$neuro['q22_mother_height_cm_status'],'length1_father'=>$neuro['q22_father_height_cm'],'length1_father_status'=>$neuro['q22_father_height_cm_status'],'weight1_mother'=>$neuro['q22_mother_weight_kg'],'weight1_mother_status'=>$neuro['q22_mother_weight_kg_status'],'weight_unit_mother'=>'kg','weight_unit_father'=>'kg', 'weight1_father'=>$neuro['q22_father_weight_kg'],'weight1_father_status'=>$neuro['q22_father_weight_kg_status'],'head_length_unit_father'=>'cm','head_length_unit_mother'=>'cm');
print "CommentID - ".$head_id."\n";

//save scores
  if ($db->isError($result)) {
        print "Could not save total score: ". $result->getMessage();
//        exit(3);
    }
}
}
?>
