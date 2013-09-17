<?php
class NDB_BVL_Instrument_LENA_DailyActivityLog extends NDB_BVL_Instrument
{
    var  $rate_day = array(""=>null,"typical"=>"A. typical/ordinary talk time",
                       "more_talkative"=>"B. more talkative than usual",
                       "less_talkative"=>"C. less talkative than usual");
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
        $this->dateTimeFields=array("Date_taken", "day1_date_completed","day2_date_complete","day3_date_completed",
                                    "day4_date_completed","day1_infection_date","day2_infection_date",
                                    "day3_infection_date","day4_infection_date");

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
        if(preg_match("/LENA_DailyActivityLog(_page[0-9]+)/",$this->page,$matches)){
            $this->_page($matches[1]);
            //call_user_method($matches[1], $this);
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
        // automatically adds examiner & date of administration
        $this->_addMetadataFields();

    }

    function _page($page) {
        
        $temp = substr($page,-1);
        $field = "day".$temp;
        $this->form->addElement("static", null, "<br><br>");
        $this->addHeader("Daily Activity Log $temp");
        $this->form->addElement("static", null, "<br><br>");
        
        $group[] = &$this->form->createElement("date",$field."_date_completed",null,$this->dateOptions );
        $group[] = &$this->form->createElement("select",$field."_date_completed_status",null,array(""=>null,'not_answered'=>'Not Answered'));
        $this->form->addGroup($group,$field."_date_completed_group","<td colspan=1>Date</td>",$this->_GUIDelimiter, false);

        unset($group);
        $this->XINRegisterRule($field."_date_completed", array($field . "_date_completed_status{@}=={@}"), "A Date, or Not Answered is required.", $name . "_date_completed_group");

        //$this->addDateElement("1_date_completed","Date:");
        $this->form->addElement("static", null, "<br><br>");
        $group[] = &$this->form->createElement("static", null, null, "Parent-Child Daily Log<BR>Hour");
        $group[] = &$this->form->createElement("static", null, null, "Environment");
        $group[] = &$this->form->createElement("static", null, null, "DLP Status");
        $group[] = &$this->form->createElement("static", null, null, "Individuals Present");
        $group[] = &$this->form->createElement("static", null, null, "Other Notes");
        $this->form->addGroup($group, $field."_headers", null, $this->_GUIDelimiter, false);
        unset($group);

        $this->_addTableRow($field);
        $this->form->addElement("static", null, "<br><br>");

        $group[] = &$this->form->createElement("select",$field."_child_sick",null,array(""=>null,"yes"=>"Yes","no"=>"No"));
        $this->form->addGroup($group,$field."_child_sick_group","<td colspan=2>Is your child sick or not feeling well today?</td>",$this->_GUIDelimiter,false);
        unset($group);
        
        $group[] = &$this->form->createElement("textarea",$field."_sickness_kind",null);
        $group[] = &$this->form->createElement("select",$field."_sickness_kind_status",null,array(""=>null,'not_answered'=>'Not Answered'));
        $this->form->addGroup($group,$field."_sickness_kind_group","<td colspan=2>If yes, what kind of sickness?</td>",$this->_GUIDelimiter,false);
        $newval = $field."_child_sick";
        $kind_status = $field."_sickness_kind_status";
        $this->XINRegisterRule ( $field."_sickness_kind", array("$newval{@}=={@}yes","$kind_status{@}!={@}not_answered"), "Please enter sickness kind, or select Not Answered",$field."_sickness_kind_group");
        unset($group);

        $this->form->addElement("static", null, "<br><br>");
        $group[] = &$this->form->createElement("date",$field."_infection_date",null,$this->dateOptions );
        $group[] = &$this->form->createElement("select",$field."_infection_date_status",null,array(""=>null,'not_answered'=>'Not Answered'));
        $this->form->addGroup($group,$field."_infection_date_group","<td colspan=2>His/Her last ear infection was:</td>",$this->_GUIDelimiter, false);
        unset($group);
        $this->XINRegisterRule($field."_infection_date", array($field . "_infection_date_status{@}=={@}"), "A Date, or Not Answered is required.", $field . "_infection_date_group");

        $this->form->addElement("static", null, "<br><br>");
        $group[] = &$this->form->createElement("select",$field."_rate_recordingday",null,$this->rate_day);
        $this->form->addGroup($group,$field."_rate_recordingday_group","<td colspan=2>I would rate this day when we used the recording device as:</td>",$this->_GUIDelimiter,false);
        unset($group);

        $this->form->addElement("static", null, "<br><br>");
        $group[] = &$this->form->createElement("textarea",$field."_comments","required");
        $group[] = &$this->form->createElement("select",$field."_comments_status",null,array(""=>null,'not_answered'=>'Not Answered'));
        $this->form->addGroup($group,$field."_comments_group","<td colspan=2>Comments:</td>", $this->_GUIDelimiter, false);
        $comments_status_fieldname = $field."_comments_status"; 
        $this->XINRegisterRule ( $field."_comments", array("$comments_status_fieldname{@}!={@}not_answered"), "Please enter Comments, or select Not Answered",$field."_comments_group");

        unset($group);
/*

        $this->form->addElement("static", null, "<br><br>");
        $group[]= &$this->form->createElement("select",$field."_more_recordings", null, array(""=>null,"yes"=>"Yes","no"=>"No"));
        $this->form->addGroup($group,$field."_more_recordings_group","<td colspan=2>Are there any more daily activity logs? </td>",$this->_GUIDelimiter, false );
*/

    }
   
   function _addTableRow ($page) {
        $time_interval = array("5_7am"=>"5:00-7:00am","7_9am"=>"7:00-9:00am","9_11am"=>"9:00-11:00am",
                         "11_1pm"=>"11:00am-1:00pm","1_3pm"=>"1:00-3:00pm","3_5pm"=>"3:00-5:00pm",
                         "5_7pm"=>"5:00-7:00pm","7_9pm"=>"7:00-9:00pm","9_11pm"=>"9:00-11:00pm","11_12pm"=>"11:00-12:00pm");
        $dlp_status = array (""=>null,"wearing_dlp"=>"+ Wearing the DLP","notwearing_dlp"=>"- Wearing the DLP");
        $individuals_present = array (""=>null,"family"=>"1 - Family Members","other"=>"2 - Other (please not)");
        $envr = array(""=>null,"home"=>"Home","away"=>"Away from home");
        foreach($time_interval as $key=>$val){
        $groupname = $page."_".$key."_group";
        $field = $page."_".$key;
        $group[] =& $this->form->createElement("static",null,null,$val);
        $group[] =& $this->form->createElement("select", $field."_environment",null,$envr);
        $group[] =& $this->form->createElement("select",$field."_dlpstatus",null,$dlp_status);
        $group[] =& $this->form->createElement("select",$field."_individuals",null,$individuals_present);
        $group[] =& $this->form->createElement("textarea",$field."_notes",null);
        $list = array ("_environment","_dlpstatus","_individuals","_notes");
        foreach($list as $term) {
           $final_field = $field.$term;
           $this->XINRegisterRule($final_field, array("$final_field{@}=={@}NEVER_REQUIRED"),null,$groupname);

        }
        $this->form->addGroup($group, $groupname, null, $this->_GUIDelimiter, false);
unset($group);
       }
   }

}
?>
