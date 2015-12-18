<?php

require_once 'HTML/QuickForm.php';
require_once 'HTML/QuickForm/Renderer/Array.php';

/*
INSERT INTO test_names VALUES ('', 'neuro_screen', 'Neuro Screener', '0', '1');

INSERT INTO instrument_subtests VALUES('', 'neuro_screen', 'neuro_screen_page1', 'Questions', 1);

-- Change for Zaphod
-- INSERT INTO test_battery VALUES ('', 'neuro_screen', '1050', '1140', 'Y', 'Visit', '3');
*/

class NDB_BVL_Instrument_neuro_screen extends NDB_BVL_Instrument
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
        $this->testName = "neuro_screen";           // test_names.Test_name
        $this->table = 'neuro_screen';              // name of database table corresponding to instrument
        // data keyed by commentID
        $this->commentID = $commentID;

        //The array of dates/timestamps to convert to database dates/timestamps
        //Any HTML_Quickform date elements must be listed here
        $this->dateTimeFields=array("Date_taken");

        //The array of selects with multiple answers allowed
        //Any HTML_Quickform multiple selects must be listed here
        $this->_selectMultipleElements = array();
         
        $db = & Database::singleton();
        $project = $db->pselectOne("SELECT c.ProjectID from neuro_screen n JOIN flag f 
                                    ON (f.CommentID= n.CommentID) JOIN session s ON (s.ID = f.SessionID) 
                                    JOIN candidate c ON (c.CandID=s.CandID) 
                                    WHERE n.CommentID=:cid", array('cid'=>$this->getCommentID()));
        // required fields for data entry completion status
        if($project == 2) {
            $this->_requiredElements = array('Examiner', 'visit', "q2_ptosis");
        } else {
            $this->_requiredElements = array('Examiner', 'visit', "q1_strabismus");
        }
	/**
	 * Array of column names to be ignored by the double data entry conflict detector.
	 */
	$this->_doubleDataEntryDiffIgnoreColumns = array('CommentID', 'UserID', 'Testdate',  'Window_Difference', 'Candidate_Age',
                            'Data_entry_completion_status',
							 'q1_strabismus_specify',
							 'q2_specify',
							 'q7_cleft_describe',
							 'q11_symmetrical_gait_abnormality_specify',
							 'q12_asymemtrical_gait_abnormality_specify',
							 'q13_tone_symmetrical_abnormality_specify',
							 'q14_tone_asymmetrical_abnormality_specify',
							 'q15_appearance_specify',
							 'q17_power_lower_limb_specify',
							 'q18_other_limb_hand_dysmorphic_describe',
							 'q19_other_physical_abnormalities',
							 'q23_adenoma_sebaceum_describe',
							 'q24_ash_leaf_macules_describe',
							 'q25_shagreen_patches_describe',
							 'q27_cafe_au_lait_spots_describe',
							 'q28_cutaneous_nodules_describe');
                             


        // setup the form
        $this->_setupForm();

        //column headers
        $this->localDefaults = array_merge($this->localDefaults, array("left"=>"LEFT", "right"=>"RIGHT"));
    
    }

    //If the instrument is not paged, remove the switch from the _setupForm method and add all the form Elements in this function.

    /**
    * method to build the HTML_Quickform object into a paged form
    *
    * @return void
    * @access private
    */
    function _setupForm(){
        if(preg_match("/neuro_screen(_page[0-9]+)/",$this->page,$matches)){
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
        // display test name
        $this->form->addElement('header', 'instrument_title', "Neuro Screener");

        // automatically adds examiner & date of administration
        $this->_addMetadataFields();
        $db = & Database::singleton();
        $record = $db->pselectRow("SELECT n.visit,c.ProjectID from neuro_screen n JOIN flag f ON (f.CommentID= n.CommentID)
                JOIN session s ON (s.ID = f.SessionID) join candidate c ON (c.CandID=s.CandID) 
                WHERE n.CommentID=:cid", array('cid'=>$this->getCommentID()));
        if($record['ProjectID'] == 2 ) {
         //which time version is being filled out?
        $this->form->addElement("select", "visit", "Visit", array(null=>"","3month"=>"3 month","6month"=>"6 month", 
                                                                  "9month"=>"9 month","12month"=>"12 month",  
                                                                  "15month"=>"15 month","24month"=>"24 month"));


        } else {
            //which time version is being filled out?
            $this->form->addElement("select", "visit", "Visit", array(null=>"","6month"=>"6 month", 
                        "12month"=>"12 month", 
                        "12month_nr"=>"12 month (new recruit)", 
                        "24month"=>"24 month"));

        }
        $this->form->addElement('static',null,'<br>');
        $this->form->addElement("textarea", "other_comments", "Comments about Validity:", array('cols'=>25, 'rows'=>4));
        $this->XINRegisterRule("other_comments", array("{other_comments}{@}=={@}NEVER_REQUIRED"));

    }

    function _page1(){
        
        $db = & Database::singleton();
        $record = $db->pselectRow("SELECT n.visit,c.ProjectID from neuro_screen n JOIN flag f ON (f.CommentID= n.CommentID)
                                   JOIN session s ON (s.ID = f.SessionID) join candidate c ON (c.CandID=s.CandID) 
                                   WHERE n.CommentID=:cid", array('cid'=>$this->getCommentID()));
        if($record['ProjectID'] == 2 ) {
           $this->generateQuestionsIBIS2($record['visit']);    
        } else {
            //header and some extra info
            $this->form->addElement("header", null, "IBIS Neuro Screener");
            $this->form->addElement("static", null, "Only fill in the questions appropriate to this time's version.");
            $this->form->addElement("static", null, "You may leave the rest blank.");
            $this->form->addElement("static", null, "<BR>");
            $this->form->addElement("static", null, "* If you experience problems with required question rules,");
            $this->form->addElement("static", null, "ensure that the visit is correctly filled in on the `Top` page.");
            $this->form->addElement("static", null, "<BR>");


            $this->form->addElement("select", "q1_strabismus", "1. Strabismus: Cover-uncover test", array(null=>"", "0_absent"=>"0 absent",
                        "1_covert"=>"1 covert (shown by test)",
                        "2_overt"=>"2 overt (observed without test)",
                        "7_can_t_tell"=>"7 can't tell about either",
                        "8_no_overt"=>"8 no overt, couldn't do covert",
                        "9_not_tested"=>"9 Not tested",
                        "not_answered"=>"Not Answered"));

            $this->addTextElement("q1_strabismus_specify", $this->indent . "Specify type:", array("q1_strabismus{@}=={@}1_covert|2_overt"));

            $this->form->addElement("select", "q2_ptosis", "2. Ptosis (droopy upper eyelid)", array(null=>"", "0_absent"=>"0 absent",
                        "1_doubtful"=>"1 doubtful",
                        "2_definite"=>"2 definite",
                        "8_suject_unable"=>"8 subject unable to carry out task",
                        "9_failure_to_test"=>"9 failure to test",
                        "not_answered"=>"Not Answered"));

            $this->addSelect("q2_ptosis_dropdown",$this->indent . "Choose R or L or Bilat.", 
                             array(null=>"",'left'=>'L','right'=>'R','bilat'=>'Bilat','none'=>'None','not_answered'=>'Not answered'));
            $this->addTextElement("q2_specify", $this->indent . "Specify R or L or Bilat.", array("q2_specify{@}=={@}NEVER_REQUIRED"));
            $this->form->addElement("select", "q3_epicanthus", "3. Epicanthus: Where upper and lower lids join the nose, point of union is", array(null=>"",
                        "0_normal"=>"0 normal",
                        "1_partly_covered"=>"1 partly covered",
                        "2_deeply_covered"=>"2 deeply covered",
                        "8_subject_unable"=>"8 subject unable to carry out task",
                        "9_failure_to_test"=>"9 failure to test",
                        "not_answered"=>"Not Answered"));

            $this->form->addElement("select", "q4_low_seated_ears", "4. Low Seated Ears", array(null=>"",
                        "0_normal"=>"0 normal (i.e. not lower)",
                        "1_lower_less_than_0.5_cm"=>"1 lower by less than or equal to 0.5 cm",
                        "2 lower_greater_than_0.5_cm"=>"2 lower by greater than 0.5 cm",
                        "8_subject_unable"=>"8 subject unable to carry out task",
                        "9_failure_to_test"=>"9 failure to test",
                        "not_answered"=>"Not Answered"));

            $this->form->addElement("select", "q5_adherent", "5. Adherent Ear Lobes: Lower edge of ears extend", array(null=>"",
                        "0_free_hanging_lobe"=>"0 free hanging lobe",
                        "1_adherent_lobe"=>"1 adherent lobe",
                        "8_subject_unable"=>"8 subject unable to carry out task",
                        "9_failure_to_test"=>"9 failure to test",
                        "not_answered"=>"Not Answered"));

            $this->form->addElement("select", "q6_ear_formation", "6. Ear Formation", array(null=>"",
                        "0_normal"=>"0 normal (i.e. soft and pliable ears)",
                        "1_abnormal"=>"1 abnormal (i.e. malformed or asymmetrical ears)",
                        "8_subject_unable"=>"8 subject unable to carry out task",
                        "9_failure_to_test"=>"9 failure to test",
                        "not_answered"=>"Not Answered"));

            $this->form->addElement("select", "q7_cleft_palate", "7. Cleft Palate/Lip", array(null=>"",
                        "0_absent"=>"0 absent",
                        "1_uncertain"=>"1 uncertain",
                        "2_present"=>"2 present (whether or not repaired)",
                        "8_subject_unable"=>"8 subject unable to carry out task",
                        "9_failure_to_test"=>"9 failure to test",
                        "not_answered"=>"Not Answered"));

            $this->addTextElement("q7_cleft_describe", $this->indent . "Describe:", array("q7_cleft_palate{@}=={@}1_uncertain|2_present"));

            $this->form->addElement("select", "q8_craniofacial_dysmorphic", "8. Other Craniofacial Dysmorphic Features", array(null=>"",
                        "0_absent"=>"0 absent",
                        "1_uncertain"=>"1 uncertain",
                        "2_present"=>"2 present",
                        "8_subject_unable"=>"8 subject unable to carry out task",
                        "9_failure_to_test"=>"9 failure to test",
                        "not_answered"=>"Not Answered"));

            $this->addTextElement("q8_craniofacial_dysmorphic_describe", $this->indent . "Describe:", array("q8_craniofacial_dysmorphic{@}=={@}1_uncertain|2_present"));

            $this->form->addElement("select", "q9_curved_fifth_finger", "9. Curved Fifth Finger", array(null=>"",
                        "0_normal"=>"0 normal",
                        "1_slightly_curved_inward"=>"1 slightly curved inward toward other fingers",
                        "2_markedly_curved_inward"=>"2 markedly curved inward toward other fingers",
                        "8_subject_unable"=>"8 subject unable to carry out task",
                        "9_failure_to_test"=>"9 failure to test",
                        "not_answered"=>"Not Answered"));

            $this->form->addElement("select", "q10_palmar_crease", "10. Palmar Crease", array(null=>"",
                        "0_normal"=>"0 normal",
                        "1_single_crease"=>"1 single transverse palmar crease",
                        "8_subject_unable to carry out task"=>"8 subject unable to carry out task",
                        "9_failure_to_test"=>"9 failure to test",
                        "not_answered"=>"Not Answered"));

            $this->form->addElement("select", "q11_symmetrical_gait_abnormality", "11. Symmetrical Gait Abnormality", array(null=>"",
                        "0_none"=>"0 none",
                        "1_uncertain_abnormality"=>"1 uncertain abnormality",
                        "2_definite_symmetrical_abnormality"=>"2 definite symmetrical abnormality",
                        "8_subject_unable"=>"8 subject unable to carry out task",
                        "9_failure_to_test"=>"9 failure to test",
                        "not_answered"=>"Not Answered"));

            $this->addTextElement("q11_symmetrical_gait_abnormality_specify", $this->indent . "Specify:", array("q11_symmetrical_gait_abnormality{@}=={@}1_uncertain_abnormality|2_definite_symmetrical_abnormality"));

            $this->form->addElement("select", "q12_asymmetrical_gait_abnormality", "12. Asymmetrical Gait Abnormality", array(null=>"",
                        "0_none"=>"0 none",
                        "1_uncertain_asymmetry"=>"1 uncertain asymmetry",
                        "2_definite_asymmetry"=>"2 definite asymmetry",
                        "8_subject_unable"=>"8 subject unable to carry out task",
                        "9_failure_to_test"=>"9 failure to test",
                        "not_answered"=>"Not Answered"));

            $this->addTextElement("q12_asymemtrical_gait_abnormality_specify", $this->indent . "Specify:", array("q12_asymmetrical_gait_abnormality{@}=={@}1_uncertain_asymmetry|2_definite_asymmetry"));

            $this->form->addElement("select", "q13_tone_symmetrical_abnormality", "13. Tone: Symmetrical Abnormality", array(null=>"",
                        "0_none"=>"0 none",
                        "1_uncertain"=>"1 uncertain",
                        "2_increased"=>"2 increased",
                        "3_decreased"=>"3 decreased",
                        "8_subject_unable"=>"8 subject unable to carry out task",
                        "9_failure_to_test"=>"9 failure to test",
                        "not_answered"=>"Not Answered"));

            $this->addTextElement("q13_tone_symmetrical_abnormality_specify", $this->indent . "Specify:");
            $this->XINRegisterRule("q13_tone_symmetrical_abnormality_specify", array("q13_tone_symmetrical_abnormality{@}=={@}2_increased|3_decreased"));

            $this->form->addElement("select", "q14_tone_asymmetrical_abnormality", "14. Tone: Asymmetrical Abnormality", array(null=>"",
                        "0_none"=>"0 none",
                        "1_uncertain"=>"1 uncertain",
                        "2_increased"=>"2 increased",
                        "3_decreased"=>"3 decreased",
                        "8_subject_unable"=>"8 subject unable to carry out task",
                        "9_failure_to_test"=>"9 failure to test",
                        "not_answered"=>"Not Answered"));

            $this->addTextElement("q14_tone_asymmetrical_abnormality_specify", $this->indent . "Specify:", array("q14_tone_asymmetrical_abnormality{@}=={@}2_increased|3_decreased"));
            //        $this->XINRegisterRule("14_tone_asymmetrical_abnormality_specify", array("14_tone_asymmetrical_abnormality{@}=={@}2_increased|3_decreased"));

            $this->form->addElement("select", "q15_appearance", "15. Appearance: Observe exposed arms...", array(null=>"",
                        "0_normal"=>"0 normal",
                        "1_uncertain_abnormality"=>"1 uncertain abnormality",
                        "2_definite_abnormality"=>"2 definite abnormality",
                        "8_subject_unable"=>"8 subject unable to carry out task",
                        "9_failure_to_test"=>"9 failure to test",
                        "not_answered"=>"Not Answered"));

            $this->addTextElement("q15_appearance_specify", $this->indent . "Specify:", array("q14_tone_asymmetrical_abnormality{@}=={@}1_uncertain_abnormality|2_definite_abnormality"));

            $this->form->addElement("select", "q16_power_upper_limb", "16. Power: Upper Limb: Get child to squeeze 2 fingers...", array(null=>"",
                        "0_normal"=>"0 normal",
                        "1_uncertain_mild_weakness"=>"1 uncertain mild weakness",
                        "2_unequivocal_weakness_or_asymmetry"=>"2 unequivocal weakness or asymmetry",
                        "8_subject_unable"=>"8 subject unable to carry out task",
                        "9_failure_to_test"=>"9 failure to test",
                        "not_answered"=>"Not Answered"));

            $this->addTextElement("q16_power_upper_limb_specify", $this->indent . "Specify:", array("q16_power_upper_limb{@}=={@}1_uncertain_mild_weakness|2_unequivocal_weakness_or_asymmetry"));

            $this->form->addElement("select", "q17_power_lower_limb", "17. Power: Lower Limb: Observe child walking, kicking, etc.", array(null=>"",
                        "0_normal"=>"0 normal",
                        "1_uncertain_mild_weakness"=>"1 uncertain mild weakness",
                        "2_unequivocal_weakness_or_asymmetry"=>"2 unequivocal weakness or asymmetry",
                        "8_subject_unable"=>"8 subject unable to carry out task",
                        "9_failure_to_test"=>"9 failure to test",
                        "not_answered"=>"Not Answered"));

            $this->addTextElement("q17_power_lower_limb_specify", $this->indent . "Specify:", array("q17_power_lower_limb{@}=={@}1_uncertain_mild_weakness|2_unequivocal_weakness_or_asymmetry"));

            $this->form->addElement("select", "q18_other_limb_hand_dysmorphic", "18. Other Limb/Hand/Feet Dysmorphic Features", array(null=>"",
                        "0_absent"=>"0 absent",
                        "1_uncertain"=>"1 uncertain",
                        "2_present"=>"2 present",
                        "8_subject_unable"=>"8 subject unable to carry out task",
                        "9_failure_to_test"=>"9 failure to test",
                        "not_answered"=>"Not Answered"));

            $this->addTextElement("q18_other_limb_hand_dysmorphic_describe", $this->indent . "Describe:", array("q18_other_limb_hand_dysmorphic{@}=={@}1_uncertain|2_present"));

            $this->addTextElement("q19_other_physical_abnormalities", "19. Other Physical Abnormalities Noted");

            $this->form->addElement("select", "q20_hyper_extensibility_of_joints", "20. Hyper extensibility of Joints: bend hand or fingers backward", array(null=>"",
                        "0_within_normal_range"=>"0 extensibility within normal range",
                        "1_somewhat_increased"=>"1 somewhat increased extensibility (uncertain abnormality)",
                        "2_definite_hyper_extensibility"=>"2 definite hyper extensibility",
                        "8_subject_unable"=>"8 subject unable to carry out task",
                        "9_failure_to_test"=>"9 failure to test",
                        "not_answered"=>"Not Answered"));

            $this->form->addElement("static", null, "21. MODIFIED EDINBURGH HANDEDNESS INVENTORY");
            $group[] = $this->form->createElement("static", "left");
            $group[] = $this->form->createElement("static", "right");
            $this->form->addGroup($group, 'left_right_group', $this->indent . "TASK", $this->_GUIDelimiter, false);
            unset($group);

            $group[] = $this->form->createElement("select", "q21_handedness_draw_or_write_left", null, array(null=>"", "+"=>"+", "+_+"=>"+ +", "+_+_+"=>"+ + +", "not_answered"=>"Not Answered"));
            $group[] = $this->form->createElement("select", "q21_handedness_draw_or_write_right", null, array(null=>"", "+"=>"+", "+_+"=>"+ +", "+_+_+"=>"+ + +", "not_answered"=>"Not Answered"));
            $this->form->addGroup($group, "q21_handedness_draw_or_write_group", $this->indent . "1. Draw or Write", $this->_GUIDelimiter, false);
            unset($group);

            $group[] = $this->form->createElement("select", "q21_handedness_throw_or_placing_left", null, array(null=>"", "+"=>"+", "+_+"=>"+ +", "+_+_+"=>"+ + +", "not_answered"=>"Not Answered"));
            $group[] = $this->form->createElement("select", "q21_handedness_throw_or_placing_right", null, array(null=>"", "+"=>"+", "+_+"=>"+ +", "+_+_+"=>"+ + +", "not_answered"=>"Not Answered"));
            $this->form->addGroup($group, "q21_handedness_throw_or_placing_group", $this->indent . "2. Throw or placing object", $this->_GUIDelimiter, false);
            unset($group);

            $group[] = $this->form->createElement("text", "q21_handedness_total_a_left", "Total a.");
            $group[] = $this->form->createElement("text", "q21_handedness_total_b_right", "Total b.");
            $this->form->addGroup($group, "q21_handedness_totals_group", $this->indent . "TOTAL", $this->_GUIDelimiter, false);
            unset($group);

            $this->form->addElement("static", null, "22. Measurements");
            //$this->form->addElement("static", null, "(Sometimes this is erroneously called #21)");
            $db =Database::singleton();
            $HMSRow = $db->pselectRow("SELECT hms.CommentID, hms.SessionID, s.CandID FROM flag ns left join flag hms ON (hms.Test_name='head_measurements_subject' AND hms.SessionID=ns.SessionID) LEFT JOIN session s ON (s.ID=hms.SessionID) WHERE ns.CommentID=:CID AND ns.CommentID NOT LIKE 'DDE%'",
                    array("CID" => $this->getCommentID()));
            $this->form->addElement("static", null, "<i>Note that this question has been moved to the <a href=\"?test_name=head_measurements_subject&candID=$HMSRow[CandID]&sessionID=$HMSRow[SessionID]&commentID=$HMSRow[CommentID]\">Head Measurements (Subject)</a> form</i>");
            /*
               $this->form->addElement("static", null, "Head Circumferences (cm):");
               $this->addNumericElement("q22_child_hc_cm", $this->indent . "a) Child:");
               $this->addNumericElement("q22_mother_hc_cm", $this->indent . "b) Mother:");
               $this->addNumericElement("q22_father_hc_cm", $this->indent . "c) Father:");

            //Some fields were added later on...
            $this->form->addElement("static", null, "Parental Height (cm):");
            $this->addNumericElement("q22_mother_height_cm", $this->indent . "d) Mother:");
            $this->addNumericElement("q22_father_height_cm", $this->indent . "e) Father:");

            $this->form->addElement("static", null, "Parental Weight (kg):");
            $this->addNumericElement("q22_mother_weight_kg", $this->indent . "f) Mother:");
            $this->addNumericElement("q22_father_weight_kg", $this->indent . "g) Father:");
             */

            $this->form->addElement("select", "q23_adenoma_sebaceum", "23. Adenoma Sebaceum", array(null=>"",
                        "0_absent"=>"0 absent",
                        "1_uncertain"=>"1 uncertain (few nodules or atypical distribution)",
                        "2_present"=>"2 present",
                        "8_subject_unable"=>"8 subject unable to carry out task",
                        "9_failure_to_test"=>"9 failure to test",
                        "not_answered"=>"Not Answered"));

            $this->addTextElement("q23_adenoma_sebaceum_describe", $this->indent . "Describe:", array("q23_adenoma_sebaceum{@}=={@}1_uncertain|2_present"));

            $this->form->addElement("select", "q24_ash_leaf_macules", "24. Ash Leaf Macules: flat, white, leaf shaped spots", array(null=>"",
                        "0_absent"=>"0 absent",
                        "1_uncertain"=>"1 uncertain",
                        "2_present"=>"2 present",
                        "8_subject_unable"=>"8 subject unable to carry out task",
                        "9_failure_to_test"=>"9 failure to test",
                        "not_answered"=>"Not Answered"));

            $this->addTextElement("q24_ash_leaf_macules_describe", $this->indent . "Describe:", array("q24_ash_leaf_macules{@}=={@}1_uncertain|2_present"));

            $this->form->addElement("select", "q25_shagreen_patches", "25. Shagreen Patches: patches of skin that resemble `untanned leather`", array(null=>"",
                        "0_absent"=>"0 absent",
                        "1_uncertain"=>"1 uncertain",
                        "2_present"=>"2 present",
                        "8_subject_unable"=>"8 subject unable to carry out task",
                        "9_failure_to_test"=>"9 failure to test",
                        "not_answered"=>"Not Answered"));

            $this->addTextElement("q25_shagreen_patches_describe", $this->indent . "Describe:", array("q25_shagreen_patches{@}=={@}1_uncertain|2_present"));

            //Question #26 removed.
            //        $this->form->addElement("select", "26_woods_lamp_examination", "26. Woods Lamp Examination", array(null=>"",
            $this->form->addElement("static", null, "26. Woods Lamp Examination - Question Removed");
            //        "0_normal"=>"0 normal",
            //        "1_uncertain"=>"1 uncertain",
            //        "2_abnormal"=>"2 abnormal",
            //        "8_subject_unable"=>"8 subject unable to carry out task",
            //        "9_failure_to_test"=>"9 failure to test",
            //        "not_answered"=>"Not Answered"));
            //
            //        $this->addTextElement("26_woods_lamp_examination_describe", $this->indent . "Describe:");

            $this->form->addElement("select", "q27_cafe_au_lait_spots", "27. Cafe au Lait spots: pale yellow/light brown spots", array(null=>"",
                        "0_absent"=>"0 absent",
                        "1_one_three_spots"=>"1 one-three spots (inclusive)",
                        "2_four_or_five_spots"=>"2 four or five spots",
                        "3_six_or_more_spots"=>"3 six or more spots (greater than 1.5 cm)",
                        "8_subject_unable"=>"8 subject unable to carry out task",
                        "9_failure_to_test"=>"9 failure to test",
                        "not_answered"=>"Not Answered"));

            $this->addTextElement("q27_cafe_au_lait_spots_describe", $this->indent . "Describe:", array("q27_cafe_au_lait_spots{@}=={@}1_one_three_spots|2_four_or_five_spots|3_six_or_more_spots"));

            $this->form->addElement("select", "q28_cutaneous_nodules", "28. Cutaneous/subcutaneous nodules: observe limbs and head", array(null=>"",
                        "0_absent"=>"0 absent",
                        "1_uncertain"=>"1 uncertain",
                        "2_one_or_more"=>"2 one or more",
                        "8_subject_unable"=>"8 subject unable to carry out task",
                        "9_failure_to_test"=>"9 failure to test",
                        "not_answered"=>"Not Answered"));

            $this->addTextElement("q28_cutaneous_nodules_describe", $this->indent . "Describe:", array("q28_cutaneous_nodules{@}=={@}1_uncertain|2_one_or_more"));

            $this->form->addElement("select", "q29_third_toe_longer", "29. Third toe longer than second", array(null=>"",
                        "0_normal"=>"0 normal",
                        "1_appears_equal"=>"1 appears equal in length to second toe",
                        "2_definitely_longer"=>"2 definitely longer than second toe",
                        "8_subject_unable"=>"8 subject unable to carry out task",
                        "9_failure_to_test"=>"9 failure to test",
                        "not_answered"=>"Not Answered"));

            $this->form->addElement("select", "q30_toe_spacing", "30. Toe spacing", array(null=>"",
                        "0_normal"=>"0 normal",
                        "1_big_gap_between_first_and_second"=>"1 big gap between first and second toes",
                        "2_partial_syndactylia_of_two_middle_toes"=>"2 partial syndactylia of two middle toes",
                        "8_subject_unable"=>"8 subject unable to carry out task",
                        "9_failure_to_test"=>"9 failure to test",
                        "not_answered"=>"Not Answered"));


            //Defining rules for each visit-specific version

            $allQuestions = array('q1_strabismus',
                    'q1_strabismus_specify',
                    //        '1_strabismus_specify_status',
                    'q2_ptosis',
                    'q2_specify',
                    //        '2_specify_status',
                    'q3_epicanthus',
                    'q4_low_seated_ears',
                    'q5_adherent',
                    'q6_ear_formation',
                    'q7_cleft_palate',
                    'q7_cleft_describe',
                    //        '7_cleft_describe_status',
                    'q8_craniofacial_dysmorphic',
                    'q8_craniofacial_dysmorphic_describe',
                    //        '8_craniofacial_dysmorphic_describe_status',
                    'q9_curved_fifth_finger',
                    'q10_palmar_crease',
                    'q11_symmetrical_gait_abnormality',
                    'q11_symmetrical_gait_abnormality_specify',
                    //        '11_symmetrical_gait_abnormality_specify_status',
                    'q12_asymmetrical_gait_abnormality',
                    'q12_asymemtrical_gait_abnormality_specify',
                    //        '12_asymemtrical_gait_abnormality_specify_status',
                    'q13_tone_symmetrical_abnormality',
                    'q13_tone_symmetrical_abnormality_specify',
                    //        '13_tone_symmetrical_abnormality_specify_status',
                    'q14_tone_asymmetrical_abnormality',
                    'q14_tone_asymmetrical_abnormality_specify',
                    //        '14_tone_asymmetrical_abnormality_specify_status',
                    'q15_appearance',
                    'q15_appearance_specify',
                    //        '15_appearance_specify_status',
                    'q16_power_upper_limb',
                    'q16_power_upper_limb_specify',
                    //        '16_power_upper_limb_specify_status',
                    'q17_power_lower_limb',
                    'q17_power_lower_limb_specify',
                    //        '17_power_lower_limb_specify_status',
                    'q18_other_limb_hand_dysmorphic',
                    'q18_other_limb_hand_dysmorphic_describe',
                    //        '18_other_limb_hand_dysmorphic_describe_status',
                    'q19_other_physical_abnormalities',
                    //        '19_other_physical_abnormalities_status',
                    'q20_hyper_extensibility_of_joints',
                    'q21_handedness_draw_or_write_left',
                    'q21_handedness_draw_or_write_right',
                    'q21_handedness_throw_or_placing_left',
                    'q21_handedness_throw_or_placing_right',
                    'q21_handedness_total_a_left',
                    'q21_handedness_total_b_right',
                    'q22_child_hc_cm',
                    //        '22_child_hc_cm_status',
                    'q22_mother_hc_cm',
                    //        '22_mother_hc_cm_status',
                    'q22_father_hc_cm',
                    //        '22_father_hc_cm_status',
                    "q22_mother_height_cm",
                    "q22_father_height_cm",        
                    "q22_mother_weight_kg",
                    "q22_father_weight_kg",
                    'q23_adenoma_sebaceum',
                    'q23_adenoma_sebaceum_describe',
                    //        '23_adenoma_sebaceum_describe_status',
                    'q24_ash_leaf_macules',
                    'q24_ash_leaf_macules_describe',
                    //        '24_ash_leaf_macules_describe_status',
                    'q25_shagreen_patches',
                    'q25_shagreen_patches_describe',
                    //        '25_shagreen_patches_describe_status',
                    //        '26_woods_lamp_examination',
                    //        '26_woods_lamp_examination_describe',
                    //        '26_woods_lamp_examination_describe_status',
                    'q27_cafe_au_lait_spots',
                    'q27_cafe_au_lait_spots_describe',
                    //        '27_cafe_au_lait_spots_describe_status',
                    'q28_cutaneous_nodules',
                    'q28_cutaneous_nodules_describe',
                    //        '28_cutaneous_nodules_describe_status',
                    'q29_third_toe_longer',
                    'q30_toe_spacing'
                        );

            //6month question numbers
            $_6month = array_merge(range(1, 10), range(13, 20), array(21), range(23, 30));

            //12month question numbers
            $_12month = array_merge(array(1, 2), range(11, 17), array(19, 20, 22, 27, 28));

            //12month new recruit numbers
            $_12month_nr = array_merge(range(1, 10), range(13, 20));

            //24month question numbers
            $_24month = array_merge(array(1, 2), range(11, 17), range(19, 21), array(22, 27, 28));

            // DB Object
            $db =& Database::singleton();

            //applicable visit version
            $query = "SELECT visit from neuro_screen WHERE CommentID = '".$this->getCommentID()."'";
            $visit = $db->selectOne($query);


            $requiredQuestions = array(); //moving it outside of the scope of the switch.  Seems to help.
            //which questions must be answered for this particular visit
            switch ($visit) {
                case "6month":
                    $requiredQuestions = $_6month;
                    break;
                case "12month":
                    $requiredQuestions = $_12month;
                    break;
                case "12month_nr":
                    $requiredQuestions = $_12month_nr;
                    break;
                case "24month":
                    $requiredQuestions = $_24month;
                    break;
            }

            foreach($allQuestions as $field) {
                //question number
                preg_match("/([0-9]+)/", $field, $matches);

                //is this question used in this version number?
                if(in_array($matches[1], $requiredQuestions)) {
                    //yes, required.  Do nothing - all questions are required by default
                } else {
                    //"un-require" other questions
                    $this->XINRegisterRule($field, array("q1_strabismus{@}=={@}Never_going_to_happen"));
                }
            }

            //hack to require question #21, because it uses QuickForm groups
            if(in_array(21, $requiredQuestions)) {
                $this->XINRegisterRule('q21_handedness_draw_or_write_left', array('q1_strabismus{@}!={@}Never_happening'), "This question is required.", "q21_handedness_draw_or_write_group");
                $this->XINRegisterRule('q21_handedness_draw_or_write_right', array('q1_strabismus{@}!={@}Never_happening'), "This question is required.", "q21_handedness_draw_or_write_group");

                $this->XINRegisterRule('q21_handedness_throw_or_placing_left', array('q1_strabismus{@}!={@}Never_happening'), "This question is required.", "q21_handedness_throw_or_placing_group");
                $this->XINRegisterRule('q21_handedness_throw_or_placing_right', array('q1_strabismus{@}!={@}Never_happening'), "This question is required.", "q21_handedness_throw_or_placing_group");

                $this->XINRegisterRule('q21_handedness_total_a_left', array('q1_strabismus{@}!={@}Never_happening'), "This question is required.", "q21_handedness_totals_group");
                $this->XINRegisterRule('q21_handedness_total_b_right', array('q1_strabismus{@}!={@}Never_happening'), "This question is required.", "q21_handedness_totals_group");
            }
        }
    
    } //end _page1()

    function generateQuestionsIBIS2($visit) {
            //header and some extra info
            $this->form->addElement("header", null, "IBIS Neuro Screener");
            $this->form->addElement("static", null, "Only fill in the questions appropriate to this time's version.");
            $this->form->addElement("static", null, "You may leave the rest blank.");
            $this->form->addElement("static", null, "<BR>");
            $this->form->addElement("static", null, "* If you experience problems with required question rules,");
            $this->form->addElement("static", null, "ensure that the visit is correctly filled in on the `Top` page.");
            $this->form->addElement("static", null, "<BR>");
            
            if($visit == '6month' || $visit == '9month' || $visit == '12month' || $visit == '15month' || $visit == '24month') {

                $this->form->addElement("select", "q1_strabismus", "1. Strabismus: Cover-uncover test", 
                            array(null=>"", "0_absent"=>"0 absent",
                            "1_covert"=>"1 covert (shown by test)",
                            "2_overt"=>"2 overt (observed without test)",
                            "7_can_t_tell"=>"7 can't tell about either",
                            "8_no_overt"=>"8 no overt, couldn't do covert",
                            "9_not_tested"=>"9 Not tested",
                            "not_answered"=>"Not Answered"));

                $this->addTextElement("q1_strabismus_specify", $this->indent . "Specify type:",
                                      array("q1_strabismus{@}=={@}1_covert|2_overt"));
            }
            $this->form->addElement("select", "q2_ptosis", "2. Ptosis (droopy upper eyelid)", array(null=>"", "0_absent"=>"0 absent",
                        "1_doubtful"=>"1 doubtful",
                        "2_definite"=>"2 definite",
                        "8_suject_unable"=>"8 subject unable to carry out task",
                        "9_failure_to_test"=>"9 failure to test",
                        "not_answered"=>"Not Answered"));

             $this->addSelect("q2_ptosis_dropdown",$this->indent . "Choose R or L or Bilat.",
                             array(null=>"",'left'=>'L','right'=>'R','bilat'=>'Bilat','none'=>'None','not_answered'=>'Not answered'));
            $this->addTextElement("q2_specify", $this->indent . "Specify R or L or Bilat.", array("q2_specify{@}=={@}NEVER_REQUIRED"));
            if($visit == '3month' || $visit == '6month') {
                $this->form->addElement("select", "q3_epicanthus", "3. Epicanthus: Where upper and lower lids join the nose, point of union is", array(null=>"",
                            "0_normal"=>"0 normal",
                            "1_partly_covered"=>"1 partly covered",
                            "2_deeply_covered"=>"2 deeply covered",
                            "8_subject_unable"=>"8 subject unable to carry out task",
                            "9_failure_to_test"=>"9 failure to test",
                            "not_answered"=>"Not Answered"));
            }

            $this->form->addElement("select", "q4_low_seated_ears", "4. Low Seated Ears", array(null=>"",
                        "0_normal"=>"0 normal (i.e. not lower)",
                        "1_lower_less_than_0.5_cm"=>"1 lower by less than or equal to 0.5 cm",
                        "2 lower_greater_than_0.5_cm"=>"2 lower by greater than 0.5 cm",
                        "8_subject_unable"=>"8 subject unable to carry out task",
                        "9_failure_to_test"=>"9 failure to test",
                        "not_answered"=>"Not Answered"));
            
            if($visit == '3month' || $visit == '6month') {

                $this->form->addElement("select", "q5_adherent", "5. Adherent Ear Lobes: Lower edge of ears extend", array(null=>"",
                            "0_free_hanging_lobe"=>"0 free hanging lobe",
                            "1_adherent_lobe"=>"1 adherent lobe",
                            "8_subject_unable"=>"8 subject unable to carry out task",
                            "9_failure_to_test"=>"9 failure to test",
                            "not_answered"=>"Not Answered"));

                $this->form->addElement("select", "q6_ear_formation", "6. Ear Formation", array(null=>"",
                            "0_normal"=>"0 normal (i.e. soft and pliable ears)",
                            "1_abnormal"=>"1 abnormal (i.e. malformed or asymmetrical ears)",
                            "8_subject_unable"=>"8 subject unable to carry out task",
                            "9_failure_to_test"=>"9 failure to test",
                            "not_answered"=>"Not Answered"));

                $this->form->addElement("select", "q7_cleft_palate", "7. Cleft Palate/Lip", array(null=>"",
                            "0_absent"=>"0 absent",
                            "1_uncertain"=>"1 uncertain",
                            "2_present"=>"2 present (whether or not repaired)",
                            "8_subject_unable"=>"8 subject unable to carry out task",
                            "9_failure_to_test"=>"9 failure to test",
                            "not_answered"=>"Not Answered"));

                $this->addTextElement("q7_cleft_describe", $this->indent . "Describe:", array("q7_cleft_palate{@}=={@}1_uncertain|2_present"));

            }
            $this->form->addElement("select", "q8_craniofacial_dysmorphic", "8. Other Craniofacial Dysmorphic Features", array(null=>"",
                        "0_absent"=>"0 absent",
                        "1_uncertain"=>"1 uncertain",
                        "2_present"=>"2 present",
                        "8_subject_unable"=>"8 subject unable to carry out task",
                        "9_failure_to_test"=>"9 failure to test",
                        "not_answered"=>"Not Answered"));

            $this->addTextElement("q8_craniofacial_dysmorphic_describe", $this->indent . "Describe:", array("q8_craniofacial_dysmorphic{@}=={@}1_uncertain|2_present"));

            $this->form->addElement("select", "q9_curved_fifth_finger", "9. Curved Fifth Finger", array(null=>"",
                        "0_normal"=>"0 normal",
                        "1_slightly_curved_inward"=>"1 slightly curved inward toward other fingers",
                        "2_markedly_curved_inward"=>"2 markedly curved inward toward other fingers",
                        "8_subject_unable"=>"8 subject unable to carry out task",
                        "9_failure_to_test"=>"9 failure to test",
                        "not_answered"=>"Not Answered"));

            $this->form->addElement("select", "q10_palmar_crease", "10. Palmar Crease", array(null=>"",
                        "0_normal"=>"0 normal",
                        "1_single_crease"=>"1 single transverse palmar crease",
                        "8_subject_unable to carry out task"=>"8 subject unable to carry out task",
                        "9_failure_to_test"=>"9 failure to test",
                        "not_answered"=>"Not Answered"));
            
            if($visit == '24month') {

                $this->form->addElement("select", "q11_symmetrical_gait_abnormality", "11. Symmetrical Gait Abnormality", array(null=>"",
                            "0_none"=>"0 none",
                            "1_uncertain_abnormality"=>"1 uncertain abnormality",
                            "2_definite_symmetrical_abnormality"=>"2 definite symmetrical abnormality",
                            "8_subject_unable"=>"8 subject unable to carry out task",
                            "9_failure_to_test"=>"9 failure to test",
                            "not_answered"=>"Not Answered"));

                $this->addTextElement("q11_symmetrical_gait_abnormality_specify", $this->indent . "Specify:", array("q11_symmetrical_gait_abnormality{@}=={@}1_uncertain_abnormality|2_definite_symmetrical_abnormality"));

                $this->form->addElement("select", "q12_asymmetrical_gait_abnormality", "12. Asymmetrical Gait Abnormality", array(null=>"",
                            "0_none"=>"0 none",
                            "1_uncertain_asymmetry"=>"1 uncertain asymmetry",
                            "2_definite_asymmetry"=>"2 definite asymmetry",
                            "8_subject_unable"=>"8 subject unable to carry out task",
                            "9_failure_to_test"=>"9 failure to test",
                            "not_answered"=>"Not Answered"));

                $this->addTextElement("q12_asymemtrical_gait_abnormality_specify", $this->indent . "Specify:", array("q12_asymmetrical_gait_abnormality{@}=={@}1_uncertain_asymmetry|2_definite_asymmetry"));
            }
            $this->form->addElement("select", "q13_tone_symmetrical_abnormality", "13. Tone: Symmetrical Abnormality", array(null=>"",
                        "0_none"=>"0 none",
                        "1_uncertain"=>"1 uncertain",
                        "2_increased"=>"2 increased",
                        "3_decreased"=>"3 decreased",
                        "8_subject_unable"=>"8 subject unable to carry out task",
                        "9_failure_to_test"=>"9 failure to test",
                        "not_answered"=>"Not Answered"));

            $this->addTextElement("q13_tone_symmetrical_abnormality_specify", $this->indent . "Specify:");
            $this->XINRegisterRule("q13_tone_symmetrical_abnormality_specify", array("q13_tone_symmetrical_abnormality{@}=={@}2_increased|3_decreased"));

            $this->form->addElement("select", "q14_tone_asymmetrical_abnormality", "14. Tone: Asymmetrical Abnormality", array(null=>"",
                        "0_none"=>"0 none",
                        "1_uncertain"=>"1 uncertain",
                        "2_increased"=>"2 increased",
                        "3_decreased"=>"3 decreased",
                        "8_subject_unable"=>"8 subject unable to carry out task",
                        "9_failure_to_test"=>"9 failure to test",
                        "not_answered"=>"Not Answered"));

            $this->addTextElement("q14_tone_asymmetrical_abnormality_specify", $this->indent . "Specify:", array("q14_tone_asymmetrical_abnormality{@}=={@}2_increased|3_decreased"));
            //        $this->XINRegisterRule("14_tone_asymmetrical_abnormality_specify", array("14_tone_asymmetrical_abnormality{@}=={@}2_increased|3_decreased"));

            $this->form->addElement("select", "q15_appearance", "15. Appearance: Observe exposed arms...", array(null=>"",
                        "0_normal"=>"0 normal",
                        "1_uncertain_abnormality"=>"1 uncertain abnormality",
                        "2_definite_abnormality"=>"2 definite abnormality",
                        "8_subject_unable"=>"8 subject unable to carry out task",
                        "9_failure_to_test"=>"9 failure to test",
                        "not_answered"=>"Not Answered"));

            $this->addTextElement("q15_appearance_specify", $this->indent . "Specify:", array("q14_tone_asymmetrical_abnormality{@}=={@}1_uncertain_abnormality|2_definite_abnormality"));
            
            if($visit != '3month') {

                $this->form->addElement("select", "q16_power_upper_limb", "16. Power: Upper Limb: Get child to squeeze 2 fingers...", array(null=>"",
                            "0_normal"=>"0 normal",
                            "1_uncertain_mild_weakness"=>"1 uncertain mild weakness",
                            "2_unequivocal_weakness_or_asymmetry"=>"2 unequivocal weakness or asymmetry",
                            "8_subject_unable"=>"8 subject unable to carry out task",
                            "9_failure_to_test"=>"9 failure to test",
                            "not_answered"=>"Not Answered"));

                $this->addTextElement("q16_power_upper_limb_specify", $this->indent . "Specify:", array("q16_power_upper_limb{@}=={@}1_uncertain_mild_weakness|2_unequivocal_weakness_or_asymmetry"));

                $this->form->addElement("select", "q17_power_lower_limb", "17. Power: Lower Limb: Observe child walking, kicking, etc.", array(null=>"",
                            "0_normal"=>"0 normal",
                            "1_uncertain_mild_weakness"=>"1 uncertain mild weakness",
                            "2_unequivocal_weakness_or_asymmetry"=>"2 unequivocal weakness or asymmetry",
                            "8_subject_unable"=>"8 subject unable to carry out task",
                            "9_failure_to_test"=>"9 failure to test",
                            "not_answered"=>"Not Answered"));

                $this->addTextElement("q17_power_lower_limb_specify", $this->indent . "Specify:", array("q17_power_lower_limb{@}=={@}1_uncertain_mild_weakness|2_unequivocal_weakness_or_asymmetry"));
            }
            
            $this->form->addElement("select", "q18_other_limb_hand_dysmorphic", "18. Other Limb/Hand/Feet Dysmorphic Features", array(null=>"",
                        "0_absent"=>"0 absent",
                        "1_uncertain"=>"1 uncertain",
                        "2_present"=>"2 present",
                        "8_subject_unable"=>"8 subject unable to carry out task",
                        "9_failure_to_test"=>"9 failure to test",
                        "not_answered"=>"Not Answered"));

            $this->addTextElement("q18_other_limb_hand_dysmorphic_describe", $this->indent . "Describe:", array("q18_other_limb_hand_dysmorphic{@}=={@}1_uncertain|2_present"));

            $this->addTextElement("q19_other_physical_abnormalities", "19. Other Physical Abnormalities Noted");
            
            if($visit != '3month') {

                $this->form->addElement("select", "q20_hyper_extensibility_of_joints", "20. Hyper extensibility of Joints: bend hand or fingers backward", array(null=>"",
                            "0_within_normal_range"=>"0 extensibility within normal range",
                            "1_somewhat_increased"=>"1 somewhat increased extensibility (uncertain abnormality)",
                            "2_definite_hyper_extensibility"=>"2 definite hyper extensibility",
                            "8_subject_unable"=>"8 subject unable to carry out task",
                            "9_failure_to_test"=>"9 failure to test",
                            "not_answered"=>"Not Answered"));
            }

            $this->form->addElement("static", null, "22. Measurements");
            //$this->form->addElement("static", null, "(Sometimes this is erroneously called #21)");
            $db =Database::singleton();
            $HMSRow = $db->pselectRow("SELECT hms.CommentID, hms.SessionID, s.CandID FROM flag ns left join flag hms ON (hms.Test_name='head_measurements_subject' AND hms.SessionID=ns.SessionID) LEFT JOIN session s ON (s.ID=hms.SessionID) WHERE ns.CommentID=:CID AND ns.CommentID NOT LIKE 'DDE%'",
                    array("CID" => $this->getCommentID()));
            $this->form->addElement("static", null, "<i>Note that this question has been moved to the <a href=\"?test_name=head_measurements_subject&candID=$HMSRow[CandID]&sessionID=$HMSRow[SessionID]&commentID=$HMSRow[CommentID]\">Head Measurements (Subject)</a> form</i>");
            /*
               $this->form->addElement("static", null, "Head Circumferences (cm):");
               $this->addNumericElement("q22_child_hc_cm", $this->indent . "a) Child:");
               $this->addNumericElement("q22_mother_hc_cm", $this->indent . "b) Mother:");
               $this->addNumericElement("q22_father_hc_cm", $this->indent . "c) Father:");

            //Some fields were added later on...
            $this->form->addElement("static", null, "Parental Height (cm):");
            $this->addNumericElement("q22_mother_height_cm", $this->indent . "d) Mother:");
            $this->addNumericElement("q22_father_height_cm", $this->indent . "e) Father:");

            $this->form->addElement("static", null, "Parental Weight (kg):");
            $this->addNumericElement("q22_mother_weight_kg", $this->indent . "f) Mother:");
            $this->addNumericElement("q22_father_weight_kg", $this->indent . "g) Father:");
             */

            $this->form->addElement("select", "q23_adenoma_sebaceum", "23. Adenoma Sebaceum", array(null=>"",
                        "0_absent"=>"0 absent",
                        "1_uncertain"=>"1 uncertain (few nodules or atypical distribution)",
                        "2_present"=>"2 present",
                        "8_subject_unable"=>"8 subject unable to carry out task",
                        "9_failure_to_test"=>"9 failure to test",
                        "not_answered"=>"Not Answered"));

            $this->addTextElement("q23_adenoma_sebaceum_describe", $this->indent . "Describe:", array("q23_adenoma_sebaceum{@}=={@}1_uncertain|2_present"));

            $this->form->addElement("select", "q24_ash_leaf_macules", "24. Ash Leaf Macules: flat, white, leaf shaped spots", array(null=>"",
                        "0_absent"=>"0 absent",
                        "1_uncertain"=>"1 uncertain",
                        "2_present"=>"2 present",
                        "8_subject_unable"=>"8 subject unable to carry out task",
                        "9_failure_to_test"=>"9 failure to test",
                        "not_answered"=>"Not Answered"));

            $this->addTextElement("q24_ash_leaf_macules_describe", $this->indent . "Describe:", array("q24_ash_leaf_macules{@}=={@}1_uncertain|2_present"));

            $this->form->addElement("select", "q25_shagreen_patches", "25. Shagreen Patches: patches of skin that resemble `untanned leather`", array(null=>"",
                        "0_absent"=>"0 absent",
                        "1_uncertain"=>"1 uncertain",
                        "2_present"=>"2 present",
                        "8_subject_unable"=>"8 subject unable to carry out task",
                        "9_failure_to_test"=>"9 failure to test",
                        "not_answered"=>"Not Answered"));

            $this->addTextElement("q25_shagreen_patches_describe", $this->indent . "Describe:", array("q25_shagreen_patches{@}=={@}1_uncertain|2_present"));

            //Question #26 removed.
            //        $this->form->addElement("select", "26_woods_lamp_examination", "26. Woods Lamp Examination", array(null=>"",
            $this->form->addElement("static", null, "26. Woods Lamp Examination - Question Removed");
            //        "0_normal"=>"0 normal",
            //        "1_uncertain"=>"1 uncertain",
            //        "2_abnormal"=>"2 abnormal",
            //        "8_subject_unable"=>"8 subject unable to carry out task",
            //        "9_failure_to_test"=>"9 failure to test",
            //        "not_answered"=>"Not Answered"));
            //
            //        $this->addTextElement("26_woods_lamp_examination_describe", $this->indent . "Describe:");

            $this->form->addElement("select", "q27_cafe_au_lait_spots", "27. Cafe au Lait spots: pale yellow/light brown spots", array(null=>"",
                        "0_absent"=>"0 absent",
                        "1_one_three_spots"=>"1 one-three spots (inclusive)",
                        "2_four_or_five_spots"=>"2 four or five spots",
                        "3_six_or_more_spots"=>"3 six or more spots (greater than 1.5 cm)",
                        "8_subject_unable"=>"8 subject unable to carry out task",
                        "9_failure_to_test"=>"9 failure to test",
                        "not_answered"=>"Not Answered"));

            $this->addTextElement("q27_cafe_au_lait_spots_describe", $this->indent . "Describe:", array("q27_cafe_au_lait_spots{@}=={@}1_one_three_spots|2_four_or_five_spots|3_six_or_more_spots"));

            $this->form->addElement("select", "q28_cutaneous_nodules", "28. Cutaneous/subcutaneous nodules: observe limbs and head", array(null=>"",
                        "0_absent"=>"0 absent",
                        "1_uncertain"=>"1 uncertain",
                        "2_one_or_more"=>"2 one or more",
                        "8_subject_unable"=>"8 subject unable to carry out task",
                        "9_failure_to_test"=>"9 failure to test",
                        "not_answered"=>"Not Answered"));

            $this->addTextElement("q28_cutaneous_nodules_describe", $this->indent . "Describe:", array("q28_cutaneous_nodules{@}=={@}1_uncertain|2_one_or_more"));

            $this->form->addElement("select", "q29_third_toe_longer", "29. Third toe longer than second", array(null=>"",
                        "0_normal"=>"0 normal",
                        "1_appears_equal"=>"1 appears equal in length to second toe",
                        "2_definitely_longer"=>"2 definitely longer than second toe",
                        "8_subject_unable"=>"8 subject unable to carry out task",
                        "9_failure_to_test"=>"9 failure to test",
                        "not_answered"=>"Not Answered"));

            $this->form->addElement("select", "q30_toe_spacing", "30. Toe spacing", array(null=>"",
                        "0_normal"=>"0 normal",
                        "1_big_gap_between_first_and_second"=>"1 big gap between first and second toes",
                        "2_partial_syndactylia_of_two_middle_toes"=>"2 partial syndactylia of two middle toes",
                        "8_subject_unable"=>"8 subject unable to carry out task",
                        "9_failure_to_test"=>"9 failure to test",
                        "not_answered"=>"Not Answered"));


            //Defining rules for each visit-specific version

            $allQuestions = array('q1_strabismus',
                    'q1_strabismus_specify',
                    //        '1_strabismus_specify_status',
                    'q2_ptosis',
                    'q2_specify',
                    //        '2_specify_status',
                    'q3_epicanthus',
                    'q4_low_seated_ears',
                    'q5_adherent',
                    'q6_ear_formation',
                    'q7_cleft_palate',
                    'q7_cleft_describe',
                    //        '7_cleft_describe_status',
                    'q8_craniofacial_dysmorphic',
                    'q8_craniofacial_dysmorphic_describe',
                    //        '8_craniofacial_dysmorphic_describe_status',
                    'q9_curved_fifth_finger',
                    'q10_palmar_crease',
                    'q11_symmetrical_gait_abnormality',
                    'q11_symmetrical_gait_abnormality_specify',
                    //        '11_symmetrical_gait_abnormality_specify_status',
                    'q12_asymmetrical_gait_abnormality',
                    'q12_asymemtrical_gait_abnormality_specify',
                    //        '12_asymemtrical_gait_abnormality_specify_status',
                    'q13_tone_symmetrical_abnormality',
                    'q13_tone_symmetrical_abnormality_specify',
                    //        '13_tone_symmetrical_abnormality_specify_status',
                    'q14_tone_asymmetrical_abnormality',
                    'q14_tone_asymmetrical_abnormality_specify',
                    //        '14_tone_asymmetrical_abnormality_specify_status',
                    'q15_appearance',
                    'q15_appearance_specify',
                    //        '15_appearance_specify_status',
                    'q16_power_upper_limb',
                    'q16_power_upper_limb_specify',
                    //        '16_power_upper_limb_specify_status',
                    'q17_power_lower_limb',
                    'q17_power_lower_limb_specify',
                    //        '17_power_lower_limb_specify_status',
                    'q18_other_limb_hand_dysmorphic',
                    'q18_other_limb_hand_dysmorphic_describe',
                    //        '18_other_limb_hand_dysmorphic_describe_status',
                    'q19_other_physical_abnormalities',
                    //        '19_other_physical_abnormalities_status',
                    'q20_hyper_extensibility_of_joints',
                    'q22_child_hc_cm',
                    //        '22_child_hc_cm_status',
                    'q22_mother_hc_cm',
                    //        '22_mother_hc_cm_status',
                    'q22_father_hc_cm',
                    //        '22_father_hc_cm_status',
                    "q22_mother_height_cm",
                    "q22_father_height_cm",        
                    "q22_mother_weight_kg",
                    "q22_father_weight_kg",
                    'q23_adenoma_sebaceum',
                    'q23_adenoma_sebaceum_describe',
                    //        '23_adenoma_sebaceum_describe_status',
                    'q24_ash_leaf_macules',
                    'q24_ash_leaf_macules_describe',
                    //        '24_ash_leaf_macules_describe_status',
                    'q25_shagreen_patches',
                    'q25_shagreen_patches_describe',
                    //        '25_shagreen_patches_describe_status',
                    //        '26_woods_lamp_examination',
                    //        '26_woods_lamp_examination_describe',
                    //        '26_woods_lamp_examination_describe_status',
                    'q27_cafe_au_lait_spots',
                    'q27_cafe_au_lait_spots_describe',
                    //        '27_cafe_au_lait_spots_describe_status',
                    'q28_cutaneous_nodules',
                    'q28_cutaneous_nodules_describe',
                    //        '28_cutaneous_nodules_describe_status',
                    'q29_third_toe_longer',
                    'q30_toe_spacing'
                        );
            //3month question numbers
            $_3month = array_merge(range(2, 10), range(13, 19), range(23, 30));

            //6month question numbers
            $_6month = array_merge(range(1, 10), range(13, 20), range(23, 30));

            //9month question numbers
            $_9month = array_merge(array(1, 2), array(4), range(8, 10), range(13, 20) ,array(23,24,25,27,28,29,30) );

            //12month question numbers
            $_12month = array_merge(array(1, 2), array(4), range(8, 10), range(13, 20) ,array(23,24,25,27,28,29,30) );
            
            //12month question numbers
            $_15month = array_merge(array(1, 2), array(4), range(8, 10), range(13, 20) ,array(23,24,25,27,28,29,30) );

            //24month question numbers
            $_24month = array_merge(array(1, 2), array(4), range(8, 20) ,array(23,24,25,27,28,29,30) );

            // DB Object
            $db =& Database::singleton();

            //applicable visit version
            $query = "SELECT visit from neuro_screen WHERE CommentID = '".$this->getCommentID()."'";
            $visit = $db->selectOne($query);


            $requiredQuestions = array(); //moving it outside of the scope of the switch.  Seems to help.
            //which questions must be answered for this particular visit
            switch ($visit) {
                case "3month":
                    $requiredQuestions = $_3month;
                    break;
                case "6month":
                    $requiredQuestions = $_6month;
                    break;
                case "9month":
                    $requiredQuestions = $_9month;
                    break;
                case "12month":
                    $requiredQuestions = $_12month;
                    break;
                case "15month":
                    $requiredQuestions = $_15month;
                    break;
                case "24month":
                    $requiredQuestions = $_24month;
                    break;
            }

            foreach($allQuestions as $field) {
                //question number
                preg_match("/([0-9]+)/", $field, $matches);

                //is this question used in this version number?
                if(in_array($matches[1], $requiredQuestions)) {
                    //yes, required.  Do nothing - all questions are required by default
                } else {
                    //"un-require" other questions
                    $this->XINRegisterRule($field, array("q1_strabismus{@}=={@}Never_going_to_happen"));
                }
            }
               
        
    }

}
?>
