ALTER TABLE tsi ADD COLUMN pregnancy_exposure_subject enum('yes','no','not_answered');
ALTER TABLE tsi ADD COLUMN pregnancy_substance_subject enum('yes','no','not_answered');
ALTER TABLE tsi ADD COLUMN pregnancy_substance_subject_status enum('not_answered');
ALTER TABLE tsi ADD COLUMN pregnancy_substance_amount_subject enum('yes','no','not_answered');
ALTER TABLE tsi ADD COLUMN pregnancy_substance_amount_subject_status enum('not_answered');
ALTER TABLE tsi ADD COLUMN pregnancy_time_exposure_subject enum('yes','no','not_answered');
ALTER TABLE tsi ADD COLUMN pregnancy_time_exposure_subject_status enum('not_answered');
