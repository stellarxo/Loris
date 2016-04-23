<?php
set_include_path(get_include_path().":../libraries:../../php/libraries:");

require_once '../../vendor/autoload.php';
require_once "NDB_Client.class.inc";
require_once "Utility.class.inc";
require_once "Candidate.class.inc";

if (empty($argv[1])) {
    print "Usage: php Data_entry2Complete-Administration2None.php (Undo, Show or Confirm) test_name visit_label1,visit_label2,visit_label3,visit_label4\n";
} else {

    $client = new NDB_Client();
    $client->makeCommandLine();
    $client->initialize('../config.xml');
            
    $DB = Database::singleton();
    //$DB->_showQueries = true;
    
    $TP = explode(',', $argv[3]);
    
    $pparam = array(
        //'DAT' => 'Complete',
        //'ADM' => 'None',
        'CEN' => '5',
        'PID' => '1',
        'COM' => 'DDE%',
        'TES' => $argv[2],
        'VI0' => $TP[0],
        'VI1' => isset($TP[1]) ? $TP[1] : null,
        'VI2' => isset($TP[2]) ? $TP[2] : null,
        'VI3' => isset($TP[3]) ? $TP[3] : null,
    );

    $rows = $DB->pselect(
        "SELECT *, f.ID as fID FROM flag AS f " .
        "JOIN session s ON f.SessionID = s.ID " . 
        "JOIN candidate c USING (CandID) " .
        "WHERE s.CenterID=:CEN AND c.ProjectID=:PID " .
        "AND f.Test_name=:TES AND (s.Visit_label=:VI0 OR s.Visit_label=:VI1 OR " .
        "s.Visit_label=:VI2 OR s.Visit_label=:VI3) " .
        "AND (f.Data_entry IS NULL AND f.Administration IS NULL) " .
        "AND f.CommentID NOT LIKE :COM " .
        "ORDER BY f.ID", $pparam
    );

    $count = 0;
    print "-- Test_name: $argv[2] / Visit_label: $argv[3]\n";
    
    
    foreach($rows as $row) {

        //print $row['CommentID'] . "\n";

        if ($argv[1] == 'Undo') {
            if ($row['Data_entry'] == '') { $Data_entry = "NULL"; } else { $Data_entry = "'" . $row['Data_entry'] . "'"; } 
            if ($row['Administration'] == '') { $Administration = "NULL"; } else { $Administration = "'" . $row['Administration'] . "'"; } 
            print "UPDATE flag SET Data_entry=" . $Data_entry . ", Administration=" . $Administration . " WHERE ID=" . $row['fID'] . ";\n";
        } elseif ($argv[1] == 'Show') {
            print "UPDATE flag SET Data_entry='Complete', Administration='None' WHERE ID=" . $row['fID'] . ";\n";
        } elseif ($argv[1] == 'Confirm') { 
            try {
                $result = $DB->update('flag', array('Data_entry' => 'Complete', 'Administration' => 'None'), array('ID' => $row['fID']));
                print ".";
            } catch (DatabaseException $ex) {
                print "Could not update new ID: ". $result->getMessage();
            }
        }

        $count++;
    }        

    print "-- " . $count . " " . $argv[1] . " updates to 'Complete,None' were done.\n\n";
}