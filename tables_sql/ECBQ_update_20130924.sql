ALTER TABLE ECBQ ADD COLUMN q_46_feelbetter enum('1_never','2_very_rarely','3_less_than_half','4_about_half','5_more_than_half','6_almost_always','7_always','does_not_apply','not_answered');
UPDATE ECBQ SET q_46_feelbetter = q_46;
ALTER TABLE ECBQ DROP COLUMN q_46;
