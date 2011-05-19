alter table neuro_screen change 1_strabismus q1_strabismus enum('0_absent','1_covert','2_overt','7_can_t_tell','8_no_overt','9_not_tested','not_answered');
alter table neuro_screen change 1_strabismus_specify q1_strabismus_specify varchar(255);
alter table neuro_screen change 1_strabismus_specify_status q1_strabismus_specify_status enum('not_answered');
alter table neuro_screen change 2_ptosis q2_ptosis enum('0_absent','1_doubtful','2_definite','8_suject_unable','9_failure_to_test','not_answered');
alter table neuro_screen change 2_specify q2_specify varchar(255);
alter table neuro_screen change 2_specify_status q2_specify_status enum('not_answered');
alter table neuro_screen change 3_epicanthus q3_epicanthus enum('0_normal','1_partly_covered','2_deeply_covered','8_subject_unable','9_failure_to_test','not_answered');
alter table neuro_screen change 4_low_seated_ears q4_low_seated_ears enum('0_normal','1_lower_less_than_0.5_cm','2 lower_greater_than_0.5_cm','8_subject_unable','9_failure_to_test','not_answered');
alter table neuro_screen change 5_adherent q5_adherent enum('0_free_hanging_lobe','1_adherent_lobe','8_subject_unable','9_failure_to_test','not_answered');
alter table neuro_screen change 6_ear_formation q6_ear_formation enum('0_normal','1_abnormal','8_subject_unable','9_failure_to_test','not_answered');
alter table neuro_screen change 7_cleft_palate q7_cleft_palate enum('0_absent','1_uncertain','2_present','8_subject_unable','9_failure_to_test','not_answered');
alter table neuro_screen change 7_cleft_describe q7_cleft_describe varchar(255);
alter table neuro_screen change 7_cleft_describe_status q7_cleft_describe_status enum('not_answered');
alter table neuro_screen change 8_craniofacial_dysmorphic q8_craniofacial_dysmorphic enum('0_absent','1_uncertain','2_present','8_subject_unable','9_failure_to_test','not_answered');
alter table neuro_screen change 8_craniofacial_dysmorphic_describe q8_craniofacial_dysmorphic_describe varchar(255);
alter table neuro_screen change 8_craniofacial_dysmorphic_describe_status q8_craniofacial_dysmorphic_describe_status enum('not_answered');
alter table neuro_screen change 9_curved_fifth_finger q9_curved_fifth_finger enum('0_normal','1_slightly_curved_inward','2_markedly_curved_inward','8_subject_unable','9_failure_to_test','not_answered');
alter table neuro_screen change 10_palmar_crease q10_palmar_crease enum('0_normal','1_single_crease','8_subject_unable to carry out task','9_failure_to_test','not_answered');
alter table neuro_screen change 11_symmetrical_gait_abnormality q11_symmetrical_gait_abnormality enum('0_none','1_uncertain_abnormality','2_definite_symmetrical_abnormality','8_subject_unable','9_failure_to_test','not_answered');
alter table neuro_screen change 11_symmetrical_gait_abnormality_specify q11_symmetrical_gait_abnormality_specify varchar(255);
alter table neuro_screen change 11_symmetrical_gait_abnormality_specify_status q11_symmetrical_gait_abnormality_specify_status enum('not_answered');
alter table neuro_screen change 12_asymmetrical_gait_abnormality q12_asymmetrical_gait_abnormality enum('0_none','1_uncertain_asymmetry','2_definite_asymmetry','8_subject_unable','9_failure_to_test','not_answered');
alter table neuro_screen change 12_asymemtrical_gait_abnormality_specify q12_asymemtrical_gait_abnormality_specify varchar(255);
alter table neuro_screen change 12_asymemtrical_gait_abnormality_specify_status q12_asymemtrical_gait_abnormality_specify_status enum('not_answered');
alter table neuro_screen change 13_tone_symmetrical_abnormality q13_tone_symmetrical_abnormality enum('0_none','1_uncertain','2_increased','3_decreased','8_subject_unable','9_failure_to_test','not_answered');
alter table neuro_screen change 13_tone_symmetrical_abnormality_specify q13_tone_symmetrical_abnormality_specify varchar(255);
alter table neuro_screen change 13_tone_symmetrical_abnormality_specify_status q13_tone_symmetrical_abnormality_specify_status enum('not_answered');
alter table neuro_screen change 14_tone_asymmetrical_abnormality q14_tone_asymmetrical_abnormality enum('0_none','1_uncertain','2_increased','3_decreased','8_subject_unable','9_failure_to_test','not_answered');
alter table neuro_screen change 14_tone_asymmetrical_abnormality_specify q14_tone_asymmetrical_abnormality_specify varchar(255);
alter table neuro_screen change 14_tone_asymmetrical_abnormality_specify_status q14_tone_asymmetrical_abnormality_specify_status enum('not_answered');
alter table neuro_screen change 15_appearance q15_appearance enum('0_normal','1_uncertain_abnormality','2_definite_abnormality','8_subject_unable','9_failure_to_test','not_answered');
alter table neuro_screen change 15_appearance_specify q15_appearance_specify varchar(255);
alter table neuro_screen change 15_appearance_specify_status q15_appearance_specify_status enum('not_answered');
alter table neuro_screen change 16_power_upper_limb q16_power_upper_limb enum('0_normal','1_uncertain_mild_weakness','2_unequivocal_weakness_or_asymmetry','8_subject_unable','9_failure_to_test','not_answered');
alter table neuro_screen change 16_power_upper_limb_specify q16_power_upper_limb_specify varchar(255);
alter table neuro_screen change 16_power_upper_limb_specify_status q16_power_upper_limb_specify_status enum('not_answered');
alter table neuro_screen change 17_power_lower_limb q17_power_lower_limb enum('0_normal','1_uncertain_mild_weakness','2_unequivocal_weakness_or_asymmetry','8_subject_unable','9_failure_to_test','not_answered');
alter table neuro_screen change 17_power_lower_limb_specify q17_power_lower_limb_specify varchar(255);
alter table neuro_screen change 17_power_lower_limb_specify_status q17_power_lower_limb_specify_status enum('not_answered');
alter table neuro_screen change 18_other_limb_hand_dysmorphic q18_other_limb_hand_dysmorphic enum('0_absent','1_uncertain','2_present','8_subject_unable','9_failure_to_test','not_answered');
alter table neuro_screen change 18_other_limb_hand_dysmorphic_describe q18_other_limb_hand_dysmorphic_describe varchar(255);
alter table neuro_screen change 18_other_limb_hand_dysmorphic_describe_status q18_other_limb_hand_dysmorphic_describe_status enum('not_answered');
alter table neuro_screen change 19_other_physical_abnormalities q19_other_physical_abnormalities varchar(255);
alter table neuro_screen change 19_other_physical_abnormalities_status q19_other_physical_abnormalities_status enum('not_answered');
alter table neuro_screen change 20_hyper_extensibility_of_joints q20_hyper_extensibility_of_joints enum('0_within_normal_range','1_somewhat_increased','2_definite_hyper_extensibility','8_subject_unable','9_failure_to_test','not_answered');
alter table neuro_screen change 21_handedness_draw_or_write_left q21_handedness_draw_or_write_left enum('+','+_+','+_+_+','not_answered');
alter table neuro_screen change 21_handedness_draw_or_write_right q21_handedness_draw_or_write_right enum('+','+_+','+_+_+','not_answered');
alter table neuro_screen change 21_handedness_throw_or_placing_right q21_handedness_throw_or_placing_right enum('+','+_+','+_+_+','not_answered');
alter table neuro_screen change 21_handedness_total_a_left q21_handedness_total_a_left varchar(255);
alter table neuro_screen change 21_handedness_total_b_right q21_handedness_total_b_right varchar(255);
alter table neuro_screen change 22_child_hc_cm q22_child_hc_cm varachar(255);
alter table neuro_screen change 22_child_hc_cm_status q22_child_hc_cm_status enum('not_answered');
alter table neuro_screen change 22_mother_hc_cm q22_mother_hc_cm varchar(255);
alter table neuro_screen change 22_mother_hc_cm_status q22_mother_hc_cm_status enum('not_answered');
alter table neuro_screen change 22_father_hc_cm q22_father_hc_cm varchar(255);
alter table neuro_screen change 22_father_hc_cm_status q22_father_hc_cm_status enum('not_answered');
alter table neuro_screen change 22_mother_height_cm q22_mother_height_cm varchar(@55);
alter table neuro_screen change 22_mother_height_cm_status q22_mother_height_cm_status enum('not_answered');
alter table neuro_screen change 22_father_height_cm q22_father_height_cm varchar(255);
alter table neuro_screen change 22_father_height_cm_status q22_father_height_cm_status enum('not_answered');
alter table neuro_screen change 22_mother_weight_kg q22_mother_weight_kg varchar(255);
alter table neuro_screen change 22_mother_weight_kg_status q22_mother_weight_kg_status enum('not_answered');
alter table neuro_screen change 22_father_weight_kg q22_father_weight_kg varchar(255);
alter table neuro_screen change 22_father_weight_kg_status q22_father_weight_kg_status enum('not_answered');
alter table neuro_screen change 23_adenoma_sebaceum q23_adenoma_sebaceum enum('0_absent','1_uncertain','2_present','8_subject_unable','9_failure_to_test','not_answered');
alter table neuro_screen change 23_adenoma_sebaceum_describe q23_adenoma_sebaceum_describe varchar(255);
alter table neuro_screen change 23_adenoma_sebaceum_describe_status q23_adenoma_sebaceum_describe_status enum('not_answered');
alter table neuro_screen change 24_ash_leaf_macules q24_ash_leaf_macules enum('0_absent','1_uncertain','2_present','8_subject_unable','9_failure_to_test','not_answered');
alter table neuro_screen change 24_ash_leaf_macules_describe q24_ash_leaf_macules_describe varchar(255);
alter table neuro_screen change 24_ash_leaf_macules_describe_status q24_ash_leaf_macules_describe_status enum('not_answered');
alter table neuro_screen change 25_shagreen_patches q25_shagreen_patches enum('0_absent','1_uncertain','2_present','8_subject_unable','9_failure_to_test','not_answered');
alter table neuro_screen change 25_shagreen_patches_describe q25_shagreen_patches_describe varchar(255);
alter table neuro_screen change 25_shagreen_patches_describe_status q25_shagreen_patches_describe_status enum('not_answered');
alter table neuro_screen change 27_cafe_au_lait_spots q27_cafe_au_lait_spots  enum('0_absent','1_one_three_spots','2_four_or_five_spots','3_six_or_more_spots','8_subject_unable','9_failure_to_test','not_answered');
alter table neuro_screen change 27_cafe_au_lait_spots_describe q27_cafe_au_lait_spots_describe varchar(255);
alter table neuro_screen change 27_cafe_au_lait_spots_describe_status q27_cafe_au_lait_spots_describe_status enum('not_answered');
alter table neuro_screen change 28_cutaneous_nodules q28_cutaneous_nodules enum('0_absent','1_uncertain','2_one_or_more','8_subject_unable','9_failure_to_test','not_answered');
alter table neuro_screen change 28_cutaneous_nodules_describe q28_cutaneous_nodules_describe varchar(255);
alter table neuro_screen change 28_cutaneous_nodules_describe_status q28_cutaneous_nodules_describe_status enum('not_answered');
alter table neuro_screen change 29_third_toe_longer q29_third_toe_longer enum('0_normal','1_appears_equal','2_definitely_longer','8_subject_unable','9_failure_to_test','not_answered');
alter table neuro_screen change 30_toe_spacing q30_toe_spacing enum('0_normal','1_big_gap_between_first_and_second','2_partial_syndactylia_of_two_middle_toes','8_subject_unable','9_failure_to_test','not_answered');
