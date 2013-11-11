CREATE TABLE `bapq_informant` (
`CommentID` varchar(255) NOT NULL default '',

                          `UserID` varchar(255) default NULL,

                          `Examiner` varchar(255) default NULL,

                          `Testdate` timestamp NOT NULL,

                          `Data_entry_completion_status` enum('Incomplete','Complete') NOT NULL default 'Incomplete',
`informant_age` varchar(255) default NULL,
`informant_age_status` enum('not_answered') default NULL,
`informant` enum('spouse','other') default NULL,
`informant_other` varchar(255) default NULL,
`informant_other_status` enum('not_answered') default NULL,
`q1_like_being_otherpeople` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`q2_hard_wordsout_smoothly` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`q3_comfortable_unexpectedchanges` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`q4_hard_avoid_sidetrack` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`q5_information_than_socialize` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`q6_talkinto_tryingnew` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`q7_intune_conversation` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`q8_warmup_unfamiliarplace` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`q9_enjoy_socialsituations` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`q10_voice_flat_monotone` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`q11_disconnected_outofsync_convo` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`q12_easy_approach` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`q13_strongneed_sameness` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`q14_others_dont_understand` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`q15_flexible` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`q16_situations_meetnew_people` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`q17_talktoomuch_certain_topics` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`q18_conversation_tobe_polite` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`q19_lookforward_newthings` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`q20_speak_tooloud_softly` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`q21_tell_someone_not_interested` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`q22_hardtime_change_routine` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`q23_good_smalltalk` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`q24_act_myways` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`q25_connecting_people` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`q26_peoplefrustrated` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`q27_conversation_boresme` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`q28_warmfriendly_others` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`q29_longpauses_conversations` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`q30_alter_dailyroutine` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`q31_alone_ratherthan_withothers` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`q32_losetrack_talking` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`q33_follow_routine` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`q34_change_topic` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`q35_doingthings_knownway` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`q36_enjoy_chatting` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
PRIMARY KEY  (`CommentID`)

              );
INSERT INTO test_names(Test_name, Full_name,Sub_group) VALUES ('bapq_informant','BAPQ (Broad Autism Phenotype Questionnaire)[Informant]',1);
INSERT INTO instrument_subtests (Test_name, Subtest_name, Description, Order_number) VALUES ('bapq_informant','bapq_informant_page2','BAPQ Informant Page2', 1);
INSERT INTO instrument_subtests (Test_name, Subtest_name, Description, Order_number) VALUES ('bapq_informant','bapq_informant_page3','BAPQ Informant Page3', 2);
