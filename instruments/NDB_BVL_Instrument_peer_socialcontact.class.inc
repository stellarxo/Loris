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
    var $gender = array(''=>NULL,'boy'=>'Boy','girl'=>'Girl','not_answered'=>'Not Answered');
    var $q3_options = array(''=>NULL, 'cousins'=>'Cousins','neighbors'=>'Neighbors',
                            'classmates'=>'Classmates','parent_friend_child'=>'Parents friends child',
                            'other'=>'Other','not_answered'=>'Not Answered');
    var $q4_options = array(''=>NULL,'mostly_your_home'=>'Mostly your home',
                            'mostly_playmate_home'=>'Mostly playmates home','equally_both'=>'Equally both',
                            'mostly_other'=>'Mostly other (such as playground)','not_answered'=>'Not Answered');
    var $q5_options = array(''=>NULL,'walking_distance'=>'Walking distance',
                            'short_drive'=>'Short drive(upto 15min)','long_drive'=>'Long drive(> 15min)',
                            'not_answered'=>'Not Answered');
    var $yesNo = array(''=>NULL,'yes'=>'Yes','no'=>'No','not_answered'=>'Not Answered');
    var $q8_options = array(''=>NULL,'none'=>'None','dont_know'=>'Dont know','autism'=>'Autism',
                            'other_developmental_delay'=>'Other developmental delay',
                            'speech_language_delay'=>'Speech or language delay',
                            'other'=>'Other','not_answered'=>'Not Answered');
    var $q9_options = array(''=>NULL,'really_likes'=>'Really likes','likes'=>'Likes',
                            'pretty_neutral'=>'Pretty neutral','just_tolerates'=>'Just tolerates',
                            'not_answered'=>'Not Answered');
    var $q10_options = array(''=>NULL,'really_likes'=>'Really likes','likes'=>'Likes',
                            'pretty_neutral'=>'Pretty neutral','just_tolerates'=>'Just tolerates',
                            'not_answered'=>'Not Answered');

    var $q11_options = array(''=>NULL,'very_well'=>'Very well','okay'=>'Okay',
                             'not_very_well'=>'Not very well','not_answered'=>'Not Answered');
    var $q12_options = array(''=>NULL,'my_child'=>'My child','playmate'=>'Playmate','both'=>'Both',
                             'adult'=>'Adult','not_answered'=>'Not Answered');
    var $q13_options = array(''=>NULL,'positive'=>'Positive','neutral'=>'Neutral','negative'=>'Negative',
                             'not_answered'=>'Not Answered');
    var $q14_options = array(''=>NULL,'very_excited'=>'Very Excited','active'=>'Active','calm'=>'Calm',
                             'not_answered'=>'Not Answered');
    var $q15_options = array(''=>NULL,'frequently'=>'Frequently','occasionally'=>'Occasionally',
                             'rarely'=>'Rarely','not_answered'=>'Not Answered');
    var $q16_options = array(''=>NULL,'ends_play'=>'Ends play','major_disruption'=>'Major disruptions',
                             'minor_disruption'=>'Minor disruption','no_disruption'=>'No disruption',
                             'not_answered'=>'Not Answered');
    var $q17_options = array(''=>NULL,'lot_of_interaction'=>'A lot of interaction',
                             'stay_close_no_interaction'=>'Stay close but do not interact much',
                             'dont_stay_close_or_interact'=>'Do not stay close or interact much', 
                             'not_answered'=>'Not Answered');
    var $q19_options = array(''=>NULL,'very_difficult'=>'Very difficult',
                             'somewhat_difficult'=>'Somewhat difficult',
                             'not_difficult'=>'Not difficult at all','not_answered'=>'Not Answered'); 
    var $q20_options = array(''=>NULL,'very_stressful'=>'Very stressful',
                             'somewhat_stressful'=>'Somewhat stressful',
                             'not_stressful'=>'Not stressful at all','not_answered'=>'Not Answered');
    var $q21_options = array(''=>NULL,'frequently'=>'Frequently','occasionally'=>'Occasionally',
                             'little_or_none'=>'Little-or-none','not_answered'=>'Not Answered');
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
        $i = 1;
         $this->form->addElement('header', 'instrument_title', "Peer Social Contact Questionnaire");
         $this->form->addElement('static', 'peer_initials_1', "Playmate #1: ");
         
         $group[] = &$this->form->createElement("text",'age_yrs_playmate_'.$i,null,null);
         $group[] =& $this->form->createElement("static", null,null,"yrs");
         $group[] = &$this->form->createElement("text",'age_mos_playmate_'.$i,null,null);
         $group[] =& $this->form->createElement("static", null,null,"mos");
         $this->form->addGroup($group, "age_playmate".$i, "Age ", $this->_GUIDelimiter, false);
         unset($group);
         
         $this->addSelect('gender_playmate_'.$i,'Gender ', $this->gender);
         $this->form->addElement('static', null, "<br /><br />");
         $this->addNumericElement("q1_number_playtimes_playmate".$i, "1. How many times did they play together in the last three months in your home?");
         $this->addNumericElement("q2_avg_playtime_playmate".$i,"2. How long are they together in an average play time?");         
         $this->addSelect('q3_related_playmate'.$i,"3. How do they know each other?", $this->q3_options);
         $this->addTextElement('q3_related_other_playmate'.$i,$this->indent."If Other please specify",
                               array("q3_related_playmate.$i{@}=={@}other"),"Please specify relationship");
         $this->addSelect('q4_playarea_playmate'.$i,"4. Where do they usually play?", $this->q4_options);
         $this->addTextElement('q4_playarea_other_playmate'.$i,$this->indent."If Other please specify",
                   array("q4_playarea_other_playmate.$i{@}=={@}mostly_other"),"Please specify play area");
         
         $this->addSelect('q5_proximity_playmate'.$i,"5. How close does this playmate live to your house?", 
                          $this->q5_options);
         $this->addSelect('q6_sameschool_playmate'.$i,"6. Is this playmate in your child's school now?", 
                          $this->yesNo);
         $this->addSelect('q7_samechildcare_playmate'.$i,"7. Is this playmate in your child's childcare now?",
                                   $this->yesNo);
         $this->addSelect('q8_specialneeds_playmate'.$i,"8. What special needs does this playmate have?",
                          $this->q8_options);
         $this->addSelect('q9_yourchild_like_playmate'.$i,"9. How much does your child like this playmate?",
                          $this->q9_options);
         $this->addSelect('q10_like_yourchild_playmate'.$i,"10. How much does this playmate like your child?",
                          $this->q9_options);
         $this->addSelect('q11_getalong_playmate'.$i,"11. How well would you say they get along?",
                          $this->q11_options);
         $this->addSelect('q12_leading_play_playmate'.$i,"12. Who usually is leading or in control of the play?",
                          $this->q12_options);
         $this->addSelect('q13_typical_playtone_playmate'.$i,"13. What is the typical tone of the play?",
                          $this->q13_options);
         $this->addSelect('q14_typical_excitement_playmate'.$i,"14. What is the typical level of excitement?",
                          $this->q14_options);
         $this->addSelect('q15_num_conflicts_playmate'.$i,"15. How often do they have conflicts during play?",
                          $this->q15_options);
         $this->addSelect('q16_disruptive_playmate'.$i,"16. How disruptive are their conflicts?",
                          $this->q16_options);
         $this->addSelect('q17_how_involved_playmate'.$i,"17. In a typical play session, how closely involved are they with each other during play?", $this->q17_options);
         $this->form->addElement('static',null,"18. What percentage of time were the play dates arranged by:");
           $this->addNumericElement("q18_arrangeplay_you_playmate".$i,$this->indent."You (%) "); 
           $this->addNumericElement("q18_arrangeplay_yourchild_playmate".$i,$this->indent."Your child (%)"); 
           $this->addNumericElement("q18_arrangeplay_other_playmate".$i,$this->indent."Other family or friends (%) "); 
         $this->addSelect('q19_arrange_contacts_playmate'.$i,"19. How difficult was it to arrange those contacts?", $this->q19_options);
         $this->addSelect('q20_stress_monitorplay_playmate'.$i,"20. How stressful is it usually for you to monitor play sessions?", $this->q20_options);
         $this->form->addElement('static',null,"21. How do you usually monitor the play at home?");
         $questions = array('q21_facililate_getalong_playmate'.$i=>'a. Directly facilitate by helping them get along',
                 'q21_participate_activity_playmate'.$i=>'b. Participate in the activity with children',
                 'q21_maintain_presence_playmate'.$i=>'c. Maintain presence (in childs view)',
                 'q21_outofview_listen_playmate'.$i=>'d. Out of view but listen to their ongoing activity',
                 'q21_outofview_notlisten_playmate'.$i=>'e. Out of view and can only hear outburts or cries');

         foreach($questions as $qstn=>$desc) {
             $this->addSelect($qstn,$this->indent.$desc, $this->q21_options);
         }

         $this->form->addElement('static',null,"22. How much does your child need your help during play with this playmate in the following areas?");
         $questions = array('q22_manage_emotions_playmate'.$i=>'a. Managing Emotions',
                 'q22_understand_rules_playmate'.$i=>'b. Understanding social rules (such as taking turns and sharing)',
                 'q22_understand_howtoplay_playmate'.$i=>'c. Understanding how to play activities',
                 'q22_startplay_playmate'.$i=>'d. Getting the play session started',
                 'q22_remain_inplay_playmate'.$i=>'e. Remaining involved in the play',
                 'q22_manage_conflicts_playmate'.$i=>'f. Managing conflicts');

         foreach($questions as $qstn=>$desc) {
             $this->addSelect($qstn,$this->indent.$desc, $this->q21_options);
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
