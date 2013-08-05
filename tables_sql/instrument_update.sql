ALTER TABLE aims DROP q37_weightshift_unusuatinedsit;
ALTER TABLE aims ADD COLUMN q37_weightshift_unusustainedsit enum('credited','observed','not_observed','above_ceiling','not_answered');
ALTER TABLE BSRC DROP avg_behaviorintervention_other_status;
