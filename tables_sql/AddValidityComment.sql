ALTER TABLE adi_r_proband ADD `other_comments` text;
ALTER TABLE adi_r_subject ADD `other_comments` text;
ALTER TABLE ados_module1 ADD `other_comments` text;
ALTER TABLE ados_module2 ADD `other_comments` text;
ALTER TABLE ados_module3 ADD `other_comments` text;
ALTER TABLE ados2_module1 ADD `other_comments` text;
ALTER TABLE ados2_module2 ADD `other_comments` text;
ALTER TABLE ados2_module3 ADD `other_comments` text;
ALTER TABLE edi ADD `other_comments` text;
ALTER TABLE edi2 ADD `other_comments` text;
ALTER TABLE i3 ADD `other_comments` text;
ALTER TABLE intervention_history ADD `other_comments` text;
ALTER TABLE neuro_screen ADD `other_comments` text;
ALTER TABLE EARLI_interview_PART_1 ADD `other_comments` text;
ALTER TABLE CBCL ADD `CommentValidity` text;
ALTER TABLE CBCL ADD `CommentValidity_status` enum('not_answered');
ALTER TABLE ECBQ ADD `CommentValidity` text;
ALTER TABLE ECBQ ADD `CommentValidity_status` enum('not_answered');
ALTER TABLE vineland_proband ADD `other_comments` text;
ALTER TABLE vineland_subject ADD `other_comments` text;

