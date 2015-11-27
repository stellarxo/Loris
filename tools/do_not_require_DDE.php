<?php
set_include_path(get_include_path().":../libraries:../../php/libraries:");

require_once '../../php/exceptions/LorisException.class.inc';
require_once '../../php/exceptions/DatabaseException.class.inc';
require_once '../../php/exceptions/ConfigurationException.class.inc';
require_once '../../vendor/smarty/smarty/libs/Smarty.class.php';
require_once "NDB_Client.class.inc";
require_once "Utility.class.inc";
require_once "Candidate.class.inc";

if (empty($argv[1])) {
    print "Usage: php do_not_require_DDE.php (Undo, Show or Confirm)\n";
} else {

    $client = new NDB_Client();
    $client->makeCommandLine();
    $client->initialize('../config.xml');
    $DB = Database::singleton();

    $pparam = array(
        'Dat' => 'Complete',
        'Adm' => 'None',
        'Cen' => '5',
        'PID' => '1',
        'Com' => 'DDE%'
    );

    $rows = $DB->pselect(
        "SELECT f.* FROM flag AS f " .
        "JOIN session s ON f.SessionID = s.ID " . 
        "JOIN candidate c USING (CandID) " .
        "WHERE f.Data_entry=:Dat " .
        "AND f.Administration=:Adm AND s.CenterID=:Cen AND " .
        "c.ProjectID=:PID AND f.CommentID NOT LIKE :Com", $pparam
    );

    $count = 0;
    
    foreach($rows as $row) {

        //print $row['CommentID'] . "\n";
        
        $DDE = $DB->pselectRow("SELECT f.ID, f.Data_entry, f.Administration FROM flag AS f where CommentID = :CommentID", array('CommentID' => 'DDE_' . $row['CommentID']));
        
        if ($DDE['Data_entry'] != 'Complete' or $DDE['Administration'] != 'None') {
            
            if ($argv[1] == 'Undo') {
                if ($DDE['Data_entry'] == '') { $Data_entry = "NULL"; } else { $Data_entry = "'" . $DDE['Data_entry'] . "'"; } 
                if ($DDE['Administration'] == '') { $Administration = "NULL"; } else { $Administration = "'" . $DDE['Administration'] . "'"; } 
                print "UPDATE flag SET Data_entry=" . $Data_entry . ", Administration=" . $Administration . " WHERE ID=" . $DDE['ID'] . ";\n";
            } elseif ($argv[1] == 'Show') {
                print "UPDATE flag SET Data_entry='Complete', Administration='None' WHERE ID=" . $DDE['ID'] . ";\n";
            } elseif ($argv[1] == 'Confirm') {
                try {
                    $result = $DB->update('flag', array('Data_entry' => 'Complete', 'Administration' => 'None'), array('ID' => $DDE['ID']));
                    print ".";
                } catch (DatabaseException $ex) {
                    print "Could not update new ID: ". $result->getMessage();
                }
            }
                
            $count++;
        }
    }        

    print "\n" . $count . " " . $argv[1] . " updates to 'Complete,None' were done.\n";
}