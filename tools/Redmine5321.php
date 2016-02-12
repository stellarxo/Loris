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
//$result = $db->pselect("SELECT userID from user_perm_rel WHERE permID=9", array());
//foreach($result as $row) { 
$vals = array('hash'=>md5('candidate_parameters'),'topic'=>'Candidate Information','content'=>'Under construction');
//save scores
  $result = $db->insert('help', $vals);
  if ($db->isError($result)) {
        print "Could not save total score: ". $result->getMessage();
//        exit(3);
    }
//}
?>
