<?php
class NDB_BVL_Instrument_sibling_socialcontact extends NDB_BVL_Instrument
{
    //Commonly used level of indentation;
    var $indent = "&nbsp;&nbsp;&nbsp;&nbsp;";

    var $rating = array(''=>NULL, '1_very_rarely'=>"1. Very Rarely", '2_rarely'=>"2. Rarely", 
                        '3_occasionally'=>"3. Occasionally",'4_somewhat_often'=>'4. Somewhat Often',
                        '5_often'=>'5. Often','6_very_often'=>'6. Very Often','refused_dontknow'=>'Refused/I Don`t Know');
    var $respondent = array(''=>NULL,'mother'=>'Mother','father'=>'Father','other'=>'Other');
    var $num_days_week = array (''=>NULL,'0'=>'0','1'=>'1','2'=>'2','3'=>'3','4'=>'4','5'=>'5',
                                '6'=>'6','7'=>'7','refused_dontknow'=>'Refused/I Don`t Know');   
    var $rating1 = array (''=>NULL,'often'=>'Often','occasionally'=>'Occasionally','never'=>'Never',
                          'refused_dontknow'=>'Refused/I Don`t Know');
    var $rating2 = array(''=>NULL,'very_well'=>'Very Well','okay'=>'Okay','not_very_well'=>'Not very well',
                         'refused_dontknow'=>'Refused/I Don`t Know');
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
        $this->testName = "sibling_socialcontact";           // test_names.Test_name
        $this->table = 'sibling_socialcontact';
        // data keyed by commentID
        $this->commentID = $commentID;
        $this->dateTimeFields = array("datecompleted");
        $config = & NDB_Config::singleton();
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

        if(preg_match("/sibling_socialcontact(_page[0-9]+)/",$this->page,$matches)){
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

        $this->form->addElement('header', 'instrument_title', "Sibling Social Contact Questionnaire");
        $this->form->addElement('static', null, "<br /><br />");
        
        $this->addBasicDate('datecompleted', "Today's date:", $this->dateOptions);
        $this->addSelect('respondent',"Completed by :", $this->respondent);
        
        $group [] = $this->createText('respondent_other',$this->indent."If Other please specify");
        $this->addGroup($group,"respondent_other_group",$this->indent."If Other please specify",null,false);
        unset($group);
        $rules_array = array("respondent{@}=={@}other");
        $this->XINRegisterRule('respondent_other', $rules_array, "Please specify relationship", 'respondent_other_group');


    }

    function _page2(){
         $this->form->addElement('header', 'instrument_title', "Sibling Social Contact Questionnaire");
         $this->form->addElement('static', null, "<br /><br />");
         
         $this->addSelect('q1_engage_together', "1. How many days per week do they usually engage in any kind of one-on-one activity together <BR>(for example playing, chores, sharing a snack, watching television)?", $this->num_days_week);
         $this->addSelect('q2_play_together', "2. How many days per week do they usually play together?" , $this->num_days_week);
         //$this->addNumericElement("q3_different_playtimes", "3. On days when they play, how many different times do they usually play?");
        // $this->addNumericElement("q4_avg_playtime", "4. How long are they together in an average play time?");
         $questions = array("q3_different_playtimes"=>"3. On days when they play, how many different times do they usually play?",
                            "q4_avg_playtime"=>"4. How long are they together in an average play time?(in Minutes)");
         foreach($questions as $field=>$label) {
             $group [] = $this->createText($field, $label);
             $this->addGroup($group, $field . "_group", $label, null, false);
             unset($group);
             $this->addGroupRule($field . "_group", array(array(array("Value must be numeric.", 'numeric'))));
         }

         
         $this->addSelect('q5_rely_olderchild',"5. To what extent do you rely on the older child to help care for the younger sibling such as help getting dressed,<BR> help during meals, or help getting ready for school?", $this->rating1);

         $this->addSelect('q6_rely_youngerchild', "6. To what extent do you rely on the younger sibling to help care for the older child such as help getting dressed,<BR> help during meals, or help getting ready for school?", $this->rating1);


         $this->addSelect('q7_getalong',"7. Overall, how well would you say they get along?", $this->rating2);
         $this->addSelect('q8_playtogeher',"8. How well would you say they play together?", $this->rating2);
         $family = array(''=>NULL,'older_child'=>'Older Child','sibling'=>'Sibling','both'=>'Both','adult'=>'Adult','refused_dontknow'=>'Refused/I Don`t Know');
         $this->addSelect('q9_controlplay',"9. Who usually is leading or in control of their play?", $family);
         $this->addSelect('q10_toneplay',"10. What is the typical tone of their play?", array(''=>NULL,'positive'=>'Positive',
                           'neutral'=>'Neutral','negative'=>'Negative','refused_dontknow'=>'Refused/I Don`t Know'));
         $this->addSelect('q11_excitementlevel',"11. What is the typical level of excitement?", array(''=>NULL,'very_excited'=>'Very Excited',
                          'active'=>'Active','calm'=>'Calm','refused_dontknow'=>'Refused/I Don`t Know'));
         $this->addSelect('q12_conflicts_duringplay',"12. How often do they have conflicts during play?", array(''=>NULL,'often'=>'Often',
                          'occasionally'=>'Occasionally','rarely'=>'Rarely','refused_dontknow'=>'Refused/I Don`t Know'));
         $this->addSelect('q13_disruptive_conflicts',"13. How disruptive are their conflicts?", array(''=>NULL,'ends_play'=>'Ends play',
                          'major_disruption'=>'Major Disruption','minor_disruption'=>'Minor Disruption','no_disruption'=>'No disruption',
                          'refused_dontknow'=>'Refused/I Don`t Know'));
         $this->addSelect('q14_involed_inplay',"14. In a typical play session, how closely involved are they with each other during play?",
                          array(''=>NULL,'lot_of_interaction'=>'A lot of interaction','stay_close_no_interaction'=>'Stay close but
                          do not interact much','dont_stay_close_or_interact'=>'Do not stay close or interact much',
                          'refused_dontknow'=>'Refused/I Don`t Know'));
         $this->addSelect('q15_stressful_playsession','15. How stressful is it usually for you to monitor play sessions?',array(''=>NULL,
                          'very_stressful'=>'Very Stressful','somewhat_stressful'=>'Somewhat Stressful','not_stressful'=>'Not Stressful',
                          'refused_dontknow'=>'Refused/I Don`t Know'));
         $this->form->addElement('static',null,"16. How do you usually monitor the play at home?");
         $questions = array('q16_help_getalong'=>'a. Directly facilitate by helping them get along?',
                            'q16_participate'=>'b. Participate in the activity with the children',
                            'q16_maintain_presence'=>'c. Maintain presence (in childrens view)',
                            'q16_outofview_listen'=>'d. Out of view but listen to their ongoing activity',
                            'q16_outofview_cry'=>'e. Out of view and can only hear outbursts or cries');
                    
         $rating3 = array(''=>NULL,'frequently'=>'Frequently','occasionally'=>'Occasionally','little_none'=>'Little-or-none',
                          'refused_dontknow'=>'Refused/I Don`t Know');
         foreach($questions as $qstn=>$desc) {
             $this->addSelect($qstn,$this->indent.$desc, $rating3);
         }
         $this->form->addElement('static',null,"17. How much do the children need your help during play in the following areas?");
         $questions = array('q17_manage_emotions'=>'a. Managing Emotions',
                            'q17_understand_rules'=>'b. Understanding social rules (such as taking turns)',
                            'q17_understand_howtoplay'=>'c. Understanding how to play games or activities',
                            'q17_startplay'=>'d. Getting the play session started',
                            'q17_remain_inplay'=>'e. Remaining involved in the play',
                            'q17_manage_conflicts'=>'f. Managing conflicts');
        
        foreach($questions as $qstn=>$desc) {
             $this->addSelect($qstn,$this->indent.$desc, $rating3);
         }


    }
    
}
