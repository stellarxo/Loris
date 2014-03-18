<?php
set_include_path(get_include_path().":../libraries:../../php/libraries:");
require_once "NDB_Client.class.inc";
require_once "QC_Checks.class.inc";
require_once "NDB_Config.class.inc";

$config =& NDB_Config::singleton("../config.xml");
$config->load("../config.xml");
$client = new NDB_Client();
$client->makeCommandLine();
$client->initialize('../config.xml');

// get a Database connection
$dbConfig = $config->getSetting('database');
$DB = new Database;
$result = $DB->connect($dbConfig['database'], $dbConfig['username'], $dbConfig['password'], $dbConfig['host'], false);
if(PEAR::isError($result)) {
        die("Could not connect to database: ".$result->getMessage());
}
if($argv) {
	$run = new QC_Checks($argv[1]);
	$run->run();
}
?>
