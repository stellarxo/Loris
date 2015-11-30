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
$session = $db->pselect("SELECT s.ID from session s
                         JOIN flag f ON ( f.sessionID = s.ID AND f.Test_name=:tname)
                              AND f.CommentID NOT LIKE 'DDE_%'",
                         array('tname'=>'ACEFamilyMedicalHistory'));
foreach ($session as $sessionID ) {
$result = $db->pselect("SELECT m.a_aut_spect_disorder, m.a_aut_spect_disorder_who,
                               m.e_rett_syndrome, m.e_rett_syndrome_who,
                               m.p_speech_delay_therapy, m.p_speech_delay_therapy_who,
                               m.m_cerebral_palsy, m.m_cerebral_palsy_who,
                               m.n_mental_retardation , m.n_mental_retardation_who,
                               m.d_neurofibromatosis, m.d_neurofibromatosis_who,
                               m.s_depression, m.s_depression_who,
                               m.r_panic_anxiety_dis, m.r_panic_anxiety_dis_who
                        FROM session s LEFT JOIN flag tflag ON (s.ID = tflag.SessionID AND tflag.Test_name='tsi')
                        LEFT JOIN flag mflag ON (s.ID = mflag.SessionID AND mflag.Test_name='med_psych_hist')
                        LEFT JOIN tsi t ON (tflag.CommentID = t.CommentID)
                        LEFT JOIN med_psych_hist m ON (mflag.CommentID = m.CommentID)
                        WHERE s.ID =:sid AND tflag.CommentID NOT LIKE 'DDE%' AND mflag.CommentID NOT LIKE 'DDE%'",
                        array('sid'=>$sessionID['ID'])) ;

$mapping = array('a_aut_spect_disorder'=>'asd_', 'e_rett_syndrome'=>'rett_syndrome_',
                 'p_speech_delay_therapy'=>'history_speechdelay_', 'm_cerebral_palsy'>'seizure_epilepsy_',
                 'n_mental_retardation'=>'mental_retardation_','s_depression'=>'depression_',
                 'r_panic_anxiety_dis'=>'anxiety_');
$final_result = array();
foreach($result as $row) {
    foreach($mapping as $key=>$val) {
        if ($row[$key] == '1_yes') {
            if (strpos($row[$key."_who"], 'parents_mom') !== false) {
                $final_result[$val."mother"] = 'yes';
            }
            if (strpos($row[$key."_who"], 'parents_dad') !== false) {
                $final_result[$val."father"] = 'yes';
            }
        }

    }
}
$figs = $db->pselect("SELECT fyr.Face_outcome_test, fyr.RelativeCode
                      FROM session s
                      LEFT JOIN flag f ON  f.SessionID = s.ID
                      LEFT JOIN figs_year3_relatives fyr ON fyr.CommentID = f.CommentID
                      WHERE (fyr.RelativeCode ='MOM' OR fyr.RelativeCode='DAD')
                            AND s.ID=:sid", array('sid'=>$sessionID['ID']));
foreach ($figs as $relative) {
    if ($relative['RelativeCode'] == 'MOM' ) {
        if ($relative['Face_outcome_test'] == 1) { // 1= Full mutation
            $final_result['fragilex_mother'] = 'yes';
        } else if ($relative['Face_outcome_test'] == 10) {
            $final_result['fragilex_mother'] = 'no';
        }
    } else if ($relative['RelativeCode'] == 'DAD' ) {
        if ($relative['Face_outcome_test'] == 1) { // 1= Full mutation
            $final_result['fragilex_father'] = 'yes';
        } else if ($relative['Face_outcome_test'] == 10) {
            $final_result['fragilex_father'] = 'no';
        }
    }
}
//print_r($final_result);
$WhereCriteria['CommentID'] = $db->pselectOne("SELECT i.CommentID FROM ACEFamilyMedicalHistory i
                                               JOIN flag f ON f.CommentID = i.CommentID
                                               JOIN session s ON s.ID = f.SessionID
                                               WHERE s.ID =:sid AND f.CommentID NOT LIKE 'DDE%'",
                                               array('sid'=>$sessionID['ID']));
$result = $db->update('ACEFamilyMedicalHistory', $final_result, $WhereCriteria);

}
?>
