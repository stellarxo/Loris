-- CREATED BY RIDA ABOU-HAIDAR to support more siblings
ALTER TABLE tsi ADD COLUMN age_sibling5 varchar(255);
ALTER TABLE tsi ADD COLUMN age_sibling6 varchar(255);
ALTER TABLE tsi ADD COLUMN age_sibling7 varchar(255);
ALTER TABLE tsi ADD COLUMN age_sibling8 varchar(255);
ALTER TABLE tsi ADD COLUMN age_sibling9 varchar(255);
ALTER TABLE tsi ADD COLUMN age_sibling10 varchar(255);

ALTER TABLE tsi ADD COLUMN dx_sibling5 varchar(255);
ALTER TABLE tsi ADD COLUMN dx_sibling6 varchar(255);
ALTER TABLE tsi ADD COLUMN dx_sibling7 varchar(255);
ALTER TABLE tsi ADD COLUMN dx_sibling8 varchar(255);
ALTER TABLE tsi ADD COLUMN dx_sibling9 varchar(255);
ALTER TABLE tsi ADD COLUMN dx_sibling10 varchar(255);

ALTER TABLE tsi ADD COLUMN dx_sibling5_status enum('not_answered');
ALTER TABLE tsi ADD COLUMN dx_sibling6_status enum('not_answered');
ALTER TABLE tsi ADD COLUMN dx_sibling7_status enum('not_answered');
ALTER TABLE tsi ADD COLUMN dx_sibling8_status enum('not_answered');
ALTER TABLE tsi ADD COLUMN dx_sibling9_status enum('not_answered');
ALTER TABLE tsi ADD COLUMN dx_sibling10_status enum('not_answered');

ALTER TABLE tsi ADD COLUMN relation_sibling5 enum('half_sibling','full_sibling','step_sibling','not_answered');
ALTER TABLE tsi ADD COLUMN relation_sibling6 enum('half_sibling','full_sibling','step_sibling','not_answered');
ALTER TABLE tsi ADD COLUMN relation_sibling7 enum('half_sibling','full_sibling','step_sibling','not_answered');
ALTER TABLE tsi ADD COLUMN relation_sibling8 enum('half_sibling','full_sibling','step_sibling','not_answered');
ALTER TABLE tsi ADD COLUMN relation_sibling9 enum('half_sibling','full_sibling','step_sibling','not_answered');
ALTER TABLE tsi ADD COLUMN relation_sibling10 enum('half_sibling','full_sibling','step_sibling','not_answered');

ALTER TABLE tsi ADD COLUMN live_at_home_sibling5 enum('yes','no','part_time','not_answered');
ALTER TABLE tsi ADD COLUMN live_at_home_sibling6 enum('yes','no','part_time','not_answered');
ALTER TABLE tsi ADD COLUMN live_at_home_sibling7 enum('yes','no','part_time','not_answered');
ALTER TABLE tsi ADD COLUMN live_at_home_sibling8 enum('yes','no','part_time','not_answered');
ALTER TABLE tsi ADD COLUMN live_at_home_sibling9 enum('yes','no','part_time','not_answered');
ALTER TABLE tsi ADD COLUMN live_at_home_sibling10 enum('yes','no','part_time','not_answered');

ALTER TABLE tsi_followup ADD COLUMN age_sibling5 varchar(255);
ALTER TABLE tsi_followup ADD COLUMN age_sibling6 varchar(255);
ALTER TABLE tsi_followup ADD COLUMN age_sibling7 varchar(255);
ALTER TABLE tsi_followup ADD COLUMN age_sibling8 varchar(255);
ALTER TABLE tsi_followup ADD COLUMN age_sibling9 varchar(255);
ALTER TABLE tsi_followup ADD COLUMN age_sibling10 varchar(255);

ALTER TABLE tsi_followup ADD COLUMN dx_sibling5 varchar(255);
ALTER TABLE tsi_followup ADD COLUMN dx_sibling6 varchar(255);
ALTER TABLE tsi_followup ADD COLUMN dx_sibling7 varchar(255);
ALTER TABLE tsi_followup ADD COLUMN dx_sibling8 varchar(255);
ALTER TABLE tsi_followup ADD COLUMN dx_sibling9 varchar(255);
ALTER TABLE tsi_followup ADD COLUMN dx_sibling10 varchar(255);

ALTER TABLE tsi_followup ADD COLUMN dx_sibling5_status enum('not_answered');
ALTER TABLE tsi_followup ADD COLUMN dx_sibling6_status enum('not_answered');
ALTER TABLE tsi_followup ADD COLUMN dx_sibling7_status enum('not_answered');
ALTER TABLE tsi_followup ADD COLUMN dx_sibling8_status enum('not_answered');
ALTER TABLE tsi_followup ADD COLUMN dx_sibling9_status enum('not_answered');
ALTER TABLE tsi_followup ADD COLUMN dx_sibling10_status enum('not_answered');

ALTER TABLE tsi_followup ADD COLUMN relation_sibling5 enum('half_sibling','full_sibling','step_sibling','not_answered');
ALTER TABLE tsi_followup ADD COLUMN relation_sibling6 enum('half_sibling','full_sibling','step_sibling','not_answered');
ALTER TABLE tsi_followup ADD COLUMN relation_sibling7 enum('half_sibling','full_sibling','step_sibling','not_answered');
ALTER TABLE tsi_followup ADD COLUMN relation_sibling8 enum('half_sibling','full_sibling','step_sibling','not_answered');
ALTER TABLE tsi_followup ADD COLUMN relation_sibling9 enum('half_sibling','full_sibling','step_sibling','not_answered');
ALTER TABLE tsi_followup ADD COLUMN relation_sibling10 enum('half_sibling','full_sibling','step_sibling','not_answered');

ALTER TABLE tsi_followup ADD COLUMN live_at_home_sibling5 enum('yes','no','part_time','not_answered');
ALTER TABLE tsi_followup ADD COLUMN live_at_home_sibling6 enum('yes','no','part_time','not_answered');
ALTER TABLE tsi_followup ADD COLUMN live_at_home_sibling7 enum('yes','no','part_time','not_answered');
ALTER TABLE tsi_followup ADD COLUMN live_at_home_sibling8 enum('yes','no','part_time','not_answered');
ALTER TABLE tsi_followup ADD COLUMN live_at_home_sibling9 enum('yes','no','part_time','not_answered');
ALTER TABLE tsi_followup ADD COLUMN live_at_home_sibling10 enum('yes','no','part_time','not_answered');
