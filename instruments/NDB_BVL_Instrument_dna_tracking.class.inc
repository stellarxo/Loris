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
    var $num_blood_samples = array(''=>NULL,1=>1,2=>2,3=>3,'more_than3'=>'More than 3','not_answered'=>'Not Answered');
    var $collection_method_blood = array(''=>NULL, 'project_staff'=>'Project Staff','local_nurse'=>'Local nurse','family_physician'=>'Family Physician','travelling_phlebotomist'=>'Travelling phlebotomist','other'=>'Other (if other specify)','not_answered'=>'Not Answered');
    var $location_sent = array(''=>NULL, 'unc'=>'UNC','repository'=>'Repository','other'=>'Other (if other specify)','not_answered'=>'Not Answered');
    var $saliva_no_collection = array(''=>NULL, 'never_scheduled'=>'Never scheduled','child_too_old'=>'Child was too old','family_declined'=>'Family Declined','family_not_responsive'=>'Family not responsive','other'=>'Other','not_answered'=>'Not Answered');
    var $blood_no_collection = array(''=>NULL, 'never_scheduled'=>'Never scheduled','child_too_old'=>'Child was too old','family_declined'=>'Family Declined','family_not_responsive'=>'Family not responsive','parent_did_not_want_child_blood_drawn'=>"Parent did not want child's blood drawn" ,'other'=>'Other','not_answered'=>'Not Answered');

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

        $group[] = &$this->form->createElement("static", null, null, "<strong>Candidate</strong>");
        $group[] = &$this->form->createElement("Static", null, null, "<strong>Proband</strong>");
        $group[] = &$this->form->createElement("static", null, null, "<strong>Mother</strong>");
        $group[] = &$this->form->createElement("static", null, null, "<strong>Father</strong>");
        $group[] = &$this->form->createElement("textarea","subject_other_specify", null, array('placeholder'=>'Specify other'));
        //$group[] = &$this->form->createElement("static", null, null, "Other", array('class' => 'dna_heading'));
       // $group[] = &$this->form->createElement("textarea","subject_other_specify", null);
                          //$group[] = $this->form->createElement("textarea", $key."_other".$subject,null);

        $this->form->addGroup($group, "headers", null, $this->_GUIDelimiter, false);
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
     
	//	$group[] =& $this->form->createElement("static",null,null,$val);
                if($key == "saliva_collected" || $key == "blood_collected" || $key == "lab_purpletop_collected1" || $key == "lab_purpletop_collected2" 
                   || $key == "yellowtop_collected1" || $key == "yellowtop_collected2") {
                    foreach($subjects as $subject) {
                        $group[] = $this->form->createElement("select", $key."_".$subject,null,$this->yesNo, array('class' => 'oneselect'));
                    }
                }
                if(strpos($key, "saliva_collection_method") !== FALSE) {
                   foreach($subjects as $subject) {
                        $group[] = $this->form->createElement("select", $key."_".$subject,null,$this->collection_method_saliva, array('class' => 'oneselect'));
                    }

                }
                if(strpos($key, "when_saliva_collected") !== FALSE || strpos($key, "when_blood_collected") !== FALSE) {
                    foreach($subjects as $subject) {
                        $group[] = $this->form->createElement("date", $key."_".$subject,null,$this->dateOptions);
                    } 
                }
                if(strpos($key, "num_blood") !== FALSE) {
                   foreach($subjects as $subject) {
                        $group[] = $this->form->createElement("select", $key."_".$subject,null,$this->num_blood_samples, array('class' => 'oneselect'));
                    }
                } 
                if(strpos($key, "blood_collection_method") !== FALSE) {
                   foreach($subjects as $subject) {
                        $group[] = $this->form->createElement("select", $key."_".$subject,null,$this->collection_method_blood, array('class' => 'oneselect'));
                    }
                }
                if(strpos($key, "blood_sent") !== FALSE) {
                   foreach($subjects as $subject) {
                        $group[] = $this->form->createElement("select", $key."_".$subject,null,$this->location_sent, array('class' => 'oneselect'));
                    }
                }

                if($key == 'blood_collected' || $key == 'saliva_collected' ) {
                    $this->form->addGroup($group, $groupname,"<strong>". $val."</strong>", $this->_GUIDelimiter, false);
                } else { 
		    $this->form->addGroup($group, $groupname, $val, $this->_GUIDelimiter, false);
                }
		unset($group);
               if(strpos($key, "saliva_collection_method") !== FALSE || strpos($key, "blood_collection_method") !== FALSE ) {
                   foreach($subjects as $subject) {
                        $group[] = $this->form->createElement("textarea", $key."_other".$subject,null);
                    }
                    $groupname = $key."_other_group";
                    $this->form->addGroup($group, $groupname, $this->indent."If other specify:", $this->_GUIDelimiter, false);
                    unset($group);
                    $this->XINRegisterRule($key."_other".$subject, array("$key.'_'.$subject{@}=={@}other"), "Please specify other", $groupname);

                }
                if($key == "saliva_collected") {
                    $groupname = $key."_".$subject."_saliva_notcollected_group";
                    foreach($subjects as $subject) {
                        $field = $key."_".$subject;
                        $group[] = $this->form->createElement("select", $field."_saliva_notcollected",null,$this->saliva_no_collection, array('class' => 'oneselect'));
                        //adding rules for each of the subjects 
                        $this->XINRegisterRule($field."_saliva_notcollected", array("$field{@}=={@}no"),'If saliva was not collected, please specify reason', $groupname);
                    }
                    $this->form->addGroup($group, $groupname, $this->indent."If no, specify reason:", $this->_GUIDelimiter, false);
                    unset($group);
                    
                    $groupname = $key."_saliva_notcollected_other_group";
                    foreach ($subjects as $subject) {
                        $field = $key."_".$subject;
		        $group[] = $this->form->createElement("textarea", $field."_saliva_notcollected_other",null);
                        $this->XINRegisterRule($field."_saliva_notcollected_other", array($field."_saliva_notcollected{@}=={@}other"),'Please specify other', $groupname);
                    }
                    $this->form->addGroup($group, $groupname, $this->indent.$this->indent."If other, specify:", $this->_GUIDelimiter, false);
                    unset($group);

                }
                if($key == "blood_collected") {
                    $groupname = $key."_".$subject."_blood_notcollected_group";
                    foreach($subjects as $subject) {
                        $field = $key."_".$subject;
                        $group[] = $this->form->createElement("select", $field."_blood_notcollected",null,$this->blood_no_collection, array('class' => 'oneselect'));
                        $this->XINRegisterRule($field."_blood_notcollected", array("$field{@}=={@}no"),'If blood was not collected, please specify reason', $groupname);                        
                    }
                    $this->form->addGroup($group, $groupname, $this->indent."If no specify reason:", $this->_GUIDelimiter, false);
                    unset($group);
                    
                 
                    $groupname = $key."_blood_notcollected_other_group";
                    foreach ($subjects as $subject) {
                        $field = $key."_".$subject;
                        $group[] = $this->form->createElement("textarea", $field."_blood_notcollected_other",null);
                        $this->XINRegisterRule($field."_blood_notcollected_other", array($field."_blood_notcollected{@}=={@}other"),'If blood was not collected, please specify reason', $groupname);                              
                    }
                    $this->form->addGroup($group, $groupname, $this->indent.$this->indent."If other, specify:", $this->_GUIDelimiter, false);
                    unset($group);
                   
                }

	}

    }

}
?>
