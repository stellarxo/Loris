<?php
class NDB_BVL_Instrument_radiology_review extends NDB_BVL_Instrument
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
        $this->testName = "radiology_review";           // test_names.Test_name
        $this->table = 'radiology_review';             // name of table containing


        // data keyed by commentID
        $this->commentID = $commentID;

        //$this->_requiredElements = array('Date_taken', 'Examiner');

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
        $this->form->addElement('header', 'instrument_title', "Radiology Review Form");

        // automatically adds examiner & date of administration
        $this->_addMetadataFields();

        $yes_no_option= array("No"=>"No", "Yes"=>"Yes");
	$normal_option= array("Normal"=>"Normal","Abnormal"=>"Abnormal");

        $this->form->addElement('header', null, '3D T1 MP-Rage');
        $this->form->addElement('select', 'Scan_done', 'Was an MRI performed?', $yes_no_option);
       	$this->form->addElement('static', null, 'If Yes?'); 
       	$this->form->addElement('date', 'MRI_date', 'Date of MRI acquisition');       
	$this->form->addElement('date', 'Review_date', 'Date of local radiology review');
        $this->form->addElement('select', 'Review_results', 'Results of local radiology review?', $normal_option);
       	$this->form->addElement('static', null, 'If abnormal, describe incidental finding(s)'); 
        $this->form->addElement('textarea', 'Incidental_findings', 'Description of incidental findings:');

    } // End Setup form

/**
    * adds metadata fields (such as Examiner and Date_taken) to the
    * current form
    *
    * @return void
    * @access private
    */
    function _addMetadataFields()
    {
        $config =& NDB_Config::singleton();
        $dateOptions = array(
        'language' => 'en',
        'format'   => 'YMd',
        'minYear'  => $config->getSetting('startYear'),
        'maxYear'  => $config->getSetting('endYear'),
        'addEmptyOption' => true,
        'emptyOptionValue' => null
        );

        $this->form->addElement('date', 'Date_taken', 'Date of Administration', $dateOptions);

        $examiners = $this->_getExaminerNames();
        $this->form->addElement('select', 'Examiner', 'Radiologist', $examiners);

     	$this->form->addGroupRule('Date_taken', 'Date of Administration is required', 'required');

        $this->form->registerRule('checkdate', 'callback', '_checkDate');
        $this->form->addRule('Date_taken', 'Date of Administration is invalid', 'checkdate');

        $this->form->addRule('Examiner', 'Examiner is required', 'required');
    }



}
?>
