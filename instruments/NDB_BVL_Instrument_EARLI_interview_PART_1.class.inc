<?php

require_once 'HTML/QuickForm.php';
require_once 'HTML/QuickForm/Renderer/Array.php';
require_once("RequiredIfGroup.inc");
require_once('RequiredIf.inc');
require_once('NDB_BVL_Instrument_EARLI_interview.class.inc');

class NDB_BVL_Instrument_EARLI_interview_PART_1 extends NDB_BVL_Instrument_EARLI_interview {
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
        $this->testName = "EARLI_interview_PART_1";           // test_names.Test_name
        $this->table = 'EARLI_interview_PART_1';              // name of table containing data keyed by commentID
        $this->commentID = $commentID;

        $db =& Database::singleton();
        $sessionid = $this->getSessionID();
        $subprojectid = $db->selectOne("SELECT SubprojectID FROM session WHERE ID='$sessionid'");
        if ($subprojectid == '3')
            $this->_requiredElements = array('interview_time','q1_2','q2_1','q2_21','q3_3_0');
        else
            $this->_requiredElements = array('interview_time','q1_2','q2_1','q2_21','q3_3_0','q4a_1','q4_31','q4_54','q4_73');


        //The array of dates/timestamps to convert to database dates/timestamps
        $this->dateTimeFields=array("interview_date", "q1_1", "q1_16", "q2_39_date_1", "q2_39_date_2", "q3_18_0", "q3_19_1_0", "q3_19_2_0", "q3_19_3_0", "q3_19_4_0", "q3_19_5_0", "q3_20_0", "q3_28_2date_0", "q3_29_d1_0", "q3_29_d2_0", "q3_29_d3_0", "q3_29_d4_0", "q3_29_d5_0", "q4a_2", "q4_41_date", "q4_44_date");

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

        $ages = array_combine(range(5,70), range(5,70));
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
       
       /*Commenting out, this will be inherited from base class
        $this->_doubleDataEntryDiffIgnoreColumns = array('CommentID', 'UserID', 'Testdate', 
                                                          'Window_Difference', 'Candidate_Age',
                                                          'Data_entry_completion_status',
                                                          'mother_id_status'
                                                          );*/
        // setup the form
        $this->_setupForm();

        $this->localDefaults = array();

        $this->_selectMultipleElements = array();


        // From Mr. David Brownlee:
        //The array of selects with multiple answers allowed
        //Any HTML_Quickform multiple selects must be listed here
        //Usually this appears at the beginning of the file in the setup() function

        $this->_selectMultipleElements = array_merge($this->_selectMultipleElements, array("q3_32_1_0","q3_32_2_0","q3_32_3_0","q3_32_4_0", "q3_32_5_0", "q4_10_p1", "q4_10_p2", "q4_10_p3", "q4_10_p4", "q4_10_p5", "q4_13_m1", "q4_13_m2", "q4_13_m3", "q4_13_m4", "q4_13_m5", "q4_20_m", "q4_22", "q4_24", "q4_28", "q4_32", "q4_35", "q4_50", "q4_52", "q4_57", "q4_60", "q4_63", "q4_66", "q4_67", "q4_68_select_1", "q4_68_select_2", "q4_68_select_3", "q4_71_select_1", "q4_71_select_2", "q4_71_select_3", "q4_76_m_1", "q4_76_m_2", "q4_76_m_3", "q4_76_m1", "q4_76_m2", "q4_76_m3", "q4_79", "q4_92", "q4_95_month_1", "q4_95_month_2", "q4_95_month_3", "q4_98_1_month", "q4_98_2_month", "q4_98_3_month", "q4_98_4_month", "q4_98_5_month", "q4_98_6_month", "q4_98_7_month", "q4_98_8_month"));


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
        $this->form->addElement('header', 'instrument_title', "EARLI Maternal Interview Sections 1-4");

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
        
        $this->form->addElement('static',null,'<br>');
        $this->form->addElement("textarea", "other_comments", "Comments about Validity:", array('cols'=>25, 'rows'=>4));
        $this->XINRegisterRule("other_comments", array("{other_comments}{@}=={@}NEVER_REQUIRED"));

    } //end function _main()



    function _page1(){   // ========================================================


        $this->form->addElement('header', null, "Section 1. DEMOGRAPHIC INFORMATION");
        $this->form->addElement('static', null, "<br/><br/><b><i>I would like to begin by confirming your birthday.</i></b>");
        $this->form->addElement('static', null, "<br/>");

        //q1-1
        $this->addCustomDateElement('q1_1', "1-1) What is your date of birth?", $this->dateOptionsOld);
        $this->form->addElement('static', null, "<br/>");

        //q1-2
        $this->form->addElement("select", "q1_2", "1-2) How old are you today? (years)" , $this->ageOptions );

        $this->form->addElement('static', null, "<br/><br/>");
        $this->form->addElement('static', null, "<b><i>Now I'd like to ask about your background.</i></b>");
        $this->form->addElement('static', null, "<br/>");

        //q1-3
        $this->form->addElement('select', 'q1_3', "1-3) Where were you born?", array(NULL=>"","01_US" => "01 U.S.", "02_Outside_US" => "02 Outside U.S.", "88_Refused" => "88 Refused", "99_Do_not_know" => "99 Do not know", "Not_Answered" => "Not Answered"));
        $this->addTextAreaElementRD('q1_3_US_State', $this->indent . "If you selected [U.S.] please specify state and skip to question 1-5:");
        $this->addTextAreaElementRD('q1_3_Outside_US', $this->indent . "If you selected [Outside U.S.] please specify country:");
        $this->form->addElement('static', null, "<br/>");
        $this->XINRegisterRule('q1_3_US_State', array("q1_3{@}=={@}01_US"), "You must specify a U.S. state", "q1_3_US_State_group");
        $this->XINRegisterRule('q1_3_Outside_US', array("q1_3{@}=={@}02_Outside_US"), "You must specify a country", "q1_3_Outside_US_group");


        //q1-4
        //this is a years select menu
        $this->form->addElement("select", "q1_4", "1-4) When did you come to live in the United States?", $this->years1950); 
        $this->form->addElement('static', null, "<br/>");
        $this->XINRegisterRule("q1_4", array("q1_3{@}=={@}02_Outside_US"), "Required if not born in the U.S.");

        //q1-5
        $this->form->addElement("select", "q1_5", "1-5) What language do you speak at home?", array(NULL=>"", "01_English" => "01 English", "02_other" => "02  Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->addTextAreaElementRD('q1_5_Other', $this->indent . "If you selected [Other] please specify:");
        $this->XINRegisterRule('q1_5_Other', array("q1_5{@}=={@}02_other"), "You must specify a language", "q1_5_Other_group");
        $this->form->addElement('static', null, $this->indent . "If you selected [English], skip to question 1-7");
        $this->form->addElement('static', null, "<br/>");

        //q1-6
        $this->form->addElement("select", "q1_6", "1-6) How well do you speak English?", array(NULL=>"", "01" => "01 Very well", "02" => "02  Well", "03" => "03  Not well", "04" => "04 Not at all", "88 Refused", "99" => "99 Do not know", "not_answered"=>"Not Answered"));
        $this->XINRegisterRule("q1_6", array("q1_5{@}=={@}02_other"), "Required if don't speak English at home");
        $this->form->addElement('static', null, "<br/>");

        //q1-7
        $this->form->addElement('select', 'q1_7', "1-7) What is your primary ethnicity?", array(NULL=>"", "01" => "01 Hispanic or Latino", "02" => "02  Not Hispanic or Latino", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [02 Not Hispanic or Latino], skip to question 1-9");
        $this->form->addElement('static', null, "<br/>");

        //q1-8
        $this->form->addElement('select', 'q1_8', "1-8) Of which Hispanic or Spanish group do you consider yourself a member? ", array(NULL=>"", "01" => "01 Mexican, Mexican American, Chicano", "02" => "02  Puerto Rican ", "03" => "03  Cuban", "04" => "04 Other Spanish / Hispanic/Latino ", "88 Refused", "99" => "99 Do not know", "not_answered"=>"Not Answered"));
        $this->XINRegisterRule("q1_8", array("q1_7{@}=={@}01"), "Required if Hispanic or Latino");
        $this->form->addElement('static', null, "<br/>");

        //q1-9
        $this->form->addElement("select", "q1_9", "1-9) What is your race?", array(NULL=>"", "01" => "01 White", "02" => "02 Black, African American", "03" => "03 American Indian / Alaskan Native Asian", "04" => "04 Asian Indian", "05" => "05 Chinese", "06" => "06 Filipino", "07" => "07 Japanese", "08" => "08 Korean", "09" => "09 Vietnamese", "10" => "10 Thai / Cambodian", "11" => "11 Other Asian Native Hawaiian/Pacific Islander",  "12" => "12 Native Hawaiian",  "13" => "13 Guamanian or Chamorro" ,  "14" => "14 Samoan",  "15" => "15 Other Pacific Islander",  "16_other" => "16 Other race", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->addTextAreaElementRD('q1_9_Other', $this->indent . "If you selected [Other race] please specify");
        $this->XINRegisterRule('q1_9_Other', array("q1_9{@}=={@}16_other"), "You must specify a race", "q1_9_Other_group");
        $this->form->addElement('static', null, "<br/>");

        //q1-10
        $this->form->addElement("select", "q1_10", "1-10 What is the highest degree or level of education you have completed?", array(NULL=>"", "01" => "01 No formal schooling completed", "02 " => "02 Nursery school to 4th grade", "03 " => "03 5th grade or 6th grade", "04" => "04 7th grade or 8th grade", "05" => "05 9th grade", "06" => "06 10th grade", "07" => "07 11th grade", "08" => "08 12th grade, no diploma", "09" => "09 High school graduate - high school diploma or equivalent (e.g., GED)", "10" => "10 Some college credit, but less than 1 year", "11" => "11 One or more years of college, no degree", "12" => "12 Technical college / vocational school", "13" => "13 Associate degree (e.g., AA, AS)", "14" => "14 Bachelor's degree (e.g., BA, AB, BS)", "15" => "15 Master's degree (e.g., MA, MS, MEng, Med, MSW, MBA)", "16" => "16 Professional degree (e.g., MD, DDS, DVM, LLB, JD)", "17" => "17 Doctorate degree (e.g., PhD, EdD)", "88" => "88 Refused", "99" => "99 Do not know", "not_answered"=>"Not Answered"));
        $this->form->addElement('static', null, "<br/>");

        //q1-11
        $this->form->addElement("select", "q1_11", "1-11) In the year you were pregnant with your child with ASD, what was your estimated total household income before taxes? Would you say it was...", array(NULL=>"", "01" => "01 Below $10,000", "02" => "02 $10,000 to $19,999", "03" => "03 $20,000 to $29,999", "04" => "04 $30,000 to $49,000", "05" => "05 $50,000 to $74,999", "06" => "06 $75,000 to $99,999", "07 $100,000 to $199,999", "08 $200,000 or more ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, "<br/>");

        //q1-12
        $this->form->addElement("select", "q1_12", "1-12) At that time, how many people were supported by that income, including both adults and children?" ,array_merge(array(NULL=>""), array_combine(range(0,15), range(0,15)), array("88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered" => "Not Answered")));
        $this->form->addElement('static', null, "<br/>");

        //q1-13
        $this->form->addElement("select", "q1_13", "1-13) What was your estimated total household income for the last 12 months before taxes? Would you say it was...", array(NULL=>"", "01" => "01 less than $10,000", "02 $10,000 to $19,999", "03" => "03 $20,000 to $29,999", "04" => "04 30,000 to $49,000", "05" => "05 $50,000 to $74,999", "06" => "06 $75,000 to $99,999", "07" => "07 100,000 to $199,999", "08" => "08 $200,000 or more ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, "<br/>");

        //q1-14
        $this->form->addElement("select", "q1_14", "1-14) How many people are supported by this income, including both adults and children?", array(NULL=>"", "0","1", "2", "3", "4", "5", "6", "7", "8", "9","10", "11", "12", "13", "14", "15", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, "<br/>");

        //q1-15
        $this->form->addElement("select", "q1_15", "1-15) Are you now married, widowed, divorced, separated, never married, or living with a partner?", array(NULL=>"", "01" => "01 Now married", "02" => "02  Widowed", "03" => "03  Divorced", "04" => "04 Separated", "05" => "05 Never married", "06" => "06 Living with a partner ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

        $this->form->addElement('static', null, "<br/><br/><b><i>The next few questions are about the biological father for last pregnancy (sibling of child with ASD).</i></b>");  
        $this->form->addElement('static', null, "<br/>");

        //q***
        $this->form->addElement("select", "father_known", "***) Is biological father for last pregnancy (sibling of child with ASD) known?", array(NULL=>"", "01_yes" => "01 Yes", "02_no" => "02 No", "not_answered"=>"Not Answered"));
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/><b>If biological father for last pregnancy (sibling of child with ASD) is unknown, skip to Section 2 - Maternal Medical History.");
        $this->form->addElement('static', null, "<br/>");

        //q1-16
        $this->addCustomDateElement("q1_16", "1-16)  What is the biological father's birth date?", $this->dateOptions1940); 
        $this->form->addElement('static', null, "<br/>");
        $this->XINRegisterRule("q1_16_date", array("father_known{@}=={@}01_yes", "q1_16_date_status{@}=={@}"), "Required if biological father of sibling is known", "q1_16_date_group");
        $this->XINRegisterRule("q1_16_date_status", array("father_known{@}=={@}01_yes", "q1_16_date{@}=={@}"), "Required if biological father of sibling is known", "q1_16_date_group");

        //q1-17
        $this->form->addElement("select", "q1_17", "1-17) How old is he today? (years)" , $this->ageOptions);
        $this->XINRegisterRule("q1_17", array("father_known{@}=={@}01_yes"), "Required if biological father of sibling is known");
        $this->form->addElement('static', null, "<br/>");

        //q1-18
        $this->form->addElement('select', 'q1_18', "1-18) Where was he born?", array(NULL=>"", "01_US" => "01 US", "02_outside_US" => "02 Outside US", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->addTextAreaElementRD('q1_18_US_State', $this->indent . "If you selected [U.S.] please specify state and skip to question 1-21:");
        $this->addTextAreaElementRD('q1_18_Outside_US', $this->indent . "If you selected [Outside U.S.] please specify country:");
        ;
        $this->XINRegisterRule("q1_18", array("father_known{@}=={@}01_yes"), "Required if biological father of sibling is known");
        $this->XINRegisterRule('q1_18_US_State', array("q1_18{@}=={@}01_US"), "You must specify a state", "q1_18_US_State_group");
        $this->XINRegisterRule('q1_18_Outside_US', array("q1_18{@}=={@}02_outside_US"), "You must specify a country", "q1_18_Outside_US_group");
        $this->form->addElement('static', null, "<br/>");

        //q1-19
        $this->form->addElement("select", "q1_19", "1-19) When did he come to live in the United States?", $this->years1940); 
        $this->XINRegisterRule("q1_19", array("q1_18{@}=={@}02_outside_US"), "Required if biological father of sibling was born outside the US");
        $this->form->addElement('static', null, "<br/>");


        //q1-20
        $this->form->addElement("select", "q1_20", "1-20) What language does he usually speak at home?", array(NULL=>"", "01_english" => "01 English", "02_other" => "02 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->addTextAreaElementRD('q1_20_Other', $this->indent . "If you selected [Other], please specify:");
        $this->form->addElement('static', null,  $this->indent . "If you selected [English], skip to question 1-22");
        $this->XINRegisterRule("q1_20", array("q1_18{@}=={@}02_outside_US"), "Required if biological father of sibling was born outside the US");
        $this->XINRegisterRule('q1_20_Other', array("q1_20{@}=={@}02_other"), "You must specify a language", "q1_20_Other_group");
        $this->form->addElement('static', null, "<br/>");

        //q1-21
        $this->form->addElement("select", "q1_21", "1-21) How well does he speak English?", array(NULL=>"", "01" => "01 Very well", "02" => "02 Well", "03" => "03  Not well", "04" => "04 Not at all ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q1_21", array("q1_20{@}=={@}02_other"), "Required if biological father of sibling does not usually speak English at home");
        $this->form->addElement('static', null, "<br/>");

        //q1-22
        $this->form->addElement("select", "q1_22", "1-22) What is his primary ethnicity?", array(NULL=>"", "01" => "01 Hispanic or Latino", "02" => "02 Not Hispanic or Latino", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null,  $this->indent . "If you selected [Not Hispanic or Latino], skip to question 1-24");
        $this->XINRegisterRule("q1_22", array("father_known{@}=={@}01_yes"), "Required if biological father of sibling is known");
        $this->form->addElement('static', null, "<br/>");

        //q1-23
        $this->form->addElement("select", "q1_23", "1-23) Of which Hispanic or Spanish group does he consider himself a member?", array(NULL=>"", "01" => "01 Mexican, Mexican American, Chicano", "02" => "02 Puerto Rican", "03" => "03  Cuban", "04" => "04 Other Spanish / Hispanic/Latino ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q1_23", array("q1_22{@}=={@}01"), "Required if biological father of sibling is Hispanic or Latino");
        $this->form->addElement('static', null, "<br/>");

        //q1-24
        $this->form->addElement("select", "q1_24", "1-24) What is his race?", array(NULL=>"", "01" => "01 White", "02" => "02 Black, African American", "03" => "03 American Indian / Alaskan Native", "04" => "04 Asian Indian", "05" => "05 Chinese", "06" => "06 Filipino", "07 Japanese", "08" => "08 Korean", "09" => "09 Vietnamese", "10" => "10 Thai / Cambodian", "11" => "11 Other Asian", "12" => "12 Native Hawaiian", "13" => "13 Guamanian or Chamorro", "14" => "14 Samoan", "15" => "15 Other Pacific Islander", "16"=>"16 Other race (specify): ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->addTextAreaElementRD('q1_24_Other', $this->indent . "If you selected [Other], please specify:");
        $this->XINRegisterRule("q1_24", array("father_known{@}=={@}01_yes"), "Required if biological father of sibling is known");
        $this->XINRegisterRule('q1_24_Other', array("q1_24{@}=={@}16"), "You must specify a race", "q1_24_Other_group");
        $this->form->addElement('static', null, "<br/>");

        //q1-25
        $this->form->addElement("select", "q1_25", "1-25) What is the highest degree or level of education he has completed?", array(NULL=>"", "01" => "01 No formal schooling completed", "02" => "02 Nursery school to 4th grade", "03" => "03  5th grade or 6th grade", "04" => "04 7th grade or 8th grade", "05" => "05 9th grade", "06" => "06 10th grade", "07 11th grade", "08" => "08 12th grade, no diploma", "09" => "09 High school graduate - high school diploma or equivalent (e.g., GED)", "10" => "10 Some college credit, but less than 1 year", "11" => "11 One or more years of college, no degree", "12" => "12 Technical college / vocational school", "13" => "13 Associate degree (e.g., AA, AS)", "14" => "14 Bachelor's degree (e.g., BA, AB, BS)", "15" => "15 Master's degree (e.g., MA, MS, MEng, Med, MSW, MBA)", "16 Professional degree (e.g., MD, DDS, DVM, LLB, JD)", "17 Doctorate degree (e.g., PhD, EdD) ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q1_25", array("father_known{@}=={@}01_yes"), "Required if biological father of sibling is known");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


    } // end function _page1() =====================================================




    function _page2()   // ========================================================
    {

        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('header', null, "Section 2. MATERNAL MEDICAL HISTORY <br /><br /> PART 1 OF 2");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<b><i>Now I'm going to ask you about <u>your</u> birth.</i></b>");

        //q2-1
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement("select", "q2_1", "2-1) Were you born prematurely, that is more than 3 weeks early?", $this->yesNo);
        $this->form->addElement('static', null,  $this->indent . "If you selected [Yes], go to question 2-2");
        $this->form->addElement('static', null,  $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 2-3");
        $this->form->addElement('static', null, "<br/>");

        //q2-2
        $this->form->addElement("select", "q2_2", "2-2) How many weeks early were you born?", array(NULL=>"", "3", "4", "5", "6", "7", "8", "9","10", "11", "12", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q2_2", array("q2_1{@}=={@}01_yes"), "Required if born more than 3 weeks early");
        $this->form->addElement('static', null, "<br/>");

        //q2-3
        $this->form->addElement("select", "q2_3", "2-3) What was your birth weight?", array(NULL=>"", "01_grams" => "01 Grams", "02_pounds" => "02 Pounds/Ounces", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->addNumericElementRD('q2_3_grams', $this->indent . "If you selected [Grams] please specify the weight (in grams):");
        $this->form->addElement('static', null, $this->indent . "If you selected [Pounds/Ounces] please specify the weight (in pounds and ounces):");
        $this->addNumericElementRD('q2_3_p', $this->indent . $this->indent . "Pounds:");
        $this->addNumericElementRD('q2_3_o', $this->indent . $this->indent . "Ounces:");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, $this->indent . "If you selected [Grams], [Pounds/Ounces] or [Refused] skip to question 2-5");
        $this->form->addElement('static', null, $this->indent . "If you selected [Don't Know] go to question 2-4");
        $this->XINRegisterRule('q2_3_grams', array("q2_3{@}=={@}01_grams"), "You must specify weight in grams", "q2_3_grams_group");
        $this->XINRegisterRule('q2_3_p', array("q2_3{@}=={@}02_pounds"), "You must specify weight in pounds and ounces", "q2_3_p_group");
        $this->XINRegisterRule('q2_3_o', array("q2_3{@}=={@}02_pounds"), "You must specify weight in pounds and ounces", "q2_3_o_group");		

        //****************************************************************************Weight (idea/code taken from Angela's code - Med-Pscyh-Data_Extraction)
/*
        $measurement2 = "Weight";
        $this->form->addElement('static', null, "<b>$measurement2 Measurement <BR></b>");
        $this->form->addElement('static', null, $noted_message_units_weight);


        $this->form->addElement('select',"{$field}_measurement_weight_units_stat", "$this->indent $measurement2 Units", array(null=>"", "grams"=>"grams","ounces"=>"ounces", "not_answered"=>"Not Answered"));
        $this->XINRegisterRule("{$field}_measurement_weight_units_stat", array("{$prevField}_chart{@}!={@}no_more_chart_data", "{$prevField}_chart{@}!={@}"), "These fields are required unless not answered is selected");

        //Add text boxes
        $this->addTextAreaElementRD("{$field}_measurement_weight_$units_weight[0]", "$this->double_indent $units_weight[0]");
        $this->addTextAreaElementRD("{$field}_measurement_weight2_$units_weight[1]", "$this->double_indent $units_weight[1]");


        $this->XINRegisterRule("{$field}_measurement_weight_$units_weight[0]", array("{$field}_measurement_weight_units_stat{@}=={@}grams", "{$prevField}_chart{@}!={@}no_more_chart_data"), "Please enter grams");
        $this->XINRegisterRule("{$field}_measurement_weight2_$units_weight[1]", array("{$field}_measurement_weight_units_stat{@}=={@}ounces", "{$prevField}_chart{@}!={@}no_more_chart_data"), "Please enter ounces");
         */

            // necessary?
/*
        $this->addTextAreaElementRD("{$field}_weight_percentage", "$this->indent Percentile");

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
         */

            $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


        //****************************************************************************end


        //q2-4
        $this->form->addElement("select", "q2_4", "2-4) Was it less than 5 pounds, 8 ounces (2500 grams) or 5 pounds, 8 ounces (2500 grams) or more?", array(NULL=>"", "01" => "01 Less than 5 pounds, 8 ounces (2500 g)", "02" => "02 5 pounds, 8 ounces (2500 g) or more ", "88 Refused", "99" => "99 Do not know", "not_answered"=>"Not Answered") );
        $this->XINRegisterRule("q2_4", array("q2_3{@}=={@}99_Do_not_know"), "Required if do not know exact weight");

        //q2-6
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement("select", "q2_5", "2-5) Were you a twin or triplet?", array(NULL=>"", "01_no" => "01 No, singleton", "02_twin" => "02 Yes, twin", "03_triplet" => "03  Yes, triplet", "04_other" => "04 Yes, other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->addTextAreaElementRD('q2_5_text', $this->indent . "If you selected [04 Yes, other], please specify:");
        $this->XINRegisterRule('q2_5_text', array("q2_5{@}=={@}04_other"), "You must specify other", "q2_5_text_group");

        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<b><i>These next questions are about your health before your last pregnancy (with sibling of child with ASD).</i></b>");
        $this->form->addElement('static', null, "<br/>");

        //q2-6
        $this->form->addElement("select", "q2_6", "2-6) Before your pregnancy with [SIBLING], were you ever told by a doctor that you had diabetes, including gestational diabetes that happens only while you're pregnant?", array(NULL=>"", "01_yes" => "01 Yes", "02_no" => "02 No", "88_refused"=>"88 Refused", "99" => "99 Do not know", "not_answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [Yes], go to question 2-7");
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 2-13");

        //q2-7
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement("select", "q2_7", "2-7) What type of diabetes did you have? Was it... [read list]", array(NULL=>"", "01" => "01 Gestational diabetes", "02" => "02 Insulin-dependent diabetes, also called Type I or Juvenile Onset", "03" => "03  Non-insulin dependent diabetes, also called Type II or Adult Onset ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q2_7", array("q2_6{@}=={@}01_yes"), "Required if had diabetes before pregnancy");
        $this->form->addElement('static', null, "<br/>");

        //q2-8
        $this->form->addElement("select", "q2_8", "2-8) When were you first diagnosed with diabetes?", $this->dateAge);
        $this->XINRegisterRule("q2_8", array("q2_6{@}=={@}01_yes"), "Required if had diabetes before pregnancy");


        $group[] =&$this->form->createElement("static", "month_names_header");
        $group[] =&$this->form->createElement("static", "year_header");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addGroup($group, "q2_8_headers", "", $this->_GUIDelimiter, false);
        unset($group);


        $group[] = &$this->form->createElement('select', "q2_8_month", null, $this->months);
        $group[] = &$this->form->createElement('select', "q2_8_year", null, $this->years1950);
        $this->form->addGroup($group, "q2_8_date", "<br />" . $this->indent . "If you selected [01 Specify Date], please specify the date:", $this->_GUIDelimiter, false);
        unset($group);
        $this->form->addElement("select", "q2_8_age", $this->indent . "If you selected [02 Age], please specify the age (years):" , $this->ageOptions);
        $this->XINRegisterRule('q2_8_month', array("q2_8{@}=={@}01_date"), "You must specify a date", "q2_8_date");	
        $this->XINRegisterRule('q2_8_year', array("q2_8{@}=={@}01_date"), "You must specify a date", "q2_8_date");	
        $this->XINRegisterRule('q2_8_age', array("q2_8{@}=={@}02_age"), "You must specify an age");	
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");

        //q2-9
        $this->form->addElement("select", "q2_9", "2-9) Did you ever take oral medications or remedies for your diabetes?", $this->yesNo);
        $this->XINRegisterRule("q2_9", array("q2_6{@}=={@}01_yes"), "Required if had diabetes before pregnancy");
        $this->addTextAreaElementRD('q2_9_text', $this->indent . "If you selected [Yes], please specify:");
        $this->XINRegisterRule('q2_9_text', array("q2_9{@}=={@}01_yes"), "You must specify medication", "q2_9_text_group");
        $this->form->addElement('static', null, "<br/>");

        //q2-10
        $this->form->addElement("select", "q2_10", "2-10) Did you ever take insulin?", $this->yesNo); 
        $this->XINRegisterRule("q2_10", array("q2_6{@}=={@}01_yes"), "Required if had diabetes before pregnancy");
        $this->form->addElement('static', null, $this->indent . "If you selected [Yes], go to question 2-11");
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 2-12");
        $this->form->addElement('static', null, "<br/>");

        //q2-11
        $this->form->addElement("select", "q2_11", "2-11) Have you been taking insulin continuously since that time?", $this->yesNo);
        $this->XINRegisterRule("q2_11", array("q2_6{@}=={@}01_yes"), "Required if had diabetes before pregnancy");
        $this->XINRegisterRule("q2_11", array("q2_10{@}=={@}01_yes"), "Required if taken insulin");
        $this->form->addElement('static', null, "<br/>");

        //q2-12
        $this->form->addElement("select", "q2_12", "2-12) Did you ever take any medications other than insulin for diabetes or its complications?", $this->yesNo); 
        $this->XINRegisterRule("q2_12", array("q2_6{@}=={@}01_yes"), "Required if had diabetes before pregnancy");
        $this->form->addElement('static', null, "<br/>");

        //q2-13
        $this->form->addElement("select", "q2_13", "2-13) Before your pregnancy with [SIBLING], were you ever told by a doctor that you had high blood pressure?", $this->yesNo);
        $this->form->addElement('static', null, $this->indent . "If you selected [Yes], go to question 2-14");
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 2-16");

        //q2-14
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement("select", "q2_14", "2-14) When were you first told by a doctor that you had high blood pressure?", $this->dateAge);

        $group[] =&$this->form->createElement("static", "month_names_header");
        $group[] =&$this->form->createElement("static", "year_header");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addGroup($group, "q2_14_headers", "", $this->_GUIDelimiter, false);
        unset($group);

        $group[] = &$this->form->createElement('select', "q2_14_month", null, $this->months);
        $group[] = &$this->form->createElement('select', "q2_14_year", null, $this->years1950);     
        $this->form->addGroup($group, "q2_14_date", "<br />" . $this->indent . "If you selected [01 Date], please specify the date:", $this->_GUIDelimiter, false);
        unset($group);
        $this->form->addElement("select", "q2_14_age", $this->indent . "If you selected [02 Age], please specify (years):", $this->ageOptions);
        $this->XINRegisterRule("q2_14", array("q2_13{@}=={@}01_yes"), "Required if had high blood pressure before sibling pregnancy");
        $this->XINRegisterRule('q2_14_month', array("q2_14{@}=={@}01_date"), "You must specify a date", "q2_14_date");
        $this->XINRegisterRule('q2_14_year', array("q2_14{@}=={@}01_date"), "You must specify a date", "q2_14_date");
        $this->XINRegisterRule('q2_14_age', array("q2_14{@}=={@}02_age"), "You must specify an age");
        $this->form->addElement('static', null, "<br/>");

        //q2-15
        $this->form->addElement("select", "q2_15", "2-15) Did you ever take oral medications or remedies for your high blood pressure?", $this->yesNo);
        $this->addTextAreaElementRD('q2_15_text', $this->indent . "If you selected [Yes], please specify:");
        $this->XINRegisterRule("q2_15", array("q2_15{@}=={@}01_yes"), "Required if had high blood pressure before sibling pregnancy", "q2_15_text_group");
        $this->XINRegisterRule('q2_15_text', array("q2_15{@}=={@}01_yes"), "You must specify a medication", "q2_15_text_group");
        $this->form->addElement('static', null, "<br/>");

        //q2-16
        $this->form->addElement("select", "q2_16", "2-16) Did you ever have seizures that were not related to fever?", $this->yesNo);
        $this->form->addElement('static', null, $this->indent . "If you selected [Yes], go to question 2-17");
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 2-18");
        $this->form->addElement('static', null, "<br/>");

        //q2-17
        $this->form->addElement("select", "q2_17", "2-17) When did these seizures start?", $this->dateAge);

        $group[] =&$this->form->createElement("static", "month_names_header");
        $group[] =&$this->form->createElement("static", "year_header");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addGroup($group, "q2_17_headers", "", $this->_GUIDelimiter, false);
        unset($group);

        $group[] = &$this->form->createElement('select', "q2_17_month", null, $this->months);
        $group[] = &$this->form->createElement('select', "q2_17_year", null, $this->years1950); 
        $this->form->addGroup($group, "q2_17_date", $this->indent . "If you selected [01 Date], please specify the date:", $this->_GUIDelimiter, false);
        unset($group);
        $this->form->addElement("select", "q2_17_age", $this->indent . "If you selected [02 Age], please specify (years):", $this->ageOptions);
        $this->XINRegisterRule("q2_17", array("q2_16{@}=={@}01_yes"), "Required if had seizures not related to fever");
        $this->XINRegisterRule('q2_17_month', array("q2_17{@}=={@}01_date"), "You must specify a date", "q2_17_date");
        $this->XINRegisterRule('q2_17_year', array("q2_17{@}=={@}01_date"), "You must specify a date", "q2_17_date");
        $this->XINRegisterRule('q2_17_age', array("q2_17{@}=={@}02_age"), "You must specify an age");
        $this->form->addElement('static', null, "<br/>");

        //q2-17a
        $this->form->addElement("select", "q2_17_a", "2-17-a) When was the most recent episode?", $this->dateAge);
        $this->XINRegisterRule('q2_17_a', array("q2_16{@}=={@}01_yes"), "Required if had seizures");

        $group[] =&$this->form->createElement("static", "month_names_header");
        $group[] =&$this->form->createElement("static", "year_header");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addGroup($group, "q2_17a_headers", "", $this->_GUIDelimiter, false);
        unset($group);

        $group[] = &$this->form->createElement('select', "q2_17a_month", null, $this->months);
        $group[] = &$this->form->createElement('select', "q2_17a_year", null, $this->years1950); 
        $this->form->addGroup($group, "q2_17a_date", "<br />" . $this->indent . "If you selected [01 Date], please specify the date:", $this->_GUIDelimiter, false);
        unset($group);
        $this->form->addElement("select", "q2_17a_age", $this->indent . "If you selected [02 Age], please specify (years):", $this->ageOptions);
        $this->XINRegisterRule('q2_17a_month', array("q2_17_a{@}=={@}01_date"), "You must specify a date", "q2_17a_date");
        $this->XINRegisterRule('q2_17a_year', array("q2_17_a{@}=={@}01_date"), "You must specify a date", "q2_17a_date");
        $this->XINRegisterRule('q2_17a_age', array("q2_17_a{@}=={@}02_age"), "You must specify an age");
        $this->form->addElement('static', null, "<br/>");

        //q2-18
        $this->form->addElement("select", "q2_18", "2-18) Before your pregnancy with [SIBLING], were you ever told by a doctor that you had epilepsy?", $this->yesNo);
        $this->form->addElement('static', null, $this->indent . "If you selected [Yes], go to question 2-19");
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 2-21");
        $this->form->addElement('static', null, "<br/>");

        //q2-19
        $this->form->addElement("select", "q2_19", "2-19) When were you first told by a doctor that you had epilepsy?", $this->dateAge);

        $group[] =&$this->form->createElement("static", "month_names_header");
        $group[] =&$this->form->createElement("static", "year_header");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addGroup($group, "q2_19_headers", "", $this->_GUIDelimiter, false);
        unset($group);

        $group[] = &$this->form->createElement('select', "q2_19_month", null, $this->months);
        $group[] = &$this->form->createElement('select', "q2_19_year", null, $this->years1950);
        $this->form->addGroup($group, "q2_19_date", "<br />" . $this->indent . "If you selected [01 Date], please specify the date:", $this->_GUIDelimiter, false);
        unset($group);
        $this->form->addElement("select", "q2_19_age", $this->indent . "If you selected [02 Age], please specify (years):", $this->ageOptions);
        $this->XINRegisterRule("q2_19", array("q2_18{@}=={@}01_yes"), "Required if had epilepsy before sibling pregnancy");
        $this->XINRegisterRule('q2_19_month', array("q2_19{@}=={@}01_date"), "You must specify a date", "q2_19_date");
        $this->XINRegisterRule('q2_19_year', array("q2_19{@}=={@}01_date"), "You must specify a date", "q2_19_date");
        $this->XINRegisterRule('q2_19_age', array("q2_19{@}=={@}02_age"), "You must specify an age");
        $this->form->addElement('static', null, "<br/>");

        //q2-20
        $this->form->addElement("select", "q2_20", "2-20) Did you take any medications or remedies for epilepsy or seizures?", $this->yesNo);
        $this->XINRegisterRule('q2_20', array("q2_18{@}=={@}01_yes"), "Required if had epilepsy");
        $this->addTextAreaElementRD('q2_20_text', $this->indent . "If you selected [Yes], please specify:");
        $this->XINRegisterRule('q2_20_text', array("q2_20{@}=={@}01_yes"), "You must specify a medication", "q2_20_text_group");
        $this->form->addElement('static', null, "<br/>");

    }// end function _page2() =====================================================




    function _page3(){   // ========================================================


        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('header', null, "Section 2. MATERNAL MEDICAL HISTORY <br /><br /> PART 2 OF 2");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


        //q2-21
        $this->form->addElement("select", "q2_21", "2-21) Before your pregnancy with [SIBLING], were you ever told by a doctor that you had a neurological disease such as migraines, strokes or multiple sclerosis?", array(NULL=>"", "01_yes" => "01 Yes", "02_no" => "02 No", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->addTextAreaElementRD('q2_21_specify', $this->indent . "If you selected [Yes], please specify:");
        $this->XINRegisterRule("q2_21_specify", array("q2_21{@}=={@}01_yes"), "You must specify", "q2_21_specify_group");
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 2-23");
        $this->form->addElement('static', null, "<br/>");


        //q2-22
        $this->form->addElement("select", "q2_22", "2-22) When were you first told by a doctor that you had [CONDITION]?", $this->dateAge); 

        $group[] =&$this->form->createElement("static", "month_names_header");
        $group[] =&$this->form->createElement("static", "year_header");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addGroup($group, "interview_start_time_headers", "", $this->_GUIDelimiter, false);
        unset($group);

        $group[] = &$this->form->createElement('select', "q2_22_month", null, $this->months);
        $group[] = &$this->form->createElement('select', "q2_22_year", null, $this->years1950);   
        $this->form->addGroup($group, "q2_22_date", "<br />" . $this->indent . "If you selected [01 Date], please specify the date:", $this->_GUIDelimiter, false);
        unset($group);
        $this->form->addElement("select", "q2_22_age", $this->indent . "If you selected [02 Age], please specify (years):", $this->ageOptions);
        $this->XINRegisterRule("q2_22", array("q2_21{@}=={@}01_yes"), "Required if had neurological disease before sibling pregnancy");
        $this->XINRegisterRule('q2_22_month', array("q2_22{@}=={@}01_date"), "You must specify month <b>and</b> year", "q2_22_date");
        $this->XINRegisterRule('q2_22_year', array("q2_22{@}=={@}01_date"), "You must specify month <b>and</b> year", "q2_22_date");
        $this->XINRegisterRule('q2_22_age', array("q2_22{@}=={@}02_age"), "You must specify an age");
        $this->form->addElement('static', null, "<br/>");


        //q2-23
        $this->form->addElement("select", "q2_23", "2-23) Before your pregnancy with [SIBLING], were you ever told by a doctor that you had any autoimmune condition such as hypothyroidism or hyperthyroidism, rheumatoid arthritis, or lupus (SLE)?", $this->yesNo);      
        $this->addTextAreaElementRD('q2_23_text', $this->indent . "If you selected [Yes], please specify:");
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 2-25");
        $this->XINRegisterRule('q2_23_text', array("q2_23{@}=={@}01_yes"), "You must specify a condition", "q2_23_text_group");
        $this->form->addElement('static', null, "<br/>");


        //q2-24
        $this->form->addElement("select", "q2_24", "2-24) When were you first told by a doctor that you had [CONDITION]?", $this->dateAge); 

        $group[] =&$this->form->createElement("static", "month_names_header");
        $group[] =&$this->form->createElement("static", "year_header");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addGroup($group, "interview_start_time_headers", "", $this->_GUIDelimiter, false);
        unset($group);

        $group[] = &$this->form->createElement('select', "q2_24_month", null, $this->months);
        $group[] = &$this->form->createElement('select', "q2_24_year", null, $this->years1950);
        $this->form->addGroup($group, "q2_24_date", "<br />" . $this->indent . "If you selected [01 Date], please specify the date:", $this->_GUIDelimiter, false);
        unset($group);
        $this->form->addElement("select", "q2_24_age", $this->indent .  "If you selected [02 Age], please specify (years):", $this->ageOptions);
        $this->XINRegisterRule("q2_24", array("q2_23{@}=={@}01_yes"), "Required if had neurological disease before sibling pregnancy");
        $this->XINRegisterRule('q2_24_month', array("q2_24{@}=={@}01_date"), "You must specify month <b>and</b> year", "q2_24_date");
        $this->XINRegisterRule('q2_24_year', array("q2_24{@}=={@}01_date"), "You must specify month <b>and</b> year", "q2_24_date");
        $this->XINRegisterRule('q2_24_age', array("q2_24{@}=={@}02_age"), "You must specify an age");
        $this->form->addElement('static', null, "<br/>");

        //q2-25
        $this->form->addElement("select", "q2_25", "2-25) Before your pregnancy with [SIBLING], were you ever told by a doctor that you had asthma or allergies?", $this->yesNo); 
        $this->addTextAreaElementRD('q2_25_text', $this->indent . "If you selected [Yes], please specify:");
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 2-27");
        $this->XINRegisterRule('q2_25_text', array("q2_25{@}=={@}01_yes"), "You must specify condition", "q2_25_text_group");
        $this->form->addElement('static', null, "<br/>");


        //q2-26
        $this->form->addElement("select", "q2_26", "2-26) When were you first told by a doctor that you had [CONDITION]?", $this->dateAge); 

        $group[] =&$this->form->createElement("static", "month_names_header");
        $group[] =&$this->form->createElement("static", "year_header");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addGroup($group, "interview_start_time_headers", "", $this->_GUIDelimiter, false);
        unset($group);

        $group[] = &$this->form->createElement('select', "q2_26_month", null, $this->months);
        $group[] = &$this->form->createElement('select', "q2_26_year", null, $this->years1950);
        $this->form->addGroup($group, "q2_26_date", "<br />" . $this->indent . "If you selected [01 Specify Date], please specify the date:", $this->_GUIDelimiter, false);
        unset($group);
        $this->form->addElement("select", "q2_26_age", $this->indent . "If you selected [02 Age], please specify (years):", $this->ageOptions);
        $this->XINRegisterRule("q2_26", array("q2_25{@}=={@}01_yes"), "Required if had asthma or allergies before sibling pregnancy");
        $this->XINRegisterRule('q2_26_month', array("q2_26{@}=={@}01_date"), "You must specify month <b>and</b> year", "q2_26_date");
        $this->XINRegisterRule('q2_26_year', array("q2_26{@}=={@}01_date"), "You must specify month <b>and</b> year", "q2_26_date");
        $this->XINRegisterRule('q2_26_age', array("q2_26{@}=={@}02_age"), "You must specify an age");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


        //q2-27
        $this->form->addElement('select', "q2_27", "2-27) Before your pregnancy with [SIBLING], were you ever told by a doctor that you had polycystic ovary syndrome (PCOS)?", $this->yesNo);
        $this->form->addElement('static', null, $this->indent . "If you selected [Yes], go to question 2-28");
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 2-30");
        $this->form->addElement('static', null, "<br/>");

        //q2-28
        $this->form->addElement("select", "q2_28", "2-28) When were you first told by a doctor that you had PCOS?", $this->dateAge); 

        $group[] =&$this->form->createElement("static", "month_names_header");
        $group[] =&$this->form->createElement("static", "year_header");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addGroup($group, "interview_start_time_headers", "", $this->_GUIDelimiter, false);
        unset($group);

        $group[] = &$this->form->createElement('select', "q2_28_month", null, $this->months);
        $group[] = &$this->form->createElement('select', "q2_28_year", null, $this->years1950);   
        $this->form->addGroup($group, "q2_28_date", "<br />". $this->indent . "If you selected [01 Date], please specify the date:", $this->_GUIDelimiter, false);
        unset($group);
        $this->form->addElement("select", "q2_28_age", $this->indent . "If you selected [02 Age], please specify (years):", $this->ageOptions);
        $this->XINRegisterRule("q2_28", array("q2_27{@}=={@}01_yes"), "Required if had polycystic ovary syndrome (PCOS) before sibling pregnancy");
        //fix group rules
        $this->XINRegisterRule('q2_28_month', array("q2_28{@}=={@}01_date"), "You must specify month <b>and</b> year", "q2_28_date");
        $this->XINRegisterRule('q2_28_year', array("q2_28{@}=={@}01_date"), "You must specify month <b>and</b> year", "q2_28_date");
        $this->XINRegisterRule('q2_28_age', array("q2_28{@}=={@}02_age"), "You must specify an age");
        $this->form->addElement('static', null, "<br/>");

        //q2-29
        $this->form->addElement("select", "q2_29", "2-29) Did you take any medications or remedies for PCOS?", $this->yesNo);
        $this->addTextAreaElementRD('q2_29_text', $this->indent . "If you selected [Yes], please specify:");
        $this->XINRegisterRule("q2_29", array("q2_27{@}=={@}01_yes"), "Required if had polycystic ovary syndrome (PCOS) before sibling pregnancy");
        $this->XINRegisterRule('q2_29_text', array("q2_29{@}=={@}01_yes"), "You must specify medications/remedies", "q2_29_text_group");
        $this->form->addElement('static', null, "<br/>");

        //q2-30
        $this->form->addElement("static", null, "2-30) Have you ever been diagnosed by a medical provider as having [CONDITION]?");
        $this->form->addElement('static', null, "<br/>");

        for ($i=1; $i<5; $i++)
        {

            $this->form->addElement('select', "q2_30_{$i}", $this->indent . "[CONDITION] #{$i}:", array(NULL=>"", "01" => "01 Tubal factor infertility", "02" => "02 Other ovulatory dysfunction (besides PCOS)", "03" => "03  Diminished ovarian reserve", "04" => "04 Endometriosis", "05" => "05 Uterine factor infertility", "07" => "07 Infertility unexplained cause", "08_other" => "08 Other infertility problems", "09" => "09 None of the above ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

            $this->addTextAreaElementRD("q2_30_other_{$i}", $this->indent . "If you selected [Other infertility problems], please specify:");
            $this->XINRegisterRule("q2_30_other_{$i}", array("q2_30_{$i}{@}=={@}08_other"), "You must specify other infertility problems", "q2_30_other_{$i}_group");

            if ($i>1)
                $this->XINRegisterRule("q2_30_{$i}", array("q2_30_{$i}{@}=={@}NEVER_REQUIRED"));

            $this->form->addElement('static', null, "<br/>");
        }


        //q2-31
        $this->form->addElement("select", "q2_31", "2-31) Before this pregnancy, did you have any other major illnesses that we haven't already asked about?", array(NULL=>"", "01_yes" => "01 Yes", "02_no" => "02 No", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [Yes], go to question 2-32");
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 2-33");
        $this->form->addElement('static', null, "<br/>");

        //q2-32
        $this->form->addElement("select", "q2_32", "2-32) What was the illness? Did you take any medication for it?", array(NULL=>"", "01_illness" => "01 Illness", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

        for ($i=1; $i <=3; $i++)
        {	
            $this->addTextAreaElementRD("q2_32_illness{$i}", $this->indent . "If you selected [01 Illness], specify illness {$i}:");
            $this->form->addElement('select', "q2_32_age{$i}", $this->indent . $this->indent . "Age at illness:", $this->ageOptions);
            $this->form->addElement('select', "q2_32_meds{$i}", $this->indent . $this->indent . "Meds taken (y/n):", $this->yesNo);

            if ($i>=2)
            {
                $this->XINRegisterRule("q2_32_illness{$i}", array("q2_32_illness{$i}{@}=={@}NEVER_REQUIRED"), "q2_32_illness{$i}_group");
                $this->XINRegisterRule("q2_32_age{$i}", array("q2_32_age{$i}{@}=={@}NEVER_REQUIRED"));
                $this->XINRegisterRule("q2_32_meds{$i}", array("q2_32_meds{$i}{@}=={@}NEVER_REQUIRED"));
            }
        }

        $this->XINRegisterRule("q2_32", array("q2_31{@}=={@}01_yes"), "Required if had other major illnesses before pregnancy");
        $this->XINRegisterRule('q2_32_illness1', array("q2_32{@}=={@}01_illness"), "You must specify an illness", "q2_32_illness1_group");
        $this->XINRegisterRule('q2_32_age1', array("q2_32{@}=={@}01_illness"), "You must specify an age");
        $this->XINRegisterRule('q2_32_meds1', array("q2_32{@}=={@}01_illness"), "You must specify if meds were taken");
        $this->form->addElement('static', null, "<br/>");

        //q2-33
        $this->form->addElement("select", "q2_33", "2-33) How would you rate your general health as a child up to the age of 16 years? Would you say it was...? [read choices]", array(NULL=>"", "01" => "01 Excellent", "02" => "02 Very good", "03" => "03  Good", "04" => "04 Fair", "05" => "05 Poor ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, "<br/>");

        //q2-34
        $this->form->addElement("select", "q2_34", "2-34) Were you ever tested for anti-sperm antibody?", array(NULL=>"", "01_yes" => "01 Yes", "02_no" => "02 No", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [Yes], go to question 2-35");
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 2-36");
        $this->form->addElement('static', null, "<br/>");

        //q2-35
        $this->form->addElement("select", "q2_35", "2-35) What were the results of your test?", array(NULL=>"", "01" => "01 Positive", "02" => "02 Negative ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q2_35", array("q2_34{@}=={@}01_yes"), "Required if tested for anti-sperm antibody");
        $this->form->addElement('static', null, "<br/>");

        //q2-36
        $this->form->addElement("select", "q2_36", "2-36) Did you have any surgical procedures to open or rejoin your fallopian tubes, to treat fibroids, or to remove endometriosis?", array(NULL=>"", "01_yes" => "01 Yes", "02_no" => "02 No", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [Yes], go to question 2-37");
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 2-38");
        $this->form->addElement('static', null, "<br/>");

        //q2-37
        $this->form->addElement("select", "q2_37", "2-37) What was the procedure?", array(NULL=>"", "01" => "01 Open fallopian tubes", "02" => "02 Rejoin fallopian tubes", "03" => "03  Treatment of uterine fibroids", "04" => "04 Removal of endometriosis", "05_other" => "05 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [Other], please specify:");
        $this->XINRegisterRule("q2_37", array("q2_36{@}=={@}01_yes"), "Required if had surgical procedures");
        $this->form->addElement('static', null, "<br/>");
        $this->addTextAreaElementRD('q2_37_text_01', $this->indent . $this->indent . "PROCEDURE #1:");
        $this->addTextAreaElementRD('q2_37_text_02', $this->indent . $this->indent . "PROCEDURE #2:");
        $this->addTextAreaElementRD('q2_37_text_03', $this->indent . $this->indent . "PROCEDURE #3:");
        $this->XINRegisterRule('q2_37_text_01', array("q2_37{@}=={@}05_other"), "You must specify a procedure", "q2_37_text_01_group");
        $this->XINRegisterRule('q2_37_text_02', array("q2_37_text_02{@}=={@}NEVER_REQUIRED"), "q2_37_text_02_group");
        $this->XINRegisterRule('q2_37_text_03', array("q2_37_text_03{@}=={@}NEVER_REQUIRED"), "q2_37_text_03_group");

        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<b><i>Now I am going to ask you about dental work you may have had.<br/></i></b>");
        $this->form->addElement('static', null, "<br/>");

        //q2-38
        $this->form->addElement("select", "q2_38", "2-38) Have you ever had any amalgam (silver-colored) fillings in your mouth?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to next section");
        $this->form->addElement('static', null, "<br/>");

        //q2-39
        $this->form->addElement("select", "q2_39", "2-39) When were these fillings put into place and how many did you have?", $this->dateAge);
        $this->addCustomDateElement('q2_39_date_1', 'If you selected [01 Date], please specify date 1:', $this->dateOptions1950);
        //		$this->XINRegisterRule("q2_39_date_1_date", array("q2_38{@}=={@}01_yes"), "Required if had amalgam fillings", "q2_39_date_1_date_group"); 
        //		$this->XINRegisterRule("q2_39_date_1_date_status", array("q2_38{@}=={@}01_yes"), "Required if had amalgam fillings", "q2_39_date_1_date_group"); 
        $this->XINRegisterRule('q2_39_date_1_date', array("q2_39{@}=={@}01_date", "q2_39_date_1_date_status{@}=={@}"), "You must specify a date", "q2_39_date_1_date_group");
        $this->XINRegisterRule('q2_39_date_1_date_status', array("q2_39{@}=={@}01_date", "q2_39_date_1_date{@}=={@}"), "You must specify a date", "q2_39_date_1_date_group");
        $this->form->addElement("select", "q2_39_num_1", $this->indent ."and the number of fillings:", array(NULL=>"",  "0","1", "2", "3", "4", "5", "6", "7", "8", "9","10", "11", "12", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));


        $this->addCustomDateElement('q2_39_date_2', 'If you selected [01 Date], please specify date 2 (if applicable):', $this->dateOptions1950);
        $this->XINRegisterRule('q2_39_date_2_date', array("q2_39_date_2_date{@}=={@}NEVER_REQUIRED"), "q2_39_date_2_date_group");
        $this->XINRegisterRule('q2_39_date_2_date_status', array("q2_39_date_2_date_status{@}=={@}NEVER_REQUIRED"), "q2_39_date_2_date_group");
        //	$this->XINRegisterRule("q2_39_date_2_date", array("q2_38{@}=={@}01_yes"), "Required if had amalgam fillings", "q2_39_date_2_date_group"); 
        //	$this->XINRegisterRule("q2_39_date_2_date_status", array("q2_38{@}=={@}01_yes"), "Required if had amalgam fillings", "q2_39_date_2_date_group"); 
        $this->form->addElement("select", "q2_39_num_2", $this->indent . "and the number of fillings:", array(NULL=>"",  "0","1", "2", "3", "4", "5", "6", "7", "8", "9","10", "11", "12", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, "<br/>");


        $this->form->addElement("select", "q2_39_age_1", "If you selected [02 Age], please specify age 1:" , $this->ageOptions );
        $this->form->addElement("select", "q2_39_num_3", $this->indent . "and the number of fillings:", array(NULL=>"",  "0","1", "2", "3", "4", "5", "6", "7", "8", "9","10", "11", "12", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));


        $this->form->addElement("select", "q2_39_age_2", "If you selected [02 Age], please specify the age 2 (if applicable):", $this->ageOptions);
        $this->form->addElement("select", "q2_39_num_4", $this->indent . "and the number of fillings:", array(NULL=>"",  "0","1", "2", "3", "4", "5", "6", "7", "8", "9","10", "11", "12", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

        $this->XINRegisterRule('q2_39', array("q2_38{@}=={@}01_yes"), "You must specify");
        $this->XINRegisterRule('q2_39_num_1', array("q2_39{@}=={@}01_date"), "You must specify number of fillings");
        $this->XINRegisterRule('q2_39_age_1', array("q2_39{@}=={@}02_age"), "You must specify an age");
        $this->XINRegisterRule('q2_39_num_3', array("q2_39{@}=={@}02_age"), "You must specify number of fillings");

        $this->XINRegisterRule('q2_39_num_2', array("q2_39_num_2{@}=={@}NEVER_REQUIRED"));
        $this->XINRegisterRule('q2_39_age_2', array("q2_39_age_2{@}=={@}NEVER_REQUIRED"));
        $this->XINRegisterRule('q2_39_num_4', array("q2_39_num_4{@}=={@}NEVER_REQUIRED"));


        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");

        //q2-40
        $this->form->addElement("select", "q2_40", "2-40) How many amalgam fillings did you have in your mouth at the time you became pregnant with your current pregnancy?", array(NULL=>"","01 None", "02" => "02 1-4", "03" => "03  5-10", "04" => "04 > 10", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule('q2_40', array("q2_38{@}=={@}01_yes"), "Required if had amalgam fillings");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('header', null, "END Section 2");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


    } //end function _page3() =====================================================




    function _page4(){   // ========================================================


        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('header', null, "Section 3. PREGNANCY AND REPRODUCTIVE HISTORY");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<b><i>Now I'm going to ask you some questions about your reproductive and pregnancy experiences.");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


        //Function with rules for the majority of this page
        $this->form->addFormRule(array(&$this,'rulesPage4'));


        //q3-1
        $this->form->addElement("select", "q3_1_0", "3-1) How old (in years) were you when you had your first menstrual period?" ,array(NULL=>"","6", "7", "8", "9","10", "11", "12", "13", "14", "15", "16", "17", "18", "19","88_Refused" => "88 Refused",  "99_Do_not_know" => "99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . " If the age is entered or [Refused], go to question 3-3");
        $this->form->addElement('static', null, $this->indent . " If you selected [Do not know], go to question 3-2");
        $this->form->addElement('static', null, "<br/>");

        //q3-2
        $this->form->addElement("select", "q3_2_0", "3-2)  What grade were you in when you had your first menstrual period?", array(NULL=>"", "1", "2", "3", "4", "5", "6", "7", "8", "9","10", "11", "12", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q3_2_0", array("q3_1_0{@}=={@}99_Do_not_know"), "Required if don't know age");
        $this->form->addElement('static', null, "<br/>");

        //q3-3
        $this->form->addElement("select", "q3_3_0", "3-3)  What was the average or typical number of days of your cycle between the first day of one menstrual period and the first day of the next menstrual period? Please think back to a time when you were not using birth control pills or other hormonal contraceptives.", array(NULL=>"", "21" => "21", "22", "23" => "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "90"=>"90 Irregular period", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, "<br/>");

        //q3-4
        $this->form->addElement("select", "q3_4_0", "3-4) How many times have you been pregnant? Please count all pregnancies, including those that ended in live birth, stillbirth, miscarriage, abortion, or a tubal, ectopic, or molar pregnancy. Include children from other relationships, your pregnancy with [PROBAND] and your last pregnancy with the sibling of the child with ASD.", array(NULL=>"", "1", "2", "3", "4", "5", "6", "7", "8", "9","10", "11", "12",  "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");

        //q3-4
        $this->form->addElement('static', null, "<b><i>The remainder of the questions in Section 3 (Pregnancy and Reproductive History) should be asked for <u>each</u> pregnancy <u> except the pregnancy with the [SIBLING</u>].</i></b>");  
        $this->form->addElement('static', null, "<i>If more than one previous pregnancy, use <b>Pregnancy Insert forms</b> and label as PREGNANCY 2, PREGNANCY 3, PREGNANCY 4, etc.</i>");
        $this->form->addElement('static', null, "<i>All questions pertaining to PREGNANCY 1 should be asked first, then PREGNANCY 2, then PREGNANCY 3, etc.</i>");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<b><i>The next few questions are about your 1st pregnancy only.</i></b>");
        $this->form->addElement('static', null, "<br/>");

        //q3-5
        $this->form->addElement("select", "q3_5_0", "3-5) How many babies were you carrying during your 1st pregnancy?", array(NULL=>"", "1"=>"1 (Single baby)", "2"=>"2 (Twins)", "3"=>"3", "4"=>"4", "5"=>"5", "88_Refused" => "88 Refused", "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . " If you selected [single baby], go to question 3-6");
        $this->form->addElement('static', null, $this->indent . " If you selected [multiple babies],go to question 3-7");
        $this->form->addElement('static', null, "<br/>");

        //q3-6
        $this->form->addElement("select", "q3_6_0", "3-6) Did your 1st pregnancy end with a/an...? ",  array(NULL=>"", "01" => "01 Live birth", "02" => "02 Stillbirth", "03" => "03  Induced abortion", "04" => "04 Miscarriage", "05" => "05 Tubal pregnancy", "06" => "06 Molar pregnancy", "07_other" => "07 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . " If you selected [Live birth], [Refused], or [Don't know], go to question 3-10");
        $this->form->addElement('static', null, $this->indent . " If you selected [Stillbirth], [Induced abortion], [Miscarriage], [Tubal pregnancy], [Molar pregnancy] or, go to question 3-12");
        $this->addTextAreaElementRD('q3_6_text_0', $this->indent . " If you selected [Other], please specify and go to question 3-12.");
        $this->XINRegisterRule("q3_6_0", array("q3_5_0{@}=={@}1"), "Required if carried single baby during 1st pregnancy");
        $this->XINRegisterRule('q3_6_text_0', array("q3_6_0{@}=={@}07_other"), "You must specify other", "q3_6_text_0_group");


        //q3-7
        $this->form->addElement('static', null, "<br/>3-7) For your 1st pregnancy, what was the outcome for each baby? Was it a/an...");
        for ($i = 1; $i <=5; $i++)
        {

            $this->form->addElement("select", "q3_7_{$i}_0", "<br/>$this->indent BABY # {$i}",  array(NULL=>"", "01" => "01 Live birth", "02" => "02 Stillbirth", "03" => "03  Induced abortion", "04" => "04 Miscarriage", "05" => "05 Tubal pregnancy", "06" => "06 Molar pregnancy", "07_other" => "07 Other ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
            if ($i<3)
                $this->XINRegisterRule("q3_7_{$i}_0", array("q3_5_0{@}!={@}1"), "Required if had multiple babies");
            $this->addTextAreaElementRD("q3_7_{$i}_text_0", $this->indent . " If you selected [Other], please specify.");
            $this->XINRegisterRule("q3_7_{$i}_text_0", array("q3_7_{$i}_0{@}=={@}07_other"), "You must specify other", "q3_7_{$i}_text_0_group");
        }

        $this->XINRegisterRule('q3_7_3_0', array("q3_7_3_0{@}=={@}NEVER_REQUIRED"));
        $this->XINRegisterRule('q3_7_4_0', array("q3_7_4_0{@}=={@}NEVER_REQUIRED"));
        $this->XINRegisterRule('q3_7_5_0', array("q3_7_5_0{@}=={@}NEVER_REQUIRED"));

        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, $this->indent . " If [01 Live birth], go to question 3-10");
        $this->form->addElement('static', null, $this->indent . " If [> 01 Live birth], go to question 3-8");
        $this->form->addElement('static', null, $this->indent . " If [other outcome(s)], go to question 3-12");
        $this->form->addElement('static', null, "<br/>");

        //q3-8
        $this->form->addElement("select", "q3_8_0", "3-8) Were the babies identical?",  array(NULL=>"", "01_yes" => "01 Yes", "02_no" => "02 No", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        //Rule is taken care of in rulesPage4 function
        $this->XINRegisterRule("q3_8_0", array("q3_8_0{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement('static', null, $this->indent . " If you selected [Yes], go to question 3-9");
        $this->form->addElement('static', null, $this->indent . " If you selected [No], [Refused] or [Don't Know], skip to question 3-10");
        $this->form->addElement('static', null, "<br/>");


        //3-9
        $this->form->addElement("select", "q3_9_0", "3-9) How do you know they are identical twins?",  array(NULL=>"", "01" => "01 Doctor told you", "02" => "02 Genetic tests", "03" => "03  They are as alike as two peas in a pod", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q3_9_0", array("q3_8_0{@}=={@}01_yes"), "Required if babies identical");
        $this->form->addElement('static', null, "<br/>");

        //q3-10
        $this->form->addElement("select", "q3_10_0", "3-10) Was this pregnancy with [PROBAND]?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

        //Rule is taken care of in rulesPage4 function
        $this->XINRegisterRule("q3_10_0", array("q3_10_0{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement('static', null, $this->indent . " If you selected [Yes], go to question 3-13");
        $this->form->addElement('static', null, $this->indent . " If you selected [No], go to question 3-11");
        $this->form->addElement('static', null, "<br/>");


        //q3-11
        $this->form->addElement("select", "q3_11_0", "3-11) Does the baby from your 1st pregnancy have the same biological father as [PROBAND]?",  array(NULL=>"", "01_yes" => "01 Yes", "02_no" => "02 No", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "<b>Record answer, then go to question 3-14</b>");
        $this->XINRegisterRule("q3_11_0", array("q3_10_0{@}=={@}02"), "Required if not pregnancy with [PROBAND]");
        $this->form->addElement('static', null, "<br/>");


        //q3-12
        $this->form->addElement("select", "q3_12_0", "3-12) Did the [OUTCOME] have the same biological father as [PROBAND]",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        //Rule is taken care of in rulesPage4 function
        $this->XINRegisterRule("q3_12_0", array("q3_12_0{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement('static', null, " $this->indent <b>Record answer, then go to question 3-20</b>");
        $this->form->addElement('static', null, "<br/>");


        //q3-13
        $this->form->addElement("static", null, "3-13)");
        $this->form->addElement('static', null, "$this->indent If you selected [live singleton birth], go to question 3-14");
        $this->form->addElement('static', null, " $this->indent If you selected [live multiple births], go to question 3-15");
        $this->form->addElement('static', null, "<br/>");

        //q3-14
        $this->form->addElement('static', null, "3-14) What is the first name of the baby from your 1st pregnancy?"); 
        $this->addTextAreaElementRD('q3_14_0', $this->indent . "FIRST NAME:");
        $this->form->addElement('static', null, $this->indent . "<b>Record answer, then go to question 3-16 (If Proband, automatic fill)</b>");
        $this->XINRegisterRule("q3_14_0", array("q3_14_0{@}=={@}NEVER_REQUIRED"), "q3_14_0_group");
        $this->form->addElement('static', null, "<br/>");

        //q3-15
        $this->form->addElement('static', null, "3-15) What are the first names of each of the babies born from your 1st pregnancy?"); 


        for ($i=1; $i<6; $i++)
        {
            $this->addTextAreaElementRD("q3_15_name{$i}_0", $this->indent . "BABY #{$i}:");

            //			if ($i>2)
            $this->XINRegisterRule("q3_15_name{$i}_0", array("q3_15_name{$i}_0{@}=={@}NEVER_REQUIRED"), "q3_15_name{$i}_0_group");
            //				$this->XINRegisterRule("q3_15_name{$i}", array("q3_15{@}=={@}00_specify"), "You must specify a name");
        }


        $this->form->addElement('static', null, " $this->indent <b>Record answer, then go to question 3-17</b>");
        $this->form->addElement('static', null, "<br/>");

        //q3-16
        $this->form->addElement("select", "q3_16_0", "3-16) What was the gender of the baby born from your 1st pregnancy? ",  array(NULL=>"", "01" => "01 Boy", "02" => "02 Girl", "88_Refused" => "88 Refused", "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q3_16_0", array("q3_16_0{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement('static', null, " $this->indent <b>Record answer, then go to question 3-18 (If Proband, automatic fill)</b>");
        $this->form->addElement('static', null, "<br/>");

        //q3-17
        $this->form->addElement('static', null, "3-17) What were the genders of the babies born from your 1st pregnancy?");

        for ($i=1; $i<6; $i++)
        {
            $this->form->addElement("select", "q3_17_{$i}_0", "$this->indent BABY #{$i}:",  array(NULL=>"", "01" => "01 Boy", "02" => "02 Girl", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));	

            //			if ($i>2)
            //	$this->XINRegisterRule("q3_17_{$i}", array("q3_17{@}=={@}00_specify"), "You must specify genders");
            //	else
            $this->XINRegisterRule("q3_17_{$i}_0", array("q3_17_{$i}_0{@}=={@}NEVER_REQUIRED"));
        }


        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, " $this->indent<b> Record answer, then go to question 3-19</b>");
        $this->form->addElement('static', null, "<br/>");

        //q3-18
        $this->addCustomDateElement('q3_18_0', $this->indent . "3-18) What is the birth date of the baby from your 1st pregnancy?", $this->dateOptions1960);
        $this->form->addElement('static', null, " $this->indent<b> Record answer, then go to question 3-30</b>");
        $this->XINRegisterRule('q3_18_0_date', array("q3_18_0_date{@}=={@}NEVER_REQUIRED"), "q3_18_0_date_group");
        $this->XINRegisterRule('q3_18_0_date_status', array("q3_18_0_date_status{@}=={@}NEVER_REQUIRED"), "q3_18_0_date_group");
        $this->form->addElement('static', null, " $this->indent <b>If proband pregnancy (YES to 3-10), record on pregnancy calendar as DOPB.</b>");
        $this->form->addElement('static', null, "<br/>");

        //q3-19
        $this->form->addElement("static", null, "3-19) What are the birth dates of each baby born from your 1st pregnancy?");


        for ($i=1; $i<6; $i++)
        {
            $this->addCustomDateElement("q3_19_{$i}_0", $this->indent . "BABY #{$i}:", $this->dateOptions1960);

            //		if ($i>2)
            $this->XINRegisterRule("q3_19_{$i}_0_date", array("q3_19_{$i}_0_date{@}=={@}NEVER_REQUIRED"), "q3_19_{$i}_0_date_group");
            $this->XINRegisterRule("q3_19_{$i}_0_date_status", array("q3_19_{$i}_0_date_status{@}=={@}NEVER_REQUIRED"), "q3_19_{$i}_0_date_group");
        }


        $this->form->addElement('static', null, " $this->indent<b> Record answer, then go to question 3-23</b>");
        $this->form->addElement('static', null, $this->indent . "<b> If proband pregnancy (YES to 3-10), record on pregnancy calendar as DOPB.</b>");
        $this->form->addElement('static', null, "<br/>");

        //q3-20
        $this->addCustomDateElement('q3_20_0', $this->indent . "3-20) On what date did your 1st pregnancy end?", $this->dateOptions1960);
        $this->XINRegisterRule("q3_20_0_date", array("q3_20_0_date{@}=={@}NEVER_REQUIRED"), "q3_20_0_date_group");
        $this->XINRegisterRule("q3_20_0_date_status", array("q3_20_0_date_status{@}=={@}NEVER_REQUIRED"), "q3_20_0_date_group");
        $this->form->addElement('static', null, " $this->indent<b> Record answer, then go to question 3-33</b>");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


        //q3-21 ***
        $this->form->addElement('static', null, " 3-21) How long had you been pregnant when the 1st pregnancy ended?");
        $this->addNumericElementRD('q3_21weeks_0', $this->indent . "Weeks");
        $this->addNumericElementRD('q3_21months_0', $this->indent . "Months");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");
        $this->XINRegisterRule('q3_21weeks_0', array("q3_21weeks_0{@}=={@}NEVER_REQUIRED"), "q3_21weeks_0_group");
        $this->XINRegisterRule('q3_21months_0', array("q3_21months_0{@}=={@}NEVER_REQUIRED"), "q3_21months_0_group");

        //q3-22
        $this->form->addElement("static", null, "3-22) How many pounds and ounces did [BABY] weigh?");
        $this->addNumericElementRD('q3_22pounds_0', $this->indent . $this->indent . " Pounds");
        $this->XINRegisterRule("q3_22pounds_0", array("q3_22pounds_0{@}=={@}NEVER_REQUIRED"), "q3_22pounds_0_group");
        $this->addNumericElementRD('q3_22ounces_0', $this->indent . $this->indent . " Ounces");
        $this->XINRegisterRule("q3_22ounces_0", array("q3_22ounces_0{@}=={@}NEVER_REQUIRED"), "q3_22ounces_0_group");
        $this->form->addElement("static", null, "$this->indent <b>Record answer, then go to question 3-24</b>");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


        //q3-23
        $this->form->addElement("static", null, "3-23) How many pounds and ounces did each baby born from your 1st pregnancy weigh?");

        for ($i=1; $i<6; $i++)
        {
            $this->form->addElement('static', null, "BABY #{$i}:");
            $this->addNumericElementRD("q3_23pounds{$i}_0", $this->indent . $this->indent . " Pounds"); 
            $this->addNumericElementRD("q3_23ounces{$i}_0", $this->indent . $this->indent . " Ounces");


            $this->XINRegisterRule("q3_23pounds{$i}_0", array("q3_23pounds{$i}_0{@}=={@}NEVER_REQUIRED"), "q3_23pounds{$i}_0_group");
            $this->XINRegisterRule("q3_23ounces{$i}_0", array("q3_23ounces{$i}_0{@}=={@}NEVER_REQUIRED"), "q3_23ounces{$i}_0_group");
        }

        $this->form->addElement('static', null, "$this->indent <b>Record answer, then go to question 3-24</b>");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


        //q3-24
        $this->form->addElement("select", "q3_24_0", "3-24) Is [BABY] still living?", $this->yesNo); 
        $this->XINRegisterRule("q3_24_0", array("q3_24_0{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement('static', null, $this->indent . " If you selected [Yes], go to question 3-30");
        $this->form->addElement('static', null, $this->indent . " If you selected [No], go to question 3-26");
        $this->form->addElement('static', null, $this->indent . " If you selected [Refused] or [Don't Know], skip to question 3-32");
        $this->form->addElement('static', null,"<br/>");
        $this->form->addElement('static', null, "<br/>");


        //q3-25	
        $this->form->addElement('static', null, "3-25) Is [BABY] still living?");
        $this->form->addElement('static', null, "<br/>");

        for ($i=1; $i<6; $i++)
        {
            $this->form->addElement("select", "q3_25_{$i}_0", "$this->indent BABY #{$i}:", $this->yesNo);

            $this->XINRegisterRule("q3_25_{$i}_0", array("q3_25_{$i}_0{@}=={@}NEVER_REQUIRED"), "q3_25_{$i}_0_group");
        }


        $this->form->addElement('static', null, "");
        $this->form->addElement('static', null, $this->indent . " If you selected [Yes], go to question 3-30");
        $this->form->addElement('static', null, $this->indent . " If you selected [No], go to question 3-27");
        $this->form->addElement('static', null, $this->indent . " If you selected [Refused], [Don't Know], skip to question 3-32");
        $this->form->addElement('static', null, " $this->indent <b>Record answer, then go to question 3-28</b>");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");

        //q3-26
        $this->addTextAreaElementRD('q3_26_0', "3-26) What did [BABY] die of?");
        $this->XINRegisterRule("q3_26_0", array("q3_24_0{@}=={@}02", "q3_26_0_status{@}=={@}"), "You must specify", "q3_26_0_group");
        $this->form->addElement('static', null, " $this->indent If you selected [Refused] or [Don't Know], skip to question 3-32");
        $this->form->addElement('static', null, " $this->indent <b>Record answer, then go to question 3-28</b>");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");

        //q3-27
        $this->form->addElement('static', null, "3-27) What did each [BABY] die of?"); 
        $this->form->addElement('static', null, "");


        for ($i=1; $i<6; $i++)
        {		
            $this->addTextAreaElementRD("q3_27_specify{$i}_0", $this->indent . "BABY #{$i}");
            $this->XINRegisterRule("q3_27_specify{$i}_0", array("q3_27_specify{$i}_0{@}=={@}NEVER_REQUIRED"), "q3_27_specify{$i}_0_group");

        }

        $this->form->addElement('static', null, " $this->indent <b>Record answer, then go to question 3-29</b>");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


        //q3-28
        $this->form->addElement('static', null, "3-28) How old was [BABY] when he/she died?");
        $this->addNumericElementRD('q3_28_years_0', $this->indent . $this->indent . " Years");
        $this->XINRegisterRule("q3_28_years_0", array("q3_24_0{@}=={@}02"), "You must specify years", "q3_28_years_0_group");
        $this->addNumericElementRD('q3_28_months_0', $this->indent . $this->indent . " Months");
        $this->XINRegisterRule("q3_28_months_0", array("q3_24_0{@}=={@}02"), "You must specify month(s)", "q3_28_months_0_group");

        // SPECIFY ONE OR BOTH???	
        $this->form->addElement('static', null, $this->indent . "<i>If don't know, ask:</i>");
        $this->addCustomDateElement("q3_28_2date_0", $this->indent . "What was the date of [BABY]'s death?", $this->dateOptions1960);
        $this->XINRegisterRule('q3_28_2date_0_date', array("q3_28_2date_0_date{@}=={@}NEVER_REQUIRED"));
        $this->XINRegisterRule('q3_28_2date_0_date_status', array("q3_28_2date_0_date_status{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement('static', null, " $this->indent <b>Record answer, then go to question 3-32</b>");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


        //q3-29
        $this->form->addElement('static', null, "3-29) How old was [BABY] when he/she died?");
        $this->form->addElement('static', null, "<br/>");

        for ($i=1; $i<6; $i++)
        {	
            $this->form->addElement('static', null, "BABY #{$i}:");
            $this->addNumericElementRD("q3_29_years{$i}_0", $this->indent . $this->indent . " Years");
            $this->addNumericElementRD("q3_29_months{$i}_0", $this->indent . $this->indent . " Months");
            $this->form->addElement('static', null, $this->indent . "<i>If don't know, ask:</i>");
            $this->XINRegisterRule("q3_29_years{$i}_0", array("q3_29_years{$i}_0{@}=={@}NEVER_REQUIRED"), "q3_29_years{$i}_0_group");
            $this->XINRegisterRule("q3_29_months{$i}_0", array("q3_29_months{$i}_0{@}=={@}NEVER_REQUIRED"), "q3_29_months{$i}_0_group");
            $this->addCustomDateElement("q3_29_d{$i}_0", $this->indent . " What was the date of [BABY]'s death?", $this->dateOptions1960);
            $this->XINRegisterRule("q3_29_d{$i}_0_date", array("q3_29_d{$i}_0_date{@}=={@}NEVER_REQUIRED"), "q3_29_d{$i}_0_date_group");
            $this->XINRegisterRule("q3_29_d{$i}_0_date_status", array("q3_29_d{$i}_0_date_status{@}=={@}NEVER_REQUIRED"), "q3_29_d{$i}_0_date_group");
            $this->form->addElement('static', null, "<br/>");
        }

        $this->form->addElement('static', null, "<br/>");


        //q3-30
        $this->form->addElement("select", "q3_30_0", "3-30)  Did you ever breastfeed or pump breast milk to feed [BABY]?", $this->yesNo); 
        $this->XINRegisterRule("q3_30_0", array("q3_30_0{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement('static', null, $this->indent . " If you selected [Yes], go to question 3-31");
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 3-32");
        $this->form->addElement('static', null,"<br/>");
        $this->form->addElement('static', null, "<br/>");

        //q3-31
        $this->form->addElement("static", null, "3-31) How long did you breastfeed [BABY]?");
        $this->addTextElementRD("q3_31_weeks_0",  $this->indent . "Enter weeks:");
        $this->addTextElementRD("q3_31_months_0", $this->indent . "or months:");
        $this->XINRegisterRule("q3_31_weeks_0", array("q3_30_0{@}=={@}01_yes", "q3_31_months_0{@}=={@}"), "You must specify weeks or months", "q3_31_weeks_0_group");
        $this->XINRegisterRule("q3_31_months_0", array("q3_30_0{@}=={@}01_yes", "q3_31_weeks_0{@}=={@}"), "You must specify weeks or months", "q3_31_months_0_group");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");

        //q3-32
        $this->form->addElement('static', null, "3-32) Have you ever received a diagnosis from a health care provider that your child/any of your children from your 1st pregnancy had or has...");
        $this->form->addElement('static', null, "<br/>");
        $list1 = array(NULL=>"", "01" => "01 Asperger's Syndrome", "02" => "02 Attention Deficit Hyperactivity Disorder (ADHD) or ADD", "03" => "03  Autism", "04" => "04 Behavioral problem (SPECIFY) (for each pregnancy that it applies to)add line JH", "05" => "05 Bipolar disorder", "06" => "06 Birth Defects (SPECIFY) (for each pregnancy that it applies to) add line JH", "07" => "07 Cerebral palsy", "08" => "08 Childhood Disintegrative Disorder", "09" => "09 Childhood onset schizophrenia", "10" => "10 Developmental delay", "11" => "11 Down Syndrome", "12" => "12 Fragile X Syndrome", "13" => "13 Hearing problems", "14" => "14 Learning disabilities", "15" => "15 Intellectual disability or mental retardation", "16 Movement or coordination problems", "17 Neurofibromatosis", "18" => "18 Obsessive compulsive disorder", "19 Other developmental problem (SPECIFY) add line JH", "20" => "20 Pervasive Developmental Disorder not otherwise specified", "21" => "21 Reactive attachment disorder of infancy or early childhood", "22" => "22 Reading difficulty", "23" => "23 Rett's Syndrome", "24 Seizure disorder or Epilepsy", "25 Self-injuring behavior", "26 Sensory integration disorder", "27 Sleep disorder", "28 Speech delays", "29 Tourette's Disorder or tic disorder", "30 Tuberous sclerosis", "31 Vision problems that cannot be corrected with glasses or contact lenses", "88_other"=>"88 Other", "97 Not applicable (SKIP)", "98" => "98 Refused", "99" => "99 Do not know", "00 None", "not_answered"=>"Not Answered");


        for ($i=1; $i<6; $i++)
        {	
            $this->form->addElement("select", "q3_32_{$i}_0",  "$this->indent BABY #{$i} (select all that apply):", $list1, "multiple size = '5'");
            $this->addTextAreaElementRD("q3_32_other{$i}_0", $this->indent . $this->indent . "  If you selected [88 Other], please specify:");
            $this->form->addElement('static', null, "<br/>");
            $this->XINRegisterRule("q3_32_other{$i}_0", array("q3_32_{$i}_0{@}=={@}88_other"), "You must specify other", "q3_32_other{$i}_0_group");
            $this->XINRegisterRule("q3_32_{$i}_0", array("q3_32_{$i}_0{@}=={@}NEVER_REQUIRED"));
        }


        $this->form->addElement('static', null, "<br/>");
        //		$this->form->addElement('header', null, $this->indent . "<b>If more than one pregnancy, continue with pregnancy insert form(s) as needed for next pregnancy(s) ending with the pregnancy that gave rise to the baby sib.</b>");
        $sessionid = $this->getSession();
        $commentid = $this->getComment($sessionid);
        $url = "main.php?test_name=EARLI_interview_S3_inserts&candID=".$_REQUEST['candID']."&sessionID=".$sessionid."&commentID=".$commentid;                
        $this->form->addElement("link", null, "<b>If more than one pregnancy (your answer was 2 or more for question 3-4):</b>", $url, 'Click here to enter data from the pregnancy insert forms');
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


        //q3-33
        $this->form->addElement("select", "q3_33_0", "3-33) We are also interested in any reproductive hormonal medications you might have taken <u>during your lifetime</u> for any reason other than to prevent pregnancy or to help you become pregnant. Did a doctor or other medical provider ever prescribe reproductive hormonal medications? ",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . " If you selected [No], [Refused] or [Don't Know] skip to question 4a-1");
        $this->form->addElement('static', null, "<br/>");


        //q3-34
        $this->form->addElement("select", "q3_34_0", "3-34) What was the reason that the hormonal medication was prescribed?",  array(NULL=>"", "01" => "01 To regulate your cycle", "02" => "02 To jump-start puberty", "03" => "03  Growth regulation", "04" => "04 Acne", "05" => "05 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q3_34_0", array("q3_33_0{@}=={@}01_yes"), "You must specify a reason");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('header', null, "<b>END Section 3");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


    }




    function rulesPage4 ($fields)
    {

        //print_r($fields);
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


        $errors = array();		

        $liveBirths = 0;

        //results from q3_6	
        if ($fields["q3_6_0"] == "01")
            $liveBirths = 1;

        //results from q3_7
        else
        {
            for ($i=1; $i<6; $i++)
            {
                if ($fields["q3_7_{$i}_0"] == "01")
                    $liveBirths++;
            }
        }


        //for q3_8
        if (empty($fields["q3_8_0"]) && ($liveBirths > 1))
            $errors["q3_8_0"] = "Required if more than 1 live birth";


        //for q3_10
        if (empty($fields["q3_10_0"]) && (($liveBirths >= 1) || answer8899($fields, "q3_6_0") || (answer8899($fields, "q3_7_1_0") && answer8899($fields, "q3_7_2_0"))))
            $errors["q3_10_0"] = "You must specify";


        //for q3_12
        if (empty($fields["q3_12_0"]) && $liveBirths<1)
            $errors["q3_12_0"] = "You must specify";


        //for q3_14 and q3_15
        if (empty($fields["q3_14_0"]) && ($liveBirths==1) && (empty($fields["q3_14_0_status"])))
        {
            $errors["q3_14_0_group"] = "You must specify a name";
        }
        if (empty($fields["q3_15_name1_0"]) && ($liveBirths>1) && (empty($fields["q3_15_name1_0_status"])))
        {
            //print "this is working..but the error message isn't";
            $errors["q3_15_name1_0_group"] = "You must specify name";
        }

        if (empty($fields["q3_15_name2_0"]) && ($liveBirths>1) && (empty($fields["q3_15_name2_0_status"])))
        {
            $errors["q3_15_name2_0_group"] = "You must specify name";
        }

        //for q3_16 and q3_17
        if (empty($fields["q3_16_0"]) && ($liveBirths == 1))
            $errors["q3_16_0"] = "You must specify a gender";
        if (empty($fields["q3_17_1_0"]) && ($liveBirths > 1))
            $errors["q3_17_1_0"] = "You must specify a gender";
        if (empty($fields["q3_17_2_0"]) && ($liveBirths > 1))
            $errors["q3_17_2_0"] = "You must specify a gender";


        //for q3_18 and q3_19	
        if (dateEmpty($fields, "q3_18_0_date") && empty($fields["q3_18_0_date_status"]) && ($liveBirths == 1))
            $errors["q3_18_0_date_group"] = "You must specify a birth date";
        if (dateEmpty($fields, "q3_19_1_0_date") && empty($fields["q3_19_1_0_date_status"]) && ($liveBirths > 1))
            $errors["q3_19_1_0_date_group"] = "You must specify a birth date";
        if (dateEmpty($fields, "q3_19_2_0_date") && empty($fields["q3_19_2_0_date_status"]) && ($liveBirths > 1))
            $errors["q3_19_2_0_date_group"] = "You must specify a birth date";

        //for q3_20
        if (dateEmpty($fields, "q3_20_0_date") && empty($fields["q3_20_0_date_status"]) && ($liveBirths < 1))
            $errors["q3_20_0_date_group"] = "You must specify";			

        //UNSURE ABOUT q3_21

        //for q3_22
        if (empty($fields["q3_22pounds_0"]) && ($liveBirths == 1) && empty($fields["q3_22pounds_0_status"]))
            $errors["q3_22pounds_0_group"] = "You must specify pounds or select from the drop-down";
        if (empty($fields["q3_22ounces_0"]) && ($liveBirths == 1) && empty($fields["q3_22ounces_0_status"]))
            $errors["q3_22ounces_0_group"] = "You must specify ounces or select from the drop-down";


        //for q3_23
        if (empty($fields["q3_23pounds1_0"]) && ($liveBirths > 1) && empty($fields["q3_23pounds1_0_status"]))
            $errors["q3_23pounds1_0_group"] = "You must specify pounds";
        if (empty($fields["q3_23ounces1_0"]) && ($liveBirths > 1) && empty($fields["q3_23ounces1_0_status"]))
            $errors["q3_23ounces1_0_group"] = "You must specify ounces";
        if (empty($fields["q3_23pounds2_0"]) && ($liveBirths > 1) && empty($fields["q3_23pounds2_0_status"]))
            $errors["q3_23pounds2_0_group"] = "You must specify pounds";
        if (empty($fields["q3_23ounces2_0"]) && ($liveBirths > 1) && empty($fields["q3_23ounces2_0_status"]))
            $errors["q3_23ounces2_0_group"] = "You must specify ounces";


        //for q3_24
        if (empty($fields["q3_24_0"]) && ($liveBirths == 1))
            $errors["q3_24_0"] = "You must specify";


        //for q3_25
        if (empty($fields["q3_25_1_0"]) && ($liveBirths > 1)) 
            $errors["q3_25_1_0"] = "You must specify";
        if (empty($fields["q3_25_2_0"]) && ($liveBirths > 1))
            $errors["q3_25_2_0"] = "You must specify";


        //for q3_27
        for ($i=1; $i<6; $i++)
        {
            if($fields["q3_25_{$i}_0"] == "02" && $liveBirths>1)
            {
                if (empty($fields["q3_27_specify{$i}_0"]) && empty($fields["q3_27_specify{$i}_0_status"])) 
                    $errors["q3_27_specify{$i}_0_group"] = "You must specify";
            }
        }


        //for q3_28
        if (dateEmpty($fields, "q3_28_2date_0_date") && empty($fields["q3_28_2date_0_date_status"]) && $fields["q3_24_0"] == "02")
            $errors["q3_28_2date_0_date_group"] = "You must specify";


        //for q3_29
        for ($i=1; $i<6; $i++)
        {
            if($fields["q3_25_{$i}_0"] == "02")
            {
                if (empty($fields["q3_29_years{$i}_0"]) && empty($fields["q3_29_years{$i}_0_status"])) 
                    $errors["q3_29_years{$i}_0_group"] = "You must specify";
                if (empty($fields["q3_29_months{$i}_0"]) && empty($fields["q3_29_months{$i}_0_status"]))
                    $errors["q3_29_months{$i}_0_group"] = "You must specify";
                if (dateEmpty($fields, "q3_29_d{$i}_0_date") && empty($fields["q3_29_d{$i}_0_date_status"]))
                {
                    $errors["q3_29_d{$i}_0_date_group"] = "You must specify";
                }
            }
        }


        //for q3_30
        if ($fields["q3_24_0"] == "01_yes" && (empty($fields["q3_30_0"])))
            $errors["q3_30_0"] = "You must specify";

        else
        {
            for ($i=1; $i<6; $i++)
            {
                if ($fields["q3_25_{$i}_0"] == "01_yes" && (empty($fields["q3_30_0"])))
                {
                    $errors["q3_30_0"] = "You must specify";
                    break;
                }
            }
        }


        //for q3_32
        //		if (empty($fields["q3_32"]) && $liveBirths >= 1)
        //			$errors["q3_32"] = "You must specify";

        if (multSelect($fields, "q3_32_1_0") && $liveBirths == 1)
            $errors["q3_32_1_0"] = "Required if 01 live birth";

        if ($liveBirths > 1)
        {
            if (multSelect($fields, "q3_32_1_0"))
                $errors["q3_32_1_0"] = "Required if >01 live births";

            if (multSelect($fields, "q3_32_2_0"))
                $errors["q3_32_2_0"] = "Required if >01 live births";
        }
        return $errors;
    }



    function _page5() {


        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('header', null, "Section 4. PROBAND PREGNANCY <br /><br /> (PART 1 OF 4)");
        $this->form->addElement('static', null, "<br/><b><i>Now I have some questions specific to your pregnancy with [PROBAND].</i></b>");
        $this->form->addElement('static', null, "<br/>");

        //function containing more complex rules
        $this->form->addFormRule(array(&$this,'rulesPage5'));


        //q4a-1
        $this->form->addElement("select", "q4a_1", "4a-1. Does your child with ASD and their younger sibling have the same biological father?", $this->yesNo); 
        $this->form->addElement('static', null, $this->indent . "If you selected [Yes], skip to question 4-4");
        $this->form->addElement('static', null, "<br/>");

        //q4a-2
        $this->addCustomDateElement('q4a_2', $this->indent . "4a-2. What is the biological father's birth date?", $this->dateOptions1940);
        $this->XINRegisterRule("q4a_2_date", array("q4a_1{@}!={@}01_yes", "q4a_2_date_status{@}=={@}"), "You must specify or select from the drop-down", "q4a_2_date_group");
        $this->XINRegisterRule('q4a_2_date_status', array("q4a_1{@}!={@}01_yes", "q4a_2_date{@}=={@}"), "You must specify or select from the drop-down", "q4a_2_date_group");
        $this->form->addElement('static', null, "<br/>");

        //q4a-3
        $this->form->addElement('select', "q4a_3", "4a-3. How old is he today? (Years)", $this->ageOptions);
        $this->XINRegisterRule("q4a_3", array("q4a_1{@}!={@}01_yes"), "You must specify");
        $this->form->addElement('static', null, "<br/>");

        //q4a-4
        $this->form->addElement('select', 'q4a_4', "4a-4. Where was he born?", array(NULL=>"","01_US" => "01 U.S.", "02_Outside_US" => "02 Outside U.S.", "88_Refused" => "88 Refused", "99_Do_not_know" => "99 Do not know", "Not_Answered" => "Not Answered"));
        $this->XINRegisterRule("q4a_4", array("q4a_1{@}!={@}01_yes"), "You must specify");
        $this->addTextAreaElementRD('q4a_4_US_State', $this->indent . "If you selected [U.S.], please specify state and skip to question 4a-6:");
        $this->addTextAreaElementRD('q4a_4_Outside_US', $this->indent . "If you selected [Outside U.S.], please specify country:");
        $this->XINRegisterRule('q4a_4_US_State', array("q4a_4{@}=={@}01_US"), "You must specify a U.S. state", "q4a_4_US_State_group");
        $this->XINRegisterRule('q4a_4_Outside_US', array("q4a_4{@}=={@}02_Outside_US"), "You must specify a country", "q4a_4_Outside_US_group");
        $this->form->addElement('static', null, "<br/>");

        //q4a-5
        $this->form->addElement('select', 'q4a_5', "4a-5. When did he come to live in the United States?", $this->years1940); 
        $this->XINRegisterRule("q4a_5", array("q4a_4{@}=={@}02_Outside_US"), "Required if not from U.S.");
        $this->form->addElement('static', null, "<br/>");

        //q4a-6
        $this->form->addElement("select", "q4a_6", "<br/> 4a-6. What language does he usually speak at home?",array(NULL=>"", "01_english" => "01 English", "02_other" => "02 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q4a_6", array("q4a_1{@}!={@}01_yes"), "You must specify");
        $this->addTextAreaElementRD('q4a_6_Other', $this->indent . "If you selected [Other] please specify:");
        $this->form->addElement('static', null, $this->indent . " If you selected [English], skip to question 4a-8");
        $this->XINRegisterRule('q4a_6_Other', array("q4a_6{@}=={@}02_other"), "You must specify other", "q4a_6_Other_group");
        $this->form->addElement('static', null, "<br/>");

        //q4a-7
        $this->form->addElement("select", "q4a_7", "4a-7 How well does he speak English?", array(NULL=>"","01 Very well", "02" => "02 Well", "03" => "03  Not well", "04" => "04 Not at all", "88 Refused", "99" => "99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q4a_7", array("q4a_6{@}=={@}02_other"), "Required if doesn't usually speak English at home");
        $this->form->addElement('static', null, "<br/>");

        //q4a-8
        $this->form->addElement("select", "q4a_8", "4a-8. What is his primary ethnicity?", array(NULL=>"","01_Hispanic/Latino" => "01 Hispanic or Latino", "02" => "02 Not Hispanic or Latino", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q4a_8", array("q4a_1{@}!={@}01_yes"), "You must specify");
        $this->form->addElement('static', null, $this->indent . "If you selected [Not Hispanic or Latino], skip to question 4a-10");
        $this->form->addElement('static', null, "<br/>");

        //q4a-9
        $this->form->addElement("select", "q4a_9", "4a-9. Of which Hispanic or Spanish group does he consider himself a member?", array(NULL=>"","01 Mexican, Mexican American, Chicano", "02" => "02 Puerto Rican ", "03" => "03  Cuban", "04" => "04 Other Spanish/Hispanic/Latino ", "88 Refused", "99" => "99 Do not know", "Not_answered"=>"Not Answered"));
        $this->XINRegisterRule("q4a_9", array("q4a_8{@}=={@}01_Hispanic/Latino"), "Required if Hispanic or Latino");
        $this->form->addElement('static', null, "<br/>");

        //q4a-10
        $this->form->addElement("select", "q4a_10", "4a-10. What is his race?", array(NULL=>"","01 White", "02 Black, African American ", "03" => "03 American Indian / Alaskan Native Asian", "04" => "04 Asian Indian", "05" => "05 Chinese", "06" => "06 Filipino", "07" => "07 Japanese", "08" => "08 Korean", "09" => "09 Vietnamese", " 10 Thai / Cambodian", " 11 Other Asian Native Hawaiian and other Pacific Islander", " 12 Native Hawaiian", " 13 Guamanian or Chamorro" , " 14 Samoan", " 15 Other Pacific Islander", "16_other"=>"16 Other race", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q4a_10", array("q4a_1{@}!={@}01_yes"), "You must specify");
        $this->addTextAreaElementRD('q4a_10_other', $this->indent . "If you selected [Other race], please specify:");
        $this->XINRegisterRule('q4a_10_other', array("q4a_10{@}=={@}16_other"), "You must specify other", "q4a_10_other_group");
        $this->form->addElement('static', null, "<br/>");


        //q4a-11
        $this->form->addElement("select", "q4a_11", "4a-11. What is the highest degree or level of education he has completed?",  array(NULL=>"", "01" => "01 No formal schooling completed", "02" => "02 Nursery school to 4th grade", "03" => "03  5th grade or 6th grade", "04" => "04 7th grade or 8th grade", "05" => "05 9th grade", "06" => "06 10th grade", "07" => "07 11th grade", "08" => "08 12th grade, no diploma", "09" => "09 High school graduate - high school diploma or equivalent (e.g., GED)", "10" => "10 Some college credit, but less than 1 year", "11" => "11 One or more years of college, no degree", "12" => "12 Technical college / vocational school", "13" => "13 Associate degree (e.g., AA, AS)", "14" => "14 Bachelor's degree (e.g., BA, AB, BS)", "15" => "15 Master's degree (e.g., MA, MS, MEng, Med, MSW, MBA)", "16" => "16 Professional degree (e.g., MD, DDS, DVM, LLB, JD)", "17" => "17 Doctorate degree (e.g., PhD, EdD) ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q4a_11", array("q4a_1{@}!={@}01_yes"), "You must specify");
        $this->form->addElement('static', null, "<br/>");

        //q4-4
        $this->form->addElement('static', null, "4-4. How much did you weigh before your pregnancy with [PROBAND] (in lbs)?");
        $this->addNumericElementRD('q4_4', $this->indent . "Enter weight in lbs:");
        $this->form->addElement('static', null, $this->indent . "If you selected [Refused] or [Don't Know] skip to question 4-6");
        $this->form->addElement('static', null, "<br/>");

        //q4-5
        $this->form->addElement('select', 'q4_5', "4-5. How much weight did you gain or lose with your pregnancy with [PROBAND]?",  array(NULL=>"", "01_gain" => "01 Weight gain", "02_loss" => "02 Weight loss", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->addNumericElementRD('q4_5_gain', $this->indent . "If you selected [01 Weight gain], please specify how much (in lbs):");
        $this->addNumericElementRD('q4_5_loss', $this->indent . "If you selected [02 Weight loss], please specify how much (in lbs):");
        $this->form->addElement('static', null, "<br/>");
        $this->XINRegisterRule('q4_5_gain', array("q4_5{@}=={@}01_gain", "q4_4{@}!={@}"), "You must specify weight gain", "q4_5_gain_group");
        $this->XINRegisterRule('q4_5_loss', array("q4_5{@}=={@}02_loss", "q4_4{@}!={@}"), "You must specify weight loss", "q4_5_loss_group");

        //q4-6
        $this->form->addElement('static', null, "4-6. What was your height without shoes?");
        $this->form->addElement("select", "q4_6_f", $this->indent .  "Feet:",  array(NULL=>"",  "1" => "1", "2" => "2", "3" => "3", "4", "5", "6", "7", "88_Refused" => "88 Refused", "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement("select", "q4_6_i", $this->indent .  "Inches:",  array(NULL=>"",  "0", "1" => "1", "2" => "2", "3" => "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "88_Refused" => "88 Refused", "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, "<br/>");

        //q4-7
        $this->form->addElement("static", null, "4-7. How far along were you when you found out you were pregnant with [PROBAND]?"); 
        $this->form->addElement("select", "q4_7_w", $this->indent .  "Weeks:",  array(NULL=>"",  "0", "1" => "1", "2" => "2", "3" => "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18" => "18", "19", "20" => "20", "21" => "21", "22" => "22", "23" => "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "36", "37", "38","88_Refused" => "88 Refused", "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement("select", "q4_7_m", $this->indent .  "Months:",  array(NULL=>"",  "0", "1" => "1", "2" => "2", "3" => "3", "4", "5", "6", "7", "8", "9", "88_Refused" => "88 Refused", "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, "<br/>");

        $this->form->addElement('static', null, $this->indent .  "<b><i>Refer to the Pregnancy Calendar.</i></b>");
        $this->form->addElement('static', null, "<br/>");

        //q4-8
        $this->form->addElement("select", "q4_8", "4-8. Between [-3] and [DOPB], did you use any birth control pills or morning after pills?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 4-11");
        $this->form->addElement('static', null, "<br/>");

        //q4-9
        $this->form->addElement('static', null, "4-9. What was the name of the pills?");
        $this->form->addElement('static', null, "<b><i>May be too difficult to remember. If can't recall, ask to refer to <u>List 2</u> in prep guide and choose from the following list:</i></b>");
        $this->form->addElement('static', null, "<br/>");

        $pillOptions = array(NULL=>"", "01" => "01 Alesse", "02" => "02 Brevicon", "03" => "03  Demulen", "04" => "04 Desogen", "05" => "05 Estrostep", "06" => "06 Levlen", "07" => "07 Levlite", "08" => "08 Levora", "09" => "09 Loestrin", "10" => "10 Lo/Ovral", "11" => "11 Micronor", "12" => "12 Mircette", "13" => "13 Modicon", "14" => "14 Necon", "15" => "15 Nordette", "16" => "16 Norinyl", "17" => "17 Nor-Q.D", "18" => "18 Ortho-Cept", "19 OrthoCyclen", "20" => "20 Ortho-Novum", "21" => "21 Ortho Tri-Cyclen", "22" => "22 Ovcon", "23" => "23 Ovral", "24 Tri-Levlen", "25 Tri-Norinyl", "26 Triphasil", "27 Trivora", "28 Zovia",  "29_other" => "29 Other", "88 Refused", "99" => "99 Do not know", "not_answered"=>"Not Answered");

        for ($i=1; $i<6; $i++)
        {
            $this->form->addElement("select", "q4_9_p{$i}", $this->indent . "Pill #{$i}", $pillOptions); 
            $this->addTextAreaElementRD("q4_9_other{$i}", $this->indent . "If you selected [Other],please specify:");
            $this->XINRegisterRule("q4_9_other{$i}", array("q4_9_p{$i}{@}=={@}29_other"), "You must specify other", "q4_9_other{$i}_group");
            $this->form->addElement('static', null, "<br/>");
        }

        $this->XINRegisterRule("q4_9_p1", array("q4_8{@}=={@}01_yes"), "Required if used birth control or morning after pills");

        for ($i=2; $i<6; $i++)
            $this->XINRegisterRule("q4_9_p{$i}", array("q4_9_p{$i}{@}=={@}NEVER_REQUIRED"));

        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");

        $this->form->addElement('static', null, "<b><i>Use Pregnancy Calendar to answer the following.</i></b>");
        $this->form->addElement('static', null, "<br/>");


        //q4-10
        $this->form->addElement('static', null, "4-10. Which months between [-3] and [DOPB] were you using [PILL NAME]?");
        for ($i=1; $i<6; $i++)
        {
            $this->form->addElement('static', null, "<br/>");
            $this->form->addElement ( "select", "q4_10_p{$i}", $this->indent . "Pill #{$i}:", $this->negThreeToTen, "multiple size='5'" );
            $this->XINRegisterRule("q4_10_p{$i}", array("q4_10_p{$i}{@}=={@}NEVER_REQUIRED"));
        }

        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


        //q4-11
        $this->form->addElement("select", "q4_11", "4-11. Between [-3] and [DOPB], did you use any other method of contraception to avoid getting pregnant?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));	
        $this->form->addElement('static', null, $this->indent . " If you selected [No], [Refused], or [Don't know], skip to question 4-14");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


        //q4-12
        $this->form->addElement('static', null, "4-12. What method of contraception were you using?");
        $this->form->addElement('static', null, $this->indent . "<b><i> If can't recall, ask to refer to <u>List 3</u> in prep guide and choose from the following list:</i></b>");

        $contraceptionOptions = array(NULL=>"", "01" => "01 Condoms (male or female)", "02" => "02 Depo-Provera", "03" => "03  Diaphram/cervical cap", "04" => "04 Intrauterine device (IUD)", "05" => "05 Norplant", "06" => "06 Spermicide", "07" => "07 Sponge", "08_other" => "08 Other", "88 Refused", "99" => "99 Do not know", "not_answered"=>"Not Answered");
        $this->form->addElement('static', null, "<br />");


        for ($i=1; $i<6; $i++)
        {
            $this->form->addElement("select", "q4_12_{$i}", $this->indent .  "CONTRACEPTIVE METHOD #{$i}:", $contraceptionOptions);
            $this->form->addElement('static', null, "<br/>");
            $this->XINRegisterRule("q4_12_{$i}", array("q4_12_{$i}{@}=={@}NEVER_REQUIRED"));
            $this->addTextAreaElementRD("q4_12_other{$i}", $this->indent . "If you selected [Other], please specify:");
            $this->XINRegisterRule("q4_12_other{$i}", array("q4_12_{$i}{@}=={@}08_other"), "You must specify other", "q4_12_other{$i}_group");
        }

        $this->form->addElement('static', null, "<br />");


        //q4-13
        $this->form->addElement('static', null, "4-13. Which months between [-3] and [DOPB] were you using [CONTRACEPTIVE METHOD]?");  	
        $this->form->addElement('static', null, $this->indent . "<i>For each <b>Contraceptive Method</b>, select all that apply: </i>");


        for ($i=1; $i<6; $i++)
        {
            $this->form->addElement("select", "q4_13_m{$i}", $this->indent . "METHOD #{$i}:", $this->negThreeToTen, 'multiple size = "5"'); 
        }

        $this->XINRegisterRule("q4_13_m1", array("q4_11{@}=={@}01_yes"), "Required if used other method of contraception");
        for ($i=2; $i<6; $i++)
            $this->XINRegisterRule("q4_13_m{$i}", array("q4_13_m{$i}{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


        //q4-14
        $this->form->addElement('static', null, "4-14.<i> If no contraceptives were used between [-3] <u>and</u> [DOPB] (i.e., 4-8 and 4-11 = No, Refused, or Do not know), go to question 4-15</i>");
        $this->form->addElement('static', null, $this->indent . " <i>If any contraceptive was used between [-3] and [DOPB] (i.e., 4-8 <u>or</u> 4-11 = Yes), go to question 4-16</i>");	
        $this->form->addElement('static', null, "<br/>");


        //q4-15
        $this->form->addElement("select", "q4_15", "4-15. Did you... (select one of the following options)",  array(NULL=>"", "01" => "01 Stop using contraception to get pregnant", "02" => "02 Get pregnant during an interruption in using contraception", "03" => "03  Not use contraception before this pregnancy", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [02 Get pregnant during an interruption in using contraception], go to question 4-31");
        $this->XINRegisterRule("q4_15", array("q4_8{@}!={@}01_yes", "q4_11{@}!={@}01_yes"), "Required if no contraceptives were used");
        $this->form->addElement('static', null, "<br/>");


        //q4-16
        $this->form->addElement("select", "q4_16", "4-16. Did you get pregnant while consistently using contraception?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q4_16", array("q4_15{@}!={@}02"), "You must specify");
        $this->form->addElement('static', null, $this->indent . "If you selected [Yes], go to question 4-19");
        $this->form->addElement('static', null, "<br/>");


        //q4-17
        $this->form->addElement("select", "q4_17", "4-17. Before getting pregnant with [PROBAND], did you have regular intercourse for a period of 12 months or more without using contraception?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q4_17", array("q4_16{@}!={@}01_yes", "q4_16{@}!={@}"), "Required if didn't get pregnant while consistently using contraception");
        $this->form->addElement('static', null, "<br/>");


        //q4-18
        $this->form->addElement("select", "q4_18", "4-18. Did you use fertility treatment to get pregnant with [PROBAND]?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q4_18", array("q4_16{@}!={@}01_yes", "q4_16{@}!={@}"), "Required if didn't get pregnant while consistently using contraception");
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 4-31");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");

        $this->form->addElement('static', null, "<br/> <b/>Assisted Reproduction</b>");
        $this->form->addElement('static', null, "<br/>");

        $this->form->addElement('static', null, "<b><i>Now I'm going to ask you some detailed questions about what type of help you or [PROBAND]'s father may have received to help you get pregnant</i></b>");
        $this->form->addElement('static', null, "<br/>");

        //q4-19
        $this->form->addElement("select", "q4_19", "4-19. Did you take any medications to help prevent miscarriage with your pregnancy with [PROBAND]?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q4_19", array("q4_19{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 4-21");
        $this->form->addElement('static', null, "<br/>");	
        $this->form->addElement('static', null, "<br/>");


        //q4-20
        $this->form->addElement('static', null, "4-20. What medications did you take?");
        $this->form->addElement('static', null, $this->indent . "<i>If respondent can't recall, ask to refer to <b> List 4</b> in prep guide and ask to select from the following list:</i>");
        $this->form->addElement('static', null, "<br/>");


        //		for ($i=1; $i<6; $i++)
        //		{
        $this->form->addElement("select", "q4_20_m", $this->indent. "Select all that apply:", array(NULL=>"", "01" => "01 Crinonevz", "02" => "02 Prometrium", "03" => "03  Heparin", "04" => "04 Baby aspirin", "05" => "05 IVIg Therapy", "06" => "06 Steroid treatment","07_other" => "07 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"), "multiple");
        $this->addTextAreaElementRD("q4_20_m_steroid", $this->indent . "If you selected [06 Steroid treatment], please specify:");
        $this->addTextAreaElementRD("q4_20_m_other", $this->indent . "If you selected [07 Other], please specify:");
        $this->XINRegisterRule("q4_20_m_steroid", array("q4_20_m{@}=={@}06"), "You must specify steroid treatment", "q4_20_m_steroid_group");
        $this->XINRegisterRule("q4_20_m_other", array("q4_20_m{@}=={@}07_other"), "You must specify other", "q4_20_m_other_group");
        //	}	

        //	$this->XINRegisterRule("q4_20_m1", array("q4_19{@}=={@}01_yes"), "Required if took medication to prevent miscarriage during [PROBAND] pregnancy");


        $this->XINRegisterRule("q4_20_m", array("q4_20_m{@}=={@}NEVER_REQUIRED"));

        $this->form->addElement('static', null, "<br/>");


        //q4-21
        $this->form->addElement("select", "q4_21", "4-21. Did you take any medications to help you become pregnant with [PROBAND]? ",  array(NULL=>"", "01_yes" => "01 Yes", "02_no" => "02 No", "88_refused" => "88 Refused", "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 4-23");
        $this->XINRegisterRule("q4_21", array("q4_21{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement('static', null, "<br/>");


        //q4_22
        $this->form->addElement('static', null, "4-22. What medications did you take?");
        $this->form->addElement('static', null,  $this->indent . "<i><b>Probe:</b> Are there any more medications? If can't recall, ask them to refer to <b>List 5</b> in prep guide and choose from the following list:<i>");     
        $this->form->addElement('static', null, "<br/>");

        //		for ($i=1; $i<6; $i++)
        //              {

        $this->form->addElement("select", "q4_22", $this->indent . "Select all that apply:",  array(NULL=>"", "01" => "01 Bromocriptine", "02" => "02 Clomid", "03" => "03  Chorionic gonadotropin", "04" => "04 Clomiphene citrate", "05" => "05 Danazol", "05" => "05 Danocrine", "06" => "06 Dostinex", "07" => "07 Factrel", "08" => "08 Fertinex", "09" => "09 Follistim", "10" => "10 Gonadorelin", "11" => "11 Gonal-F", "12" => "12 Humegon", "13" => "13 Lupron", "14" => "14 Lutrepulse", "16" => "16 Metrodin", "17" => "17 Novarel", "18" => "18 Parlodel", "19" => "19 Pergonal", "20" => "20 Pregnyl", "21" => "21 Profasi HP", "22" => "22 Provera", "23" => "23 Repronex", "24 Serophene", "25 Synarel", "26_other" => "26 Other", "88 Refused", "99" => "99 Do not know", "not_answered"=>"Not Answered"), 'multiple size = "5"');
        $this->addTextAreaElementRD("q4_22_specify", $this->indent . "If you selected [Other], please specify:");
        $this->XINRegisterRule("q4_22_specify", array("q4_22{@}=={@}26_other"), "You must specify", "q4_22_specify_group");
        //            }

        //		$this->XINRegisterRule("q4_22_1", array("q4_21{@}=={@}01_yes"), "Required if took medications to help become pregnant with [PROBAND]");

        $this->XINRegisterRule("q4_22", array("q4_22{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


        //q4-23
        $this->form->addElement("select", "q4_23", "4-23. Did you have any other procedures to help you become pregnant with [PROBAND]?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, "<br/>");
        $this->XINRegisterRule("q4_23", array("q4_18{@}=={@}01_yes"), "Required if used fertility treatment");
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know]:");
        $this->form->addElement('static', null, $this->indent . $this->indent . " If child's biological father known, go to 4-27");
        $this->form->addElement('static', null, $this->indent . $this->indent . " If child's biological father is unknown, go to 4-31");
        $this->form->addElement('static', null, "<br/>");

        //q4-24
        $this->form->addElement('static', null, "4-24. I'm going to read you a list of procedures. Please tell me if you received any of these to help you get pregnant with [PROBAND].");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, $this->indent . "<i>If can't recall, ask them to refer to <b>List 6</b> in prep guide.</i>");
        $this->form->addElement('static', null, $this->indent . "<i>For each procedure coded in 4-24, ask questions 4-25 thru 4-26.</i>");
        $this->form->addElement('static', null, "<br/>");


        //		for ($i=1; $i<4; $i++)
        //              {
        $this->form->addElement("select", "q4_24", $this->indent . "Select all that apply:",  array(NULL=>"", "01" => "01 Artificial insemination or intrauterine insemination", "02" => "02 In vitro fertilization- embryo transfer (IVF-ET)", "03" => "03 Gamete intrafallopian transfer (GIFT)", "04" => "04 Zygote intrafallopian transfer (ZIFT)", "05" => "05 Intracytoplasmic sperm injection (ICSI)", "06" => "06 Frozen embryo transfer", "07" => "07 Tubal embryo transfer (TET)", "08" => "08 Other", "88_Refused" => "88 Refused", "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"), "multiple size = '5'");
        $this->addTextAreaElementRD("q4_24_specify", $this->indent . " If you selected [Other], please specify:");
        $this->XINRegisterRule("q4_24_specify", array("q4_24_p{$i}{@}=={@}08"), "You must specify", "q4_24_specify_group");
        //            }


        $this->XINRegisterRule("q4_24", array("q4_24{@}=={@}NEVER_REQUIRED"));


        $this->form->addElement('static', null, $this->indent . " If you selected [Refused] or [Don't Know]:");
        $this->form->addElement('static', null, $this->indent . " $this->indent If child's biological father known, then go to 4-27");
        $this->form->addElement('static', null, $this->indent . " $this->indent If child's biological father is unknown, go to 4-31");
        $this->form->addElement('static', null, "<br/>");


        //q4-25
        $this->form->addElement('static', null, "4-25. Were <u>donor</u> eggs, sperm or embryos used?");
        $this->form->addElement('static', null, $this->indent .  "<i>Using the same PROC codes as in 4-24, choose the appropriate answer for each item.</i>");

        $oneToThree = array("1"=>"Eggs", "2"=>"Sperm", "3"=>"Embryo");
        reset($oneToThree);

        for ($i=1; $i<4; $i++){

            $this->form->addElement('static', null, "<br/>");
            $this->form->addElement('static', null, $this->indent . "PROC #{$i}:");


            foreach ($oneToThree as $key=>$value)
            {
                $this->form->addElement("select", "q4_25_{$value}_{$i}", $this->indent . $this->indent . "{$value}:", $this->yesNo);
                $this->XINRegisterRule("q4_25_{$value}_{$i}", array("q4_25_{$value}_{$i}{@}=={@}NEVER_REQUIRED"));
            }
        }


        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


        //q4-26
        $this->form->addElement('static', null, "4-26. Were <u>frozen</u> eggs, sperm or embryos used?");
        $this->form->addElement('static', null, $this->indent .  "<i>Using the same PROC codes as in 4-24, choose the appropriate answer for each item.</i>");

        $oneToThree = array("1"=>"Eggs", "2"=>"Sperm", "3"=>"Embryo");
        reset($oneToThree);

        for ($i=1; $i<4; $i++){

            $this->form->addElement('static', null, "<br/>");
            $this->form->addElement('static', null, $this->indent . "PROC #{$i}:");

            foreach ($oneToThree as $key=>$value)
            {
                $this->form->addElement("select", "q4_26_{$value}_{$i}", $this->indent . $this->indent . "{$value}:", $this->yesNo);
                $this->XINRegisterRule("q4_26_{$value}_{$i}", array("q4_26_{$value}_{$i}{@}=={@}NEVER_REQUIRED"));
            }
        }

        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement("static", null, $this->indent . "<b>If [PROBAND] father is unknown, go to 4-31</b>");
        $this->form->addElement('static', null, "<br/>");


        //q4-27
        $this->form->addElement("select", "q4_27", "4-27. Did [PROBAND]'s father take any medications to help you become pregnant?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q4_27", array("q4_27{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 4-29");
        $this->form->addElement('static', null, "<br/>");

        //q4-28
        $this->form->addElement('static', null, "4-28. What medications did he take?");
        $this->form->addElement('static', null,  $this->indent . "<i>Probe: Are there any more medications? If can't recall, ask them to refer to <b> List</b> 5 in prep guide and choose from the following list:</i>");     
        $this->form->addElement('static', null, "<br/>");

        //	for ($i=1; $i<6; $i++)
        //	{

        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement("select", "q4_28", $this->indent . $this->indent . "Select all that apply:",  array(NULL=>"", "01" => "01 Bromocriptine", "02" => "02 Clomid", "03" => "03  Chorionic gonadotropin", "04" => "04 Clomiphene citrate", "05" => "05 Danazol", "05" => "05 Danocrine", "06" => "06 Dostinex", "07" => "07 Factrel", "08" => "08 Fertinex", "09" => "09 Follistim", "10" => "10 Gonadorelin", "11" => "11 Gonal-F", "12" => "12 Humegon", "13" => "13 Lupron", "14" => "14 Lutrepulse", "16" => "16 Metrodin", "17" => "17 Novarel", "18" => "18 Parlodel", "19" => "19 Pergonal", "20" => "20 Pregnyl", "21" => "21 Profasi HP", "22" => "22 Provera", "23" => "23 Repronex", "24" => "24 Serophene", "25" => "25 Synarel", "26" => "26 Other", "88_refused" => "88 Refused", "99_do_not_know" => "99 Do not know", "not_answered"=>"Not Answered"), 'multiple size = "5"');
        $this->addTextAreaElementRD("q4_28_other", $this->indent . $this->indent . " If you selected [Other], please specify:" );
        //	}

        $this->XINRegisterRule("q4_28_other", array("q4_28{@}=={@}26_other"), "You must specify", "q4_28_other_group");

        $this->XINRegisterRule("q4_28", array("q4_28{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement('static', null, "<br/>");


        //q 4-29
        $this->form->addElement("select", "q4_29", "4-29. Did [PROBAND]'s father have any procedures or surgeries to help you become pregnant?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q4_29", array("q4a_1{@}=={@}01_yes|02", "q4_27{@}=={@}01_yes"), "You must specify");
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 4-31");
        $this->form->addElement('static', null, "<br/>");


        //q4-30
        $this->form->addElement('static', null, "4-30. What was the procedure?");
        $this->form->addElement('static', null, $this->indent. "<i>Probe: Are there any more procedures?</i>");
        $this->form->addElement('static', null, "<br/>");


        for ($i=1; $i<4; $i++)
        {
            $this->addTextAreaElementRD("q4_30_p{$i}", $this->indent . "Procedure #{$i}:");
        }

        $this->XINRegisterRule("q4_30_p1", array("q4_29{@}=={@}01_yes"), "Required if father had procedures or surgeries", "q4_30_p1_group");

        for ($i=2; $i<4; $i++)
            $this->XINRegisterRule("q4_30_p{$i}", array("q4_30_p{$i}{@}=={@}NEVER_REQUIRED"), "q4_30_p{$i}_group");


        $this->addTextAreaElementRD('q4_30_additional', $this->indent . "Additional procedures: ");
        $this->XINRegisterRule("q4_30_additional", array("q4_30_additional{@}=={@}NEVER_REQUIRED"), "q4_30_additional_group");
        $this->form->addElement('static', null, "<br/>");	
        $this->form->addElement('static', null, "<br/>");

    }

    function rulesPage5($fields) {

        $errors = array();

        function multSelect($fields, $question1, $question2)
        {
            return (($fields[$question1] == array(0=>null) && $fields[$question2]) || (empty($fields[$question1])) && $fields[$question2] == "01_yes");
        }

        //q4_10
        if($fields["q4_10_p1"] == array(0=>null) || (empty($fields["q4_10_p1"]) &&  $fields["q4_8"] == "01_yes"))
            $errors["q4_10_p1"] = "You must specify month(s)";

        //q4_12
        if (empty($fields["q4_12_1"]) && $fields["q4_11"] == "01_yes")
            $errors["q4_12_1"] = "You must specify contraceptive";

        //q4_13
        if (multSelect($fields, "q4_13_m1", "q4_11"))
            $errors["q4_13_m1"] = "You must specify month(s)";

        //q4_19
        if (empty($fields["q4_19"]) && ($fields["q4_16"] == "01_yes" || $fields["q4_18"] == "01_yes"))
            $errors["q4_19"] = "You must specify";

        //q4_20
        if (multSelect($fields, "q4_20_m", "q4_19"))
            $errors["q4_20_m"] = "You must specify medications";

        //q4_21
        if (empty($fields["q4_21"]) && ($fields["q4_16"] == "01_yes" || $fields["q4_18"] == "01_yes"))// != "02"||"88_refused"||"99_Do_not_know"||"Not_Answered"))
            $errors["q4_21"] = "You must specify";

        //q4_22
        if (multSelect($fields, "q4_22", "q4_21"))
            $errors["q4_22"] = "You must specify medications";

        //q4_23
        if (empty($fields["q4_23"]) && ($fields["q4_16"] == "01_yes" || $fields["q4_18"] == "01_yes"))
            $errors["q4_23"] = "You must specify";

        //q4_24
        if (multSelect($fields, "q4_24", "q4_23"))
            $errors["q4_24"] = "You must specify procedures";

        $questions = array("Eggs_1", "Sperm_1", "Embryo_1");

        //q4_25
        if ($fields["q4_24"] != array(0=>"88_Refused") && $fields["q4_24"] != array(0=>"99_Do_not_know") && $fields["q4_24"] != array(0=>NULL) && $fields["q4_23"] == "01_yes")
        {
            foreach ($questions as $field)
            {
                if (empty($fields["q4_25_$field"]))
                    $errors["q4_25_$field"] = "You must specify";
            }
        }

        //q4_26
        if ($fields["q4_24"] != array(0=>"88_Refused") && $fields["q4_24"] != array(0=>"99_Do_not_know") && $fields["q4_24"] !=  array(0=>NULL) && $fields["q4_23"] == "01_yes")
        {
            foreach ($questions as $field)
            {
                if (empty($fields["q4_26_$field"]))
                    $errors["q4_26_$field"] = "You must specify";
            }
        }

        //q4_27
        if ($fields["q4_23"] != "01_yes")
        {
            if (($fields["q4a_1"] == "01_yes"|| $fields["q4a_1"] == "02") && empty($fields["q4_27"]) && ($fields["q4_16"] == "01_yes" || $fields["q4_18"] == "01_yes"))
                $errors["q4_27"] = "Required if biological father is known";
        }

        else if ($fields["q4_24"] == "88_Refused"|| $fields["q4_24"] == "99_Do_not_know")
        {
            if (($fields["q4a_1"] == "01_yes"||"02") && empty($fields["q4_27"]))
                $errors["q4_27"] = "Required if biological father is known";			
        }


        //q4_28
        if (multSelect($fields, "q4_28", "q4_27"))
            $errors["q4_28"] = "You must specify medications";


        //		if (($fields["q4a_1"] == "01_yes"|| $fields["q4a_1"] == "02") && $fields["q4_27"] == "01_yes" && empty($fields["q8_29"]))
        //			$errors["q4_29"] == "You must specify";

        return $errors;

    }


    function _page6() {


        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('header', null, "Section 4. PROBAND PREGNANCY <br /><br /> (PART 2 OF 4)");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('header', null, "<b>Morning Sickness</b>");

        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<b><i>Now I have some more detailed questions about your pregnancy with [PROBAND]. You will need to look at your pregnancy calendar for [PROBAND].</i></b>");
        $this->form->addElement('static', null, "<br/>");

        //function with more complex rules
        $this->form->addFormRule(array(&$this,'rulesPage6'));


        //q4-31
        $this->form->addElement("select", "q4_31", "4-31. During the pregnancy with [PROBAND] did you have any nausea?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 4-34");
        $this->form->addElement('static', null, "<br/>");


        //q4-32
        $this->form->addElement("select", "q4_32", "4-32. During which months did you have nausea? Select all that apply:", $this->negThreeToTen, "multiple size = '5'");
        $this->XINRegisterRule('q4_32', array("q4_32{@}=={@}NEVER_REQUIRED"));


        //q4-33
        $this->form->addElement ( 'static', null, "4-33. How often during [SPECIFY MONTH] did you have nausea?" );
        $group[] =&$this->form->createElement("static", "month_header");
        $group[] =&$this->form->createElement("static", "freq_header");
        $this->form->addGroup($group, "q4_33_headers", "Would you say it was...", $this->_GUIDelimiter, false);
        unset($group);

        unset($negThreeToTen[10]); //only want to go up to 9
        $aToF = array("a", "b", "c", "d", "e", "f");
        foreach($aToF as $label) {
            $group[] = &$this->form->createElement( "select", "q4_33_m_{$label}", null, array_merge((array (NULL => "")) , $this->negThreeToTen));
            $group[] = &$this->form->createElement ( "select", "q4_33_f_{$label}", null, array (NULL => "", "01" => "01 Less than once a week", "02" => "02 Once a week", "03" => "03  A few times a week", "04" => "04 Every day", "88 Refused", "99" => "99 Do not know", "not_answered"=>"Not Answered" ) );
            $this->form->addGroup($group, "q4_33_{$label}_group", "{$label})", $this->_GUIDelimiter, false);
            unset($group);
            //Don't require all questions, but allow them to be filled in, if desired.
            if ($label=="a") continue; //Special rules apply to the first month
            $this->XINRegisterRule("q4_33_m_{$label}", array("q4_33_m_{$label}{@}=={@}NEVER_REQUIRED"), "q4_33_{$label}_group");
            $this->XINRegisterRule("q4_33_f_{$label}", array("q4_31_f_{$label}{@}=={@}NEVER_REQUIRED"), "q4_33_{$label}_group");
        }
        //Only require the first month to be answered, if there was nausea.  Trust that the rest will be filled in as needed.
        $this->XINRegisterRule("q4_33_m_a", array("q4_31{@}=={@}01_yes"), "Required if there was nausea", "q4_33_a_group");
        $this->XINRegisterRule("q4_33_f_a", array("q4_31{@}=={@}01_yes"), "Required if there was nausea", "q4_33_a_group");
        $this->form->addElement('static', null, "<br/>");


        //q4-34
        $this->form->addElement("select", "q4_34", "4-34. During the pregnancy with [PROBAND] did you have any vomiting?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 4-39");
        $this->form->addElement('static', null, "<br/>");



        //q4-35
        $this->form->addElement ("select", "q4_35", "4-35. During which months did you vomit? Select all that apply:", $this->negThreeToTen, "multiple size = '5'");
        $this->XINRegisterRule('q4_35', array("q4_35{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement('static', null, "<br/>");


        //q4-36
        $this->form->addElement ( 'static', null, "4-36. How often during [SPECIFY MONTH] did you vomit?" );
        $group[] =&$this->form->createElement("static", "month_header");
        $group[] =&$this->form->createElement("static", "freq_header");
        $this->form->addGroup($group, "q4_36_headers", "Would you say it was...", $this->_GUIDelimiter, false);
        unset($group);

        unset($negThreeToTen[10]); //only want to go up to 9
        $aToF = array("a", "b", "c", "d", "e", "f");
        foreach($aToF as $label) {
            $group[] = &$this->form->createElement( "select", "q4_36_m_{$label}", null, $this->negThreeToTen);
            $group[] = &$this->form->createElement ( "select", "q4_36_f_{$label}", null, array (NULL => "", "01" => "01 Less than once a week", "02" => "02 Once a week", "03" => "03  A few times a week", "04" => "04 Every day", "88 Refused", "99" => "99 Do not know", "not_answered"=>"Not Answered" ) );
            $this->form->addGroup($group, "q4_36_{$label}_group", "{$label})", $this->_GUIDelimiter, false);
            unset($group);
            //Don't require all questions, but allow them to be filled in, if desired.
            if ($label=="a") continue; //Special rules apply to the first month
            $this->XINRegisterRule("q4_36_m_{$label}", array("q4_36_m_{$label}{@}=={@}NEVER_REQUIRED"), "q4_36_{$label}_group");
            $this->XINRegisterRule("q4_36_f_{$label}", array("q4_36_f_{$label}{@}=={@}NEVER_REQUIRED"), "q4_36_{$label}_group");
        }
        //Only require the first month to be answered, if there was vomiting.  Trust that the rest will be filled in as needed.
        $this->XINRegisterRule("q4_36_m_a", array("q4_34{@}=={@}01_yes"), "Required if there was vomiting", "q4_36_a_group");
        $this->XINRegisterRule("q4_36_f_a", array("q4_34{@}=={@}01_yes"), "Required if there was vomiting", "q4_36_a_group");


        $this->form->addElement('static', null, $this->indent . "<b><i>If nausea or vomiting occurred during pregnancy (i.e., 4-31 or 4-34 = [Yes]), go to question 4-37.</i></b>");
        $this->form->addElement('static', null, $this->indent . "<b><i>If no nausea or vomiting occurred during pregnancy (i.e 4-31 and 4-34 = [No], [Refused] or [Don't Know]), go to question 4-39.</i></b>");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


        //q4-37
        $this->form->addElement("select", "q4_37", "4-37. Did you ever require medical treatment for the nausea or vomiting?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule('q4_37', array("q4_37{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know], skip to question 4-39");

        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "4-38. What medicine/treatment did you take? Was it...");


        $oneToThree = array("1"=>"#1", "2"=>"#2", "3"=>"#3");
        reset($oneToThree);

        while(list($field, $label) = each($oneToThree)){

            $this->form->addElement('static', null, "<br/>");

            $this->form->addElement("select", "q4_38_med_{$field}", $this->indent . "MED {$label}:", array(NULL=>"", "01" => "01 Vitamin B6 (pyridoxine)", "02" => "02 Unisom (doxylamine)", "03" => "03  Emetrol", "04" => "04 Ginger", "05_other" => "05 Other",  "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

            $this->addTextAreaElementRD("q4_38_other{$field}", $this->indent . "If you selected [Other], please specify:");
            $this->XINRegisterRule("q4_38_other{$field}", array("q4_38_med_{$field}{@}=={@}05_other"), "You must specify other", "q4_38_other{$field}_group");
        }


        $this->XINRegisterRule("q4_38_med_1", array("q4_37{@}=={@}01_yes"), "Required if there was medical treatment");
        $this->XINRegisterRule("q4_38_med_2", array("q4_38_med_2{@}=={@}NEVER_REQUIRED"));
        $this->XINRegisterRule("q4_38_med_3", array("q4_38_med_3{@}=={@}NEVER_REQUIRED"));


        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<b>Prenatal Care</b>");
        $this->form->addElement('static', null, "<br/>");


        //q4-39
        $this->form->addElement("select", "q4_39",  "4-39. During your pregnancy with [PROBAND], how many ultrasounds did you have?", array_merge((array(NULL=>"")),(array_combine(range(0,20), range(0,20))),(array("88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"))));
        $this->form->addElement('static', null, "<br/>");

        //q4-40
        $this->form->addElement("select", "q4_40", "4-40. Did you have an Amniocentesis or amnio?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 4-43.");
        $this->form->addElement('static', null, "<br/>");

        //q4-41
        $this->form->addElement("static", null, "4-41. When was it done?");
        $this->XINRegisterRule("q4_41", array("q4_40{@}=={@}01_yes"), "Required if had Amniocentesis or amnio");
        $this->addCustomDateElement('q4_41_date', $this->indent . "Please specify date:", $this->dateOptions2007);
        $this->form->addElement("select", "q4_41_week", $this->indent . "OR gestational weeks:" ,array_merge((array(NULL=>"")), (array_combine(range(1,45), range(1,45))), array("88_refused"=>"88 Refused", "99_do_not_know"=>"99 Do not know", "not_answered"=>"Not Answered")));	
        $this->XINRegisterRule("q4_41_date_date", array("q4_40{@}=={@}01_yes", "q4_41_week{@}=={@}", "q4_41_date_date_status{@}=={@}"), "You must specify date", "q4_41_date_date_group");
        $this->XINRegisterRule("q4_41_date_date_status", array("q4_40{@}=={@}01_yes", "q4_41_week{@}=={@}", "q4_41_date_date{@}=={@}"), "You must specify date", "q4_41_date_date_group");
        $this->XINRegisterRule("q4_41_week", array("q4_40{@}=={@}01_yes", "q4_41_date_date{@}=={@}", "q4_41_date_date_status{@}=={@}"), "OR weeks");
        $this->form->addElement('static', null, "<br/>");

        //q4-42
        $this->form->addElement("select", "q4_42", "4-42. Were there any abnormalities detected?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q4_42", array("q4_40{@}=={@}01_yes"), "Required if had Amniocentesis or amnio");
        $this->form->addElement('static', null, "<br/>");

        //q4-43
        $this->form->addElement("select", "q4_43", "4-43. Did you have Chorionic Villus Sampling or CVS?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 4-46");
        $this->form->addElement('static', null, "<br/>");

        //q4-44
        $this->form->addElement("static", null, "4-44. When was it done?");
        $this->addCustomDateElement('q4_44_date', $this->indent . "Specify date:", $this->dateOptions2007);
        $this->form->addElement("select", "q4_44_week", $this->indent . "OR gestational weeks:", array_merge((array(NULL=>"")),(array_combine(range(0,20), range(0,20))),(array("88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"))));
        //		$this->XINRegisterRule("q4_44", array("q4_43{@}=={@}01_yes"), "Required if had Chorionic Villus Sampling or CVS");
        $this->XINRegisterRule("q4_44_date_date_status", array("q4_44_week{@}=={@}", "q4_44_date_date{@}=={@}", "q4_43{@}=={@}01_yes"), "You must specify date", "q4_44_date_date_group");
        $this->XINRegisterRule("q4_44_date_date", array("q4_44_week{@}=={@}", "q4_44_date_date_status{@}=={@}", "q4_43{@}=={@}01_yes"), "You must specify date", "q4_44_date_date_group");
        $this->XINRegisterRule("q4_44_week", array("q4_44_date_date{@}=={@}", "q4_44_date_date_status{@}=={@}", "q4_43{@}=={@}01_yes"), "OR weeks");
        $this->form->addElement('static', null, "<br/>");


        //q4-45
        $this->form->addElement("select", "q4_45", "4-45. Were there any abnormalities detected?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q4_45", array("q4_43{@}=={@}01_yes"), "Required if had Chorionic Villus Sampling or CVS");
        $this->form->addElement('static', null, "<br/>");


        //q4-46
        $this->form->addElement("select", "q4_46", "4-46. Were you told that there was [rhesus] or [Rh] incompatibility between you and [PROBAND]?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 4-50");
        $this->form->addElement('static', null, "<br/>");


        //q4-47
        $this->form->addElement("select", "q4_47", "4-47. If your blood type is Rh-, during pregnancy you might have been given injections of Rhogam. Did you receive any Rhogam injections while you were pregnant with [PROBAND]?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q4_47", array("q4_46{@}=={@}01_yes"), "Required if had rhesus or Rh incompatibility");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<b><i>Ask if pregnant more than twice (including younger sibling of child with ASD) (i.e., question 3-4 > 2)</i></b>");
        $this->form->addElement('static', null, "<br/>");


        //q4-48
        $this->form->addElement("select", "q4_48", "4-48. Did you receive Rhogam injections for any other pregnancy (other than the pregnancy with [PROBAND] or [SIBLING]?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q4_48", array("q4_46{@}=={@}01_yes"), "Required if had rhesus or Rh incompatibility");
        $this->form->addElement('static', null, "<br/>");


        //q4-49
        $this->form->addElement("select", "q4_49", "4-49. Were there any problems with [PROBAND] because of the rhesus incompatibility?",  array(NULL=>"", "01_yes" => "01 Yes", "02_no" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->addTextAreaElementRD('q4_49_text', $this->indent . "If you selected [Yes], please specify:");
        $this->XINRegisterRule("q4_49", array("q4_46{@}=={@}01_yes"), "Required if had rhesus or Rh incompatibility");
        $this->XINRegisterRule("q4_49_text", array("q4_49{@}=={@}01_yes"), "You must specify", "q4_49_text_group");
        $this->form->addElement('static', null, "<br/>");


        //q4-50
        $this->form->addElement ("select", "q4_50", "4-50. During your pregnancy with [PROBAND], did you receive shots or immunizations such as",  array(NULL=>"", "01" => "01 Immunoglobulin injection (other than RhoGam)?", "02" => "02 No ", "03_other" => "03  Other", "05" => "05 Flu Shot", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"), "multiple size = '7'");
        $this->addTextAreaElementRD('q4_50_text', $this->indent . "If you selected [Other], please specify:");
        $this->XINRegisterRule("q4_50_text", array("q4_50{@}=={@}03_other"), "You must specify other", "q4_50_text_group");

        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<b/>Vaginal Douching");
        $this->form->addElement('static', null, "<b><i>Refer to the pregnancy calendar for the following questions.</i></b>");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


        //q4-51
        $this->form->addElement("select", "q4_51", "4-51. Did you ever douche between [-3] and [DOPB]?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 4-54");
        $this->form->addElement('static', null, "<br/>");


        //q4-52
        $this->form->addElement('static', null, "4-52. Between [-3] and [DOPB], which months did you douche?");
        $this->form->addElement("select", "q4_52",  $this->indent . " Choose all that apply:", $this->negThreeToNine, "multiple size = '5'"); 
        $this->form->addElement('static', null, $this->indent . "If you selected [Refused] or [Don't Know] skip to question 4-54");
        $this->form->addElement('static', null, "<br/>");


        //q4-53
        $this->form->addElement ( 'static', null, "4-53. On average, how often would you say you douched during [SPECIFY MONTH]?" );
        $group[] =&$this->form->createElement("static", "month_header");
        $group[] =&$this->form->createElement("static", "freq_header");
        $this->form->addGroup($group, "q4_53_headers", "Would you say it was...", $this->_GUIDelimiter, false);
        unset($group);

        unset($negThreeToTen[10]); //only want to go up to 9
        $aToF = array("a", "b", "c", "d", "e", "f");
        foreach($aToF as $label) {
            $group[] = &$this->form->createElement( "select", "q4_53_m_{$label}", null, $this->negThreeToTen);
            $group[] = &$this->form->createElement ( "select", "q4_53_f_{$label}", null, array (NULL => "", "01" => "01 Less than once a week", "02" => "02 Once a week", "03" => "03 A few times a week", "04" => "04 Every day", "88 Refused", "99" => "99 Do not know", "not_answered"=>"Not Answered" ) );
            $this->form->addGroup($group, "q4_53_{$label}_group", "{$label})", $this->_GUIDelimiter, false);
            unset($group);
            //Don't require all questions, but allow them to be filled in, if desired.
            if ($label=="a") continue; //Special rules apply to the first month
            $this->XINRegisterRule("q4_53_m_{$label}", array("q4_53_m_{$label}{@}=={@}NEVER_REQUIRED"), "q4_53_{$label}_group");
            $this->XINRegisterRule("q4_53_f_{$label}", array("q4_53_f_{$label}{@}=={@}NEVER_REQUIRED"), "q4_53_{$label}_group");
        }
        //Only require the first month to be answered, if there was douching.  Trust that the rest will be filled in as needed.
        $this->XINRegisterRule("q4_53_m_a", array("q4_51{@}=={@}01_yes"), "Required if there was douching", "q4_53_a_group");
        $this->XINRegisterRule("q4_53_f_a", array("q4_51{@}=={@}01_yes"), "Required if there was douching", "q4_53_a_group");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


    }//end function _page6()========================================================



    function rulesPage6($fields)
    {

        $errors = array();

        function multSelect($fields, $question1, $question2)
        {
            return (($fields[$question1] == array(0=>null) && $fields[$question2] == "01_yes") || (empty($fields[$question1])) && $fields[$question2] == "01_yes");
        }

        //q4-32
        if (multSelect($fields, "q4_32", "q4_31"))
            $errors["q4_32"] = "Required if there was nausea";

        //q4-35
        if (multSelect($fields, "q4_35", "q4_34"))
            $errors["q4_35"] = "Required if there was vomiting";

        //q4-37
        if (($fields["q4_31"] == "01_yes" || $fields["q4_34"] == "01_yes"))
        {
            if (empty($fields["q4_37"]))
                $errors["q4_37"] = "Required if there was nausea or vomiting";
        }


        //q4-52
        if (multSelect($fields, "q4_52", "q4_51"))
            $errors["q4_52"] = "Required if there was douching";

        return $errors;

    }


    function _page7(){   // ========================================================


        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('header', null, "Section 4. PROBAND PREGNANCY <br /><br /> (PART 3 OF 4)");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('header', null, "<b/>Maternal Medical Conditions");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");

        //function with more complex rules
        $this->form->addFormRule(array(&$this,'rulesPage7'));


        //q4-54
        $this->form->addElement("select", "q4_54", "4-54. During your pregnancy with [PROBAND] were you ever told by a physician or nurse that you had preeclampsia or toxemia?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 4-56");
        $this->form->addElement('static', null, "<br/>");

        //q4-55
        $this->form->addElement("select", "q4_55", "4-55. Did you take any medicine for preeclampsia or toxemia?", array(NULL=>"", "01_yes" => "01 Yes", "02_no" => "02 No", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 4-56");
        $this->XINRegisterRule("q4_55", array("q4_54{@}=={@}01_yes"), "Required if had preeclampsia or toxemia");
        $this->form->addElement('static', null, "<br/>");

        //q4-56
        $this->form->addElement("select", "q4_56", "4-56. During your pregnancy with [PROBAND] were you ever told by a physician or nurse that you had premature labor?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 4-59");

        $OneToNine = array("1"=>"01", "2"=>"02", "3"=>"03", "4"=>"04", "5"=>"05", "6"=>"06", "7"=>"07", "8"=>"08", "9"=>"09");
        $answerOptions = array(null=>"") + ($OneToNine) + array("88_Refused" => "88 Refused", "99_Do_not_know" => "99 Do not know", "not_answered" => "Not Answered");

        //q4-57
        $this->form->addElement ( "select", "q4_57", "4-57. During which months of the pregnancy did you have the premature labor? Select all that apply:", $answerOptions, "multiple size = '5'" );
        $this->XINRegisterRule("q4_57", array("q4_57{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement('static', null, "<br/>");

        //q4-58
        $this->form->addElement("select", "q4_58", "4-58. Did you take any medicine for premature labor?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q4_58", array("q4_56{@}=={@}01_yes"), "Required if had premature labor");
        $this->form->addElement('static', null, "<br/>");

        //q4-59
        $this->form->addElement("select", "q4_59", "4-59. During your pregnancy with [PROBAND] did you have vaginal bleeding?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 4-62");


        //q4-60
        $this->form->addElement ( "select", "q4_60", "4-60. During which months of pregnancy did you have the bleeding? Select all that apply:", $answerOptions, "multiple size = '5'" );
        $this->XINRegisterRule("q4_60", array("q4_60{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement('static', null, "<br/>");

        //q4-61
        $this->form->addElement("select", "q4_61", "4-61. Did you take any medicine for the bleeding?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q4_61", array("q4_59{@}=={@}01_yes"), "Required if had bleeding");
        $this->form->addElement('static', null, "<br/>");

        //q4-62
        $this->form->addElement("select", "q4_62", "4-62 During your pregnancy with [PROBAND] were you ever told by a physician or nurse that you had gestational diabetes?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 4-65");
        $this->form->addElement('static', null, "<br/>");


        //q4-63
        $this->form->addElement ( "select", "q4_63", "4-63. During which months did you have the gestational diabetes? Select all that apply:", $answerOptions, "multiple size = '5'" );
        $this->XINRegisterRule("q4_63", array("q4_63{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement('static', null, "<br/>");

        //q4-64
        $this->form->addElement("select", "q4_64", "4-64. Did you take any medicine for gestational diabetes?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q4_64", array("q4_62{@}=={@}01_yes"), "Required if had gestational diabetes");
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 4-65");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");

        $this->form->addElement('static', null, "<b><i>Now, I am going to ask you about some illnesses, surgeries and other procedures that you might have had during your pregnancy with [PROBAND]. I'm going to ask you about the time period from three months before you became pregnant with [PROBAND] until [HIS/HER] delivery.</i></b>");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<b/>Reproductive and Major Perinatal Infections");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<b><i>I am going to start off by asking you about some infections that you might have had during that pregnancy.</i></b>");
        $this->form->addElement('static', null, "<br/>");

        //q4-65
        $this->form->addElement('static', null, "4-65. Between [-3] and [DOPB] did you have any of the following infections?");

        $aToX = array("a" => "A. Bacterial Vaginosis", "b" => "B. Candidiasis", "c" => "C. Chlamydia", "d" => "D. Chicken pox", "e" => "E. Cytomegalovirus", "f" => "F. Genital Herpes", "g" =>"G. Group B Streptococcal infection", "h" =>"H. Hepatitis A", "i" =>"I. Hepatitis B", "j" =>  "J. Hepatitis C", "k" => "K. Human Papilloma Virus (HPV)", "l" => "L. Influenza", "m" =>"M. Mononucleosis", "n" => "N. Parvovirus or Fifth disease", "o" => "O. Pelvic Inflammatory Disease (PID)", "p" => "P. Pneumonia", "q" => "Q. Rubella or German measles", "r" => "R. Shingles", "s" => "S. Syphilis", "t" => "T. Toxoplasmosis", "u" =>"U. Trichomoniasis", "v" => "V. Upper respiratory infection", "w" => "W. Urinary tract infection ", "x" => "X. Other conditions");
        //reset($aToX);

        while(list($field, $label) = each($aToX)){

            $this->form->addElement("select", "q4_65_{$field}", $this->indent . "{$label}:", array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        }

        $this->form->addElement('static', null, $this->indent . $this->indent . " If you selected [Yes] for Genital Herpes, go to question 4-66");
        $this->form->addElement('static', null, $this->indent . $this->indent . " If you selected [Yes] for Venereal/genital warts, go to question 4-67");
        $this->form->addElement('static', null, $this->indent . $this->indent . " If you selected [Yes] for any other infection on the list, go to question 4-68");
        $this->form->addElement('static', null, $this->indent . $this->indent . " If you selected [No], [Refused] or [Don't Know] for <u>all</u>, go to question 4-70");
        $this->addTextAreaElementRD('q4_65_other', $this->indent . $this->indent . " If you selected [Other conditions], (e.g., vaginitis, fibroids, venereal warts, or endometriosis), please specify:");
        $this->XINRegisterRule("q4_65_other", array("q4_65_x{@}=={@}01_yes"), "You must specify other", "q4_65_other_group");
        $this->form->addElement('static', null, "<br/>");


        //q4-66
        $this->form->addElement ( "select", "q4_66", "4-66. During which months from [-3] to [DOPB] did you have the Herpes outbreak? Select all that apply:", $this->negThreeToNine, "multiple size = '5'" );
        $this->XINRegisterRule('q4_66', array("q4_66{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement('static', null, "<br/>");


        //q4-67
        $this->form->addElement('select', 'q4_67', "4-67. During which months from [-3] to [DOPB] did you have the Venereal/genital warts outbreak? Select all that apply:", $this->negThreeToNine, "multiple size = '5'");
        $this->XINRegisterRule('q4_67', array("q4_67{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement('static', null, "<br/>");


        //q4-68
        $this->form->addElement('static', null, "4-68. During which months from [-3] to [DOPB] did you have [INFECTION]?");
        $this->form->addElement('static', null, $this->indent . "<i>Select [INFECTION] as entered in 4-65</i>");


        foreach ($this->oneToThree as $field=>$label)
        {
            $this->form->addElement('static', null, "<br/>");
            $this->form->addElement("select", "q4_68_{$field}", $this->indent . "INFECTION {$label}", array_merge(array(NULL=>""), $aToX, array("88_refused"=>"88 Refused", "99_Do_not_know"=>"99 Do not know", "not_answered"=>"Not Answered")));
            $this->form->addElement("select", "q4_68_select_{$field}", $this->indent . "Select all that apply: ", $this->negThreeToTen , "multiple size = '5'");	
            $this->XINRegisterRule("q4_68_{$field}", array("q4_68_{$field}{@}=={@}NEVER_REQUIRED"));
            $this->XINRegisterRule("q4_68_select_{$field}", array("q4_68_select_{$field}{@}=={@}NEVER_REQUIRED"));

        }

        //	reset ($aToX);

        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


        //q4-69
        $this->form->addElement("select", "q4_69", "4-69. Was medication taken for the infection?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q4_69", array("q4_69{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 4-70");

        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('header', null, "<b/>Other Illnesses");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<b><i>I am going to ask you about some illnesses that you might have had during that pregnancy.</i></b>");
        $this->form->addElement('static', null, "<br/>");


        //q4-70
        $this->form->addElement('static', null, "4-70. Between [-3] and [DOPB] did you have any of the following illnesses?");
        $aToM = array("a" => "A. Migraine", "b" => "B. Depression", "c" => "C. Nervousness", "d" => "D. Anxiety", "e" => "E. Bipolar", "f" => "F. Other Mental Disorders", "g" => "G. Epilepsy or Seizure", "h" => "H. Thyroid condition", "i" => "I. Allergy", "j" =>  "J. Asthma", "k" => "K. Arthritis", "l" => "L. Neurologic Disease", "m" => "M.Autoimmune condition");
        //	reset($aToM);


        foreach ($aToM as $field=>$label)
        {
            $this->form->addElement("select", "q4_70_{$field}", $this->indent . "{$label}:", array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        }

        $this->addTextAreaElementRD('q4_70f', $this->indent . "If you selected [f. Other Mental Disorders], please specify:");
        $this->addTextAreaElementRD('q4_70l', $this->indent . "If you selected [l. Neurologic Disease ], please specify:");
        $this->addTextAreaElementRD('q4_70m', $this->indent . "If you selected [m. Autoimmune Condition], please specify:");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, $this->indent . "If you selected [Yes] for any illness on the list, go to question 4-71");
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] for <u>all</u>, go to question 4-73");
        $this->form->addElement('static', null, "<br/>");
        $this->XINRegisterRule("q4_70f", array("q4_70_f{@}=={@}01_yes"), "You must specify other mental disorders", "q4_70f_group");
        $this->XINRegisterRule("q4_70l", array("q4_70_l{@}=={@}01_yes"), "You must specify neurologic disease", "q4_70l_group");
        $this->XINRegisterRule("q4_70m", array("q4_70_m{@}=={@}01_yes"), "You must specify autoimmune condition", "q4_70m_group");


        //q4-71
        $this->form->addElement('static', null, "4-71. During which months from [-3] to [DOPB] did you have [illness]?"); 

        foreach($this->oneToThree as $field=>$label)
        {
            $this->form->addElement('static', null, "<br/>");
            $this->form->addElement("select", "q4_71_{$field}", $this->indent . "ILLNESS {$label}:",  array(NULL=>"") + $aToM + array("88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
            $this->XINRegisterRule("q4_71_{$field}", array("q4_71_{$field}{@}=={@}NEVER_REQUIRED"));
            $this->form->addElement("select", "q4_71_select_{$field}", $this->indent . "Select all that apply: ", $this->negThreeToTen , "multiple size = '5'");	
            $this->XINRegisterRule("q4_71_select_{$field}", array("q4_71_select_{$field}{@}=={@}NEVER_REQUIRED"));
        }


        reset($aToM);
        $this->form->addElement('static', null, "<br/>");


        //q4-72
        $this->form->addElement("select", "q4_72", "4-72. Was medication taken for the illness?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q4_72", array("q4_72{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 4-73");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");



    }// end function _page7()========================================================


    function rulesPage7($fields)
    {

        $errors = array();

        function multSelect($fields, $question1, $question2)
        {
            return (($fields[$question1] == array(0=>null) && $fields[$question2] == "01_yes") || (empty($fields[$question1])) && $fields[$question2] == "01_yes");
        }

        //q4-57
        if (multSelect($fields, "q4_57", "q4_56"))
            $errors["q4_57"] = "Required if there was premature labour";

        //q4-60
        if (multSelect($fields, "q4_60", "q4_59"))
            $errors["q4_60"] = "Required if there was vaginal bleeding";

        //q4-63
        if (multSelect($fields, "q4_63", "q4_62"))
            $errors["q4_63"] = "Required if had gestational diabetes";

        //q4-66
        if (multSelect($fields, "q4_66", "q4_65_f"))
            $errors["q4_66"] = "Required if had genital herpes";

        //        if (multSelect($fields, "q4_67", "q4_65_y"))
        //              $errors["q4_67"] = "Required if had venerial/genital warts";



        $letters = array("a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x");

        //q4-68, q4-69
        for ($i=0; $i<24; $i++)
        {
            if($fields["q4_65_$letters[$i]"] == "01_yes")
            {	
                if (empty($fields["q4_68_1"]))	
                    $errors["q4_68_1"] = "Required if had any of the above infections";
                if ($fields["q4_68_select_1"] == array(0=>null) || (empty($fields["q4_68_select_1"])))
                    $errors["q4_68_select_1"] = "You must specify month(s)";
                if (empty($fields["q4_69"]))
                    $errors["q4_69"] = "Required if had any of the above infections";
                break;
            }
        }


        //q4-71, q4-72
        for ($i=0; $i<13; $i++)
        {
            if($fields["q4_70_$letters[$i]"] == "01_yes")
            {
                if(empty($fields["q4_71_1"]))
                    $errors["q4_71_1"] = "Required if had any of the above illnesses";
                if ($fields["q4_71_select_1"] == array(0=>null) || (empty($fields["q4_71_select_1"])))
                    $errors["q4_71_select_1"] = "You must specify month(s)";
                if(empty($fields["q4_72"]))
                    $errors["q4_72"] = "Required if had any of the above illnesses";
                break;
            }
        }

        return $errors;
    }




    function _page8(){   // ========================================================


        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('header', null, "Section 4. PROBAND PREGNANCY <br /><br /> (PART 4 OF 4)");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('header', null, "<b/>Oral/Dental Disease");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<b><i>Now I am going to ask you about some oral or dental diseases that you might have had during that pregnancy.</i></b>");
        $this->form->addElement('static', null, "<br/>");

        //function with more complex rules
        $this->form->addFormRule(array(&$this,'rulesPage8'));

        //q4-73
        $this->form->addElement("select", "q4_73", "4-73. Between [-3] and [DOPB], did a doctor or dentist ever tell you that you had gingivitis or periodontitis?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 4-80");
        $this->form->addElement('static', null, "<br/>");

        //q4-74
        $this->form->addElement("select", "q4_74", "4-74. Did you take any medication for the gingivitis or periodontitis between [-3] and [DOPB]?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q4_74", array("q4_73{@}=={@}01_yes"), "Required if had gingivitis or periodontitis");
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 4-77");
        $this->form->addElement('static', null, "<br/>");

        //q4-75
        $this->form->addElement('static', null, "4-75. What medicine did you take?");
        $this->form->addElement('static', null, $this->indent . "<i>Probe: anything else?</i>");
        $this->form->addElement('static', null, $this->indent . "<i>If can't recall, refer to <b> List 8a</b> in prep guide and read drug list:</i>");

        for ($i=1; $i<4; $i++)
        {
            $this->form->addElement('static', null, "<br/>");

            $this->form->addElement("select", "q4_75_{$i}", $this->indent . "MED #{$i}:", array(NULL=>"", "13" => "13 Clindamycin", "16" => "16 Doxycycline", "24 Metronidazole", "25 Minocyline", "29 Penicillin", "97_other" =>"97 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

            $this->addTextAreaElementRD("q4_75_other{$i}", $this->indent . "If you selected [Other], please specify:");
            $this->XINRegisterRule("q4_75_other{$i}", array("q4_75_{$i}{@}=={@}97_other"), "You must specify other", "q4_75_other{$i}_group");
        }


        $this->XINRegisterRule("q4_75_1", array("q4_74{@}=={@}01_yes"), "Required if taken medication");
        $this->XINRegisterRule("q4_75_2", array("q4_75_2{@}=={@}NEVER_REQUIRED"));
        $this->XINRegisterRule("q4_75_3", array("q4_75_3{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement('static', null, "<br/>");
        $this->addTextAreaElementRD('q4_75_additional', $this->indent . "Additional:");
        $this->XINRegisterRule("q4_75_additional", array("q4_75_additional{@}=={@}NEVER_REQUIRED"), "q4_75_additional_group"); 
        $this->form->addElement('static', null, "<b>For <u>each</u> medication given in 4-75, go to 4-76</b>");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


        //q4-76
        $this->form->addElement('static', null, "4-76. During which months from [-3] to [DOPB] did you take [MEDICATION]?");  

        for ($i=1; $i<4; $i++)
        {
            $this->form->addElement("select", "q4_76_m_{$i}",   $this->indent . "MED #{$i} (Select all that apply):", $this->negThreeToTen, "multiple size = '5'");
        } 


        for ($i=1; $i<4; $i++)
        {
            $this->form->addElement("select", "q4_76_m{$i}",   $this->indent . "Other MED #{$i} (Select all that apply):", $this->negThreeToTen, "multiple size = '5'");
        }

        $this->XINRegisterRule("q4_76_m1", array("q4_73{@}=={@}01_yes"), "Required if taken medication");
        $this->XINRegisterRule("q4_76_m2", array("q4_76_m2{@}=={@}NEVER_REQUIRED"));
        $this->XINRegisterRule("q4_76_m3", array("q4_76_m3{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement('static', null, "<br/>");

        //q4-77
        $this->form->addElement("select", "q4_77", "4-77. Did you have any treatment other than antibiotics for gingivitis or periodontitis between [-3] and [DOPB]?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q4_77", array("q4_73{@}=={@}01_yes"), "Required if had gingivitis or periodontitis");
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 4-80");
        $this->form->addElement('static', null, "<br/>");


        //q4-78
        $this->form->addElement("select", "q4_78", "4-78. What treatments did you have? Was it...",  array(NULL=>"", "01" => "01 Root planing and scaling", "02" => "02 Gingival curettage", "03" => "03  Splinting", "04_other" => "04 Other ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->addTextAreaElementRD('q4_78_other', $this->indent . "If you selected [Other], please specify (Other #1):");
        $this->addTextAreaElementRD('q4_78_other2', $this->indent . "If you selected [Other], please specify (Other #2):");
        $this->XINRegisterRule("q4_78", array("q4_77{@}=={@}01_yes"), "Required if had treatment");
        $this->XINRegisterRule("q4_78_other", array("q4_78{@}=={@}04_other"), "You must specify other", "q4_78_other_group"); 
        $this->XINRegisterRule("q4_78_other2", array("q4_78_other2{@}=={@}NEVER_REQUIRED"), "q4_78_other2_group"); 
        $this->form->addElement('static', null, "<br/>");


        //q4-79
        $this->form->addElement("select", "q4_79", "4-79. During which months from [-3] to [DOPB] did you get the treatment? (Select all that apply):", $this->negThreeToTen , "multiple size = '5'");  
        $this->XINRegisterRule("q4_79", array("q4_77{@}=={@}01_yes"), "Required if had treatment");
        $this->form->addElement('static', null, "<br/>");

        $this->form->addElement('header', null, "<b/>Injuries");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<b><i>The next few questions are about any injuries that you might have had during your pregnancy with [PROBAND].</i></b>");
        $this->form->addElement('static', null, "<br/>");


        //q4-80
        $this->form->addElement("select", "q4_80", "4-80. During your pregnancy with [PROBAND], did you have an injury that required medical attention?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 4-89");
        $this->form->addElement('static', null, "<br/>");


        //q4-81
        $this->addTextAreaElementRD('q4_81', "4-81. What injury did you have?");
        $this->XINRegisterRule("q4_81", array("q4_80{@}=={@}01_yes"), "Required if had injury", "q4_81_group");
        $this->form->addElement('static', null, "<br/>");


        //q4-82
        $this->form->addElement("select", "q4_82", "4-82 Between [-3] and [DOPB], during which month did this injury happen?", $this->negThreeToTen);
        $this->XINRegisterRule("q4_82", array("q4_80{@}=={@}01_yes"), "Required if had injury");
        $this->form->addElement('static', null, "<br/>");

        //q4-83
        $this->form->addElement("select", "q4_83", "4-83. Did you ever lose consciousness because of this injury?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q4_83", array("q4_80{@}=={@}01_yes"), "Required if had injury");
        $this->form->addElement('static', null, "<br/>");

        //q4-84
        $this->form->addElement("select", "q4_84", "4-84. Was medication taken for the injury?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q4_84", array("q4_80{@}=={@}01_yes"), "Required if had injury");
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 4-85");
        $this->form->addElement('static', null, "<br/>");


        //q4-85
        $this->form->addElement("select", "q4_85", "4-85. During your pregnancy with [PROBAND], did you have any other injury that required medical attention?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q4_85", array("q4_80{@}=={@}01_yes"), "Required if had injury");
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 4-89");
        $this->form->addElement('static', null, "<br/>");

        //q4-86
        $this->addTextAreaElementRD('q4_86', "4-86. What was the other injury you had?");
        $this->XINRegisterRule("q4_86", array("q4_85{@}=={@}01_yes"), "Required if had injury", "q4_86_group");
        $this->form->addElement('static', null, "<br/>");

        //q4-87
        $this->form->addElement("select", "q4_87", "4-87. Between [-3] and [DOPB], during which month did this other injury happen?",  $this->negThreeToTen);
        $this->XINRegisterRule("q4_87", array("q4_85{@}=={@}01_yes"), "Required if had injury");
        $this->form->addElement('static', null, "<br/>");

        //q4-88
        $this->form->addElement("select", "q4_88", "4-88. Did you ever lose consciousness because of this other injury?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q4_88", array("q4_85{@}=={@}01_yes"), "Required if had injury");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


        $this->form->addElement('header', null, "<b/>Surgery");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<b><i>Now, I'm going to ask you about any surgeries or procedures that you might have had during your pregnancy with [PROBAND].</i></b>");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");

        //q4-89
        $this->form->addElement("select", "q4_89", "4-89. During your pregnancy with [PROBAND], did you have any dental, medical, or surgical procedures that required the use of general or local anesthesia?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 4-93");
        $this->form->addElement('static', null, "<br/>");

        //q4-90
        $this->form->addElement('static', null, "4-90. What procedure(s) did you have done?");
        $this->form->addElement('static', null, $this->indent . "<i>Probe: Any others?</i>");	
        $this->addTextAreaElementRD('q4_90_p1', $this->indent . "Please specify procedure #1:");
        $this->XINRegisterRule("q4_90_p1", array("q4_89{@}=={@}01_yes"), "Required if had procedures", "q4_90_p1_group"); 
        $this->addTextAreaElementRD('q4_90_p2', $this->indent . "Procedure #2:");
        $this->XINRegisterRule("q4_90_p2", array("q4_90_p2{@}=={@}NEVER_REQUIRED"), "q4_90_p2_group");
        $this->addTextAreaElementRD('q4_90_p3', $this->indent . "Procedure #3:");
        $this->XINRegisterRule("q4_90_p3", array("q4_90_p3{@}=={@}NEVER_REQUIRED"), "q4_90_p3_group");
        $this->addTextAreaElementRD('q4_90_additional', $this->indent . "Additional: ");
        $this->form->addElement('static', null, "<br/>");
        $this->XINRegisterRule("q4_90_additional", array("q4_90_additional{@}=={@}NEVER_REQUIRED"), "q4_90_additional_group"); 


        //q4-91
        $this->form->addElement('static', null, "4-91. For [PROCEDURE], did you have general anesthesia or local anesthesia?");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement("select", "q4_91_p1", $this->indent . "Procedure #1:",  array(NULL=>"", "01" => "01 General", "02" => "02 Local", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement("select", "q4_91_p2", $this->indent . "Procedure #2:",  array(NULL=>"", "01" => "01 General", "02" => "02 Local", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement("select", "q4_91_p3", $this->indent . "Procedure #3:",  array(NULL=>"", "01" => "01 General", "02" => "02 Local", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q4_91_p1", array("q4_89{@}=={@}01_yes"), "Required if had procedures");
        $this->XINRegisterRule("q4_91_p2", array("q4_91_p2{@}=={@}NEVER_REQUIRED")); 
        $this->XINRegisterRule("q4_91_p3", array("q4_91_p3{@}=={@}NEVER_REQUIRED")); 
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, $this->indent . "If you selected [Refused] or [Don't Know] skip to question 4-93");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


        //q4-92
        $this->form->addElement("static", null,  "4-92. In which month between [-3] and [DOPB] did you receive the anesthesia?");
        $this->form->addElement("select", "q4_92", $this->indent . "Select all that apply:", $this->negThreeToTen, "multiple size = '5'");
        $this->XINRegisterRule("q4_92", array("q4_92{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");

        $this->form->addElement('static', null, "<b/>Other Procedures");
        $this->form->addElement('static', null, "<br/>");


        //q4-93
        $this->form->addElement('static', null, "4-93. During your pregnancy with [PROBAND], did you have");

        $aToG = array("a" => "A. X-rays, including dental", "b" => "B. Mammogram", "c" => "C. CT/CAT scans", "d" => "D. MRI/magnetic resonance", "e" => "E. Radionuclide study or scan", "f" => "F. Radiation treatments or scan", "g" =>"G. Other");
        reset($aToG);

        while(list($field, $label) = each($aToG)){

            $this->form->addElement("select", "q4_93_{$field}", $this->indent . "{$label}:", array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        }

        $this->addTextAreaElementRD("q4_93_other", $this->indent . "If you selected [Other], please specify:");
        $this->XINRegisterRule('q4_93_other', array("q4_93_g{@}=={@}01_yes"), "You must specify other", "q4_93_other_group");
        $this->form->addElement('static', null, $this->indent . "If you selected [yes] for mammogram in 4-93, go to question 4-107");
        $this->form->addElement('static', null, $this->indent . "If you selected [Yes] for any other procedure in 4-93, go to question 4-94");
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] for <u>all</u>, go to question 4-96");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");



        //q4_94
        $this->form->addElement('static', null, "4-94. What part of your body was tested? Enter procedure as indicated above and specify body part:");
        $this->form->addElement('static', null, "<br/>");

        for ($i=1; $i<4; $i++)
        {
            $this->form->addElement("select", "q4_94_{$i}", $this->indent . "<b>Procedure #{$i}:</b>", array(NULL=>"", "a" => "A. X-rays, including dental", "b" => "B. Mammogram", "c" => "C. CT/CAT scans", "d" => "D. MRI/magnetic resonance", "e" => "E. Radionuclide study or scan", "f" => "F. Radiation treatments or scan", "g" =>"G. Other", "88_refused"=>"88 Refused", "99_Do_not_know"=>"99 Do not know", "not_answered"=>"Not Answered"));

            $this->addTextAreaElementRD("q4_94_{$i}_other", $this->indent . $this->indent . "If you selected [Other], please specify:");
            $this->XINRegisterRule("q4_94_{$i}_other", array("q4_94_{$i}{@}=={@}g"), "You must specify other", "q4_94_{$i}_other_group");
            $this->addTextAreaElementRD("q4_94_{$i}_body", $this->indent . $this->indent . "Body Part Tested:");
            $this->XINRegisterRule("q4_94_{$i}", array("q4_94_{$i}{@}=={@}NEVER_REQUIRED"));	
            $this->XINRegisterRule("q4_94_{$i}_body", array("q4_94_{$i}_body{@}=={@}NEVER_REQUIRED"), "q4_94_{$i}_body_group"); 

        }

        $this->form->addElement('static', null, "<br/>");


        //q4-95
        $this->form->addElement('static', null, "4-95. During which month between [-3] and [DOPB] was the [PROCEDURE] done? Enter procedure as indicated above and specify month:");
        $this->form->addElement('static', null, "<br/>");

        for ($i=1; $i<4; $i++)
        {
            $this->form->addElement("select", "q4_95_{$i}", $this->indent . "<b>Procedure #{$i}:</b>", array(NULL=>"", "a" => "A. X-rays, including dental", "b" => "B. Mammogram", "c" => "C. CT/CAT scans", "d" => "D. MRI/magnetic resonance", "e" => "E. Radionuclide study or scan", "f" => "F. Radiation treatments or scan", "g" =>"G. Other", "88_refused"=>"88 Refused", "99_Do_not_know"=>"99 Do not know", "not_answered"=>"Not Answered"));

            $this->addTextAreaElementRD("q4_95_{$i}_other", $this->indent . $this->indent . "If you selected [Other], please specify:");
            $this->XINRegisterRule("q4_95_{$i}_other", array("q4_95_{$i}{@}=={@}g"), "You must specify other", "q4_95_{$i}_other_group");

            $this->XINRegisterRule("q4_95_{$i}", array("q4_95_{$i}{@}=={@}NEVER_REQUIRED"));

            $this->form->addElement("select", "q4_95_month_{$i}", $this->indent . $this->indent . "Please select month:",  $this->negThreeToTen, "multiple size = '5'");
            $this->XINRegisterRule("q4_95_month_{$i}", array("q4_95_month_{$i}{@}=={@}NEVER_REQUIRED"));
            $this->form->addElement('static', null, "<br/>");
        }

        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('header', null, "<b/>Medication Use");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<b/>This should be asked about medications not already reported before.");

        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<b><i>We are interested in medications, including over-the-counter medications that you might have taken during your pregnancy with [PROBAND].</i></b>");
        $this->form->addElement('static', null, "<br/>");

        $this->form->addElement('static', null, "<b><i>Please refer to <u>LISTS 8A through 8N</u> in your preparatory guide so that we can get the most accurate information possible.</i></b>");
        $this->form->addElement('static', null, "<br/>");

        $this->form->addElement('static', null, "<b><i>The medications in the list have been organized as best as possible by condition so please look for the heading and find your medication under that.</i></b>");
        $this->form->addElement('static', null, "<br/>");

        $this->form->addElement('static', null, "<b><i>If you do not see your medication, please look under the 'other medications' category. If your medication is not listed at all, we still want you to tell us about it. Medications can be in pill form, nasal spray, patches, creams, etc.</i</b>");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");

        //q4-96
        $this->form->addElement('static', null, "4-96. Between [-3] and [DOPB] did you take any medications for the following conditions?");

        $aToJ = array("a" => "A. General headaches", "b" => "B. Back pain", "c" => "C.Chest pain ", "d"=> "D. Cold", "e" => "E. Acne", "f" => "F. For dieting", "g" =>"G. Heartburn", "h" =>"H. To relieve constipation or diarrhea", "i" =>"I. Sleep disorder", "j" =>  "J. Other");

        foreach ($aToJ as $field => $label){
            $this->form->addElement("select", "q4_96_{$field}", $this->indent . "{$label}:", array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        }

        reset($aToJ);
        $this->addTextAreaElementRD('q4_96_other', $this->indent . "If you selected [Other], please specify:");
        $this->XINRegisterRule('q4_96_other', array("q4_96_j{@}=={@}01_yes"), "You must specify other", "q4_96_other_group");
        $this->form->addElement('static', null, $this->indent . "If you selected [Yes] for any condition in 4-96, go to question 4-97");
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] for <u>all</u>, skip to the next section");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


        //q4-97
        $this->form->addElement('static', null, "4-97. What medicine did you take for [CONDITION]? Specify conditions previously indicated and enter the name(s) of the medication(s) used:");
        $this->form->addElement('static', null, $this->indent . "<i>Refer to <b>List 8a</b> through <b>8n</b> in prep guide.</i>");

        for ($i=1; $i<6; $i++){

            $this->form->addElement('static', null, "<br/>");
            $this->form->addElement('static', null, "<br/>");
            $this->form->addElement("select", "q4_97_{$i}", $this->indent . "<b>Condition #{$i}</b>", array(NULL=>"") + $aToJ + array("88_refused"=>"88 Refused", "99_Do_not_know"=>"99 Do not know", "not_answered"=>"Not Answered")); 

            $this->XINRegisterRule("q4_97_{$i}", array("q4_97_{$i}{@}=={@}NEVER_REQUIRED"));

            for ($j=1; $j<4; $j++)
            {
                $this->addTextAreaElementRD("q4_97_{$i}_med{$j}", $this->indent . $this->indent . "Medication #{$j}.");
                $this->XINRegisterRule("q4_97_{$i}_med{$j}", array("q4_97_{$i}_med{$j}{@}=={@}NEVER_REQUIRED"), "q4_97_{$i}_med{$j}_group");
            }
        }

        $this->form->addElement('static', null, "<br/>");



        //q4-98
        $this->form->addElement('static', null, "4-98. Between [-3] and [DOPB], which months did you take the medication? Select condition as previously indicated, specify medication used, and select all months that apply:");

        for ($i=1; $i<9; $i++){

            $this->form->addElement('static', null, "<br/>");

            $this->form->addElement("select", "q4_98_{$i}", $this->indent . "<b>Condition #{$i}:</b>", array(NULL=>"") + $aToJ + array("88_refused"=>"88 Refused", "99_Do_not_know"=>"99 Do not know", "not_answered"=>"Not Answered"));
            $this->XINRegisterRule("q4_98_{$i}", array("q4_98_{$i}{@}=={@}NEVER_REQUIRED"));


            //			$this->addTextAreaElementRD("q4_98_{$field}_other", $this->indent . "If you selected [Other], please specify:");
            //			$this->XINRegisterRule("q4_98_{$field}_other", array("q4_98_cond_{$field}{@}=={@}j. Other"), "You must specify other");
            //		$this->form->addRule(array("q4_98_cond_{$field}_other", "q4_98_cond_{$field}"), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'j. Other'));
            //		$this->setRequired("q4_98_cond_{$field}_other"); //*****************************


            $this->addTextAreaElementRD("q4_98_{$i}_med", $this->indent . $this->indent . "Medication #{$i}:");
            $this->form->addElement("select", "q4_98_{$i}_month",   $this->indent . $this->indent . " Please select all months that apply:",  $this->negThreeToTen, "multiple size = '5'");
            $this->XINRegisterRule("q4_98_{$i}_med", array("q4_97_{$i}_med1{@}!={@}"), "Required if took medication", "q4_98_{$i}_med_group");
            $this->XINRegisterRule("q4_98_{$i}_month", array("q4_97_{$i}_med1{@}!={@}"), "Required if took medication");
            $this->form->addElement('static', null, "<br/>");
        }

        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('header', null, "END Section 4.");
        $this->form->addElement('static', null, "<br/>");


    } //end function _page8() ======================================================



    function rulesPage8($fields)
    {
        $errors = array();


        function multSelect($fields, $question1, $question2, $answer)
        {
            return (($fields[$question1] == array(0=>null) && $fields[$question2] == $answer) || (empty($fields[$question1])) && $fields[$question2] == $answer);
        }

        //q4-76
        if (multSelect($fields, "q4_76_m_1", "q4_74", "01_yes"))
            $errors["q4_76_m_1"] = "Required if took medication for gingivitis or periodontitis";

        //q4-79
        if (multSelect($fields, "q4_79", "q4_77", "01_yes"))
            $errors["q4_79"] = "Required if received treatment for gingivitis or periodontitis";

        //q4-92
        if (multSelect($fields, "q4_92", "q4_91_p1", ("01"||"02")))
            $errors["q4_92"] = "You must specify month(s)";

        $letterOptions = array("a", "b", "c", "d", "e", "f", "g", "h", "i", "j");


        //q4-94, q4-95
        for ($i=0; $i<count($letterOptions); $i++)
        {

            if (multSelect($fields, "q4_95_month_1", "q4_93_$letterOptions[$i]", "01_yes") && $letterOptions[$i] != "b")
                $errors["q4_95_month_1"] = "You must specify month(s)";


            if ($fields["q4_93_$letterOptions[$i]"] == "01_yes" && $letterOptions[$i]!= "b" )
            {
                if (empty($fields["q4_94_1"]))
                    $errors["q4_94_1"] = "Required if had any of the above procedures";

                if (empty($fields["q4_94_1_body"]) && empty($fields["q4_94_1_body_status"]))
                    $errors["q4_94_1_body_group"] = "Required if had any of the above procedures";


                if (empty($fields["q4_95_1"]))
                {
                    $errors["q4_95_1"] = "Required if had any of the above procedures";
                    break;
                }					
            }
        }


        //q4-97, q4-98
        for ($i=0; $i<count($letterOptions); $i++)
        {
            if (multSelect($fields, "q4_98_1_month", "q4_96_$letterOptions[$i]", "01_yes"))
                $errors["q4_98_1_month"] = "You must specify month(s)";

            if ($fields["q4_96_$letterOptions[$i]"] == "01_yes")
            {
                if (empty($fields["q4_97_1"]))
                    $errors["q4_97_1"] = "Required if had any of the above conditions";

                if (empty($fields["q4_97_1_med1"]) && empty($fields["q4_97_1_med1_status"]))
                    $errors["q4_97_1_med1_group"] = "You must specify medication taken";

                if (empty($fields["q4_98_1"]))
                    $errors["q4_98_1"] = "Required if had any of the above conditions";

                if (empty($fields["q4_98_1_med"]) && empty($fields["q4_98_1_med_status"]))
                {
                    $errors["q4_98_1_med_group"] = "You must specify medication taken";
                    break;
                }
            }
        }	

        return $errors;
    }


}

?>
