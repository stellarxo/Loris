<?
set_include_path(get_include_path().":../libraries:../../php/libraries:");
require_once "NDB_Client.class.inc";
require_once "Utility.class.inc";

$client = new NDB_Client();
$client->makeCommandLine();
$client->initialize('../config.xml');

$DB = Database::singleton();

$completed = $DB->pselect("SELECT f.SessionID, f.CommentID, f.Test_name FROM flag f WHERE Test_name IN ('ados_module1', 'ados_module2', 'ados_module3', 'ados2_module1', 'ados2_module2', 'ados2_module3') AND f.Administration IN ('Partial', 'All') AND f.CommentID NOT LIKE 'DDE%' ORDER BY f.SessionID", array());
foreach($completed as $row) {
    $incomplete = $DB->pselect("SELECT CommentID, Test_name FROM flag WHERE SessionID=:SID AND Test_name IN ('ados_module1', 'ados_module2', 'ados_module3', 'ados2_module1', 'ados2_module2', 'ados2_module3') AND Administration IS NULL AND CommentID NOT LIKE 'DDE%' ORDER BY SessionID", array('SID' => $row['SessionID']));
    foreach($incomplete as $inc_row) {
        print "Setting $inc_row[Test_name] ($inc_row[CommentID]) to Administration=None because $row[Test_name] administered (SessionID: $row[SessionID])\n";
        $DB->update("flag", array('Administration' => 'None', 'Data_entry' => 'Complete'), array('CommentID' => $inc_row['CommentID']));
        $DB->update("flag", array('Administration' => 'None', 'Data_entry' => 'Complete'), array('CommentID' => 'DDE_' . $inc_row['CommentID']));
    }
    //$DB->run("UPDATE flag SET Administration='None', Data_entry='Complete' WHERE SessionID=$row[SessionID] AND Test_name IN ('ados_module1', 'ados_module2', 'ados_module3', 'ados2_module1', 'ados2_module2', 'ados2_module3') AND Administration IS NULL AND CommentID NOT LIKE 'DDE%'");
    //$DB->update("flag", array('Administration' => 'None', 'Data_entry' => 'Complete'), array('SessionID' => $row['SessionID'], 'Test_name' => 'ados_module1', 'Administration' => null));

}
?>
