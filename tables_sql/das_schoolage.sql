CREATE TABLE `das_schoolage` (
`CommentID` varchar(255) NOT NULL default '',

                          `UserID` varchar(255) default NULL,

                          `Examiner` varchar(255) default NULL,

                          `Testdate` timestamp NOT NULL,

                          `Data_entry_completion_status` enum('Incomplete','Complete') NOT NULL default 'Incomplete',
`Date_taken` date default NULL,
`Candidate_Age` varchar(255) default NULL,
`Window_Difference` varchar(255) default NULL,
`Total_1` varchar(255) default NULL,
`Total_2` varchar(255) default NULL,
`Total_3` varchar(255) default NULL,
`Total_4` varchar(255) default NULL,
`Total_5` varchar(255) default NULL,
`Total_6` varchar(255) default NULL,
`Total_7` varchar(255) default NULL,
`Total_8` varchar(255) default NULL,
`other_comments` text default NULL,
PRIMARY KEY  (`CommentID`)

              );
