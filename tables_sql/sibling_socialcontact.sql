CREATE TABLE `sibling_socialcontact` (
`CommentID` varchar(255) NOT NULL default '',

                          `UserID` varchar(255) default NULL,

                          `Examiner` varchar(255) default NULL,

                          `Testdate` timestamp NOT NULL,

                          `Data_entry_completion_status` enum('Incomplete','Complete') NOT NULL default 'Incomplete',
`datecompleted` date default NULL,
`respondent` enum('mother','father','other') default NULL,
`respondent_other` varchar(255) default NULL,
`respondent_other_status` enum('not_answered') default NULL,
`q1_engage_together` enum('0','1','2','3','4','5','6','7','not_answered') default NULL,
`q2_play_together` enum('0','1','2','3','4','5','6','7','not_answered') default NULL,
`q3_different_playtimes` varchar(255) default NULL,
`q3_different_playtimes_status` enum('not_answered') default NULL,
`q4_avg_playtime` varchar(255) default NULL,
`q4_avg_playtime_status` enum('not_answered') default NULL,
`q5_rely_olderchild` enum('often','ocassionally','never','not_answered') default NULL,
`q6_rely_youngerchild` enum('often','ocassionally','never','not_answered') default NULL,
`q7_getalong` enum('very_well','okay','not_very_well','not_answered') default NULL,
`q8_playtogeher` enum('very_well','okay','not_very_well','not_answered') default NULL,
`q9_controlplay` enum('older_child','sibling','both','adult','not_answered') default NULL,
`q10_toneplay` enum('positive','neutral','negative','not_answered') default NULL,
`q11_excitementlevel` enum('very_excited','active','calm','not_answered') default NULL,
`q12_conflicts_duringplay` enum('often','occasionally','rarely','not_answered') default NULL,
`q13_disruptive_conflicts` enum('ends_play','major_disruption','minor_disruption','no_disruption','not_answered') default NULL,
`q14_involed_inplay` enum('lot_of_interaction','stay_close_no_interaction','dont_stay_close_or_interact','not_answered') default NULL,
`q15_stressful_playsession` enum('very_stressful','somewhat_stressful','not_stressful','not_answered') default NULL,
`q16_help_getalong` enum('frequently','occasionally','little_none','not_answered') default NULL,
`q16_participate` enum('frequently','occasionally','little_none','not_answered') default NULL,
`q16_maintain_presence` enum('frequently','occasionally','little_none','not_answered') default NULL,
`q16_outofview_listen` enum('frequently','occasionally','little_none','not_answered') default NULL,
`q16_outofview_cry` enum('frequently','occasionally','little_none','not_answered') default NULL,
`q17_manage_emotions` enum('frequently','occasionally','little_none','not_answered') default NULL,
`q17_understand_rules` enum('frequently','occasionally','little_none','not_answered') default NULL,
`q17_understand_howtoplay` enum('frequently','occasionally','little_none','not_answered') default NULL,
`q17_startplay` enum('frequently','occasionally','little_none','not_answered') default NULL,
`q17_remain_inplay` enum('frequently','occasionally','little_none','not_answered') default NULL,
`q17_manage_conflicts` enum('frequently','occasionally','little_none','not_answered') default NULL,
PRIMARY KEY  (`CommentID`)

              );
INSERT INTO test_names(Test_name, Full_name,Sub_group) VALUES ('sibling_socialcontact','Sibling Contact Questionnaire',1);
INSERT INTO instrument_subtests(Test_name,Subtest_name,Description,Order_number) values ('sibling_socialcontact','sibling_socialcontact_page2','Sibling Contact Questionnaire', 1);
