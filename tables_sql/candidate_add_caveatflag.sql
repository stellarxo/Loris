ALTER TABLE candidate ADD COLUMN flagged_caveatemptor enum('true','false');
ALTER TABLE candidate ADD COLUMN flagged_info enum('older_sibling_autism' , 'family_excluded');
