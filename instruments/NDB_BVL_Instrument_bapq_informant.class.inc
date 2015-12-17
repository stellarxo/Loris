<?php

require_once 'HTML/QuickForm.php';
require_once 'HTML/QuickForm/Renderer/Array.php';

class NDB_BVL_Instrument_bapq_informant extends NDB_BVL_Instrument
{
    //Commonly used level of indentation;
    var $indent = "&nbsp;&nbsp;&nbsp;&nbsp;";

    var $rating = array(''=>NULL, '1_very_rarely'=>"1. Very Rarely", '2_rarely'=>"2. Rarely", 
                        '3_occasionally'=>"3. Occasionally",'4_somewhat_often'=>'4. Somewhat Often',
                        '5_often'=>'5. Often','6_very_often'=>'6. Very Often');
    var $informant = array(''=>NULL,'spouse'=>'Spouse','other'=>'Other');



    //abstract function setup($commentHe/SheD, $page);
    /**
     * sets up basic data, such as the HTML_Quickform object, and so on.
     *
     * @param string $commentHe/SheD  the CommentHe/SheD identifying the data to load
     * @param string $page       if a multipage form, the page to show
     * @return void
     * @access public
     */
    function setup($commentID, $page){
        $this->formType="XIN";
        $this->form = new HTML_Quickform('test_form');
        $this->page = $page;            // page label (number or
        
        // set the object properties
        $this->testName = "bapq_informant";           // test_names.Test_name
        $this->table = 'bapq_informant';
        // data keyed by commentHe/SheD
        $this->commentID = $commentID;

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

        if(preg_match("/bapq_informant(_page[0-9]+)/",$this->page,$matches)){
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
        $this->form->addElement('header', 'instrument_title', "BAPQ-PSPQ : Personality Styles and Preferences Questionnaire");
        $this->form->addElement('static', null, "<br /><br />");

        $this->addNumericElement('informant_age','Your Age:<BR>(Please indicate your age in years)');

        $this->addSelect('informant',"Relationship to respondent/participant", $this->informant);
        $this->addTextElement('informant_other',$this->indent."If Other please specify",
                              array("informant{@}=={@}other"),"Please specify relationship");

        $this->form->addElement('static', null, "<br /><br />");
        $questions = array("q1_like_being_otherpeople" => "1. He/She likes being around other people",
                           "q2_hard_wordsout_smoothly" =>"2. He/She finds it hard to get his/her words out smoothly",
                           "q3_comfortable_unexpectedchanges"=>"3. He/She is comfortable with unexpected changes in plans",
                           "q4_hard_avoid_sidetrack"=>"4. It's hard for him/her to avoid getting sidetracked in conversations",
                           "q5_information_than_socialize"=>"5. He/She would rather talk to people to get information that to socialize",
                           "q6_talkinto_tryingnew"=>"6. People have to talk him/her into trying something new",
                           "q7_intune_conversation"=>"7. He/She is 'in-tune' with the other person during conversation",
                           "q8_warmup_unfamiliarplace"=>"8. He/She has to warm himself/herself up to the idea of visiting an unfamiliar place",
                           "q9_enjoy_socialsituations"=>"9. He/She enjoys being in social situations",
                           "q10_voice_flat_monotone"=>"10. His/Her voice has a flat or monotone sound to it",
                           "q11_disconnected_outofsync_convo"=>"11. He/She feels disconnected or 'out of sync' in conversations with others",
                           "q12_easy_approach"=>"12. People find it easy to approach him/her");

        foreach($questions as $field=>$label) {
            $this->addSelect($field, $label, $this->rating);
        }
   
        $this->form->addFormRule(array(&$this, 'BAPQ_Rules'));

    }

    function _page2() {
       
       $this->form->addElement('header', 'instrument_title', "BAPQ-PSPQ : Personality Styles and Preferences Questionnaire Page2");
       $questions = array("q13_strongneed_sameness"=>"13. He/She feels a strong need for sameness from day to day",
                           "q14_others_dont_understand"=>"14. People ask him/her to repeat things he/she has said because they don't understand",
                           "q15_flexible"=>"15. He/She is flexible about how things should be done",
                           "q16_situations_meetnew_people"=>"16. He/She looks forward to situations where he/she can meet new people",
                           "q17_talktoomuch_certain_topics"=>"17. He/She has been told that he/she talks too much about certain topics",
                           "q18_conversation_tobe_polite"=>"18. When he/she makes conversation it is just to be polite",
                           "q19_lookforward_newthings"=>"19. He/She looks foward to trying new things",
                           "q20_speak_tooloud_softly"=>"20. He/She speaks too loudly or softly",
                           "q21_tell_someone_not_interested"=>"21. He/She can tell when someone is not interested in what he/she is saying",
                           "q22_hardtime_change_routine"=>"22. He/She has a hard time dealing with changes in his/her routine",
                           "q23_good_smalltalk"=>"23. He/She is good at making small talk",
                           "q24_act_myways"=>"24. He/She acts very set in his/her ways");

        foreach($questions as $field=>$label) {
            $this->addSelect($field, $label, $this->rating);
        }
   
     
    }
    
    function _page3() {
       
       $this->form->addElement('header', 'instrument_title', "BAPQ-PSPQ : Personality Styles and Preferences Questionnaire Page2");
       $questions = array("q25_connecting_people"=>"25. He/She feel like he/she is really connecting with other people",
                           "q26_peoplefrustrated"=>"26. People get frustrated by his/her unwillingness to bend",
                           "q27_conversation_boresme"=>"27. Conversation bores him/her",
                           "q28_warmfriendly_others"=>"28. He/She is warm and friendly in his/her interactions with others",
                           "q29_longpauses_conversations"=>"29. He/She leaves long pauses in conversations",
                           "q30_alter_dailyroutine"=>"30. He/She alters his/her daily routine by trying something different",
                           "q31_alone_ratherthan_withothers"=>"31. He/She prefers to be alone rather than with others",
                           "q32_losetrack_talking"=>"32. He/She loses track of his/her original point when talking to people",
                           "q33_follow_routine"=>"33. He/She likes to closely follow a routine while working",
                           "q34_change_topic"=>"34. He/She can tell when it is time to change topics in conversation",
                           "q35_doingthings_knownway"=>"35. He/She keeps doing things the way he/she know, even if another way might be better",
                           "q36_enjoy_chatting"=>"36. He/She enjoys chatting with people");

        foreach($questions as $field=>$label) {
            $this->addSelect($field, $label, $this->rating);
        }
       $this->addBasicTextArea("comments", "Do you have any other comments?");
       $this->XINRegisterRule('comments', array('comments{@}=={@}NEVER_REQUIRED'));
   
     
    }
    function BAPQ_Rules($values) {
       $errors = array();
       if(intval($values['informant_age']) > 100) {
           $errors['informant_age_group'] = "Specify age between 0 and 100";    
       }
       return $errors;
    }
}
