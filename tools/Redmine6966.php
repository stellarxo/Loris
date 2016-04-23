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
$file = fopen('ibis_consent.csv','r');

while(($line = fgetcsv($file)) !== FALSE) {
//print_r($line);
$query         = "SELECT CandID FROM candidate
                  WHERE PSCID='$line[0]'";
$record        = array();
$record        = $db->pselectOne($query, array());

$consent_status = $db->pselectRow("SELECT CandID, study_consent, study_consent_date
                                   FROM participant_status WHERE CandID=:cid", array('cid'=>$record));
//print_r($consent_status);
$date = explode('.', $line[2]);
$month = str_pad($date[0], 2, '0', STR_PAD_LEFT);
$day = str_pad($date[1], 2, '0', STR_PAD_LEFT);
$date_consent = $date[2]."-".$month."-".$day;
$vals = array('study_consent'=>'yes', 'study_consent_date'=>$date_consent,  'CandID'=>$record);
$Where = array('CandID'=>$record);
$success = $DB->delete("consent_info_history",$Where);
$ParticipantCount = $DB->pselectOne(
		"SELECT study_consent_date FROM consent_info_history WHERE CandID = :cid",
		array("cid"=>$record)
		);
print " HERE $date_consent $ParticipantCount for $record \n";
$vals = array('study_consent'=>'yes', 'study_consent_date'=>$date_consent);
if (empty($ParticipantCount)) {
print "No DATE for the candidate $record \n";
} else {

}
$vals = array('study_consent'=>'yes', 'study_consent_date'=>$date_consent, 'CandID'=>$record);
$success = $DB->insert("consent_info_history",$vals);

/*
if ($ParticipantCount > 0) {
	$success = $DB->update(
			"participant_status",
			$vals,
			array("CandID"=>$record)
			);
} else {
	//insert it
        $vals = array('study_consent'=>'yes', 'study_consent_date'=>$date_consent, 'CandID'=>$record);
	$success = $DB->insert("participant_status",$vals);
}
*/
//$db->insert('participant_status', $vals);
}

?>
