<?php
require_once 'NDB_Menu.class.inc';

/**
 * The welcome menu
 * @package main
 */
class NDB_Menu_statistics_site extends NDB_Menu
{
    function __construct() {
        $this->instruments = $this->_getInstrumentList();
    }
    function _getInstrumentList() {
        $DB =& Database::singleton();
        if(PEAR::isError($DB)) {
            return PEAR::raiseError("Could not connect to database: ".$DB->getMessage());
        }

        $instrumentList = $DB->pselect("SELECT Test_name FROM test_names ORDER BY Test_name", array());
        if(Utility::isErrorX($instrumentList)) {
            return PEAR::raiseError("DB Error: ".$instrumentList->getMessage());
        }
        $instruments = array();
        foreach($instrumentList as $list) {
            $instruments[] = $list['Test_name'];    
        }
        return $instruments;

    }
    // Helper function to get a friendlier version of the instrument name.
    // This is mostly used for the MRI site statistics, which uses 
    // names like "Tarchive_Missing" for "MRI Parameter Form Completed but Missing Tarchive Entry"
    function _getInstrumentName($instrument) {

        $DB =& Database::singleton();
        if(PEAR::isError($DB)) {
            return PEAR::raiseError("Could not connect to database: ".$DB->getMessage());
        }

        $instrumentName = $DB->pselectOne("SELECT Full_name FROM test_names WHERE Test_name=:tname", array('tname'=>$instrument));
        if(Utility::isErrorX($instrumentName)) {
            return PEAR::raiseError("DB Error: ".$instrumentName->getMessage());
        }

        return $instrumentName;
    }
    function _CompleteCount($id, $instrument,$ExtraProject_Criteria) {
        $DB =& Database::singleton();
        $count = $DB->selectOne(
                "SELECT count(s.CandID)  FROM session as s, 
                candidate as c, flag as f, {$instrument} as i 
                WHERE s.ID=f.SessionID AND f.CommentID=i.CommentID 
                AND s.CandID=c.CandID  
                AND s.Cancelled='N' AND s.Active='Y' 
                AND s.CenterID={$id} AND f.Data_entry='Complete' 
                AND s.Current_stage <> 'Recycling Bin'
                AND f.Administration='All'
                $ExtraProject_Criteria
                AND i.CommentID NOT LIKE 'DDE%';");
        if (PEAR::isError($result)) {
            return PEAR::raiseError("DB Error: ".$result->getMessage());
        }
        return $count;

    }
    function _GetResults($id, $instrument,$ExtraProject_Criteria) {
        $DB =& Database::singleton();
        $DB->select("SELECT s.CandID, f.SessionID, i.CommentID, c.PSCID, 
                lower(s.Visit_label) as Visit_label
                FROM session as s, candidate as c, flag as f, 
                {$instrument} as i 
                WHERE s.ID=f.SessionID AND f.CommentID=i.CommentID 
                AND s.CandID=c.CandID  
                AND s.Cancelled='N' AND s.Active='Y' 
                AND s.Current_stage <> 'Recycling Bin'
                AND s.CenterID={$id} 
                AND (f.Data_entry is NULL OR f.Data_entry<>'Complete')
                $ExtraProject_Criteria
                AND i.CommentID NOT LIKE 'DDE%' ORDER BY s.Visit_label, c.PSCID;", $result);
        if (PEAR::isError($result)) {
            return PEAR::raiseError("DB Error: ".$result->getMessage());
        }
        return $result;
    }
    function setup()
    {   
        // If following a breadcrumb, redirect to the original statistics page
        // since the test_name/subtest don't work the same for the site specific
        // pages as for non-site specific
        if(isset($_GET['subtest'])) {
            header("Location: ?test_name=statistics#data_entry");
        }
        $DB =& Database::singleton();
        if(PEAR::isError($DB)) {
            return PEAR::raiseError("Could not connect to database: ".$DB->getMessage());
        }
        $DB->selectRow("SELECT CenterID as ID, PSCArea as Name FROM psc WHERE CenterID=" . $_REQUEST['CenterID'], $center);
        $id = $center['ID'];
        $name = $center['Name'];
        foreach(Utility::getProjectList() as $key => $value) {
            $projects[$key] = $value;
        }
       if(isset($_REQUEST['projectID']) && $_REQUEST['projectID'] != '') {
            $ExtraProject_Criteria = ' AND (c.ProjectID IS NULL OR c.ProjectID=' . $_REQUEST['projectID'] . ')';
            $projectName = $projects[$_REQUEST['projectID']];
            $projectID = $_REQUEST['projectID'];

        } else {
            $ExtraProject_Criteria = '';
        }

        // List of all visits. Add to it any time a new one is seen, so
        // that we can iterate over it to display later, and leave blank
        // cells for ones that are missing for a given instrument in the 
        // template
        $visits = array();

        $data = array();
        foreach($this->instruments as $instrument){
           // $instrument = $instruments['Test_name'];
            $complete_count = $this->_CompleteCount($id, $instrument,$ExtraProject_Criteria); 

            $results = $this->_GetResults($id, $instrument,$ExtraProject_Criteria);

            $test_url = $instrument;
            if(substr($test_url, 0, 10) == "figs_year3"){
                $test_url = "figs_year3";
            }
            foreach($results as $row) {
                if(!in_array($row['Visit_label'], $visits)) {
                    $visits[] = $row['Visit_label'];
                }
                $results[$row['Visit_label']][] = array(
                        'test_url' => $test_url,
                        'CandID' => $row['CandID'],
                        'SessionID' => $row['SessionID'],
                        'CommentID' => $row['CommentID'],
                        'PSCID' => $row['PSCID']
                        );
            }
            
            $data[] = array('name' => $instrument, 'count' => $complete_count,
                            'incompletes' => $results,'fullname'=> $this->_getInstrumentName($instrument));
        }

        $this->tpl_data["data"] = $data;
        $this->tpl_data["SiteName"] = $name;
        $this->tpl_data["CenterID"] = $id;
        $this->tpl_data["ProjectID"] = $projectID;
        $this->tpl_data["ProjectName"] = $projectName;
        print_r($this->tpl_data);
        sort($visits);
        $this->tpl_data['AllVisits'] = $visits;
        $this->tpl_data['NumVisitLabels'] = count($visits);

    } // End function
} // End class
    ?>
