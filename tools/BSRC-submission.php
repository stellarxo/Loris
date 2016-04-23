<?php
/**
* Will create a BSRC submisson from mysql data into an excel workbook
* 
* PHP Version 5.5.9
* 
*  @category Main
*  @package  BSRC-submission
*  @author   Gregory Luneau <gregory.luneau@mcgill.ca>
*  @license  http://www.gnu.org/licenses/gpl-3.0.txt GPLv3
*  @version  GIT: <git_id>
*  @link     https://www.github.com/aces/IBIS/
**/
set_include_path(get_include_path().":../libraries:../../php/libraries:");

require_once '../../vendor/autoload.php';
require_once "NDB_Client.class.inc";
require_once "Utility.class.inc";
require_once "Candidate.class.inc";

/**
* Converst the column number into the excel column name in letters
* 
* @param int $num The column number
* 
* @return string $letter The excel column name in letters
* 
**/
function getNameFromNumber($num)
{
    $numeric = $num % 26;
    $letter  = chr(65 + $numeric);
    $num2    = intval($num / 26);
    if ($num2 > 0) {
        return getNameFromNumber($num2 - 1) . $letter;
    } else {
        return $letter;
    }
}

/**
* Add a sheet to the excel workbook with name specified
* 
* @param string $query The SQL query to run
* @param string $name  Name of the excel tab
*  
* @return null
* 
**/
function addSheet($query, $name)
{
    global $DB, $ExcelApplication;

    print "adding tab " . $name . "\n";
    $DB->select($query, $result);

    $ExcelWorkSheet = new PHPExcel_Worksheet($ExcelApplication, $name);
    $ExcelApplication->addSheet($ExcelWorkSheet, -1);

    // Add Column names
    $ExcelWorkSheet->fromArray(array_keys($result[0]), ' ', 'A1');
    // Add Data
    $ExcelWorkSheet->fromArray($result, ' ', 'A2');

    // Bold Cyan Column headers
    $numCol = count($result[0]) - 1;
    $header = 'a1:' . getNameFromNumber($numCol) . '1';
    $ExcelWorkSheet->getStyle($header)->getFill()->setFillType(
        \PHPExcel_Style_Fill::FILL_SOLID
    )->getStartColor()->setARGB('00e0ffff');

    $hor_cen = \PHPExcel_Style_Alignment::HORIZONTAL_CENTER;
    $style   = array(
                'font'      => array('bold' => true),
                'alignment' => array('horizontal' => $hor_cen),
               );
    $ExcelWorkSheet->getStyle($header)->applyFromArray($style);

    // Redimension columns to max size of data
    for ($col = 0; $col <= $numCol; $col++) {
        $ExcelWorkSheet->getColumnDimension(
            getNameFromNumber($col)
        )->setAutoSize(true);
    }
}

// Main
if (empty($argv[1])) {
    print "Usage: php BSRC-submission.php Dec2015\n";
} else {

    // Create a new PHPExcel Object
    $ExcelApplication = new PHPExcel();
    // Removing builtin sheet make it easier to use same function to add sheets later
    $ExcelApplication->removeSheetByIndex(0);

    $client = new NDB_Client();
    $client->makeCommandLine();
    $client->initialize('../config.xml');

    $DB = Database::singleton();

    $TQ = array(
           "Mullen"                      => "SELECT c.IBISId AS id_number,
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
                WHERE ps.study_consent='yes' AND s.CenterID!=1 
                AND f.Data_entry='Complete' AND s.Visit_label <='V24'
                AND f.CommentID NOT LIKE 'DDE_%' AND cu.CommentID2 is null 
                AND s.Current_stage<>'Recycling Bin' AND m.Date_taken is not null 
                AND (s.SubprojectID=1 OR s.SubprojectID=2 OR s.SubprojectID=3);",
           "Vineland"                    => "SELECT
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
                JOIN vineland_subject v ON (v.CommentID=f.CommentID) 
                JOIN participant_status ps ON (ps.CandID=c.CandID)
                LEFT JOIN conflicts_unresolved cu ON (cu.CommentId2=f.CommentID)
                WHERE ps.study_consent='yes' AND s.CenterID!=1 AND c.Active='Y' 
                AND (COALESCE(ps.study_consent_withdrawal,'0000-00-00')='0000-00-00')
                AND f.Data_entry='Complete' AND s.Visit_label <='V24'
                AND f.CommentID NOT LIKE 'DDE_%' AND cu.CommentID2 is null 
                AND s.Current_stage<>'Recycling Bin' AND v.Date_taken is not null 
                AND (s.SubprojectID=1 OR s.SubprojectID=2 OR s.SubprojectID=3)
                AND v.Candidate_Age >= 0;",
           "ADI"                         => "SELECT
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
                JOIN adi_r_subject a ON (a.CommentID=f.CommentID) 
                JOIN participant_status ps ON (ps.CandID=c.CandID)
                LEFT JOIN conflicts_unresolved cu ON (cu.CommentId2=f.CommentID)
                WHERE ps.study_consent='yes' AND s.CenterID!=1 AND c.Active='Y' 
                AND (COALESCE(ps.study_consent_withdrawal,'0000-00-00')='0000-00-00')
                AND f.Data_entry='Complete' AND s.Visit_label <='V24'
                AND f.CommentID NOT LIKE 'DDE_%' AND cu.CommentID2 is null 
                AND s.Current_stage<>'Recycling Bin' AND a.Date_taken is not null 
                AND (s.SubprojectID=1 OR s.SubprojectID=2 OR s.SubprojectID=3)
                AND a.Candidate_Age >= 0;",
           "MacArthur Words & Gestures"  => "SELECT
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
                WHERE ps.study_consent='yes' AND s.CenterID!=1 
                AND f.Data_entry='Complete' AND s.Visit_label <='V24'
                AND f.CommentID NOT LIKE 'DDE_%' AND cu.CommentID2 is null 
                AND s.Current_stage<>'Recycling Bin' AND m.Date_taken is not null 
                AND (s.SubprojectID=1 OR s.SubprojectID=2 OR s.SubprojectID=3);",
           "MacArthur Words & Sentences" => "SELECT
                DISTINCT c.IBISId AS id_number, 
                null AS date_of_testing,
                null AS age_at_testing,
                null AS version,
                null AS respondent,
                null AS cdi_ws_a1,
                null AS cdi_ws_a2,
                null AS cdi_ws_a3,
                null AS cdi_ws_a4,
                null AS cdi_ws_a5,
                null AS cdi_ws_a6,
                null AS cdi_ws_a7,
                null AS cdi_ws_a8,
                null AS cdi_ws_a9,
                null AS cdi_ws_a10,
                null AS cdi_ws_a11,
                null AS cdi_ws_a12,
                null AS cdi_ws_a13,
                null AS cdi_ws_a14,
                null AS cdi_ws_a15,
                null AS cdi_ws_a16,
                null AS cdi_ws_a17,
                null AS cdi_ws_a18,
                null AS cdi_ws_a19,
                null AS cdi_ws_a20,
                null AS cdi_ws_a21,
                null AS cdi_ws_a22,
                null AS cdi_ws_a_total,
                null AS cdi_ws_a_total_percentile,
                null AS cdi_ws_b1,
                null AS cdi_ws_b2,
                null AS cdi_ws_b3,
                null AS cdi_ws_b4,
                null AS cdi_ws_b5,
                null AS cdi_ws_part_ii_a1,
                null AS cdi_ws_part_ii_a2,
                null AS cdi_ws_part_ii_a3,
                null AS cdi_ws_part_ii_a4,
                null AS cdi_ws_part_ii_b,
                null AS cdi_ws_part_ii_b_percentile,
                null AS cdi_ws_part_ii_c,
                null AS cdi_ws_part_ii_combine_words,
                null AS cdi_ws_part_ii_d1,
                null AS cdi_ws_part_ii_d2,
                null AS cdi_ws_part_ii_d3,
                null AS cdi_ws_part_ii_m3l,
                null AS cdi_ws_part_ii_m3l_percentile,
                null AS cdi_ws_part_ii_e,
                null AS cdi_ws_part_ii_e_percentile
                FROM flag f JOIN session s ON (f.SessionID=s.ID) 
                JOIN candidate c ON (s.CandID=c.CandID)
                JOIN participant_status ps ON (ps.CandID=c.CandID)
                WHERE ps.study_consent='yes' AND s.CenterID!=1 AND c.Active='Y'
                AND f.CommentID NOT LIKE 'DDE_%' AND s.Visit_label <='V24'
                AND (COALESCE(ps.study_consent_withdrawal,'0000-00-00')='0000-00-00')
                AND (s.SubprojectID=1 OR s.SubprojectID=2 OR s.SubprojectID=3);",
           "Family Info"                 => "SELECT
                null AS family_id,
                null AS recruitment_date,
                null AS referral_source,
                null AS risk_status,
                null AS drop_status,
                null AS attrition_reason",
           "Person Info"                 => "SELECT DISTINCT 
                null AS family_id,
                c.IBISId AS id_number, 
                null AS family_member_type,
                null AS date_of_birth,
                null AS NDAR_GUID,
                null AS diagnosis,
                null AS method_of_diagnosis,
                null AS grant_number
                FROM flag f JOIN session s ON (f.SessionID=s.ID) 
                JOIN candidate c ON (s.CandID=c.CandID) 
                JOIN participant_status ps ON (ps.CandID=c.CandID)
                WHERE ps.study_consent='yes' AND s.CenterID!=1 AND c.Active='Y'
                AND f.CommentID NOT LIKE 'DDE_%' AND s.Visit_label <='V24'
                AND (COALESCE(ps.study_consent_withdrawal,'0000-00-00')='0000-00-00')
                AND (s.SubprojectID=1 OR s.SubprojectID=2 OR s.SubprojectID=3);",
           "Demographics"                => "SELECT DISTINCT c.IBISId AS id_number, 
                t.Date_taken AS date_of_testing,
                ROUND(t.Candidate_Age) AS age_at_testing,
                c.DoB AS baby_dob,
                c.Gender AS baby_gender,
                t.candidate_race AS baby_race,
                t.child_ethnicity AS baby_ethnicity,
                null AS baby_birth_order,
                t.mother_dob_date AS bio_mother_dob,
                t.mother_race AS bio_mother_race,
                t.mother_ethnicity AS bio_mother_ethnicity,
                t.father_dob_date AS bio_father_dob,
                t.father_race AS bio_father_race,
                t.father_ethnicity AS bio_father_ethnicity,
                'mother' AS respondent_relationship,
                null AS other_dob,
                null AS other_race,
                null AS other_ethnicity,
                t.mother_education AS respondent_ed,
                null AS respondent_marital_status,
                null AS respondent_employment,
                t.mother_occupation AS respondnet_occupation,
                t.ses_income AS household_income,
                null AS adults,
                null AS children,
                null AS number_asd,
                c.ProbandDoB AS child_1_dob,
                c.ProbandGender AS child_1_gender,
                p.2012alg_clinical_diag AS child_1_diagnosis,
                null AS child_2_dob,
                null AS child_2_gender,
                null AS child_2_diagnosis,
                null AS child_3_dob,
                null AS child_3_gender,
                null AS child_3_diagnosis,
                null AS child_4_dob,
                null AS child_4_gender,
                null AS child_4_diagnosis,
                null AS child_5_dob,
                null AS child_5_gender,
                null AS child_5_diagnosis,
                null AS child_6_dob,
                null AS child_6_gender,
                null AS child_6_diagnosis,
                null AS spouse_dob,
                'father' AS spouse_relation_to_baby,
                t.father_education AS spouse_ed,
                null AS spouse_employment,
                t.father_occupation AS spouse_occupation,
                null AS spouse_child_care,
                t.primary_language AS home_languages,
                null AS frequency_english,
                CASE s.SubprojectID WHEN 1 THEN 'high-risk' WHEN 2 THEN 'high-risk' 
                WHEN 3 THEN 'low-risk' END AS cohort
                FROM candidate c 
                JOIN session s ON (s.CandID=c.CandID) 
                LEFT JOIN flag ft ON (ft.SessionID=s.ID and ft.Test_name='tsi')
                JOIN tsi t ON (t.CommentID=ft.CommentID 
                and t.CommentID not like 'DDE_%')
                LEFT JOIN flag fp ON (fp.SessionID=s.ID 
                and fp.Test_name='adi_r_proband')
                JOIN adi_r_proband p ON (p.CommentID=fp.CommentID 
                and p.CommentID not like 'DDE_%')
                JOIN participant_status ps ON (ps.CandID=c.CandID)
                WHERE ps.study_consent='yes' AND s.CenterID!=1 AND c.Active='Y' 
                AND (COALESCE(ps.study_consent_withdrawal,'0000-00-00')='0000-00-00')
                AND (s.SubprojectID=1 OR s.SubprojectID=2 OR s.SubprojectID=3)
                AND (((ft.administration <> 'None' AND ft.administration is not null)
                OR t.data_entry_completion_status='Complete') 
                OR ((fp.administration <> 'None' AND fp.administration is not null) 
                OR p.data_entry_completion_status='Complete'))
                AND t.Candidate_Age >= 0 AND s.Visit_label <='V24';",
           "Clinical Best Estimate"      => "SELECT
                DISTINCT c.IBISId AS id_number, 
                null AS date_of_testing,
                null AS age_at_testing,
                null AS cbe_method,
                null AS cbe_professional,
                null AS cbe_diagnosis
                FROM flag f JOIN session s ON (f.SessionID=s.ID) 
                JOIN candidate c ON (s.CandID=c.CandID) 
                JOIN participant_status ps ON (ps.CandID=c.CandID)
                WHERE ps.study_consent='yes' AND s.CenterID!=1 AND c.Active='Y'
                AND f.CommentID NOT LIKE 'DDE_%' AND s.Visit_label <='V24'
                AND (COALESCE(ps.study_consent_withdrawal,'0000-00-00')='0000-00-00')
                AND (s.SubprojectID=1 OR s.SubprojectID=2 OR s.SubprojectID=3);",
           "ADOS"                        => "SELECT 
                c.IBISId as id_number, 
                a.Date_taken AS date_of_testing,
                ROUND(a.Candidate_Age) AS age_at_testing,
                'module 1' AS module,
                null AS version,
                null AS algorithm_type,
                null AS communication_total,
                null AS social_interaction_total,
                null AS communication_social_total,
                null AS play_imagination_creativity,
                null AS stereotyped_behaviors,
                a1,
                a2,
                a3,
                a4,
                a5,
                a6,
                a7,
                a8,
                ADOS_classification,
                b1,
                b10,
                b11,
                b12,
                b2,
                b3,
                b4,
                b5,
                b6,
                b7,
                b8,
                b9,
                c1,
                c2,
                d1,
                d2,
                d3,
                d4,
                e1,
                e2,
                e3,
                restricted_repetitive_behavior_total,
                social_affect_restricted_repetitive_behavior_total,
                social_affect_total,
                Validity
                FROM flag f JOIN session s ON (f.SessionID=s.ID)
                JOIN candidate c ON (s.CandID=c.CandID)
                JOIN ados_module1 a ON (a.CommentID=f.CommentID)
                JOIN participant_status ps ON (ps.CandID=c.CandID)
                LEFT JOIN conflicts_unresolved cu ON (cu.CommentId2=f.CommentID)
                WHERE ps.study_consent='yes' AND s.CenterID!=1 AND c.Active='Y' 
                AND (COALESCE(ps.study_consent_withdrawal,'0000-00-00')='0000-00-00')
                AND f.Data_entry='Complete' AND s.Visit_label <='V24'
                AND f.CommentID NOT LIKE 'DDE_%' AND cu.CommentID2 is null
                AND (s.SubprojectID=1 OR s.SubprojectID=2 OR s.SubprojectID=3)
                UNION
                SELECT
                c.IBISId as id_number, 
                a.Date_taken AS date_of_testing,
                ROUND(a.Candidate_Age) AS age_at_testing,
                'module 2' AS module,
                null AS version,
                null AS algorithm_type,
                null AS communication_total,
                null AS social_interaction_total,
                null AS communication_social_total,
                null AS play_imagination_creativity,
                null AS stereotyped_behaviors,
                a1,
                a2,
                a3,
                a4,
                a5,
                a6,
                a7,
                a8,
                ADOS_classification,
                b1,
                b10,
                b11,
                null AS b12,
                b2,
                b3,
                b4,
                b5,
                b6,
                b7,
                b8,
                b9,
                c1,
                c2,
                d1,
                d2,
                d3,
                d4,
                e1,
                e2,
                e3,
                restricted_repetitive_behavior_total,
                social_affect_restricted_repetitive_behavior_total,
                social_affect_total,
                Validity
                FROM flag f JOIN session s ON (f.SessionID=s.ID)
                JOIN candidate c ON (s.CandID=c.CandID)
                JOIN ados_module2 a ON (a.CommentID=f.CommentID)
                JOIN participant_status ps ON (ps.CandID=c.CandID)
                LEFT JOIN conflicts_unresolved cu ON (cu.CommentId2=f.CommentID)
                WHERE ps.study_consent='yes' AND s.CenterID!=1 AND c.Active='Y' 
                AND (COALESCE(ps.study_consent_withdrawal,'0000-00-00')='0000-00-00')
                AND f.Data_entry='Complete' AND s.Visit_label <='V24'
                AND f.CommentID NOT LIKE 'DDE_%' AND cu.CommentID2 is null
                AND (s.SubprojectID=1 OR s.SubprojectID=2 OR s.SubprojectID=3)
                UNION
                SELECT
                c.IBISId as id_number, 
                a.Date_taken AS date_of_testing,
                ROUND(a.Candidate_Age) AS age_at_testing,
                'module 3' AS module,
                null AS version,
                null AS algorithm_type,
                null AS communication_total,
                null AS social_interaction_total,
                null AS communication_social_total,
                null AS play_imagination_creativity,
                null AS stereotyped_behaviors,
                a1,
                a2,
                a3,
                a4,
                a5,
                a6,
                a7,
                a8,
                ADOS_classification,
                b1,
                b10,
                null AS b11,
                null AS b12,
                b2,
                b3,
                b4,
                b5,
                b6,
                b7,
                b8,
                b9,
                c1,
                null AS c2,
                d1,
                d2,
                d3,
                d4,
                e1,
                e2,
                e3,
                restricted_repetitive_behavior_total,
                social_affect_restricted_repetitive_behavior_total,
                social_affect_total,
                Validity
                FROM flag f JOIN session s ON (f.SessionID=s.ID)
                JOIN candidate c ON (s.CandID=c.CandID)
                JOIN ados_module3 a ON (a.CommentID=f.CommentID)
                JOIN participant_status ps ON (ps.CandID=c.CandID)
                LEFT JOIN conflicts_unresolved cu ON (cu.CommentId2=f.CommentID)
                WHERE ps.study_consent='yes' AND s.CenterID!=1 AND c.Active='Y' 
                AND (COALESCE(ps.study_consent_withdrawal,'0000-00-00')='0000-00-00')
                AND f.Data_entry='Complete' AND s.Visit_label <='V24'
                AND f.CommentID NOT LIKE 'DDE_%' AND cu.CommentID2 is null
                AND (s.SubprojectID=1 OR s.SubprojectID=2 OR s.SubprojectID=3);",
           "SCQ"                         => "SELECT
                DISTINCT c.IBISId AS id_number, 
                q.Date_taken AS date_of_testing,
                ROUND(q.Candidate_Age) AS age_at_testing,
                q.scq_version AS version,
                null AS respondent,
                q.score AS scq_total_score,
                scq_diagnosis,
                q1_talk_short_phrases,
                q2_to_and_fro,
                q3_odd_phrases,
                q4_socially_inappropriate,
                q5_pronouns_mixed,
                q6_words_invented,
                q7_said_same_thing,
                q8_particular_way,
                q9_facial_expressions,
                q10_hand_like_tool,
                q11_interests_that_preoccupy,
                q12_interested_in_parts	q13_intense_interests,
                q14_sight_feel_sound,
                q15_mannerisms,
                q16_complicated_movements,
                q17_deliberate_injury,
                q18_carry_objects,
                q19_particular_friends,
                q20_talk_friendly,
                q21_spontaneously_copy,
                q22_spontaneously_point,
                q23_gestures,
                q24_nod_yes,
                q25_shake_no,
                q26_look_directly,
                q27_smile_back,
                q28_show_things,
                q29_offer_share,
                q30_join_enjoyment,
                q31_comfort	q32_wanted_something,
                q33_facial_expressions,
                q34_spontaneously_join,
                q35_play_pretend,
                q36_seem_interested,
                q37_respond_positively,
                q38_came_into_room,
                q39_play_imaginative,
                q40_play_cooperatively,
                scq_version
                FROM flag f JOIN session s ON (f.SessionID=s.ID) 
                JOIN scq_proband q ON (q.CommentID=f.CommentID)
                JOIN candidate c ON (s.CandID=c.CandID)
                JOIN participant_status ps ON (ps.CandID=c.CandID)
                WHERE ps.study_consent='yes' AND s.CenterID!=1 AND c.Active='Y'
                AND f.CommentID NOT LIKE 'DDE_%' AND s.Visit_label <='V24'
                AND (COALESCE(ps.study_consent_withdrawal,'0000-00-00')='0000-00-00')
                AND (s.SubprojectID=1 OR s.SubprojectID=2 OR s.SubprojectID=3);",
           "SRS"                         => "SELECT
                DISTINCT c.IBISId AS id_number, 
                r.Date_taken AS date_of_testing,
                ROUND(r.Candidate_Age) AS age_at_testing,
                null AS version,
                null AS test_form,
                r.completed_by AS respondent,
                null AS srs_total_raw,
                r.srs_score AS srs_total_t_score,
                null AS srs_social_awareness_raw,
                null AS srs_social_cognition_raw,
                null AS srs_social_communication_raw,
                null AS srs_social_motivation_raw,
                null AS srs_autistic_mannerisms_raw,
                null AS srs_social_awareness_t_score,
                null AS srs_social_cognition_t_score,
                null AS srs_social_communication_t_score,
                null AS srs_social_motivation_t_score,
                null AS srs_autistic_mannerisms_t_score,
                q1_fidgety_social_situations,
                q2_expressions_dont_match,
                q3_seems_self_confident,
                q4_auto_pilot_under_stress,
                q5_no_recognize_take_advantage,
                q6_rather_be_alone,
                q7_aware_others_feeling,
                q8_behaves_strange,
                q9_clings_to_adults,
                q10_unable_pickup_meaning,
                q11_good_self_confidence,
                q12_able_communicate_feelings,
                q13_slow_turntaking_interactions,
                q14_not_well_coordinated,
                q15_able_understand_meaning,
                q16_avoids_eye_contact,
                q17_recognizes_unfair,
                q18_playground_no_interaction,
                q19_frustrated_conversations,
                q20_strange_playing,
                q21_able_imitate_others,
                q22_play_appropriately,
                q23_no_group_activities,
                q24_more_difficulty_routine,
                q25_doesnt_mind_out_of_step,
                q26_offers_comfort_to_others,
                q27_avoids_social_interactions,
                q28_talks_about_same_thing,
                q29_regarded_as_weird,
                q30_becomes_upset,
                q31_cant_get_mind_off_something,
                q32_wants_to_be_changed,
                q33_socially_awkward,
                q34_avoids_emotional_close,
                q35_trouble_keeping_flow,
                q36_difficulty_relating_adults,
                q37_difficulty_relating_peers,
                q38_responds_to_mood_changes,
                q39_restricted_interests,
                q40_imaginative,
                q41_wanders_aimlessly_activities,
                q42_overly_sensitive_sounds_smells,
                q43_separates_from_caregivers,
                q44_doesnt_understand_events,
                q45_focuses_attention_others,
                q46_overly_serious_expressions,
                q47_too_silly,
                q48_sense_of_humor,
                q49_does_well_few_tasks,
                q50_repetitive_odd_behaviors,
                q51_responds_odd_ways,
                q52_knows_talking_too_loud,
                q53_talks_unusual_tone_of_voice,
                q54_reacts_people_as_objects,
                q55_knows_invading_space,
                q56_walks_between_people,
                q57_other_children_dont_like,
                q58_concentrates_on_parts,
                q59_overly_suspicious,
                q60_is_emotionally_distant,
                q61_inflexible,
                q62_unusual_reasons,
                q63_touches_others_usually,
                q64_tense_social_settings,
                q65_stares_into_space
                FROM flag f JOIN session s ON (f.SessionID=s.ID)
                JOIN SRS r ON (r.CommentID=f.CommentID)
                JOIN candidate c ON (s.CandID=c.CandID)
                JOIN participant_status ps ON (ps.CandID=c.CandID)
                WHERE ps.study_consent='yes' AND s.CenterID!=1 AND c.Active='Y'
                AND f.CommentID NOT LIKE 'DDE_%'
                AND (COALESCE(ps.study_consent_withdrawal,'0000-00-00')='0000-00-00')
                AND (s.SubprojectID=1 OR s.SubprojectID=2 OR s.SubprojectID=3);",
           "Head Circumference"          => "SELECT
                DISTINCT c.IBISId AS id_number, 
                h.Date_taken AS date_of_testing,
                ROUND(h.Candidate_Age) AS age_at_testing,
                null AS data_method,
                h.head_circumference1 AS head_circumference,
                h.head_circumference_unit AS hc_units,
                h.weight1 AS weight,
                h.weight_unit AS weight_units,
                h.length1 AS height,
                h.head_length_unit AS height_units
                FROM flag f JOIN session s ON (f.SessionID=s.ID)
                JOIN head_measurements_subject h ON (h.CommentID=f.CommentID) 
                JOIN candidate c ON (s.CandID=c.CandID)
                JOIN participant_status ps ON (ps.CandID=c.CandID)
                WHERE ps.study_consent='yes' AND s.CenterID!=1 AND c.Active='Y'
                AND f.CommentID NOT LIKE 'DDE_%' AND s.Visit_label <='V24'
                AND (COALESCE(ps.study_consent_withdrawal,'0000-00-00')='0000-00-00')
                AND (s.SubprojectID=1 OR s.SubprojectID=2 OR s.SubprojectID=3);",
           "Intervention History"        => "SELECT
                DISTINCT c.IBISId AS id_number, 
                null AS visit,
                b.Date_taken AS date_of_testing,
                ROUND(b.Candidate_Age) AS age_at_testing,
                null AS test_version,
                b.date_lastVisit_date AS date_last_visit,
                null AS inthx1,
                null AS inthx2,
                null AS inthx2_avg_hrs,
                null AS inthx2_total_since,
                null AS inthx3,
                null AS inthx4,
                null AS inthx5,
                b.servicetype_occupationaltherapy AS inthx_ot,
                b.startdate_occupationaltherapy AS inthx_ot_start,
                null AS inthx_ot_start_age,
                b.continue_occupationaltherapy AS inthx_ot_still,
                b.stopdate_occupationaltherapy AS inthx_ot_stop,
                null AS inthx_ot_stop_age,
                null AS inthx_ot_ind_grp,
                b.setting_occupationaltherapy AS inthx_ot_setting,
                null AS inthx_ot_setting_other,
                b.avg_occupationaltherapy AS inthx_ot_avg_hrs_week,
                b.servicetype_physicaltherapy AS inthx_pt,
                b.startdate_physicaltherapy AS inthx_pt_start,
                null AS inthx_pt_start_age,
                b.continue_physicaltherapy AS inthx_pt_still,
                b.stopdate_physicaltherapy AS inthx_pt_stop,
                null AS inthx_pt_stop_age,
                null AS inthx_pt_ind_grp,
                b.setting_physicaltherapy AS inthx_pt_setting,
                null AS inthx_pt_setting_other,
                b.avg_physicaltherapy AS inthx_pt_avg_hrs_week,
                null AS inthx_speech,
                b.startdate_speechlangtherapy AS inthx_speech_start,
                null AS inthx_speech_start_age,
                b.continue_speechlangtherapy AS inthx_speech_still,
                b.stopdate_speechlangtherapy AS inthx_speech_stop,
                null AS inthx_speech_stop_age,
                null AS inthx_speech_ind_grp,
                b.setting_speechlangtherapy AS inthx_speech_setting,
                null AS inthx_speech_setting_other,
                b.avg_speechlangtherapy AS inthx_speech_avg_hrs_week,
                null AS inthx_comp,
                null AS inthx_comp_start,
                null AS inthx_comp_start_age,
                null AS inthx_comp_still,
                null AS inthx_comp_stop,
                null AS inthx_comp_stop_age,
                null AS inthx_comp_ind_grp,
                null AS inthx_comp_setting,
                null AS inthx_comp_setting_other,
                null AS inthx_comp_avg_hrs_week,
                null AS inthx_other,
                null AS inthx_other_description,
                null AS inthx_other_start,
                null AS inthx_other_start_age,
                null AS inthx_other_still,
                null AS inthx_other_stop,
                null AS inthx_other_stop_age,
                null AS inthx_other_ind_grp,
                null AS inthx_other_setting,
                null AS inthx_other_setting_other,
                null AS inthx_other_avg_hrs_week,
                null AS inthx6_a_since_last,
                null AS inthx6_b_past_year,
                null AS inthx7,
                null AS inthx7_specify,
                null AS inthx8,
                null AS inthx8_specify,
                null AS inthx9,
                null AS inthx10_speech,
                null AS inthx10_ot,
                null AS inthx10_pt,
                null AS inthx10_comp,
                null AS inthx10_other,
                null AS inthx_comments
                FROM flag f JOIN session s ON (f.SessionID=s.ID)
                JOIN BSRC b ON (b.CommentID=f.CommentID)
                JOIN candidate c ON (s.CandID=c.CandID)
                JOIN participant_status ps ON (ps.CandID=c.CandID)
                WHERE ps.study_consent='yes' AND s.CenterID!=1 AND c.Active='Y'
                AND f.CommentID NOT LIKE 'DDE_%' AND s.Visit_label <='V24'
                AND (COALESCE(ps.study_consent_withdrawal,'0000-00-00')='0000-00-00')
                AND (s.SubprojectID=1 OR s.SubprojectID=2 OR s.SubprojectID=3);",
          );

    foreach ($TQ as $name => $query) {
        addSheet($query, $name);
    }

    // Writing the excel file out
    $writer = PHPExcel_IOFactory::createWriter($ExcelApplication, 'Excel2007');
    $writer->save('BSRC-submission-' . $argv[1] . '.xlsx');

    print "-- were done.\n\n";
}
