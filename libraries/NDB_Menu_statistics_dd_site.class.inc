<?php
require_once 'NDB_Menu_statistics_site.class.inc';

/**
 * The welcome menu
 * @package main
 */
class NDB_Menu_statistics_dd_site extends NDB_Menu_statistics_site
{
    function _CompleteCount($id, $instrument) {
        $DB =& Database::singleton();
        return $DB->selectOne("SELECT count(s.CandID)  FROM session as s, candidate as c, flag as f, {$instrument} as i WHERE s.ID=f.SessionID AND f.CommentID=i.CommentID AND s.CandID=c.CandID  AND s.Cancelled='N' AND s.Active='Y' AND s.CenterID={$id} AND f.Data_entry='Complete' AND f.Administration='All' AND i.CommentID LIKE 'DDE%' ORDER BY c.PSCID;");
    }
    function _GetResults($id, $instrument) {
        $DB =& Database::singleton();
        $DB->select("SELECT s.CandID, f.SessionID, i.CommentID, c.PSCID, lower(s.Visit_label) as Visit_label  FROM session as s, candidate as c, flag as f, {$instrument} as i WHERE s.ID=f.SessionID AND f.CommentID=i.CommentID AND s.CandID=c.CandID  AND s.Cancelled='N' AND s.Active='Y' AND s.CenterID={$id} AND (f.Data_entry is NULL OR f.Data_entry<>'Complete') AND i.CommentID LIKE 'DDE%' ORDER BY c.PSCID;", $result);
        return $result;
    }

} // End class
?>
