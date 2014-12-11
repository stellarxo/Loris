<?php
/**
 * This script queries the database for t1, t2, dti, 65 dir dti, bold
 * and bold b1000 scans accquired for each candidate at visit level.
 * For each of the dti25 and bold scans accquired we report number of
 * frames. Creates one csv file per visit per project
 *
 *  PHP Version 5
 *
 * @category Main
 * @package  Loris
 * @author   Rathi Sekaran <sekaranrathi@gmail.com>
 * @license  Loris license
 * @link     https://www.github.com/aces/Loris-Trunk/
 */
set_include_path(get_include_path().":../libraries:../../php/libraries:");
require_once "NDB_Client.class.inc";
require_once "Utility.class.inc";
require_once "Database.class.inc";
//require_once "../../tools/generic_includes.php";
$client = new NDB_Client();
$client->makeCommandLine();
$client->initialize('../config.xml');


$db = Database::singleton();
if (Utility::isErrorX($db)) {
    print "Could not connect to database: " . $db->getMessage();
    exit(1);
}
$visit   = array('V03', 'V06', 'V09','V12', 'V24', 'V36');
$project = array(1=>'IBIS1',2=>'IBIS2',3=>'FRX',4=>'EARLI');
//$visit = array('V06'); $project = array(1=>'IBIS1');
foreach ($project as $key=>$val) {
    foreach ($visit as $visit_label) {
        $query = "SELECT c.CandID,c.PSCID, s.ID, c.Gender, CASE s.SubprojectID WHEN 1
            THEN '6 mo recruit' WHEN 2 THEN '12mo recruit'
            WHEN 3 THEN 'Control'
            WHEN 4 THEN 'FRX 6mo' WHEN 5 THEN 'FRX 12mo'
            WHEN 6 THEN 'EARLI sib'
            WHEN 9 THEN 'High Risk' WHEN 10 THEN 'Low Risk'
            END as Cohort
            FROM session s
            JOIN candidate c ON c.CandID = s.CandID
            LEFT JOIN participant_status p ON p.CandID=c.CandID
            WHERE s.Visit_label NOT LIKE 'living%'
            AND s.Visit_label NOT LIKE 'LEGO%'
            AND s.Active <>'N' AND c.ProjectID=$key
            AND s.Visit_label='$visit_label'
            AND c.CenterID<>1 AND p.study_consent='yes'
            AND p.study_consent_withdrawal IS NULL
            ORDER BY s.Visit_label, c.ProjectID";

        $record   = array();//print $query;
        $record   = $db->pselect($query, array());
        $filename = "scan_".$val."_".$visit_label.".csv";
        $fd       = fopen($filename, 'w+');
        if ($fd === false) {
            exit(-1);
        }
        $header = array('CandID','PSCID','Gender','Subproject',
                'DSMIV_checklist','DSMIV_checklist_PDD',
                'DSMV_checklist_asd', 'DSMV_checklist_scd','ADOS_DERIVED',
                'Selected_T1','T1_QCStatus','T1_Filename',
                'Selected_T2', 'T2_QCStatus', 'T2_Filename',
                'DTI25','Num_Frame_DTI25','DTI25_Filename',
                'DTI65','DTI65_Filename','DTI65_B1000',
                'DTI65_B1000_Filename','Bold','Num_Runs_Bold',
                'Num_Runs_Bold_MRIPF', 'Bold_frames1','Bold_Filename1',
                'Bold_frames2','Bold_Filename2','Bold_frames3','Bold_Filename3',
                'Bold_frames4','Bold_Filename4','Bold_frames5','Bold_Filename5');
        fputcsv($fd, $header);
        $num_dti = 0;$num_dti65 = 0;$num_dti65_b1000 = 0;$num_bold = 0;
        foreach ($record as $row) {
            $num_runs = 0;

            $candidate = array('CandID'=>$row['CandID'],'PSCID'=>$row['PSCID'],
                    'Gender'=>$row['Gender'],'Subproject'=>$row['Cohort'],
                    'DSMIV_checklist'=>'','DSMIV_checklist_PDD'=>'',
                    'DSMV_checklist_asd'=>'', 'DSMV_checklist_scd'=>'','ADOS_DERIVED'=>'',
                    'Selected_T1'=>'no','T1_QCStatus'=>'','T1_Filename'=>'',
                    'Selected_T2'=>'no','T2_QCStatus'=>'','T2_Filename'=>'',
                    'DTI25'=>'no','Num_Frame_DTI25'=>0,'DTI25_Filename'=>'',
                    'DTI65'=>'no','DTI65_Filename'=>'' ,'DTI65_B1000'=>'no',
                    'DTI65_B1000_Filename'=>'', 'Bold'=>'no','Num_Runs_Bold'=>'',
                    'Num_Runs_Bold_MRIPF'=>'','Bold_frames1'=>0,'Bold_Filename1'=>'',
                    'Bold_frames2'=>0,'Bold_Filename2'=>'','Bold_frames3'=>0,
                    'Bold_Filename3'=>'','Bold_frames4'=>0,'Bold_Filename4'=>'',
                    'Bold_frames5'=>0,'Bold_Filename5'=>'');

            $id = $row['ID']; //this is the session ID
            if ($visit_label == 'V24') {
                                $query_asd  = "SELECT d4. q4_criteria_autistic_disorder, d4. q4_criteria_PDD, 
                                      d5. meet_dsm_asd, d5. meet_dsm_scd
                               FROM session s 
                               LEFT JOIN flag d5flag ON (s.ID = d5flag.SessionID 
                                    AND d5flag.Test_name='DSMV_checklist') 
                               LEFT JOIN flag d4flag ON (s.ID = d4flag.SessionID 
                                    AND d4flag.Test_name='DSMIV_checklist') 
                               LEFT JOIN DSMIV_checklist d4 ON (d4.CommentID = d4flag.CommentID)
                               LEFT JOIN DSMV_checklist d5 ON (d5.CommentID = d5flag.CommentID)
                               WHERE d5flag.CommentID NOT LIKE 'DDE%' 
                                     AND d4flag.CommentID NOT LIKE 'DDE%'
                                     AND s.ID=$id";
                $result_asd = $db->pselect($query_asd, array()); 
                foreach ($result_asd as $asd) {
                    $candidate['DSMIV_checklist']     = $asd['q4_criteria_autistic_disorder'];
                    $candidate['DSMIV_checklist_PDD'] = $asd['q4_criteria_PDD'];
                    $candidate['DSMV_checklist_asd']  = $asd['meet_dsm_asd'];
                    $candidate['DSMV_checklist_scd']  = $asd['meet_dsm_scd'];
                }
                $ADOSModule = getADOSModule($id); //print $ADOSModule."\n";
                if (!empty($ADOSModule)) {
                    $derived_ados = "SELECT a.ADOS_classification FROM session s
                                     LEFT JOIN flag aflag ON (s.ID = aflag.SessionID 
                                          AND aflag.Test_name= $ADOSModule)
                                     LEFT JOIN $ADOSModule a ON (a.CommentID = aflag.CommentID)
                                     WHERE aflag.CommentID NOT LIKE 'DDE%'
                                           AND s.ID=$id";
                    $value_derives = $db->pselectOne($derived_ados, array());
                    if (!empty($value_derived)) {
                        $candidate['ADOS_DERIVED'] = $value_derived; 
                    }
                }

            }
            $scan_types = array('T1'=>'t1w', 'T2'=>'t2w');
            foreach ($scan_types as $sc_key=>$sc_val) {
               $query_t12 = "SELECT DISTINCT m.Scan_type, q.QCStatus, f.File
                FROM files f
                JOIN mri_scan_type m on m.ID = f. AcquisitionProtocolID
                JOIN parameter_file p ON p.FileID=f.FileID
                JOIN files_qcstatus q ON q.FileID=f.FileID
                WHERE m.Scan_type='$sc_val' AND p.ParameterTypeID=1
                      AND p.Value <>'' AND f.SessionID=$id";
                $result    = $db->pselectRow($query_t12, array());
               // print "SESSION - $id";print_r($result);print"\n";
                if (isset($result['Scan_type']) ) {
                    $candidate['Selected_'.$sc_key] = 'yes';
                    $candidate[$sc_key.'_QCStatus'] = $result['QCStatus'];
                    $candidate[$sc_key.'_Filename'] = $result['File']; //print_r($candidate);
                }
            }
            $scan_info  = "SELECT DISTINCT m.Scan_type, p.Value as 'Num_Frames',
                                 f.File FROM files f
                          JOIN mri_scan_type m on m.ID = f. AcquisitionProtocolID
                          JOIN parameter_file p ON p.FileID=f.FileID
                          WHERE m.Scan_type IN('DTI65', 'dti','DTI65_B1000','ep2d_bold')
                                AND f.SessionID=$id AND parameterTypeID=353";
            $scan_types = $db->pselect($scan_info, array());
            // if(!empty($scan_types)) {
            foreach ($scan_types as $scan_type) {
                if ('dti' == $scan_type['Scan_type']) {
                    $candidate['DTI25'] = 'yes';
                    $num_dti++;
                    if ($scan_type['Num_Frames'] > $candidate['Num_Frame_DTI25']) {
                        $candidate['Num_Frame_DTI25'] = $scan_type['Num_Frames'];
                    }
                    $candidate['DTI25_Filename'] = $scan_type['File'];
                }
                if ('DTI65' == $scan_type['Scan_type']) {
                    $candidate['DTI65'] = 'yes';
                    $num_dti65++;
                    $candidate['DTI65_Filename'] = $scan_type['File'];
                }
                if ('DTI65_B1000' == $scan_type['Scan_type']) {
                    $candidate['DTI65_B1000'] = 'yes';
                    $num_dti65_b1000++;
                    $candidate['DTI65_B1000_Filename'] = $scan_type['File'];
                }
                if ('ep2d_bold' == $scan_type['Scan_type']) {
                    $candidate['Bold'] = 'yes';
                    $num_bold++; $num_runs++;
                    $candidate['Bold_frames'.$num_runs]   = $scan_type['Num_Frames'];
                    $candidate['Bold_Filename'.$num_runs] = $scan_type['File'];
                }
            }
            $no_bold = $db->pselectOne("SELECT m.BOLD_Number_Complete_Runs
                    FROM mri_parameter_form m
                    JOIN flag f ON f.CommentID = m.CommentID
                    JOIN session s ON s.ID = f.SessionID
                    AND f.SessionID=$id AND f.CommentID NOT LIKE 'DDE_%'", array());
            if (!empty ($no_bold)) {
                $candidate['Num_Runs_Bold_MRIPF'] = $no_bold;
            }
            fputcsv($fd, $candidate);
            //}
        }
        $candidate_tot = array('CandID'=>'Total','PSCID'=>'',
                'DTI65'=>$num_dti65,'DTI25'=>$num_dti,
                'DTI65_B1000'=>$num_dti65_b1000,
                'Bold'=>$num_bold,'Num_Frames_Bold'=>'');
        //               fputcsv($fd,$candidate_tot);
    }
}

/**
 * Gets the ADOS module that was Administered at a particular
 * SessionID
 *
 * @param int $SessionID The Session
 *
 * @return string Test_name of ADOS module. null if not found
 */
function getADOSModule($SessionID)
{   
	$db = Database::singleton();
	if (Utility::isErrorX($db)) {
		print "Could not connect to database: " . $db->getMessage();
		exit(1);
	}
	$rows = $db->pselect(
			"SELECT Test_name, Administration FROM flag " .
			"WHERE SessionID=:SID AND Test_name LIKE 'ados%'" .
			" AND CommentID NOT LIKE 'DDE%'",
			array('SID' => $SessionID)
			);
	foreach ($rows as $row) {
		if ($row['Administration'] === 'All') {
			return $row['Test_name'];
		}
	}
	return null;
}

?>
