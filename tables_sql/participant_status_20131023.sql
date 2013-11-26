ALTER TABLE participant_status_options ADD COLUMN parentID int(10);
ALTER TABLE participant_status ADD COLUMN participant_suboptions int(10) AFTER participant_status;
ALTER TABLE participant_status DROP COLUMN withdrawal_reasons;
ALTER TABLE participant_status DROP COLUMN withdrawal_reasons_other_specify;
ALTER TABLE participant_status DROP COLUMN withdrawal_reasons_other_specify_status;
DELETE FROM participant_status_options;
INSERT INTO `participant_status_options` VALUES (1,'Active',0,NULL),(2,'Refused/Not Enrolled',0,NULL),(3,'Ineligible',0,NULL),(4,'Excluded',0,NULL),(5,'Inactive',1,NULL),(6,'Incomplete',1,NULL),(7,'Complete',0,NULL),(8,'Unsure',NULL,5),(9,'Requiring Further Investigation',NULL,5),(10,'Not Responding',NULL,5),(11,'Death',NULL,6),(12,'Lost to Followup',NULL,6);
ALTER TABLE pariticpant_status DROP COLUMN reason_specify;
ALTER TABLE pariticpant_status DROP COLUMN reason_specify_status;
