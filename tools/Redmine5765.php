<?php
/**
 * Created by PhpStorm.
 * User: Stella
 * Date: 15-06-17
 * Time: 10:17 AM
 *
 * PATCH : Saves relationship_to_child entries in temp column relationship_to_child_temp
 *  and maps text answers in relationship_to_child column to drop down choices
 *
 *
 */

set_include_path(get_include_path().":../libraries:../../php/libraries:");
require_once "NDB_Client.class.inc";
require_once"Utility.class.inc";
require_once"Database.class.inc";

$client = new NDB_Client();
$client->makeCommandLine();
$client->initialize('../config.xml');

$db =& Database::singleton();


$query = $db->pselect("SELECT relationship_to_child, relationship_to_child_specify, relationship_to_child_status FROM csbs", array());

// copy previous values into temp column
foreach ($query as $row) {
    $query = $db->update('csbs', array($row['relationship_to_child_temp'] => $row['relationship_to_child']));
}

// map text values to drop down options
foreach ($query as $row) {

    // Mother
    if ($row['relationship_to_child'] == 'mother' or $row['relationship_to_child'] == 'Mother' or $row['relationship_to_child'] == 'Mom') {
        $query = $db->update('csbs', array($row['relationship_to_child'] => '1_Mother'));
    }

    // Father
    elseif ($row['relationship_to_child'] == 'father' or $row['relationship_to_child'] == 'Father' or $row['relationship_to_child'] == 'Dad' or $row['relationship_to_child'] == 'dad') {
        $query = $db->update('csbs', array($row['relationship_to_child'] => '1_Father'));
    }

    // Not Answered
    elseif ($row['relationship_to_child_status'] == 'not_answered' or $row['relationship_to_child'] == 'No response' or $row['relationship_to_child'] == 'NA' or $row['relationship_to_child'] == 'n/a') {
        $query = $db->update('csbs', array($row['relationship_to_child'] => 'not_answered'));
    }

    // Other
    elseif ($row['relationship_to_child'] != "" && $row['relationship_to_child'] != NULL) {
        $response = $row['relationship_to_child'];
        $query = $db->update('csbs', array($row['relationship_to_child'] => '3_Other'));
        $query = $db->update('csbs', array($row['relationship_to_child_specify'] => $response));
    }

}

// Run following query to remove column
// ALTER TABLE csbs DROP COLUMN relationship_to_child_status


?>