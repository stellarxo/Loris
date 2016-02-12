<?php

set_include_path(get_include_path().":../libraries:../../php/libraries:");
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
$query = "select c.PSCID,c.candID, c.IBISID, p.ndar_consent, p.ndar_consent_date,
          p.ndar_consent_withdrawal,p.study_consent,po.Description 
          from candidate c join participant_status p on p.CandID=c.candID 
          join participant_status_options po on po.ID=p.participant_status 
          where p.ndar_consent='no' and c.CenterID<>1 and c.Active='Y'";

$result = $db->pselect($query, array());
foreach($result as $row){
	$dir = "NDAR_2015";
	$dh  = opendir($dir);
	while (false !== ($filename = readdir($dh))) {
		$file = file_get_contents($dir."/".$filename); 
		preg_match_all ('/'.$row['IBISID'].'/', $file, $matches);
                foreach($matches as $val) {
                    if(!empty($val)) {
		        echo "matched: " . $val[0] . "\n";
                    }
                }
	}
}
?>
