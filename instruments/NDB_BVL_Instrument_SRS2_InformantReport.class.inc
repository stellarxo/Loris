<?php

require_once 'HTML/QuickForm.php';
require_once 'HTML/QuickForm/Renderer/Array.php';

class NDB_BVL_Instrument_SRS2_InformantReport extends NDB_BVL_Instrument
{
    //Commonly used level of indentation;
    var $indent = "&nbsp;&nbsp;&nbsp;&nbsp;";

    var $rating = array(''=>NULL, '1_not_true'=>"1. Not True", '2_sometimes_true'=>"2. Sometimes True", 
                        '3_often_true'=>"3. Often True",'4_almost_always_true'=>'4. Almost Always True',
                        'refused_dontknow'=>"Refused/I Don't Know");
    var $informant = array(''=>NULL,'mother'=>'Mother','father'=>'Father','other_relative'=>'Other Relative',
                           'spouse'=>'Spouse','other'=>'Other');

    var $gender = array(''=>NULL,'male'=>'Male','female'=>'Female');
      
    //abstract function setup($commentID, $page);
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
        
        // set the object properties
        $this->testName = "SRS2_InformantReport";           // test_names.Test_name
        $this->table = 'SRS2_InformantReport';
        
        
        // data keyed by commentID
        $this->commentID = $commentID;
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

        if(preg_match("/SRS2_InformantReport(_page[0-9]+)/",$this->page,$matches)){
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
        $this->form->addElement('header', 'instrument_title', "SRS2 - Adult");
        
        $this->form->addElement('static','lorisSubHeader',"<strong>Instructions:</strong><BR>For each question, please choose an option that best describes this individual's behaviour <strong>over the past 6 months </strong>");

        $field = 'informant_age';$label = 'Your Age <BR>(Please indicate your age in years)';
        $group [] = $this->createText($field, $label);
        $this->addGroup($group, $field . "_group", $label, null, false);
        //$this->XINRegisterRule($field,array("$field{@}=={@}NEVER_REQUIRED"), $field . "_group");
        unset($group);
        $this->addGroupRule($field . "_group", array(array(array("Value must be numeric.", 'numeric'))));
        $this->addSelect('informant_gender',"Gender ", $this->gender);
        //$this->XINRegisterRule('respondent_gender',array("respondent_gender{@}=={@}NEVER_REQUIRED"));
 
        $this->addSelect('informant',"Relationship to rated individual", $this->informant);
        /*$this->addTextElement('informant_other',$this->indent."If Other please specify",
                              array("informant{@}=={@}other"),"Please specify relationship");
        */
        $group [] = $this->createText('informant_other',$this->indent."If Other please specify");
        $this->addGroup($group,"informant_other_group",$this->indent."If Other please specify",null,false);
        unset($group);
        $rules_array = array("informant{@}=={@}other");
        $this->XINRegisterRule('informant_other', $rules_array, "Please specify relationship", 'informant_other_group');



        $this->form->addElement('static', null, "<br /><br />");
        $questions = array("q1_uncomfortable_socialsituations" => "1. Seems much more uncomfortable in social situations than when alone",
                           "q2_wrong_facialexpressions" =>"2. Expressions on his or her face don't match what he or she is saying",
                           "q3_self_confident"=>"3. Seems self-confident when interacting with others",
                           "q4_rigid_inflexible"=>"4. When under stress, he or she shows rigid or inflexible patterns of behavior that seem odd",
                           "q5_others_take_advantage"=>"5. Doesn't recognize when others are trying to take advantage of him or her",
                           "q6_rather_be_alone"=>"6. Would rather be alone than with others",
                           "q7_aware_others_feeling"=>"7. Is aware of what others are thinking or feeling",
                           "q8_behave_strange_bizzare"=>"8. Behaves in ways that seem strange or bizarre",
                           "q9_overly_dependent"=>"9. Seems too dependent on others for help with meeting basic needs",
                           "q10_takethings_literally"=>"10. Takes things too literally, and doesn't get the real meaning of a conversation",
                           "q11_have_selfconfidence"=>"11. Has good self-confidence",
                           "q12_communicate_toothers"=>"12. Is able to communicate his or her feelings to others",
                           "q13_awkward_turn_takingtalk"=>"13. Is awkward in turn-taking interactions with others (for example, doesn't seem to understand<BR>the give-and-take of conversations)",
                           "q14_notwell_coordinated"=>"14. Is not well coordinated",
                           "q15_changefacialexp_understandmeaning"=>"15. Recognizes and appropriately responds to changes in other people's tone of voice and facial expressions"
                           );

        foreach($questions as $field=>$label) {
            $this->addSelect($field, $label, $this->rating);
     //       $this->XINRegisterRule($field,array("$field{@}=={@}NEVER_REQUIRED"));
        }
        $this->form->addElement('static','lorisSubHeader',"SRS-2 Informat Report copyright © 2012 by Western Psychological Services. Reprint authorized by the<BR>author, J. Constantino, under WPS agreement for the sole use in registered scholarly study. Not to be reprinted in<BR> whole or in part, for any additional purpose, without the prior written authorization of WPS. All rights reserved<BR>(rights@wpspublish.com)");
        $this->form->addFormRule(array(&$this, 'SRS2_Rules'));
 
    }

    function _page2(){
         $this->form->addElement('header', 'instrument_title', "SRS2 - Adult");

         $questions = array("q16_avoideyecontact"=>"16. Avoids eye contact or has unusual eye contact",
                           "q17_recognize_unfair"=>"17. Recognizes when something is unfair",
                           "q18_difficulty_makingfriends"=>"18. Has difficulty making friends, even when trying his or her best",
                           "q19_frustrated_converyingideas"=>"19. Gets frustrated trying to get ideas across in conversations",
                           "q20_unusual_interests"=>"20. Shows unusual sensory interests (for example, smelling his or her fingers frequently)<BR>or strange repetitive ways of handling or manipulating small items within reach",
                           "q21_imitate_actionsexpressions"=>"21. Is able to imitate others' actions and demeanor when it is <BR>socially appropriate to do so",
                           "q22_interact_appropriately"=>"22. Interacts appropriately with other adults",
                           "q23_joingroups_activities"=>"23. Does not join group activities or social events unless forced to do so",
                           "q24_diff_changeroutine"=>"24. Has more difficulty than others with changes in his or her routine",
                           "q25_diff_wavelength"=>"25. Doesn't mind being out of step with or 'not on the same wavelength' as others",
                           "q26_offer_comfort"=>"26. Offers comfort to others when they are sad",
                           "q27_avoid_socialinteractions"=>"27. Avoids starting social interactions with other adults",
                           "q28_think_overandover"=>"28. Thinks or talks about the same thing over and over",
                           "q29_odd_weird"=>"29. Is regarded by others as odd or weird",
                           "q30_upset_situations"=>"30. Becomes upset in a situation with lots of things going on",
                           "q31_cant_getmind_off"=>"31. Can't get his or her mind off something once he or she starts thinking about it",
                           "q32_good_personal_hygiene"=>"32. Has good personal hygiene");

        foreach($questions as $field=>$label) {
            $this->addSelect($field, $label, $this->rating);
   //         $this->XINRegisterRule($field,array("$field{@}=={@}NEVER_REQUIRED"));

        }
        $this->form->addElement('static','lorisSubHeader',"SRS-2 Informat Report copyright © 2012 by Western Psychological Services. Reprint authorized by the<BR>author, J. Constantino, under WPS agreement for the sole use in registered scholarly study. Not to be reprinted in<BR> whole or in part, for any additional purpose, without the prior written authorization of WPS. All rights reserved<BR>(rights@wpspublish.com)");
    }

    function _page3(){
         $this->form->addElement('header', 'instrument_title', "SRS2 - Adult");

         $questions = array("q33_socially_awkward"=>"33. Is socially awkward, even when trying to be polite",
                           "q34_avoid_emotionallyclose"=>"34. Avoids people who want to be emotionally close to him or her",
                           "q35_trouble_keepingup"=>"35. Has trouble keeping up with the flow of a normal conversation",
                           "q36_difficulty_relating_family"=>"36. Has difficulty relating to family members",
                           "q37_difficulty_relating_adults"=>"37. Has difficulty relating to other adults",
                           "q38_respond_moodchange"=>"38. Responds appropriately to mood changes in others (for example<BR> when a friend's mood changes from happy to sad)",
                           "q39_interested_toofew_topics"=>"39. Has an unusually narrow range of interests",
                           "q40_imaginative"=>"40. Is imaginative without loosing touch with reality",
                           "q41_wander_aimlessly"=>"41. Wanders aimlessly from one activity to another",
                           "q42_overly_sensitive"=>"42. Seems overly sensitive to sounds, textures, or smells",
                           "q43_enjoy_smalltalk"=>"43. Enjoys and is competent with small talk (casual conversation with others)",
                           "q44_touble_chains_causation"=>"44. Doesn't understand how events relate to one another (cause and effect)<BR> the way other adults do",
                           "q45_pay_attention"=>"45. Generally gets interested in what others nearby are paying attention to",
                            "q46_serious_facialexp"=>"46. Has overly serious facial expressions",
                            "q47_laugh_inappropriarte"=>"47. Laughs at inappropriate times",
                            "q48_goodsense_humor"=>"48. Has a sense of humor, understands jokes",
                            "q49_wellat_intellectualtasks"=>"49. Does extremely well at a few intellectual or computational tasks,<BR> but does not do as well at most other tasks",
                            "q50_repetitive_behavior"=>"50. Has repetitive, odd behaviors",
                            "q51_diff_directqstn"=>"51. Has difficulty answering questions directly and ends up talking around the subject",
                            );

        foreach($questions as $field=>$label) {
            $this->addSelect($field, $label, $this->rating);
  //          $this->XINRegisterRule($field,array("$field{@}=={@}NEVER_REQUIRED"));
        }
        $this->form->addElement('static','lorisSubHeader',"SRS-2 Informat Report copyright © 2012 by Western Psychological Services. Reprint authorized by the<BR>author, J. Constantino, under WPS agreement for the sole use in registered scholarly study. Not to be reprinted in<BR> whole or in part, for any additional purpose, without the prior written authorization of WPS. All rights reserved<BR>
(rights@wpspublish.com)");
    }

    function _page4(){
        // display test name
        $this->form->addElement('header', 'instrument_title', "SRS2 - Adult");

       $this->form->addElement('static', null, "<br /><br />");
        $questions = array("q52_overly_loud" => "52. Knows when he or she is talking too loud or making too much noise",
                           "q53_monotone_voice"=>"53. Talks to people with an unusual tone of voice (for example, talks like a robot or <BR> like he or she is giving a lecture)",
                           "q54_thinkpeople_as_objects"=>"54. Seems to react to people as if they are objects",
                           "q55_invade_personalspace"=>"55. Knows when he or she is too close to someone or is invading someone's space",
                           "q56_walk_btwn_people"=>"56. Walks in between two people who are talking",
                           "q57_isolate_myself"=>"57. Isolative; tends not to leave his or her home",
                           "q58_concentrateon_parts"=>"58. Concentrates too much on parts of things rather than seeing the whole picture",
                           "q59_suspicious_ofpeople"=>"59. Is overly suspicious",
                           "q60_emotionally_distant"=>"60. Is emotionally distant, doesn't show his or her feelings",
                           "q61_infelxible"=>"61. Is inflexible, has a hard time changing his or her mind ",
                           "q62_reason_unusual"=>"62. Gives unusual or illogical reasons for doing things",
                           "q63_greeting_unusual"=>"63. Touches or greets others in an unusual way",
                           "q64_tense_socialsitations"=>"64. Is too tense in social settings",
                           "q65_staring_gazing"=>"65. Stares or gazes off into space"
                          );

        foreach($questions as $field=>$label) {
            $this->addSelect($field, $label, $this->rating);
//            $this->XINRegisterRule($field,array("$field{@}=={@}NEVER_REQUIRED"));
        }
        $this->form->addElement('static','lorisSubHeader',"SRS-2 Informat Report copyright © 2012 by Western Psychological Services. Reprint authorized by the<BR>author, J. Constantino, under WPS agreement for the sole use in registered scholarly study. Not to be reprinted in<BR> whole or in part, for any additional purpose, without the prior written authorization of WPS. All rights reserved<BR>
(rights@wpspublish.com)");

    }
    function SRS2_Rules($values) {
       $errors = array();
       if(intval($values['informant_age']) > 100 || intval($values['informant_age']) < 0) {
           $errors['informant_age_group'] = "Specify age between 0 and 100";
       }
       if(empty($values['informant_age'])) {
           $errors['informant_age_group'] = "Please specify age in years";
       }

       return $errors;
    }

    function getReview() {
        $DB = Database::singleton();
        $smarty = new Smarty_neurodb();
        $tpl_data = array();

        $tpl_data['questions'] = $DB->pselect(
            "SELECT Description as question,
            SourceField FROM parameter_type 
            WHERE SourceFrom=:TN AND 
            SourceField NOT IN ('Validity', 'Administration')",
                array(
                    'TN' => $this->testName
                )
            );

        $Responses = $DB->pselectRow(
            "SELECT * FROM " . $this->testName . " WHERE CommentID=:CID",
            array('CID' => $this->getCommentID())
        );
        foreach ($tpl_data['questions'] as $key=>&$row) {
            if (isset($Responses[$row['SourceField']])) {
                if($row['SourceField'] == 'informant_other' && $Responses['informant'] != 'other') {
                   unset($tpl_data['questions'][$key]);
                } else {
                    $row['response'] = $Responses[$row['SourceField']];
                }

            }
        }

        $smarty->assign($tpl_data);
        $html = $smarty->fetch("directentry_review.tpl");
        return $html;
    }


}
?>
