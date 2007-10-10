CREATE TABLE `measurements` (
`CommentID` varchar(255) NOT NULL default '',

                          `UserID` varchar(255) default NULL,

                          `Examiner` varchar(255) default NULL,

                          `Testdate` timestamp(14) NOT NULL,

                          `Data_entry_completion_status` enum('Incomplete','Complete') NOT NULL default 'Incomplete',
`Date_taken` date default NULL,
`head_cirfumference1` varchar(255) default NULL,
`head_cirfumference1_status` enum('not_answered') default NULL,
`head_cirfumference2` varchar(255) default NULL,
`head_cirfumference2_status` enum('not_answered') default NULL,
`length1` varchar(255) default NULL,
`length1_status` enum('not_answered') default NULL,
`length2` varchar(255) default NULL,
`length2_status` enum('not_answered') default NULL,
`measurement_method` enum('lying_down','standing_up','not_answered') default NULL,
`weight1` varchar(255) default NULL,
`weight1_status` enum('not_answered') default NULL,
`weight2` varchar(255) default NULL,
`weight2_status` enum('not_answered') default NULL,
PRIMARY KEY  (`CommentID`)

              ) TYPE=MyISAM;
