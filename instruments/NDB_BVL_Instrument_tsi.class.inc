<?php

require_once('RequiredIf.inc');


class NDB_BVL_Instrument_tsi extends NDB_BVL_Instrument
{
    var $ValidityEnabled = false;
    var $ValidityRequired = false;

	var $yesNo = array(null=>"", "yes"=>"Yes", "no"=>"No", "not_answered"=>"Not Answered");

	var $education_choices = array(null => "", "not_answered" => "Not Answered", "j_high" => "Junior High", "some_hs" => "Some Highschool", "some_college_12yr_degree" => "Some College 12yr Degree", "college_degree" => "College Degree", "some_grad_level" => "Some Graduate Level", "grad_degree" => "Graduate Degree");
	
	/*
	INSERT INTO test_names VALUES ('', 'tsi', 'Telephone Screening Interview', '0', '1');

	INSERT INTO instrument_subtests VALUES('', 'tsi', 'tsi_page1', 'Exclusionary Factors', 1);
	INSERT INTO instrument_subtests VALUES('', 'tsi', 'tsi_page2', 'Medical History or MRI/Sedation', 2);
	INSERT INTO instrument_subtests VALUES('', 'tsi', 'tsi_page3', 'Medical Records / Research Staff', 3);

	INSERT INTO test_battery VALUES ('', 'tsi', '150', '210', 'Y', 'Screening', '1');
	INSERT INTO test_battery VALUES ('', 'tsi', '300', '420', 'Y', 'Screening', '2');
	INSERT INTO test_battery VALUES ('', 'tsi', '150', '420', 'Y', 'Screening', '3');
	
	ALTER TABLE tsi ADD contact_date date;	
	ALTER TABLE tsi ADD contact_date_status enum('not_answered');
	
	ALTER TABLE tsi ADD contacted_by varchar(255);
	
	ALTER TABLE tsi ADD complications_birth enum('yes','no','not_answered');
	
	ALTER TABLE tsi ADD exc_inc_subject_meets_criteria enum('yes','no','not_answered');      
	
	*/

	/**
	 * Array of column names to be ignored by the double data entry conflict detector.
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
		$this->formType="XIN";
		$this->form = new HTML_Quickform('test_form');
		$this->page = $page;            // page label (number or
		// string - used by
		// user-defined child classes)

		// set the object properties
		$this->testName = "tsi";           // test_names.Test_name
		$this->table = 'tsi';              // name of database table corresponding to instrument
		// data keyed by commentID
		$this->commentID = $commentID;

		//The array of dates/timestamps to convert to database dates/timestamps
		//Any HTML_Quickform date elements must be listed here
		$this->dateTimeFields=array("Date_taken");

		//The array of selects with multiple answers allowed
		//Any HTML_Quickform multiple selects must be listed here
		$this->_selectMultipleElements = array('candidate_race', 'mother_race', 'father_race');

		// required fields for data entry completion status
		$this->_requiredElements = array('Examiner', "ses_income", , "neurological_problems_proband", "med_his_q_1_med_surgical_problems", "exc_inc_meets_criteria");
		$this->_doubleDataEntryDiffIgnoreColumns = array('CommentID', 'UserID', 'Testdate', 
								 'in_utero_substance_proband',
								 'in_utero_substance_proband_status',
								 'in_utero_substance_amount_proband',
								 'in_utero_substance_amount_proband_status',
								 'in_utero_time_exposure_proband',
								 'in_utero_time_exposure_proband_status',
								 'asd_further_information',
								 'asd_further_information_status',
								 'med_his_q_3_surgery_describe',
								 'med_his_q_3_surgery_describe_status',
								 'med_his_q_5_medications_describe',
								 'med_his_q_5_medications_describe_status',
								 'med_his_q_6_allergies_describe',
								 'med_his_q_6_allergies_describe_status',
								 'med_his_q_8_brain_MRI_results',
								 'med_his_q_8_brain_MRI_results_status',								
								 'med_his_q_9_anethesia_problems',
								 'med_his_q_9_anethesia_problems_status',
								 'med_his_q_10_nap',
								 'med_his_q_10_nap_status',
								 'med_his_q_11_nap_how_long',
								 'med_his_q_11_nap_how_long_status',
                                 'further_information');
		

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
		if(ereg("tsi(_page[0-9]+)",$this->page,$matches)){
			call_user_method($matches[1], &$this);
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
		// display test name
		$this->form->addElement('header', 'instrument_title', 
"Telephone Screening Interview");

		// automatically adds examiner & date of administration
		$this->_addMetadataFields();

		$this->form->addElement('header', null, "Identifying information");
		$this->form->addElement('header', null, "This type of identifying information should not be entered in the database");
		
		$config =& NDB_Config::singleton();

	        $this->dateOptions = array(
        	'language' => 'en',
        	'format'   => 'YMd',
        	'minYear'  => $config->getSetting('startYear') - 20, //allows for siblings up to 20 years older than candidate
        	'maxYear'  => $config->getSetting('endYear'),
        	'addEmptyOption' => true,
        	'emptyOptionValue' => null
	    	);
        
		$nonAskedQuestions = array("Subject's Name",
		"Subject ID:",
		"Date of Contact:", 
		"Date of Birth:",
		"Contacted By:",
		"Subject's Gender: $this->indent Subject's Age (in months):");
		foreach ($nonAskedQuestions as $field) {
		    if($field == "Date of Contact:"){
		        $this->addDateElement("contact", $field);
		    }
		    elseif($field == "Contacted By:"){
		        $this->form->addElement("text", "contacted_by", $field);
    	        $this->XINRegisterRule ( "contacted_by", array ("contact_date_status{@}!={@}not_answered"), "Please enter person who contacted" );

		    }
		    else{
		        $this->form->addElement('static', null, $field);
		    }
		}
		
		//Ethnicity
		$this->form->addElement("select", "child_ethnicity", "Candidate Ethnicity:", array(null=>"", "hispanic"=>"Hispanic", "non_hispanic"=>"Non-Hispanic", "not_answered"=>"Not Answered"));

		$this->form->addElement("select", "mother_ethnicity", "Mother Ethnicity:", array(null=>"", "hispanic"=>"Hispanic", "non_hispanic"=>"Non-Hispanic", "not_answered"=>"Not Answered"));

		$this->form->addElement("select", "father_ethnicity", "Father Ethnicity:", array(null=>"", "hispanic"=>"Hispanic", "non_hispanic"=>"Non-Hispanic", "not_answered"=>"Not Answered"));
		

		//RACES
		$this->form->addElement("select", "candidate_race", "Candidate Race:", array("white"=>"White", "black_african_american"=>"Black or African American", "asian"=>"Asian", "unknown_not_reported"=>"Unknown or not Reported", "american_indian_alaska_native"=>"American Indian / Alaska Native", "native_hawaiian_pacific_islander"=>"Native Hawaiian / Other Pacific Islander", "more_than_one_race"=>"More than one race (select all applicable)"), "multiple");
        	$this->form->addRule("candidate_race", "Must answer this race question", 'required');
		
		$this->form->addElement("select", "mother_race", "Mother Race:", array("white"=>"White", "black_african_american"=>"Black or African American", "asian"=>"Asian", "unknown_not_reported"=>"Unknown or not Reported", "american_indian_alaska_native"=>"American Indian / Alaska Native", "native_hawaiian_pacific_islander"=>"Native Hawaiian / Other Pacific Islander", "more_than_one_race"=>"More than one race (select all applicable)"), "multiple");
        	$this->form->addRule("mother_race", "Must answer this race question", 'required');

        	$this->form->addElement("select", "father_race", "Father Race:", array("white"=>"White", "black_african_american"=>"Black or African American", "asian"=>"Asian", "unknown_not_reported"=>"Unknown or not Reported", "american_indian_alaska_native"=>"American Indian / Alaska Native", "native_hawaiian_pacific_islander"=>"Native Hawaiian / Other Pacific Islander", "more_than_one_race"=>"More than one race (select all applicable)"), "multiple");
       
        	$this->form->addRule("father_race", "Must answer this race question", 'required');
		
		$this->form->addElement("static", null, "<b>Parent's Information:</b><br><br>");
		
		$this->addTextElement("primary_language", "Primary language spoken in the home:");
		
		//Mother's Information
    	$this->form->addElement("static", null, "<b>Mother's Information</b><br>");
		
		/*
     	$this->addTextElement("mother_first_name", "First Name:");
     	$this->form->addElement("text", "mother_middle_name", "Middle Name:");
	    $this->addTextElement ("mother_last_name", "Last Name" );
        */
        
        $this->form->addElement("static", null, "First Name:<br>");
    	$this->form->addElement("static", null, "Middle Name: <br>");
    	$this->form->addElement("static", null, "Last Name: <br>");
    	
        $this->addTextElement("mother_occupation", "Occupation:");        
        
        $this->form->addElement("select", "mother_education", "Highest Level of Education", array(null => "", "not_answered" => "Not Answered", "j_high" => "Junior High", "some_hs" => "Some Highschool", "high_school"=> "High School", "some_college" => "Some College/2yr Degree", "college_degree" => "College Degree", "some_grad_level" => "Some Graduate Level", "grad_degree" => "Graduate Degree"));
    	
    	$this->XINRegisterRule ( "mother_education_rule", array ("mother_education{@}!={@}"), "Please enter the mother's education" );
        
    
    	$config =& NDB_Config::singleton();
        
        $this->dateOptions = array(
            'language' => 'en',
            'format'   => 'YMd',
            'minYear'  => $config->getSetting('startYear') -80, //allows for siblings up to 20 years older than candidate
            'maxYear'  => $config->getSetting('endYear'),
            'addEmptyOption' => true,
            'emptyOptionValue' => null
    	);
		
	   $this->addDateElement('mother_dob', "Date of Birth:");
       
	    //Father's Information
	    
        $this->form->addElement("static", null, "<br><br><b>Father's Information</b><br>");
        
        $this->form->addElement("static", null, "First Name:<br>");
        $this->form->addElement("static", null, "Middle Name: <br>");
        $this->form->addElement("static", null, "Last Name: <br>");

        /*
        $this->addTextElement("father_first_name", "First Name:");
        $this->form->addElement("text", "father_middle_name", "Middle Name:");
    	$this->addTextElement ("father_last_name", "Last Name" );
        */
        
        $this->addTextElement("father_occupation", "Occupation:");        

        $this->form->addElement("select", "father_education", "Highest Level of Education", array(null => "", "not_answered" => "Not Answered", "j_high" => "Junior High", "some_hs" => "Some Highschool", "high_school"=> "High School", "some_college" => "Some College/2yr Degree", "college_degree" => "College Degree", "some_grad_level" => "Some Graduate Level", "grad_degree" => "Graduate Degree"));
        
        $this->XINRegisterRule ( "father_education_rule", array ("father_education{@}!={@}"), "Please enter the father's education" );

    	$config =& NDB_Config::singleton();

	$this->addDateElement('father_dob', "Date of Birth:");
      		
      	$this->form->addElement("static", null, "<br><br>");
      	
	$this->form->addElement("select", "ses_income", "SES:", array(null=>"", "less_than_25K"=>"less than $24,999", "25K-35K"=>"$25,000 - 34,999", "35K-50K"=>"$35,000 - 49,999", "50K-75K"=>"$50,000 - 74,999", "75K-100K"=>"$75,000 - 99,999", "100K-150K"=>"$100,000 - 149,999", "150K-200K"=>"$150,000 - 199,000", "over_200K"=>"over $200,000", "not_answered"=>"Not Answered"));

        $nonAskedQuestions = array("<br>Parent's Telephone:",
		"Parent's Address:",
		"$this->indent a) Older sibling",
		"$this->indent b) other siblings:",
		"Nature of Referral:",
		"SUBJECT  Ever been a patient at UNC?");
		foreach ($nonAskedQuestions as $field) {
			$this->form->addElement('static', null, $field);
		}
	}

	function _page1(){

		$this->form->addElement('header', null, "Exclusionary Factors - ASD PROBANDs only");

		$questionArray = array("neurological_problems_proband"=>"Any neurological problems in PROBAND?",
		"genetic_conditions_proband"=>"Diagnosed/suspected genetic conditions or syndromes?",
		"seizures_disorders"=>"Seizures/other neurological disorder (tuberous sclerosis)?",
		"relative_with_disorder"=>"1st degree relative w/ MR, schizophrenia, bipolar or psychosis?",
		"cns"=>"CNS problem/injury?",
		"tested_for_fragile_x"=>"Tested for Fragile X syndrome?");
		foreach($questionArray as $field=>$label) {
			$this->form->addElement("select", $field, $label, $this->yesNo);
		}

		$this->form->addElement('select', "in_utero_exposure_proband", "Exposure in-utero to meds, alcohol, or drugs (Rx or non)?", $this->yesNo);

		$questionArray = array("substance_proband"=>"Name of substance (get spelling):",
		"substance_amount_proband"=>"Amount of substance at one time:",
		"time_exposure_proband"=>"Time period of exposure (weeks of pregnancy):");
		foreach($questionArray as $field=>$label) {
			$this->addTextElement("in_utero_" . $field, $this->indent . $label, array("in_utero_exposure_proband{@}=={@}yes"), "This field is required if there was in-utero exposure");
		}

		$this->addTextAreaElement("asd_further_information", "If yes to any of the above, obtain further information.", array("typical_or_asd_subject{@}=={@}asd"));

		$this->form->addElement("header", null, "Exclusionary Factors - Infant subjects");
		$questionArray = array(
		"neurological_problems_subject"=>"Any neurological problems in SUBJECT?",
		"genetic_conditions_subject"=>"Diagnosed/suspected genetic conditions or syndromes?",
		"seizures_or_neuro_disorder"=>"Seizures or other neurological disorder?",
		"cns_problems"=>"CNS problems?",
		"congenital_heart_problems"=>"Congenital heart problems?",
		"hearing_vision_impairments"=>"Significant hearing/vision problems?",
		"diabetes"=>"Diabetes or gestational diabetes?",
		"complications_birth" => "Any complications at birth?",
		"premature_birth"=>"Premature birth (<37 weeks )?",
		"low_birth_weight"=>"Birth weight <4lbs. 6oz. (2000 grams)?",
		"tested_for_fragile_x_subject"=>"Tested for Fragile X syndrome?",
		"delivery_problems"=>"Problems during delivery?");
		foreach($questionArray as $field=>$label) {
			$this->form->addElement("select", $field, $label, $this->yesNo);
			if ($field == 'premature_birth') {
			    $this->addTextElement('weeks_gestation', $this->indent . "Number of weeks gestation", array("premature_birth{@}=={@}yes"), "If premature, how many gestational weeks?");
			}
		}

		$this->form->addElement('select', "in_utero_exposure", "Exposure in-utero to meds, alcohol, or drugs (Rx or non)?", $this->yesNo);

		$questionArray = array("substance"=>"Name of substance (get spelling):",
		"substance_amount"=>"Amount of substance at one time:",
		"time_exposure"=>"Time period of exposure (weeks of pregnancy):");
		foreach($questionArray as $field=>$label) {
			$this->addTextElement("in_utero_" . $field, $this->indent . $label, array("in_utero_exposure{@}=={@}yes"), "This field is required if there was in-utero exposure");
		}
		$this->addTextAreaElement("further_information", "If yes to any of the above, obtain further information.");
	}

	function _page2() {
		$this->form->addElement('header', null, "Medical History Pertaining to MRI/Sedation");
		$this->form->addElement("select", "med_his_q_1_med_surgical_problems", "1. Has X ever had any serious medical or surgical problems?", $this->yesNo);
		$this->form->addElement("select", "med_his_q_2_hospitalized", "2. Has X ever been hospitalized?", $this->yesNo);
		$this->form->addElement("select", "med_his_q_3_surgery", "3. Surgery of any type?", $this->yesNo);
		$this->addTextElement("med_his_q_3_surgery_describe", $this->indent . "Describe:", array("med_his_q_3_surgery{@}=={@}yes"), "This field is required if there was surgery");
		$this->form->addElement("select", "med_his_q_4_metal", "4. Does X have any metal plates, clips, etc. from surgery?", $this->yesNo);
		$this->form->addElement("select", "med_his_q_5_medications", "5. Has X taken any medications over the last 12 months?", $this->yesNo);
		$this->addTextElement("med_his_q_5_medications_describe", $this->indent . "If yes, list medications:", array("med_his_q_5_medications{@}=={@}yes"), "This field is required if there were medications");
		$this->form->addElement("select", "med_his_q_6_allergies", "6. Does X have any allergies to medicines?", $this->yesNo);
		$this->addTextElement("med_his_q_6_allergies_describe", $this->indent . "If yes, describe:", array("med_his_q_6_allergies{@}=={@}yes"), "This field is required if there are allergies");
		$this->form->addElement("select", "med_his_q_7_doctor", "7. Has X seen a doctor over the last 12 months?", $this->yesNo);
		$this->form->addElement("select", "med_his_q_8_brain_MRI", "8. Has X ever had an MRI of the brain?", $this->yesNo);
		$this->addTextElement("med_his_q_8_brain_MRI_results", $this->indent . "If yes, what were the results?", array("med_his_q_8_brain_MRI{@}=={@}yes"), "This field is required if a brain MRI was done.");
		$this->form->addElement("select", "med_his_q_9_anethesia", "9. Has X ever had anesthesia or other forms of sedation?", $this->yesNo);
		$this->addTextElement("med_his_q_9_anethesia_problems", $this->indent . "Problems with sedation?", array("med_his_q_9_anethesia{@}=={@}yes"), "This field is required if there were sedation problems.");
		$this->addTextElement("med_his_q_10_nap", "10. Does X nap during the day?");
		$this->addTextElement("med_his_q_11_nap_how_long", "11. When & how long?");
		$this->form->addElement("select", "med_his_q_12_likelihood_sleep", "12. On a scale of 1-10, please rate the likelihood of your child sleeping through a scan.", array(null=>"", 1=>"1", 2=>"2",  3=>"3", 4=>"4", 5=>"5", 6=>"6", 7=>"7", 8=>"8", 9=>"9", 10=>"10", "not_answered"=>"Not Answered"));
		
	}

	function _page3() {
		$this->form->addElement("header", null, "Medical Records");
		$this->addTextElement("city_of_birth", "City of Birth:");
        
		$this->form->addElement('header', null, "This type of identifying information should not be entered in the database");
		$this->form->addElement("static", null, "Any diagnoses, dates and locations:");
		$this->form->addElement("static", null, "Has X had any other cognitive/developmental testing?");
		$this->form->addElement("static", null, $this->indent . "If yes, where was evaluation done/who conducted the evaluation?");
		$this->form->addElement("static", null, "Is any member of your family participating in a research study at this time?");
		
		$this->form->addElement("header", null, "FOR RESEARCH STAFF TO COMPLETE");
		$this->form->addElement("static", null, "Exclusion/Inclusion");
		$this->form->addElement("select", "exc_inc_meets_criteria", "1. This proband meets any of the medical or neurological exclusion criteria for this study. (see Section A)", $this->yesNo);
		$this->form->addElement("select", "exc_inc_subject_meets_criteria", "2. This subject meets any of the medical or neurological exclusion criteria for this study. (see Section B)", $this->yesNo);
		$this->form->addElement("select", "exc_inc_contraindication", "3. This subject has evidence for contraindication to MRI. (see Section B)", $this->yesNo);
		$this->form->addElement("static", null, "Disposition");
		$this->form->addElement("select", "disposition", "Proceed to next level beyond screening?", $this->yesNo);
	}
	
}
?>
