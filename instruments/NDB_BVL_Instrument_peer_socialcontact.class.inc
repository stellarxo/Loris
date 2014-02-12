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
    var $age_yrs = array(''=>NULL,'1'=>'1 yr','2'=>'2 yrs','3'=>'3 yrs','4'=>'4 yrs','5'=>'5 yrs',
                         '6'=>'6 yrs','7'=>'7 yrs','8'=>'8 yrs','9'=>'9 yrs','10'=>'10 yrs',
                         '11'=>'11 yrs','12'=>'12 yrs','13'=>'13 yrs','14'=>'14 yrs','15'=>'15 yrs');
    var $age_mos = array(''=>NULL,'1'=>'1 mos','2'=>'2 mos','3'=>'3 mos','4'=>'4 mos','5'=>'5 mos',
                         '6'=>'6 mos','7'=>'7 mos','8'=>'8 mos','9'=>'9 mos','10'=>'10 mos',
                         '11'=>'11 mos','12'=>'12 mos');
    var $gender = array(''=>NULL,'boy'=>'Boy','girl'=>'Girl');
    var $q3_options = array(''=>NULL, 'cousins'=>'Cousins','neighbors'=>'Neighbors',
                            'classmates'=>'Classmates','parent_friend_child'=>'Parents friends child',
                            'other'=>'Other');
    var $q4_options = array(''=>NULL,'mostly_your_home'=>'Mostly your home',
                            'mostly_playmate_home'=>'Mostly playmates home','equally_both'=>'Equally both',
                            'mostly_other'=>'Mostly other (such as playground)');
    var $q5_options = array(''=>NULL,'walking_distance'=>'Walking distance',
                            'short_drive'=>'Short drive(upto 15min)','long_drive'=>'Long drive(> 15min)');
    var $yesNo = array(''=>NULL,'yes'=>'Yes','no'=>'No');
    var $q8_options = array(''=>NULL,'none'=>'None','dont_know'=>'Dont know','autism'=>'Autism',
                            'other_developmental_delay'=>'Other developmental delay',
                            'speech_language_delay'=>'Speech or language delay',
                            'other'=>'Other');
    var $q9_options = array(''=>NULL,'really_likes'=>'Really likes','likes'=>'Likes',
                            'pretty_neutral'=>'Pretty neutral','just_tolerates'=>'Just tolerates');
    var $q10_options = array(''=>NULL,'really_likes'=>'Really likes','likes'=>'Likes',
                            'pretty_neutral'=>'Pretty neutral','just_tolerates'=>'Just tolerates');

    var $q11_options = array(''=>NULL,'very_well'=>'Very well','okay'=>'Okay',
                             'not_very_well'=>'Not very well');
    var $q12_options = array(''=>NULL,'my_child'=>'My child','playmate'=>'Playmate','both'=>'Both',
                             'adult'=>'Adult');
    var $q13_options = array(''=>NULL,'positive'=>'Positive','neutral'=>'Neutral','negative'=>'Negative');
    var $q14_options = array(''=>NULL,'very_excited'=>'Very Excited','active'=>'Active','calm'=>'Calm');
    var $q15_options = array(''=>NULL,'frequently'=>'Frequently','occasionally'=>'Occasionally',
                             'rarely'=>'Rarely');
    var $q16_options = array(''=>NULL,'ends_play'=>'Ends play','major_disruption'=>'Major disruptions',
                             'minor_disruption'=>'Minor disruption','no_disruption'=>'No disruption');
    var $q17_options = array(''=>NULL,'lot_of_interaction'=>'A lot of interaction',
                             'stay_close_no_interaction'=>'Stay close but do not interact much',
                             'dont_stay_close_or_interact'=>'Do not stay close or interact much');
    var $q19_options = array(''=>NULL,'very_difficult'=>'Very difficult',
                             'somewhat_difficult'=>'Somewhat difficult',
                             'not_difficult'=>'Not difficult at all'); 
    var $q20_options = array(''=>NULL,'very_stressful'=>'Very stressful',
                             'somewhat_stressful'=>'Somewhat stressful',
                             'not_stressful'=>'Not stressful at all');
    var $q21_options = array(''=>NULL,'frequently'=>'Frequently','occasionally'=>'Occasionally',
                             'little_or_none'=>'Little-or-none');
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
        
        // required fields for data entry completion status
        $this->_requiredElements = array('datecompleted','know_1_2');
        for($i = 1; $i <= $record['total_playmates']; $i++) {
              array_push($this->_requiredElements,"age_yrs_playmate_".$i );     
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
        
        $group [] = $this->createText('respondent_other',$this->indent."If Other please specify");
        $this->addGroup($group,"respondent_other_group",$this->indent."If Other please specify",null,false);
        unset($group);
        $rules_array = array("respondent{@}=={@}other");
        $this->XINRegisterRule('respondent_other', $rules_array, "Please specify relationship", 'respondent_other_group');

        $this->form->addElement('static', null, "<br /><br />");
        $this->addSelect('total_playmates',"Please choose the number of playmates your child has :", $this->num_playmates);
        $this->form->addElement('static', null, "Please list the initals of the children your child plays with regularly in the lines below:");
        for($i = 1; $i <=$this->total_peer; $i++) {
           $group [] = $this->createText("peer_initials_".$i,"Initials of child $i:");
           $this->addGroup($group,"peer_initials_".$i."_group","Initials of child $i:",null, false);
           unset($group);
           $this->XINRegisterRule('peer_initials_'.$i, array("peer_initials_.$i{@}=={@}NEVER_REQUIRED"), null, "peer_initials_".$i."_group");
        }
        $this->form->addElement("static", null, "<br><br>");
        $this->form->addFormRule(array(&$this, 'Peer_Rules'));

    }
    function _page2() {
        
        $this->addHeader("In the table below indicate which<BR> children know each other");
        $this->form->addElement("static", null, "<br><br>");
        $group[] = &$this->form->createElement("static", null, null, "Child 1");
        $group[] = &$this->form->createElement("static", null, null, "Child 2");
        $group[] = &$this->form->createElement("static", null, null, "Child 3");
        $group[] = &$this->form->createElement("static", null, null, "Child 4");
        $group[] = &$this->form->createElement("static", null, null, "Child 5");
          $this->form->addGroup($group, $i."_headers", null, $this->_GUIDelimiter, false);
            unset($group);
        $know_eachother = array(""=>null,"yes"=>"Yes","no"=>"No");
        for($i = 1; $i < $this->localDefaults['total_peer']; $i++){
            $groupname = $i."_group";
            for($j = 1; $j <= $this->localDefaults['total_peer']; $j++ )  {
                $field = "know_".$i."_".$j;
                if($j <= $i){
                    $group[] =& $this->form->createElement("static", null,null,"-");

                } else {
                    $group[] =& $this->form->createElement("select", $field,null,$know_eachother);
                }
            }

            $this->form->addGroup($group, $groupname, "Child ".$i, $this->_GUIDelimiter, false);
            unset($group);
        }

         //$this->form->addElement("static", null, "<br><br>");
         $this->form->addElement('header', null, "Initials of the playmates are :");
         $this->form->addElement("static", null, "<br><br>");
         for ($i = 1; $i<= $this->total_peer; $i++) {
             if(!empty($this->localDefaults["peer_initials_".$i])) {
                 $this->form->addElement('static',"peer_initials_".$i, "Initials of child $i:"); 
             }
          }
        
    }
    function _page3(){
       
         $this->_generate_Questions(1); // playmate #1
         $this->form->addFormRule(array(&$this, 'Peer_Rules'));
    }
    function _page4() {
        $this->_generate_Questions(2); // playmate #2   
        $this->form->addFormRule(array(&$this, 'Peer_Rules'));
    }
    function _page5() {
        $this->_generate_Questions(3); // playmate #3   
        $this->form->addFormRule(array(&$this, 'Peer_Rules'));
    }
    function _page6() {
        $this->_generate_Questions(4); // playmate #4   
        $this->form->addFormRule(array(&$this, 'Peer_Rules'));
    }
    function _page7() {
        $this->_generate_Questions(5); // playmate #5   
        $this->form->addFormRule(array(&$this, 'Peer_Rules'));
    }

    function _generate_Questions($playmate) {
         $i = $playmate;
         $this->form->addElement('header', 'instrument_title', "Peer Social Contact Questionnaire");
         $this->form->addElement('static', 'peer_initials_'.$i, "Playmate #".$i." : ");
        
         $group[] = &$this->form->createElement("select",'age_yrs_playmate_'.$i,null,$this->age_yrs);
         $group[] = &$this->form->createElement("select",'age_mos_playmate_'.$i,null,$this->age_mos);
         $this->form->addGroup($group, "age_playmate".$i, "Age ", null, false);
         unset($group);

         $this->addSelect('gender_playmate_'.$i,'Gender ', $this->gender);
         $this->form->addElement('static', null, "<br /><br />");
         $questions = array("q1_number_playtimes_playmate".$i=> "1. How many times did they play together in the last three months <BR>$this->indent in your home?","q2_avg_playtime_playmate".$i=>"2. How long are they together in an average play time? (mins)");
         foreach($questions as $field=>$label) {
             $group [] = $this->createText($field, $label);
             $this->addGroup($group, $field . "_group", $label, null, false);
             unset($group);
             $this->addGroupRule($field . "_group", array(array(array("Value must be numeric.", 'numeric'))));
         }
         $this->addSelect('q3_related_playmate'.$i,"3. How do they know each other?", $this->q3_options);
         
         $group [] = $this->createText('q3_related_other_playmate'.$i,$this->indent."If Other please specify");
         $this->addGroup($group,'q3_related_other_playmate'.$i."_group",$this->indent."If Other please specify",null,false);
         unset($group);
         $rules_array = array("q3_related_playmate.$i{@}=={@}other");
         $this->XINRegisterRule('q3_related_other_playmate'.$i, $rules_array, "Please specify relationship", 'q3_related_other_playmate'.$i.'_group');

         $this->addSelect('q4_playarea_playmate'.$i,"4. Where do they usually play?", $this->q4_options);
        
         $group [] = $this->createText('q4_playarea_other_playmate'.$i,$this->indent."If Other please specify");
         $this->addGroup($group,'q4_playarea_other_playmate'.$i."_group",$this->indent."If Other please specify",null,false);
         unset($group);
         $rules_array = array("q4_playarea_playmate.$i{@}=={@}mostly_other");
         $this->XINRegisterRule('q4_playarea_other_playmate'.$i, $rules_array, "Please specify play area", 'q4_playarea_other_playmate'.$i.'_group');

         $this->addSelect('q5_proximity_playmate'.$i,"5. How close does this playmate live to your house?", 
                          $this->q5_options);
         $this->addSelect('q6_sameschool_playmate'.$i,"6. Is this playmate in your child's school now?", 
                          $this->yesNo);
         $this->addSelect('q7_samechildcare_playmate'.$i,"7. Is this playmate in your child's childcare now?",
                          $this->yesNo);
         $this->addSelect('q8_specialneeds_playmate'.$i,"8. What special needs does this playmate have?",
                          $this->q8_options);
         $group [] = $this->createText('q8_specialneeds_other_playmate'.$i,$this->indent."If Other please specify");
         $this->addGroup($group,'q8_specialneeds_other_playmate'.$i."_group",$this->indent."If Other please specify",null,false);
         unset($group);
         $rules_array = array("q8_specialneeds_playmate.$i{@}=={@}other");
         $this->XINRegisterRule('q8_specialneeds_other_playmate'.$i, $rules_array, "Please specify play area", 'q8_specialneeds_other_playmate'.$i.'_group');

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
         $this->addSelect('q17_how_involved_playmate'.$i,"17. In a typical play session, how closely involved are they with <BR>$this->indent each other during play?", $this->q17_options);
         $this->form->addElement('static',null,"18. What percentage of time were the play dates arranged by:");
        
         $q18 = array("q18_arrangeplay_you_playmate".$i=>$this->indent."You (%) ",
                      "q18_arrangeplay_yourchild_playmate".$i=>$this->indent."Your child (%)",
                      "q18_arrangeplay_other_playmate".$i=>$this->indent."Other family or friends (%) ");
         foreach($q18 as $field=>$label) {
             $group [] = $this->createText($field, $label);
             $this->addGroup($group, $field . "_group", $label, null, false);
             unset($group);
             $this->addGroupRule($field . "_group", array(array(array("Value must be numeric.", 'numeric'))));
         }

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

         $this->form->addElement('static',null,"22. How much does your child need your help during play with <BR>$this->indent this playmate in the following areas?");
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
            if($values["q3_related_playmate".$i] == 'other'&& empty($values["q3_related_other_playmate".$i]) ) {
                $errors["q3_related_other_playmate".$i."_group"] = "Please specify relationship";    
            }

            if($values["q4_playarea_playmate".$i] == 'mostly_other' && empty($values["q4_playarea_other_playmate".$i])) {
                $errors["q4_playarea_other_playmate".$i."_group"] = "Please specify play area";    
            }
            if($values["q8_specialneeds_playmate".$i] == 'other' && empty($values["q8_specialneeds_other_playmate".$i])) {
                $errors["q8_specialneeds_other_playmate".$i."_group"] = "Please specify play area";
            }

        }
        return $errors;
    }
    
}
