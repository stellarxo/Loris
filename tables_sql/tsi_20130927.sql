ALTER TABLE tsi ADD COLUMN is_infant_adopted enum('yes','no','not_answered');
ALTER TABLE tsi ADD COLUMN is_infant_twin enum('yes','no','not_answered');
ALTER TABLE tsi ADD COLUMN premature_birth_proband enum('yes','no','not_answered');
ALTER TABLE tsi ADD COLUMN gestation_proband varchar(255);
ALTER TABLE tsi ADD COLUMN gestation_proband_stautus  enum('not_answered');
ALTER TABLE tsi ADD COLUMN birthweight_proband_lb  enum('0','1','2','3','4','5','6','7','8','9','10','11','12','13','14','15'); 
ALTER TABLE tsi ADD COLUMN birthweight_proband_oz enum('0','1','2','3','4','5','6','7','8','9','10','11','12','13','14','15');
ALTER TABLE tsi ADD COLUMN birthweight_proband_lb_status enum('not_answered');
ALTER TABLE tsi ADD COLUMN complications_birth_proband enum('yes','no','not_answered');
ALTER TABLE tsi ADD COLUMN breastfed_proband enum('yes','no','not_answered');
ALTER TABLE tsi ADD COLUMN breastfed_duration_proband varchar(255);
ALTER TABLE tsi ADD COLUMN breastfed_duration_proband_status enum('not_answered');
ALTER TABLE tsi ADD COLUMN medication_in_breastfeed_proband enum('yes','no','not_answered');
ALTER TABLE tsi ADD COLUMN substance_breastfed_proband varchar(255);
ALTER TABLE tsi ADD COLUMN substance_breastfed_proband_status enum('not_answered');
ALTER TABLE tsi ADD COLUMN substance_breastfed_amount_proband varchar(255);
ALTER TABLE tsi ADD COLUMN substance_breastfed_amount_proband_status enum('not_answered');
ALTER TABLE tsi ADD COLUMN time_exposure_breastfed_proband varchar(255);
ALTER TABLE tsi ADD COLUMN time_exposure_breastfed_proband_status enum('not_answered');
ALTER TABLE tsi ADD COLUMN pregnancy_complication_subject enum('yes','no','not_answered');
ALTER TABLE tsi ADD COLUMN jaundice_subject enum('yes','no','not_answered');
ALTER TABLE tsi ADD COLUMN lightherapy_subject varchar(255);
ALTER TABLE tsi ADD COLUMN lightherapy_subject_status enum('not_answered');
ALTER TABLE tsi ADD COLUMN breastfed_subject enum('yes','no','not_answered');
ALTER TABLE tsi ADD COLUMN breastfed_duration_subject varchar(255);
ALTER TABLE tsi ADD COLUMN breastfed_duration_subject_status enum('not_answered');
ALTER TABLE tsi ADD COLUMN medication_in_breastfeed_subject enum('yes','no','not_answered');
ALTER TABLE tsi ADD COLUMN substance_breastfed_subject varchar(255); 
ALTER TABLE tsi ADD COLUMN substance_breastfed_subject_status enum('not_answered');
ALTER TABLE tsi ADD COLUMN substance_breastfed_amount_subject varchar(255);
ALTER TABLE tsi ADD COLUMN substance_breastfed_amount_subject_status enum('not_answered');
ALTER TABLE tsi ADD COLUMN time_exposure_breastfed_subject varchar(255);
ALTER TABLE tsi ADD COLUMN time_exposure_breastfed_subject_status enum('not_answered');
ALTER TABLE tsi CHANGE COLUMN med_his_q_9_anethesia_problems med_his_q_9_anethesia_notes varchar(255);
ALTER TABLE tsi ADD COLUMN med_his_q_9_anethesia_notes_status enum('not_answered');
ALTER TABLE tsi CHANGE COLUMN med_his_q_9_anethesia_problems med_his_q_9_anethesia_notes varchar(255); 
ALTER TABLE tsi ADD COLUMN med_his_q_9_anethesia_notes_status enum('not_answered');
ALTER TABLE tsi CHANGE COLUMN med_his_q_8_brain_MRI_results med_his_q_8_brain_MRI_notes varchar(255);
ALTER TABLE tsi ADD COLUMN med_his_q_8_brain_MRI_notes_status enum('not_answered');
ALTER TABLE tsi ADD COLUMN med_his_q_8_brain_MRI_results enum('typical','atypical','not_answered'); 
ALTER TABLE tsi ADD COLUMN med_his_q_9_anethesia_problems enum('yes','no','not_answered');
UPDATE tsi SET neurological_problems_proband = seizures_disorders WHERE seizures_disorders='yes';
ALTER TABLE tsi DROP COLUMN med_his_q_9_anethesia_problems_status;
ALTER TABLE tsi DROP COLUMN med_his_q_8_brain_MRI_results_status;
ALTER TABLE tsi DROP COLUMN seizures_disorders;
