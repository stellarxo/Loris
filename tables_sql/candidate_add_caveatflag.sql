ALTER TABLE candidate ADD COLUMN flagged_caveatemptor enum('true','false') DEFAULT 'false';
ALTER TABLE candidate ADD COLUMN flagged_reason int(6);
ALTER TABLE candidate ADD COLUMN flagged_other varchar(255);
ALTER TABLE candidate ADD CoLUMN flagged_other_status enum ('not_answered');
CREATE TABLE caveat_options (ID INT, Description varchar(255), PRIMARY KEY (ID) );
INSERT INTO caveat_options VALUES (1,'Older Sibling diagnosed with autism. Child moved from LR to HR'),(2,'Family met exclusionary criteria after enrollment in study'), (3,'Other');
