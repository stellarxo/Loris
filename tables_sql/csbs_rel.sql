-- MySQL dump 10.11
--
-- Host: zaphod    Database: nihaceProd
-- ------------------------------------------------------
-- Server version	5.0.32-Debian_7etch5-log

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `csbs_reliability`
--

DROP TABLE IF EXISTS `csbs_reliability`;
CREATE TABLE `csbs_reliability` (
  `CommentID` varchar(255) NOT NULL default '',
  `UserID` varchar(255) default NULL,
  `Examiner` varchar(255) default NULL,
  `Testdate` timestamp NOT NULL default CURRENT_TIMESTAMP on update CURRENT_TIMESTAMP,
  `Data_entry_completion_status` enum('Incomplete','Complete') NOT NULL default 'Incomplete',
  `Date_taken` date default NULL,
  `relationship_to_child` varchar(255) default NULL,
  `relationship_to_child_status` enum('not_answered') default NULL,
  `q_1_alertness` enum('1_less_than_usual','2_typical','3_very_alert_greater','not_answered') default NULL,
  `q_2_emotional_reaction` enum('1_more_negative','2_typical','3_more_positive','not_answered') default NULL,
  `q_3_level_of_interest` enum('1_less_interest','2_typical','3_greater','not_answered') default NULL,
  `q_4_comfort_level` enum('1_more_cautious','2_typical','3_more_comfortable','not_answered') default NULL,
  `q_5_level_of_activity` enum('1_less_active','2_typical','3_more_active','not_answered') default NULL,
  `q_6_level_of_communication` enum('1_less_than_usual','2_typical','3_greater_than_usual','not_answered') default NULL,
  `q_7_play_behaviour` enum('1_less_organized','2_typical','3_more_organized','not_answered') default NULL,
  `comments` text,
  `comments_status` enum('not_answered') default NULL,
  `q_1_gaze_shifts_1` varchar(255) default NULL,
  `q_1_gaze_shifts_2` varchar(255) default NULL,
  `q_1_gaze_shifts_3` varchar(255) default NULL,
  `q_1_gaze_shifts_4` varchar(255) default NULL,
  `q_1_gaze_shifts_5` varchar(255) default NULL,
  `q_1_gaze_shifts_6` varchar(255) default NULL,
  `q_1_gaze_shifts_raw_score` varchar(255) default NULL,
  `q_2_shared_positive_affect_1` varchar(255) default NULL,
  `q_2_shared_positive_affect_2` varchar(255) default NULL,
  `q_2_shared_positive_affect_3` varchar(255) default NULL,
  `q_2_shared_positive_affect_4` varchar(255) default NULL,
  `q_2_shared_positive_affect_5` varchar(255) default NULL,
  `q_2_shared_positive_affect_6` varchar(255) default NULL,
  `q_2_shared_positive_affect_raw_score` varchar(255) default NULL,
  `q_3_gaze_point_following_2` varchar(255) default NULL,
  `q_3_gaze_point_following_5` varchar(255) default NULL,
  `q_3_gaze_point_following_raw_score` varchar(255) default NULL,
  `emotion_eye_gaze_weighted` varchar(255) default NULL,
  `q_4_rate_of_communicating_1` enum('not_answered','0','1','2','3') default NULL,
  `q_4_rate_of_communicating_2` enum('not_answered','0','1','2','3') default NULL,
  `q_4_rate_of_communicating_3` enum('not_answered','0','1','2','3') default NULL,
  `q_4_rate_of_communicating_4` enum('not_answered','0','1','2','3') default NULL,
  `q_4_rate_of_communicating_5` enum('not_answered','0','1','2','3') default NULL,
  `q_4_rate_of_communicating_6` enum('not_answered','0','1','2','3') default NULL,
  `q_4_rate_of_communicating_raw_score` varchar(255) default NULL,
  `q_5_behaviour_regulation_1` varchar(255) default NULL,
  `q_5_behaviour_regulation_2` varchar(255) default NULL,
  `q_5_behaviour_regulation_3` varchar(255) default NULL,
  `q_5_behaviour_regulation_4` varchar(255) default NULL,
  `q_5_behaviour_regulation_5` varchar(255) default NULL,
  `q_5_behaviour_regulation_6` varchar(255) default NULL,
  `q_5_behaviour_regulation_raw_score` varchar(255) default NULL,
  `q_6_social_interaction_1` varchar(255) default NULL,
  `q_6_social_interaction_2` varchar(255) default NULL,
  `q_6_social_interaction_3` varchar(255) default NULL,
  `q_6_social_interaction_4` varchar(255) default NULL,
  `q_6_social_interaction_5` varchar(255) default NULL,
  `q_6_social_interaction_6` varchar(255) default NULL,
  `q_6_social_interaction_raw_score` varchar(255) default NULL,
  `q_7_joint_attention_1` varchar(255) default NULL,
  `q_7_joint_attention_2` varchar(255) default NULL,
  `q_7_joint_attention_3` varchar(255) default NULL,
  `q_7_joint_attention_4` varchar(255) default NULL,
  `q_7_joint_attention_5` varchar(255) default NULL,
  `q_7_joint_attention_6` varchar(255) default NULL,
  `q_7_joint_attention_raw_score` varchar(255) default NULL,
  `communication_weighted` varchar(255) default NULL,
  `q_8_conventional_gestures_gives` varchar(255) default NULL,
  `q_8_conventional_gestures_shows` varchar(255) default NULL,
  `q_8_conventional_gestures_pushes_pulls` varchar(255) default NULL,
  `q_8_conventional_gestures_reaches` varchar(255) default NULL,
  `q_8_conventional_gestures_raw_score` varchar(255) default NULL,
  `q_8_conventional_gestures_points` varchar(255) default NULL,
  `q_8_conventional_gestures_waves` varchar(255) default NULL,
  `q_8_conventional_gestures_nods_head` varchar(255) default NULL,
  `q_8_conventional_gestures_shakes_head` varchar(255) default NULL,
  `q_9_distal_gestures_1` varchar(255) default NULL,
  `q_9_distal_gestures_2` varchar(255) default NULL,
  `q_9_distal_gestures_3` varchar(255) default NULL,
  `q_9_distal_gestures_4` varchar(255) default NULL,
  `q_9_distal_gestures_5` varchar(255) default NULL,
  `q_9_distal_gestures_6` varchar(255) default NULL,
  `q_9_distal_gestures_raw_score` varchar(255) default NULL,
  `gestures_weighted` varchar(255) default NULL,
  `q_10_syllables_consonants_1` varchar(255) default NULL,
  `q_10_syllables_consonants_2` varchar(255) default NULL,
  `q_10_syllables_consonants_3` varchar(255) default NULL,
  `q_10_syllables_consonants_4` varchar(255) default NULL,
  `q_10_syllables_consonants_5` varchar(255) default NULL,
  `q_10_syllables_consonants_6` varchar(255) default NULL,
  `q_10_syllables_consonants_raw_score` varchar(255) default NULL,
  `q_11_inventory_of_consonants_m` varchar(255) default NULL,
  `q_11_inventory_of_consonants_n` varchar(255) default NULL,
  `q_11_inventory_of_consonants_b_p` varchar(255) default NULL,
  `q_11_inventory_of_consonants_d_t` varchar(255) default NULL,
  `q_11_inventory_of_consonants_g_k` varchar(255) default NULL,
  `q_11_inventory_of_consonants_raw_score` varchar(255) default NULL,
  `q_11_inventory_of_consonants_w` varchar(255) default NULL,
  `q_11_inventory_of_consonants_l` varchar(255) default NULL,
  `q_11_inventory_of_consonants_y` varchar(255) default NULL,
  `q_11_inventory_of_consonants_s` varchar(255) default NULL,
  `q_11_inventory_of_consonants_sh` varchar(255) default NULL,
  `sounds_weighted` varchar(255) default NULL,
  `q_12_words_1` varchar(255) default NULL,
  `q_12_words_2` varchar(255) default NULL,
  `q_12_words_3` varchar(255) default NULL,
  `q_12_words_4` varchar(255) default NULL,
  `q_12_words_5` varchar(255) default NULL,
  `q_12_words_6` varchar(255) default NULL,
  `q_12_words_raw_score` varchar(255) default NULL,
  `q_13_words_1` varchar(255) default NULL,
  `q_13_words_2` varchar(255) default NULL,
  `q_13_words_3` varchar(255) default NULL,
  `q_13_words_4` varchar(255) default NULL,
  `q_13_words_raw_score` varchar(255) default NULL,
  `q_13_words_5` varchar(255) default NULL,
  `q_13_words_6` varchar(255) default NULL,
  `q_13_words_7` varchar(255) default NULL,
  `q_13_words_8` varchar(255) default NULL,
  `q_13_words_9` varchar(255) default NULL,
  `q_13_words_10` varchar(255) default NULL,
  `q_13_words_11` varchar(255) default NULL,
  `q_13_words_12` varchar(255) default NULL,
  `q_13_words_13` varchar(255) default NULL,
  `q_13_words_14` varchar(255) default NULL,
  `q_13_words_15` varchar(255) default NULL,
  `q_13_words_16` varchar(255) default NULL,
  `q_14_word_combos_1` varchar(255) default NULL,
  `q_14_word_combos_2` varchar(255) default NULL,
  `q_14_word_combos_3` varchar(255) default NULL,
  `q_14_word_combos_4` varchar(255) default NULL,
  `q_14_word_combos_5` varchar(255) default NULL,
  `q_14_word_combos_6` varchar(255) default NULL,
  `q_14_word_combos_raw_score` varchar(255) default NULL,
  `q_15_word_combos_1` varchar(255) default NULL,
  `q_15_word_combos_2` varchar(255) default NULL,
  `q_15_word_combos_raw_score` varchar(255) default NULL,
  `q_15_word_combos_3` varchar(255) default NULL,
  `q_15_word_combos_4` varchar(255) default NULL,
  `q_15_word_combos_5` varchar(255) default NULL,
  `q_15_word_combos_6` varchar(255) default NULL,
  `q_15_word_combos_7` varchar(255) default NULL,
  `q_15_word_combos_8` varchar(255) default NULL,
  `words_weighted` varchar(255) default NULL,
  `q_16_language_comp_objects_1` varchar(255) default NULL,
  `q_16_language_comp_objects_2` varchar(255) default NULL,
  `q_16_language_comp_objects_3` varchar(255) default NULL,
  `q_16_language_comp_objects_4` varchar(255) default NULL,
  `q_16_language_comp_raw_score` varchar(255) default NULL,
  `q_16_language_comp_person_1` varchar(255) default NULL,
  `q_16_language_comp_person_2` varchar(255) default NULL,
  `q_16_language_comp_person_3` varchar(255) default NULL,
  `q_16_language_comp_body_parts_1` varchar(255) default NULL,
  `q_16_language_comp_body_parts_2` varchar(255) default NULL,
  `q_16_language_comp_body_parts_3` varchar(255) default NULL,
  `q_16_language_comp_body_parts_4` varchar(255) default NULL,
  `q_16_language_comp_body_parts_raw_score` varchar(255) default NULL,
  `understanding_weighted` varchar(255) default NULL,
  `q_17_action_schemes_puts_in` varchar(255) default NULL,
  `q_17_action_schemes_puts_on` varchar(255) default NULL,
  `q_17_action_schemes_drinks_with_bottle` varchar(255) default NULL,
  `q_17_action_schemes_drinks_with_cup` varchar(255) default NULL,
  `q_17_action_schemes_hugs` varchar(255) default NULL,
  `q_17_action_schemes_kisses` varchar(255) default NULL,
  `q_17_action_schemes_raw_score` varchar(255) default NULL,
  `q_17_action_schemes_feeds_with_utensil` varchar(255) default NULL,
  `q_17_action_schemes_feeds_with_bowl` varchar(255) default NULL,
  `q_17_action_schemes_stirs` varchar(255) default NULL,
  `q_17_action_schemes_scoops` varchar(255) default NULL,
  `q_17_action_schemes_pours` varchar(255) default NULL,
  `q_17_action_schemes_other` varchar(255) default NULL,
  `q_17_action_schemes_other_specify` varchar(255) default NULL,
  `q_18_actions_towards_other_1` varchar(255) default NULL,
  `q_18_actions_towards_other_2` varchar(255) default NULL,
  `q_18_actions_towards_other_3` varchar(255) default NULL,
  `q_18_actions_towards_other_4` varchar(255) default NULL,
  `q_18_actions_towards_other_5` varchar(255) default NULL,
  `q_18_actions_towards_other_6` varchar(255) default NULL,
  `q_18_actions_towards_other_raw_score` varchar(255) default NULL,
  `q_19_sequence_action_schemes_1` varchar(255) default NULL,
  `q_19_sequence_action_schemes_2` varchar(255) default NULL,
  `q_19_sequence_action_schemes_3` varchar(255) default NULL,
  `q_19_sequence_action_schemes_4` varchar(255) default NULL,
  `q_19_sequence_action_schemes_5` varchar(255) default NULL,
  `q_19_sequence_action_schemes_6` varchar(255) default NULL,
  `q_19_sequence_action_schemes_raw_score` varchar(255) default NULL,
  `q_20_stacks_tower` enum('0_refuses','1_tries_but_fails','2_stacks','3_stacks','4_stacks','5_stacks','not_answered') default NULL,
  `q_20_stacks_tower_raw_score` varchar(255) default NULL,
  `object_use_weighted` varchar(255) default NULL,
  PRIMARY KEY  (`CommentID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `csbs_reliability`
--

LOCK TABLES `csbs_reliability` WRITE;
/*!40000 ALTER TABLE `csbs_reliability` DISABLE KEYS */;
INSERT INTO `csbs_reliability` VALUES ('116434dcc1234c65161202252026',NULL,NULL,'2009-02-12 18:47:12','Incomplete',NULL,NULL,NULL,'1_less_than_usual','3_more_positive','3_greater','2_typical','2_typical','2_typical','3_more_organized',NULL,NULL,'unchecked','unchecked','unchecked','unchecked','unchecked','unchecked',NULL,'unchecked','unchecked','unchecked','unchecked','unchecked','unchecked',NULL,'unchecked','unchecked',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,'unchecked','unchecked','unchecked','unchecked','unchecked','unchecked',NULL,'unchecked','unchecked','unchecked','unchecked','unchecked','unchecked',NULL,'unchecked','unchecked','unchecked','unchecked','unchecked','unchecked',NULL,NULL,'unchecked','unchecked','unchecked','unchecked',NULL,'unchecked','unchecked','unchecked','unchecked','unchecked','unchecked','unchecked','unchecked','unchecked','unchecked',NULL,NULL,'unchecked','unchecked','unchecked','unchecked','unchecked','unchecked',NULL,'unchecked','unchecked','unchecked','unchecked','unchecked',NULL,'unchecked','unchecked','unchecked','unchecked','unchecked',NULL,'unchecked','unchecked','unchecked','unchecked','unchecked','unchecked',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,'unchecked','unchecked','unchecked','unchecked','unchecked','unchecked',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,'unchecked','unchecked','unchecked','unchecked','unchecked','unchecked',NULL,'unchecked','unchecked','unchecked','unchecked','unchecked','unchecked',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
/*!40000 ALTER TABLE `csbs_reliability` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2009-03-18 21:26:50
