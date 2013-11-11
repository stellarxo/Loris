ALTER TABLE participant_status_options ADD COLUMN parentID int(10);
ALTER TABLE participant_status ADD COLUMN participant_subOptions int(10) AFTER participant_statusID;
ALTER TABLE participant_status DROP COLUMN withdrawal_reasons;
ALTER TABLE participant_status DROP COLUMN withdrawal_reasons_other_specify;
ALTER TABLE participant_status DROP COLUMN withdrawal_reasons_other_specify_status;
