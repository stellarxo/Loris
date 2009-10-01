<?php
require_once "NDB_Reliability.class.inc";
//require_once "NDB_BVL_Instrument.class.inc";

/**
 * The forms for the tracking log menu
 * @package mri
 * @subpackage NIHPD
 */
class NDB_Reliability_csbs_reliability extends NDB_Reliability

{
// function _hasAccess()
//     {
//         // create user object
//         $user =& User::singleton();
//         if (PEAR::isError($user)) {
//             return PEAR::raiseError("User Error: ".$user->getMessage());
//         }

//         $DB =& Database::singleton();
//         if (PEAR::isError($DB)) {
//             return PEAR::raiseError("Could not connect to database: ".$DB->getMessage());
//         }
       
//         if(!empty($this->identifier)) {
//             $query = "SELECT psc.CenterID FROM tracking_logs, candidate, psc WHERE tracking_logs.CandID=candidate.CandID AND candidate.CenterID=psc.CenterID AND tracking_logs.Tracking_log_ID='$this->identifier'";
//             $recordCenterID = $DB->selectOne($query);
            
//             return ($user->hasPermission('tracking_logs')
//                     && ($user->hasPermission('tracking_logs_edit_all')
//                         || ($user->getData('CenterID') == $recordCenterID)));

//         } else {
//             return ($user->hasPermission('tracking_logs'));
//         }
//     }

    function _getDefaults()
    {
        $DB =& Database::singleton();
        if(PEAR::isError($DB)) {
            return PEAR::raiseError("Could not connect to database: ".$DB->getMessage());
        }
               
        //print_r($this->identifier);
        if (!empty($this->identifier)) { 
            
            // set the csbs_reliability values 
            $DB->selectRow("SELECT * FROM csbs_reliability WHERE CommentID = '$this->identifier' AND reliability_center_id = '$this->reliability_center_id'", $row);
            if (PEAR::isError($row)) {
                return PEAR::raiseError("DB Error: ".$row->getMessage());
            }

            // print_r($row['CommentID']);

            // Set the defaults
            $defaults['Examiner'] = $row['Examiner'];
            $defaults['Date_taken'] = $row['Date_taken'];
            $defaults['CommentID'] = $row['CommentID'];
            $defaults['reliability_score'] = $row['reliability_score'];
            $defaults['q_1_alertness'] = $row['q_1_alertness'];
            $defaults['q_2_emotional_reaction'] = $row['q_2_emotional_reaction'];
            $defaults['q_3_level_of_interest'] = $row['q_3_level_of_interest'];
            $defaults['q_4_comfort_level'] = $row['q_4_comfort_level'];
            $defaults['q_5_level_of_activity'] = $row['q_5_level_of_activity'];
            $defaults['q_6_level_of_communication'] = $row['q_6_level_of_communication'];
            $defaults['q_7_play_behaviour'] = $row['q_7_play_behaviour'];
            $defaults['comments'] = $row['comments'];
            $defaults['comments_status'] = $row['comments_status'];
            $defaults['q_1_gaze_shifts_1']=$row['q_1_gaze_shifts_1'];
            $defaults['q_1_gaze_shifts_2']=$row['q_1_gaze_shifts_2'];
            $defaults['q_1_gaze_shifts_3']=$row['q_1_gaze_shifts_3'];
            $defaults['q_1_gaze_shifts_4']=$row['q_1_gaze_shifts_4'];
            $defaults['q_1_gaze_shifts_5']=$row['q_1_gaze_shifts_5'];
            $defaults['q_1_gaze_shifts_6']=$row['q_1_gaze_shifts_6'];
            $defaults['q_1_gaze_shifts_raw_score']=$row['q_1_gaze_shifts_raw_score'];
            $defaults['q_2_shared_positive_affect_1']=$row['q_2_shared_positive_affect_1'];
            $defaults['q_2_shared_positive_affect_2']=$row['q_2_shared_positive_affect_2'];
            $defaults['q_2_shared_positive_affect_3']=$row['q_2_shared_positive_affect_3'];
            $defaults['q_2_shared_positive_affect_4']=$row['q_2_shared_positive_affect_4'];
            $defaults['q_2_shared_positive_affect_5']=$row['q_2_shared_positive_affect_5'];
            $defaults['q_2_shared_positive_affect_6']=$row['q_2_shared_positive_affect_6'];
            $defaults['q_2_shared_positive_affect_raw_score']=$row['q_2_shared_positive_affect_raw_score'];
            $defaults['q_3_gaze_point_following_2']=$row['q_3_gaze_point_following_2'];
            $defaults['q_3_gaze_point_following_5']=$row['q_3_gaze_point_following_5'];
            $defaults['q_3_gaze_point_following_raw_score']=$row['q_3_gaze_point_following_raw_score'];
            $defaults['emotion_eye_gaze_weighted']=$row['emotion_eye_gaze_weighted'];
            $defaults['q_4_rate_of_communicating_1']=$row['q_4_rate_of_communicating_1'];
            $defaults['q_4_rate_of_communicating_2']=$row['q_4_rate_of_communicating_2'];
            $defaults['q_4_rate_of_communicating_3']=$row['q_4_rate_of_communicating_3'];
            $defaults['q_4_rate_of_communicating_4']=$row['q_4_rate_of_communicating_4'];
            $defaults['q_4_rate_of_communicating_5']=$row['q_4_rate_of_communicating_5'];
            $defaults['q_4_rate_of_communicating_6']=$row['q_4_rate_of_communicating_6'];
            $defaults['q_4_rate_of_communicating_raw_score']=$row['q_4_rate_of_communicating_raw_score'];
            $defaults['q_5_behaviour_regulation_1']=$row['q_5_behaviour_regulation_1'];
            $defaults['q_5_behaviour_regulation_2']=$row['q_5_behaviour_regulation_2'];
            $defaults['q_5_behaviour_regulation_3']=$row['q_5_behaviour_regulation_3'];
            $defaults['q_5_behaviour_regulation_4']=$row['q_5_behaviour_regulation_4'];
            $defaults['q_5_behaviour_regulation_5']=$row['q_5_behaviour_regulation_5'];
            $defaults['q_5_behaviour_regulation_6']=$row['q_5_behaviour_regulation_6'];
            $defaults['q_5_behaviour_regulation_raw_score']=$row['q_5_behaviour_regulation_raw_score'];
            $defaults['q_6_social_interaction_1']=$row['q_6_social_interaction_1'];
            $defaults['q_6_social_interaction_2']=$row['q_6_social_interaction_2'];
            $defaults['q_6_social_interaction_3']=$row['q_6_social_interaction_3'];
            $defaults['q_6_social_interaction_4']=$row['q_6_social_interaction_4'];
            $defaults['q_6_social_interaction_5']=$row['q_6_social_interaction_5'];
            $defaults['q_6_social_interaction_6']=$row['q_6_social_interaction_6'];
            $defaults['q_6_social_interaction_raw_score']=$row['q_6_social_interaction_raw_score'];
            $defaults['q_7_joint_attention_1']=$row['q_7_joint_attention_1'];
            $defaults['q_7_joint_attention_2']=$row['q_7_joint_attention_2'];
            $defaults['q_7_joint_attention_3']=$row['q_7_joint_attention_3'];
            $defaults['q_7_joint_attention_4']=$row['q_7_joint_attention_4'];
            $defaults['q_7_joint_attention_5']=$row['q_7_joint_attention_5'];
            $defaults['q_7_joint_attention_6']=$row['q_7_joint_attention_6'];
            $defaults['q_7_joint_attention_raw_score']=$row['q_7_joint_attention_raw_score'];
            $defaults['communication_weighted']=$row['communication_weighted'];
            $defaults['q_8_conventional_gestures_gives']=$row['q_8_conventional_gestures_gives'];
            $defaults['q_8_conventional_gestures_shows']=$row['q_8_conventional_gestures_shows'];
            $defaults['q_8_conventional_gestures_pushes_pulls']=$row['q_8_conventional_gestures_pushes_pulls'];
            $defaults['q_8_conventional_gestures_reaches']=$row['q_8_conventional_gestures_reaches'];
            $defaults['q_8_conventional_gestures_raw_score']=$row['q_8_conventional_gestures_raw_score'];
            $defaults['q_8_conventional_gestures_points']=$row['q_8_conventional_gestures_points'];
            $defaults['q_8_conventional_gestures_waves']=$row['q_8_conventional_gestures_waves'];
            $defaults['q_8_conventional_gestures_nods_head']=$row['q_8_conventional_gestures_nods_head'];
            $defaults['q_8_conventional_gestures_shakes_head']=$row['q_8_conventional_gestures_shakes_head'];
            $defaults['q_9_distal_gestures_1']=$row['q_9_distal_gestures_1'];
            $defaults['q_9_distal_gestures_2']=$row['q_9_distal_gestures_2'];
            $defaults['q_9_distal_gestures_3']=$row['q_9_distal_gestures_3'];
            $defaults['q_9_distal_gestures_4']=$row['q_9_distal_gestures_4'];
            $defaults['q_9_distal_gestures_5']=$row['q_9_distal_gestures_5'];
            $defaults['q_9_distal_gestures_6']=$row['q_9_distal_gestures_6'];
            $defaults['q_9_distal_gestures_raw_score']=$row['q_9_distal_gestures_raw_score'];
            $defaults['gestures_weighted']=$row['gestures_weighted'];
            $defaults['q_10_syllables_consonants_1']=$row['q_10_syllables_consonants_1'];
            $defaults['q_10_syllables_consonants_2']=$row['q_10_syllables_consonants_2'];
            $defaults['q_10_syllables_consonants_3']=$row['q_10_syllables_consonants_3'];
            $defaults['q_10_syllables_consonants_4']=$row['q_10_syllables_consonants_4'];
            $defaults['q_10_syllables_consonants_5']=$row['q_10_syllables_consonants_5'];
            $defaults['q_10_syllables_consonants_6']=$row['q_10_syllables_consonants_6'];
            $defaults['q_10_syllables_consonants_raw_score']=$row['q_10_syllables_consonants_raw_score'];
            $defaults['q_11_inventory_of_consonants_m']=$row['q_11_inventory_of_consonants_m'];
            $defaults['q_11_inventory_of_consonants_n']=$row['q_11_inventory_of_consonants_n'];
            $defaults['q_11_inventory_of_consonants_b_p']=$row['q_11_inventory_of_consonants_b_p'];
            $defaults['q_11_inventory_of_consonants_d_t']=$row['q_11_inventory_of_consonants_d_t'];
            $defaults['q_11_inventory_of_consonants_g_k']=$row['q_11_inventory_of_consonants_g_k'];
            $defaults['q_11_inventory_of_consonants_raw_score']=$row['q_11_inventory_of_consonants_raw_score'];
            $defaults['q_11_inventory_of_consonants_w']=$row['q_11_inventory_of_consonants_w'];
            $defaults['q_11_inventory_of_consonants_l']=$row['q_11_inventory_of_consonants_l'];
            $defaults['q_11_inventory_of_consonants_y']=$row['q_11_inventory_of_consonants_y'];
            $defaults['q_11_inventory_of_consonants_s']=$row['q_11_inventory_of_consonants_s'];
            $defaults['q_11_inventory_of_consonants_sh']=$row['q_11_inventory_of_consonants_sh'];
            $defaults['sounds_weighted']=$row['sounds_weighted'];
            $defaults['q_12_words_1']=$row['q_12_words_1'];
            $defaults['q_12_words_2']=$row['q_12_words_2'];
            $defaults['q_12_words_3']=$row['q_12_words_3'];
            $defaults['q_12_words_4']=$row['q_12_words_4'];
            $defaults['q_12_words_5']=$row['q_12_words_5'];
            $defaults['q_12_words_6']=$row['q_12_words_6'];
            $defaults['q_12_words_raw_score']=$row['q_12_words_raw_score'];
            $defaults['q_13_words_1']=$row['q_13_words_1'];
            $defaults['q_13_words_2']=$row['q_13_words_2'];
            $defaults['q_13_words_3']=$row['q_13_words_3'];
            $defaults['q_13_words_4']=$row['q_13_words_4'];
            $defaults['q_13_words_raw_score']=$row['q_13_words_raw_score'];
            $defaults['q_13_words_5']=$row['q_13_words_5'];
            $defaults['q_13_words_6']=$row['q_13_words_6'];
            $defaults['q_13_words_7']=$row['q_13_words_7'];
            $defaults['q_13_words_8']=$row['q_13_words_8'];
            $defaults['q_13_words_9']=$row['q_13_words_9'];
            $defaults['q_13_words_10']=$row['q_13_words_10'];
            $defaults['q_13_words_11']=$row['q_13_words_11'];
            $defaults['q_13_words_12']=$row['q_13_words_12'];
            $defaults['q_13_words_13']=$row['q_13_words_13'];
            $defaults['q_13_words_14']=$row['q_13_words_14'];
            $defaults['q_13_words_15']=$row['q_13_words_15'];
            $defaults['q_13_words_16']=$row['q_13_words_16'];
            $defaults['q_14_word_combos_1']=$row['q_14_word_combos_1'];
            $defaults['q_14_word_combos_2']=$row['q_14_word_combos_2'];
            $defaults['q_14_word_combos_3']=$row['q_14_word_combos_3'];
            $defaults['q_14_word_combos_4']=$row['q_14_word_combos_4'];
            $defaults['q_14_word_combos_5']=$row['q_14_word_combos_5'];
            $defaults['q_14_word_combos_6']=$row['q_14_word_combos_6'];
            $defaults['q_14_word_combos_raw_score']=$row['q_14_word_combos_raw_score'];
            $defaults['q_15_word_combos_1']=$row['q_15_word_combos_1'];
            $defaults['q_15_word_combos_2']=$row['q_15_word_combos_2'];
            $defaults['q_15_word_combos_raw_score']=$row['q_15_word_combos_raw_score'];
            $defaults['q_15_word_combos_3']=$row['q_15_word_combos_3'];
            $defaults['q_15_word_combos_4']=$row['q_15_word_combos_4'];
            $defaults['q_15_word_combos_5']=$row['q_15_word_combos_5'];
            $defaults['q_15_word_combos_6']=$row['q_15_word_combos_6'];
            $defaults['q_15_word_combos_7']=$row['q_15_word_combos_7'];
            $defaults['q_15_word_combos_8']=$row['q_15_word_combos_8'];
            $defaults['words_weighted']=$row['words_weighted'];
            $defaults['q_16_language_comp_objects_1']=$row['q_16_language_comp_objects_1'];
            $defaults['q_16_language_comp_objects_2']=$row['q_16_language_comp_objects_2'];
            $defaults['q_16_language_comp_objects_3']=$row['q_16_language_comp_objects_3'];
            $defaults['q_16_language_comp_objects_4']=$row['q_16_language_comp_objects_4'];
            $defaults['q_16_language_comp_raw_score']=$row['q_16_language_comp_raw_score'];
            $defaults['q_16_language_comp_person_1']=$row['q_16_language_comp_person_1'];
            $defaults['q_16_language_comp_person_2']=$row['q_16_language_comp_person_2'];
            $defaults['q_16_language_comp_person_3']=$row['q_16_language_comp_person_3'];
            $defaults['q_16_language_comp_person_raw_score']=$row['q_16_language_comp_person_raw_score'];
            $defaults['q_16_language_comp_body_parts_1']=$row['q_16_language_comp_body_parts_1'];
            $defaults['q_16_language_comp_body_parts_2']=$row['q_16_language_comp_body_parts_2'];
            $defaults['q_16_language_comp_body_parts_3']=$row['q_16_language_comp_body_parts_3'];
            $defaults['q_16_language_comp_body_parts_4']=$row['q_16_language_comp_body_parts_4'];
            $defaults['q_16_language_comp_body_parts_raw_score']=$row['q_16_language_comp_body_parts_raw_score'];
            $defaults['understanding_weighted']=$row['understanding_weighted'];
            $defaults['q_17_action_schemes_puts_in']=$row['q_17_action_schemes_puts_in'];
            $defaults['q_17_action_schemes_puts_on']=$row['q_17_action_schemes_puts_on'];
            $defaults['q_17_action_schemes_drinks_with_bottle']=$row['q_17_action_schemes_drinks_with_bottle'];
            $defaults['q_17_action_schemes_drinks_with_cup']=$row['q_17_action_schemes_drinks_with_cup'];
            $defaults['q_17_action_schemes_hugs']=$row['q_17_action_schemes_hugs'];
            $defaults['q_17_action_schemes_kisses']=$row['q_17_action_schemes_kisses'];
            $defaults['q_17_action_schemes_raw_score']=$row['q_17_action_schemes_raw_score'];
            $defaults['q_17_action_schemes_feeds_with_utensil']=$row['q_17_action_schemes_feeds_with_utensil'];
            $defaults['q_17_action_schemes_feeds_with_bowl']=$row['q_17_action_schemes_feeds_with_bowl'];
            $defaults['q_17_action_schemes_stirs']=$row['q_17_action_schemes_stirs'];
            $defaults['q_17_action_schemes_scoops']=$row['q_17_action_schemes_scoops'];
            $defaults['q_17_action_schemes_pours']=$row['q_17_action_schemes_pours'];
            $defaults['q_17_action_schemes_other']=$row['q_17_action_schemes_other'];
            $defaults['q_17_action_schemes_other_specify']=$row['q_17_action_schemes_other_specify'];
            $defaults['q_18_actions_towards_other_1']=$row['q_18_actions_towards_other_1'];
            $defaults['q_18_actions_towards_other_2']=$row['q_18_actions_towards_other_2'];
            $defaults['q_18_actions_towards_other_3']=$row['q_18_actions_towards_other_3'];
            $defaults['q_18_actions_towards_other_4']=$row['q_18_actions_towards_other_4'];
            $defaults['q_18_actions_towards_other_5']=$row['q_18_actions_towards_other_5'];
            $defaults['q_18_actions_towards_other_6']=$row['q_18_actions_towards_other_6'];
            $defaults['q_18_actions_towards_other_raw_score']=$row['q_18_actions_towards_other_raw_score'];
            $defaults['q_19_sequence_action_schemes_1']=$row['q_19_sequence_action_schemes_1'];
            $defaults['q_19_sequence_action_schemes_2']=$row['q_19_sequence_action_schemes_2'];
            $defaults['q_19_sequence_action_schemes_3']=$row['q_19_sequence_action_schemes_3'];
            $defaults['q_19_sequence_action_schemes_4']=$row['q_19_sequence_action_schemes_4'];
            $defaults['q_19_sequence_action_schemes_5']=$row['q_19_sequence_action_schemes_5'];
            $defaults['q_19_sequence_action_schemes_6']=$row['q_19_sequence_action_schemes_6'];
            $defaults['q_19_sequence_action_schemes_raw_score']=$row['q_19_sequence_action_schemes_raw_score'];
            $defaults['q_20_stacks_tower']=$row['q_20_stacks_tower'];
            $defaults['q_20_stacks_tower_raw_score']=$row['q_20_stacks_tower_raw_score'];
            $defaults['object_use_weighted']=$row['object_use_weighted'];
            

            // Set the date
            //  $date = explode('-', $row['aMRI_date']);
            //  $defaults['aMRI_date']['Y'] = $date[0];
            //  $defaults['aMRI_date']['M'] = $date[1];
            //  $defaults['aMRI_date']['d'] = $date[2];

        } else {
            echo("Identifer empty! No ID has been chosen. Please contact Samir at the DCC.<br>");
        }
        
        $sites = array(1 => 'DCC', 2 => 'SEA', 3 => 'PHI', 4 => 'STL', 5 => 'UNC');
        $defaults['reliability_center'] = $sites[$this->reliability_center_id];

        return $defaults;
    }

   
    function score(){

        //holds raw question values
        $score_record = array();
        
        //holds calculated
        $db =& Database::singleton();
        if(PEAR::isError($db)) {
            return PEAR::raiseError ("Could not connect to database: ".$db->getMessage());
        }

        // null scores
        //$this->_nullScores();

        //Get values from both tables of csbs (reliability and original)
        $query = "SELECT * FROM csbs_reliability WHERE CommentID='$this->identifier' AND reliability_center_id = '$this->reliability_center_id'";
        $query1 = "SELECT * FROM csbs WHERE CommentID='".$this->identifier."'";
        $query2 = "SELECT * FROM csbs_wetherby_lookup WHERE CommentID='standard1'";
 
        $db->selectRow($query, $score_record);
        if (PEAR::isError($score_record)) {
            return PEAR::raiseError("Could not get scores: ".$score_record->getMessage());
        }
      
        $db->selectRow($query1, $score_record1);
        if (PEAR::isError($score_record1)) {
            return PEAR::raiseError("Could not get scores: ".$score_record1->getMessage());
        }

        $db->selectRow($query2, $score_record2);
        if (PEAR::isError($score_record2)) {
            return PEAR::raiseError("Could not get scores: ".$score_record2->getMessage());
        }
     
        // Do the actual CSBS scoring (as is done for regular data entry)

        // Calculate raw scores
        $reliability["q_1_gaze_shifts_raw_score"] = $this->_countChecked($score_record, "q_1_gaze_shifts_");
        $reliability["q_2_shared_positive_affect_raw_score"] = $this->_countChecked($score_record, "q_2_shared_positive_affect_");
        $reliability["q_3_gaze_point_following_raw_score"] = $this->_countChecked($score_record, "q_3_gaze_point_following_");

        $score_record["q_4_rate_of_communicating_raw_score"]= NULL;

        foreach($score_record as $field=>$value) {if(ereg("q_4_rate_of_communicating", $field)) {$score_q4 += $value;}}
       
        // what's up with this?
        $reliability["q_4_rate_of_communicating_raw_score"] = $score_q4;
        $reliability["q_5_behaviour_regulation_raw_score"] = $this->_countChecked($score_record, "q_5_behaviour_regulation");
        $reliability["q_6_social_interaction_raw_score"] = $this->_countChecked($score_record, "q_6_social_interaction");
        $reliability["q_7_joint_attention_raw_score"] = $this->_countChecked($score_record, "q_7_joint_attention");
        $reliability["q_8_conventional_gestures_raw_score"] = $this->_countChecked($score_record, "q_8_conventional_gestures_");
        $reliability["q_9_distal_gestures_raw_score"] = $this->_countChecked($score_record, "q_9_distal_gestures_");
        $reliability["q_10_syllables_consonants_raw_score"] = $this->_countChecked($score_record, "q_10_syllables_consonants_"); 
        $reliability["q_11_inventory_of_consonants_raw_score"] = $this->_countChecked($score_record, "q_11_inventory_of_consonants_");
        $reliability["q_12_words_raw_score"] = $this->_countChecked($score_record, "q_12_words_");
        $reliability["q_13_words_raw_score"] = $this->_countWords($score_record, "q_13_words_");
        $reliability["q_14_word_combos_raw_score"] = $this->_countChecked($score_record, "q_14_word_combos_");
        $reliability["q_15_word_combos_raw_score"] = $this->_countWords($score_record, "q_15_word_combos_");
        $reliability["q_16_language_comp_raw_score"] = $this->_countWords($score_record, "q_16_language_");
        $reliability["q_17_action_schemes_raw_score"] = $this->_countChecked($score_record, "q_17_action_schemes_");
        $reliability["q_18_actions_towards_other_raw_score"] = $this->_countWords($score_record, "q_18_actions_towards_other_");
        $reliability["q_19_sequence_action_schemes_raw_score"] = $this->_countWords($score_record, "q_19_sequence_action_schemes_");
        
        // Describe this scoring
        if (is_int(intval(substr($score_record["q_20_stacks_tower"], 0, 1)))) {
            $reliability["q_20_stacks_tower_raw_score"] = intval(substr($score_record["q_20_stacks_tower"], 0, 1));
        } else {$reliability["q_20_stacks_tower_raw_score"] = 0;}
    	
    	// Calculate subscales
        $reliability["emotion_eye_gaze_weighted"] = $reliability["q_1_gaze_shifts_raw_score"] + $reliability["q_2_shared_positive_affect_raw_score"] +
        3 * $reliability["q_3_gaze_point_following_raw_score"];

        $reliability["communication_weighted"] = $reliability["q_4_rate_of_communicating_raw_score"] / 3 + $reliability["q_5_behaviour_regulation_raw_score"] + $reliability["q_6_social_interaction_raw_score"] + $reliability["q_7_joint_attention_raw_score"];

        $reliability['gestures_weighted'] = $reliability["q_8_conventional_gestures_raw_score"] * 2 + $reliability["q_9_distal_gestures_raw_score"];

        $reliability["sounds_weighted"] = $reliability["q_10_syllables_consonants_raw_score"] + 2 * $reliability["q_11_inventory_of_consonants_raw_score"];
        $reliability["words_weighted"] = $reliability["q_12_words_raw_score"] + $reliability["q_13_words_raw_score"] / 2 +  
        $reliability["q_14_word_combos_raw_score"] + $reliability["q_15_word_combos_raw_score"];

        $q_16_language_comp_objects = $this->_countWords($score_record, "q_16_language_comp_objects_");
        $q_16_language_comp_person = $this->_countWords($score_record, "q_16_language_comp_person_");
        $q_16_language_comp_body_parts = $this->_countWords($score_record, "q_16_language_comp_body_parts_");
        
        //enforce cutoffs
        if ($q_16_language_comp_objects > 3) $q_16_language_comp_objects = 3;
        if ($q_16_language_comp_person > 2) $q_16_language_comp_person = 2;
        if ($q_16_language_comp_body_parts > 3) $q_16_language_comp_body_parts = 3;
        

        $reliability["q_16_language_comp_raw_score"]= $q_16_language_comp_objects + $q_16_language_comp_person + $q_16_language_comp_body_parts;

        $reliability["understanding_weighted"] = $q_16_language_comp_objects * 3 + $q_16_language_comp_person * 3 + $q_16_language_comp_body_parts * 3;
        $reliability["object_use_weighted"] = $reliability["q_17_action_schemes_raw_score"] + $reliability["q_18_actions_towards_other_raw_score"] +
        $reliability["q_19_sequence_action_schemes_raw_score"] + $reliability["q_20_stacks_tower_raw_score"];
       
        // If the reliability is to be compared to the wetherby gold standard
         if ($score_record['Gold_standard']=='Gold_standard'){
              echo("This is the Gold standard check<br>");

             $reliability_count=0;            

            // Checking the relevant fields
            if ($score_record2['q_1_gaze_shifts_raw_score']!=$reliability['q_1_gaze_shifts_raw_score']) { 
		//echo("Score q_1_gaze_shifts_raw_score does not match. <br>"); 
		$reliability["q_1_gaze_shifts_raw_score_match"]='N'; 
		$reliability_count++;}
            
	    if ($score_record2['q_2_shared_positive_affect_raw_score']!=$reliability['q_2_shared_positive_affect_raw_score']) { echo("Score q_2_shared_positive_affect_raw_score does not match. <br>"); $reliability['q_2_shared_positive_affect_raw_score_match']='N';$reliability_count++;}
            if ($score_record2['q_3_gaze_point_following_raw_score']!=$reliability['q_3_gaze_point_following_raw_score']) { echo("Score q_3_gaze_point_raw_score does not match.<br>"); $reliability['q_3_gaze_point_following_raw_score_match']='N';$reliability_count++;}
            if ($score_record2['emotion_eye_gaze_weighted']!=$reliability['emotion_eye_gaze_weighted']) { echo("Score emotion_eye_gaze_weighted does not match. <br>"); $reliability['emotion_eye_gaze_weighted_match']='N';}
            if ($score_record2['q_4_rate_of_communicating_raw_score']!=$reliability['q_4_rate_of_communicating_raw_score']) { echo("Score q_4_rate_of_communicating_raw_score does not match. <br>"); $reliability['q_4_rate_of_communicating_raw_score_match']='N';$reliability_count++;}
           if ($score_record2['q_5_behaviour_regulation_raw_score']!=$reliability['q_5_behaviour_regulation_raw_score']) { echo("Score q_5_behaviour_regulation_raw_score does not match. <br>"); $reliability['q_5_behaviour_regulation_raw_score_match']='N';$reliability_count++;}
            if ($score_record2['q_6_social_interaction_raw_score']!=$reliability['q_6_social_interaction_raw_score']) { echo("Score q_6_social_interaction_raw_score does not match. <br>"); $reliability['q_6_social_interaction_raw_score_match']='N';$reliability_count++;}
            if ($score_record2['q_7_joint_attention_raw_score']!=$reliability['q_7_joint_attention_raw_score']) { echo("Score q_7_joint_attention_raw_score does not match. <br>"); $reliability['q_7_joint_attention_raw_score_match']='N';$reliability_count++;}
            if ($score_record2['communication_weighted']!=$reliability['communication_weighted']) { echo("Score communication_weighted does not match. <br>"); $reliability['communication_weighted_match']='N';}
            if ($score_record2['q_8_conventional_gestures_raw_score']!=$reliability['q_8_conventional_gestures_raw_score']) { echo("Score q_8_conventional_gestures_raw_scores  does not match. <br>"); $reliability['q_8_conventional_gestures_raw_score_match']='N';$reliability_count++;}
            if ($score_record2['q_9_distal_gestures_raw_score']!=$reliability['q_9_distal_gestures_raw_score']) { echo("Score q_9_distal_gestures_raw_scores does not match. <br>"); $reliability['q_9_distal_gestures_raw_score_match']='N';$reliability_count++;}
           if ($score_record2['gestures_weighted']!=$reliability['gestures_weighted']) { echo("Score gestures_weighted does not match. <br>"); $reliability['gestures_weighted_match']='N';}
            if ($score_record2['q_10_syllables_consonants_raw_score']!=$reliability['q_10_syllables_consonants_raw_score']) { echo("Score q_10_syllables_consonants_raw_score does not match. <br>"); $reliability['q_10_syllables_consonants_raw_score_match']='N';$reliability_count++;}
           if ($score_record2['q_11_inventory_of_consonants_raw_score']!=$reliability['q_11_inventory_of_consonants_raw_score']) { echo("Score q_11_inventory_of_consonants_raw_score does not match. <br>"); $reliability['q_11_inventory_of_consonants_raw_score_match']='N';$reliability_count++;}
            if ($score_record2['q_12_words_raw_score']!=$reliability['q_12_words_raw_score']) { echo("Score q_12_words_raw_score does not match. <br>"); $reliability['q_12_words_raw_score_match']='N';$reliability_count++;}
            if ($score_record2['q_13_words_raw_score']!=$reliability['q_13_words_raw_score']) { echo("Score q_13_words_raw_score does not match. <br>"); $reliability['q_13_words_raw_score_match']='N';$reliability_count++;}
            if ($score_record2['q_14_word_combos_raw_score']!=$reliability['q_14_word_combos_raw_score']) { echo("Score q_14_word_combos_raw_score does not match. <br>"); $reliability['q_14_word_combos_raw_score_match']='N';$reliability_count++;}
            if ($score_record2['q_15_word_combos_raw_score']!=$reliability['q_15_word_combos_raw_score']) { echo("Score q_15_word_combos_raw_score does not match. <br>"); $reliability['q_15_word_combos_raw_score_match']='N';$reliability_count++;}
            if ($score_record2['words_weighted']!=$reliability['words_weighted']) { echo("Score words_weighted does not match. <br>"); $reliability['words_weighted_match']='N';}
            
            // object names, person names, 
            if ($score_record2['q_16_language_comp_objects']!=$q_16_language_comp_objects) { echo("Score q_16_language_comp_objects does not match. <br>"); 
            //$reliability['q_16_language_comp_objects']='N';
            $reliability_count++;}
            
            if ($score_record2['q_16_language_comp_person']!=$q_16_language_comp_person) { echo("Score q_16_language_comp_person does not match. <br>"); 
            // $reliability['q_16_language_comp_person']='N';
            $reliability_count++;}
            
            if ($score_record2['q_16_language_comp_body_parts']!=$q_16_language_comp_body_parts) { echo("Score q_16_language_comp_body_parts does not match. <br>"); 
            //$reliability['q_16_language_comp_body_parts']='N';
            $reliability_count++;}
            
            //if ($score_record2['q_16_language_comp_raw_score']!=$reliability['q_16_language_comp_raw_score']) { echo("Score q_16_language_comp_objects_raw_score does not match. <br>"); $reliability['q_16_language_comp_raw_score_match']='N';$reliability_count++;}
            //if ($score_record2['q_16_language_comp_body_parts_raw_score']!=$reliability['q_16_language_comp_body_parts_raw_score']) { echo("Score q_16_language_comp_body_parts_raw_score does not match. <br>"); $reliability['q_16_language_comp_body_parts_raw_score_match']='N';$reliability_count++;}
            
            if ($score_record2['understanding_weighted']!=$reliability['understanding_weighted']) { echo("Score understanding_weighted does not match. <br>"); $reliability['understanding_weighted_match']='N';}
            if ($score_record2['q_17_action_schemes_raw_score']!=$reliability['q_17_action_schemes_raw_score']) { echo("Score q_17_action_schemes_raw_scores does not match. <br>"); $reliability['q_17_action_schemes_raw_score_match']='N';$reliability_count++;}
            if ($score_record2['q_18_actions_towards_other_raw_score']!=$reliability['q_18_actions_towards_other_raw_score']) { echo("Score q_18_actions_towards_other_raw_score does not match. <br>"); $reliability['q_18_actions_towards_other_raw_score_match']='N';$reliability_count++;}
            if ($score_record2['q_19_sequence_action_schemes_raw_score']!=$reliability['q_19_sequence_action_schemes_raw_score']) { echo("Score q_19_sequence_action_schemes_raw_score does not match. <br>"); $reliability['q_19_sequence_action_schemes_raw_score_match']='N';$reliability_count++;}
            if ($score_record2['q_20_stacks_tower_raw_score']!=$reliability['q_20_stacks_tower_raw_score']) { echo("Score q_20_stacks_tower does not match. <br>"); $reliability['q_20_stacks_tower_raw_score_match']='N';$reliability_count++;}
            if ($score_record2['object_use_weighted']!=$reliability['object_use_weighted']) { echo("object_use_weighted does not match. <br>"  ); $reliability['object_use_weighted_match']='N';}
            
            // Score the reliability
            $reliability['reliability_score']= ((22-$reliability_count)/22*100);
            
         } // endif
         
         // If the reliability is to be compared to the initial data entry
         elseif ($score_record['Gold_standard']=='Initial_entry') {
             echo("This is the initial check.");
             
             $reliability_count=0;            

            // Checking the relevant fields
            if ($score_record1['q_1_gaze_shifts_raw_score']!=$reliability['q_1_gaze_shifts_raw_score']) { echo("Score q_1_gaze_shifts_raw_score does not match. <br>"); $reliability['q_1_gaze_shifts_raw_score_match']='N'; $reliability_count++;}
            if ($score_record1['q_2_shared_positive_affect_raw_score']!=$reliability['q_2_shared_positive_affect_raw_score']) { echo("Score q_2_shared_positive_affect_raw_score does not match. <br>"); $reliability['q_2_shared_positive_affect_raw_score_match']='N';$reliability_count++;}
            if ($score_record1['q_3_gaze_point_following_raw_score']!=$reliability['q_3_gaze_point_following_raw_score']) { echo("Score q_3_gaze_point_raw_score does not match.<br>"); $reliability['q_3_gaze_point_following_raw_score_match']='N';$reliability_count++;}
            if ($score_record1['emotion_eye_gaze_weighted']!=$reliability['emotion_eye_gaze_weighted']) { echo("Score emotion_eye_gaze_weighted does not match. <br>"); $reliability['emotion_eye_gaze_weighted_match']='N';}
            if ($score_record1['q_4_rate_of_communicating_raw_score']!=$reliability['q_4_rate_of_communicating_raw_score']) { echo("Score q_4_rate_of_communicating_raw_score does not match. <br>"); $reliability['q_4_rate_of_communicating_raw_score_match']='N';$reliability_count++;}
           if ($score_record1['q_5_behaviour_regulation_raw_score']!=$reliability['q_5_behaviour_regulation_raw_score']) { echo("Score q_5_behaviour_regulation_raw_score does not match. <br>"); $reliability['q_5_behaviour_regulation_raw_score_match']='N';$reliability_count++;}
            if ($score_record1['q_6_social_interaction_raw_score']!=$reliability['q_6_social_interaction_raw_score']) { echo("Score q_6_social_interaction_raw_score does not match. <br>"); $reliability['q_6_social_interaction_raw_score_match']='N';$reliability_count++;}
            if ($score_record1['q_7_joint_attention_raw_score']!=$reliability['q_7_joint_attention_raw_score']) { echo("Score q_7_joint_attention_raw_score does not match. <br>"); $reliability['q_7_joint_attention_raw_score_match']='N';$reliability_count++;}
            if ($score_record1['communication_weighted']!=$reliability['communication_weighted']) { echo("Score communication_weighted does not match. <br>"); $reliability['communication_weighted_match']='N';}
            if ($score_record1['q_8_conventional_gestures_raw_score']!=$reliability['q_8_conventional_gestures_raw_score']) { echo("Score q_8_conventional_gestures_raw_scores  does not match. <br>"); $reliability['q_8_conventional_gestures_raw_score_match']='N';$reliability_count++;}
            if ($score_record1['q_9_distal_gestures_raw_score']!=$reliability['q_9_distal_gestures_raw_score']) { echo("Score q_9_distal_gestures_raw_scores does not match. <br>"); $reliability['q_9_distal_gestures_raw_score_match']='N';$reliability_count++;}
           if ($score_record1['gestures_weighted']!=$reliability['gestures_weighted']) { echo("Score gestures_weighted does not match. <br>"); $reliability['gestures_weighted_match']='N';}
            if ($score_record1['q_10_syllables_consonants_raw_score']!=$reliability['q_10_syllables_consonants_raw_score']) { echo("Score q_10_syllables_consonants_raw_score does not match. <br>"); $reliability['q_10_syllables_consonants_raw_score_match']='N';$reliability_count++;}
           if ($score_record1['q_11_inventory_of_consonants_raw_score']!=$reliability['q_11_inventory_of_consonants_raw_score']) { echo("Score q_11_inventory_of_consonants_raw_score does not match. <br>"); $reliability['q_11_inventory_of_consonants_raw_score_match']='N';$reliability_count++;}
            if ($score_record1['q_12_words_raw_score']!=$reliability['q_12_words_raw_score']) { echo("Score q_12_words_raw_score does not match. <br>"); $reliability['q_12_words_raw_score_match']='N';$reliability_count++;}
            if ($score_record1['q_13_words_raw_score']!=$reliability['q_13_words_raw_score']) { echo("Score q_13_words_raw_score does not match. <br>"); $reliability['q_13_words_raw_score_match']='N';$reliability_count++;}
            if ($score_record1['q_14_word_combos_raw_score']!=$reliability['q_14_word_combos_raw_score']) { echo("Score q_14_word_combos_raw_score does not match. <br>"); $reliability['q_14_word_combos_raw_score_match']='N';$reliability_count++;}
            if ($score_record1['q_15_word_combos_raw_score']!=$reliability['q_15_word_combos_raw_score']) { echo("Score q_15_word_combos_raw_score does not match. <br>"); $reliability['q_15_word_combos_raw_score_match']='N';$reliability_count++;}
            if ($score_record1['words_weighted']!=$reliability['words_weighted']) { echo("Score words_weighted does not match. <br>"); $reliability['words_weighted_match']='N';}
            
            // object names, person names, 
            if ($score_record1['q_16_language_comp_objects']!=$q_16_language_comp_objects) { echo("Score q_16_language_comp_objects does not match. <br>"); 
            //$reliability['q_16_language_comp_objects']='N';
            $reliability_count++;}
            
            if ($score_record1['q_16_language_comp_person']!=$q_16_language_comp_person) { echo("Score q_16_language_comp_person does not match. <br>"); 
            // $reliability['q_16_language_comp_person']='N';
            $reliability_count++;}
            
            if ($score_record1['q_16_language_comp_body_parts']!=$q_16_language_comp_body_parts) { echo("Score q_16_language_comp_body_parts does not match. <br>"); 
            //$reliability['q_16_language_comp_body_parts']='N';
            $reliability_count++;}
            
            //if ($score_record1['q_16_language_comp_raw_score']!=$reliability['q_16_language_comp_raw_score']) { echo("Score q_16_language_comp_objects_raw_score does not match. <br>"); $reliability['q_16_language_comp_raw_score_match']='N';$reliability_count++;}
            //if ($score_record1['q_16_language_comp_body_parts_raw_score']!=$reliability['q_16_language_comp_body_parts_raw_score']) { echo("Score q_16_language_comp_body_parts_raw_score does not match. <br>"); $reliability['q_16_language_comp_body_parts_raw_score_match']='N';$reliability_count++;}
            
            if ($score_record1['understanding_weighted']!=$reliability['understanding_weighted']) { echo("Score understanding_weighted does not match. <br>"); $reliability['understanding_weighted_match']='N';}
            if ($score_record1['q_17_action_schemes_raw_score']!=$reliability['q_17_action_schemes_raw_score']) { echo("Score q_17_action_schemes_raw_scores does not match. <br>"); $reliability['q_17_action_schemes_raw_score_match']='N';$reliability_count++;}
            if ($score_record1['q_18_actions_towards_other_raw_score']!=$reliability['q_18_actions_towards_other_raw_score']) { echo("Score q_18_actions_towards_other_raw_score does not match. <br>"); $reliability['q_18_actions_towards_other_raw_score_match']='N';$reliability_count++;}
            if ($score_record1['q_19_sequence_action_schemes_raw_score']!=$reliability['q_19_sequence_action_schemes_raw_score']) { echo("Score q_19_sequence_action_schemes_raw_score does not match. <br>"); $reliability['q_19_sequence_action_schemes_raw_score_match']='N';$reliability_count++;}
            if ($score_record1['q_20_stacks_tower_raw_score']!=$reliability['q_20_stacks_tower_raw_score']) { echo("Score q_20_stacks_tower does not match. <br>"); $reliability['q_20_stacks_tower_raw_score_match']='N';$reliability_count++;}
            if ($score_record1['object_use_weighted']!=$reliability['object_use_weighted']) { echo("object_use_weighted does not match. <br>"  ); $reliability['object_use_weighted_match']='N';}
            
            // Score the reliability
            $reliability['reliability_score']= ((22-$reliability_count)/22*100);
            


        }
              
        // end elseif
        else {
            echo("what the heck is going on?<br>");
        } // end else
        
        // Calculate the scoring reliability

        // print_r($this->identifier);

        // Do the update here for the relibaility scores - saving the scores
		$result = $db->update("csbs_reliability", $reliability, array("CommentID"=>$this->identifier, "reliability_center_id" => $this->reliability_center_id));
		if($db->isError($result)) {
			return PEAR::raiseError("Could not save total score: ". $result->getMessage());
		}
    
      $result = $db->update("reliability", array('Reliability_score' => $reliability['reliability_score']), array("CommentID"=>$this->identifier, "Instrument" => 'csbs', "reliability_center_id" => $this->reliability_center_id));
		if($db->isError($result)) {
			return PEAR::raiseError("Could not save total score: ". $result->getMessage());
		}
/*	 // Update the main relibaility table with the overall reliability score 
                $result1 = $db->update("reliability", $reliability['reliability_score'], array("CommentID"=>$this->identifier));
                if($db->isError($result1)) {
                        return PEAR::raiseError("Could not save total score: ". $result1->getMessage());
                }
*/

    } // end function score
           
    function _countChecked($record, $genericLabel) {
        foreach ($record as $field=>$value) {
            if (ereg($genericLabel, $field)) {
                $score += ($value == "checked");
            }
        }
        return $score;
    }

    function _countWords($record, $genericLabel) {
        foreach($record as $field=>$value) {
            if(ereg($genericLabel, $field) && !is_null($value)) {
                $score++; 
            }
        }
        return $score;
    }
    
    function _nullScores()
    {
        $db=& Database::singleton();
        if (PEAR::isError($db)) {
            return PEAR::raiseError("Could not connect to database: ".$db->getMessage()."\n");
        }
        
        // set the scores to NULL
        foreach ($this->scores as $val) {
            $scores[$val]=null;
        }

        // update the scores
        $success = $db->update("csbs_reliability",$scores,array("CommentID"=>$this->identifier, "reliability_center_id" => $this->reliability_center_id));
        if (PEAR::isError($success)) {
            return PEAR::raiseError("DB Error, fail null the scores:\n".$success->getMessage()."\n");
        }
        return;
    }    


    function csbs_reliability()
    {
       $this->_addMetadataFields();
       $this->form->addElement("static", "reliability_center", "Site of Reliability Test:");
       
        //Scoring header
        $this->form->addElement('header', 'instrument_title', "Scoring:");
        $this->form->addElement("static", "reliability_score", "Reliability Score (%):");

        //display test name
        $this->form->addElement('header', 'instrument_title', "Communication and Symbolic Behaviour Scales - Development Profile");
        
        // automatically adds examiner & date of administration
        //         $this->_addMetadataFields();
        //         $this->addTextElement("filled_out_by", "Filled out by:");
        //         $this->addTextElement("relationship_to_child", "Relationship to child:");

        $GoldStandardArray = array("Initial_entry"=>"Initial Entry", "Gold_standard"=>"Gold standard" );
       
        $this->form->addElement("select", "Gold_standard", "Compare against:", $GoldStandardArray);
        $this->form->addElement("static", "CommentID", "CommentID:");
        //$this->form->addElement("static", q_1_gaze_shifts_raw_score_match, "q_1_gaze_shifts_raw_score_match:" );

	// This section does not seem to be necessary for the reliability
/* 	 $this->form->addElement("static", null, "Circle the response that comes closest to your observations.");
        $this->form->addElement("select", "q_1_alertness", "1. Alertness", array(null=>"", "1_less_than_usual"=>"1. less than usual/sleepy", "2_typical"=>"2. typical", "3_very_alert_greater"=>"3. very alert / greater than usual", "not_answered"=>"Not Answered"));
        $this->form->addElement("select", "q_2_emotional_reaction", "2. Emotional reaction", array(null=>"", "1_more_negative"=>"1. more negative than usual", "2_typical"=>"2. typical", "3_more_positive"=>"3. more positive than usual", "not_answered"=>"Not Answered"));
        $this->form->addElement("select", "q_3_level_of_interest", "3. Level of interest and attention", array(null=>"", "1_less_interest"=>"1. less interest than usual", "2_typical"=>"2. typical", "3_greater"=>"3. greater interest / greater attention", "not_answered"=>"Not Answered"));
        $this->form->addElement("select", "q_4_comfort_level", "4. Comfort level", array(null=>"", "1_more_cautious"=>"1. more cautious", "2_typical"=>"2. typical", "3_more_comfortable"=>"3. more confortable", "not_answered"=>"Not Answered"));
        $this->form->addElement("select", "q_5_level_of_activity", "5. Level of activity", array(null=>"", "1_less_active"=>"1. less active than usual", "2_typical"=>"2. typical", "3_more_active"=>"3. more active than usual", "not_answered"=>"Not Answered"));
        $this->form->addElement("select", "q_6_level_of_communication", "6. Overall level of communication", array(null=>"", "1_less_than_usual"=>"1. less than usual", "2_typical"=>"2. typical", "3_greater_than_usual"=>"3. greater than usual", "not_answered"=>"Not Answered"));
        $this->form->addElement("select", "q_7_play_behaviour", "7. Play behavior", array(null=>"", "1_less_organized"=>"1. less organized", "2_typical"=>"2. typical", "3_more_organized"=>"3. more organized", "not_answered"=>"Not Answered"));
        $this->form->addElement("select", "q_", "", array(null=>"", "1_"=>"1. ", "2_typical"=>"2. typical", "3_"=>"3. ", "not_answered"=>"Not Answered"));

        // $this->addTextAreaElement("comments", "Comments:");   

       // Setting up the scoring grid
        for($int = 1; $int <= 6; $int++) {
            $group[]= &$this->form->createElement("static", "h_" . $int, null);
        }
        $group[]= &$this->form->createElement("static", "raw_score", null);
        $this->form->addGroup($group, "number_headers", "Sampling Opportunity", $this->_GUIDelimiter, false);
        unset($group);

        $group[]= &$this->form->createElement("static", "wind_up_toy", null);
        $group[]= &$this->form->createElement("static", "balloon", null);
        $group[]= &$this->form->createElement("static", "bubbles", null);
        $group[]= &$this->form->createElement("static", "jar", null);
        $group[]= &$this->form->createElement("static", "books", null);
        $group[]= &$this->form->createElement("static", "play", null);
        $this->form->addGroup($group, null, "Toy", $this->_GUIDelimiter, false);
        unset($group);

*/
        
        //line break
        $this->form->addElement("static", null, $this->indent);
        
        //Emotion and Eye Gaze
        $this->form->addElement("header", null, "Emotion and Eye Gaze");
        for($int = 1; $int <= 6; $int++) {
            $group[] = &$this->form->createElement("advcheckbox", "q_1_gaze_shifts_" . $int, null, null, null, array("unchecked", "checked"));
        }
        $group[] = &$this->form->createElement("static", "q_1_gaze_shifts_raw_score");
        $this->form->addGroup($group, null, "1. Gaze shifts", $this->_GUIDelimiter, false);
        unset($group);
        
        for($int = 1; $int <= 6; $int++) {
            $group[] = &$this->form->createElement("advcheckbox", "q_2_shared_positive_affect_" . $int, null, null, null, array("unchecked", "checked"));
        }
        $group[] = &$this->form->createElement("static", "q_2_shared_positive_affect_raw_score");
        $this->form->addGroup($group, null, "2. Shared positive affect", $this->_GUIDelimiter, false);
        unset($group);
        
        $group[] = &$this->form->createElement("static", null, null);
        $group[] = &$this->form->createElement("advcheckbox", "q_3_gaze_point_following_2", null, null, null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("static", null, null);
        $group[] = &$this->form->createElement("static", null, null);
        $group[] = &$this->form->createElement("advcheckbox", "q_3_gaze_point_following_5", null, null, null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("static", null, null);
        $group[] = &$this->form->createElement("static", "q_3_gaze_point_following_raw_score");

        $this->form->addGroup($group, null, "3. Gaze/point following", $this->_GUIDelimiter, false);
        unset($group);
        
        $this->form->addElement("static", "emotion_eye_gaze_weighted", "Emotion and Eye Gaze Weighted:");
        
        //Communication
        $this->form->addElement("header", null, "Communication");
        for($int = 1; $int <=6; $int++) {
            $group[] = &$this->form->createElement("select", "q_4_rate_of_communicating_" . $int, "", array(null=>"", "not_answered"=>"N/A", "0"=>"0", "1"=>"1", "2"=>"2", "3"=>"3+"));
            //  $this->XINRegisterRule("q_4_rate_of_communicating_" . $int, array("q_4_rate_of_communicating_" . $int . "{@}=={@}"), "Responses are required for each sampling opportunity.", "q_4_rate_of_communicating_group");
        }
        $group[] = &$this->form->createElement("static", "q_4_rate_of_communicating_raw_score");
        $this->form->addGroup($group, "q_4_rate_of_communicating_group", "4. Rate of communication", $this->_GUIDelimiter, false);
        unset($group);
        
        for($int = 1; $int <= 6; $int++) {
            $group[] = &$this->form->createElement("advcheckbox", "q_5_behaviour_regulation_" . $int, null, null, null, array("unchecked", "checked"));
        }
        $group[] = &$this->form->createElement("static", "q_5_behaviour_regulation_raw_score");
        $this->form->addGroup($group, null, "5. Behaviour regulation", $this->_GUIDelimiter, false);
        unset($group);

        for($int = 1; $int <= 6; $int++) {
            $group[] = &$this->form->createElement("advcheckbox", "q_6_social_interaction_" . $int, null, null, null, array("unchecked", "checked"));
        }
        $group[] = &$this->form->createElement("static", "q_6_social_interaction_raw_score");
        $this->form->addGroup($group, null, "6. Social interaction", $this->_GUIDelimiter, false);
        unset($group);
        
        for($int = 1; $int <= 6; $int++) {
            $group[] = &$this->form->createElement("advcheckbox", "q_7_joint_attention_" . $int, null, null, null, array("unchecked", "checked"));
        }
        $group[] = &$this->form->createElement("static", "q_7_joint_attention_raw_score");
        $this->form->addGroup($group, null, "7. Joint attention", $this->_GUIDelimiter, false);
        unset($group);
        
        $this->form->addElement("static", "communication_weighted", "Communication Weighted:");

        //Gestures
        $this->form->addElement("header", null, "Gestures");
        $group[] = &$this->form->createElement("advcheckbox", "q_8_conventional_gestures_gives", null, "gives", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_8_conventional_gestures_shows", null, "shows", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_8_conventional_gestures_pushes_pulls", null, "pushes/pulls", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_8_conventional_gestures_reaches", null, "reaches", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("static", null, null);
        $group[] = &$this->form->createElement("static", null, null);
        $group[] = &$this->form->createElement("static", "q_8_conventional_gestures_raw_score");
        $this->form->addGroup($group, null, "8. Inventory of conventional gestures", $this->_GUIDelimiter, false);
        unset($group);
        $group[] = &$this->form->createElement("advcheckbox", "q_8_conventional_gestures_points", null, "points", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_8_conventional_gestures_waves", null, "waves", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_8_conventional_gestures_nods_head", null, "nods head", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_8_conventional_gestures_shakes_head", null, "shakes head", null, array("unchecked", "checked"));
        $this->form->addGroup($group, null, null, $this->_GUIDelimiter, false);
        unset($group);

        for($int = 1; $int <=6; $int++) {
            $group[] = &$this->form->createElement("advcheckbox", "q_9_distal_gestures_" . $int, null, null, null, array("unchecked", "checked"));
        }
        $group[] = &$this->form->createElement("static", "q_9_distal_gestures_raw_score");
        $this->form->addGroup($group, null, "9. Distal gestures", $this->_GUIDelimiter, false);
        unset($group);
        
        $this->form->addElement("static", "gestures_weighted", "Gestures Weighted:");

        //Sounds
        $this->form->addElement("header", null, "Sounds");
        for($int = 1; $int <=6; $int++) {
            $group[] = &$this->form->createElement("advcheckbox", "q_10_syllables_consonants_" . $int, null, null, null, array("unchecked", "checked"));
        }
        $group[] = &$this->form->createElement("static", "q_10_syllables_consonants_raw_score");
        $this->form->addGroup($group, null, "10. Syllables with consonants", $this->_GUIDelimiter, false);
        unset($group);
        
        $group[] = &$this->form->createElement("advcheckbox", "q_11_inventory_of_consonants_m", null, "/m/", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_11_inventory_of_consonants_n", null, "/n/", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_11_inventory_of_consonants_b_p", null, "/b|p/", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_11_inventory_of_consonants_d_t", null, "/d|t/", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_11_inventory_of_consonants_g_k", null, "/g|k/", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("static", null, null);
        $group[] = &$this->form->createElement("static", "q_11_inventory_of_consonants_raw_score");
        $this->form->addGroup($group, null, "11. Inventory of consonants", $this->_GUIDelimiter, false);
        unset($group);
        
        $group[] = &$this->form->createElement("advcheckbox", "q_11_inventory_of_consonants_w", null, "/w/", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_11_inventory_of_consonants_l", null, "/l/", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_11_inventory_of_consonants_y", null, "/y/", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_11_inventory_of_consonants_s", null, "/s/", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_11_inventory_of_consonants_sh", null, "/sh/", null, array("unchecked", "checked"));
        $this->form->addGroup($group, null, null, $this->_GUIDelimiter, false);
        unset($group);

        $this->form->addElement("static", "sounds_weighted", "Sounds Weighted:");

        //Words
        $this->form->addElement("header", null, "Words");
        for($int = 1; $int <=6; $int++) {
            $group[] = &$this->form->createElement("advcheckbox", "q_12_words_" . $int, null, null, null, array("unchecked", "checked"));
        }
        $group[] = &$this->form->createElement("static", "q_12_words_raw_score");
        $this->form->addGroup($group, null, "12. Words", $this->_GUIDelimiter, false);
        unset($group);
        
        for($row = 0; $row <= 3; $row++) {
            for($col = 1; $col <= 4; $col++) {
                $group[] = &$this->form->createElement("text", "q_13_words_" . ($col + ($row * 4)) );
            }
            if ($row == 0) {
                $label = "13. Inventory of words";
                $group[] = &$this->form->createElement("static", null, null);
                $group[] = &$this->form->createElement("static", null, null);
                $group[] = &$this->form->createElement("static", "q_13_words_raw_score");
            } else {$label = null;}
            $this->form->addGroup($group, "q_13_words_{$row}_group", $label, $this->_GUIDelimiter, false);
            unset($group);
            for($int = 1; $int <= 16; $int++) {
                //   $this->XINRegisterRule("q_13_words_" . $int, array("q_13_words_" . $int . "{@}=={@}NEVER_REQUIRED"), null, "q_13_words_" . intval($int / 4) . "_group");
            }
        }

        for($int = 1; $int <=6; $int++) {
            $group[] = &$this->form->createElement("advcheckbox", "q_14_word_combos_" . $int, null, null, null, array("unchecked", "checked"));
        }
        $group[] = &$this->form->createElement("static", "q_14_word_combos_raw_score");
        $this->form->addGroup($group, null, "14. Word combinations", $this->_GUIDelimiter, false);
        unset($group);
        
        for($row = 0; $row <= 3; $row++) {
            for($col = 1; $col <= 2; $col++) {
                $group[] = &$this->form->createElement("text", "q_15_word_combos_" . ($col + ($row * 2)) );
            }
            if ($row == 0) {$label = "15. Inventory of word combos";
                $group[] = &$this->form->createElement("static", null, null);
                $group[] = &$this->form->createElement("static", null, null);
                $group[] = &$this->form->createElement("static", null, null);
                $group[] = &$this->form->createElement("static", null, null);
                $group[] = &$this->form->createElement("static", "q_15_word_combos_raw_score");
            } else {$label = null;}
            $this->form->addGroup($group, "q_15_word_combos_{$row}_group", $label, $this->_GUIDelimiter, false);
            unset($group);
            for($int = 1; $int <= 8; $int++) {
                //  $this->XINRegisterRule("q_15_word_combos_" . $int, array("q_15_word_combos_" . $int . "{@}=={@}NEVER_REQUIRED"), null, "q_15_word_combos_" . intval($int / 2) . "_group");
            }
        }

        $this->form->addElement("static", "words_weighted", "Words Weighted:");

        // Setting up the 6 column grid
        for($int = 1; $int <= 6; $int++) {
            $group[]= &$this->form->createElement("static", null, $this->indent);
        }
        $group[] = &$this->form->createElement("static", null, null);
        $group[]= &$this->form->createElement("static", "raw_score", null);
        $this->form->addGroup($group, null, null, $this->_GUIDelimiter, false);
        unset($group);
        
        //Understanding
        $this->form->addElement("header", null, "Understanding");
        $group[] = &$this->form->createElement("static", "object_names", null);
        for($col = 1; $col <= 4; $col++) {
            $group[] = &$this->form->createElement("text", "q_16_language_comp_objects_" . $col);
            //  $this->XINRegisterRule("q_16_language_comp_objects_" . $col, array("q_16_language_comp_objects_" . $col . "{@}=={@}NEVER_REQUIRED"), null, "q_16_language_comp_objects_group");
        }
        $group[] = &$this->form->createElement("static", null, null);
        $group[] = &$this->form->createElement("static", null, null);
        $group[] = &$this->form->createElement("static", "q_16_language_comp_raw_score");
        $this->form->addGroup($group, "q_16_language_comp_objects_group", "16. Language comprehension" . $this->indent, $this->_GUIDelimiter, false);
        unset($group);
        
        $group[] = &$this->form->createElement("static", "person_names", null);
        for($col = 1; $col <= 3; $col++) {
            $group[] = &$this->form->createElement("text", "q_16_language_comp_person_" . $col);
            //   $this->XINRegisterRule("q_16_language_comp_person_" . $col, array("q_16_language_comp_person_" . $col . "{@}=={@}NEVER_REQUIRED"), null, "q_16_language_comp_person_group");
        }
        $this->form->addGroup($group, "q_16_language_comp_person_group", null, $this->_GUIDelimiter, false);
        unset($group);

        $group[] = &$this->form->createElement("static", "body_parts", null);
        for($col = 1; $col <= 4; $col++) {
            $group[] = &$this->form->createElement("text", "q_16_language_comp_body_parts_" . $col);
            //   $this->XINRegisterRule("q_16_language_comp_body_parts_" . $col, array("q_16_language_comp_body_parts_" . $col . "{@}=={@}NEVER_REQUIRED"), null, "q_16_language_comp_body_parts_group");
        }
        $group[] = &$this->form->createElement("static", "q_16_language_comp_body_parts_raw_score");
        $this->form->addGroup($group, "q_16_language_comp_body_parts_group", null, $this->_GUIDelimiter, false);
        unset($group);

        $this->form->addElement("static", "understanding_weighted", "Understanding Weighted:");
        
        //Object Use
        $this->form->addElement("header", null, "Object Use");
        $group[] = &$this->form->createElement("advcheckbox", "q_17_action_schemes_puts_in", null, "puts in(1)", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_17_action_schemes_puts_on", null, "puts on(2)", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_17_action_schemes_drinks_with_bottle", null, "drinks with bottle(3)", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_17_action_schemes_drinks_with_cup", null, "drinks with cup(4)", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_17_action_schemes_hugs", null, "hugs(5)", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_17_action_schemes_kisses", null, "kisses(6)", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("static", null, null);
        $group[] = &$this->form->createElement("static", "q_17_action_schemes_raw_score");
        $this->form->addGroup($group, null, "17. Inventory of action schemes", $this->_GUIDelimiter, false);
        unset($group);

        $group[] = &$this->form->createElement("advcheckbox", "q_17_action_schemes_feeds_with_utensil", null, "feeds with utensil(7)", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_17_action_schemes_feeds_with_bowl", null, "feeds with bowl(8)", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_17_action_schemes_stirs", null, "stirs(9)", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_17_action_schemes_scoops", null, "scoops(10)", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_17_action_schemes_pours", null, "pours(11)", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("advcheckbox", "q_17_action_schemes_other", null, "other(12)", null, array("unchecked", "checked"));
        $group[] = &$this->form->createElement("text", "q_17_action_schemes_other_specify");
        $this->form->addGroup($group, "q_17_action_schemes_group_2", null, $this->_GUIDelimiter, false);
        // $this->XINRegisterRule("q_17_action_schemes_other_specify", array("q_17_action_schemes_other_specify{@}=={@}NEVER_REQUIRED"), null, "q_17_action_schemes_group_2");
        unset($group);
        
        //Action schemes towards other
        for($int = 1; $int <= 6; $int++) {
            $group[] = &$this->form->createElement("text", "q_18_actions_towards_other_" . $int, null);
        }
        $group[] = &$this->form->createElement("static", null, null);
        $group[] = &$this->form->createElement("static", "q_18_actions_towards_other_raw_score");
        $this->form->addGroup($group, "q_18_actions_towards_other_group", "18. Action schemes towards other", $this->_GUIDelimiter, false);
        unset($group);
        for($int = 1; $int <= 6; $int++) {
            //   $this->XINRegisterRule("q_18_actions_towards_other_" . $int, array("q_18_actions_towards_other_" . $int . "{@}=={@}NEVER_REQUIRED"), null, "q_18_actions_towards_other_group");
        }
        
        //Sequence action schemes
        for($int = 1; $int <= 6; $int++) {
            $group[] = &$this->form->createElement("text", "q_19_sequence_action_schemes_" . $int, null);
        }
        $group[] = &$this->form->createElement("static", null, null);
        $group[] = &$this->form->createElement("static", "q_19_sequence_action_schemes_raw_score");
        $this->form->addGroup($group, "q_19_sequence_action_schemes_group", "19. Sequence action schemes", $this->_GUIDelimiter, false);
        unset($group);
        for($int = 1; $int <= 6; $int++) {
            //    $this->XINRegisterRule("q_19_sequence_action_schemes_" . $int, array("q_19_sequence_action_schemes_" . $int . "{@}=={@}NEVER_REQUIRED"), null, "q_19_sequence_action_schemes_group");
        }
        
        //Stacks tower of blocks
        $group[] = &$this->form->createElement("select", "q_20_stacks_tower", "20. Stacks tower of blocks", array(null=>"", "0_refuses"=>"0 - Refuses",
                                "1_tries_but_fails"=>"1 - Tries but fails",
                                "2_stacks"=>"Stacks 2",
                                "3_stacks"=>"Stacks 3",
                                "4_stacks"=>"Stacks 4",
                                "5_stacks"=>"Stacks 5",
                                "not_answered"=>"Not Answered"));
        $group[] = &$this->form->createElement("static", null, null);
        $group[] = &$this->form->createElement("static", null, null);
        $group[] = &$this->form->createElement("static", null, null);
        $group[] = &$this->form->createElement("static", null, null);
        $group[] = &$this->form->createElement("static", null, null);
        $group[] = &$this->form->createElement("static", null, null);
        $group[] = &$this->form->createElement("static", "q_20_stacks_tower_raw_score");
        $this->form->addGroup($group, "q_20_stacks_tower_group", "20. Stacks tower of blocks", $this->_GUIDelimiter, false);
        unset($group); 

        $this->form->addElement("static", "object_use_weighted", "Object Use Weighted:");


        $this->redirect = "test_name=$this->name"; // what does this do?
        
        //------------------------------------------------------------
       
       //  //Take this out
//         // put this into csbs_reliability function
//         $renderer =& new HTML_QuickForm_Renderer_Default();
//         $renderer->setFormTemplate("<form{attributes}><table class=\"instrument\">{content}</table></form>");
//         $renderer->setElementTemplate("<tr><td class=\"lab\"><!-- BEGIN required --><span style=\"color: #ff0000\">*</span><!-- END required -->{label}</td><td class=\"ele\"><!-- BEGIN error --><span style=\"color: #ff0000\">{error}</span><br /><!-- END error -->{element}</td></tr>");
//         $renderer->setElementTemplate("<tr><td class=\"lab\"><i>{label}</i></td><td class=\"ele\">\t<i>{element}</i></td></tr>", "static");
//         $renderer->setHeaderTemplate("<tr><th colspan=\"2\"><br><b>{header}</b></th></tr>");
//         $this->form->accept($renderer);
//         $this->tpl_data['tempFormHTML'] = $renderer->toHtml();

//         // My get defaults function sets $defaults array
//         $localDefaults = $this->_getDefaults();
//         if (PEAR::isError($localDefaults)) {
//             return PEAR::raiseError("NDB_Form::display(): ".$localDefaults->getMessage());
//         }
//         if(!is_array($localDefaults)) { $localDefaults = array(); }


//         $this->form->setDefaults($this->defaults);
//     	$this->form->applyFilter('__ALL__', 'trim');


    } // End function tracking_log
      

 function _process($values)
    {
        $DB =& Database::singleton();
        if(PEAR::isError($DB)) {
            return PEAR::raiseError("Could not connect to database: ".$DB->getMessage());
        }

        $user =& User::singleton();
        // if(!$user->hasPermission('tracking_logs_edit_all')) {
        //    $values['Lock_record'] = 'Locked';
        // }
              
        $DB->selectRow("SELECT * FROM csbs_reliability WHERE CommentID = '$this->identifier' AND reliability_center_id = $this->reliability_center_id", $row);
          if (PEAR::isError($row)) {
              return PEAR::raiseError("DB Error: ".$row->getMessage());
          }

          if (empty($row)) {
            
            // insert the event
            $success = $DB->insert('csbs_reliability', array(
                                                             'CommentID' => $this->identifier,
                                                             'Examiner' => $values['Examiner'],
                                                              'Date_taken' => $this->_getDatabaseDate($values['Date_taken']),
                                                              'Gold_standard' => $values['Gold_standard'],
                                                              "reliability_center_id" => $this->reliability_center_id,
                                                             'q_1_alertness' => $values['q_1_alertness'],
                                                             'q_2_emotional_reaction' => $values['q_2_emotional_reaction'],
                                                             'q_3_level_of_interest' => $values['q_3_level_of_interest'], 
                                                             'q_4_comfort_level' => $values['q_4_comfort_level'],
                                                             'q_5_level_of_activity' => $values['q_5_level_of_activity'],
                                                             'q_6_level_of_communication' => $values['q_6_level_of_communication'],
                                                             'q_7_play_behaviour' => $values['q_7_play_behaviour'],
                                                             'q_1_gaze_shifts_1'=> $values['q_1_gaze_shifts_1'],
                                                             'q_1_gaze_shifts_2'=> $values['q_1_gaze_shifts_2'],
                                                             'q_1_gaze_shifts_3'=> $values['q_1_gaze_shifts_3'],
                                                             'q_1_gaze_shifts_4'=> $values['q_1_gaze_shifts_4'],
                                                             'q_1_gaze_shifts_5'=> $values['q_1_gaze_shifts_5'],
                                                             'q_1_gaze_shifts_6'=> $values['q_1_gaze_shifts_6'],
                                                             'q_2_shared_positive_affect_1'=> $values['q_2_shared_positive_affect_1'],
                                                             'q_2_shared_positive_affect_2'=> $values['q_2_shared_positive_affect_2'],
                                                             'q_2_shared_positive_affect_3'=> $values['q_2_shared_positive_affect_3'],
                                                             'q_2_shared_positive_affect_4'=> $values['q_2_shared_positive_affect_4'],
                                                             'q_2_shared_positive_affect_5'=> $values['q_2_shared_positive_affect_5'],
                                                             'q_2_shared_positive_affect_6'=> $values['q_2_shared_positive_affect_6'],
                                                             'q_3_gaze_point_following_2'=> $values['q_3_gaze_point_following_2'],
                                                             'q_3_gaze_point_following_5'=> $values['q_3_gaze_point_following_5'],
                                                             'q_4_rate_of_communicating_1'=> $values['q_4_rate_of_communicating_1'],
                                                             'q_4_rate_of_communicating_2'=> $values['q_4_rate_of_communicating_2'],
                                                             'q_4_rate_of_communicating_3'=> $values['q_4_rate_of_communicating_3'],
                                                             'q_4_rate_of_communicating_4'=> $values['q_4_rate_of_communicating_4'],
                                                             'q_4_rate_of_communicating_5'=> $values['q_4_rate_of_communicating_5'],
                                                             'q_4_rate_of_communicating_6'=> $values['q_4_rate_of_communicating_6'],
                                                             'q_5_behaviour_regulation_1'=> $values['q_5_behaviour_regulation_1'],
                                                             'q_5_behaviour_regulation_2'=> $values['q_5_behaviour_regulation_2'],
                                                             'q_5_behaviour_regulation_3'=> $values['q_5_behaviour_regulation_3'],
                                                             'q_5_behaviour_regulation_4'=> $values['q_5_behaviour_regulation_4'],
                                                             'q_5_behaviour_regulation_5'=> $values['q_5_behaviour_regulation_5'],
                                                             'q_5_behaviour_regulation_6'=> $values['q_5_behaviour_regulation_6'],
                                                             'q_6_social_interaction_1'=> $values['q_6_social_interaction_1'],
                                                             'q_6_social_interaction_2'=> $values['q_6_social_interaction_2'],
                                                             'q_6_social_interaction_3'=> $values['q_6_social_interaction_3'],
                                                             'q_6_social_interaction_4'=> $values['q_6_social_interaction_4'],
                                                             'q_6_social_interaction_5'=> $values['q_6_social_interaction_5'],
                                                             'q_6_social_interaction_6'=> $values['q_6_social_interaction_6'],
                                                             'q_7_joint_attention_1'=> $values['q_7_joint_attention_1'],
                                                             'q_7_joint_attention_2'=> $values['q_7_joint_attention_2'],
                                                             'q_7_joint_attention_3'=> $values['q_7_joint_attention_3'],
                                                             'q_7_joint_attention_4'=> $values['q_7_joint_attention_4'],
                                                             'q_7_joint_attention_5'=> $values['q_7_joint_attention_5'],
                                                             'q_7_joint_attention_6'=> $values['q_7_joint_attention_6'],
                                                             'q_8_conventional_gestures_gives'=> $values['q_8_conventional_gestures_gives'],
                                                             'q_8_conventional_gestures_shows'=> $values['q_8_conventional_gestures_shows'],
                                                             'q_8_conventional_gestures_pushes_pulls'=> $values['q_8_conventional_gestures_pushes_pulls'],
                                                             'q_8_conventional_gestures_reaches'=> $values['q_8_conventional_gestures_reaches'],
                                                             'q_8_conventional_gestures_points'=> $values['q_8_conventional_gestures_points'],
                                                             'q_8_conventional_gestures_waves'=> $values['q_8_conventional_gestures_waves'],
                                                             'q_8_conventional_gestures_nods_head'=> $values['q_8_conventional_gestures_nods_head'],
                                                             'q_8_conventional_gestures_shakes_head'=> $values['q_8_conventional_gestures_shakes_head'],
                                                             'q_9_distal_gestures_1'=> $values['q_9_distal_gestures_1'],
                                                             'q_9_distal_gestures_2'=> $values['q_9_distal_gestures_2'],
                                                             'q_9_distal_gestures_3'=> $values['q_9_distal_gestures_3'],
                                                             'q_9_distal_gestures_4'=> $values['q_9_distal_gestures_4'],
                                                             'q_9_distal_gestures_5'=> $values['q_9_distal_gestures_5'],
                                                             'q_9_distal_gestures_6'=> $values['q_9_distal_gestures_6'],
                                                             'q_10_syllables_consonants_1'=> $values['q_10_syllables_consonants_1'],
                                                             'q_10_syllables_consonants_2'=> $values['q_10_syllables_consonants_2'],
                                                             'q_10_syllables_consonants_3'=> $values['q_10_syllables_consonants_3'],
                                                             'q_10_syllables_consonants_4'=> $values['q_10_syllables_consonants_4'],
                                                             'q_10_syllables_consonants_5'=> $values['q_10_syllables_consonants_5'],
                                                             'q_10_syllables_consonants_6'=> $values['q_10_syllables_consonants_6'],
                                                             'q_11_inventory_of_consonants_m'=> $values['q_11_inventory_of_consonants_m'],
                                                             'q_11_inventory_of_consonants_n'=> $values['q_11_inventory_of_consonants_n'],
                                                             'q_11_inventory_of_consonants_b_p'=> $values['q_11_inventory_of_consonants_b_p'],
                                                             'q_11_inventory_of_consonants_d_t'=> $values['q_11_inventory_of_consonants_d_t'],
                                                             'q_11_inventory_of_consonants_g_k'=> $values['q_11_inventory_of_consonants_g_k'],
                                                             'q_11_inventory_of_consonants_w'=> $values['q_11_inventory_of_consonants_w'],
                                                             'q_11_inventory_of_consonants_l'=> $values['q_11_inventory_of_consonants_l'],
                                                             'q_11_inventory_of_consonants_y'=> $values['q_11_inventory_of_consonants_y'],
                                                             'q_11_inventory_of_consonants_s'=> $values['q_11_inventory_of_consonants_s'],
                                                             'q_11_inventory_of_consonants_sh'=> $values['q_11_inventory_of_consonants_sh'],
                                                             'q_12_words_1'=> $values['q_12_words_1'],
                                                             'q_12_words_2'=> $values['q_12_words_2'],
                                                             'q_12_words_3'=> $values['q_12_words_3'],
                                                             'q_12_words_4'=> $values['q_12_words_4'],
                                                             'q_12_words_5'=> $values['q_12_words_5'],
                                                             'q_12_words_6'=> $values['q_12_words_6'],
                                                             'q_13_words_1'=> $values['q_13_words_1'],
                                                             'q_13_words_2'=> $values['q_13_words_2'],
                                                             'q_13_words_3'=> $values['q_13_words_3'],
                                                             'q_13_words_4'=> $values['q_13_words_4'],
                                                             'q_13_words_5'=> $values['q_13_words_5'],
                                                             'q_13_words_6'=> $values['q_13_words_6'],
                                                             'q_13_words_7'=> $values['q_13_words_7'],
                                                             'q_13_words_8'=> $values['q_13_words_8'],
                                                             'q_13_words_9'=> $values['q_13_words_9'],
                                                             'q_13_words_10'=> $values['q_13_words_10'],
                                                             'q_13_words_11'=> $values['q_13_words_11'],
                                                             'q_13_words_12'=> $values['q_13_words_12'],
                                                             'q_13_words_13'=> $values['q_13_words_13'],
                                                             'q_13_words_14'=> $values['q_13_words_14'],
                                                             'q_13_words_15'=> $values['q_13_words_15'],
                                                             'q_13_words_16'=> $values['q_13_words_16'],
                                                             'q_14_word_combos_1'=> $values['q_14_word_combos_1'],
                                                             'q_14_word_combos_2'=> $values['q_14_word_combos_2'],
                                                             'q_14_word_combos_3'=> $values['q_14_word_combos_3'],
                                                             'q_14_word_combos_4'=> $values['q_14_word_combos_4'],
                                                             'q_14_word_combos_5'=> $values['q_14_word_combos_5'],
                                                             'q_14_word_combos_6'=> $values['q_14_word_combos_6'],
                                                             'q_15_word_combos_1'=> $values['q_15_word_combos_1'],
                                                             'q_15_word_combos_2'=> $values['q_15_word_combos_2'],
                                                             'q_15_word_combos_3'=> $values['q_15_word_combos_3'],
                                                             'q_15_word_combos_4'=> $values['q_15_word_combos_4'],
                                                             'q_15_word_combos_5'=> $values['q_15_word_combos_5'],
                                                             'q_15_word_combos_6'=> $values['q_15_word_combos_6'],
                                                             'q_15_word_combos_7'=> $values['q_15_word_combos_7'],
                                                             'q_15_word_combos_8'=> $values['q_15_word_combos_8'],
                                                             'q_16_language_comp_objects_1'=> $values['q_16_language_comp_objects_1'],
                                                             'q_16_language_comp_objects_2'=> $values['q_16_language_comp_objects_2'],
                                                             'q_16_language_comp_objects_3'=> $values['q_16_language_comp_objects_3'],
                                                             'q_16_language_comp_objects_4'=> $values['q_16_language_comp_objects_4'],
                                                             'q_16_language_comp_person_1'=> $values['q_16_language_comp_person_1'],
                                                             'q_16_language_comp_person_2'=> $values['q_16_language_comp_person_2'],
                                                             'q_16_language_comp_person_3'=> $values['q_16_language_comp_person_3'],
                                                             'q_16_language_comp_body_parts_1'=> $values['q_16_language_comp_body_parts_1'],
                                                             'q_16_language_comp_body_parts_2'=> $values['q_16_language_comp_body_parts_2'],
                                                             'q_16_language_comp_body_parts_3'=> $values['q_16_language_comp_body_parts_3'],
                                                             'q_16_language_comp_body_parts_4'=> $values['q_16_language_comp_body_parts_4'],
                                                             'q_17_action_schemes_puts_in'=> $values['q_17_action_schemes_puts_in'],
                                                             'q_17_action_schemes_puts_on'=> $values['q_17_action_schemes_puts_on'],
                                                             'q_17_action_schemes_drinks_with_bottle'=> $values['q_17_action_schemes_drinks_with_bottle'],
                                                             'q_17_action_schemes_drinks_with_cup'=> $values['q_17_action_schemes_drinks_with_cup'],
                                                             'q_17_action_schemes_hugs'=> $values['q_17_action_schemes_hugs'],
                                                             'q_17_action_schemes_kisses'=> $values['q_17_action_schemes_kisses'],
                                                             'q_17_action_schemes_feeds_with_utensil'=> $values['q_17_action_schemes_feeds_with_utensil'],
                                                             'q_17_action_schemes_feeds_with_bowl'=> $values['q_17_action_schemes_feeds_with_bowl'],
                                                             'q_17_action_schemes_stirs'=> $values['q_17_action_schemes_stirs'],
                                                             'q_17_action_schemes_scoops'=> $values['q_17_action_schemes_scoops'],
                                                             'q_17_action_schemes_pours'=> $values['q_17_action_schemes_pours'],
                                                             'q_17_action_schemes_other'=> $values['q_17_action_schemes_other'],
                                                             'q_17_action_schemes_other_specify'=> $values['q_17_action_schemes_other_specify'],
                                                             'q_18_actions_towards_other_1'=> $values['q_18_actions_towards_other_1'],
                                                             'q_18_actions_towards_other_2'=> $values['q_18_actions_towards_other_2'],
                                                             'q_18_actions_towards_other_3'=> $values['q_18_actions_towards_other_3'],
                                                             'q_18_actions_towards_other_4'=> $values['q_18_actions_towards_other_4'],
                                                             'q_18_actions_towards_other_5'=> $values['q_18_actions_towards_other_5'],
                                                             'q_18_actions_towards_other_6'=> $values['q_18_actions_towards_other_6'],
                                                             'q_19_sequence_action_schemes_1'=> $values['q_19_sequence_action_schemes_1'],
                                                             'q_19_sequence_action_schemes_2'=> $values['q_19_sequence_action_schemes_2'],
                                                             'q_19_sequence_action_schemes_3'=> $values['q_19_sequence_action_schemes_3'],
                                                             'q_19_sequence_action_schemes_4'=> $values['q_19_sequence_action_schemes_4'],
                                                             'q_19_sequence_action_schemes_5'=> $values['q_19_sequence_action_schemes_5'],
                                                             'q_19_sequence_action_schemes_6'=> $values['q_19_sequence_action_schemes_6'],
                                                             'q_20_stacks_tower'=> $values['q_20_stacks_tower'],
                                                             
                                                             'q_1_alertness_match'=> $reliability['q_1_alertness_match'], 	
                                                             'q_2_emotional_reaction_match'=> $reliability['q_2_emotional_reaction_match'], 
                                                             'q_3_level_of_interest_match'=> $reliability['q_3_level_of_interest_match'],  
                                                             'q_4_comfort_level_match'=> $reliability['q_4_comfort_level_match'], 
                                                             'q_5_level_of_activity_match'=> $reliability['q_5_level_of_activity_match'], 
                                                             'q_6_level_of_communication_match'=> $reliability['q_6_level_of_communication_match'], 
                                                             'q_7_play_behaviour_match'=> $reliability['q_7_play_behaviour_match'], 
                                                             'q_1_gaze_shifts_1_match'=> $reliability['q_1_gaze_shifts_1_match'], 
                                                             'q_1_gaze_shifts_2_match'=> $reliability['q_1_gaze_shifts_2_match'], 
                                                             'q_1_gaze_shifts_3_match'=> $reliability['q_1_gaze_shifts_3_match'], 
                                                             'q_1_gaze_shifts_4_match'=> $reliability['q_1_gaze_shifts_4_match'], 
                                                             'q_1_gaze_shifts_5_match'=> $reliability['q_1_gaze_shifts_5_match'], 
                                                             'q_1_gaze_shifts_6_match'=> $reliability['q_1_gaze_shifts_6_match'], 
                                                             'q_1_gaze_shifts_raw_score_match'=> $reliability['q_1_gaze_shifts_raw_score_match'], 
                                                             'q_2_shared_positive_affect_1_match'=> $reliability['q_2_shared_positive_affect_1_match'], 
                                                             'q_2_shared_positive_affect_2_match'=> $reliability['q_2_shared_positive_affect_2_match'], 
                                                             'q_2_shared_positive_affect_3_match'=> $reliability['q_2_shared_positive_affect_3_match'], 
                                                             'q_2_shared_positive_affect_4_match'=> $reliability['q_2_shared_positive_affect_4_match'], 
                                                             'q_2_shared_positive_affect_5_match'=> $reliability['q_2_shared_positive_affect_5_match'], 
                                                             'q_2_shared_positive_affect_6_match'=> $reliability['q_2_shared_positive_affect_6_match'], 
                                                             'q_2_shared_positive_affect_raw_score_match'=> $reliability['q_2_shared_positive_affect_raw_score_match'], 
                                                             'q_3_gaze_point_following_2_match'=> $reliability['q_3_gaze_point_following_2_match'], 
                                                             'q_3_gaze_point_following_5_match'=> $reliability['q_3_gaze_point_following_5_match'], 
                                                             'q_3_gaze_point_following_raw_score_match'=> $reliability['q_3_gaze_point_following_raw_score_match'], 
                                                             'emotion_eye_gaze_weighted_match'=> $reliability['emotion_eye_gaze_weighted_match'], 
                                                             'q_4_rate_of_communicating_1_match'=> $reliability['q_4_rate_of_communicating_1_match'], 
                                                             'q_4_rate_of_communicating_2_match'=> $reliability['q_4_rate_of_communicating_2_match'], 
                                                             'q_4_rate_of_communicating_3_match'=> $reliability['q_4_rate_of_communicating_3_match'], 
                                                             'q_4_rate_of_communicating_4_match'=> $reliability['q_4_rate_of_communicating_4_match'], 
                                                             'q_4_rate_of_communicating_5_match'=> $reliability['q_4_rate_of_communicating_5_match'], 
                                                             'q_4_rate_of_communicating_6_match'=> $reliability['q_4_rate_of_communicating_6_match'], 
                                                             'q_4_rate_of_communicating_raw_score_match'=> $reliability['q_4_rate_of_communicating_raw_score_match'], 
                                                             'q_5_behaviour_regulation_1_match'=> $reliability['q_5_behaviour_regulation_1_match'], 
                                                             'q_5_behaviour_regulation_2_match'=> $reliability['q_5_behaviour_regulation_2_match'], 
                                                             'q_5_behaviour_regulation_3_match'=> $reliability['q_5_behaviour_regulation_3_match'], 
                                                             'q_5_behaviour_regulation_4_match'=> $reliability['q_5_behaviour_regulation_4_match'], 
                                                             'q_5_behaviour_regulation_5_match'=> $reliability['q_5_behaviour_regulation_5_match'], 
                                                             'q_5_behaviour_regulation_6_match'=> $reliability['q_5_behaviour_regulation_6_match'], 
                                                             'q_5_behaviour_regulation_raw_score_match'=> $reliability['q_5_behaviour_regulation_raw_score_match'], 
                                                             'q_6_social_interaction_1_match'=> $reliability['q_6_social_interaction_1_match'], 
                                                             'q_6_social_interaction_2_match'=> $reliability['q_6_social_interaction_2_match'], 
                                                             'q_6_social_interaction_3_match'=> $reliability['q_6_social_interaction_3_match'], 
                                                             'q_6_social_interaction_4_match'=> $reliability['q_6_social_interaction_4_match'], 
                                                             'q_6_social_interaction_5_match'=> $reliability['q_6_social_interaction_5_match'], 
                                                             'q_6_social_interaction_6_match'=> $reliability['q_6_social_interaction_6_match'], 
                                                             'q_6_social_interaction_raw_score_match'=> $reliability['q_6_social_interaction_raw_score_match'], 
                                                             'q_7_joint_attention_1_match'=> $reliability['q_7_joint_attention_1_match'], 
                                                             'q_7_joint_attention_2_match'=> $reliability['q_7_joint_attention_2_match'], 
                                                             'q_7_joint_attention_3_match'=> $reliability['q_7_joint_attention_3_match'], 
                                                             'q_7_joint_attention_4_match'=> $reliability['q_7_joint_attention_4_match'], 
                                                             'q_7_joint_attention_5_match'=> $reliability['q_7_joint_attention_5_match'], 
                                                             'q_7_joint_attention_6_match'=> $reliability['q_7_joint_attention_6_match'], 
                                                             'q_7_joint_attention_raw_score_match'=> $reliability['q_7_joint_attention_raw_score_match'], 
                                                             'communication_weighted_match'=> $reliability['communication_weighted_match'], 
                                                             'q_8_conventional_gestures_gives_match'=> $reliability['q_8_conventional_gestures_gives_match'], 
                                                             'q_8_conventional_gestures_shows_match'=> $reliability['q_8_conventional_gestures_shows_match'], 
                                                             'q_8_conventional_gestures_pushes_pulls_match'=> $reliability['q_8_conventional_gestures_pushes_pulls_match'], 
                                                             'q_8_conventional_gestures_reaches_match'=> $reliability['q_8_conventional_gestures_reaches_match'], 
                                                             'q_8_conventional_gestures_raw_score_match'=> $reliability['q_8_conventional_gestures_raw_score_match'], 
                                                             'q_8_conventional_gestures_points_match'=> $reliability['q_8_conventional_gestures_points_match'], 
                                                             'q_8_conventional_gestures_waves_match'=> $reliability['q_8_conventional_gestures_waves_match'], 
                                                             'q_8_conventional_gestures_nods_head_match'=> $reliability['q_8_conventional_gestures_nods_head_match'], 
                                                             'q_8_conventional_gestures_shakes_head_match'=> $reliability['q_8_conventional_gestures_shakes_head_match'], 
                                                             'q_9_distal_gestures_1_match'=> $reliability['q_9_distal_gestures_1_match'], 
                                                             'q_9_distal_gestures_2_match'=> $reliability['q_9_distal_gestures_2_match'], 
                                                             'q_9_distal_gestures_3_match'=> $reliability['q_9_distal_gestures_3_match'], 
                                                             'q_9_distal_gestures_4_match'=> $reliability['q_9_distal_gestures_4_match'], 
                                                             'q_9_distal_gestures_5_match'=> $reliability['q_9_distal_gestures_5_match'], 
                                                             'q_9_distal_gestures_6_match'=> $reliability['q_9_distal_gestures_6_match'], 
                                                             'q_9_distal_gestures_raw_score_match'=> $reliability['q_9_distal_gestures_raw_score_match'], 
                                                             'gestures_weighted_match'=> $reliability['gestures_weighted_match'], 
                                                             'q_10_syllables_consonants_1_match'=> $reliability['q_10_syllables_consonants_1_match'], 
                                                             'q_10_syllables_consonants_2_match'=> $reliability['q_10_syllables_consonants_2_match'], 
                                                             'q_10_syllables_consonants_3_match'=> $reliability['q_10_syllables_consonants_3_match'], 
                                                             'q_10_syllables_consonants_4_match'=> $reliability['q_10_syllables_consonants_4_match'], 
                                                             'q_10_syllables_consonants_5_match'=> $reliability['q_10_syllables_consonants_5_match'], 
                                                             'q_10_syllables_consonants_6_match'=> $reliability['q_10_syllables_consonants_6_match'], 
                                                             'q_10_syllables_consonants_raw_score_match'=> $reliability['q_10_syllables_consonants_raw_score_match'], 
                                                             'q_11_inventory_of_consonants_m_match'=> $reliability['q_11_inventory_of_consonants_m_match'], 
                                                             'q_11_inventory_of_consonants_n_match'=> $reliability['q_11_inventory_of_consonants_n_match'], 
                                                             'q_11_inventory_of_consonants_b_p_match'=> $reliability['q_11_inventory_of_consonants_b_p_match'], 
                                                             'q_11_inventory_of_consonants_d_t_match'=> $reliability['q_11_inventory_of_consonants_d_t_match'], 
                                                             'q_11_inventory_of_consonants_g_k_match'=> $reliability['q_11_inventory_of_consonants_g_k_match'], 
                                                             'q_11_inventory_of_consonants_raw_score_match'=> $reliability['q_11_inventory_of_consonants_raw_score_match'], 
                                                             'q_11_inventory_of_consonants_w_match'=> $reliability['q_11_inventory_of_consonants_w_match'], 
                                                             'q_11_inventory_of_consonants_l_match'=> $reliability['q_11_inventory_of_consonants_l_match'], 
                                                             'q_11_inventory_of_consonants_y_match'=> $reliability['q_11_inventory_of_consonants_y_match'], 
                                                             'q_11_inventory_of_consonants_s_match'=> $reliability['q_11_inventory_of_consonants_s_match'], 
                                                             'q_11_inventory_of_consonants_sh_match'=> $reliability['q_11_inventory_of_consonants_sh_match'], 
                                                             'sounds_weighted_match'=> $reliability['sounds_weighted_match'], 
                                                             'q_12_words_1_match'=> $reliability['q_12_words_1_match'], 
                                                             'q_12_words_2_match'=> $reliability['q_12_words_2_match'], 
                                                             'q_12_words_3_match'=> $reliability['q_12_words_3_match'], 
                                                             'q_12_words_4_match'=> $reliability['q_12_words_4_match'], 
                                                             'q_12_words_5_match'=> $reliability['q_12_words_5_match'], 
                                                             'q_12_words_6_match'=> $reliability['q_12_words_6_match'], 
                                                             'q_12_words_raw_score_match'=> $reliability['q_12_words_raw_score_match'], 
                                                             'q_13_words_1_match'=> $reliability['q_13_words_1_match'], 
                                                             'q_13_words_2_match'=> $reliability['q_13_words_2_match'], 
                                                             'q_13_words_3_match'=> $reliability['q_13_words_3_match'], 
                                                             'q_13_words_4_match'=> $reliability['q_13_words_4_match'], 
                                                             'q_13_words_raw_score_match'=> $reliability['q_13_words_raw_score_match'], 
                                                             'q_13_words_5_match'=> $reliability['q_13_words_5_match'], 
                                                             'q_13_words_6_match'=> $reliability['q_13_words_6_match'], 
                                                             'q_13_words_7_match'=> $reliability['q_13_words_7_match'], 
                                                             'q_13_words_8_match'=> $reliability['q_13_words_8_match'], 
                                                             'q_13_words_9_match'=> $reliability['q_13_words_9_match'], 
                                                             'q_13_words_10_match'=> $reliability['q_13_words_10_match'], 
                                                             'q_13_words_11_match'=> $reliability['q_13_words_11_match'], 
                                                             'q_13_words_12_match'=> $reliability['q_13_words_12_match'], 
                                                             'q_13_words_13_match'=> $reliability['q_13_words_13_match'], 
                                                             'q_13_words_14_match'=> $reliability['q_13_words_14_match'], 
                                                             'q_13_words_15_match'=> $reliability['q_13_words_15_match'], 
                                                             'q_13_words_16_match'=> $reliability['q_13_words_16_match'], 
                                                             'q_14_word_combos_1_match'=> $reliability['q_14_word_combos_1_match'], 
                                                             'q_14_word_combos_2_match'=> $reliability['q_14_word_combos_2_match'], 
                                                             'q_14_word_combos_3_match'=> $reliability['q_14_word_combos_3_match'], 
                                                             'q_14_word_combos_4_match'=> $reliability['q_14_word_combos_4_match'], 
                                                             'q_14_word_combos_5_match'=> $reliability['q_14_word_combos_5_match'], 
                                                             'q_14_word_combos_6_match'=> $reliability['q_14_word_combos_6_match'], 
                                                             'q_14_word_combos_raw_score_match'=> $reliability['q_14_word_combos_raw_score_match'], 
                                                             'q_15_word_combos_1_match'=> $reliability['q_15_word_combos_1_match'], 
                                                             'q_15_word_combos_2_match'=> $reliability['q_15_word_combos_2_match'], 
                                                             'q_15_word_combos_raw_score_match'=> $reliability['q_15_word_combos_raw_score_match'], 
                                                             'q_15_word_combos_3_match'=> $reliability['q_15_word_combos_3_match'], 
                                                             'q_15_word_combos_4_match'=> $reliability['q_15_word_combos_4_match'], 
                                                             'q_15_word_combos_5_match'=> $reliability['q_15_word_combos_5_match'], 
                                                             'q_15_word_combos_6_match'=> $reliability['q_15_word_combos_6_match'], 
                                                             'q_15_word_combos_7_match'=> $reliability['q_15_word_combos_7_match'], 
                                                             'q_15_word_combos_8_match'=> $reliability['q_15_word_combos_8_match'], 
                                                             'words_weighted_match'=> $reliability['words_weighted_match'], 
                                                             'q_16_language_comp_objects_1_match'=> $reliability['q_16_language_comp_objects_1_match'], 
                                                             'q_16_language_comp_objects_2_match'=> $reliability['q_16_language_comp_objects_2_match'], 
                                                             'q_16_language_comp_objects_3_match'=> $reliability['q_16_language_comp_objects_3_match'], 
                                                             'q_16_language_comp_objects_4_match'=> $reliability['q_16_language_comp_objects_4_match'], 
                                                             'q_16_language_comp_raw_score_match'=> $reliability['q_16_language_comp_raw_score_match'], 
                                                             'q_16_language_comp_person_1_match'=> $reliability['q_16_language_comp_person_1_match'], 
                                                             'q_16_language_comp_person_2_match'=> $reliability['q_16_language_comp_person_2_match'], 
                                                             'q_16_language_comp_person_3_match'=> $reliability['q_16_language_comp_person_3_match'], 
                                                             'q_16_language_comp_body_parts_1_match'=> $reliability['q_16_language_comp_body_parts_1_match'], 
                                                             'q_16_language_comp_body_parts_2_match'=> $reliability['q_16_language_comp_body_parts_2_match'], 
                                                             'q_16_language_comp_body_parts_3_match'=> $reliability['q_16_language_comp_body_parts_3_match'], 
                                                             'q_16_language_comp_body_parts_4_match'=> $reliability['q_16_language_comp_body_parts_4_match'], 
                                                             'q_16_language_comp_body_parts_raw_score_match'=> $reliability['q_16_language_comp_body_parts_raw_score_match'], 
                                                             'understanding_weighted_match'=> $reliability['understanding_weighted_match'], 
                                                             'q_17_action_schemes_puts_in_match'=> $reliability['q_17_action_schemes_puts_in_match'], 
                                                             'q_17_action_schemes_puts_on_match'=> $reliability['q_17_action_schemes_puts_on_match'], 
                                                             'q_17_action_schemes_drinks_with_bottle_match'=> $reliability['q_17_action_schemes_drinks_with_bottle_match'], 
                                                             'q_17_action_schemes_drinks_with_cup_match'=> $reliability['q_17_action_schemes_drinks_with_cup_match'], 
                                                             'q_17_action_schemes_hugs_match'=> $reliability['q_17_action_schemes_hugs_match'], 
                                                             'q_17_action_schemes_kisses_match'=> $reliability['q_17_action_schemes_kisses_match'], 
                                                             'q_17_action_schemes_raw_score_match'=> $reliability['q_17_action_schemes_raw_score_match'], 
                                                             'q_17_action_schemes_feeds_with_utensil_match'=> $reliability['q_17_action_schemes_feeds_with_utensil_match'], 
                                                             'q_17_action_schemes_feeds_with_bowl_match'=> $reliability['q_17_action_schemes_feeds_with_bowl_match'], 
                                                             'q_17_action_schemes_stirs_match'=> $reliability['q_17_action_schemes_stirs_match'], 
                                                             'q_17_action_schemes_scoops_match'=> $reliability['q_17_action_schemes_scoops_match'], 
                                                             'q_17_action_schemes_pours_match'=> $reliability['q_17_action_schemes_pours_match'], 
                                                             'q_17_action_schemes_other_match'=> $reliability['q_17_action_schemes_other_match'], 
                                                             'q_17_action_schemes_other_specify_match'=> $reliability['q_17_action_schemes_other_specify_match'], 
                                                             'q_18_actions_towards_other_1_match'=> $reliability['q_18_actions_towards_other_1_match'], 
                                                             'q_18_actions_towards_other_2_match'=> $reliability['q_18_actions_towards_other_2_match'], 
                                                             'q_18_actions_towards_other_3_match'=> $reliability['q_18_actions_towards_other_3_match'], 
                                                             'q_18_actions_towards_other_4_match'=> $reliability['q_18_actions_towards_other_4_match'], 
                                                             'q_18_actions_towards_other_5_match'=> $reliability['q_18_actions_towards_other_5_match'], 
                                                             'q_18_actions_towards_other_6_match'=> $reliability['q_18_actions_towards_other_6_match'], 
                                                             'q_18_actions_towards_other_raw_score_match'=> $reliability['q_18_actions_towards_other_raw_score_match'], 
                                                             'q_19_sequence_action_schemes_1_match'=> $reliability['q_19_sequence_action_schemes_1_match'], 
                                                             'q_19_sequence_action_schemes_2_match'=> $reliability['q_19_sequence_action_schemes_2_match'], 
                                                             'q_19_sequence_action_schemes_3_match'=> $reliability['q_19_sequence_action_schemes_3_match'], 
                                                             'q_19_sequence_action_schemes_4_match'=> $reliability['q_19_sequence_action_schemes_4_match'], 
                                                             'q_19_sequence_action_schemes_5_match'=> $reliability['q_19_sequence_action_schemes_5_match'], 
                                                             'q_19_sequence_action_schemes_6_match'=> $reliability['q_19_sequence_action_schemes_6_match'], 
                                                             'q_19_sequence_action_schemes_raw_score_match'=> $reliability['q_19_sequence_action_schemes_raw_score_match'], 
                                                             'q_20_stacks_tower_match'=> $reliability['q_20_stacks_tower_match'], 
                                                             'q_20_stacks_tower_raw_score_match'=> $reliability['q_20_stacks_tower_raw_score_match'], 
                                                             'object_use_weighted_match'=> $reliability['object_use_weighted']
                                                             ));
            if (PEAR::isError($success)) {
                return PEAR::raiseError("DB Error: ".$success->getMessage());
            }
            $this->identifier = $DB->lastInsertID;
        } else {
            // update the event
            $success = $DB->update('csbs_reliability', array(
                                                             // 'CommentID' => $this->identifier,
                                                             'Examiner' => $values['Examiner'],
                                                              'Date_taken' => $this->_getDatabaseDate($values['Date_taken']),
                                                             'Gold_standard' => $values['Gold_standard'],
                                                             'q_1_alertness' => $values['q_1_alertness'],
                                                             'q_2_emotional_reaction' => $values['q_2_emotional_reaction'],
                                                             'q_3_level_of_interest' => $values['q_3_level_of_interest'], 
                                                             'q_4_comfort_level' => $values['q_4_comfort_level'],
                                                             'q_5_level_of_activity' => $values['q_5_level_of_activity'],
                                                             'q_6_level_of_communication' => $values['q_6_level_of_communication'],
                                                             'q_7_play_behaviour' => $values['q_7_play_behaviour'],
                                                             'q_1_gaze_shifts_1'=> $values['q_1_gaze_shifts_1'],
                                                             'q_1_gaze_shifts_2'=> $values['q_1_gaze_shifts_2'],
                                                             'q_1_gaze_shifts_3'=> $values['q_1_gaze_shifts_3'],
                                                             'q_1_gaze_shifts_4'=> $values['q_1_gaze_shifts_4'],
                                                             'q_1_gaze_shifts_5'=> $values['q_1_gaze_shifts_5'],
                                                             'q_1_gaze_shifts_6'=> $values['q_1_gaze_shifts_6'],
                                                             'q_2_shared_positive_affect_1'=> $values['q_2_shared_positive_affect_1'],
                                                             'q_2_shared_positive_affect_2'=> $values['q_2_shared_positive_affect_2'],
                                                             'q_2_shared_positive_affect_3'=> $values['q_2_shared_positive_affect_3'],
                                                             'q_2_shared_positive_affect_4'=> $values['q_2_shared_positive_affect_4'],
                                                             'q_2_shared_positive_affect_5'=> $values['q_2_shared_positive_affect_5'],
                                                             'q_2_shared_positive_affect_6'=> $values['q_2_shared_positive_affect_6'],
                                                             'q_3_gaze_point_following_2'=> $values['q_3_gaze_point_following_2'],
                                                             'q_3_gaze_point_following_5'=> $values['q_3_gaze_point_following_5'],
                                                             'q_4_rate_of_communicating_1'=> $values['q_4_rate_of_communicating_1'],
                                                             'q_4_rate_of_communicating_2'=> $values['q_4_rate_of_communicating_2'],
                                                             'q_4_rate_of_communicating_3'=> $values['q_4_rate_of_communicating_3'],
                                                             'q_4_rate_of_communicating_4'=> $values['q_4_rate_of_communicating_4'],
                                                             'q_4_rate_of_communicating_5'=> $values['q_4_rate_of_communicating_5'],
                                                             'q_4_rate_of_communicating_6'=> $values['q_4_rate_of_communicating_6'],
                                                             'q_5_behaviour_regulation_1'=> $values['q_5_behaviour_regulation_1'],
                                                             'q_5_behaviour_regulation_2'=> $values['q_5_behaviour_regulation_2'],
                                                             'q_5_behaviour_regulation_3'=> $values['q_5_behaviour_regulation_3'],
                                                             'q_5_behaviour_regulation_4'=> $values['q_5_behaviour_regulation_4'],
                                                             'q_5_behaviour_regulation_5'=> $values['q_5_behaviour_regulation_5'],
                                                             'q_5_behaviour_regulation_6'=> $values['q_5_behaviour_regulation_6'],
                                                             'q_6_social_interaction_1'=> $values['q_6_social_interaction_1'],
                                                             'q_6_social_interaction_2'=> $values['q_6_social_interaction_2'],
                                                             'q_6_social_interaction_3'=> $values['q_6_social_interaction_3'],
                                                             'q_6_social_interaction_4'=> $values['q_6_social_interaction_4'],
                                                             'q_6_social_interaction_5'=> $values['q_6_social_interaction_5'],
                                                             'q_6_social_interaction_6'=> $values['q_6_social_interaction_6'],
                                                             'q_7_joint_attention_1'=> $values['q_7_joint_attention_1'],
                                                             'q_7_joint_attention_2'=> $values['q_7_joint_attention_2'],
                                                             'q_7_joint_attention_3'=> $values['q_7_joint_attention_3'],
                                                             'q_7_joint_attention_4'=> $values['q_7_joint_attention_4'],
                                                             'q_7_joint_attention_5'=> $values['q_7_joint_attention_5'],
                                                             'q_7_joint_attention_6'=> $values['q_7_joint_attention_6'],
                                                             'q_8_conventional_gestures_gives'=> $values['q_8_conventional_gestures_gives'],
                                                             'q_8_conventional_gestures_shows'=> $values['q_8_conventional_gestures_shows'],
                                                             'q_8_conventional_gestures_pushes_pulls'=> $values['q_8_conventional_gestures_pushes_pulls'],
                                                             'q_8_conventional_gestures_reaches'=> $values['q_8_conventional_gestures_reaches'],
                                                             'q_8_conventional_gestures_points'=> $values['q_8_conventional_gestures_points'],
                                                             'q_8_conventional_gestures_waves'=> $values['q_8_conventional_gestures_waves'],
                                                             'q_8_conventional_gestures_nods_head'=> $values['q_8_conventional_gestures_nods_head'],
                                                             'q_8_conventional_gestures_shakes_head'=> $values['q_8_conventional_gestures_shakes_head'],
                                                             'q_9_distal_gestures_1'=> $values['q_9_distal_gestures_1'],
                                                             'q_9_distal_gestures_2'=> $values['q_9_distal_gestures_2'],
                                                             'q_9_distal_gestures_3'=> $values['q_9_distal_gestures_3'],
                                                             'q_9_distal_gestures_4'=> $values['q_9_distal_gestures_4'],
                                                             'q_9_distal_gestures_5'=> $values['q_9_distal_gestures_5'],
                                                             'q_9_distal_gestures_6'=> $values['q_9_distal_gestures_6'],
                                                             'q_10_syllables_consonants_1'=> $values['q_10_syllables_consonants_1'],
                                                             'q_10_syllables_consonants_2'=> $values['q_10_syllables_consonants_2'],
                                                             'q_10_syllables_consonants_3'=> $values['q_10_syllables_consonants_3'],
                                                             'q_10_syllables_consonants_4'=> $values['q_10_syllables_consonants_4'],
                                                             'q_10_syllables_consonants_5'=> $values['q_10_syllables_consonants_5'],
                                                             'q_10_syllables_consonants_6'=> $values['q_10_syllables_consonants_6'],
                                                             'q_11_inventory_of_consonants_m'=> $values['q_11_inventory_of_consonants_m'],
                                                             'q_11_inventory_of_consonants_n'=> $values['q_11_inventory_of_consonants_n'],
                                                             'q_11_inventory_of_consonants_b_p'=> $values['q_11_inventory_of_consonants_b_p'],
                                                             'q_11_inventory_of_consonants_d_t'=> $values['q_11_inventory_of_consonants_d_t'],
                                                             'q_11_inventory_of_consonants_g_k'=> $values['q_11_inventory_of_consonants_g_k'],
                                                             'q_11_inventory_of_consonants_w'=> $values['q_11_inventory_of_consonants_w'],
                                                             'q_11_inventory_of_consonants_l'=> $values['q_11_inventory_of_consonants_l'],
                                                             'q_11_inventory_of_consonants_y'=> $values['q_11_inventory_of_consonants_y'],
                                                             'q_11_inventory_of_consonants_s'=> $values['q_11_inventory_of_consonants_s'],
                                                             'q_11_inventory_of_consonants_sh'=> $values['q_11_inventory_of_consonants_sh'],
                                                             'q_12_words_1'=> $values['q_12_words_1'],
                                                             'q_12_words_2'=> $values['q_12_words_2'],
                                                             'q_12_words_3'=> $values['q_12_words_3'],
                                                             'q_12_words_4'=> $values['q_12_words_4'],
                                                             'q_12_words_5'=> $values['q_12_words_5'],
                                                             'q_12_words_6'=> $values['q_12_words_6'],
                                                             'q_13_words_1'=> $values['q_13_words_1'],
                                                             'q_13_words_2'=> $values['q_13_words_2'],
                                                             'q_13_words_3'=> $values['q_13_words_3'],
                                                             'q_13_words_4'=> $values['q_13_words_4'],
                                                             'q_13_words_5'=> $values['q_13_words_5'],
                                                             'q_13_words_6'=> $values['q_13_words_6'],
                                                             'q_13_words_7'=> $values['q_13_words_7'],
                                                             'q_13_words_8'=> $values['q_13_words_8'],
                                                             'q_13_words_9'=> $values['q_13_words_9'],
                                                             'q_13_words_10'=> $values['q_13_words_10'],
                                                             'q_13_words_11'=> $values['q_13_words_11'],
                                                             'q_13_words_12'=> $values['q_13_words_12'],
                                                             'q_13_words_13'=> $values['q_13_words_13'],
                                                             'q_13_words_14'=> $values['q_13_words_14'],
                                                             'q_13_words_15'=> $values['q_13_words_15'],
                                                             'q_13_words_16'=> $values['q_13_words_16'],
                                                             'q_14_word_combos_1'=> $values['q_14_word_combos_1'],
                                                             'q_14_word_combos_2'=> $values['q_14_word_combos_2'],
                                                             'q_14_word_combos_3'=> $values['q_14_word_combos_3'],
                                                             'q_14_word_combos_4'=> $values['q_14_word_combos_4'],
                                                             'q_14_word_combos_5'=> $values['q_14_word_combos_5'],
                                                             'q_14_word_combos_6'=> $values['q_14_word_combos_6'],
                                                             'q_15_word_combos_1'=> $values['q_15_word_combos_1'],
                                                             'q_15_word_combos_2'=> $values['q_15_word_combos_2'],
                                                             'q_15_word_combos_3'=> $values['q_15_word_combos_3'],
                                                             'q_15_word_combos_4'=> $values['q_15_word_combos_4'],
                                                             'q_15_word_combos_5'=> $values['q_15_word_combos_5'],
                                                             'q_15_word_combos_6'=> $values['q_15_word_combos_6'],
                                                             'q_15_word_combos_7'=> $values['q_15_word_combos_7'],
                                                             'q_15_word_combos_8'=> $values['q_15_word_combos_8'],
                                                             'q_16_language_comp_objects_1'=> $values['q_16_language_comp_objects_1'],
                                                             'q_16_language_comp_objects_2'=> $values['q_16_language_comp_objects_2'],
                                                             'q_16_language_comp_objects_3'=> $values['q_16_language_comp_objects_3'],
                                                             'q_16_language_comp_objects_4'=> $values['q_16_language_comp_objects_4'],
                                                             'q_16_language_comp_person_1'=> $values['q_16_language_comp_person_1'],
                                                             'q_16_language_comp_person_2'=> $values['q_16_language_comp_person_2'],
                                                             'q_16_language_comp_person_3'=> $values['q_16_language_comp_person_3'],
                                                             'q_16_language_comp_body_parts_1'=> $values['q_16_language_comp_body_parts_1'],
                                                             'q_16_language_comp_body_parts_2'=> $values['q_16_language_comp_body_parts_2'],
                                                             'q_16_language_comp_body_parts_3'=> $values['q_16_language_comp_body_parts_3'],
                                                             'q_16_language_comp_body_parts_4'=> $values['q_16_language_comp_body_parts_4'],
                                                             'q_17_action_schemes_puts_in'=> $values['q_17_action_schemes_puts_in'],
                                                             'q_17_action_schemes_puts_on'=> $values['q_17_action_schemes_puts_on'],
                                                             'q_17_action_schemes_drinks_with_bottle'=> $values['q_17_action_schemes_drinks_with_bottle'],
                                                             'q_17_action_schemes_drinks_with_cup'=> $values['q_17_action_schemes_drinks_with_cup'],
                                                             'q_17_action_schemes_hugs'=> $values['q_17_action_schemes_hugs'],
                                                             'q_17_action_schemes_kisses'=> $values['q_17_action_schemes_kisses'],
                                                             'q_17_action_schemes_feeds_with_utensil'=> $values['q_17_action_schemes_feeds_with_utensil'],
                                                             'q_17_action_schemes_feeds_with_bowl'=> $values['q_17_action_schemes_feeds_with_bowl'],
                                                             'q_17_action_schemes_stirs'=> $values['q_17_action_schemes_stirs'],
                                                             'q_17_action_schemes_scoops'=> $values['q_17_action_schemes_scoops'],
                                                             'q_17_action_schemes_pours'=> $values['q_17_action_schemes_pours'],
                                                             'q_17_action_schemes_other'=> $values['q_17_action_schemes_other'],
                                                             'q_17_action_schemes_other_specify'=> $values['q_17_action_schemes_other_specify'],
                                                             'q_18_actions_towards_other_1'=> $values['q_18_actions_towards_other_1'],
                                                             'q_18_actions_towards_other_2'=> $values['q_18_actions_towards_other_2'],
                                                             'q_18_actions_towards_other_3'=> $values['q_18_actions_towards_other_3'],
                                                             'q_18_actions_towards_other_4'=> $values['q_18_actions_towards_other_4'],
                                                             'q_18_actions_towards_other_5'=> $values['q_18_actions_towards_other_5'],
                                                             'q_18_actions_towards_other_6'=> $values['q_18_actions_towards_other_6'],
                                                             'q_19_sequence_action_schemes_1'=> $values['q_19_sequence_action_schemes_1'],
                                                             'q_19_sequence_action_schemes_2'=> $values['q_19_sequence_action_schemes_2'],
                                                             'q_19_sequence_action_schemes_3'=> $values['q_19_sequence_action_schemes_3'],
                                                             'q_19_sequence_action_schemes_4'=> $values['q_19_sequence_action_schemes_4'],
                                                             'q_19_sequence_action_schemes_5'=> $values['q_19_sequence_action_schemes_5'],
                                                             'q_19_sequence_action_schemes_6'=> $values['q_19_sequence_action_schemes_6'],
                                                             'q_20_stacks_tower'=> $values['q_20_stacks_tower'],
                                                             
                                                             'q_1_alertness_match'=> $reliability['q_1_alertness_match'], 	
                                                             'q_2_emotional_reaction_match'=> $reliability['q_2_emotional_reaction_match'], 
                                                             'q_3_level_of_interest_match'=> $reliability['q_3_level_of_interest_match'],  
                                                             'q_4_comfort_level_match'=> $reliability['q_4_comfort_level_match'], 
                                                             'q_5_level_of_activity_match'=> $reliability['q_5_level_of_activity_match'], 
                                                             'q_6_level_of_communication_match'=> $reliability['q_6_level_of_communication_match'], 
                                                             'q_7_play_behaviour_match'=> $reliability['q_7_play_behaviour_match'], 
                                                             'q_1_gaze_shifts_1_match'=> $reliability['q_1_gaze_shifts_1_match'], 
                                                             'q_1_gaze_shifts_2_match'=> $reliability['q_1_gaze_shifts_2_match'], 
                                                             'q_1_gaze_shifts_3_match'=> $reliability['q_1_gaze_shifts_3_match'], 
                                                             'q_1_gaze_shifts_4_match'=> $reliability['q_1_gaze_shifts_4_match'], 
                                                             'q_1_gaze_shifts_5_match'=> $reliability['q_1_gaze_shifts_5_match'], 
                                                             'q_1_gaze_shifts_6_match'=> $reliability['q_1_gaze_shifts_6_match'], 
                                                             'q_1_gaze_shifts_raw_score_match'=> $reliability['q_1_gaze_shifts_raw_score_match'], 
                                                             'q_2_shared_positive_affect_1_match'=> $reliability['q_2_shared_positive_affect_1_match'], 
                                                             'q_2_shared_positive_affect_2_match'=> $reliability['q_2_shared_positive_affect_2_match'], 
                                                             'q_2_shared_positive_affect_3_match'=> $reliability['q_2_shared_positive_affect_3_match'], 
                                                             'q_2_shared_positive_affect_4_match'=> $reliability['q_2_shared_positive_affect_4_match'], 
                                                             'q_2_shared_positive_affect_5_match'=> $reliability['q_2_shared_positive_affect_5_match'], 
                                                             'q_2_shared_positive_affect_6_match'=> $reliability['q_2_shared_positive_affect_6_match'], 
                                                             'q_2_shared_positive_affect_raw_score_match'=> $reliability['q_2_shared_positive_affect_raw_score_match'], 
                                                             'q_3_gaze_point_following_2_match'=> $reliability['q_3_gaze_point_following_2_match'], 
                                                             'q_3_gaze_point_following_5_match'=> $reliability['q_3_gaze_point_following_5_match'], 
                                                             'q_3_gaze_point_following_raw_score_match'=> $reliability['q_3_gaze_point_following_raw_score_match'], 
                                                             'emotion_eye_gaze_weighted_match'=> $reliability['emotion_eye_gaze_weighted_match'], 
                                                             'q_4_rate_of_communicating_1_match'=> $reliability['q_4_rate_of_communicating_1_match'], 
                                                             'q_4_rate_of_communicating_2_match'=> $reliability['q_4_rate_of_communicating_2_match'], 
                                                             'q_4_rate_of_communicating_3_match'=> $reliability['q_4_rate_of_communicating_3_match'], 
                                                             'q_4_rate_of_communicating_4_match'=> $reliability['q_4_rate_of_communicating_4_match'], 
                                                             'q_4_rate_of_communicating_5_match'=> $reliability['q_4_rate_of_communicating_5_match'], 
                                                             'q_4_rate_of_communicating_6_match'=> $reliability['q_4_rate_of_communicating_6_match'], 
                                                             'q_4_rate_of_communicating_raw_score_match'=> $reliability['q_4_rate_of_communicating_raw_score_match'], 
                                                             'q_5_behaviour_regulation_1_match'=> $reliability['q_5_behaviour_regulation_1_match'], 
                                                             'q_5_behaviour_regulation_2_match'=> $reliability['q_5_behaviour_regulation_2_match'], 
                                                             'q_5_behaviour_regulation_3_match'=> $reliability['q_5_behaviour_regulation_3_match'], 
                                                             'q_5_behaviour_regulation_4_match'=> $reliability['q_5_behaviour_regulation_4_match'], 
                                                             'q_5_behaviour_regulation_5_match'=> $reliability['q_5_behaviour_regulation_5_match'], 
                                                             'q_5_behaviour_regulation_6_match'=> $reliability['q_5_behaviour_regulation_6_match'], 
                                                             'q_5_behaviour_regulation_raw_score_match'=> $reliability['q_5_behaviour_regulation_raw_score_match'], 
                                                             'q_6_social_interaction_1_match'=> $reliability['q_6_social_interaction_1_match'], 
                                                             'q_6_social_interaction_2_match'=> $reliability['q_6_social_interaction_2_match'], 
                                                             'q_6_social_interaction_3_match'=> $reliability['q_6_social_interaction_3_match'], 
                                                             'q_6_social_interaction_4_match'=> $reliability['q_6_social_interaction_4_match'], 
                                                             'q_6_social_interaction_5_match'=> $reliability['q_6_social_interaction_5_match'], 
                                                             'q_6_social_interaction_6_match'=> $reliability['q_6_social_interaction_6_match'], 
                                                             'q_6_social_interaction_raw_score_match'=> $reliability['q_6_social_interaction_raw_score_match'], 
                                                             'q_7_joint_attention_1_match'=> $reliability['q_7_joint_attention_1_match'], 
                                                             'q_7_joint_attention_2_match'=> $reliability['q_7_joint_attention_2_match'], 
                                                             'q_7_joint_attention_3_match'=> $reliability['q_7_joint_attention_3_match'], 
                                                             'q_7_joint_attention_4_match'=> $reliability['q_7_joint_attention_4_match'], 
                                                             'q_7_joint_attention_5_match'=> $reliability['q_7_joint_attention_5_match'], 
                                                             'q_7_joint_attention_6_match'=> $reliability['q_7_joint_attention_6_match'], 
                                                             'q_7_joint_attention_raw_score_match'=> $reliability['q_7_joint_attention_raw_score_match'], 
                                                             'communication_weighted_match'=> $reliability['communication_weighted_match'], 
                                                             'q_8_conventional_gestures_gives_match'=> $reliability['q_8_conventional_gestures_gives_match'], 
                                                             'q_8_conventional_gestures_shows_match'=> $reliability['q_8_conventional_gestures_shows_match'], 
                                                             'q_8_conventional_gestures_pushes_pulls_match'=> $reliability['q_8_conventional_gestures_pushes_pulls_match'], 
                                                             'q_8_conventional_gestures_reaches_match'=> $reliability['q_8_conventional_gestures_reaches_match'], 
                                                             'q_8_conventional_gestures_raw_score_match'=> $reliability['q_8_conventional_gestures_raw_score_match'], 
                                                             'q_8_conventional_gestures_points_match'=> $reliability['q_8_conventional_gestures_points_match'], 
                                                             'q_8_conventional_gestures_waves_match'=> $reliability['q_8_conventional_gestures_waves_match'], 
                                                             'q_8_conventional_gestures_nods_head_match'=> $reliability['q_8_conventional_gestures_nods_head_match'], 
                                                             'q_8_conventional_gestures_shakes_head_match'=> $reliability['q_8_conventional_gestures_shakes_head_match'], 
                                                             'q_9_distal_gestures_1_match'=> $reliability['q_9_distal_gestures_1_match'], 
                                                             'q_9_distal_gestures_2_match'=> $reliability['q_9_distal_gestures_2_match'], 
                                                             'q_9_distal_gestures_3_match'=> $reliability['q_9_distal_gestures_3_match'], 
                                                             'q_9_distal_gestures_4_match'=> $reliability['q_9_distal_gestures_4_match'], 
                                                             'q_9_distal_gestures_5_match'=> $reliability['q_9_distal_gestures_5_match'], 
                                                             'q_9_distal_gestures_6_match'=> $reliability['q_9_distal_gestures_6_match'], 
                                                             'q_9_distal_gestures_raw_score_match'=> $reliability['q_9_distal_gestures_raw_score_match'], 
                                                             'gestures_weighted_match'=> $reliability['gestures_weighted_match'], 
                                                             'q_10_syllables_consonants_1_match'=> $reliability['q_10_syllables_consonants_1_match'], 
                                                             'q_10_syllables_consonants_2_match'=> $reliability['q_10_syllables_consonants_2_match'], 
                                                             'q_10_syllables_consonants_3_match'=> $reliability['q_10_syllables_consonants_3_match'], 
                                                             'q_10_syllables_consonants_4_match'=> $reliability['q_10_syllables_consonants_4_match'], 
                                                             'q_10_syllables_consonants_5_match'=> $reliability['q_10_syllables_consonants_5_match'], 
                                                             'q_10_syllables_consonants_6_match'=> $reliability['q_10_syllables_consonants_6_match'], 
                                                             'q_10_syllables_consonants_raw_score_match'=> $reliability['q_10_syllables_consonants_raw_score_match'], 
                                                             'q_11_inventory_of_consonants_m_match'=> $reliability['q_11_inventory_of_consonants_m_match'], 
                                                             'q_11_inventory_of_consonants_n_match'=> $reliability['q_11_inventory_of_consonants_n_match'], 
                                                             'q_11_inventory_of_consonants_b_p_match'=> $reliability['q_11_inventory_of_consonants_b_p_match'], 
                                                             'q_11_inventory_of_consonants_d_t_match'=> $reliability['q_11_inventory_of_consonants_d_t_match'], 
                                                             'q_11_inventory_of_consonants_g_k_match'=> $reliability['q_11_inventory_of_consonants_g_k_match'], 
                                                             'q_11_inventory_of_consonants_raw_score_match'=> $reliability['q_11_inventory_of_consonants_raw_score_match'], 
                                                             'q_11_inventory_of_consonants_w_match'=> $reliability['q_11_inventory_of_consonants_w_match'], 
                                                             'q_11_inventory_of_consonants_l_match'=> $reliability['q_11_inventory_of_consonants_l_match'], 
                                                             'q_11_inventory_of_consonants_y_match'=> $reliability['q_11_inventory_of_consonants_y_match'], 
                                                             'q_11_inventory_of_consonants_s_match'=> $reliability['q_11_inventory_of_consonants_s_match'], 
                                                             'q_11_inventory_of_consonants_sh_match'=> $reliability['q_11_inventory_of_consonants_sh_match'], 
                                                             'sounds_weighted_match'=> $reliability['sounds_weighted_match'], 
                                                             'q_12_words_1_match'=> $reliability['q_12_words_1_match'], 
                                                             'q_12_words_2_match'=> $reliability['q_12_words_2_match'], 
                                                             'q_12_words_3_match'=> $reliability['q_12_words_3_match'], 
                                                             'q_12_words_4_match'=> $reliability['q_12_words_4_match'], 
                                                             'q_12_words_5_match'=> $reliability['q_12_words_5_match'], 
                                                             'q_12_words_6_match'=> $reliability['q_12_words_6_match'], 
                                                             'q_12_words_raw_score_match'=> $reliability['q_12_words_raw_score_match'], 
                                                             'q_13_words_1_match'=> $reliability['q_13_words_1_match'], 
                                                             'q_13_words_2_match'=> $reliability['q_13_words_2_match'], 
                                                             'q_13_words_3_match'=> $reliability['q_13_words_3_match'], 
                                                             'q_13_words_4_match'=> $reliability['q_13_words_4_match'], 
                                                             'q_13_words_raw_score_match'=> $reliability['q_13_words_raw_score_match'], 
                                                             'q_13_words_5_match'=> $reliability['q_13_words_5_match'], 
                                                             'q_13_words_6_match'=> $reliability['q_13_words_6_match'], 
                                                             'q_13_words_7_match'=> $reliability['q_13_words_7_match'], 
                                                             'q_13_words_8_match'=> $reliability['q_13_words_8_match'], 
                                                             'q_13_words_9_match'=> $reliability['q_13_words_9_match'], 
                                                             'q_13_words_10_match'=> $reliability['q_13_words_10_match'], 
                                                             'q_13_words_11_match'=> $reliability['q_13_words_11_match'], 
                                                             'q_13_words_12_match'=> $reliability['q_13_words_12_match'], 
                                                             'q_13_words_13_match'=> $reliability['q_13_words_13_match'], 
                                                             'q_13_words_14_match'=> $reliability['q_13_words_14_match'], 
                                                             'q_13_words_15_match'=> $reliability['q_13_words_15_match'], 
                                                             'q_13_words_16_match'=> $reliability['q_13_words_16_match'], 
                                                             'q_14_word_combos_1_match'=> $reliability['q_14_word_combos_1_match'], 
                                                             'q_14_word_combos_2_match'=> $reliability['q_14_word_combos_2_match'], 
                                                             'q_14_word_combos_3_match'=> $reliability['q_14_word_combos_3_match'], 
                                                             'q_14_word_combos_4_match'=> $reliability['q_14_word_combos_4_match'], 
                                                             'q_14_word_combos_5_match'=> $reliability['q_14_word_combos_5_match'], 
                                                             'q_14_word_combos_6_match'=> $reliability['q_14_word_combos_6_match'], 
                                                             'q_14_word_combos_raw_score_match'=> $reliability['q_14_word_combos_raw_score_match'], 
                                                             'q_15_word_combos_1_match'=> $reliability['q_15_word_combos_1_match'], 
                                                             'q_15_word_combos_2_match'=> $reliability['q_15_word_combos_2_match'], 
                                                             'q_15_word_combos_raw_score_match'=> $reliability['q_15_word_combos_raw_score_match'], 
                                                             'q_15_word_combos_3_match'=> $reliability['q_15_word_combos_3_match'], 
                                                             'q_15_word_combos_4_match'=> $reliability['q_15_word_combos_4_match'], 
                                                             'q_15_word_combos_5_match'=> $reliability['q_15_word_combos_5_match'], 
                                                             'q_15_word_combos_6_match'=> $reliability['q_15_word_combos_6_match'], 
                                                             'q_15_word_combos_7_match'=> $reliability['q_15_word_combos_7_match'], 
                                                             'q_15_word_combos_8_match'=> $reliability['q_15_word_combos_8_match'], 
                                                             'words_weighted_match'=> $reliability['words_weighted_match'], 
                                                             'q_16_language_comp_objects_1_match'=> $reliability['q_16_language_comp_objects_1_match'], 
                                                             'q_16_language_comp_objects_2_match'=> $reliability['q_16_language_comp_objects_2_match'], 
                                                             'q_16_language_comp_objects_3_match'=> $reliability['q_16_language_comp_objects_3_match'], 
                                                             'q_16_language_comp_objects_4_match'=> $reliability['q_16_language_comp_objects_4_match'], 
                                                             'q_16_language_comp_raw_score_match'=> $reliability['q_16_language_comp_raw_score_match'], 
                                                             'q_16_language_comp_person_1_match'=> $reliability['q_16_language_comp_person_1_match'], 
                                                             'q_16_language_comp_person_2_match'=> $reliability['q_16_language_comp_person_2_match'], 
                                                             'q_16_language_comp_person_3_match'=> $reliability['q_16_language_comp_person_3_match'], 
                                                             'q_16_language_comp_body_parts_1_match'=> $reliability['q_16_language_comp_body_parts_1_match'], 
                                                             'q_16_language_comp_body_parts_2_match'=> $reliability['q_16_language_comp_body_parts_2_match'], 
                                                             'q_16_language_comp_body_parts_3_match'=> $reliability['q_16_language_comp_body_parts_3_match'], 
                                                             'q_16_language_comp_body_parts_4_match'=> $reliability['q_16_language_comp_body_parts_4_match'], 
                                                             'q_16_language_comp_body_parts_raw_score_match'=> $reliability['q_16_language_comp_body_parts_raw_score_match'], 
                                                             'understanding_weighted_match'=> $reliability['understanding_weighted_match'], 
                                                             'q_17_action_schemes_puts_in_match'=> $reliability['q_17_action_schemes_puts_in_match'], 
                                                             'q_17_action_schemes_puts_on_match'=> $reliability['q_17_action_schemes_puts_on_match'], 
                                                             'q_17_action_schemes_drinks_with_bottle_match'=> $reliability['q_17_action_schemes_drinks_with_bottle_match'], 
                                                             'q_17_action_schemes_drinks_with_cup_match'=> $reliability['q_17_action_schemes_drinks_with_cup_match'], 
                                                             'q_17_action_schemes_hugs_match'=> $reliability['q_17_action_schemes_hugs_match'], 
                                                             'q_17_action_schemes_kisses_match'=> $reliability['q_17_action_schemes_kisses_match'], 
                                                             'q_17_action_schemes_raw_score_match'=> $reliability['q_17_action_schemes_raw_score_match'], 
                                                             'q_17_action_schemes_feeds_with_utensil_match'=> $reliability['q_17_action_schemes_feeds_with_utensil_match'], 
                                                             'q_17_action_schemes_feeds_with_bowl_match'=> $reliability['q_17_action_schemes_feeds_with_bowl_match'], 
                                                             'q_17_action_schemes_stirs_match'=> $reliability['q_17_action_schemes_stirs_match'], 
                                                             'q_17_action_schemes_scoops_match'=> $reliability['q_17_action_schemes_scoops_match'], 
                                                             'q_17_action_schemes_pours_match'=> $reliability['q_17_action_schemes_pours_match'], 
                                                             'q_17_action_schemes_other_match'=> $reliability['q_17_action_schemes_other_match'], 
                                                             'q_17_action_schemes_other_specify_match'=> $reliability['q_17_action_schemes_other_specify_match'], 
                                                             'q_18_actions_towards_other_1_match'=> $reliability['q_18_actions_towards_other_1_match'], 
                                                             'q_18_actions_towards_other_2_match'=> $reliability['q_18_actions_towards_other_2_match'], 
                                                             'q_18_actions_towards_other_3_match'=> $reliability['q_18_actions_towards_other_3_match'], 
                                                             'q_18_actions_towards_other_4_match'=> $reliability['q_18_actions_towards_other_4_match'], 
                                                             'q_18_actions_towards_other_5_match'=> $reliability['q_18_actions_towards_other_5_match'], 
                                                             'q_18_actions_towards_other_6_match'=> $reliability['q_18_actions_towards_other_6_match'], 
                                                             'q_18_actions_towards_other_raw_score_match'=> $reliability['q_18_actions_towards_other_raw_score_match'], 
                                                             'q_19_sequence_action_schemes_1_match'=> $reliability['q_19_sequence_action_schemes_1_match'], 
                                                             'q_19_sequence_action_schemes_2_match'=> $reliability['q_19_sequence_action_schemes_2_match'], 
                                                             'q_19_sequence_action_schemes_3_match'=> $reliability['q_19_sequence_action_schemes_3_match'], 
                                                             'q_19_sequence_action_schemes_4_match'=> $reliability['q_19_sequence_action_schemes_4_match'], 
                                                             'q_19_sequence_action_schemes_5_match'=> $reliability['q_19_sequence_action_schemes_5_match'], 
                                                             'q_19_sequence_action_schemes_6_match'=> $reliability['q_19_sequence_action_schemes_6_match'], 
                                                             'q_19_sequence_action_schemes_raw_score_match'=> $reliability['q_19_sequence_action_schemes_raw_score_match'], 
                                                             'q_20_stacks_tower_match'=> $reliability['q_20_stacks_tower_match'], 
                                                             'q_20_stacks_tower_raw_score_match'=> $reliability['q_20_stacks_tower_raw_score_match'], 
                                                             'object_use_weighted_match'=> $reliability['object_use_weighted']
                                                             ),          
                                                             array('CommentID'=>$this->identifier)
                                                             ); 
            if (PEAR::isError($success)) {
                return PEAR::raiseError("DB Error: ".$success->getMessage());
            }
        }
        
        
          $scoreResult = $this->score();

          if($this->isError($scoreResult)) {
                   return PEAR::raiseError($scoreResult->getMessage());
               }
        
        $this->form->freeze();
        $this->tpl_data['success'] = true;
    }
 

    function _validate($values)
    {
        $DB =& Database::singleton();
        $query = "SELECT count(*) AS counter FROM candidate WHERE CandID='$values[CandID]' and PSCID='$values[PSCID]'";
        $recordsFound = $DB->selectOne($query);
        $errors = array();
        
        if($recordsFound < 1) {
            $errors['CandID'] = "Specified DCCID and PSCID do not exist or do not match.";
        }
        
        return $errors;
    }   
    
    function display()
    {
        if(!$this->form->isFrozen()) {
            // hidden values
            $this->form->addElement('hidden', 'test_name', $this->name);
            $this->form->addElement('hidden', 'subtest', $this->page);
            $this->form->addElement('hidden', 'identifier', $this->identifier);
            $this->form->addElement('hidden', 'reliability_center_id', $this->reliability_center_id);
            $this->form->addElement('submit', 'fire_away', 'Save Data', 'class=button');
         }

        // get the defaults
        $localDefaults = $this->_getDefaults();
        if (PEAR::isError($localDefaults)) {
            return PEAR::raiseError("NDB_Form::display(): ".$localDefaults->getMessage());
        }
        if(!is_array($localDefaults)) { $localDefaults = array(); }
        // set the quickform object defaults
        $this->form->setDefaults(array_merge($this->defaults, $localDefaults));

	    // trim all values
    	$this->form->applyFilter('__ALL__', 'trim');

        // display the HTML_Quickform object
        $smarty = new Smarty_neurodb;
        
        // display the HTML_Quickform object
         return $this->form->toHTML();
        
        $renderer =& new HTML_QuickForm_Renderer_Default();
        $renderer->setFormTemplate("<form{attributes}><table class=\"instrument\">{content}</table></form>");
        $renderer->setElementTemplate("<tr><td class=\"lab\"><!-- BEGIN required --><span style=\"color: #ff0000\">*</span><!-- END required -->{label}</td><td class=\"ele\"><!-- BEGIN error --><span style=\"color: #ff0000\">{error}</span><br /><!-- END error -->{element}</td></tr>");
        $renderer->setElementTemplate("<tr><td class=\"lab\"><i>{label}</i></td><td class=\"ele\">\t<i>{element}</i></td></tr>", "static");
        $renderer->setHeaderTemplate("<tr><th colspan=\"2\"><br><b>{header}</b></th></tr>");
        $this->form->accept($renderer);
        return $renderer->toHtml();
        
    }
  
    function _addMetadataFields()
     {
         $config =& NDB_Config::singleton();
         $dateOptions = array(
                              'language' => 'en',
                              'format'   => 'YMd',
                              'minYear'  => $config->getSetting('startYear'),
                              'maxYear'  => $config->getSetting('endYear'),
                              'addEmptyOption' => true,
                              'emptyOptionValue' => null
                              );

         $this->form->addElement('date', 'Date_taken', 'Date of Administration', $dateOptions);

         $examiners = $this->_getExaminerNames();
         $this->form->addElement('select', 'Examiner', 'Examiner', $examiners);

         //$this->form->addElement('text', 'Examiner', 'Examiner');

         $this->form->addGroupRule('Date_taken', 'Date of Administration is required', 'required');

         $this->form->registerRule('checkdate', 'callback', '_checkDate');
         $this->form->addRule('Date_taken', 'Date of Administration is invalid', 'checkdate');

         $this->form->addRule('Examiner', 'Examiner is required', 'required');
     }

     function _getExaminerNames()
      {
          $db =& Database::singleton();
          $centerID = $db->selectOne("SELECT session.CenterID FROM session, flag WHERE session.ID=flag.SessionID and flag.CommentID='".$this->identifier."'");

          $db->select("SELECT examinerID, full_name FROM examiners WHERE centerID='$centerID' ORDER BY full_name", $results);
          if($db->isError($results)) {
              return $this->raiseError("Could not get examiner names: ".$results->getMessage());
          }

          $examiners = array(''=>'');
          if(is_array($results) && !empty($results)) {
              foreach($results AS $row) {
                  $examiners[$row['examinerID']] = $row['full_name'];
              }
          }
          return $examiners;
      }

      function _getDatabaseDate($formDateValue){
           if(!empty($formDateValue)){
               if(count($formDateValue)==2){
                   $databaseValue = "$formDateValue[H]:$formDateValue[i]";  //handle time (HH:MM:SS)
               } else {
                   $databaseValue = "$formDateValue[Y]-$formDateValue[M]-$formDateValue[d]";  //handle date (YYYY/MM/DD)
               }
           }
           return $databaseValue;
       }


}
?>