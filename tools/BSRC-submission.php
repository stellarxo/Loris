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
    
    //    s.SubprojectID, 
    //    s.Current_stage, 
    //    s.Visit, 
    
    $rows = $DB->select(
       "SELECT
        c.IBISId as id_number, 
        m.Date_taken as date_of_testing,
        m.Candidate_Age as age_at_testing,
        null as adjusted_age,
        null as version,
        m.gross_motor_raw,
        m.visual_reception_raw,
        m.fine_motor_raw,
        m.receptive_language_raw,
        m.expressive_language_raw,
        m.gross_motor_age_equivalent as gross_motor_ae,
        m.visual_reception_age_equivalent as visual_reception_ae,
        m.fine_motor_age_equivalent,
        m.receptive_language_age_equivalent,
        m.expressive_language_age_equivalent,
        m.gross_motor_t,
        m.visual_reception_t,
        m.receptive_language_t,
        m.expressive_language_t,
        m.composite_standard_score
        FROM flag f JOIN session s ON (f.SessionID=s.ID) 
        JOIN candidate c ON (s.CandID=c.CandID)
        JOIN mullen m ON (m.CommentID=f.CommentID) 
        JOIN participant_status ps ON (ps.CandID=c.CandID)
        LEFT JOIN conflicts_unresolved cu ON (cu.CommentId2=f.CommentID)
        WHERE ps.study_consent='yes' AND s.CenterID!=1 AND f.Data_entry='Complete' 
        AND f.CommentID NOT LIKE 'DDE_%' AND cu.CommentID2 is null 
        AND s.Current_stage<>'Recycling Bin' AND m.Date_taken is not null 
        AND (s.SubprojectID=1 OR s.SubprojectID=2 OR s.SubprojectID=3);
    ",$result);

    $count = 0;
    
    foreach($rows as $row) {

        //print $row['CommentID'] . "\n";
        print_r($row);
        exit;
        
        $count++;
    }        

    print "-- " . $count . " " . $argv[1] . " updates to 'Complete,None' were done.\n\n";
}