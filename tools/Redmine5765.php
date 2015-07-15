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
require_once __DIR__ . "/../../vendor/autoload.php";
require_once "NDB_Client.class.inc";
require_once"Utility.class.inc";
require_once"Database.class.inc";

$client = new NDB_Client();
$client->makeCommandLine();
$client->initialize('../config.xml');

$db =& Database::singleton();

$query = $db->pselect("SELECT CommentID, relationship_to_child, relationship_to_child_specify, relationship_to_child_temp, relationship_to_child_status FROM csbs", array());

// copy previous values into temp column
foreach ($query as $row) {
    if ($row['relationship_to_child_temp']==NULL) {
        $vals = array('relationship_to_child_temp' => $row['relationship_to_child']);
        $Where = array('CommentID'=>$row['CommentID']);
        $result = $db->update('csbs', $vals, $Where);
    }
}

$options = array('not_answered', '1_Mother', '2_Father', '3_Other');

// map text values to drop down options
foreach ($query as $row) {

    $vals = array();
    $Where = array('CommentID'=>$row['CommentID']);

    // Mother
    if ($row['relationship_to_child'] == 'mother' or $row['relationship_to_child'] == 'Mother' or $row['relationship_to_child'] == 'Mom') {
        $vals = array('relationship_to_child' => $options[1]);
    }
    // Father
    elseif ($row['relationship_to_child'] == 'father' or $row['relationship_to_child'] == 'Father' or $row['relationship_to_child'] == 'Dad' or $row['relationship_to_child'] == 'dad') {
        $vals = array('relationship_to_child' => $options[2]);
    }
    // Not Answered
    elseif ($row['relationship_to_child_status'] == 'not_answered' or $row['relationship_to_child'] == 'No response' or $row['relationship_to_child'] == 'NA' or $row['relationship_to_child'] == 'n/a') {
        $vals = array('relationship_to_child' => $options[0]);
    }
    // Other
    elseif ($row['relationship_to_child'] != "" && $row['relationship_to_child'] != NULL && !in_array($row['relationship_to_child'], $options)) {
        $query = $db->update('csbs', array('relationship_to_child_specify' => $row['relationship_to_child']), $Where);
        $vals = array('relationship_to_child' => $options[3]);
    }

    if (!empty($vals)) {
        $query = $db->update('csbs', $vals, $Where);
    }

}

// Run following queries afterwards:
// ALTER TABLE csbs MODIFY relationship_to_child enum('1_Mother','2_Father','3_Other','not_answered');
// ALTER TABLE csbs DROP COLUMN relationship_to_child_status;
// ALTER TABLE csbs DROP COLUMN relationship_to_child_temp;


?>

