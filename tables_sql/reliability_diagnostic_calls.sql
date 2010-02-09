DROP TABLE IF EXISTS reliability_diagnostic_calls;

CREATE TABLE `reliability_diagnostic_calls` (
            `date_of_review` date,
			`caseID_1` varchar(256),
            `caseID_2` varchar(256),
            `caseID_3` varchar(256)
              ) TYPE=MyISAM;


INSERT INTO reliability_diagnostic_calls (date_of_review, caseID_1, caseID_2) VALUES 
("2009-08-27", "SEA0001", NULL),
("2009-09-10", "UNC0147", NULL),
("2009-10-08", "PHI0005", NULL);
