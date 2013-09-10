<?php
class NDB_BVL_Instrument_LENA_DailyActivityLog extends NDB_BVL_Instrument
{
    var  $rate_day = array(""=>null,"typical"=>"A. typical/ordinary example of our parent child talk time",
                       "more_talkative"=>"B. more talkative than our usual parent child talk talk",
                       "less_talkative"=>"C. less talkative than our usual parent child talk time");
/*
    INSERT INTO test_names (Test_name,Full_name, Sub_group) VALUES ('LENA_DailyActivityLog','LENA Daily Activity Log',1);

    INSERT INTO instrument_subtests (Test_name,Subtest_name,Description,Order_number) values ('LENA_DailyActivityLog','LENA_DailyActivityLog_page1','DailyActivityLog 1','1');
    INSERT INTO instrument_subtests (Test_name,Subtest_name,Description,Order_number) values ('LENA_DailyActivityLog','LENA_DailyActivityLog_page2','DailyActivityLog 2','2');
    INSERT INTO instrument_subtests (Test_name,Subtest_name,Description,Order_number) values ('LENA_DailyActivityLog','LENA_DailyActivityLog_page3','DailyActivityLog 3','3');
    INSERT INTO instrument_subtests (Test_name,Subtest_name,Description,Order_number) values ('LENA_DailyActivityLog','LENA_DailyActivityLog_page4','DailyActivityLog 4','4');
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
        $this->testName = "LENA_DailyActivityLog";           // test_names.Test_name
        $this->table = 'LENA_DailyActivityLog';             // name of table containing

        // data keyed by commentID
        $this->commentID = $commentID;

        //The array of dates/timestamps to convert to database dates/timestamps
        //Any HTML_Quickform date elements must be listed here
        $this->dateTimeFields=array("Date_taken","1_date_completed","2_date_completed",
                                    "3_date_completed","4_date_completed","1_infection_date",
                                    "2_infection_date","3_infection_date","4_infection_date");

        $this->_requiredElements = array('Date_taken', 'Examiner'); 

        $config =& NDB_Config::singleton();
        $this->dateOptions = array(
        'language' => 'en',
        'format'   => 'YMd',
        'minYear'  => $config->getSetting('startYear'),
        'maxYear'  => $config->getSetting('endYear'),
        'addEmptyOption' => true,
        'emptyOptionValue' => null
        );
        
        $db =& Database::singleton();
        if(PEAR::isError($db)) {
            return PEAR::raiseError ("Could not connect to database: ".$db->getMessage());
        }
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
        if(preg_match("/LENA_DailyActivityLog(_page[1-9]+)/",$this->page,$matches)){
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
        $this->addHeader("LENA Daily Activity Log");
        $this->addBasicText("child_name","Child's Name:");
    }

    function _page1() {
        
        $this->addBasicDate("1_date_completed","Date:");
        $group[] = &$this->form->createElement("static", null, null, "Parent-Child Daily Log<BR>Hour");
        $group[] = &$this->form->createElement("static", null, null, "Environment");
        $group[] = &$this->form->createElement("static", null, null, "DLP Status");
        $group[] = &$this->form->createElement("static", null, null, "Individuals Present");
        $group[] = &$this->form->createElement("static", null, null, "Other Notes");
        $group[] = &$this->form->createElement("static", null, null, null);
        $this->form->addGroup($group, "1_headers", null, $this->_GUIDelimiter, false);
        unset($group);

        $this->_addTableRow(1);

        $this->addSelect("1_child_sick","Is your child sick or not feeling well today?",array(""=>null,"yes"=>"Yes","no"=>"No"));
        $this->addTextAreaGroup("1_sickness_kind","If yes, what kind of sickness?");
        $this->XINRegisterRule ( "1_sickness_kind", array ("1_child_sick{@}=={@}yes"), "Please enter sickness kind" );

        $this->addBasicDate("1_infection_date","His/Her last ear infection was:");
        
        $this->addSelect("1_rate_recordingday","I would rate this day when we used the recording device as:",$this->rate_day);
        $this->addTextAreaGroup("1_comments","Comments:");
        $this->addSelect("1_more_recordings","Are there any more daily activity logs", array("yes"=>"Yes","no"=>"No"));

    }
    
    function _page2() {
        
        $this->addBasicDate("2_date_completed","Date:");
        $group[] = &$this->form->createElement("static", null, null, "Parent-Child Daily Log<BR>Hour");
        $group[] = &$this->form->createElement("static", null, null, "Environment");
        $group[] = &$this->form->createElement("static", null, null, "DLP Status");
        $group[] = &$this->form->createElement("static", null, null, "Individuals Present");
        $group[] = &$this->form->createElement("static", null, null, "Other Notes");
        $group[] = &$this->form->createElement("static", null, null, null);
        $this->_addTableRow(2);

        $this->addSelect("2_child_sick","Is your child sick or not feeling well today?",array(""=>null,"yes"=>"Yes","no"=>"No"));
        $this->addTextAreaGroup("2_sickness_kind","If yes, what kind of sickness?");
        $this->XINRegisterRule ( "2_sickness_kind", array ("2_child_sick{@}=={@}yes"), "Please enter sickness kind" );

        $this->addBasicDate("2_infection_date","His/Her last ear infection was:");
 
        $this->addSelect("2_rate_recordingday","I would rate this day when we used the recording device as:",$this->rate_day);
        $this->addTextAreaGroup("2_comments","Comments:");
        $this->addSelect("2_more_recordings","Are there any more daily activity logs", array("yes"=>"Yes","no"=>"No"));

    }

    function _page3() {
        
        $this->addBasicDate("3_date_completed","Date:");
        $group[] = &$this->form->createElement("static", null, null, "Parent-Child Daily Log<BR>Hour");
        $group[] = &$this->form->createElement("static", null, null, "Environment");
        $group[] = &$this->form->createElement("static", null, null, "DLP Status");
        $group[] = &$this->form->createElement("static", null, null, "Individuals Present");
        $group[] = &$this->form->createElement("static", null, null, "Other Notes");
        $group[] = &$this->form->createElement("static", null, null, null);
        $this->_addTableRow(3);

        $this->addSelect("3_child_sick","Is your child sick or not feeling well today?",array(""=>null,"yes"=>"Yes","no"=>"No"));
        $this->addTextAreaGroup("3_sickness_kind","If yes, what kind of sickness?");
        $this->XINRegisterRule ( "3_sickness_kind", array ("3_child_sick{@}=={@}yes"), "Please enter sickness kind" );

        $this->addBasicDate("3_infection_date","His/Her last ear infection was:");
 
        $this->addSelect("3_rate_recordingday","I would rate this day when we used the recording device as:",$this->rate_day);
        $this->addTextAreaGroup("3_comments","Comments:");
        $this->addSelect("3_more_recordings","Are there any more daily activity logs", array("yes"=>"Yes","no"=>"No"));

    }
    
    function _page4() {
        
        $this->addBasicDate("4_date_completed","Date:");
        $group[] = &$this->form->createElement("static", null, null, "Parent-Child Daily Log<BR>Hour");
        $group[] = &$this->form->createElement("static", null, null, "Environment");
        $group[] = &$this->form->createElement("static", null, null, "DLP Status");
        $group[] = &$this->form->createElement("static", null, null, "Individuals Present");
        $group[] = &$this->form->createElement("static", null, null, "Other Notes");
        $group[] = &$this->form->createElement("static", null, null, null);
        $this->_addTableRow(4);

        $this->addSelect("4_child_sick","Is your child sick or not feeling well today?",array(""=>null,"yes"=>"Yes","no"=>"No"));
        $this->addTextAreaGroup("4_sickness_kind","If yes, what kind of sickness?");
        $this->XINRegisterRule ( "4_sickness_kind", array ("4_child_sick{@}=={@}yes"), "Please enter sickness kind" );

        $this->addBasicDate("4_infection_date","His/Her last ear infection was:");
 
        $this->addSelect("4_rate_recordingday","I would rate this day when we used the recording device as:",$this->rate_day);
        $this->addTextAreaGroup("4_comments","Comments:");

    }


    function _addTableRow ($page) { 
        $time_interval = array("5_7am"=>"5:00-7:00am","7_9am"=>"7:00am-9:00am","9_11am"=>"9:00-11:00am",
                         "11_1pm"=>"11:00am-1:00pm","1_3pm"=>"1:00-3:00pm","3_5pm"=>"3:00-5:00pm",
                         "5_7pm"=>"5:00-7:00pm","7_9pm"=>"7:00-9:00pm","9_11pm"=>"9:00-11:00pm","11_12pm"=>"11:00-12:00pm");
        $dlp_status = array (""=>null,"wearing_dlp"=>"+ Wearing the DLP","notwearing_dlp"=>"- Wearing the DLP");
        $individuals_present = array (""=>null,"family"=>"1 - Family Members","other"=>"2 - Other (please not)");
        $envr = array(""=>null,"home"=>"Home","away"=>"Away from home");
        foreach($time_interval as $key=>$val){
        $groupname = $page."_".$key."_group";
        $group[] =& $this->form->addElement("static",null,$this->indent.$val);
        $group[] =& $this->form->addElement("select",$page."_".$key."_environment",null,$envr);
        $group[] =& $this->form->addElement("select",$page."_".$key."_dlpstatus",null,$dlp_status);
        $group[] =& $this->form->addElement("select",$page."_".$key."_individuals",null,$individuals_present);
        $group[] =& $this->form->addElement("textarea",$page."_".$key."_notes",null);
        $group[] =& $this->form->addElement("select",$page."_".$key."_option", null, array('' => '','not_answered'=>'Not Answered'));
        $this->form->addGroup($group, $groupname, null, $this->_GUIDelimiter, false);
        unset($group);

       }
   }

}
?>
