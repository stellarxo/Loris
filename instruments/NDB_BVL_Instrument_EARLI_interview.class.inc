<?php


require_once("RequiredIfGroup.inc");
require_once('RequiredIf.inc');

class NDB_BVL_Instrument_EARLI_interview extends NDB_BVL_Instrument {

	var $scoreLabels = array("activity_level"=>"Activity Level",
	"distress_to_limitations"=>"Distress to Limitations",
	"fear"=>"Fear",
	"duration_of_orienting"=>"Duration of Orienting",
	"smiling_and_laughter"=>"Smiling and Laughter",
	"high_pleasure"=>"High Pleasure",
	"low_pleasure"=>"Low Pleasure",
	"soothability"=>"Soothability",
	"falling_reactivity"=>"Falling Reactivity", ///Rate of Recovery from Distress",
	"cuddliness"=>"Cuddliness",
	"perceptual_sensitivity"=>"Perceptual Sensitivity",
	"sadness"=>"Sadness",
	"approach"=>"Approach",
	"vocal_reactivity"=>"Vocal Reactivity");

	//define on a per page basis, as needed
	var $dateOptions = array();

	//number arrays
	//	var $negThreeToNine = array();

	var $negThreeToNineComplete = array();
	var $negThreeToTenComplete = array();
	var $oneToSeventyComplete = array();

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
		$this->page = $page;            // page label (number or
		// string - used by
		// user-defined child classes)

		// set the object properties
		$this->testName = "EARLI_interview";           // test_names.Test_name
		$this->table = 'EARLI_interview';              // name of table containing
		// data keyed by commentID
		$this->commentID = $commentID;

		//The array of dates/timestamps to convert to database dates/timestamps
		$this->dateTimeFields=array("Date_taken", "q1_1", "q1_4_specify", "q1_16_specify", "q1_19_specify", "q2_8_date", "q2_14_date", "q2_17_date", "q2_17a_date", "q2_19_date", "q2_22_date", "q2_24_date", "q2_26_date", "q2_28_date", "q2_39_date_1", "q2_39_date_2", "q4a_2", "q4a_5", "q4_41_date", "q4_44_date", "q5_1_date", "q5_42_date", "q5_45_date", "q5_49_date", "q5_52_date", "q5_57_date");

		//GLOBAL DEFINITIONS

		//date formats
		$config =& NDB_Config::singleton();
		$this->dateOptions = array(
		'language' => 'en',
		'format'   => 'YMd',
		'minYear'  => $config->getSetting('startYear') - 57, //allows for proband siblings up to 20 years older than candidate
		'maxYear'  => $config->getSetting('endYear'),
		'addEmptyOption' => true,
		'emptyOptionValue' => null
		);

		//number arrays
		$negThreeToNine1 = array_combine(range(-3, 9), range(-3, 9));
		unset($negThreeToNine1[0]);
		$this->negThreeToNineComplete = array(null=>"") + ($negThreeToNine1) + array("88_Refused" => "88 Refused", "99_Do_not_know" => "99 Do not know", "not_answered" => "Not Answered");


		$negThreeToTen = array_combine(range(-3, 10), range(-3, 10));
		unset($negThreeToTen[0]);
		$this->negThreeToTenComplete = array(null=>"") + ($negThreeToTen) + array("88_Refused" => "88 Refused", "99_Do_not_know" => "99 Do not know", "not_answered" => "Not Answered");
		
		
        $oneToSeventy = array_combine(range(1, 70), range(1, 70));
		$this->oneToSeventyComplete = array(null=>"") + ($oneToSeventy) + array("88_Refused" => "88 Refused", "99_Do_not_know" => "99 Do not know", "not_answered" => "Not Answered");


		// setup the form

		$this->_setupForm();
		
		
        
		$this->localDefaults = array();


		$this->_selectMultipleElements = array();

		// From Mr. David Brownlee:
		//The array of selects with multiple answers allowed
		//Any HTML_Quickform multiple selects must be listed here
		//Usually this appears at the beginning of the file in the setup() function
		$this->_selectMultipleElements = array_merge($this->_selectMultipleElements, array('q5_33', "q5_36", "q5_39"));

		//column headers
		//Usually this appears at the beginning of the file in the setup() function
		$this->localDefaults = array_merge($this->localDefaults, array("month_header"=>"MONTH #", "freq_header"=>"FREQ"));

	}

	/**
    * method to build the HTML_Quickform object into a paged form
    *
    * @return void
    * @access private
    */
	function _setupForm()
	{
		$this->answer_options=array(NULL=>'', '1'=>'1', '2'=>'2', '3'=>'3', '4'=>'4', '5'=>'5', '6'=>'6', '7'=>'7', 'does_not_apply'=>'Does not apply', 'not_answered'=>'Not Answered');

		// Mr. Samir's Rule
		// Register the RequiredIf quickform rule
		$this->form->registerRule('requiredIfGroup', null, 'HTML_QuickForm_Rule_RequiredIfGroup', 'RequiredIfGroup.inc');
		$this->form->registerRule('requiredIf', null, 'HTML_QuickForm_Rule_RequiredIf', 'RequiredIf.inc');
		//$this->form->addFormRule(array(&$this,'XINValidate'));


		if(ereg("(_page[0-9]+)", $this->page, $matches)) {
			call_user_method($matches[1], &$this);

		} else {
			$this->_main();
		}

	}

	function _main(){


		// display test name
		$this->form->addElement('header', 'instrument_title', "Infant Behavior Questionnaire - Revised (IBQ-R)");

		// add examiner & date of administration
		$this->_addMetadataFields();

		$this->form->addElement('header', null, 'Calculate Scores');

		//score headers
		$this->form->addElement('static', "scale", "Scale");

		//score columns
		foreach($this->scoreLabels as $field=>$label) {
			$this->form->addElement('static', $field, $label);
		}
		//calculate subscales

		// Mr. Samir's Rule
		// Register the RequiredIf quickform rule
		$this->form->registerRule('requiredIfGroup', null, 'HTML_QuickForm_Rule_RequiredIfGroup', 'RequiredIfGroup.inc');
		$this->form->registerRule('requiredIf', null, 'HTML_QuickForm_Rule_RequiredIf', 'RequiredIf.inc');




	}

	function _page1(){   // ========================================================


		// To implement Xin Rule

		$this->form->addFormRule(array(&$this,'XINValidate'));

		// To implement date

		$config =& NDB_Config::singleton();

		$dateOptionsYears = array(
		'language' => 'en',
		'format'   => 'Y',
		'minYear'  => $config->getSetting('startYear'), //allows for siblings up to 20 years older than candidate
		'maxYear'  => $config->getSetting('endYear'),
		'addEmptyOption' => true,
		'emptyOptionValue' => null
		);
		$dateOptionsMy = array( //dateOptionsYM as better name
		'language' => 'en',
		'format'   => 'YM',
		'minYear'  => $config->getSetting('startYear'), //allows for siblings up to 20 years older than candidate
		'maxYear'  => $config->getSetting('endYear'),
		'addEmptyOption' => true,
		'emptyOptionValue' => null
		);

		$dateOptionsOld = array(
		'language' => 'en',
		'format'   => 'Y',
		'minYear'  => '1900', //allows for siblings up to 20 years older than candidate
		'maxYear'  => $config->getSetting('endYear'),
		'addEmptyOption' => true,
		'emptyOptionValue' => null
		);


		$dateOptionsOldMY = array(
		'language' => 'en',
		'format'   => 'YM',
		'minYear'  => '1900', //allows for siblings up to 20 years older than candidate
		'maxYear'  => $config->getSetting('endYear'),
		'addEmptyOption' => true,
		'emptyOptionValue' => null
		);


		$this->form->addElement('header', null, "Section 1. DEMOGRAPHIC INFORMATION");
		$this->form->addElement('static', null, "<b>I would like to begin by confirming your birthday.</b>");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('date', 'q1_1', "1-1) What is your date of birth?", $dateOptionsOld);
		$this->setRequired('q1_1');
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q1_2", "1-2) How old are you today? (Years)" ,array(NULL=>"", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "36", "37", "38", "39", "40", "41", "42", "43", "44", "45", "46", "47", "48", "49", "50", "51", "52", "53", "54", "55", "56", "57", "58", "59", "60", "61", "62", "63", "64", "65", "66", "67", "68", "69", "70", "Not_Answered" => "Not Answered"));

		$this->setRequired('q1_2');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b>Now I'd like to ask about your background.</b>");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('select', 'q1_3', "1-3) Where were you born?", array(NULL=>"","01_US" => "01 U.S.", "02_Outside_US" => "02 Outside U.S.", "88_Refused" => "88 Refused", "99_Do_not_know" => "99 Do not know", "Not_Answered" => "Not Answered"));

		$this->setRequired('q1_3');

		$this->form->addElement('textarea', 'q1_3_US_State', $this->indent . "If [U.S.] please specify state:");
		$this->form->addElement('static', null, $this->indent . "If [U.S.], skip to question 1-5");
		$this->form->addRule(array("q1_3_US_State", "q1_3"), 'Please specify state.', 'requiredIf', array("operator"=>"==", "value"=>"01_US"));
		$this->setRequired('q1_3_US_State');


		$this->form->addElement('textarea', 'q1_3_Outside_US', $this->indent . "If [Outside U.S.] please specify country:");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addRule(array('q1_3_Outside_US', 'q1_3'), 'Please specify country.', 'requiredIf', array("operator"=>"==", "value"=>"02_Outside_US"));
		$this->setRequired('q1_3_Outside_US');

		$this->form->addElement("select", "q1_4", "1-4) When did you come to live in the United States?",array(NULL=>"", "specify" => "00 Specify", "88_Refused" => "88 Refused", "99" => "99 Do not know", "Not_Answered" => "Not Answered"));	$this->form->addRule(array('q1_4', 'q1_3'), 'q1-4 is required', 'requiredIf', array('operator'=>'!=', 'value'=>'01_US'));
		$this->setRequired('q1_4');
		$this->form->addElement('date', 'q1_4_specify', "If [00 Specify], please specify the year:", $dateOptionsOld);

		$this->form->addRule(array('q1_4_specify', 'q1_4'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'specify'));
		$this->setRequired('q1_4_specify');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q1_5", "1-5) What language do you speak at home?", array(NULL=>"", "01_English" => "01 English", "02" => "02  Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, $this->indent . "If [English], skip to question 1-7");
		$this->setRequired('q1_5');
		$this->form->addElement('textarea', 'q1_5_Other', $this->indent . "If [Other] please specify:");
		$this->form->addRule(array('q1_5_Other', 'q1_5'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'02'));
		$this->setRequired('q1_5_Other');

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q1_6", "1-6) How well do you speak English?", array(NULL=>"", "01" => "01 Very well", "02" => "02  Well", "03" => "03  Not well", "04" => "04 Not at all", "88 Refused", "99" => "99 Do not know"));

		$this->form->addRule(array('q1_6', 'q1_5'), 'q1-6 is required', 'requiredIf', array('operator'=>'!=', 'value'=>'01_English'));
		$this->setRequired('q1_6');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('select', 'q1_7', "1-7) What is your primary ethnicity?", array(NULL=>"", "01" => "01 Hispanic or Latino", "02" => "02  Not Hispanic or Latino", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->setRequired('q1_7');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [02 Not Hispanic or Latino] skip to question 1-9");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('select', 'q1_8', "1-8) Of which Hispanic or Spanish group do you consider yourself a member? ", array(NULL=>"", "01" => "01 Mexican, Mexican American, Chicano
", "02" => "02  Puerto Rican ", "03" => "03  Cuban", "04" => "04 Other Spanish / Hispanic/
Latino ", "88 Refused", "99" => "99 Do not know"));

		$this->form->addRule(array('q1_8', 'q1_7'), 'q1-8 is required', 'requiredIf', array('operator'=>'!=', 'value'=>'02'));
		$this->setRequired('q1_8');

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q1_9", "1-9) What is your race?", array(NULL=>"", "01" => "01 White
", "02" => "02 Black, African American
", "03" => "03 American Indian / Alaskan Native Asian", "04" => "04 Asian Indian", "05" => "05 Chinese", "06" => "06 Filipino", "07" => "07 Japanese", "08" => "08 Korean", "02" => "09 Vietnamese", "10" => "10 Thai / Cambodian", "11" => "11 Other Asian Native Hawaiian/Pacific Islander",  "12" => "12 Native Hawaiian",  "13" => "13 Guamanian or Chamorro" ,  "14" => "14 Samoan",  "15" => "15 Other Pacific Islander",  "16" => "16 Other race", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->setRequired('q1_9');


		$this->form->addElement('textarea', 'q1_9_Other', $this->indent . "If [Other race] please speciy");
		$this->form->addRule(array('q1_9_Other', 'q1_9'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'16'));
		$this->setRequired('q1_9_Other');        $this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q1_10", "1-10 What is the highest degree or level of education you have completed?", array(NULL=>"", "01" => "01 No formal schooling completed", "02 " => "02 Nursery school to 4th grade", "03 " => "03 5th grade or 6th grade", "04" => "04 7th grade or 8th grade", "05" => "05 9th grade", "06" => "06 10th grade", "07" => "07 11th grade", "08" => "08 12th grade, no diploma", "09" => "09 High school graduate - high school diploma or equivalent (e.g., GED)", "10" => "10 Some college credit, but less than 1 year", "11" => "11 One or more years of college, no degree", "12" => "12 Technical college / vocational school", "13" => "13 Associate degree (e.g., AA, AS)", "14" => "14 Bachelor's degree (e.g., BA, AB, BS)", "15" => "15 Master's degree (e.g., MA, MS, MEng, Med, MSW, MBA)", "16" => "16 Professional degree (e.g., MD, DDS, DVM, LLB, JD)", "17" => "17 Doctorate degree (e.g., PhD, EdD)", "88" => "88 Refused", "99" => "99 Do not know"));

		$this->setRequired('q1_10');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q1_11", "1-11) In the year you were pregnant with your child with ASD, what was your estimated total household income before taxes? Would you say it was...", array(NULL=>"", "01" => "01 Below $10,000", "02" => "02 $10,000 to $19,999", "03" => "03 $20,000 to $29,999", "04" => "04 $30,000 to $49,000", "05" => "05 $50,000 to $74,999", "06" => "06 $75,000 to $99,999", "07 $100,000 to $199,999", "08 $200,000 or more ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->setRequired('q1_11');

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q1_12", "1-12) At that time, how many people were supported by that income, including both
adults and children?" ,array(NULL=>"", "0","1", "2", "3", "4", "5", "6", "7", "8", "9","10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered" => "Not Answered"));

		$this->setRequired('q1_12');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q1_13", "1-13) What was your estimated total household income for the last 12 months before
taxes? Would you say it was...", array(NULL=>"", "01" => "01 less than $10,000", " 02 $10,000 to $19,999", "03" => "03 $20,000 to $29,999", "04" => "04 30,000 to $49,000", "05" => "05 $50,000 to $74,999", "06" => "06 $75,000 to $99,999", "07" => "07 100,000 to $199,999", "08" => "08 $200,000 or more ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->setRequired('q1_13');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q1_14", "1-14) How many people are supported by this income, including both adults and
children?", array(NULL=>"",  "0","1", "2", "3", "4", "5", "6", "7", "8", "9","10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->setRequired('q1_14');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q1_15", "1-15) Are you now married, widowed, divorced, separated, never married, or living
with a partner?", array(NULL=>"", "01" => "01 Now married", "02" => "02  Widowed", "03" => "03  Divorced", "04" => "04 Separated", "05" => "05 Never married", "06" => "06 Living with a partner ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->setRequired('q1_15');
		$this->form->addElement('static', null, "<br/><b>The next few questions are about the biological father for last pregnancy (sibling of child with
ASD).");  

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q1_15a", "1_15a) Is biological father for last pregnancy (sibling of child with ASD) known?", array(NULL=>"", "01_yes" => "01 Yes", "02_no" => "02 No"));
		$this->setRequired('q1_15a');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b>If biological father for last pregnancy (sibling of child with ASD) is unknown, skip to Section 2 - Maternal Medical History.");

		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q1_16_select", "1-16)  What is the biological father's birth date?", array(NULL=>"", "00" => "00 Specify", "a" => "88/88/8888 Refused", "b" => "99/99/9999 Do not know", "Not_Answered" => "Not Answered"));
		$this->setRequired('q1_16_select');
		$this->form->addElement('date', 'q1_16_specify', "If [00 Specify], please specify the year:", $dateOptionsOld);

		$this->form->addRule(array('q1_16_specify', 'q1_16_select'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'00'));
		$this->setRequired('q1_16_specify');

		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q1_17", "1-17) How old is he today? (Years)" , $oneToSeventyComplete);

		$this->setRequired('q1_17');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('select', 'q1_18', "1-18) Where was he born?", array(NULL=>"", "01" => "01 US", "02" => "02 Outside US", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->setRequired('q1_18');

		$this->form->addElement('textarea', 'q1_18_US_State', $this->indent . "If [U.S.] please specify state:");
		$this->form->addElement('static', null, $this->indent . "If [U.S.], skip to question 1-21");

		$this->form->addRule(array('q1_18_US_State', 'q1_18'), 'Please specify state.', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q1_18_US_State');

		$this->form->addElement('textarea', 'q1_18_Outside_US', $this->indent . "If [Outside U.S.] please specify country:");
		$this->form->addRule(array('q1_18_Outside_US', 'q1_18'), 'Please specify country.', 'requiredIf', array('operator'=>'==', 'value'=>'02'));
		$this->setRequired('q1_18_Outside_US');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q1_19", "1-19) When did he come to live in the United States?", array(NULL=>"",  "00" => "00 Specify", "a" => "8888 Refused", "b" => "9999 Do not know", "Not_Answered" => "Not Answered"));


		$this->form->addRule(array('q1_19', 'q1_18'), 'q1-19 is required', 'requiredIf', array('operator'=>'!=', 'value'=>'01'));
		$this->setRequired('q1_19');

		$this->form->addElement('date', 'q1_19_specify', "If [00 Specify], please specify the year:", $dateOptionsOld);

		$this->form->addRule(array('q1_19_specify', 'q1_19'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'00'));
		$this->setRequired('q1_19_specify');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q1_20", "1-20) What language does he usually speak at home?<br/> $this->indent If [English], skip to question 1-22",array(NULL=>"", "01" => "01 English", "02" => "02 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addElement('textarea', 'q1_20_Other', $this->indent . "If [Other] please specify:");

		$this->form->addRule(array('q1_20_Other', 'q1_20'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'02'));
		$this->setRequired('q1_20_Other');


		$this->form->addRule(array('q1_20', 'q1_18'), 'q1-20 is required', 'requiredIf', array('operator'=>'!=', 'value'=>'01 US'));
		$this->setRequired('q1_20');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q1_21", "1-21) How well does he speak English?", array(NULL=>"", "01" => "01 Very well", "02" => "02 Well", "03" => "03  Not well", "04" => "04 Not at all ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addRule(array('q1_21', 'q1_20'), 'q1-21 is required', 'requiredIf', array('operator'=>'!=', 'value'=>'01'));
		$this->setRequired('q1_21');


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q1_22", "1-22) What is his primary ethnicity?", array(NULL=>"", "01" => "01 Hispanic or Latino", "02" => "02 Not Hispanic or Latino", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->setRequired('q1_22');
		$this->form->addElement('static', null,  $this->indent . "If [Not Hispanic or Latino], skip to question 1-24");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q1_23", "1-23) Of which Hispanic or Spanish group does he consider himself a member?", array(NULL=>"", "01" => "01 Mexican, Mexican American, Chicano", "02" => "02 Puerto Rican", "03" => "03  Cuban", "04" => "04 Other Spanish / Hispanic/Latino ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addRule(array('q1_23', 'q1_22'), 'q1-23 is required', 'requiredIf', array('operator'=>'!=', 'value'=>'02'));
		$this->setRequired('q1_23');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q1_24", "1-24) What is his race?", array(NULL=>"", "01" => "01 White", "02" => "02 Black, African American", "03" => "03  American Indian / Alaskan Native", "04" => "04 Asian Indian", "05" => "05 Chinese", "06" => "06 Filipino", "07 Japanese", "08" => "08 Korean", "09" => "09 Vietnamese", "10" => "10 Thai / Cambodian", "11" => "11 Other Asian", "12" => "12 Native Hawaiian", "13" => "13 Guamanian or Chamorro", "14" => "14 Samoan", "15" => "15 Other Pacific Islander", "16 Other race (specify): ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->setRequired('q1_24');


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q1_25", "1-25) What is the highest degree or level of education he has completed?", array(NULL=>"", "01" => "01 No formal schooling completed", "02" => "02 Nursery school to 4th grade", "03" => "03  5th grade or 6th grade", "04" => "04 7th grade or 8th grade", "05" => "05 9th grade", "06" => "06 10th grade", "07 11th grade", "08" => "08 12th grade, no diploma", "09" => "09 High school graduate - high school diploma or equivalent (e.g., GED)", "10" => "10 Some college credit, but less than 1 year", "11" => "11 One or more years of college, no degree", "12" => "12 Technical college / vocational school", "13" => "13 Associate degree (e.g., AA, AS)", "14" => "14 Bachelor's degree (e.g., BA, AB, BS)", "15" => "15 Master's degree (e.g., MA, MS, MEng, Med, MSW, MBA)", "16 Professional degree (e.g., MD, DDS, DVM, LLB, JD)", "17 Doctorate degree (e.g., PhD, EdD) ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->setRequired('q1_25');
	}



	function _page2(){   // ========================================================


		// To implement Xin Rule

		$this->form->addFormRule(array(&$this,'XINValidate'));
		// To implement date


		$config =& NDB_Config::singleton();

		$dateOptions = array(
		'language' => 'en',
		'format'   => 'YMd',
		'minYear'  => $config->getSetting('startYear'), //allows for siblings up to 20 years older than candidate
		'maxYear'  => $config->getSetting('endYear'),
		'addEmptyOption' => true,
		'emptyOptionValue' => null
		);
		$dateOptionsYears = array(
		'language' => 'en',
		'format'   => 'Y',
		'minYear'  => $config->getSetting('startYear'), //allows for siblings up to 20 years older than candidate
		'maxYear'  => $config->getSetting('endYear'),
		'addEmptyOption' => true,
		'emptyOptionValue' => null
		);
		$dateOptionsMy = array(
		'language' => 'en',
		'format'   => 'YM',
		'minYear'  => $config->getSetting('startYear'), //allows for siblings up to 20 years older than candidate
		'maxYear'  => $config->getSetting('endYear'),
		'addEmptyOption' => true,
		'emptyOptionValue' => null
		);

		$dateOptionsOldMY = array(
		'language' => 'en',
		'format'   => 'YM',
		'minYear'  => '1900', //allows for siblings up to 20 years older than candidate
		'maxYear'  => $config->getSetting('endYear'),
		'addEmptyOption' => true,
		'emptyOptionValue' => null
		);


		$this->form->addElement('header', null, "Section 2. MATERNAL MEDICAL HISTORY");
		$this->form->addElement('static', null, "Now I'm going to ask you about your birth.");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q2_1", "2-1) Were you born prematurely, that is more than 3 weeks early?", array(NULL=>"", "01" => "01 Yes ", "02_no" => "02 No", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null,  $this->indent . "If [Yes], go to question 2-2");
		$this->form->addElement('static', null,  $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 2-3");

		$this->setRequired('q2_1');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q2_2", "2-2) How many weeks early were you born?", array(NULL=>"",  "0","1", "2", "3", "4", "5", "6", "7", "8", "9","10","88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addRule(array('q2_2', 'q2_1'), 'q2-2 is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q2_2');

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q2_3", "2-3) What was your birth weight?", array(NULL=>"", "01" => "01 Grams", "02" => "02 Pounds/Ounces", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addElement('textarea', 'q2_3_grams', $this->indent . "If [Grams] please specify the weight (in digits):");
		$this->form->addElement('static', null, $this->indent . "If [Pounds/Ounces] please specify the weight (in digits):");
		$this->form->addElement('textarea', 'q2_3_p', $this->indent . $this->indent . "Pounds:");
		$this->form->addElement('textarea', 'q2_3_o', $this->indent . $this->indent . "Ounces:");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Grams] or [Pounds/Ounces] or [Refused] skip to question 2-5");
		$this->form->addElement('static', null, $this->indent . "If [Don't Know] go to question 2-4");
		$this->setRequired('q2_3');

		$this->form->addElement('static', null, "<br/>");



		//****************************************************************************Weight (idea/code taken from Angela's code - Med-Pscyh-Data_Extraction)

		$measurement2 = "Weight";

		$this->form->addElement('static', null, "<b>$measurement2 Measurement <BR></b>");
		$this->form->addElement('static', null, $noted_message_units_weight);


		$this->form->addElement('select',"{$field}_measurement_weight_units_stat", "$this->double_indent $measurement2 Units", array(null=>"", "grams"=>"grams","ounces"=>"ounces", "not_answered"=>"Not Answered"));

		$this->XINRegisterRule("{$field}_measurement_weight_units_stat", array("{$prevField}_chart{@}!={@}no_more_chart_data", "{$prevField}_chart{@}!={@}"), "These fields are required unless not answered is selected");

		//Add text boxes
		$this->form->addElement('text', "{$field}_measurement_weight_$units_weight[0]", "$this->double_indent $units_weight[0]");
		$this->form->addElement('text', "{$field}_measurement_weight_$units_weight[1]", "$this->double_indent $units_weight[1]");


		$this->XINRegisterRule("{$field}_measurement_weight_$units_weight[0]", array("{$field}_measurement_weight_units_stat{@}=={@}grams", "{$prevField}_chart{@}!={@}no_more_chart_data"), "Please enter grams");
		$this->XINRegisterRule("{$field}_measurement_weight_$units_weight[1]", array("{$field}_measurement_weight_units_stat{@}=={@}ounces", "{$prevField}_chart{@}!={@}no_more_chart_data"), "Please enter ounces");


		$this->form->addElement('text', "{$field}_weight_percentage", "$this->double_indent Percentile");

		$this->XINRegisterRule("{$field}_weight_percentage", array("{$field}_measurement_weight_units_stat{@}!={@}not_answered", "{$field}_measurement_weight_units_stat{@}!={@}"), "Please enter a percentile");


		if($result["{$field}_measurement_weight_units_stat"] == "grams"){
			$grams_value = $result["{$field}_measurement_weight_grams"];
			$newValues["{$field}_measurement_weight_ounces"] = (28.35)*$grams_value;
		}
		else if($result["{$field}_measurement_weight_units_stat"] == "ounces"){
			$ounces_value = $result["{$field}_measurement_weight_ounces"];
			$newValues["{$field}_measurement_weight_grams"] = (0.0353)*$ounces_value;
		}

		else{
			$newValues["{$field}_measurement_weight_ounces"] = NULL;
			$newValues["{$field}_measurement_weight_grams"] = NULL;

		}
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//****************************************************************************end



		$this->form->addElement("select", "q2_4", "2-4) Was it less than 5 pounds, 8 ounces (2500 grams) or 5 pounds, 8 ounces
(2500 grams) or more?", array(NULL=>"", "01" => "01 Less than 5 pounds, 8 ounces (2500 g)", "02" => "02 5 pounds, 8 ounces (2500 g) or more ", "88 Refused", "99" => "99 Do not know") );
		$this->setRequired('q2_4');


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q2_5", "2-5) Were you a twin or triplet?", array(NULL=>"", "01" => "01 No, singleton", "02" => "02 Yes, twin", "03" => "03  Yes, triplet", "04" => "04 Yes, other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->setRequired('q2_5');

		$this->form->addElement('textarea', 'q2_5_text', $this->indent . "If [04 Yes, other], please specify:");
		$this->form->addRule(array('q2_5_text', 'q2_5'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'04'));
		$this->setRequired('q2_5_text');


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b>These next questions are about your health before your last pregnancy (with sibling of child
with ASD).");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q2_6", "2-6) Before your pregnancy with [SIBLING], were you ever told by a doctor that you
had diabetes, including gestational diabetes that happens only while you're
pregnant?", array(NULL=>"", "01_yes" => "01 Yes", "02_no" => "02 No", "88 Refused", "99" => "99 Do not know"));

		$this->form->addElement('static', null, $this->indent . "If [Yes], go to question 2-7");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 2-13");
		$this->setRequired('q2_6');


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q2_7", "2-7) What type of diabetes did you have? Was it... [read list]", array(NULL=>"", "01" => "01 Gestational diabetes", "02" => "02 Insulin-dependent diabetes, also called Type I or Juvenile Onset", "03" => "03  Non-insulin dependent diabetes, also called Type II or Adult Onset ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addRule(array('q2_7', 'q2_6'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q2_7');


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q2_8", "2-8) When were you first diagnosed with diabetes?", array(NULL=>"", "01" => "01 Specify Date", "02" => "02 Specify Age ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));


		$this->form->addRule(array('q2_8', 'q2_6'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q2_8');


		$this->form->addElement('date', 'q2_8_date', 'If [01 Specify Date], please specify the ate:', $dateOptionsMy);
		$this->form->addRule(array('q2_8_date', 'q2_8'), 'This field is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q2_8_date');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q2_8_age", "If [02 Age], please specify the age (in years):" ,array(NULL=>"", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21" => "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "36", "37", "38", "39", "40", "41", "42", "43", "44", "45", "46", "47", "48", "49", "50", "51", "52", "53", "54", "55", "56", "57", "58", "59", "60", "61", "62", "63", "64", "65", "66", "67", "68", "69", "70"));

		$this->form->addRule(array('q2_8_age', 'q2_8'), 'This field is required', 'requiredIf', array('operator'=>'==', 'value'=>'02'));
		$this->setRequired('q2_8_age');




		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q2_9", "2-9) Did you ever take oral medications or remedies for your diabetes?", array(NULL=>"", "01_yes" => "01 Yes", "02_no" => "02 No", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addRule(array('q2_9', 'q2_6'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q2_9');
		$this->form->addElement('textarea', 'q2_9_text', $this->indent . "If [Yes], please specify:");
		$this->form->addRule(array('q2_9_text', 'q2_9'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q2_9_text');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q2_10", "2-10) Did you ever take insulin?", array(NULL=>"", "01_yes" => "01 Yes", "02_no" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered")
		);
		$this->form->addElement('static', null, $this->indent . "If [Yes], go to question 2-11");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 2-12");
		$this->form->addRule(array('q2_10', 'q2_6'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q2_10');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q2_11", "2-11) Have you been taking insulin continuously since that time?", array(NULL=>"", "01_yes" => "01 Yes", "02_no" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addRule(array('q2_11', 'q2_6'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q2_11');

		$this->form->addRule(array('q2_11', 'q2_10'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q2_11');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q2_12", "2-12) Did you ever take any medications other than insulin for diabetes or its
complications?", array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered")
		);
		$this->form->addRule(array('q2_12', 'q2_6'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q2_12');


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q2_13", "2-13) Before your pregnancy with [SIBLING], were you ever told by a doctor that you
had high blood pressure?", array(NULL=>"", "01_yes" => "01 Yes", "02_no" => "02 No", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, $this->indent . "If [Yes], go to question 2-14");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 2-16");
		$this->setRequired('q2_13');


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q2_14", "2-14) When were you first told by a doctor that you had high blood pressure?", array(NULL=>"", "01" => "01 Date", "02" => "02 Age ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addRule(array('q2_14', 'q2_13'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q2_14');

		$this->form->addElement('date', 'q2_14_date', 'If [01 Date], please specify:', $dateOptionsMy);

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q2_14_age", "If [02 Age], please specify (Years):" ,array(NULL=>"", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21" => "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "36", "37", "38", "39", "40", "41", "42", "43", "44", "45", "46", "47", "48", "49", "50", "51", "52", "53", "54", "55", "56", "57", "58", "59", "60", "61", "62", "63", "64", "65", "66", "67", "68", "69", "70"));




		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q2_15", "2-15) Did you ever take oral medications or remedies for your high blood pressure?", array(NULL=>"", "01_yes" => "01 Yes", "02_no" => "02 No", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->setRequired('q2_15');
		$this->form->addElement('textarea', 'q2_15_text', $this->indent . "If [Yes], please specify:");
		$this->form->addRule(array('q2_15_text', 'q2_15'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'01'));

		$this->setRequired('q2_15_text');      // ******************

		$this->form->addRule(array('q2_15', 'q2_13'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));

		$this->setRequired('q2_15');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q2_16", "2-16) Did you ever have seizures that were not related to fever?", array(NULL=>"", "01_yes" => "01 Yes", "02_no" => "02 No", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, $this->indent . "If [Yes], go to question 2-17");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 2-18");
		$this->setRequired('q2_16');


		$this->form->addElement('static', null, $this->indent . "If [Yes], go to question 2-17");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 2-18");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q2_17", "2-17) When did these seizures start?", array(NULL=>"",  "01" => "01 Date", "02" => "02 Age ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addRule(array('q2_17', 'q2_16'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q2_17');

		$this->form->addElement('date', 'q2_17_date', 'If [01 Date], please specify:', $dateOptionsMy);

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q2_17_age", "If [02 Age], please specify (Years):" ,array(NULL=>"", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21" => "21", "22", "23" => "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "36", "37", "38", "39", "40", "41", "42", "43", "44", "45", "46", "47", "48", "49", "50", "51", "52", "53", "54", "55", "56", "57", "58", "59", "60", "61", "62", "63", "64", "65", "66", "67", "68", "69", "70"));


		$this->form->addRule(array('q2_17_date', 'q2_17'), 'Please specify', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q2_17_date');
		$this->form->addRule(array('q2_17_age', 'q2_17'), 'Please specify', 'requiredIf', array('operator'=>'==', 'value'=>'02'));
		$this->setRequired('q2_17_age');



		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q2_17_a", "2-17-a) When was the most recent episode?", array(NULL=>"",  "01" => "01 Date", "02" => "02 Age ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addRule(array('q2_17a', 'q2_16'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q2_17a');



		$this->form->addElement('date', 'q2_17a_date', 'If [01 Date], please specify:', $dateOptionsMy);

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q2_17a_age", "If [02 Age], please specify (Years):" ,array(NULL=>"", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21" => "21", "22", "23" => "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "36", "37", "38", "39", "40", "41", "42", "43", "44", "45", "46", "47", "48", "49", "50", "51", "52", "53", "54", "55", "56", "57", "58", "59", "60", "61", "62", "63", "64", "65", "66", "67", "68", "69", "70"));



		$this->form->addRule(array('q2_17a_date', 'q2_17a'), 'Please specify', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q2_17a_date');
		$this->form->addRule(array('q2_17a_age', 'q2_17a'), 'Please specify', 'requiredIf', array('operator'=>'==', 'value'=>'02'));
		$this->setRequired('q2_17a_age');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q2_18", "2-18) Before your pregnancy with [SIBLING], were you ever told by a doctor that you
had epilepsy?", array(NULL=>"", "01_yes" => "01 Yes", "02_no" => "02 No", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, $this->indent . "If [Yes], go to question 2-19");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 2-21");

		$this->setRequired('q2_18');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q2_19", "2-19) When were you first told by a doctor that you had epilepsy?", array(NULL=>"",  "01" => "01 Date", "02" => "02 Age ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addRule(array('q2_19', 'q2_18'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q2_19');

		$this->form->addElement('date', 'q2_19_date', 'If [01 Date], please specify:', $dateOptionsMy);

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q2_19_age", "If [02 Age], please specify (Years):" ,array(NULL=>"", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21" => "21", "22", "23" => "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "36", "37", "38", "39", "40", "41", "42", "43", "44", "45", "46", "47", "48", "49", "50", "51", "52", "53", "54", "55", "56", "57", "58", "59", "60", "61", "62", "63", "64", "65", "66", "67", "68", "69", "70"));


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q2_20", "2-20) Did you take any medications or remedies for epilepsy or seizures?", array(NULL=>"", "01_yes" => "01 Yes", "02_no" => "02 No", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('textarea', 'q2_20_text', $this->indent . "If [Yes], please specify:");
		$this->form->addRule(array('q2_20_text', 'q2_20'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q2_20_text');      // ******************
		$this->form->addRule(array('q2_20', 'q2_18'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q2_20');



	}

	function _page3(){   // ========================================================


		// To implement Xin Rule

		$this->form->addFormRule(array(&$this,'XINValidate'));


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q2_21", "2-21) Before your pregnancy with [SIBLING], were you ever told by a doctor that you had a neurological disease such as migraines, strokes or multiple sclerosis?", array(NULL=>"", "01_yes" => "01 Yes", "02_no" => "02 No", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('textarea', 'q2_21_text', $this->indent . "If [Yes], please specify:");
		$this->form->addRule(array('q2_21_text', 'q2_21'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q2_21_text');      // ******************

		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 2-23");
		$this->setRequired('q2_21');


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q2_22", "2-22) When were you first told by a doctor that you had [CONDITION]?", array(NULL=>"",  "01" => "01 Date", "02" => "02 Age ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addRule(array('q2_22', 'q2_21'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q2_22');


		$this->form->addElement('date', 'q2_22_date', 'If [01 Date], please specify:', $dateOptionsMy);

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q2_22_age", "If [02 Age], please specify (Years):" ,array(NULL=>"", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21" => "21", "22", "23" => "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "36", "37", "38", "39", "40", "41", "42", "43", "44", "45", "46", "47", "48", "49", "50", "51", "52", "53", "54", "55", "56", "57", "58", "59", "60", "61", "62", "63", "64", "65", "66", "67", "68", "69", "70"));


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q2_23", "2-23) Before your pregnancy with [SIBLING], were you ever told by a doctor that you
had any autoimmune condition such as hypothyroidism or hyperthyroidism,
rheumatoid arthritis, or lupus (SLE)?", array(NULL=>"", "01_yes" => "01 Yes", "02_no" => "02 No", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));          
		$this->form->addElement('textarea', 'q2_23_text', $this->indent . "If [Yes], please specify:");
		$this->form->addRule(array('q2_23_text', 'q2_23'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q2_23_text');      // ******************

		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 2-25");

		$this->setRequired('q2_23');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q2_24", "2-24) When were you first told by a doctor that you had [CONDITION]?", array(NULL=>"",  "01" => "01 Date", "02" => "02 Age ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addRule(array('q2_24', 'q2_23'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q2_24');


		$this->form->addElement('date', 'q2_24_date', 'If [01 Date], please specify:', $dateOptionsMy);

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q2_24_age", "If [02 Age], please specify (Years):" ,array(NULL=>"", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21" => "21", "22", "23" => "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "36", "37", "38", "39", "40", "41", "42", "43", "44", "45", "46", "47", "48", "49", "50", "51", "52", "53", "54", "55", "56", "57", "58", "59", "60", "61", "62", "63", "64", "65", "66", "67", "68", "69", "70"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q2_25", "2-25) Before your pregnancy with [SIBLING], were you ever told by a doctor that you
had asthma or allergies?", array(NULL=>"", "01_yes" => "01 Yes", "02_no" => "02 No", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('textarea', 'q2_25_text', $this->indent . "If [Yes], please specify:");
		$this->form->addRule(array('q2_25_text', 'q2_25'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q2_25_text');      // ******************

		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 2-27");
		$this->setRequired('q2_25');



		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q2_26", "2-26) When were you first told by a doctor that you had [CONDITION]?", array(NULL=>"", "01" => "01 Specify Date", "02" => "02 Specify Age ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));


		$this->form->addRule(array('q2_26', 'q2_25'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q2_26');


		$this->form->addElement('date', 'q2_26_date', 'If [01 Specify Date], please specify the ate:', $dateOptionsMy);

		$this->form->addRule(array('q2_26_date', 'q2_26'), 'Please specify the date.', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q2_26_date');


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q2_8_age", "If [02 Age], please specify the age (in years):" ,array(NULL=>"", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21" => "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "36", "37", "38", "39", "40", "41", "42", "43", "44", "45", "46", "47", "48", "49", "50", "51", "52", "53", "54", "55", "56", "57", "58", "59", "60", "61", "62", "63", "64", "65", "66", "67", "68", "69", "70"));

		$this->form->addElement('static', null, "<br/>");
		$this->form->addRule(array('q2_26_age', 'q2_26'), 'Please select the age.', 'requiredIf', array('operator'=>'==', 'value'=>'02'));
		$this->setRequired('q2_26_age');


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q2_27", "2-27) Before your pregnancy with [SIBLING], were you ever told by a doctor that you
had polycystic ovary syndrome (PCOS)?", array(NULL=>"", "01_yes" => "01 Yes", "02_no" => "02 No", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('textarea', 'q2_27_text', $this->indent . "If [Yes], please specify:");
		$this->form->addRule(array('q2_27_text', 'q2_27'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q2_27_text');      // ******************

		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 2-30");
		$this->setRequired('q2_27');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q2_28", "2-28) When were you first told by a doctor that you had PCOS?", array(NULL=>"",  "01" => "01 Date", "02" => "02 Age ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addRule(array('q2_28', 'q2_27'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q2_28');

		$this->form->addElement('date', 'q2_28_date', 'If [01 Date], please specify:', $dateOptionsMy);

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q2_28_age", "If [02 Age], please specify (Years):" ,array(NULL=>"", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21" => "21", "22", "23" => "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "36", "37", "38", "39", "40", "41", "42", "43", "44", "45", "46", "47", "48", "49", "50", "51", "52", "53", "54", "55", "56", "57", "58", "59", "60", "61", "62", "63", "64", "65", "66", "67", "68", "69", "70"));


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q2_29", "2-29) Did you take any medications or remedies for PCOS?", array(NULL=>"", "01_yes" => "01 Yes", "02_no" => "02 No", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addElement('textarea', 'q2_29_text', $this->indent . "If [Yes], please specify:");
		$this->form->addRule(array('q2_29', 'q2_27'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q2_29');

		$this->form->addRule(array('q2_29_text', 'q2_29'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q2_29_text');      // ******************


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q2_30", "2-30) Have you ever been diagnosed by a medical provider as having [CONDITION]?", array(NULL=>"", "01" => "01 Tubal factor infertility", "02" => "02 Other ovulatory dysfunction (besides PCOS)", "03" => "03  Diminished ovarian reserve", "04" => "04 Endometriosis", "05" => "05 Uterine factor infertility", "07" => "07 Infertility unexplained cause", "08" => "08 Other infertility problems", "09" => "09 None of the above ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->setRequired('q2_30');
		$this->form->addElement('textarea', 'q2_30_text', $this->indent . "If [Other infertility problems], please specify:");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q2_31", "2-31) Before this pregnancy, did you have any other major illnesses that we haven't
already asked about?", array(NULL=>"", "01_yes" => "01 Yes", "02_no" => "02 No", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addElement('static', null, $this->indent . "If [Yes], go to question 2-32");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 2-33");
		$this->setRequired('q2_31');


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q2_32", "2-32) What was the illness? Did you take any medication for it?", array(NULL=>"", "01" => "01 Illness", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addRule(array('q2_32', 'q2_31'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q2_32');


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q2_33", "2-33) How would you rate your general health as a child up to the age of 16 years?
Would you say it was...? [read choices]", array(NULL=>"", "01" => "01 Excellent", "02" => "02 Very good", "03" => "03  Good", "04" => "04 Fair", "05" => "05 Poor ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->setRequired('q2_33');


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q2_34", "2-34) Were you ever tested for anti-sperm antibody?", array(NULL=>"", "01_yes" => "01 Yes", "02_no" => "02 No", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, $this->indent . "If [Yes], go to question 2-35");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 2-36");

		$this->setRequired('q2_34');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q2_35", "2-35) What were the results of your test?", array(NULL=>"", "01" => "01 Positive", "02" => "02 Negative ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addRule(array('q2_35', 'q2_34'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q2_35');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q2_36", "2-36) Did you have any surgical procedures to open or rejoin your fallopian tubes, to
treat fibroids, or to remove endometriosis?", array(NULL=>"", "01_yes" => "01 Yes", "02_no" => "02 No", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->setRequired('q2_36');
		$this->form->addElement('static', null, $this->indent . "If [Yes], go to question 2-37");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 2-38");
		$this->setRequired('q2_37');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q2_37", "2-37) What was the procedure?", array(NULL=>"", "01" => "01 Open fallopian tubes", "02" => "02 Rejoin fallopian tubes", "03" => "03  Treatment of uterine fibroids", "04" => "04 Removal of endometriosis", "05" => "05 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addRule(array('q2_37', 'q2_36'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q2_37');

		$this->form->addElement('static', null, $this->indent . "If [Other], please specify:");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'q2_37_text_01', $this->indent . $this->indent . "PROCEDURE #1:");
		$this->form->addRule(array('q2_37_text_01', 'q2_37'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'05'));
		$this->setRequired('q2_37_text_01');

		$this->form->addElement('textarea', 'q2_37_text_02', $this->indent . $this->indent . "PROCEDURE #2:");
		$this->form->addElement('textarea', 'q2_37_text_03', $this->indent . $this->indent . "PROCEDURE #3:");


		$this->form->addElement('static', null, "<b>Now I am going to ask you about dental work you may have had.<br/></b>");




		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q2_38", "2-38) Have you ever had any amalgam (silver-colored) fillings in your mouth?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));

		$this->setRequired('q2_38');
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to next section");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q2_39", "2-39) When were these fillings put into place and how many did you have?", array(NULL=>"", "01" => "01 Specify Date (1 time)",  "01_1" => "01 Specify Date (2 times)","02" => "02 Specify Age (1 time)", "02_1" => "02 Specify Age (2 times)", "88_Refused" => "88 Refused", "99" => "99 Do not know", "Not_Answered" => "Not Answered"));

		$this->setRequired('q2_39');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('date', 'q2_39_date_1', 'If [01 Specify Date (1 time)], please specify the date:', $dateOptionsOldMY);

		$this->form->addRule(array('q2_39_date_1', 'q2_39'), 'Please specify the date.', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q2_39_date_1');


		$this->form->addElement("select", "q2_39_num_1", "and the number of fillings:", array(NULL=>"",  "0","1", "2", "3", "4", "5", "6", "7", "8", "9","10", "11", "12", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addRule(array('q2_39_num_1', 'q2_39'), 'Please select the number.', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q2_39_num_1');



		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('date', 'q2_39_date_2', 'If [01 Specify Date (2 times)], please specify both dates:', $dateOptionsOldMY);


		$this->form->addRule(array('q2_39_date_1', 'q2_39'), 'Please specify the date.', 'requiredIf', array('operator'=>'==', 'value'=>'01_1'));
		$this->setRequired('q2_39_date_1');


		$this->form->addRule(array('q2_39_date_2', 'q2_39'), 'Please specify the date.', 'requiredIf', array('operator'=>'==', 'value'=>'01_1'));
		$this->setRequired('q2_39_date_2');


		$this->form->addElement("select", "q2_39_num_2", "and the number of fillings:", array(NULL=>"",  "0","1", "2", "3", "4", "5", "6", "7", "8", "9","10", "11", "12", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addRule(array('q2_39_num_1', 'q2_39'), 'Please select the number.', 'requiredIf', array('operator'=>'==', 'value'=>'01_1'));
		$this->setRequired('q2_39_num_1');


		$this->form->addRule(array('q2_39_num_2', 'q2_39'), 'Please select the number.', 'requiredIf', array('operator'=>'==', 'value'=>'01_1'));
		$this->setRequired('q2_39_num_2');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q2_39_age_1", "If [02 Specify Age (1 time)], please specify age (in years):" ,array(NULL=>"", "1", "2", "3", "4", "5", "6", "7", "8", "9","10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21" => "21", "22", "23" => "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "36", "37", "38", "39", "40", "41", "42", "43", "44", "45", "46", "47", "48", "49", "50", "51", "52", "53", "54", "55", "56", "57", "58", "59", "60", "61", "62", "63", "64", "65", "66", "67", "68", "69", "70"));


		$this->form->addRule(array('q2_39_age_1', 'q2_39'), 'Please specify the age.', 'requiredIf', array('operator'=>'==', 'value'=>'02'));
		$this->setRequired('q2_39_age_1');


		$this->form->addElement("select", "q2_39_num_3", "and the number of fillings:", array(NULL=>"",  "0","1", "2", "3", "4", "5", "6", "7", "8", "9","10", "11", "12", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addRule(array('q2_39_num_3', 'q2_39'), 'Please select the number.', 'requiredIf', array('operator'=>'==', 'value'=>'02'));
		$this->setRequired('q2_39_num_3');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q2_39_age_2", "If [02 Specify Age (2 times)], please specify  the 2nd age (in years):" ,array(NULL=>"", "1", "2", "3", "4", "5", "6", "7", "8", "9","10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21" => "21", "22", "23" => "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "36", "37", "38", "39", "40", "41", "42", "43", "44", "45", "46", "47", "48", "49", "50", "51", "52", "53", "54", "55", "56", "57", "58", "59", "60", "61", "62", "63", "64", "65", "66", "67", "68", "69", "70"));

		$this->form->addRule(array('q2_39_age_1', 'q2_39'), 'Please specify the age.', 'requiredIf', array('operator'=>'==', 'value'=>'02_1'));
		$this->setRequired('q2_39_age_1');

		$this->form->addRule(array('q2_39_age_2', 'q2_39'), 'Please specify both ages.', 'requiredIf', array('operator'=>'==', 'value'=>'02_1'));
		$this->setRequired('q2_39_age_2');


		$this->form->addElement('static', null, "<br/>");

		$this->form->addRule(array('q2_39_num_3', 'q2_39'), 'Please select the number.', 'requiredIf', array('operator'=>'==', 'value'=>'02_1'));
		$this->setRequired('q2_39_num_3');

		$this->form->addElement("select", "q2_39_num_4", "and the number of fillings:", array(NULL=>"",  "0","1", "2", "3", "4", "5", "6", "7", "8", "9","10", "11", "12", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addRule(array('q2_39_num_4', 'q2_39'), 'Please select the number.', 'requiredIf', array('operator'=>'==', 'value'=>'02_1'));
		$this->setRequired('q2_39_num_4');


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q2_40", "2-40) How many amalgam fillings did you have in your mouth at the time you
became pregnant with your current pregnancy?", array(NULL=>"","01 None", "02" => "02 1-4", "03" => "03  5-10", "04" => "04 > 10", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('header', null, "END Section 2");
		$this->setRequired('q2_40');











	}


	//--------------------------------------------------------------


	function _page4(){   // ========================================================


		// To implement Xin Rule

		$this->form->addFormRule(array(&$this,'XINValidate'));



		$config =& NDB_Config::singleton();

		$dateOptions = array(
		'language' => 'en',
		'format'   => 'YMd',
		'minYear'  => $config->getSetting('startYear'), //allows for siblings up to 20 years older than candidate
		'maxYear'  => $config->getSetting('endYear'),
		'addEmptyOption' => true,
		'emptyOptionValue' => null
		);
		$dateOptionsYears = array(
		'language' => 'en',
		'format'   => 'Y',
		'minYear'  => $config->getSetting('startYear'), //allows for siblings up to 20 years older than candidate
		'maxYear'  => $config->getSetting('endYear'),
		'addEmptyOption' => true,
		'emptyOptionValue' => null
		);
		$dateOptionsMy = array(
		'language' => 'en',
		'format'   => 'YM',
		'minYear'  => $config->getSetting('startYear'), //allows for siblings up to 20 years older than candidate
		'maxYear'  => $config->getSetting('endYear'),
		'addEmptyOption' => true,
		'emptyOptionValue' => null
		);

		$this->form->addElement('header', null, "Section 3. PREGNANCY AND REPRODUCTIVE HISTORY");
		$this->form->addElement('header', null, "PART 1");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b>Now I'm going to ask you some questions about your reproductive and pregnancy
experiences.");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q3_1", "3-1) How old (in years) were you when you had your first menstrual period?" ,array(NULL=>"", "7", "8", "9","10", "11", "12", "13", "14", "15", "16", "17", "18", "88_Refused" => "88 Refused",  "99_Do_not_know" => "99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->setRequired('q3_1');

		$this->form->addElement('static', null, $this->indent . " If the age is entered or [Refused], go to question 3-3");
		$this->form->addElement('static', null, $this->indent . " If [Do not know], go to question 3-2");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q3_2", "3-2)  What grade were you in when you had your first menstrual period?", array(NULL=>"", "1", "2", "3", "4", "5", "6", "7", "8", "9","10", "11", "12", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addRule(array('q3_2', 'q3_1'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'99_Do_not_know'));
		$this->setRequired('q3_2');

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q3_3", "3-3)  What was the average or typical number of days of your cycle between the
first day of one menstrual period and the first day of the next menstrual
period? Please think back to a time when you were not using birth control pills
or other hormonal contraceptives.", array(NULL=>"", "21" => "21", "22", "23" => "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "90 Irregular period", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->setRequired('q3_3');

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q3_4", "3-4) How many times have you been pregnant? Please count all pregnancies,
including those that ended in live birth, stillbirth, miscarriage, abortion, or a
tubal, ectopic, or molar pregnancy. Include children from other relationships,
your pregnancy with [PROBAND] and your last pregnancy with the sibling of
the child with ASD.", array(NULL=>"", "1", "2", "3", "4", "5", "6", "7", "8", "9","10", "11", "12",  "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->setRequired('q3_4');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b>The remainder of the questions in Section 3 (Pregnancy and Reproductive History) should
be asked for each pregnancy except the pregnancy with the [SIBLING].</b>");  

		$this->form->addElement('static', null, "<b>$this->inden If more than one previous pregnancy, use Pregnancy Insert forms and label as
PREGNANCY 2, PREGNANCY 3, PREGNANCY 4, etc.");

		$this->form->addElement('static', null, "<b>All questions pertaining to PREGNANCY 1 should be asked first, then PREGNANCY 2, then PREGNANCY 3, etc.");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b>The next few questions are about your 1st pregnancy only.");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q3_5", "3-5) How many babies were you carrying during your 1st pregnancy?", array(NULL=>"", "1"=>"1 (Single baby)", "2"=>"2 (Twins)", "3"=>"3", "4"=>"4", "5"=>"5", "88_Refused" => "88 Refused", "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->setRequired('q3_5');
		$this->form->addElement('static', null, $this->indent . " If [single baby], go to question 3-6");
		$this->form->addElement('static', null, $this->indent . " If [multiple babies],go to question 3-7");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q3_6", "3-6) Did your 1st pregnancy end with a/an...? ",  array(NULL=>"", "01" => "01 Live birth", "02" => "02 Stillbirth", "03" => "03  Induced abortion", "04" => "04 Miscarriage", "05" => "05 Tubal pregnancy", "06" => "06 Molar pregnancy", "07" => "07 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addRule(array('q3_6', 'q3_5'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'1'));
		$this->setRequired('q3_6');

		$this->form->addElement('static', null, $this->indent . " If [Live birth], go to question 3-10");
		$this->form->addElement('static', null, $this->indent . " If [Stillbirth] or [Induced abortion] or [Miscarriage] or [Tubal pregnancy] or [Molar pregnancy] or [Other], go to question 3-12");
		$this->form->addElement('static', null, $this->indent . " If [Refused] or [Don't Know], skip to question 3-10");

		$this->form->addElement('textarea', 'q3_6_text', $this->indent . " If [Other], please specify.");
		$this->form->addRule(array('q3_6_text', 'q3_6'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'07'));
		$this->setRequired('q3_6_text');


		$this->form->addElement('static', null, "<br/>3-7) For your 1st pregnancy, what was the outcome for each baby? Was it a/an...");

		$this->form->addElement("select", "q3_7_1", "<br/>$this->indent BABY # 1",  array(NULL=>"", "01" => "01 Live birth", "02" => "02 Stillbirth", "03" => "03  Induced abortion", "04" => "04 Miscarriage", "05" => "05 Tubal pregnancy", "06" => "06 Molar pregnancy", "07" => "07 Other ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->setRequired('q3_7_1');

		$this->form->addElement('textarea', 'q3_7_1_text', $this->indent . " If [Other], please specify.");
		$this->form->addRule(array('q3_7_1_text', 'q3_7_1'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'07'));
		$this->setRequired('q3_7_1_text');

		$this->form->addElement("select", "q3_7_2", "<br/>$this->indent BABY # 2",  array(NULL=>"", "01" => "01 Live birth", "02" => "02 Stillbirth", "03" => "03  Induced abortion", "04" => "04 Miscarriage", "05" => "05 Tubal pregnancy", "06" => "06 Molar pregnancy", "07" => "07 Other ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('textarea', 'years', $this->indent . "<br/> $this->indent If [Other], please specify.");
		$this->setRequired('q3_7_2');

		$this->form->addElement('textarea', 'q3_7_2_text', $this->indent . " If [Other], please specify.");
		$this->form->addRule(array('q3_7_2_text', 'q3_7_2'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'07'));
		$this->setRequired('q3_7_2_text');

		$this->form->addElement("select", "q3_7_3", "<br/>$this->indent BABY # 3",  array(NULL=>"", "01" => "01 Live birth", "02" => "02 Stillbirth", "03" => "03  Induced abortion", "04" => "04 Miscarriage", "05" => "05 Tubal pregnancy", "06" => "06 Molar pregnancy", "07" => "07 Other ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('textarea', 'years', $this->indent . "<br/> $this->indent If [Other], please specify.");

		$this->form->addElement('textarea', 'q3_7_3_text', $this->indent . " If [Other], please specify.");
		$this->form->addRule(array('q3_7_3_text', 'q3_7_3'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'07'));
		$this->setRequired('q3_7_3_text');

		$this->form->addElement("select", "q3_7_4", "<br/>$this->indent BABY # 4",  array(NULL=>"", "01" => "01 Live birth", "02" => "02 Stillbirth", "03" => "03  Induced abortion", "04" => "04 Miscarriage", "05" => "05 Tubal pregnancy", "06" => "06 Molar pregnancy", "07" => "07 Other ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('textarea', 'years', $this->indent . "<br/> $this->indent If [Other], please specify.");
		$this->form->addElement('textarea', 'q3_7_4_text', $this->indent . " If [Other], please specify.");
		$this->form->addRule(array('q3_7_4_text', 'q3_7_4'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'07'));
		$this->setRequired('q3_7_4_text');

		$this->form->addElement("select", "q3_7_5", "<br/>$this->indent BABY # 5",  array(NULL=>"", "01" => "01 Live birth", "02" => "02 Stillbirth", "03" => "03  Induced abortion", "04" => "04 Miscarriage", "05" => "05 Tubal pregnancy", "06" => "06 Molar pregnancy", "07" => "07 Other ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('textarea', 'years', $this->indent . "<br/> $this->indent If [Other], please specify.");
		$this->form->addElement('textarea', 'q3_7_5_text', $this->indent . " If [Other], please specify.");
		$this->form->addRule(array('q3_7_5_text', 'q3_7_5'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'07'));
		$this->setRequired('q3_7_5_text');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . " If [01 Live birth], go to question 3-10");
		$this->form->addElement('static', null, $this->indent . " If [> 01 Live birth], go to question 3-8");
		$this->form->addElement('static', null, $this->indent . " If [other outcome(s)], go to question 3-12");

		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q3_8", "3-8) Were the babies identical?",  array(NULL=>"", "01_yes" => "01 Yes", "02_no" => "02 No", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, $this->indent . " If [Yes], go to question 3-9");
		$this->form->addElement('static', null, $this->indent . " If [No] or [Refused] or [Don't Know], skip to question 3-10");

		$this->setRequired('q3_');

		$this->form->addElement("select", "q3_9", "3-9) How do you know they are identical twins?",  array(NULL=>"", "01" => "01 Doctor told you", "02" => "02 Genetic tests", "03" => "03  They are as alike as two peas in a pod", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addElement('static', null, "<br/>");

		$this->form->addRule(array('q3_9', 'q3_8'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q3_9');

		$this->form->addElement("select", "q3_10", "3-10) Was this pregnancy with [PROBAND]?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered")
		);

		$this->form->addRule(array('q3_10', 'q3_6'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q3_10');

		$this->form->addElement('static', null, $this->indent . " If [Yes], go to question 3-13");
		$this->form->addElement('static', null, $this->indent . " If [No], go to question 3-11");


		$this->form->addRule(array('q3_10', 'q3_7_1'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q3_10');

		$this->form->addRule(array('q3_10', 'q3_8'), 'This question is required', 'requiredIf', array('operator'=>'!=', 'value'=>'01'));
		$this->setRequired('q3_10');


		$this->form->addElement("select", "q3_11", "3-11) Does the baby from your 1st pregnancy have the same biological father as
[PROBAND]?",  array(NULL=>"", "01_yes" => "01 Yes", "02_no" => "02 No", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, $this->indent . "<b>Record answer, then [go to question 3-14]</b>");
		$this->form->addRule(array('q3_11', 'q3_10'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'02'));
		$this->setRequired('q3_11');

		$this->form->addElement("select", "q3_12", "3-12) Did the [OUTCOME] have the same biological father as [PROBAND]",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, " $this->indent Record answer, then [go to question 3-20]</b>");

		$this->form->addRule(array('q3_12', 'q3_10'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'02'));
		$this->setRequired('q3_12');


		$this->form->addElement("select", "q3_13", "3-13) Please select from the following:", array(NULL=>"", "01" => "Singleton birth",  "02" => "Multiple births", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addRule(array('q3_13', 'q3_10'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q3_13');


		$this->form->addElement('static', null, "If [live singleton birth], then go to question 3-14");
		$this->form->addElement('static', null, $this->indent . " $this->indent If [live multiple births], then go to question 3-15");

		$this->form->addElement('static', null, "3-14) What is the first name of the baby from your 1st
pregnancy?");       
		$this->form->addElement('textarea', 'q3_14_first_name', $this->indent . "FIRST NAME:");

		$this->form->addRule(array('q3_14_first_name', 'q3_13'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q3_14_first_name');

		$this->form->addElement('static', null, $this->indent . "Record answer, then go to question 3-16. (if Proband, automatic fill)");

		$this->form->addElement('static', null, "3-15) What are the first names of each of the babies born
from your 1st pregnancy?");       
		$this->form->addElement('textarea', 'q3_15_name1', $this->indent . "BABY #1:");
		$this->form->addElement('textarea', 'q3_15_name2', $this->indent . "BABY #2:");
		$this->form->addElement('textarea', 'q3_15_name3', $this->indent . "BABY #3:");
		$this->form->addElement('textarea', 'q3_15_name4', $this->indent . "BABY #4:");
		$this->form->addElement('textarea', 'q3_15_name5', $this->indent . "BABY #5:");
		$this->form->addElement('static', null, " $this->indent Record answer, then go to question 3-17");

		$this->form->addRule(array('q3_15_name1', 'q3_13'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'02'));
		$this->setRequired('q3_15_name1');

		$this->form->addRule(array('q3_15_name2', 'q3_13'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'02'));
		$this->setRequired('q3_15_name2');

		$this->form->addElement("select", "q3_16", "3-16) What was the gender of the baby born from your 1st pregnancy? ",  array(NULL=>"", "01" => "01 Boy", "02" => "02 Girl ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));


		$this->form->addRule(array('q3_16', 'q3_13'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q3_16');


		$this->form->addElement('static', null, " $this->indent Record answer, then [go to question 3-18] (if Proband, automatic fill)</b>");

		$this->form->addElement('static', null, "3-17) What were the genders of the babies born from your 1st pregnancy?");

		$this->setRequired('q3_');

		$this->form->addElement("select", "q3_17_1", "BABY #1 ",  array(NULL=>"", "01" => "01 Boy", "02" => "02 Girl ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->setRequired('q3_');

		$this->form->addElement("select", "q3_17b", "<br/>$this->indent BABY #2 ",  array(NULL=>"", "01" => "01 Boy", "02" => "02 Girl ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->setRequired('q3_');

		$this->form->addElement("select", "q3_17c", "<br/>$this->indent BABY #3 ",  array(NULL=>"", "01" => "01 Boy", "02" => "02 Girl ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->setRequired('q3_');

		$this->form->addElement("select", "q3_17d", "<br/>$this->indent BABY #4 ",  array(NULL=>"", "01" => "01 Boy", "02" => "02 Girl ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->setRequired('q3_');

		$this->form->addElement("select", "q3_17e", "<br/>$this->indent BABY #5 ",  array(NULL=>"", "01" => "01 Boy", "02" => "02 Girl ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addElement('static', null, " $this->indent Record answer, then [go to question 3-19]");

		$this->setRequired('q3_');

		$this->form->addElement("select", "q3_18", "3-18) What is the birth date of the baby from your 1st
pregnancy?",  array(NULL=>"", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addElement('static', null, " $this->indent Record answer, then [go to question 3-30]");


		$this->form->addElement('static', null, " $this->indent If proband pregnancy (YES to 3-10), record on pregnancy calendar as DOPB.");

		$this->setRequired('q3_');



		$this->form->addElement("select", "q3_19", "3-19) What are the birth dates of each baby born
from your 1st pregnancy?",  array(NULL=>"", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));


		$this->form->addElement('static', null, " $this->indent Record answer, then [go to question 3-23]</b>");


		$this->form->addElement('static', null, $this->indent . " If proband pregnancy (YES to 3-10), record on pregnancy calendar as DOPB.");


		$this->setRequired('q3_');

		$this->form->addElement("select", "q3_20", "3-20) On what date did your 1st pregnancy end?",  array(NULL=>"","88 Refused", "99" => "99 Do not know", "Not_Answered" => "Not Answered"));

		$this->form->addElement('static', null, " $this->indent Record answer, then [go to question 3-33]</b>");



	}




	function _page5(){   // ========================================================

		// To implement Xin Rule

		$this->form->addFormRule(array(&$this,'XINValidate'));






		$this->form->addElement('header', null, "Section 3. PREGNANCY AND REPRODUCTIVE HISTORY");
		$this->form->addElement('header', null, "PART 2");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");



		$this->form->addElement('static', null, " 3-21) How long had you been pregnant when the 1st
pregnancy ended?"); 
		$this->form->addElement('textarea', 'week', $this->indent . "Weeks");
		$this->form->addElement('textarea', 'months', $this->indent . "Months");

		$this->setRequired('q3_');

		$this->form->addElement("select", "q3_22", "3-22) How many pounds and ounces did [BABY] weigh?",  array(NULL=>"", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addElement('static', null, " $this->indent Record answer, then [go to question 3-24]</b>");

		$this->setRequired('q3_');

		$this->form->addElement("select", "q3_23", "3-23) How many pounds and ounces did each baby
born from your 1st pregnancy weigh?",  array(NULL=>"", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));       
		$this->form->addElement('static', null, " $this->indent Record answer, then [go to question 3-25]</b>");
		$this->setRequired('q3_');

		$this->form->addElement("select", "q3_24", "3-24) Is [BABY] still living?",  array(NULL=>"", "01_yes" => "01 Yes", "02_no" => "02 No", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, $this->indent . " If [Yes], go to question 3-30");
		$this->form->addElement('static', null, $this->indent . " If [No], go to question 3-26");

		$this->form->addElement('static', null, $this->indent . " If [Refused] or [Don't Know], skip to question 3-32");
		$this->form->addElement('static', null, "3-25) Is [BABY] still living?");

		$this->form->addElement("select", "q3_25a", "BABY #1 ",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));

		$this->setRequired('q3_');

		$this->form->addElement("select", "q3_25b", "BABY #2 ",  array(NULL=>"", "01_yes" => "01 Yes", "02_no" => "02 No", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->setRequired('q3_');

		$this->form->addElement("select", "q3_25c", "BABY #3 ",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->setRequired('q3_');

		$this->form->addElement("select", "q3_25d", "BABY #4 ",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->setRequired('q3_');

		$this->form->addElement("select", "q3_25e", "BABY #5 ",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "");
		$this->form->addElement('static', null, $this->indent . " If [Yes], go to question 3-30");
		$this->form->addElement('static', null, $this->indent . " If [No], go to question 3-27");
		$this->form->addElement('static', null, $this->indent . " If [Refused] or [Don't Know], skip to question 3-32");

		$this->form->addElement('static', null, " $this->indent Record answer, then [go to question 3-28]");

		$this->form->addElement('static', null, "");
		$this->form->addElement('static', null, "3-26) What did [BABY] die of?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'years', $this->indent . "Give the reason");
		$this->setRequired('q3_');

		$this->form->addElement("select", "q3_26",  "$this->indent or choose from following:",  array(NULL=>"", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));


		$this->form->addElement('static', null, " $this->indent If [Refused] or [Don't Know], skip to question 3-32");
		$this->form->addElement('static', null, " $this->indent Record answer, then [go to question 3-28]");


		$this->form->addElement('static', null, "");
		$this->form->addElement('static', null, "3-27) What did each [BABY] die of?");
		$this->form->addElement('static', null, "");
		$this->form->addElement('static', null, "BABY #1:");
		$this->form->addElement('textarea', 'years', $this->indent . "Give the reason");
		$this->setRequired('q3_');

		$this->form->addElement("select", "q3_27",  "$this->indent or choose from following:",  array(NULL=>"", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "BABY #2:");
		$this->form->addElement('textarea', 'years', $this->indent . "Give the reason");
		$this->setRequired('q3_');

		$this->form->addElement("select", "q3_27",  "$this->indent or choose from following:",  array(NULL=>"", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "BABY #3:");
		$this->form->addElement('textarea', 'years', $this->indent . "Give the reason");
		$this->setRequired('q3_');

		$this->form->addElement("select", "q3_27",  "$this->indent or choose from following:",  array(NULL=>"", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "BABY #4:");
		$this->form->addElement('textarea', 'years', $this->indent . "Give the reason");
		$this->setRequired('q3_');

		$this->form->addElement("select", "q3_27",  "$this->indent or choose from following:",  array(NULL=>"", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "BABY #5:");
		$this->form->addElement('textarea', 'years', $this->indent . "Give the reason");
		$this->setRequired('q3_');

		$this->form->addElement("select", "q3_27",  "$this->indent or choose from following:",  array(NULL=>"", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addElement('static', null, " $this->indent Record answer, then [go to question 3-29]");


		$this->form->addElement('static', null, "");


		$this->form->addElement('static', null, "3-28) How old was [BABY] when he/she died?");
		$this->form->addElement('textarea', 'week', $this->indent . $this->indent . " Years");
		$this->form->addElement('textarea', 'months', $this->indent . $this->indent . " Months");
		$this->setRequired('q3_');

		$this->form->addElement("select", "q3_28",  "$this->indent or choose from following:",  array(NULL=>"", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addElement('static', null, $this->indent . " If don't know, ask:");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . " What was the date of [BABY]'s death?");
		$this->form->addElement('textarea', 'week', $this->indent . $this->indent . "  Enter date");
		$this->setRequired('q3_');

		$this->form->addElement("select", "q3_28_a",  "$this->indent $this->indent or choose from following:",  array(NULL=>"", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addElement('static', null, " $this->indent Record answer, then [go to question 3-32]");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "3-29) How old was [BABY] when he/she died?");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "BABY #1:");
		$this->form->addElement('textarea', 'week', $this->indent . $this->indent . " Years");
		$this->form->addElement('textarea', 'months', $this->indent . $this->indent . " Months");
		$this->setRequired('q3_');

		$this->form->addElement("select", "q3_29",  "$this->indent or choose from following:",  array(NULL=>"", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, $this->indent . " If don't know, ask:");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . " What was the date of [BABY]'s death?");
		$this->form->addElement('textarea', 'week', $this->indent . $this->indent . "  Enter date");
		$this->setRequired('q3_');

		$this->form->addElement("select", "q3_29_a",  "$this->indent $this->indent or choose from following:",  array(NULL=>"", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "BABY #2:");
		$this->form->addElement('textarea', 'week', $this->indent . $this->indent . " Years");
		$this->form->addElement('textarea', 'months', $this->indent . $this->indent . " Months");
		$this->setRequired('q3_');

		$this->form->addElement("select", "q3_29",  "$this->indent or choose from following:",  array(NULL=>"", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addElement('static', null, $this->indent . " If don't know, ask:");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . " What was the date of [BABY]'s death?");
		$this->form->addElement('textarea', 'week', $this->indent . $this->indent . "  Enter date");
		$this->setRequired('q3_');

		$this->form->addElement("select", "q3_29_b",  "$this->indent $this->indent or choose from following:",  array(NULL=>"", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));



		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "BABY #3:");
		$this->form->addElement('textarea', 'week', $this->indent . $this->indent . " Years");
		$this->form->addElement('textarea', 'months', $this->indent . $this->indent . " Months");
		$this->setRequired('q3_');

		$this->form->addElement("select", "q3_29",  "$this->indent or choose from following:",  array(NULL=>"", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, $this->indent . " If don't know, ask:");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . " What was the date of [BABY]'s death?");
		$this->form->addElement('textarea', 'week', $this->indent . $this->indent . "  Enter date");
		$this->setRequired('q3_');

		$this->form->addElement("select", "q3_29_c",  "$this->indent $this->indent or choose from following:",  array(NULL=>"", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "BABY #4:");
		$this->form->addElement('textarea', 'week', $this->indent . $this->indent . " Years");
		$this->form->addElement('textarea', 'months', $this->indent . $this->indent . " Months");
		$this->setRequired('q3_');

		$this->form->addElement("select", "q3_29",  "$this->indent or choose from following:",  array(NULL=>"", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addElement('static', null, $this->indent . " If don't know, ask:");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . " What was the date of [BABY]'s death?");
		$this->form->addElement('textarea', 'week', $this->indent . $this->indent . "  Enter date");
		$this->setRequired('q3_');

		$this->form->addElement("select", "q3_29_d",  "$this->indent $this->indent or choose from following:",  array(NULL=>"", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "BABY #5:");
		$this->form->addElement('textarea', 'week', $this->indent . $this->indent . " Years");
		$this->form->addElement('textarea', 'months', $this->indent . $this->indent . " Months");
		$this->setRequired('q3_');

		$this->form->addElement("select", "q3_29",  "$this->indent or choose from following:",  array(NULL=>"", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addElement('static', null, $this->indent . " If don't know, ask:");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . " What was the date of [BABY]'s death?");
		$this->form->addElement('textarea', 'week', $this->indent . $this->indent . "  Enter date");
		$this->setRequired('q3_');

		$this->form->addElement("select", "q3_29_e",  $this->indent. $this->indent . "or choose from following:",  array(NULL=>"", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addElement('static', null, $this->indent . "Record answer, then [go to question 3-32]");


		$this->setRequired('q3_29');

		$this->form->addElement("select", "q3_30", "3-30)  Did you ever breastfeed or pump breast milk to feed [BABY]?", array(NULL=>"", "01_yes" => "01 Yes", "02_no" => "02 No", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addElement('static', null, $this->indent . " If [Yes], go to question 3-31");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 2-32");

		$this->form->addElement("static", null, "3-31) How long did you breastfeed [BABY]");
		$this->addTextElement("q3_31weeks", "...weeks","" ,"" , array(NULL=>"", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->addTextElement("q3_31months", "...months", "", "", array(NULL=>"", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		//     $this->addTextElement("q3_31",  "3-31) For how many weeks or months did you breastfeed [BABY]","" , "", array(NULL=>"", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		//        $this->form->addElement('static', null, " 3-31) For how many weeks or months did you breastfeed [BABY]?");
		//      $this->form->addElement('textarea', 'week', $this->indent . "Weeks");
		//    $this->form->addElement('textarea', 'months', $this->indent . "Months");



		$this->setRequired('q3_30');

		//        $this->form->addElement("select", "q3_31",  "$this->indent $this->indent or choose from following:",  array(NULL=>"", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		//      $this->form->addElement('static', null, $this->indent . " If [Refused] or [Don't Know] skip to question 2-32");
		//    $this->form->addElement('static', null, $this->indent . " unnecessary KP");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "3-32) Have you ever received a diagnosis from a health care provider that your child/any of your children from your 1st pregnancy had or has...");
		$this->form->addElement('static', null, "<br/>");
		$this->setRequired('q3_');

		$this->form->addElement("select", "q3_32",  "$this->indent BABY #1",  array(NULL=>"", "01" => "01 Asperger's Syndrome", "02" => "02 Attention Deficit Hyperactivity Disorder (ADHD) or ADD", "03" => "03  Autism", "04" => "04 Behavioral problem (SPECIFY) (for each pregnancy that it applies to)add line JH", "05" => "05 Bipolar disorder", "06" => "06 Birth Defects (SPECIFY) (for each pregnancy that it applies to) add line JH", "07" => "07 Cerebral palsy", "08" => "08 Childhood Disintegrative Disorder", "09" => "09 Childhood onset schizophrenia", "10" => "10 Developmental delay", "11" => "11 Down Syndrome", "12" => "12 Fragile X Syndrome", "13" => "13 Hearing problems", "14" => "14 Learning disabilities", "15" => "15 Intellectual disability or mental retardation", "16 Movement or coordination problems", "17 Neurofibromatosis", "18" => "18 Obsessive compulsive disorder", "19 Other developmental problem (SPECIFY) add line JH", "20" => "20 Pervasive Developmental Disorder not otherwise specified", "21" => "21 Reactive attachment disorder of infancy or early childhood", "22" => "22 Reading difficulty", "23" => "23 Rett's Syndrome", "24 Seizure disorder or Epilepsy", "25 Self-injuring behavior", "26 Sensory integration disorder", "27 Sleep disorder", "28 Speech delays", "29 Tourette's Disorder or tic disorder", "30 Tuberous sclerosis", "31 Vision problems that cannot be corrected with glasses or contact lenses", "88 Other", "97 Not applicable (SKIP)", "98" => "98 Refused", "99" => "99 Do not know", "00 None"));
		$this->form->addElement('textarea', 'week', $this->indent . $this->indent . "  If [88 Other], please specify:");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q3_32",  "$this->indent BABY #2",  array(NULL=>"", "01" => "01 Asperger's Syndrome", "02" => "02 Attention Deficit Hyperactivity Disorder (ADHD) or ADD", "03" => "03  Autism", "04" => "04 Behavioral problem (SPECIFY) (for each pregnancy that it applies to)add line JH", "05" => "05 Bipolar disorder", "06" => "06 Birth Defects (SPECIFY) (for each pregnancy that it applies to) add line JH", "07" => "07 Cerebral palsy", "08" => "08 Childhood Disintegrative Disorder", "09" => "09 Childhood onset schizophrenia", "10" => "10 Developmental delay", "11" => "11 Down Syndrome", "12" => "12 Fragile X Syndrome", "13" => "13 Hearing problems", "14" => "14 Learning disabilities", "15" => "15 Intellectual disability or mental retardation", "16 Movement or coordination problems", "17 Neurofibromatosis", "18" => "18 Obsessive compulsive disorder", "19 Other developmental problem (SPECIFY) add line JH", "20" => "20 Pervasive Developmental Disorder not otherwise specified", "21" => "21 Reactive attachment disorder of infancy or early childhood", "22" => "22 Reading difficulty", "23" => "23 Rett's Syndrome", "24 Seizure disorder or Epilepsy", "25 Self-injuring behavior", "26 Sensory integration disorder", "27 Sleep disorder", "28 Speech delays", "29 Tourette's Disorder or tic disorder", "30 Tuberous sclerosis", "31 Vision problems that cannot be corrected with glasses or contact lenses", "88 Other", "97 Not applicable (SKIP)", "98" => "98 Refused", "99" => "99 Do not know", "00 None"));
		$this->form->addElement('textarea', 'week', $this->indent . $this->indent . "  If [88 Other], please specify:");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q3_32",  "$this->indent BABY #3",  array(NULL=>"", "01" => "01 Asperger's Syndrome", "02" => "02 Attention Deficit Hyperactivity Disorder (ADHD) or ADD", "03" => "03  Autism", "04" => "04 Behavioral problem (SPECIFY) (for each pregnancy that it applies to)add line JH", "05" => "05 Bipolar disorder", "06" => "06 Birth Defects (SPECIFY) (for each pregnancy that it applies to) add line JH", "07" => "07 Cerebral palsy", "08" => "08 Childhood Disintegrative Disorder", "09" => "09 Childhood onset schizophrenia", "10" => "10 Developmental delay", "11" => "11 Down Syndrome", "12" => "12 Fragile X Syndrome", "13" => "13 Hearing problems", "14" => "14 Learning disabilities", "15" => "15 Intellectual disability or mental retardation", "16 Movement or coordination problems", "17 Neurofibromatosis", "18" => "18 Obsessive compulsive disorder", "19 Other developmental problem (SPECIFY) add line JH", "20" => "20 Pervasive Developmental Disorder not otherwise specified", "21" => "21 Reactive attachment disorder of infancy or early childhood", "22" => "22 Reading difficulty", "23" => "23 Rett's Syndrome", "24 Seizure disorder or Epilepsy", "25 Self-injuring behavior", "26 Sensory integration disorder", "27 Sleep disorder", "28 Speech delays", "29 Tourette's Disorder or tic disorder", "30 Tuberous sclerosis", "31 Vision problems that cannot be corrected with glasses or contact lenses", "88 Other", "97 Not applicable (SKIP)", "98" => "98 Refused", "99" => "99 Do not know", "00 None"));
		$this->form->addElement('textarea', 'week', $this->indent . $this->indent . "  If [88 Other], please specify:");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q3_32",  "$this->indent BABY #4",  array(NULL=>"", "01" => "01 Asperger's Syndrome", "02" => "02 Attention Deficit Hyperactivity Disorder (ADHD) or ADD", "03" => "03  Autism", "04" => "04 Behavioral problem (SPECIFY) (for each pregnancy that it applies to)add line JH", "05" => "05 Bipolar disorder", "06" => "06 Birth Defects (SPECIFY) (for each pregnancy that it applies to) add line JH", "07" => "07 Cerebral palsy", "08" => "08 Childhood Disintegrative Disorder", "09" => "09 Childhood onset schizophrenia", "10" => "10 Developmental delay", "11" => "11 Down Syndrome", "12" => "12 Fragile X Syndrome", "13" => "13 Hearing problems", "14" => "14 Learning disabilities", "15" => "15 Intellectual disability or mental retardation", "16 Movement or coordination problems", "17 Neurofibromatosis", "18" => "18 Obsessive compulsive disorder", "19 Other developmental problem (SPECIFY) add line JH", "20" => "20 Pervasive Developmental Disorder not otherwise specified", "21" => "21 Reactive attachment disorder of infancy or early childhood", "22" => "22 Reading difficulty", "23" => "23 Rett's Syndrome", "24 Seizure disorder or Epilepsy", "25 Self-injuring behavior", "26 Sensory integration disorder", "27 Sleep disorder", "28 Speech delays", "29 Tourette's Disorder or tic disorder", "30 Tuberous sclerosis", "31 Vision problems that cannot be corrected with glasses or contact lenses", "88 Other", "97 Not applicable (SKIP)", "98" => "98 Refused", "99" => "99 Do not know", "00 None"));
		$this->form->addElement('textarea', 'other', $this->indent . $this->indent . "  If [88 Other], please specify:");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q3_32",  "$this->indent BABY #5",  array(NULL=>"", "01" => "01 Asperger's Syndrome", "02" => "02 Attention Deficit Hyperactivity Disorder (ADHD) or ADD", "03" => "03  Autism", "04" => "04 Behavioral problem (SPECIFY) (for each pregnancy that it applies to)add line JH", "05" => "05 Bipolar disorder", "06" => "06 Birth Defects (SPECIFY) (for each pregnancy that it applies to) add line JH", "07" => "07 Cerebral palsy", "08" => "08 Childhood Disintegrative Disorder", "09" => "09 Childhood onset schizophrenia", "10" => "10 Developmental delay", "11" => "11 Down Syndrome", "12" => "12 Fragile X Syndrome", "13" => "13 Hearing problems", "14" => "14 Learning disabilities", "15" => "15 Intellectual disability or mental retardation", "16 Movement or coordination problems", "17 Neurofibromatosis", "18" => "18 Obsessive compulsive disorder", "19 Other developmental problem (SPECIFY) add line JH", "20" => "20 Pervasive Developmental Disorder not otherwise specified", "21" => "21 Reactive attachment disorder of infancy or early childhood", "22" => "22 Reading difficulty", "23" => "23 Rett's Syndrome", "24 Seizure disorder or Epilepsy", "25 Self-injuring behavior", "26 Sensory integration disorder", "27 Sleep disorder", "28 Speech delays", "29 Tourette's Disorder or tic disorder", "30 Tuberous sclerosis", "31 Vision problems that cannot be corrected with glasses or contact lenses", "88 Other", "97 Not applicable (SKIP)", "98" => "98 Refused", "99" => "99 Do not know", "00 None"));
		$this->form->addElement('textarea', 'week', $this->indent . "If [88 Other], please specify:");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('header', null, $this->indent . "If more than one pregnancy, continue with pregnancy insert form(s) as needed for
next pregnancy(s) ending with the pregnancy that gave rise to the baby sib.");
		$this->form->addElement('header', null, "Insert completed forms behind this pag.e");
		$this->form->addElement("select", "q3_33", "3-33) We are also interested in any reproductive hormonal medications you
might have taken during your lifetime for any reason other than to prevent
pregnancy or to help you become pregnant. Did a doctor or other medical
provider ever prescribe reproductive hormonal medications? ",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));

		$this->form->addElement('static', null, $this->indent . " If [No] or [Refused] or [Don't Know] skip to question 4a-1");

		$this->setRequired('q3_33');

		$this->form->addElement("select", "q3_34", "3-34) What was the reason that the hormonal medication was prescribed?",  array(NULL=>"", "01" => "01 To regulate your cycle", "02" => "02 To jump-start puberty", "03" => "03  Growth regulation", "04" => "04 Acne", "05" => "05 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->setRequired('q3_34');
		$this->form->addElement('header', null, "<b>END Section 3");



	}


	function _page6() {   // ========================================================

		// To implement Xin Rule

		$this->form->addFormRule(array(&$this,'XINValidate'));

		$negThreeToTen = array_combine(range(-3, 10), range(-3, 10));
		unset($negThreeToTen[0]);
		$answerOptions = array(null=>"") + ($negThreeToTen) + array("88_Refused" => "88 Refused", "99_Do_not_know" => "99 Do not know", "not_answered" => "Not Answered");



		$this->form->addElement('header', null, "Section 4. PROBAND PREGNANCY");

		$this->form->addElement('header', null, "(Part 1)");


		$this->form->addElement('static', null, "<br/><b>Now I have some questions specific to your pregnancy with [PROBAND].</b>");

		$this->form->addElement("select", "q4a_1", "4a-1. Does your child with ASD and their younger
sibling have the same biological father?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addRule(array('q4a_1', 'q3_33'), 'This question is required', 'requiredIf', array('operator'=>'!=', 'value'=>'01'));

		$this->setRequired('q4a_1');


		$this->form->addElement('static', null, $this->indent . "If [Yes], skip to question 4-1");


		$this->form->addElement('date', 'q4a_2', "4a-2. What is your date of birth? Please enter date:", $dateOptions);
		$this->form->addElement("select", "q4_", $this->indent .  "or choose from following:",  array(NULL=>"", "88/88/8888 Refused", "99/99/9999 Do not know", "Not_Answered" => "Not Answered"));


		$this->form->addElement("select", "q4a_3", "4a-3. How old is he today? (Years)" ,array(NULL=>"", "11", "12", "13", "14", "15", "16", "17", "18" => "18", "19", "20" => "20", "21" => "21", "22" => "22", "23" => "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "36", "37", "38", "39", "40", "41", "42", "43", "44", "45", "46", "47", "48", "49", "50", "51", "52", "53", "54", "55", "56", "57", "58", "59", "60", "61", "62", "63", "64", "65", "66", "67", "68", "69", "70", "71", "72", "73", "74", "75", "77", "77", "78", "79", "80", "Not_Answered" => "Not Answered"));

		$this->setRequired('q4a_3');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('select', 'q4a_4', "4a-4. Where was he born?", array(NULL=>"","01_US" => "01 U.S.", "02_Outside_US" => "02 Outside U.S.", "88_Refused" => "88 Refused", "99_Do_not_know" => "99 Do not know", "Not_Answered" => "Not Answered"));

		$this->form->addElement('textarea', 'q4a_4_US_State', $this->indent . "If [U.S.], please specify state:");
		$this->form->addElement('textarea', 'q4a_4_Outside_US', $this->indent . "If [Outside U.S.], please specify country:");

		$this->form->addElement('static', null, $this->indent . "If [Outside U.S.], skip to question 4a-6");

		$this->form->addRule(array('q4a_4_US_State', '4a_4'), 'Please specify state.', 'requiredIf', array('operator'=>'==', 'value'=>'01_US'));
		$this->setRequired('q4a_4_US_State');

		$this->form->addRule(array('q4a_4_Outside_US', '4a_4'), 'Please specify country.', 'requiredIf', array('operator'=>'==', 'value'=>'02_Outside_US'));
		$this->setRequired('q4a_4_Outside_US');


		$this->form->addElement('static', null, "<br/>");



		$this->form->addElement('date', 'q4a_5', "4a-5. When did he come to live in the United States?", $this->dateOptions);


		$this->form->addElement("select", "q5_63", "5-63. What medication did you take?",  array(NULL=>"","CODE_01"=>"CODE 01: Aldomet", "CODE_02"=>"CODE 02: Labetalol", "CODE_03"=>"CODE 03: Hydralazine", "CODE_04"=>"CODE 04: Nifedipine", "CODE_05"=>"CODE 05: Magnesium Sulfate", "CODE_09"=>"CODE 09: Other"));

		$this->form->addRule(array('q5_63', 'q5_62'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q5_63');

		$this->form->addElement('textarea', 'q5_63_CODE_09_other', $this->indent . $this->indent . "If [CODE 09: Other], please specify:");


		$this->form->addRule(array('q5_63_CODE_09_other', 'q5_63'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'CODE_09'));
		$this->setRequired('q5_63_CODE_09_other');


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Medications for
hypertension /
preeclampsia:");

		$this->form->addElement('static', null, "<br/>");
		$questionArray = array("CODE_01"=>"CODE 01: Aldomet", "CODE_02"=>"CODE 02: Labetalol", "CODE_03"=>"CODE 03: Hydralazine", "CODE_04"=>"CODE 04: Nifedipine", "CODE_05"=>"CODE 05: Magnesium Sulfate", "CODE_09"=>"CODE 09: Other");
		reset($questionArray);

		while(list($field, $label) = each($questionArray)) {

			$this->form->addElement('static', null, "{$label}");
			$this->form->addElement("select", "q5_63_1_{$field}",  $this->indent .  "Month medication taken:",  array(NULL=>"","1", "2", "3", "4", "5", "6", "7", "8", "9", "Refused", "Do not know", "Not_Answered" => "Not Answered"));
			$this->form->addElement("select", "q5_63_2_{$field}",  $this->indent .  "Route of
Administration:",  array(NULL=>"","Oral", "Infusion", "Rectal", "Injection", "Infusion", "Not_Answered" => "Not Answered"));

			//testing HTML_QuickForm rules
			//		$field = "one";  //just for now...
			$answerOptions = array(NULL=>"", "tab_per_day" => "_____tabs or caps / day, for ____ days",
			"tab_week"=>"_____tabs or caps / week",
			"tab_month"=>"_____tabs or caps / month",
			"tab_every_day"=>"_____tabs or caps everyday",
			"other" => "Other", "Refused", "Do not know", "Not_Answered" => "Not Answered");
			var_dump($answerOptions);
			$this->form->addElement("select", "q5_63_3_{$field}",  $this->indent . "How often/number of capsules", $answerOptions);

			//        array('key'=>"value");
			//        array('db'=>'seen');

			$this->form->addElement('textarea', 'q5_63_3_{$field}_tabs', $this->indent . $this->indent . "Enter the number of tabs or caps:");
			$this->form->addRule(array('q5_63_3_{$field}_tabs', 'q5_63_3_{$field}'), 'Please specify.', 'requiredIf', array('operator'=>'!=', 'value'=>'NULL'));
			$this->setRequired('q5_63_3_{$field}_tabs');

			//        $this->form->addElement('textarea', 'q5_63_3_{$field}_day', $this->indent . $this->indent . "If [_____tabs or caps / day, for ____ days], please enter the number of days:");
			//		$this->form->addRule(array('q5_63_3_{$field}_day', 'q5_63_3_{$field}'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'tab_day'));
			//        $this->setRequired('q5_63_3_{$field}_day');
			//
			// //       $this->form->addElement('textarea', 'q5_63_3_{$field}_other', $this->indent . $this->indent . "If [Other], please specify:");
			//        $this->addTextElement('q5_63_3_{$field}_other', "If Other (test)");
			//		$this->form->addRule(array('q5_63_3_{$field}_other', 'q5_63_3_{$field}'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'Other'));
			//        $this->setRequired('q5_63_3_{$field}_other'); //**************************
		}


		$this->form->addElement('static', null, $this->indent . "Please select the year");
		//	$this->form->addRule(array('q4a_5', 'q1_3'), 'This question is required', 'requiredIf', array('operator'=>'!=', 'value'=>'01_US'));
		//      $this->setRequired('q4a_5');
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q4a_5_select", $this->indent . "or choose from following:",  array(NULL=>"", "8888 Refused", "9999 Do not know", "Not_Answered" => "Not Answered"));

		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q4a_6", "<br/> 4a-6. What language does he usually speak at home?",array(NULL=>"", "01" => "01 English", "02" => "02 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, $this->indent . " If [English], skip to question 4a-8");

		$this->setRequired('q4a_6');
		$this->form->addElement('textarea', 'q4a_6_Other', $this->indent . "If [Other] please specify:");
		$this->form->addRule(array('q4a_6_Other', 'q4a_6'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'02'));
		$this->setRequired('q4a_6_Other');
		$this->form->addElement("select", "q4a_7", "4a-7 How well does he speak English?", array(NULL=>"","01 Very well", "02" => "02 Well", "03" => "03  Not well", "04" => "04 Not at all", "88 Refused", "99" => "99 Do not know"));
		$this->form->addRule(array('q4a_7', 'q4a_6'), 'q1-6 is required', 'requiredIf', array('operator'=>'!=', 'value'=>'01_English'));

		$this->setRequired('q4a_7');


		$this->form->addElement("select", "q4a_8", "4a-8. What is his primary ethnicity?", array(NULL=>"","01 Hispanic", " or Latino", "02" => "02 Not Hispanic or Latino", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, $this->indent . "If [Not Hispanic or Latino], skip to question 4a-10");

		$this->form->addElement("select", "q4a_9", "4a-9. Of which Hispanic or Spanish group does he consider himself a member?", array(NULL=>"","01 Mexican, Mexican American, Chicano", "02" => "02 Puerto Rican ", "03" => "03  Cuban", "04" => "04 Other Spanish/Hispanic/Latino ", "88 Refused", "99" => "99 Do not know"));
		$this->form->addRule(array('q4a_9', 'q4a_8'), 'Please specify.', 'requiredIf', array('operator'=>'!=', 'value'=>'02'));
		$this->setRequired('q4a_9');

		$this->form->addElement("select", "q4a_10", "4a-10. What is his race?", array(NULL=>"","01 White
", "02Black, African American
", "03" => "03 American Indian / Alaskan Native Asian", "04" => "04 Asian Indian", "05" => "05 Chinese", "06" => "06 Filipino", "07" => "07 Japanese", "08" => "08 Korean", "09" => "09 Vietnamese", " 10 Thai / Cambodian", " 11 Other Asian Native Hawaiian and other Pacific Islander", " 12 Native Hawaiian", " 13 Guamanian or Chamorro" , " 14 Samoan", " 15 Other Pacific Islander", " 16 Other race ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addElement('textarea', 'other', $this->indent . "If [Other race],please specify:");

		$this->form->addRule(array('q4a_10_text', 'q4a_10'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'0'));
		$this->setRequired('q4a_10_text');

		$this->setRequired('q4a_10');

		$this->form->addElement("select", "q4_", "4a-11. What is the highest degree or level of education he has completed?",  array(NULL=>"", "01" => "01 No formal schooling completed", "02" => "02 Nursery school to 4th grade", "03" => "03  5th grade or 6th grade", "04" => "04 7th grade or 8th grade", "05" => "05 9th grade", "06" => "06 10th grade", "07" => "07 11th grade", "08" => "08 12th grade, no diploma", "09" => "09 High school graduate - high school diploma or equivalent (e.g., GED)", "10" => "10 Some college credit, but less than 1 year", "11" => "11 One or more years of college, no degree", "12" => "12 Technical college / vocational school", "13" => "13 Associate degree (e.g., AA, AS)", "14" => "14 Bachelor's degree (e.g., BA, AB, BS)", "15" => "15 Master's degree (e.g., MA, MS, MEng, Med, MSW, MBA)", "16" => "16 Professional degree (e.g., MD, DDS, DVM, LLB, JD)", "17" => "17 Doctorate degree (e.g., PhD, EdD) ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));


		$this->form->addElement('static', null, $this->indent .  "4-4. How much did you weigh before your pregnancy with
[PROBAND]?"); 
		$this->form->addElement('textarea', 'q4_4', $this->indent . "lbs.");
		$this->form->addElement("select", "q4_4_select", $this->indent .  "or choose from following:",  array(NULL=>"", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addElement('static', null, $this->indent . "If [Refused] or [Don't Know] skip to question 4-6");


		$this->form->addElement('static', null, "4-5. How much weight did you gain or lose with your pregnancy with [PROBAND]?");
		$this->form->addElement('textarea', 'week', $this->indent . "lbs.");
		$this->form->addElement("select", "q4_",  "$this->indent or choose from following:",  array(NULL=>"", "01" => "01 Weight gain", "02" => "02 Weight loss", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addElement('textarea', 'gain', $this->indent . "If [01 Weight gain], please specify how much:");
		$this->form->addElement('textarea', 'loss', $this->indent . "If [02 Weight loss], please specify how much:");

		$this->form->addElement('static', null, "4-6. What was your height without shoes?");

		$this->form->addElement("select", "q4_6_f", $this->indent .  "Feet:",  array(NULL=>"",  "1" => "1", "2" => "2", "3" => "3", "4", "5", "6", "7", "88_Refused" => "88 Refused", "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement("select", "q4_6_i", $this->indent .  "Inches:",  array(NULL=>"",  "0", "1" => "1", "2" => "2", "3" => "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "88_Refused" => "88 Refused", "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->setRequired('q4_6_f');
		$this->setRequired('q4_6_i');



		$this->form->addElement("select", "q4_7", $this->indent .  "4-7. How far along were you when you found out you were pregnant with [DOBS]?",  array(NULL=>"",  "00_w" => "00 Specify weeks", "00_m" => "00 Specify months" ,"88_Refused" => "88 Refused", "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));



		$this->form->addElement("select", "q4_7_w", $this->indent .  "Weeks:",  array(NULL=>"",  "0", "1" => "1", "2" => "2", "3" => "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18" => "18", "19", "20" => "20", "21" => "21", "22" => "22", "23" => "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "36", "37", "38","88_Refused" => "88 Refused", "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));


		$this->form->addElement("select", "q4_7_m", $this->indent .  "Months:",  array(NULL=>"",  "0", "1" => "1", "2" => "2", "3" => "3", "4", "5", "6", "7", "8", "9", "88_Refused" => "88 Refused", "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));


		$this->form->addRule(array('q4_7_w', 'q4_7'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'00_w'));
		$this->setRequired('q4_7_w');

		$this->form->addRule(array('q4_7_m', 'q4_7'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'00_m'));
		$this->setRequired('q4_7_m');

		$this->form->addElement('static', null, $this->indent .  "<b/>Refer to the Pregnancy Calendar.");


		$this->form->addElement("select", "q4_8", "4-8. Between [-3] and [DOPB], did you use any birth control pills or
morning after pills?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));

		$this->form->addElement('static', null, $this->indent . "If [Refused] or [Don't Know] skip to question 4-11");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "4-9. What was the name of the pills?");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . " May be too difficult to remember. If can't recall, ask to refer to List 2 in prep guide and choose from the following list:");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q4_9_p1", $this->indent .  "Pill #1",  array(NULL=>"", "01" => "01 Alesse", "02" => "02 Brevicon", "03" => "03  Demulen", "04" => "04 Desogen", "05" => "05 Estrostep", "06" => "06 Levlen", "07" => "07 Levlite", "08" => "08 Levora", "09" => "09 Loestrin", "10" => "10 Lo/Ovral", "11" => "11 Micronor", "12" => "12 Mircette", "13" => "13 Modicon", "14" => "14 Necon", "15" => "15 Nordette", "16" => "16 Norinyl", "17" => "17 Nor-Q.D", "18" => "18 Ortho-Cept", "19 OrthoCyclen", "20" => "20 Ortho-Novum", "21" => "21 Ortho Tri-Cyclen", "22" => "22 Ovcon", "23" => "23 Ovral", "24 Tri-Levlen", "25 Tri-Norinyl", "26 Triphasil", "27 Trivora", "28 Zovia",  "29" => "29 Other", "88 Refused", "99" => "99 Do not know"));

		$this->form->addRule(array('q4_9_p1', 'q4_8'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q4_9_p1');


		$this->form->addElement('textarea', 'other', $this->indent . "If [Other],please specify:");

		$this->form->addRule(array('q4_9_p1_text', 'q4_9_p1'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'29'));
		$this->setRequired('q4_9_p1_text');

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q4_9_p2", $this->indent .  "
        #2",  array(NULL=>"", "01" => "01 Alesse", "02" => "02 Brevicon", "03" => "03  Demulen", "04" => "04 Desogen", "05" => "05 Estrostep", "06" => "06 Levlen", "07" => "07 Levlite", "08" => "08 Levora", "09" => "09 Loestrin", "10" => "10 Lo/Ovral", "11" => "11 Micronor", "12" => "12 Mircette", "13" => "13 Modicon", "14" => "14 Necon", "15" => "15 Nordette", "16" => "16 Norinyl", "17" => "17 Nor-Q.D", "18" => "18 Ortho-Cept", "19 OrthoCyclen", "20" => "20 Ortho-Novum", "21" => "21 Ortho Tri-Cyclen", "22" => "22 Ovcon", "23" => "23 Ovral", "24 Tri-Levlen", "25 Tri-Norinyl", "26 Triphasil", "27 Trivora", "28 Zovia", "29 Other", "88 Refused", "99" => "99 Do not know"));
		$this->form->addElement('textarea', 'other', $this->indent . $this->indent . " If [Other], please specify:");

		$this->form->addRule(array('q4_9_p2_text', 'q4_9_p2'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'29'));
		$this->setRequired('q4_9_p2_text'); //*****************************

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q4_9_p3", $this->indent .  " Pill #3",  array(NULL=>"", "01" => "01 Alesse", "02" => "02 Brevicon", "03" => "03  Demulen", "04" => "04 Desogen", "05" => "05 Estrostep", "06" => "06 Levlen", "07" => "07 Levlite", "08" => "08 Levora", "09" => "09 Loestrin", "10" => "10 Lo/Ovral", "11" => "11 Micronor", "12" => "12 Mircette", "13" => "13 Modicon", "14" => "14 Necon", "15" => "15 Nordette", "16" => "16 Norinyl", "17" => "17 Nor-Q.D", "18" => "18 Ortho-Cept", "19 OrthoCyclen", "20" => "20 Ortho-Novum", "21" => "21 Ortho Tri-Cyclen", "22" => "22 Ovcon", "23" => "23 Ovral", "24 Tri-Levlen", "25 Tri-Norinyl", "26 Triphasil", "27 Trivora", "28 Zovia", "29 Other", "88 Refused", "99" => "99 Do not know"));
		$this->form->addElement('textarea', 'other', $this->indent . $this->indent . " If [Other], please specify:");

		$this->form->addRule(array('q4_9_p3_text', 'q4_9_p3'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'0'));
		$this->setRequired('q4_9_p3_text'); //*****************************

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q4_9_p4", $this->indent .  "Pill #4",  array(NULL=>"", "01" => "01 Alesse", "02" => "02 Brevicon", "03" => "03  Demulen", "04" => "04 Desogen", "05" => "05 Estrostep", "06" => "06 Levlen", "07" => "07 Levlite", "08" => "08 Levora", "09" => "09 Loestrin", "10" => "10 Lo/Ovral", "11" => "11 Micronor", "12" => "12 Mircette", "13" => "13 Modicon", "14" => "14 Necon", "15" => "15 Nordette", "16" => "16 Norinyl", "17" => "17 Nor-Q.D", "18" => "18 Ortho-Cept", "19 OrthoCyclen", "20" => "20 Ortho-Novum", "21" => "21 Ortho Tri-Cyclen", "22" => "22 Ovcon", "23" => "23 Ovral", "24 Tri-Levlen", "25 Tri-Norinyl", "26 Triphasil", "27 Trivora", "28 Zovia", "29 Other", "88 Refused", "99" => "99 Do not know"));
		$this->form->addElement('textarea', 'other', $this->indent . $this->indent . " If [Other], please specify:");

		$this->form->addRule(array('q4_9_p4_text', 'q4_9_p4'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'0'));
		$this->setRequired('q4_9_p4_text'); //*****************************

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q4_9_p5", $this->indent .  "Pill #5",  array(NULL=>"", "01" => "01 Alesse", "02" => "02 Brevicon", "03" => "03  Demulen", "04" => "04 Desogen", "05" => "05 Estrostep", "06" => "06 Levlen", "07" => "07 Levlite", "08" => "08 Levora", "09" => "09 Loestrin", "10" => "10 Lo/Ovral", "11" => "11 Micronor", "12" => "12 Mircette", "13" => "13 Modicon", "14" => "14 Necon", "15" => "15 Nordette", "16" => "16 Norinyl", "17" => "17 Nor-Q.D", "18" => "18 Ortho-Cept", "19 OrthoCyclen", "20" => "20 Ortho-Novum", "21" => "21 Ortho Tri-Cyclen", "22" => "22 Ovcon", "23" => "23 Ovral", "24 Tri-Levlen", "25 Tri-Norinyl", "26 Triphasil", "27 Trivora", "28 Zovia", "29 Other", "88 Refused", "99" => "99 Do not know"));
		$this->form->addElement('textarea', 'other', $this->indent . $this->indent . " If [Other], please specify:");

		$this->form->addRule(array('q4_9_p5_text', 'q4_9_p5'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'0'));
		$this->setRequired('q4_9_p5_text'); //*****************************


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>Use Pregnancy Calendar to answer the following.");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "4-10. Which months between [-3] and [DOPB] were you using [PILL NAME]?");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement ( "select", "q4_10_p1", "Pill #1:", $answerOptions, "multiple size='5'" );
		$this->form->addRule(array('q4_10_p1', 'q4_8'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q4_10_p1');

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement ( "select", "q4_10_p2", "Pill #2:", $answerOptions, "multiple" );

		$this->form->addRule(array('q4_10_p2', 'q4_9_p2'), 'Please specify.', 'requiredIf', array('operator'=>'!=', 'value'=>'NULL'));
		$this->setRequired('q4_10_p2');


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement ( "select", "q4_10_p3", "Pill #3:", $answerOptions, "multiple" );
		$this->form->addElement('static', null, "<br/>");
		$this->form->addRule(array('q4_10_p3', 'q4_9_p3'), 'Please specify.', 'requiredIf', array('operator'=>'!=', 'value'=>'NULL'));
		$this->setRequired('q4_10_p3');

		$this->form->addElement ( "select", "q4_10_p4", "Pill #4:", $answerOptions, "multiple" );
		$this->form->addRule(array('q4_10_p4', 'q4_9_p4'), 'Please specify.', 'requiredIf', array('operator'=>'!=', 'value'=>'NULL'));
		$this->setRequired('q4_10_p4');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement ( "select", "q4_10_p5", "Pill #5:", $answerOptions, "multiple" );
		$this->form->addRule(array('q4_10_p5', 'q4_9_p5'), 'Please specify.', 'requiredIf', array('operator'=>'!=', 'value'=>'NULL'));
		$this->setRequired('q4_10_p5');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q4_11", "4-11. Between [-3] and [DOPB], did you use any other method of
contraception to avoid getting pregnant?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));

		$this->setRequired('q4_11');
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "4-12. What method of contraception were you using?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, " If can't recall, ask to refer to List 3 in prep guide and choose from the following list:");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q4_12_m1", $this->indent .  "METHOD #1:",  array(NULL=>"", "01" => "01 Condoms (male or female)", "02" => "02 Depo-Provera", "03" => "03  Diaphram/cervical cap", "04" => "04 Intrauterine device (IUD)", "05" => "05 Norplant", "06" => "06 Spermicide", "07" => "07 Sponge", "08" => "08 Other", "88 Refused", "99" => "99 Do not know"));

		$this->form->addRule(array('q4_12_m1', 'q4_11'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q4_12_m1');

		$this->form->addElement('textarea', 'q4_12_m1_text', $this->indent . "If [Other], please specify:");

		$this->form->addRule(array('q4_12_m1_text', 'q4_12_m1'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'08'));
		$this->setRequired('q4_12_m1_text'); //*****************************

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q4_12_m2", $this->indent .  "METHOD #2:",  array(NULL=>"", "01" => "01 Condoms (male or female)", "02" => "02 Depo-Provera", "03" => "03  Diaphram/cervical cap", "04" => "04 Intrauterine device (IUD)", "05" => "05 Norplant", "06" => "06 Spermicide", "07" => "07 Sponge", "08" => "08 Other", "88 Refused", "99" => "99 Do not know"));

		$this->form->addElement('textarea', 'q4_12_m2_text', $this->indent . "If [Other], please specify:");

		$this->form->addRule(array('q4_12_m2_text', 'q4_12_m2'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'08'));
		$this->setRequired('q4_12_m2_text'); //*****************************


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q4_12_m3", $this->indent .  "METHOD #3:",  array(NULL=>"", "01" => "01 Condoms (male or female)", "02" => "02 Depo-Provera", "03" => "03  Diaphram/cervical cap", "04" => "04 Intrauterine device (IUD)", "05" => "05 Norplant", "06" => "06 Spermicide", "07" => "07 Sponge", "08" => "08 Other", "88 Refused", "99" => "99 Do not know"));

		$this->form->addElement('textarea', 'q4_12_m3_text', $this->indent . "If [Other], please specify:");

		$this->form->addRule(array('q4_12_m3_text', 'q4_12_m3'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'08'));
		$this->setRequired('q4_12_m3_text'); //*****************************

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "4-13. Which months between [-3]
and [DOPB] were you using
[CONTRACEPTIVE
METHOD]?");  

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "Met #1:");
		$this->form->addElement("select", "q4_13_m1", $this->indent . $this->indent . " Select all that apply from the following list:",  array(NULL=>"","-3", "-2", "-1", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" => "10", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addRule(array('q4_13_m1', 'q4_11'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q4_13_m1');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "Met #2:");
		$this->form->addElement("select", "q4_13_m2", $this->indent . $this->indent . " Select all that apply from the following list:",  array(NULL=>"","-3", "-2", "-1", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" => "10", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addRule(array('q4_13_m2', 'q4_12_m2'), 'This question is required', 'requiredIf', array('operator'=>'!=', 'value'=>'NULL'));
		$this->setRequired('q4_13_m2');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "Met #3:");
		$this->form->addElement("select", "q4_13_m3", $this->indent . $this->indent . " Select all that apply from the following list:",  array(NULL=>"","-3", "-2", "-1", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" => "10", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addRule(array('q4_13_m3', 'q4_12_m3'), 'This question is required', 'requiredIf', array('operator'=>'!=', 'value'=>'NULL'));
		$this->setRequired('q4_13_m3');

		$this->form->addElement('static', null, "4-14. If no contraceptives were used between [-3] and [DOPB] (i.e., 4-8 and 4-11 = No, Refused, or Do not know), then go to question 4-15");
		$this->form->addElement('static', null, $this->indent . "If any contraceptive was used between [-3] and [DOPB] (i.e., 4-8 or 4-11 = Yes), then go to
question 4-16");

		$this->form->addElement("select", "q4_", "4-15. Did you...",  array(NULL=>"", "01" => "01 Stop using contraception to get pregnant", "02" => "02 Get pregnant during an interruption in using contraception", "03" => "03  Not use contraception before this pregnancy", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addElement('static', null, $this->indent . "If [02 Get pregnant during an interruption in using contraception], go to question 4-31");

		$this->form->addElement("select", "q4_", "4-16. Did you get pregnant while consistently using contraception?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));

		$this->form->addElement('static', null, $this->indent . "If [Yes], go to question 4-19");

		$this->form->addElement("select", "q4_17", "4-17. Before getting pregnant with [PROBAND], did you have regular intercourse for a period of 12 months or more without using
contraception?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));

		$this->form->addRule(array('q4_17', 'q4_16'), 'This question is required', 'requiredIf', array('operator'=>'!=', 'value'=>'01'));
		$this->setRequired('q4_17');

		$this->form->addElement("select", "q4_18", "4-18. Did you use fertility treatment to get pregnant with [PROBAND]?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));

		$this->form->addRule(array('q4_18', 'q4_16'), 'This question is required', 'requiredIf', array('operator'=>'!=', 'value'=>'01'));
		$this->setRequired('q4_18');
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 4-31");


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/> <b/>Assisted Reproduction");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>Now I'm going to ask you some detailed questions about what type of help you or [PROBAND]'s
father may have received to help you get pregnant");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q4_19", "4-19. Did you take any medications to help prevent miscarriage with
your pregnancy with [PROBAND]?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));

		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 4-21");

		$this->form->addElement('static', null, "<br/>");

	}


	function _page7(){   // ========================================================

		// To implement Xin Rule

		$this->form->addFormRule(array(&$this,'XINValidate'));




		$this->form->addElement('static', null, "4-20. What medications did you take?");

		$this->form->addElement('static', null, $this->indent . "If respondent can't recall, ask to refer to List 4 in prep guide and ask to select from the following list:");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q4_20_m1", $this->indent. " Med #1:", array(NULL=>"", "01" => "01 Crinonevz", "02" => "02 Prometrium", "03" => "03  Heparin", "04" => "04 Baby aspirin", "05" => "05 IVIg Therapy", "07" => "07 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));


		$this->form->addRule(array('q4_20_m1', 'q4_19'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q4_20_m1');

		$this->form->addElement('textarea', 'q4_20_m1_text1', $this->indent . $this->indent. "If [06 Steroid treatmen], please specify:");

		$this->form->addRule(array('q4_20_m1_text1', 'q4_20_m1'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'06'));
		$this->setRequired('q4_20_m1_text1'); //*****************************

		$this->form->addElement('textarea', 'other', $this->indent . $this->indent . " If [Other], please specify:");

		$this->form->addRule(array('q4_20_m1_text2', 'q4_20_m1'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'07'));
		$this->setRequired('q4_20_m1_text2'); //*****************************


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q4_20_m2", $this->indent. " Med #2:", array(NULL=>"", "01" => "01 Crinonevz", "02" => "02 Prometrium", "03" => "03  Heparin", "04" => "04 Baby aspirin", "05" => "05 IVIg Therapy", "07" => "07 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));


		$this->form->addElement('textarea', 'q4_20_m2_text1', $this->indent . $this->indent . " If [06 Steroid treatmen], please specify:");

		$this->form->addRule(array('q4_20_m2_text1', 'q4_20_m2'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'06'));
		$this->setRequired('q4_20_m1_text1'); //*****************************


		$this->form->addElement('textarea', 'q4_20_m2_text2', $this->indent . $this->indent . " If [Other], please specify:");

		$this->form->addRule(array('q4_20_m2_text2', 'q4_20_m2'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'07'));
		$this->setRequired('q4_20_m2_text2'); //*****************************

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q4_20_m3", $this->indent. " Med #3:", array(NULL=>"", "01" => "01 Crinonevz", "02" => "02 Prometrium", "03" => "03  Heparin", "04" => "04 Baby aspirin", "05" => "05 IVIg Therapy", "07" => "07 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));


		$this->form->addElement('textarea', 'q4_20_m3_text1', $this->indent . $this->indent . " If [06 Steroid treatmen], please specify:");

		$this->form->addRule(array('q4_20_m3_text1', 'q4_20_m3'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'06'));
		$this->setRequired('q4_20_m3_text1'); //*****************************

		$this->form->addElement('textarea', 'q4_20_m3_text2', $this->indent . $this->indent . " If [Other], please specify:");


		$this->form->addRule(array('q4_20_m3_text2', 'q4_20_m3'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'07'));
		$this->setRequired('q4_20_m3_text2'); //*****************************

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q4_", "4-21. Did you take any medications to help you become pregnant with [PROBAND]? ",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 4-23");


		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "4-22. What medications did you take?");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null,  $this->indent . "Probe: Are there any more medications?
If can't recall, ask them to refer to List 5 in prep guide and choose from the following list:");     

		$this->form->addElement("select", "q4_22_1", $this->indent . $this->indent . " Med #1",  array(NULL=>"", "01" => "01 Bromocriptine", "02" => "02 Clomid", "03" => "03  Chorionic gonadotropin", "04" => "04 Clomiphene citrate", "05" => "05 Danazol", "05" => "05 Danocrine", "06" => "06 Dostinex", "07" => "07 Factrel", "08" => "08 Fertinex", "09" => "09 Follistim", "10" => "10 Gonadorelin", "11" => "11 Gonal-F", "12" => "12 Humegon", "13" => "13 Lupron", "14" => "14 Lutrepulse", "16" => "16 Metrodin", "17" => "17 Novarel", "18" => "18 Parlodel", "19" => "19 Pergonal", "20" => "20 Pregnyl", "21" => "21 Profasi HP", "22" => "22 Provera", "23" => "23 Repronex", "24 Serophene", "25 Synarel", "26" => "26 Other", "88 Refused", "99" => "99 Do not know"));


		$this->form->addRule(array('q4_22_1', 'q4_21'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q4_22_1');

		$this->form->addElement('textarea', 'q4_22_1_t', $this->indent . $this->indent . " If [Other], please specify. Drug #1:");

		$this->form->addRule(array('q4_22_1_t', 'q4_22_1'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'26'));
		$this->setRequired('q4_22_1_t'); //*****************************


		$this->form->addElement("select", "q4_22_2", $this->indent . $this->indent . " Med #2",  array(NULL=>"", "01" => "01 Bromocriptine", "02" => "02 Clomid", "03" => "03  Chorionic gonadotropin", "04" => "04 Clomiphene citrate", "05" => "05 Danazol", "05" => "05 Danocrine", "06" => "06 Dostinex", "07" => "07 Factrel", "08" => "08 Fertinex", "09" => "09 Follistim", "10" => "10 Gonadorelin", "11" => "11 Gonal-F", "12" => "12 Humegon", "13" => "13 Lupron", "14" => "14 Lutrepulse", "16" => "16 Metrodin", "17" => "17 Novarel", "18" => "18 Parlodel", "19" => "19 Pergonal", "20" => "20 Pregnyl", "21" => "21 Profasi HP", "22" => "22 Provera", "23" => "23 Repronex", "24 Serophene", "25 Synarel", "26 Other", "88 Refused", "99" => "99 Do not know"));
		$this->form->addElement('textarea', 'q4_22_2_t', $this->indent . $this->indent . " If [Other], please specify. Drug #2:");

		$this->form->addRule(array('q4_22_2_t', 'q4_22_2'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'26'));
		$this->setRequired('q4_22_2_t'); //*****************************


		$this->form->addElement("select", "q4_22_3", $this->indent . $this->indent . " Med #3",  array(NULL=>"", "01" => "01 Bromocriptine", "02" => "02 Clomid", "03" => "03  Chorionic gonadotropin", "04" => "04 Clomiphene citrate", "05" => "05 Danazol", "05" => "05 Danocrine", "06" => "06 Dostinex", "07" => "07 Factrel", "08" => "08 Fertinex", "09" => "09 Follistim", "10" => "10 Gonadorelin", "11" => "11 Gonal-F", "12" => "12 Humegon", "13" => "13 Lupron", "14" => "14 Lutrepulse", "16" => "16 Metrodin", "17" => "17 Novarel", "18" => "18 Parlodel", "19" => "19 Pergonal", "20" => "20 Pregnyl", "21" => "21 Profasi HP", "22" => "22 Provera", "23" => "23 Repronex", "24 Serophene", "25 Synarel", "26 Other", "88 Refused", "99" => "99 Do not know"));
		$this->form->addElement('textarea', 'q4_22_3_t', $this->indent . $this->indent . " If [Other], please specify. Drug #3:");

		$this->form->addRule(array('q4_22_3_t', 'q4_22_3'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'26'));
		$this->setRequired('q4_22_3_t'); //*****************************


		$this->form->addElement("select", "q4_22_4", $this->indent . $this->indent . " Med #4",  array(NULL=>"", "01" => "01 Bromocriptine", "02" => "02 Clomid", "03" => "03  Chorionic gonadotropin", "04" => "04 Clomiphene citrate", "05" => "05 Danazol", "05" => "05 Danocrine", "06" => "06 Dostinex", "07" => "07 Factrel", "08" => "08 Fertinex", "09" => "09 Follistim", "10" => "10 Gonadorelin", "11" => "11 Gonal-F", "12" => "12 Humegon", "13" => "13 Lupron", "14" => "14 Lutrepulse", "16" => "16 Metrodin", "17" => "17 Novarel", "18" => "18 Parlodel", "19" => "19 Pergonal", "20" => "20 Pregnyl", "21" => "21 Profasi HP", "22" => "22 Provera", "23" => "23 Repronex", "24 Serophene", "25 Synarel", "26 Other", "88 Refused", "99" => "99 Do not know"));
		$this->form->addElement('textarea', 'q4_22_4_t', $this->indent . $this->indent . " If [Other], please specify. Drug #4:");

		$this->form->addRule(array('q4_22_4_t', 'q4_22_4'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'26'));
		$this->setRequired('q4_22_4_t'); //*****************************

		$this->form->addElement("select", "q4_22_5", $this->indent . $this->indent . " Med #5",  array(NULL=>"", "01" => "01 Bromocriptine", "02" => "02 Clomid", "03" => "03  Chorionic gonadotropin", "04" => "04 Clomiphene citrate", "05" => "05 Danazol", "05" => "05 Danocrine", "06" => "06 Dostinex", "07" => "07 Factrel", "08" => "08 Fertinex", "09" => "09 Follistim", "10" => "10 Gonadorelin", "11" => "11 Gonal-F", "12" => "12 Humegon", "13" => "13 Lupron", "14" => "14 Lutrepulse", "16" => "16 Metrodin", "17" => "17 Novarel", "18" => "18 Parlodel", "19" => "19 Pergonal", "20" => "20 Pregnyl", "21" => "21 Profasi HP", "22" => "22 Provera", "23" => "23 Repronex", "24 Serophene", "25 Synarel", "26 Other", "88 Refused", "99" => "99 Do not know"));
		$this->form->addElement('textarea', 'q4_22_5_t', $this->indent . $this->indent . " If [Other], please specify. Drug #5:");

		$this->form->addRule(array('q4_22_5_t', 'q4_22_5'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'26'));
		$this->setRequired('q4_22_5_t'); //*****************************


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q4_23", "4-23. Did you have any other procedures to help you become pregnant with
[PROBAND]?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->setRequired('q4_23');
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know], then:");

		$this->form->addElement('static', null, $this->indent . $this->indent . " If child's biological father known, then go to 4-27");

		$this->form->addElement('static', null, $this->indent . $this->indent . " If child's biological father is unknown, then go to 4-31");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "4-24. I'm going to read you a list of procedures. Please tell me if you
received any of these to help you get pregnant with [PROBAND].");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If can't recall, ask them to refer to List 6 in prep guide.");
		$this->form->addElement('static', null, $this->indent . "For each procedure coded in 4-24, ask questions 4-25 thru 4-26.");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q4_24_p1", $this->indent . "PROC #1:",  array(NULL=>"", "01" => "01 Artificial insemination or intrauterine insemination", "02" => "02 In vitro fertilization- embryo transfer (IVF-ET)", "03" => "03  Gamete intrafallopian transfer (GIFT)", "04" => "04 Zygote intrafallopian transfer (ZIFT)", "05" => "05 Intracytoplasmic sperm injection (ICSI)", "06" => "06 Frozen embryo transfer", "07" => "07 Tubal embryo transfer (TET)", "08" => "08 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addRule(array('q4_24_p1', 'q4_23'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q4_24_p1');

		$this->form->addElement('textarea', 'q4_24_p1_other', $this->indent . $this->indent . " If [Other], please specify. OTHER PROC #1:");
		$this->form->addRule(array('q4_24_p1_other', 'q4_24_p1'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'08'));
		$this->setRequired('q4_24_p1_other');


		$this->form->addElement('static', null, $this->indent . $this->indent . " If [Refused] or [Don't Know], then:");

		$this->form->addElement('static', null, $this->indent . $this->indent . " $this->indent If child's biological father known, then go to 4-27");

		$this->form->addElement('static', null, $this->indent . $this->indent . " $this->indent If child's biological father is unknown, then go to 4-31");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q4_24_p2", $this->indent . "PROC #2:",  array(NULL=>"", "01" => "01 Artificial insemination or intrauterine insemination", "02" => "02 In vitro fertilization- embryo transfer (IVF-ET)", "03" => "03  Gamete intrafallopian transfer (GIFT)", "04" => "04 Zygote intrafallopian transfer (ZIFT)", "05" => "05 Intracytoplasmic sperm injection (ICSI)", "06" => "06 Frozen embryo transfer", "07" => "07 Tubal embryo transfer (TET)", "08" => "08 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));


		$this->form->addElement('textarea', 'q4_24_p2_other', $this->indent . $this->indent . " If [Other], please specify. OTHER PROC #2:");
		$this->form->addRule(array('q4_24_p2_other', 'q4_24_p2'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'08'));
		$this->setRequired('q4_24_p2_other');


		$this->form->addElement('static', null, $this->indent . $this->indent . " If [Refused] or [Don't Know], then:");

		$this->form->addElement('static', null, $this->indent . $this->indent . " $this->indent If child's biological father known, then go to 4-27");

		$this->form->addElement('static', null, $this->indent . $this->indent . " $this->indent If child's biological father is unknown, then go to 4-31");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q4_24_p3", $this->indent . "PROC #3:",  array(NULL=>"", "01" => "01 Artificial insemination or intrauterine insemination", "02" => "02 In vitro fertilization- embryo transfer (IVF-ET)", "03" => "03  Gamete intrafallopian transfer (GIFT)", "04" => "04 Zygote intrafallopian transfer (ZIFT)", "05" => "05 Intracytoplasmic sperm injection (ICSI)", "06" => "06 Frozen embryo transfer", "07" => "07 Tubal embryo transfer (TET)", "08" => "08 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addElement('textarea', 'q4_24_p3_other', $this->indent . $this->indent . " If [Other], please specify. OTHER PROC #3:");

		$this->form->addRule(array('q4_24_p3_other', 'q4_24_p3'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'08'));
		$this->setRequired('q4_24_p3_other');

		$this->form->addElement('static', null, $this->indent . $this->indent . " If [Refused] or [Don't Know], then:");

		$this->form->addElement('static', null, $this->indent . $this->indent . " $this->indent If child's biological father known, then go to 4-27");

		$this->form->addElement('static', null, $this->indent . $this->indent . " $this->indent If child's biological father is unknown, then go to 4-31");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "4-25. Were donor eggs, sperm or embryos used?");

		$this->form->addElement('static', null, $this->indent .  "Using the same PROC codes as in 4-24, choose the appropriate answer for each item.");


		$oneToThree = array("1"=>"#1", "2"=>"#2", "3"=>"#3");
		reset($oneToThree);

		while(list($field, $label) = each($oneToThree)){

			$this->form->addElement('static', null, "<br/>");

			$this->form->addElement('static', null, $this->indent . "PROC {$label}:");

			$this->form->addElement("select", "eggs_{$field}", $this->indent . $this->indent . " Eggs:", array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "98" => "98 Refused", "99" => "99 Do not know", "Not_Answered" => "Not Answered"));

			$this->form->addElement("select", "sperm_{$field}", $this->indent . $this->indent . " Sperm:", array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "98" => "98 Refused", "99" => "99 Do not know", "Not_Answered" => "Not Answered"));
			$this->form->addElement("select", "embryo_{$field}", $this->indent . $this->indent . " Embryo:", array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "98" => "98 Refused", "99" => "99 Do not know", "Not_Answered" => "Not Answered"));
		}
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "4-26. Were frozen eggs, sperm or embryos used?");

		$this->form->addElement('static', null, $this->indent .  "Using the same PROC codes as in 4-24, choose the appropriate answer for each item.");


		$oneToThree = array("1"=>"#1", "2"=>"#2", "3"=>"#3");
		reset($oneToThree);

		while(list($field, $label) = each($oneToThree)){

			$this->form->addElement('static', null, "<br/>");

			$this->form->addElement('static', null, $this->indent . "OTHER PROC {$label}:");

			$this->form->addElement("select", "eggs_{$field}", $this->indent . $this->indent . " Eggs:", array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "98" => "98 Refused", "99" => "99 Do not know", "Not_Answered" => "Not Answered"));

			$this->form->addElement("select", "sperm_{$field}", $this->indent . $this->indent . " Sperm:", array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "98" => "98 Refused", "99" => "99 Do not know", "Not_Answered" => "Not Answered"));
			$this->form->addElement("select", "embryo_{$field}", $this->indent . $this->indent . " Embryo:", array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "98" => "98 Refused", "99" => "99 Do not know", "Not_Answered" => "Not Answered"));
		}


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>If [PROBAND]'s biological father is unknown, then go to 4-31");




		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q4_27", "4-27. Did [PROBAND]'s father take any medications to help you become
pregnant?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));

		$this->form->addRule(array('q4_27', 'q1_15a'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01_yes'));
		$this->setRequired('q4_27');

		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 4-29");

		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "4-28. What medications did he take?");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null,  $this->indent . "Probe: Are there any more medications?
If can't recall, ask them to refer to List 5 in prep guide and choose from the following list:");     
		$this->form->addElement('static', null, "<br/>");

		$oneToEight = array("1"=>"#1", "2"=>"#2", "3"=>"#3", "#4"=>"#4", "5"=>"#5", "6"=>"#6", "7"=>"#7", "8"=>"#8");
		reset($oneToEight);

		while(list($field, $label) = each($oneToEight)){

			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement("select", "q4_28_{$field}", $this->indent . $this->indent . " Med {$label}:",  array(NULL=>"", "01" => "01 Bromocriptine", "02" => "02 Clomid", "03" => "03  Chorionic gonadotropin", "04" => "04 Clomiphene citrate", "05" => "05 Danazol", "05" => "05 Danocrine", "06" => "06 Dostinex", "07" => "07 Factrel", "08" => "08 Fertinex", "09" => "09 Follistim", "10" => "10 Gonadorelin", "11" => "11 Gonal-F", "12" => "12 Humegon", "13" => "13 Lupron", "14" => "14 Lutrepulse", "16" => "16 Metrodin", "17" => "17 Novarel", "18" => "18 Parlodel", "19" => "19 Pergonal", "20" => "20 Pregnyl", "21" => "21 Profasi HP", "22" => "22 Provera", "23" => "23 Repronex", "24 Serophene", "25 Synarel", "26 Other", "88 Refused", "99" => "99 Do not know"));
			$this->form->addElement('textarea', 'other', $this->indent . $this->indent . " If [Other], please specify. Drug {$label}:");


		}
		$this->form->addRule(array('q4_28_1', 'q4_27'), 'This field is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q4_28_1');
		$this->form->addElement("select", "q4_29", "4-29. Did [PROBAND]'s father have any procedures or surgeries to help you
become pregnant?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));

		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 4-31");

		$this->form->addElement('static', null, "<br/>");

		$this->setRequired('q4_29');

		$this->form->addElement('static', null, "4-30. What was the procedure?");


		$this->form->addElement("select", "q4_30_p1",  $this->indent . $this->indent . "Procedure #1:",  array(NULL=>"",  "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addElement('textarea', 'q4_30_proc1', $this->indent . "If [00 Specify] please specify PROC #1:");

		$this->form->addRule(array('q4_30_p1', 'q4_29'), 'This field is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q4_30_p1');

		$this->form->addRule(array('q4_30_proc1', 'q4_30_p1'), 'This field is required', 'requiredIf', array('operator'=>'==', 'value'=>'00'));
		$this->setRequired('q4_30_proc1');

		$this->form->addElement("select", "q4_30_p2",  $this->indent . $this->indent . "Procedure #1:",  array(NULL=>"",  "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addElement('textarea', 'q4_30_proc2', $this->indent . "If [00 Specify] please specify PROC #2:");
		$this->form->addRule(array('q4_30_proc2', 'q4_30_p2'), 'This field is required', 'requiredIf', array('operator'=>'==', 'value'=>'00'));
		$this->setRequired('q4_30_proc2');


		$this->form->addElement("select", "q4_30_p3",  $this->indent . $this->indent . "Procedure #1:",  array(NULL=>"",  "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));


		$this->form->addElement('textarea', 'q4_30_proc3', $this->indent . "If [00 Specify] please specify PROC #3:");

		$this->form->addRule(array('q4_30_proc3', 'q4_30_p3'), 'This field is required', 'requiredIf', array('operator'=>'==', 'value'=>'00'));
		$this->setRequired('q4_30_proc3');

		$this->form->addElement('static', null, "<br/>");




	}


	function _page8(){   // ========================================================

		// To implement Xin Rule

		$this->form->addFormRule(array(&$this,'XINValidate'));



		$this->form->addElement('static', null, "(<b/>Morning Sickness)");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Now I have some more detailed questions about your pregnancy with [PROBAND]. You will need
to look at your pregnancy calendar for [PROBAND].");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q4_31", "4-31. During the pregnancy with [PROBAND] did you have any nausea?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));

		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 4-34");

		$this->form->addElement('static', null, "<br/>");

		unset($negThreeToTen[0]);
		$answerOptions = array(null=>"") + ($negThreeToTen) + array("88_Refused" => "88 Refused", "99_Do_not_know" => "99 Do not know", "not_answered" => "Not Answered");
		$this->form->addElement ( "select", "q4_32", "4-32. During which months did you have nausea?", $answerOptions, "multiple" );
		$this->XINRegisterRule('q4_32', array("q4_31{@}=={@}01_yes"), "This is required if there was nausea.");  //This rule doesn't work on multiple selects.




		$this->form->addElement ( 'static', null, "4-33. How often during [SPECIFY MONTH] did you have nausea?" );
		$group[] =&$this->form->createElement("static", "month_header");
		$group[] =&$this->form->createElement("static", "freq_header");
		$this->form->addGroup($group, "q4_33_headers", "Would you say it was...", $this->_GUIDelimiter, false);
		unset($group);

		unset($negThreeToTen[10]); //only want to go up to 9
		$aToF = array("a", "b", "c", "d", "e", "f");
		foreach($aToF as $label) {
			$group[] = &$this->form->createElement( "select", "q4_33_m_{$label}", null, array (NULL => "") + $negThreeToTen + array("not_answered" => "Not Answered"));
			$group[] = &$this->form->createElement ( "select", "q4_33_f_{$label}", null, array (NULL => "", "01" => "01 Less than once a week", "02" => "02 Once a week", "03" => "03  A few times a week", "04" => "04 Every day", "88 Refused", "99" => "99 Do not know" ) );
			$this->form->addGroup($group, "q4_33_{$label}_group", "{$label})", $this->_GUIDelimiter, false);
			unset($group);
			//Don't require all questions, but allow them to be filled in, if desired.
			if ($label=="a") continue; //Special rules apply to the first month
			$this->XINRegisterRule("q4_33_m_{$label}", array("q4_31{@}=={@}NEVER_REQUIRED"));
			$this->XINRegisterRule("q4_33_f_{$label}", array("q4_31{@}=={@}NEVER_REQUIRED"));
		}
		//Only require the first month to be answered, if there was nausea.  Trust that the rest will be filled in as needed.
		$this->XINRegisterRule("q4_33_m_a", array("q4_31{@}=={@}01_yes"), "This is required if there was nausea", "q4_33_a_group");
		$this->XINRegisterRule("q4_33_f_a", array("q4_31{@}=={@}01_yes"), "This is required if there was nausea", "q4_33_a_group");




		$this->form->addElement("select", "q4_", "4-34. During the pregnancy with [PROBAND] did you have any vomiting?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->setRequired('q4_34');

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 4-39");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");


		$negThreeToTen = array_combine(range(-3, 10), range(-3, 10));
		unset($negThreeToTen[0]);
		$answerOptions = array(null=>"") + ($negThreeToTen) + array("88_Refused" => "88 Refused", "99_Do_not_know" => "99 Do not know", "not_answered" => "Not Answered");
		$this->form->addElement ( "select", "q4_35", "4-35. During which months did you vomit? Choose all that apply:", $answerOptions, "multiple" );
		$this->XINRegisterRule('q4_35', array("q4_34{@}=={@}01_yes"), "This is required if there was nausea.");  //This rule doesn't work on multiple selects.



		$this->form->addElement ( 'static', null, "4-36. How often during [SPECIFY MONTH] did you vomit?" );
		$group[] =&$this->form->createElement("static", "month_header");
		$group[] =&$this->form->createElement("static", "freq_header");
		$this->form->addGroup($group, "q4_36_headers", "Would you say it was...", $this->_GUIDelimiter, false);
		unset($group);

		unset($negThreeToTen[10]); //only want to go up to 9
		$aToF = array("a", "b", "c", "d", "e", "f");
		foreach($aToF as $label) {
			$group[] = &$this->form->createElement( "select", "q4_36_m_{$label}", null, array (NULL => "") + $negThreeToTen + array("not_answered" => "Not Answered"));
			$group[] = &$this->form->createElement ( "select", "q4_36_f_{$label}", null, array (NULL => "", "01" => "01 Less than once a week", "02" => "02 Once a week", "03" => "03  A few times a week", "04" => "04 Every day", "88 Refused", "99" => "99 Do not know" ) );
			$this->form->addGroup($group, "q4_36_{$label}_group", "{$label})", $this->_GUIDelimiter, false);
			unset($group);
			//Don't require all questions, but allow them to be filled in, if desired.
			if ($label=="a") continue; //Special rules apply to the first month
			$this->XINRegisterRule("q4_36_m_{$label}", array("q4_34{@}=={@}NEVER_REQUIRED"));
			$this->XINRegisterRule("q4_36_f_{$label}", array("q4_34{@}=={@}NEVER_REQUIRED"));
		}
		//Only require the first month to be answered, if there was vomiting.  Trust that the rest will be filled in as needed.
		$this->XINRegisterRule("q4_36_m_a", array("q4_34{@}=={@}01_yes"), "This is required if there was vomiting", "q4_36_a_group");
		$this->XINRegisterRule("q4_36_f_a", array("q4_34{@}=={@}01_yes"), "This is required if there was vomiting", "q4_36_a_group");




		$this->form->addElement('static', null, $this->indent . "If nausea or vomiting occurred during pregnancy (i.e., 4-31 or 4-34 = [Yes]), then go to 4-37.");


		$this->form->addElement('static', null, $this->indent . "If no nausea or vomiting occurred during pregnancy (i.e 4-31 and 4-34 = [No] or [Refused] or [Don't Know]), then go to  4-39.");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q4_37", "4-37. Did you ever require medical treatment for the nausea or vomiting?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));

		$this->form->addRule(array('q4_37', 'q4_31'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q4_37');

		$this->form->addRule(array('q4_37', 'q4_34'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q4_37');

		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 4-39");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "4-38. What medicine/treatment did you take? Was it...");


		$oneToThree = array("1"=>"#1", "2"=>"#2", "3"=>"#3");
		reset($oneToThree);

		while(list($field, $label) = each($oneToThree)){

			$this->form->addElement('static', null, "<br/>");


			$this->form->addElement("select", "q4_38_med_{$field}", $this->indent . "MED {$label}:", array(NULL=>"", "01" => "01 Vitamin B6 (pyridoxine)", "02" => "02 Unisom (doxylamine)", "03" => "03  Emetrol", "04" => "04 Ginger", "05" => "05 Other",  "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

			$this->form->addElement('textarea', 'q4_38_med_{$field}_other', $this->indent . "If [Other], please specify:");

			$this->form->addRule(array('q4_38_med_{$field}_other', 'q4_37_med_{$field}'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'05'));
			$this->setRequired('q4_38_med_{$field}_other'); //*****************************


		}

		$this->form->addRule(array('q4_38_med_1', 'q4_37'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q4_38_med_1');


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/Prenatal Care>");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q4_39",  "4-39. During your pregnancy with [PROBAND], how many ultrasounds did you
have?",  array(NULL=>"",  "0", "1" => "1", "2" => "2", "3" => "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->setRequired('q4_39');

		$this->form->addElement("select", "q4_40", "4-40. Did you have an Amniocentesis or amnio?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 4-43");


		$this->setRequired('q4_40');


		$this->form->addElement("select", "q4_41", $this->indent . "4-41. When was it done?",  array(NULL=>"", "00_sd" => "00 Specify date", "00_sw" => "00 Specify gestational weeks", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));   // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('date', 'q4_41_date', "If [00 Specify date] please specify date:", $dateOptions);

		$this->form->addElement("select", "q4_41_week", "If [00 Specify gestational weeks] please specify weeks:" ,array(NULL=>"", "1", "2", "3", "4", "5", "6", "7", "8", "9","10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21" => "21", "22", "23" => "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "36", "37", "38", "39", "40", "41", "42", "43", "44", "45"));


		$this->form->addRule(array('q4_41', 'q4_40'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q4_41');

		$this->form->addRule(array('q4_41_date', 'q4_41'), 'Please specify', 'requiredIf', array('operator'=>'==', 'value'=>'00_sd'));
		$this->setRequired('q4_41_date');

		$this->form->addRule(array('q4_41_week', 'q4_41'), 'Please specify', 'requiredIf', array('operator'=>'==', 'value'=>'00_sw'));
		$this->setRequired('q4_41_week');


		$this->form->addElement("select", "q4_42", "4-42. Were there any abnormalities detected?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addRule(array('q4_42', 'q4_40'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q4_42');

		$this->form->addElement("select", "q4_", "4-43. Did you have Chorionic Villus Sampling or CVS?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 4-46");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q4_44", "4-44. When was it done?",  array(NULL=>"",  "00_sd" => "00 Specify date", "00_sw" => "00 Specify gestational weeks", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));   // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
		$this->form->addElement('date', 'q4_44_date', "If [00 Specify date] please specify date:", $dateOptions);

		$this->form->addElement("select", "q4_44_week", "If [00 Specify gestational weeks] please specify weeks:" ,array(NULL=>"", "1", "2", "3", "4", "5", "6", "7", "8", "9","10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21" => "21", "22", "23" => "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "36", "37", "38", "39", "40", "41", "42", "43", "44", "45"));
		$this->form->addRule(array('q4_44', 'q4_43'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q4_44');

		$this->form->addRule(array('q4_44_date', 'q4_44'), 'Please specify', 'requiredIf', array('operator'=>'==', 'value'=>'00_sd'));
		$this->setRequired('q4_44_date');

		$this->form->addRule(array('q4_44_week', 'q4_44'), 'Please specify', 'requiredIf', array('operator'=>'==', 'value'=>'00_sw'));
		$this->setRequired('q4_44_week');


		$this->form->addElement("select", "q4_", "4-45. Were there any abnormalities detected?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addRule(array('q4_45', 'q4_43'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q4_45');


		$this->form->addElement("select", "q4_46", "4-46. Were you told that there was [rhesus] or [Rh] incompatibility between you
and [PROBAND]?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 4-50");
		$this->setRequired('q4_46');
		$this->form->addElement("select", "q4_47", "4-47. If your blood type is Rh-, during pregnancy you might have been given
injections of Rhogam. Did you receive any Rhogam injections while you
were pregnant with [PROBAND]?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));

		$this->form->addRule(array('q4_47', 'q4_46'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q4_47');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Ask if pregnant more than twice (including younger sibling of child with ASD) (i.e.,
question 3-4 > 2)");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q4_48", "4-48. Did you receive Rhogam injections for any other pregnancy (other than the
pregnancy with [PROBAND] or [SIBLING]?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addRule(array('q4_48', 'q4_46'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q4_48');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q4_49", "4-49. Were there any problems with [PROBAND] because of the rhesus
incompatibility?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addRule(array('q4_49', 'q4_46'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q4_49');

		$this->form->addElement('textarea', 'q4_49_text', $this->indent . "If [Yes], please specify:");

		$this->form->addRule(array('q4_49_text', 'q4_49'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q4_49_text'); //*****************************


		$this->form->addElement("select", "q4_50", "4-50. During your pregnancy with [PROBAND], did you receive shots or
immunizations such as",  array(NULL=>"", "01" => "01 Immunoglobulin injection (other than RhoGam)?", "02" => "02 No ", "03" => "03  Other", "05" => "05 Flu Shot", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addElement('textarea', 'q4_50_text', $this->indent . "If [Other], please specify:");

		$this->form->addRule(array('q4_50_text', 'q4_q4_50'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'03'));
		$this->setRequired('q4_50_text'); //*****************************



		$this->form->addElement('header', null, "Section 4. PROBAND PREGNANCY");

		$this->form->addElement('header', null, "(Part 2)");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Vaginal Douching");
		$this->form->addElement('static', null, "<b/>Refer to the pregnancy calendar for the following questions.");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q4_51", "4-51. Did you ever douche between [-3] and [DOPB]?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 4-54");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "4-52. Between [-3] and [DOPB], which months did you douche?");

		$this->form->addElement("select", "q4_52",  $this->indent . " Choose all that apply:",  array(NULL=>"","-3", "-2", "-1", "01", "02", "03" => "03 ", "04" => "04", "05" => "05", "06" => "06", "07" => "07", "08" => "08", "09" => "09",  "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered" => "Not Answered"));

		$this->form->addElement('static', null, $this->indent . "If [Refused] or [Don't Know] skip to question 4-54");
		$this->form->addRule(array('q4_52', 'q4_51'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q4_52');

		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement ( 'static', null, "4-53. On average, how often would you say you douched during [SPECIFY MONTH]?" );
		$group[] =&$this->form->createElement("static", "month_header");
		$group[] =&$this->form->createElement("static", "freq_header");
		$this->form->addGroup($group, "q4_53_headers", "Would you say it was...", $this->_GUIDelimiter, false);
		unset($group);

		unset($negThreeToTen[10]); //only want to go up to 9
		$aToF = array("a", "b", "c", "d", "e", "f");
		foreach($aToF as $label) {
			$group[] = &$this->form->createElement( "select", "q4_53_m_{$label}", null, array (NULL => "") + $negThreeToTen + array("not_answered" => "Not Answered"));
			$group[] = &$this->form->createElement ( "select", "q4_53_f_{$label}", null, array (NULL => "", "01" => "01 Less than once a week", "02" => "02 Once a week", "03" => "03  A few times a week", "04" => "04 Every day", "88 Refused", "99" => "99 Do not know" ) );
			$this->form->addGroup($group, "q4_53_{$label}_group", "{$label})", $this->_GUIDelimiter, false);
			unset($group);
			//Don't require all questions, but allow them to be filled in, if desired.
			if ($label=="a") continue; //Special rules apply to the first month
			$this->XINRegisterRule("q4_53_m_{$label}", array("q4_51{@}=={@}NEVER_REQUIRED"));
			$this->XINRegisterRule("q4_53_f_{$label}", array("q4_51{@}=={@}NEVER_REQUIRED"));
		}
		//Only require the first month to be answered, if there was douching.  Trust that the rest will be filled in as needed.
		$this->XINRegisterRule("q4_53_m_a", array("q4_51{@}=={@}01_yes"), "This is required if there was douching", "q4_53_a_group");
		$this->XINRegisterRule("q4_53_f_a", array("q4_51{@}=={@}01_yes"), "This is required if there was douching", "q4_53_a_group");




	}

	function _page9(){   // ========================================================

		// To implement Xin Rule

		$this->form->addFormRule(array(&$this,'XINValidate'));



		$this->form->addElement('static', null, "<b/>Maternal Medical Conditions");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q4_54", "4-54. During your pregnancy with [PROBAND] were you ever told by a
physician or nurse that you had preeclampsia or toxemia?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 4-56");
		$this->setRequired('q4_');
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q4_55", "4-55. Did you take any medicine for preeclampsia or toxemia?", array(NULL=>"", "01_yes" => "01 Yes", "02_no" => "02 No", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 4-56");
		$this->form->addRule(array('q4_55', 'q4_54'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q4_55');
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q4_56", "4-56. During your pregnancy with [PROBAND] were you ever told by a
physician or nurse that you had premature labor?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 4-59");
		$this->setRequired('q4_56');
		$this->form->addElement('static', null, "<br/>");



		$OneToNine = array_combine(range(1, 9), range(1, 9));
		$answerOptions = array(null=>"") + ($OneToNine) + array("88_Refused" => "88 Refused", "99_Do_not_know" => "99 Do not know", "not_answered" => "Not Answered");
		$this->form->addElement ( "select", "q4_57", "4-57. During which months of the pregnancy did you have the
premature labor?", $answerOptions, "multiple" );
		$this->XINRegisterRule('q4_57', array("q4_56{@}=={@}01_yes"), "This is required if there was nausea.");  //This rule doesn't work on multiple selects.



		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q4_58", "4-58. Did you take any medicine for premature labor?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addRule(array('q4_58', 'q4_56'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q4_58');

		$this->form->addElement("select", "q4_59", "4-59. During your pregnancy with [PROBAND] did you have vaginal bleeding?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 4-62");
		$this->setRequired('q4_59');

		$this->form->addElement('static', null, "<br/>");

		$OneToNine = array_combine(range(1, 9), range(1, 9));
		$answerOptions = array(null=>"") + ($OneToNine) + array("88_Refused" => "88 Refused", "99_Do_not_know" => "99 Do not know", "not_answered" => "Not Answered");
		$this->form->addElement ( "select", "q4_60", "4-60. During which months of pregnancy did you have the
bleeding?", $answerOptions, "multiple" );
		$this->XINRegisterRule('q4_60', array("q4_59{@}=={@}01_yes"), "This is required if there was bleeding.");  //This rule doesn't work on multiple selects.



		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q4_61", "4-61. Did you take any medicine for the bleeding?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addRule(array('q4_61', 'q4_59'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q4_61');


		$this->form->addElement("select", "q4_62", "4-62 During your pregnancy with [PROBAND] were you ever told by a
physician or nurse that you had gestational diabetes?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 4-65");
		$this->setRequired('q4_62');
		$this->form->addElement('static', null, "<br/>");



		$OneToNine = array_combine(range(1, 9), range(1, 9));
		$answerOptions = array(null=>"") + ($OneToNine) + array("88_Refused" => "88 Refused", "99_Do_not_know" => "99 Do not know", "not_answered" => "Not Answered");
		$this->form->addElement ( "select", "q4_63", "4-63. During which months did you have the gestational
diabetes?", $answerOptions, "multiple" );
		$this->XINRegisterRule('q4_63', array("q4_62{@}=={@}01_yes"), "This is required if there was gestational diabetes.");  //This rule doesn't work on multiple selects.




		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q4_64", "4-64. Did you take any medicine for gestational diabetes?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 4-65");
		$this->form->addRule(array('q4_64', 'q4_62'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q4_64');

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/Now, I am going to ask you about some illnesses, surgeries and other procedures that you might
have had during your pregnancy with [PROBAND]. I'm going to ask you about the time period
from three months before you became pregnant with [PROBAND] until [HIS/HER] delivery.>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Reproductive and Major Perinatal Infections");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>I am going to start off by asking you about some infections that you might have had during that
pregnancy.");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "4-65. Between [-3] and [DOPB] did you have any
of the following infections?");


		$aToX = array("a. Bacterial Vaginosis" => "A. Bacterial Vaginosis", "b. Candidiasis" => "B. Candidiasis", "c. Chlamydia" => "C. Chlamydia", "d. Chicken pox" => "D. Chicken pox", "e. Cytomegalovirus" => "E. Cytomegalovirus", "f. Genital Herpes" => "F. Genital Herpes", "g. Group B Streptococcal infection" =>"G. Group B Streptococcal infection", "h. Hepatitis A" =>"H. Hepatitis A", "i. Hepatitis B" =>"I. Hepatitis B", "j. Hepatitis C" =>  "J. Hepatitis C", "k. Human Papilloma Virus (HPV)" => "K. Human Papilloma Virus (HPV)", "l. Influenza" => "L. Influenza", "m. Mononucleosis" =>"M. Mononucleosis", "n. Parvovirus or Fifth disease" => "N. Parvovirus or Fifth disease", "o. Pelvic Inflammatory Disease (PID)" => "O. Pelvic Inflammatory Disease (PID)", "p. Pneumonia" => "P. Pneumonia", "q. Rubella or German measles" => "Q. Rubella or German measles", "r. Shingles" => "R. Shingles", "s. Syphilis" => "S. Syphilis", "t. Toxoplasmosis" => "T. Toxoplasmosis", "u. Trichomoniasis" =>"U. Trichomoniasis", "v. Upper respiratory infection" => "V. Upper respiratory infection", "w. Urinary tract infection " => "W. Urinary tract infection ", "x. Other conditions" => "X. Other conditions", "y. Venereal warts" => "Y. Venereal warts");
		reset($aToX);

		while(list($field, $label) = each($aToX)){

			$this->form->addElement('static', null, "<br/>");

			$this->form->addElement("select", "q4_65_med_{$field}", $this->indent . "{$label}:", array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));

			$this->setRequired('q4_65_med_{$field}');

		}

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . $this->indent . " If [Yes] for Genital Herpes, go to question 4-66");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . $this->indent . " If [Yes] for Venereal/genital warts, go to question 4-67");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . $this->indent . " If [Yes] for any other infection on the list, go to question 4-68");
		$this->form->addElement('textarea', 'q4_65_other', $this->indent . $this->indent . " If [Other conditions], (e.g., vaginitis, fibroids, venereal warts, or endometriosis), please specify:");

		//	$this->form->addRule(array('q4_65_other','q4_65_med_x. Other conditions') 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q4_q4_65_other'); //*****************************

		$this->form->addElement('static', null, $this->indent . $this->indent . " If [Refused] skip to question 4-78");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . $this->indent . " If [No] or [Refused] or [Don't Know] for all, go to question 4-70");

		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement ( "select", "q4_66", "4-66. During which months from [-3] to [DOPB]
did you have the Herpes outbreak? Select all that apply:", $negThreeToNineComplete, "multiple" );
		$this->XINRegisterRule('q4_66', array("q4_65_med_f. Genital Herpes{@}=={@}01_yes"), "This is required if you had the Herpes outbreak.");  //This rule doesn't work on multiple selects.



		$this->form->addElement('static', null, "4-67. During which months from [-3] to [DOPB]
did you have the Venereal/genital warts
outbreak?");  

		$this->form->addElement("select", "q4_67",   $this->indent . "Select all that apply:",  array(NULL=>"", "-3", "-2", "-1", "01", "02", "03" => "03 ", "04" => "04", "05" => "05", "06" => "06", "07" => "07", "08" => "08", "09" => "09", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered" => "Not Answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addRule(array('q4_67', 'q4_65_med_f. Genital Herpes'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q4_67');
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "4-68. During which months
from [-3] to [DOPB] did
you have [INFECTION]?");

		$oneToThree = array("1"=>"#1", "2"=>"#2", "3"=>"#3");
		reset($oneToThree);

		while(list($field, $label) = each($oneToThree)){

			$this->form->addElement('static', null, "<br/>");


			$this->form->addElement("select", "q4_68_{$field}", $this->indent . "INFECTION {$label}",  array("a. Bacterial Vaginosis" => "A. Bacterial Vaginosis", "b. Candidiasis" => "B. Candidiasis", "c. Chlamydia" => "C. Chlamydia", "d. Chicken pox" => "D. Chicken pox", "e. Cytomegalovirus" => "E. Cytomegalovirus", "f. Genital Herpes" => "F. Genital Herpes", "g. Group B Streptococcal infection" =>"G. Group B Streptococcal infection", "h. Hepatitis A" =>"H. Hepatitis A", "i. Hepatitis B" =>"I. Hepatitis B", "j. Hepatitis C" =>  "J. Hepatitis C", "k. Human Papilloma Virus (HPV)" => "K. Human Papilloma Virus (HPV)", "l. Influenza" => "L. Influenza", "m. Mononucleosis" =>"M. Mononucleosis", "n. Parvovirus or Fifth disease" => "N. Parvovirus or Fifth disease", "o. Pelvic Inflammatory Disease (PID)" => "O. Pelvic Inflammatory Disease (PID)", "p. Pneumonia" => "P. Pneumonia", "q. Rubella or German measles" => "Q. Rubella or German measles", "r. Shingles" => "R. Shingles", "s. Syphilis" => "S. Syphilis", "t. Toxoplasmosis" => "T. Toxoplasmosis", "u. Trichomoniasis" =>"U. Trichomoniasis", "v. Upper respiratory infection" => "V. Upper respiratory infection", "w. Urinary tract infection " => "W. Urinary tract infection ", "x. Other conditions" => "X. Other conditions", "y. Venereal warts" => "Y. Venereal warts", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->form->addRule(array('q4_68_{$field}', 'q4_65_{$field}'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));

			$this->setRequired('q4_68_{$field}');
			$this->form->addElement('static', null, "<br/>");

		}


		$this->form->addElement("select", "q4_69", "4-69. Was medication taken for the infection?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 4-70");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>Other Illnesses");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>I am going to ask you about some illnesses that you might have had during that pregnancy.");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "4-70. Between [-3] and [DOPB] did you have any of the following illnesses?");

		$aToM = array("a. Migraine" => "A. Migraine", "b. Depression" => "B. Depression", "c. Nervousness" => "C. Nervousness", "d. Anxiety" => "D. Anxiety", "e. Bipolar" => "E. Bipolar", "f. Other Mental Disorders" => "F. Other Mental Disorders", "g. Epilepsy or Seizure" => "G. Epilepsy or Seizure", "h. Thyroid condition" => "H. Thyroid condition", "i. Allergy" => "I. Allergy", "j. Asthma" =>  "J. Asthma", "k. Arthritis" => "K. Arthritis", "l. Neurologic Disease" => "L. Neurologic Disease", "m. Autoimmune condition" => "M.Autoimmune condition");
		reset($aToM);

		while(list($field, $label) = each($aToM)){

			$this->form->addElement('static', null, "<br/>");

			$this->form->addElement("select", "ill_{$field}", $this->indent . "{$label}:", array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));

		}

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('textarea', 'f', $this->indent . "If [f. Other Mental Disorder], please specify:");

		$this->form->addRule(array('q4__text', 'q4_'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'0'));
		$this->setRequired('q4__text'); //*****************************

		$this->form->addElement('textarea', 'm', $this->indent . "If [m. Autoimmune condition], please specify:");

		$this->form->addRule(array('q4__text', 'q4_'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'0'));
		$this->setRequired('q4__text'); //*****************************



		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . $this->indent . " If [Yes], go to question 4-71");

		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] for all, then go to question 4-73");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "4-71. During which months from [-3] to
[DOPB] did you have [illness]?");


		$oneToThree = array("1"=>"#1", "2"=>"#2", "3"=>"#3");
		reset($oneToThree);

		while(list($field, $label) = each($oneToThree)){

			$this->form->addElement('static', null, "<br/>");

			$this->form->addElement("select", "q4_71_ill_{$field}", "ILLNESS {$label}:",  array(NULL=>"", "a. Migraine" => "A. Migraine", "b. Depression" => "B. Depression", "c. Nervousness" => "C. Nervousness", "d. Anxiety" => "D. Anxiety", "e. Bipolar" => "E. Bipolar", "f. Other Mental Disorders" => "F. Other Mental Disorders", "g. Epilepsy or Seizure" => "G. Epilepsy or Seizure", "h. Thyroid condition" => "H. Thyroid condition", "i. Allergy" => "I. Allergy", "j. Asthma" =>  "J. Asthma", "k. Arthritis" => "K. Arthritis", "l. Neurologic Disease" => "L. Neurologic Disease", "m. Autoimmune condition" => "M. Autoimmune condition", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		}

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q472_", "4-72. Was medication taken for the illness?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 4-73");


		$this->form->addElement('static', null, "<br/>");




	}

	function _page10(){   // ========================================================

		// To implement Xin Rule

		$this->form->addFormRule(array(&$this,'XINValidate'));






		$this->form->addElement('static', null, "<b/>Oral/Dental Disease");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Now I am going to ask you about some oral or dental diseases that you might have had during
that pregnancy.");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q4_73", "4-73. Between [-3] and [DOPB], did a doctor or dentist ever tell you that you had
gingivitis or periodontitis?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 4-80");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q4_74", "4-74. Did you take any medication for the gingivitis or periodontitis between
[-3] and [DOPB]?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 4-77");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "4-75. What medicine did you take?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If can't recall, refer to List 8a in prep guide and read drug list:");

		$oneToThree = array("1"=>"#1", "2"=>"#2", "3"=>"#3");
		reset($oneToThree);

		while(list($field, $label) = each($oneToThree)){

			$this->form->addElement('static', null, "<br/>");


			$this->form->addElement("select", "med_{$field}", $this->indent . "MED {$label}:", array(NULL=>"", "13" => "13 Clindamycin", "16" => "16 Doxycycline", "24 Metronidazole", "25 Minocyline", "29 Penicillin", "97 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));


			$this->form->addElement('textarea', 'other', $this->indent . "If [Other], please specify. OTHER MED {$label}:");

		}

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>For each medication given in 4-75, go to 4-76");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "4-76. During which
months from
[-3] to [DOPB] did
you take
[MEDICATION]?");  

		$oneToThree = array("1"=>"#1", "2"=>"#2", "3"=>"#3");
		reset($oneToThree);

		while(list($field, $label) = each($oneToThree)){

			$this->form->addElement('static', null, "<br/>");

			$this->form->addElement("select", "q4_76_m_{$field}",   $this->indent . "MED {$label} (Select all that apply):",  array(NULL=>"", "-3", "-2", "-1", "01", "02", "03" => "03 ", "04" => "04", "05" => "05", "06" => "06", "07" => "07", "08" => "08", "09" => "09", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered" => "Not Answered"));
		}
		$oneToThree = array("1"=>"#1", "2"=>"#2", "3"=>"#3");
		reset($oneToThree);

		while(list($field, $label) = each($oneToThree)){

			$this->form->addElement('static', null, "<br/>");

			$this->form->addElement("select", "q4_76_om_{$field}",   $this->indent . "Other MED {$label} (Select all that apply):",  array(NULL=>"", "-3", "-2", "-1", "01", "02", "03" => "03 ", "04" => "04", "05" => "05", "06" => "06", "07" => "07", "08" => "08", "09" => "09", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know","Not_Answered" => "Not Answered"));
		}

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q4_77", "4-77. Did you have any treatment other than antibiotics for gingivitis or
periodontitis between [-3] and [DOPB]?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 4-80");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q4_78", "4-78. What treatments did you have? Was it...",  array(NULL=>"", "01" => "01 Root planing and scaling", "02" => "02 Gingival curettage", "03" => "03  Splinting", "04" => "04 Other ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addRule(array('q4_78', 'q4_77'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q4_78');
		$this->form->addElement('textarea', 'q4_78_other', $this->indent . "If [Other], please specify (Other #1):");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addRule(array('q4_78_other', 'q4_78'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'04'));
		$this->setRequired('q4_78_other');

		$this->form->addElement('textarea', 'q4_78_other2', $this->indent . "If [Other], please specify (Other #2):");


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q4_79", $this->indent . "4-79. During which months from [-3] to
[DOPB] did you get the treatment? (Select all that apply):",  array(NULL=>"","-3", "-2", "-1", "01", "02", "03" => "03 ", "04" => "04", "05" => "05", "06" => "06", "07" => "07", "08" => "08", "09" => "09", "10" => "10", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered" => "Not Answered"));  

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>Injuries");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>The next few questions are about any injuries that you might have had during your pregnancy
with [PROBAND].");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q4_80", "4-80. During your pregnancy with [PROBAND], did you have an injury that required
medical attention?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 4-89");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('textarea', 'q4_81', $this->indent . "4-81. What injury did you have?");
		$this->form->addRule(array('q4_81', 'q4_80'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q4_81');
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q4_82", $this->indent . "4-82 Between [-3] and [DOPB], during which month did this injury happen?",  array(NULL=>"","-3", "-2", "-1", "01", "02", "03" => "03 ", "04" => "04", "05" => "05", "06" => "06", "07" => "07", "08" => "08", "09" => "09", "10" => "10", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered" => "Not Answered"));

		$this->form->addRule(array('q4_82', 'q4_80'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q4_82');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q4_83", "4-83. Did you ever lose consciousness because of this injury?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addRule(array('q4_83', 'q4_80'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q4_83');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q4_84", "4-84. Was medication taken for the injury?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 4-85");
		$this->form->addRule(array('q4_84', 'q4_80'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q4_84');
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q4_85", "4-85. During your pregnancy with [PROBAND], did you have any other
injury that required medical attention?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addRule(array('q4_85', 'q4_80'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q4_85');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 4-89");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'q4_86', "4-86. What was the other injury you had?");
		$this->form->addRule(array('q4_86', 'q4_85'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q4_86');
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q4_87", $this->indent . "4-87. Between [-3] and [DOPB], during which
month did this other injury happen?",  array(NULL=>"","-3", "-2", "-1", "01", "02", "03" => "03 ", "04" => "04", "05" => "05", "06" => "06", "07" => "07", "08" => "08", "09" => "09", "10" => "10", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered" => "Not Answered"));  
		$this->form->addRule(array('q4_87', 'q4_85'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q4_87');
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q4_88", "4-88. Did you ever lose consciousness because of this other injury?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));

		$this->form->addRule(array('q4_88', 'q4_85'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q4_88');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Surgery");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Now, I'm going to ask you about any surgeries or procedures that you might have had during
your pregnancy with [PROBAND].");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q4_", "4-89. During your pregnancy with [PROBAND], did you have any dental,
medical, or surgical procedures that required the use of general or
local anesthesia?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 4-93");
		$this->setRequired('q4_89');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "4-90. What procedure(s) did you have done?");

		$this->form->addElement("select", "q4_90_p1", "Procedure #1:",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addRule(array('q4_90_p1', 'q4_89'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q4_90_p1');
		$this->form->addElement('textarea', 'q4_90_p1_t', $this->indent . "If [00 Specify] please specify procedure #1");
		$this->form->addRule(array('q4_90_p1_t', 'q4_90_p1'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'00'));
		$this->setRequired('q4_90_p1_t');
		$this->form->addElement("select", "q4_90_p2", "Procedure #2:",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addElement('textarea', 'q4_90_p2_t', $this->indent . "If [00 Specify] please specify procedure #2");
		$this->form->addRule(array('q4_90_p2_t', 'q4_90_p2'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'00'));
		$this->setRequired('q4_90_p2_t');
		$this->form->addElement("select", "q4_90_p3", "Procedure #3:",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addElement('textarea', 'q4_90_p3_t', $this->indent . "If [00 Specify] please specify procedure #3");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addRule(array('q4_90_p3_t', 'q4_90_p3'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'00'));
		$this->setRequired('q4_90_p3_t');
		$this->form->addElement('static', null, "4-91. For [PROCEDURE], did you have general
anesthesia or local anesthesia?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q4_91_p1", $this->indent . "Procedure #1:",  array(NULL=>"", "01" => "01 General", "02" => "02 Local", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addRule(array('q4_91_p1', 'q4_89'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q4_91_p1');

		$this->form->addElement('static', null, $this->indent . "If [Refused] or [Don't Know] skip to question 4-93");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q4_91_p2", $this->indent . "Procedure #2:",  array(NULL=>"", "01" => "01 General", "02" => "02 Local", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, $this->indent . "If [Refused] or [Don't Know] skip to question 4-93");
		$this->form->addRule(array('q4_91_p2', 'q4_90_p2'), 'This question is required', 'requiredIf', array('operator'=>'!=', 'value'=>'NULL'));
		$this->setRequired('q4_91_p2');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q4_91_p3", $this->indent . "Procedure #3:",  array(NULL=>"", "01" => "01 General", "02" => "02 Local", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addRule(array('q4_91_p3', 'q4_90_p3'), 'This question is required', 'requiredIf', array('operator'=>'!=', 'value'=>'NULL'));
		$this->setRequired('q4_91_p3');
		$this->form->addElement('static', null, $this->indent . "If [Refused] or [Don't Know] skip to question 4-93");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q4_92",  "4-92. In which month between [-3] and [DOPB]
did you receive the anesthesia?",  array(NULL=>"","-3", "-2", "-1", "01", "02", "03" => "03 ", "04" => "04", "05" => "05", "06" => "06", "07" => "07", "08" => "08", "09" => "09", "10" => "10",  "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered" => "Not Answered"));  

		$this->form->addRule(array('q4_92', 'q4_89'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q4_92');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>Other Procedures");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "4-93. During your pregnancy with [PROBAND], did
you have");


		$aToG = array("a. X-rays, including dental" => "A. X-rays, including dental", "b. Mammogram" => "B. Mammogram", "c. CT/CAT scans" => "C. CT/CAT scans", "d. MRI/magnetic resonance" => "D. MRI/magnetic resonance", "e. Radionuclide study or scan" => "E. Radionuclide study or scan", "f. Radiation treatments or scan" => "F. Radiation treatments or scan", "g. Other" =>"G. Other");

		reset($aToG);

		while(list($field, $label) = each($aToG)){

			$this->form->addElement('static', null, "<br/>");

			$this->form->addElement("select", "q4_93_med_{$field}", $this->indent . "{$label}:", array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));


		}
		$this->form->addElement('textarea', 'q4_93_med_{$field}_other', $this->indent . "If [Other], please specify:");

		$this->form->addRule(array('q4_93_med_{$field}_other', 'q4_93_med_g. Other'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q4_93_med_{$field}_other'); //*****************************

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . $this->indent . " If [yes] for mammogram in 4-93, go to question 4-107");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . $this->indent . " If [Yes] for any other procedure in 4-93, go to question 4-94");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] for all, go to question 4-96");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "4-94. What part of your body was
tested?");
		$oneToThree = array("1"=>"#1", "2"=>"#2", "3"=>"#3");
		reset($oneToThree);

		while(list($field, $label) = each($oneToThree)){
			$this->form->addElement("select", "q4_94_{$field}", $this->indent . "Procedure {$label}:", array("a. X-rays, including dental" => "A. X-rays, including dental", "b. Mammogram" => "B. Mammogram", "c. CT/CAT scans" => "C. CT/CAT scans", "d. MRI/magnetic resonance" => "D. MRI/magnetic resonance", "e. Radionuclide study or scan" => "E. Radionuclide study or scan", "f. Radiation treatments or scan" => "F. Radiation treatments or scan", "g. Other" =>"G. Other"));

			$this->form->addElement('textarea', 'q4_94_{$field}_other', $this->indent . "If [Other], please specify:");

			$this->form->addElement('static', null, "<br/>");
			$this->form->addRule(array('q4_94_{$field}_other', 'q4_94_{$field}'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'g. Other'));
			$this->setRequired('q4_94_{$field}_other'); //*****************************
			$this->form->addElement('textarea', 'q4_94_{$field}_body', $this->indent . "Body Part Tested:");

		}
		$this->setRequired('q4_94_1');
		$this->setRequired('q4_94_1_body');
		$this->form->addRule(array('q4_94_#2_body', 'q4_94_#2'), 'Please specify.', 'requiredIf', array('operator'=>'!=', 'value'=>'NULL'));
		$this->setRequired('q4_94_#2_body');
		$this->form->addRule(array('q4_94_#3_body', 'q4_94_#3'), 'Please specify.', 'requiredIf', array('operator'=>'!=', 'value'=>'NULL'));
		$this->setRequired('q4_94_#3_body');


		$this->form->addElement('static', null, "4-95. During which month between [-3]
and [DOPB] was the [PROCEDURE] done?");

		$oneToThree = array("1"=>"#1", "2"=>"#2", "3"=>"#3");
		reset($oneToThree);

		while(list($field, $label) = each($oneToThree)){
			$this->form->addElement("select", "q4_95_{$field}", $this->indent . "Procedure {$label}:", array("a. X-rays, including dental" => "A. X-rays, including dental", "b. Mammogram" => "B. Mammogram", "c. CT/CAT scans" => "C. CT/CAT scans", "d. MRI/magnetic resonance" => "D. MRI/magnetic resonance", "e. Radionuclide study or scan" => "E. Radionuclide study or scan", "f. Radiation treatments or scan" => "F. Radiation treatments or scan", "g. Other" =>"G. Other"));

			$this->form->addElement('textarea', 'q4_95_{$field}_other', $this->indent . "If [Other], please specify:");

			$this->form->addElement('static', null, "<br/>");
			$this->form->addRule(array('q4_95_{$field}_other', 'q4_95_{$field}'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'g. Other'));
			$this->setRequired('q4_95_{$field}_other'); //*****************************
			$this->form->addElement("select", "q4_95_month_{$field}",   $this->indent . "Please select month:",  array(NULL=>"", "-3", "-2", "-1", "01", "02", "03" => "03 ", "04" => "04", "05" => "05", "06" => "06", "07" => "07", "08" => "08", "09" => "09", "10" => "10", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered" => "Not Answered"));

		}
		$this->setRequired('q4_95_1');
		$this->setRequired('q4_95_month_1');
		$this->form->addRule(array('q4_95_month_#2', 'q4_95_#2'), 'Please specify.', 'requiredIf', array('operator'=>'!=', 'value'=>'NULL'));
		$this->setRequired('q4_95_month_#2');
		$this->form->addRule(array('q4_95_month_#3', 'q4_95_#3'), 'Please specify.', 'requiredIf', array('operator'=>'!=', 'value'=>'NULL'));
		$this->setRequired('q4_95_month_#3');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");




	}



	function _page11(){   // ========================================================



		// To implement date

		$config =& NDB_Config::singleton();

		$dateOptions = array(
		'language' => 'en',
		'format'   => 'YMd',
		'minYear'  => $config->getSetting('startYear'), //allows for siblings up to 20 years older than candidate
		'maxYear'  => $config->getSetting('endYear'),
		'addEmptyOption' => true,
		'emptyOptionValue' => null
		);
		$dateOptionsYears = array(
		'language' => 'en',
		'format'   => 'Y',
		'minYear'  => $config->getSetting('startYear'), //allows for siblings up to 20 years older than candidate
		'maxYear'  => $config->getSetting('endYear'),
		'addEmptyOption' => true,
		'emptyOptionValue' => null
		);
		$dateOptionsMy = array(
		'language' => 'en',
		'format'   => 'YM',
		'minYear'  => $config->getSetting('startYear'), //allows for siblings up to 20 years older than candidate
		'maxYear'  => $config->getSetting('endYear'),
		'addEmptyOption' => true,
		'emptyOptionValue' => null
		);

		$dateOptionsOld = array(
		'language' => 'en',
		'format'   => 'Y',
		'minYear'  => '1900', //allows for siblings up to 20 years older than candidate
		'maxYear'  => $config->getSetting('endYear'),
		'addEmptyOption' => true,
		'emptyOptionValue' => null
		);



		$this->form->addElement('static', null, "<b/>Medication Use");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>This should be asked about medications not already reported before");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>We are interested in medications, including over-the-counter medications that you might have
taken during your pregnancy with [PROBAND].");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>Please refer to LISTS 8A through 8N in your preparatory guide so that we can get the most
accurate information possible.");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>The medications in the list have been organized as best as possible by condition so please look
for the heading and find your medication under that.");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>If you do not see your medication, please look under the ???other medications' category. If your
medication is not listed at all, we still want you to tell us about it. Medications can be in pill form,
nasal spray, patches, creams, etc.");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "4-96. Between [-3] and [DOPB] did you take any
medications for the following conditions?");
		$aToJ = array("a. General headaches" => "A. General headaches", "b. Back pain" => "B. Back pain", "c. Chest pain" => "C.Chest pain ", "d. Cold" => "D. Cold", "e. Acne" => "E. Acne", "f. For dieting" => "F. For dieting", "g. Heartburn" =>"G. Heartburn", "h. To relieve constipation or diarrhea" =>"H. To relieve constipation or diarrhea", "i. Sleep disorder" =>"I. Sleep disorder", "j. Other" =>  "J. Other");
		reset($aToJ);
		while(list($field, $label) = each($aToJ)){

			$this->form->addElement('static', null, "<br/>");

			$this->form->addElement("select", "q4_96_med_{$field}", $this->indent . "{$label}:", array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));



		}

		$this->form->addElement('textarea', 'q4_96_med_other', $this->indent . "If [Other], please specify:");

		$this->form->addRule(array('q4_96_med_other', 'q4_q4_96_med_j. Other'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q4_96_med_{$field}_other'); //*****************************

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [yes] for any condition in 4-96, go to question 4-97");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] for all, skip to the next section");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "4-97. What medicine did you take for [CONDITION]?");

		$this->form->addElement('static', null, $this->indent . "Condition:");

		$aToE = array("a." => "a.", "b." => "b.", "c." => "c.", "d." => "d.", "e." => "e.");
		reset($aToE);
		while(list($field, $label) = each($aToE)){

			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('static', null, "Refer to List 8a through 8n in prep guide.");
			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement("select", "q4_97_cond_{$field}", $this->indent . "{$label}", array(NULL=>"", "a. General headaches" => "A. General headaches", "b. Back pain" => "B. Back pain", "c. Chest pain" => "C.Chest pain ", "d. Cold" => "D. Cold", "e. Acne" => "E. Acne", "f. For dieting" => "F. For dieting", "g. Heartburn" =>"G. Heartburn", "h. To relieve constipation or diarrhea" =>"H. To relieve constipation or diarrhea", "i. Sleep disorder" =>"I. Sleep disorder", "j. Other" =>  "J. Other"));


			$this->form->addElement('textarea', 'q4_97_cond_{$field}_other', $this->indent . "If [Other], please specify:");

			$this->form->addRule(array('q4_97_cond_{$field}_other', 'q4_97_cond_{$field}'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'j. Other'));
			$this->setRequired('q4_97_cond_{$field}_other'); //*****************************


			$this->form->addElement('textarea', 'q4_97_med1', $this->indent . "Please write the name of the medication #1.");
			$this->form->addElement('textarea', 'q4_97_med2', $this->indent . "Please write the name of the medication #2.");
			$this->form->addElement('textarea', 'q4_97_med3', $this->indent . "Please write the name of the medication #3.");



		}


		$this->form->addElement('static', null, "4-98. Between [-3] and [DOPB], which months did you take the medication?");


		$this->form->addElement('static', null, $this->indent . "Condition:");


		$oneToTen = array("1"=>"#1", "2"=>"#2", "3"=>"#3", "#4"=>"#4", "5"=>"#5", "6"=>"#6", "7"=>"#7", "8"=>"#8", "9"=>"#9", "10"=>"#10");
		reset($oneToTen);

		while(list($field, $label) = each($oneToTen)){

			$this->form->addElement('static', null, "<br/>");

			$this->form->addElement("select", "q4_98_cond_{$field}", $this->indent . "Condition {$label}:", array(NULL=>"", "a. General headaches" => "A. General headaches", "b. Back pain" => "B. Back pain", "c. Chest pain" => "C.Chest pain ", "d. Cold" => "D. Cold", "e. Acne" => "E. Acne", "f. For dieting" => "F. For dieting", "g. Heartburn" =>"G. Heartburn", "h. To relieve constipation or diarrhea" =>"H. To relieve constipation or diarrhea", "i. Sleep disorder" =>"I. Sleep disorder", "j. Other" =>  "J. Other"));


			$this->form->addElement('textarea', 'q4_98_cond_{$field}_other', $this->indent . "If [Other], please specify:");

			$this->form->addRule(array('q4_98_cond_{$field}_other', 'q4_98_cond_{$field}'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'j. Other'));
			$this->setRequired('q4_98_cond_{$field}_other'); //*****************************

			$this->form->addElement('textarea', 'q4_98_med_{$field}', $this->indent . "Please write the name of medication {$label}:");

			$this->form->addElement("select", "q4_98_month_{$field}",   $this->indent . " Please select all that apply:",  array(NULL=>"", "-3", "-2", "-1", "01", "02", "03" => "03 ", "04" => "04", "05" => "05", "06" => "06", "07" => "07", "08" => "08", "09" => "09", "10" => "10", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered" => "Not Answered"));


			$this->form->addElement('static', null, "<br/>");
		}




	}

	function _page12(){   // ========================================================

		// To implement Xin Rule

		$this->form->addFormRule(array(&$this,'XINValidate'));














		$this->form->addElement('header', null, "Section 5: SIBLING PREGNANCY");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>Now I have some questions specific to your pregnancy with the younger sibling of your child with
ASD (Ask name of sibling).");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q5_1", $this->indent . "5-1. What date did the doctor give you as the expected due date?",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		$this->setRequired('q5_1');
		$this->form->addElement('date', 'q5_1_date', "If [00 Specify] please specify the date:", $dateOptions);
		$this->form->addRule(array('q5_1_date', 'q5_1'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'00'));
		$this->setRequired('q5_1_date');
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If date given, record in Pregnancy Calendar, then go to question 5-2");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q5_2", $this->indent . "5-2. How much did you weigh before you were pregnant with the sibling of your child with ASD?",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'q5_2_t', $this->indent . "If [00 Specify] please specify (in lbs):");
		$this->form->addRule(array('q5_2_t', 'q5_2'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'00'));
		$this->setRequired('q5_2_t');



		$this->form->addElement("select", "q5_3", $this->indent . "5-3. How much weight did you gain or lose with your pregnancy with
the sibling of your child with ASD?",  array(NULL=>"", "00_wg_kg" => "00 Specify Weight gain (in kgs)", "00_wg_lb" => "00 Specify Weight gain (in lbs)", "00_wl_kg" => "00 Specify Weight loss (in kgs)",  "00_wl_lb" => "00 Specify Weight loss (in lbs)", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

		$this->form->addElement('textarea', 'q5_3_wg_kg', $this->indent . "If [00 Specify Weight gain (in kgs)] please specify Weight gain (kgs):");

		$this->form->addElement('textarea', 'q5_3_wg_lb', $this->indent . "If [00 Specify Weight gain (in lbs)] please specify Weight gain (lbs):");

		$this->form->addElement('textarea', 'q5_3_wl_kg', $this->indent . "If [00 Specify Weight loss (in kgs)] please specify Weight loss (kgs):");
		$this->form->addElement('textarea', 'q5_3_wl_lb', $this->indent . "If [00 Specify Weight loss (in lbs)] please specify Weight loss (lbs):");

		$this->form->addRule(array('q5_3_wg_kg', 'q5_3'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'00_wg_kg'));
		$this->setRequired('q5_3_wg_kg');

		$this->form->addRule(array('q5_3_wg_lb', 'q5_3'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'00_wg_lb'));
		$this->setRequired('q5_3_wg_lb');

		$this->form->addRule(array('q5_3_wl_kg', 'q5_3'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'00_wl_kg'));
		$this->setRequired('q5_3_wl_kg');

		$this->form->addRule(array('q5_3_wl_lb', 'q5_3'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'00_wl_lb'));
		$this->setRequired('q5_3_wl_lb');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");



		$this->form->addElement('static', null, "5-4. What was your height without shoes?");

		$this->form->addElement("select", "q5_4_f", $this->indent .  "Feet:",  array(NULL=>"",  "1" => "1", "2" => "2", "3" => "3", "4", "5", "6", "7", "88_Refused" => "88 Refused", "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement("select", "q5_4_i", $this->indent .  "Inches:",  array(NULL=>"",  "0", "1" => "1", "2" => "2", "3" => "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "88_Refused" => "88 Refused", "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->setRequired('q5_4_f');
		$this->setRequired('q5_4_i');



		$this->form->addElement("select", "q5_5", $this->indent .  "5-5. How far along were you when you found out you were pregnant with [DOBS]?",  array(NULL=>"",  "00_w" => "00 Specify weeks", "00_m" => "00 Specify months" ,"88_Refused" => "88 Refused", "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));



		$this->form->addElement("select", "q5_5_w", $this->indent .  "Weeks:",  array(NULL=>"",  "0", "1" => "1", "2" => "2", "3" => "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18" => "18", "19", "20" => "20", "21" => "21", "22" => "22", "23" => "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "36", "37", "38","88_Refused" => "88 Refused", "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));


		$this->form->addElement("select", "q5_5_m", $this->indent .  "Months:",  array(NULL=>"",  "0", "1" => "1", "2" => "2", "3" => "3", "4", "5", "6", "7", "8", "9", "88_Refused" => "88 Refused", "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));


		$this->form->addRule(array('q5_5_w', 'q5_5'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'00_w'));
		$this->setRequired('q5_5_w');

		$this->form->addRule(array('q5_5_m', 'q5_5'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'00_m'));
		$this->setRequired('q5_5_m');

		$this->form->addElement('static', null, $this->indent .  "<b/>Refer to the Pregnancy Calendar.");


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Refer to the Pregnancy Calendar");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q5_6", "5-6. Between [-3] and [DOBS] did you use any birth control pills or morning after
pills?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 5-9");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "5-7. What was the name of the pills?");


		$oneToFive = array("1"=>"#1", "2"=>"#2", "3"=>"#3", "#4"=>"#4", "5"=>"#5");
		reset($oneToFive);

		while(list($field, $label) = each($oneToFive)){

			$this->form->addElement('static', null, "<br/>");


			$this->form->addElement("select", "5_7_med_{$field}", $this->indent . "Pill {$label}:", array(NULL=>"", "01" => "01 Alesse", "02" => "02 Brevicon", "03" => "03  Demulen", "04" => "04 Desogen", "05" => "05 Estrostep", "06" => "06 Levlen", "07" => "07 Levlite", "08" => "08 Levora", "09" => "09 Loestrin", "10" => "10 Lo/Ovral", "11" => "11 Micronor", "12" => "12 Mircette", "13" => "13 Modicon", "14" => "14 Necon", "15" => "15 Nordette", "16" => "16 Norinyl", "17" => "17 Nor-Q.D", "18" => "18 Ortho-Cept", "19" => "19 OrthoCyclen", "20" => "20 Ortho-Novum", "21" => "21 Ortho Tri-Cyclen", "22" => "22 Ovcon", "23" => "23 Ovral", "24 Tri-Levlen", "25 Tri-Norinyl", "26 Triphasil", "27 Trivora", "28 Zovia",  "29" => "29 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

			$this->form->addElement('textarea', '5_7_med_{$field}_other', $this->indent . "If [Other], please specify:");

			$this->form->addRule(array('5_7_med_{$field}_other', '5_7_med_{$field}'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'29'));
			$this->setRequired('5_7_med_{$field}_other'); //**************************

		}

		$this->form->addRule(array('5_7_med_1', 'q5_6'), 'Please specify the name of the pill(s).', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('5_7_med_1');


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "5-8. Which months between [-3] and [DOBS]
were you using [PILL NAME]?");


		$oneToFive = array("1"=>"#1", "2"=>"#2", "3"=>"#3", "#4"=>"#4", "5"=>"#5");
		reset($oneToFive);

		while(list($field, $label) = each($oneToFive)){

			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement("select", "q5_8_{$field}",   $this->indent . "Pill {$label} (Select all that apply):",  array(NULL=>"", "-3", "-2", "-1", "01", "02", "03" => "03 ", "04" => "04", "05" => "05", "06" => "06",  "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered" => "Not Answered"));

			$this->form->addRule(array('q5_8_{$field}', 'q5_7_{$field}'), 'Please specify.', 'requiredIf', array('operator'=>'!=', 'value'=>'NULL'));
			$this->setRequired('q5_8_{$field}');

		}
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q5_9", "5-9. Between [-3] and [DOBS] did you use any other method of contraception
to avoid getting pregnant?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 5-12");

		$this->setRequired('q5_9');

		$this->form->addElement('static', null, "5-10. What method of contraception were you using?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, " If can't recall, ask to refer to List 3 in prep guide and choose from the following list:");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q5_10_m1", $this->indent .  "METHOD #1:",  array(NULL=>"", "01" => "01 Condoms (male or female)", "02" => "02 Depo-Provera", "03" => "03  Diaphram/cervical cap", "04" => "04 Intrauterine device (IUD)", "05" => "05 Norplant", "06" => "06 Spermicide", "07" => "07 Sponge", "08" => "08 Other", "88 Refused", "99" => "99 Do not know"));

		$this->form->addRule(array('q5_10_m1', 'q5_9'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q5_10_m1');

		$this->form->addElement('textarea', 'q5_10_m1_text', $this->indent . "If [Other], please specify:");

		$this->form->addRule(array('q5_10_m1_text', 'q5_10_m1'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'08'));
		$this->setRequired('q5_10_m1_text'); //*****************************

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q5_10_m2", $this->indent .  "METHOD #2:",  array(NULL=>"", "01" => "01 Condoms (male or female)", "02" => "02 Depo-Provera", "03" => "03  Diaphram/cervical cap", "04" => "04 Intrauterine device (IUD)", "05" => "05 Norplant", "06" => "06 Spermicide", "07" => "07 Sponge", "08" => "08 Other", "88 Refused", "99" => "99 Do not know"));

		$this->form->addElement('textarea', 'q5_10_m2_text', $this->indent . "If [Other], please specify:");

		$this->form->addRule(array('q5_10_m2_text', 'q5_10_m2'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'08'));
		$this->setRequired('q5_10_m2_text'); //*****************************

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q5_10_m3", $this->indent .  "METHOD #3:",  array(NULL=>"", "01" => "01 Condoms (male or female)", "02" => "02 Depo-Provera", "03" => "03  Diaphram/cervical cap", "04" => "04 Intrauterine device (IUD)", "05" => "05 Norplant", "06" => "06 Spermicide", "07" => "07 Sponge", "08" => "08 Other", "88 Refused", "99" => "99 Do not know"));

		$this->form->addElement('textarea', 'q5_10_m3_text', $this->indent . "If [Other], please specify:");

		$this->form->addRule(array('q5_10_m3_text', 'q5_10_m3'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'08'));
		$this->setRequired('q5_10_m3_text'); //*****************************

		$this->form->addElement("select", "q5_10_m4", $this->indent .  "METHOD #4:",  array(NULL=>"", "01" => "01 Condoms (male or female)", "02" => "02 Depo-Provera", "03" => "03  Diaphram/cervical cap", "04" => "04 Intrauterine device (IUD)", "05" => "05 Norplant", "06" => "06 Spermicide", "07" => "07 Sponge", "08" => "08 Other", "88 Refused", "99" => "99 Do not know"));

		$this->form->addElement('textarea', 'q5_10_m4_text', $this->indent . "If [Other], please specify:");

		$this->form->addRule(array('q5_10_m4_text', 'q5_10_m4'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'08'));
		$this->setRequired('q5_10_m4_text'); //*****************************

		$this->form->addElement("select", "q5_10_m5", $this->indent .  "METHOD #5:",  array(NULL=>"", "01" => "01 Condoms (male or female)", "02" => "02 Depo-Provera", "03" => "03  Diaphram/cervical cap", "04" => "04 Intrauterine device (IUD)", "05" => "05 Norplant", "06" => "06 Spermicide", "07" => "07 Sponge", "08" => "08 Other", "88 Refused", "99" => "99 Do not know"));

		$this->form->addElement('textarea', 'q5_10_m5_text', $this->indent . "If [Other], please specify:");

		$this->form->addRule(array('q5_10_m5_text', 'q5_10_m5'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'08'));
		$this->setRequired('q5_10_m5_text'); //*****************************



		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "5-11. Which months between [-3]
and [DOPB] were you using
[CONTRACEPTIVE
METHOD]?");  

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "Met #1:");
		$this->form->addElement("select", "q5_11_m1", $this->indent . $this->indent . " Select all that apply from the following list:",  array(NULL=>"","-3", "-2", "-1", "1", "2", "3", "4", "5", "6", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addRule(array('q5_11_m1', 'q5_9'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q5_11_m1');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "Met #2:");
		$this->form->addElement("select", "q5_11_m2", $this->indent . $this->indent . " Select all that apply from the following list:",  array(NULL=>"","-3", "-2", "-1", "1", "2", "3", "4", "5", "6", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));


		$this->form->addRule(array('q5_11_m2', 'q5_10_m2'), 'This question is required', 'requiredIf', array('operator'=>'!=', 'value'=>'NULL'));
		$this->setRequired('q5_11_m2');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "Met #3:");
		$this->form->addElement("select", "q5_11_m3", $this->indent . $this->indent . " Select all that apply from the following list:",  array(NULL=>"","-3", "-2", "-1", "1", "2", "3", "4", "5", "6", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addRule(array('q5_11_m3', 'q5_10_m3'), 'This question is required', 'requiredIf', array('operator'=>'!=', 'value'=>'NULL'));
		$this->setRequired('q5_11_m3');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "Met #4:");
		$this->form->addElement("select", "q5_11_m4", $this->indent . $this->indent . " Select all that apply from the following list:",  array(NULL=>"","-3", "-2", "-1", "1", "2", "3", "4", "5", "6", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addRule(array('q5_11_m4', 'q5_10_m4'), 'This question is required', 'requiredIf', array('operator'=>'!=', 'value'=>'NULL'));
		$this->setRequired('q5_11_m4');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "Met #5:");
		$this->form->addElement("select", "q5_11_m5", $this->indent . $this->indent . " Select all that apply from the following list:",  array(NULL=>"","-3", "-2", "-1", "1", "2", "3", "4", "5", "6", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addRule(array('q5_11_m5', 'q5_10_m5'), 'This question is required', 'requiredIf', array('operator'=>'!=', 'value'=>'NULL'));
		$this->setRequired('q5_11_m5');

		$this->form->addElement('static', null, "<br/>");





		$this->form->addElement('static', null, "5-12. If no contraceptives were used between [-3] and [DOBS] (i.e., 5-6 and 5-9 = No, Refused, or Do not know), then go to question 5-13");
		$this->form->addElement('static', null, $this->indent . "If any contraceptive was used between [-3] and [DOBS] (i.e., 5-6 or 5-9 = Yes), then go to
question 5-14");

		$this->form->addElement("select", "q5_13", "5-13. Did you...",  array(NULL=>"", "01" => "01 Stop using contraception to get pregnant", "02" => "02 Get pregnant during an interruption in using contraception", "03" => "03  Not use contraception before this pregnancy", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addElement('static', null, $this->indent . "If [01 Stop using contraception to get pregnant], go to question 5-15");
		$this->form->addElement('static', null, $this->indent . "If [02 Get pregnant during an interruption in using contraception], go to question 5-32");

		$this->form->addElement("select", "q5_", "5-14. Did you get pregnant while consistently using contraception?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));

		$this->form->addElement('static', null, $this->indent . "If [Yes], go to question 5-32");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q5_15a", "5-15a. At the time you became pregnant, did you ...?",  array(NULL=>"", "01" => "01 Want to become pregnant then", "02" => "02 Want to wait until later",  "03" => "03 Not want to become pregnant at all", "04" => "04 Didn???t care","88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));

		$this->form->addRule(array('q5_15a', 'q5_13'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q5_15a');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q5_15b", "5-15b. Before getting pregnant with [SIBLING], did you have regular
intercourse for a period of 12 months or more without using
contraception?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));

		$this->form->addRule(array('q5_15b', 'q5_13'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q5_15b');


		$this->form->addElement("select", "q5_16", "5-16. Did you use fertility treatment to get pregnant with [SIBLING]?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addRule(array('q5_16', 'q5_13'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q5_16');

		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 5-32");


	}


	function _page13(){   // ========================================================

		// To implement Xin Rule

		$this->form->addFormRule(array(&$this,'XINValidate'));





		// To implement date

		$config =& NDB_Config::singleton();

		$dateOptions = array(
		'language' => 'en',
		'format'   => 'YMd',
		'minYear'  => $config->getSetting('startYear'), //allows for siblings up to 20 years older than candidate
		'maxYear'  => $config->getSetting('endYear'),
		'addEmptyOption' => true,
		'emptyOptionValue' => null
		);
		$dateOptionsYears = array(
		'language' => 'en',
		'format'   => 'Y',
		'minYear'  => $config->getSetting('startYear'), //allows for siblings up to 20 years older than candidate
		'maxYear'  => $config->getSetting('endYear'),
		'addEmptyOption' => true,
		'emptyOptionValue' => null
		);
		$dateOptionsMy = array(
		'language' => 'en',
		'format'   => 'YM',
		'minYear'  => $config->getSetting('startYear'), //allows for siblings up to 20 years older than candidate
		'maxYear'  => $config->getSetting('endYear'),
		'addEmptyOption' => true,
		'emptyOptionValue' => null
		);

		$dateOptionsOld = array(
		'language' => 'en',
		'format'   => 'Y',
		'minYear'  => '1900', //allows for siblings up to 20 years older than candidate
		'maxYear'  => $config->getSetting('endYear'),
		'addEmptyOption' => true,
		'emptyOptionValue' => null
		);



		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/> <b/>Assisted Reproduction");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/Now, I'm going to ask you some detailed questions about what type of help you or your baby's
father (we should get his name earlier so we can refer to him by name) may have received to help you
get pregnant with the younger sibling of your child with ASD.");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q5_17", "5-17. Did you take any medications to help prevent miscarriage with
your pregnancy with [SIBLING]?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addRule(array('q5_17', 'q5_13'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q5_17');

		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 5-19");

		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "5-18. What medications did you take?");

		$this->form->addElement('static', null, $this->indent . "If respondent can't recall, ask to refer to List 4 in prep guide and ask to select from the following list:");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q5_18_m1", $this->indent. " Med #1:", array(NULL=>"", "01" => "01 Crinonevz", "02" => "02 Prometrium", "03" => "03  Heparin", "04" => "04 Baby aspirin", "05" => "05 IVIg Therapy", "06" => "06 Steroid treatment", "07" => "07 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addRule(array('q5_18_m1', 'q5_17'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q5_18_m1');

		$this->form->addElement('textarea', 'q5_18_m1_S1_t', $this->indent . $this->indent . " If [06 Steroid treatmen], please specify STEROID #1:");
		$this->form->addRule(array('q5_q5_18_m1_S1_t', 'q5_18_m1'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'06'));
		$this->setRequired('q5_q5_18_m1_S1_t');
		$this->form->addElement('textarea', 'q5_18_m1_t', $this->indent . $this->indent . " If [Other], please specify MEDICATION #1:");
		$this->form->addRule(array('q5_q5_18_m1_t', 'q5_18_m1'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'07'));
		$this->setRequired('q5_18_m1_t');
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q5_18_m2", $this->indent. " Med #2:", array(NULL=>"", "01" => "01 Crinonevz", "02" => "02 Prometrium", "03" => "03  Heparin", "04" => "04 Baby aspirin", "05" => "05 IVIg Therapy", "06" => "06 Steroid treatment", "07" => "07 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));


		$this->form->addElement('textarea', 'q5_18_m2_S2_t', $this->indent . $this->indent . " If [06 Steroid treatmen], please specify STEROID #2:");
		$this->form->addRule(array('q5_q5_18_m2_S2_t', 'q5_18_m2'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'06'));
		$this->setRequired('q5_18_m2_S2_t');
		$this->form->addElement('textarea', 'q5_18_m2_t', $this->indent . $this->indent . " If [Other], please specify MEDICATION #2:");
		$this->form->addRule(array('q5_q5_18_m2_t', 'q5_18_m2'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'07'));
		$this->setRequired('q5_q5_18_m2_t');
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q5_18_m3", $this->indent. " Med #3:", array(NULL=>"", "01" => "01 Crinonevz", "02" => "02 Prometrium", "03" => "03  Heparin", "04" => "04 Baby aspirin", "05" => "05 IVIg Therapy", "06" => "06 Steroid treatment", "07" => "07 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));


		$this->form->addElement('textarea', 'q5_18_m3_S3_t', $this->indent . $this->indent . " If [06 Steroid treatmen], please specify STEROID #3:");
		$this->form->addRule(array('q5_q5_18_m3_S3_t', 'q5_18_m3'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'06'));
		$this->setRequired('q5_q5_18_m3_S3_t');
		$this->form->addElement('textarea', 'q5_18_m3_t', $this->indent . $this->indent . " If [Other], please specify MEDICATION #3:");
		$this->form->addRule(array('q5_q5_18_m3_t', 'q5_18_m3'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'07'));
		$this->setRequired('q5_18_m3_t');
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q5_", "5-19. Did you take any medications to help you become pregnant with? ",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 5-21");
		$this->form->addRule(array('q5_19', 'q5_17'), 'This question is required', 'requiredIf', array('operator'=>'!=', 'value'=>'01'));
		$this->setRequired('q5_19');

		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "5-20. What medications did you take?");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null,  $this->indent . "Probe: Are there any more medications?
If can't recall, ask them to refer to List 5 in prep guide and choose from the following list:");     

		$this->form->addElement("select", "q5_20_1", $this->indent . $this->indent . " Med #1",  array(NULL=>"", "01" => "01 Bromocriptine", "02" => "02 Clomid", "03" => "03  Chorionic gonadotropin", "04" => "04 Clomiphene citrate", "05" => "05 Danazol", "05" => "05 Danocrine", "06" => "06 Dostinex", "07" => "07 Factrel", "08" => "08 Fertinex", "09" => "09 Follistim", "10" => "10 Gonadorelin", "11" => "11 Gonal-F", "12" => "12 Humegon", "13" => "13 Lupron", "14" => "14 Lutrepulse", "16" => "16 Metrodin", "17" => "17 Novarel", "18" => "18 Parlodel", "19" => "19 Pergonal", "20" => "20 Pregnyl", "21" => "21 Profasi HP", "22" => "22 Provera", "23" => "23 Repronex", "24 Serophene", "25 Synarel", "26" => "26 Other", "88 Refused", "99" => "99 Do not know"));
		$this->form->addElement('textarea', 'q5_20_1_t', $this->indent . $this->indent . " If [Other], please specify. Drug #1:");

		$this->form->addElement("select", "q5_20_2", $this->indent . $this->indent . " Med #2",  array(NULL=>"", "01" => "01 Bromocriptine", "02" => "02 Clomid", "03" => "03  Chorionic gonadotropin", "04" => "04 Clomiphene citrate", "05" => "05 Danazol", "05" => "05 Danocrine", "06" => "06 Dostinex", "07" => "07 Factrel", "08" => "08 Fertinex", "09" => "09 Follistim", "10" => "10 Gonadorelin", "11" => "11 Gonal-F", "12" => "12 Humegon", "13" => "13 Lupron", "14" => "14 Lutrepulse", "16" => "16 Metrodin", "17" => "17 Novarel", "18" => "18 Parlodel", "19" => "19 Pergonal", "20" => "20 Pregnyl", "21" => "21 Profasi HP", "22" => "22 Provera", "23" => "23 Repronex", "24 Serophene", "25 Synarel", "26" => "26 Other", "88 Refused", "99" => "99 Do not know"));
		$this->form->addElement('textarea', 'q5_20_2_t', $this->indent . $this->indent . " If [Other], please specify. Drug #2:");

		$this->form->addElement("select", "q5_20_3", $this->indent . $this->indent . " Med #3",  array(NULL=>"", "01" => "01 Bromocriptine", "02" => "02 Clomid", "03" => "03  Chorionic gonadotropin", "04" => "04 Clomiphene citrate", "05" => "05 Danazol", "05" => "05 Danocrine", "06" => "06 Dostinex", "07" => "07 Factrel", "08" => "08 Fertinex", "09" => "09 Follistim", "10" => "10 Gonadorelin", "11" => "11 Gonal-F", "12" => "12 Humegon", "13" => "13 Lupron", "14" => "14 Lutrepulse", "16" => "16 Metrodin", "17" => "17 Novarel", "18" => "18 Parlodel", "19" => "19 Pergonal", "20" => "20 Pregnyl", "21" => "21 Profasi HP", "22" => "22 Provera", "23" => "23 Repronex", "24 Serophene", "25 Synarel", "26" => "26 Other", "88 Refused", "99" => "99 Do not know"));
		$this->form->addElement('textarea', 'q5_20_3_t', $this->indent . $this->indent . " If [Other], please specify. Drug #3:");

		$this->form->addElement("select", "q5_20_4", $this->indent . $this->indent . " Med #4",  array(NULL=>"", "01" => "01 Bromocriptine", "02" => "02 Clomid", "03" => "03  Chorionic gonadotropin", "04" => "04 Clomiphene citrate", "05" => "05 Danazol", "05" => "05 Danocrine", "06" => "06 Dostinex", "07" => "07 Factrel", "08" => "08 Fertinex", "09" => "09 Follistim", "10" => "10 Gonadorelin", "11" => "11 Gonal-F", "12" => "12 Humegon", "13" => "13 Lupron", "14" => "14 Lutrepulse", "16" => "16 Metrodin", "17" => "17 Novarel", "18" => "18 Parlodel", "19" => "19 Pergonal", "20" => "20 Pregnyl", "21" => "21 Profasi HP", "22" => "22 Provera", "23" => "23 Repronex", "24 Serophene", "25 Synarel", "26" => "26 Other", "88 Refused", "99" => "99 Do not know"));
		$this->form->addElement('textarea', 'q5_20_4_t', $this->indent . $this->indent . " If [Other], please specify. Drug #4:");

		$this->form->addElement("select", "q5_20_5", $this->indent . $this->indent . " Med #5",  array(NULL=>"", "01" => "01 Bromocriptine", "02" => "02 Clomid", "03" => "03  Chorionic gonadotropin", "04" => "04 Clomiphene citrate", "05" => "05 Danazol", "05" => "05 Danocrine", "06" => "06 Dostinex", "07" => "07 Factrel", "08" => "08 Fertinex", "09" => "09 Follistim", "10" => "10 Gonadorelin", "11" => "11 Gonal-F", "12" => "12 Humegon", "13" => "13 Lupron", "14" => "14 Lutrepulse", "16" => "16 Metrodin", "17" => "17 Novarel", "18" => "18 Parlodel", "19" => "19 Pergonal", "20" => "20 Pregnyl", "21" => "21 Profasi HP", "22" => "22 Provera", "23" => "23 Repronex", "24 Serophene", "25 Synarel", "26" => "26 Other", "88 Refused", "99" => "99 Do not know"));
		$this->form->addElement('textarea', 'q5_20_5_t', $this->indent . $this->indent . " If [Other], please specify. Drug #5:");



		$this->form->addRule(array('q5_20_1', 'q5_19'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q5_20_1');

		$this->form->addElement('textarea', 'q5_20_1_t', $this->indent . $this->indent . " If [Other], please specify. Drug #1:");

		$this->form->addRule(array('q5_20_1_t', 'q5_20_1'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'26'));
		$this->setRequired('q5_20_1_t'); //*****************************

		$this->form->addRule(array('q5_20_2_t', 'q5_20_2'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'26'));
		$this->setRequired('q5_20_2_t'); //*****************************

		$this->form->addRule(array('q5_20_3_t', 'q5_20_3'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'26'));
		$this->setRequired('q5_20_3_t'); //*****************************

		$this->form->addRule(array('q5_20_4_t', 'q5_20_4'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'26'));
		$this->setRequired('q5_20_4_t'); //*****************************


		$this->form->addRule(array('q5_20_5_t', 'q5_20_5'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'26'));
		$this->setRequired('q5_20_5_t'); //*****************************


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q5_21", "5-21. Did you have any other procedures to help you become pregnant with
[SIBLING]?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know], then:");


		$this->form->addElement('static', null, $this->indent . $this->indent . " If child's biological father known, then go to 5-28 5-25
JH");

		$this->form->addElement('static', null, $this->indent . $this->indent . " If child's biological father is unknown, then go to 5-32");

		$this->form->addRule(array('q5_21', 'q5_19'), 'This question is required', 'requiredIf', array('operator'=>'!=', 'value'=>'01'));
		$this->setRequired('q5_21');


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "5-22. I'm going to read you a list of procedures. Please tell me if you
received any of these to help you get pregnant with [SIBLING].");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If can't recall, ask them to refer to List 6 in prep guide.");
		$this->form->addElement('static', null, $this->indent . "For each procedure coded in 5-22, ask questions 5-23 thru 5-24.");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q5_22_p#1", $this->indent . "PROC #1:",  array(NULL=>"", "01" => "01 Artificial insemination or intrauterine insemination", "02" => "02 In vitro fertilization- embryo transfer (IVF-ET)", "03" => "03  Gamete intrafallopian transfer (GIFT)", "04" => "04 Zygote intrafallopian transfer (ZIFT)", "05" => "05 Intracytoplasmic sperm injection (ICSI)", "06" => "06 Frozen embryo transfer", "07" => "07 Tubal embryo transfer (TET)", "08" => "08 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addElement('textarea', 'q5_22_p#1_other', $this->indent . $this->indent . " If [Other], please specify. OTHER PROC #1:");

		$this->form->addElement('static', null, $this->indent . $this->indent . " If [Refused] or [Don't Know], then:");

		$this->form->addElement('static', null, $this->indent . $this->indent . $this->indent . " If child's biological father known, then go to 5-25");

		$this->form->addElement('static', null, $this->indent . $this->indent . $this->indent . " If child's biological father is unknown, then go to 5-32");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q5_22_p#2", $this->indent . "PROC #2:",  array(NULL=>"", "01" => "01 Artificial insemination or intrauterine insemination", "02" => "02 In vitro fertilization- embryo transfer (IVF-ET)", "03" => "03  Gamete intrafallopian transfer (GIFT)", "04" => "04 Zygote intrafallopian transfer (ZIFT)", "05" => "05 Intracytoplasmic sperm injection (ICSI)", "06" => "06 Frozen embryo transfer", "07" => "07 Tubal embryo transfer (TET)", "08" => "08 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addElement('textarea', 'q5_22_p#2_other', $this->indent . $this->indent . " If [Other], please specify. OTHER PROC #2:");

		$this->form->addElement('static', null, $this->indent . $this->indent . " If [Refused] or [Don't Know], then:");

		$this->form->addElement('static', null, $this->indent . $this->indent . $this->indent . " If child's biological father known, then go to 5-25");

		$this->form->addElement('static', null, $this->indent . $this->indent . $this->indent . " If child's biological father is unknown, then go to 5-32");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q5_22_p#3", $this->indent . "PROC #3:",  array(NULL=>"", "01" => "01 Artificial insemination or intrauterine insemination", "02" => "02 In vitro fertilization- embryo transfer (IVF-ET)", "03" => "03  Gamete intrafallopian transfer (GIFT)", "04" => "04 Zygote intrafallopian transfer (ZIFT)", "05" => "05 Intracytoplasmic sperm injection (ICSI)", "06" => "06 Frozen embryo transfer", "07" => "07 Tubal embryo transfer (TET)", "08" => "08 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addElement('textarea', 'q5_22_p#3_other', $this->indent . $this->indent . " If [Other], please specify. OTHER PROC #3:");

		$this->form->addElement('static', null, $this->indent . $this->indent . " If [Refused] or [Don't Know], then:");

		$this->form->addElement('static', null, $this->indent . $this->indent . $this->indent . " If child's biological father known, then go to 5-25");

		$this->form->addElement('static', null, $this->indent . $this->indent . $this->indent . " If child's biological father is unknown, then go to 5-32");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addRule(array('q5_22_p#1', 'q5_21'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q5_22_p#1');

		$this->form->addRule(array('q5_22_p#1_other', 'q5_22_p#1'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'08'));
		$this->setRequired('q5_22_p#1_other');

		$this->form->addRule(array('q5_22_p#2_other', 'q5_22_p#2'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'08'));
		$this->setRequired('q5_22_p#2_other');


		$this->form->addRule(array('q5_22_p#3_other', 'q5_22_p#3'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'08'));
		$this->setRequired('q5_22_p#3_other');





		$this->form->addElement('static', null, "5-23. Were donor eggs, sperm or embryos used?");

		$this->form->addElement('static', null, $this->indent .  "Using the same PROC codes as in 5-22, choose the appropriate answer for each item.");


		$oneToThree = array("1"=>"#1", "2"=>"#2", "3"=>"#3");
		reset($oneToThree);

		while(list($field, $label) = each($oneToThree)){

			$this->form->addElement('static', null, "<br/>");

			$this->form->addElement('static', null, $this->indent . "PROC {$label}:");

			$this->form->addElement("select", "q5_23_eggs_{$field}", $this->indent . $this->indent . " Eggs:", array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "98" => "98 Refused", "99" => "99 Do not know", "Not_Answered" => "Not Answered"));

			$this->form->addElement("select", "q5_23_sperm_{$field}", $this->indent . $this->indent . " Sperm:", array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "98" => "98 Refused", "99" => "99 Do not know", "Not_Answered" => "Not Answered"));
			$this->form->addElement("select", "q5_23_embryo_{$field}", $this->indent . $this->indent . " Embryo:", array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "98" => "98 Refused", "99" => "99 Do not know", "Not_Answered" => "Not Answered"));


			$this->form->addRule(array('q5_23_eggs_{$field}', 'q5_22_p{$field}'), 'This question is required', 'requiredIf', array('operator'=>'!=', 'value'=>'NULL'));
			$this->setRequired('q5_23_eggs_{$field}');

			$this->form->addRule(array('q5_23_sperm_{$field}', 'q5_22_p{$field}'), 'This question is required', 'requiredIf', array('operator'=>'!=', 'value'=>'NULL'));
			$this->setRequired('q5_23_sperm_{$field}');

			$this->form->addRule(array('q5_23_embryo_{$field}', 'q5_22_p{$field}'), 'This question is required', 'requiredIf', array('operator'=>'!=', 'value'=>'NULL'));
			$this->setRequired('q5_23_embryo_{$field}');

			$this->form->addElement('static', null, $this->indent . "OTHER PROC {$label}:");

			$this->form->addElement("select", "q5_23_eggs_{$field}_other", $this->indent . $this->indent . " Eggs:", array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "98" => "98 Refused", "99" => "99 Do not know", "Not_Answered" => "Not Answered"));

			$this->form->addElement("select", "q5_23_sperm_{$field}_other", $this->indent . $this->indent . " Sperm:", array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "98" => "98 Refused", "99" => "99 Do not know", "Not_Answered" => "Not Answered"));
			$this->form->addElement("select", "q5_23_embryo_{$field}_other", $this->indent . $this->indent . " Embryo:", array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "98" => "98 Refused", "99" => "99 Do not know", "Not_Answered" => "Not Answered"));


			$this->form->addRule(array('q5_23_eggs_{$field}_other', 'q5_22_p{$field}'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'08'));
			$this->setRequired('q5_23_eggs_{$field}_other');

			$this->form->addRule(array('q5_23_sperm_{$field}_other', 'q5_22_p{$field}'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'08'));
			$this->setRequired('q5_23_sperm_{$field}_other');

			$this->form->addRule(array('q5_23_embryo_{$field}_other', 'q5_22_p{$field}'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'08'));
			$this->setRequired('q5_23_embryo_{$field}_other');


		}

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "5-24. Were frozen eggs, sperm or embryos used?");

		$this->form->addElement('static', null, $this->indent .  "Using the same PROC codes as in 5-22, choose the appropriate answer for each item.");


		$oneToThree = array("1"=>"#1", "2"=>"#2", "3"=>"#3");
		reset($oneToThree);

		while(list($field, $label) = each($oneToThree)){

			$this->form->addElement('static', null, "<br/>");

			$this->form->addElement('static', null, $this->indent . "PROC {$label}:");

			$this->form->addElement("select", "q5_24_eggs_{$field}", $this->indent . $this->indent . " Eggs:", array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "98" => "98 Refused", "99" => "99 Do not know", "Not_Answered" => "Not Answered"));

			$this->form->addElement("select", "q5_24_sperm_{$field}", $this->indent . $this->indent . " Sperm:", array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "98" => "98 Refused", "99" => "99 Do not know", "Not_Answered" => "Not Answered"));
			$this->form->addElement("select", "q5_24_embryo_{$field}", $this->indent . $this->indent . " Embryo:", array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "98" => "98 Refused", "99" => "99 Do not know", "Not_Answered" => "Not Answered"));


			$this->form->addRule(array('q5_24_eggs_{$field}', 'q5_22_p{$field}'), 'This question is required', 'requiredIf', array('operator'=>'!=', 'value'=>'NULL'));
			$this->setRequired('q5_24_eggs_{$field}');

			$this->form->addRule(array('q5_24_sperm_{$field}', 'q5_22_p{$field}'), 'This question is required', 'requiredIf', array('operator'=>'!=', 'value'=>'NULL'));
			$this->setRequired('q5_24_sperm_{$field}');

			$this->form->addRule(array('q5_24_embryo_{$field}', 'q5_22_p{$field}'), 'This question is required', 'requiredIf', array('operator'=>'!=', 'value'=>'NULL'));
			$this->setRequired('q5_24_embryo_{$field}');

			$this->form->addElement('static', null, $this->indent . "OTHER PROC {$label}:");

			$this->form->addElement("select", "q5_24_eggs_{$field}_other", $this->indent . $this->indent . " Eggs:", array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "98" => "98 Refused", "99" => "99 Do not know", "Not_Answered" => "Not Answered"));

			$this->form->addElement("select", "q5_24_sperm_{$field}_other", $this->indent . $this->indent . " Sperm:", array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "98" => "98 Refused", "99" => "99 Do not know", "Not_Answered" => "Not Answered"));
			$this->form->addElement("select", "q5_24_embryo_{$field}_other", $this->indent . $this->indent . " Embryo:", array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "98" => "98 Refused", "99" => "99 Do not know", "Not_Answered" => "Not Answered"));


			$this->form->addRule(array('q5_24_eggs_{$field}_other', 'q5_22_p{$field}'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'08'));
			$this->setRequired('q5_24_eggs_{$field}_other');

			$this->form->addRule(array('q5_24_sperm_{$field}_other', 'q5_22_p{$field}'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'08'));
			$this->setRequired('q5_24_sperm_{$field}_other');

			$this->form->addRule(array('q5_24_embryo_{$field}_other', 'q5_22_p{$field}'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'08'));
			$this->setRequired('q5_24_embryo_{$field}_other');


		}
		$this->form->addElement('static', null, "<br/>");




	}


	function _page14(){   // ========================================================

		// To implement Xin Rule

		$this->form->addFormRule(array(&$this,'XINValidate'));


		$this->form->addElement('hidden', 'q5_14');
		$this->form->addElement('hidden', 'q5_13');
		$this->form->addElement('hidden', 'q5_16');

		$this->form->addFormRule(array(&$this,'XINValidate'));

		$this->form->addElement("select", "q5_25a", "5-25a. Is [SIBLING]'s biological father known?",  array(NULL=>"", "01_yes" => "01 Yes", "02_no" => "02 No"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>If [SIBLING]'s biological father is unknown, then go to 5-32");

		$this->form->addElement('static', null, "<br/>");

		$this->setRequired('q5_25a');


		$this->form->addElement("select", "q5_25b", "5-25b. Has [the SIBLINGS pregnancy's father] ever been diagnosed by a
medical provider as having male infertility factor?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));


		$this->form->addRule(array('q5_25b', 'q5_25a'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q5_25b');


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q5_26", "5-26. Was the [SIBLINGS]'s father ever tested for anti-sperm antibody?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 5-28");

		$this->form->addRule(array('q5_26', 'q5_25a'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q5_26');


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q5_27", "5-27. What were the results of his your test?",  array(NULL=>"", "01" => "01 Positive", "02" => "02 Negative", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addRule(array('q5_27', 'q5_26'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q5_27');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q5_28", "5-28. Did [SIBLING]'s father take any medications to help you become
pregnant?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));

		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 5-30");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addRule(array('q5_28', 'q5_26'), 'This question is required', 'requiredIf', array('operator'=>'!=', 'value'=>'01'));
		$this->setRequired('q5_28');

		$this->form->addElement('static', null, "5-29. What medications did he take?");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null,  $this->indent . "Probe: Are there any more medications?
If can't recall, ask them to refer to List 5 in prep guide and choose from the following list:");     
		$this->form->addElement('static', null, "<br/>");

		$oneToEight = array("1"=>"#1", "2"=>"#2", "3"=>"#3", "#4"=>"#4", "5"=>"#5", "6"=>"#6", "7"=>"#7", "8"=>"#8");
		reset($oneToEight);

		while(list($field, $label) = each($oneToEight)){

			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement("select", "q5_29_{$field}", $this->indent . $this->indent . " Med {$label}:",  array(NULL=>"", "01" => "01 Bromocriptine", "02" => "02 Clomid", "03" => "03  Chorionic gonadotropin", "04" => "04 Clomiphene citrate", "05" => "05 Danazol", "05" => "05 Danocrine", "06" => "06 Dostinex", "07" => "07 Factrel", "08" => "08 Fertinex", "09" => "09 Follistim", "10" => "10 Gonadorelin", "11" => "11 Gonal-F", "12" => "12 Humegon", "13" => "13 Lupron", "14" => "14 Lutrepulse", "16" => "16 Metrodin", "17" => "17 Novarel", "18" => "18 Parlodel", "19" => "19 Pergonal", "20" => "20 Pregnyl", "21" => "21 Profasi HP", "22" => "22 Provera", "23" => "23 Repronex", "24 Serophene", "25 Synarel", "26" => "26 Other", "88 Refused", "99" => "99 Do not know"));
			$this->form->addElement('textarea', 'q5_29_{$field}_other', $this->indent . $this->indent . " If [Other], please specify. Drug {$label}:");



			$this->form->addRule(array('q5_29_{$field}_other', 'q5_29_{$field}'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'26'));
			$this->setRequired('q5_29_{$field}_other');

		}


		$this->form->addRule(array('q5_29_1', 'q5_28'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q5_29_1');


		$this->form->addElement("select", "q5_30", "5-30. Did [SIBLING PREGNANCY]'s father have any procedures or surgeries to help you
become pregnant?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));

		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 5-32");

		$this->form->addRule(array('q5_30', 'q5_28'), 'This question is required', 'requiredIf', array('operator'=>'!=', 'value'=>'01'));
		$this->setRequired('q5_30');

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "5-31. What was the procedure?");




		$this->form->addElement("select", "q5_31_p1",  $this->indent . $this->indent . "Procedure #1:",  array(NULL=>"",  "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addElement('textarea', 'q5_31_proc1', $this->indent . "If [00 Specify] please specify PROC #1:");

		$this->form->addRule(array('q5_31_p1', 'q5_30'), 'This field is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q5_31_p1');

		$this->form->addRule(array('q5_31_proc1', 'q5_31_p1'), 'This field is required', 'requiredIf', array('operator'=>'==', 'value'=>'00'));
		$this->setRequired('q5_31_proc1');

		$this->form->addElement("select", "q5_31_p2",  $this->indent . $this->indent . "Procedure #1:",  array(NULL=>"",  "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addElement('textarea', 'q5_31_proc2', $this->indent . "If [00 Specify] please specify PROC #2:");
		$this->form->addRule(array('q5_31_proc2', 'q5_31_p2'), 'This field is required', 'requiredIf', array('operator'=>'==', 'value'=>'00'));
		$this->setRequired('q5_31_proc2');


		$this->form->addElement("select", "q5_31_p3",  $this->indent . $this->indent . "Procedure #1:",  array(NULL=>"",  "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));


		$this->form->addElement('textarea', 'q5_31_proc3', $this->indent . "If [00 Specify] please specify PROC #3:");

		$this->form->addRule(array('q5_31_proc3', 'q5_31_p3'), 'This field is required', 'requiredIf', array('operator'=>'==', 'value'=>'00'));
		$this->setRequired('q5_31_proc3');



		//Morning Sickness section
		$this->form->addElement ( 'header', null, "Morning Sickness" );
		$this->form->addElement ( 'static', null, "<b/>Now I have some more detailed questions about your pregnancy with [SIBLING]." );

		//5-32 is automatically required.
		$this->form->addElement ( "select", "q5_32", "5-32. Did you have any nausea with your pregnancy with [SIBLING]?", array (NULL => "", "01_yes" => "01 Yes", "02_no" => "02 No ", "88_refused" => "88 Refused", "99_Do_not_know" => "99 Do not know", "not_answered" => "Not answered" ) );
		$this->form->addElement ( 'static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 5-35" );

		//5-33 is only required is there was nausea form 5-32.
		$negThreeToTen = array_combine(range(-3, 10), range(-3, 10));
		unset($negThreeToTen[0]);
		$answerOptions = array(null=>"") + ($negThreeToTen) + array("88_Refused" => "88 Refused", "99_Do_not_know" => "99 Do not know", "not_answered" => "Not Answered");
		$this->form->addElement ( "select", "q5_33", "5-33. During which months did you have nausea?", $answerOptions, "multiple" );
		$this->XINRegisterRule('q5_33', array("q5_32{@}=={@}01_yes"), "This is required if there was nausea.");  //This rule doesn't work on multiple selects.

		//5-34
		$this->form->addElement ( 'static', null, "5-34. How often during [SPECIFY MONTH] did you have nausea?" );
		$group[] =&$this->form->createElement("static", "month_header");
		$group[] =&$this->form->createElement("static", "freq_header");
		$this->form->addGroup($group, "q5_34_headers", "Would you say it was...", $this->_GUIDelimiter, false);
		unset($group);

		$aToF = array("a", "b", "c", "d", "e", "f");
		foreach($aToF as $label) {
			$group[] =&$this->form->createElement ( "select", "q5_34_m_{$label}", null, array (NULL => "") + $negThreeToTen + array("not_answered" => "Not Answered" ) );
			$group[] =&$this->form->createElement ( "select", "q5_34_f_{$label}", null, array (NULL => "", "01" => "01 Less than once a week", "02" => "02 Once a week", "03" => "03  A few times a week", "04" => "04 Every day", "88 Refused", "99" => "99 Do not know" ) );
			$this->form->addGroup($group, "q5_34_{$label}_group", "{$label})", $this->_GUIDelimiter, false);
			unset($group);
			//Don't require all these questions, but allow them to be filled in, if desired.
			if ($label=="a") continue; //Special rules apply to the first month
			$this->XINRegisterRule("q5_34_m_{$label}", array("q5_32{@}=={@}NEVER_REQUIRED"));
			$this->XINRegisterRule("q5_34_f_{$label}", array("q5_32{@}=={@}NEVER_REQUIRED"));
		}
		//Only require the first month to be answered if there was nausea.
		$this->XINRegisterRule("q5_34_m_a", array("q5_32{@}=={@}01_yes"), "This is required if there was nausea.", "q5_34_a_group");
		$this->XINRegisterRule("q5_34_f_a", array("q5_32{@}=={@}01_yes"), "This is required if there was nausea.", "q5_34_a_group");

		//5-35
		//This is required by default
		$this->form->addElement ( "select", "q5_35", "5-35. Did you have any vomiting?", array (NULL => "", "01_yes" => "01 Yes", "02_no" => "02 No ", "88_refused" => "88 Refused", "99_Do_not_know" => "99 Do not know", "Not_Answered" => "Not answered" ) );
		$this->form->addElement ( 'static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 5-38" );

		//5-36
		unset($answerOptions[10]); //only want months -3 -> 09 this time.
		$this->form->addElement ( "select", "q5_36", "5-36. During which months did you vomit? Choose all that apply:", $answerOptions, "multiple");
		$this->XINRegisterRule("q5_36", array("q5_35{@}=={@}01_yes"), "Please select all months");

		//5-37
		$this->form->addElement ( 'static', null, "5-37. How often during [SPECIFY MONTH] did you vomit?" );
		$group[] =&$this->form->createElement("static", "month_header");
		$group[] =&$this->form->createElement("static", "freq_header");
		$this->form->addGroup($group, "q5_37_headers", "Would you say it was...", $this->_GUIDelimiter, false);
		unset($group);

		unset($negThreeToTen[10]); //only want to go up to 9
		foreach($aToF as $label) {
			$group[] = &$this->form->createElement( "select", "q5_37_m_{$label}", null, array (NULL => "") + $negThreeToTen + array("not_answered" => "Not Answered"));
			$group[] = &$this->form->createElement ( "select", "q5_37_f_{$label}", null, array (NULL => "", "01" => "01 Less than once a week", "02" => "02 Once a week", "03" => "03  A few times a week", "04" => "04 Every day", "88 Refused", "99" => "99 Do not know" ) );
			$this->form->addGroup($group, "q5_37_{$label}_group", "{$label})", $this->_GUIDelimiter, false);
			unset($group);
			//Don't require all questions, but allow them to be filled in, if desired.
			if ($label=="a") continue; //Special rules apply to the first month
			$this->XINRegisterRule("q5_37_m_{$label}", array("q5_35{@}=={@}NEVER_REQUIRED"));
			$this->XINRegisterRule("q5_37_f_{$label}", array("q5_35{@}=={@}NEVER_REQUIRED"));
		}
		//Only require the first month to be answered, if there was vomiting.  Trust that the rest will be filled in as needed.
		$this->XINRegisterRule("q5_37_m_a", array("q5_35{@}=={@}01_yes"), "This is required if there was vomiting", "q5_37_a_group");
		$this->XINRegisterRule("q5_37_f_a", array("q5_35{@}=={@}01_yes"), "This is required if there was vomiting", "q5_37_a_group");

		//5-38
		$this->form->addElement ( 'static', null, $this->indent . "If nausea or vomiting occurred during pregnancy (i.e., 5-32 or 5-35= [Yes]), then go to 5-38." );
		$this->form->addElement ( 'static', null, $this->indent . "If no nausea or vomiting occurred during pregnancy (i.e 5-32 and 5-35 = [No] or [Refused] or [Don't Know]), then go to  5-40." );
		$this->form->addElement ( "select", "q5_38", "5-38. Did you ever require medical treatment for the nausea or vomiting?", array (NULL => "", "01_yes" => "01 Yes", "02_no" => "02 No ", "88_refused" => "88 Refused", "99_Do_not_know" => "99 Do not know", "Not_Answered" => "Not answered" ) );
		$this->XINRegisterRule ( "q5_38", array ("q5_32{@}=={@}01_yes|q5_35{@}=={@}01_yes" ), 'This field is required since there was nausea or vomiting');
		$this->form->addElement ( 'static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 5-40" );

		//5-39
		$this->form->addElement ( 'select', "q5_39", "5-39. What medicine/treatment did you take? Was it...", array (NULL => "", "01_vitB6" => "01 Vitamin B6 (pyridoxine)", "02_unisom" => "02 Unisom (doxylamine)", "03_emetrol" => "03  Emetrol", "04_ginger" => "04 Ginger", "05_other" => "05 Other", "88_Refused" => "88 Refused", "99_Do_not_know" => "99 Do not know", "Not_Answered" => "Not Answered" ), "multiple");
		$this->XINRegisterRule("q5_39", array("q5_38{@}=={@}01_yes"), "Please describe the medicine"); //This rule doesn't appear to work at all due to q5_39 being a select multiple.  Oh well, best to just leave it alone.
		$this->addTextElement("q5_39_other", $this->indent . "If 05 Other, please specify", array("q5_39{@}=={@}NEVER_REQUIRED")); //Rules don't read multiple selects either.




		$this->form->addElement('static', null, "<br/>");


		$this->form->addRule(array('q5_39_med_1', 'q5_38'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q5_39_med_1');



		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/Prenatal Care>");

		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q5_40",  "5-40. During your pregnancy with [SIBLING], how many ultrasounds did you have?",   array(NULL=>"",  "0", "1" => "1", "2" => "2", "3" => "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));



	}





	function _page15(){   // ========================================================


		// To implement Xin Rule

		$this->form->addFormRule(array(&$this,'XINValidate'));
		$this->form->addElement("select", "q5_41", "5-41. Did you have an Amniocentesis or amnio?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 5-44");


		$this->form->addElement("select", "q5_42", $this->indent . "5-42. When was it done?",  array(NULL=>"", "00_sd" => "00 Specify date", "00_sw" => "00 Specify gestational weeks", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addElement('date', 'q5_42_date', "If [00 Specify date] please specify date:", $dateOptions);

		$this->form->addElement("select", "q5_42_week", "If [00 Specify gestational weeks] please specify weeks:" ,array(NULL=>"", "1", "2", "3", "4", "5", "6", "7", "8", "9","10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21" => "21", "22", "23" => "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "36", "37", "38", "39", "40", "41", "42", "43", "44", "45"));
		$this->form->addRule(array('q5_42', 'q5_41'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q5_42');

		$this->form->addRule(array('q5_42_date', 'q5_42'), 'Please specify', 'requiredIf', array('operator'=>'==', 'value'=>'00_sd'));
		$this->setRequired('q5_42_date');

		$this->form->addRule(array('q5_42_week', 'q5_42'), 'Please specify', 'requiredIf', array('operator'=>'==', 'value'=>'00_sw'));
		$this->setRequired('q5_42_week');

		$this->form->addElement("select", "q5_43", "5-43. Were there any abnormalities detected?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addRule(array('q5_43', 'q5_41'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q5_43');



		$this->form->addElement("select", "q5_44", "5-44. Did you have an audible fetal heart rate assessment?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 5-47");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addRule(array('q5_44', 'q5_41'), 'This question is required', 'requiredIf', array('operator'=>'!=', 'value'=>'01'));
		$this->setRequired('q5_44');

		$this->form->addElement("select", "q5_45", "5-45. When was it done?",  array(NULL=>"",  "00_sd" => "00 Specify date", "00_sw" => "00 Specify gestational weeks", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addElement('date', 'q5_45_date', "If [00 Specify date] please specify date:", $dateOptions);

		$this->form->addElement("select", "q5_45_week", "If [00 Specify gestational weeks] please specify weeks:" ,array(NULL=>"", "1", "2", "3", "4", "5", "6", "7", "8", "9","10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21" => "21", "22", "23" => "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "36", "37", "38", "39", "40", "41", "42", "43", "44", "45"));
		$this->form->addRule(array('q5_45', 'q5_44'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q5_45');

		$this->form->addRule(array('q5_45_date', 'q5_45'), 'Please specify', 'requiredIf', array('operator'=>'==', 'value'=>'00_sd'));
		$this->setRequired('q5_45_date');

		$this->form->addRule(array('q5_45_week', 'q5_45'), 'Please specify', 'requiredIf', array('operator'=>'==', 'value'=>'00_sw'));
		$this->setRequired('q5_45week');

		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q5_46", "5-46. Were there any abnormalities detected?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addRule(array('q5_46', 'q5_44'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q5_46');

		$this->form->addElement("select", "q5_47", "5-47. Did you have an antenatal testing?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 5-51");
		$this->form->addRule(array('q5_47', 'q5_43'), 'This question is required', 'requiredIf', array('operator'=>'!=', 'value'=>'01'));
		$this->setRequired('q5_47');
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q5_48", "5-48. What kind of test was done?",  array(NULL=>"", "01" => "01 Non-Stress Test (NST)", "02" => "02 Ultrasound check for fluid (AFI)", "03" => "03  Biophysical Profile (BPP)", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addElement('static', null, "<br/>");
		$this->form->addRule(array('q5_48', 'q5_47'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q5_48');



		$this->form->addElement("select", "q5_49", "5-49. When was it done?",  array(NULL=>"",  "00_sd" => "00 Specify date", "00_sw" => "00 Specify gestational weeks", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addElement('date', 'q5_49_date', "If [00 Specify date] please specify date:", $dateOptions);

		$this->form->addElement("select", "q5_49_week", "If [00 Specify gestational weeks] please specify weeks:" ,array(NULL=>"", "1", "2", "3", "4", "5", "6", "7", "8", "9","10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21" => "21", "22", "23" => "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "36", "37", "38", "39", "40", "41", "42", "43", "44", "45"));
		$this->form->addRule(array('q5_49', 'q5_47'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q5_49');

		$this->form->addRule(array('q5_49_date', 'q5_49'), 'Please specify', 'requiredIf', array('operator'=>'==', 'value'=>'00_sd'));
		$this->setRequired('q5_49_date');

		$this->form->addRule(array('q5_49_week', 'q5_49'), 'Please specify', 'requiredIf', array('operator'=>'==', 'value'=>'00_sw'));
		$this->setRequired('q5_49week');

		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q5_50", "5-50. Were there any abnormalities detected?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addRule(array('q5_50', 'q5_47'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q5_50');



		$this->form->addElement("select", "q5_51", "5-51. Did you have Chorionic Villus Sampling or CVS?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));

		$this->form->addRule(array('q5_51', 'q5_47'), 'This question is required', 'requiredIf', array('operator'=>'!=', 'value'=>'01'));
		$this->setRequired('q5_51');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 5-54");

		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q5_52", "5-52. When was it done?",  array(NULL=>"",  "00_sd" => "00 Specify date", "00_sw" => "00 Specify gestational weeks", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addElement('date', 'q5_52_date', "If [00 Specify date] please specify date:", $dateOptions);

		$this->form->addElement("select", "q5_52_week", "If [00 Specify gestational weeks] please specify weeks:" ,array(NULL=>"", "1", "2", "3", "4", "5", "6", "7", "8", "9","10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21" => "21", "22", "23" => "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "36", "37", "38", "39", "40", "41", "42", "43", "44", "45"));
		$this->form->addRule(array('q5_52', 'q5_51'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q5_52');

		$this->form->addRule(array('q5_52_date', 'q5_52'), 'Please specify', 'requiredIf', array('operator'=>'==', 'value'=>'00_sd'));
		$this->setRequired('q5_52_date');

		$this->form->addRule(array('q5_52_week', 'q5_52'), 'Please specify', 'requiredIf', array('operator'=>'==', 'value'=>'00_sw'));
		$this->setRequired('q5_52week');

		$this->form->addElement('static', null, "<br/>");





		$this->form->addElement("select", "q5_53", "5-53. Were there any abnormalities detected?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");


		$this->form->addRule(array('q5_53', 'q5_51'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q5_53');

		$this->form->addElement("select", "q5_54", "5-54. Were you told that there was [rhesus] or [Rh] incompatibility between
you and [SIBLING PREGNANCY]?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 5-56");

		$this->form->addRule(array('q5_54', 'q5_51'), 'This question is required', 'requiredIf', array('operator'=>'!=', 'value'=>'01'));
		$this->setRequired('q5_54');

		$this->form->addElement("select", "q5_55", "5-55. If your blood type is Rh-, you might have been given injections of
Rhogam. Did you receive any Rhogam injections during your pregnancy
with [SIBLING]?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addRule(array('q5_55', 'q5_54'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q5_55');

		$this->form->addElement("select", "q5_56", "5-56. During your pregnancy with [SIBLING], did you receive shots or
immunizations, such as...",  array(NULL=>"", "01" => "01 Immunoglobulin injection (other than RhoGam)?", "02_no" => "02 No", "03" => "03  Other", "04" => "04 Flu Shot", "05" => "05 Tetanus vaccine", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");


		$this->form->addRule(array('q5_56', 'q5_54'), 'This question is required', 'requiredIf', array('operator'=>'!=', 'value'=>'01'));
		$this->setRequired('q5_56');




		$this->form->addElement("select", "q5_57", "5-57. When was it done?",  array(NULL=>"",  "00_sd" => "00 Specify date", "00_sw" => "00 Specify gestational weeks", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addElement('date', 'q5_57_date', "If [00 Specify date] please specify date:", $dateOptions);

		$this->form->addElement("select", "q5_57_week", "If [00 Specify gestational weeks] please specify weeks:" ,array(NULL=>"", "1", "2", "3", "4", "5", "6", "7", "8", "9","10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21" => "21", "22", "23" => "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "36", "37", "38", "39", "40", "41", "42", "43", "44", "45"));
		$this->form->addRule(array('q5_57', 'q5_55'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q5_57');

		$this->form->addRule(array('q5_57_date', 'q5_57'), 'Please specify', 'requiredIf', array('operator'=>'==', 'value'=>'00_sd'));
		$this->setRequired('q5_57_date');

		$this->form->addRule(array('q5_57_week', 'q5_57'), 'Please specify', 'requiredIf', array('operator'=>'==', 'value'=>'00_sw'));
		$this->setRequired('q5_57week');

		$this->form->addElement('static', null, "<br/>");



	}


	function _page16(){   // ========================================================

		// To implement Xin Rule

		$this->form->addFormRule(array(&$this,'XINValidate'));


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Vaginal Douching");
		$this->form->addElement('static', null, "<b/>Refer to the pregnancy calendar for the following questions.");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q5_58", "5-58. Did you ever douche between [-3] and [DOBS]?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 5-61");
		$this->setRequired('q5_58');

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q5_59", "5-59. Between [-3] and [DOBS], which months did you douche? Choose all that apply:",  array(NULL=>"","-3", "-2", "-1", "01", "02", "03" => "03 ", "04" => "04", "05" => "05", "06" => "06", "07" => "07", "08" => "08", "09" => "09", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered" => "Not Answered"));


		$this->form->addRule(array('q5_59', 'q5_58'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q5_59');
		$this->form->addElement('static', null, $this->indent . "If [Refused] or [Don't Know] skip to question 5-60");

		$this->form->addElement('static', null, "<br/>");





		$this->form->addElement ( 'static', null, "5-60. On average, how often would you say you
douched during [SPECIFY MONTH]?" );
		$group[] =&$this->form->createElement("static", "month_header");
		$group[] =&$this->form->createElement("static", "freq_header");
		$this->form->addGroup($group, "q5_60_headers", "Would you say it was...", $this->_GUIDelimiter, false);
		unset($group);

		unset($negThreeToTen[10]); //only want to go up to 9
		$aToF = array("a", "b", "c", "d", "e", "f");
		foreach($aToF as $label) {
			$group[] = &$this->form->createElement( "select", "q5_60_m_{$label}", null, array (NULL => "") + $negThreeToTen + array("not_answered" => "Not Answered"));
			$group[] = &$this->form->createElement ( "select", "q5_60_f_{$label}", null, array (NULL => "", "01" => "01 Less than once a week", "02" => "02 Once a week", "03" => "03  A few times a week", "04" => "04 Every day", "88 Refused", "99" => "99 Do not know" ) );
			$this->form->addGroup($group, "q5_60_{$label}_group", "{$label})", $this->_GUIDelimiter, false);
			unset($group);
			//Don't require all questions, but allow them to be filled in, if desired.
			if ($label=="a") continue; //Special rules apply to the first month
			$this->XINRegisterRule("q5_60_m_{$label}", array("q5_58{@}=={@}NEVER_REQUIRED"));
			$this->XINRegisterRule("q5_60_f_{$label}", array("q5_58{@}=={@}NEVER_REQUIRED"));
		}
		//Only require the first month to be answered, if there was douching.  Trust that the rest will be filled in as needed.
		$this->XINRegisterRule("q5_60_m_a", array("q5_58{@}=={@}01_yes"), "This is required if there was vomiting", "q5_60_a_group");
		$this->XINRegisterRule("q5_60_f_a", array("q5_58{@}=={@}01_yes"), "This is required if there was douching", "q5_60_a_group");





		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Maternal Medical Conditions");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q5_61", "5-61. During your pregnancy with [SIBLING] were you ever told by a
physician or nurse that you had preeclampsia or toxemia?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 5-64");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q5_62", "5-62. Did you take any medicine for preeclampsia or toxemia?", array(NULL=>"", "01_yes" => "01 Yes", "02_no" => "02 No", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 5-64");
		$this->form->addRule(array('q5_62', 'q5_61'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q5_62');
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q5_63", "5-63. What medication did you take?",  array(NULL=>"","CODE_01"=>"CODE 01: Aldomet", "CODE_02"=>"CODE 02: Labetalol", "CODE_03"=>"CODE 03: Hydralazine", "CODE_04"=>"CODE 04: Nifedipine", "CODE_05"=>"CODE 05: Magnesium Sulfate", "CODE_09"=>"CODE 09: Other"));

		$this->form->addRule(array('q5_63', 'q5_62'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q5_63');

		$this->form->addElement('textarea', 'q5_63_CODE_09_other', $this->indent . $this->indent . "If [CODE 09: Other], please specify:");


		$this->form->addRule(array('q5_63_CODE_09_other', 'q5_63'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'CODE_09'));
		$this->setRequired('q5_63_CODE_09_other');


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Medications for hypertension / preeclampsia:");

		reset($questionArray);
		$questionArray = array("CODE_01"=>"CODE 01: Aldomet", "CODE_02"=>"CODE 02: Labetalol", "CODE_03"=>"CODE 03: Hydralazine", "CODE_04"=>"CODE 04: Nifedipine", "CODE_05"=>"CODE 05: Magnesium Sulfate", "CODE_09"=>"CODE 09: Other");
		reset($questionArray);

		while(list($field, $label) = each($questionArray)) {

			$this->form->addElement('static', null, "{$label}");
			$this->form->addElement("select", "q5_63_1_{$field}",  $this->indent .  "Month medication taken:",  array(NULL=>"","1", "2", "3", "4", "5", "6", "7", "8", "9", "Refused", "Do not know", "Not_Answered" => "Not Answered"));
			$this->form->addElement("select", "q5_63_2_{$field}",  $this->indent .  "Route of
Administration:",  array(NULL=>"","Oral", "Infusion", "Rectal", "Injection", "Infusion", "Not_Answered" => "Not Answered"));

			//testing HTML_QuickForm rules
			//		$field = "one";  //just for now...
			$answerOptions = array(NULL=>"", "tab_per_day" => "_____tabs or caps / day, for ____ days",
			"tab_week"=>"_____tabs or caps / week",
			"tab_month"=>"_____tabs or caps / month",
			"tab_every_day"=>"_____tabs or caps everyday",
			"other" => "Other", "Refused", "Do not know", "Not_Answered" => "Not Answered");
			var_dump($answerOptions);
			$this->form->addElement("select", "q5_63_3_{$field}",  $this->indent . "How often/number of capsules", $answerOptions);

			//        array('key'=>"value");
			//        array('db'=>'seen');

			$this->form->addElement('textarea', 'q5_63_3_{$field}_tabs', $this->indent . $this->indent . "Enter the number of tabs or caps:");
			$this->form->addRule(array('q5_63_3_{$field}_tabs', 'q5_63_3_{$field}'), 'Please specify.', 'requiredIf', array('operator'=>'!=', 'value'=>'NULL'));
			$this->setRequired('q5_63_3_{$field}_tabs');

			$this->form->addElement('textarea', 'q5_63_3_{$field}_day', $this->indent . $this->indent . "If [_____tabs or caps / day, for ____ days], please enter the number of days:");
			$this->form->addRule(array('q5_63_3_{$field}_day', 'q5_63_3_{$field}'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'tab_day'));
			$this->setRequired('q5_63_3_{$field}_day');

			//       $this->form->addElement('textarea', 'q5_63_3_{$field}_other', $this->indent . $this->indent . "If [Other], please specify:");
			$this->addTextElement('q5_63_3_{$field}_other', "If Other (test)");
			$this->form->addRule(array('q5_63_3_{$field}_other', 'q5_63_3_{$field}'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'Other'));
			$this->setRequired('q5_63_3_{$field}_other'); //**************************

		}






	}


	function _page17(){   // ========================================================

		// To implement Xin Rule

		$this->form->addFormRule(array(&$this,'XINValidate'));



		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement ( "select", "q5_64", "5-64. During your pregnancy with [SIBLING] were you ever told by a
physician or nurse that you had premature labor?", array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 5-68");


		$this->form->addElement('static', null, "<br/>");





		$OneToNine = array_combine(range(1, 9), range(1, 9));
		$answerOptions = array(null=>"") + ($OneToNine) + array("88_Refused" => "88 Refused", "99_Do_not_know" => "99 Do not know", "not_answered" => "Not Answered");
		$this->form->addElement ( "select", "q5_65", "5-65. During which months of the pregnancy did you have the
premature labor?", $answerOptions, "multiple" );
		$this->XINRegisterRule('q5_65', array("q5_64{@}=={@}01_yes"), "This is required if you had premature labor.");  //This rule doesn't work on multiple selects.



		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q5_", "5-66. Did you take any medicine for premature labor?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 5-68");
		$this->form->addRule(array('q5_66', 'q5_64'), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'01'));
		$this->setRequired('q5_66');
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "5-67. What medications did you take for preterm labor?");


		$questionArray = array("CODE 01: Terbutaline"=>"CODE 01: Terbutaline", "CODE 02: Magnesium Sulfate"=>"CODE 02: Magnesium Sulfate", "CODE 03: 17 alpha hydroxyl
progesterone acetate"=>"CODE 03: 17 alpha hydroxyl
progesterone acetate", "CODE 04: Indocin"=>"CODE 04: Indocin", "CODE 05: Nifedipine"=>"CODE 05: Nifedipine",  "CODE 06: "=>"CODE 06: ", "CODE 07: "=>"CODE 07: ", "CODE 08: Other"=>"CODE 08: Other");
		reset($questionArray);

		while(list($field, $label) = each($questionArray)){


			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('static', null, "{$label}");
			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement("select", "q5_",  $this->indent .  "Month medication taken:",  array(NULL=>"","1", "2", "3", "4", "5", "6", "7", "8", "9", "Refused", "Do not know", "Not_Answered" => "Not Answered"));
			$this->form->addElement("select", "q5_",  $this->indent .  "Route of
Administration:",  array(NULL=>"","Oral", "Infusion", "Rectal", "Injection", "Infusion", "Not_Answered" => "Not Answered"));

			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement("select", "q5_",  $this->indent . "How often/number of capsules",  array(NULL=>"", "tab_day" => "_____tabs or caps / day, for ____ days", "_____tabs or caps / week", "_____tabs or caps / month", "_____tabs or caps everyday", "Other" => "Other", "Refused", "Do not know", "Not_Answered" => "Not Answered"));

			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('textarea', 'tabs_day', $this->indent . $this->indent . "Enter the number of tabs or caps:");
			$this->form->addElement('textarea', 'other', $this->indent . $this->indent . "If [_____tabs or caps / day, for ____ days], please enter the number of days:");

			$this->form->addElement('textarea', 'other', $this->indent . $this->indent . "If [Other], please specify:");

			$this->form->addRule(array('q5__text', 'q5_'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'0'));
			$this->setRequired('q5__text'); //**************************


		}


	}



	function _page18(){   // ========================================================

		// To implement Xin Rule

		$this->form->addFormRule(array(&$this,'XINValidate'));









		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q5_68", "5-68. During your pregnancy with [SIBLING] did you have vaginal bleeding?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 5-72");

		$this->form->addRule(array('q5_68', 'q5_64'), 'This question is required', 'requiredIf', array('operator'=>'!=', 'value'=>'01'));
		$this->setRequired('q5_68');

		$this->form->addRule(array('q5_68', 'q5_66'), 'This question is required', 'requiredIf', array('operator'=>'!=', 'value'=>'01'));
		$this->setRequired('q5_68');

		$this->form->addElement('static', null, "<br/>");


		$OneToNine = array_combine(range(1, 9), range(1, 9));
		$answerOptions = array(null=>"") + ($OneToNine) + array("88_Refused" => "88 Refused", "99_Do_not_know" => "99 Do not know", "not_answered" => "Not Answered");
		$this->form->addElement ( "select", "q5_69", "5-69. During which months of pregnancy did you have the
bleeding?", $answerOptions, "multiple" );
		$this->XINRegisterRule('q5_69', array("q5_68{@}=={@}01_yes"), "This is required if you had bleeding.");  //This rule doesn't work on multiple selects.



		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q5_", "5-70. Did you take any medicine for the bleeding?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "5-71. What medications did you take for vaginal bleeding?");


		$questionArray = array("CODE 01: Terbutaline"=>"CODE 01: Terbutaline", "CODE 02: Magnesium Sulfate"=>"CODE 02: Magnesium Sulfate", "CODE 03: 17 alpha hydroxyl
progesterone acetate"=>"CODE 03: 17 alpha hydroxyl
progesterone acetate", "CODE 04: Indocin"=>"CODE 04: Indocin", "CODE 05: Nifedipine"=>"CODE 05: Nifedipine",  "CODE 06: "=>"CODE 06: ", "CODE 07: "=>"CODE 07: ", "CODE 08: Other"=>"CODE 08: Other");
		reset($questionArray);

		while(list($field, $label) = each($questionArray)){


			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('static', null, "{$label}");
			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement("select", "q5_",  $this->indent .  "Month medication taken:",  array(NULL=>"","1", "2", "3", "4", "5", "6", "7", "8", "9", "Refused", "Do not know", "Not_Answered" => "Not Answered"));
			$this->form->addElement("select", "q5_",  $this->indent .  "Route of
Administration:",  array(NULL=>"","Oral", "Infusion", "Rectal", "Injection", "Infusion", "Not_Answered" => "Not Answered"));

			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement("select", "q5_",  $this->indent . "How often/number of capsules",  array(NULL=>"", "tab_day" => "_____tabs or caps / day, for ____ days", "_____tabs or caps / week", "_____tabs or caps / month", "_____tabs or caps everyday", "Other" => "Other", "Refused", "Do not know", "Not_Answered" => "Not Answered"));

			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('textarea', 'tabs_day', $this->indent . $this->indent . "Enter the number of tabs or caps:");
			$this->form->addElement('textarea', 'other', $this->indent . $this->indent . "If [_____tabs or caps / day, for ____ days], please enter the number of days:");

			$this->form->addElement('textarea', 'other', $this->indent . $this->indent . "If [Other], please specify:");

			$this->form->addRule(array('q5__text', 'q5_'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'0'));
			$this->setRequired('q5__text'); //**************************


		}

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q5_", "5-72 During your pregnancy with [SIBLING] were you ever told by a
physician or nurse that you had gestational diabetes?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 5-76");

		$this->form->addElement('static', null, "<br/>");


		$OneToNine = array_combine(range(1, 9), range(1, 9));
		$answerOptions = array(null=>"") + ($OneToNine) + array("88_Refused" => "88 Refused", "99_Do_not_know" => "99 Do not know", "not_answered" => "Not Answered");
		$this->form->addElement ( "select", "q5_73", "5-73. During which months did you have the gestational
diabetes?", $answerOptions, "multiple" );
		$this->XINRegisterRule('q5_73', array("q5_72{@}=={@}01_yes"), "This is required if you had gestational diabetes.");  //This rule doesn't work on multiple selects.



		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q5_", "5-74. Did you take any medicine for gestational diabetes?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 5-76");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "5-75. What medications did you take for gestational diabetes?");


		$questionArray = array("CODE 01: Insulin"=>"CODE 01: Insulin", "CODE 02: Glucotrol"=>"CODE 02: Glucotrol", "CODE 03: Glyburide"=>"CODE 03: Glyburide", "CODE 04: Glipizide"=>"CODE 04: Glipizide", "CODE 05: Gludophage /
metformin"=>"CODE 05: Gludophage /
metformin", "CODE 09: Other"=>"CODE 09: Other");
		reset($questionArray);

		while(list($field, $label) = each($questionArray)){


			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('static', null, "{$label}");
			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement("select", "q5_",  $this->indent .  "Month medication taken:",  array(NULL=>"","1", "2", "3", "4", "5", "6", "7", "8", "9", "Refused", "Do not know", "Not_Answered" => "Not Answered"));
			$this->form->addElement("select", "q5_",  $this->indent .  "Route of
Administration:",  array(NULL=>"","Oral", "Infusion", "Rectal", "Injection", "Infusion", "Not_Answered" => "Not Answered"));

			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement("select", "q5_",  $this->indent . "How often/number of capsules",  array(NULL=>"", "tab_day" => "_____tabs or caps / day, for ____ days", "_____tabs or caps / week", "_____tabs or caps / month", "_____tabs or caps everyday", "Other" => "Other", "Refused", "Do not know", "Not_Answered" => "Not Answered"));

			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('textarea', 'tabs_day', $this->indent . $this->indent . "Enter the number of tabs or caps:");
			$this->form->addElement('textarea', 'other', $this->indent . $this->indent . "If [_____tabs or caps / day, for ____ days], please enter the number of days:");

			$this->form->addElement('textarea', 'other', $this->indent . $this->indent . "If [Other], please specify:");

			$this->form->addRule(array('q5__text', 'q5_'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'0'));
			$this->setRequired('q5__text'); //**************************


		}









	}



	function _page19(){   // ========================================================













		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>Now, I am going to ask you about some illnesses, surgeries and other procedures that you might
have had during your pregnancy with [SIBLING]. I'm going to ask you about the time period from
three months before you became pregnant until [DOBS].");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Reproductive and Major Perinatal Infections");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>I am going to start off by asking you about some infections that you might have had during your
pregnancy with [SIBLING]. Please refer to List 7 in your preparatory guide and follow along.");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "5-76. Between [-3] and [DOBS] did you have any
of the following infections?");


		$aToX = array("a. Bacterial Vaginosis" => "A. Bacterial Vaginosis", "b. Candidiasis" => "B. Candidiasis", "c. Chlamydia" => "C. Chlamydia", "d. Chicken pox" => "D. Chicken pox", "e. Cytomegalovirus" => "E. Cytomegalovirus", "f. Genital Herpes" => "F. Genital Herpes", "g. Group B Streptococcal infection" =>"G. Group B Streptococcal infection", "h. Hepatitis A" =>"H. Hepatitis A", "i. Hepatitis B" =>"I. Hepatitis B", "j. Hepatitis C" =>  "J. Hepatitis C", "k. Human Papilloma Virus (HPV)" => "K. Human Papilloma Virus (HPV)", "l. Influenza" => "L. Influenza", "m. Mononucleosis" =>"M. Mononucleosis", "n. Parvovirus or Fifth disease" => "N. Parvovirus or Fifth disease", "o. Pelvic Inflammatory Disease (PID)" => "O. Pelvic Inflammatory Disease (PID)", "p. Pneumonia" => "P. Pneumonia", "q. Rubella or German measles" => "Q. Rubella or German measles", "r. Shingles" => "R. Shingles", "s. Syphilis" => "S. Syphilis", "t. Toxoplasmosis" => "T. Toxoplasmosis", "u. Trichomoniasis" =>"U. Trichomoniasis", "v. Upper respiratory infection" => "V. Upper respiratory infection", "w. Urinary tract infection " => "W. Urinary tract infection ", "x. Other conditions" => "X. Other conditions");
		reset($aToX);

		while(list($field, $label) = each($aToX)){

			$this->form->addElement('static', null, "<br/>");

			$this->form->addElement("select", "med_{$field}", $this->indent . "{$label}:", array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));

		}

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . $this->indent . " If [Yes] for Herpes, go to question 5-77");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . $this->indent . " If [Yes] for Venereal/genital, go to question 5-78");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . $this->indent . " If [Yes] for any other infection on the list, go to question 5-79");
		$this->form->addElement('textarea', 'other', $this->indent . $this->indent . " If [Other conditions], (e.g., vaginitis, fibroids, venereal warts, or endometriosis), please specify:");

		$this->form->addRule(array('q5__text', 'q5_'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'0'));
		$this->setRequired('q5__text'); //**************************


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . $this->indent . " If [No] or [Refused] or [Don't Know] for all, go to question 5-83");

		$this->form->addElement('static', null, "<br/>");



		$this->form->addElement('static', null, "<br/>");


		$OneToNine = array_combine(range(1, 9), range(1, 9));
		$answerOptions = array(null=>"") + ($OneToNine) + array("88_Refused" => "88 Refused", "99_Do_not_know" => "99 Do not know", "not_answered" => "Not Answered");
		$this->form->addElement ( "select", "q5_77", "5-77. During which months from [-3] to [DOBS]
did you have the Herpes outbreak?", $answerOptions, "multiple" );
		$this->XINRegisterRule('q5_77', array("q5_76{@}=={@}01_yes"), "This is required if you had the Herpes outbreak.");  //This rule doesn't work on multiple selects.



		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . $this->indent . " If [Yes] for Herpes, go to question 5-80");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . $this->indent . " If [Yes] for Venereal/genital, go to question 5-80");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . $this->indent . " If [Yes] for any other infection on the list, go to question 5-80");


		$this->form->addElement('static', null, $this->indent . $this->indent . " If [No] or [Refused] or [Don't Know] for all, go to question 5-86");

		$this->form->addElement('static', null, "<br/>");


		$negThreeToTen = array_combine(range(-3, 10), range(-3, 10));
		unset($negThreeToTen[0]);
		$answerOptions = array(null=>"") + ($negThreeToTen) + array("88_Refused" => "88 Refused", "99_Do_not_know" => "99 Do not know", "not_answered" => "Not Answered");
		$this->form->addElement ( "select", "q5_78", "5-78. During which months from [-3] to [DOBS]
did you have the Venereal/genital warts
outbreak?", $answerOptions, "multiple" );
		$this->XINRegisterRule('q5_78', array("q5_77{@}=={@}01_yes"), "This is required if you had the Venereal/genital warts
outbreak.");  //This rule doesn't work on multiple selects.




		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If yes for any other infection on the list, go to question 5-80");
		$this->form->addElement('static', null, $this->indent . $this->indent . " If [No] or [Refused] or [Don't Know] for all infections, go to question 5-83");


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "5-79. During which months
from [-3] to [DOBS] did
you have [INFECTION]?");


		$oneToThree = array("1"=>"#1", "2"=>"#2", "3"=>"#3");
		reset($oneToThree);

		while(list($field, $label) = each($oneToThree)){

			$this->form->addElement('static', null, "<br/>");


			$this->form->addElement ( "select", "q5_79_i_{$field}", "INFECTION {$label}:", array(NULL=>"", "a. Bacterial Vaginosis" => "A. Bacterial Vaginosis", "b. Candidiasis" => "B. Candidiasis", "c. Chlamydia" => "C. Chlamydia", "d. Chicken pox" => "D. Chicken pox", "e. Cytomegalovirus" => "E. Cytomegalovirus", "f. Genital Herpes" => "F. Genital Herpes", "g. Group B Streptococcal infection" =>"G. Group B Streptococcal infection", "h. Hepatitis A" =>"H. Hepatitis A", "i. Hepatitis B" =>"I. Hepatitis B", "j. Hepatitis C" =>  "J. Hepatitis C", "k. Human Papilloma Virus (HPV)" => "K. Human Papilloma Virus (HPV)", "l. Influenza" => "L. Influenza", "m. Mononucleosis" =>"M. Mononucleosis", "n. Parvovirus or Fifth disease" => "N. Parvovirus or Fifth disease", "o. Pelvic Inflammatory Disease (PID)" => "O. Pelvic Inflammatory Disease (PID)", "p. Pneumonia" => "P. Pneumonia", "q. Rubella or German measles" => "Q. Rubella or German measles", "r. Shingles" => "R. Shingles", "s. Syphilis" => "S. Syphilis", "t. Toxoplasmosis" => "T. Toxoplasmosis", "u. Trichomoniasis" =>"U. Trichomoniasis", "v. Upper respiratory infection" => "V. Upper respiratory infection", "w. Urinary tract infection " => "W. Urinary tract infection ", "x. Other conditions" => "X. Other conditions"));


			$this->form->addElement('static', null, "<br/>");
			$negThreeToTen = array_combine(range(-3, 10), range(-3, 10));
			unset($negThreeToTen[0]);
			$answerOptions = array(null=>"") + ($negThreeToTen) + array("88_Refused" => "88 Refused", "99_Do_not_know" => "99 Do not know", "not_answered" => "Not Answered");
			$this->form->addElement ( "select", "q5_79_m_{$field}", "Select all that apply:", $answerOptions, "multiple" );


		}

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q4_", "5-80. Was medication taken for the infection?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 5-83");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "5-81. What did you take? ");


		$oneToThree = array("1"=>"#1", "2"=>"#2", "3"=>"#3");
		reset($oneToThree);

		while(list($field, $label) = each($oneToThree)){

			$this->form->addElement('static', null, "<br/>");

			$this->form->addElement('static', null,  $this->indent . "INFECTION {$label}");
			$oneTo3 = array("1"=>"1", "2"=>"2", "3"=>"3");
			reset($oneTo3);

			while(list($field, $label) = each($oneTo3)){

				$this->form->addElement("select", "q5_",   $this->indent . $this->indent . "Med {$label}:",  array(NULL=>"", "Achromycin ", "Acyclovir ", "Amoxicillin ", "Amoxil ", "Augmentin ", "Azithromycin", "Bactrim", "Biaxin ", "Cefprozil", "Ceftin ", "Cefuroxime", "Cefzil ", "Cephalexin", "Cipro ", "Ciprofloxacin", "Clarithromycin", "Cleocin ", "Clindamycin", "Cofatrim", "Cotrim ", "Diflucan ", "Doxycin", "Doxycycline ", "Doxytec", "Dynacin", "EES", "E-Mycin ", "Erythrocin", "Erythromycin", "Flagyl ", "Fluconazole", "Ilosone", "Keflex ", "Levaquin", "Levofloxacin", "Macrobid ", "Metronidazole", "Minocin", "Minocycline", "Mycostatin", "Nilstat", "Nitrofurantoin", "Novacet ", "Novo-Doxylin", "Nystatin", "Nystex", "Panmycin", "Penicillin", "Penicillin VK ", "Penicillin V potassium", "Protostat", "Quixin", "Septra ", "Sodium sulfacetamide-sulfur", "Sulfatrim", "Sumycin", "Tetracap", "Tetracycline", "Topicycline", "Trimox", "Valacyclovir", "Valtrex ", "Veetids ", "Vibramycin ", "Vibra-Tabs", "Zithromax ", "Zovirax" , "Not_Answered" => "Not Answered"));
			}
		}
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "5-82. When was it taken?");


		$oneToThree = array("1"=>"#1", "2"=>"#2", "3"=>"#3");
		reset($oneToThree);

		while(list($field, $label) = each($oneToThree)){

			$this->form->addElement('static', null, "<br/>");

			$this->form->addElement('static', null,  $this->indent . "INFECTION {$label}");
			$oneTo3 = array("1"=>"1", "2"=>"2", "3"=>"3");
			reset($oneTo3);

			while(list($field, $label) = each($oneTo3)){

				$this->form->addElement("select", "q4_",   $this->indent . $this->indent . "Med {$label}:",  array(NULL=>"", "-3", "-2", "-1", "01", "02", "03" => "03 ", "04" => "04", "05" => "05", "06" => "06", "07" => "07", "08" => "08", "09" => "09", "10" => "10", "Not_Answered" => "Not Answered"));
				$this->form->addElement("select", "q4_",   $this->indent . $this->indent . "",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));   // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

				$this->form->addElement('static', null, "<br/>");
			}
		}
		$this->form->addElement('static', null, "<br/>");



	}


	function _page20(){   // ========================================================

		// To implement Xin Rule

		$this->form->addFormRule(array(&$this,'XINValidate'));
		$negThreeToTen = array_combine(range(-3, 10), range(-3, 10));
		unset($negThreeToTen[0]);











		$this->form->addElement('static', null, "<b/>Other Illnesses");

		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<b/>I am going to ask you about some illnesses that you might have had during your pregnancy with
[SIBLING].");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "5-83. Between [-3] and [DOBS] did you have any of the
following illnesses?");


		$aToM = array("a. Migraine" => "A. Migraine", "b. Depression" => "B. Depression", "c. Nervousness" => "C. Nervousness", "d. Anxiety" => "D. Anxiety", "e. Bipolar" => "E. Bipolar", "f. Other Mental Disorders" => "F. Other Mental Disorders", "g. Epilepsy or Seizure" => "G. Epilepsy or Seizure", "h. Thyroid condition" => "H. Thyroid condition", "i. Allergy" => "I. Allergy", "j. Asthma" =>  "J. Asthma", "k. Arthritis" => "K. Arthritis", "l. Neurologic Disease" => "L. Neurologic Disease", "m. Autoimmune condition" => "M.Autoimmune condition");
		reset($aToM);

		while(list($field, $label) = each($aToM)){

			$this->form->addElement('static', null, "<br/>");

			$this->form->addElement("select", "ill_{$field}", $this->indent . "{$label}:", array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));

		}

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('textarea', 'f', $this->indent . "If yes for any illness on the list, go to question 5-84");

		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] for all, then go to question 5-88");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "5-84. During which months from [-3] to
[DOBS] did you have [illness]?");


		$oneToThree = array("1"=>"#1", "2"=>"#2", "3"=>"#3");
		reset($oneToThree);

		while(list($field, $label) = each($oneToThree)){

			$this->form->addElement('static', null, "<br/>");


			$this->form->addElement ( "select", "q5_84_ill_{$field}", "ILLNESS {$label}:", array(NULL=>"", "a. Migraine" => "A. Migraine", "b. Depression" => "B. Depression", "c. Nervousness" => "C. Nervousness", "d. Anxiety" => "D. Anxiety", "e. Bipolar" => "E. Bipolar", "f. Other Mental Disorders" => "F. Other Mental Disorders", "g. Epilepsy or Seizure" => "G. Epilepsy or Seizure", "h. Thyroid condition" => "H. Thyroid condition", "i. Allergy" => "I. Allergy", "j. Asthma" =>  "J. Asthma", "k. Arthritis" => "K. Arthritis", "l. Neurologic Disease" => "L. Neurologic Disease", "m. Autoimmune condition" => "M.Autoimmune condition"));


			$this->form->addElement('static', null, "<br/>");


			$this->form->addElement('static', null, "<br/>");
			$negThreeToTen = array_combine(range(-3, 10), range(-3, 10));
			unset($negThreeToTen[0]);
			$answerOptions = array(null=>"") + ($negThreeToTen) + array("88_Refused" => "88 Refused", "99_Do_not_know" => "99 Do not know", "not_answered" => "Not Answered");
			$this->form->addElement ( "select", "q5_84_m_{$field}", "Select all that apply:", $answerOptions, "multiple" );


			$this->form->addElement('static', null, "<br/>");



		}

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q4_85", "5-85. Was medication taken for the illness?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 5-88");


		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "5-86. What did you take?");


		$oneToThree = array("1"=>"#1", "2"=>"#2", "3"=>"#3");
		reset($oneToThree);

		while(list($field, $label) = each($oneToThree)){

			$this->form->addElement('static', null, "<br/>");

			$this->form->addElement('static', null,  $this->indent . "ILLNESS {$label}");
			$oneTo3 = array("1"=>"1", "2"=>"2", "3"=>"3");
			reset($oneTo3);

			while(list($field, $label) = each($oneTo3)){

				$this->form->addElement("select", "q5_",   $this->indent . $this->indent . "Med {$label}:",  array(NULL=>"", "Achromycin ", "Acyclovir ", "Amoxicillin ", "Amoxil ", "Augmentin ", "Azithromycin", "Bactrim", "Biaxin ", "Cefprozil", "Ceftin ", "Cefuroxime", "Cefzil ", "Cephalexin", "Cipro ", "Ciprofloxacin", "Clarithromycin", "Cleocin ", "Clindamycin", "Cofatrim", "Cotrim ", "Diflucan ", "Doxycin", "Doxycycline ", "Doxytec", "Dynacin", "EES", "E-Mycin ", "Erythrocin", "Erythromycin", "Flagyl ", "Fluconazole", "Ilosone", "Keflex ", "Levaquin", "Levofloxacin", "Macrobid ", "Metronidazole", "Minocin", "Minocycline", "Mycostatin", "Nilstat", "Nitrofurantoin", "Novacet ", "Novo-Doxylin", "Nystatin", "Nystex", "Panmycin", "Penicillin", "Penicillin VK ", "Penicillin V potassium", "Protostat", "Quixin", "Septra ", "Sodium sulfacetamide-sulfur", "Sulfatrim", "Sumycin", "Tetracap", "Tetracycline", "Topicycline", "Trimox", "Valacyclovir", "Valtrex ", "Veetids ", "Vibramycin ", "Vibra-Tabs", "Zithromax ", "Zovirax" , "Not_Answered" => "Not Answered"));
			}
		}



		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "5-87. When was it taken?");


		$oneToThree = array("1"=>"#1", "2"=>"#2", "3"=>"#3");
		reset($oneToThree);

		while(list($field, $label) = each($oneToThree)){

			$this->form->addElement('static', null, "<br/>");

			$this->form->addElement('static', null,  $this->indent . "ILLNESS {$label}");
			$oneTo3 = array("1"=>"1", "2"=>"2", "3"=>"3");
			reset($oneTo3);

			while(list($field, $label) = each($oneTo3)){

				$this->form->addElement("select", "q4_",   $this->indent . $this->indent . "Med {$label}:",  array(NULL=>"", "-3", "-2", "-1", "01", "02", "03" => "03 ", "04" => "04", "05" => "05", "06" => "06", "07" => "07", "08" => "08", "09" => "09", "10" => "10", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered" => "Not Answered"));

				$this->form->addElement('static', null, "<br/>");
			}
		}
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<b/>Oral/Dental Disease");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Now I am going to ask you about some oral or dental diseases that you might have had during
your pregnancy with [SIBLING].");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q4_", "5-88. Between [-3] and [DOBS], did a doctor or dentist ever tell you that you had
gingivitis or periodontitis?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 5-95");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q4_", "5-89. Did you take any medication for the gingivitis or periodontitis between
[-3] and [DOBS]?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 5-92");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "5-90. What medicine did you take?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If can't recall, refer to List 8a in prep guide and read drug list:");

		$oneToThree = array("1"=>"#1", "2"=>"#2", "3"=>"#3");
		reset($oneToThree);

		while(list($field, $label) = each($oneToThree)){

			$this->form->addElement('static', null, "<br/>");


			$this->form->addElement("select", "med_{$field}", $this->indent . "MED {$label}:", array(NULL=>"", "13" => "13 Clindamycin", "16" => "16 Doxycycline", "24 Metronidazole", "25 Minocyline", "29 Penicillin", "97 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

			$this->form->addElement('textarea', 'other', $this->indent . "If [Other], please specify. OTHER MED {$label}:");

		}

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>For each medication given in 5-90, go to 5-91");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "5-91. During which
months from
[-3] to [DOBS] did
you take
[MEDICATION]?");  

		$oneToThree = array("1"=>"#1", "2"=>"#2", "3"=>"#3");
		reset($oneToThree);

		while(list($field, $label) = each($oneToThree)){

			$this->form->addElement('static', null, "<br/>");


			$negThreeToTen = array_combine(range(-3, 10), range(-3, 10));
			unset($negThreeToTen[0]);
			$answerOptions = array(null=>"") + ($negThreeToTen) + array("88_Refused" => "88 Refused", "99_Do_not_know" => "99 Do not know", "not_answered" => "Not Answered");
			$this->form->addElement ( "select", "q5_91_med_{$field}", "MED {$label} (Select all that apply):", $answerOptions, "multiple" );



		}

		$oneToThree = array("1"=>"#1", "2"=>"#2", "3"=>"#3");
		reset($oneToThree);

		while(list($field, $label) = each($oneToThree)){

			$this->form->addElement('static', null, "<br/>");


			$this->form->addElement ( "select", "q5_91_med_o_{$field}", "Other MED {$label} (Select all that apply):", $answerOptions, "multiple" );


		}


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q5_", "5-92. Did you have any treatment other than antibiotics for gingivitis or
periodontitis between [-3] and [DOBS]?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 5-95");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q5_", "5-93. What treatments did you have? Was it...",  array(NULL=>"", "01" => "01 Root planing and scaling", "02" => "02 Gingival curettage", "03" => "03  Splinting", "04" => "04 Other ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('textarea', 'other', $this->indent . "If [Other], please specify (Other #1):");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('textarea', 'other', $this->indent . "If [Other], please specify (Other #2):");

		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement ( "select", "q5_94", "5-94. During which months from [-3] to
[DOBS] did you get the treatment? (Select all that apply):", $answerOptions, "multiple" );



		$this->form->addElement('static', null, "<br/>");







	}


	function _page21(){   // ========================================================


		// To implement Xin Rule

		$this->form->addFormRule(array(&$this,'XINValidate'));

		$negThreeToTen = array_combine(range(-3, 10), range(-3, 10));
		unset($negThreeToTen[0]);
		$answerOptions = array(null=>"") + ($negThreeToTen) + array("88_Refused" => "88 Refused", "99_Do_not_know" => "99 Do not know", "not_answered" => "Not Answered");





		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Injuries");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>The next few questions are about any injuries that you might have had during your pregnancy
with [SIBLING].");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q5_95", "5-95. During your pregnancy with [SIBLING], did you have an injury that required
medical attention?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 5-106");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('textarea', 'other', $this->indent . "5-96. What injury did you have?");

		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement ( "select", "q5_97", "5-97 Between [-3] and [DOBS], during which
month did this injury happen? (Select all that apply):", $answerOptions, "multiple" );



		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q5_", "5-98. Did you ever lose consciousness because of this injury?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q5_", "5-99. Was medication taken for the injury?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 5-102");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "5-100 What did you take?");
		$this->form->addElement('textarea', 'other', $this->indent . "Med 1:");
		$this->form->addElement('textarea', 'other', $this->indent . "Med 2:");
		$this->form->addElement('textarea', 'other', $this->indent . "Med 3:");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "5-101. When was it taken?");

		$oneToThree = array("1"=>"#1", "2"=>"#2", "3"=>"#3");
		reset($oneToThree);

		while(list($field, $label) = each($oneToThree)){

			$this->form->addElement('static', null, "<br/>");

			$this->form->addElement("select", "q5_",   $this->indent . "MED {$label} (Select all that applyEnter month):",  array(NULL=>"", "-3", "-2", "-1", "01", "02", "03" => "03 ", "04" => "04", "05" => "05", "06" => "06", "07" => "07", "08" => "08", "09" => "09", "Not_Answered" => "Not Answered"));
			$this->form->addElement("select", "q5_",   $this->indent . "",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));   // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
		}

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q5_", "5-102. During your pregnancy with [SIBLING], did you have any other
injury that required medical attention?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 5-106");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'other', "5-103. What was the other injury you had?");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "5-104. Between [-3] and [DOBS], during which
month did this other injury happen?"); 
		$this->form->addElement("select", "q5_", $this->indent . "Month # (Select all that apply):",  array(NULL=>"","-3", "-2", "-1", "01", "02", "03" => "03 ", "04" => "04", "05" => "05", "06" => "06", "07" => "07", "08" => "08", "09" => "09", "10" => "10", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered" => "Not Answered"));


		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q5_", "5-105. Did you ever lose consciousness because of this other injury?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 5-");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Surgery");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Now, I'm going to ask you about any surgeries or procedures that you might have had during
your pregnancy with [SIBLING].");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q5_", "5-106. During your pregnancy with [SIBLING], did you have any dental,
medical, or surgical procedures that required the use of general or
local anesthesia?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 5-110");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "5-107. What procedure(s) did you have done?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'week', $this->indent . "Enter the procedure #1");
		$this->form->addElement("select", "q5_", $this->indent . "",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'week', $this->indent . "Enter the procedure #2");
		$this->form->addElement("select", "q5_", $this->indent . "",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'week', $this->indent . "Enter the procedure #3");
		$this->form->addElement("select", "q5_", $this->indent . "",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "5-108. For [PROCEDURE], did you have general
anesthesia or local anesthesia?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'week', $this->indent . "Procedure #1");
		$this->form->addElement("select", "q5_", $this->indent . "or choose from following:",  array(NULL=>"", "01" => "01 General", "02" => "02 Local", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addElement('static', null, $this->indent . "If [Refused] or [Don't Know] skip to question 5-110");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'week', $this->indent . "Procedure #2");
		$this->form->addElement("select", "q5_", $this->indent . "or choose from following:",  array(NULL=>"", "01" => "01 General", "02" => "02 Local", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, $this->indent . "If [Refused] or [Don't Know] skip to question 5-93");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'week', $this->indent . "Procedure #3");        $this->form->addElement("select", "q5_", $this->indent . "or choose from following:",  array(NULL=>"", "01" => "01 General", "02" => "02 Local", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addElement('static', null, $this->indent . "If [Refused] or [Don't Know] skip to question 5-110");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "5-109. In which month between [-3] and [DOBS]
did you receive the anesthesia?"); 

		$this->form->addElement("select", "q5_", $this->indent . "Month # (Select all that apply):",  array(NULL=>"","-3", "-2", "-1", "01", "02", "03" => "03 ", "04" => "04", "05" => "05", "06" => "06", "07" => "07", "08" => "08", "09" => "09", "10" => "10",  "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered" => "Not Answered"));

	}


	function _page22(){   // ========================================================

		// To implement Xin Rule

		$this->form->addFormRule(array(&$this,'XINValidate'));

		$negThreeToTen = array_combine(range(-3, 10), range(-3, 10));
		unset($negThreeToTen[0]);
		$answerOptions = array(null=>"") + ($negThreeToTen) + array("88_Refused" => "88 Refused", "99_Do_not_know" => "99 Do not know", "not_answered" => "Not Answered");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>Other Procedures");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "5-110. During your pregnancy with [SIBLING], did
you have");


		$aToG = array("a. X-rays, including dental" => "A. X-rays, including dental", "b. Mammogram" => "B. Mammogram", "c. CT/CAT scans" => "C. CT/CAT scans", "d. MRI/magnetic resonance" => "D. MRI/magnetic resonance", "e. Radionuclide study or scan" => "E. Radionuclide study or scan", "f. Radiation treatments or scan" => "F. Radiation treatments or scan", "g. Other" =>"G. Other");

		reset($aToG);

		while(list($field, $label) = each($aToG)){

			$this->form->addElement('static', null, "<br/>");

			$this->form->addElement("select", "med_{$field}", $this->indent . "{$label}:", array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));

			$this->form->addElement('textarea', 'other', $this->indent . 'If [Other], please specify:');
		}

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . $this->indent . " If [yes] for mammogram, go to question 5-112");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . $this->indent . " If [Yes] for any other procedure, go to question 5-111");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] for all, go to question 5-113");

		$this->form->addElement('static', null, "<br/>");


		// 5-111??????????????????????????????????????????????

		// 5-112??????????????????????????????????????????????

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Medication Use");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>This should be asked about medications not already reported before");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>We are interested in medications, including over-the-counter medications that you might have
taken during your pregnancy with [SIBLING].");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>Please refer to LISTS 8A through 8N in your preparatory guide so that we can get the most
accurate information possible.");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>The medications in the list have been organized as best as possible by condition so please look
for the heading and find your medication under that.");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>If you do not see your medication, please look under the ???other medications' category. If your
medication is not listed at all, we still want you to tell us about it. Medications can be in pill form,
nasal spray, patches, creams, etc.");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "5-113. Between [-3] and [DOBS] did you take any
medications for the following conditions?");
		$aToJ = array("a. General headaches" => "A. General headaches", "b. Back pain" => "B. Back pain", "c. Chest pain" => "C.Chest pain ", "d. Cold" => "D. Cold", "e. Acne" => "E. Acne", "f. For dieting" => "F. For dieting", "g. Heartburn" =>"G. Heartburn", "h. To relieve constipation or diarrhea" =>"H. To relieve constipation or diarrhea", "i. Sleep disorder" =>"I. Sleep disorder", "j. Other" =>  "J. Other");
		reset($aToJ);
		while(list($field, $label) = each($aToJ)){

			$this->form->addElement('static', null, "<br/>");

			$this->form->addElement("select", "med_{$field}", $this->indent . "{$label}:", array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));}


			$this->form->addElement('textarea', 'other', $this->indent . "If [Other], please specify:");

			$this->form->addRule(array('q5__text', 'q5_'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'0'));
			$this->setRequired('q5__text'); //**************************



			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('static', null, $this->indent . $this->indent . "If [yes] for any condition in 5-113, go to question 5-114");

			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] for all, skip to the next section");

			$this->form->addElement('static', null, "<br/>");


			// 5-114??????????????????????????????????????????????

			// 5-115??????????????????????????????????????????????



			$this->form->addElement('static', null, "<br/>");


	}


	function _page23(){   // ========================================================

		// To implement Xin Rule

		$this->form->addFormRule(array(&$this,'XINValidate'));

		$negThreeToTen = array_combine(range(-3, 10), range(-3, 10));
		unset($negThreeToTen[0]);
		$answerOptions = array(null=>"") + ($negThreeToTen) + array("88_Refused" => "88 Refused", "99_Do_not_know" => "99 Do not know", "not_answered" => "Not Answered");

		$OneToNine = array_combine(range(1, 9), range(1, 9));
		unset($OneToNine[0]);
		$answerOptions1_9 = array(null=>"") + ($OneToNine) + array("88_Refused" => "88 Refused", "99_Do_not_know" => "99 Do not know", "not_answered" => "Not Answered");



		$this->form->addElement('header', null, "Section 6. DIET");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>Now I am going to ask you some questions regarding your diet.");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		$w = 0; // to choose the varying questions
		$x = 6; // section #
		$y = 1; // question #
		$z = 1; // for "go to question" #z
		for ( $y = 1; $y <= 81; $y += 1){

			$z = $y + 4;


			$questions =  array("During your pregnancy with [SIBLING], did you taken any prenatal vitamins?", "During your pregnancy with [SIBLING] did you taken any Multivitamins?", "During [-3] to [DOBS] did you take any vitamin A?", "During your pregnancy with [SIBLING] did you taken any beta-carotene?", "During your pregnancy with [SIBLING] did you taken any vitamin B6?", "During your pregnancy with [SIBLING], did you taken any vitamin B12?", "During your pregnancy with [SIBLING] did you taken any folic acid?", "During your pregnancy with [SIBLING] did you taken any vitamin C?", "During your pregnancy with [SIBLING] did you taken any vitamin D?", "During your pregnancy with [SIBLING] did you taken any vitamin D-fortified food or drink?", "During your pregnancy with [SIBLING] did you taken any vitamin E?", "During your pregnancy with [SIBLING] did you taken iron?", "During your pregnancy with [SIBLING] did you take any calcium (including a calcium plus vitamin D supplement or antacids, like Tums)?", "During your pregnancy with [SIBLING] have you taken any calcium-fortified food or drink?", "During your pregnancy with [SIBLING] did you take any zinc?", "During your pregnancy with [SIBLING] did you take other supplements, such as Slim Fast, Instant Breakfast, protein powder, or brewer's yeast? ", "During your pregnancy with [SIBLING[ did you take any St. John's Worts?", "During your pregnancy with [SIBLING] did you taken any ginseng?", "During your pregnancy with [SIBLING] did you take any omega-3 fatty acids?", "During your pregnancy with [SIBLING] did you take any fish oil?", "During your pregnancy with [SIBLING] did you take any other supplements or vitamins?");


			$this->form->addElement("select", "q{$x}_{$y}", "{$x}-{$y}. {$questions[$w]}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question {$x}-{$z}");


			$w += 1;
			$y += 1;

			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('textarea', 'other', "{$x}-{$y}. What was the name of the brand you took?");


			$y += 1;

			$this->form->addElement('static', null, "<br/>");


			$this->form->addElement ( "select", "q{$x}_{$y}", "{$x}-{$y}. Which month(s) of pregnancy did you take it? (Select all that apply):", $answerOptions1_9, "multiple" );


			$this->form->addElement('static', null, "<br/>");

			$y += 1;

			$this->form->addElement("select", "q{$x}_{$y}", "{$x}-{$y}. How often/number of capsules did you take?",  array(NULL=>"", "tab_day" => "_____tabs or caps / day, for ____ days", "_____tabs or caps / week", "_____tabs or caps / month", "_____tabs or caps everyday", "Other" => "Other", "Refused", "Do not know", "Not_Answered" => "Not Answered"));

			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('textarea', 'tabs_day_{$x}_{$y}', $this->indent . $this->indent . "Please select the frequency.");
			$this->form->addElement('textarea', 'day_{$x}_{$y}', $this->indent . $this->indent . "If [_____tabs or caps / day, for ____ days], please enter the number of days:");

			$this->form->addElement('textarea', 'other', $this->indent . $this->indent . "If [Other], please specify:");

			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('static', null, "<br/>");

		}
		$this->form->addElement('static', null, "<br/>");




	}


	function _page24(){   // ========================================================

		// To implement Xin Rule

		$this->form->addFormRule(array(&$this,'XINValidate'));

		$negThreeToTen = array_combine(range(-3, 10), range(-3, 10));
		unset($negThreeToTen[0]);
		$answerOptions = array(null=>"") + ($negThreeToTen) + array("88_Refused" => "88 Refused", "99_Do_not_know" => "99 Do not know", "not_answered" => "Not Answered");


		$OneToNine = array_combine(range(1, 9), range(1, 9));
		unset($OneToNine[0]);
		$answerOptions1_9 = array(null=>"") + ($OneToNine) + array("88_Refused" => "88 Refused", "99_Do_not_know" => "99 Do not know", "not_answered" => "Not Answered");



		$this->form->addElement('static', null, "<b/>Water");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>Now I am going to ask you questions regarding your water intake.");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q6_85", "6-85. During your pregnancy with [SIBLING], about how many ounces of plain,
non-carbonated, non-flavored water did you drink daily, including water
used to make juice, punch, or other drinks?",  array(NULL=>"", "01" => "01 More than 64 ounces (8 cups)", "02" => "02 32 - 64 ounces (4 - 8 cups)", "03" => "03  8 - 32 ounces (1 - 4 cups)", "04" => "04 Less than 8 ounces (1 cup)", "05" => "05 None", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [None] or [Refused] or [Don't Know] skip to question 6-96");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q6_86", "6-86. During your pregnancy with [SIBLING], about how much of this plain
drinking water came from your home faucets?",  array(NULL=>"", "01" => "01 All", "02" => "02 Most", "03" => "03  Some", "04" => "04 None", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [None] or [Refused] or [Don't Know] skip to question 6-89");


		$this->form->addElement("select", "q6_87", "6-87. Is the water you drink from your home faucets filtered through any purifier?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 6-89");

		$this->form->addElement("select", "q6_88", "6-88. Please state which type of filtration system you use.",  array(NULL=>"", "01" => "01 Brita", "02" => "02 Pur", "03" => "03  Reverse Osmosis", "04" => "04 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('textarea', 'other', $this->indent . 'If [Other], please specify:');

		$this->form->addElement("select", "q6_89", "6-89.",  array(NULL=>"", "01" => "01 Bottled water", "02" => "02 Dispensed bottled water (large water canister with spigot)", "03" => "03  Tap water and/or drinking fountain", "04" => "04 Other source", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('textarea', 'other', $this->indent . 'If [Other], please specify:');

		$this->form->addElement("select", "q6_90", "6-90. During your pregnancy with [SIBLING], how often did you drink water from
plastic water bottles -- the disposable type that water is sold in?
(ONE NEW BOTTLE = ONE TIME)",  array(NULL=>"", "01" => "01 Never ", "02" => "02 Once every 2 months, or less", "03" => "03  Once a month", "04" => "04 Once every 2 weeks", "05" => "05 Once a week", "06" => "06 Every other day", "07" => "07 Once a day", "08" => "08 Several times a day", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Never] go to question 6-98");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q6_91", "6-91. Did you ever reuse these disposable water bottles?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] go to question 6-93");

		$this->form->addElement("select", "q6_92", "6-92. During your pregnancy with [SIBLING], how often did you drink from
disposable single-use water bottles that had been re-used?",  array(NULL=>"", "01" => "01 Never", "02" => "02 Less than once a month", "03" => "03  1 - 3 times a month", "04" => "04 Once a week", "05" => "05 2 - 3 times a week", "06" => "06 4 - 6 times a week", "07" => "07 Once a day", "08" => "08 More than once a day", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q6_93", "6-93. During your pregnancy with [SIBLING], how often did you drink water from a
disposable single-use water bottle that had been frozen or heated?",  array(NULL=>"", "01" => "01 Never", "02" => "02 Less than once a month", "03" => "03  1 - 3 times a month", "04" => "04 Once a week", "05" => "05 2 - 3 times a week", "06" => "06 4 - 6 times a week", "07" => "07 Once a day", "08" => "08 More than once a day", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q6_94", "6-94. During your pregnancy with [SIBLING], how often did you drink from a nondisposable
(reusable) plastic water bottle?",  array(NULL=>"", "01" => "01 Never", "02" => "02 Less than once a month", "03" => "03  1 - 3 times a month", "04" => "04 Once a week", "05" => "05 2 - 3 times a week", "06" => "06 4 - 6 times a week", "07" => "07 Once a day", "08" => "08 More than once a day", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Never] go to question 6-96");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If or [Refused] or [Don't Know] skip to question 6-96");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('textarea', 'other', "6-95. What was the brand of the non-disposable (reusable)
plastic water bottle you usually used?"); 
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>Food Preparation");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>Now I am going to ask you about your food preparation.");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q6_96", "6-96. During your pregnancy with [SIBLING], how often did you eat prepackaged
foods or meals in a plastic dish or container?",  array(NULL=>"", "01" => "01 Never", "02" => "02 Less than once a month", "03" => "03  1 - 3 times a month", "04" => "04 Once a week", "05" => "05 2 - 3 times a week", "06" => "06 4 - 6 times a week", "07" => "07 Once a day", "08" => "08 More than once a day", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If or [Refused] or [Don't Know] skip to question 6-97");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q6_97", "6-97. During your pregnancy with [SIBLING], how often did you eat prepackaged
foods or meals in a Styrofoam dish or container?",  array(NULL=>"", "01" => "01 Never", "02" => "02 Less than once a month", "03" => "03  1 - 3 times a month", "04" => "04 Once a week", "05" => "05 2 - 3 times a week", "06" => "06 4 - 6 times a week", "07" => "07 Once a day", "08" => "08 More than once a day", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q6_98", "6-98. Do you do the majority of the cooking in the household?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 About half", "03" => "03  No", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 6-101");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q6_99", "6-99. When using the stove-top, what percent of the time do you turn on the vent
over the stove?",  array(NULL=>"", "01" => "01 Never", "02" => "02 Hardly ever (a few times a year)", "03" => "03  Sometimes (once a month)", "04" => "04 Somewhat frequently (2 - 4 times a month)", "05" => "05 Often (at least once a week)", "06" => "06 Always", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q6_99", "6-99. When using the stove-top, what percent of the time do you turn on the vent
over the stove?",  array(NULL=>"", "01" => "01 Never", "02" => "02 Hardly ever (a few times a year)", "03" => "03  Sometimes (once a month)", "04" => "04 Somewhat frequently (2 - 4 times a month)", "05" => "05 Often (at least once a week)", "06" => "06 Always", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q6_100", "6-100. During your pregnancy with [SIBLING], how often did you microwave food in
a plastic container for yourself to eat?",  array(NULL=>"", "01" => "01 Never", "02" => "02 Less than once a month", "03" => "03  Once a month", "04" => "04 Once every 2 weeks", "05" => "05 Once a week", "06" => "06 Every other day", "07" => "07 Once a day", "08" => "08 Several times a day", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q6_101", "6-101. During your pregnancy with [SIBLING] did you use plastic containers to
store food in your household?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q6_102", "6-102. During your pregnancy with [SIBLING], did you use plastic wrap to store
food in your household?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q6_103", "6-103. How many times per week did you eat fast food (including Chinese take-out)
when you were pregnant with [SIBLING]?",  array(NULL=>"", "01" => "01 Never", "02" => "02 Less than once per week", "03" => "03  1 - 3 times per week", "04" => "04 4 - 6 times per week", "05" => "05 7 - 9 times per week", "06" => "06 10 - 12 times per week", "07" => "07 13 - 14 times per week", "08" => "08 15 or more times per week", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q6_104", "6-104. How many times per week did you eat pre-packaged candy or bakery items,
like Twinkies when you were pregnant with [SIBLING?",  array(NULL=>"", "01" => "01 Never", "02" => "02 Less than once per week", "03" => "03  1 - 3 times per week", "04" => "04 4 - 6 times per week", "05" => "05 7 - 9 times per week", "06" => "06 10 - 12 times per week", "07" => "07 13 - 14 times per week", "08" => "08 15 or more times per week", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>Liquid Vitamin");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q6_105", "6-105 In the past trimester, have you taken any liquid vitamins?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to Section 7");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'other', "6-106. What was the name of the brand you took?");


		$this->form->addElement ( "select", "q6_107", "6-107. Which month(s) of pregnancy did you take it? (Select all that apply):", $answerOptions1_9, "multiple" );


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "", "6-108. How often/number of capsules did you take?",  array(NULL=>"", "tab_day" => "_____tabs or caps / day, for ____ days", "_____tabs or caps / week", "_____tabs or caps / month", "_____tabs or caps everyday", "Other" => "Other", "Refused", "Do not know", "Not_Answered" => "Not Answered"));

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'tabs_day_6_108', $this->indent . $this->indent . "Please select the frequency.");
		$this->form->addElement('textarea', 'day_{$x}_{$y}', $this->indent . $this->indent . "If [_____tabs or caps / day, for ____ days], please enter the number of days:");

		$this->form->addElement('textarea', 'other', $this->indent . $this->indent . "If [Other], please specify:");





	}


	function _page25(){   // ========================================================

		// To implement Xin Rule

		$this->form->addFormRule(array(&$this,'XINValidate'));

		$negThreeToTen = array_combine(range(-3, 10), range(-3, 10));
		unset($negThreeToTen[0]);
		$answerOptions = array(null=>"") + ($negThreeToTen) + array("88_Refused" => "88 Refused", "99_Do_not_know" => "99 Do not know", "not_answered" => "Not Answered");




		$this->form->addElement('header', null, "Section 7. HOME ENVIRONMENTAL EXPOSURES");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>Now I will ask you questions about the places you have lived since about 3 months before
becoming pregnant with [SIBLING] until [DOBS]. Please refer to your calendar and to the Mother's
Residential History form.");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Residential History");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('textarea', 'other', $this->indent . "7-1. What is the full address of the home
where you lived? (please include house
or apt number)"); 

		$this->form->addElement('textarea', 'other', $this->indent . "7-2. What was the month and year when you started living here?");


		$this->form->addElement("select", "q7_3", "7-3. What type of residence was/is it?",  array(NULL=>"", "01" => "01 Single house", "02" => "02 House attached to one or more other houses (duplex/triplex/4-plex)", "03" => "03  Building with 2-4 apartments", "04" => "04 Building with 5-19 apartments", "05" => "05 Building with 20 or more apartments", "06" => "06 Condominium", "07" => "07 Mobile home, RV, boat, van etc.", "08" => "08 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Other], please specify:');

		$this->form->addElement("select", "q7_4", "7-4. Is this house, apartment, or mobile home...",  array(NULL=>"", "01" => "01 Owned by you or someone in this household with a mortgage or loan?", "02" => "02 Owned by you or someone in this household free and clear (i.e., without a
mortgage or loan)?", "03" => "03  Rented for cash rent", "04" => "04 Occupied without payment of cash rent?", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('textarea', 'other', $this->indent . 'If [Other], please specify:');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "7-5. How many square feet was the home that you live in?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'week', $this->indent . "Enter square feet ");
		$this->form->addElement("select", "q6_", $this->indent . "",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "7-6. About what year was this house/building built?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Ask participant to make an estimate or check with the landlord if
applicable.");       
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "For an approximate year, code [1980s] as 1985, code [early 1980s] as
1982, code [late 1980s] as 1988, etc.");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('textarea', 'week', $this->indent . "Enter year");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('textarea', 'week', $this->indent . "OR
Approximate year:");
		$this->form->addElement("select", "q7_", $this->indent . "or choose from following:",  array(NULL=>"", "9998 Refused", "9999 Do not know", "Not_Answered" => "Not Answered"));
		$this->form->addElement("select", "q7_", "7-7. Did/does the tap water come from a private well?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q7_", "7-8. About how old was the building when you moved in?",  array(NULL=>"", "01" => "01 More than 50 years old", "02" => "02 25-50 years old", "03" => "03  10-25 years old", "04" => "04 Less than 10 years old", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q7_", "7-9. Was/is the outside of the building painted?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q7_", "7-10. Was/is it within ?? mile of agricultural fields or a golf course?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q7_", "7-11. Was/is it within 3 blocks of a gas station?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q7_", "7-12. Was the house ever tested for lead?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 7-14");

		$this->form->addElement("select", "q7_", "7-13. What were the results of the lead test?",  array(NULL=>"", "01" => "01 High
02 Normal", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q7_", "7-14. Have you lived in any other homes since 3 months prior to your [DOBS]?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If [Yes], [repeat all above questions with insert");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q7_", "7-15. Did you have any problems with dampness in your house or basement when
you were pregnant with [SIBLING}?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 7-17");


		$this->form->addElement("select", "q7_", "7-17 Did anyone use any chemicals to kill the mold, mildew or remove the odor
when you were pregnant with [SIBLING}?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "7-18 Which trimester(s) of pregnancy with [SIBLING] were
these chemicals used?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q7_", "Select all that apply",  array(NULL=>"", "01", "02",  "03","88 Refused", "99" => "99 Do not know", "Not_Answered" => "Not Answered"));


		$this->form->addElement('textarea', 'week', $this->indent . "Enter ");
		$this->form->addElement("select", "q7_", $this->indent . "",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


	}


	function _page26(){   // ========================================================

		// To implement Xin Rule

		$this->form->addFormRule(array(&$this,'XINValidate'));

		$negThreeToTen = array_combine(range(-3, 10), range(-3, 10));
		unset($negThreeToTen[0]);
		$answerOptions = array(null=>"") + ($negThreeToTen) + array("88_Refused" => "88 Refused", "99_Do_not_know" => "99 Do not know", "not_answered" => "Not Answered");


		$negThreeToNine = array_combine(range(-3, 9), range(-3, 9));
		unset($negThreeToNine[0]);
		$answerOptions2 = array(null=>"") + ($negThreeToNine) + array("88_Refused" => "88 Refused", "99_Do_not_know" => "99 Do not know", "not_answered" => "Not Answered");


		$this->form->addElement('static', null, "<b/>Household Product Use");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>Now I am going to ask you about your household product use.");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q7_", "7-19. How often was your home dusted when you were pregnant with [SIBLING]?",  array(NULL=>"", "01" => "01 Never", "02" => "02 At least once per day", "03" => "03  3 to 6 times per week", "04" => "04 1 or 2 times per week", "05" => "05 1 to 3 times per month", "06" => "06 6 to 11 times per year", "07" => "07 1 to 5 times per year", "08" => "08 Less than once per year", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, $this->indent . "If [01 Never], go to question 7-16");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q7_", "7-20. Did you do the dusting when you were pregnant with [SIBLING]?",  array(NULL=>"", "01" => "01 Yes, usually", "02" => "02 No, usually", "03" => "03  About half the time", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q7_", "7-21. During your pregnancy with [SIBLING], approximately how many hours a day
did you keep the windows or doors open in your home? Was it",  array(NULL=>"", "01" => "01 Less than 1 hour per day", "02" => "02 1-3 hours per day", "03" => "03  4-12 hours per day", "04" => "04 More than 12 hours per day, or", "05" => "05 Not at all", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q7_", "7-22. During cleaning of your home with chemical products like aerosols, were
ventilation sources such as fans or windows routinely used when you were
pregnant with [SIBLING]?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");





















		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>Indoor Products");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q7_", "7-23. Between [-3] and [DOBS], did you use paints, stains or lacquers in your
home?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 7-27");


		$this->form->addElement('static', null, "<br/>");



		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "7-24. What was the name of the product? How was it used? Who used it?");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('textarea', 'product', $this->indent . 'Product #1:');

		$this->form->addElement('textarea', 'product', $this->indent . 'How it was used?');
		$this->form->addElement("select", "q7_", $this->indent . "Who used the product",  array(NULL=>"", "Mother", "Father", "Other", "Not_Answered" => "Not Answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'product', $this->indent . 'Product #2:');

		$this->form->addElement('textarea', 'product', $this->indent . 'How it was used?');
		$this->form->addElement("select", "q7_", $this->indent . "Who used the product",  array(NULL=>"", "Mother", "Father", "Other", "Not_Answered" => "Not Answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('textarea', 'product', $this->indent . 'Product #3:');

		$this->form->addElement('textarea', 'product', $this->indent . 'How it was used?');
		$this->form->addElement("select", "q7_", $this->indent . "Who used the product",  array(NULL=>"", "Mother", "Father", "Other", "Not_Answered" => "Not Answered"));
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "7-25. During which months was the product used?");

		$this->form->addElement ( "select", "q7_25_p1", "Product #1: (Select all that apply):", $answerOptions2, "multiple" );
		$this->form->addElement ( "select", "q7_25_p2", "Product #2: (Select all that apply):", $answerOptions2, "multiple" );
		$this->form->addElement ( "select", "q7_25_p3", "Product #3: (Select all that apply):", $answerOptions2, "multiple" );


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "7-26 How often was it used between [-3] and [DOBS]?");
		$this->form->addElement('static', null, "<br/>");

		$oneToThree = array("1"=>"#1", "2"=>"#2", "3"=>"#3");
		reset($oneToThree);

		while(list($field, $label) = each($oneToThree)){

			$this->form->addElement('static', null, "<br/>");

			$this->form->addElement('static', null, $this->indent . "Product {$label}:");

			$this->form->addElement("select", "q7_",   $this->indent . "or choose one of the following:",  array(NULL=>"", "01" => "01 1 day", "02" => "02 2 - 3 days", "03" => "03  4 - 6 days", "04" => "04 1 week", "05" => "05 1 -2 weeks", "06" => "06 2 - 3 weeks", "07" => "07 3 - 4 weeks", "08" => "08 1 month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		}
		$this->form->addElement("select", "q7_", "7-27. Between [-3] and [DOBS], did you use adhesives or petroleum products?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 7-31");


		$this->form->addElement('static', null, "<br/>");



		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "7-28. What was the name of the product? How was it used? Who used it?");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('textarea', 'product', $this->indent . 'Product #1:');

		$this->form->addElement('textarea', 'product', $this->indent . 'How it was used?');
		$this->form->addElement("select", "q7_", $this->indent . "Who used the product",  array(NULL=>"", "Mother", "Father", "Other", "Not_Answered" => "Not Answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'product', $this->indent . 'Product #2:');

		$this->form->addElement('textarea', 'product', $this->indent . 'How it was used?');
		$this->form->addElement("select", "q7_", $this->indent . "Who used the product",  array(NULL=>"", "Mother", "Father", "Other", "Not_Answered" => "Not Answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('textarea', 'product', $this->indent . 'Product #3:');

		$this->form->addElement('textarea', 'product', $this->indent . 'How it was used?');
		$this->form->addElement("select", "q7_", $this->indent . "Who used the product",  array(NULL=>"", "Mother", "Father", "Other", "Not_Answered" => "Not Answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "7-29. During which months was the product used?");



		$this->form->addElement ( "select", "q7_29_p1", "Product #1: (Select all that apply):", $answerOptions2, "multiple" );
		$this->form->addElement ( "select", "q7_29_p2", "Product #2: (Select all that apply):", $answerOptions2, "multiple" );
		$this->form->addElement ( "select", "q7_29_p3", "Product #3: (Select all that apply):", $answerOptions2, "multiple" );

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "7-30. How often was it used between [-3] and [DOBS]?");
		$this->form->addElement('static', null, "<br/>");

		$oneToThree = array("1"=>"#1", "2"=>"#2", "3"=>"#3");
		reset($oneToThree);

		while(list($field, $label) = each($oneToThree)){

			$this->form->addElement('static', null, "<br/>");

			$this->form->addElement('static', null, $this->indent . "Product {$label}:");

			$this->form->addElement("select", "q7_",   $this->indent . "or choose one of the following:",  array(NULL=>"", "01" => "01 1 day", "02" => "02 2 - 3 days", "03" => "03  4 - 6 days", "04" => "04 1 week", "05" => "05 1 -2 weeks", "06" => "06 2 - 3 weeks", "07" => "07 3 - 4 weeks", "08" => "08 1 month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		}

		$this->form->addElement("select", "q7_", "7-31. Between [-3] and [DOBS], were you exposed to any broken thermometers or
thermostats with mercury in them?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 7-33");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement ( "select", "q7_32", "7-32. During which months did this happen? (Select all that apply):", $answerOptions2, "multiple" );


		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q7_", "7-33. Between [-3] and [DOBS], were you exposed to any broken fluorescent light
bulbs?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 7-35");


		$this->form->addElement ( "select", "q7_34", "7-34. During which months did this happen? (Select all that apply):", $answerOptions2, "multiple" );

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q7_", "7-35. Between [-3] and [DOBS], were you exposed to any broken electronic
switches or relays, or broken gauges?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 7-37");


		$this->form->addElement ( "select", "q7_36", "7-36. During which months did this happen? (Select all that apply):", $answerOptions2, "multiple" );



		$this->form->addElement('static', null, "<br/>");


	}


	function _page27(){   // ========================================================

		// To implement Xin Rule

		$this->form->addFormRule(array(&$this,'XINValidate'));




		$this->form->addElement('static', null, "<b/>Personal care products");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "7-37. I am going to read you a list of personal care products. Please
tell me if you used any of the following during your pregnancy
with [SIBLING].");
		$this->form->addElement('static', null, "<br/>");

		$oneToFive = array("1"=>"#1", "2"=>"#2", "3"=>"#3", "#4"=>"#4", "5"=>"#5");
		reset($oneToFive);

		while(list($field, $label) = each($oneToFive)){

			$this->form->addElement('static', null, "<br/>");

			$this->form->addElement("select", "q7_", "Product {$label}:",  array(NULL=>"", "01" => "01 Hair Color", "02" => "02 Nail Polish", "03" => "03  Sun Screen", "04" => "04 Perfume", "05" => "05 Insect Repellant", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->form->addElement('static', null, $this->indent . "If [Refused] or [Don't Know] skip to question 7-39");

		}

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "7-38. While you were pregnant with
[SIBLING], please tell which trimester
or trimesters you use the products?");
		$this->form->addElement('static', null, "<br/>");

		$oneToFive = array("1"=>"#1", "2"=>"#2", "3"=>"#3", "#4"=>"#4", "5"=>"#5");
		reset($oneToFive);

		while(list($field, $label) = each($oneToFive)){

			$this->form->addElement('static', null, "<br/>");

			$this->form->addElement("select", "q7_", "Product {$label}:",  array(NULL=>"", "01" => "01 First Trimester", "02" => "02 Second Trimester", "03" => "03  Third Trimester", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		}
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "7-39 I am going to read you a list of pesticides or pet products.
Please tell me if you used any of the following during your
pregnancy with [SIBLING].");
		$this->form->addElement('static', null, "<br/>");

		$oneToSix = array("1"=>"#1", "2"=>"#2", "3"=>"#3", "#4"=>"#4", "5"=>"#5",  "6"=>"#6");
		reset($oneToSix);

		while(list($field, $label) = each($oneToSix)){

			$this->form->addElement('static', null, "<br/>");

			$this->form->addElement("select", "q7_", "Product {$label}:",  array(NULL=>"", "01" => "01 Ant Traps", "02" => "02 Roach Traps", "03" => "03  Insect Spray", "04" => "04 Fogger", "05" => "05 Flea Treatment for Pets", "06" => "06 Change the cat litter", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

			$this->form->addElement('static', null, $this->indent . "If [Refused] or [Don't Know] skip to question SECTION 8");
		}

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "7-40. While you were pregnant with
[SIBLING], please tell which trimester
or trimesters you used the products?");
		$this->form->addElement('static', null, "<br/>");

		$oneToSix = array("1"=>"#1", "2"=>"#2", "3"=>"#3", "#4"=>"#4", "5"=>"#5",  "6"=>"#6");
		reset($oneToSix);

		while(list($field, $label) = each($oneToSix)){

			$this->form->addElement('static', null, "<br/>");

			$this->form->addElement("select", "q7_", "Product {$label}:",  array(NULL=>"", "01" => "01 First Trimester", "02" => "02 Second Trimester", "03" => "03  Third Trimester", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

			$this->form->addElement('static', null, $this->indent . "If [Refused] or [Don't Know] skip to question SECTION 8");
		}







	}

	function _page28(){   // ========================================================

		// To implement Xin Rule

		$this->form->addFormRule(array(&$this,'XINValidate'));





		$this->form->addElement('header', null, "Section 8. Occupational/Hobby Exposures (Sibling Pregnancy)");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>Now I will ask you questions about your jobs, any volunteer work, school work, and hobbies that
you may have had while you were pregnant with [SIBLING]. Please only include activities that you
did for one hour a week or longer. I will begin by asking about the types of jobs you've had and
whether you've been in school. Please include all jobs and school, whether the work or schooling
were done at home or somewhere else.");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "8-1 Between [-3] and DOBS, how many full time jobs have you had?");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'week', $this->indent . "Enter number:");
		$this->form->addElement("select", "q8_", $this->indent . "",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-2 Between [-3] and DOBS, how many part time jobs have you had?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'week', $this->indent . "Enter number:");
		$this->form->addElement("select", "q8_", $this->indent . "",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-3 Between [-3] and DOBS, how many volunteer jobs have you had? (e.g.
hospital, fire department, humane society)");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'week', $this->indent . "Enter number:");
		$this->form->addElement("select", "q8_", $this->indent . "",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-4 Between [-3] and DOBS, how many schools have you attended had?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'week', $this->indent . "Enter number:");
		$this->form->addElement("select", "q8_", $this->indent . "",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>A. Add responses from 8-1, 8-2, and 8-3 = __________sum of jobs");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>B. Add responses from 8-1, 8-2, 8-3, and 8-4 = __________sum of jobs and school");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>If B (sum of jobs and school) = 0 then go to 8-21");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>If A (sum of jobs) = 1 then go to 8-5");

		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<b/>If A(sum of jobs)= 0 and B(sum of jobs and school) ??? 1 then go to 8-8");

		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<b/>Now I will ask you questions about each one of your jobs, starting with job where you worked the
most hours");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q8_", "8-5 What is your job title or occupation? (For example, teacher, secretary,
nurse, clerk, maid, paralegal, or lab assistant)",  array(NULL=>"", "01" => "01 Any Health Care (Human and Animal)", "02" => "02 Education/Teaching", "03" => "03  Restaurant, Bar, or Food Service", "04" => "04 Cleaning and Building Maintenance", "05" => "05 Child Care (Pre-Kindergarten)", "06" => "06 Beautician/Barber", "07" => "07 Driver", "08" => "08 Agriculture, Farming, Landscaping, Pesticide Workers", "09" => "09 Other Industry or Business", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-6 What type of activities do you do most often at this job? (For
example, teach classes, work on the computer, keep account
books, file, photocopy, answer phone, wait table, help
customers, do lab work, or carpentry)");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "ANY HEALTH CARE (HUMAN AND ANIMAL)",  array(NULL=>"", "01" => "01 Health care provider office (e.g. physicians, dentist, etc.)", "02" => "02 Free-standing outpatient/ambulatory care center facility; Center facility", "03" => "03  Hospital", "04" => "04 Home health care agency", "05" => "05 Skilled nursing facility/rehab facility", "06" => "06 Nursing home/assisted living", "07" => "07 Pharmacy", "08" => "08 Veterinary clinic/hospital", "09" => "09 Other health care facility or service", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Other health care facility or service], please specify:');


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q8_", "EDUCATION/TEACHING",  array(NULL=>"", "10" => "10 Elementary or middle/high school", "11" => "11 Business, technical or trade school", "12" => "12 College or university", "13" => "13 Other school/education provider", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('textarea', 'other', $this->indent . 'If [], please specify:');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q8_", "RESTAURANT, BAR, OR FOOD SERVICE",  array(NULL=>"", "15" => "15 Grocery store bakery (Bakery in a grocery store)", "16" => "16 Restaurant, caterer or other food service (All restaurants, coffee
shops and fast food)", "17" => "17 Bar", "18" => "18 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('textarea', 'other', $this->indent . 'If [Other], please specify:');
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "CLEANING AND BUILDING MAINTENANCE",  array(NULL=>"", "19" => "19 Company that cleans or maintains buildings or homes, include
cleaning schools, homes and hotels", "20" => "20 Clean or maintain a private home (work for one person or family
only)", "21" => "21 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('textarea', 'other', $this->indent . 'If [Other], please specify:');
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "CHILD CARE (PRE-KINDERGARTEN)",  array(NULL=>"", "22" => "22 Child care facility", "23" => "23 Child care in caretaker's home", "24 Child care in child's home", "25 Other child care ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('textarea', 'other', $this->indent . 'If [Other child care], please specify:');
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "BEAUTICIAN/BARBER",  array(NULL=>"", "26 Barber shop", "27 Beauty shop", "28 Nail salon", "29 Other beauty services", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('textarea', 'other', $this->indent . 'If [Other beauty services], please specify:');
		$this->form->addElement('static', null, "<br/>");



		$this->form->addElement("select", "q8_", "DRIVER",  array(NULL=>"", "30 School bus driver", "31 Other public transportation", "32 (bus, subway, light rail, streetcar, ect.)", "33 Taxi and limousine service", "34 Tourism", "35 Postal service", "36 Couriers and messengers", "37 Private households", "38 Trucking", "39 Other driving business or industry", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('textarea', 'other', $this->indent . 'If [Other driving business or industry], please specify:');
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q8_", "AGRICULTURE, FARMING, LANDSCAPING, PESTICIDE WORKERS",  array(NULL=>"", "40 Agriculture/farming-crops", "41 Landscaping services and/or pest/control services", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('textarea', 'other', $this->indent . 'If [], please specify:');
		$this->form->addElement('static', null, "<br/>");



		$this->form->addElement("select", "q8_", "OTHER INDUSTRY OR BUSINESS",  array(NULL=>"", "42 Retail sales", "43 Wholesale", "44 Manufacturing", "45 Warehousing", "46 Information and telecommunications (includes internet)", "47 Finance, insurance, real estate, and leasing", "48 Professional, scientific, management, administrative, social
services", "49 Arts, entertainment and recreation (includes hotels, motels and
bed and breakfasts)", "50 Public administration", "51 Services other than public administration (maintenance and repair,
religious, dry-cleaning, funeral home, civic organizations)", "52 Military", "53 Construction", "54 Airlines", "55 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('textarea', 'other', $this->indent . 'If [Other], please specify:');
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q8_", "8-8 Now think about school, for this school/job, what best describes the place where you typically work/go to school?",  array(NULL=>"", "01" => "01 Office Area", "02" => "02 Store", "03" => "03  Classroom", "04" => "04 Hotel or Motel", "05" => "05 Restaurant", "06" => "06 Residence, such as
your home or someone
else's home", "07" => "07 Healthcare facility or
hospital", "08" => "08 Laboratory", "09" => "09 Factory, plant or
production area", "10" => "10 Warehouse", "11" => "11 Garage or shop", "12" => "12 Some other indoor
location", "13" => "13 Loading dock", "14" => "14 Construction site", "15" => "15 Grounds, yard, or garden", "16" => "16 Some other outdoor location", "17" => "17 Motor vehicle", "18" => "18 Some other outdoor location", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'other', $this->indent . 'If [12 Some other indoor location], please specify:');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'other', $this->indent . 'If [16 Some other outdoor location], please specify:');
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('textarea', 'other', $this->indent . 'If [18 Some other outdoor location], please specify:');
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-9 How long have you been at this job/attending this school?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'week', $this->indent . "Enter the nummber:");
		$this->form->addElement("select", "q8_", $this->indent . "AND choose from following:",  array(NULL=>"", "Years", "months", "weeks", "days"));


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", $this->indent . "OR choose from following:",  array(NULL=>"", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-10 What is the address that you actually
work at this job/attend school?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'week', $this->indent . "Enter address:");
		$this->form->addElement("select", "q8_", $this->indent . "or code from following:",  array(NULL=>"", "01" => "01 Home", "02" => "02 Varies (Construction, Landscaping)", "03" => "03  Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addElement('textarea', 'other', $this->indent . 'If [Other], please specify:');


		$this->form->addElement('static', null, "");
		$this->form->addElement('static', null, "<br/>");

		$mToF = array("Monday"=>"Monday", "Tuesday"=>"Tuesday", "Wednesday"=>"Wednesday", "Thursday"=>"Thursday", "Friday"=>"Friday",  "Saturday"=>"Saturday",  "Sunday"=>"Sunday");
		reset($mToF);

		while(list($field, $label) = each($mToF)){

			$this->form->addElement('static', null, "<br/>");

			$this->form->addElement("select", "q8_", "{$label}:",  array(NULL=>"", "1 Work
Day", "2 Not Work
Day"));

			$this->form->addElement('textarea', 'other', $this->indent . 'Start time:');
			$this->form->addElement('textarea', 'other', $this->indent . 'End time:');
		}

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q8_", "8-12 Was your drinking water source at this school/at that school usually...",  array(NULL=>"", "01" => "01 Tap water", "02" => "02 Filtered tap water", "03" => "03  Bottled water", "04" => "04 Some other source?", "05" => "05 Don't drink water at work", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Some other sourceOther], please specify:');


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Occupational Coding Box");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "n If 8-5 coded [01] and 8-6 coded [01] - [25] OR [30] - [55] then go to the Health Professional Module
(8-127)");
		$this->form->addElement('static', null, "n If 8-5 coded [01] and 8-6 coded [26]-[29], then go to the Beautician/Barber Module then go to 8-291");
		$this->form->addElement('static', null, "n If 8-5 coded [02] and 8-6 coded [01]-[21] or [26] - [55] then go to the Teacher Module then go to8-152");
		$this->form->addElement('static', null, "n If 8-5 coded [02] and 8-6 coded [22]-[25], then go to the Childcare Worker Module then go to8-273");
		$this->form->addElement('static', null, "n If 8-5 coded [03] then go to the Restaurant Worker Module then go to 8-196");
		$this->form->addElement('static', null, "n If 8-5 coded [04] then go to the Cleaners and Building Maintenance Module then go to 8-211");
		$this->form->addElement('static', null, "n If 8-5 coded [05] and 8-6 coded [01]-[21] OR [26] - [55] then go to the Childcare Worker Module then go to 8-
273");

		$this->form->addElement('static', null, "n If 8-5 coded [05] and 8-6 coded [22]-[25], then go to the Teacher Module then go to8-152");
		$this->form->addElement('static', null, "n If 8-5 coded [06] then go to the Beautician/Barber Module then go to8-291");
		$this->form->addElement('static', null, "n If 8-5 coded [07] then go to the Driver Module (8-308)");
		$this->form->addElement('static', null, "n If 8-5 coded [08] then go to the Agricultural Module then go to starts at 8-321");
		$this->form->addElement('static', null, "n If 8-5 coded [09] and 8-6 coded [01] - [09], then go to the Health Professional Module then go to8-127");
		$this->form->addElement('static', null, "n If 8-5 coded [09] and 8-6 coded [10]- [13], then go to the Teacher Module then go to8-152");
		$this->form->addElement('static', null, "n If 8-5 coded [09] and 8-6 coded [14] - [18], then go to the Restaurant Worker Module then go to 8-196");
		$this->form->addElement('static', null, "n If 8-5 coded [09] and 8-6 coded [19] -[21], then go to the Cleaners and Building Maintenance Module (8-211)");
		$this->form->addElement('static', null, "n If 8-5 coded [09] and 8-6 coded [22] - [25], then go to the Childcare Worker Module then go to8-273");
		$this->form->addElement('static', null, "n If 8-5 coded [09] and 8-6 coded [26]- [29], then go to the Beautician/Barber Module then go to8-291");
		$this->form->addElement('static', null, "n If 8-5 coded [09] and 8-6 coded [30] - [39], then go to the Driver Module (8-308)");
		$this->form->addElement('static', null, "n If 8-5 coded [09] and 8-6 coded [40] - [41], then go to the Agricultural Module (starts at 8-321)");
		$this->form->addElement('static', null, "n If 8-5 coded [09] and 8-6 coded [42]- [55], then go to the Generic Exposure Module (starts at 8-98)");
		$this->form->addElement('static', null, "n Otherwise, go to the Generic Exposure Module (starts at 8-98)");
		$this->form->addElement('static', null, "n When complete, continue with 8-13");


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If more than one occupation listed in A. use Occupational Insert forms (questions 8-5 to 8-12) and
each related Occupational Module listed in the Occupational Coding Box and label as OCCUPATION
2 OCCUPATION 3 OCCUPATION 4 etc.");


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-13 Between [-3] and DOBS, have you used or worked around any chemicals,
dust or fumes, radiation, bacteria, or viruses that we have not yet talked
about for this job/school?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to BOX A");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-14 Can you name those chemicals, dust, radiation, bacteria or
viruses?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'week', $this->indent . "Chemical/dust");
		$this->form->addElement("select", "q8_", $this->indent . "",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-15 Please describe your contact with those chemicals, dusts,
radiation, bacteria, or viruses.");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'week', $this->indent . "Description");
		$this->form->addElement("select", "q8_", $this->indent . "",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>Now thinking of the chemicals, dust or fumes, radiation, bacteria, or virus that you mentioned...");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q8_", "8-16 Between [-3] and DOBS, how often did you wear or use personal protective
equipment (PPE) to protect you from the things you have mentioned?",  array(NULL=>"", "01" => "01 Always", "02" => "02 Often", "03" => "03  Rarely", "04" => "04 Never", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Probe: By personal protective equipment, I mean things like gloves, dust masks,
goggles, aprons, lab coats or other protective clothing.");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Never] or [Refused] or [Don't Know] skip to BOX A");

		$this->form->addElement('static', null, "8-17 Which type of protective clothing or
equipment have you worn?");
		$this->form->addElement('static', null, "Code all that apply.");

		$this->form->addElement('static', null, "PROBE: Any other protective clothing or
equipment?");
		$this->form->addElement('static', null, "<br/>");

		$aToH = array("a) Gloves"=>"a) Gloves", "b) Overalls"=>"b) Overalls", "c) Overcoat (e.g. lab coat, smoke, apron)"=>"c) Overcoat (e.g. lab coat, smoke, apron)", "d) Dust mask"=>"d) Dust mask", "e) Goggles or safety glasses"=>"e) Goggles or safety glasses",  "f) Work boots/shoes"=>"f) Work boots/shoes",  "g) Other"=>"g) Other",  "h) Respirator"=>"h) Respirator");
		reset($aToH);

		while(list($field, $label) = each($aToH)){

			$this->form->addElement('static', null, "<br/>");

			$this->form->addElement("select", "q8_", "{$label}:",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));

		}
		$this->form->addElement('textarea', 'other', $this->indent . 'For [g) Other], if [Yes], please specify:');


		$this->form->addElement('static', null, $this->indent . "If [Yes] for any protective clothing in a-g then go
to question 8-19");

		$this->form->addElement('static', null, $this->indent . "If [Yes] for [h] then go
to question 8-18");

		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] for all, then skip to question 8-19");


		$this->form->addElement("select", "q7_", "8-18 What type of respirator was it?",  array(NULL=>"", "01" => "01 A half-mask chemical cartridge respirator, which is silicone or rubber and
covers your mouth and nose", "02" => "02 A full-mask chemical cartridge respirator, which is rubber and covers your eyes, nose, and mouth", "03" => "03  An air-supplied or SCBA respirator", "04" => "04 Some other kind of respirator?", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('textarea', 'other', $this->indent . 'If [Some other kind of respirator], please specify:');

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q7_", "8-19 Was there any kind of a ventilation system to remove exhaust, dust, smoke
or fumes from the area?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Probe: By ventilation system we mean purposely opening windows or doors,
using a fume hood, or other ventilation system.");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to BOX A");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-20 What ventilation systems are
present to remove exhaust, dust,
smoke or fumes from the area? Is
there...");

		$this->form->addElement('static', null, "Code all that apply.");
		$this->form->addElement('static', null, "<br/>");

		$aToF = array("a) A general ventilator system, meaning open doors or
windows, use fan, ect."=>"a) A general ventilator system, meaning open doors or
windows, use fan, ect.", "b) A regular HVAC system for the building and room
heating and cooling"=>"b) A regular HVAC system for the building and room
heating and cooling", "c) A fume hood, lab hood, or other partially enclosed
equipment"=>"c) A fume hood, lab hood, or other partially enclosed
equipment", "d) A glove box or other totally enclosed
equipment"=>"d) A glove box or other totally enclosed
equipment", "e) A portable exhaust hose or tube, such as those used
for welding or to attach to vehicle tailpipe"=>"e) A portable exhaust hose or tube, such as those used
for welding or to attach to vehicle tailpipe",  "f) Some other type of ventilation system"=>"f) Some other type of ventilation system");
		reset($aToF);

		while(list($field, $label) = each($aToF)){

			$this->form->addElement('static', null, "<br/>");

			$this->form->addElement("select", "q8_", "{$label}:",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));

		}
		$this->form->addElement('textarea', 'other', $this->indent . 'Please specify:');
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>BOX A");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Cycle through question 8-5 to BOX A and any related module for each job listed in A. Sum of
Jobs");

		$this->form->addElement('static', null, "Cycle through 8-8 to BOX A and any related module for each school listed in 8-4");
		$this->form->addElement('static', null, $this->indent . "If this is the last job or school then go to question 8-21");


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>Now, I would like to ask some questions about hobbies that you do at home or someplace else.");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q7_", "8-21 In any of your hobbies, do you use chemicals such as pesticides, solvents,
greases, paint, glue, or that generate dusts or fumes, such as woodworking,
soldering or welding?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] then END of INTERVIEW");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-22 Could you please tell me what those hobbies are?");
		$oneToFive = array("1"=>"#1", "2"=>"#2", "3"=>"#3", "#4"=>"#4", "5"=>"#5");
		reset($oneToFive);

		while(list($field, $label) = each($oneToFive)){

			$this->form->addElement('textarea', 'hobby', $this->indent . "Hobby {$label}:");
			$this->form->addElement("select", "q7_", $this->indent . "",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

		}

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-23 How many hours would you estimate that you spend
doing this hobby per month for each hobby you
mentioned?");
		$oneToFive = array("1"=>"#1", "2"=>"#2", "3"=>"#3", "#4"=>"#4", "5"=>"#5");
		reset($oneToFive);

		while(list($field, $label) = each($oneToFive)){

			$this->form->addElement('textarea', 'hobby', $this->indent . "Hobby {$label} (Hours):");
			$this->form->addElement("select", "q7_", $this->indent . "",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

		}

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>BOX B");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If [Yes] to 8-21, then: go to Clean Hands Module, Personal Protective Equipment Module, and then the Ventilation
Module (start with question 8-24)");

		$this->form->addElement('static', null,  $this->indent . "go to Clean Hands Module, Personal Protective Equipment Module, and then the Ventilation
Module (start with question 8-24)");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null,  $this->indent . "When all Modules are complete go to END of INTERVIEW");

		$this->form->addElement('static', null, "<br/>");


	}


	function _page29(){   // ========================================================

		// To implement Xin Rule

		$this->form->addFormRule(array(&$this,'XINValidate'));




		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: CLEAN HANDS");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q7_", "8-24 Did you regularly get chemicals or dust on your hands or skin?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] then end Clean Hands Module and go to 8-27");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-25 When you had chemicals or dust
on your hands, when did you
wash your hands?");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Code all that apply:");

		$this->form->addElement('static', null, "<br/>");
		$aToG = array("a) When taking a break at work"=>"a) When taking a break at work", "b) Before eating"=>"b) Before eating", "c) Before smoking"=>"c) Before smoking", "d) At the end of the work shift"=>"d) At the end of the work shift", "e) When the task is completed"=>"e) When the task is completed",  "f) Whenever I get my hands dirty"=>"f) Whenever I get my hands dirty",  "g) Don't wash hands"=>"g) Don't wash hands");
		reset($aToG);

		while(list($field, $label) = each($aToG)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");


		}


		$this->form->addElement('static', null, $this->indent . "If [Yes] to [g] then end Clean Hands
Module and go to 8-27");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-26 What did you use to wash
chemicals or dust off your hands?");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Code all that apply:");

		$this->form->addElement('static', null, "<br/>");

		$aToE = array("a) Soap and water or water only"=>"a) Soap and water or water only", "b) [Goop] or similar cleaners"=>"b) [Goop] or similar cleaners", "c) Mineral spirits, turpentine, or paint thinner"=>"c) Mineral spirits, turpentine, or paint thinner", "d) Gasoline or kerosene"=>"d) Gasoline or kerosene", "e) Something else"=>"e) Something else");
		reset($aToE);
		while(list($field, $label) = each($aToE)){
			$this->form->addElement("select", "q8_", "{$label}:",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}

		$this->form->addElement('textarea', 'other', $this->indent . 'If [Yes] to [e) Something else], please specify:');


		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: PERSONAL PROTECTIVE EQUIPMENT");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-27 Between [-3] and DOBS, how often did you wear or use personal protective
equipment (PPE) to protect you from the things you have mentioned? By
personal protective equipment, I mean the things like gloves, dust mask,
goggles, aprons, lab coats or other protective clothing, would you say
always, often, rarely, or never us personal protective equipment?",  array(NULL=>"", "01" => "01 Always", "02" => "02 Often", "03" => "03  Rarely", "04" => "04 Never", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Never] or [Refused] or [Don't Know] then end Personal Protective Module and go to 8-30");


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-27a What did you use to wash
chemicals or dust off your hands?");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Code all that apply:");

		$this->form->addElement('static', null, "<br/>");

		$aToE = array("a) Soap and water or water only"=>"a) Soap and water or water only", "b) [Goop] or similar cleaners"=>"b) [Goop] or similar cleaners", "c) Mineral spirits, turpentine, or paint thinner"=>"c) Mineral spirits, turpentine, or paint thinner", "d) Gasoline or kerosene"=>"d) Gasoline or kerosene", "e) Something else"=>"e) Something else");
		reset($aToE);
		while(list($field, $label) = each($aToE)){
			$this->form->addElement("select", "q8_", "{$label}:",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}

		$this->form->addElement('textarea', 'other', $this->indent . 'If [Yes] to [e) Something else], please specify:');


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-28 Which type of protective clothing or equipment did you wear?");
		$this->form->addElement('static', null, "Code all that apply.");

		$this->form->addElement('static', null, "PROBE: Any other protective clothing or
equipment?");
		$this->form->addElement('static', null, "<br/>");

		$aToH = array("a) Gloves"=>"a) Gloves", "b) Overalls"=>"b) Overalls", "c) Overcoat (e.g. lab coat, smoke, apron)"=>"c) Overcoat (e.g. lab coat, smoke, apron)", "d) Dust mask"=>"d) Dust mask",  "e) Respirator"=>"e) Respirator", "f) Goggles or safety glasses"=>"f) Goggles or safety glasses",  "g) Work boots/shoes"=>"g) Work boots/shoes",  "h) Other"=>"h) Other");
		reset($aToH);

		while(list($field, $label) = each($aToH)){

			$this->form->addElement('static', null, "<br/>");

			$this->form->addElement("select", "q8_", "{$label}:",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));

		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Yes] to [h], please specify:');

		$this->form->addElement('static', null, $this->indent . "If [Yes] to [e] then go
to question 8-19");
		$this->form->addElement('static', null, $this->indent . "If [Yes] for [h] then go
to question 8-29");
		$this->form->addElement('static', null, $this->indent . "Otherwise [end Personal Protective
Equipment Module and go to 8-30]");

		$this->form->addElement('static', null, "8-31 What ventilation systems are
present to remove exhaust, dust,
smoke or fumes from the area? Is
there...");

		$this->form->addElement('static', null, "Code all that apply.");
		$this->form->addElement('static', null, "<br/>");
		$aToF = array("a) A general ventilator system, meaning open doors or
windows, use fan, ect."=>"a) A general ventilator system, meaning open doors or
windows, use fan, ect.", "b) A regular HVAC system for the building and room
heating and cooling"=>"b) A regular HVAC system for the building and room
heating and cooling", "c) A fume hood, lab hood, or other partially enclosed
equipment"=>"c) A fume hood, lab hood, or other partially enclosed
equipment", "d) A glove box or other totally enclosed
equipment"=>"d) A glove box or other totally enclosed
equipment", "e) A portable exhaust hose or tube, such as those used
for welding or to attach to vehicle tailpipe"=>"e) A portable exhaust hose or tube, such as those used
for welding or to attach to vehicle tailpipe",  "f) Some other type of ventilation system"=>"f) Some other type of ventilation system");
		reset($aToF);

		while(list($field, $label) = each($aToF)){

			$this->form->addElement('static', null, "<br/>");

			$this->form->addElement("select", "q8_", "{$label}:",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));

		}
		$this->form->addElement('textarea', 'other', $this->indent . 'Please specify:');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-32 For any of the hobbies do you
use...");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$aToG = array("a) Art supplies, such as paint, ceramic glazes or clays"=>"a) Art supplies, such as paint, ceramic glazes or clays", "b) Glue, such as for scrapbooking or other crafts"=>"b) Glue, such as for scrapbooking or other crafts", "c) Pesticides, such as for gardening"=>"c) Pesticides, such as for gardening", "d) Paints, solvents, or paint thinners, such as those used for
furniture repair or painting?"=>"d) Paints, solvents, or paint thinners, such as those used for
furniture repair or painting?", "e) Grease or oils, such as working on your car"=>"e) Grease or oils, such as working on your car",  "f) Solder or welding supplies"=>"f) Solder or welding supplies",  "g) Wood working or carpentry"=>"g) Wood working or carpentry");
		reset($aToG);
		while(list($field, $label) = each($aToG)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] for all 8-24 part A through G go to END of INTERVIEW");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: USING ART SUPPLIES");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "8-33 Which art supplies did you
typically use? Or use at least once
a week?");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Code all that apply:");

		$this->form->addElement('static', null, "<br/>");

		$aToF = array("a) Markers"=>"a) Markers", "b) Paints"=>"b) Paints", "c) Inks"=>"c) Inks", "d) Glazes"=>"d) Glazes", "e) Something else"=>"e) Something else",  "f) No art supplies containing chemicals"=>"f) No art supplies containing chemicals");
		reset($aToF);
		while(list($field, $label) = each($aToF)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Yes] to [e) Something else] then please specify:');


		$this->form->addElement('static', null, "8-34 How often did you use the following art supplies?");
		$this->form->addElement('static', null, "Probe: How many hours per day, per week or per month did you use the
following art supplies?");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Enter number and choose units or select from the list");

		$this->form->addElement('static', null, "<br/>");

		$aToF = array("a) Markers"=>"a) Markers", "b) Paints"=>"b) Paints", "c) Inks"=>"c) Inks", "d) Glazes"=>"d) Glazes", "e) Something else"=>"e) Something else",  "f) No art supplies containing chemicals"=>"f) No art supplies containing chemicals");
		reset($aToF);
		while(list($field, $label) = each($aToF)){
			$this->form->addElement('static', null, "{$label}:");
			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('textarea', 'other', $this->indent . 'Number:');
			$this->form->addElement('textarea', 'other', $this->indent . 'Units:');
			$this->form->addElement("select", "q8_", "or select from the following:",  array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Yes] to [e) Something else] then please specify:');

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: GLUING");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-35 Did you routinely use glues or adhesives?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-36 Which glues did you use?");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Code all that apply:");

		$this->form->addElement('static', null, "<br/>");

		$list = array("a) Hot melt glues or adhesives"=>"a) Hot melt glues or adhesives", "b) Contact adhesives, such as rubber cement"=>"b) Contact adhesives, such as rubber cement", "c) Water-based adhesives, such as vinyl or acrylic resins"=>"c) Water-based adhesives, such as vinyl or acrylic resins", "d) Wood laminates"=>"d) Wood laminates", "e) Something else"=>"e) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [e) Something else] then please specify:');

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-37 How strong was the smell of {hot melt glues/contact adhesives/water-based
adhesives/wood laminates}?");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Code for each yes response in 8-36");

		$this->form->addElement('static', null, "<br/>");

		$list = array("a) Hot melt glues or adhesives"=>"a) Hot melt glues or adhesives", "b) Contact adhesives, such as rubber cement"=>"b) Contact adhesives, such as rubber cement", "c) Water-based adhesives, such as vinyl or acrylic resins"=>"c) Water-based adhesives, such as vinyl or acrylic resins", "d) Wood laminates"=>"d) Wood laminates", "e) Something else"=>"e) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}", array(NULL=>"", "01" => "01 Slight", "02" => "02 Moderate", "03" => "03  Strong", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->form->addElement('static', null, "<br/>");
		}

		$this->form->addElement("select", "q8_", "8-38 Did you wipe off the excess glue or adhesive with a solvent?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-39 What solvent did you typically
wipe it off with?");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Code all that apply:");

		$this->form->addElement('static', null, "<br/>");

		$list = array("a) Acetone"=>"a) Acetone", "b) Paint thinner"=>"b) Paint thinner", "c) Citrus-based chemicals"=>"c) Citrus-based chemicals", "d) Something else"=>"d) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [d) Something else] then please specify:');

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-40 How often did you use the following glues or adhesives?");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Probe: How many hours per day, per week or per month do you use the
following glues or adhesives?");
		$this->form->addElement('static', null, "<br/>");

		$list = array("a) Hot melt glues or adhesives"=>"a) Hot melt glues or adhesives", "b) Contact adhesives, such as rubber cement"=>"b) Contact adhesives, such as rubber cement", "c) Water-based adhesives, such as vinyl or acrylic resins"=>"c) Water-based adhesives, such as vinyl or acrylic resins", "d) Wood laminates"=>"d) Wood laminates", "e) Something else"=>"e) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement('static', null, "{$label}:");
			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('textarea', 'other', $this->indent . 'Number:');
			$this->form->addElement('textarea', 'other', $this->indent . 'Units:');
			$this->form->addElement("select", "q8_", "or select from the following:",  array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('static', null, $this->indent . "If yes 8-24 part c then [go to Pesticide Use Module]");

		$this->form->addElement('static', null, "<br/>");



	}


	function _page30(){   // ========================================================

		// To implement Xin Rule

		$this->form->addFormRule(array(&$this,'XINValidate'));




		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: PESTICIDE USE");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-41 Pesticides include many types of chemicals used to repel, kill, or control
unwanted weeds, insects, rodents, fungi, or bacteria. They include
herbicides, insecticides, rodenticides, fungicides, and bactericides. Did
you mix, apply, spray, process or use pesticides?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 8-64");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-42 Between [3] and DOBS, which
types of pesticides did you use?");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Code all that apply:");

		$this->form->addElement('static', null, "<br/>");

		$list = array("a) Insecticides which kill bugs"=>"a) Insecticides which kill bugs", "b) Herbicides or weed killer"=>"b) Herbicides or weed killer", "c) Rodenticides which kill rats and mice"=>"c) Rodenticides which kill rats and mice", "d) Fungicides which kill mold or fungus"=>"d) Fungicides which kill mold or fungus", "e) Bactericides which kill bacteria"=>"e) Bactericides which kill bacteria",  "f) Something else?"=>"f) Something else?");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [f) Something else] then please specify:');

		$this->form->addElement('static', null, $this->indent . "If [No] to all a-f thengo to 8-52");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-43 Where did you use the pesticides?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$list = array("a) In or around buildings"=>"a) In or around buildings", "b) On crops"=>"b) On crops", "c) On forests"=>"c) On forests", "d) On roads"=>"d) On roads", "e) On seeds"=>"e) On seeds",  "f) On animals"=>"f) On animals",  "g) For aquatic pest control"=>"g) For aquatic pest control",  "h) To process, pack, or manufacture them at warehouse
or factory"=>"h) To process, pack, or manufacture them at warehouse
or factory",  "i) Something else?"=>"i) Something else?");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}        $this->form->addElement('textarea', 'other', $this->indent . 'If [i) Something else] then please specify:');


		$this->form->addElement('static', null, $this->indent . "If [Yes] to [8-42 part a] then go to 8-44");

		$this->form->addElement('static', null, $this->indent . "If [Yes] to [8-42 part b] then go to 8-45");

		$this->form->addElement('static', null, $this->indent . "If [Yes] to [8-42 part c] then go to 8-46");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [8-42 part d] then go to 8-47");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [8-42 part e] then go to 8-48");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-44 You said that you used insecticides or bug killers.
Please name all that you used"); 
		$this->form->addElement('textarea', 'week', $this->indent . "Enter insecticide name:");
		$this->form->addElement("select", "q5_", $this->indent . "",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-45 You said that you used herbicides or weed killers.");
		$this->form->addElement('textarea', 'week', $this->indent . "Enter herbicide name:");
		$this->form->addElement("select", "q5_", $this->indent . "",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-46 You said that you used rodenticides. Please name all
that you use"); 
		$this->form->addElement('textarea', 'week', $this->indent . "Enter rodenticide name:");
		$this->form->addElement("select", "q5_", $this->indent . "",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-47 You said that you used fungicides or mold and
fungus killers. Please name all that you use"); 
		$this->form->addElement('textarea', 'week', $this->indent . "Enter fungicide name:");
		$this->form->addElement("select", "q5_", $this->indent . "",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-48 You said that you used bactericides or bacteria killers.
Please name all that you use"); 
		$this->form->addElement('textarea', 'week', $this->indent . "Enter bactericide name:");
		$this->form->addElement("select", "q5_", $this->indent . "",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-49 How often did you use the following pesticide products?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Probe: How many hours per day, per week or per month do you use the
following glues or adhesives?");
		$this->form->addElement('static', null, "<br/>");

		$list = array("a) Insecticides which kill bugs"=>"a) Insecticides which kill bugs", "b) Herbicides or weed killer"=>"b) Herbicides or weed killer", "c) Rodenticides which kill rats and mice"=>"c) Rodenticides which kill rats and mice", "d) Fungicides which kill mold or fungus"=>"d) Fungicides which kill mold or fungus", "e) Bactericides which kill bacteria"=>"e) Bactericides which kill bacteria",  "f) Something else?"=>"f) Something else?");
		reset($list);
		while(list($field, $label) = each($list)){

			$this->form->addElement('static', null, "{$label}:");
			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('textarea', 'other', $this->indent . 'Number:');
			$this->form->addElement('textarea', 'other', $this->indent . 'Units:');
			$this->form->addElement("select", "q8_", "or select from the following:",  array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->form->addElement('static', null, "<br/>");
		}


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-50 Which of the following activities
did you typically do?");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Code all that apply:");

		$this->form->addElement('static', null, "<br/>");

		$list = array("a) Mix pesticides"=>"a) Mix pesticides", "b) Put pesticides into a spray container or tank"=>"b) Put pesticides into a spray container or tank", "c) Spray or apply pesticides"=>"c) Spray or apply pesticides", "d) Dispose of waste from pesticide use"=>"d) Dispose of waste from pesticide use", "e) Something else?"=>"e) Something else?");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [e) Something else] then please specify:');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q8_", "8-51 Between [-3] and DOBS, were there 3 or more times when your clothing has
gotten wet with pesticides?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");



		$this->form->addElement('static', null, $this->indent . "If [Yes] to [8-43] then go to 8-52");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-52 You said that you apply pesticides
to crops. How did you usually
apply them?");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Code all that apply:");

		$this->form->addElement('static', null, "<br/>");

		$list = array("a) Using hand-held devices"=>"a) Using hand-held devices", "b) By tractor or truck"=>"b) By tractor or truck", "c) By aircraft"=>"c) By aircraft", "d) Something else?"=>"d) Something else?");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [a] then go to question 8-53");
		$this->form->addElement('textarea', 'other', $this->indent . 'If [d) Something else] then please specify:');


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-53 What type of hand-operated
devices did you usually use?");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Code all that apply:");

		$this->form->addElement('static', null, "<br/>");

		$list = array("a) Pressurized can or aerosols"=>"a) Pressurized can or aerosols", "b) Pressurized cylinders"=>"b) Pressurized cylinders", "c) Trigger pump sprayers or squirt guns"=>"c) Trigger pump sprayers or squirt guns", "Hose-end sprayers"=>"Hose-end sprayers", "e) Compressed air sprayers worn on the back pack or
slung over the shoulder"=>"e) Compressed air sprayers worn on the back pack or
slung over the shoulder",  "f) Push-pull hand pump sprayer"=>"f) Push-pull hand pump sprayer",  "g) Something else?"=>"g) Something else?");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [b or c for 8-52] then [go to question 8-54]");


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-54 What type of pesticide application
device did you use for your
vehicle or aircraft?");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Code all that apply:");

		$this->form->addElement('static', null, "<br/>");

		$list = array("a) Low-pressure boomless sprayer"=>"a) Low-pressure boomless sprayer", "b) Boom sprayer"=>"b) Boom sprayer", "c) High pressure hydraulic sprayers"=>"c) High pressure hydraulic sprayers", "d) Air-blast sprayer"=>"d) Air-blast sprayer", "e) Low-volume air sprayer or mist blower"=>"e) Low-volume air sprayer or mist blower",  "f) Ultra-low volume or ULV sprayer (IF NEEDED: uses
fine droplets with little water)"=>"f) Ultra-low volume or ULV sprayer (IF NEEDED: uses
fine droplets with little water)",  "g) Something else?"=>"g) Something else?");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [b for 8-52] then [go to question 8-55 and 8-56]");
		$this->form->addElement("select", "q8_", "8-55 Did the vehicle you used for this usually have a cab?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q8_", "8-56 Did you usually keep the windows open or closed?",  array(NULL=>"", "01" => "01 Open", "02" => "02 Closed", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, $this->indent . "If [Yes] to [8-43 part b, part c, or part d] then [go to question 8-57]");


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-57 What form of pesticide did you
apply?");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Code all that apply:");

		$this->form->addElement('static', null, "<br/>");

		$list = array("a) Liquid"=>"a) Liquid", "b) Dust"=>"b) Dust", "c) Granules (typically used for landscaping)"=>"c) Granules (typically used for landscaping)", "d) Something else?"=>"d) Something else?");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part a] then [go to 8-58]");


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-59 What type of dust did you apply?");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Code all that apply:");

		$this->form->addElement('static', null, "<br/>");

		$list = array("a) Coarse"=>"a) Coarse", "b) Medium"=>"b) Medium", "c) Fine"=>"c) Fine");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part b] then [go to 8-59 and 8-60]");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q8_", "8-60 You said that you applied pesticides to animals. What type of animals did
you typically apply pesticides to?",  array(NULL=>"", "01" => "01 Farm animals", "02" => "02 Companion animals, such as dogs and cats", "03" => "03  Both farm animals and companion animals", "04" => "04 Some other type of animal?", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Some other type of animal], please specify:');


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-61 How did you usually them? Did
you...");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Code all that apply:");

		$this->form->addElement('static', null, "<br/>");

		$list = array("a) Spray the animals"=>"a) Spray the animals", "b) Dust or pour it on animals"=>"b) Dust or pour it on animals", "c) Inject the animals"=>"c) Inject the animals", "d) Use ear tags"=>"d) Use ear tags", "e) Dip the animals"=>"e) Dip the animals",  "f) Use power duster"=>"f) Use power duster",  "g) Use pest strips"=>"g) Use pest strips",  "h) Use fog/mist animals"=>"h) Use fog/mist animals",  "i) Use rope wick"=>"i) Use rope wick",  "j) Use something else"=>"j) Use something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [8-43 part a] then [go to 8-62]");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-62 You said that you applied
pesticides in or around buildings.
Did you usually use a...");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Code all that apply:");

		$this->form->addElement('static', null, "<br/>");

		$list = array("a) Mist blower"=>"a) Mist blowe", "b) Hand-held spray gun or wand with a spray"=>"b) Hand-held spray gun or wand with a spray", "c) Backpack sprayer "=>"c) Backpack sprayer ", "d) Rig that sat on the floor "=>"d) Rig that sat on the floor ", "e) Dust by hand"=>"e) Dust by hand",  "f) Sub-surface application methods, such as for termite control"=>"f) Sub-surface application methods, such as for termite control",  "g) Something else"=>"g) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-63 On average, how many total days a year did you apply pesticides?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'week', $this->indent . "Enter number of days:");
		$this->form->addElement("select", "q8_", $this->indent . "",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [8-24 part d] then [go to Painting, Paint Removal, Paint Cleaning Module, and Organic Solvent Module]");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: PAINTING, PAINT REMOVAL, PAINT CLEANING");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-64 Did you typically do any of the
following activities?");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Code all that apply:");

		$this->form->addElement('static', null, "<br/>");

		$list = array("a"=>"a) Painting, varnishing, or staining", "b"=>"b) Paint removal", "c"=>"c) Paint thinning and cleaning", "d"=>"d) Something else", "e"=>"e) None of the above");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [None of the above] then [go to end of
Painting Module and go to 8-72]");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Refused] or [Don't Know] then [end Painting Module and go to 8-72]");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part a] then [go to 8-65, 8-66,
8-67]");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-65 What kind of paint did you use?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Laytex or water-based paint", "b"=>"b) Acrylic", "c"=>"c) Oil-based paint (enamel)", "d"=>"d) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-66 Did you usually brush, roll, or
spray paint?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Brush", "b"=>"b) Roll", "c"=>"c) Spray", "d"=>"d) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [8-64 part b] then [go to 8-68]");


		$this->form->addElement("select", "q8_", "8-67 Did you use primers with lead, chromate, or zinc?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-68 How did you typically remove
paint?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Heat gun", "b"=>"b) Scraper or wire stripper with a drill bit
attachment", "c"=>"c) Chemical paint stripper", "d"=>"d) Some other paint removal method");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Some other paint removal method] then please specify:');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [8-64 part c] then [go to 8-69]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-69 What did you typically use to thin
or clean paint, varnish or stain");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Paint thinner, mineral spirits, or turpertin", "b"=>"b) Lacquer thinner", "c"=>"c) Alcohol", "d"=>"d) Water", "e"=>"e) Citrus-based products",  "f"=>"f) Gasoline or kerosene",  "g"=>"g) Other");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [8-68 part c] then [go to 8-70]");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-70 What chemicals did you use to
strip paint?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Lacquer or paint thinner", "b"=>"b) Lye (Sodium hydroxide)", "c"=>"c) Ammonia (Ammonia Hydroxide)", "d"=>"d) Other");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Other] then please specify:');
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-71 How often did you use the following paint, paint thinners, or paint
strippers?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Probe: How many hours per day, per week or per month did you use the
following paint, paint thinners, or paint strippers?");
		$this->form->addElement('static', null, "<br/>");

		$list = array("a"=>"a) Laytex or water-based paint", "b"=>"b) Acrylic", "c"=>"c) Oil-based paint (enamel)","d"=>"d) Paint thinner, mineral spirits, or turpertin", "e"=>"e) Lacquer thinner", "f"=>"f) Alcohol", "g"=>"g) Water", "h"=>"h) Citrus-based products",  "i"=>"i) Gasoline or kerosene", "j"=>"j) Lacquer or paint thinner", "k"=>"k) Lye (Sodium hydroxide)", "l"=>"l) Ammonia (Ammonia Hydroxide)", "m"=>"m) Other" );

		reset($list);
		while(list($field, $label) = each($list)){

			$this->form->addElement('static', null, "{$label}:");
			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('textarea', 'other', $this->indent . 'Number:');
			$this->form->addElement('textarea', 'other', $this->indent . 'Units:');
			$this->form->addElement("select", "q8_", "or select from the following:",  array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->form->addElement('static', null, "<br/>");
		}


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: CLEANING WITH ORGANIC SOLVENTS");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-72 Did you routinely clean parts with organic solvents or other products to
degrease metal parts?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] then [end Cleaning with Organic Solvents Module]");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-73 What cleaning products did you
typically use?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) [Gunk] or similar cleaner", "b"=>"b) Acid", "c"=>"c) Alcohols", "d"=>"d) Alkalis or caustics", "e"=>"e) Cutting oils",  "f"=>"f) Diesel",  "g"=>"g) Gasoline",  "h"=>"h) Mineral spirits, paint thinner, naphtha, Stoddard
solvent, turpentin", "i"=>"i) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "8-74 How often did you use the following cleaning products?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Probe: How many hours per day, per week or per month did you use the
following cleaning products?");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) [Gunk] or similar cleaner", "b"=>"b) Acid", "c"=>"c) Alcohols", "d"=>"d) Alkalis or caustics", "e"=>"e) Cutting oils",  "f"=>"f) Diesel",  "g"=>"g) Gasoline",  "h"=>"h) Mineral spirits, paint thinner, naphtha, Stoddard
solvent, turpentin", "i"=>"i) Something else");

		reset($list);
		while(list($field, $label) = each($list)){

			$this->form->addElement('static', null, "{$label}:");
			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('textarea', 'other', $this->indent . 'Number:');
			$this->form->addElement('textarea', 'other', $this->indent . 'Units:');
			$this->form->addElement("select", "q8_", "or select from the following:",  array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->form->addElement('static', null, "<br/>");
		}


		$this->form->addElement("select", "q8_", "8-75 How often did you work with heating degreasing chemicals?",  array(NULL=>"", "01" => "01 Always", "02" => "02 Sometimes", "03" => "03  Never", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 8-");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [8-24 part E] then [go to Lubricating Engines and Machinery Module and Fuel and Exhaust Smells Module]");


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: LUBRICATING ENGINES & MACHINERY");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-76 Did you routinely use lubricating oils, or waxes on engines or machinery?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] then [end Lubricating Module]");


		$this->form->addElement('static', null, "8-77 What types of lubricants did you work with?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'week', $this->indent . "Enter lubricant");
		$this->form->addElement("select", "q8_", $this->indent . "",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-78 What types of cutting oils did you
work with?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Straight cutting oils or oils that look and feel like motor
oil", "b"=>"b) Soluble cutting oils or oils that are milky white", "c"=>"c) Synthetic cutting oils or oils that feel like water or may
be brightly colored, such as green or blue", "d"=>"d) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "8-79 How often did you use the following lubricants?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Probe: How many hours per day, per week or per month did you use the
following lubricants?");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Straight cutting oils or oils that look and feel like motor oil", "b"=>"b) Soluble cutting oils or oils that are milky white", "c"=>"c) Synthetic cutting oils or oils that feel like water or may be brightly colored, such as green or blue", "d"=>"d) Something else");

		reset($list);
		while(list($field, $label) = each($list)){

			$this->form->addElement('static', null, "{$label}:");
			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('textarea', 'other', $this->indent . 'Number:');
			$this->form->addElement('textarea', 'other', $this->indent . 'Units:');
			$this->form->addElement("select", "q8_", "or select from the following:",  array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->form->addElement('static', null, "<br/>");
		}


		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: FUEL AND EXHAUST SMELLS");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q8_", "8-80 Did you regularly smell fuel vapors, such as from gas or fuel tanks, or
exhaust vapors, such as from car or truck tail pipes?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] then [end Fuel and Exhaust Smells Module]");


		$this->form->addElement("select", "q8_", "8-81 How strong was the smell",  array(NULL=>"", "01" => "01 Slight", "02" => "02 Moderate", "03" => "03  Strong", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If [Yes] to [8-24 part F] then [go to Soldering and Welding Module]");
		$this->form->addElement('static', null, "<br/>");





	}


	function _page31(){   // ========================================================

		// To implement Xin Rule

		$this->form->addFormRule(array(&$this,'XINValidate'));





		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: SOLDERING AND WELDING");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-82 Did you do any of the following?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Soldering or brazing", "b"=>"b) Smell fumes from others who solder or
braze", "c"=>"c) Welding or flame cutting", "d"=>"d) Smell fumes from others who weld or flame cut", "e"=>"e) Some other welding or soldering method?",  "f"=>"f) None of the above");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [None of the above] then [END Soldering Module]");
		$this->form->addElement('static', null, $this->indent . "If [Refused] or [Don't Know] to [part a-e] then [END Soldering Module]");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-83 What types of metal did
{you/then/you and those who weld
or flame cut around you} weld or
flame cut?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Aluminum", "b"=>"b) Brass or bronze", "c"=>"c) Cast iron", "d"=>"d) Copper", "e"=>"e) Steel",  "f"=>"f) Titanium-based alloy",  "g"=>"g) Other");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part a-d] then [go to 8-85]");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part f-g] then [go to 8-85]");


		$this->form->addElement('static', null, $this->indent . "If [Refused] or [Don't Know] to [part a-e] then [go to 8-85]");


		$this->form->addElement("select", "q8_", "8-84 What kind of steel was it?",  array(NULL=>"", "01" => "01 Cadmium plated steel", "02" => "02 Chromium plated steel", "03" => "03  Galvanized iron", "04" => "04 Lead-plated or leaded steel", "05" => "05 Mild, carbon, or construction steel", "06" => "06 Stainless steel", "07" => "07 Another type of steel?", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('textarea', 'other', $this->indent . 'If [Another type of steel], please specify:');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q8_", "8-85 What type of welding or flame cutting did {you/they/you and those who weld
or flame cut around you} do?",  array(NULL=>"", "01" => "01 Oxygas, oxyfuel, or oxyacetylene", "02" => "02 MIG (Metal Inert Gas)", "03" => "03  TIG (Tungsten Inert Gas)", "04" => "04 Stick electrode (shielded metal arc welding)", "05" => "05 Resistance, such as sport, seam, flash, butt, and projection", "06" => "06 Solid state, such as friction or roll", "07" => "07 Plasma arc", "08" => "08 Submerged arc", "09" => "09 Something else", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else], please specify:');

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If [Yes] to [8-82 part a or b] then [go to 8-86, 8-87, 8-88, and 8-89]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-86 What did {you/then/you and those
who solder or braze around you}
solder or braze?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Pipes", "b"=>"b) Electrical or electronic parts", "c"=>"c) Other");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-87 Did {you/they/you and those who solder or braze around you} use lead-free
solder?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));

		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q8_", "8-88 Did the solder usually contain any unusual ingredients such as cadmium,
silver, copper, nickel, zinc, arsenic, beryllium, antimony, indium, or
bismuth?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('textarea', 'other', $this->indent . 'If [Yes] then please specify:');


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-89 What did {you/then/you and those
who solder or braze around you}
solder or braze?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Brass", "b"=>"b) Bronze", "c"=>"c) Cast iron", "d"=>"d) Copper", "e"=>"e) Nickel",  "f"=>"f) Other types of iron",  "g"=>"g) Stainless steel",  "h"=>"h) Other steel");

		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [f) Other types of iron] then please specify:');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'other', $this->indent . 'If [i) Other] then please specify:');
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, $this->indent . "If [Yes] to [8-24 part G] then [go to Wood Dust Module]");


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: WOOD DUST");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "8-90 Did you typically do any of the
following:");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Saw wood", "b"=>"b) Sand wood", "c"=>"c) Machine or make wood parts", "d"=>"d) Use a wood chipper", "e"=>"e) Other activities that generate wood",  "f"=>"f) None of these");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Other activities that generate wood] then please specify:');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [None of these] then [go to 8-92]");

		$this->form->addElement('static', null, $this->indent . "If [Refused] or [Don't Know] to [part a-f] then [go to 8-92]");

		$this->form->addElement('static', null, "8-91 How often did you do these things?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Probe: How many hours per day, per week, or per month do you saw wood,
sand wood, do machining, make wood parts, use a wood chipper, or other
activities that generate wood dust?");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Saw wood", "b"=>"b) Sand wood", "c"=>"c) Machine or make wood parts", "d"=>"d) Use a wood chipper", "e"=>"e) Other activities that generate wood",  "f"=>"f) None of these");

		reset($list);
		while(list($field, $label) = each($list)){

			$this->form->addElement('static', null, "{$label}:");
			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('textarea', 'other', $this->indent . 'Number:');
			$this->form->addElement('textarea', 'other', $this->indent . 'Units:');
			$this->form->addElement("select", "q8_", "or select from the following:",  array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->form->addElement('static', null, "<br/>");
		}

		$this->form->addElement("select", "q8_", "8-92 Did your job typically involve handling treated lumber, that is wood treated
with chemical preservatives and has a greenish appearance?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] then [end Wood Module]");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-93 What did you do with the treated
wood or lumber? Did you...");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Handle it, carry it, or move it", "b"=>"", "c"=>"", "d"=>"", "e"=>"",  "f"=>"",  "g"=>"",  "h"=>"");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q8_", "8-94 When you handled the treated wood, was it usually wet or dry?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q8_", "8-95 Did you apply a preservative, such as cresotoe, to the wood yourself?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 8-97");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-96 What preservatives did you use to
treat the wood");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Pentachlorophenol or PCP", "b"=>"b) Inorganic chemicals, such as copper chromium, arsenate, also called CCA or ACA", "c"=>"c) Creosote", "d"=>"d) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-97 How often did you handle treated wood?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Probe: How many hours per day, per week, or per month did you handle
treated wood?");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Pentachlorophenol or PCP", "b"=>"b) Inorganic chemicals, such as copper chromium, arsenate, also called CCA or ACA", "c"=>"c) Creosote", "d"=>"d) Something else");

		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement('static', null, "{$label}:");
			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('textarea', 'other', $this->indent . 'Number:');
			$this->form->addElement('textarea', 'other', $this->indent . 'Units:');
			$this->form->addElement("select", "q8_", "or select from the following:",  array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->form->addElement('static', null, "<br/>");
		}

		$this->form->addElement('static', null, "<b/>When all Modules are complete go to END of INTERVIEW");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>OCCUPATION MODULE: Generic Exposure Module (GE)");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: PHOTOCOPYING/LASER JET PROXIMITY");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q8_", "8-98 Did this job require that you regularly stand at a photocopier for more than
1 hour per day?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q8_", "8-99 Did this job require that you sit within 10 feet of an operating laser jet
printer for more than 1 hour per day?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-100 Between [-3] and DOBS, did you
work with or near any of the
following at this job/school?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Chemicals", "b"=>"b) Work-generated dust", "c"=>"c) Metal fumes (such as from welding or grinding)", "d"=>"d) Bacteria or viruses", "e"=>"e) Animals (dogs, cats, cattle, pigs, ect)",  "f"=>"f) Radiation");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}


		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] for [for 8-100 for all] then go to 8-104");


		$this->form->addElement('static', null, "8-101 Please tell me the name of each chemical/dust/bacteria or
virus/animal/radiation you worked with or near.");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'week', $this->indent . "a) Chemical Name");
		$this->form->addElement("select", "q8_", $this->indent . "",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'week', $this->indent . "b) Dust");
		$this->form->addElement("select", "q8_", $this->indent . "",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'week', $this->indent . "d) Bacteria or Virus Name");
		$this->form->addElement("select", "q8_", $this->indent . "",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'week', $this->indent . "e) Animals Name");
		$this->form->addElement("select", "q8_", $this->indent . "",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'week', $this->indent . "f) Radiation Name");
		$this->form->addElement("select", "q8_", $this->indent . "",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-102 How did you work with that
chemical/dust/virus/animal/radiation? If you did not
personally work with or use it, just say you worked
near it.");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'week', $this->indent . "a) Activity - Chemical Name");
		$this->form->addElement("select", "q8_", $this->indent . "",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'week', $this->indent . "b) Activity - Dust");
		$this->form->addElement("select", "q8_", $this->indent . "",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'week', $this->indent . "c) Activity - Metal Fumes");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'week', $this->indent . "d) Activity - Bacteria or Virus Name");
		$this->form->addElement("select", "q8_", $this->indent . "",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'week', $this->indent . "e) Activity - Animals Name");
		$this->form->addElement("select", "q8_", $this->indent . "",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'week', $this->indent . "f) Activity - Radiation Name");
		$this->form->addElement("select", "q8_", $this->indent . "",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-103 How many hours per week did you work with or near it.
This is actually time, not including time spent on breaks
and lunch, and other work activities where you don't use
or are not near.");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"", "b"=>"", "c"=>"", "d"=>"", "e"=>"",  "f"=>"",  "g"=>"",  "h"=>"");
		$list = array("a"=>"a) Chemicals", "b"=>"b) Work-generated dust", "c"=>"c) Metal fumes (such as from welding or grinding)", "d"=>"d) Bacteria or viruses", "e"=>"e) Animals (dogs, cats, cattle, pigs, ect)",  "f"=>"f) Radiation");

		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01" => "01 Less than 1 hour per week", "02" => "02 1-10 hours per week", "03" => "03  11-20 hours per week", "04" => "04 21-40 hours per week", "05" => "05 More than 40 hours per week", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [8-100 part C] then [go to Soldering and Welding Module]");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: SOLDERING AND WELDING");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-104 Did you do any of the following?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Soldering or brazing", "b"=>"b) Smell fumes from others who solder or
braze", "c"=>"c) Welding or flame cutting", "d"=>"d) Smell fumes from others who weld or flame cut,", "e"=>"e) Some other welding or soldering method?",  "f"=>"f) None of the above");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Some other welding or soldering method?] then please specify:');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [None of the above]  then go to 8-112");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] for [8-104 for all] then go to 8-112");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] for [8-104 part a or b] then [go to 8-105, 8-106, 8-107, 8-108]");

		$this->form->addElement('static', null, $this->indent . "Otherwise, go to 8-111a");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-105 What types of metal did
{you/then/you and those who weld
or flame cut around you} weld or
flame cut?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("h"=>"h) Aluminum", "i"=>"i) Brass or bronz", "j"=>"j) Cast iron", "k"=>"k) Copper", "l"=>"l) Steel",  "m"=>"m) Titanium-based alloy",  "n"=>"n) Other");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [a-d] then [go to 8-107]");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [f-g] then [go to 8-107]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q8_", "8-106 What kind of steel was it?",  array(NULL=>"", "01" => "01 Cadmium plated steel", "02" => "02 Chromium plated steel", "03" => "03  Galvanized iron", "04" => "04 Lead-plated or leaded steel", "05" => "05 Mild, carbon, or construction steel", "06" => "06 Stainless steel", "07" => "07 Another type of steel?", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Another type of steel], please specify:');
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-107 What type of welding or flame cutting did {you/they/you and those who weld
or flame cut around you} do?",  array(NULL=>"", "01" => "01 Oxygas, oxyfuel, or oxyacetylene", "02" => "02 MIG (Metal Inert Gas)", "03" => "03  TIG (Tungsten Inert Gas)", "04" => "04 Stick electrode (shielded metal arc welding)", "05" => "05 Resistance, such as sport, seam, flash, butt, and projection", "06" => "06 Solid state, such as friction or roll", "07" => "07 Plasma arc", "08" => "08 Submerged arc", "09" => "09 Something else", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part a or b for 8-104] then [go to 8-108, 8-109, 8-110, 8-111]");
		$this->form->addElement('static', null, $this->indent . "Otherwise, go to 8-111a");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-108 What did {you/then/you and those
who solder or braze around you}
solder or braze?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Pipes", "b"=>"b) Electrical or electronic parts", "c"=>"c) Other");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Other] then please specify:');
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-109 Did {you/they/you and those who solder or braze around you} use lead-free
solder?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-110 Did the solder usually contain any unusual ingredients such as cadmium,
silver, copper, nickel, zinc, arsenic, beryllium, antimony, indium, or
bismuth?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Yes] then please specify:');


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-111 What did {you/then/you and those
who solder or braze around you}
solder or braze?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Brass", "b"=>"b) Bronze", "c"=>"c) Cast iron", "d"=>"d) Copper", "e"=>"e) Nickel",  "f"=>"f) Other types of iron",  "g"=>"g) Stainless steel",  "h"=>"h) Other steel",  "i"=>"i) Other");

		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Other] then please specify:');


		$this->form->addElement('static', null, "8-111a How often did you use the following metals?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Probe: How many hours per day, per week or per month do you use the
following metals?");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Brass", "b"=>"b) Bronze", "c"=>"c) Cast iron", "d"=>"d) Copper", "e"=>"e) Nickel",  "f"=>"f) Other types of iron",  "g"=>"g) Stainless steel",  "h"=>"h) Other steel",  "i"=>"i) Other");

		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement('static', null, "{$label}:");
			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('textarea', 'other', $this->indent . 'Number:');
			$this->form->addElement('textarea', 'other', $this->indent . 'Units:');
			$this->form->addElement("select", "q8_", "or select from the following:",  array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [any in part A-F 8-100] then [go to Clean Hands Module 8-112]");


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: CLEAN HANDS");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q8_", "8-112 Did you regularly get chemicals or dust on your hands or skin?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] then [end Module and go to 8-115]");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-113 When you had chemicals or dust
on your hands, when did you
wash your hands?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) When taking a break at work", "b"=>"b) Before eating", "c"=>"c) Before smoking", "d"=>"d) At the end of the work shift", "e"=>"e) When the task is completed",  "f"=>"f) Whenever I get my hands dirty",  "g"=>"g) Don't wash hands",  "h"=>"");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Don't wash hands] then [end Module and go to 8-115]");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-114 What did you use to wash
chemicals or dust off your hands?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Soap and water or water only", "b"=>"b) [Goop] or similar cleaners", "c"=>"c) Mineral spirits, turpentine, or paint thinner", "d"=>"d) Gasoline or kerosene", "e"=>"e) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: FUEL AND EXHAUST SMELLS");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-115 Did you regularly smell fuel vapors, such as from gas or fuel tanks, or
exhaust vapors, such as from car or truck tail pipes?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] then [end Module and go to 8-117]");

		$this->form->addElement("select", "q8_", "8-116 How strong was the smell",  array(NULL=>"", "01" => "01 Slight", "02" => "02 Moderate", "03" => "03  Strong", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");





	}


	function _page32(){   // ========================================================

		// To implement Xin Rule

		$this->form->addFormRule(array(&$this,'XINValidate'));





		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: PERSONAL PROTECTIVE EQUIPMENT");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q8_", "8-117 Between [-3] and DOBS, how often did you wear or use personal protective
equipment (PPE) to protect you from the things you have mentioned? By
personal protective equipment, I mean the things like gloves, dust mask,
goggles, aprons, lab coats or other protective clothing, would you say
always, often, rarely, or never us personal protective equipment?",  array(NULL=>"", "01" => "01 Always", "02" => "02 Often", "03" => "03  Rarely", "04" => "04 Never", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Never] then [end Module and go to BOX-GE]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-119 Which type of protective clothing
or equipment did you wear?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "PROBE: Any other protective
clothing or equipment?");

		$list = array("a"=>"a) Gloves", "b"=>"b) Overalls", "c"=>"c) Overcoat (e.g. lab coat, smoke, apron", "d"=>"d) Dust mask", "e"=>"e) Respirator",  "f"=>"f) Goggles or safety glasses",  "g"=>"g) Work boots/shoes",  "h"=>"h) Other");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Other] then please specify:');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part E in 8-119] then [go to 8-120]");
		$this->form->addElement('static', null, $this->indent . "Otherwise [end Module and go to BOX-GE]");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-120 What type of respirator was it?",  array(NULL=>"", "01" => "01 A half-mask chemical cartridge respirator, which is silicone or rubber", "02" => "02 A full-mask chemical cartridge respirator", "03" => "03  An air-supplied or SCBA respirator", "04" => "04 Some other kind of respirator?", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Some other kind of respirator] then please specify:');

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>BOX-GE");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>If [Yes] to any in [part A-F in 8-100] and [Yes] to [any in 01 to 12 in 8-8] or [Yes] to [8-115] then [go to Ventilation and Enclosure Module] starts in 8-121");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: VENTILATION & ENCLOSURES");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q8_", "8-121 Was there any kind of a ventilation system to remove exhaust, dust, smoke
or fumes from the area?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));

		$this->form->addElement('static', null, "Probe: By ventilation system we mean purposely opening windows or doors,
using a fume hood, or other ventilation system.");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] then [End Module and go to 8-123]");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-122 What ventilation systems were
present to remove exhaust, dust,
smoke or fumes from the area? Are there...");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) A general ventilator system, meaning open doors or
windows, use fan, etc.", "b"=>"b) A regular HVAC system for the building and room
heating and cooling", "c"=>"c) A fume hood, lab hood, or other partially enclosed
equipment", "d"=>"d) A glove box or other totally enclosed
equipment", "e"=>"e) A portable exhaust hose or tube, such as those used
for welding or to attach to vehicle tailpipe", "f"=>"f) Some other type of ventilation system");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-123 Between [-3] and DOBS, were any chemical leaks or spills, unusual or
strong odors, dusty conditions or any other non-routine exposure events at
this job/school?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] then [go to 8-13]");


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-124 Please briefly describe the event. What happened?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'week', $this->indent . "Enter description:");
		$this->form->addElement("select", "q8_", $this->indent . "",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		$this->form->addElement('static', null, $this->indent . "If or [Refused] or [Don't Know] then [go to 8-13]");

		$this->form->addElement("select", "q8_", "8-125 Were you hospitalized?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-126 Are you ok now?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>When Generic Exposure Module complete and there are NO more Occupational Modules to Complete
listed in the Occupational Coding Box, then go to 8-13");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>OCCUPATION MODULE: Health Professional (HP)");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box HP-1");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part a in 8-127] then [go to 8-128 and 8-129]");
		$this->form->addElement('static', null, "Otherwise [go to Box HP-2]");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] for [part a-g in 8-127] then [got to Box HP-16]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-128 Between [-3] and DOBS, which
anesthetic gases were used while
you were in the area?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Nitrous oxide", "b"=>"b) Halothane", "c"=>"c) Ether", "d"=>"d) Fluorane", "e"=>"e) Etherane",  "f"=>"f) Chloroform",  "g"=>"g) Some other anesthetic gas");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Some other anesthetic gas] then please specify:');
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q8_", "8-129 How many hours per week did you work in an area where anesthetic gases
are being used? This is actually time, not including time spent on breaks
and lunch, and other work activities where you don't use or are not near.",  array(NULL=>"", "01" => "01 Less than 1 hour per week", "02" => "02 1-10 hours per week", "03" => "03  11-20 hours per week", "04" => "04 21-40 hours per week", "05" => "05 More than 40 hours per week", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box HP-2");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part b in 8-127] then [go to 8-130]");
		$this->form->addElement('static', null, "Otherwise [go to Box HP-4]");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q8_", "8-130 Where instruments or other equipment are sterilized, how were they
sterilized?",  array(NULL=>"", "01" => "01 In an autoclave or sterilizing unit that uses only steam or water", "02" => "02 In an autoclave or sterilizing unit that uses ethylene oxide", "03" => "03  In a liquid solution", "04" => "04 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Other] then please specify:');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box HP-3");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If response to [8-130] is [03] then [go to 8-131]");
		$this->form->addElement('static', null, "Otherwise [go to Box HP-4]");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-131 What chemical sterilizing agent was
typically used in the solution?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Formaldehyde", "b"=>"b) Phisohex", "c"=>"c) Steris", "d"=>"d) Cidex", "e"=>"e) Another sterilizing agent?",  "f"=>"f) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box HP-4");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part c in 8-127] then [go to 8-132]");
		$this->form->addElement('static', null, "Otherwise [go to Box HP-5]");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "8-132 What anti-neoplastic or anti-cancer drugs were used
or mixed most often in the area?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'week', $this->indent . "Enter drug name:");
		$this->form->addElement("select", "q8_", $this->indent . "",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box HP-5");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part d in 8-127] then [go to 8-133]");
		$this->form->addElement('static', null, "Otherwise [go to Box HP-6]");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-133 Between [-3] and DOBS, which
disinfectants or antiseptics have
you used?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Betadine", "b"=>"b) Duraprep", "c"=>"c) Formaldehyde", "d"=>"d) Hibiclens", "e"=>"e) Iodophor or Iodophorm",  "f"=>"f) Lysol",  "g"=>"g) Phisohex or phisoderm",  "h"=>"h) Skin prep or alcohol pads",  "i"=>"i) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box HP-6");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part e in 8-127] then [go to 8-134]");
		$this->form->addElement('static', null, "Otherwise [go to Box HP-8]");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-134 Between [-3] and DOBS which of
the following were used in the
laboratory area in which you
work?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Dyes as either a powder past or liquid", "b"=>"b) Solvents", "c"=>"c) Formaldehyde", "d"=>"d) Hibiclens", "e"=>"e) Iodophor or Iodophorm",  "f"=>"f) None");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('static', null, "<b/>Box HP-7");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part b in 8-134] then [go to 8-134a]");
		$this->form->addElement('static', null, "Otherwise [go to Box HP-8]");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-134a What solvents were used in your
laboratory work area?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Acetone", "b"=>"b) Chloroform", "c"=>"c) Ethanol", "d"=>"d) Propanol", "e"=>"e) Toluene",  "f"=>"f) Xylene",  "g"=>"g) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box HP-8");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part g in 8-127] then [go to 8-135]");
		$this->form->addElement('static', null, "Otherwise [go to Box HP-11]");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-135 What types of animals were typically
treated in your work area?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Dogs", "b"=>"b) Cats", "c"=>"c) Reptiles (turtles, lizards, snakes)", "d"=>"d) Large animals (horses. Cattle, pigs, ect)", "e"=>"e) Some other animals");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Some other animals] then please specify:');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box HP-9");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part b in 8-135] then [go to 8-136]");
		$this->form->addElement('static', null, "Otherwise [go to Box HP-10]");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-136 To your knowledge, were you ever infected with the parasite that causes
toxoplasmosis?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box HP-10");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part b in 8-135] then [go to 8-136]");
		$this->form->addElement('static', null, "Otherwise [go to Box HP-10]");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-137 To you knowledge, were you ever infected with salmonella from a reptile?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box HP-11");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part b in 8-135] then [go to 8-136]");
		$this->form->addElement('static', null, "Otherwise [go to Box HP-10]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-138 Between [-3] and DOBS did you
work near any of the following?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) X-ray equipment", "b"=>"b) Aniography equipment", "c"=>"c) CAT scanning equipment", "d"=>"d) MRI equipment", "e"=>"e) Radioisotopes or radionuclides",  "f"=>"f) Thoroscopy equipment",  "g"=>"g) None of the these");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box HP-12");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part b in 8-135] then [go to 8-136]");
		$this->form->addElement('static', null, "Otherwise [go to Box HP-10]");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-139 Which of the following did you do
in a room when working around
this equipment or radioisotopes?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Wear a dosimeter or film badge that measures your
radiation", "b"=>"b) Wear a leaded apron", "c"=>"c) Stand behind a leaded barrier or outside the room while
the x-ray is taken", "d"=>"d) Something else", "e"=>"e) No action taken");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');


		$this->form->addElement("select", "q8_", "8-140 Between [-3] and DOBS did you handled blood or tissues or materials
contaminated with blood?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box HP-13");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "[go to Clean Hands Module] starts on 8-141");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: CLEAN HANDS");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q8_", "8-141 Did you regularly get chemicals or dust on your hands or skin?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] then [end Module and go to 8-144]");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-142 When you had chemicals or dust
on your hands, when did you
wash your hands?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) When taking a break at work", "b"=>"b) Before eating", "c"=>"c) Before smoking", "d"=>"d) At the end of the work shift", "e"=>"e) When the task is completed",  "f"=>"f) Whenever I get my hands dirty",  "g"=>"g) Don't wash hands");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('static', null, $this->indent . "If [Don't wash hands] then [end Module and go to 8-144]");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-143 What did you use to wash
chemicals or dust off your hands?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Soap and water or water only", "b"=>"b) [Goop] or similar cleaners", "c"=>"c) Mineral spirits, turpentine, or paint thinner", "d"=>"d) Gasoline or kerosene", "e"=>"e) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: PERSONAL PROTECTIVE EQUIPMENT");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-144 Between [-3] and DOBS, how often did you wear or use personal protective
equipment (PPE) to protect you from the things you have mentioned? By
personal protective equipment, I mean the things like gloves, dust mask,
goggles, aprons, lab coats or other protective clothing, would you say
always, often, rarely, or never us personal protective equipment?",  array(NULL=>"", "01" => "01 Always", "02" => "02 Often", "03" => "03  Rarely", "04" => "04 Never", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, $this->indent . "If [Never] then [end Module and go to 8-148]");
		$this->form->addElement('static', null, $this->indent . "If [Refused] then [end Module and go to 8-148]");
		$this->form->addElement('static', null, $this->indent . "If [Don't Know] then [end Module and go to 8-148]");

		$this->form->addElement('static', null, "8-146 Which type of protective clothing or
equipment did you wear?");
		$this->form->addElement('static', null, "Code all that apply.");

		$this->form->addElement('static', null, "PROBE: Any other protective clothing or
equipment?");
		$this->form->addElement('static', null, "<br/>");

		$aToH = array("a) Gloves"=>"a) Gloves", "b) Overalls"=>"b) Overalls", "c) Overcoat (e.g. lab coat, smoke, apron)"=>"c) Overcoat (e.g. lab coat, smoke, apron)",  "d) Dust mask"=>"d) Dust mask", "e) Respirator"=>"e) Respirator", "f) Goggles or safety glasses"=>"f) Goggles or safety glasses",  "g) Work boots/shoes"=>"g) Work boots/shoes",  "h) Other"=>"h) Other");
		reset($aToH);

		while(list($field, $label) = each($aToH)){

			$this->form->addElement('static', null, "<br/>");

			$this->form->addElement("select", "q8_", "{$label}:",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));

		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Other], Please specify:');


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Box PPE");
		$this->form->addElement('static', null, $this->indent . "If [Yes] for [part d in 8-146] then [go to 8-147]");
		$this->form->addElement('static', null, "Otherwise [end Module and go to 8-148]");


		$this->form->addElement("select", "q7_", "8-147 What type of respirator was it?",  array(NULL=>"", "01" => "01 A half-mask chemical cartridge respirator, which is silicone or rubber and
covers your mouth and nose", "02" => "02 A full-mask chemical cartridge respirator, which is rubber and covers your eyes, nose, and mouth", "03" => "03  An air-supplied or SCBA respirator", "04" => "04 Some other kind of respirator?", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('textarea', 'other', $this->indent . 'If [Some other kind of respirator], please specify:');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: VENTILATION & ENCLOSURES");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q7_", "8-148 Was there any kind of a ventilation system to remove exhaust, dust, smoke
or fumes from the area?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Probe: By ventilation system we mean purposely opening windows or doors,
using a fume hood, or other ventilation system.");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] then [end Module and go to 8-150]");
		$this->form->addElement('static', null, $this->indent . "If [Refused] [end Module and go to 8-150]");
		$this->form->addElement('static', null, $this->indent . "If [Don't Know] [end Module and go to 8-150]");


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-149 What ventilation systems are
present to remove exhaust, dust,
smoke or fumes from the area? Is
there...");

		$this->form->addElement('static', null, "Code all that apply.");
		$this->form->addElement('static', null, "<br/>");

		$aToF = array("a) A general ventilator system, meaning open doors or
windows, use fan, ect."=>"a) A general ventilator system, meaning open doors or
windows, use fan, ect.", "b) A regular HVAC system for the building and room
heating and cooling"=>"b) A regular HVAC system for the building and room
heating and cooling", "c) A fume hood, lab hood, or other partially enclosed
equipment"=>"c) A fume hood, lab hood, or other partially enclosed
equipment", "d) A glove box or other totally enclosed
equipment"=>"d) A glove box or other totally enclosed
equipment", "e) A portable exhaust hose or tube, such as those used
for welding or to attach to vehicle tailpipe"=>"e) A portable exhaust hose or tube, such as those used
for welding or to attach to vehicle tailpipe",  "f) Some other type of ventilation system"=>"f) Some other type of ventilation system");
		reset($aToF);

		while(list($field, $label) = each($aToF)){

			$this->form->addElement('static', null, "<br/>");

			$this->form->addElement("select", "q8_", "{$label}:",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));

		}
		$this->form->addElement('textarea', 'other', $this->indent . 'Please specify:');







	}


	function _page33(){   // ========================================================

		// To implement Xin Rule

		$this->form->addFormRule(array(&$this,'XINValidate'));






		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: PHOTOCOPYING/LASER JET PROXIMITY");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q8_", "8-150 Did this job require that you regularly stand at a photocopier for more than
1 hour per day?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-151 Did this job require that you sit within 10 feet of an operating laser jet
printer for more than 1 hour per day?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "When occupational module complete, and there are NO more Occupational Modules to Complete listed in
the Occupational Coding Box then go to 8-13");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>OCCUPATION MODULE: Teacher (TE)");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-152 Which of the following subjects
did you teach?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Art", "b"=>"b) Shop, woodworking, or industrial arts", "c"=>"c) Biology", "d"=>"d) Chemistry", "e"=>"e) None of these");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Shop, woodworking, or industrial arts] then please specify:');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [None of these]  then [end Module and go to 8-194]");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Refused], [Don't Know] and/or [No] to all then [end Module and go to 8-194]");


		$this->form->addElement("select", "q8_", "8-153 Between [-3] and DOBS did you use chemicals or generated dusts or metal
fumes in your class? Examples include paint, glue, acids, and solder or
welding materials.",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If [No] then [end Module and go to 8-194]");
		$this->form->addElement('static', null, $this->indent . "If [Refused] [end Module and go to 8-194]");
		$this->form->addElement('static', null, $this->indent . "If [Don't Know] [end Module and go to 8-194]");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>BOX TE-1");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part a or b in 8-152] and [Yes] in [8-153] then [go to 8-154]");
		$this->form->addElement('static', null, "Otherwise [go to Box TE-2]");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-154 Between [-3] and DOBS, what
chemicals did you use in your
classes?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Acetone", "b"=>"b) Acids", "c"=>"c) Glue", "d"=>"d) Paint or paint related chemicals (varnish, paint, thinner,
turpentine, etc.)", "e"=>"e) Gasoline, oil, or hydraulic fluids",  "f"=>"f) Soldering or welding",  "g"=>"g) None",  "h"=>"h) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>BOX TE-2");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part c or d in 8-152] then [go to 8-155]");
		$this->form->addElement('static', null, "Otherwise [go to Ventilation and Enclosures Module ] starts on 8-164");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-155 Between [-3] and DOBS, what
chemicals or agents did you use
in your classes?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Acetone", "b"=>"b) Acids", "c"=>"c) Alcohols", "d"=>"d) Caustics", "e"=>"e) Chloroform",  "f"=>"f) Ester",  "g"=>"g) Ethers",  "h"=>"h) Ketones",  "i"=>"i) Mold or other microbials",  "j"=>"j) Toluene or xylene",  "k"=>"k) None",  "l"=>"l) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [] then ");
		$this->form->addElement('static', null, "8-156 How often did you use the following chemicals in your classroom:");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Probe: How many hours per day, per week or per month do you use the
following chemicals in your classroom?");
		$this->form->addElement('static', null, "<br/>");

		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement('static', null, "{$label}:");
			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('textarea', 'other', $this->indent . 'Number:');
			$this->form->addElement('textarea', 'other', $this->indent . 'Units:');
			$this->form->addElement("select", "q8_", "or select from the following:",  array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: CLEAN HANDS");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-157 Did you regularly get chemicals or dust on your hands or skin?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] then [End Module and go to 8-160]");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-158 When you had chemicals or dust
on your hands, when did you
wash your hands?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");



		$list = array("a"=>"a) When taking a break at work", "b"=>"b) Before eating", "c"=>"c) Before smoking", "d"=>"d) At the end of the work shift", "e"=>"e) When the task is completed",  "f"=>"f) Whenever I get my hands dirty",  "g"=>"g) Don't wash hands");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('static', null, $this->indent . "If [Don't wash hands] then [end Module and go to 8-160]");

		$this->form->addElement('static', null, "8-159 What did you use to wash
chemicals or dust off your hands?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Soap and water or water only", "b"=>"b) [Goop] or similar cleaners", "c"=>"c) Mineral spirits, turpentine, or paint thinner", "d"=>"d) Gasoline or kerosene", "e"=>"e) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: PERSONAL PROTECTIVE EQUIPMENT");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q8_", "8-160 Between [-3] and DOBS, how often did you wear or use personal protective
equipment (PPE) to protect you from the things you have mentioned? By
personal protective equipment, I mean the things like gloves, dust mask,
goggles, aprons, lab coats or other protective clothing, would you say
always, often, rarely, or never us personal protective equipment?",  array(NULL=>"", "01" => "01 Always", "02" => "02 Often", "03" => "03  Rarely", "04" => "04 Never", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, $this->indent . "If [Never] then [end Module and go to 8-164]");
		$this->form->addElement('static', null, $this->indent . "If [Refused] then [end Module and go to 8-164]");
		$this->form->addElement('static', null, $this->indent . "If [Don't Know] then [end Module and go to 8-164]");

		$this->form->addElement('static', null, "8-162 Which type of protective clothing or
equipment did you wear?");
		$this->form->addElement('static', null, "Code all that apply.");

		$this->form->addElement('static', null, "PROBE: Any other protective clothing or
equipment?");
		$this->form->addElement('static', null, "<br/>");

		$aToH = array("a) Gloves"=>"a) Gloves", "b) Overalls"=>"b) Overalls", "c) Overcoat (e.g. lab coat, smoke, apron)"=>"c) Overcoat (e.g. lab coat, smoke, apron)",  "d) Dust mask"=>"d) Dust mask", "e) Respirator"=>"e) Respirator", "f) Goggles or safety glasses"=>"f) Goggles or safety glasses",  "g) Work boots/shoes"=>"g) Work boots/shoes",  "h) Other"=>"h) Other");
		reset($aToH);

		while(list($field, $label) = each($aToH)){

			$this->form->addElement('static', null, "<br/>");

			$this->form->addElement("select", "q8_", "{$label}:",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));

		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Other], Please specify:');


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Box PPE");
		$this->form->addElement('static', null, $this->indent . "If [Yes] for [part e in 8-162] then [go to 8-163]");
		$this->form->addElement('static', null, "Otherwise [go to Ventilation and Enclosures Module ] starts on 8-164");


		$this->form->addElement("select", "q7_", "8-163 What type of respirator was it?",  array(NULL=>"", "01" => "01 A half-mask chemical cartridge respirator, which is silicone or rubber and
covers your mouth and nose", "02" => "02 A full-mask chemical cartridge respirator, which is rubber and covers your eyes, nose, and mouth", "03" => "03  An air-supplied or SCBA respirator", "04" => "04 Some other kind of respirator?", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('textarea', 'other', $this->indent . 'If [Some other kind of respirator], please specify:');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: VENTILATION & ENCLOSURES");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q7_", "8-164 Was there any kind of a ventilation system to remove exhaust, dust, smoke
or fumes from the area?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Probe: By ventilation system we mean purposely opening windows or doors,
using a fume hood, or other ventilation system.");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] then [end Module and go to Box TE-3]");
		$this->form->addElement('static', null, $this->indent . "If [Refused] [end Module and go to Box TE-3]");
		$this->form->addElement('static', null, $this->indent . "If [Don't Know] [end Module and go to Box TE-3]");


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-165 What ventilation systems are
present to remove exhaust, dust,
smoke or fumes from the area? Is
there...");

		$this->form->addElement('static', null, "Code all that apply.");
		$this->form->addElement('static', null, "<br/>");

		$aToF = array("a) A general ventilator system, meaning open doors or
windows, use fan, ect."=>"a) A general ventilator system, meaning open doors or
windows, use fan, ect.", "b) A regular HVAC system for the building and room
heating and cooling"=>"b) A regular HVAC system for the building and room
heating and cooling", "c) A fume hood, lab hood, or other partially enclosed
equipment"=>"c) A fume hood, lab hood, or other partially enclosed
equipment", "d) A glove box or other totally enclosed
equipment"=>"d) A glove box or other totally enclosed
equipment", "e) A portable exhaust hose or tube, such as those used
for welding or to attach to vehicle tailpipe"=>"e) A portable exhaust hose or tube, such as those used
for welding or to attach to vehicle tailpipe",  "f) Some other type of ventilation system"=>"f) Some other type of ventilation system");
		reset($aToF);

		while(list($field, $label) = each($aToF)){

			$this->form->addElement('static', null, "<br/>");

			$this->form->addElement("select", "q8_", "{$label}:",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));

		}
		$this->form->addElement('textarea', 'other', $this->indent . 'Please specify:');


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>BOX TE-3");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part b in 8-152] then [go to Fuel and Exhaust Module] starts on 8-165a]");
		$this->form->addElement('static', null, "Otherwise [go to Ventilation and Enclosures Module ] starts on 8-164");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: FUEL AND EXHAUST SMELLS");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-165a Did you regularly smell fuel vapors, such as from gas or fuel tanks, or
exhaust vapors, such as from car or truck tail pipes?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] then [End Module and go to Box TE-4]");

		$this->form->addElement("select", "q8_", "8-165b How strong was the smell",  array(NULL=>"", "01" => "01 Slight", "02" => "02 Moderate", "03" => "03  Strong", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");



		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>BOX TE-4");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part b in 8-152] then [go to Lubrication Engines Module] starts on 8-166]");
		$this->form->addElement('static', null, "Otherwise [go to Box TE-5]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: LUBRICATING ENGINES & MACHINERY");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-166 Did you routinely use lubricating oils, or waxes on engines or machinery?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If [No] then [end Module and go to Box TE-5]");
		$this->form->addElement('static', null, $this->indent . "If [Refused] [end Module and go to Box TE-5]");
		$this->form->addElement('static', null, $this->indent . "If [Don't Know] [end Module and go to Box TE-5]");

		$this->form->addElement('static', null, "8-167 What types of lubricants did you work with?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'week', $this->indent . "Enter lubricant");
		$this->form->addElement("select", "q8_", $this->indent . "",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-168 What types of cutting oils did you
work with?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Straight cutting oils or oils that look and feel like motor
oil", "b"=>"b) Soluble cutting oils or oils that are milky white", "c"=>"c) Synthetic cutting oils or oils that feel like water or may
be brightly colored, such as green or blue", "d"=>"d) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "8-169 How often did you use the following lubricants?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Probe: How many hours per day, per week or per month did you use the
following lubricants?");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Straight cutting oils or oils that look and feel like motor oil", "b"=>"b) Soluble cutting oils or oils that are milky white", "c"=>"c) Synthetic cutting oils or oils that feel like water or may be brightly colored, such as green or blue", "d"=>"d) Something else");

		reset($list);
		while(list($field, $label) = each($list)){

			$this->form->addElement('static', null, "{$label}:");
			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('textarea', 'other', $this->indent . 'Number:');
			$this->form->addElement('textarea', 'other', $this->indent . 'Units:');
			$this->form->addElement("select", "q8_", "or select from the following:",  array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>BOX TE-5");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part c in 8-154] then [go to Glue Module] starts on 8-170");
		$this->form->addElement('static', null, "Otherwise [go to Box TE-6]");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: GLUING");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-170 Did you routinely use glues or adhesives?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] then [end Module and go to Box TE-6]");
		$this->form->addElement('static', null, $this->indent . "If [Refused] then [end Module and go to Box TE-6]");
		$this->form->addElement('static', null, $this->indent . "If [Don't Know] then [end Module and go to Box TE-6]");


		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "8-171 Which glues did you use?");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Code all that apply:");

		$this->form->addElement('static', null, "<br/>");

		$list = array("a) Hot melt glues or adhesives"=>"a) Hot melt glues or adhesives", "b) Contact adhesives, such as rubber cement"=>"b) Contact adhesives, such as rubber cement", "c) Water-based adhesives, such as vinyl or acrylic resins"=>"c) Water-based adhesives, such as vinyl or acrylic resins", "d) Wood laminates"=>"d) Wood laminates", "e) Something else"=>"e) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [e) Something else] then please specify:');

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-172 How strong was the smell of {hot melt glues/contact adhesives/water-based
adhesives/wood laminates}?");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Code for each yes response in 8-171");

		$this->form->addElement('static', null, "<br/>");

		$list = array("a) Hot melt glues or adhesives"=>"a) Hot melt glues or adhesives", "b) Contact adhesives, such as rubber cement"=>"b) Contact adhesives, such as rubber cement", "c) Water-based adhesives, such as vinyl or acrylic resins"=>"c) Water-based adhesives, such as vinyl or acrylic resins", "d) Wood laminates"=>"d) Wood laminates", "e) Something else"=>"e) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}", array(NULL=>"", "01" => "01 Slight", "02" => "02 Moderate", "03" => "03  Strong", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->form->addElement('static', null, "<br/>");
		}

		$this->form->addElement("select", "q8_", "8-173 Did you wipe off the excess glue or adhesive with a solvent?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If [No] then [go to 8-175]");
		$this->form->addElement('static', null, $this->indent . "If [Refused] then [go to 8-175]");
		$this->form->addElement('static', null, $this->indent . "If [Don't Know] then [go to 8-175]");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-174 What solvent did you typically
wipe it off with?");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Code all that apply:");

		$this->form->addElement('static', null, "<br/>");

		$list = array("a) Acetone"=>"a) Acetone", "b) Paint thinner"=>"b) Paint thinner", "c) Citrus-based chemicals"=>"c) Citrus-based chemicals", "d) Something else"=>"d) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [d) Something else] then please specify:');

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-175 How often did you use the following glues or adhesives?");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Probe: How many hours per day, per week or per month do you use the
following glues or adhesives?");
		$this->form->addElement('static', null, "<br/>");

		$list = array("a) Hot melt glues or adhesives"=>"a) Hot melt glues or adhesives", "b) Contact adhesives, such as rubber cement"=>"b) Contact adhesives, such as rubber cement", "c) Water-based adhesives, such as vinyl or acrylic resins"=>"c) Water-based adhesives, such as vinyl or acrylic resins", "d) Wood laminates"=>"d) Wood laminates", "e) Something else"=>"e) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement('static', null, "{$label}:");
			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('textarea', 'other', $this->indent . 'Number:');
			$this->form->addElement('textarea', 'other', $this->indent . 'Units:');
			$this->form->addElement("select", "q8_", "or select from the following:",  array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->form->addElement('static', null, "<br/>");
		}



		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>BOX TE-6");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part c in 8-154] then [go to Paint Module] starts on 8-176");
		$this->form->addElement('static', null, "Otherwise [go to Box TE-7]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>The next few questions ask about painting, varnishing, and staining.");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: PAINTING, PAINT REMOVAL, PAINT CLEANING");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-176 Did you typically do any of the
following activities?");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Code all that apply:");

		$this->form->addElement('static', null, "<br/>");

		$list = array("a"=>"a) Painting, varnishing, or staining", "b"=>"b) Paint removal", "c"=>"c) Paint thinning and cleaning", "d"=>"d) Something else", "e"=>"e) None of the above");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then [End Module
and go to Box TE-7]');
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If [None of the above] then [End Module and
go to Box TE-7]");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No], [Refused] and/or [Don't Know] for [part a-e] then [End Module and go to
Box TE-7]");
		$this->form->addElement('static', null, "<br/>");



	}


	function _page34(){   // ========================================================

		// To implement Xin Rule

		$this->form->addFormRule(array(&$this,'XINValidate'));





		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>BOX PT-1");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part a in 8-176] then [go to 8-177, 8-178,
8-179]");
		$this->form->addElement('static', null, "Otherwise [go to Box PT-2]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-177 What kind of paint did you use?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Laytex or water-based paint", "b"=>"b) Acrylic", "c"=>"c) Oil-based paint (enamel)", "d"=>"d) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-178 Did you usually brush, roll, or
spray paint?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Brush", "b"=>"b) Roll", "c"=>"c) Spray", "d"=>"d) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [8-64 part b] then [go to 8-68]");


		$this->form->addElement("select", "q8_", "8-179 Did you use primers with lead, chromate, or zinc?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>BOX PT-2");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part b in 8-176] then [go to 8-180]");
		$this->form->addElement('static', null, "Otherwise [go to Box PT-3]");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-180 How did you typically remove
paint?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Heat gun", "b"=>"b) Scraper or wire stripper with a drill bit
attachment", "c"=>"c) Chemical paint stripper", "d"=>"d) Some other paint removal method");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Some other paint removal method] then please specify:');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [8-64 part c] then [go to 8-69]");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>BOX PT-3");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part c in 8-176] then [go to 8-181]");
		$this->form->addElement('static', null, "Otherwise [go to 8-183]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-181 What did you typically use to thin
or clean paint, varnish or stain");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Paint thinner, mineral spirits, or turpertin", "b"=>"b) Lacquer thinner", "c"=>"c) Alcohol", "d"=>"d) Water", "e"=>"e) Citrus-based products",  "f"=>"f) Gasoline or kerosene",  "g"=>"g) Other");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [8-68 part c] then [go to 8-70]");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-182 What chemicals did you use to
strip paint?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Lacquer or paint thinner", "b"=>"b) Lye (Sodium hydroxide)", "c"=>"c) Ammonia (Ammonia Hydroxide)", "d"=>"d) Other");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Other] then please specify:');
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>BOX PT-4");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part c in 8-180] then [go to 8-183]");
		$this->form->addElement('static', null, "Otherwise [go to 8-184]");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "8-183 How often did you use the following paint, paint thinners, or paint
strippers?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Probe: How many hours per day, per week or per month did you use the
following paint, paint thinners, or paint strippers?");
		$this->form->addElement('static', null, "<br/>");

		$list = array("a"=>"a) Laytex or water-based paint", "b"=>"b) Acrylic", "c"=>"c) Oil-based paint (enamel)","d"=>"d) Paint thinner, mineral spirits, or turpertin", "e"=>"e) Lacquer thinner", "f"=>"f) Alcohol", "g"=>"g) Water", "h"=>"h) Citrus-based products",  "i"=>"i) Gasoline or kerosene", "j"=>"j) Lacquer or paint thinner", "k"=>"k) Lye (Sodium hydroxide)", "l"=>"l) Ammonia (Ammonia Hydroxide)", "m"=>"m) Other" );

		reset($list);
		while(list($field, $label) = each($list)){

			$this->form->addElement('static', null, "{$label}:");
			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('textarea', 'other', $this->indent . 'Number:');
			$this->form->addElement('textarea', 'other', $this->indent . 'Units:');
			$this->form->addElement("select", "q8_", "or select from the following:",  array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->form->addElement('static', null, "<br/>");
		}

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>BOX TE-7");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part f in 8-154] then [go to Soldering or Welding Module] starts on 8-184");
		$this->form->addElement('static', null, "Otherwise [go to Box TE-8]");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: SOLDERING AND WELDING");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-184 Did you do any of the following?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Soldering or brazing", "b"=>"b) Smell fumes from others who solder or
braze", "c"=>"c) Welding or flame cutting", "d"=>"d) Smell fumes from others who weld or flame cut,", "e"=>"e) Some other welding or soldering method?",  "f"=>"f) None of the above");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Some other welding or soldering method?] then please specify:');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [None of the above] then [End Module and go to
Box TE-8]");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No], [Refused] and/or [Don't Know] for [part a-e] then [End Module and go to
Box TE-8]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>BOX SW-1");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part a in 8-184] then [go to 8-188, 8-189, 8-190, 8-191]");
		$this->form->addElement('static', null, $this->indent . "Otherwise, go to 8-191a");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-185 What types of metal did
{you/then/you and those who weld
or flame cut around you} weld or
flame cut?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("h"=>"h) Aluminum", "i"=>"i) Brass or bronz", "j"=>"j) Cast iron", "k"=>"k) Copper", "l"=>"l) Steel",  "m"=>"m) Titanium-based alloy",  "n"=>"n) Other");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Other] then please specify:');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [any a-g] then [go to 8-187]");
		$this->form->addElement('static', null, $this->indent . "If [No], [Refused], [Don't Know] to all then [go to 8-187]");


		$this->form->addElement("select", "q8_", "8-186 What kind of steel was it?",  array(NULL=>"", "01" => "01 Cadmium plated steel", "02" => "02 Chromium plated steel", "03" => "03  Galvanized iron", "04" => "04 Lead-plated or leaded steel", "05" => "05 Mild, carbon, or construction steel", "06" => "06 Stainless steel", "07" => "07 Another type of steel?", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Another type of steel], please specify:');
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-187 What type of welding or flame cutting did {you/they/you and those who weld
or flame cut around you} do?",  array(NULL=>"", "01" => "01 Oxygas, oxyfuel, or oxyacetylene", "02" => "02 MIG (Metal Inert Gas)", "03" => "03  TIG (Tungsten Inert Gas)", "04" => "04 Stick electrode (shielded metal arc welding)", "05" => "05 Resistance, such as sport, seam, flash, butt, and projection", "06" => "06 Solid state, such as friction or roll", "07" => "07 Plasma arc", "08" => "08 Submerged arc", "09" => "09 Something else", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>BOX SW-1");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part a or b in 8-184] then [go to 8-188, 8-189, 8-190, 8-191]");
		$this->form->addElement('static', null, $this->indent . "Otherwise, go to 8-191a");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-188 What did {you/then/you and those
who solder or braze around you}
solder or braze?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Pipes", "b"=>"b) Electrical or electronic parts", "c"=>"c) Other");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Other] then please specify:');
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-189 Did {you/they/you and those who solder or braze around you} use lead-free
solder?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-190 Did the solder usually contain any unusual ingredients such as cadmium,
silver, copper, nickel, zinc, arsenic, beryllium, antimony, indium, or
bismuth?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Yes] then please specify:');


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-191 What did {you/then/you and those
who solder or braze around you}
solder or braze?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Brass", "b"=>"b) Bronze", "c"=>"c) Cast iron", "d"=>"d) Copper", "e"=>"e) Nickel",  "f"=>"f) Other types of iron",  "g"=>"g) Stainless steel",  "h"=>"h) Other steel",  "i"=>"i) Other");

		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Other] then please specify:');


		$this->form->addElement('static', null, "8-191a How often did you use the following metals?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Probe: How many hours per day, per week or per month do you use the
following metals?");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Brass", "b"=>"b) Bronze", "c"=>"c) Cast iron", "d"=>"d) Copper", "e"=>"e) Nickel",  "f"=>"f) Other types of iron",  "g"=>"g) Stainless steel",  "h"=>"h) Other steel",  "i"=>"i) Other");

		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement('static', null, "{$label}:");
			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('textarea', 'other', $this->indent . 'Number:');
			$this->form->addElement('textarea', 'other', $this->indent . 'Units:');
			$this->form->addElement("select", "q8_", "or select from the following:",  array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->form->addElement('static', null, "<br/>");
		}

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>BOX TE-8");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part a in 8-154] then [go to Art Supply Module AND Photocopying/Laser Jet Proximity Module]
starts on 8-192");

		$this->form->addElement('static', null, "<br/>");



		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: USING ART SUPPLIES");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "8-192 Which art supplies did you
typically use? Or use at least once
a week?");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Code all that apply:");

		$this->form->addElement('static', null, "<br/>");

		$aToF = array("a) Markers"=>"a) Markers", "b) Paints"=>"b) Paints", "c) Inks"=>"c) Inks", "d) Glazes"=>"d) Glazes", "e) Something else"=>"e) Something else",  "f) No art supplies containing chemicals"=>"f) No art supplies containing chemicals");
		reset($aToF);
		while(list($field, $label) = each($aToF)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Yes] to [e) Something else] then please specify:');


		$this->form->addElement('static', null, "8-193 How often did you use the following art supplies?");
		$this->form->addElement('static', null, "Probe: How many hours per day, per week or per month did you use the
following art supplies?");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Enter number and choose units or select from the list");

		$this->form->addElement('static', null, "<br/>");

		$aToF = array("a) Markers"=>"a) Markers", "b) Paints"=>"b) Paints", "c) Inks"=>"c) Inks", "d) Glazes"=>"d) Glazes", "e) Something else"=>"e) Something else",  "f) No art supplies containing chemicals"=>"f) No art supplies containing chemicals");
		reset($aToF);
		while(list($field, $label) = each($aToF)){
			$this->form->addElement('static', null, "{$label}:");
			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('textarea', 'other', $this->indent . 'Number:');
			$this->form->addElement('textarea', 'other', $this->indent . 'Units:');
			$this->form->addElement("select", "q8_", "or select from the following:",  array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Yes] to [e) Something else] then please specify:');


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: PHOTOCOPYING/LASER JET PROXIMITY");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q8_", "8-194 Did this job require that you regularly stand at a photocopier for more than
1 hour per day?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-195 Did this job require that you sit within 10 feet of an operating laser jet
printer for more than 1 hour per day?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "When occupational module complete, and there are NO more Occupational Modules to Complete listed in
the Occupational Coding Box then go to 8-13");	
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>When occupational module complete, and there are NO more Occupational Modules to Complete listed in
the Occupational Coding Box then [go to 8-13]");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>OCCUPATION MODULE: Restaurant Worker (RW)");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-196 Did you typically do any of the
following?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Clean counters, floors, and equipment", "b"=>"b) Wash dishes", "c"=>"c) Wait on tables", "d"=>"d) See smoke from the grills, fryers, or deep fryers", "e"=>"e) Cut or chop raw meat");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('static', null, $this->indent . "If [No], [Refused], and/or [Don't Know] to [part a-e] then [End Module and go to 8-13]");
			$this->form->addElement('static', null, $this->indent . "If [Yes] to [part d] then [go to 8-197]");
			$this->form->addElement('static', null, "Otherwise [go to 8-198]");


		}

		$this->form->addElement("select", "q8_", "8-197 Typically, how smoky was the smoke from the grills or deep fryers?",  array(NULL=>"", "01" => "01 Not every smoky", "02" => "02 Slightly smoky", "03" => "03  Moderately smoky", "04" => "04 Very smoky", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-198 Between [-3] and DOBS, did you ever...");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Cuts on the hands", "b"=>"b) Blood on your hands");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");

		}


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: HOUSEHOLD CLEANER USE");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q8_", "8-199 Did you typically use household cleaning products",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, $this->indent . "If [No] then [end Module and go to Clean Hands Module 8-202]");
		$this->form->addElement('static', null, $this->indent . "If [Refused] [end Module and go to Clean Hands Module 8-202]");
		$this->form->addElement('static', null, $this->indent . "If [Don't Know] [end Module and go to Clean Hands Module 8-202]");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-200 Which types of cleaning products
did you typically use at work?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Ammonia products", "b"=>"b) Chlorine bleach", "c"=>"c) Floor cleaner", "d"=>"d) Floor polish", "e"=>"e) Floor stripper",  "f"=>"f) Furniture or wood polish",  "g"=>"g) Metal polish",  "h"=>"h) Oven cleaner",  "i"=>"i) Paint stripper",  "j"=>"j) Spot and stain remover or carpet cleaner",  "k"=>"k) Turpertine or mineral spirits",  "l"=>"l) Window or mirror cleaner",  "m"=>"m) Other");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Other] then please specify:');
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "8-201 How often did you use the following cleaning products?");
		$this->form->addElement('static', null, "Probe: How many hours per day, per week or per month did you use the
following art supplies?");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Enter number and choose units or select from the list");

		$this->form->addElement('static', null, "<br/>");
		$aToF = array("a"=>"a) Ammonia products", "b"=>"b) Chlorine bleach", "c"=>"c) Floor cleaner", "d"=>"d) Floor polish", "e"=>"e) Floor stripper",  "f"=>"f) Furniture or wood polish",  "g"=>"g) Metal polish",  "h"=>"h) Oven cleaner",  "i"=>"i) Paint stripper",  "j"=>"j) Spot and stain remover or carpet cleaner",  "k"=>"k) Turpertine or mineral spirits",  "l"=>"l) Window or mirror cleaner",  "m"=>"m) Other");

		reset($aToF);
		while(list($field, $label) = each($aToF)){
			$this->form->addElement('static', null, "{$label}:");
			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('textarea', 'other', $this->indent . 'Number:');
			$this->form->addElement('textarea', 'other', $this->indent . 'Units:');
			$this->form->addElement("select", "q8_", "or select from the following:",  array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: CLEAN HANDS");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-202 Did you regularly get chemicals or dust on your hands or skin?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] then [End Module and go to 8-205]");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-158 When you had chemicals or dust
on your hands, when did you
wash your hands?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");



		$list = array("a"=>"a) When taking a break at work", "b"=>"b) Before eating", "c"=>"c) Before smoking", "d"=>"d) At the end of the work shift", "e"=>"e) When the task is completed",  "f"=>"f) Whenever I get my hands dirty",  "g"=>"g) Don't wash hands");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('static', null, $this->indent . "If [Don't wash hands] then [end Module and go to to PPE Module 8-205]");

		$this->form->addElement('static', null, "8-204 What did you use to wash
chemicals or dust off your hands?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Soap and water or water only", "b"=>"b) [Goop] or similar cleaners", "c"=>"c) Mineral spirits, turpentine, or paint thinner", "d"=>"d) Gasoline or kerosene", "e"=>"e) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: PERSONAL PROTECTIVE EQUIPMENT");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q8_", "8-205 Between [-3] and DOBS, how often did you wear or use personal protective
equipment (PPE) to protect you from the things you have mentioned? By
personal protective equipment, I mean the things like gloves, dust mask,
goggles, aprons, lab coats or other protective clothing, would you say
always, often, rarely, or never us personal protective equipment?",  array(NULL=>"", "01" => "01 Always", "02" => "02 Often", "03" => "03  Rarely", "04" => "04 Never", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, $this->indent . "If [Never] then [end Module and go to Ventilation Module 8-209]");
		$this->form->addElement('static', null, $this->indent . "If [Refused] then [end Module and go to Ventilation Module 8-209]");
		$this->form->addElement('static', null, $this->indent . "If [Don't Know] then [end Module and go to Ventilation Module 8-209]");


		$this->form->addElement('static', null, "8-206 What did you use to wash
chemicals or dust off your hands?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("f"=>"f) Soap and water or water only", "g"=>"g) [Goop] or similar cleaners", "h"=>"h) Mineral spirits, turpentine, or paint thinner", "i"=>"i) Gasoline or kerosene", "j"=>"j) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [j) Something else] then please specify:');

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-207 Which type of protective clothing or
equipment did you wear?");
		$this->form->addElement('static', null, "Code all that apply.");

		$this->form->addElement('static', null, "PROBE: Any other protective clothing or
equipment?");
		$this->form->addElement('static', null, "<br/>");

		$aToH = array("a) Gloves"=>"a) Gloves", "b) Overalls"=>"b) Overalls", "c) Overcoat (e.g. lab coat, smoke, apron)"=>"c) Overcoat (e.g. lab coat, smoke, apron)",  "d) Dust mask"=>"d) Dust mask", "e) Respirator"=>"e) Respirator", "f) Goggles or safety glasses"=>"f) Goggles or safety glasses",  "g) Work boots/shoes"=>"g) Work boots/shoes",  "h) Other"=>"h) Other");
		reset($aToH);

		while(list($field, $label) = each($aToH)){

			$this->form->addElement('static', null, "<br/>");

			$this->form->addElement("select", "q8_", "{$label}:",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));

		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Other], Please specify:');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] for [part e] then [go to 8-208]");
		$this->form->addElement('static', null, "Otherwise [End Module and go to Ventilation Module ] starts on 8-209");


		$this->form->addElement("select", "q7_", "8-208 What type of respirator was it?",  array(NULL=>"", "01" => "01 A half-mask chemical cartridge respirator, which is silicone or rubber and
covers your mouth and nose", "02" => "02 A full-mask chemical cartridge respirator, which is rubber and covers your eyes, nose, and mouth", "03" => "03  An air-supplied or SCBA respirator", "04" => "04 Some other kind of respirator?", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('textarea', 'other', $this->indent . 'If [Some other kind of respirator], please specify:');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: VENTILATION & ENCLOSURES");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q7_", "8-209 Was there any kind of a ventilation system to remove exhaust, dust, smoke
or fumes from the area?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Probe: By ventilation system we mean purposely opening windows or doors,
using a fume hood, or other ventilation system.");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] then [end Module and go to 8-13]");
		$this->form->addElement('static', null, $this->indent . "If [Refused] [end Module and go to 8-13]");
		$this->form->addElement('static', null, $this->indent . "If [Don't Know] [end Module and go to 8-13]");


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-210 What ventilation systems were
present to remove exhaust, dust,
smoke or fumes from the area? Are
there...");

		$this->form->addElement('static', null, "Code all that apply.");
		$this->form->addElement('static', null, "<br/>");

		$aToF = array("a) A general ventilator system, meaning open doors or
windows, use fan, ect."=>"a) A general ventilator system, meaning open doors or
windows, use fan, ect.", "b) A regular HVAC system for the building and room
heating and cooling"=>"b) A regular HVAC system for the building and room
heating and cooling", "c) A fume hood, lab hood, or other partially enclosed
equipment"=>"c) A fume hood, lab hood, or other partially enclosed
equipment", "d) A glove box or other totally enclosed
equipment"=>"d) A glove box or other totally enclosed
equipment", "e) A portable exhaust hose or tube, such as those used
for welding or to attach to vehicle tailpipe"=>"e) A portable exhaust hose or tube, such as those used
for welding or to attach to vehicle tailpipe",  "f) Some other type of ventilation system"=>"f) Some other type of ventilation system");
		reset($aToF);

		while(list($field, $label) = each($aToF)){

			$this->form->addElement('static', null, "<br/>");

			$this->form->addElement("select", "q8_", "{$label}:",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));

		}
		$this->form->addElement('textarea', 'other', $this->indent . 'Please specify:');


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>When occupational module complete, and there are NO more Occupational Modules to Complete listed in
the Occupational Coding Box then [go to 8-13]");
		$this->form->addElement('static', null, "<br/>");




	}



	function _page35(){   // ========================================================

		// To implement Xin Rule

		$this->form->addFormRule(array(&$this,'XINValidate'));




		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>OCCUPATION MODULE: Cleaners & building maintenance worker (CM)");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-211 Did you conduct any building maintenance activities",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>BOX CM-1");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [8-211] then [go to 8-212]");
		$this->form->addElement('static', null, $this->indent . "Otherwise [go to Household Cleaners Module] starts on 8-263a");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-212 Did you maintain...");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) A furnace or boiler", "b"=>"b) AC equipment");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");

			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('static', null, "<b/>BOX CM-2");
			$this->form->addElement('static', null, "<br/>");

			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('static', null, $this->indent . "If [Yes] to [part a in 8-212] then [go to 8-214]");
			$this->form->addElement('static', null, $this->indent . "Otherwise [go to Lubricating Module] starts on 8-215");

		}
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-213 What type of fuel was usually used
to power the furnace or boiler?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Oil", "b"=>"b) Electricity", "c"=>"c) Methane gas", "d"=>"d) Natural gas", "e"=>"e) Coal",  "f"=>"f) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');
		$this->form->addElement('static', null, "<br/>");



		$this->form->addElement('static', null, "8-214 How often did you use or work around the following heating fuels?");
		$this->form->addElement('static', null, "Probe: How many hours per day, per week or per month did you use the
following art supplies?");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Enter number and choose units or select from the list");

		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Oil", "b"=>"b) Electricity", "c"=>"c) Methane gas", "d"=>"d) Natural gas", "e"=>"e) Coal",  "f"=>"f) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement('static', null, "{$label}:");
			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('textarea', 'other', $this->indent . 'Number:');
			$this->form->addElement('textarea', 'other', $this->indent . 'Units:');
			$this->form->addElement("select", "q8_", "or select from the following:",  array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->form->addElement('static', null, "<br/>");
		}

		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: LUBRICATING ENGINES & MACHINERY");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-215 Did you routinely use lubricating oils, or waxes on engines or machinery?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If [No] then [end Module and go to 8-219]");
		$this->form->addElement('static', null, $this->indent . "If [Refused] [end Module and go to 8-219]");
		$this->form->addElement('static', null, $this->indent . "If [Don't Know] [end Module and go to 8-219]");

		$this->form->addElement('static', null, "8-216 What types of lubricants did you work with?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'week', $this->indent . "Enter lubricant");
		$this->form->addElement("select", "q8_", $this->indent . "",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-217 What types of cutting oils did you
work with?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Straight cutting oils or oils that look and feel like motor
oil", "b"=>"b) Soluble cutting oils or oils that are milky white", "c"=>"c) Synthetic cutting oils or oils that feel like water or may
be brightly colored, such as green or blue", "d"=>"d) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "8-218 How often did you use the following lubricants?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Probe: How many hours per day, per week or per month did you use the
following lubricants?");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Straight cutting oils or oils that look and feel like motor oil", "b"=>"b) Soluble cutting oils or oils that are milky white", "c"=>"c) Synthetic cutting oils or oils that feel like water or may be brightly colored, such as green or blue", "d"=>"d) Something else");

		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement('static', null, "{$label}:");
			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('textarea', 'other', $this->indent . 'Number:');
			$this->form->addElement('textarea', 'other', $this->indent . 'Units:');
			$this->form->addElement("select", "q8_", "or select from the following:",  array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->form->addElement('static', null, "<br/>");
		}

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: CLEANING WITH ORGANIC SOLVENTS");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-219 Did you routinely clean parts with organic solvents or other products to
degrease metal parts?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, $this->indent . "If [No] then [end Module and go to 8-223]");
		$this->form->addElement('static', null, $this->indent . "If [Refused] [end Module and go to 8-223]");
		$this->form->addElement('static', null, $this->indent . "If [Don't Know] [end Module and go to 8-223]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-220 What cleaning products did you
typically use?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) [Gunk] or similar cleaner", "b"=>"b) Acid", "c"=>"c) Alcohols", "d"=>"d) Alkalis or caustics", "e"=>"e) Cutting oils",  "f"=>"f) Diesel",  "g"=>"g) Gasoline",  "h"=>"h) Mineral spirits, paint thinner, naphtha, Stoddard
solvent, turpentin", "i"=>"i) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-221 How often did you use the following cleaning products?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Probe: How many hours per day, per week or per month did you use the
following cleaning products?");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) [Gunk] or similar cleaner", "b"=>"b) Acid", "c"=>"c) Alcohols", "d"=>"d) Alkalis or caustics", "e"=>"e) Cutting oils",  "f"=>"f) Diesel",  "g"=>"g) Gasoline",  "h"=>"h) Mineral spirits, paint thinner, naphtha, Stoddard
solvent, turpentin", "i"=>"i) Something else");

		reset($list);
		while(list($field, $label) = each($list)){

			$this->form->addElement('static', null, "{$label}:");
			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('textarea', 'other', $this->indent . 'Number:');
			$this->form->addElement('textarea', 'other', $this->indent . 'Units:');
			$this->form->addElement("select", "q8_", "or select from the following:",  array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->form->addElement('static', null, "<br/>");
		}


		$this->form->addElement("select", "q8_", "8-222 How often did you work with heating degreasing chemicals?",  array(NULL=>"", "01" => "01 Always", "02" => "02 Sometimes", "03" => "03  Never", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 8-");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [8-24 part E] then [go to Lubricating Engines and Machinery Module and Fuel and Exhaust Smells Module]");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>The next few questions ask about painting, varnishing, and staining.");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: PAINTING, PAINT REMOVAL, PAINT CLEANING");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-223 Did you typically do any of the
following activities?");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Code all that apply:");

		$this->form->addElement('static', null, "<br/>");

		$list = array("a"=>"a) Painting, varnishing, or staining", "b"=>"b) Paint removal", "c"=>"c) Paint thinning and cleaning", "d"=>"d) Something else", "e"=>"e) None of the above");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If [None of the above] then [End Module and
go to 8-231]");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No], [Refused] and/or [Don't Know] to all then [End Module and go to
8-231]");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>BOX PT-1");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part a in 8-225] then [go to 8-224, 8-225,
8-179]");
		$this->form->addElement('static', null, "Otherwise [go to Box PT-2]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-224 What kind of paint did you use?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Laytex or water-based paint", "b"=>"b) Acrylic", "c"=>"c) Oil-based paint (enamel)", "d"=>"d) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-225 Did you usually brush, roll, or
spray paint?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Brush", "b"=>"b) Roll", "c"=>"c) Spray", "d"=>"d) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [8-64 part b] then [go to 8-68]");

		$this->form->addElement("select", "q8_", "8-226 Did you use primers with lead, chromate, or zinc?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>BOX PT-2");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part b in 8-225] then [go to 8-227]");
		$this->form->addElement('static', null, "Otherwise [go to Box PT-3]");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-227 How did you typically remove
paint?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Heat gun", "b"=>"b) Scraper or wire stripper with a drill bit
attachment", "c"=>"c) Chemical paint stripper", "d"=>"d) Some other paint removal method");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Some other paint removal method] then please specify:');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [8-64 part c] then [go to 8-69]");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>BOX PT-3");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part c in 8-227] then [go to 8-228]");
		$this->form->addElement('static', null, "Otherwise [go to 8-230]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-228 What did you typically use to thin
or clean paint, varnish or stain");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Paint thinner, mineral spirits, or turpertin", "b"=>"b) Lacquer thinner", "c"=>"c) Alcohol", "d"=>"d) Water", "e"=>"e) Citrus-based products",  "f"=>"f) Gasoline or kerosene",  "g"=>"g) Other");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [8-68 part c] then [go to 8-70]");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-182 What chemicals did you use to
strip paint?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Other] then please specify:');
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>BOX PT-4");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part c in 8-227] then [go to 8-228]");
		$this->form->addElement('static', null, "Otherwise [go to 8-230]");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-229 What chemicals did you use to
strip paint?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Lacquer or paint thinner", "b"=>"b) Lye (Sodium hydroxide)", "c"=>"c) Ammonia (Ammonia Hydroxide)", "d"=>"d) Other");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Other] then please specify:');
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "8-230 How often did you use the following paint, paint thinners, or paint
strippers?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Probe: How many hours per day, per week or per month did you use the
following paint, paint thinners, or paint strippers?");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Laytex or water-based paint", "b"=>"b) Acrylic", "c"=>"c) Oil-based paint (enamel)","d"=>"d) Paint thinner, mineral spirits, or turpertin", "e"=>"e) Lacquer thinner", "f"=>"f) Alcohol", "g"=>"g) Water", "h"=>"h) Citrus-based products",  "i"=>"i) Gasoline or kerosene", "j"=>"j) Lacquer or paint thinner", "k"=>"k) Lye (Sodium hydroxide)", "l"=>"l) Ammonia (Ammonia Hydroxide)", "m"=>"m) Other" );

		reset($list);
		while(list($field, $label) = each($list)){

			$this->form->addElement('static', null, "{$label}:");
			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('textarea', 'other', $this->indent . 'Number:');
			$this->form->addElement('textarea', 'other', $this->indent . 'Units:');
			$this->form->addElement("select", "q8_", "or select from the following:",  array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->form->addElement('static', null, "<br/>");
		}


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: WOOD DUST");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "8-231 Did you typically do any of the
following:");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Saw wood", "b"=>"b) Sand wood", "c"=>"c) Machine or make wood parts", "d"=>"d) Use a wood chipper", "e"=>"e) Other activities that generate wood",  "f"=>"f) None of these");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Other activities that generate wood] then please specify:');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [None of these] then [go to 8-233]");

		$this->form->addElement('static', null, $this->indent . "If [No], [Refused] and/or [Don't Know] for all then [go to 8-233]");

		$this->form->addElement('static', null, "8-232 How often did you do these things?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Probe: How many hours per day, per week, or per month do you saw wood,
sand wood, do machining, make wood parts, use a wood chipper, or other
activities that generate wood dust?");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Saw wood", "b"=>"b) Sand wood", "c"=>"c) Machine or make wood parts", "d"=>"d) Use a wood chipper", "e"=>"e) Other activities that generate wood",  "f"=>"f) None of these");

		reset($list);
		while(list($field, $label) = each($list)){

			$this->form->addElement('static', null, "{$label}:");
			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('textarea', 'other', $this->indent . 'Number:');
			$this->form->addElement('textarea', 'other', $this->indent . 'Units:');
			$this->form->addElement("select", "q8_", "or select from the following:",  array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->form->addElement('static', null, "<br/>");
		}

		$this->form->addElement("select", "q8_", "8-233 Did your job typically involve handling treated lumber, that is wood treated
with chemical preservatives and has a greenish appearance?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] then [End Module and go to 8-239]");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-234 What did you do with the treated
wood or lumber? Did you...");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Handle it, carry it, or move it", "b"=>"", "c"=>"", "d"=>"", "e"=>"",  "f"=>"",  "g"=>"",  "h"=>"");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q8_", "8-235 When you handled the treated wood, was it usually wet or dry?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q8_", "8-236 Did you apply a preservative, such as cresotoe, to the wood yourself?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 8-238");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-237 What preservatives did you use to
treat the wood");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Pentachlorophenol or PCP", "b"=>"b) Inorganic chemicals, such as copper chromium, arsenate, also called CCA or ACA", "c"=>"c) Creosote", "d"=>"d) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-238 How often did you handle treated wood?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Probe: How many hours per day, per week, or per month did you handle
treated wood?");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Pentachlorophenol or PCP", "b"=>"b) Inorganic chemicals, such as copper chromium, arsenate, also called CCA or ACA", "c"=>"c) Creosote", "d"=>"d) Something else");

		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement('static', null, "{$label}:");
			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('textarea', 'other', $this->indent . 'Number:');
			$this->form->addElement('textarea', 'other', $this->indent . 'Units:');
			$this->form->addElement("select", "q8_", "or select from the following:",  array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('static', null, "<br/>");




	}


	function _page36(){   // ========================================================

		// To implement Xin Rule

		$this->form->addFormRule(array(&$this,'XINValidate'));






		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: PESTICIDE USE");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-239 Pesticides include many types of chemicals used to repel, kill, or control
unwanted weeds, insects, rodents, fungi, or bacteria. They include
herbicides, insecticides, rodenticides, fungicides, and bactericides. Did
you mix, apply, spray, process or use pesticides?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 8-262");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-240 Between [3] and DOBS, which
types of pesticides did you use?");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Code all that apply:");

		$this->form->addElement('static', null, "<br/>");

		$list = array("a) Insecticides which kill bugs"=>"a) Insecticides which kill bugs", "b) Herbicides or weed killer"=>"b) Herbicides or weed killer", "c) Rodenticides which kill rats and mice"=>"c) Rodenticides which kill rats and mice", "d) Fungicides which kill mold or fungus"=>"d) Fungicides which kill mold or fungus", "e) Bactericides which kill bacteria"=>"e) Bactericides which kill bacteria",  "f) Something else?"=>"f) Something else?");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [f) Something else] then please specify:');

		$this->form->addElement('static', null, $this->indent . "If [No] to all a-f thengo to 8-52");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-241 Where did you use the pesticides?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$list = array("a) In or around buildings"=>"a) In or around buildings", "b) On crops"=>"b) On crops", "c) On forests"=>"c) On forests", "d) On roads"=>"d) On roads", "e) On seeds"=>"e) On seeds",  "f) On animals"=>"f) On animals",  "g) For aquatic pest control"=>"g) For aquatic pest control",  "h) To process, pack, or manufacture them at warehouse
or factory"=>"h) To process, pack, or manufacture them at warehouse
or factory",  "i) Something else?"=>"i) Something else?");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}        $this->form->addElement('textarea', 'other', $this->indent . 'If [i) Something else] then please specify:');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box PU-1");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part a in 8-240] then [go to 8-242]");
		$this->form->addElement('static', null, $this->indent . "Otherwise [go to Box PU-2]");


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-242 You said that you used insecticides or bug killers. Please name all that you used");
		$this->form->addElement('textarea', 'week', $this->indent . "Enter insecticide name:");
		$this->form->addElement("select", "q5_", $this->indent . "",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box PU-2");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part b in 8-240] then [go to 8-243]");
		$this->form->addElement('static', null, $this->indent . "Otherwise [go to Box PU-3]");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-243 You said that you used herbicides or weed killers.");
		$this->form->addElement('textarea', 'week', $this->indent . "Enter herbicide name:");
		$this->form->addElement("select", "q5_", $this->indent . "",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box PU-3");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part b in 8-240] then [go to 8-244]");
		$this->form->addElement('static', null, $this->indent . "Otherwise [go to Box PU-4]");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-244 You said that you used rodenticides. Please name all
that you use"); 
		$this->form->addElement('textarea', 'week', $this->indent . "Enter rodenticide name:");
		$this->form->addElement("select", "q5_", $this->indent . "",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box PU-4");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part d in 8-240] then [go to 8-245]");
		$this->form->addElement('static', null, $this->indent . "Otherwise [go to Box PU-5]");

		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "8-245 You said that you used fungicides or mold and
fungus killers. Please name all that you use"); 
		$this->form->addElement('textarea', 'week', $this->indent . "Enter fungicide name:");
		$this->form->addElement("select", "q5_", $this->indent . "",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box PU-5");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part e in 8-240] then [go to 8-245]");
		$this->form->addElement('static', null, $this->indent . "Otherwise [go to Box PU-5]");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-246 You said that you used bactericides or bacteria killers.
Please name all that you use"); 
		$this->form->addElement('textarea', 'week', $this->indent . "Enter bactericide name:");
		$this->form->addElement("select", "q5_", $this->indent . "",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-247 How often did you use the following pesticide products?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Probe: How many hours per day, per week or per month do you use the
following glues or adhesives?");
		$this->form->addElement('static', null, "<br/>");

		$list = array("a) Insecticides which kill bugs"=>"a) Insecticides which kill bugs", "b) Herbicides or weed killer"=>"b) Herbicides or weed killer", "c) Rodenticides which kill rats and mice"=>"c) Rodenticides which kill rats and mice", "d) Fungicides which kill mold or fungus"=>"d) Fungicides which kill mold or fungus", "e) Bactericides which kill bacteria"=>"e) Bactericides which kill bacteria",  "f) Something else?"=>"f) Something else?");
		reset($list);
		while(list($field, $label) = each($list)){

			$this->form->addElement('static', null, "{$label}:");
			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('textarea', 'other', $this->indent . 'Number:');
			$this->form->addElement('textarea', 'other', $this->indent . 'Units:');
			$this->form->addElement("select", "q8_", "or select from the following:",  array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->form->addElement('static', null, "<br/>");
		}


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-248 Which of the following activities
did you typically do?");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Code all that apply:");

		$this->form->addElement('static', null, "<br/>");

		$list = array("a) Mix pesticides"=>"a) Mix pesticides", "b) Put pesticides into a spray container or tank"=>"b) Put pesticides into a spray container or tank", "c) Spray or apply pesticides"=>"c) Spray or apply pesticides", "d) Dispose of waste from pesticide use"=>"d) Dispose of waste from pesticide use", "e) Something else?"=>"e) Something else?");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [e) Something else] then please specify:');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q8_", "8-249 Between [-3] and DOBS, were there 3 or more times when your clothing has
gotten wet with pesticides?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box PU-6");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part b in 8-241] then [go to 8-250]");
		$this->form->addElement('static', null, $this->indent . "Otherwise [go to Box PU-10]");

		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "8-250 You said that you apply pesticides
to crops. How did you usually
apply them?");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Code all that apply:");

		$this->form->addElement('static', null, "<br/>");

		$list = array("a) Using hand-held devices"=>"a) Using hand-held devices", "b) By tractor or truck"=>"b) By tractor or truck", "c) By aircraft"=>"c) By aircraft", "d) Something else?"=>"d) Something else?");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [a] then go to question 8-53");
		$this->form->addElement('textarea', 'other', $this->indent . 'If [d) Something else] then please specify:');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box PU-7");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part a in 8-250] then [go to 8-251]");
		$this->form->addElement('static', null, $this->indent . "Otherwise [go to Box PU-8]");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-251 What type of hand-operated
devices did you usually use?");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Code all that apply:");

		$this->form->addElement('static', null, "<br/>");

		$list = array("a) Pressurized can or aerosols"=>"a) Pressurized can or aerosols", "b) Pressurized cylinders"=>"b) Pressurized cylinders", "c) Trigger pump sprayers or squirt guns"=>"c) Trigger pump sprayers or squirt guns", "Hose-end sprayers"=>"Hose-end sprayers", "e) Compressed air sprayers worn on the back pack or
slung over the shoulder"=>"e) Compressed air sprayers worn on the back pack or
slung over the shoulder",  "f) Push-pull hand pump sprayer"=>"f) Push-pull hand pump sprayer",  "g) Something else?"=>"g) Something else?");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box PU-8");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part b or c in 8-250] then [go to 8-252]");
		$this->form->addElement('static', null, $this->indent . "Otherwise [go to Box PU-9]");

		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-252 What type of pesticide application
device did you use for your
vehicle or aircraft?");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Code all that apply:");

		$this->form->addElement('static', null, "<br/>");

		$list = array("a) Low-pressure boomless sprayer"=>"a) Low-pressure boomless sprayer", "b) Boom sprayer"=>"b) Boom sprayer", "c) High pressure hydraulic sprayers"=>"c) High pressure hydraulic sprayers", "d) Air-blast sprayer"=>"d) Air-blast sprayer", "e) Low-volume air sprayer or mist blower"=>"e) Low-volume air sprayer or mist blower",  "f) Ultra-low volume or ULV sprayer (IF NEEDED: uses
fine droplets with little water)"=>"f) Ultra-low volume or ULV sprayer (IF NEEDED: uses
fine droplets with little water)",  "g) Something else?"=>"g) Something else?");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box PU-9");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part b in 8-250] then [go to 8-253 and 8-254]");
		$this->form->addElement('static', null, $this->indent . "Otherwise [go to Box PU-10]");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q8_", "8-253 Did the vehicle you used for this usually have a cab?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q8_", "8-254 Did you usually keep the windows open or closed?",  array(NULL=>"", "01" => "01 Open", "02" => "02 Closed", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box PU-10");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part b,c or d in 8-241] then [go to 8-255]");
		$this->form->addElement('static', null, $this->indent . "Otherwise [go to Box PU-13]");

		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "8-255 What form of pesticide did you
apply?");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Code all that apply:");

		$this->form->addElement('static', null, "<br/>");

		$list = array("a) Liquid"=>"a) Liquid", "b) Dust"=>"b) Dust", "c) Granules (typically used for landscaping)"=>"c) Granules (typically used for landscaping)", "d) Something else?"=>"d) Something else?");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box PU-11");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part a in 8-255] then [go to 8-256]");
		$this->form->addElement('static', null, $this->indent . "Otherwise [go to Box PU-12]");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-256 What type of liquid did you apply?");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Code all that apply:");

		$this->form->addElement('static', null, "<br/>");

		$list = array("a)"=>"a) Coarse, which are produced by coarse disk or solid
stream gun nozzles", "b)"=>"b) Fine, which are produced by high pressure hollowcone
and fan-spray nozzles", "c)"=>"c) Mists, which are produced by high pressure pumps,
rotors and atomizers", "d"=>"d) Aerosols and fogs, which are produced by thermal
aerosol generators, rotors and atomizers", "e"=>"e) Smokes and fumes, which are produced by thermal
fog generators",  "f"=>"f) Vapors, which are droplets less than 0.001
micron",  "g"=>"g) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box PU-12");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part b in 8-255] then [go to 8-257]");
		$this->form->addElement('static', null, $this->indent . "Otherwise [go to Box PU-13]");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box PU-12");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part b in 8-255] then [go to 8-257]");
		$this->form->addElement('static', null, $this->indent . "Otherwise [go to Box PU-13]");


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-257 What type of dust did you apply?");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Code all that apply:");

		$this->form->addElement('static', null, "<br/>");

		$list = array("a) Coarse"=>"a) Coarse", "b) Medium"=>"b) Medium", "c) Fine"=>"c) Fine");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box PU-6");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part e in 8-241] then [go to 8-258 and 8-259]");
		$this->form->addElement('static', null, $this->indent . "Otherwise [go to Box PU-14]");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q8_", "8-258 You said that you applied pesticides to animals. What type of animals did
you typically apply pesticides to?",  array(NULL=>"", "01" => "01 Farm animals", "02" => "02 Companion animals, such as dogs and cats", "03" => "03  Both farm animals and companion animals", "04" => "04 Some other type of animal?", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Some other type of animal], please specify:');


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-259 How did you usually them? Did
you...");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Code all that apply:");

		$this->form->addElement('static', null, "<br/>");

		$list = array("a) Spray the animals"=>"a) Spray the animals", "b) Dust or pour it on animals"=>"b) Dust or pour it on animals", "c) Inject the animals"=>"c) Inject the animals", "d) Use ear tags"=>"d) Use ear tags", "e) Dip the animals"=>"e) Dip the animals",  "f) Use power duster"=>"f) Use power duster",  "g) Use pest strips"=>"g) Use pest strips",  "h) Use fog/mist animals"=>"h) Use fog/mist animals",  "i) Use rope wick"=>"i) Use rope wick",  "j) Use something else"=>"j) Use something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box PU-14");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part a in 8-241] then [go to 8-260]");
		$this->form->addElement('static', null, $this->indent . "Otherwise [go to Box 8-261]");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-260 You said that you applied
pesticides in or around buildings.
Did you usually use a...");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Code all that apply:");

		$this->form->addElement('static', null, "<br/>");

		$list = array("a) Mist blower"=>"a) Mist blowe", "b) Hand-held spray gun or wand with a spray"=>"b) Hand-held spray gun or wand with a spray", "c) Backpack sprayer "=>"c) Backpack sprayer ", "d) Rig that sat on the floor "=>"d) Rig that sat on the floor ", "e) Dust by hand"=>"e) Dust by hand",  "f) Sub-surface application methods, such as for termite control"=>"f) Sub-surface application methods, such as for termite control",  "g) Something else"=>"g) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-261 On average, how many total days a year did you apply pesticides?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'week', $this->indent . "Enter number of days:");
		$this->form->addElement("select", "q8_", $this->indent . "",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [8-24 part d] then [go to Painting, Paint Removal, Paint Cleaning Module, and Organic Solvent Module]");

		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: FUEL AND EXHAUST SMELLS");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-262 Did you regularly smell fuel vapors, such as from gas or fuel tanks, or
exhaust vapors, such as from car or truck tail pipes?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] then [End Module and go to 8-263a]");

		$this->form->addElement("select", "q8_", "8-263 How strong was the smell",  array(NULL=>"", "01" => "01 Slight", "02" => "02 Moderate", "03" => "03  Strong", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: HOUSEHOLD CLEANER USE");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q8_", "8-263a Did you typically use household cleaning products",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, $this->indent . "If [No] then [end Module and go to Clean Hands Module 8-264]");
		$this->form->addElement('static', null, $this->indent . "If [Refused] [end Module and go to Clean Hands Module 8-264]");
		$this->form->addElement('static', null, $this->indent . "If [Don't Know] [end Module and go to Clean Hands Module 8-264]");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-263b Which types of cleaning products
did you typically use at work?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Ammonia products", "b"=>"b) Chlorine bleach", "c"=>"c) Floor cleaner", "d"=>"d) Floor polish", "e"=>"e) Floor stripper",  "f"=>"f) Furniture or wood polish",  "g"=>"g) Metal polish",  "h"=>"h) Oven cleaner",  "i"=>"i) Paint stripper",  "j"=>"j) Spot and stain remover or carpet cleaner",  "k"=>"k) Turpertine or mineral spirits",  "l"=>"l) Window or mirror cleaner",  "m"=>"m) Other");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Other] then please specify:');
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "8-263c How often did you use the following cleaning products?");
		$this->form->addElement('static', null, "Probe: How many hours per day, per week or per month did you use the
following art supplies?");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Enter number and choose units or select from the list");

		$this->form->addElement('static', null, "<br/>");
		$aToF = array("a"=>"a) Ammonia products", "b"=>"b) Chlorine bleach", "c"=>"c) Floor cleaner", "d"=>"d) Floor polish", "e"=>"e) Floor stripper",  "f"=>"f) Furniture or wood polish",  "g"=>"g) Metal polish",  "h"=>"h) Oven cleaner",  "i"=>"i) Paint stripper",  "j"=>"j) Spot and stain remover or carpet cleaner",  "k"=>"k) Turpertine or mineral spirits",  "l"=>"l) Window or mirror cleaner",  "m"=>"m) Other");

		reset($aToF);
		while(list($field, $label) = each($aToF)){
			$this->form->addElement('static', null, "{$label}:");
			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('textarea', 'other', $this->indent . 'Number:');
			$this->form->addElement('textarea', 'other', $this->indent . 'Units:');
			$this->form->addElement("select", "q8_", "or select from the following:",  array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->form->addElement('static', null, "<br/>");
		}

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: CLEAN HANDS");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-264 Did you regularly get chemicals or dust on your hands or skin?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] then [End Module and go to 8-267]");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-265 When you had chemicals or dust
on your hands, when did you
wash your hands?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");



		$list = array("a"=>"a) When taking a break at work", "b"=>"b) Before eating", "c"=>"c) Before smoking", "d"=>"d) At the end of the work shift", "e"=>"e) When the task is completed",  "f"=>"f) Whenever I get my hands dirty",  "g"=>"g) Don't wash hands");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('static', null, $this->indent . "If [Don't wash hands] then [end Module and go to to PPE Module 8-267]");

		$this->form->addElement('static', null, "8-266 What did you use to wash
chemicals or dust off your hands?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Soap and water or water only", "b"=>"b) [Goop] or similar cleaners", "c"=>"c) Mineral spirits, turpentine, or paint thinner", "d"=>"d) Gasoline or kerosene", "e"=>"e) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');


		$this->form->addElement('static', null, "<br/>");



		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: PERSONAL PROTECTIVE EQUIPMENT");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q8_", "8-267 Between [-3] and DOBS, how often did you wear or use personal protective
equipment (PPE) to protect you from the things you have mentioned? By
personal protective equipment, I mean the things like gloves, dust mask,
goggles, aprons, lab coats or other protective clothing, would you say
always, often, rarely, or never us personal protective equipment?",  array(NULL=>"", "01" => "01 Always", "02" => "02 Often", "03" => "03  Rarely", "04" => "04 Never", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, $this->indent . "If [Never] then [end Module and go to Ventilation Module 8-271]");
		$this->form->addElement('static', null, $this->indent . "If [Refused] then [end Module and go to Ventilation Module 8-271]");
		$this->form->addElement('static', null, $this->indent . "If [Don't Know] then [end Module and go to Ventilation Module 8-271]");


		$this->form->addElement('static', null, "8-268 What did you use to wash
chemicals or dust off your hands?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("f"=>"f) Soap and water or water only", "g"=>"g) [Goop] or similar cleaners", "h"=>"h) Mineral spirits, turpentine, or paint thinner", "i"=>"i) Gasoline or kerosene", "j"=>"j) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [j) Something else] then please specify:');

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-269 Which type of protective clothing or
equipment did you wear?");
		$this->form->addElement('static', null, "Code all that apply.");

		$this->form->addElement('static', null, "PROBE: Any other protective clothing or
equipment?");
		$this->form->addElement('static', null, "<br/>");

		$aToH = array("a) Gloves"=>"a) Gloves", "b) Overalls"=>"b) Overalls", "c) Overcoat (e.g. lab coat, smoke, apron)"=>"c) Overcoat (e.g. lab coat, smoke, apron)",  "d) Dust mask"=>"d) Dust mask", "e) Respirator"=>"e) Respirator", "f) Goggles or safety glasses"=>"f) Goggles or safety glasses",  "g) Work boots/shoes"=>"g) Work boots/shoes",  "h) Other"=>"h) Other");
		reset($aToH);

		while(list($field, $label) = each($aToH)){

			$this->form->addElement('static', null, "<br/>");

			$this->form->addElement("select", "q8_", "{$label}:",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));

		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Other], Please specify:');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] for [part e] then [go to 8-270]");
		$this->form->addElement('static', null, "Otherwise [End Module and go to Ventilation Module ] starts on 8-271");


		$this->form->addElement("select", "q7_", "8-270 What type of respirator was it?",  array(NULL=>"", "01" => "01 A half-mask chemical cartridge respirator, which is silicone or rubber and
covers your mouth and nose", "02" => "02 A full-mask chemical cartridge respirator, which is rubber and covers your eyes, nose, and mouth", "03" => "03  An air-supplied or SCBA respirator", "04" => "04 Some other kind of respirator?", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('textarea', 'other', $this->indent . 'If [Some other kind of respirator], please specify:');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: VENTILATION & ENCLOSURES");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q7_", "8-271 Was there any kind of a ventilation system to remove exhaust, dust, smoke
or fumes from the area?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Probe: By ventilation system we mean purposely opening windows or doors,
using a fume hood, or other ventilation system.");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] then [end Module and go to 8-13]");
		$this->form->addElement('static', null, $this->indent . "If [Refused] [end Module and go to 8-13]");
		$this->form->addElement('static', null, $this->indent . "If [Don't Know] [end Module and go to 8-13]");


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-272 What ventilation systems were
present to remove exhaust, dust,
smoke or fumes from the area? Are
there...");

		$this->form->addElement('static', null, "Code all that apply.");
		$this->form->addElement('static', null, "<br/>");

		$aToF = array("a) A general ventilator system, meaning open doors or
windows, use fan, ect."=>"a) A general ventilator system, meaning open doors or
windows, use fan, ect.", "b) A regular HVAC system for the building and room
heating and cooling"=>"b) A regular HVAC system for the building and room
heating and cooling", "c) A fume hood, lab hood, or other partially enclosed
equipment"=>"c) A fume hood, lab hood, or other partially enclosed
equipment", "d) A glove box or other totally enclosed
equipment"=>"d) A glove box or other totally enclosed
equipment", "e) A portable exhaust hose or tube, such as those used
for welding or to attach to vehicle tailpipe"=>"e) A portable exhaust hose or tube, such as those used
for welding or to attach to vehicle tailpipe",  "f) Some other type of ventilation system"=>"f) Some other type of ventilation system");
		reset($aToF);

		while(list($field, $label) = each($aToF)){

			$this->form->addElement('static', null, "<br/>");

			$this->form->addElement("select", "q8_", "{$label}:",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));

		}
		$this->form->addElement('textarea', 'other', $this->indent . 'Please specify:');


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>When occupational module complete, and there are NO more Occupational Modules to Complete listed in
the Occupational Coding Box then [go to 8-13]");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>OCCUPATION MODULE: Childcare Worker (CW)");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-273 Did you use art supplies while performing your child care duties?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If [Yes] then [go to Art Supplies Module 8-274]");
		$this->form->addElement('static', null, $this->indent . "If [No] then [go to Gluing Module 8-276]");
		$this->form->addElement('static', null, $this->indent . "If [Refused] then[go to Gluing Module 8-276]");
		$this->form->addElement('static', null, $this->indent . "If [Don't Know] then [go to Gluing Module 8-276]");


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: USING ART SUPPLIES");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "8-274 Which art supplies did you
typically use? Or use at least once
a week?");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Code all that apply:");

		$this->form->addElement('static', null, "<br/>");

		$aToF = array("a) Markers"=>"a) Markers", "b) Paints"=>"b) Paints", "c) Inks"=>"c) Inks", "d) Glazes"=>"d) Glazes", "e) Something else"=>"e) Something else",  "f) No art supplies containing chemicals"=>"f) No art supplies containing chemicals");
		reset($aToF);
		while(list($field, $label) = each($aToF)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Yes] to [e) Something else] then please specify:');


		$this->form->addElement('static', null, "8-275 How often did you use the following art supplies?");
		$this->form->addElement('static', null, "Probe: How many hours per day, per week or per month did you use the
following art supplies?");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Enter number and choose units or select from the list");

		$this->form->addElement('static', null, "<br/>");

		$aToF = array("a) Markers"=>"a) Markers", "b) Paints"=>"b) Paints", "c) Inks"=>"c) Inks", "d) Glazes"=>"d) Glazes", "e) Something else"=>"e) Something else",  "f) No art supplies containing chemicals"=>"f) No art supplies containing chemicals");
		reset($aToF);
		while(list($field, $label) = each($aToF)){
			$this->form->addElement('static', null, "{$label}:");
			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('textarea', 'other', $this->indent . 'Number:');
			$this->form->addElement('textarea', 'other', $this->indent . 'Units:');
			$this->form->addElement("select", "q8_", "or select from the following:",  array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Yes] to [e) Something else] then please specify:');

		$this->form->addElement('static', null, "<br/>");


	}


	function _page37(){   // ========================================================

		// To implement Xin Rule

		$this->form->addFormRule(array(&$this,'XINValidate'));





		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: GLUING");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-276 Did you routinely use glues or adhesives?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] then [end Module and go to 8-282]");
		$this->form->addElement('static', null, $this->indent . "If [Refused] then [end Module and go to 8-282]");
		$this->form->addElement('static', null, $this->indent . "If [Don't Know] then [end Module and go to 8-282]");


		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "8-277 Which glues did you use?");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Code all that apply:");

		$this->form->addElement('static', null, "<br/>");

		$list = array("a) Hot melt glues or adhesives"=>"a) Hot melt glues or adhesives", "b) Contact adhesives, such as rubber cement"=>"b) Contact adhesives, such as rubber cement", "c) Water-based adhesives, such as vinyl or acrylic resins"=>"c) Water-based adhesives, such as vinyl or acrylic resins", "d) Wood laminates"=>"d) Wood laminates", "e) Something else"=>"e) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [e) Something else] then please specify:');

		$this->form->addElement('static', null, $this->indent . "If [No], [Don't Know] and/or [Refused] to all then go to question 8-279");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-278 How strong was the smell of {hot melt glues/contact adhesives/water-based
adhesives/wood laminates}?");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Code for each yes response in 8-277");

		$this->form->addElement('static', null, "<br/>");

		$list = array("a) Hot melt glues or adhesives"=>"a) Hot melt glues or adhesives", "b) Contact adhesives, such as rubber cement"=>"b) Contact adhesives, such as rubber cement", "c) Water-based adhesives, such as vinyl or acrylic resins"=>"c) Water-based adhesives, such as vinyl or acrylic resins", "d) Wood laminates"=>"d) Wood laminates", "e) Something else"=>"e) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}", array(NULL=>"", "01" => "01 Slight", "02" => "02 Moderate", "03" => "03  Strong", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->form->addElement('static', null, "<br/>");
		}

		$this->form->addElement("select", "q8_", "8-279 Did you wipe off the excess glue or adhesive with a solvent?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If [No] then [go to 8-281]");
		$this->form->addElement('static', null, $this->indent . "If [Refused] then [go to 8-281]");
		$this->form->addElement('static', null, $this->indent . "If [Don't Know] then [go to 8-281]");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-280 What solvent did you typically
wipe it off with?");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Code all that apply:");

		$this->form->addElement('static', null, "<br/>");

		$list = array("a) Acetone"=>"a) Acetone", "b) Paint thinner"=>"b) Paint thinner", "c) Citrus-based chemicals"=>"c) Citrus-based chemicals", "d) Something else"=>"d) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [d) Something else] then please specify:');

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-281 How often did you use the following glues or adhesives?");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Probe: How many hours per day, per week or per month do you use the
following glues or adhesives?");
		$this->form->addElement('static', null, "<br/>");

		$list = array("a) Hot melt glues or adhesives"=>"a) Hot melt glues or adhesives", "b) Contact adhesives, such as rubber cement"=>"b) Contact adhesives, such as rubber cement", "c) Water-based adhesives, such as vinyl or acrylic resins"=>"c) Water-based adhesives, such as vinyl or acrylic resins", "d) Wood laminates"=>"d) Wood laminates", "e) Something else"=>"e) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement('static', null, "{$label}:");
			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('textarea', 'other', $this->indent . 'Number:');
			$this->form->addElement('textarea', 'other', $this->indent . 'Units:');
			$this->form->addElement("select", "q8_", "or select from the following:",  array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->form->addElement('static', null, "<br/>");
		}




		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: CLEAN HANDS");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-282 Did you regularly get chemicals or dust on your hands or skin?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] then [End Module and go to 8-285]");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-283 When you had chemicals or dust
on your hands, when did you
wash your hands?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");



		$list = array("a"=>"a) When taking a break at work", "b"=>"b) Before eating", "c"=>"c) Before smoking", "d"=>"d) At the end of the work shift", "e"=>"e) When the task is completed",  "f"=>"f) Whenever I get my hands dirty",  "g"=>"g) Don't wash hands");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('static', null, $this->indent . "If [Don't wash hands] then [end Module and go to to 8-285]");


		$this->form->addElement('static', null, "8-284 What did you use to wash
chemicals or dust off your hands?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Soap and water or water only", "b"=>"b) [Goop] or similar cleaners", "c"=>"c) Mineral spirits, turpentine, or paint thinner", "d"=>"d) Gasoline or kerosene", "e"=>"e) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');


		$this->form->addElement('static', null, "<br/>");



		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: PERSONAL PROTECTIVE EQUIPMENT");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q8_", "8-285 Between [-3] and DOBS, how often did you wear or use personal protective
equipment (PPE) to protect you from the things you have mentioned? By
personal protective equipment, I mean the things like gloves, dust mask,
goggles, aprons, lab coats or other protective clothing, would you say
always, often, rarely, or never us personal protective equipment?",  array(NULL=>"", "01" => "01 Always", "02" => "02 Often", "03" => "03  Rarely", "04" => "04 Never", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, $this->indent . "If [Never] then [end Module and go to Ventilation Module 8-271]");
		$this->form->addElement('static', null, $this->indent . "If [Refused] then [end Module and go to Ventilation Module 8-271]");
		$this->form->addElement('static', null, $this->indent . "If [Don't Know] then [end Module and go to Ventilation Module 8-271]");


		$this->form->addElement('static', null, "8-286 What did you use to wash
chemicals or dust off your hands?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("f"=>"f) Soap and water or water only", "g"=>"g) [Goop] or similar cleaners", "h"=>"h) Mineral spirits, turpentine, or paint thinner", "i"=>"i) Gasoline or kerosene", "j"=>"j) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-287 Which type of protective clothing or
equipment did you wear?");
		$this->form->addElement('static', null, "Code all that apply.");

		$this->form->addElement('static', null, "PROBE: Any other protective clothing or
equipment?");
		$this->form->addElement('static', null, "<br/>");

		$aToH = array("a) Gloves"=>"a) Gloves", "b) Overalls"=>"b) Overalls", "c) Overcoat (e.g. lab coat, smoke, apron)"=>"c) Overcoat (e.g. lab coat, smoke, apron)",  "d) Dust mask"=>"d) Dust mask", "e) Respirator"=>"e) Respirator", "f) Goggles or safety glasses"=>"f) Goggles or safety glasses",  "g) Work boots/shoes"=>"g) Work boots/shoes",  "h) Other"=>"h) Other");
		reset($aToH);

		while(list($field, $label) = each($aToH)){

			$this->form->addElement('static', null, "<br/>");

			$this->form->addElement("select", "q8_", "{$label}:",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));

		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Other], Please specify:');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] for [part e] then [go to 8-288]");
		$this->form->addElement('static', null, "Otherwise [End Module and go to Ventilation Module ] starts on 8-289");


		$this->form->addElement("select", "q7_", "8-288 What type of respirator was it?",  array(NULL=>"", "01" => "01 A half-mask chemical cartridge respirator, which is silicone or rubber and
covers your mouth and nose", "02" => "02 A full-mask chemical cartridge respirator, which is rubber and covers your eyes, nose, and mouth", "03" => "03  An air-supplied or SCBA respirator", "04" => "04 Some other kind of respirator?", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('textarea', 'other', $this->indent . 'If [Some other kind of respirator], please specify:');




		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: PHOTOCOPYING/LASER JET PROXIMITY");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q8_", "8-289 Did this job require that you regularly stand at a photocopier for more than
1 hour per day?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-290 Did this job require that you sit within 10 feet of an operating laser jet
printer for more than 1 hour per day?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>When occupational module complete, and there are NO more Occupational Modules to Complete listed in
the Occupational Coding Box then [go to 8-13]");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>OCCUPATION MODULE: Beautician/Barber (BB)");
		$this->form->addElement('static', null, "<br/>");




		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-291 Between [-3] and DOBS, did you
do any of the follow:");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Color or dye hai", "b"=>"b) Bleach hair", "c"=>"c) Tint hair", "d"=>"d) Perm hair", "e"=>"e) Straighten hair using chemicals",  "f"=>"f) Use hair spray",  "g"=>"g) None of these");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [None of these] then [go to 8-296]");


		$this->form->addElement('static', null, "8-292 How often did you do the following activities?");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Probe: How many hours per day, per week or per month do you use the
following glues or adhesives?");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Color or dye hai", "b"=>"b) Bleach hair", "c"=>"c) Tint hair", "d"=>"d) Perm hair", "e"=>"e) Straighten hair using chemicals",  "f"=>"f) Use hair spray",  "g"=>"g) None of these");

		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement('static', null, "{$label}:");
			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('textarea', 'other', $this->indent . 'Number:');
			$this->form->addElement('textarea', 'other', $this->indent . 'Units:');
			$this->form->addElement("select", "q8_", "or select from the following:",  array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->form->addElement('static', null, "<br/>");
		}



		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-293 Between [-3] and DOBS, what type
of hair dye did you use:");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Temporary such as Cationic dyes (IF NEEDED:
METHYL VIOLET),Anionic dyes, or Azo dyes (IF
NEEDED: SUCH AS WATER BASED
RINSES)", "b"=>"b) Semi-permanent mixtures of nitro dyes and
anthraquinones. These dyes produce red yellow and
blue colorings", "c"=>"c) Permanent oxidation dyes (IF NEEDED:
OXIDATION DYES OR 'PARA' DYES). They contain
an oxidizing agent like hydrogen peroxide", "d"=>"d) Quasi-permanent dyes are a mixture of semipermanent
and permanent oxidation dyes");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");

		}

		$this->form->addElement("select", "q8_", "8-294 Which basic color did you use most often?",  array(NULL=>"", "01" => "01 Black", "02" => "02 Brown or brunette", "03" => "03  Blonde", "04" => "04 Red", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-295 Which kind of solution did you usually use to disinfect combs and brushes",  array(NULL=>"", "01" => "01 Barbicide solution", "02" => "02 Bleach solution", "03" => "03  Alcohol solution", "04" => "04 Chlorine solution", "05" => "05 Lysol solution", "06" => "06 Formaldehyde solution", "07" => "07 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('textarea', 'other', $this->indent . 'If [Other], please specify:');


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-296 Did you typically do either of the following?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Manicure clients' nails", "b"=>"b) Apply acrylic nails");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box BB-2");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part a or b in 8-296] then [go to 8-296a]");
		$this->form->addElement('static', null, $this->indent . "Otherwise [go to Clean hands Module 8-297]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q8_", "8-296a
Did you use a manicurist's ventilation table? If needed: Has fan to exhaust
vapors",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: CLEAN HANDS");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-297 Did you regularly get chemicals or dust on your hands or skin?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] then [End Module and go to 8-300]");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-298 When you had chemicals or dust
on your hands, when did you
wash your hands?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");



		$list = array("a"=>"a) When taking a break at work", "b"=>"b) Before eating", "c"=>"c) Before smoking", "d"=>"d) At the end of the work shift", "e"=>"e) When the task is completed",  "f"=>"f) Whenever I get my hands dirty",  "g"=>"g) Don't wash hands");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('static', null, $this->indent . "If [Don't wash hands] then [end Module and go to to PPE Module 8-300]");

		$this->form->addElement('static', null, "8-299 What did you use to wash
chemicals or dust off your hands?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Soap and water or water only", "b"=>"b) [Goop] or similar cleaners", "c"=>"c) Mineral spirits, turpentine, or paint thinner", "d"=>"d) Gasoline or kerosene", "e"=>"e) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: VENTILATION & ENCLOSURES");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q7_", "8-300 Was there any kind of a ventilation system to remove exhaust, dust, smoke
or fumes from the area?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Probe: By ventilation system we mean purposely opening windows or doors,
using a fume hood, or other ventilation system.");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] then [end Module and go to 8-302]");
		$this->form->addElement('static', null, $this->indent . "If [Refused] [end Module and go to 8-302]");
		$this->form->addElement('static', null, $this->indent . "If [Don't Know] [end Module and go to 8-302]");


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-301 What ventilation systems were
present to remove exhaust, dust,
smoke or fumes from the area? Are
there...");

		$this->form->addElement('static', null, "Code all that apply.");
		$this->form->addElement('static', null, "<br/>");

		$aToF = array("a) A general ventilator system, meaning open doors or
windows, use fan, ect."=>"a) A general ventilator system, meaning open doors or
windows, use fan, ect.", "b) A regular HVAC system for the building and room
heating and cooling"=>"b) A regular HVAC system for the building and room
heating and cooling", "c) A fume hood, lab hood, or other partially enclosed
equipment"=>"c) A fume hood, lab hood, or other partially enclosed
equipment", "d) A glove box or other totally enclosed
equipment"=>"d) A glove box or other totally enclosed
equipment", "e) A portable exhaust hose or tube, such as those used
for welding or to attach to vehicle tailpipe"=>"e) A portable exhaust hose or tube, such as those used
for welding or to attach to vehicle tailpipe",  "f) Some other type of ventilation system"=>"f) Some other type of ventilation system");
		reset($aToF);

		while(list($field, $label) = each($aToF)){

			$this->form->addElement('static', null, "<br/>");

			$this->form->addElement("select", "q8_", "{$label}:",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));

		}
		$this->form->addElement('textarea', 'other', $this->indent . 'i f[Some other type of ventilation system], please specify:');






	}




	function _page38(){   // ========================================================

		// To implement Xin Rule

		$this->form->addFormRule(array(&$this,'XINValidate'));




		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: PHOTOCOPYING/LASER JET PROXIMITY");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-302 Did this job require that you regularly stand at a photocopier for more than
1 hour per day?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-303 Did this job require that you sit within 10 feet of an operating laser jet
printer for more than 1 hour per day?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>When occupational module complete, and there are NO more Occupational Modules to Complete listed in
the Occupational Coding Box then [go to 8-13]");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: PERSONAL PROTECTIVE EQUIPMENT");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q8_", "8-304 Between [-3] and DOBS, how often did you wear or use personal protective
equipment (PPE) to protect you from the things you have mentioned? By
personal protective equipment, I mean the things like gloves, dust mask,
goggles, aprons, lab coats or other protective clothing, would you say
always, often, rarely, or never us personal protective equipment?",  array(NULL=>"", "01" => "01 Always", "02" => "02 Often", "03" => "03  Rarely", "04" => "04 Never", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, $this->indent . "If [Never] then [end Module and go to Ventilation Module 8-209]");
		$this->form->addElement('static', null, $this->indent . "If [Refused] then [end Module and go to Ventilation Module 8-209]");
		$this->form->addElement('static', null, $this->indent . "If [Don't Know] then [end Module and go to Ventilation Module 8-209]");


		$this->form->addElement('static', null, "8-305 What did you use to wash
chemicals or dust off your hands?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("f"=>"f) Soap and water or water only", "g"=>"g) [Goop] or similar cleaners", "h"=>"h) Mineral spirits, turpentine, or paint thinner", "i"=>"i) Gasoline or kerosene", "j"=>"j) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [j) Something else] then please specify:');

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-306 Which type of protective clothing or
equipment did you wear?");
		$this->form->addElement('static', null, "Code all that apply.");

		$this->form->addElement('static', null, "PROBE: Any other protective clothing or
equipment?");
		$this->form->addElement('static', null, "<br/>");

		$aToH = array("a) Gloves"=>"a) Gloves", "b) Overalls"=>"b) Overalls", "c) Overcoat (e.g. lab coat, smoke, apron)"=>"c) Overcoat (e.g. lab coat, smoke, apron)",  "d) Dust mask"=>"d) Dust mask", "e) Respirator"=>"e) Respirator", "f) Goggles or safety glasses"=>"f) Goggles or safety glasses",  "g) Work boots/shoes"=>"g) Work boots/shoes",  "h) Other"=>"h) Other");
		reset($aToH);

		while(list($field, $label) = each($aToH)){

			$this->form->addElement('static', null, "<br/>");

			$this->form->addElement("select", "q8_", "{$label}:",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));

		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Other], Please specify:');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] for [part e] then [go to 8-307]");
		$this->form->addElement('static', null, "Otherwise [End Module and go to Ventilation Module ] starts on 8-13");


		$this->form->addElement("select", "q7_", "8-307 What type of respirator was it?",  array(NULL=>"", "01" => "01 A half-mask chemical cartridge respirator, which is silicone or rubber and
covers your mouth and nose", "02" => "02 A full-mask chemical cartridge respirator, which is rubber and covers your eyes, nose, and mouth", "03" => "03  An air-supplied or SCBA respirator", "04" => "04 Some other kind of respirator?", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('textarea', 'other', $this->indent . 'If [Some other kind of respirator], please specify:');

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>When complete module complete, and there are NO more Occupational Modules to Complete listed in
the Occupational Coding Box then [go to 8-13]");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>OCCUPATION MODULE: Driver (DR)");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-308 What kind of vehicle did you primarily drive at work?",  array(NULL=>"", "01" => "01 Bus", "02" => "02 Truck", "03" => "03  Taxi or cab", "04" => "04 Limousine", "05" => "05 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box DR - 1");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If response in [8-308] = [01] then [go to 8-309]");
		$this->form->addElement('static', null, "Otherwise [go to Box DR-2]");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-310 What size truck did you typically drive?",  array(NULL=>"", "01" => "01 Light trucks, such as pickup trucks, vans, or SUVs", "02" => "02 Medium trucks, such as delivery trucks", "03" => "03  Heavy trucks, such as tractor-trailors", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q8_", "8-311 What fuel powers the type of vehicle did you typically drive?",  array(NULL=>"", "01" => "01 Gasoline", "02" => "02 Diesel", "03" => "03  Propane or natural gas", "04" => "04 Electric", "05" => "05 Biodiesel", "06" => "06 Hybrid gas/ electric", "07" => "07 E-85", "08" => "08 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q8_", "8-312 What best describes where you typically drove?",  array(NULL=>"", "01" => "01 Mostly city driving", "02" => "02 Mostly rural driving", "03" => "03  Highway driving", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");



		$this->form->addElement('static', null, "8-313 In a typical work week, how many hours did you usually spend behind
the wheel driving in this job? Don't include time spent commuting to
and from work.");
		$this->form->addElement('static', null, "Probe: How many hours per day, per week or per month did you use the
following art supplies?");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Enter number and choose units or select from the list");

		$this->form->addElement('static', null, "<br/>");
		$aToF = array("a"=>"a) Ammonia products", "b"=>"b) Chlorine bleach", "c"=>"c) Floor cleaner", "d"=>"d) Floor polish", "e"=>"e) Floor stripper",  "f"=>"f) Furniture or wood polish",  "g"=>"g) Metal polish",  "h"=>"h) Oven cleaner",  "i"=>"i) Paint stripper",  "j"=>"j) Spot and stain remover or carpet cleaner",  "k"=>"k) Turpertine or mineral spirits",  "l"=>"l) Window or mirror cleaner",  "m"=>"m) Other");

		reset($aToF);
		while(list($field, $label) = each($aToF)){
			$this->form->addElement('static', null, "{$label}:");
			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('textarea', 'other', $this->indent . 'Number:');
			$this->form->addElement('textarea', 'other', $this->indent . 'Units:');
			$this->form->addElement("select", "q8_", "or select from the following:",  array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-314 While driving to work while you were
pregnant with [SIBLING], what were the
typical conditions while driving in the
vehicles?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Windows were open", "b"=>"b) Ventilation recirculation was off", "c"=>"c) Was anyone smoking in the vehicle");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [] then ");



		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: LUBRICATING ENGINES & MACHINERY");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-315 Did you routinely use lubricating oils, or waxes on engines or machinery?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If [No] then [end Module and go to 8-319]");
		$this->form->addElement('static', null, $this->indent . "If [Refused] [end Module and go to 8-319]");
		$this->form->addElement('static', null, $this->indent . "If [Don't Know] [end Module and go to 8-319]");

		$this->form->addElement('static', null, "8-316 What types of lubricants did you work with?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'week', $this->indent . "Enter lubricant");
		$this->form->addElement("select", "q8_", $this->indent . "",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-317 What types of cutting oils did you
work with?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Straight cutting oils or oils that look and feel like motor
oil", "b"=>"b) Soluble cutting oils or oils that are milky white", "c"=>"c) Synthetic cutting oils or oils that feel like water or may
be brightly colored, such as green or blue", "d"=>"d) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "8-318 How often did you use the following lubricants?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Probe: How many hours per day, per week or per month did you use the
following lubricants?");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Straight cutting oils or oils that look and feel like motor oil", "b"=>"b) Soluble cutting oils or oils that are milky white", "c"=>"c) Synthetic cutting oils or oils that feel like water or may be brightly colored, such as green or blue", "d"=>"d) Something else");

		reset($list);
		while(list($field, $label) = each($list)){

			$this->form->addElement('static', null, "{$label}:");
			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('textarea', 'other', $this->indent . 'Number:');
			$this->form->addElement('textarea', 'other', $this->indent . 'Units:');
			$this->form->addElement("select", "q8_", "or select from the following:",  array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->form->addElement('static', null, "<br/>");
		}

		$this->form->addElement('static', null, "<br/>");



	}

	function _page39(){   // ========================================================

		// To implement Xin Rule

		$this->form->addFormRule(array(&$this,'XINValidate'));






		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: FUEL AND EXHAUST SMELLS");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-319 Did you regularly smell fuel vapors, such as from gas or fuel tanks, or
exhaust vapors, such as from car or truck tail pipes?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] then [End Module and go to 8-13]");

		$this->form->addElement("select", "q8_", "8-320 How strong was the smell",  array(NULL=>"", "01" => "01 Slight", "02" => "02 Moderate", "03" => "03  Strong", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");



		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>When complete module complete, and there are NO more Occupational Modules to Complete listed in
the Occupational Coding Box then [go to 8-13]");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>OCCUPATION MODULE: Agricultural Worker (AW)");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-321 Between [-3] and DOBS, which of
the following activities did you
perform or been near:");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Picked fruits or vegetables by hand", "b"=>"b) Driven or ridden in a tractor or other farm
equipment", "c"=>"c) Fumigated barns, stalls or pens", "d"=>"d) Mixed, applied, spread fertilizer", "e"=>"e) Mixed or added supplements such as additives,
pesticides, etc.",  "f"=>"f) Cleaned up a pesticide spill or leak",  "g"=>"g) Sterilized equipment",  "h"=>"h) Something else with chemical exposure");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box AW - 1");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No], [Refused] and/or [Do not know] to [part a-h in 8-321] then [go to Lubricating Module] starting on 8-334");
		$this->form->addElement('static', null, $this->indent . "Otherwise [go to Clean hands Module 8-332]");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box AW - 2");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part b in 8-321] then [go to Fuel and Exhaust Module] starting on 8-323");
		$this->form->addElement('static', null, $this->indent . "Otherwise [go to Clean hands Module 8-325]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: FUEL AND EXHAUST SMELLS");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-323 Did you regularly smell fuel vapors, such as from gas or fuel tanks, or
exhaust vapors, such as from car or truck tail pipes?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] then [End Module and go to 8-13]");

		$this->form->addElement("select", "q8_", "8-324 How strong was the smell",  array(NULL=>"", "01" => "01 Slight", "02" => "02 Moderate", "03" => "03  Strong", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");



		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-325 What type of farming or
agricultural operation were you
involved in:");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Cattle or dairy", "b"=>"b) Pigs", "c"=>"c) Poultry", "d"=>"d) Sheep or goats", "e"=>"e) Grains or cereals",  "f"=>"f) Fruit and vineyards",  "g"=>"g) Vegetables",  "h"=>"h) Tobacco",  "i"=>"i) Mushroom",  "j"=>"j) Something else with chemical exposure");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box AW - 3");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part b in 8-321] then [go to 8-326");
		$this->form->addElement('static', null, $this->indent . "Otherwise [go to Box AW - 4]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q8_", "8-326 What fuel did your tractor use?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else], please specify:');


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box AW - 4");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part f in 8-321] then [go to 8-327");
		$this->form->addElement('static', null, $this->indent . "Otherwise [go to 8-328]");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box AW - 5");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part a in 8-321] and [Yes] to [8-328] then [go to 8-329, 8-330, 8-331, 8-332]");
		$this->form->addElement('static', null, $this->indent . "Otherwise [go to 8-333]");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-329 Between [-3] and DOBS, which
crops did you pick by hand?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Apples", "b"=>"b) Corn", "c"=>"c) Cotton", "d"=>"d) Cucumbers", "e"=>"e) Flowers",  "f"=>"f) Grapefruit",  "g"=>"g) Grapes",  "h"=>"h) Green beans",  "i"=>"i) Lemons",  "j"=>"j) Lettuce",  "k"=>"k) Limes",  "l"=>"l) Melons",  "m"=>"m) Oranges",  "n"=>"n) Peaches",  "o"=>"o) Pears",  "p"=>"p) Rice",  "q"=>"q) Spinach",  "r"=>"r) Squash",  "s"=>"s) Tomatoes",  "t"=>"t) Wheats",  "u"=>"u) Other");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Other] then please specify:');


		$this->form->addElement("select", "q8_", "8-330 Between [-3] and DOBS, how many times did you ever enter a field or
orchard to pick or gather fruits or vegetables, grains, or other crops within 2
days of having been sprayed with pesticides, herbicides, weed killers,
insecticides, or bug killers?",  array(NULL=>"", "01" => "01 Never", "02" => "02 Once", "03" => "03  2-5 times", "04" => "04 6-10 times", "05" => "05 More than 10 times", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-331 Some people work at jobs where their clothes or shoes get dirty from oil, dust, chemicals, ect. How often did your work clothes get dirty at this job?",  array(NULL=>"", "01" => "01 Never", "02" => "02 Sometimes", "03" => "03  Always", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-332 What clothing did you usually
wear at work?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Shorts or short skirt", "b"=>"b) Long pants or a long skirt", "c"=>"c) Short-sleeved shirt or blouse", "d"=>"d) Long-sleeved shirt or dress", "e"=>"e) Jacket, sweatshirt, apron, or other item worn over your
clothes");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}


		$this->form->addElement("select", "q8_", "8-333 After handling fruits or vegetables, oil, dust, chemicals, ect., did you usually",  array(NULL=>"", "01" => "01 Change your clothes immediately", "02" => "02 Change clothes at lunch or during a bathroom break", "03" => "03  Change clothes at the end of the day", "04" => "04 Wear the same clothes two days in a row or more before washing them", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");




		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: LUBRICATING ENGINES & MACHINERY");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-334 Did you routinely use lubricating oils, or waxes on engines or machinery?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If [No] then [end Module and go to 8-338]");
		$this->form->addElement('static', null, $this->indent . "If [Refused] [end Module and go to 8-338]");
		$this->form->addElement('static', null, $this->indent . "If [Don't Know] [end Module and go to 8-338]");

		$this->form->addElement('static', null, "8-335 What types of lubricants did you work with?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'week', $this->indent . "Enter lubricant");
		$this->form->addElement("select", "q8_", $this->indent . "",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-336 What types of cutting oils did you
work with?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Straight cutting oils or oils that look and feel like motor
oil", "b"=>"b) Soluble cutting oils or oils that are milky white", "c"=>"c) Synthetic cutting oils or oils that feel like water or may
be brightly colored, such as green or blue", "d"=>"d) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "8-337 How often did you use the following lubricants?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Probe: How many hours per day, per week or per month did you use the
following lubricants?");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Straight cutting oils or oils that look and feel like motor oil", "b"=>"b) Soluble cutting oils or oils that are milky white", "c"=>"c) Synthetic cutting oils or oils that feel like water or may be brightly colored, such as green or blue", "d"=>"d) Something else");

		reset($list);
		while(list($field, $label) = each($list)){

			$this->form->addElement('static', null, "{$label}:");
			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('textarea', 'other', $this->indent . 'Number:');
			$this->form->addElement('textarea', 'other', $this->indent . 'Units:');
			$this->form->addElement("select", "q8_", "or select from the following:",  array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->form->addElement('static', null, "<br/>");
		}

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: CLEANING WITH ORGANIC SOLVENTS");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-338  Did you routinely clean parts with organic solvents or other products to
degrease metal parts?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, $this->indent . "If [No] then [end Module and go to 8-342]");
		$this->form->addElement('static', null, $this->indent . "If [Refused] [end Module and go to 8-342]");
		$this->form->addElement('static', null, $this->indent . "If [Don't Know] [end Module and go to 8-342]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-339 What cleaning products did you
typically use?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) [Gunk] or similar cleaner", "b"=>"b) Acid", "c"=>"c) Alcohols", "d"=>"d) Alkalis or caustics", "e"=>"e) Cutting oils",  "f"=>"f) Diesel",  "g"=>"g) Gasoline",  "h"=>"h) Mineral spirits, paint thinner, naphtha, Stoddard
solvent, turpentin", "i"=>"i) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "8-340 How often did you use the following cleaning products?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Probe: How many hours per day, per week or per month did you use the
following cleaning products?");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) [Gunk] or similar cleaner", "b"=>"b) Acid", "c"=>"c) Alcohols", "d"=>"d) Alkalis or caustics", "e"=>"e) Cutting oils",  "f"=>"f) Diesel",  "g"=>"g) Gasoline",  "h"=>"h) Mineral spirits, paint thinner, naphtha, Stoddard
solvent, turpentin", "i"=>"i) Something else");

		reset($list);
		while(list($field, $label) = each($list)){

			$this->form->addElement('static', null, "{$label}:");
			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('textarea', 'other', $this->indent . 'Number:');
			$this->form->addElement('textarea', 'other', $this->indent . 'Units:');
			$this->form->addElement("select", "q8_", "or select from the following:",  array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->form->addElement('static', null, "<br/>");
		}


		$this->form->addElement("select", "q8_", "8-341 How often did you work with heating degreasing chemicals?",  array(NULL=>"", "01" => "01 Always", "02" => "02 Sometimes", "03" => "03  Never", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");



	}
	function _page40(){   // ========================================================

		// To implement Xin Rule

		$this->form->addFormRule(array(&$this,'XINValidate'));






		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: PAINTING, PAINT REMOVAL, PAINT CLEANING");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>The next few questions ask about painting, varnishing, and staining.");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-342 Did you typically do any of the
following activities?");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Code all that apply:");

		$this->form->addElement('static', null, "<br/>");

		$list = array("a"=>"a) Painting, varnishing, or staining", "b"=>"b) Paint removal", "c"=>"c) Paint thinning and cleaning", "d"=>"d) Something else", "e"=>"e) None of the above");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No], [Refused] and/or [Don't Know] to all then [End Module and go to
8-35]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part e in 8-225] then [End Module and go to
8-35]");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>BOX PT-1");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part a in 8-342] then [go to 8-343 and 8-344]");
		$this->form->addElement('static', null, "Otherwise [go to Box PT-2]");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-343 What kind of paint did you use?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Laytex or water-based paint", "b"=>"b) Acrylic", "c"=>"c) Oil-based paint (enamel)", "d"=>"d) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-344 Did you usually brush, roll, or
spray paint?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Brush", "b"=>"b) Roll", "c"=>"c) Spray", "d"=>"d) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [8-64 part b] then [go to 8-68]");


		$this->form->addElement("select", "q8_", "8-345 Did you use primers with lead, chromate, or zinc?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>BOX PT-2");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part b in 8-342] then [go to 8-346]");
		$this->form->addElement('static', null, "Otherwise [go to Box PT-3]");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-346 How did you typically remove
paint?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Heat gun", "b"=>"b) Scraper or wire stripper with a drill bit
attachment", "c"=>"c) Chemical paint stripper", "d"=>"d) Some other paint removal method");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Some other paint removal method] then please specify:');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [8-64 part c] then [go to 8-69]");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>BOX PT-3");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part c in 8-342] then [go to 8-347]");
		$this->form->addElement('static', null, "Otherwise [go to 8-349]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-347 What did you typically use to thin
or clean paint, varnish or stain");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Paint thinner, mineral spirits, or turpertin", "b"=>"b) Lacquer thinner", "c"=>"c) Alcohol", "d"=>"d) Water", "e"=>"e) Citrus-based products",  "f"=>"f) Gasoline or kerosene",  "g"=>"g) Other");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>BOX PT-4");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part c in 8-346] then [go to 8-348]");
		$this->form->addElement('static', null, "Otherwise [go to 8-349]");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "8-348 What chemicals did you use to
strip paint?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Lacquer or paint thinner", "b"=>"b) Lye (Sodium hydroxide)", "c"=>"c) Ammonia (Ammonia Hydroxide)", "d"=>"d) Other");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Other] then please specify:');
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-349 How often did you use the following paint, paint thinners, or paint
strippers?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Probe: How many hours per day, per week or per month did you use the
following paint, paint thinners, or paint strippers?");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Laytex or water-based paint", "b"=>"b) Acrylic", "c"=>"c) Oil-based paint (enamel)","d"=>"d) Paint thinner, mineral spirits, or turpertin", "e"=>"e) Lacquer thinner", "f"=>"f) Alcohol", "g"=>"g) Water", "h"=>"h) Citrus-based products",  "i"=>"i) Gasoline or kerosene", "j"=>"j) Lacquer or paint thinner", "k"=>"k) Lye (Sodium hydroxide)", "l"=>"l) Ammonia (Ammonia Hydroxide)", "m"=>"m) Other" );

		reset($list);
		while(list($field, $label) = each($list)){

			$this->form->addElement('static', null, "{$label}:");
			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('textarea', 'other', $this->indent . 'Number:');
			$this->form->addElement('textarea', 'other', $this->indent . 'Units:');
			$this->form->addElement("select", "q8_", "or select from the following:",  array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->form->addElement('static', null, "<br/>");
		}


		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: SOLDERING AND WELDING");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-350 Did you do any of the following?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Soldering or brazing", "b"=>"b) Smell fumes from others who solder or
braze", "c"=>"c) Welding or flame cutting", "d"=>"d) Smell fumes from others who weld or flame cut,", "e"=>"e) Some other welding or soldering method?",  "f"=>"f) None of the above");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Some other welding or soldering method?] then please specify:');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [None of the above] then [End Module and go to 8-358]");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No], [Refused] and/or [Don't Know] for [all part a-f] then [End Module and go to
8-358]");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>BOX SW-1");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part a or b in 8-350] then [go to 8-354, 8-355, 8-356, 8-357]");
		$this->form->addElement('static', null, $this->indent . "Otherwise, go to 8-357a");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-351 What types of metal did
{you/then/you and those who weld
or flame cut around you} weld or
flame cut?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("h"=>"h) Aluminum", "i"=>"i) Brass or bronz", "j"=>"j) Cast iron", "k"=>"k) Copper", "l"=>"l) Steel",  "m"=>"m) Titanium-based alloy",  "n"=>"n) Other");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Other] then please specify:');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [any part in a-d] then [go to 8-353]");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [any part in f and g] then [go to 8-353]");

		$this->form->addElement("select", "q8_", "8-352 What kind of steel was it?",  array(NULL=>"", "01" => "01 Cadmium plated steel", "02" => "02 Chromium plated steel", "03" => "03  Galvanized iron", "04" => "04 Lead-plated or leaded steel", "05" => "05 Mild, carbon, or construction steel", "06" => "06 Stainless steel", "07" => "07 Another type of steel?", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Another type of steel], please specify:');
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-353 What type of welding or flame cutting did {you/they/you and those who weld
or flame cut around you} do?",  array(NULL=>"", "01" => "01 Oxygas, oxyfuel, or oxyacetylene", "02" => "02 MIG (Metal Inert Gas)", "03" => "03  TIG (Tungsten Inert Gas)", "04" => "04 Stick electrode (shielded metal arc welding)", "05" => "05 Resistance, such as sport, seam, flash, butt, and projection", "06" => "06 Solid state, such as friction or roll", "07" => "07 Plasma arc", "08" => "08 Submerged arc", "09" => "09 Something else", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>BOX SW-2");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part a or b in 8-350] then [go to 8-354, 8-355, 8-356, 8-357]");
		$this->form->addElement('static', null, $this->indent . "Otherwise, go to 8-357a");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-354 What did {you/then/you and those
who solder or braze around you}
solder or braze?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Pipes", "b"=>"b) Electrical or electronic parts", "c"=>"c) Other");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Other] then please specify:');
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-355 Did {you/they/you and those who solder or braze around you} use lead-free
solder?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-356 Did the solder usually contain any unusual ingredients such as cadmium,
silver, copper, nickel, zinc, arsenic, beryllium, antimony, indium, or
bismuth?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Yes] then please specify:');


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-357 What did {you/then/you and those
who solder or braze around you}
solder or braze?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Brass", "b"=>"b) Bronze", "c"=>"c) Cast iron", "d"=>"d) Copper", "e"=>"e) Nickel",  "f"=>"f) Other types of iron",  "g"=>"g) Stainless steel",  "h"=>"h) Other steel",  "i"=>"i) Other");

		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Other] then please specify:');


		$this->form->addElement('static', null, "8-357a How often did you use the following metals?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Probe: How many hours per day, per week or per month do you use the
following metals?");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Brass", "b"=>"b) Bronze", "c"=>"c) Cast iron", "d"=>"d) Copper", "e"=>"e) Nickel",  "f"=>"f) Other types of iron",  "g"=>"g) Stainless steel",  "h"=>"h) Other steel",  "i"=>"i) Other");

		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement('static', null, "{$label}:");
			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('textarea', 'other', $this->indent . 'Number:');
			$this->form->addElement('textarea', 'other', $this->indent . 'Units:');
			$this->form->addElement("select", "q8_", "or select from the following:",  array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->form->addElement('static', null, "<br/>");
		}

		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: WOOD DUST");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "8-358 Did you typically do any of the
following:");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Saw wood", "b"=>"b) Sand wood", "c"=>"c) Machine or make wood parts", "d"=>"d) Use a wood chipper", "e"=>"e) Other activities that generate wood",  "f"=>"f) None of these");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Other activities that generate wood] then please specify:');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [None of these] then [go to 8-360]");

		$this->form->addElement('static', null, $this->indent . "If [No], [Refused] and/or [Don't Know] for all then [go to 8-360]");

		$this->form->addElement('static', null, "8-359 How often did you do these things?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Probe: How many hours per day, per week, or per month do you saw wood,
sand wood, do machining, make wood parts, use a wood chipper, or other
activities that generate wood dust?");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Saw wood", "b"=>"b) Sand wood", "c"=>"c) Machine or make wood parts", "d"=>"d) Use a wood chipper", "e"=>"e) Other activities that generate wood",  "f"=>"f) None of these");

		reset($list);
		while(list($field, $label) = each($list)){

			$this->form->addElement('static', null, "{$label}:");
			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('textarea', 'other', $this->indent . 'Number:');
			$this->form->addElement('textarea', 'other', $this->indent . 'Units:');
			$this->form->addElement("select", "q8_", "or select from the following:",  array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->form->addElement('static', null, "<br/>");
		}

		$this->form->addElement("select", "q8_", "8-360 Did your job typically involve handling treated lumber, that is wood treated
with chemical preservatives and has a greenish appearance?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] then [End Module and go to 8-366]");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-361 What did you do with the treated
wood or lumber? Did you...");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Handle it, carry it, or move it", "b"=>"", "c"=>"", "d"=>"", "e"=>"",  "f"=>"",  "g"=>"",  "h"=>"");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q8_", "8-362 When you handled the treated wood, was it usually wet or dry?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q8_", "8-363 Did you apply a preservative, such as cresotoe, to the wood yourself?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 8-365");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-364 What preservatives did you use to
treat the wood");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Pentachlorophenol or PCP", "b"=>"b) Inorganic chemicals, such as copper chromium, arsenate, also called CCA or ACA", "c"=>"c) Creosote", "d"=>"d) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-365 How often did you handle treated wood?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Probe: How many hours per day, per week, or per month did you handle
treated wood?");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Pentachlorophenol or PCP", "b"=>"b) Inorganic chemicals, such as copper chromium, arsenate, also called CCA or ACA", "c"=>"c) Creosote", "d"=>"d) Something else");

		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement('static', null, "{$label}:");
			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('textarea', 'other', $this->indent . 'Number:');
			$this->form->addElement('textarea', 'other', $this->indent . 'Units:');
			$this->form->addElement("select", "q8_", "or select from the following:",  array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->form->addElement('static', null, "<br/>");
		}




	}


	function _page41(){   // ========================================================

		// To implement Xin Rule

		$this->form->addFormRule(array(&$this,'XINValidate'));






		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: PESTICIDE USE");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-366 Pesticides include many types of chemicals used to repel, kill, or control
unwanted weeds, insects, rodents, fungi, or bacteria. They include
herbicides, insecticides, rodenticides, fungicides, and bactericides. Did
you mix, apply, spray, process or use pesticides?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] or [Refused] or [Don't Know] skip to question 8-389");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-3670 Between [3] and DOBS, which
types of pesticides did you use?");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Code all that apply:");

		$this->form->addElement('static', null, "<br/>");

		$list = array("a) Insecticides which kill bugs"=>"a) Insecticides which kill bugs", "b) Herbicides or weed killer"=>"b) Herbicides or weed killer", "c) Rodenticides which kill rats and mice"=>"c) Rodenticides which kill rats and mice", "d) Fungicides which kill mold or fungus"=>"d) Fungicides which kill mold or fungus", "e) Bactericides which kill bacteria"=>"e) Bactericides which kill bacteria",  "f) Something else?"=>"f) Something else?");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [f) Something else] then please specify:');

		$this->form->addElement('static', null, $this->indent . "If [No] to all a-f thengo to 8-52");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-368 Where did you use the pesticides?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");

		$list = array("a) In or around buildings"=>"a) In or around buildings", "b) On crops"=>"b) On crops", "c) On forests"=>"c) On forests", "d) On roads"=>"d) On roads", "e) On seeds"=>"e) On seeds",  "f) On animals"=>"f) On animals",  "g) For aquatic pest control"=>"g) For aquatic pest control",  "h) To process, pack, or manufacture them at warehouse
or factory"=>"h) To process, pack, or manufacture them at warehouse
or factory",  "i) Something else?"=>"i) Something else?");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}        $this->form->addElement('textarea', 'other', $this->indent . 'If [i) Something else] then please specify:');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box PU-1");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part a in 8-367] then [go to 8-369]");
		$this->form->addElement('static', null, $this->indent . "Otherwise [go to Box PU-2]");


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-369 You said that you used insecticides or bug killers. Please name all that you used");
		$this->form->addElement('textarea', 'week', $this->indent . "Enter insecticide name:");
		$this->form->addElement("select", "q5_", $this->indent . "",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box PU-2");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part b in 8-367] then [go to 8-370]");
		$this->form->addElement('static', null, $this->indent . "Otherwise [go to Box PU-3]");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-370 You said that you used herbicides or weed killers.");
		$this->form->addElement('textarea', 'week', $this->indent . "Enter herbicide name:");
		$this->form->addElement("select", "q5_", $this->indent . "",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box PU-3");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part c in 8-367] then [go to 8-371]");
		$this->form->addElement('static', null, $this->indent . "Otherwise [go to Box PU-4]");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-371 You said that you used rodenticides. Please name all
that you use"); 
		$this->form->addElement('textarea', 'week', $this->indent . "Enter rodenticide name:");
		$this->form->addElement("select", "q5_", $this->indent . "",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box PU-4");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part d in 8-367] then [go to 8-372]");
		$this->form->addElement('static', null, $this->indent . "Otherwise [go to Box PU-5]");

		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "8-372 You said that you used fungicides or mold and
fungus killers. Please name all that you use"); 
		$this->form->addElement('textarea', 'week', $this->indent . "Enter fungicide name:");
		$this->form->addElement("select", "q5_", $this->indent . "",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box PU-5");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part e in 8-367] then [go to 8-372]");
		$this->form->addElement('static', null, $this->indent . "Otherwise [go to 8-374]");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-373 You said that you used bactericides or bacteria killers.
Please name all that you use"); 
		$this->form->addElement('textarea', 'week', $this->indent . "Enter bactericide name:");
		$this->form->addElement("select", "q5_", $this->indent . "",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-374 How often did you use the following pesticide products?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Probe: How many hours per day, per week or per month do you use the
following glues or adhesives?");
		$this->form->addElement('static', null, "<br/>");

		$list = array("a) Insecticides which kill bugs"=>"a) Insecticides which kill bugs", "b) Herbicides or weed killer"=>"b) Herbicides or weed killer", "c) Rodenticides which kill rats and mice"=>"c) Rodenticides which kill rats and mice", "d) Fungicides which kill mold or fungus"=>"d) Fungicides which kill mold or fungus", "e) Bactericides which kill bacteria"=>"e) Bactericides which kill bacteria",  "f) Something else?"=>"f) Something else?");
		reset($list);
		while(list($field, $label) = each($list)){

			$this->form->addElement('static', null, "{$label}:");
			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('textarea', 'other', $this->indent . 'Number:');
			$this->form->addElement('textarea', 'other', $this->indent . 'Units:');
			$this->form->addElement("select", "q8_", "or select from the following:",  array(NULL=>"", "01" => "01 Hours", "02" => "02 Days", "03" => "03  Week", "04" => "04 Month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			$this->form->addElement('static', null, "<br/>");
		}


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-375 Which of the following activities
did you typically do?");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Code all that apply:");

		$this->form->addElement('static', null, "<br/>");

		$list = array("a) Mix pesticides"=>"a) Mix pesticides", "b) Put pesticides into a spray container or tank"=>"b) Put pesticides into a spray container or tank", "c) Spray or apply pesticides"=>"c) Spray or apply pesticides", "d) Dispose of waste from pesticide use"=>"d) Dispose of waste from pesticide use", "e) Something else?"=>"e) Something else?");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [e) Something else] then please specify:');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q8_", "8-376 Between [-3] and DOBS, were there 3 or more times when your clothing has
gotten wet with pesticides?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box PU-6");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part b in 8-368] then [go to 8-377]");
		$this->form->addElement('static', null, $this->indent . "Otherwise [go to Box PU-10]");

		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "8-377 You said that you apply pesticides
to crops. How did you usually
apply them?");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Code all that apply:");

		$this->form->addElement('static', null, "<br/>");

		$list = array("a) Using hand-held devices"=>"a) Using hand-held devices", "b) By tractor or truck"=>"b) By tractor or truck", "c) By aircraft"=>"c) By aircraft", "d) Something else?"=>"d) Something else?");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [d) Something else] then please specify:');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box PU-7");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If [Yes] to [a in 8-377] then [go to 8-378]");
		$this->form->addElement('static', null, $this->indent . "Otherwise [go to Box PU-8]");

		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "8-378 What type of hand-operated
devices did you usually use?");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Code all that apply:");

		$this->form->addElement('static', null, "<br/>");

		$list = array("a) Pressurized can or aerosols"=>"a) Pressurized can or aerosols", "b) Pressurized cylinders"=>"b) Pressurized cylinders", "c) Trigger pump sprayers or squirt guns"=>"c) Trigger pump sprayers or squirt guns", "Hose-end sprayers"=>"Hose-end sprayers", "e) Compressed air sprayers worn on the back pack or
slung over the shoulder"=>"e) Compressed air sprayers worn on the back pack or
slung over the shoulder",  "f) Push-pull hand pump sprayer"=>"f) Push-pull hand pump sprayer",  "g) Something else?"=>"g) Something else?");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box PU-8");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part b or c in 8-377] then [go to 8-379]");
		$this->form->addElement('static', null, $this->indent . "Otherwise [go to Box PU-9]");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-379 What type of pesticide application
device did you use for your
vehicle or aircraft?");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Code all that apply:");

		$this->form->addElement('static', null, "<br/>");

		$list = array("a) Low-pressure boomless sprayer"=>"a) Low-pressure boomless sprayer", "b) Boom sprayer"=>"b) Boom sprayer", "c) High pressure hydraulic sprayers"=>"c) High pressure hydraulic sprayers", "d) Air-blast sprayer"=>"d) Air-blast sprayer", "e) Low-volume air sprayer or mist blower"=>"e) Low-volume air sprayer or mist blower",  "f) Ultra-low volume or ULV sprayer (IF NEEDED: uses
fine droplets with little water)"=>"f) Ultra-low volume or ULV sprayer (IF NEEDED: uses
fine droplets with little water)",  "g) Something else?"=>"g) Something else?");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box PU-9");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part b in 8-377] then [go to 8-380 and 8-381]");
		$this->form->addElement('static', null, $this->indent . "Otherwise [go to Box PU-10]");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q8_", "8-380 Did the vehicle you used for this usually have a cab?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q8_", "8-381 Did you usually keep the windows open or closed?",  array(NULL=>"", "01" => "01 Open", "02" => "02 Closed", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box PU-10");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part b,c or d in 8-368] then [go to 8-382]");
		$this->form->addElement('static', null, $this->indent . "Otherwise [go to Box PU-13]");

		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('static', null, "8-382 What form of pesticide did you
apply?");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Code all that apply:");

		$this->form->addElement('static', null, "<br/>");

		$list = array("a) Liquid"=>"a) Liquid", "b) Dust"=>"b) Dust", "c) Granules (typically used for landscaping)"=>"c) Granules (typically used for landscaping)", "d) Something else?"=>"d) Something else?");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box PU-11");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part a in 8-382] then [go to 8-383]");
		$this->form->addElement('static', null, $this->indent . "Otherwise [go to Box PU-12]");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-383 What type of liquid did you apply?");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Code all that apply:");

		$this->form->addElement('static', null, "<br/>");

		$list = array("a)"=>"a) Coarse, which are produced by coarse disk or solid
stream gun nozzles", "b)"=>"b) Fine, which are produced by high pressure hollowcone
and fan-spray nozzles", "c)"=>"c) Mists, which are produced by high pressure pumps,
rotors and atomizers", "d"=>"d) Aerosols and fogs, which are produced by thermal
aerosol generators, rotors and atomizers", "e"=>"e) Smokes and fumes, which are produced by thermal
fog generators",  "f"=>"f) Vapors, which are droplets less than 0.001
micron",  "g"=>"g) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box PU-12");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part b in 8-382] then [go to 8-384]");
		$this->form->addElement('static', null, $this->indent . "Otherwise [go to Box PU-13]");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-384 What type of dust did you apply?");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Code all that apply:");

		$this->form->addElement('static', null, "<br/>");

		$list = array("a) Coarse"=>"a) Coarse", "b) Medium"=>"b) Medium", "c) Fine"=>"c) Fine");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box PU-13");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part f in 8-368] then [go to 8-385 and 8-386]");
		$this->form->addElement('static', null, $this->indent . "Otherwise [go to Box PU-14]");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q8_", "8-385 You said that you applied pesticides to animals. What type of animals did
you typically apply pesticides to?",  array(NULL=>"", "01" => "01 Farm animals", "02" => "02 Companion animals, such as dogs and cats", "03" => "03  Both farm animals and companion animals", "04" => "04 Some other type of animal?", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Some other type of animal], please specify:');


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-386 How did you usually them? Did
you...");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Code all that apply:");

		$this->form->addElement('static', null, "<br/>");

		$list = array("a) Spray the animals"=>"a) Spray the animals", "b) Dust or pour it on animals"=>"b) Dust or pour it on animals", "c) Inject the animals"=>"c) Inject the animals", "d) Use ear tags"=>"d) Use ear tags", "e) Dip the animals"=>"e) Dip the animals",  "f) Use power duster"=>"f) Use power duster",  "g) Use pest strips"=>"g) Use pest strips",  "h) Use fog/mist animals"=>"h) Use fog/mist animals",  "i) Use rope wick"=>"i) Use rope wick",  "j) Use something else"=>"j) Use something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Box PU-14");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, $this->indent . "If [Yes] to [part a in 8-368] then [go to 8-387]");
		$this->form->addElement('static', null, $this->indent . "Otherwise [go to 8-388]");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-387 You said that you applied
pesticides in or around buildings.
Did you usually use a...");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "Code all that apply:");

		$this->form->addElement('static', null, "<br/>");

		$list = array("a) Mist blower"=>"a) Mist blowe", "b) Hand-held spray gun or wand with a spray"=>"b) Hand-held spray gun or wand with a spray", "c) Backpack sprayer "=>"c) Backpack sprayer ", "d) Rig that sat on the floor "=>"d) Rig that sat on the floor ", "e) Dust by hand"=>"e) Dust by hand",  "f) Sub-surface application methods, such as for termite control"=>"f) Sub-surface application methods, such as for termite control",  "g) Something else"=>"g) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "8-388 On average, how many total days a year did you apply pesticides?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'week', $this->indent . "Enter number of days:");
		$this->form->addElement("select", "q8_", $this->indent . "",  array(NULL=>"", "00" => "00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [Yes] to [8-24 part d] then [go to Painting, Paint Removal, Paint Cleaning Module, and Organic Solvent Module]");

		$this->form->addElement('static', null, "<br/>");



		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: FUEL AND EXHAUST SMELLS");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-389 Did you regularly smell fuel vapors, such as from gas or fuel tanks, or
exhaust vapors, such as from car or truck tail pipes?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] then [End Module and go to 8-391]");

		$this->form->addElement("select", "q8_", "8-390 How strong was the smell",  array(NULL=>"", "01" => "01 Slight", "02" => "02 Moderate", "03" => "03  Strong", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");



		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>ACTIVITY MODULE: CLEAN HANDS");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "8-391 Did you regularly get chemicals or dust on your hands or skin?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . "If [No] then [End Module and go to 8-13]");


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-392 When you had chemicals or dust
on your hands, when did you
wash your hands?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");



		$list = array("a"=>"a) When taking a break at work", "b"=>"b) Before eating", "c"=>"c) Before smoking", "d"=>"d) At the end of the work shift", "e"=>"e) When the task is completed",  "f"=>"f) Whenever I get my hands dirty",  "g"=>"g) Don't wash hands");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('static', null, $this->indent . "If [Don't wash hands] then [end Module and go to 8-13]");

		$this->form->addElement('static', null, "8-393 What did you use to wash
chemicals or dust off your hands?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "Code all that apply:");
		$this->form->addElement('static', null, "<br/>");
		$list = array("a"=>"a) Soap and water or water only", "b"=>"b) [Goop] or similar cleaners", "c"=>"c) Mineral spirits, turpentine, or paint thinner", "d"=>"d) Gasoline or kerosene", "e"=>"e) Something else");
		reset($list);
		while(list($field, $label) = each($list)){
			$this->form->addElement("select", "q8_", "{$label}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not answered"));
			$this->form->addElement('static', null, "<br/>");
		}
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Something else] then please specify:');


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b/>When complete module complete, and there are NO more Occupational Modules to Complete listed in
the Occupational Coding Box then [go to 8-13]");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");



	}



	function _page42(){   // ========================================================

		// To implement Xin Rule

		$this->form->addFormRule(array(&$this,'XINValidate'));




		$this->form->addElement('textarea', 'week', $this->indent . "Interview End date:");

		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('textarea', 'week', $this->indent . "Interview End time:");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'other', $this->indent . "Interviewer's notes");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Occupational Insert Form (questions 8-5 to 8-12)");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Now I will ask you questions about next job you mentioned, starting with (2nd, 3rd, 4th, ect) job
where you worked. We will begin with the next job where you worked you the most hours.");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q8_", "8-5 What is your job title or occupation? (For example, teacher, secretary,
nurse, clerk, maid, paralegal, or lab assistant)",  array(NULL=>"", "01" => "01 Any Health Care (Human and Animal)", "02" => "02 Education/Teaching", "03" => "03  Restaurant, Bar, or Food Service", "04" => "04 Cleaning and Building Maintenance", "05" => "05 Child Care (Pre-Kindergarten)", "06" => "06 Beautician/Barber", "07" => "07 Driver", "08" => "08 Agriculture, Farming, Landscaping, Pesticide Workers", "09" => "09 Other Industry or Business", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-6 What type of activities do you do most often at this job? (For
example, teach classes, work on the computer, keep account
books, file, photocopy, answer phone, wait table, help
customers, do lab work, or carpentry)");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "ANY HEALTH CARE (HUMAN AND ANIMAL)",  array(NULL=>"", "01" => "01 Health care provider office (e.g. physicians, dentist, etc.)", "02" => "02 Free-standing outpatient/ambulatory care center facility; Center facility", "03" => "03  Hospital", "04" => "04 Home health care agency", "05" => "05 Skilled nursing facility/rehab facility", "06" => "06 Nursing home/assisted living", "07" => "07 Pharmacy", "08" => "08 Veterinary clinic/hospital", "09" => "09 Other health care facility or service", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Other health care facility or service], please specify:');


		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q8_", "EDUCATION/TEACHING",  array(NULL=>"", "10" => "10 Elementary or middle/high school", "11" => "11 Business, technical or trade school", "12" => "12 College or university", "13" => "13 Other school/education provider", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('textarea', 'other', $this->indent . 'If [], please specify:');

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q8_", "RESTAURANT, BAR, OR FOOD SERVICE",  array(NULL=>"", "15" => "15 Grocery store bakery (Bakery in a grocery store)", "16" => "16 Restaurant, caterer or other food service (All restaurants, coffee
shops and fast food)", "17" => "17 Bar", "18" => "18 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('textarea', 'other', $this->indent . 'If [Other], please specify:');
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "CLEANING AND BUILDING MAINTENANCE",  array(NULL=>"", "19" => "19 Company that cleans or maintains buildings or homes, include
cleaning schools, homes and hotels", "20" => "20 Clean or maintain a private home (work for one person or family
only)", "21" => "21 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('textarea', 'other', $this->indent . 'If [Other], please specify:');
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "CHILD CARE (PRE-KINDERGARTEN)",  array(NULL=>"", "22" => "22 Child care facility", "23" => "23 Child care in caretaker's home", "24 Child care in child's home", "25 Other child care ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('textarea', 'other', $this->indent . 'If [Other child care], please specify:');
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", "BEAUTICIAN/BARBER",  array(NULL=>"", "26 Barber shop", "27 Beauty shop", "28 Nail salon", "29 Other beauty services", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('textarea', 'other', $this->indent . 'If [Other beauty services], please specify:');
		$this->form->addElement('static', null, "<br/>");



		$this->form->addElement("select", "q8_", "DRIVER",  array(NULL=>"", "30 School bus driver", "31 Other public transportation", "32 (bus, subway, light rail, streetcar, ect.)", "33 Taxi and limousine service", "34 Tourism", "35 Postal service", "36 Couriers and messengers", "37 Private households", "38 Trucking", "39 Other driving business or industry", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('textarea', 'other', $this->indent . 'If [Other driving business or industry], please specify:');
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q8_", "AGRICULTURE, FARMING, LANDSCAPING, PESTICIDE WORKERS",  array(NULL=>"", "40 Agriculture/farming-crops", "41 Landscaping services and/or pest/control services", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('textarea', 'other', $this->indent . 'If [], please specify:');
		$this->form->addElement('static', null, "<br/>");



		$this->form->addElement("select", "q8_", "OTHER INDUSTRY OR BUSINESS",  array(NULL=>"", "42 Retail sales", "43 Wholesale", "44 Manufacturing", "45 Warehousing", "46 Information and telecommunications (includes internet)", "47 Finance, insurance, real estate, and leasing", "48 Professional, scientific, management, administrative, social
services", "49 Arts, entertainment and recreation (includes hotels, motels and
bed and breakfasts)", "50 Public administration", "51 Services other than public administration (maintenance and repair,
religious, dry-cleaning, funeral home, civic organizations)", "52 Military", "53 Construction", "54 Airlines", "55 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('textarea', 'other', $this->indent . 'If [Other], please specify:');
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement("select", "q8_", "8-8 Now think about school, for this school/job, what best describes the place where you typically work/go to school?",  array(NULL=>"", "01" => "01 Office Area", "02" => "02 Store", "03" => "03  Classroom", "04" => "04 Hotel or Motel", "05" => "05 Restaurant", "06" => "06 Residence, such as
your home or someone
else's home", "07" => "07 Healthcare facility or
hospital", "08" => "08 Laboratory", "09" => "09 Factory, plant or
production area", "10" => "10 Warehouse", "11" => "11 Garage or shop", "12" => "12 Some other indoor
location", "13" => "13 Loading dock", "14" => "14 Construction site", "15" => "15 Grounds, yard, or garden", "16" => "16 Some other outdoor location", "17" => "17 Motor vehicle", "18" => "18 Some other outdoor location", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'other', $this->indent . 'If [12 Some other indoor location], please specify:');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'other', $this->indent . 'If [16 Some other outdoor location], please specify:');
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('textarea', 'other', $this->indent . 'If [18 Some other outdoor location], please specify:');
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-9 How long have you been at this job/attending this school?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'week', $this->indent . "Enter the nummber:");
		$this->form->addElement("select", "q8_", $this->indent . "AND choose from following:",  array(NULL=>"", "Years", "months", "weeks", "days"));


		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement("select", "q8_", $this->indent . "OR choose from following:",  array(NULL=>"", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "8-10 What is the address that you actually
work at this job/attend school?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'week', $this->indent . "Enter address:");
		$this->form->addElement("select", "q8_", $this->indent . "or code from following:",  array(NULL=>"", "01" => "01 Home", "02" => "02 Varies (Construction, Landscaping)", "03" => "03  Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addElement('textarea', 'other', $this->indent . 'If [Other], please specify:');


		$this->form->addElement('static', null, "");
		$this->form->addElement('static', null, "<br/>");

		$mToF = array("Monday"=>"Monday", "Tuesday"=>"Tuesday", "Wednesday"=>"Wednesday", "Thursday"=>"Thursday", "Friday"=>"Friday",  "Saturday"=>"Saturday",  "Sunday"=>"Sunday");
		reset($mToF);

		while(list($field, $label) = each($mToF)){

			$this->form->addElement('static', null, "<br/>");

			$this->form->addElement("select", "q8_", "{$label}:",  array(NULL=>"", "1 Work
Day", "2 Not Work
Day"));

			$this->form->addElement('textarea', 'other', $this->indent . 'Start time:');
			$this->form->addElement('textarea', 'other', $this->indent . 'End time:');
		}

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement("select", "q8_", "8-12 Was your drinking water source at this school/at that school usually...",  array(NULL=>"", "01" => "01 Tap water", "02" => "02 Filtered tap water", "03" => "03 Bottled water", "04" => "04 Some other source?", "05" => "05 Don't drink water at work", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('textarea', 'other', $this->indent . 'If [Some other sourceOther], please specify:');



	}

}

?>