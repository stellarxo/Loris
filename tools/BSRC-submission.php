<?php
set_include_path(get_include_path().":../libraries:../../php/libraries:");

require_once '../../vendor/autoload.php';
require_once "NDB_Client.class.inc";
require_once "Utility.class.inc";
require_once "Candidate.class.inc";

if (empty($argv[1])) {
    print "Usage: php BSRC-submission.php Dec2015\n";
} else {

    /** Create a new PHPExcel Object **/
    $ExcelApplication = new PHPExcel();
    $ExcelApplication->removeSheetByIndex(0);
    
    $client = new NDB_Client();
    $client->makeCommandLine();
    $client->initialize('../config.xml');
            
    $DB = Database::singleton();
    //$DB->_showQueries = true;
   
    function getNameFromNumber($num) 
    {
        $numeric = $num % 26;
        $letter = chr(65 + $numeric);
        $num2 = intval($num / 26);
        if ($num2 > 0) {
            return getNameFromNumber($num2 - 1) . $letter;
        } else {
            return $letter;
        }
    }

    function addSheet($query, $name) 
    {
        global $DB, $ExcelApplication;
        
        print "adding tab " . $name . "\n";
        $DB->select($query, $result);

        $ExcelWorkSheet = new PHPExcel_Worksheet($ExcelApplication, $name);
        $ExcelApplication->addSheet($ExcelWorkSheet, -1);
  
        $ExcelWorkSheet->fromArray(array_keys($result[0]),' ','A1');
        $ExcelWorkSheet->fromArray($result,' ','A2');

        $numCol = count($result[0]) - 1;
        $header = 'a1:' . getNameFromNumber($numCol) . '1';
        $ExcelWorkSheet->getStyle($header)->getFill()->setFillType(\PHPExcel_Style_Fill::FILL_SOLID)->getStartColor()->setARGB('00e0ffff');
        $style = array(
            'font' => array('bold' => true,),
            'alignment' => array('horizontal' => \PHPExcel_Style_Alignment::HORIZONTAL_CENTER,),
        );
        $ExcelWorkSheet->getStyle($header)->applyFromArray($style);

        for ($col = 0; $col <= $numCol; $col++)
        {
            $ExcelWorkSheet->getColumnDimension(getNameFromNumber($col))->setAutoSize(true);
        }
    }
     
    //    s.SubprojectID, 
    //    s.Current_stage, 
    //    s.Visit, 
    $name  = "Mullen";
    $query = "SELECT
        c.IBISId AS id_number, 
        m.Date_taken AS date_of_testing,
        ROUND(m.Candidate_Age) AS age_at_testing,
        null AS adjusted_age,
        null AS version,
        m.gross_motor_raw,
        m.visual_reception_raw,
        m.fine_motor_raw,
        m.receptive_language_raw AS receptive_lang_raw,
        m.expressive_language_raw AS expressive_lang_raw,
        m.gross_motor_age_equivalent AS gross_motor_ae,
        m.visual_reception_age_equivalent AS visual_reception_ae,
        m.fine_motor_age_equivalent AS fine_motor_ae,
        m.receptive_language_age_equivalent AS receptive_lang_ae,
        m.expressive_language_age_equivalent AS expressive_lang_ae,
        m.gross_motor_t AS gross_motor_t_score,
        m.visual_reception_t AS visual_reception_t_score,
        null AS fine_motor_t_score,
        m.receptive_language_t AS receptive_lang_t_score,
        m.expressive_language_t AS expressive_lang_t_score,
        m.composite_standard_score AS early_learning_composite,
        null AS other_verbal_iq,
        null AS other_nonverbal_iq,
        null AS other_iq
        FROM flag f JOIN session s ON (f.SessionID=s.ID) 
        JOIN candidate c ON (s.CandID=c.CandID)
        JOIN mullen m ON (m.CommentID=f.CommentID) 
        JOIN participant_status ps ON (ps.CandID=c.CandID)
        LEFT JOIN conflicts_unresolved cu ON (cu.CommentId2=f.CommentID)
        WHERE ps.study_consent='yes' AND s.CenterID!=1 AND f.Data_entry='Complete' 
        AND f.CommentID NOT LIKE 'DDE_%' AND cu.CommentID2 is null 
        AND s.Current_stage<>'Recycling Bin' AND m.Date_taken is not null 
        AND (s.SubprojectID=1 OR s.SubprojectID=2 OR s.SubprojectID=3);";    
    //addSheet($query, $name);
    
    // s.SubprojectID, s.Current_stage, s.Visit, 
    $name = "Vineland";
    $query = "SELECT
        c.IBISId AS id_number, 
        v.Date_taken AS date_of_testing,
        ROUND(v.Candidate_Age) AS age_at_testing,
        null AS version,
        v.FORM AS test_form,
        v.RELATIONSHIP AS respondent,
        v.REC_RAW AS receptive_lang_raw,
        v.EXP_RAW AS expressive_lang_raw,
        v.WRN_RAW AS written_raw,
        v.PER_RAW AS personal_raw,
        v.DOM_RAW AS domestic_raw,
        v.CMM_RAW AS community_raw,
        v.IPR_RAW AS interpersonal_relationships_raw,
        v.PL_RAW AS play_and_leisure_raw,
        v.CS_RAW AS coping_raw,
        v.GMS_RAW AS gross_motor_raw,
        v.FMS_RAW AS fine_motor_raw,
        v.REC_VSCALE AS receptive_lang_v_scale_score,
        v.EXP_VSCALE AS expressive_lang_v_scale_score,
        v.WRN_VSCALE AS written_v_scale_score,
        v.PER_VSCALE AS personal_v_scale_score,
        v.DOM_VSCALE AS domestic_v_scale_score,
        v.CMM_VSCALE AS community_v_scale_score,
        v.IPR_VSCALE AS interpersonal_relationships_v_scale_score,
        v.PL_VSCALE AS play_and_leisure_v_scale_score,
        v.CS_VSCALE AS coping_v_scale_score,
        v.GMS_VSCALE AS gross_motor_v_scale_score,
        v.FMS_VSCALE AS fine_motor_v_scale_score,
        v.REC_AGE_EQUIV AS receptive_lang_age_eq,
        v.EXP_AGE_EQUIV AS expressive_lang_age_eq,
        v.WRN_AGE_EQUIV AS written_age_eq,
        v.PER_AGE_EQUIV AS personal_age_eq,
        v.DOM_AGE_EQUIV AS domestic_age_eq,
        v.CMM_AGE_EQUIV AS community_age_eq,
        v.IPR_AGE_EQUIV AS interpersonal_relationships_age_eq,
        v.PL_AGE_EQUIV AS play_and_leisure_age_eq,
        v.CS_AGE_EQUIV coping_age_eq,
        v.GMS_AGE_EQUIV AS gross_motor_age_eq,
        v.FMS_AGE_EQUIV AS fine_motor_age_eq,
        v.COM_SUM_VSCALES_FOR_DOMAIN AS communication_domain_ss,
        v.DLS_SUM_VSCALES_FOR_DOMAIN AS daily_living_skills_domain_ss,
        v.SOC_SUM_VSCALES_FOR_DOMAIN AS socialization_domain_ss,
        v.MS_SUM_VSCALES_FOR_DOMAIN AS motor_domain_ss,
        v.ABC_SUM_ALL_DOM_STD_SCORES AS adaptive_behavior_composite,
        null AS maladaptive_behavior_internalizing_raw,
        null AS maladaptive_behavior_externalizing_raw,
        null AS maladaptive_behavior_internalizing_v_scale_score,
        null AS maladapative_behavior_externalizing_v_scale_score
        FROM flag f JOIN session s ON (f.SessionID=s.ID) 
        JOIN candidate c ON (s.CandID=c.CandID)
        JOIN vineland_proband v ON (v.CommentID=f.CommentID) 
        JOIN participant_status ps ON (ps.CandID=c.CandID)
        LEFT JOIN conflicts_unresolved cu ON (cu.CommentId2=f.CommentID)
        WHERE ps.study_consent='yes' AND s.CenterID!=1 AND f.Data_entry='Complete' 
        AND f.CommentID NOT LIKE 'DDE_%' AND cu.CommentID2 is null 
        AND s.Current_stage<>'Recycling Bin' AND v.Date_taken is not null 
        AND (s.SubprojectID=1 OR s.SubprojectID=2 OR s.SubprojectID=3);";
    //addSheet($query, $name);
       
    //         s.SubprojectID, s.Current_stage, s.Visit,
    $name = "ADI";
    $query = "SELECT
        c.IBISId AS id_number, 
        a.Date_taken AS date_of_testing,
        ROUND(a.Candidate_Age) AS age_at_testing,
        null AS version,
        null AS algorithm,
        null AS adi_a1,
        null AS adi_a2,
        null AS adi_a3,
        null AS adi_a4,
        a.A_Total AS adi_a_total,
        null AS adi_b1,
        null AS adi_b2,
        null AS adi_b3,
        null AS adi_b4,
        a.BV_Total AS adi_bv_total,
        a.BNV_Total AS adi_bnv_total,
        null AS adi_c1,
        null AS adi_c2,
        null AS adi_c3,
        null AS adi_c4,
        a.C_Total AS adi_c_total,
        a.D_Total AS adi_d_total
        FROM flag f JOIN session s ON (f.SessionID=s.ID) 
        JOIN candidate c ON (s.CandID=c.CandID)
        JOIN adi_r_proband a ON (a.CommentID=f.CommentID) 
        JOIN participant_status ps ON (ps.CandID=c.CandID)
        LEFT JOIN conflicts_unresolved cu ON (cu.CommentId2=f.CommentID)
        WHERE ps.study_consent='yes' AND s.CenterID!=1 AND f.Data_entry='Complete' 
        AND f.CommentID NOT LIKE 'DDE_%' AND cu.CommentID2 is null 
        AND s.Current_stage<>'Recycling Bin' AND a.Date_taken is not null 
        AND (s.SubprojectID=1 OR s.SubprojectID=2 OR s.SubprojectID=3);";
    //addSheet($query, $name);
    
    //         s.SubprojectID, s.Current_stage, s.Visit,
    $name = "MacArthur Words & Gestures";
    $query = "SELECT
        c.IBISId AS id_number, 
        m.Date_taken AS date_of_testing,
        ROUND(m.Candidate_Age) AS age_at_testing,
        null AS version,
        null AS respondent,
        m.I_A_1 AS cdi_wg_a1,
        m.I_A_2 AS cdi_wg_a2,
        m.I_A_3 AS cdi_wg_a3,
        phrases_understood_number AS cdi_wg_b,
        null AS cdi_wg_b_pct,
        m.I_C_1 as cdi_wg_c1,
        m.I_C_2 as cdi_wg_c2,
        null AS cdi_wg_d1_understands,
        null AS cdi_wg_d1_understands_and_says,
        null AS cdi_wg_d2_understands,
        null AS cdi_wg_d2_understands_and_says,
        null AS cdi_wg_d3_understands,
        null AS cdi_wg_d3_understands_and_says,
        null AS cdi_wg_d4_understands,
        null AS cdi_wg_d4_understands_and_says,
        null AS cdi_wg_d5_understands,
        null AS cdi_wg_d5_understands_and_says,
        null AS cdi_wg_d6_understands,
        null AS cdi_wg_d6_understands_and_says,
        null AS cdi_wg_d7_understands,
        null AS cdi_wg_d7_understands_and_says,
        null AS cdi_wg_d8_understands,
        null AS cdi_wg_d8_understands_and_says,
        null AS cdi_wg_d9_understands,
        null AS cdi_wg_d9_understands_and_says,
        null AS cdi_wg_d10_understands,
        null AS cdi_wg_d10_understands_and_says,
        null AS cdi_wg_d11_understands,
        null AS cdi_wg_d11_understands_and_says,
        null AS cdi_wg_d12_understands,
        null AS cdi_wg_d12_understands_and_says,
        null AS cdi_wg_d13_understands,
        null AS cdi_wg_d13_understands_and_says,
        null AS cdi_wg_d14_understands,
        null AS cdi_wg_d14_understands_and_says,
        null AS cdi_wg_d15_understands,
        null AS cdi_wg_d15_understands_and_says,
        null AS cdi_wg_d16_understands,
        null AS cdi_wg_d16_understands_and_says,
        null AS cdi_wg_d17_understands,
        null AS cdi_wg_d17_understands_and_says,
        null AS cdi_wg_d18_understands,
        null AS cdi_wg_d18_understands_and_says,
        null AS cdi_wg_d19_understands,
        null AS cdi_wg_d19_understands_and_says,
        m.words_understood_number AS cdi_wg_d_understands_total,
        null AS cdi_wg_d_understands_percentile,
        null AS cdi_wg_d_understands_and_says_total,
        null AS cdi_wg_d_understands_and_says_percentile,
        null AS cdi_wg_part_ii_a,
        null AS cdi_wg_part_ii_b,
        m.early_gestures_number AS cdi_wg_early_gestures_total,
        null AS cdi_wg_early_gestures_percentile,
        null AS cdi_wg_part_ii_c,
        null AS cdi_wg_part_ii_d,
        null AS cdi_wg_part_ii_e, 
        m.later_gestures_number AS cdi_wg_later_gestures_total,
        null AS cdi_wg_later_gestrues_percentile,
        m.total_gestures_number AS cdi_wg_total_gestures,
        null AS cdi_wg_total_gestrues_percentile
        FROM flag f JOIN session s ON (f.SessionID=s.ID) 
        JOIN candidate c ON (s.CandID=c.CandID)
        JOIN macarthur_words_gestures m ON (m.CommentID=f.CommentID) 
        JOIN participant_status ps ON (ps.CandID=c.CandID)
        LEFT JOIN conflicts_unresolved cu ON (cu.CommentId2=f.CommentID)
        WHERE ps.study_consent='yes' AND s.CenterID!=1 AND f.Data_entry='Complete' 
        AND f.CommentID NOT LIKE 'DDE_%' AND cu.CommentID2 is null 
        AND s.Current_stage<>'Recycling Bin' AND m.Date_taken is not null 
        AND (s.SubprojectID=1 OR s.SubprojectID=2 OR s.SubprojectID=3);";
    //addSheet($query, $name);    
    
    //         s.SubprojectID, s.Current_stage, s.Visit,
    $name = "MacArthur Words & Sentences";
    $query = "SELECT
        c.IBISId AS id_number, 
        m.Date_taken AS date_of_testing,
        ROUND(m.Candidate_Age) AS age_at_testing,
        m.version as version,
        m.respondent as repondent,
        m.cdi_ws_a_total AS cdi_ws_a_total,
        m.cdi_ws_part_ii_b AS cdi_ws_part_ii_b,
        m.cdi_ws_part_ii_c AS cdi_ws_part_ii_c,
        m.cdi_ws_part_ii_e AS cdi_ws_part_ii_e
        FROM flag f JOIN session s ON (f.SessionID=s.ID) 
        JOIN candidate c ON (s.CandID=c.CandID)
        JOIN mullen m ON (m.CommentID=f.CommentID) 
        JOIN participant_status ps ON (ps.CandID=c.CandID)
        WHERE ps.study_consent='yes' AND s.CenterID!=1 
        AND (s.SubprojectID=1 OR s.SubprojectID=2 OR s.SubprojectID=3);";
    addSheet($query, $name);
    
    // Writing the excel file out
    $writer = PHPExcel_IOFactory::createWriter($ExcelApplication, 'Excel2007');
    $writer->save('BSRC-submission-' . $argv[1] . '.xlsx');
    
    print "-- were done.\n\n";
}