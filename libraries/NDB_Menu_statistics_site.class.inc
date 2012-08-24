<?php
require_once 'NDB_Menu.class.inc';

/**
 * The welcome menu
 * @package main
 */
class NDB_Menu_statistics_site extends NDB_Menu
{
    var $instruments = array(
            //      "EARLI_interview",
            //"ace_medical_history",
            "adi_r_proband",
            "adi_r_subject",
            "ados_module1",
            "ados_module2",
            "ados_module3",
            "aosi",
            "csbs", 
            "csbs_sponteneity",
            "DSMIV_checklist",
            "EARLI_interview_PART_1",
            "EARLI_interview_PART_2",
            "EARLI_interview_PART_3",
            "EARLI_interview_PART_4",
            "EARLI_interview_S3_inserts",
            "EARLI_interview_S7_inserts",
            "edi",
            "figs_year3",
            "figs_year3_relatives",
            "fyi",
            "head_measurements_proband",
            "head_measurements_subject",
            "i3",
            "ibq_r",
            "intervention_history",
            "m_chat_proband",
            "m_chat_subject",
            //    "macarthur_cdi",
            "macarthur_words_gestures",
            //    "med_extract_new_recruit",
            "med_psych_hist",
            "med_records_24",
            "med_records_recruit",
            "med_records_proband",
            "mri_parameter_form",
            "mullen",
            "neuro_screen",
            "prefrontal_task",
            "radiology_review",
            "rbs_r",
            "RSMS",
            "scq_proband",
            "scq_subject",
            "seq",
            "SRS",
            "tsi",
            "tsi_followup",
            "vineland_proband",
            "vineland_subject" 
    );

    // Helper function to get a friendlier version of the instrument name.
    // This is mostly used for the MRI site statistics, which uses 
    // names like "Tarchive_Missing" for "MRI Parameter Form Completed but Missing Tarchive Entry"
    function _getInstrumentName($instrument) {
        return $instrument;
    }
    function _CompleteCount($id, $instrument) {
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
                AND i.CommentID NOT LIKE 'DDE%';");
        if (PEAR::isError($result)) {
            return PEAR::raiseError("DB Error: ".$result->getMessage());
        }
        return $count;

    }
    function _GetResults($id, $instrument) {
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
        // List of all visits. Add to it any time a new one is seen, so
        // that we can iterate over it to display later, and leave blank
        // cells for ones that are missing for a given instrument in the 
        // template
        $visits = array();

        $data = array();
        foreach($this->instruments as $instrument){           
            $complete_count = $this->_CompleteCount($id, $instrument); 

            $results = $this->_GetResults($id, $instrument);

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
            $data[] = array('name' => $this->_getInstrumentName($instrument), 'count' => $complete_count, 'incompletes' => $results);
        }

        $this->tpl_data["data"] = $data;
        $this->tpl_data["SiteName"] = $name;
        $this->tpl_data["CenterID"] = $id;
        sort($visits);
        $this->tpl_data['AllVisits'] = $visits;
        $this->tpl_data['NumVisitLabels'] = count($visits);

    } // End function
} // End class
    ?>
