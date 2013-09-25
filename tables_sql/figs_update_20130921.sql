ALTER TABLE figs_year3_relatives ADD COLUMN Psychosis_Q4_NoDepression_temp enum('0','1','9','NA');
UPDATE figs_year3_relatives SET Psychosis_Q4_NoDepression_temp = '0' WHERE Psychosis_Q4_NoDepression = 'No';
UPDATE figs_year3_relatives SET Psychosis_Q4_NoDepression_temp = '1' WHERE Psychosis_Q4_NoDepression = 'Yes';
UPDATE figs_year3_relatives SET Psychosis_Q4_NoDepression_temp = '9' WHERE Psychosis_Q4_NoDepression = 'Unk';
UPDATE figs_year3_relatives SET Psychosis_Q4_NoDepression_temp = 'NA' WHERE Psychosis_Q4_NoDepression = 'NA';
ALTER TABLE figs_year3_relatives DROP COLUMN Psychosis_Q4_NoDepression;
ALTER TABLE figs_year3_relatives CHANGE COLUMN Psychosis_Q4_NoDepression_temp Psychosis_Q4_NoDepression enum('0','1','9','NA');
