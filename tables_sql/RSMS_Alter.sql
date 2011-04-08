ALTER TABLE RSMS CHANGE COLUMN q1_rate_body_1 q1_rate_body_1 enum('0','1','2','3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17', '18', '19', '20', 'NA');
ALTER TABLE RSMS CHANGE COLUMN q1_rate_body_2 q1_rate_body_2 enum('0','1','2','3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17', '18', '19', '20', 'NA');
ALTER TABLE RSMS CHANGE COLUMN q1_rate_body_3 q1_rate_body_3 enum('0','1','2','3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17', '18', '19', '20', 'NA');
ALTER TABLE RSMS CHANGE q1_rate_body_4 q1_rate_body_4 enum('0','1','2','3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17', '18', '19', '20', 'NA');
ALTER TABLE RSMS CHANGE q1_rate_body_5 q1_rate_body_5 enum('0','1','2','3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17', '18', '19', '20', 'NA');
ALTER TABLE RSMS CHANGE q1_rate_body_6 q1_rate_body_6 enum('0','1','2','3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17', '18', '19', '20', 'NA');

ALTER TABLE RSMS CHANGE COLUMN q3_rate_object_1 q3_rate_object_1 enum('0','1','2','3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17', '18', '19', '20', 'NA');
ALTER TABLE RSMS CHANGE COLUMN q3_rate_object_2 q3_rate_object_2 enum('0','1','2','3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17', '18', '19', '20', 'NA');
ALTER TABLE RSMS CHANGE COLUMN q3_rate_object_3 q3_rate_object_3 enum('0','1','2','3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17', '18', '19', '20', 'NA');
ALTER TABLE RSMS CHANGE q3_rate_object_4 q3_rate_object_4 enum('0','1','2','3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17', '18', '19', '20', 'NA');
ALTER TABLE RSMS CHANGE q3_rate_object_5 q3_rate_object_5 enum('0','1','2','3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17', '18', '19', '20', 'NA');
ALTER TABLE RSMS CHANGE q3_rate_object_6 q3_rate_object_6 enum('0','1','2','3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17', '18', '19', '20', 'NA');


ALTER TABLE RSMS ADD COLUMN q1_score_weighted varchar(255) AFTER q1_score;
UPDATE RSMS SET q1_score_weighted=q1_score;
UPDATE RSMS SET q1_score=null;

ALTER TABLE RSMS ADD COLUMN q3_score_weighted varchar(255) AFTER q3_score;
UPDATE RSMS SET q3_score_weighted=q3_score;
UPDATE RSMS SET q3_score=null;

ALTER TABLE RSMS ADD COLUMN q1_3_score varchar(255);

ALTER TABLE RSMS ADD COLUMN q2_inv_body_flaps_number enum('0','1','2','3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17', '18', '19', '20','21','22','23','24','25','26','27','28','29','30','31','32','33','34','35','36','37','38','39','40', 'NA') AFTER q2_inv_body_flaps;
ALTER TABLE RSMS ADD COLUMN q2_inv_body_pats_number enum('0','1','2','3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17', '18', '19', '20','21','22','23','24','25','26','27','28','29','30','31','32','33','34','35','36','37','38','39','40', 'NA') AFTER q2_inv_body_pats;
ALTER TABLE RSMS ADD COLUMN q2_inv_body_rubs_number enum('0','1','2','3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17', '18', '19', '20','21','22','23','24','25','26','27','28','29','30','31','32','33','34','35','36','37','38','39','40', 'NA') AFTER q2_inv_body_rubs;
ALTER TABLE RSMS ADD COLUMN q2_inv_body_stiffens_number enum('0','1','2','3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17', '18', '19', '20','21','22','23','24','25','26','27','28','29','30','31','32','33','34','35','36','37','38','39','40', 'NA') AFTER q2_inv_body_stiffens;

ALTER TABLE RSMS ADD COLUMN q4a_inv_object_swipes_number enum('0','1','2','3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17', '18', '19', '20','21','22','23','24','25','26','27','28','29','30','31','32','33','34','35','36','37','38','39','40', 'NA') AFTER q4a_inv_object_swipes;
ALTER TABLE RSMS ADD COLUMN q4a_inv_object_rubs_number enum('0','1','2','3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17', '18', '19', '20','21','22','23','24','25','26','27','28','29','30','31','32','33','34','35','36','37','38','39','40', 'NA') AFTER q4a_inv_object_rubs;
ALTER TABLE RSMS ADD COLUMN q4a_inv_object_rolls_number enum('0','1','2','3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17', '18', '19', '20','21','22','23','24','25','26','27','28','29','30','31','32','33','34','35','36','37','38','39','40', 'NA') AFTER q4a_inv_object_rolls;
ALTER TABLE RSMS ADD COLUMN q4a_inv_object_rocks_number enum('0','1','2','3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17', '18', '19', '20','21','22','23','24','25','26','27','28','29','30','31','32','33','34','35','36','37','38','39','40', 'NA') AFTER q4a_inv_object_rocks;
ALTER TABLE RSMS ADD COLUMN q4a_inv_object_spins_number enum('0','1','2','3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17', '18', '19', '20','21','22','23','24','25','26','27','28','29','30','31','32','33','34','35','36','37','38','39','40', 'NA') AFTER q4a_inv_object_spins;

ALTER TABLE RSMS ADD COLUMN q4b_inv_object_collects_number enum('0','1','2','3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17', '18', '19', '20','21','22','23','24','25','26','27','28','29','30','31','32','33','34','35','36','37','38','39','40', 'NA') AFTER q4b_inv_object_collects;
ALTER TABLE RSMS ADD COLUMN q4b_inv_object_moves_number enum('0','1','2','3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17', '18', '19', '20','21','22','23','24','25','26','27','28','29','30','31','32','33','34','35','36','37','38','39','40', 'NA') AFTER q4b_inv_object_moves;
ALTER TABLE RSMS ADD COLUMN q4b_inv_object_lines_number enum('0','1','2','3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17', '18', '19', '20','21','22','23','24','25','26','27','28','29','30','31','32','33','34','35','36','37','38','39','40', 'NA') AFTER q4b_inv_object_lines;
ALTER TABLE RSMS ADD COLUMN q4b_inv_object_clutches_number enum('0','1','2','3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17', '18', '19', '20','21','22','23','24','25','26','27','28','29','30','31','32','33','34','35','36','37','38','39','40', 'NA') AFTER q4b_inv_object_clutches;

alter table RSMS add column `total_time_assessment` enum('5','6','7','8','9','10','11','12','13','14','15','16','17','18','19','20','21','22','23','24','25','26','27','28','29','30','31','32','33','34','35','36','37','38','39','40','41','42','43','44','45','46','47','48','49','50','51','52','53','54','55','56','57','58','59','60','NA') AFTER `Window_Difference`;
ALTER TABLE RSMS add column `total_play_time` enum('1','2','3','4','5','6','7','8','9','10','11','12','13','14','15','NA') after `total_time_assessment`;
ALTER TABLE RSMS add column `toys_displayed` enum('half','full') after `total_play_time`;

