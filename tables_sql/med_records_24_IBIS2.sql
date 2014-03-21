ALTER TABLE med_records_24 ADD COLUMN other_genetic_result_completed_specify varchar(255);
ALTER TABLE med_records_24 ADD COLUMN other_genetic_result_completed_specify_status enum('not_answered');
ALTER TABLE med_records_24 ADD COLUMN Lastupdated_growthchart_date date;
ALTER TABLE med_records_24 ADD COLUMN Lastupdated_growthchart_date_status enum('not_answered') ;
ALTER TABLE med_records_24 ADD COLUMN Lastupdated_growthchart_date2 date;
ALTER TABLE med_records_24 ADD COLUMN Lastupdated_growthchart_date2_status enum('not_answered') ;
