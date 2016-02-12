<?php

require_once 'HTML/QuickForm.php';
require_once 'HTML/QuickForm/Renderer/Array.php';

class NDB_BVL_Instrument_bapq_respondent extends NDB_BVL_Instrument
{
    //Commonly used level of indentation;
    var $indent = "&nbsp;&nbsp;&nbsp;&nbsp;";

    var $rating = array(''=>NULL, '1_very_rarely'=>"1. Very Rarely", '2_rarely'=>"2. Rarely", 
                        '3_occasionally'=>"3. Occasionally",'4_somewhat_often'=>'4. Somewhat Often',
                        '5_often'=>'5. Often','6_very_often'=>'6. Very Often');
    var $respondent = array(''=>NULL,'mother'=>'Mother','father'=>'Father','stepmother'=>'Step-Mother',
                            'stepfather'=>'Step-Father','other'=>'Other');



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
        $this->testName = "bapq_respondent";           // test_names.Test_name
        $this->table = 'bapq_respondent';
        // data keyed by commentID
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

        if(preg_match("/bapq_respondent(_page[0-9]+)/",$this->page,$matches)){
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

        $this->addNumericElement('respondent_age','Your Age:<BR>(Please indicate your age in years)');

        $this->addSelect('respondent',"Relationship to child", $this->respondent);
        $this->addTextElement('respondent_other',$this->indent."If Other please specify",
                              array("respondent{@}=={@}other"),"Please specify relationship");

        $this->form->addElement('static', null, "<br /><br />");
        $questions = array("q1_like_being_otherpeople" => "1. I like being around other people",
                           "q2_hard_wordsout_smoothly" =>"2. I find it hard to get my words out smoothly",
                           "q3_comfortable_unexpectedchanges"=>"3. I am comfortable with unexpected changes in plans",
                           "q4_hard_avoid_sidetrack"=>"4. It's hard for me to avoid getting sidetracked in conversations",
                           "q5_information_than_socialize"=>"5. I would rather talk to people to get information that to socialize",
                           "q6_talkinto_tryingnew"=>"6. People have to talk me into trying something new",
                           "q7_intune_conversation"=>"7. I am 'in-tune' with the other person during conversation",
                           "q8_warmup_unfamiliarplace"=>"8. I have to warm myself up to the idea of visiting an unfamiliar place",
                           "q9_enjoy_socialsituations"=>"9. I enjoy being in social situations",
                           "q10_voice_flat_monotone"=>"10. My voice has a flat or monotone sound to it",
                           "q11_disconnected_outofsync_convo"=>"11. I feel disconnected or 'out of sync' in conversations with others",
                           "q12_easy_approach"=>"12. People find it easy to approach me");

        foreach($questions as $field=>$label) {
            $this->addSelect($field, $label, $this->rating);
        }
   
        $this->form->addFormRule(array(&$this, 'BAPQ_Rules'));

    }

    function _page2(){
         $this->form->addElement('header', 'instrument_title', "BAPQ-PSPQ : Personality Styles and Preferences Questionnaire Page2");
         $this->form->addElement('static', null, "<br /><br />");
         $questions = array("q13_strongneed_sameness"=>"13. I feel a strong need for sameness from day to day",
                           "q14_others_dont_understand"=>"14. People ask me to repeat things I've said because they don't understand",
                           "q15_flexible"=>"15. I am flexible about how things should be done",
                           "q16_situations_meetnew_people"=>"16. I look forward to situations where I can meet new people",
                           "q17_talktoomuch_certain_topics"=>"17. I have been told that I talk too much about certain topics",
                           "q18_conversation_tobe_polite"=>"18. When I make conversation it is just to be polite",
                           "q19_lookforward_newthings"=>"19. I look foward to trying new things",
                           "q20_speak_tooloud_softly"=>"20. I speak too loudly or softly",
                           "q21_tell_someone_not_interested"=>"21. I can tell when someone is not interested in what I am saying",
                           "q22_hardtime_change_routine"=>"22. I have a hard time dealing with changes in my routine",
                           "q23_good_smalltalk"=>"23. I am good at making small talk",
                           "q24_act_myways"=>"24. I act very set in my ways");

        foreach($questions as $field=>$label) {
            $this->addSelect($field, $label, $this->rating);
        }

    }
    
    function _page3(){
         $this->form->addElement('header', 'instrument_title', "BAPQ-PSPQ : Personality Styles and Preferences Questionnaire Page3");
         $this->form->addElement('static', null, "<br /><br />");
         $questions = array("q25_connecting_people"=>"25. I feel like I am really connecting with other people",
                           "q26_peoplefrustrated"=>"26. People get frustrated by my unwillingness to bend",
                           "q27_conversation_boresme"=>"27. Conversation bores me",
                           "q28_warmfriendly_others"=>"28. I am warm and friendly in my interactions with others",
                           "q29_longpauses_conversations"=>"29. I leave long pauses in conversations",
                           "q30_alter_dailyroutine"=>"30. I alter my daily routine by trying something different",
                           "q31_alone_ratherthan_withothers"=>"31. I prefer to be alone rather than with others",
                           "q32_losetrack_talking"=>"32. I lose track of my original point when talking to people",
                           "q33_follow_routine"=>"33. I like to closely follow a routine while working",
                           "q34_change_topic"=>"34. I can tell when it is time to change topics in conversation",
                           "q35_doingthings_knownway"=>"35. I keep doing things the way I know, even if another way might be better",
                           "q36_enjoy_chatting"=>"36. I enjoy chatting with people");

        foreach($questions as $field=>$label) {
            $this->addSelect($field, $label, $this->rating);
        }

         //$this->form->addElement("textarea", 'comments', 'Do', array('cols'=>25, 'rows'=>4));
        $this->addBasicTextArea('comments',"Do you have any other comments?");

        //unset($this->XINRules['comments']) ;
        $this->XINRegisterRule('comments', array('comments{@}=={@}NEVER_REQUIRED'));


    }


    function BAPQ_Rules($values) {
       $errors = array();
       if(intval($values['respondent_age']) > 100) {
           $errors['respondent_age_group'] = "Specify age between 0 and 100";    
       }
       return $errors;
    }
}
