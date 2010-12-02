<?php
require_once 'NDB_Menu_statistics_site.class.inc';

/**
 * The welcome menu
 * @package main
 */
class NDB_Menu_statistics_mri_site extends NDB_Menu_statistics_site
{
    function _getInstrumentName($instrument) {
        switch($instrument) {
            case "Tarchive_Missing":
                return "MRI Parameter Form Completed but Missing tarchive entry";
            case "PF_Missing":
                return "MRI Browser Populated, but no MRI parameter form completed";
            case "Files_Missing":
                return "MRI Parameter Form Completed but nothing in MRI Browser";
        }
        return parent::_getInstrumentName($instrument);
    }
    function _CompleteCount($id, $instrument) {
        return null;
    }
    function _GetResults($id, $instrument) {
        $DB =& Database::singleton();
        switch($instrument) {
            case 'Tarchive_Missing':
                $query = "SELECT DISTINCT f.CommentID as CommentID, 
                            c.PSCID, s.ID as SessionID, s.CandID as CandID,
                            lower(Visit_label) as Visit_label
                    FROM flag f JOIN session s ON (f.SessionID=s.ID)
                        LEFT JOIN mri_parameter_form m ON (m.CommentID=f.CommentID)
                        LEFT JOIN tarchive t ON (s.CandID=MID(t.PatientName, 9, 6))
                        LEFT JOIN candidate c ON (s.CandID=c.CandID)
                        WHERE f.CommentID NOT LIKE 'DDE%'
                            AND f.Test_name='mri_parameter_form'
                            AND f.Administration <> 'None'
                            AND t.TarchiveID IS NULL
                            AND s.Active='Y'
                            AND s.Cancelled='N'
                            AND f.Data_entry='Complete'
                            AND s.CenterID=" . $DB->quote($_REQUEST['CenterID']) . "
                            AND (m.T1_Scan_done IS NULL OR m.T1_Scan_done <> 'No')
                        ORDER BY c.PSCID";
                break;
            case 'Files_Missing':
                $query = "SELECT DISTINCT f.CommentID as CommentID, s.ID as SessionID, c.PSCID, s.CandID, lower(s.Visit_label) as Visit_label
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
                        AND s.CenterID=" .  $DB->quote($_REQUEST['CenterID'])
                    . "ORDER BY c.PSCID";
                break;
            case 'PF_Missing': $query =
                "SELECT DISTINCT c.PSCID, s.ID as SessionID,
                        lower(s.Visit_label) as Visit_label
                    FROM files LEFT JOIN session s ON (files.SessionID=s.ID)
                        LEFT JOIN flag f on (f.SessionID=s.ID AND f.Test_name='mri_parameter_form' AND f.CommentID NOT LIKE 'DDE%')
                        LEFT JOIN mri_parameter_form mpf ON (mpf.CommentID=f.CommentID)
                        LEFT JOIN candidate c ON (c.CandID=s.CandID)
                        WHERE s.Active='Y' and s.Cancelled='N'
                           AND c.PSCID <> 'scanner'
                           AND (f.ID IS NULL OR
                           f.Data_entry <> 'Complete')
                           AND s.CenterID=" .
                           $DB->quote($_REQUEST['CenterID'])
                           . "ORDER BY c.PSCID";
                break;

        }
        if($query) $DB->select($query, $result);
        return $result;
    }
    function setup() {
        $this->instruments = array("Tarchive_Missing", "Files_Missing", "PF_Missing");
        return parent::setup();
        
    }

} // End class
?>
