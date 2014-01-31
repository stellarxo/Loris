CREATE TABLE `pspq_2` (
`CommentID` varchar(255) NOT NULL default '',
`UserID` varchar(255) default NULL,
`Examiner` varchar(255) default NULL,
`Testdate` timestamp NOT NULL,
`Data_entry_completion_status` enum('Incomplete','Complete') NOT NULL default 'Incomplete',
`datecompleted_respondent` date default NULL,
`respondent_age` varchar(255) default NULL,
`respondent_age_status` enum('not_answered') default NULL,
`respondent` enum('mother','father','stepmother','stepfather','other') default NULL,
`respondent_other` varchar(255) default NULL,
`respondent_other_status` enum('not_answered') default NULL,
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
`comments` text default NULL,
`informant_age` varchar(255) default NULL,
`informant_age_status` enum('not_answered') default NULL,
`informant` enum('spouse','other') default NULL,
`informant_other` varchar(255) default NULL,
`informant_other_status` enum('not_answered') default NULL,
`datecompleted_informant` date default NULL,
`qi1_like_being_otherpeople` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`qi2_hard_wordsout_smoothly` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`qi3_comfortable_unexpectedchanges` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`qi4_hard_avoid_sidetrack` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`qi5_information_than_socialize` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`qi6_talkinto_tryingnew` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`qi7_intune_conversation` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`qi8_warmup_unfamiliarplace` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`qi9_enjoy_socialsituations` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`qi10_voice_flat_monotone` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`qi11_disconnected_outofsync_convo` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`qi12_easy_approach` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`qi13_strongneed_sameness` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`qi14_others_dont_understand` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`qi15_flexible` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`qi16_situations_meetnew_people` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`qi17_talktoomuch_certain_topics` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`qi18_conversation_tobe_polite` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`qi19_lookforward_newthings` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`qi20_speak_tooloud_softly` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`qi21_tell_someone_not_interested` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`qi22_hardtime_change_routine` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`qi23_good_smalltalk` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`qi24_act_myways` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`qi25_connecting_people` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`qi26_peoplefrustrated` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`qi27_conversation_boresme` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`qi28_warmfriendly_others` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`qi29_longpauses_conversations` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`qi30_alter_dailyroutine` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`qi31_alone_ratherthan_withothers` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`qi32_losetrack_talking` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`qi33_follow_routine` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`qi34_change_topic` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`qi35_doingthings_knownway` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`qi36_enjoy_chatting` enum('1_very_rarely','2_rarely','3_occasionally','4_somewhat_often','5_often','6_very_often') default NULL,
`comments_informant` text default NULL,
PRIMARY KEY  (`CommentID`)
);
INSERT INTO test_names(Test_name, Full_name,Sub_group,isDirectEntry) VALUES ('pspq_2','PSPQ-2 (Personality Styles and Preferences Questionnaire)',6,true);
INSERT INTO instrument_subtests (Test_name, Subtest_name, Description, Order_number) VALUES ('pspq_2','pspq_2_page2','Respondent Page2', 1);
INSERT INTO instrument_subtests (Test_name, Subtest_name, Description, Order_number) VALUES ('pspq_2','pspq_2_page3','Respondent Page3', 2);
INSERT INTO instrument_subtests (Test_name, Subtest_name, Description, Order_number) VALUES ('pspq_2','pspq_2_page4','Informant Page1', 3);
INSERT INTO instrument_subtests (Test_name, Subtest_name, Description, Order_number) VALUES ('pspq_2','pspq_2_page5','Informant Page2', 4);
INSERT INTO instrument_subtests (Test_name, Subtest_name, Description, Order_number) VALUES ('pspq_2','pspq_2_page6','Informant Page3', 5);
