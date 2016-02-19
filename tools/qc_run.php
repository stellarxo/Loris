<?php
set_include_path(get_include_path().":../libraries:../../php/libraries:");

require_once "../../vendor/autoload.php";
require_once "NDB_Client.class.inc";
require_once "QC_Checks.class.inc";
require_once "NDB_Config.class.inc";


$client = new NDB_Client();
$client->makeCommandLine();
$client->initialize('../config.xml');

$factory = NDB_Factory::singleton();
$config = $factory->config('../config.xml');

if($argv) {
	$run = new QC_Checks($argv[1]);
	$run->run();
}
?>
