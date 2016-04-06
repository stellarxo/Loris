<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/** Error reporting */
//error_reporting(E_ALL);
//ini_set('display_errors', TRUE);
//ini_set('display_startup_errors', TRUE);

set_include_path(get_include_path().":../../libraries:../../../php/libraries:");
require_once __DIR__ . "/../../../vendor/autoload.php";
require('../../externals/spreadsheet-reader/php-excel-reader/excel_reader2.php');
require('../../externals/spreadsheet-reader/SpreadsheetReader.php');
//require_once "NDB_Page.class.inc";
require_once "NDB_Client.class.inc";
require_once "Utility.class.inc";

$client = new NDB_Client();
$client->makeCommandLine();
$client->initialize('../../config.xml');
$DB = Database::singleton();

//$Reader = new SpreadsheetReader($argv[1]);
//$Sheets = $Reader -> Sheets();
//print_r($Sheets);
//$Reader->ChangeSheet($argv[2]);


$file = $argv[1];
$fp = fopen($file, "r");
$headers = fgetcsv($fp);
$headers = array_slice($headers, 3, 36);

$i=2;

// foreach ($Reader as $Key => $excel_row)
while($excel_row = fgetcsv($fp))
{
    //print $Key . ": ". "SELECT * FROM files where File like '%" . $excel_row[11] . "_DTIPrepReg_001.mnc'" ;  
    // _DTIPrepReg_001.mnc 
    // "SELECT * FROM files where File like '%" . $excel_row[2] . "%' and SeriesUID is not null"
    // "SELECT * FROM files where File like '%" . $excel_row[2] . "_DTIPrepReg_001.mnc'"
    
    $name_prep = $excel_row[40] . "_DTIPrepReg_001.mnc";
    $name_wild = $excel_row[40] . ".mnc";
    
    $db_files_prep = $DB->pselectRow("SELECT * FROM files where File like '%" . $name_prep . "'", array());
    $db_files_wild = $DB->pselectRow("SELECT * FROM files where File like '%" . $name_wild . "%'", array());    
//print_r($excel_row);
    
    if ($db_files_prep) { 
        $db_files = $db_files_prep; 
        $name_file = $name_prep;
    } else  { 
        $db_files = $db_files_wild; 
        $name_file = $name_wild;
    }
    
    if ($db_files) 
    {
        // file found proceed
        //print_r($db_files);
        // print "$excel_row[2], $excel_row[1], $db_files[FileID], ";

        // files_qcstatus is already populated
        $db_files_qcstatus = $DB->pselectRow("SELECT * FROM files_qcstatus where FileID=:FID", array("FID" => $db_files["FileID"]));
        if (!$db_files_qcstatus)
        {
            print $i .": no db_files_qcstatus.\n";
        }
        else {
            print $i . ":" . $name_file . " db_files_qcstatus found.\n";
        }
        //print_r($db_files_qcstatus);
        
        // feedback_mri_comments already present
        $db_feedback_mri_comments = $DB->pselectRow("SELECT * FROM feedback_mri_comments where FileID=:FID", array("FID" => $db_files["FileID"]));
        if (!$db_feedback_mri_comments)
        {
        //    print "no db_feedback_mri_comments, ";
        }
        //print_r($db_feedback_mri_comments);
        
        $db_parameter_file = $DB->pselect("SELECT * FROM parameter_file where FileID=:FID", array("FID" => $db_files["FileID"]));
        //print_r($db_parameter_file);
        if (!$db_parameter_file)
        {
            print "no db_parameter_file, ";
        }
        
        
        //$success = $DB->insert('files_qcstatus', array('FileID'=>$db_files["FileID"],
        //                                           'Value'=>'dti',
        //                                          'ParameterTypeID'=>$typeID));
        
    } 
    else
    {
        // file not found, explain
        print $i . ":" . $name_file . " File not found in the db, can't insert QC data.\n";
    }    
    
    //print ".";
    //$handle = fopen ("php://stdin","r");
    //$line = fgets($handle);
    $i++;
}
	

