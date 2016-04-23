<?php

require_once 'HTML/QuickForm.php';
require_once 'HTML/QuickForm/Renderer/Array.php';
require_once("RequiredIfGroup.inc");
require_once('RequiredIf.inc');
require_once('NDB_BVL_Instrument_EARLI_interview.class.inc');



/*

insert into test_battery values ('', 'EARLI_interview_S3_inserts', 0, 0, 'Y', 'Visit', '1', 'Vsupplement');

insert into test_battery values ('', 'EARLI_interview_S3_inserts', 0, 0, 'Y', 'Visit', '2', 'Vsupplement');

insert into test_battery values ('', 'EARLI_interview_S3_inserts', 0, 0, 'Y', 'Visit', '3', 'Vsupplement');


insert into test_names values('', 'EARLI_interview_S3_inserts', 'EARLI Interview Section 3 Inserts', 0, 1, NULL);


insert into instrument_subtests values ('', 'EARLI_interview_S3_inserts', 'EARLI_interview_page1', 'Section 3 Insert Pregnancy 2', '1');

insert into instrument_subtests values ('', 'EARLI_interview_S3_inserts', 'EARLI_interview_page2', 'Section 3 Insert Pregnancy 3', '2');)

insert into instrument_subtests values ('', 'EARLI_interview_S3_inserts', 'EARLI_interview_page3', 'Section 3 Insert Pregnancy 4', '3');

insert into instrument_subtests values ('', 'EARLI_interview_S3_inserts', 'EARLI_interview_page4', 'Section 3 Insert Pregnancy 5', '4');

insert into instrument_subtests values ('', 'EARLI_interview_S3_inserts', 'EARLI_interview_page5', 'Section 3 Insert Pregnancy 6', '5');

insert into instrument_subtests values ('', 'EARLI_interview_S3_inserts', 'EARLI_interview_page6', 'Section 3 Insert Pregnancy 7', '6');

insert into instrument_subtests values ('', 'EARLI_interview_S3_inserts', 'EARLI_interview_page7', 'Section 3 Insert Pregnancy 8', '7');

insert into instrument_subtests values ('', 'EARLI_interview_S3_inserts', 'EARLI_interview_page8', 'Section 3 Insert Pregnancy 9', '8');

insert into instrument_subtests values ('', 'EARLI_interview_S3_inserts', 'EARLI_interview_page9', 'Section 3 Insert Pregnancy 10', '9');

insert into instrument_subtests values ('', 'EARLI_interview_S3_inserts', 'EARLI_interview_page10', 'Section 3 Insert Pregnancy 11', '10');


*/


class NDB_BVL_Instrument_EARLI_interview_S3_inserts extends NDB_BVL_Instrument_EARLI_interview {


         var $dateOptions1960 = array(
                'language' => 'en',
                'format'   => 'YMd',
                'minYear'  => '1960',/* $config->getSetting('startYear') *///
                'maxYear'  => '2017' /*$config->getSetting('endYear')*/,
                'addEmptyOption' => true,
                'emptyOptionValue' => null);

      //month array
        var $months = array(null=>"", "January"=>"January", "February"=>"February", "March"=>"March", "April"=>"April", "May"=>"May", "June"=>"June", "July"=>"July", "August"=>"August", "September"=>"September", "October"=>"October", "November"=>"November", "December"=>"December", "88_refused" => "88 Refused", "99_dont_know"=> "99 Don't know", "Not_answered" => "Not Answered");

        //number arrays
        var $yesNo = array(null => "", '01_yes' => "Yes", '02' => "No", '88_refused' => "88 Refused", '99_dont_know'=> "99 Don't know", 'not_answered' => "Not Answered" );
        var $dateAge = array(NULL=>"",  "01_date" => "01 Date", "02_age" => "02 Age ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered");


        var $ageOptions = array();
        var $years1940 = array();
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
                $this->testName = "EARLI_interview_S3_inserts";           // test_names.Test_name
                $this->table = 'EARLI_interview_S3_inserts';              // name of table containing data keyed by commentID
                $this->commentID = $commentID;
                $this->_requiredElements = array('interview_time', 'q3_5_1');


                //The array of dates/timestamps to convert to database dates/timestamps
                $this->dateTimeFields=array("interview_date", "q3_18_1", "q3_18_2", "q3_18_3", "q3_18_4", "q3_18_5", "q3_18_6", "q3_18_7", "q3_18_8", "q3_18_9", "q3_18_10", "q3_19_1_1", "q3_19_2_1", "q3_19_3_1", "q3_19_4_1", "q3_19_5_1",  "q3_19_1_2",  "q3_19_2_2",  "q3_19_3_2",  "q3_19_4_2",  "q3_19_5_2",  "q3_19_1_3",  "q3_19_2_3",  "q3_19_3_3",  "q3_19_4_3",  "q3_19_5_3",  "q3_19_1_4",  "q3_19_2_4",  "q3_19_3_4",  "q3_19_4_4",  "q3_19_5_4",  "q3_19_1_5",  "q3_19_2_5",  "q3_19_3_5",  "q3_19_4_5",  "q3_19_1_6",  "q3_19_2_6",  "q3_19_3_6",  "q3_19_4_6",  "q3_19_5_6",  "q3_19_1_7",  "q3_19_2_7",  "q3_19_3_7",  "q3_19_4_7",  "q3_19_5_7",  "q3_19_1_8",  "q3_19_2_8",  "q3_19_3_8",  "q3_19_4_8",  "q3_19_5_8",  "q3_19_1_9",  "q3_19_2_9",  "q3_19_3_9",  "q3_19_4_9",  "q3_19_5_9",  "q3_19_1_10",  "q3_19_2_10",  "q3_19_3_10",  "q3_19_4_10",  "q3_19_5_10", "q3_20_1", "q3_20_2", "q3_20_3", "q3_20_4", "q3_20_5", "q3_20_6", "q3_20_7", "q3_20_8", "q3_20_9", "q3_20_10", "q3_28_2date_1", "q3_28_2date_2", "q3_28_2date_3", "q3_28_2date_4", "q3_28_2date_5", "q3_28_2date_6", "q3_28_2date_7", "q3_28_2date_8", "q3_28_2date_9", "q3_28_2date_10", "q3_29_d1_1", "q3_29_d2_1", "q3_29_d3_1", "q3_29_d4_1", "q3_29_d5_1", "q3_29_d1_2", "q3_29_d2_2", "q3_29_d3_2", "q3_29_d4_3", "q3_29_d5_2","q3_29_d1_3", "q3_29_d2_3", "q3_29_d3_3", "q3_29_d4_3", "q3_29_d5_3","q3_29_d1_4", "q3_29_d2_4", "q3_29_d3_4", "q3_29_d4_4", "q3_29_d5_5","q3_29_d1_5", "q3_29_d2_5", "q3_29_d3_5", "q3_29_d4_5", "q3_29_d5_5","q3_29_d1_6", "q3_29_d2_6", "q3_29_d3_6", "q3_29_d4_6", "q3_29_d5_6","q3_29_d1_7", "q3_29_d2_7", "q3_29_d3_7", "q3_29_d4_7", "q3_29_d5_7","q3_29_d1_8", "q3_29_d2_8", "q3_29_d3_8", "q3_29_d4_8", "q3_29_d5_8","q3_29_d1_9", "q3_29_d2_9", "q3_29_d3_9", "q3_29_d4_9", "q3_29_d5_9","q3_29_d1_10", "q3_29_d2_10", "q3_29_d3_10", "q3_29_d4_10", "q3_29_d5_10");

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

                $ages = array_combine(range(11,70), range(11,70));
                $this->ageOptions = array(NULL=>"") + ($ages) + array("88_refused"=>"88 Refused", "99_do_not_know"=>"99 Don't Know", "not_answered"=>"Not Answered");

                $years = array_combine(range(1940, 2017), range(1940, 2017));
                $this->years1940 = array(NULL=>"") + ($years) + array("88_Refused" => "88 Refused", "99_Do_not_know" => "99 Do not know", "not_answered" => "Not Answered");
                reset($years);

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

                $this->_selectMultipleElements = array_merge($this->_selectMultipleElements, array("q3_32_1_1","q3_32_2_1","q3_32_3_1","q3_32_4_1", "q3_32_5_1", "q3_32_1_2","q3_32_2_2","q3_32_3_2","q3_32_4_2", "q3_32_5_2", "q3_32_1_3","q3_32_2_3","q3_32_3_3","q3_32_4_3", "q3_32_5_3","q3_32_1_4","q3_32_2_4","q3_32_3_4","q3_32_4_4", "q3_32_5_4", "q3_32_1_5","q3_32_2_5","q3_32_3_5","q3_32_4_5", "q3_32_5_5", "q3_32_1_6","q3_32_2_6","q3_32_3_6","q3_32_4_6", "q3_32_5_6", "q3_32_1_7","q3_32_2_7","q3_32_3_7","q3_32_4_7", "q3_32_5_7", "q3_32_1_8","q3_32_2_8","q3_32_3_8","q3_32_4_8", "q3_32_5_8", "q3_32_1_9","q3_32_2_9","q3_32_3_9","q3_32_4_9", "q3_32_5_9", "q3_32_1_10","q3_32_2_10","q3_32_3_10","q3_32_4_10", "q3_32_5_10")); 


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
                $this->form->addElement('header', 'instrument_title', "EARLI Maternal Interview Sections 3 Inserts");

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

	var $x;

	function _page1(){
		$this->createPages(1);
		$x = 1;
	}

	function _page2(){ 
		$this->createPages(2);
		$x = 2;
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


	function createPages($i)   // ========================================================
	{
                $this->form->addElement('static', null, "<br/>");
		$x = $i;
		$k = $i + 1;
                $this->form->addElement('header', null, "Section 3. PREGNANCY AND REPRODUCTIVE HISTORY INSERT PREGNANCY $k");
                $this->form->addElement('static', null, "<br/>");
                $this->form->addElement('static', null, "<br/>");
            //    $this->form->addElement('static', null, "<b><i>Now I'm going to ask you some questions about your reproductive and pregnancy experiences.");
                $this->form->addElement('static', null, "<br/>");


                //Function with rules for the majority of this page
                $this->form->addFormRule(array(&$this,'rulesPage1'));

/*
                //q3-1
                $this->form->addElement("select", "q3_1_$i", "3-1-$i) How old (in years) were you when you had your first menstrual period?" ,array(NULL=>"","6", "7", "8", "9","10", "11", "12", "13", "14", "15", "16", "17", "18", "19","88_Refused" => "88 Refused",  "99_Do_not_know" => "99 Do not know", "Not_Answered"=>"Not Answered"));
                $this->form->addElement('static', null, $this->indent . " If the age is entered or [Refused], go to question 3-3");
                $this->form->addElement('static', null, $this->indent . " If you selected [Do not know], go to question 3-2");
                $this->form->addElement('static', null, "<br/>");

                //q3-2
                $this->form->addElement("select", "q3_2_$i", "3-2-$i)  What grade were you in when you had your first menstrual period?", array(NULL=>"", "1", "2", "3", "4", "5", "6", "7", "8", "9","10", "11", "12", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
                $this->XINRegisterRule("q3_2_$i", array("q3_1_$i{@}=={@}99_Do_not_know"), "Required if don't know age");
                $this->form->addElement('static', null, "<br/>");

                //q3-3
                $this->form->addElement("select", "q3_3_$i", "3-3-$i)  What was the average or typical number of days of your cycle between the first day of one menstrual period and the first day of the next menstrual period? Please think back to a time when you were not using birth control pills or other hormonal contraceptives.", array(NULL=>"", "21" => "21", "22"=>"22", "23" => "23", "24"=>"24", "25"=>"25", "26"=>"26", "27"=>"27", "28"=>"28", "29"=>"29", "30"=>"30", "31"=>"31", "32"=>"32", "33"=>"33", "34"=>"34", "35"=>"35", "90 Irregular period", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
                $this->form->addElement('static', null, "<br/>");


                //q3-4
                $this->form->addElement('static', null, "<b><i>The remainder of the questions in Section 3 (Pregnancy and Reproductive History) should be asked for <u>each</u> pregnancy <u> except the pregnancy with the [SIBLING</u>].</i></b>");
/*            
		  $this->form->addElement('static', null, "<i>If more than one previous pregnancy, use <b>Pregnancy Insert forms</b> and label as PREGNANCY 2, PREGNANCY 3, PREGNANCY 4, etc.</i>");
                $this->form->addElement('static', null, "<i>All questions pertaining to PREGNANCY 1 should be asked first, then PREGNANCY 2, then PREGNANCY 3, etc.</i>");
*/

                $this->form->addElement('static', null, "<br/>");
		
		if ($i == 1)
                	$this->form->addElement('static', null, "<b><i>The next few questions are about your 2nd pregnancy only.</i></b>");
		if ($i == 2)
                	$this->form->addElement('static', null, "<b><i>The next few questions are about your 3rd pregnancy only.</i></b>");
		if ($i > 2)
                	$this->form->addElement('static', null, "<b><i>The next few questions are about your {$k}th pregnancy only.</i></b>");
                $this->form->addElement('static', null, "<br/>");

                //q3-5
                $this->form->addElement("select", "q3_5_$i", "3-5-$i) How many babies were you carrying during this pregnancy?", array(NULL=>"", "1"=>"1 (Single baby)", "2"=>"2 (Twins)", "3"=>"3", "4"=>"4", "5"=>"5", "88_Refused" => "88 Refused", "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
                $this->form->addElement('static', null, $this->indent . " If you selected [single baby], go to question 3-6");
                $this->form->addElement('static', null, $this->indent . " If you selected [multiple babies],go to question 3-7");
                $this->form->addElement('static', null, "<br/>");

                //q3-6
                $this->form->addElement("select", "q3_6_$i", "3-6-$i) Did this pregnancy end with a/an...? ",  array(NULL=>"", "01" => "01 Live birth", "02" => "02 Stillbirth", "03" => "03  Induced abortion", "04" => "04 Miscarriage", "05" => "05 Tubal pregnancy", "06" => "06 Molar pregnancy", "07_other" => "07 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
                $this->form->addElement('static', null, $this->indent . " If you selected [Live birth], [Refused], or [Don't know], go to question 3-10");
                $this->form->addElement('static', null, $this->indent . " If you selected [Stillbirth], [Induced abortion], [Miscarriage], [Tubal pregnancy], [Molar pregnancy] or, go to question 3-12");
                $this->addTextAreaElementRD("q3_6_text_$i", $this->indent . " If you selected [Other], please specify and go to question 3-12.");
                $this->XINRegisterRule("q3_6_$i", array("q3_5_$i{@}=={@}1"), "Required if carried single baby during 1st pregnancy");
                $this->XINRegisterRule("q3_6_text_$i", array("q3_6_$i{@}=={@}07_other"), "You must specify other", "q3_6_text_{$i}_group");


                //q3-7
                $this->form->addElement('static', null, "<br/>3-7-$i) For this pregnancy, what was the outcome for each baby? Was it a/an...");

                for ($j=1; $j<=5; $j++)
                {

                       $this->form->addElement("select", "q3_7_{$j}_{$i}", "<br/>$this->indent BABY # {$j}",  array(NULL=>"", "01" => "01 Live birth", "02" => "02 Stillbirth", "03" => "03  Induced abortion", "04" => "04 Miscarriage", "05" => "05 Tubal pregnancy", "06" => "06 Molar pregnancy", "07_other" => "07 Other ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
                        if ($j<3)
                                $this->XINRegisterRule("q3_7_{$j}_{$i}", array("q3_5_$i{@}!={@}1"), "Required if had multiple babies");
                        $this->addTextAreaElementRD("q3_7_{$j}_text_{$i}", $this->indent . " If you selected [Other], please specify.");
                        $this->XINRegisterRule("q3_7_{$j}_text_{$i}", array("q3_7_{$j}_{$i}{@}=={@}07_other"), "You must specify other", "q3_7_{$j}_text_{$i}_group");
                }

                $this->XINRegisterRule("q3_7_3_{$i}", array("q3_7_3_{$i}{@}=={@}NEVER_REQUIRED"));
                $this->XINRegisterRule("q3_7_4_{$i}", array("q3_7_4_{$i}{@}=={@}NEVER_REQUIRED"));
                $this->XINRegisterRule("q3_7_5_{$i}", array("q3_7_5_{$i}{@}=={@}NEVER_REQUIRED"));

                $this->form->addElement('static', null, "<br/>");
                $this->form->addElement('static', null, $this->indent . " If [01 Live birth], go to question 3-10");
                $this->form->addElement('static', null, $this->indent . " If [> 01 Live birth], go to question 3-8");
                $this->form->addElement('static', null, $this->indent . " If [other outcome(s)], go to question 3-12");
                $this->form->addElement('static', null, "<br/>");

                //q3-8
                $this->form->addElement("select", "q3_8_$i", "3-8-$i) Were the babies identical?",  array(NULL=>"", "01_yes" => "01 Yes", "02_no" => "02 No", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
                //Rule is in rulesPage1 function
                $this->XINRegisterRule("q3_8_$i", array("q3_8_$i{@}=={@}NEVER_REQUIRED"));
                $this->form->addElement('static', null, $this->indent . " If you selected [Yes], go to question 3-9");
                $this->form->addElement('static', null, $this->indent . " If you selected [No], [Refused] or [Don't Know], skip to question 3-10");
                $this->form->addElement('static', null, "<br/>");


                //3-9
                $this->form->addElement("select", "q3_9_$i", "3-9-$i) How do you know they are identical twins?",  array(NULL=>"", "01" => "01 Doctor told you", "02" => "02 Genetic tests", "03" => "03  They are as alike as two peas in a pod", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
                $this->XINRegisterRule("q3_9_$i", array("q3_8_$i{@}=={@}01_yes"), "Required if babies identical");
                $this->form->addElement('static', null, "<br/>");

                //q3-10
                $this->form->addElement("select", "q3_10_$i", "3-10-$i) Was this pregnancy with [PROBAND]?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

                $this->XINRegisterRule("q3_10_$i", array("q3_10_$i{@}=={@}NEVER_REQUIRED"));
                $this->form->addElement('static', null, $this->indent . " If you selected [Yes], go to question 3-13");
                $this->form->addElement('static', null, $this->indent . " If you selected [No], go to question 3-11");
                $this->form->addElement('static', null, "<br/>");


                //q3-11
                $this->form->addElement("select", "q3_11_$i", "3-11-$i) Does the baby from this pregnancy have the same biological father as [PROBAND]?",  array(NULL=>"", "01_yes" => "01 Yes", "02_no" => "02 No", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
                $this->form->addElement('static', null, $this->indent . "<b>Record answer, then go to question 3-14</b>");
                $this->XINRegisterRule("q3_11_$i", array("q3_10_$i{@}=={@}02"), "Required if not pregnancy with [PROBAND]");
                $this->form->addElement('static', null, "<br/>");


                //q3-12
                $this->form->addElement("select", "q3_12_$i", "3-12-$i) Did the [OUTCOME] have the same biological father as [PROBAND]",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
                $this->XINRegisterRule("q3_12_$i", array("q3_12_$i{@}=={@}NEVER_REQUIRED"));
                $this->form->addElement('static', null, " $this->indent <b>Record answer, then go to question 3-20</b>");
                $this->form->addElement('static', null, "<br/>");


                //q3-13
                $this->form->addElement("static", null, "3-13-$i)");
                $this->form->addElement('static', null, "$this->indent If you selected [live singleton birth], go to question 3-14");
                $this->form->addElement('static', null, " $this->indent If you selected [live multiple births], go to question 3-15");
                $this->form->addElement('static', null, "<br/>");


                //q3-14
                $this->form->addElement('static', null, "3-14-$i) What is the first name of the baby from this pregnancy?");
                $this->addTextAreaElementRD("q3_14_$i", $this->indent . "FIRST NAME:");
                $this->form->addElement('static', null, $this->indent . "<b>Record answer, then go to question 3-16 (If Proband, automatic fill)</b>");
                $this->XINRegisterRule("q3_14_$i", array("q3_14_$i{@}=={@}NEVER_REQUIRED"), "q3_14_{$i}_group");
                $this->form->addElement('static', null, "<br/>");

                //q3-15
                $this->form->addElement('static', null, "3-15-$i) What are the first names of each of the babies born from this pregnancy?"); //, array(NULL=>"", "00_specify"=>"00 Specify", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        //      $this->XINRegisterRule("q3_15", array("q3_15{@}=={@}NEVER_REQUIRED"));


                for ($j=1; $j<6; $j++)
                {
                        $this->addTextAreaElementRD("q3_15_name{$j}_{$i}", $this->indent . "BABY #{$j}:");

//                      if ($i>2)
                                $this->XINRegisterRule("q3_15_name{$j}_{$i}", array("q3_15_name{$j}_{$i}{@}=={@}NEVER_REQUIRED"), "q3_15_name{$j}_{$i}_group");
//                              $this->XINRegisterRule("q3_15_name{$i}", array("q3_15{@}=={@}00_specify"), "You must specify a name");
                }


                $this->form->addElement('static', null, " $this->indent <b>Record answer, then go to question 3-17</b>");
                $this->form->addElement('static', null, "<br/>");


                //q3-16
                $this->form->addElement("select", "q3_16_$i", "3-16-$i) What was the gender of the baby born from this pregnancy? ",  array(NULL=>"", "01" => "01 Boy", "02" => "02 Girl ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
                $this->XINRegisterRule("q3_16_$i", array("q3_16_$i{@}=={@}NEVER_REQUIRED"));
                $this->form->addElement('static', null, " $this->indent <b>Record answer, then go to question 3-18 (If Proband, automatic fill)</b>");
                $this->form->addElement('static', null, "<br/>");

                //q3-17
                $this->form->addElement('static', null, "3-17-$i) What were the genders of the babies born from this pregnancy?");

                for ($j=1; $j<6; $j++)
                {
                        $this->form->addElement("select", "q3_17_{$j}_{$i}", "$this->indent BABY #{$j}:",  array(NULL=>"", "01" => "01 Boy", "02" => "02 Girl", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

//                      if ($i>2)
                        //      $this->XINRegisterRule("q3_17_{$i}", array("q3_17{@}=={@}00_specify"), "You must specify genders");
                //      else
                                $this->XINRegisterRule("q3_17_{$j}_{$i}", array("q3_17_{$j}_{$i}{@}=={@}NEVER_REQUIRED"));
                }


                $this->form->addElement('static', null, "<br/>");
                $this->form->addElement('static', null, " $this->indent<b> Record answer, then go to question 3-19</b>");
                $this->form->addElement('static', null, "<br/>");


                //q3-18
                $this->addCustomDateElement("q3_18_$i", "3-18-$i) What is the birth date of the baby from this pregnancy?", $this->dateOptions1960);
                $this->form->addElement('static', null, " $this->indent<b> Record answer, then go to question 3-30</b>");
                $this->XINRegisterRule("q3_18_{$i}_date", array("q3_18_{$i}_date{@}=={@}NEVER_REQUIRED"), "q3_18_{$i}_date_group");
                $this->XINRegisterRule("q3_18_{$i}_date_status", array("q3_18_{$i}_date_status{@}=={@}NEVER_REQUIRED"), "q3_18_{$i}_date_group");
                $this->form->addElement('static', null, " $this->indent <b>If proband pregnancy (YES to 3-10), record on pregnancy calendar as DOPB.</b>");
                $this->form->addElement('static', null, "<br/>");


                //q3-19
                $this->form->addElement("static", null, "3-19-$i) What are the birth dates of each baby born from this pregnancy?");


                for ($j=1; $j<6; $j++)
                {
                        $this->addCustomDateElement("q3_19_{$j}_{$i}", $this->indent . "BABY #{$j}:", $this->dateOptions1960);

        //              if ($i>2)
                                $this->XINRegisterRule("q3_19_{$j}_{$i}_date", array("q3_19_{$j}_{$i}_date{@}=={@}NEVER_REQUIRED"), "q3_19_{$j}_{$i}_date_group");
                                $this->XINRegisterRule("q3_19_{$j}_{$i}_date_status", array("q3_19_{$j}_{$i}_date_status{@}=={@}NEVER_REQUIRED"), "q3_19_{$j}_{$i}_date_group");
                }


                $this->form->addElement('static', null, " $this->indent<b> Record answer, then go to question 3-23</b>");
                $this->form->addElement('static', null, $this->indent . "<b> If proband pregnancy (YES to 3-10), record on pregnancy calendar as DOPB.</b>");
                $this->form->addElement('static', null, "<br/>");


                //q3-20
                $this->addCustomDateElement("q3_20_$i", "3-20-$i) On what date did this pregnancy end?", $this->dateOptions1960);
                $this->XINRegisterRule("q3_20_{$i}_date", array("q3_20_{$i}_date{@}=={@}NEVER_REQUIRED"), "q3_20_{$i}_date_group");
                $this->XINRegisterRule("q3_20_{$i}_date_status", array("q3_20_{$i}_date_status{@}=={@}NEVER_REQUIRED"), "q3_20_{$i}_date_group");
                $this->form->addElement('static', null, " $this->indent<b> Record answer, then go to question 3-33</b>");
                $this->form->addElement('static', null, "<br/>");
                $this->form->addElement('static', null, "<br/>");
                $this->form->addElement('static', null, "<br/>");


                //q3-21 ***
                $this->form->addElement('static', null, " 3-21-$i) How long had you been pregnant when this pregnancy ended?");
                $this->addNumericElementRD("q3_21weeks_{$i}", $this->indent . "Weeks");
                $this->addNumericElementRD("q3_21months_{$i}", $this->indent . "Months");
                $this->form->addElement('static', null, "<br/>");
                $this->form->addElement('static', null, "<br/>");

                //q3-22
                $this->form->addElement("static", null, "3-22-$i) How many pounds and ounces did [BABY] weigh?");
                $this->addNumericElementRD("q3_22pounds_$i", $this->indent . $this->indent . " Pounds");
                $this->XINRegisterRule("q3_22pounds_$i", array("q3_22pounds_$i{@}=={@}NEVER_REQUIRED"), "q3_22pounds_{$i}_group");
                $this->addNumericElementRD("q3_22ounces_$i", $this->indent . $this->indent . " Ounces");
                $this->XINRegisterRule("q3_22ounces_$i", array("q3_22ounces_$i{@}=={@}NEVER_REQUIRED"), "q3_22ounces_{$i}_group");
                $this->form->addElement("static", null, "$this->indent <b>Record answer, then go to question 3-24</b>");
                $this->form->addElement('static', null, "<br/>");
                $this->form->addElement('static', null, "<br/>");

                //q3-23
                $this->form->addElement("static", null, "3-23-$i) How many pounds and ounces did each baby born from this pregnancy weigh?");

                for ($j=1; $j<6; $j++)
                {
                        $this->form->addElement('static', null, "BABY #{$j}:");
                        $this->addNumericElementRD("q3_23pounds{$j}_{$i}", $this->indent . $this->indent . " Pounds");
                        $this->addNumericElementRD("q3_23ounces{$j}_{$i}", $this->indent . $this->indent . " Ounces");


                        $this->XINRegisterRule("q3_23pounds{$j}_{$i}", array("q3_23pounds{$j}_{$i}{@}=={@}NEVER_REQUIRED"), "q3_23pounds{$j}_{$i}_group");
                        $this->XINRegisterRule("q3_23ounces{$j}_{$i}", array("q3_23ounces{$j}_{$i}{@}=={@}NEVER_REQUIRED"), "q3_23ounces{$j}_{$i}_group");
                }

                $this->form->addElement('static', null, "$this->indent <b>Record answer, then go to question 3-24</b>");
                $this->form->addElement('static', null, "<br/>");
                $this->form->addElement('static', null, "<br/>");


                //q3-24
                $this->form->addElement("select", "q3_24_$i", "3-24-$i) Is [BABY] still living?", $this->yesNo);
                $this->XINRegisterRule("q3_24_$i", array("q3_24_$i{@}=={@}NEVER_REQUIRED"));
                $this->form->addElement('static', null, $this->indent . " If you selected [Yes], go to question 3-30");
                $this->form->addElement('static', null, $this->indent . " If you selected [No], go to question 3-26");
                $this->form->addElement('static', null, $this->indent . " If you selected [Refused] or [Don't Know], skip to question 3-32");
                $this->form->addElement('static', null,"<br/>");
                $this->form->addElement('static', null, "<br/>");


                //q3-25
                $this->form->addElement('static', null, "3-25-$i) Is [BABY] still living?");
                $this->form->addElement('static', null, "<br/>");

                for ($j=1; $j<6; $j++)
                {
                        $this->form->addElement("select", "q3_25_{$j}_{$i}", "$this->indent BABY #{$j}:", $this->yesNo);

                        $this->XINRegisterRule("q3_25_{$j}_{$i}", array("q3_25_{$j}_{$i}{@}=={@}NEVER_REQUIRED"));
                }

                $this->form->addElement('static', null, "");
                $this->form->addElement('static', null, $this->indent . " If you selected [Yes], go to question 3-30");
                $this->form->addElement('static', null, $this->indent . " If you selected [No], go to question 3-27");
                $this->form->addElement('static', null, $this->indent . " If you selected [Refused], [Don't Know], skip to question 3-32");
                $this->form->addElement('static', null, " $this->indent <b>Record answer, then go to question 3-28</b>");
                $this->form->addElement('static', null, "<br/>");
                $this->form->addElement('static', null, "<br/>");


                //q3-26
                $this->addTextAreaElementRD("q3_26_$i", "3-26-$i) What did [BABY] die of?");
                $this->XINRegisterRule("q3_26_$i", array("q3_24_$i{@}=={@}02"), "You must specify", "q3_26_{$i}_group");

                $this->form->addElement('static', null, " $this->indent If you selected [Refused] or [Don't Know], skip to question 3-32");
                $this->form->addElement('static', null, " $this->indent <b>Record answer, then go to question 3-28</b>");
                $this->form->addElement('static', null, "<br/>");
                $this->form->addElement('static', null, "<br/>");

                //q3-27
                $this->form->addElement('static', null, "3-27-$i) What did each [BABY] die of?");
                $this->form->addElement('static', null, "");


                for ($j=1; $j<6; $j++)
                {
                        $this->addTextAreaElementRD("q3_27_specify{$j}_{$i}", $this->indent . "BABY #{$j}");
                        $this->XINRegisterRule("q3_27_specify{$j}_{$i}", array("q3_27_specify{$j}_{$i}{@}=={@}NEVER_REQUIRED"), "q3_27_specify{$j}_{$i}_group");
                }

                $this->form->addElement('static', null, " $this->indent <b>Record answer, then go to question 3-29</b>");
                $this->form->addElement('static', null, "<br/>");
                $this->form->addElement('static', null, "<br/>");


                //q3-28
                $this->form->addElement('static', null, "3-28-$i) How old was [BABY] when he/she died?");
                $this->addNumericElementRD("q3_28_years_$i", $this->indent . $this->indent . " Years");
                $this->XINRegisterRule("q3_28_years_$i", array("q3_24_$i{@}=={@}02"), "You must specify years", "q3_28_years_{$i}_group");
                $this->addNumericElementRD("q3_28_months_$i", $this->indent . $this->indent . " Months");
                $this->XINRegisterRule("q3_28_months_$i", array("q3_24_$i{@}=={@}02"), "You must specify month(s)", "q3_28_months_{$i}_group");
               $this->form->addElement('static', null, $this->indent . "<i>If don't know, ask:</i>");

                $this->addCustomDateElement("q3_28_2date_$i", $this->indent . "What was the date of [BABY]'s death?", $this->dateOptions1960);
		$this->XINRegisterRule("q3_28_2date_{$i}_date", array("q3_28_2date_{$i}_date{@}=={@}NEVER_REQUIRED"));
		$this->XINRegisterRule("q3_28_2date_{$i}_date_status", array("q3_28_2date_{$i}_date_status{@}=={@}NEVER_REQUIRED"));
                $this->form->addElement('static', null, $this->indent . "<b>Record answer, then go to question 3-32</b>");
                $this->form->addElement('static', null, "<br/>");
                $this->form->addElement('static', null, "<br/>");


                //q3-29
                $this->form->addElement('static', null, "3-29-$i) How old was [BABY] when he/she died?");
                $this->form->addElement('static', null, "<br/>");

                for ($j=1; $j<6; $j++)
                {
                        $this->form->addElement('static', null, "BABY #{$j}:");
                        $this->addNumericElementRD("q3_29_years{$j}_{$i}", $this->indent . $this->indent . " Years");
                        $this->addNumericElementRD("q3_29_months{$j}_{$i}", $this->indent . $this->indent . " Months");
                        $this->form->addElement('static', null, $this->indent . "<i>If don't know, ask:</i>");
                        $this->XINRegisterRule("q3_29_years{$j}_{$i}", array("q3_29_years{$j}_{$i}{@}=={@}NEVER_REQUIRED"), "q3_29_years{$j}_{$i}_group");
                        $this->XINRegisterRule("q3_29_months{$j}_{$i}", array("q3_29_months{$j}_{$i}{@}=={@}NEVER_REQUIRED"), "q3_29_months{$j}_{$i}");
                        $this->addCustomDateElement("q3_29_d{$j}_{$i}", $this->indent . " What was the date of [BABY]'s death?", $this->dateOptions1960);
                        $this->XINRegisterRule("q3_29_d{$j}_{$i}_date", array("q3_29_d{$j}_{$i}_date{@}=={@}NEVER_REQUIRED"), "q3_29_d{$j}_{$i}_date_group");
                        $this->XINRegisterRule("q3_29_d{$j}_{$i}_date_status", array("q3_29_d{$j}_{$i}_date_status{@}=={@}NEVER_REQUIRED"), "q3_29_d{$j}_{$i}_date_group");
                        $this->form->addElement('static', null, "<br/>");
                }

                $this->form->addElement('static', null, "<br/>");


                //q3-30
                $this->form->addElement("select", "q3_30_$i", "3-30-$i)  Did you ever breastfeed or pump breast milk to feed [BABY]?", $this->yesNo);
                $this->XINRegisterRule("q3_30_$i", array("q3_30_$i{@}=={@}NEVER_REQUIRED"));
                $this->form->addElement('static', null, $this->indent . " If you selected [Yes], go to question 3-31");
                $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 3-32");
                $this->form->addElement('static', null,"<br/>");
                $this->form->addElement('static', null, "<br/>");

                //q3-31
                $this->form->addElement("static", null, "3-31-$i) How long did you breastfeed [BABY]?");
                $this->addTextElementRD("q3_31_weeks_$i",  $this->indent . "Enter weeks:");
                $this->addTextElementRD("q3_31_months_$i", $this->indent . "or months:");
                $this->XINRegisterRule("q3_31_weeks_$i", array("q3_30_$i{@}=={@}01_yes", "q3_31_months_$i{@}=={@}", "q3_31_months_{$i}_status{@}=={@}"), "You must specify weeks or months", "q3_31_weeks_{$i}_group");
                $this->XINRegisterRule("q3_31_months_$i", array("q3_30_$i{@}=={@}01_yes", "q3_31_weeks_$i{@}=={@}", "q3_31_weeks_{$i}_status{@}=={@}"), "You must specify weeks or months", "q3_31_months_{$i}_group");
                $this->form->addElement('static', null, "<br/>");
                $this->form->addElement('static', null, "<br/>");


                //q3-32
                $this->form->addElement('static', null, "3-32-$i) Have you ever received a diagnosis from a health care provider that your child/any of your children from this pregnancy had or has...");
                $this->form->addElement('static', null, "<br/>");
                $list1 = array(NULL=>"", "01" => "01 Asperger's Syndrome", "02" => "02 Attention Deficit Hyperactivity Disorder (ADHD) or ADD", "03" => "03  Autism", "04" => "04 Behavioral problem (SPECIFY) (for each pregnancy that it applies to)add line JH", "05" => "05 Bipolar disorder", "06" => "06 Birth Defects (SPECIFY) (for each pregnancy that it applies to) add line JH", "07" => "07 Cerebral palsy", "08" => "08 Childhood Disintegrative Disorder", "09" => "09 Childhood onset schizophrenia", "10" => "10 Developmental delay", "11" => "11 Down Syndrome", "12" => "12 Fragile X Syndrome", "13" => "13 Hearing problems", "14" => "14 Learning disabilities", "15" => "15 Intellectual disability or mental retardation", "16 Movement or coordination problems", "17 Neurofibromatosis", "18" => "18 Obsessive compulsive disorder", "19 Other developmental problem (SPECIFY) add line JH", "20" => "20 Pervasive Developmental Disorder not otherwise specified", "21" => "21 Reactive attachment disorder of infancy or early childhood", "22" => "22 Reading difficulty", "23" => "23 Rett's Syndrome", "24 Seizure disorder or Epilepsy", "25 Self-injuring behavior", "26 Sensory integration disorder", "27 Sleep disorder", "28 Speech delays", "29 Tourette's Disorder or tic disorder", "30 Tuberous sclerosis", "31 Vision problems that cannot be corrected with glasses or contact lenses", "88_other"=>"88 Other", "97 Not applicable (SKIP)", "98" => "98 Refused", "99" => "99 Do not know", "00 None", "not_answered"=>"Not Answered");


                for ($j=1; $j<6; $j++)
                {
                        $this->form->addElement("select", "q3_32_{$j}_{$i}",  "$this->indent BABY #{$j} (select all that apply):", $list1, "multiple size = '5'");
                        $this->addTextAreaElementRD("q3_32_other{$j}_{$i}", $this->indent . $this->indent . "  If you selected [88 Other], please specify:");
                        $this->form->addElement('static', null, "<br/>");
                        $this->XINRegisterRule("q3_32_other{$j}_{$i}", array("q3_32_{$j}_{$i}{@}=={@}88_other"), "You must specify other", "q3_32_other{$j}_{$i}_group");
                        $this->XINRegisterRule("q3_32_{$j}_{$i}", array("q3_32_{$j}_{$i}{@}=={@}NEVER_REQUIRED"));
                }

                $this->form->addElement('static', null, "<br/>");
                $this->form->addElement('header', null, $this->indent . "<b>If more than one pregnancy, continue with pregnancy insert form(s) as needed for next pregnancy(s) ending with the pregnancy that gave rise to the baby sib.</b>");
                $this->form->addElement('static', null, "<br/>");
                $this->form->addElement('static', null, "<br/>");

/*
                $this->form->addElement('static', null, "<br/>");
                $this->form->addElement('header', null, $this->indent . "<b>If more than one pregnancy, continue with pregnancy insert form(s) as needed for next pregnancy(s) ending with the pregnancy that gave rise to the baby sib.</b>");
           //   $this->form->addElement('header', null, "<b>Insert completed forms behind this page.</b>");
                $this->form->addElement('static', null, "<br/>");


                //q3-33
                $this->form->addElement("select", "q3_33_$i", "3-33-$i) We are also interested in any reproductive hormonal medications you might have taken <u>during your lifetime</u> for any reason other than to prevent pregnancy or to help you become pregnant. Did a doctor or other medical provider ever prescribe reproductive hormonal medications? ",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
                $this->form->addElement('static', null, $this->indent . " If you selected [No], [Refused] or [Don't Know] skip to question 4a-1");
                $this->form->addElement('static', null, "<br/>");


                //q3-34
                $this->form->addElement("select", "q3_34_$i", "3-34-$i) What was the reason that the hormonal medication was prescribed?",  array(NULL=>"", "01" => "01 To regulate your cycle", "02" => "02 To jump-start puberty", "03" => "03  Growth regulation", "04" => "04 Acne", "05" => "05 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
                $this->XINRegisterRule("q3_34_$i", array("q3_33_$i{@}=={@}01_yes"), "You must specify a reason");
                $this->form->addElement('static', null, "<br/>");
                $this->form->addElement('header', null, "<b>END Section 3");
                $this->form->addElement('static', null, "<br/>");
                $this->form->addElement('static', null, "<br/>");
*/		

       	} // end function _createPages() =====================================================


	function rulesPage1 ($fields)
        {

		
                function multSelect($fields, $question1)
                {
                        return ($fields[$question1] == array(0=>null) || empty($fields[$question1]));
                }


                function answer8899 ($fields, $question)
                {
                        return ($fields[$question] == "88_Refused" || $fields[$question] == "99_Do_not_know");
                }

			
		function dateEmpty($fields, $question)
		{
			return (empty($fields[$question]['Y']) || empty($fields[$question]['M']) || empty($fields[$question]['d']) || empty($fields[$question]));
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

	
                $errors = array();

                $liveBirths = 0;

		
                //results from q3_6
                if ($fields["q3_6_$j"] == "01")
                        $liveBirths = 1;


                //results from q3_7
                else
                {
                        for ($i=1; $i<6; $i++)
                        {
                                if ($fields["q3_7_{$i}_{$j}"] == "01")
                                        $liveBirths++;
                        }
                }



                //for q3_8
                if (empty($fields["q3_8_$j"]) && ($liveBirths > 1))
                        $errors["q3_8_$j"] = "Required if more than 1 live birth";


                //for q3_10
                if (empty($fields["q3_10_$j"]) && (($liveBirths >= 1) || answer8899($fields, "q3_6_$j") || (answer8899($fields, "q3_7_1_$j") && answer8899($fields, "q3_7_2_$j"))))
                        $errors["q3_10_$j"] = "You must specify";


//              if (empty($fields["q3_12"]) && (($liveBirths < 1) || !answer8899($fields, "q3_6") || (!answer8899($fields, "q3_7_1") && !answer8899($fields, "q3_7_2"))))
                //for q3_12
                if (empty($fields["q3_12_$j"]) && $liveBirths<1)
                        $errors["q3_12_$j"] = "You must specify";


                //for q3_14 and q3_15
                if (empty($fields["q3_14_$j"]) && ($liveBirths==1) && (empty($fields["q3_14_{$j}_status"])))
                {
                        $errors["q3_14_{$j}_group"] = "You must specify a name";
                }
                if (empty($fields["q3_15_name1_$j"]) && ($liveBirths>1) && (empty($fields["q3_15_name1_{$j}_status"])))
                {
                      //  print "this is working..but the error message isn't";
                        $errors["q3_15_name1_{$j}_group"] = "You must specify name";
                }

                if (empty($fields["q3_15_name2_$j"]) && ($liveBirths>1) && (empty($fields["q3_15_name2_{$j}_status"])))
                {
                        $errors["q3_15_name2_{$j}_group"] = "You must specify name";
                }


                //for q3_16 and q3_17
                if (empty($fields["q3_16_$j"]) && ($liveBirths == 1))
                        $errors["q3_16_$j"] = "You must specify a gender";
                if (empty($fields["q3_17_1_$j"]) && ($liveBirths > 1))
                        $errors["q3_17_1_$j"] = "You must specify a gender";
                if (empty($fields["q3_17_2_$j"]) && ($liveBirths > 1))
                        $errors["q3_17_2_$j"] = "You must specify a gender";


                //for q3_18 and q3_19

		if (dateEmpty($fields, "q3_18_{$j}_date") && empty($fields["q3_18_{$j}_date_status"]) && ($liveBirths == 1))
                        $errors["q3_18_{$j}_date_group"] = "You must specify a birth date";
                if (dateEmpty($fields, "q3_19_1_{$j}_date") && empty($fields["q3_19_1_{$j}_date_status"]) && ($liveBirths > 1))
                        $errors["q3_19_1_{$j}_date_group"] = "You must specify a birth date";
                if (dateEmpty($fields, "q3_19_2_{$j}_date") && empty($fields["q3_19_2_{$j}_date_status"]) && ($liveBirths > 1))
                        $errors["q3_19_2_{$j}_date_group"] = "You must specify a birth date";


                //for q3_20
                if (dateEmpty($fields, "q3_20_{$j}_date") && empty($fields["q3_20_{$j}_date_status"]) && ($liveBirths < 1))
                        $errors["q3_20_{$j}_date_group"] = "You must specify";


                //UNSURE ABOUT q3_21

                //for q3_22
                if (empty($fields["q3_22pounds_$j"]) && ($liveBirths == 1) && empty($fields["q3_22pounds_{$j}_status"]))
                        $errors["q3_22pounds_{$j}_group"] = "You must specify pounds or select from the drop-down";
                if (empty($fields["q3_22ounces_$j"]) && ($liveBirths == 1) && empty($fields["q3_22ounces_{$j}_status"]))
                        $errors["q3_22ounces_{$j}_group"] = "You must specify ounces or select from the drop-down";


                //for q3_23
                if (empty($fields["q3_23pounds1_$j"]) && ($liveBirths > 1) && empty($fields["q3_23pounds1_{$j}_status"]))
                        $errors["q3_23pounds1_{$j}_group"] = "You must specify pounds";
                if (empty($fields["q3_23ounces1_$j"]) && ($liveBirths > 1) && empty($fields["q3_23ounces1_{$j}_status"]))
                        $errors["q3_23ounces1_{$j}_group"] = "You must specify ounces";
                if (empty($fields["q3_23pounds2_$j"]) && ($liveBirths > 1) && empty($fields["q3_23pounds2_{$j}_status"]))
                        $errors["q3_23pounds2_{$j}_group"] = "You must specify pounds";
                if (empty($fields["q3_23ounces2_$j"]) && ($liveBirths > 1) && empty($fields["q3_23ounces2_{$j}_status"]))
                        $errors["q3_23ounces2_{$j}_group"] = "You must specify ounces";


                //for q3_24
                if (empty($fields["q3_24_$j"]) && ($liveBirths == 1))
                        $errors["q3_24_$j"] = "You must specify";


                //for q3_25
                if (empty($fields["q3_25_1_$j"]) && ($liveBirths > 1))
                        $errors["q3_25_1_$j"] = "You must specify";
                if (empty($fields["q3_25_2_$j"]) && ($liveBirths > 1))
                        $errors["q3_25_2_$j"] = "You must specify";


                //for q3_27
//              if (empty($fields["q3_27_specify$i"]))
//              {
                        for ($i=1; $i<6; $i++)
                        {
                                if($fields["q3_25_{$i}_{$j}"] == "02" && $liveBirths>1)
                                {
                                        if (empty($fields["q3_27_specify{$i}_{$j}"]) && empty($fields["q3_27_specify{$i}_{$j}_status"]))
                                                $errors["q3_27_specify{$i}_{$j}_group"] = "You must specify";
                                }
                        }



               //for q3_28 
               if (dateEmpty($fields, "q3_28_2date_{$j}_date") && empty($fields["q3_28_2date_{$j}_date_status"]) && $fields["q3_24_{$j}"] == "02")
                        $errors["q3_28_2date_{$j}_date_group"] = "You must specify";



                //for q3_29
                for ($i=1; $i<6; $i++)
                {
                        if($fields["q3_25_{$i}_{$j}"] == "02")
                        {
                                if (empty($fields["q3_29_years{$i}_{$j}"]) && empty($fields["q3_29_years{$i}_{$j}_status"]))
                                        $errors["q3_29_years{$i}_{$j}_group"] = "You must specify";
                                if (empty($fields["q3_29_months{$i}_{$j}"]) && empty($fields["q3_29_months{$i}_{$j}_status"]))
                                        $errors["q3_29_months{$i}_{$j}_group"] = "You must specify";
                                if (dateEmpty($fields, "q3_29_d{$i}_{$j}_date") && empty($fields["q3_29_d{$i}_{$j}_date_status"]))
                                {
                                        $errors["q3_29_d{$i}_{$j}_date_group"] = "You must specify";
                                }
                        }
                }


                //for q3_30
                if ($fields["q3_24_$j"] == "01_yes" && (empty($fields["q3_30_$j"])))
                        $errors["q3_30_$j"] = "You must specify";
                else
                {
                        for ($i=1; $i<6; $i++)
                        {
                                if ($fields["q3_25_{$i}_{$j}"] == "01_yes" && (empty($fields["q3_30_$j"])))
                                {
                                        $errors["q3_30_$j"] = "You must specify";
                                        break;
                                }
                        }
                }
                //for q3_32
//              if (empty($fields["q3_32"]) && $liveBirths >= 1)
//                      $errors["q3_32"] = "You must specify";

                if (multSelect($fields, "q3_32_1_$j") && $liveBirths == 1)
                        $errors["q3_32_1_$j"] = "Required if 01 live birth";

                if ($liveBirths > 1)
                {
                        if (multSelect($fields, "q3_32_1_$j"))
                                $errors["q3_32_1_$j"] = "Required if >01 live births";

                        if (multSelect($fields, "q3_32_2_$j"))
                                $errors["q3_32_2_$j"] = "Required if >01 live births";
                }

                return $errors;
        }



} //end EARLI Maternal Interview S3 Inserts  =================================================

?>
