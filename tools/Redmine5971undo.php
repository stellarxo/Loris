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

$rows = $db->pselect("select tbl, col, old, new, primaryVals from history where tbl='head_measurements_subject' AND changeDate LIKE '2014-07-23%' AND userID='rathi' ORDER BY changeDate DESC");
foreach($rows as $row) { 
    $set = array($row['col'] => $row['old']);
    $whereQ = array('CommentID' => $row['primaryVals']);
    $db->update("head_measurements_subject", $set, $whereQ);
}
?>
