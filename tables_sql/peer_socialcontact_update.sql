ALTER TABLE peer_socialcontact MODIFY COLUMN q25_school_numdays_perweek enum('0','1','2','3','4','5','6','7'); 
ALTER TABLE peer_socialcontact MODIFY COLUMN q31_childcare_numdays_perweek enum('0','1','2','3','4','5','6','7'); 
ALTER TABLE peer_socialcontact MODIFY COLUMN q26_school_numhrs_perday enum('0','1','2','3','4','5','6','7','8','9','10','11','12','13','14','15','16','17','18','19','20','21','22','23','24'); 
ALTER TABLE peer_socialcontact MODIFY COLUMN q32_childcare_numhrs_perday enum('0','1','2','3','4','5','6','7','8','9','10','11','12','13','14','15','16','17','18','19','20','21','22','23','24');
ALTER TABLE peer_socialcontact ADD COLUMN q34_numchildren_specialneeds varchar(255);
UPDATE peer_socialcontact SET q34_numchildren_specialneeds = q35_numchildren_specialneeds;
ALTER TABLE peer_socialcontact DROP q35_numchildren_specialneeds;
