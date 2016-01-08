<?php
require_once 'NDB_Menu.class.inc';

/**
 * The welcome menu
 * @package main
 */
class NDB_Menu_reliability_breakdown extends NDB_Menu
{
    function _hasAccess() {
        $user =& User::singleton();
        return $user->hasPermission('send_to_dcc');
    }

    function setup()
    {
        $DB =& Database::singleton();

        $CommentID = $_REQUEST['CommentID'];
        $instrument_name = $_REQUEST['instrument'];

        $orig = $DB->pselectRow("SELECT * FROM $instrument_name WHERE CommentID=:CID", array('CID' => $CommentID));
        $reliable = $DB->pselectRow("SELECT * FROM $instrument_name" . "_reliability WHERE CommentID=:CID", array("CID" => $CommentID));

        $changes = array();
        
        foreach ($reliable as $key => $val) {
            switch($key) {
                // Skip things that are expected to be different
            case 'CommentID':
            case 'record_id':
            case 'reliability_center_id':
            case 'Gold_standard':
            case 'Reliability_score_scored_items':
            case 'Reliability_score_all_items':
            case 'UserID':
            case 'Examiner':
            case 'Testdate':
            case 'Data_entry_completion_status':
            case 'Date_taken':
            case 'Candidate_Age':
            case 'Window_Difference':
                continue 2; // without the 2 continue just breaks the switch, see http://php.net/manual/en/control-structures.switch.php
            default:
                break;
            }

            if($val == $orig[$key]) {
                ;//print "$key: match\n";
            } else {
                $changes[] = array('key' =>$key, 'original' => $orig[$key], 'reliable' => $val);
            }

        }
        $this->tpl_data['differences'] = $changes;



    } // End function
} // End class
?>
