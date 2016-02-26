-- Add informant to child relationship field and text field for "other" option
ALTER TABLE pspq_1 ADD informant_child_other varchar(255);
ALTER TABLE pspq_2 ADD informant_child_other varchar(255);
ALTER TABLE pspq_1 ADD informant_child enum('mother','father','stepmother','stepfather','other');
ALTER TABLE pspq_2 ADD informant_child enum('mother','father','stepmother','stepfather','other');