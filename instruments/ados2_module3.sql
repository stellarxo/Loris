CREATE TABLE `ados2_module3` (
        `CommentID` varchar(255) NOT NULL DEFAULT '',
        `UserID` varchar(255) DEFAULT NULL,
        `Examiner` varchar(255) DEFAULT NULL,
        `Testdate` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
        `Data_entry_completion_status` enum('Incomplete','Complete') NOT NULL DEFAULT 'Incomplete',
        `Date_taken` date DEFAULT NULL,
        `Candidate_Age` varchar(255) DEFAULT NULL,
        `Window_Difference` varchar(255) DEFAULT NULL,
        `social_affect_total` varchar(255) DEFAULT NULL,
        `restricted_repetitive_behavior_total` varchar(255) DEFAULT NULL,
        `social_affect_restricted_repetitive_behavior_total` varchar(255) DEFAULT NULL,
        `ADOS_classification` varchar(255) DEFAULT NULL,
        `a1` enum('0','1','2','3','not_answered') DEFAULT NULL,
        `a2` enum('0','1','2','7','not_answered') DEFAULT NULL,
        `a3` enum('0','1','2','3','not_answered') DEFAULT NULL,
        `a4` enum('0','1','2','3','not_answered') DEFAULT NULL,
        `a5` enum('0','1','2','not_answered') DEFAULT NULL,
        `a6` enum('0','1','2','3','not_answered') DEFAULT NULL,
        `a7` enum('0','1','2','3','not_answered') DEFAULT NULL,
        `a8` enum('0','1','2','3','not_answered') DEFAULT NULL,
        `a9` enum('0','1','2','3','8','not_answered') DEFAULT NULL,
        `b1` enum('0','2','not_answered') DEFAULT NULL,
        `b2` enum('0','1','2','not_answered') DEFAULT NULL,
        `b3` enum('0','1','2','7','8','not_answered') DEFAULT NULL,
        `b4` enum('0','1','2','not_answered') DEFAULT NULL,
        `b5` enum('0','1','2','not_answered') DEFAULT NULL,
        `b6` enum('0','1','2','3','not_answered') DEFAULT NULL,
        `b7` enum('0','1','2','3','not_answered') DEFAULT NULL,
        `b8` enum('0','1','2','3','7','not_answered') DEFAULT NULL,
        `b9` enum('0','1','2','3','not_answered') DEFAULT NULL,
        `b10` enum('0','1','2','3','not_answered') DEFAULT NULL,
        `b11` enum('0','1','2','3','not_answered') DEFAULT NULL,
        `c1` enum('0','1','2','3','not_answered') DEFAULT NULL,
        `d1` enum('0','1','2','3','not_answered') DEFAULT NULL,
        `d1_specify` text,
        `d1_specify_status` enum('not_answered') DEFAULT NULL,
        `d2` enum('0','1','2','3','not_answered') DEFAULT NULL,
        `d2_specify` text,
        `d2_specify_status` enum('not_answered') DEFAULT NULL,
        `d3` enum('0','1','2','not_answered') DEFAULT NULL,
        `d4` enum('0','1','2','3','not_answered') DEFAULT NULL,
        `d5` enum('0','1','2','not_answered') DEFAULT NULL,
        `d5_specify` text,
        `d5_specify_status` enum('not_answered') DEFAULT NULL,
        `e1` enum('0','1','2','3','7','not_answered') DEFAULT NULL,
        `e2` enum('0','1','2','3','not_answered') DEFAULT NULL,
        `e3` enum('0','1','2','not_answered') DEFAULT NULL,
        `a4_weighted` varchar(255) DEFAULT NULL,
        `a7_weighted` varchar(255) DEFAULT NULL,
        `a8_weighted` varchar(255) DEFAULT NULL,
        `a9_weighted` varchar(255) DEFAULT NULL,
        `b1_weighted` varchar(255) DEFAULT NULL,
        `b2_weighted` varchar(255) DEFAULT NULL,
        `b4_weighted` varchar(255) DEFAULT NULL,
        `b7_weighted` varchar(255) DEFAULT NULL,
        `b8_weighted` varchar(255) DEFAULT NULL,
        `b9_weighted` varchar(255) DEFAULT NULL,
        `b10_weighted` varchar(255) DEFAULT NULL,
        `d1_weighted` varchar(255) DEFAULT NULL,
        `d2_weighted` varchar(255) DEFAULT NULL,
        `d4_weighted` varchar(255) DEFAULT NULL,
        `social_affect_gotham_weighted` varchar(255) DEFAULT NULL,
        `restricted_repetitive_gotham_weighted` varchar(255) DEFAULT NULL,
        `gotham_weighted_score` varchar(255) DEFAULT NULL,
        `severity_score_lookup` varchar(255) DEFAULT NULL,
        PRIMARY KEY (`CommentID`)
    ) ENGINE=MyISAM DEFAULT CHARSET=latin1;
