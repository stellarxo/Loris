<?php

require_once('RequiredIf.inc');
require_once 'HTML/QuickForm.php';
require_once 'HTML/QuickForm/Renderer/Array.php';

class NDB_BVL_Instrument_tsi_followup extends NDB_BVL_Instrument
{
    	var $ValidityEnabled = false;
    	var $ValidityRequired = false;

	var $yesNo = array(null=>"", "yes"=>"Yes", "no"=>"No", "not_answered"=>"Not Answered");

	var $education_choices = array(null => "", "not_answered" => "Not Answered", "j_high" => "Junior High", "some_hs" => "Some Highschool", "some_college_12yr_degree" => "Some College 12yr Degree", "college_degree" => "College Degree", "some_grad_level" => "Some Graduate Level", "grad_degree" => "Graduate Degree");
 	
	function getSession()
	{
		$db =& Database::singleton();
        $sessionid = $this->getSessionID();
        if($sessionid === false){
           return null;    
        }
        $timepoint =& TimePoint::singleton($sessionid);
        $candidate =& Candidate::singleton($timepoint->getCandID());
        $candID = $timepoint->getCandID(); 
        $projID = $candidate->getProjectID();

        if ($projID == 2) {
            //for IBIS2 tsi is part of Screening visit
            $sessionid = $db->pselectOne("SELECT ID FROM session WHERE CandID=:cndID and Visit_label LIKE '%screening%'", 
                                          array('cndID' => $candID));
        } else { 
 		    $sessionid = $db->pselectOne("SELECT ID FROM session WHERE CandID=:cndID and Visit_label LIKE '%06'", 
                                          array('cndID' => $candID));
        }
        if($sessionid == array()) {
            return null;
        }
		return $sessionid;
	}

	function getComment($sessionid)
	{
		$db =& Database::singleton();
	
 		$commentid = $db->pselectOne("SELECT CommentID FROM flag WHERE SessionID=:SID and Test_name = 'tsi' and CommentID NOT LIKE 'DDE%'", array('SID' => $sessionid));
        if($commentid == array()) {
            return null;
        }
		
		return $commentid;
	}

	/*
	INSERT INTO test_names VALUES ('', 'tsi_followup', 'Telephone Screening Interview - Followup', '0', '1', NULL);

	INSERT INTO instrument_subtests VALUES('', 'tsi_followup', 'tsi_followup_page1', 'Exclusionary Factors', 1);
	INSERT INTO instrument_subtests VALUES('', 'tsi_followup', 'tsi_followup_page2', 'Medical History or MRI/Sedation', 2);
	INSERT INTO instrument_subtests VALUES('', 'tsi_followup', 'tsi_followup_page3', 'Medical Records', 3);
	INSERT INTO instrument_subtests values('', 'tsi_followup', 'tsi_followup_page4', 'Research Staff', 4);

	INSERT INTO test_battery VALUES ('', 'tsi_followup', '300', '420', 'Y', 'Visit', '1', NULL);
	INSERT INTO test_battery VALUES ('', 'tsi_followup', '660', '780', 'Y', 'Visit', '1', NULL);
	INSERT INTO test_battery VALUES ('', 'tsi_followup', '1053', '1179', 'Y', 'Visit', '1', NULL);
	INSERT INTO test_battery VALUES ('', 'tsi_followup', '660', '780', 'Y', 'Visit', '2', NULL);
	INSERT INTO test_battery VALUES ('', 'tsi_followup', '1053', '1179', 'Y', 'Visit', '2', NULL);
	INSERT INTO test_battery VALUES ('', 'tsi_followup', '300', '420', 'Y', 'Visit', '3', NULL);
	INSERT INTO test_battery VALUES ('', 'tsi_followup', '660', '780', 'Y', 'Visit', '3', NULL);
	INSERT INTO test_battery VALUES ('', 'tsi_followup', '1053', '1179', 'Y', 'Visit', '3', NULL);


	
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
		$this->testName = "tsi_followup";           // test_names.Test_name
		$this->table = 'tsi_followup';              // name of database table corresponding to instrument
		// data keyed by commentID
		$this->commentID = $commentID;

		//The array of dates/timestamps to convert to database dates/timestamps
		//Any HTML_Quickform date elements must be listed here
		$this->dateTimeFields=array("Date_taken");

		//The array of selects with multiple answers allowed
		//Any HTML_Quickform multiple selects must be listed here
		$this->_selectMultipleElements = array('candidate_race', 'mother_race', 'father_race');

		// required fields for data entry completion status
		$this->_requiredElements = array("ses_income", "neurological_problems_subject", "med_his_q_1_med_surgical_problems", "exc_inc_meets_criteria" );
		$this->_doubleDataEntryDiffIgnoreColumns = array('CommentID', 'UserID', 'Testdate',  'Window_Difference', 'Candidate_Age',
								 'in_utero_substance_proband',
								 'in_utero_substance_amount_proband',
								 'in_utero_time_exposure_proband',
								 'asd_further_information',
								 'med_his_q_3_surgery_describe',
								 'med_his_q_5_medications_describe',
								 'med_his_q_6_allergies_describe',
								 'med_his_q_8_brain_MRI_results',
								 'med_his_q_9_anethesia_problems',
								 'med_his_q_10_nap',
								 'med_his_q_10_nap_status',
								 'med_his_q_11_nap_how_long',
                                 'further_information',
                                 'Data_entry_completion_status');
         
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

		if(preg_match("/tsi_followup(_page[0-9]+)/",$this->page,$matches)){
			call_user_method($matches[1], $this);
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
		$this->form->addElement('header', 'instrument_title', "Telephone Screening Interview - Followup");

		// automatically adds examiner & date of administration
		$this->_addMetadataFields();

		$this->form->addElement('header', null, "Identifying information");
		
		$config =& NDB_Config::singleton();

	        $this->dateOptions = array(
        	'language' => 'en',
        	'format'   => 'YMd',
        	'minYear'  => $config->getSetting('startYear') - 20, //allows for siblings up to 20 years older than candidate
        	'maxYear'  => $config->getSetting('endYear'),
        	'addEmptyOption' => true,
        	'emptyOptionValue' => null
	    	);
        
		$nonAskedQuestions = array("Subject's Name:",
		"Subject ID:",
		"Date of Birth:",
        "Estimated Due Date: $this->indent Data entered during candidate registration",
		"Subject's Age (in months):");
		foreach ($nonAskedQuestions as $field) {
		        $this->form->addElement('static', null, $field);
		    }
		//Ethnicity
		$this->form->addElement("static", null, "<br/><b>The following information does not change across time. Please ensure that it is entered in the TSI.</b>");

		$sessionid = $this->getSession();
		$commentid = $this->getComment($sessionid);
        $url = '';
        if(isset($_REQUEST['candID'])) {
            $url = "main.php?test_name=tsi&candID=".$_REQUEST['candID']."&sessionID=".$sessionid."&commentID=".$commentid;
            $this->form->addElement("link", null, "City of Birth:", $url, 'Click here to verify or enter this data in the TSI');
        } else {
            $this->form->addElement("link", null, "City of Birth:", '', 'Error: No Candidate specified');
        }
		$this->form->addElement("static", null, "Candidate Ethnicity:");		

//		$this->form->addElement("link", null, "Candidate Ethnicity:", $url, 'Click here to verify or enter this data in the TSI'); 

//              $this->form->addElement('link', null, null, "$url", 'Enter this data in the TSI');

 //               $url = "main.php?test_name=tsi&candID=".$_REQUEST['candID']."&sessionID=".$sessionid."&commentID=".$commentid;


		$this->form->addElement("static", null, "Mother Ethnicity:");

		$this->form->addElement("static", null, "Father Ethnicity:"); 
		

		//RACES
		$this->form->addElement("static", null, "Candidate Race:");
		
		$this->form->addElement("static", null, "Mother Race:");

        	$this->form->addElement("static", null, "Father Race:");
		
		$this->form->addElement("header", null, "<br/><b>Parents' Information</b><br>");
		
		//Mother's Information
    		$this->form->addElement("static", null, "<br/><b>Mother's Information</b><br>");
		
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
		
        $this->form->addElement("link", null, "Date of birth:", $url, 'Click here to verify or enter this data in the TSI');
//	$this->form->addElement("static", 'mother_dob', "Date of Birth:");
       

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

        $this->form->addElement("link", null, "Date of Birth:", $url, 'Click here to verify or enter this data in the TSI');
	//$this->form->addElement("static", 'father_dob', "Date of Birth:");
      		
      	$this->form->addElement("static", null, "<br><br>");
      	
	$this->form->addElement("select", "ses_income", "SES:", array(null=>"", "less_than_25K"=>"less than $24,999", "25K-35K"=>"$25,000 - 34,999", "35K-50K"=>"$35,000 - 49,999", "50K-75K"=>"$50,000 - 74,999", "75K-100K"=>"$75,000 - 99,999", "100K-150K"=>"$100,000 - 149,999", "150K-200K"=>"$150,000 - 199,000", "over_200K"=>"over $200,000", "not_answered"=>"Not Answered"));

        $nonAskedQuestions = array("<br>Parent's Telephone:",
		"Parent's Address:",
		"$this->indent a) Older sibling",
		"$this->indent b) Other siblings",
		"Nature of Referral:",
		);
		foreach ($nonAskedQuestions as $field) {
			$this->form->addElement('static', null, $field);
		}

        $this->form->addElement("static", null, "<br><br><b>Other siblings</b><br>");
	for($i = 1; $i<=10; $i++) {
		$this->addScoreColumn(null, "Sibling $i");
		$field = 'age_sibling'.$i; $label = $this->indent. 'Age (Please indicate age in years):';
		$group [] = $this->createText($field, $label);
		$this->addGroup($group, $field . "_group", $label, null, false);
		$this->XINRegisterRule($field,array("$field{@}=={@}NEVER_REQUIRED"), $field . "_group");
		unset($group);
		$this->addGroupRule($field . "_group", array(array(array("Value must be numeric.", 'numeric'))));
		$this->addTextElement("dx_sibling".$i, $this->indent . "Dx:");
		$this->XINRegisterRule("dx_sibling".$i,array("$field{@}!={@}"), "Specify diagnoses for sibling $i", "dx_sibling".$i."_group");
		$this->addSelect('relation_sibling'.$i, $this->indent. "Specify relationship:",
				array(''=>NULL,'half_sibling'=>'Half sibling', 'full_sibling'=>'Full sibling',
					'step_sibling'=>'Step sibling','not_answered'=>'Not Answered'));
		$this->XINRegisterRule("relation_sibling".$i, array("$field{@}!={@}"), "Specify relationship for sibling $i");
		$this->addSelect('live_at_home_sibling'.$i, $this->indent. "Live in home:", array(''=>NULL,'yes'=>'Yes','no'=>'No','not_answered'=>'Not Answered'));
		$this->XINRegisterRule("live_at_home_sibling".$i, array("$field{@}!={@}"), "Specify if sibling $i lives at home or not");
	}

	}

	function _page1(){

		$this->form->addElement('header', null, "Exclusionary Factors - PROBANDs only");

		$questionArray = array("neurological_problems_proband"=>"Any neurological problems such as Cerebral Palsy or Tuber Sclerosis in PROBAND?",
		"genetic_conditions_proband"=>"Diagnosed/suspected genetic conditions or syndromes?",
	//	"relative_with_disorder"=>"1st degree relative w/ MR, schizophrenia, bipolar or psychosis?",
        "relative_mr" =>$this->indent."MR?",
        "relative_schizophrenia"=>$this->indent."Schizophrenia?",
        "relative_bipolar"=>$this->indent."Bipolar?",
        "relative_psychosis"=>$this->indent."Psychosis?",
		"cns"=>"CNS problem/injury such as a head injury or meningitis?",
		"tested_for_fragile_x"=>"Tested for Fragile X syndrome?");
		foreach($questionArray as $field=>$label) {
			$this->form->addElement("select", $field, $label, $this->yesNo);
//			$this->XINRegisterRule($field, array("typical_or_asd_subject{@}=={@}asd"), "This field is required for an ASD subject");
        }
      	$this->addTextAreaElement("asd_further_information", "If yes to any of the above, obtain further information.");  //array("typical_or_asd_subject{@}=={@}asd"));

		$this->form->addElement("header", null, "Exclusionary Factors - Infant subjects");
		$questionArray = array(
		"neurological_problems_subject"=>"Any neurological problems such as Cerebral Palsy or Tuber Sclerosis in SUBJECT?",
		"genetic_conditions_subject"=>"Diagnosed/suspected genetic conditions or syndromes?",
		"seizures_or_neuro_disorder"=>"Do they have or have had any seizures?",
		"cns_problems"=>"CNS problems such as head injury or meningitis?",
		"congenital_heart_problems"=>"Congenital heart problems?",
		"hearing_vision_impairments"=>"Significant hearing/vision problems?",
		"diabetes"=>"Diabetes?",
		"tested_for_fragile_x_subject"=>"Tested for Fragile X syndrome?");
		foreach($questionArray as $field=>$label) {
			$this->form->addElement("select", $field, $label, $this->yesNo);
			if ($field == 'premature_birth') {
			    $this->addTextElement('weeks_gestation', $this->indent . "Number of weeks gestation", array("premature_birth{@}=={@}yes"), "If premature, how many gestational weeks?");
            }
        }
		$this->addTextAreaElement("further_information", "If yes to any of the above, obtain further information.");
	}

	function _page2() {
		$this->form->addElement('header', null, "Medical History Pertaining to MRI/Sedation");
		$this->form->addElement("static", null, '<br />');
		$this->form->addElement("select", "med_his_q_1_med_surgical_problems", "1. Has X ever had any serious medical or surgical problems?", $this->yesNo);
		$this->form->addElement("select", "med_his_q_2_hospitalized", "2. Has X ever been hospitalized?", $this->yesNo);
		$this->form->addElement("select", "med_his_q_3_surgery", "3. Surgery of any type?", $this->yesNo);
		$this->addTextElement("med_his_q_3_surgery_describe", $this->indent . "Describe:", array("med_his_q_3_surgery{@}=={@}yes"), "This field is required if there was surgery");
		$this->form->addElement("select", "med_his_q_4_metal", "4. Does X have any metal plates, clips, etc. from surgery?", $this->yesNo);
		$this->form->addElement("select", "med_his_q_5_medications", "5. Has X taken any medications since their last visit?", $this->yesNo);
		$this->addTextElement("med_his_q_5_medications_describe", $this->indent . "If yes, list medications:", array("med_his_q_5_medications{@}=={@}yes"), "This field is required if there were medications");
		$this->form->addElement("select", "med_his_q_6_allergies", "6. Does X have any allergies to medicines?", $this->yesNo);
		$this->addTextElement("med_his_q_6_allergies_describe", $this->indent . "If yes, describe:", array("med_his_q_6_allergies{@}=={@}yes"), "This field is required if there are allergies");
		$this->form->addElement("select", "med_his_q_7_doctor", "7. Has X seen a doctor since their last visit?", $this->yesNo);
        $this->form->addElement("select", "med_his_q_8_brain_MRI", "8. Has X ever had an MRI of the brain outside of IBIS?", $this->yesNo);
        $this->form->addElement("select","med_his_q_8_brain_MRI_results", $this->indent . "If yes, what were the results?", array(null=>"","typical"=>"Typical","atypical"=>"Atypical","not_answered"=>"Not Answered"));
        $this->XINRegisterRule ( "med_his_q_8_brain_MRI_results", array("med_his_q_8_brain_MRI{@}=={@}yes"),"Please specify results");
        $this->addTextAreaElement("med_his_q_8_brain_MRI_notes", $this->indent . "Notes", array("med_his_q_8_brain_MRI_results{@}=={@}atypical"));
        $this->form->addElement("select", "med_his_q_9_anethesia", "9. Has X ever had anesthesia or other forms of sedation?", $this->yesNo);
        $this->form->addElement("select","med_his_q_9_anethesia_problems", $this->indent . "Problems with sedation?",$this->yesNo);
        $this->XINRegisterRule ( "med_his_q_9_anethesia_problems", array("med_his_q_9_anethesia{@}=={@}yes"),"Please specify if there were problems");
        $this->addTextAreaElement("med_his_q_9_anethesia_notes", $this->indent . "Notes", array("med_his_q_9_anethesia_problems{@}=={@}yes"));

        $this->addTextElement("med_his_q_10_nap", "10. Does X nap during the day?");
		$this->addTextElement("med_his_q_11_nap_how_long", "11. When & how long?");
		$this->form->addElement("select", "med_his_q_12_likelihood_sleep", "12. On a scale of 1-10, please rate the likelihood of your child sleeping through a scan.", array(null=>"", 1=>"1", 2=>"2",  3=>"3", 4=>"4", 5=>"5", 6=>"6", 7=>"7", 8=>"8", 9=>"9", 10=>"10", "not_answered"=>"Not Answered"));
     

	}

	function _page3() {
		$this->form->addElement("header", null, "Additional Information");
/*
  		$sessionid = $this->getSession();
                $commentid = $this->getComment($sessionid);
                $url = "main.php?test_name=tsi&candID=".$_REQUEST['candID']."&sessionID=".$sessionid."&commentID=".$commentid;
		$this->form->addElement("static", null, "<br/><b>The following information does not change across time. Please ensure that it is entered in the TSI.</b>");
                $this->form->addElement("link", null, "City of Birth:", $url, 'Click here to verify or enter this data in the TSI');
       */

    		$config =& NDB_Config::singleton();
        	$this->dateOptions = array(
            		'language' => 'en',
            		'format'   => 'YMd',
            		'minYear'  => $config->getSetting('startYear'),
            		'maxYear'  => $config->getSetting('endYear'),
            		'addEmptyOption' => true,
            		'emptyOptionValue' => null
        	);
/*
		$this->form->addElement("static", null, '<br />');
		$this->form->addElement("select", "diagnoses", "Has X had any diagnoses?", array(NULL=>"", "yes"=>"Yes", "no"=>"No", "not_answered"=>"Not Answered"));
		$this->form->addElement("static", null, "If you answered yes, please specify dates and locations:");
		
		for ($i = 1; $i<6; $i++)
		{
			$this->addDateElement("date_diagnosis$i", $this->indent . "Date of diagnosis $i:");
			$this->addTextElement("location_diagnosis$i", $this->indent . "Location of diagnosis $i:");

			if ($i == 1)
			{
				$this->XINRegisterRule("date_diagnosis{$i}_date", array("diagnoses{@}=={@}yes", "date_diagnosis{$i}_date_status{@}=={@}"), "If you answered yes, you must specify date", "date_diagnosis{$i}_date_group");	
				$this->XINRegisterRule("date_diagnosis{$i}_status", array("diagnoses{@}=={@}yes", "date_diagnosis{$i}_date{@}=={@}"), "If you answered yes, you must specify date", "date_diagnosis{$i}_date_group");	
				$this->XINRegisterRule("location_diagnosis$i", array("diagnoses{@}=={@}yes"), "If you answered yes, you must specify location", "location_diagnosis{$i}_group"); 
			}

			else
			{
				$this->XINRegisterRule("date_diagnosis{$i}_date", array("date_diagnosis{$i}_date{@}=={@}NEVER_REQUIRED"), "date_diagnosis$i"); 
				$this->XINRegisterRule("date_diagnosis{$i}_status", array("date_diagnosis{$i}_status{@}=={@}NEVER_REQUIRED"), "date_diagnosis$i"); 
				$this->XINRegisterRule("location_diagnosis$i", array("location_diagnosis{$i}{@}=={@}NEVER_REQUIRED")); 
			}
		}

		$this->form->addElement("static", null, '<br />');
		$this->form->addElement("static", null, "If more than 5 diagnoses, contact DCC or report a Mantis bug.");
		$this->form->addElement("static", null, '<br />');

		$this->form->addElement("select", "cog_dev_testing", "Has X had any other cognitive/developmental testing?", array(NULL=>"", "yes"=>"Yes", "no"=>"No", "not_answered"=>"Not Answered"));
		$this->form->addElement("static", null, $this->indent . "If yes, where was evaluation done/who conducted the evaluation?");

                for ($i = 1; $i<6; $i++)
                {
                        $this->addTextElement("where_evaluation$i", $this->indent . "Location of evaluation $i:");
                        $this->addTextElement("who_evaluation$i", $this->indent . "Who conducted evaluation $i:");

			if ($i == 1)
			{
				$this->XINRegisterRule("where_evaluation$i", array("cog_dev_testing{@}=={@}yes"), "If you answered yes, you must specify location", "where_evaluation{$i}_group");
				$this->XINRegisterRule("who_evaluation$i", array("cog_dev_testing{@}=={@}yes"), "If you answered yes, you must specify who conducted evaluation", "who_evaluation{$i}_group");
			}

			else
			{
				$this->XINRegisterRule("where_evaluation$i", array("where_evaluation$i{@}=={@}NEVER_REQUIRED"));
				$this->XINRegisterRule("who_evaluation$i", array("who_evaluation$i{@}=={@}NEVER_REQUIRED"));
			}
                }
*/
      	$this->form->addElement("select","med_overall_concern","Do you have overall or specific concerns about your child's development at this time?", $this->yesNo);
        $this->addTextAreaElement("med_overall_concern_notes", $this->indent . "If yes, what are they?", array("med_overall_concern{@}=={@}yes"));
  
		$this->form->addElement("static", null, '<br />');

		$this->form->addElement("static", null, "Has the Infant SIB received any therapies (e.g. behavioral, physical, speech, occupational)?");
	
		for ($i=1; $i<7; $i++)
		{
			$this->form->addElement("select", "therapy$i", $this->indent . "$i. Type of Tx", array("NULL"=>"", "1_intensive_early"=>"1. ABA/discrete trial/Lovaas intensive early intervention", "2_occ_therapy"=>"2. Occupational therapy", "3_physical_therapy"=>"3. Physical therapy", "4_speech_therapy"=>"4. Speech therapy", "5_counseling_child"=>"5. Counseling/psychological services for child", "6_play_therapy"=>"6. Play therapy", "7_music_therapy"=>"7. Music therapy", "8_auditory_training"=>"8. Auditory integration training", "9_teacch"=>"9. TEACCH", "10_developmental_play_therapy"=>"10. Developmental play therapy (Hanen, RDI)", "11_social_skills_training"=>"11. Social skills training", "12_special_ed"=>"12. Special education", "13_parent_child_socialization"=>"13. Parent-Child socialization/skill building support", "14_recreational_sports"=>"14. Recreational sports for child", "15_typical_class"=>"15. Typical class", "16_home_program"=>"16. Home program (not ABA)", "17_nutritional"=>"17. Nutritional", "18_parenting_class"=>"18. Parenting class/seminar", "19_counseling_parent"=>"19. Counseling/psychologial services for parent", "20_parent_child_recreation"=>"20. Parent-Child recreation", "21_other"=>"21. Other (e.g. biomedical)","none"=>"22. None", "not_answered"=>"Not Answered"));
			$this->addTextElement("other_therapy$i", $this->indent . $this->indent . "If you selected other, please specify:");
			$this->addNumericElement("agetx$i", $this->indent . "$i. Age of SIB (months)");
			$this->addNumericElement("durationtx$i", $this->indent . "$i. Duration of Tx (months)");
			$this->form->addElement("select", "effectivenesstx$i", $this->indent . "$i. Was Tx effective?", array(NULL=>"", "yes"=>"Yes", "no"=>"No", "ongoing"=>"Ongoing", "unknown"=>"Unknown"));
			$this->addTextAreaElement("therapy_notes$i", $this->indent . "$i. Notes");
			$this->form->addElement("static", null, '<br />');
			$this->XINRegisterRule("therapy$i", array("therapy$i{@}=={@}NEVER_REQUIRED"));
			$this->XINRegisterRule("other_therapy$i", array("therapy$i{@}=={@}21_other"), "If you selected other therapy, please specify", "other_therapy{$i}_group");
			$this->XINRegisterRule("agetx$i", array("therapy$i{@}!={@}NULL", "therapy$i{@}!={@}not_answered"), "You must specify age", "agetx{$i}_group");
			$this->XINRegisterRule("durationtx$i", array("therapy$i{@}!={@}NULL", "therapy$i{@}!={@}not_answered"), "You must specify duration", "durationtx{$i}_group");
			$this->XINRegisterRule("effectivenesstx$i", array("therapy$i{@}!={@}NULL", "therapy$i{@}!={@}not_answered"), "You must specify effectiveness");
			$this->XINRegisterRule("therapy_notes$i", array("therapy$i{@}!={@}NULL", "therapy$i{@}!={@}not_answered"), "You must specify", "therapy_notes{$i}_group");
		}
	}

        function _page4() {

		$this->form->addElement("header", null, "FOR RESEARCH STAFF TO COMPLETE");
		$this->form->addElement("static", null, '<br />');
		$this->form->addElement("static", null, "Exclusion/Inclusion");
		$this->form->addElement("select", "exc_inc_meets_criteria", "1. This proband meets any of the medical or neurological exclusion criteria for this study. (see Section A)", $this->yesNo);
		$this->form->addElement("select", "exc_inc_subject_meets_criteria", "2. This subject meets any of the medical or neurological exclusion criteria for this study. (see Section B)", $this->yesNo);
		$this->form->addElement("select", "exc_inc_contraindication", "3. This subject has evidence for contraindication to MRI. (see Section B)", $this->yesNo);
	/*
        $this->form->addElement("static", null, '<br />');
		$this->form->addElement("static", null, "Disposition");
		$this->form->addElement("select", "disposition", "Proceed to next level beyond screening?", $this->yesNo);
     */
        }
     
     function score() {
            $db =& Database::singleton();

            // Get the item scores
            $record= $db->pselectRow("SELECT * FROM $this->table WHERE CommentID=:cid", array('cid'=>$this->getCommentID()));
            $score = array();

            if($record['relative_mr'] == 'yes' || $record['relative_schizophrenia']== 'yes'
                    || $record['relative_bipolar']=='yes' || $record['relative_psychosis']== 'yes')  {
                $score['relative_with_disorder'] = 'yes';
            } else {
                $score['relative_with_disorder'] = 'no';
            }
            $result = $db->update($this->table, $score, array('CommentID'=>$this->getCommentID()));
        }


}
?>
