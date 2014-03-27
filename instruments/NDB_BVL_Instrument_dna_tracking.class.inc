<?php
class NDB_BVL_Instrument_dna_tracking extends NDB_BVL_Instrument
{
    /*
    INSERT INTO test_names (Test_name,Full_name, Sub_group) VALUES ('dna_tracking','DNA Tracking',1);

    INSERT INTO instrument_subtests (Test_name,Subtest_name,Description,Order_number) values ('dna_tracking','dna_tracking_page1','DailyActivityLog 1','1');
  */
    /**
    * sets up basic data, such as the HTML_Quickform object, and so on.
    *
    * @param string $commentID  the CommentID identifying the data to load
    * @param string $page       if a multipage form, the page to show
    * @return void
    * @access public
    */
    var $indent = "&nbsp;&nbsp;&nbsp;&nbsp;";
    var $yesNo = array(''=>NULL,'yes'=>'Yes','no'=>'No','not_answered'=>'Not Answered');
    var $collection_method_saliva = array(''=>NULL, 'project_staff'=>'Project Staff','kit_mail'=>'Kit sent by mail','other'=>'Other (if other specify)','not_answered'=>'Not Answered');
    var $num_blood_samples = array(''=>NULL,1=>1,2=>2,'more_than2'=>'More than 2','not_answered'=>'Not Answered');
    var $collection_method_blood = array(''=>NULL, 'project_staff'=>'Project Staff','local_nurse'=>'Local nurse','family_physician'=>'Family Physician','travelling_phlebotomist'=>'Travelling phlebotomist','other'=>'Other (if other specify)','not_answered'=>'Not Answered');
    var $location_sent = array(''=>NULL, 'unc'=>'UNC','repository'=>'Repository','other'=>'Other (if other specify)','not_answered'=>'Not Answered');
    function setup($commentID, $page){

        $this->formType="XIN";
        $this->form = new HTML_Quickform('test_form');
        $this->page = $page;            // page label (number or
        // string - used by
        // user-defined child classes)

        // set the object properties
        $this->testName = "dna_tracking";           // test_names.Test_name
        $this->table = 'dna_tracking';             // name of table containing

        // data keyed by commentID
        $this->commentID = $commentID;

        //The array of dates/timestamps to convert to database dates/timestamps
        //Any HTML_Quickform date elements must be listed here
        //rathi updatethis
        $this->dateTimeFields=array("Date_taken","day1_date_completed","day2_date_completed","day3_date_completed",
                                    "day4_date_completed","day1_infection_date","day2_infection_date",
                                    "day3_infection_date","day4_infection_date");

        $this->_requiredElements = array('Date_taken', 'Examiner','day1_child_sick'); 

        $config =& NDB_Config::singleton();
        $this->dateOptions = array(
        'language' => 'en',
        'format'   => 'YMd',
        'minYear'  => $config->getSetting('startYear'),
        'maxYear'  => $config->getSetting('endYear'),
        'addEmptyOption' => true,
        'emptyOptionValue' => null
        );
        
        $db =& Database::singleton();
        if(PEAR::isError($db)) {
            return PEAR::raiseError ("Could not connect to database: ".$db->getMessage());
        }
        // setup the form
        $this->_setupForm();

    }
    /**
     * method to build the HTML_Quickform object into a paged form
     *
     * @return void
     * @access private
     */
    function _setupForm(){
        if(preg_match("/dna_tracking(_page[0-9]+)/",$this->page,$matches)){
            $this->_page($matches[1]);
            //call_user_method($matches[1], $this);
        } else {
            $this->_main();
        }

        //Defines the call back function for HTML Quickform to use when validating the form.
        $this->form->addFormRule(array(&$this,'XINValidate'));
    }
   
    /**
     * generates the main page of the form.
     *
     * @return void
     * @access private
     *
     */
    function _main(){
        $this->addHeader("DNA Tracking");

        $group[] = &$this->form->createElement("static", null, null, "Candidate", array('class' => 'dna_heading'));
        $group[] = &$this->form->createElement("Static", null, null, "Proband",array('class' => 'dna_heading'));
        $group[] = &$this->form->createElement("static", null, null, "Mother", array('class' => 'dna_heading'));
        $group[] = &$this->form->createElement("static", null, null, "Father", array('class' => 'dna_heading'));
        $group[] = &$this->form->createElement("static", null, null, "Other", array('class' => 'dna_heading'));
       // $group[] = &$this->form->createElement("textarea","subject_other_specify", null);
                          //$group[] = $this->form->createElement("textarea", $field."_other".$subject,null);

        $this->form->addGroup($group, $field."_headers", null, $this->_GUIDelimiter, false);
        unset($group);
        // automatically adds examiner & date of administration
	$questions = array("saliva_collected"=>"Was saliva collected?","when_saliva_collected1"=>"1. When was saliva collected?",
                           "saliva_collection_method1"=>"1. How was saliva collected?", "when_saliva_collected2"=>"2. When was saliva collected?",
                           "saliva_collection_method2"=>"2. How was saliva collected?","blood_collected"=>"Was blood collected?",
			   "when_blood_collected1"=>"1. When was blood collected?","lab_purpletop_collected1"=>"1. Was the lab/purple top collected?",
                           "num_blood1"=>"1. How many?","yellowtop_collected1"=>"1. Was the yellow top collected?" , 
                           "blood_collection_method1"=>"1. How was blood collected?","blood_sent1"=>"1. Where was blood sent?", 
                           "when_blood_collected2"=>"2. When was blood collected?","lab_purpletop_collected2"=>"2. Was the lab/purple top collected?",
                           "num_blood2"=>"2. How many?","yellowtop_collected2"=>"2. Was the yellow top collected?", 
                           "blood_collection_method2"=>"2. How was blood collected?","blood_sent2"=>"2. Where was blood sent?");
        $subjects = array('candidate','proband','mother','father','other');
	foreach($questions as $key=>$val){
		$groupname = $key."_group";
		$field = $key;
     
	//	$group[] =& $this->form->createElement("static",null,null,$val);
                if($key == "saliva_collected" || $key == "blood_collected" || $key == "lab_purpletop_collected1" || $key == "lab_purpletop_collected2" 
                   || $key == "yellowtop_collected1" || $key == "yellowtop_collected2") {
                    foreach($subjects as $subject) {
                        $group[] = $this->form->createElement("select", $field."_".$subject,null,$this->yesNo, array('class' => 'oneselect'));
                    }
                }
                if(strpos($key, "saliva_collection_method") !== FALSE) {
                   foreach($subjects as $subject) {
                        $group[] = $this->form->createElement("select", $field."_".$subject,null,$this->collection_method_saliva, array('class' => 'oneselect'));
                    }

                }
                if(strpos($key, "when_saliva_collected") !== FALSE || strpos($key, "when_blood_collected") !== FALSE) {
                    foreach($subjects as $subject) {
                        $group[] = $this->form->createElement("date", $field."_".$subject,null,$this->dateOptions);
                    } 
                }
                if(strpos($key, "num_blood") !== FALSE) {
                   foreach($subjects as $subject) {
                        $group[] = $this->form->createElement("select", $field."_".$subject,null,$this->num_blood_samples, array('class' => 'oneselect'));
                    }
                } 
                if(strpos($key, "blood_collection_method") !== FALSE) {
                   foreach($subjects as $subject) {
                        $group[] = $this->form->createElement("select", $field."_".$subject,null,$this->collection_method_blood, array('class' => 'oneselect'));
                    }
                }
                if(strpos($key, "blood_sent") !== FALSE) {
                   foreach($subjects as $subject) {
                        $group[] = $this->form->createElement("select", $field."_".$subject,null,$this->location_sent, array('class' => 'oneselect'));
                    }
                }

 
		$this->form->addGroup($group, $groupname, $val, $this->_GUIDelimiter, false);
		unset($group);
               if(strpos($key, "saliva_collection_method") !== FALSE || strpos($key, "blood_collection_method") !== FALSE ) {
                   foreach($subjects as $subject) {
                        $group[] = $this->form->createElement("textarea", $field."_other".$subject,null);
                    }
                    $groupname = $key."_other_group";
                    $this->form->addGroup($group, $groupname, $this->indent."If other specify:", $this->_GUIDelimiter, false);
                    unset($group);
                    $this->XINRegisterRule($field."_other".$subject, array("$key.'_'.$subject{@}=={@}other"), "Please specify other", $groupname);

                }

	}

    }

}
?>
