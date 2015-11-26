<?php
require_once 'NDB_Menu.class.inc';

/**
 * The welcome menu
 * @package main
 */
class NDB_Menu_reliability_diagnostic_calls extends NDB_Menu
{
    function setup()
    {   
       $DB =& Database::singleton();
       
        $DB->select("SELECT * FROM reliability_diagnostic_calls", $result);
            foreach($result as $row){          
               $data[] = array('date_of_review' => $row['date_of_review'], 'caseID_1' => $row['caseID_1'], 'caseID_2' => $row['caseID_2'], 'caseID_3' => $row['caseID_3']);
            }
            $this->tpl_data["data"] = $data;      
      
           
    } // End function
} // End class
?>