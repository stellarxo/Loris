<?php

require_once 'HTML/QuickForm.php';
require_once 'HTML/QuickForm/Renderer/Array.php';

class NDB_BVL_Instrument_audiology extends NDB_BVL_Instrument
{
/*
INSERT INTO test_names VALUES ('', 'audiology', 'Audiology Evaluation Results', '0', '1');

INSERT INTO test_battery VALUES ('', 'audiology', '660', '780', 'Y', 'Visit', '1');
INSERT INTO test_battery VALUES ('', 'audiology', '660', '780', 'Y', 'Visit', '2');
*/

    var $ValidityEnabled = false;
    var $ValidityRequired = false;


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
        $this->testName = "audiology";           // test_names.Test_name
        $this->table = 'audiology';              // name of database table corresponding to instrument
        // data keyed by commentID
        $this->commentID = $commentID;
        
        //The array of dates/timestamps to convert to database dates/timestamps
        //Any HTML_Quickform date elements must be listed here
        $this->dateTimeFields=array("Date_taken");
            
        //The array of selects with multiple answers allowed
        //Any HTML_Quickform multiple selects must be listed here
        $this->_selectMultipleElements = array();

        // required fields for data entry completion status
        $this->_requiredElements = array('Examiner');
	/**
	 * Array of column names to be ignored by the double data entry conflict detector.
	 */
	$this->_doubleDataEntryDiffIgnoreColumns = array('CommentID', 'UserID', 'Testdate', 'Window_Difference', 'Candidate_Age',
							 'not_completed_other_specify',
							 'not_completed_other_specify_status',
							 'other_method_specify',
							 'other_method_specify_status',
							 'equivocal_evaluation_results_specify',
							 'equivocal_evaluation_results_specify_status');
	



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
        if(preg_match("/audiology(_page[0-9]+)/",$this->page,$matches)){
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
        $this->form->addElement('header', null, 'Audiology');
        
        // automatically adds examiner & date of administration
        $this->_addMetadataFields();
        
        $this->form->addElement('header', 'instrument_title', "Audiology Evaluation Results");
        
        $this->form->addElement("select", "not_completed", "An audiology evaluation was not completed because...", array(null=>"", "non-asd"=>"Non-ASD", "other"=>"Other (please specify)"));
        $this->XINRegisterRule("not_completed", array("not_completed{@}=={@}NEVER_REQUIRED"));
        $this->addTextElement("not_completed_other_specify", $this->indent . "If other, please specify", array("not_completed{@}=={@}other"), "Please specify.");
        
        $config =& NDB_Config::singleton();
        $this->dateOptions = array(
        'language' => 'en',
        'format'   => 'YMd',
        'minYear'  => $config->getSetting('startYear'),
        'maxYear'  => $config->getSetting('endYear'),
        'addEmptyOption' => true,
        'emptyOptionValue' => null
        );
        $this->addDateElement('hearing_screening', "Date of hearing screening:");
        $this->XINRegisterRule("hearing_screening_date", array("hearing_screening_date_status{@}=={@}", "not_completed{@}!={@}non-asd"), "Please specify date of hearing");

        $this->form->addElement("static", null);
        $this->form->addElement("header", null, "Methods used: (check all that apply)");
        $this->form->addElement("advcheckbox", "vra", "Visual Reinforcement Audiometry", null, null, array("unused", "used"));
        $this->form->addElement("advcheckbox", "oae", "Otoacoustic Emission Testing", null, null, array("unused", "used"));
        $this->form->addElement("advcheckbox", "tympanometry", "Tympanometry", null, null, array("unused", "used"));
        $this->form->addElement("advcheckbox", "other_method", "Other", null, null, array("unused", "used"));
        $this->addTextElement("other_method_specify", $this->indent . "Please specify", array("other_method{@}=={@}used"), "Please specify");
        
        $this->form->addElement("static", null);
        $this->form->addElement("header", null, "Test Results:");
        $this->form->addElement("select", "test_results", "Result", array(null=>"", "normal_hearing"=>"Normal hearing", "temporary_hearing_difficulty"=>"Temporary hearing difficulty", "equivocal_evaluation_results"=>"Equivocal evaluation results", "permanent_abnormal_hearing"=>"Permanent abnormal hearing", "not_answered"=>"Not Answered"));
        $this->XINRegisterRule("test_results", array("not_completed{@}!={@}non-asd"), "Required");
        $this->form->addElement("select", "test_results_ear", $this->indent . "Ear", array(null=>"", "left_ear"=>"Left Ear", "right_ear"=>"Right Ear", "bilateral"=>"Bilateral", "not_answered"=>"Not answered"));
        $this->XINRegisterRule("test_results_ear", array("test_results{@}!={@}normal_hearing", "not_completed{@}!={@}non-asd"), "Please specify and ear");
        $this->form->addElement("select", "test_results_severity", $this->indent . "Severity", array(null=>"", "partial"=>"Partial", "total"=>"Total", "not_answered"=>"Not Answered"));
        $this->XINRegisterRule("test_results_severity", array("test_results{@}=={@}temporary_hearing_difficulty|permanent_abnormal_hearing"), "Please indicate a severity");
        $this->addTextAreaElement("equivocal_evaluation_results_specify", $this->indent . $this->indent . "Equivocal evaluation results specify", array("test_results{@}=={@}equivocal_evaluation_results"), "This field is required for equivocal results");

    }

}
?>
