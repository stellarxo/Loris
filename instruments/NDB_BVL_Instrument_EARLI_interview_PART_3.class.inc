<?php

require_once 'HTML/QuickForm.php';
require_once 'HTML/QuickForm/Renderer/Array.php';
require_once("RequiredIfGroup.inc");
require_once('RequiredIf.inc');
require_once('NDB_BVL_Instrument_EARLI_interview.class.inc');

class NDB_BVL_Instrument_EARLI_interview_PART_3 extends NDB_BVL_Instrument_EARLI_interview {


	var $dateOptions = array(
                'language' => 'en',
                'format'   => 'YMd',
                'minYear'  =>  '2007', //$config->getSetting('startYear'),
                'maxYear'  => '2017', //$config->getSetting('endYear'),
                'addEmptyOption' => true,
                'emptyOptionValue' => null);
	
		
	//number arrays
	var $yesNo = array(null => "", '01_yes' => "Yes", '02' => "No", '88_refused' => "88 Refused", '99_dont_know'=> "99 Don't know", 'not_answered' => "Not Answered" );


	//other misc. arrays
	var $ventilators = array("a"=>"a) A general ventilator system, meaning open doors or windows, use fan, etc.", "b"=>"b) A regular HVAC system for the building and room heating and cooling", "c"=>"c) A fume hood, lab hood, or other partially enclosed equipment", "d"=>"d) A glove box or other totally enclosed equipment", "e"=>"e) A portable exhaust hose or tube, such as those used for welding or to attach to vehicle tailpipe",  "f"=>"f) Some other type of ventilation system");

	var $adhesives = array("a"=>"a) Hot melt glues or adhesives", "b"=>"b) Contact adhesives, such as rubber cement", "c"=>"c) Water-based adhesives, such as vinyl or acrylic resins", "d"=>"d) Wood laminates", "e"=>"e) Something else");

	var $protectiveEquipment = array("a"=>"a) Gloves", "b"=>"b) Overalls", "c"=>"c) Overcoat (e.g. lab coat, smoke, apron)", "d"=>"d) Dust mask", "e"=>"e) Respirator", "f"=>"f) Goggles or safety glasses", "g"=>"g) Work boots/shoes", "h"=>"h) Other");


	/**
    * sets up basic data, such as  *
    * @param string $commentID  the CommentID identifying the data to load
    * @param string $page       if a multipage form, the page to show
    * @return void
    * @access public
    */
	function setup($commentID, $page)
	{

		$this->formType="XIN";
		$this->form = new HTML_Quickform('test_form');
		$this->page = $page;            // page label (number or string - used by user-defined child classes)

		// set the object properties
		$this->testName = "EARLI_interview_PART_3";           // test_names.Test_name
		$this->table = 'EARLI_interview_PART_3';              // name of table containing data keyed by commentID
		$this->commentID = $commentID;
		$this->requiredElements = array('interview_time', 'q8_1', 'q8_21', 'q8_41', 'q8_76', 'q8_98', 'q8_127_a', 'q8_152_a'); 
          
 /*Commenting out, this will be inherited from base class
        $this->_doubleDataEntryDiffIgnoreColumns = array('CommentID', 'UserID', 'Testdate',
                                                         'Window_Difference', 'Candidate_Age',
                                                         'Data_entry_completion_status'
                                                         );
   */   
		//The array of dates/timestamps to convert to database dates/timestamps
		$this->dateTimeFields=array("interview_date");

		//GLOBAL DEFINITIONS
		
		// setup the form
		$this->_setupForm();
				        
		$this->localDefaults = array();

//		$this->_selectMultipleElements = array();


		// From Mr. David Brownlee:
		//The array of selects with multiple answers allowed
		//Any HTML_Quickform multiple selects must be listed here
		//Usually this appears at the beginning of the file in the setup() function


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

		if(preg_match("/EARLI_interview(_page[0-9]+)/", $this->page, $matches))
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
		$this->form->addElement('header', 'instrument_title', "EARLI Maternal Interview Section 8 long (1)");

		// add examiner & date of administration
		//$this->_addMetadataFields();

		$this->form->addElement('static', null, '<br /><br />');
		

		//Setup
		$this->addTextAreaElement('mother_id', "Mother's study ID no:");
		$this->addTextAreaElement('interviewer', "<br />Interviewer:");
	 	$this->addDateElement('interview_date', "<br />Start date:");
		
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


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('header', null, "Section 8. Occupational/Hobby Exposures (Sibling Pregnancy)");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<b><i>Now I will ask you questions about your jobs, any volunteer work, school work, and hobbies that you may have had while you were pregnant with [SIBLING]. Please only include activities that you did for one hour a week or longer. I will begin by asking about the types of jobs you've had and whether you've been in school. Please include all jobs and school, whether the work or schooling were done at home or somewhere else.</i></b>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8-1
		$this->addNumericElementRD('q8_1', "8-1 Between [-3] and DOBS, how many full time jobs have you had?");
		$this->form->addElement('static', null, "<br/>");

		//q8-2
		$this->addNumericElementRD('q8_2', "8-2 Between [-3] and DOBS, how many part time jobs have you had?");
		$this->form->addElement('static', null, "<br/>");

		//q8-3
		$this->addNumericElementRD('q8_3', "8-3 Between [-3] and DOBS, how many volunteer jobs have you had? (e.g. hospital, fire department, humane society)");

		$this->form->addElement('static', null, "<br/>");
		$this->addNumericElementRD("sum_jobs", "<b/>A. Add responses from 8-1, 8-2, and 8-3 = _______sum of jobs");
		$this->form->addElement('static', null, "<br/>");


		//q8-4
		$this->addNumericElementRD('q8_4', "8-4 Between [-3] and DOBS, how many schools have you attended?");
		$this->form->addElement('static', null, "<br/>");

		$this->addNumericElementRD("sum_jobs_school", "<b/>B. Add responses from 8-1, 8-2, 8-3, and 8-4 = _______sum of jobs and school");
		$this->form->addElement('static', null, "<b/>If B (sum of jobs and school) = 0, go to 8-21");
		$this->form->addElement('static', null, "<b/>If A (sum of jobs) = 1, go to 8-5");
		$this->form->addElement('static', null, "<b/>If A(sum of jobs)= 0, <b>and</b> B(sum of jobs and school) >= 1, go to 8-8");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<b><i>Now I will ask you questions about each one of your jobs, starting with job where you worked the most hours</i></b>");
		$this->form->addElement('static', null, "<br/>");

		//q8-5
		$this->form->addElement("select", "q8_5", "8-5 What is your job title or occupation? (For example, teacher, secretary, nurse, clerk, maid, paralegal, or lab assistant)",  array(NULL=>"", "01" => "01 Any Health Care (Human and Animal)", "02" => "02 Education/Teaching", "03" => "03  Restaurant, Bar, or Food Service", "04" => "04 Cleaning and Building Maintenance", "05" => "05 Child Care (Pre-Kindergarten)", "06" => "06 Beautician/Barber", "07" => "07 Driver", "08" => "08 Agriculture, Farming, Landscaping, Pesticide Workers", "09" => "09 Other Industry or Business", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_5", array("sum_jobs{@}=={@}1"), "Required if sum of jobs = 1");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

		//q8-6
		$this->form->addElement('static', null, "8-6 What type of activities do you do most often at this job? (For example, teach classes, work on the computer, keep account books, file, photocopy, answer phone, wait table, help customers, do lab work, or carpentry)");
		$this->form->addElement('static', null, "<br/>");

		//q8_6_1
		$this->form->addElement("select", "q8_6_1", "ANY HEALTH CARE (HUMAN AND ANIMAL)",  array(NULL=>"", "01" => "01 Health care provider office", "02" => "02 Free-standing outpatient/ambulatory care center facility", "03" => "03  Hospital", "04" => "04 Home health care agency", "05" => "05 Skilled nursing facility/rehab facility", "06" => "06 Nursing home/assisted living", "07" => "07 Pharmacy", "08" => "08 Veterinary clinic/hospital", "09" => "09 Other health care facility or service", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_6_1", array("q8_5{@}=={@}01"), "Required if selected 01 above");
		$this->addTextAreaElementRD('q8_6_1other', $this->indent . 'If you selected [Other health care facility or service], please specify:');
		$this->XINRegisterRule("q8_6_1other", array("q8_6_1{@}=={@}09"), "You must specify other", "q8_6_1other_group");
		$this->form->addElement('static', null, "<br/>");


		//q8_6_2
		$this->form->addElement("select", "q8_6_2", "EDUCATION/TEACHING",  array(NULL=>"", "10" => "10 Elementary or middle/high school", "11" => "11 Business, technical or trade school", "12" => "12 College or university", "13" => "13 Other school/education provider", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_6_2", array("q8_5{@}=={@}02"), "Required if selected 02 above");
		$this->addTextAreaElementRD('q8_6_2other', $this->indent . 'If you selected [13 Other school/education provider], please specify:');
		$this->XINRegisterRule("q8_6_2other", array("q8_6_2{@}=={@}13"), "You must specify other", "q8_6_2other_group");
		$this->form->addElement('static', null, "<br/>");


		//q8_6_3
		$this->form->addElement("select", "q8_6_3", "RESTAURANT, BAR, OR FOOD SERVICE",  array(NULL=>"", "14"=>"14 Retail bakery (Bakery only)", "15" => "15 Grocery store bakery (Bakery in a grocery store)", "16" => "16 Restaurant, caterer or other food service", "17" => "17 Bar", "18_other" => "18 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_6_3", array("q8_5{@}=={@}03"), "Required if selected 03 above");
		$this->addTextAreaElementRD('q8_6_3other', $this->indent . 'If you selected [Other], please specify:');
		$this->XINRegisterRule("q8_6_3other", array("q8_6_3{@}=={@}18_other"), "You must specify other", "q8_6_3other_group");
		$this->form->addElement('static', null, "<br/>");


		//q8_6_4
		$this->form->addElement("select", "q8_6_4", "CLEANING AND BUILDING MAINTENANCE",  array(NULL=>"", "19" => "19 Company that cleans or maintains buildings or homes", "20" => "20 Clean or maintain a private home", "21_other" => "21 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_6_4", array("q8_5{@}=={@}04"), "Required if selected 04 above");
		$this->addTextAreaElementRD('q8_6_4other', $this->indent . 'If you selected [Other], please specify:');
		$this->XINRegisterRule("q8_6_4other", array("q8_6_4{@}=={@}21_other"), "You must specify other", "q8_6_4other_group");
		$this->form->addElement('static', null, "<br/>");


		//q8_6_5
		$this->form->addElement("select", "q8_6_5", "CHILD CARE (PRE-KINDERGARTEN)",  array(NULL=>"", "22" => "22 Child care facility", "23" => "23 Child care in caretaker's home", "24"=>"24 Child care in child's home", "25_other"=>"25 Other child care ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_6_5", array("q8_5{@}=={@}05"), "Required if selected 05 above");
		$this->addTextAreaElementRD('q8_6_5other', $this->indent . 'If [Other child care], please specify:');
		$this->XINRegisterRule("q8_6_5other", array("q8_6_5{@}=={@}25_other"), "You must specify other", "q8_6_5other_group");
		$this->form->addElement('static', null, "<br/>");


		//q8_6_6
		$this->form->addElement("select", "q8_6_6", "BEAUTICIAN/BARBER",  array(NULL=>"", "26 Barber shop", "27 Beauty shop", "28 Nail salon", "29_other"=>"29 Other beauty services", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_6_6", array("q8_5{@}=={@}06"), "Required if selected 06 above");
		$this->addTextAreaElementRD('q8_6_6other', $this->indent . 'If you selected [Other beauty services], please specify:');
		$this->XINRegisterRule("q8_6_6other", array("q8_6_6{@}=={@}29_other"), "You must specify other", "q8_6_6other_group");
		$this->form->addElement('static', null, "<br/>");


		//q8_6_7
		$this->form->addElement("select", "q8_6_7", "DRIVER",  array(NULL=>"", "30"=>"30 School bus driver", "31_other"=>"31 Other public transportation", "32"=>"32 (bus, subway, light rail, streetcar, ect.)", "33"=>"33 Taxi and limousine service", "34"=>"34 Tourism", "35"=>"35 Postal service", "36"=>"36 Couriers and messengers", "37"=>"37 Private households", "38"=>"38 Trucking", "39"=>"39 Other driving business or industry", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_6_7", array("q8_5{@}=={@}07"), "Required if selected 07 above");
		$this->addTextAreaElementRD('q8_6_7other', $this->indent . 'If you selected [Other driving business or industry], please specify:');
		$this->XINRegisterRule("q8_6_7other", array("q8_6_7{@}=={@}31_other"), "You must specify other", "q8_6_7other_group");
		$this->form->addElement('static', null, "<br/>");


		//q8_6_8
		$this->form->addElement("select", "q8_6_8", "AGRICULTURE, FARMING, LANDSCAPING, PESTICIDE WORKERS",  array(NULL=>"", "40"=>"40 Agriculture/farming-crops", "41"=>"41 Landscaping services and/or pest/control services", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_6_8", array("q8_5{@}=={@}08"), "Required if selected 08 above");
		$this->form->addElement('static', null, "<br/>");

		//q8_6_9
		$this->form->addElement("select", "q8_6_9", "OTHER INDUSTRY OR BUSINESS", array(NULL=>"", "42"=>"42 Retail sales", "43"=>"43 Wholesale", "44"=>"44 Manufacturing", "45"=>"45 Warehousing", "46"=>"46 Information and telecommunications (includes internet)", "47"=>"47 Finance, insurance, real estate, and leasing", "48"=>"48 Professional, scientific, management, administrative, social services", "49"=>"49 Arts, entertainment and recreation", "50"=>"50 Public administration", "51"=>"51 Services other than public administration", "52"=>"52 Military", "53"=>"53 Construction", "54"=>"54 Airlines", "55_other"=>"55 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_6_9", array("q8_5{@}=={@}09"), "Required if selected 09 above");
		$this->addTextAreaElementRD('q8_6_9other', $this->indent . 'If you selected [Other], please specify:');
		$this->XINRegisterRule("q8_6_9other", array("q8_6_9{@}=={@}55_other"), "You must specify other", "q8_6_9other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_7
		$this->addTextAreaElementRD("q8_7", "8-7 In what kind of business or industry is this job?");
		$this->XINRegisterRule("q8_7", array("sum_jobs{@}=={@}1"), "Required if had one job", "q8_7_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_8
		$this->form->addElement("select", "q8_8", "8-8 Now think about school, for this school/job, what best describes the place where you typically work/go to school?",  array(NULL=>"", "01" => "01 Office Area", "02" => "02 Store", "03" => "03  Classroom", "04" => "04 Hotel or Motel", "05" => "05 Restaurant", "06" => "06 Residence, such as your home or someone else's home", "07" => "07 Healthcare facility or hospital", "08" => "08 Laboratory", "09" => "09 Factory, plant or production area", "10" => "10 Warehouse", "11" => "11 Garage or shop", "12" => "12 Some other indoor location", "13" => "13 Loading dock", "14" => "14 Construction site", "15" => "15 Grounds, yard, or garden", "16" => "16 Some other outdoor location", "17" => "17 Motor vehicle", "18" => "18 Some other outdoor location", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered")); 		
		$this->XINRegisterRule("q8_8", array("sum_jobs{@}=={@}0", "sum_jobs_school{@}>={@}1"), "Required if sum of jobs = 0 and sum of jobs and school >= 1");
		$this->form->addElement('static', null, "<br/>");
		$this->addTextAreaElementRD('q8_8other1', $this->indent . 'If you selected [12 Some other indoor location], please specify:');
		$this->addTextAreaElementRD('q8_8other2', $this->indent . 'If you selected [16 Some other outdoor location], please specify:');
		$this->XINRegisterRule("q8_8other1", array("q8_8{@}=={@}12"), "You must specify other indoor location", "q8_8other1_group");
		$this->XINRegisterRule("q8_8other2", array("q8_8{@}=={@}16"), "You must specify other outdoor location", "q8_8other1_group");
		$this->form->addElement('static', null, "<br/>");

//		$this->addTextAreaElementRD('q8_8other3', $this->indent . 'If you selected [18 Some other outdoor location], please specify:');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_9
		$this->form->addElement('static', null, "8-9 How long have you been at this job/attending this school?");
		$this->XINRegisterRule("q8_9", array("sum_jobs{@}=={@}0", "sum_jobs_school{@}>={@}1"), "Required if sum of schools is at least 1");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q8_9", $this->indent . "Choose from following:",  array(NULL=>"", "Years" => "Years", "Months" => "Months", "Weeks" => "Weeks", "Days" => "Days", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->addTextAreaElementRD('q8_9_specify', $this->indent . "If you selected [Years], [Months], [Weeks] or [Days], specify the time:");
		$this->XINRegisterRule("q8_9_specify", array("q8_9{@}=={@}Years|Months|Weeks|Days"), "You must specify the time", "q8_9specify_group");
		$this->form->addElement('static', null, "<br/>");


		//q8_10
		$this->form->addElement('select', 'q8_10', "8-10 What is the address that you actually work at this job/attend school? Enter address below or select one of the following:", array(NULL=>"", "01" => "01 Home", "02" => "02 Varies (Construction, Landscaping)", "03" => "03  Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_10", array("sum_jobs_school{@}>={@}1"), "Required if number of schools is at least 1");
		$this->addTextAreaElementRD('q8_10_address', $this->indent . "Address:");
		$this->addTextAreaElementRD('q8_10_other', $this->indent . 'If you selected [Other], please specify:');
		$this->XINRegisterRule("q8_10_address", array("q8_10_address{@}=={@}NEVER_REQUIRED"), "q8_10_address_group");
		$this->XINRegisterRule("q8_10_other", array("q8_10{@}=={@}03_other"), "You must specify other", "q8_10_other_group");
		$this->form->addElement('static', null, "");
		$this->form->addElement('static', null, "<br/>");


		//q8_11
		$this->form->addElement('static', null, "8-11 Between [-3] and DOBS, what days of the week did you usually work at this job/go to school? What time do you usually finish work/school on (day)?");
		$this->form->addElement('static', null, "<br/>");

		$mToF = array("Monday"=>"Monday", "Tuesday"=>"Tuesday", "Wednesday"=>"Wednesday", "Thursday"=>"Thursday", "Friday"=>"Friday",  "Saturday"=>"Saturday",  "Sunday"=>"Sunday");
		reset($mToF);

		while(list($field, $label) = each($mToF)){

			$this->form->addElement("select", "q8_11{$field}", "{$label}:",  array(NULL=>"", "01_work"=>"1 Work Day", "02_not_work"=>"2 Not Work Day", "88_Refused" => "88 Refused", "99_Do_Not_Know" => "99 Don't know", "Not_Answered" => "Not Answered"));
			$this->XINRegisterRule("q8_11_{$field}", array("sum_jobs{@}=={@}0", "sum_jobs_school{@}>={@}1"), "Required if number of schools is at least 1");

			$this->addTextAreaElementRD("q8_11_start{$field}", $this->indent . 'Start time:');
			$this->addTextAreaElementRD("q8_11_end{$field}", $this->indent . 'End time:');
			$this->form->addElement('static', null, "<br/>");
			$this->XINRegisterRule("q8_11_start{$field}", array("q8_11{$field}{@}=={@}01_work"), "You must specify start time", "q8_11_start{$field}_group");
			$this->XINRegisterRule("q8_11_end{$field}", array("q8_11{$field}{@}=={@}01_work"), "You must specify end time", "q8_11_end{$field}_group");
		}

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_12
		$this->form->addElement("select", "q8_12", "8-12 Was your drinking water source at this work/school usually...",  array(NULL=>"", "01" => "01 Tap water", "02" => "02 Filtered tap water", "03" => "03  Bottled water", "04" => "04 Some other source?", "05" => "05 Don't drink water at work", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_12", array("sum_jobs_school{@}>={@}1"), "Required if number of schools is at least 1");
		$this->addTextAreaElementRD('q8_12_other', $this->indent . 'If you selected [Some other source], please specify:');
		$this->XINRegisterRule("q8_12_other", array("q8_12{@}=={@}04_other"), "You must specify other source", "q8_12_other_group");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Occupational Coding Box");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "-> If 8-5 coded [01] and 8-6 coded [01] - [25] OR [30] - [55], go to the Health Professional Module (8-127)");
		$this->form->addElement('static', null, "-> If 8-5 coded [01] and 8-6 coded [26]-[29], go to the Beautician/Barber Module then go to 8-291");
		$this->form->addElement('static', null, "-> If 8-5 coded [02] and 8-6 coded [01]-[21] or [26] - [55], go to the Teacher Module then go to 8-152");
		$this->form->addElement('static', null, "-> If 8-5 coded [02] and 8-6 coded [22]-[25], go to the Childcare Worker Module then go to 8-273");
		$this->form->addElement('static', null, "-> If 8-5 coded [03], go to the Restaurant Worker Module, then  go to 8-196");
		$this->form->addElement('static', null, "-> If 8-5 coded [04], go to the Cleaners and Building Maintenance Module, then go to 8-211");
		$this->form->addElement('static', null, "-> If 8-5 coded [05] and 8-6 coded [01]-[21] OR [26] - [55], go to the Childcare Worker Module then go to 8-273");

		$this->form->addElement('static', null, "-> If 8-5 coded [05] and 8-6 coded [22]-[25], go to the Teacher Module, then go to 8-152");
		$this->form->addElement('static', null, "-> If 8-5 coded [06], go to the Beautician/Barber Module, then go to 8-291");
		$this->form->addElement('static', null, "-> If 8-5 coded [07], go to the Driver Module (8-308)");
		$this->form->addElement('static', null, "-> If 8-5 coded [08], go to the Agricultural Module, then go to starts at 8-321");
		$this->form->addElement('static', null, "-> If 8-5 coded [09] and 8-6 coded [01] - [09], go to the Health Professional Module then go to 8-127");
		$this->form->addElement('static', null, "-> If 8-5 coded [09] and 8-6 coded [10]- [13], go to the Teacher Module then go to 8-152");
		$this->form->addElement('static', null, "-> If 8-5 coded [09] and 8-6 coded [14] - [18], go to the Restaurant Worker Module then go to 8-196");
		$this->form->addElement('static', null, "-> If 8-5 coded [09] and 8-6 coded [19] -[21], go to the Cleaners and Building Maintenance Module (8-211)");
		$this->form->addElement('static', null, "-> If 8-5 coded [09] and 8-6 coded [22] - [25], go to the Childcare Worker Module then go to 8-273");
		$this->form->addElement('static', null, "-> If 8-5 coded [09] and 8-6 coded [26]- [29], go to the Beautician/Barber Module then go to8-291");
		$this->form->addElement('static', null, "-> If 8-5 coded [09] and 8-6 coded [30] - [39], go to the Driver Module (8-308)");
		$this->form->addElement('static', null, "-> If 8-5 coded [09] and 8-6 coded [40] - [41], go to the Agricultural Module (starts at 8-321)");
		$this->form->addElement('static', null, "-> If 8-5 coded [09] and 8-6 coded [42]- [55], go to the Generic Exposure Module (starts at 8-98)");
		$this->form->addElement('static', null, "-> Otherwise, go to the Generic Exposure Module (starts at 8-98)");
		$this->form->addElement('static', null, "-> When complete, continue with 8-13");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<i>If more than one occupation listed in A. use <b>Occupational Insert forms (questions 8-5 to 8-12)</b> and each related <b>Occupational Module</b> listed in the <b>Occupational Coding Box</b> and label as OCCUPATION 2 OCCUPATION 3 OCCUPATION 4 etc.");
		$this->form->addElement('static', null, "<br/>");


		//q8_13
		$this->form->addElement("select", "q8_13", "8-13 Between [-3] and DOBS, have you used or worked around any chemicals, dust or fumes, radiation, bacteria, or viruses that we have not yet talked about for this job/school?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_13", array("sum_jobs_school{@}>={@}1"), "Required if number of schools is at least 1");
		$this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to BOX A");
		$this->form->addElement('static', null, "<br/>");


		//q8_14
		$this->addTextAreaElementRD('q8_14', "8-14 Can you name those chemicals, dust, radiation, bacteria or viruses?"); 
		$this->XINRegisterRule("q8_14", array("q8_13{@}=={@}01_yes"), "You must specify", "q8_14_group");
		$this->form->addElement('static', null, "<br/>");


		//q8_15
		$this->addTextAreaElementRD('q8_15', "8-15 Please describe your contact with those chemicals, dusts,radiation, bacteria, or viruses.");
		$this->XINRegisterRule("q8_15", array("q8_13{@}=={@}01_yes"), "You must describe", "q8_15_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<b><i>Now thinking of the chemicals, dust or fumes, radiation, bacteria, or virus that you mentioned...</i></b>");
		$this->form->addElement('static', null, "<br/>");


		//q8_16
		$this->form->addElement("select", "q8_16", "8-16 Between [-3] and DOBS, how often did you wear or use personal protective equipment (PPE) to protect you from the things you have mentioned?",  array(NULL=>"", "01" => "01 Always", "02" => "02 Often", "03" => "03  Rarely", "04" => "04 Never", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_16", array("q8_13{@}=={@}01_yes"), "You must specify");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<i>Probe: By personal protective equipment, I mean things like gloves, dust masks, goggles, aprons, lab coats or other protective clothing.</i>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If you selected [Never], [Refused] or [Don't Know] skip to BOX A");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_17
		$this->form->addElement('static', null, "8-17 Which type of protective clothing or equipment have you worn? Code all that apply.");
		$this->form->addElement('static', null, "<i>PROBE: Any other protective clothing or equipment?</i>");
		$this->form->addElement('static', null, "<br/>");

		foreach($this->protectiveEquipment as $field=>$label)
		{
			$this->form->addElement("select", "q8_17_{$field}", "{$label}:",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_17_{$field}", array("q8_16{@}=={@}01|02|03"), "You must specify");
		}


		$this->addTextAreaElementRD('q8_17_other', $this->indent . 'If you selected [Yes] for [g) Other], please specify:');
		$this->XINRegisterRule("q8_17_other", array("q8_17_g{@}=={@}01_yes"), "You must specify other", "q8_17_other_group");
		$this->form->addElement('static', null, $this->indent . "If you selected [Yes] for any protective clothing in a-g, go to question 8-19");
		$this->form->addElement('static', null, $this->indent . "If you selected [Yes] for [h) Respirator], go to question 8-18");
		$this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] for <u>all</u>, skip to question 8-19");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_18
		$this->form->addElement("select", "q8_18", "8-18 What type of respirator was it?",  array(NULL=>"", "01" => "01 A half-mask chemical cartridge respirator", "02" => "02 A full-mask chemical cartridge respirator", "03" => "03  An air-supplied or SCBA respirator", "04" => "04 Some other kind of respirator?", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_18", array("q8_17_e{@}=={@}01_yes"), "You must specify respirator");
		$this->addTextAreaElementRD('q8_18other', $this->indent . 'If you selected [Some other kind of respirator], please specify:');
		$this->XINRegisterRule("q8_18other", array("q8_18{@}=={@}04"), "You must specify other respirator", "q8_18other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_19
		$this->form->addElement("select", "q8_19", "8-19 Was there any kind of a ventilation system to remove exhaust, dust, smoke or fumes from the area?", $this->yesNo);
		$this->XINRegisterRule("q8_19", array("q8_16{@}=={@}01|02|03"), "Required if used personal protective equipment");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<i>Probe: By ventilation system we mean purposely opening windows or doors, using a fume hood, or other ventilation system.</i>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to BOX A");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_20
		$this->form->addElement('static', null, "8-20 What ventilation systems are present to remove exhaust, dust, smoke or fumes from the area? Is there...Code all that apply.");
		$this->form->addElement('static', null, "<br/>");

		foreach($this->ventilators as $field=>$label)
		{
			$this->form->addElement("select", "q8_20_{$field}", "{$label}:", $this->yesNo); 
			$this->XINRegisterRule("q8_20_{$field}", array("q8_19{@}=={@}01_yes"), "You must specify ventilation system(s)");
		}

		$this->addTextAreaElementRD('q8_20_other', $this->indent . 'Please specify:');
		$this->XINRegisterRule("q8_20_other", array("q8_20_f{@}=={@}01_yes"), "You must specify other ventilation system", "q8_20_other_group");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>BOX A");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Cycle through question <b>8-5 to BOX A</b> and any related module for <u>each</u> job listed in A. Sum of Jobs");
		$this->form->addElement('static', null, "Cycle through <b>8-8 to BOX A</b> and any related module for <u>each</u> school listed in 8-4");
		$this->form->addElement('static', null, "If this is the last job or school then go to question 8-21");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");



	} //end function _page23() =====================================================





	function _page24(){   // ========================================================


                $this->form->addElement('static', null, "<br/>");
                $this->form->addElement('static', null, "<br/>");
	        $this->form->addElement('static', null, "<b><i>Now, I would like to ask some questions about hobbies that you do at home or someplace else.</i></b>");
                $this->form->addElement('static', null, "<br/>");
                $this->form->addElement('static', null, "<br/>");


   		//q8_21
                $this->form->addElement("select", "q8_21", "8-21 In any of your hobbies, do you use chemicals such as pesticides, solvents, greases, paint, glue, or that generate dusts or fumes, such as woodworking, soldering or welding?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
                $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know], <b>END of INTERVIEW</b>");
                $this->form->addElement('static', null, "<br/>");


                //q8_22
                $this->form->addElement('static', null, "8-22 Could you please tell me what those hobbies are?");

                $oneToFive = array("1"=>"#1", "2"=>"#2", "3"=>"#3", "4"=>"#4", "5"=>"#5");
        //      reset($oneToFive);

                while(list($field, $label) = each($oneToFive)){

                        //$this->form->addElement("select", "q8_22_{$field}", $this->indent . "Hobby {$field}",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
                        $this->addTextAreaElementRD("q8_22_{$field}", $this->indent . "Hobby{$label}:");

                        if ($field>1)
                                $this->XINRegisterRule("q8_22_{$field}", array("q8_22_{$field}{@}=={@}NEVER_REQUIRED"), "q8_22_{$field}_group");
                        else
                		$this->XINRegisterRule("q8_22_{$field}", array("q8_21{@}=={@}01_yes"), "You must specify hobby", "q8_22_{$field}_group");
                }

                $this->form->addElement('static', null, "<br/>");


                //q8_23
                $this->form->addElement('static', null, "8-23 How many hours would you estimate that you spend doing this hobby per month for each hobby you mentioned?");
                $this->form->addElement('static', null, "<br/>");

                for ($i=1; $i<6; $i++)
                {
//                      $this->form->addElement("select", "q8_23_{$field}", $this->indent . "Hobby {$field}",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

                        $this->addTextAreaElementRD("q8_23_{$i}", $this->indent . "Hobby#{$i} (Hours):");

                        if ($i>1)
                                $this->XINRegisterRule("q8_23_{$i}", array("q8_23_{$i}{@}=={@}NEVER_REQUIRED"), "q8_23_{$i}_group");
                        else
                                $this->XINRegisterRule("q8_23_{$i}", array("q8_21{@}=={@}01_yes"), "You must specify hours", "q8_23_{$i}_group");            
		}

                $this->form->addElement('static', null, "<br/>");
                $this->form->addElement('static', null, "<br/>");


                $this->form->addElement('static', null, "<b/>BOX B");
                $this->form->addElement('static', null, $this->indent . "If you selected [Yes] to 8-21: <br/>$this->indent go to Clean Hands Module, Personal Protective Equipment Module, and then the Ventilation Module (start with question 8-24)");
                $this->form->addElement('static', null,  $this->indent . "When all Modules are complete go to <b>END of INTERVIEW</b>");
                $this->form->addElement('static', null, "<br/>");
                $this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: CLEAN HANDS");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_24
		$this->form->addElement("select", "q8_24", "8-24 Did you regularly get chemicals or dust on your hands or skin?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused", "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_24", array("q8_21{@}=={@}01_yes"), "Required if used any chemicals for hobbies");
		$this->form->addElement('static', null, $this->indent . "If you selected [No], end Clean Hands Module and go to 8-27");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

		//q8_25
		$this->form->addElement('static', null, "8-25 When you had chemicals or dust on your hands, when did you wash your hands? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$aToG = array("a"=>"a) When taking a break at work", "b"=>"b) Before eating", "c"=>"c) Before smoking", "d"=>"d) At the end of the work shift", "e"=>"e) When the task is completed", "f"=>"f) Whenever I get my hands dirty", "g"=>"g) Don't wash hands");

		foreach ($aToG as $field=>$label)
		{
			$this->form->addElement("select", "q8_25_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_25_{$field}", array("q8_24{@}=={@}01_yes"), "You must specify");
		}


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If you selected [Yes] to [g], end Clean Hands Module and go to 8-27");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_26
		$this->form->addElement('static', null, "8-26 What did you use to wash chemicals or dust off your hands? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$aToE = array("a"=>"a) Soap and water or water only", "b"=>"b) [Goop] or similar cleaners", "c"=>"c) Mineral spirits, turpentine, or paint thinner", "d"=>"d) Gasoline or kerosene", "e"=>"e) Something else");

		foreach ($aToE as $field=>$label)
		{
			$this->form->addElement("select", "q8_26_{$field}", "{$label}:",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_26_{$field}", array("q8_24{@}=={@}01_yes", "q8_25_g{@}!={@}01_yes"), "You must specify");
		}

		$this->addTextAreaElementRD('q8_26_other', $this->indent . 'If you selected [Yes] to [e) Something else], please specify:');
		$this->XINRegisterRule('q8_26_other', array("q8_26_e{@}=={@}01_yes"), "You must specify something else", "q8_26_other_group");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: PERSONAL PROTECTIVE EQUIPMENT");
		$this->form->addElement('static', null, "<br/>");

		//q8_27
		$this->form->addElement("select", "q8_27", "8-27 Between [-3] and DOBS, how often did you wear or use personal protective equipment (PPE) to protect you from the things you have mentioned? By personal protective equipment, I mean the things like gloves, dust mask, goggles, aprons, lab coats or other protective clothing, would you say always, often, rarely, or never us personal protective equipment?", array(NULL=>"", "01" => "01 Always", "02" => "02 Often", "03" => "03 Rarely", "04" => "04 Never", "88_Refused" => "88 Refused", "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule('q8_27', array("q8_21{@}=={@}01_yes"), "You must specify");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If you selected [Never], [Refused] or [Don't Know], end Personal Protective Module and go to 8-30");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_27a
		$this->form->addElement('static', null, "8-27a What did you use to wash chemicals or dust off your hands? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		foreach ($aToE as $field=>$label)
		{
			$this->form->addElement("select", "q8_27a{$field}", "{$label}:",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_27a{$field}", array("q8_27{@}=={@}01|02|03"), "You must specify");
		}

		$this->addTextAreaElementRD('q8_27a_other', $this->indent . 'If you selected [Yes] to [e) Something else], please specify:');
		$this->XINRegisterRule('q8_27a_other', array("q8_27ae{@}=={@}01_yes"), "You must specify something else", "q8_27a_other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_28
		$this->form->addElement('static', null, "8-28 Which type of protective clothing or equipment did you wear? Code all that apply.");
		$this->form->addElement('static', null, "<i>PROBE: Any other protective clothing or equipment?</i>");
		$this->form->addElement('static', null, "<br/>");

		foreach ($this->protectiveEquipment as $field=>$label)
		{
			$this->form->addElement("select", "q8_28_{$field}", "{$label}:",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_28_{$field}", array("q8_27{@}=={@}01|02|03"), "You must specify");
		}

		$this->addTextAreaElementRD('q8_28_other', $this->indent . 'If you selected [Yes] to [h Other], please specify:');
		$this->XINRegisterRule('q8_28_other', array("q8_28_h{@}=={@}01_yes"), "You must specify other", "q8_28_other_group");
		$this->form->addElement('static', null, $this->indent . "If [Yes] for [e], go to question 8-29");
		$this->form->addElement('static', null, $this->indent . "Otherwise end Personal Protective Equipment Module and go to 8-30");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_29
		$this->form->addElement('select', 'q8_29', "8-29 What type of respirator was it?", array(NULL=>"", "01" => "01) A half-mask chemical cartridge respirator", "02"=>"02 A full-mask chemical cartridge respirator", "03"=>"03) An air-supplied or SCBA respirator", "04"=>"04) Some other kind of respirator?",  "88_Refused"=>"88 Refused", "99_Do_Not_Know"=>"99 Don't know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule('q8_29', array("q8_28_e{@}=={@}01_yes"), "You must specify respirator");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: VENTILATION & ENCLOSURES");
		$this->form->addElement('static', null, "<br/>");


		//q8_30
		$this->form->addElement('select', 'q8_30', "8-30 Was there any kind of a ventilation system to remove exhaust, dust, smoke or fumes from the area?", array(NULL=>"", "01_yes"=>"Yes", "02_no"=>"No", "88_Refused"=>"88 Refused", "99_Do_Not_Know"=>"99 Don't know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<i>Probe: By ventilation system we mean purposely opening windows or doors, using a fume hood, or other ventilation system.</i>");
		$this->XINRegisterRule('q8_30', array("q8_21{@}=={@}01_yes"), "You must specify");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

		
		//q8_31
		$this->form->addElement('static', null, "8-31 What ventilation systems are present to remove exhaust, dust, smoke or fumes from the area? Is there...Code all that apply.");
		$this->form->addElement('static', null, "<br/>");

		foreach ($this->ventilators as $field=>$label)	
		{
			$this->form->addElement("select", "q8_31_{$field}", "{$label}:",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_31_{$field}", array("q8_30{@}=={@}01_yes"), "You must specify ventilation system(s)");
		}

		$this->addTextAreaElementRD('q8_31_other', $this->indent . 'If you selected [f) Some other type of ventilation system], please specify:');
		$this->XINRegisterRule('q8_31_other', array("q8_31_f{@}=={@}01_yes"), "You must specify other", "q8_31_other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		


		//q8_32
		$this->form->addElement('static', null, "8-32 For any of the hobbies do you use...Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$aToG = array("a"=>"a) Art supplies, such as paint, ceramic glazes or clays", "b"=>"b) Glue, such as for scrapbooking or other crafts", "c"=>"c) Pesticides, such as for gardening", "d"=>"d) Paints, solvents, or paint thinners, such as those used for furniture repair or painting?", "e"=>"e) Grease or oils, such as working on your car",  "f"=>"f) Solder or welding supplies",  "g"=>"g) Wood working or carpentry");
		reset($aToG);

		while(list($field, $label) = each($aToG)){
			$this->form->addElement("select", "q8_32_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_32_{$field}", array("q8_21{@}=={@}01_yes"), "You must specify");
		}

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] for all <u>8-32</u> part A through G go to <b>END of INTERVIEW</b>");
		$this->form->addElement('static', null, $this->indent . "If you selected [Yes] to part a, go to the Art Supply Module");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: USING ART SUPPLIES");
		$this->form->addElement('static', null, "<br/>");


		//q8_33
		$this->form->addElement('static', null, "8-33 Which art supplies did you typically use? Or use at least once a week? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$aToF = array("a"=>"a) Markers", "b"=>"b) Paints", "c"=>"c) Inks", "d"=>"d) Glazes", "e"=>"e) Something else",  "f"=>"f) No art supplies containing chemicals");
	
		foreach ($aToF as $field=>$label)
		{	
			$this->form->addElement("select", "q8_33_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_33_{$field}", array("q8_32_a{@}=={@}01_yes"), "Required if used art supplies");
		}

		$this->addTextAreaElementRD('q8_33_other', $this->indent . 'If you selected [Yes] to [e) Something else], please specify:');
		$this->XINRegisterRule('q8_33_other', array("q8_33_e{@}=={@}01_yes"), "You must specify something else", "q8_33_other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_34
		$this->form->addElement('static', null, "8-34 How often did you use the following art supplies?");
		$this->form->addElement('static', null, "<i>Probe: How many hours per day, per week or per month did you use the following art supplies?</i>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Select units or other from the list and specify number:");
		$this->form->addElement('static', null, "<br/>");

		foreach ($aToF as $field=>$label)
		{
			$this->form->addElement('select', "q8_34_{$field}", "{$label}:", array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->XINRegisterRule("q8_34_{$field}", array("q8_33_{$field}{@}=={@}01_yes"), "Required if used {$label}");
			$this->addNumericElementRD("q8_34_number{$field}", $this->indent . 'Number:');
			$this->form->addElement('static', null, "<br/>");
			//$this->XINRegisterRule("q8_34_{$field}", array("q8_34_{$field}{@}=={@}NEVER_REQUIRED"));
			$this->XINRegisterRule("q8_34_number{$field}", array("q8_34_{$field}{@}=={@}01|02|03|04"), "You must specify a number", "q8_34_number{$field}_group");
		}

		$this->addTextAreaElementRD('q8_34_other', $this->indent . 'If you selected [Yes] to [e) Something else], please specify:');
		$this->XINRegisterRule('q8_34_other', array("q8_34_e{@}=={@}01_yes"), "You must specify something else", "q8_34_other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "If you selected [Yes] to q8-32 part b, go to the Gluing Activity Module");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: GLUING");
		$this->form->addElement('static', null, "<br/>");


		//q8_35
		$this->form->addElement("select", "q8_35", "8-35 Did you routinely use glues or adhesives?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_35", array("q8_32_b{@}=={@}01_yes"), "Required if used glue");
		$this->form->addElement('static', null, "<br/>");


		//q8_36
		$this->form->addElement('static', null, "8-36 Which glues did you use? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		
		foreach ($this->adhesives as $field=>$label)
		{
			$this->form->addElement("select", "q8_36_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused", "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_36_{$field}", array("q8_35{@}=={@}01_yes"), "You must specify type of glue(s)");
		}

		$this->addTextAreaElementRD('q8_36_other', $this->indent . 'If you selected [e) Something else], please specify:');
		$this->XINRegisterRule('q8_36_other', array("q8_36_e{@}=={@}01_yes"), "You must specify something else", "q8_36_other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_37
		$this->form->addElement('static', null, "8-37 How strong was the smell of {hot melt glues/contact adhesives/water-based adhesives/wood laminates}? Code for each yes response in 8-36");
		$this->form->addElement('static', null, "<br/>");

		foreach ($this->adhesives as $field=>$label)
		{
			$this->form->addElement("select", "q8_37_{$field}", "{$label}", array(NULL=>"", "01" => "01 Slight", "02" => "02 Moderate", "03" => "03 Strong", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->XINRegisterRule("q8_37_{$field}", array("q8_36_{$field}{@}=={@}01_yes"), "You must specify smell strength");
		}

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

		
		//q8_38
		$this->form->addElement("select", "q8_38", "8-38 Did you wipe off the excess glue or adhesive with a solvent?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule('q8_38', array("q8_35{@}=={@}01_yes"), "You must specify");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_39
		$this->form->addElement('static', null, "8-39 What solvent did you typically wipe it off with? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$solvents = array("a"=>"a) Acetone", "b"=>"b) Paint thinner", "c"=>"c) Citrus-based chemicals", "d"=>"d) Something else");

		foreach ($solvents as $field=>$label)
		{
			$this->form->addElement("select", "q8_39_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_39_{$field}", array("q8_38{@}=={@}01_yes"), "You must specify");
		}

		$this->addTextAreaElementRD('q8_39_other', $this->indent . 'If you selected [d) Something else], please specify:');
		$this->XINRegisterRule('q8_39_other', array("q8_39_d{@}=={@}01_yes"), "You must specify something else", "q8_39_other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_40
		$this->form->addElement('static', null, "8-40 How often did you use the following glues or adhesives?");
		$this->form->addElement('static', null, "<i>Probe: How many hours per day, per week or per month do you use the following glues or adhesives?</i>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Select units or other from the list and specify number:");
		$this->form->addElement('static', null, "<br/>");

		foreach ($this->adhesives as $field=>$label)
		{
			$this->form->addElement('select', "q8_40_{$field}", "{$label}:", array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->XINRegisterRule("q8_40_{$field}", array("q8_36_{$field}{@}=={@}01_yes"), "You must specify frequency");
			$this->addTextAreaElementRD("q8_40_number{$field}", $this->indent . 'Number:');
			$this->XINRegisterRule("q8_40_number{$field}", array("q8_40_{$field}{@}=={@}01|02|03|04"), "You must specify number", "q8_40_number{$field}_group");
		}

		$this->form->addElement('static', null, $this->indent . "If yes 8-32 part c then [go to Pesticide Use Module]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


	} //end function _page24() =====================================================




	function _page25(){   // ========================================================


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: PESTICIDE USE");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//function with more complex rules
		$this->form->addFormRule(array(&$this, 'rulesPage25'));


		//q8_41
		$this->form->addElement("select", "q8_41", "8-41 Pesticides include many types of chemicals used to repel, kill, or control unwanted weeds, insects, rodents, fungi, or bacteria. They include herbicides, insecticides, rodenticides, fungicides, and bactericides. Did you mix, apply, spray, process or use pesticides?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_41", array("q8_41{@}=={@}NEVER_REQUIRED"));
		$this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 8-64");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_42
		$this->form->addElement('static', null, "8-42 Between [3] and DOBS, which types of pesticides did you use? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$pesticides = array("a"=>"a) Insecticides which kill bugs", "b"=>"b) Herbicides or weed killer", "c"=>"c) Rodenticides which kill rats and mice", "d"=>"d) Fungicides which kill mold or fungus", "e"=>"e) Bactericides which kill bacteria",  "f"=>"f) Something else?");

		foreach ($pesticides as $field=>$label)
		{
			$this->form->addElement("select", "q8_42_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_42_{$field}", array("q8_41{@}=={@}01_yes"), "You must specify");
		}

		$this->addTextAreaElementRD('q8_42_other', $this->indent . 'If you selected [f) Something else], please specify:');
		$this->XINRegisterRule('q8_42_other', array("q8_42_f{@}=={@}01_yes"), "You must specify other", "q8_42_other_group");
		$this->form->addElement('static', null, $this->indent . "If you selected [No] to <u>all</u> <b>a-f</b>,go to 8-52");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_43
		$this->form->addElement('static', null, "8-43 Where did you use the pesticides? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$list = array("a"=>"a) In or around buildings", "b"=>"b) On crops", "c"=>"c) On forests", "d"=>"d) On roads", "e"=>"e) On seeds",  "f"=>"f) On animals",  "g"=>"g) For aquatic pest control",  "h"=>"h) To process, pack, or manufacture them at warehouse or factory",  "i"=>"i) Something else?");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_43_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_43_{$field}", array("q8_41{@}=={@}01_yes"), "Required if used pesticides");
			
		}        

		$this->addTextAreaElementRD('q8_43_other', $this->indent . 'If you selected [i) Something else], please specify:');
		$this->XINRegisterRule('q8_43_other', array("q8_43_i{@}=={@}01_yes"), "You must specify something else", "q8_43_other_group");
		$this->form->addElement('static', null, $this->indent . "If you selected [Yes] to [8-42 part a], go to 8-44");
		$this->form->addElement('static', null, $this->indent . "If you selected [Yes] to [8-42 part b], go to 8-45");
		$this->form->addElement('static', null, $this->indent . "If you selected [Yes] to [8-42 part c], go to 8-46");
		$this->form->addElement('static', null, $this->indent . "If you selected [Yes] to [8-42 part d], go to 8-47");
		$this->form->addElement('static', null, $this->indent . "If you selected [Yes] to [8-42 part e], go to 8-48");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_44
		$this->addTextAreaElementRD('q8_44', "8-44 You said that you used insecticides or bug killers. Please name all that you used:");
		$this->XINRegisterRule('q8_44', array("q8_42_a{@}=={@}01_yes"), "You must specify insecticide", "q8_44_group");
		$this->form->addElement('static', null, "<br/>");


		//q8_45
		$this->addTextAreaElementRD('q8_45', "8-45 You said that you used herbicides or weed killers. Please name all that you used:");
		$this->XINRegisterRule('q8_45', array("q8_42_b{@}=={@}01_yes"), "You must specify herbicide", "q8_45_group");
		$this->form->addElement('static', null, "<br/>");


		//q8_46
		$this->addTextAreaElementRD('q8_46', "8-46 You said that you used rodenticides. Please name all that you used:");
		$this->XINRegisterRule('q8_46', array("q8_42_c{@}=={@}01_yes"), "You must specify rodenticide", "q8_46_group");
		$this->form->addElement('static', null, "<br/>");


		//q8_47
		$this->addTextAreaElementRD('q8_47', "8-47 You said that you used fungicides or mold and fungus killers. Please name all that you used:");
		$this->XINRegisterRule('q8_47', array("q8_42_d{@}=={@}01_yes"), "You must specify fungicicide", "q8_47_group");
		$this->form->addElement('static', null, "<br/>");


		//q8_48
		$this->addTextAreaElementRD('q8_48', "8-48 You said that you used bactericides or bacteria killers. Please name all that you used:");
		$this->XINRegisterRule('q8_48', array("q8_42_e{@}=={@}01_yes"), "You must specify bactericide", "q8_48_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_49
		$this->form->addElement('static', null, "8-49 How often did you use the following pesticide products?");
		$this->form->addElement('static', null, "<i>Probe: How many hours per day, per week or per month do you use the following glues or adhesives?</i>");
		$this->form->addElement('static', null, "<br/>");

		foreach ($pesticides as $field=>$label)
		{

			$this->form->addElement('select', "q8_49_{$field}", "{$label}:",  array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->XINRegisterRule("q8_49_{$field}", array("q8_42_{$field}{@}=={@}01_yes"), "You must specify time");
			$this->addTextAreaElementRD("q8_49_number{$field}", $this->indent . "Number:");
			$this->XINRegisterRule("q8_49_number{$field}", array("q8_49_{$field}{@}=={@}01|02|03|04"), "You must specify time", "q8_49_number{$field}_group");
		}

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_50
		$this->form->addElement('static', null, "8-50 Which of the following activities did you typically do? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$activities = array("a"=>"a) Mix pesticides", "b"=>"b) Put pesticides into a spray container or tank", "c"=>"c) Spray or apply pesticides", "d"=>"d) Dispose of waste from pesticide use", "e"=>"e) Something else?");
		reset($list);

		foreach($activities as $field=>$label){
			$this->form->addElement("select", "q8_50_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_50_{$field}", array("q8_50_{$field}{@}=={@}NEVER_REQUIRED"));
		}

		$this->addTextAreaElementRD('q8_50_other', $this->indent . 'If you selected [e) Something else], please specify:');
		$this->XINRegisterRule('q8_50_other', array("q8_50_e{@}=={@}01_yes"), "You must specify something else", "q8_50_other_group");
		$this->form->addElement('static', null, "<br/>");


		//q8_51
		$this->form->addElement("select", "q8_51", "8-51 Between [-3] and DOBS, were there 3 or more times when your clothing has gotten wet with pesticides?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused", "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_51", array("q8_51{@}=={@}NEVER_REQUIRED"));
		$this->form->addElement('static', null, $this->indent . "If you selected [Yes] to [8-43 b], go to 8-52");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_52
		$this->form->addElement('static', null, "8-52 You said that you apply pesticides to crops. How did you usually apply them? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$list = array("a"=>"a) Using hand-held devices", "b"=>"b) By tractor or truck", "c"=>"c) By aircraft", "d"=>"d) Something else?");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_52_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_52_{$field}", array("q8_43_b{@}=={@}01_yes"), "You must specify application methods");
		}

		$this->addTextAreaElementRD('q8_52_other', $this->indent . 'If you selected [d) Something else], please specify:');
		$this->XINRegisterRule('q8_52_other', array("q8_52_d{@}=={@}01_yes"), "You must specify something else", "q8_52_other_group");
		$this->form->addElement('static', null, $this->indent . "If  you selected [Yes] to [a], go to question 8-53");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_53
		$this->form->addElement('static', null, "8-53 What type of hand-operated devices did you usually use? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$list = array("a"=>"a) Pressurized can or aerosols", "b"=>"b) Pressurized cylinders", "c"=>"c) Trigger pump sprayers or squirt guns", "d"=>"d) Hose-end sprayers", "e"=>"e) Compressed air sprayers worn on the back pack or slung over the shoulder",  "f"=>"f) Push-pull hand pump sprayer",  "g"=>"g) Something else?");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_53_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_53_{$field}", array("q8_52_a{@}=={@}01_yes"), "You must specify hand-operated device(s)");
		}

		$this->addTextAreaElementRD('q8_53_other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule('q8_53_other', array("q8_53_g{@}=={@}01_yes"), "You must specify something else", "q8_53_other_group");
		$this->form->addElement('static', null, $this->indent . "If you selected [Yes] to [b or c for 8-52], [go to question 8-54]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_54
		$this->form->addElement('static', null, "8-54 What type of pesticide application device did you use for your vehicle or aircraft? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$list = array("a"=>"a) Low-pressure boomless sprayer", "b"=>"b) Boom sprayer", "c"=>"c) High pressure hydraulic sprayers", "d"=>"d) Air-blast sprayer", "e"=>"e) Low-volume air sprayer or mist blower",  "f"=>"f) Ultra-low volume or ULV sprayer (IF NEEDED: uses fine droplets with little water)",  "g"=>"g) Something else?");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_54_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_54_{$field}", array("q8_54_{$field}{@}=={@}NEVER_REQUIRED"));
		}

		$this->addTextAreaElementRD('q8_54_other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule('q8_54_other', array("q8_54_g{@}=={@}01_yes"), "You must specify something else", "q8_54_other_group");
		$this->form->addElement('static', null, $this->indent . "If you selected [Yes] to [b for 8-52], [go to question 8-55 and 8-56]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_55
		$this->form->addElement("select", "q8_55", "8-55 Did the vehicle you used for this usually have a cab?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_55", array("q8_52_b{@}=={@}01_yes"), "Required if applied pesticides by tractor or truck");
		$this->form->addElement('static', null, "<br/>");


		//q8_56
		$this->form->addElement("select", "q8_56", "8-56 Did you usually keep the windows open or closed?",  array(NULL=>"", "01" => "01 Open", "02" => "02 Closed", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_56", array("q8_52_b{@}=={@}01_yes"), "Required if applied pesticides by tractor or truck");
		$this->form->addElement('static', null, $this->indent . "If you selected [Yes] to [8-43 part b, part c, or part d], [go to question 8-57]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_57
		$this->form->addElement('static', null, "8-57 What form of pesticide did you apply? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$list = array("a"=>"a) Liquid", "b"=>"b) Dust", "c"=>"c) Granules (typically used for landscaping)", "d"=>"d) Something else?");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_57_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_57_{$field}", array("q8_57_{$field}{@}=={@}NEVER_REQUIRED"));
		}
		
		$this->addTextAreaElementRD('q8_57_other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule('q8_57_other', array("q8_57_d{@}=={@}01_yes"), "You must specify something else", "q8_57_other_group");
		$this->form->addElement('static', null, $this->indent . "If you selected [Yes] to [part a], [go to 8-58]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_59
		$this->form->addElement('static', null, "8-58 What type of liquid did you apply? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$liquidList = array("a"=>"a) Coarse, which are produced by coarse disk or solid stream gun nozzles", "b"=>"b) Fine, which are produced by high pressure hollow-cone and fan-spray nozzles", "c"=>"c) Mists, which are produced by high pressure pumps, rotors and atomizers", "d" => "d) Aerosols and fogs, which are produced by thermal aerosol generators, rotors and atomizers", "e" => "e) Smokes and fumes, which are produced by thermal fog generators", "f" => "f) Vapors, which are droplets less than 0.001 micron", "g" => "g) Something else?");
                reset($liquidList);

                while(list($field, $label) = each($liquidList)){
                        $this->form->addElement("select", "q8_58_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_58_{$field}", array("q8_57_a{@}=={@}01_yes"), "You must specify type of liquid");

                }

		$this->addTextAreaElementRD('q8_58_other', $this->indent . 'If you selected [g) Something else?], please specify:');
		$this->XINRegisterRule('q8_58_other', array("q8_58_g{@}=={@}01_yes"), "You must specify other", "q8_58_other_group");
		$this->form->addElement('static', null, $this->indent . "If you selected [Yes] to [8-57 part b], go to 8-59");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_59
		$this->form->addElement('static', null, "8-59 What type of dust did you apply? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Coarse", "b"=>"b) Medium", "c"=>"c) Fine");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_59_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_59_{$field}", array("q8_57_b{@}=={@}01_yes"), "You must specify type of dust");
		}

		$this->form->addElement('static', null, $this->indent . "If you selected [Yes] to [part f] in q8-43,[go to 8-60 and 8-61]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_60
		$this->form->addElement("select", "q8_60", "8-60 You said that you applied pesticides to animals. What type of animals did you typically apply pesticides to?",  array(NULL=>"", "01" => "01 Farm animals", "02" => "02 Companion animals, such as dogs and cats", "03" => "03  Both farm animals and companion animals", "04" => "04 Some other type of animal?", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_60", array("q8_43_f{@}=={@}01_yes"), "You must specify animals");
		$this->addTextAreaElementRD('q8_60_other', $this->indent . 'If you selected [Some other type of animal], please specify:');
		$this->XINRegisterRule("q8_60_other", array("q8_60{@}=={@}04"), "You must specify other", "q8_60_other_group");
		$this->form->addElement('static', null, "<br/>");


		//q8_61
		$this->form->addElement('static', null, "8-61 How did you usually apply them? Did you...Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$list = array("a"=>"a) Spray the animals", "b"=>"b) Dust or pour it on animals", "c"=>"c) Inject the animals", "d"=>"d) Use ear tags", "e"=>"e) Dip the animals",  "f"=>"f) Use power duster",  "g"=>"g) Use pest strips",  "h"=>"h) Use fog/mist animals",  "i"=>"i) Use rope wick",  "j"=>"j) Use something else");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_61_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_61_{$field}", array("q8_43_f{@}=={@}01_yes"), "You must specify application on animals");
		}

		$this->addTextAreaElementRD('q8_61_other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule('q8_61_other', array("q8_61_j{@}=={@}01_yes"), "You must specify something else", "q8_61_other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If you selected [Yes] to [8-43 part a], [go to 8-62]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

		
		//q8_62
		$this->form->addElement('static', null, "8-62 You said that you applied pesticides in or around buildings. Did you usually use a...Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$list = array("a"=>"a) Mist blower", "b"=>"b) Hand-held spray gun or wand with a spray", "c"=>"c) Backpack sprayer ", "d"=>"d) Rig that sat on the floor", "e"=>"e) Dust by hand",  "f"=>"f) Sub-surface application methods, such as for termite control",  "g"=>"g) Something else");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_62_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_62_{$field}", array("q8_43_a{@}=={@}01_yes"), "You must specify");
		}

		$this->addTextAreaElementRD('q8_62_other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule('q8_62_other', array("q8_62_g{@}=={@}01_yes"), "You must specify something else", "q8_62_other_group");
		$this->form->addElement('static', null, "<br/>");


		//q8_63
		$this->addTextAreaElementRD('q8_63', "8-63 On average, how many total days a year did you apply pesticides?");
		$this->XINRegisterRule("q8_63", array("q8_41{@}=={@}01_yes"), "Required if applied pesticides", "q8_63_group");
		$this->form->addElement('static', null, $this->indent . "If you selected [Yes] to [8-32 part d], [go to Painting, Paint Removal, Paint Cleaning Module, and Organic Solvent Module]");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: PAINTING, PAINT REMOVAL, PAINT CLEANING");
		$this->form->addElement('static', null, "<br/>");


		//q8_64
		$this->form->addElement('static', null, "8-64 Did you typically do any of the following activities? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$list = array("a"=>"a) Painting, varnishing, or staining", "b"=>"b) Paint removal", "c"=>"c) Paint thinning and cleaning", "d"=>"d) Something else", "e"=>"e) None of the above");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_64_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_64_{$field}", array("q8_32_d{@}=={@}01_yes"), "Required if used paints, solvents, or paint thinners");
		}

		$this->addTextAreaElementRD('q8_64_other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule('q8_64_other', array("q8_64_d{@}=={@}01_yes"), "You must specify something else", "q8_64_other_group");
		$this->form->addElement('static', null, $this->indent . "If you selected [None of the above], [Refused], or [Don't know], end Painting Module and go to 8-72");
		$this->form->addElement('static', null, $this->indent . "If you selected [Yes] to [part a], [go to 8-65, 8-66, 8-67]");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_65
		$this->form->addElement('static', null, "8-65 What kind of paint did you use? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Laytex or water-based paint", "b"=>"b) Acrylic", "c"=>"c) Oil-based paint (enamel)", "d"=>"d) Something else");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_65_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_65_{$field}", array("q8_64_a{@}=={@}01_yes"), "You must specify paint type");
		}

		$this->addTextAreaElementRD('q8_65_other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule('q8_65_other', array("q8_65_d{@}=={@}01_yes"), "You must specify something else", "q8_65_other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_66
		$this->form->addElement('static', null, "8-66 Did you usually brush, roll, or spray paint?");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Brush", "b"=>"b) Roll", "c"=>"c) Spray", "d"=>"d) Something else");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_66_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_66_{$field}", array("q8_64_a{@}=={@}01_yes"), "You must specify paint activity");
		}

		$this->addTextAreaElementRD('q8_66_other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule('q8_66_other', array("q8_66_d{@}=={@}01_yes"), "You must specify something else", "q8_66_other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_67
		$this->form->addElement("select", "q8_67", "8-67 Did you use primers with lead, chromate, or zinc?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_67", array("q8_64_a{@}=={@}01_yes"), "You must specify");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If you selected [Yes] to [8-64 part b], [go to 8-68]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_68
		$this->form->addElement('static', null, "8-68 How did you typically remove paint? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Heat gun", "b"=>"b) Scraper or wire stripper with a drill bit attachment", "c"=>"c) Chemical paint stripper", "d"=>"d) Some other paint removal method");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_68_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_68_{$field}", array("q8_64_b{@}=={@}01_yes"), "You must specify paint removal");
		}

		$this->addTextAreaElementRD('q8_68_other', $this->indent . 'If you selected [Some other paint removal method], please specify:');
		$this->XINRegisterRule('q8_68_other', array("q8_68_d{@}=={@}01_yes"), "You must specify other", "q8_68_other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If you selected [Yes] to [8-64 part c], [go to 8-69]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_69
		$this->form->addElement('static', null, "8-69 What did you typically use to thin or clean paint, varnish or stain? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$list = array("a"=>"a) Paint thinner, mineral spirits, or turpertine", "b"=>"b) Lacquer thinner", "c"=>"c) Alcohol", "d"=>"d) Water", "e"=>"e) Citrus-based products",  "f"=>"f) Gasoline or kerosene",  "g"=>"g) Other");
		reset($list); 

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_69_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_69_{$field}", array("q8_64_c{@}=={@}01_yes"), "You must specify thinner/cleaner");
		}

		$this->addTextAreaElementRD('q8_69_other', $this->indent . 'If you selected [Other], please specify:');
		$this->XINRegisterRule('q8_69_other', array("q8_69_d{@}=={@}01_yes"), "You must specify other", "q8_69_other_group");
		$this->form->addElement('static', null, $this->indent . "If you selected [Yes] to [8-68 part c], [go to 8-70]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_70
		$this->form->addElement('static', null, "8-70 What chemicals did you use to strip paint? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Lacquer or paint thinner", "b"=>"b) Lye (Sodium hydroxide)", "c"=>"c) Ammonia (Ammonia Hydroxide)", "d"=>"d) Other");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_70_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_70_{$field}", array("q8_68_c{@}=={@}01_yes"), "You must specify paint type");
		}

		$this->addTextAreaElementRD('q8_70_other', $this->indent . 'If you selected [Other], please specify:');
		$this->XINRegisterRule('q8_70_other', array("q8_70_d{@}=={@}01_yes"), "You must specify other", "q8_70_other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_71
		$this->form->addElement('static', null, "8-71 How often did you use the following paint, paint thinners, or paint strippers?");
		$this->form->addElement('static', null, "<i>Probe: How many hours per day, per week or per month did you use the following paint, paint thinners, or paint strippers?</i>");
		$this->form->addElement('static', null, "<br/>");

		$list = array("a"=>"a) Laytex or water-based paint", "b"=>"b) Acrylic", "c"=>"c) Oil-based paint (enamel)","d"=>"d) Paint thinner, mineral spirits, or turpertin", "e"=>"e) Lacquer thinner", "f"=>"f) Alcohol", "g"=>"g) Water", "h"=>"h) Citrus-based products",  "i"=>"i) Gasoline or kerosene", "j"=>"j) Lacquer or paint thinner", "k"=>"k) Lye (Sodium hydroxide)", "l"=>"l) Ammonia (Ammonia Hydroxide)", "m"=>"m) Other" );

		reset($list);
		while(list($field, $label) = each($list)){

			$this->form->addElement('select', "q8_71_{$field}", "{$label}:", array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->XINRegisterRule("q8_71_{$field}", array("q8_70_{$field}{@}=={@}01_yes"), "Required if answered yes to 70-{$field}");
			$this->addTextAreaElementRD("q8_71_other{$field}", $this->indent . 'Number:');
			$this->XINRegisterRule("q8_71_other{$field}", array("q8_71_{$field}{@}=={@}01|02|03|04"), "You must specify number", "q8_71_other{$field}_group");
		}


		$this->form->addElement('static', null, $this->indent . "If you selected [Yes] to [8-32 part d], [go to 8-72]");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: CLEANING WITH ORGANIC SOLVENTS");
		$this->form->addElement('static', null, "<br/>");


		//q8_72
		$this->form->addElement("select", "q8_72", "8-72 Did you routinely clean parts with organic solvents or other products to degrease metal parts?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_72", array("q8_72{@}=={@}NEVER_REQUIRED"));
		$this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know], end Cleaning with Organic Solvents Module");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_73
		$this->form->addElement('static', null, "8-73 What cleaning products did you typically use? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) [Gunk] or similar cleaner", "b"=>"b) Acid", "c"=>"c) Alcohols", "d"=>"d) Alkalis or caustics", "e"=>"e) Cutting oils",  "f"=>"f) Diesel",  "g"=>"g) Gasoline",  "h"=>"h) Mineral spirits, paint thinner, naphtha, Stoddard solvent, turpentin", "i"=>"i) Something else");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_73_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_73_{$field}", array("q8_72{@}=={@}01_yes"), "You must specify cleaning product(s)");	
		}

		$this->addTextAreaElementRD('q8_73_other', $this->indent . "If you selected [Something else] then please specify:");
		$this->XINRegisterRule("q8_73_other", array("q8_73_i{@}=={@}01_yes"), "You must specify something else", "q8_73_other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_74
		$this->form->addElement('static', null, "8-74 How often did you use the following cleaning products?");
		$this->form->addElement('static', null, "<i>Probe: How many hours per day, per week or per month did you use the following cleaning products?</i>");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) [Gunk] or similar cleaner", "b"=>"b) Acid", "c"=>"c) Alcohols", "d"=>"d) Alkalis or caustics", "e"=>"e) Cutting oils",  "f"=>"f) Diesel",  "g"=>"g) Gasoline",  "h"=>"h) Mineral spirits, paint thinner, naphtha, Stoddard solvent, turpentin", "i"=>"i) Something else");

		reset($list);
		while(list($field, $label) = each($list)){

			$this->form->addElement('select',"q8_74_{$field}", "{$label}:", array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->XINRegisterRule("q8_74_{$field}", array("q8_73_{$field}{@}=={@}01_yes"), "You must specify units");	
			$this->addTextAreaElementRD("q8_74_other{$field}", $this->indent . 'Number:');
			$this->XINRegisterRule("q8_74_other{$field}", array("q8_74_{$field}{@}=={@}01|02|03|04"), "You must specify number", "q8_74_other{$field}_group");
		}
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_75
		$this->form->addElement("select", "q8_75", "8-75 How often did you work with heating degreasing chemicals?",  array(NULL=>"", "01" => "01 Always", "02" => "02 Sometimes", "03" => "03  Never", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_75", array("q8_72{@}=={@}01_yes"), "You must specify");	
		$this->form->addElement('static', null, $this->indent . "If you selected [Yes] to [8-32 part e], [go to Lubricating Engines and Machinery Module and Fuel and Exhaust Smells Module]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

	} //end function _page25() ======================================================



	function rulesPage25($fields)
	{

		$errors = array();

                $db =& Database::singleton();


                $db->selectRow("SELECT q8_32_c, q8_32_d FROM EARLI_interview_PART_3 WHERE CommentID='".$this->getCommentID()."'", $answer);


                function multSelect($fields, $question1, $question2)
                {
                        return ($fields[$question1] == array(0=>null) || (empty($fields[$question1])) && $fields[$question2] == "01_yes");
                }


		$options = array("a", "b", "c", "d", "e", "f"); 

		if ($answer["q8_32_c"] == "01_yes" && empty($fields["q8_41"]))
			$errors["q8_41"] = "You must specify";

		if ($answer["q8_32_d"] == "01_yes")
		{
			for ($i=0; $i<5; $i++)
			{
				if (empty($fields["q8_64_$options[$i]"]))
					$errors["q8_64_$options[$i]"] = "You must specify";
			}
			
			if(empty($fields["q8_72"]))
				$errors["q8_72"] = "You must specify";
		}


		for ($i=0; $i<6; $i++)
		{
			if ($fields["q8_42_$options[$i]"] == "01_yes")
			{
				for ($j=0; $j<5; $j++)
				{
					if (empty($fields["q8_50_$options[$j]"]))
						$errors["q8_50_$options[$j]"] = "You must specify";
				}
			
				if (empty($fields["q8_51"]))
				{
					$errors["q8_51"] = "You must specify";
					break;
				}
			}

		}

		$options2 = array("a", "b", "c", "d", "e", "f", "g");

		if($fields["q8_52_b"] == "01_yes" || $fields["q8_52_c"] == "01_yes")
		{

			for ($i=0; $i<7; $i++)
			{
				if (empty($fields["q8_54_$options2[$i]"]))
					$errors["q8_54_$options2[$i]"] = "Required if applied pesticides by tractor, truck or aircraft";
			}
		}

		if ($fields["q8_43_b"] == "01_yes" || $fields["q8_43_c"] == "01_yes" || $fields["q8_43_d"] == "01_yes")
		for ($i=0; $i<4; $i++)
		{
			if (empty($fields["q8_54_$options2[$i]"]))
				$errors["q8_57_$options2[$i]"] = "Required if applied pesticides on crops, forests or roads"; 
		}


		for ($i=0; $i<5; $i++)
		{
			if ($fields["q5_64_$options2[$i]"] == "01_yes")
			{
				if (empty($fields["q5_71"]))
					$errors["q5_71"] = "You must specify";
				break;
			}	
		}
		
		return $errors;
	}




	function _page26(){   // ========================================================


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
                $this->form->addElement('static', null, "<b/>ACTIVITY MODULE: LUBRICATING ENGINES & MACHINERY");
                $this->form->addElement('static', null, "<br/>");


                //q8_76
                $this->form->addElement("select", "q8_76", "8-76 Did you routinely use lubricating oils, or waxes on engines or machinery?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
                $this->XINRegisterRule("q8_76", array("q8_76{@}=={@}NEVER_REQUIRED"));
                $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know], end Lubricating Module");
                $this->form->addElement('static', null, "<br/>");


                //q8_77
                $this->addTextAreaElementRD('q8_77', "8-77 What types of lubricants did you work with?");
                $this->XINRegisterRule("q8_77", array("q8_76{@}=={@}01_yes"), "You must specify", "q8_77_group");
                $this->form->addElement('static', null, "<br/>");


                //q8_78
                $this->form->addElement('static', null, "8-78 What types of cutting oils did you work with? Code all that apply:");
                $this->form->addElement('static', null, "<br/>");
                $list = array("a"=>"a) Straight cutting oils or oils that look and feel like motor oil", "b"=>"b) Soluble cutting oils or oils that are milky white", "c"=>"c) Synthetic cutting oils or oils that feel like water or may be brightly colored, such as green or blue", "d"=>"d) Something else");
                reset($list);

                while(list($field, $label) = each($list)){
                        $this->form->addElement("select", "q8_78_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
                        $this->XINRegisterRule("q8_78_{$field}", array("q8_76{@}=={@}01_yes"), "You must specify cutting oil(s)");
                }

                $this->addTextAreaElementRD('q8_78_other', $this->indent . 'If you selected [Something else] then please specify:');
                $this->XINRegisterRule("q8_78_other", array("q8_78_d{@}=={@}01_yes"), "You must specify something else", "q8_78_other_group");
                $this->form->addElement('static', null, "<br/>");


                //q8_79
                $this->form->addElement('static', null, "8-79 How often did you use the following lubricants?");
                $this->form->addElement('static', null, "<br/>");
                $this->form->addElement('static', null, "<i>Probe: How many hours per day, per week or per month did you use the following lubricants?</i>");
                $this->form->addElement('static', null, "<br/>");
                $list = array("a"=>"a) Straight cutting oils or oils that look and feel like motor oil", "b"=>"b) Soluble cutting oils or oils that are milky white", "c"=>"c) Synthetic cutting oils or oils that feel like water or may be brightly colored, such as green or blue", "d"=>"d) Something else");

                reset($list);
                while(list($field, $label) = each($list)){

                        $this->form->addElement('select', "q8_79_{$field}", "{$label}:",  array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
                        $this->XINRegisterRule("q8_79_{$field}", array("q8_78_{$field}{@}=={@}01_yes"), "You must specify frequency");
                        $this->addTextAreaElementRD("q8_79_other{$field}", $this->indent . 'Number:');
                        $this->XINRegisterRule("q8_79_other{$field}", array("q8_79_{$field}{@}=={@}01|02|03|04"), "You must specify number", "q8_79_other{$field}_group");
                }

                $this->form->addElement('static', null, "<br/>");
                $this->form->addElement('static', null, "<br/>");
                $this->form->addElement('static', null, "<b/>ACTIVITY MODULE: FUEL AND EXHAUST SMELLS");
                $this->form->addElement('static', null, "<br/>");


                //q8_80
                $this->form->addElement("select", "q8_80", "8-80 Did you regularly smell fuel vapors, such as from gas or fuel tanks, or exhaust vapors, such as from car or truck tail pipes?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
                $this->XINRegisterRule("q8_80", array("q8_80{@}=={@}NEVER_REQUIREd"));
                $this->form->addElement('static', null, $this->indent . "If you selected [No], [end Fuel and Exhaust Smells Module]");
                $this->form->addElement('static', null, "<br/>");


                //q8_81
                $this->form->addElement("select", "q8_81", "8-81 How strong was the smell?",  array(NULL=>"", "01" => "01 Slight", "02" => "02 Moderate", "03" => "03  Strong", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
                $this->XINRegisterRule("q8_81", array("q8_80{@}=={@}01_yes"), "You must specify");
                $this->form->addElement('static', null, "<br/>");
                $this->form->addElement('static', null, "<br/>");
                $this->form->addElement('static', null, $this->indent . "If you selected [Yes] to [8-32 part f], go to Soldering and Welding Module");
                $this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: SOLDERING AND WELDING");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//function with more complex rules
		$this->form->addFormRule(array(&$this, 'rulesPage26'));
		

		//q8_82
		$this->form->addElement('static', null, "8-82 Did you do any of the following? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Soldering or brazing", "b"=>"b) Smell fumes from others who solder or braze", "c"=>"c) Welding or flame cutting", "d"=>"d) Smell fumes from others who weld or flame cut", "e"=>"e) Some other welding or soldering method?",  "f"=>"f) None of the above");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_82_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No", "88_refused" => "88 Refused", "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_82_{$field}", array("q8_82_{$field}{@}=={@}NEVER_REQUIRED"));
		}

		$this->addTextAreaElementRD('q8_82other', $this->indent . 'If you selected [Some other welding or soldering method?], please specify:');
		$this->XINRegisterRule("q8_82other", array("q8_82_e{@}=={@}01_yes"), "You must specify other", "q8_82other_group");
		$this->form->addElement('static', null, $this->indent . "If you selected [None of the above], [Refused], or [Don't Know], END Soldering Module");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_83
		$this->form->addElement('static', null, "8-83 What types of metal did {you/they/you and those who weld or flame cut around you} weld or flame cut? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Aluminum", "b"=>"b) Brass or bronze", "c"=>"c) Cast iron", "d"=>"d) Copper", "e"=>"e) Steel",  "f"=>"f) Titanium-based alloy",  "g"=>"g) Other");
		reset($list); 

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_83_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_83_{$field}", array("q8_83_{$field}{@}=={@}NEVER_REQUIRED"));
		}

		$this->addTextAreaElementRD('q8_83other', $this->indent . 'If you selected [Other], please specify:');
		$this->XINRegisterRule("q8_83other", array("q8_83_g{@}=={@}01_yes"), "You must specify other", "q8_83other_group");
		$this->form->addElement('static', null, $this->indent . "If you selected [Yes] to [part a-d], [go to 8-85]");
		$this->form->addElement('static', null, $this->indent . "If you selected [Yes] to [part f-g], [go to 8-85]");
		$this->form->addElement('static', null, $this->indent . "If you selected [Refused] or [Don't Know] to [part a-e], [go to 8-85]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_84
		$this->form->addElement("select", "q8_84", "8-84 What kind of steel was it?",  array(NULL=>"", "01" => "01 Cadmium plated steel", "02" => "02 Chromium plated steel", "03" => "03  Galvanized iron", "04" => "04 Lead-plated or leaded steel", "05" => "05 Mild, carbon, or construction steel", "06" => "06 Stainless steel", "07" => "07 Another type of steel?", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_84", array("q8_83_e{@}=={@}01_yes"), "You must specify kind of steel");
		$this->addTextAreaElementRD('q8_84other', $this->indent . 'If you selected [Another type of steel], please specify:');
		$this->XINRegisterRule("q8_84other", array("q8_84{@}=={@}07"), "You must specify another", "q8_84other_group"); 
		$this->form->addElement('static', null, "<br/>");


		//q8_85
		$this->form->addElement("select", "q8_85", "8-85 What type of welding or flame cutting did {you/they/you and those who weld or flame cut around you} do?",  array(NULL=>"", "01" => "01 Oxygas, oxyfuel, or oxyacetylene", "02" => "02 MIG (Metal Inert Gas)", "03" => "03  TIG (Tungsten Inert Gas)", "04" => "04 Stick electrode", "05" => "05 Resistance", "06" => "06 Solid state", "07" => "07 Plasma arc", "08" => "08 Submerged arc", "09" => "09 Something else", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_85", array("q8_85{@}=={@}NEVER_REQUIRED")); 
		$this->addTextAreaElementRD('q8_85other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule("q8_85other", array("q8_85{@}=={@}09"), "You must specify something else", "q8_85other_group");
		$this->form->addElement('static', null, $this->indent . "If you selected [Yes] to [8-82 part a or b], go to 8-86, 8-87, 8-88, and 8-89");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_86
		$this->form->addElement('static', null, "8-86 What did {you/they/you and those who solder or braze around you} solder or braze? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Pipes", "b"=>"b) Electrical or electronic parts", "c"=>"c) Other");
		reset($list); 

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_86_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_86_{$field}", array("q8_86_{$field}{@}=={@}NEVER_REQUIRED"));
		}

		$this->addTextAreaElementRD('q8_86other', $this->indent . 'If you selected [Other], please specify:');
		$this->XINRegisterRule("q8_86other", array("q8_86_c{@}=={@}01_yes"), "You must specify other", "q8_86other_group");
		$this->form->addElement('static', null, "<br/>");


		//q8_87
		$this->form->addElement("select", "q8_87", "8-87 Did {you/they/you and those who solder or braze around you} use lead-free solder?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_87", array("q8_87{@}=={@}NEVER_REQUIRED"));
		$this->form->addElement('static', null, "<br/>");


		//q8_88
		$this->form->addElement("select", "q8_88", "8-88 Did the solder usually contain any unusual ingredients such as cadmium, silver, copper, nickel, zinc, arsenic, beryllium, antimony, indium, or bismuth?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_88", array("q8_88{@}=={@}NEVER_REQUIRED"));
		$this->form->addElement('static', null, "<br/>");
		$this->addTextAreaElementRD('q8_88specify', $this->indent . 'If you selected [Yes], please specify:');
		$this->XINRegisterRule("q8_88specify", array("q8_88{@}=={@}01_yes"), "You must specify ingredients", "q8_88specify_group");
		$this->form->addElement('static', null, "<br/>");


		//q8_89
		$this->form->addElement('static', null, "8-89 What did {you/they/you and those who solder or braze around you} solder or braze? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Brass", "b"=>"b) Bronze", "c"=>"c) Cast iron", "d"=>"d) Copper", "e"=>"e) Nickel",  "f"=>"f) Other types of iron",  "g"=>"g) Stainless steel",  "h"=>"h) Other steel");

		reset($list);
		while(list($field, $label) = each($list)){

			$this->form->addElement("select", "q8_89_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_89_{$field}", array("q8_89_{$field}{@}=={@}NEVER_REQUIRED"));
		}

		$this->addTextAreaElementRD('q8_89otheriron', $this->indent . 'If you selected [f) Other types of iron], please specify:');
		$this->XINRegisterRule("q8_89otheriron", array("q8_89_f{@}=={@}01_yes"), "You must specify other iron", "q8_89otheriron_group");
		$this->addTextAreaElementRD('q8_89othersteel', $this->indent . 'If you selected [h) Other steel], please specify:');
		$this->XINRegisterRule("q8_89othersteel", array("q8_89_h{@}=={@}01_yes"), "You must specify other steel", "q8_89othersteel_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If you selected [Yes] to [8-32 part g], go to Wood Dust Module");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: WOOD DUST");
		$this->form->addElement('static', null, "<br/>");


		//q8_90
		$this->form->addElement('static', null, "8-90 Did you typically do any of the following? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Saw wood", "b"=>"b) Sand wood", "c"=>"c) Machine or make wood parts", "d"=>"d) Use a wood chipper", "e"=>"e) Other activities that generate wood",  "f"=>"f) None of these");

		foreach ($list as $field=>$label)
		{
			$this->form->addElement("select", "q8_90_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_90_{$field}", array("q8_90_{$field}{@}=={@}NEVER_REQUIRED"));

		}

		$this->addTextAreaElementRD('q8_90other', $this->indent . 'If you selected [Other activities that generate wood] then please specify:');
		$this->XINRegisterRule("q8_90other", array("q8_90_e{@}=={@}01_yes"), "You must specify other activity(ies)", "q8_90other_group");
		$this->form->addElement('static', null, $this->indent . "If you selected [None of these], [go to 8-92]");
		$this->form->addElement('static', null, $this->indent . "If you selected [Refused] or [Don't Know] to [part a-f] then [go to 8-92]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_91
		$this->form->addElement('static', null, "8-91 How often did you do these things?");
		$this->form->addElement('static', null, "<i>Probe: How many hours per day, per week, or per month do you saw wood, sand wood, do machining, make wood parts, use a wood chipper, or other activities that generate wood dust?</i>");
		$this->form->addElement('static', null, "<br/>");

		foreach ($list as $field=>$label)
		{
			$this->form->addElement('select', "q8_91_{$field}", "{$label}:",  array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->addTextAreaElementRD("q8_91_other{$field}", $this->indent . 'Number:');
			$this->XINRegisterRule("q8_91_{$field}", array("q8_90_{$field}{@}=={@}01_yes"), "You must specify frequency");
			$this->XINRegisterRule("q8_91_other{$field}", array("q8_91_{$field}{@}=={@}01|02|03|04"), "You must specify number", "q8_91_other{$field}_group");
		}

		$this->form->addElement('static', null, "<br/>");


		//q8_92
		$this->form->addElement("select", "q8_92", "8-92 Did your job typically involve handling treated lumber, that is wood treated with chemical preservatives and has a greenish appearance?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_92", array("q8_92{@}=={@}NEVER_REQUIRED"));
		$this->form->addElement('static', null, $this->indent . "If you selected [No] or [Refused] or [Don't Know], end Wood Module");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_93
		$this->form->addElement('static', null, "8-93 What did you do with the treated wood or lumber? Did you...Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Handle it, carry it, or move it", "b"=>"b) Saw or cut it", "c"=>"c) Sand it", "d"=>"d) Something else?", "e"=>"e) None of these");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_93_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_93_{$field}", array("q8_92{@}=={@}01_yes"), "You must specify an activity");
		}

		$this->addTextAreaElementRD('q8_93other', $this->indent . 'If you selected [Something else?], please specify:');
		$this->XINRegisterRule("q8_93other", array("q8_93_d{@}=={@}01_yes"), "You must specify something else", "q8_93other_group");
		$this->form->addElement('static', null, "<br/>");


		//q8_94
		$this->form->addElement("select", "q8_94", "8-94 When you handled the treated wood, was it usually wet or dry?",  array(NULL=>"", "01_wet" => "01 Wet", "02_dry" => "02 Dry", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_94", array("q8_92{@}=={@}01_yes"), "You must specify if wet or dry");
		$this->form->addElement('static', null, "<br/>");


		//q8_95
		$this->form->addElement("select", "q8_95", "8-95 Did you apply a preservative, such as cresotoe, to the wood yourself?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_95", array("q8_92{@}=={@}01_yes"), "You must specify if applied preservative");
		$this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 8-97");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_96
		$this->form->addElement('static', null, "8-96 What preservatives did you use to treat the wood? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Pentachlorophenol or PCP", "b"=>"b) Inorganic chemicals, such as copper chromium, arsenate, also called CCA or ACA", "c"=>"c) Creosote", "d"=>"d) Something else");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_96_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_96_{$field}", array("q8_95{@}=={@}01_yes"), "You must specify preservative(s)");
		}

		$this->addTextAreaElementRD('q8_96other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule("q8_96other", array("q8_96_d{@}=={@}01_yes"), "You must specify something else", "q8_96other_group");
		$this->form->addElement('static', null, "<br/>");


		//q8_97

		$this->form->addElement('select', "q8_97", "8-97 How often did you handle treated wood?",  array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<i>Probe: How many hours per day, per week, or per month did you handle treated wood?</i>");
		$this->XINRegisterRule("q8_97", array("q8_92{@}=={@}01_yes"), "You must specify frequency");
		$this->addTextAreaElementRD("q8_97_number", $this->indent . 'Number:');
		$this->XINRegisterRule("q8_97_number", array("q8_97{@}=={@}01|02|03|04"), "You must specify number", "q8_97_number_group");
	

		$this->form->addElement('static', null, "<b><i>When all Modules are complete go to END of INTERVIEW.</i></b>");
		$this->form->addElement('static', null, "<br/>");



	} //end function _page26() =====================================================


	
	function rulesPage26($fields)
	{

		$errors = array();

		$options = array("a", "b", "c", "d", "e", "f", "g", "h");


                $db =& Database::singleton();


                $db->selectRow("SELECT q8_32_e, q8_32_f, q8_32_g FROM EARLI_interview_PART_3 WHERE CommentID='".$this->getCommentID()."'", $answer);


                if ($answer["q8_32_e"] == "01_yes")
                {
                        if(empty($fields["q8_76"]))
                                $errors["q8_76"] = "You must specify";
                        if(empty($fields["q8_80"]))
                                $errors["q8_80"] = "You must specify";
                }


                if ($answer["q8_32_f"] == "01_yes")
                {
			for ($i=0; $i<6; $i++)
			{
                        	if(empty($fields["q8_82_$options[$i]"]))
                                	$errors["q8_82_$options[$i]"] = "You must specify";
			}
		}

		for ($i=0; $i<5; $i++)
		{
			if ($fields["q8_82_$options[$i]"] == "01_yes")
			{

				if (empty($fields["q8_85"]))
					$errors["q8_85"] = "You must specify";

				for ($j=0; $j<7; $j++)
				{
					if (empty($fields["q8_83_$options[$j]"]))
						$errors["q8_83_$options[$j]"] = "You must specify";

				}
			break;
			}	
		}	

	
                if ($answer["q8_32_g"] == "01_yes")
                {
			for ($i=0; $i<6; $i++)
			{
                        	if(empty($fields["q8_90_$options[$i]"]))
                                	$errors["q8_90_$options[$i]"] = "You must specify";
			}
		}


		if($fields["q8_83_a"] == "01_yes" || $fields["q8_83_b"] == "01_yes")
		{
			for ($i=0; $i<3; $i++)
			{
				if(empty($fields["q8_86_$options[$i]"]))
					$errors["q8_86_$options[$i]"] = "Required if selected yes for aluminum, brass, or bronze";
			}

			if(empty($fields["q8_87"]))
				$errors["q8_87"] = "Required if selected yes to aluminum, brass, or bronze";

			if(empty($fields["q8_88"]))
				$errors["q8_88"] = "Required if selected yes to aluminum, brass, or bronze";

			for ($i = 0; $i<8; $i++)
			{
				if(empty($fields["q8_89_$options[$i]"]))
					$errors["q8_89_$options[$i]"] = "Required if selected yes to aluminum, brass, or bronze";
			}
		}


                if ($answer["q8_32_g"] == "01_yes")
                {
			for ($i=0; $i<6; $i++)
			{
                        	if(empty($fields["q8_90_$options[$i]"]))
                                	$errors["q8_90_$options[$i]"] = "You must specify";
			}
			
			if (empty($fields["q8_92"]))
                        	$errors["q8_92"] = "You must specify";
			
                }


		return $errors;
	}


	function _page27(){   // ========================================================

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('header', null, "<b/>OCCUPATION MODULE: Generic Exposure Module (GE)");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: PHOTOCOPYING/LASER JET PROXIMITY");
		$this->form->addElement('static', null, "<br/>");


		//function with more xcomplex rules
		$this->form->addFormRule(array(&$this, 'rulesPage27'));

		//q8_98
		$this->form->addElement("select", "q8_98", "8-98 Did this job require that you regularly stand at a photocopier for more than 1 hour per day?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_98", array("q8_98{@}=={@}NEVER_REQUIRED"));
		$this->form->addElement('static', null, "<br/>");


		//q8_99
		$this->form->addElement("select", "q8_99", "8-99 Did this job require that you sit within 10 feet of an operating laser jet printer for more than 1 hour per day?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_99", array("q8_99{@}=={@}NEVER_REQUIRED"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_100
		$this->form->addElement('static', null, "8-100 Between [-3] and DOBS, did you work with or near any of the following at this job/school? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Chemicals", "b"=>"b) Work-generated dust", "c"=>"c) Metal fumes (such as from welding or grinding)", "d"=>"d) Bacteria or viruses", "e"=>"e) Animals (dogs, cats, cattle, pigs, ect)", "f"=>"f) Radiation");
	
		foreach ($list as $field=>$label)
		{	
			$this->form->addElement("select", "q8_100_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_100_{$field}", array("q8_100_{$field}{@}=={@}NEVER_REQUIRED"));
		}

		$this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] for [for 8-100 for all], go to 8-104");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_101
		$this->form->addElement('static', null, "8-101 Please tell me the name of each chemical/dust/bacteria or virus/animal/radiation you worked with or near.");

		$chemicals = array("a"=>"a) Chemical Name", "b"=>"b) Dust", "c"=>"c) Metal fumes", "d"=>"d) Bacteria or Virus Name", "e"=>"e) Animals Name", "f"=>"f) Radiation Name");

		foreach ($chemicals as $key=>$value)
		{
			$this->addTextAreaElementRD("q8_101_{$key}", $this->indent . "{$value}");
			$this->XINRegisterRule("q8_101_{$key}", array("q8_100_{$key}{@}=={@}01_yes"), "You must specify name", "q8_101_{$key}_group");
		}
		
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_102
		$this->form->addElement('static', null, "8-102 How did you work with that chemical/dust/virus/animal/radiation? If you did not personally work with or use it, just say you worked near it.");
		

		foreach($chemicals as $key=>$value)
                {
                        $this->addTextAreaElementRD("q8_102_{$key}", $this->indent . "{$value}");
			$this->XINRegisterRule("q8_102_{$key}", array("q8_100_{$key}{@}=={@}01_yes"), "You must specify type of work", "q8_102_{$key}_group");
                }

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_103
		$this->form->addElement('static', null, "8-103 How many hours per week did you work with or near it? This is actual time, not including time spent on breaks and lunch, and other work activities where you don't use or are not near. Code all that apply:");
		$this->form->addElement('static', null, "<br/>");


		foreach ($list as $field=>$label)
		{
			$this->form->addElement("select", "q8_103_{$field}", "{$label}",  array(NULL=>"", "01" => "01 Less than 1 hour per week", "02" => "02 1-10 hours per week", "03" => "03  11-20 hours per week", "04" => "04 21-40 hours per week", "05" => "05 More than 40 hours per week", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->XINRegisterRule("q8_103_{$field}", array("q8_100_{$field}{@}=={@}01_yes"), "You must specify hours per week");
		}

		$this->form->addElement('static', null, $this->indent . "If you selected [Yes] to [8-100 part c], go to Soldering and Welding Module");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: SOLDERING AND WELDING");
		$this->form->addElement('static', null, "<br/>");


		//q8_104
		$this->form->addElement('static', null, "8-104 Did you do any of the following? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Soldering or brazing", "b"=>"b) Smell fumes from others who solder or braze", "c"=>"c) Welding or flame cutting", "d"=>"d) Smell fumes from others who weld or flame cut,", "e"=>"e) Some other welding or soldering method?",  "f"=>"f) None of the above");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_104_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_104_{$field}", array("q8_104_{$field}{@}=={@}NEVER_REQUIRED"));
		}

		$this->addTextAreaElementRD('q8_104other', $this->indent . 'If you selected [Some other welding or soldering method?], please specify:');
		$this->XINRegisterRule("q8_104other", array("q8_104_e{@}=={@}01_yes"), "You must specify other", "q8_104other_group");
		$this->form->addElement('static', null, $this->indent . "If you selected [None of the above], go to 8-112");
		$this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] for 8-104 for <u>all</u>, go to 8-112");
		$this->form->addElement('static', null, $this->indent . "If you selected [Yes] for [8-104 part a, or b], go to 8-105, 8-106, 8-107, 8-108");
		$this->form->addElement('static', null, $this->indent . "Otherwise, go to 8-111a");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_105
		$this->form->addElement('static', null, "8-105 What types of metal did {you/they/you and those who weld or flame cut around you} weld or flame cut? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Aluminum", "b"=>"b) Brass or bronze", "c"=>"c) Cast iron", "d"=>"d) Copper", "e"=>"e) Steel",  "f"=>"f) Titanium-based alloy",  "g"=>"g) Other");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_105_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_105_{$field}", array("q8_105_{$field}{@}=={@}NEVER_REQUIRED"));

		}

		$this->addTextAreaElementRD('q8_105other', $this->indent . 'If you selected [Other], please specify:');
		$this->XINRegisterRule("q8_105other", array("q8_105_g{@}=={@}01_yes"), "You must specify other", "q8_105other_group");
		$this->form->addElement('static', null, $this->indent . "If you selected [Yes] to [a-d], [go to 8-107]");
		$this->form->addElement('static', null, $this->indent . "If you selected [Yes] to [f-g], [go to 8-107]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_106
		$this->form->addElement("select", "q8_106", "8-106 What kind of steel was it?",  array(NULL=>"", "01" => "01 Cadmium plated steel", "02" => "02 Chromium plated steel", "03" => "03  Galvanized iron", "04" => "04 Lead-plated or leaded steel", "05" => "05 Mild, carbon, or construction steel", "06" => "06 Stainless steel", "07" => "07 Another type of steel?", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_106", array("q8_105_e{@}=={@}01_yes"), "You must specify kind of steel");
		$this->addTextAreaElementRD('q8_106other', $this->indent . 'If you selected [Another type of steel?], please specify:');
		$this->XINRegisterRule('q8_106other', array("q8_106{@}=={@}07"), "You must specify other", "q8_106other_group");
		$this->form->addElement('static', null, "<br/>");


		//q8_107
		$this->form->addElement("select", "q8_107", "8-107 What type of welding or flame cutting did {you/they/you and those who weld or flame cut around you} do?",  array(NULL=>"", "01" => "01 Oxygas, oxyfuel, or oxyacetylene", "02" => "02 MIG (Metal Inert Gas)", "03" => "03  TIG (Tungsten Inert Gas)", "04" => "04 Stick electrode (shielded metal arc welding)", "05" => "05 Resistance, such as sport, seam, flash, butt, and projection", "06" => "06 Solid state, such as friction or roll", "07" => "07 Plasma arc", "08" => "08 Submerged arc", "09" => "09 Something else", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_107", array("q8_107{@}=={@}NEVER_REQUIRED"));
		$this->form->addElement('static', null, $this->indent . "If you selected [Yes] to [part a or b for 8-104], go to 8-108, 8-109, 8-110, 8-111");
		$this->form->addElement('static', null, $this->indent . "Otherwise, go to 8-111a");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_108
		$this->form->addElement('static', null, "8-108 What did {you/they/you and those who solder or braze around you} solder or braze? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Pipes", "b"=>"b) Electrical or electronic parts", "c"=>"c) Other");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_108_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_108_{$field}", array("q8_108_{$field}{@}=={@}NEVER_REQUIRED"));
		}

		$this->addTextAreaElementRD('q8_108other', $this->indent . 'If you selected [Other], please specify:');
		$this->XINRegisterRule('q8_108other', array("q8_108_c{@}=={@}01_yes"), "You must specify other", "q8_108other_group");
		$this->form->addElement('static', null, "<br/>");


		//q8_109
		$this->form->addElement("select", "q8_109", "8-109 Did {you/they/you and those who solder or braze around you} use lead-free solder?", array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_109", array("q8_109{@}=={@}NEVER_REQUIRED"));
		$this->form->addElement('static', null, "<br/>");


		//q8_110
		$this->form->addElement("select", "q8_110", "8-110 Did the solder usually contain any unusual ingredients such as cadmium, silver, copper, nickel, zinc, arsenic, beryllium, antimony, indium, or bismuth?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_110", array("q8_110{@}=={@}NEVER_REQUIRED"));
		$this->addTextAreaElementRD('q8_110other', $this->indent . 'If you selected [Yes] then please specify:');
		$this->XINRegisterRule('q8_110other', array("q8_110{@}=={@}01_yes"), "You must specify ingredients", "q8_110other_group");
		$this->form->addElement('static', null, "<br/>");


		//q8_111
		$this->form->addElement('static', null, "8-111 What did {you/they/you and those who solder or braze around you} solder or braze? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Brass", "b"=>"b) Bronze", "c"=>"c) Cast iron", "d"=>"d) Copper", "e"=>"e) Nickel",  "f"=>"f) Other types of iron",  "g"=>"g) Stainless steel",  "h"=>"h) Other steel",  "i"=>"i) Other");

		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_111_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_111_{$field}", array("q8_111_{$field}{@}=={@}NEVER_REQUIRED"));
		}

		$this->addTextAreaElementRD('q8_111otheriron', $this->indent . 'If you selected [Other types of iron], please specify:');
		$this->XINRegisterRule('q8_111otheriron', array("q8_111_f{@}=={@}01_yes"), "You must specify other iron", "q8_111otheriron_group");
		$this->addTextAreaElementRD('q8_111othersteel', $this->indent . 'If you selected [Other steel], please specify:');
		$this->XINRegisterRule('q8_111othersteel', array("q8_111_h{@}=={@}01_yes"), "You must specify other steel", "q8_111othersteel_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_111a
		$this->form->addElement('static', null, "8-111a How often did you use the following metals?");
		$this->form->addElement('static', null, "<i>Probe: How many hours per day, per week or per month do you use the following metals?</i>");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Brass", "b"=>"b) Bronze", "c"=>"c) Cast iron", "d"=>"d) Copper", "e"=>"e) Nickel",  "f"=>"f) Other types of iron",  "g"=>"g) Stainless steel",  "h"=>"h) Other steel",  "i"=>"i) Other");

		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement('select', "q8_111a_{$field}", "{$label}:", array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->XINRegisterRule("q8_111a_{$field}", array("q8_104_f{@}!={@}01_yes", "q8_104_f{@}!={@}"), "You must specify");
			$this->addTextAreaElementRD("q8_111a_other{$field}", $this->indent . 'Number:');
			$this->XINRegisterRule("q8_111a_other{$field}", array("q8_111a_{$field}{@}=={@}01|02|03|04"), "You must specify number", "q8_111a_other{$field}_group");
		}

		$this->form->addElement('static', null, $this->indent . "If you selected [Yes] to any in part a-f 8-100, go to Clean Hands Module 8-112");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: CLEAN HANDS");
		$this->form->addElement('static', null, "<br/>");


		//q8_112
		$this->form->addElement("select", "q8_112", "8-112 Did you regularly get chemicals or dust on your hands or skin?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_112", array("q8_112{@}=={@}NEVER_REQUIRED"));
		$this->form->addElement('static', null, $this->indent . "If you selected [No], end Module and go to 8-115");
		$this->form->addElement('static', null, "<br/>");


		//q8_113
		$this->form->addElement('static', null, "8-113 When you had chemicals or dust on your hands, when did you wash your hands? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) When taking a break at work", "b"=>"b) Before eating", "c"=>"c) Before smoking", "d"=>"d) At the end of the work shift", "e"=>"e) When the task is completed",  "f"=>"f) Whenever I get my hands dirty",  "g"=>"g) Don't wash hands");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_113_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_113_{$field}", array("q8_112{@}=={@}01_yes"), "You must specify when hands were washed");
		}

		$this->form->addElement('static', null, $this->indent . "If you selected [Don't wash hands], end Module and go to 8-115");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_114
		$this->form->addElement('static', null, "8-114 What did you use to wash chemicals or dust off your hands? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Soap and water or water only", "b"=>"b) [Goop] or similar cleaners", "c"=>"c) Mineral spirits, turpentine, or paint thinner", "d"=>"d) Gasoline or kerosene", "e"=>"e) Something else");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_114_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_114_{$field}", array("q8_113{@}!={@}g", "q8_112{@}!={@}02"), "You must specify when hands were washed");
		}

		$this->addTextAreaElementRD('q8_114other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule('q8_114other', array("q8_114_e{@}=={@}01_yes"), "You must specify something else", "q8_114other_group");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: FUEL AND EXHAUST SMELLS");
		$this->form->addElement('static', null, "<br/>");


		//q8_115
		$this->form->addElement("select", "q8_115", "8-115 Did you regularly smell fuel vapors, such as from gas or fuel tanks, or exhaust vapors, such as from car or truck tail pipes?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_115", array("q8_115{@}=={@}NEVER_REQUIRED"));
		$this->form->addElement('static', null, $this->indent . "If you selected [No], end Module and go to 8-117");
		$this->form->addElement('static', null, "<br/>");


		//q8_116
		$this->form->addElement("select", "q8_116", "8-116 How strong was the smell?",  array(NULL=>"", "01" => "01 Slight", "02" => "02 Moderate", "03" => "03  Strong", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_116", array("q8_115{@}=={@}01_yes"), "You must specify");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: PERSONAL PROTECTIVE EQUIPMENT");
		$this->form->addElement('static', null, "<br/>");


		//q8_117
		$this->form->addElement("select", "q8_117", "8-117 Between [-3] and DOBS, how often did you wear or use personal protective equipment (PPE) to protect you from the things you have mentioned? By personal protective equipment, I mean the things like gloves, dust mask, goggles, aprons, lab coats or other protective clothing, would you say always, often, rarely, or never us personal protective equipment?",  array(NULL=>"", "01" => "01 Always", "02" => "02 Often", "03" => "03  Rarely", "04" => "04 Never", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_117", array("q8_117{@}=={@}NEVER_REQUIRED"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If you selected [Never], end Module and go to BOX-GE");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_119
		$this->form->addElement('static', null, "8-119 Which type of protective clothing or equipment did you wear? Code all that apply:");
		$this->form->addElement('static', null, "<i>PROBE: Any other protective clothing or equipment?</i>");
		$this->form->addElement('static', null, "<br/>");

		foreach ($this->protectiveEquipment as $field=>$label)
		{
			$this->form->addElement("select", "q8_119_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_119_{$field}", array("q8_117{@}!={@}04"), "Required if used protective equipment");
		}

		$this->addTextAreaElementRD('q8_119other', $this->indent . 'If you selected [Other], please specify:');
		$this->XINRegisterRule('q8_119other', array("q8_119_h{@}=={@}01_yes"), "You must specify other", "q8_119other_group");
		$this->form->addElement('static', null, $this->indent . "If you selected [Yes] to [part E in 8-119], go to 8-120");
		$this->form->addElement('static', null, $this->indent . "Otherwise end Module and go to BOX-GE");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_120
		$this->form->addElement("select", "q8_120", "8-120 What type of respirator was it?",  array(NULL=>"", "01" => "01 A half-mask chemical cartridge respirator", "02" => "02 A full-mask chemical cartridge respirator", "03" => "03  An air-supplied or SCBA respirator", "04" => "04 Some other kind of respirator?", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_120", array("q8_119_e{@}=={@}01_yes"), "You must specify type of respirator");
		$this->addTextAreaElementRD('q8_120other', $this->indent . 'If you selected [Some other kind of respirator], please specify:');
		$this->XINRegisterRule('q8_120other', array("q8_120{@}=={@}04"), "You must specify some other kind of respirator", "q8_120other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<b/>BOX-GE");
		$this->form->addElement('static', null, "If you selected [Yes] to any in [part A-F in 8-100] <u>and</u> [Yes] to [any in 01 to 12 in 8-8] <u>or</u> [Yes] to [8-115], go to Ventilation and Enclosure Module - starts in 8-121");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: VENTILATION & ENCLOSURES");
		$this->form->addElement('static', null, "<br/>");


		//q8_121
		$this->form->addElement("select", "q8_121", "8-121 Was there any kind of a ventilation system to remove exhaust, dust, smoke or fumes from the area?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_121", array("q8_121{@}=={@}NEVER_REQUIRED"));
		$this->form->addElement('static', null, "<i>Probe: By ventilation system we mean purposely opening windows or doors, using a fume hood, or other ventilation system.</i>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused], [Don't Know], end Module and go to 8-123");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_122
		$this->form->addElement('static', null, "8-122 What ventilation systems were present to remove exhaust, dust, smoke or fumes from the area? Are there...Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		foreach ($this->ventilators as $field=>$label)
		{
			$this->form->addElement("select", "q8_122_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_122_{$field}", array("q8_121{@}=={@}01_yes"), "Required if there was a ventilation system");
		}

		$this->addTextAreaElementRD('q8_122other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule('q8_122other', array("q8_122_f{@}=={@}01_yes"), "You must specify something else", "q8_122other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_123
		$this->form->addElement("select", "q8_123", "8-123 Between [-3] and DOBS, were any chemical leaks or spills, unusual or strong odors, dusty conditions or any other non-routine exposure events at this job/school?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_123", array("q8_123{@}=={@}NEVER_REQUIRED"));
		$this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know], go to 8-13");
		$this->form->addElement('static', null, "<br/><br />");


		//q8_124
		$this->addTextAreaElementRD('q8_124', "8-124 Please briefly describe the event. What happened?");
		$this->XINRegisterRule("q8_124", array("q8_123{@}=={@}01_yes"), "Required if there were any of the above conditions", "q8_124_group");
		$this->form->addElement('static', null, $this->indent . "If you selected [Refused] or [Don't Know], go to 8-13");
		$this->form->addElement('static', null, "<br/><br />");


		//q8_125
		$this->form->addElement("select", "q8_125", "8-125 Were you hospitalized?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_125", array("q8_124_status{@}=={@}", "q8_124{@}!={@}"), "Required if there were any of the above conditions");
		$this->form->addElement('static', null, "<br/>");


		//q8_126
		$this->form->addElement("select", "q8_126", "8-126 Are you ok now?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_126", array("q8_124_status{@}=={@}", "q8_124{@}!={@}"), "Required if there were any of the above conditions");
		$this->form->addElement('static', null, "<br/><br />");
		$this->form->addElement('static', null, "<b/>When Generic Exposure Module complete and there are NO more Occupational Modules to Complete listed in the Occupational Coding Box, go to 8-13");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


	} //end function _page27() =====================================================



	function rulesPage27($fields)
	{

		$errors = array();

		$db =& Database::singleton();

		$db->selectRow("SELECT q8_5, q8_6_9 FROM EARLI_interview_PART_3 WHERE CommentID='".$this->getCommentID()."'", $occupation); 

		$options = array("a", "b", "c", "d", "e", "f", "g", "h");

                if($occupation["q8_5"] == "09" && ($occupation["q8_6_9"] >= "42" && $occupation["q8_6_9"] <= "55"))
                {
                        if (empty($fields["q8_98"]))
                                $errors["q8_98"] = "You must specify";
                        if (empty($fields["q8_99"]))
                                $errors["q8_99"] = "You must specify";

                        for ($i=0; $i<6; $i++)
                        {
                                if (empty($fields["q8_100_$options[$i]"]))
                                        $errors["q8_100_$options[$i]"] = "You must specify";
                        }
			
			for ($i=0; $i<6; $i++)
			{
                        	if (empty($fields["q8_104_$options[$i]"]))
                                	$errors["q8_104_$options[$i]"] = "You must specify";
			}

                }


                if($fields["q8_104_a"] == "01_yes" || $fields["q8_104_b"] == "01_yes")
                {
                        for ($i = 0; $i<7; $i++)
                        {
                                if(empty($fields["q8_105_$options[$i]"]))
                                        $errors["q8_105_$options[$i]"] = "You must specify";
                        }

                        if(empty($fields["q8_107"]))
                                $errors["q8_107"] = "You must specify";


                        for ($i = 0; $i<3; $i++)
			{
                        	if(empty($fields["q8_108_$options[$i]"]))
                                	$errors["q8_108_$options[$i]"] = "You must specify";
			}

                        if(empty($fields["q8_109"]))
                                $errors["q8_109"] = "You must specify";


                        if(empty($fields["q8_110"]))
                                $errors["q8_110"] = "You must specify";


                        for ($i=0; $i<9; $i++)
			{
                        	if(empty($fields["q8_111_$options[$i]"]))
                                	$errors["q8_111_$options[$i]"] = "You must specify";
			}
                }


                for ($i=0; $i<6; $i++)
                {
                        if($fields["q8_104_$options[$i]"] == "01_yes")
                        {
                                if(empty($fields["q8_112"]))
                                        $errors["q8_112"] = "You must specify";

                                if(empty($fields["q8_115"]))
                                        $errors["q8_115"] = "You must specify";

                                if(empty($fields["q8_117"]))
                                {
                                        $errors["q8_117"] = "You must specify";
                                        break;
                                }


                        }
                }

		$condition = false;	

		for ($i=0; $i<6; $i++)
		{
			if ($fields["q8_100_$options[$i]"] == "01_yes")
			{
				if (empty($fields["q8_117"]))
					$errors["q8_117"] = "You must specify";

				if (empty($fields["q8_123"]))
					$errors["q8_123"] = "You must specify";
	
				for ($j=0; $j<12; $j++)
				{
					if ($j<10)
					{
						if (($fields["q8_8"] == "0" + $j) && empty($fields["q8_121"]))
						{
							$errors["q8_121"] = "You must specify";
							$condition = true;
							break;
						}
					}

					else
					{
						if (($fields["q8_8"] == $j) && empty($fields["q8_121"]))
						{
							$errors["q8_121"] = "You must specify";
							$condition = true;
							break;
						}
					}
				}		

			}

			if ($condition == true)
				break;
		}

		return $errors;
	}



	function _page28(){   // ========================================================

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>OCCUPATION MODULE: Health Professional (HP)");
		$this->form->addElement('static', null, "<br/>");


		//function with more complex rules
		$this->form->addFormRule(array(&$this, 'rulesPage28'));


                //q8_127
                $this->form->addElement('static', null, "8-127 Between [-3] and DOBS, did you work in any areas where the following activities take place? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
                $activities = array("a"=>"a) General anesthetic gases are used or administered", "b"=>"b) Instruments or other equipment are sterilized", "c"=>"c) Anti-neoplastic or anti-cancer drugs are mixed", "d"=>"d) Disinfectants or antiseptics are used", "e"=>"e) In a laboratory",  "f"=>"f) X-rays or other diagnostic or therapeutic work involving radiation takes place",  "g"=>"g) Animals are present or treated");

		foreach ($activities as $field=>$label)
		{
                        $this->form->addElement("select", "q8_127_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_127_{$field}", array("q8_127_{$field}{@}=={@}NEVER_REQUIRED"));
                }

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box HP-1");
		$this->form->addElement('static', null, "If you selected [Yes] to [part a in 8-127], go to 8-128 and 8-129");
		$this->form->addElement('static', null, "Otherwise [go to Box HP-2]");
		$this->form->addElement('static', null, "If you selected [No], [Refused] or [Don't Know] for [part a-g in 8-127], go to Box HP-16");
		$this->form->addElement('static', null, "<br/>");
		

		//q8_128
		$this->form->addElement('static', null, "8-128 Between [-3] and DOBS, which anesthetic gases were used while you were in the area? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Nitrous oxide", "b"=>"b) Halothane", "c"=>"c) Ether", "d"=>"d) Fluorane", "e"=>"e) Etherane",  "f"=>"f) Chloroform",  "g"=>"g) Some other anesthetic gas");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_128_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_128_{$field}", array("q8_127_a{@}=={@}01_yes"), "You must specify anesthetic gases");
		}

		$this->addTextAreaElementRD('q8_128other', $this->indent . 'If you selected [Some other anesthetic gas], please specify:');
		$this->XINRegisterRule('q8_128other', array("q8_128_g{@}=={@}01_yes"), "You must specify other", "q8_128other_group");
		$this->form->addElement('static', null, "<br/>");

		
		//q8_129
		$this->form->addElement("select", "q8_129", "8-129 How many hours per week did you work in an area where anesthetic gases are being used? This is actually time, not including time spent on breaks and lunch, and other work activities where you don't use or are not near.",  array(NULL=>"", "01" => "01 Less than 1 hour per week", "02" => "02 1-10 hours per week", "03" => "03  11-20 hours per week", "04" => "04 21-40 hours per week", "05" => "05 More than 40 hours per week", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_129", array("q8_127_a{@}=={@}01_yes"), "You must specify time");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box HP-2");
		$this->form->addElement('static', null, "If you selected [Yes] to [part b in 8-127], go to 8-130");
		$this->form->addElement('static', null, "Otherwise [go to Box HP-4]");
		$this->form->addElement('static', null, "<br/><br />");


		//q8_130
		$this->form->addElement("select", "q8_130", "8-130 Where instruments or other equipment are sterilized, how were they sterilized?",  array(NULL=>"", "01" => "01 In an autoclave or sterilizing unit that uses only steam or water", "02" => "02 In an autoclave or sterilizing unit that uses ethylene oxide", "03" => "03  In a liquid solution", "04" => "04 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_130", array("q8_127_b{@}=={@}01_yes"), "You must specify sterilization method");
		$this->addTextAreaElementRD('q8_130other', $this->indent . 'If you selected [Other], please specify:');
		$this->XINRegisterRule('q8_130other', array("q8_130{@}=={@}04"), "You must specify other", "q8_130other_group");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box HP-3");
		$this->form->addElement('static', null, "If response to [8-130] is [03], go to 8-131");
		$this->form->addElement('static', null, "Otherwise [go to Box HP-4]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_131
		$this->form->addElement('static', null, "8-131 What chemical sterilizing agent was typically used in the solution? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Formaldehyde", "b"=>"b) Phisohex", "c"=>"c) Steris", "d"=>"d) Cidex", "e"=>"e) Another sterilizing agent?", "f"=>"f) Something else");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_131_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_131_{$field}", array("q8_130{@}=={@}03"), "You must specify sterilizing agent");
		}

		$this->addTextAreaElementRD('q8_131other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule('q8_131other', array("q8_131_f{@}=={@}01_yes"), "You must specify something else", "q8_131other_group");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box HP-4");
		$this->form->addElement('static', null, "If you selected [Yes] to [part c in 8-127], go to 8-132");
		$this->form->addElement('static', null, "Otherwise [go to Box HP-5]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_132
		$this->addTextAreaElementRD('q8_132', "8-132 What anti-neoplastic or anti-cancer drugs were used or mixed most often in the area?");
		$this->XINRegisterRule("q8_132", array("q8_127_c{@}=={@}01_yes"), "You must specify anti-neoplastic or anti-cancer drugs", "q8_132_group");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box HP-5");
		$this->form->addElement('static', null, "If you selected [Yes] to [part d in 8-127], go to 8-133");
		$this->form->addElement('static', null, "Otherwise [go to Box HP-6]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_133
		$this->form->addElement('static', null, "8-133 Between [-3] and DOBS, which disinfectants or antiseptics have you used? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Betadine", "b"=>"b) Duraprep", "c"=>"c) Formaldehyde", "d"=>"d) Hibiclens", "e"=>"e) Iodophor or Iodophorm",  "f"=>"f) Lysol", "g"=>"g) Phisohex or phisoderm", "h"=>"h) Skin prep or alcohol pads", "i"=>"i) Something else");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_133_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_133_{$field}", array("q8_127_d{@}=={@}01_yes"), "You must specify disinfectants or antiseptics");
		}


		$this->addTextAreaElementRD('q8_133other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule('q8_133other', array("q8_133_i{@}=={@}01_yes"), "You must specify something else", "q8_133other_group");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box HP-6");
		$this->form->addElement('static', null, "If you selected [Yes] to [part e in 8-127], go to 8-134");
		$this->form->addElement('static', null, "Otherwise [go to Box HP-8]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_134
		$this->form->addElement('static', null, "8-134 Between [-3] and DOBS which of the following were used in the laboratory area in which you work? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Dyes as either a powder past or liquid", "b"=>"b) Solvents", "c"=>"c) Formaldehyde", "d"=>"d) Hibiclens", "e"=>"e) Iodophor or Iodophorm",  "f"=>"f) None");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_134_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_134_{$field}", array("q8_127_e{@}=={@}01_yes"), "You must specify");
		}

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box HP-7");
		$this->form->addElement('static', null, "If you selected [Yes] to [part b in 8-134], go to 8-134a]");
		$this->form->addElement('static', null, "Otherwise [go to Box HP-8]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_134a
		$this->form->addElement('static', null, "8-134a What solvents were used in your laboratory work area? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Acetone", "b"=>"b) Chloroform", "c"=>"c) Ethanol", "d"=>"d) Propanol", "e"=>"e) Toluene",  "f"=>"f) Xylene",  "g"=>"g) Something else");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_134a_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_134a_{$field}", array("q8_134_b{@}=={@}01_yes"), "You must specify solvents");
		}


		$this->addTextAreaElementRD('q8_134a_other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule('q8_134a_other', array("q8_134a_g{@}=={@}01_yes"), "You must specify something else", "q8_134a_other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box HP-8");
		$this->form->addElement('static', null, "If you selected [Yes] to [part g in 8-127], go to 8-135");
		$this->form->addElement('static', null, "Otherwise [go to Box HP-11]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");



		//q8_135
		$this->form->addElement('static', null, "8-135 What types of animals were typically treated in your work area? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Dogs", "b"=>"b) Cats", "c"=>"c) Reptiles (turtles, lizards, snakes)", "d"=>"d) Large animals (horses, cattle, pigs, etc.)", "e"=>"e) Some other animals");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_135_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_135_{$field}", array("q8_127_g{@}=={@}01_yes"), "You must specify animals");
		}

		$this->addTextAreaElementRD('q8_135other', $this->indent . 'If you selected [Some other animals], please specify:');
		$this->XINRegisterRule('q8_135other', array("q8_135_e{@}=={@}01_yes"), "You must specify something else", "q8_135other_group");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box HP-9");
		$this->form->addElement('static', null, "If you selected [Yes] to [part b in 8-135], go to 8-136");
		$this->form->addElement('static', null, "Otherwise [go to Box HP-10]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_136
		$this->form->addElement("select", "q8_136", "8-136 To your knowledge, were you ever infected with the parasite that causes toxoplasmosis?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_136", array("q8_135_b{@}=={@}01_yes"), "You must specify");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>Box HP-10");
		$this->form->addElement('static', null, "If you selected [Yes] to [part c in 8-135], go to 8-137");
		$this->form->addElement('static', null, "Otherwise [go to Box HP-11]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_137
		$this->form->addElement("select", "q8_137", "8-137 To you knowledge, were you ever infected with salmonella from a reptile?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_137", array("q8_135_c{@}=={@}01_yes"), "You must specify");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>Box HP-11");
		$this->form->addElement('static', null, "If you selected [Yes] to [part f in 8-127], go to 8-138");
		$this->form->addElement('static', null, "Otherwise [go to Box HP-12]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_138
		$this->form->addElement('static', null, "8-138 Between [-3] and DOBS did you work near any of the following? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) X-ray equipment", "b"=>"b) Aniography equipment", "c"=>"c) CAT scanning equipment", "d"=>"d) MRI equipment", "e"=>"e) Radioisotopes or radionuclides",  "f"=>"f) Thoroscopy equipment",  "g"=>"g) None of the these");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_138_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_138_{$field}", array("q8_127_f{@}=={@}01_yes"), "You must specify");
		}

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box HP-12");
		$this->form->addElement('static', null, "If you selected [Yes] to [part a-f in 8-138], go to 8-139");
		$this->form->addElement('static', null, "Otherwise [go to Ventilation and Enclosure Module] - starts on 8-148");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_139
		$this->form->addElement('static', null, "8-139 Which of the following did you do in a room when working around this equipment or radioisotopes? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Wear a dosimeter or film badge that measures your radiation", "b"=>"b) Wear a leaded apron", "c"=>"c) Stand behind a leaded barrier or outside the room while the x-ray is taken", "d"=>"d) Something else", "e"=>"e) No action taken"); 
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_139_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused", "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_139_{$field}", array("q8_139_{$field}{@}=={@}NEVER_REQUIRED"));
		}

		$this->addTextAreaElementRD('q8_139other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule('q8_139other', array("q8_139_d{@}=={@}01_yes"), "You must specify something else", "q8_139other_group");
		$this->form->addElement('static', null, "<br/><br />");


		//q8_140
		$this->form->addElement("select", "q8_140", "8-140 Between [-3] and DOBS did you handle blood or tissues or materials contaminated with blood?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_140", array("q8_138_a{@}=={@}01_yes"), "You must specify");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>Box HP-13");
		$this->form->addElement('static', null, "Go to Clean Hands Module - starts on 8-141");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: CLEAN HANDS");
		$this->form->addElement('static', null, "<br/>");


		//q8_141
		$this->form->addElement("select", "q8_141", "8-141 Did you regularly get chemicals or dust on your hands or skin?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_141", array("q8_141{@}=={@}NEVER_REQUIRED"));
		$this->form->addElement('static', null, $this->indent . "If you selected [No], end Module and go to 8-144");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_142
		$this->form->addElement('static', null, "8-142 When you had chemicals or dust on your hands, when did you wash your hands? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) When taking a break at work", "b"=>"b) Before eating", "c"=>"c) Before smoking", "d"=>"d) At the end of the work shift", "e"=>"e) When the task is completed",  "f"=>"f) Whenever I get my hands dirty",  "g"=>"g) Don't wash hands");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_142_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_142_{$field}", array("q8_142{@}=={@}NEVER_REQUIRED"));
		}

		$this->form->addElement('static', null, $this->indent . "If you selected [Don't wash hands], end Module and go to 8-144");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_143
		$this->form->addElement('static', null, "8-143 What did you use to wash chemicals or dust off your hands? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Soap and water or water only", "b"=>"b) [Goop] or similar cleaners", "c"=>"c) Mineral spirits, turpentine, or paint thinner", "d"=>"d) Gasoline or kerosene", "e"=>"e) Something else");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_143_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_143_{$field}", array("q8_143_{$field}{@}=={@}NEVER_REQUIRED"));
		}

		$this->addTextAreaElementRD('q8_143other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule('q8_143other', array("q8_143_e{@}=={@}01_yes"), "You must specify something else", "q8_143other_group");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: PERSONAL PROTECTIVE EQUIPMENT");
		$this->form->addElement('static', null, "<br/>");


		//q8_144
		$this->form->addElement("select", "q8_144", "8-144 Between [-3] and DOBS, how often did you wear or use personal protective equipment (PPE) to protect you from the things you have mentioned? By personal protective equipment, I mean the things like gloves, dust mask, goggles, aprons, lab coats or other protective clothing, would you say always, often, rarely, or never us personal protective equipment?",  array(NULL=>"", "01" => "01 Always", "02" => "02 Often", "03" => "03  Rarely", "04" => "04 Never", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_144", array("q8_144{@}=={@}NEVER_REQUIRED"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If you selected [Never], [Refused], or [Don't Know], end Module and go to 8-148");
		$this->form->addElement('static', null, "<br/><br />");


		//q8_146
		$this->form->addElement('static', null, "8-146 Which type of protective clothing or equipment did you wear? Code all that apply.");
		$this->form->addElement('static', null, "<i>PROBE: Any other protective clothing or equipment?</i>");
		$this->form->addElement('static', null, "<br/>");

		foreach ($this->protectiveEquipment as $field=>$label)
		{
			$this->form->addElement("select", "q8_146_{$field}", "{$label}:",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_146_{$field}", array("q8_144{@}=={@}01|02|03"), "You must specify");
		}

		$this->addTextAreaElementRD('q8_146other', $this->indent . 'If you selected [Other], Please specify:');
		$this->XINRegisterRule("q8_146other", array("q8_146_h{@}=={@}01_yes"), "You must specify other", "q8_146other_group");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b>Box PPE</b>");
		$this->form->addElement('static', null, "If you selected [Yes] for [part d in 8-146], go to 8-147");
		$this->form->addElement('static', null, "Otherwise end Module and go to 8-148");
		$this->form->addElement('static', null, "<br/><br />");


		//q8_147
		$this->form->addElement("select", "q8_147", "8-147 What type of respirator was it?",  array(NULL=>"", "01" => "01 A half-mask chemical cartridge respirator", "02" => "02 A full-mask chemical cartridge respirator", "03" => "03  An air-supplied or SCBA respirator", "04" => "04 Some other kind of respirator?", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_147", array("q8_146_d{@}=={@}01_yes"), "You must specify");
		$this->addTextAreaElementRD('q8_147other', $this->indent . 'If [Some other kind of respirator], please specify:');
		$this->XINRegisterRule('q8_147other', array("q8_147{@}=={@}04"), "You must specify other", "q8_147other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: VENTILATION & ENCLOSURES");
		$this->form->addElement('static', null, "<br/>");


		//q8_148
		$this->form->addElement("select", "q8_148", "8-148 Was there any kind of a ventilation system to remove exhaust, dust, smoke or fumes from the area?", array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_148", array("q8_148{@}=={@}NEVER_REQUIRED"));
		$this->form->addElement('static', null, "<i>Probe: By ventilation system we mean purposely opening windows or doors, using a fume hood, or other ventilation system.</i>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused], or [Don't Know],  end Module and go to 8-150");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_149
		$this->form->addElement('static', null, "8-149 What ventilation systems are present to remove exhaust, dust, smoke or fumes from the area? Is there...Code all that apply.");
		$this->form->addElement('static', null, "<br/>");

		$ventilator = array("a"=>"a) A general ventilator system, meaning open doors or windows, use fan, etc.", "b"=>"b) A regular HVAC system for the building and room heating and cooling", "c"=>"c) A fume hood, lab hood, or other partially enclosed equipment", "d"=>"d) A glove box or other totally enclosed equipment", "e"=>"e) A portable exhaust hose or tube, such as those used for welding or to attach to vehicle tailpipe", "f"=>"f) Some other type of ventilation system");
		reset($ventilator);

		while(list($field, $label) = each($ventilator)){

			$this->form->addElement("select", "q8_149_{$field}", "{$label}:",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused", "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_149_{$field}", array("q8_148{@}=={@}01_yes"), "You must specify");

		}

		$this->addTextAreaElementRD('q8_149other', $this->indent . 'Please specify:');
		$this->XINRegisterRule("q8_149other", array("q8_149_f{@}=={@}01_yes"), "You must specify other", "q8_149other_group");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: PHOTOCOPYING/LASER JET PROXIMITY");
		$this->form->addElement('static', null, "<br/>");


		//q8_150
		$this->form->addElement("select", "q8_150", "8-150 Did this job require that you regularly stand at a photocopier for more than 1 hour per day?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_150", array("q8_150{@}=={@}NEVER_REQUIRED"));
		$this->form->addElement('static', null, "<br/>");


		//q8_151
		$this->form->addElement("select", "q8_151", "8-151 Did this job require that you sit within 10 feet of an operating laser jet printer for more than 1 hour per day?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_151", array("q8_151{@}=={@}NEVER_REQUIRED"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "When occupational module complete, and there are NO more Occupational Modules to Complete listed in the Occupational Coding Box then go to 8-13");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

	} //end function _page28() =====================================================



	function rulesPage28($fields)
	{

		$errors = array();

                $db =& Database::singleton();

                $db->selectRow("SELECT q8_5, q8_6_1, q8_6_2, q8_6_3, q8_6_4, q8_6_5, q8_6_7, q8_6_8, q8_6_9 FROM EARLI_interview_PART_3 WHERE CommentID='".$this->getCommentID()."'", $occupation);


		$options = array("a", "b", "c", "d", "e", "f", "g");


		if ($occupation["q8_5"] == "01" && (($occupation["q8_6_1"] >= "01" || $occupation["q8_6_2"] >= "10" || $occupation["q8_6_3"] >= "14" || $occupation["q8_6_4"] >= "19" || $occupation["q8_6_5"] >= "22") || ($occupation["q8_6_7"] >= "30" || $occupation["q8_6_8"] >= "40" || $occupation["q8_6_9"] <= "55"))) 
		{
			for ($i=0; $i<7; $i++)
			{
				if (empty($fields["q8_127_$options[$i]"]))
					$errors["q8_127_$options[$i]"] = "You must specify";	
			}
		}

		if ($occupation["q8_5"] == "01" && ($occupation["q8_6"] >= "01" && $fields["q8_6"] <= "09"))
		{
                        for ($i=0; $i<7; $i++)
                        {
                                if (empty($fields["q8_127_$options[$i]"]))
                                        $errors["q8_127_$options[$i]"] = "You must specify";
                        }
		}


		for ($i=0; $i<6; $i++)
		{
			if ($fields["q8_138_$options[$i]"] == "01_yes")
			{
				for ($j=0; $j<5; $j++)
				{
					if (empty($fields["q8_139_$options[$j]"]))
						$errors["q8_139_$options[$j]"] = "Required if worked near any of the above";
				}
				
				if (empty($fields["q8_140"]))
					$errors["q8_140"] = "Required if worked near any of the above";
				
				if (empty($fields["q8_141"]))
					$errors["q8_141"] = "Required if worked near any of the above";


				if (empty($fields["q8_144"]))
					$errors["q8_144"] = "Required if worked near any of the above";

				break;
			}
		}

		for ($i=0; $i<7; $i++)
		{
			if ($fields["q8_127_$options[$i]"] == "01_yes")
			{
				if (empty($fields["q8_141"]))
					$errors["q8_141"] = "You must specify";
				
				if (empty($fields["q8_144"]))
					$errors["q8_144"] = "You must specify";

				if (($fields["q8_141"] != "02") && ($fields["q8_141"] != ""))
				{
					for ($j=0; $j<7; $j++)
					{
						if (empty($fields["q8_142_$options[$j]"]))
							$errors["q8_142_$options[$j]"] = "You must specify";
					}
				}	

				if (($fields["q8_142_g"] != "01_yes") && ($fields["q8_142_g"] != ""))
				{
					for ($j=0; $j<5; $j++)
					{
						if (empty($fields["q8_143_$options[$j]"]))
							$errors["q8_143_$options[$j]"] = "You must specify";
					}
				}
				
				if (empty($fields["q8_148"]))
					$errors["q8_148"] = "You must specify";

				if (empty($fields["q8_150"]))
					$errors["q8_150"] = "You must specify";

				if (empty($fields["q8_151"]))
					$errors["q8_151"] = "You must specify";
		
				break;
			}
		}

		return $errors;
	}



	function _page29(){   // ========================================================


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>OCCUPATION MODULE: Teacher (TE)");
		$this->form->addElement('static', null, "<br/>");


		//function with more complex rules
		$this->form->addFormRule(array(&$this, 'rulesPage29'));
		

		//q8_152
		$this->form->addElement('static', null, "8-152 Which of the following subjects did you teach? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Art", "b"=>"b) Shop, woodworking, or industrial arts", "c"=>"c) Biology", "d"=>"d) Chemistry", "e"=>"e) None of these");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_152_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_152_{$field}", array("q8_152_{$field}{@}=={@}NEVER_REQUIRED"));
		}

		$this->addTextAreaElementRD('q8_152other', $this->indent . 'If you selected [Shop, woodworking, or industrial arts], please specify:');
		$this->XINRegisterRule("q8_152other", array("q8_152_b{@}=={@}01_yes"), "You must specify subject", "q8_152other_group");
		$this->form->addElement('static', null, $this->indent . "If you selected [None of these], end Module and go to 8-194");
		$this->form->addElement('static', null, $this->indent . "If you selected [Refused], [Don't Know] and/or [No] to all, end Module and go to 8-194");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_153
		$this->form->addElement("select", "q8_153", "8-153 Between [-3] and DOBS did you use chemicals or generated dusts or metal fumes in your class? Examples include paint, glue, acids, and solder or welding materials.",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_153", array("q8_153{@}=={@}NEVER_REQUIRED"));
		$this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused], or [Don't Know], end Module and go to 8-194");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>BOX TE-1");
		$this->form->addElement('static', null, "If you selected [Yes] to [part a or b in 8-152] and [Yes] in [8-153], go to 8-154");
		$this->form->addElement('static', null, "Otherwise [go to Box TE-2]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_154
		$this->form->addElement('static', null, "8-154 Between [-3] and DOBS, what chemicals did you use in your classes? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$chemicals = array("a"=>"a) Acetone", "b"=>"b) Acids", "c"=>"c) Glue", "d"=>"d) Paint or paint related chemicals (varnish, paint, thinner, turpentine, etc.)", "e"=>"e) Gasoline, oil, or hydraulic fluids",  "f"=>"f) Soldering or welding",  "g"=>"g) None",  "h"=>"h) Something else");

		foreach ($chemicals as $field=>$label)
		{
			$this->form->addElement("select", "q8_154_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_154_{$field}", array("q8_154_{$field}{@}=={@}NEVER_REQUIRED"));

		}

		$this->addTextAreaElementRD('q8_154other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule("q8_154other", array("q8_154_h{@}=={@}01_yes"), "You must specify something else", "q8_154other_group");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>BOX TE-2");
		$this->form->addElement('static', null, "If you selected [Yes] to [part c or d in 8-152], go to 8-155");
		$this->form->addElement('static', null, "Otherwise, go to Ventilation and Enclosures Module - starts on 8-164");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_155
		$this->form->addElement('static', null, "8-155 Between [-3] and DOBS, what chemicals or agents did you use in your classes? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$agents = array("a"=>"a) Acetone", "b"=>"b) Acids", "c"=>"c) Alcohols", "d"=>"d) Caustics", "e"=>"e) Chloroform",  "f"=>"f) Ester",  "g"=>"g) Ethers",  "h"=>"h) Ketones",  "i"=>"i) Mold or other microbials",  "j"=>"j) Toluene or xylene",  "k"=>"k) None",  "l"=>"l) Something else");

		foreach ($agents as $field=>$label)
		{
			$this->form->addElement("select", "q8_155_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_155_{$field}", array("q8_155_{$field}{@}=={@}NEVER_REQUIRED"));
		}

		$this->addTextAreaElementRD('q8_155other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule("q8_155other", array("q8_155_l{@}=={@}01_yes"), "You must specify something else", "q8_155other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		

		//q8_156
		$this->form->addElement('static', null, "8-156 How often did you use the following chemicals in your classroom:");
		$this->form->addElement('static', null, "<i>Probe: How many hours per day, per week or per month do you use the following chemicals in your classroom?</i>");
		$this->form->addElement('static', null, "<br/>");

		foreach ($agents as $field=>$label)
		{
			$this->form->addElement('select', "q8_156_{$field}", "{$label}:",  array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03 Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->XINRegisterRule("q8_156_{$field}", array("q8_155_{$field}{@}=={@}01_yes"), "You must specify");
			$this->addTextAreaElementRD("q8_156_number{$field}", $this->indent . 'Number:');
			$this->XINRegisterRule("q8_156_number{$field}", array("q8_156_{$field}{@}=={@}01|02|03|04"), "You must specify hours", "q8_156_number{$field}_group");
		}

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: CLEAN HANDS");
		$this->form->addElement('static', null, "<br/>");


		//q8_157
		$this->form->addElement("select", "q8_157", "8-157 Did you regularly get chemicals or dust on your hands or skin?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused", "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_157", array("q8_157{@}=={@}NEVER_REQUIRED"));
		$this->form->addElement('static', null, $this->indent . "If you selected [No], end Module and go to 8-160");
		$this->form->addElement('static', null, "<br/>");


		//q8_158
		$this->form->addElement('static', null, "8-158 When you had chemicals or dust on your hands, when did you wash your hands? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$list = array("a"=>"a) When taking a break at work", "b"=>"b) Before eating", "c"=>"c) Before smoking", "d"=>"d) At the end of the work shift", "e"=>"e) When the task is completed",  "f"=>"f) Whenever I get my hands dirty",  "g"=>"g) Don't wash hands");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_158_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_158_{$field}", array("q8_157{@}=={@}01_yes"), "You must specify");
		}

		$this->form->addElement('static', null, $this->indent . "If you selected [Don't wash hands], end Module and go to 8-160");
		$this->form->addElement('static', null, "<br/>");


		//q8_159
		$this->form->addElement('static', null, "8-159 What did you use to wash chemicals or dust off your hands? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Soap and water or water only", "b"=>"b) [Goop] or similar cleaners", "c"=>"c) Mineral spirits, turpentine, or paint thinner", "d"=>"d) Gasoline or kerosene", "e"=>"e) Something else");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_159_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_159_{$field}", array("q8_158_g{@}!={@}01_yes", "q8_158_g{@}!={@}"), "You must specify");
		}
		
		$this->addTextAreaElementRD('q8_159other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule("q8_159other", array("q8_159_e{@}=={@}01_yes"), "You must specify something else", "q8_159other_group");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: PERSONAL PROTECTIVE EQUIPMENT");
		$this->form->addElement('static', null, "<br/>");


		//q8_160
		$this->form->addElement("select", "q8_160", "8-160 Between [-3] and DOBS, how often did you wear or use personal protective equipment (PPE) to protect you from the things you have mentioned? By personal protective equipment, I mean the things like gloves, dust mask, goggles, aprons, lab coats or other protective clothing, would you say always, often, rarely, or never us personal protective equipment?",  array(NULL=>"", "01" => "01 Always", "02" => "02 Often", "03" => "03  Rarely", "04" => "04 Never", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_160", array("q8_160{@}=={@}NEVER_REQUIRED"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If you selected [Never], [Refused], or [Don't know], end Module and go to 8-164");
		$this->form->addElement('static', null, "<br/>");


		//q8_162
		$this->form->addElement('static', null, "8-162 Which type of protective clothing or equipment did you wear? Code all that apply.");
		$this->form->addElement('static', null, "<i>PROBE: Any other protective clothing or equipment?</i>");
		$this->form->addElement('static', null, "<br/>");

		foreach ($this->protectiveEquipment as $field=>$label)
		{
			$this->form->addElement("select", "q8_162_{$field}", "{$label}:",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_162_{$field}", array("q8_160{@}=={@}01|02|03"), "You must specify");
		}

		$this->addTextAreaElementRD('q8_162_other', $this->indent . 'If you selected [Other], please specify:');
		$this->XINRegisterRule("q8_162_other", array("q8_162_h{@}=={@}01_yes"), "You must specify other", "q8_162_other_group");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b>Box PPE</b>");
		$this->form->addElement('static', null, "If you selected [Yes] for [part e in 8-162], go to 8-163");
		$this->form->addElement('static', null, "Otherwise, go to Ventilation and Enclosures Module - starts on 8-164");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8-163
		$this->form->addElement("select", "q8_163", "8-163 What type of respirator was it?",  array(NULL=>"", "01" => "01 A half-mask chemical cartridge respirator", "02" => "02 A full-mask chemical cartridge respirator", "03" => "03  An air-supplied or SCBA respirator", "04" => "04 Some other kind of respirator?", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_163", array("q8_162_e{@}=={@}01_yes"), "You must specify type of respirator");
		$this->addTextAreaElementRD('q8_163other', $this->indent . 'If you selected [Some other kind of respirator], please specify:');
		$this->XINRegisterRule("q8_163other", array("q8_163{@}=={@}04"), "You must specify other", "q8_163other_group");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: VENTILATION & ENCLOSURES");
		$this->form->addElement('static', null, "<br/>");


		//q8_164
		$this->form->addElement("select", "q8_164", "8-164 Was there any kind of a ventilation system to remove exhaust, dust, smoke or fumes from the area?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_164", array("q8_164{@}=={@}NEVER_REQUIRED"));
		$this->form->addElement('static', null, "<i>Probe: By ventilation system we mean purposely opening windows or doors, using a fume hood, or other ventilation system.</i>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused], or [Don't know], end Module and go to Box TE-3");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_165
		$this->form->addElement('static', null, "8-165 What ventilation systems are present to remove exhaust, dust, smoke or fumes from the area? Is there...Code all that apply.");
		$this->form->addElement('static', null, "<br/>");

		foreach ($this->ventilators as $field=>$label)
		{
			$this->form->addElement("select", "q8_165_{$field}", "{$label}:",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_165_{$field}", array("q8_164{@}=={@}01_yes"), "You must specify type of ventilation system");
		}

		$this->addTextAreaElementRD('q8_165other', $this->indent . 'Please specify:');
		$this->XINRegisterRule("q8_165other", array("q8_165_f{@}=={@}01_yes"), "You must specify other", "q8_165other_group");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>BOX TE-3");
		$this->form->addElement('static', null, "If you selected [Yes] to [part b in 8-152], go to Fuel and Exhaust Module - starts on 8-165a");
		$this->form->addElement('static', null, "Otherwise, go to BOX TE-4");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: FUEL AND EXHAUST SMELLS");
		$this->form->addElement('static', null, "<br/>");


		//q8_165a
		$this->form->addElement("select", "q8_165a", "8-165a Did you regularly smell fuel vapors, such as from gas or fuel tanks, or exhaust vapors, such as from car or truck tail pipes?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered")); 
		$this->XINRegisterRule("q8_165a", array("q8_152_b{@}=={@}01_yes"), "Required if teach shop, woodworking or inudstrial arts");
		$this->form->addElement('static', null, $this->indent . "If you selected [No], end Module and go to Box TE-4");
		$this->form->addElement('static', null, "<br/>");


		//q8_165b
		$this->form->addElement("select", "q8_165b", "8-165b How strong was the smell?",  array(NULL=>"", "01" => "01 Slight", "02" => "02 Moderate", "03" => "03  Strong", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_165b", array("q8_165a{@}=={@}01_yes"), "Required if regularly smell fuel vapors");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>BOX TE-4");
		$this->form->addElement('static', null, "If you selected [Yes] to [part b in 8-152], go to Lubrication Engines Module starts on 8-166]");
		$this->form->addElement('static', null, "Otherwise [go to Box TE-5]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: LUBRICATING ENGINES & MACHINERY");
		$this->form->addElement('static', null, "<br/>");


		//q8_166
		$this->form->addElement("select", "q8_166", "8-166 Did you routinely use lubricating oils, or waxes on engines or machinery?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_166", array("q8_152_b{@}=={@}01_yes"), "Required if teach shop, woodworking or inudstrial arts");
		$this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused], or [Don't Know], end Module and go to Box TE-5");
		$this->form->addElement('static', null, "<br/>");

	
		//q8_167
		$this->addTextAreaElementRD("q8_167", "8-167 What types of lubricants did you work with?");
		$this->XINRegisterRule("q8_167", array("q8_166{@}=={@}01_yes"), "Required if routinely use libricating oils or waxes", "q8_167_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_168
		$this->form->addElement('static', null, "8-168 What types of cutting oils did you work with? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$oils = array("a"=>"a) Straight cutting oils or oils that look and feel like motor oil", "b"=>"b) Soluble cutting oils or oils that are milky white", "c"=>"c) Synthetic cutting oils or oils that feel like water or may be brightly colored, such as green or blue", "d"=>"d) Something else");

		foreach ($oils as $field=>$label)
		{
			$this->form->addElement("select", "q8_168_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_168_{$field}", array("q8_166{@}=={@}01_yes"), "Required if routinely use libricating oils or waxes");
		}

		$this->addTextAreaElementRD('q8_168other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule("q8_168other", array("q8_168_d{@}=={@}01_yes"), "You must specify something else", "q8_168other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_169
		$this->form->addElement('static', null, "8-169 How often did you use the following lubricants?");
		$this->form->addElement('static', null, "<i>Probe: How many hours per day, per week or per month did you use the following lubricants?</i>");
		$this->form->addElement('static', null, "<br/>");
		

		foreach ($oils as $field=>$label)
		{
			$this->form->addElement('select', "q8_169_{$field}", "{$label}:",  array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->XINRegisterRule("q8_169_{$field}", array("q8_168_{$field}{@}=={@}01_yes"), "Required if routinely use libricating oils or waxes");
			$this->addTextAreaElementRD("q8_169_other{$field}", $this->indent . 'Number:');
			$this->XINRegisterRule("q8_169_other{$field}", array("q8_169_{$field}{@}=={@}01|02|03|04"), "You must specify number", "q8_169_other{$field}_group");
		}


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>BOX TE-5");
		$this->form->addElement('static', null, "If you selected [Yes] to [part c in 8-154], go to Glue Module - starts on 8-170");
		$this->form->addElement('static', null, "Otherwise [go to Box TE-6]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: GLUING");
		$this->form->addElement('static', null, "<br/>");


		//q8_170
		$this->form->addElement("select", "q8_170", "8-170 Did you routinely use glues or adhesives?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_170", array("q8_154_c{@}=={@}01_yes"), "Required if used glue in classes");
		$this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused], or [Don't Know], end Module and go to Box TE-6");
		$this->form->addElement('static', null, "<br/>");


		//q8_171
		$this->form->addElement('static', null, "8-171 Which glues did you use? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		foreach ($this->adhesives as $field=>$label)
		{
			$this->form->addElement("select", "q8_171_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_171_{$field}", array("q8_170{@}=={@}01_yes"), "Required if routinely used glues or adhesives");
		}
		
		$this->addTextAreaElementRD('q8_171other', $this->indent . 'If you selected [e) Something else], please specify:');
		$this->XINRegisterRule('q8_171other', array("q8_171_e{@}=={@}01_yes"), "You must specify something else", "q8_171other_group");
		$this->form->addElement('static', null, "<br/>");


		//q8_172
		$this->form->addElement('static', null, "8-172 How strong was the smell of {hot melt glues/contact adhesives/water-based adhesives/wood laminates}? <i>Code for each yes response in 8-171</i>");
		$this->form->addElement('static', null, "<br/>");

		foreach ($this->adhesives as $field=>$label)
		{
			$this->form->addElement("select", "q8_172_{$field}", "{$label}", array(NULL=>"", "01" => "01 Slight", "02" => "02 Moderate", "03" => "03  Strong", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->XINRegisterRule("q8_172_{$field}", array("q8_171_{$field}{@}=={@}01_yes"), "Required if routinely used:");
		}

		$this->form->addElement('static', null, "<br/>");


		//q8_173
		$this->form->addElement("select", "q8_173", "8-173 Did you wipe off the excess glue or adhesive with a solvent?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_173", array("q8_170{@}=={@}01_yes"), "Required if routinely used glues or adhesives");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused], or [Don't Know], go to 8-175]");
		$this->form->addElement('static', null, "<br/>");


		//q8_174
		$this->form->addElement('static', null, "8-174 What solvent did you typically wipe it off with? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$solvents = array("a"=>"a) Acetone", "b"=>"b) Paint thinner", "c"=>"c) Citrus-based chemicals", "d"=>"d) Something else");

		foreach ($solvents as $field=>$label)
		{
			$this->form->addElement("select", "q8_174_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_174_{$field}", array("q8_173{@}=={@}01_yes"), "Required if used solvent");
		}
 
		$this->addTextAreaElementRD('q8_174other', $this->indent . 'If you selected [d) Something else], please specify:');
		$this->XINRegisterRule("q8_174other", array("q8_174_d{@}=={@}01_yes"), "You must specify lubricant", "q8_174other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_175
		$this->form->addElement('static', null, "8-175 How often did you use the following glues or adhesives?");
		$this->form->addElement('static', null, "<i>Probe: How many hours per day, per week or per month do you use the following glues or adhesives?</i>");
		$this->form->addElement('static', null, "<br/>");

		foreach($this->adhesives as $field=>$label)
		{
			$this->form->addElement('select', "q8_175_{$field}", "{$label}:", array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->XINRegisterRule("q8_175_{$field}", array("q8_171_{$field}{@}=={@}01_yes"), "Required if routinely used this glue or adhesive");
			$this->addTextAreaElementRD("q8_175_number{$field}", $this->indent . 'Number:');
			$this->XINRegisterRule("q8_175_number{$field}", array("q8_175_{$field}{@}=={@}01|02|03|04"), "You must specify number", "q8_175_number{$field}_group");
		}

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>BOX TE-6");
		$this->form->addElement('static', null, "If you selected [Yes] to [part d in 8-154], go to Paint Module - starts on 8-176");
		$this->form->addElement('static', null, "Otherwise [go to Box TE-7]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<br/>");
	        $this->form->addElement('static', null, "<b/>ACTIVITY MODULE: PAINTING, PAINT REMOVAL, PAINT CLEANING");
                $this->form->addElement('static', null, "<br/>");
                $this->form->addElement('static', null, "<b><i>The next few questions ask about painting, varnishing, and staining.</i></b>");
                $this->form->addElement('static', null, "<br/>");


                //q8_176
                $this->form->addElement('static', null, "8-176 Did you typically do any of the following activities? Code all that apply:");
                $this->form->addElement('static', null, "<br/>");

                $list = array("a"=>"a) Painting, varnishing, or staining", "b"=>"b) Paint removal", "c"=>"c) Paint thinning and cleaning", "d"=>"d) Something else", "e"=>"e) None of the above");
                reset($list);

                while(list($field, $label) = each($list)){
                        $this->form->addElement("select", "q8_176_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_176_{$field}", array("q8_154_d{@}=={@}01_yes"), "Required if used paints");
		}

                $this->addTextAreaElementRD('q8_176other', $this->indent . 'If you selected [Something else], please specify and go to Box TE-7:');
                $this->XINRegisterRule("q8_176other", array("q8_176_d{@}=={@}01_yes"), "You must specify something else", "q8_176other_group");
                $this->form->addElement('static', null, $this->indent . "If you selected [None of the above], end Module and go to Box TE-7");
                $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] and/or [Don't Know] for [part a-e], end Module and go to Box TE-7]");
                $this->form->addElement('static', null, "<br/>");
                $this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>BOX PT-1");
		$this->form->addElement('static', null, "If you selected [Yes] to [part a in 8-176], go to 8-177, 8-178, 8-179]");
		$this->form->addElement('static', null, "Otherwise [go to Box PT-2]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_177
		$this->form->addElement('static', null, "8-177 What kind of paint did you use? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Laytex or water-based paint", "b"=>"b) Acrylic", "c"=>"c) Oil-based paint (enamel)", "d"=>"d) Something else");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_177_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_177_{$field}", array("q8_176_a{@}=={@}01_yes"), "Required if did painting, varnishing or staining");
		}

		$this->addTextAreaElementRD('q8_177other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule("q8_177other", array("q8_177_d{@}=={@}01_yes"), "You must specify something else", "q8_177other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_178
		$this->form->addElement('static', null, "8-178 Did you usually brush, roll, or spray paint? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Brush", "b"=>"b) Roll", "c"=>"c) Spray", "d"=>"d) Something else");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_178_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_178_{$field}", array("q8_176_a{@}=={@}01_yes"), "Required if did painting, varnishing or staining");
		}
		$this->addTextAreaElementRD('q8_178other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule("q8_178other", array("q8_178_d{@}=={@}01_yes"), "You must specify something else", "q8_178other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_179
		$this->form->addElement("select", "q8_179", "8-179 Did you use primers with lead, chromate, or zinc?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_179", array("q8_176_a{@}=={@}01_yes"), "Required if did painting, varnishing or staining");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>BOX PT-2");
		$this->form->addElement('static', null, "If you selected [Yes] to [part b in 8-176], go to 8-180");
		$this->form->addElement('static', null, "Otherwise [go to Box PT-3]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_180
		$this->form->addElement('static', null, "8-180 How did you typically remove paint? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Heat gun", "b"=>"b) Scraper or wire stripper with a drill biti attachment", "c"=>"c) Chemical paint stripper", "d"=>"d) Some other paint removal method");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_180_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_180_{$field}", array("q8_176_b{@}=={@}01_yes"), "Required if did paint removal");
		}

		$this->addTextAreaElementRD('q8_180other', $this->indent . 'If you selected [Some other paint removal method], please specify:');
		$this->XINRegisterRule("q8_180other", array("q8_180_d{@}=={@}01_yes"), "You must specify other", "q8_180other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>BOX PT-3");
		$this->form->addElement('static', null, "If you selected [Yes] to [part c in 8-176], go to 8-181");
		$this->form->addElement('static', null, "Otherwise [go to 8-183]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_181
		$this->form->addElement('static', null, "8-181 What did you typically use to thin or clean paint, varnish or stain? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Paint thinner, mineral spirits, or turpertin", "b"=>"b) Lacquer thinner", "c"=>"c) Alcohol", "d"=>"d) Water", "e"=>"e) Citrus-based products",  "f"=>"f) Gasoline or kerosene",  "g"=>"g) Other");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_181_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_181_{$field}", array("q8_176_c{@}=={@}01_yes"), "Required if did paint thinning and cleaning");
		}

		$this->addTextAreaElementRD('q8_181other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule("q8_181other", array("q8_181_g{@}=={@}01_yes"), "You must specify something else", "q8_181other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_182
		$this->form->addElement('static', null, "8-182 What chemicals did you use to strip paint? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Lacquer or paint thinner", "b"=>"b) Lye (Sodium hydroxide)", "c"=>"c) Ammonia (Ammonia Hydroxide)", "d"=>"d) Other");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_182_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_182_{$field}", array("q8_176_c{@}=={@}01_yes"), "Required if did paint thinning and cleaning");
		}

		$this->addTextAreaElementRD('q8_182other', $this->indent . 'If you selected [Other], please specify:');
		$this->XINRegisterRule("q8_182other", array("q8_182_d{@}=={@}01_yes"), "You must specify other", "q8_182other_group");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>BOX PT-4");
		$this->form->addElement('static', null, "If you selected [Yes] to [part c in 8-180], go to 8-183");
		$this->form->addElement('static', null, "Otherwise [go to 8-184]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_183
		$this->form->addElement('static', null, "8-183 How often did you use the following paint, paint thinners, or paint strippers?");
		$this->form->addElement('static', null, "<i>Probe: How many hours per day, per week or per month did you use the following paint, paint thinners, or paint strippers?</i>");
		$this->form->addElement('static', null, "<br/>");

		$list = array("a"=>"a) Laytex or water-based paint", "b"=>"b) Acrylic", "c"=>"c) Oil-based paint (enamel)","d"=>"d) Paint thinner, mineral spirits, or turpertin", "e"=>"e) Lacquer thinner", "f"=>"f) Alcohol", "g"=>"g) Water", "h"=>"h) Citrus-based products",  "i"=>"i) Gasoline or kerosene", "j"=>"j) Lacquer or paint thinner", "k"=>"k) Lye (Sodium hydroxide)", "l"=>"l) Ammonia (Ammonia Hydroxide)", "m"=>"m) Other" );

		reset($list);
		while(list($field, $label) = each($list)){

			$this->form->addElement('select', "q8_183_{$field}", "{$label}:", array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->XINRegisterRule("q8_183_{$field}", array("q8_180_c{@}=={@}01_yes"), "Required if used chemical paint stripper");
			$this->addTextAreaElementRD("q8_183_number{$field}", $this->indent . 'Number:');
			$this->XINRegisterRule("q8_183_number{$field}", array("q8_183_{$field}{@}=={@}01|02|03|04"), "You must specify number", "q8_183_number{$field}_group");
		}

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>BOX TE-7");
		$this->form->addElement('static', null, "If you selected [Yes] to [part f in 8-154], go to Soldering or Welding Module - starts on 8-184");
		$this->form->addElement('static', null, "Otherwise [go to Box TE-8]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: SOLDERING AND WELDING");
		$this->form->addElement('static', null, "<br/>");


		//q8_184
		$this->form->addElement('static', null, "8-184 Did you do any of the following? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Soldering or brazing", "b"=>"b) Smell fumes from others who solder or braze", "c"=>"c) Welding or flame cutting", "d"=>"d) Smell fumes from others who weld or flame cut,", "e"=>"e) Some other welding or soldering method?",  "f"=>"f) None of the above");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_184_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_184_{$field}", array("q8_154_f{@}=={@}01_yes"), "Required if did soldering or welding");
		}

		$this->addTextAreaElementRD('q8_184other', $this->indent . 'If you selected [Some other welding or soldering method?] then please specify:');
		$this->XINRegisterRule("q8_184other", array("q8_184_e{@}=={@}01_yes"), "You must specify other", "q8_184other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If you selected [None of the above], [End Module and go to Box TE-8]");
		$this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] and/or [Don't Know] for [part a-e], end Module and go to Box TE-8");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>BOX SW-1");
		$this->form->addElement('static', null, "If you selected [Yes] to [part a in 8-184], go to 8-188, 8-189, 8-190, 8-191");
		$this->form->addElement('static', null, "Otherwise, go to 8-191a");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_185
		$this->form->addElement('static', null, "8-185 What types of metal did {you/they/you and those who weld or flame cut around you} weld or flame cut? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$metals = array("a"=>"a) Aluminum", "b"=>"b) Brass or bronze", "c"=>"c) Cast iron", "d"=>"d) Copper", "e"=>"e) Steel",  "f"=>"f) Titanium-based alloy",  "g"=>"g) Other");

		foreach ($metals as $field=>$label)
		{
			$this->form->addElement("select", "q8_185_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_185_{$field}", array("q8_184_c{@}=={@}01_yes"), "Required if did welding or flame cutting");
		}

		$this->addTextAreaElementRD('q8_185other', $this->indent . 'If you selected [Other], please specify:');
		$this->XINRegisterRule("q8_185other", array("q8_185_d{@}=={@}01_yes"), "You must specify other", "q8_185other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If you selected [Yes] to [e], go to 8-186]");
		$this->form->addElement('static', null, $this->indent . "If you selected [Yes] to [any a-g], go to 8-187]");
		$this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused], [Don't Know] to <u>all</u>, go to 8-187");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_186
		$this->form->addElement("select", "q8_186", "8-186 What kind of steel was it?",  array(NULL=>"", "01" => "01 Cadmium plated steel", "02" => "02 Chromium plated steel", "03" => "03  Galvanized iron", "04" => "04 Lead-plated or leaded steel", "05" => "05 Mild, carbon, or construction steel", "06" => "06 Stainless steel", "07" => "07 Another type of steel?", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_186", array("q8_185_l{@}=={@}01_yes"), "You must specify kind of steel");
		$this->addTextAreaElementRD('q8_186other', $this->indent . 'If you selected [Another type of steel], please specify:');
		$this->XINRegisterRule("q8_186other", array("q8_186{@}=={@}07"), "You must specify other", "q8_186other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_187
		$this->form->addElement("select", "q8_187", "8-187 What type of welding or flame cutting did {you/they/you and those who weld or flame cut around you} do?",  array(NULL=>"", "01" => "01 Oxygas, oxyfuel, or oxyacetylene", "02" => "02 MIG (Metal Inert Gas)", "03" => "03  TIG (Tungsten Inert Gas)", "04" => "04 Stick electrode (shielded metal arc welding)", "05" => "05 Resistance, such as sport, seam, flash, butt, and projection", "06" => "06 Solid state, such as friction or roll", "07" => "07 Plasma arc", "08" => "08 Submerged arc", "09" => "09 Something else", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_187", array("q8_184_a{@}!={@}01_yes", "q8_184_f{@}!={@}01_yes", "q8_184_c{@}=={@}01_yes"), "You must specify kind of welding or flame cutting");
		$this->addTextAreaElementRD('q8_187other', $this->indent . 'If you selected [Something else], please specify:');
                $this->XINRegisterRule("q8_187other", array("q8_187{@}=={@}09"), "You must specify something else", "q8_187other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>BOX SW-1");
		$this->form->addElement('static', null, "If you selected [Yes] to [part a or b in 8-184], go to 8-188, 8-189, 8-190, 8-191");
		$this->form->addElement('static', null, "Otherwise, go to 8-191a");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_188
		$this->form->addElement('static', null, "8-188 What did {you/then/you and those who solder or braze around you} solder or braze? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Pipes", "b"=>"b) Electrical or electronic parts", "c"=>"c) Other");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_188_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_188_{$field}", array("q8_188_{$field}{@}=={@}NEVER_REQUIRED"));
		}

		$this->addTextAreaElementRD('q8_188other', $this->indent . 'If you selected [Other], please specify:');
                $this->XINRegisterRule("q8_188other", array("q8_188_c{@}=={@}01_yes"), "You must specify other", "q8_188other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_189
		$this->form->addElement("select", "q8_189", "8-189 Did {you/they/you and those who solder or braze around you} use lead-free solder?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
                $this->XINRegisterRule("q8_189", array("q8_189{@}=={@}NEVER_REQUIRED"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_190
		$this->form->addElement("select", "q8_190", "8-190 Did the solder usually contain any unusual ingredients such as cadmium, silver, copper, nickel, zinc, arsenic, beryllium, antimony, indium, or bismuth?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_190", array("q8_190{@}=={@}NEVER_REQUIREd"));
		$this->addTextAreaElementRD('q8_190other', $this->indent . 'If you selected [Yes], please specify:');
		$this->XINRegisterRule("q8_190other", array("q8_190{@}=={@}01_yes"), "You must specify ingredients", "q8_190other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_191
		$this->form->addElement('static', null, "8-191 What did {you/they/you and those who solder or braze around you} solder or braze? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Brass", "b"=>"b) Bronze", "c"=>"c) Cast iron", "d"=>"d) Copper", "e"=>"e) Nickel",  "f"=>"f) Other types of iron",  "g"=>"g) Stainless steel",  "h"=>"h) Other steel",  "i"=>"i) Other");

		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_191_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_191_{$field}", array("q8_191_{$field}{@}=={@}NEVER_REQUIRED"));
		}

		$this->addTextAreaElementRD('q8_191otheriron', $this->indent . 'If you selected [Other types of iron], please specify:');
                $this->XINRegisterRule("q8_191otheriron", array("q8_191_f{@}=={@}01_yes"), "You must specify other iron", "q8_191otheriron_group");
		$this->addTextAreaElementRD('q8_191othersteel', $this->indent . 'If you selected [Other steel], please specify:');
                $this->XINRegisterRule("q8_191othersteel", array("q8_191_h{@}=={@}01_yes"), "You must specify other steel", "q8_191othersteel_group");
		$this->addTextAreaElementRD('q8_191other', $this->indent . 'If you selected [Other], please specify:');
                $this->XINRegisterRule("q8_191other", array("q8_191_i{@}=={@}01_yes"), "You must specify other", "q8_191other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_191a
		$this->form->addElement('static', null, "8-191a How often did you use the following metals?");
		$this->form->addElement('static', null, "<i>Probe: How many hours per day, per week or per month do you use the following metals?i</i>");
		$this->form->addElement('static', null, "<br/>");

		foreach ($metals as $field => $label)
		{
			$this->form->addElement('select', "q8_191a_{$field}", "{$label}:",  array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->XINRegisterRule("q8_191a_{$field}", array("q8_185_{$field}{@}=={@}01_yes"), "You must specify frequency");
			$this->addTextAreaElementRD("q8_191a_number{$field}", $this->indent . 'Number:');
                	$this->XINRegisterRule("q8_191a_number{$field}", array("q8_191a_{$field}{@}=={@}01|02|03|04"), "You must specify number", "q8_191a_number{$field}_group");
		}

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>BOX TE-8");
		$this->form->addElement('static', null, "If you selected [Yes] to [part a in 8-152], go to Art Supply Module AND Photocopying/Laser Jet Proximity Module - starts on 8-192");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: USING ART SUPPLIES");
		$this->form->addElement('static', null, "<br/>");


		//q8_192
		$this->form->addElement('static', null, "8-192 Which art supplies did you typically use? Or use at least once a week? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$artSupplies = array("a"=>"a) Markers", "b"=>"b) Paints", "c"=>"c) Inks", "d"=>"d) Glazes", "e"=>"e) Something else",  "f"=>"f) No art supplies containing chemicals");

		foreach ($artSupplies as $field=>$label)
		{
			$this->form->addElement("select", "q8_192_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_192_{$field}", array("q8_152_a{@}=={@}01_yes"), "Required if taught art");
		} 

		$this->addTextAreaElementRD('q8_192other', $this->indent . 'If you selected [Yes] to e) Something else, please specify:');
                $this->XINRegisterRule("q8_192other", array("q8_192_e{@}=={@}01_yes"), "You must specify other", "q8_192other_group");
		$this->form->addElement('static', null, "<br/>");


		//q8_193
		$this->form->addElement('static', null, "8-193 How often did you use the following art supplies?");
		$this->form->addElement('static', null, "<i>Probe: How many hours per day, per week or per month did you use the following art supplies?</i>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Enter number and choose units or select from the list");
		$this->form->addElement('static', null, "<br/>");

		foreach ($artSupplies as $field=>$label)
		{
			$this->form->addElement('select', "q8_193_{$field}", "{$label}:", array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->XINRegisterRule("q8_193_{$field}", array("q8_192_{$field}{@}=={@}01_yes"), "Required if used");
			$this->addTextAreaElementRD("q8_193_number{$field}", $this->indent . 'Number:');
                	$this->XINRegisterRule("q8_193_number{$field}", array("q8_193_{$field}{@}=={@}01|02|03|04"), "You must specify number", "q8_193_number{$field}_group");
		}

//		$this->addTextAreaElementRD('q8_193other', $this->indent . 'If you selected [Yes] to [e) Something else], please specify:');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: PHOTOCOPYING/LASER JET PROXIMITY");
		$this->form->addElement('static', null, "<br/>");


		//q8_194
		$this->form->addElement("select", "q8_194", "8-194 Did this job require that you regularly stand at a photocopier for more than 1 hour per day?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_194", array("q8_194{@}=={@}NEVER_REQUIRED"));
		$this->form->addElement('static', null, "<br/>");


		//q8_195
		$this->form->addElement("select", "q8_195", "8-195 Did this job require that you sit within 10 feet of an operating laser jet printer for more than 1 hour per day?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_195", array("q8_195{@}=={@}NEVER_REQUIRED"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b>When occupational module is complete, and there are NO more Occupational Modules to Complete listed in the Occupational Coding Box, go to 8-13</b>");	
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


	} //end function _page29() =====================================================


	
	function rulesPage29($fields)
	{
		$errors = array();

                $db =& Database::singleton();

                $db->selectRow("SELECT q8_5, q8_6_1, q8_6_2, q8_6_3, q8_6_4, q8_6_5, q8_6_6, q8_6_7, q8_6_8, q8_6_9 FROM EARLI_interview_PART_3 WHERE CommentID='".$this->getCommentID()."'", $occupation);


		$options = array("a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l");


		if($occupation["q8_5"] == "02" && (($occupation["q8_6_1"] >= "01" || $occupation["q8_6_2"] >= "10" || $occupation["q8_6_3"] >= "14" || $occupation["q8_6_4"] >= "19" || $occupation["q8_6_6"] >= "26" || $occupation["q8_6_7"] >= "30" || $occupation["q8_6_8"] >= "40" || $occupation["q8_6_9"] >= "42")))
		{
			for ($i=0; $i<5; $i++)
			{
				if (empty($fields["q8_152_$options[$i]"]))
					$errors["q8_152_$options[$i]"] = "You must specify";
			}
				if (empty($fields["q8_194"]))
					$errors["q8_194"] = "You must specify";	
				if (empty($fields["q8_195"]))
					$errors["q8_195"] = "You must specify";	
		}

		if ($occupation["q8_5"] == "05" && ($occupation["q8_6_5"] >= "22" || $occupation["q8_6_5"] <= "25"))
		{
                        for ($i=0; $i<5; $i++)
                        {
				if (empty($fields["q8_152_$options[$i]"]))
					$errors["q8_152_$options[$i]"] = "You must specify";
			}
				if (empty($fields["q8_194"]))
					$errors["q8_194"] = "You must specify";	
				if (empty($fields["q8_195"]))
					$errors["q8_195"] = "You must specify";	
		}


		if ($occupation["q8_5"] == "09" && ($occupation["q8_6_2"] >= "10" || $occupation["q8_6_2"] <= "13"))
		{
                        for ($i=0; $i<5; $i++)
                        {
				if (empty($fields["q8_152_$options[$i]"]))
					$errors["q8_152_$options[$i]"] = "You must specify";
			}
				if (empty($fields["q8_194"]))
					$errors["q8_194"] = "You must specify";	
				if (empty($fields["q8_195"]))
					$errors["q8_195"] = "You must specify";	
		}


		for ($i=0; $i<4; $i++)
		{
			if ($fields["q8_152_$options[$i]"] == "01_yes")
			{
				if (empty($fields["q8_153"]))
					$errors["q8_153"] = "You must specify";	

				break;
			}
		}


		if (($fields["q8_153"] == "01_yes") && ($fields["q8_152_a"] == "01_yes"))
		{
			for ($j=0; $j<6; $j++)
			{
				if ($fields["q8_153"] == "01_yes" && (empty($fields["q8_192_$options[$j]"])))
					$errors["q8_192_$options[$j]"] = "You must specify";
			}
		}

		if (($fields["q8_153"] == "01_yes") && ($fields["q8_152_a"] == "01_yes" || $fields["q8_152_b"] == "01_yes"))
		{
			for ($i=0; $i<8; $i++)
			{
				if (empty($fields["q8_154_$options[$i]"]))
					$errors["q8_154_$options[$i]"] = "You must specify";
			}
		}


		if (($fields["q8_152_c"] == "01_yes" || $fields["q8_152_d"] == "01_yes") && ($fields["q8_153"] = "01_yes"))
		{
			for ($i=0; $i<12; $i++)
			{
				if (empty($fields["q8_155_$options[$i]"]))
					$errors["q8_155_$options[$i]"] = "You must specify";	
			}
			
			if (empty($fields["q8_157"]))
				$errors["q8_157"] = "You must specify";

			if (empty($fields["q8_160"]))
				$errors["q8_160"] = "You must specify";
		}

                if ($fields["q8_153"] == "01_yes" && (empty($fields["q8_164"])))
                        $errors["q8_164"] = "You must specify";

                if ($fields["q8_153"] == "01_yes" && $fields["q8_152_b"] == "01_yes" && (empty($fields["q8_165a"])))
                        $errors["q8_165a"] = "You must specify";

                if ($fields["q8_153"] == "01_yes" && $fields["q8_152_b"] == "01_yes" && (empty($fields["q8_166"])))
                        $errors["q8_166"] = "You must specify";

                if ($fields["q8_153"] == "01_yes" && $fields["q8_154_c"] == "01_yes" && (empty($fields["q8_170"])))
                        $errors["q8_170"] = "You must specify";

				
		for ($j=0; $j<5; $j++)
		{
			if ($fields["q8_153"] == "01_yes" && $fields["q8_154_d"] == "01_yes" && (empty($fields["q8_176_$options[$j]"])))
				$errors["q8_176_$options[$j]"] = "You must specify";
		}

                for ($j=0; $j<6; $j++)
                {
                	if ($fields["q8_153"] == "01_yes" && $fields["q8_154_f"] == "01_yes" && (empty($fields["q8_184_$options[$j]"])))
                        	$errors["q8_184_$options[$j]"] = "You must specify";
		}

		if ($fields["q8_184_a"] == "01_yes" || $fields["q8_184_b"] == "01_yes")
		{

			for ($i=0; $i<3; $i++)
			{
				if (empty($fields["q8_188_$options[$i]"]))
					$errors["q8_188_$options[$i]"] = "Required if did soldering or brazing";
			}

			if (empty($fields["q8_189"]))
				$errors["q8_189"] = "Required if did soldering or brazing";

			if (empty($fields["q8_190"]))
				$errors["q8_190"] = "Required if did soldering or brazing";

			for ($i=0; $i<9; $i++)
			{
				if (empty($fields["q8_191_$options[$i]"]))
					$errors["q8_191_$options[$i]"] = "Required if did soldering or brazing";
			}
		}

		return $errors;	
	}

} //end EARLI Maternal Interview part 3 =================================================

?>
