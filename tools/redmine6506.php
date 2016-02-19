<?php

set_include_path(get_include_path().":../libraries:../../php/libraries:");
//require_once __DIR__ . "/../../vendor/autoload.php";
require_once "NDB_Client.class.inc";
require_once"Utility.class.inc";
require_once"Database.class.inc";

$client = new NDB_Client();
$client->makeCommandLine();
$client->initialize('../config.xml');

$db =& Database::singleton();


/*
 *
 * HEAD MEASUREMENTS (PROBAND)
 *
 */

$fields_proband = array(
    'head_circumference1_status',
    'head_circumference2_status',
    'length1_status',
    'length2_status',
    'weight1_status',
    'weight2_status'
);

$query_proband = $db->pselect("SELECT CommentID,
head_circumference1_status,head_circumference2_status,
length1_status,length2_status,
weight1_status,weight2_status
FROM head_measurements_proband", array());

/*
 * for each row, check if a DDE exists
 * if so, populate NULL DDE *_status field
 * if initial data entry is 'not_answered'
 */

foreach ($query_proband as $row) {

    $DDECommentID = 'DDE_' . $row['CommentID'];

    if (in_array($DDECommentID, $query_proband)) {
        foreach ($fields_proband as $field) {
            if ($row[$field] == 'not_answered' && $query_proband[$DDECommentID][$field] == NULL) {
                $query_proband = $db->update(
                    'head_measurements_proband',
                    array($query_proband[$DDECommentID][$field] => 'not_answered')
                );
            }
        }
    }
}


/*
 *
 * HEAD MEASUREMENTS (SUBJECT)
 *
 */

$fields_subject = array_merge($fields_proband,
    array(
        'head_circumference1_mother_status',
        'head_circumference2_mother_status',
        'length1_mother_status',
        'length2_mother_status',
        'weight1_mother_status',
        'weight2_mother_status',
        'head_circumference1_father_status',
        'head_circumference2_father_status',
        'length1_father_status',
        'length2_father_status',
        'weight1_father_status',
        'weight2_father_status'
    )
);

$query_subject = $db->pselect("SELECT CommentID,
head_circumference1_status,
head_circumference2_status,
length1_status,
length2_status,
weight1_status,
weight2_status,
head_circumference1_mother_status,
head_circumference2_mother_status,
length1_mother_status,
length2_mother_status,
weight1_mother_status,
weight2_mother_status,
head_circumference1_father_status,
head_circumference2_father_status,
length1_father_status,
length2_father_status,
weight1_father_status,
weight2_father_status
FROM head_measurements_subject", array());

/*
 * for each row, check if a DDE exists
 * if so, populate NULL DDE *_status field
 * if initial data entry is 'not_answered'
 */

foreach ($query_subject as $row) {

    $DDECommentID = 'DDE_' . $row['CommentID'];

    if (in_array($DDECommentID, $query_subject)) {
        foreach ($fields_subject as $field) {
            if ($row[$field] == 'not_answered' && $query_subject[$DDECommentID][$field] == NULL) {
                $query_subject = $db->update(
                    'head_measurements_subject',
                    array($query_subject[$DDECommentID][$field] => 'not_answered')
                );
            }
        }
    }
}

?>


