ALTER TABLE adi_r_proband ADD COLUMN 2012alg_range_concern varchar(255) DEFAULT NULL;
ALTER TABLE adi_r_proband ADD COLUMN 2012alg_research_diag varchar(255) DEFAULT NULL;
ALTER TABLE adi_r_proband ADD COLUMN 2012alg_clinical_diag varchar(255) DEFAULT NULL;
UPDATE adi_r_proband SET 2012alg_range_concern = 2011alg_range_concern;
UPDATE adi_r_proband SET 2012alg_research_diag = 2011alg_research_diag;
UPDATE adi_r_proband SET 2012alg_clinical_diag = 2011alg_clinical_diag;
ALTER TABLE adi_r_proband DROP 2011alg_research_diag;
ALTER TABLE adi_r_proband DROP 2011alg_clinical_diag;
ALTER TABLE adi_r_proband DROP 2011alg_range_concern;
ALTER TABLE adi_r_subject ADD COLUMN 2012alg_range_concern varchar(255) DEFAULT NULL;
ALTER TABLE adi_r_subject ADD COLUMN 2012alg_research_diag varchar(255) DEFAULT NULL;
ALTER TABLE adi_r_subject ADD COLUMN 2012alg_clinical_diag varchar(255) DEFAULT NULL;
UPDATE adi_r_subject SET 2012alg_range_concern = 2011alg_range_concern;
UPDATE adi_r_subject SET 2012alg_research_diag = 2011alg_research_diag;
UPDATE adi_r_subject SET 2012alg_clinical_diag = 2011alg_clinical_diag;
ALTER TABLE adi_r_subject DROP 2011alg_research_diag;
ALTER TABLE adi_r_subject DROP 2011alg_clinical_diag;
ALTER TABLE adi_r_subject DROP 2011alg_range_concern;

