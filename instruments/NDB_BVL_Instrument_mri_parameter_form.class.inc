<?php
class NDB_BVL_Instrument_mri_parameter_form extends NDB_BVL_Instrument
{
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
        $this->testName = "mri_parameter_form";           // test_names.Test_name
        $this->table = 'mri_parameter_form';             // name of table containing

        // data keyed by commentID
        $this->commentID = $commentID;

        //The array of dates/timestamps to convert to database dates/timestamps
        //Any HTML_Quickform date elements must be listed here
        $this->dateTimeFields=array("Date_taken");

        //$this->_requiredElements = array('Date_taken', 'Examiner', 'CaregiverReport');

        $config =& NDB_Config::singleton();
        $this->dateOptions = array(
        'language' => 'en',
        'format'   => 'YMd',
        'minYear'  => $config->getSetting('startYear'),
        'maxYear'  => $config->getSetting('endYear'),
        'addEmptyOption' => true,
        'emptyOptionValue' => null
        );

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

        // display test name
        $this->form->addElement('header', 'instrument_title', "MRI Parameter Form");

        // automatically adds examiner & date of administration
        $this->_addMetadataFields();
        
        $this->addHourMinElement("wait_time", "Wait Time for Scanner (hours:minutes)");
        $this->addHourMinElement("total_duration", "Total Duration of Session (hours:minutes)");

        $yes_no_option= array(""=>NULL, "No"=>"No", "Complete"=>"Yes, Complete Acquisition", "Partial"=>"Yes, Partial Acquisition", "not_answered"=>"Not Answered");

        $this->form->addElement('header', null, 'Localizer');
        $this->form->addElement('static', null, 'Scan time: 1-2 min (exact details are not critical)');

        $this->form->addElement('header', null, 'Warm up scan (Coarse TSE PD/T2W)');
        $this->form->addElement('static', null, 'Optional warm-up sequence of site\'s choosing');
        $this->form->addElement('static', null, 'Scan time:  should not exceed 2 minutes');

        $this->form->addElement('header', null, '3D T1 MP-Rage');
        $this->form->addElement('static', null, 'SIEMENS: tfl');
        $this->form->addElement('select', 'T1_Scan_done', 'Was this sequence acquired?', $yes_no_option);
        $this->addNumericElement("T1_number_attempts", "Number of scan attempts:");
        $this->addDateElement('T1_Scan_done', 'If so, when?');
        $this->addTextAreaElement('T1_Comments', 'Comments');

        $this->form->addElement('header', null, 'High Resolution 3D T2W');
        $this->form->addElement('static', null, 'SIEMENS: tse_vfl');
        $this->form->addElement('select', 'T2_Scan_done', 'Was this sequence acquired?', $yes_no_option);
        $this->addNumericElement("T2_number_attempts", "Number of scan attempts:");
        $this->addDateElement('T2_Scan_done', 'If so, when?');
        $this->addTextAreaElement('T2_Comments', 'Comments');

        $this->form->addElement('header', null, '25 Direction DTI');
        $this->form->addElement('static', null, 'SIEMENS: epd2_diff');
        $this->form->addElement('select', 'DTI_Scan_done', 'Was this sequence acquired?', $yes_no_option);
        $this->addNumericElement("DTI_number_attempts", "Number of scan attempts:");
        $this->addDateElement('DTI_Scan_done', 'If so, when?');
        $this->addTextAreaElement('DTI_Comments', 'Comments');

    } // End setupForm
}
?>