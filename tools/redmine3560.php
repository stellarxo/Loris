<?php
/**
 * Created by PhpStorm.
 * User: Stella
 * Date: 15-06-25
 * Time: 3:49 PM
 */

set_include_path(get_include_path().":../libraries:../../php/libraries:");
require_once "NDB_Client.class.inc";
require_once"Utility.class.inc";
require_once"Database.class.inc";

$client = new NDB_Client();
$client->makeCommandLine();
$client->initialize('../config.xml');

//$Factory =& NDB_Factory::singleton();
$db =& Database::singleton();

// Set date for output file titles
$date=date("FY");

// Used in both standard and head measurements submissions
$DDEQuery = $db->pselect("SELECT f.Data_entry, f.CommentID, s.CandID
FROM flag f JOIN session s ON (f.SessionID=s.ID)
WHERE f.CommentID LIKE 'DDE_%'", array());

// Input file of list of PSCIDs or DCCIDs into array
$fp = fopen("~/Users/Stella/Desktop/input.csv", "r");
$candidateList = fgetcsv($fp);
fclose($fp);

/*
 *
 * Standard BSRC Submission Query
 *
 */

$query1 = $db->pselect("SELECT f.CommentID,
s.Visit_label,s.SubprojectID,
t.Candidate_Age, t.child_ethnicity, t.father_ethnicity, t.mother_ethnicity,
t.candidate_race, t.mother_race, t.father_race, t.ses_income, t.primary_language, t.primary_language_status,
t.mother_occupation, t.mother_occupation_status, t.mother_education, t.father_occupation,
t.father_occupation_status, t.father_education,
ps.study_consent,
cu.CommentId1
FROM flag f JOIN session s ON (f.SessionID=s.ID) JOIN candidate c ON (s.CandID=c.CandID)
JOIN tsi t ON (t.CommentID=f.CommentID) JOIN participant_status ps ON (ps.CandID=c.CandID)
LEFT JOIN conflicts_unresolved cu ON (cu.CommentId1=f.CommentID)
WHERE f.CommentID NOT LIKE 'DDE_%'", array());

// OUTPUT FILE
$fp1 = fopen("demographics_BSRC_{$date}_final.csv", 'w');

// where data will be stored
$entries1 = array();

// Search query rows for each candidate with consent
foreach ($candidateList as $candidate) {
    $found = false;
    do {
        foreach ($query1 as $row) {
            if ($candidate['PSCID'] == $row['PSCID']) $found = true;
        }
    } while ($found == false);

    // Populate the rows for the csv into an array
    $entry = array();

    // Populate fields according to header
    $headers=array('IBISID','Site Code','SubprojectID','Gender','study_consent','Visit_label','DDE_Complete',
        'conflicts_exist','Candidate_Age','child_ethnicity','father_ethnicity','mother_ethnicity',
        'candidate_race','mother_race','father_race','ses_income','primary_language','primary_language_status',
        'mother_occupation','mother_occupation_status','mother_education','father_occupation',
        'father_occupation_status','father_education');

    foreach ($headers as $header) {
        switch ($header) {
            case "DDE_Complete":
                foreach ($DDEQuery as $DDERow) {
                    if ($DDERow['CandID'] == $candidate['CandID'] && $DDERow['Data_entry'] == 'Complete') {
                        array_push($entry, $candidate['Y']);
                    } else {
                        array_push($entry, $candidate['N']);
                    }
                }
                break;
            case "conflicts exist":
                if ($candidate['CommentID1'] != NULL) {
                    array_push($entry, $candidate['Y']);
                } else {
                    array_push($entry, $candidate['N']);
                }
                break;
            default:
                array_push($fields, $candidate[$header]);
        }
    }
    $entries1[] = $entry;
}

foreach ($entries1 as $line) {
    fputcsv($fp1, $line);
}

fclose($fp1);



/*
 *
 * BSRC HEAD MEASUREMENTS SUBMISSION
 *
 *
 */

$query2 = $db->pselect("SELECT f.CommentID,
s.Visit_label,
c.IBISID,
h.CommentID, h.Candidate_Age,
h.head_circumference_unit, h.head_circumference1, h.head_circumference2,
h.head_length_unit, h.length1, h.length2, h.measurement_method,
h.weight_unit, h.weight1, h.weight2,
h.head_circumference_unit_mother, h.head_circumference1_mother,
h.head_length_unit_mother, h.length1_mother, h.weight_unit_mother, h.weight1_mother,
h.head_circumference_unit_father, h.head_circumference1_father,
h.head_length_unit_father, h.length1_father, h.weight_unit_father, h.weight1_father, h.comments,
cu.CommentId1
FROM flag f JOIN session s ON (f.SessionID=s.ID) JOIN candidate c ON (s.CandID=c.CandID)
JOIN head_measurements_subject h ON (h.CommentID=f.CommentID) JOIN participant_status ps ON (ps.CandID=c.CandID)
LEFT JOIN conflicts_unresolved cu ON (cu.CommentId1=f.CommentID)
WHERE f.CommentID NOT LIKE 'DDE_%'", array());

// OUTPUT FILE
$fp2 = fopen("head_measurements_subject_BSRC_{$date}.csv", 'w');

// multi-dimensional where data will be stored
$entries2 = array();

// Search query rows for each candidate with consent
foreach ($candidateList as $candidate) {
    $found = false;
    do {
        foreach ($query2 as $row) {
            if ($candidate == $row['PSCID']) $found = true;
        }
    } while ($found == false);

    // Populate all data for a single candidate in array $entry
    $entry = array();

    // Populate fields according to header
    $headers=array('IBISID','Visit_label','DDE_Complete','conflicts_exist','Candidate_Age',
        'head_circumference_unit','head_circumference1','head_circumference2','head_length_unit',
        'length1','length2','measurement_method','weight_unit','weight1','weight2',
        'head_circumference_unit_mother','head_circumference1_mother','head_length_unit_mother',
        'length1_mother','weight_unit_mother','weight1_mother','head_circumference_unit_father',
        'head_circumference1_father','head_length_unit_father','length1_father','weight_unit_father',
        'weight1_father','comments');

    foreach ($headers as $header) {
        switch ($header) {
            case "DDE_Complete":
                foreach ($DDEQuery as $DDERow) {
                    if ($DDERow['CandID'] == $candidate['CandID'] && $DDERow['Data_entry'] == 'Complete') {
                        array_push($entry, $candidate['Y']);
                    } else {
                        array_push($entry, $candidate['N']);
                    }
                }
                break;
            case "conflicts exist":
                if ($candidate['CommentID1'] == $candidate['CommentID']) {
                    array_push($entry, $candidate['Y']);
                } else {
                    array_push($entry, $candidate['N']);
                }
                break;
            default:
                array_push($entry, $candidate[$header]);
        }
    }
    $entries2[] = $entry;
}

foreach ($entries2 as $line) {
    fputcsv($fp2, $line);
}

fclose($fp2);

?>



