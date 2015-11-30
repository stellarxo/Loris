<?php
require_once "NDB_Form.class.inc";
//require_once "NDB_BVL_Instrument.class.inc";

/**
 * The forms for the tracking log menu
 * @package mri
 * @subpackage NIHPD
 */
class NDB_Form_adi_r_reliability extends NDB_Form

{
// function _hasAccess()
//     {
//         // create user object
//         $user =& User::singleton();

//         $DB =& Database::singleton();
       
//         if(!empty($this->identifier)) {
//             $query = "SELECT psc.CenterID FROM tracking_logs, candidate, psc WHERE tracking_logs.CandID=candidate.CandID AND candidate.CenterID=psc.CenterID AND tracking_logs.Tracking_log_ID='$this->identifier'";
//             $recordCenterID = $DB->selectOne($query);
            
//             return ($user->hasPermission('tracking_logs')
//                     && ($user->hasPermission('tracking_logs_edit_all')
//                         || ($user->getData('CenterID') == $recordCenterID)));

//         } else {
//             return ($user->hasPermission('tracking_logs'));
//         }
//     }

    function _getDefaults()
    {
        $DB =& Database::singleton();

        $DB->select("SELECT * FROM adi_r_reliability", $result);
               
        //print_r($this->identifier);
        if (!empty($this->identifier)) { 
            
            // set the adi_r_reliability values 
            $DB->selectRow("SELECT * FROM adi_r_reliability WHERE CommentID = '$this->identifier'", $row);
     
            // Set the defaults
            // print_r($row['CommentID']);
            
            $defaults['Examiner'] = $row['Examiner'];
            $defaults['Date_taken'] = $row['Date_taken'];
            $defaults['CommentID'] = $row['CommentID'];
            $defaults['DoB_proband'] = $row['DoB_proband'];
            $defaults['Reliability_score_all_items'] = $row['Reliability_score_all_items'];
            $defaults['Reliability_score_scored_items'] = $row['Reliability_score_scored_items'];
            $defaults['Total_A1'] = $row['Total_A1'];
            $defaults['Total_A2'] = $row['Total_A2'];
            $defaults['Total_A3'] = $row['Total_A3'];
            $defaults['Total_A4'] = $row['Total_A4'];
            $defaults['A_Total'] = $row['A_Total'];
            $defaults['Total_B1'] = $row['Total_B1'];
            $defaults['Total_B4'] = $row['Total_B4'];
            $defaults['Total_B2V'] = $row['Total_B2V'];
            $defaults['Total_B3V'] = $row['Total_B3V'];
            $defaults['BV_Total'] = $row['BV_Total'];
            $defaults['BNV_Total'] = $row['BNV_Total'];
            $defaults['Total_C1'] = $row['Total_C1'];
            $defaults['Total_C2'] = $row['Total_C2'];
            $defaults['Total_C3'] = $row['Total_C3'];
            $defaults['Total_C4'] = $row['Total_C4'];
            $defaults['C_Total'] = $row['C_Total'];
            $defaults['D_Total'] = $row['D_Total'];
            $defaults['q_2_age_first_noticed_code'] = $row['q_2_age_first_noticed_code'];
            $defaults['q_2_age_first_noticed_code_status'] = $row['q_2_age_first_noticed_code_status'];
            $defaults['q_4_onset_as_perceived_code'] = $row['q_4_onset_as_perceived_code'];
            $defaults['q_4_onset_as_perceived_code_status'] = $row['q_4_onset_as_perceived_code_status'];
            $defaults['q_5_first_walked_code'] = $row['q_5_first_walked_code'];
            $defaults['q_5_first_walked_code_status'] = $row['q_5_first_walked_code_status'];
            $defaults['q_6_bladder_daytime_code'] = $row['q_6_bladder_daytime_code'];
            $defaults['q_6_bladder_daytime_code_status'] = $row['q_6_bladder_daytime_code_status'];
            $defaults['q_7_bladder_nighttime_code'] = $row['q_7_bladder_nighttime_code'];
            $defaults['q_7_bladder_nighttime_code_status'] = $row['q_7_bladder_nighttime_code_status'];
            $defaults['q_8_bowel_control_code'] = $row['q_8_bowel_control_code'];
            $defaults['q_8_bowel_control_code_status'] = $row['q_8_bowel_control_code_status'];
            $defaults['q_9_first_single_words_code'] = $row['q_9_first_single_words_code'];
            $defaults['q_9_first_single_words_code_status'] = $row['q_9_first_single_words_code_status'];
            $defaults['q_10_first_phrases_code'] = $row['q_10_first_phrases_code'];
            $defaults['q_10_first_phrases_code_status'] = $row['q_10_first_phrases_code_status'];
            $defaults['q_11_loss_of_language'] = $row['q_11_loss_of_language'];
            $defaults['q_12_level_before_loss_code'] = $row['q_12_level_before_loss_code'];
            $defaults['13_loss_of_spontaneous_use_code'] = $row['13_loss_of_spontaneous_use_code'];
            $defaults['14_loss_of_intent_code'] = $row['14_loss_of_intent_code'];
            $defaults['15_loss_of_syntactical_code'] = $row['15_loss_of_syntactical_code'];
            $defaults['16_loss_of_articulation_code'] = $row['16_loss_of_articulation_code'];
            $defaults['q_17_main_loss_apparent_code'] = $row['q_17_main_loss_apparent_code'];
            $defaults['q_17_main_loss_apparent_code_status'] = $row['q_17_main_loss_apparent_code_status'];
            $defaults['q_18_loss_due_to_illness'] = $row['q_18_loss_due_to_illness'];
            $defaults['q_19_duration_of_loss_code'] = $row['q_19_duration_of_loss_code'];
            $defaults['q_19_duration_of_loss_code_status'] = $row['q_19_duration_of_loss_code_status'];
            $defaults['q_20_loss_of_skills_code'] = $row['q_20_loss_of_skills_code'];
            $defaults['q_21_puposive_hand_movements_code'] = $row['q_21_puposive_hand_movements_code'];
            $defaults['q_22_motor_skills_code'] = $row['q_22_motor_skills_code'];
            $defaults['q_23_self_help_skills_code'] = $row['q_23_self_help_skills_code'];
            $defaults['q_24_constructive_play_code'] = $row['q_24_constructive_play_code'];
            $defaults['q_25_social_engagement_code'] = $row['q_25_social_engagement_code'];
            $defaults['q_26_loss_first_apparent_code'] = $row['q_26_loss_first_apparent_code'];
            $defaults['q_26_loss_first_apparent_code_status'] = $row['q_26_loss_first_apparent_code_status'];
            $defaults['q_27_physical_illness_code'] = $row['q_27_physical_illness_code'];
            $defaults['q_28_duration_of_loss_code'] = $row['q_28_duration_of_loss_code'];
            $defaults['q_28_duration_of_loss_code_status'] = $row['q_28_duration_of_loss_code_status'];
            $defaults['q_29_compreh_simple_current'] = $row['q_29_compreh_simple_current'];
            $defaults['q_29_compreh_simple_most_abnormal'] = $row['q_29_compreh_simple_most_abnormal'];
            $defaults['q_30_overall_level_of_language'] = $row['q_30_overall_level_of_language'];
            $defaults['q_31_use_of_others_body_current_code'] = $row['q_31_use_of_others_body_current_code'];
            $defaults['q_31_use_of_others_body_ever_code'] = $row['q_31_use_of_others_body_ever_code'];
            $defaults['q_32_artic_pronun_current_code'] = $row['q_32_artic_pronun_current_code'];
            $defaults['q_32_artic_pronun_5years_code'] = $row['q_32_artic_pronun_5years_code'];
            $defaults['q_33_stereotyped_utterances_current_code'] = $row['q_33_stereotyped_utterances_current_code'];
            $defaults['q_33_stereotyped_utterances_ever_code'] = $row['q_33_stereotyped_utterances_ever_code'];
            $defaults['q_34_social_verb_chat_current_code'] = $row['q_34_social_verb_chat_current_code'];
            $defaults['q_34_social_verb_chat_ever_code'] = $row['q_34_social_verb_chat_ever_code'];
            $defaults['q_35_recipr_convers_current_code'] = $row['q_35_recipr_convers_current_code'];
            $defaults['q_35_recipr_convers_ever_code'] = $row['q_35_recipr_convers_ever_code'];
            $defaults['q_36_inappropriate_qs_current_code'] = $row['q_36_inappropriate_qs_current_code'];
            $defaults['q_36_inappropriate_qs_ever_code'] = $row['q_36_inappropriate_qs_ever_code'];
            $defaults['q_37_prenominal_reversal_current_code'] = $row['q_37_prenominal_reversal_current_code'];
            $defaults['q_37_prenominal_reversal_ever_code'] = $row['q_37_prenominal_reversal_ever_code'];
            $defaults['q_38_neologisms_current_code'] = $row['q_38_neologisms_current_code'];
            $defaults['q_38_neologisms_ever_code'] = $row['q_38_neologisms_ever_code'];
            $defaults['q_39_verbal_rituals_current_code'] = $row['q_39_verbal_rituals_current_code'];
            $defaults['q_39_verbal_rituals_ever_code'] = $row['q_39_verbal_rituals_ever_code'];
            $defaults['q_40_inton_vol_rhythm_rate_current_code'] = $row['q_40_inton_vol_rhythm_rate_current_code'];
            $defaults['q_40_inton_vol_rhythm_rate_ever_code'] = $row['q_40_inton_vol_rhythm_rate_ever_code'];
            $defaults['q_41_cur_comm_speech_current_code'] = $row['q_41_cur_comm_speech_current_code'];
            $defaults['q_41_cur_comm_speech_at5_code'] = $row['q_41_cur_comm_speech_at5_code'];
            $defaults['q_42_point_express_interest_current_code'] = $row['q_42_point_express_interest_current_code'];
            $defaults['q_42_point_express_inter_most_abnormal_code'] = $row['q_42_point_express_inter_most_abnormal_code'];
            $defaults['q_43_nodding_current_code'] = $row['q_43_nodding_current_code'];
            $defaults['q_43_nodding_most_abnormal_code'] = $row['q_43_nodding_most_abnormal_code'];
            $defaults['q_44_head_shaking_current_code'] = $row['q_44_head_shaking_current_code'];
            $defaults['q_44_head_shaking_most_abnormal_code'] = $row['q_44_head_shaking_most_abnormal_code'];
            $defaults['q_45_conventional_instr_gests_current_code'] = $row['q_45_conventional_instr_gests_current_code'];
            $defaults['q_45_conventional_instr_gests_most_abnormal_code'] = $row['q_45_conventional_instr_gests_most_abnormal_code'];
            $defaults['q_46_attent_voice_current_code'] = $row['q_46_attent_voice_current_code'];
            $defaults['q_46_attent_voice_most_abnormal_code'] = $row['q_46_attent_voice_most_abnormal_code'];
            $defaults['q_47_spont_imit_current_code'] = $row['q_47_spont_imit_current_code'];
            $defaults['q_47_spont_imit_most_abnormal_code'] = $row['q_47_spont_imit_most_abnormal_code'];
            $defaults['q_48_imag_play_current_code'] = $row['q_48_imag_play_current_code'];
            $defaults['q_48_imag_play_most_abnormal_code'] = $row['q_48_imag_play_most_abnormal_code'];
            $defaults['q_49_imag_play_peers_current_code'] = $row['q_49_imag_play_peers_current_code'];
            $defaults['q_49_imag_play_peers_most_abnormal_code'] = $row['q_49_imag_play_peers_most_abnormal_code'];
            $defaults['q_50_direct_gaze_current_code'] = $row['q_50_direct_gaze_current_code'];
            $defaults['q_50_direct_gaze_most_abnormal_code'] = $row['q_50_direct_gaze_most_abnormal_code'];
            $defaults['q_51_social_smiling_current_code'] = $row['q_51_social_smiling_current_code'];
            $defaults['q_51_social_smiling_most_abnormal_code'] = $row['q_51_social_smiling_most_abnormal_code'];
            $defaults['q_52_show_direct_atten_current_code'] = $row['q_52_show_direct_atten_current_code'];
            $defaults['q_52_show_direct_atten_most_abnormal_code'] = $row['q_52_show_direct_atten_most_abnormal_code'];
            $defaults['q_53_offer_share_current_code'] = $row['q_53_offer_share_current_code'];
            $defaults['q_53_offer_share_most_abnormal_code'] = $row['q_53_offer_share_most_abnormal_code'];
            $defaults['q_54_seek_share_enjoy_current_code'] = $row['q_54_seek_share_enjoy_current_code'];
            $defaults['q_54_seek_share_enjoy_most_abnormal_code'] = $row['q_54_seek_share_enjoy_most_abnormal_code'];
            $defaults['q_55_offer_comf_current_code'] = $row['q_55_offer_comf_current_code'];
            $defaults['q_55_offer_comf_most_abnormal_code'] = $row['q_55_offer_comf_most_abnormal_code'];
            $defaults['q_56_qual_social_overts_current_code'] = $row['q_56_qual_social_overts_current_code'];
            $defaults['q_56_qual_social_overts_most_abnormal_code'] = $row['q_56_qual_social_overts_most_abnormal_code'];
            $defaults['q_57_range_facial_expr_current_code'] = $row['q_57_range_facial_expr_current_code'];
            $defaults['q_57_range_facial_expr_most_abnormal_code'] = $row['q_57_range_facial_expr_most_abnormal_code'];
            $defaults['q_58_inappropriate_facial_current_code'] = $row['q_58_inappropriate_facial_current_code'];
            $defaults['q_58_inappropriate_facial_ever_code'] = $row['q_58_inappropriate_facial_ever_code'];
            $defaults['q_59_appropriat_resp_current_code'] = $row['q_59_appropriat_resp_current_code'];
            $defaults['q_59_appropriat_resp_most_abnormal_code'] = $row['q_59_appropriat_resp_most_abnormal_code'];
            $defaults['q_60_init_activities_current_code'] = $row['q_60_init_activities_current_code'];
            $defaults['q_60_init_activities_most_abnormal_code'] = $row['q_60_init_activities_most_abnormal_code'];
            $defaults['q_61_imit_soc_play_current_code'] = $row['q_61_imit_soc_play_current_code'];
            $defaults['q_61_imit_soc_play_most_abnormal_code'] = $row['q_61_imit_soc_play_most_abnormal_code'];
            $defaults['q_62_inter_children_current_code'] = $row['q_62_inter_children_current_code'];
            $defaults['q_62_inter_children_most_abnormal_code'] = $row['q_62_inter_children_most_abnormal_code'];
            $defaults['q_63_resp_approaches_current_code'] = $row['q_63_resp_approaches_current_code'];
            $defaults['q_63_resp_approaches_most_abnormal_code'] = $row['q_63_resp_approaches_most_abnormal_code'];
            $defaults['q_64_group_play_peers_current_code'] = $row['q_64_group_play_peers_current_code'];
            $defaults['q_64_group_play_peers_most_abnormal_code'] = $row['q_64_group_play_peers_most_abnormal_code'];
            $defaults['q_65_friendships_current_code'] = $row['q_65_friendships_current_code'];
            $defaults['q_65_friendships_most_abnormal_code'] = $row['q_65_friendships_most_abnormal_code'];
            $defaults['q_66_soc_disinhibit_current_code'] = $row['q_66_soc_disinhibit_current_code'];
            $defaults['q_66_soc_disinhibit_most_abnormal_code'] = $row['q_66_soc_disinhibit_most_abnormal_code'];
            $defaults['q_67_unusual_preoccupations_current_code'] = $row['q_67_unusual_preoccupations_current_code'];
            $defaults['q_67_unusual_preoccupations_ever_code'] = $row['q_67_unusual_preoccupations_ever_code'];
            $defaults['q_68_circumscr_ints_current_code'] = $row['q_68_circumscr_ints_current_code'];
            $defaults['q_68_circumscr_ints_ever_code'] = $row['q_68_circumscr_ints_ever_code'];
            $defaults['q_69_repet_use_objects_current_code'] = $row['q_69_repet_use_objects_current_code'];
            $defaults['q_69_repet_use_objects_ever_code'] = $row['q_69_repet_use_objects_ever_code'];
            $defaults['q_70_compulsions_rituals_current_code'] = $row['q_70_compulsions_rituals_current_code'];
            $defaults['q_70_compulsions_rituals_ever_code'] = $row['q_70_compulsions_rituals_ever_code'];
            $defaults['q_71_unusual_sens_ints_current_code'] = $row['q_71_unusual_sens_ints_current_code'];
            $defaults['q_71_unusual_sens_ints_ever_code'] = $row['q_71_unusual_sens_ints_ever_code'];
            $defaults['q_72_undo_gen_sens_noise_current_code'] = $row['q_72_undo_gen_sens_noise_current_code'];
            $defaults['q_72_undo_gen_sens_noise_ever_code'] = $row['q_72_undo_gen_sens_noise_ever_code'];
            $defaults['q_73_idiosyncratic_current_code'] = $row['q_73_idiosyncratic_current_code'];
            $defaults['q_73_idiosyncratic_ever_code'] = $row['q_73_idiosyncratic_ever_code'];
            $defaults['q_74_diff_minor_changes_current_code'] = $row['q_74_diff_minor_changes_current_code'];
            $defaults['q_74_diff_minor_changes_ever_code'] = $row['q_74_diff_minor_changes_ever_code'];
            $defaults['q_75_resist_trivial_chng_current_code'] = $row['q_75_resist_trivial_chng_current_code'];
            $defaults['q_75_resist_trivial_chng_ever_code'] = $row['q_75_resist_trivial_chng_ever_code'];
            $defaults['q_76_unus_attach_objects_current_code'] = $row['q_76_unus_attach_objects_current_code'];
            $defaults['q_76_unus_attach_objects_ever_code'] = $row['q_76_unus_attach_objects_ever_code'];
            $defaults['q_77_hands_finger_manners_current_code'] = $row['q_77_hands_finger_manners_current_code'];
            $defaults['q_77_hands_finger_manners_ever_code'] = $row['q_77_hands_finger_manners_ever_code'];
            $defaults['q_78_oth_complex_manners_current_code'] = $row['q_78_oth_complex_manners_current_code'];
            $defaults['q_78_oth_complex_manners_ever_code'] = $row['q_78_oth_complex_manners_ever_code'];
            $defaults['q_79_midline_hand_moves_current_code'] = $row['q_79_midline_hand_moves_current_code'];
            $defaults['q_79_midline_hand_moves_ever_code'] = $row['q_79_midline_hand_moves_ever_code'];
            $defaults['q_80_gait_current_code'] = $row['q_80_gait_current_code'];
            $defaults['q_80_gait_most_abnormal_code'] = $row['q_80_gait_most_abnormal_code'];
            $defaults['q_81_aggress_caregivers_current_code'] = $row['q_81_aggress_caregivers_current_code'];
            $defaults['q_81_aggress_caregivers_ever_code'] = $row['q_81_aggress_caregivers_ever_code'];
            $defaults['q_82_aggress_noncaregivers_current_code'] = $row['q_82_aggress_noncaregivers_current_code'];
            $defaults['q_82_aggress_noncaregivers_ever_code'] = $row['q_82_aggress_noncaregivers_ever_code'];
            $defaults['q_83_self_injury_current_code'] = $row['q_83_self_injury_current_code'];
            $defaults['q_83_self_injury_ever_code'] = $row['q_83_self_injury_ever_code'];
            $defaults['q_84_hyperventilation_current_code'] = $row['q_84_hyperventilation_current_code'];
            $defaults['q_84_hyperventilation_ever_code'] = $row['q_84_hyperventilation_ever_code'];
            $defaults['q_85_faints_fits_blackouts_current_code'] = $row['q_85_faints_fits_blackouts_current_code'];
            $defaults['q_85_faints_fits_blackouts_ever_code'] = $row['q_85_faints_fits_blackouts_ever_code'];
            $defaults['q_86_age_when_abnormality_first_evident'] = $row['q_86_age_when_abnormality_first_evident'];
            $defaults['q_87_interviewers_judgment'] = $row['q_87_interviewers_judgment'];
            $defaults['q_87_interviewers_judgment_status'] = $row['q_87_interviewers_judgment_status'];
            $defaults['q_88_visuospatial_ability_current_code'] = $row['q_88_visuospatial_ability_current_code'];
            $defaults['q_88_visuospatial_ability_ever_code'] = $row['q_88_visuospatial_ability_ever_code'];
            $defaults['q_89_memory_still_current_code'] = $row['q_89_memory_still_current_code'];
            $defaults['q_89_memory_still_ever_code'] = $row['q_89_memory_still_ever_code'];
            $defaults['q_90_musical_ability_current_code'] = $row['q_90_musical_ability_current_code'];
            $defaults['q_90_musical_ability_ever_code'] = $row['q_90_musical_ability_ever_code'];
            $defaults['q_91_drawings_skill_current_code'] = $row['q_91_drawings_skill_current_code'];
            $defaults['q_91_drawings_skill_ever_code'] = $row['q_91_drawings_skill_ever_code'];
            $defaults['q_92_reading_ability_current_code'] = $row['q_92_reading_ability_current_code'];
            $defaults['q_92_reading_ability_ever_code'] = $row['q_92_reading_ability_ever_code'];
            $defaults['q_93_computational_ability_current_code'] = $row['q_93_computational_ability_current_code'];
            $defaults['q_93_computational_ability_ever_code'] = $row['q_93_computational_ability_ever_code'];

            // Set the date
            //  $date = explode('-', $row['aMRI_date']);
            //  $defaults['aMRI_date']['Y'] = $date[0];
            //  $defaults['aMRI_date']['M'] = $date[1];
            //  $defaults['aMRI_date']['d'] = $date[2];

        } else {
            echo("Identifer empty! No ID has been chosen. Please contact Samir at the DCC.<br>");
        }

        return $defaults;
    }

   
    function score(){

        //holds raw question values
        $score_record = array();
       
        //holds calculated
        $db =& Database::singleton();

        // null scores
        //$this->_nullScores();
       
        //Get values from both tables of adi_r (reliability and original)
        $query = "SELECT * FROM adi_r_reliability WHERE CommentID='".$this->identifier."'";
        $query1 = "SELECT * FROM adi_r_proband WHERE CommentID='".$this->identifier."'";
        $query2 = "SELECT * FROM adi_r_reliability_lookup WHERE CommentID='standard_adir_SEA0012'";
        $query3 = "SELECT * FROM adi_r_reliability_lookup WHERE CommentID='standard_adir_SEA0070'";


        $db->selectRow($query, $score_record);
              
        $db->selectRow($query1, $score_record1);
        
        $db->selectRow($query2, $score_record2);
        
        $db->selectRow($query3, $score_record3);
        
     
        // If the reliability is to be compared to the gold standard
        if ($score_record['Gold_standard']=='Gold_standard_SEA0012'){
            echo("This is the Gold standard check for SEA0012<br>");
                
            $reliability_count_raw=0;            
            $reliability_count_scored=0;            
            $denominator=0;
            $denominator_scored=0;


            if($score_record['q_2_age_first_noticed_code']=='8' AND $score_record2['q_2_age_first_noticed_code']=='8'){}
            elseif ($score_record['q_2_age_first_noticed_code']=='998' && $score_record2['q_2_age_first_noticed_code']=='998'){}
            else {
                $denominator++; $denominator_scored++; echo('q2 is neither 8 or 998 for both entries<br>');
                if(abs($score_record2['q_2_age_first_noticed_code'] - $score_record['q_2_age_first_noticed_code']) >3){$reliability_count_raw++; $reliability_count_scored++;}}
            
            if($score_record['q_4_onset_as_perceived_code']=='8' AND $score_record2['q_4_onset_as_perceived_code']=='8'){}
            elseif($score_record['q_4_onset_as_perceived_code']=='998' AND $score_record2['q_4_onset_as_perceived_code']=='998'){}
            else {
                $denominator++; echo('q4 is neither 8 or 998 for both entries<br>');
                if ($score_record['q_4_onset_as_perceived_code'] != $score_record2['q_4_onset_as_perceived_code']) { $reliability_count_raw++;}}
            
            if($score_record['q_5_first_walked_code']=='8' AND $score_record2['q_5_first_walked_code']=='8'){}
            elseif($score_record['q_5_first_walked_code']=='998' && $score_record2['q_5_first_walked_code']=='998'){}
            else {
                $denominator++;echo('q5 is neither 8 or 998 for both entries<br>');
                if (abs($score_record['q_5_first_walked_code'] - $score_record2['q_5_first_walked_code']) >3) { $reliability_count_raw++;}} 
            
            if($score_record['q_6_bladder_daytime_code'] =='8' AND $score_record2['q_6_bladder_daytime_code']=='8'){}
            elseif($score_record['q_6_bladder_daytime_code']=='998' && $score_record2['q_6_bladder_daytime_code']=='998'){}
            else {
                $denominator++;echo('q6 is neither 8 or 998 for both entries<br>');
                if (abs($score_record['q_6_bladder_daytime_code'] - $score_record2['q_6_bladder_daytime_code']) >3){ $reliability_count_raw++;}}
            
            if($score_record['q_7_bladder_nighttime_code'] =='8' AND $score_record2['q_7_bladder_nighttime_code']=='8'){}
            elseif($score_record['q_7_bladder_nighttime_code'] =='998' && $score_record2['q_7_bladder_nighttime_code']=='998'){}
            else {
                $denominator++;echo('q7 is neither 8 or 998 for both entries<br>');
                if (abs($score_record['q_7_bladder_nighttime_code'] - $score_record2['q_7_bladder_nighttime_code']) >3){ $reliability_count_raw++;}} 
            if($score_record['q_8_bowel_control_code'] =='8' AND $score_record2['control']=='8'){}
            elseif($score_record['q_8_bowel_control_code'] =='998' && $score_record2['control']=='998'){}
            else {
                $denominator++;echo('q8 is neither 8 or 998 for both entries<br>');
                if (abs($score_record['q_8_bowel_control_code'] - $score_record2['q_8_bowel_control_code']) >3){ $reliability_count_raw++;}} 
            if($score_record['q_9_first_single_words_code'] =='8' AND $score_record2['q_9_first_single_words_code']=='8'){}
            elseif($score_record['q_9_first_single_words_code']=='998' && $score_record2['q_9_first_single_words_code']=='998'){}
            else {
                $denominator++; $denominator_scored++; echo('q9 is neither 8 or 998 for both entries<br>');
                if (abs($score_record['q_9_first_single_words_code'] - $score_record2['q_9_first_single_words_code']) >3){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_10_first_phrases_code'] =='8' AND $score_record2['q_10_first_phrases_code']=='8'){}
            elseif($score_record['q_10_first_phrases_code']=='998' && $score_record2['q_10_first_phrases_code']=='998'){}
            else {
                $denominator++; $denominator_scored++; echo('q10 is neither 8 or 998 for both entries<br>');
                if (abs($score_record['q_10_first_phrases_code'] - $score_record2['q_10_first_phrases_code']) >3){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if ($score_record['q_11_loss_of_language'] =='8_NA' AND $score_record2['q_11_loss_of_language']=='8_NA'){}
            elseif($score_record['q_10_first_phrases_code']=='998' && $score_record2['q_11_loss_of_language']=='998'){}
            else {                    
                $denominator++;echo('q11 is neither 8 or 998 for both entries<br>');
                if($score_record['q_11_loss_of_language']  != $score_record2['q_11_loss_of_language']){ $reliability_count_raw++;}} 
           
            if($score_record['q_12_level_before_loss_code'] =='8_insufficient' AND $score_record2['q_12_level_before_loss_code']=='8_insufficient'){}
            elseif($score_record['q_12_level_before_loss_code'] =='998' && $score_record2['q_12_level_before_loss_code']=='998'){}
            else {
                $denominator++;echo('q12 is neither 8 or 998 for both entries<br>');
                if ($score_record['q_12_level_before_loss_code'] != $score_record2['q_12_level_before_loss_code']){ $reliability_count_raw++;}} 
            if($score_record['13_loss_of_spontaneous_use_code'] =='8_insufficient' AND $score_record2['13_loss_of_spontaneous_use_code']=='8_insufficient'){}
            elseif($score_record['13_loss_of_spontaneous_use_code']=='998' && $score_record2['13_loss_of_spontaneous_use_code']=='998'){}
            else {
                $denominator++;echo('q13 is neither 8 or 998 for both entries<br>');
                if ($score_record['13_loss_of_spontaneous_use_code'] != $score_record2['13_loss_of_spontaneous_use_code']){ $reliability_count_raw++;}} 
            if($score_record['14_loss_of_intent_code'] =='8_insufficient' AND $score_record2['14_loss_of_intent_code']=='8_insufficient'){}
            elseif($score_record['14_loss_of_intent_code'] =='998' && $score_record2['14_loss_of_intent_code']=='998'){}
            else {
                $denominator++;echo('q14 is neither 8 or 998 for both entries<br>');
                if ($score_record['14_loss_of_intent_code'] != $score_record2['14_loss_of_intent_code']){ $reliability_count_raw++;}} 
            if($score_record['15_loss_of_syntactical_code'] =='8_insufficient' AND $score_record2['15_loss_of_syntactical_code']=='8_insufficient'){}
            elseif($score_record['15_loss_of_syntactical_code'] =='998' && $score_record2['15_loss_of_syntactical_code']=='998'){}
            else {
                $denominator++;echo('q15 is neither 8 or 998 for both entries<br>');
                if ($score_record['15_loss_of_syntactical_code'] != $score_record2['15_loss_of_syntactical_code']){ $reliability_count_raw++;}} 
            if($score_record['16_loss_of_articulation_code'] =='8_insufficient' AND $score_record2['16_loss_of_articulation_code']=='8_insufficient'){}
            elseif($score_record['16_loss_of_articulation_code'] =='998' && $score_record2['16_loss_of_articulation_code']=='998'){}
            else {
                $denominator++;echo('q16 is neither 8 or 998 for both entries<br>');
                if ($score_record['16_loss_of_articulation_code'] != $score_record2['16_loss_of_articulation_code']){ $reliability_count_raw++;}} 
            if($score_record['q_17_main_loss_apparent_code'] =='8' AND $score_record2['q_17_main_loss_apparent_code']=='8'){}
            elseif($score_record['q_17_main_loss_apparent_code'] =='998' && $score_record2['q_17_main_loss_apparent_code']=='998'){}
            else {
                $denominator++;echo('q17 is neither 8 or 998 for both entries<br>');
                if (abs($score_record['q_17_main_loss_apparent_code'] - $score_record2['q_17_main_loss_apparent_code']) >3){ $reliability_count_raw++;}} 
            if($score_record['q_18_loss_due_to_illness'] =='8_no_loss' AND $score_record2['q_18_loss_due_to_illness']=='8_no_loss'){}
            elseif($score_record['q_18_loss_due_to_illness'] =='998' && $score_record2['q_18_loss_due_to_illness']=='998'){}
            else {
                $denominator++;echo('q18 is neither 8 or 998 for both entries<br>');
                if ($score_record['q_18_loss_due_to_illness'] != $score_record2['q_18_loss_due_to_illness']){ $reliability_count_raw++;}} 
            
            if($score_record['q_19_duration_of_loss_code'] =='8' AND $score_record2['q_19_duration_of_loss_code']=='8'){}
            elseif($score_record['q_19_duration_of_loss_code'] =='998' && $score_record2['q_19_duration_of_loss_code']=='998'){}
            else {
                $denominator++;echo('q19 is neither 8 or 998 for both entries<br>');
                if (abs($score_record['q_19_duration_of_loss_code'] - $score_record2['q_19_duration_of_loss_code']) >3){ $reliability_count_raw++;}} 
                        
            if($score_record['q_20_loss_of_skills_code'] =='8_NA' AND $score_record2['q_20_loss_of_skills_code']=='8_NA'){}
            elseif($score_record['q_20_loss_of_skills_code'] =='998' && $score_record2['q_20_loss_of_skills_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_20_loss_of_skills_code'] != $score_record2['q_20_loss_of_skills_code']){ $reliability_count_raw++;}} 
            if($score_record['q_21_puposive_hand_movements_code'] =='8_NA' AND $score_record2['q_21_puposive_hand_movements_code']=='8_NA'){}
            elseif($score_record['q_21_puposive_hand_movements_code'] =='998' && $score_record2['q_21_puposive_hand_movements_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_21_puposive_hand_movements_code'] != $score_record2['q_21_puposive_hand_movements_code']){ $reliability_count_raw++;}} 
            if($score_record['q_22_motor_skills_code'] =='8_NA' AND $score_record2['q_22_motor_skills_code']=='8_NA'){}
            elseif($score_record['q_22_motor_skills_code'] =='998' && $score_record2['q_22_motor_skills_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_22_motor_skills_code'] != $score_record2['q_22_motor_skills_code']){ $reliability_count_raw++;}} 
            if($score_record['q_23_self_help_skills_code'] =='8_NA' AND $score_record2['q_23_self_help_skills_code']=='8_NA'){}
            elseif($score_record['q_23_self_help_skills_code'] =='998' && $score_record2['q_23_self_help_skills_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_23_self_help_skills_code'] != $score_record2['q_23_self_help_skills_code']){ $reliability_count_raw++;}} 
            if($score_record['q_24_constructive_play_code'] =='8_NA' AND $score_record2['q_24_constructive_play_code']=='8_NA'){}
            elseif($score_record['q_24_constructive_play_code'] =='998' && $score_record2['q_24_constructive_play_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_24_constructive_play_code'] != $score_record2['q_24_constructive_play_code']){ $reliability_count_raw++;}} 
            if($score_record['q_25_social_engagement_code'] =='8_NA' AND $score_record2['q_25_social_engagement_code']=='8_NA'){}
            elseif($score_record['q_25_social_engagement_code'] =='998' && $score_record2['q_25_social_engagement_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_25_social_engagement_code'] != $score_record2['q_25_social_engagement_code']){ $reliability_count_raw++;}} 
            if($score_record['q_26_loss_first_apparent_code'] =='8' AND $score_record2['q_26_loss_first_apparent_code']=='8'){}
            elseif($score_record['q_26_loss_first_apparent_code']=='998' && $score_record2['q_26_loss_first_apparent_code']=='998'){}
            else {
                $denominator++;
                if (abs($score_record['q_26_loss_first_apparent_code'] - $score_record2['q_26_loss_first_apparent_code']) >3){ $reliability_count_raw++;}} 
            if($score_record['q_27_physical_illness_code'] =='8_no_loss' AND $score_record2['q_27_physical_illness_code']=='8_no_loss'){}
            elseif($score_record['q_27_physical_illness_code'] =='998' && $score_record2['q_27_physical_illness_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_27_physical_illness_code'] != $score_record2['q_27_physical_illness_code']){ $reliability_count_raw++;}} 
            if($score_record['q_28_duration_of_loss_code'] =='8' AND $score_record2['q_28_duration_of_loss_code']=='8'){}
            elseif($score_record['q_28_duration_of_loss_code']=='998' && $score_record2['q_28_duration_of_loss_code']=='998'){}
            else {
                $denominator++;
                if (abs($score_record['q_28_duration_of_loss_code'] - $score_record2['q_28_duration_of_loss_code']) >3){ $reliability_count_raw++;}} 
            if($score_record['q_29_compreh_simple_current'] =='8_NA' AND $score_record2['q_29_compreh_simple_current']=='8_NA'){}
            elseif($score_record['q_29_compreh_simple_current'] =='998' && $score_record2['q_29_compreh_simple_current']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_29_compreh_simple_current'] != $score_record2['q_29_compreh_simple_current']){ $reliability_count_raw++;}} 
            if($score_record['q_29_compreh_simple_most_abnormal'] =='8_NA' AND $score_record2['q_29_compreh_simple_most_abnormal']=='8_NA'){}
            elseif($score_record['q_29_compreh_simple_most_abnormal'] =='998' && $score_record2['q_29_compreh_simple_most_abnormal']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_29_compreh_simple_most_abnormal'] != $score_record2['q_29_compreh_simple_most_abnormal']){ $reliability_count_raw++;}} 
            if($score_record['q_30_overall_level_of_language'] =='8_NA' AND $score_record2['q_30_overall_level_of_language']=='8_NA'){}
            elseif($score_record['q_30_overall_level_of_language'] =='998' && $score_record2['q_30_overall_level_of_language']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_30_overall_level_of_language'] != $score_record2['q_30_overall_level_of_language']){ $reliability_count_raw++;}} 
            if($score_record['q_31_use_of_others_body_current_code'] =='8_little' AND $score_record2['q_31_use_of_others_body_current_code']=='8_little'){}
            elseif($score_record['q_31_use_of_others_body_current_code'] =='998' && $score_record2['q_31_use_of_others_body_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_31_use_of_others_body_current_code'] != $score_record2['q_31_use_of_others_body_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_31_use_of_others_body_ever_code'] =='8_little' AND $score_record2['q_31_use_of_others_body_ever_code']=='8_little'){}
            elseif($score_record['q_31_use_of_others_body_ever_code'] =='998' && $score_record2['q_31_use_of_others_body_ever_code']=='998'){}
            else {
                $denominator++; $denominator_scored++;
                if ($score_record['q_31_use_of_others_body_ever_code'] != $score_record2['q_31_use_of_others_body_ever_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_32_artic_pronun_current_code'] =='8_NA' AND $score_record2['q_32_artic_pronun_current_code']=='8_NA'){}
            elseif($score_record['q_32_artic_pronun_current_code'] =='998' && $score_record2['q_32_artic_pronun_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_32_artic_pronun_current_code'] != $score_record2['q_32_artic_pronun_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_32_artic_pronun_5years_code'] =='8_NA' AND $score_record2['q_32_artic_pronun_5years_code']=='8_NA'){}
            elseif($score_record['q_32_artic_pronun_5years_code'] =='998' && $score_record2['q_32_artic_pronun_5years_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_32_artic_pronun_5years_code'] != $score_record2['q_32_artic_pronun_5years_code']){ $reliability_count_raw++;}} 
            if($score_record['q_33_stereotyped_utterances_current_code'] =='8_NA' AND $score_record2['q_33_stereotyped_utterances_current_code']=='8_NA'){}
            elseif($score_record['q_33_stereotyped_utterances_current_code'] =='998' && $score_record2['q_33_stereotyped_utterances_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_33_stereotyped_utterances_current_code'] != $score_record2['q_33_stereotyped_utterances_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_33_stereotyped_utterances_ever_code'] =='8_NA' AND $score_record2['q_33_stereotyped_utterances_ever_code']=='8_NA'){}
            elseif($score_record['q_33_stereotyped_utterances_ever_code'] =='998' && $score_record2['q_33_stereotyped_utterances_ever_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if ($score_record['q_33_stereotyped_utterances_ever_code'] != $score_record2['q_33_stereotyped_utterances_ever_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_34_social_verb_chat_current_code'] =='8_NA' AND $score_record2['q_34_social_verb_chat_current_code']=='8_NA'){}
            elseif($score_record['q_34_social_verb_chat_current_code'] =='998' && $score_record2['q_34_social_verb_chat_current_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if ($score_record['q_34_social_verb_chat_current_code'] != $score_record2['q_34_social_verb_chat_current_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_34_social_verb_chat_ever_code'] =='8_NA' AND $score_record2['q_34_social_verb_chat_current_code']=='8_NA'){}
            elseif($score_record['q_34_social_verb_chat_ever_code'] =='998' && $score_record2['q_34_social_verb_chat_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_34_social_verb_chat_ever_code'] != $score_record2['q_34_social_verb_chat_ever_code']){ $reliability_count_raw++;}} 
            if($score_record['q_35_recipr_convers_current_code'] =='8_NA' AND $score_record2['q_35_recipr_convers_current_code']=='8_NA'){}
            elseif($score_record['q_35_recipr_convers_current_code'] =='998' && $score_record2['q_35_recipr_convers_current_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if ($score_record['q_35_recipr_convers_current_code'] != $score_record2['q_35_recipr_convers_current_code']){ $reliability_count_raw++; $reliability_count_scored++;}}
            if($score_record['q_35_recipr_convers_ever_code'] =='8_NA' AND $score_record2['q_35_recipr_convers_ever_code']=='8_NA'){}
            elseif($score_record['q_35_recipr_convers_ever_code'] =='998' && $score_record2['q_35_recipr_convers_ever_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_35_recipr_convers_ever_code'] != $score_record2['q_35_recipr_convers_ever_code']){ $reliability_count_raw++;}} 
            if($score_record['q_36_inappropriate_qs_current_code'] =='8_NA' AND $score_record2['q_36_inappropriate_qs_current_code']=='8_NA'){}
            elseif($score_record['q_36_inappropriate_qs_current_code'] =='998' && $score_record2['q_36_inappropriate_qs_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_36_inappropriate_qs_current_code'] != $score_record2['q_36_inappropriate_qs_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_36_inappropriate_qs_ever_code'] =='8_NA' AND $score_record2['q_36_inappropriate_qs_ever_code']=='8_NA'){}
            elseif($score_record['q_36_inappropriate_qs_ever_code'] =='998' && $score_record2['q_36_inappropriate_qs_ever_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if ($score_record['q_36_inappropriate_qs_ever_code'] != $score_record2['q_36_inappropriate_qs_ever_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_37_prenominal_reversal_current_code'] =='8_NA' AND $score_record2['q_37_prenominal_reversal_current_code']=='8_NA'){}
            elseif($score_record['q_37_prenominal_reversal_current_code'] =='998' && $score_record2['q_37_prenominal_reversal_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_37_prenominal_reversal_current_code'] != $score_record2['q_37_prenominal_reversal_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_37_prenominal_reversal_ever_code'] =='8_NA' AND $score_record2['q_37_prenominal_reversal_ever_code']=='8_NA'){}
            elseif($score_record['q_37_prenominal_reversal_ever_code'] =='998' && $score_record2['q_37_prenominal_reversal_ever_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if ($score_record['q_37_prenominal_reversal_ever_code'] != $score_record2['q_37_prenominal_reversal_ever_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_38_neologisms_current_code'] =='8_NA' AND $score_record2['q_38_neologisms_current_code']=='8_NA'){}
            elseif($score_record['q_38_neologisms_current_code'] =='998' && $score_record2['q_38_neologisms_current_code']=='998'){}
            else {
                    $denominator++;
                    if ($score_record['q_38_neologisms_current_code'] != $score_record2['q_38_neologisms_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_38_neologisms_ever_code'] =='8_NA' AND $score_record2['q_38_neologisms_ever_code']=='8_NA'){}
            elseif($score_record['q_38_neologisms_ever_code'] =='998' && $score_record2['q_38_neologisms_ever_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if ($score_record['q_38_neologisms_ever_code'] != $score_record2['q_38_neologisms_ever_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_39_verbal_rituals_current_code'] =='8_NA' AND $score_record2['q_39_verbal_rituals_current_code']=='8_NA'){}
            elseif($score_record['q_39_verbal_rituals_current_code'] =='998' && $score_record2['q_39_verbal_rituals_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_39_verbal_rituals_current_code'] != $score_record2['q_39_verbal_rituals_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_39_verbal_rituals_ever_code'] =='8_NA' AND $score_record2['q_39_verbal_rituals_ever_code']=='8_NA'){}
            elseif($score_record['q_39_verbal_rituals_ever_code'] =='998' && $score_record2['q_39_verbal_rituals_ever_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if ($score_record['q_39_verbal_rituals_ever_code'] != $score_record2['q_39_verbal_rituals_ever_code']){ $reliability_count_raw++; $reliability_count_scored++;}}
            if($score_record['q_40_inton_vol_rhythm_rate_current_code'] =='8_NA' AND $score_record2['q_40_inton_vol_rhythm_rate_current_code']=='8_NA'){}
                elseif($score_record['q_40_inton_vol_rhythm_rate_current_code'] =='998' && $score_record2['q_40_inton_vol_rhythm_rate_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_40_inton_vol_rhythm_rate_current_code'] != $score_record2['q_40_inton_vol_rhythm_rate_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_40_inton_vol_rhythm_rate_ever_code'] =='8_NA' AND $score_record2['q_40_inton_vol_rhythm_rate_ever_code']=='8_NA'){}
            elseif($score_record['q_40_inton_vol_rhythm_rate_ever_code'] =='998' && $score_record2['q_40_inton_vol_rhythm_rate_ever_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_40_inton_vol_rhythm_rate_ever_code'] != $score_record2['q_40_inton_vol_rhythm_rate_ever_code']){ $reliability_count_raw++;}} 
            if($score_record['q_41_cur_comm_speech_current_code'] =='8_NA' AND $score_record2['q_41_cur_comm_speech_current_code']=='8_NA'){}
            elseif($score_record['q_41_cur_comm_speech_current_code'] =='998' && $score_record2['q_41_cur_comm_speech_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_41_cur_comm_speech_current_code'] != $score_record2['q_41_cur_comm_speech_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_41_cur_comm_speech_at5_code'] =='8_NA' AND $score_record2['q_41_cur_comm_speech_at5_code']=='8_NA'){}
            elseif($score_record['q_41_cur_comm_speech_at5_code'] =='998' && $score_record2['q_41_cur_comm_speech_at5_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_41_cur_comm_speech_at5_code'] != $score_record2['q_41_cur_comm_speech_at5_code']){ $reliability_count_raw++;}} 
            if($score_record['q_42_point_express_interest_current_code'] =='8_NA' AND $score_record2['q_42_point_express_interest_current_code']=='8_NA'){}
            elseif($score_record['q_42_point_express_interest_current_code'] =='998' && $score_record2['q_42_point_express_interest_current_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;echo('q42 is neither 8 or 998 for both entries<br>');
                if ($score_record['q_42_point_express_interest_current_code'] != $score_record2['q_42_point_express_interest_current_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_42_point_express_inter_most_abnormal_code'] =='8_NA' AND $score_record2['q_42_point_express_inter_most_abnormal_code']=='8_NA'){}
            elseif($score_record['q_42_point_express_inter_most_abnormal_code'] =='998' && $score_record2['q_42_point_express_inter_most_abnormal_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_42_point_express_inter_most_abnormal_code'] != $score_record2['q_42_point_express_inter_most_abnormal_code']){ $reliability_count_raw++;}} 
            if($score_record['q_43_nodding_current_code'] =='8_NA' AND $score_record2['q_43_nodding_current_code']=='8_NA'){}
            elseif($score_record['q_43_nodding_current_code'] =='998' && $score_record2['q_43_nodding_current_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if ($score_record['q_43_nodding_current_code'] != $score_record2['q_43_nodding_current_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_43_nodding_most_abnormal_code'] =='8_NA' AND $score_record2['q_43_nodding_most_abnormal_code']=='8_NA'){}
            elseif($score_record['q_43_nodding_most_abnormal_code'] =='998' && $score_record2['q_43_nodding_most_abnormal_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_43_nodding_most_abnormal_code'] != $score_record2['q_43_nodding_most_abnormal_code']){ $reliability_count_raw++;}} 
            if($score_record['q_44_head_shaking_current_code'] =='8_NA' AND $score_record2['q_44_head_shaking_current_code']=='8_NA'){}
            elseif($score_record['q_44_head_shaking_current_code'] =='998' && $score_record2['q_44_head_shaking_current_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if ($score_record['q_44_head_shaking_current_code'] != $score_record2['q_44_head_shaking_current_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_44_head_shaking_most_abnormal_code'] =='8_NA' AND $score_record2['q_44_head_shaking_most_abnormal_code']=='8_NA'){}
            elseif($score_record['q_44_head_shaking_most_abnormal_code'] =='998' && $score_record2['q_44_head_shaking_most_abnormal_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_44_head_shaking_most_abnormal_code'] != $score_record2['q_44_head_shaking_most_abnormal_code']){ $reliability_count_raw++;}} 
            if($score_record['q_45_conventional_instr_gests_current_code'] =='8_NA' AND $score_record2['q_45_conventional_instr_gests_current_code']=='8_NA'){}
            elseif($score_record['q_45_conventional_instr_gests_current_code'] =='998' && $score_record2['q_45_conventional_instr_gests_current_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if ($score_record['q_45_conventional_instr_gests_current_code'] != $score_record2['q_45_conventional_instr_gests_current_code']){ $reliability_count_raw++; $reliability_count_scored++;}}              
            if($score_record['q_45_conventional_instr_gests_most_abnormal_code'] =='8_NA' AND $score_record2['q_45_conventional_instr_gests_most_abnormal_code']=='8_NA'){}
            elseif($score_record['q_45_conventional_instr_gests_most_abnormal_code'] =='998' && $score_record2['q_45_conventional_instr_gests_most_abnormal_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_45_conventional_instr_gests_most_abnormal_code'] != $score_record2['q_45_conventional_instr_gests_most_abnormal_code']){ $reliability_count_raw++;}} 
            if($score_record['q_46_attent_voice_current_code'] =='8_NA' AND $score_record2['q_46_attent_voice_current_code']=='8_NA'){}
            elseif($score_record['q_46_attent_voice_current_code'] =='998' && $score_record2['q_46_attent_voice_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_46_attent_voice_current_code'] != $score_record2['q_46_attent_voice_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_46_attent_voice_most_abnormal_code'] =='8_NA' AND $score_record2['q_46_attent_voice_most_abnormal_code']=='8_NA'){}
            elseif($score_record['q_46_attent_voice_most_abnormal_code'] =='998' && $score_record2['q_46_attent_voice_most_abnormal_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_46_attent_voice_most_abnormal_code'] != $score_record2['q_46_attent_voice_most_abnormal_code']){ $reliability_count_raw++;}} 
            if($score_record['q_47_spont_imit_current_code'] =='8_NA' AND $score_record2['q_47_spont_imit_current_code']=='8_NA'){}
            elseif($score_record['q_47_spont_imit_current_code'] =='998' && $score_record2['q_47_spont_imit_current_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if ($score_record['q_47_spont_imit_current_code'] != $score_record2['q_47_spont_imit_current_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_47_spont_imit_most_abnormal_code'] =='8_NA' AND $score_record2['q_47_spont_imit_most_abnormal_code']=='8_NA'){}
            elseif($score_record['q_47_spont_imit_most_abnormal_code'] =='998' && $score_record2['q_47_spont_imit_most_abnormal_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_47_spont_imit_most_abnormal_code'] != $score_record2['q_47_spont_imit_most_abnormal_code']){ $reliability_count_raw++;}} 
            
            
            if($score_record['q_48_imag_play_current_code'] =='8_NA' AND $score_record2['q_48_imag_play_current_code']=='8_NA'){}
            elseif($score_record['q_48_imag_play_current_code'] =='998' && $score_record2['q_48_imag_play_current_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;echo('q48cur is neither 8 or 998 for both entries<br>');
                if ($score_record['q_48_imag_play_current_code'] != $score_record2['q_48_imag_play_current_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
           
            
            if($score_record['q_48_imag_play_most_abnormal_code'] =='8_NA' AND $score_record2['q_48_imag_play_most_abnormal_code']=='8_NA'){}
            elseif($score_record['q_48_imag_play_most_abnormal_code'] =='998' && $score_record2['q_48_imag_play_most_abnormal_code']=='998'){}
            else {
                $denominator++;echo('q48abn is neither 8 or 998 for both entries<br>');
            if ($score_record['q_48_imag_play_most_abnormal_code'] != $score_record2['q_48_imag_play_most_abnormal_code']){ $reliability_count_raw++;}} 
            
            
            if($score_record['q_49_imag_play_peers_current_code'] =='8_NA' AND $score_record2['q_49_imag_play_peers_current_code']=='8_NA'){}
            elseif($score_record['q_49_imag_play_peers_current_code'] =='998' && $score_record2['q_49_imag_play_peers_current_code']=='998'){}
            else {
                $denominator++;echo('q49curr is neither 8 or 998 for both entries<br>');
                if ($score_record['q_49_imag_play_peers_current_code'] != $score_record2['q_49_imag_play_peers_current_code']){ $reliability_count_raw++;}} 
            
            if($score_record['q_49_imag_play_peers_most_abnormal_code'] =='8_NA' AND $score_record2['q_49_imag_play_peers_most_abnormal_code']=='8_NA'){}
            elseif($score_record['q_49_imag_play_peers_most_abnormal_code'] =='998' && $score_record2['q_49_imag_play_peers_most_abnormal_code']=='998'){}
            else {
                $denominator++;echo('q49abn is neither 8 or 998 for both entries<br>');
                if ($score_record['q_49_imag_play_peers_most_abnormal_code'] != $score_record2['q_49_imag_play_peers_most_abnormal_code']){ $reliability_count_raw++;}} 

            if($score_record['q_50_direct_gaze_current_code'] =='8_NA' AND $score_record2['q_50_direct_gaze_current_code']=='8_NA'){}
            elseif($score_record['q_50_direct_gaze_current_code'] =='998' && $score_record2['q_50_direct_gaze_current_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if ($score_record['q_50_direct_gaze_current_code'] != $score_record2['q_50_direct_gaze_current_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_50_direct_gaze_most_abnormal_code'] =='8_NA' AND $score_record2['q_50_direct_gaze_most_abnormal_code']=='8_NA'){}
            elseif($score_record['q_50_direct_gaze_most_abnormal_code'] =='998' && $score_record2['q_50_direct_gaze_most_abnormal_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_50_direct_gaze_most_abnormal_code'] != $score_record2['q_50_direct_gaze_most_abnormal_code']){ $reliability_count_raw++;}} 
            if($score_record['q_51_social_smiling_current_code'] =='8_NA' AND $score_record2['q_51_social_smiling_current_code']=='8_NA'){}
            elseif($score_record['q_51_social_smiling_current_code'] =='998' && $score_record2['q_51_social_smiling_current_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if ($score_record['q_51_social_smiling_current_code'] != $score_record2['q_51_social_smiling_current_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_51_social_smiling_most_abnormal_code'] =='8_NA' AND $score_record2['q_51_social_smiling_most_abnormal_code']=='8_NA'){}
            elseif($score_record['q_51_social_smiling_most_abnormal_code'] =='998' && $score_record2['q_51_social_smiling_most_abnormal_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_51_social_smiling_most_abnormal_code'] != $score_record2['q_51_social_smiling_most_abnormal_code']){ $reliability_count_raw++;}} 
            if($score_record['q_52_show_direct_atten_current_code'] =='8_NA' AND $score_record2['q_52_show_direct_atten_current_code']=='8_NA'){}
            elseif($score_record['q_52_show_direct_atten_current_code'] =='998' && $score_record2['q_52_show_direct_atten_current_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if ($score_record['q_52_show_direct_atten_current_code'] != $score_record2['q_52_show_direct_atten_current_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_52_show_direct_atten_most_abnormal_code'] =='8_NA' AND $score_record2['q_52_show_direct_atten_most_abnormal_code']=='8_NA'){}
            elseif($score_record['q_52_show_direct_atten_most_abnormal_code'] =='998' && $score_record2['q_52_show_direct_atten_most_abnormal_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_52_show_direct_atten_most_abnormal_code'] != $score_record2['q_52_show_direct_atten_most_abnormal_code']){ $reliability_count_raw++;}} 
            if($score_record['q_53_offer_share_current_code'] =='8_NA' AND $score_record2['q_53_offer_share_current_code']=='8_NA'){}
            elseif($score_record['q_53_offer_share_current_code'] =='998' && $score_record2['q_53_offer_share_current_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if ($score_record['q_53_offer_share_current_code'] != $score_record2['q_53_offer_share_current_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_53_offer_share_most_abnormal_code'] =='8_NA' AND $score_record2['q_53_offer_share_most_abnormal_code']=='8_NA'){}
            elseif($score_record['q_53_offer_share_most_abnormal_code'] =='998' && $score_record2['q_53_offer_share_most_abnormal_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_53_offer_share_most_abnormal_code'] != $score_record2['q_53_offer_share_most_abnormal_code']){ $reliability_count_raw++;}} 
            if($score_record['q_54_seek_share_enjoy_current_code'] =='8_NA' AND $score_record2['q_54_seek_share_enjoy_current_code']=='8_NA'){}
            elseif($score_record['q_54_seek_share_enjoy_current_code'] =='998' && $score_record2['q_54_seek_share_enjoy_current_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if ($score_record['q_54_seek_share_enjoy_current_code'] != $score_record2['q_54_seek_share_enjoy_current_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_54_seek_share_enjoy_most_abnormal_code'] =='8_NA' AND $score_record2['q_54_seek_share_enjoy_most_abnormal_code']=='8_NA'){}
            elseif($score_record['q_54_seek_share_enjoy_most_abnormal_code'] =='998' && $score_record2['q_54_seek_share_enjoy_most_abnormal_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_54_seek_share_enjoy_most_abnormal_code'] != $score_record2['q_54_seek_share_enjoy_most_abnormal_code']){ $reliability_count_raw++;}} 
            if($score_record['q_55_offer_comf_current_code'] =='8_NA' AND $score_record2['q_55_offer_comf_current_code']=='8_NA'){}
            elseif($score_record['q_55_offer_comf_current_code'] =='998' && $score_record2['q_55_offer_comf_current_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if ($score_record['q_55_offer_comf_current_code'] != $score_record2['q_55_offer_comf_current_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_55_offer_comf_most_abnormal_code'] =='8_NA' AND $score_record2['q_55_offer_comf_most_abnormal_code']=='8_NA'){}
            elseif($score_record['q_55_offer_comf_most_abnormal_code'] =='998' && $score_record2['q_55_offer_comf_most_abnormal_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_55_offer_comf_most_abnormal_code'] != $score_record2['q_55_offer_comf_most_abnormal_code']){ $reliability_count_raw++;}} 
            if($score_record['q_56_qual_social_overts_current_code'] =='8_NA' AND $score_record2['q_56_qual_social_overts_current_code']=='8_NA'){}
            elseif($score_record['q_56_qual_social_overts_current_code'] =='998' && $score_record2['q_56_qual_social_overts_current_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if ($score_record['q_56_qual_social_overts_current_code'] != $score_record2['q_56_qual_social_overts_current_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_56_qual_social_overts_most_abnormal_code'] =='8_NA' AND $score_record2['q_56_qual_social_overts_most_abnormal_code']=='8_NA'){}
            elseif($score_record['q_56_qual_social_overts_most_abnormal_code'] =='998' && $score_record2['q_56_qual_social_overts_most_abnormal_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_56_qual_social_overts_most_abnormal_code'] != $score_record2['q_56_qual_social_overts_most_abnormal_code']){ $reliability_count_raw++;}}             
            if($score_record['q_57_range_facial_expr_current_code'] =='8_NA' AND $score_record2['q_57_range_facial_expr_current_code']=='8_NA'){}
            elseif($score_record['q_57_range_facial_expr_current_code'] =='998' && $score_record2['q_57_range_facial_expr_current_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if ($score_record['q_57_range_facial_expr_current_code'] != $score_record2['q_57_range_facial_expr_current_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_57_range_facial_expr_most_abnormal_code'] =='8_NA' AND $score_record2['q_57_range_facial_expr_most_abnormal_code']=='8_NA'){}
                elseif($score_record['q_57_range_facial_expr_most_abnormal_code'] =='998' && $score_record2['q_57_range_facial_expr_most_abnormal_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_57_range_facial_expr_most_abnormal_code'] != $score_record2['q_57_range_facial_expr_most_abnormal_code']){ $reliability_count_raw++;}} 
            if($score_record['q_58_inappropriate_facial_current_code'] =='8_NA' AND $score_record2['q_58_inappropriate_facial_current_code']=='8_NA'){}
            elseif($score_record['q_58_inappropriate_facial_current_code'] =='998' && $score_record2['q_58_inappropriate_facial_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_58_inappropriate_facial_current_code'] != $score_record2['q_58_inappropriate_facial_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_58_inappropriate_facial_ever_code'] =='8_NA' AND $score_record2['q_58_inappropriate_facial_ever_code']=='8_NA'){}
            elseif($score_record['q_58_inappropriate_facial_ever_code'] =='998' && $score_record2['q_58_inappropriate_facial_ever_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if ($score_record['q_58_inappropriate_facial_ever_code'] != $score_record2['q_58_inappropriate_facial_ever_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_59_appropriat_resp_current_code'] =='8_NA' AND $score_record2['q_59_appropriat_resp_current_code']=='8_NA'){}
            elseif($score_record['q_59_appropriat_resp_current_code'] =='998' && $score_record2['q_59_appropriat_resp_current_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if ($score_record['q_59_appropriat_resp_current_code'] != $score_record2['q_59_appropriat_resp_current_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_59_appropriat_resp_most_abnormal_code'] =='8_NA' AND $score_record2['q_59_appropriat_resp_most_abnormal_code']=='8_NA'){}
            elseif($score_record['q_59_appropriat_resp_most_abnormal_code'] =='998' && $score_record2['q_59_appropriat_resp_most_abnormal_code']=='998'){}
            else {
                $denominator++;
                    if ($score_record['q_59_appropriat_resp_most_abnormal_code'] != $score_record2['q_59_appropriat_resp_most_abnormal_code']){ $reliability_count_raw++;}} 
            if($score_record['q_60_init_activities_current_code'] =='8_NA' AND $score_record2['q_60_init_activities_current_code']=='8_NA'){}
            elseif($score_record['q_60_init_activities_current_code'] =='998' && $score_record2['q_60_init_activities_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_60_init_activities_current_code'] != $score_record2['q_60_init_activities_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_60_init_activities_most_abnormal_code'] =='8_NA' AND $score_record2['q_60_init_activities_most_abnormal_code']=='8_NA'){}
            elseif($score_record['q_60_init_activities_most_abnormal_code'] =='998' && $score_record2['q_60_init_activities_most_abnormal_code']=='998'){}
            else {
                    $denominator++;
                    if ($score_record['q_60_init_activities_most_abnormal_code'] != $score_record2['q_60_init_activities_most_abnormal_code']){ $reliability_count_raw++;}} 
            if($score_record['q_61_imit_soc_play_current_code'] =='8_NA' AND $score_record2['q_61_imit_soc_play_current_code']=='8_NA'){}
            elseif($score_record['q_61_imit_soc_play_current_code'] =='998' && $score_record2['q_61_imit_soc_play_current_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if ($score_record['q_61_imit_soc_play_current_code'] != $score_record2['q_61_imit_soc_play_current_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_61_imit_soc_play_most_abnormal_code'] =='8_NA' AND $score_record2['q_61_imit_soc_play_most_abnormal_code']=='8_NA'){}
            elseif($score_record['q_61_imit_soc_play_most_abnormal_code'] =='998' && $score_record2['q_61_imit_soc_play_most_abnormal_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_61_imit_soc_play_most_abnormal_code'] != $score_record2['q_61_imit_soc_play_most_abnormal_code']){ $reliability_count_raw++;}} 
            if($score_record['q_62_inter_children_current_code'] =='8_NA' AND $score_record2['q_62_inter_children_current_code']=='8_NA'){}
            elseif($score_record['q_62_inter_children_current_code'] =='998' && $score_record2['q_62_inter_children_current_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if ($score_record['q_62_inter_children_current_code'] != $score_record2['q_62_inter_children_current_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_62_inter_children_most_abnormal_code'] =='8_NA' AND $score_record2['q_62_inter_children_most_abnormal_code']=='8_NA'){}
            elseif($score_record['q_62_inter_children_most_abnormal_code'] =='998' && $score_record2['q_62_inter_children_most_abnormal_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_62_inter_children_most_abnormal_code'] != $score_record2['q_62_inter_children_most_abnormal_code']){ $reliability_count_raw++;}} 
            if($score_record['q_63_resp_approaches_current_code'] =='8_NA' AND $score_record2['q_63_resp_approaches_current_code']=='8_NA'){}
            elseif($score_record['q_63_resp_approaches_current_code'] =='998' && $score_record2['q_63_resp_approaches_current_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if ($score_record['q_63_resp_approaches_current_code'] != $score_record2['q_63_resp_approaches_current_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_63_resp_approaches_most_abnormal_code'] =='8_NA' AND $score_record2['q_63_resp_approaches_most_abnormal_code']=='8_NA'){}
            elseif($score_record['q_63_resp_approaches_most_abnormal_code'] =='998' && $score_record2['q_63_resp_approaches_most_abnormal_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_63_resp_approaches_most_abnormal_code'] != $score_record2['q_63_resp_approaches_most_abnormal_code']){ $reliability_count_raw++;}} 
            if($score_record['q_64_group_play_peers_current_code'] =='8_NA' AND $score_record2['q_64_group_play_peers_current_code']=='8_NA'){}
            elseif($score_record['q_64_group_play_peers_current_code'] =='998' && $score_record2['q_64_group_play_peers_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_64_group_play_peers_current_code'] != $score_record2['q_64_group_play_peers_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_64_group_play_peers_most_abnormal_code'] =='8_NA' AND $score_record2['q_64_group_play_peers_most_abnormal_code']=='8_NA'){}
            elseif($score_record['q_64_group_play_peers_most_abnormal_code'] =='998' && $score_record2['q_64_group_play_peers_most_abnormal_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_64_group_play_peers_most_abnormal_code'] != $score_record2['q_64_group_play_peers_most_abnormal_code']){ $reliability_count_raw++;}} 
            if($score_record['q_65_friendships_current_code'] =='8_NA' AND $score_record2['q_65_friendships_current_code']=='8_NA'){}
            elseif($score_record['q_65_friendships_current_code'] =='998' && $score_record2['q_65_friendships_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_65_friendships_current_code'] != $score_record2['q_65_friendships_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_65_friendships_most_abnormal_code'] =='8_NA' AND $score_record2['q_65_friendships_most_abnormal_code']=='8_NA'){}
            elseif($score_record['q_65_friendships_most_abnormal_code'] =='998' && $score_record2['q_65_friendships_most_abnormal_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_65_friendships_most_abnormal_code'] != $score_record2['q_65_friendships_most_abnormal_code']){ $reliability_count_raw++;}} 
            if($score_record['q_66_soc_disinhibit_current_code'] =='8_NA' AND $score_record2['q_66_soc_disinhibit_current_code']=='8_NA'){}
            elseif($score_record['q_66_soc_disinhibit_current_code'] =='998' && $score_record2['q_66_soc_disinhibit_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_66_soc_disinhibit_current_code'] != $score_record2['q_66_soc_disinhibit_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_66_soc_disinhibit_most_abnormal_code'] =='8_NA' AND $score_record2['q_66_soc_disinhibit_most_abnormal_code']=='8_NA'){}
            elseif($score_record['q_66_soc_disinhibit_most_abnormal_code'] =='998' && $score_record2['q_66_soc_disinhibit_most_abnormal_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_66_soc_disinhibit_most_abnormal_code'] != $score_record2['q_66_soc_disinhibit_most_abnormal_code']){ $reliability_count_raw++;}} 
            if($score_record['q_67_unusual_preoccupations_current_code'] =='8_NA' AND $score_record2['q_67_unusual_preoccupations_current_code']=='8_NA'){}
            elseif($score_record['q_67_unusual_preoccupations_current_code'] =='998' && $score_record2['q_67_unusual_preoccupations_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_67_unusual_preoccupations_current_code'] != $score_record2['q_67_unusual_preoccupations_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_67_unusual_preoccupations_ever_code'] =='8_NA' AND $score_record2['q_67_unusual_preoccupations_ever_code']=='8_NA'){}
            elseif($score_record['q_67_unusual_preoccupations_ever_code'] =='998' && $score_record2['q_67_unusual_preoccupations_ever_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if ($score_record['q_67_unusual_preoccupations_ever_code'] != $score_record2['q_67_unusual_preoccupations_ever_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_68_circumscr_ints_current_code'] =='8_NA' AND $score_record2['q_68_circumscr_ints_current_code']=='8_NA'){}
            elseif($score_record['q_68_circumscr_ints_current_code'] =='998' && $score_record2['q_68_circumscr_ints_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_68_circumscr_ints_current_code'] != $score_record2['q_68_circumscr_ints_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_68_circumscr_ints_ever_code'] =='8_NA' AND $score_record2['q_68_circumscr_ints_ever_code']=='8_NA'){}
            elseif($score_record['q_68_circumscr_ints_ever_code'] =='998' && $score_record2['q_68_circumscr_ints_ever_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if ($score_record['q_68_circumscr_ints_ever_code'] != $score_record2['q_68_circumscr_ints_ever_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_69_repet_use_objects_current_code'] =='8_NA' AND $score_record2['q_69_repet_use_objects_current_code']=='8_NA'){}
            elseif($score_record['q_69_repet_use_objects_current_code'] =='998' && $score_record2['q_69_repet_use_objects_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_69_repet_use_objects_current_code'] != $score_record2['q_69_repet_use_objects_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_69_repet_use_objects_ever_code'] =='8_NA' AND $score_record2['q_69_repet_use_objects_ever_code']=='8_NA'){}
            elseif($score_record['q_69_repet_use_objects_ever_code'] =='998' && $score_record2['q_69_repet_use_objects_ever_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if ($score_record['q_69_repet_use_objects_ever_code'] != $score_record2['q_69_repet_use_objects_ever_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_70_compulsions_rituals_current_code'] =='8_NA' AND $score_record2['q_70_compulsions_rituals_current_code']=='8_NA'){}
            elseif($score_record['q_70_compulsions_rituals_current_code'] =='998' && $score_record2['q_70_compulsions_rituals_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_70_compulsions_rituals_current_code'] != $score_record2['q_70_compulsions_rituals_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_70_compulsions_rituals_ever_code'] =='8_NA' AND $score_record2['q_70_compulsions_rituals_ever_code']=='8_NA'){}
            elseif($score_record['q_70_compulsions_rituals_ever_code'] =='998' && $score_record2['q_70_compulsions_rituals_ever_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if ($score_record['q_70_compulsions_rituals_ever_code'] != $score_record2['q_70_compulsions_rituals_ever_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_71_unusual_sens_ints_current_code'] =='8_NA' AND $score_record2['q_71_unusual_sens_ints_current_code']=='8_NA'){}
            elseif($score_record['q_71_unusual_sens_ints_current_code'] =='998' && $score_record2['q_71_unusual_sens_ints_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_71_unusual_sens_ints_current_code'] != $score_record2['q_71_unusual_sens_ints_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_71_unusual_sens_ints_ever_code'] =='8_NA' AND $score_record2['q_71_unusual_sens_ints_ever_code']=='8_NA'){}
            elseif($score_record['q_71_unusual_sens_ints_ever_code'] =='998' && $score_record2['q_71_unusual_sens_ints_ever_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if ($score_record['q_71_unusual_sens_ints_ever_code'] != $score_record2['q_71_unusual_sens_ints_ever_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_72_undo_gen_sens_noise_current_code'] =='8_NA' AND $score_record2['q_72_undo_gen_sens_noise_current_code']=='8_NA'){}
            elseif($score_record['q_72_undo_gen_sens_noise_current_code'] =='998' && $score_record2['q_72_undo_gen_sens_noise_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_72_undo_gen_sens_noise_current_code'] != $score_record2['q_72_undo_gen_sens_noise_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_72_undo_gen_sens_noise_ever_code'] =='8_NA' AND $score_record2['q_72_undo_gen_sens_noise_ever_code']=='8_NA'){}
            elseif($score_record['q_72_undo_gen_sens_noise_ever_code'] =='998' && $score_record2['q_72_undo_gen_sens_noise_ever_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_72_undo_gen_sens_noise_ever_code'] != $score_record2['q_72_undo_gen_sens_noise_ever_code']){ $reliability_count_raw++;}} 
            if($score_record['q_73_idiosyncratic_current_code'] =='8_NA' AND $score_record2['q_73_idiosyncratic_current_code']=='8_NA'){}
            elseif($score_record['q_73_idiosyncratic_current_code'] =='998' && $score_record2['q_73_idiosyncratic_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_73_idiosyncratic_current_code'] != $score_record2['q_73_idiosyncratic_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_73_idiosyncratic_ever_code'] =='8_NA' AND $score_record2['q_73_idiosyncratic_ever_code']=='8_NA'){}
            elseif($score_record['q_73_idiosyncratic_ever_code'] =='998' && $score_record2['q_73_idiosyncratic_ever_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_73_idiosyncratic_ever_code'] != $score_record2['q_73_idiosyncratic_ever_code']){ $reliability_count_raw++;}} 
            if($score_record['q_74_diff_minor_changes_current_code'] =='8_NA' AND $score_record2['q_74_diff_minor_changes_current_code']=='8_NA'){}
            elseif($score_record['q_74_diff_minor_changes_current_code'] =='998' && $score_record2['q_74_diff_minor_changes_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_74_diff_minor_changes_current_code'] != $score_record2['q_74_diff_minor_changes_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_74_diff_minor_changes_ever_code'] =='8_NA' AND $score_record2['q_74_diff_minor_changes_ever_code']=='8_NA'){}
            elseif($score_record['q_74_diff_minor_changes_ever_code'] =='998' && $score_record2['q_74_diff_minor_changes_ever_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_74_diff_minor_changes_ever_code'] != $score_record2['q_74_diff_minor_changes_ever_code']){ $reliability_count_raw++;}} 
            if($score_record['q_75_resist_trivial_chng_current_code'] =='8_NA' AND $score_record2['q_75_resist_trivial_chng_current_code']=='8_NA'){}
            elseif($score_record['q_75_resist_trivial_chng_current_code'] =='998' && $score_record2['q_75_resist_trivial_chng_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_75_resist_trivial_chng_current_code'] != $score_record2['q_75_resist_trivial_chng_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_75_resist_trivial_chng_ever_code'] =='8_NA' AND $score_record2['q_75_resist_trivial_chng_ever_code']=='8_NA'){}
            elseif($score_record['q_75_resist_trivial_chng_ever_code'] =='998' && $score_record2['q_75_resist_trivial_chng_ever_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_75_resist_trivial_chng_ever_code'] != $score_record2['q_75_resist_trivial_chng_ever_code']){ $reliability_count_raw++;}} 
            if($score_record['q_76_unus_attach_objects_current_code'] =='8_NA' AND $score_record2['q_76_unus_attach_objects_current_code']=='8_NA'){}
            elseif($score_record['q_76_unus_attach_objects_current_code'] =='998' && $score_record2['q_76_unus_attach_objects_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_76_unus_attach_objects_current_code'] != $score_record2['q_76_unus_attach_objects_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_76_unus_attach_objects_ever_code'] =='8_NA' AND $score_record2['q_76_unus_attach_objects_ever_code']=='8_NA'){}
            elseif($score_record['q_76_unus_attach_objects_ever_code'] =='998' && $score_record2['q_76_unus_attach_objects_ever_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_76_unus_attach_objects_ever_code'] != $score_record2['q_76_unus_attach_objects_ever_code']){ $reliability_count_raw++;}} 
            if($score_record['q_77_hands_finger_manners_current_code'] =='8_NA' AND $score_record2['q_77_hands_finger_manners_current_code']=='8_NA'){}
            elseif($score_record['q_77_hands_finger_manners_current_code'] =='998' && $score_record2['q_77_hands_finger_manners_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_77_hands_finger_manners_current_code'] != $score_record2['q_77_hands_finger_manners_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_77_hands_finger_manners_ever_code'] =='8_NA' AND $score_record2['q_77_hands_finger_manners_ever_code']=='8_NA'){}
            elseif($score_record['q_77_hands_finger_manners_ever_code'] =='998' && $score_record2['q_77_hands_finger_manners_ever_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if ($score_record['q_77_hands_finger_manners_ever_code'] != $score_record2['q_77_hands_finger_manners_ever_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_78_oth_complex_manners_current_code'] =='8_NA' AND $score_record2['q_78_oth_complex_manners_current_code']=='8_NA'){}
            elseif($score_record['q_78_oth_complex_manners_current_code'] =='998' && $score_record2['q_78_oth_complex_manners_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_78_oth_complex_manners_current_code'] != $score_record2['q_78_oth_complex_manners_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_78_oth_complex_manners_ever_code'] =='8_NA' AND $score_record2['q_78_oth_complex_manners_ever_code']=='8_NA'){}
            elseif($score_record['q_78_oth_complex_manners_ever_code'] =='998' && $score_record2['q_78_oth_complex_manners_ever_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if ($score_record['q_78_oth_complex_manners_ever_code'] != $score_record2['q_78_oth_complex_manners_ever_code']){ $reliability_count_raw++; $reliability_count_scored++;}}  
            if($score_record['q_79_midline_hand_moves_current_code'] =='8_NA' AND $score_record2['q_79_midline_hand_moves_current_code']=='8_NA'){}
            elseif($score_record['q_79_midline_hand_moves_current_code'] =='998' && $score_record2['q_79_midline_hand_moves_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_79_midline_hand_moves_current_code'] != $score_record2['q_79_midline_hand_moves_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_79_midline_hand_moves_ever_code'] =='8_NA' AND $score_record2['q_79_midline_hand_moves_ever_code']=='8_NA'){}
            elseif($score_record['q_79_midline_hand_moves_ever_code'] =='998' && $score_record2['q_79_midline_hand_moves_ever_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_79_midline_hand_moves_ever_code'] != $score_record2['q_79_midline_hand_moves_ever_code']){ $reliability_count_raw++;}} 
            if($score_record['q_80_gait_current_code'] =='8_NA' AND $score_record2['q_80_gait_current_code']=='8_NA'){}
            elseif($score_record['q_80_gait_current_code'] =='998' && $score_record2['q_80_gait_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_80_gait_current_code'] != $score_record2['q_80_gait_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_80_gait_most_abnormal_code'] =='8_NA' AND $score_record2['q_80_gait_most_abnormal_code']=='8_NA'){}
            elseif($score_record['q_80_gait_most_abnormal_code'] =='998' && $score_record2['q_80_gait_most_abnormal_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_80_gait_most_abnormal_code'] != $score_record2['q_80_gait_most_abnormal_code']){ $reliability_count_raw++;}} 
            if($score_record['q_81_aggress_caregivers_current_code'] =='8_NA' AND $score_record2['q_81_aggress_caregivers_current_code']=='8_NA'){}
            elseif($score_record['q_81_aggress_caregivers_current_code'] =='998' && $score_record2['q_81_aggress_caregivers_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_81_aggress_caregivers_current_code'] != $score_record2['q_81_aggress_caregivers_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_81_aggress_caregivers_ever_code'] =='8_NA' AND $score_record2['q_81_aggress_caregivers_ever_code']=='8_NA'){}
            elseif($score_record['q_81_aggress_caregivers_ever_code'] =='998' && $score_record2['q_81_aggress_caregivers_ever_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_81_aggress_caregivers_ever_code'] != $score_record2['q_81_aggress_caregivers_ever_code']){ $reliability_count_raw++;}} 
            if($score_record['q_82_aggress_noncaregivers_current_code'] =='8_NA' AND $score_record2['q_82_aggress_noncaregivers_current_code']=='8_NA'){}
            elseif($score_record['q_82_aggress_noncaregivers_current_code'] =='998' && $score_record2['q_82_aggress_noncaregivers_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_82_aggress_noncaregivers_current_code'] != $score_record2['q_82_aggress_noncaregivers_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_82_aggress_noncaregivers_ever_code'] =='8_NA' AND $score_record2['q_82_aggress_noncaregivers_ever_code']=='8_NA'){}
            elseif($score_record['q_82_aggress_noncaregivers_ever_code'] =='998' && $score_record2['q_82_aggress_noncaregivers_ever_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_82_aggress_noncaregivers_ever_code'] != $score_record2['q_82_aggress_noncaregivers_ever_code']){ $reliability_count_raw++;}} 
            if($score_record['q_83_self_injury_current_code'] =='8_NA' AND $score_record2['q_83_self_injury_current_code']=='8_NA'){}
            elseif($score_record['q_83_self_injury_current_code'] =='998' && $score_record2['q_83_self_injury_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_83_self_injury_current_code'] != $score_record2['q_83_self_injury_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_83_self_injury_ever_code'] =='8_NA' AND $score_record2['q_83_self_injury_ever_code']=='8_NA'){}
            elseif($score_record['q_83_self_injury_ever_code'] =='998' && $score_record2['q_83_self_injury_ever_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_83_self_injury_ever_code'] != $score_record2['q_83_self_injury_ever_code']){ $reliability_count_raw++;}} 
            if($score_record['q_84_hyperventilation_current_code'] =='8_NA' AND $score_record2['q_84_hyperventilation_current_code']=='8_NA'){}
            elseif($score_record['q_84_hyperventilation_current_code'] =='998' && $score_record2['q_84_hyperventilation_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_84_hyperventilation_current_code'] != $score_record2['q_84_hyperventilation_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_84_hyperventilation_ever_code'] =='8_NA' AND $score_record2['q_84_hyperventilation_ever_code']=='8_NA'){}
            elseif($score_record['q_84_hyperventilation_ever_code'] =='998' && $score_record2['q_84_hyperventilation_ever_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_84_hyperventilation_ever_code'] != $score_record2['q_84_hyperventilation_ever_code']){ $reliability_count_raw++;}} 
            if($score_record['q_85_faints_fits_blackouts_current_code'] =='8_NA' AND $score_record2['q_85_faints_fits_blackouts_current_code']=='8_NA'){}
            elseif($score_record['q_85_faints_fits_blackouts_current_code'] =='998' && $score_record2['q_85_faints_fits_blackouts_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_85_faints_fits_blackouts_current_code'] != $score_record2['q_85_faints_fits_blackouts_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_85_faints_fits_blackouts_ever_code'] =='8_NA' AND $score_record2['q_85_faints_fits_blackouts_ever_code']=='8_NA'){}
            elseif($score_record['q_85_faints_fits_blackouts_ever_code'] =='998' && $score_record2['q_85_faints_fits_blackouts_ever_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_85_faints_fits_blackouts_ever_code'] != $score_record2['q_85_faints_fits_blackouts_ever_code']){ $reliability_count_raw++;}} 
            if($score_record['q_86_age_when_abnormality_first_evident'] =='8_NA' AND $score_record2['q_86_age_when_abnormality_first_evident']=='8_NA'){}
            elseif($score_record['q_86_age_when_abnormality_first_evident'] =='998' && $score_record2['q_86_age_when_abnormality_first_evident']=='998'){}
            else {
                $denominator++; $denominator_scored++;
                if ($score_record['q_86_age_when_abnormality_first_evident'] != $score_record2['q_86_age_when_abnormality_first_evident']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_87_interviewers_judgment'] =='8' AND $score_record2['q_87_interviewers_judgment']=='8'){}
            elseif($score_record['q_87_interviewers_judgment'] =='998' && $score_record2['q_87_interviewers_judgment']=='998'){}
            else {
                $denominator++; $denominator_scored++;
                if (abs($score_record['q_87_interviewers_judgment'] - $score_record2['q_87_interviewers_judgment']) >3){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_88_visuospatial_ability_current_code'] =='8_NA' AND $score_record2['q_88_visuospatial_ability_current_code']=='8_NA'){}
            elseif($score_record['q_88_visuospatial_ability_current_code'] =='998' && $score_record2['q_88_visuospatial_ability_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_88_visuospatial_ability_current_code'] != $score_record2['q_88_visuospatial_ability_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_88_visuospatial_ability_ever_code'] =='8_NA' AND $score_record2['q_88_visuospatial_ability_ever_code']=='8_NA'){}
            elseif($score_record['q_88_visuospatial_ability_ever_code'] =='998' && $score_record2['q_88_visuospatial_ability_ever_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_88_visuospatial_ability_ever_code'] != $score_record2['q_88_visuospatial_ability_ever_code']){ $reliability_count_raw++;}} 
            if($score_record['q_89_memory_still_current_code'] =='8_NA' AND $score_record2['q_89_memory_still_current_code']=='8_NA'){}
            elseif($score_record['q_89_memory_still_current_code'] =='998' && $score_record2['q_89_memory_still_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_89_memory_still_current_code'] != $score_record2['q_89_memory_still_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_89_memory_still_ever_code'] =='8_NA' AND $score_record2['q_89_memory_still_ever_code']=='8_NA'){}
            elseif($score_record['q_89_memory_still_ever_code'] =='998' && $score_record2['q_89_memory_still_ever_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_89_memory_still_ever_code'] != $score_record2['q_89_memory_still_ever_code']){ $reliability_count_raw++;}} 
            if($score_record['q_90_musical_ability_current_code'] =='8_NA' AND $score_record2['q_90_musical_ability_current_code']=='8_NA'){}
            elseif($score_record['q_90_musical_ability_current_code'] =='998' && $score_record2['q_90_musical_ability_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_90_musical_ability_current_code'] != $score_record2['q_90_musical_ability_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_90_musical_ability_ever_code'] =='8_NA' AND $score_record2['q_90_musical_ability_ever_code']=='8_NA'){}
            elseif($score_record['q_90_musical_ability_ever_code'] =='998' && $score_record2['q_90_musical_ability_ever_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_90_musical_ability_ever_code'] != $score_record2['q_90_musical_ability_ever_code']){ $reliability_count_raw++;}} 
            if($score_record['q_91_drawings_skill_current_code'] =='8_NA' AND $score_record2['q_91_drawings_skill_current_code']=='8_NA'){}
            elseif($score_record['q_91_drawings_skill_current_code'] =='998' && $score_record2['q_91_drawings_skill_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_91_drawings_skill_current_code'] != $score_record2['q_91_drawings_skill_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_91_drawings_skill_ever_code'] =='8_NA' AND $score_record2['q_91_drawings_skill_ever_code']=='8_NA'){}
            elseif($score_record['q_91_drawings_skill_ever_code'] =='998' && $score_record2['q_91_drawings_skill_ever_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_91_drawings_skill_ever_code'] != $score_record2['q_91_drawings_skill_ever_code']){ $reliability_count_raw++;}} 
            if($score_record['q_92_reading_ability_current_code'] =='8_NA' AND $score_record2['q_92_reading_ability_current_code']=='8_NA'){}
            elseif($score_record['q_92_reading_ability_current_code'] =='998' && $score_record2['q_92_reading_ability_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_92_reading_ability_current_code'] != $score_record2['q_92_reading_ability_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_92_reading_ability_ever_code'] =='8_NA' AND $score_record2['q_92_reading_ability_ever_code']=='8_NA'){}
            elseif($score_record['q_92_reading_ability_ever_code'] =='998' && $score_record2['q_92_reading_ability_ever_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_92_reading_ability_ever_code'] != $score_record2['q_92_reading_ability_ever_code']){ $reliability_count_raw++;}} 
            if($score_record['q_93_computational_ability_current_code'] =='8_NA' AND $score_record2['q_93_computational_ability_current_code']=='8_NA'){}
            elseif($score_record['q_93_computational_ability_current_code'] =='998' && $score_record2['q_93_computational_ability_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_93_computational_ability_current_code'] != $score_record2['q_93_computational_ability_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_93_computational_ability_ever_code'] =='8_NA' AND $score_record2['q_93_computational_ability_ever_code']=='8_NA'){}
            elseif($score_record['q_93_computational_ability_ever_code'] =='998' && $score_record2['q_93_computational_ability_ever_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_93_computational_ability_ever_code'] != $score_record2['q_93_computational_ability_ever_code']){ $reliability_count_raw++;}} 
         

               
            echo('<br>');
           // print_r($denominator);
            echo('<br>');
           // print_r($reliability_count_raw);
            echo('<br>');
            echo('<br>');
           // print_r($denominator_scored);
            echo('<br>');
           // print_r($reliability_count_scored);
            echo('<br>');

            // Score the reliability
            $reliability['Reliability_score_all_items']= (($denominator-$reliability_count_raw)/$denominator*100);
            $reliability['Reliability_score_scored_items']= (($denominator_scored-$reliability_count_scored)/$denominator_scored*100);
           
          
        }
        // If the reliability is to be compared to the gold standard
        elseif ($score_record['Gold_standard']=='Gold_standard_SEA0070'){
            echo("This is the Gold standard check for SEA0070<br>");
            

            $reliability_count_raw=0;            
            $reliability_count_scored=0;            
            $denominator=0;
            $denominator_scored=0;

            // TO DO!!!!!!!!!!!!!!!!!!!!! CHECK scoring range. Might use different values for scored count. And score
            // record 2 to score record 3 once things are known about the check.
if($score_record['q_2_age_first_noticed_code']=='8' AND $score_record3['q_2_age_first_noticed_code']=='8'){}
            elseif ($score_record['q_2_age_first_noticed_code']=='998' && $score_record3['q_2_age_first_noticed_code']=='998'){}
            else {
                $denominator++; $denominator_scored;
                if(abs($score_record3['q_2_age_first_noticed_code'] - $score_record['q_2_age_first_noticed_code']) >3){$reliability_count_raw++; $reliability_count_scored++;}}

            if($score_record['q_4_onset_as_perceived_code']=='8' AND $score_record3['q_4_onset_as_perceived_code']=='8'){}
            elseif($score_record['q_4_onset_as_perceived_code']=='998' AND $score_record3['q_4_onset_as_perceived_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_4_onset_as_perceived_code'] != $score_record3['q_4_onset_as_perceived_code']) { $reliability_count_raw++;}}

            if($score_record['q_5_first_walked_code'] =='8' AND $score_record3['q_5_first_walked_code']=='8'){}
            elseif($score_record['q_5_first_walked_code'] =='998' && $score_record3['q_5_first_walked_code']=='998'){}
            else {
                $denominator++;
                if (abs($score_record['q_5_first_walked_code'] - $score_record3['q_5_first_walked_code']) >3) { $reliability_count_raw++;}} 
            
            if($score_record['q_6_bladder_daytime_code'] =='8' AND $score_record3['q_6_bladder_daytime_code']=='8'){}
            elseif($score_record['q_6_bladder_daytime_code'] =='998' && $score_record3['q_6_bladder_daytime_code']=='998'){}
            else {
                $denominator++;
                if (abs($score_record['q_6_bladder_daytime_code'] - $score_record3['q_6_bladder_daytime_code']) >3){ $reliability_count_raw++;}}
            
            if($score_record['q_7_bladder_nighttime_code'] =='8' AND $score_record3['q_7_bladder_nighttime_code']=='8'){}
            elseif($score_record['q_7_bladder_nighttime_code'] =='998' && $score_record3['q_7_bladder_nighttime_code']=='998'){}
            else {
                $denominator++;
                if (abs($score_record['q_7_bladder_nighttime_code'] - $score_record3['q_7_bladder_nighttime_code']) >3){ $reliability_count_raw++;}} 

            if($score_record['q_8_bowel_control_code'] =='8' AND $score_record3['q_8_bowel_control_code']=='8'){}
            elseif($score_record['q_8_bowel_control_code'] =='998' && $score_record3['q_8_bowel_control_code']=='998'){}
            else {
                $denominator++;
                if (abs($score_record['q_8_bowel_control_code'] - $score_record3['q_8_bowel_control_code']) >3){ $reliability_count_raw++;}} 
            if($score_record['q_9_first_single_words_code'] =='8' AND $score_record3['q_9_first_single_words_code']=='8'){}
            elseif($score_record['q_9_first_single_words_code'] =='998' && $score_record3['q_9_first_single_words_code']=='998'){}
            else {
                $denominator++; $denominator_scored++;
                if (abs($score_record['q_9_first_single_words_code'] - $score_record3['q_9_first_single_words_code']) >3){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_10_first_phrases_code'] =='8' AND $score_record3['q_10_first_phrases_code']=='8'){}
            elseif($score_record['q_10_first_phrases_code'] =='998' && $score_record3['q_10_first_phrases_code']=='998'){}
            else {
                $denominator++; $denominator_scored++;
                if (abs($score_record['q_10_first_phrases_code'] - $score_record3['q_10_first_phrases_code']) >3){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if ($score_record['q_11_loss_of_language'] =='8' AND $score_record3['q_11_loss_of_language']=='8'){}
            elseif($score_record['q_10_first_phrases_code'] =='998' && $score_record3['q_10_first_phrases_code']=='998'){}
            else {                    
                $denominator++;
                if($score_record['q_11_loss_of_language']  != $score_record3['q_11_loss_of_language']){ $reliability_count_raw++;}} 
            if($score_record['q_12_level_before_loss_code'] =='8' AND $score_record3['q_12_level_before_loss_code']=='8'){}
            elseif($score_record['q_12_level_before_loss_code'] =='998' && $score_record3['q_12_level_before_loss_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_12_level_before_loss_code'] != $score_record3['q_12_level_before_loss_code']){ $reliability_count_raw++;}} 
            if($score_record['13_loss_of_spontaneous_use_code'] =='8' AND $score_record3['13_loss_of_spontaneous_use_code']=='8'){}
            elseif($score_record['13_loss_of_spontaneous_use_code'] =='998' && $score_record3['13_loss_of_spontaneous_use_code']=='998'){}
            else {
                $denominator++;
                if (($score_record['13_loss_of_spontaneous_use_code'] =='2' AND $score_record3['13_loss_of_spontaneous_use_code']=='3') ||
                      ($score_record['13_loss_of_spontaneous_use_code'] =='3' AND $score_record3['13_loss_of_spontaneous_use_code']=='2'))
                {
                   #Don't count this
                }
                 else if ($score_record['13_loss_of_spontaneous_use_code'] != $score_record3['13_loss_of_spontaneous_use_code']){ $reliability_count_raw++;}} 

            if($score_record['14_loss_of_intent_code'] =='8' AND $score_record3['14_loss_of_intent_code']=='8'){}
            elseif($score_record['14_loss_of_intent_code'] =='998' && $score_record3['14_loss_of_intent_code']=='998'){}
            else {
                $denominator++;
                if (($score_record['14_loss_of_intent_code'] =='2' AND $score_record3['14_loss_of_intent_code']=='3') ||
                     ($score_record['14_loss_of_intent_code'] =='3' AND $score_record3['14_loss_of_intent_code']=='2'))
               {
                  #Don't count this
               }
                else if ($score_record['14_loss_of_intent_code'] != $score_record3['14_loss_of_intent_code']){ $reliability_count_raw++;}} 
            if($score_record['15_loss_of_syntactical_code'] =='8' AND $score_record3['15_loss_of_syntactical_code']=='8'){}
            elseif($score_record['15_loss_of_syntactical_code'] =='998' && $score_record3['15_loss_of_syntactical_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['15_loss_of_syntactical_code'] != $score_record3['15_loss_of_syntactical_code']){ $reliability_count_raw++;}} 
            if($score_record['16_loss_of_articulation_code'] =='8' AND $score_record3['16_loss_of_articulation_code']=='8'){}
            elseif($score_record['16_loss_of_articulation_code'] =='998' && $score_record3['16_loss_of_articulation_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['16_loss_of_articulation_code'] != $score_record3['16_loss_of_articulation_code']){ $reliability_count_raw++;}} 
            if($score_record['q_17_main_loss_apparent_code'] =='8' AND $score_record3['q_17_main_loss_apparent_code']=='8'){}
            elseif($score_record['q_17_main_loss_apparent_code'] =='998' && $score_record3['q_17_main_loss_apparent_code']=='998'){}
            else {
                $denominator++;
                if (abs($score_record['q_17_main_loss_apparent_code'] - $score_record3['q_17_main_loss_apparent_code']) >3){ $reliability_count_raw++;}} 
            if($score_record['q_18_loss_due_to_illness'] =='8' AND $score_record3['q_18_loss_due_to_illness']=='8'){}
            elseif($score_record['q_18_loss_due_to_illness'] =='998' && $score_record3['q_18_loss_due_to_illness']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_18_loss_due_to_illness'] != $score_record3['q_18_loss_due_to_illness']){ $reliability_count_raw++;}} 
            if($score_record['q_19_duration_of_loss_code'] =='8' AND $score_record3['q_19_duration_of_loss_code']=='8'){}
            elseif($score_record['q_19_duration_of_loss_code'] =='998' && $score_record3['q_19_duration_of_loss_code']=='998'){}
            else {
                $denominator++;
                if (abs($score_record['q_19_duration_of_loss_code'] - $score_record3['q_19_duration_of_loss_code']) >3){ $reliability_count_raw++;}} 
            if($score_record['q_20_loss_of_skills_code'] =='8' AND $score_record3['q_20_loss_of_skills_code']=='8'){}
            elseif($score_record['q_20_loss_of_skills_code'] =='998' && $score_record3['q_20_loss_of_skills_code']=='998'){}
            else {
                $denominator++;
                if (($score_record['q_20_loss_of_skills_code'] =='2' AND $score_record3['q_20_loss_of_skills_code']=='3') ||
                  ($score_record['q_20_loss_of_skills_code'] =='3' AND $score_record3['q_20_loss_of_skills_code']=='2'))
                 {
                    #Don't count this
                 }
                 else if ($score_record['q_20_loss_of_skills_code'] != $score_record3['q_20_loss_of_skills_code']){ $reliability_count_raw++;}} 
            if($score_record['q_21_puposive_hand_movements_code'] =='8' AND $score_record3['q_21_puposive_hand_movements_code']=='8'){}
            elseif($score_record['q_21_puposive_hand_movements_code'] =='998' && $score_record3['q_21_puposive_hand_movements_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_21_puposive_hand_movements_code'] != $score_record3['q_21_puposive_hand_movements_code']){ $reliability_count_raw++;}} 
            if($score_record['q_22_motor_skills_code'] =='8' AND $score_record3['q_22_motor_skills_code']=='8'){}
            elseif($score_record['q_22_motor_skills_code'] =='998' && $score_record3['q_22_motor_skills_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_22_motor_skills_code'] != $score_record3['q_22_motor_skills_code']){ $reliability_count_raw++;}} 
            if($score_record['q_23_self_help_skills_code'] =='8' AND $score_record3['q_23_self_help_skills_code']=='8'){}
            elseif($score_record['q_23_self_help_skills_code'] =='998' && $score_record3['q_23_self_help_skills_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_23_self_help_skills_code'] != $score_record3['q_23_self_help_skills_code']){ $reliability_count_raw++;}} 
            if($score_record['q_24_constructive_play_code'] =='8' AND $score_record3['q_24_constructive_play_code']=='8'){}
            elseif($score_record['q_24_constructive_play_code'] =='998' && $score_record3['q_24_constructive_play_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_24_constructive_play_code'] != $score_record3['q_24_constructive_play_code']){ $reliability_count_raw++;}} 
            if($score_record['q_25_social_engagement_code'] =='8' AND $score_record3['q_25_social_engagement_code']=='8'){}
            elseif($score_record['q_25_social_engagement_code'] =='998' && $score_record3['q_25_social_engagement_code']=='998'){}
            else {
                $denominator++;
                if (($score_record['q_25_social_engagement_code'] =='2' AND $score_record3['q_25_social_engagement_code']=='3') ||
                   ($score_record['q_25_social_engagement_code'] =='3' AND $score_record3['q_25_social_engagement_code']=='2'))
                  {
                     #Don't count this
                  }
                  else if ($score_record['q_25_social_engagement_code'] != $score_record3['q_25_social_engagement_code']){ $reliability_count_raw++;}} 
            if($score_record['q_26_loss_first_apparent_code'] =='8' AND $score_record3['q_26_loss_first_apparent_code']=='8'){}
            elseif($score_record['q_26_loss_first_apparent_code'] =='998' && $score_record3['q_26_loss_first_apparent_code']=='998'){}
            else {
                $denominator++;
                if (abs($score_record['q_26_loss_first_apparent_code'] - $score_record3['q_26_loss_first_apparent_code']) >3){ $reliability_count_raw++;}} 
            if($score_record['q_27_physical_illness_code'] =='8' AND $score_record3['q_27_physical_illness_code']=='8'){}
            elseif($score_record['q_27_physical_illness_code'] =='998' && $score_record3['q_27_physical_illness_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_27_physical_illness_code'] != $score_record3['q_27_physical_illness_code']){ $reliability_count_raw++;}} 
            if($score_record['q_28_duration_of_loss_code'] =='8' AND $score_record3['q_28_duration_of_loss_code']=='8'){}
            elseif($score_record['q_28_duration_of_loss_code'] =='998' && $score_record3['q_28_duration_of_loss_code']=='998'){}
            else {
                $denominator++;
                if (abs($score_record['q_28_duration_of_loss_code'] - $score_record3['q_28_duration_of_loss_code']) >3){ $reliability_count_raw++;}} 
            if($score_record['q_29_compreh_simple_current'] =='8' AND $score_record3['q_29_compreh_simple_current']=='8'){}
            elseif($score_record['q_29_compreh_simple_current'] =='998' && $score_record3['q_29_compreh_simple_current']=='998'){}
            else {
                $denominator++;
                if (($score_record['q_29_compreh_simple_current'] =='2' AND $score_record3['q_29_compreh_simple_current']=='3') ||
                    ($score_record['q_29_compreh_simple_current'] =='3' AND $score_record3['q_29_compreh_simple_current']=='2'))
                   {
                      #Don't count this
                   }
                   else if ($score_record['q_29_compreh_simple_current'] != $score_record3['q_29_compreh_simple_current']){ $reliability_count_raw++;}} 
            if($score_record['q_29_compreh_simple_most_abnormal'] =='8' AND $score_record3['q_29_compreh_simple_most_abnormal']=='8'){}
            elseif($score_record['q_29_compreh_simple_most_abnormal'] =='998' && $score_record3['q_29_compreh_simple_most_abnormal']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_29_compreh_simple_most_abnormal'] != $score_record3['q_29_compreh_simple_most_abnormal']){ $reliability_count_raw++;}} 
            if($score_record['q_30_overall_level_of_language'] =='8' AND $score_record3['q_30_overall_level_of_language']=='8'){}
            elseif($score_record['q_30_overall_level_of_language'] =='998' && $score_record3['q_30_overall_level_of_language']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_30_overall_level_of_language'] != $score_record3['q_30_overall_level_of_language']){ $reliability_count_raw++;}} 
            if($score_record['q_31_use_of_others_body_current_code'] =='8' AND $score_record3['q_31_use_of_others_body_current_code']=='8'){}
            elseif($score_record['q_31_use_of_others_body_current_code'] =='998' && $score_record3['q_31_use_of_others_body_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_31_use_of_others_body_current_code'] != $score_record3['q_31_use_of_others_body_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_31_use_of_others_body_ever_code'] =='8' AND $score_record3['q_31_use_of_others_body_ever_code']=='8'){}
            elseif($score_record['q_31_use_of_others_body_ever_code'] =='998' && $score_record3['q_31_use_of_others_body_ever_code']=='998'){}
            else {
                $denominator++; $denominator_scored++;
                if ($score_record['q_31_use_of_others_body_ever_code'] != $score_record3['q_31_use_of_others_body_ever_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_32_artic_pronun_current_code'] =='8' AND $score_record3['q_32_artic_pronun_current_code']=='8'){}
            elseif($score_record['q_32_artic_pronun_current_code'] =='998' && $score_record3['q_32_artic_pronun_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_32_artic_pronun_current_code'] != $score_record3['q_32_artic_pronun_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_32_artic_pronun_5years_code'] =='8' AND $score_record3['q_32_artic_pronun_5years_code']=='8'){}
            elseif($score_record['q_32_artic_pronun_5years_code'] =='998' && $score_record3['q_32_artic_pronun_5years_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_32_artic_pronun_5years_code'] != $score_record3['q_32_artic_pronun_5years_code']){ $reliability_count_raw++;}} 
            if($score_record['q_33_stereotyped_utterances_current_code'] =='8' AND $score_record3['q_33_stereotyped_utterances_current_code']=='8'){}
            elseif($score_record['q_33_stereotyped_utterances_current_code'] =='998' && $score_record3['q_33_stereotyped_utterances_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_33_stereotyped_utterances_current_code'] != $score_record3['q_33_stereotyped_utterances_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_33_stereotyped_utterances_ever_code'] =='8' AND $score_record3['q_33_stereotyped_utterances_ever_code']=='8'){}
            elseif($score_record['q_33_stereotyped_utterances_ever_code'] =='998' && $score_record3['q_33_stereotyped_utterances_ever_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if ($score_record['q_33_stereotyped_utterances_ever_code'] != $score_record3['q_33_stereotyped_utterances_ever_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_34_social_verb_chat_current_code'] =='8' AND $score_record3['q_34_social_verb_chat_current_code']=='8'){}
            elseif($score_record['q_34_social_verb_chat_current_code'] =='998' && $score_record3['q_34_social_verb_chat_current_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if ($score_record['q_34_social_verb_chat_current_code'] != $score_record3['q_34_social_verb_chat_current_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_34_social_verb_chat_ever_code'] =='8' AND $score_record3['q_34_social_verb_chat_ever_code']=='8'){}
            elseif($score_record['q_34_social_verb_chat_ever_code'] =='998' && $score_record3['q_34_social_verb_chat_ever_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_34_social_verb_chat_ever_code'] != $score_record3['q_34_social_verb_chat_ever_code']){ $reliability_count_raw++;}} 
            if($score_record['q_35_recipr_convers_current_code'] =='8' AND $score_record3['q_35_recipr_convers_current_code']=='8'){}
            elseif($score_record['q_35_recipr_convers_current_code'] =='998' && $score_record3['q_35_recipr_convers_current_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if ($score_record['q_35_recipr_convers_current_code'] != $score_record3['q_35_recipr_convers_current_code']){ $reliability_count_raw++; $reliability_count_scored++;}}
            if($score_record['q_35_recipr_convers_ever_code'] =='8' AND $score_record3['q_35_recipr_convers_ever_code']=='8'){}
            elseif($score_record['q_35_recipr_convers_ever_code'] =='998' && $score_record3['q_35_recipr_convers_ever_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_35_recipr_convers_ever_code'] != $score_record3['q_35_recipr_convers_ever_code']){ $reliability_count_raw++;}} 
            if($score_record['q_36_inappropriate_qs_current_code'] =='8' AND $score_record3['q_36_inappropriate_qs_current_code']=='8'){}
            elseif($score_record['q_36_inappropriate_qs_current_code'] =='998' && $score_record3['q_36_inappropriate_qs_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_36_inappropriate_qs_current_code'] != $score_record3['q_36_inappropriate_qs_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_36_inappropriate_qs_ever_code'] =='8' AND $score_record3['q_36_inappropriate_qs_ever_code']=='8'){}
            elseif($score_record['q_36_inappropriate_qs_ever_code'] =='998' && $score_record3['q_36_inappropriate_qs_ever_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if ($score_record['q_36_inappropriate_qs_ever_code'] != $score_record3['q_36_inappropriate_qs_ever_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_37_prenominal_reversal_current_code'] =='8' AND $score_record3['q_37_prenominal_reversal_current_code']=='8'){}
            elseif($score_record['q_37_prenominal_reversal_current_code'] =='998' && $score_record3['q_37_prenominal_reversal_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_37_prenominal_reversal_current_code'] != $score_record3['q_37_prenominal_reversal_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_37_prenominal_reversal_ever_code'] =='8' AND $score_record3['q_37_prenominal_reversal_ever_code']=='8'){}
            elseif($score_record['q_37_prenominal_reversal_ever_code'] =='998' && $score_record3['q_37_prenominal_reversal_ever_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if ($score_record['q_37_prenominal_reversal_ever_code'] != $score_record3['q_37_prenominal_reversal_ever_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_38_neologisms_current_code'] =='8' AND $score_record3['q_38_neologisms_current_code']=='8'){}
            elseif($score_record['q_38_neologisms_current_code'] =='998' && $score_record3['q_38_neologisms_current_code']=='998'){}
            else {
                    $denominator++;
                    if ($score_record['q_38_neologisms_current_code'] != $score_record3['q_38_neologisms_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_38_neologisms_ever_code'] =='8' AND $score_record3['q_38_neologisms_ever_code']=='8'){}
            elseif($score_record['q_38_neologisms_ever_code'] =='998' && $score_record3['q_38_neologisms_ever_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if ($score_record['q_38_neologisms_ever_code'] != $score_record3['q_38_neologisms_ever_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_39_verbal_rituals_current_code'] =='8' AND $score_record3['q_39_verbal_rituals_current_code']=='8'){}
            elseif($score_record['q_39_verbal_rituals_current_code'] =='998' && $score_record3['q_39_verbal_rituals_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_39_verbal_rituals_current_code'] != $score_record3['q_39_verbal_rituals_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_39_verbal_rituals_ever_code'] =='8' AND $score_record3['q_39_verbal_rituals_ever_code']=='8'){}
            elseif($score_record['q_39_verbal_rituals_ever_code'] =='998' && $score_record3['q_39_verbal_rituals_ever_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if ($score_record['q_39_verbal_rituals_ever_code'] != $score_record3['q_39_verbal_rituals_ever_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_40_inton_vol_rhythm_rate_current_code'] =='8' AND $score_record3['q_40_inton_vol_rhythm_rate_current_code']=='8'){}
                elseif($score_record['q_40_inton_vol_rhythm_rate_current_code'] =='998' && $score_record3['q_40_inton_vol_rhythm_rate_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_40_inton_vol_rhythm_rate_current_code'] != $score_record3['q_40_inton_vol_rhythm_rate_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_40_inton_vol_rhythm_rate_ever_code'] =='8' AND $score_record3['q_40_inton_vol_rhythm_rate_ever_code']=='8'){}
            elseif($score_record['q_40_inton_vol_rhythm_rate_ever_code'] =='998' && $score_record3['q_40_inton_vol_rhythm_rate_ever_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_40_inton_vol_rhythm_rate_ever_code'] != $score_record3['q_40_inton_vol_rhythm_rate_ever_code']){ $reliability_count_raw++;}} 
            if($score_record['q_41_cur_comm_speech_current_code'] =='8' AND $score_record3['q_41_cur_comm_speech_current_code']=='8'){}
            elseif($score_record['q_41_cur_comm_speech_current_code'] =='998' && $score_record3['q_41_cur_comm_speech_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_41_cur_comm_speech_current_code'] != $score_record3['q_41_cur_comm_speech_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_41_cur_comm_speech_at5_code'] =='8' AND $score_record3['q_41_cur_comm_speech_at5_code']=='8'){}
            elseif($score_record['q_41_cur_comm_speech_at5_code'] =='998' && $score_record3['q_41_cur_comm_speech_at5_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_41_cur_comm_speech_at5_code'] != $score_record3['q_41_cur_comm_speech_at5_code']){ $reliability_count_raw++;}} 
            if($score_record['q_42_point_express_interest_current_code'] =='8' AND $score_record3['q_42_point_express_interest_current_code']=='8'){}
            elseif($score_record['q_42_point_express_interest_current_code'] =='998' && $score_record3['q_42_point_express_interest_current_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if ($score_record['q_42_point_express_interest_current_code'] != $score_record3['q_42_point_express_interest_current_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_42_point_express_inter_most_abnormal_code'] =='8' AND $score_record3['q_42_point_express_inter_most_abnormal_code']=='8'){}
            elseif($score_record['q_42_point_express_inter_most_abnormal_code'] =='998' && $score_record3['q_42_point_express_inter_most_abnormal_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_42_point_express_inter_most_abnormal_code'] != $score_record3['q_42_point_express_inter_most_abnormal_code']){ $reliability_count_raw++;}} 
            if($score_record['q_43_nodding_current_code'] =='8' AND $score_record3['q_43_nodding_current_code']=='8'){}
            elseif($score_record['q_43_nodding_current_code'] =='998' && $score_record3['q_43_nodding_current_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if ($score_record['q_43_nodding_current_code'] != $score_record3['q_43_nodding_current_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_43_nodding_most_abnormal_code'] =='8' AND $score_record3['q_43_nodding_most_abnormal_code']=='8'){}
            elseif($score_record['q_43_nodding_most_abnormal_code'] =='998' && $score_record3['q_43_nodding_most_abnormal_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_43_nodding_most_abnormal_code'] != $score_record3['q_43_nodding_most_abnormal_code']){ $reliability_count_raw++;}} 
            if($score_record['q_44_head_shaking_current_code'] =='8' AND $score_record3['q_44_head_shaking_current_code']=='8'){}
            elseif($score_record['q_44_head_shaking_current_code'] =='998' && $score_record3['q_44_head_shaking_current_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if ($score_record['q_44_head_shaking_current_code'] != $score_record3['q_44_head_shaking_current_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_44_head_shaking_most_abnormal_code'] =='8' AND $score_record3['q_44_head_shaking_most_abnormal_code']=='8'){}
            elseif($score_record['q_44_head_shaking_most_abnormal_code'] =='998' && $score_record3['q_44_head_shaking_most_abnormal_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_44_head_shaking_most_abnormal_code'] != $score_record3['q_44_head_shaking_most_abnormal_code']){ $reliability_count_raw++;}} 
            if($score_record['q_45_conventional_instr_gests_current_code'] =='8' AND $score_record3['q_45_conventional_instr_gests_current_code']=='8'){}
            elseif($score_record['q_45_conventional_instr_gests_current_code'] =='998' && $score_record3['q_45_conventional_instr_gests_current_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if (($score_record['q_45_conventional_instr_gests_current_code'] =='2' AND $score_record3['q_45_conventional_instr_gests_current_code']=='3') ||
                    ($score_record['q_45_conventional_instr_gests_current_code'] =='3' AND $score_record3['q_45_conventional_instr_gests_current_code']=='2'))
                   {
                      #Don't count this
                   }
                   else if ($score_record['q_45_conventional_instr_gests_current_code'] != $score_record3['q_45_conventional_instr_gests_current_code']){ $reliability_count_raw++; $reliability_count_scored++;}}              
            if($score_record['q_45_conventional_instr_gests_most_abnormal_code'] =='8' AND $score_record3['q_45_conventional_instr_gests_most_abnormal_code']=='8'){}
            elseif($score_record['q_45_conventional_instr_gests_most_abnormal_code'] =='998' && $score_record3['q_45_conventional_instr_gests_most_abnormal_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_45_conventional_instr_gests_most_abnormal_code'] != $score_record3['q_45_conventional_instr_gests_most_abnormal_code']){ $reliability_count_raw++;}} 
            if($score_record['q_46_attent_voice_current_code'] =='8' AND $score_record3['q_46_attent_voice_current_code']=='8'){}
            elseif($score_record['q_46_attent_voice_current_code'] =='998' && $score_record3['q_46_attent_voice_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_46_attent_voice_current_code'] != $score_record3['q_46_attent_voice_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_46_attent_voice_most_abnormal_code'] =='8' AND $score_record3['q_46_attent_voice_most_abnormal_code']=='8'){}
            elseif($score_record['q_46_attent_voice_most_abnormal_code'] =='998' && $score_record3['q_46_attent_voice_most_abnormal_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_46_attent_voice_most_abnormal_code'] != $score_record3['q_46_attent_voice_most_abnormal_code']){ $reliability_count_raw++;}} 
            if($score_record['q_47_spont_imit_current_code'] =='8' AND $score_record3['q_47_spont_imit_current_code']=='8'){}
            elseif($score_record['q_47_spont_imit_current_code'] =='998' && $score_record3['q_47_spont_imit_current_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if (($score_record['q_47_spont_imit_current_code'] =='2' AND $score_record3['q_47_spont_imit_current_code']=='3') ||
                     ($score_record['q_47_spont_imit_current_code'] =='3' AND $score_record3['q_47_spont_imit_current_code']=='2'))
                    {
                       #Don't count this
                    }
                    else if ($score_record['q_47_spont_imit_current_code'] != $score_record3['q_47_spont_imit_current_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_47_spont_imit_most_abnormal_code'] =='8' AND $score_record3['q_47_spont_imit_most_abnormal_code']=='8'){}
            elseif($score_record['q_47_spont_imit_most_abnormal_code'] =='998' && $score_record3['q_47_spont_imit_most_abnormal_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_47_spont_imit_most_abnormal_code'] != $score_record3['q_47_spont_imit_most_abnormal_code']){ $reliability_count_raw++;}} 
            if($score_record['q_48_imag_play_current_code'] =='8' AND $score_record3['q_48_imag_play_current_code']=='8'){}
            elseif($score_record['q_48_imag_play_current_code'] =='998' && $score_record3['q_48_imag_play_current_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if ($score_record['q_48_imag_play_current_code'] != $score_record3['q_48_imag_play_current_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_48_imag_play_most_abnormal_code'] =='8' AND $score_record3['q_48_imag_play_most_abnormal_code']=='8'){}
            elseif($score_record['q_48_imag_play_most_abnormal_code'] =='998' && $score_record3['q_48_imag_play_most_abnormal_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_48_imag_play_most_abnormal_code'] != $score_record3['q_48_imag_play_most_abnormal_code']){ $reliability_count_raw++;}} 
            if($score_record['q_49_imag_play_peers_current_code'] =='8' AND $score_record3['q_49_imag_play_peers_current_code']=='8'){}
            elseif($score_record['q_49_imag_play_peers_current_code'] =='998' && $score_record3['q_49_imag_play_peers_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_49_imag_play_peers_current_code'] != $score_record3['q_49_imag_play_peers_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_49_imag_play_peers_most_abnormal_code'] =='8' AND $score_record3['q_49_imag_play_peers_most_abnormal_code']=='8'){}
            elseif($score_record['q_49_imag_play_peers_most_abnormal_code'] =='998' && $score_record3['q_49_imag_play_peers_most_abnormal_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_49_imag_play_peers_most_abnormal_code'] != $score_record3['q_49_imag_play_peers_most_abnormal_code']){ $reliability_count_raw++;}} 
            if($score_record['q_50_direct_gaze_current_code'] =='8' AND $score_record3['q_50_direct_gaze_current_code']=='8'){}
            elseif($score_record['q_50_direct_gaze_current_code'] =='998' && $score_record3['q_50_direct_gaze_current_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if ($score_record['q_50_direct_gaze_current_code'] != $score_record3['q_50_direct_gaze_current_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_50_direct_gaze_most_abnormal_code'] =='8' AND $score_record3['q_50_direct_gaze_most_abnormal_code']=='8'){}
            elseif($score_record['q_50_direct_gaze_most_abnormal_code'] =='998' && $score_record3['q_50_direct_gaze_most_abnormal_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_50_direct_gaze_most_abnormal_code'] != $score_record3['q_50_direct_gaze_most_abnormal_code']){ $reliability_count_raw++;}} 
            if($score_record['q_51_social_smiling_current_code'] =='8' AND $score_record3['q_51_social_smiling_current_code']=='8'){}
            elseif($score_record['q_51_social_smiling_current_code'] =='998' && $score_record3['q_51_social_smiling_current_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if ($score_record['q_51_social_smiling_current_code'] != $score_record3['q_51_social_smiling_current_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_51_social_smiling_most_abnormal_code'] =='8' AND $score_record3['q_51_social_smiling_most_abnormal_code']=='8'){}
            elseif($score_record['q_51_social_smiling_most_abnormal_code'] =='998' && $score_record3['q_51_social_smiling_most_abnormal_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_51_social_smiling_most_abnormal_code'] != $score_record3['q_51_social_smiling_most_abnormal_code']){ $reliability_count_raw++;}} 
            if($score_record['q_52_show_direct_atten_current_code'] =='8' AND $score_record3['q_52_show_direct_atten_current_code']=='8'){}
            elseif($score_record['q_52_show_direct_atten_current_code'] =='998' && $score_record3['q_52_show_direct_atten_current_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if ($score_record['q_52_show_direct_atten_current_code'] != $score_record3['q_52_show_direct_atten_current_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_52_show_direct_atten_most_abnormal_code'] =='8' AND $score_record3['q_52_show_direct_atten_most_abnormal_code']=='8'){}
            elseif($score_record['q_52_show_direct_atten_most_abnormal_code'] =='998' && $score_record3['q_52_show_direct_atten_most_abnormal_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_52_show_direct_atten_most_abnormal_code'] != $score_record3['q_52_show_direct_atten_most_abnormal_code']){ $reliability_count_raw++;}} 
            if($score_record['q_53_offer_share_current_code'] =='8' AND $score_record3['q_53_offer_share_current_code']=='8'){}
            elseif($score_record['q_53_offer_share_current_code'] =='998' && $score_record3['q_53_offer_share_current_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if (($score_record['q_53_offer_share_current_code'] =='2' AND $score_record3['q_53_offer_share_current_code']=='3') ||
                      ($score_record['q_53_offer_share_current_code'] =='3' AND $score_record3['q_53_offer_share_current_code']=='2'))
                     {
                        #Don't count this
                     }
                     else if ($score_record['q_53_offer_share_current_code'] != $score_record3['q_53_offer_share_current_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_53_offer_share_most_abnormal_code'] =='8' AND $score_record3['q_53_offer_share_most_abnormal_code']=='8'){}
            elseif($score_record['q_53_offer_share_most_abnormal_code'] =='998' && $score_record3['q_53_offer_share_most_abnormal_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_53_offer_share_most_abnormal_code'] != $score_record3['q_53_offer_share_most_abnormal_code']){ $reliability_count_raw++;}} 
            if($score_record['q_54_seek_share_enjoy_current_code'] =='8' AND $score_record3['q_54_seek_share_enjoy_current_code']=='8'){}
            elseif($score_record['q_54_seek_share_enjoy_current_code'] =='998' && $score_record3['q_54_seek_share_enjoy_current_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if ($score_record['q_54_seek_share_enjoy_current_code'] != $score_record3['q_54_seek_share_enjoy_current_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_54_seek_share_enjoy_most_abnormal_code'] =='8' AND $score_record3['q_54_seek_share_enjoy_most_abnormal_code']=='8'){}
            elseif($score_record['q_54_seek_share_enjoy_most_abnormal_code'] =='998' && $score_record3['q_54_seek_share_enjoy_most_abnormal_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_54_seek_share_enjoy_most_abnormal_code'] != $score_record3['q_54_seek_share_enjoy_most_abnormal_code']){ $reliability_count_raw++;}} 
            if($score_record['q_55_offer_comf_current_code'] =='8' AND $score_record3['q_55_offer_comf_current_code']=='8'){}
            elseif($score_record['q_55_offer_comf_current_code'] =='998' && $score_record3['q_55_offer_comf_current_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if (($score_record['q_55_offer_comf_current_code'] =='2' AND $score_record3['q_55_offer_comf_current_code']=='3') ||
                       ($score_record['q_55_offer_comf_current_code'] =='3' AND $score_record3['q_55_offer_comf_current_code']=='2'))
                      {
                         #Don't count this
                      }
                      else if ($score_record['q_55_offer_comf_current_code'] != $score_record3['q_55_offer_comf_current_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_55_offer_comf_most_abnormal_code'] =='8' AND $score_record3['q_55_offer_comf_most_abnormal_code']=='8'){}
            elseif($score_record['q_55_offer_comf_most_abnormal_code'] =='998' && $score_record3['q_55_offer_comf_most_abnormal_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_55_offer_comf_most_abnormal_code'] != $score_record3['q_55_offer_comf_most_abnormal_code']){ $reliability_count_raw++;}} 
            if($score_record['q_56_qual_social_overts_current_code'] =='8' AND $score_record3['q_56_qual_social_overts_current_code']=='8'){}
            elseif($score_record['q_56_qual_social_overts_current_code'] =='998' && $score_record3['q_56_qual_social_overts_current_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if (($score_record['q_56_qual_social_overts_current_code'] =='2' AND $score_record3['q_56_qual_social_overts_current_code']=='3') ||
                   ($score_record['q_56_qual_social_overts_current_code'] =='3' AND $score_record3['q_56_qual_social_overts_current_code']=='2'))
                  {
                     #Don't count this
                  }
                  else if ($score_record['q_56_qual_social_overts_current_code'] != $score_record3['q_56_qual_social_overts_current_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_56_qual_social_overts_most_abnormal_code'] =='8' AND $score_record3['q_56_qual_social_overts_most_abnormal_code']=='8'){}
            elseif($score_record['q_56_qual_social_overts_most_abnormal_code'] =='998' && $score_record3['q_56_qual_social_overts_most_abnormal_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_56_qual_social_overts_most_abnormal_code'] != $score_record3['q_56_qual_social_overts_most_abnormal_code']){ $reliability_count_raw++;}}             
            if($score_record['q_57_range_facial_expr_current_code'] =='8' AND $score_record3['q_57_range_facial_expr_current_code']=='8'){}
            elseif($score_record['q_57_range_facial_expr_current_code'] =='998' && $score_record3['q_57_range_facial_expr_current_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if ($score_record['q_57_range_facial_expr_current_code'] != $score_record3['q_57_range_facial_expr_current_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_57_range_facial_expr_most_abnormal_code'] =='8' AND $score_record3['q_57_range_facial_expr_most_abnormal_code']=='8'){}
                elseif($score_record['q_57_range_facial_expr_most_abnormal_code'] =='998' && $score_record3['q_57_range_facial_expr_most_abnormal_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_57_range_facial_expr_most_abnormal_code'] != $score_record3['q_57_range_facial_expr_most_abnormal_code']){ $reliability_count_raw++;}} 
            if($score_record['q_58_inappropriate_facial_current_code'] =='8' AND $score_record3['q_58_inappropriate_facial_current_code']=='8'){}
            elseif($score_record['q_58_inappropriate_facial_current_code'] =='998' && $score_record3['q_58_inappropriate_facial_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_58_inappropriate_facial_current_code'] != $score_record3['q_58_inappropriate_facial_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_58_inappropriate_facial_ever_code'] =='8' AND $score_record3['q_58_inappropriate_facial_ever_code']=='8'){}
            elseif($score_record['q_58_inappropriate_facial_ever_code'] =='998' && $score_record3['q_58_inappropriate_facial_ever_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if ($score_record['q_58_inappropriate_facial_ever_code'] != $score_record3['q_58_inappropriate_facial_ever_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_59_appropriat_resp_current_code'] =='8' AND $score_record3['q_59_appropriat_resp_current_code']=='8'){}
            elseif($score_record['q_59_appropriat_resp_current_code'] =='998' && $score_record3['q_59_appropriat_resp_current_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if (($score_record['q_59_appropriat_resp_current_code'] =='2' AND $score_record3['q_59_appropriat_resp_current_code']=='3') ||
                    ($score_record['q_59_appropriat_resp_current_code'] =='3' AND $score_record3['q_59_appropriat_resp_current_code']=='2'))
                   {
                      #Don't count this
                   }
                   elseif ($score_record['q_59_appropriat_resp_current_code'] != $score_record3['q_59_appropriat_resp_current_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_59_appropriat_resp_most_abnormal_code'] =='8' AND $score_record3['q_59_appropriat_resp_most_abnormal_code']=='8'){}
            elseif($score_record['q_59_appropriat_resp_most_abnormal_code'] =='998' && $score_record3['q_59_appropriat_resp_most_abnormal_code']=='998'){}
            else {
                $denominator++;
                    if ($score_record['q_59_appropriat_resp_most_abnormal_code'] != $score_record3['q_59_appropriat_resp_most_abnormal_code']){ $reliability_count_raw++;}} 
            if($score_record['q_60_init_activities_current_code'] =='8' AND $score_record3['q_60_init_activities_current_code']=='8'){}
            elseif($score_record['q_60_init_activities_current_code'] =='998' && $score_record3['q_60_init_activities_current_code']=='998'){}
            else {
                $denominator++;
                if (($score_record['q_60_init_activities_current_code'] =='2' AND $score_record3['q_60_init_activities_current_code']=='3') ||
                     ($score_record['q_60_init_activities_current_code'] =='3' AND $score_record3['q_60_init_activities_current_code']=='2'))
                    {
                       #Don't count this
                    }
                    else if ($score_record['q_60_init_activities_current_code'] != $score_record3['q_60_init_activities_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_60_init_activities_most_abnormal_code'] =='8' AND $score_record3['q_60_init_activities_most_abnormal_code']=='8'){}
            elseif($score_record['q_60_init_activities_most_abnormal_code'] =='998' && $score_record3['q_60_init_activities_most_abnormal_code']=='998'){}
            else {
                    $denominator++;
                    if ($score_record['q_60_init_activities_most_abnormal_code'] != $score_record3['q_60_init_activities_most_abnormal_code']){ $reliability_count_raw++;}} 
            if($score_record['q_61_imit_soc_play_current_code'] =='8' AND $score_record3['q_61_imit_soc_play_current_code']=='8'){}
            elseif($score_record['q_61_imit_soc_play_current_code'] =='998' && $score_record3['q_61_imit_soc_play_current_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if ($score_record['q_61_imit_soc_play_current_code'] != $score_record3['q_61_imit_soc_play_current_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_61_imit_soc_play_most_abnormal_code'] =='8' AND $score_record3['q_61_imit_soc_play_most_abnormal_code']=='8'){}
            elseif($score_record['q_61_imit_soc_play_most_abnormal_code'] =='998' && $score_record3['q_61_imit_soc_play_most_abnormal_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_61_imit_soc_play_most_abnormal_code'] != $score_record3['q_61_imit_soc_play_most_abnormal_code']){ $reliability_count_raw++;}} 
            if($score_record['q_62_inter_children_current_code'] =='8' AND $score_record3['q_62_inter_children_current_code']=='8'){}
            elseif($score_record['q_62_inter_children_current_code'] =='998' && $score_record3['q_62_inter_children_current_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if (($score_record['q_62_inter_children_current_code'] =='2' AND $score_record3['q_62_inter_children_current_code']=='3') ||
                      ($score_record['q_62_inter_children_current_code'] =='3' AND $score_record3['q_62_inter_children_current_code']=='2'))
                     {
                        #Don't count this
                     }
                     else if ($score_record['q_62_inter_children_current_code'] != $score_record3['q_62_inter_children_current_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_62_inter_children_most_abnormal_code'] =='8' AND $score_record3['q_62_inter_children_most_abnormal_code']=='8'){}
            elseif($score_record['q_62_inter_children_most_abnormal_code'] =='998' && $score_record3['q_62_inter_children_most_abnormal_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_62_inter_children_most_abnormal_code'] != $score_record3['q_62_inter_children_most_abnormal_code']){ $reliability_count_raw++;}} 
            if($score_record['q_63_resp_approaches_current_code'] =='8' AND $score_record3['q_63_resp_approaches_current_code']=='8'){}
            elseif($score_record['q_63_resp_approaches_current_code'] =='998' && $score_record3['q_63_resp_approaches_current_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if ($score_record['q_63_resp_approaches_current_code'] != $score_record3['q_63_resp_approaches_current_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_63_resp_approaches_most_abnormal_code'] =='8' AND $score_record3['q_63_resp_approaches_most_abnormal_code']=='8'){}
            elseif($score_record['q_63_resp_approaches_most_abnormal_code'] =='998' && $score_record3['q_63_resp_approaches_most_abnormal_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_63_resp_approaches_most_abnormal_code'] != $score_record3['q_63_resp_approaches_most_abnormal_code']){ $reliability_count_raw++;}} 
            if($score_record['q_64_group_play_peers_current_code'] =='8' AND $score_record3['q_64_group_play_peers_current_code']=='8'){}
            elseif($score_record['q_64_group_play_peers_current_code'] =='998' && $score_record3['q_64_group_play_peers_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_64_group_play_peers_current_code'] != $score_record3['q_64_group_play_peers_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_64_group_play_peers_most_abnormal_code'] =='8' AND $score_record3['q_64_group_play_peers_most_abnormal_code']=='8'){}
            elseif($score_record['q_64_group_play_peers_most_abnormal_code'] =='998' && $score_record3['q_64_group_play_peers_most_abnormal_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_64_group_play_peers_most_abnormal_code'] != $score_record3['q_64_group_play_peers_most_abnormal_code']){ $reliability_count_raw++;}} 
            if($score_record['q_65_friendships_current_code'] =='8' AND $score_record3['q_65_friendships_current_code']=='8'){}
            elseif($score_record['q_65_friendships_current_code'] =='998' && $score_record3['q_65_friendships_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_65_friendships_current_code'] != $score_record3['q_65_friendships_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_65_friendships_most_abnormal_code'] =='8' AND $score_record3['q_65_friendships_most_abnormal_code']=='8'){}
            elseif($score_record['q_65_friendships_most_abnormal_code'] =='998' && $score_record3['q_65_friendships_most_abnormal_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_65_friendships_most_abnormal_code'] != $score_record3['q_65_friendships_most_abnormal_code']){ $reliability_count_raw++;}} 
            if($score_record['q_66_soc_disinhibit_current_code'] =='8' AND $score_record3['q_66_soc_disinhibit_current_code']=='8'){}
            elseif($score_record['q_66_soc_disinhibit_current_code'] =='998' && $score_record3['q_66_soc_disinhibit_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_66_soc_disinhibit_current_code'] != $score_record3['q_66_soc_disinhibit_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_66_soc_disinhibit_most_abnormal_code'] =='8' AND $score_record3['q_66_soc_disinhibit_most_abnormal_code']=='8'){}
            elseif($score_record['q_66_soc_disinhibit_most_abnormal_code'] =='998' && $score_record3['q_66_soc_disinhibit_most_abnormal_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_66_soc_disinhibit_most_abnormal_code'] != $score_record3['q_66_soc_disinhibit_most_abnormal_code']){ $reliability_count_raw++;}} 
            if($score_record['q_67_unusual_preoccupations_current_code'] =='8' AND $score_record3['q_67_unusual_preoccupations_current_code']=='8'){}
            elseif($score_record['q_67_unusual_preoccupations_current_code'] =='998' && $score_record3['q_67_unusual_preoccupations_current_code']=='998'){}
            else {
                $denominator++;
                if (($score_record['q_67_unusual_preoccupations_current_code'] =='2' AND $score_record3['q_67_unusual_preoccupations_current_code']=='3') ||
                       ($score_record['q_67_unusual_preoccupations_current_code'] =='3' AND $score_record3['q_67_unusual_preoccupations_current_code']=='2'))
                      {
                         #Don't count this
                      }
                      else if ($score_record['q_67_unusual_preoccupations_current_code'] != $score_record3['q_67_unusual_preoccupations_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_67_unusual_preoccupations_ever_code'] =='8' AND $score_record3['q_67_unusual_preoccupations_ever_code']=='8'){}
            elseif($score_record['q_67_unusual_preoccupations_ever_code'] =='998' && $score_record3['q_67_unusual_preoccupations_ever_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if (($score_record['q_67_unusual_preoccupations_ever_code'] =='2' AND $score_record3['q_67_unusual_preoccupations_ever_code']=='3') ||
                        ($score_record['q_67_unusual_preoccupations_ever_code'] =='3' AND $score_record3['q_67_unusual_preoccupations_ever_code']=='2'))
                       {
                          #Don't count this
                       }
                       else if ($score_record['q_67_unusual_preoccupations_ever_code'] != $score_record3['q_67_unusual_preoccupations_ever_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_68_circumscr_ints_current_code'] =='8' AND $score_record3['q_68_circumscr_ints_current_code']=='8'){}
            elseif($score_record['q_68_circumscr_ints_current_code'] =='998' && $score_record3['q_68_circumscr_ints_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_68_circumscr_ints_current_code'] != $score_record3['q_68_circumscr_ints_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_68_circumscr_ints_ever_code'] =='8' AND $score_record3['q_68_circumscr_ints_ever_code']=='8'){}
            elseif($score_record['q_68_circumscr_ints_ever_code'] =='998' && $score_record3['q_68_circumscr_ints_ever_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if ($score_record['q_68_circumscr_ints_ever_code'] != $score_record3['q_68_circumscr_ints_ever_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_69_repet_use_objects_current_code'] =='8' AND $score_record3['q_69_repet_use_objects_current_code']=='8'){}
            elseif($score_record['q_69_repet_use_objects_current_code'] =='998' && $score_record3['q_69_repet_use_objects_current_code']=='998'){}
            else {
                $denominator++;
                if (($score_record['q_69_repet_use_objects_current_code'] =='2' AND $score_record3['q_69_repet_use_objects_current_code']=='3') ||
                         ($score_record['q_69_repet_use_objects_current_code'] =='3' AND $score_record3['q_69_repet_use_objects_current_code']=='2'))
                        {
                           #Don't count this
                        }
                        else if ($score_record['q_69_repet_use_objects_current_code'] != $score_record3['q_69_repet_use_objects_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_69_repet_use_objects_ever_code'] =='8' AND $score_record3['q_69_repet_use_objects_ever_code']=='8'){}
            elseif($score_record['q_69_repet_use_objects_ever_code'] =='998' && $score_record3['q_69_repet_use_objects_ever_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if (($score_record['q_69_repet_use_objects_ever_code'] =='2' AND $score_record3['q_69_repet_use_objects_ever_code']=='3') ||
                   ($score_record['q_69_repet_use_objects_ever_code'] =='3' AND $score_record3['q_69_repet_use_objects_ever_code']=='2'))
                  {
                     #Don't count this
                  }
                  else if ($score_record['q_69_repet_use_objects_ever_code'] != $score_record3['q_69_repet_use_objects_ever_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_70_compulsions_rituals_current_code'] =='8' AND $score_record3['q_70_compulsions_rituals_current_code']=='8'){}
            elseif($score_record['q_70_compulsions_rituals_current_code'] =='998' && $score_record3['q_70_compulsions_rituals_current_code']=='998'){}
            else {
                $denominator++;
                if (($score_record['q_70_compulsions_rituals_current_code'] =='2' AND $score_record3['q_70_compulsions_rituals_current_code']=='3') ||
                    ($score_record['q_70_compulsions_rituals_current_code'] =='3' AND $score_record3['q_70_compulsions_rituals_current_code']=='2'))
                   {
                      #Don't count this
                   }
                   else if ($score_record['q_70_compulsions_rituals_current_code'] != $score_record3['q_70_compulsions_rituals_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_70_compulsions_rituals_ever_code'] =='8' AND $score_record3['q_70_compulsions_rituals_ever_code']=='8'){}
            elseif($score_record['q_70_compulsions_rituals_ever_code'] =='998' && $score_record3['q_70_compulsions_rituals_ever_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if (($score_record['q_70_compulsions_rituals_ever_code'] =='2' AND $score_record3['q_70_compulsions_rituals_ever_code']=='3') ||
                     ($score_record['q_70_compulsions_rituals_ever_code'] =='3' AND $score_record3['q_70_compulsions_rituals_ever_code']=='2'))
                    {
                       #Don't count this
                    }
                    else if ($score_record['q_70_compulsions_rituals_ever_code'] != $score_record3['q_70_compulsions_rituals_ever_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_71_unusual_sens_ints_current_code'] =='8' AND $score_record3['q_71_unusual_sens_ints_current_code']=='8'){}
            elseif($score_record['q_71_unusual_sens_ints_current_code'] =='998' && $score_record3['q_71_unusual_sens_ints_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_71_unusual_sens_ints_current_code'] != $score_record3['q_71_unusual_sens_ints_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_71_unusual_sens_ints_ever_code'] =='8' AND $score_record3['q_71_unusual_sens_ints_ever_code']=='8'){}
            elseif($score_record['q_71_unusual_sens_ints_ever_code'] =='998' && $score_record3['q_71_unusual_sens_ints_ever_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if ($score_record['q_71_unusual_sens_ints_ever_code'] != $score_record3['q_71_unusual_sens_ints_ever_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_72_undo_gen_sens_noise_current_code'] =='8' AND $score_record3['q_72_undo_gen_sens_noise_current_code']=='8'){}
            elseif($score_record['q_72_undo_gen_sens_noise_current_code'] =='998' && $score_record3['q_72_undo_gen_sens_noise_current_code']=='998'){}
            else {
                $denominator++;
                if (($score_record['q_72_undo_gen_sens_noise_current_code'] =='2' AND $score_record3['q_72_undo_gen_sens_noise_current_code']=='3') ||
                      ($score_record['q_72_undo_gen_sens_noise_current_code'] =='3' AND $score_record3['q_72_undo_gen_sens_noise_current_code']=='2'))
                     {
                        #Don't count this
                     }
                     else if ($score_record['q_72_undo_gen_sens_noise_current_code'] != $score_record3['q_72_undo_gen_sens_noise_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_72_undo_gen_sens_noise_ever_code'] =='8' AND $score_record3['q_72_undo_gen_sens_noise_ever_code']=='8'){}
            elseif($score_record['q_72_undo_gen_sens_noise_ever_code'] =='998' && $score_record3['q_72_undo_gen_sens_noise_ever_code']=='998'){}
            else {
                $denominator++;
                if (($score_record['q_72_undo_gen_sens_noise_ever_code'] =='2' AND $score_record3['q_72_undo_gen_sens_noise_ever_code']=='3') ||
                  ($score_record['q_72_undo_gen_sens_noise_ever_code'] =='3' AND $score_record3['q_72_undo_gen_sens_noise_ever_code']=='2'))
                 {
                    #Don't count this
                 }
                 else if ($score_record['q_72_undo_gen_sens_noise_ever_code'] != $score_record3['q_72_undo_gen_sens_noise_ever_code']){ $reliability_count_raw++;}} 
            if($score_record['q_73_idiosyncratic_current_code'] =='8' AND $score_record3['q_73_idiosyncratic_current_code']=='8'){}
            elseif($score_record['q_73_idiosyncratic_current_code'] =='998' && $score_record3['q_73_idiosyncratic_current_code']=='998'){}
            else {
                $denominator++;
                if (($score_record['q_73_idiosyncratic_current_code'] =='2' AND $score_record3['q_73_idiosyncratic_current_code']=='3') ||
                   ($score_record['q_73_idiosyncratic_current_code'] =='3' AND $score_record3['q_73_idiosyncratic_current_code']=='2'))
                  {
                     #Don't count this
                  }
                  else if ($score_record['q_73_idiosyncratic_current_code'] != $score_record3['q_73_idiosyncratic_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_73_idiosyncratic_ever_code'] =='8' AND $score_record3['q_73_idiosyncratic_ever_code']=='8'){}
            elseif($score_record['q_73_idiosyncratic_ever_code'] =='998' && $score_record3['q_73_idiosyncratic_ever_code']=='998'){}
            else {
                $denominator++;
                if (($score_record['q_73_idiosyncratic_ever_code'] =='2' AND $score_record3['q_73_idiosyncratic_ever_code']=='3') ||
                    ($score_record['q_73_idiosyncratic_ever_code'] =='3' AND $score_record3['q_73_idiosyncratic_ever_code']=='2'))
                   {
                      #Don't count this
                   }
                   else if ($score_record['q_73_idiosyncratic_ever_code'] != $score_record3['q_73_idiosyncratic_ever_code']){ $reliability_count_raw++;}} 
            if($score_record['q_74_diff_minor_changes_current_code'] =='8' AND $score_record3['q_74_diff_minor_changes_current_code']=='8'){}
            elseif($score_record['q_74_diff_minor_changes_current_code'] =='998' && $score_record3['q_74_diff_minor_changes_current_code']=='998'){}
            else {
                $denominator++;
                if (($score_record['q_74_diff_minor_changes_current_code'] =='2' AND $score_record3['q_74_diff_minor_changes_current_code']=='3') ||
                     ($score_record['q_74_diff_minor_changes_current_code'] =='3' AND $score_record3['q_74_diff_minor_changes_current_code']=='2'))
                    {
                       #Don't count this
                    }
                    else if ($score_record['q_74_diff_minor_changes_current_code'] != $score_record3['q_74_diff_minor_changes_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_74_diff_minor_changes_ever_code'] =='8' AND $score_record3['q_74_diff_minor_changes_ever_code']=='8'){}
            elseif($score_record['q_74_diff_minor_changes_ever_code'] =='998' && $score_record3['q_74_diff_minor_changes_ever_code']=='998'){}
            else {
                $denominator++;
                if (($score_record['q_74_diff_minor_changes_ever_code'] =='2' AND $score_record3['q_74_diff_minor_changes_ever_code']=='3') ||
                      ($score_record['q_74_diff_minor_changes_ever_code'] =='3' AND $score_record3['q_74_diff_minor_changes_ever_code']=='2'))
                     {
                        #Don't count this
                     }
                     else if ($score_record['q_74_diff_minor_changes_ever_code'] != $score_record3['q_74_diff_minor_changes_ever_code']){ $reliability_count_raw++;}} 
            if($score_record['q_75_resist_trivial_chng_current_code'] =='8' AND $score_record3['q_75_resist_trivial_chng_current_code']=='8'){}
            elseif($score_record['q_75_resist_trivial_chng_current_code'] =='998' && $score_record3['q_75_resist_trivial_chng_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_75_resist_trivial_chng_current_code'] != $score_record3['q_75_resist_trivial_chng_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_75_resist_trivial_chng_ever_code'] =='8' AND $score_record3['q_75_resist_trivial_chng_ever_code']=='8'){}
            elseif($score_record['q_75_resist_trivial_chng_ever_code'] =='998' && $score_record3['q_75_resist_trivial_chng_ever_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_75_resist_trivial_chng_ever_code'] != $score_record3['q_75_resist_trivial_chng_ever_code']){ $reliability_count_raw++;}} 
            if($score_record['q_76_unus_attach_objects_current_code'] =='8' AND $score_record3['q_76_unus_attach_objects_current_code']=='8'){}
            elseif($score_record['q_76_unus_attach_objects_current_code'] =='998' && $score_record3['q_76_unus_attach_objects_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_76_unus_attach_objects_current_code'] != $score_record3['q_76_unus_attach_objects_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_76_unus_attach_objects_ever_code'] =='8' AND $score_record3['q_76_unus_attach_objects_ever_code']=='8'){}
            elseif($score_record['q_76_unus_attach_objects_ever_code'] =='998' && $score_record3['q_76_unus_attach_objects_ever_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_76_unus_attach_objects_ever_code'] != $score_record3['q_76_unus_attach_objects_ever_code']){ $reliability_count_raw++;}} 
            if($score_record['q_77_hands_finger_manners_current_code'] =='8' AND $score_record3['q_77_hands_finger_manners_current_code']=='8'){}
            elseif($score_record['q_77_hands_finger_manners_current_code'] =='998' && $score_record3['q_77_hands_finger_manners_current_code']=='998'){}
            else {
                $denominator++;
                if (($score_record['q_77_hands_finger_manners_current_code'] =='2' AND $score_record3['q_77_hands_finger_manners_current_code']=='3') ||
                       ($score_record['q_77_hands_finger_manners_current_code'] =='3' AND $score_record3['q_77_hands_finger_manners_current_code']=='2'))
                      {
                         #Don't count this
                      }
                      else if ($score_record['q_77_hands_finger_manners_current_code'] != $score_record3['q_77_hands_finger_manners_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_77_hands_finger_manners_ever_code'] =='8' AND $score_record3['q_77_hands_finger_manners_ever_code']=='8'){}
            elseif($score_record['q_77_hands_finger_manners_ever_code'] =='998' && $score_record3['q_77_hands_finger_manners_ever_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if (($score_record['q_77_hands_finger_manners_ever_code'] =='2' AND $score_record3['q_77_hands_finger_manners_ever_code']=='3') ||
                        ($score_record['q_77_hands_finger_manners_ever_code'] =='3' AND $score_record3['q_77_hands_finger_manners_ever_code']=='2'))
                       {
                          #Don't count this
                       }
                       else if ($score_record['q_77_hands_finger_manners_ever_code'] != $score_record3['q_77_hands_finger_manners_ever_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_78_oth_complex_manners_current_code'] =='8' AND $score_record3['q_78_oth_complex_manners_current_code']=='8'){}
            elseif($score_record['q_78_oth_complex_manners_current_code'] =='998' && $score_record3['q_78_oth_complex_manners_current_code']=='998'){}
            else {
                $denominator++;
                if (($score_record['q_78_oth_complex_manners_current_code'] =='2' AND $score_record3['q_78_oth_complex_manners_current_code']=='3') ||
                         ($score_record['q_78_oth_complex_manners_current_code'] =='3' AND $score_record3['q_78_oth_complex_manners_current_code']=='2'))
                        {
                           #Don't count this
                        }
                        else if ($score_record['q_78_oth_complex_manners_current_code'] != $score_record3['q_78_oth_complex_manners_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_78_oth_complex_manners_ever_code'] =='8' AND $score_record3['q_78_oth_complex_manners_ever_code']=='8'){}
            elseif($score_record['q_78_oth_complex_manners_ever_code'] =='998' && $score_record3['q_78_oth_complex_manners_ever_code']=='998'){}
            else {
                $denominator++;$denominator_scored++;
                if (($score_record['q_78_oth_complex_manners_ever_code'] =='2' AND $score_record3['q_78_oth_complex_manners_ever_code']=='3') ||
                          ($score_record['q_78_oth_complex_manners_ever_code'] =='3' AND $score_record3['q_78_oth_complex_manners_ever_code']=='2'))
                         {
                            #Don't count this
                         }
                         else if ($score_record['q_78_oth_complex_manners_ever_code'] != $score_record3['q_78_oth_complex_manners_ever_code']){ $reliability_count_raw++; $reliability_count_scored++;}}  
            if($score_record['q_79_midline_hand_moves_current_code'] =='8' AND $score_record3['q_79_midline_hand_moves_current_code']=='8'){}
            elseif($score_record['q_79_midline_hand_moves_current_code'] =='998' && $score_record3['q_79_midline_hand_moves_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_79_midline_hand_moves_current_code'] != $score_record3['q_79_midline_hand_moves_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_79_midline_hand_moves_ever_code'] =='8' AND $score_record3['q_79_midline_hand_moves_ever_code']=='8'){}
            elseif($score_record['q_79_midline_hand_moves_ever_code'] =='998' && $score_record3['q_79_midline_hand_moves_ever_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_79_midline_hand_moves_ever_code'] != $score_record3['q_79_midline_hand_moves_ever_code']){ $reliability_count_raw++;}} 
            if($score_record['q_80_gait_current_code'] =='8' AND $score_record3['q_80_gait_current_code']=='8'){}
            elseif($score_record['q_80_gait_current_code'] =='998' && $score_record3['q_80_gait_current_code']=='998'){}
            else {
                $denominator++;
                if (($score_record['q_80_gait_current_code'] =='2' AND $score_record3['q_80_gait_current_code']=='3') ||
                           ($score_record['q_80_gait_current_code'] =='3' AND $score_record3['q_80_gait_current_code']=='2'))
                          {
                             #Don't count this
                          }
                          else if ($score_record['q_80_gait_current_code'] != $score_record3['q_80_gait_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_80_gait_most_abnormal_code'] =='8' AND $score_record3['q_80_gait_most_abnormal_code']=='8'){}
            elseif($score_record['q_80_gait_most_abnormal_code'] =='998' && $score_record3['q_80_gait_most_abnormal_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_80_gait_most_abnormal_code'] != $score_record3['q_80_gait_most_abnormal_code']){ $reliability_count_raw++;}} 
            if($score_record['q_81_aggress_caregivers_current_code'] =='8' AND $score_record3['q_81_aggress_caregivers_current_code']=='8'){}
            elseif($score_record['q_81_aggress_caregivers_current_code'] =='998' && $score_record3['q_81_aggress_caregivers_current_code']=='998'){}
            else {
                $denominator++;
                if (($score_record['q_81_aggress_caregivers_current_code'] =='2' AND $score_record3['q_81_aggress_caregivers_current_code']=='3') ||
                 ($score_record['q_81_aggress_caregivers_current_code'] =='3' AND $score_record3['q_81_aggress_caregivers_current_code']=='2'))
                {
                   #Don't count this
                }
                else if ($score_record['q_81_aggress_caregivers_current_code'] != $score_record3['q_81_aggress_caregivers_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_81_aggress_caregivers_ever_code'] =='8' AND $score_record3['q_81_aggress_caregivers_ever_code']=='8'){}
            elseif($score_record['q_81_aggress_caregivers_ever_code'] =='998' && $score_record3['q_81_aggress_caregivers_ever_code']=='998'){}
            else {
                $denominator++;
                if (($score_record['q_81_aggress_caregivers_ever_code'] =='2' AND $score_record3['q_81_aggress_caregivers_ever_code']=='3') ||
                  ($score_record['q_81_aggress_caregivers_ever_code'] =='3' AND $score_record3['q_81_aggress_caregivers_ever_code']=='2'))
                 {
                    #Don't count this
                 }
                 else if ($score_record['q_81_aggress_caregivers_ever_code'] != $score_record3['q_81_aggress_caregivers_ever_code']){ $reliability_count_raw++;}} 
            if($score_record['q_82_aggress_noncaregivers_current_code'] =='8' AND $score_record3['q_82_aggress_noncaregivers_current_code']=='8'){}
            elseif($score_record['q_82_aggress_noncaregivers_current_code'] =='998' && $score_record3['q_82_aggress_noncaregivers_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_82_aggress_noncaregivers_current_code'] != $score_record3['q_82_aggress_noncaregivers_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_82_aggress_noncaregivers_ever_code'] =='8' AND $score_record3['q_82_aggress_noncaregivers_ever_code']=='8'){}
            elseif($score_record['q_82_aggress_noncaregivers_ever_code'] =='998' && $score_record3['q_82_aggress_noncaregivers_ever_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_82_aggress_noncaregivers_ever_code'] != $score_record3['q_82_aggress_noncaregivers_ever_code']){ $reliability_count_raw++;}} 
            if($score_record['q_83_self_injury_current_code'] =='8' AND $score_record3['q_83_self_injury_current_code']=='8'){}
            elseif($score_record['q_83_self_injury_current_code'] =='998' && $score_record3['q_83_self_injury_current_code']=='998'){}
            else {
                $denominator++;
                if (($score_record['q_83_self_injury_current_code'] =='2' AND $score_record3['q_83_self_injury_current_code']=='3') ||
                   ($score_record['q_83_self_injury_current_code'] =='3' AND $score_record3['q_83_self_injury_current_code']=='2'))
                  {
                     #Don't count this
                  }
                  else if ($score_record['q_83_self_injury_current_code'] != $score_record3['q_83_self_injury_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_83_self_injury_ever_code'] =='8' AND $score_record3['q_83_self_injury_ever_code']=='8'){}
            elseif($score_record['q_83_self_injury_ever_code'] =='998' && $score_record3['q_83_self_injury_ever_code']=='998'){}
            else {
                $denominator++;
                if (($score_record['q_83_self_injury_ever_code'] =='2' AND $score_record3['q_83_self_injury_ever_code']=='3') ||
                    ($score_record['q_83_self_injury_ever_code'] =='3' AND $score_record3['q_83_self_injury_ever_code']=='2'))
                   {
                      #Don't count this
                   }
                   else if ($score_record['q_83_self_injury_ever_code'] != $score_record3['q_83_self_injury_ever_code']){ $reliability_count_raw++;}} 
            if($score_record['q_84_hyperventilation_current_code'] =='8' AND $score_record3['q_84_hyperventilation_current_code']=='8'){}
            elseif($score_record['q_84_hyperventilation_current_code'] =='998' && $score_record3['q_84_hyperventilation_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_84_hyperventilation_current_code'] != $score_record3['q_84_hyperventilation_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_84_hyperventilation_ever_code'] =='8' AND $score_record3['q_84_hyperventilation_ever_code']=='8'){}
            elseif($score_record['q_84_hyperventilation_ever_code'] =='998' && $score_record3['q_84_hyperventilation_ever_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_84_hyperventilation_ever_code'] != $score_record3['q_84_hyperventilation_ever_code']){ $reliability_count_raw++;}} 
            if($score_record['q_85_faints_fits_blackouts_current_code'] =='8' AND $score_record3['q_85_faints_fits_blackouts_current_code']=='8'){}
            elseif($score_record['q_85_faints_fits_blackouts_current_code'] =='998' && $score_record3['q_85_faints_fits_blackouts_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_85_faints_fits_blackouts_current_code'] != $score_record3['q_85_faints_fits_blackouts_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_85_faints_fits_blackouts_ever_code'] =='8' AND $score_record3['q_85_faints_fits_blackouts_ever_code']=='8'){}
            elseif($score_record['q_85_faints_fits_blackouts_ever_code'] =='998' && $score_record3['q_85_faints_fits_blackouts_ever_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_85_faints_fits_blackouts_ever_code'] != $score_record3['q_85_faints_fits_blackouts_ever_code']){ $reliability_count_raw++;}} 
            if($score_record['q_86_age_when_abnormality_first_evident'] =='8' AND $score_record3['q_86_age_when_abnormality_first_evident']=='8'){}
            elseif($score_record['q_86_age_when_abnormality_first_evident'] =='998' && $score_record3['q_86_age_when_abnormality_first_evident']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_86_age_when_abnormality_first_evident'] != $score_record3['q_86_age_when_abnormality_first_evident']){ $reliability_count_raw++;}} 
            if($score_record['q_87_interviewers_judgment'] =='8' AND $score_record3['q_87_interviewers_judgment']=='8'){}
            elseif($score_record['q_87_interviewers_judgment'] =='998' && $score_record3['q_87_interviewers_judgment']=='998'){}
            else {
                $denominator++; $demoninator_scored++;
                if (abs($score_record['q_87_interviewers_judgment'] - $score_record3['q_87_interviewers_judgment']) >3){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_88_visuospatial_ability_current_code'] =='8' AND $score_record3['q_88_visuospatial_ability_current_code']=='8'){}
            elseif($score_record['q_88_visuospatial_ability_current_code'] =='998' && $score_record3['q_88_visuospatial_ability_current_code']=='998'){}
            else {
                $denominator++; $demoninator_scrored++;
                if ($score_record['q_88_visuospatial_ability_current_code'] != $score_record3['q_88_visuospatial_ability_current_code']){ $reliability_count_raw++; $reliability_count_scored++;}} 
            if($score_record['q_88_visuospatial_ability_ever_code'] =='8' AND $score_record3['q_88_visuospatial_ability_ever_code']=='8'){}
            elseif($score_record['q_88_visuospatial_ability_ever_code'] =='998' && $score_record3['q_88_visuospatial_ability_ever_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_88_visuospatial_ability_ever_code'] != $score_record3['q_88_visuospatial_ability_ever_code']){ $reliability_count_raw++;}} 
            if($score_record['q_89_memory_still_current_code'] =='8' AND $score_record3['q_89_memory_still_current_code']=='8'){}
            elseif($score_record['q_89_memory_still_current_code'] =='998' && $score_record3['q_89_memory_still_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_89_memory_still_current_code'] != $score_record3['q_89_memory_still_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_89_memory_still_ever_code'] =='8' AND $score_record3['q_89_memory_still_ever_code']=='8'){}
            elseif($score_record['q_89_memory_still_ever_code'] =='998' && $score_record3['q_89_memory_still_ever_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_89_memory_still_ever_code'] != $score_record3['q_89_memory_still_ever_code']){ $reliability_count_raw++;}} 
            if($score_record['q_90_musical_ability_current_code'] =='8' AND $score_record3['q_90_musical_ability_current_code']=='8'){}
            elseif($score_record['q_90_musical_ability_current_code'] =='998' && $score_record3['q_90_musical_ability_current_code']=='998'){}
            else {
                $denominator++;
                if (($score_record['q_90_musical_ability_current_code'] =='2' AND $score_record3['q_90_musical_ability_current_code']=='3') ||
                     ($score_record['q_90_musical_ability_current_code'] =='3' AND $score_record3['q_90_musical_ability_current_code']=='2'))
                    {
                       #Don't count this
                    }
                    else if ($score_record['q_90_musical_ability_current_code'] != $score_record3['q_90_musical_ability_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_90_musical_ability_ever_code'] =='8' AND $score_record3['q_90_musical_ability_ever_code']=='8'){}
            elseif($score_record['q_90_musical_ability_ever_code'] =='998' && $score_record3['q_90_musical_ability_ever_code']=='998'){}
            else {
                $denominator++;
                if (($score_record['q_90_musical_ability_ever_code'] =='2' AND $score_record3['q_90_musical_ability_ever_code']=='3') ||
                      ($score_record['q_90_musical_ability_ever_code'] =='3' AND $score_record3['q_90_musical_ability_ever_code']=='2'))
                     {
                        #Don't count this
                     }
                     else if ($score_record['q_90_musical_ability_ever_code'] != $score_record3['q_90_musical_ability_ever_code']){ $reliability_count_raw++;}} 
            if($score_record['q_91_drawings_skill_current_code'] =='8' AND $score_record3['q_91_drawings_skill_current_code']=='8'){}
            elseif($score_record['q_91_drawings_skill_current_code'] =='998' && $score_record3['q_91_drawings_skill_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_91_drawings_skill_current_code'] != $score_record3['q_91_drawings_skill_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_91_drawings_skill_ever_code'] =='8' AND $score_record3['q_91_drawings_skill_ever_code']=='8'){}
            elseif($score_record['q_91_drawings_skill_ever_code'] =='998' && $score_record3['q_91_drawings_skill_ever_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_91_drawings_skill_ever_code'] != $score_record3['q_91_drawings_skill_ever_code']){ $reliability_count_raw++;}} 
            if($score_record['q_92_reading_ability_current_code'] =='8' AND $score_record3['q_92_reading_ability_current_code']=='8'){}
            elseif($score_record['q_92_reading_ability_current_code'] =='998' && $score_record3['q_92_reading_ability_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_92_reading_ability_current_code'] != $score_record3['q_92_reading_ability_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_92_reading_ability_ever_code'] =='8' AND $score_record3['q_92_reading_ability_ever_code']=='8'){}
            elseif($score_record['q_92_reading_ability_ever_code'] =='998' && $score_record3['q_92_reading_ability_ever_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_92_reading_ability_ever_code'] != $score_record3['q_92_reading_ability_ever_code']){ $reliability_count_raw++;}} 
            if($score_record['q_93_computational_ability_current_code'] =='8' AND $score_record3['q_93_computational_ability_current_code']=='8'){}
            elseif($score_record['q_93_computational_ability_current_code'] =='998' && $score_record3['q_93_computational_ability_current_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_93_computational_ability_current_code'] != $score_record3['q_93_computational_ability_current_code']){ $reliability_count_raw++;}} 
            if($score_record['q_93_computational_ability_ever_code'] =='8' AND $score_record3['q_93_computational_ability_ever_code']=='8'){}
            elseif($score_record['q_93_computational_ability_ever_code'] =='998' && $score_record3['q_93_computational_ability_ever_code']=='998'){}
            else {
                $denominator++;
                if ($score_record['q_93_computational_ability_ever_code'] != $score_record3['q_93_computational_ability_ever_code']){ $reliability_count_raw++;}} 
            
            // Score the reliability
            $reliability['Reliability_score_all_items']= (($denominator-$reliability_count_raw)/$denominator*100);
            $reliability['Reliability_score_scored_items']= (($denominator_scored-$reliability_count_scored)/$denominator_scored*100);
//print_r($reliability['Reliability_score_all_items']);
           
         }
         // If the reliability is to be compared to the initial data entry
         elseif ($score_record['Gold_standard']=='Initial_entry') {
             echo("This is the initial check.");
             
             $reliability_count=0;            
             
             // Checking the relevant fields
             //             if ($score_record1['q_1_gaze_shifts_raw_score']!=$reliability['q_1_gaze_shifts_raw_score']) { echo("Score q_1_gaze_shifts_raw_score does not match. <br>"); $reliability['q_1_gaze_shifts_raw_score_match']='N'; $reliability_count++;}
            
            // Score the reliability
            $reliability['reliability_score']= ((22-$reliability_count)/22*100);
        
        }
              
        // end elseif
        else {
            echo("what the heck is going on?<br>");
            $reliability['reliability_score_all_items']= 0;
        } // end else
        
         // print_r($this->identifier);
      
        // Do the update here for the relibaility scores - saving the scores
		$result = $db->update("adi_r_reliability", $reliability, array("CommentID"=>$this->identifier));
    
/*	 // Update the main relibaility table with the overall reliability score 
                $result1 = $db->update("reliability", $reliability['reliability_score'], array("CommentID"=>$this->identifier));
*/

    } // end function score
           
    function _nullScores()
    {
        $db=& Database::singleton();
        
        // set the scores to NULL
        foreach ($this->scores as $val) {
            $scores[$val]=null;
        }

        // update the scores
        $success = $db->update("adi_r_reliability",$scores,array("CommentID"=>$this->identifier));
        return;
    }    


    function adi_r_reliability()
    {
       $this->_addMetadataFields();
        //Scoring header
        $this->form->addElement('header', 'instrument_title', "Scoring:");
        $this->form->addElement("static", "Reliability_score_all_items", "Reliability Score - all items (%):");
        $this->form->addElement("static", "Reliability_score_scored_items", "Reliability Score - scored items (%):");

        $GoldStandardArray = array(""=>NULL, "Gold_standard_SEA0012"=>"Gold standard SEA0012","Gold_standard_SEA0070"=>"Gold standard SEA0070", "Initial_entry"=>"Initial Entry");
        $this->form->addElement("select", "Gold_standard", "Compare against:", $GoldStandardArray);
        $this->form->addRule('Gold_standard', 'Gold standard is required', 'required');
        
        $this->form->addElement("static", "CommentID", "CommentID:");

        // Form stuff (page 2)
        $config =& NDB_Config::singleton();
        $dateOptions = array(
        'language' => 'en',
        'format'   => 'YMd',
        'minYear'  => $config->getSetting('startYear') - 20, //allows for proband siblings up to 20 years older than candidate
        'maxYear'  => $config->getSetting('endYear'),
        'addEmptyOption' => true,
        'emptyOptionValue' => null
        );

        $this->form->addElement('date', 'Age_proband', 'DoB Proband', $dateOptions);
       
        // Form stuff (page 2)
        $this->form->addElement("header", null, "EARLY DEVELOPMENT");
    	$this->addTextElement("q_2_age_first_noticed_code", "2. Age (in months) when parents first noticed that something was not quite right...");
    	//$this->addLargeTextAreaElement("q_2_age_first_noticed_text");
        //$this->addLargeTextAreaElement("q_3_first_symptoms_text", "3. First symptoms to arouse parental concern");
        $this->addTextElement("q_4_onset_as_perceived_code", "4. Onset as perceived with hindsight");
    	//$this->addLargeTextAreaElement("q_4_onset_as_perceived_text");
        $this->addTextElement("q_5_first_walked_code", "5. First walked unaided");
		//$this->addLargeTextAreaElement("q_5_first_walked_text");
        $this->addTextElement("q_6_bladder_daytime_code", "6. Acquisition of bladder control: daytime");
		//$this->addLargeTextAreaElement("q_6_bladder_daytime_text");
        $this->addTextElement("q_7_bladder_nighttime_code", "7. Acquisition of bladder control: nighttime");
		//$this->addLargeTextAreaElement("q_7_bladder_nighttime_text");
		$this->addTextElement("q_8_bowel_control_code", "8. Acquisition of bowel control");
		//$this->addLargeTextAreaElement("q_8_bowel_control_text");

        //line break
        $this->form->addElement("static", null, $this->indent);

        // Form stuff (Page 3)
        $yesNoNA = array(''=>NULL, '0_no'=>"0. No", '1_yes'=>"1. Yes", 'not_answered'=>"Not answered");
        $this->form->addElement("header", null, "ACQUISITION AND LOSS OF LANGUAGE/OTHER SKILLS");
        $this->addTextElement("q_9_first_single_words_code", "9. Age of first single words");
		//$this->addLargeTextAreaElement("q_9_first_single_words_text");
        $this->addTextElement("q_10_first_phrases_code", "10. Age of first phrases (if ever used)");
		//$this->addLargeTextAreaElement("q_10_first_phrases_text");
        $this->form->addElement("select", "q_11_loss_of_language", "11. Loss of language skills after acquisition", $yesNoNA);
        $answerArray = array(""=>NULL, "0_daily"=>"0. Daily", "1_occasional"=>"1. Occasional", "2_upon_request"=>"2. Produced upon request", "3_spontaneous_imitations"=>"3. Spontaneous imitations", "8_no_change"=>"8. No change", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("select", "q_12_level_before_loss_code", "12. Level of communicative language before loss", $answerArray);
		$this->XINRegisterRule("q_12_level_before_loss_code", array("q_11_loss_of_language{@}=={@}1_yes"), "This is required if language was lost (answered 'yes' to question 11)");
		//$this->addLargeTextAreaElement("q_12_level_before_loss_text", $this->indent . "Describe:", array("q_11_loss_of_language{@}=={@}1_yes"), "This is required if language was lost (answered 'yes' to question 11)");
        $answerArray = array(""=>NULL, "0_no_loss"=>"0. No definite loss", "1_probable_loss"=>"1. Probable loss", "2_definite_loss"=>"2. Definite Loss", "8_insufficient"=>"8. Insufficient", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$questionArray = array("13_loss_of_spontaneous_use"=>"13. Loss of spontaneous use",
								"14_loss_of_intent"=>"14. Loss of communicative intent",
								"15_loss_of_syntactical"=>"15. Loss of syntactical skills",
								"16_loss_of_articulation"=>"16. Loss of articulation");
		foreach($questionArray as $field=>$label) {
			$this->form->addElement("select", $field . "_code", $label, $answerArray);
			$this->XINRegisterRule($field . "_code", array("q_11_loss_of_language{@}=={@}1_yes"), "This is required if language was lost (answered 'yes' to question 11)");
//			$this->addTextAreaElement($field . "_text", $this->indent . "Describe:");
			$this->XINRegisterRule($field . "_text", array("q_11_loss_of_language{@}=={@}1_yes"), "This is required if language was lost (answered 'yes' to question 11)");
		}
		
		$this->addTextElement("q_17_main_loss_apparent_code", "17. Age when main loss of language skills first apparent", array("q_11_loss_of_language{@}=={@}1_yes"), "This is required if language was lost (answered 'yes' to question 11)");
		//$this->addLargeTextAreaElement("q_17_main_loss_apparent_text", $this->indent . "Describe:", array("q_11_loss_of_language{@}=={@}1_yes"), "This is required if language was lost (answered 'yes' to question 11)");
	
		$answerArray = array(""=>NULL, "0_loss_no_relevance"=>"0. Loss no possible relevance", "1_loss_illness"=>"1. Loss from illness", "2_loss_impaired"=>"2. Loss from impaired consciousness", "8_no_loss"=>"8. No loss", "9_not_asked"=>"9. Not asked", "not_anwered"=>"Not Answered");
		$this->form->addElement("select", "q_18_loss_due_to_illness", "18. Association of loss of language with physical illness", $answerArray);
		$this->XINRegisterRule("q_18_loss_due_to_illness_code", array("q_11_loss_of_language{@}=={@}1_yes"), "This is required if language was lost (answered 'yes' to question 11)");
		//$this->addLargeTextAreaElement("q_18_loss_due_to_illness_text", $this->indent . "Describe:", array("q_11_loss_of_language{@}=={@}1_yes"), "This is required if language was lost (answered 'yes' to question 11)");
	
		$this->addTextElement("q_19_duration_of_loss_code", "19. Duration of loss of language skills", array("q_11_loss_of_language{@}=={@}1_yes"), "This is required if language was lost (answered 'yes' to question 11)");
		//$this->addLargeTextAreaElement("q_19_duration_of_loss_text", $this->indent . "Describe:", array("q_11_loss_of_language{@}=={@}1_yes"), "This is required if language was lost (answered 'yes' to question 11)");
		
      
        // Form stuff (Page 4)
        $this->form->addElement("header", null, "GENERAL LOSS OF SKILLS");
		$answerArray = array(""=>NULL, "0_no_consistent_loss"=>"0. No consistent loss", "1_probable_loss"=>"1. Probable loss", "2_account_definite_loss"=>"2. Account of definite loss", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("select", "q_20_loss_of_skills_code", "20. Loss of skills (for at least 3 months)", $answerArray);
		//$this->addLargeTextAreaElement("q_20_loss_of_skills_text");
		
		$questionArray = array("q_21_puposive_hand_movements"=>"21. Purposive hand movements",
		"q_22_motor_skills"=>"22. Motor skills",
		"q_23_self_help_skills"=>"23. Self-help skills",
		"q_24_constructive_play"=>"24. Constructive or imaginative play",
		"q_25_social_engagement"=>"25. Social engagement and responsiveness");
		$answerArray = array(""=>NULL, "0_none"=>"0. None", "1_possible"=>"1. Possible", "2_definite"=>"2. Definite", "not_answered"=>"Not Answered");
		foreach ($questionArray as $field=>$label) {
			$this->form->addElement("select", $field . "_code", $label, $answerArray);
//			$this->addTextAreaElement($field . "_text", $this->indent . "Describe:");
		}		
		
		$this->addTextElement("q_26_loss_first_apparent_code", "26. Age when main loss of skill first apparent");
//		$this->addTextAreaElement("q_26_loss_first_apparent_text", $this->indent . "Describe:");
		
		$answerArray = array(""=>NULL, "0_no_relevance"=>"0. No possibly relevance", "1_definite_illness"=>"1. Definite illness", "2_impaired_consciousness"=>"2. Impaired consciousness", "8_no_loss"=>"8. No loss", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("select", "q_27_physical_illness_code", "27. Association of loss of skills with physical illness", $answerArray);
		//$this->addLargeTextAreaElement("q_27_physical_illness_text");
		
		$this->addTextElement("q_28_duration_of_loss_code", "28. Duration of loss of skills");
		//$this->addLargeTextAreaElement("q_28_duration_of_loss_text", $this->indent . "Describe:");

        // Form stuff (Page 5)
        $this->form->addElement("header", null, "LANGUAGE AND COMMUNICATION FUNCTIONING");
		
		$answerArray = array(""=>NULL, "0_perform_unexpected"=>"0. Perform an unexpected", "1_get_an_object"=>"1. Get an object", "2_understand_many_words"=>"2. Understand many words", "3_understand_fewer_than_50"=>"3. Understand fewer than 50", "4_little_or_no"=>"4. Little or no comprehension of words", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("static", null, "29. Comprehension of simple language");
		$this->form->addElement("select", "q_29_compreh_simple_current",  $this->indent . "Current", $answerArray);
		$this->form->addElement("select", "q_29_compreh_simple_most_abnormal",  $this->indent . "Most Abnormal (4.0-5.0)", $answerArray);
		//$this->addLargeTextAreaElement("q_29_compreh_simple_text");
		
		$answerArray = array(""=>NULL, "0_fuctional"=>"0. Functional", "1_no_functional"=>"1. No functional use", "2_fewer_than_5"=>"2. Fewer than five", "not_answered"=>"Not Answered");
		$this->form->addElement("select", "q_30_overall_level_of_language", "30. Overall level of language", $answerArray);
		
		$answerArray = array(""=>NULL, "0_no_use"=>"0. No use", "1_occasional_point"=>"1. Occasional to point", "2_occasional_for"=>"2. Occasional 'for'", "3_regular"=>"3. Regular", "8_little"=>"8. Little", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("static", null, "31. Use of other's body to communicate");
		$this->form->addElement("select", "q_31_use_of_others_body_current_code", $this->indent . "Current:", $answerArray);
		$this->form->addElement("select", "q_31_use_of_others_body_ever_code", $this->indent . "Ever:", $answerArray);
		//$this->addLargeTextAreaElement("q_31_use_of_others_body_text");
		
		$answerArray = array(""=>NULL, "0_anybody"=>"0. Anybody", "1_family"=>"1. Family", "2_difficulties"=>"2. Difficulties", "3_strangers"=>"3. Strangers", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("static", null, "32. Articulation/pronunciation");
		$this->form->addElement("select", "q_32_artic_pronun_current_code", $this->indent . "Current:", $answerArray);
		$this->form->addElement("select", "q_32_artic_pronun_5years_code", $this->indent . "At 5.0 Years:", $answerArray);
		//$this->addLargeTextAreaElement("q_32_artic_pronun_text");
		
		$answerArray = array(""=>NULL, "0_rarely"=>"0. Rarely", "1_more_repetitive"=>"1. More repetitive", "2_often_stereotyped"=>"2. Often stereotyped utterances", "3_exclusively_stereotyped"=>"3. Exclusively stereotyped utterances", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("static", null, "33. Stereotyped utterances and delayed echolalia");
		$this->form->addElement("select", "q_33_stereotyped_utterances_current_code", $this->indent . "Current:", $answerArray);
		$this->form->addElement("select", "q_33_stereotyped_utterances_ever_code", $this->indent . "Ever:", $answerArray);
		//$this->addLargeTextAreaElement("q_33_stereotyped_utterances_text");
		
		$answerArray = array(""=>NULL, "0_verbalizes"=>"0. Verbalizes", "1_some_response"=>"1. Some response", "2_some_alert"=>"2. Some alert", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("static", null, "34. Social verbalization/chat");
		$this->form->addElement("select", "q_34_social_verb_chat_current_code", $this->indent . "Current:", $answerArray);
		$this->form->addElement("select", "q_34_social_verb_chat_ever_code", $this->indent . "Ever:", $answerArray);
		//$this->addLargeTextAreaElement("q_34_social_verb_chat_text");

		$answerArray = array(""=>NULL, "0_conversational"=>"0. Conversational flows", "1_occasional"=>"1. Occasional", "2_little_or_not"=>"2. Little of no", "3_very_little"=>"3. Very little", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("static", null, "35. Reciprocal conversation (within subject's level of language)");
		$this->form->addElement("select", "q_35_recipr_convers_current_code", $this->indent . "Current:", $answerArray);
		$this->form->addElement("select", "q_35_recipr_convers_ever_code", $this->indent . "Ever:", $answerArray);
		//$this->addLargeTextAreaElement("q_35_recipr_convers_text");
		
		$answerArray = array(""=>NULL, "0_none_or_rare"=>"0. No or very rare", "1_some_questions"=>"1. Use of some questions", "2_frequent"=>"2. Frequent", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("static", null, "36. Inappropriate questions or statements");
		$this->form->addElement("select", "q_36_inappropriate_qs_current_code", $this->indent . "Current:", $answerArray);
		$this->form->addElement("select", "q_36_inappropriate_qs_ever_code", $this->indent . "Ever:", $answerArray);
		//$this->addLargeTextAreaElement("q_36_inappropriate_qs_text");

		$answerArray = array(""=>NULL, "0_no_confusion"=>"0. No confusion", "1_refers"=>"1. Refers", "2_you_I_confusion"=>"2. You/I confusion", "3_pronominal"=>"3. Pronominal", "7_other_types"=>"7. Other types of pronominal", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("static", null, "37. Prenominal reversal");
		$this->form->addElement("select", "q_37_prenominal_reversal_current_code", $this->indent . "Current:", $answerArray);
		$this->form->addElement("select", "q_37_prenominal_reversal_ever_code", $this->indent . "Ever:", $answerArray);
		//$this->addLargeTextAreaElement("q_37_prenominal_reversal_text");

		$answerArray = array(""=>NULL, "0_no_use"=>"0. No use", "1_occasional"=>"1. Occasional", "2_regular"=>"2. Regular", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("static", null, "38. Neologisms/Idiosyncratic language");
		$this->form->addElement("select", "q_38_neologisms_current_code", $this->indent . "Current:", $answerArray);
		$this->form->addElement("select", "q_38_neologisms_ever_code", $this->indent . "Ever:", $answerArray);
		//$this->addLargeTextAreaElement("q_38_neologisms_text");

		$answerArray = array(""=>NULL, "0_no_rituals"=>"0. No rituals", "1_tendency"=>"1. Tendency", "2_special_way"=>"2. Special way", "3_as_for2_with_difficulty"=>"3. As for '2', with difficulty", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("static", null, "39. Verbal rituals");
		$this->form->addElement("select", "q_39_verbal_rituals_current_code", $this->indent . "Current:", $answerArray);
		$this->form->addElement("select", "q_39_verbal_rituals_ever_code", $this->indent . "Ever:", $answerArray);
		//$this->addLargeTextAreaElement("q_39_verbal_rituals_text");

		$answerArray = array(""=>NULL, "0_normal"=>"0. Normal", "1_shows_abnormalities"=>"1. Shows abnormalities", "2_clearly_abnormal"=>"2. Clearly abnormal", "3_frequetly_peculiar"=>"3. Frequently peculiar", "7_stutter"=>"7. Stutter", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("static", null, "40. Intonation/volume/rhythm/rate");
		$this->form->addElement("select", "q_40_inton_vol_rhythm_rate_current_code", $this->indent . "Current:", $answerArray);
		$this->form->addElement("select", "q_40_inton_vol_rhythm_rate_ever_code", $this->indent . "Ever:", $answerArray);
		//$this->addLargeTextAreaElement("q_40_inton_vol_rhythm_rate_text");

        // Form stuff (Page 6)
	$this->form->addElement("header", null, "LANGUAGE AND COMMUNICATION FUNCTIONING (Continued)");

		$answerArray = array(""=>NULL, "0_speech_used_frequently"=>"0. Speech used frequently", "1_some_communication"=>"1. Some communication", "2_some_spontaneous"=>"2. Some spontaneous", "3_lillte_or_no"=>"3. Little or no", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("static", null, "41. Current communicative speech");
		$this->form->addElement("select", "q_41_cur_comm_speech_current_code", $this->indent . "Current:", $answerArray);
		$this->form->addElement("select", "q_41_cur_comm_speech_at5_code", $this->indent . "At 5.0 years:", $answerArray);
		//$this->addLargeTextAreaElement("q_41_cur_comm_speech_text");
		
		$answerArray = array(""=>NULL, "0_spontaneously"=>"0. Spontaneously points", "1_limited_attempt"=>"1. Limited attempt", "2_little_or_no"=>"2. Little or no", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("static", null, "42. Pointing to express interest");
		$this->form->addElement("select", "q_42_point_express_interest_current_code", $this->indent . "Current:", $answerArray);
		$this->form->addElement("select", "q_42_point_express_inter_most_abnormal_code", $this->indent . "Most abnormal 4.0-5.0 years:", $answerArray);
		//$this->addLargeTextAreaElement("q_42_pointing_to_express_interest_text");
		
		$answerArray = array(""=>NULL, "0_consistently"=>"0. Consistently", "1_sometimes"=>"1. Sometimes", "2_never"=>"2. Never", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_43_nodding";
		$label = "43. Nodding";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);
		
		$answerArray = array(""=>NULL, "0_consistently"=>"0. Consistently", "1_sometimes"=>"1. Sometimes", "2_never"=>"2. Never", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_44_head_shaking";
		$label = "44. Head shaking";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);
		
		$answerArray = array(""=>NULL, "0_appripriate"=>"0. Appropriate", "1_spontaneous"=>"1. Spontaneous", "2_inconsistent"=>"2_inconsistent", "3_no_use"=>"3. No use", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_45_conventional_instr_gests";
		$label = "45. Conventional/instrumental gestures";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);
		
		$answerArray = array(""=>NULL, "0_usually"=>"0. Usually", "1_not_consistently"=>"1. Not consistently", "2_usually_does_not"=>"2. Usually does not", "3_rarely"=>"3. Rarely", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_46_attent_voice";
		$label = "46. Attention to voice";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);
		
		$answerArray = array(""=>NULL, "0_spontaneous"=>"0. Spontaneous", "1_some"=>"1. Some", "2_limited"=>"2. Limited", "3_very_rare"=>"3. Very rare", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_47_spont_imit";
		$label = "47. Spontaneous imitation of actions";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);
		
		$answerArray = array(""=>NULL, "0_variety"=>"0. Variety", "1_some"=>"1. Some", "2_occasional"=>"2. Occasional", "3_no_pretend"=>"3. No pretend", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_48_imag_play";
		$label = "48. Imaginative play";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);
		
		$answerArray = array(""=>NULL, "0_imaginative"=>"0. Imaginative",  "1_some_participation"=>"1. Some participation",  "2_some_play"=>"2. Some play",  "3_no_play"=>"3. No play", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_49_imag_play_peers";
		$label = "49. Imaginative play with peers";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);

        // Form stuff (Page 7)
	$this->form->addElement("header", null, "SOCIAL DEVELOPMENT AND PLAY");

		$answerArray = array(""=>NULL, "0_normal"=>"0. Normal", "1_definite"=>"1. Definite", "2_uncertain"=>"2. Uncertain", "3_unusual"=>"3. Unusual", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_50_direct_gaze";
		$label = "50. Direct gaze";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_regularly"=>"0. Regularly", "1_some_reciprocal"=>"1. Some reciprocal", "2_some_smiling"=>"2. Some smiling", "3_little_or_no"=>"3. Little or no", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_51_social_smiling";
		$label = "51. Social smiling";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_regular"=>"0. Regular", "1_possible"=>"1. Possible", "2_some"=>"2. Some", "3_rare"=>"3. Rare", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_52_show_direct_atten";
		$label = "52. Showing and directing attention";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);
		
		$answerArray = array(""=>NULL, "0_frequent"=>"0. Frequent", "1_some"=>"1. Some", "2_sometimes"=>"2. Sometimes", "3_no_sharing"=>"3. No sharing", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_53_offer_share";
		$label = "53. Offering to share";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_frequent"=>"0. Frequent", "1_some"=>"1. Some", "2_few"=>"2. Few", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_54_seek_share_enjoy";
		$label = "54. Seeking to share her/his enjoyment with others";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_frequently"=>"0. Frequently", "1_partial"=>"1. Partial", "2_rarely"=>"2. Rarely", "3_never"=>"3. Never", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_55_offer_comf";
		$label = "55. Offerings comfort";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_consistently"=>"0. Consistently", "1_may"=>"1. May", "2_rarely"=>"2. Rarely", "3_shows_no"=>"3. Shows no", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_56_qual_social_overts";
		$label = "56. Quality of social overtures";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_full"=>"0. Full", "1_somewhat"=>"1. Somewhat", "2_markedly"=>"2. Markedly", "3_little_or_no"=>"3. Little or no", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_57_range_facial_expr";
		$label = "57. Range of facial expressions used to communicate";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_almost_always"=>"0. Almost always", "1_slightly"=>"1. Slightly", "2_obviously"=>"2. Obviously", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("static", null, "58. Inappropriate facial expressions");
		$this->form->addElement("select", "q_58_inappropriate_facial_current_code", $this->indent . "Current:", $answerArray);
		$this->form->addElement("select", "q_58_inappropriate_facial_ever_code", $this->indent . "Ever:", $answerArray);
		//$this->addLargeTextAreaElement("q_58_inappropriate_facial_text");
		
		$answerArray = array(""=>NULL, "0_appropriate"=>"0. Appropriate", "1_some"=>"1. Some", "2_responds"=>"2. Responds", "3_little_or_no"=>"3. Little or no", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_59_appropriat_resp";
		$label = "59. Appropriateness of social responses";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);
		
		//$this->addLargeTextAreaElement("q_60_favourite_activities", "Favourite Activities");
		//$this->addLargeTextAreaElement("q_60_favourite_toys_objects", "Favourite Toys / Objects");

        // Form stuff (Page 8)
	$answerArray = array(""=>NULL, "0_range"=>"0. Range", "1_initiates"=>"1. Initiates", "2_passive"=>"2. Passive", "3_no_active"=>"3. No active", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_60_init_activities";
		$label = "60. Initiation of appropriate activities";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_normal"=>"0. Normal", "1_some"=>"1. Some", "2_little"=>"2. Little", "3_no_evidence"=>"3. No evidence", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_61_imit_soc_play";
		$label = "61. Imitative social play";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_often"=>"0. Often", "1_usually"=>"1. Usually", "2_occasionaly"=>"2. Occasionaly", "3_shows_no"=>"3. Shows no", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_62_inter_children";
		$label = "62. Interest in children";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_generally"=>"0. Generally", "1_sometimes"=>"1. Sometimes", "2_rarely"=>"2. Rarely", "3_consistently"=>"3. Consistently", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_63_resp_approaches";
		$label = "63. Response to approaches of other children";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_actively"=>"0. Actively", "1_some"=>"1. Some", "2_enjoys"=>"2. Enjoys", "3_seeks_no"=>"3. Seeks no", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_64_group_play_peers";
		$label = "64. Group play peers";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0"=>"0", "1"=>"1", "2"=>"2", "3_no_peer"=>"3. No peer", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_65_friendships";
		$label = "65. Friendships";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_normal"=>"0. Normal", "1_occasional"=>"1. Occasional", "2_lack"=>"2. Lack", "3_marked"=>"3. Marked", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_66_soc_disinhibit";
		$label = "66. Social disinhibition";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);

        // Form stuff (Page 9)
	$this->form->addElement("header", null, "INTERESTS AND BEHAVIOURS");

		$answerArray = array(""=>NULL, "0_no_unusual"=>"0. No unusual", "1_unusual"=>"1. Unusual", "2_definite_intrudes"=>"2. Definite intrudes", "3_definite_interferes"=>"3. Definite Interferes", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_67_unusual_preoccupations";
		$label = "67. Unusual preoccupations";
		$this->_addCurrentEver($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_no"=>"0. No", "1_special"=>"1. Special", "2_definite_no_interfere"=>"2. Definite no interfere", "3_definite_impairment"=>"3. Definite impairment", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_68_circumscr_ints";
		$label = "68. Circumscribed interests";
		$this->_addCurrentEver($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_little_or_no"=>"0. Little or no", "1_some"=>"1. Some", "2_does_not_constrain"=>"2. Does not constrain", "3_prevents"=>"3. Prevents", "7_infant_toys"=>"7. Infant toys", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_69_repet_use_objects";
		$label = "69. Repetitive use of objects or interest in parts of objects";
		$this->_addCurrentEver($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_no"=>"0. No", "1_some"=>"1. Some", "2_one_or_more"=>"2. One or more", "3_marked"=>"3. Marked", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_70_compulsions_rituals";
		$label = "70. Compulsions/rituals";
		$this->_addCurrentEver($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_no_unusual"=>"0. No unusual", "1_one_or_two"=>"1. One or two", "2_has"=>"2. Has", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_71_unusual_sens_ints";
		$label = "71. Unusual sensory interests";
		$this->_addCurrentEver($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_no_general"=>"0. No general", "1_slight"=>"1. Slight", "2_definite_not_distressing"=>"2. Definite not distressing", "3_definite_interferes"=>"3. Definite interferes", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_72_undo_gen_sens_noise";
		$label = "72. Undo general sensitivity to noise";
		$this->_addCurrentEver($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_no"=>"0. No", "1_mild"=>"1. Mild", "2_occasional"=>"2. Occasional", "3_substantial"=>"3. Substantial", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_73_idiosyncratic";
		$label = "73. Abnormal, idiosyncratic, negative response to specific sensory stimuli";
		$this->_addCurrentEver($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_no"=>"0. No", "1_unusually"=>"1. Unusually", "2_resistance"=>"2. Resistance", "3_substantial"=>"3. Substantial", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_74_diff_minor_changes";
		$label = "74. Difficulties with minor changes in subjects own routines or personal environment";
		$this->_addCurrentEver($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_none"=>"0. None", "1_unusually"=>"1. Unusually", "2_avoid"=>"2. Avoid", "3_substantial"=>"3. Substantial", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_75_resist_trivial_chng";
		$label = "75. Resistance to trivial changes in the environment";
		$this->_addCurrentEver($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_no"=>"0. No", "1_some"=>"1. Some", "2_significant"=>"2. Significant", "3_intrusive"=>"3. Intrusive", "6_beyond_5"=>"6. Beyond age 5", "7_series"=>"7. Series", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_76_unus_attach_objects";
		$label = "76. Unusual attachments to objects";
		$this->_addCurrentEver($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_no"=>"0. No", "1_occasional"=>"1. Occasional", "2_definite"=>"2. Definite", "3_marked"=>"3. Marked", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_77_hands_finger_manners";
		$label = "77. Hands and finger mannerisms";
		$this->_addCurrentEver($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_no"=>"0. No", "1_only"=>"1. Only", "2_definite"=>"2. Definite", "3_marked"=>"3. Marked", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_78_oth_complex_manners";
		$label = "78. Other complex mannerisms or stereotyped body movements";
		$this->_addCurrentEver($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_no"=>"0. No", "1_occasional"=>"1. Occasional", "2_definite"=>"2. Definite", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_79_midline_hand_moves";
		$label = "79. Midline hand movements";
		$this->_addCurrentEver($field, $label, $answerArray);

        // Form stuff (Page 10)
	$this->form->addElement("header", null, "GENERAL BEHAVIOURS");
	
		$answerArray = array(""=>NULL, "0_normal"=>"0. Normal", "1_somewhat"=>"1. Somewhat", "2_defnitely"=>"2. Definitely", "3_gait_odd"=>"3. Gait odd", "7_gait_neurological"=>"7. Gait neurological", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_80_gait";
		$label = "80. Gait";
		$this->_addCurrentMostAbnormal($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_no"=>"0. No", "1_mild"=>"1. Mild", "2_definite"=>"2. Definite", "3_violence"=>"3. Violence", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_81_aggress_caregivers";
		$label = "81. Aggression towards caregivers or family members";
		$this->_addCurrentEver($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_rare"=>"0. Rare", "1_mild"=>"1. Mild", "2_definite"=>"2. Definite", "3_violence"=>"3. Violence", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_82_aggress_noncaregivers";
		$label = "82. Aggression toward noncaregivers or nonfamily members";
		$this->_addCurrentEver($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_no"=>"0. No", "1_slight"=>"1. Slight", "2_definitely"=>"2. Definitely", "3_serious"=>"3. Serious", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_83_self_injury";
		$label = "83. Self-injury";
		$this->_addCurrentEver($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_no"=>"0. No", "1_occasional"=>"1. Occasional", "2_frequent"=>"2. Frequent", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_84_hyperventilation";
		$label = "84. Hyperventilation";
		$this->_addCurrentEver($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0_no"=>"0. No", "1_history"=>"1. History", "2_definite"=>"2. Definite", "7_febrile"=>"7. Febrile", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$field = "q_85_faints_fits_blackouts";
		$label = "85. Faints/fits/blackouts";
		$this->_addCurrentEver($field, $label, $answerArray);

		$answerArray = array(""=>NULL, "0"=>"0", "1"=>"1", "2"=>"2", "3"=>"3", "4"=>"4", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$this->form->addElement("select", "q_86_age_when_abnormality_first_evident", "86. Age when abnormality first evident", $answerArray);
		//$this->addLargeTextAreaElement("q_86_age_when_abnormality_first_evident_text");

		$this->addTextElement("q_87_interviewers_judgment", "87. Interviewers judgment on age when developmental abnormalities probably first manifest");
        // Form stuff (Page 11)
        $this->form->addElement("header", null, "SPECIAL ISOLATED SKILLS");
		
		//$this->addLargeTextAreaElement("special_isolated_skills", "Special isolated skills");

		$answerArray = array(""=>NULL, "0_no"=>"0. No", "1_above_subject"=>"1. Above subject", "2_above_population"=>"2. Above population", "7_meaningful"=>"7. Meaningful", "8_NA"=>"8. N/A", "9_not_asked"=>"9. Not asked", "not_answered"=>"Not Answered");
		$questionArray = array("q_88_visuospatial_ability"=>"88. Visuospatial ability",
								"q_89_memory_still"=>"89. Memory still",
								"q_90_musical_ability"=>"90. Musical ability",
								"q_91_drawings_skill"=>"91. Drawings skill",
								"q_92_reading_ability"=>"92. Reading ability",
								"q_93_computational_ability"=>"93. Computational ability");
		foreach($questionArray as $field=>$label) {
			$this->form->addElement("static", null, $label);
			$this->form->addElement("select", $field . "_current_code", $this->indent . "Current:", $answerArray);
			$this->form->addElement("select", $field . "_ever_code", $this->indent . "Ever:", $answerArray);
		}


        $this->redirect = "test_name=$this->name"; // what does this do?
        
        //------------------------------------------------------------
       
       //  //Take this out
//         // put this into adi_r_reliability function
//         $renderer =& new HTML_QuickForm_Renderer_Default();
//         $renderer->setFormTemplate("<form{attributes}><table class=\"instrument\">{content}</table></form>");
//         $renderer->setElementTemplate("<tr><td class=\"lab\"><!-- BEGIN required --><span style=\"color: #ff0000\">*</span><!-- END required -->{label}</td><td class=\"ele\"><!-- BEGIN error --><span style=\"color: #ff0000\">{error}</span><br /><!-- END error -->{element}</td></tr>");
//         $renderer->setElementTemplate("<tr><td class=\"lab\"><i>{label}</i></td><td class=\"ele\">\t<i>{element}</i></td></tr>", "static");
//         $renderer->setHeaderTemplate("<tr><th colspan=\"2\"><br><b>{header}</b></th></tr>");
//         $this->form->accept($renderer);
//         $this->tpl_data['tempFormHTML'] = $renderer->toHtml();

//         // My get defaults function sets $defaults array
//         $localDefaults = $this->_getDefaults();
//         if(!is_array($localDefaults)) { $localDefaults = array(); }


//         $this->form->setDefaults($this->defaults);
//     	$this->form->applyFilter('__ALL__', 'trim');


    } // End function 

    function addDateElement($name, $label){
        $group [] = $this->form->createElement("date", $name . "_date", null, $this->dateOptions);
        $this->dateTimeFields[] = $name . "_date"; //add to array of dates and times.
        $group [] = $this->form->createElement("select", $name . "_date_status", null, array(NULL=>"", 'not_answered'=>"Not Answered"));
        $this->form->addGroup($group, $name . "_date_group", $label, $this->_GUIDelimiter, FALSE);
        unset($group);
        $this->XINRegisterRule($name . "_date", array($name . "_date_status{@}=={@}"), "A Date, or Not Answered is required.", $name . "_date_group");
        
    }
    function XINRegisterRule($elname, $rules, $message="", $group=""){
        if(!is_array($rules)){
            $rules_array[]=$rules;
        } else {
            $rules_array=$rules;
        }
        $this->XINRules[$elname]['message']=$message;
        $this->XINRules[$elname]['group']=$group;

        foreach($rules_array AS $rule){
            $this->XINRules[$elname]['rules'][]=$rule;
        }
        return true;
    }
    function addTextElement($field, $label, $rules=array(), $rule_message='This field is required.', $refusals=array(''=>'', 'not_answered'=>'Not Answered')){
        $group[]=&$this->form->createElement("text", $field);
        $group[]=&$this->form->createElement("select", $field."_status", "", $refusals);
        $this->form->addGroup($group, $field.'_group', $label, null, false);
        unset($group);
        $rules_array=array_merge(array($field.'_status{@}=={@}'), $rules);
        $this->XINRegisterRule($field, $rules_array, $rule_message, $field.'_group');
    }

          function addLargeTextAreaElement($field, $label = "&nbsp;&nbsp;&nbsp;&nbsp;Describe:", $rules=array(), $rule_message='This field must be completed or marked as not answered.') {
        return;  //removed all free form comment text boxes.
        $group[]=&$this->form->createElement("textarea", $field, null, array('cols'=>60, 'rows'=>6));
        $group[]=&$this->form->createElement("select", $field."_status", "", array(NULL=>'', 'not_answered'=>'Not Answered'));
        $this->form->addGroup($group, $field.'_group', $label, null, false);
        unset($group);
        $rules_array=array_merge(array($field.'_status{@}=={@}'),$rules);
        $this->XINRegisterRule($field, $rules_array, $rule_message, $field.'_group');
    }
    
	function _addCurrentMostAbnormal($field, $label, $answerArray) { 
		$this->form->addElement("static", null, $label);
		$this->form->addElement("select", $field . "_current_code", $this->indent . "Current:", $answerArray);
		$this->form->addElement("select", $field . "_most_abnormal_code", $this->indent . "Most abnormal 4.0-5.0 years:", $answerArray);
		//$this->addLargeTextAreaElement($field . "_text");
	}

	function _addCurrentEver($field, $label, $answerArray) { 
		$this->form->addElement("static", null, $label);
		$this->form->addElement("select", $field . "_current_code", $this->indent . "Current:", $answerArray);
		$this->form->addElement("select", $field . "_ever_code", $this->indent . "Ever:", $answerArray);
		//$this->addLargeTextAreaElement($field . "_text");
	}
	
	function _cleanTo3Digits($string) {
	   return ereg_replace("[^0-9]", "", substr($string, 0, 3));
	}

 function _process($values)
    {
        $DB =& Database::singleton();
       
        $scoreResult = $this->score();
        

        $user =& User::singleton();
        // if(!$user->hasPermission('tracking_logs_edit_all')) {
        //    $values['Lock_record'] = 'Locked';
        // }
           
        if (empty($this->identifier)) { 
            
            // insert the event
            $success = $DB->insert('adi_r_reliability', array(
                                                             'Examiner' => $values['Examiner'],
                                                             'Date_taken' => $this->_getDatabaseDate($values['Date_taken']),
                                                             'CommentID' => $this->identifier,
                                                             'DoB_proband' => $values['DoB_proband'],
                                                             'Gold_standard' => $values['Gold_standard'],
                                                             'q_2_age_first_noticed_code' => $values['q_2_age_first_noticed_code'],
                                                             'q_2_age_first_noticed_code_status' => $values['q_2_age_first_noticed_code_status'],
                                                             'q_4_onset_as_perceived_code' => $values['q_4_onset_as_perceived_code'],
                                                             'q_4_onset_as_perceived_code_status' => $values['q_4_onset_as_perceived_code_status'],
                                                             'q_5_first_walked_code' => $values['q_5_first_walked_code'],
                                                             'q_5_first_walked_code_status' => $values['q_5_first_walked_code_status'],
                                                             'q_6_bladder_daytime_code' => $values['q_6_bladder_daytime_code'],
                                                             'q_6_bladder_daytime_code_status' => $values['q_6_bladder_daytime_code_status'],
                                                             'q_7_bladder_nighttime_code' => $values['q_7_bladder_nighttime_code'],
                                                             'q_7_bladder_nighttime_code_status' => $values['q_7_bladder_nighttime_code_status'],
                                                             'q_8_bowel_control_code' => $values['q_8_bowel_control_code'],
                                                             'q_8_bowel_control_code_status' => $values['q_8_bowel_control_code_status'],
                                                             'q_9_first_single_words_code' => $values['q_9_first_single_words_code'],
                                                             'q_9_first_single_words_code_status' => $values['q_9_first_single_words_code_status'],
                                                             'q_10_first_phrases_code' => $values['q_10_first_phrases_code'],
                                                             'q_10_first_phrases_code_status' => $values['q_10_first_phrases_code_status'],
                                                             'q_11_loss_of_language' => $values['q_11_loss_of_language'],
                                                             'q_12_level_before_loss_code' => $values['q_12_level_before_loss_code'],
                                                             '13_loss_of_spontaneous_use_code' => $values['13_loss_of_spontaneous_use_code'],
                                                             '14_loss_of_intent_code' => $values['14_loss_of_intent_code'],
                                                             '15_loss_of_syntactical_code' => $values['15_loss_of_syntactical_code'],
                                                             '16_loss_of_articulation_code' => $values['16_loss_of_articulation_code'],
                                                             'q_17_main_loss_apparent_code' => $values['q_17_main_loss_apparent_code'],
                                                             'q_17_main_loss_apparent_code_status' => $values['q_17_main_loss_apparent_code_status'],
                                                             'q_18_loss_due_to_illness' => $values['q_18_loss_due_to_illness'],
                                                             'q_19_duration_of_loss_code' => $values['q_19_duration_of_loss_code'],
                                                             'q_19_duration_of_loss_code_status' => $values['q_19_duration_of_loss_code_status'],
                                                             'q_20_loss_of_skills_code' => $values['q_20_loss_of_skills_code'],
                                                             'q_21_puposive_hand_movements_code' => $values['q_21_puposive_hand_movements_code'],
                                                             'q_22_motor_skills_code' => $values['q_22_motor_skills_code'],
                                                             'q_23_self_help_skills_code' => $values['q_23_self_help_skills_code'],
                                                             'q_24_constructive_play_code' => $values['q_24_constructive_play_code'],
                                                             'q_25_social_engagement_code' => $values['q_25_social_engagement_code'],
                                                             'q_26_loss_first_apparent_code' => $values['q_26_loss_first_apparent_code'],
                                                             'q_26_loss_first_apparent_code_status' => $values['q_26_loss_first_apparent_code_status'],
                                                             'q_27_physical_illness_code' => $values['q_27_physical_illness_code'],
                                                             'q_28_duration_of_loss_code' => $values['q_28_duration_of_loss_code'],
                                                             'q_28_duration_of_loss_code_status' => $values['q_28_duration_of_loss_code_status'],
                                                             'q_29_compreh_simple_current' => $values['q_29_compreh_simple_current'],
                                                             'q_29_compreh_simple_most_abnormal' => $values['q_29_compreh_simple_most_abnormal'],
                                                             'q_30_overall_level_of_language' => $values['q_30_overall_level_of_language'],
                                                             'q_31_use_of_others_body_current_code' => $values['q_31_use_of_others_body_current_code'],
                                                             'q_31_use_of_others_body_ever_code' => $values['q_31_use_of_others_body_ever_code'],
                                                             'q_32_artic_pronun_current_code' => $values['q_32_artic_pronun_current_code'],
                                                             'q_32_artic_pronun_5years_code' => $values['q_32_artic_pronun_5years_code'],
                                                             'q_33_stereotyped_utterances_current_code' => $values['q_33_stereotyped_utterances_current_code'],
                                                             'q_33_stereotyped_utterances_ever_code' => $values['q_33_stereotyped_utterances_ever_code'],
                                                             'q_34_social_verb_chat_current_code' => $values['q_34_social_verb_chat_current_code'],
                                                             'q_34_social_verb_chat_ever_code' => $values['q_34_social_verb_chat_ever_code'],
                                                             'q_35_recipr_convers_current_code' => $values['q_35_recipr_convers_current_code'],
                                                             'q_35_recipr_convers_ever_code' => $values['q_35_recipr_convers_ever_code'],
                                                             'q_36_inappropriate_qs_current_code' => $values['q_36_inappropriate_qs_current_code'],
                                                             'q_36_inappropriate_qs_ever_code' => $values['q_36_inappropriate_qs_ever_code'],
                                                             'q_37_prenominal_reversal_current_code' => $values['q_37_prenominal_reversal_current_code'],
                                                             'q_37_prenominal_reversal_ever_code' => $values['q_37_prenominal_reversal_ever_code'],
                                                             'q_38_neologisms_current_code' => $values['q_38_neologisms_current_code'],
                                                             'q_38_neologisms_ever_code' => $values['q_38_neologisms_ever_code'],
                                                             'q_39_verbal_rituals_current_code' => $values['q_39_verbal_rituals_current_code'],
                                                             'q_39_verbal_rituals_ever_code' => $values['q_39_verbal_rituals_ever_code'],
                                                             'q_40_inton_vol_rhythm_rate_current_code' => $values['q_40_inton_vol_rhythm_rate_current_code'],
                                                             'q_40_inton_vol_rhythm_rate_ever_code' => $values['q_40_inton_vol_rhythm_rate_ever_code'],
                                                             'q_41_cur_comm_speech_current_code' => $values['q_41_cur_comm_speech_current_code'],
                                                             'q_41_cur_comm_speech_at5_code' => $values['q_41_cur_comm_speech_at5_code'],
                                                             'q_42_point_express_interest_current_code' => $values['q_42_point_express_interest_current_code'],
                                                             'q_42_point_express_inter_most_abnormal_code' => $values['q_42_point_express_inter_most_abnormal_code'],
                                                             'q_43_nodding_current_code' => $values['q_43_nodding_current_code'],
                                                             'q_43_nodding_most_abnormal_code' => $values['q_43_nodding_most_abnormal_code'],
                                                             'q_44_head_shaking_current_code' => $values['q_44_head_shaking_current_code'],
                                                             'q_44_head_shaking_most_abnormal_code' => $values['q_44_head_shaking_most_abnormal_code'],
                                                             'q_45_conventional_instr_gests_current_code' => $values['q_45_conventional_instr_gests_current_code'],
                                                             'q_45_conventional_instr_gests_most_abnormal_code' => $values['q_45_conventional_instr_gests_most_abnormal_code'],
                                                             'q_46_attent_voice_current_code' => $values['q_46_attent_voice_current_code'],
                                                             'q_46_attent_voice_most_abnormal_code' => $values['q_46_attent_voice_most_abnormal_code'],
                                                             'q_47_spont_imit_current_code' => $values['q_47_spont_imit_current_code'],
                                                             'q_47_spont_imit_most_abnormal_code' => $values['q_47_spont_imit_most_abnormal_code'],
                                                             'q_48_imag_play_current_code' => $values['q_48_imag_play_current_code'],
                                                             'q_48_imag_play_most_abnormal_code' => $values['q_48_imag_play_most_abnormal_code'],
                                                             'q_49_imag_play_peers_current_code' => $values['q_49_imag_play_peers_current_code'],
                                                             'q_49_imag_play_peers_most_abnormal_code' => $values['q_49_imag_play_peers_most_abnormal_code'],
                                                             'q_50_direct_gaze_current_code' => $values['q_50_direct_gaze_current_code'],
                                                             'q_50_direct_gaze_most_abnormal_code' => $values['q_50_direct_gaze_most_abnormal_code'],
                                                             'q_51_social_smiling_current_code' => $values['q_51_social_smiling_current_code'],
                                                             'q_51_social_smiling_most_abnormal_code' => $values['q_51_social_smiling_most_abnormal_code'],
                                                             'q_52_show_direct_atten_current_code' => $values['q_52_show_direct_atten_current_code'],
                                                             'q_52_show_direct_atten_most_abnormal_code' => $values['q_52_show_direct_atten_most_abnormal_code'],
                                                             'q_53_offer_share_current_code' => $values['q_53_offer_share_current_code'],
                                                             'q_53_offer_share_most_abnormal_code' => $values['q_53_offer_share_most_abnormal_code'],
                                                             'q_54_seek_share_enjoy_current_code' => $values['q_54_seek_share_enjoy_current_code'],
                                                             'q_54_seek_share_enjoy_most_abnormal_code' => $values['q_54_seek_share_enjoy_most_abnormal_code'],
                                                             'q_55_offer_comf_current_code' => $values['q_55_offer_comf_current_code'],
                                                             'q_55_offer_comf_most_abnormal_code' => $values['q_55_offer_comf_most_abnormal_code'],
                                                             'q_56_qual_social_overts_current_code' => $values['q_56_qual_social_overts_current_code'],
                                                             'q_56_qual_social_overts_most_abnormal_code' => $values['q_56_qual_social_overts_most_abnormal_code'],
                                                             'q_57_range_facial_expr_current_code' => $values['q_57_range_facial_expr_current_code'],
                                                             'q_57_range_facial_expr_most_abnormal_code' => $values['q_57_range_facial_expr_most_abnormal_code'],
                                                             'q_58_inappropriate_facial_current_code' => $values['q_58_inappropriate_facial_current_code'],
                                                             'q_58_inappropriate_facial_ever_code' => $values['q_58_inappropriate_facial_ever_code'],
                                                             'q_59_appropriat_resp_current_code' => $values['q_59_appropriat_resp_current_code'],
                                                             'q_59_appropriat_resp_most_abnormal_code' => $values['q_59_appropriat_resp_most_abnormal_code'],
                                                             'q_60_init_activities_current_code' => $values['q_60_init_activities_current_code'],
                                                             'q_60_init_activities_most_abnormal_code' => $values['q_60_init_activities_most_abnormal_code'],
                                                             'q_61_imit_soc_play_current_code' => $values['q_61_imit_soc_play_current_code'],
                                                             'q_61_imit_soc_play_most_abnormal_code' => $values['q_61_imit_soc_play_most_abnormal_code'],
                                                             'q_62_inter_children_current_code' => $values['q_62_inter_children_current_code'],
                                                             'q_62_inter_children_most_abnormal_code' => $values['q_62_inter_children_most_abnormal_code'],
                                                             'q_63_resp_approaches_current_code' => $values['q_63_resp_approaches_current_code'],
                                                             'q_63_resp_approaches_most_abnormal_code' => $values['q_63_resp_approaches_most_abnormal_code'],
                                                             'q_64_group_play_peers_current_code' => $values['q_64_group_play_peers_current_code'],
                                                             'q_64_group_play_peers_most_abnormal_code' => $values['q_64_group_play_peers_most_abnormal_code'],
                                                             'q_65_friendships_current_code' => $values['q_65_friendships_current_code'],
                                                             'q_65_friendships_most_abnormal_code' => $values['q_65_friendships_most_abnormal_code'],
                                                             'q_66_soc_disinhibit_current_code' => $values['q_66_soc_disinhibit_current_code'],
                                                             'q_66_soc_disinhibit_most_abnormal_code' => $values['q_66_soc_disinhibit_most_abnormal_code'],
                                                             'q_67_unusual_preoccupations_current_code' => $values['q_67_unusual_preoccupations_current_code'],
                                                             'q_67_unusual_preoccupations_ever_code' => $values['q_67_unusual_preoccupations_ever_code'],
                                                             'q_68_circumscr_ints_current_code' => $values['q_68_circumscr_ints_current_code'],
                                                             'q_68_circumscr_ints_ever_code' => $values['q_68_circumscr_ints_ever_code'],
                                                             'q_69_repet_use_objects_current_code' => $values['q_69_repet_use_objects_current_code'],
                                                             'q_69_repet_use_objects_ever_code' => $values['q_69_repet_use_objects_ever_code'],
                                                             'q_70_compulsions_rituals_current_code' => $values['q_70_compulsions_rituals_current_code'],
                                                             'q_70_compulsions_rituals_ever_code' => $values['q_70_compulsions_rituals_ever_code'],
                                                             'q_71_unusual_sens_ints_current_code' => $values['q_71_unusual_sens_ints_current_code'],
                                                             'q_71_unusual_sens_ints_ever_code' => $values['q_71_unusual_sens_ints_ever_code'],
                                                             'q_72_undo_gen_sens_noise_current_code' => $values['q_72_undo_gen_sens_noise_current_code'],
                                                             'q_72_undo_gen_sens_noise_ever_code' => $values['q_72_undo_gen_sens_noise_ever_code'],
                                                             'q_73_idiosyncratic_current_code' => $values['q_73_idiosyncratic_current_code'],
                                                             'q_73_idiosyncratic_ever_code' => $values['q_73_idiosyncratic_ever_code'],
                                                             'q_74_diff_minor_changes_current_code' => $values['q_74_diff_minor_changes_current_code'],
                                                             'q_74_diff_minor_changes_ever_code' => $values['q_74_diff_minor_changes_ever_code'],
                                                             'q_75_resist_trivial_chng_current_code' => $values['q_75_resist_trivial_chng_current_code'],
                                                             'q_75_resist_trivial_chng_ever_code' => $values['q_75_resist_trivial_chng_ever_code'],
                                                             'q_76_unus_attach_objects_current_code' => $values['q_76_unus_attach_objects_current_code'],
                                                             'q_76_unus_attach_objects_ever_code' => $values['q_76_unus_attach_objects_ever_code'],
                                                             'q_77_hands_finger_manners_current_code' => $values['q_77_hands_finger_manners_current_code'],
                                                             'q_77_hands_finger_manners_ever_code' => $values['q_77_hands_finger_manners_ever_code'],
                                                             'q_78_oth_complex_manners_current_code' => $values['q_78_oth_complex_manners_current_code'],
                                                             'q_78_oth_complex_manners_ever_code' => $values['q_78_oth_complex_manners_ever_code'],
                                                             'q_79_midline_hand_moves_current_code' => $values['q_79_midline_hand_moves_current_code'],
                                                             'q_79_midline_hand_moves_ever_code' => $values['q_79_midline_hand_moves_ever_code'],
                                                             'q_80_gait_current_code' => $values['q_80_gait_current_code'],
                                                             'q_80_gait_most_abnormal_code' => $values['q_80_gait_most_abnormal_code'],
                                                             'q_81_aggress_caregivers_current_code' => $values['q_81_aggress_caregivers_current_code'],
                                                             'q_81_aggress_caregivers_ever_code' => $values['q_81_aggress_caregivers_ever_code'],
                                                             'q_82_aggress_noncaregivers_current_code' => $values['q_82_aggress_noncaregivers_current_code'],
                                                             'q_82_aggress_noncaregivers_ever_code' => $values['q_82_aggress_noncaregivers_ever_code'],
                                                             'q_83_self_injury_current_code' => $values['q_83_self_injury_current_code'],
                                                             'q_83_self_injury_ever_code' => $values['q_83_self_injury_ever_code'],
                                                             'q_84_hyperventilation_current_code' => $values['q_84_hyperventilation_current_code'],
                                                             'q_84_hyperventilation_ever_code' => $values['q_84_hyperventilation_ever_code'],
                                                             'q_85_faints_fits_blackouts_current_code' => $values['q_85_faints_fits_blackouts_current_code'],
                                                             'q_85_faints_fits_blackouts_ever_code' => $values['q_85_faints_fits_blackouts_ever_code'],
                                                             'q_86_age_when_abnormality_first_evident' => $values['q_86_age_when_abnormality_first_evident'],
                                                             'q_87_interviewers_judgment' => $values['q_87_interviewers_judgment'],
                                                             'q_87_interviewers_judgment_status' => $values['q_87_interviewers_judgment_status'],
                                                             'q_88_visuospatial_ability_current_code' => $values['q_88_visuospatial_ability_current_code'],
                                                             'q_88_visuospatial_ability_ever_code' => $values['q_88_visuospatial_ability_ever_code'],
                                                             'q_89_memory_still_current_code' => $values['q_89_memory_still_current_code'],
                                                             'q_89_memory_still_ever_code' => $values['q_89_memory_still_ever_code'],
                                                             'q_90_musical_ability_current_code' => $values['q_90_musical_ability_current_code'],
                                                             'q_90_musical_ability_ever_code' => $values['q_90_musical_ability_ever_code'],
                                                             'q_91_drawings_skill_current_code' => $values['q_91_drawings_skill_current_code'],
                                                             'q_91_drawings_skill_ever_code' => $values['q_91_drawings_skill_ever_code'],
                                                             'q_92_reading_ability_current_code' => $values['q_92_reading_ability_current_code'],
                                                             'q_92_reading_ability_ever_code' => $values['q_92_reading_ability_ever_code'],
                                                             'q_93_computational_ability_current_code' => $values['q_93_computational_ability_current_code'],
                                                             'q_93_computational_ability_ever_code' => $values['q_93_computational_ability_ever_code']
                                                             ));
            $this->identifier = $DB->lastInsertID;
        } else {
            // update the event
            $success = $DB->update('adi_r_reliability', array(
                                                              // 'CommentID' => $this->identifier,
                                                              'Examiner' => $values['Examiner'],
                                                              'Date_taken' => $this->_getDatabaseDate($values['Date_taken']),
                                                              'Gold_standard' => $values['Gold_standard'],
                                                              'DoB_proband' => $values['DoB_proband'],
                                                              'q_2_age_first_noticed_code' => $values['q_2_age_first_noticed_code'],
                                                              'q_2_age_first_noticed_code_status' => $values['q_2_age_first_noticed_code_status'],
                                                              'q_4_onset_as_perceived_code' => $values['q_4_onset_as_perceived_code'],
                                                              'q_4_onset_as_perceived_code_status' => $values['q_4_onset_as_perceived_code_status'],
                                                              'q_5_first_walked_code' => $values['q_5_first_walked_code'],
                                                              'q_5_first_walked_code_status' => $values['q_5_first_walked_code_status'],
                                                              'q_6_bladder_daytime_code' => $values['q_6_bladder_daytime_code'],
                                                              'q_6_bladder_daytime_code_status' => $values['q_6_bladder_daytime_code_status'],
                                                              'q_7_bladder_nighttime_code' => $values['q_7_bladder_nighttime_code'],
                                                              'q_7_bladder_nighttime_code_status' => $values['q_7_bladder_nighttime_code_status'],
                                                              'q_8_bowel_control_code' => $values['q_8_bowel_control_code'],
                                                              'q_8_bowel_control_code_status' => $values['q_8_bowel_control_code_status'],
                                                              'q_9_first_single_words_code' => $values['q_9_first_single_words_code'],
                                                              'q_9_first_single_words_code_status' => $values['q_9_first_single_words_code_status'],
                                                              'q_10_first_phrases_code' => $values['q_10_first_phrases_code'],
                                                              'q_10_first_phrases_code_status' => $values['q_10_first_phrases_code_status'],
                                                              'q_11_loss_of_language' => $values['q_11_loss_of_language'],
                                                              'q_12_level_before_loss_code' => $values['q_12_level_before_loss_code'],
                                                              '13_loss_of_spontaneous_use_code' => $values['13_loss_of_spontaneous_use_code'],
                                                              '14_loss_of_intent_code' => $values['14_loss_of_intent_code'],
                                                              '15_loss_of_syntactical_code' => $values['15_loss_of_syntactical_code'],
                                                              '16_loss_of_articulation_code' => $values['16_loss_of_articulation_code'],
                                                              'q_17_main_loss_apparent_code' => $values['q_17_main_loss_apparent_code'],
                                                              'q_17_main_loss_apparent_code_status' => $values['q_17_main_loss_apparent_code_status'],
                                                              'q_18_loss_due_to_illness' => $values['q_18_loss_due_to_illness'],
                                                              'q_19_duration_of_loss_code' => $values['q_19_duration_of_loss_code'],
                                                              'q_19_duration_of_loss_code_status' => $values['q_19_duration_of_loss_code_status'],
                                                              'q_20_loss_of_skills_code' => $values['q_20_loss_of_skills_code'],
                                                              'q_21_puposive_hand_movements_code' => $values['q_21_puposive_hand_movements_code'],
                                                              'q_22_motor_skills_code' => $values['q_22_motor_skills_code'],
                                                              'q_23_self_help_skills_code' => $values['q_23_self_help_skills_code'],
                                                              'q_24_constructive_play_code' => $values['q_24_constructive_play_code'],
                                                              'q_25_social_engagement_code' => $values['q_25_social_engagement_code'],
                                                              'q_26_loss_first_apparent_code' => $values['q_26_loss_first_apparent_code'],
                                                              'q_26_loss_first_apparent_code_status' => $values['q_26_loss_first_apparent_code_status'],
                                                              'q_27_physical_illness_code' => $values['q_27_physical_illness_code'],
                                                              'q_28_duration_of_loss_code' => $values['q_28_duration_of_loss_code'],
                                                              'q_28_duration_of_loss_code_status' => $values['q_28_duration_of_loss_code_status'],
                                                              'q_29_compreh_simple_current' => $values['q_29_compreh_simple_current'],
                                                              'q_29_compreh_simple_most_abnormal' => $values['q_29_compreh_simple_most_abnormal'],
                                                              'q_30_overall_level_of_language' => $values['q_30_overall_level_of_language'],
                                                              'q_31_use_of_others_body_current_code' => $values['q_31_use_of_others_body_current_code'],
                                                              'q_31_use_of_others_body_ever_code' => $values['q_31_use_of_others_body_ever_code'],
                                                              'q_32_artic_pronun_current_code' => $values['q_32_artic_pronun_current_code'],
                                                              'q_32_artic_pronun_5years_code' => $values['q_32_artic_pronun_5years_code'],
                                                              'q_33_stereotyped_utterances_current_code' => $values['q_33_stereotyped_utterances_current_code'],
                                                              'q_33_stereotyped_utterances_ever_code' => $values['q_33_stereotyped_utterances_ever_code'],
                                                              'q_34_social_verb_chat_current_code' => $values['q_34_social_verb_chat_current_code'],
                                                              'q_34_social_verb_chat_ever_code' => $values['q_34_social_verb_chat_ever_code'],
                                                              'q_35_recipr_convers_current_code' => $values['q_35_recipr_convers_current_code'],
                                                              'q_35_recipr_convers_ever_code' => $values['q_35_recipr_convers_ever_code'],
                                                              'q_36_inappropriate_qs_current_code' => $values['q_36_inappropriate_qs_current_code'],
                                                              'q_36_inappropriate_qs_ever_code' => $values['q_36_inappropriate_qs_ever_code'],
                                                              'q_37_prenominal_reversal_current_code' => $values['q_37_prenominal_reversal_current_code'],
                                                              'q_37_prenominal_reversal_ever_code' => $values['q_37_prenominal_reversal_ever_code'],
                                                              'q_38_neologisms_current_code' => $values['q_38_neologisms_current_code'],
                                                              'q_38_neologisms_ever_code' => $values['q_38_neologisms_ever_code'],
                                                              'q_39_verbal_rituals_current_code' => $values['q_39_verbal_rituals_current_code'],
                                                              'q_39_verbal_rituals_ever_code' => $values['q_39_verbal_rituals_ever_code'],
                                                              'q_40_inton_vol_rhythm_rate_current_code' => $values['q_40_inton_vol_rhythm_rate_current_code'],
                                                              'q_40_inton_vol_rhythm_rate_ever_code' => $values['q_40_inton_vol_rhythm_rate_ever_code'],
                                                              'q_41_cur_comm_speech_current_code' => $values['q_41_cur_comm_speech_current_code'],
                                                              'q_41_cur_comm_speech_at5_code' => $values['q_41_cur_comm_speech_at5_code'],
                                                              'q_42_point_express_interest_current_code' => $values['q_42_point_express_interest_current_code'],
                                                              'q_42_point_express_inter_most_abnormal_code' => $values['q_42_point_express_inter_most_abnormal_code'],
                                                              'q_43_nodding_current_code' => $values['q_43_nodding_current_code'],
                                                              'q_43_nodding_most_abnormal_code' => $values['q_43_nodding_most_abnormal_code'],
                                                              'q_44_head_shaking_current_code' => $values['q_44_head_shaking_current_code'],
                                                              'q_44_head_shaking_most_abnormal_code' => $values['q_44_head_shaking_most_abnormal_code'],
                                                              'q_45_conventional_instr_gests_current_code' => $values['q_45_conventional_instr_gests_current_code'],
                                                              'q_45_conventional_instr_gests_most_abnormal_code' => $values['q_45_conventional_instr_gests_most_abnormal_code'],
                                                              'q_46_attent_voice_current_code' => $values['q_46_attent_voice_current_code'],
                                                              'q_46_attent_voice_most_abnormal_code' => $values['q_46_attent_voice_most_abnormal_code'],
                                                              'q_47_spont_imit_current_code' => $values['q_47_spont_imit_current_code'],
                                                              'q_47_spont_imit_most_abnormal_code' => $values['q_47_spont_imit_most_abnormal_code'],
                                                              'q_48_imag_play_current_code' => $values['q_48_imag_play_current_code'],
                                                              'q_48_imag_play_most_abnormal_code' => $values['q_48_imag_play_most_abnormal_code'],
                                                              'q_49_imag_play_peers_current_code' => $values['q_49_imag_play_peers_current_code'],
                                                              'q_49_imag_play_peers_most_abnormal_code' => $values['q_49_imag_play_peers_most_abnormal_code'],
                                                              'q_50_direct_gaze_current_code' => $values['q_50_direct_gaze_current_code'],
                                                              'q_50_direct_gaze_most_abnormal_code' => $values['q_50_direct_gaze_most_abnormal_code'],
                                                              'q_51_social_smiling_current_code' => $values['q_51_social_smiling_current_code'],
                                                              'q_51_social_smiling_most_abnormal_code' => $values['q_51_social_smiling_most_abnormal_code'],
                                                              'q_52_show_direct_atten_current_code' => $values['q_52_show_direct_atten_current_code'],
                                                              'q_52_show_direct_atten_most_abnormal_code' => $values['q_52_show_direct_atten_most_abnormal_code'],
                                                              'q_53_offer_share_current_code' => $values['q_53_offer_share_current_code'],
                                                              'q_53_offer_share_most_abnormal_code' => $values['q_53_offer_share_most_abnormal_code'],
                                                              'q_54_seek_share_enjoy_current_code' => $values['q_54_seek_share_enjoy_current_code'],
                                                              'q_54_seek_share_enjoy_most_abnormal_code' => $values['q_54_seek_share_enjoy_most_abnormal_code'],
                                                              'q_55_offer_comf_current_code' => $values['q_55_offer_comf_current_code'],
                                                              'q_55_offer_comf_most_abnormal_code' => $values['q_55_offer_comf_most_abnormal_code'],
                                                              'q_56_qual_social_overts_current_code' => $values['q_56_qual_social_overts_current_code'],
                                                              'q_56_qual_social_overts_most_abnormal_code' => $values['q_56_qual_social_overts_most_abnormal_code'],
                                                              'q_57_range_facial_expr_current_code' => $values['q_57_range_facial_expr_current_code'],
                                                              'q_57_range_facial_expr_most_abnormal_code' => $values['q_57_range_facial_expr_most_abnormal_code'],
                                                              'q_58_inappropriate_facial_current_code' => $values['q_58_inappropriate_facial_current_code'],
                                                              'q_58_inappropriate_facial_ever_code' => $values['q_58_inappropriate_facial_ever_code'],
                                                              'q_59_appropriat_resp_current_code' => $values['q_59_appropriat_resp_current_code'],
                                                              'q_59_appropriat_resp_most_abnormal_code' => $values['q_59_appropriat_resp_most_abnormal_code'],
                                                              'q_60_init_activities_current_code' => $values['q_60_init_activities_current_code'],
                                                              'q_60_init_activities_most_abnormal_code' => $values['q_60_init_activities_most_abnormal_code'],
                                                              'q_61_imit_soc_play_current_code' => $values['q_61_imit_soc_play_current_code'],
                                                              'q_61_imit_soc_play_most_abnormal_code' => $values['q_61_imit_soc_play_most_abnormal_code'],
                                                             'q_62_inter_children_current_code' => $values['q_62_inter_children_current_code'],
                                                              'q_62_inter_children_most_abnormal_code' => $values['q_62_inter_children_most_abnormal_code'],
                                                              'q_63_resp_approaches_current_code' => $values['q_63_resp_approaches_current_code'],
                                                              'q_63_resp_approaches_most_abnormal_code' => $values['q_63_resp_approaches_most_abnormal_code'],
                                                              'q_64_group_play_peers_current_code' => $values['q_64_group_play_peers_current_code'],
                                                              'q_64_group_play_peers_most_abnormal_code' => $values['q_64_group_play_peers_most_abnormal_code'],
                                                              'q_65_friendships_current_code' => $values['q_65_friendships_current_code'],
                                                              'q_65_friendships_most_abnormal_code' => $values['q_65_friendships_most_abnormal_code'],
                                                              'q_66_soc_disinhibit_current_code' => $values['q_66_soc_disinhibit_current_code'],
                                                              'q_66_soc_disinhibit_most_abnormal_code' => $values['q_66_soc_disinhibit_most_abnormal_code'],
                                                              'q_67_unusual_preoccupations_current_code' => $values['q_67_unusual_preoccupations_current_code'],
                                                              'q_67_unusual_preoccupations_ever_code' => $values['q_67_unusual_preoccupations_ever_code'],
                                                              'q_68_circumscr_ints_current_code' => $values['q_68_circumscr_ints_current_code'],
                                                              'q_68_circumscr_ints_ever_code' => $values['q_68_circumscr_ints_ever_code'],
                                                              'q_69_repet_use_objects_current_code' => $values['q_69_repet_use_objects_current_code'],
                                                              'q_69_repet_use_objects_ever_code' => $values['q_69_repet_use_objects_ever_code'],
                                                              'q_70_compulsions_rituals_current_code' => $values['q_70_compulsions_rituals_current_code'],
                                                              'q_70_compulsions_rituals_ever_code' => $values['q_70_compulsions_rituals_ever_code'],
                                                              'q_71_unusual_sens_ints_current_code' => $values['q_71_unusual_sens_ints_current_code'],
                                                              'q_71_unusual_sens_ints_ever_code' => $values['q_71_unusual_sens_ints_ever_code'],
                                                              'q_72_undo_gen_sens_noise_current_code' => $values['q_72_undo_gen_sens_noise_current_code'],
                                                              'q_72_undo_gen_sens_noise_ever_code' => $values['q_72_undo_gen_sens_noise_ever_code'],
                                                              'q_73_idiosyncratic_current_code' => $values['q_73_idiosyncratic_current_code'],
                                                              'q_73_idiosyncratic_ever_code' => $values['q_73_idiosyncratic_ever_code'],
                                                              'q_74_diff_minor_changes_current_code' => $values['q_74_diff_minor_changes_current_code'],
                                                              'q_74_diff_minor_changes_ever_code' => $values['q_74_diff_minor_changes_ever_code'],
                                                              'q_75_resist_trivial_chng_current_code' => $values['q_75_resist_trivial_chng_current_code'],
                                                              'q_75_resist_trivial_chng_ever_code' => $values['q_75_resist_trivial_chng_ever_code'],
                                                              'q_76_unus_attach_objects_current_code' => $values['q_76_unus_attach_objects_current_code'],
                                                              'q_76_unus_attach_objects_ever_code' => $values['q_76_unus_attach_objects_ever_code'],
                                                              'q_77_hands_finger_manners_current_code' => $values['q_77_hands_finger_manners_current_code'],
                                                              'q_77_hands_finger_manners_ever_code' => $values['q_77_hands_finger_manners_ever_code'],
                                                              'q_78_oth_complex_manners_current_code' => $values['q_78_oth_complex_manners_current_code'],
                                                              'q_78_oth_complex_manners_ever_code' => $values['q_78_oth_complex_manners_ever_code'],
                                                              'q_79_midline_hand_moves_current_code' => $values['q_79_midline_hand_moves_current_code'],
                                                              'q_79_midline_hand_moves_ever_code' => $values['q_79_midline_hand_moves_ever_code'],
                                                              'q_80_gait_current_code' => $values['q_80_gait_current_code'],
                                                              'q_80_gait_most_abnormal_code' => $values['q_80_gait_most_abnormal_code'],
                                                              'q_81_aggress_caregivers_current_code' => $values['q_81_aggress_caregivers_current_code'],
                                                              'q_81_aggress_caregivers_ever_code' => $values['q_81_aggress_caregivers_ever_code'],
                                                              'q_82_aggress_noncaregivers_current_code' => $values['q_82_aggress_noncaregivers_current_code'],
                                                              'q_82_aggress_noncaregivers_ever_code' => $values['q_82_aggress_noncaregivers_ever_code'],
                                                              'q_83_self_injury_current_code' => $values['q_83_self_injury_current_code'],
                                                              'q_83_self_injury_ever_code' => $values['q_83_self_injury_ever_code'],
                                                              'q_84_hyperventilation_current_code' => $values['q_84_hyperventilation_current_code'],
                                                              'q_84_hyperventilation_ever_code' => $values['q_84_hyperventilation_ever_code'],
                                                              'q_85_faints_fits_blackouts_current_code' => $values['q_85_faints_fits_blackouts_current_code'],
                                                              'q_85_faints_fits_blackouts_ever_code' => $values['q_85_faints_fits_blackouts_ever_code'],
                                                              'q_86_age_when_abnormality_first_evident' => $values['q_86_age_when_abnormality_first_evident'],
                                                              'q_87_interviewers_judgment' => $values['q_87_interviewers_judgment'],
                                                              'q_87_interviewers_judgment_status' => $values['q_87_interviewers_judgment_status'],
                                                              'q_88_visuospatial_ability_current_code' => $values['q_88_visuospatial_ability_current_code'],
                                                              'q_88_visuospatial_ability_ever_code' => $values['q_88_visuospatial_ability_ever_code'],
                                                              'q_89_memory_still_current_code' => $values['q_89_memory_still_current_code'],
                                                              'q_89_memory_still_ever_code' => $values['q_89_memory_still_ever_code'],
                                                              'q_90_musical_ability_current_code' => $values['q_90_musical_ability_current_code'],
                                                              'q_90_musical_ability_ever_code' => $values['q_90_musical_ability_ever_code'],
                                                              'q_91_drawings_skill_current_code' => $values['q_91_drawings_skill_current_code'],
                                                              'q_91_drawings_skill_ever_code' => $values['q_91_drawings_skill_ever_code'],
                                                              'q_92_reading_ability_current_code' => $values['q_92_reading_ability_current_code'],
                                                              'q_92_reading_ability_ever_code' => $values['q_92_reading_ability_ever_code'],
                                                              'q_93_computational_ability_current_code' => $values['q_93_computational_ability_current_code'],
                                                              'q_93_computational_ability_ever_code' => $values['q_93_computational_ability_ever_code']
                                                              ),          
                                   array('CommentID'=>$this->identifier)
                                   ); 
        }
        
        $this->form->freeze();
        $this->tpl_data['success'] = true;
    }
 
 function _validate($values)
 {
     $DB =& Database::singleton();
     $query = "SELECT count(*) AS counter FROM candidate WHERE CandID='$values[CandID]' and PSCID='$values[PSCID]'";
     $recordsFound = $DB->selectOne($query);
     $errors = array();
     
     if($recordsFound < 1) {
         $errors['CandID'] = "Specified DCCID and PSCID do not exist or do not match.";
     }
     
     return $errors;
 }   
 
 function display()
 {
     if(!$this->form->isFrozen()) {
         // hidden values
         $this->form->addElement('hidden', 'test_name', $this->name);
         $this->form->addElement('hidden', 'subtest', $this->page);
         $this->form->addElement('hidden', 'identifier', $this->identifier);
         $this->form->addElement('submit', 'fire_away', 'Save Data', 'class=button');
     }
     
     // get the defaults
     $localDefaults = $this->_getDefaults();
     if(!is_array($localDefaults)) { $localDefaults = array(); }
     // set the quickform object defaults
     $this->form->setDefaults(array_merge($this->defaults, $localDefaults));
     
     // trim all values
     $this->form->applyFilter('__ALL__', 'trim');
     
     // display the HTML_Quickform object
     $smarty = new Smarty_neurodb;
     
     // display the HTML_Quickform object
     return $this->form->toHTML();
     
     $renderer =& new HTML_QuickForm_Renderer_Default();
     $renderer->setFormTemplate("<form{attributes}><table class=\"instrument\">{content}</table></form>");
     $renderer->setElementTemplate("<tr><td class=\"lab\"><!-- BEGIN required --><span style=\"color: #ff0000\">*</span><!-- END required -->{label}</td><td class=\"ele\"><!-- BEGIN error --><span style=\"color: #ff0000\">{error}</span><br /><!-- END error -->{element}</td></tr>");
     $renderer->setElementTemplate("<tr><td class=\"lab\"><i>{label}</i></td><td class=\"ele\">\t<i>{element}</i></td></tr>", "static");
     $renderer->setHeaderTemplate("<tr><th colspan=\"2\"><br><b>{header}</b></th></tr>");
     $this->form->accept($renderer);
     return $renderer->toHtml();
     
 } // end function display
 
 function _addMetadataFields()
  {
      $config =& NDB_Config::singleton();
      $dateOptions = array(
                           'language' => 'en',
                           'format'   => 'YMd',
                           'minYear'  => $config->getSetting('startYear'),
                           'maxYear'  => $config->getSetting('endYear'),
                           'addEmptyOption' => true,
                           'emptyOptionValue' => null
                           );

      $this->form->addElement('date', 'Date_taken', 'Date of Administration', $dateOptions);
      
      $examiners = $this->_getExaminerNames();
      $this->form->addElement('select', 'Examiner', 'Examiner', $examiners);
      
      //$this->form->addElement('text', 'Examiner', 'Examiner');
      
      $this->form->addGroupRule('Date_taken', 'Date of Administration is required', 'required');
      
      $this->form->registerRule('checkdate', 'callback', '_checkDate');
      $this->form->addRule('Date_taken', 'Date of Administration is invalid', 'checkdate');
      
      $this->form->addRule('Examiner', 'Examiner is required', 'required');
  }
  
  function _getExaminerNames()
   {
       $db =& Database::singleton();
       $centerID = $db->selectOne("SELECT session.CenterID FROM session, flag WHERE session.ID=flag.SessionID and flag.CommentID='".$this->identifier."'");

       $db->select("SELECT examinerID, full_name FROM examiners WHERE centerID='$centerID' ORDER BY full_name", $results);
       
       $examiners = array(''=>'');
       if(is_array($results) && !empty($results)) {
           foreach($results AS $row) {
               $examiners[$row['examinerID']] = $row['full_name'];
           }
       }
       return $examiners;
   }
   
   function _getDatabaseDate($formDateValue){
        if(!empty($formDateValue)){
            if(count($formDateValue)==2){
                $databaseValue = "$formDateValue[H]:$formDateValue[i]";  //handle time (HH:MM:SS)
            } else {
                $databaseValue = "$formDateValue[Y]-$formDateValue[M]-$formDateValue[d]";  //handle date (YYYY/MM/DD)
            }
        }
        return $databaseValue;
    }
 
}
?>
