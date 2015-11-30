<?php
set_include_path(get_include_path().":../libraries:../../php/libraries:");
//require_once "NDB_Menu_statistics.class.inc";
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

$aloof = array(1,5,9,12,16,18,23,25,27,28,31,36);
$pragmatic_language = array(2,4,7,10,11,14,17,20,21,29,32,34);
$rigid = array(3,6,8,13,15,19,22,24,26,30,33,35);
$candidate_list = $db->pselect("SELECT DISTINCT (s.CandID) FROM flag f JOIN session s ON (s.ID=f.SessionID)
                                WHERE (Test_name = 'pspq_1' OR Test_name='pspq_2') 
                                AND f.CommentID NOT LIKE 'DDE%'", array());
foreach($candidate_list as $cand) {
    $candidate = $cand['CandID'];
    $query         = "SELECT f.CommentID FROM flag f JOIN pspq_1 pspq1 
                      ON (f.CommentID = pspq1.CommentID)
                      JOIN session s on (s.ID = f.SessionID) WHERE s.CandID =:cand";
    $pspq_1        = $db->pselectOne($query, array('cand' =>$candidate));
    if (Utility::isErrorX($pspq_1)) {
        print "Query has failed to select: ".$pspq_1->getMessage();
        //        exit(2);
    }
    $query         = "SELECT f.CommentID FROM flag f JOIN pspq_2 pspq2
                      ON (f.CommentID = pspq2.CommentID)
                      JOIN session s on (s.ID = f.SessionID) WHERE s.CandID =:cand";
    $pspq_2        = $db->pselectOne($query, array('cand' =>$candidate));
    if (Utility::isErrorX($pspq_2)) {
        print "Query has failed to select: ".$pspq_2->getMessage();
        //        exit(2);
    }
    $query         = "SELECT f.CommentID FROM flag f JOIN pspq_score scoring 
                      ON (f.CommentID = scoring.CommentID)
                      JOIN session s on (s.ID = f.SessionID) WHERE s.CandID =:cand";
    $scoreID       = $db->pselectOne($query, array('cand' =>$candidate));
    if (Utility::isErrorX($scoreID)) {
        print "Query has failed to select: ".$scoreID->getMessage();
        //        exit(2);
    }

    $query         = "SELECT * from pspq_1 WHERE CommentID = :CommentID";
    $WhereCriteria = array('CommentID'=>$pspq_1);
    $pspq1_data        = $db->pselectRow($query, $WhereCriteria);
    if (Utility::isErrorX($pspq1_data)) {
            print "Query has failed to select: ".$pspq1_data->getMessage();
    }
    $query         = "SELECT * from pspq_2 WHERE CommentID = :CommentID";
    $WhereCriteria = array('CommentID'=>$pspq_2);
    $pspq2_data        = $db->pselectRow($query, $WhereCriteria);
    
    if (Utility::isErrorX($pspq2_data)) {
            print "Query has failed to select: ".$pspq2_data->getMessage();
    }
    if($pspq1_data['Data_entry_completion_status'] == 'Complete' && 
       $pspq2_data['Data_entry_completion_status'] == 'Complete') {
      
        $parents = array('p1'=>$pspq1_data, 'p2'=>$pspq2_data);
        foreach($parents as $key=>$val) {
            $data = array();
            $data = assignscores($val);
            $data = reversescores($data);
            $scores = calculateSubscaleScores($data, $key);
            $scores[$key."_age"] = $val['respondent_age'];
            $scores[$key."_relation_candidate"] = $val['respondent'];
            $scores[$key."_gender"] = $val['respondent_gender'];
            $scores[$key."_relation_respondent"] = $val['informant'];
            $scores[$key."_informant_gender"] = $val['informant_gender'];
            //save scores
            $result = $db->update('pspq_score', $scores, array('CommentID'=>$scoreID));

        }
    }
    
}
function reversescores($values) {
    $reverse_items = array(1,3,7,9,12,15,16,19,21,23,25,28,30,34,36);
    $participant = array('respondent'=>'q','informant'=>'qi');
    foreach($participant as $key=>$val) {
       foreach($reverse_items as $qnum) {
           $field = $val.$qnum."_";
           foreach($values as $k=>$v) {
               if(strpos($k, $field) !== FALSE && !empty($v)) {
                  $values[$k] = abs($v-6) + 1;
               }    
           }
       }    
    }
    return $values;
}
function assignscores($values) { 
  
  foreach ($values as $key=>$val) {
      $num_val = explode("_", $val);
      $values[$key] = $num_val[0];
  }
  return $values; 
}

function calculateSubscaleScores($values,$parent) {
 $scores = array();
 $subscales = array('aloof'=>array(1,5,9,12,16,18,23,25,27,28,31,36),
                    'rigid'=>array(2,4,7,10,11,14,17,20,21,29,32,34),
                    'pragmatic_language'=> array(3,6,8,13,15,19,22,24,26,30,33,35));
 $aloof = array(1,5,9,12,16,18,23,25,27,28,31,36);
 $pragmatic_language = array(2,4,7,10,11,14,17,20,21,29,32,34);
 $rigid = array(3,6,8,13,15,19,22,24,26,30,33,35);
 $participant = array('respondent'=>'q','informant'=>'qi');
 foreach($participant as $key=>$val) {
     
     $total_count = 0;
     foreach($subscales as $scale=>$qsnts) {
         $scores[$parent."_".$key."_".$scale] = 0;
          $scores[$parent."_".$key."_total"] = 0;
         foreach($qsnts as $qnum) {
             $field = $val.$qnum."_";
             foreach ($values as $k=>$v) {
                 if(strpos($k, $field) !== FALSE) {
                     if (empty($v)) {
                         $scores[$parent."_".$key."_".$scale] = 'N/A';
                         $scores[$parent."_".$key."_total"] = 'N/A';
                         break;
                     } else {
                         //                    print $k."####".$v."\n";
                         $scores[$parent."_".$key."_".$scale] += $v;   
                         $scores[$parent."_".$key."_total"] += $v;
                         $total_count++;
                     } 
                 }
             }
         }
         if($scores[$parent."_".$key."_".$scale] != 'N/A') {
             $scores[$parent."_".$key."_".$scale] = round($scores[$parent."_".$key."_".$scale]/sizeof($qsnts), 2);
         }
     }
     $scores[$parent."_".$key."_total"] = round($scores[$parent."_".$key."_total"]/$total_count,2);
 }
 // calculating best estimate scores
 foreach($subscales as $scale=>$qstns) {
     $scores[$parent.'_best_estimate_'.$scale] = 'N/A';     
     foreach($participant as $key=>$val) {
         $scores[$parent.'_best_estimate_'.$scale] += $scores[$parent."_".$key."_".$scale];
     }
     $scores[$parent.'_best_estimate_'.$scale] = round($scores[$parent.'_best_estimate_'.$scale]/sizeof($participant), 2);
 }
 $scores[$parent.'_best_estimate_total'] = 'N/A';
 foreach($participant as $key=>$val) {
     $scores[$parent.'_best_estimate_total'] += $scores[$parent."_".$key."_total"];

 }

 $scores[$parent.'_best_estimate_total'] = round($scores[$parent.'_best_estimate_total']/sizeof($participant),2);
 return $scores;
}
?>
