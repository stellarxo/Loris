ALTER TABLE pspq_1 ADD COLUMN informant_confidence enum('extremely_confident','very_confident','moderately_confident','little_confident','not_confident');
ALTER TABLE pspq_2 ADD COLUMN informant_confidence enum('extremely_confident','very_confident','moderately_confident','little_confident','not_confident');
ALTER TABLE pspq_1 CHANGE COLUMN datecompleted_respondent Date_taken date;
ALTER TABLE pspq_2 CHANGE COLUMN datecompleted_respondent Date_taken date;
ALTER TABLE pspq_1 DROP COLUMN datecompleted_informant;
ALTER TABLE pspq_2 DROP COLUMN datecompleted_informant;
