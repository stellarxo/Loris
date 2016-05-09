CREATE TABLE `seq` (
`CommentID` varchar(255) NOT NULL default '',

                          `UserID` varchar(255) default NULL,

                          `Examiner` varchar(255) default NULL,

                          `Testdate` timestamp NOT NULL,

                          `Data_entry_completion_status` enum('Incomplete','Complete') NOT NULL default 'Incomplete',
`Date_taken` date default NULL,
`Candidate_Age` varchar(255) default NULL,
`Window_Difference` varchar(255) default NULL,
`person_completing` enum('mother','father','both_parents','teacher','other') default NULL,
`person_completing_other` varchar(255) default NULL,
`total_seq` varchar(255) default NULL,
`total_hypo` varchar(255) default NULL,
`total_hyper` varchar(255) default NULL,
`total_seeking` varchar(255) default NULL,
`total_social` varchar(255) default NULL,
`total_non-social` varchar(255) default NULL,
`total_tactile` varchar(255) default NULL,
`total_auditory` varchar(255) default NULL,
`total_visual` varchar(255) default NULL,
`total_gustatory_olfactory` varchar(255) default NULL,
`total_vestibular_proprioceptive` varchar(255) default NULL,
`other_comments` text default NULL,
`q1_react_sensitively` enum('almost_never','once_in_a_while','sometimes','frequently','almost_always','not_answered') default NULL,
`q1_react_sensitively_change` enum('yes','no','not_answered') default NULL,
`q1_react_sensitively_what_do` text default NULL,
`q1_react_sensitively_what_do_status` enum('not_answered') default NULL,
`q2_enjoy_music` enum('almost_never','once_in_a_while','sometimes','frequently','almost_always','not_answered') default NULL,
`q2_enjoy_music_change` enum('yes','no','not_answered') default NULL,
`q2_enjoy_music_what_do` text default NULL,
`q2_enjoy_music_what_do_status` enum('not_answered') default NULL,
`q3_ignore_call` enum('almost_never','once_in_a_while','sometimes','frequently','almost_always','not_answered') default NULL,
`q3_ignore_call_change` enum('yes','no','not_answered') default NULL,
`q3_ignore_call_what_do` text default NULL,
`q3_ignore_call_what_do_status` enum('not_answered') default NULL,
`q4_ignore_tune_out` enum('almost_never','once_in_a_while','sometimes','frequently','almost_always','not_answered') default NULL,
`q4_ignore_tune_out_change` enum('yes','no','not_answered') default NULL,
`q4_ignore_tune_out_what_do` text default NULL,
`q4_ignore_tune_out_what_do_status` enum('not_answered') default NULL,
`q5_notive_sounds` enum('almost_never','once_in_a_while','sometimes','frequently','almost_always','not_answered') default NULL,
`q5_notive_sounds_change` enum('yes','no','not_answered') default NULL,
`q5_notive_sounds_what_do` text default NULL,
`q5_notive_sounds_what_do_status` enum('not_answered') default NULL,
`q6_show_distress_loud` enum('almost_never','once_in_a_while','sometimes','frequently','almost_always','not_answered') default NULL,
`q6_show_distress_loud_change` enum('yes','no','not_answered') default NULL,
`q6_show_distress_loud_what_do` text default NULL,
`q6_show_distress_loud_what_do_status` enum('not_answered') default NULL,
`q7_enjoy_picture_books` enum('almost_never','once_in_a_while','sometimes','frequently','almost_always','not_answered') default NULL,
`q7_enjoy_picture_books_change` enum('yes','no','not_answered') default NULL,
`q7_enjoy_picture_books_what_do` text default NULL,
`q7_enjoy_picture_books_what_do_status` enum('not_answered') default NULL,
`q8_disturbed_by_light` enum('almost_never','once_in_a_while','sometimes','frequently','almost_always','not_answered') default NULL,
`q8_disturbed_by_light_change` enum('yes','no','not_answered') default NULL,
`q8_disturbed_by_light_what_do` text default NULL,
`q8_disturbed_by_light_what_do_status` enum('not_answered') default NULL,
`q9_stare_at_lights` enum('almost_never','once_in_a_while','sometimes','frequently','almost_always','not_answered') default NULL,
`q9_stare_at_lights_change` enum('yes','no','not_answered') default NULL,
`q9_stare_at_lights_what_do` text default NULL,
`q9_stare_at_lights_what_do_status` enum('not_answered') default NULL,
`q10_slow_to_notice` enum('almost_never','once_in_a_while','sometimes','frequently','almost_always','not_answered') default NULL,
`q10_slow_to_notice_change` enum('yes','no','not_answered') default NULL,
`q10_slow_to_notice_what_do` text default NULL,
`q10_slow_to_notice_what_do_status` enum('not_answered') default NULL,
`q11_avoid_looking` enum('almost_never','once_in_a_while','sometimes','frequently','almost_always','not_answered') default NULL,
`q11_avoid_looking_change` enum('yes','no','not_answered') default NULL,
`q11_avoid_looking_what_do` text default NULL,
`q11_avoid_looking_what_do_status` enum('not_answered') default NULL,
`q12_seem_to_ignore` enum('almost_never','once_in_a_while','sometimes','frequently','almost_always','not_answered') default NULL,
`q12_seem_to_ignore_change` enum('yes','no','not_answered') default NULL,
`q12_seem_to_ignore_what_do` text default NULL,
`q12_seem_to_ignore_what_do_status` enum('not_answered') default NULL,
`q13_enjoy_watching_videos` enum('almost_never','once_in_a_while','sometimes','frequently','almost_always','not_answered') default NULL,
`q13_enjoy_watching_videos_change` enum('yes','no','not_answered') default NULL,
`q13_enjoy_watching_videos_what_do` text default NULL,
`q13_enjoy_watching_videos_what_do_status` enum('not_answered') default NULL,
`q14_dislike_cuddling` enum('almost_never','once_in_a_while','sometimes','frequently','almost_always','not_answered') default NULL,
`q14_dislike_cuddling_change` enum('yes','no','not_answered') default NULL,
`q14_dislike_cuddling_what_do` text default NULL,
`q14_dislike_cuddling_what_do_status` enum('not_answered') default NULL,
`q15_show_distress_grooming` enum('almost_never','once_in_a_while','sometimes','frequently','almost_always','not_answered') default NULL,
`q15_show_distress_grooming_change` enum('yes','no','not_answered') default NULL,
`q15_show_distress_grooming_what_do` text default NULL,
`q15_show_distress_grooming_what_do_status` enum('not_answered') default NULL,
`q16_avoid_touching` enum('almost_never','once_in_a_while','sometimes','frequently','almost_always','not_answered') default NULL,
`q16_avoid_touching_change` enum('yes','no','not_answered') default NULL,
`q16_avoid_touching_what_do` text default NULL,
`q16_avoid_touching_what_do_status` enum('not_answered') default NULL,
`q17_react_negatively` enum('almost_never','once_in_a_while','sometimes','frequently','almost_always','not_answered') default NULL,
`q17_react_negatively_change` enum('yes','no','not_answered') default NULL,
`q17_react_negatively_what_do` text default NULL,
`q17_react_negatively_what_do_status` enum('not_answered') default NULL,
`q18_trouble_adjusting` enum('almost_never','once_in_a_while','sometimes','frequently','almost_always','not_answered') default NULL,
`q18_trouble_adjusting_change` enum('yes','no','not_answered') default NULL,
`q18_trouble_adjusting_what_do` text default NULL,
`q18_trouble_adjusting_what_do_status` enum('not_answered') default NULL,
`q19_slow_to_react` enum('almost_never','once_in_a_while','sometimes','frequently','almost_always','not_answered') default NULL,
`q19_slow_to_react_change` enum('yes','no','not_answered') default NULL,
`q19_slow_to_react_what_do` text default NULL,
`q19_slow_to_react_what_do_status` enum('not_answered') default NULL,
`q20_dislike_tickled` enum('almost_never','once_in_a_while','sometimes','frequently','almost_always','not_answered') default NULL,
`q20_dislike_tickled_change` enum('yes','no','not_answered') default NULL,
`q20_dislike_tickled_what_do` text default NULL,
`q20_dislike_tickled_what_do_status` enum('not_answered') default NULL,
`q21_ignore_tap` enum('almost_never','once_in_a_while','sometimes','frequently','almost_always','not_answered') default NULL,
`q21_ignore_tap_change` enum('yes','no','not_answered') default NULL,
`q21_ignore_tap_what_do` text default NULL,
`q21_ignore_tap_what_do_status` enum('not_answered') default NULL,
`q22_refuse_new_foods` enum('almost_never','once_in_a_while','sometimes','frequently','almost_always','not_answered') default NULL,
`q22_refuse_new_foods_change` enum('yes','no','not_answered') default NULL,
`q22_refuse_new_foods_what_do` text default NULL,
`q22_refuse_new_foods_what_do_status` enum('not_answered') default NULL,
`q23_smell_objects` enum('almost_never','once_in_a_while','sometimes','frequently','almost_always','not_answered') default NULL,
`q23_smell_objects_change` enum('yes','no','not_answered') default NULL,
`q23_smell_objects_what_do` text default NULL,
`q23_smell_objects_what_do_status` enum('not_answered') default NULL,
`q24_interested_smell` enum('almost_never','once_in_a_while','sometimes','frequently','almost_always','not_answered') default NULL,
`q24_interested_smell_change` enum('yes','no','not_answered') default NULL,
`q24_interested_smell_what_do` text default NULL,
`q24_interested_smell_what_do_status` enum('not_answered') default NULL,
`q25_put_objects` enum('almost_never','once_in_a_while','sometimes','frequently','almost_always','not_answered') default NULL,
`q25_put_objects_change` enum('yes','no','not_answered') default NULL,
`q25_put_objects_what_do` text default NULL,
`q25_put_objects_what_do_status` enum('not_answered') default NULL,
`q26_enjoy_riding` enum('almost_never','once_in_a_while','sometimes','frequently','almost_always','not_answered') default NULL,
`q26_enjoy_riding_change` enum('yes','no','not_answered') default NULL,
`q26_enjoy_riding_what_do` text default NULL,
`q26_enjoy_riding_what_do_status` enum('not_answered') default NULL,
`q27_like_jump` enum('almost_never','once_in_a_while','sometimes','frequently','almost_always','not_answered') default NULL,
`q27_like_jump_change` enum('yes','no','not_answered') default NULL,
`q27_like_jump_what_do` text default NULL,
`q27_like_jump_what_do_status` enum('not_answered') default NULL,
`q28_seek_physical` enum('almost_never','once_in_a_while','sometimes','frequently','almost_always','not_answered') default NULL,
`q28_seek_physical_change` enum('yes','no','not_answered') default NULL,
`q28_seek_physical_what_do` text default NULL,
`q28_seek_physical_what_do_status` enum('not_answered') default NULL,
`q29_uneasy_dizzy` enum('almost_never','once_in_a_while','sometimes','frequently','almost_always','not_answered') default NULL,
`q29_uneasy_dizzy_change` enum('yes','no','not_answered') default NULL,
`q29_uneasy_dizzy_what_do` text default NULL,
`q29_uneasy_dizzy_what_do_status` enum('not_answered') default NULL,
`q30_flap_arms` enum('almost_never','once_in_a_while','sometimes','frequently','almost_always','not_answered') default NULL,
`q30_flap_arms_change` enum('yes','no','not_answered') default NULL,
`q30_flap_arms_what_do` text default NULL,
`q30_flap_arms_what_do_status` enum('not_answered') default NULL,
`q31_free_time` text default NULL,
`q31_free_time_status` enum('not_answered') default NULL,
`q32_seem_happiest` text default NULL,
`q32_seem_happiest_status` enum('not_answered') default NULL,
`q33_enjoy_interaction` text default NULL,
`q33_enjoy_interaction_status` enum('not_answered') default NULL,
`q34_works_best` text default NULL,
`q34_works_best_status` enum('not_answered') default NULL,
`q35_other_comments` text default NULL,
`q35_other_comments_status` enum('not_answered') default NULL,
`q36_a_sounds` enum('almost_never','once_in_a_while','sometimes','frequently','almost_always','not_answered') default NULL,
`q36_b_lights` enum('almost_never','once_in_a_while','sometimes','frequently','almost_always','not_answered') default NULL,
`q36_c_smells` enum('almost_never','once_in_a_while','sometimes','frequently','almost_always','not_answered') default NULL,
`q36_d_tastes` enum('almost_never','once_in_a_while','sometimes','frequently','almost_always','not_answered') default NULL,
`q36_e_textures` enum('almost_never','once_in_a_while','sometimes','frequently','almost_always','not_answered') default NULL,
`q36_f_touch` enum('almost_never','once_in_a_while','sometimes','frequently','almost_always','not_answered') default NULL,
`q37_seek_or_crave` text default NULL,
`q37_seek_or_crave_status` enum('not_answered') default NULL,
`q38_pick_eater` enum('yes','maybe','no','not_answered') default NULL,
`q38_selective` enum('almost_never','once_in_a_while','sometimes','frequently','almost_always','not_answered') default NULL,
`q39_favourite_food_qualities` text default NULL,
`q39_favourite_food_qualities_status` enum('not_answered') default NULL,
`q40_why_foods` text default NULL,
`q40_why_foods_status` enum('not_answered') default NULL,
`q41_a_sounds` enum('almost_never','once_in_a_while','sometimes','frequently','almost_always','not_answered') default NULL,
`q41_b_lights` enum('almost_never','once_in_a_while','sometimes','frequently','almost_always','not_answered') default NULL,
`q41_c_smells` enum('almost_never','once_in_a_while','sometimes','frequently','almost_always','not_answered') default NULL,
`q41_d_tastes` enum('almost_never','once_in_a_while','sometimes','frequently','almost_always','not_answered') default NULL,
`q41_e_textures` enum('almost_never','once_in_a_while','sometimes','frequently','almost_always','not_answered') default NULL,
`q41_f_touch` enum('almost_never','once_in_a_while','sometimes','frequently','almost_always','not_answered') default NULL,
`q42_sensory_change` enum('yes','maybe','no','not_answered') default NULL,
`q42_sensory_change_how` text default NULL,
`q42_sensory_change_how_status` enum('not_answered') default NULL,
`q43_notice_change` text default NULL,
`q43_notice_change_status` enum('not_answered') default NULL,
PRIMARY KEY  (`CommentID`)

              );
