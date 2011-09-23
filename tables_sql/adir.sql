CREATE TABLE `adir` (
`CommentID` varchar(255) NOT NULL default '',

                          `UserID` varchar(255) default NULL,

                          `Examiner` varchar(255) default NULL,

                          `Testdate` timestamp(14) NOT NULL,

                          `Data_entry_completion_status` enum('Incomplete','Complete') NOT NULL default 'Incomplete',
`Date_taken` date default NULL,
`informant_relation` varchar(255) default NULL,
`DoB_proband` date default NULL,
`Total_A1` varchar(255) default NULL,
`Total_A2` varchar(255) default NULL,
`Total_A3` varchar(255) default NULL,
`Total_A4` varchar(255) default NULL,
`A_Total` varchar(255) default NULL,
`Total_B1` varchar(255) default NULL,
`Total_B4` varchar(255) default NULL,
`Total_B2V` varchar(255) default NULL,
`Total_B3V` varchar(255) default NULL,
`BV_Total` varchar(255) default NULL,
`BNV_Total` varchar(255) default NULL,
`Total_C1` varchar(255) default NULL,
`Total_C2` varchar(255) default NULL,
`Total_C3` varchar(255) default NULL,
`Total_C4` varchar(255) default NULL,
`C_Total` varchar(255) default NULL,
PRIMARY KEY  (`CommentID`)

              ) TYPE=MyISAM;
