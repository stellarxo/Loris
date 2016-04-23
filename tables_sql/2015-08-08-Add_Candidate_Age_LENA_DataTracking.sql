--  Add Candidate_Age field to LENA_DataTracking instrument
ALTER TABLE `LENA_DataTrackingForm`
ADD `Candidate_Age` varchar(255) DEFAULT NULL;
