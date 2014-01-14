<?php
set_include_path(get_include_path().":../libraries:../../php/libraries:");
//require_once "NDB_Menu_statistics.class.inc";
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
$candidate_list = $db->pselect("SELECT c.CandID FROM candidate c JOIN session s ON (s.CandID=c.CandID) WHERE 
                   s.Visit_label='V36' AND s.SubprojectID IN (9,10) AND c.PSCID NOT LIKE 'DCC%'");
foreach($candidate_list as $candidate) {
    $query         = "SELECT informant.CommentID as Informant ,respondent.CommentID as Respondent 
                      FROM flag f JOIN bapq_respondent respondent on (f.CommentID = e.CommentID)
                      JOIN session s on (s.ID = f.SessionID) WHERE s.CandID = $candidate";
    $record        = array();
    $record        = $db->pselect($query, array());
    if (Utility::isErrorX($record)) {
        print "Query has failed to select: ".$record->getMessage();
        //        exit(2);
    }
}
