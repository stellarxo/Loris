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
$mapping = array('height_met'=>'length1','weight_met'=>'weight1','head_circum'=>'head_circumference1','facial_dysmorp'=>'q4_low_seated_ears',
                 'eyes_strabismus'=>'q1_strabismus','eyes_ptosis'=>'q2_ptosis','medprob_ear'=>'q4_low_seated_ears','rev_mouthcleftlip'=>'q7_cleft_palate',
                 'limb_joint_loos'=>'q20_hyper_extensibility_of_joints','skin_hypopigmen'=>'q24_ash_leaf_macules','skin_hyperpig'=>'q27_cafe_au_lait_spots',
                 'skin_abnorm'=>'q23_adenoma_sebaceum','hypotonia'=>'q13_tone_symmetrical_abnormality','hypertonia'=>'q13_tone_symmetrical_abnormality',
                 'muscle_streng'=>'q17_power_lower_limb');
$head_measurements_subject = array('head_length_child','weight1_child','head_circumference1_child');
$neuro_screen = array('q4_low_seated_ears','q1_strabismus','q2_ptosis','q4_low_seated_ears','q5_adherent','q6_ear_formation','q7_cleft_palate','q20_hyper_extensibility_of_joints',
                      'q24_ash_leaf_macules','q27_cafe_au_lait_spots','q23_adenoma_sebaceum','q25_shagreen_patches_describe','q28_cutaneous_nodules','q13_tone_symmetrical_abnormality',
                      'q17_power_lower_limb','q18_other_limb_hand_dysmorphic');

$result       = $db->pselect("SELECT h.length1, h.weight1, h.head_circumference1, n.q4_low_seated_ears, n.q1_strabismus,n.q2_ptosis,
                              n.q4_low_seated_ears, n.q5_adherent, n.q6_ear_formation, n.q7_cleft_palate, n.q20_hyper_extensibility_of_joints,
                              n.q24_ash_leaf_macules, n.q27_cafe_au_lait_spots, n.q23_adenoma_sebaceum, n.q25_shagreen_patches_describe,
                              n.q28_cutaneous_nodules,n.q13_tone_symmetrical_abnormality, n.q17_power_lower_limb, n.q18_other_limb_hand_dysmorphic FROM 
                              session s LEFT JOIN flag nflag ON (s.ID = nflag.SessionID AND nflag.Test_name='neuro_screen') 
                              LEFT JOIN flag hflag ON (s.ID = hflag.SessionID AND hflag.Test_name='head_measurements_subject')
                              LEFT JOIN neuro_screen n ON (nflag.CommentID = n.CommentID)
                              LEFT JOIN head_measurements_subject h ON (hflag.CommentID = h.CommentID) WHERE s.ID = 482 AND nflag.CommentID NOT LIKE 'DDE%' 
                              AND hflag.CommentID NOT LIKE 'DDE%'", array());
foreach($result as $row) {
 print "EUROHERE \n"; 
print_r($row);
}
//print_r($result);
?>
