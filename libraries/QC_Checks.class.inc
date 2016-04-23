<?php
require_once "NDB_Client.class.inc";
/**
 * Queries database for certain parameter and values to check validity of data
 *
 * QC Checks class
 * @package main
 */

class QC_Checks {

    function __construct($site) {
        $this->site = $site;    
    }

    function run() {
        $factory = NDB_Factory::singleton();
        $DB = $factory->Database();
        $list_of_sites = Utility::getSiteList(false);
        print " \nQC REPORT FOR SITE ".$list_of_sites[$this->site]. "\n\n";       

        $tests = $DB->pselect("SELECT Test_name FROM test_names WHERE Test_name NOT LIKE '%_proband' AND Test_name NOT LIKE 'EARLI%' AND Test_name NOT LIKE 'figs%' AND Test_name NOT LIKE 'ACEFamilyMedicalHistory' AND Test_name NOT LIKE 'dna_tracking' AND Test_name NOT LIKE 'LENA_DataTrackingForm' AND Test_name NOT LIKE 'SRS2%' AND Test_name NOT LIKE 'parental_stress_scale'", array()) ;
        /* ************************************************************************* */
        // Determine instruments where administration < DoB, or sessions where Visit < DoB
        /* ************************************************************************* */
        print "\n SESSIONS WITH ADMINISTRATION BEFORE DOB\n";
        print"---------------------------------------\n";
        $queries = array("SELECT c.PSCID, c.CandID, s.Visit_label, 'Date_visit' FROM candidate c LEFT JOIN session s USING (CandID) WHERE s.Date_visit < c.DoB AND COALESCE(s.Visit, 'NotFailure') <> 'Failure' AND c.CenterID = $this->site");

        foreach($tests as $row) {
            $test = $row['Test_name'];
            if($test == 'tsi') {
                continue;
            }
            $queries[] = "SELECT c.PSCID, c.CandID, s.Visit_label, '$test' FROM candidate c LEFT JOIN session s USING (CandID) LEFT JOIN flag f ON (f.SessionID=s.ID) LEFT JOIN $test t USING (CommentID) WHERE f.Test_name=" . $DB->quote($test)  . " AND t.Date_taken < c.DoB AND f.Data_entry='Complete' AND COALESCE(s.Visit, 'NotFailure') <> 'Failure' AND c.CenterID = $this->site";            
            $query = implode($queries, " UNION ");
            //print "$query\n";
            $bad_entries = $DB->pselect($query . " ORDER BY PSCID", array());
            foreach($bad_entries as $row) {
                print implode($row, "\t");
                print "\n";
            }

        }
        //exit(0);
        /* ************************************************************************* */
        // Determine sessions where Date_taken of visit n > Date taken of visit n+1
        /* ************************************************************************* */
        print "\n\nSESSIONS WITH VISIT N AFTER VISIT N+1\n";
        print "-------------------------------------\n";
        foreach($tests as $test_row) {
            $test = $test_row['Test_name'];
            $instrument_query = "SELECT c.PSCID, c.CandID, t.Date_taken, s.Visit_label, f.CommentID FROM candidate c LEFT JOIN session s USING (CandID) LEFT JOIN flag f ON (f.SessionID=s.ID) JOIN $test t USING (CommentID) WHERE f.Test_name=" . $DB->quote($test)  . " AND f.CommentID NOT LIKE 'DDE%' AND s.Active='Y' AND c.Active='Y' AND t.Date_taken IS NOT NULL  AND f.Data_entry='Complete' AND COALESCE(s.Visit, 'NotFailure') <> 'Failure' AND c.CenterID = $this->site ORDER BY PSCID, Visit_label ";
            $instrument_data = $DB->pselect($instrument_query, array());
            //    print_r($instrument_data);
            $LastCandidate = '';
            $LastDateTaken = 0;
            $LastCommentID = '';
            foreach($instrument_data as $row) {
                if($row['PSCID'] != $LastCandidate) {
                    $LastCandidate = $row['PSCID'];
                    $LastDateTaken = $row['Date_taken'];
                    $LastVisit = $row['Visit_label'];
                    $LastCommentID= $row['CommentID'];
                    continue;
                }
                if($LastDateTaken > $row['Date_taken']) {
                    $disp = array($row['PSCID'], $row['CandID'], $row['Visit_label'], $test, $LastVisit . ' > ' . $row['Visit_label']);
                    print implode($disp, "\t");
                    print "\n";
                }
                $LastCandidate = $row['PSCID'];
                $LastDateTaken = $row['Date_taken'];
                $LastVisit = $row['Visit_label'];
                $LastCommentID= $row['CommentID'];

            }
        }
          /* ************************************************************************* */
        // Determine sessions where Date_taken of visit n = Date taken of visit n+1
        /* ************************************************************************* */
        print "\n\nSESSIONS WITH VISIT N IS SAME DATE AS VISIT N+1\n";
        print "-------------------------------------\n";
        foreach($tests as $test_row) {
            $test = $test_row['Test_name'];
            $instrument_query = "SELECT c.PSCID, c.CandID, t.Date_taken, s.Visit_label, f.CommentID FROM candidate c LEFT JOIN session s USING (CandID) LEFT JOIN flag f ON (f.SessionID=s.ID) JOIN $test t USING (CommentID) WHERE f.Test_name=" . $DB->quote($test)  . " AND f.CommentID NOT LIKE 'DDE%' AND s.Active='Y' AND c.Active='Y' AND t.Date_taken IS NOT NULL  AND f.Data_entry='Complete' AND COALESCE(s.Visit, 'NotFailure') <> 'Failure' AND c.CenterID = $this->site ORDER BY PSCID, Visit_label ";
            $instrument_data = $DB->pselect($instrument_query, array());
            //    print_r($instrument_data);
            $LastCandidate = '';
            $LastDateTaken = 0;
            $LastCommentID = '';
            foreach($instrument_data as $row) {
                if($row['PSCID'] != $LastCandidate) {
                    $LastCandidate = $row['PSCID'];
                    $LastDateTaken = $row['Date_taken'];
                    $LastVisit = $row['Visit_label'];
                    $LastCommentID= $row['CommentID'];
                    continue;
                }
                if($LastDateTaken == $row['Date_taken']) {
                    $disp = array($row['PSCID'], $row['CandID'], $row['Visit_label'], $test, $LastVisit . ' = ' . $row['Visit_label']);
                    print implode($disp, "\t");
                    print "\n";
                }
                $LastCandidate = $row['PSCID'];
                $LastDateTaken = $row['Date_taken'];
                $LastVisit = $row['Visit_label'];
                $LastCommentID= $row['CommentID'];

            }
        }


        print "\n\nSESSIONS WITH DUPLICATE SCANS\n";
        print"-------------------------------------\n";
        $query = "SELECT c.PSCID, c.CandID, s.Visit_label, pf.Value, count(*) from parameter_file pf left join files f ON (f.SeriesUID=pf.Value) left join session s ON (s.ID=f.SessionID) left join candidate c USING (CandID) where ParameterTypeID=151 AND c.CenterID = $this->site group by Value having count(*) > 1 ORDER BY c.PSCID";

        $results = $DB->pselect($query, array());

        foreach($results as $row) {
            print "$row[PSCID]\t$row[CandID]\t$row[Visit_label]\t$row[Value]\n";
        }

        print "\n\nSITES WITH LAST LEGO SCAN MORE THAN 2 MONTHS AGO\n";
        print "--------------------------------------------------- \n";
        $query = "SELECT psc.MRI_Alias, MAX(pf.Value) as LastLego from files f left join parameter_file pf on (pf.FileID=f.FileID AND pf.ParameterTypeID=67) LEFT JOIN session s ON (s.ID=f.SessionID) LEFT JOIN psc ON (psc.CenterID=s.CenterID) WHERE File like '%lego%' AND s.CenterID = $this->site GROUP BY s.CenterID HAVING MAX(pf.Value) < :cutoff";
        $results = $DB->pselect($query, array("cutoff" => date("Ymd", strtotime('-2 months'))));
        print "\nSite\tLast Lego\n";
        foreach($results as $row) {
            print "$row[MRI_Alias]\t$row[LastLego]\n";
        }
        print "\n\nSCANS THAT FAILED INSERTION IN LAST WEEK\n";
        print"-------------------------------------\n";
        $data = $DB->pselect("SELECT CandID, c.PSCID, time_run, series_description FROM mri_protocol_violated_scans LEFT JOIN candidate c USING (CandID) WHERE time_run > DATE_SUB(now(), INTERVAL 1 WEEK) AND c.CenterID = $this->site ORDER BY time_run DESC" , array());
        foreach($data as $row) {
            print implode("\t", $row);
            print "\n";
        }
        print "\n\n CANDIDATE THAT HAVE MORE THAN 1 ADOS MODULE ADMINISTRATION = All/Partial \n";
        print "--------------------------------------\n";
        $data = $DB->pselect("SELECT c.PSCID,c.CandID,f1.Administration as A1,f2.Administration as A2,f3.Administration as A3 from candidate c JOIN session s on s.CandID=c.CandID  join flag f1 on ( s.ID=f1.SessionID AND f1.Test_name='ados_module1' AND f1.CommentID NOT LIKE 'DDE%' ) join flag f2 on ( s.ID=f2.SessionID AND f2.Test_name='ados_module2' AND f2.CommentID NOT LIKE 'DDE%' ) join flag f3 on ( s.ID=f3.SessionID AND f3.Test_name='ados_module3' AND f3.CommentID NOT LIKE 'DDE%' ) WHERE s.CenterID IN (2,3,4,5) AND c.Active='Y' AND c.CenterID = $this->site", array());
        $fields = array('All', 'Partial');

        foreach($data as $row) {
            if(!empty($row['A1']) || !empty($row['A2']) || !empty($row['A3'])) {
                if(in_array($row['A1'] , $fields) && (in_array($row['A2'], $fields) || in_array($row['A3'], $fields))) {
                    print implode("\t", $row);
                    print "\n";
                }
            }

        }
        print "\n\n CANDIDATE THAT HAVE MORE THAN 1 ADOS2 MODULE ADMINISTRATION = All/Partial \n";
        $data = $DB->pselect("SELECT c.PSCID,c.CandID,f1.Administration as A1,f2.Administration as A2,f3.Administration as A3 from candidate c JOIN session s on s.CandID=c.CandID  join flag f1 on ( s.ID=f1.SessionID AND f1.Test_name='ados2_module1' AND f1.CommentID NOT LIKE 'DDE%' ) join flag f2 on ( s.ID=f2.SessionID AND f2.Test_name='ados2_module2' AND f2.CommentID NOT LIKE 'DDE%' ) join flag f3 on ( s.ID=f3.SessionID AND f3.Test_name='ados2_module3' AND f3.CommentID NOT LIKE 'DDE%' ) WHERE s.CenterID IN (2,3,4,5) AND c.Active='Y' AND c.CenterID = $this->site", array());
        $fields = array('All', 'Partial');

        foreach($data as $row) {
            if(!empty($row['A1']) || !empty($row['A2']) || !empty($row['A3'])) {
                if(in_array($row['A1'] , $fields) && (in_array($row['A2'], $fields) || in_array($row['A3'], $fields))) {
                    print implode("\t", $row);
                    print "\n";
                }
            }
        }
        print"\n\n FOR MRI PARAMETER FORM HAVE Date_take = Date of MRI = Date of 25dir DTI = Date of Spectroscopy = Date of 65 dir DTI = Date of BOLD \n";
        print"--------------------------------------\n";
        $data = $DB->pselect("SELECT c.PSCID,c.CandID, s.Visit_label,Date_taken, DATEDIFF(T1_Scan_done_date, DTI_Scan_done_date) AS d1,  DATEDIFF(T1_Scan_done_date,DTI65Dir_Scan_done_date) AS d2,  DATEDIFF(T1_Scan_done_date,BOLD_Scan_done_date) AS d3,  DATEDIFF(T1_Scan_done_date,Spectroscopy_Scan_done_date) AS d4 from mri_parameter_form m join flag f on f.CommentID = m.CommentID join session s on s.ID = f.SessionID join candidate c on c.CandID = s.CandID WHERE f.CommentID NOT LIKE 'DDE%' AND f.CommentID NOT LIKE '%DCC%' AND Date_taken IS NOT NULL AND c.CenterID = $this->site", array());
        $fields = array ('T1_Scan_done_date', 'DTI_Scan_done_date', 'DTI65Dir_Scan_done_date', 'BOLD_Scan_done_date', 'Spectroscopy_Scan_done_date');
        foreach ($data as $row) {
            foreach($fields as $field) {
                if(!empty($row[$field])  && $row[$field] == $row['Date_taken']) {
                    if(abs($row['d1']) > 2 || abs($row['d2']) > 2 || abs($row['d3']) >2 || abs($row['d1']) >2) {
                        print implode("\t", $row);
                        print "\n";
                        break;
                    }
                }
            }
        }
        $tests = $DB->pselect("SELECT Test_name,Full_name FROM test_names WHERE Test_name NOT LIKE 'csbs_sponteneity' AND Test_name NOT LIKE '' AND Test_name NOT LIKE 'vineland_%'", array()) ;
        /* ************************************************************************* */
        // Determine instruments where Data_entry = Complete and DDE =N
        /* ************************************************************************* */

        print "\n\n INSTRUMENTS where Data_entry = Complete and DDE =N \n";
        print "--------------------------------------\n";
        foreach($tests as $test) {
            $instrument = $test['Test_name'];
            $data = $DB->pselect("SELECT c.PSCID,c.CandID, s.Visit_label, i.CommentID from $instrument i JOIN flag f ON (f.CommentID=i.CommentID) JOIN session s ON (s.ID=f.SessionID) JOIN candidate c ON (c.CandID=s.CandID) WHERE COALESCE(s.Current_stage, '') <> 'Recycling Bin' AND COALESCE(s.Visit, '') NOT IN ('Failure', 'Withdrawal') AND COALESCE(s.Screening, '') NOT IN ('Failure', 'Withdrawal') AND f.Administration='All' AND f.Data_entry='Complete' AND EXISTS (SELECT 'x' FROM flag df WHERE df.CommentID=CONCAT('DDE_', i.CommentID) AND df.Data_entry !='Complete') AND c.CenterID = $this->site", array());
            if(sizeof($data) > 1 ) {
                print "\n INSTRUMENT - ".$test['Full_name']."\n";
            }
            foreach($data as $row) {
                print implode("\t", $row);
                print "\n";
            }
        }
        /* ************************************************************************* */
        // Determine instruments where Data_entry = Complete and Conflicts exist =Y
        /* ************************************************************************* */

        print "\n\n INSTRUMENTS where Data_entry = Complete and Conflicts =Y \n";
        print "--------------------------------------\n";
        foreach($tests as $test) {
            $instrument = $test['Test_name'];
            $data = $DB->pselect("SELECT c.PSCID,c.CandID, s.Visit_label, i.CommentID from $instrument i JOIN flag f ON (f.CommentID=i.CommentID) JOIN session s ON (s.ID=f.SessionID) JOIN candidate c ON (c.CandID=s.CandID) WHERE COALESCE(s.Current_stage, '') <> 'Recycling Bin' AND COALESCE(s.Visit, '') NOT IN ('Failure', 'Withdrawal') AND COALESCE(s.Screening, '') NOT IN ('Failure', 'Withdrawal') AND f.Administration='All' AND f.Data_entry='Complete' AND EXISTS (SELECT 'x' FROM flag df WHERE df.CommentID=CONCAT('DDE_', i.CommentID) AND df.Data_entry='Complete') AND EXISTS (SELECT 'x' FROM conflicts_unresolved cu WHERE cu.CommentId1=i.CommentID OR cu.CommentId2=i.CommentID) AND c.CenterID = $this->site", array());
            if(sizeof($data) > 1 ) {
                print "\n INSTRUMENT - ".$test['Full_name']."\n";
            }
            foreach($data as $row) {
                print implode("\t", $row);
                print "\n";
            }
        }
        /* ************************************************************************* */
        // CHECK IF FIGS date = 0002-02-02
        /* ************************************************************************* */

        print "\n\n CHECK IF FIGS date = 0002-02-02 \n";
        print "--------------------------------------\n";
        $data = $DB->pselect("SELECT c.PSCID,c.CandID, s.Visit_label, i.CommentID from figs_year3 i JOIN flag f ON (f.CommentID=i.CommentID) JOIN session s ON (s.ID=f.SessionID) JOIN candidate c ON (c.CandID=s.CandID) WHERE COALESCE(s.Current_stage, '') <> 'Recycling Bin' AND COALESCE(s.Visit, '') NOT IN ('Failure', 'Withdrawal') AND COALESCE(s.Screening, '') NOT IN ('Failure', 'Withdrawal') AND f.Administration='All' AND f.Data_entry='Complete' AND i.Date_taken= '0002-02-02' AND c.CenterID = $this->site", array());
        foreach($data as $row) {
            print implode("\t", $row);
            print "\n";
        }
        /* ************************************************************************* */
        // CHECK IF Mullen date of administration - MRI PF date of administration >30
        /* ************************************************************************* */

        print "\n\n CHECK IF Mullen date of administration - MRI PF date of administration >30 \n";
        print "--------------------------------------\n";
        $data = $DB->pselect("SELECT c.PSCID,c.CandID,s.Visit_label, ROUND(DATEDIFF(m.Date_taken, mr.Date_taken) / (365/12)*30) AS datediff from candidate c JOIN session s on s.CandID=c.CandID  join flag f1 on ( s.ID=f1.SessionID AND f1.CommentID NOT LIKE 'DDE%' ) join mullen m ON (m.CommentID=f1.CommentID) join flag f2 on ( s.ID=f2.SessionID AND f2.CommentID NOT LIKE 'DDE%' ) JOIN mri_parameter_form mr ON (mr.CommentID=f2.CommentID) WHERE s.CenterID IN (3,3,4,5) AND c.Active='Y' AND c.CenterID = $this->site", array());
        $header = array('PSCID', 'DCCID', 'Visit_label', 'Date difference');
        foreach($header as $row) {
            print $row."\t";
        }
        print "\n";
        foreach($data as $row) {
            if(abs($row['datediff']) > 30) {
                $row['datediff'] = "\t".abs($row['datediff']);
                print implode("\t", $row);
                print "\n";
            }
        }
        /* ************************************************************************* */
        // CHECK IF DOB proband in Vineland, ADI R Proband and DOB_proband in candidate are same
        /* ************************************************************************* */

        print "\n\n CHECK IF DOB proband in Vineland, ADI R Proband and DOB_proband in candidate are same\n";
        print "--------------------------------------\n";
        $data = $DB->pselect("SELECT c.PSCID,c.CandID, c.ProbandDoB, a.DoB_proband,v.BIRTH_DATE from candidate c JOIN session s on s.CandID=c.CandID  join flag f1 on ( s.ID=f1.SessionID AND f1.CommentID NOT LIKE 'DDE%' ) join  adi_r_proband a ON (a.CommentID=f1.CommentID) join flag f2 on ( s.ID=f2.SessionID AND f2.CommentID NOT LIKE 'DDE%' ) JOIN vineland_proband v ON (v.CommentID=f2.CommentID) WHERE s.CenterID IN (3,3,4,5) AND c.Active='Y' AND c.CenterID = $this->site", array());
        $header = array('PSCID', 'DCCID', 'ProbandDoB', 'ADI-R ProbandDoB','Vineland ProbandDob');
        foreach($header as $row) {
            print $row."\t";
        }
        foreach($data as $row) {
            if(!empty($row['ProbandDoB']) || $row['ProbandDoB'] != '0000-00-00' ) {
                if( !empty( $row['DoB_proband']) && $row['ProbandDoB'] != $row['DoB_proband']) {
                    $row['BIRTH_DATE'] = "\t".$row['BIRTH_DATE'];
                    print implode("\t", $row);
                    print "\n";
                    break;

                } else if(!empty($row['BIRTH_DATE']) && $row['BIRTH_DATE'] != $row['ProbandDoB']) {
                    $row['BIRTH_DATE'] = "\t".$row['BIRTH_DATE'];
                    print implode("\t", $row);
                    print "\n";
                    break;


                }

            }
        }
        /* ************************************************************************* */
        // CHECK IF proband gender in Vineland, proband gender in candidate are same
        /* ************************************************************************* */

        print "\n\n CHECK IF proband gender in Vineland and proband gender in candidate are same\n";
        print "--------------------------------------\n";
        $data = $DB->pselect("SELECT c.PSCID,c.CandID, c.ProbandGender,v.SEX from candidate c JOIN session s on s.CandID=c.CandID join flag f2 on ( s.ID=f2.SessionID AND f2.CommentID NOT LIKE 'DDE%' ) JOIN vineland_proband v ON (v.CommentID=f2.CommentID) WHERE s.CenterID IN (3,3,4,5) AND c.Active='Y' AND c.CenterID = $this->site", array());
        $header = array('PSCID', 'DCCID', 'ProbandGender', 'Vineland_ProbandGender');
        foreach($header as $row) {
            print $row."\t";
        }
        foreach($data as $row) {
            if(!empty($row['ProbandGender']) ) {
                $gender = substr($row['ProbandGender'], 0, 1);
                if( !empty( $row['SEX'])  && (strcasecmp($row['SEX'],$gender) != 0)) {
                    $row['SEX'] = "\t".$row['SEX'];
                    print implode("\t", $row);
                    print "\n";
                }
            }
        }
        /* ************************************************************************* */
        // CHECK IF DOB candidate < DOB proband
        /* ************************************************************************* */

        print "\n\n CHECK IF DOB candidate < DOB proband\n";
        print "--------------------------------------\n";
        $data = $DB->pselect("SELECT c.PSCID,c.CandID, c.DoB,c.ProbandDoB,ROUND(DATEDIFF(c.DOB, c.ProbandDoB) / (365/12)) AS datediff from candidate c JOIN session s on s.CandID=c.CandID join flag f2 on ( s.ID=f2.SessionID AND f2.CommentID NOT LIKE 'DDE%' ) WHERE s.CenterID IN (3,3,4,5) AND c.Active='Y' AND c.CenterID = $this->site", array());
        $header = array('PSCID', 'DCCID', 'CandidateDoB', 'ProbandDoB', 'Age_Diff');
        if(sizeof($data) > 0 ){
            foreach($header as $row) {
                print $row."\t";
            }
        }
        foreach($data as $row) {
            if($row['datediff'] < 0) {
                print implode("\t", $row);
                print "\n";
            }

        }
        /* ************************************************************************* */
        // CHECK _score and _score_override are equal for q1,q2,q3,q6 for AOSI
        /* ************************************************************************* */

        print "\n\n CHECK _score and _score_override are equal for q1,q2,q3,q6 for AOSI\n";
        print "--------------------------------------\n";
        $fields = array('q1_visual_tracking','q2_disengagement_of_attention','q3_orients_to_name',
                'q6_imitation_of_actions');
        $data = $DB->pselect("SELECT c.PSCID,c.CandID,s.Visit_label,a.CommentID, a.q1_visual_tracking_score,a.q1_visual_tracking_score_override,a.q2_disengagement_of_attention_score,a.q2_disengagement_of_attention_score_override,a.q3_orients_to_name_score,a.q3_orients_to_name_score_override,a.q6_imitation_of_actions_score,a.q6_imitation_of_actions_score_override from candidate c JOIN session s on s.CandID=c.CandID join flag f2 on ( s.ID=f2.SessionID AND f2.CommentID NOT LIKE 'DDE%') JOIN aosi a ON (a.CommentID=f2.CommentID) WHERE s.CenterID IN (3,3,4,5) AND c.Active='Y' AND a.Data_entry_completion_status='Complete' AND s.CenterID = $this->site", array());
        $header = array('PSCID', 'DCCID', 'Visit_label', 'CommentID','q1_visual_tracking_score','q1_visual_tracking_score_override',
                'q2_disengagement_of_attention_score','q2_disengagement_of_attention_score_override','q3_orients_to_name_score',
                'q3_orients_to_name_score_override','q6_imitation_of_actions_score','q6_imitation_of_actions_score_override');
        if(sizeof($data) > 0 ){
            foreach($header as $row) {
                print $row."\t";
            }
            print "\n";
        }
        foreach($data as $row) {
            foreach($fields as $field) {
                $score = substr($row[$field."_score"], 0, 1);
                if($row[$field."_score_override"] != 8 && $score != 'U'
                        && $row[$field."_score_override"] != $row[$field."_score"]) {
                    print implode("\t", $row);
                    print "\n";
                    break;
                }
            }
        }
        /* ************************************************************************* */
        // CHECK consent status and consent withdrawal status
        /* ************************************************************************* */

        print "\n\n CHECK consent status and consent withdrawal status \n";
        print "--------------------------------------\n";
        $data = $DB->pselect("SELECT c.PSCID,c.CandID,ps.study_consent,ps.study_consent_withdrawal, ps.ndar_consent,ps.ndar_consent_withdrawal from candidate c JOIN participant_status ps ON (ps.CandID = c.CandID) WHERE c.Active='Y' AND c.PSCID NOT LIKE 'DCC%' AND c.CenterID = $this->site", array());
        $header = array('PSCID', 'DCCID', 'Studyconsent','Study withdrawal','NDARconsent','NDAR withdrawal');
        if(sizeof($data) > 0 ){
            foreach($header as $row) {
                print $row."\t";
            }
            print "\n";
        }
        foreach($data as $row) {
            if($row['study_consent'] == 'yes' && ($row['study_consent_withdrawal']!= '0000-00-00')
                    || $row['ndar_consent'] == 'yes' && ($row['ndar_consent_withdrawal']!= '0000-00-00')) {
                print implode("\t", $row);
                print "\n";
            }
        } 
        /* ************************************************************************* */
        // CHECK Candidate DOB is same at scan time and date taken in MRI Parameter Form is same as scan date
        /* ************************************************************************* */

        print "\n\n CHECK Candidate DOB is same at scan time and date taken in MRI Parameter Form is same as scan date \n";
        print "--------------------------------------\n";
        $data = $DB->pselect("SELECT File,session.ID, flag.CommentID, dob.Value as PatientDOB, candidate.DoB, study_date.Value as StudyDate, m.Date_taken as MRI_PF_Date_taken from files LEFT JOIN parameter_file dob USING (FileID) LEFT JOIN parameter_file study_date USING (FileID) LEFT JOIN session ON session.ID = files.SessionID JOIN candidate ON candidate.CandID = session.CandID JOIN flag ON flag.SessionID = session.ID JOIN mri_parameter_form m ON m.CommentID = flag.CommentID  WHERE study_date.ParameterTypeID=275 AND dob.ParameterTypeID=161 AND flag.CommentID NOT LIKE 'DDE_%' AND candidate.CenterID = $this->site", array());  
 $header = array('File', 'SessionID', 'CommentID','PatientDoB(YYYYMMDD)','Candidate DoB(YYYYMMDD)','StudyDate','MRI_PF_Date_taken','Issue');
 if(sizeof($data) > 0 ){
	 foreach($header as $row) {
		 print $row."\t";
	 }
	 print "\n";
 }
 $session = '';
 foreach($data as $row) {

	 $row['MRI_PF_Date_taken']  = preg_replace('/-/', '', $row['MRI_PF_Date_taken']);
	 $row['DoB']  = preg_replace('/-/', '', $row['DoB']);
	 if($row['ID'] != $session) {
		 if($row['MRI_PF_Date_taken'] != $row['StudyDate'] || $row['PatientDOB'] != $row['DoB']) {
                     if($row['MRI_PF_Date_taken'] != $row['StudyDate']) {
                          $row['Issue'] = 'Scan date mismatch';
                      } else {
                          $row['Issue'] = 'DoB mismatch';
                      }
			 print_r($row);
			 print "\n";
		 }
		 $session = $row['ID'];
	 }
   }
       /* ************************************************************************* */
        // CHECK multiple selected T1 files
        /* ************************************************************************* */

        print "\n\n CHECK multiple selected T1 files \n";
        print "--------------------------------------\n";
        $data = $DB->pselect("SELECT CandID, Visit_label, count(f.FileID), Value "
            . "FROM files f JOIN parameter_file pf ON (pf.FileID=f.FileID) "
            . "JOIN session s ON (s.ID=f.SessionID) WHERE pf.ParameterTypeID=1 "
            . "AND pf.Value='t1w' AND File not like '%lego%' "
            . "AND File not like '%phantom%' AND CenterID=:CID "
            . "GROUP BY SessionID HAVING count(f.FileID)>1 "
            . "ORDER BY count(f.FileID)", array("CID" => $this->site));
        $header = array('CandID', 'Visit_label', 'Num_Files', 'Value');
        if(sizeof($data) > 0 ){
            foreach($header as $row) {
                print $row."\t";
            }
            print "\n";
        }
        foreach($data as $row) {
            print implode("\t", $row);
            print "\n";
        }
        /* ************************************************************************* */
        // CHECK multiple selected T2 files
        /* ************************************************************************* */

        print "\n\n CHECK multiple selected T2 files \n";
        print "--------------------------------------\n";
        $data = $DB->pselect("SELECT CandID, Visit_label, count(f.FileID), Value FROM files f JOIN parameter_file pf ON (pf.FileID=f.FileID) JOIN session s ON (s.ID=f.SessionID) WHERE pf.ParameterTypeID=1 AND pf.Value='t2w' AND File not like '%lego%' AND File not like '%phantom%' AND CenterID=$this->site GROUP BY SessionID HAVING count(f.FileID)>1 ORDER BY count(f.FileID)");
        $header = array('CandID', 'Visit_label', 'Num_Files', 'Value');
        if(sizeof($data) > 0 ){
            foreach($header as $row) {
                print $row."\t";
            }
            print "\n";
        }
        foreach($data as $row) {
            print implode("\t", $row);
            print "\n";
        }


  }
}
?>
