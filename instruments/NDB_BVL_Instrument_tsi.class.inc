<?php
class NDB_BVL_Instrument_tsi extends NDB_BVL_Instrument
{
	var $yesNo = array(null=>"", "yes"=>"Yes", "no"=>"No", "not_answered"=>"Not Answered");
	
	/*
	INSERT INTO test_names VALUES ('', 'tsi', 'Telephone Screening Interview', '0', '1');

	INSERT INTO instrument_subtests VALUES('', 'tsi', 'tsi_page1', 'Exclusionary Factors', 1);
	INSERT INTO instrument_subtests VALUES('', 'tsi', 'tsi_page2', 'Medical History or MRI/Sedation', 2);
	INSERT INTO instrument_subtests VALUES('', 'tsi', 'tsi_page3', 'Medical Records / Research Staff', 3);

	INSERT INTO test_battery VALUES ('', 'tsi', '150', '210', 'Y', 'Screening', '1');
	INSERT INTO test_battery VALUES ('', 'tsi', '300', '420', 'Y', 'Screening', '2');
	INSERT INTO test_battery VALUES ('', 'tsi', '150', '420', 'Y', 'Screening', '3');
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
		$this->testName = "tsi";           // test_names.Test_name
		$this->table = 'tsi';              // name of database table corresponding to instrument
		// data keyed by commentID
		$this->commentID = $commentID;

		//The array of dates/timestamps to convert to database dates/timestamps
		//Any HTML_Quickform date elements must be listed here
		$this->dateTimeFields=array("Date_taken");

		//The array of selects with multiple answers allowed
		//Any HTML_Quickform multiple selects must be listed here
		$this->_selectMultipleElements = array();

		// required fields for data entry completion status
		$this->_requiredElements = array('Examiner', "typical_or_asd_subject");

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
		if(ereg("tsi(_page[0-9]+)",$this->page,$matches)){
			call_user_method($matches[1], &$this);
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
		// display test name
		$this->form->addElement('header', 'instrument_title', 
"Telephone Screening Interview");

		// automatically adds examiner & date of administration
		$this->_addMetadataFields();

		$this->form->addElement('header', null, "Identifying information");
		$this->form->addElement('header', null, "This type of identifying information should not be entered in the database");
		$nonAskedQuestions = array("Subject's Name",
		"Subject ID:",
		"Date of Contact: Date of Birth:",
		"Contacted By:",
		"Subject's Gender: $this->indent Subject's Age (in months):",
		"Ethnicity:",
		"Race:",
		"Parent's Information:",
		"Parent's Telephone:",
		"Parent's Address:",
		"$this->indent a) Older sibling",
		"$this->indent b) other siblings:",
		"Nature of Referral:",
		"SUBJECT  Ever been a patient at UNC?");
		foreach ($nonAskedQuestions as $field) {
			$this->form->addElement('static', null, $field);
		}

	}

	function _page1(){
		//typical or ASD subject?
		$this->form->addElement("select", "typical_or_asd_subject", "Typical or ASD subject?", array(null=>"", "typical"=>"Typical", "asd"=>"ASD", "not_answered"=>"Not Answered"));

		$this->form->addElement('header', null, "Exclusionary Factors - ASD PROBANDs only");

		$questionArray = array("neurological_problems_proband"=>"Any neurological problems in PROBAND?",
		"genetic_conditions_proband"=>"Diagnosed/suspected genetic conditions or syndromes?",
		"seizures_disorders"=>"Seizures/other neurological disorder (tuberous sclerosis)?",
		"relative_with_disorder"=>"1st degree relative w/ MR, schizophrenia, bipolar or psychosis?",
		"cns"=>"CNS problem/injury?",
		"tested_for_fragile_x"=>"Tested for Fragile X syndrome?");
		foreach($questionArray as $field=>$label) {
			$this->form->addElement("select", $field, $label, $this->yesNo);
			$this->XINRegisterRule($field, array("typical_or_asd_subject{@}=={@}asd"), "This field is required for an ASD subject");
		}

		$this->addTextAreaElement("asd_further_information", "If yes to any of the above, obtain further information.", array("typical_or_asd_subject{@}=={@}asd"));

		$this->form->addElement("header", null, "Exclusionary Factors - Infant subjects");
		$questionArray = array("relative_with_asd"=>"1st or 2nd relative with ASD?",
		"neurological_problems_subject"=>"Any neurological problems in SUBJECT?",
		"genetic_conditions_subject"=>"Diagnosed/suspected genetic conditions or syndromes?",
		"seizures_or_neuro_disorder"=>"Seizures or other neurological disorder?",
		"cns_problems"=>"CNS problems?",
		"congenital_heart_problems"=>"Congenital heart problems?",
		"hearing_vision_impairments"=>"Significant hearing/vision problems?",
		"diabetes"=>"Diabetes or gestational diabetes?",
		"premature_birth"=>"Premature birth (<37 weeks )?",
		"low_birth_weight"=>"Birth weight <4lbs. 6oz. (2000 grams)?",
		"delivery_problems"=>"Problems during delivery?");
		foreach($questionArray as $field=>$label) {
			$this->form->addElement("select", $field, $label, $this->yesNo);
		}

		$this->form->addElement('select', "in_utero_exposure", "Exposure in-utero to meds, alcohol, or drugs (Rx or non)?", $this->yesNo);

		$questionArray = array("substance"=>"Name of substance (get spelling):",
		"substance_amount"=>"Amount of substance at one time:",
		"time_exposure"=>"Time period of exposure (weeks of pregnancy):");
		foreach($questionArray as $field=>$label) {
			$this->addTextElement("in_utero_" . $field, $this->indent . $label, array("in_utero_exposure{@}=={@}yes"), "This field is required if there was in-utero exposure");
		}
		$this->addTextAreaElement("further_information", "If yes to any of the above, obtain further information.");
	}

	function _page2() {
		$this->form->addElement('header', null, "Medical History Pertaining to MRI/Sedation");
		$this->form->addElement("select", "med_his_q_1_med_surgical_problems", "1. Has X ever had any serious medical or surgical problems?", $this->yesNo);
		$this->form->addElement("select", "med_his_q_2_hospitalized", "2. Has X ever been hospitalized?", $this->yesNo);
		$this->form->addElement("select", "med_his_q_3_surgery", "3. Surgery of any type?", $this->yesNo);
		$this->addTextElement("med_his_q_3_surgery_describe", $this->indent . "Describe:", array("med_his_q_3_surgery{@}=={@}yes"), "This field is required if there was surgery");
		$this->form->addElement("select", "med_his_q_4_metal", "4. Does X have any metal plates, clips, etc. from surgery?", $this->yesNo);
		$this->form->addElement("select", "med_his_q_5_medications", "5. Has X taken any medications over the last 12 months?", $this->yesNo);
		$this->addTextElement("med_his_q_5_medications_describe", $this->indent . "If yes, list medications:", array("med_his_q_5_medications{@}=={@}yes"), "This field is required if there were medications");
		$this->form->addElement("select", "med_his_q_6_allergies", "6. Does X have any allergies to medicines?", $this->yesNo);
		$this->addTextElement("med_his_q_6_allergies_describe", $this->indent . "If yes, describe:", array("med_his_q_6_allergies{@}=={@}yes"), "This field is required if there are allergies");
		$this->form->addElement("select", "med_his_q_7_doctor", "7. Has X seen a doctor over the last 12 months?", $this->yesNo);
		$this->form->addElement("select", "med_his_q_8_brain_MRI", "8. Has X ever had an MRI of the brain?", $this->yesNo);
		$this->addTextElement("med_his_q_8_brain_MRI_results", $this->indent . "If yes, what were the results?", array("med_his_q_8_brain_MRI{@}=={@}yes"), "This field is required if a brain MRI was done.");
		$this->form->addElement("select", "med_his_q_9_anethesia", "9. Has X ever had anesthesia or other forms of sedation?", $this->yesNo);
		$this->addTextElement("med_his_q_9_anethesia_problems", $this->indent . "Problems with sedation?", array("med_his_q_9_anethesia{@}=={@}yes"), "This field is required if there were sedation problems.");
		$this->addTextElement("med_his_q_10_nap", "10. Does X nap during the day?");
		$this->addTextElement("med_his_q_11_nap_how_long", "11. When & how long?");
		$this->form->addElement("select", "med_his_q_12_likelihood_sleep", "12. On a scale of 1-10, please rate the likelihood of your child sleeping through a scan.", array(null=>"", 1=>"1", 2=>"2",  3=>"3", 4=>"4", 5=>"5", 6=>"6", 7=>"7", 8=>"8", 9=>"9", 10=>"10", "not_answered"=>"Not Answered"));
		
	}

	function _page3() {
		$this->form->addElement("header", null, "Medical Records");
		$this->form->addElement('header', null, "This type of identifying information should not be entered in the database");
		$this->form->addElement("static", null, "Any diagnoses, dates and locations:");
		$this->form->addElement("static", null, "Has X had any other cognitive/developmental testing?");
		$this->form->addElement("static", null, $this->indent . "If yes, where was evaluation done/who conducted the evaluation?");
		$this->form->addElement("static", null, "Is any member of your family participating in a research study at this time?");
		
		$this->form->addElement("header", null, "FOR RESEARCH STAFF TO COMPLETE");
		$this->form->addElement("static", null, "Exclusion/Inclusion");
		$this->form->addElement("select", "exc_inc_meets_criteria", "1. This subject meets any of the medical or neurological exclusion criteria for this study. (see Section A)", $this->yesNo);
		$this->form->addElement("select", "exc_inc_contraindication", "3. This subject has evidence for contraindication to MRI. (see Section B)", $this->yesNo);
		$this->form->addElement("static", null, "Disposition");
		$this->form->addElement("select", "disposition", "Proceed to next level beyond screening?", $this->yesNo);
	}
	
}
?>
