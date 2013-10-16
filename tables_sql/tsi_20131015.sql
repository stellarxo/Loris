ALTER TABLE tsi ADD COLUMN lighttherapy_days_proband_status enum('not_answered');
ALTER TABLE tsi ADD COLUMN breastfed_proband_months_status  enum('not_answered');
ALTER TABLE tsi ADD COLUMN breastfed_proband_weeks_status enum('not_answered');
ALTER TABLE tsi ADD COLUMN breastfed_subject_months_status enum('not_answered');
ALTER TABLE tsi ADD COLUMN breastfed_subject_weeks_status enum('not_answered');
ALTER TABLE tsi CHANGE COLUMN lighttherapy_subject lighttherapy_subject enum('yes','no','not_answered');
ALTER TABLE tsi ADD COLUMN lighttherapy_days_subject varchar(255);
ALTER TABLE tsi ADD COLUMN lighttherapy_days_subject_status enum('not_answered');
