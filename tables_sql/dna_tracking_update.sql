ALTER TABLE dna_tracking CHANGE saliva_collection_method1_candidate saliva_collection_method1_candidate enum('project_staff','kit_mail','travelling_phlebotomist','other','not_answered');
ALTER TABLE dna_tracking CHANGE saliva_collection_method1_proband saliva_collection_method1_proband enum('project_staff','kit_mail','travelling_phlebotomist','other','not_answered');
ALTER TABLE dna_tracking CHANGE saliva_collection_method1_mother saliva_collection_method1_mother enum('project_staff','kit_mail','travelling_phlebotomist','other','not_answered');
ALTER TABLE dna_tracking CHANGE saliva_collection_method1_father saliva_collection_method1_father enum('project_staff','kit_mail','travelling_phlebotomist','other','not_answered');
ALTER TABLE dna_tracking CHANGE saliva_collection_method1_other saliva_collection_method1_other enum('project_staff','kit_mail','travelling_phlebotomist','other','not_answered');
ALTER TABLE dna_tracking CHANGE saliva_collection_method2_candidate saliva_collection_method2_candidate enum('project_staff','kit_mail','travelling_phlebotomist','other','not_answered');
ALTER TABLE dna_tracking CHANGE saliva_collection_method2_proband saliva_collection_method2_proband enum('project_staff','kit_mail','travelling_phlebotomist','other','not_answered');
ALTER TABLE dna_tracking CHANGE saliva_collection_method2_mother saliva_collection_method2_mother enum('project_staff','kit_mail','travelling_phlebotomist','other','not_answered');
ALTER TABLE dna_tracking CHANGE saliva_collection_method2_father saliva_collection_method2_father enum('project_staff','kit_mail','travelling_phlebotomist','other','not_answered');
ALTER TABLE dna_tracking CHANGE saliva_collection_method2_other saliva_collection_method2_other enum('project_staff','kit_mail','travelling_phlebotomist','other','not_answered');
ALTER TABLE dna_tracking CHANGE saliva_notcollected_candidate saliva_notcollected_candidate enum('never_scheduled','child_too_old','family_declined','family_not_responsive','other','not_answered');
ALTER TABLE dna_tracking CHANGE saliva_notcollected_proband saliva_notcollected_proband enum('never_scheduled','child_too_old','family_declined','family_not_responsive','other','not_answered');
ALTER TABLE dna_tracking CHANGE saliva_notcollected_mother saliva_notcollected_mother enum('never_scheduled','child_too_old','family_declined','family_not_responsive','other','not_answered');
ALTER TABLE dna_tracking CHANGE saliva_notcollected_father saliva_notcollected_father enum('never_scheduled','child_too_old','family_declined','family_not_responsive','other','not_answered');
ALTER TABLE dna_tracking CHANGE saliva_notcollected_other saliva_notcollected_other enum('never_scheduled','child_too_old','family_declined','family_not_responsive','other','not_answered');
ALTER TABLE dna_tracking CHANGE blood_notcollected_candidate blood_notcollected_candidate enum('never_scheduled','child_too_old','family_declined','family_not_responsive','parent_did_not_want_child_blood_drawn','draw_attempted_unable_to_obtain','individual_declined','individual_not_responsive','collected_blood_sample','other','not_answered');
ALTER TABLE dna_tracking CHANGE blood_notcollected_proband blood_notcollected_proband enum('never_scheduled','child_too_old','family_declined','family_not_responsive','parent_did_not_want_child_blood_drawn','draw_attempted_unable_to_obtain','individual_declined','individual_not_responsive','collected_blood_sample','other','not_answered');
ALTER TABLE dna_tracking CHANGE blood_notcollected_mother blood_notcollected_mother enum('never_scheduled','child_too_old','family_declined','family_not_responsive','parent_did_not_want_child_blood_drawn','draw_attempted_unable_to_obtain','individual_declined','individual_not_responsive','collected_blood_sample','other','not_answered');
ALTER TABLE dna_tracking CHANGE blood_notcollected_father blood_notcollected_father enum('never_scheduled','child_too_old','family_declined','family_not_responsive','parent_did_not_want_child_blood_drawn','draw_attempted_unable_to_obtain','individual_declined','individual_not_responsive','collected_blood_sample','other','not_answered');
ALTER TABLE dna_tracking CHANGE blood_notcollected_other blood_notcollected_other enum('never_scheduled','child_too_old','family_declined','family_not_responsive','parent_did_not_want_child_blood_drawn','draw_attempted_unable_to_obtain','individual_declined','individual_not_responsive','collected_blood_sample','other','not_answered');
ALTER TABLE dna_tracking CHANGE blood_notcollected_candidate blood_notcollected_candidate enum('never_scheduled','child_too_old','family_declined','family_not_responsive','parent_did_not_want_child_blood_drawn','draw_attempted_unable_to_obtain','individual_declined','individual_not_responsive','other','not_answered');
ALTER TABLE dna_tracking CHANGE blood_notcollected_proband blood_notcollected_proband enum('never_scheduled','child_too_old','family_declined','family_not_responsive','parent_did_not_want_child_blood_drawn','draw_attempted_unable_to_obtain','individual_declined','individual_not_responsive','other','not_answered');
ALTER TABLE dna_tracking CHANGE blood_notcollected_mother blood_notcollected_mother enum('never_scheduled','child_too_old','family_declined','family_not_responsive','parent_did_not_want_child_blood_drawn','draw_attempted_unable_to_obtain','individual_declined','individual_not_responsive','other','not_answered');
ALTER TABLE dna_tracking CHANGE blood_notcollected_father blood_notcollected_father enum('never_scheduled','child_too_old','family_declined','family_not_responsive','parent_did_not_want_child_blood_drawn','draw_attempted_unable_to_obtain','individual_declined','individual_not_responsive','other','not_answered');
ALTER TABLE dna_tracking CHANGE blood_notcollected_other blood_notcollected_other enum('never_scheduled','child_too_old','family_declined','family_not_responsive','parent_did_not_want_child_blood_drawn','draw_attempted_unable_to_obtain','individual_declined','individual_not_responsive','other','not_answered');
ALTER TABLE dna_tracking ADD COLUMN num_yellowtop_collected1_candidate enum('1','2','3','more_than3','not_answered');
ALTER TABLE dna_tracking ADD COLUMN num_yellowtop_collected1_proband enum('1','2','3','more_than3','not_answered');
ALTER TABLE dna_tracking ADD COLUMN num_yellowtop_collected1_mother enum('1','2','3','more_than3','not_answered');
ALTER TABLE dna_tracking ADD COLUMN num_yellowtop_collected1_father enum('1','2','3','more_than3','not_answered');
ALTER TABLE dna_tracking ADD COLUMN num_yellowtop_collected1_other enum('1','2','3','more_than3','not_answered');
ALTER TABLE dna_tracking ADD COLUMN num_yellowtop_collected2_candidate enum('1','2','3','more_than3','not_answered');
ALTER TABLE dna_tracking ADD COLUMN num_yellowtop_collected2_proband enum('1','2','3','more_than3','not_answered');
ALTER TABLE dna_tracking ADD COLUMN num_yellowtop_collected2_mother enum('1','2','3','more_than3','not_answered');
ALTER TABLE dna_tracking ADD COLUMN num_yellowtop_collected2_father enum('1','2','3','more_than3','not_answered');
ALTER TABLE dna_tracking ADD COLUMN num_yellowtop_collected2_other enum('1','2','3','more_than3','not_answered');
