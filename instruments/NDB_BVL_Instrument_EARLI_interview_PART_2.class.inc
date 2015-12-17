<?php

require_once 'HTML/QuickForm.php';
require_once 'HTML/QuickForm/Renderer/Array.php';
require_once("RequiredIfGroup.inc");
require_once('RequiredIf.inc');
require_once('NDB_BVL_Instrument_EARLI_interview.class.inc');

class NDB_BVL_Instrument_EARLI_interview_PART_2 extends NDB_BVL_Instrument_EARLI_interview {


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
        $this->testName = "EARLI_interview_PART_2";           // test_names.Test_name
        $this->table = 'EARLI_interview_PART_2';              // name of table containing data keyed by commentID
        $this->commentID = $commentID;

        $db =& Database::singleton();
        $fertilityTreatment = $db->selectOne("SELECT q5_16 FROM EARLI_interview_PART_2 WHERE CommentID='$commentID'");
        if ($fertilityTreatment == '01_yes')
            $this->_requiredElements = array('interview_time','q5_3', 'q5_17', 'q5_32', 'q5_58', 'q5_68', 'q5_76_a', 'q5_88', 'q5_95', 'q5_110_a', 'q6_1', 'q6_85', 'q7_2_m', 'q7_19', 'q7_37_1');
        else
            $this->_requiredElements = array('interview_time','q5_3','q5_32', 'q5_58', 'q5_68', 'q5_76_a', 'q5_88', 'q5_95', 'q5_110_a', 'q6_1', 'q6_85', 'q7_2_m', 'q7_19', 'q7_37_1');



        //The array of dates/timestamps to convert to database dates/timestamps
        $this->dateTimeFields=array("interview_date", "q5_1", "q5_42_date", "q5_45_date", "q5_49_date", "q5_52_date", "q5_57_date");

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
        
        /* Commenting out, this will be inherited from base class
        $this->_doubleDataEntryDiffIgnoreColumns = array('CommentID', 'UserID', 'Testdate',
                                                         'Window_Difference', 'Candidate_Age',
                                                         'Data_entry_completion_status'
                                                        );
        */
        // setup the form
        $this->_setupForm();

        $this->localDefaults = array();

        $this->_selectMultipleElements = array();


        // From Mr. David Brownlee:
        //The array of selects with multiple answers allowed
        //Any HTML_Quickform multiple selects must be listed here
        //Usually this appears at the beginning of the file in the setup() function

        $this->_selectMultipleElements = array_merge($this->_selectMultipleElements, array("q5_8_1", "q5_8_2", "q5_8_3", "q5_8_4", "q5_8_5", "q5_11_1", "q5_11_2", "q5_11_3", "q5_11_4", "q5_11_5", 'q5_33', "q5_36", "q5_39", "q5_59", "q5_65", "q5_69", "q5_73", "q5_77", "q5_78", "q5_79_m_1", "q5_79_m_2", "q5_79_m_3", "q5_82_1_med1", "q5_82_1_med2", "q5_82_1_med3", "q5_82_2_med1", "q5_82_2_med2", "q5_82_2_med3", "q5_82_3_med1", "q5_82_3_med2", "q5_82_3_med3", "q5_84_1_m", "q5_84_2_m", "q5_84_3_m", "q5_87_1_med1", "q5_87_1_med2", "q5_87_1_med3", "q5_87_2_med1", "q5_87_2_med2", "q5_87_2_med3", "q5_87_3_med1", "q5_87_3_med2", "q5_87_3_med3", "q5_91_1", "q5_91_2", "q5_91_3", "q5_94", "q5_97", "q5_101_1", "q5_101_2", "q5_101_3", "q5_104", "q5_109", "q5_112_month1", "q5_112_month2", "q5_112_month3", "q5_115_months1", "q5_115_months2", "q5_115_months3", "q5_115_months4", "q5_115_months5", "q5_115_months6", "q6_3", "q6_7", "q6_11", "q6_15", "q6_19", "q6_23", "q6_27", "q6_31", "q6_35", "q6_39", "q6_43", "q6_47", "q6_51", "q6_55", "q6_59", "q6_63", "q6_67", "q6_71", "q6_75", "q6_79", "q6_83", "q6_107", "q7_16", "q7_18", "q7_25_p1", "q7_25_p2", "q7_25_p3", "q7_29_p1", "q7_29_p2", "q7_29_p3", "q7_32", "q7_34", "q7_36", "q7_38_1", "q7_38_2", "q7_38_3","q7_38_4", "q7_38_5", "q7_40_1", "q7_40_2", "q7_40_3", "q7_40_4", "q7_40_5", "q7_40_6"));

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
        $this->form->addElement('header', 'instrument_title', "EARLI Maternal Interview Sections 5-7");

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



    function _page9(){   // ========================================================


        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('header', null, "Section 5: SIBLING PREGNANCY <br /><br />(PART 1 OF 9)");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");

        $this->form->addElement('static', null, "<b/>Now I have some questions specific to your pregnancy with the younger sibling of your child with ASD (Ask name of sibling).");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");

        //function with more complex rules
        $this->form->addFormRule(array(&$this,'rulesPage9'));


        //q5-1
        $this->addCustomDateElement('q5_1', $this->indent . "5-1. What date did the doctor give you as the expected due date?", $this->dateOptions2007);
        $this->form->addElement('static', null, $this->indent . "<i>If date given, record in Pregnancy Calendar, then go to question 5-2</i>");
        $this->form->addElement('static', null, "<br/>");


        //q5-2
        $this->addTextAreaElementRD('q5_2_t', $this->indent . "5-2. How much did you weigh before you were pregnant with the sibling of your child with ASD? Please specify (in lbs):");
        //	$this->form->addRule(array('q5_2_t', 'q5_2'), 'Please specify.', 'requiredIf', array('operator'=>'==', 'value'=>'00'));
        //	$this->setRequired('q5_2_t');
        $this->form->addElement('static', null, "<br/>");


        //q5-3
        $this->form->addElement("select", "q5_3", "5-3. How much weight did you gain or lose with your pregnancy with the sibling of your child with ASD?",  array(NULL=>"", "00_wg_kg" => "00 Specify Weight gain (in kgs)", "00_wg_lb" => "00 Specify Weight gain (in lbs)", "00_wl_kg" => "00 Specify Weight loss (in kgs)",  "00_wl_lb" => "00 Specify Weight loss (in lbs)", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        $this->addNumericElementRD('q5_3_wg_kg', $this->indent . "If you selected [00 Specify Weight gain (in kgs)] please specify Weight gain (kgs):");
        $this->addNumericElementRD('q5_3_wg_lb', $this->indent . "If you selected [00 Specify Weight gain (in lbs)] please specify Weight gain (lbs):");
        $this->addNumericElementRD('q5_3_wl_kg', $this->indent . "If you selected [00 Specify Weight loss (in kgs)] please specify Weight loss (kgs):");
        $this->addNumericElementRD('q5_3_wl_lb', $this->indent . "If you selected [00 Specify Weight loss (in lbs)] please specify Weight loss (lbs):");
        $this->XINRegisterRule('q5_3_wg_kg', array("q5_3{@}=={@}00_wg_kg"), "You must specify weight gain (in kg)", "q5_3_wg_kg_group");
        $this->XINRegisterRule('q5_3_wg_lb', array("q5_3{@}=={@}00_wg_lb"), "You must specify weight gain (in lb)", "q5_3_wg_lb_group");
        $this->XINRegisterRule('q5_3_wl_kg', array("q5_3{@}=={@}00_wl_kg"), "You must specify weight loss (in kg)", "q5_3_wl_kg_group");
        $this->XINRegisterRule('q5_3_wl_lb', array("q5_3{@}=={@}00_wl_lb"), "You must specify weight loss (in lb)", "q5_3_wl_lb_group");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");

        //q5-4
        $this->form->addElement('static', null, "5-4. What was your height without shoes?");
        $this->form->addElement("select", "q5_4_f", $this->indent .  "Feet:",  array(NULL=>"",  "1" => "1", "2" => "2", "3" => "3", "4", "5", "6", "7", "88_Refused" => "88 Refused", "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement("select", "q5_4_i", $this->indent .  "Inches:",  array(NULL=>"",  "0", "1" => "1", "2" => "2", "3" => "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "88_Refused" => "88 Refused", "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, "<br/>");


        //q5-5
        $this->form->addElement("static", null, "5-5. How far along were you when you found out you were pregnant with [DOBS]?");
        $this->form->addElement("select", "q5_5_w", $this->indent .  "Weeks:",  array(NULL=>"") + array_combine(range(0,38), range(0,38)) + array("88_Refused" => "88 Refused", "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement("select", "q5_5_m", $this->indent .  "or Months:",  array(NULL=>"",  "0", "1" => "1", "2" => "2", "3" => "3", "4", "5", "6", "7", "8", "9", "88_Refused" => "88 Refused", "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<i>Refer to the <b>Pregnancy Calendar</b></i>");
        $this->form->addElement('static', null, "<br/>");


        //q5-6
        $this->form->addElement("select", "q5_6", "5-6. Between [-3] and [DOBS] did you use any birth control pills or morning after pills?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 5-9");
        $this->form->addElement('static', null, "<br/>");


        //q5-7
        $this->form->addElement('static', null, "5-7. What was the name of the pills?");
        $this->form->addElement('static', null, "<br/>");

        for ($i = 1; $i<6; $i++)
        {
            $this->form->addElement("select", "q5_7_med_{$i}", $this->indent . "Pill #{$i}:", array(NULL=>"", "01" => "01 Alesse", "02" => "02 Brevicon", "03" => "03  Demulen", "04" => "04 Desogen", "05" => "05 Estrostep", "06" => "06 Levlen", "07" => "07 Levlite", "08" => "08 Levora", "09" => "09 Loestrin", "10" => "10 Lo/Ovral", "11" => "11 Micronor", "12" => "12 Mircette", "13" => "13 Modicon", "14" => "14 Necon", "15" => "15 Nordette", "16" => "16 Norinyl", "17" => "17 Nor-Q.D", "18" => "18 Ortho-Cept", "19" => "19 OrthoCyclen", "20" => "20 Ortho-Novum", "21" => "21 Ortho Tri-Cyclen", "22" => "22 Ovcon", "23" => "23 Ovral", "24 Tri-Levlen", "25 Tri-Norinyl", "26 Triphasil", "27 Trivora", "28 Zovia",  "29_other" => "29 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

            $this->addTextAreaElementRD("q5_7_med_{$i}_other", $this->indent . "If you selected [Other], please specify:");
            $this->XINRegisterRule("q5_7_med_{$i}_other", array("q5_7_med_{$i}{@}=={@}29_other"), "You must specify other", "q5_7_med_{$i}_other");
        }

        $this->XINRegisterRule("q5_7_med_1", array("q5_6{@}=={@}01_yes"), "Required if used birth control or morning after pills");

        for ($i = 2; $i<6; $i++)
            $this->XINRegisterRule("q5_7_med_{$i}", array("q5_7_med_{$i}{@}=={@}NEVER_REQUIRED"));

        $this->form->addElement('static', null, "<br/>");



        //q5-8
        $this->form->addElement('static', null, "5-8. Which months between [-3] and [DOBS] were you using [PILL NAME]?");

        for ($i=1; $i<6; $i++)
        {

            $this->form->addElement("select", "q5_8_{$i}", $this->indent . "Pill {$i} (Select all that apply):",  array(NULL=>"", "-3"=>"-3", "-2"=>"-2", "-1"=>"-1", "01"=>"01", "02"=>"02", "03" => "03 ", "04" => "04", "05" => "05", "06" => "06",  "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered" => "Not Answered"), "multiple size = '5'");
            $this->XINRegisterRule("q5_8_{$i}", array("q5_8_{$i}{@}=={@}NEVER_REQUIRED"), "q5_8_{$i}_group");

        }

        $this->form->addElement('static', null, "<br/>");


        //q5-9
        $this->form->addElement("select", "q5_9", "5-9. Between [-3] and [DOBS] did you use any other method of contraception to avoid getting pregnant?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 5-12");
        $this->form->addElement('static', null, "<br/>");


        //q5-10
        $this->form->addElement('static', null, "5-10. What method of contraception were you using?");
        $this->form->addElement('static', null, "<i> If can't recall, ask to refer to <b>List 3</b> in prep guide and choose from the following list:</i>");
        $this->form->addElement('static', null, "<br/>");


        for ($i=1; $i<6; $i++)
        {
            $this->form->addElement("select", "q5_10_m{$i}", $this->indent .  "METHOD #{$i}:",  array(NULL=>"", "01" => "01 Condoms (male or female)", "02" => "02 Depo-Provera", "03" => "03  Diaphram/cervical cap", "04" => "04 Intrauterine device (IUD)", "05" => "05 Norplant", "06" => "06 Spermicide", "07" => "07 Sponge", "08_other" => "08 Other", "88 Refused", "99" => "99 Do not know", "not_answered"=>"Not Answered"));
            $this->addTextAreaElementRD("q5_10_m{$i}_other", $this->indent . "If you selected [Other], please specify:");
            $this->XINRegisterRule("q5_10_m{$i}_other", array("q5_10_m{$i}{@}=={@}08_other"), "You must specify other", "q5_10_m{$i}_other_group");
        }


        $this->XINRegisterRule("q5_10_m1", array("q5_9{@}=={@}01_yes"), "Required if used other contraception method");

        for ($i=2; $i<6; $i++)
            $this->XINRegisterRule("q5_10_m{$i}", array("q5_10_m{$i}{@}=={@}NEVER_REQUIRED"));

        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


        //q5-11
        $this->form->addElement('static', null, "5-11. Which months between [-3] and [DOPB] were you using [CONTRACEPTIVE METHOD]? For each contraceptive method, select all that apply:");  
        $this->form->addElement('static', null, "<br/>");


        for ($i=1; $i<6; $i++)
        {
            $this->form->addElement('select', "q5_11_{$i}", $this->indent . "Method #{$i}:",  array(NULL=>"","-3", "-2", "-1", "1", "2", "3", "4", "5", "6", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"), "multiple size = '5'");
            $this->XINRegisterRule("q5_11_{$i}", array("q5_11_{$i}{@}=={@}NEVER_REQUIRED"));
        }

        $this->form->addElement('static', null, "<br/>");


        //q5-12
        $this->form->addElement('static', null, "5-12. If no contraceptives were used between [-3] and [DOBS] (i.e., 5-6 and 5-9 = No, Refused, or Do not know), go to question 5-13");
        $this->form->addElement('static', null, "If any contraceptive was used between [-3] and [DOBS] (i.e., 5-6 or 5-9 = Yes), go to question 5-14");
        $this->form->addElement('static', null, "<br/>");


        //q5-13
        $this->form->addElement("select", "q5_13", "5-13. Did you...<i>(read choices)</i>",  array(NULL=>"", "01" => "01 Stop using contraception to get pregnant", "02" => "02 Get pregnant during an interruption in using contraception", "03" => "03  Not use contraception before this pregnancy", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [01 Stop using contraception to get pregnant], go to question 5-15");
        $this->form->addElement('static', null, $this->indent . "If you selected [02 Get pregnant during an interruption in using contraception], go to question 5-32");
        $this->XINRegisterRule("q5_13", array("q5_6{@}!={@}01_yes", "q5_9{@}!={@}01_yes"), "Required if no contraceptives used");
        $this->form->addElement('static', null, "<br/>");


        //q5-14
        $this->form->addElement("select", "q5_14", "5-14. Did you get pregnant while consistently using contraception?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q5_14", array("q5_14{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement('static', null, $this->indent . "If you selected [Yes], go to question 5-32");
        $this->form->addElement('static', null, "<br/>");


        //q5-15a
        $this->form->addElement("select", "q5_15a", "5-15a. At the time you became pregnant, did you ...?",  array(NULL=>"", "01" => "01 Want to become pregnant then", "02" => "02 Want to wait until later",  "03" => "03 Not want to become pregnant at all", "04" => "04 Didn't care","88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q5_15a", array("q5_15a{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement('static', null, "<br/>");


        //q5-15b
        $this->form->addElement("select", "q5_15b", "5-15b. Before getting pregnant with [SIBLING], did you have regular intercourse for a period of 12 months or more without using contraception?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q5_15b", array("q5_15b{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement('static', null, "<br/>");


        //q5-16
        $this->form->addElement("select", "q5_16", "5-16. Did you use fertility treatment to get pregnant with [SIBLING]?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 5-32");
        $this->XINRegisterRule("q5_16", array("q5_16{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


    } //end function _page9() ======================================================



    function rulesPage9($fields)
    {
        $errors = array();

        function multSelect($fields, $question1, $question2)
        {
            return ($fields[$question1] == array(0=>null) && $fields[$question2] == "01_yes" || (empty($fields[$question1])) && $fields[$question2] == "01_yes");
        }


        //q5-8
        if (multSelect($fields, "q5_8_1", "q5_6"))
            $errors["q5_8_1"] = "You must specify month(s)";

        //q5-11
        if (multSelect($fields, "q5_11_1", "q5_9"))
            $errors["q5_11_1"] = "You must specify month(s)";


        //q5-14
        if (($fields["q5_6"] == "01_yes" || $fields["q5_9"] == "01_yes") && empty($fields["q5_14"]))
            $errors["q5_14"] = "Required if contraceptives were used between [-3] and [DOBS]";


        //q5-15a
        if (($fields["q5_13"] == "01" || ($fields["q5_14"] != "01_yes" && !(empty($fields["q5_14"])))) && empty($fields["q5_15a"]))
            $errors["q5_15a"] = "Required if weren't using contraception when became pregnant";


        //q5-15b
        if (($fields["q5_13"] == "01" || ($fields["q5_14"] != "01_yes"  && !(empty($fields["q5_14"])))) && empty($fields["q5_15b"]))
            $errors["q5_15b"] = "Required if weren't using contraception when became pregnant";

        //q5-16
        if (($fields["q5_13"] == "01" || ($fields["q5_14"] != "01_yes" && !(empty($fields["q5_14"])))) && empty($fields["q5_16"]))
            $errors["q5_16"] = "Required if weren't using contraception when became pregnant";


        return $errors;

    }



    function _page10(){   // ========================================================


        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('header', null, "Section 5: SIBLING PREGNANCY <br /><br />(PART 2 OF 9)");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/> <b/>Assisted Reproduction");
        $this->form->addElement('static', null, "<br/>");

        //function with more complex rules
        $this->form->addFormRule(array(&$this,'rulesPage10'));


        $this->form->addElement('static', null, "<b>Now, I'm going to ask you some detailed questions about what type of help you or your baby's father (we should get his name earlier so we can refer to him by name) may have received to help you get pregnant with the younger sibling of your child with ASD.</b>");
        $this->form->addElement('static', null, "<br/>");

        //q5-17
        $this->form->addElement("select", "q5_17", "5-17. Did you take any medications to help prevent miscarriage with your pregnancy with [SIBLING]?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q5_17", array("q5_17{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 5-19");
        $this->form->addElement('static', null, "<br/>");

        //q5-18
        $this->form->addElement('static', null, "5-18. What medications did you take?");
        $this->form->addElement('static', null, $this->indent . "<i>If respondent can't recall, ask to refer to <b>List 4</b> in prep guide and ask to select from the following list:</i>");
        $this->form->addElement('static', null, "<br/>");


        for ($i=1; $i<6; $i++)
        {

            $this->form->addElement("select", "q5_18_m{$i}", $this->indent. " Med #{$i}:", array(NULL=>"", "01" => "01 Crinonevz", "02" => "02 Prometrium", "03" => "03  Heparin", "04" => "04 Baby aspirin", "05" => "05 IVIg Therapy", "06_steroid" => "06 Steroid treatment", "07_other" => "07 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
            $this->addTextAreaElementRD("q5_18_m{$i}_S{$i}", $this->indent . $this->indent . " If you selected [06 Steroid treatment], please specify STEROID #{$i}:");
            $this->addTextAreaElementRD("q5_18_m{$i}_other", $this->indent . $this->indent . " If you selected [Other], please specify MEDICATION #{$i}:");
            $this->XINRegisterRule("q5_18_m{$i}_S{$i}", array("q5_18_m{$i}{@}=={@}06_steroid"), "You must specify steroid", "q5_18_m{$i}_S{$i}_group");
            $this->XINRegisterRule("q5_18_m{$i}_other", array("q5_18_m{$i}{@}=={@}07_other"), "You must specify other", "q5_18_m{$i}_other_group");
        }

        $this->XINRegisterRule("q5_18_m1", array("q5_17{@}=={@}01_yes"), "Required if took medications");

        for ($i=2; $i<6; $i++)
            $this->XINRegisterRule("q5_18_m{$i}", array("q5_18_m{$i}{@}=={@}NEVER_REQUIRED"));


        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");

        //q5-19
        $this->form->addElement("select", "q5_19", "5-19. Did you take any medications to help you become pregnant? ",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 5-21");
        $this->XINRegisterRule("q5_19", array("q5_19{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement('static', null, "<br/>");


        //q5-20
        $this->form->addElement('static', null, "5-20. What medications did you take?");
        $this->form->addElement('static', null,  $this->indent . "<i>Probe: Are there any more medications?<br/> $this->indent If can't recall, ask them to refer to <b>List 5</b> in prep guide and choose from the following list:</i><br/>");     

        $medicationOptions = array(NULL=>"", "01" => "01 Bromocriptine", "02" => "02 Clomid", "03" => "03  Chorionic gonadotropin", "04" => "04 Clomiphene citrate", "05" => "05 Danazol", "05" => "05 Danocrine", "06" => "06 Dostinex", "07" => "07 Factrel", "08" => "08 Fertinex", "09" => "09 Follistim", "10" => "10 Gonadorelin", "11" => "11 Gonal-F", "12" => "12 Humegon", "13" => "13 Lupron", "14" => "14 Lutrepulse", "16" => "16 Metrodin", "17" => "17 Novarel", "18" => "18 Parlodel", "19" => "19 Pergonal", "20" => "20 Pregnyl", "21" => "21 Profasi HP", "22" => "22 Provera", "23" => "23 Repronex", "24" => "24 Serophene", "25" => "25 Synarel", "26_other" => "26 Other", '88_refused' => "88 Refused", "99" => "99 Do not know", "Not_answered" => "Not Answered");


        for ($i=1; $i<6; $i++)
        {

            $this->form->addElement("select", "q5_20_{$i}", $this->indent . $this->indent . " Med #{$i}", $medicationOptions); 
            $this->addTextAreaElementRD("q5_20_{$i}_other", $this->indent . $this->indent . " If you selected [Other], please specify:");
            $this->XINRegisterRule("q5_20_{$i}_other", array("q5_20_{$i}{@}=={@}26_other"), "You must specify other", "q5_20_{$i}_other_group");
        }


        $this->XINRegisterRule("q5_20_1", array("q5_19{@}=={@}01_yes"), "Required if took medication");

        for ($i=2; $i<6; $i++)
            $this->XINRegisterRule("q5_20_{$i}", array("q5_20_{$i}{@}=={@}NEVER_REQUIRED"));


        $this->addTextAreaElementRD('q5_20_additional_t', $this->indent . $this->indent . " Additional:");
        $this->XINRegisterRule("q5_20_additional_t", array("q5_20_additional_t{@}=={@}NEVER_REQUIRED"), "q5_20_additional_t_group");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


        //q5-21
        $this->form->addElement("select", "q5_21", "5-21. Did you have any other procedures to help you become pregnant with [SIBLING]?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know]:");
        $this->form->addElement('static', null, $this->indent . $this->indent . " If child's biological father known, go to 5-25");
        $this->form->addElement('static', null, $this->indent . $this->indent . " If child's biological father is unknown, go to 5-32");
        $this->XINRegisterRule("q5_21", array("q5_21{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement('static', null, "<br/>");


        //q5-22
        $this->form->addElement('static', null, "5-22. I'm going to read you a list of procedures. Please tell me if you received any of these to help you get pregnant with [SIBLING]:");
        $this->form->addElement('static', null, $this->indent . "If can't recall, ask them to refer to <u>List 6</u> in prep guide.");
        $this->form->addElement('static', null, $this->indent . "For each procedure coded in 5-22, ask questions 5-23 thru 5-24.");
        $this->form->addElement('static', null, "<br/>");


        $procedureOptions =  array(NULL=>"", "01" => "01 Artificial insemination or intrauterine insemination", "02" => "02 In vitro fertilization- embryo transfer (IVF-ET)", "03" => "03  Gamete intrafallopian transfer (GIFT)", "04" => "04 Zygote intrafallopian transfer (ZIFT)", "05" => "05 Intracytoplasmic sperm injection (ICSI)", "06" => "06 Frozen embryo transfer", "07" => "07 Tubal embryo transfer (TET)", "08_other" => "08 Other", "88_refused"=>"88 Refused", "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered");

        $this->form->addElement("select", "q5_22_p1", $this->indent . "PROC #1:", $procedureOptions); 
        $this->addTextAreaElementRD('q5_22_p1_other', $this->indent . $this->indent . " If you selected [Other], please specify:");

        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement("select", "q5_22_p2", $this->indent . "PROC #2:", $procedureOptions);
        $this->addTextAreaElementRD('q5_22_p2_other', $this->indent . $this->indent . " If you selected [Other], please specify:");

        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement("select", "q5_22_p3", $this->indent . "PROC #3:", $procedureOptions); 
        $this->addTextAreaElementRD('q5_22_p3_other', $this->indent . $this->indent . " If you selected [Other], please specify:");

        $this->form->addElement('static', null, "<br/>");

        for ($i=1; $i<4; $i++)
            $this->XINRegisterRule("q5_22_p{$i}_other", array("q5_22_p{$i}{@}=={@}08_other"), "You must specify other", "q5_22_p{$i}_other_group");


        $this->XINRegisterRule("q5_22_p1", array("q5_21{@}=={@}01_yes"), "You must specify procedure 1");
        $this->XINRegisterRule("q5_22_p2", array("q5_22_p2{@}=={@}NEVER_REQUIRED"));
        $this->XINRegisterRule("q5_22_p3", array("q5_22_p3{@}=={@}NEVER_REQUIRED"));

        $this->form->addElement('static', null, $this->indent . $this->indent . " If you selected [Refused] or [Don't Know]:");
        $this->form->addElement('static', null, $this->indent . $this->indent . $this->indent . " If child's biological father known, then go to 5-25");
        $this->form->addElement('static', null, $this->indent . $this->indent . $this->indent . " If child's biological father is unknown, then go to 5-32");
        $this->form->addElement('static', null, "<br/>");


        //q5-23
        $this->form->addElement('static', null, "5-23. Were <u>donor</u> eggs, sperm or embryos used?");
        $this->form->addElement('static', null, $this->indent .  "Using the same PROC codes as in 5-22, choose the appropriate answer for each item.");
        $this->form->addElement('static', null, "<br/>");

        $oneToThree = array("1"=>"Eggs", "2"=>"Sperm", "3"=>"Embryo");
        for ($i=1; $i<4; $i++)
        {    
            $this->form->addElement('static', null, $this->indent . "PROC {$i}:");

            foreach ($oneToThree as $key=>$value)
            {
                $this->form->addElement("select", "q5_23_{$value}_{$key}_{$i}", $this->indent . $this->indent . "{$value}:", array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "98" => "98 Refused", "99" => "99 Do not know", "Not_Answered" => "Not Answered"));
                //				$this->form->addRule(array("q5_23_{$value}_{$key}_{$i}", "q5_22_p{$i}"), 'This question is required', 'requiredIf', array('operator'=>'!=', 'value'=>'NULL'));
                //				$this->setRequired("q5_23_{$value}_{$key}_{$i}");
                if ($i==1)
                    $this->XINRegisterRule("q5_23_{$value}_{$key}_{$i}", array("q5_22_p{$i}{@}=={@}01|02|03|04|05|06|07"), "Required if specified procedures");
                else
                    $this->XINRegisterRule("q5_23_{$value}_{$key}_{$i}", array("q5_23_{$value}_{$key}_{$i}{@}=={@}NEVER_REQUIRED"));

            }

            $this->form->addElement('static', null, $this->indent . "OTHER PROC {$i}:");

            foreach ($oneToThree as $key=>$value)
            {
                $this->form->addElement("select", "q5_23_{$value}_{$key}other_{$i}", $this->indent . $this->indent . "{$value}:", array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "98" => "98 Refused", "99" => "99 Do not know", "Not_Answered" => "Not Answered"));

                if ($i==1)
                    $this->XINRegisterRule("q5_23_{$value}_{$key}other_{$i}", array("q5_22_p{$i}{@}=={@}08_other"), "Required if specified other");
                else
                    $this->XINRegisterRule("q5_23_{$value}_{$key}other_{$i}", array("q5_22_p{$i}{@}=={@}NEVER_REQUIRED"));
                //				$this->form->addRule(array("q5_23_{$value}_{$key}other", "q5_22_p{$key}"), 'This question is required', 'requiredIf', array('operator'=>'==', 'value'=>'08'));
                //				$this->setRequired("q5_23_{$value}_{$key}other");
            }

            $this->form->addElement('static', null, "<br/>");
        }

        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


        //q5-24
        $this->form->addElement('static', null, "5-24. Were <u>frozen</u> eggs, sperm or embryos used?");
        $this->form->addElement('static', null, $this->indent .  "Using the same PROC codes as in 5-22, choose the appropriate answer for each item.");
        $this->form->addElement('static', null, "<br/>");

        for ($i=1; $i<4; $i++)
        {
            $this->form->addElement('static', null, $this->indent . "PROC {$i}:");

            foreach ($oneToThree as $key=>$value)
            {
                $this->form->addElement("select", "q5_24_{$value}_{$key}_{$i}", $this->indent . $this->indent . "{$value}:", array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "98" => "98 Refused", "99" => "99 Do not know", "Not_Answered" => "Not Answered"));

                if ($i==1)  
                    $this->XINRegisterRule("q5_24_{$value}_{$key}_{$i}", array("q5_22_p{$i}{@}=={@}01|02|03|04|05|06|07"), "Required if specified procedures");

                else        
                    $this->XINRegisterRule("q5_24_{$value}_{$key}_{$i}", array("q5_23_{$value}_{$i}{@}=={@}NEVER_REQUIRED"));
            }

            $this->form->addElement('static', null, $this->indent . "OTHER PROC {$i}:");

            foreach ($oneToThree as $key=>$value)
            {
                $this->form->addElement("select", "q5_24_{$value}_{$key}other_{$i}", $this->indent . $this->indent . "{$value}:", array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "98" => "98 Refused", "99" => "99 Do not know", "Not_Answered" => "Not Answered"));
                if ($i==1)
                    $this->XINRegisterRule("q5_24_{$value}_{$key}other_{$i}", array("q5_22_p{$i}{@}=={@}08_other"), "Required if specified other");
                else
                    $this->XINRegisterRule("q5_24_{$value}_{$key}other_{$i}", array("q5_22_p{$i}{@}=={@}NEVER_REQUIRED"));
            }

            $this->form->addElement('static', null, "<br/>");
        }


        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


    } //end function _page10() =====================================================




    function rulesPage10 ($fields)
    {

        $errors = array();

        $db =& Database::singleton();



        $db->selectRow("SELECT q5_16 FROM EARLI_interview_PART_2 WHERE CommentID='".$this->getCommentID()."'", $answer);

        //print_r($fields);

        if ($answer["q5_16"] == "01_yes")
        {
            if (empty($fields["q5_17"]))
                $errors["q5_17"] = "You must specify";
            if (empty($fields["q5_19"]))
                $errors["q5_19"] = "You must specify";
            if (empty($fields["q5_21"]))
                $errors["q5_21"] = "You must specify";

        }

        return $errors;

    }


    function _page11(){   // ========================================================


        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('header', null, "Section 5: SIBLING PREGNANCY <br /><br />(PART 3 OF 9)");
        $this->form->addElement('static', null, "<br/>");


        //function with more complex rules
        $this->form->addFormRule(array(&$this,'rulesPage11'));


        //q5***
        $this->form->addElement("select", "q5", "5***. Is [SIBLING]'s biological father known?", $this->yesNo); 
        $this->form->addElement('static', null, $this->indent . "If [SIBLING]'s biological father is unknown, go to 5-32");
        $this->XINRegisterRule("q5", array("q5{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement('static', null, "<br/>");

        //q5-25
        $this->form->addElement("select", "q5_25", "5-25. Has [the SIBLINGS pregnancy's father] ever been diagnosed by a medical provider as having male infertility factor?",  array(NULL=>"", "01_yes" => "01 Yes", "02_no" => "02 No", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q5_25", array("q5_father_known{@}=={@}01_yes"), "Required if father is known");
        $this->form->addElement('static', null, "<br/>");

        //q5-26
        $this->form->addElement("select", "q5_26", "5-26. Was the [SIBLINGS]'s father ever tested for anti-sperm antibody?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 5-28");
        $this->XINRegisterRule("q5_26", array("q5{@}=={@}01_yes"), "Required if father is known");
        $this->form->addElement('static', null, "<br/>");


        //q5-27
        $this->form->addElement("select", "q5_27", "5-27. What were the results of his test?",  array(NULL=>"", "01" => "01 Positive", "02" => "02 Negative", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule('q5_27', array("q5_26{@}=={@}01_yes"), "Required if father tested");
        $this->form->addElement('static', null, "<br/>");

        //q5-28
        $this->form->addElement("select", "q5_28", "5-28. Did [SIBLING]'s father take any medications to help you become pregnant?",  array(NULL=>"", "01_yes" => "01 Yes", "02_no" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 5-30");
        $this->XINRegisterRule("q5_28", array("q5_26{@}=={@}01_yes"), "Required if biological father is known");
        $this->form->addElement('static', null, "<br/>");


        //q5-29
        $this->form->addElement('static', null, "5-29. What medications did he take?");
        $this->form->addElement('static', null,  $this->indent . "<i>Probe: Are there any more medications? <br/> $this->indent If can't recall, ask them to refer to <b>List 5</b> in prep guide and choose from the following list:</i>");     
        $this->form->addElement('static', null, "<br/>");


        for ($i=1; $i<6; $i++)
        {
            $this->form->addElement("select", "q5_29_$i", $this->indent . " Med # $i:", array(NULL=>"", "01" => "01 Bromocriptine", "02" => "02 Clomid", "03" => "03 Chorionic gonadotropin", "04" => "04 Clomiphene citrate", "05" => "05 Danazol", "06" => "06 Danocrine", "07" => "07 Dostinex", "08" => "08 Factrel", "09" => "09 Fertinex", "10" => "10 Follistim", "11" => "11 Gonadorelin", "12" => "12 Gonal-F", "13" => "13 Humegon", "14" => "14 Lupron", "15" => "15 Lutrepulse", "16" => "16 Metrodin", "17" => "17 Novarel", "18" => "18 Parlodel", "19" => "19 Pergonal", "20" => "20 Pregnyl", "21" => "21 Profasi HP", "22" => "22 Provera", "23" => "23 Repronex", "24 Serophene", "25 Synarel", "26_other" => "26 Other", "88_refused"=>"88 Refused", "99" => "99 Do not know", "not_answered"=>"Not Answered"));
            if ($i==1)
                $this->XINRegisterRule("q5_29_$i", array("q5_28{@}=={@}01_yes"), "Required if father took medication");
            else
                $this->XINRegisterRule("q5_29_{$i}", array("q5_29_{$i}{@}=={@}NEVER_REQUIRED"));


            $this->addTextAreaElementRD("q5_29_other_$i", $this->indent . $this->indent . " If you selected [Other], please specify. Drug {$label}:");

            $this->XINRegisterRule("q5_29_other_$i", array("q5_29_$i{@}=={@}26_other"), "You must specify other", "q5_29_other_{$i}_group");
        }

        $this->form->addElement('static', null, "<br/>");


        //q5-30
        $this->form->addElement("select", "q5_30", "5-30. Did [SIBLING PREGNANCY]'s father have any procedures or surgeries to help you become pregnant?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q5_30", array("q5{@}=={@}01_yes"), "Required if biological father is known");
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 5-32");
        $this->form->addElement('static', null, "<br/>");



        //q5-31
        $this->form->addElement('static', null, "5-31. What was the procedure?");

        for ($i=1; $i<4; $i++)
        {
            $this->addTextAreaElementRD("q5_31_p{$i}", $this->indent . "Procedure #{$i}:");
        }	

        $this->XINRegisterRule("q5_31_p1", array("q5_30{@}=={@}01_yes"), "Required if father had procedures or surgeries", "q5_31_p1_group");
        $this->XINRegisterRule("q5_31_p2", array("q5_31_p2{@}=={@}NEVER_REQUIRED"), "q5_31_p2_group");
        $this->XINRegisterRule("q5_31_p3", array("q5_31_p3{@}=={@}NEVER_REQUIRED"), "q5_31_p3_group");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");

        //Morning Sickness section
        $this->form->addElement ( 'header', null, "Morning Sickness" );
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement ( 'static', null, "<b><i>Now I have some more detailed questions about your pregnancy with [SIBLING].</i></b>" );
        $this->form->addElement('static', null, "<br/>");

        //q5-32 is automatically required.
        $this->form->addElement ( "select", "q5_32", "5-32. Did you have any nausea with your pregnancy with [SIBLING]?", array (NULL => "", "01_yes" => "01 Yes", "02_no" => "02 No ", "88_refused" => "88 Refused", "99_Do_not_know" => "99 Do not know", "not_answered" => "Not Answered" ) );
        $this->form->addElement ( 'static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 5-35" );


        //q5-33 is only required is there was nausea form 5-32.
        $this->form->addElement ( "select", "q5_33", "5-33. During which months did you have nausea? Select all that apply:", $this->negThreeToTen, "multiple size = '5'" );
        $this->XINRegisterRule('q5_33', array("q5_33{@}=={@}NEVER_REQUIRED"));

        //q5-34
        $this->form->addElement ( 'static', null, "5-34. How often during [SPECIFY MONTH] did you have nausea?" );
        $group[] =&$this->form->createElement("static", "month_header");
        $group[] =&$this->form->createElement("static", "freq_header");
        $this->form->addGroup($group, "q5_34_headers", "Would you say it was...", $this->_GUIDelimiter, false);
        unset($group);

        $aToF = array("a", "b", "c", "d", "e", "f");
        foreach($aToF as $label) {
            $group[] =&$this->form->createElement ( "select", "q5_34_m_{$label}", null, array (NULL => "") + $this->negThreeToTen );
            $group[] =&$this->form->createElement ( "select", "q5_34_f_{$label}", null, array (NULL => "", "01" => "01 Less than once a week", "02" => "02 Once a week", "03" => "03  A few times a week", "04" => "04 Every day", "88 Refused", "99" => "99 Do not know", "not_answered"=>"Not Answered") );
            $this->form->addGroup($group, "q5_34_{$label}_group", "{$label})", $this->_GUIDelimiter, false);
            unset($group);
            //Don't require all these questions, but allow them to be filled in, if desired.
            if ($label=="a") continue; //Special rules apply to the first month
            $this->XINRegisterRule("q5_34_m_{$label}", array("q5_34_m_{$label}{@}=={@}NEVER_REQUIRED"), "q5_34_{$label}_group");
            $this->XINRegisterRule("q5_34_f_{$label}", array("q5_34_f_{$label}{@}=={@}NEVER_REQUIRED"), "q5_34_{$label}_group");
        }
        //Only require the first month to be answered if there was nausea.
        $this->XINRegisterRule("q5_34_m_a", array("q5_32{@}=={@}01_yes"), "Required if there was nausea.", "q5_34_a_group");
        $this->XINRegisterRule("q5_34_f_a", array("q5_32{@}=={@}01_yes"), "Required if there was nausea.", "q5_34_a_group");
        $this->form->addElement('static', null, "<br/>");


        //q5-35
        //This is required by default
        $this->form->addElement ( "select", "q5_35", "5-35. Did you have any vomiting?", array (NULL => "", "01_yes" => "01 Yes", "02_no" => "02 No ", "88_refused" => "88 Refused", "99_Do_not_know" => "99 Do not know", "Not_Answered" => "Not Answered" ) );
        $this->form->addElement ( 'static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 5-38" );

        //q5-36
        unset($answerOptions[10]); //only want months -3 -> 09 this time.
        $this->form->addElement ( "select", "q5_36", "5-36. During which months did you vomit? Choose all that apply:", $this->negThreeToNine, "multiple size = '5'");
        $this->XINRegisterRule("q5_36", array("q5_35{@}=={@}01_yes"), "Required if there was vomiting");

        //q5-37
        $this->form->addElement ( 'static', null, "5-37. How often during [SPECIFY MONTH] did you vomit?" );
        $group[] =&$this->form->createElement("static", "month_header");
        $group[] =&$this->form->createElement("static", "freq_header");
        $this->form->addGroup($group, "q5_37_headers", "Would you say it was...", $this->_GUIDelimiter, false);
        unset($group);

        unset($negThreeToTen[10]); //only want to go up to 9
        foreach($aToF as $label) {
            $group[] = &$this->form->createElement( "select", "q5_37_m_{$label}", null, array (NULL => "") + $this->negThreeToTen);
            $group[] = &$this->form->createElement ( "select", "q5_37_f_{$label}", null, array (NULL => "", "01" => "01 Less than once a week", "02" => "02 Once a week", "03" => "03  A few times a week", "04" => "04 Every day", "88 Refused", "99" => "99 Do not know", "not_answered"=>"Not Answered" ) );
            $this->form->addGroup($group, "q5_37_{$label}_group", "{$label})", $this->_GUIDelimiter, false);
            unset($group);
            //Don't require all questions, but allow them to be filled in, if desired.
            if ($label=="a") continue; //Special rules apply to the first month
            $this->XINRegisterRule("q5_37_m_{$label}", array("q5_37_m_{$label}{@}=={@}NEVER_REQUIRED"), "q5_37_{$label}_group");
            $this->XINRegisterRule("q5_37_f_{$label}", array("q5_37_f_{$label}{@}=={@}NEVER_REQUIRED"), "q5_37_{$label}_group");
        }
        //Only require the first month to be answered, if there was vomiting.  Trust that the rest will be filled in as needed.
        $this->XINRegisterRule("q5_37_m_a", array("q5_35{@}=={@}01_yes"), "Required if there was vomiting", "q5_37_a_group");
        $this->XINRegisterRule("q5_37_f_a", array("q5_35{@}=={@}01_yes"), "Required if there was vomiting", "q5_37_a_group");


        $this->form->addElement ( 'static', null, $this->indent . "If nausea or vomiting occurred during pregnancy (i.e., 5-32 or 5-35= [Yes]), go to 5-38." );
        $this->form->addElement ( 'static', null, $this->indent . "If no nausea or vomiting occurred during pregnancy (i.e 5-32 and 5-35 = [No], [Refused] or [Don't Know]), then go to  5-40." );
        $this->form->addElement('static', null, "<br/>");


        //q5-38
        $this->form->addElement ( "select", "q5_38", "5-38. Did you ever require medical treatment for the nausea or vomiting?", array (NULL => "", "01_yes" => "01 Yes", "02_no" => "02 No ", "88_refused" => "88 Refused", "99_Do_not_know" => "99 Do not know", "Not_Answered" => "Not Answered" ) );
        $this->XINRegisterRule ( "q5_38", array ("q5_38{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement ( 'static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 5-40" );


        //q5-39
        $this->form->addElement ( 'select', "q5_39", "5-39. What medicine/treatment did you take? Was it...Select all that apply:", array (NULL => "", "01_vitB6" => "01 Vitamin B6 (pyridoxine)", "02_unisom" => "02 Unisom (doxylamine)", "03_emetrol" => "03  Emetrol", "04_ginger" => "04 Ginger", "05_other" => "05 Other", "88_Refused" => "88 Refused", "99_Do_not_know" => "99 Do not know", "Not_Answered" => "Not Answered" ), "multiple size = '5'");
        $this->XINRegisterRule("q5_39", array("q5_39{@}=={@}NEVER_REQUIRED")); //Now working //This rule doesn't appear to work at all due to q5_39 being a select multiple.  Oh well, best to just leave it alone.
        $this->addTextAreaElementRD("q5_39_other", $this->indent . "If you selected [05 Other], please specify");
        $this->XINRegisterRule("q5_39_other", array("q5_39{@}=={@}05_other"), "You must specify other", "q5_39_other_group"); 

        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('header', null, "<b>Prenatal Care</b>");
        $this->form->addElement('static', null, "<br/>");

        //q5-40
        $this->form->addElement("select", "q5_40",  "5-40. During your pregnancy with [SIBLING], how many ultrasounds did you have?",   array(NULL=>"",  "0", "1" => "1", "2" => "2", "3" => "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, "<br/>");


        //q5-41
        $this->form->addElement("select", "q5_41", "5-41. Did you have an Amniocentesis or amnio?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 5-44");
        $this->form->addElement('static', null, "<br/>");


        $gestational = array(NULL=>"") + array_combine(range(1,45), range(1,45)) + array("88_refused"=>"88 Refused", "99_do_not_know"=>"99 Do not know", "not_answered"=>"Not Answered");

        //q5-42
        $this->form->addElement("static", null, "5-42. When was it done?"); 
        $this->addCustomDateElement('q5_42_date', $this->indent . "Please specify date:", $this->dateOptions2007);
        $this->form->addElement("select", "q5_42_weeks", $this->indent . "OR gestational weeks:" , $gestational);
        $this->XINRegisterRule('q5_42_weeks', array("q5_42_date_date{@}=={@}", "q5_42_date_date_status{@}=={@}", "q5_41{@}=={@}01_yes"), "OR You must specify weeks");
        $this->XINRegisterRule('q5_42_date_date', array("q5_42_weeks{@}=={@}", "q5_42_date_date_status{@}=={@}", "q5_41{@}=={@}01_yes"), "You must specify date or select from the drop-down", "q5_42_date_date_group");
        $this->XINRegisterRule('q5_42_date_date_status', array("q5_42_weeks{@}=={@}", "q5_42_date_date{@}=={@}", "q5_41{@}=={@}01_yes"), "You must specify date or select from the drop-down", "q5_42_date_date_group");
        $this->form->addElement('static', null, "<br/>");

        //q5-43
        $this->form->addElement("select", "q5_43", "5-43. Were there any abnormalities detected?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q5_43", array("q5_41{@}=={@}01_yes"), "Required if had amniocentesis or amnio");
        $this->form->addElement('static', null, "<br/>");

        //q5-44
        $this->form->addElement("select", "q5_44", "5-44. Did you have an audible fetal heart rate assessment?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 5-47");
        $this->form->addElement('static', null, "<br/>");

        //q5-45
        $this->form->addElement("static", null, "5-45. When was it done?");
        $this->addCustomDateElement('q5_45_date', $this->indent . "Specify date:", $this->dateOptions2007);
        $this->form->addElement("select", "q5_45_weeks", $this->indent . "OR gestational weeks:", $gestational);
        $this->XINRegisterRule("q5_45", array("q5_44{@}=={@}01_yes"), "Required if had fetal heart rate assessment");
        $this->XINRegisterRule('q5_45_weeks', array("q5_45_date_date{@}=={@}", "q5_45_date_date_status{@}=={@}", "q5_44{@}=={@}01_yes"), "OR You must specify weeks");
        $this->XINRegisterRule('q5_45_date_date', array("q5_45_weeks{@}=={@}", "q5_45_date_date_status{@}=={@}", "q5_44{@}=={@}01_yes"), "You must specify date or select from the drop-down", "q5_45_date_date_group");
        $this->XINRegisterRule('q5_45_date_date_status', array("q5_45_weeks{@}=={@}", "q5_45_date_date{@}=={@}", "q5_44{@}=={@}01_yes"), "You must specify date or select from the drop-down", "q5_45_date_date_group");
        //		$this->XINRegisterRule("q5_45_weeks", array("q5_45{@}=={@}NEVER_REQUIRED"));
        //		$this->XINRegisterRule("q5_45_", array("q5_45{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement('static', null, "<br/>");

        //q5-46
        $this->form->addElement("select", "q5_46", "5-46. Were there any abnormalities detected?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q5_46", array("q5_44{@}=={@}01_yes"), "Required if had fetal heart rate assessment");
        $this->form->addElement('static', null, "<br/>");


        //q5-47
        $this->form->addElement("select", "q5_47", "5-47. Did you have an antenatal testing?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 5-51");
        $this->form->addElement('static', null, "<br/>");

        //q5-48
        $this->form->addElement("select", "q5_48", "5-48. What kind of test was done?",  array(NULL=>"", "01" => "01 Non-Stress Test (NST)", "02" => "02 Ultrasound check for fluid (AFI)", "03" => "03  Biophysical Profile (BPP)", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q5_48", array("q5_47{@}=={@}01_yes"), "Required if had antenatal testing");
        $this->form->addElement('static', null, "<br/>");

        //q5-49
        $this->form->addElement("static", null, "5-49. When was it done?");
        $this->addCustomDateElement('q5_49_date', $this->indent . "Please specify date:", $this->dateOptions2007);
        $this->form->addElement("select", "q5_49_weeks", $this->indent . "OR gestational weeks:", $gestational);

        $this->XINRegisterRule('q5_49_weeks', array("q5_49_date_date{@}=={@}", "q5_49_date_date_status{@}=={@}", "q5_47{@}=={@}01_yes"), "OR You must specify weeks");
        $this->XINRegisterRule('q5_49_date_date', array("q5_49_weeks{@}=={@}", "q5_49_date_date_status{@}=={@}", "q5_47{@}=={@}01_yes"), "You must specify date or select from the drop-down", "q5_49_date_date_group");
        $this->XINRegisterRule('q5_49_date_date_status', array("q5_49_weeks{@}=={@}", "q5_49_date_date{@}=={@}", "q5_47{@}=={@}01_yes"), "You must specify date or select from the drop-down", "q5_49_date_date_group");
        $this->form->addElement('static', null, "<br/>");

        //q5-50
        $this->form->addElement("select", "q5_50", "5-50. Were there any abnormalities detected?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q5_50", array("q5_47{@}=={@}01_yes"), "Required if had antenatal testing");
        $this->form->addElement('static', null, "<br/>");


        //q5-51
        $this->form->addElement("select", "q5_51", "5-51. Did you have Chorionic Villus Sampling or CVS?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 5-54");
        $this->form->addElement('static', null, "<br/>");


        //q5-52
        $this->form->addElement("static", null, "5-52. When was it done?");
        $this->addCustomDateElement('q5_52_date', $this->indent . "Please specify date:", $this->dateOptions2007);
        $this->form->addElement("select", "q5_52_weeks", $this->indent . "OR gestational weeks:", $gestational);

        $this->XINRegisterRule('q5_52_weeks', array("q5_52_date_date{@}=={@}", "q5_52_date_date_status{@}=={@}", "q5_51{@}=={@}01_yes"), "OR You must specify weeks");
        $this->XINRegisterRule('q5_52_date_date', array("q5_52_weeks{@}=={@}", "q5_52_date_date_status{@}=={@}", "q5_51{@}=={@}01_yes"), "You must specify date or select from the drop-down", "q5_52_date_date_group");
        $this->XINRegisterRule('q5_52_date_date_status', array("q5_52_weeks{@}=={@}", "q5_52_date_date{@}=={@}", "q5_51{@}=={@}01_yes"), "You must specify date or select from the drop-down", "q5_52_date_date_group");
        $this->form->addElement('static', null, "<br/>");


        //q5-53
        $this->form->addElement("select", "q5_53", "5-53. Were there any abnormalities detected?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q5_53", array("q5_51{@}=={@}01_yes"), "Required if had Chorionic Villus Sampling or CVS");
        $this->form->addElement('static', null, "<br/>");

        //q5-54
        $this->form->addElement("select", "q5_54", "5-54. Were you told that there was [rhesus] or [Rh] incompatibility between you and [SIBLING PREGNANCY]?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 5-56");
        $this->form->addElement('static', null, "<br/>");

        //q5-55
        $this->form->addElement("select", "q5_55", "5-55. If your blood type is Rh-, you might have been given injections of Rhogam. Did you receive any Rhogam injections during your pregnancy with [SIBLING]?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q5_55", array("q5_54{@}=={@}01_yes"), "Required if had rhesus or Rh incompatibility");
        $this->form->addElement('static', null, "<br/>");

        //q5-56
        $this->form->addElement("select", "q5_56", "5-56. During your pregnancy with [SIBLING], did you receive shots or immunizations, such as...",  array(NULL=>"", "01" => "01 Immunoglobulin injection (other than RhoGam)?", "02_no" => "02 No", "03" => "03  Other", "04" => "04 Flu Shot", "05" => "05 Tetanus vaccine", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->addTextAreaElementRD("q5_56_other", $this->indent . "If you selected [03 Other], please specify:");
        $this->XINRegisterRule('q5_56_other', array("q5_56{@}=={@}03"), "You must specify other immunizations", "q5_56_other_group");
        $this->form->addElement('static', null, "<br/>");

        //q5-57
        $this->form->addElement("static", null, "5-57. When was it done?");
        $this->addCustomDateElement('q5_57_date', $this->indent . "Please specify date:", $this->dateOptions2007);
        $this->form->addElement("select", "q5_57_weeks", $this->indent . "OR gestational weeks:", $gestational);

        $this->XINRegisterRule('q5_57_weeks', array("q5_57_date_date{@}=={@}", "q5_57_date_date_status{@}=={@}", "q5_56{@}=={@}01|02|03|04|05"), "OR You must specify weeks");
        $this->XINRegisterRule('q5_57_date_date', array("q5_57_weeks{@}=={@}", "q5_57_date_date_status{@}=={@}", "q5_56{@}=={@}01|02|03|04|05"), "You must specify date or select from the drop-down", "q5_57_date_date_group");
        $this->XINRegisterRule('q5_57_date_date_status', array("q5_57_weeks{@}=={@}", "q5_57_date_date{@}=={@}", "q5_56{@}=={@}01|02|03|04|05"), "You must specify date or select from the drop-down", "q5_57_date_date_group");

        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


    } //end function _page11() ======================================================



    function rulesPage11($fields)
    {

        $errors = array();

        $db =& Database::singleton();


        function multSelect($fields, $question1, $question2)
        {
            return (($fields[$question1] == array(0=>null)  && $fields[$question2] == "01_yes") || (empty($fields[$question1])) && $fields[$question2] == "01_yes");
        }


        $db->selectRow("SELECT q5_16 FROM EARLI_interview_PART_2 WHERE CommentID='".$this->getCommentID()."'", $answer);

        $otherCommentID = $db->selectOne("SELECT CommentID from flag where Test_name='EARLI_interview_PART_1' and SessionID=" . $this->getSessionID());

        $db->selectRow("SELECT q4a_1 FROM EARLI_interview_PART_1 WHERE CommentID='". $otherCommentID."'", $answ);


        //	print_r($fields);

        //q5_25a
        if ($answer["q5_16"] == "01_yes")
        {
            if ($answ["q4a_1"] == "01_yes" || $answ["q4a_1"] == "02")
            {
                if (empty($fields["q5"]))
                    $errors["q5"] =  "You must specify";
            }
        }

        //q5-33
        if (multSelect($fields, "q5_33", "q5_32"))
            $errors["q5_33"] = "You must specify month(s)";

        //q5-36
        if (multSelect($fields, "q5_36", "q5_35"))
            $errors["q5_36"] = "You must specify month(s)";

        //q5-38
        if (($fields["q5_32"] == "01_yes" || $fields["q5_35"] == "01_yes") && empty($fields["q5_38"]))
            $errors["q5_38"] = "Required if there was nausea or vomiting";

        //q5-39
        if (multSelect($fields, "q5_39", "q5_38"))
            $errors["q5_39"] = "You must specify medication/treatment(s)";

        return $errors;

    }




    function _page12(){   // ========================================================


        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('header', null, "Section 5: SIBLING PREGNANCY <br /><br />(PART 4 OF 9)");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<b/>Vaginal Douching");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<b>Refer to the pregnancy calendar for the following questions.</b>");
        $this->form->addElement('static', null, "<br/>");


        //function with more complex rules
        $this->form->addFormRule(array(&$this,'rulesPage12'));


        //q5-58
        $this->form->addElement("select", "q5_58", "5-58. Did you ever douche between [-3] and [DOBS]?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 5-61");
        $this->form->addElement('static', null, "<br/>");


        //q5-59
        $this->form->addElement("select", "q5_59", "5-59. Between [-3] and [DOBS], which months did you douche? Choose all that apply:", $this->negThreeToNine, "multiple size = '5'");
        $this->form->addElement('static', null, $this->indent . "If you selected [Refused] or [Don't Know] skip to question 5-60");
        $this->form->addElement('static', null, "<br/>");


        //q5-60
        $this->form->addElement('static', null, "5-60. On average, how often would you say you douched during [SPECIFY MONTH]?");
        $group[] =&$this->form->createElement("static", "month_header");
        $group[] =&$this->form->createElement("static", "freq_header");
        $this->form->addGroup($group, "q5_60_headers", "Would you say it was...", $this->_GUIDelimiter, false);
        unset($group);


        $aToF = array("a", "b", "c", "d", "e", "f");
        foreach($aToF as $label) {
            $group[] = &$this->form->createElement( "select", "q5_60_m_{$label}", null, $this->negThreeToTen);
            $group[] = &$this->form->createElement ( "select", "q5_60_f_{$label}", null, array (NULL => "", "01" => "01 More than once a week", "02" => "02 Once a week", "03" => "03  Once every 2-3 weeks", "04" => "04 Once a month or less", "88 Refused", "99" => "99 Do not know", "not_answered"=>"Not Answered") );
            $this->form->addGroup($group, "q5_60_{$label}_group", "{$label})", $this->_GUIDelimiter, false);
            unset($group);
            //Don't require all questions, but allow them to be filled in, if desired.
            if ($label=="a") continue; //Special rules apply to the first month
            $this->XINRegisterRule("q5_60_m_{$label}", array("q5_60_m_{$label}{@}=={@}NEVER_REQUIRED"), "q5_60_{$label}_group");
            $this->XINRegisterRule("q5_60_f_{$label}", array("q5_60_f_{$label}{@}=={@}NEVER_REQUIRED"), "q5_60_{$label}_group");
        }

        //Only require the first month to be answered, if there was douching.  Trust that the rest will be filled in as needed.
        $this->XINRegisterRule("q5_60_m_a", array("q5_58{@}=={@}01_yes"), "Required if there was douching", "q5_60_a_group");
        $this->XINRegisterRule("q5_60_f_a", array("q5_58{@}=={@}01_yes"), "Required if there was douching", "q5_60_a_group");


        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('header', null, "<b/>Maternal Medical Conditions");
        $this->form->addElement('static', null, "<br/>");

        //q5-61
        $this->form->addElement("select", "q5_61", "5-61. During your pregnancy with [SIBLING] were you ever told by a physician or nurse that you had preeclampsia or toxemia?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 5-64");
        $this->form->addElement('static', null, "<br/>");

        //q5-62
        $this->form->addElement("select", "q5_62", "5-62. Did you take any medicine for preeclampsia or toxemia?", array(NULL=>"", "01_yes" => "01 Yes", "02_no" => "02 No", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 5-64");
        $this->XINRegisterRule("q5_62", array("q5_61{@}=={@}01_yes"), "Required if had preeclampsia or toxemia");
        $this->form->addElement('static', null, "<br/>");


        //q5-63
        $this->form->addElement("select", "q5_63", "5-63. What medication did you take?",  array(NULL=>"","CODE_01"=>"CODE 01: Aldomet", "CODE_02"=>"CODE 02: Labetalol", "CODE_03"=>"CODE 03: Hydralazine", "CODE_04"=>"CODE 04: Nifedipine", "CODE_05"=>"CODE 05: Magnesium Sulfate", "CODE_09"=>"CODE 09: Other", "88_refused"=>"88 Refused", "99_do_not_know"=>"99 Do not know", "not_answered"=>"Not Answered"));
        $this->addTextAreaElementRD('q5_63_CODE_09_other', $this->indent . "If you selected [CODE 09: Other], please specify:");
        $this->XINRegisterRule("q5_63", array("q5_62{@}=={@}01_yes"), "Required if took medication");
        $this->XINRegisterRule("q5_63_CODE_09_other", array("q5_63{@}=={@}CODE_09"), "You must specify other", "q5_63_CODE_09_other_group");


        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<b>Medications for hypertension / preeclampsia:</b>");
        $this->form->addElement('static', null, "<br/>");

        $questionArray = array("CODE_01"=>"CODE 01: Aldomet", "CODE_02"=>"CODE 02: Labetalol", "CODE_03"=>"CODE 03: Hydralazine", "CODE_04"=>"CODE 04: Nifedipine", "CODE_05"=>"CODE 05: Magnesium Sulfate", "CODE_09"=>"CODE 09: Other");
        reset($questionArray);

        while(list($field, $label) = each($questionArray)) {

            $this->form->addElement('static', null, "{$label}"); 
            $this->form->addElement("select", "q5_63_{$field}_month",  $this->indent .  "Month medication taken:",  array(NULL=>"","1", "2", "3", "4", "5", "6", "7", "8", "9", "Refused", "Do not know", "Not_Answered" => "Not Answered"));
            $this->XINRegisterRule("q5_63_{$field}_month", array("q5_63{@}=={@}{$field}"), "Required if taken {$label}");
            $this->form->addElement("select", "q5_63_{$field}_admin",  $this->indent .  "Route of Administration:",  array(NULL=>"", "01_oral" => "Oral", "02_infusion" => "Infusion", "03_rectal" => "Rectal", "04_injection" => "Injection", "88_refused" =>"Refused", "99_Do_not_know" => "Don't know", "Not_Answered" => "Not Answered"));
            $this->XINRegisterRule("q5_63_{$field}_admin", array("q5_63{@}=={@}{$field}"), "Required if taken {$label}");

            //testing HTML_QuickForm rules
            //		$field = "one";  //just for now...
            $answerOptions = array(NULL=>"", 
                "tab_per_day" => "(#)_____tabs or caps/day, for(#)_____ days", 
                    "tab_week"=>"(#)_____tabs or caps/week", 
                        "tab_month"=>"(#)_____tabs or caps/month", 
                            "tab_everyday"=>"(#)_____tabs or caps everyday", 
                                "other" => "Other", "Refused", "Do not know", "Not_Answered" => "Not Answered");

            //var_dump($answerOptions);
            //        array('key'=>"value");
            //        array('db'=>'seen');

            $this->form->addElement("select", "q5_63_{$field}_freq",  $this->indent . "How often/number of capsules", $answerOptions);
            $this->XINRegisterRule("q5_63_{$field}_freq", array("q5_63{@}=={@}{$field}"), "Required if took {$label}");

            $this->addNumericElementRD("q5_63_{$field}_tabs", $this->indent . "Enter the number of tabs or caps:");
            $this->XINRegisterRule("q5_63_{$field}_tabs", array("q5_63{@}=={@}{$field}", "q5_63_{$field}_freq{@}=={@}tab_per_day|tab_week|tab_month_|tab_everyday"), "Required if took {$label}", "q5_63_{$field}_tabs_group");

            $this->addNumericElementRD("q5_63_{$field}_day", $this->indent . "If you selected [(#)_____tabs or caps/day, for(#)____ days], please enter the number of days:");
            $this->XINRegisterRule("q5_63_{$field}_day", array("q5_63{@}=={@}{$field}", "q5_63_{$field}_freq{@}=={@}tab_per_day"), "You must specify number of days", "q5_63_{$field}_day_group");

            $this->addTextAreaElementRD("q5_63_{$field}_other_specify", $this->indent . $this->indent . "If [Other], please specify other frequency:");
            $this->XINRegisterRule("q5_63_{$field}_other_specify", array("q5_63{@}=={@}{$field}|q5_63_{$field}_freq{@}=={@}other"), "You must specify other", "q5_63_{$field}_other_specify_group");
            $this->form->addElement('static', null, "<br/>");
            $this->form->addElement('static', null, "<br/>");

        }

        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");

        //q5-64
        $this->form->addElement ( "select", "q5_64", "5-64. During your pregnancy with [SIBLING] were you ever told by a physician or nurse that you had premature labor?", array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 5-68");
        $this->form->addElement('static', null, "<br/>");

        $answerOptions = array(null=>"", "1"=>"1", "2"=>"2", "3"=>"3", "4"=>"4", "5"=>"5", "6"=>"6", "7"=>"7", "8"=>"8", "9"=>"9", "88_Refused" => "88 Refused", "99_Do_not_know" => "99 Do not know", "not_answered" => "Not Answered");

        //q5-65
        $this->form->addElement ( "select", "q5_65", "5-65. During which months of the pregnancy did you have the premature labor?", $answerOptions, "multiple size = '5'" );
        $this->XINRegisterRule('q5_65', array("q5_64{@}=={@}01_yes"), "This is required if you had premature labor."); 
        $this->form->addElement('static', null, "<br/>");

        //q5-66
        $this->form->addElement("select", "q5_66", "5-66. Did you take any medicine for premature labor?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q5_66", array("q5_64{@}=={@}01_yes"), "Required if had premature labor");
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 5-68");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");

        $questionArray = array("CODE_01"=>"CODE 01: Terbutaline", "CODE_02"=>"CODE 02: Magnesium Sulfate", "CODE_03"=>"CODE 03: 17 alpha hydroxyl progesterone acetate", "CODE_04"=>"CODE 04: Indocin", "CODE_05"=>"CODE 05: Nifedipine", "CODE_06"=>"CODE 06: Steroids", "CODE_07"=>"CODE 07: Antibiotics", "CODE_08"=>"CODE 08: Other");
        reset($questionArray);

        //q5-67
        $this->form->addElement('select', "q5_67", "5-67. What medications did you take for preterm labor?", array(NULL=>"") + $questionArray + array("88_refused"=>"88 Refused", "99_do_not_know"=>"99 Do not know", "not_answered"=>"Not Answered"));
        $this->XINRegisterRule("q5_67", array("q5_66{@}=={@}01_yes"), "Required if taken medicine");
        $this->addTextAreaElementRD('q5_67_CODE_08_other', $this->indent . "If you selected [CODE 08: Other], please specify:");
        $this->XINRegisterRule("q5_67_CODE_08_other", array("q5_67{@}=={@}CODE_08"), "You must specify other", "q5_67_CODE_08_other_group");


        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<b>List of medications for preterm labour:</b>");

        while(list($field, $label) = each($questionArray)){

            $this->form->addElement('static', null, "<br/>");
            $this->form->addElement('static', null, "{$label}");
            $this->form->addElement("select", "q5_67_{$field}_month", $this->indent . "Month medication taken:", array(NULL=>"","1", "2", "3", "4", "5", "6", "7", "8", "9", "Refused", "Do not know", "Not_Answered" => "Not Answered"));
            $this->XINRegisterRule("q5_67_{$field}_month", array("q5_67{@}=={@}{$field}"), "Required if taken {$label}");

            $this->form->addElement("select", "q5_67_{$field}_admin", $this->indent . "Route of Administration:",  array(NULL=>"", "oral"=>"Oral", "rectal"=>"Rectal", "injection"=>"Injection", "infusion"=>"Infusion", "Not_Answered" => "Not Answered"));
            $this->XINRegisterRule("q5_67_{$field}_admin", array("q5_67{@}=={@}{$field}"), "Required if taken {$label}");

            $this->form->addElement("select", "q5_67_{$field}_freq", $this->indent . "How often/number of capsules",  array(NULL=>"", "tab_day" => "(#)_____tabs or caps/day, for (#) ____days", "tab_week"=>"(#)_____tabs or caps/week", "tab_month"=>"(#)_____tabs or caps/month", "tab_everyday"=>"(#)_____tabs or caps everyday", "other" => "Other", "Refused", "Do not know", "Not_Answered" => "Not Answered"));
            $this->XINRegisterRule("q5_67_{$field}_freq", array("q5_67{@}=={@}{$field}"), "Required if taken {$label}");

            $this->addNumericElementRD("q5_67_{$field}_tabs", $this->indent . $this->indent . "Enter the number of tabs or caps:");
            $this->XINRegisterRule("q5_67_{$field}_tabs", array("q5_67{@}=={@}{$field}", "q5_67_{$field}_freq{@}=={@}tab_day|tab_week|tab_month|tab_everyday"), "Required if taken {$label}", "q5_67_{$field}_tabs_group");

            $this->addNumericElementRD("q5_67_{$field}_days", $this->indent . $this->indent . "If you selected [(#)_____tabs or caps/day, for (#)____ days], please enter the number of days:");
            $this->XINRegisterRule("q5_67_{$field}_days", array("q5_67{@}=={@}{$field}", "q5_67_{$field}_freq{@}=={@}tab_day"), "You must specify number of days", "q5_67_{$field}_days_group");

            $this->addTextAreaElementRD("q5_67_{$field}_other_specify", $this->indent . $this->indent . "If you selected [Other], please specify:");
            $this->XINRegisterRule("q5_67_{$field}_other_specify", array("q5_67{@}=={@}{$field}|q5_67_{$field}_freq{@}=={@}other"), "You must specify other", "q5_67_{$field}_other_specify_group");

        }

        $this->form->addElement('static', null, "<br/><br/>");


    } //end function _page12() ======================================================



    function rulesPage12($fields)
    {

        $errors = array();

        function multSelect($fields, $question1, $question2)
        {
            return (($fields[$question1] == array(0=>null) && $fields[$question2] == "01_yes") || (empty($fields[$question1])) && $fields[$question2] == "01_yes");
        }


        //q5-59
        if (multSelect($fields, "q5_59", "q5_58"))
            $errors["q5_59"] = "You must specify month(s)";		

        //q5-65
        if (multSelect($fields, "q5_65", "q5_64"))
            $errors["q5_65"] = "You must specify month(s)";


        return $errors;
    }



    function _page13(){   // ========================================================


        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('header', null, "Section 5: SIBLING PREGNANCY <br /><br />(PART 5 OF 9)");
        $this->form->addElement('static', null, "<br/>");


        //function with more complex rules
        $this->form->addFormRule(array(&$this,'rulesPage13'));


        //q5-68
        $this->form->addElement("select", "q5_68", "5-68. During your pregnancy with [SIBLING] did you have vaginal bleeding?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 5-72");
        $this->form->addElement('static', null, "<br/>");


        $answerOptions = array(null=>"", "1"=>"1", "2"=>"2", "3"=>"3", "4"=>"4", "5"=>"5", "6"=>"6", "7"=>"7", "8"=>"8", "9"=>"9", "88_Refused" => "88 Refused", "99_Do_not_know" => "99 Do not know", "not_answered" => "Not Answered");

        //q5-69
        $this->form->addElement ( "select", "q5_69", "5-69. During which months of pregnancy did you have the bleeding?", $answerOptions, "multiple size = '5'" );
        $this->form->addElement('static', null, "<br/>");


        //q5-70
        $this->form->addElement("select", "q5_70", "5-70. Did you take any medicine for the bleeding?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule('q5_70', array("q5_68{@}=={@}01_yes"), "Required if had bleeding."); 
        $this->form->addElement('static', null, "<br/>");


        //q5-71
        $questionArray = array("CODE_01"=>"CODE 01: Terbutaline", "CODE_02"=>"CODE 02: Magnesium Sulfate", "CODE_03"=>"CODE 03: 17 alpha hydroxyl progesterone acetate", "CODE_04"=>"CODE 04: Indocin", "CODE_05"=>"CODE 05: Nifedipine", "CODE_06"=>"CODE 06: Steroids", "CODE_07"=>"CODE 07: Antibiotics", "CODE_08"=>"CODE 08: Other"); 

        $this->form->addElement('select', "q5_71", "5-71. What medications did you take for vaginal bleeding?", array(NULL=>"") + $questionArray + array("88_refused"=>"88 Refused", "99_Do_not_know"=>"99 Do not know", "not_answered"=>"Not Answered"));
        $this->XINRegisterRule('q5_71', array("q5_70{@}=={@}01_yes"), "Required if took medicine");
        $this->addTextAreaElementRD('q5_71_CODE_08_other', $this->indent . "If you selected [CODE 08: Other], please specify:");
        $this->XINRegisterRule("q5_71_CODE_08_other", array("q5_71{@}=={@}CODE_08"), "You must specify other", "q5_71_CODE_08_other_group");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<b>List of medications for vaginal bleeding:</b>");


        foreach ($questionArray as $field=>$label)
        {
            $this->form->addElement('static', null, "<br/>");
            $this->form->addElement('static', null, "{$label}");
            $this->form->addElement("select", "q5_71_{$field}_month",  $this->indent .  "Month medication taken:",  array(NULL=>"","1", "2", "3", "4", "5", "6", "7", "8", "9", "Refused", "Do not know", "Not_Answered" => "Not Answered"));
            $this->XINRegisterRule("q5_71_{$field}_month", array("q5_71{@}=={@}{$field}"), "Required if took {$label}");

            $this->form->addElement("select", "q5_71_{$field}_admin",  $this->indent .  "Route of Administration:",  array(NULL=>"", "oral"=>"Oral", "rectal"=>"Rectal", "injection"=>"Injection", "infusion"=>"Infusion", "Refused" => "Refused", "Don_not_know" => "Don't know", "Not_Answered" => "Not Answered"));
            $this->XINRegisterRule("q5_71_{$field}_admin", array("q5_71{@}=={@}{$field}"), "Required if took {$label}");

            $this->form->addElement("select", "q5_71_{$field}_freq",  $this->indent . "How often/number of capsules",  array(NULL=>"", "tab_day" => "(#)_____tabs or caps/day, for (#)____days", "tab_week"=>"(#)_____tabs or caps/week", "tab_month"=>"(#)_____tabs or caps/month", "tab_everyday"=>"(#)_____tabs or caps everyday", "other" => "Other", "Refused", "Do not know", "Not_Answered" => "Not Answered"));
            $this->XINRegisterRule("q5_71_{$field}_freq", array("q5_71{@}=={@}{$field}"), "Required if took {$label}");

            $this->addNumericElementRD("q5_71_{$field}_tabs", $this->indent . $this->indent . "Enter the number of tabs or caps:");
            $this->XINRegisterRule("q5_71_{$field}_tabs", array("q5_71{@}=={@}{$field}", "q5_71_{$field}_freq{@}=={@}tab_day|tab_week|tab_month|tab_everyday"), "Required if taken {$label}", "q5_71_{$field}_tabs_group");

            $this->addNumericElementRD("q5_71_{$field}_days", $this->indent . $this->indent . "If you selected [(#)_____tabs or caps/day, for(#)____days], please enter the number of days:");
            $this->XINRegisterRule("q5_71_{$field}_days", array("q5_71{@}=={@}{$field}", "q5_71_{$field}_freq{@}=={@}tab_day"), "You must specify number of days", "q5_71_{$field}_days_group");

            $this->addTextAreaElementRD("q5_71_{$field}_other_specify", $this->indent . $this->indent . "If you selected [Other], please specify:");
            $this->XINRegisterRule("q5_71_{$field}_other_specify", array("q5_71{@}=={@}{$field}|q5_71_{$field}_freq{@}=={@}other"), "You must specify other", "q5_71_{$field}_other_specify_group");

        }

        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


        //q5-72
        $this->form->addElement("select", "q5_72", "5-72 During your pregnancy with [SIBLING] were you ever told by a physician or nurse that you had gestational diabetes?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 5-76");

        $answerOptions = array(null=>"", "1"=>"1", "2"=>"2", "3"=>"3", "4"=>"4", "5"=>"5", "6"=>"6", "7"=>"7", "8"=>"8", "9"=>"9", "88_Refused" => "88 Refused", "99_Do_not_know" => "99 Do not know", "not_answered" => "Not Answered");

        //q5-73
        $this->form->addElement ( "select", "q5_73", "5-73. During which months did you have the gestational diabetes?", $answerOptions, "multiple size = '5'" );
        $this->XINRegisterRule('q5_73', array("q5_73{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement('static', null, "<br/>");

        //q5-74
        $this->form->addElement("select", "q5_74", "5-74. Did you take any medicine for gestational diabetes?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q5_74", array("q5_72{@}=={@}01_yes"), "Required if had gestational diabetes");
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 5-76");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");
        reset($questionArray);


        //q5-75
        $questionArray = array("CODE_01"=>"CODE 01: Insulin", "CODE_02"=>"CODE 02: Glucotrol", "CODE_03"=>"CODE 03: Glyburide", "CODE_04"=>"CODE 04: Glipizide", "CODE_05"=>"CODE 05: Gludophage/metformin", "CODE_09"=>"CODE 09: Other");

        $this->form->addElement('select', "q5_75", "5-75. What medications did you take for gestational diabetes?", array(NULL=>"") + $questionArray + array("88_refused"=>"88 Refused", "99_Do_not_know"=>"99 Do not know", "not_answered"=>"Not Answered"));
        $this->XINRegisterRule("q5_75", array("q5_74{@}=={@}01_yes"), "Required if took medicine for gestational diabetes");
        $this->addTextAreaElementRD('q5_75_CODE_09_other', $this->indent . "If you selected [CODE 09: Other], please specify:");
        $this->XINRegisterRule("q5_75_CODE_09_other", array("q5_75{@}=={@}CODE_09"), "You must specify other", "q5_75_CODE_09_other_group");

        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<b>Medications for gestational diabetes</b>");


        foreach ($questionArray as $field=>$label)
        {

            $this->form->addElement('static', null, "<br/>");
            $this->form->addElement('static', null, "{$label}");
            $this->form->addElement("select", "q5_75_{$field}_month",  $this->indent .  "Month medication taken:",  array(NULL=>"","1", "2", "3", "4", "5", "6", "7", "8", "9", "Refused", "Do not know", "Not_Answered" => "Not Answered"));
            $this->XINRegisterRule("q5_75_{$field}_month", array("q5_75{@}=={@}{$field}"), "Required if took {$label}");

            $this->form->addElement("select", "q5_75_{$field}_admin",  $this->indent .  "Route of Administration:",  array(NULL=>"", "oral"=>"Oral", "rectal"=>"Rectal", "injection"=>"Injection", "infusion"=>"Infusion", "Refused" => "Refused", "Do_not_know" => "Don't know", "Not_Answered" => "Not Answered"));
            $this->XINRegisterRule("q5_75_{$field}_admin", array("q5_75{@}=={@}{$field}"), "Required if took {$label}");

            $this->form->addElement("select", "q5_75_{$field}_freq",  $this->indent . "How often/number of capsules",  array(NULL=>"", "tab_day" => "(#)_____tabs or caps/day, for (#)____days", "tab_wek"=>"(#)_____tabs or caps/week", "tab_month"=>"(#)_____tabs or caps/month", "tab_everyday"=>"(#)_____tabs or caps everyday", "Other" => "Other", "Refused", "Do not know", "Not_Answered" => "Not Answered"));
            $this->XINRegisterRule("q5_75_{$field}_freq", array("q5_75{@}=={@}{$field}"), "Required if took {$label}");

            $this->addNumericElementRD("q5_75_{$field}_tabs", $this->indent . $this->indent . "Enter the number of tabs or caps:");
            $this->XINRegisterRule("q5_75_{$field}_tabs", array("q5_75{@}=={@}{$field}", "q5_75_{$field}_freq{@}=={@}tab_day|tab_week|tab_month|tab_everyday"), "Required if took {$label}", "q5_75_{$field}_tabs_group");

            $this->addNumericElementRD("q5_75_{$field}_days", $this->indent . $this->indent . "If you selected [(#)_____tabs or caps/day, for (#) ____days], please enter the number of days:");
            $this->XINRegisterRule("q5_75_{$field}_days", array("q5_75{@}=={@}{$field}", "q5_75_{$field}_freq{@}=={@}tab_day"), "You must specify number of days", "q5_75_{$field}_days_group");

            $this->addTextAreaElementRD("q5_75_{$field}_otherfreq", $this->indent . $this->indent . "If you selected [Other], please specify:");
            $this->XINRegisterRule("q5_75_{$field}_otherfreq", array("q5_75_{$field}_freq{@}=={@}other"), "You must specify other", "q5_75_{$field}_otherfreq_group");

        }

        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


    } //end function _page13() ======================================================



    function rulesPage13($fields)
    {
        $errors = array();

        function multSelect($fields, $question1, $question2)
        {
            return (($fields[$question1] == array(0=>null) && $fields[$question2] == "01_yes") || (empty($fields[$question1])) && $fields[$question2] == "01_yes");
        }


        //q5-69
        if (multSelect($fields, "q5_69", "q5_68"))
            $errors["q5_69"] = "You must specify month(s)";


        //q5-73
        if (multSelect($fields, "q5_73", "q5_72"))
            $errors["q5_73"] = "You must specify month(s)";


        return $errors;

    }




    function _page14(){   // ========================================================


        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('header', null, "Section 5: SIBLING PREGNANCY <br /><br />(PART 6 OF 9)");
        $this->form->addElement('static', null, "<br/>");

        $this->form->addElement('static', null, "<b><i>Now, I am going to ask you about some illnesses, surgeries and other procedures that you mighti have had during your pregnancy with [SIBLING]. I'm going to ask you about the time period from three months before you became pregnant until [DOBS].</i></b>");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('header', null, "<b/>Reproductive and Major Perinatal Infections");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<b><i>I am going to start off by asking you about some infections that you might have had during your pregnancy with [SIBLING]. Please refer to <u>List 7</u> in your preparatory guide and follow along.</i></b>");
        $this->form->addElement('static', null, "<br/>");


        //function with more complex rules
        $this->form->addFormRule(array(&$this, 'rulesPage14'));

        //q5-76
        $this->form->addElement('static', null, "5-76. Between [-3] and [DOBS] did you have any of the following infections?");

        $aToX = array("a" => "A. Bacterial Vaginosis", "b" => "B. Candidiasis", "c" => "C. Chlamydia", "d" => "D. Chicken pox", "e" => "E. Cytomegalovirus", "f" => "F. Genital Herpes", "g" =>"G. Group B Streptococcal infection", "h" =>"H. Hepatitis A", "i" =>"I. Hepatitis B", "j" => "J. Hepatitis C", "k" => "K. Human Papilloma Virus (HPV)", "l" => "L. Influenza", "m" =>"M. Mononucleosis", "n" => "N. Parvovirus or Fifth disease", "o" => "O. Pelvic Inflammatory Disease (PID)", "p" => "P. Pneumonia", "q" => "Q. Rubella or German measles", "r" => "R. Shingles", "s" => "S. Syphilis", "t" => "T. Toxoplasmosis", "u" =>"U. Trichomoniasis", "v" => "V. Upper respiratory infection", "w" => "W. Urinary tract infection", "x" => "X. Other conditions");
        //	reset($aToX);

        foreach($aToX as $field=>$label){

            $this->form->addElement("select", "q5_76_{$field}", $this->indent . "{$label}:", array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        }

        $this->addTextAreaElementRD('q5_76_other', $this->indent . $this->indent . " If you selected [Other conditions], (e.g., vaginitis, fibroids, venereal warts, or endometriosis), please specify:");
        $this->XINRegisterRule('q5_76_other', array("q5_76_x_other{@}=={@}01_yes"), "You must specify other", "q5_76_other_group");
        $this->form->addElement('static', null, $this->indent . $this->indent . " If you selected [Yes] for Herpes, go to question 5-77");
        $this->form->addElement('static', null, $this->indent . $this->indent . " If you selected [Yes] for Venereal/genital, go to question 5-78");
        $this->form->addElement('static', null, $this->indent . $this->indent . " If you selected [Yes] for any other infection on the list, go to question 5-79");
        $this->form->addElement('static', null, $this->indent . $this->indent . " If you selected [No], [Refused] or [Don't Know] for all, go to question 5-83");


        //q5-77
        $this->form->addElement ( "select", "q5_77", "5-77. During which months from [-3] to [DOBS] did you have the Herpes outbreak?", $this->negThreeToNine, "multiple size = '5'" );
        $this->form->addElement('static', null, $this->indent . $this->indent . " If you selected [Yes] for Herpes, go to question 5-80");
        $this->form->addElement('static', null, $this->indent . $this->indent . " If you selected [Yes] for Venereal/genital, go to question 5-80");
        $this->form->addElement('static', null, $this->indent . $this->indent . " If you selected [Yes] for any other infection on the list, go to question 5-80");
        $this->form->addElement('static', null, $this->indent . $this->indent . " If you selected [No], [Refused] or [Don't Know] for all, go to question 5-86");


        //q5-78
        $this->form->addElement ( "select", "q5_78", "5-78. During which months from [-3] to [DOBS] did you have the Venereal/genital warts outbreak?", $this->negThreeToTen, "multiple size = '5'" );
        $this->XINRegisterRule('q5_78', array("q5_76_x_other{@}=={@}01_yes"), "This is required if you had the Venereal/genital warts outbreak."); 
        $this->form->addElement('static', null, $this->indent . "If you selected [Yes] for any other infection on the list, go to question 5-79");
        $this->form->addElement('static', null, $this->indent . " If you selected [No], [Refused] or [Don't Know] for <u>all</u> infections, go to question 5-83");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


        //q5-79
        $this->form->addElement('static', null, "5-79. During which months from [-3] to [DOBS] did you have [INFECTION]?");
        $this->form->addElement('static', null, "<br/>");

        $oneToThree = array("1"=>"#1", "2"=>"#2", "3"=>"#3");

        foreach ($oneToThree as $field=>$label)	{

            $this->form->addElement ( "select", "q5_79_{$field}", $this->indent ."INFECTION {$label}:", array(NULL=>"") + $aToX + array("88_refused"=>"88 Refused", "99_Do_not_know"=>"99 Do not know", "not_answered"=>"Not Answered"));
            $this->form->addElement ( "select", "q5_79_m_{$field}", $this->indent . $this->indent . "Select all that apply:", $this->negThreeToTen, "multiple size = '5'" );
            $this->XINRegisterRule("q5_79_{$field}", array("q5_79_{$field}{@}=={@}NEVER_REQUIRED"));
            //	foreach ($aToX as $f=>$l)
            //	{	
            //		if (($f!="f_genital_herpes") && ($f!="x_other") && ($field=="1"))
            //		{
            //			$this->XINRegisterRule("q5_79_{$field}", array("q5_76_{$f}{@}=={@}01_yes"), "You must specify infection as indicated in 5-76");
            //			$this->XINRegisterRule("q5_79_m_{$field}", array("q5_76_{$f}{@}=={@}01_yes"), "You must specify month(s)");		
            //		}
            //	}	

            $this->XINRegisterRule('q5_79_other', array("q5_76_x_other{@}=={@}01_yes"), "You must specify other");
        }

        $this->form->addElement('static', null, "<br/>");


        //q5-80
        $this->form->addElement("select", "q5_80", "5-80. Was medication taken for the infection?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q5_80", array("q5_79_1{@}!={@}"), "Required if 5-79 is specified");
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 5-83");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


        //q5-81
        $this->form->addElement('static', null, "5-81. What did you take? Refer to List 8a");

        foreach ($oneToThree as $field=>$label){

            $this->form->addElement('static', null, "<br/>");
            $this->form->addElement('static', null,  $this->indent . "INFECTION {$label}:");

            for ($i=1; $i<4; $i++)
            {
                $this->form->addElement("select", "q5_81_{$field}_med{$i}",   $this->indent . $this->indent . "Med {$i}:",  array(NULL=>"", "Achromycin ", "Acyclovir ", "Amoxicillin ", "Amoxil ", "Augmentin ", "Azithromycin", "Bactrim", "Biaxin ", "Cefprozil", "Ceftin ", "Cefuroxime", "Cefzil ", "Cephalexin", "Cipro ", "Ciprofloxacin", "Clarithromycin", "Cleocin ", "Clindamycin", "Cofatrim", "Cotrim ", "Diflucan ", "Doxycin", "Doxycycline ", "Doxytec", "Dynacin", "EES", "E-Mycin ", "Erythrocin", "Erythromycin", "Flagyl ", "Fluconazole", "Ilosone", "Keflex ", "Levaquin", "Levofloxacin", "Macrobid ", "Metronidazole", "Minocin", "Minocycline", "Mycostatin", "Nilstat", "Nitrofurantoin", "Novacet ", "Novo-Doxylin", "Nystatin", "Nystex", "Panmycin", "Penicillin", "Penicillin VK ", "Penicillin V potassium", "Protostat", "Quixin", "Septra ", "Sodium sulfacetamide-sulfur", "Sulfatrim", "Sumycin", "Tetracap", "Tetracycline", "Topicycline", "Trimox", "Valacyclovir", "Valtrex ", "Veetids ", "Vibramycin ", "Vibra-Tabs", "Zithromax ", "Zovirax" , "other"=>"Other", "88_refused"=>"88 Refused", "99_do_not_know"=>"99 Do not know", "Not_Answered" => "Not Answered"));

                if ($field ==1 && $i==1)
                    $this->XINRegisterRule("q5_81_{$field}_med{$i}", array("q5_80{@}=={@}01_yes"), "Specify medication");
                else
                    $this->XINRegisterRule("q5_81_{$field}_med{$i}", array("q5_81_{$field}_{$i}{@}=={@}NEVER_REQUIRED"));	
            }
        }

        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


        //q5-82
        $this->form->addElement('static', null, "5-82. When was it taken? For [INFECTION] indicated above, select all months that apply:");
        $this->form->addElement('static', null, "<br/>");

        foreach($this->oneToThree as $field=>$label){

            $this->form->addElement('static', null, $this->indent . "INFECTION {$label}:");


            for ($i=1; $i<4; $i++){
                $this->form->addElement("select", "q5_82_{$field}_med{$i}", $this->indent . $this->indent . "Med {$i}:", $this->negThreeToTen, 'multiple size = "5"'); 
                $this->XINRegisterRule("q5_82_{$field}_med{$i}", array("q5_82_{$field}_med{$i}{@}=={@}NEVER_REQUIRED"));
            }

            $this->form->addElement('static', null, "<br/>");
        }

        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


    }// end function _page14() ======================================================




    function rulesPage14($fields)
    {

        $errors = array();

        function multSelect($fields, $question1, $question2, $option)
        {
            return (($fields[$question1] == array(0=>null) && $fields[$question2] == $option) || (empty($fields[$question1])) && $fields[$question2] == $option);
        }


        //q5-77	
        if (multSelect($fields, "q5_77", "q5_76_f", "01_yes"))
            $errors["q5_77"] = "Required if had genital herpes"; 

        $letterOptions = array("a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x");


        //q5-79, q5-80
        for ($i=0; $i<23; $i++)
        {
            if ($fields["q5_76_$letterOptions[$i]"] == "01_yes")
            {
                if ($letterOptions[$i] != "f" && empty($fields["q5_79_1"])) 
                    $errors["q5_79_1"] = "Required if had any of the above infections with the exception of herpes";

                else if (empty($fields["q5_80"]))
                    $errors["q5_80"] = "Required if had any of the above infections";
            }			

            //q5-79 months
            if (multSelect($fields, "q5_79_m_1", "q5_76_$letterOptions[$i]", "01_yes"))
                $errors["q5_79_m_1"] = "You must specify month(s)";
        }


        //q5-82
        if (multSelect($fields, "q5_82_1_med1", "q5_80", "01_yes"))
            $errors["q5_82_1_med1"] = "You must specify month(s)";


        return $errors;
    }





    function _page15(){   // ========================================================


        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('header', null, "Section 5: SIBLING PREGNANCY <br /><br />(PART 7 OF 9)");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<b/>Other Illnesses");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<b><i>I am going to ask you about some illnesses that you might have had during your pregnancy with [SIBLING].</i></b>");
        $this->form->addElement('static', null, "<br/>");


        //function with more complex rules
        $this->form->addFormRule(array(&$this, 'rulesPage15'));


        //q5-83
        $this->form->addElement('static', null, "5-83. Between [-3] and [DOBS] did you have any of the following illnesses?");

        $aToM = array("a" => "A. Migraine", "b" => "B. Depression", "c" => "C. Nervousness", "d" => "D. Anxiety", "e" => "E. Bipolar", "f" => "F. Other Mental Disorders", "g" => "G. Epilepsy or Seizure", "h" => "H. Thyroid condition", "i" => "I. Allergy", "j" =>  "J. Asthma", "k" => "K. Arthritis", "l" => "L. Neurologic Disease", "m" => "M. Autoimmune Condition");
        //		reset($aToM);

        foreach ($aToM as $field => $label) {

            $this->form->addElement("select", "q5_83_ill_{$field}", $this->indent . "{$label}:", array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        }

        $this->addTextAreaElementRD('q5_83_f', $this->indent . "If you selected [f. Other Mental Disorders], please specify: ");
        $this->addTextAreaElementRD('q5_83_l', $this->indent . "If you selected [l. Neurologic Disease], please specify: ");
        $this->addTextAreaElementRD('q5_83_m', $this->indent . "If you selected [m. Autoimmune Condition], please specify: ");
        $this->form->addElement('static', null , $this->indent . "If you selected [Yes] for any illness on the list, go to question 5-84");
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] for all, go to question 5-88");
        $this->form->addElement('static', null, "<br/>");
        $this->XINRegisterRule('q5_83_f', array("q5_83_ill_f{@}=={@}01_yes"), "You must specify", "q5_83_f_group");
        $this->XINRegisterRule('q5_83_l', array("q5_83_ill_l{@}=={@}01_yes"), "You must specify", "q5_83_l_group");
        $this->XINRegisterRule('q5_83_m', array("q5_83_ill_m{@}=={@}01_yes"), "You must specify", "q5_83_m_group");
        $this->form->addElement('static', null, "<br/>");


        //q5-84
        $this->form->addElement('static', null, "5-84. During which months from [-3] to [DOBS] did you have [illness]? Specify illness as previously indicated and select all that apply:");

        $this->form->addElement('static', null, "<br/>");

        for ($i=1; $i<4; $i++){

            $this->form->addElement ("select", "q5_84_{$i}", $this->indent . "ILLNESS {$i}:", array(NULL=>"") + $aToM + array("88_refused"=>"88 Refused", "99_do_not_know"=>"99 Do not know", "not_answered"=>"Not Answered"));
            $this->XINRegisterRule("q5_84_{$i}", array("q5_84_{$i}{@}=={@}NEVER_REQUIRED"));

            $this->form->addElement ("select", "q5_84_{$i}_m", $this->indent . $this->indent . "Select all months that apply:", $this->negThreeToTen, "multiple size = '5'" );
            $this->XINRegisterRule("q5_84_{$i}_m", array("q5_84_{$i}_m{@}=={@}NEVER_REQUIRED"));

            $this->form->addElement('static', null, "<br/>");
        }


        //q5-85
        $this->form->addElement("select", "q5_85", "5-85. Was medication taken for the first illness?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q5_85", array("q5_85{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement("select", "q5_85_illness2", "5-85. Was medication taken for the second illness?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q5_85_illness2", array("q5_85_illness2{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement("select", "q5_85_illness3", "5-85. Was medication taken for the third illness?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q5_85_illness3", array("q5_85_illness3{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 5-88");

        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


        //q5-86
        $this->form->addElement('static', null, "5-86. What did you take? For [ILLNESS] indicated above, specify medication: (refer to <u> List 8a</u>)");
        for ($i=1; $i<4; $i++){

            $this->form->addElement('static', null, "<br/>");
            $this->form->addElement('static', null,  $this->indent . "ILLNESS {$i}");
            $this->XINRegisterRule("q5_86_1", array("q5_85{@}=={@}01_yes"), "Required if took medication");
            $this->XINRegisterRule("q5_86_2", array("q5_86_2{@}=={@}NEVER_REQUIRED"));
            $this->XINRegisterRule("q5_86_3", array("q5_86_3{@}=={@}NEVER_REQUIRED"));

            foreach ($this->oneToThree as $field => $label){

                $this->form->addElement("select", "q5_86_{$i}_med{$field}",   $this->indent . $this->indent . "Med {$label}:",  array(NULL=>"", "Achromycin ", "Acyclovir ", "Amoxicillin ", "Amoxil ", "Augmentin ", "Azithromycin", "Bactrim", "Biaxin ", "Cefprozil", "Ceftin ", "Cefuroxime", "Cefzil ", "Cephalexin", "Cipro ", "Ciprofloxacin", "Clarithromycin", "Cleocin ", "Clindamycin", "Cofatrim", "Cotrim ", "Diflucan ", "Doxycin", "Doxycycline ", "Doxytec", "Dynacin", "EES", "E-Mycin ", "Erythrocin", "Erythromycin", "Flagyl ", "Fluconazole", "Ilosone", "Keflex ", "Levaquin", "Levofloxacin", "Macrobid ", "Metronidazole", "Minocin", "Minocycline", "Mycostatin", "Nilstat", "Nitrofurantoin", "Novacet ", "Novo-Doxylin", "Nystatin", "Nystex", "Panmycin", "Penicillin", "Penicillin VK ", "Penicillin V potassium", "Protostat", "Quixin", "Septra ", "Sodium sulfacetamide-sulfur", "Sulfatrim", "Sumycin", "Tetracap", "Tetracycline", "Topicycline", "Trimox", "Valacyclovir", "Valtrex ", "Veetids ", "Vibramycin ", "Vibra-Tabs", "Zithromax ", "Zovirax", "other"=>"Other", "88_refused"=>"88 Refused", "99_do_not_know"=>"99 Do not know", "not_answered"=>"Not Answered"));
                $this->XINRegisterRule("q5_86_1_med1", array("q5_85{@}=={@}01_yes"), "Specify medication");
                $this->XINRegisterRule("q5_86_2_med1", array("q5_86_2_med1{@}=={@}NEVER_REQUIRED"));
                $this->XINRegisterRule("q5_86_3_med1", array("q5_86_3_med1{@}=={@}NEVER_REQUIRED"));
                $this->XINRegisterRule("q5_86_{$i}_med2", array("q5_86_{$i}_med2{@}=={@}NEVER_REQUIRED"));
                $this->XINRegisterRule("q5_86_{$i}_med3", array("q5_86_{$i}_med3{@}=={@}NEVER_REQUIRED"));

                $this->addTextAreaElement("q5_86_{$i}_other{$field}", $this->indent . $this->indent . "Other medication:", array("q5_86_{$i}_med{$field}{@}=={@}other"), "You must specify other medication");			

            }
        }

        $this->form->addElement('static', null, "<br/>");

        //q5-87
        $this->form->addElement('static', null, "5-87. When was it taken? For [ILLNESS] and [MEDICATION] indicated above, select all that apply:");
        $this->form->addElement('static', null, "<br/>");

        foreach ($this->oneToThree as $field=>$label){

            $this->form->addElement('static', null,  $this->indent . "ILLNESS {$label}");


            for ($i=1; $i<4; $i++){

                $this->form->addElement("select", "q5_87_{$field}_med{$i}",   $this->indent . $this->indent . "Med {$i}:",  $this->negThreeToTen, "multiple size = '5'");
                $this->XINRegisterRule("q5_87_{$field}_med{$i}", array("q5_87_{$field}_med{$i}{@}=={@}NEVER_REQUIRED"));
            }

            $this->form->addElement('static', null, "<br/>");
        }
        $this->form->addElement('static', null, "<br/>");


        $this->form->addElement('header', null, "<b/>Oral/Dental Disease");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<b>Now I am going to ask you about some oral or dental diseases that you might have had during your pregnancy with [SIBLING].</b>");
        $this->form->addElement('static', null, "<br/>");


        //q5-88
        $this->form->addElement("select", "q5_88", "5-88. Between [-3] and [DOBS], did a doctor or dentist ever tell you that you had gingivitis or periodontitis?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 5-95");
        $this->form->addElement('static', null, "<br/>");


        //q5-89
        $this->form->addElement("select", "q5_89", "5-89. Did you take any medication for the gingivitis or periodontitis between [-3] and [DOBS]?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 5-92");
        $this->XINRegisterRule("q5_89", array("q5_88{@}=={@}01_yes"), "Required if had gingivitis or periodontitis");
        $this->form->addElement('static', null, "<br/>");

        //q5-90
        $this->form->addElement('static', null, "5-90. What medicine did you take?");
        $this->form->addElement('static', null, $this->indent . "<i>Probe: Anything else?</i>");
        $this->form->addElement('static', null, $this->indent . "<i>If can't recall, refer to <b>List 8a</b> in prep guide and read drug list:</i>");

        foreach ($this->oneToThree as $field=>$label){

            $this->form->addElement('static', null, "<br/>");
            $this->form->addElement("select", "q5_90_med_{$field}", $this->indent . "MED {$label}:", array(NULL=>"", "13" => "13 Clindamycin", "16" => "16 Doxycycline", "24 Metronidazole", "25 Minocyline", "29 Penicillin", "97_other"=>"97 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
            $this->addTextAreaElementRD("q5_90_other_{$field}", $this->indent . "If you selected [Other], please specify. OTHER MED {$label}:");
            $this->XINRegisterRule("q5_90_other_{$field}", array("q5_90_med_{$field}{@}=={@}97_other"), "You must specify other", "q5_90_other_{$field}_group");
        }

        $this->XINRegisterRule("q5_90_med_1", array("q5_89{@}=={@}01_yes"), "Required if took medication");
        $this->XINRegisterRule("q5_90_med_2", array("q5_90_med_2{@}=={@}NEVER_REQUIRED"));
        $this->XINRegisterRule("q5_90_med_3", array("q5_90_med_3{@}=={@}NEVER_REQUIRED"));
        $this->addTextAreaElementRD('q5_90_additional', $this->indent . "Additional");
        $this->XINRegisterRule("q5_90_additional", array("q5_90_additional{@}=={@}NEVER_REQUIRED"), "q5_90_additional_group");
        $this->form->addElement('static', null, "<br/>");

        $this->form->addElement('static', null, $this->indent . "<i>For <u>each</u> medication given in 5-90, go to 5-91</i>");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


        //q5-91
        $this->form->addElement('static', null, "5-91. During which months from [-3] to [DOBS] did you take [MEDICATION]?");  

        foreach ($this->oneToThree as $field=>$label){

            $this->form->addElement('static', null, "<br/>");
            $this->form->addElement ( "select", "q5_91_{$field}", $this->indent . "MED {$label} (Select all that apply):", $this->negThreeToTen, "multiple size = '5'" );
        }

        $this->form->addElement('static', null, "<br/>");

        //q5-92
        $this->form->addElement("select", "q5_92", "5-92. Did you have any treatment other than antibiotics for gingivitis or periodontitis between [-3] and [DOBS]?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q5_92", array("q5_88{@}=={@}01_yes"), "Required if had gingivitis or periodontitis");
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 5-95");
        $this->form->addElement('static', null, "<br/>");

        //q5-93
        $this->form->addElement("select", "q5_93", "5-93. What treatments did you have? Was it...",  array(NULL=>"", "01" => "01 Root planing and scaling", "02" => "02 Gingival curettage", "03" => "03  Splinting", "04_other" => "04 Other ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q5_93", array("q5_92{@}=={@}01_yes"), "Required if had other treatment");
        $this->addTextAreaElementRD('q5_93_other', $this->indent . "If you selected [Other], please specify (Other #1):");
        $this->XINRegisterRule("q5_93_other", array("q5_93{@}=={@}04_other"), "You must specify other", "q5_93_other_group");
        $this->form->addElement('static', null, "<br/>");
        $this->addTextAreaElementRD('q5_93_other2', $this->indent . "If you selected [Other], please specify (Other #2):");
        $this->XINRegisterRule("q5_93_other2", array("q5_93_other2{@}=={@}NEVER_REQUIRED"), "q5_93_other2_group");
        $this->form->addElement('static', null, "<br/>");

        //q5-94
        $this->form->addElement ( "select", "q5_94", "5-94. During which months from [-3] to [DOBS] did you get the treatment? (Select all that apply):", $this->negThreeToTen, "multiple size = '5'" );
        $this->XINRegisterRule("q5_94", array("q5_93{@}=={@}01|02|03|04_other"), "Specify month(s)");
        $this->form->addElement('static', null, "<br/>");

    } //end function _page15() =====================================================



    function rulesPage15($fields)
    {

        $errors = array();

        function multSelect($fields, $question1, $question2, $option)
        {
            return (($fields[$question1] == array(0=>null) && $fields[$question2] == $option) || (empty($fields[$question1])) && $fields[$question2] == $option);
        }


        $options = array("a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m");


        //q5-84, q5-85	
        for ($i=0; $i<13; $i++)
        {
            if ($fields["q5_83_ill_$options[$i]"] == "01_yes")
            {
                if (empty($fields["q5_85"]))
                    $errors["q5_85"] = "Required if had any of the above illnesses";

                if (empty($fields["q5_84_1"]))
                {
                    $errors["q5_84_1"] = "Required if had any of the above illnesses";
                    break;
                }
            }

            //q5-84
            if (multSelect($fields, "q5_84_1_m", "q5_83_ill_$options[$i]", "01_yes"))
            {
                if(empty($fields["q5_84_1"]))
                    $errors["q5_84_1"] = "You must specify illness";

                $errors["q5_84_1_m"] = "You must specify month(s)";
            }
        }


        //q5-87	
        if (multSelect($fields, "q5_87_1_med1", "q5_85", "01_yes"))
            $errors["q5_87_1_med1"] = "You must specify month(s)";


        //q5-91
        if (multSelect($fields, "q5_91_1", "q5_89", "01_yes"))
            $errors["q5_91_1"] = "You must specify month(s)";


        //q5-94
        if (multSelect($fields, "q5_94", "q5_92", "01_yes"))
            $errors["q5_94"] = "You must specify month(s)";

        return $errors;
    }




    function _page16(){   // ========================================================


        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('header', null, "Section 5: SIBLING PREGNANCY <br /><br />(PART 8 OF 9)");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<b/>Injuries");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<b><i>The next few questions are about any injuries that you might have had during your pregnancy with [SIBLING].</i></b>");
        $this->form->addElement('static', null, "<br/>");


        //function with more complex rules
        $this->form->addFormRule(array(&$this, 'rulesPage16'));

        //q5-95
        $this->form->addElement("select", "q5_95", "5-95. During your pregnancy with [SIBLING], did you have an injury that required medical attention?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 5-106");
        $this->form->addElement('static', null, "<br/>");

        //q5-96
        $this->addTextAreaElementRD('q5_96', "5-96. What injury did you have?");
        $this->XINRegisterRule("q5_96", array("q5_95{@}=={@}01_yes"), "Required if had injury", "q5_96_group");
        $this->form->addElement('static', null, "<br/>");

        //q5-97
        $this->form->addElement ( "select", "q5_97", "5-97 Between [-3] and [DOBS], during which month did this injury happen? (Select all that apply):", $this->negThreeToTen, "multiple size = '5'" );
        $this->XINRegisterRule("q5_97", array("q5_95{@}=={@}01_yes"), "Required if had injury");
        $this->form->addElement('static', null, "<br/>");

        //q5-98
        $this->form->addElement("select", "q5_98", "5-98. Did you ever lose consciousness because of this injury?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q5_98", array("q5_95{@}=={@}01_yes"), "Required if had injury");
        $this->form->addElement('static', null, "<br/>");

        //q5-99
        $this->form->addElement("select", "q5_99", "5-99. Was medication taken for the injury?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q5_99", array("q5_95{@}=={@}01_yes"), "Required if had injury");
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 5-102");
        $this->form->addElement('static', null, "<br/>");

        //q5-100
        $this->form->addElement('static', null, "5-100 What did you take?");
        $this->addTextAreaElementRD('q5_100_1', $this->indent . "Med 1:");
        $this->XINRegisterRule("q5_100_1", array("q5_99{@}=={@}01_yes"), "Required if took medication", "q5_100_1_group");
        $this->addTextAreaElementRD('q5_100_2', $this->indent . "Med 2:");
        $this->XINRegisterRule("q5_100_2", array("q5_100_2{@}=={@}NEVER_REQUIRED"), "q5_100_2_group");
        $this->addTextAreaElementRD('q5_100_3', $this->indent . "Med 3:");
        $this->XINRegisterRule("q5_100_3", array("q5_100_3{@}=={@}NEVER_REQUIRED"), "q5_100_3_group");
        $this->form->addElement('static', null, "<br/>");


        //q5-101
        $this->form->addElement('static', null, "5-101. When was it taken?");

        for ($i=1; $i<4; $i++)
            $this->form->addElement("select", "q5_101_{$i}",   $this->indent . "MED #{$i} (Select all that apply):", $this->negThreeToNine, "multiple size = '5'");

        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


        //q5-102
        $this->form->addElement("select", "q5_102", "5-102. During your pregnancy with [SIBLING], did you have any other injury that required medical attention?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q5_102", array("q5_95{@}=={@}01_yes"), "Required if had injury");
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 5-106");
        $this->form->addElement('static', null, "<br/>");


        //q5-103
        $this->addTextAreaElementRD('q5_103', "5-103. What was the other injury you had?");
        $this->XINRegisterRule("q5_103", array("q5_102{@}=={@}01_yes"), "Required if had other injury", "q5_103_group");
        $this->form->addElement('static', null, "<br/>");


        //q5-104
        $this->form->addElement('static', null, "5-104. Between [-3] and [DOBS], during which month did this other injury happen?"); 
        $this->XINRegisterRule("q5_104", array("q5_102{@}=={@}01_yes"), "Required if had other injury");
        $this->form->addElement("select", "q5_104", $this->indent . "Month # (Select all that apply):", $this->negThreeToTen, "multiple size = '5'");
        $this->form->addElement('static', null, "<br/>");

        //q5-105
        $this->form->addElement("select", "q5_105", "5-105. Did you ever lose consciousness because of this other injury?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q5_105", array("q5_102{@}=={@}01_yes"), "Required if had other injury");


        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('header', null, "<b/>Surgery");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<b><i>Now, I'm going to ask you about any surgeries or procedures that you might have had during your pregnancy with [SIBLING].</i></b>");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


        //q5-106
        $this->form->addElement("select", "q5_106", "5-106. During your pregnancy with [SIBLING], did you have any dental, medical, or surgical procedures that required the use of general or local anesthesia?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 5-110");
        $this->form->addElement('static', null, "<br/>");


        //q5-107
        $this->form->addElement('static', null, "5-107. What procedure(s) did you have done?");
        $this->form->addElement('static', null, "<br/>");

        for ($i=1; $i<4; $i++)
            $this->addTextAreaElementRD("q5_107_{$i}", $this->indent . "Procedure #{$i}:");

        $this->XINRegisterRule("q5_107_1", array("q5_106{@}=={@}01_yes"), "Specify procedure 1", "q5_107_1_group");
        $this->XINRegisterRule("q5_107_2", array("q5_107_2{@}=={@}NEVER_REQUIRED"), "q5_107_2_group");
        $this->XINRegisterRule("q5_107_3", array("q5_107_3{@}=={@}NEVER_REQUIRED"), "q5_107_3_group");
        $this->form->addElement('static', null, "<br/>");


        //q5-108
        $this->form->addElement('static', null, "5-108. For [PROCEDURE], did you have general anesthesia or local anesthesia?");
        $this->form->addElement('static', null, "<br/>");

        for ($i=1; $i<4; $i++)
        {
            $this->form->addElement('select', "q5_108_p{$i}", $this->indent . "Procedure #1", array(NULL=>"", "01" => "01 General", "02" => "02 Local", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
            $this->form->addElement('static', null, "<br/>");
        }

        $this->XINRegisterRule("q5_108_p1", array("q5_106{@}=={@}01_yes"), "Required if procedure was done");
        $this->XINRegisterRule("q5_108_p2", array("q5_108_p2{@}=={@}NEVER_REQUIRED"));
        $this->XINRegisterRule("q5_108_p3", array("q5_108_p3{@}=={@}NEVER_REQUIRED"));

        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, $this->indent . "If you selected [Refused] or [Don't Know] skip to question 5-110");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


        //q5-109
        $this->form->addElement('static', null, "5-109. In which month between [-3] and [DOBS] did you receive the anesthesia?"); 
        $this->form->addElement("select", "q5_109", $this->indent . "Month # (Select all that apply):", $this->negThreeToTen, "multiple size = '5'");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


    }// end function _page16() =====================================================



    function rulesPage16($fields)
    {

        $errors = array();

        function multSelect($fields, $question1, $question2, $option)
        {
            return ($fields[$question1] == array(0=>null) || (empty($fields[$question1])) && $fields[$question2] == $option);
        }


        //q5-97
        if (multSelect($fields, "q5_97", "q5_95", "01_yes"))
            $errors["q5_97"] = "You must specify month(s)";


        //q5-101
        if (multSelect($fields, "q5_101_1", "q5_99", "01_yes"))
            $errors["q5_101_1"] = "You must specify month(s)";


        //q5-104
        if (multSelect($fields, "q5_104", "q5_102", "01_yes"))
            $errors["q5_104"] = "You must sepcify month(s)";


        //q5-109
        for ($i = 1; $i<=4; $i++)
        {
            if(multSelect($fields, "q5_109", "q5_108_p$i", "01") || multSelect($fields, "q5_109", "q5_108_p$i", "02"))	
            {
                $errors["q5_109"] = "You must specify month(s)";
                break;
            }
        }

        return $errors;
    }



    function _page17(){   // ========================================================


        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('header', null, "Section 5: SIBLING PREGNANCY <br /><br />(PART 9 OF 9)");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<b/>Other Procedures");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


        //function with more complex rules
        $this->form->addFormRule(array(&$this, 'rulesPage17'));


        //q5-110
        $this->form->addElement('static', null, "5-110. During your pregnancy with [SIBLING], did you have...");

        $aToG = array("a" => "A. X-rays, including dental", "b" => "B. Mammogram", "c" => "C. CT/CAT scans", "d" => "D. MRI/magnetic resonance", "e" => "E. Radionuclide study or scan", "f" => "F. Radiation treatments or scan", "g" =>"G. Other");

        foreach($aToG as $field=>$label){

            $this->form->addElement("select", "q5_110_{$field}", $this->indent . "{$label}:", array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        }

        $this->addTextAreaElementRD('q5_110_other', $this->indent . 'If you selected [Other], please specify:');
        $this->XINRegisterRule("q5_110_other", array("q5_110_g{@}=={@}01_yes"), "You must specify other", "q5_110_other_group");
        $this->form->addElement('static', null, $this->indent . "If you selected [Yes] for mammogram, go to question 5-112");
        $this->form->addElement('static', null, $this->indent . "If you selected [Yes] for any other procedure, go to question 5-111");
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] for <u>all</u>, go to question 5-113");
        $this->form->addElement('static', null, "<br/>");


        //q5-111
        $this->form->addElement('static', null, "5-111. What part of your body was tested?");
        $this->form->addElement('static', null, "<br/>");

        $this->form->addElement('static', null, "<br/>");

        for ($i=1; $i<4; $i++)
        {
            $this->form->addElement('select', "q5_111_proc{$i}", $this->indent . "Procedure #{$i} as indicated previously:", array(NULL=>"") + $aToG + array("88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
            $this->addTextAreaElementRD("q5_111_bodypart{$i}", $this->indent . $this->indent . "Body part tested:");
            $this->form->addElement('static', null, "<br/>");

            $this->XINRegisterRule("q5_111_proc{$i}", array("q5_111_proc{$i}{@}=={@}NEVER_REQUIRED"));
            $this->XINRegisterRule("q5_111_bodypart{$i}", array("q5_111_bodypart{$i}{@}=={@}NEVER_REQUIRED"), "Specify body part", "q5_111_bodypart{$i}_group");
        }

        $this->form->addElement('static', null, "<br/>");



        //q5-112
        $this->form->addElement('static', null, "5-112. During which month between [-3] and [DOBS] was the [PROCEDURE] done? Select all that apply: ");
        $this->form->addElement('static', null, "<br/>");


        for ($i=1; $i<4; $i++)
        {
            $this->form->addElement('select', "q5_112_proc{$i}", $this->indent . "Procedure #{$i} as indicated previously:", array(NULL=>"") + $aToG + array("88_refused"=>"88 Refused", "99_do_not_know"=>"99 Do not know", "not_answered"=>"Not Answered"));
            $this->form->addElement('select', "q5_112_month{$i}", $this->indent . $this->indent . "Month:",  array(NULL=>"","-3" => "-3", "-2" => "-2", "-1" => "-1", "01" => "01", "02" => "02", "03" => "03 ", "04" => "04", "05" => "05", "06" => "06", "07" => "07", "08" => "08", "09" => "09", "10" => "10",  "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered" => "Not Answered"), "multiple size = '5'");
            $this->XINRegisterRule("q5_112_proc{$i}", array("q5_112{@}=={@}00_specify"), "You must specify procedure and month(s)");
            $this->XINRegisterRule("q5_112_month{$i}", array("q5_112_proc{$i}{@}!={@}NULL"), "You must specify month(s)");
        }

        $this->XINRegisterRule("q5_112_proc2", array("q5_112_proc2{@}=={@}NEVER_REQUIRED"));
        $this->XINRegisterRule("q5_112_proc3", array("q5_112_proc3{@}=={@}NEVER_REQUIRED"));


        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('header', null, "<b/>Medication Use");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<b/>This should be asked about medications not already reported before.");

        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<b><i>We are interested in medications, including over-the-counter medications that you might have taken during your pregnancy with [SIBLING].</i></b>");
        $this->form->addElement('static', null, "<br/>");

        $this->form->addElement('static', null, "<b><i>Please refer to <u>LISTS 8A through 8N</u> in your preparatory guide so that we can get the most accurate information possible.</i><b>");
        $this->form->addElement('static', null, "<br/>");

        $this->form->addElement('static', null, "<b><i>The medications in the list have been organized as best as possible by condition so please look for the heading and find your medication under that.</i></b>");
        $this->form->addElement('static', null, "<br/>");

        $this->form->addElement('static', null, "<b><i>If you do not see your medication, please look under the ???other medications' category. If your medication is not listed at all, we still want you to tell us about it. Medications can be in pill form, nasal spray, patches, creams, etc.</i></b>");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


        //q5-113
        $this->form->addElement('static', null, "5-113. Between [-3] and [DOBS] did you take any medications for the following conditions?");
        $aToJ = array("a" => "A. General headaches", "b" => "B. Back pain", "c" => "C.Chest pain ", "d" => "D. Cold", "e" => "E. Acne", "f" => "F. For dieting", "g" =>"G. Heartburn", "h" =>"H. To relieve constipation or diarrhea", "i" =>"I. Sleep disorder", "j" =>  "J. Other");
        reset($aToJ);

        while(list($field, $label) = each($aToJ)){

            $this->form->addElement("select", "q5_113_{$field}", $this->indent . "{$label}:", array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        }

        $this->addTextAreaElementRD('q5_113_other', $this->indent . "If you selected [Other], please specify:");
        $this->XINRegisterRule("q5_113_other", array("q5_113_j{@}=={@}01_yes"), "You must specify other", "q5_113_other_group");	
        $this->form->addElement('static', null,  $this->indent . "If you selected [Yes] for any condition in 5-113, go to question 5-114");
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] for <u>all</u>, skip to the next section");
        $this->form->addElement('static', null, "<br/>");


        //q5-114
        $this->form->addElement('static', null, "5-114. What medicine did you take for [CONDITION]? Select condition(s) as indicated above and specify medication taken for each:");
        $this->form->addElement('static', null, $this->indent . "<i>Refer to <b>List 8a</b> through <b>8n</b> in prep guide.</i>");
        $this->form->addElement('static', null, "<br/>");


        for ($i = 1; $i<=5; $i++)
        {		
            $this->form->addElement('select', "q5_114_{$i}", $this->indent . "Condition {$i}: ", (array(NULL=> "") + $aToJ + array("88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered")));

            for ($j = 1; $j<4; $j++)
            {
                $this->addTextAreaElementRD("q5_114_{$i}_med{$j}", $this->indent . $this->indent . "Medication #{$j}: ");
                if ($i>1 || ($i==1 && $j>1))
                    $this->XINRegisterRule("q5_114_{$i}_med{$j}", array("q5_114_{$i}_med{$j}{@}=={@}NEVER_REQUIRED"), "q5_114_{$i}_med{$j}_group");
            }

            if ($i>1)
                $this->XINRegisterRule("q5_114_{$i}", array("q5_114_{$i}{@}=={@}NEVER_REQUIRED"));
        }	

        $this->XINRegisterRule("q5_114_1", array("q5_114{@}=={@}00_specify"), "Specify condition");
        $this->XINRegisterRule("q5_114_1_med1", array("q5_114{@}=={@}00_specify"), "Specify medication", "q5_114_1_med1_group");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


        //q5-115
        $this->form->addElement('static', null, "5-115. Between [-3] and [DOBS], which months did you take the medication? Select condition and medication as indicated above and select all months that apply:");

        for ($i = 1; $i<=7; $i++)
        {

            $this->form->addElement('static', null, "<br/>");
            $this->form->addElement('select', "q5_115_condition{$i}", "{$i}. Condition: ", (array(NULL=> "") + $aToJ + array("88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered")));

            $this->addTextAreaElementRD("q5_115_condition{$i}_med{$i}", $this->indent . "Medication: ");
            $this->form->addElement('select', "q5_115_months{$i}", $this->indent . "Months: ", $this->negThreeToTen, "multiple size = '5'");

            $this->XINRegisterRule("q5_115_condition{$i}", array("q5_115_condition{$i}{@}=={@}NEVER_REQUIRED"));
            $this->XINRegisterRule("q5_115_condition{$i}_med{$i}", array("q5_115_condition{$i}_med{$i}{@}=={@}NEVER_REQUIRED"), "q5_115_condition{$i}_med{$i}_group");

        }

        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('header', null, "END Section 5.");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");

    } //end function _page17() =====================================================


    function rulesPage17($fields)
    {

        $errors = array();

        function multSelect($fields, $question1, $question2, $option)
        {
            return (($fields[$question1] == array(0=>null) && $fields[$question2] == $option) || (empty($fields[$question1])) && $fields[$question2] == $option);
        }


        $options = array("a", "c", "d", "e", "f", "g");


        //q5-111
        for ($i=0; $i<6; $i++)
        {
            if ($fields["q5_110_$options[$i]"] == "01_yes" && empty($fields["q5_111_proc1"]))
            {
                $errors["q5_111_proc1"] = "Required if had any of the above procedures, other than mammogram";
            }

            if ($fields["q5_110_$options[$i]"] == "01_yes" && empty($fields["q5_111_bodypart1"]))
            {
                $errors["q5_111_bodypart1_group"] = "Required if had any of the above procedures, other than mammogram";
                break;
            }
        }	


        $options2 = array("a", "b", "c", "d", "e", "f", "g");


        //q5-112
        for ($i=0; $i<7; $i++)
        {

            if ($fields["q5_110_$options2[$i]"] == "01_yes" && empty($fields["q5_112_proc1"]))
            {
                $errors["q5_112_proc1"] = "Required if had any of the above procedures";
            }

            if (multSelect($fields, "q5_112_month1", "q5_110_$options[$i]", "01_yes"))
            {
                $errors["q5_112_month1"] = "You must specify month(s)";
                break;
            }
        }


        $options3 = array("a", "b", "c", "d", "e", "f", "g", "h", "i", "j");


        //q5-114, q5-115
        for ($i=0; $i<10; $i++)
        {


            if ($fields["q5_113_$options3[$i]"] == "01_yes" && empty($fields["q5_114_1"]))
                $errors["q5_114_1"] = "Required if took medication for any of the above conditions";

            if ($fields["q5_113_$options3[$i]"] == "01_yes" && empty($fields["q5_114_1_med1"]))
                $errors["q5_114_1_med1_group"] = "Required if took medication for any of the above conditions";

            if ($fields["q5_113_$options3[$i]"] == "01_yes" && empty($fields["q5_115_condition1"]))
                $errors["q5_115_condition1"] = "Required if took medication for any of the above conditions";

            if ($fields["q5_113_$options3[$i]"] == "01_yes" && empty($fields["q5_115_condition1_med1"]))
                $errors["q5_115_condition1_med1_group"] = "Required if took medication for any of the above conditions";

            if (multSelect($fields, "q5_115_months1", "q5_113_$options[$i]", "01_yes"))
            {
                $errors["q5_115_months1"] = "You must specify month(s)";
                break;
            }

        }


        return $errors;
    }




    function _page18(){   // ========================================================


        $answerOptions1_9 = array(null=>"", "1"=>"1", "2"=>"2", "3"=>"3", "4"=>"4", "5"=>"5", "6"=>"6", "7"=>"7", "8"=>"8", "9"=>"9", "88_Refused" => "88 Refused", "99_Do_not_know" => "99 Do not know", "not_answered" => "Not Answered");


        $this->form->addElement('header', null, "Section 6. DIET <br /><br /> (PART 1 OF 2)");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");

        $this->form->addElement('static', null, "<b><i>Now I am going to ask you some questions regarding your diet.</i></b>");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


        //function with more complex rules
        $this->form->addFormRule(array(&$this, 'rulesPage18'));


        $i = 0; // to choose the varying questions - array index
        $section = 6; // section #
        $question = 1; // question #
        $skip = 1; // for "go to question" #z
        for ($question = 1; $question <= 81; $question += 1){

            $skip = $question + 4;

            $questions =  array("During your pregnancy with [SIBLING], did you take any prenatal vitamins?", "During your pregnancy with [SIBLING] did you take any Multivitamins?", "During [-3] to [DOBS] did you take any vitamin A?", "During your pregnancy with [SIBLING] did you take any beta-carotene?", "During your pregnancy with [SIBLING] did you take any vitamin B6?", "During your pregnancy with [SIBLING], did you take any vitamin B12?", "During your pregnancy with [SIBLING] did you take any folic acid?", "During your pregnancy with [SIBLING] did you take any vitamin C?", "During your pregnancy with [SIBLING] did you take any vitamin D?", "During your pregnancy with [SIBLING] did you take any vitamin D-fortified food or drink?", "During your pregnancy with [SIBLING] did you take any vitamin E?", "During your pregnancy with [SIBLING] did you take iron?", "During your pregnancy with [SIBLING] did you take any calcium (including a calcium plus vitamin D supplement or antacids, like Tums)?", "During your pregnancy with [SIBLING] have you take any calcium-fortified food or drink?", "During your pregnancy with [SIBLING] did you take any zinc?", "During your pregnancy with [SIBLING] did you take other supplements, such as Slim Fast, Instant Breakfast, protein powder, or brewer's yeast? ", "During your pregnancy with [SIBLING[ did you take any St. John's Worts?", "During your pregnancy with [SIBLING] did you take any ginseng?", "During your pregnancy with [SIBLING] did you take any omega-3 fatty acids?", "During your pregnancy with [SIBLING] did you take any fish oil?", "During your pregnancy with [SIBLING] did you take any other supplements or vitamins?");


            $this->form->addElement("select", "q{$section}_{$question}", "{$section}-{$question}. {$questions[$i]}",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
            $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question {$section}-{$skip}");

            $i += 1;
            $question += 1;
            $previous = $question - 1;


            $this->form->addElement('static', null, "<br/>");
            $this->addTextAreaElementRD("q{$section}_{$question}", "{$section}-{$question}. What was the name of the brand you took?");
            $this->XINRegisterRule("q{$section}_{$question}", array("q{$section}_{$previous}{@}=={@}01_yes"), "Specify brand", "q{$section}_{$question}_group"); 


            $question += 1;
            $this->form->addElement('static', null, "<br/>");
            $this->form->addElement ( "select", "q{$section}_{$question}", "{$section}-{$question}. Which month(s) of pregnancy did you take it? (Select all that apply):", $answerOptions1_9, "multiple size = '5'" );
            $this->XINRegisterRule("q{$section}_{$question}", array("q{$section}_{$previous}{@}=={@}01_yes"), "Specify brand"); 
            $this->form->addElement('static', null, "<br/>");

            $question += 1;
            $this->form->addElement("select", "q{$section}_{$question}", "{$section}-{$question}. How often/number of capsules did you take?",  array(NULL=>"", "tab_day" => "(#)_____tabs or caps/day, for (#) ____days", "tab_week"=>"(#)_____tabs or caps/week", "tab_month"=>"(#)_____tabs or caps/month", "tab_everyday"=>"(#)_____tabs or caps everyday", "Other" => "Other", "Refused"=>"Refused", "Do not know"=>"Don't Know", "Not_Answered" => "Not Answered"));
            $this->XINRegisterRule("q{$section}_{$question}", array("q{$section}_{$previous}{@}=={@}01_yes"), "Specify frequency"); 
            $this->form->addElement('static', null, "<br/>");
            $this->addNumericElementRD("q{$section}_{$question}_tabs_day", $this->indent . $this->indent . "# tabs or caps");
            $this->addNumericElementRD("q{$section}_{$question}_days", $this->indent . $this->indent . "If [(#)_____tabs or caps/day, for (#)____days], please enter the number of days:");
            $this->addTextAreaElementRD("q{$section}_{$question}_other", $this->indent . $this->indent . "If you selected [Other], please specify:");

            $this->XINRegisterRule("q{$section}_{$question}_other", array("q{$section}_{$question}{@}=={@}Other"), "You must specify other", "q{$section}_{$question}_other_group");

            $this->XINRegisterRule("q{$section}_{$question}_tabs_day", array("q{$section}_{$question}{@}=={@}tab_day|tab_week|tab_month|tab_everyday"), "You must specify # tabs or caps", "q{$section}_{$question}_tabs_day_group");
            $this->XINRegisterRule("q{$section}_{$question}_days", array("q{$section}_{$question}{@}=={@}tab_day"), "You must specify days", "q{$section}_{$question}_days_group");
            $this->form->addElement('static', null, "<br/>");
            $this->form->addElement('static', null, "<br/>");

        }


    } //end function _page18() =====================================================



    function rulesPage18($fields)
    {

        $errors = array();

        function multSelect($fields, $question1, $question2)
        {
            return (($fields[$question1] == array(0=>null) && $fields[$question2] == "01_yes") || (empty($fields[$question1])) && $fields[$question2] == "01_yes");
        }


        //q6-3, 6-7, 6-11... to q6-84
        for ($i=3; $i<84; $i+=4)
        {
            $j = $i-2;
            if (multSelect($fields, "q6_$i", "q6_$j"))
                $errors["q6_$i"] = "You must specify month(s)";
        }

        return $errors;

    }



    function _page19(){   // ========================================================


        $answerOptions1_9 = array(null=>"", "1"=>"1", "2"=>"2", "3"=>"3", "4"=>"4", "5"=>"5", "6"=>"6", "7"=>"7", "8"=>"8", "9"=>"9", "88_Refused" => "88 Refused", "99_Do_not_know" => "99 Do not know", "not_answered" => "Not Answered");

        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('header', null, "Section 6. DIET <br /><br /> (PART 2 OF 2)");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<b/>Water");
        $this->form->addElement('static', null, "<br/>");

        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<b><i>Now I am going to ask you questions regarding your water intake.</i></b>");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


        //function with more complex rules
        $this->form->addFormRule(array(&$this, 'rulesPage19'));


        //q6-85
        $this->form->addElement("select", "q6_85", "6-85. During your pregnancy with [SIBLING], about how many ounces of plain, non-carbonated, non-flavored water did you drink daily, including water used to make juice, punch, or other drinks?",  array(NULL=>"", "01" => "01 More than 64 ounces (8 cups)", "02" => "02 32 - 64 ounces (4 - 8 cups)", "03" => "03  8 - 32 ounces (1 - 4 cups)", "04" => "04 Less than 8 ounces (1 cup)", "05" => "05 None", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [None], [Refused] or [Don't Know] skip to question 6-96");
        $this->form->addElement('static', null, "<br/>");


        //q6-86
        $this->form->addElement("select", "q6_86", "6-86. During your pregnancy with [SIBLING], about how much of this plain drinking water came from your home faucets?",  array(NULL=>"", "01" => "01 All", "02" => "02 Most", "03" => "03  Some", "04" => "04 None", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [None], [Refused] or [Don't Know] skip to question 6-89");
        $this->XINRegisterRule("q6_86", array("q6_85{@}=={@}01|02|03|04"), "Required if drank plain water");
        $this->form->addElement('static', null, "<br/>");


        //q6-87
        $this->form->addElement("select", "q6_87", "6-87. Is the water you drink from your home faucets filtered through any purifier?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 6-89");
        $this->XINRegisterRule("q6_87", array("q6_86{@}=={@}01|02|03"), "Required if drank plain water from home faucets");
        $this->form->addElement('static', null, "<br/>");


        //q6-88
        $this->form->addElement("select", "q6_88", "6-88. Please state which type of filtration system you use.",  array(NULL=>"", "01_brita" => "01 Brita", "02_pur" => "02 Pur", "03_r_osmosis" => "03 Reverse Osmosis", "04_other" => "04 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->addTextAreaElementRD('q6_88_other', $this->indent . 'If you selected [Other], please specify:');
        $this->XINRegisterRule('q6_88_other', array("q6_88{@}=={@}04_other"), "You must specify other", "q6_88_other_group");
        $this->XINRegisterRule("q6_88", array("q6_87{@}=={@}01_yes"), "Required if drank purified water");
        $this->form->addElement('static', null, "<br/>");


        //q6-89
        $this->form->addElement("select", "q6_89", "6-89. During your pregnancy with [SIBLING], what was your main source of plain drinking water that did not come from your home? <i>Please select only one</i>",  array(NULL=>"", "01" => "01 Bottled water", "02" => "02 Dispensed bottled water (large water canister with spigot)", "03" => "03  Tap water and/or drinking fountain", "04_other" => "04 Other source", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->addTextAreaElementRD('q6_89_other', $this->indent . 'If you selected [Other], please specify:');
        $this->XINRegisterRule('q6_89_other', array("q6_89{@}=={@}04_other"), "You must specify other", "q6_89_other_group");
        $this->XINRegisterRule("q6_89", array("q6_85{@}=={@}01|02|03|04"), "Required if drank plain water");
        $this->form->addElement('static', null, "<br/>");


        //q6-90
        $this->form->addElement("select", "q6_90", "6-90. During your pregnancy with [SIBLING], how often did you drink water from plastic water bottles -- the disposable type that water is sold in? (ONE NEW BOTTLE = ONE TIME)",  array(NULL=>"", "01" => "01 Never ", "02" => "02 Once every 2 months, or less", "03" => "03  Once a month", "04" => "04 Once every 2 weeks", "05" => "05 Once a week", "06" => "06 Every other day", "07" => "07 Once a day", "08" => "08 Several times a day", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [Never] go to question 6-96");
        $this->XINRegisterRule("q6_90", array("q6_85{@}=={@}01|02|03|04"), "Required if drank plain water");
        $this->form->addElement('static', null, "<br/>");


        //q6-91
        $this->form->addElement("select", "q6_91", "6-91. Did you ever reuse these disposable water bottles?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No] go to question 6-93");
        $this->XINRegisterRule("q6_91", array("q6_90{@}=={@}02|03|04|05|06}07|08|88|88|Not_Answered"), "Required if drank water from plastic bottles");
        $this->form->addElement('static', null, "<br/>");		


        //q6-92
        $this->form->addElement("select", "q6_92", "6-92. During your pregnancy with [SIBLING], how often did you drink from disposable single-use water bottles that had been re-used?",  array(NULL=>"", "01" => "01 Never", "02" => "02 Less than once a month", "03" => "03  1 - 3 times a month", "04" => "04 Once a week", "05" => "05 2 - 3 times a week", "06" => "06 4 - 6 times a week", "07" => "07 Once a day", "08" => "08 More than once a day", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q6_92", array("q6_91{@}=={@}01_yes"), "Required if reused disposable water bottles");
        $this->form->addElement('static', null, "<br/>");


        //q6-93
        $this->form->addElement("select", "q6_93", "6-93. During your pregnancy with [SIBLING], how often did you drink water from a disposable single-use water bottle that had been frozen or heated?",  array(NULL=>"", "01" => "01 Never", "02" => "02 Less than once a month", "03" => "03  1 - 3 times a month", "04" => "04 Once a week", "05" => "05 2 - 3 times a week", "06" => "06 4 - 6 times a week", "07" => "07 Once a day", "08" => "08 More than once a day", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q6_93", array("q6_90{@}=={@}02|03|04|05|06}07|08|88|88|Not_Answered"), "Required if drank water from plastic bottles");
        $this->form->addElement('static', null, "<br/>");


        //q6-94
        $this->form->addElement("select", "q6_94", "6-94. During your pregnancy with [SIBLING], how often did you drink from a nondisposable (reusable) plastic water bottle?",  array(NULL=>"", "01" => "01 Never", "02" => "02 Less than once a month", "03" => "03  1 - 3 times a month", "04" => "04 Once a week", "05" => "05 2 - 3 times a week", "06" => "06 4 - 6 times a week", "07" => "07 Once a day", "08" => "08 More than once a day", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [01 Never], [Refused] or [Don't Know] skip to question 6-96");
        $this->XINRegisterRule("q6_94", array("q6_90{@}=={@}02|03|04|05|06}07|08|88|88|Not_Answered"), "Required if drank water from plastic bottles");
        $this->form->addElement('static', null, "<br/>");


        //q6-95
        $this->addTextAreaElementRD('q6_95', "6-95. What was the brand of the non-disposable (reusable) plastic water bottle you usually used?"); 
        $this->XINRegisterRule("q6_95", array("q6_94{@}=={@}02|03|04|05|06|07|08"), "Required if drank from a nondisposable plastic water bottle", "q6_95_group");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


        $this->form->addElement('header', null, "<b/>Food Preparation");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<b><i>Now I am going to ask you about your food preparation.</i></b>");
        $this->form->addElement('static', null, "<br/>");


        //q6-96
        $this->form->addElement("select", "q6_96", "6-96. During your pregnancy with [SIBLING], how often did you eat prepackaged foods or meals in a plastic dish or container?",  array(NULL=>"", "01" => "01 Never", "02" => "02 Less than once a month", "03" => "03  1 - 3 times a month", "04" => "04 Once a week", "05" => "05 2 - 3 times a week", "06" => "06 4 - 6 times a week", "07" => "07 Once a day", "08" => "08 More than once a day", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [Refused] or [Don't Know] skip to question 6-97");
        $this->form->addElement('static', null, "<br/>");


        //q6-97
        $this->form->addElement("select", "q6_97", "6-97. During your pregnancy with [SIBLING], how often did you eat prepackaged foods or meals in a Styrofoam dish or container?",  array(NULL=>"", "01" => "01 Never", "02" => "02 Less than once a month", "03" => "03  1 - 3 times a month", "04" => "04 Once a week", "05" => "05 2 - 3 times a week", "06" => "06 4 - 6 times a week", "07" => "07 Once a day", "08" => "08 More than once a day", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, "<br/>");


        //q6-98
        $this->form->addElement("select", "q6_98", "6-98. Do you do the majority of the cooking in the household?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 About half", "03" => "03  No", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 6-101");
        $this->form->addElement('static', null, "<br/>");


        //q6-99
        $this->form->addElement("select", "q6_99", "6-99. When using the stove-top, what percent of the time do you turn on the vent over the stove?",  array(NULL=>"", "01" => "01 Never", "02" => "02 Hardly ever (a few times a year)", "03" => "03  Sometimes (once a month)", "04" => "04 Somewhat frequently (2 - 4 times a month)", "05" => "05 Often (at least once a week)", "06" => "06 Always", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q6_99", array("q6_98{@}=={@}01_yes"), "Required if do majority of cooking");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


        //q6-100
        $this->form->addElement("select", "q6_100", "6-100. During your pregnancy with [SIBLING], how often did you microwave food in a plastic container for yourself to eat?",  array(NULL=>"", "01" => "01 Never", "02" => "02 Less than once a month", "03" => "03  Once a month", "04" => "04 Once every 2 weeks", "05" => "05 Once a week", "06" => "06 Every other day", "07" => "07 Once a day", "08" => "08 Several times a day", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q6_100", array("q6_98{@}=={@}01_yes"), "Required if do majority of cooking");
        $this->form->addElement('static', null, "<br/>");


        //q6-101
        $this->form->addElement("select", "q6_101", "6-101. During your pregnancy with [SIBLING] did you use plastic containers to store food in your household?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, "<br/>");

        //q6-102
        $this->form->addElement("select", "q6_102", "6-102. During your pregnancy with [SIBLING], did you use plastic wrap to store food in your household?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, "<br/>");


        //q6-103
        $this->form->addElement("select", "q6_103", "6-103. How many times per week did you eat fast food (including Chinese take-out) when you were pregnant with [SIBLING]?",  array(NULL=>"", "01" => "01 Never", "02" => "02 Less than once per week", "03" => "03  1 - 3 times per week", "04" => "04 4 - 6 times per week", "05" => "05 7 - 9 times per week", "06" => "06 10 - 12 times per week", "07" => "07 13 - 14 times per week", "08" => "08 15 or more times per week", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, "<br/>");


        //q6-104
        $this->form->addElement("select", "q6_104", "6-104. How many times per week did you eat pre-packaged candy or bakery items, like Twinkies when you were pregnant with [SIBLING?",  array(NULL=>"", "01" => "01 Never", "02" => "02 Less than once per week", "03" => "03  1 - 3 times per week", "04" => "04 4 - 6 times per week", "05" => "05 7 - 9 times per week", "06" => "06 10 - 12 times per week", "07" => "07 13 - 14 times per week", "08" => "08 15 or more times per week", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");

        $this->form->addElement('header', null, "<b/>Liquid Vitamin");
        $this->form->addElement('static', null, "<br/>");


        //q6-105
        $this->form->addElement("select", "q6_105", "6-105 In the past trimester, have you taken any liquid vitamins?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to Section 7");
        $this->form->addElement('static', null, "<br/>");


        //q6-106
        $this->addTextAreaElementRD('q6_106', "6-106. What was the name of the brand you took?");
        $this->XINRegisterRule("q6_106", array("q6_105{@}=={@}01_yes"), "Required if took liquid vitamins", "q6_106_group");
        $this->form->addElement('static', null, "<br/>");


        //q6-107
        $this->form->addElement ("select", "q6_107", "6-107. Which month(s) of pregnancy did you take it? (Select all that apply):", $answerOptions1_9, "multiple size = '5'" );
        $this->XINRegisterRule("q6_107", array("q6_105{@}=={@}01_yes"), "Required if took liquid vitamins");
        $this->form->addElement('static', null, "<br/>");


        //q6-108
        $this->form->addElement("select", "q6_108", "6-108. How often/number of capsules did you take?",  array(NULL=>"", "tab_day" => "(#)_____tabs or caps/day, for (#)____days", "tab_week"=>"(#)_____tabs or caps/week", "tab_month"=>"(#)_____tabs or caps/month", "tab_everyday"=>"(#)_____tabs or caps everyday", "Other" => "Other", "Refused" => "Refused", "Do not know"=>"Don't Know", "Not_Answered" => "Not Answered"));
        $this->XINRegisterRule("q6_108", array("q6_105{@}=={@}01_yes"), "Required if took liquid vitamins");
        $this->form->addElement('static', null, "<br/>");

        $this->addNumericElementRD('q6_108_tabs', $this->indent . $this->indent . "# tabs or caps:");
        $this->XINRegisterRule("q6_108_tabs", array("q6_108{@}=={@}tab_day|tab_week|tab_month|tab_everyday"), "You must specify # tabs or caps", "q6_108_tabs_group");

        $this->addNumericElementRD("q6_108_days", $this->indent . $this->indent . "If you selected [(#)_____tabs or caps/day, for (#) ____days], please enter the number of days:");
        $this->XINRegisterRule("q6_108_days", array("q6_108{@}=={@}tab_day"), "You must specify days", "q6_108_days_group");

        $this->addTextAreaElementRD('q6_108_other', $this->indent . $this->indent . "If you selected [Other], please specify:");
        $this->XINRegisterRule("q6_108_other", array("q6_108{@}=={@}Other"), "You must specify other", "q6_108_other_group");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('header', null, "END Section 6.");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");

    } //end function _page19() =====================================================


    function rulesPage19($fields)
    {

        $errors = array();


        function multSelect($fields, $question1, $question2)
        {
            return (($fields[$question1] == array(0=>null) && $fields[$question2] == "01_yes") || (empty($fields[$question1])) && $fields[$question2] == "01_yes");
        }


        //q6-107
        if (multSelect($fields, "q6_107", "q6_105"))
            $errors["q6_107"] = "You must specify month(s)";


        return $errors;
    }



    function _page20(){   // ========================================================


        $this->form->addElement('header', null, "Section 7. HOME ENVIRONMENTAL EXPOSURES <br /><br /> (PART 1 OF 3)");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");

        $this->form->addElement('static', null, "<b><i>Now I will ask you questions about the places you have lived since about 3 months before becoming pregnant with [SIBLING] until [DOBS]. Please refer to your calendar and to the Mother's Residential History form.</i></b>");


        //function with more complex rules
        $this->form->addFormRule(array(&$this, 'rulesPage20'));

        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<b/>Residential History");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");

        //q7-1
        $this->addTextAreaElementRD('q7_1', "7-1. What is the full address of the home where you lived? (please include house or apt number)"); 
        $this->form->addElement('static', null, "<br/>");

        //q7-2
        $this->form->addElement('static', null, "<br/>");

        $group[] =&$this->form->createElement("static", "month_header");
        $group[] =&$this->form->createElement("static", "year_header");
        $this->form->addGroup($group, "q7_2_headers", null, $this->_GUIDelimiter, false);
        unset($group);

        $group[] = &$this->form->createElement( "select", "q7_2_m", null, $this->months);
        $group[] = &$this->form->createElement ( "select", "q7_2_y", null, $this->years1950);
        $this->form->addGroup($group, "q7_2_group", "7-2. What was the month and year when you started living here?", $this->_GUIDelimiter, false);
        $this->XINRegisterRule("q7_2_m", array("q7_2_m{@}=={@}"),"You must specify month and year", "q7_2_group");
        $this->XINRegisterRule("q7_2_y", array("q7_2_y{@}=={@}"),"You must specify month and year", "q7_2_group");
        unset($group);
        $this->form->addElement('static', null, "<br/>");


        //q7-3
        $this->form->addElement("select", "q7_3", "7-3. What type of residence was/is it?",  array(NULL=>"", "01" => "01 Single house", "02" => "02 House attached to one or more other houses (duplex/triplex/4-plex)", "03" => "03  Building with 2-4 apartments", "04" => "04 Building with 5-19 apartments", "05" => "05 Building with 20 or more apartments", "06" => "06 Condominium", "07" => "07 Mobile home, RV, boat, van etc.", "08_other" => "08 Other", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->addTextAreaElementRD('q7_3_other', $this->indent . 'If you selected [Other], please specify:');
        $this->XINRegisterRule('q7_3_other', array("q7_3{@}=={@}08_other"), "You must specify other", "q7_3_other_group");
        $this->form->addElement('static', null, "<br/>");


        //q7-4
        $this->form->addElement("select", "q7_4", "7-4. Is this house, apartment, or mobile home...",  array(NULL=>"", "01" => "01 Owned by you or someone in this household with a mortgage or loan?", "02" => "02 Owned by you or someone in this household without a mortgage or loan)?", "03" => "03  Rented for cash rent", "04" => "04 Occupied without payment of cash rent?", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, "<br/>");


        //q7-5
        $this->addNumericElementRD('q7_5', $this->indent . "7-5. How many square feet was the home that you live in?");
        $this->form->addElement('static', null, "<br/>");


        //q7-6
        $this->form->addElement('static', null, "7-6. About what year was this house/building built?");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<i>Ask participant to make an estimate or check with the landlord if applicable.</i>");     
        $this->form->addElement('static', null, "<i>For an approximate year, code [1980s] as 1985, code [early 1980s] as 1982, code [late 1980s] as 1988, etc.</i>");
        $this->addTextAreaElementRD('q7_6_year', $this->indent . "Enter year");
        $this->addTextAreaElementRD('q7_6_appr_year', $this->indent . "OR Approximate year:");
        $this->XINRegisterRule("q7_6_year", array("q7_6_appr_year{@}=={@}"), "You must specify year", "q7_6_year_group");
        $this->XINRegisterRule("q7_6_appr_year", array("q7_6_year{@}=={@}"), "OR approximate year", "q7_6_appr_year_group");
        $this->form->addElement('static', null, "<br/>");


        //q7-7
        $this->form->addElement("select", "q7_7", "7-7. Did/does the tap water come from a private well?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, "<br/>");


        //q7-8
        $this->form->addElement("select", "q7_8", "7-8. About how old was the building when you moved in?",  array(NULL=>"", "01" => "01 More than 50 years old", "02" => "02 25-50 years old", "03" => "03  10-25 years old", "04" => "04 Less than 10 years old", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, "<br/>");


        //q7-9
        $this->form->addElement("select", "q7_9", "7-9. Was/is the outside of the building painted?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, "<br/>");


        //q7-10
        $this->form->addElement("select", "q7_10", "7-10. Was/is it within 1/4 mile of agricultural fields or a golf course?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, "<br/>");


        //q7-11
        $this->form->addElement("select", "q7_11", "7-11. Was/is it within 3 blocks of a gas station?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, "<br/>");


        //q7-12
        $this->form->addElement("select", "q7_12", "7-12. Was the house ever tested for lead?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 7-14");
        $this->form->addElement('static', null, "<br/>");


        //q7-13
        $this->form->addElement("select", "q7_13", "7-13. What were the results of the lead test?",  array(NULL=>"", "01" => "01 High", "02"=>"02 Normal", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q7_13", array("q7_12{@}=={@}01_yes"), "Required if house tested for lead");
        $this->form->addElement('static', null, "<br/>");


        //q7-14
        $this->form->addElement("select", "q7_14", "7-14. Have you lived in any other homes since 3 months prior to your [DOBS]?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [Yes], repeat all above questions with insert");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


        //q7-15
        $this->form->addElement("select", "q7_15", "7-15. Did you have any problems with dampness in your house or basement when you were pregnant with [SIBLING}?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 7-17");


        //q7-16
        $this->form->addElement("select", "q7_16", "7-16. Which trimester(s) of pregnancy with [SIBLING] did you have these dampness problems? Select all that apply:",  array(NULL=>"", "01" => "01", "02" => "02", "03" => "03", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"), "multiple");
        $this->form->addElement('static', null, "<br/>");


        //q7-17
        $this->form->addElement("select", "q7_17", "7-17 Did anyone use any chemicals to kill the mold, mildew or remove the odor when you were pregnant with [SIBLING}?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 7-19");
        $this->form->addElement('static', null, "<br/>");


        $this->form->addElement('select', 'q7_18', "7-18 Which trimester(s) of pregnancy with [SIBLING] were these chemicals used? Select all that apply:", array(NULL=>"", "01"=>"01", "02"=>"02", "03"=> "03","88 Refused", "99" => "99 Do not know", "Not_Answered" => "Not Answered"), "multiple");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


    } //end function _page20() ======================================================



    function rulesPage20($fields)
    {
        $errors = array();		

        function multSelect($fields, $question1, $question2)
        {
            return (($fields[$question1] == array(0=>null) && $fields[$question2] == "01_yes") || (empty($fields[$question1])) && $fields[$question2] == "01_yes");
        }


        //q7-16	
        if (multSelect($fields, "q7_16", "q7_15"))
            $errors["q7_16"] = "You must specify trimester(s)";		


        //q6-18
        if (multSelect($fields, "q7_18", "q7_17"))
            $errors["q7_18"] = "You must specify trimester(s)";		


        return $errors;
    }



    function _page21(){   // ========================================================


        $this->form->addElement('header', null, "Section 7. HOME ENVIRONMENTAL EXPOSURES <br /><br /></br /> (PART 2 OF 3)");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<b/>Household Product Use");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<b><i>Now I am going to ask you about your household product use.</i></b>");
        $this->form->addElement('static', null, "<br/>");


        //function with more complex rules
        $this->form->addFormRule(array(&$this, 'rulesPage21'));

        //q7-19
        $this->form->addElement("select", "q7_19", "7-19. How often was your home dusted when you were pregnant with [SIBLING]?",  array(NULL=>"", "01" => "01 Never", "02" => "02 At least once per day", "03" => "03  3 to 6 times per week", "04" => "04 1 or 2 times per week", "05" => "05 1 to 3 times per month", "06" => "06 6 to 11 times per year", "07" => "07 1 to 5 times per year", "08" => "08 Less than once per year", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [01 Never], go to question 7-21");
        $this->form->addElement('static', null, "<br/>");


        //q7-20
        $this->form->addElement("select", "q7_20", "7-20. Did you do the dusting when you were pregnant with [SIBLING]?",  array(NULL=>"", "01" => "01 Yes, usually", "02" => "02 No, usually", "03" => "03  About half the time", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->XINRegisterRule("q7_20", array("q7_19{@}=={@}02|03|04|05|06|07|08"), "Required if home was dusted");
        $this->form->addElement('static', null, "<br/>");


        //q7-21
        $this->form->addElement("select", "q7_21", "7-21. During your pregnancy with [SIBLING], approximately how many hours a day did you keep the windows or doors open in your home? Was it",  array(NULL=>"", "01" => "01 Less than 1 hour per day", "02" => "02 1-3 hours per day", "03" => "03  4-12 hours per day", "04" => "04 More than 12 hours per day, or", "05" => "05 Not at all", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, "<br/>");


        //q7-22 
        $this->form->addElement("select", "q7_22", "7-22. During cleaning of your home with chemical products like aerosols, were ventilation sources such as fans or windows routinely used when you were pregnant with [SIBLING]?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");

        $this->form->addElement('header', null, "<b/>Indoor Products");
        $this->form->addElement('static', null, "<br/>");


        //q7-23
        $this->form->addElement("select", "q7_23", "7-23. Between [-3] and [DOBS], did you use paints, stains or lacquers in your home?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 7-27");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


        //q7-24
        $this->form->addElement('static', null, "7-24. What was the name of the product? How was it used? Who used it?");
        $this->form->addElement('static', null, "<br/>");


        for ($i = 1; $i<4; $i++)
        {
            $this->addTextAreaElementRD("q7_24_product{$i}", $this->indent . "Product #{$i}:"); 
            $this->addTextAreaElementRD("q7_24_product{$i}_how", $this->indent . $this->indent . 'How it was used?');
            $this->form->addElement("select", "q7_24_product{$i}_who", $this->indent . $this->indent . "Who used the product?", array(NULL=>"", "Mother", "Father", "Other", "Not_Answered" => "Not Answered"));
            $this->form->addElement('static', null, "<br/>");

            if ($i>1)
            {
                $this->XINRegisterRule("q7_24_product{$i}", array("q7_24_product{$i}{@}=={@}NEVER_REQUIRED"), "q7_24_product{$i}_group");
                $this->XINRegisterRule("q7_24_product{$i}_how", array("q7_24_product{$i}_how{@}=={@}NEVER_REQUIRED"), "q7_24_product{$i}_how_group");
                $this->XINRegisterRule("q7_24_product{$i}_who", array("q7_24_product{$i}_who{@}=={@}NEVER_REQUIRED"));
            }
        }

        $this->XINRegisterRule("q7_24_product1", array("q7_23{@}=={@}01_yes"), "You must specify product", "q7_24_product1_group");
        $this->XINRegisterRule("q7_24_product1_how", array("q7_23{@}=={@}01_yes"), "You must specify use", "q7_24_product1_how_group");
        $this->XINRegisterRule("q7_24_product1_who", array("q7_23{@}=={@}01_yes"), "You must specify user");
        $this->form->addElement('static', null, "<br/>");


        //q7-25
        $this->form->addElement('static', null, "7-25. During which months was the product used?");
        $this->form->addElement ("select", "q7_25_p1", $this->indent . "Product #1: (Select all that apply):", $this->negThreeToNine, "multiple size = '5'" );
        $this->form->addElement ( "select", "q7_25_p2", $this->indent . "Product #2: (Select all that apply):", $this->negThreeToNine, "multiple size = '5'" );
        $this->form->addElement ( "select", "q7_25_p3", $this->indent . "Product #3: (Select all that apply):", $this->negThreeToNine, "multiple size = '5'" );
        $this->form->addElement('static', null, "<br/>");



        //q7-26
        $this->form->addElement('static', null, "7-26 How often was it used between [-3] and [DOBS]?");

        foreach($this->oneToThree as $field=>$label){

            $this->form->addElement('static', null, "<br/>");
            $this->form->addElement('select',"q7_26_{$field}", $this->indent . "Product {$label}:",  array(NULL=>"", "01" => "01 1 day", "02" => "02 2 - 3 days", "03" => "03  4 - 6 days", "04" => "04 1 week", "05" => "05 1 -2 weeks", "06" => "06 2 - 3 weeks", "07" => "07 3 - 4 weeks", "08" => "08 1 month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
            if ($field>1)
                $this->XINRegisterRule("q7_26_{$field}", array("q7_26{$field}{@}=={@}NEVER_REQUIRED"));
        }

        $this->XINRegisterRule("q7_26_1", array("q7_23{@}=={@}01_yes"), "Required if used any of the above products");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


        //q7-27
        $this->form->addElement("select", "q7_27", "7-27. Between [-3] and [DOBS], did you use adhesives or petroleum products?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 7-31");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


        //q7-28
        $this->form->addElement('static', null, "7-28. What was the name of the product? How was it used? Who used it?");
        $this->form->addElement('static', null, "<br/>");

        for ($i = 1; $i<4; $i++)
        {		

            $this->addTextAreaElementRD("q7_28_product{$i}", $this->indent . "Product #{$i}:");
            $this->addTextAreaElementRD("q7_28_product{$i}_how", $this->indent . $this->indent . 'How it was used?');
            $this->form->addElement("select", "q7_28_product{$i}_who", $this->indent . $this->indent . "Who used the product?", array(NULL=>"", "Mother", "Father", "Other", "Not_Answered" => "Not Answered"));

            if ($i>1)
            {
                $this->XINRegisterRule("q7_28_product{$i}", array("q7_28_product{$i}{@}=={@}NEVER_REQUIRED"), "q7_28_product{$i}_group");
                $this->XINRegisterRule("q7_28_product{$i}_how", array("q7_28_product{$i}_how{@}=={@}NEVER_REQUIRED"), "q7_28_product{$i}_how_group");
                $this->XINRegisterRule("q7_28_product{$i}_who", array("q7_28_product{$i}_who{@}=={@}NEVER_REQUIRED"));
            }
        }

        $this->XINRegisterRule("q7_28_product1", array("q7_27{@}=={@}01_yes"), "You must specify product", "q7_28_product1_group");
        $this->XINRegisterRule("q7_28_product1_how", array("q7_27{@}=={@}01_yes"), "You must specify use", "q7_28_product1_how_group");
        $this->XINRegisterRule("q7_28_product1_who", array("q7_27{@}=={@}01_yes"), "You must specify user");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


        //q7-29
        $this->form->addElement('static', null, "7-29. During which months was the product used?");
        $this->form->addElement ( "select", "q7_29_p1", $this->indent . "Product #1: (Select all that apply):", $this->negThreeToNine, "multiple size = '5'" );
        $this->form->addElement ( "select", "q7_29_p2", $this->indent . "Product #2: (Select all that apply):", $this->negThreeToNine, "multiple size = '5'" );
        $this->form->addElement ( "select", "q7_29_p3", $this->indent . "Product #3: (Select all that apply):", $this->negThreeToNine, "multiple size = '5'" );

        $this->XINRegisterRule("q7_29_p1", array("q7_27{@}=={@}01_yes"), "Required if used any of the above products");
        $this->XINRegisterRule("q7_29_p2", array("q7_29_p2{@}=={@}NEVER_REQUIRED"));
        $this->XINRegisterRule("q7_29_p3", array("q7_29_p3{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement('static', null, "<br/>");


        //q7-30
        $this->form->addElement('static', null, "7-30. How often was it used between [-3] and [DOBS]?");

        foreach ($this->oneToThree as $field=>$label){

            $this->form->addElement('static', null, "<br/>");
            $this->form->addElement('select', "q7_30_{$field}", $this->indent . "Product {$label}:", array(NULL=>"", "01" => "01 1 day", "02" => "02 2 - 3 days", "03" => "03  4 - 6 days", "04" => "04 1 week", "05" => "05 1 -2 weeks", "06" => "06 2 - 3 weeks", "07" => "07 3 - 4 weeks", "08" => "08 1 month", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));

            if ($field>1)
                $this->XINRegisterRule("q7_30_{$field}", array("q7_30_{$field}{@}=={@}NEVER_REQUIRED"));
        }

        $this->XINRegisterRule("q7_30_1", array("q7_27{@}=={@}01_yes"), "Required if used any of the above products");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


        //q7-31
        $this->form->addElement("select", "q7_31", "7-31. Between [-3] and [DOBS], were you exposed to any broken thermometers or thermostats with mercury in them?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 7-33");
        $this->form->addElement('static', null, "<br/>");


        //q7-32
        $this->form->addElement ( "select", "q7_32", "7-32. During which months did this happen? (Select all that apply):", $this->negThreeToNine, "multiple size = '5'" );
        $this->XINRegisterRule("q7_32", array("q7_31{@}=={@}01_yes"), "Required if exposed to mercury");
        $this->form->addElement('static', null, "<br/>");


        //q7-33
        $this->form->addElement("select", "q7_33", "7-33. Between [-3] and [DOBS], were you exposed to any broken fluorescent light bulbs?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 7-35");

        //q7-34
        $this->form->addElement ( "select", "q7_34", "7-34. During which months did this happen? (Select all that apply):", $this->negThreeToNine, "multiple size = '5'");
        $this->XINRegisterRule("q7_34", array("q7_33{@}=={@}01_yes"), "Required if exposed to broken fluorescent bulbs");
        $this->form->addElement('static', null, "<br/>");


        //q7-35
        $this->form->addElement("select", "q7_35", "7-35. Between [-3] and [DOBS], were you exposed to any broken electronic switches or relays, or broken gauges?",  array(NULL=>"", "01_yes" => "01 Yes", "02" => "02 No ", "88_refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"));
        $this->form->addElement('static', null, $this->indent . "If you selected [No], [Refused] or [Don't Know] skip to question 7-37");


        //q7-36
        $this->form->addElement ( "select", "q7_36", "7-36. During which months did this happen? (Select all that apply):", $this->negThreeToNine, "multiple size = '5'");
        $this->XINRegisterRule("q7_36", array("q7_35{@}=={@}01_yes"), "Required if exposed to broken switches, relays, gauges");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");



    } //end function _page21() =====================================================


    function rulesPage21($fields)
    {
        $errors = array();

        function multSelect($fields, $question1, $question2)
        {
            return (($fields[$question1] == array(0=>null) && $fields[$question2] == "01_yes") || (empty($fields[$question1])) && $fields[$question2] == "01_yes");
        }


        //q7-25
        if (multSelect($fields, "q7_25_p1", "q7_23"))
            $errors["q7_25_p1"] = "You must specify month(s)";


        //q7-29
        if (multSelect($fields, "q7_29_p1", "q7_27"))
            $errors["q7_29_p1"] = "You must specify month(s)";


        //q7-32, 7-34, 7-36
        for ($i=32; $i<37; $i+=2)
        {
            $j = $i-1;
            if (multSelect($fields, "q7_$i", "q7_$j"))
                $errors["q7_$i"] = "You must specify month(s)";
        }

        return $errors;
    }



    function _page22(){   // ========================================================


        $this->form->addElement('header', null, "Section 7. HOME ENVIRONMENTAL EXPOSURES <br /><br /></br /> (PART 3 OF 3)");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<b/>Personal care products");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


        //function with more complex rules
        $this->form->addFormRule(array(&$this, 'rulesPage22'));


        //q7-37
        $this->form->addElement('static', null, "7-37. I am going to read you a list of personal care products. Please tell me if you used any of the following during your pregnancy with [SIBLING].");

        $products = array("1"=>"1. Hair Colour", "2"=>"2. Nail Polish", "3"=>"3. Sun Screen", "4"=>"4. Perfume", "5"=>"5. Insect Repellant");
        //reset($oneToFive);
        $this->form->addElement('static', null, "<br/>");

        foreach ($products as $field=>$label){

            $this->form->addElement("select", "q7_37_{$field}", $this->indent . "{$label}", $this->yesNo); 
        }

        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, $this->indent . $this->indent . "If you selected [Refused] or [Don't Know] skip to question 7-39");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


        //q7-38
        $this->form->addElement('static', null, "7-38. While you were pregnant with [SIBLING], please tell which trimester or trimesters you use the products?");

        $this->form->addElement('static', null, "<br/>");
        $oneToFive = array("1"=>"#1", "2"=>"#2", "3"=>"#3", "4"=>"#4", "5"=>"#5");
        foreach($oneToFive as $field=>$label){

            $this->form->addElement("select", "q7_38_{$field}", $this->indent . $this->indent . "Product {$label}:",  array(NULL=>"", "01" => "01 First Trimester", "02" => "02 Second Trimester", "03" => "03  Third Trimester", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"), "multiple");

        }
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


        //q7-39
        $this->form->addElement('static', null, "7-39 I am going to read you a list of pesticides or pet products. Please tell me if you used any of the following during your pregnancy with [SIBLING].");

        $oneToSix = array("1"=>"1. Ant Traps", "2"=>"2. Roach Traps", "3"=>"3. Insect Spray", "4"=>"4. Fogger", "5"=>"5. Flea Treatment for Pets",  "6"=>"6. Change the Cat Litter");
        $this->form->addElement('static', null, "<br/>");

        while(list($field, $label) = each($oneToSix)){

            $this->form->addElement("select", "q7_39_{$field}", $this->indent . "{$label}:", $this->yesNo);

        }

        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, $this->indent . $this->indent . "If you selected [Refused] or [Don't Know] skip to SECTION 8");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


        //q7-40
        $this->form->addElement('static', null, "7-40. While you were pregnant with [SIBLING], please tell which trimester or trimesters you used the products?");

        $oneToSix = array("1"=>"#1", "2"=>"#2", "3"=>"#3", "4"=>"#4", "5"=>"#5",  "6"=>"#6");
        reset($oneToSix);

        while(list($field, $label) = each($oneToSix)){

            $this->form->addElement("select", "q7_40_{$field}", $this->indent . "Product {$label}:",  array(NULL=>"", "01" => "01", "02" => "02", "03" => "03", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered"), "multiple");

            if ($field>1)
                $this->XINRegisterRule("q7_40_{$field}", array("q7_40_{$field}{@}=={@}NEVER_REQUIRED"));

        }

        $this->XINRegisterRule("q7_40_1", array("q7_39{@}=={@}00_specify"), "You must specify trimester(s)");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, $this->indent . $this->indent . "If you selected [Refused] or [Don't Know] skip to question SECTION 8");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('header', null, "END Section 7.");
        $this->form->addElement('static', null, "<br/>");
        $this->form->addElement('static', null, "<br/>");


    } //end function _page22() =====================================================


    function rulesPage22($fields)
    {

        $errors = array();

        function multSelect($fields, $question1, $question2)
        {
            return (($fields[$question1] == array(0=>null) && $fields[$question2] == "01_yes") || (empty($fields[$question1])) && $fields[$question2] == "01_yes");
        }


        //q7-38
        for ($i=1; $i<6; $i++)	
        {
            if (multSelect($fields, "q7_38_$i", "q7_37_$i"))
                $errors["q7_38_$i"] = "You must specify trimester(s)";
        }


        //q7-40
        for ($i=1; $i<7; $i++)
        {
            if (multSelect($fields, "q7_40_$i", "q7_39_$i"))
                $errors["q7_40_$i"] = "You must specify trimester(s)";
        }

        return $errors;
    }


} //end EARLI Maternal Interview Part 2 =================================================

?>
