ALTER TABLE med_records_24 ADD not_completed enum('non-asd','other') DEFAULT NULL;
ALTER TABLE med_records_24 ADD not_completed_other_specify varchar(255) DEFAULT NULL;
ALTER TABLE med_records_24 ADD not_completed_other_specify_status enum('not_answered') DEFAULT NULL;
ALTER TABLE med_records_24 ADD hearing_screening_date date DEFAULT NULL;
ALTER TABLE med_records_24 ADD hearing_screening_date_status enum('not_answered') DEFAULT NULL;
ALTER TABLE med_records_24 ADD vra varchar(255) DEFAULT NULL;
ALTER TABLE med_records_24 ADD oae varchar(255) DEFAULT NULL;
ALTER TABLE med_records_24 ADD tympanometry varchar(255) DEFAULT NULL;
ALTER TABLE med_records_24 ADD other_method varchar(255) DEFAULT NULL;
ALTER TABLE med_records_24 ADD other_method_specify varchar(255) DEFAULT NULL;
ALTER TABLE med_records_24 ADD other_method_specify_status enum('not_answered') DEFAULT NULL;
ALTER TABLE med_records_24 ADD test_results enum('normal_hearing','temporary_hearing_difficulty','equivocal_evaluation_results','permanent_abnormal_hearing','not_answered') DEFAULT NULL;
ALTER TABLE med_records_24 ADD test_results_ear enum('left_ear','right_ear','bilateral','not_answered') DEFAULT NULL;
ALTER TABLE med_records_24 ADD test_results_severity enum('partial','total','not_answered') DEFAULT NULL;
ALTER TABLE med_records_24 ADD equivocal_evaluation_results_specify text;
ALTER TABLE med_records_24 ADD equivocal_evaluation_results_specify_status enum('not_answered') DEFAULT NULL;
INSERT INTO instrument_subtests (Test_name,Subtest_name, Description,Order_number) VALUES ('med_records_24','med_records_24_page4','Audiology Report',4);
