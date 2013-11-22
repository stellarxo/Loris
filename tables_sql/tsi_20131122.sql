ALTER TABLE tsi DROP COLUMN relative_mri;
ALTER TABLE tsi_followup DROP COLUMN relative_mri;
ALTER TABLE tsi ADD COLUMN relative_mr enum('yes','no','not_answered') AFTER genetic_conditions_proband;
ALTER TABLE tsi_followup ADD COLUMN relative_mr enum('yes','no','not_answered') AFTER genetic_conditions_proband;
UPDATE tsi SET relative_schizophrenia = null, relative_bipolar = null, relative_psychosis = null WHERE relative_schizophrenia = 'yes'; 
UPDATE tsi SET relative_schizophrenia = NULL, relative_bipolar = NULL, relative_psychosis = NULL WHERE relative_schizophrenia = 'no'; 
UPDATE tsi_followup SET relative_schizophrenia = NULL, relative_bipolar = NULL, relative_psychosis = NULL WHERE relative_schizophrenia='yes'; 
UPDATE tsi_followup SET relative_schizophrenia = NULL, relative_bipolar = NULL, relative_psychosis = NULL WHERE relative_schizophrenia='no'; 
