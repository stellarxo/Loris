ALTER TABLE aosi CHANGE COLUMN 1_visual_tracking_press_1 q1_visual_tracking_press_1 enum('0','1','2','8','not_answered');
ALTER TABLE aosi CHANGE COLUMN 1_visual_tracking_press_2 q1_visual_tracking_press_2 enum('0','1','2','8','not_answered');
ALTER TABLE aosi CHANGE COLUMN 1_visual_tracking_press_3 q1_visual_tracking_press_3 enum('0','1','2','8','not_answered');
ALTER TABLE aosi CHANGE COLUMN 1_visual_tracking_score_override q1_visual_tracking_score_override enum('0','1','2','8','not_answered');
ALTER TABLE aosi CHANGE COLUMN 1_visual_tracking_score q1_visual_tracking_score varchar(255);
ALTER TABLE aosi CHANGE COLUMN 1_visual_tracking_notes q1_visual_tracking_notes text;
ALTER TABLE aosi CHANGE COLUMN 1_visual_tracking_notes_status q1_visual_tracking_notes_status enum('not_answered');
ALTER TABLE aosi CHANGE COLUMN 2_disengagement_of_attention_press_1 q2_disengagement_of_attention_press_1 enum('0','1','2','8','not_answered');
ALTER TABLE aosi CHANGE COLUMN 2_disengagement_of_attention_press_2 q2_disengagement_of_attention_press_2 enum('0','1','2','8','not_answered');
ALTER TABLE aosi CHANGE COLUMN 2_disengagement_of_attention_press_3 q2_disengagement_of_attention_press_3 enum('0','1','2','8','not_answered');
ALTER TABLE aosi CHANGE COLUMN 2_disengagement_of_attention_score_override q2_disengagement_of_attention_score_override enum('0', '1', '2', '8', 'not_answered');
ALTER TABLE aosi CHANGE COLUMN 2_disengagement_of_attention_score q2_disengagement_of_attention_score varchar(255);
ALTER TABLE aosi CHANGE COLUMN 2_disengagement_of_attention_notes q2_disengagement_of_attention_notes text; 
ALTER TABLE aosi CHANGE COLUMN 2_disengagement_of_attention_notes_status q2_disengagement_of_attention_notes_status enum('not_answered');
ALTER TABLE aosi CHANGE COLUMN 3_orients_to_name_press_1_trial_1 q3_orients_to_name_press_1_trial_1 enum('orients_with_eye_contact','orients_without_eye_contact','fail_to_orient','not_applicable','not_answered');
ALTER TABLE aosi CHANGE COLUMN 3_orients_to_name_press_1_trial_2 q3_orients_to_name_press_1_trial_2 enum('orients_with_eye_contact','orients_without_eye_contact','fail_to_orient','not_applicable','not_answered');
ALTER TABLE aosi CHANGE COLUMN 3_orients_to_name_press_2_trial_1 q3_orients_to_name_press_2_trial_1 enum('orients_with_eye_contact','orients_without_eye_contact','fail_to_orient','not_applicable','not_answered');
ALTER TABLE aosi CHANGE COLUMN 3_orients_to_name_press_2_trial_2 q3_orients_to_name_press_2_trial_2 enum('orients_with_eye_contact','orients_without_eye_contact','fail_to_orient','not_applicable','not_answered');
ALTER TABLE aosi CHANGE COLUMN 3_orients_to_name_press_3_trial_1 q3_orients_to_name_press_3_trial_1 enum('orients_with_eye_contact','orients_without_eye_contact','fail_to_orient','not_applicable','not_answered');
ALTER TABLE aosi CHANGE COLUMN 3_orients_to_name_press_3_trial_2 q3_orients_to_name_press_3_trial_2 enum('orients_with_eye_contact','orients_without_eye_contact','fail_to_orient','not_applicable','not_answered');
ALTER TABLE aosi CHANGE COLUMN 3_orients_to_name_score_override q3_orients_to_name_score_override enum('0','1','2','8');
ALTER TABLE aosi CHANGE COLUMN 3_orients_to_name_score q3_orients_to_name_score varchar(255);
ALTER TABLE aosi CHANGE COLUMN 3_orients_to_name_notes q3_orients_to_name_notes text;
ALTER TABLE aosi CHANGE COLUMN 3_orients_to_name_notes_status q3_orients_to_name_notes_status enum('not_answered');
ALTER TABLE aosi CHANGE COLUMN 4_differential_response_to_facial_emotion q4_differential_response_to_facial_emotion enum('0','1','2','8','not_answered');
ALTER TABLE aosi CHANGE COLUMN 4_differential_response_to_facial_emotion_score q4_differential_response_to_facial_emotion_score varchar(255);
ALTER TABLE aosi CHANGE COLUMN 4_differential_response_to_facial_emotion_notes q4_differential_response_to_facial_emotion_notes text;
ALTER TABLE aosi CHANGE COLUMN 4_differential_response_to_facial_emotion_notes_status q4_differential_response_to_facial_emotion_notes_status enum('not_answered');
ALTER TABLE aosi CHANGE COLUMN 5_anticipatory_response q5_anticipatory_response enum('0','1','2','3','8','not_answered');
ALTER TABLE aosi CHANGE COLUMN 5_anticipatory_response_score q5_anticipatory_response_score varchar(255) ;
ALTER TABLE aosi CHANGE COLUMN 5_anticipatory_response_notes q5_anticipatory_response_notes text;
ALTER TABLE aosi CHANGE COLUMN 5_anticipatory_response_notes_status q5_anticipatory_response_notes_status enum('not_answered');
ALTER TABLE aosi CHANGE COLUMN 6_imitation_of_actions_activity_1 q6_imitation_of_actions_activity_1 varchar(255);
ALTER TABLE aosi CHANGE COLUMN 6_imitation_of_actions_act_1_att_1 q6_imitation_of_actions_act_1_att_1 enum('0','1','2','8','not_answered');
ALTER TABLE aosi CHANGE COLUMN 6_imitation_of_actions_act_1_att_2 q6_imitation_of_actions_act_1_att_2 enum('0','1','2','8','not_answered');
ALTER TABLE aosi CHANGE COLUMN 6_imitation_of_actions_act_1_att_3 q6_imitation_of_actions_act_1_att_3 enum('0','1','2','8','not_answered');
ALTER TABLE aosi CHANGE COLUMN 6_imitation_of_actions_activity_2 q6_imitation_of_actions_activity_2 varchar(255);
ALTER TABLE aosi CHANGE COLUMN 6_imitation_of_actions_act_2_att_1 q6_imitation_of_actions_act_2_att_1 enum('0','1','2','8','not_answered');
ALTER TABLE aosi CHANGE COLUMN 6_imitation_of_actions_act_2_att_2 q6_imitation_of_actions_act_2_att_2 enum('0','1','2','8','not_answered');
ALTER TABLE aosi CHANGE COLUMN 6_imitation_of_actions_act_2_att_3 q6_imitation_of_actions_act_2_att_3 enum('0','1','2','8','not_answered');
ALTER TABLE aosi CHANGE COLUMN 6_imitation_of_actions_activity_3 q6_imitation_of_actions_activity_3 varchar(255);
ALTER TABLE aosi CHANGE COLUMN 6_imitation_of_actions_act_3_att_1 q6_imitation_of_actions_act_3_att_1 enum('0','1','2','8','not_answered');
ALTER TABLE aosi CHANGE COLUMN 6_imitation_of_actions_act_3_att_2 q6_imitation_of_actions_act_3_att_2 enum('0','1','2','8','not_answered');
ALTER TABLE aosi CHANGE COLUMN 6_imitation_of_actions_act_3_att_3 q6_imitation_of_actions_act_3_att_3 enum('0','1','2','8','not_answered');
ALTER TABLE aosi CHANGE COLUMN 6_imitation_of_actions_score_override q6_imitation_of_actions_score_override enum('0','1','2','8');
ALTER TABLE aosi CHANGE COLUMN 6_imitation_of_actions_score q6_imitation_of_actions_score varchar(255);
ALTER TABLE aosi CHANGE COLUMN 6_imitation_of_actions_notes q6_imitation_of_actions_notes text;
ALTER TABLE aosi CHANGE COLUMN 6_imitation_of_actions_notes_status q6_imitation_of_actions_notes_status enum('not_answered');
ALTER TABLE aosi CHANGE COLUMN 7_social_babbling q7_social_babbling enum('0','1','2','3','8','not_answered');
ALTER TABLE aosi CHANGE COLUMN 7_social_babbling_notes q7_social_babbling_notes text;
ALTER TABLE aosi CHANGE COLUMN 7_social_babbling_notes_status q7_social_babbling_notes_status enum('not_answered');
ALTER TABLE aosi CHANGE COLUMN 8_eye_contact q8_eye_contact enum('0','2','8','not_answered');
ALTER TABLE aosi CHANGE COLUMN 8_eye_contact_notes q8_eye_contact_notes text;
ALTER TABLE aosi CHANGE COLUMN 8_eye_contact_notes_status q8_eye_contact_notes_status enum('not_answered');
ALTER TABLE aosi CHANGE COLUMN 9_reciprocal_social_smile q9_reciprocal_social_smile enum('0','1','2','3','8','not_answered');
ALTER TABLE aosi CHANGE COLUMN 9_reciprocal_social_smile_notes q9_reciprocal_social_smile_notes text;
ALTER TABLE aosi CHANGE COLUMN 9_reciprocal_social_smile_notes_status q9_reciprocal_social_smile_notes_status enum('not_answered');
ALTER TABLE aosi CHANGE COLUMN 10_coordination_of_eye_gaze_and_action q10_coordination_of_eye_gaze_and_action enum('0','1','2','3','8','not_answered');
ALTER TABLE aosi CHANGE COLUMN 10_coordination_of_eye_gaze_and_action_notes q10_coordination_of_eye_gaze_and_action_notes text;
ALTER TABLE aosi CHANGE COLUMN 10_coordination_of_eye_gaze_and_action_notes_status q10_coordination_of_eye_gaze_and_action_notes_status enum('not_answered');
ALTER TABLE aosi CHANGE COLUMN 11_reactivity q11_reactivity enum('0','1','2','3','8','not_answered');
ALTER TABLE aosi CHANGE COLUMN 11_reactivity_notes q11_reactivity_notes text;
ALTER TABLE aosi CHANGE COLUMN 11_reactivity_notes_status q11_reactivity_notes_status enum('not_answered');
ALTER TABLE aosi CHANGE COLUMN 14_social_interest q14_social_interest enum('0','1','2','3','8','not_answered');
ALTER TABLE aosi CHANGE COLUMN 14_social_interest_notes q14_social_interest_notes text;
ALTER TABLE aosi CHANGE COLUMN 14_social_interest_notes_status q14_social_interest_notes_status enum('not_answered');
ALTER TABLE aosi CHANGE COLUMN 15_transitions q15_transitions enum('0','1','2','8','not_answered');
ALTER TABLE aosi CHANGE COLUMN 15_transitions_notes q15_transitions_notes text;
ALTER TABLE aosi CHANGE COLUMN 15_transitions_notes_status q15_transitions_notes_status enum('not_answered');
ALTER TABLE aosi CHANGE COLUMN 16_motor_control_and_behaviour q16_motor_control_and_behaviour enum('0','1','2','8','not_answered');
ALTER TABLE aosi CHANGE COLUMN 16_motor_control_and_behaviour_notes q16_motor_control_and_behaviour_notes text;
ALTER TABLE aosi CHANGE COLUMN 16_motor_control_and_behaviour_notes_status q16_motor_control_and_behaviour_notes_status enum('not_answered');
ALTER TABLE aosi CHANGE COLUMN 17_atypical_motor q17_atypical_motor enum('0','2','8','not_answered');
ALTER TABLE aosi CHANGE COLUMN 17_atypical_motor_notes q17_atypical_motor_notes text;
ALTER TABLE aosi CHANGE COLUMN 17_atypical_motor_notes_status q17_atypical_motor_notes_status enum('not_answered');
ALTER TABLE aosi CHANGE COLUMN 18_atypical_sensory q18_atypical_sensory enum('0','2','8','not_answered');
ALTER TABLE aosi CHANGE COLUMN 18_atypical_sensory_notes q18_atypical_sensory_notes text;
ALTER TABLE aosi CHANGE COLUMN 18_atypical_sensory_notes_status q18_atypical_sensory_notes_status enum('not_answered');
ALTER TABLE aosi CHANGE COLUMN 19_engagement_of_attention q19_engagement_of_attention enum('0','1','2','8','not_answered');
ALTER TABLE aosi CHANGE COLUMN 19_engagement_of_attention_notes q19_engagement_of_attention_notes text;
ALTER TABLE aosi CHANGE COLUMN 19_engagement_of_attention_notes_status q19_engagement_of_attention_notes_status enum('not_answered');
ALTER TABLE aosi CHANGE COLUMN 20_insistence_on_particular_objects q20_insistence_on_particular_objects enum('0','1','2','8','not_answered');
ALTER TABLE aosi CHANGE COLUMN 20_insistence_on_particular_objects_notes q20_insistence_on_particular_objects_notes text;
ALTER TABLE aosi CHANGE COLUMN 20_insistence_on_particular_objects_notes_status q20_insistence_on_particular_objects_notes_status enum('not_answered');
ALTER TABLE aosi CHANGE COLUMN 21_social_referencing q21_social_referencing enum('0','1','2','8','not_answered');
ALTER TABLE aosi CHANGE COLUMN 21_social_referencing_notes q21_social_referencing_notes text;
ALTER TABLE aosi CHANGE COLUMN 21_social_referencing_notes_status q21_social_referencing_notes_status enum('not_answered');