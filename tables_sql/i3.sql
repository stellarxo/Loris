CREATE TABLE `i3` (
`CommentID` varchar(255) NOT NULL default '',

                          `UserID` varchar(255) default NULL,

                          `Examiner` varchar(255) default NULL,

                          `Testdate` timestamp(14) NOT NULL,

                          `Data_entry_completion_status` enum('Incomplete','Complete') NOT NULL default 'Incomplete',
`Date_taken` date default NULL,
`interest1` enum('report_interest','no_more_interests') default NULL,
`interest1_description` text default NULL,
`interest1_description_status` enum('not_answered') default NULL,
`interest1_age_of_onset` enum('1','2','3','4','5','6','7','8','9','10','11','12','13','14','15','16','17','18','19','20','21','22','23','24','25','26','27','28','29','30','31','32','33','34','35','36','37','38','39','40','41','42','43','44','45','46','47','48','NA') default NULL,
`interest1_intensity` enum('1','2','3','4','5','NA') default NULL,
`interest1_peculiarity` enum('1','2','3','4','5','NA') default NULL,
`interest1_persistent` enum('yes','no','unknown','NA') default NULL,
`interest2` enum('report_interest','no_more_interests') default NULL,
`interest2_description` text default NULL,
`interest2_description_status` enum('not_answered') default NULL,
`interest2_age_of_onset` enum('1','2','3','4','5','6','7','8','9','10','11','12','13','14','15','16','17','18','19','20','21','22','23','24','25','26','27','28','29','30','31','32','33','34','35','36','37','38','39','40','41','42','43','44','45','46','47','48','NA') default NULL,
`interest2_intensity` enum('1','2','3','4','5','NA') default NULL,
`interest2_peculiarity` enum('1','2','3','4','5','NA') default NULL,
`interest2_persistent` enum('yes','no','unknown','NA') default NULL,
`interest3` enum('report_interest','no_more_interests') default NULL,
`interest3_description` text default NULL,
`interest3_description_status` enum('not_answered') default NULL,
`interest3_age_of_onset` enum('1','2','3','4','5','6','7','8','9','10','11','12','13','14','15','16','17','18','19','20','21','22','23','24','25','26','27','28','29','30','31','32','33','34','35','36','37','38','39','40','41','42','43','44','45','46','47','48','NA') default NULL,
`interest3_intensity` enum('1','2','3','4','5','NA') default NULL,
`interest3_peculiarity` enum('1','2','3','4','5','NA') default NULL,
`interest3_persistent` enum('yes','no','unknown','NA') default NULL,
`interest4` enum('report_interest','no_more_interests') default NULL,
`interest4_description` text default NULL,
`interest4_description_status` enum('not_answered') default NULL,
`interest4_age_of_onset` enum('1','2','3','4','5','6','7','8','9','10','11','12','13','14','15','16','17','18','19','20','21','22','23','24','25','26','27','28','29','30','31','32','33','34','35','36','37','38','39','40','41','42','43','44','45','46','47','48','NA') default NULL,
`interest4_intensity` enum('1','2','3','4','5','NA') default NULL,
`interest4_peculiarity` enum('1','2','3','4','5','NA') default NULL,
`interest4_persistent` enum('yes','no','unknown','NA') default NULL,
`interest5` enum('report_interest','no_more_interests') default NULL,
`interest5_description` text default NULL,
`interest5_description_status` enum('not_answered') default NULL,
`interest5_age_of_onset` enum('1','2','3','4','5','6','7','8','9','10','11','12','13','14','15','16','17','18','19','20','21','22','23','24','25','26','27','28','29','30','31','32','33','34','35','36','37','38','39','40','41','42','43','44','45','46','47','48','NA') default NULL,
`interest5_intensity` enum('1','2','3','4','5','NA') default NULL,
`interest5_peculiarity` enum('1','2','3','4','5','NA') default NULL,
`interest5_persistent` enum('yes','no','unknown','NA') default NULL,
`interest6` enum('report_interest','no_more_interests') default NULL,
`interest6_description` text default NULL,
`interest6_description_status` enum('not_answered') default NULL,
`interest6_age_of_onset` enum('1','2','3','4','5','6','7','8','9','10','11','12','13','14','15','16','17','18','19','20','21','22','23','24','25','26','27','28','29','30','31','32','33','34','35','36','37','38','39','40','41','42','43','44','45','46','47','48','NA') default NULL,
`interest6_intensity` enum('1','2','3','4','5','NA') default NULL,
`interest6_peculiarity` enum('1','2','3','4','5','NA') default NULL,
`interest6_persistent` enum('yes','no','unknown','NA') default NULL,
`interest7` enum('report_interest','no_more_interests') default NULL,
`interest7_description` text default NULL,
`interest7_description_status` enum('not_answered') default NULL,
`interest7_age_of_onset` enum('1','2','3','4','5','6','7','8','9','10','11','12','13','14','15','16','17','18','19','20','21','22','23','24','25','26','27','28','29','30','31','32','33','34','35','36','37','38','39','40','41','42','43','44','45','46','47','48','NA') default NULL,
`interest7_intensity` enum('1','2','3','4','5','NA') default NULL,
`interest7_peculiarity` enum('1','2','3','4','5','NA') default NULL,
`interest7_persistent` enum('yes','no','unknown','NA') default NULL,
PRIMARY KEY  (`CommentID`)

              ) TYPE=MyISAM;
