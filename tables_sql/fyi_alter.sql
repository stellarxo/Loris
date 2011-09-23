ALTER TABLE fyi ADD COLUMN orientrec integer(2) NULL;
ALTER TABLE fyi ADD COLUMN affeng integer(2) NULL;
ALTER TABLE fyi ADD COLUMN imitate integer(2) NULL;
ALTER TABLE fyi ADD COLUMN express integer(2) NULL;
ALTER TABLE fyi ADD COLUMN senproc integer(2) NULL;
ALTER TABLE fyi ADD COLUMN regpat integer(2) NULL;
ALTER TABLE fyi ADD COLUMN react integer(2) NULL;
ALTER TABLE fyi ADD COLUMN repplay integer(2) NULL;

ALTER TABLE fyi ADD COLUMN soc_com_risk decimal(5,3) NULL;
ALTER TABLE fyi ADD COLUMN sen_reg_risk decimal(5,3) NULL;
ALTER TABLE fyi ADD COLUMN risk_score decimal(5,3) NULL;
ALTER TABLE fyi ADD COLUMN percentile integer(3) NULL;
