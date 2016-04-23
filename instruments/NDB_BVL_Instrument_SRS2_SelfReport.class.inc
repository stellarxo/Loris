<?php

require_once 'HTML/QuickForm.php';
require_once 'HTML/QuickForm/Renderer/Array.php';

class NDB_BVL_Instrument_SRS2_SelfReport extends NDB_BVL_Instrument
{
    //Commonly used level of indentation;
    var $indent = "&nbsp;&nbsp;&nbsp;&nbsp;";

    var $rating = array(''=>NULL, '1_not_true'=>"1. Not True", '2_sometimes_true'=>"2. Sometimes True", 
                        '3_often_true'=>"3. Often True",'4_almost_always_true'=>'4. Almost Always True',
                        'refused_dontknow'=>"Refused/I Don't Know");

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
        $this->testName = "SRS2_SelfReport";           // test_names.Test_name
        $this->table = 'SRS2_SelfReport';
        
        
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

        if(preg_match("/SRS2_SelfReport(_page[0-9]+)/",$this->page,$matches)){
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
        $this->form->addElement('header', 'instrument_title', "SRS2 - Self Report");
        
        $this->form->addElement('static','lorisSubHeader',"<strong>Instructions:</strong><BR>For each question, please choose an option that best describes your behaviour <strong>over the past 6 months </strong>");
        $this->form->addElement('header', 'instrument_title', "Self Rating");

        //$this->addNumericElement('respondent_age','Your Age <BR>(Please indicate your age in years)');
        $field = 'respondent_age';$label = 'Your Age <BR>(Please indicate your age in years)';
        $group [] = $this->createText($field, $label);
        $this->addGroup($group, $field . "_group", $label, null, false);
        //$this->XINRegisterRule($field,array("$field{@}=={@}NEVER_REQUIRED"), $field . "_group");
        unset($group);
        $this->addGroupRule($field . "_group", array(array(array("Value must be numeric.", 'numeric'))));
        
        $this->addSelect('respondent_gender',"Gender ", $this->gender);
       // $this->XINRegisterRule('respondent_gender',array("respondent_gender{@}=={@}NEVER_REQUIRED"));

        $this->form->addElement('static', null, "<br /><br />");
        $questions = array("q1_uncomfortable_socialsituations" => "1. I am much more uncomfortable in social situations than when I am by myself",
                           "q2_wrong_facialexpressions" =>"2. My facial expressions send the wrong message to others about how I actually feel",
                           "q3_self_confident"=>"3. I feel self-confident when interacting with others",
                           "q4_rigid_inflexible"=>"4. When under stress, I engage in rigid or inflexible patterns of behavior that seem odd to people",
                           "q5_others_take_advantage"=>"5. I do not recognize when others are trying to take advantage of me",
                           "q6_rather_be_alone"=>"6. I would rather be alone than with others",
                           "q7_aware_others_feeling"=>"7. I am usually aware of how others are feeling",
                           "q8_behave_strange_bizzare"=>"8. I behave in ways that seem strange or bizarre to others",
                           "q9_overly_dependent"=>"9. I am overly dependent on others for help with meeting my everyday needs",
                           "q10_takethings_literally"=>"10. I take things too literally, and because of that, I misinterpret the intended meaning of parts<BR> of a conversation",
                           "q11_have_selfconfidence"=>"11. I have good self-confidence",
                           "q12_communicate_toothers"=>"12. I am unable to communicate my feelings to others",
                           "q13_awkward_turn_takingtalk"=>"13. I am awkward in turn-taking interactions with others (for example, I have a hard time keeping<BR>up with the give-and-take of a conversation)",
                           "q14_notwell_coordinated"=>"14. I am not well coordinated",
                           "q15_changefacialexp_understandmeaning"=>"15. When people change their tone or facial expression, I usually pick up on that and understand what it means"                             );

        foreach($questions as $field=>$label) {
            $this->addSelect($field, $label, $this->rating);
           // $this->XINRegisterRule($field,array("$field{@}=={@}NEVER_REQUIRED"));
        }
        $this->form->addElement('static','lorisSubHeader',"SRS-2 Self Report copyright © 2012 by Western Psychological Services. Reprint authorized by the<BR>author, J. Constantino, under WPS agreement for the sole use in registered scholarly study. Not to be reprinted in<BR> whole or in part, for any additional purpose, without the prior written authorization of WPS. All rights reserved<BR>
(rights@wpspublish.com)");
        $this->form->addFormRule(array(&$this, 'SRS2_Rules'));

    }

    function _page2(){
         $this->form->addElement('header', 'instrument_title', "SRS2 - Self Report");

         $questions = array("q16_avoideyecontact"=>"16. I avoid eye contact or am told that I have unusual eye contact",
                           "q17_recognize_unfair"=>"17. I recognize when something is unfair",
                           "q18_difficulty_makingfriends"=>"18. I have difficulty making friends, even when trying my best",
                           "q19_frustrated_converyingideas"=>"19. I get frustrated trying to get ideas across in conversations",
                           "q20_unusual_interests"=>"20. I have sensory interests that others find unusual (for example, smelling<BR>or looking at things in a special way)",
                           "q21_imitate_actionsexpressions"=>"21. I am able to imitate others' actions and expressions when it is <BR>socially appropriate to do so",
                           "q22_interact_appropriately"=>"22. I interact appropriately with other adults",
                           "q23_joingroups_activities"=>"23. I do not join group activities or social events unless prompted or strongly<BR> urged to do so",
                           "q24_diff_changeroutine"=>"24. I have more difficulty than others with changes in my routine",
                           "q25_diff_wavelength"=>"25. I do not mind being out of step with or 'not on the same' wavelength as others",
                           "q26_offer_comfort"=>"26. I offer comfort to others when they are sad",
                           "q27_avoid_socialinteractions"=>"27. I avoid starting social interactions with other adults",
                           "q28_think_overandover"=>"28. I think or talk about the same thing over and over",
                           "q29_odd_weird"=>"29. I am regarded by others as odd or weird",
                           "q30_upset_situations"=>"30. I become upset in situations with lots of things going on",
                           "q31_cant_getmind_off"=>"31. I can't get my mind off something once I start thinking about it",
                           "q32_good_personal_hygiene"=>"32. I have good personal hygiene");

        foreach($questions as $field=>$label) {
            $this->addSelect($field, $label, $this->rating);
            //$this->XINRegisterRule($field,array("$field{@}=={@}NEVER_REQUIRED"));

        }
        $this->form->addElement('static','lorisSubHeader',"SRS-2 Self Report copyright © 2012 by Western Psychological Services. Reprint authorized by the<BR>author, J. Constantino, under WPS agreement for the sole use in registered scholarly study. Not to be reprinted in<BR> whole or in part, for any additional purpose, without the prior written authorization of WPS. All rights reserved<BR>
(rights@wpspublish.com)");
    }

    function _page3(){
         $this->form->addElement('header', 'instrument_title', "SRS2 - Self Report");

         $questions = array("q33_socially_awkward"=>"33. My behavior is socially awkward, even when trying to be polite",
                           "q34_avoid_emotionallyclose"=>"34. I avoid people who want to be emotionally close to me",
                           "q35_trouble_keepingup"=>"35. I have trouble keeping up with the flow of a normal conversation",
                           "q36_difficulty_relating_family"=>"36. I have difficulty relating to family members",
                           "q37_difficulty_relating_adults"=>"37. I have difficulty relating to adults outside of my family",
                           "q38_respond_moodchange"=>"38. I respond appropriately to mood changes in others (for example<BR> when a friend's mood changes from happy to sad)",
                           "q39_interested_toofew_topics"=>"39. People think I am interested in too few topics, or that I get <BR>too carried away with those topics",
                           "q40_imaginative"=>"40. I am imaginative",
                           "q41_wander_aimlessly"=>"41. I sometimes seem to wander aimlessly from one activity to another",
                           "q42_overly_sensitive"=>"42. I am overly sensitive to certain sounds, textures, or smells",
                           "q43_enjoy_smalltalk"=>"43. I enjoy small talk (casual conversation with others)",
                           "q44_touble_chains_causation"=>"44. I have more trouble than most people with understanding chains of causation<BR>(in other words, how events are related to one another)",
                           "q45_pay_attention"=>"45. When others around me are paying attention to something, I get interested in what they<BR>are attending to",
                            "q46_serious_facialexp"=>"46. Others feel that I have overly serious facial expressions",
                            "q47_laugh_inappropriarte"=>"47. I laugh at inappropriate times",
                            "q48_goodsense_humor"=>"48. I have a good sense of humor and can understand jokes",
                            "q49_wellat_intellectualtasks"=>"49. I do extremely well at certain kinds of intellectual tasks, but do not do<BR>as well at most other tasks",
                            "q50_repetitive_behavior"=>"50. I have repetitive behaviors that others consider odd",
                            "q51_diff_directqstn"=>"51. I have difficulty answering questions directly and end up talking around the subject",
                            );

        foreach($questions as $field=>$label) {
            $this->addSelect($field, $label, $this->rating);
            //$this->XINRegisterRule($field,array("$field{@}=={@}NEVER_REQUIRED"));
        }
        $this->form->addElement('static','lorisSubHeader',"SRS-2 Self Report copyright © 2012 by Western Psychological Services. Reprint authorized by the<BR>author, J. Constantino, under WPS agreement for the sole use in registered scholarly study. Not to be reprinted in<BR> whole or in part, for any additional purpose, without the prior written authorization of WPS. All rights reserved<BR>
(rights@wpspublish.com)");
    }

    function _page4(){
        // display test name
        $this->form->addElement('header', 'instrument_title', "SRS2 - Self Report");

       $this->form->addElement('static', null, "<br /><br />");
        $questions = array("q52_overly_loud" => "52. I get overly loud without realizing it",
                           "q53_monotone_voice"=>"53. I tend to talk in a monotone voice (in other words, less inflection of voice<BR>than most people demonstrate)",
                           "q54_thinkpeople_as_objects"=>"54. I tend to think about people in the same way that I do objects",
                           "q55_invade_personalspace"=>"55. I get too close to others or invade their personal space without realizing it",
                           "q56_walk_btwn_people"=>"56. I sometimes make the mistake of walking between two people who are trying<BR>to talk to one another",
                           "q57_isolate_myself"=>"57. I tend to isolate myself",
                           "q58_concentrateon_parts"=>"58. I concentrate too much on parts of things than seeing the whole picture",
                           "q59_suspicious_ofpeople"=>"59. I am more suspicious than most people",
                           "q60_emotionally_distant"=>"60. Other people think I am emotionally distant and do not show my feelings",
                           "q61_infelxible"=>"61. I tend to be inflexible",
                           "q62_reason_unusual"=>"62. When I tell someone my reason for doing something, it strikes the person as<BR>unusual or illogical",
                           "q63_greeting_unusual"=>"63. My way of greeting another person is unusual",
                           "q64_tense_socialsitations"=>"64. I am much more tense in social settings than when I am by myself",
                           "q65_staring_gazing"=>"65. I find myself staring or gazing off into space"
                          );

        foreach($questions as $field=>$label) {
            $this->addSelect($field, $label, $this->rating);
            //$this->XINRegisterRule($field,array("$field{@}=={@}NEVER_REQUIRED"));
        }
        $this->form->addElement('static','lorisSubHeader',"SRS-2 Self Report copyright © 2012 by Western Psychological Services. Reprint authorized by the<BR>author, J. Constantino, under WPS agreement for the sole use in registered scholarly study. Not to be reprinted in<BR> whole or in part, for any additional purpose, without the prior written authorization of WPS. All rights reserved<BR>
(rights@wpspublish.com)");

    }
     function SRS2_Rules($values) {
       $errors = array();
       if(intval($values['respondent_age']) > 100 || intval($values['respondent_age']) < 0) {
           $errors['respondent_age_group'] = "Specify age between 0 and 100";
       }
       if(empty($values['respondent_age'])) {
           $errors['respondent_age_group'] = "Please specify age in years";
       }

       return $errors;
    }

}
?>
