<?php

require_once 'HTML/QuickForm.php';
require_once 'HTML/QuickForm/Renderer/Array.php';

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
    var $collection_method_saliva = array(''=>NULL, 'project_staff'=>'Project Staff','kit_mail'=>'Kit sent by mail','travelling_phlebotomist'=>'Travelling phlebotomist', 'other'=>'Other (if other specify)','not_answered'=>'Not Answered');
    var $num_blood_samples = array(''=>NULL,1=>1,2=>2,3=>3,'more_than3'=>'More than 3','not_answered'=>'Not Answered');
    var $collection_method_blood = array(''=>NULL, 'project_staff'=>'Project Staff','local_nurse'=>'Local nurse','family_physician'=>'Family Physician','travelling_phlebotomist'=>'Travelling phlebotomist','other'=>'Other (if other specify)','not_answered'=>'Not Answered');
    var $location_sent = array(''=>NULL, 'unc'=>'UNC','repository'=>'Repository','other'=>'Other (if other specify)','not_answered'=>'Not Answered');
    var $saliva_no_collection = array(''=>NULL, 'never_scheduled'=>'Never scheduled','child_too_old'=>'Child was too old','family_declined'=>'Family Declined','family_not_responsive'=>'Family not responsive','individual_declined'=>'Individual declined','individual_not_responsive'=>'Individual not responsive','collected_blood_sample'=>'Got blood sample','other'=>'Other','not_answered'=>'Not Answered');
    var $blood_no_collection = array(''=>NULL, 'never_scheduled'=>'Never scheduled','child_too_old'=>'Child was too old','family_declined'=>'Family Declined','family_not_responsive'=>'Family not responsive','parent_did_not_want_child_blood_drawn'=>"Parent did not want child's blood drawn" ,'draw_attempted_unable_to_obtain'=>'Draw attempted, but unable to obtain' ,'individual_declined'=>'Individual declined','individual_not_responsive'=>'Individual not responsive','other'=>'Other','not_answered'=>'Not Answered');

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
        $this->XINRegisterRule("subject_other_specify", array("subject_other_specify{@}=={@}NEVER_REQUIRED"));
        $this->form->addGroup($group, "headers", null, $this->_GUIDelimiter, false);
        unset($group);
        // automatically adds examiner & date of administration
	$questions = array("saliva_collected"=>"Was saliva collected?","when_saliva_collected1"=>"1. When was saliva collected?",
                           "saliva_collection_method1"=>"1. How was saliva collected?", "when_saliva_collected2"=>"2. When was saliva collected?",
                           "saliva_collection_method2"=>"2. How was saliva collected?","blood_collected"=>"Was blood collected?",
			   "when_blood_collected1"=>"1. When was blood collected?","lab_purpletop_collected1"=>"1. Was the lab/purple top collected?",
                           "num_blood1"=>"1. How many lab/purple top samples collected?","yellowtop_collected1"=>"1. Was the yellow top collected?" ,
                           "num_yellowtop_collected1"=>"1. How many yellow top samples collected?", 
                           "blood_collection_method1"=>"1. How was blood collected?","blood_sent1"=>"1. Where was blood sent?", 
                           "when_blood_collected2"=>"2. When was blood collected?","lab_purpletop_collected2"=>"2. Was the lab/purple top collected?",
                           "num_blood2"=>"2. How many lab/purple top samples collected?","yellowtop_collected2"=>"2. Was the yellow top collected?",
                           "num_yellowtop_collected2"=>"2. How many yellow top samples collected?",
                           "blood_collection_method2"=>"2. How was blood collected?","blood_sent2"=>"2. Where was blood sent?");
        $subjects = array('candidate','proband','mother','father','other');
        $types = array('saliva','blood');
                        $this->form->registerRule('checkdate', 'callback', '_checkDate');
        $this->form->addFormRule(array(&$this, 'dna_rules'));
	foreach($questions as $key=>$val){
		$groupname = $key."_group";
     
                if($key == "saliva_collected" || $key == "blood_collected" || $key == "lab_purpletop_collected1" || $key == "lab_purpletop_collected2" 
                   || $key == "yellowtop_collected1" || $key == "yellowtop_collected2") {
                    foreach($subjects as $subject) {
                        $group[] = $this->form->createElement("select", $key."_".$subject,null,$this->yesNo, array('class' => 'oneselect'));
                        $field   = $key."_".$subject;
                        $this->XINRegisterRule( $field, array("$field{@}=={@}NEVER_REQUIRED"));
                     /*   if(strpos($key, "1") !== FALSE && $key == "blood_collected") {
                                  // If blood was collected then require yellow/purple top collected question
                                  $this->XINRegisterRule( $key."_".$subject, array("$field{@}=={@}yes"), "Please specify", $groupname);
                       }
                       if(strpos($key, "2")) {
                              foreach($types as $type) {
                                  // If blood or saliva was collected then enter date
                                  $field = $key."_".$subject;
                                  $this->XINRegisterRule( $field, array("$field{@}=={@}NEVER_REQUIRED"));
                              }
                       }
                     */
                    }// end of foreach
                }
                if(strpos($key, "saliva_collection_method") !== FALSE) {
                   foreach($subjects as $subject) {
                        $group[] = $this->form->createElement("select", $key."_".$subject,null,$this->collection_method_saliva, array('class' => 'oneselect'));
                         $field = $key."_".$subject;
                         $this->XINRegisterRule( $field, array("$field{@}=={@}NEVER_REQUIRED"));

                      /*   if(strpos($key, "1")) {
                              foreach($types as $type) {
                                  $field = $type."_collected_".$subject;
                                  // If blood or saliva was collected then enter collection method
                                  $this->XINRegisterRule( $key."_".$subject, array("$field{@}=={@}yes"), "Please specify collection method", $groupname);
                              }
                       }
                       if(strpos($key, "2")) {
                              foreach($types as $type) {
                                  // If blood or saliva was collected then enter date
                                  $field = $key."_".$subject;
                                  $this->XINRegisterRule( $field, array("$field{@}=={@}NEVER_REQUIRED"));
                              }
                       }
                       */

                    } 

                }
                if(strpos($key, "when_saliva_collected") !== FALSE || strpos($key, "when_blood_collected") !== FALSE) {
                    foreach($subjects as $subject) {
                        $this->dateTimeFields[] = $key."_".$subject;
                        $group[] = $this->form->createElement("date", $key."_".$subject,null,$this->dateOptions);
                        $field = $key."_".$subject;
                        $this->XINRegisterRule( $field, array("$field{@}=={@}NEVER_REQUIRED"));
                        $this->form->addRule($field, 'Date is invalid', 'checkdate');

                       /*
                        if(strpos($key, "1")) {
                              foreach($types as $type) {
                                  $field = $type."_collected_".$subject;
                                  // If blood or saliva was collected then enter date
                       //           $this->XINRegisterRule( $key."_".$subject, array("$field{@}=={@}yes"), "Please specify date", $groupname);
                              } 
                       }
                       if(strpos($key, "2")) {
                              foreach($types as $type) {
                                 // $field = $type."_collected_".$subject;
                                  // If blood or saliva was collected then enter date
                                  $field = $key."_".$subject;
                                  $this->XINRegisterRule( $field, array("$field{@}=={@}NEVER_REQUIRED"));
                              }
                       }
                      */
                    } 
                }
                if(strpos($key, "num_blood") !== FALSE || strpos($key, "num_yellowtop_collected") !== FALSE) {
                   foreach($subjects as $subject) {
                        $group[] = $this->form->createElement("select", $key."_".$subject,null,$this->num_blood_samples, array('class' => 'oneselect'));
                        $field = $key."_".$subject;
                        $this->XINRegisterRule( $field, array("$field{@}=={@}NEVER_REQUIRED"));

 /*                       if(strpos($key, "1")) {
                                  $field = "blood_collected_".$subject; 
                                  // If blood was collected then require number of tubes
                                  $this->XINRegisterRule( $key."_".$subject, array("$field{@}=={@}yes"), "Please specify", $groupname);
                       }
                       if(strpos($key, "2")) {
                              foreach($types as $type) {
                                
                                  $field = $key."_".$subject;
                                  $this->XINRegisterRule( $field, array("$field{@}=={@}NEVER_REQUIRED"));
                              }
                       }
*/
                    } // end for each
                } 
                if(strpos($key, "blood_collection_method") !== FALSE) {
                   foreach($subjects as $subject) {
                        $group[] = $this->form->createElement("select", $key."_".$subject,null,$this->collection_method_blood, array('class' => 'oneselect'));
                         $field = $key."_".$subject;
                         $this->XINRegisterRule( $field, array("$field{@}=={@}NEVER_REQUIRED"));

                       /*     if(strpos($key, "1")) {
                                  $field = "blood_collected_".$subject; 
                                  // If blood was collected then require number of tubes
                                  $this->XINRegisterRule( $key."_".$subject, array("$field{@}=={@}yes"), "Please specify", $groupname);
                       }
                       if(strpos($key, "2")) {
                              foreach($types as $type) {
                                  $field = $key."_".$subject;
                                  $this->XINRegisterRule( $field, array("$field{@}=={@}NEVER_REQUIRED"));
                              }
                       }
                     */
                    } // end of foreach
                }
                if(strpos($key, "blood_sent") !== FALSE) {
                   foreach($subjects as $subject) {
                        $group[] = $this->form->createElement("select", $key."_".$subject,null,$this->location_sent, array('class' => 'oneselect'));
                        $field = $key."_".$subject;
                        $this->XINRegisterRule( $field, array("$field{@}=={@}NEVER_REQUIRED"));

                      /*  if(strpos($key, "1")) {
                                  $field = "blood_collected_".$subject;
                                  // If blood was collected then require number of tubes
                                  $this->XINRegisterRule( $key."_".$subject, array("$field{@}=={@}yes"), "Please specify", $groupname);
                       }
                       if(strpos($key, "2")) {
                              foreach($types as $type) {

                                  $field = $key."_".$subject;
                                  $this->XINRegisterRule( $field, array("$field{@}=={@}NEVER_REQUIRED"));
                              }
                       }
                      */
                    } //end foreach
                }

                if($key == 'blood_collected' || $key == 'saliva_collected' ) {
                    $this->form->addGroup($group, $groupname,"<strong>". $val."</strong>", $this->_GUIDelimiter, false);
                } else { 
		    $this->form->addGroup($group, $groupname, $val, $this->_GUIDelimiter, false);
                }
		unset($group);
               if(strpos($key, "saliva_collection_method") !== FALSE || strpos($key, "blood_collection_method") !== FALSE ) {
                   $groupname = $key."_other_group";
                   foreach($subjects as $subject) {
                        $field = $key."_".$subject; 
                        $group[] = $this->form->createElement("textarea", $field."_other",null); 
                        $this->XINRegisterRule($field."_other", array("$field{@}=={@}NEVER_REQUIRED"));
                    }
                    $this->form->addGroup($group, $groupname, $this->indent."If other specify:", $this->_GUIDelimiter, false);
                    unset($group);
		    if(strpos($key, "saliva_collection_method") !== FALSE ) {
			    $groupname = "blankline_group";
			    foreach ($subjects as $subject) {
				    $group[] = $this->form->createElement("static", null,null,null, array('class'=>'blankline'));
			    }
			    $this->form->addGroup($group, $groupname,null, $this->_GUIDelimiter, false);
			    unset($group);
		    }
                }
                if($key == "saliva_collected") {
                    $groupname = "saliva_notcollected_group";
                    foreach($subjects as $subject) {
                        $group[] = $this->form->createElement("select", "saliva_notcollected_".$subject,null,$this->saliva_no_collection, array('class' => 'oneselect'));
                        //adding rules for each of the subjects 
                       // $this->XINRegisterRule("saliva_notcollected_".$subject, array("$field{@}=={@}no"),'If saliva was not collected, please specify reason', $groupname);
                        $field = "saliva_notcollected_".$subject;
                        $this->XINRegisterRule("saliva_notcollected_".$subject, array("$field{@}=={@}NEVER_REQUIRED"));
                    }
                    $this->form->addGroup($group, $groupname, $this->indent."If no, specify reason:", $this->_GUIDelimiter, false);
                    unset($group);
                    
                    $groupname = "saliva_notcollected_other_group";
                    foreach ($subjects as $subject) {
                        $field = "saliva_notcollected_".$subject;
		        $group[] = $this->form->createElement("textarea", $field."_other",null);
                        $this->XINRegisterRule($field."_other", array($field."_other{@}=={@}NEVER_REQUIRED"));
                    }
                    $this->form->addGroup($group, $groupname, $this->indent.$this->indent."If other, specify:", $this->_GUIDelimiter, false);
                    unset($group);
                  
                }
                if($key == "blood_collected") {
                    $groupname = "blood_notcollected_group";
                    foreach($subjects as $subject) {
                        $field = $key."_".$subject;
                        $group[] = $this->form->createElement("select", "blood_notcollected_".$subject,null,$this->blood_no_collection, array('class' => 'oneselect'));
                        $this->XINRegisterRule("blood_notcollected_".$subject, array("$field{@}=={@}no"),'If blood was not collected, please specify reason', $groupname);                        
                    }
                    $this->form->addGroup($group, $groupname, $this->indent."If no specify reason:", $this->_GUIDelimiter, false);
                    unset($group);
                    
                 
                    $groupname = "blood_notcollected_other_group";
                    foreach ($subjects as $subject) {
                        $field = "blood_notcollected_".$subject;
                        $group[] = $this->form->createElement("textarea", $field."_other",null);
                        $this->XINRegisterRule( $field."_other", array($field."_other{@}=={@}NEVER_REQUIRED"));                              
                    }
                    $this->form->addGroup($group, $groupname, $this->indent.$this->indent."If other, specify:", $this->_GUIDelimiter, false);
                    unset($group);
                   
                }
		if(strpos($key, "blood_sent") !== FALSE) {
                      $groupname = $key."_other_group"; 
		      foreach($subjects as $subject) { 
                           $field = $key."_".$subject."_other";
                           $group[] = $this->form->createElement("textarea",$field, null);
                           $this->XINRegisterRule($field,  array("$field{@}=={@}NEVER_REQUIRED"));
	        	}
                        $this->form->addGroup($group, $groupname, $this->indent.$this->indent."If other, specify:", $this->_GUIDelimiter, false);
                        unset($group);

			$groupname = "blankline_group";
			foreach ($subjects as $subject) {
				$group[] = $this->form->createElement("static", null,null,null, array('class'=>'blankline'));
			}
			$this->form->addGroup($group, $groupname,null, $this->_GUIDelimiter, false);
			unset($group);

                }
	}

    }

    function dna_rules ($values) { 
        $errors = array();
        $subjects = array('candidate','proband','mother','father','other');
        foreach($subjects as $subject) {
              $field = "blood_collected_".$subject; 
              
              if( ($values[$field] == 'yes') && empty($values["yellowtop_collected1_".$subject])) {
                  $errors['yellowtop_collected1_group'] = "Specify if yellowtop was collected for $subject";
              } 
              if($values[$field] == 'yes' && empty($values["lab_purpletop_collected1_".$subject])) { 
                  $errors['lab_purpletop_collected1_group'] = "Specify if lab/purple top was collected for $subject";
             } 
             $blood_when = array(); $blood_when = $values["when_blood_collected1_".$subject];
             if($values[$field] == 'yes' && _checkDate($blood_when) == false) { 
                  $errors['when_blood_collected1_group'] = "Specify date for $subject";
             } 
             if($values[$field] == 'yes' && empty($values["num_blood1_".$subject])) {
                  $errors['num_blood1_group'] = "Specify number of purple tubes for $subject";
             }
             if($values[$field] == 'yes' && empty($values["num_yellowtop_collected1_".$subject])) {
                  $errors['num_yellowtop_collected1_group'] = "Specify number of yellow tubes for $subject";
             }
             if($values[$field] == 'yes' && empty($values["blood_collection_method1_".$subject])) {
                  $errors['blood_collection_method1_group'] = "Specify how blood was collected for $subject";
             }
             if($values[$field] == 'yes' && empty($values["blood_sent1_".$subject])) {
                  $errors['blood_sent1_group'] = "Specify where blood was sent for $subject";
             }
             if($values[$field] == 'yes' && $values["blood_collection_method1_".$subject] == 'other'
                && empty($values["blood_collection_method1_".$subject."_other" ] )) {
                  $errors["blood_collection_method1_other_group" ] = "Specify other for $subject";
             }
             if($values["blood_collection_method2_".$subject] == 'other'
                && empty($values["blood_collection_method2_".$subject."_other" ] )) {
                  $errors["blood_collection_method2_other_group" ] = "Specify other for $subject";
             }

             if($values[$field] == 'no' && empty($values["blood_notcollected_".$subject]) ) {
                  $errors["blood_notcollected_group"] = "Specify reason for $subject";
             }
             if($values[$field] == 'no' && $values["blood_notcollected_".$subject] == "other" 
                 && empty($values["blood_notcollected_".$subject."_other"]) ) {
                 $errors["blood_notcollected_other_group"] = "Specify other for $subject";
             }
             $saliva_field = "saliva_collected_".$subject;
             if($values[$saliva_field] == 'yes' && empty ($values["saliva_collection_method1_".$subject]) )  {
                 $errors["saliva_collection_method1_group"] = "Specify how saliva was collected for $subject";
              }
	     for($i =1; $i<=2;$i++){
		     if($values["saliva_collection_method".$i."_".$subject] == 'other' 
                        && empty($values["saliva_collection_method".$i."_".$subject."_other"] ) ) {
			     $errors["saliva_collection_method".$i."_other_group"] = "Specify other for $subject";
		     }
	     }
             $saliva_when = array(); $saliva_when = $values["when_saliva_collected1_".$subject];
             if($values[$saliva_field] == 'yes' && empty($saliva_when['Y'])) {
                  $errors['when_saliva_collected1_group'] = "Specify date for $subject";
             }
             if($values[$saliva_field] == 'yes' && (empty($saliva_when['Y']) || empty($saliva_when['M']) || empty($saliva_when['d'])) ) {
                  $errors['when_saliva_collected1_group'] = "Specify date for $subject";
             }
             if($values[$saliva_field] == 'no' && empty($values["saliva_notcollected_".$subject] ) ) {
                 $errors["saliva_notcollected_group"] = "Specify reason for $subject";
             }
             if($values[$saliva_field] == 'no' && $values["saliva_notcollected_".$subject] == "other"
                 && empty($values["saliva_notcollected_".$subject."_other"]) ) {
                 $errors["saliva_notcollected_other_group"] = "Specify other for $subject";
             }
             $saliva_when2 = $values["when_saliva_collected2_".$subject]; 
             if(!empty($saliva_when2['Y']) && empty($values["saliva_collection_method2_".$subject] ) ) { 
                $errors["saliva_collection_method2_group"] = "Specify how saliva was collected for $subject";
             }
             if(_checkDate($saliva_when2) == false) {
                  $errors['when_saliva_collected2_group'] = "Invalid date for $subject";

             }
             if(_checkDate($saliva_when) == false) {
                  $errors['when_saliva_collected1_group'] = "Invalid date for $subject";

             }
/*
             if( (_checkDate($saliva_when) == true)   && (_checkDate($saliva_when2) == true ) 
               &&  ($values["when_saliva_collected1_".$subject] > $values["when_saliva_collected2_".$subject])) {
                  $errors['when_saliva_collected2_group'] = "Date sample collected should be after first sample was collected for $subject";

            }
*/
            $blood_when2 = array(); $blood_when2 = $values["when_blood_collected2_".$subject];
             if(_checkDate($blood_when2) == false) {
                  $errors['when_blood_collected2_group'] = "Invalid date for $subject";

             }
             if(_checkDate($blood_when1) == false) {
                  $errors['when_blood_collected1_group'] = "Invalid date for $subject";

             }

  /*           if
        /*    if(!empty($blood_when2['Y']) && !empty($blood_when['Y'] ) ) { 
                if ($values["when_blood_collected1_".$subject] < $values["when_blood_collected2_".$subject]) {
                  $errors['when_blood_collected2_group'] = "Date sample collected should be after first sample was collected for $subject";
                }
            }
*/
            
            if( !empty($blood_when2['Y']) && empty($values["yellowtop_collected2_".$subject])) {
                  $errors['yellowtop_collected2_group'] = "Specify if yellowtop was collected for $subject";
             }
            if( !empty($blood_when2['Y']) && empty($values["lab_purpletop_collected2_".$subject])) {
                  $errors['lab_purpletop_collected2_group'] = "Specify if lab/purple top was collected for $subject";
            }
           
             if(!empty($blood_when2['Y'])  && empty($values["num_blood2_".$subject])) {
                  $errors['num_blood2_group'] = "Specify number of tubes for $subject";
             }
            if(!empty($blood_when2['Y'])  && empty($values["num_yellowtop_collected2_".$subject])) {
                  $errors['num_yellowtop_collected2_group'] = "Specify number of yellow tubes for $subject";
             }

             if( !empty($blood_when2['Y'])  && empty($values["blood_collection_method2_".$subject])) {
                  $errors['blood_collection_method2_group'] = "Specify how blood was collected for $subject";
             }
             if(!empty($blood_when2['Y']) && empty($values["blood_sent2_".$subject])) {
                  $errors['blood_sent2_group'] = "Specify where blood was sent for $subject";
             }
             if(!empty($blood_when2['Y']) && $values["blood_sent2_".$subject] == "other" 
                 && empty($values["blood_sent2_".$subject."_other"] ) ) 
             { 
                $errors["blood_sent2_other_group"] = "Specify other for $subject";
             }

    }
        return $errors;
   }
}
?>
