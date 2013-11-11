ALTER TABLE candidate ADD COLUMN flagged_caveatemptor enum('true','false') DEFAULT 'false';
ALTER TABLE candidate ADD COLUMN flagged_info enum('older_sibling_autism','family_excluded','other');
ALTER TABLE candidate ADD COLUMN flagged_other varchar(255);
ALTER TABLE candidate ADD CoLUMN flagged_other_status enum ('not_answered');
