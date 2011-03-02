ALTER TABLE csbs ADD COLUMN q_16_language_comp_objects_1_name varchar(255) AFTER words_weighted;
ALTER TABLE csbs ADD COLUMN q_16_language_comp_objects_2_name varchar(255) AFTER q_16_language_comp_objects_1;
ALTER TABLE csbs ADD COLUMN q_16_language_comp_objects_3_name varchar(256) AFTER q_16_language_comp_objects_2;
ALTER TABLE csbs ADD COLUMN q_16_language_comp_objects_4_name varchar(255) AFTER q_16_language_comp_objects_3;

ALTER TABLE csbs ADD COLUMN q_16_language_comp_person_1_name varchar(255) AFTER q_16_language_comp_raw_score;
ALTER TABLE csbs ADD COLUMN q_16_language_comp_person_2_name varchar(256) AFTER q_16_language_comp_person_1;
ALTER TABLE csbs ADD COLUMN q_16_language_comp_person_3_name varchar(255) AFTER q_16_language_comp_person_2;

ALTER TABLE csbs ADD COLUMN q_16_language_comp_body_parts_1_name varchar(255) AFTER q_16_language_comp_person_3;
ALTER TABLE csbs ADD COLUMN q_16_language_comp_body_parts_2_name varchar(255) AFTER q_16_language_comp_body_parts_1;
ALTER TABLE csbs ADD COLUMN q_16_language_comp_body_parts_3_name varchar(256) AFTER q_16_language_comp_body_parts_2;
ALTER TABLE csbs ADD COLUMN q_16_language_comp_body_parts_4_name varchar(255) AFTER q_16_language_comp_body_parts_3;


ALTER TABLE csbs ADD COLUMN q_17_action_schemes_none varchar(255) AFTER q_17_action_schemes_pours;

ALTER TABLE csbs CHANGE q_18_actions_towards_other_1 q_18_action_towards_other_1 enum('puts_in', 'puts_on', 'drinks_with_bottle', 'drinks_with_cup', 'hugs', 'kisses', 'feeds_with_utensil', 'feeds_with_bowl', 'stirs', 'scoops', 'pours', 'other', 'none');
ALTER TABLE csbs ADD COLUMN q_18_action_towards_other_1_agent enum('parent', 'clinician', 'toy', 'other') AFTER q_18_action_towards_other_1;
ALTER TABLE csbs ADD COLUMN q_18_action_towards_other_1_agent_specify varchar(255) AFTER q_18_action_towards_other_1_agent;
ALTER TABLE csbs CHANGE q_18_actions_towards_other_2 q_18_action_towards_other_2 enum('puts_in', 'puts_on', 'drinks_with_bottle', 'drinks_with_cup', 'hugs', 'kisses', 'feeds_with_utensil', 'feeds_with_bowl', 'stirs', 'scoops', 'pours', 'other', 'none');
ALTER TABLE csbs ADD COLUMN q_18_action_towards_other_2_agent enum('parent', 'clinician', 'toy', 'other') AFTER q_18_action_towards_other_2;
ALTER TABLE csbs ADD COLUMN q_18_action_towards_other_2_agent_specify varchar(255) AFTER q_18_action_towards_other_2_agent;
ALTER TABLE csbs CHANGE q_18_actions_towards_other_3 q_18_action_towards_other_3 enum('puts_in', 'puts_on', 'drinks_with_bottle', 'drinks_with_cup', 'hugs', 'kisses', 'feeds_with_utensil', 'feeds_with_bowl', 'stirs', 'scoops', 'pours', 'other', 'none');
ALTER TABLE csbs ADD COLUMN q_18_action_towards_other_3_agent enum('parent', 'clinician', 'toy', 'other') AFTER q_18_action_towards_other_3;
ALTER TABLE csbs ADD COLUMN q_18_action_towards_other_3_agent_specify varchar(255) AFTER q_18_action_towards_other_3_agent;
ALTER TABLE csbs CHANGE q_18_actions_towards_other_4 q_18_action_towards_other_4 enum('puts_in', 'puts_on', 'drinks_with_bottle', 'drinks_with_cup', 'hugs', 'kisses', 'feeds_with_utensil', 'feeds_with_bowl', 'stirs', 'scoops', 'pours', 'other', 'none');
ALTER TABLE csbs ADD COLUMN q_18_action_towards_other_4_agent enum('parent', 'clinician', 'toy', 'other') AFTER q_18_action_towards_other_4;
ALTER TABLE csbs ADD COLUMN q_18_action_towards_other_4_agent_specify varchar(255) AFTER q_18_action_towards_other_4_agent;
ALTER TABLE csbs CHANGE q_18_actions_towards_other_5 q_18_action_towards_other_5 enum('puts_in', 'puts_on', 'drinks_with_bottle', 'drinks_with_cup', 'hugs', 'kisses', 'feeds_with_utensil', 'feeds_with_bowl', 'stirs', 'scoops', 'pours', 'other', 'none');
ALTER TABLE csbs ADD COLUMN q_18_action_towards_other_5_agent enum('parent', 'clinician', 'toy', 'other') AFTER q_18_action_towards_other_5;
ALTER TABLE csbs ADD COLUMN q_18_action_towards_other_5_agent_specify varchar(255) AFTER q_18_action_towards_other_5_agent;
ALTER TABLE csbs CHANGE q_18_actions_towards_other_6 q_18_action_towards_other_6 enum('puts_in', 'puts_on', 'drinks_with_bottle', 'drinks_with_cup', 'hugs', 'kisses', 'feeds_with_utensil', 'feeds_with_bowl', 'stirs', 'scoops', 'pours', 'other', 'none');
ALTER TABLE csbs ADD COLUMN q_18_action_towards_other_6_agent enum('parent', 'clinician', 'toy', 'other') AFTER q_18_action_towards_other_6;
ALTER TABLE csbs ADD COLUMN q_18_action_towards_other_6_agent_specify varchar(255) AFTER q_18_action_towards_other_6_agent;

ALTER TABLE csbs ADD COLUMN q_19_sequence_action_schemes_1_action1 enum('puts_in', 'puts_on', 'drinks_with_bottle', 'drinks_with_cup', 'hugs', 'kisses', 'feeds_with_utensil', 'feeds_with_bowl', 'stirs', 'scoops', 'pours', 'other', 'none') AFTER q_19_sequence_action_schemes_1;
ALTER TABLE csbs ADD COLUMN q_19_sequence_action_schemes_1_action2 enum('puts_in', 'puts_on', 'drinks_with_bottle', 'drinks_with_cup', 'hugs', 'kisses', 'feeds_with_utensil', 'feeds_with_bowl', 'stirs', 'scoops', 'pours', 'other', 'none') AFTER q_19_sequence_action_schemes_1_action1;
ALTER TABLE csbs ADD COLUMN q_19_sequence_action_schemes_2_action1 enum('puts_in', 'puts_on', 'drinks_with_bottle', 'drinks_with_cup', 'hugs', 'kisses', 'feeds_with_utensil', 'feeds_with_bowl', 'stirs', 'scoops', 'pours', 'other', 'none') AFTER q_19_sequence_action_schemes_2;
ALTER TABLE csbs ADD COLUMN q_19_sequence_action_schemes_2_action2 enum('puts_in', 'puts_on', 'drinks_with_bottle', 'drinks_with_cup', 'hugs', 'kisses', 'feeds_with_utensil', 'feeds_with_bowl', 'stirs', 'scoops', 'pours', 'other', 'none') AFTER q_19_sequence_action_schemes_2_action1;
ALTER TABLE csbs ADD COLUMN q_19_sequence_action_schemes_3_action1 enum('puts_in', 'puts_on', 'drinks_with_bottle', 'drinks_with_cup', 'hugs', 'kisses', 'feeds_with_utensil', 'feeds_with_bowl', 'stirs', 'scoops', 'pours', 'other', 'none') AFTER q_19_sequence_action_schemes_3;
ALTER TABLE csbs ADD COLUMN q_19_sequence_action_schemes_3_action2 enum('puts_in', 'puts_on', 'drinks_with_bottle', 'drinks_with_cup', 'hugs', 'kisses', 'feeds_with_utensil', 'feeds_with_bowl', 'stirs', 'scoops', 'pours', 'other', 'none') AFTER q_19_sequence_action_schemes_3_action1;
ALTER TABLE csbs ADD COLUMN q_19_sequence_action_schemes_4_action1 enum('puts_in', 'puts_on', 'drinks_with_bottle', 'drinks_with_cup', 'hugs', 'kisses', 'feeds_with_utensil', 'feeds_with_bowl', 'stirs', 'scoops', 'pours', 'other', 'none') AFTER q_19_sequence_action_schemes_4;
ALTER TABLE csbs ADD COLUMN q_19_sequence_action_schemes_4_action2 enum('puts_in', 'puts_on', 'drinks_with_bottle', 'drinks_with_cup', 'hugs', 'kisses', 'feeds_with_utensil', 'feeds_with_bowl', 'stirs', 'scoops', 'pours', 'other', 'none') AFTER q_19_sequence_action_schemes_4_action1;
ALTER TABLE csbs ADD COLUMN q_19_sequence_action_schemes_5_action1 enum('puts_in', 'puts_on', 'drinks_with_bottle', 'drinks_with_cup', 'hugs', 'kisses', 'feeds_with_utensil', 'feeds_with_bowl', 'stirs', 'scoops', 'pours', 'other', 'none') AFTER q_19_sequence_action_schemes_5;
ALTER TABLE csbs ADD COLUMN q_19_sequence_action_schemes_5_action2 enum('puts_in', 'puts_on', 'drinks_with_bottle', 'drinks_with_cup', 'hugs', 'kisses', 'feeds_with_utensil', 'feeds_with_bowl', 'stirs', 'scoops', 'pours', 'other', 'none') AFTER q_19_sequence_action_schemes_5_action1;
ALTER TABLE csbs ADD COLUMN q_19_sequence_action_schemes_6_action1 enum('puts_in', 'puts_on', 'drinks_with_bottle', 'drinks_with_cup', 'hugs', 'kisses', 'feeds_with_utensil', 'feeds_with_bowl', 'stirs', 'scoops', 'pours', 'other', 'none') AFTER q_19_sequence_action_schemes_6;
ALTER TABLE csbs ADD COLUMN q_19_sequence_action_schemes_6_action2 enum('puts_in', 'puts_on', 'drinks_with_bottle', 'drinks_with_cup', 'hugs', 'kisses', 'feeds_with_utensil', 'feeds_with_bowl', 'stirs', 'scoops', 'pours', 'other', 'none') AFTER q_19_sequence_action_schemes_6_action1;
