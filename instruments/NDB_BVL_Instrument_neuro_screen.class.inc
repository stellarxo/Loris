<?php

/*
INSERT INTO test_names VALUES ('', 'neuro_screen', 'Neuro Screen', '0', '1');

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

        // required fields for data entry completion status
        $this->_requiredElements = array('Examiner', 'visit', "1_strabismus");

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
        if(ereg("neuro_screen(_page[0-9]+)",$this->page,$matches)){
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
        $this->form->addElement('header', 'instrument_title', "Neuro Screener");

        // automatically adds examiner & date of administration
        $this->_addMetadataFields();

        //which time version is being filled out?
        $this->form->addElement("select", "visit", "Visit", array(null=>"", "6month"=>"6 month", "12month"=>"12 month", "24month"=>"24 month", "not_answered"=>"Not Answered"));
    }

    function _page1(){

        //header and some extra info
        $this->form->addElement("header", null, "IBIS Neuro Screener");
        $this->form->addElement("static", null, "* If you experience problems with required question rules,");
        $this->form->addElement("static", null, "ensure that the visit is correctly filled in on the `Top` page.");
        $this->form->addElement("static", null, "<BR>");
        
        $this->form->addElement("select", "1_strabismus", "1. Strabismus: Cover-uncover test", array(null=>"", "0_absent"=>"0 absent",
        "1_covert"=>"1 covert (shown by test)",
        "2_overt"=>"2 overt (observed without test)",
        "7_can_t_tell"=>"7 can't tell about either",
        "8_no_overt"=>"8 no overt, couldn't do covert",
        "9_not_tested"=>"9 Not tested",
        "not_answered"=>"Not Answered"));

        $this->addTextElement("1_strabismus_specify", $this->indent . "Specify type:");

        $this->form->addElement("select", "2_ptosis", "2. Ptosis (droopy upper eyelid)", array(null=>"", "0_absent"=>"0 absent",
        "1_doubtful"=>"1 doubtful",
        "2 definite"=>"2 definite",
        "8_suject_unable"=>"8 subject unable to carry out task",
        "9_failure_to_test"=>"9 failure to test",
        "not_answered"=>"Not Answered"));

        $this->addTextElement("2_specify", $this->indent . "Specify R or L or Bilat.");

        $this->form->addElement("select", "3_epicanthus", "3. Epicanthus: Where upper and lower lids join the nose, point of union is", array(null=>"",
        "0_normal"=>"0 normal",
        "1_partly_covered"=>"1 partly covered",
        "2_deeply_covered"=>"2 deeply covered",
        "8_subject_unable"=>"8 subject unable to carry out task",
        "9_failure_to_test"=>"9 failure to test",
        "not_answered"=>"Not Answered"));

        $this->form->addElement("select", "4_low_seated_ears", "4. Low Seated Ears", array(null=>"",
        "0_normal"=>"0 normal (i.e. not lower)",
        "1_lower_less_than_0.5_cm"=>"1 lower by less than or equal to 0.5 cm",
        "2 lower_greater_than_0.5_cm"=>"2 lower by greater than 0.5 cm",
        "8_subject_unable"=>"8 subject unable to carry out task",
        "9_failure_to_test"=>"9 failure to test",
        "not_answered"=>"Not Answered"));

        $this->form->addElement("select", "5_adherent", "5. Adherent Ear Lobes: Lower edge of ears extend", array(null=>"",
        "0_free_hanging_lobe"=>"0 free hanging lobe",
        "1_adherent_lobe"=>"1 adherent lobe",
        "8_subject_unable"=>"8 subject unable to carry out task",
        "9_failure_to_test"=>"9 failure to test",
        "not_answered"=>"Not Answered"));

        $this->form->addElement("select", "6_ear_formation", "6. Ear Formation", array(null=>"",
        "0_normal"=>"0 normal (i.e. soft and pliable ears)",
        "1_abnormal"=>"1 abnormal (i.e. malformed or asymmetrical ears)",
        "8_subject_unable"=>"8 subject unable to carry out task",
        "9_failure_to_test"=>"9 failure to test",
        "not_answered"=>"Not Answered"));

        $this->form->addElement("select", "7_cleft_palate", "7. Cleft Palate/Lip", array(null=>"",
        "0_absent"=>"0 absent",
        "1_uncertain"=>"1 uncertain",
        "2_present"=>"2 present (whether or not repaired)",
        "8_subject_unable"=>"8 subject unable to carry out task",
        "9_failure_to_test"=>"9 failure to test",
        "not_answered"=>"Not Answered"));

        $this->addTextElement("7_cleft_describe", $this->indent . "Describe:");

        $this->form->addElement("select", "8_craniofacial_dysmorphic", "8. Other Craniofacial Dysmorphic Features", array(null=>"",
        "0_absent"=>"0 absent",
        "1_uncertain"=>"1 uncertain",
        "2_present"=>"2 present",
        "8_subject_unable"=>"8 subject unable to carry out task",
        "9_failure_to_test"=>"9 failure to test",
        "not_answered"=>"Not Answered"));

        $this->addTextElement("8_craniofacial_dysmorphic_describe", $this->indent . "Describe:");

        $this->form->addElement("select", "9_curved_fifth_finger", "9. Curved Fifth Finger", array(null=>"",
        "0_normal"=>"0 normal",
        "1_slightly_curved_inward"=>"1 slightly curved inward toward other fingers",
        "2_markedly_curved_inward"=>"2 markedly curved inward toward other fingers",
        "8_subject_unable"=>"8 subject unable to carry out task",
        "9_failure_to_test"=>"9 failure to test",
        "not_answered"=>"Not Answered"));

        $this->form->addElement("select", "10_palmar_crease", "10. Palmar Crease", array(null=>"",
        "0_normal"=>"0 normal",
        "1_single_crease"=>"1 single transverse palmar crease",
        "8_subject_unable to carry out task"=>"8 subject unable to carry out task",
        "9_failure_to_test"=>"9 failure to test",
        "not_answered"=>"Not Answered"));

        $this->form->addElement("select", "11_symmetrical_gait_abnormality", "11. Symmetrical Gait Abnormality", array(null=>"",
        "0_none"=>"0 none",
        "1_uncertain_abnormality"=>"1 uncertain abnormality",
        "2_definite_symmetrical_abnormality"=>"2 definite symmetrical abnormality",
        "8_subject_unable"=>"8 subject unable to carry out task",
        "9_failure_to_test"=>"9 failure to test",
        "not_answered"=>"Not Answered"));

        $this->addTextElement("11_symmetrical_gait_abnormality_specify", $this->indent . "Specify:");

        $this->form->addElement("select", "12_asymmetrical_gait_abnormality", "12. Asymmetrical Gait Abnormality", array(null=>"",
        "0_none"=>"0 none",
        "1_uncertain_asymmetry"=>"1 uncertain asymmetry",
        "2_definite_asymmetry"=>"2 definite asymmetry",
        "8_subject_unable"=>"8 subject unable to carry out task",
        "9_failure_to_test"=>"9 failure to test",
        "not_answered"=>"Not Answered"));

        $this->addTextElement("12_asymemtrical_gait_abnormality_specify", $this->indent . "Specify:");

        $this->form->addElement("select", "13_tone_symmetrical_abnormality", "13. Tone: Symmetrical Abnormality", array(null=>"",
        "0_none"=>"0 none",
        "1_uncertain"=>"1 uncertain",
        "2_increased"=>"2 increased",
        "3_decreased"=>"3 decreased",
        "8_subject_unable"=>"8 subject unable to carry out task",
        "9_failure_to_test"=>"9 failure to test",
        "not_answered"=>"Not Answered"));

        $this->addTextElement("13_tone_symmetrical_abnormality_specify", $this->indent . "Specify:");
        $this->XINRegisterRule("13_tone_symmetrical_abnormality_specify", array("13_tone_symmetrical_abnormality{@}=={@}2_increased|3_decreased"));

        $this->form->addElement("select", "14_tone_asymmetrical_abnormality", "14. Tone: Asymmetrical Abnormality", array(null=>"",
        "0_none"=>"0 none",
        "1_uncertain"=>"1 uncertain",
        "2_increased"=>"2 increased",
        "3_decreased"=>"3 decreased",
        "8_subject_unable"=>"8 subject unable to carry out task",
        "9_failure_to_test"=>"9 failure to test",
        "not_answered"=>"Not Answered"));

        $this->addTextElement("14_tone_asymmetrical_abnormality_specify", $this->indent . "Specify:");
        $this->XINRegisterRule("14_tone_asymmetrical_abnormality_specify", array("14_tone_asymmetrical_abnormality{@}=={@}2_increased|3_decreased"));

        $this->form->addElement("select", "15_appearance", "15. Appearance: Observe exposed arms...", array(null=>"",
        "0_normal"=>"0 normal",
        "1_uncertain_abnormality"=>"1 uncertain abnormality",
        "2_definite_abnormality"=>"2 definite abnormality",
        "8_subject_unable"=>"8 subject unable to carry out task",
        "9_failure_to_test"=>"9 failure to test",
        "not_answered"=>"Not Answered"));

        $this->addTextElement("15_appearance_specify", $this->indent . "Specify:");

        $this->form->addElement("select", "16_power_upper_limb", "16. Power: Upper Limb: Get child to squeeze 2 fingers...", array(null=>"",
        "0_normal"=>"0 normal",
        "1_uncertain_mild_weakness"=>"1 uncertain mild weakness",
        "2_unequivocal_weakness_or_asymmetry"=>"2 unequivocal weakness or asymmetry",
        "8_subject_unable"=>"8 subject unable to carry out task",
        "9_failure_to_test"=>"9 failure to test",
        "not_answered"=>"Not Answered"));

        $this->addTextElement("16_power_upper_limb_specify", $this->indent . "Specify:");

        $this->form->addElement("select", "17_power_lower_limb", "17. Power: Lower Limb: Observe child walking, kicking, etc.", array(null=>"",
        "0_normal"=>"0 normal",
        "1_uncertain_mild_weakness"=>"1 uncertain mild weakness",
        "2_unequivocal_weakness_or_asymmetry"=>"2 unequivocal weakness or asymmetry",
        "8_subject_unable"=>"8 subject unable to carry out task",
        "9_failure_to_test"=>"9 failure to test",
        "not_answered"=>"Not Answered"));

        $this->addTextElement("17_power_lower_limb_specify", $this->indent . "Specify:");

        $this->form->addElement("select", "18_other_limb_hand_dysmorphic", "18. Other Limb/Hand/Feet Dysmorphic Features", array(null=>"",
        "0_absent"=>"0 absent",
        "1_uncertain"=>"1 uncertain",
        "2_present"=>"2 present",
        "8_subject_unable"=>"8 subject unable to carry out task",
        "9_failure_to_test"=>"9 failure to test",
        "not_answered"=>"Not Answered"));

        $this->addTextElement("18_other_limb_hand_dysmorphic_describe", $this->indent . "Describe:");

        $this->addTextElement("19_other_physical_abnormalities", "19. Other Physical Abnormalities Noted");

        $this->form->addElement("select", "20_hyper_extensibility_of_joints", "20. Hyper extensibility of Joints: bend hand or fingers backward", array(null=>"",
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

        $group[] = $this->form->createElement("select", "21_handedness_draw_or_write_left", null, array(null=>"", "+"=>"+", "+_+"=>"+ +", "+_+_+"=>"+ + +", "not_answered"=>"Not Answered"));
        $group[] = $this->form->createElement("select", "21_handedness_draw_or_write_right", null, array(null=>"", "+"=>"+", "+_+"=>"+ +", "+_+_+"=>"+ + +", "not_answered"=>"Not Answered"));
        $this->form->addGroup($group, "21_handedness_draw_or_write_group", $this->indent . "1. Draw or Write", $this->_GUIDelimiter, false);
        unset($group);

        $group[] = $this->form->createElement("select", "21_handedness_throw_or_placing_left", null, array(null=>"", "+"=>"+", "+_+"=>"+ +", "+_+_+"=>"+ + +", "not_answered"=>"Not Answered"));
        $group[] = $this->form->createElement("select", "21_handedness_throw_or_placing_right", null, array(null=>"", "+"=>"+", "+_+"=>"+ +", "+_+_+"=>"+ + +", "not_answered"=>"Not Answered"));
        $this->form->addGroup($group, "21_handedness_throw_or_placing_group", $this->indent . "2. Throw or placing object", $this->_GUIDelimiter, false);
        unset($group);

        $group[] = $this->form->createElement("text", "21_handedness_total_a_left", "Total a.");
        $group[] = $this->form->createElement("text", "21_handedness_total_b_right", "Total b.");
        $this->form->addGroup($group, "21_handedness_totals_group", $this->indent . "TOTAL", $this->_GUIDelimiter, false);
        unset($group);

        $this->form->addElement("static", null, "22. Measurements (in cm)");
        $this->form->addElement("static", null, "(Sometimes this is erroneously called #21)");
        $this->addTextElement("22_child_hc_cm", $this->indent . "Child HC:");
        $this->addTextElement("22_mother_hc_cm", $this->indent . "Mother HC:");
        $this->addTextElement("22_father_hc_cm", $this->indent . "Father HC:");

        $this->form->addElement("select", "23_adenoma_sebaceum", "23. Adenoma Sebaceum", array(null=>"",
        "0_absent"=>"0 absent",
        "1_uncertain"=>"1 uncertain (few nodules or atypical distribution)",
        "2_present"=>"2 present",
        "8_subject_unable"=>"8 subject unable to carry out task",
        "9_failure_to_test"=>"9 failure to test",
        "not_answered"=>"Not Answered"));

        $this->addTextElement("23_adenoma_sebaceum_describe", $this->indent . "Describe:");

        $this->form->addElement("select", "24_ash_leaf_macules", "24. Ash Leaf Macules: flat, white, leaf shaped spots", array(null=>"",
        "0_absent"=>"0 absent",
        "1_uncertain"=>"1 uncertain",
        "2_present"=>"2 present",
        "8_subject_unable"=>"8 subject unable to carry out task",
        "9_failure_to_test"=>"9 failure to test",
        "not_answered"=>"Not Answered"));

        $this->addTextElement("24_ash_leaf_macules_describe", $this->indent . "Describe:");

        $this->form->addElement("select", "25_shagreen_patches", "25. Shagreen Patches: patches of skin that resemble `untanned leather`", array(null=>"",
        "0_absent"=>"0 absent",
        "1_uncertain"=>"1 uncertain",
        "2_present"=>"2 present",
        "8_subject_unable"=>"8 subject unable to carry out task",
        "9_failure_to_test"=>"9 failure to test",
        "not_answered"=>"Not Answered"));

        $this->addTextElement("25_shagreen_patches_describe", $this->indent . "Describe:");

        $this->form->addElement("select", "26_woods_lamp_examination", "26. Woods Lamp Examination", array(null=>"",
        "0_normal"=>"0 normal",
        "1_uncertain"=>"1 uncertain",
        "2_abnormal"=>"2 abnormal",
        "8_subject_unable"=>"8 subject unable to carry out task",
        "9_failure_to_test"=>"9 failure to test",
        "not_answered"=>"Not Answered"));

        $this->addTextElement("26_woods_lamp_examination_describe", $this->indent . "Describe:");

        $this->form->addElement("select", "27_cafe_au_lait_spots", "27. Cafe au Lait spots: pale yellow/light brown spots", array(null=>"",
        "0_absent"=>"0 absent",
        "1_one_three_spots"=>"1 one-three spots (inclusive)",
        "2_four_or_five_spots"=>"2 four or five spots",
        "3_six_or_more_spots"=>"3 six or more spots (greater than 1.5 cm)",
        "8_subject_unable"=>"8 subject unable to carry out task",
        "9_failure_to_test"=>"9 failure to test",
        "not_answered"=>"Not Answered"));

        $this->addTextElement("27_cafe_au_lait_spots_describe", $this->indent . "Describe:");

        $this->form->addElement("select", "28_cutaneous_nodules", "28. Cutaneous/subcutaneous nodules: observe limbs and head", array(null=>"",
        "0_absent"=>"0 absent",
        "1_uncertain"=>"1 uncertain",
        "2_one_or_more"=>"2 one or more",
        "8_subject_unable"=>"8 subject unable to carry out task",
        "9_failure_to_test"=>"9 failure to test",
        "not_answered"=>"Not Answered"));

        $this->addTextElement("28_cutaneous_nodules_describe", $this->indent . "Describe:");

        $this->form->addElement("select", "29_third_toe_longer", "29. Third toe longer than second", array(null=>"",
        "0_normal"=>"0 normal",
        "1_appears_equal"=>"1 appears equal in length to second toe",
        "2_definitely_longer"=>"2 definitely longer than second toe",
        "8_subject_unable"=>"8 subject unable to carry out task",
        "9_failure_to_test"=>"9 failure to test",
        "not_answered"=>"Not Answered"));

        $this->form->addElement("select", "30_toe_spacing", "30. Toe spacing", array(null=>"",
        "0_normal"=>"0 normal",
        "1_big_gap_between_first_and_second"=>"1 big gap between first and second toes",
        "2_partial_syndactylia_of_two_middle_toes"=>"2 partial syndactylia of two middle toes",
        "8_subject_unable"=>"8 subject unable to carry out task",
        "9_failure_to_test"=>"9 failure to test",
        "not_answered"=>"Not Answered"));

        
        //Defining rules for each visit-specific version
        
        $allQuestions = array('1_strabismus',
        '1_strabismus_specify',
//        '1_strabismus_specify_status',
        '2_ptosis',
        '2_specify',
//        '2_specify_status',
        '3_epicanthus',
        '4_low_seated_ears',
        '5_adherent',
        '6_ear_formation',
        '7_cleft_palate',
        '7_cleft_describe',
//        '7_cleft_describe_status',
        '8_craniofacial_dysmorphic',
        '8_craniofacial_dysmorphic_describe',
//        '8_craniofacial_dysmorphic_describe_status',
        '9_curved_fifth_finger',
        '10_palmar_crease',
        '11_symmetrical_gait_abnormality',
        '11_symmetrical_gait_abnormality_specify',
//        '11_symmetrical_gait_abnormality_specify_status',
        '12_asymmetrical_gait_abnormality',
        '12_asymemtrical_gait_abnormality_specify',
//        '12_asymemtrical_gait_abnormality_specify_status',
        '13_tone_symmetrical_abnormality',
        '13_tone_symmetrical_abnormality_specify',
//        '13_tone_symmetrical_abnormality_specify_status',
        '14_tone_asymmetrical_abnormality',
        '14_tone_asymmetrical_abnormality_specify',
//        '14_tone_asymmetrical_abnormality_specify_status',
        '15_appearance',
        '15_appearance_specify',
//        '15_appearance_specify_status',
        '16_power_upper_limb',
        '16_power_upper_limb_specify',
//        '16_power_upper_limb_specify_status',
        '17_power_lower_limb',
        '17_power_lower_limb_specify',
//        '17_power_lower_limb_specify_status',
        '18_other_limb_hand_dysmorphic',
        '18_other_limb_hand_dysmorphic_describe',
//        '18_other_limb_hand_dysmorphic_describe_status',
        '19_other_physical_abnormalities',
//        '19_other_physical_abnormalities_status',
        '20_hyper_extensibility_of_joints',
        '21_handedness_draw_or_write_left',
        '21_handedness_draw_or_write_right',
        '21_handedness_throw_or_placing_left',
        '21_handedness_throw_or_placing_right',
        '21_handedness_total_a_left',
        '21_handedness_total_b_right',
        '22_child_hc_cm',
//        '22_child_hc_cm_status',
        '22_mother_hc_cm',
//        '22_mother_hc_cm_status',
        '22_father_hc_cm',
//        '22_father_hc_cm_status',
        '23_adenoma_sebaceum',
        '23_adenoma_sebaceum_describe',
//        '23_adenoma_sebaceum_describe_status',
        '24_ash_leaf_macules',
        '24_ash_leaf_macules_describe',
//        '24_ash_leaf_macules_describe_status',
        '25_shagreen_patches',
        '25_shagreen_patches_describe',
//        '25_shagreen_patches_describe_status',
        '26_woods_lamp_examination',
        '26_woods_lamp_examination_describe',
//        '26_woods_lamp_examination_describe_status',
        '27_cafe_au_lait_spots',
        '27_cafe_au_lait_spots_describe',
//        '27_cafe_au_lait_spots_describe_status',
        '28_cutaneous_nodules',
        '28_cutaneous_nodules_describe',
//        '28_cutaneous_nodules_describe_status',
        '29_third_toe_longer',
        '30_toe_spacing'
        );

        //6month question numbers
        $_6month = array_merge(range(1, 10), range(13, 20), array(21), range(23, 30));

        //12month question numbers
        $_12month = array_merge(array(1, 2), range(11, 17), array(19, 20, 22, 27, 28));

        //24month question numbers
        $_24month = array_merge(array(1, 2), range(11, 17), range(19, 21), array(22, 27, 28));

        // DB Object
        $db =& Database::singleton();
        if(PEAR::isError($db)) {
            return PEAR::raiseError ("Could not connect to database: ".$db->getMessage());
        }

        //applicable visit version
        $query = "SELECT visit from neuro_screen WHERE CommentID = '".$this->getCommentID()."'";
        $visit = $db->selectOne($query);
        if(PEAR::isError($visit)){
            return PEAR::raiseError("Query has failed to select Visit: ".$visit->getMessage());
        }

        //which questions must be answered for this particular visit
        switch ($visit) {
            case "6month":
            $requiredQuestions = $_6month;
            break;
            case "12month":
            $requiredQuestions = $_12month;
            break;
            case "24month":
            $requiredQuestions = $_24month;
            break;
        }
        
        foreach($allQuestions as $field) {
            //question number
            ereg("([0-9]+)", $field, $matches);
            
            //is this question used in this version number?
            if(in_array($matches[1], $requiredQuestions)) {
                //yes, required.  Do nothing - all questions are required by default
            } else {
                //"un-require" other questions
                $this->XINRegisterRule($field, array("1_strabismus{@}=={@}Never_going_to_happen"));
            }
         }
         
         //hack to require question #21, because it uses QuickForm groups
         if(in_array(21, $requiredQuestions)) {
            $this->XINRegisterRule('21_handedness_draw_or_write_left', array('1_strabismus{@}!={@}Never_happening'), "This question is required.", "21_handedness_draw_or_write_group");
            $this->XINRegisterRule('21_handedness_draw_or_write_right', array('1_strabismus{@}!={@}Never_happening'), "This question is required.", "21_handedness_draw_or_write_group");

           $this->XINRegisterRule('21_handedness_throw_or_placing_left', array('1_strabismus{@}!={@}Never_happening'), "This question is required.", "21_handedness_throw_or_placing_group");
            $this->XINRegisterRule('21_handedness_throw_or_placing_right', array('1_strabismus{@}!={@}Never_happening'), "This question is required.", "21_handedness_throw_or_placing_group");

           $this->XINRegisterRule('21_handedness_total_a_left', array('1_strabismus{@}!={@}Never_happening'), "This question is required.", "21_handedness_totals_group");
            $this->XINRegisterRule('21_handedness_total_b_right', array('1_strabismus{@}!={@}Never_happening'), "This question is required.", "21_handedness_totals_group");
         }

    } //end _page1()

}
?>
