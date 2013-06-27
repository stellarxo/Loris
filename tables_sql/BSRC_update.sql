ALTER TABLE BSRC ADD COLUMN setting_physicaltherapy enum('office/clinic','home','daycare/preschool','other','not_answered');
ALTER TABLE BSRC ADD COLUMN setting_speechlangtherapy enum('office/clinic','home','daycare/preschool','other','not_answered');
ALTER TABLE BSRC ADD COLUMN setting_behaviorintervention enum('office/clinic','home','daycare/preschool','other','not_answered');
ALTER TABLE BSRC ADD COLUMN setting_otheroptions enum('office/clinic','home','daycare/preschool','other','not_answered');
ALTER TABLE BSRC CHANGE avg_occupationaltherapy avg_occupationaltherapy decimal(10,0);
ALTER TABLE BSRC CHANGE avg_physicaltherapy_other avg_physicaltherapy_other decimal(10,0);
ALTER TABLE BSRC CHANGE avg_speechlangtherapy_other avg_speechlangtherapy_other decimal(10,0);
ALTER TABLE BSRC CHANGE avg_other avg_other decimal(10,0);
