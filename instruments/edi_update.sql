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
UPDATE edi SET timeframe_visit = "0-6m" AND bir = bir_0_6months WHERE bir_0_6months IS NOT NULL;
UPDATE edi SET timeframe_visit = "0-6m" AND dea = dea_0_6months WHERE dea_0_6months IS NOT NULL;
UPDATE edi SET timeframe_visit = "0-6m" AND div = div_0_6months WHERE div_0_6months IS NOT NULL;
UPDATE edi SET timeframe_visit = "0-6m" AND mar = mar_0_6months WHERE mar_0_6months IS NOT NULL;
UPDATE edi SET timeframe_visit = "0-6m" AND mov = mov_0_6months WHERE mov_0_6months IS NOT NULL;
UPDATE edi SET timeframe_visit = "0-6m" AND tem = tem_0_6months WHERE tem_0_6months IS NOT NULL;
UPDATE edi SET timeframe_visit = "0-6m" AND per = per_0_6months WHERE per_0_6months IS NOT NULL;
UPDATE edi SET timeframe_visit = "0-6m" AND chc = chc_0_6months WHERE chc_0_6months IS NOT NULL;
UPDATE edi SET timeframe_visit = "0-6m" AND chs = chs_0_6months WHERE chs_0_6months IS NOT NULL;
UPDATE edi SET timeframe_visit = "0-6m" AND sei = sei_0_6months WHERE sei_0_6months IS NOT NULL;
UPDATE edi SET timeframe_visit = "0-6m" AND hea = hea_0_6months WHERE hea_0_6months IS NOT NULL;
UPDATE edi SET timeframe_visit = "0-6m" AND othi = othi_0_6months WHERE othi_0_6months IS NOT NULL;
UPDATE edi SET timeframe_visit = "0-6m" AND hifv = hifv_0_6months WHERE hifv_0_6months IS NOT NULL;
UPDATE edi SET timeframe_visit = "0-6m" AND hosp = hosp_0_6months WHERE hosp_0_6months IS NOT NULL;
UPDATE edi SET timeframe_visit = "0-6m" AND mill = mill_0_6months WHERE mill_0_6months IS NOT NULL;
UPDATE edi SET timeframe_visit = "7m-12m" AND bir = bir_7_12months WHERE bir_7_12months IS NOT NULL;
UPDATE edi SET timeframe_visit = "7m-12m" AND dea = dea_7_12months WHERE dea_7_12months IS NOT NULL;
UPDATE edi SET timeframe_visit = "7m-12m" AND div: = div_7_12months WHERE div_7_12months IS NOT NULL;
UPDATE edi SET timeframe_visit = "7m-12m" AND mar = mar_7_12months WHERE mar_7_12months IS NOT NULL;
UPDATE edi SET timeframe_visit = "7m-12m" AND mov = mov_7_12months WHERE mov_7_12months IS NOT NULL;
UPDATE edi SET timeframe_visit = "7m-12m" AND tem = tem_7_12months WHERE tem_7_12months IS NOT NULL;
UPDATE edi SET timeframe_visit = "7m-12m" AND per = per_7_12months WHERE per_7_12months IS NOT NULL;
UPDATE edi SET timeframe_visit = "7m-12m" AND chc = chc_7_12months WHERE chc_7_12months IS NOT NULL;
UPDATE edi SET timeframe_visit = "7m-12m" AND chs = chs_7_12months WHERE chs_7_12months IS NOT NULL;
UPDATE edi SET timeframe_visit = "7m-12m" AND sei = sei_7_12months WHERE sei_7_12months IS NOT NULL;
UPDATE edi SET timeframe_visit = "7m-12m" AND hea = hea_7_12months WHERE hea_7_12months IS NOT NULL;
UPDATE edi SET timeframe_visit = "7m-12m" AND othi = othi_7_12months WHERE othi_7_12months IS NOT NULL;
UPDATE edi SET timeframe_visit = "7m-12m" AND hifv = hifv_7_12months WHERE hifv_7_12months IS NOT NULL;
UPDATE edi SET timeframe_visit = "7m-12m" AND hosp = hosp_7_12months WHERE hosp_7_12months IS NOT NULL;
UPDATE edi SET timeframe_visit = "7m-12m" AND mill = mill_7_12months WHERE mill_7_12months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-18m" AND bir = bir_13_18months WHERE bir_13_18months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-18m" AND dea = dea_13_18months WHERE dea_13_18months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-18m" AND div: = div_13_18months WHERE div_13_18months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-18m" AND mar = mar_13_18months WHERE mar_13_18months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-18m" AND mov = mov_13_18months WHERE mov_13_18months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-18m" AND tem = tem_13_18months WHERE tem_13_18months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-18m" AND per = per_13_18months WHERE per_13_18months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-18m" AND chc = chc_13_18months WHERE chc_13_18months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-18m" AND chs = chs_13_18months WHERE chs_13_18months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-18m" AND sei = sei_13_18months WHERE sei_13_18months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-18m" AND hea = hea_13_18months WHERE hea_13_18months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-18m" AND othi = othi_13_18months WHERE othi_13_18months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-18m" AND hifv = hifv_13_18months WHERE hifv_13_18months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-18m" AND hosp = hosp_13_18months WHERE hosp_13_18months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-18m" AND mill = mill_13_18months WHERE mill_13_18months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-24m" AND bir = bir_13_24months WHERE bir_13_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-24m" AND dea = dea_13_24months WHERE dea_13_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-24m" AND div: = div_13_24months WHERE div_13_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-24m" AND mar = mar_13_24months WHERE mar_13_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-24m" AND mov = mov_13_24months WHERE mov_13_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-24m" AND tem = tem_13_24months WHERE tem_13_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-24m" AND per = per_13_24months WHERE per_13_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-24m" AND chc = chc_13_24months WHERE chc_13_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-24m" AND chs = chs_13_24months WHERE chs_13_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-24m" AND sei = sei_13_24months WHERE sei_13_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-24m" AND hea = hea_13_24months WHERE hea_13_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-24m" AND othi = othi_13_24months WHERE othi_13_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-24m" AND hifv = hifv_13_24months WHERE hifv_13_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-24m" AND hosp = hosp_13_24months WHERE hosp_13_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "13m-24m" AND mill = mill_13_24months WHERE mill_13_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "19m-24m" AND bir = bir_19_24months WHERE bir_19_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "19m-24m" AND dea = dea_19_24months WHERE dea_19_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "19m-24m" AND div: = div_19_24months WHERE div_19_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "19m-24m" AND mar = mar_19_24months WHERE mar_19_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "19m-24m" AND mov = mov_19_24months WHERE mov_19_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "19m-24m" AND tem = tem_19_24months WHERE tem_19_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "19m-24m" AND per = per_19_24months WHERE per_19_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "19m-24m" AND chc = chc_19_24months WHERE chc_19_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "19m-24m" AND chs = chs_19_24months WHERE chs_19_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "19m-24m" AND sei = sei_19_24months WHERE sei_19_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "19m-24m" AND hea = hea_19_24months WHERE hea_19_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "19m-24m" AND othi = othi_19_24months WHERE othi_19_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "19m-24m" AND hifv = hifv_19_24months WHERE hifv_19_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "19m-24m" AND hosp = hosp_19_24months WHERE hosp_19_24months IS NOT NULL;
UPDATE edi SET timeframe_visit = "19m-24m" AND mill = mill_19_24months WHERE mill_19_24months IS NOT NULL;















