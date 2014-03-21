ALTER TABLE med_records_proband ADD COLUMN Lastupdated_growthchart_date date;
ALTER TABLE med_records_proband ADD COLUMN Lastupdated_growthchart_date_status enum('not_answered') ;
ALTER TABLE med_records_proband ADD COLUMN Lastupdated_growthchart2_date date;
ALTER TABLE med_records_proband ADD COLUMN Lastupdated_growthchart2_date_status enum('not_answered') ;
ALTER TABLE med_records_proband ADD COLUMN other_genetic_result_completed_specify varchar(255);
ALTER TABLE med_records_proband ADD COLUMN other_genetic_result_completed_specify_status enum('not_answered');
