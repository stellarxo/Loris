<?php
class NDB_BVL_Instrument_LENAV09_DataTrackingForm extends NDB_BVL_Instrument
{
    var $ValidityEnabled = false;
    var $ValidityRequired = false;
    var $participate = array(""=>null,'yes'=>'YES. If yes, skip to Section C.','no'=>'NO. If no, complete Section B only.');
    var $session = array(""=>null,'1'=>'1','2'=>'2','3'=>'3','4'=>'4');
    var $duration = array(""=>null,'full_day'=>'Full day(16 hrs)','less_16hrs'=>'<16hrs','notused_del'=>'Recording not used or deleted');
    var $reasons_decline = array(""=>null,'issues_related_to_privacy'=>'Issues related to privacy',
                            'time_consuming_or_burdensome'=>'Time consuming or burdensome',
                            'spouse_not_participate'=>'Spouse or partner of consenting parent or caregiver does not want to participate',
                            'lena_not_seen_as_beneficial'=>'LENA not seen as beneficial',
                            'just_not_interested'=>'Just not interested','other'=>'Other'); 
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
        $this->testName = "LENAV09_DataTrackingForm";           // test_names.Test_name
        $this->table = 'LENAV09_DataTrackingForm';             // name of table containing

        // data keyed by commentID
        $this->commentID = $commentID;

        //The array of dates/timestamps to convert to database dates/timestamps
        //Any HTML_Quickform date elements must be listed here
        $this->dateTimeFields=array("Date_taken", "wait_time", "total_duration");

        $this->_requiredElements = array('Date_taken', 'Examiner'); //, 'CaregiverReport');

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
    
         $this->addHeader("LENAV09 Data Tracking Form");    
         $this->addLabel("<BR><strong>Section A. Data Submission</strong>");
         $this->addBasicDate("v09_datecompleted","Date Form Completed:");
         $this->addSelect("family_participate", "<BR>Did family agree to participate?",$this->participate); 
        $this->addLabel("<BR><strong>Section B. Reason(s) for Decline</strong>");
        $this->addSelect("v09_reasonsdecline","Check All That Apply<BR>Ctrl+click or Cmd+click to select multiple options", $this->reasons_decline, "multiple size='5'");
        $this->XINRegisterRule("v09_reasonsdecline",array("family_participate{@}=={@}no"));
         
        $this->addLabel("<BR><strong>Section C. DLP Tracking Information</strong>");
        $this->addSelect("number_session","Number of Recording sessions:", $this->session);
        $this->XINRegisterRule("number_session",array("family_participate{@}=={@}yes"));
        
        $this->addLabel("<BR> Duration of recording session:");
        $this->addSelect("duration_session1","Recording Session 1", $this->duration);
        $this->XINRegisterRule("duration_session1",array("number_session{@}=={@}1|2|3|4"));
        $this->addTextAreaGroup("comments_session1","Comments(e.g., did DLP malfunction?)");
        $this->XINRegisterRule("comments_session1",array("number_session{@}=={@}1|2|3|4"));

        $this->addSelect("duration_session2","Recording Session 2", $this->duration);
        $this->XINRegisterRule("duration_session2",array("number_session{@}=={@}2|3|4"));
        $this->addTextAreaGroup("comments_session2","Comments(e.g., did DLP malfunction?)");
        $this->XINRegisterRule("comments_session2",array("number_session{@}=={@}2|3|4"));
        
        $this->addSelect("duration_session3","Recording Session 3", $this->duration);
        $this->XINRegisterRule("duration_session3",array("number_session{@}=={@}3|4"));
        $this->addTextAreaGroup("comments_session3","Comments(e.g., did DLP malfunction?)");
        $this->XINRegisterRule("comments_session3",array("number_session{@}=={@}3|4"));
        
        $this->addSelect("duration_session4","Recording Session 4", $this->duration);
        $this->XINRegisterRule("duration_session4",array("number_session{@}=={@}4"));
        $this->addTextAreaGroup("comments_session4","Comments(e.g., did DLP malfunction?)");
        $this->XINRegisterRule("comments_session4",array("number_session{@}=={@}4"));
        
        $this->form->addElement('file', 'directions_file', 'Upload the export file');
    }

}
       
?>
