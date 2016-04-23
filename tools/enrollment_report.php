<?php
set_include_path(get_include_path().":../libraries:../../php/libraries:");
require_once "NDB_Menu_statistics.class.inc";
require_once "NDB_Client.class.inc";
require_once "Utility.class.inc";

$client = new NDB_Client();
$client->makeCommandLine();
$client->initialize('../config.xml');

$date = date("Y-m-d");
$dir = "../../htdocs/EnrollmentReport/".$date;
mkdir($dir, 0777); //create directory where all enrollment reports will be placed
chdir($dir);
$DB->select("SELECT CenterID as NumericID, PSCArea as LongName, Name as ShortName FROM psc WHERE CenterID IN (2, 3, 4, 5)", $centers);
$centers[null]= null;
$projects[null]=null;
foreach(Utility::getProjectList() as $key => $value) {
    $projects[$key] = $value;
}
foreach( $centers as $site){
    if($site != null){
        $siteID = $site['NumericID'];
    }else{
        $siteID = null;
    }
    foreach( $projects as $projID => $projName){
        if($projID != null){
            $filename = "EnrollmentReport_".$site['ShortName']."_".$projName.".csv";
            $fd = fopen($filename, 'w+');
            if($fd === FALSE){
                exit(-1);
            }
        }
        if($siteID == null && $projID == null){
            $filename = "EnrollmentReport_Total.csv";
            $fd = fopen($filename, 'w+');
            if($fd === FALSE){
                exit(-1);
            }

        }
        $results = NDB_Menu_statistics::getEnrollmentData($siteID, $projID);
        foreach( $results as $tablesection => $enrolldata){
            switch($tablesection){
                case "enroll_data":
                    $headers = array('Ethnic Category',' Females', 'Males', 'Sex/Gender Unknown',' Total');
                    fputcsv($fd, $headers);
                    break;

                case "enroll_data_race":
                    $headers = array('Racial Categories',' Females', 'Males', 'Sex/Gender Unknown',' Total');
                    fputcsv($fd,$headers);
                    break;

                case "enroll_data_hispanic":
                    $headers = array('Racial Categories - Hispanic',' Females', 'Males', 'Sex/Gender Unknown',' Total');
                    fputcsv($fd,$headers);
                    break;

                case "withdraw":
                    $header = array('Total Failure or Withdrawls');
                    $failures = array('withdraw'=>$enrolldata);
                    fputcsv($fd,$header);
                    fputcsv($fd,$failures);
                    break;
            }


            foreach( $enrolldata as $row){
                fputcsv($fd,$row);
            }
        }
    }
}

?>
