<?php
require_once "NDB_Reliability.class.inc";
//require_once "NDB_BVL_Instrument.class.inc";

/**
 * The forms for the tracking log menu
 * @package mri
 * @subpackage NIHPD
 */
class NDB_Reliability_aims_reliability extends NDB_Reliability

{
// function _hasAccess()
//     {
//         // create user object
//         $user =& User::singleton();

//         $DB =& Database::singleton();
       
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

    function _getAgeInMonths() {
        throw new LorisException("Could not calculate age because don't know if subject or proband");
    }
    function _getDefaults()
    {
          
        $DB =& Database::singleton();
        $DB->select("SELECT * FROM {$this->name}", $result);
               
        //print_r($this->identifier);
        if (!empty($this->identifier)) { 
            // set the aims_reliability values 
            $DB->selectRow("SELECT * FROM {$this->name} WHERE CommentID = '$this->identifier' AND reliability_center_id='$this->reliability_center_id'", $row);
     
            // Set the defaults
            // print_r($row['CommentID']);
            
            $sites = array(1 => 'DCC', 2 => 'SEA', 3 => 'PHI', 4 => 'STL', 5 => 'UNC');
                        
            $initial_table = preg_replace('/_reliability/', '', $this->name);
            
            foreach($row as $key=>$value) {
                $defaults[$key] = $value;    
            }
            $defaults['CommentID'] = "<a href=\"main.php?test_name=reliability_breakdown&instrument=$initial_table&CommentID=$row[CommentID]\">" . $row['CommentID'] . "</a>";

        } else {
            echo("Identifer empty! No ID has been chosen. Please contact Samir at the DCC.<br>");
        }

        return $defaults;
    }

   
    function score(){      
        //holds raw question values
        $score_record = array();
        //holds calculated
        $db =& Database::singleton();

        // null scores
        //$this->_nullScores();
       $initial_table = preg_replace('/_reliability/', '', $this->name);
       
        //Get values from both tables of adi_r (reliability and original)
        $query = "SELECT * FROM {$this->name} WHERE CommentID='".$this->identifier."'  AND reliability_center_id='$this->reliability_center_id'";
        $query1 = "SELECT * FROM {$initial_table} WHERE CommentID='".$this->identifier."'";

        $db->selectRow($query, $score_record);             
        $db->selectRow($query1, $score_record1);
       
        $instrument_record = $score_record1; 
        $reliability_record = $score_record;        
        $mismatches  = 0;            
        $denominator = 0;
        $algorithm_mismatches  = 0;
        $algorithm_denominator = 0;
        $age_months = $this->_getAgeInMonths($instrument_record, $reliability_record);
        $algorithm_questions = array('q1_pronelying1','q2_pronelying2','q3_prone_prop','q4_forearmsupport1','q5_prone_mobility','q6_forearmsupport2','q7_extended_armsupport','q8_rollingprone_supine_wo_rotation','q9_swimming','q10_reach_forearmsupport','q11_pivoting','q12_rollingprone_supine_w_rotation','q13_fourpoint_kneeling','q14_propped_sidelying','q15_reciprocal_crawling','q16_fourptkneel_sit_halfsit','q17_reciprocal_creeping1','q18_reach_extended_armsupport','q19_fourpoint_kneeling2','q20_mod_fourpoint_kneeling','q21_reciprocal_creeping2','q22_supinelying1','q23_supinelying2','q24_supinelying3','q25_supinglying4','q26_hands_knees','q27_active_extension','q28_hands_feet','q29_rollingsupine_prone_wo_rotation','q30_rollingsupine_prone_w_rotation','q31_sit_w_support','q32_sit_proppedarms','q33_pullsit','q34_unsustained_sitting','q35_sit_w_armsupport','q36_unsustained_sit_wo_armsupport','q37_weightshift_unsustainedsit','q38_sit_wo_armsupport1','q39_reach_rotation_sit','q40_sit_prone','q41_sit_fourpoint_kneel','q42_sit_wo_armsupport2','q43_supportedstand1','q44_supportedstand2','q45_supportstand3','q46_pullstand_w_support','q47_pullstand','q48_supportstand_w_rotation','q49_cruise_wo_rotation','q50_halfkneel','q51_controllower_stand','q52_cruise_w_rotation','q53_standalone','q54_earlystep','q55_stand_modsquat','q56_stand_quadposition','q57_walkalone','q58_squat');
        foreach($instrument_record as $key=>$value){ 
            if(!preg_match("/^q[1-9]/", $key)) continue;
            $rel_key = $key;
            $algorithm_question = in_array($key, $algorithm_questions);
            $rel_value = $reliability_record[$rel_key];
	    if(!empty($value) && !empty($rel_value) ) {

		    $denominator++;
		    if($algorithm_question){ 
			    $algorithm_denominator++;
		    }


		    if( $this->_checkEquivalency($value,$rel_value))  continue;
		    //echo("MISMATCH<BR>");                 
		    $mismatches++;
		    if($algorithm_question){
			    $algorithm_mismatches++;
		    }
	    }
        }
        //print "Denominator : $denominator , MISMATCHES : $mismatches, ALG_DENOM : $algorithm_denominator, ALG_MISMATCH : $algorithm_mismatches";
             // Score the reliability
             $reliability['Reliability_score_all_items']= (($denominator-$mismatches)/$denominator*100);
            // $reliability['Reliability_score_scored_items']= (($algorithm_denominator-$algorithm_mismatches)/$algorithm_denominator*100);

        
      
        // Do the update here for the relibaility scores - saving the scores
            $result = $db->update("{$this->name}", $reliability, array("CommentID"=>$this->identifier, 'reliability_center_id' => $this->reliability_center_id));
            $result = $db->update("reliability", array("Reliability_score" => round(min($reliability['Reliability_score_all_items'], $reliability['Reliability_score_scored_items']),3)), array("CommentID"=>$this->identifier, "Instrument" => preg_replace("/_reliability$/", "", $this->name), 'reliability_center_id' => $this->reliability_center_id));
            // Update the main relibaility table with the overall reliability score 
            $result1 = $db->update("reliability", array('reliability_score'=> $reliability['Reliability_score_all_items']), array("CommentID"=>$this->identifier));
    } // end function score
    
    function _checkEquivalency( $val, $rel_val) {
        if ($val == 'credited' && ($rel_val == 'observed' || $rel_val == 'credited') ) {
            return true;
        } else if ($val == 'not_observed' && ($rel_val == 'above_ceiling' || $rel_val == 'not_observed') ) {
            return true;
        } else if($val == 'observed' && ($rel_val == 'observed' || $rel_val == 'credited') ) {
            return true;
        } else if($val == 'above_ceiling' && ($rel_val == 'above_ceiling' || $rel_val == 'not_observed') ) {
            return true;
        }
        
        return false;
    } 
    function _nullScores()
    {
        $db=& Database::singleton();
        
        // set the scores to NULL
        foreach ($this->scores as $val) {
            $scores[$val]=null;
        }

        // update the scores
        $success = $db->update("{$this->name}",$scores,array("CommentID"=>$this->identifier, 'reliability_center_id' => $this->reliability_center_id));
        return;
    }    

    function aims_reliability()
    {
      $this->create_form();
    }


    function create_form()
    { 
       $this->_addMetadataFields();
       $this->form->addElement("static", "reliability_center", "Site of Reliability Test:");

        //Scoring header
        $this->form->addElement('header', 'instrument_title', "Scoring:");
       // $this->form->addElement("static", "Reliability_score_scored_items", "Reliability Score All items(%):");
        $this->form->addElement("static", "Reliability_score_all_items", "Reliability Scored items(%):");
        $this->form->addElement("static", "CommentID", "CommentID:");

        //display test name

 
        $this->form->addElement('header',null,'Prone');
        $this->addSelect('prone_first_item','First Item Within Window:', array(NULL=>'','1'=>'Prone Lying(1)','2'=>'Prone Lying(2)','3'=>'Prone Prop','4'=>'Forearm Support(1)','5'=>'Prone Mobility','6'=>'Forearm Support(2)','7'=>'Extended Arm Support','8'=>'Rolling Prone to Supine w/o Rotation','9'=>'Swimming','10'=>'Reaching from Forearm Support','11'=>'Pivots','12'=>'Rolling Prone to Supine with Rotation','13'=>'Four-Point Kneeling','14'=>'Propped Sidelying','15'=>'Reciprocal Crawling','16'=>'Four-Point Kneeling to Sitting/Half-Sitting','17'=>'Reciprocal Creeping(1)','18'=>'Reaching from Extended Arm Support','19'=>'Four-Point Kneeling(2)','20'=>'Modified Four-Point Kneeling','21'=>'Reciprocal Creeping(2)'));
        $this->addSelect('prone_last_item','Last Item Within Window:', array(NULL=>'','1'=>'Prone Lying(1)','2'=>'Prone Lying(2)','3'=>'Prone Prop','4'=>'Forearm Support(1)','5'=>'Prone Mobility','6'=>'Forearm Support(2)','7'=>'Extended Arm Support','8'=>'Rolling Prone to Supine w/o Rotation','9'=>'Swimming','10'=>'Reaching from Forearm Support','11'=>'Pivots','12'=>'Rolling Prone to Supine with Rotation','13'=>'Four-Point Kneeling','14'=>'Propped Sidelying','15'=>'Reciprocal Crawling','16'=>'Four-Point Kneeling to Sitting/Half-Sitting','17'=>'Reciprocal Creeping(1)','18'=>'Reaching from Extended Arm Support','19'=>'Four-Point Kneeling(2)','20'=>'Modified Four-Point Kneeling','21'=>'Reciprocal Creeping(2)'));
        $this->addSelect('q1_pronelying1','<b>Prone Lying(1): </b>Phsiological flexion - Turns head to clear nose from surface', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->addSelect('q2_pronelying2','<b>Prone Lying(2):</b> Lifts head symmetrically to 45 degrees - Cannot maintain head in midline', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->addSelect('q3_prone_prop','<b>Prone Prop: </b> Elbows behind shoulders - Unsustained head raising to 45 degrees', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->addSelect('q4_forearmsupport1','<b>Forearm Support(1): </b>Lifts and maintains head past 45 degrees - Elbows in line with shoulders - Chest Centered', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->addSelect('q5_prone_mobility','<b>Prone Mobility: </b> Head to 90 degrees - Uncontrolled Weight Shifts', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->addSelect('q6_forearmsupport2','<b>Forearm Support(2): </b>Elbows in front of shoulder - Active chin tuck with neck elongation', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->addSelect('q7_extended_armsupport','<b>Extended Arm Support: </b>Arms extended - Chin tuck and chest elevated - Lateral weight shift', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->addSelect('q8_rollingprone_supine_wo_rotation','<b>Rolling Prone to Supine Without Rotation: </b>Movement initiated by head - Trunk moves as one unit', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->addSelect('q9_swimming','<b>Swimming: </b>Active extensor pattern', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->addSelect('q10_reach_forearmsupport','<b>Reaching from Forearm Support: </b>Active weight shift from one side - Controlled reach with free arm', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->addSelect('q11_pivoting','<b>Pivots : </b>Pivots - Movement in arms and legs - Lateral trunk flexion', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->addSelect('q12_rollingprone_supine_w_rotation','<b>Rolling Prone to Supine with Rotation: </b>Trunk rotation', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->addSelect('q13_fourpoint_kneeling','<b>Four-Point Kneeling: </b>Legs flexed, abducted, and externally rotated - Lumbar lordosis - Maintains position', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->addSelect('q14_propped_sidelying','<b>Propped Sidelying: </b>Dissociation of legs - Shoulder stability - Rotation within body axis', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->addSelect('q15_reciprocal_crawling','<b>Reciprocal Crawling: </b>Reciprocal arm and leg movements with trunk rotation', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->addSelect('q16_fourptkneel_sit_halfsit','<b>Four-Point Kneeling to Sitting or Half-Sitting: </b>Plays in and out of position - May get to sitting', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->addSelect('q17_reciprocal_creeping1','<b>Reciprocal Creeping(1): </b>Legs abducted, and externally rotated - Lumbar lordosis: weight shift side to side with lateral trunk flexion', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->addSelect('q18_reach_extended_armsupport','<b>Reaching from Extended Arm Support: </b>Reaches with extended arm - Trunk rotation', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->addSelect('q19_fourpoint_kneeling2','<b>Four-Point Kneeling(2) :</b>Hips aligned under pelvis - Flattening of lumbar spine', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->addSelect('q20_mod_fourpoint_kneeling','<b>Modified Four-Point Kneeling: </b>Plays in position - May move forward', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->addSelect('q21_reciprocal_creeping2','<b>Reciprocal Creeping(2) :</b>Lumbar spine flat - Moves with trunk rotation', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->form->addElement('header',null,'Supine');
        $this->addSelect('supine_first_item','First Item in Window', array(NULL=>'','22'=>'Supine Lying(1)','23'=>'Supine Lying(2)','24'=>'Supine Lying(3)','25'=>'Supine Lying(4)','26'=>'Hands to Knees','27'=>'Active Extension','28'=>'Hands to Feet','29'=>'Rolling Supine to Prone Without Rotation','30'=>'Rolling Supine to Prone With Rotation'));
        $this->addSelect('supine_last_item','Last Item in Window', array(NULL=>'','22'=>'Supine Lying(1)','23'=>'Supine Lying(2)','24'=>'Supine Lying(3)','25'=>'Supine Lying(4)','26'=>'Hands to Knees','27'=>'Active Extension','28'=>'Hands to Feet','29'=>'Rolling Supine to Prone Without Rotation','30'=>'Rolling Supine to Prone With Rotation'));
        $this->addSelect('q22_supinelying1','<b>Supine Lying(1): </b>Physiological flexion - Head rotation: mouth to hand - Random arm and leg movement', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->addSelect('q23_supinelying2','<b>Supine Lying(2): </b>Head rotation towards midline - Nonobligatory ATNR', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->addSelect('q24_supinelying3','<b>Supine Lying(3)</b>Head in midline - Moves arms but unable to bring hands to midline', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->addSelect('q25_supinglying4','<b>Supine Lying(4): </b>Neck flexors active - chin tuck - Brings hands to midline', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->addSelect('q26_hands_knees','<b>Hands to Knees: </b>Chin tuck - Reaches hands to knees - Abdominals active', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->addSelect('q27_active_extension','<b>Active Extension: </b>Pushes into extension with legs', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->addSelect('q28_hands_feet','<b>Hands to Feet: </b>Can maintain legs in mid-range - Pelvic mobility present', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->addSelect('q29_rollingsupine_prone_wo_rotation','<b>Rolling Supine to Prone Without Rotation: </b>Lateral head righting - Trunk moves as one unit', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->addSelect('q30_rollingsupine_prone_w_rotation','<b>Rolling Supine to Prone With Rotation: </b>Trunk rotation', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->form->addElement('header',null,'Sitting');
        $this->addSelect('sit_first_item','First Item in Window', array(NULL=>'','31'=>'Sitting With Support','32'=>'Sitting With Propped Arms','33'=>'Pull to Sit','34'=>'Unsustained Sitting','35'=>'Sitting With Arm Support','36'=>'Unsustained Sitting Without Arm Support','37'=>'Weight Shift in Unsustained Sitting','38'=>'Sitting Without Arm Suport','39'=>'Reach With Rotation in Sitting','40'=>'Sitting to Prone','41'=>'Sitting to Four-point Kneeling','42'=>'Sitting Without Arm Support(2)'));
        $this->addSelect('sit_last_item','Last Item in Window', array(NULL=>'','31'=>'Sitting With Support','32'=>'Sitting With Propped Arms','33'=>'Pull to Sit','34'=>'Unsustained Sitting','35'=>'Sitting With Arm Support','36'=>'Unsustained Sitting Without Arm Support','37'=>'Weight Shift in Unsustained Sitting','38'=>'Sitting Without Arm Suport','39'=>'Reach With Rotation in Sitting','40'=>'Sitting to Prone','41'=>'Sitting to Four-point Kneeling','42'=>'Sitting Without Arm Support(2)'));
        $this->addSelect('q31_sit_w_support','<b>Sitting With Support: </b>Lifts and maintains head in midline briefly', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->addSelect('q32_sit_proppedarms','<b>Sitting With Propped Arms: </b>Maintains head in midline - Supports weight on arms briefly', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->addSelect('q33_pullsit','<b>Pull to Sit: </b>Chin tuck: head in line or in front of body', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->addSelect('q34_unsustained_sitting','<b>Unsustained Sitting: </b>Scapular adduction  and humeral extension - Cannot maintain position', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->addSelect('q35_sit_w_armsupport','<b>Sitting With Arm Support: </b>Thoracic spine extended - Head movements free from trunk: propped on extended arms', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->addSelect('q36_unsustained_sit_wo_armsupport','<b>Unustained Sitting Without Arm Support :</b>Cannot be left alone in sitting indefinitely', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->addSelect('q37_weightshift_unsustainedsit','<b>Weight Shift in Unsustained Sitting: </b>Weight shift forward, backwards, and sideways - Cannot be left alone in sitting', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->addSelect('q38_sit_wo_armsupport1','<b>Sitting Without Arm Support(1): </b>Arms move away from body - Can play with a toy - Can be left alone in sitting', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->addSelect('q39_reach_rotation_sit','<b>Reach With Rotation in Sitting: </b>Sits independently - Reaches for toy with trunk rotation', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->addSelect('q40_sit_prone','<b>Sitting to Prone: </b>Moves out of sitting to achieve prone lying - Pulls with arms: legs inactive', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->addSelect('q41_sit_fourpoint_kneel','<b>Sitting to Four-Point Kneeling: </b>Actively lifts pelvis, buttocks, and unweighted leg to assume four-point kneeling', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->addSelect('q42_sit_wo_armsupport2','<b>Sitting Without Arm Support(2): </b>Position of legs varies - Infant moves in and out of positions easily', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->form->addElement('header',null,'Standing');
        $this->addSelect('stand_first_item','First Item in Window', array(NULL=>'','43'=>'Supported Standing(1)','44'=>'Supported Standing(2)','45'=>'SupportedStanding(3)','46'=>'Pull to Stand W Support','47'=>'Pull to Stand/Stands','48'=>'Supported Standing W Rotation','49'=>'Cruising W/O Rotation','50'=>'Half-Kneeling','51'=>'Controlling lowering through Standing','52'=>'Cruising With Rotation','53'=>'Stands Alone','54'=>'Early Stepping','55'=>'Standing from Modified Squat','56'=>'Standing from Quadrupled Position','57'=>'Walks Alone','58'=>'Squat'));
        $this->addSelect('stand_last_item','Last Item in Window', array(NULL=>'','43'=>'Supported Standing(1)','44'=>'Supported Standing(2)','45'=>'SupportedStanding(3)','46'=>'Pull to Stand W Support','47'=>'Pull to Stand/Stands','48'=>'Supported Standing W Rotation','49'=>'Cruising W/O Rotation','50'=>'Half-Kneeling','51'=>'Controlling lowering through Standing','52'=>'Cruising With Rotation','53'=>'Stands Alone','54'=>'Early Stepping','55'=>'Standing from Modified Squat','56'=>'Standing from Quadrupled Position','57'=>'Walks Alone','58'=>'Squat'));
        $this->addSelect('q43_supportedstand1','<b>Supported Standing(1): </b>May have intermittent hip and knee flexion', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->addSelect('q44_supportedstand2','<b>Supported Standing(2): </b>Head in line with body - Hips behind shoulders - Variable movement of legs', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->addSelect('q45_supportstand3','<b>Supported Standing(3): </b>Hips in line with shoulders- Active control of trunk - Variable movements of legs', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->addSelect('q46_pullstand_w_support','<b>Pull to Stand With Support : </b> Pushes down with arms and extends knees', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->addSelect('q47_pullstand','<b>Pull to Stand/Stands :</b> Pulls to stand;shifts weight from side to side', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->addSelect('q48_supportstand_w_rotation','<b>Supported Standing With Rotation :</b> Rotation of trunk and pelvis', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->addSelect('q49_cruise_wo_rotation','<b>Cruising Without Rotation :</b> Cruises sideways without rotation', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->addSelect('q50_halfkneel','<b>Half Kneeling :</b> May assume standing or play in position', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->addSelect('q51_controllower_stand','<b>Controlling Lowering Through Standing :</b> Controlled lowering from standing', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->addSelect('q52_cruise_w_rotation','<b>Cruising With Rotation :</b> Cruises with rotation', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->addSelect('q53_standalone','<b>Stands Alone :</b> Stands alone momentarily- Balance reactions in feet', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->addSelect('q54_earlystep','<b>Early Stepping :</b> Walks independently; moves quickly with short steps', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->addSelect('q55_stand_modsquat','<b>Standding from Modified Squat :</b> Moves from squat to standing with controlled flexion and extension of hips and knees', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->addSelect('q56_stand_quadposition','<b>Standing from Quadruped Position :</b> Pushes quickly with hands to get standing', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->addSelect('q57_walkalone','<b>Walks Alone :</b> Walks independently', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));
        $this->addSelect('q58_squat','<b>Squat :</b> Maintains position by balance reactions in feet and position of trunk', array(NULL=>'','credited'=>'credited','observed'=>'observed','not_observed'=>'not_observed','above_ceiling'=>'above_ceiling'));

        
    } // End function 

 
   	
	function _cleanTo3Digits($string) {
	   return ereg_replace("[^0-9]", "", substr($string, 0, 3));
	}

 function _process($values)
 {
       
        $DB =& Database::singleton();

        $user =& User::singleton();
          
        $DB->selectRow("SELECT * FROM {$this->name} WHERE CommentID = '$this->identifier' AND reliability_center_id = $this->reliability_center_id", $row);
          
          $invalid = $values['invalid'];
          $DB->update("reliability", array('invalid' => $invalid), array("CommentID"=>$this->identifier, "Instrument" => preg_replace("/_reliability$/", "", $this->name), "reliability_center_id" => $this->reliability_center_id));
          unset($values['invalid']);
          
          if($invalid == "yes"){
            $this->form->freeze();
            $this->tpl_data['success'] = true;
            return;
          }
          foreach($values as $key=>$value) {
             if($key == 'Date_taken' || $key == 'DoB_proband'){
                $values[$key] = $this->_getDatabaseDate($values[$key]);    
             }    
          }
          if (empty($row)) {
            
            $values['CommentID'] = $this->identifier;
            $values['reliability_center_id'] = $this->reliability_center_id;
            // insert the event
            $success = $DB->insert($this->name, $values);
        } else {
            // update the event 
            $success = $DB->update($this->name, $values,          
                                   array('CommentID'=>$this->identifier, 'reliability_center_id' => $this->reliability_center_id)
                                   ); 
        }
        
        $scoreResult = $this->score();
        
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
     
 } // end function display
 
 
}
?>
