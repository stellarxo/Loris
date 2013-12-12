CREATE TABLE `participant_status_history` (
        `ID` int(10) unsigned NOT NULL AUTO_INCREMENT,
        `CandID` int(6) NOT NULL DEFAULT '0',
        `entry_staff` varchar(255) DEFAULT NULL,
        `data_entry_date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
        `participant_status` int(11) DEFAULT NULL,
        `reason_specify` varchar(255),
        `reason_specify_status` enum('not_answered') DEFAULT NULL,
        `participant_subOptions` int(11) DEFAULT NULL,
        PRIMARY KEY (`ID`),
        UNIQUE KEY `ID` (`ID`)
        );
