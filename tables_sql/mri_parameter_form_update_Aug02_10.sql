ALTER TABLE mri_parameter_form ADD COLUMN Scanner_Type enum('Hospital', 'Research', 'Other');
ALTER TABLE mri_parameter_form ADD COLUMN Scanner_Type_other varchar(255);

ALTER TABLE mri_parameter_form ADD COLUMN BOLD_Scan_done enum('Complete', 'Partial', 'not_answered');
ALTER TABLE mri_parameter_form ADD COLUMN BOLD_number_attempts integer;

ALTER TABLE mri_parameter_form ADD COLUMN BOLD_Scan_done_date date;
ALTER TABLE mri_parameter_form ADD COLUMN BOLD_Scan_done_date_status enum('not_answered');
ALTER TABLE mri_parameter_form ADD COLUMN BOLD_Comments text;
ALTER TABLE mri_parameter_form ADD COLUMN BOLD_Comments_status enum('not_answered');

ALTER TABLE mri_parameter_form ADD COLUMN Spectroscopy_Scan_done enum('Complete', 'Partial', 'not_answered');
ALTER TABLE mri_parameter_form ADD COLUMN Spectroscopy_number_attempts integer;

ALTER TABLE mri_parameter_form ADD COLUMN Spectroscopy_Scan_done_date date;
ALTER TABLE mri_parameter_form ADD COLUMN Spectroscopy_Scan_done_date_status enum('not_answered');
ALTER TABLE mri_parameter_form ADD COLUMN Spectroscopy_Comments text;
ALTER TABLE mri_parameter_form ADD COLUMN Spectroscopy_Comments_status enum('not_answered');
ALTER TABLE mri_parameter_form ADD COLUMN Spectroscopy_long_echo_acquired enum('acquired', 'not_acquired', 'not_answered');
ALTER TABLE mri_parameter_form ADD COLUMN Spectroscopy_short_echo_acquired enum('acquired', 'not_acquired', 'not_answered');
ALTER TABLE mri_parameter_form ADD COLUMN Spectroscopy_water_scan_acquired enum('acquired', 'not_acquired', 'not_answered');

