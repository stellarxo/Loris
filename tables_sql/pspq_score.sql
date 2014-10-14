CREATE TABLE `pspq_score` (
`CommentID` varchar(255) NOT NULL default '',
`p1_relation_candidate` varchar(255) default NULL,
`p1_age` varchar(255) default NULL,
`p1_gender` varchar(255) default NULL,
`p1_relation_respondent` varchar(255) default NULL,
`p1_informant_gender` varchar(255) default NULL,
`p1_respondent_aloof` varchar(255) default NULL,
`p1_informant_aloof` varchar(255) default NULL,
`p1_best_estimate_aloof` varchar(255) default NULL,
`p1_respondent_pragmatic_language` varchar(255) default NULL,
`p1_informant_pragmatic_language` varchar(255) default NULL,
`p1_best_estimate_pragmatic_language` varchar(255) default NULL,
`p1_respondent_rigid` varchar(255) default NULL,
`p1_informant_rigid` varchar(255) default NULL,
`p1_best_estimate_rigid` varchar(255) default NULL,
`p1_respondent_total` varchar(255) default NULL,
`p1_informant_total` varchar(255) default NULL,
`p1_best_estimate_total` varchar(255) default NULL,
`p2_relation_candidate` varchar(255) default NULL,
`p2_age` varchar(255) default NULL,
`p2_gender` varchar(255) default NULL,
`p2_relation_respondent` varchar(255) default NULL,
`p2_informant_gender` varchar(255) default NULL,
`p2_respondent_aloof` varchar(255) default NULL,
`p2_informant_aloof` varchar(255) default NULL,
`p2_best_estimate_aloof` varchar(255) default NULL,
`p2_respondent_pragmatic_language` varchar(255) default NULL,
`p2_informant_pragmatic_language` varchar(255) default NULL,
`p2_best_estimate_pragmatic_language` varchar(255) default NULL,
`p2_respondent_rigid` varchar(255) default NULL,
`p2_informant_rigid` varchar(255) default NULL,
`p2_best_estimate_rigid` varchar(255) default NULL,
`p2_respondent_total` varchar(255) default NULL,
`p2_informant_total` varchar(255) default NULL,
`p2_best_estimate_total` varchar(255) default NULL,
PRIMARY KEY  (`CommentID`)
              );
INSERT INTO test_names (Test_name, Full_name, Sub_group) VALUES ('pspq_score', 'PSPQ Scoring', 6);
