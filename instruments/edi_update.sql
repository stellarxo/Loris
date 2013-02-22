ALTER TABLE edi ADD `bir` enum('0_no','1_possible','2_definite','not_answered');
ALTER TABLE edi ADD `dea` enum('0_no','1_possible','2_definite','not_answered');
ALTER TABLE edi ADD `div` enum('0_no','1_possible','2_definite','not_answered');
ALTER TABLE edi ADD `mar` enum('0_no','1_possible','2_definite','not_answered');
ALTER TABLE edi ADD `mov` enum('0_no','1_possible','2_definite','not_answered');
ALTER TABLE edi ADD `tem` enum('0_no','1_possible','2_definite','not_answered');
ALTER TABLE edi ADD `per` enum('0_no','1_possible','2_definite','not_answered');
ALTER TABLE edi ADD `chc` enum('0_no','1_possible','2_definite','not_answered');
ALTER TABLE edi ADD `chs` enum('0_no','1_possible','2_definite','not_answered');
ALTER TABLE edi ADD `sei` enum('0_no','1_possible','2_definite','not_answered');
ALTER TABLE edi ADD `hea` enum('0_no','1_possible','2_definite','not_answered');
ALTER TABLE edi ADD `othi` enum('0_no','1_possible','2_definite','not_answered');
ALTER TABLE edi ADD `hifv` enum('0_no','1_possible','2_definite','not_answered');
ALTER TABLE edi ADD `hosp` enum('0_no','1_possible','2_definite','not_answered');
ALTER TABLE edi ADD `mill` enum('0_no','1_possible','2_definite','not_answered');
ALTER TABLE edi ADD `timeframe_visit` enum('0-3m','0-6m','3m-6m','3m-9m','6m-9m','6m-12m','6m-15m','7m-12m','9m-12m','9m-15m','12m-15m','12m-24m','13m-18m','13m-24m','15m-24m','19m-24m','24m-36m');
DELETE FROM instrument_subtests WHERE ID=109;
DELETE FROM instrument_subtests WHERE ID=133;
DELETE FROM instrument_subtests WHERE ID=134;
DELETE FROM instrument_subtests WHERE ID=110;
UPDATE edi SET timeframe_visit = "0-6m" , bir = bir_0_6months WHERE bir_0_6months IS NOT NULL;
UPDATE edi SET timeframe_visit = "0-6m" , dea = dea_0_6months WHERE dea_0_6months IS NOT NULL;
UPDATE edi SET timeframe_visit = "0-6m" , div = div_0_6months WHERE div_0_6months IS NOT NULL;
UPDATE edi SET timeframe_visit = "0-6m" , mar = mar_0_6months WHERE mar_0_6months IS NOT NULL;
UPDATE edi SET timeframe_visit = "0-6m" , mov = mov_0_6months WHERE mov_0_6months IS NOT NULL;
UPDATE edi SET timeframe_visit = "0-6m" , tem = tem_0_6months WHERE tem_0_6months IS NOT NULL;
UPDATE edi SET timeframe_visit = "0-6m" , per = per_0_6months WHERE per_0_6months IS NOT NULL;
UPDATE edi SET timeframe_visit = "0-6m" , chc = chc_0_6months WHERE chc_0_6months IS NOT NULL;
UPDATE edi SET timeframe_visit = "0-6m" , chs = chs_0_6months WHERE chs_0_6months IS NOT NULL;
UPDATE edi SET timeframe_visit = "0-6m" , sei = sei_0_6months WHERE sei_0_6months IS NOT NULL;
UPDATE edi SET timeframe_visit = "0-6m" , hea = hea_0_6months WHERE hea_0_6months IS NOT NULL;
UPDATE edi SET timeframe_visit = "0-6m" , othi = othi_0_6months WHERE othi_0_6months IS NOT NULL;
UPDATE edi SET timeframe_visit = "0-6m" , hifv = hifv_0_6months WHERE hifv_0_6months IS NOT NULL;
UPDATE edi SET timeframe_visit = "0-6m" , hosp = hosp_0_6months WHERE hosp_0_6months IS NOT NULL;
UPDATE edi SET timeframe_visit = "0-6m" , mill = mill_0_6months WHERE mill_0_6months IS NOT NULL;
UPDATE edi SET timeframe_visit = "7m-12m" , bir = bir_7_12months WHERE bir_7_12months IS NOT NULL;
UPDATE edi SET timeframe_visit = "7m-12m" , dea = dea_7_12months WHERE dea_7_12months IS NOT NULL;
UPDATE edi SET timeframe_visit = "7m-12m" , div = div_7_12months WHERE div_7_12months IS NOT NULL;
UPDATE edi SET timeframe_visit = "7m-12m" , mar = mar_7_12months WHERE mar_7_12months IS NOT NULL;
UPDATE edi SET timeframe_visit = "7m-12m" , mov = mov_7_12months WHERE mov_7_12months IS NOT NULL;
UPDATE edi SET timeframe_visit = "7m-12m" , tem = tem_7_12months WHERE tem_7_12months IS NOT NULL;
UPDATE edi SET timeframe_visit = "7m-12m" , per = per_7_12months WHERE per_7_12months IS NOT NULL;
UPDATE edi SET timeframe_visit = "7m-12m" , chc = chc_7_12months WHERE chc_7_12months IS NOT NULL;
UPDATE edi SET timeframe_visit = "7m-12m" , chs = chs_7_12months WHERE chs_7_12months IS NOT NULL;
UPDATE edi SET timeframe_visit = "7m-12m" , sei = sei_7_12months WHERE sei_7_12months IS NOT NULL;
UPDATE edi SET timeframe_visit = "7m-12m" , hea = hea_7_12months WHERE hea_7_12months IS NOT NULL;
UPDATE edi SET timeframe_visit = "7m-12m" , othi = othi_7_12months WHERE othi_7_12months IS NOT NULL;
UPDATE edi SET timeframe_visit = "7m-12m" , hifv = hifv_7_12months WHERE hifv_7_12months IS NOT NULL;
UPDATE edi SET timeframe_visit = "7m-12m" , hosp = hosp_7_12months WHERE hosp_7_12months IS NOT NULL;
UPDATE edi SET timeframe_visit = "7m-12m" , mill = mill_7_12months WHERE mill_7_12months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-18m" , bir = bir_13_18months WHERE bir_13_18months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-18m" , dea = dea_13_18months WHERE dea_13_18months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-18m" , div = div_13_18months WHERE div_13_18months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-18m" , mar = mar_13_18months WHERE mar_13_18months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-18m" , mov = mov_13_18months WHERE mov_13_18months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-18m" , tem = tem_13_18months WHERE tem_13_18months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-18m" , per = per_13_18months WHERE per_13_18months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-18m" , chc = chc_13_18months WHERE chc_13_18months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-18m" , chs = chs_13_18months WHERE chs_13_18months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-18m" , sei = sei_13_18months WHERE sei_13_18months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-18m" , hea = hea_13_18months WHERE hea_13_18months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-18m" , othi = othi_13_18months WHERE othi_13_18months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-18m" , hifv = hifv_13_18months WHERE hifv_13_18months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-18m" , hosp = hosp_13_18months WHERE hosp_13_18months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-18m" , mill = mill_13_18months WHERE mill_13_18months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-24m" , bir = bir_13_24months WHERE bir_13_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-24m" , dea = dea_13_24months WHERE dea_13_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-24m" , div = div_13_24months WHERE div_13_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-24m" , mar = mar_13_24months WHERE mar_13_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-24m" , mov = mov_13_24months WHERE mov_13_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-24m" , tem = tem_13_24months WHERE tem_13_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-24m" , per = per_13_24months WHERE per_13_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-24m" , chc = chc_13_24months WHERE chc_13_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-24m" , chs = chs_13_24months WHERE chs_13_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-24m" , sei = sei_13_24months WHERE sei_13_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-24m" , hea = hea_13_24months WHERE hea_13_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-24m" , othi = othi_13_24months WHERE othi_13_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-24m" , hifv = hifv_13_24months WHERE hifv_13_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-24m" , hosp = hosp_13_24months WHERE hosp_13_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-24m" , mill = mill_13_24months WHERE mill_13_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "19m-24m" , bir = bir_19_24months WHERE bir_19_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "19m-24m" , dea = dea_19_24months WHERE dea_19_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "19m-24m" , div = div_19_24months WHERE div_19_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "19m-24m" , mar = mar_19_24months WHERE mar_19_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "19m-24m" , mov = mov_19_24months WHERE mov_19_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "19m-24m" , tem = tem_19_24months WHERE tem_19_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "19m-24m" , per = per_19_24months WHERE per_19_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "19m-24m" , chc = chc_19_24months WHERE chc_19_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "19m-24m" , chs = chs_19_24months WHERE chs_19_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "19m-24m" , sei = sei_19_24months WHERE sei_19_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "19m-24m" , hea = hea_19_24months WHERE hea_19_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "19m-24m" , othi = othi_19_24months WHERE othi_19_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "19m-24m" , hifv = hifv_19_24months WHERE hifv_19_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "19m-24m" , hosp = hosp_19_24months WHERE hosp_19_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "19m-24m" , mill = mill_19_24months WHERE mill_19_24months IS NOT NULL;















