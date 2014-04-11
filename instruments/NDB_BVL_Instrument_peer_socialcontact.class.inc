<?php
class NDB_BVL_Instrument_peer_socialcontact extends NDB_BVL_Instrument
{
    //Commonly used level of indentation;
    var $indent = "&nbsp;&nbsp;&nbsp;&nbsp;";

    var $rating = array(''=>NULL, '1_very_rarely'=>"1. Very Rarely", '2_rarely'=>"2. Rarely", 
                        '3_occasionally'=>"3. Occasionally",'4_somewhat_often'=>'4. Somewhat Often',
                        '5_often'=>'5. Often','6_very_often'=>'6. Very Often','refused_dontknow'=>"Refused/I Don't Know");
    var $respondent = array(''=>NULL,'mother'=>'Mother','father'=>'Father','other'=>'Other');
    var $num_playmates = array(''=>NULL,0=>0,1=>1,2=>2,3=>3,4=>4,5=>5);
    var $total_peer = 5;
    var $age_yrs = array(''=>NULL,'0'=>'0yrs','1'=>'1 yr','2'=>'2 yrs','3'=>'3 yrs','4'=>'4 yrs','5'=>'5 yrs',
                         '6'=>'6 yrs','7'=>'7 yrs','8'=>'8 yrs','9'=>'9 yrs','10'=>'10 yrs',
                         '11'=>'11 yrs','12'=>'12 yrs','13'=>'13 yrs','14'=>'14 yrs','15'=>'15 yrs',
                         'refused_dontknow'=>"Refused/I Don't Know");
    var $age_mos = array(''=>NULL,'0'=>'0 mos','1'=>'1 mos','2'=>'2 mos','3'=>'3 mos','4'=>'4 mos','5'=>'5 mos',
                         '6'=>'6 mos','7'=>'7 mos','8'=>'8 mos','9'=>'9 mos','10'=>'10 mos',
                         '11'=>'11 mos','12'=>'12 mos','refused_dontknow'=>"Refused/I Don't Know");
    var $gender = array(''=>NULL,'boy'=>'Boy','girl'=>'Girl','refused_dontknow'=>"Refused/I Don't Know");
    var $q3_options = array(''=>NULL, 'cousins'=>'Cousins','neighbors'=>'Neighbors',
                            'classmates'=>'Classmates','parent_friend_child'=>"Parent's friend's child",
                            'other'=>'Other','refused_dontknow'=>"Refused/I Don't Know");
    var $q4_options = array(''=>NULL,'mostly_your_home'=>'Mostly your home',
                            'mostly_playmate_home'=>'Mostly playmates home','equally_both'=>'Equally both',
                            'mostly_other'=>'Mostly other (such as playground)','refused_dontknow'=>"Refused/I Don't Know");
    var $q5_options = array(''=>NULL,'walking_distance'=>'Walking distance',
                            'short_drive'=>'Short drive(up to 15min)','long_drive'=>'Long drive(> 15min)',
                            'refused_dontknow'=>"Refused/I Don't Know");
    var $yesNo = array(''=>NULL,'yes'=>'Yes','no'=>'No','refused_dontknow'=>"Refused/I Don't Know");
    var $q8_options = array(''=>NULL,'none'=>'None','dont_know'=>"Don't know",'autism'=>'Autism',
                            'other_developmental_delay'=>'Other developmental delay',
                            'speech_language_delay'=>'Speech or language delay',
                            'other'=>'Other','refused_dontknow'=>"Refused/I Don't Know");
    var $q9_options = array(''=>NULL,'really_likes'=>'Really likes','likes'=>'Likes',
                            'pretty_neutral'=>'Pretty neutral','just_tolerates'=>'Just tolerates',
                            'refused_dontknow'=>"Refused/I Don't Know");
    var $q10_options = array(''=>NULL,'really_likes'=>'Really likes','likes'=>'Likes',
                            'pretty_neutral'=>'Pretty neutral','just_tolerates'=>'Just tolerates',
                            'refused_dontknow'=>"Refused/I Don't Know");

    var $q11_options = array(''=>NULL,'very_well'=>'Very well','okay'=>'Okay',
                             'not_very_well'=>'Not very well','refused_dontknow'=>"Refused/I Don't Know");
    var $q12_options = array(''=>NULL,'my_child'=>'My child','playmate'=>'Playmate','both'=>'Both',
                             'adult'=>'Adult','refused_dontknow'=>"Refused/I Don't Know");
    var $q13_options = array(''=>NULL,'positive'=>'Positive','neutral'=>'Neutral','negative'=>'Negative',
                             'refused_dontknow'=>"Refused/I Don't Know");
    var $q14_options = array(''=>NULL,'very_excited'=>'Very Excited','active'=>'Active','calm'=>'Calm',
                             'refused_dontknow'=>"Refused/I Don't Know");
    var $q15_options = array(''=>NULL,'frequently'=>'Frequently','occasionally'=>'Occasionally',
                             'rarely'=>'Rarely','refused_dontknow'=>"Refused/I Don't Know");
    var $q16_options = array(''=>NULL,'ends_play'=>'Ends play','major_disruption'=>'Major disruptions',
                             'minor_disruption'=>'Minor disruption','no_disruption'=>'No disruption',
                             'refused_dontknow'=>"Refused/I Don't Know");
    var $q17_options = array(''=>NULL,'lot_of_interaction'=>'A lot of interaction',
                             'stay_close_no_interaction'=>'Stay close but do not interact much',
                             'dont_stay_close_or_interact'=>'Do not stay close or interact much',
                             'refused_dontknow'=>"Refused/I Don't Know");
    var $q19_options = array(''=>NULL,'very_difficult'=>'Very difficult',
                             'somewhat_difficult'=>'Somewhat difficult',
                             'not_difficult'=>'Not difficult at all',
                             'refused_dontknow'=>"Refused/I Don't Know"); 
    var $q20_options = array(''=>NULL,'very_stressful'=>'Very stressful',
                             'somewhat_stressful'=>'Somewhat stressful',
                             'not_stressful'=>'Not stressful at all',
                             'refused_dontknow'=>"Refused/I Don't Know");
    var $q21_options = array(''=>NULL,'frequently'=>'Frequently','occasionally'=>'Occasionally',
                             'little_or_none'=>'Little-or-none','refused_dontknow'=>"Refused/I Don't Know");
    var $q23_options = array(''=>NULL,'yes'=>'Yes','no'=>'No (go to next section)','refused_dontknow'=>"Refused/I Don't Know");
    var $q24_options = array(''=>NULL,'yes'=>'Yes','no'=>'No','refused_dontknow'=>"Refused/I Don't Know");
    var $activity_desc = array(''=>NULL,'religious'=>'a. Religious activity','play_group'=>'b. Play group','sports'=>'c. Sports(soccer, dance etc)','recreational'=>'d. Recreational (music, art, reading, etc.)','other'=>'e. Other','refused_dontknow'=>"Refused/I Don't Know");
    var $special_service = array(''=>NULL,'occupational_physical'=>'a. Occupational/Physical therapy','lang_speech'=>'b. Language or speech therapy','behavior'=>'c. Behavior therapy','social_skills'=>'d. Social skills or play group');
    var $numdays_week = array(''=>NULL,'0'=>'0','1'=>'1','2'=>'2','3'=>'3','4'=>'4','5'=>'5','6'=>'6','7'=>'7','refused_dontknow'=>"Refused/I Don't Know");
    var $numhrs_day = array(''=>NULL,'0'=>'0','1'=>'1','2'=>'2','3'=>'3','4'=>'4','5'=>'5','6'=>'6','7'=>'7','8'=>'8','9'=>'9',
                            '10'=>'10','11'=>'11','12'=>'12','13'=>'13','14'=>'14','15'=>'15','16'=>'16','17'=>'17','18'=>'18',
                            '19'=>'19','20'=>'20','21'=>'21','22'=>'22','23'=>'23','24'=>'24','refused_dontknow'=>"Refused/I Don't Know");
    var $promote_play = array(''=>NULL,'almost_always'=>'a. Almost always','sometimes'=>'b. Sometimes','never'=>'c. Never', 'refused_dontknow'=>"Refused/I Don't Know");
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
       // $this->dateTimeFields = array("datecompleted");
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
        } else {
            $this->localDefaults['total_peer'] = 5; //by default we want the total playmates as 5 in order for the data dictionary to work properly
        }
        
        // required fields for data entry completion status
        $this->_requiredElements = array('total_playmates');
        /*
        for($i = 1; $i <= $record['total_playmates']; $i++) {
              array_push($this->_requiredElements,"age_yrs_playmate_".$i );     
        }
        */
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
        
       // $this->addBasicDate('datecompleted', "Today's date:", $this->dateOptions);
        $this->addSelect('respondent',"Completed by :", $this->respondent);
        
        $group [] = $this->createText('respondent_other',$this->indent."If Other please specify");
        $this->addGroup($group,"respondent_other_group",$this->indent."If Other please specify",null,false);
        unset($group);
        $rules_array = array("respondent{@}=={@}other");
        $this->XINRegisterRule('respondent_other', $rules_array, "Please specify relationship", 'respondent_other_group');

        $this->form->addElement('header', null, "Section 1: Individual Playmates");
        $this->form->addElement('static', 'lorisSubHeader', "We would like to know about the children your child plays with regularly outside of<BR>school, childcare or group activities. Please do not include siblings or other<BR>relatives living in your home. List the children your child plays with at least every<BR>three months and who are at least 2 years old and no more than 10 years old.<BR>There are spaces for you to list up to five children; however, most children do not <BR>have that many regular playmates. It's easy to forget some children when making<BR>such lists. Please think about children your child knows in various groups (such as <BR> cousins, neighbors, classmates, children of your friends, etc) or settings (such as <BR>church, childcare, recreational activities, the gym, etc.). If there are more than five<BR>children, please list the ones your child plays with most frequently.");

        $this->addSelect('total_playmates',"Please choose the number of playmates your child has :", $this->num_playmates);
        $this->form->addElement('static', 'lorisSubHeader', "Please list the initals of the children your child plays with regularly <BR>the lines below:");
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
        
       // $this->form->addElement("static",null,"In the table below indicate which children know each other.<BR>You must select `Yes` or `No` fields to save this form.<BR>");
        $db =& Database::singleton();
        if(Utility::isErrorX($db)) {
            print "Could not connect to database: ".$db->getMessage();
        }
        $numplaymates = $db->pselectOne("SELECT total_playmates FROM ".$this->table." WHERE CommentID=:cid",
                array('cid' =>$this->getCommentID()));

        if (Utility::isErrorX($numplaymates)) {
            print "Query has failed to select: ".$numplaymates->getMessage();
        }
          if(isset($_GET["key"])) {
            $key = $_GET["key"]; 
        }

        $colspan = $numplaymates -1; 
	if($numplaymates > 1) {
		$group[] = &$this->form->createElement("static", null, null,"");
		$this->form->addGroup($group,"page2_header","<td colspan= $colspan>In the table below indicate which of your children's playmates know<BR> each other. You must select 'Yes' or 'No' in all field to save this form.</td>", null,false);
 		unset($group);

	} else if($numplaymates == 1) {
                $group[] = &$this->form->createElement("static", null, null,""); 
                
                $this->form->addGroup($group,"page2_header","<td colspan= $colspan>In the previous page you have indicated $numplaymates playmate(s).<BR> Please click 'Save and Continue' to go to the next section. </td>", null,false);
                unset($group);

	} else if($numplaymates == 0) {
                 $group[] = &$this->form->createElement("static", null, null,"");

                $this->form->addGroup($group,"page2_header","<td colspan= $colspan>In the previous page you have indicated $numplaymates playmate(s). <BR>Click here go to the next section:<a href=\"survey.php?key=$key&pageNum=7\"><font color=\"#0000FF\"> <u>Section 2 </u></font></a> </td>", null,false);
                unset($group);

        }
        $this->localDefaults['total_peer'] = $numplaymates;
        if($this->localDefaults['total_peer'] > 1) {
            $group[] = &$this->form->createElement("static", null, null, "Child 1");
        }
        if($this->localDefaults['total_peer'] >= 2) {
            $group[] = &$this->form->createElement("static", null, null, "Child 2");
        }
        if($this->localDefaults['total_peer'] >= 3) {
            $group[] = &$this->form->createElement("static", null, null, "Child 3");
        }
        if($this->localDefaults['total_peer'] >= 4) {
            $group[] = &$this->form->createElement("static", null, null, "Child 4");
        }
        if($this->localDefaults['total_peer'] == 5) {
            $group[] = &$this->form->createElement("static", null, null, "Child 5");
        }  
        //$this->form->addGroup($group, "table_headers","<td colspan= 2></td>" , $this->_GUIDelimiter, false);
        if($this->localDefaults['total_peer'] >1 ) {
            $this->form->addGroup($group, "table_headers",null , $this->_GUIDelimiter, false);
            unset($group);
        }
        $know_eachother = array(""=>null,"yes"=>"Yes","no"=>"No","refused_dontknow"=>"Refused/I Don't Know");
        for($i = 1; $i < $this->localDefaults['total_peer']; $i++){
            $groupname = $i."_group";
            for($j = 1; $j <= $this->localDefaults['total_peer']; $j++ )  {
                $field = "know_".$i."_".$j;
                if($j <= $i){
                    $group[] =& $this->form->createElement("static", null,null,"-");

                } else {
                    $group[] =& $this->form->createElement("select", $field,null,$know_eachother);
                }
            $this->XINRegisterRule($field, array("$field{@}=={@}NEVER_REQUIRED"), $groupname);
            }
            $this->form->addGroup($group, $groupname, "Child ".$i, $this->_GUIDelimiter, false);
            unset($group);
        }
	if($this->localDefaults['total_peer'] > 0) {
		$group[] = &$this->form->createElement("static", null, null,"");
		$this->form->addGroup($group,"page2_header","<td colspan= $colspan>Initials of the playmates are :<BR></td>", null,false);
		unset($group);
	}
         for ($i = 1; $i<= $this->localDefaults['total_peer']; $i++) {
             if(!empty($this->localDefaults["peer_initials_".$i])) {
               $group[] =& $this->form->createElement("static", "peer_initials_".$i,null,null);
               $this->form->addGroup($group,$i."_header","<td colspan= $colspan>Initials of child $i:</td>", null,false);
               unset($group);

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
    function _page8()
    {
       $this->form->addElement('header', 'section2_header', "Section 2: Educational or Child Care Activities");

       $this->form->addElement('static', 'lorisSubHeader',"Aside from individual play activities, children participate in group activities in educational and <BR>childcare placements with peers. We'd like to know a little about your child's current placements.<BR><BR>If your child is not in school or childcare, please go to next section. Press 'Save and Continue' <BR>at the bottom of screen to continue with the survey.");
       $this->form->addElement('header','section2_a',"School");
        
       $this->addSelect('q23_childin_school',"23. Is your child in school or preschool?",$this->q23_options);
       $this->XINRegisterRule('q23_childin_school', array("q23_childin_school{@}=={@}NEVER_REQUIRED"), "Please specify");

       $this->addSelect('q24_childin_spneeds_school',"24. Is your child in a classroom which specializes in educating children<BR>$this->indent with special educational needs?",$this->q23_options);
      $this->XINRegisterRule('q24_childin_spneeds_school', array("q23_childin_school{@}=={@}yes"), "Please specify"); 
       
      $this->addSelect('q25_school_numdays_perweek','25. How many days per week is your child in school?', $this->numdays_week);
      $this->XINRegisterRule('q25_school_numdays_perweek', array("q25_school_numdays_perweek{@}=={@}NEVER_REQUIRED"));

      $this->addSelect('q26_school_numhrs_perday','26. How many hours per day is your child in school?', $this->numhrs_day);
      $this->XINRegisterRule('q26_school_numhrs_perday', array("q26_school_numhrs_perday{@}=={@}NEVER_REQUIRED"));
      
      $questions = array('q27_numchildren_perclass'=>'27. How many children are in the (primary) classroom at school?',
                         'q28_numchildren_specialneeds'=>'28. How many of the children have special needs in the (primary)<BR> classroom at school?');
       foreach($questions as $field=>$label) {
           $group [] = $this->createText($field, $label);
           $this->addGroup($group, $field . "_group", $label, null, false);
           $this->XINRegisterRule($field, array("$field{@}=={@}NEVER_REQUIRED"));
           unset($group);
           $this->addGroupRule($field . "_group", array(array(array("Value must be numeric.", 'numeric'))));
       }
       $this->form->addElement('header','section2_b',"Childcare");

       $this->addSelect('q29_childin_childcare',"29. Is your child in a childcare setting?",$this->q23_options);
       $this->XINRegisterRule('q29_childin_childcare', array("q29_childin_childcare{@}=={@}NEVER_REQUIRED"), "Please specify");

       $this->addSelect('q30_childin_spneeds_childcare',"30. Is the childcare setting a center which specializes in educating<BR>$this->indent children  with special educational needs?",$this->q23_options);
       $this->XINRegisterRule('q30_childin_spneeds_childcare', array("q29_childin_childcare{@}=={@}yes"), "Please specify");
       
       $this->addSelect('q31_childcare_numdays_perweek','31. How many days per week is your child in a childcare setting?', $this->numdays_week);
       $this->XINRegisterRule('q31_childcare_numdays_perweek', array("q31_childcare_numdays_perweek{@}=={@}NEVER_REQUIRED"));
       
       $this->addSelect('q32_childcare_numhrs_perday','32. How many hours per day is your child in a childcare setting?',$this->numhrs_day);
       $this->XINRegisterRule('q32_childcare_numhrs_perday',array("q32_childcare_numhrs_perday{@}=={@}NEVER_REQUIRED"));

       $questions = array('q33_numchildren_perclass'=>'33. How many children are in the (primary) classroom? at childcare',
               'q34_numchildren_specialneeds'=>"34. How many of the children have special needs in the (primary)<BR> $this->indent classroom at childcare?");
       foreach($questions as $field=>$label) {
           $group [] = $this->createText($field, $label);
           $this->addGroup($group, $field . "_group", $label, null, false);
           $this->XINRegisterRule($field, array("$field{@}=={@}NEVER_REQUIRED"));
           unset($group);
           $this->addGroupRule($field . "_group", array(array(array("Value must be numeric.", 'numeric'))));
       }

    }
    function _page9()
    {
        $this->form->addElement('header', 'section3_header', "Section 3: Community Group Activities");

        $this->form->addElement('static', 'lorisSubHeader',"In addition to school or childcare, some children regularly participate in other group<BR>activities with their peers, such as swimming lessons, soccer, or classes outside of school.<BR>If your child participates in such activities, please list up to three groups below.<BR><BR>If your child does not participate in any such groups, please go to the next section.<BR>Press 'Save and Continue' at the bottom of screen to continue with the survey.<BR><BR>**Please note that groups designed to provide special services for children with<BR>developmental problems are to be included in the next section**");
        for($i = 1; $i <= 3; $i++) {
            
            $this->form->addElement('header', 'group_header'.$i, " Group $i");

            $group [] = $this->createText("activity_".$i,"Type or name of group activity :");
            $this->addGroup($group,"activity_".$i."_group","Type or name of group activity :",null, false);
            $this->XINRegisterRule('activity_'.$i, array("activity_$i{@}=={@}NEVER_REQUIRED"), null, "activity_".$i."_group");
            unset($group);
            $this->addSelect('activity_desc_'.$i,"Which one of the following best describes the group",$this->activity_desc);
            $this->XINRegisterRule('activity_desc_'.$i, array("activity_desc_$i{@}=={@}NEVER_REQUIRED") );

            $group [] = $this->createText('activity_other'.$i,$this->indent."If Other please specify");
            $this->addGroup($group,'activity_other'.$i."_group",$this->indent."If Other please specify",null,false);
            unset($group);
            $rules_array = array("activity_$i{@}=={@}other");
            $this->XINRegisterRule('activity_other'.$i, $rules_array, "Please specify activity", 'activity_other'.$i.'_group');

            $questions = array('activity'.$i."_meet_permonth"=>'How many times each month does the group meet?',
                               'activity'.$i."_numchildren_participate"=>"How many children participate in the group?",
                               'activity'.$i."_numchildren_class"=>"How many of these children are in your child's classroom at school or daycare?",
                               'activity'.$i."_numchildren_spneeds"=>"How many of these children have special needs(if known)?");
            foreach($questions as $field=>$label) {
                $group [] = $this->createText($field, $label);
                $this->addGroup($group, $field . "_group", $label, null, false);
                $this->XINRegisterRule($field, array("$field{@}=={@}NEVER_REQUIRED"),$field . "_group");
                unset($group);
                $this->addGroupRule($field . "_group", array(array(array("Value must be numeric.", 'numeric'))));
            }

        }

    }
    function _page10()
    {
        $this->form->addElement('header', 'section4_header', "Section 4: Groups for Special Services");

        $this->form->addElement('static', 'lorisSubHeader',"Some children who need special services outside of school, such as speech <BR>or physical therapy, receive them in a group setting. If your child regularly participates<BR> with other children in such therapeutic groups, please list up to three of them below.<BR><BR>If your child does not participate in such groups, leave it blank and <BR>press 'Save and Continue' at the bottom of screen to continue with the survey.");
        for($i = 1; $i <= 3; $i++) {

            $this->form->addElement('header', 'group_header'.$i, " Group $i");

            $group [] = $this->createText("special_service_".$i,"Type or name of group activity :");
            $this->addGroup($group,"special_service_".$i."_group","Type or name of group activity :",null, false);
            unset($group);
            $this->XINRegisterRule('special_service_'.$i, array("special_service_.$i{@}=={@}NEVER_REQUIRED"), null, "special_service_".$i."_group");
            $this->addSelect('special_service_desc_'.$i,"Which one of the following best describes the group",$this->special_service);
            $this->XINRegisterRule('special_service_desc_'.$i, array("special_service_$i{@}=={@}NEVER_REQUIRED") );

            $questions = array('special_service'.$i."_meet_permonth"=>'How many times each month does the group meet?',
                    'special_service'.$i."_numchildren_participate"=>"How many children participate in the group?",
                    'special_service'.$i."_numchildren_class"=>"How many of these children are in your child's classroom at school or daycare?");
            foreach($questions as $field=>$label) {
                $group [] = $this->createText($field, $label);
                $this->addGroup($group, $field . "_group", $label, null, false);
                $this->XINRegisterRule($field, array("$field{@}=={@}NEVER_REQUIRED"),$field . "_group");
                unset($group);
                $this->addGroupRule($field . "_group", array(array(array("Value must be numeric.", 'numeric'))));
            }

        }

    }
   function _page11() 
  {
       $this->form->addElement('header', 'section4_header', "Section 5: Effects of Autism on Children's play");
       $this->form->addElement('static','lorisSubHeader', "Please complete the following section if your child has ever been diagnosed with autism<BR> (fill out for either a current diagnosis or a history of autism in the past)");
       $this->addSelect('q1_autism_effect_discuss', "1. When trying to help your child establish a friendship with a peer, do you discuss<BR> issues related to autism with peer's parents in order to promote better play?", $this->promote_play);
       $this->XINRegisterRule('q1_autism_effect_discuss',array("q1_autism_effect_discuss{@}=={@}NEVER_REQUIRED"));
       $strategy = array(''=>NULL, 'detail_about_child_strength_weakness'=>"a. Go into a lot of detail about your child's strengths and weaknesses", 
                         'no_details_not_minimizing_issues_either'=>'b. Not many details, but not minimizing issues either',
                         'minimize_issues_comfortable'=>'c. Minimize the issues to try to help them feel comfortable',
                         'never_discuss'=>'d. Never discuss it','refused_dontknow'=>"Refused/I Don't Know"); 
       $this->addSelect('q2_autism_effect_discuss_parents', "2. If you do discuss these issues with parents to promote better play with peers,<BR> which strategy best describes your approach? ", $strategy);
       $this->XINRegisterRule('q2_autism_effect_discuss_parents',array("q2_autism_effect_discuss_parents{@}=={@}NEVER_REQUIRED"));

       $avoid_arranging = array(''=>NULL,'frequently'=>'a. Frequently','occasionally'=>'b. Occasionally','rarely_never'=>'c. Rarely or never','refused_dontknow'=>"Refused/I Don't Know");
       $this->addSelect('q3_autism_effect_difficulty_arrangingplay', "3. How often have you experienced difficulty in arranging play opportunities for your<BR> child which you believe is due to your child having autism? ", $avoid_arranging);
       $this->XINRegisterRule('q3_autism_effect_difficulty_arrangingplay',array("q3_autism_effect_difficulty_arrangingplay{@}=={@}NEVER_REQUIRED"));

       $this->addSelect('q4_autism_effect_avoid_arranding_play', "4. How often have you avoided arranging play opportunities for your child due to fear<BR> of rejection due to your child having autism?", $avoid_arranging);
       $this->XINRegisterRule('q4_autism_effect_avoid_arranding_play',array("q4_autism_effect_avoid_arranding_play{@}=={@}NEVER_REQUIRED"));
       
       $this->addSelect('q5_autism_effect_concernc_childskill',"5. How often have you avoided arranging play opportunities for your child due to concern <BR>that your child's social skills are not good enough?", $avoid_arranging);
      $this->XINRegisterRule('q5_autism_effect_concernc_childskill',array("q5_autism_effect_concernc_childskill{@}=={@}NEVER_REQUIRED"));
      
      $restrict = array(''=>NULL, 'very_much'=>'a. Very much','somewhat'=>'b. Somewhat','not_at_all'=>'c. Not at all','refused_dontknow'=>"Refused/I Don't Know");
      $this->addSelect('q6_autism_effect_restrict_socialtime',"6. To what extent do the various medical and educational services your child requires<BR> restrict the amount of time your child has for social opportunities with peers?", $restrict);
      $this->XINRegisterRule('q6_autism_effect_restrict_socialtime',array("q6_autism_effect_restrict_socialtime{@}=={@}NEVER_REQUIRED"));
      
     $school = array(''=>NULL, 'very_satisfied'=>'a. Very satisfied','somewhat_satisfied'=>'b. Somewhat satisfied','not_satisfied'=>'c. Not satisfied','extremely_dissatisfied'=>'d. Extremely dissatisfied','not_in_school'=>'e. Not in school' ,'refused_dontknow'=>"Refused/I Don't Know"); 
     $this->addSelect('q7_autism_effect_satisfaction_schoolstaff', "7. How satisfied are you with how the school staff help your child get along with peers?", $school);
     $this->XINRegisterRule('q7_autism_effect_satisfaction_schoolstaff',array("q7_autism_effect_satisfaction_schoolstaff{@}=={@}NEVER_REQUIRED"));

      $daycare = array(''=>NULL, 'very_satisfied'=>'a. Very satisfied','somewhat_satisfied'=>'b. Somewhat satisfied','not_satisfied'=>'c. Not satisfied','extremely_dissatisfied'=>'d. Extremely dissatisfied','not_in_daycare'=>'e. Not in daycare' ,'refused_dontknow'=>"Refused/I Don't Know");
      $this->addSelect('q8_autism_effect_satisfaction_daycarestaff', "8. How satisfied are you with how the daycare staff help your child get along with peers?", $daycare);
      $this->XINRegisterRule('q8_autism_effect_satisfaction_daycarestaff',array("q8_autism_effect_satisfaction_daycarestaff{@}=={@}NEVER_REQUIRED"));
      
      $q9_options = array(''=>NULL, 'mostly'=>'Mostly','some'=>'Some','rarely'=>'Rarely','refused_dontknow'=>"Refused/I Don't Know"); 
      $this->form->addElement('static',null,"9. To what extent does your child tend to play with each of the groups listed below?");
      $questions = array('q9a_autism_effect_other_children_autism'=>'a. Other children with autism',
                 'q9b_autism_effect_other_children_devdelay'=>'b. Other children with developmental delays',
                 'q9c_autism_effect_sameage'=>'c. Typically developing children -same age',
                 'q9d_autism_effect_younger'=>'d. Typically developing children -younger',
                 'q9e_autism_effect_older'=>'e. Typically developing children -older');

      foreach($questions as $qstn=>$desc) {
             $this->addSelect($qstn,$this->indent.$desc, $q9_options);
             $this->XINRegisterRule($qstn, array("$qstn{@}=={@}NEVER_REQUIRED"));

         }

      $this->form->addElement('static',null,"10. Which group of peers does your child play with the best? Please rank order 1 through 5.");
        $questions = array('q10a_autism_effect_other_children_autism'=>'a. Other children with autism',
                 'q10b_autism_effect_other_children_devdelay'=>'b. Other children with developmental delays',
                 'q10c_autism_effect_sameage'=>'c. Typically developing children -same age',
                 'q10d_autism_effect_younger'=>'d. Typically developing children -younger',
                 'q10e_autism_effect_older'=>'e. Typically developing children -older');

      foreach($questions as $field=>$label) {
             $group [] = $this->createText($field, $label);
             $this->addGroup($group, $field . "_group",$this->indent. $label, null, false);
             $this->XINRegisterRule($field,array("$field{@}=={@}NEVER_REQUIRED"),$field . "_group");
             unset($group);
             $this->addGroupRule($field . "_group", array(array(array("Value must be numeric.", 'numeric'))));
         }

       $this->addBasicTextArea("q11_comments", "11. Feel free to describe any other ways in which you have noticed that having autism has<BR> affected your child's social contacts with peers:");
       $this->XINRegisterRule('q11_comments', array('q11_comments{@}=={@}NEVER_REQUIRED'));
 
   } 
   function _generate_Questions($playmate) {
         $i = $playmate;
         $this->form->addElement('header', 'instrument_title', "Peer Social Contact Questionnaire");

         $this->form->addElement('static', 'lorisSubHeader',"Now, we would like to find out more about your child's relationship with each individual playmate.<BR>Answer the questions below in relationship to their contact in the last three months.");
        if(isset($_GET["key"])) {
            $key = $_GET["key"];
        }
        $db =& Database::singleton();
        if(Utility::isErrorX($db)) {
            print "Could not connect to database: ".$db->getMessage();
        }

        $numplaymates = $db->pselectOne("SELECT total_playmates FROM ".$this->table." WHERE CommentID=:cid",
                array('cid' =>$this->getCommentID()));

        if (Utility::isErrorX($numplaymates)) {
            print "Query has failed to select: ".$numplaymates->getMessage();
        }

         if($playmate > $numplaymates) {
              $this->form->addElement('static', 'lorisSubHeader',"<strong>NOTE: You only need to fill this form if the playmate initals are specified below.<BR>If no initials are specified click here go to the next section:<a href=\"survey.php?key=$key&pageNum=7\"><font color=\"#0000FF\"> <u>Section 2 </u></font></a> <strong>");

         } else {
              $this->form->addElement('static', 'lorisSubHeader',"<strong>NOTE: You only need to fill this form if the playmate initals are specified below.<strong>");
         }
         $this->form->addElement('static', 'peer_initials_'.$i, "Playmate #".$i." : ");
        
         $group[] = &$this->form->createElement("select",'age_yrs_playmate_'.$i,null,$this->age_yrs);
         $group[] = &$this->form->createElement("select",'age_mos_playmate_'.$i,null,$this->age_mos);
         $this->form->addGroup($group, "age_playmate".$i."_group", "Age ", null, false);
         $this->XINRegisterRule('age_yrs_playmate_'.$i, array("age_yrs_playmate_$i{@}=={@}NEVER_REQUIRED"), "age_playmate".$i."_group");
         $this->XINRegisterRule('age_mos_playmate_'.$i, array("age_mos_playmate_$i{@}=={@}NEVER_REQUIRED"), "age_playmate".$i."_group");
         unset($group);

         $this->addSelect('gender_playmate_'.$i,'Gender ', $this->gender);
         $this->XINRegisterRule('gender_playmate_'.$i, array("gender_playmate_.$i{@}=={@}NEVER_REQUIRED"));
         
         $questions = array("q1_number_playtimes_playmate".$i=> "1. How many times on average did they play together in the last <BR>$this->indent three months in your home?","q2_avg_playtime_playmate".$i=>"2. How long are they together in an average play time? (in Minutes)");
         foreach($questions as $field=>$label) {
             $group [] = $this->createText($field, $label);
             $this->addGroup($group, $field . "_group", $label, null, false);
             $this->XINRegisterRule($field,array("$field{@}=={@}NEVER_REQUIRED"),$field . "_group");
             unset($group);
             $this->addGroupRule($field . "_group", array(array(array("Value must be numeric.", 'numeric'))));
         }
         $this->addSelect('q3_related_playmate'.$i,"3. How do they know each other?", $this->q3_options);
         $this->XINRegisterRule('q3_related_playmate'.$i, array("q3_related_playmate.$i{@}=={@}NEVER_REQUIRED"));

         $group [] = $this->createText('q3_related_other_playmate'.$i,$this->indent."If Other please specify");
         $this->addGroup($group,'q3_related_other_playmate'.$i."_group",$this->indent."If Other please specify",null,false);
         unset($group);
         $rules_array = array("q3_related_playmate$i{@}=={@}other");
         $this->XINRegisterRule('q3_related_other_playmate'.$i, $rules_array, "Please specify relationship", 'q3_related_other_playmate'.$i.'_group');

         $this->addSelect('q4_playarea_playmate'.$i,"4. Where do they usually play?", $this->q4_options);
         $this->XINRegisterRule('q4_playarea_playmate'.$i, array("q4_playarea_playmate.$i{@}=={@}NEVER_REQUIRED"));

         $group [] = $this->createText('q4_playarea_other_playmate'.$i,$this->indent."If Other please specify");
         $this->addGroup($group,'q4_playarea_other_playmate'.$i."_group",$this->indent."If Other please specify",null,false);
         unset($group);
         $rules_array = array("q4_playarea_playmate$i{@}=={@}mostly_other");
         $this->XINRegisterRule('q4_playarea_other_playmate'.$i, $rules_array, "Please specify play area", 'q4_playarea_other_playmate'.$i.'_group');

         $this->addSelect('q5_proximity_playmate'.$i,"5. How close does this playmate live to your house?", 
                          $this->q5_options);

         $this->XINRegisterRule('q5_proximity_playmate'.$i, array("q5_proximity_playmate.$i{@}=={@}NEVER_REQUIRED"));
        // $this->XINRegisterRule(''.$i, array(".$i{@}=={@}NEVER_REQUIRED"));
         $this->addSelect('q6_sameschool_playmate'.$i,"6. Is this playmate in your child's school now?", 
                          $this->yesNo);
         $this->XINRegisterRule('q6_sameschool_playmate'.$i, array("q6_sameschool_playmate.$i{@}=={@}NEVER_REQUIRED"));
         $this->addSelect('q7_samechildcare_playmate'.$i,"7. Is this playmate in your child's childcare now?",
                          $this->yesNo);
         $this->XINRegisterRule('q7_samechildcare_playmate'.$i, array("q7_samechildcare_playmate.$i{@}=={@}NEVER_REQUIRED"));
         $this->addSelect('q8_specialneeds_playmate'.$i,"8. What special needs does this playmate have?<BR>Press Ctrl+click or Cmd+click to select mutiple options",
                          $this->q8_options, "multiple size='8'");
         $this->_selectMultipleElements[] = 'q8_specialneeds_playmate'.$i;
         $this->XINRegisterRule('q8_specialneeds_playmate'.$i, array("q8_specialneeds_playmate.$i{@}=={@}NEVER_REQUIRED"));
         $group [] = $this->createText('q8_specialneeds_other_playmate'.$i,$this->indent."If Other please specify");
         $this->addGroup($group,'q8_specialneeds_other_playmate'.$i."_group",$this->indent."If Other please specify",null,false);
       //  $this->XINRegisterRule('q8_specialneeds_other_playmate'.$i, array("q8_specialneeds_other_playmate.$i{@}=={@}NEVER_REQUIRED"),'q8_specialneeds_other_playmate'.$i."_group");
         unset($group);
         $rules_array = array("q8_specialneeds_playmate$i{@}=={@}other");
         $this->XINRegisterRule('q8_specialneeds_other_playmate'.$i, $rules_array, "Please specify play area", 'q8_specialneeds_other_playmate'.$i.'_group');

         $this->addSelect('q9_yourchild_like_playmate'.$i,"9. How much does your child like this playmate?",
                          $this->q9_options);
         $this->XINRegisterRule('q9_yourchild_like_playmate'.$i, array("q9_yourchild_like_playmate.$i{@}=={@}NEVER_REQUIRED"));

         $this->addSelect('q10_like_yourchild_playmate'.$i,"10. How much does this playmate like your child?",
                          $this->q9_options);
         $this->XINRegisterRule('q10_like_yourchild_playmate'.$i, array("q10_like_yourchild_playmate.$i{@}=={@}NEVER_REQUIRED"));

         $this->addSelect('q11_getalong_playmate'.$i,"11. How well would you say they get along?",
                          $this->q11_options);
         $this->XINRegisterRule('q11_getalong_playmate'.$i, array("q11_getalong_playmate.$i{@}=={@}NEVER_REQUIRED"));

         $this->addSelect('q12_leading_play_playmate'.$i,"12. Who usually is leading or in control of the play?",
                          $this->q12_options);
         $this->XINRegisterRule('q12_leading_play_playmate'.$i, array("q12_leading_play_playmate.$i{@}=={@}NEVER_REQUIRED"));

         $this->addSelect('q13_typical_playtone_playmate'.$i,"13. What is the typical tone of the play?",
                          $this->q13_options);
         $this->XINRegisterRule('q13_typical_playtone_playmate'.$i, array("q13_typical_playtone_playmate.$i{@}=={@}NEVER_REQUIRED"));

         $this->addSelect('q14_typical_excitement_playmate'.$i,"14. What is the typical level of excitement?",
                          $this->q14_options);
         $this->XINRegisterRule('q14_typical_excitement_playmate'.$i, array("q14_typical_excitement_playmate.$i{@}=={@}NEVER_REQUIRED"));

         $this->addSelect('q15_num_conflicts_playmate'.$i,"15. How often do they have conflicts during play?",
                          $this->q15_options);
         $this->XINRegisterRule('q15_num_conflicts_playmate'.$i, array("q15_num_conflicts_playmate.$i{@}=={@}NEVER_REQUIRED"));

         $this->addSelect('q16_disruptive_playmate'.$i,"16. How disruptive are their conflicts?",
                          $this->q16_options);
         $this->XINRegisterRule('q16_disruptive_playmate'.$i, array("q16_disruptive_playmate.$i{@}=={@}NEVER_REQUIRED"));

         $this->addSelect('q17_how_involved_playmate'.$i,"17. In a typical play session, how closely involved are they with <BR>$this->indent each other during play?", $this->q17_options);
         $this->XINRegisterRule('q17_how_involved_playmate'.$i, array("q17_how_involved_playmate.$i{@}=={@}NEVER_REQUIRED"));

         $this->form->addElement('static',null,"18. What percentage of time were the play dates arranged by:");
        
         $q18 = array("q18_arrangeplay_you_playmate".$i=>$this->indent."You (%) ",
                      "q18_arrangeplay_yourchild_playmate".$i=>$this->indent."Your child (%)",
                      "q18_arrangeplay_other_playmate".$i=>$this->indent."Other family or friends (%) ");
         foreach($q18 as $field=>$label) {
             $group [] = $this->createText($field, $label);
             $this->addGroup($group, $field . "_group", $label, null, false);
             $this->XINRegisterRule($field, array("$field{@}=={@}NEVER_REQUIRED"),$field . "_group");
             unset($group);
             $this->addGroupRule($field . "_group", array(array(array("Value must be numeric. Please enter value without % symbol", 'numeric'))));
         }

         $this->addSelect('q19_arrange_contacts_playmate'.$i,"19. How difficult was it to arrange those contacts?", $this->q19_options);
         $this->XINRegisterRule('q19_arrange_contacts_playmate'.$i, array("q19_arrange_contacts_playmate.$i{@}=={@}NEVER_REQUIRED"));

         $this->addSelect('q20_stress_monitorplay_playmate'.$i,"20. How stressful is it usually for you to monitor play sessions?", $this->q20_options);
         $this->XINRegisterRule('q20_stress_monitorplay_playmate'.$i, array("q20_stress_monitorplay_playmate.$i{@}=={@}NEVER_REQUIRED"));

         $this->form->addElement('static',null,"21. How do you usually monitor the play at home?");
         $questions = array('q21_facililate_getalong_playmate'.$i=>'a. Directly facilitate by helping them get along',
                 'q21_participate_activity_playmate'.$i=>'b. Participate in the activity with children',
                 'q21_maintain_presence_playmate'.$i=>'c. Maintain presence (in childs view)',
                 'q21_outofview_listen_playmate'.$i=>'d. Out of view but listen to their ongoing activity',
                 'q21_outofview_notlisten_playmate'.$i=>'e. Out of view and can only hear outbursts or cries');

         foreach($questions as $qstn=>$desc) {
             $this->addSelect($qstn,$this->indent.$desc, $this->q21_options);
             $this->XINRegisterRule($qstn, array("$qstn{@}=={@}NEVER_REQUIRED"));

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
             $this->XINRegisterRule($qstn, array("$qstn{@}=={@}NEVER_REQUIRED"));
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
	    for($i= 1; $i<=5; $i++) {
		    $q18 = array("q18_arrangeplay_you_playmate".$i,
				    "q18_arrangeplay_yourchild_playmate".$i,
				    "q18_arrangeplay_other_playmate".$i);
		$total = $values["q18_arrangeplay_you_playmate".$i] + $values["q18_arrangeplay_yourchild_playmate".$i] +
                         $values["q18_arrangeplay_other_playmate".$i];
                if($total > 100 ) { 
                     $errors["q18_arrangeplay_you_playmate".$i."_group"] = "The total percent should add up to 100";
                }
	    }

        }
//        print_r($errors);
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
        $total_playmates = $Responses['total_playmates'];
        $questions_toremove = array('peer_initials_' ,'age_yrs_playmate_','age_mos_playmate_','gender_playmate_','q_number_playtimes_playmate','q2_avg_playtime_playmate','q3_related_playmate','q3_related_other_playmate','q4_playarea_playmate','q4_playarea_other_playmate','q5_proximity_playmate','q6_sameschool_playmate','q7_samechildcare_playmate','q8_specialneeds_playmate','q8_specialneeds_other_playmate','q9_yourchild_like_playmate','q0_like_yourchild_playmate','q_getalong_playmate','q2_leading_play_playmate','q3_typical_playtone_playmate','q4_typical_excitement_playmate','q5_num_conflicts_playmate','q6_disruptive_playmate','q7_how_involved_playmate','q8_arrangeplay_you_playmate','q8_arrangeplay_yourchild_playmate','q8_arrangeplay_other_playmate','q9_arrange_contacts_playmate','q20_stress_monitorplay_playmate','q2_facililate_getalong_playmate','q2_participate_activity_playmate','q2_maintain_presence_playmate','q2_outofview_listen_playmate','q2_outofview_notlisten_playmate','q22_manage_emotions_playmate','q22_understand_rules_playmate','q22_understand_howtoplay_playmate','q22_startplay_playmate','q22_remain_inplay_playmate','q22_manage_conflicts_playmate');
      for($i= $total_playmates+1; $i<=5; $i++) {
           foreach($questions_toremove as $qstn) {
               $field = $qstn.$i;
               foreach($tpl_data['questions'] as $key=>$val) {
                   if($val['SourceField'] == $field) {
                       unset($tpl_data['questions'][$key]);
                   }
               }
           }
       }
       $questions_other = array('q3_related_playmate'=>'q3_related_other_playmate','q4_playarea_playmate'=>'q4_playarea_other_playmate',
                                'q8_specialneeds_playmate'=>'q8_specialneeds_other_playmate');
       for($i=1; $i<=5; $i++) {
         foreach($questions_other as $other=>$other_val) {
             $field = $other.$i;
             foreach($tpl_data['questions'] as $key=>$val) {
                   if($val['SourceField'] == $other_val.$i && $Responses[$field] != 'other') {
                       unset($tpl_data['questions'][$key]); //unset all if Other specify question if answer to previous question is not set to other
                   }
               }

          }
       }
       $activity_other = array('activity_desc_'=>'activity_other');
       for($i=1; $i<=3; $i++) {
         foreach($questions_other as $other=>$other_val) {
             $field = $other.$i;
             foreach($tpl_data['questions'] as $key=>$val) {
                   if($val['SourceField'] == $other_val.$i && $Responses[$field] != 'other') {
                       unset($tpl_data['questions'][$key]); //unset all if Other specify question if answer to previous question is not set to other
                   }
               }

          }
       }

       foreach ($tpl_data['questions'] as $key=>&$row) {
            if (isset($Responses[$row['SourceField']])) {
                if($row['SourceField'] == 'respondent_other' && $Responses['respondent'] != 'other') {
                   unset($tpl_data['questions'][$key]);
                } elseif (empty ($row['question'] ) || empty($row['SourceField']) ) {
                   unset($tpl_data['questions'][$key]); //removes static fields from showing up
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
