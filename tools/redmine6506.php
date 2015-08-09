<?php

set_include_path(get_include_path().":../libraries:../../php/libraries:");
require_once "NDB_Client.class.inc";
require_once"Utility.class.inc";
require_once"Database.class.inc";

$client = new NDB_Client();
$client->makeCommandLine();
$client->initialize('../config.xml');

$fields = array(
    'head_circumference1_status', 'head_circumference2_status',
    'length1_status', 'length2_status',
    'weight1_status', 'weight2_status',
    'head_circumference1_mother_status', 'head_circumference2_mother_status',
    'length1_mother_status', 'length2_mother_status',
    'weight1_mother_status', 'weight2_mother_status',
    'head_circumference1_father_status', 'head_circumference2_father_status',
    'length1_father_status', 'length2_father_status',
    'weight1_father_status', 'weight2_father_status'
);

$query_subject = $db->pselect("SELECT CommentID,
head_circumference1_status,head_circumference2_status,
length1_status,length2_status,
weight1_status,weight2_status,
head_circumference1_mother_status,head_circumference2_mother_status,
length1_mother_status,length2_mother_status,
weight1_mother_status,weight2_mother_status,
head_circumference1_father_status,head_circumference2_father_status,
length1_father_status,length2_father_status,
weight1_father_status,weight2_father_status
FROM head_measurements_subject", array());

// CHECK THESE & FIELDS FOR *_proband
$query_proband = $db->pselect("SELECT CommentID,
head_circumference1_status,head_circumference2_status,
length1_status,length2_status,
weight1_status,weight2_status,
head_circumference1_mother_status,head_circumference2_mother_status,
length1_mother_status,length2_mother_status,
weight1_mother_status,weight2_mother_status,
head_circumference1_father_status,head_circumference2_father_status,
length1_father_status,length2_father_status,
weight1_father_status,weight2_father_status
FROM head_measurements_proband", array());

/*
 * for each row, check if a DDE exists
 * if so, populate NULL DDE *_status field
 * if initial data entry is 'not_answered'
 */


foreach ($query_subject as $row) {

    $DDECommentID = 'DDE_' . $row['CommentID'];

    if (in_array($DDECommentID,$query)) {
        foreach ($fields as $field) {
            if ($row[$field] == 'not_answered' && $query[$DDECommentID][$field] == NULL) {
                $query = $db->update('head_measurements_subject', array($query[$DDECommentID][$field] => 'not_answered'));
            }
        }
    }
}

foreach ($query_proband as $row) {

    $DDECommentID = 'DDE_' . $row['CommentID'];

    if (in_array($DDECommentID,$query)) {
        foreach ($fields as $field) {
            if ($row[$field] == 'not_answered' && $query[$DDECommentID][$field] == NULL) {
                $query = $db->update('head_measurements_proband', array($query[$DDECommentID][$field] => 'not_answered'));
            }
        }
    }
}


?>


