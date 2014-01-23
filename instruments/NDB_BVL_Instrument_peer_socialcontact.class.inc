<?php
class NDB_BVL_Instrument_peer_socialcontact extends NDB_BVL_Instrument
{
    //Commonly used level of indentation;
    var $indent = "&nbsp;&nbsp;&nbsp;&nbsp;";

    var $rating = array(''=>NULL, '1_very_rarely'=>"1. Very Rarely", '2_rarely'=>"2. Rarely", 
                        '3_occasionally'=>"3. Occasionally",'4_somewhat_often'=>'4. Somewhat Often',
                        '5_often'=>'5. Often','6_very_often'=>'6. Very Often');
    var $respondent = array(''=>NULL,'mother'=>'Mother','father'=>'Father','other'=>'Other');
    var $num_playmates = array(''=>NULL, 1=>1,2=>2,3=>3,4=>4,5=>5);
    var $total_peer = 5;
//    var 
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
        $this->testName = "peer_socialcontact";           // test_names.Test_name
        $this->table = 'peer_socialcontact';
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
        
        $db =& Database::singleton();
        if(Utility::isErrorX($db)) {
            print "Could not connect to database: ".$db->getMessage();
        }
        $record = $db->pselectRow("SELECT * FROM ".$this->table." WHERE CommentID=:cid",
                array('cid' =>$this->getCommentID()));

        if (Utility::isErrorX($record)) {
            print "Query has failed to select: ".$record->getMessage();
            $record = array();
        }
        $fields = array('peer_initials_1','peer_initials_2','peer_initials_3','peer_initials_4','peer_initials_5');
        foreach($fields as $field) {
            $this->localDefaults[$field] = $record[$field];     
        }
        if(!empty($record['total_playmates'])) {
            $this->localDefaults['total_peer'] = $record['total_playmates'];
        }
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

        if(preg_match("/peer_socialcontact(_page[0-9]+)/",$this->page,$matches)){
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

        $this->form->addElement('header', 'instrument_title', "Peer Social Contact Questionnaire");
        $this->form->addElement('static', null, "<br /><br />");
        
        $this->addBasicDate('datecompleted', "Today's date:", $this->dateOptions);
        $this->addSelect('respondent',"Completed by :", $this->respondent);
        $this->addTextElement('respondent_other',$this->indent."If Other please specify",
                              array("respondent{@}=={@}other"),"Please specify relationship");

        $this->form->addElement('static', null, "<br /><br />");
        $this->addSelect('total_playmates',"Please choose the number of playmates your child has :", $this->num_playmates);
        $this->form->addElement('static', null, "Please list the initals of the children your child plays with regularly in the lines below:");
        for($i = 1; $i <=$this->total_peer; $i++) {
            $this->addTextElement("peer_initials_".$i, "Initials of child $i:", 
                                  array("peer_initials_.$i{@}=={@}NEVER_REQUIRED"));
        }
        $this->form->addElement("static", null, "<br><br>");
        $this->form->addFormRule(array(&$this, 'Peer_Rules'));

    }
    function _page2() {
        $this->form->addElement('static', null, "In the table below indicate which children know each other");

        $group[] = &$this->form->createElement("static", null, null, "Child $i");
        $group[] = &$this->form->createElement("static", null, null, "Child 2");
        $group[] = &$this->form->createElement("static", null, null, "Child 3");
        $group[] = &$this->form->createElement("static", null, null, "Child 4");
        $group[] = &$this->form->createElement("static", null, null, "Child 5");
          $this->form->addGroup($group, $i."_headers", null, $this->_GUIDelimiter, false);
            unset($group);
        $know_eachother = array(""=>null,"yes"=>"Yes","no"=>"No");
        for($i = 1; $i < $this->localDefaults['total_peer']; $i++){
            $groupname = $i."_group";
            //$group[] =& $this->form->createElement("static",null,null,"Child ".$i);
            for($j = 1; $j <= $this->localDefaults['total_peer']; $j++ )  {
                $field = $i."_".$j;
                if($j <= $i){
                    $group[] =& $this->form->createElement("static", null,null,"-");

                } else {
                    $group[] =& $this->form->createElement("select", $field,null,$know_eachother);
                }
            }

            $this->form->addGroup($group, $groupname, "Child $i", $this->_GUIDelimiter, false);
            unset($group);
        }
         $this->form->addElement('static', null, "Initials of the playmates are :");
         for ($i = 1; $i<= $this->total_peer; $i++) {
             if(!empty($this->localDefaults["peer_initials_".$i])) {
                 $this->form->addElement('static',"peer_initials_".$i, "Initials of child $i:"); 
             }
          }
        
    }
    function _page3(){
         $this->form->addElement('header', 'instrument_title', "Peer Social Contact Questionnaire");
         $this->form->addElement('header', 'instrument_title', "Playmate #1");
         $this->form->addElement('static', null, "<br /><br />");
         
         $this->addSelect('q1_engage_together', "1. How many days per week do they usually engage in any kind of one-on-one 
            activity together <BR>(for example playing, chores, sharing a snack, watching television)?", $this->num_days_week);
         $this->addSelect('q2_play_together', "2. How many days per week do they usually play together?" , $this->num_days_week);
         $this->addNumericElement("q3_different_playtimes", "3. On days when they play, how many different times do they usually play?");
         $this->addNumericElement("q4_avg_playtime", "4. How long are they together in an average play time?");
         $rating1 = array (''=>NULL,'often'=>'Often','ocassionally'=>'Ocasionally','never'=>'Never','not_answered'=>'Not Answered');
         
         $this->addSelect('q5_rely_olderchild',"5. To what extent do you rely on the older child to help care for the younger
            sibling such as help getting dressed,<BR> help during meals, or help getting ready for school?", $rating1);
         $this->addSelect('q6_rely_youngerchild', "6. To what extent do you rely on the younger sibling to help care for the older
            child such as help getting dressed,<BR> help during meals, or help getting ready for school?", $rating1);

         $rating2 = array(''=>NULL,'very_well'=>'Very Well','okay'=>'Okay','not_very_well'=>'Not very well','not_answered'=>'Not Answered');

         $this->addSelect('q7_getalong',"7. Overall, how well would you say they get along?", $rating2);
         $this->addSelect('q8_playtogeher',"8. How well would you say they play together?", $rating2);
         $family = array(''=>NULL,'older_child'=>'Older Child','sibling'=>'Sibling','both'=>'Both','adult'=>'Adult','not_answered'=>'Not Answered');
         $this->addSelect('q9_controlplay',"9. Who usually is leading or in control of their play?", $family);
         $this->addSelect('q10_toneplay',"10. What is the typical tone of their play?", array(''=>NULL,'positive'=>'Positive',
                           'neutral'=>'Neutral','negative'=>'Negative','not_answered'=>'Not Answered'));
         $this->addSelect('q11_excitementlevel',"11. What is the typical level of excitement?", array(''=>NULL,'very_excited'=>'Very Excited',
                          'active'=>'Active','calm'=>'Calm','not_answered'=>'Not Answered'));
         $this->addSelect('q12_conflicts_duringplay',"12. How often do they have conflicts during play?", array(''=>NULL,'often'=>'Often',
                          'occasionally'=>'Occasionally','rarely'=>'Rarely','not_answered'=>'Not Answered'));
         $this->addSelect('q13_disruptive_conflicts',"13. How disruptive are their conflicts?", array(''=>NULL,'ends_play'=>'Ends play',
                          'major_disruption'=>'Major Disruption','minor_disruption'=>'Minor Disruption','no_disruption'=>'No disruption',
                          'not_answered'=>'Not Answered'));
         $this->addSelect('q14_involed_inplay',"14. In a typical play session, how closely involved are they with each other during play?",
                          array(''=>NULL,'lot_of_interaction'=>'A lot of interaction','stay_close_no_interaction'=>'Stay close but
                          do not interact much','dont_stay_close_or_interact'=>'Do not stay close or interact much',
                          'not_answered'=>'Not Answered'));
         $this->addSelect('q15_stressful_playsession','15. How stressful is it usually for you to monitor play sessions?',array(''=>NULL,
                          'very_stressful'=>'Very Stressful','somewhat_stressful'=>'Somewhat Stressful','not_stressful'=>'Not Stressful',
                          'not_answered'=>'Not Answered'));
         $this->form->addElement('static',null,"16. How do you usually monitor the play at home?");
         $questions = array('q16_help_getalong'=>'a. Directly facilitate by helping them get along?',
                            'q16_participate'=>'b. Participate in the activity with the children',
                            'q16_maintain_presence'=>'c. Maintain presence (in childrens view)',
                            'q16_outofview_listen'=>'d. Out of view but listen to their ongoing activity',
                            'q16_outofview_cry'=>'e. Out of view and can only hear outbursts or cries');
                    
         $rating3 = array(''=>NULL,'frequently'=>'Frequently','occasionally'=>'Occasionally','little_none'=>'Little-or-none',
                          'not_answered'=>'Not Answered');
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
    function Peer_Rules ($values) {
        $errors = array(); 
        for($i = 1; $i <= $this->total_peer; $i++) {
            if((empty($values["peer_initials_".$i]) && $i <= $values["total_playmates"])) {
                $errors["peer_initials_".$i."_group"] = "Please specify playmate initials";    
            }    
        }
        return $errors;
    }
    
}
