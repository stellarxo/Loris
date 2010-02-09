ALTER TABLE reliability ADD COLUMN reliability_center_id int(11) NOT NULL DEFAULT 1 AFTER CommentID;
ALTER TABLE aosi_reliability ADD COLUMN reliability_center_id int(11) NOT NULL DEFAULT 1 AFTER CommentID;
ALTER TABLE adi_r_reliability ADD COLUMN reliability_center_id int(11) NOT NULL DEFAULT 1 AFTER CommentID;
ALTER TABLE ados_module1_reliability ADD COLUMN reliability_center_id int(11) NOT NULL DEFAULT 1 AFTER CommentID;
ALTER TABLE ados_module2_reliability ADD COLUMN reliability_center_id int(11) NOT NULL DEFAULT 1 AFTER CommentID;
ALTER TABLE csbs_reliability ADD COLUMN reliability_center_id int(11) NOT NULL DEFAULT 1 AFTER CommentID;


