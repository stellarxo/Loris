CREATE TABLE `parental_stress_scale` (
`CommentID` varchar(255) NOT NULL default '',

                          `UserID` varchar(255) default NULL,

                          `Examiner` varchar(255) default NULL,

                          `Testdate` timestamp NOT NULL,

                          `Data_entry_completion_status` enum('Incomplete','Complete') NOT NULL default 'Incomplete',
`Date_taken_date` date default NULL,
`Date_taken_date_status` enum('not_answered') default NULL,
`visit` enum('','Screening','V03','V06','V09','V09LENA','V12','V15','V15LENA','V18','V24','V36','Vsupplement','not_answered') default NULL,
`person_interviewed` varchar(255) default NULL,
`person_interviewed_status` enum('not_answered') default NULL,
`interviewed_by` varchar(255) default NULL,
`interviewed_by_status` enum('not_answered') default NULL,
`recording_device` enum('','audio','video') default NULL,
`comments` text default NULL,
`comments_status` enum('not_answered') default NULL,
`parent_scale_score` varchar(255) default NULL,
`q1_happy_parent` enum('','1_strongly_disagree','2_disagree','3_undecided','4_agree','5_strongly_agree','refused_dontknow') default NULL,
`q2_do_for_children` enum('','1_strongly_disagree','2_disagree','3_undecided','4_agree','5_strongly_agree','refused_dontknow') default NULL,
`q3_caring_takes_more_energy` enum('','1_strongly_disagree','2_disagree','3_undecided','4_agree','5_strongly_agree','refused_dontknow') default NULL,
`q4_worry_doing_enough` enum('','1_strongly_disagree','2_disagree','3_undecided','4_agree','5_strongly_agree','refused_dontknow') default NULL,
`q5_close_to_children` enum('','1_strongly_disagree','2_disagree','3_undecided','4_agree','5_strongly_agree','refused_dontknow') default NULL,
`q6_enjoy_spending_time` enum('','1_strongly_disagree','2_disagree','3_undecided','4_agree','5_strongly_agree','refused_dontknow') default NULL,
`q7_imp_affection` enum('','1_strongly_disagree','2_disagree','3_undecided','4_agree','5_strongly_agree','refused_dontknow') default NULL,
`q8_optimistic_future` enum('','1_strongly_disagree','2_disagree','3_undecided','4_agree','5_strongly_agree','refused_dontknow') default NULL,
`q9_major_stress` enum('','1_strongly_disagree','2_disagree','3_undecided','4_agree','5_strongly_agree','refused_dontknow') default NULL,
`q10_notime_flexibility` enum('','1_strongly_disagree','2_disagree','3_undecided','4_agree','5_strongly_agree','refused_dontknow') default NULL,
`q11_financial_burden` enum('','1_strongly_disagree','2_disagree','3_undecided','4_agree','5_strongly_agree','refused_dontknow') default NULL,
`q12_diff_balance_responsibilities` enum('','1_strongly_disagree','2_disagree','3_undecided','4_agree','5_strongly_agree','refused_dontknow') default NULL,
`q13_embarassing_stressful` enum('','1_strongly_disagree','2_disagree','3_undecided','4_agree','5_strongly_agree','refused_dontknow') default NULL,
`q14_decide_no_children` enum('','1_strongly_disagree','2_disagree','3_undecided','4_agree','5_strongly_agree','refused_dontknow') default NULL,
`q15_overwhelmed_as_parent` enum('','1_strongly_disagree','2_disagree','3_undecided','4_agree','5_strongly_agree','refused_dontknow') default NULL,
`q16_few_choices_no_control` enum('','1_strongly_disagree','2_disagree','3_undecided','4_agree','5_strongly_agree','refused_dontknow') default NULL,
`q17_satisfied_parent` enum('','1_strongly_disagree','2_disagree','3_undecided','4_agree','5_strongly_agree','refused_dontknow') default NULL,
`q18_children_enjoyable` enum('','1_strongly_disagree','2_disagree','3_undecided','4_agree','5_strongly_agree','refused_dontknow') default NULL,
PRIMARY KEY  (`CommentID`)
);
INSERT INTO instrument_subtests VALUES('', 'parental_stress_scale', 'parental_stress_scale_page1', 'Page1', 1);
INSERT INTO test_names(Test_name, Full_name,Sub_group,isDirectEntry) VALUES ('parental_stress_scale','Parental Stress Scales',6, false);

