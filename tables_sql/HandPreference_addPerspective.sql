ALTER TABLE HandPreference ADD COLUMN administration_perspective enum('child_perspective','examiner_perspective');
UPDATE HandPreference SET administration_perspective='examiner_perspective' WHERE Date_taken < '2014-09-03';
