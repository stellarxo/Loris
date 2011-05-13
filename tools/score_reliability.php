<?
require_once("./generic_includes.php");
require_once("Console/Getopt.php");
if($argc < 2) {
    print "Usage: $argv[0] instrument [--blind|-b]\n";
    exit(-1);
}
$instrument = $argv[1];
array_shift($argv);

$parser = new Console_Getopt();
$args = $parser->readPHPArgv();
array_shift($args);
$opts = $parser->getopt($args, 'b', array('blind'));
foreach ($opts[0] as $opt) {
    switch($opt[0]) {
        case '--blind':
        case 'b':
            $blind = 1;
            break;
        default: break;
    }
}
if($blind) {
    print "Rescoring blind coding\n\n";
    $_REQUEST['blind'] = 1;
}
$instrument_name = "NDB_Reliability_$instrument";
if(!file_exists("../libraries/NDB_Reliability_$instrument" . "_reliability.class.inc")) {
    print "Instrument $instrument does not have reliability coding\n";
    exit(-2);
}
require_once("NDB_Reliability.class.inc");
require_once("NDB_Reliability_$instrument" . "_reliability.class.inc");

if($blind) {
    $CommentIDs = $DB->pselect("SELECT f.CommentID FROM flag f JOIN blind_coding r ON (r.CommentID=f.CommentID) WHERE f.Test_name=:Instrument", array('Instrument' => $instrument));
} else {
    $CommentIDs = $DB->pselect("SELECT f.CommentID FROM flag f JOIN reliability r ON (r.CommentID=f.CommentID) WHERE f.Test_name=:Instrument", array('Instrument' => $instrument));
}

function GetCenterID($CommentID) {
    global $DB;
    global $blind;
    if($blind) {
        $ret = $DB->pselectOne("SELECT reliability_center_id FROM blind_coding WHERE CommentID=:CID", array('CID' => $CommentID));
    } else {
        $ret = $DB->pselectOne("SELECT reliability_center_id FROM reliability WHERE CommentID=:CID", array('CID' => $CommentID));
    }
    return $ret;
}
foreach ($CommentIDs as $row) {
    $CommentID = $row['CommentID'];
    print "Scoring $CommentID\n";
    $inst = NDB_Reliability::factory($instrument . "_reliability", '', $CommentID, GetCenterID($CommentID));
    $inst->score();
    print "Scored $CommentID";
    $inst->save();
}

?>
