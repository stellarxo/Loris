#!/usr/bin/php
<?

/*
Compare tsting script
*/

set_include_path(get_include_path().":../../php/libraries:");
require_once "NDB_Client.class.inc";

$client = new NDB_Client();
$client->makeCommandLine();
$client->initialize('../config.xml');
require_once "ConflictDetector.class.inc";

$db =& Database::singleton();


$instrument_name=$argv[0];


$instance_pairs = getInstancePairsForInstrument($instrument_name);

require_once "../../project/instruments/NDB_BVL_Instrument_".$instrument_name.".class.inc";

foreach($instance_pairs AS $instance_pair) {
    print "Checking $instrument_name $instance_pair[0]\n";
    ConflictDetector::clearConflictsForInstance($instance_pair[0]);
    $diff=ConflictDetector::detectConflictsForCommentIds($instrument_name, $instance_pair[0], $instance_pair[1]);
    ConflictDetector::recordUnresolvedConflicts($diff);
}


function getInstancePairsForInstrument($instrument_name) {
    $db =& Database::singleton();

    $query = "SELECT CommentID, CONCAT('DDE_', CommentID) AS DDECommentID FROM flag where Test_name='$instrument_name' and LEFT(CommentID, 3) != 'DDE'";
    $db->select($query, $instances);

    $instance_pairs = array();

    foreach($instances AS $instance) {
        $instance_pairs[] = array($instance['CommentID'], $instance['DDECommentID']);
    }

    return $instance_pairs;
}

?>
