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

	$this->form = new HTML_Quickform('test_form');
        $this->page = $page;            // page label (number or
                                        // string - used by
                                        // user-defined child classes)

        // set the object properties
        $this->testName = "mri_parameter_form";           // test_names.Test_name
        $this->table = 'mri_parameter_form';             // name of table containing
	
	// data keyed by commentID
        $this->commentID = $commentID;

	//$this->_requiredElements = array('Date_taken', 'Examiner', 'CaregiverReport');

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
        
        $yes_no_option= array(""=>NULL, "No"=>"No", "Complete"=>"Yes, Complete Acquisition", "Partial"=>"Yes, Partial Acquisition");
        
        $this->form->addElement('header', null, 'Localizer');
        $this->form->addElement('static', null, 'Scan time: 1-2 min (exact details are not critical)');
        
        $this->form->addElement('header', null, 'Warm up scan (Coarse TSE PD/T2W)');
        $this->form->addElement('static', null, 'Optional warm-up sequence of site\'s choosing');
        $this->form->addElement('static', null, 'Scan time:  should not exceed 2 minutes');
        
        $this->form->addElement('header', null, '3D T1 MP-Rage');
       	$this->form->addElement('static', null, 'SIEMENS: tfl');
        $this->form->addElement('select', 'T1_Scan_done', 'Was this scan done?', $yes_no_option);
        $this->form->addElement('date', 'T1_Scan_done_date', 'If so, when?');
        $this->form->addElement('textarea', 'T1_Comments', 'Comments');

        $this->form->addElement('header', null, 'High Resolution 3D T2W');
        $this->form->addElement('static', null, 'SIEMENS: tse_vfl');
        $this->form->addElement('select', 'T2_Scan_done', 'Was this scan done?', $yes_no_option);
        $this->form->addElement('date', 'T2_Scan_done_date', 'If so, when?');
        $this->form->addElement('textarea', 'T2_Comments', 'Comments');
        
        $this->form->addElement('header', null, '25 Direction DTI');
        $this->form->addElement('static', null, 'SIEMENS: epd2_diff');
        $this->form->addElement('select', 'DTI_Scan_done', 'Was this scan done?', $yes_no_option);
        $this->form->addElement('date', 'DTI_Scan_done_date', 'If so, when?');
        $this->form->addElement('textarea', 'DTI_Comments', 'Comments');
    } // End Setup form
}
?>