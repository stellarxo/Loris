<?php
set_include_path(get_include_path().":../libraries:../../php/libraries:");
require_once "NDB_Client.class.inc";
require_once "Utility.class.inc";
require_once "Database.class.inc";
//require_once "../../tools/generic_includes.php";
$client = new NDB_Client();
$client->makeCommandLine();
$client->initialize('../config.xml');

$db        =& Database::singleton();
if (Utility::isErrorX($db)) {
        print "Could not connect to database: " . $db->getMessage();
            exit(1);
}
$mapping = array('preg_complic'=>'pregnancy_complication_subject','preg_dxdrug'=>'','birth_weight_lbs'=>'birth_weight_lbs',
                 'ldnb_lgthin'=>'ldnb_lgthin', 'full_term'=>'full_term','ldnb_hosptotalmom'=>'ldnb_hosptotalmom',
                 'rev_headfebseiz'=>'rev_headfebseiz','rev_headseizure'=>'q15_seizures_convulsions',
                 'fhxcp'=>'fhxcp','hist_trauma'=>'hist_trauma','rev_eartest'=>'rev_eartest','rev_eartestresult'=>'rev_eartestresult',
                 'rev_neckspinalab'=>'rev_neckspinalab','rev_skinbirthmark'=>'rev_skinbirthmark',
                 'rev_cardiomalfunc'=>'rev_cardiomalfunc','rev_immunomedallergy'=>'med_his_q_6_allergies',
                 'gen_dis'=>'gen_dis','othmem_bipolar','othmem_depression'=>'othmem_depression','othmem_anxiety'=>'othmem_anxiety',
                 'othmem_schizophrenia'=>'othmem_schizophrenia','othmem_adhd'=>'othmem_adhd');
/*
$tsi = array(t.pregnancy_complication_subject, t.premature_birth, t.weeks_gestation, t.med_his_q_6_allergies);
$neuro_screen = array(n.q23_adenoma_sebaceum,n.q25_shagreen_patches_describe);
$med_psych_hist =  array(m.q6_a_antibio_infections_when_taken, m.q6_b_acne_meds_when_taken, 
        m.q6_c_birth_control_meds_when_taken,
        m.q6_d_antihypertensives_when_taken,
        m.q6_e_heart_cardiac_meds_when_taken,
        m.q6_f_add_meds_when_taken,
        m.q6_g_antiepilep_anti_seizure_when_taken,
        m.q6_h_diabetes_meds_when_taken,
        m.q6_i_thyroid_meds_when_taken,
        m.q6_j_antidepressants_when_taken,
        m.q6_k_mood_stabs_anti_psychos_when_taken,
        m.q6_l_tranquilizers_nerve_pills_when_taken,
        m.q6_m_pain_killers_when_taken,
        m.q6_n_sedatives_sleeping_pills_when_taken,
        m.q6_o_anti_inflam_immune_when_taken,
        m.q6_p_treatment_for_HIV_when_taken,
        m.q6_q_thalidomide_when_taken,
        m.q6_r_misoprostol_when_taken,
        m.q6_s_other_when_taken,
        m.q11_birth_weight_lbs,
        m.q11_birth_weight_ozs,
        m.q14_child_hospitalised_days,
        m.q14_child_hospitalised_hours,
        m.q15_c_fever_seizures,
        m.q15_seizures_convulsions,
        m.m_cerebral_palsy, 
        m.q16_has_child_ever,
        m.q17_birth_defects,
        m.e_rett_syndrome,
        m.e_rett_syndrome_who, 
        m.c_tuberous_sclerosis,
        m.c_tuberous_sclerosis_who,
        m.b_fragile_x,
        m.b_fragile_x_who,
        m.d_neurofibromatosis,
        m.d_neurofibromatosis_who,
        m.t_manic_depres_bi,
        m.t_manic_depres_bi_who,
        m.s_depression_who,
        m.s_depression_who_who,
        m.r_panic_anxiety_dis,
        m.r_panic_anxiety_dis_who,
        m.u_schizophrenia,
        m.u_schizophrenia_who,
        m.q_add,
        m.q_add_who
        );

$med_records = array(mr.first_measurement_length_units_stat, mr.first_measurement_length_cm,mr.first_measurement_length_inches,mr.not_completed,
                     mr.test_results); */
$result = $db->pselect("SELECT t.pregnancy_complication_subject, t.premature_birth, t.weeks_gestation, t.med_his_q_6_allergies,
                        mr.first_measurement_length_units_stat, mr.first_measurement_length_cm,mr.first_measurement_length_inches,
                        mr.not_completed, mr.test_results, m.q6_a_antibio_infections_when_taken, m.q6_b_acne_meds_when_taken,
                        m.q6_c_birth_control_meds_when_taken, m.q6_d_antihypertensives_when_taken, m.q6_e_heart_cardiac_meds_when_taken,
                        m.q6_f_add_meds_when_taken, m.q6_g_antiepilep_anti_seizure_when_taken, m.q6_h_diabetes_meds_when_taken,
                        m.q6_i_thyroid_meds_when_taken, m.q6_j_antidepressants_when_taken, m.q6_k_mood_stabs_anti_psychos_when_taken,
                        m.q6_l_tranquilizers_nerve_pills_when_taken, m.q6_m_pain_killers_when_taken, m.q6_n_sedatives_sleeping_pills_when_taken,
                        m.q6_o_anti_inflam_immune_when_taken,m.q6_p_treatment_for_HIV_when_taken, m.q6_q_thalidomide_when_taken,
                        m.q6_r_misoprostol_when_taken, m.q6_s_other_when_taken,m.q11_birth_weight_lbs, m.q11_birth_weight_ozs,
                        m.q14_child_hospitalised_days, m.q14_child_hospitalised_hours, m.q15_c_fever_seizures, m.q15_seizures_convulsions,
                        m.m_cerebral_palsy, m.q16_has_child_ever, m.q17_birth_defects, m.e_rett_syndrome, m.e_rett_syndrome_who,
                        m.c_tuberous_sclerosis, m.c_tuberous_sclerosis_who, m.b_fragile_x, m.b_fragile_x_who, m.d_neurofibromatosis,
                        m.d_neurofibromatosis_who, m.t_manic_depres_bi, m.t_manic_depres_bi_who, m.s_depression_who,m.s_depression_who,
                        m.r_panic_anxiety_dis, m.r_panic_anxiety_dis_who, m.u_schizophrenia, m.u_schizophrenia_who, m.q_add,m.q_add_who,
                        n.q23_adenoma_sebaceum,n.q25_shagreen_patches_describe
                        FROM session s LEFT JOIN flag tflag ON (s.ID = tflag.SessionID AND tflag.Test_name='tsi') 
                        LEFT JOIN flag mflag ON (s.ID = mflag.SessionID AND mflag.Test_name='med_psych_hist')
                        LEFT JOIN flag nflag ON (s.ID = nflag.SessionID AND nflag.Test_name='neuro_screen')
                        LEFT JOIN flag mrflag ON (s.ID = mrflag.SessionID AND mrflag.Test_name='med_records_24')
                        LEFT JOIN tsi t ON (tflag.CommentID = t.CommentID)
                        LEFT JOIN med_psych_hist m ON (mflag.CommentID = m.CommentID)
                        LEFT JOIN neuro_screen n ON (nflag.CommentID = n.CommentID)
                        LEFT JOIN med_records_24 mr ON (mrflag.CommentID = mr.CommentID) WHERE s.ID = 482 AND tflag.CommentID NOT LIKE 'DDE%' 
                        AND mflag.CommentID NOT LIKE 'DDE%' AND mrflag.CommentID NOT LIKE 'DDE%' AND nflag.CommentID NOT LIKE 'DDE%'", array());

print_r($result);
?>
