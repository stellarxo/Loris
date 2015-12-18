<?php

require_once 'HTML/QuickForm.php';
require_once 'HTML/QuickForm/Renderer/Array.php';
require_once("RequiredIfGroup.inc");
require_once('RequiredIf.inc');
require_once('NDB_BVL_Instrument_EARLI_interview.class.inc');

class NDB_BVL_Instrument_EARLI_interview_S7_inserts extends NDB_BVL_Instrument_EARLI_interview {



	var $dateOptions2007 = array(
                'language' => 'en',
                'format'   => 'YMd',
                'minYear'  =>  '2007',
                'maxYear'  => '2017', 
                'addEmptyOption' => true,
                'emptyOptionValue' => null);


	//month array
	var $months = array(null=>"", "January"=>"January", "February"=>"February", "March"=>"March", "April"=>"April", "May"=>"May", "June"=>"June", "July"=>"July", "August"=>"August", "September"=>"September", "October"=>"October", "November"=>"November", "December"=>"December", "88_refused" => "88 Refused", "99_dont_know"=> "99 Don't know", "Not_answered" => "Not Answered");
		
	//number arrays
	var $yesNo = array(null => "", '01_yes' => "Yes", '02' => "No", '88_refused' => "88 Refused", '99_dont_know'=> "99 Don't know", 'not_answered' => "Not Answered" );
	var $dateAge = array(NULL=>"",  "01_date" => "01 Date", "02_age" => "02 Age ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered");

	var $years1950 = array(); 
	var $negThreeToNine= array();
	var $negThreeToTen = array();
	var $oneToSeventy = array();
	var $oneToThree = array("1"=>"1", "2"=>"2", "3"=>"3");

	var $columnHeaders = array("month_names_header", "year_header", "month_header", "freq_header");


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
		$this->testName = "EARLI_interview_S7_inserts";           // test_names.Test_name
		$this->table = 'EARLI_interview_S7_inserts';              // name of table containing data keyed by commentID
		$this->commentID = $commentID;

                $db =& Database::singleton();
                $this->_requiredElements = array('interview_time', 'q7_2_m_1', 'q7_19_1', 'q7_37_1_1');



		//The array of dates/timestamps to convert to database dates/timestamps
		$this->dateTimeFields=array("interview_date");

		//GLOBAL DEFINITIONS

		//date formats

		$config =& NDB_Config::singleton();
		$this->dateOptions = array(
		'language' => 'en',
		'format'   => 'YMd',
		'minYear'  => $config->getSetting('startYear'), //allows for proband siblings up to 20 years older than candidate
		'maxYear'  => $config->getSetting('endYear'),
		'addEmptyOption' => true,
		'emptyOptionValue' => null
		);


		$years = array_combine(range(1950, 2017), range(1950, 2017));
                $this->years1950 = array(NULL=>"") + ($years) + array("88_Refused" => "88 Refused", "99_Do_not_know" => "99 Do not know", "not_answered" => "Not Answered");

		//number arrays
		$this->negThreeToNine = array(NULL=>"", "-3" => "-3", "-2"=>"-2", "-1"=>"-1", "01"=>"01", "02"=>"02", "03"=>"03", "04"=>"04", "05"=>"05", "06"=>"06", "07"=>"07", "08"=>"08", "09"=>"09", "88"=>"88 Refused", "99"=>"99 Don't Know", "NA"=>"Not Answered");

		$this->negThreeToTen = array(NULL=>"", "-3" => "-3", "-2"=>"-2", "-1"=>"-1", "01"=>"01", "02"=>"02", "03"=>"03", "04"=>"04", "05"=>"05", "06"=>"06", "07"=>"07", "08"=>"08", "09"=>"09", "10"=>"10", "88"=>"88 Refused", "99"=>"99 Don't Know", "NA"=>"Not Answered");
		
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

		$this->_selectMultipleElements = array_merge($this->_selectMultipleElements, array("q7_16_1", "q7_18_1", "q7_25_p1_1", "q7_25_p2_1", "q7_25_p3_1", "q7_29_p1_1", "q7_29_p2_1", "q7_29_p3_1", "q7_32_1", "q7_34_1", "q7_36_1", "q7_38_1_1", "q7_38_2_1", "q7_38_3_1","q7_38_4_1", "q7_38_5_1", "q7_40_1_1", "q7_40_2_1", "q7_40_3_1", "q7_40_4_1", "q7_40_5_1", "q7_40_6_1", "q7_16_2", "q7_18_2", "q7_25_p1_2", "q7_25_p2_2", "q7_25_p3_2", "q7_29_p1_2", "q7_29_p2_2", "q7_29_p3_2", "q7_32_2", "q7_34_2", "q7_36_2", "q7_38_1_2", "q7_38_2_2", "q7_38_3_2","q7_38_4_2", "q7_38_5_2", "q7_40_1_2", "q7_40_2_2", "q7_40_3_2", "q7_40_4_2", "q7_40_5_2", "q7_40_6_2", "q7_16_3", "q7_18_3", "q7_25_p1_3", "q7_25_p2_3", "q7_25_p3_3", "q7_29_p1_3", "q7_29_p2_3", "q7_29_p3_3", "q7_32_3", "q7_34_3", "q7_36_3", "q7_38_1_3", "q7_38_2_3", "q7_38_3_3","q7_38_4_3", "q7_38_5_3", "q7_40_1_3", "q7_40_2_3", "q7_40_3_3", "q7_40_4_3", "q7_40_5_3", "q7_40_6_3"));

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
		//$this->form->addFormRule(array(&$this,'XINValidate'));

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
		$this->form->addElement('header', 'instrument_title', "EARLI Maternal Interview Section 7 Home Inserts");

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
		$group[] = &$this->form->createElement('select', 'AMPM', null, array(NULL=>"", "AM"=>"AM", "PM"=>"PM", "not_answered"=>"Not Answered"));
		$this->form->addGroup($group, "interview_start_time", "<br />Start time:", $this->_GUIDelimiter, false);
                unset($group);
		$this->XINRegisterRule("interview_time", array("interivew_date{@}!={@}NULL"), "Required", "interview_start_time");
		$this->XINRegisterRule("AMPM", array("interivew_date{@}!={@}NULL"), "Required", "interview_start_time");
		$this->form->addElement('static', null, '<br /><br />');


		// Mr. Samir's Rule
		// Register the RequiredIf quickform rule
		$this->form->registerRule('requiredIfGroup', null, 'HTML_QuickForm_Rule_RequiredIfGroup', 'RequiredIfGroup.inc');
		$this->form->registerRule('requiredIf', null, 'HTML_QuickForm_Rule_RequiredIf', 'RequiredIf.inc');

	} //end function _main()


        function _page1(){
                $this->createPages1(1);
        }

        function _page2(){
                $this->createPages2(1);
        }

        function _page3(){
                $this->createPages3(1);
        }


        function _page4(){
                $this->createPages1(2);
        }

        function _page5(){
                $this->createPages2(2);
        }

        function _page6(){
                $this->createPages3(2);
        }


        function _page7(){
                $this->createPages1(3);
        }

        function _page8(){
                $this->createPages2(3);
        }

        function _page9(){
                $this->createPages3(3);
        }




	function createPages1($i){   // ========================================================


		$this->form->addElement('header', null, "Section 7. HOME ENVIRONMENTAL EXPOSURES INSERT FORM $i<br /><br /> (PART 1 OF 3)");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('static', null, "<b><i>Now I will ask you questions about the places you have lived since about 3 months before becoming pregnant with [SIBLING] until [DOBS]. Please refer to your calendar and to the Mother's Residential History form.</i></b>");

		//function with more complex rules
		$this->form->addFormRule(array(&$this, 'rulesPage1'));

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Residential History");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		
		//q7-1
		$this->addTextAreaElementRD("q7_1_$i", "7-1-$i. What is the full address of the home where you lived? (please include house or apt number)"); 
		$this->form->addElement('static', null, "<br/>");

		//q7-2
		$this->form->addElement('static', null, "<br/>");

 		$group[] =&$this->form->createElement("static", "month_header");
                $group[] =&$this->form->createElement("static", "year_header");
                $this->form->addGroup($group, "q7_2_headers_$i", null, $this->_GUIDelimiter, false);
                unset($group);

                $group[] = &$this->form->createElement( "select", "q7_2_m_$i", null, $this->months);
                $group[] = &$this->form->createElement ( "select", "q7_2_y_$i", null, $this->years1950);
                $this->form->addGroup($group, "q7_2_group_$i", "7-2-$i. What was the month and year when you started living here?", $this->_GUIDelimiter, false);
		$this->XINRegisterRule("q7_2_m_$i", array("q7_2_m_$i{@}=={@}"),"You must specify month and year", "q7_2_group");
		$this->XINRegisterRule("q7_2_y_$i", array("q7_2_y_$i{@}=={@}"),"You must specify month and year", "q7_2_group");
                unset($group);
		$this->form->addElement('static', null, "<br/>");


		//q7-3
		$this->form->addElement("select", "q7_3_$i", "7-3-$i. What type of residence was/is it?",  array(NULL=>"", "01" => "01 Single house", "02" => "02 House attached to one or more other houses (duplex/triplex/4-plex)", "03" => "03  Building with 2-4 apartments", "04" => "04 Building with 5-19 apartments", "05" => "05 Building with 20 or more apartments", "06" => "06 Condominium", "07" => "07 Mobile home, RV, boat, van etc.", "08_other" => "08 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->addTextAreaElementRD("q7_3_other_$i", $this->indent . 'If you selected [Other], please specify:');
		$this->XINRegisterRule("q7_3_other_$i", array("q7_3_$i{@}=={@}08_other"), "You must specify other", "q7_3_other_{$i}_group");
		$this->form->addElement('static', null, "<br/>");


		//q7-4
		$this->form->addElement("select", "q7_4_$i", "7-4-$i. Is this house, apartment, or mobile home...",  array(NULL=>"", "01" => "01 Owned by you or someone in this household with a mortgage or loan?", "02" => "02 Owned by you or someone in this household without a mortgage or loan)?", "03" => "03  Rented for cash rent", "04" => "04 Occupied without payment of cash rent?", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");


		//q7-5
		$this->addNumericElementRD("q7_5_$i", $this->indent . "7-5-$i. How many square feet was the home that you live in?");
		$this->form->addElement('static', null, "<br/>");


		//q7-6
		$this->form->addElement('static', null, "7-6-$i. About what year was this house/building built?");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<i>Ask participant to make an estimate or check with the landlord if applicable.</i>");     
		$this->form->addElement('static', null, "<i>For an approximate year, code [1980s] as 1985, code [early 1980s] as 1982, code [late 1980s] as 1988, etc.</i>");
		$this->addTextAreaElementRD("q7_6_year_$i", $this->indent . "Enter year");
		$this->addTextAreaElementRD("q7_6_appr_year_$i", $this->indent . "OR Approximate year:");
		$this->XINRegisterRule("q7_6_year_$i", array("q7_6_appr_year_$i{@}=={@}"), "You must specify year", "q7_6_year_{$i}_group");
		$this->XINRegisterRule("q7_6_appr_year_$i", array("q7_6_year_$i{@}=={@}"), "OR approximate year", "q7_6_appr_year_{$i}_group");
		$this->form->addElement('static', null, "<br/>");


		//q7-7
		$this->form->addElement("select", "q7_7_$i", "7-7-$i. Did/does the tap water come from a private well?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");


		//q7-8
		$this->form->addElement("select", "q7_8_$i", "7-8-$i. About how old was the building when you moved in?",  array(NULL=>"", "01" => "01 More than 50 years old", "02" => "02 25-50 years old", "03" => "03  10-25 years old", "04" => "04 Less than 10 years old", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");


		//q7-9
		$this->form->addElement("select", "q7_9_$i", "7-9-$i. Was/is the outside of the building painted?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");


		//q7-10
		$this->form->addElement("select", "q7_10_$i", "7-10-$i. Was/is it within 1/4 mile of agricultural fields or a golf course?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");


		//q7-11
		$this->form->addElement("select", "q7_11_$i", "7-11-$i. Was/is it within 3 blocks of a gas station?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");


		//q7-12
		$this->form->addElement("select", "q7_12_$i", "7-12-$i. Was the house ever tested for lead?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 7-14");
		$this->form->addElement('static', null, "<br/>");


		//q7-13
		$this->form->addElement("select", "q7_13_$i", "7-13-$i. What were the results of the lead test?",  array(NULL=>"", "01" => "01 High", "02"=>"02 Normal", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q7_13_$i", array("q7_12_$i{@}=={@}01_yes"), "Required if house tested for lead");
		$this->form->addElement('static', null, "<br/>");


		//q7-14
		$this->form->addElement("select", "q7_14_$i", "7-14-$i. Have you lived in any other homes since 3 months prior to your [DOBS]?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, $this->indent . "If you selected [Yes], repeat all above questions with insert");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q7-15
		$this->form->addElement("select", "q7_15_$i", "7-15-$i. Did you have any problems with dampness in your house or basement when you were pregnant with [SIBLING}?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 7-17");


		//q7-16
		$this->form->addElement("select", "q7_16_$i", "7-16-$i. Which trimester(s) of pregnancy with [SIBLING] did you have these dampness problems? Select all that apply:",  array(NULL=>"", "01" => "01", "02" => "02", "03" => "03", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"), "multiple");
		$this->form->addElement('static', null, "<br/>");


		//q7-17
		$this->form->addElement("select", "q7_17_$i", "7-17-$i. Did anyone use any chemicals to kill the mold, mildew or remove the odor when you were pregnant with [SIBLING}?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 7-19");
		$this->form->addElement('static', null, "<br/>");


		$this->form->addElement('select', "q7_18_$i", "7-18-$i Which trimester(s) of pregnancy with [SIBLING] were these chemicals used? Select all that apply:", array(NULL=>"", "01"=>"01", "02"=>"02", "03"=> "03","88 Refused", "99" => "99 Do not know", "Not_Answered" => "Not Answered"), "multiple");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


	} //end function _page20() ======================================================



	function rulesPage1($fields)
	{
		$errors = array();		

                function multSelect($fields, $question1, $question2)
                {
                        return (($fields[$question1] == array(0=>null) && $fields[$question2] == "01_yes") || (empty($fields[$question1])) && $fields[$question2] == "01_yes");
                }

                $i = 0;
                foreach ($fields as $key=>$value)
                {
                        $len = strlen($key);
                        $j = $key[$len-1];
                        $i++;
                        if ($i ==1)
                                break;
                }

	
		//q7-16	
		if (multSelect($fields, "q7_16_$j", "q7_15_$j"))
			$errors["q7_16_$j"] = "You must specify trimester(s)";		


		//q6-18
		if (multSelect($fields, "q7_18_$j", "q7_17_$j"))
			$errors["q7_18_$j"] = "You must specify trimester(s)";		


		return $errors;
	}



	function createPages2($i){   // ========================================================


		$this->form->addElement('header', null, "Section 7. HOME ENVIRONMENTAL EXPOSURES INSERT FORM $i <br /><br /></br /> (PART 2 OF 3)");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Household Product Use");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b><i>Now I am going to ask you about your household product use.</i></b>");
		$this->form->addElement('static', null, "<br/>");


		//function with more complex rules
		$this->form->addFormRule(array(&$this, 'rulesPage2'));

		//q7-19
		$this->form->addElement("select", "q7_19_$i", "7-19-$i. How often was your home dusted when you were pregnant with [SIBLING]?",  array(NULL=>"", "01" => "01 Never", "02" => "02 At least once per day", "03" => "03  3 to 6 times per week", "04" => "04 1 or 2 times per week", "05" => "05 1 to 3 times per month", "06" => "06 6 to 11 times per year", "07" => "07 1 to 5 times per year", "08" => "08 Less than once per year", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, $this->indent . "If you selected [01 Never], go to question 7-21");
		$this->form->addElement('static', null, "<br/>");


		//q7-20
		$this->form->addElement("select", "q7_20_$i", "7-20-$i. Did you do the dusting when you were pregnant with [SIBLING]?",  array(NULL=>"", "01" => "01 Yes, usually", "02" => "02 No, usually", "03" => "03  About half the time", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->XINRegisterRule("q7_20_$i", array("q7_19_$i{@}=={@}02|03|04|05|06|07|08"), "Required if home was dusted");
		$this->form->addElement('static', null, "<br/>");


		//q7-21
		$this->form->addElement("select", "q7_21_$i", "7-21-$i. During your pregnancy with [SIBLING], approximately how many hours a day did you keep the windows or doors open in your home? Was it",  array(NULL=>"", "01" => "01 Less than 1 hour per day", "02" => "02 1-3 hours per day", "03" => "03  4-12 hours per day", "04" => "04 More than 12 hours per day, or", "05" => "05 Not at all", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");


		//q7-22 
		$this->form->addElement("select", "q7_22_$i", "7-22-$i. During cleaning of your home with chemical products like aerosols, were ventilation sources such as fans or windows routinely used when you were pregnant with [SIBLING]?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

		$this->form->addElement('header', null, "<b/>Indoor Products");
		$this->form->addElement('static', null, "<br/>");


		//q7-23
		$this->form->addElement("select", "q7_23_$i", "7-23-$i. Between [-3] and [DOBS], did you use paints, stains or lacquers in your home?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 7-27");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q7-24
		$this->form->addElement('static', null, "7-24-$i. What was the name of the product? How was it used? Who used it?");
		$this->form->addElement('static', null, "<br/>");


		for ($j = 1; $j<4; $j++)
                {
                        $this->addTextAreaElementRD("q7_24_product{$j}_$i", $this->indent . "Product #{$j}:"); 
                        $this->addTextAreaElementRD("q7_24_product{$j}_how_$i", $this->indent . $this->indent . 'How it was used?');
                        $this->form->addElement("select", "q7_24_product{$j}_who_$i", $this->indent . $this->indent . "Who used the product?", array(NULL=>"", "Mother", "Father", "Other", "Not_Answered" => "Not Answered"));
                        $this->form->addElement('static', null, "<br/>");

			if ($j>1)
			{
				$this->XINRegisterRule("q7_24_product{$j}_$i", array("q7_24_product{$j}_$i{@}=={@}NEVER_REQUIRED"), "q7_24_product{$j}_{$i}_group");
				$this->XINRegisterRule("q7_24_product{$j}_how_$i", array("q7_24_product{$j}_how_$i{@}=={@}NEVER_REQUIRED"), "q7_24_product{$j}_how_{$i}_group");
				$this->XINRegisterRule("q7_24_product{$j}_who_$i", array("q7_24_product{$j}_who_$i{@}=={@}NEVER_REQUIRED"));
			}
                }

		$this->XINRegisterRule("q7_24_product1_$i", array("q7_23_$i{@}=={@}01_yes"), "You must specify product", "q7_24_product1_{$i}_group");
		$this->XINRegisterRule("q7_24_product1_how_$i", array("q7_23_$i{@}=={@}01_yes"), "You must specify use", "q7_24_product1_how_{$i}_group");
		$this->XINRegisterRule("q7_24_product1_who_$i", array("q7_23_$i{@}=={@}01_yes"), "You must specify user");
		$this->form->addElement('static', null, "<br/>");


		//q7-25
		$this->form->addElement('static', null, "7-25-$i. During which months was the product used?");
		$this->form->addElement ("select", "q7_25_p1_$i", $this->indent . "Product #1: (Select all that apply):", $this->negThreeToNine, "multiple size = '5'" );
		$this->form->addElement ( "select", "q7_25_p2_$i", $this->indent . "Product #2: (Select all that apply):", $this->negThreeToNine, "multiple size = '5'" );
		$this->form->addElement ( "select", "q7_25_p3_$i", $this->indent . "Product #3: (Select all that apply):", $this->negThreeToNine, "multiple size = '5'" );
		$this->form->addElement('static', null, "<br/>");



		//q7-26
		$this->form->addElement('static', null, "7-26-$i. How often was it used between [-3] and [DOBS]?");

		foreach($this->oneToThree as $field=>$label){

			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('select',"q7_26_{$field}_$i", $this->indent . "Product {$label}:",  array(NULL=>"", "01" => "01 1 day", "02" => "02 2 - 3 days", "03" => "03  4 - 6 days", "04" => "04 1 week", "05" => "05 1 -2 weeks", "06" => "06 2 - 3 weeks", "07" => "07 3 - 4 weeks", "08" => "08 1 month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
			if ($field>1)
				$this->XINRegisterRule("q7_26_{$field}_$i", array("q7_26{$field}_$i{@}=={@}NEVER_REQUIRED"));
		}

		$this->XINRegisterRule("q7_26_1_$i", array("q7_23_$i{@}=={@}01_yes"), "Required if used any of the above products");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

		
		//q7-27
		$this->form->addElement("select", "q7_27_$i", "7-27-$i. Between [-3] and [DOBS], did you use adhesives or petroleum products?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 7-31");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");

		
		//q7-28
		$this->form->addElement('static', null, "7-28-$i. What was the name of the product? How was it used? Who used it?");
		$this->form->addElement('static', null, "<br/>");

		for ($j = 1; $j<4; $j++)
		{		

			$this->addTextAreaElementRD("q7_28_product{$j}_$i", $this->indent . "Product #{$j}:");
			$this->addTextAreaElementRD("q7_28_product{$j}_how_$i", $this->indent . $this->indent . 'How it was used?');
			$this->form->addElement("select", "q7_28_product{$j}_who_$i", $this->indent . $this->indent . "Who used the product?", array(NULL=>"", "Mother", "Father", "Other", "Not_Answered" => "Not Answered"));

			if ($j>1)
                        {
                                $this->XINRegisterRule("q7_28_product{$j}_$i", array("q7_28_product{$j}_$i{@}=={@}NEVER_REQUIRED"), "q7_28_product{$j}_{$i}_group");
                                $this->XINRegisterRule("q7_28_product{$j}_how_$i", array("q7_28_product{$j}_how_$i{@}=={@}NEVER_REQUIRED"), "q7_28_product{$j}_how_{$i}_group");
                             	$this->XINRegisterRule("q7_28_product{$j}_who_$i", array("q7_28_product{$j}_who_$i{@}=={@}NEVER_REQUIRED"));
                        }
		}

		$this->XINRegisterRule("q7_28_product1_{$i}", array("q7_27_$i{@}=={@}01_yes"), "You must specify product", "q7_28_product1_{$i}_group");
                $this->XINRegisterRule("q7_28_product1_how_{$i}", array("q7_27_$i{@}=={@}01_yes"), "You must specify use", "q7_28_product1_how_{$i}_group");
                $this->XINRegisterRule("q7_28_product1_who_$i", array("q7_27_$i{@}=={@}01_yes"), "You must specify user");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q7-29
		$this->form->addElement('static', null, "7-29-$i. During which months was the product used?");
		$this->form->addElement ( "select", "q7_29_p1_$i", $this->indent . "Product #1: (Select all that apply):", $this->negThreeToNine, "multiple size = '5'" );
		$this->form->addElement ( "select", "q7_29_p2_$i", $this->indent . "Product #2: (Select all that apply):", $this->negThreeToNine, "multiple size = '5'" );
		$this->form->addElement ( "select", "q7_29_p3_$i", $this->indent . "Product #3: (Select all that apply):", $this->negThreeToNine, "multiple size = '5'" );

		$this->XINRegisterRule("q7_29_p1_$i", array("q7_27_$i{@}=={@}01_yes"), "Required if used any of the above products");
		$this->XINRegisterRule("q7_29_p2_$i", array("q7_29_p2_$i{@}=={@}NEVER_REQUIRED"));
                $this->XINRegisterRule("q7_29_p3_$i", array("q7_29_p3_$i{@}=={@}NEVER_REQUIRED"));
		$this->form->addElement('static', null, "<br/>");


		//q7-30
		$this->form->addElement('static', null, "7-30_$i. How often was it used between [-3] and [DOBS]?");

		foreach ($this->oneToThree as $field=>$label){

			$this->form->addElement('static', null, "<br/>");
			$this->form->addElement('select', "q7_30_{$field}_$i", $this->indent . "Product {$label}:", array(NULL=>"", "01" => "01 1 day", "02" => "02 2 - 3 days", "03" => "03  4 - 6 days", "04" => "04 1 week", "05" => "05 1 -2 weeks", "06" => "06 2 - 3 weeks", "07" => "07 3 - 4 weeks", "08" => "08 1 month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

			if ($field>1)
				$this->XINRegisterRule("q7_30_{$field}_$i", array("q7_30_{$field}_$i{@}=={@}NEVER_REQUIRED"));
		}

		$this->XINRegisterRule("q7_30_1_$i", array("q7_27_$i{@}=={@}01_yes"), "Required if used any of the above products");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q7-31
		$this->form->addElement("select", "q7_31_$i", "7-31-$i. Between [-3] and [DOBS], were you exposed to any broken thermometers or thermostats with mercury in them?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 7-33");
		$this->form->addElement('static', null, "<br/>");


		//q7-32
		$this->form->addElement ( "select", "q7_32_$i", "7-32-$i. During which months did this happen? (Select all that apply):", $this->negThreeToNine, "multiple size = '5'" );
		$this->XINRegisterRule("q7_32_$i", array("q7_31_$i{@}=={@}01_yes"), "Required if exposed to mercury");
		$this->form->addElement('static', null, "<br/>");


		//q7-33
		$this->form->addElement("select", "q7_33_$i", "7-33-$i. Between [-3] and [DOBS], were you exposed to any broken fluorescent light bulbs?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 7-35");

		//q7-34
		$this->form->addElement ( "select", "q7_34_$i", "7-34-$i. During which months did this happen? (Select all that apply):", $this->negThreeToNine, "multiple size = '5'");
		$this->XINRegisterRule("q7_34_$i", array("q7_33_$i{@}=={@}01_yes"), "Required if exposed to broken fluorescent bulbs");
		$this->form->addElement('static', null, "<br/>");


		//q7-35
		$this->form->addElement("select", "q7_35_$i", "7-35-$i. Between [-3] and [DOBS], were you exposed to any broken electronic switches or relays, or broken gauges?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
		$this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 7-37");


		//q7-36
		$this->form->addElement ( "select", "q7_36_$i", "7-36-$i. During which months did this happen? (Select all that apply):", $this->negThreeToNine, "multiple size = '5'");
		$this->XINRegisterRule("q7_36_$i", array("q7_35_$i{@}=={@}01_yes"), "Required if exposed to broken switches, relays, gauges");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");



	} //end function _page21() =====================================================


	function rulesPage2($fields)
	{
		$errors = array();

                function multSelect($fields, $question1, $question2)
                {
                        return (($fields[$question1] == array(0=>null) && $fields[$question2] == "01_yes") || (empty($fields[$question1])) && $fields[$question2] == "01_yes");
                }

                $i = 0;
                foreach ($fields as $key=>$value)
                {
                        $len = strlen($key);
                        $j = $key[$len-1];
                        $i++;
                        if ($i ==1)
                                break;
                }

		//q7-25
		if (multSelect($fields, "q7_25_p1_$j", "q7_23_$j"))
			$errors["q7_25_p1_$j"] = "You must specify month(s)";


		//q7-29
                if (multSelect($fields, "q7_29_p1_$j", "q7_27_$j"))
                        $errors["q7_29_p1_$j"] = "You must specify month(s)";


		//q7-32, 7-34, 7-36
		for ($i=32; $i<37; $i+=2)
		{
			$k = $i-1;
			if (multSelect($fields, "q7_$i", "q7_$k"))
				$errors["q7_$i"] = "You must specify month(s)";
		}

		return $errors;
	}



	function createPages3($i){   // ========================================================


		$this->form->addElement('header', null, "Section 7. HOME ENVIRONMENTAL EXPOSURES INSERT FORM $i <br /><br /></br /> (PART 3 OF 3)");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<b/>Personal care products");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//function with more complex rules
		$this->form->addFormRule(array(&$this, 'rulesPage3'));


		//q7-37
		$this->form->addElement('static', null, "7-37_$i. I am going to read you a list of personal care products. Please tell me if you used any of the following during your pregnancy with [SIBLING].");

		$products = array("1"=>"1. Hair Colour", "2"=>"2. Nail Polish", "3"=>"3. Sun Screen", "4"=>"4. Perfume", "5"=>"5. Insect Repellant");
		//reset($oneToFive);
		$this->form->addElement('static', null, "<br/>");

		foreach ($products as $field=>$label){

			$this->form->addElement("select", "q7_37_{$field}_$i", $this->indent . "{$label}", $this->yesNo); 
		}

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . $this->indent . "If you selected [Refused] or [Don't Know] skip to question 7-39");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q7-38
		$this->form->addElement('static', null, "7-38-$i. While you were pregnant with [SIBLING], please tell which trimester or trimesters you use the products?");

		$this->form->addElement('static', null, "<br/>");
		$oneToFive = array("1"=>"#1", "2"=>"#2", "3"=>"#3", "4"=>"#4", "5"=>"#5");
		foreach($oneToFive as $field=>$label){

			$this->form->addElement("select", "q7_38_{$field}_$i", $this->indent . $this->indent . "Product {$label}:",  array(NULL=>"", "01" => "01 First Trimester", "02" => "02 Second Trimester", "03" => "03  Third Trimester", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"), "multiple");

		}
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q7-39
		$this->form->addElement('static', null, "7-39-$i. I am going to read you a list of pesticides or pet products. Please tell me if you used any of the following during your pregnancy with [SIBLING].");

		$oneToSix = array("1"=>"1. Ant Traps", "2"=>"2. Roach Traps", "3"=>"3. Insect Spray", "4"=>"4. Fogger", "5"=>"5. Flea Treatment for Pets",  "6"=>"6. Change the Cat Litter");
		$this->form->addElement('static', null, "<br/>");

		while(list($field, $label) = each($oneToSix)){

			$this->form->addElement("select", "q7_39_{$field}_$i", $this->indent . "{$label}:", $this->yesNo);
			
		}

		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . $this->indent . "If you selected [Refused] or [Don't Know] skip to SECTION 8");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


		//q7-40
		$this->form->addElement('static', null, "7-40-$i. While you were pregnant with [SIBLING], please tell which trimester or trimesters you used the products?");

		$oneToSix = array("1"=>"#1", "2"=>"#2", "3"=>"#3", "4"=>"#4", "5"=>"#5",  "6"=>"#6");
		reset($oneToSix);

		while(list($field, $label) = each($oneToSix)){

			$this->form->addElement("select", "q7_40_{$field}_$i", $this->indent . "Product {$label}:",  array(NULL=>"", "01" => "01", "02" => "02", "03" => "03", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"), "multiple");

			if ($field>1)
                                $this->XINRegisterRule("q7_40_{$field}_$i", array("q7_40_{$field}_$i{@}=={@}NEVER_REQUIRED"));

		}

		$this->XINRegisterRule("q7_40_1_$i", array("q7_39{@}=={@}00_specify"), "You must specify trimester(s)");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, $this->indent . $this->indent . "If you selected [Refused] or [Don't Know] skip to question SECTION 8");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('header', null, "END Section 7.");
		$this->form->addElement('static', null, "<br/>");
		$this->form->addElement('static', null, "<br/>");


	} //end function _page22() =====================================================


	function rulesPage3($fields)
	{

		$errors = array();

                function multSelect($fields, $question1, $question2)
                {
                        return (($fields[$question1] == array(0=>null) && $fields[$question2] == "01_yes") || (empty($fields[$question1])) && $fields[$question2] == "01_yes");
                }

                $i = 0;
                foreach ($fields as $key=>$value)
                {
                        $len = strlen($key);
                        $j = $key[$len-1];
                        $i++;
                        if ($i ==1)
                                break;
                }



		//q7-38
		for ($i=1; $i<6; $i++)	
		{
			if (multSelect($fields, "q7_38_{$i}_{$j}", "q7_37_{$i}_{$j}"))
				$errors["q7_38_{$i}_{$j}"] = "You must specify trimester(s)";
		}


		//q7-40
		for ($i=1; $i<7; $i++)
		{
			if (multSelect($fields, "q7_40_{$i}_{$j}", "q7_39_{$i}_{$j}"))
				$errors["q7_40_{$i}_{$j}"] = "You must specify trimester(s)";
		}

		return $errors;
	}


} //end EARLI Maternal Interview Part 2 =================================================

?>
