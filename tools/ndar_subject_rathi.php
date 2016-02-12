<?php
set_include_path(get_include_path().":../libraries:../../php/libraries:");
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
$project = array(1=>'IBIS1');
foreach($project as $key=>$val) { 
$query = "SELECT c.IBISID, s.CenterID as Site, CASE s.SubprojectID WHEN 1 THEN 'High Risk' WHEN 2 THEN 'High Risk' WHEN 3 THEN 'Low Risk' WHEN 9 THEN 'High Risk' WHEN 10 THEN 'Low Risk' END as Cohort, c.ProbandGUID,  c.ProbandGender, c.CandidateGUID, c.Gender, i.Date_taken,ROUND(DATEDIFF(i.Date_taken, c.DoB) / (365/12)) AS Candidate_Age_in_Months, i.Date_taken,ROUND(DATEDIFF(i.Date_taken, c.ProbandDoB) / (365/12)) AS Proband_Age_in_Months, i.Candidate_race as race, i.child_ethnicity as ethnic_group, f.CommentID,f.Data_entry,f.Administration from candidate c left join session s on s.CandID = c.CandID left join flag f on f.SessionID = s.ID left join tsi i on i.CommentID=f.CommentID join participant_status ps on ps.CandID = c.CandID WHERE COALESCE(s.Current_stage, '') <> 'Recycling Bin' AND COALESCE(s.Visit, '') NOT IN ('Failure', 'Withdrawal') AND COALESCE(s.Screening, '') NOT IN ('Failure', 'Withdrawal') AND EXISTS (SELECT 'x' FROM flag df WHERE df.CommentID=CONCAT('DDE_', i.CommentID)) AND NOT EXISTS (SELECT 'x' FROM conflicts_unresolved cu WHERE cu.CommentId1=i.CommentID OR cu.CommentId2=i.CommentID) AND s.CenterID IN (2, 3, 4, 5) AND ( ps.study_consent = 'yes' AND ps.study_consent_withdrawal IS NULL ) AND (ps.ndar_consent = 'yes' AND ps.ndar_consent_withdrawal IS NULL) and c.ProjectID = $key AND COALESCE(c.CandidateGUID, '') <> ''";
//print $query;
$record = array();
$record = $db->pselect($query, array());
if (Utility::isErrorX($record)) {
        print "Query has failed to select: ".$record->getMessage();
        //        exit(2);
}
 $filename = "ndar_subject_".$val.".csv";
  $fd = fopen($filename, 'w+');
  if ($fd === FALSE) {
    exit(-1);
  }
 $header1 = array('ndar_subject01');
 fputcsv($fd, $header1);
 $headers = array('IBISID','SubjectKey','Gender','Site','Cohort','Candidate_Age_in_Months','Date_taken','family_study','race','ethnic_group',
                  'twins_study','sibling_study','sample_taken','phenotype_description','subjectkey_sibling1','src_sibling1_id','sibling_type1');
 fputcsv($fd, $headers);
 $data = array('twins_populate'=>'No','sibling_study'=>'Yes','family_study'=>'No','sample_taken'=>'No');
 foreach($record as $row) {
 $row = array_merge($row,$data);
 $DD_Entry = $db->pselectOne("SELECT Data_entry FROM flag Where CommentID=:cid", array('cid'=>'DDE_'.$row['CommentID']));
 foreach($row as $key=>$val){
	 if(strpos($key, 'Date_taken') !== FALSE || $key == 'DoB' || strpos($key, 'Date_Taken') !== FALSE) {
		 //print "VAL: $val";
		 $Date = explode('-', $val); //print_r($Date);
		 $row[$key] = $Date[1] . '/' . '01' . '/' . $Date[0];
	 }
 } 
 if($row['Candidate_Age_in_Months'] < 0){
    $row['Candidate_Age_in_Months'] =0;
 }
 $type='';
 $type_pr ='';
 if($row['ProbandGender']== 'Male') {
   $type = "Full Brother FB";
 } else if($row['ProbandGender'] == 'Female'){
   $type = "Full Sister FS";
  } else {
    $type = " ";
   }
 if($row['Gender']== 'Male') {
   $type_pr = "Full Brother FB";
 } else if($row['Gender'] == 'Female'){
   $type_pr = "Full Sister FS";
  }
 $race = $row['race'];
 if (empty($race) || $DD_Entry != 'Complete' || $row['Data_entry'] != 'Complete' || $row['Administration'] != 'All') {
	 $race_final ="999";
 } else {

	 if(strpos($race,'more_than_one_race') !== FALSE){
		 $race_final = "More than one race";
	 } else { 
		 if(strpos($race,'white') !== FALSE){
			 $race_final = "White";
		 } else  if(strpos($race,'asian') !== FALSE){
			 $race_final = "Asian";
		 } else if(strpos($race,'black_african_american') !== FALSE){
			 $race_final = "Black or African American";
		 } else if(strpos($race,'white') !== FALSE){
			 $race_final = "White";
		 } 
	 }
 }
if(empty($row['ethnic_group']) || $DD_Entry != 'Complete'|| $row['Data_entry'] != 'Complete' || $row['Administration'] != 'All' ) {
    $row['ethnic_group'] ="999";
}
 $candidate = array($row['IBISID'], $row['CandidateGUID'], $row['Gender'], $row['Site'], $row['Cohort'], $row['Candidate_Age_in_Months'], $row['Date_taken'],
                    'No',$race_final,$row['ethnic_group'],'No','Yes','No', $row['Cohort']." Sibling",$row['ProbandGUID'],$row['IBISID']."pr", $type);
 
 fputcsv($fd, $candidate);
 if(!empty($row['ProbandGUID'])){
     $proband   = array($row['IBISID']."pr", $row['ProbandGUID'], $row['ProbandGender'], $row['Site'], "Proband", $row['Proband_Age_in_Months'], $row['Date_taken'],
                    'No',"Unknown or not reported","Unknown or not reported",'No','Yes','No', "Proband of Sibling",$row['CandidateGUID'], $row['IBISID'], $type_pr);
     fputcsv($fd, $proband);
  }	
 }
}
?>
