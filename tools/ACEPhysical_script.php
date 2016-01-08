<?php
set_include_path(get_include_path().":../libraries:../../php/libraries:");
require_once "NDB_Client.class.inc";
require_once "Utility.class.inc";
require_once "Database.class.inc";
//require_once "../../tools/generic_includes.php";
$client = new NDB_Client();
$client->makeCommandLine();
$client->initialize('../config.xml');

$db        =& Database::singleton();
if (Utility::isErrorX($db)) {
        print "Could not connect to database: " . $db->getMessage();
            exit(1);
}
$mapping = array('height_met'=>'length1','weight_met'=>'weight1','head_circum'=>'head_circumference1','facial_dysmorp'=>'facial_dysmorp',
                 'eyes_strabismus'=>'eyes_strabismus','eyes_ptosis'=>'eyes_ptosis','medprob_ear'=>'medprob_ear','rev_mouthcleftlip'=>'rev_mouthcleftlip',
                 'limb_joint_loos'=>'limb_joint_loos','skin_hypopigmen'=>'skin_hypopigmen','skin_hyperpig'=>'skin_hyperpig',
                 'skin_abnorm'=>'skin_abnorm','hypotonia'=>'hypotonia','hypertonia'=>'hypertonia','muscle_streng'=>'muscle_streng');
$head_measurements_subject = array('head_length_child','weight1_child','head_circumference1_child');
$neuro_screen = array('q4_low_seated_ears','q1_strabismus','q2_ptosis','q4_low_seated_ears','q5_adherent','q6_ear_formation','q7_cleft_palate','q20_hyper_extensibility_of_joints',
                      'q24_ash_leaf_macules','q27_cafe_au_lait_spots','q23_adenoma_sebaceum','q25_shagreen_patches_describe','q28_cutaneous_nodules','q13_tone_symmetrical_abnormality',
                      'q17_power_lower_limb','q18_other_limb_hand_dysmorphic');
$session = $db->pselect("SELECT s.ID from session s
                         JOIN flag f ON ( f.sessionID = s.ID AND f.Test_name=:tname)
                              AND f.CommentID NOT LIKE 'DDE_%'",
                         array('tname'=>'ACESubjectPhysicalExam'));
foreach ($session as $sessionID ) {
$result       = $db->pselect("SELECT h.length1, h.weight1, h.head_circumference1, n.q1_strabismus,n.q2_ptosis,
                              n.q4_low_seated_ears, n.q5_adherent, n.q6_ear_formation, n.q7_cleft_palate,q8_craniofacial_dysmorphic,
                              n.q20_hyper_extensibility_of_joints,
                              n.q24_ash_leaf_macules, n.q27_cafe_au_lait_spots, n.q23_adenoma_sebaceum, n.q25_shagreen_patches_describe,
                              n.q28_cutaneous_nodules,n.q13_tone_symmetrical_abnormality,n.q14_tone_asymmetrical_abnormality,
                              n.q17_power_lower_limb, n.q16_power_upper_limb FROM
                              session s LEFT JOIN flag nflag ON (s.ID = nflag.SessionID AND nflag.Test_name='neuro_screen')
                              LEFT JOIN flag hflag ON (s.ID = hflag.SessionID AND hflag.Test_name='head_measurements_subject')
                              LEFT JOIN neuro_screen n ON (nflag.CommentID = n.CommentID)
                              LEFT JOIN head_measurements_subject h ON (hflag.CommentID = h.CommentID)
                              WHERE s.ID =:sid AND nflag.CommentID NOT LIKE 'DDE%'
                                    AND hflag.CommentID NOT LIKE 'DDE%'", array('sid'=>$sessionID['ID']));
$value_mapping = array('1_covert'=>'yes','2_overt'=>'yes','0_absent'=>'no','9_not_tested'=>'nk','7_can_t_tell'=>'nk',
                       '9_failure_to_test'=>'nk','2_definite'=>'yes','0_absent'=>'no','1_doubtful'=>'nk',
                       '8_suject_unable'=>'nk');
$unable = array('9_failure_to_test','8_suject_unable','not_answered');
foreach($result as $row) {
    if ($row['q1_strabismus'] == '1_covert' || $row['q1_strabismus'] == '2_overt') {
        $row['eyes_strabismus'] = 'yes';
    } else if ($row['q1_strabismus'] == '0_absent') {
        $row['eyes_strabismus'] = 'no';
    } else if ($row['q1_strabismus'] == '9_not_tested' || $row['q1_strabismus'] == '7_can_t_tell' ) {
        $row['eyes_strabismus'] = 'nk';
    }
    if ($row['q2_ptosis'] == '0_absent') {
        $row['eyes_ptosis'] = 'no';
    } else if ($row['q2_ptosis'] == '2_definite' ) { 
        $row['eyes_ptosis'] = 'yes';
    } else if ($row['q2_ptosis'] == '1_doubtful' || $row['q2_ptosis'] == '8_suject_unable' 
               || $row['q2_ptosis'] == '9_failure_to_test') {
        $row['eyes_ptosis'] = 'nk';
    } 
    
    if ($row['q4_low_seated_ears'] == '0_normal' || $row['q5_adherent'] == '0_free_hanging_lobe' 
       || $row['q6_ear_formation'] == '0_normal') {
           $row['medprob_ear'] = 'no';
     } else if ($row['q4_low_seated_ears'] == '1_lower_less_than_0.5_cm' || $row['q4_low_seated_ears'] == '2 lower_greater_than_0.5_cm'
               || $row['q5_adherent'] == '1_adherent_lobe' || $row['q6_ear_formation'] == '1_abnormal' ) {
           $row['medprob_ear'] = 'yes';
     } else if ($row['q4_low_seated_ears'] == '8_subject_unable' || $row['q4_low_seated_ears'] == '9_failure_to_test' 
                || $row['q5_adherent'] == '8_subject_unable' || $row['q5_adherent'] == '9_failure_to_test' 
                || $row['q6_ear_formation'] == '8_subject_unable' || $row['q6_ear_formation'] == '9_failure_to_test' ) {
            $row['medprob_ear'] = 'nk';
     }
     if ($row['q4_low_seated_ears'] == '0_normal' || $row['q8_craniofacial_dysmorphic'] == '0_absent') {
             $row['facial_dysmorp'] = 'no';
      } else if ($row['q4_low_seated_ears'] == '1_lower_less_than_0.5_cm' || $row['q4_low_seated_ears'] == '2 lower_greater_than_0.5_cm'
                  || $row['q8_craniofacial_dysmorphic'] == '2_present') {
            $row['facial_dysmorp'] = 'yes';
      } else if ($row['q4_low_seated_ears'] == '8_subject_unable' || $row['q4_low_seated_ears'] == '9_failure_to_test'
                || $row['q8_craniofacial_dysmorphic'] == '1_uncertain' || $row['q8_craniofacial_dysmorphic'] == '9_failure_to_test'
                || $row['q8_craniofacial_dysmorphic'] == '8_subject_unable') {
            $row['facial_dysmorp'] = 'nk';
     }
     if ($row['q7_cleft_palate'] == '2_present') {
         $row['rev_mouthcleftlip'] = 'yes';
     } else if ($row['q7_cleft_palate'] == '0_absent') {
         $row['rev_mouthcleftlip'] = 'no';
     } else if ($row['q7_cleft_palate'] == '1_uncertain' || $row['q7_cleft_palate'] == '8_subject_unable' 
                || $row['q7_cleft_palate'] == '9_failure_to_test') {
          $row['rev_mouthcleftlip'] = 'nk';
     } 
     if ($row['q20_hyper_extensibility_of_joints'] == '0_within_normal_range') {
          $row['limb_joint_loos'] = 'yes';      
     } else if ($row['q20_hyper_extensibility_of_joints'] == '1_somewhat_increased' 
                || $row['q20_hyper_extensibility_of_joints'] == '2_definite_hyper_extensibility' ) {
          $row['limb_joint_loos'] = 'no';
     } else if ($row['q20_hyper_extensibility_of_joints'] == '8_subject_unable' 
                || $row['q20_hyper_extensibility_of_joints'] == '9_failure_to_test') {
          $row['limb_joint_loos'] = 'nk';
     }
    
     if ($row['q24_ash_leaf_macules'] == '2_present') {
         $row['skin_hypopigmen'] = 'yes';
     } else if ($row['q24_ash_leaf_macules'] == '0_absent') {
         $row['skin_hypopigmen'] = 'no';
     } else if ($row['q24_ash_leaf_macules'] == '8_subject_unable' || $row['q24_ash_leaf_macules'] =='9_failure_to_test' ) {
         $row['skin_hypopigmen'] = 'nk';
     }
     if ($row['q27_cafe_au_lait_spots'] == '1_one_three_spots' || $row['q27_cafe_au_lait_spots'] == '2_four_or_five_spots'
         || $row['q27_cafe_au_lait_spots'] == '3_six_or_more_spots') {
         $row['skin_hyperpig'] = 'yes';
     } else if ($row['q27_cafe_au_lait_spots'] == '0_absent') {
         $row['skin_hyperpig'] = 'no';
     } else if (in_array($row['q27_cafe_au_lait_spots'],$unable ) ) {
         $row['skin_hyperpig'] = 'nk';
     }
     if($row['q25_shagreen_patches_describe'] == '2_present' || $row['q25_shagreen_patches_describe'] == '1_uncertain'
        || $row['q23_adenoma_sebaceum'] == '1_uncertain' || $row['q23_adenoma_sebaceum'] == '2_present'
        || $row['q28_cutaneous_nodules'] == '1_uncertain' || $row['q28_cutaneous_nodules'] == '2_one_or_more' ) {
            $row['skin_abnorm'] = 'yes';
     } else if ($row['q25_shagreen_patches_describe'] == '0_absent' || $row['q23_adenoma_sebaceum'] == '0_absent'
                || $row['q28_cutaneous_nodules'] == '0_absent') {
            $row['skin_abnorm'] = 'no';
     } else if (in_array($row['q25_shagreen_patches'], $unable) || in_array($row['q23_adenoma_sebaceum'], $unable)
                || in_array($row['q28_cutaneous_nodules'], $unable) ) {
            $row['skin_abnorm'] = 'nk';
     }
     if($row['q13_tone_symmetrical_abnormality'] == '2_increased' || $row['q14_tone_asymmetrical_abnormality'] == '2_increased') {
         $row['hypertonia'] = 'yes';
     } else {
         $row['hypertonia'] = 'no';
     }
     if($row['q13_tone_symmetrical_abnormality'] == '3_decreased' || $row['q14_tone_asymmetrical_abnormality'] == '3_decreased') {
         $row['hypotonia'] = 'yes';
     } else {
         $row['hypotonia'] = 'no';
     }

     $limb_weak = array('1_uncertain_mild_weakness', '2_unequivocal_weakness_or_asymmetry');
     if($row['q16_power_upper_limb'] == '0_normal' || $row['q17_power_lower_limb'] == '0_normal') {
         $row['muscle_streng'] = 'no';
     } else if (in_array($row['q16_power_upper_limb'], $limb_weak) || in_array($row['q17_power_lower_limb'], $limb_weak)) {
         $row['muscle_streng'] = 'yes';
     } else if ( in_array($row['q16_power_upper_limb'], $unable) || in_array($row['q17_power_lower_limb'], $unable)) {
         $row['muscle_streng'] = 'nk';
     }


}
$final = array();
foreach($mapping as $key=>$val) {
        $final[$key] = $row[$val];
}
//print_r($final);
$WhereCriteria['CommentID'] = $db->pselectOne("SELECT i.CommentID FROM ACESubjectPhysicalExam i
                                               JOIN flag f ON f.CommentID = i.CommentID
                                               JOIN session s ON s.ID = f.SessionID
                                               WHERE s.ID =:sid AND f.CommentID NOT LIKE 'DDE%'",
                                               array('sid'=>$sessionID['ID']));
$result = $db->update('ACESubjectPhysicalExam', $final, $WhereCriteria);

}
?>
