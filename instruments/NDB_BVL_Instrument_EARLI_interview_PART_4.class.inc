<?php

require_once 'HTML/QuickForm.php';
require_once 'HTML/QuickForm/Renderer/Array.php';
require_once("RequiredIfGroup.inc");
require_once('RequiredIf.inc');
require_once('NDB_BVL_Instrument_EARLI_interview.class.inc');

class NDB_BVL_Instrument_EARLI_interview_PART_4 extends NDB_BVL_Instrument_EARLI_interview {


	var $dateOptions2007 = array(
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
		$this->testName = "EARLI_interview_PART_4";           // test_names.Test_name
		$this->table = 'EARLI_interview_PART_4';              // name of table containing data keyed by commentID
		$this->commentID = $commentID;
		$this->requiredElements = array('interview_time', 'q8_196_a', 'q8_211', 'q8_273', 'q8_302', 'q8_308', 'q8_321_a', 'q8_342_a', 'q8_366', 'interview_end_date');


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
                                                         'Data_entry_completion_status'
                                                         );
        */
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
	//	$this->form->addFormRule(array(&$this,'XINValidate'));

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
		$this->form->addElement('header', 'instrument_title', "EARLI Maternal Interview Section 8 long (2)");

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



	function _page30(){   // ========================================================

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>OCCUPATION MODULE: Restaurant Worker (RW)");
		$this->form->addElement('static', null, "<br/>");


		//function with more complex rules
		$this->form->addFormRule(array(&$this, 'rulesPage30'));		


		//q8_196
		$this->form->addElement('static', null, "8-196 Did you typically do any of the following? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Clean counters, floors, and equipment", "b"=>"b) Wash dishes", "c"=>"c) Wait on tables", "d"=>"d) See smoke from the grills, fryers, or deep fryers", "e"=>"e) Cut or chop raw meat");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_196_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_196_{$field}", array("q8_196_{$field}{@}=={@}NEVER_REQUIRED"));
		}	

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused], and/or [Don't Know] to [part a-e], end Module and go to 8-13");
		$this->form->addElement('static', null, $this->indent . "If you selected [Yes] to [part d], go to 8-197");
		$this->form->addElement('static', null, $this->indent . "Otherwise [go to 8-198]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

		
		//q8_197
		$this->form->addElement("select", "q8_197", "8-197 Typically, how smoky was the smoke from the grills or deep fryers?",  array(NULL=>"", "01" => "01 Not every smoky", "02" => "02 Slightly smoky", "03" => "03  Moderately smoky", "04" => "04 Very smoky", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_197", array("q8_196_d{@}=={@}01_yes"), "Required if work(ed) around smoke");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_198
		$this->form->addElement('static', null, "8-198 Between [-3] and DOBS, did you ever get...Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Cuts on the hands", "b"=>"b) Blood on your hands");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_198_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_198_{$field}", array("q8_198_{$field}{@}=={@}NEVER_REQUIRED")); 
		}

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: HOUSEHOLD CLEANER USE");
		$this->form->addElement('static', null, "<br/>");


		//q8_199
		$this->form->addElement("select", "q8_199", "8-199 Did you typically use household cleaning products",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_199", array("q8_199{@}=={@}NEVER_REQUIRED")); 
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused], or [Don't Know], end Module and go to Clean Hands Module 8-202");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_200
		$this->form->addElement('static', null, "8-200 Which types of cleaning products did you typically use at work? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Ammonia products", "b"=>"b) Chlorine bleach", "c"=>"c) Floor cleaner", "d"=>"d) Floor polish", "e"=>"e) Floor stripper",  "f"=>"f) Furniture or wood polish",  "g"=>"g) Metal polish",  "h"=>"h) Oven cleaner",  "i"=>"i) Paint stripper",  "j"=>"j) Spot and stain remover or carpet cleaner",  "k"=>"k) Turpertine or mineral spirits",  "l"=>"l) Window or mirror cleaner",  "m"=>"m) Other");

		foreach ($list as $field=>$label)
		{
			$this->form->addElement("select", "q8_200_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_200_{$field}", array("q8_199{@}=={@}01_yes"), "Required if used household cleaning products");
		}

		$this->addTextAreaElementRD('q8_200other', $this->indent . 'If you selected [m) Other], please specify:');
		$this->XINRegisterRule("q8_200other", array("q8_200_m{@}=={@}01_yes"), "You must specify other", "q8_200other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_201
		$this->form->addElement('static', null, "8-201 How often did you use the following cleaning products?");
		$this->form->addElement('static', null, "<i>Probe: How many hours per day, per week or per month did you use the following art supplies?</i>");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Enter number and choose units or select from the list");

		$this->form->addElement('static', null, "<br/>");
		

		foreach ($list as $field=>$label) 
		{
			$this->form->addElement('select', "q8_201_{$field}", "{$label}:", array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->XINRegisterRule("q8_201_{$field}", array("q8_200_{$field}{@}=={@}01_yes"), "Required if used this cleaning products");
			$this->addTextAreaElementRD("q8_201_number{$field}", $this->indent . 'Number:');
			$this->XINRegisterRule("q8_201_number{$field}", array("q8_201_{$field}{@}=={@}01|02|03|04"), "You must specify number", "q8_201_number{$field}_group");
		}

		$this->addTextAreaElementRD("q8_201_other", $this->indent . 'If you selected [m) Other], please specify:');
		$this->XINRegisterRule("q8_201_other", array("q8_201_m{@}=={@}01_yes"), "You must specify other", "q8_201_other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: CLEAN HANDS");
		$this->form->addElement('static', null, "<br/>");


		//q8_202
		$this->form->addElement("select", "q8_202", "8-202 Did you regularly get chemicals or dust on your hands or skin?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, $this->indent . "If you selected [No], end Module and go to 8-205");
		$this->XINRegisterRule("q8_202", array("q8_202{@}=={@}NEVER_REQUIRED")); 
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_203
		$this->form->addElement('static', null, "8-203 When you had chemicals or dust on your hands, when did you wash your hands? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$list = array("a"=>"a) When taking a break at work", "b"=>"b) Before eating", "c"=>"c) Before smoking", "d"=>"d) At the end of the work shift", "e"=>"e) When the task is completed",  "f"=>"f) Whenever I get my hands dirty",  "g"=>"g) Don't wash hands");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_203_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_203_{$field}", array("q8_202{@}=={@}01_yes"), "You must specify");
		}

		$this->form->addElement('static', null, $this->indent . "If you selected [Don't wash hands], end Module and go to to PPE Module 8-205");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_204
		$this->form->addElement('static', null, "8-204 What did you use to wash chemicals or dust off your hands? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$wash = array("a"=>"a) Soap and water or water only", "b"=>"b) [Goop] or similar cleaners", "c"=>"c) Mineral spirits, turpentine, or paint thinner", "d"=>"d) Gasoline or kerosene", "e"=>"e) Something else");

		foreach ($wash as $field=>$label)
		{
			$this->form->addElement("select", "q8_204_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_204_{$field}", array("q8_203_g{@}!={@}01_yes", "q8_203_g{@}!={@}"), "You must specify");
		}

		$this->addTextAreaElementRD('q8_204other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule("q8_204other", array("q8_204_e{@}=={@}01_yes"), "You must specify something else", "q8_204other_group");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: PERSONAL PROTECTIVE EQUIPMENT");
		$this->form->addElement('static', null, "<br/>");


		//q8_205
		$this->form->addElement("select", "q8_205", "8-205 Between [-3] and DOBS, how often did you wear or use personal protective equipment (PPE) to protect you from the things you have mentioned? By personal protective equipment, I mean the things like gloves, dust mask, goggles, aprons, lab coats or other protective clothing, would you say always, often, rarely, or never us personal protective equipment?",  array(NULL=>"", "01" => "01 Always", "02" => "02 Often", "03" => "03  Rarely", "04" => "04 Never", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_205", array("q8_196_a{@}=={@}01_yes"), "You must specify");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If you selected [Never], [Refused], or [Don't Know], end Module and go to Ventilation Module 8-209");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_206
		$this->form->addElement('static', null, "8-206 What did you use to wash chemicals or dust off your hands? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		foreach ($wash as $field=>$label)
		{
			$this->form->addElement("select", "q8_206_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_206_{$field}", array("q8_205{@}=={@}01|02|03"), "You must specify");
		}

		$this->addTextAreaElementRD('q8_206other', $this->indent . 'If you selected [j) Something else], please specify:');
		$this->XINRegisterRule("q8_206other", array("q8_206_j{@}=={@}01_yes"), "You must specify something else", "q8_206other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_207
		$this->form->addElement('static', null, "8-207 Which type of protective clothing or equipment did you wear? Code all that apply.");
		$this->form->addElement('static', null, "<i>PROBE: Any other protective clothing or equipment?</i>");
		$this->form->addElement('static', null, "<br/>");

		foreach ($this->protectiveEquipment as $field=>$label)
		{
			$this->form->addElement("select", "q8_207_{$field}", "{$label}:",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_207_{$field}", array("q8_205{@}=={@}01|02|03"), "You must specify");
		}

		$this->addTextAreaElementRD('q8_207other', $this->indent . 'If you selected [Other], please specify:');
		$this->XINRegisterRule("q8_207other", array("q8_207_h{@}=={@}01_yes"), "You must specify other", "q8_207other_group");
		$this->form->addElement('static', null, $this->indent . "If you selected [Yes] for [part e], go to 8-208");
		$this->form->addElement('static', null, "Otherwise, end Module and go to Ventilation Module - starts on 8-209");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_208
		$this->form->addElement("select", "q8_208", "8-208 What type of respirator was it?", array(NULL=>"", "01" => "01 A half-mask chemical cartridge respirator", "02" => "02 A full-mask chemical cartridge respirator", "03" => "03  An air-supplied or SCBA respirator", "04" => "04 Some other kind of respirator?", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_208", array("q8_207_e{@}=={@}01_yes"), "You must specify type of respirator");
		$this->addTextAreaElementRD('q8_208other', $this->indent . 'If you selected [Some other kind of respirator], please specify:');
		$this->XINRegisterRule("q8_208other", array("q8_208{@}=={@}04"), "You must specify other", "q8_208other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: VENTILATION & ENCLOSURES");
		$this->form->addElement('static', null, "<br/>");


		//q8_209
		$this->form->addElement("select", "q8_209", "8-209 Was there any kind of a ventilation system to remove exhaust, dust, smoke or fumes from the area?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_209", array("q8_209{@}=={@}NEVER_REQUIRED")); 
		$this->form->addElement('static', null, "<i>Probe: By ventilation system we mean purposely opening windows or doors, using a fume hood, or other ventilation system.</i>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused], or [Don't Know], end Module and go to 8-13");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_210
		$this->form->addElement('static', null, "8-210 What ventilation systems were present to remove exhaust, dust, smoke or fumes from the area? Are there...Code all that apply.");
		$this->form->addElement('static', null, "<br/>");

		foreach ($this->ventilators as $field=>$label)
		{
			$this->form->addElement("select", "q8_210_{$field}", "{$label}:",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_210_{$field}", array("q8_209{@}=={@}01_yes"), "You must specify ventilation systems");
		}

		$this->addTextAreaElementRD('q8_210other', $this->indent . 'Please specify:');
		$this->XINRegisterRule("q8_210other", array("q8_210_f{@}=={@}01_yes"), "You must specify other", "q8_210other_group");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>When occupational module is complete, and there are NO more Occupational Modules to Complete listed in the Occupational Coding Box, go to 8-13");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


	} //end function _page30() =====================================================




	function rulesPage30($fields)
	{
		$errors = array();

		$options = array("a", "b", "c", "d", "e");

                $db =& Database::singleton();

		$otherCommentID = $db->selectOne("SELECT CommentID from flag where Test_name='EARLI_interview_PART_3' and SessionID=" . $this->getSessionID()); 

                $db->selectRow("SELECT q8_5, q8_6_3 FROM EARLI_interview_PART_3 WHERE CommentID='". $otherCommentID."'", $occupation);


//		$occupation = getOccupation("q8_5", "q8_6_3");

		if ($occupation["q8_5"] == "03")
		{
			for ($i=0; $i<5; $i++)
			{
				if(empty($fields["q8_196_$options[$i]"]))
					$errors["q8_196_$options[$i]"] = "You must specify";
			}
		}

		if ($occupation["q8_5"] == "09" && ($occupation["q8_6_3"] >= "14" && $occupation["q8_6_3"] <= "18"))
		{
                        for ($i=0; $i<5; $i++)
                        {
                                if(empty($fields["q8_196_$options[$i]"]))
                                        $errors["q8_196_$options[$i]"] = "You must specify";
                        }
		}	

		
		for ($i=0; $i<5; $i++)
		{
			if ($fields["q8_196_$options[$i]"] == "01_yes")
			{
				if (empty($fields["q8_198_a"]))
					$errors["q8_198_a"] = "Required if did any of the above";

				if (empty($fields["q8_198_b"]))
					$errors["q8_198_b"] = "Required if did any of the above";

				if (empty($fields["q8_199"]))
					$errors["q8_199"] = "You must specify";
				
				if (empty($fields["q8_202"]))
					$errors["q8_202"] = "You must specify";
				
				if (empty($fields["q8_205"]))
					$errors["q8_205"] = "You must specify";			

				if (empty($fields["q8_209"]))
					$errors["q8_209"] = "You must specify";
			}
		}

		return $errors;
	}



	function _page31(){   // ========================================================

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>OCCUPATION MODULE: Cleaners & building maintenance worker (CM)");
		$this->form->addElement('static', null, "<br/>");


		//function with more complex rules
		$this->form->addFormRule(array(&$this, 'rulesPage31'));


		//q8_211
		$this->form->addElement("select", "q8_211", "8-211 Did you conduct any building maintenance activities?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No", "88_refused" => "88 Refused", "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_211", array("q8_211{@}=={@}NEVER_REQUIRED"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>BOX CM-1");
		$this->form->addElement('static', null, "If you selected [Yes] to [8-211], go to 8-212");
		$this->form->addElement('static', null, "Otherwise, go to Household Cleaners Module - starts on 8-263a");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_212
		$this->form->addElement('static', null, "8-212 Did you maintain...Code all that apply:");
		$list = array("a"=>"a) A furnace or boiler", "b"=>"b) AC equipment");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_212_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_212_{$field}", array("q8_211{@}=={@}01_yes"), "Required if conducted building maintenance");
		}	

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>BOX CM-2");
		$this->form->addElement('static', null, "If you selected [Yes] to [part a in 8-212], go to 8-213 and 8-214");
		$this->form->addElement('static', null, "Otherwise, go to Lubricating Module - starts on 8-215");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_213
		$this->form->addElement('static', null, "8-213 What type of fuel was usually used to power the furnace or boiler? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Oil", "b"=>"b) Electricity", "c"=>"c) Methane gas", "d"=>"d) Natural gas", "e"=>"e) Coal",  "f"=>"f) Something else");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_213_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_213_{$field}", array("q8_212_a{@}=={@}01_yes"), "Required if maintained a furnace or boiler");
		}

		$this->addTextAreaElementRD('q8_213other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule("q8_213other", array("q8_213_f{@}=={@}01_yes"), "You must specify something else", "q8_213other_group");
		$this->form->addElement('static', null, "<br/>");


		//q8_214
		$this->form->addElement('static', null, "8-214 How often did you use or work around the following heating fuels?");
		$this->form->addElement('static', null, "<i>Probe: How many hours per day, per week or per month did you use the following art supplies?</i>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Enter number and choose units or select from the list");
		$this->form->addElement('static', null, "<br/>");

		$list = array("a"=>"a) Oil", "b"=>"b) Electricity", "c"=>"c) Methane gas", "d"=>"d) Natural gas", "e"=>"e) Coal",  "f"=>"f) Something else");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement('select', "q8_214_{$field}", "{$label}:",  array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->XINRegisterRule("q8_214_{$field}", array("q8_212_a{@}=={@}01_yes"), "Required if maintained a furnace or boiler");
			$this->addTextAreaElementRD("q8_214_number{$field}", $this->indent . 'Number:');
			$this->XINRegisterRule("q8_214_number{$field}", array("q8_214_{$field}{@}=={@}01|02|03|04"), "You must specify number", "q8_214_number{$field}_group");
		}

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: LUBRICATING ENGINES & MACHINERY");
		$this->form->addElement('static', null, "<br/>");


		//q8_215
		$this->form->addElement("select", "q8_215", "8-215 Did you routinely use lubricating oils, or waxes on engines or machinery?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_215", array("q8_211{@}=={@}01_yes"), "Required if conducted building maintenance activities");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused], or [Don't Know], end Module and go to 8-219");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_216
		$this->addTextAreaElementRD("q8_216", "8-216 What types of lubricants did you work with?");
		$this->XINRegisterRule("q8_216", array("q8_215{@}=={@}01_yes"), "Required if use lubricating oils or waxes", "q8_216_group");
		$this->form->addElement('static', null, "<br/>");


		//q8_217
		$this->form->addElement('static', null, "8-217 What types of cutting oils did you work with? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Straight cutting oils or oils that look and feel like motor oil", "b"=>"b) Soluble cutting oils or oils that are milky white", "c"=>"c) Synthetic cutting oils or oils that feel like water or may be brightly colored, such as green or blue", "d"=>"d) Something else");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_217_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_217_{$field}", array("q8_211{@}=={@}01_yes"), "Required if conducted building maintenance activities");
		}

		$this->addTextAreaElementRD('q8_217other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule("q8_217other", array("q8_217_d{@}=={@}01_yes"), "You must specify something else", "q8_217other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_218
		$this->form->addElement('static', null, "8-218 How often did you use the following lubricants?");
		$this->form->addElement('static', null, "<i>Probe: How many hours per day, per week or per month did you use the following lubricants?</i>");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Straight cutting oils or oils that look and feel like motor oil", "b"=>"b) Soluble cutting oils or oils that are milky white", "c"=>"c) Synthetic cutting oils or oils that feel like water or may be brightly colored, such as green or blue", "d"=>"d) Something else");

		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement('select', "q8_218_{$field}", "{$label}:", array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->XINRegisterRule("q8_218_{$field}", array("q8_211{@}=={@}01_yes"), "Required if conducted building maintenance activities");
			$this->addTextAreaElementRD("q8_218_number{$field}", $this->indent . 'Number:');
			$this->XINRegisterRule("q8_218_number{$field}", array("q8_218_{$field}{@}=={@}01|02|03|04"), "You must specify a number", "q8_218_number{$field}_group");
		}

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: CLEANING WITH ORGANIC SOLVENTS");
		$this->form->addElement('static', null, "<br/>");


		//q8_219
		$this->form->addElement("select", "q8_219", "8-219 Did you routinely clean parts with organic solvents or other products to degrease metal parts?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_219", array("q8_211{@}=={@}01_yes"), "Required if conducted building maintenance activities");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused], or [Don't Know], end Module and go to 8-223");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_220
		$this->form->addElement('static', null, "8-220 What cleaning products did you typically use? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) [Gunk] or similar cleaner", "b"=>"b) Acid", "c"=>"c) Alcohols", "d"=>"d) Alkalis or caustics", "e"=>"e) Cutting oils",  "f"=>"f) Diesel",  "g"=>"g) Gasoline",  "h"=>"h) Mineral spirits, paint thinner, naphtha, Stoddard solvent, turpentin", "i"=>"i) Something else");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_220_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_220_{$field}", array("q8_219{@}=={@}01_yes"), "Required if cleaned parts with organic solvents or other products");
		}

		$this->addTextAreaElementRD('q8_220other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule("q8_220other", array("q8_220_i{@}=={@}01_yes"), "You must specify something else", "q8_220other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_221
		$this->form->addElement('static', null, "8-221 How often did you use the following cleaning products?");
		$this->form->addElement('static', null, "<i>Probe: How many hours per day, per week or per month did you use the following cleaning products?</i>");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) [Gunk] or similar cleaner", "b"=>"b) Acid", "c"=>"c) Alcohols", "d"=>"d) Alkalis or caustics", "e"=>"e) Cutting oils",  "f"=>"f) Diesel",  "g"=>"g) Gasoline",  "h"=>"h) Mineral spirits, paint thinner, naphtha, Stoddard solvent, turpentin", "i"=>"i) Something else");
		reset($list);

		while(list($field, $label) = each($list)){

			$this->form->addElement('select', "q8_221_{$field}", "{$label}:", array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->XINRegisterRule("q8_221_{$field}", array("q8_219{@}=={@}01_yes"), "Required if cleaned parts with organic solvents or other products");
			$this->addTextAreaElementRD("q8_221_number{$field}", $this->indent . 'Number:');
			$this->XINRegisterRule("q8_221_number{$field}", array("q8_221_{$field}{@}=={@}01|02|03|04"), "You must specify a number", "q8_221_number{$field}_group");
		}

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

		
		//q8_222
		$this->form->addElement("select", "q8_222", "8-222 How often did you work with heating degreasing chemicals?",  array(NULL=>"", "01" => "01 Always", "02" => "02 Sometimes", "03" => "03  Never", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_222", array("q8_219{@}=={@}01_yes"), "Required if cleaned parts with organic solvents or other products");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: PAINTING, PAINT REMOVAL, PAINT CLEANING");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>The next few questions ask about painting, varnishing, and staining.");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_223
		$this->form->addElement('static', null, "8-223 Did you typically do any of the following activities? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$list = array("a"=>"a) Painting, varnishing, or staining", "b"=>"b) Paint removal", "c"=>"c) Paint thinning and cleaning", "d"=>"d) Something else", "e"=>"e) None of the above");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_223_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_223_{$field}", array("q8_211{@}=={@}01_yes"), "Required if conducted building maintenance activities");
		}

		$this->addTextAreaElementRD('q8_223other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule("q8_223other", array("q8_223_d{@}=={@}01_yes"), "You must specify something else", "q8_223other_group");
		$this->form->addElement('static', null, $this->indent . "If you selected [None of the above], end Module and go to 8-231");
		$this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] and/or [Don't Know] to <u>all</u>, end Module and go to 8-231");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>BOX PT-1");
		$this->form->addElement('static', null, "If you selected [Yes] to [part a in 8-223], go to 8-224, 8-225, 8-226");
		$this->form->addElement('static', null, "Otherwise [go to Box PT-2]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_224
		$this->form->addElement('static', null, "8-224 What kind of paint did you use? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Laytex or water-based paint", "b"=>"b) Acrylic", "c"=>"c) Oil-based paint (enamel)", "d"=>"d) Something else");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_224_{$field}", "{$label}:",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_224_{$field}", array("q8_223_a{@}=={@}01_yes"), "Required if did painting, varnishing or staining");
		}

		$this->addTextAreaElementRD('q8_224other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule("q8_224other", array("q8_224_d{@}=={@}01_yes"), "You must specify something else", "q8_224other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_225
		$this->form->addElement('static', null, "8-225 Did you usually brush, roll, or spray paint? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Brush", "b"=>"b) Roll", "c"=>"c) Spray", "d"=>"d) Something else");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_225_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_225_{$field}", array("q8_223_a{@}=={@}01_yes"), "Required if did painting, varnishing or staining");
		}

		$this->addTextAreaElementRD('q8_225other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule("q8_225other", array("q8_225_d{@}=={@}01_yes"), "You must specify something else", "q8_225other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

		
		//q8_226
		$this->form->addElement("select", "q8_226", "8-226 Did you use primers with lead, chromate, or zinc?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_226", array("q8_223_a{@}=={@}01_yes"), "Required if did painting, varnishing or staining");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>BOX PT-2");
		$this->form->addElement('static', null, "If you selected [Yes] to [part b in 8-223], go to 8-227");
		$this->form->addElement('static', null, "Otherwise [go to Box PT-3]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_227
		$this->form->addElement('static', null, "8-227 How did you typically remove paint? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Heat gun", "b"=>"b) Scraper or wire stripper with a drill bit attachment", "c"=>"c) Chemical paint stripper", "d"=>"d) Some other paint removal method");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_227_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_227_{$field}", array("q8_223_b{@}=={@}01_yes"), "Required if removed paint");
		}

		$this->addTextAreaElementRD('q8_227other', $this->indent . 'If you selected [Some other paint removal method], please specify:');
		$this->XINRegisterRule("q8_227other", array("q8_227_d{@}=={@}01_yes"), "You must specify something else", "q8_227other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>BOX PT-3");
		$this->form->addElement('static', null, "If you selected [Yes] to [part c in 8-223], go to 8-228");
		$this->form->addElement('static', null, "Otherwise [go to 8-230]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_228
		$this->form->addElement('static', null, "8-228 What did you typically use to thin or clean paint, varnish or stain? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Paint thinner, mineral spirits, or turpertin", "b"=>"b) Lacquer thinner", "c"=>"c) Alcohol", "d"=>"d) Water", "e"=>"e) Citrus-based products",  "f"=>"f) Gasoline or kerosene",  "g"=>"g) Other");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_228_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_228_{$field}", array("q8_223_c{@}=={@}01_yes"), "Required if did paint thinning and cleaning");
		}

		$this->addTextAreaElementRD('q8_228other', $this->indent . 'If you selected [Other], please specify:');
		$this->XINRegisterRule("q8_228other", array("q8_228_g{@}=={@}01_yes"), "You must specify other", "q8_228other_group");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>BOX PT-4");
		$this->form->addElement('static', null, "If you selected [Yes] to [part c in 8-227], go to 8-229");
		$this->form->addElement('static', null, "Otherwise [go to 8-230]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_229
		$this->form->addElement('static', null, "8-229 What chemicals did you use to strip paint? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Lacquer or paint thinner", "b"=>"b) Lye (Sodium hydroxide)", "c"=>"c) Ammonia (Ammonia Hydroxide)", "d"=>"d) Other");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_229_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_229_{$field}", array("q8_227_c{@}=={@}01_yes"), "Required if used chemical paint strippers");
		}

		$this->addTextAreaElementRD('q8_229other', $this->indent . 'If you selected [Other], please specify:');
		$this->XINRegisterRule("q8_229other", array("q8_229_d{@}=={@}01_yes"), "You must specify other", "q8_229other_group");
		$this->form->addElement('static', null, "<br/>");


		//q8_230
		$this->form->addElement('static', null, "8-230 How often did you use the following paint, paint thinners, or paint strippers?");
		$this->form->addElement('static', null, "<i>Probe: How many hours per day, per week or per month did you use the following paint, paint thinners, or paint strippers?i</i>");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Laytex or water-based paint", "b"=>"b) Acrylic", "c"=>"c) Oil-based paint (enamel)","d"=>"d) Paint thinner, mineral spirits, or turpertin", "e"=>"e) Lacquer thinner", "f"=>"f) Alcohol", "g"=>"g) Water", "h"=>"h) Citrus-based products",  "i"=>"i) Gasoline or kerosene", "j"=>"j) Lacquer or paint thinner", "k"=>"k) Lye (Sodium hydroxide)", "l"=>"l) Ammonia (Ammonia Hydroxide)", "m"=>"m) Other" );

		reset($list);
		while(list($field, $label) = each($list)){

			$this->form->addElement('select', "q8_230_{$field}", "{$label}:", array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->XINRegisterRule("q8_230_{$field}", array("q8_223_c{@}=={@}01_yes"), "Required if did painting, paint thinning, or paint stripping");
			$this->addTextAreaElementRD("q8_230_number{$field}", $this->indent . 'Number:');
			$this->XINRegisterRule("q8_230_number{$field}", array("q8_230_{$field}{@}=={@}01|02|03|04"), "You must specify a number", "q8_230_number{$field}_group");
		}

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: WOOD DUST");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_231
		$this->form->addElement('static', null, "8-231 Did you typically do any of the following? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$activities = array("a"=>"a) Saw wood", "b"=>"b) Sand wood", "c"=>"c) Machine or make wood parts", "d"=>"d) Use a wood chipper", "e"=>"e) Other activities that generate wood",  "f"=>"f) None of these");

		foreach ($activities as $field=>$label)
		{
			$this->form->addElement("select", "q8_231_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_231_{$field}", array("q8_211{@}=={@}01_yes"), "Required if did any building maintenance activities");
		}

		$this->addTextAreaElementRD('q8_231other', $this->indent . 'If you selected [Other activities that generate wood], please specify:');
		$this->XINRegisterRule("q8_231other", array("q8_231_d{@}=={@}01_yes"), "You must specify other", "q8_231other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If you selected [None of these], go to 8-233");
		$this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] and/or [Don't Know] for <u>all</u>, go to 8-233");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_232
		$this->form->addElement('static', null, "8-232 How often did you do these things?");
		$this->form->addElement('static', null, "<i>Probe: How many hours per day, per week, or per month do you saw wood, sand wood, do machining, make wood parts, use a wood chipper, or other activities that generate wood dust?</i>");
		$this->form->addElement('static', null, "<br/>");

		foreach ($activities as $field=>$label)
		{
			$this->form->addElement('select', "q8_232_{$field}", "{$label}:", array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->XINRegisterRule("q8_232_{$field}", array("q8_231_{$field}{@}=={@}01_yes"), "Required if did any of the above activities");
			$this->addTextAreaElementRD("q8_232_number{$field}", $this->indent . 'Number:');
			$this->XINRegisterRule("q8_232_number{$field}", array("q8_232_{$field}{@}=={@}01|02|03|04"), "You must specify a number", "q8_232_number{$field}");
		}

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_233
		$this->form->addElement("select", "q8_233", "8-233 Did your job typically involve handling treated lumber, that is wood treated with chemical preservatives and has a greenish appearance?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_233", array("q8_211{@}=={@}01_yes"), "Required if did any building maintenance activities");
		$this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know], end Module and go to 8-239");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_234
		$this->form->addElement('static', null, "8-234 What did you do with the treated wood or lumber? Did you...Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Handle it, carry it, or move it", "b"=>"b) Saw or cut it", "c"=>"c) Sand it", "d"=>"d) Something else?");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_234_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_234_{$field}", array("q8_233{@}=={@}01_yes"), "Required if handled treated lumber");
		}

		$this->addTextAreaElementRD('q8_234other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule("q8_234other", array("q8_234_d{@}=={@}01_yes"), "You must specify something else", "q8_234other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_235
		$this->form->addElement("select", "q8_235", "8-235 When you handled the treated wood, was it usually wet or dry?",  array(NULL=>"", "01_wet" => "01 Wet", "02_dry" => "02 Dry", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_235", array("q8_233{@}=={@}01_yes"), "Required if handled treated lumber");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_236
		$this->form->addElement("select", "q8_236", "8-236 Did you apply a preservative, such as cresotoe, to the wood yourself?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_236", array("q8_233{@}=={@}01_yes"), "Required if handled treated lumber");
		$this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know], skip to question 8-238");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_237
		$this->form->addElement('static', null, "8-237 What preservatives did you use to treat the wood? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Pentachlorophenol or PCP", "b"=>"b) Inorganic chemicals, such as copper chromium, arsenate, also called CCA or ACA", "c"=>"c) Creosote", "d"=>"d) Something else");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_237_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_237_{$field}", array("q8_236{@}=={@}01_yes"), "Required if applied preservative(s) to the wood");
		}

		$this->addTextAreaElementRD('q8_237other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule("q8_237other", array("q8_237_d{@}=={@}01_yes"), "You must specify something else", "q8_237other_group");
		$this->form->addElement('static', null, "<br/>");


		//q8_238
		$this->form->addElement('static', null, "8-238 How often did you handle treated wood?");
		$this->form->addElement('static', null, "<i>Probe: How many hours per day, per week, or per month did you handle treated wood?</i>");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Pentachlorophenol or PCP", "b"=>"b) Inorganic chemicals, such as copper chromium, arsenate, also called CCA or ACA", "c"=>"c) Creosote", "d"=>"d) Something else");

		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement('select', "q8_238_{$field}", "{$label}:", array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->XINRegisterRule("q8_238_{$field}", array("q8_233{@}=={@}01_yes"), "Required if handled treated lumber");
			$this->addTextAreaElementRD("q8_238_number{$field}", $this->indent . 'Number:');
			$this->XINRegisterRule("q8_238_number{$field}", array("q8_238_{$field}{@}=={@}01|02|03|04"), "You must specify a number", "q8_238_number{$field}_group");	
		}

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: PESTICIDE USE");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_239
		$this->form->addElement("select", "q8_239", "8-239 Pesticides include many types of chemicals used to repel, kill, or control unwanted weeds, insects, rodents, fungi, or bacteria. They include herbicides, insecticides, rodenticides, fungicides, and bactericides. Did you mix, apply, spray, process or use pesticides?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_239", array("q8_211{@}=={@}01_yes"), "Required if did any building maintenance activities");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know], skip to question 8-262");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_240
		$this->form->addElement('static', null, "8-240 Between [3] and DOBS, which types of pesticides did you use? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$pesticides = array("a"=>"a) Insecticides which kill bugs", "b"=>"b) Herbicides or weed killer", "c"=>"c) Rodenticides which kill rats and mice", "d"=>"d) Fungicides which kill mold or fungus", "e"=>"e) Bactericides which kill bacteria",  "f"=>"f) Something else?");

		foreach ($pesticides as $field=>$label)
		{
			$this->form->addElement("select", "q8_240_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_240_{$field}", array("q8_239{@}=={@}01_yes"), "Required if handled pesticides");
		}

		$this->addTextAreaElementRD('q8_240other', $this->indent . 'If you selected [f) Something else], please specify:');
		$this->XINRegisterRule("q8_240other", array("q8_240_f{@}=={@}01_yes"), "You must specify something else", "q8_240other_group");
		$this->form->addElement('static', null, $this->indent . "If you selected [No] to <u>all</u> a-f,go to 8-52");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_241
		$this->form->addElement('static', null, "8-241 Where did you use the pesticides? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$list = array("a"=>"a) In or around buildings", "b"=>"b) On crops", "c"=>"c) On forests", "d"=>"d) On roads", "e"=>"e) On seeds", "f"=>"f) On animals", "g"=>"g) For aquatic pest control", "h"=>"h) To process, pack, or manufacture them at warehouse or factory",  "i"=>"i) Something else?");


		foreach ($list as $field=>$label)
		{
			$this->form->addElement("select", "q8_241_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_241_{$field}", array("q8_239{@}=={@}01_yes"), "You must specify locaiton(s)");
		}

	        $this->addTextAreaElementRD('q8_241other', $this->indent . 'If you selected [i) Something else], please specify:');
		$this->XINRegisterRule("q8_241other", array("q8_241_i{@}=={@}01_yes"), "You must specify something else", "q8_241other_group");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box PU-1");
		$this->form->addElement('static', null, "If you selected [Yes] to [part a in 8-240], go to 8-242");
		$this->form->addElement('static', null, "Otherwise, go to Box PU-2");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_242
		$this->addTextAreaElementRD('q8_242', "8-242 You said that you used insecticides or bug killers. Please name all that you used");
		$this->XINRegisterRule("q8_242", array("q8_240_a{@}=={@}01_yes"), "Required if used insecticides", "q8_242_group");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box PU-2");
		$this->form->addElement('static', null, "If you selected [Yes] to [part b in 8-240], go to 8-243");
		$this->form->addElement('static', null, "Otherwise, go to Box PU-3");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_243
		$this->addTextAreaElementRD('q8_243', "8-243 You said that you used herbicides or weed killers.");
		$this->XINRegisterRule("q8_243", array("q8_240_b{@}=={@}01_yes"), "Required if used herbicides", "q8_243_group");
				
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box PU-3");
		$this->form->addElement('static', null, "If you selected [Yes] to [part c in 8-240], go to 8-244");
		$this->form->addElement('static', null, "Otherwise, go to Box PU-4");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_244
		$this->addTextAreaElementRD('q8_244', "8-244 You said that you used rodenticides. Please name all that you use");
		$this->XINRegisterRule("q8_244", array("q8_240_c{@}=={@}01_yes"), "Required if used rodenticides", "q8_244_group");
				

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box PU-4");
		$this->form->addElement('static', null, "If you selected [Yes] to [part d in 8-240], go to 8-245");
		$this->form->addElement('static', null, "Otherwise, go to Box PU-5");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_245
		$this->addTextAreaElementRD('q8_245', "8-245 You said that you used fungicides or mold and fungus killers. Please name all that you use");
		$this->XINRegisterRule("q8_245", array("q8_240_d{@}=={@}01_yes"), "Required if used fungicides", "q8_245_group");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box PU-5");
		$this->form->addElement('static', null, "If you selected [Yes] to [part e in 8-240], go to 8-246");
		$this->form->addElement('static', null, "Otherwise, go to 8-247");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_246
		$this->addTextAreaElementRD('q8_246', "8-246 You said that you used bactericides or bacteria killers. Please name all that you use");
		$this->XINRegisterRule("q8_246", array("q8_240_e{@}=={@}01_yes"), "Required if used bactericides", "q8_246_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_247
		$this->form->addElement('static', null, "8-247 How often did you use the following pesticide products?");
		$this->form->addElement('static', null, "<i>Probe: How many hours per day, per week or per month do you use the following glues or adhesives?</i>");
		$this->form->addElement('static', null, "<br/>");

		foreach ($pesticides as $field=>$label)
		{

			$this->form->addElement('select', "q8_247_{$field}", "{$label}:",  array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->XINRegisterRule("q8_247_{$field}", array("q8_240_{$field}{@}=={@}01_yes"), "Required if used this product");
			$this->addTextAreaElementRD("q8_247_number{$field}", $this->indent . 'Number:');
			$this->XINRegisterRule("q8_247_number{$field}", array("q8_247_{$label}{@}=={@}01|02|03|04"), "You must specify something else", "q8_247_number{$field}_group");
		}

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_248
		$this->form->addElement('static', null, "8-248 Which of the following activities did you typically do? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$pesticideActivities = array("a"=>"a) Mix pesticides", "b"=>"b) Put pesticides into a spray container or tank", "c"=>"c) Spray or apply pesticides", "d"=>"d) Dispose of waste from pesticide use", "e"=>"e) Something else?");

		foreach ($pesticideActivities as $field=>$label)
		{
			$this->form->addElement("select", "q8_248_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_248_{$field}", array("q8_239{@}=={@}01_yes"), "Required if handled pesticides");
		}

		$this->addTextAreaElementRD('q8_248other', $this->indent . 'If you selected [e) Something else], please specify:');
		$this->XINRegisterRule("q8_248other", array("q8_248_e{@}=={@}01_yes"), "You must specify something else", "q8_248other_group");
		$this->form->addElement('static', null, "<br/>");


		//q8_249
		$this->form->addElement("select", "q8_249", "8-249 Between [-3] and DOBS, were there 3 or more times when your clothing has gotten wet with pesticides?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_249", array("q8_239{@}=={@}01_yes"), "Required if handled pesticides");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box PU-6");
		$this->form->addElement('static', null, $this->indent . "If you selected [Yes] to [part b in 8-241], go to 8-250");
		$this->form->addElement('static', null, $this->indent . "Otherwise, go to Box PU-10");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_250
		$this->form->addElement('static', null, "8-250 You said that you apply pesticides to crops. How did you usually apply them? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$pesticideApplications = array("a"=>"a) Using hand-held devices", "b"=>"b) By tractor or truck", "c"=>"c) By aircraft", "d"=>"d) Something else?");

		foreach ($pesticideApplications as $field=>$label)
		{
			$this->form->addElement("select", "q8_250_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_250_{$field}", array("q8_241_b{@}=={@}01_yes"), "Required if used pesticides on crops");
		}

		$this->addTextAreaElementRD('q8_250other', $this->indent . 'If you selected [d) Something else], please specify:');
		$this->XINRegisterRule("q8_250other", array("q8_250_d{@}=={@}01_yes"), "You must specify something else", "q8_250other_group");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box PU-7");
		$this->form->addElement('static', null, "If you selected [Yes] to [part a in 8-250], go to 8-251");
		$this->form->addElement('static', null, "Otherwise, go to Box PU-8");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_251
		$this->form->addElement('static', null, "8-251 What type of hand-operated devices did you usually use? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$handDevices = array("a"=>"a) Pressurized can or aerosols", "b"=>"b) Pressurized cylinders", "c"=>"c) Trigger pump sprayers or squirt guns", "d"=>"d) Hose-end sprayers", "e"=>"e) Compressed air sprayers worn on the back pack or slung over the shoulder",  "f"=>"f) Push-pull hand pump sprayer",  "g"=>"g) Something else?");

		foreach ($handDevices as $field=>$label)
		{
			$this->form->addElement("select", "q8_251_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_251_{$field}", array("q8_250_a{@}=={@}01_yes"), "Required if applied pesticides with hand-operated devices");
		}

		$this->addTextAreaElementRD('q8_251other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule("q8_251other", array("q8_251_g{@}=={@}01_yes"), "You must specify something else", "q8_251other_group");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box PU-8");
		$this->form->addElement('static', null, "If you selectd [Yes] to [part b or c in 8-250], go to 8-252");
		$this->form->addElement('static', null, "Otherwise, go to Box PU-9");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_252
		$this->form->addElement('static', null, "8-252 What type of pesticide application device did you use for your vehicle or aircraft? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$vehicleDevices = array("a"=>"a) Low-pressure boomless sprayer", "b"=>"b) Boom sprayer", "c"=>"c) High pressure hydraulic sprayers", "d"=>"d) Air-blast sprayer", "e"=>"e) Low-volume air sprayer or mist blower",  "f"=>"f) Ultra-low volume or ULV sprayer (IF NEEDED: uses fine droplets with little water)",  "g"=>"g) Something else?");


		foreach ($vehicleDevices as $field=>$label)
		{
			$this->form->addElement("select", "q8_252_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_252_{$field}", array("q8_252_{$field}{@}=={@}NEVER_REQUIRED"));
		}

		$this->addTextAreaElementRD('q8_252other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule("q8_252other", array("q8_252{@}=={@}01_yes"), "You must specify something else", "q8_252other_group");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box PU-9");
		$this->form->addElement('static', null, "If you selected [Yes] to [part b in 8-250], go to 8-253 and 8-254");
		$this->form->addElement('static', null, "Otherwise, go to Box PU-10");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_253
		$this->form->addElement("select", "q8_253", "8-253 Did the vehicle you used for this usually have a cab?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_253", array("q8_250_b{@}=={@}01_yes"), "Required if applied pesticides by tractor or truck.");
		$this->form->addElement('static', null, "<br/>");


		//q8_254
		$this->form->addElement("select", "q8_254", "8-254 Did you usually keep the windows open or closed?",  array(NULL=>"", "01" => "01 Open", "02" => "02 Closed", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_254", array("q8_250_b{@}=={@}01_yes"), "Required if applied pesticides by tractor or truck.");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box PU-10");
		$this->form->addElement('static', null, "If you selected [Yes] to [part b,c or d in 8-241], go to 8-255");
		$this->form->addElement('static', null, $this->indent . "Otherwise, go to Box PU-13");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_255
		$this->form->addElement('static', null, "8-255 What form of pesticide did you apply? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$pesticideForm = array("a"=>"a) Liquid", "b"=>"b) Dust", "c"=>"c) Granules (typically used for landscaping)", "d"=>"d) Something else?");

		foreach ($pesticideForm as $field=>$label)
		{
			$this->form->addElement("select", "q8_255_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_255_{$field}", array("q8_255_{$field}{@}=={@}NEVER_REQUIRED"));
		}

		$this->addTextAreaElementRD('q8_255other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule("q8_255other", array("q8_255_d{@}=={@}01_yes"), "You must specify something else", "q8_255other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box PU-11");
		$this->form->addElement('static', null, "If you selected [Yes] to [part a in 8-255], go to 8-256");
		$this->form->addElement('static', null, "Otherwise, go to Box PU-12");
		$this->form->addElement('static', null, "<br/><br />");


		//q8_256
		$this->form->addElement('static', null, "8-256 What type of liquid did you apply? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$liquidPesticides = array("a"=>"a) Coarse, which are produced by coarse disk or solid stream gun nozzles", "b"=>"b) Fine, which are produced by high pressure hollowcone and fan-spray nozzles", "c"=>"c) Mists, which are produced by high pressure pumps, rotors and atomizers", "d"=>"d) Aerosols and fogs, which are produced by thermal aerosol generators, rotors and atomizers", "e"=>"e) Smokes and fumes, which are produced by thermal fog generators",  "f"=>"f) Vapors, which are droplets less than 0.001 micron",  "g"=>"g) Something else");


		foreach ($liquidPesticides as $field=>$label)
		{
			$this->form->addElement("select", "q8_256_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_256_{$field}", array("q8_255_a{@}=={@}01_yes"), "Required if applied liquid pesticides");	
		}

		$this->addTextAreaElementRD('q8_256other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule('q8_256other', array("q8_256_g{@}=={@}01_yes"), "You must specify something else", "q8_256other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box PU-12");
		$this->form->addElement('static', null, "If you selected [Yes] to [part b in 8-255], go to 8-257");
		$this->form->addElement('static', null, $this->indent . "Otherwise, go to Box PU-13");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_257
		$this->form->addElement('static', null, "8-257 What type of dust did you apply? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$dustPesticides = array("a"=>"a) Coarse", "b"=>"b) Medium", "c"=>"c) Fine");

		foreach ($dustPesticides as $field=>$label)
		{
			$this->form->addElement("select", "q8_257_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_257_{$field}", array("q8_255_b{@}=={@}01_yes"), "Required if applied dust pesticides");	
		}

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box PU-13");
		$this->form->addElement('static', null, "If you selected [Yes] to [part f in 8-241], go to 8-258 and 8-259");
		$this->form->addElement('static', null, "Otherwise, go to Box PU-14");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_258
		$this->form->addElement("select", "q8_258", "8-258 You said that you applied pesticides to animals. What type of animals did you typically apply pesticides to?",  array(NULL=>"", "01" => "01 Farm animals", "02" => "02 Companion animals, such as dogs and cats", "03" => "03  Both farm animals and companion animals", "04" => "04 Some other type of animal?", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_258", array("q8_241_f{@}=={@}01_yes"), "Required if applied pesticides on animals");	
		$this->addTextAreaElementRD('q8_258other', $this->indent . 'If you selected [Some other type of animal], please specify:');
		$this->XINRegisterRule('q8_258other', array("q8_258{@}=={@}04"), "You must specify other", "q8_258other_group");
		$this->form->addElement('static', null, "<br/>");


		//q8_259
		$this->form->addElement('static', null, "8-259 How did you usually them? Did you...Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$animalPesticides = array("a"=>"a) Spray the animals", "b"=>"b) Dust or pour it on animals", "c"=>"c) Inject the animals", "d"=>"d) Use ear tags", "e"=>"e) Dip the animals", "f"=>"f) Use power duster", "g"=>"g) Use pest strips", "h"=>"h) Use fog/mist animals", "i"=>"i) Use rope wick", "j"=>"j) Use something else");
		
		foreach ($animalPesticides as $field=>$label)
		{
			$this->form->addElement("select", "q8_259_{$field}", "{$label}", array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_259_{$field}", array("q8_241_f{@}=={@}01_yes"), "Required if applied pesticides on animals");	
		}

		$this->addTextAreaElementRD('q8_259other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule('q8_259other', array("q8_259_j{@}=={@}01_yes"), "You must specify something else", "q8_259other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box PU-14");
		$this->form->addElement('static', null, "If you selected [Yes] to [part a in 8-241], go to 8-260");
		$this->form->addElement('static', null, "Otherwise, go to Box 8-261");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		
		//q8_260
		$this->form->addElement('static', null, "8-260 You said that you applied pesticides in or around buildings. Did you usually use a...Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$buildingPesticides = array("a"=>"a) Mist blower", "b"=>"b) Hand-held spray gun or wand with a spray", "c"=>"c) Backpack sprayer ", "d"=>"d) Rig that sat on the floor ", "e"=>"e) Dust by hand",  "f"=>"f) Sub-surface application methods, such as for termite control",  "g"=>"g) Something else");

		foreach ($buildingPesticides as $field=>$label)
		{
			$this->form->addElement("select", "q8_260_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_260_{$field}", array("q8_241_a{@}=={@}01_yes"), "Required if applied pesticides in or around buildings");	
		}

		$this->addTextAreaElementRD('q8_260other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule('q8_260other', array("q8_260_g{@}=={@}01_yes"), "You must specify something else", "q8_260other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");



		//q8_261
		$this->addTextAreaElementRD('q8_261', "8-261 On average, how many total days a year did you apply pesticides?");
		$this->XINRegisterRule("q8_261", array("q8_239{@}=={@}01_yes"), "Required if applied pesticides", "q8_261_group");	
		$this->form->addElement('static', null, $this->indent . "If you selected [Yes] to [8-24 part d], go to Painting, Paint Removal, Paint Cleaning Module, and Organic Solvent Module");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: FUEL AND EXHAUST SMELLS");
		$this->form->addElement('static', null, "<br/>");


		//q8_262
		$this->form->addElement("select", "q8_262", "8-262 Did you regularly smell fuel vapors, such as from gas or fuel tanks, or exhaust vapors, such as from car or truck tail pipes?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_262", array("q8_211{@}=={@}01_yes"), "Required if conducted building maintenance activities");
		$this->form->addElement('static', null, $this->indent . "If you selected [No], end Module and go to 8-263a");
		$this->form->addElement('static', null, "<br/>");


		//q8_263
		$this->form->addElement("select", "q8_263", "8-263 How strong was the smell?",  array(NULL=>"", "01" => "01 Slight", "02" => "02 Moderate", "03" => "03  Strong", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_263", array("q8_262{@}=={@}01_yes"), "Required if smelled fuel or exhaust vapors");	
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: HOUSEHOLD CLEANER USE");
		$this->form->addElement('static', null, "<br/>");


		//q8_263a
		$this->form->addElement("select", "q8_263a", "8-263a Did you typically use household cleaning products",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused], or [Don't Know], end Module and go to Clean Hands Module 8-264");
		$this->form->addElement('static', null, "<br/>");


		//q8_263b
		$this->form->addElement('static', null, "8-263b Which types of cleaning products did you typically use at work? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$householdCleaning = array("a"=>"a) Ammonia products", "b"=>"b) Chlorine bleach", "c"=>"c) Floor cleaner", "d"=>"d) Floor polish", "e"=>"e) Floor stripper",  "f"=>"f) Furniture or wood polish",  "g"=>"g) Metal polish",  "h"=>"h) Oven cleaner",  "i"=>"i) Paint stripper",  "j"=>"j) Spot and stain remover or carpet cleaner",  "k"=>"k) Turpertine or mineral spirits",  "l"=>"l) Window or mirror cleaner",  "m"=>"m) Other");
		
		foreach ($householdCleaning as $field=>$label)
		{
			$this->form->addElement("select", "q8_263b_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_263b_{$field}", array("q8_263a{@}=={@}01_yes"), "Required if used household cleaning products");	
		}

		$this->addTextAreaElementRD('q8_263bother', $this->indent . 'If you selected [Other], please specify:');
		$this->XINRegisterRule("q8_263bother", array("q8_263b_m{@}=={@}01_yes"), "You must specify other", "q8_263bother_group");	
		$this->form->addElement('static', null, "<br/>");


		//q8_263c
		$this->form->addElement('static', null, "8-263c How often did you use the following cleaning products?");
		$this->form->addElement('static', null, "<i>Probe: How many hours per day, per week or per month did you use the following art supplies?</i>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Enter number and choose units or select from the list:");

		$this->form->addElement('static', null, "<br/>");


		foreach ($householdCleaning as $field=>$label)
		{
			$this->form->addElement('select', "q8_263c_{$field}", "{$label}:",  array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->XINRegisterRule("q8_263c_{$field}", array("q8_263b_{$field}{@}=={@}01_yes"), "Required if used household cleaning products");	
			$this->addTextAreaElementRD("q8_263c_number{$field}", $this->indent . 'Number:');
			$this->XINRegisterRule("q8_263c_number{$field}", array("q8_263c_{$field}{@}=={@}01|02|03|04"), "You must specify a number", "q8_263c_number{$field}_group");
		}

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: CLEAN HANDS");
		$this->form->addElement('static', null, "<br/>");


		//q8_264
		$this->form->addElement("select", "q8_264", "8-264 Did you regularly get chemicals or dust on your hands or skin?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_264", array("q8_264{@}=={@}NEVER_REQUIRED"));
		$this->form->addElement('static', null, $this->indent . "If you selected [No], end Module and go to 8-267");
		$this->form->addElement('static', null, "<br/>");


		//q8_265
		$this->form->addElement('static', null, "8-265 When you had chemicals or dust on your hands, when did you wash your hands? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$chemWashing = array("a"=>"a) When taking a break at work", "b"=>"b) Before eating", "c"=>"c) Before smoking", "d"=>"d) At the end of the work shift", "e"=>"e) When the task is completed",  "f"=>"f) Whenever I get my hands dirty",  "g"=>"g) Don't wash hands");

		foreach ($chemWashing as $field=>$label)
		{
			$this->form->addElement("select", "q8_265_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_265_{$field}", array("q8_264{@}!={@}02"), "Required if got chemicals or dust on hands or skin");	
		}

		$this->form->addElement('static', null, $this->indent . "If you selected [Don't wash hands], end Module and go to to PPE Module 8-267");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_266
		$this->form->addElement('static', null, "8-266 What did you use to wash chemicals or dust off your hands? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$chemCleaners = array("a"=>"a) Soap and water or water only", "b"=>"b) [Goop] or similar cleaners", "c"=>"c) Mineral spirits, turpentine, or paint thinner", "d"=>"d) Gasoline or kerosene", "e"=>"e) Something else");

		foreach($chemCleaners as $field=>$label)
		{
			$this->form->addElement("select", "q8_266_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_266_{$field}", array("q8_265_g{@}!={@}01_yes", "q8_265_g{@}!={@}"), "Required if washed hands");	
		}

		$this->addTextAreaElementRD('q8_266other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule("q8_266other", array("q8_266_e{@}=={@}01_yes"), "You must specify something else", "q8_266other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: PERSONAL PROTECTIVE EQUIPMENT");
		$this->form->addElement('static', null, "<br/>");


		//q8_267
		$this->form->addElement("select", "q8_267", "8-267 Between [-3] and DOBS, how often did you wear or use personal protective equipment (PPE) to protect you from the things you have mentioned? By personal protective equipment, I mean the things like gloves, dust mask, goggles, aprons, lab coats or other protective clothing, would you say always, often, rarely, or never us personal protective equipment?",  array(NULL=>"", "01" => "01 Always", "02" => "02 Often", "03" => "03  Rarely", "04" => "04 Never", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_267", array("q8_267{@}=={@}NEVER_REQUIRED"));
		$this->form->addElement('static', null, $this->indent . "If you selected [Never], [Refused], or [Don't Know], end Module and go to Ventilation Module 8-271");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		

		//q8_268
		$this->form->addElement('static', null, "8-268 What did you use to wash chemicals or dust off your hands? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("f"=>"f) Soap and water or water only", "g"=>"g) [Goop] or similar cleaners", "h"=>"h) Mineral spirits, turpentine, or paint thinner", "i"=>"i) Gasoline or kerosene", "j"=>"j) Something else");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_268_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_268_{$field}", array("q8_267{@}=={@}01|02|03"), "Required if used personal protective equipment");	
		}

		$this->addTextAreaElementRD('q8_268other', $this->indent . 'If you selected [j) Something else], please specify:');
		$this->XINRegisterRule("q8_268other", array("q8_268_j{@}=={@}01_yes"), "You must specify something else", "q8_268other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_269
		$this->form->addElement('static', null, "8-269 Which type of protective clothing or equipment did you wear? Code all that apply.");
		$this->form->addElement('static', null, "<i>PROBE: Any other protective clothing or equipment?</i>");
		$this->form->addElement('static', null, "<br/>");


		foreach($this->protectiveEquipment as $field=>$label)
		{
			$this->form->addElement("select", "q8_269_{$field}", "{$label}:",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_269_{$field}", array("q8_267{@}=={@}01|02|03"), "Required if used personal protective equipment");	
		}

		$this->addTextAreaElementRD('q8_269other', $this->indent . 'If you selected [Other], please specify:');
		$this->XINRegisterRule("q8_269other", array("q8_269_h{@}=={@}01_yes"), "You must specify other", "q8_269other_group");
		$this->form->addElement('static', null, $this->indent . "If you selected [Yes] for [part e], go to 8-270");
		$this->form->addElement('static', null, $this->indent . "Otherwise, end Module and go to Ventilation Module - starts on 8-271");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_270
		$this->form->addElement("select", "q8_270", "8-270 What type of respirator was it?",  array(NULL=>"", "01" => "01 A half-mask chemical cartridge respirator", "02" => "02 A full-mask chemical cartridge respirator", "03" => "03  An air-supplied or SCBA respirator", "04" => "04 Some other kind of respirator?", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_270", array("q8_269_e{@}=={@}01_yes"), "Required if used a respirator");
		$this->addTextAreaElementRD('q8_270other', $this->indent . 'If you selected [Some other kind of respirator], please specify:');
		$this->XINRegisterRule("q8_270other", array("q8_270{@}=={@}04"), "You must specify other", "q8_270other_group");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: VENTILATION & ENCLOSURES");
		$this->form->addElement('static', null, "<br/>");


		//q8_271
		$this->form->addElement("select", "q8_271", "8-271 Was there any kind of a ventilation system to remove exhaust, dust, smoke or fumes from the area?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_271", array("q8_271{@}=={@}NEVER_REQUIRED"));
		$this->form->addElement('static', null, "<i>Probe: By ventilation system we mean purposely opening windows or doors, using a fume hood, or other ventilation system.</i>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused], or [Don't Know], end Module and go to 8-13");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_272
		$this->form->addElement('static', null, "8-272 What ventilation systems were present to remove exhaust, dust, smoke or fumes from the area? Are there...Code all that apply.");
		$this->form->addElement('static', null, "<br/>");


		foreach ($this->ventilators as $field=>$label)
		{
			$this->form->addElement("select", "q8_272_{$field}", "{$label}:",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_272_{$field}", array("q8_271{@}=={@}01_yes"), "Required if there was a ventilation system");
		}

		$this->addTextAreaElementRD('q8_272other', $this->indent . 'Please specify:');
		$this->XINRegisterRule("q8_272other", array("q8_272_f{@}=={@}01_yes"), "You must specify other", "q8_272other_group");
		

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>When occupational module is complete, and there are NO more Occupational Modules to Complete listed in the Occupational Coding Box, go to 8-13");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


	} //end function _page31() =====================================================



	function rulesPage31($fields)
	{
		$errors = array();

		$options = array("a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m");
		$questions = array("q8_211", "q8_263a", "q8_264", "q8_267", "q7_271");


                $db =& Database::singleton();

                $otherCommentID = $db->selectOne("SELECT CommentID from flag where Test_name='EARLI_interview_PART_3' and SessionID=" . $this->getSessionID());

                $db->selectRow("SELECT q8_5, q8_6_4 FROM EARLI_interview_PART_3 WHERE CommentID='". $otherCommentID."'", $occupation);


		if ($occupation["q8_5"] == "04")
		{
			for ($i=0; $i<5; $i++)
			{
				if (empty($fields[$questions[$i]]))
					$errors[$questions[$i]] = "You must specify";
			}
		}

		if ($occupation["q8_5"] == "09" && ($occupation["q8_6_4"] >= 19 && $occupation["q8_6_4"] <= "21"))
		{
                        for ($i=0; $i<5; $i++)
                        {
                                if (empty($fields[$questions[$i]]))
                                        $errors[$questions[$i]] = "You must specify";
                        }
		}

		for ($i=0; $i<5; $i++)
		{
			if ($fields["q8_223_$options[$i]"] == "01_yes")
			{
				for ($j=0; $j<13; $j++)
				{
					if (empty($fields["q8_230_$options[$j]"]))
						$errors["q8_230_$options[$j]"] = "You must specify";
				}
				break;
			}
		}

	
		if ($fields["q8_250_b"] == "01_yes" || $fields["q8_250_c"] == "01_yes")
		{
			for ($i=0; $i<7; $i++)
			{
				if (empty($fields["q8_252_$options[$i]"]))
					$errors["q8_252_$options[$i]"] = "Required if applied pesticides by aircraft, tractor or truck";
			}
		}

		if ($fields["q8_241_b"] == "01_yes" || $fields["q8_241_c"] == "01_yes" || $fields["q8_241_d"] == "01_yes")
		{
			for ($i=0; $i<4; $i++)
			{
				if (empty($fields["q8_255_$options[$i]"]))
					$errors["q8_255_$options[$i]"] = "Required if used pesticides on crops, forests or roads";
			}
		}

		return $errors;
	}


	function _page32(){   // ========================================================


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>OCCUPATION MODULE: Childcare Worker (CW)");
		$this->form->addElement('static', null, "<br/>");

		//function with more complex rules
		$this->form->addFormRule(array(&$this, 'rulesPage32'));
		

		//q8_273
		$this->form->addElement("select", "q8_273", "8-273 Did you use art supplies while performing your child care duties?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_273", array("q8_273{@}=={@}NEVER_REQUIRED"));

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If you selected [Yes], go to Art Supplies Module 8-274");
		$this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused], or [Don't Know], go to Gluing Module 8-276");
		
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: USING ART SUPPLIES");
		$this->form->addElement('static', null, "<br/>");


		//q8_274
		$this->form->addElement('static', null, "8-274 Which art supplies did you typically use? Or use at least once a week? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$artSupplies = array("a"=>"a) Markers", "b"=>"b) Paints", "c"=>"c) Inks", "d"=>"d) Glazes", "e"=>"e) Something else",  "f"=>"f) No art supplies containing chemicals");

		foreach ($artSupplies as $field=>$label)
		{
			$this->form->addElement("select", "q8_274_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_274_{$field}", array("q8_273{@}=={@}01_yes"), "Required if used art supplies");
		}

		$this->addTextAreaElementRD('q8_274other', $this->indent . 'If you selected [Yes] to [e) Something else], please specify:');
		$this->XINRegisterRule("q8_274other", array("q8_274_e{@}=={@}01_yes"), "You must specify something else", "q8_274other_group");	
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_275
		$this->form->addElement('static', null, "8-275 How often did you use the following art supplies?");
		$this->form->addElement('static', null, "<i>Probe: How many hours per day, per week or per month did you use the following art supplies?</i>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Enter number and choose units or select from the list");
		$this->form->addElement('static', null, "<br/>");

		
		foreach ($artSupplies as $field=>$label)
		{
			$this->form->addElement('select', "q8_275_{$field}", "{$label}:", array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->XINRegisterRule("q8_275_{$field}", array("q8_274_{$field}{@}=={@}01_yes"), "Required if used:");
			$this->addTextAreaElementRD("q8_275_number{$field}", $this->indent . 'Number:');
			$this->XINRegisterRule("q8_275_number{$field}", array("q8_275_{$field}{@}=={@}1|02|03|04"), "You must specify a number", "q8_275_number{$field}_group");
		}

	//	$this->addTextAreaElementRD('q8_275other', $this->indent . 'If you selected [Yes] to [e) Something else], please specify:');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: GLUING");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_276
		$this->form->addElement("select", "q8_276", "8-276 Did you routinely use glues or adhesives?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_276", array("q8_276{@}=={@}NEVER_REQUIRED"));
		$this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know], end Module and go to 8-282");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		

		//q8_277
		$this->form->addElement('static', null, "8-277 Which glues did you use? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		foreach ($this->adhesives as $field=>$label)
		{
			$this->form->addElement("select", "q8_277_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_277_{$field}", array("q8_276{@}=={@}01_yes"), "Required if used glues or adhesives");
		}

		$this->addTextAreaElementRD('q8_277other', $this->indent . 'If you selected [e) Something else], please specify:');
		$this->XINRegisterRule("q8_277other", array("q8_277_e{@}=={@}01_yes"), "You must specify something else", "q8_277other_group");
		$this->form->addElement('static', null, $this->indent . "If you selected [No], [Don't Know] and/or [Refused] to <u>all</u> then go to question 8-279");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_278
		$this->form->addElement('static', null, "8-278 How strong was the smell of {hot melt glues/contact adhesives/water-based adhesives/wood laminates}?");
		$this->form->addElement('static', null, "Code for each yes response in 8-277");
		$this->form->addElement('static', null, "<br/>");

		foreach ($this->adhesives as $field=>$label)
		{
			$this->form->addElement("select", "q8_278_{$field}", "{$label}", array(NULL=>"", "01" => "01 Slight", "02" => "02 Moderate", "03" => "03  Strong", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->XINRegisterRule("q8_278_{$field}", array("q8_277_{$field}{@}=={@}01_yes"), "Required if used this glue or adhesive");
		}

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_279
		$this->form->addElement("select", "q8_279", "8-279 Did you wipe off the excess glue or adhesive with a solvent?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_279", array("q8_276{@}=={@}01_yes"), "Required if routinely used glues or adhesives");
		$this->form->addElement('static', null, $this->indent . "If [No], [Refused], or [Don't Know], go to 8-281");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_280
		$this->form->addElement('static', null, "8-280 What solvent did you typically wipe it off with? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$solvents = array("a"=>"a) Acetone", "b"=>"b) Paint thinner", "c"=>"c) Citrus-based chemicals", "d"=>"d) Something else");
		foreach ($solvents as $field=>$label)
		{
			$this->form->addElement("select", "q8_280_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_280_{$field}", array("q8_279{@}=={@}01_yes"), "Required if used a solvent");
		}

		$this->addTextAreaElementRD('q8_280other', $this->indent . 'If you selected [d) Something else], please specify:');
		$this->XINRegisterRule("q8_280other", array("q8_280_d{@}=={@}01_yes"), "You must specify something else", "q8_280other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_281
		$this->form->addElement('static', null, "8-281 How often did you use the following glues or adhesives?");
		$this->form->addElement('static', null, "<i>Probe: How many hours per day, per week or per month do you use the following glues or adhesives?</i>");
		$this->form->addElement('static', null, "<br/>");

		foreach($this->adhesives as $field=>$label)
		{
			$this->form->addElement('select', "q8_281_{$field}", "{$label}:", array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->XINRegisterRule("q8_281_{$field}", array("q8_277_{$field}{@}=={@}01_yes"), "Required if used: ");
			$this->addTextAreaElementRD("q8_281_number{$field}", $this->indent . 'Number:');
			$this->XINRegisterRule("q8_281_number{$field}", array("q8_281_{$field}{@}=={@}01|02|03|04"), "You must specify a number", "q8_281_number{$field}_group");
		}

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: CLEAN HANDS");
		$this->form->addElement('static', null, "<br/>");


		//q8_282
		$this->form->addElement("select", "q8_282", "8-282 Did you regularly get chemicals or dust on your hands or skin?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_282", array("q8_282{@}=={@}NEVER_REQUIRED"));
		$this->form->addElement('static', null, $this->indent . "If you selected [No], end Module and go to 8-285");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_283
		$this->form->addElement('static', null, "8-283 When you had chemicals or dust on your hands, when did you wash your hands? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$list = array("a"=>"a) When taking a break at work", "b"=>"b) Before eating", "c"=>"c) Before smoking", "d"=>"d) At the end of the work shift", "e"=>"e) When the task is completed",  "f"=>"f) Whenever I get my hands dirty",  "g"=>"g) Don't wash hands");

		foreach ($list as $field=>$label)
		{
			$this->form->addElement("select", "q8_283_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_283_{$field}", array("q8_282{@}=={@}01_yes"), "Required if got chemicals or dust on hands and skin");
		}

		$this->form->addElement('static', null, $this->indent . "If you selected [Don't wash hands], end Module and go to to 8-285");
		reset($list);
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");



		//q8_284
		$this->form->addElement('static', null, "8-284 What did you use to wash chemicals or dust off your hands? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Soap and water or water only", "b"=>"b) [Goop] or similar cleaners", "c"=>"c) Mineral spirits, turpentine, or paint thinner", "d"=>"d) Gasoline or kerosene", "e"=>"e) Something else");

		foreach ($list as $field=>$label)
		{
			$this->form->addElement("select", "q8_284_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_284_{$field}", array("q8_283_g{@}!={@}01_yes", "q8_283_g{@}!={@}"), "Required if washed hands");
		}

		$this->addTextAreaElementRD('q8_284other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule("q8_284other", array("q8_284_e{@}=={@}01_yes"), "You must specify something else", "q8_284other_group");
		reset($list);
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: PERSONAL PROTECTIVE EQUIPMENT");
		$this->form->addElement('static', null, "<br/>");


		//q8_285
		$this->form->addElement("select", "q8_285", "8-285 Between [-3] and DOBS, how often did you wear or use personal protective equipment (PPE) to protect you from the things you have mentioned? By personal protective equipment, I mean the things like gloves, dust mask, goggles, aprons, lab coats or other protective clothing, would you say always, often, rarely, or never us personal protective equipment?",  array(NULL=>"", "01" => "01 Always", "02" => "02 Often", "03" => "03  Rarely", "04" => "04 Never", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_285", array("q8_285{@}=={@}NEVER_REQUIRED"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_286
		$this->form->addElement('static', null, "8-286 What did you use to wash chemicals or dust off your hands? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Soap and water or water only", "b"=>"b) [Goop] or similar cleaners", "c"=>"c) Mineral spirits, turpentine, or paint thinner", "d"=>"d) Gasoline or kerosene", "e"=>"e) Something else");

		foreach ($list as $field=>$label)
		{
			$this->form->addElement("select", "q8_286_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_286_{$field}", array("q8_286_{$field}{@}=={@}NEVER_REQUIREd"));
		}
		
		$this->addTextAreaElementRD('q8_286other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule("q8_286other", array("q8_286_e{@}=={@}01_yes"), "You must specify something else", "q8_286other_group");
		reset($list);
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_287
		$this->form->addElement('static', null, "8-287 Which type of protective clothing or equipment did you wear? Code all that apply.");
		$this->form->addElement('static', null, "<i>PROBE: Any other protective clothing or equipment?</i>");
		$this->form->addElement('static', null, "<br/>");

		foreach ($this->protectiveEquipment as $field=>$label)
		{
			$this->form->addElement("select", "q8_287_{$field}", "{$label}:",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_287_{$field}", array("q8_285{@}=={@}01|02|03"), "Required if used personal protective equipment");
		}

		$this->addTextAreaElementRD('q8_287other', $this->indent . 'If you selected [Other], please specify:');
		$this->XINRegisterRule("q8_287other", array("q8_287_h{@}=={@}01_yes"), "You must specify other", "q8_287other_group");
		$this->form->addElement('static', null, $this->indent . "If you selected [Yes] for [part e], go to 8-288");
		$this->form->addElement('static', null, $this->indent . "Otherwise, end Module and go to Photocopying/Laser Jet Module - starts on 8-289");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_288
		$this->form->addElement("select", "q8_288", "8-288 What type of respirator was it?",  array(NULL=>"", "01" => "01 A half-mask chemical cartridge respirator", "02" => "02 A full-mask chemical cartridge respirator", "03" => "03  An air-supplied or SCBA respirator", "04" => "04 Some other kind of respirator?", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_288", array("q8_287_e{@}=={@}01_yes"), "You must specify type of respirator");
		$this->addTextAreaElementRD('q8_288other', $this->indent . 'If you selected [Some other kind of respirator], please specify:');
		$this->XINRegisterRule("q8_288other", array("q8_288{@}=={@}04"), "You must specify other", "q8_288other_group");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: PHOTOCOPYING/LASER JET PROXIMITY");
		$this->form->addElement('static', null, "<br/>");


		//q8_289
		$this->form->addElement("select", "q8_289", "8-289 Did this job require that you regularly stand at a photocopier for more than 1 hour per day?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_289", array("q8_289{@}=={@}NEVER_REQUIRED"));
		$this->form->addElement('static', null, "<br/>");


		//q8_290
		$this->form->addElement("select", "q8_290", "8-290 Did this job require that you sit within 10 feet of an operating laser jet printer for more than 1 hour per day?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_290", array("q8_290{@}=={@}NEVER_REQUIRED"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>When occupational module complete, and there are NO more Occupational Modules to Complete listed in the Occupational Coding Box then [go to 8-13]");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>OCCUPATION MODULE: Beautician/Barber (BB)");
		
		
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-291 Between [-3] and DOBS, did you do any of the following? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Color or dye hair", "b"=>"b) Bleach hair", "c"=>"c) Tint hair", "d"=>"d) Perm hair", "e"=>"e) Straighten hair using chemicals",  "f"=>"f) Use hair spray",  "g"=>"g) None of these");

		foreach ($list as $field=>$label)
		{
			$this->form->addElement("select", "q8_291_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_291_{$field}", array("q8_291_{$field}{@}=={@}NEVER_REQUIRED"));
		}

		$this->form->addElement('static', null, $this->indent . "If you selected [None of these], [No], [Refused], or [Don't Know], go to 8-296");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		reset($list);	
	
		//q8_292
		$this->form->addElement('static', null, "8-292 How often did you do the following activities?");
		$this->form->addElement('static', null, "<i>Probe: How many hours per day, per week or per month do you use the following glues or adhesives?</i>");
		$this->form->addElement('static', null, "<br/>");


		$list = array("a"=>"a) Color or dye hair", "b"=>"b) Bleach hair", "c"=>"c) Tint hair", "d"=>"d) Perm hair", "e"=>"e) Straighten hair using chemicals",  "f"=>"f) Use hair spray");

		foreach ($list as $field=>$label)
		{
			$this->form->addElement('select', "q8_292_{$field}", "{$label}:", array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->XINRegisterRule("q8_292_{$field}", array("q8_291_{$field}{@}=={@}01_yes"), "Required if did: ");
			$this->addTextAreaElementRD("q8_292_number{$field}", $this->indent . 'Number:');
			$this->XINRegisterRule("q8_292_number{$field}", array("q8_292_{$field}{@}=={@}01|02|03|04"), "You must specify a number", "q8_292_number{$field}_group");
		}
		
		reset($list);
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
                $this->form->addElement('static', null, "<b/>Box BB-1");
                $this->form->addElement('static', null, "If you selected [Yes] to [part a in 8-291], go to 8-293 and 8-294");
                $this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_293
		$this->form->addElement('static', null, "8-293 Between [-3] and DOBS, what type of hair dye did you use? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$dye = array("a"=>"a) <b>Temporary</b>, such as Cationic dyes (IF NEEDED: METHYL VIOLET), Anionic dyes, or Azo dyes (IF NEEDED: SUCH AS WATER BASED RINSES)", "b"=>"b) <b>Semi-permanent</b> mixtures of nitro dyes and anthraquinones. These dyes produce red yellow and  blue colorings", "c"=>"c) <b>Permanent oxidation dyes</b> (IF NEEDED: OXIDATION DYES OR 'PARA' DYES). They contain an oxidizing agent like hydrogen peroxide", "d"=>"d) <b>Quasi-permanent</b> dyes are a mixture of semipermanent and permanent oxidation dyes");

		foreach ($dye as $field => $label) {
			$this->form->addElement("select", "q8_293_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_293_{$field}", array("q8_291_a{@}=={@}01_yes"), "Required if colored or dyed hair");
		}

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_294
		$this->form->addElement("select", "q8_294", "8-294 Which basic color did you use most often?",  array(NULL=>"", "01" => "01 Black", "02" => "02 Brown or brunette", "03" => "03  Blonde", "04" => "04 Red", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_294", array("q8_291_a{@}=={@}01_yes"), "Required if colored or dyed hair");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_295
		$this->form->addElement("select", "q8_295", "8-295 Which kind of solution did you usually use to disinfect combs and brushes",  array(NULL=>"", "01" => "01 Barbicide solution", "02" => "02 Bleach solution", "03" => "03  Alcohol solution", "04" => "04 Chlorine solution", "05" => "05 Lysol solution", "06" => "06 Formaldehyde solution", "07" => "07 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_295", array("q8_295{@}=={@}NEVER_REQUIRED"));
		$this->addTextAreaElementRD('q8_295other', $this->indent . 'If you selected [Other], please specify:');
		$this->XINRegisterRule("q8_295other", array("q8_295{@}=={@}07"), "You must specify other", "q8_295other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_296
		$this->form->addElement('static', null, "8-296 Did you typically do either of the following? Code all that apply:");
		$list = array("a"=>"a) Manicure clients' nails", "b"=>"b) Apply acrylic nails");

		foreach ($list as $field=>$label)
		{
			$this->form->addElement("select", "q8_296_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_296_{$field}", array("q8_296_{$field}{@}=={@}NEVER_REQUIRED"));
		}

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box BB-2");
		$this->form->addElement('static', null, "If you selected [Yes] to [part a or b in 8-296], go to 8-296a");
		$this->form->addElement('static', null, "Otherwise, go to Clean hands Module 8-297");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_296a
		$this->form->addElement("select", "q8_296a", "8-296a Did you use a manicurist's ventilation table? <i>If needed: Has fan to exhaust vapors</i>",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_296a", array("q8_296a{@}=={@}NEVER_REQUIRED"));  
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: CLEAN HANDS");
		$this->form->addElement('static', null, "<br/>");


		//q8_297
		$this->form->addElement("select", "q8_297", "8-297 Did you regularly get chemicals or dust on your hands or skin?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_297", array("q8_297{@}=={@}NEVER_REQUIRED"));  
		$this->form->addElement('static', null, $this->indent . "If you selected [No], end Module and go to 8-300");
		$this->form->addElement('static', null, "<br/>");


		//q8_298
		$this->form->addElement('static', null, "8-298 When you had chemicals or dust on your hands, when did you wash your hands? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$list = array("a"=>"a) When taking a break at work", "b"=>"b) Before eating", "c"=>"c) Before smoking", "d"=>"d) At the end of the work shift", "e"=>"e) When the task is completed",  "f"=>"f) Whenever I get my hands dirty",  "g"=>"g) Don't wash hands");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_298_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_298_{$field}", array("q8_297{@}!={@}02"), "Required if got chemicals or dust on hands or skin");
		}

		$this->form->addElement('static', null, $this->indent . "If you selected [Don't wash hands], end Module and go to to PPE Module 8-300");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_299
		$this->form->addElement('static', null, "8-299 What did you use to wash chemicals or dust off your hands? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Soap and water or water only", "b"=>"b) [Goop] or similar cleaners", "c"=>"c) Mineral spirits, turpentine, or paint thinner", "d"=>"d) Gasoline or kerosene", "e"=>"e) Something else");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_299_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_299_{$field}", array("q8_298_g{@}!={@}01_yes", "q8_298_g{@}!={@}"), "Required if washed hands");
		}

		$this->addTextAreaElementRD('q8_299other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule("q8_299other", array("q8_299_e{@}=={@}01_yes"), "You must specify something else", "q8_299other_group");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: VENTILATION & ENCLOSURES");
		$this->form->addElement('static', null, "<br/>");


		//q8_300
		$this->form->addElement("select", "q8_300", "8-300 Was there any kind of a ventilation system to remove exhaust, dust, smoke or fumes from the area?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<i>Probe: By ventilation system we mean purposely opening windows or doors, using a fume hood, or other ventilation system.</i>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused], or [Don't Know], end Module and go to 8-302");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_301
		$this->form->addElement('static', null, "8-301 What ventilation systems were present to remove exhaust, dust, smoke or fumes from the area? Are there...Code all that apply.");
		$this->form->addElement('static', null, "<br/>");

		foreach ($this->ventilators as $field=>$label)
		{
			$this->form->addElement("select", "q8_301_{$field}", "{$label}:",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_301_{$field}", array("q8_300{@}=={@}01_yes"), "Required if there was a ventilation system");
		}

		$this->addTextAreaElementRD('q8_301other', $this->indent . 'If you selected [Some other type of ventilation system], please specify:');
		$this->XINRegisterRule("q8_301other", array("q8_301_f{@}=={@}01_yes"), "You must specify other", "q8_301other_group");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: PHOTOCOPYING/LASER JET PROXIMITY");
		$this->form->addElement('static', null, "<br/>");


		//q8_302
		$this->form->addElement("select", "q8_302", "8-302 Did this job require that you regularly stand at a photocopier for more than 1 hour per day?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_302", array("q8_302{@}=={@}NEVER_REQUIRED"));  
		$this->form->addElement('static', null, "<br/>");


		//q8_303
		$this->form->addElement("select", "q8_303", "8-303 Did this job require that you sit within 10 feet of an operating laser jet printer for more than 1 hour per day?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_303", array("q8_303{@}=={@}NEVER_REQUIRED"));  
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: PERSONAL PROTECTIVE EQUIPMENT");
		$this->form->addElement('static', null, "<br/>");


		//q8_304
		$this->form->addElement("select", "q8_304", "8-304 Between [-3] and DOBS, how often did you wear or use personal protective equipment (PPE) to protect you from the things you have mentioned? By personal protective equipment, I mean the things like gloves, dust mask, goggles, aprons, lab coats or other protective clothing, would you say always, often, rarely, or never us personal protective equipment?",  array(NULL=>"", "01" => "01 Always", "02" => "02 Often", "03" => "03  Rarely", "04" => "04 Never", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_304", array("q8_304{@}=={@}NEVER_REQUIRED"));  
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_305
		$this->form->addElement('static', null, "8-305 What did you use to wash chemicals or dust off your hands? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Soap and water or water only", "b"=>"b) [Goop] or similar cleaners", "c"=>"c) Mineral spirits, turpentine, or paint thinner", "d"=>"d) Gasoline or kerosene", "e"=>"e) Something else");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_305_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_305_{$field}", array("q8_305_{$field}{@}=={@}NEVER_REQUIRED")); 
		}

		$this->addTextAreaElementRD('q8_305other', $this->indent . 'If you selected [j) Something else], please specify:');
		$this->XINRegisterRule("q8_305other", array("q8_305_e{@}=={@}01_yes"), "You must specify something else", "q8_305other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_306
		$this->form->addElement('static', null, "8-306 Which type of protective clothing or equipment did you wear? Code all that apply.");
		$this->form->addElement('static', null, "<i>PROBE: Any other protective clothing or equipment?</i>");
		$this->form->addElement('static', null, "<br/>");

		foreach($this->protectiveEquipment as $field=>$label)
		{
			$this->form->addElement("select", "q8_306_{$field}", "{$label}:",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_306_{$field}", array("q8_304{@}=={@}01|02|03"), "Required if wore personal protective equipment");
		}

		$this->addTextAreaElementRD('q8_306other', $this->indent . 'If you selected [Other], please specify:');
		$this->XINRegisterRule("q8_306other", array("q8_306_h{@}=={@}01_yes"), "You must specify other", "q8_306other_group");
		$this->form->addElement('static', null, $this->indent . "If you selected [Yes] for [part e], go to 8-307");
		$this->form->addElement('static', null, $this->indent . "Otherwise, end Module and go to Ventilation Module - starts on 8-13");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

		
		//q8_307
		$this->form->addElement("select", "q8_307", "8-307 What type of respirator was it?",  array(NULL=>"", "01" => "01 A half-mask chemical cartridge respirator", "02" => "02 A full-mask chemical cartridge respirator", "03" => "03  An air-supplied or SCBA respirator", "04" => "04 Some other kind of respirator?", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_307", array("q8_306_e{@}=={@}01_yes"), "You must specify type of respirator");
		$this->addTextAreaElementRD('q8_307other', $this->indent . 'If you selected [Some other kind of respirator], please specify:');
		$this->XINRegisterRule("q8_307other", array("q8_307{@}=={@}04"), "You must specify other", "q8_307other_group");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>When module is complete, and there are NO more Occupational Modules to Complete listed in the Occupational Coding Box, go to 8-13");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


	} //end function _page32() =====================================================


	function rulesPage32 ($fields)
	{

		$errors = array();

		$options = array("a", "b", "c", "d", "e", "f", "g");

		$questions = array("q8_273", "q8_276", "q8_282", "q8_285", "q8_286_a", "q8_286_b", "q8_286_c", "q8_286_d", "q8_286_e", "q8_289", "q8_290");


                $db =& Database::singleton();

                $otherCommentID = $db->selectOne("SELECT CommentID from flag where Test_name='EARLI_interview_PART_3' and SessionID=" . $this->getSessionID());

                $db->selectRow("SELECT q8_5, q8_6_1, q8_6_2, q8_6_3, q8_6_4, q8_6_5, q8_6_6, q8_6_7, q8_6_8, q8_6_9 FROM EARLI_interview_PART_3 WHERE CommentID='". $otherCommentID."'", $occupation);


		//for childcare worker

		if ($occupation["q8_5"] == "02" && ($occupation["q8_6_5"] >= "22" && $occupation["q8_6_5"] <= "25"))
		{
			for ($i=0; $i<11; $i++)
			{		
				if (empty($fields[$questions[$i]]))
					$errors[$questions[$i]] = "You must specify";
			}
		}


		if ($occupation["q8_5"] == "05" && ($occupation["q8_6_1"] >= "01" || $occupation["q8_6_2"] >= "10" || $occupation["q8_6_3"] >= "14" || $occupation["q8_6_4"] >= "19" || $occupation["q8_6_6"] >= "26" || $occupation["q8_6_7"] >= "30" || $occupation["q8_6_8"] >= "40" || $occupation["q8_6_9"] >= "42"))
		{
                        for ($i=0; $i<11; $i++)
                        {
                                if (empty($fields[$questions[$i]]))
                                        $errors[$questions[$i]] = "You must specify";
                        }
		}


		if ($occupation["q8_5"] == "09" && ($occupation["q8_6_5"] <="25" && $occupation["q8_6_5"] >= "22"))
		{
                        for ($i=0; $i<11; $i++)
                        {
                                if (empty($fields[$questions[$i]]))
                                        $errors[$questions[$i]] = "You must specify";
                        }
		}


		$questions2 = array("q8_296_a", "q8_296_b", "q8_297", "q8_300", "q8_302", "q8_303", "q8_304");


		//for beautician/barber

		if ($occupation["q8_5"] == "01" && ($occupation["q8_6_6"] >= "26" && $occupation["q8_6_6"] <= "29"))
		{
			for ($i=0; $i<7; $i++)
			{
				if (empty($fields["q8_291_$options[$i]"]))
					$errors["q8_291_$options[$i]"] = "You must specify";
			}

			for ($i=0; $i<7; $i++)
			{
				if (empty($fields[$questions2[$i]]))
					$errors[$questions2[$i]] = "You must specify";
			}

			for ($i=0; $i<5; $i++)
			{
                                if (empty($fields["q8_305_$options[$i]"]))
                                        $errors["q8_305_$options[$i]"] = "You must specify";
                        }
		}


		if ($occupation["q8_5"] == "09" && ($occupation["q8_6_6"] >= "26" && $occupation["q8_6_6"] <= "29"))
		{
                        for ($i=0; $i<7; $i++)
                        {
                                if (empty($fields["q8_291_$options[$i]"]))
                                        $errors["q8_291_$options[$i]"] = "You must specify";
                        }

                        for ($i=0; $i<7; $i++)
                        {
                                if (empty($fields[$questions2[$i]]))
                                        $errors[$questions2[$i]] = "You must specify";
                        }

                        for ($i=0; $i<5; $i++)
                        {
                                if (empty($fields["q8_305_$options[$i]"]))
                                        $errors["q8_305_$options[$i]"] = "You must specify";
                        }
		}


		if ($occupation["q8_5"] == "06")
                {
                        for ($i=0; $i<7; $i++)
                        {
                                if (empty($fields["q8_291_$options[$i]"]))
                                        $errors["q8_291_$options[$i]"] = "You must specify";
                        }
                
                        for ($i=0; $i<7; $i++)
                        {
                                if (empty($fields[$questions2[$i]]))
                                        $errors[$questions2[$i]] = "You must specify";
                        }

                        for ($i=0; $i<5; $i++)
                        {
                                if (empty($fields["q8_305_$options[$i]"]))
                                        $errors["q8_305_$options[$i]"] = "You must specify";
                        }
                }


		for ($i=0; $i<6; $i++)
		{
			if ($fields["q8_291_$options[$i]"] == "01_yes")
			{	
				if (empty($fields["q8_295"]))
					$errors["q8_295"] = "You must specify";
				break;
			}
		}

		if (($fields["q8_296_a"] == "01_yes" || $fields["q8_296_b"] == "01_yes") && (empty($fields["q8_296a"])))
			$errors["q8_296a"] = "You must specify";

		return $errors;
	}


	function _page33(){   // ========================================================


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>OCCUPATION MODULE: Driver (DR)");
		$this->form->addElement('static', null, "<br/>");


		//function with more complex rules
		$this->form->addFormRule(array(&$this, 'rulesPage33'));
		

		//q8_308
		$this->form->addElement("select", "q8_308", "8-308 What kind of vehicle did you primarily drive at work?",  array(NULL=>"", "01" => "01 Bus", "02" => "02 Truck", "03" => "03  Taxi or cab", "04" => "04 Limousine", "05" => "05 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_308", array("q8_308{@}=={@}NEVER_REQUIRED"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box DR - 1");
		$this->form->addElement('static', null, "If response in [8-308] = [01], go to 8-309");
		$this->form->addElement('static', null, "Otherwise, go to Box DR-2");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_309
		$this->form->addElement("select", "q8_309", "8-309 What kind of bus did you usually drive?", array(NULL=>"", "01" => "01 School bus", "02" => "02 Municipal or city bus", "03" => "03 Long distance bus such as Greyhound or Trailways", "04" => "04 Something else", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_309", array("q8_308{@}=={@}01"), "Required if drove a bus");
                $this->form->addElement('static', null, "<br/>");
                $this->form->addElement('static', null, "<br/>");

                $this->form->addElement('static', null, "<b/>Box DR - 2");
                $this->form->addElement('static', null, "If response in [8-308] = [02], go to 8-310");
                $this->form->addElement('static', null, "Otherwise, go to 8-311");
                $this->form->addElement('static', null, "<br/>");
                $this->form->addElement('static', null, "<br/>");


		//q8_310
		$this->form->addElement("select", "q8_310", "8-310 What size truck did you typically drive?",  array(NULL=>"", "01" => "01 Light trucks, such as pickup trucks, vans, or SUVs", "02" => "02 Medium trucks, such as delivery trucks", "03" => "03  Heavy trucks, such as tractor-trailors", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_310", array("q8_308{@}=={@}02"), "Required if drove a truck");
		$this->form->addElement('static', null, "<br/>");


		//q8_311
		$this->form->addElement("select", "q8_311", "8-311 What fuel powers the type of vehicle did you typically drive?",  array(NULL=>"", "01" => "01 Gasoline", "02" => "02 Diesel", "03" => "03  Propane or natural gas", "04" => "04 Electric", "05" => "05 Biodiesel", "06" => "06 Hybrid gas/ electric", "07" => "07 E-85", "08" => "08 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_311", array("q8_311{@}=={@}NEVER_REQUIRED"));
		$this->form->addElement('static', null, "<br/>");



		//q8_312
		$this->form->addElement("select", "q8_312", "8-312 What best describes where you typically drove?",  array(NULL=>"", "01" => "01 Mostly city driving", "02" => "02 Mostly rural driving", "03" => "03  Highway driving", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_312", array("q8_312{@}=={@}NEVER_REQUIRED"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_313
		$this->form->addElement('select', 'q8_313', "8-313 In a typical work week, how many hours did you usually spend behind the wheel driving in this job? Don't include time spent commuting to and from work.", array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<i>Probe: How many hours per day, per week or per month did you use the following art supplies?</i>");
		//$aToF = array("a"=>"a) Ammonia products", "b"=>"b) Chlorine bleach", "c"=>"c) Floor cleaner", "d"=>"d) Floor polish", "e"=>"e) Floor stripper",  "f"=>"f) Furniture or wood polish",  "g"=>"g) Metal polish",  "h"=>"h) Oven cleaner",  "i"=>"i) Paint stripper",  "j"=>"j) Spot and stain remover or carpet cleaner",  "k"=>"k) Turpertine or mineral spirits",  "l"=>"l) Window or mirror cleaner",  "m"=>"m) Other");
		$this->XINRegisterRule("q8_313", array("q8_313{@}=={@}NEVER_REQUIRED"));
		$this->addTextAreaElementRD("q8_313_number", $this->indent . 'Number:');
		$this->XINRegisterRule("q8_313_number", array("q8_313{@}=={@}01|02|03|04"), "You must specify a number", "q8_313_number_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");



		//q8_314
		$this->form->addElement('static', null, "8-314 While driving to work while you were pregnant with [SIBLING], what were the typical conditions while driving in the vehicles? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Windows were open", "b"=>"b) Ventilation recirculation was off (fresh air was blowing in)", "c"=>"c) Was anyone smoking in the vehicle");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_314_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_314_{$field}", array("q8_314_{$field}{@}=={@}NEVER_REQUIRED")); 
		}

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: LUBRICATING ENGINES & MACHINERY");
		$this->form->addElement('static', null, "<br/>");


		//q8_315
		$this->form->addElement("select", "q8_315", "8-315 Did you routinely use lubricating oils, or waxes on engines or machinery?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_315", array("q8_315{@}=={@}NEVER_REQUIRED")); 
		$this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused], or [Don't Know], end Module and go to 8-319");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_316
		$this->addTextAreaElementRD("q8_316", "8-316 What types of lubricants did you work with?"); 
		$this->XINRegisterRule("q8_316", array("q8_315{@}=={@}01_yes"), "Required if used lubricating oils or waxes", "q8_316_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_317
		$this->form->addElement('static', null, "8-317 What types of cutting oils did you work with? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Straight cutting oils or oils that look and feel like motor oil", "b"=>"b) Soluble cutting oils or oils that are milky white", "c"=>"c) Synthetic cutting oils or oils that feel like water or may be brightly colored, such as green or blue", "d"=>"d) Something else");

		foreach ($list as $field=>$label)
		{
			$this->form->addElement("select", "q8_317_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_317_{$field}", array("q8_315{@}=={@}01_yes"), "Required if used lubricating oils or waxes");
		}

		$this->addTextAreaElementRD('q8_317other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule("q8_317other", array("q8_317_d{@}=={@}01_yes"), "You must specify something else", "q8_317other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");



		//q8_318
		$this->form->addElement('static', null, "8-318 How often did you use the following lubricants?");
		$this->form->addElement('static', null, "<i>Probe: How many hours per day, per week or per month did you use the following lubricants?</i>");
		$this->form->addElement('static', null, "<br/>");
		

		foreach ($list as $field=>$label)
		{
			$this->form->addElement('select', "q8_318_{$field}", "{$label}:", array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->XINRegisterRule("q8_318_{$field}", array("q8_315{@}=={@}01_yes"), "Required if used lubricating oils or waxes");
			$this->addTextAreaElementRD("q8_318_number{$field}", $this->indent . 'Number:');
			$this->XINRegisterRule("q8_318_number{$field}", array("q8_318_{$field}{@}=={@}01|02|03|04"), "You must specify hours", "q8_318_number{$field}_group");
		}

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

                $this->form->addElement('static', null, "<br/>");
                $this->form->addElement('static', null, "<b/>ACTIVITY MODULE: FUEL AND EXHAUST SMELLS");                
		$this->form->addElement('static', null, "<br/>");
                $this->form->addElement('static', null, "<br/>");

                //q8_319
                $this->form->addElement("select", "q8_319", "8-319 Did you regularly smell fuel vapors, such as from gas or fuel tanks, or exhaust vapors, such as from car or truck tail pipes?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_319", array("q8_319{@}=={@}NEVER_REQUIRED"));
                $this->form->addElement('static', null, $this->indent . "If [No], [End Module and go to 8-13]");
                $this->form->addElement('static', null, "<br/>");


                //q8_320
                $this->form->addElement("select", "q8_320", "8-320 How strong was the smell?",  array(NULL=>"", "01" => "01 Slight", "02" => "02 Moderate", "03" => "03  Strong", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_320", array("q8_319{@}=={@}01_yes"), "Required if smelled fuel vapors or exhaust vapors");
                $this->form->addElement('static', null, "<br/>");

                $this->form->addElement('static', null, "<br/>");
                $this->form->addElement('static', null, "<b/>When complete module complete, and there are NO more Occupational Modules to Complete listed in the Occupational Coding Box then [go to 8-13]");
                $this->form->addElement('static', null, "<br/>");
                $this->form->addElement('static', null, "<br/>");


	} //end function _page33() =====================================================



	function rulesPage33($fields)
	{
		$errors = array();

		$questions = array("q8_308", "q8_311", "q8_312", "q8_313", "q8_315", "q8_319");

		$options = array("a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m");


                $db =& Database::singleton();


                $otherCommentID = $db->selectOne("SELECT CommentID from flag where Test_name='EARLI_interview_PART_3' and SessionID=" . $this->getSessionID());
                $db->selectRow("SELECT q8_5, q8_6_7 FROM EARLI_interview_PART_3 WHERE CommentID='".$otherCommentID."'", $occupation);


		if ($occupation["q8_5"] == "07")
		{
			for($i=0; $i<6; $i++)
			{
				if (empty($fields[$questions[$i]]))
					$errors[$questions[$i]] = "You must specify";
			}

			for ($i=0; $i<3; $i++)
			{
                                if (empty($fields["q8_314_$options[$i]"]))
                                        $errors["q8_314_$options[$i]"] = "You must specify";
			}
		}	

		if ($occupation["q8_5"] == "09" && ($occupation["q8_6_7"] >= "30" && $occupation["q8_6_7"] <= "39"))
		{
			for ($i=0; $i<6; $i++)
			{
				if (empty($fields[$questions[$i]]))
					$errors[$questions[$i]] = "You must specify";	
			}

                        for ($i=0; $i<3; $i++)
                        {
                                if (empty($fields["q8_314_$options[$i]"]))
                                        $errors["q8_314_$options[$i]"] = "You must specify";
                        }
		}


		return $errors;
	}



	function _page34(){   // ========================================================


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>OCCUPATION MODULE: Agricultural Worker (AW)");
		$this->form->addElement('static', null, "<br/>");


		//function with more complex rules
		$this->form->addFormRule(array(&$this, 'rulesPage34'));

		//q8_321
		$this->form->addElement('static', null, "8-321 Between [-3] and DOBS, which of the following activities did you perform or been near? Code all that apply:");
		$list = array("a"=>"a) Picked fruits or vegetables by hand", "b"=>"b) Driven or ridden in a tractor or other farm equipment", "c"=>"c) Fumigated barns, stalls or pens", "d"=>"d) Mixed, applied, spread fertilizer", "e"=>"e) Mixed or added supplements such as additives, pesticides, etc.",  "f"=>"f) Cleaned up a pesticide spill or leak",  "g"=>"g) Sterilized equipment",  "h"=>"h) Something else with chemical exposure");
//		reset($list);

		foreach ($list as $field=>$label)
		{
			$this->form->addElement("select", "q8_321_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused", "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_321_{$field}", array("q8_321_{$field}{@}=={@}NEVER_REQUIRED"));
		}

		$this->addTextAreaElementRD('q8_321other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule('q8_321other', array("q8_321_h{@}=={@}01_yes"), "You must specify something else", "q8_321other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>Box AW - 1");
		$this->form->addElement('static', null, "If you selected [No], [Refused] and/or [Do not know] to [part a-h in 8-321], go to Lubricating Module starting on 8-334");
		$this->form->addElement('static', null, "Otherwise, go to 8-322");
		$this->form->addElement('static', null, "<br/>");


		//q8_322
		$this->form->addElement("static", "q8_322", "8-322 How often did you do the following activities? Don't include time spent commuting to and from work.<br /><i>Probe: How many hours per day, per week or per month did you use the following materials?");
		$this->form->addElement('static', null, "<br/>");

		foreach ($list as $field=>$label)
		{
                        $this->form->addElement("select", "q8_322_{$field}", "{$label}",  array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03 Month", "88_refused"=>"88 Refused", "99_Do_not_know"=>"99 Don't know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_322_{$field}", array("q8_321_{$field}{@}=={@}01_yes"), "Required if performed:");
			$this->addTextAreaElementRD("q8_322_number{$field}", "Number:");
			$this->XINRegisterRule("q8_322_number{$field}", array("q8_322_{$field}{@}=={@}01|02|03|04"), "You must specify a number", "q8_322_number{$field}_group");
                }

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box AW - 2");
		$this->form->addElement('static', null, "If you selected [Yes] to [part b in 8-321], go to Fuel and Exhaust Module starting on 8-323");
		$this->form->addElement('static', null, "Otherwise, go to 8-325");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: FUEL AND EXHAUST SMELLS");
		$this->form->addElement('static', null, "<br/>");

		//q8_323
		$this->form->addElement("select", "q8_323", "8-323 Did you regularly smell fuel vapors, such as from gas or fuel tanks, or exhaust vapors, such as from car or truck tail pipes?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_323", array("q8_321_b{@}=={@}01_yes"), "Required if drove a tractor or other farming equipment");
		$this->form->addElement('static', null, "<br/>");


		//q8_324
		$this->form->addElement("select", "q8_324", "8-324 How strong was the smell?",  array(NULL=>"", "01" => "01 Slight", "02" => "02 Moderate", "03" => "03  Strong", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_324", array("q8_323{@}=={@}01_yes"), "Required if smelled fuel vapors");
		$this->form->addElement('static', null, "<br/>");


		//q8_325
		$this->form->addElement('static', null, "8-325 What type of farming or agricultural operation were you involved in? Code all that apply:");
		$list = array("a"=>"a) Cattle or dairy", "b"=>"b) Pigs", "c"=>"c) Poultry", "d"=>"d) Sheep or goats", "e"=>"e) Grains or cereals",  "f"=>"f) Fruit and vineyards",  "g"=>"g) Vegetables",  "h"=>"h) Tobacco",  "i"=>"i) Mushroom",  "j"=>"j) Something else with chemical exposure");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_325_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_325_{$field}", array("q8_325_{$field}{@}=={@}NEVER_REQUIRED"));
		}

		$this->addTextAreaElementRD('q8_325other', $this->indent . 'If you selected [Something else with chemical exposure], please specify:');
		$this->XINRegisterRule("q8_325other", array("q8_325_j{@}=={@}01_yes"), "You must specify something else", "q8_325other_group");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box AW - 3");
		$this->form->addElement('static', null, "If you selected [Yes] to [part b in 8-321], go to 8-326");
		$this->form->addElement('static', null, "Otherwise, go to Box AW - 4");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_326
		$this->form->addElement("select", "q8_326", "8-326 What fuel did your tractor use?",  array(NULL=>"", "01" => "01 Diesel powered equipment", "02" => "02 Gasoline powered equipment", "03"=>"03 Something else", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_326", array("q8_321_b{@}=={@}01_yes"), "Required if drove a tractor or other farm equipment");
		$this->addTextAreaElementRD('q8_326other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule("q8_326other", array("q8_326{@}=={@}03"), "You must specify something else", "q8_326other_group");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box AW - 4");
		$this->form->addElement('static', null, "If you selected [Yes] to [part e in 8-321],go to 8-327");
		$this->form->addElement('static', null, "Otherwise, go to 8-328");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_327
		$this->form->addElement("static", null, "8-327 You said that you put additives in the animal feed. Which did you add? Code all that apply.");
		$list = array("a"=>"a) Carbarsone/carbodox", "b"=>"b) Olaquindox", "c"=>"c) Roxarsone", "d"=>"d) Nitarsone", "e"=>"e) Obpa",  "f"=>"f) Arsanilic acid",  "g"=>"g) Antibiotics",  "h"=>"h) Hormones",  "i"=>"i) Something else with chemical exposure");
		reset($list);

		while(list($field, $label) = each($list)){

			$this->form->addElement("select", "q8_327_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_327_{$field}", array("q8_321_e{@}=={@}01_yes"), "Required if mixed additives");
		}

		$this->addTextAreaElementRD('q8_327other', $this->indent . 'If you selected [Something else with chemical exposure], please specify:');
		$this->XINRegisterRule("q8_327other", array("q8_327_i{@}=={@}01_yes"), "You must specify something else", "q8_327other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_328
		$this->form->addElement("select", "q8_328", "8-328 Did the farms you worked on use pesticides or herbicides to control insects or weeds?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_328", array("q8_328{@}=={@}NEVER_REQUIRED"));
		$this->form->addElement('static', null, "If you selected [No], [Refused], or [Don't know], go to Lubricating Module"); 

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box AW - 5");
		$this->form->addElement('static', null, "If you selected [Yes] to [part a in 8-321] and [Yes] to [8-328], go to 8-329, 8-330, 8-331, 8-332");
		$this->form->addElement('static', null, "Otherwise, go to 8-333");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_329
		$this->form->addElement('static', null, "8-329 Between [-3] and DOBS, which crops did you pick by hand? Code all that apply:");
		$list = array("a"=>"a) Apples", "b"=>"b) Corn", "c"=>"c) Cotton", "d"=>"d) Cucumbers", "e"=>"e) Flowers",  "f"=>"f) Grapefruit",  "g"=>"g) Grapes",  "h"=>"h) Green beans",  "i"=>"i) Lemons",  "j"=>"j) Lettuce",  "k"=>"k) Limes",  "l"=>"l) Melons",  "m"=>"m) Oranges",  "n"=>"n) Peaches",  "o"=>"o) Pears",  "p"=>"p) Rice",  "q"=>"q) Spinach",  "r"=>"r) Squash",  "s"=>"s) Tomatoes",  "t"=>"t) Wheats",  "u"=>"u) Other");

		foreach ($list as $field=>$label)
		{
			$this->form->addElement("select", "q8_329_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_329_{$field}", array("q8_321_a{@}=={@}01_yes", "q8_328{@}=={@}01_yes"), "Required if picked fruit or vegetables, and farm(s) used pesticides or herbicides");
		}

		$this->addTextAreaElementRD('q8_329other', $this->indent . 'If you selected [Other], please specify:');
		$this->XINRegisterRule("q8_329other", array("q8_329_u{@}=={@}01_yes"), "You must specify other", "q8_329other_group");
		reset($list);
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_330
		$this->form->addElement("select", "q8_330", "8-330 Between [-3] and DOBS, how many times did you ever enter a field or orchard to pick or gather fruits or vegetables, grains, or other crops within 2 days of having been sprayed with pesticides, herbicides, weed killers, insecticides, or bug killers?",  array(NULL=>"", "01" => "01 Never", "02" => "02 Once", "03" => "03  2-5 times", "04" => "04 6-10 times", "05" => "05 More than 10 times", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_330", array("q8_321_a{@}=={@}01_yes", "q8_328{@}=={@}01_yes"), "Required if picked fruit or vegetables, and farm(s) used pesticides or herbicides");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_331
		$this->form->addElement("select", "q8_331", "8-331 Some people work at jobs where their clothes or shoes get dirty from oil, dust, chemicals, ect. How often did your work clothes get dirty at this job?",  array(NULL=>"", "01" => "01 Never", "02" => "02 Sometimes", "03" => "03  Always", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_331", array("q8_321_a{@}=={@}01_yes", "q8_328{@}=={@}01_yes"), "Required if picked fruit or vegetables, and farm(s) used pesticides or herbicides");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_332
		$this->form->addElement('static', null, "8-332 What clothing did you usually wear at work? Code all that apply:");
		$list = array("a"=>"a) Shorts or short skirt", "b"=>"b) Long pants or a long skirt", "c"=>"c) Short-sleeved shirt or blouse", "d"=>"d) Long-sleeved shirt or dress", "e"=>"e) Jacket, sweatshirt, apron, or other item worn over your clothes");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_332_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_332_{$field}", array("q8_321_a{@}=={@}01_yes", "q8_328{@}=={@}01_yes"), "Required if picked fruit or vegetables, and farm(s) used pesticides or herbicides");
		}

		$this->form->addElement('static', null, "<br/>");


		//q8_333
		$this->form->addElement("select", "q8_333", "8-333 After handling fruits or vegetables, oil, dust, chemicals, ect., did you usually:",  array(NULL=>"", "01" => "01 Change your clothes immediately", "02" => "02 Change clothes during lunch/ bathroom break", "03" => "03  Change clothes at the end of the day", "04" => "04 Wear the same clothes two days in a row or more before washing them", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_333", array("q8_333{@}=={@}NEVER_REQUIRED")); 
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: LUBRICATING ENGINES & MACHINERY");
		$this->form->addElement('static', null, "<br/>");


		//q8_334
		$this->form->addElement("select", "q8_334", "8-334 Did you routinely use lubricating oils, or waxes on engines or machinery?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_334", array("q8_334{@}=={@}NEVER_REQUIRED")); 
		$this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused], or [Don't Know], end Module and go to 8-338");
		$this->form->addElement('static', null, "<br/>");


		//q8_335
		$this->addTextAreaElementRD('q8_335', "8-335 What types of lubricants did you work with?");
		$this->XINRegisterRule("q8_335", array("q8_334{@}=={@}01_yes"), "Required if used lubricating oils or waxes", "q8_335_group");
		$this->form->addElement('static', null, "<br/>");


		//q8_336
		$this->form->addElement('static', null, "8-336 What types of cutting oils did you work with? Code all that apply:");
		$list = array("a"=>"a) Straight cutting oils or oils that look and feel like motor oil", "b"=>"b) Soluble cutting oils or oils that are milky white", "c"=>"c) Synthetic cutting oils or oils that feel like water or may be brightly colored, such as green or blue", "d"=>"d) Something else");
		
		foreach ($list as $field=>$label)
		{
			$this->form->addElement("select", "q8_336_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_336_{$field}", array("q8_334{@}=={@}01_yes"), "Required if used lubricating oils or waxes");
		}

		$this->addTextAreaElementRD('q8_336other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule("q8_336other", array("q8_336_d{@}=={@}01_yes"), "You must specify something else", "q8_336other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_337
		$this->form->addElement('static', null, "8-337 How often did you use the following lubricants?");
		$this->form->addElement('static', null, "<i>Probe: How many hours per day, per week or per month did you use the following lubricants?</i>");
		$this->form->addElement('static', null, "<br/>");

		foreach ($list as $field=>$label)
		{

			$this->form->addElement('select', "q8_337_{$field}", "{$label}:", array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->XINRegisterRule("q8_337_{$field}", array("q8_336_{$field}{@}=={@}01_yes"), "Required if used this lubricant");
			$this->addTextAreaElementRD("q8_337_number{$field}", $this->indent . 'Number:');
			$this->XINRegisterRule("q8_337_number{$field}", array("q8_337_{$field}{@}=={@}01|02|03|04"), "You must specify a number", "q8_337_number{$field}_group");
		}

		reset($list);

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: CLEANING WITH ORGANIC SOLVENTS");
		$this->form->addElement('static', null, "<br/>");

		
		//q8_338
		$this->form->addElement("select", "q8_338", "8-338  Did you routinely clean parts with organic solvents or other products to degrease metal parts?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_338", array("q8_338{@}=={@}NEVER_REQUIRED")); 
		$this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused], or [Don't Know], end Module and go to 8-342");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_339
		$this->form->addElement('static', null, "8-339 What cleaning products did you typically use? Code all that apply:");
		$list = array("a"=>"a) [Gunk] or similar cleaner", "b"=>"b) Acid", "c"=>"c) Alcohols", "d"=>"d) Alkalis or caustics", "e"=>"e) Cutting oils",  "f"=>"f) Diesel",  "g"=>"g) Gasoline",  "h"=>"h) Mineral spirits, paint thinner, naphtha, Stoddard solvent, turpentin", "i"=>"i) Something else");

		foreach ($list as $field=>$label)
		{
			$this->form->addElement("select", "q8_339_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_339_{$field}", array("q8_338{@}=={@}01_yes"), "Required if degreased metal parts");
		}

		$this->addTextAreaElementRD('q8_339other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule("q8_339other", array("q8_339_i{@}=={@}01_yes"), "You must specify something else", "q8_339other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_340
		$this->form->addElement('static', null, "8-340 How often did you use the following cleaning products?");
		$this->form->addElement('static', null, "<i>Probe: How many hours per day, per week or per month did you use the following cleaning products?</i>");
		$this->form->addElement('static', null, "<br/>");


		foreach ($list as $field=>$label)
		{
			$this->form->addElement('select',"q8_340_{$field}", "{$label}:",  array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->XINRegisterRule("q8_340_{$field}", array("q8_339_{$field}{@}=={@}01_yes"), "Required if used this product");
			$this->addTextAreaElementRD("q8_340_number{$field}", $this->indent . 'Number:');
			$this->XINRegisterRule("q8_340_number{$field}", array("q8_340_{$field}{@}=={@}01|02|03|04"), "You must specify", "q8_340_number{$field}_group");
		}

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		

		//q8_341
		$this->form->addElement("select", "q8_341", "8-341 How often did you work with heating degreasing chemicals?",  array(NULL=>"", "01" => "01 Always", "02" => "02 Sometimes", "03" => "03  Never", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_341", array("q8_338{@}=={@}01_yes"), "Required if degreased metal parts");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");



	} //end function _page34() =====================================================


	function rulesPage34($fields)
	{
		$errors = array();

		$options = array("a", "b", "c", "d", "e", "f", "g", "h", "i", "j");


                $db =& Database::singleton();

                $otherCommentID = $db->selectOne("SELECT CommentID from flag where Test_name='EARLI_interview_PART_3' and SessionID=" . $this->getSessionID());
                $db->selectRow("SELECT q8_5, q8_6_8 FROM EARLI_interview_PART_3 WHERE CommentID='".$otherCommentID."'", $occupation);


		if ($occupation["q8_5"] == "08")
		{
			for ($i=0; $i<8; $i++)
			{	
				if (empty($fields["q8_321_$options[$i]"]))
					$errors["q8_321_$options[$i]"] = "You must specify";
			}

                        if (empty($fields["q8_334"]))
 	                       $errors["q8_334"] = "You must specify";

                        if (empty($fields["q8_338"]))
  	                      $errors["q8_338"] = "You must specify";

		}	


		if ($occupation["q8_5"] == "09" && ($occupation["q8_6_8"] == "40" || $occupation["q8_6_8"] == "41"))
		{
                        for ($i=0; $i<8; $i++)
                        {
                                if (empty($fields["q8_321_$options[$i]"]))
                                        $errors["q8_321_$options[$i]"] = "You must specify";
                        }

                        if (empty($fields["q8_334"]))
                               $errors["q8_334"] = "You must specify";

                        if (empty($fields["q8_338"]))
                              $errors["q8_338"] = "You must specify";
		}


		for ($i=0; $i<8; $i++)
		{
			if ($fields["q8_321_$options[$i]"] == "01_yes")
			{
				for ($j=0; $j<10; $j++)
				{
					if (empty($fields["q8_325_$options[$j]"]))
						$errors["q8_325_$options[$j]"] = "You must specify";
				}

				if (empty($fields["q8_328"]))
					$errors["q8_328"] = "You must specify";

				if (empty($fields["q8_333"]))
					$errors["q8_333"] = "You must specify";

				break;
			}
		}
		return $errors;
	}



	function _page35(){   // ========================================================


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: PAINTING, PAINT REMOVAL, PAINT CLEANING");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>The next few questions ask about painting, varnishing, and staining.");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//function with more complex rules
		$this->form->addFormRule(array(&$this, 'rulesPage35'));


		//q8_342
		$this->form->addElement('static', null, "8-342 Did you typically do any of the following activities? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$list = array("a"=>"a) Painting, varnishing, or staining", "b"=>"b) Paint removal", "c"=>"c) Paint thinning and cleaning", "d"=>"d) Something else", "e"=>"e) None of the above");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_342_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_342_{$field}", array("q8_342_{$field}{@}=={@}NEVER_REQUIRED"));
		}

		$this->addTextAreaElementRD('q8_342other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule("q8_342other", array("q8_342_e{@}=={@}01_yes"), "You must specify something else", "q8_342other_group");
		$this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] and/or [Don't Know] to <u>part a-d</u>, or [Yes] to [part e], end Module and go to 8-35]");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>BOX PT-1");
		$this->form->addElement('static', null, "If you selected [Yes] to [part a in 8-342], go to 8-343, 8-344, and 8-345");
		$this->form->addElement('static', null, "Otherwise [go to Box PT-2]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_343
		$this->form->addElement('static', null, "8-343 What kind of paint did you use? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Laytex or water-based paint", "b"=>"b) Acrylic", "c"=>"c) Oil-based paint (enamel)", "d"=>"d) Something else");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_343_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_343_{$field}", array("q8_342_a{@}=={@}01_yes"), "Required if did painting, varnishing or staining");
		}

		$this->addTextAreaElementRD('q8_343other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule("q8_343other", array("q8_343_d{@}=={@}01_yes"), "You must specify something else", "q8_343other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_344
		$this->form->addElement('static', null, "8-344 Did you usually brush, roll, or spray paint? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Brush", "b"=>"b) Roll", "c"=>"c) Spray", "d"=>"d) Something else");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_344_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_344_{$field}", array("q8_342_a{@}=={@}01_yes"), "Required if did painting, varnishing or staining");
		}

		$this->addTextAreaElementRD('q8_344other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule("q8_344other", array("q8_344_d{@}=={@}01_yes"), "You must specify something else", "q8_344other_group");
		$this->form->addElement('static', null, $this->indent . "If you selected [Yes] to [8-64 part b], go to 8-68");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_345
		$this->form->addElement("select", "q8_345", "8-345 Did you use primers with lead, chromate, or zinc?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_345", array("q8_342_a{@}=={@}01_yes"), "Required if did painting, varnishing or staining");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>BOX PT-2");
		$this->form->addElement('static', null, "If you selected [Yes] to [part b in 8-342], go to 8-346");
		$this->form->addElement('static', null, "Otherwise [go to Box PT-3]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_346
		$this->form->addElement('static', null, "8-346 How did you typically remove paint? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Heat gun", "b"=>"b) Scraper or wire stripper with a drill bit attachment", "c"=>"c) Chemical paint stripper", "d"=>"d) Some other paint removal method");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_346_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_346_{$field}", array("q8_342_b{@}=={@}01_yes"), "Required if did paint removal");
		}

		$this->addTextAreaElementRD('q8_346other', $this->indent . 'If you selected [Some other paint removal method], please specify:');
		$this->XINRegisterRule("q8_346other", array("q8_346_d{@}=={@}01_yes"), "You must specify something else", "q8_346other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>BOX PT-3");
		$this->form->addElement('static', null, "If you selected [Yes] to [part c in 8-342], go to 8-347");
		$this->form->addElement('static', null, "Otherwise [go to 8-349]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");



		//q8_347
		$this->form->addElement('static', null, "8-347 What did you typically use to thin or clean paint, varnish or stain? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Paint thinner, mineral spirits, or turpertin", "b"=>"b) Lacquer thinner", "c"=>"c) Alcohol", "d"=>"d) Water", "e"=>"e) Citrus-based products",  "f"=>"f) Gasoline or kerosene",  "g"=>"g) Other");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_347_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_347_{$field}", array("q8_342_c{@}=={@}01_yes"), "Required if did paint thinning or cleaning");
		}

		$this->addTextAreaElementRD('q8_347other', $this->indent . 'If you selected [Other], please specify:');
		$this->XINRegisterRule("q8_347other", array("q8_347_g{@}=={@}01_yes"), "You must specify other", "q8_347other_group");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>BOX PT-4");
		$this->form->addElement('static', null, "If you selected [Yes] to [part c in 8-346], go to 8-348");
		$this->form->addElement('static', null, "Otherwise [go to 8-349]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_348
		$this->form->addElement('static', null, "8-348 What chemicals did you use to strip paint? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Lacquer or paint thinner", "b"=>"b) Lye (Sodium hydroxide)", "c"=>"c) Ammonia (Ammonia Hydroxide)", "d"=>"d) Other");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_348_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_348_{$field}", array("q8_346_c{@}=={@}01_yes"), "Required if used chemical paint stripper");
		}

		$this->addTextAreaElementRD('q8_348other', $this->indent . 'If you selected [Other], please specify:');
		$this->XINRegisterRule("q8_348other", array("q8_348_d{@}=={@}01_yes"), "You must specify other", "q8_348other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_349
		$this->form->addElement('static', null, "8-349 How often did you use the following paint, paint thinners, or paint strippers?");
		$this->form->addElement('static', null, "<i>Probe: How many hours per day, per week or per month did you use the following paint, paint thinners, or paint strippers?</i>");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Laytex or water-based paint", "b"=>"b) Acrylic", "c"=>"c) Oil-based paint (enamel)","d"=>"d) Paint thinner, mineral spirits, or turpertin", "e"=>"e) Lacquer thinner", "f"=>"f) Alcohol", "g"=>"g) Water", "h"=>"h) Citrus-based products",  "i"=>"i) Gasoline or kerosene", "j"=>"j) Lacquer or paint thinner", "k"=>"k) Lye (Sodium hydroxide)", "l"=>"l) Ammonia (Ammonia Hydroxide)", "m"=>"m) Other" );

		reset($list);
		while(list($field, $label) = each($list)){

			$this->form->addElement('select', "q8_349_{$field}", "{$label}:", array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->XINRegisterRule("q8_349_{$field}", array("q8_342_a{@}=={@}01_yes"), "Required if used:");
			$this->addTextAreaElementRD("q8_349_number{$field}", $this->indent . 'Number:');
			$this->XINRegisterRule("q8_349_number{$field}", array("q8_349_{$field}{@}=={@}01|02|03|04"), "You must specify a number", "q8_349_number{$field}_group");
		}

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: SOLDERING AND WELDING");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-350 Did you do any of the following? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Soldering or brazing", "b"=>"b) Smell fumes from others who solder or braze", "c"=>"c) Welding or flame cutting", "d"=>"d) Smell fumes from others who weld or flame cut,", "e"=>"e) Some other welding or soldering method?",  "f"=>"f) None of the above");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_350_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_350_{$field}", array("q8_350_{$field}{@}=={@}NEVER_REQUIRED"));
		}

		$this->addTextAreaElementRD('q8_350other', $this->indent . 'If you selected [Some other welding or soldering method?], please specify:');
		$this->XINRegisterRule("q8_350other", array("q8_350_e{@}=={@}01_yes"), "You must specify other", "q8_350other_group");
		$this->form->addElement('static', null, $this->indent . "If you selected [None of the above], end Module and go to 8-358");
		$this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] and/or [Don't Know] for [all part a-f], end Module and go to 8-358]");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>BOX SW-1");
		$this->form->addElement('static', null, $this->indent . "If you selected [Yes] to [part a or b in 8-350], go to 8-354, 8-355, 8-356, 8-357");
		$this->form->addElement('static', null, $this->indent . "Otherwise, go to 8-357a");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_351
		$this->form->addElement('static', null, "8-351 What types of metal did {you/they/you and those who weld or flame cut around you} weld or flame cut? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Aluminum", "b"=>"b) Brass or bronz", "c"=>"c) Cast iron", "d"=>"d) Copper", "e"=>"e) Steel",  "f"=>"f) Titanium-based alloy",  "g"=>"g) Other");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_351_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_351_{$field}", array("q8_351_{$field}{@}=={@}NEVER_REQUIRED"));
		}

		$this->addTextAreaElementRD('q8_351other', $this->indent . 'If you selected [Other], please specify:');
		$this->XINRegisterRule("q8_351other", array("q8_351_g{@}=={@}01_yes"), "You must specify other", "q8_351other_group");
		$this->form->addElement('static', null, $this->indent . "If you selected [Yes] to [any part in a-d], go to 8-353");
		$this->form->addElement('static', null, $this->indent . "If you selected [Yes] to [any part in f and g], go to 8-353");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_352
		$this->form->addElement("select", "q8_352", "8-352 What kind of steel was it?",  array(NULL=>"", "01" => "01 Cadmium plated steel", "02" => "02 Chromium plated steel", "03" => "03  Galvanized iron", "04" => "04 Lead-plated or leaded steel", "05" => "05 Mild, carbon, or construction steel", "06" => "06 Stainless steel", "07" => "07 Another type of steel?", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_352", array("q8_351_e{@}=={@}01_yes"), "You must specify kind of steel");
		$this->addTextAreaElementRD('q8_352other', $this->indent . 'If you selected [Another type of steel], please specify:');
		$this->XINRegisterRule("q8_352other", array("q8_352{@}=={@}07"), "You must specify other", "q8_352other_group");
		$this->form->addElement('static', null, "<br/>");



		//q8_353
		$this->form->addElement("select", "q8_353", "8-353 What type of welding or flame cutting did {you/they/you and those who weld or flame cut around you} do?",  array(NULL=>"", "01" => "01 Oxygas, oxyfuel, or oxyacetylene", "02" => "02 MIG (Metal Inert Gas)", "03" => "03  TIG (Tungsten Inert Gas)", "04" => "04 Stick electrode (shielded metal arc welding)", "05" => "05 Resistance, such as sport, seam, flash, butt, and projection", "06" => "06 Solid state, such as friction or roll", "07" => "07 Plasma arc", "08" => "08 Submerged arc", "09" => "09 Something else", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_353", array("q8_353{@}=={@}NEVER_REQUIRED"));
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>BOX SW-2");
		$this->form->addElement('static', null, "If you selected [Yes] to [part a or b in 8-350], go to 8-354, 8-355, 8-356, 8-357");
		$this->form->addElement('static', null, "Otherwise, go to 8-357a");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_354
		$this->form->addElement('static', null, "8-354 What did {you/they/you and those who solder or braze around you} solder or braze? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Pipes", "b"=>"b) Electrical or electronic parts", "c"=>"c) Other");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_354_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_354_{$field}", array("q8_354_{$field}{@}=={@}NEVER_REQUIRED"));
		}

		$this->addTextAreaElementRD('q8_354other', $this->indent . 'If you selected [Other], please specify:');
		$this->XINRegisterRule("q8_354other", array("q8_354_c{@}=={@}01_yes"), "You must specify other", "q8_354other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_355
		$this->form->addElement("select", "q8_355", "8-355 Did {you/they/you and those who solder or braze around you} use lead-free solder?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_355", array("q8_355{@}=={@}NEVER_REQUIRED"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_356
		$this->form->addElement("select", "q8_356", "8-356 Did the solder usually contain any unusual ingredients such as cadmium, silver, copper, nickel, zinc, arsenic, beryllium, antimony, indium, or bismuth?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_356", array("q8_356{@}=={@}NEVER_REQUIRED"));
		$this->addTextAreaElementRD('q8_356other', 'If you selected [Yes], please specify:');
		$this->XINRegisterRule("q8_356other", array("q8_356{@}=={@}01_yes"), "You must specify ingredients", "q8_356other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_357
		$this->form->addElement('static', null, "8-357 What did {you/they/you and those who solder or braze around you} solder or braze? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$metals = array("a"=>"a) Brass", "b"=>"b) Bronze", "c"=>"c) Cast iron", "d"=>"d) Copper", "e"=>"e) Nickel",  "f"=>"f) Other types of iron",  "g"=>"g) Stainless steel",  "h"=>"h) Other steel",  "i"=>"i) Other");

		foreach ($metals as $field=>$label)
		{
			$this->form->addElement("select", "q8_357_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_357_{$field}", array("q8_357_{$field}{@}=={@}NEVER_REQUIRED"));
		}

		$this->addTextAreaElementRD('q8_357otheriron', $this->indent . 'If you selected [f) Other types of iron], please specify:');
		$this->XINRegisterRule("q8_357otheriron", array("q8_357_f{@}=={@}01_yes"), "You must specify other iron", "q8_357otheriron_group");
		$this->addTextAreaElementRD('q8_357othersteel', $this->indent . 'If you selected [h) Other steel], please specify:');
		$this->XINRegisterRule("q8_357othersteel", array("q8_357_h{@}=={@}01_yes"), "You must specify other steel", "q8_357othersteel_group");
		$this->addTextAreaElementRD('q8_357other', $this->indent . 'If you selected [i) Other], please specify:');
		$this->XINRegisterRule("q8_357other", array("q8_357_i{@}=={@}01_yes"), "You must specify other", "q8_357other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_357a
		$this->form->addElement('static', null, "8-357a How often did you use the following metals?");
		$this->form->addElement('static', null, "<i>Probe: How many hours per day, per week or per month do you use the following metals?</i>");
		$this->form->addElement('static', null, "<br/>");

		foreach ($metals as $field=>$label)
		{
			$this->form->addElement('select',"q8_357a_{$field}", "{$label}:",  array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->XINRegisterRule("q8_357a_{$field}", array("q8_357_{$field}{@}=={@}01_yes"), "Required if used this metal");
			$this->addTextAreaElementRD("q8_357a_number{$field}", $this->indent . 'Number:');
			$this->XINRegisterRule("q8_357a_number{$field}", array("q8_357a_{$field}{@}=={@}01|02|03|04"), "You must specify a number", "q8_357a_number{$field}_group");
		}

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: WOOD DUST");
		$this->form->addElement('static', null, "<br/>");


		//q8_358
		$this->form->addElement('static', null, "8-358 Did you typically do any of the following? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Saw wood", "b"=>"b) Sand wood", "c"=>"c) Machine or make wood parts", "d"=>"d) Use a wood chipper", "e"=>"e) Other activities that generate wood",  "f"=>"f) None of these");

		foreach ($list as $field=>$label)
		{
			$this->form->addElement("select", "q8_358_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_358_{$field}", array("q8_358_{$field}{@}=={@}NEVER_REQUIRED"));
		}

		reset($list); 
		$this->addTextAreaElementRD('q8_358other', $this->indent . 'If you selected [Other activities that generate wood], please specify:');
		$this->XINRegisterRule("q8_358other", array("q8_358_e{@}=={@}01_yes"), "You must specify other", "q8_358other_group");
		$this->form->addElement('static', null, $this->indent . "If you selected [None of these], go to 8-360");
		$this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] and/or [Don't Know] for <u>all</u>,go to 8-360");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_359
		$this->form->addElement('static', null, "8-359 How often did you do these things?");
		$this->form->addElement('static', null, "<i>Probe: How many hours per day, per week, or per month do you saw wood, sand wood, do machining, make wood parts, use a wood chipper, or other activities that generate wood dust?</i>");
		$this->form->addElement('static', null, "<br/>");

		
		$list = array("a"=>"a) Saw wood", "b"=>"b) Sand wood", "c"=>"c) Machine or make wood parts", "d"=>"d) Use a wood chipper", "e"=>"e) Other activities that generate wood");
		foreach ($list as $field=>$label)
		{
			$this->form->addElement('select', "q8_359_{$field}", "{$label}:",  array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->XINRegisterRule("q8_359_{$field}", array("q8_358_{$field}{@}=={@}01_yes"), "Required if did any of the above activities");
			$this->addTextAreaElementRD("q8_359_number{$field}", $this->indent . 'Number:');
			$this->XINRegisterRule("q8_359_number{$field}", array("q8_359_{$field}{@}=={@}01|02|03|04"), "You must specify a number", "q8_359_number{$field}_group");
		}

		reset($list);
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_360
		$this->form->addElement("select", "q8_360", "8-360 Did your job typically involve handling treated lumber, that is wood treated with chemical preservatives and has a greenish appearance?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_360", array("q8_360{@}=={@}NEVER_REQUIRED"));
		$this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know], end Module and go to 8-366");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_361
		$this->form->addElement('static', null, "8-361 What did you do with the treated wood or lumber? Did you...Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Handle it, carry it, or move it", "b"=>"b) Saw or cut it", "c"=>"c) Sand it", "d"=>"d) Something else", "e"=>"e) None of these");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_361_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_361_{$field}", array("q8_360{@}=={@}01_yes"), "Required if handled treated lumber");
		}

		$this->addTextAreaElementRD('q8_361other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule("q8_361other", array("q8_361_d{@}=={@}01_yes"), "You must specify something else", "q8_361other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_362
		$this->form->addElement("select", "q8_362", "8-362 When you handled the treated wood, was it usually wet or dry?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_362", array("q8_360{@}=={@}01_yes"), "Required if handled treated lumber");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_363
		$this->form->addElement("select", "q8_363", "8-363 Did you apply a preservative, such as cresotoe, to the wood yourself?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_363", array("q8_360{@}=={@}01_yes"), "Required if handled treated lumber");
		$this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know], skip to question 8-365");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_364
		$this->form->addElement('static', null, "8-364 What preservatives did you use to treat the wood? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Pentachlorophenol or PCP", "b"=>"b) Inorganic chemicals, such as copper chromium, arsenate, also called CCA or ACA", "c"=>"c) Creosote", "d"=>"d) Something else");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_364_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_364_{$field}", array("q8_363{@}=={@}01_yes"), "Required if applied a preservative to the wood");
		}

		$this->addTextAreaElementRD('q8_364other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule("q8_364other", array("q8_364_d{@}=={@}01_yes"), "You must specify something else", "q8_364other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_365
		$this->form->addElement('select', "q8_365", "8-365 How often did you handle treated wood?", array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<i>Probe: How many hours per day, per week, or per month did you handle treated wood?</i>");
		$this->XINRegisterRule("q8_365", array("q8_360{@}=={@}01_yes"), "Required if handled treated lumber");
		$this->addTextAreaElementRD("q8_365_number", $this->indent . 'Number:');
		$this->XINRegisterRule("q8_365_number", array("q8_365{@}=={@}01|02|03|04"), "You must specify a number", "q8_365_number_group");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


	} //end function _page35() =====================================================



	function rulesPage35($fields)
	{
		$errors = array();

		$options = array("a", "b", "c", "d", "e", "f", "g", "h", "i");


                $db =& Database::singleton();

                $otherCommentID = $db->selectOne("SELECT CommentID from flag where Test_name='EARLI_interview_PART_3' and SessionID=" . $this->getSessionID());
                $db->selectRow("SELECT q8_5, q8_6_8 FROM EARLI_interview_PART_3 WHERE CommentID='".$otherCommentID."'", $occupation);


		for ($i=0; $i<5; $i++)
		{
			if ($fields["q8_342_$options[$i]"] == "01_yes")
			{
				for ($j=0; $j<13; $j++)
				{
					if (empty($fields["q8_349_$options[$i]"]))
						$errors["q8_349_$options[$i]"] = "You must specify";	
				}
			}
		}


                if ($occupation["q8_5"] == "08")
                {
			for ($i=0; $i<5; $i++)
			{
				if (empty($fields["q8_342_$options[$i]"]))
					$errors["q8_342_$options[$i]"] = "You must specify";

			}
			for ($i=0; $i<6; $i++)
			{
				if (empty($fields["q8_350_$options[$i]"]))
					$errors["q8_350_$options[$i]"] = "You must specify";
			}

			for ($i=0; $i<6; $i++)
			{
				if (empty($fields["q8_358_$options[$i]"]))
					$errors["q8_358_$options[$i]"] = "You must specify";
			}

                        if (empty($fields["q8_360"]))
                                $errors["q8_360"] = "You must specify";

		}

                if ($occupation["q8_5"] == "09" && ($occupation["q8_6_8"] == "40" || $occupation["q8_6_8"] == "41"))
                {
			for ($i=0; $i<6; $i++)
			{
                                if (empty($fields["q8_350_$options[$i]"]))
                                        $errors["q8_350_$options[$i]"] = "You must specify";
			}
			
			for ($i=0; $i<6; $i++)
			{
				if (empty($fields["q8_358_$options[$i]"]))
					$errors["q8_358_$options[$i]"] = "You must specify";
			}

                        if (empty($fields["q8_360"]))
                                $errors["q8_360"] = "You must specify";
		}


		if ($fields["q8_350_a"] == "01_yes" || $fields["q8_350_b"] == "01_yes")
		{
		
			for ($i=0; $i<3; $i++)
			{
				if (empty($fields["q8_354_$options[$i]"]))
					$errors["q8_354_$options[$i]"] = "You must specify";

			}

			if (empty($fields["q8_355"]))
				$errors["q8_355"] = "You must specify";
			
			if (empty($fields["q8_356"]))
				$errors["q8_356"] = "You must specify";

			for ($i=0; $i<9; $i++)
			{
                                if (empty($fields["q8_357_$options[$i]"]))
                                        $errors["q8_357_$options[$i]"] = "You must specify";
			}
		}
	

		if ($fields["q8_350_c"] == "01_yes" || $fields["q8_350_d"] == "01_yes")
		{
                        for ($i=0; $i<7; $i++)
                        {
                                if (empty($fields["q8_351_$options[$i]"]))
                                        $errors["q8_351_$options[$i]"] = "You must specify";
			}
		}

		return $errors;
	}



	function _page36(){   // ========================================================


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: PESTICIDE USE");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

		//function with more complex rules
		$this->form->addFormRule(array(&$this, 'rulesPage36'));
		
		//q8_366
		$this->form->addElement("select", "q8_366", "8-366 Pesticides include many types of chemicals used to repel, kill, or control unwanted weeds, insects, rodents, fungi, or bacteria. They include herbicides, insecticides, rodenticides, fungicides, and bactericides. Did you mix, apply, spray, process or use pesticides?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_366", array("q8_366{@}=={@}NEVER_REQUIRED"));
		$this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know], skip to question 8-389");
		$this->form->addElement('static', null, "<br/>");


		//q8_367
		$this->form->addElement('static', null, "8-367 Between [3] and DOBS, which types of pesticides did you use? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$pesticides = array("a"=>"a) Insecticides which kill bugs", "b"=>"b) Herbicides or weed killer", "c"=>"c) Rodenticides which kill rats and mice", "d"=>"d) Fungicides which kill mold or fungus", "e"=>"e) Bactericides which kill bacteria",  "f"=>"f) Something else?");

		foreach ($pesticides as $field=>$label)
		{
			$this->form->addElement("select", "q8_367_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_367_{$field}", array("q8_366{@}=={@}01_yes"), "Required if used pesticides");
		}

		$this->addTextAreaElementRD('q8_367other', $this->indent . 'If you selected [f) Something else], please specify:');
		$this->XINRegisterRule("q8_367other", array("q8_367_f{@}=={@}01_yes"), "You must specify something else", "q8_367other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_368
		$this->form->addElement('static', null, "8-368 Where did you use the pesticides? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$list = array("a"=>"a) In or around buildings", "b"=>"b) On crops", "c"=>"c) On forests", "d"=>"d) On roads", "e"=>"e) On seeds",  "f"=>"f) On animals",  "g"=>"g) For aquatic pest control",  "h"=>"h) To process, pack, or manufacture them at warehouse or factory",  "i"=>"i) Something else?");
		reset($list);

		foreach($list as $field => $label){
			$this->form->addElement("select", "q8_368_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_368_{$field}", array("q8_366{@}=={@}01_yes"), "Required if used pesticides", "q8_368_{$field}_group");
		}        


		$this->addTextAreaElementRD('q8_368other', $this->indent . 'If you selected [i) Something else], please specify:');
		$this->XINRegisterRule("q8_368other", array("q8_368_i{@}=={@}01_yes"), "You must specify something else", "q8_368other_group");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box PU-1");
		$this->form->addElement('static', null, "If you selected [Yes] to [part a in 8-367], go to 8-369");
		$this->form->addElement('static', null, "Otherwise, go to Box PU-2");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_369
		$this->addTextAreaElementRD('q8_369', "8-369 You said that you used insecticides or bug killers. Please name all that you used");
		$this->XINRegisterRule("q8_369", array("q8_367_a{@}=={@}01_yes"), "Required if used insecticides", "q8_369_group");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box PU-2");
		$this->form->addElement('static', null, "If you selected [Yes] to [part b in 8-367], go to 8-370");
		$this->form->addElement('static', null, "Otherwise, go to Box PU-3");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_370
		$this->addTextAreaElementRD("q8_370", "8-370 You said that you used herbicides or weed killers");
		$this->XINRegisterRule("q8_370", array("q8_367_b{@}=={@}01_yes"), "Required if used herbicides", "q8_370_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>Box PU-3");
		$this->form->addElement('static', null, "If you selected [Yes] to [part c in 8-367], go to 8-371");
		$this->form->addElement('static', null,  "Otherwise, go to Box PU-4");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_371
		$this->addTextAreaElementRD("q8_371", "8-371 You said that you used rodenticides. Please name all that you use");
		$this->XINRegisterRule("q8_371", array("q8_367_c{@}=={@}01_yes"), "Required if used rodenticides", "q8_371_group");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box PU-4");
		$this->form->addElement('static', null, "If you selected [Yes] to [part d in 8-367], go to 8-372");
		$this->form->addElement('static', null, "Otherwise, go to Box PU-5");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_372
		$this->addTextAreaElementRD('q8_372', "8-372 You said that you used fungicides or mold and fungus killers. Please name all that you use");
		$this->XINRegisterRule("q8_372", array("q8_367_d{@}=={@}01_yes"), "Required if used fungicides", "q8_372_group");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box PU-5");
		$this->form->addElement('static', null, "If you selected [Yes] to [part e in 8-367], go to 8-373");
		$this->form->addElement('static', null, "Otherwise, go to 8-374");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_373
		$this->addTextAreaElementRD('q8_373', "8-373 You said that you used bactericides or bacteria killers. Please name all that you use");
		$this->XINRegisterRule("q8_373", array("q8_367_e{@}=={@}01_yes"), "Required if used bactericides", "q8_373_group");
		$this->form->addElement('static', null, "<br/>");


		//q8_374
		$this->form->addElement('static', null, "8-374 How often did you use the following pesticide products?");
		$this->form->addElement('static', null, "<i>Probe: How many hours per day, per week or per month do you use the following glues or adhesives?</i>");
		$this->form->addElement('static', null, "<br/>");
		
		foreach ($pesticides as $field=>$label)
		{
			$this->form->addElement('select', "q8_374_{$field}", "{$label}:",  array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->XINRegisterRule("q8_374_{$field}", array("q8_367_{$field}{@}=={@}01_yes"), "Required if used this pesticide product");
			$this->addTextAreaElementRD("q8_374_number{$field}", $this->indent . 'Number:');
			$this->XINRegisterRule("q8_374_number{$field}", array("q8_374_{$field}{@}=={@}01|02|03|04"), "You must specify a number", "q8_374_number{$field}_group");
		}
		$this->form->addElement('static', null, "<br/>");


		//q8_375
		$this->form->addElement('static', null, "8-375 Which of the following activities did you typically do? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$list = array("a"=>"a) Mix pesticides", "b"=>"b) Put pesticides into a spray container or tank", "c"=>"c) Spray or apply pesticides", "d"=>"d) Dispose of waste from pesticide use", "e"=>"e) Something else?");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_375_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_375_{$field}", array("q8_366{@}=={@}01_yes"), "Required if used pesticides");
		}

		$this->addTextAreaElementRD('q8_375other', $this->indent . 'If you selected [e) Something else], please specify:');
		$this->XINRegisterRule("q8_375other", array("q8_375_e{@}=={@}01_yes"), "You must specify something else", "q8_375other_group");
		$this->form->addElement('static', null, "<br/>");



		//q8_376
		$this->form->addElement("select", "q8_376", "8-376 Between [-3] and DOBS, were there 3 or more times when your clothing has gotten wet with pesticides?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_376", array("q8_366{@}=={@}01_yes"), "Required if used pesticides");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box PU-6");
		$this->form->addElement('static', null, "If you selected [Yes] to [part b in 8-368], go to 8-377");
		$this->form->addElement('static', null, "Otherwise, go to Box PU-10");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_377
		$this->form->addElement('static', null, "8-377 You said that you apply pesticides to crops. How did you usually apply them? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$list = array("a"=>"a) Using hand-held devices", "b"=>"b) By tractor or truck", "c"=>"c) By aircraft", "d"=>"d) Something else?");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_377_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_377_{$field}", array("q8_368_b{@}=={@}01_yes"), "Required if applied pesticides to crops");
		}

		$this->addTextAreaElementRD('q8_377other', $this->indent . 'If you selected [d) Something else], please specify:');
		$this->XINRegisterRule("q8_377other", array("q8_377_d{@}=={@}01_yes"), "You must specify something else", "q8_377other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>Box PU-7");
		$this->form->addElement('static', null, "If you selected [Yes] to [a in 8-377], go to 8-378");
		$this->form->addElement('static', null, "Otherwise, go to Box PU-8");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_378
		$this->form->addElement('static', null, "8-378 What type of hand-operated devices did you usually use? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$list = array("a"=>"a) Pressurized can or aerosols", "b"=>"b) Pressurized cylinders", "c"=>"c) Trigger pump sprayers or squirt guns", "d"=>"d) Hose-end sprayers", "e"=>"e) Compressed air sprayers worn on the back pack or slung over the shoulder",  "f"=>"f) Push-pull hand pump sprayer",  "g"=>"g) Something else?");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_378_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_378_{$field}", array("q8_377_a{@}=={@}01_yes"), "Required if used hand-operated devices");
		}

		$this->addTextAreaElementRD('q8_378other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule("q8_378other", array("q8_378_g{@}=={@}01_yes"), "You must specify something else", "q8_378other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>Box PU-8");
		$this->form->addElement('static', null, "If you selected [Yes] to [part b or c in 8-377], go to 8-379");
		$this->form->addElement('static', null, "Otherwise, go to Box PU-9");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_379
		$this->form->addElement('static', null, "8-379 What type of pesticide application device did you use for your vehicle or aircraft? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$list = array("a"=>"a) Low-pressure boomless sprayer", "b"=>"b) Boom sprayer", "c"=>"c) High pressure hydraulic sprayers", "d"=>"d) Air-blast sprayer", "e"=>"e) Low-volume air sprayer or mist blower",  "f"=>"f) Ultra-low volume or ULV sprayer (IF NEEDED: uses fine droplets with little water)",  "g"=>"g) Something else?");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_379_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_379_{$field}", array("q8_379_{$field}{@}=={@}NEVER_REQUIRED"));
		}

		$this->addTextAreaElementRD('q8_379other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule("q8_379other", array("q8_379_g{@}=={@}01_yes"), "You must specify something else", "q8_379other_group");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>Box PU-9");
		$this->form->addElement('static', null, "If you selected [Yes] to [part b in 8-377], go to 8-380 and 8-381");
		$this->form->addElement('static', null, "Otherwise, go to Box PU-10");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_380
		$this->form->addElement("select", "q8_380", "8-380 Did the vehicle you used for this usually have a cab?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_380", array("q8_377_b{@}=={@}01_yes"), "Required if applied pesticides by tractor or truck");
		$this->form->addElement('static', null, "<br/>");


		//q8_381
		$this->form->addElement("select", "q8_381", "8-381 Did you usually keep the windows open or closed?",  array(NULL=>"", "01" => "01 Open", "02" => "02 Closed", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_381", array("q8_377_b{@}=={@}01_yes"), "Required if applied pesticides by tractor or truck");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box PU-10");
		$this->form->addElement('static', null, "If you selected [Yes] to [part b,c or d in 8-368], go to 8-382]");
		$this->form->addElement('static', null, "Otherwise, go to Box PU-13");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_382
		$this->form->addElement('static', null, "8-382 What form of pesticide did you apply? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$list = array("a"=>"a) Liquid", "b"=>"b) Dust", "c"=>"c) Granules (typically used for landscaping)", "d"=>"d) Something else?");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_382_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_382_{$field}", array("q8_382_{$field}{@}=={@}NEVER_REQUIRED"));
		}

		$this->addTextAreaElementRD('q8_382other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule("q8_382other", array("q8_382_d{@}=={@}01_yes"), "You must specify something else", "q8_382other_group");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box PU-11");
		$this->form->addElement('static', null, "If you selected [Yes] to [part a in 8-382], go to 8-383");
		$this->form->addElement('static', null, "Otherwise, go to Box PU-12");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_383
		$this->form->addElement('static', null, "8-383 What type of liquid did you apply? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$list = array("a"=>"a) Coarse, which are produced by coarse disk or solid stream gun nozzles", "b"=>"b) Fine, which are produced by high pressure hollowcone and fan-spray nozzles", "c"=>"c) Mists, which are produced by high pressure pumps, rotors and atomizers", "d"=>"d) Aerosols and fogs, which are produced by thermal aerosol generators, rotors and atomizers", "e"=>"e) Smokes and fumes, which are produced by thermal fog generators",  "f"=>"f) Vapors, which are droplets less than 0.001 micron",  "g"=>"g) Something else");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_383_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_383_{$field}", array("q8_382_a{@}=={@}01_yes"), "Required if applied liquid pesticide");
		}

                $this->addTextAreaElementRD('q8_383other', $this->indent . 'If you selected [Something else], please specify:');
                $this->XINRegisterRule("q8_382other", array("q8_383_g{@}=={@}01_yes"), "You must specify something else", "q8_383other_group");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box PU-12");
		$this->form->addElement('static', null, "If you selected [Yes] to [part b in 8-382], go to 8-384");
		$this->form->addElement('static', null, "Otherwise, go to Box PU-13");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_384
		$this->form->addElement('static', null, "8-384 What type of dust did you apply? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$list = array("a"=>"a) Coarse", "b"=>"b) Medium", "c"=>"c) Fine");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_384_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_384_{$field}", array("q8_382_b{@}=={@}01_yes"), "Required if applied dust pesticide");
		}

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box PU-13");
		$this->form->addElement('static', null, "If you selected [Yes] to [part f in 8-368], go to 8-385 and 8-386");
		$this->form->addElement('static', null, "Otherwise, go to Box PU-14");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_385
		$this->form->addElement("select", "q8_385", "8-385 You said that you applied pesticides to animals. What type of animals did you typically apply pesticides to?",  array(NULL=>"", "01" => "01 Farm animals", "02" => "02 Companion animals, such as dogs and cats", "03" => "03  Both farm animals and companion animals", "04" => "04 Some other type of animal?", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_385", array("q8_368_f{@}=={@}01_yes"), "Required if applied pesticides on animals");
		$this->addTextAreaElementRD('q8_385other', $this->indent . 'If you selected [Some other type of animal], please specify:');
		$this->XINRegisterRule("q8_385other", array("q8_385{@}=={@}04"), "You must specify other", "q8_385other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_386
		$this->form->addElement('static', null, "8-386 How did you usually them? Did you...Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$list = array("a"=>"a) Spray the animals", "b"=>"b) Dust or pour it on animals", "c"=>"c) Inject the animals", "d"=>"d) Use ear tags", "e"=>"e) Dip the animals", "f"=>"f) Use power duster",  "g"=>"g) Use pest strips",  "h"=>"h) Use fog/mist animals",  "i"=>"i) Use rope wick",  "j"=>"j) Use something else");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_386_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_386_{$field}", array("q8_368_f{@}=={@}01_yes"), "Required if applied pesticides on animals");
		}

		$this->addTextAreaElementRD('q8_386other', $this->indent . 'If you selected [j) Use something else], please specify:');
		$this->XINRegisterRule("q8_386other", array("q8_386_j{@}=={@}01_yes"), "You must specify something else", "q8_386other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box PU-14");
		$this->form->addElement('static', null, "If you selected [Yes] to [part a in 8-368], go to 8-387");
		$this->form->addElement('static', null, "Otherwise, go to 8-388");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_387
		$this->form->addElement('static', null, "8-387 You said that you applied pesticides in or around buildings. Did you usually use a...Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$list = array("a"=>"a) Mist blower", "b"=>"b) Hand-held spray gun or wand with a spray", "c"=>"c) Backpack sprayer", "d"=>"d) Rig that sat on the floor", "e"=>"e) Dust by hand", "f"=>"f) Sub-surface application methods, such as for termite control", "g"=>"g) Something else?");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_387_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_387_{$field}", array("q8_368_a{@}=={@}01_yes"), "Required if applied pesticides in or around buildings");
		}

		$this->addTextAreaElementRD('q8_387other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule("q8_387other", array("q8_387_g{@}=={@}01_yes"), "You must specify something else", "q8_387other_group");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q8_388
		$this->addTextAreaElementRD('q8_388', "8-388 On average, how many total days a year did you apply pesticides?");
		$this->XINRegisterRule("q8_388", array("q8_366{@}=={@}01_yes"), "Required if applied pesticides", "q8_388_group");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: FUEL AND EXHAUST SMELLS");
		$this->form->addElement('static', null, "<br/>");

		//q8_389
		$this->form->addElement("select", "q8_389", "8-389 Did you regularly smell fuel vapors, such as from gas or fuel tanks, or exhaust vapors, such as from car or truck tail pipes?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_389", array("q8_389{@}=={@}NEVER_REQUIRED"));
		$this->form->addElement('static', null, $this->indent . "If you selected [No], end Module and go to 8-391");
		$this->form->addElement('static', null, "<br/>");


		//q8_390
		$this->form->addElement("select", "q8_390", "8-390 How strong was the smell?",  array(NULL=>"", "01" => "01 Slight", "02" => "02 Moderate", "03" => "03  Strong", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q8_390", array("q8_389{@}=={@}01_yes"), "Required if smelled fuel or exhaust vapors");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: CLEAN HANDS");
		$this->form->addElement('static', null, "<br/>");


		//q8_391
		$this->form->addElement("select", "q8_391", "8-391 Did you regularly get chemicals or dust on your hands or skin?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->XINRegisterRule("q8_391", array("q8_391{@}=={@}NEVER_REQUIRED"));
		$this->form->addElement('static', null, $this->indent . "If you selected [No], end Module and go to 8-13");
		$this->form->addElement('static', null, "<br/>");


		//q8_392
		$this->form->addElement('static', null, "8-392 When you had chemicals or dust on your hands, when did you wash your hands? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$list = array("a"=>"a) When taking a break at work", "b"=>"b) Before eating", "c"=>"c) Before smoking", "d"=>"d) At the end of the work shift", "e"=>"e) When the task is completed",  "f"=>"f) Whenever I get my hands dirty",  "g"=>"g) Don't wash hands");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_392_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_392_{$field}", array("q8_391{@}=={@}01_yes"), "Required if got chemicals or dust on hands or skin");
		}

		$this->form->addElement('static', null, $this->indent . "If you selected [Don't wash hands], end Module and go to 8-13");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");



		//q8_393
		$this->form->addElement('static', null, "8-393 What did you use to wash chemicals or dust off your hands? Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Soap and water or water only", "b"=>"b) [Goop] or similar cleaners", "c"=>"c) Mineral spirits, turpentine, or paint thinner", "d"=>"d) Gasoline or kerosene", "e"=>"e) Something else");
		reset($list);

		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_393_{$field}", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->XINRegisterRule("q8_393_{$field}", array("q8_392_g{@}!={@}01_yes", "q8_392_g{@}!={@}"), "Required if washed hands");
		}

		$this->addTextAreaElementRD('q8_393other', $this->indent . 'If you selected [Something else], please specify:');
		$this->XINRegisterRule("q8_393other", array("q8_393_e{@}=={@}01_yes"), "You must specify something else", "q8_393other_group");	

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>When complete module complete, and there are NO more Occupational Modules to Complete listed in the Occupational Coding Box then [go to 8-13]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


	} //end function _page36() =====================================================



	function rulesPage36($fields)
	{
		$errors = array();

		$options = array("a", "b", "c", "d", "e", "f", "g", "h", "i");


                $db =& Database::singleton();

                $otherCommentID = $db->selectOne("SELECT CommentID from flag where Test_name='EARLI_interview_PART_3' and SessionID=" . $this->getSessionID());
                $db->selectRow("SELECT q8_5, q8_6_8 FROM EARLI_interview_PART_3 WHERE CommentID='".$otherCommentID."'", $occupation);

                if ($occupation["q8_5"] == "08")
                {
			if (empty($fields["q8_366"]))
				$errors["q8_366"] = "You must specify";

			if (empty($fields["q8_389"]))
				$errors["q8_389"] = "You must specify";

			if (empty($fields["q8_391"]))
				$errors["q8_391"] = "You must specify";
		}
		

                if ($occupation["q8_5"] == "09" && ($occupation["q8_6_8"] == "40" || $occupation["q8_6_8"] == "41"))
                {
                        if (empty($fields["q8_366"]))
        	                 $errors["q8_366"] = "You must specify";

                        if (empty($fields["q8_389"]))
                                $errors["q8_389"] = "You must specify";

                        if (empty($fields["q8_391"]))
                                $errors["q8_391"] = "You must specify";
                }


                if ($fields["q8_377_a"] == "01_yes" || $fields["q8_377_b"] == "01_yes")
                {
                        for ($i=0; $i<7; $i++)
                        {
                                if (empty($fields["q8_379_$options[$i]"]))
                                        $errors["q8_379_$options[$i]"] = "Required if applied pesticides by tractor or truck";
                        }
                }


		if ($fields["q8_368_b"] == "01_yes" || $fields["q8_368_c"] == "01_yes" || $fields["q8_368_d"] == "01_yes")
		{
			for ($i=0; $i<4; $i++)
			{
				if (empty($fields["q8_382_$options[$i]"]))
					$errors["q8_382_$options[$i]"] = "You must specify";
			}
		}	
		return $errors;
	}



	function _page37(){   // ========================================================
		

		$timeOptions = array_combine(range(1,12), range(1,12));

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('header', "end_interview", "End of EARLI Interview Section 8 long");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addFormRule(array(&$this, 'rulesPage37'));

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
		$this->form->addElement('static', null, "<br/>");

                unset($group);
                $this->form->addElement('static', null, "<br/>");

                $this->XINRegisterRule("interview_end_time", array("interivew_end_date{@}!={@}NULL"), "Required", "interview_end_time_group");
                $this->XINRegisterRule("AMPM_bottom", array("interivew_end_date{@}!={@}NULL"), "Required", "interview_start_time_group");


		//interviewer notes
		$this->addTextAreaElement('interviewer_notes', "Interviewer's notes");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

	} //end function _page37() =======================================================


	function rulesPage37($fields)
        {
                $errors = array();

		if(empty($fields["interview_end_time"]) && empty($fields["AMPM_bottom"]))
			$errors["interview_end_time_group"] = "You must specify time";


		return $errors;
	}	

/*
	function _page38() { // ==========================================================

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Occupational Insert Form (questions 8-5 to 8-12)");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Now I will ask you questions about next job you mentioned, starting with (2nd, 3rd, 4th, ect) job where you worked. We will begin with the next job where you worked you the most hours.");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//occ_insert_q8_5
		$this->form->addElement("select", "occ_insert_q8_5", "8-5 What is your job title or occupation? (For example, teacher, secretary, nurse, clerk, maid, paralegal, or lab assistant)", array(NULL=>"", "01" => "01 Any Health Care (Human and Animal)", "02" => "02 Education/Teaching", "03" => "03  Restaurant, Bar, or Food Service", "04" => "04 Cleaning and Building Maintenance", "05" => "05 Child Care (Pre-Kindergarten)", "06" => "06 Beautician/Barber", "07" => "07 Driver", "08" => "08 Agriculture, Farming, Landscaping, Pesticide Workers", "09" => "09 Other Industry or Business", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//occ_insert_q8_6
		$this->form->addElement('static', null, "8-6 What type of activities do you do most often at this job? (For example, teach classes, work on the computer, keep account books, file, photocopy, answer phone, wait table, help customers, do lab work, or carpentry)");
		$this->form->addElement('static', null, "<br/>");


		//occ_insert_q8_6a
		$this->form->addElement("select", "occ_insert_q8_6a", "ANY HEALTH CARE (HUMAN AND ANIMAL)",  array(NULL=>"", "01" => "01 Health care provider office (e.g. physicians, dentist, etc.)", "02" => "02 Free-standing outpatient/ambulatory care center facility; Center facility", "03" => "03  Hospital", "04" => "04 Home health care agency", "05" => "05 Skilled nursing facility/rehab facility", "06" => "06 Nursing home/assisted living", "07" => "07 Pharmacy", "08" => "08 Veterinary clinic/hospital", "09" => "09 Other health care facility or service", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->addTextAreaElementRD('occ_insert_q8_6aother', $this->indent . 'If you selected [Other health care facility or service], please specify:');
		$this->XINRegisterRule("occ_insert_q8_6aother", array("occ_insert_q8_6a{@}=={@}09"), "You must specify other");
		$this->form->addElement('static', null, "<br/>");


		//occ_insert_q8_6b
		$this->form->addElement("select", "occ_insert_q8_6b", "EDUCATION/TEACHING",  array(NULL=>"", "10" => "10 Elementary or middle/high school", "11" => "11 Business, technical or trade school", "12" => "12 College or university", "13" => "13 Other school/education provider", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->addTextAreaElementRD('occ_insert_q8_6bother', $this->indent . 'If you selected [Other school/education provider], please specify:');
		$this->XINRegisterRule("occ_insert_q8_6bother", array("occ_insert_q8_6b{@}=={@}13"), "You must specify other");
		$this->form->addElement('static', null, "<br/>");


		//occ_insert_q8_6c
		$this->form->addElement("select", "occ_insert_q8_6c", "RESTAURANT, BAR, OR FOOD SERVICE",  array(NULL=>"", "15" => "15 Grocery store bakery (Bakery in a grocery store)", "16" => "16 Restaurant, caterer or other food service (All restaurants, coffee shops and fast food)", "17" => "17 Bar", "18" => "18 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->addTextAreaElementRD('occ_insert_q8_6cother', $this->indent . 'If you selected [Other], please specify:');
		$this->XINRegisterRule("occ_insert_q8_6cother", array("occ_insert_q8_6c{@}=={@}18"), "You must specify other");
		$this->form->addElement('static', null, "<br/>");


		//occ_insert_q8_6d
		$this->form->addElement("select", "occ_insert_q8_6d", "CLEANING AND BUILDING MAINTENANCE",  array(NULL=>"", "19" => "19 Company that cleans or maintains buildings or homes, include cleaning schools, homes and hotels", "20" => "20 Clean or maintain a private home (work for one person or family only)", "21" => "21 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->addTextAreaElementRD('occ_insert_q8_6dother', $this->indent . 'If you selected [Other], please specify:');
		$this->form->addElement('static', null, "<br/>");


		//occ_insert_q8_6e
		$this->form->addElement("select", "occ_insert_q8_6e", "CHILD CARE (PRE-KINDERGARTEN)",  array(NULL=>"", "22" => "22 Child care facility", "23" => "23 Child care in caretaker's home", "24"=>"24 Child care in child's home", "25"=>"25 Other child care ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->addTextAreaElementRD('occ_insert_q8_6eother', $this->indent . 'If you selected [Other child care], please specify:');
		$this->XINRegisterRule("occ_insert_q8_6eother", array("occ_insert_q8_6e{@}=={@}25"), "You must specify other");
		$this->form->addElement('static', null, "<br/>");


		//occ_insert_q8_6f
		$this->form->addElement("select", "occ_insert_q8_6f", "BEAUTICIAN/BARBER",  array(NULL=>"", "26"=>"26 Barber shop", "27"=>"27 Beauty shop", "28"=>"28 Nail salon", "29"=>"29 Other beauty services", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->addTextAreaElementRD('occ_insert_q8_6fother', $this->indent . 'If you selected [Other beauty services], please specify:');
		$this->XINRegisterRule("occ_insert_q8_6fother", array("occ_insert_q8_6f{@}=={@}29"), "You must specify other");
		$this->form->addElement('static', null, "<br/>");


		//occ_insert_q8_6g
		$this->form->addElement("select", "occ_insert_q8_6g", "DRIVER",  array(NULL=>"", "30"=> "30 School bus driver", "31"=>"31 Other public transportation", "32"=>"32 (bus, subway, light rail, streetcar, ect.)", "33"=>"33 Taxi and limousine service", "34"=>"34 Tourism", "35"=>"35 Postal service", "36"=>"36 Couriers and messengers", "37"=>"37 Private households", "38"=>"38 Trucking", "39"=>"39 Other driving business or industry", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->addTextAreaElementRD('occ_insert_q8_6gother', $this->indent . 'If you selected [Other driving business or industry], please specify:');
		$this->XINRegisterRule("occ_insert_q8_6gother", array("occ_insert_q8_6g{@}=={@}39"), "You must specify other");
		$this->form->addElement('static', null, "<br/>");


		//occ_insert_q8_6h
		$this->form->addElement("select", "occ_insert_q8_6h", "AGRICULTURE, FARMING, LANDSCAPING, PESTICIDE WORKERS",  array(NULL=>"", "40 Agriculture/farming-crops", "41 Landscaping services and/or pest/control services", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");


		//occ_insert_q8_6i
		$this->form->addElement("select", "occ_insert_q8_6i", "OTHER INDUSTRY OR BUSINESS",  array(NULL=>"", "42"=>"42 Retail sales", "43"=>"43 Wholesale", "44"=>"44 Manufacturing", "45"=>"45 Warehousing", "46"=>"46 Information and telecommunications (includes internet)", "47"=>"47 Finance, insurance, real estate, and leasing", "48"=>"48 Professional, scientific, management, administrative, social services", "49"=>"49 Arts, entertainment and recreation (includes hotels, motels and bed and breakfasts)", "50"=>"50 Public administration", "51"=>"51 Services other than public administration (maintenance and repair, religious, dry-cleaning, funeral home, civic organizations)", "52"=>"52 Military", "53"=>"53 Construction", "54"=>"54 Airlines", "55"=>"55 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->addTextAreaElementRD('occ_insert_q8_6iother', $this->indent . 'If you selected [Other], please specify:');
		$this->XINRegisterRule("occ_insert_q8_6iother", array("occ_insert_q8_6i{@}=={@}55"), "You must specify other");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//occ_insert_q8_7
		$this->form->addElement("select", "occ_insert_q8_7", "8-7 In what kind of business or industry is this job?",  array(NULL=>"", "00_Specify" => "00 Specify", "88_Refused" => "88 Refused", "99_Do_Not_Know" => "99 Don't know", "Not_answered" => "Not Answered"));
		$this->form->addElement("textarea", "occ_insert_q8_7_specify", "<i>Probe: What does this company make or do?");
		$this->XINRegisterRule("occ_insert_q8_7_specify", array("occ_insert_q8_7{@}=={@}00_specify"), "You must specify business or industry");	
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//occ_insert_q8_8
		$this->form->addElement("select", "occ_insert_q8_8", "8-8 Now think about school, for this school/job, what best describes the place where you typically work/go to school?",  array(NULL=>"", "01" => "01 Office Area", "02" => "02 Store", "03" => "03  Classroom", "04" => "04 Hotel or Motel", "05" => "05 Restaurant", "06" => "06 Residence, such as your home or someone else's home", "07" => "07 Healthcare facility or hospital", "08" => "08 Laboratory", "09" => "09 Factory, plant or production area", "10" => "10 Warehouse", "11" => "11 Garage or shop", "12" => "12 Some other indoor location", "13" => "13 Loading dock", "14" => "14 Construction site", "15" => "15 Grounds, yard, or garden", "16" => "16 Some other outdoor location", "17" => "17 Motor vehicle", "18" => "18 Some other outdoor location", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->addTextAreaElementRD('occ_insert_q8_8other1', $this->indent . 'If you selected [12 Some other indoor location], please specify:');
		$this->XINRegisterRule("occ_insert_q8_8other1", array("occ_insert_q8_8{@}=={@}12"), "You must specify indoor location");	
		$this->addTextAreaElementRD('occ_insert_q8_8other2', $this->indent . 'If you selected [16 Some other outdoor location], please specify:');
		$this->XINRegisterRule("occ_insert_q8_8other2", array("occ_insert_q8_8{@}=={@}16"), "You must specify outdoor location");	
		$this->addTextAreaElementRD('occ_insert_q8_8other3', $this->indent . 'If you selected [18 Some other outdoor location], please specify:');
		$this->XINRegisterRule("occ_insert_q8_8other3", array("occ_insert_q8_8{@}=={@}18"), "You must specify outdoor location");	
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//occ_insert_q8_9
		$this->form->addElement('select', 'occ_insert_q8_9', "8-9 How long have you been at this job/attending this school?", array(NULL=>"", "01"=>"Years", "02"=>"Months", "03"=>"Weeks", "04"=>"Days", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->addTextAreaElementRD('occ_insert_q8_9number', $this->indent . "Enter the nummber:");
		$this->XINRegisterRule("occ_insert_q8_9number", array("occ_insert_q8_9{@}=={@}01|02|03|04"), "You must specify a number");	
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//occ_insert_q8_10
		$this->form->addElement('select', 'occ_insert_q8_10', "8-10 What is the address that you actually work at this job/attend school?", array(NULL=>"", "01" => "01 Home", "02" => "02 Varies (Construction, Landscaping)", "03" => "03  Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->addTextAreaElementRD('occ_insert_q8_10specify', $this->indent . "Enter address:");
		$this->XINRegisterRule("occ_insert_q8_10specify", array("occ_insert_q8_10{@}=={@}03"), "You must specify an address");	
		$this->form->addElement('static', null, "");
		$this->form->addElement('static', null, "<br/>");

		$timeOptions = array_combine(range(1,12), range(1,12));


		//occ_insert_q8_11
		$mToF = array("Monday"=>"Monday", "Tuesday"=>"Tuesday", "Wednesday"=>"Wednesday", "Thursday"=>"Thursday", "Friday"=>"Friday",  "Saturday"=>"Saturday",  "Sunday"=>"Sunday");

		foreach ($mToF as $field=>$label)
		{

			$this->form->addElement("select", "occ_insert_q8_11_{$field}", "<b>{$label}:</b>",  array(NULL=>"", "01"=>"1 Work Day", "02"=>"2 Not Work Day"));
			$group[] = &$this->form->createElement('select', "occ_insert_q8_11_start{$field}", null, array(NULL=> "") + ($timeOptions));
			$group[] = &$this->form->createElement('select', "occ_insert_q8_11_start{$field}_AMPM", "AM/PM", array(NULL=>"", "AM" => "AM", "PM" => "PM"));
			$group2[]= &$this->form->createElement('select', "occ_insert_q8_11_end{$field}", null, array(NULL=>"") + ($timeOptions));
			$group2[]= &$this->form->createElement('select', "occ_insert_q8_11_end{$field}_AMPM", "AM/PM", array(NULL=>"", "AM" => "AM", "PM" => "PM"));
			 $this->form->addGroup($group, "occ_insert_q8_11_{$field}_group", $this->indent . "Start time:", $this->_GUIDelimiter, false);
			 $this->form->addGroup($group2, "occ_insert_q8_11_{$field}_group2", $this->indent . "End time:", $this->_GUIDelimiter, false);
                        unset($group);
			unset($group2);

			$this->XINRegisterRule("occ_insert_q8_11_start{$field}", array("occ_insert_q8_11_{$field}{@}=={@}01"), "You must specify a start time");	
			$this->XINRegisterRule("occ_insert_q8_11_start{$field}_AMPM", array("occ_insert_q8_11_{$field}{@}=={@}03"), "You must specify start time of day");	
			$this->XINRegisterRule("occ_insert_q8_11_end{$field}", array("occ_insert_q8_11_{$field}{@}=={@}03"), "You must specify an end time");	
			$this->XINRegisterRule("occ_insert_q8_10_end{$field}_AMPM", array("occ_insert_q8_11_{$field}{@}=={@}03"), "You must specify end time of day");	
		
		}


                        //Don't require all questions, but allow them to be filled in, if desired.
//                        if ($label=="a") continue; //Special rules apply to the first month
  //                      $this->XINRegisterRule("q5_60_m_{$label}", array("q5_58{@}=={@}NEVER_REQUIRED"));
    //                    $this->XINRegisterRule("q5_60_f_{$label}", array("q5_58{@}=={@}NEVER_REQUIRED"));


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//occ_insert_q8_12
		$this->form->addElement("select", "occ_insert_q8_12", "8-12 Was your drinking water source at this school/at that school usually...",  array(NULL=>"", "01" => "01 Tap water", "02" => "02 Filtered tap water", "03" => "03 Bottled water", "04" => "04 Some other source?", "05" => "05 Don't drink water at work", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->addTextAreaElementRD('occ_insert_q8_12other', $this->indent . 'If you selected [Some other source?], please specify:');
		$this->XINRegisterRule("occ_insert_q8_12other", array("occ_insert_q8_12{@}=={@}04"), "You must specify other");	
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

	} //end function _page38() ===============================================
*/

} //end EARLI Maternal Interview part 3 =================================================

?>
