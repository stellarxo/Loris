<?php

require_once 'HTML/QuickForm.php';
require_once 'HTML/QuickForm/Renderer/Array.php';

class NDB_BVL_Instrument_SRS extends NDB_BVL_Instrument
{
    var $ValidityEnabled = false;
    var $ValidityRequired = false;


    /*
    INSERT INTO test_names (Test_name, Full_name, LimitAge, Sub_Group)
        VALUES ('SRS', 'Social Responsiveness Scale (Preschool Version for 3-Year-Olds)', '0', '1');

    INSERT INTO instrument_subtests VALUES('', 'SRS', 'SRS_page1', 'Page 1 (1-32)', 1);
    INSERT INTO instrument_subtests VALUES('', 'SRS', 'SRS_page2', 'Page 2 (33-65', 2);
    -- No more page 3. 
    -- INSERT INTO instrument_subtests VALUES('', 'SRS', 'SRS_page3', 'Page 3', 3);
    */

    /* array indexing from page number to question array for that page. 
     * the _page($pageNum) function takes the appropriate page, and adds
     * all the questions to the page.
     */
    var $questions = array(
            1 => array(
                'q1_fidgety_social_situations'      => 'Seems much more fidgety in social situations than when alone',
                'q2_expressions_dont_match'         => "Expressions on his/her face don't match what he/she is saying",
                'q3_seems_self_confident'           => 'Seems self confident when interacting with others',
                'q4_auto_pilot_under_stress'        => 'When under stress, child seems to go on "auto-pilot"',
                'q5_no_recognize_take_advantage'    => "Doesn't recognize when others are trying to take advantage of him/her",
                'q6_rather_be_alone'                => 'Would rather be alone than with others',
                'q7_aware_others_feeling'           => 'Is aware of what others are thinking or feeling',
                'q8_behaves_strange'                => "Behaves in ways which seem strange or bizarre",
                'q9_clings_to_adults'               => "Clings to adults, seems too dependent on them",
                "q10_unable_pickup_meaning"         => "Unable to pick up on any of the meaning of conversations of older children or adults",
                "q11_good_self_confidence"          => "Has good self-confidence",
                "q12_able_communicate_feelings"     => "Is able to communicate his or her feelings to others in words or gestures",
                "q13_slow_turntaking_interactions"  => "Is slow or awkward in turn-taking interactions with peers",
                "q14_not_well_coordinated"          => "Is not well coordinated in physical activities",
                "q15_able_understand_meaning"       => "Is able to understand the meaning of other people's tone of voice and facial expressions",
                "q16_avoids_eye_contact"            => "Avoids eye contact, or has unusual eye contact",
            /* ),
            2 => array( */
                "q17_recognizes_unfair"             => "Recognizes when something is unfair",
                "q18_playground_no_interaction"     => "When on the playground or in a group with other young children, child does not attempt to interact with the other children",
                "q19_frustrated_conversations"      => "Gets frustrated trying to get ideas across in conversations",
                "q20_strange_playing"               => "Has strange way of playing with toys",
                "q21_able_imitate_others"           => "Is able to imitate others' actions",
                "q22_play_appropriately"            => "Plays appropriately with children his/her age",
                "q23_no_group_activities"           => "Does not join group activities unless told to do so",
                "q24_more_difficulty_routine"       => "Has more difficulty than other children with changes in his/her routine",
                "q25_doesnt_mind_out_of_step"       => 'Doesn\'t seem to mind being "out of step" or not on the "same wavelength" as others',
                "q26_offers_comfort_to_others"      => "Offers comfort to others when they are sad",
                "q27_avoids_social_interactions"    => "Avoids starting social interactions with peers or adults",
                "q28_talks_about_same_thing"        => "Thinks or talks about the same thing over and over",
                "q29_regarded_as_weird"             => "Is regarded by others as odd or weird",
                "q30_becomes_upset"                 => "Becomes upset in a situation with lots of things going on",
                "q31_cant_get_mind_off_something"   => "Can't get his/her mind off something once he/she starts thinking about it",
                "q32_wants_to_be_changed"           => "Wants to be changed when diaper or underwear are soiled or wet"),
            2 => array(
                "q33_socially_awkward"              => "Is socially awkward",
                "q34_avoids_emotional_close"        => "Avoids people who want to be emotionally close to him/her",
                "q35_trouble_keeping_flow"          => "Has trouble keeping up with the flow of a normal interaction with other children",
                "q36_difficulty_relating_adults"    => 'Has difficulty "relating" to adults',
                "q37_difficulty_relating_peers"     => 'Has difficulty "relating" to peers',
                "q38_responds_to_mood_changes"      => "Responds appropriately to mood changes in others",
                "q39_restricted_interests"          => "Has a restricted (or unusually narrow) range of interests",
                "q40_imaginative"                   => "Is imaginative, good at pretending (without losing touch with reality)",
                "q41_wanders_aimlessly_activities"  => "Wanders aimlessly from one activity to another",
                "q42_overly_sensitive_sounds_smells"=> "Seems overly sensitive to sounds, textures, or smells",
            /* ),
            3 => array( */
                "q43_separates_from_caregivers"     => "Separates easily from caregivers",
                "q44_doesnt_understand_events"      => "Doesn't understand how events are related to one another the way other children his/her age do",
                "q45_focuses_attention_others"      => "Focuses his/her attention to where others are looking or listening",
                "q46_overly_serious_expressions"    => "Has overly serious facial expressions",
                "q47_too_silly"                     => "Is too silly or laughs inappropriately",
                "q48_sense_of_humor"                => "Has a sense of humor, understands jokes",
                "q49_does_well_few_tasks"           => "Does extremely well at a few tasks, but does not do as well at most other tasks",
                "q50_repetitive_odd_behaviors"      => "Has repetitive, odd behaviors such as hand flapping or rocking",
                "q51_responds_odd_ways"             => "Responds to clear, direct questions in ways that don't seem to make any sense",
                "q52_knows_talking_too_loud"        => "Knows when he/she is talking too loud or making too much noise",
                "q53_talks_unusual_tone_of_voice"   => "Talks to people with an unusual tone of voice (for example, talks like a robot or like he/she is giving a lecture)",
                "q54_reacts_people_as_objects"      => "Seems to react to people as if they are objects",
                "q55_knows_invading_space"          => "Knows when he/she is too close to someone or is invading someone's space",
                "q56_walks_between_people"          => "Walks in between two people who are talking",
                "q57_other_children_dont_like"      => "Other children do not like to play with him/her",
                "q58_concentrates_on_parts"         => "Concentrates too much on parts of things rather than \"seeing the whole picture\"",
                "q59_overly_suspicious"             => "Is overly suspicious",
                "q60_is_emotionally_distant"        => "Is emotionally distant, doesn't show his/her emotions",
                "q61_inflexible"                    => "Is inflexible, has a hard time changing his/her mind",
                "q62_unusual_reasons"               => "Gives unusual or illogical reasons for doing things",
                "q63_touches_others_usually"        => "Touches others in an unusual way",
                "q64_tense_social_settings"         => "Is too tense in social settings",
                "q65_stares_into_space"             => "Stares or gazes off into space"
            )
    );

    var $scoreCols = array("srs_score");

    // Question numbers where not true = 0 and always true = 3
    // in the scoring algorithm
    var $ForwardCoded = array (1, 2, 4, 5, 6, 8, 9, 10, 13, 14, 
            16, 18, 19, 20, 23, 24, 25, 27, 28, 29, 30, 31, 33,
            34, 35, 36, 37, 39, 41, 42, 44, 46, 47, 49, 50, 51,
            53, 54, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65);
    // Question numbers where not true = 3 and always true = 0
    // in the scoring algorithm
    var $ReverseCoded = array(3, 7, 11, 12, 15, 17, 21, 22, 26,
            32, 38, 40, 43, 45, 48, 52, 55);


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
        $this->testName = "SRS";           // test_names.Test_name
        $this->table = 'SRS';              // name of database table corresponding to instrument
        // data keyed by commentID
        $this->commentID = $commentID;

        //The array of dates/timestamps to convert to database dates/timestamps
        //Any HTML_Quickform date elements must be listed here
        $this->dateTimeFields=array("Date_taken");

        //The array of selects with multiple answers allowed
        //Any HTML_Quickform multiple selects must be listed here
        $this->_selectMultipleElements = array();

        // Get the subject age in months for scoring

        $db =& Database::singleton();
        // required fields for data entry completion status
        $this->_requiredElements = array('Examiner', "Date_taken", 'q1_fidgety_social_situations', "q17_recognizes_unfair",
                "q43_separates_from_caregivers");

        //MODIFY THIS WHEN THE SCORING IS IMPLEMENTED

        $this->_doubleDataEntryDiffIgnoreColumns = array('CommentID', 'UserID', 'Testdate', 'Window_Difference', 'Candidate_Age','Data_entry_completion_status','srs_score');

        // setup the form
        $this->_setupForm();

    }

    //If the instrument is not paged, remove the switch from the _setupForm method and add all the form Elements in this function.

    /**
    * method to build the HTML_Quickform object into a paged form
    *
    * @return void
    * @access private
    */
    function _setupForm(){
        if(preg_match("/SRS_page([0-9]+)/",$this->page,$matches)){
            $this->_page($matches[1]);
        } else {
            $this->_main();
        }

        //Defines the call back function for HTML Quickform to use when validating the form.
        $this->form->addFormRule(array(&$this,'XINValidate'));
    }

    function _addDropdown($question_name, $question) {
        $this->form->addElement("select", "$question_name", $question, 
                array('' => '', 
                        'not_true' => "Not True", 
                        'sometimes_true' =>"Sometimes True", 
                        'often_true' => "Often True", 
                        'always_true' => "Almost Always True", 
                        'not_answered' => "Not Answered"
                )
        );

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
        $this->form->addElement('header', 'instrument_title', "Social Responsiveness Scale");

        // automatically adds examiner & date of administration
        $this->_addMetadataFields();
        $this->form->addElement("select", "completed_by", "This form filled out by", array('' => '', 'mother' => "Mother", 'father' =>"Father", 'other' => "Other", 'not_answered' => "Not Answered"));
        $this->addTextElement("completed_by_other", "Specify (if other):", array("completed_by{@}=={@}other"), "Required if filled out by other");

        $this->form->addElement("static", "srs_score", "SRS Score:");
/*     }

    function _page($pageNum) { */
        //$this->form->addElement('header', 'instrument_title', "Social Responsiveness Scale Page (SRS) - Page $pageNum");
        $this->form->addElement('header', 'instrument_title', "Social Responsiveness Scale Page (SRS)");
        $this->form->addElement('static', '', '<br />');
        $this->form->addElement('static', '', '<br />');

        $qNum = 1;
        $page_questions = array_merge($this->questions[1], $this->questions[2]);

        foreach($page_questions as $field => $question) {
            $this->_addDropdown($field, $qNum . '. ' . $question);
            $qNum++;
        }
    }

    function score() {
        if($this->_determineDataEntryCompletionStatus() == "Incomplete") {
           return;
        }
        $this->_nullScores($this->scoreCols);
        $db =& Database::singleton();
        $db->selectRow("SELECT * FROM $this->table WHERE CommentID='".$this->getCommentID()."'", $Answers);

        if($this->getSessionID() != NULL) { //quickform_parser doesn't use any specific session
            $timepoint =& TimePoint::singleton($this->getSessionID());
            $dob = $timepoint->getEffectiveDateOfBirth();
        }

        if(!empty($dob) && !empty($Answers['Date_taken'])) {
            $age = Utility::calculateAge($dob, $Answers["Date_taken"]);
             if(is_array($age)) {
                $age_months = $age['year'] * 12 + $age['mon'];
             } else {
                $scores['srs_score'] = "Error calculating age. Must specify date of administration.";
                $db->update($this->table, $scores, array('CommentID'=>$this->getCommentID()));
                return;
             }
        }

        if($age_months < 33) {
            $scores['srs_score'] = "Child too young to score.";
            $db->update($this->table, $scores, array('CommentID'=>$this->getCommentID()));
            return;
        } else if($age_months > 48) {
            $scores['srs_score'] = "Child too old to score.";
            $db->update($this->table, $scores, array('CommentID'=>$this->getCommentID()));
            return;
        }

        $scores = array();

        // add an arbitrary 0 index, so that index n maps to question n
        $fields_array = array(0 => "no question zero");
        foreach($this->questions as $page => $questions) {
            $fields_array = array_merge($fields_array, array_keys($questions));
        }

        $score = 0;
        $not_answered = 0;
        foreach($this->ForwardCoded as $QuestionNumber) {
            switch($Answers[$fields_array[$QuestionNumber]]) {
                case 'not_true':
                    $score += 0;
                    break;
                case 'sometimes_true':
                    $score += 1;
                    break;
                case 'often_true': 
                    $score += 2;
                    break;
                case 'always_true':
                    $score += 3;
                    break;
                case 'not_answered':
                    $not_answered += 1;
                    break;
            }
        }

        foreach($this->ReverseCoded as $QuestionNumber) {
            switch($Answers[$fields_array[$QuestionNumber]]) {
                case 'not_true':
                    $score += 3;
                    break;
                case 'sometimes_true':
                    $score += 2;
                    break;
                case 'often_true': 
                    $score += 1;
                    break;
                case 'always_true':
                    $score += 0;
                    break;
                case 'not_answered':
                    $not_answered += 1;
                    break;
            }
        }
        $scores['srs_score'] = $score;
        if($not_answered > 7) {
            $scores['srs_score'] = "More than 7 questions not answered. Score is invalid";
        }

        // save the resultant total
        if($scores != array()) {
            $result = $db->update($this->table, $scores, array('CommentID'=>$this->getCommentID()));
        }
    }
}
?>
