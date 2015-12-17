<?php

require_once 'HTML/QuickForm.php';
require_once 'HTML/QuickForm/Renderer/Array.php';
require_once "TimePoint.class.inc";

class NDB_BVL_Instrument_med_psych_hist extends NDB_BVL_Instrument
{
    /*
    INSERT INTO test_names VALUES ('', 'med_psych_hist', 'Medical Psychiatric History', '0', '1');
    INSERT INTO instrument_subtests VALUES('', 'med_psych_hist', 'med_psych_hist_page1', '1. Pregnancy History', 1);
    INSERT INTO instrument_subtests VALUES('', 'med_psych_hist', 'med_psych_hist_page2', '3. Child and Relatives', 2);
    INSERT INTO instrument_subtests VALUES('', 'med_psych_hist', 'med_psych_hist_page3', '4. Pregnancy', 3);
    INSERT INTO instrument_subtests VALUES('', 'med_psych_hist', 'med_psych_hist_page4', '7. Pregnancy Health Problems', 4);
    INSERT INTO instrument_subtests VALUES('', 'med_psych_hist', 'med_psych_hist_page5', '15. Neurological Function', 5);
    INSERT INTO test_battery VALUES ('', 'med_psych_hist', '1050', '1140', 'Y', 'Visit', '3');
    */

    var $ValidityEnabled = false;
    var $ValidityRequired = false;

    var $columnHeaders = array("presence_header",
    "relative_header",
    "other_relative_header");
    var $yesNo = array('0_no'=>"0. No", "1_yes"=>"1. Yes", "not_answered"=>"Not Answered");

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
        $this->testName = "med_psych_hist";           // test_names.Test_name
        $this->table = 'med_psych_hist';              // name of database table corresponding to instrument
        // data keyed by commentID
        $this->commentID = $commentID;

        //The array of dates/timestamps to convert to database dates/timestamps
        //Any HTML_Quickform date elements must be listed here
        $this->dateTimeFields=array("Date_taken");

        //The array of selects with multiple answers allowed
        //Any HTML_Quickform multiple selects must be listed here
        $this->_selectMultipleElements = array(
//        "a_aut_spect_disorder_who",
//        "b_fragile_x_who",
//        "c_tuberous_sclerosis_who",
//        "d_neurofibromatosis_who",
//        "e_rett_syndrome_who",
//        "f_child_disint_disorder_who",
//        "g_prader_willi_syndrome_who",
//        "h_angelman_syndrome_who",
//        "i_other_chromosomal_who",
//        "j_congenital_rubella_who",
//        "k_pku_who",
//        "l_hydrocephalus_who",
//        "m_cerebral_palsy_who",
//        "n_mental_retardation_who",
//        "o_seizures_who",
//        "p_speech_delay_therapy_who",
//        "q_add_who",
//        "r_panic_anxiety_dis_who",
//        "s_depression_who",
//        "t_manic_depres_bi_who",
//        "u_schizophrenia_who",
//        "v_hospital_mental_ill_who",
//        "w_birth_defects_who",
//        "x_cancer_who",
//        "y_norrie_syndrome_who",
        "q4_pregnancy_ART_type", "q5_pregnancy_health_problems",
        "q6_pregnancy_meds", "q7_baby_health_problems", "q8_pregnancy_alcohol_tobacco", "q9_pregnancy_drugs", "q12_birth_interventions", "q16_has_child_ever", "q17_birth_defects");

        // required fields for data entry completion status
        //		$this->_requiredElements = array('Examiner', 'abbrev_full_version', "child_pregnancy_number", "4_pregnancy_ART", "10_meds_induce_labor", "15_seizures_convulsions");
        $this->_requiredElements = array('Examiner', 'abbrev_full_version');

        $config =& NDB_Config::singleton();
        $this->dateOptions = array(
        'language' => 'en',
        'format'   => 'YMd',
        'minYear'  => $config->getSetting('startYear') - 20, //allows for siblings up to 20 years older than candidate
        'maxYear'  => $config->getSetting('endYear'),
        'addEmptyOption' => true,
        'emptyOptionValue' => null
        );

        // Column headers
        $this->localDefaults = array_merge($this->localDefaults, array("presence_header"=>"Presence",
        "relative_header"=>"Relative",
        "other_relative_header"=>"Other Relative"));
        //Are we using the Full or Abbreviated version?
        // DB Object
        $db =& Database::singleton();

        //applicable version
        // This hasn't been implemented terrifically smoothly.  It may require an extra "Save Data" click.
        // During most regular workflows (data entry), the glitches should go unnoticed.  Hopefully.
        $query = "SELECT abbrev_full_version from med_psych_hist WHERE CommentID = '".$this->getCommentID()."'";
        $version = $db->selectOne($query);

        if ($version == 'abbrev') {
            $this->_requiredElements = array_merge($this->_requiredElements, array("child_pregnancy_number"));
        } else {
            $this->_requiredElements = array_merge($this->_requiredElements, array("q4_pregnancy_ART", "q10_meds_induce_labor", "q15_seizures_convulsions"));
        }
        $record = $db->pselectOne("SELECT followup_form_updated FROM med_psych_hist WHERE CommentID=:cid", array('cid'=>$this->getCommentID()));
        if($record == 'no') {
            $this->_requiredElements = array();
        }
//print_r($this->_requiredElements);
    /**
    * Array of column names to be ignored by the double data entry conflict detector.
    */
    $this->_doubleDataEntryDiffIgnoreColumns = array('CommentID', 'UserID', 'Testdate',  'Window_Difference', 'Candidate_Age',
						     'relationship_to_child_other', 
						     'a_aut_spect_disorder_who_other',
						     'b_fragile_x_who_other', 
						     'c_tuberous_sclerosis_who_other', 
						     'd_neurofibromatosis_who_other', 
						     'e_rett_syndrome_who_other', 
						     'f_child_disint_disorder_who_other',
						     'g_prader_willi_syndrome_who_other',
						     'h_angelman_syndrome_who_other',
						     'i_other_chromosomal_who_other',
						     'j_congenital_rubella_who_other',
						     'k_pku_who_other',
						     'l_hydrocephalus_who_other',
						     'm_cerebral_palsy_who_other',
						     'n_mental_retardation_who_other',
						     'o_seizures_who_other',
						     'p_speech_delay_therapy_who_other',
						     'q_add_who_other',
						     'r_panic_anxiety_dis_who_other',
						     's_depression_who_other',
						     't_manic_depres_bi_who_other',
						     'u_schizophrenia_who_other',
						     'v_hospital_mental_ill_who_other',
						     'w_birth_defects_who_other',
						     'x_cancer_who_other',
						     'x_cancer_other',
						     'q4_pregnancy_ART_type_specify',
						     'q5_pregnancy_health_problems_specify',
						     'q6_preg_meds_q_thalid_specify',
						     'q6_preg_meds_r_miso_specify',
						     'q6_preg_meds_s_other_specify',
						     'q7_a_positive_blood_test_specify',
						     'q7_b_abnormal_ultra_sono_specify',
						     'q7_c_abnormal_amnio_CVS_specify',
						     'q7_d_other_specify',
						     'q9_i_other_specify',
						     'q16_unconscious_1_years',
						     'q16_unconscious_1_months',
						     'q16_unconscious_2_years',
						     'q16_unconscious_2_months',
						     'q16_unconscious_3_years',
						     'q16_unconscious_3_months',
						     'q17_d_heart_defect_specify',
						     'q17_e_kidney_defect_specify',
						     'q17_f_other_defect_specify',
						     'q18_other_chronic_a_specify',
						     'q18_other_chronic_b_specify',
						     'q18_other_chronic_c_specify',
						     'Data_entry_completion_status'
                             );

    

        // setup the form
        $this->_setupForm();
						      

    }

    //If the instrument is not paged, remove the switch from the _setupForm method and add all the form Elements in this function.

    /**
    * method to build the HTML_Quickform object into a paged form
    *
    * @return void
    * @access private
    */
    function _setupForm(){

        //add the initial null choice to the commonly-presented answers options.
        $this->yesNo = array_merge(array(null=>''), $this->yesNo);
        
        //determine page to display
        if(preg_match("/med_psych_hist(_page[0-9]+)/",$this->page,$matches)){
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
 
        $db = & Database::singleton();
        if(isset($_REQUEST['CommentID'])){
        $cand = $db->pselectRow("SELECT c.CandID, s.Visit_label from session as s, flag as f, candidate c where f.sessionId = s.ID and
                                 s.CandID=c.CandID and f.CommentID=:cid", array('cid'=>$this->getCommentID())); 

        $candidate = Candidate::singleton($cand['CandID'] ); 

        $firstVisit = false;
        $vLabel = $db->pselectOne("SELECT Visit_label FROM session s JOIN candidate c 
                                   ON (c.CandID = s.CandID) WHERE c.CandID=:cid 
                                   ORDER BY Date_Visit", array('cid'=>$cand['CandID']));//get first visit for candidate 
        if($vLabel ==  $cand['Visit_label']){
            $firstVisit = true; //if current visit label is same as visit label returned must be first visit   
        }
        $current_visitlabel = $cand['Visit_label'];
        $this->form->addFormRule(array(&$this, 'firstVisitCheck'));
        }
        // display test name
        $this->form->addElement('header', 'instrument_title', "Medical and Psychiatric History");

        // automatically adds examiner & date of administration
        $this->_addMetadataFields();

        $this->form->addElement('select', 'relationship_to_child', "Relationship to Child to be seen in study:", array(NULL=>"",
        "biological_mother"=>"biological mother",
        "biological_father"=>"biological father",
        "adoptive_mother"=>"adoptive mother",
        "stepmother"=>"stepmother",
        "stepfather"=>"stepfather",
        "adoptive_father"=>"adoptive father",
        "other"=>"other",
        "not_answered"=>"Not Answered"));
        $this->addTextElement('relationship_to_child_other', $this->indent . "If other, (please explain)", array('relationship_to_child{@}=={@}other'), "This field is required if the relationship is not previously identified.");

        $this->form->addElement('select', 'abbrev_full_version', "Full or abbreviated (items #1-#3) version:", array(null=>'', 'full'=>"Full", 'abbrev'=>"Abbreviated"));

		$this->addSelect('followup_form_updated',"Were there any changes?<BR>(Required only if NOT first visit)", array(null=>'','yes'=>'Yes','no'=>'No','not_answered'=>'Not Answered'));
        $this->XINRegisterRule("followup_form_updated", array("followup_form_updated{@}=={@}NEVER_REQUIRED"));
 
		$this->addLabel("NOTE: If 'No' is entered, continue data entry at item 4, unless the <BR>abbreviated version was administered (in which case, no further <BR> data entry is required).");

    }

    function _page1(){
        $this->form->addElement('header', null, "1. Pregnancy history:");
        $this->form->addElement('static', null, "Nothing needs be filled out after 'No More Pregnancies' is indicated.");
        $this->form->addElement('static', null, null);

        $firstToTwentieth = array("first"=>"First", "second"=>"Second", "third"=>"Third", "fourth"=>"Fourth", "fifth"=>"Fifth", "sixth"=>"Sixth", "seventh"=>"Seventh", "eighth"=>"Eighth", "ninth"=>"Ninth", "tenth"=>"Tenth", "eleventh"=>"Eleventh", "twelfth"=>"Twelfth", "thirteenth"=>"Thirteenth", "fourteenth"=>"Fourteenth", "fifteenth"=>"Fifteenth", "sixteenth"=>"Sixteenth", "seventeenth"=>"Seventeenth", "eighteenth"=>"Eighteenth", "nineteenth"=>"Nineteenth", "twentieth"=>"Twentieth");
        reset($firstToTwentieth);
        while(list($field, $label) = each($firstToTwentieth)){
//        foreach($firstToTwentieth as $label=>$nth) {
            $this->form->addElement('static', null, "{$label} Pregnancy");
            $this->form->addElement("select", "{$field}_a_pregnancy_outcome", $this->indent . "a. What was the outcome of this pregnancy?", array(NULL=>"", "live_birth"=>"Live birth",
            "still_birth"=>"Stillbirth",
            "elective_termination"=>"Elective Termination",
            "miscarriage"=>"Miscarriage",
            "no_more_pregnancies"=>"No More Pregnancies",
            "not_answered"=>"Not Answered"));

            //Once "No More Pregnancies" is selected once, nothing further is required.
            $this->XINRegisterRule("{$field}_a_pregnancy_outcome", array("{$prevField}_a_pregnancy_outcome{@}!={@}no_more_pregnancies", "{$prevField}_a_pregnancy_outcome{@}!={@}"), 'This field is required until the prior pregnancy is marked with "No More Pregnancies"');
            prev($firstToTwentieth);
            $prevField = key($firstToTwentieth);// {
            next($firstToTwentieth);

            $this->form->addElement('select', "{$field}_a_pregnancy_outcome_still_living", $this->indent . "1. If live birth, child still living", array(NULL=>"", "yes"=>"Yes", "no"=>"No", "not_answered"=>"Not Answered"));
            $this->XINRegisterRule("{$field}_a_pregnancy_outcome_still_living", array("{$field}_a_pregnancy_outcome{@}=={@}live_birth"), "This field is required if a. outcome of this pregnancy was a Live birth");

            //Test the rule here...
            $this->addDateElement("{$field}_b_date_of_birth", $this->indent . "b. Date of birth (if stillbirth or live birth only)");
            $this->XINRegisterRule("{$field}_b_date_of_birth_date", array("{$field}_a_pregnancy_outcome{@}=={@}live_birth|still_birth"), "Date of birth is required for stillbirth or live birth only.", "{$field}_b_date_of_birth_date_group");

            $this->form->addElement("select", "{$field}_c_delivery_week", $this->indent . "c. At what week did you deliver in this pregnancy? (if stillbirth or live birth only)", array(null=>"",
            "greater_than_37"=>"Greater than 37 completed weeks",
            "less_than_28"=>"Less than 28 completed weeks",
            "between_28_32"=>"Between 28 and 32 completed weeks",
            "between_32_37"=>"Between 32 and 37 completed weeks",
            "unknown"=>"Fetus age at delivery unknown",
            "not_answered"=>"Not Answered"));
            $this->XINRegisterRule("{$field}_c_delivery_week", array("{$field}_a_pregnancy_outcome{@}=={@}live_birth|still_birth"), "This field is required if a. outcome of this pregnancy was a Live birth.");
        }

        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement("header", null, "Pregnancy Number");
        $this->form->addElement("select", "child_pregnancy_number", "2. What pregnancy number corresponds to the child being evaluated for this study?", array_merge(array(NULL=>""), $firstToTwentieth, array('not_answered'=>"Not Answered")));

    }

    function _page2(){
        $this->form->addElement("header", null, "3. The items below ask about the medical history of the child and relatives");
        $this->form->addElement("static", null, "***Hold the CTRL key while clicking to select multiple relatives.");
        $answerArray = array(null=>"", '0_no'=>"0. No", "1_yes"=>"1. Yes", "2_not_sure"=>"2. Not Sure", "not_answered"=>"Not Answered");
        $questionArray = array(
        "a_aut_spect_disorder"=>"a. Autism Spectrum Disorder",
        "b_fragile_x"=>"b. Fragile X",
        "c_tuberous_sclerosis"=>"c. Tuberous Sclerosis",
        "d_neurofibromatosis"=>"d. Neurofibromatosis",
        "e_rett_syndrome"=>"e. Rett Syndrome",
        "f_child_disint_disorder"=>"f. Childhood Disintegration Disorder",
        "g_prader_willi_syndrome"=>"g. Prader Willi Syndrome",
        "h_angelman_syndrome"=>"h. Angelman Syndrome",
        "i_other_chromosomal"=>"i. Other chromosomal abnormality, disorder or syndrome",
        //"i_other_chromosomal"=>"i. Other chromosomal abnormality, disorder or syndrome",
        "j_congenital_rubella"=>"j. Congenital rubella",
        "k_pku"=>"k. PKU",
        "l_hydrocephalus"=>"l. Hydrocephalus",
        "m_cerebral_palsy"=>"m. Cerebral Palsy",
        "n_mental_retardation"=>"n. Mental retardation",
        "o_seizures"=>"o. Seizures",
        "p_speech_delay_therapy"=>"p. Speech delay requiring therapy",
        "q_add"=>"q. Attention Deficit Disorder (ADD)",
        "r_panic_anxiety_dis"=>"r. Panic or anxiety disorder",
        "s_depression"=>"s. Depression",
        "t_manic_depres_bi"=>"t. Manic depression/Bipolar",
        "u_schizophrenia"=>"u. Schizophrenia",
        "v_hospital_mental_ill"=>"v. Been admitted to a hospital for psychiatric illness",
        "w_birth_defects"=>"w. Birth defects (e.g., cleft lip or palate, open spine)",
        "x_cancer"=>"x. Cancer (please specify type)",
        //"x_cancer"=>"x. Cancer (please specify type)",
        "y_norrie_syndrome"=>"y. Norrie Syndrome");

        $realtives = array(null=>"",
        "child"=>"Child",
        "parents_mom"=>"Parents of Child (Mom)",
        "parents_dad"=>"Parents of Child (Dad)",
        "siblings"=>"Siblings",
        "half_siblings_mat"=>"Half Siblings (Mat)",
        "half_siblings_pat"=>"Half Siblings (Pat)",
        "first_cousins_mat"=>"First Cousins (Mat)",
        "first_cousins_pat"=>"First Cousins (Pat)",
        "aunts_uncles_mat"=>"Aunts & Uncles (Mat)",
        "aunts_uncles_pat"=>"Aunts & Uncles (Pat)",
        "grandparents_mat"=>"Grandparents (Mat)",
        "grandparents_pat"=>"Grandparents (Pat)",
//        "multiple_relatives"=>"Multiple Relatives (describe)",
        "other"=>"Other (specify relationship)",
        "not_answered"=>"Not Answered");

        //Column headers
        $group[] = $this->form->createElement("static", "presence_header");
        $group[] = $this->form->createElement("static", "relative_header");
        $group[] = $this->form->createElement("static", "other_relative_header");
        $this->form->addGroup($group, null, "Disorder", $this->_GUIDelimiter, FALSE);
        unset($group);

        foreach($questionArray as $field=>$label) {
            $group[] = $this->form->createElement("select", $field, $label, $answerArray);
//            $group[] = $this->form->createElement("select", "{$field}_who", null, $realtives, "multiple");
            $group[] = $this->form->createElement("select", "{$field}_who", null, $realtives, "multiple size='5'");
            $group[] = $this->form->createElement("text", "{$field}_who_other", null);
            $group[] = $this->form->createElement("select", "{$field}_who_other_status", null, array(null=>"", "not_answered"=>"Not Answered"));
            $this->form->addGroup($group, "{$field}_group", $label, $this->_GUIDelimiter, FALSE);

            //insert into the _selectMultiple array
            $this->_selectMultipleElements[] = "{$field}_who";
            
            $this->XINRegisterRule("$field", array("$field{@}=={@}"), "Please indicate the presence of the disorder / problem.", "{$field}_group");
            $this->XINRegisterRule("{$field}_who", array("{$field}{@}=={@}1_yes|2_not_sure"), "Please indicate the effected realtive.", "{$field}_group");
            $this->XINRegisterRule("{$field}_who_other", array("{$field}_who{@}=={@}other", "{$field}_who_other_status{@}=={@}"), "Please specify the other relative(s).", "{$field}_group");
            //			$this->XINRegisterRule("{$field}_who_other_status", array("{$field}_who_other{@}=={@}"), "Please specify the other relative, or select Not Answered", "{$field}_group");
            $this->XINRegisterRule("{$field}_who_other_status", array("{$field}_who{@}=={@}other", "{$field}_who_other{@}=={@}"), "Please specify the relative, or select Not Answered", "{$field}_group");
            unset($group);

            if($field == "i_other_chromosomal") {
                $this->addTextElement("i_other_chromosomal_other", $this->indent . "Please specify", array("i_other_chromosomal{@}=={@}1_yes|2_not_sure"), "Please specify the chromosomal abnormality");
            } elseif ($field == "x_cancer") {
                $this->addTextElement("x_cancer_other", $this->indent . "Please specify", array("x_cancer{@}=={@}1_yes|2_not_sure"), "Please specify the cancer type");

            }
        }
    }

    function _page3() {
        $this->form->addElement("select", "q4_pregnancy_ART", "4. Was this pregnancy the result of Assisted Reproductive Technology (ART)?", $this->yesNo);
        $this->form->addElement("select", "q4_pregnancy_ART_type", $this->indent . "If 1. YES, what type(s) of ART/ovulation induction techniques: (select all used)", array(
        "a_ovulation_induction"=>"a. Ovulation induction",
        "b_in_vitro_fertilization"=>"b. In Vitro Fertilization (IVF)",
        "c_GIFT_or_ZIFT"=>"c. GIFT or ZIFT",
        "d_Intracytoplasmic_sperm_injection"=>"d. Intracytoplasmic sperm injection (ICSI)",
        "e_sperm_donor"=>"e. Sperm donor",
        "f_egg_donor"=>"f. Egg donor",
        "g_eggs_or_embryos_frozen"=>"g. Eggs or embryos frozen",
        "h_other"=>"h. Other"), "multiple");
        $this->XINRegisterRule("q4_pregnancy_ART_type", array("q4_pregnancy_ART{@}=={@}1_yes"), "Please indicate which ART were used.");
        $this->addTextElement("q4_pregnancy_ART_type_specify", $this->indent . $this->indent . "If other, (please specify)", array("q4_pregnancy_ART_type{@}=={@}h_other"), "If other ART used, please specify or select Not Answered");

        $this->form->addElement("select", "q5_preg_health_probs", "5. At any time in this pregnancy, did you have any of the following health problems? (select all used)", array(
        "a_fever_over_101_or_infection"=>"a.   Fever over 101 F or infection",
        "b_seizures"=>"b. Seizures",
        "c_viral_illness"=>"c. Viral illness",
        ""=>"d.Question Removed", 
        "e_preterm_labor"=>"e. Preterm labor requiring treatment",
        "f_other_major_illness_or_injury"=>"f. Other major illness or injury",
        "g_vaginal_bleeding"=>"g. Vaginal Bleeding",
        "h_generalized_edema"=>"h. Generalized edema",
        "i_proteinuria"=>"i. Proteinuria",
        "j_high_blood_pressure"=>"j. High blood pressure"), "multiple");
        $this->addTextElement("q5_pregnancy_health_problems_specify", $this->indent . "If other, (please specify)", array("q5_pregnancy_health_problems{@}=={@}f_other_major_illness_or_injury"), "If other health problems, please specify or select Not Answered");

        $questionArray = array("a_antibio_infections"=>"a. Antibiotics for infections",
        "b_acne_meds"=>"b. Medications for acne",
        "c_birth_control_meds"=>"c. Medications for birth control",
        "d_antihypertensives"=>"d. Antihypertensives for high blood pressure",
        "e_heart_cardiac_meds"=>"e. Medications for heart or cardiac problems",
        "f_ADD_meds"=>"f. Medications for Attention Deficit Disorder",
        "g_antiepilep_anti_seizure"=>"g. Antiepileptics or anti-seizure medications",
        "h_diabetes_meds"=>"h. Medications to control diabetes",
        "i_thyroid_meds"=>"i. Medications to regulate thyroid",
        "j_antidepressants"=>"j. Antidepressants",
        "k_mood_stabs_anti_psychos"=>"k. Mood stabilizers or anti-psychotics",
        "l_tranquilizers_nerve_pills"=>"l. Tranquilizers or nerve pills",
        "m_pain_killers"=>"m. Pain killers",
        "n_sedatives_sleeping_pills"=>"n. Sedatives or sleeping pills",
        "o_anti_inflam_immune"=>"o. Anti-inflammatory or anti-immune drugs",
        "p_treatment_for_HIV"=>"p. Treatment for HIV",
        "q_thalidomide"=>"q. Thalidomide (please specify why)",
        "r_misoprostol"=>"r. Misoprostol (please specify why)",
        "s_other"=>"s. Other (please specify medication and why)");

        $this->form->addElement("select", "q6_pregnancy_meds", "6. In this pregnancy, did you take any of the following prescription medications?",
        $questionArray, "multiple");

        $this->form->addElement("static", null, "Please specify when's");
        foreach($questionArray as $field=>$label) {
            $this->form->addElement("select", "q6_{$field}_when_taken", $this->indent . "If $label were taken, when?:", array("0_before"=>"0 Before", "1_after"=>"1 After", "2_both"=>"2 Both", "3_breastfeeding"=>"3 Breastfeeding","not_answered"=>"Not Answered"), "multiple size='5'");
            $this->XINRegisterRule("q6_{$field}_when_taken", array("q6_pregnancy_meds{@}=={@}{$field}"), "Please specify when $label was taken");
            $this->_selectMultipleElements[]= "q6_{$field}_when_taken";
        }

        $this->form->addElement("static", null, "Please specify what's and why's");
        $this->addTextElement("q6_preg_meds_q_thalid_specify", $this->indent . "If q. Thalidomide, please specify why medication was prescribed", array("q6_pregnancy_meds{@}=={@}q_thalidomide"), "If Thalidomide was prescribed, please specify why.");
        $this->addTextElement("q6_preg_meds_r_miso_specify", $this->indent . "If r. Misoprostol, please specify why medication was prescribed", array("q6_pregnancy_meds{@}=={@}r_misoprostol"), "If Misoprostol was prescribed, please specify why.");
        $this->addTextElement("q6_preg_meds_s_other_specify", $this->indent . "If s. Other, please specify medication and why it was prescribed", array("q6_pregnancy_meds{@}=={@}s_other"), "If Other meds were prescribed, please specify which and why.");
    }

    function _page4() {

        //7.
        $this->form->addElement("select", "q7_baby_health_problems", "7. In this pregnancy, did your doctor tell you that the baby had any of the following health problems?", array("a_positive_blood_test"=>"a. Screen positive on a blood test",
        "b_abnormal_ultrasound_or_sonogram"=>"b. Abnormal ultrasound or sonogram",
        "c_abnormal_amniocentesis_or_CVS"=>"c. Abnormality from an amniocentesis or CVS",// (please specify)
        "d_other"=>"d. Other (please specify)"), "multiple");
        $this->addTextElement("q7_a_positive_blood_test_specify", $this->indent . "If positive blood tests, please specify", array("q7_baby_health_problems{@}=={@}a_positive_blood_test"), "Please specify the results of the positive blood test.");
        $this->addTextElement("q7_b_abnormal_ultra_sono_specify", $this->indent . "If abnormal ultrasound or sonogram, please specify", array("q7_baby_health_problems{@}=={@}b_abnormal_ultrasound_or_sonogram"), "Please specify the results of the abnormal ultrasound or sonogram.");
        $this->addTextElement("q7_c_abnormal_amnio_CVS_specify", $this->indent . "If abnormal abnormal amniocentesis or CVS, please specify", array("q7_baby_health_problems{@}=={@}c_abnormal_amniocentesis_or_CVS"), "Please specify the results of the abnormal amniocentesis or CVS");
        $this->addTextElement("q7_d_other_specify", $this->indent . "If other, please specify", array("q7_baby_health_problems{@}=={@}d_other"), "Please specify the other results.");

        //8.
        $this->form->addElement("select", "q8_pregnancy_alcohol_tobacco", "8. In this pregnancy, did you do any of the following activities?", array("a_drink_alcohol"=>"a. Drink alcohol", "b_smoke_cigarettes_or_tobacco"=>"b. Smoke cigarettes or tobacco"), "multiple");
        $this->form->addElement("select", "q8_a_drink_alcohol_when_taken", $this->indent . "If alcohol was taken, when?:", array("0_before"=>"0 Before", "1_after"=>"1 After", "2_both"=>"2 Both","3_breastfeeding"=>"3 Breastfeeding", "not_answered"=>"Not Answered"), "multiple size='5'"  );
        $this->_selectMultipleElements[] = "q8_a_drink_alcohol_when_taken";
        $this->XINRegisterRule("q8_a_drink_alcohol_when_taken", array("q8_pregnancy_alcohol_tobacco{@}=={@}a_drink_alcohol"), "Please specify when alcohol was taken");
        $this->form->addElement("select", "q8_a1_drink_quantity", $this->indent . "How many drinks did you usually have in one week?:", array(""=>NULL, "0"=>"0", "1_2"=>"1-2", "3_more"=>"3 or more","not_answered"=>"Not Answered"));
        $this->XINRegisterRule("q8_a1_drink_quantity", array("q8_pregnancy_alcohol_tobacco{@}=={@}a_drink_alcohol"), "Please specify when alcohol was taken");
        $this->addNumericElement("q8_a2_drink_max_week", $this->indent . "What is the maximum number of drinks you had in one week?");
        $this->XINRegisterRule("q8_a2_drink_max_week", array("q8_pregnancy_alcohol_tobacco{@}=={@}a_drink_alcohol"), "Please specify when alcohol was taken");
        $this->form->addElement("select", "q8_b_tobacco_when_taken", $this->indent . "If tobacco was taken, when?:", array("0_before"=>"0 Before", "1_after"=>"1 After", "2_both"=>"2 Both","3_breastfeeding"=>"3 Breastfeeding", "not_answered"=>"Not Answered"), "multiple size='5'");
        $this->_selectMultipleElements[] = "q8_b_tobacco_when_taken";
        $this->XINRegisterRule("q8_b_tobacco_when_taken", array("q8_pregnancy_alcohol_tobacco{@}=={@}b_smoke_cigarettes_or_tobacco"), "Please specify when tobacco was taken");
        $this->form->addElement("select", "q8_b1_cigarette_perday", $this->indent . "How many cigarettes did you smoke per day?:", array(""=>NULL, "0"=>"0", "5_10"=>"5-10", "10_more"=>"10 or more","not_answered"=>"Not Answered"));
        $this->XINRegisterRule("q8_b1_cigarette_perday", array("q8_b1_cigarette_perday{@}=={@}NEVER_REQUIRED"));

        $this->form->addFormRule(array(&$this, 'Med_Rules'));

        $this->form->addElement('static', null, null);


        //9.
        $questionArray = array("a_marijuana_hashish"=>"a. Smoke marijuana or hashish (THC)",
        "b_cocaine_crack_free_base"=>"b. Use Cocaine, Crack or Free base",
        "c_heroin"=>"c. Use Heroin (includes speed balling)",
        "d_methadone"=>"d. Take Methadone",
        "e_amphet_stims"=>"e. Take Amphetamines or other stimulants",
        "f_ecstasy"=>"f. Take Ecstasy",
        "g_hallucinogens"=>"g. Take Hallucinogens",
        "h_inhalants"=>"h. Take inhalants that you sniff or breathe",
        "i_other"=>"i. Other (please specify)");

        $this->form->addElement("select", "q9_pregnancy_drugs", "9. In this pregnancy, did you do any of the following activities?",
        $questionArray, "multiple");

        $this->form->addElement("static", null, "Please specify when the drugs were taken");
        foreach($questionArray as $field=>$label) {
            $this->form->addElement("select", "q9_{$field}_when_taken", $this->indent . "If $label were taken, when?:", array( "0_before"=>"0 Before", "1_after"=>"1 After", "2_both"=>"2 Both", "3_breastfeeding"=>"3 Breastfeeding", "not_answered"=>"Not Answered"), "multiple size='5'");
            $this->XINRegisterRule("q9_{$field}_when_taken", array("q9_pregnancy_drugs{@}=={@}{$field}"), "Please specify when $label was taken");
            $this->_selectMultipleElements[] = "q9_{$field}_when_taken";
        }
        $this->addTextElement("q9_i_other_specify", $this->indent . $this->indent ."If other drugs, please specify", array("q9_pregnancy_drugs{@}=={@}i_other"), "If other drugs were taken, please specify");

        //Labour, Deliver and Newborn info
        //10.
        $this->form->addElement("header", null, "Labour, delivery and newborn information");
        $this->form->addElement("select", "q10_meds_induce_labor", "10. Were you given any medications to induce or start labor?", $this->yesNo);
        $this->form->addElement("select", "q10_spinal_anesthesia", "10b. Did you have a spinal or general anesthesia for the birth?", $this->yesNo);

        //11.
        $this->form->addElement("static", null, "11. How much did this child weigh at birth...");
        $this->addTextElement("q11_birth_weight_lbs", $this->indent . "...in pounds");
        $this->addTextElement("q11_birth_weight_ozs", $this->indent . "...and ounces");

        $this->form->addElement("static", null, "11b. What where this child's APGAR scores at...");
        $this->addTextElement("q11_apgar_1_minute", $this->indent . "...at 1 minute:");
        $this->addTextElement("q11_apgar_5_minute", $this->indent . "...at 5 minutes:");

        //12.
        $this->form->addElement("select", "q12_birth_interventions", "12. Did this child need any of the following during/after labor and delivery:", array("a_resuscitation_breathe_heart"=>"a. Resuscitation, help to breathe or get heart started",
        "b_forceps_vacuum"=>"b. Forceps/vacuum extraction",
        "c_meconium_stain"=>"c. Meconium stain in the amniotic fluid",
        "d_cord_prolapse"=>"d. Cord prolapse/around neck/knot",
        "e_nonvertex_presentation"=>"e. Nonvertex presentation (i.e., breech)",
        "f_trauma_on_delivery"=>"f. Trauma on delivery",
        "g_respiratory_distress"=>"g. Respiratory distress syndrome",
        "h_septicemia_meningitis"=>"h. Septicemia/meningitis",
        "i_hyperbilirubinemia"=>"i. Hyperbilirubinemia",
        "j_anemia_requiring_transfusion"=>"j. Anemia requiring transfusion",
        "k_irritable_floppy_infant_convulsions"=>"k. Irritable/floppy infant/convulsions",
        "l_clinical_dysmaturity"=>"l. Clinical dysmaturity",
        "m_difficulty_regulating_temperature"=>"m. Difficulty regulating temperature",
        "n_oxygen_treatment"=>"n. Oxygen treatment (>30 %)"
        ), "multiple");

        //13.
        $this->form->addElement("select", "q13_neonatal_icu", "13. Did this child stay in the neonatal intensive care unit?", $this->yesNo);
        $this->addTextElement("q13_neonatal_icu_reason", $this->indent . $this->indent . "If yes, why did the child stay at NICU", array("q13_neonatal_icu{@}=={@}1_yes"), "Please indicate the reason why child was in the Neonatal ICU");
        $this->addNumericElement("q13_neonatal_icu_days", $this->indent . $this->indent . "a. Number of days", array("q13_neonatal_icu{@}=={@}1_yes"), "Please indicate the number of days spent in the Neonatal ICU");
        $this->addNumericElement("q13_neonatal_icu_hours", $this->indent . $this->indent . "b. Number of hours", array("q13_neonatal_icu{@}=={@}1_yes"), "Please indicate the number of hours spent in the Neonatal ICU");

        //14.
        $this->form->addElement("static", null, "14. How many days or hours total did this child stay in the hospital?");
        $this->addNumericElement("q14_child_hospitalised_days", $this->indent . "Number of days:");
        $this->addNumericElement("q14_child_hospitalised_hours", $this->indent . "Number of hours:");
    }

    function _page5() {
        //15.
        $this->form->addElement("select", "q15_seizures_convulsions", "15. Has this child ever had seizures or convulsions?", $this->yesNo);
        //		$this->form->addElement("static", null);
        $this->form->addElement("select", "q15_a_first_seizure", $this->indent . "If yes, a. when was the first seizure?", array(null=>"", "0_first_month"=>"0. First month of life",
        "1_1-12_months"=>"1. 1-12 months (before 1st birthday)",
        "2_12-24 months"=>"2. 12-24 months (before 2nd birthday)",
        "3_2-5 years"=>"3. 2-5 years (before 5th birthday)",
        "4_>5 years"=>"4. >5 years",
        "not_answered"=>"Not Answered"));
        $this->XINRegisterRule("q15_a_first_seizure", array("q15_seizures_convulsions{@}=={@}1_yes"), "Please indicate when was the first seizure.");
        $this->form->addElement("select", "q15_b_now_seizures", $this->indent . "b. Does this child have seizures or convulsions now?", $this->yesNo);
        $this->XINRegisterRule("q15_b_now_seizures", array("q15_seizures_convulsions{@}=={@}1_yes"), "Please indicate if the seizures are current.");
        $this->form->addElement("select", "q15_c_fever_seizures", $this->indent . "c. Did the seizures only occur when this child had a fever?", $this->yesNo);
        $this->XINRegisterRule("q15_c_fever_seizures", array("q15_seizures_convulsions{@}=={@}1_yes"), "Please indicate if the seizures occur with a fever.");
        $this->form->addElement("select", "q15_d_seizure_medication", $this->indent . "d. Does this child now take medications to help control seizures?", $this->yesNo);
        $this->XINRegisterRule("q15_d_seizure_medication", array("q15_seizures_convulsions{@}=={@}1_yes"), "Please indicate if medications are taken.");

        //16.
        $questionArray = array("a_abnormal_brain_picture"=>"a. Had an abnormal picture of the brain",
        "b_meningitis_encephalitis"=>"b. Been hospitalized for meningitis or encephalitis",
        "c_lost_consciousness_head_injury"=>"c. Lost consciousness due to a head injury");
        $this->form->addElement("select", "q16_has_child_ever", "16. Has this child ever...", $questionArray, "multiple");

        $this->form->addElement("static", null, "If the child has lost consciousness...");
        $this->form->addElement("static", null, $this->indent . "At what age(s) did this child lose consciousness");
        for ($i = 1; $i <= 3; $i++) {
            $this->addTextElement("q16_unconscious_{$i}_years", $this->indent . $this->indent . "Unconscious {$i} years:", array("q16_has_child_ever{@}=={@}c_lost_consciousness_head_injury"), "Please indicate the age in years, or Not Answered");
            $this->addTextElement("q16_unconscious_{$i}_months", $this->indent . $this->indent .  "Unconscious {$i} months:", array("q16_has_child_ever{@}=={@}c_lost_consciousness_head_injury"), "Please indicate the age in months, or Not Answered");
        }

        //17.
        $this->form->addElement("select", "q17_birth_defects", "17. Did this child have any of the following birth defects?", array("a_cleft_lip_palate"=>"a. Cleft lip or palate", "b_Abnormal_shape_hands_etc"=>"b. Abnormal shape of hands, feet, arms or legs",
        "c_open_spine"=>"c. Open spine",
        "d_heart_defect"=>"d. Heart defect (please specify",
        "e_kidney_defect"=>"e. Kidney defect(please specify)",
        "f_other_defect"=>"f. Other defect(please specify)"), "multiple");
        $this->addTextElement("q17_d_heart_defect_specify", $this->indent . "If heart defect, please specify", array("q17_birth_defects{@}=={@}d_heart_defect"), "Please specify the heart defect.");
        $this->addTextElement("q17_e_kidney_defect_specify", $this->indent . "If kidney defect, please specify", array("q17_birth_defects{@}=={@}e_kidney_defect"), "Please specify the kidney defect.");
        $this->addTextElement("q17_f_other_defect_specify", $this->indent . "If other defect, please specify", array("q17_birth_defects{@}=={@}f_other_defect"), "Please specify the other defect.");

        //18.
        $this->form->addElement("select", "q18_other_chronic", "18. Does the child being evaluated today for autism have any other chronic medical problems?", $this->yesNo);
        $this->form->addElement("static", null, $this->indent . "If yes...");
        $abc = array("a"=>"1", "b"=>"2", "c"=>"3");
        foreach ($abc as $abcth=>$nth) {
            $this->addTextElement("q18_other_chronic_{$abcth}_specify", $this->indent . $this->indent . "Medical problem #{$nth}", array("q18_other_chronic{@}=={@}1_yes"), "Please indicate the medical problem.");
            $this->form->addElement("select", "q18_other_chronic_{$abcth}_hospitalized", $this->indent . $this->indent . "1. Was the child hospitalized for medical problem #{$nth}?", $this->yesNo);
            $this->XINRegisterRule("q18_other_chronic_{$abcth}_hospitalized", array("q18_other_chronic_{$abcth}_specify{@}!={@}"), "Please indicate whether hospitalization occured");
        }
    }

    function Med_Rules($values) {
        $errors = array();
        if( ($values['q8_pregnancy_alcohol_tobacco'] == 'b_smoke_cigarettes_or_tobacco') 
           || ($values['q8_b_tobacco_when_taken'] != null)
           && ($values['q8_b1_cigarette_perday']) == null) {
            
            $errors['q8_b1_cigarette_perday'] = 'Please specify number of cigarettes per day'; 
        }
        
        return $errors;
    }
    function firstVisitCheck($values) {
        $db = & Database::singleton();

        $cand = $db->pselectRow("SELECT c.CandID, s.Visit_label from session as s, flag as f, candidate c where f.sessionId = s.ID and
                                 s.CandID=c.CandID and f.CommentID=:cid", array('cid'=>$this->getCommentID())); 


        $candidate =& Candidate::singleton($cand['CandID']);

        $firstVisit = false;
        $vLabel = $db->pselectOne("SELECT Visit_label FROM session s JOIN candidate c 
                                   ON (c.CandID = s.CandID) WHERE c.CandID=:cid 
                                   ORDER BY Date_Visit", array('cid'=>$cand['CandID']));//get first visit for candidate 
        if($vLabel ==  $cand['Visit_label']){
            $firstVisit = true; //if current visit label is same as visit label returned must be first visit   
        }
        $current_visitlabel = $cand['Visit_label'];
        if($vLabel != $current_visitlabel && empty($values['followup_form_updated'])) { 
            $errors['followup_form_updated'] = "PLease indicate if there were changes";
        }

        return $errors;
    }

}
?>
