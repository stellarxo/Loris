<?php
require_once 'NDB_Menu.class.inc';
require_once 'NDB_Menu_Filter_reliability.class.inc';

/**
 * The welcome menu
 * @package main
 */
class NDB_Menu_statistics extends NDB_Menu
{
        function _inCenter($centerID, $Centres) {
            foreach ($Centres as $Centre) {
                if($Centre['NumericID'] == $centerID) {
                    return TRUE;
                }
            }
            return FALSE;
        }
    function render_stats_table($header, $subcats, $visits, $dropdown_name, $dropdown_opt, $dropdown_selected, $centres, $data, $Subsection="") {
        $tpl_data = array();
        $tpl_data['test_name'] = $_REQUEST['test_name'];
        $tpl_data['Subsection'] = $Subsection;
        $tpl_data['Visits'] = $visits;
        $smarty = new Smarty_neurodb();
        $tpl_data['Header'] = $header;
        $tpl_data['Subcategories'] = $subcats;
        $tpl_data['Subprojects'] = Utility::getSubprojectList(); //array('1' => '6 Month Recruit', '2' => '12 Month Recruit', '3' => 'Control');
        $tpl_data['DropdownName'] = $dropdown_name;
        $tpl_data['DropdownOptions'] = $dropdown_opt;
        $tpl_data['DropdownSelected'] = $dropdown_selected;
        $tpl_data['Centers'] = $centres;
        foreach($data as $row) {
            $subproj = $row['SubprojectID'];
            $vl = $row['VLabel'];
            $subcat = $row['Subcat'];
            $center = $row['CenterID'];


            if(array_search($vl, $visits) !== FALSE && array_search($subcat, $subcats) !== FALSE && $this->_inCenter($center, $centres) !== FALSE) {
                $tpl_data['data'][$subproj][$vl][$subcat] += $row['val'];
                $tpl_data['data'][$subproj][$vl]['total'] += $row['val'];
                $tpl_data['data'][$subproj][$subcat] += $row['val'];
                $tpl_data['data'][$vl][$subcat] += $row['val'];
                $tpl_data['data'][$vl]['total'] += $row['val'];
                $tpl_data['data'][$subproj]['C' . $center][$vl][$subcat] = $row['val'];
                $tpl_data['data']['Cat' . $subcat] += $row['val'];
                $tpl_data['data'][$subproj]['C' . $center][$subcat] += $row['val'];
                $tpl_data['data']['C' . $center][$vl][$subcat] += $row['val'];
                $tpl_data['data'][$subproj]['total'] += $row['val'];
                $tpl_data['data']['C' . $center][$subcat] += $row['val'];
                $tpl_data['data']['total'] += $row['val'];
            }

        }
        $smarty->assign($tpl_data);
        $html = $smarty->fetch("table_statistics.tpl");
        return $html;

    }
    function setup()
    {
        $DB =& Database::singleton();
        if (PEAR::isError($DB)) {
            return PEAR::raiseError("Could not connect to database: ".$DB->getMessage());
        }

        $subprojects = Utility::getSubprojectList(); //array('1' => '6 Month Recruit', '2' => '12 Month Recruit', '3' => 'Control');
        if(isset($_REQUEST['site']) && $_REQUEST['site'] != '') {
            $ExtraSite_Criteria = 'AND (c.CenterID IS NULL OR c.CenterID=' . $_REQUEST['site'] . ')';
        }
        else {
            $ExtraSite_Criteria = '';
        }
        $this->tpl_data['Subprojects'] = $subprojects;
        $DB->select("SELECT s.subprojectid as rowid, 
                            COUNT(DISTINCT(c.PSCID)) as val 
                     FROM candidate as c LEFT JOIN session s ON (s.CandID=c.CandID) 
                     WHERE s.active='Y' and s.Cancelled='N' AND s.CenterID <> '1'        
                        AND c.Active='Y' AND c.Cancelled='N'
                        AND (s.Current_stage IN ('Visit', 'Screening')) 
        AND COALESCE(s.Screening,'') NOT IN ('Failure', 'Withdrawal')
        AND COALESCE(s.Visit,'') NOT IN ('Failure', 'Withdrawal')
                        $ExtraSite_Criteria
                     GROUP BY s.subprojectid", $result);
        foreach($result as $row) {
            $this->tpl_data['registered'][$row['rowid']]['visit'] = $row['val'];
            $this->tpl_data['registered']['visittotal'] += $row['val'];
        }

        $DB->select("SELECT s.subprojectid as rowid, count(DISTINCT(c.PSCID)) as val from candidate as c left join session s ON (s.CandID=c.CandID) WHERE coalesce(s.active, 'Y')='Y' and coalesce(s.Cancelled,'N')='N' AND c.CenterID <> '1' and c.PSCID <> 'scanner' and coalesce(s.visit_label, 'v06') in ('v06', 'v12', 'v18', 'v24', 'v36') AND c.Active='Y' AND c.Cancelled='N'
        $ExtraSite_Criteria group by s.subprojectid", $result);
        foreach($result as $row) {
            $this->tpl_data['registered'][$row['rowid']]['total'] = $row['val'];
            $this->tpl_data['registered']['total'] += $row['val'];
        }

	// Total, explicitly calculated instead of added in the loop to ensure there's no one double registered in 2 different cohorts
        $DB->select("SELECT count(distinct(c.PSCID)) from candidate as c WHERE c.PSCID<>'scanner' AND c.CenterID<>'1' AND c.Active='Y' AND c.Cancelled='N' 
        $ExtraSite_Criteria", $total);
        if (PEAR::isError($total)) {
            return PEAR::raiseError("DB Error: ".$total->getMessage());
        }
        list(,$total)=each($total[0]);
        $Total_candidates = $total;
        $this->tpl_data['Total_candidates'] = $Total_candidates;

        // Number of visits.
        // This is based on the EDI completion status, since the EDI
        // is done by every cohort at every visit
        $DB->select("SELECT count(DISTINCT c.PSCID) as val, s.SubprojectID as rowid FROM flag f join session s ON (s.ID=f.SessionID) join candidate c ON (c.CandID=s.CandID)  where f.Test_name IN 
            ('edi', 'mri_parameter_form', 'vineland_subject') 
        AND COALESCE(s.Screening,'') NOT IN ('Failure', 'Withdrawal')
        AND COALESCE(s.Visit,'') NOT IN ('Failure', 'Withdrawal')
                AND s.Active='Y' and s.Cancelled='N'
                AND c.Active='Y' and c.Cancelled='N'
                AND (f.Administration = 'All' OR f.Administration='Partial')
                AND s.Current_stage <> 'Recycling Bin'
                $ExtraSite_Criteria
        GROUP BY s.SubprojectID", $result);
        foreach($result as $row) {
            $this->tpl_data['edi'][$row['rowid']]['complete'] = $row['val'];
            $this->tpl_data['edi']['complete'] += $row['val'];
        }

        // Number of T1 candidates scanned
        $DB->select("SELECT count(DISTINCT c.PSCID) as val, s.SubprojectID as rowid FROM flag f JOIN mri_parameter_form mp USING(CommentID) join session s ON (s.ID=f.SessionID) join candidate c ON (c.CandID=s.CandID) WHERE f.Test_name='mri_parameter_form'
        AND COALESCE(s.Screening,'') NOT IN ('Failure', 'Withdrawal')
        AND COALESCE(s.Visit,'') NOT IN ('Failure', 'Withdrawal')
                AND s.Active='Y' and s.Cancelled='N'
                AND c.Active='Y' and c.Cancelled='N'
                AND f.Administration <> 'None'
                AND mp.T1_Scan_done='Complete'
                AND s.Current_stage <> 'Recycling Bin'
                $ExtraSite_Criteria
             GROUP BY s.SubprojectID", $result);
        foreach($result as $row) {
            $this->tpl_data['scanned'][$row['rowid']]['complete'] = $row['val'];
            $this->tpl_data['scanned']['complete'] += $row['val'];
        }
        
        // NUMBER OF CANDIDATES STATS TABLE

        
        // Adds a C to the start of the centerid, because that's how the
        // template is looking for it. Exclude DCC and UofA
        $DB->select("SELECT CONCAT('C', CenterID) as ID, CenterID as NumericID, PSCArea as LongName, Name as ShortName FROM psc WHERE CenterID IN (2, 3, 4, 5)", $centers);
        if(PEAR::isError($centers)) {
            return PEAR::raiseError("DB Error: ".$centers->getMessage());
        }
        $this->tpl_data['Centers'] = $centers;
        $this->tpl_data['Sites'] = array('' => 'All Sites');
        foreach ($centers as $row) {
            $this->tpl_data['Sites'][$row['NumericID']] = $row['LongName'];
            if($_REQUEST['site'] == $row['NumericID']) {
                $this->tpl_data['CurrentSite'] = array('ID' => $row['NumericID'], 'Name' => $row['LongName']);
            }
        }
        $this->tpl_data['Subprojects'] = Utility::getSubprojectList(); //array('1' => '6 Month Recruit', '2' => '12 Month Recruit', '3' => 'Control');
        $Visits = array ('6 Month' => 'v06', '12 Month' => 'v12', '18 Month' => 'v18', '24 Month' => 'v24', '36 Month' => 'v36');
        $this->tpl_data['Visits'] = $Visits;

        $instruments  = array_merge(
            array( '' => 'Recruit Gender Breakdown'),
                Utility::getAllInstruments()
        );
        $this->tpl_data['scored_instruments'] = Utility::getScoredInstruments(); 
        $this->tpl_data['all_instruments'] = Utility::getAllInstruments();
        if(isset($_REQUEST['instrument']) && $_REQUEST['instrument'] != '') {
            $Subcategories = array('Complete', 'Incomplete'); 
            $DB->select("SELECT count(*) as val, 
                                f.Data_entry as Subcat, 
                                c.CenterID as CenterID, 
                                s.SubprojectID as SubprojectID,
                                CASE s.visit_label
                                    WHEN 'v6' THEN 'v06'
                                    WHEN '6mo' THEN 'v06'
                                    WHEN '12m' THEN 'v12'
                                    WHEN '18mo' THEN 'v18'
                                    WHEN '24mo' THEN 'v24'
                                ELSE lower(s.visit_label) END as VLabel
                        FROM session s JOIN candidate c ON (s.CandID=c.CandID)
                            JOIN flag f ON (f.SessionID=s.ID)
                            JOIN $_REQUEST[instrument] i USING(CommentID)
                        WHERE s.Cancelled='N' AND s.Active='Y' AND
                            c.CenterID <> '1' AND f.Data_entry='Complete' AND
                            f.Administration='All' AND
                            f.CommentID NOT LIKE 'DDE%'
                    GROUP BY c.CenterID, SubprojectID, VLabel, Subcat
                    UNION
                    SELECT count(*) as val, 'Incomplete' as Subcat, 
                            c.CenterID as CenterID, 
                            s.SubprojectID as SubprojectID,
                                CASE s.visit_label
                                    WHEN '6mo' THEN 'v06'
                                    WHEN '12m' THEN 'v12'
                                    WHEN '18mo' THEN 'v18'
                                    WHEN '24mo' THEN 'v24'
                                ELSE lower(s.visit_label) END as VLabel
                    FROM session s JOIN candidate c USING(CandID) 
                        JOIN flag f ON (f.SessionID=s.ID) 
                        JOIN $_REQUEST[instrument] i USING(CommentID)
                    WHERE s.Cancelled='N' AND s.Active='Y' and s.CenterID <> 1
                    AND f.CommentID NOT LIKE 'DDE%' AND (f.Data_entry IS NULL OR f.Data_entry <> 'Complete')
                    GROUP BY c.CenterID, SubprojectID, VLabel, Subcat
            ", &$result);
            $this->tpl_data['RecruitsTable'] = $this->render_stats_table("Data Entry Completion Status for $_REQUEST[instrument]", $Subcategories, $Visits, "instrument", $instruments, $_REQUEST['instrument'], $centers, $result, "demographics");
        } else {
            $Subcategories = array('Male', 'Female');
            $DB->select("SELECT c.CenterID as CenterID, 
                            s.SubprojectID as SubprojectID, 
                            CASE s.visit_label
                                WHEN '6mo' THEN 'v06'
                                WHEN '12m' THEN 'v12'
                                WHEN '18mo' THEN 'v18'
                                WHEN '24mo' THEN 'v24'
                                ELSE lower(s.visit_label) END as VLabel,
                        c.gender as Subcat,
                        count(s.CandID) as val
                 FROM session s JOIN candidate c ON (s.CandID=c.CandID) 
                 WHERE s.Cancelled='N'  AND s.active='Y' AND s.CenterID <> '1'
                    AND ((s.Current_stage IN ('Visit', 'Screening')
                    AND s.SubprojectID IN (1, 2)) OR s.SubprojectID=3) 
       AND COALESCE(s.Screening,'') NOT IN ('Failure', 'Withdrawal')
        AND COALESCE(s.Visit,'') NOT IN ('Failure', 'Withdrawal')
                 GROUP BY c.CenterID, SubprojectID, VLabel, Subcat", &$result);
            if (PEAR::isError($result)) {
                return PEAR::raiseError("DB Error: ".$result->getMessage());
            }
            $this->tpl_data['RecruitsTable'] = $this->render_stats_table("Breakdown of Registered Candidates", $Subcategories, $Visits, "instrument", $instruments, '', $centers, $result, "demographics");
        }



	//---- BEHAVIORAL STATS -----
        $sites = array('2' => 'sea', '3' => 'phi', '4' => 'stl', '5' => 'unc');
        $mri_data = array();
        $DB->select("SELECT s.CenterID,
                            f.Data_Entry as Data_Entry,
                            CASE s.visit_label
                                WHEN '6mo' THEN 'v06'
                                WHEN '12m' THEN 'v12'
                                WHEN '18mo' THEN 'v18'
                                WHEN '24mo' THEN 'v24'
                                ELSE lower(s.visit_label) END as VLabel,
                            COUNT(s.CandID) as val
                        FROM session s JOIN candidate c ON (s.CandID=c.CandID)
                            JOIN flag f ON (f.SessionID=s.ID)
                        WHERE 
                        s.Cancelled='N' AND s.Active='Y' 
                        AND c.Cancelled='N' AND c.Active='Y' 
                        AND s.Current_stage <> 'Recycling Bin'
                            AND f.CommentID NOT LIKE 'DDE%' 
                        GROUP by s.CenterID, VLabel, f.Data_Entry", 
        $result);

        foreach($result as $row) {
            // Put some things into variables to make the lines shorter
            // so that they don't wrap. Note that "c"(enter array) needs to 
            // be a reference since we'll be modifying it.
            $center = $row['CenterID'];
            $vl = $row['VLabel'];
            $c =& $this->tpl_data['behaviour']['C' . $center];

            $c[$vl]['total'] += $row['val'];
            $c['all']['total'] += $row['val'];
            if($row['Data_Entry'] == 'Complete') {
                $c[$vl]['complete'] += $row['val'];
                $c['all']['complete'] += $row['val'];
            }
            if($c[$vl]['total'] != 0) {
                $c[$vl]['percent'] = 
                        floor($c[$vl]['complete'] / $c[$vl]['total']*100);
            }
            if($c['all']['total'] != 0) {
                $c['all']['percent'] = 
                        floor($c['all']['complete'] / $c['all']['total']*100);
            }
        }

        // DDE STATS
        $DB->select("SELECT s.CenterID, 
                            f.Data_Entry as Data_Entry, 
                            CASE s.visit_label
                                WHEN '6mo' THEN 'v06'
                                WHEN '12m' THEN 'v12'
                                WHEN '18mo' THEN 'v18'
                                WHEN '24mo' THEN 'v24'
                                ELSE lower(s.visit_label) END as VLabel,
                            COUNT(s.CandID) as val
                    FROM session as s JOIN candidate as c ON (s.CandID=c.CandID) JOIN flag as f ON (f.SessionID=s.ID) 
                    WHERE s.Cancelled='N' AND s.Active='Y' 
                        AND s.Current_stage <> 'Recycling Bin'
                        AND f.CommentID LIKE 'DDE%' 
                        AND c.Cancelled='N' AND c.Active='Y' 
                        AND (f.Test_name NOT LIKE '%parameter%' 
                                AND f.Test_name NOT LIKE '%radiological%' 
                                AND f.Test_name NOT LIKE '%vineland%')
                    GROUP BY s.CenterID, VLabel, f.Data_Entry ORDER BY c.PSCID;",
        $result);
        foreach($result as $row) {
            $center = $row['CenterID'];
            $vl = $row['VLabel'];
            $c =& $this->tpl_data['dde']['C' . $center];

            $c[$vl]['total'] += $row['val'];
            $c['all']['total'] += $row['val'];
            if($row['Data_Entry'] == 'Complete') {
                $c[$vl]['complete'] += $row['val'];
                $c['all']['complete'] += $row['val'];
            }
            if($c[$vl]['total'] != 0) {
                $c[$vl]['percent'] = 
                        floor($c[$vl]['complete'] / $c[$vl]['total']*100);
            }
            if($c['all']['total'] != 0) {
                $c['all']['percent'] = 
                        floor($c['all']['complete'] / $c['all']['total']*100);
            }
        }

        $MRISubcategories = array('Complete', 'Partial Run', 'No Scan'); 
        $MRIOptions = array('T1' => 'T1', 
            'T2' => 'T2', 
            'T1T2' => 'T1 and T2',
            'DTI' => 'DTI',
            'BOLD' => 'BOLD',
            'Spectroscopy' => 'Spectroscopy'
        );
        if($_REQUEST['mri_type']) {
            $MRI_Type = $_REQUEST['mri_type'];
            $MRI_Type_Field = $_REQUEST['mri_type'] . "_Scan_Done";
            $MRIHeader = "$MRI_Type Breakdown";
            if($_REQUEST['mri_type'] == 'T1T2') {
                $MRI_Type_Field = "T1_Scan_Done='Complete' and T2_Scan_Done='Complete'";
                $MRIHeader = "T1 and T2 Complete Breakdown";
                $CaseStatement = "
                         CASE($MRI_Type_Field)
                            WHEN True then 'Complete'
                            WHEN False Then 'Incomplete'
                            ELSE 'Incomplete'
                         END";
                $MRISubcategories = array('Complete', 'Incomplete');
            } else {
                $CaseStatement = "
                         CASE($MRI_Type_Field)
                            WHEN 'Partial' THEN 'Partial Run'
                            WHEN 'No' THEN 'No Scan'
                            ELSE $MRI_Type_Field
                         END";
            }
        } else {
            $MRI_Type_Field = 'T1_Scan_Done';
            $MRI_Type = 'T1';
            $MRIHeader = "T1 Scan Done Breakdown";
            $CaseStatement = "
                     CASE($MRI_Type_Field)
                        WHEN 'Partial' THEN 'Partial Run'
                        WHEN 'No' THEN 'No Scan'
                        ELSE $MRI_Type_Field
                     END";
        }
        $DB->select("SELECT s.SubprojectID, 
                         c.CenterID, 
                         lower(s.Visit_label) as VLabel,
                         $CaseStatement as Subcat,
                         COUNT(*) as val 
                  FROM mri_parameter_form m JOIN flag f USING (CommentID) 
                        JOIN session s ON (f.SessionID=s.ID) 
                        JOIN candidate c ON (c.CandID=s.CandID) 
                  WHERE s.Current_stage <> 'Recycling Bin' 
                        AND f.Administration <> 'None'
                        AND s.Cancelled='N'
                        AND s.Active='Y'
                        AND c.Cancelled='N'
                        AND c.Active='Y'
                  GROUP BY Subcat, s.SubprojectID, c.CenterID, s.Visit_label", &$result);
        $M_Visits = array ('6 Month' => 'v06', '12 Month' => 'v12', '24 Month' => 'v24');
        $this->tpl_data['MRI_Done_Table'] = $this->render_stats_table($MRIHeader, $MRISubcategories, $M_Visits, "mri_type", $MRIOptions, $MRI_Type, $centers, $result, "mri");

        $DB->select("SELECT s.SubprojectID, 
                         c.CenterID, 
                         CASE s.visit_label
                            WHEN '6mo' THEN 'v06'
                            WHEN '12m' THEN 'v12'
                            WHEN '18mo' THEN 'v18'
                            WHEN '24mo' THEN 'v24'
                         ELSE lower(s.visit_label) END as VLabel,
                         COUNT(*) as val 
                  FROM mri_parameter_form m JOIN flag f USING (CommentID) 
                        JOIN session s ON (f.SessionID=s.ID) 
                        JOIN candidate c ON (c.CandID=s.CandID) 
                  WHERE T1_Scan_Done='Complete' 
                        AND s.Current_stage <> 'Recycling Bin' 
                        AND f.Administration <> 'None'
                        AND s.Cancelled='N'
                        AND s.Active='Y'
                  GROUP BY s.SubprojectID, c.CenterID, s.Visit_label;", 
        $result);
        foreach($result as $row) {
            $center = $row['CenterID'];
            $cohort = $row['SubprojectID'];
            $vl = $row['VLabel'];
            $c =& $this->tpl_data['mri_total'][$cohort]['C' . $center];

            $c[$vl] += $row['val'];
            $this->tpl_data['mri_total']['C' . $center][$vl]['total'] += $row['val'];
            $this->tpl_data['mri_total'][$cohort]['total'] += $row['val'];
            $this->tpl_data['mri_total']['total'] += $row['val'];

        }

        // MRI INTEGRITY STATS 
        // MRI parameter form is completed, but nothing in tarchive
        $DB->select("SELECT COUNT(distinct f.CommentID) as val, 
                            s.CenterID as CenterID
                     FROM flag f JOIN session s ON (f.SessionID=s.ID) 
                     LEFT JOIN mri_parameter_form m ON (m.CommentID=f.CommentID)
                     -- LEFT JOIN tarchive t ON (s.CandID=MID(t.PatientName, 9, 6))
                     LEFT JOIN tarchive t ON (s.CandID=MID(t.PatientName, 9, 6) AND MID(t.PatientName, 16, 3)=s.Visit_label)
                     LEFT JOIN candidate c ON (s.CandID=c.CandID)
                     WHERE f.CommentID NOT LIKE 'DDE%' 
                            AND f.Test_name='mri_parameter_form' 
                            and f.Administration <> 'None'
                            and t.TarchiveID IS NULL
                            AND s.Active='Y' 
                            AND s.Cancelled='N' 
                            AND t.TarchiveID IS NULL 
                            AND f.Data_entry='Complete'
                            AND (m.T1_Scan_done IS NULL OR m.T1_Scan_done <> 'No')
                     GROUP BY s.CenterID;", $result);
        foreach($result as $row) {
            $this->tpl_data['mri_errors'][$row['CenterID']]['no_tarchive'] = $row['val'];
        }

        // MRI parameter form completed, but nothing in browser
        $DB->select("SELECT s.CenterID as CenterID, 
                            COUNT(distinct f.CommentID) as val
                     FROM mri_parameter_form m LEFT JOIN flag f ON (f.CommentID=m.CommentID)
                        LEFT JOIN session s ON (s.ID=f.SessionID) 
                        LEFT JOIN files fi ON (fi.SessionID=f.SessionID) 
                     WHERE (m.DTI_Scan_done <> 'No' 
                            OR m.T2_Scan_done <> 'No' 
                            OR m.T1_Scan_done <> 'No') 
                           AND fi.FileID IS NULL 
                           AND f.Data_entry = 'Complete'
                           AND s.Active='Y' AND s.Cancelled = 'N'
                     GROUP by s.CenterID;", $result);
        foreach($result as $row) {
            $this->tpl_data['mri_errors'][$row['CenterID']]['no_browser'] = $row['val'];
        }

        // MRI Browser populated, but no MRI parameter form completed.
        $DB->select("SELECT s.CenterID as CenterID, COUNT(distinct s.ID) as val
                        FROM files LEFT JOIN session s ON (files.SessionID=s.ID)
                        LEFT JOIN flag f on (f.SessionID=s.ID
                            AND f.Test_name='mri_parameter_form' 
                            AND f.CommentID NOT LIKE 'DDE%') 
                        LEFT JOIN mri_parameter_form mpf ON (mpf.CommentID=f.CommentID)
                        LEFT JOIN candidate c ON (c.CandID=s.CandID)
                        WHERE s.Active='Y' and s.Cancelled='N' 
                            AND (f.ID IS NULL OR f.Data_entry <> 'Complete') 
                            AND c.PSCID <> 'scanner'
                        GROUP BY s.CenterID", $result);
        foreach($result as $row) {
            $this->tpl_data['mri_errors'][$row['CenterID']]['no_parameter'] = $row['val'];
        }


        // TOP MRI TABLE

        // Below this has not been optimized. It's kind of ugly.
          foreach($centers as $center) {
              $id = $center['NumericID'];
              $name = $center['LongName'];
	// -------- MRI STATS---------------
            $DB->select("SELECT COUNT(distinct s.CandID, s.Visit_label) FROM tarchive as t, session as s WHERE MID(t.PatientName,9,6)=s.CandID AND s.CenterID={$center['NumericID']};", $result23);
              if (PEAR::isError($result23)) {
                  return PEAR::raiseError("DB Error: ".$result23->getMessage());
              }
              list(,$result23)=each($result23[0]);
              $work_station_count = $result23;
              
              $DB->select("SELECT COUNT(s.CandID) FROM session as s, psc as p, candidate as c WHERE c.CandID=s.CandID AND s.Active='Y' AND s.Cancelled='N' AND s.CenterID=p.CenterID  AND s.Scan_done='Y' AND s.CenterID={$id} ORDER BY s.CandID;", $result24);
                if (PEAR::isError($result24)) {
                    return PEAR::raiseError("DB Error: ".$result24->getMessage());
                }
                list(,$result24)=each($result24[0]);
                $claimed_count = $result24;
                
                $DB->select("SELECT COUNT(s.CandID) FROM mri_parameter_form as pf, session as s, flag as f, psc as p, candidate as c WHERE f.CommentID=pf.CommentID AND s.ID=f.SessionID AND c.CandID=s.CandID AND s.Active='Y' AND s.Cancelled='N' AND s.CenterID=p.CenterID AND pf.Data_entry_completion_status='Complete' AND s.CenterID={$id} ORDER BY p.Name;", $result25);
                  if (PEAR::isError($result25)) {
                      return PEAR::raiseError("DB Error: ".$result25->getMessage());
                  }
                  list(,$result25)=each($result25[0]);
                  $forms_count = $result25;
                $three_scans = $DB->selectOne("SELECT count(distinct CandID) FROM session v06 
                        WHERE v06.Scan_done='Y' AND v06.Active='Y' AND v06.Cancelled='N' AND v06.Visit_label='v06' 
                            AND EXISTS (SELECT 'x' FROM session v12 
                                            WHERE v12.Scan_done='Y' AND v12.Active='Y' AND v12.Cancelled='N' AND v12.Visit_label='v12' AND v06.CANDID=v12.CandID) 
                            AND EXISTS (SELECT 'x' FROM session v24
                                            WHERE v24.Scan_done='Y' AND v24.Active='Y' AND v24.Cancelled='N' AND v24.Visit_label='v24' AND v06.CANDID=v24.CandID) 
                            AND v06.CenterID='{$id}'");
                print "$id";
                print "asdf $three_scans";
              
              $mri_data[] = array('name' => $name,  'work_station_count' => $work_station_count, 'claimed_count' => $claimed_count, 'forms_count' => $forms_count, 'all_three_scans' => $three_scans);
              
        }

        $this->tpl_data['mri_data'] = $mri_data;
        $this->tpl_data['reliability_completion'] = $this->getReliabilityData();

    } // End function


    function _getCrossSiteReliabilityData($name, $inst_name, $cutoff, $extra_where="") {
        $data = $this->_getSingleReliabilityData($name, $inst_name, $cutoff,
            " $extra_where AND CommentID NOT LIKE CONCAT('%', CASE reliability_center_id WHEN 1 THEN 'dcc' WHEN 2 THEN 'SEA' WHEN 3 THEN 'PHI' WHEN 4 THEN 'STL' WHEN 5 THEN 'UNC' WHEN 6 THEN 'UofA' END, '%')");
        $data['name'] = $name . ' (Cross Site)';
        return $data;
    }
    function _getWithinSiteReliabilityData($name, $inst_name, $cutoff, $extra_where = "") {
        $data = $this->_getSingleReliabilityData($name, $inst_name, $cutoff,
            " $extra_where AND CommentID like CONCAT('%', CASE reliability_center_id WHEN 1 THEN 'dcc' WHEN 2 THEN 'SEA' WHEN 3 THEN 'PHI' WHEN 4 THEN 'STL' WHEN 5 THEN 'UNC' WHEN 6 THEN 'UofA' END, '%')");
        $data['name'] = $name . ' (Within Site)';
        return $data;
    }
    function _getSingleReliabilityData($name, $inst_name, $cutoff, $extra_where = '') {
        if(isset($_REQUEST['site']) && $_REQUEST['site'] != '') {
            $extra_where .= ' AND c.CenterID=' . $_REQUEST['site'];
        }
        $db = Database::singleton();
        $ret = array();
        $ret['name'] = $name;
        $ret['complete'] = $db->selectOne("SELECT count(*) from reliability r JOIN flag f USING(CommentID) JOIN session s ON (s.ID=f.SessionID) JOIN candidate c ON (c.CandID=s.CandID) where Instrument='$inst_name' and Invalid <> 'yes' and Reliability_score IS NOT NULL AND c.CenterID <> 1 $extra_where");
        $ret['reliable'] = $db->selectOne("SELECT count(*) from reliability r JOIN flag f USING(CommentID) JOIN session s ON (s.ID=f.SessionID) JOIN candidate c ON (c.CandID=s.CandID)where Instrument='$inst_name' and Invalid <> 'yes' and Reliability_score IS NOT NULL and Reliability_score > $cutoff AND c.CenterID <> 1 $extra_where");
        $ret['total'] = $db->selectOne("SELECT count(*) from reliability r JOIN flag f USING(CommentID) JOIN session s ON (s.ID=f.SessionID) JOIN candidate c ON (c.CandID=s.CandID) where Instrument='$inst_name' and Invalid <> 'yes' AND c.CenterID <> 1 $extra_where");
        if($ret['total'] == 0) {
            // These should probably be indeterminate instead of 0, but 0
            // looks cleaner.
            $ret['percent_complete'] = '0';
            $ret['percent_reliable'] = '0';
        } else {
            $ret['percent_complete'] = round($ret['complete'] / $ret['total'] * 100);
            $ret['percent_reliable'] = round($ret['reliable'] / $ret['total'] * 100);
        }
        return $ret;
    }
    function getReliabilityData() {
        // Whether something is reliable or not isn't stored in the database,
        // but calculated on the fly. 
        // As a result, we need to manually calculate it and maintain for each
        // type of thing Tanya wants stats for here separately

        // Thresholds was copy/pasted from 
        $thresholds = NDB_Menu_Filter_Reliability::getThreshholds();
        $tests = array(
            'adi_r_proband' => 'ADI-R (Proband)',
            'adi_r_subject' => 'ADI-R (Subject)',
            'ados_module1' => 'ADOS (Module 1)',
            'ados_module2' => 'ADOS (Module 2)',
            'aosi' => 'AOSI',
            'csbs' => 'CSBS'

        );
        $within_cross = array('adi_r_subject', 'ados_module1', 'ados_module2', 'aosi', 'csbs');

        $reliable = array();
        foreach($tests as $inst => $name) {
            if(in_array($inst, $within_cross)) {
                if($inst == 'aosi') {
                    $reliable[] = $this->_getWithinSiteReliabilityData(
                            $name . " v06", 
                            $inst, $thresholds[$inst], 
                            " AND EXISTS (SELECT 'x' FROM flag f JOIN session s ON (s.ID=f.SessionID) WHERE f.CommentID=r.CommentID and lower(s.Visit_label)='v06')");
                    $reliable[] = $this->_getCrossSiteReliabilityData(
                            $name . " v06", 
                            $inst, $thresholds[$inst], 
                            " AND EXISTS (SELECT 'x' FROM flag f JOIN session s ON (s.ID=f.SessionID) WHERE f.CommentID=r.CommentID and lower(s.Visit_label)='v06')");
                    $reliable[] = $this->_getWithinSiteReliabilityData(
                            $name . " v12", 
                            $inst, $thresholds[$inst], 
                            " AND EXISTS (SELECT 'x' FROM flag f JOIN session s ON (s.ID=f.SessionID) WHERE f.CommentID=r.CommentID and lower(s.Visit_label)='v12')");
                    $reliable[] = $this->_getCrossSiteReliabilityData(
                            $name . " v12", 
                            $inst, $thresholds[$inst], 
                            " AND EXISTS (SELECT 'x' FROM flag f JOIN session s ON (s.ID=f.SessionID) WHERE f.CommentID=r.CommentID and lower(s.Visit_label)='v12')");
                } else {
                    $reliable[] = $this->_getWithinSiteReliabilityData($name, 
                            $inst, $thresholds[$inst]);
                    $reliable[] = $this->_getCrossSiteReliabilityData($name, 
                            $inst, $thresholds[$inst]);
                }
            } else {
                $reliable[] = $this->_getSingleReliabilityData($name, 
                    $inst, $thresholds[$inst]);
            }
        }

        return $reliable;
    }
} // End class
?>
