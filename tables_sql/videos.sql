CREATE TABLE `videos` (
							`record_id` integer(11) NOT NULL AUTO_INCREMENT,
							`PSCID` varchar(255) NOT NULL default '',
							`Instrument` varchar(255) default NULL,
							`visitLabel` varchar(255) default NULL,
								`Date_uploaded` timestamp(14) NOT NULL,
								`File_type` varchar(255) default NULL,
								`Data_dir` varchar(255) default NULL,
								`File_name` varchar(255) default NULL,
								`uploaded_by` varchar(255) default NULL,
								`For_site` integer(2) NULL,
								`comments`  text default NULL,
								PRIMARY KEY  (`record_id`)

              ) TYPE=MyISAM;
