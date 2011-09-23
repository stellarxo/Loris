<?
set_include_path(get_include_path().":../libraries:../../php/libraries:");
require_once "NDB_Client.class.inc";
require_once "Utility.class.inc";

$client = new NDB_Client();
$client->makeCommandLine();
$client->initialize('../config.xml');

$DB =& Database::singleton();
$SessionIDs = $DB->pselect("SELECT session.ID FROM session JOIN candidate USING (CandID) WHERE session.Active='Y' and candidate.Active='Y' AND candidate.PSCID <> 'scanner'", array());

foreach ($SessionIDs as $row) {
    Utility::SetSupplementalGrantStatus($row['ID']);
}
?>
