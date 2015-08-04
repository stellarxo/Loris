<?php
/**
 * Created by PhpStorm.
 * User: Stella
 * Date: 15-06-25
 * Time: 3:49 PM
 *
 * Creates TSI & Head Measurements (Subject) CSV Files for BSRC Submission
 *
 */


set_include_path(get_include_path().":../libraries:../../php/libraries:");
//require_once __DIR__ . "/../../vendor/autoload.php";
require_once "NDB_Client.class.inc";
require_once"Utility.class.inc";
require_once"Database.class.inc";

$client = new NDB_Client();
$client->makeCommandLine();
$client->initialize('../config.xml');

$db =& Database::singleton();

// Set date for output file titles
$date=date("FY");


// list of PSCIDs or DCCIDs into array
$candidateList = $db->pselect("SELECT distinct CandID from candidate", array());


/*
 *
 * Standard BSRC Submission Query
 *
 */


$query1 = $db->pselect("SELECT
f.CommentID,
c.CandID, c.IBISId, c.CenterID, c.Gender,
s.Visit_label,s.SubprojectID, s.ID,
t.Candidate_Age, t.child_ethnicity, t.father_ethnicity, t.mother_ethnicity,
t.candidate_race, t.mother_race, t.father_race, t.ses_income, t.primary_language, t.primary_language_status,
t.mother_occupation, t.mother_occupation_status, t.mother_education, t.father_occupation,
t.father_occupation_status, t.father_education,
ps.study_consent,
cu.CommentId1
FROM flag f JOIN session s ON (f.SessionID=s.ID) JOIN candidate c ON (s.CandID=c.CandID)
JOIN tsi t ON (t.CommentID=f.CommentID) JOIN participant_status ps ON (ps.CandID=c.CandID)
LEFT JOIN conflicts_unresolved cu ON (cu.CommentId1=f.CommentID)
WHERE f.CommentID NOT LIKE 'DDE_%' AND ps.study_consent='yes'", array());


// OUTPUT FILE
$fp1 = fopen("demographics_BSRC_{$date}_final.csv", 'w');


$headers1=array("IBISID","Site Code","SubprojectID","Gender","study_consent","Visit_label","DDE_Complete",
    "conflicts_exist","Candidate_Age","child_ethnicity","father_ethnicity","mother_ethnicity",
    "candidate_race","mother_race","father_race","ses_income","primary_language","primary_language_status",
    "mother_occupation","mother_occupation_status","mother_education","father_occupation",
    "father_occupation_status","father_education");

// Add headers to 1st row
fputcsv($fp1, $headers1);


// Search query rows for each candidate with consent
foreach ($candidateList as $candidateCell) {

    $candidate = implode($candidateCell);

    foreach ($query1 as $row) {

        if ($candidate == $row['CandID']) {

            // Populate each row for the csv into array $entry
            $entry = array();

            // Populate fields according to header
            foreach ($headers1 as $header) {
                switch ($header) {
                    case "DDE_Complete":
                        $sessionID = $row['ID'];
                        $DDEQuery = $db->pselect("SELECT f.Data_entry FROM flag f JOIN session s ON (f.SessionID=s.ID)
                            WHERE f.CommentID LIKE 'DDE_%' AND s.CandID=$candidate AND s.ID=$sessionID AND f.Test_name='tsi'", array());
                        foreach ($DDEQuery as $DDERow) {
                            if (implode($DDERow) == 'Complete') {
                            array_push($entry, "Y");
                            } else {
                            array_push($entry, "N");
                            }
                        }
                        break;
                    case "conflicts_exist":
                        if ($row['CommentId1'] != NULL) {
                            array_push($entry, "Y");
                        } else {
                            array_push($entry, "N");
                        }
                        break;
                    case "SubprojectID":
                        switch ($row['SubprojectID']) {
                            case 1:
                                array_push($entry, "6 month recruit");
                                break;
                            case 2:
                                array_push($entry, "12 month recruit");
                                break;
                            case 3:
                                array_push($entry, "Control");
                                break;
                            case 4:
                                array_push($entry, "6 month recruits FRX");
                                break;
                            case 5:
                                array_push($entry, "12 month recruits FRX");
                                break;
                            case 6:
                                array_push($entry, "EARLI Sib");
                                break;
                            case 7:
                                array_push($entry, "Relative");
                                break;
                            case 9:
                                array_push($entry, "IBIS2 High Risk");
                                break;
                            case 10:
                                array_push($entry, "IBIS2 Low Risk");
                                break;
                            default:
                                array_push($entry, $row['SubprojectID']);
                        }
                        break;
                    case "IBISID":
                        array_push($entry, $row['IBISId']);
                        break;
                    case "Site Code":
                        array_push($entry, $row['CenterID']);
                        break;
                    default:
                        array_push($entry, $row[$header]);
                }
            }

            $testFields1 = array("child_ethnicity","father_ethnicity","mother_ethnicity",
                "candidate_race","mother_race","father_race","ses_income","primary_language","primary_language_status",
                "mother_occupation","mother_occupation_status","mother_education","father_occupation",
                "father_occupation_status","father_education");

            // if all fields are null (test was not filled out), exclude from csv
            foreach ($testFields1 as $field) {
                if ($row[$field] != NULL) {
                    fputcsv($fp1, $entry);
                    break;
                }
            }
        }
    }
}


fclose($fp1);




/*
 *
 * BSRC HEAD MEASUREMENTS SUBMISSION
 *
 *
 */


$query2 = $db->pselect("SELECT
f.CommentID,
c.CandID, c.IBISID,
s.Visit_label, s.ID,
h.Candidate_Age, h.head_circumference_unit, h.head_circumference1, h.head_circumference2,
h.head_length_unit, h.length1, h.length2, h.measurement_method, h.weight_unit, h.weight1, h.weight2,
h.head_circumference_unit_mother, h.head_circumference1_mother,
h.head_length_unit_mother, h.length1_mother, h.weight_unit_mother, h.weight1_mother,
h.head_circumference_unit_father, h.head_circumference1_father,
h.head_length_unit_father, h.length1_father, h.weight_unit_father, h.weight1_father, h.comments,
cu.CommentId1
FROM flag f JOIN session s ON (f.SessionID=s.ID) JOIN candidate c ON (s.CandID=c.CandID)
JOIN head_measurements_subject h ON (h.CommentID=f.CommentID) JOIN participant_status ps ON (ps.CandID=c.CandID)
LEFT JOIN conflicts_unresolved cu ON (cu.CommentId1=f.CommentID)
WHERE f.CommentID NOT LIKE 'DDE_%' AND ps.study_consent='yes'", array());


// OUTPUT FILE
$fp2 = fopen("head_measurements_subject_BSRC_{$date}.csv", 'w');


$headers2=array("IBISID","Visit_label","DDE_Complete","conflicts_exist","Candidate_Age",
    "head_circumference_unit","head_circumference1","head_circumference2","head_length_unit",
    "length1","length2","measurement_method","weight_unit","weight1","weight2",
    "head_circumference_unit_mother","head_circumference1_mother","head_length_unit_mother",
    "length1_mother","weight_unit_mother","weight1_mother","head_circumference_unit_father",
    "head_circumference1_father","head_length_unit_father","length1_father","weight_unit_father",
    "weight1_father","comments");

// Add headers to 1st row
fputcsv($fp2, $headers2);


// Search query rows for each candidate with consent
foreach ($candidateList as $candidateCell) {

    $candidate = implode($candidateCell);

    foreach ($query2 as $row) {

        if ($candidate == $row['CandID']) {

            // Populate each row for the csv into array $entry
            $entry = array();

            // Populate fields according to header
            foreach ($headers2 as $header) {
                switch ($header) {
                    case "DDE_Complete":
                        $sessionID = $row['ID'];
                        $DDEQuery = $db->pselect("SELECT f.Data_entry FROM flag f JOIN session s ON (f.SessionID=s.ID)
                            WHERE f.CommentID LIKE 'DDE_%' AND s.CandID=$candidate AND s.ID=$sessionID AND f.Test_name='head_measurements_subject'", array());
                        foreach ($DDEQuery as $DDERow) {
                            if (implode($DDERow) == 'Complete') {
                                array_push($entry, "Y");
                            } else {
                                array_push($entry, "N");
                            }
                        }
                        break;
                    case "conflicts_exist":
                        if ($row['CommentId1'] != NULL) {
                            array_push($entry, "Y");
                        } else {
                            array_push($entry, "N");
                        }
                        break;
                    case "IBISID":
                        array_push($entry, $row['IBISId']);
                        break;
                    default:
                        array_push($entry, $row[$header]);
                }
            }

            $testFields2 = array("head_circumference_unit","head_circumference1","head_circumference2","head_length_unit",
                "length1","length2","measurement_method","weight_unit","weight1","weight2",
                "head_circumference_unit_mother","head_circumference1_mother","head_length_unit_mother",
                "length1_mother","weight_unit_mother","weight1_mother","head_circumference_unit_father",
                "head_circumference1_father","head_length_unit_father","length1_father","weight_unit_father",
                "weight1_father","comments");

            // if all fields are null (test was not filled out), exclude from csv
            foreach ($testFields2 as $field) {
                if ($row[$field] != NULL) {
                    fputcsv($fp2, $entry);
                    break;
                }
            }
        }
    }
}



fclose($fp2);


?>



