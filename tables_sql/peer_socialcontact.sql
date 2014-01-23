CREATE TABLE `peer_socialcontact` (
`CommentID` varchar(255) NOT NULL default '',

                          `UserID` varchar(255) default NULL,

                          `Examiner` varchar(255) default NULL,

                          `Testdate` timestamp NOT NULL,

                          `Data_entry_completion_status` enum('Incomplete','Complete') NOT NULL default 'Incomplete',
`datecompleted` date default NULL,
`respondent` enum('mother','father','other') default NULL,
`respondent_other` varchar(255) default NULL,
`respondent_other_status` enum('not_answered') default NULL,
`peer_initials_1` varchar(255) default NULL,
`peer_initials_1_status` enum('not_answered') default NULL,
`peer_initials_2` varchar(255) default NULL,
`peer_initials_2_status` enum('not_answered') default NULL,
`peer_initials_3` varchar(255) default NULL,
`peer_initials_3_status` enum('not_answered') default NULL,
`peer_initials_4` varchar(255) default NULL,
`peer_initials_4_status` enum('not_answered') default NULL,
`peer_initials_5` varchar(255) default NULL,
`peer_initials_5_status` enum('not_answered') default NULL,
`1_2` enum('yes','no') default NULL,
`1_3` enum('yes','no') default NULL,
`1_4` enum('yes','no') default NULL,
`1_5` enum('yes','no') default NULL,
`2_3` enum('yes','no') default NULL,
`2_4` enum('yes','no') default NULL,
`2_5` enum('yes','no') default NULL,
`3_4` enum('yes','no') default NULL,
`3_5` enum('yes','no') default NULL,
`4_5` enum('yes','no') default NULL,
PRIMARY KEY  (`CommentID`)

              );
