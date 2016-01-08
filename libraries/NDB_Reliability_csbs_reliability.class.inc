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
    var $columns = array('q_1_gaze_shifts_raw_score',
        'q_2_shared_positive_affect_raw_score',
        'q_3_gaze_point_following_raw_score',
        'q_4_rate_of_communicating_raw_score',
        'q_5_behaviour_regulation_raw_score',
        'q_6_social_interaction_raw_score',
        'q_7_joint_attention_raw_score',
        'q_8_conventional_gestures_raw_score',
        'q_9_distal_gestures_raw_score',
        'q_10_syllables_consonants_raw_score',
        'q_11_inventory_of_consonants_raw_score',
        'q_12_words_raw_score',
        'q_13_words_raw_score',
        'q_14_word_combos_raw_score',
        'q_15_word_combos_raw_score',
        'q_16a_language_comp_object_raw_score',
        'q_16b_language_comp_person_name_raw_score',
        'q_16c_language_comp_body_parts_raw_score',
        'q_17_action_schemes_raw_score',
        'q_18_actions_towards_other_raw_score',
        'q_19_sequence_action_schemes_raw_score',
        'q_20_stacks_tower_raw_score'
    );

    function _getDefaults()
    {
        $DB =& Database::singleton();
               
        if (!empty($this->identifier)) { 
            
            // get the csbs_reliability values 
            $DB->selectRow("SELECT * FROM csbs_reliability WHERE CommentID = '$this->identifier' AND reliability_center_id = '$this->reliability_center_id'", $defaults);

            // Make the CommentID a link to the comparison page
            $initial_table = preg_replace('/_reliability/', '', $this->name);
            $defaults['CommentID'] = "<a href=\"main.php?test_name=reliability_breakdown&instrument=$initial_table&CommentID=$defaults[CommentID]\">" . $defaults['CommentID'] . "</a>";
        } else {
            echo("Identifer empty! No ID has been chosen. Please contact Samir at the DCC.<br>");
        }
        
        $sites = array(1 => 'DCC', 2 => 'SEA', 3 => 'PHI', 4 => 'STL', 5 => 'UNC');
        $defaults['reliability_center'] = $sites[$this->reliability_center_id];

        return $defaults;
    }

    function score() {

        //holds raw question values
        $score_record = array();
        
        //holds calculated
        $db =& Database::singleton();

        // null scores
        //$this->_nullScores();

        //Get values from both tables of csbs (reliability and original)
        $query = "SELECT * FROM csbs_reliability WHERE CommentID='$this->identifier' AND reliability_center_id = '$this->reliability_center_id'";
        $query1 = "SELECT * FROM csbs WHERE CommentID='".$this->identifier."'";
        $query2 = "SELECT * FROM csbs_wetherby_lookup WHERE CommentID='standard1'";
 
        $db->selectRow($query, $score_record);
        $db->selectRow($query1, $score_record1);
        $db->selectRow($query2, $score_record2);
     
        // Do the actual CSBS scoring (as is done for regular data entry)
        if ($score_record['Gold_standard']=='Initial_entry') {
            $comparison = $score_record1;
        } else if($score_record['Gold_standard'] === 'Gold_standard' ) {
            $comparison = $score_record2;
        }

        // Calculate the scoring reliability
        $score = 0;
        foreach($this->columns as $key) {
            if($this->compareScore($key, $comparison, $score_record)) {
                $score += 1;
            } 
        }
        if($score_record['Gold_standard'] !== 'Initial_entry' && $score_record['Gold_standard'] !== 'Gold_standard') {
            echo("<font color='red'>Warning: no comparison selected. Contact Samir at the DCC.</font><BR>");
        }
        

        $score_percent = ($score / 22.0) * 100;
    
        $result = $db->update("reliability", array('Reliability_score' => $score_percent), array("CommentID"=>$this->identifier, "Instrument" => 'csbs', "reliability_center_id" => $this->reliability_center_id));
        $result = $db->update("csbs_reliability", array('reliability_score' => $score_percent), array("CommentID"=>$this->identifier, "reliability_center_id" => $this->reliability_center_id));
    } // end function score

    function compareScore($field, $original, $comparison) {
        // If it's within 1, it's "Agree"
        if(abs($comparison[$field] - $original[$field]) <= 1) {
            return true;
        }
        return false;
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
        
        //         $this->addTextElement("filled_out_by", "Filled out by:");
        //         $this->addTextElement("relationship_to_child", "Relationship to child:");

        $GoldStandardArray = array("Initial_entry"=>"Initial Entry", "Gold_standard"=>"Gold standard" );
       
        $this->form->addElement("select", "Gold_standard", "Compare against:", $GoldStandardArray);
        $this->form->addElement("static", "CommentID", "CommentID:");

        $options = array('' => NULL);
        foreach(range(0, 20) as $i) {
            $options[$i] = $i;
        };

        $this->form->addElement('select', 'q_1_gaze_shifts_raw_score', '1. Gaze shifts', $options);
        $this->form->addElement('select', 'q_2_shared_positive_affect_raw_score', '2. Shared positive affect', $options);
        $this->form->addElement('select', 'q_3_gaze_point_following_raw_score', '3. Gaze/point following', $options);
        $this->form->addElement('select', 'q_4_rate_of_communicating_raw_score', '4. Rate of communicating', $options);
        $this->form->addElement('select', 'q_5_behaviour_regulation_raw_score', '5. Behavior regulation', $options);
        $this->form->addElement('select', 'q_6_social_interaction_raw_score', '6. Social interaction', $options);
        $this->form->addElement('select', 'q_7_joint_attention_raw_score', '7. Joint attention', $options);
        $this->form->addElement('select', 'q_8_conventional_gestures_raw_score', '8. Inventory of conventional gestures', $options);
        $this->form->addElement('select', 'q_9_distal_gestures_raw_score', '9. Distal gestures', $options);
        $this->form->addElement('select', 'q_10_syllables_consonants_raw_score', '10. Syllables with consonants', $options);

        $this->form->addElement('select', 'q_11_inventory_of_consonants_raw_score', '11. Inventory of consonants', $options);
        $this->form->addElement('select', 'q_12_words_raw_score', '12. Words', $options);
        $this->form->addElement('select', 'q_13_words_raw_score', '13. Inventory of words', $options);
        $this->form->addElement('select', 'q_14_word_combos_raw_score', '14. Word combinations', $options);
        $this->form->addElement('select', 'q_15_word_combos_raw_score', '15. Inventory of world combinations', $options);
        $this->form->addElement('select', 'q_16a_language_comp_object_raw_score', '16a. Object name', $options);
        $this->form->addElement('select', 'q_16b_language_comp_person_name_raw_score', '16b. Person name', $options);
        $this->form->addElement('select', 'q_16c_language_comp_body_parts_raw_score', '16c. Body parts', $options);
        $this->form->addElement('select', 'q_17_action_schemes_raw_score', '17. Inventory of actions schemes', $options);
        $this->form->addElement('select', 'q_18_actions_towards_other_raw_score', '18. Action schemes towards other', $options);
        $this->form->addElement('select', 'q_19_sequence_action_schemes_raw_score', '19. Sequences action schemes', $options);
        $this->form->addElement('select', 'q_20_stacks_tower_raw_score', '20. Stacks tower of blocks', $options);

    } 
      
    function _process($values) {
        $DB =& Database::singleton();

        $row = $DB->pselectRow("SELECT * from csbs_reliability WHERE CommentID=:CID AND reliability_center_id=:RCID", array('CID' => $this->identifier, 'RCID' => $this->reliability_center_id));

        $invalid = $values['invalid'];
        $DB->update("reliability", array('invalid' => $invalid), array("CommentID"=>$this->identifier, "Instrument" => 'ados_module1', "reliability_center_id" => $this->reliability_center_id));
        unset($values['invalid']);

        if($invalid == "yes"){
          $this->form->freeze();
          $this->tpl_data['success'] = true;
          return;
        }

        if(isset($values['Date_taken'])) {
            $values['Date_taken'] = $this->_getDatabaseDate($values['Date_taken']);
        }

        if(empty($row)) {
            // insert
            $values['CommentID'] = $this->identifier;
            $DB->insert("csbs_reliability", $values);
        } else {
            // update
            $DB->update("csbs_reliability", $values, array('CommentID'=>$this->identifier));
        }

        $scoreResult = $this->score();

        $this->form->freeze();
        $this->tpl_data['success'] = true;

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
        
    }
}
?>
