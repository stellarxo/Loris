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
        'Data_entry' => 'Complete',
        'Administration' => 'None',
        'CenterID' => '5',
        'ProjectID' => '1',
        'CommentID' => 'DDE%'
    );

    $rows = $DB->pselect(
        "SELECT f.* FROM flag AS f JOIN session s ON f.SessionID = s.ID JOIN " .
        "project_rel p USING (SubprojectID) WHERE f.Data_entry=:Data_entry " .
        "AND f.Administration=:Administration AND s.CenterID=:CenterID AND " .
        "p.ProjectID=:ProjectID AND CommentID NOT LIKE :CommentID", $pparam
    );

    $count = 0;
    
    foreach($rows as $row) {

        //print $row['CommentID'] . "\n";
        
        $DDE = $DB->pselect("SELECT f.ID, f.Data_entry, f.Administration FROM flag AS f where CommentID = :CommentID", array('CommentID' => 'DDE_' . $row['CommentID']));
        
        if ($DDE[0]['Data_entry'] != 'Complete' or $DDE[0]['Administration'] != 'None') {
            
            if ($argv[1] == 'Undo') {
                if ($DDE[0]['Data_entry'] == '') { $Data_entry = "NULL"; } else { $Data_entry = "'" . $DDE[0]['Data_entry'] . "'"; } 
                if ($DDE[0]['Administration'] == '') { $Administration = "NULL"; } else { $Administration = "'" . $DDE[0]['Administration'] . "'"; } 
                print "UPDATE flag SET Data_entry=" . $Data_entry . ", Administration=" . $Administration . " WHERE ID=" . $DDE[0]['ID'] . ";\n";
            } elseif ($argv[1] == 'Show') {
                print "UPDATE flag SET Data_entry='Complete', Administration='None' WHERE ID=" . $DDE[0]['ID'] . ";\n";
            } elseif ($argv[1] == 'Confirm') {
                $result = $DB->update('flag', array('Data_entry' => 'Complete', 'Administration' => 'None'), array('ID' => $DDE[0]['ID']));

                if ($DB->isError($result)) {
                    print "Could not update new ID: ". $result->getMessage();
                } else {
                    print ".";
                }
            }
                
            $count++;
        }
    }        

    print "\n" . $count . " " . $argv[1] . " updates to 'Complete,None' were done.\n";
}