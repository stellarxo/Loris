CREATE TABLE `BSRC` (
`CommentID` varchar(255) NOT NULL default '',
                          `UserID` varchar(255) default NULL,
                          `Examiner` varchar(255) default NULL,
                          `Testdate` timestamp NOT NULL,
                          `Data_entry_completion_status` enum('Incomplete','Complete') NOT NULL default 'Incomplete',
`Date_taken` date default NULL,
`Candidate_Age` varchar(255) default NULL,
`Window_Difference` varchar(255) default NULL,
`Date_lastvisit_date` date default NULL,
`Date_lastvisit_date_status` enum('not_answered') default NULL,
`q1_earlyintervention_birthtothreeprg` enum('yes','no','not_answered') default NULL,
`q2_receive_earlyintervention_birthtothreeprg` enum('yes','no','not_answered') default NULL,
`hrs_earlyintervention_birthtothreeprg` text default NULL,
`hrs_earlyintervention_birthtothreeprg_status` enum('not_answered') default NULL,
`total_earlyintervention_birthtothreeprg` text default NULL,
`total_earlyintervention_birthtothreeprg_status` enum('not_answered') default NULL,
`q3_communityact` enum('yes','no','not_answered') default NULL,
`q4_participate_social` enum('yes','no','not_answered') default NULL,
`q5_service_delay` enum('yes','no','not_answered') default NULL,
`servicetype_occupationaltherapy` enum('yes','no','not_answered') default NULL,
`startdate_occupationaltherapy` varchar(255) default NULL,
`startdate_occupationaltherapy_status` enum('not_answered') default NULL,
`continue_occupationaltherapy` enum('yes','no','not_answered') default NULL,
`continue_occupationaltherapy_comment` text default NULL,
`continue_occupationaltherapy_comment_status` enum('not_answered') default NULL,
`indgrp_occupationaltherapy` enum('individual_','group_','not_answered') default NULL,
`setting_occupationaltherapy` enum('office/clinic','home','daycare/preschool','other','not_answered') default NULL,
`setting_occupationaltherapy_other` varchar(255) default NULL,
`setting_occupationaltherapy_other_status` enum('not_answered') default NULL,
`avg_occupationaltherapy` varchar(255) default NULL,
`avg_occupationaltherapy_status` enum('not_answered') default NULL,
`servicetype_physicaltherapy` enum('yes','no','not_answered') default NULL,
`startdate_physicaltherapy` text default NULL,
`startdate_physicaltherapy_status` enum('not_answered') default NULL,
`continue_physicaltherapy` enum('yes','no','not_answered') default NULL,
`continue_physicaltherapy_comment` varchar(255) default NULL,
`continue_physicaltherapy_comment_status` enum('not_answered') default NULL,
`indgrp_physicaltherapy` enum('individual_','group_','not_answered') default NULL,
`setting_physicaltherapy_other` varchar(255) default NULL,
`setting_physicaltherapy_other_status` enum('not_answered') default NULL,
`avg_physicaltherapy_other` varchar(255) default NULL,
`avg_physicaltherapy_other_status` enum('not_answered') default NULL,
`servicetype_speechlangtherapy` enum('yes','no','not_answered') default NULL,
`startdate_speechlangtherapy` text default NULL,
`startdate_speechlangtherapy_status` enum('not_answered') default NULL,
`continue_speechlangtherapy` enum('yes','no','not_answered') default NULL,
`continue_speechlangtherapy_comment` varchar(255) default NULL,
`continue_speechlangtherapy_comment_status` enum('not_answered') default NULL,
`indgrp_speechlangtherapy` enum('individual_','group_','not_answered') default NULL,
`setting_speechlangtherapy_other` varchar(255) default NULL,
`setting_speechlangtherapy_other_status` enum('not_answered') default NULL,
`avg_speechlangtherapy_other` varchar(255) default NULL,
`avg_speechlangtherapy_other_status` enum('not_answered') default NULL,
`startdate_behaviorintervention` text default NULL,
`startdate_behaviorintervention_status` enum('not_answered') default NULL,
`continue_behaviorintervention` enum('yes','no','not_answered') default NULL,
`continue_behaviorintervention_comment` varchar(255) default NULL,
`continue_behaviorintervention_comment_status` enum('not_answered') default NULL,
`indgrp_behaviorintervention` enum('individual_','group_','not_answered') default NULL,
`setting_behaviorintervention_other` varchar(255) default NULL,
`setting_behaviorintervention_other_status` enum('not_answered') default NULL,
`avg_behaviorintervention_other` varchar(255) default NULL,
`avg_behaviorintervention_other_status` enum('not_answered') default NULL,
`servicetype_other` enum('yes','no','not_answered') default NULL,
`startdate_other` text default NULL,
`startdate_other_status` enum('not_answered') default NULL,
`continue_other` enum('yes','no','not_answered') default NULL,
`continue_other_comment` varchar(255) default NULL,
`continue_other_comment_status` enum('not_answered') default NULL,
`indgrp_other` enum('individual_','group_','not_answered') default NULL,
`setting_other` varchar(255) default NULL,
`setting_other_status` enum('not_answered') default NULL,
`avg_other` varchar(255) default NULL,
`avg_other_status` enum('not_answered') default NULL,
`q6_avgperweek_A` text default NULL,
`q6_avgperweek_A_status` enum('not_answered') default NULL,
`q6_avgperweek_B` text default NULL,
`q6_avgperweek_B_status` enum('not_answered') default NULL,
`q7_alt_therapy` enum('yes','no','not_answered') default NULL,
`q7_alt_therapy_other` text default NULL,
`q7_alt_therapy_other_status` enum('not_answered') default NULL,
`q8_medical_pharma` enum('yes','no','not_answered') default NULL,
`q8_medical_pharma_other` text default NULL,
`q8_medical_pharma_other_status` enum('not_answered') default NULL,
`q9_continue_nextyr` enum('yes','no','not_answered') default NULL,
`q10_therapyoptions` varchar(255) default NULL,
`general_comments` text default NULL,
`general_comments_status` enum('not_answered') default NULL,
PRIMARY KEY  (`CommentID`)
);
REPLACE INTO test_names (Test_name, Full_name, Sub_group) VALUES ('BSRC', 'BSRC Treatment form', 1);
