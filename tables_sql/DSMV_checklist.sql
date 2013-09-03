CREATE TABLE `DSMV_checklist` (
`CommentID` varchar(255) NOT NULL default '',

                          `UserID` varchar(255) default NULL,

                          `Examiner` varchar(255) default NULL,

                          `Testdate` timestamp NOT NULL,

                          `Data_entry_completion_status` enum('Incomplete','Complete') NOT NULL default 'Incomplete',
`Date_taken` date default NULL,
`Candidate_Age` varchar(255) default NULL,
`Window_Difference` varchar(255) default NULL,
`qa1_deficit_reciprocity` enum('yes','no') default NULL,
`qa2_deficit_nonverbal` enum('yes','no') default NULL,
`qa3_deficit_relationships` enum('yes','no') default NULL,
`qb1_stereotyped_speech` enum('yes','no') default NULL,
`qb2_adherence_routine` enum('yes','no') default NULL,
`qb3_restricted_interests` enum('yes','no') default NULL,
`qb4_hypohyper_reactsensory` enum('yes','no') default NULL,
`c_symptoms_earlychildhood` enum('yes','no','not_applicable') default NULL,
`d_cause_social_impairment` enum('yes','no','not_applicable') default NULL,
`asdlevel_socialcommunication` enum('level3','level2','level1','no_support','not_answered') default NULL,
`asdlevel_restricted_interest` enum('level3','level2','level1','no_support','not_answered') default NULL,
`meet_dsm_asd` enum('yes','no') default NULL,
`dsm_asd_confidence` enum('3_very_confident','2_somewhat_confident','1_not_confident') default NULL,
`dsm_asd_comments` text default NULL,
`dsm_asd_comments_status` enum('not_answered') default NULL,
`qa1_deficit_communication_social` enum('yes','no') default NULL,
`qa2_change_communication` enum('yes','no') default NULL,
`qa3_deficit_followrules` enum('yes','no') default NULL,
`qb_limit_communication` enum('yes','no') default NULL,
`qc_onset_earlychildhood` enum('yes','no') default NULL,
`meet_dsm_scd` enum('yes','no') default NULL,
`dsm_scd_confidence` enum('3_very_confident','2_somewhat_confident','1_not_confident') default NULL,
`dsm_scd_comments` text default NULL,
`dsm_scd_comments_status` enum('not_answered') default NULL,
`name_assessor` varchar(255) default NULL,
`date_taken_assessor_date` date default NULL,
`date_taken_assessor_date_status` enum('not_answered') default NULL,
`dsm5_confirmed_diagnosis` enum('yes','no') default NULL,
`name_confirming_clinician` varchar(255) default NULL,
`date_taken_confirming_clinician` date default NULL,
PRIMARY KEY  (`CommentID`));
REPLACE INTO test_names (Test_name, Full_name, Sub_group) VALUES ('DSMV_checklist', 'DSMV_checklist', 1);
INSERT INTO instrument_subtests (Test_name, Subtest_name, Description) VALUES ('DSMV_checklist', 'DSMV_checklist_page1', 'Autism Spectrum Disorder Checklist');
INSERT INTO instrument_subtests (Test_name, Subtest_name, Description) VALUES ('DSMV_checklist', 'DSMV_checklist_page2', 'Social Communication Disorder');
INSERT INTO instrument_subtests (Test_name, Subtest_name, Description) VALUES ('DSMV_checklist', 'DSMV_checklist_page3', 'Diagnostic Consensus');
