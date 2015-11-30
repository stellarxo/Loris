<?php
require_once "NDB_Reliability.class.inc";
//require_once "NDB_BVL_Instrument.class.inc";

/**
 * The forms for the tracking log menu
 * @package mri
 * @subpackage NIHPD
 */
class NDB_Reliability_ados2_module1_reliability extends NDB_Reliability

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
    var $option01238 = array(""=>NULL, 0=>0, 1=>1, 2=>2, 3=>3, 8=>8, "not_answered"=>"Not Answered");
    var $option01234 = array(""=>NULL, 0=>0, 1=>1, 2=>2, 3=>3, 4=>4, "not_answered"=>"Not Answered");
    var $option0128 = array(""=>NULL, 0=>0, 1=>1, 2=>2, 8=>8, "not_answered"=>"Not Answered");
    var $option0123 = array(""=>NULL, 0=>0, 1=>1, 2=>2, 3=>3, "not_answered"=>"Not Answered");
    var $option02 = array(""=>NULL, 0=>0, 2=>2, "not_answered"=>"Not Answered");
    var $option012 = array(""=>NULL, 0=>0, 1=>1, 2=>2, "not_answered"=>"Not Answered");
    var $option0127 = array(""=>NULL, 0=>0, 1=>1, 2=>2, 7=>7, "not_answered"=>"Not Answered");
    var $option01237 = array(""=>NULL, 0=>0, 1=>1, 2=>2,3=>3, 7=>7,"not_answered"=>"Not Answered");
    var $option012378 = array(""=>NULL, 0=>0, 1=>1, 2=>2,3=>3, 7=>7,8=>8,"not_answered"=>"Not Answered");
    var $scoreCols = array("social_affect_total", "restricted_repetitive_behavior_total", "social_affect_restricted_repetitive_behavior_total", "ADOS_classification",
                             'a2_weighted',
                             'a3_weighted',
                             'a8_weighted',
                             'b1_weighted',
                             'b3_weighted',
                             'b4_weighted',
                             'b5_weighted',
                             'b9_weighted',
                             'b10_weighted',
                             'b11_weighted',
                             'b12_weighted',
                             'd1_weighted',
                             'd2_weighted',
                             'd4_weighted',
                             'social_affect_gotham_weighted',
                             'restricted_repetitive_gotham_weighted',
                             'gotham_weighted_score',
                             'severity_score_lookup');

    function _getAgeInMonths() {
        throw new LorisException("Could not calculate age because don't know if subject or proband");
    }
    function _getDefaults()
    {
          
        $DB =& Database::singleton();
        $DB->select("SELECT * FROM {$this->name}", $result);
               
        //print_r($this->identifier);
        if (!empty($this->identifier)) { 
            // set the ados2_module1_reliability values 
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
       
        $instrument_record = $this->_convertScore($score_record1); 
        $reliability_record = $this->_convertScore($score_record);        
        $mismatches  = 0;            
        $denominator = 0;
        $algorithm_mismatches  = 0;
        $algorithm_denominator = 0;
        $age_months = $this->_getAgeInMonths($instrument_record, $reliability_record);
        if($instrument_record['a1'] == 3 || $instrument_record['a1'] == 4) {
             $algorithm_questions = array ('a2','a8','b1','b3','b4','b5','b9','b10','b11','b12','a3','d1','d2','d4');
        } else if ($instrument_record['a1'] == 0 || $instrument_record['a1'] == 1 || $instrument_record['a1'] == 2) {
             $algorithm_questions = array('a2','a7','a8','b1','b3','b4','b5','b9','b10','b12','a5','d1','d2','d4');
        }
        foreach($instrument_record as $key=>$value){ 
            $rel_key = $key;
            $algorithm_question = in_array($key, $algorithm_questions);
            $rel_value = $reliability_record[$rel_key];
	    if(!empty($value) && !empty($rel_value) ) {

		    $denominator++;
		    if($algorithm_question){ 
			    $algorithm_denominator++;
		    }

		    if( $value ==  $rel_value)  continue;
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
             $reliability['Reliability_score_scored_items']= (($algorithm_denominator-$algorithm_mismatches)/$algorithm_denominator*100);

        
      
        // Do the update here for the relibaility scores - saving the scores
		$result = $db->update("{$this->name}", $reliability, array("CommentID"=>$this->identifier, 'reliability_center_id' => $this->reliability_center_id));
		$result = $db->update("reliability", array("Reliability_score" => round(min($reliability['Reliability_score_all_items'], $reliability['Reliability_score_scored_items']),3)), array("CommentID"=>$this->identifier, "Instrument" => preg_replace("/_reliability$/", "", $this->name), 'reliability_center_id' => $this->reliability_center_id));
	 // Update the main relibaility table with the overall reliability score 
                $result1 = $db->update("reliability", array('reliability_score'=> $reliability['Reliability_score_all_items']), array("CommentID"=>$this->identifier));
    } // end function score
    
    function _convertScore( $scores) {
        foreach($scores as $field=>$value) {
            if($value == 0) {
                $scores[$field] = 0;
            } elseif ($value == 1) {
                $scores[$field] = 1;
            } elseif ($value == 2) {
                $scores[$field] = 2;
            } elseif ($value == 3) {
                $scores[$field] = 2;
            } elseif ($value >= 4) {
                $scores[$field] = 0;
            } elseif ($value == "not_answered") {
                $scores[$field] = 0;
            }
        }
        return $scores;
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

    function ados2_module1_reliability()
    {
      $this->create_form();
    }


    function create_form()
    { 
       $this->_addMetadataFields();
       $this->form->addElement("static", "reliability_center", "Site of Reliability Test:");

        //Scoring header
        $this->form->addElement('header', 'instrument_title', "Scoring:");
        $this->form->addElement("static", "Reliability_score_scored_items", "Reliability Score Scored items(%):");
        $this->form->addElement("static", "Reliability_score_all_items", "Reliability All items(%):");
        $this->form->addElement("static", "CommentID", "CommentID:");

        //display test name
        $this->form->addElement('header', null, "CODING:");
        $this->form->addElement("static", null, "<BR>"); //line space

        $this->form->addElement('header', null, "Section A: Language and Communication");
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'a1', '1. Overall Level of Non-Echoed Language', $this->option01234);
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'a2', '2. Frequency of Vocalization Directed to Others', $this->option0123);
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'a3', '3. Intonation of Vocalizations or Verbalization', $this->option0128);
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'a4', '4. Immediate Echolalia', $this->option01238);
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'a5', '5. Stereotyped/Idiosyncratic Use of Words or Phrases', $this->option01238);
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'a6', '6. Use of Others Body to Communicate', $this->option0128);
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'a7', '7. Pointing', $this->option0123);
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'a8', '8. Gestures', $this->option0128);

        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement("static", null, "<BR>"); //line space


           //Section B: Reciprocal Social Interaction
        $this->form->addElement('header', null, "Section B: Reciprocal Social Interaction");
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement("static", null, "<BR>"); //line space

        $this->form->addElement('select', 'b1', '1. Unusual Eye Contact', $this->option02);
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'b2', '2. Responsive Social Smile', $this->option0123);
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'b3', '3. Facial Expressions Directed to Others', $this->option012);
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'b4', '4. Integration of Gaze and Other Behaviors During Social Overtures', $this->option0123);
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'b5', '5. Shared Enjoyment in Interaction', $this->option0123);
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'b6', '6. Response to Name', $this->option0123);
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'b7', '7. Requesting', $this->option0123);
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'b8', '8. Giving', $this->option012);
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'b9', '9. Showing', $this->option012);
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'b10', '10. Spontaneous Initiation of Joint Attention', $this->option012);
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'b11', '11. Response to Joint Attention', $this->option0123);
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'b12', '12. Quality of Social Overtures', $this->option0123);
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select','b13a','13a. Amount of Social Overtures/Maintenance of Attention:EXAMINER',$this->option01237);
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select','b13b','13b. Amount of Social Overtures/Maintenance of Attention:PARENT/CAREGIVER',$this->option012378);
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select','b14','14. Quality of Social Response',$this->option0123);
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select','b15','15. Level Of Engagement',$this->option0123);
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select','b16','16. Overall Quality of Rapport',$this->option0123);
        $this->form->addElement("static", null, "<BR>"); //line space

        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement("static", null, "<BR>"); //line space

        $this->form->addElement('header', null, "Section C: Play");
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'c1', '1. Functional Play with Objects', $this->option0123);
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'c2', '2. Imagination/Creativity', $this->option0123);

        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement("static", null, "<BR>"); //line space

        //Section D: Stereotyped Behaviors and Restricted Interests
        $this->form->addElement('header', null, "Section D: Stereotyped Behaviors and Restricted Interests");
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'd1', '1. Unusual Sensory Interest in Play Material/Person', $this->option0123);
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->addTextAreaElement('d1_specify', $this->indent . "Please specify:");
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'd2', '2. Hand and Finger and Other Complex Mannerisms', $this->option0123);
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->addTextAreaElement('d2_specify', $this->indent . "Please specify:");
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'd3', '3. Self-Injurious Behavior', $this->option012);
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'd4', '4. Unusually Repetitive Interests or Stereotyped Behaviors', $this->option0123);
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->addTextAreaElement('d4_specify', $this->indent . "Please specify unusual preoccupations, rituals, repetitive behaviors:");

        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement("static", null, "<BR>"); //line space

        //Section E: Other Abnormal Behaviors
        $this->form->addElement('header', null, "Section E: Other Abnormal Behaviors");
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'e1', '1. Overactivity', $this->option01237);
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'e2', '2. Tantrums, Aggression, Negative or Disruptive Behavior', $this->option0123);
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'e3', '3. Anxiety', $this->option012);

        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement("static", null, "<BR>"); //line space
 
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
