ALTER TABLE CBCL DROP COLUMN q100_otherproblems;
ALTER TABLE CBCL DROP COLUMN q100_otherproblems_status;
ALTER TABLE CBCL ADD COLUMN q100_otherproblems_1 text;
ALTER TABLE CBCL ADD COLUMN q100_otherproblems_1_status enum('not_answered');
ALTER TABLE CBCL ADD COLUMN q100_otherproblems_1_option enum('0_not_true','1_somewhat_or_sometimes_true','2_very_true_or_often_true','not_answered');
ALTER TABLE CBCL ADD COLUMN q100_otherproblems_1_parent enum('yes','no');
ALTER TABLE CBCL ADD COLUMN q100_otherproblems_2 text;
ALTER TABLE CBCL ADD COLUMN q100_otherproblems_2_status enum('not_answered');
ALTER TABLE CBCL ADD COLUMN q100_otherproblems_2_option enum('0_not_true','1_somewhat_or_sometimes_true','2_very_true_or_often_true','not_answered' );
ALTER TABLE CBCL ADD COLUMN q100_otherproblems_2_parent enum('yes','no');
ALTER TABLE CBCL ADD COLUMN q100_otherproblems_3 text;
ALTER TABLE CBCL ADD COLUMN q100_otherproblems_3_status enum('not_answered');
ALTER TABLE CBCL ADD COLUMN q100_otherproblems_3_option enum('0_not_true','1_somewhat_or_sometimes_true','2_very_true_or_often_true','not_answered' );
ALTER TABLE CBCL ADD COLUMN q100_otherproblems_3_parent enum('yes','no');

