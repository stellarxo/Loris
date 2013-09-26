CREATE TABLE `LENA_DataTrackingForm` (
`CommentID` varchar(255) NOT NULL default '',
                          `UserID` varchar(255) default NULL,
                          `Examiner` varchar(255) default NULL,
                          `Testdate` timestamp NOT NULL,
                          `Data_entry_completion_status` enum('Incomplete','Complete') NOT NULL default 'Incomplete',
`datecompleted` date default NULL,
`family_participate` enum('yes','no') default NULL,
`reasonsdecline` varchar(255) default NULL,
`number_session` enum('1','2','3','4') default NULL,
`duration_session1` enum('full_day','less_16hrs','notused_del') default NULL,
`comments_session1` text default NULL,
`comments_session1_status` enum('not_answered') default NULL,
`duration_session2` enum('full_day','less_16hrs','notused_del') default NULL,
`comments_session2` text default NULL,
`comments_session2_status` enum('not_answered') default NULL,
`duration_session3` enum('full_day','less_16hrs','notused_del') default NULL,
`comments_session3` text default NULL,
`comments_session3_status` enum('not_answered') default NULL,
`duration_session4` enum('full_day','less_16hrs','notused_del') default NULL,
`comments_session4` text default NULL,
`File_name` varchar(256) default NULL,
`File_type` varchar(256) default NULL,
`Data_dir` varchar(256) default NULL,
PRIMARY KEY  (`CommentID`)
              );
ALTER TABLE LENA_DataTrackingForm ADD COLUMN Type_1 varchar(20);
ALTER TABLE LENA_DataTrackingForm ADD COLUMN DLP_1  varchar(20);
ALTER TABLE LENA_DataTrackingForm ADD COLUMN ProcessingFile_1 varchar(70);
ALTER TABLE LENA_DataTrackingForm ADD COLUMN Timestamp_1 DATETIME;
ALTER TABLE LENA_DataTrackingForm ADD COLUMN Duration_1 varchar(8);
ALTER TABLE LENA_DataTrackingForm ADD COLUMN Meaningful_1 varchar(8);
ALTER TABLE LENA_DataTrackingForm ADD COLUMN Distant_1 varchar(8);
ALTER TABLE LENA_DataTrackingForm ADD COLUMN TV_1 varchar(8);
ALTER TABLE LENA_DataTrackingForm ADD COLUMN TV_Pct_1 varchar(5);
ALTER TABLE LENA_DataTrackingForm ADD COLUMN Noise_1 varchar(8);
ALTER TABLE LENA_DataTrackingForm ADD COLUMN Silence_1 varchar(8);
ALTER TABLE LENA_DataTrackingForm ADD COLUMN AWC_Actual_1 varchar(5); 
ALTER TABLE LENA_DataTrackingForm ADD COLUMN CTC_Actual_1 varchar(3); 
ALTER TABLE LENA_DataTrackingForm ADD COLUMN CVC_Actual_1 varchar(3);
ALTER TABLE LENA_DataTrackingForm ADD COLUMN AVA_StdScore decimal(3,2);
ALTER TABLE LENA_DataTrackingForm ADD COLUMN AVA_StdScore_Pct varchar(5);
