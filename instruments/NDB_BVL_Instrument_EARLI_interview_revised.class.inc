<?php

require_once 'HTML/QuickForm.php';
require_once 'HTML/QuickForm/Renderer/Array.php';
require_once("RequiredIfGroup.inc");
require_once('RequiredIf.inc');
require_once('NDB_BVL_Instrument_EARLI_interview.class.inc');

class NDB_BVL_Instrument_EARLI_interview_revised extends NDB_BVL_Instrument_EARLI_interview {


	var $dateOptions2007 = array(
                'language' => 'en',
                'format'   => 'YMd',
                'minYear'  =>  '2007', //$config->getSetting('startYear')
                'maxYear'  => '2017', //$config->getSetting('endYear'),
                'addEmptyOption' => true,
                'emptyOptionValue' => null);
	

	//arrays
	var $yesNo = array(null => "", '01_yes' => "Yes", '02' => "No", '88_refused' => "88 Refused", '99_dont_know'=> "99 Don't know", 'not_answered' => "Not Answered" );

	var $months = array(NULL=>"", "Jan"=>"Jan", "Feb"=>"Feb", "Mar"=>"Mar", "Apr"=>"Apr", "May"=>"May", "Jun"=>"Jun", "Jul"=>"Jul", "Aug"=>"Aug", "Sept"=>"Sept", "Oct"=>"Oct", "Nov"=>"Nov", "Dec"=>"Dec", "88_refused"=>"88 Refused", "99_Do_not_know"=>"99 Do not know", "not_answered"=>"Not Answered");

	var $years = array();



	function setup($commentID, $page)
	{

		$this->formType="XIN";
		$this->form = new HTML_Quickform('test_form');
		$this->page = $page;            // page label (number or string - used by user-defined child classes)

		// set the object properties
		$this->testName = "EARLI_interview_revised";           // test_names.Test_name
		$this->table = 'EARLI_interview_revised';              // name of table containing data keyed by commentID
		$this->commentID = $commentID;
		$this->requiredElements = array('interview_time', 'q8_1_1_job', 'q8_2_a', 'q8_3_a_company', 'interview_end_date'); 

		//The array of dates/timestamps to convert to database dates/timestamps
		$this->dateTimeFields=array("interview_date", "interview_end_date");

		//GLOBAL DEFINITIONS

               $config =& NDB_Config::singleton();
                $this->dateOptions = array(
                'language' => 'en',
                'format'   => 'YMd',
                'minYear'  => $config->getSetting('startYear'), //allows for proband siblings up to 20 years older than candidate
                'maxYear'  => $config->getSetting('endYear'),
                'addEmptyOption' => true,
                'emptyOptionValue' => null
                );

       /* Commenting out, this will be inherited from base class
        $this->_doubleDataEntryDiffIgnoreColumns = array('CommentID', 'UserID', 'Testdate',
                                                         'Window_Difference', 'Candidate_Age',
                                                         'Data_entry_completion_status'                                                                                             );
		*/
        // setup the form
		$this->_setupForm();
				        
		$this->localDefaults = array();

//		$this->_selectMultipleElements = array();


		//column headers
		//Usually this appears at the beginning of the file in the setup() function
		$this->localDefaults = array_merge($this->localDefaults, array("hour_header"=>"TIME", "AMPM_header"=>"AM / PM", "month_names_header" => "MONTH", "year_header"=>"YEAR", "month_header"=>"MONTH #", "freq_header"=>"FREQ"));


	}


	/**
    	* method to build the HTML_Quickform object into a paged form
	* @return void
   	* @access private
    	*/

	function _setupForm()
	{

		// Mr. Samir's Rule
		// Register the RequiredIf quickform rule
		$this->form->registerRule('requiredIfGroup', null, 'HTML_QuickForm_Rule_RequiredIfGroup', 'RequiredIfGroup.inc');
		$this->form->registerRule('requiredIf', null, 'HTML_QuickForm_Rule_RequiredIf', 'RequiredIf.inc');

		//Defines the call back function for HTML Quickform to use when validating the form.
		//XIN rule is applied to every single field in the form
		$this->form->addFormRule(array(&$this,'XINValidate'));

		if(preg_match("/EARLI_interview(_page[0-9]+)_revised/", $this->page, $matches))
		{
			call_user_method($matches[1], $this);
		}	

		else
		{
			$this->_main();
		}	
	}


	function _main()
	{

		// display test name
		$this->form->addElement('header', 'instrument_title', "EARLI Maternal Interview Section 8 (revised)");

		// add examiner & date of administration
		//$this->_addMetadataFields();

		$this->form->addElement('static', null, '<br /><br />');
		

		//Setup
		$this->addTextAreaElement('mother_id', "Mother's study ID no:");
		$this->addTextAreaElement('interviewer', "<br />Interviewer:");
	 	$this->addDateElement('interview_date', "<br />Start date:", $this->dateOptions2007);
		
		$group[] =&$this->form->createElement("static", "hour_header");
                $group[] =&$this->form->createElement("static", "AMPM_header");
                $this->form->addGroup($group, "interview_start_time_headers", "", $this->_GUIDelimiter, false);
                unset($group);

		$group[] = &$this->form->createElement('select', 'interview_time', null, array(NULL=>"") + array_combine(range(1,12), range(1,12)) + array("not_answered"=>"Not Answered"));
		$group[] = &$this->form->createElement('select', 'AMPM_top', null, array(NULL=>"", "AM"=>"AM", "PM"=>"PM", "not_answered"=>"Not Answered"));
		$this->form->addGroup($group, "interview_start_time", "<br />Start time:", $this->_GUIDelimiter, false);
                unset($group);
		$this->XINRegisterRule("interview_time", array("interivew_date{@}!={@}NULL"), "Required", "interview_start_time");
		$this->XINRegisterRule("AMPM_top", array("interivew_date{@}!={@}NULL"), "Required", "interview_start_time");
		$this->form->addElement('static', null, '<br /><br />');


		// Mr. Samir's Rule
		// Register the RequiredIf quickform rule
		$this->form->registerRule('requiredIfGroup', null, 'HTML_QuickForm_Rule_RequiredIfGroup', 'RequiredIfGroup.inc');
		$this->form->registerRule('requiredIf', null, 'HTML_QuickForm_Rule_RequiredIf', 'RequiredIf.inc');

	}



	function _page23(){   // ========================================================


		$this->form->addElement('header', null, "Section 8. Occupational/Hobby Exposures (Sibling Pregnancy)");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b>Now I am going to ask you about jobs you have had starting 6 months before your new baby was conceived until today.");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-1 To the best of your ability, please tell us about each job or occupation you held for at least 1 month in the US or elsewhere while you were pregnant with [SIBLING]. Include full-time, seasonal work, part-time, volunteer work and military service if you worked the cumulative equivalent of 1 month or more. Include the last job that you held while pregnant with [SIBLING], even if you have had this for less than 1 month; begin with that job and continue back. Please estimate the time period if you cannot remember exact dates. (Attach additional pages if needed.)");
		
		$years = array(NULL=>"") + array_combine(range(1970,2017), range(1970, 2017)) + array("88_refused"=>"88 Refused", "99_Do_not_know"=>"99 Do not know", "not_answered"=>"Not Answered");

		for ($i=1; $i<7; $i++)
		{
			$this->addTextAreaElementRD("q8_1_{$i}_job", "<b>Job title #{$i}</b>");
			$this->XINRegisterRule("q8_1_{$i}_job", array("q8_1_{$i}_job{@}=={@}NEVER_REQUIRED"), "q8_1_{$i}_job_group");
	
			//job start date
	                $group[] =&$this->form->createElement("static", "month_names_header");
        	        $group[] =&$this->form->createElement("static", "year_header");
                	$this->form->addGroup($group, "q8_1_{$i}_job_start_headers", "", $this->_GUIDelimiter, false);
                	unset($group);

                	$group[] = &$this->form->createElement('select', "q8_1_{$i}_job_start_month", null, $this->months);
                	$group[] = &$this->form->createElement('select', "q8_1_{$i}_job_start_year", null, $years); 
                	$this->form->addGroup($group, "q8_1_{$i}_job_start", "<br />Start date:", $this->_GUIDelimiter, false);
			$this->XINRegisterRule("q8_1_{$i}_job_start_month", array("q8_1_{$i}_job_status{@}=={@}", "q8_1_{$i}_job{@}!={@}"), "You must specify time span", "q8_1_{$i}_job_start"); 
			$this->XINRegisterRule("q8_1_{$i}_job_start_year", array("q8_1_{$i}_job_status{@}=={@}", "q8_1_{$i}_job{@}!={@}", "q8_1_{$i}_job_start_month{@}!={@}"), "You must specify time span", "q8_1_{$i}_job_start"); 
                	unset($group);
                	$this->form->addElement('static', null, '<br /><br />');
			
	
			//job end date
                        $group[] =&$this->form->createElement("static", "month_names_header");
                        $group[] =&$this->form->createElement("static", "year_header");
                        $this->form->addGroup($group, "q8_1_{$i}_job_end_headers", "", $this->_GUIDelimiter, false);
                        unset($group);

                        $group[] = &$this->form->createElement('select', "q8_1_{$i}_job_end_month", null, $this->months); 
                        $group[] = &$this->form->createElement('select', "q8_1_{$i}_job_end_year", null, $years); 
                        $this->form->addGroup($group, "q8_1_{$i}_job_end", "<br />End date:", $this->_GUIDelimiter, false);         
			$this->XINRegisterRule("q8_1_{$i}_job_end_month", array("q8_1_{$i}_job_status{@}=={@}", "q8_1_{$i}_job{@}!={@}"), "You must specify time span", "q8_1_{$i}_job_end"); 
			$this->XINRegisterRule("q8_1_{$i}_job_end_year", array("q8_1_{$i}_job_status{@}=={@}", "q8_1_{$i}_job{@}!={@}"), "You must specify time span", "q8_1_{$i}_job_end"); 
			unset($group);
                        $this->form->addElement('static', null, '<br /><br />');

			$this->addNumericElementRD("q8_1_{$i}_hrs", "Average hours/week");
			$this->XINRegisterRule("q8_1_{$i}_hrs", array("q8_1_{$i}_job{@}!={@}", "q8_1_{$i}_job_status{@}=={@}"), "You must specify number of hours", "q8_1_{$i}_hrs_group");

			$this->addTextAreaElementRD("q8_1_{$i}_task", "Main job tasks");
			$this->XINRegisterRule("q8_1_{$i}_task", array("q8_1_{$i}_job_status{@}=={@}", "q8_1_{$i}_job{@}!={@}"), "You must specify tasks performed", "q8_1_{$i}_task_group");

			$this->addTextAreaElementRD("q8_1_{$i}_tools", "What machines, tools and materials did you use on the job?");
			$this->XINRegisterRule("q8_1_{$i}_tools", array("q8_1_{$i}_job_status{@}=={@}", "q8_1_{$i}_job{@}!={@}"), "You must specify machines, tools and materials", "q8_1_{$i}_tools_group");

			$this->addTextAreaElementRD("q8_1_{$i}_company", "Company name");
			$this->XINRegisterRule("q8_1_{$i}_company", array("q8_1_{$i}_job_status{@}=={@}", "q8_1_{$i}_job{@}!={@}"), "You must specify company name", "q8_1_{$i}_company_group");

			$this->addTextAreaElementRD("q8_1_{$i}_site", "What did your company do at that site?");
			$this->XINRegisterRule("q8_1_{$i}_site", array("q8_1_{$i}_job_status{@}=={@}", "q8_1_{$i}_job{@}!={@}"), "You must specify company activities", "q8_1_{$i}_site_group");

                        $this->form->addElement('static', null, '<br /><br />');
                        $this->form->addElement('static', null, '<br /><br />');
		}


	} //end function _page23() ==========================================================================================



	function _page24() {


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-2 While you were pregnant with sibling, did you perform any of the following tasks or activities as part of your normal duties?");

		$tasks = array("a"=>"a. Welding", "b"=>"b. Painting", "c"=>"c. Degreasing parts or equipment", "d"=>"d. Working with glues", "e"=>"e. Working where pesticides were used", "f"=>"f. Sandblasting", "g"=>"g. Working with or near diesel-powered equipment", "h"=>"h. Working with or around live animals", "i"=>"i. Industrial firefighting", "j"=>"j. Volunteer firefighting - Urban", "k"=>"k. Volunteer firefighting - Rural", "l"=>"l. Volunteer firefighting - Forest", "m"=>"m. Working with X-ray or radioactive material", "n"=>"n. Working at temperatures more than 100F (hot)", "o"=>"o. Working at temperatures less than 32F (cold)", "p"=>"p. Working with noisy machines/tools", "q"=>"q. Working with vibrating machines/tools", "r"=>"r. Standing for more than half of workday", "s"=>"s. Work outdoors for more than half of workday");


		foreach ($tasks as $field=>$label)
		{
			$this->form->addElement("select", "q8_2_{$field}", "{$label}:", $this->yesNo);
			$this->addTextAreaElementRD("q8_2_{$field}_jobs", $this->indent . "In which of your jobs did you perform this task? List all <i>job numbers</i> that apply");
			$this->XINRegisterRule("q8_2_{$field}_jobs", array("q8_2_{$field}{@}=={@}01_yes"), "You must specify jobs for this task", "q8_2_{$field}_jobs_group");
			$this->form->addElement('static', null, "<br/>");
		}
	
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

	} //end function _page24() ===============================================================================




	function _page25() {


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-3 Please describe any gaps in your work history while you were pregnant with [SIBLING], that have not been captured. Do include any periods of 1 week or more of absence from work, such as absences for education, illness, paternity leave, vacation, care giving (i.e. child or elder care), unemployment or retirement");

		$options = array("a"=>"a", "b"=>"b", "c"=>"c", "d"=>"d");

		$years = array(NULL=>"") + array_combine(range(1970, 2017), range(1970, 2017)) + array("88_refused"=>"88 Refused", "99_Do_not_know"=>"99 Do not know", "not_answered"=>"Not Answered");

		foreach ($options as $field=>$label)
		{
                        $group[] =&$this->form->createElement("static", "month_names_header");
                        $group[] =&$this->form->createElement("static", "year_header");
                        $this->form->addGroup($group, "q8_3_{$field}_job_gap_headers", "", $this->_GUIDelimiter, false);
                        unset($group);

                        $group[] = &$this->form->createElement('select', "q8_3_{$field}_gap_month", null, $this->months);
                        $group[] = &$this->form->createElement('select', "q8_3_{$field}_gap_year", null, $years);
                        $this->form->addGroup($group, "q8_3_{$field}_gap", "<br />{$label}. Date started (Mo/Yr)", $this->_GUIDelimiter, false); 
			unset($group); 


			$this->XINRegisterRule("q8_3_{$field}_gap_month", array("q8_3_{$field}_gap_month{@}=={@}NEVER_REQUIRED"), "q8_3_{$field}_gap"); 
			$this->XINRegisterRule("q8_3_{$field}_gap_year", array("q8_3_{$field}_gap_year{@}=={@}NEVER_REQUIRED"), "q8_3_{$field}_gap"); 

			$this->addTextAreaElementRD("q8_3_{$field}_company", $this->indent . "How long?");
			$this->XINRegisterRule("q8_3_{$field}_company", array("q8_3_{$field}_gap_month{@}!={@}", "q8_3_{$field}_gap_year{@}!={@}"), "You must specify length", "q8_3_{$field}_company_group");
			$this->addTextAreaElementRD("q8_3_{$field}_reason", $this->indent . "What was the reason for the gap or absence?");
			$this->XINRegisterRule("q8_3_{$field}_reason", array("q8_3_{$field}_gap_month{@}!={@}", "q8_3_{$field}_gap_year{@}!={@}"), "You must specify reason", "q8_3_{$field}_reason_group");
			$this->form->addElement('static', null, "<br/>");
		}

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


	} //end function _page25() =====================================================



	function _page26(){   // ========================================================
		

		$timeOptions = array_combine(range(1,12), range(1,12));

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('header', 'end_instrument', "End of EARLI Interview Section 8 (revised)");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

		//interview end date
		$this->addDateElement('interview_end_date', "Interview end date:", $this->dateOptions2007);
		$this->form->addElement('static', null, "<br/>");


		//interview end time
                $group[] =&$this->form->createElement("static", "hour_header");
                $group[] =&$this->form->createElement("static", "AMPM_header");
                $this->form->addGroup($group, "interview_end_time_headers", "", $this->_GUIDelimiter, false);
                unset($group);

		$group[] = &$this->form->createElement('select', 'interview_end_time', "", array(NULL=>"") + ($timeOptions) + array("not_answered"=>"Not Answered"));
		$group[] = &$this->form->createElement('select', 'AMPM_bottom', "", array(NULL=>"", "AM"=>"AM", "PM"=>"PM", "not_answered"=>"Not Answered"));
		$this->form->addGroup($group, "interview_end_time_group", "Interview end time:", $this->_GUIDelimiter, false);
                unset($group);
		$this->form->addElement('static', null, "<br/>");

                $this->XINRegisterRule("interview_end_time", array("interivew_end_date{@}!={@}NULL"), "Required", "interview_end_time_group");
                $this->XINRegisterRule("AMPM_bottom", array("interivew_end_date{@}!={@}NULL"), "Required", "interview_start_time_group");


		//interviewer notes
		$this->addTextAreaElement('interviewer_notes', "Interviewer's notes");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

	} //end function _page26() =======================================================


} //end EARLI Maternal Interview part 3 =================================================

?>
