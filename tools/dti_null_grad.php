<?php
set_include_path(get_include_path().":../project/libraries:../../php/libraries:");
//require_once __DIR__ . "/../vendor/autoload.php";
// path to config file
$configFile = "../project/config.xml";

require_once "NDB_Client.class.inc";
require_once "NDB_BVL_Battery.class.inc";
$client = new NDB_Client();
$client->makeCommandLine();
$client->initialize($configFile);

$db =& Database::singleton();
if(Utility::isErrorX($DB)) {
    return PEAR::raiseError("Could not connect to database: ".$DB->getMessage());
}

$file = "dti_null_list.csv";
$fp = fopen($file, "r");

while(($line = fgetcsv($fp)) !== FALSE) {
print_r($line);
}

?>
