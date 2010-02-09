CREATE TABLE `aosi_reliability` (
`CommentID` varchar(255) NOT NULL default '',
`UserID` varchar(255) default NULL,
`Examiner` varchar(255) default NULL,
`Data_entry_completion_status` enum('Incomplete','Complete') NOT NULL default 'Incomplete',
`Date_taken` date default NULL,
`Gold_standard` enum('Gold_standard','Initial_entry') default NULL,
`reliability_score` decimal(5,2) default NULL,
`examiner_location` enum('examiner','in_room_observer','behind_mirror','videotape','not_answered') default NULL,
`total_score_1_18` varchar(255) default NULL,
`number_of_markers` varchar(255) default NULL,
`1_visual_tracking_press_1` enum('0','1','2','8','not_answered') default NULL,
`1_visual_tracking_press_2` enum('0','1','2','8','not_answered') default NULL,
`1_visual_tracking_press_3` enum('0','1','2','8','not_answered') default NULL,
`1_visual_tracking_score_override` enum('0','1','2','8') default NULL,
`1_visual_tracking_score` varchar(255) default NULL,
`1_visual_tracking_notes` text default NULL,
`1_visual_tracking_notes_status` enum('not_answered') default NULL,
`2_disengagement_of_attention_press_1` enum('0','1','2','8','not_answered') default NULL,
`2_disengagement_of_attention_press_2` enum('0','1','2','8','not_answered') default NULL,
`2_disengagement_of_attention_press_3` enum('0','1','2','8','not_answered') default NULL,
`2_disengagement_of_attention_score_override` enum('0','1','2','8') default NULL,
`2_disengagement_of_attention_score` varchar(255) default NULL,
`2_disengagement_of_attention_notes` text default NULL,
`2_disengagement_of_attention_notes_status` enum('not_answered') default NULL,
`free_play_period_1_notes` text default NULL,
`free_play_period_1_notes_status` enum('not_answered') default NULL,
`3_orients_to_name_press_1_trial_1` enum('orients_with_eye_contact','orients_without_eye_contact','fail_to_orient','not_applicable','not_answered') default NULL,
`3_orients_to_name_press_1_trial_2` enum('orients_with_eye_contact','orients_without_eye_contact','fail_to_orient','not_applicable','not_answered') default NULL,
`3_orients_to_name_press_2_trial_1` enum('orients_with_eye_contact','orients_without_eye_contact','fail_to_orient','not_applicable','not_answered') default NULL,
`3_orients_to_name_press_2_trial_2` enum('orients_with_eye_contact','orients_without_eye_contact','fail_to_orient','not_applicable','not_answered') default NULL,
`3_orients_to_name_press_3_trial_1` enum('orients_with_eye_contact','orients_without_eye_contact','fail_to_orient','not_applicable','not_answered') default NULL,
`3_orients_to_name_press_3_trial_2` enum('orients_with_eye_contact','orients_without_eye_contact','fail_to_orient','not_applicable','not_answered') default NULL,
`3_orients_to_name_score_override` enum('0','1','2','8') default NULL,
`3_orients_to_name_score` varchar(255) default NULL,
`3_orients_to_name_notes` text default NULL,
`3_orients_to_name_notes_status` enum('not_answered') default NULL,
`4_differential_response_to_facial_emotion` enum('0','1','2','8','not_answered') default NULL,
`4_differential_response_to_facial_emotion_score` varchar(255) default NULL,
`4_differential_response_to_facial_emotion_notes` text default NULL,
`4_differential_response_to_facial_emotion_notes_status` enum('not_answered') default NULL,
`5_anticipatory_response` enum('0','1','2','3','8','not_answered') default NULL,
`5_anticipatory_response_score` varchar(255) default NULL,
`5_anticipatory_response_notes` text default NULL,
`5_anticipatory_response_notes_status` enum('not_answered') default NULL,
`6_imitation_of_actions_activity_1` varchar(255) default NULL,
`6_imitation_of_actions_act_1_att_1` enum('0','1','2','8','not_answered') default NULL,
`6_imitation_of_actions_act_1_att_2` enum('0','1','2','8','not_answered') default NULL,
`6_imitation_of_actions_act_1_att_3` enum('0','1','2','8','not_answered') default NULL,
`6_imitation_of_actions_activity_2` varchar(255) default NULL,
`6_imitation_of_actions_act_2_att_1` enum('0','1','2','8','not_answered') default NULL,
`6_imitation_of_actions_act_2_att_2` enum('0','1','2','8','not_answered') default NULL,
`6_imitation_of_actions_act_2_att_3` enum('0','1','2','8','not_answered') default NULL,
`6_imitation_of_actions_activity_3` varchar(255) default NULL,
`6_imitation_of_actions_act_3_att_1` enum('0','1','2','8','not_answered') default NULL,
`6_imitation_of_actions_act_3_att_2` enum('0','1','2','8','not_answered') default NULL,
`6_imitation_of_actions_act_3_att_3` enum('0','1','2','8','not_answered') default NULL,
`6_imitation_of_actions_score_override` enum('0','1','2','8') default NULL,
`6_imitation_of_actions_score` varchar(255) default NULL,
`6_imitation_of_actions_notes` text default NULL,
`6_imitation_of_actions_notes_status` enum('not_answered') default NULL,
`free_play_period_2_notes` text default NULL,
`free_play_period_2_notes_status` enum('not_answered') default NULL,
`7_social_babbling` enum('0','1','2','3','8','not_answered') default NULL,
`7_social_babbling_notes` text default NULL,
`7_social_babbling_notes_status` enum('not_answered') default NULL,
`8_eye_contact` enum('0','2','8','not_answered') default NULL,
`8_eye_contact_notes` text default NULL,
`8_eye_contact_notes_status` enum('not_answered') default NULL,
`9_reciprocal_social_smile` enum('0','1','2','3','8','not_answered') default NULL,
`9_reciprocal_social_smile_notes` text default NULL,
`9_reciprocal_social_smile_notes_status` enum('not_answered') default NULL,
`10_coordination_of_eye_gaze_and_action` enum('0','1','2','3','8','not_answered') default NULL,
`10_coordination_of_eye_gaze_and_action_notes` text default NULL,
`10_coordination_of_eye_gaze_and_action_notes_status` enum('not_answered') default NULL,
`11_reactivity` enum('0','1','2','3','8','not_answered') default NULL,
`11_reactivity_notes` text default NULL,
`11_reactivity_notes_status` enum('not_answered') default NULL,
`14_social_interest` enum('0','1','2','3','8','not_answered') default NULL,
`14_social_interest_notes` text default NULL,
`14_social_interest_notes_status` enum('not_answered') default NULL,
`15_transitions` enum('0','1','2','8','not_answered') default NULL,
`15_transitions_notes` text default NULL,
`15_transitions_notes_status` enum('not_answered') default NULL,
`16_motor_control_and_behaviour` enum('0','1','2','8','not_answered') default NULL,
`16_motor_control_and_behaviour_notes` text default NULL,
`16_motor_control_and_behaviour_notes_status` enum('not_answered') default NULL,
`17_atypical_motor` enum('0','2','8','not_answered') default NULL,
`17_atypical_motor_notes` text default NULL,
`17_atypical_motor_notes_status` enum('not_answered') default NULL,
`18_atypical_sensory` enum('0','2','8','not_answered') default NULL,
`18_atypical_sensory_notes` text default NULL,
`18_atypical_sensory_notes_status` enum('not_answered') default NULL,
`19_engagement_of_attention` enum('0','1','2','8','not_answered') default NULL,
`19_engagement_of_attention_notes` text default NULL,
`19_engagement_of_attention_notes_status` enum('not_answered') default NULL,
`20_insistence_on_particular_objects` enum('0','1','2','8','not_answered') default NULL,
`20_insistence_on_particular_objects_notes` text default NULL,
`20_insistence_on_particular_objects_notes_status` enum('not_answered') default NULL,
`21_social_referencing` enum('0','1','2','8','not_answered') default NULL,
`21_social_referencing_notes` text default NULL,
`21_social_referencing_notes_status` enum('not_answered') default NULL,
PRIMARY KEY  (`CommentID`)

              ) TYPE=MyISAM;
