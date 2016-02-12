<?php
set_include_path(get_include_path().":../libraries:../../php/libraries:");
require_once "NDB_Client.class.inc";
require_once "Utility.class.inc";
require_once "Database.class.inc";
//require_once "../../tools/generic_includes.php";
$client = new NDB_Client();
$client->makeCommandLine();
$client->initialize('../config.xml');


//$CommentID = $argv[1];
$db        =& Database::singleton();
if (Utility::isErrorX($db)) {
        print "Could not connect to database: " . $db->getMessage();
            exit(1);
}

$file = fopen('intervention_history.csv','r');

while(($line = fgetcsv($file)) !== FALSE) {
$query         = "SELECT c.CandID, c.PSCID, i.CommentID, s.Visit_Label from intervention_history i JOIN flag f on (f.CommentID = i.CommentID) 
                  JOIN session s on (s.ID = f.SessionID) join candidate c on (c.CandID = s.CandID ) 
                  WHERE c.PSCID=$line[0] AND s.Visit_label=$line[1]";
$record        = array();
$record        = $db->pselect($query, array());
if (Utility::isErrorX($record)) {
        print "Query has failed to select: ".$record->getMessage();
            exit(2);
}
if(!empty($record)) {
            $cid    = "'".$row['CommentID']."'";
            $query1 = "SELECT Administration, Data_entry FROM flag WHERE CommentID=$cid";
            $record1 = array();
            $record1  = $db->pselect($query1, array());
            foreach($record1 as $row1) { 
                if($row1['Administration'] != 'None' && $row1['Data_entry'] != 'Complete') {
                     print $row['CandID']."-".$row['PSCID']."-".$row['CommentID']."-".$row['Visit_Label']."\n";
		     $vals = array('Administration'=>'None', 'Data_entry'=>'Complete' );
		     $Where = array('CommentID'=>$row['CommentID']);
		     //save scores
		     $result = $db->update('flag', $vals, $Where);
		     if ($db->isError($result)) {
			     print "Could not save total score: ". $result->getMessage();
			     //        exit(3);
		     }

                }
            }
	}      
}
}
?>
