<?php
set_include_path(get_include_path() . ":../libraries:../../php/libraries:");
require_once "Database.class.inc";

class NDAR_Release_2016
{

    function __construct($instrument, $project)
    {
        $this->instrument = $instrument;
        $this->project = $project;
    }

    function getWhere()
    {
        if (strpos($this->instrument, '_proband') !== FALSE) {
            $GUID = "AND COALESCE(c.ProbandGUID, '') <> ''";
        } else {
            $GUID = "AND COALESCE(c.CandidateGUID, '') <> ''";
        }
        $Base = "COALESCE(s.Current_stage, '') <> 'Recycling Bin' AND COALESCE(s.Visit, '') NOT IN ('Failure', 'Withdrawal') AND COALESCE(s.Screening, '') NOT IN ('Failure', 'Withdrawal') AND f.Administration='All' AND f.Data_entry='Complete' AND EXISTS (SELECT 'x' FROM flag df WHERE df.CommentID=CONCAT('DDE_', i.CommentID) AND df.Data_entry='Complete') AND NOT EXISTS (SELECT 'x' FROM conflicts_unresolved cu WHERE cu.CommentId1=i.CommentID OR cu.CommentId2=i.CommentID) AND s.CenterID IN (2, 3, 4, 5) AND ( ps.study_consent = 'yes' AND ps.study_consent_withdrawal IS NULL) AND (ps.ndar_consent = 'yes' AND ps.ndar_consent_withdrawal IS NULL) AND c.Active='Y' AND s.Active ='Y'";
        if ($this->instrument == 'adi_r_proband') {
            if ($this->project == 2) {
                return $Base . " AND i.Summary_diagnosis='ASD+' AND s.SubprojectID IN (9,10) AND s.Visit_label ='Screening' $GUID";
            } else {
                // Check Summary_diagnosis=ASD+
                return $Base . " AND i.Summary_diagnosis='ASD+' AND s.SubprojectID IN (1,2) $GUID";
            }
        } else if ($this->instrument == 'm_chat_proband') {
            // Check score=Fail and not Control
            if ($this->project == 2) {
                return $Base . " AND s.Visit_label='Screening' $GUID";
            } else {
                return $Base . " AND s.SubprojectID <> 3 AND i.score='Fail' $GUID";
            }
        } else if ($this->instrument == 'scq_proband') {
            // Check scq_diagnosis=ASD_Positive and 6/12mo recruit
            if ($this->project == 2) {
                return $Base . " AND s.Visit_label='Screening' $GUID";
            } else {
                return $Base . " AND s.SubprojectID IN (1, 2) AND i.scq_diagnosis='ASD Positive' $GUID";
            }
        } else if ($this->instrument == 'aosi' || $this->instrument == 'ibq_r') {
            if ($this->project == 2 && $this->instrument == 'aosi') {
                return $Base . " AND s.SubprojectID = 10 AND UPPER(s.Visit_label) IN ('V06','V09', 'V12', 'V15') $GUID";
            } else if ($this->project == 2 && $this->instrument == 'ibq_r') {
                return $Base . " AND (s.SubprojectID=10 AND UPPER(s.Visit_label) IN ('V03','V06','V09','V12') OR s.SubprojectID=9 AND UPPER(s.Visit_label) IN ('V03')) $GUID";

            } else {
                return $Base . " AND ((s.SubprojectID=1 AND UPPER(s.Visit_label)='V06') OR (s.SubprojectID=3 AND UPPER(s.Visit_label) IN ('V06', 'V12'))) $GUID";
            }
        } else if ($this->instrument == 'vineland_proband') {
            if ($this->project == 1) {
                return "COALESCE(s.Current_stage, '') <> 'Recycling Bin' AND COALESCE(s.Visit, '') NOT IN ('Failure', 'Withdrawal') AND COALESCE(s.Screening, '') NOT IN ('Failure', 'Withdrawal') AND f.Administration='All' AND f.Data_entry='Complete' AND s.CenterID IN (2, 3, 4, 5) AND s.SubprojectID IN (1, 2) AND ( ps.study_consent = 'yes' AND ps.study_consent_withdrawal IS NULL) AND (ps.ndar_consent = 'yes' AND ps.ndar_consent_withdrawal IS NULL) $GUID";
            } else {
                // No DDE
                return "COALESCE(s.Current_stage, '') <> 'Recycling Bin' AND COALESCE(s.Visit, '') NOT IN ('Failure', 'Withdrawal') AND COALESCE(s.Screening, '') NOT IN ('Failure', 'Withdrawal') AND
             f.Administration='All' AND f.Data_entry='Complete' AND s.CenterID IN (2, 3, 4, 5) AND s.SubprojectID=9 AND s.Visit_label='Screening' AND ( ps.study_consent = 'yes' AND ps.study_consent_withdrawal IS NULL) AND (ps.ndar_consent = 'yes' AND ps.ndar_consent_withdrawal IS NULL) $GUID ";
            }
        } else if ($this->instrument == 'vineland_subject') {
            // No DDE
            if ($this->project == 2) {
                return "COALESCE(s.Current_stage, '') <> 'Recycling Bin' AND COALESCE(s.Visit, '') NOT IN ('Failure', 'Withdrawal') AND COALESCE(s.Screening, '') NOT IN ('Failure', 'Withdrawal') AND f.Administration='All' AND f.Data_entry='Complete' AND s.CenterID IN (2, 3, 4, 5) AND ((s.SubprojectID=9 AND UPPER(s.Visit_label)='V03') OR (s.SubprojectID=10 AND UPPER(s.Visit_label) IN ('V03','V06','V09', 'V12','V15','V18', 'V24'))) AND ( ps.study_consent = 'yes' AND ps.study_consent_withdrawal IS NULL) AND (ps.ndar_consent = 'yes' AND ps.ndar_consent_withdrawal IS NULL) $GUID ";
            } else {
                return "COALESCE(s.Current_stage, '') <> 'Recycling Bin' AND COALESCE(s.Visit, '') NOT IN ('Failure', 'Withdrawal') AND COALESCE(s.Screening, '') NOT IN ('Failure', 'Withdrawal') AND f.Administration='All' AND f.Data_entry='Complete' AND s.CenterID IN (2, 3, 4, 5) AND ((s.SubprojectID=1 AND UPPER(s.Visit_label)='V06') OR (s.SubprojectID=3 AND UPPER(s.Visit_label) IN ('V06', 'V12', 'V24'))) AND ( ps.study_consent = 'yes' AND ps.study_consent_withdrawal IS NULL) AND (ps.ndar_consent = 'yes' AND ps.ndar_consent_withdrawal IS NULL) $GUID ";
            }
        } else if ($this->instrument == 'prefrontal_task' || $this->instrument == 'csbs') {
            if ($this->project == 2 && $this->instrument == 'csbs') {
                return $Base . " AND s.SubprojectID=10 AND UPPER(s.Visit_label) IN ('V09', 'V15') $GUID";
            } else {
                return $Base . " AND s.SubprojectID=3 AND UPPER(s.Visit_label) IN ('V12', 'V24') $GUID";
            }
        } else if ($this->instrument == 'fyi') {
            return $Base . " AND s.SubprojectID=3 AND UPPER(s.Visit_label)='V12' $GUID";
        } else if ($this->instrument == 'edi') {
            return $Base . " AND ((s.SubprojectID=1 AND UPPER(s.Visit_label)='V06') OR  (s.SubprojectID=3 AND UPPER(s.Visit_label) IN ('V06', 'V12', 'V24' ))) AND s.SubprojectID <> 2 $GUID";
        } else if ($this->instrument == 'scq' || $this->instrument == 'rbs_r') {
            if ($this->project == 2) {
                if ($this->instrument == 'rbs_r') {
                    return $Base . " AND s.SubprojectID=10 AND s.Visit_label ='V12' $GUID";
                }
                else {
                    return $Base . " AND s.SubprojectID=9 AND UPPER(s.Visit_label) IN ('V12', 'V24') $GUID";
                }
            } else {
                return $Base . " AND UPPER(s.Visit_label) IN ('V12', 'V24') $GUID";
            }
        } else if ($this->instrument == 'seq' && $this->project == 1) {
            return $Base . " AND UPPER(s.Visit_label) IN ('V12', 'V24') $GUID";
        } else if ($this->instrument == 'mullen' || $this->instrument == 'edi2') {
            if ($this->project == 2) {
                return $Base . " AND (s.SubprojectID=10 AND UPPER(s.Visit_label) IN ('V03','V06','V09','V12','V15','V18','V24') OR s.SubprojectID=9 AND UPPER(s.Visit_label) IN ('V03')) $GUID";
            }
            else {
                return $Base . " AND s.SubprojectID<>7 AND UPPER(s.Visit_label) IN ('V06', 'V12', 'V24') $GUID";
            }
        } else if ($this->instrument == 'charge') {
            // Don't use Base because there's multiple instruments
            // All the conflicts don't exist is done in the join, since they need to be part of the left join
            // criteria
            return " COALESCE( medpsychflag.CommentID, neuroscreenflag.CommentID, tsiflag.CommentID) IS NOT NULL AND
                    COALESCE(s.Current_stage, '') <> 'Recycling Bin' AND COALESCE(s.Visit, '') NOT IN ('Failure', 'Withdrawal')
                    AND COALESCE(s.Screening, '') NOT IN ('Failure', 'Withdrawal')
                    AND s.CenterID IN (2, 3, 4, 5) AND ((s.SubprojectID=1 AND UPPER(s.Visit_label)='V06') OR (s.SubprojectID=3 AND UPPER(s.Visit_label) IN ('V06', 'V12', 'V24'))) AND ( ps.study_consent = 'yes' AND ps.study_consent_withdrawal IS NULL) AND (ps.ndar_consent = 'yes' AND ps.ndar_consent_withdrawal IS NULL) $GUID";
        } else if ($this->instrument == 'head_measurements_subject' && $this->project == 2) {
            return $Base . " AND ((s.SubprojectID=9 AND UPPER(s.Visit_label)='V03') OR (s.SubprojectID=10 AND UPPER(s
            .Visit_label) IN ('V03','V06','V09','V12','V15','V18','V24'))) $GUID";
        } else if ($this->instrument == 'macarthur_words_gestures') {
            if ($this->project == 2) {
                return $Base . " AND (s.SubprojectID=10 AND UPPER(s.Visit_label) IN ('V12', 'V24')) $GUID";
            } else {
                return $Base . " AND UPPER(s.Visit_label) IN ('V12', 'V24') $GUID";
            }
        } else if ($this->instrument == 'ndar_subject') {
            if ($this->project == 2) {
                return $Base . " AND UPPER(s.Visit_label) IN ('V03') $GUID";
            }
            return $Base . " AND c.ProjectID = $this->project $GUID";
        }
        return $Base . " AND ((s.SubprojectID=1 AND UPPER(s.Visit_label)='V06') OR (s.SubprojectID=3 AND UPPER(s.Visit_label) IN ('V06', 'V12', 'V24'))) $GUID";
    }

    function getCommonFields()
    {
        $ndar_info = " ps.study_consent AS 'Study Consent', ps.study_consent_date AS 'Study Consent Date', ps.ndar_consent AS 'NDAR Consent', ps.ndar_consent_date AS 'NDAR Consent Date',ps.ndar_consent_withdrawal,ps.study_consent_withdrawal, ";
        if ($this->instrument == 'charge') {
            return "c.IBISID, ";
        }
        if (strpos($this->instrument, '_proband') !== FALSE) {
            if ($this->instrument == 'm_chat_proband' || $this->instrument == 'scq_proband') {
                // No validity
                return "c.IBISID,  c.ProbandGUID,  CASE c.ProbandGender WHEN 'Male' THEN 'M' WHEN 'Female' THEN 'F' END AS ProbandGender, ROUND(DATEDIFF(i.Date_taken, c.ProbandDoB) / (365/12)) AS Proband_Age_in_Months, i.Date_taken as interview_date, ";
            }
            return "c.IBISID, c.ProbandGUID,  CASE c.ProbandGender WHEN 'Male' THEN 'M' WHEN 'Female' THEN 'F' END AS ProbandGender, ROUND(DATEDIFF(i.Date_taken, c.ProbandDoB) / (365/12)) AS Proband_Age_in_Months, f.Validity as validity_of_data, i.Date_taken as interview_date, ";
        } else {
            $NoValidities = array('macarthur_words_gestures', 'seq', 'rbs_r', 'ibq_r', 'head_measurements_subject', 'prefrontal_task', 'fyi', 'scq_proband');
            if (in_array($this->instrument, $NoValidities)) {
                if ($this->instrument == 'head_measurements_subject') {
                    return "c.IBISID, c.CandidateGUID as subjectkey, CASE c.Gender WHEN 'Male' THEN 'M' WHEN 'Female' THEN 'F' END AS Gender, ROUND(DATEDIFF(i.Date_taken, c.DoB) / (365/12)) AS Candidate_Age_in_Months, i.Date_taken as interview_date, ";
                }
                return "c.IBISID, c.CandidateGUID, CASE c.Gender WHEN 'Male' THEN 'M' WHEN 'Female' THEN 'F' END AS Gender , ROUND(DATEDIFF(i.Date_taken, c.DoB) / (365/12)) AS Candidate_Age_in_Months, i.Date_taken as interview_date, ";
            }
            return "c.IBISID, c.CandidateGUID, CASE c.Gender WHEN 'Male' THEN 'M' WHEN 'Female' THEN 'F' END AS Gender , ROUND(DATEDIFF(i.Date_taken, c.DoB) / (365/12)) AS Candidate_Age_in_Months, f.Validity as validity_of_data, i.Date_taken as interview_date, ";
        }
    }

    function getInstrumentFields()
    {
        if ($this->instrument == 'adi_r_proband') {
            $fields = array(
                'i.A_Total',
                'i.BNV_Total',
                'i.BV_Total',
                'i.C_Total',
                'i.D_Total',
                'i.Total_A1',
                'i.Total_A2',
                'i.Total_A3',
                'i.Total_A4',
                'i.Total_B1',
                'i.Total_B2V',
                'i.Total_B3V',
                'i.Total_B4',
                'i.Total_C1',
                'i.Total_C2',
                'i.Total_C3',
                'i.Total_C4',
                'i.summary_diagnosis',
                'i.informant_relation as relationship',
                'i.q_2_age_first_noticed_code',
                'i.q_4_onset_as_perceived_code',
                'i.q_5_first_walked_code',
                'i.q_6_bladder_daytime_code',
                'i.q_7_bladder_nighttime_code',
                'i.q_8_bowel_control_code',
                'i.q_9_first_single_words_code',
                'i.q_10_first_phrases_code',
                'i.q_11_loss_of_language',
                'i.q_12_level_before_loss_code',
                'i.q_13_loss_of_spontaneous_use_code',
                'i.q_14_loss_of_intent_code',
                'i.q_15_loss_of_syntactical_code',
                'i.q_16_loss_of_articulation_code',
                'i.q_17_main_loss_apparent_code',
                'i.q_18_loss_due_to_illness',
                'i.q_19_duration_of_loss_code',
                'i.q_20_loss_of_skills_code',
                'i.q_21_puposive_hand_movements_code',
                'i.q_22_motor_skills_code',
                'i.q_23_self_help_skills_code',
                'i.q_24_constructive_play_code',
                'i.q_25_social_engagement_code',
                'i.q_26_loss_first_apparent_code',
                'i.q_27_physical_illness_code',
                'i.q_28_duration_of_loss_code',
                'i.q_29_compreh_simple_current',
                'i.q_29_compreh_simple_most_abnormal',
                'i.q_30_overall_level_of_language',
                'i.q_31_use_of_others_body_current_code AS q_31_use_of_oth_body_curr_code',
                'i.q_31_use_of_others_body_ever_code ',
                'i.q_32_artic_pronun_5years_code',
                'i.q_32_artic_pronun_current_code',
                'i.q_33_stereotyped_utterances_current_code',
                'i.q_33_stereotyped_utterances_ever_code',
                'i.q_34_social_verb_chat_current_code',
                'i.q_34_social_verb_chat_ever_code',
                'i.q_35_recipr_convers_current_code',
                'i.q_35_recipr_convers_ever_code',
                'i.q_36_inappropriate_qs_current_code',
                'i.q_36_inappropriate_qs_ever_code',
                'i.q_37_prenominal_reversal_current_code',
                'i.q_37_prenominal_reversal_ever_code',
                'i.q_38_neologisms_current_code',
                'i.q_38_neologisms_ever_code',
                'i.q_39_verbal_rituals_current_code',
                'i.q_39_verbal_rituals_ever_code',
                'i.q_40_inton_vol_rhythm_rate_current_code',
                'i.q_40_inton_vol_rhythm_rate_ever_code',
                'i.q_41_cur_comm_speech_at5_code',
                'i.q_41_cur_comm_speech_current_code',
                'i.q_42_point_express_inter_most_abnormal_code',
                'i.q_42_point_express_interest_current_code',
                'i.q_43_nodding_current_code',
                'i.q_43_nodding_most_abnormal_code',
                'i.q_44_head_shaking_current_code',
                'i.q_44_head_shaking_most_abnormal_code',
                'i.q_45_conventional_instr_gests_current_code',
                'i.q_45_conventional_instr_gests_most_abnormal_code',
                'i.q_46_attent_voice_current_code',
                'i.q_46_attent_voice_most_abnormal_code',
                'i.q_47_spont_imit_current_code',
                'i.q_47_spont_imit_most_abnormal_code',
                'i.q_48_imag_play_current_code',
                'i.q_48_imag_play_most_abnormal_code',
                'i.q_49_imag_play_peers_current_code',
                'i.q_49_imag_play_peers_most_abnormal_code',
                'i.q_50_direct_gaze_current_code',
                'i.q_50_direct_gaze_most_abnormal_code',
                'i.q_51_social_smiling_current_code',
                'i.q_51_social_smiling_most_abnormal_code',
                'i.q_52_show_direct_atten_current_code',
                'i.q_52_show_direct_atten_most_abnormal_code',
                'i.q_53_offer_share_current_code',
                'i.q_53_offer_share_most_abnormal_code',
                'i.q_54_seek_share_enjoy_current_code',
                'i.q_54_seek_share_enjoy_most_abnormal_code',
                'i.q_55_offer_comf_current_code',
                'i.q_55_offer_comf_most_abnormal_code',
                'i.q_56_qual_social_overts_current_code',
                'i.q_56_qual_social_overts_most_abnormal_code',
                'i.q_57_range_facial_expr_current_code',
                'i.q_57_range_facial_expr_most_abnormal_code',
                'i.q_58_inappropriate_facial_current_code',
                'i.q_58_inappropriate_facial_ever_code',
                'i.q_59_appropriat_resp_current_code',
                'i.q_59_appropriat_resp_most_abnormal_code',
                'i.q_60_init_activities_current_code',
                'i.q_60_init_activities_most_abnormal_code',
                'i.q_61_imit_soc_play_current_code',
                'i.q_61_imit_soc_play_most_abnormal_code',
                'i.q_62_inter_children_current_code',
                'i.q_62_inter_children_most_abnormal_code',
                'i.q_63_resp_approaches_current_code',
                'i.q_63_resp_approaches_most_abnormal_code',
                'i.q_64_group_play_peers_current_code',
                'i.q_64_group_play_peers_most_abnormal_code',
                'i.q_65_friendships_current_code',
                'i.q_65_friendships_most_abnormal_code',
                'i.q_66_soc_disinhibit_current_code',
                'i.q_66_soc_disinhibit_most_abnormal_code',
                'i.q_67_unusual_preoccupations_current_code',
                'i.q_67_unusual_preoccupations_ever_code',
                'i.q_68_circumscr_ints_current_code',
                'i.q_68_circumscr_ints_ever_code',
                'i.q_69_repet_use_objects_current_code',
                'i.q_69_repet_use_objects_ever_code',
                'i.q_70_compulsions_rituals_current_code',
                'i.q_70_compulsions_rituals_ever_code',
                'i.q_71_unusual_sens_ints_current_code',
                'i.q_71_unusual_sens_ints_ever_code',
                'i.q_72_undo_gen_sens_noise_current_code',
                'i.q_72_undo_gen_sens_noise_ever_code',
                'i.q_73_idiosyncratic_current_code',
                'i.q_73_idiosyncratic_ever_code',
                'i.q_74_diff_minor_changes_current_code',
                'i.q_74_diff_minor_changes_ever_code',
                'i.q_75_resist_trivial_chng_current_code',
                'i.q_75_resist_trivial_chng_ever_code',
                'i.q_76_unus_attach_objects_current_code',
                'i.q_76_unus_attach_objects_ever_code',
                'i.q_77_hands_finger_manners_current_code',
                'i.q_77_hands_finger_manners_ever_code',
                'i.q_78_oth_complex_manners_current_code',
                'i.q_78_oth_complex_manners_ever_code',
                'i.q_79_midline_hand_moves_current_code',
                'i.q_79_midline_hand_moves_ever_code',
                'i.q_80_gait_current_code',
                'i.q_80_gait_most_abnormal_code',
                'i.q_81_aggress_caregivers_current_code',
                'i.q_81_aggress_caregivers_ever_code',
                'i.q_82_aggress_noncaregivers_current_code',
                'i.q_82_aggress_noncaregivers_ever_code',
                'i.q_83_self_injury_current_code',
                'i.q_83_self_injury_ever_code',
                'i.q_84_hyperventilation_current_code',
                'i.q_84_hyperventilation_ever_code',
                'i.q_85_faints_fits_blackouts_current_code',
                'i.q_85_faints_fits_blackouts_ever_code',
                'i.q_86_age_when_abnormality_first_evident',
                'i.q_87_interviewers_judgment',
                'i.q_88_visuospatial_ability_current_code',
                'i.q_88_visuospatial_ability_ever_code',
                'i.q_89_memory_still_current_code',
                'i.q_89_memory_still_ever_code',
                'i.q_90_musical_ability_current_code',
                'i.q_90_musical_ability_ever_code',
                'i.q_91_drawings_skill_current_code',
                'i.q_91_drawings_skill_ever_code',
                'i.q_92_reading_ability_current_code',
                'i.q_92_reading_ability_ever_code',
                'i.q_93_computational_ability_current_code',
                'i.q_93_computational_ability_ever_code'
            );
        } else if ($this->instrument === 'aosi') {
            $fields = array(
                'i.examiner_location',
                'i.total_score_1_18 AS aosi_totalscore',
                'i.number_of_markers AS aosi_numbermarkers',
                'i.q1_visual_tracking_score AS aosi_q1_visualinstructions',
                'i.q2_disengagement_of_attention_score as aosi_q2_disengagementscore',
                'i.q3_orients_to_name_score AS aosi_q3_orientsnameinstruct',
                'i.q4_differential_response_to_facial_emotion',
                'i.q5_anticipatory_response',
                'i.q6_imitation_of_actions_score AS aosi_q6_activitiesinstruction',
                'i.q7_social_babbling',
                'i.q8_eye_contact',
                'i.q9_reciprocal_social_smile',
                'i.q10_coordination_of_eye_gaze_and_action',
                'i.q11_reactivity',
                'i.q14_social_interest',
                'i.q15_transitions',
                'i.q16_motor_control_and_behaviour',
                'i.q17_atypical_motor',
                'i.q18_atypical_sensory',
                'i.q19_engagement_of_attention',
                'i.q20_insistence_on_particular_objects',
                'i.q21_social_referencing',
            );
        } else if ($this->instrument == 'seq') {
            $fields = array(
                'i.person_completing',
                'i.person_completing_other',
                'i.q1_react_sensitively',
                'i.q1_react_sensitively_change',
                'i.q2_enjoy_music',
                'i.q2_enjoy_music_change',
                'i.q3_ignore_call',
                'i.q3_ignore_call_change',
                'i.q4_ignore_tune_out',
                'i.q4_ignore_tune_out_change',
                'i.q5_notive_sounds',
                'i.q5_notive_sounds_change',
                'i.q6_show_distress_loud',
                'i.q6_show_distress_loud_change',
                'i.q7_enjoy_picture_books_change',
                'i.q8_disturbed_by_light',
                'i.q8_disturbed_by_light_change',
                'i.q9_stare_at_lights',
                'i.q9_stare_at_lights_change',
                'i.q10_slow_to_notice AS sesi4a',
                'i.q10_slow_to_notice_change AS sesi4b',
                'i.q11_avoid_looking',
                'i.q11_avoid_looking_change',
                'i.q12_seem_to_ignore',
                'i.q12_seem_to_ignore_change',
                'i.q13_enjoy_watching_videos',
                'i.q13_enjoy_watching_videos_change',
                'i.q14_dislike_cuddling',
                'i.q14_dislike_cuddling_change',
                'i.q15_show_distress_grooming',
                'i.q15_show_distress_grooming_change',
                'i.q16_avoid_touching',
                'i.q16_avoid_touching_change',
                'i.q17_react_negatively',
                'i.q17_react_negatively_change',
                'i.q18_trouble_adjusting',
                'i.q18_trouble_adjusting_change',
                'i.q19_slow_to_react',
                'i.q19_slow_to_react_change',
                'i.q20_dislike_tickled',
                'i.q20_dislike_tickled_change',
                'i.q21_ignore_tap',
                'i.q21_ignore_tap_change',
                'i.q22_refuse_new_foods',
                'i.q22_refuse_new_foods_change',
                'i.q23_smell_objects',
                'i.q23_smell_objects_change',
                'i.q24_interested_smell',
                'i.q24_interested_smell_change',
                'i.q25_put_objects',
                'i.q25_put_objects_change',
                'i.q26_enjoy_riding',
                'i.q26_enjoy_riding_change',
                'i.q27_like_jump',
                'i.q27_like_jump_change',
                'i.q28_seek_physical',
                'i.q28_seek_physical_change',
                'i.q29_uneasy_dizzy',
                'i.q29_uneasy_dizzy_change',
                'i.q30_flap_arms',
                'i.q30_flap_arms_change',
                'i.q36_a_sounds',
                'i.q36_b_lights',
                'i.q36_c_smells',
                'i.q36_d_tastes',
                'i.q36_e_textures',
                'i.q36_f_touch',
                'i.q38_pick_eater',
                'i.q38_selective',
                'i.q41_a_sounds',
                'i.q41_b_lights',
                'i.q41_c_smells',
                'i.q41_d_tastes',
                'i.q41_e_textures',
                'i.q41_f_touch',
                'i.q42_sensory_change',
            );
        } else if ($this->instrument == 'm_chat_proband') {
            $fields = array(
                'i.total_item_fails',
                'i.total_critical_fails',
                'i.score',
                'i.q1_swung_on_knee',
                'i.q2_interest_other_children',
                'i.q3_climbing',
                'i.q4_peek_a_boo',
                'i.q5_pretends',
                'i.q6_index_point',
                'i.q7_index_interest',
                'i.q8_play_properly',
                'i.q9_bring_objects',
                'i.q10_look_eye',
                'i.q11_oversensitive',
                'i.q12_smile_to_face',
                'i.q13_imitate_you',
                'i.q14_respond_to_name',
                'i.q15_point_and_look',
                'i.q16_walk',
                'i.q17_look_at_similar',
                'i.q18_unusual_finger',
                'i.q19_try_to_attract',
                'i.q20_wondered_deaf',
                'i.q21_understand_speach',
                'i.q22_stare_no_purpose',
                'i.q23_look_at_face'
            );
        } else if ($this->instrument == 'mullen') {
            $fields = array('i.other_comments',
                'i.expressive_lang_1',
                'i.expressive_lang_2',
                'i.expressive_lang_3',
                'i.expressive_lang_4',
                'i.expressive_lang_5',
                'i.expressive_lang_6',
                'i.expressive_lang_7',
                'i.expressive_lang_8',
                'i.expressive_lang_9',
                'i.expressive_lang_10',
                'i.expressive_lang_11',
                'i.expressive_lang_12',
                'i.expressive_lang_13',
                'i.expressive_lang_14',
                'i.expressive_lang_15',
                'i.expressive_lang_16',
                'i.expressive_lang_17',
                'i.expressive_lang_18',
                'i.expressive_lang_19',
                'i.expressive_lang_20',
                'i.expressive_lang_21',
                'i.expressive_lang_22',
                'i.expressive_lang_23',
                'i.expressive_lang_24',
                'i.expressive_lang_25',
                'i.expressive_lang_26',
                'i.expressive_lang_27',
                'i.expressive_lang_28',
                'i.expressive_language_raw',
                'i.expressive_language_t',
                'i.expressive_language_percentile',
                'i.expressive_language_description',
                'i.expressive_language_age_equivalent',
                'i.cognitive_t_score_sum',
                'i.composite_standard_score',
                'i.composite_percentile',
                'i.composite_description',
                'i.gross_motor_1',
                'i.gross_motor_2',
                'i.gross_motor_3',
                'i.gross_motor_4',
                'i.gross_motor_5',
                'i.gross_motor_6',
                'i.gross_motor_7',
                'i.gross_motor_8',
                'i.gross_motor_9',
                'i.gross_motor_10',
                'i.gross_motor_11',
                'i.gross_motor_12',
                'i.gross_motor_13',
                'i.gross_motor_14',
                'i.gross_motor_15',
                'i.gross_motor_16',
                'i.gross_motor_17',
                'i.gross_motor_18',
                'i.gross_motor_19',
                'i.gross_motor_20',
                'i.gross_motor_21',
                'i.gross_motor_22',
                'i.gross_motor_23',
                'i.gross_motor_24',
                'i.gross_motor_25',
                'i.gross_motor_26',
                'i.gross_motor_27',
                'i.gross_motor_28',
                'i.gross_motor_29',
                'i.gross_motor_30',
                'i.gross_motor_31',
                'i.gross_motor_32',
                'i.gross_motor_33',
                'i.gross_motor_34',
                'i.gross_motor_35',
                'i.gross_motor_raw',
                'i.gross_motor_t',
                'i.gross_motor_percentile',
                'i.gross_motor_description',
                'i.gross_motor_age_equivalent',
                'i.visual_recept_1',
                'i.visual_recept_2',
                'i.visual_recept_3',
                'i.visual_recept_4',
                'i.visual_recept_5',
                'i.visual_recept_6',
                'i.visual_recept_7',
                'i.visual_recept_8',
                'i.visual_recept_9',
                'i.visual_recept_10',
                'i.visual_recept_11',
                'i.visual_recept_12',
                'i.visual_recept_13',
                'i.visual_recept_14',
                'i.visual_recept_15',
                'i.visual_recept_16',
                'i.visual_recept_17',
                'i.visual_recept_18',
                'i.visual_recept_19',
                'i.visual_recept_20',
                'i.visual_recept_21',
                'i.visual_recept_22',
                'i.visual_recept_23',
                'i.visual_recept_24',
                'i.visual_recept_25',
                'i.visual_recept_26',
                'i.visual_recept_27',
                'i.visual_recept_28',
                'i.visual_recept_29',
                'i.visual_recept_30',
                'i.visual_recept_31',
                'i.visual_recept_32',
                'i.visual_recept_33',
                'i.visual_reception_raw',
                'i.visual_reception_t',
                'i.visual_reception_percentile',
                'i.visual_reception_description',
                'i.visual_reception_age_equivalent',
                'i.fine_motor_1',
                'i.fine_motor_2',
                'i.fine_motor_3',
                'i.fine_motor_4',
                'i.fine_motor_5',
                'i.fine_motor_6',
                'i.fine_motor_7',
                'i.fine_motor_8',
                'i.fine_motor_9',
                'i.fine_motor_10',
                'i.fine_motor_11',
                'i.fine_motor_12',
                'i.fine_motor_13',
                'i.fine_motor_14',
                'i.fine_motor_15',
                'i.fine_motor_16',
                'i.fine_motor_17',
                'i.fine_motor_18',
                'i.fine_motor_19',
                'i.fine_motor_20',
                'i.fine_motor_21',
                'i.fine_motor_22',
                'i.fine_motor_23',
                'i.fine_motor_24',
                'i.fine_motor_25',
                'i.fine_motor_26',
                'i.fine_motor_27',
                'i.fine_motor_28',
                'i.fine_motor_29',
                'i.fine_motor_30',
                'i.fine_motor_raw',
                'i.fine_motor_t',
                'i.fine_motor_percentile',
                'i.fine_motor_description',
                'i.fine_motor_age_equivalent',
                'i.receptive_lang_1',
                'i.receptive_lang_2',
                'i.receptive_lang_3',
                'i.receptive_lang_4',
                'i.receptive_lang_5',
                'i.receptive_lang_6',
                'i.receptive_lang_7',
                'i.receptive_lang_8',
                'i.receptive_lang_9',
                'i.receptive_lang_10',
                'i.receptive_lang_11',
                'i.receptive_lang_12',
                'i.receptive_lang_13',
                'i.receptive_lang_14',
                'i.receptive_lang_15',
                'i.receptive_lang_16',
                'i.receptive_lang_17',
                'i.receptive_lang_18',
                'i.receptive_lang_19',
                'i.receptive_lang_20',
                'i.receptive_lang_21',
                'i.receptive_lang_22',
                'i.receptive_lang_23',
                'i.receptive_lang_24',
                'i.receptive_lang_25',
                'i.receptive_lang_26',
                'i.receptive_lang_27',
                'i.receptive_lang_28',
                'i.receptive_lang_29',
                'i.receptive_lang_30',
                'i.receptive_lang_31',
                'i.receptive_lang_32',
                'i.receptive_lang_33',
                'i.receptive_language_raw',
                'i.receptive_language_t',
                'i.receptive_language_percentile',
                'i.receptive_language_description',
                'i.receptive_language_age_equivalent'
            );
        } else if ($this->instrument == 'scq_proband' || $this->instrument == 'scq_subject') {
            $fields = array('i.score', 'i.q1_talk_short_phrases', 'i.q2_to_and_fro', 'i.q3_odd_phrases', 'i.q4_socially_inappropriate', 'i.q5_pronouns_mixed', 'i.q6_words_invented', 'i.q7_said_same_thing', 'i.q8_particular_way', 'i.q9_facial_expressions', 'i.q10_hand_like_tool', 'i.q11_interests_that_preoccupy', 'i.q12_interested_in_parts', 'i.q13_intense_interests', 'i.q14_sight_feel_sound', 'i.q15_mannerisms', 'i.q16_complicated_movements', 'i.q17_deliberate_injury', 'i.q18_carry_objects', 'i.q19_particular_friends', 'i.q20_talk_friendly', 'i.q21_spontaneously_copy', 'i.q22_spontaneously_point', 'i.q23_gestures', 'i.q24_nod_yes', 'i.q25_shake_no', 'i.q26_look_directly', 'i.q27_smile_back', 'i.q28_show_things', 'i.q29_offer_share', 'i.q30_join_enjoyment', 'i.q31_comfort', 'i.q32_wanted_something', 'i.q33_facial_expressions', 'i.q34_spontaneously_join', 'i.q35_play_pretend', 'i.q36_seem_interested', 'i.q37_respond_positively', 'i.q38_came_into_room', 'i.q39_play_imaginative', 'i.q40_play_cooperatively');
        } else if ($this->instrument == 'vineland_subject' || $this->instrument == 'vineland_proband') {
            $fields = array(
                'i.CommentID',
                'i.RELATIONSHIP as relationship',
                'i.`ABC_%ILE_RANK` as ABC_PERCENTILE_RANK',
                'i.`ABC_95%_CI` as ABC_95PERCENT_CI',
                'i.ABC_ADAPT_LEVEL',
                'i.ABC_STANINE',
                'i.ABC_STD_SCORE',
                'i.ABC_SUM_ALL_DOM_STD_SCORES',
                'i.`CMM_95%_CI` AS CMM_95PERCENT_CI',
                'i.CMM_ADAPT_LEVEL',
                'i.CMM_AGE_EQUIV',
                'i.CMM_RAW',
                'i.CMM_SW',
                'i.CMM_VSCALE',
                'i.`COM_%ILE_RANK` as COM_PERCENTILE_RANK',
                'i.`COM_95%_CI` as COM_95PERCENT_CI',
                'i.COM_ADAPT_LEVEL',
                'i.COM_STANINE',
                'i.COM_STD_SCORE',
                'i.COM_SUM_VSCALES_FOR_DOMAIN',
                'i.COM_SW',
                'i.`CS_95%_CI` as CS_95PERCENT_CI',
                'i.CRIT_ITEM_1',
                'i.CRIT_ITEM_2',
                'i.CRIT_ITEM_3',
                'i.CRIT_ITEM_4',
                'i.CRIT_ITEM_5',
                'i.CRIT_ITEM_6',
                'i.CRIT_ITEM_7',
                'i.CRIT_ITEM_8',
                'i.CRIT_ITEM_9',
                'i.CRIT_ITEM_10',
                'i.CRIT_ITEM_11',
                'i.CRIT_ITEM_12',
                'i.CRIT_ITEM_13',
                'i.CRIT_ITEM_14',
                'i.CRIT_SEVERITY_ITEM_10',
                'i.CRIT_SEVERITY_ITEM_11',
                'i.CRIT_SEVERITY_ITEM_12',
                'i.CRIT_SEVERITY_ITEM_13',
                'i.CRIT_SEVERITY_ITEM_14',
                'i.CS_ADAPT_LEVEL',
                'i.CS_AGE_EQUIV',
                'i.CS_RAW',
                'i.CS_SW',
                'i.CS_VSCALE',
                'i.`DLS_%ILE_RANK` as DLS_PERCENTILE_RANK',
                'i.`DLS_95%_CI` as DLS_95PERCENT_CI',
                'i.DLS_ADAPT_LEVEL',
                'i.DLS_STANINE',
                'i.DLS_STD_SCORE',
                'i.DLS_SUM_VSCALES_FOR_DOMAIN',
                'i.DLS_SW',
                'i.`DOM_95%_CI` as DOM_95PERCENT_CI',
                'i.DOM_ADAPT_LEVEL',
                'i.DOM_AGE_EQUIV',
                'i.DOM_RAW',
                'i.DOM_SW',
                'i.DOM_VSCALE',
                'i.`EXP_95%_CI` AS EXP_95PERCENT_CI',
                'i.EXP_ADAPT_LEVEL',
                'i.EXP_AGE_EQUIV',
                'i.EXP_RAW',
                'i.EXP_SW',
                'i.EXP_VSCALE',
                'i.`EXT_95%_CI` AS EXT_95PERCENT_CI',
                'i.EXT_ADAPT_LEVEL',
                'i.EXT_RAW',
                'i.EXT_VSCALE',
                'i.`FMS_95%_CI` AS FMS_95PERCENT_CI',
                'i.FMS_ADAPT_LEVEL',
                'i.FMS_AGE_EQUIV',
                'i.FMS_RAW',
                'i.FMS_SW',
                'i.FMS_VSCALE',
                'i.`GMS_95%_CI` as GMS_95PERCENT_CI',
                'i.GMS_ADAPT_LEVEL',
                'i.GMS_AGE_EQUIV',
                'i.GMS_RAW',
                'i.GMS_SW',
                'i.GMS_VSCALE',
                'i.GRADE',
                'i.`INT_95%_CI` AS INT_95PERCENT_CI',
                'i.INT_ADAPT_LEVEL',
                'i.INT_RAW',
                'i.INT_VSCALE',
                'i.`IPR_95%_CI` AS IPR_95PERCENT_CI',
                'i.IPR_ADAPT_LEVEL',
                'i.IPR_AGE_EQUIV',
                'i.IPR_RAW',
                'i.IPR_SW',
                'i.IPR_VSCALE',
                'i.`MBI_95%_CI` AS MBI_95PERCENT_CI',
                'i.MBI_ADAPT_LEVEL',
                'i.MBI_RAW',
                'i.MBI_VSCALE',
                'i.`MS_%ILE_RANK` AS MS_PERCENTILE_RANK',
                'i.`MS_95%_CI` AS MS_95PERCENT_CI',
                'i.MS_ADAPT_LEVEL',
                'i.MS_STANINE',
                'i.MS_STD_SCORE',
                'i.MS_SUM_VSCALES_FOR_DOMAIN',
                'i.MS_SW',
                'i.`OTH_95%_CI` AS OTH_95PERCENT_CI',
                'i.OTH_ADAPT_LEVEL',
                'i.OTH_RAW',
                'i.OTH_STATUS',
                'i.OTH_VSCALE',
                'i.`PER_95%_CI` AS PER_95PERCENT_CI',
                'i.PER_ADAPT_LEVEL',
                'i.PER_AGE_EQUIV',
                'i.PER_RAW',
                'i.PER_SW',
                'i.PER_VSCALE',
                'i.`PL_95%_CI` AS PL_95PERCENT_CI',
                'i.PL_ADAPT_LEVEL',
                'i.PL_AGE_EQUIV',
                'i.PL_RAW',
                'i.PL_SW',
                'i.PL_VSCALE',
                'i.`REC_95%_CI` AS REC_95PERCENT_CI',
                'i.REC_ADAPT_LEVEL',
                'i.REC_AGE_EQUIV',
                'i.REC_RAW',
                'i.REC_SW',
                'i.REC_VSCALE',
                'i.`SOC_%ILE_RANK` AS SOC_PERCENTILE_RANK',
                'i.`SOC_95%_CI` as SOC_95PERCENT_CI',
                'i.SOC_ADAPT_LEVEL',
                'i.SOC_STANINE',
                'i.SOC_STD_SCORE',
                'i.SOC_SUM_VSCALES_FOR_DOMAIN',
                'i.SOC_SW',
                'i.`WRN_95%_CI` AS WRN_95PERCENT_CI',
                'i.WRN_ADAPT_LEVEL',
                'i.WRN_AGE_EQUIV',
                'i.WRN_RAW',
                'i.WRN_SW',
                'i.WRN_VSCALE');
        } else if ($this->instrument == 'rbs_r') {
            $fields = array('i.Date_taken as interview_date', 'i.respondent', 'i.I_stereotyped_endorsed', 'i.I_stereotyped_score', 'i.II_self_injurious_endorsed', 'i.II_self_injurious_score', 'i.III_compulsive_endorsed', 'i.III_compulsive_score', 'i.IV_ritualistic_endorsed', 'i.IV_ritualistic_score', 'i.overall_endorsed', 'i.overall_score', 'i.q1_whole_body', 'i.q10_bites_self', 'i.q11_pulls', 'i.q12_rubs_or_scratches', 'i.q13_inserts_finger_or_object', 'i.q14_skin_picking', 'i.q15_arranging_ordering', 'i.q16_completeness', 'i.q17_washing_cleaning', 'i.q18_checking', 'i.q19_counting', 'i.q2_head', 'i.q20_hoarding_saving', 'i.q21_repeating', 'i.q22_touch_tap', 'i.q23_eating_mealtime', 'i.q24_sleeping_bedtime', 'i.q25_self_care', 'i.q26_travel_transportation', 'i.q27_play_leisure', 'i.q28_communication', 'i.q29_insists_things_remain', 'i.q3_hand_finger', 'i.q30_objects_to_visiting', 'i.q31_upset_if_interrupted', 'i.q32_walking_in_a_pattern', 'i.q33_insists_on_sitting_at_same_place', 'i.q34_dislikes_change', 'i.q35_insists_on_particular_door', 'i.q36_likes_same_cd', 'i.q37_resists_changing_activities', 'i.q38_insists_on_same_routine', 'i.q39_insists_that_specific', 'i.q4_locomotion', 'i.q40_fascination_preoccupation', 'i.q41_strongly_attached', 'i.q42_preoccupation_with_parts', 'i.q43_fascination_with_movement', 'i.q5_object_usage', 'i.q6_sensory', 'i.q7_hits_self_body_part', 'i.q8_hits_self_against_surface', 'i.q9_hits_self_with_object', 'i.V_sameness_endorsed', 'i.V_sameness_score', 'i.VI_restricted_endorsed', 'i.VI_restricted_score');
        } else if ($this->instrument == 'macarthur_words_gestures') {
            $fields = array('i.early_gestures_number',
                // 'i.early_gestures_percentile',
                'i.I_A_1',
                'i.I_A_2',
                // 'i.I_A_3',
                'i.I_B_1',
                'i.I_B_10',
                'i.I_B_11',
                'i.I_B_12',
                'i.I_B_13',
                'i.I_B_14',
                'i.I_B_15',
                'i.I_B_16',
                'i.I_B_17',
                'i.I_B_18',
                'i.I_B_19',
                'i.I_B_2',
                'i.I_B_20',
                'i.I_B_21',
                'i.I_B_22',
                'i.I_B_23',
                'i.I_B_24',
                'i.I_B_25',
                'i.I_B_26',
                'i.I_B_27',
                'i.I_B_28',
                'i.I_B_3',
                'i.I_B_4',
                'i.I_B_5',
                'i.I_B_6',
                'i.I_B_7',
                'i.I_B_8',
                'i.I_B_9',
                'i.I_C_1',
                'i.I_C_2',
                'i.I_D_1_1',
                'i.I_D_1_10',
                'i.I_D_1_11',
                'i.I_D_1_12',
                'i.I_D_1_2',
                'i.I_D_1_3',
                'i.I_D_1_4',
                'i.I_D_1_5',
                'i.I_D_1_6',
                'i.I_D_1_7',
                'i.I_D_1_8',
                'i.I_D_1_9',
                'i.I_D_10_1',
                'i.I_D_10_10',
                'i.I_D_10_11',
                'i.I_D_10_12',
                'i.I_D_10_13',
                'i.I_D_10_14',
                'i.I_D_10_15',
                'i.I_D_10_16',
                'i.I_D_10_17',
                'i.I_D_10_18',
                'i.I_D_10_19',
                'i.I_D_10_2',
                'i.I_D_10_20',
                'i.I_D_10_21',
                'i.I_D_10_22',
                'i.I_D_10_23',
                'i.I_D_10_24',
                'i.I_D_10_25',
                'i.I_D_10_26',
                'i.I_D_10_27',
                'i.I_D_10_3',
                'i.I_D_10_4',
                'i.I_D_10_5',
                'i.I_D_10_6',
                'i.I_D_10_7',
                'i.I_D_10_8',
                'i.I_D_10_9',
                'i.I_D_11_1',
                'i.I_D_11_10',
                'i.I_D_11_11',
                'i.I_D_11_12',
                'i.I_D_11_13',
                'i.I_D_11_14',
                'i.I_D_11_15',
                'i.I_D_11_16',
                'i.I_D_11_17',
                'i.I_D_11_18',
                'i.I_D_11_19',
                'i.I_D_11_2',
                'i.I_D_11_20',
                'i.I_D_11_3',
                'i.I_D_11_4',
                'i.I_D_11_5',
                'i.I_D_11_6',
                'i.I_D_11_7',
                'i.I_D_11_8',
                'i.I_D_11_9',
                'i.I_D_12_1',
                'i.I_D_12_10',
                'i.I_D_12_11',
                'i.I_D_12_12',
                'i.I_D_12_13',
                'i.I_D_12_14',
                'i.I_D_12_15',
                'i.I_D_12_16',
                'i.I_D_12_17',
                'i.I_D_12_18',
                'i.I_D_12_19',
                'i.I_D_12_2',
                'i.I_D_12_3',
                'i.I_D_12_4',
                'i.I_D_12_5',
                'i.I_D_12_6',
                'i.I_D_12_7',
                'i.I_D_12_8',
                'i.I_D_12_9',
                'i.I_D_13_1',
                'i.I_D_13_10',
                'i.I_D_13_11',
                'i.I_D_13_12',
                'i.I_D_13_13',
                'i.I_D_13_14',
                'i.I_D_13_15',
                'i.I_D_13_16',
                'i.I_D_13_17',
                'i.I_D_13_18',
                'i.I_D_13_19',
                'i.I_D_13_2',
                'i.I_D_13_20',
                'i.I_D_13_21',
                'i.I_D_13_22',
                'i.I_D_13_23',
                'i.I_D_13_24',
                'i.I_D_13_25',
                'i.I_D_13_26',
                'i.I_D_13_27',
                'i.I_D_13_28',
                'i.I_D_13_29',
                'i.I_D_13_3',
                'i.I_D_13_30',
                'i.I_D_13_31',
                'i.I_D_13_32',
                'i.I_D_13_33',
                'i.I_D_13_34',
                'i.I_D_13_35',
                'i.I_D_13_36',
                'i.I_D_13_37',
                'i.I_D_13_38',
                'i.I_D_13_39',
                'i.I_D_13_4',
                'i.I_D_13_40',
                'i.I_D_13_41',
                'i.I_D_13_42',
                'i.I_D_13_43',
                'i.I_D_13_44',
                'i.I_D_13_45',
                'i.I_D_13_46',
                'i.I_D_13_47',
                'i.I_D_13_48',
                'i.I_D_13_49',
                'i.I_D_13_5',
                'i.I_D_13_50',
                'i.I_D_13_51',
                'i.I_D_13_52',
                'i.I_D_13_53',
                'i.I_D_13_54',
                'i.I_D_13_55',
                'i.I_D_13_6',
                'i.I_D_13_7',
                'i.I_D_13_8',
                'i.I_D_13_9',
                'i.I_D_14_1',
                'i.I_D_14_2',
                'i.I_D_14_3',
                'i.I_D_14_4',
                'i.I_D_14_5',
                'i.I_D_14_6',
                'i.I_D_14_7',
                'i.I_D_14_8',
                'i.I_D_15_1',
                'i.I_D_15_10',
                'i.I_D_15_11',
                'i.I_D_15_12',
                'i.I_D_15_13',
                'i.I_D_15_14',
                'i.I_D_15_15',
                'i.I_D_15_16',
                'i.I_D_15_17',
                'i.I_D_15_18',
                'i.I_D_15_19',
                'i.I_D_15_2',
                'i.I_D_15_20',
                'i.I_D_15_21',
                'i.I_D_15_22',
                'i.I_D_15_23',
                'i.I_D_15_24',
                'i.I_D_15_25',
                'i.I_D_15_26',
                'i.I_D_15_27',
                'i.I_D_15_28',
                'i.I_D_15_29',
                'i.I_D_15_3',
                'i.I_D_15_30',
                'i.I_D_15_31',
                'i.I_D_15_32',
                'i.I_D_15_33',
                'i.I_D_15_34',
                'i.I_D_15_35',
                'i.I_D_15_36',
                'i.I_D_15_37',
                'i.I_D_15_4',
                'i.I_D_15_5',
                'i.I_D_15_6',
                'i.I_D_15_7',
                'i.I_D_15_8',
                'i.I_D_15_9',
                'i.I_D_16_1',
                'i.I_D_16_10',
                'i.I_D_16_11',
                'i.I_D_16_2',
                'i.I_D_16_3',
                'i.I_D_16_4',
                'i.I_D_16_5',
                'i.I_D_16_6',
                'i.I_D_16_7',
                'i.I_D_16_8',
                'i.I_D_16_9',
                'i.I_D_17_1',
                'i.I_D_17_2',
                'i.I_D_17_3',
                'i.I_D_17_4',
                'i.I_D_17_5',
                'i.I_D_17_6',
                'i.I_D_18_1',
                'i.I_D_18_10',
                'i.I_D_18_11',
                'i.I_D_18_2',
                'i.I_D_18_3',
                'i.I_D_18_4',
                'i.I_D_18_5',
                'i.I_D_18_6',
                'i.I_D_18_7',
                'i.I_D_18_8',
                'i.I_D_18_9',
                'i.I_D_19_1',
                'i.I_D_19_2',
                'i.I_D_19_3',
                'i.I_D_19_4',
                'i.I_D_19_5',
                'i.I_D_19_6',
                'i.I_D_19_7',
                'i.I_D_19_8',
                'i.I_D_2_1',
                'i.I_D_2_10',
                'i.I_D_2_11',
                'i.I_D_2_12',
                'i.I_D_2_13',
                'i.I_D_2_14',
                'i.I_D_2_15',
                'i.I_D_2_16',
                'i.I_D_2_17',
                'i.I_D_2_18',
                'i.I_D_2_19',
                'i.I_D_2_2',
                'i.I_D_2_20',
                'i.I_D_2_21',
                'i.I_D_2_22',
                'i.I_D_2_23',
                'i.I_D_2_24',
                'i.I_D_2_25',
                'i.I_D_2_26',
                'i.I_D_2_27',
                'i.I_D_2_28',
                'i.I_D_2_29',
                'i.I_D_2_3',
                'i.I_D_2_30',
                'i.I_D_2_31',
                'i.I_D_2_32',
                'i.I_D_2_33',
                'i.I_D_2_34',
                'i.I_D_2_35',
                'i.I_D_2_36',
                'i.I_D_2_4',
                'i.I_D_2_5',
                'i.I_D_2_6',
                'i.I_D_2_7',
                'i.I_D_2_8',
                'i.I_D_2_9',
                'i.I_D_3_1',
                'i.I_D_3_2',
                'i.I_D_3_3',
                'i.I_D_3_4',
                'i.I_D_3_5',
                'i.I_D_3_6',
                'i.I_D_3_7',
                'i.I_D_3_8',
                'i.I_D_3_9',
                'i.I_D_4_1',
                'i.I_D_4_2',
                'i.I_D_4_3',
                'i.I_D_4_4',
                'i.I_D_4_5',
                'i.I_D_4_6',
                'i.I_D_4_7',
                'i.I_D_4_8',
                'i.I_D_5_1',
                'i.I_D_5_10',
                'i.I_D_5_11',
                'i.I_D_5_12',
                'i.I_D_5_13',
                'i.I_D_5_14',
                'i.I_D_5_15',
                'i.I_D_5_16',
                'i.I_D_5_17',
                'i.I_D_5_18',
                'i.I_D_5_19',
                'i.I_D_5_2',
                'i.I_D_5_20',
                'i.I_D_5_21',
                'i.I_D_5_22',
                'i.I_D_5_23',
                'i.I_D_5_24',
                'i.I_D_5_25',
                'i.I_D_5_26',
                'i.I_D_5_27',
                'i.I_D_5_28',
                'i.I_D_5_29',
                'i.I_D_5_3',
                'i.I_D_5_30',
                'i.I_D_5_4',
                'i.I_D_5_5',
                'i.I_D_5_6',
                'i.I_D_5_7',
                'i.I_D_5_8',
                'i.I_D_5_9',
                'i.I_D_6_1',
                'i.I_D_6_10',
                'i.I_D_6_11',
                'i.I_D_6_12',
                'i.I_D_6_13',
                'i.I_D_6_14',
                'i.I_D_6_15',
                'i.I_D_6_16',
                'i.I_D_6_17',
                'i.I_D_6_18',
                'i.I_D_6_19',
                'i.I_D_6_2',
                'i.I_D_6_3',
                'i.I_D_6_4',
                'i.I_D_6_5',
                'i.I_D_6_6',
                'i.I_D_6_7',
                'i.I_D_6_8',
                'i.I_D_6_9',
                'i.I_D_7_1',
                'i.I_D_7_10',
                'i.I_D_7_11',
                'i.I_D_7_12',
                'i.I_D_7_13',
                'i.I_D_7_14',
                'i.I_D_7_15',
                'i.I_D_7_16',
                'i.I_D_7_17',
                'i.I_D_7_18',
                'i.I_D_7_19',
                'i.I_D_7_2',
                'i.I_D_7_20',
                'i.I_D_7_3',
                'i.I_D_7_4',
                'i.I_D_7_5',
                'i.I_D_7_6',
                'i.I_D_7_7',
                'i.I_D_7_8',
                'i.I_D_7_9',
                'i.I_D_8_1',
                'i.I_D_8_10',
                'i.I_D_8_11',
                'i.I_D_8_12',
                'i.I_D_8_13',
                'i.I_D_8_14',
                'i.I_D_8_15',
                'i.I_D_8_16',
                'i.I_D_8_17',
                'i.I_D_8_18',
                'i.I_D_8_19',
                'i.I_D_8_2',
                'i.I_D_8_20',
                'i.I_D_8_21',
                'i.I_D_8_22',
                'i.I_D_8_23',
                'i.I_D_8_24',
                'i.I_D_8_3',
                'i.I_D_8_4',
                'i.I_D_8_5',
                'i.I_D_8_6',
                'i.I_D_8_7',
                'i.I_D_8_8',
                'i.I_D_8_9',
                'i.I_D_9_1',
                'i.I_D_9_10',
                'i.I_D_9_11',
                'i.I_D_9_12',
                'i.I_D_9_13',
                'i.I_D_9_14',
                'i.I_D_9_15',
                'i.I_D_9_16',
                'i.I_D_9_17',
                'i.I_D_9_18',
                'i.I_D_9_19',
                'i.I_D_9_2',
                'i.I_D_9_20',
                'i.I_D_9_21',
                'i.I_D_9_22',
                'i.I_D_9_23',
                'i.I_D_9_24',
                'i.I_D_9_25',
                'i.I_D_9_26',
                'i.I_D_9_27',
                'i.I_D_9_28',
                'i.I_D_9_29',
                'i.I_D_9_3',
                'i.I_D_9_30',
                'i.I_D_9_31',
                'i.I_D_9_32',
                'i.I_D_9_33',
                'i.I_D_9_34',
                'i.I_D_9_35',
                'i.I_D_9_36',
                'i.I_D_9_4',
                'i.I_D_9_5',
                'i.I_D_9_6',
                'i.I_D_9_7',
                'i.I_D_9_8',
                'i.I_D_9_9',
                'i.II_A_1',
                'i.II_A_10',
                'i.II_A_11',
                'i.II_A_12',
                'i.II_A_2',
                'i.II_A_3',
                'i.II_A_4',
                'i.II_A_5',
                'i.II_A_6',
                'i.II_A_7',
                'i.II_A_8',
                'i.II_A_9',
                'i.II_B_1',
                'i.II_B_2',
                'i.II_B_3',
                'i.II_B_4',
                'i.II_B_5',
                'i.II_B_6',
                'i.II_C_1',
                'i.II_C_10',
                'i.II_C_11',
                'i.II_C_12',
                'i.II_C_13',
                'i.II_C_14',
                'i.II_C_15',
                'i.II_C_16',
                'i.II_C_17',
                'i.II_C_2',
                'i.II_C_3',
                'i.II_C_4',
                'i.II_C_5',
                'i.II_C_6',
                'i.II_C_7',
                'i.II_C_8',
                'i.II_C_9',
                'i.II_D_1',
                'i.II_D_10',
                'i.II_D_11',
                'i.II_D_12',
                'i.II_D_13',
                'i.II_D_2',
                'i.II_D_3',
                'i.II_D_4',
                'i.II_D_5',
                'i.II_D_6',
                'i.II_D_7',
                'i.II_D_8',
                'i.II_D_9',
                'i.II_E_1',
                'i.II_E_10',
                'i.II_E_11',
                'i.II_E_12',
                'i.II_E_13',
                'i.II_E_14',
                'i.II_E_15',
                'i.II_E_2',
                'i.II_E_3',
                'i.II_E_4',
                'i.II_E_5',
                'i.II_E_6',
                'i.II_E_7',
                'i.II_E_8',
                'i.II_E_9',
                'i.later_gestures_number',
                // 'i.later_gestures_percentile',
                'i.phrases_understood_number',
                // 'i.phrases_understood_percentile',
                'i.words_produced_number',
                // 'i.words_produced_percentile',
                'i.words_understood_number',
                // 'i.words_understood_percentile',
                'i.total_gestures_number'
                // 'i.total_gestures_percentile'
            );
        } else if ($this->instrument == 'csbs') {
            $fields = array('i.object_use_weighted',
                'i.relationship_to_child',
                'i.q_1_alertness',
                'i.q_2_emotional_reaction',
                'i.q_3_level_of_interest',
                'i.q_4_comfort_level',
                'i.q_5_level_of_activity',
                'i.q_6_level_of_communication',
                'i.q_7_play_behaviour',
                'i.emotion_eye_gaze_standard',
                'i.emotion_eye_gaze_percentile',
                'i.communication_standard',
                'i.communication_percentile',
                'i.gestures_standard',
                'i.gestures_percentile',
                'i.sounds_standard',
                'i.sounds_percentile',
                'i.words_standard',
                'i.words_percentile',
                'i.understanding_standard',
                'i.understanding_percentile',
                'i.object_use_standard',
                'i.object_use_percentile',
                'i.social_composite_score',
                'i.social_composite_standard',
                'i.social_composite_percentile',
                'i.speech_composite_score',
                'i.speech_composite_standard',
                'i.speech_composite_percentile',
                'i.symbolic_composite_score',
                'i.symbolic_composite_standard',
                'i.symbolic_composite_percentile',
                'i.total_weighted_raw_score',
                'i.total_standard',
                'i.total_percentile',
                'i.q_1_gaze_shifts_1',
                'i.q_1_gaze_shifts_2',
                'i.q_1_gaze_shifts_3',
                'i.q_1_gaze_shifts_4',
                'i.q_1_gaze_shifts_5',
                'i.q_1_gaze_shifts_6',
                'i.q_1_gaze_shifts_raw_score',
                'i.q_2_shared_positive_affect_1',
                'i.q_2_shared_positive_affect_2',
                'i.q_2_shared_positive_affect_3',
                'i.q_2_shared_positive_affect_4',
                'i.q_2_shared_positive_affect_5',
                'i.q_2_shared_positive_affect_6',
                'i.q_2_shared_positive_affect_raw_score',
                'i.q_3_gaze_point_following_2',
                'i.q_3_gaze_point_following_5',
                'i.q_3_gaze_point_following_raw_score',
                'i.emotion_eye_gaze_weighted',
                'i.q_4_rate_of_communicating_1',
                'i.q_4_rate_of_communicating_2',
                'i.q_4_rate_of_communicating_3',
                'i.q_4_rate_of_communicating_4',
                'i.q_4_rate_of_communicating_5',
                'i.q_4_rate_of_communicating_6',
                'i.q_4_rate_of_communicating_raw_score',
                'i.q_5_behaviour_regulation_1',
                'i.q_5_behaviour_regulation_2',
                'i.q_5_behaviour_regulation_3',
                'i.q_5_behaviour_regulation_4',
                'i.q_5_behaviour_regulation_5',
                'i.q_5_behaviour_regulation_6',
                'i.q_5_behaviour_regulation_raw_score',
                'i.q_6_social_interaction_1',
                'i.q_6_social_interaction_2',
                'i.q_6_social_interaction_3',
                'i.q_6_social_interaction_4',
                'i.q_6_social_interaction_5',
                'i.q_6_social_interaction_6',
                'i.q_6_social_interaction_raw_score',
                'i.q_7_joint_attention_1',
                'i.q_7_joint_attention_2',
                'i.q_7_joint_attention_3',
                'i.q_7_joint_attention_4',
                'i.q_7_joint_attention_5',
                'i.q_7_joint_attention_6',
                'i.q_7_joint_attention_raw_score',
                'i.communication_weighted',
                'i.q_8_conventional_gestures_gives',
                'i.q_8_conventional_gestures_shows',
                'i.q_8_conventional_gestures_pushes_pulls',
                'i.q_8_conventional_gestures_reaches',
                'i.q_8_conventional_gestures_raw_score',
                'i.q_8_conventional_gestures_points',
                'i.q_8_conventional_gestures_waves',
                'i.q_8_conventional_gestures_nods_head',
                'i.q_8_conventional_gestures_shakes_head',
                'i.q_9_distal_gestures_1',
                'i.q_9_distal_gestures_2',
                'i.q_9_distal_gestures_3',
                'i.q_9_distal_gestures_4',
                'i.q_9_distal_gestures_5',
                'i.q_9_distal_gestures_6',
                'i.q_9_distal_gestures_raw_score',
                'i.gestures_weighted',
                'i.q_10_syllables_consonants_1',
                'i.q_10_syllables_consonants_2',
                'i.q_10_syllables_consonants_3',
                'i.q_10_syllables_consonants_4',
                'i.q_10_syllables_consonants_5',
                'i.q_10_syllables_consonants_6',
                'i.q_10_syllables_consonants_raw_score',
                'i.q_11_inventory_of_consonants_m',
                'i.q_11_inventory_of_consonants_n',
                'i.q_11_inventory_of_consonants_b_p',
                'i.q_11_inventory_of_consonants_d_t',
                'i.q_11_inventory_of_consonants_g_k',
                'i.q_11_inventory_of_consonants_raw_score',
                'i.q_11_inventory_of_consonants_w',
                'i.q_11_inventory_of_consonants_l',
                'i.q_11_inventory_of_consonants_y',
                'i.q_11_inventory_of_consonants_s',
                'i.q_11_inventory_of_consonants_sh',
                'i.sounds_weighted',
                'i.q_12_words_1',
                'i.q_12_words_2',
                'i.q_12_words_3',
                'i.q_12_words_4',
                'i.q_12_words_5',
                'i.q_12_words_6',
                'i.q_12_words_raw_score',
                'i.q_13_words_1',
                'i.q_13_words_2',
                'i.q_13_words_3',
                'i.q_13_words_4',
                'i.q_13_words_raw_score',
                'i.q_13_words_5',
                'i.q_13_words_6',
                'i.q_13_words_7',
                'i.q_13_words_8',
                'i.q_13_words_9',
                'i.q_13_words_10',
                'i.q_13_words_11',
                'i.q_13_words_12',
                'i.q_13_words_13',
                'i.q_13_words_14',
                'i.q_13_words_15',
                'i.q_13_words_16',
                'i.q_14_word_combos_1',
                'i.q_14_word_combos_2',
                'i.q_14_word_combos_3',
                'i.q_14_word_combos_4',
                'i.q_14_word_combos_5',
                'i.q_14_word_combos_6',
                'i.q_14_word_combos_raw_score',
                'i.q_15_word_combos_1',
                'i.q_15_word_combos_2',
                'i.q_15_word_combos_raw_score',
                'i.q_15_word_combos_3',
                'i.q_15_word_combos_4',
                'i.q_15_word_combos_5',
                'i.q_15_word_combos_6',
                'i.q_16_language_comp_raw_score',
                'i.q_15_word_combos_7',
                'i.q_15_word_combos_8',
                'i.words_weighted',
                'i.wind_up_admin',
                'i.q_16_language_comp_objects_1_name',
                'i.balloon_admin',
                'i.q_16_language_comp_objects_1',
                'i.bubbles_admin',
                'i.q_16_language_comp_objects_2_name',
                'i.jar_admin',
                'i.q_16_language_comp_objects_2',
                'i.books_admin',
                'i.q_16_language_comp_objects_3_name',
                'i.play_admin',
                'i.q_16_language_comp_objects_3',
                'i.q_16_language_comp_objects_4_name',
                'i.q_16_language_comp_objects_4',
                'i.q_16_language_comp_person_1_name',
                'i.q_16_language_comp_person_1',
                'i.q_16_language_comp_person_2_name',
                'i.q_16_language_comp_person_2',
                'i.q_16_language_comp_person_3_name',
                'i.q_16_language_comp_person_3',
                'i.q_16_language_comp_body_parts_1_name',
                'i.q_16_language_comp_body_parts_1',
                'i.q_16_language_comp_body_parts_2_name',
                'i.q_16_language_comp_body_parts_2',
                'i.q_16_language_comp_body_parts_3_name',
                'i.q_16_language_comp_body_parts_3',
                'i.q_16_language_comp_body_parts_4_name',
                'i.q_16_language_comp_body_parts_4',
                'i.understanding_weighted',
                'i.q_17_action_schemes_puts_in',
                'i.q_17_action_schemes_puts_on',
                'i.q_17_action_schemes_drinks_with_bottle',
                'i.q_17_action_schemes_drinks_with_cup',
                'i.q_18_actions_towards_other_raw_score',
                'i.q_17_action_schemes_hugs',
                'i.q_17_action_schemes_kisses',
                'i.q_17_action_schemes_feeds_with_utensil',
                'i.q_17_action_schemes_feeds_with_bowl',
                'i.q_17_action_schemes_stirs',
                'i.q_17_action_schemes_scoops',
                'i.q_17_action_schemes_pours',
                'i.q_19_sequence_action_schemes_raw_score',
                'i.q_17_action_schemes_other',
                'i.q_17_action_schemes_other_specify',
                'i.q_17_action_schemes_none',
                'i.q_17_action_schemes_raw_score',
                'i.q_18_action_towards_other_1',
                'i.q_18_action_towards_other_1_agent',
                'i.q_18_action_towards_other_1_agent_specify',
                'i.q_18_action_towards_other_2',
                'i.q_18_action_towards_other_2_agent',
                'i.q_18_action_towards_other_2_agent_specify',
                'i.q_18_action_towards_other_3',
                'i.q_18_action_towards_other_3_agent',
                'i.q_18_action_towards_other_3_agent_specify',
                'i.q_18_action_towards_other_4',
                'i.q_18_action_towards_other_4_agent',
                'i.q_18_action_towards_other_4_agent_specify',
                'i.q_18_action_towards_other_5',
                'i.q_18_action_towards_other_5_agent',
                'i.q_18_action_towards_other_5_agent_specify',
                'i.q_18_action_towards_other_6',
                'i.q_18_action_towards_other_6_agent',
                'i.q_18_action_towards_other_6_agent_specify',
                'i.q_19_sequence_action_schemes_1_action1',
                'i.q_19_sequence_action_schemes_1_action2',
                'i.q_19_sequence_action_schemes_2_action1',
                'i.q_19_sequence_action_schemes_2_action2',
                'i.q_19_sequence_action_schemes_3_action1',
                'i.q_19_sequence_action_schemes_3_action2',
                'i.q_19_sequence_action_schemes_4_action1',
                'i.q_19_sequence_action_schemes_4_action2',
                'i.q_19_sequence_action_schemes_5_action1',
                'i.q_19_sequence_action_schemes_5_action2',
                'i.q_19_sequence_action_schemes_6_action1',
                'i.q_19_sequence_action_schemes_6_action2',
                'CASE i.q_20_stacks_tower WHEN \'not_administered\' THEN \'6_not_administered\' ELSE i.q_20_stacks_tower END as q_20_stacks_tower',
                'i.q_20_stacks_tower_raw_score',
                'gestures_standard',
                'gestures_percentile',
                'i.q_16a_language_comp_object_raw_score',
                'i.q_16b_language_comp_person_name_raw_score',
                'i.q_16c_language_comp_body_parts_raw_score'
            );
        } else if ($this->instrument == 'ibq_r') {
            $fields = array('i.activity_level', 'i.approach', 'i.cuddliness', 'i.distress_to_limitations', 'i.duration_of_orienting', 'i.falling_reactivity', 'i.fear', 'i.high_pleasure', 'i.low_pleasure', 'i.perceptual_sensitivity', 'i.sadness', 'i.smiling_and_laughter', 'i.soothability', 'i.vocal_reactivity', 'i.q_1', 'i.q_10', 'i.q_100', 'i.q_101', 'i.q_102', 'i.q_103', 'i.q_104', 'i.q_105', 'i.q_106', 'i.q_107', 'i.q_108', 'i.q_109', 'i.q_11', 'i.q_110', 'i.q_111', 'i.q_112', 'i.q_113', 'i.q_114', 'i.q_115', 'i.q_116', 'i.q_117', 'i.q_118', 'i.q_119', 'i.q_12', 'i.q_120', 'i.q_121', 'i.q_122', 'i.q_123', 'i.q_124', 'i.q_125', 'i.q_126', 'i.q_127', 'i.q_128', 'i.q_129', 'i.q_13', 'i.q_130', 'i.q_131', 'i.q_132', 'i.q_133', 'i.q_134', 'i.q_135', 'i.q_136', 'i.q_137', 'i.q_138', 'i.q_139', 'i.q_14', 'i.q_140', 'i.q_141', 'i.q_142', 'i.q_143', 'i.q_144', 'i.q_145', 'i.q_146', 'i.q_147', 'i.q_148', 'i.q_149', 'i.q_15', 'i.q_150', 'i.q_151', 'i.q_152', 'i.q_153', 'i.q_154', 'i.q_155', 'i.q_156', 'i.q_157', 'i.q_158', 'i.q_159', 'i.q_16', 'i.q_160', 'i.q_161', 'i.q_162', 'i.q_163', 'i.q_164', 'i.q_165', 'i.q_166', 'i.q_167', 'i.q_168', 'i.q_169', 'i.q_17', 'i.q_170', 'i.q_171', 'i.q_172', 'i.q_173', 'i.q_174', 'i.q_175', 'i.q_176', 'i.q_177', 'i.q_178', 'i.q_179', 'i.q_18', 'i.q_180', 'i.q_181', 'i.q_182', 'i.q_183', 'i.q_184', 'i.q_185', 'i.q_186', 'i.q_187', 'i.q_188', 'i.q_189', 'i.q_19', 'i.q_190', 'i.q_191', 'i.q_2', 'i.q_20', 'i.q_21', 'i.q_22', 'i.q_23', 'i.q_24', 'i.q_25', 'i.q_26', 'i.q_27', 'i.q_28', 'i.q_29', 'i.q_3', 'i.q_30', 'i.q_31', 'i.q_32', 'i.q_33', 'i.q_34', 'i.q_35', 'i.q_36', 'i.q_37', 'i.q_38', 'i.q_39', 'i.q_4', 'i.q_40', 'i.q_41', 'i.q_42', 'i.q_43', 'i.q_44', 'i.q_45', 'i.q_46', 'i.q_47', 'i.q_48', 'i.q_49', 'i.q_5', 'i.q_50', 'i.q_51', 'i.q_52', 'i.q_53', 'i.q_54', 'i.q_55', 'i.q_56', 'i.q_57', 'i.q_58', 'i.q_59', 'i.q_6', 'i.q_60', 'i.q_61', 'i.q_62', 'i.q_63', 'i.q_64', 'i.q_65', 'i.q_66', 'i.q_67', 'i.q_68', 'i.q_69', 'i.q_7', 'i.q_70', 'i.q_71', 'i.q_72', 'i.q_73', 'i.q_74', 'i.q_75', 'i.q_76', 'i.q_77', 'i.q_78', 'i.q_79', 'i.q_8', 'i.q_80', 'i.q_81', 'i.q_82', 'i.q_83', 'i.q_84', 'i.q_85', 'i.q_86', 'i.q_87', 'i.q_88', 'i.q_89', 'i.q_9', 'i.q_90', 'i.q_91', 'i.q_92', 'i.q_93', 'i.q_94', 'i.q_95', 'i.q_96', 'i.q_97', 'i.q_98', 'i.q_99');
        } else if ($this->instrument == 'head_measurements_subject') {
            $fields = array('i.length1', 'i.length2', 'i.head_length_unit', 'i.weight1', 'i.weight2', 'i.weight_unit');
        } else if ($this->instrument == 'prefrontal_task') {
            $fields = array('i.training', 'i.training_finds_partially_covered', 'i.training_finds_fully_covered', 'i.training_retrieves_R_well', 'i.training_retrieves_R_well_trial', 'i.training_retrieves_R_well_trial_of', 'i.training_retrieves_L_well', 'i.training_retrieves_L_well_trial', 'i.training_retrieves_L_well_trial_of', 'i.start_side', 'i.trial_1', 'i.trial_2', 'i.trial_3', 'i.trial_4', 'i.trial_5', 'i.trial_6', 'i.trial_7', 'i.trial_8', 'i.trial_9', 'i.trial_10', 'i.trial_11', 'i.trial_12', 'i.trial_13', 'i.trial_14', 'i.trial_15', 'i.trial_16', 'i.trial_17', 'i.trial_18', 'i.trial_19', 'i.trial_20', 'i.trial_21', 'i.trial_22', 'i.trial_23', 'i.trial_24', 'i.first_reversal', 'i.second_reversal', 'i.third_reversal', 'i.fourth_reversal', 'i.validity_of_data', 'i.invalidity_reason', 'i.invalidity_comment', 'i.invalidity_comment_status', 'i.5sec_overall_correct', 'i.5sec_overall_trials', 'i.5sec_reversals_correct', 'i.5sec_reversals_trials', 'i.12sec_overall_correct', 'i.12sec_overall_trials', 'i.12sec_reversals_correct', 'i.12sec_reversals_trials');
        } else if ($this->instrument == 'fyi') {
            $fields = array('i.person_filling_out', 'i.person_filling_out_specify', 'i.risk_score', 'i.percentile', 'i.soc_com_risk', 'i.sen_reg_risk', 'i.orientrec', 'i.affeng', 'i.imitate', 'i.express', 'i.senproc', 'i.regpat', 'i.react', 'i.repplay', 'i.q_1', 'i.q_2', 'i.q_3', 'i.q_4', 'i.q_5', 'i.q_6', 'i.q_7', 'i.q_8', 'i.q_9', 'i.q_10', 'i.q_11', 'i.q_12', 'i.q_13', 'i.q_14', 'i.q_15', 'i.q_16', 'i.q_17', 'i.q_18', 'i.q_19', 'i.q_20', 'i.q_21', 'i.q_22', 'i.q_23', 'i.q_24', 'i.q_25', 'i.q_26', 'i.q_27', 'i.q_28', 'i.q_29', 'i.q_30', 'i.q_31', 'i.q_32', 'i.q_33', 'i.q_34', 'i.q_35', 'i.q_36', 'i.q_37', 'i.q_38', 'i.q_39', 'i.q_40', 'i.q_41', 'i.q_42', 'i.q_43', 'i.q_44', 'i.q_45', 'i.q_46', 'i.q_47', 'i.q_48', 'i.q_49', 'i.q_50', 'i.q_51', 'i.q_52', 'i.q_53', 'i.q_54', 'i.q_55', 'i.q_56', 'i.q_57', 'i.q_58', 'i.q_59', 'i.q_60', 'i.sounds_p', 'i.sounds_b', 'i.sounds_t', 'i.sounds_d', 'i.sounds_k', 'i.sounds_g', 'i.sounds_m', 'i.sounds_n', 'i.sounds_w', 'i.sounds_y', 'i.sounds_h', 'i.sounds_s', 'i.q_62', 'i.q_63');
        } else if ($this->instrument == 'edi' || $this->instrument == 'edi2') {
            $fields = array('i.score_0_3_regulatory', 'i.score_0_3_total_symptoms', 'i.score_10_12_communication', 'i.score_10_12_regulatory', 'i.score_10_12_repetitive_behaviour', 'i.score_10_12_social', 'i.score_10_12_total_symptoms', 'i.score_13_15_communication', 'i.score_13_15_regulatory', 'i.score_13_15_repetitive_behaviour', 'i.score_13_15_social', 'i.score_13_15_total_symptoms', 'i.score_16_18_communication', 'i.score_16_18_regulatory', 'i.score_16_18_repetitive_behaviour', 'i.score_16_18_social', 'i.score_16_18_total_symptoms', 'i.score_19_21_communication', 'i.score_19_21_regulatory', 'i.score_19_21_repetitive_behaviour', 'i.score_19_21_social', 'i.score_19_21_total_symptoms', 'i.score_22_24_communication', 'i.score_22_24_regulatory', 'i.score_22_24_repetitive_behaviour', 'i.score_22_24_social', 'i.score_22_24_total_symptoms', 'i.score_4_6_regulatory', 'i.score_4_6_social', 'i.score_4_6_total_symptoms', 'i.score_7_9_communication', 'i.score_7_9_regulatory', 'i.score_7_9_social', 'i.score_7_9_total_symptoms', 'i.EDI1', 'i.EDI2', 'i.EDI3', 'i.EDI4', 'i.EDI5', 'i.EDI6', 'i.EDI7', 'i.EDI8', 'i.EDI9', 'i.EDI10', 'i.EDI11', 'i.EDI12', 'i.EDI13', 'i.EDI14', 'i.EDI15', 'i.EDI16', 'i.EDI17', 'i.EDI18', 'i.EDI19', 'i.EDI20', 'i.EDI21', 'i.EDI22', 'i.EDI23', 'i.EDI24', 'i.EDI25', 'i.EDI26', 'i.EDI27', 'i.EDI28', 'i.EDI29', 'i.EDI30', 'i.EDI31', 'i.EDI32', 'i.EDI33', 'i.EDI34', 'i.EDI35', 'i.EDI36', 'i.EDI37', 'i.EDI38', 'i.EDI39', 'i.EDI40', 'i.EDI41', 'i.EDI42', 'i.EDI43', 'i.EDI44', 'i.EDI45', 'i.EDI46', 'i.EDI47', 'i.EDI48', 'i.EDI49', 'i.EDI50', 'i.EDI51', 'i.EDI52', 'i.EDI53', 'i.EDI54', 'i.EDI55', 'i.EDI56', 'i.EDI57', 'i.EDI58', 'i.EDI59', 'i.EDI60', 'i.EDI61', 'i.EDI62', 'i.EDI63', 'i.EDI64', 'i.EDI65', 'i.EDI66', 'i.EDI67', 'i.EDI68', 'i.EDI69', 'i.EDI70', 'i.EDI71', 'i.EDI72', 'i.EDI73', 'i.EDI74', 'i.EDI75', 'i.EDI76', 'i.EDI77', 'i.EDI78', 'i.EDI79', 'i.EDI80', 'i.EDI81', 'i.EDI82', 'i.EDI83', 'i.EDI84', 'i.EDI85', 'i.EDI86', 'i.EDI87', 'i.EDI88', 'i.EDI89', 'i.EDI90', 'i.EDI91', 'i.EDI92', 'i.EDI93', 'i.EDI94', 'i.EDI95', 'i.EDI96', 'i.inj', 'i.dear', 'i.conf', 'i.legl', 'i.emp', 'i.crim', 'i.hea AS edihea', 'i.hosp as edihosp');
        } else if ($this->instrument == 'charge') {
            $fields = array(
                'c.CandidateGUID',
                "CASE c.Gender WHEN 'Male' THEN 'M' WHEN 'Female' THEN 'F' END AS Gender",
                "IF(medpsych.Date_taken != '', DATE_FORMAT(medpsych.Date_taken, '%m/%d/%Y'), '01/01/1900') as Med_Psych_Hist_Date_Taken",
                'medpsych.Candidate_Age as Med_Psych_Hist_Candidate_Age',
                "CASE medpsych.q16_has_child_ever WHEN 'b_meningitis_encephalitis' THEN 'Yes' WHEN 'b_meningitis_encephalitis{@}c_lost_consciousness_head_injury' THEN 'Yes' ELSE 'NK' END as q16_has_child_ever",
                'medpsych.q15_c_fever_seizures',
                "CASE medpsych.q15_seizures_convulsions WHEN '0_no' THEN 'No' WHEN '1_yes' THEN 'Yes' ELSE 'NK' END AS q15_seizures_convulsions",
                'medpsych.q17_birth_defects',
                'neuroscreen.q19_other_physical_abnormalities',
                "CASE neuroscreen.q1_strabismus WHEN '0_absent' THEN 'No' WHEN '1_covert' THEN 'Yes' WHEN '2_overt' THEN 'Yes' WHEN '7_can_t_tell' THEN 'NK' WHEN '8_no_overt' THEN 'NK' WHEN '9_not_tested' THEN 'NK' WHEN 'not_answered' THEN 'NK' END AS q1_strabismus",
                'neuroscreen.q6_ear_formation',
                'tsi.med_his_q_5_medications_describe',
                'tsi.med_his_q_8_brain_MRI_results',
                "CASE tsi.congenital_heart_problems WHEN 'yes' THEN 'Yes' WHEN 'no' THEN 'No' ELSE 'NK' END AS congenital_heart_problems",
                "CASE tsi.med_his_q_6_allergies WHEN 'yes' THEN 'Yes' WHEN 'no' THEN 'No' ELSE 'NK' END AS med_his_q_6_allergies",
                'tsi.med_his_q_6_allergies_describe',
                "'NK' as develop_regression",
                "'NK' as rev_earrecuotitis",
                "'NK' as rev_endodiabetes",
                "'999' as rev_endodiabetestype",
                "'NK' as rev_endohyperthyroidism",
                "'NK' as rev_endohypothyroidism",
                "'NK' as rev_gastroreflux",
                "'NK' as rev_gastrorefluxmed",
                "'NK' as rev_headseizurecontrol",
                "'NK' as rev_immunoenvallergy",
                "'NK' as rev_immunoinfluenzvacc",
                "'999' as rev_immunoinfluenzvacc1_h1n1",
                "'999' as rev_immunoinfluenzvacc2_h1n1",
                "'999' as rev_immunoinfluenzvacc3_h1n1",
                "'999' as rev_immunoinfluenzvacc4_h1n1",
                "'999' as rev_immunoinfluenzvacc5_h1n1",
                "'NK' as rev_immunorecurinfection",
                "'NK' as rev_immunosepsis",
                "'NK' as rev_pulasthma",
                "'NK' as rev_skinabcesses"
            );
        }
        return implode($fields, ", ");
    }

    function getFields()
    {
        return $this->getCommonFields() . $this->getInstrumentFields();
    }

    function getQuery()
    {
        $validating = TRUE;
        
        if ($validating) {
            $test_fields = "c.PSCID, s.Visit_label, s.SubprojectID, ";
        } else { $test_fields = ""; }
        
        if ($this->instrument == 'demographics') {
            return "SELECT DISTINCT ". $test_fields ." IBISID, CandidateGUID, ProbandGUID, CASE c.Gender WHEN 'Male' THEN 'M' WHEN 'Female' THEN 'F' END AS Gender, CASE c.ProbandGender WHEN 'Male' THEN 'M' WHEN 'Female' THEN 'F' END as ProbandGender, c.CenterID as Site, CASE s.SubprojectID WHEN 1 THEN 'High Risk' WHEN 2 THEN 'High Risk' WHEN 3 THEN 'Low Risk' END as Cohort FROM candidate c JOIN session s ON (s.CandID=c.CandID) WHERE c.Active='Y' AND s.Active='Y' AND COALESCE(s.Current_stage, '') <> 'Recycling Bin' AND COALESCE(s.Visit, '') NOT IN ('Failure', 'Withdrawal') AND COALESCE(s.Screening, '') NOT IN ('Failure', 'Withdrawal') AND c.CandidateGUID IS NOT NULL AND s.SubprojectID IN (1, 2, 3) AND c.CenterID IN (2, 3, 4, 5) ";
        } else if ($this->instrument == 'charge') {
            return "SELECT ". $test_fields . $this->getFields() . " FROM session s JOIN candidate c USING (CandID) JOIN participant_status ps ON (ps.CandID = c.CandID) LEFT JOIN flag medpsychflag ON (s.ID=medpsychflag.SessionID AND medpsychflag.Test_name='med_psych_hist' AND medpsychflag.Administration='All' AND medpsychflag.Data_entry='Complete' AND EXISTS (SELECT 'x' FROM flag df WHERE df.CommentID=CONCAT('DDE_', medpsychflag.CommentID) AND df.Data_entry='Complete') AND NOT EXISTS (SELECT 'x' FROM conflicts_unresolved cu WHERE cu.CommentId1=medpsychflag.CommentID OR cu.CommentId2=medpsychflag.CommentID) )
                    LEFT JOIN flag neuroscreenflag ON (s.ID=neuroscreenflag.SessionID AND neuroscreenflag.Test_name='neuro_screen' AND neuroscreenflag.Administration='All' AND neuroscreenflag.Data_entry='Complete' AND EXISTS (SELECT 'x' FROM flag df WHERE df.CommentID=CONCAT('DDE_', neuroscreenflag.CommentID) AND df.Data_entry='Complete') AND NOT EXISTS (SELECT 'x' FROM conflicts_unresolved cu WHERE cu.CommentId1=neuroscreenflag.CommentID OR cu.CommentId2=neuroscreenflag.CommentID))
                    LEFT JOIN flag tsiflag ON (s.ID=tsiflag.SessionID AND tsiflag.Test_name='tsi' AND tsiflag.Administration='All' AND tsiflag.Data_entry='Complete' AND EXISTS (SELECT 'x' FROM flag df WHERE df.CommentID=CONCAT('DDE_', tsiflag.CommentID) AND df.Data_entry='Complete') AND NOT EXISTS (SELECT 'x' FROM conflicts_unresolved cu WHERE cu.CommentId1=tsiflag.CommentID OR cu.CommentId2=tsiflag.CommentID) )
                    LEFT JOIN med_psych_hist medpsych ON (medpsychflag.CommentID=medpsych.CommentID)
                    LEFT JOIN neuro_screen neuroscreen ON (neuroscreenflag.CommentID=neuroscreen.CommentID)
                    LEFT JOIN tsi tsi ON (tsiflag.CommentID=tsi.CommentID)
                    WHERE " . $this->getWhere();
        } else if ($this->instrument == 'ndar_subject') {
            return "SELECT ". $test_fields ." c.IBISID, s.CenterID as Site, CASE s.SubprojectID WHEN 1 THEN 'High Risk' WHEN 2 THEN 'High Risk' WHEN 3 THEN 'Low Risk' WHEN 9 THEN 'High Risk' WHEN 10 THEN 'Low Risk' END as Cohort, c.ProbandGUID,   CASE c.ProbandGender WHEN 'Male' THEN 'M' WHEN 'Female' THEN 'F' END AS ProbandGender, c.CandidateGUID, CASE c.Gender WHEN 'Male' THEN 'M' WHEN 'Female' THEN 'F' END AS Gender, i.Date_taken,ROUND(DATEDIFF(i.Date_taken, c.DoB) / (365/12)) AS Candidate_Age_in_Months, i.Date_taken as interview_date,ROUND(DATEDIFF(i.Date_taken, c.ProbandDoB) / (365/12)) AS Proband_Age_in_Months, i.Candidate_race as race, i.child_ethnicity as ethnic_group from candidate c  left join session s on s.CandID = c.CandID join flag f on f.SessionID = s.ID join tsi i on i.CommentID=f.CommentID join participant_status ps on ps.CandID = c.CandID WHERE " . $this->getWhere();
        }
        print  "SELECT ". $test_fields . $this->getFields() . " FROM " . $this->instrument . " i JOIN flag f ON (f.CommentID=i.CommentID) JOIN session s ON (s.ID=f.SessionID) JOIN candidate c ON (c.CandID=s.CandID) JOIN participant_status ps ON (ps.CandID = c.CandID) JOIN participant_status_options pso ON (pso.ID =  ps.participant_status) WHERE " . $this->getWhere() . " AND c.ProjectID= $this->project AND pso.Description NOT IN ('Ineligible', 'Excluded')";
        return "SELECT ". $test_fields . $this->getFields() . " FROM " . $this->instrument . " i JOIN flag f ON (f.CommentID=i.CommentID) JOIN session s ON (s.ID=f.SessionID) JOIN candidate c ON (c.CandID=s.CandID) JOIN participant_status ps ON (ps.CandID = c.CandID) JOIN participant_status_options pso ON (pso.ID = ps.participant_status) WHERE " . $this->getWhere() . " AND c.ProjectID= $this->project AND pso.Description NOT IN ('Ineligible', 'Excluded')";
    }

    function process($results)
    {
        $converted = array();
        foreach ($results as $row) {

            if ($this->instrument === 'adi_r_proband') {
                if ($row['BNV_Total'] == 'Verbal') {
                    $row['subject_verbal'] = 'yes';
                } else if ($row['BV_Total'] == 'Nonverbal') {
                    $row['subject_verbal'] = 'no';
                } else {
                    $row['subject_verbal'] = '';
                }
                $add = array('method_adi' => 1, 'rx' => 999);
                $row = array_merge($row, $add);
            }
            if (strpos($this->instrument, '_proband') !== FALSE) {
                $row['IBISID'] = $row['IBISID'] . "pr";

            }
            foreach ($row as $key => $val) {

                if (strpos($key, 'IBISID') !== FALSE) {
                    $ibis[] = $val;

                }

                if (strpos($key, 'interview_date') !== FALSE || $key == 'DoB' || strpos($key, 'interview_date') !== FALSE) {
                    //print "VAL: $val";
                    $Date = explode('-', $val);
                    $row[$key] = $Date[1] . '/' . '01' . '/' . $Date[0];
                }
                if ($this->instrument == 'adi_r_proband') {
                    if ($key == 'Total_B2V' || $key == 'Total_B3V' || $key == 'BV_Total' || $key == 'BNV_Total') {
                        if ($val == 'Verbal' || $val == 'Nonverbal') {
                            $row[$key] = '';
                        }
                    }

                    if (strpos($key, 'q_') === 0 || $key === 'relationship') {
                        $matches = array();
                        //ndar mapping - 1=mom, 2=dad,28=both parents, 13=other, -999= Missing
                        $relationships = array(0 => 1, 1 => 2, 3 => 28, 5 => 13, 9 => '-999');
                        if (preg_match('/(\d+)_(.*)/', $val, $matches) === 1) {
                            if ($key === 'relationship') {
                                $row[$key] = $relationships[$matches[1]];
                            } else {
                                $row[$key] = $matches[1];
                            }
                        } else if ($val == 'not_answered' && $key === 'relationship') {
                            $row[$key] = '-999';
                        }

                    }
                }
                if (strpos($key, 'Candidate_Age') !== FALSE) {
                    $row[$key] = intval($val);
                }

                if ($this->instrument == 'csbs') {
                    if (strpos($key, 'q_20_stacks_tower') !== FALSE) {
                        $temp = explode("_", $val);
                        if (is_numeric($temp[0])) {
                            $row[$key] = $temp[0];
                        }
                    }
                    $relationships = array('Mother' => 1, 'Mom' => 1, 'mother' => 1, 'Father' => 2, 'Dad' => 2, 'dad' => 2, 'Mom/Dad' => 28, 'Both Parents' => 28,
                        'mother and father' => 28, 'father and mother' => 28, 'Fater' => 2, 'Other' => 90, 'NA' => '-999');
                    if ($key === 'relationship_to_child') {
                        if (!empty($val)) {
                            $row[$key] = $relationships[$val];
                        } else {
                            $row[$key] = '-999';//missing
                        }
                    }

                    $add = array('communication_concern' => '999', 'communication_rs' => '999', 'emotion_eyegaze_concern' => '999', 'emotion_eyegaze_rs' => '999',
                        'gestures_concern' => '999', 'gestures_rs' => '999', 'objec_use_concern' => '999', 'object_use_rs' => '999',
                        'social_concern' => '999', 'sounds_concern' => '999', 'sounds_rs' => '999', 'speech_concern' => '999', 'symbolic_concern' => '999',
                        'total_concern' => '999', 'understanding_concern' => '999', 'understanding_rs' => '999', 'words_concern' => '999', 'words_rs' => '999');
                    $row = array_merge($row, $add);
                    if (strpos($key, 'understanding_standard') !== FALSE || strpos($key, 'understanding_percentile') !== FALSE) {
                        if (empty($val)) {
                            $row[$key] = '999';
                        }
                    }
                    $map = array('q_4_rate_of_communicating_raw_score' => 'communication_scale4',
                        'q_5_behaviour_regulation_raw_score' => 'communication_scale5',
                        'q_6_social_interaction_raw_score' => 'communication_scale6',
                        'q_7_joint_attention_raw_score' => 'communication_scale7',
                        'q_1_gaze_shifts_raw_score' => 'emotion_eyegaze_scale1',
                        'q_2_shared_positive_affect_raw_score' => 'emotion_eyegaze_scale2',
                        'q_3_gaze_point_following_raw_score' => 'emotion_eyegaze_scale3',
                        'q_8_conventional_gestures_raw_score' => 'gestures_scale8',
                        'q_9_distal_gestures_raw_score' => 'gestures_scale9',
                        'q_17_action_schemes_raw_score' => 'object_use_scale17',
                        'q_18_actions_towards_other_raw_score' => 'object_use_scale18',
                        'q_20_stacks_tower_raw_score' => 'object_use_scale20',
                        'q_10_syllables_consonants_raw_score' => 'sounds_scale10',
                        'q_11_inventory_of_consonants_raw_score' => 'sounds_scale11',
                        'q_16a_language_comp_object_raw_score' => 'understanding_scale16a',
                        'q_16b_language_comp_person_name_raw_score' => 'understanding_scale16b',
                        'q_12_words_raw_score' => 'words_scale12',
                        'q_13_words_raw_score' => 'words_scale13',
                        'q_14_word_combos_raw_score' => 'words_scale14',
                        'q_15_word_combos_raw_score' => 'words_scale15',
                        'q_19_sequence_action_schemes_raw_score' => 'object_use_scale19',
                        'q_16c_language_comp_body_parts_raw_score' => 'understanding_scale16c');
//print_r($map);
                    foreach ($map as $field => $new_val) {
                        if (strpos($key, $field) !== FALSE) {
                            $new_field = $new_val;
                            //print $key;
                            if (strpos($key, 'q_15_word_combos_raw_score') !== FALSE || strpos($key, 'q_13_words_raw_score') !== FALSE) {
                                if (empty($val)) {
                                    $val = 0;
                                }
                            }
                            unset($row[$key]);
                            $add = array($new_field => $val);
                            $row = array_merge($row, $add);
                        }
                    }

                    if (strpos($key, 'q_1_alertness') !== FALSE || strpos($key, 'q_2_emotional_reaction') !== FALSE || strpos($key, 'q_3_level_of_interest') !== FALSE
                        || strpos($key, 'q_4_comfort_level') !== FALSE || strpos($key, 'q_5_level_of_activity') !== FALSE || strpos($key, 'q_6_level_of_communication') !== FALSE
                        || strpos($key, 'q_7_play_behaviour') !== FALSE
                    ) {
                        $temp = explode("_", $val);
                        if (is_numeric($temp[0])) {
                            $row[$key] = $temp[0];
                        } else {
                            $row[$key] = 4;
                        }
                    }
                }
                if ($this->instrument == 'macarthur_words_gestures') {
                    $fieldstochange = array('I_B_1', 'I_B_2', 'I_B_3', 'I_B_4', 'I_B_5', 'I_B_6', 'I_B_7', 'I_B_8', 'I_B_9', 'I_B_10',
                        'I_B_11', 'I_B_12', 'I_B_13', 'I_B_14', 'I_B_15', 'I_B_16', 'I_B_17', 'I_B_18', 'I_B_19',
                        'I_B_20', 'I_B_21', 'I_B_22', 'I_B_23', 'I_B_24', 'I_B_25', 'I_B_26', 'I_B_27', 'I_B_28');
                    if (in_array($key, $fieldstochange)) {
                        if ($val == 'understands') {
                            $row[$key] = 1;
                        } elseif ($val == null) {
                            $row[$key] = 0;
                        }
                    }
                    if (strpos($key, 'I_C_1') !== FALSE || strpos($key, 'I_C_2') !== FALSE) {
                        if ($val == 'never') {
                            $row[$key] = 0;
                        } elseif ($val == 'sometimes') {
                            $row[$key] = 1;
                        } elseif ($val == 'often') {
                            $row[$key] = 2;
                        } elseif ($val == 'not_answered') {
                            $row[$key] = 'not_answered';
                        }
                    }
                    if (strpos($key, 'I_A_1') !== FALSE || strpos($key, 'I_A_2') !== FALSE || strpos($key, 'I_A_3') !== FALSE) {
                        if ($val == 'yes') {
                            $row[$key] = 1;
                        }
                        if ($val == 'no') {
                            $row[$key] = 0;
                        }
                    }
                    if (strpos($key, 'percentile') !== FALSE && strpos($val, 'old') !== FALSE) {
                        $row[$key] = 999;
                    }
                }
                if ($this->instrument == 'edi' || $this->instrument == 'edi2') {
                    $fieldstochange = array('EDI1', 'EDI2', 'EDI3', 'EDI4', 'EDI5', 'EDI6', 'EDI7', 'EDI8', 'EDI9', 'EDI10', 'EDI11', 'EDI12',
                        'EDI13', 'EDI14', 'EDI15', 'EDI16', 'EDI17', 'EDI18', 'EDI19', 'EDI20', 'EDI21', 'EDI22', 'EDI23',
                        'EDI24', 'EDI25', 'EDI26', 'EDI27', 'EDI28', 'EDI29', 'EDI30', 'EDI31', 'EDI32', 'EDI33', 'EDI34',
                        'EDI35', 'EDI36', 'EDI37', 'EDI38', 'EDI39', 'EDI40', 'EDI41', 'EDI42', 'EDI43', 'EDI44', 'EDI45',
                        'EDI46', 'EDI47', 'EDI48', 'EDI49', 'EDI50', 'EDI51', 'EDI52', 'EDI53', 'EDI54', 'EDI55', 'EDI56',
                        'EDI57', 'EDI58', 'EDI59', 'EDI60', 'EDI61', 'EDI62', 'EDI63', 'EDI64', 'EDI65', 'EDI66', 'EDI67',
                        'EDI68', 'EDI69', 'EDI70', 'EDI71', 'EDI72', 'EDI73', 'EDI74', 'EDI75', 'EDI76', 'EDI77', 'EDI78',
                        'EDI79', 'EDI80', 'EDI81', 'EDI82', 'EDI83', 'EDI84', 'EDI85', 'EDI86', 'EDI87', 'EDI88', 'EDI89',
                        'EDI90', 'EDI91', 'EDI92', 'EDI93', 'EDI94', 'EDI95', 'EDI96');
                    if (in_array($key, $fieldstochange)) {
                        $key_new = $key . "_NDAR";
                        unset($row[$key]);
                        if ($val == 'not_answered') {
                            $new = array($key_new => 9);
                        } else {
                            $new = array($key_new => $val);
                        }
                        $row = array_merge($row, $new);

                    }
                    if (strpos($key, 'edihosp') !== FALSE || strpos($key, 'edihea') !== FALSE) {
                        if ($val == 'not_answered' || empty($val)) {
                            $row[$key] = 9;
                        } else {
                            $temp = explode('_', $val);
                            $row[$key] = $temp[0];
                        }
                    }
                    $addfields = array('edict_c' => 999, 'edict_r' => 999, 'edict_rg' => 999, 'edict_s' => 999, 'edict_se' => 999, 'edict_t' => 999,
                        'edict_x' => 999, 'edifamt' => 999, 'edigtot' => 999, 'edimedt' => 999, 'edistrt' => 999);
                    $row = array_merge($row, $addfields);
                }
                if ($this->instrument == 'vineland_subject' || $this->instrument == 'vineland_proband') {
                    $fieldstochange = array('ABC_STD_SCORE', 'COM_STD_SCORE', 'DLS_STD_SCORE', 'SOC_STD_SCORE', 'MS_STD_SCORE',
                        'CRIT_ITEM_1', 'CRIT_ITEM_2', 'CRIT_ITEM_3', 'CRIT_ITEM_4', 'CRIT_ITEM_5', 'CRIT_ITEM_6',
                        'CRIT_ITEM_7', 'CRIT_ITEM_8', 'CRIT_ITEM_9', 'CRIT_ITEM_10', 'CRIT_ITEM_11', 'CRIT_ITEM_12',
                        'CRIT_ITEM_13', 'CRIT_ITEM_14');
                    $relationships = array('Mother' => 1, 'Mom' => 1, 'Father' => 2, 'Dad' => 2, 'dad' => 2, 'Mom/Dad' => 28, 'Both Parents' => 28,
                        'mother and father' => 28, 'father and mother' => 28, 'Fater' => 2, 'Other' => 90);
                    if ($key === 'relationship') {
                        if (!empty($val)) {
                            $row[$key] = $relationships[$val];
                        } else {
                            $row[$key] = '-999';//missing
                        }
                    }

                    if (in_array($key, $fieldstochange)) {
                        if (empty($val) || trim($val) == false) {
                            $row[$key] = 999;
                        }
                    }
                    if (strpos($val, 'Moderately') !== FALSE) {
                        $val = str_replace("Moderately", "Mod.", $val);
                    }
                    $add_columns = array('communicationdomain_totala' => 999, 'livingskillsdomain_totala' => 999, 'motorskillsdomain_totala' => 999, 'socializationdomain_totala' => 999);
                    $row = array_merge($row, $add_columns);
                    //  print "CommentID - ".$row['CommentID'] ."\n ";
                    $ndar_vineland_columns = $this->getMoreNDARFields($this->instrument, $row['CommentID']);
                    $row = array_merge($row, $ndar_vineland_columns);
                    if ($key === 'CommentID') {
                        unset($row[$key]);
                    }
                }
                if ($this->instrument == 'mullen') {
                    if (strpos($key, 'expressive_lang_') !== FALSE || strpos($key, 'gross_motor_') !== FALSE ||
                        strpos($key, 'visual_recept_') !== FALSE || strpos($key, 'fine_motor_') !== FALSE ||
                        strpos($key, 'receptive_lang_') !== FALSE
                    ) {
                        if (is_null($val) || empty($val)) {
                            $row[$key] = 9;
                        }
                    }
                    $add_columns = array('info_med' => 999, 'scl2_mtchsize_largered' => 999, 'scl2_mtchsize_largeyellow' => 999,
                        'scl2_mtchsize_smallred' => 999, 'scl2_mtchsize_smallyellow' => 999, 'scl4_color_black' => 999,
                        'scl4_color_blue' => 999, 'scl4_color_brown' => 999, 'scl4_color_green' => 999, 'scl4_color_orange' => 999,
                        'scl4_color_purple' => 999, 'scl4_color_red' => 999, 'scl4_color_yellow' => '999');
                    $row = array_merge($row, $add_columns);
                }
                if ($this->instrument == 'aosi') {
                    $score_fields = array('aosi_totalscore', 'aosi_numbermarkers', 'aosi_q1_visualinstructions',
                        'aosi_q2_disengagementscore', 'aosi_q3_orientsnameinstruct', 'aosi_q6_activitiesinstruction');
                    if (in_array($key, $score_fields) &&
                        (strpos($val, 'N') !== FALSE || strpos($val, 'Unable') !== FALSE)
                    ) {
                        $row[$key] = 8;
                    }
                }
                if ($this->instrument == 'scq_proband' || $this->instrument == 'scq_subject') {
                    if (strpos($key, 'q') !== FALSE && empty($val)) {
                        $row[$key] = 'not_answered';
                    }

                }
                if ($this->instrument == 'm_chat_proband') {
                    $add_columns = array('fu_q8_proper_play_shapes' => 999);
                    $row = array_merge($row, $add_columns);
                }
                if ($this->instrument == 'ndar_subject') {
                    if (strpos($key, 'interview_date') !== FALSE || $key == 'DoB' || strpos($key, 'Date_Taken') !== FALSE) {
                        $Date = explode('-', $val); //print_r($Date);
                        $row[$key] = $Date[1] . '/' . '01' . '/' . $Date[0];
                    }


                }

            }
            if ($this->instrument == 'head_measurements_subject') {
                $add_columns = array('height_met' => '', 'height_std' => '', 'weight_met' => '', 'weight_std' => '');
                if ($row['head_length_unit'] == 'cm') {
                    $add_columns['height_met'] = $row['length1'];
                } else if ($row['head_length_unit'] == 'inches') {
                    $add_columns['height_std'] = $row['length1'];
                }
                if ($row['weight_unit'] == 'kg') {
                    $add_columns['weight_met'] = $row['weight1'];
                } else if ($row['weight_unit'] == 'lbs') {
                    $add_columns['weight_std'] = $row['weight1'];
                }
                unset($row['head_length_unit']);
                unset($row['weight_unit']);
                unset($row['length1']);
                unset($row['length2']);
                unset($row['weight1']);
                unset($row['weight2']);

                $row = array_merge($row, $add_columns);
            }

            if (array_key_exists('validity_of_data', $row) && empty($row['validity_of_data'])) {
                $row['validity_of_data'] = 999;
            }
            $converted[] = $row;

        }
        return $converted;
    }

    function writeResults($results, $header, $filename)
    {
        $fd = fopen($filename, 'w+');
        if ($fd === FALSE) {
            exit(-1);
        }
        print "#### $header";
        $headers = array($header);
        fputcsv($fd, $headers);

        fputcsv($fd, array_keys($results[0]));
        foreach ($results as $row) {
            fputcsv($fd, $row);
        }
        return $fd;
    }

    function run()
    {
        $headers = array('adi_r_proband' => 'adi_200304', 'aosi' => 'earli_aosi01', 'csbs' => 'csbs_dp_behavior02', 'edi' => 'edi01', 'charge' => 'charge_medical_history02',
            'fyi' => 'fyi01', 'ibq_r' => 'ibq_r01', 'macarthur_words_gestures' => 'mci_words_gestures01', 'vineland_proband' => 'vinelandsurvey_200505',
            'm_chat_proband' => 'm_chat02', 'mullen' => 'mullen03', 'prefrontal_task' => 'prefront_task01', 'edi2' => 'edi01',
            'rbs_r' => 'rbs_r02', 'seq' => 'seq01', 'vineland_subject' => 'vinelandsurvey_200505', 'adi_r_subject' => 'adir_200304',
            'head_measurements_subject' => 'charge_physicalexam01', 'ndar_subject' => 'ndar_subject01');
        $Query = $this->getQuery();
        // print $Query;
        $db = &Database::singleton();
        $header = $headers[$this->instrument];
        $project_map = array(1 => '', 2 => '_IBIS2');
        $ending = $project_map[$this->project] . ".csv";
        if ($this->instrument == 'scq_proband' || $this->instrument == 'scq_subject') {
            $results = $db->pselect($Query . " AND i.scq_version='lifetime'", array());
            $converted = $this->process($results);
            $header = 'scq_lifetime04';
            $this->writeResults($converted, $header, '/var/www/loris/project/tools/NDAR_2016/' . $this->instrument . '_lifetime' . $ending);
            $results = $db->pselect($Query . " AND i.scq_version='current'", array());
            $converted = $this->process($results);
            $header = 'scq_current04';
            $this->writeResults($converted, $header, '/var/www/loris/project/tools/NDAR_2016/' . $this->instrument . '_current' . $ending);

        } else {
            $results = $db->pselect($Query, array());
            $converted = $this->process($results);
            $this->writeResults($converted, $header, '/var/www/loris/project/tools/NDAR_2016/' . $this->instrument . $ending);
        }
        return $converted;
    }

    function getMoreNDARFields($table, $commentID)
    {
        $db = Database::singleton();
        $sections = array(
            array('Name' => "REC", 'Items' => 21),
            array('Name' => "EXP", 'Items' => 55),
            array('Name' => "WRN", 'Items' => 26),
            array('Name' => "PER", 'Items' => 42),
            array('Name' => "DOM", 'Items' => 25),
            array('Name' => "CMM", 'Items' => 45),
            array('Name' => "IPR", 'Items' => 39),
            array('Name' => "PL", 'Items' => 32),
            array('Name' => "CS", 'Items' => 31),
            array('Name' => "GMS", 'Items' => 41),
            array('Name' => "FMS", 'Items' => 37),
            array('Name' => "INT", 'Items' => 12),
            array('Name' => "EXT", 'Items' => 11),
            array('Name' => "OTH", 'Items' => 16)
        );
        $setvalue = array();
        foreach ($sections as $section) {
            $numq = $section['Items'];
            $record = array();
            $for_select = '';
            for ($i = 1; $i < $numq; $i++) {
                $item = $section['Name'] . "_ITEM_" . $i;
                $corritem = $section['Name'] . "_CORRECTED_ITEM_" . $i;
                array_push($record, array($corritem => '', $item => ''));
                $for_select .= $item . "," . $corritem . ",";
            }
//            print $for_select . "CommentID - $commentID \n";
            $record = $db->pSelectRow("select $for_select Date_taken from " . $table . " WHERE CommentID=:cid", array('cid' => $commentID));
            if (!empty($record)) {
                for ($i = 1; $i < $numq; $i++) {
                    $ndar_item = $section['Name'] . "_ITEM_" . $i . "_NDAR";
                    $item = $section['Name'] . "_ITEM_" . $i;
                    $corritem = $section['Name'] . "_CORRECTED_ITEM_" . $i;
                    if ($record[$corritem] == "" && $record[$item] == "") {
                        $setvalue[$ndar_item] = '999';
                    } elseif ($record[$corritem] == "") {
                        $setvalue[$ndar_item] = $record[$item];
                    } else {
                        $setvalue[$ndar_item] = $record[$corritem];
                    }

                    if ($setvalue[$ndar_item] == 'N') {
                        $setvalue[$ndar_item] = 'N/O';
                    }
                } //end for
            }
        }

        return $setvalue;
    }
}

?>
