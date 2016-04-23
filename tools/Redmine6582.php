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


$query1 = "SELECT c.CandID, c.PSCID, s.Visit_label, f.CommentID from flag f join session s on s.ID=f.SessionID join candidate c on c.CandID=s.CandID WHERE c.CenterID=4 AND f.test_name='HandPreference' AND (f.Data_entry IS NULL AND f.Administration IS NULL) AND c.ProjectID=1";
$record1 = array();
$record1  = $db->pselect($query1, array());
foreach($record1 as $row) { 
	print $row['CandID']."-".$row['PSCID']."-".$row['CommentID']."-".$row['Visit_label']."\n";
	$vals = array('Administration'=>'None', 'Data_entry'=>'Complete' );
	$Where = array('CommentID'=>$row['CommentID']);
	//save scores
	$result = $db->update('flag', $vals, $Where);
	if ($db->isError($result)) {
		print "Could not save total score: ". $result->getMessage();
		//        exit(3);
	}
}
?>
