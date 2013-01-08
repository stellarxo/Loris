CREATE TABLE `certification` (
        `certID` int(10) unsigned NOT NULL AUTO_INCREMENT,
        `examinerID` int(10) unsigned NOT NULL DEFAULT '0',
        `date_cert` date DEFAULT NULL,
        `visit_label` varchar(255) DEFAULT NULL,
        `testID` varchar(255) NOT NULL DEFAULT '',
        `pass` enum('not_certified','in_training','certified') DEFAULT NULL,
        `comment` varchar(255) DEFAULT NULL,
        PRIMARY KEY (`certID`,`testID`)
        )

CREATE TABLE `certification_history` (
        `id` int(11) NOT NULL AUTO_INCREMENT,
        `col` varchar(255) NOT NULL DEFAULT '',
        `old` text,
        `old_date` date DEFAULT NULL,
        `new` text,
        `new_date` date DEFAULT NULL,
        `primaryCols` varchar(255) DEFAULT 'certID',
        `primaryVals` text,
        `testID` int(3) DEFAULT NULL,
        `visit_label` varchar(255) DEFAULT NULL,
        `changeDate` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
        `userID` varchar(255) NOT NULL DEFAULT '',
        `type` char(1) DEFAULT NULL,
        PRIMARY KEY (`id`)
        )


