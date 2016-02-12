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

$file = fopen('/home/rathi/tsi_primarylang_update.csv','r');

while(($line = fgetcsv($file)) !== FALSE) {
//print_r($line);
$comtID = $db->pselectOne("SELECT f.CommentID from flag f JOIN session s on s.ID = f.SessionID JOIN candidate c on c.CandID = s.CandID WHERE f.Test_name=:tname AND c.CandID=:cid", array('cid'=>$line[0],'tname'=>'tsi'));
$vals = array('primary_language'=>$line[2]);
$Where = array('CommentID'=>$comtID);
//save scores
//   $result = $db->update('tsi', $vals, $Where);
    if ($db->isError($result)) {
        print "Could not save total score: ". $result->getMessage();
//        exit(3);
    }
 
}
?>
