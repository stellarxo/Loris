<?php
require_once 'NDB_Menu.class.inc';

/**
 * The welcome menu
 * @package main
 */
class NDB_Menu_statistics extends NDB_Menu
{
    function setup()
    {
        $DB =& Database::singleton();
        if (PEAR::isError($DB)) {
            return PEAR::raiseError("Could not connect to database: ".$DB->getMessage());
        }

        $subprojects = array('1' => '6 Month Recruit', '2' => '12 Month Recruit', '3' => 'Control');
        $this->tpl_data['Subprojects'] = $subprojects;
        $DB->select("SELECT s.subprojectid as rowid, 
                            COUNT(DISTINCT(c.PSCID)) as val 
                     FROM candidate as c LEFT JOIN session s ON (s.CandID=c.CandID) 
                     WHERE s.active='Y' and s.Cancelled='N' AND s.CenterID <> '1'        
                        AND (s.Current_stage IN ('Visit', 'Screening'))
                     GROUP BY s.subprojectid", $result);
        foreach($result as $row) {
            $this->tpl_data['registered'][$row['rowid']]['visit'] = $row['val'];
            $this->tpl_data['registered']['visittotal'] += $row['val'];
        }

        $DB->select("SELECT s.subprojectid as rowid, count(DISTINCT(c.PSCID)) as val from candidate as c left join session s ON (s.CandID=c.CandID) WHERE coalesce(s.active, 'Y')='Y' and coalesce(s.Cancelled,'N')='N' AND c.CenterID <> '1' and c.PSCID <> 'scanner' and coalesce(s.visit_label, 'v06') in ('v06', 'v12', 'v18', 'v24', 'v36', '6mo', '12mo') group by s.subprojectid", $result);
        foreach($result as $row) {
            $this->tpl_data['registered'][$row['rowid']]['total'] = $row['val'];
            $this->tpl_data['registered']['total'] += $row['val'];
        }

	// Total, explicitly calculated instead of added in the loop to ensure there's no one double registered in 2 different cohorts
        $DB->select("SELECT count(distinct(c.PSCID)) from candidate as c WHERE c.PSCID<>'scanner' AND c.CenterID<>'1';", $total);
        if (PEAR::isError($total)) {
            return PEAR::raiseError("DB Error: ".$total->getMessage());
        }
        list(,$total)=each($total[0]);
        $Total_candidates = $total;
        $this->tpl_data['Total_candidates'] = $Total_candidates;


        // NUMBER OF CANDIDATES STATS TABLE

        
        // Adds a C to the start of the centerid, because that's how the
        // template is looking for it. Exclude DCC and UofA
        $DB->select("SELECT CONCAT('C', CenterID) as ID, CenterID as NumericID, PSCArea as LongName, Name as ShortName FROM psc WHERE CenterID IN (2, 3, 4, 5)", $centers);
        if(PEAR::isError($centers)) {
            return PEAR::raiseError("DB Error: ".$centers->getMessage());
        }
        $this->tpl_data['Centers'] = $centers;
        $this->tpl_data['Subprojects'] = array('1' => '6 Month Recruit', '2' => '12 Month Recruit', '3' => 'Control');
        $this->tpl_data['Visits'] = array ('6 Month' => 'v06', '12 Month' => 'v12', '18 Month' => 'v18', '24 Month' => 'v24', '36 Month' => 'v36');

        $this->tpl_data['instruments'] = array_merge(
            array( '' => 'Recruit Gender Breakdown'),
            Utility::getAllInstruments()
        );
        if(isset($_REQUEST['instrument']) && $_REQUEST['instrument'] != '') {
            $this->tpl_data['instrument'] = $_REQUEST['instrument'];
            $this->tpl_data['RecruitHeader'] = "Data Entry Completion Status Breakdown for $_REQUEST[instrument]";
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
                                    -- WHEN 'v6' THEN 'v06'
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

            /*$DB->select("SELECT count(*) as val, 
                        COALESCE(i.Data_entry_completion_status,'Confused') as Subcat, 
                        c.CenterID as CenterID, 
                        s.SubprojectID as SubprojectID, 
                        CASE s.visit_label
                            WHEN 'v6' THEN 'v06'
                            WHEN '6mo' THEN 'v06'
                            WHEN '12m' THEN 'v12'
                            WHEN '18mo' THEN 'v18'
                            WHEN '24mo' THEN 'v24'
                            ELSE lower(s.visit_label) END as VLabel
                    FROM session s JOIN candidate c USING (CandID) LEFT JOIN flag f ON (s.ID=f.SessionID)
                        LEFT JOIN $_REQUEST[instrument] i USING(CommentID)
                    WHERE s.active='Y' AND s.CenterID <> '1' AND s.Cancelled='N'
                        AND (CommentID IS NULL OR CommentID NOT LIKE 'DDE%') AND (f.Test_name IS NULL OR f.Test_name='$_REQUEST[instrument]')
                    AND ((s.Current_stage IN ('Visit', 'Screening')
                    AND s.SubprojectID IN (1, 2)) OR s.SubprojectID=3) 
                    GROUP BY c.CenterID, SubprojectID, VLabel, Subcat", &$result); */
        } else {
            $Subcategories = array('Male', 'Female');
            $this->tpl_data['RecruitHeader'] = "Breakdown of Registered Candidates";
            $DB->select("SELECT c.CenterID as CenterID, 
                            s.SubprojectID as SubprojectID, 
                            CASE s.visit_label
                                WHEN 'v6' THEN 'v06'
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
                 GROUP BY c.CenterID, SubprojectID, VLabel, Subcat", &$result);
        }
        if (PEAR::isError($result)) {
            return PEAR::raiseError("DB Error: ".$result->getMessage());
        }

        foreach($result as $row) {
            $subproj = $row['SubprojectID'];
            $vl = $row['VLabel'];
            $subcat = $row['Subcat'];
            $center = $row['CenterID'];
            $this->tpl_data['recruits'][$subproj]['C' . $center][$vl][$subcat] = $row['val'];

            // Keep a running tally so that we can avoid calculating things
            // in the template
            $this->tpl_data['recruits'][$subproj][$vl][$subcat] += $row['val'];
            $this->tpl_data['recruits'][$subproj][$vl]['total'] += $row['val'];
            $this->tpl_data['recruits'][$vl][$subcat] += $row['val'];
            $this->tpl_data['recruits'][$vl]['total'] += $row['val'];
            $this->tpl_data['recruits'][$subproj]['total'] += $row['val'];

            $this->tpl_data['recruits']['C' . $center][$subcat] += $row['val'];
            $this->tpl_data['recruits']['C' . $center][$vl][$subcat] += $row['val'];
        }
        $this->tpl_data['Subcategories'] = $Subcategories;


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
                        WHERE s.Cancelled='N' AND s.Active='Y' 
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
                        AND f.CommentID LIKE 'DDE%' 
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

        // MRI Browser populated, but no MRI parameter form completed.
        $DB->select("SELECT s.CenterID as CenterID, COUNT(distinct s.ID) as val
                        FROM files LEFT JOIN session s ON (files.SessionID=s.ID)
                        LEFT JOIN flag f on (f.SessionID=s.ID
                            AND f.Test_name='mri_parameter_form' 
                            AND f.CommentID NOT LIKE 'DDE%') 
                        LEFT JOIN mri_parameter_form mpf ON (mpf.CommentID=f.CommentID)
                        WHERE s.Active='Y' and s.Cancelled='N' 
                            AND (f.ID IS NULL OR f.Data_entry <> 'Complete')
                        GROUP BY s.CenterID", $result);
        foreach($result as $row) {
            $this->tpl_data['mri_errors'][$row['CenterID']]['no_parameter'] = $row['val'];
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
                     GROUP by s.CenterID;", $result);
        foreach($result as $row) {
            $this->tpl_data['mri_errors'][$row['CenterID']]['no_browser'] = $row['val'];
        }

        // MRI parameter form is completed, but nothing in tarchive
        $DB->select("SELECT COUNT(distinct f.CommentID) as val, 
                            s.CenterID as CenterID
                     FROM flag f JOIN session s ON (f.SessionID=s.ID) 
                     LEFT JOIN mri_parameter_form m ON (m.CommentID=f.CommentID)
                     LEFT JOIN tarchive t ON (s.CandID=MID(t.PatientName, 9, 6))
                     WHERE f.CommentID NOT LIKE 'DDE%' 
                            AND f.Test_name='mri_parameter_form' 
                            AND s.Active='Y' 
                            AND s.Cancelled='N' 
                            AND t.TarchiveID IS NULL 
                            AND f.Data_entry='Complete'
                     GROUP BY s.CenterID;", $result);
        foreach($result as $row) {
            $this->tpl_data['mri_errors'][$row['CenterID']]['no_tarchive'] = $row['val'];
        }



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
              
              $mri_data[] = array('name' => $name,  'work_station_count' => $work_station_count, 'claimed_count' => $claimed_count, 'forms_count' => $forms_count);
              
        }
        $this->tpl_data['mri_data'] = $mri_data;
    } // End function
} // End class
?>
