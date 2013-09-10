ALTER TABLE FamilyEnvironmentScales ADD COLUMN q82_spontaneous_discussion enum('true','false','not_answered');
UPDATE FamilyEnvironmentScales SET q82_spontaneous_discussion = q82_spontaneous_discussionl; 
ALTER TABLE FamilyEnvironmentScales DROP COLUMN q82_spontaneous_discussionl; 
