CREATE TABLE `radiology_review` (
`CommentID` varchar(255) NOT NULL default '',
`UserID` varchar(255) default NULL,
`Examiner` varchar(255) default NULL,
`Data_entry_completion_status` enum('Incomplete','Complete') NOT NULL default 'Incomplete',
`Date_taken` date default NULL,
`Scan_done` enum('No', 'Yes') NULL,
`MRI_date` date NULL,
`Review_date` date NULL,
`Review_results` enum('Normal', 'Abnormal') NULL,
`Incidental_findings` text NULL,
PRIMARY KEY  (`CommentID`));