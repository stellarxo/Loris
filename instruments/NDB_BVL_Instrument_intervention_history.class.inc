<?php
		    
require_once 'HTML/QuickForm.php';
require_once 'HTML/QuickForm/Renderer/Array.php';

class NDB_BVL_Instrument_intervention_history extends NDB_BVL_Instrument
{
/**
INSERT INTO test_names VALUES ('', 'intervention_history', 'Intervention History', '0', '1', NULL);
INSERT INTO instrument_subtests VALUES('', 'intervention_history', 'intervention_history_page1', 'Intervention 1', 1);
INSERT INTO instrument_subtests VALUES('', 'intervention_history', 'intervention_history_page2', 'Intervention 2', 2);
INSERT INTO instrument_subtests VALUES('', 'intervention_history', 'intervention_history_page3', 'Intervention 3', 3);
INSERT INTO instrument_subtests VALUES('', 'intervention_history', 'intervention_history_page4', 'Intervention 4', 4);
INSERT INTO instrument_subtests VALUES('', 'intervention_history', 'intervention_history_page5', 'Intervention 5', 5);
INSERT INTO instrument_subtests VALUES('', 'intervention_history', 'intervention_history_page6', 'Intervention 6', 6);
INSERT INTO instrument_subtests VALUES('', 'intervention_history', 'intervention_history_page7', 'Intervention 7', 7);
INSERT INTO instrument_subtests VALUES('', 'intervention_history', 'intervention_history_page8', 'Intervention 8', 8);
INSERT INTO instrument_subtests VALUES('', 'intervention_history', 'intervention_history_page9', 'Intervention 9', 9);
INSERT INTO instrument_subtests VALUES('', 'intervention_history', 'intervention_history_page10', 'Intervention 10', 10);
INSERT INTO test_battery VALUES ('', 'intervention_history', '660', '780', 'Y', 'Visit', '1', NULL);
INSERT INTO test_battery VALUES ('', 'intervention_history', '1053', '1179', 'Y', 'Visit', '1', NULL);
INSERT INTO test_battery VALUES ('', 'intervention_history', '660', '780', 'Y', 'Visit', '2', NULL);
INSERT INTO test_battery VALUES ('', 'intervention_history', '660', '780', 'Y', 'Visit', '2', NULL);
INSERT INTO test_battery VALUES ('', 'intervention_history', '1053', '1179', 'Y', 'Visit', '3', NULL);
INSERT INTO test_battery VALUES ('', 'intervention_history', '1053', '1179', 'Y', 'Visit', '3', NULL);
**/

    var $dateOptions = array(
                'language' => 'en',
                'format'   => 'YMd',
                'minYear'  =>  '2007',
                'maxYear'  => '2017',
                'addEmptyOption' => true,
                'emptyOptionValue' => null);

    var $scoreLabels = array("q1_intensity_1"=>"", 
			"q1_intensity_2"=>"",
			"q1_intensity_3"=>"",
			"q1_intensity_4"=>"",
			"q1_intensity_5"=>"",
			"q1_intensity_6"=>"",
			"q1_intensity_7"=>"",
			"q1_intensity_8"=>"",
			"q1_intensity_9"=>"",
			"q1_intensity_10"=>"",
                        );



    /**
    * sets up basic data, such as the HTML_Quickform object, and so on.
    *
    * @param string $commentID  the CommentID identifying the data to load
    * @param string $page       if a multipage form, the page to show
    * @return void
    * @access public
    */
    function setup($commentID, $page){
        $this->formType="XIN";
        $this->form = new HTML_Quickform('test_form');
        $this->page = $page;            // page label (number or
        // string - used by
        // user-defined child classes)
        
        // set the object properties
        $this->testName = "intervention_history";           // test_names.Test_name
        $this->table = 'intervention_history';              // name of database table corresponding to instrument
        // data keyed by commentID
        $this->commentID = $commentID;
        
        //The array of dates/timestamps to convert to database dates/timestamps
        //Any HTML_Quickform date elements must be listed here
        $this->dateTimeFields=array("Date_taken" , "q4_date_began_1", "q4_date_began_2", "q4_date_began_3", "q4_date_began_4", "q4_date_began_5", "q4_date_began_6", "q4_date_began_7", "q4_date_began_8", "q4_date_began_9", "q4_date_began_10", "q5_date_ended_1", "q5_date_ended_2", "q5_date_ended_3", "q5_date_ended_4", "q5_date_ended_5", "q5_date_ended_6", "q5_date_ended_7", "q5_date_ended_8", "q5_date_ended_9", "q5_date_ended_10");
            
        //The array of selects with multiple answers allowed
        //Any HTML_Quickform multiple selects must be listed here
        $this->_selectMultipleElements = array();

        // required fields for data entry completion status
        $this->_requiredElements = array("Examiner", "q1_type_of_intervention_1");



	/**
	 * Array of column names to be ignored by the double data entry conflict detector.
	 */
     // Commented out so that the ones from NDB_BVL_Instrument are picked up. This doesn't seem to be any different
	//$this->_doubleDataEntryDiffIgnoreColumns = array('CommentID', 'UserID', 'Testdate');

        // setup the form
        $this->_setupForm();

    }
    
    //If the instrument is not paged, remove the switch from the _setupForm method and add all the form Elements in this function.
    
    /**
    * method to build the HTML_Quickform object into a paged form
    *
    * @return void
    * @access private
    */
    function _setupForm(){

    	if(preg_match("/intervention_history(_page[0-9]+)/", $this->page, $matches))
        {
 	       call_user_method($matches[1], $this);
        }
	else
	{
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
        // display test name
        $this->form->addElement('header', 'instrument_title', "Intervention History");
        $this->form->addElement("static", null, "<br/>");
        $this->form->addElement("static", null, "<br/>");
        
        // automatically adds examiner & date of administration
        $this->_addMetadataFields();
        $this->form->addElement("static", null, "<br/>");
        $this->form->addElement("select", "q_respondent_", "Respondent", array(null=>'', 'mom'=>'Mom', 'dad'=>'Dad', "teacher"=>"Teacher", "other"=>"Other", "not_answered"=>"Not Answered"));
        $this->addTextElement("respondent_other_", "Other respondent (please specify):", array("respondent_{@}=={@}other"));
        $this->form->addElement("static", null, "<br/>");
        $this->form->addElement('static',null,'<br>');
        $this->form->addElement("textarea", "other_comments", "Comments about Validity:", array('cols'=>25, 'rows'=>4));
        $this->XINRegisterRule("other_comments", array("{other_comments}{@}=={@}NEVER_REQUIRED"));


    }
   
   function _page1(){
                $this->createPages(1);
   }

   function _page2(){
                $this->createPages(2);
   }

   function _page3(){
                $this->createPages(3);
   }

   function _page4(){
                $this->createPages(4);
   }

   function _page5(){
                $this->createPages(5);
   }

   function _page6(){
                $this->createPages(6);
   }

   function _page7(){
                $this->createPages(7);
   }

   function _page8(){
                $this->createPages(8);
   }

   function _page9(){
                $this->createPages(9);
   }

   function _page10(){
                $this->createPages(10);
   }

    function createPages($i){


        $this->form->addElement('header', 'instrument_title', "Intervention History Form $i");
        $this->form->addElement("static", null, "<br/>");
        $this->form->addElement("static", null, "<br/>");


        $this->form->addElement("select", "q1_type_of_intervention_$i", "1. Type of intervention", array(null=>'', '1_intensive_early'=>'1. ABA/discrete trial/Lovaasi/intensive early intervention', '2_occ_therapy'=>'2. Occupational therapy', "3_physical_therapy"=>"3. Physical therapy", "4_speech_therapy"=>"4. Speech Therapy", "5_counseling_child"=>"5. Counseling/psychological services for child", "6_play_therapy"=>"6. Play therapy", "7_music_therapy"=>"7. Music therapy", "8_auditory_training"=>"8. Auditory integration training", "9_teacch"=>"9. TEACCH", "10_developmental_play_therapy"=>"10. Developmental play therapy (Hanen, RDI)", "11_social_skills_training"=>"11. Social skills training", "12_special_ed"=>"12. Special education", "13_parent_child_socialization"=>"13. Parent-Child socialization/skill building support", "14_recreational_sports"=>"14. Recreational sports for child", "15_typical_class"=>"15. Typical class", "16_home_program"=>"16. Home program (not ABA)", "17_nutritional"=>"17. Nutritional", "18_parenting_class"=>"18. Parenting class/seminar", "19_counseling_parent"=>"19. Counseling/psychologial services for parent", "20_parent_child_recreation"=>"20. Parent-Child recreation", "21_other"=>"21. Other (e.g. biomedical)", "none"=>"No interventions", "not_answered"=>"Not Answered"));
        $this->addTextElement("q1_intervention_other_$i", $this->indent . "Other intervention (please specify):", array("q1_type_of_intervention_$i{@}=={@}21_other"));
        $this->form->addElement("static", null, "<br/>");

        $this->addTextElement("q2_school_service_provider_$i", "2. Name of school/service provider");
	$this->XINRegisterRule("q2_school_service_provider_$i", array("q1_type_of_intervention_$i{@}!={@}none"), "This field is required", "q2_school_service_provider_{$i}_group");

        $this->form->addElement("static", null, "<br/>");

        $this->form->addElement("select", "q3_setting_$i", "3. Setting", array(null=>'', 'S'=>"S School", 'C'=>"C Center", 'H'=>"H Home", 'PC'=>"PC Private Clinic", "O"=>"O Other", "not_answered"=>"Not Answered"));
	$this->XINRegisterRule("q3_setting_$i", array("q1_type_of_intervention_$i{@}!={@}none"), "This field is required");
        $this->addTextElement("q3_setting_other_$i", $this->indent . "Other setting (please specify):", array("3_setting_$i{@}=={@}O"));
        $this->form->addElement("static", null, "<br/>");

        $this->addDateElement("q4_date_began_$i", "4. Date began");
        $this->XINRegisterRule("q4_date_began_{$i}_date", array("q1_type_of_intervention_$i{@}!={@}none", "q4_date_began_{$i}_date_status{@}=={@}"), "This field is required", "q4_date_began_{$i}_date_group");
        $this->XINRegisterRule("q4_date_began_{$i}_date_status", array("q1_type_of_intervention_$i{@}!={@}none", "q4_date_began_{$i}_date{@}=={@}"), "This field is required", "q4_date_began_{$i}_date_group");

        $this->form->addElement("static", null, "<br/>");

        $this->addDateElement("q5_date_ended_$i", "5. Date ended");
        $this->XINRegisterRule("q5_date_ended_{$i}_date", array("q1_type_of_intervention_$i{@}!={@}none", "q5_date_ended_{$i}_date_status{@}=={@}"), "This field is required", "q5_date_ended_{$i}_date_group");
        $this->XINRegisterRule("q5_date_ended_{$i}_date_status", array("q1_type_of_intervention_$i{@}!={@}none", "q5_date_ended_{$i}_date{@}=={@}"), "This field is required", "q5_date_ended_{$i}_date_group");
        $this->form->addElement("static", null, "<br/>");

        $this->addNumericElement("q6_hours_per_week_$i", "6. Hours per week");
	$this->XINRegisterRule("q6_hours_per_week_$i", array("q1_type_of_intervention_$i{@}!={@}none"), "This field is required", "q6_hours_per_week_{$i}_group");
        $this->form->addElement("static", null, "<br/>");

        $this->form->addElement("select", "q7_group_individual_$i", "7. Group or individual", array(null=>'', "group"=>"Group", "individual"=>"Individual", "not_answered"=>"Not answered"));
	$this->XINRegisterRule("q7_group_individual_$i", array("q1_type_of_intervention_$i{@}!={@}none"), "This field is required");
        $this->form->addElement("static", null, "<br/>");

        $this->form->addElement("static", null, "8. Class ratio");
        $this->addNumericElement("q8_class_ratio_adult_$i", $this->indent . "# Adult");
	$this->XINRegisterRule("q8_class_ratio_adult_$i", array("q1_type_of_intervention_$i{@}!={@}none"), "This field is required", "q8_class_ratio_adult_{$i}_group");

        $this->addNumericElement("q8_class_ratio_children_$i", $this->indent . "# Child");
	$this->XINRegisterRule("q8_class_ratio_children_$i", array("q1_type_of_intervention_$i{@}!={@}none"), "This field is required", "q8_class_ratio_children_{$i}_group");
        $this->form->addElement("static", null, "<br/>");

        $this->form->addElement("select", "q9_provider_background_$i", "9. Provider background", array(null=>'', "S"=>"S Specialist (e.g. Psychologist/SLP/OT)", "P"=>"P Paraprofessional (e.g. interventionist)", "U"=>"U Untrained parent/volunteer", "not_answered"=>"Not Answered"));
	$this->XINRegisterRule("q9_provider_background_$i", array("q1_type_of_intervention_$i{@}!={@}none"), "This field is required");
        $this->form->addElement("static", null, "<br/>");

        $this->addTextElement("q10_breaks_$i", "10. Breaks (length in weeks)");
	$this->XINRegisterRule("q10_breaks_$i", array("q1_type_of_intervention_$i{@}!={@}none"), "This field is required", "q10_breaks_{$i}_group");
        $this->form->addElement("static", null, "<br/>");

        $this->form->addElement("static", "q11_intensity_$i", "11. Intensity");
        $this->form->addElement("static", null, "<br/>");


    }

	function score()
	{

        $this->_nullScores($this->scoreLabels);


        $db =& Database::singleton();

        $query = "SELECT * FROM ".$this->table." WHERE CommentID='".$this->getCommentID()."'";
	$values = array();
        $db->selectRow($query, $values);


	for ($i=1; $i < 11; $i++)
	{

		if ($values["q1_type_of_intervention_$i"] == 'none')		
			$scores["q11_intensity_$i"] = 0;

		else
		{
			$diff = $this->date_diff($values["q5_date_ended_{$i}_date"], $values["q4_date_began_{$i}_date"]);


			if ($diff == 0)
				$scores["q11_intensity_$i"] = 0;

			else
			{
				$scores["q11_intensity_$i"] = ($diff - $values["q10_breaks_$i"]) * $values["q6_hours_per_week_$i"] * ($values["q8_class_ratio_adult_$i"]/$values["q8_class_ratio_children_$i"]);
				$scores["q11_intensity_$i"] = number_format($scores["q11_intensity_$i"], 2);
			}
		}

	        $result = $db->update($this->table, $scores, array("CommentID"=>$this->getCommentID()));

	}

	}


	function date_diff($d1, $d2){

		$d1 = (is_string($d1) ? strtotime($d1) : $d1);
		$d2 = (is_string($d2) ? strtotime($d2) : $d2);
		
		$year1 = date("Y", $d1);
		$year2 = date("Y", $d2);
		$month1 = date("m", $d1);
		$month2 = date("m", $d2);
		$day1 = date("d", $d1);
		$day2 = date("d", $d2);

		$diffDays = (($year1 - $year2) * 365) + (($month1 - $month2) * 30.5) + ($day1 - $day2);
		$diffWeeks = $diffDays/7;
		return $diffWeeks;
	}
}

?>
