CREATE TABLE `aosi` (
`CommentID` varchar(255) NOT NULL default '',

                          `UserID` varchar(255) default NULL,

                          `Examiner` varchar(255) default NULL,

                          `Testdate` timestamp(14) NOT NULL,

                          `Data_entry_completion_status` enum('Incomplete','Complete') NOT NULL default 'Incomplete',
`Date_taken` date default NULL,
`examiner_location` enum('examiner','in_room_observer','behind_mirror','videotape','not_answered') default NULL,
`total_score_1_18` varchar(255) default NULL,
`number_of_markers` varchar(255) default NULL,
PRIMARY KEY  (`CommentID`)

              ) TYPE=MyISAM;
