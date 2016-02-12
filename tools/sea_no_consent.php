<?php
set_include_path(get_include_path().":../libraries:../../php/libraries:");
require_once "NDB_Client.class.inc";
require_once "Utility.class.inc";
require_once "Database.class.inc";
require_once "FeedbackMRI.class.inc";

//require_once "../../tools/generic_includes.php";
$client = new NDB_Client();
$client->makeCommandLine();
$client->initialize('../config.xml');

$DB =& Database::singleton();

//$file = "QCResults.csv";
$file = "SEA_NO_CONSENTS.csv";
$fp = fopen($file, "r");
$headers = fgetcsv($fp);
print_r($headers);
while(($line = fgetcsv($file)) !== FALSE) {

print_r($line);
}
?>
