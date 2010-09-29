<?php
require_once 'NDB_Menu.class.inc';

/**
 * The welcome menu
 * @package main
 */


class NDB_Menu_statistics_mri_site extends NDB_Menu
{
    function _AddToData($name, $type, $result) {
        $incompletes = array();
        foreach($result as $row) {
            $incomplete = array(
                'name' => $row['name'],
                'session' => $row['session'],
                'CommentID' => $row['CommentID'],
                'CandID' => $row['CandID']
            );
            $incompletes[] =  $incomplete;
        }
        $this->tpl_data['data'][] = array('type' => $type, 'title' => $name, 'incompletes' => $incompletes);
    }

    function setup()
    {   
        $DB =& Database::singleton();
        if(PEAR::isError($DB)) {
            return PEAR::raiseError("Could not connect to database: ".$DB->getMessage());
        }
       
         $this->tpl_data['data']=array();
         // MRI parameter form is completed, but nothing in tarchive
         $DB->select("SELECT DISTINCT f.CommentID as CommentID, s.PSCID as name, s.ID as session, s.CandID as CandID
                      FROM flag f JOIN session s ON (f.SessionID=s.ID)
                      LEFT JOIN mri_parameter_form m ON (m.CommentID=f.CommentID)
                      LEFT JOIN tarchive t ON (s.CandID=MID(t.PatientName, 9, 6))
                      WHERE f.CommentID NOT LIKE 'DDE%'
                        AND f.Test_name='mri_parameter_form'
                        AND t.TarchiveID IS NULL
                        AND s.Active='Y'
                        AND s.Cancelled='N'
                        AND f.Data_entry='Complete'
                        AND s.CenterID=" . $DB->quote($_REQUEST['CenterID']) . "
                        ;", $result);
         $this->_AddToData('MRI Parameter Form Completed but Missing tarchive entry', 'parameter_form', $result);


         // MRI parameter form completed, but nothing in browser
         $DB->select("SELECT DISTINCT f.CommentID as CommentID, s.ID as session, c.PSCID as name, s.CandID as CandID
                      FROM mri_parameter_form m LEFT JOIN flag f ON
                                (f.CommentID=m.CommentID)
                           LEFT JOIN session s ON (s.ID=f.SessionID)
                           LEFT JOIN files fi ON (fi.SessionID=f.SessionID)
                           LEFT JOIN candidate c ON (c.CandID=s.CandID)
                      WHERE (m.DTI_Scan_done <> 'No'
                             OR m.T2_Scan_done <> 'No'
                             OR m.T1_Scan_done <> 'No')
                             AND fi.FileID IS NULL
                             AND f.Data_entry= 'Complete'
                             AND s.Active='Y'
                             AND s.Cancelled='N'
                             AND s.CenterID=" . 
                                $DB->quote($_REQUEST['CenterID']), $result);
         $this->_AddToData('MRI Parameter Form Completed but nothing in MRI Browser', 'parameter_form', $result);

         // MRI Browser populated, but no MRI parameter form completed.
         $DB->select("SELECT DISTINCT c.PSCID as name, s.ID as session
                      FROM files LEFT JOIN session s ON (files.SessionID=s.ID)
                            LEFT JOIN flag f on (f.SessionID=s.ID 
                                        AND f.Test_name='mri_parameter_form'
                                        AND f.CommentID NOT LIKE 'DDE%')
                            LEFT JOIN mri_parameter_form mpf ON
                                        (mpf.CommentID=f.CommentID)
                            LEFT JOIN candidate c ON (c.CandID=s.CandID)
                      WHERE s.Active='Y' and s.Cancelled='N'
                            AND c.PSCID <> 'scanner'
                            AND (f.ID IS NULL OR
                                f.Data_entry <> 'Complete')
                            AND s.CenterID=" .
                                $DB->quote($_REQUEST['CenterID']), $result);
         $this->_AddToData('MRI Browser Populated, but no MRI parameter form completed', 'mri_browser', $result);
                 

    } // End function
} // End class
?>
