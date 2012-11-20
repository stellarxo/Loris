<?php

require_once('NDB_BVL_Instrument_head_measurements.class.inc');

class NDB_BVL_Instrument_head_measurements_subject extends NDB_BVL_Instrument_head_measurements
{
/*
INSERT INTO test_names VALUES ('', 'head_measurements_subject', 'Head Measurements (Subject)', '0', '1');
INSERT INTO test_battery VALUES ('', 'head_measurements_subject', '1050', '1140', 'Y', 'Visit', '3');
*/
    /**
    * sets up basic data, such as the HTML_Quickform object, and so on.
    *
    * @param string $commentID  the CommentID identifying the data to load
    * @param string $page       if a multipage form, the page to show
    * @return void
    * @access public
    */
    function setup($commentID, $page){
        // set the object properties
        $this->testName = "head_measurements_subject";           // test_names.Test_name
        $this->table = 'head_measurements_subject';              // name of database table corresponding to instrument
        
        $this->_setup($commentID, $page);
    }   

    /**
    * generates the main page of the form.
    *
    * @return void
    * @access private
    *
    */
    function _main(){
        // display test name
        $this->form->addElement('header', 'instrument_title', "Measurements Data Sheet");
    
        // automatically adds examiner & date of administration
        $this->_addMetadataFields();
    
        $this->form->addElement('header', null, 'Head Measurements');
        $types = array('Child', 'Mother', 'Father');
        foreach($types as $type) {
            if($type === 'Child') {
                $suffix = '';
            } else {
                $suffix= '_' . strtolower($type);
            }
            $this->form->addElement('static', null, "<br><b>" . $type .'</b>:');
            $this->form->addElement('select', "head_circumference_unit$suffix", 'Unit for head circumference', array('c    m' => 'centimeters', "inches" => "inches", "not_answered" => "Not Answered"));
            $this->addTextElement("head_circumference1$suffix", "Circumference 1:");
            if($type === 'Child') {
                $this->addTextElement("head_circumference2$suffix", "Circumference 2:");
            }
        
            $this->form->addElement('header', null, 'Length');
            $this->form->addElement('select', "head_length_unit$suffix", 'Unit for length', array('cm' => 'centimeters'    , "inches" => "inches", "not_answered" => "Not Answered"));
            $this->addTextElement("length1$suffix", "Length 1:");
            if($type === 'Child') {
                $this->addTextElement("length2$suffix", "Length 2:");
            }
            if($type === 'Child') {
                $this->form->addElement("select", 'measurement_method', $this->indent . "Child was measured:", array    (""=>NULL, "lying_down"=>"Lying down", "standing_up"=>"Standing up", "not_answered"=>"Not Answered"));
            }
       
            $this->form->addElement('header', null, 'Weight');
            $this->form->addElement('select', "weight_unit$suffix", 'Unit for weight', array('kg' => 'kilograms', "lbs"     => "pounds", "not_answered" => "Not Answered"));
            $this->addTextElement("weight1$suffix", "Weight 1:");
            if($type === 'Child') {
                $this->addTextElement("weight2$suffix", "Weight 2:");
            }
        }
        $this->addTextAreaElement('comments', 'General Comments:');
  
    }

}
?>
