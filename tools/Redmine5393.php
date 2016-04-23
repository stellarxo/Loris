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
$result = $db->pselect("select s.CandID, c.PSCID, f.CommentID from candidate c join session s on s.CandID=c.CandID join flag f on f.SessionID=s.ID WHERE f.Test_name='RSMS' AND s.CenterID=3 AND c.ProjectID=1", array());
foreach($result as $row) { 
$vals = array('Data_entry'=>'Complete', 'Administration'=>'None');
$Where = array('CommentID'=>$row['CommentID']);
//save scores
   $result = $db->update('flag', $vals, $Where);
    if ($db->isError($result)) {
        print "Could not save total score: ". $result->getMessage();
//        exit(3);
    }
}
?>
