DROP TABLE IF EXISTS adi_r_initial_reliability;

CREATE TABLE `adi_r_initial_reliability` (
            `site` varchar(256) NOT NULL,
			`rater` varchar(256) NOT NULL,
            `reliable` enum('Yes','No','In progress') default NULL,
		  	`with_umacc_reliable_clinician` boolean,
                        `outside_research_group` enum('Yes','No') default NULL,
		  	`reliability_established_date` date,
		    `administration_status` enum('Yes', 'No', 'Current', 'In Training') default NULL
              ) TYPE=MyISAM;


INSERT INTO adi_r_initial_reliability (site, rater, reliable, with_umacc_reliable_clinician, outside_research_group, reliability_established_date, administration_status) VALUES 
('SEA', 'Annette Estes', "Yes", FALSE, "No", '1998-01-01', "Current"),
('SEA', 'Lindsey Sterling', "Yes", FALSE, "No", '2007-01-01', "No"),
('SEA', 'Karen Burner', "Yes", FALSE, "No", '2006-03-20', "Current"),
('SEA', 'Vanessa Hus', "Yes", FALSE, "No", '2007-01-01', "No"),
('SEA', 'Tanya St. John', "Yes", TRUE, "No", '2008-10-01', "Current"),
('SEA', 'Phil Cali', "Yes", TRUE, "No", '2009-11-06', "Current"),
('UNC', 'Chad Chappell', "Yes", FALSE, "No", '2001-01-01', "Current"),
('UNC', 'Leigh Anne Weisenfeld', "In progress", FALSE, "No", NULL, "Current"),
('UNC', 'Deb Childress', "Yes", FALSE, "No", NULL, "No"),
('UNC', 'Jessica Hetrick', "Yes", FALSE, "No", NULL, "No"),
('SEA', 'Lauren Elder', "Yes", FALSE, "No", '2005', "No"),
('STL', 'Helen Valenza', "Yes", FALSE, "No", '2008-02-05', "Current"),
('STL', 'Patti LaVesser', "Yes", TRUE, "No", '2008-02-17', "No"),
('STL', 'Anna Abbaachi', "Yes", TRUE, "No", '2008-03-01', "Current"),
('PHI', 'Sarah Paterson', "Yes", FALSE, "No", '2008-07-13', NULL),
('PHI', 'Sarah Woldoff', "Yes", FALSE, "No", '2007-01-01', NULL),
('PHI', 'Juhi Pandey', "Yes", FALSE, "No", '2007-01-01', NULL),
('PHI', 'Elizabeth McCaffery', "Yes", TRUE, "No", NULL, NULL),
('PHI', 'Christine Ghilain', "Yes", FALSE, "No", '2010-02-16', NULL),
('PHI', 'Jordana Woodford', "Yes", TRUE, "No", '2009-07-20', NULL),
('PHI', 'Susan Epstein', "Yes", TRUE, "No", '2008-08-01', NULL);

DROP TABLE IF EXISTS figs_initial_reliability;

CREATE TABLE `figs_initial_reliability` (
            `site` varchar(256) NOT NULL,
            `lead_clinician` enum('Yes','No') default NULL,		
			`rater` varchar(256) NOT NULL,
			`date_administration_1` date,
			`date_administration_2` date,
			`date_administration_3` date,
			`date_administration_4` date,
			`tape_sent_date_1` date,
			`tape_sent_date_2` date,
			`tape_sent_date_3` date,
			`tape_sent_date_4` date,
			`feedback_date_1` date,
			`feedback_date_2` date,
			`feedback_date_3` date,
			`feedback_date_4` date,
            `reliable` enum('Yes','No','In progress') default NULL,
		  	`case_ID_1` varchar(256),
		  	`case_ID_2` varchar(256),
		  	`case_ID_3` varchar(256),
		  	`case_ID_4` varchar(256),
		  	`reliability_established_date` date,
		    `administration_status` enum('Yes', 'No', 'Current', 'In Training') default NULL
              ) TYPE=MyISAM;



INSERT INTO figs_initial_reliability (site, rater, lead_clinician, case_ID_1, date_administration_1, tape_sent_date_1, feedback_date_1, case_ID_2, date_administration_2, tape_sent_date_2, feedback_date_2, case_ID_3, date_administration_3, tape_sent_date_3, feedback_date_3, reliable, reliability_established_date, administration_status) VALUES 
('SEA', 'Vanessa Hus'	    , NULL , 'SEA0001', '2007-12-07', '2008-02-13', '2008-3-31' , NULL     , NULL        , NULL        , NULL        , NULL     , NULL        , NULL          , NULL        , "In progress", NULL        , "No"),
('SEA', 'Lindsey Sterling'  , NULL , 'SEA0003', '2008-01-11', '2008-02-13', '2008-4-8'  , NULL     , NULL        , NULL        , NULL        , NULL     , NULL        , NULL          , NULL        , "In progress", NULL        , NULL),
('SEA', 'Karen Burner'      , NULL , 'SEA0004', '2008-03-03', '2008-03-17', '2008-6-9'  , NULL     , NULL        , NULL        , NULL        , NULL     , NULL        , NULL          , NULL        , "In progress", NULL         , NULL),
('SEA', 'Vanessa Rivera'    , NULL ,  NULL    ,  NULL       ,  NULL       ,  NULL       , NULL     , NULL        , NULL        , NULL        , NULL     , NULL        , NULL          , NULL        , "In progress", NULL        , NULL),
('STL', 'Helen Valenza'     , "Yes",  NULL    ,  NULL       ,  NULL       ,  NULL       , NULL     , NULL        , NULL        , NULL        , NULL     , NULL        , NULL          , NULL        , "Yes"        , '2004-10-01', NULL),
('STL', 'Jeanette Mattingly', NULL ,  NULL    ,  NULL       ,  NULL       ,  NULL       , NULL     , NULL        , NULL        , NULL        , NULL     , NULL        , NULL          , NULL        , "Yes"        , '2009-10-06', NULL),
('PHI', 'Amanda Bennett'    , NULL ,  NULL    ,  NULL       ,  NULL       ,  NULL       , NULL     , NULL        , NULL        , NULL        , NULL     , NULL        , NULL          , NULL        , "In progress", NULL        , NULL),
('PHI', 'Sarah Paterson'    , NULL ,  NULL    ,  NULL       ,  NULL       ,  NULL       , NULL     , NULL        , NULL        , NULL        , NULL     , NULL        , NULL          , NULL        , "In progress", NULL        , NULL),
('PHI', 'Isabelle Rostain'  , NULL , 'PHI0056', '2008-10-28',  NULL       , '2009-02-20', 'PHI0080', '2009-01-23', NULL        , '2009-03-06', 'PHI0086', '2009-02-12', '2009-02-12', '2009-03-26', "Yes"        , '2008-10-28', "No"),
('PHI', 'Christine Ghilain' , NULL , 'PHI0090', '2009-02-05', '2009-02-05', '2009-03-31', 'PHI0097', '2009-02-12', '2009-02-12', '2009-04-20', 'PHI0146', '2009-11-09', '2009-11-12', '2009-12-21', "In progress", NULL        , "Yes"),
('PHI', 'Kira Carter'       , NULL , 'PHI0151', '2009-11-10', '2009-11-12', '2009-12-21', 'PHI0153', '2010-02-19', '2010-02-23', NULL        , NULL     , NULL        , NULL          , NULL        , "In progress", NULL        , "Yes"),
('UNC', 'Chad Chappell'     , NULL , NULL     ,  NULL       , NULL        ,  NULL       , NULL     , NULL        , '2009-09-24', NULL        , NULL     , NULL        , NULL          , NULL        , "In progress", NULL        , NULL),
('UNC', 'Jaclyn Anthony'    , NULL , NULL     ,  NULL       ,  NULL       ,  NULL       , NULL     , NULL        , NULL        , NULL        , NULL     , NULL        , NULL          , NULL        , "In progress", NULL        , NULL);


DROP TABLE IF EXISTS aosi_initial_reliability;

CREATE TABLE `aosi_initial_reliability` (
            `site` varchar(256) NOT NULL,
			`rater` varchar(256) NOT NULL,
            `reliable` enum('Yes','No','In progress') default NULL,
            `case_age_mo` integer (3),
            `tape_sent_date_1` date,
            `case_ID_1` varchar(256),
						`tape_sent_date_2` date,
            `case_ID_2` varchar(256),
            `reliability_percentage` integer(3),
		  	`reliability_established_date` date,
				    `administration_status` enum('Yes', 'No', 'Current', 'In Training') default NULL
              ) TYPE=MyISAM;

INSERT INTO aosi_initial_reliability (site, rater, reliable, tape_sent_date_1, case_ID_1, case_age_mo, tape_sent_date_2, case_ID_2, reliability_percentage, reliability_established_date, administration_status) VALUES 
('SEA', 'Lindsey Sterling',"Yes", '2008-2-18', 'SEA0001', '6', NULL, NULL, '79', NULL, "No"),
('SEA', 'Lindsey Sterling', "In progress", NULL, NULL, '12', NULL, NULL, NULL, NULL, "No"),
('SEA', 'Karen Burner',"Yes", '2008-2-18', 'EC016', '8', NULL, NULL, '100', '2008-1-24', "Current"),
('SEA', 'Karen Burner', "Yes", '2008-10-3', 'SEA0004', '12', NULL, NULL, '84', '2008-8-20', "Current"),
('SEA', 'Vanessa Hus',"Yes", '2008-4-16', 'SEA0014', '6', NULL, NULL, '83', '2008-4-4', "No"),
('SEA', 'Vanessa Hus', "Yes", '2008-10-14', 'SEA0014', '12', NULL, NULL, '89', '2008-10-10', "No"),
('SEA', 'Shanna Alvarez',"Yes", '2009-07-16', 'SEA0100', '6', NULL, NULL, NULL, '2009-07-16', "Current"),
('SEA', 'Shanna Alvarez',"In progress", '2010-01', 'SEAXXXX', '12', NULL, NULL, NULL, NULL, "In Training"),
('PHI', 'Sarah Paterson', "Yes", NULL, 'PHI0002', '6', NULL, NULL, '79', '2008-9-10', NULL),
('PHI', 'Sarah Paterson', "Yes", NULL, 'PHI0015', '12', NULL, NULL, '95', '2008-11-25', NULL),
('PHI', 'Christine Ghilain', "In progress", '2009-11-04', NULL, '6', NULL, NULL, NULL, NULL, NULL),
('PHI', 'Christine Ghilain', "In progress", '2009-11-04', NULL, '12', NULL, NULL, NULL, NULL, NULL),
('UNC', 'Chad Chappell', "In progress", '2009-08-21', 'UNC0005', '6', NULL, NULL, NULL, NULL, NULL),
('UNC', 'Chad Chappell', "In progress", '2009-08-21', 'UNC0003', '12', NULL, NULL, NULL, NULL, NULL),
('UNC', 'Leigh Anne Weisenfeld', "In progress", NULL, NULL, '6', NULL, NULL, NULL, NULL, NULL),
('UNC', 'Leigh Anne Weisenfeld', "In progress", NULL, NULL, '12', NULL, NULL, NULL, NULL, NULL),
('STL', 'Kelly Botteron', "In progress", '2009-12-01', NULL, '6', '2010-02-03', NULL, NULL, NULL, NULL),
('STL', 'Kelly Botteron', "In progress", '2009-12-01', NULL, '12', '2010-02-03', NULL, NULL, NULL, NULL),
('STL', 'Lisa Flake', "In progress", '2009-08-19', 'STL0091', '6', NULL, NULL, NULL, NULL, NULL),
('STL', 'Lisa Flake', "In progress", '2010-02-15', 'STL0112', '12', NULL, NULL, NULL, NULL, NULL),
('STL', 'Jeanette Mattingly', "In progress", NULL, NULL, '6', NULL, NULL, NULL, NULL, NULL),
('STL', 'Jeanette Mattingly', "In progress", '2009-08-14', 'STL0041', '12', NULL, NULL, NULL, NULL, NULL);


DROP TABLE IF EXISTS csbs_initial_reliability;

CREATE TABLE `csbs_initial_reliability` (
            `site` varchar(256) NOT NULL,
			`rater` varchar(256) NOT NULL,
			`type` varchar(256) NOT NULL,
            `reliable` enum('Yes','No','In progress','Not applicable') default NULL,
            `reliability_percentage` integer(3),
            `examiner_coder_status` varchar(256) NOT NULL,
		  	`reliability_established_date` date,
				    `administration_status` enum('Yes', 'No', 'Current', 'In Training') default NULL
              ) TYPE=MyISAM;
             

INSERT INTO csbs_initial_reliability (site, rater, type, reliable, reliability_established_date, examiner_coder_status, administration_status) VALUES 
('SEA', 'Karen Burner', "training kit", "Yes", '2008-04-09', NULL, "Current"),
('SEA', 'Karen Burner', "UW Gold Standard", "Yes", '2008-04-09', NULL, "Current"),
('SEA', 'Vanessa Hus', "training kit", "Yes", '2008-04-09', NULL, "No"),
('SEA', 'Vanessa Hus', "UW Gold Standard", "Yes", '2008-04-09', NULL, "No"),
('SEA', 'Tanya St. John', "training kit", "Not applicable", NULL, 'Examiner', "Current"),
('SEA', 'Shanna Alvarez', "training kit", "Yes", '2009-10-23', NULL, "Current"),
('SEA', 'Shanna Alvarez', "UW Gold Standard", "Yes", '2009-10-23', NULL, "Current"),
('PHI', 'Sarah Paterson', "training kit", "Yes", '2008-04-01', NULL, NULL),
('PHI', 'Sarah Paterson', "UW Gold Standard", "Yes", '2008-09-28', NULL, NULL),
('PHI', 'Jordana Woodford', "training kit", "Yes", '2005-06-01', NULL, NULL),
('PHI', 'Jordana Woodford', "UW Gold Standard", "In progress", NULL, NULL, NULL),
('UNC', 'Chad Chappell', "training kit", "Yes", '2009-03-01', NULL, "Current"),
('UNC', 'Chad Chappell', "UW Gold Standard", "Yes", NULL, NULL, NULL),
('UNC', 'Leigh Anne Weisenfeld', "training kit", "Not applicable", NULL, 'Examiner', "Current"),
('UNC', 'Leigh Anne Weisenfeld', "UW Gold Standard", "Not applicable", NULL, 'Examiner', "Current"),
('STL', 'Lisa Flake', "training kit", "Yes", '2007-02-09', NULL, "Current"),
('STL', 'Lisa Flake', "UW Gold Standard", "Yes", '2009-08-03', NULL, "Current"),
('STL', 'Brittany Perez', "training kit", "Yes", '2009-06-03', NULL, "Current"),
('STL', 'Brittany Perez', "UW Gold Standard", "Yes", '2009-08-05', NULL, "Current"),
('STL', 'Jeanette Mattingly', "training kit", "Yes", '2009-01-07', NULL, "Current"),
('STL', 'Jeanette Mattingly', "UW Gold Standard", "Yes", '2009-08-07', NULL, "Current");


DROP TABLE IF EXISTS ados_initial_reliability;

CREATE TABLE `ados_initial_reliability` (
            `site` varchar(256) NOT NULL,
			`rater` varchar(256) NOT NULL,
            `reliable` enum('Yes','No','In progress') default NULL,
		  	`with_umacc_reliable_clinician` boolean,
		  	`reliability_established_date` date,
		    `administration_status` enum('Yes', 'No', 'Current', 'In Training') default NULL
              ) TYPE=MyISAM;


INSERT INTO ados_initial_reliability (site, rater, reliable, with_umacc_reliable_clinician, reliability_established_date, administration_status) VALUES 
('SEA', 'Annette Estes', "Yes", FALSE, '1998-01-01', "No"),
('SEA', 'Karen Burner', "Yes", FALSE, '2004-09-22', "Current"),
('SEA', 'Vanessa Hus', "Yes", FALSE, '2007-01-01', "No"),
('SEA', 'Tanya St. John', "Yes", TRUE, '2008-12-01', "Current"),
('PHI', 'Sarah Woldoff', "Yes", FALSE, '2007-01-01', NULL),
('PHI', 'Juhi Pandey', "Yes", FALSE, '2007-01-01', NULL),
('UNC', 'Chad Chappell', "Yes", FALSE, '2001-01-01', "Current"),
('UNC', 'Leigh Anne Weisenfeld', "In progress", FALSE, NULL, "Current"),
('UNC', 'Deb Childress', "Yes", FALSE, NULL, "No"),
('STL', 'Patti LaVesser', "In progress", FALSE, NULL, "No"),
('STL', 'Anna Abbaachi', "Yes", FALSE, '2009-12-23', "Current");


DROP TABLE IF EXISTS mullen_initial_reliability;

CREATE TABLE `mullen_initial_reliability` (
            `site` varchar(256) NOT NULL,
			`rater` varchar(256) NOT NULL,
            `reliable` enum('Yes','No','In progress') default NULL,
            `lead_clinician` enum('Yes','No') default NULL,
		  	`reliability_established_date` date,
				    `administration_status` enum('Yes', 'No', 'Current', 'In Training') default NULL
              ) TYPE=MyISAM;


INSERT INTO mullen_initial_reliability (site, rater, lead_clinician, reliable, reliability_established_date, administration_status) VALUES 
('SEA', 'Karen Burner', "Yes", "Yes", '2007-03-01', "Current"),
('SEA', 'Vanessa Hus', NULL, "Yes", '2007-03-01', "No"),
('SEA', 'Tanya St. John', "Yes", "Yes", '2008-10-01', "Current"),
('SEA', 'Shanna Alvarez', NULL, "Yes", '2009-09-16', "Current"),
('SEA', 'Lindsey Sterling', NULL, "Yes", '2007-03-01', "No"),
('PHI', 'Sarah Woldoff', "Yes", "Yes", NULL, NULL),
('PHI', 'Juhi Pandey', "Yes", "Yes", NULL, NULL),
('PHI', 'Sarah Paterson', "Yes", "Yes", NULL, NULL),
('PHI', 'Susan Epstein', "Yes", "Yes", NULL, NULL),
('PHI', 'Jordana Woodford', "Yes", "Yes", NULL, NULL),
('UNC', 'Chad Chappell', "Yes", "Yes", NULL, "Current"),
('UNC', 'Jessica Hetrick', NULL, "Yes", NULL, "No"),
('UNC', 'Leigh Anne Weisenfeld', NULL, "Yes", NULL, "Current"),
('STL', 'Casey Babb', NULL, "Yes", NULL, "Current"),
('STL', 'Patti LaVesser', NULL, "In progress", NULL, "No"),
('STL', 'Jeanette Mattingly', NULL, "Yes", NULL, "Current");



