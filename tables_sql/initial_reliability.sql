DROP TABLE IF EXISTS adi_r_initial_reliability;

CREATE TABLE `adi_r_initial_reliability` (
            `site` varchar(256) NOT NULL,
			`rater` varchar(256) NOT NULL,
            `reliable` enum('Yes','No','In progress') default NULL,
		  	`with_umacc_reliable_clinician` boolean,
		  	`reliability_established_date` date
              ) TYPE=MyISAM;


INSERT INTO adi_r_initial_reliability (site, rater, reliable, with_umacc_reliable_clinician, reliability_established_date) VALUES 
('SEA', 'Annette Estes', "Yes", FALSE, '1998-01-01'),
('SEA', 'Lindsey Sterling', "Yes", FALSE, '2007-01-01'),
('SEA', 'Karen Burner', "Yes", FALSE, '2006-03-20'),
('SEA', 'Vanessa Hus', "Yes", FALSE, '2007-01-01'),
('SEA', 'Tanya St. John', "Yes", TRUE, '2008-10-01'),
('UNC', 'Chad Chappell', "Yes", FALSE, '2001-01-01'),
('UNC', 'Leigh Anne Weisenfeld', "In progress", FALSE, NULL),
('UNC', 'Deb Childress', "Yes", FALSE, NULL),
('UNC', 'Jessica Hetrick', "In progress", FALSE, NULL),
('???', 'Lauren Elder', "In progress", FALSE, NULL),
('STL', 'Helen Valenza', "Yes", FALSE, '2008-02-05'),
('STL', 'Patti LaVesser', "Yes", TRUE, '2008-02-17'),
('STL', 'Lisa Flake', "In progress", FALSE, NULL),
('STL', 'Anna Abbaachi', "Yes", TRUE, '2008-03-01'),
('PHI', 'Sarah Paterson', "Yes", FALSE, '2008-07-13'),
('PHI', 'Sarah Woldoff', "Yes", FALSE, '2007-01-01'),
('PHI', 'Juhi Pandey', "Yes", FALSE, '2007-01-01'),
('PHI', 'Elizabeth McCaffery', "Yes", TRUE, NULL),
('PHI', 'Christine Ghilain', "In progress", FALSE, NULL),
('PHI', 'Jordana Woodford', "Yes", TRUE, '2009-07-20'),
('PHI', 'Susan Epstein', "Yes", TRUE, '2008-08-01');

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
		  	`reliability_established_date` date
              ) TYPE=MyISAM;



INSERT INTO figs_initial_reliability (site, rater, lead_clinician, case_ID_1, date_administration_1, tape_sent_date_1, feedback_date_1, case_ID_2, date_administration_2, tape_sent_date_2, feedback_date_2, case_ID_3, date_administration_3, tape_sent_date_3, feedback_date_3, reliable, reliability_established_date) VALUES 
('SEA', 'Vanessa Hus', NULL , 'SEA0001', '2007-12-07', '2008-02-13', '2008-3-31' , NULL     , NULL        , NULL        , NULL        , NULL     , NULL       , NULL        , NULL       , "In progress", NULL),
('SEA', 'Lindsey Sterling'  , NULL , 'SEA0003', '2008-01-11', '2008-02-13', '2008-4-8'  , NULL     , NULL        , NULL        , NULL        , NULL     , NULL       , NULL        , NULL       , "In progress", NULL),
('SEA', 'Karen Burner'    , NULL , 'SEA0004', '2008-03-03', '2008-03-17', '2008-6-9'  , NULL     , NULL        , NULL        , NULL        , NULL     , NULL       , NULL        , NULL       , "In progress", NULL),
('SEA', 'Vanessa Rivera', NULL ,  NULL    ,  NULL       ,  NULL       ,  NULL       , NULL     , NULL        , NULL        , NULL        , NULL     , NULL       , NULL        , NULL       , "In progress", NULL),
('SEA', 'Annette Estes' , NULL ,  NULL    ,  NULL       ,  NULL       ,  NULL       , NULL     , NULL        , NULL        , NULL        , NULL     , NULL       , NULL        , NULL       , "In progress", NULL),
('STL', 'Helen Valenza'    , "Yes",  NULL    ,  NULL       ,  NULL       ,  NULL       , NULL     , NULL        , NULL        , NULL        , NULL     , NULL       , NULL        , NULL       , "Yes"        , '2004-10-01'),
('STL', 'Jeanette Mattingly' , NULL ,  NULL    ,  NULL       ,  NULL       ,  NULL       , NULL     , NULL        , NULL        , NULL        , NULL     , NULL       , NULL        , NULL       , "In progress", NULL),
('PHI', 'Amanda Bennett' , NULL ,  NULL    ,  NULL       ,  NULL       ,  NULL       , NULL     , NULL        , NULL        , NULL        , NULL     , NULL       , NULL        , NULL       , "In progress", NULL),
('PHI', 'Sarah Paterson' , NULL ,  NULL    ,  NULL       ,  NULL       ,  NULL       , NULL     , NULL        , NULL        , NULL        , NULL     , NULL       , NULL        , NULL       , "In progress", NULL),
('PHI', 'Isabelle Rostain' , NULL , 'PHI0056', '2008-10-28',  NULL       , '2009-02-20', 'PHI0080', '2009-01-23', NULL        , '2009-03-06', 'PHI0086', '2009-2-12', '2009-02-12', '2009-3-26', "Yes"        , '2008-10-28'),
('PHI', 'Christine Ghilain', NULL , 'PHI0090', '2009-02-05', '2009-02-05', '2009-03-31', 'PHI0097', '2009-02-12', '2009-02-12', '2009-04-20', NULL     , NULL       , NULL        , NULL       , "In progress", NULL),
('UNC', 'Chad Chappell'     , NULL , NULL    ,  NULL        , '2009-09-24',  NULL       , NULL     , NULL        , '2009-09-24', NULL        , NULL     , NULL       , NULL        , NULL       , "In progress", NULL),
('UNC', 'Jaclyn Anthony'   , NULL , NULL    ,  NULL        ,  NULL      ,  NULL       , NULL     , NULL        , NULL      , NULL        , NULL     , NULL       , NULL        , NULL       , "In progress", NULL);


DROP TABLE IF EXISTS aosi_initial_reliability;

CREATE TABLE `aosi_initial_reliability` (
            `site` varchar(256) NOT NULL,
			`rater` varchar(256) NOT NULL,
            `reliable` enum('Yes','No','In progress') default NULL,
            `tape_sent_date` date,
            `case_ID` varchar(256),
            `case_age_mo` integer (3),
            `reliability_percentage` integer(3),
		  	`reliability_established_date` date
              ) TYPE=MyISAM;

INSERT INTO aosi_initial_reliability (site, rater, reliable, tape_sent_date, case_ID, case_age_mo, reliability_percentage, reliability_established_date) VALUES 
('SEA', 'Lindsey Sterling',"Yes", '2008-2-18', 'SEA0001', '6', '79', NULL),
('SEA', 'Lindsey Sterling', "In progress", NULL, NULL, '12', NULL, NULL),
('SEA', 'Karen Burner',"Yes", '2008-2-18', 'EC016', '8', '100', '2008-1-24'),
('SEA', 'Karen Burner', "Yes", '2008-10-3', 'SEA0004', '12', '84', '2008-8-20'),
('SEA', 'Vanessa Hus',"Yes", '2008-4-16', 'SEA0014', '6', '83', '2008-4-4'),
('SEA', 'Vanessa Hus', "Yes", '2008-10-14', 'SEA0014', '12', '89', '2008-10-10'),
('SEA', 'Shanna Alvarez',"In progress", '2009-07-16', 'SEA0100', '6', NULL, NULL),
('SEA', 'Shanna Alvarez',"In progress", NULL, NULL, '12', NULL, NULL),
('SEA', 'Annette Estes',"In progress", NULL, NULL, '6', NULL, NULL),
('SEA', 'Annette Estes',"In progress", '2008-10-14', NULL, '12', NULL, NULL),
('PHI', 'Sarah Paterson', "Yes", NULL, 'PHI0002', '6', '79', '2008-9-10'),
('PHI', 'Sarah Paterson', "Yes", NULL, 'PHI0015', '12', '95', '2008-11-25'),
('PHI', 'Christine Ghilain', "In progress", NULL, NULL, '6', NULL, NULL),
('PHI', 'Christine Ghilain', "In progress", NULL, NULL, '12', NULL, NULL),
('UNC', 'Chad Chappell', "In progress", '2009-08-21', 'UNC0005', '6', NULL, NULL),
('UNC', 'Chad Chappell', "In progress", '2009-08-21', 'UNC0003', '12', NULL, NULL),
('UNC', 'Leigh Anne Weisenfeld', "In progress", NULL, NULL, '6', NULL, NULL),
('UNC', 'Leigh Anne Weisenfeld', "In progress", NULL, NULL, '12', NULL, NULL),
('STL', 'Kelly Botteron', "In progress", NULL, NULL, '6', NULL, NULL),
('STL', 'Kelly Botteron', "In progress", NULL, NULL, '12', NULL, NULL),
('STL', 'Lisa Flake', "In progress", '2009-08-19', 'STL0091', '6', NULL, NULL),
('STL', 'Lisa Flake', "In progress", NULL, NULL, '12', NULL, NULL),
('STL', 'Jeanette Mattingly', "In progress", NULL, NULL, '6', NULL, NULL),
('STL', 'Jeanette Mattingly', "In progress", '2009-08-14', 'STL0041', '12', NULL, NULL);


DROP TABLE IF EXISTS csbs_initial_reliability;

CREATE TABLE `csbs_initial_reliability` (
            `site` varchar(256) NOT NULL,
			`rater` varchar(256) NOT NULL,
			`type` varchar(256) NOT NULL,
            `reliable` enum('Yes','No','In progress') default NULL,
            `reliability_percentage` integer(3),
            `examiner_coder_status` varchar(256) NOT NULL,
		  	`reliability_established_date` date
              ) TYPE=MyISAM;
             

INSERT INTO csbs_initial_reliability (site, rater, type, reliable, reliability_established_date, examiner_coder_status) VALUES 
('SEA', 'Karen Burner', "training kit", "Yes", '2008-4-9', NULL),
('SEA', 'Karen Burner', "UW Gold Standard", "In progress", NULL, NULL),
('SEA', 'Vanessa Hus', "training kit", "Yes", '2008-4-9', NULL),
('SEA', 'Vanessa Hus', "UW Gold Standard", "In progress", NULL, NULL),
('SEA', 'Tanya St. John', "training kit", "In progress", NULL, 'Examiner'),
('SEA', 'Tanya St. John', "UW Gold Standard", "In progress", NULL, 'Examiner'),
('PHI', 'Sarah Paterson', "training kit", "Yes", '2008-04-01', NULL),
('PHI', 'Sarah Paterson', "UW Gold Standard", "Yes", '2008-09-28', NULL),
('PHI', 'Jordana Woodford', "training kit", "Yes", '2005-06-01', NULL),
('PHI', 'Jordana Woodford', "UW Gold Standard", "In progress", NULL, NULL),
('UNC', 'Chad Chappell', "training kit", "Yes", '2009-03-01', NULL),
('UNC', 'Chad Chappell', "UW Gold Standard", "Yes", NULL, NULL),
('STL', 'Lisa Flake', "training kit", "Yes", '2007-02-09', NULL),
('STL', 'Lisa Flake', "UW Gold Standard", "In progress", NULL, NULL),
('STL', 'Brittany Perez', "training kit", "Yes", '2009-06-03', NULL),
('STL', 'Brittany Perez', "UW Gold Standard", "In progress", NULL, NULL),
('STL', 'Jeanette Mattingly', "training kit", "Yes", '2009-01-07', NULL),
('STL', 'Jeanette Mattingly', "UW Gold Standard", "In progress", NULL, NULL);


DROP TABLE IF EXISTS ados_initial_reliability;

CREATE TABLE `ados_initial_reliability` (
            `site` varchar(256) NOT NULL,
			`rater` varchar(256) NOT NULL,
            `reliable` enum('Yes','No','In progress') default NULL,
		  	`with_umacc_reliable_clinician` boolean,
		  	`reliability_established_date` date
              ) TYPE=MyISAM;


INSERT INTO ados_initial_reliability (site, rater, reliable, with_umacc_reliable_clinician, reliability_established_date) VALUES 
('SEA', 'Annette Estes', "Yes", FALSE, '1998-01-01'),
('SEA', 'Karen Burner', "Yes", FALSE, '2004-09-22'),
('SEA', 'Vanessa Hus', "Yes", FALSE, '2007-01-01'),
('SEA', 'Tanya St. John', "Yes", TRUE, '2008-12-01'),
('PHI', 'Sarah Woldoff', "Yes", FALSE, '2007-01-01'),
('PHI', 'Juhi Pandey', "Yes", FALSE, '2007-01-01'),
('UNC', 'Chad Chappell', "Yes", FALSE, '2001-01-01'),
('UNC', 'Leigh Anne Weisenfeld', "In progress", FALSE, NULL),
('UNC', 'Deb Childress', "Yes", FALSE, NULL),
('STL', 'Patti LaVesser', "In progress", FALSE, NULL),
('STL', 'Lisa Flake', "In progress", FALSE, NULL),
('STL', 'Anna Abbaachi', "In progress", FALSE, NULL);


DROP TABLE IF EXISTS mullen_initial_reliability;

CREATE TABLE `mullen_initial_reliability` (
            `site` varchar(256) NOT NULL,
			`rater` varchar(256) NOT NULL,
            `reliable` enum('Yes','No','In progress') default NULL,
            `lead_clinician` enum('Yes','No') default NULL,
		  	`reliability_established_date` date		
              ) TYPE=MyISAM;


INSERT INTO mullen_initial_reliability (site, rater, lead_clinician, reliable, reliability_established_date) VALUES 
('SEA', 'Karen Burner', "Yes", "Yes", '2007-03-01'),
('SEA', 'Vanessa Hus', NULL, "Yes", '2007-03-01'),
('SEA', 'Tanya St. John', "Yes", "Yes", '2008-10-01'),
('SEA', 'Shanna Alvarez', NULL, "Yes", '2009-09-16'),
('SEA', 'Lindsey Sterling', NULL, "Yes", '2007-03-01'),
('PHI', 'Sarah Woldoff', "Yes", "Yes", NULL),
('PHI', 'Juhi Pandey', "Yes", "Yes", NULL),
('PHI', 'Sarah Paterson', "Yes", "Yes", NULL),
('PHI', 'Susan Epstein', "Yes", "Yes", NULL),
('PHI', 'Jordana Woodford', "Yes", "Yes", NULL),
('UNC', 'Chad Chappell', NULL, "Yes", NULL),
('UNC', 'Jessica Hetrick', NULL, "In progress", NULL),
('UNC', 'Leigh Anne Weisenfeld', NULL, "Yes", NULL),
('STL', 'Casey Babb', NULL, "Yes", NULL),
('STL', 'Lisa Flake', NULL, "In progress", NULL),
('STL', 'Patti LaVesser', NULL, "In progress", NULL),
('STL', 'Jeanette Mattingly', NULL, "Yes", NULL);



