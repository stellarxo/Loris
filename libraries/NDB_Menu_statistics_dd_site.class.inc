<?php
require_once 'NDB_Menu_statistics_site.class.inc';

/**
 * The welcome menu
 * @package main
 */
class NDB_Menu_statistics_dd_site extends NDB_Menu_statistics_site
{

    function notexcluded($var) {
        switch($var) {
            case "vineland_subject":
            case "vineland_proband":
            case "csbs_sponteneity":
                return false;
            default: return true;
        }
    }
    function __construct() {
        $this->instruments = $this->_getInstrumentList(); 
        $this->instruments = array_filter($this->instruments, array(&$this, 'notexcluded'));
    }
    function _CompleteCount($id, $instrument,$ExtraProject_Criteria) {
        $DB =& Database::singleton();
        return $DB->selectOne("SELECT count(s.CandID)  FROM session as s, candidate as c, flag as f, {$instrument} as i WHERE 
                s.ID=f.SessionID AND f.CommentID=i.CommentID 
                AND s.CandID=c.CandID  
                AND s.Cancelled='N' AND s.Active='Y' 
                AND s.Current_stage <> 'Recycling Bin'
                AND s.CenterID={$id} AND f.Data_entry='Complete' AND f.Administration='All'
                $ExtraProject_Criteria
                AND i.CommentID LIKE 'DDE%' ORDER BY c.PSCID;");
    }
    function _GetResults($id, $instrument, $ExtraProject_Criteria) {
        $DB =& Database::singleton();
        $DB->select("SELECT s.CandID, f.SessionID, i.CommentID, c.PSCID, lower(s.Visit_label) as Visit_label  FROM session as s, candidate as c, flag as f, {$instrument} as i 
                WHERE s.ID=f.SessionID AND f.CommentID=i.CommentID AND 
                    s.CandID=c.CandID  AND s.Cancelled='N' AND s.Active='Y' 
                    AND s.CenterID={$id} 
                    AND s.Current_stage <> 'Recycling Bin'
                    $ExtraProject_Criteria
                    AND (f.Data_entry is NULL OR f.Data_entry<>'Complete') AND i.CommentID LIKE 'DDE%' ORDER BY c.PSCID;", $result);
        return $result;
    }

} // End class
?>
