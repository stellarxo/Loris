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
$data = $DB->pselect("SELECT CommentID From flag f join session s on s.ID=f.SessionID join candidate c on c.CandID=s.CandID WHERE f.Test_name='ECBQ' AND c.ProjectID=1 AND s.CenterID IN (2,4,5)");
foreach($data as $row) {
$result = $db->update('flag', array('Data_entry'=>'Complete'), array('CommentID'=> $row['CommentID'] ));
if (Utility::isErrorX($result)) {
        print "Query has failed to select: ".$result->getMessage();
        //        exit(2);
}

}

/*
$txt_file    = file_get_contents('ECBQ_dave.txt');
$rows        = explode("\n", $txt_file);
array_shift($rows);


foreach($rows as $data ) {
  $values = explode("\t", $data);
 if(!empty($values)) {
  $Cmtid = $values[0];
  $admin = $values[1];
  $dec = $values[2];
if($admin == 'NULL') {
$result = $db->update('flag', array('Administration'=>NULL), array('CommentID'=> $Cmtid));
if (Utility::isErrorX($result)) {
        print "Query has failed to select: ".$result->getMessage();
        //        exit(2);
}

}
$result = $db->update('flag', array('Administration'=>NULL), array('CommentID'=> '113320PHI020729463531369924572'));
if (Utility::isErrorX($result)) {
        print "Query has failed to select: ".$result->getMessage();
        //        exit(2);
}
$result2 = $db->update('ECBQ', array('Data_entry_completion_status'=>'Incomplete'), array('CommentID'=>'113320PHI020729463531369924572'));
if (Utility::isErrorX($result2)) {
        print "Query has failed to select: ".$result2->getMessage();
        //        exit(2);

}
}
}
*/
?>
