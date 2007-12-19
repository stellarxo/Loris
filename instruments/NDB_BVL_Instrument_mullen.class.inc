<?php
class NDB_BVL_Instrument_mullen extends NDB_BVL_Instrument
{
    /*
    INSERT INTO test_names VALUES ('', 'mullen', 'Mullen (Mullen Scales of Early Learning)', '0', '1');

    INSERT INTO instrument_subtests VALUES('', 'mullen', 'mullen_page1', 'Gross Motor', 1);
    INSERT INTO instrument_subtests VALUES('', 'mullen', 'mullen_page2', 'Visual Reception', 2);
    INSERT INTO instrument_subtests VALUES('', 'mullen', 'mullen_page3', 'Fine Motor', 3);
    INSERT INTO instrument_subtests VALUES('', 'mullen', 'mullen_page4', 'Receptive Language', 4);
    INSERT INTO instrument_subtests VALUES('', 'mullen', 'mullen_page5', 'Expressive Language', 5);

    For Hamilton (testing only)...
--    INSERT INTO test_battery VALUES ('', 'mullen', '1005', '1140', 'Y', 'Visit', '3');

    For NIHACE... (already there)
    INSERT INTO test_battery VALUES ('', 'mullen', '150', '780', 'Y', 'Visit', '1');
    INSERT INTO test_battery VALUES ('', 'mullen', '300', '780', 'Y', 'Visit', '2');
    INSERT INTO test_battery VALUES ('', 'mullen', '150', '780', 'Y', 'Visit', '3');

    */

    var $yesNo = array(""=>null, "no"=>"No", "yes"=>"Yes", "not_answered"=>"Not Answered");

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
        $this->testName = "mullen";           // test_names.Test_name
        $this->table = 'mullen';              // name of database table corresponding to instrument
        // data keyed by commentID
        $this->commentID = $commentID;

        //The array of dates/timestamps to convert to database dates/timestamps
        //Any HTML_Quickform date elements must be listed here
        $this->dateTimeFields=array("Date_taken");

        //The array of selects with multiple answers allowed
        //Any HTML_Quickform multiple selects must be listed here
        $this->_selectMultipleElements = array();

        // required fields for data entry completion status
        $this->_requiredElements = array('Examiner');
        //MODIFY THIS WHEN THE SCORING IS IMPLEMENTED
        
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
        if(ereg("mullen(_page[0-9]+)",$this->page,$matches)){
            call_user_method($matches[1], &$this);
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
        $this->form->addElement('header', 'instrument_title', "Mullen Scales of Early Learning");

        // automatically adds examiner & date of administration
        $this->_addMetadataFields();

        $this->form->addElement("header", null, "Please answer only non-identifying questions");
        $this->form->addElement("static", null, "Child's Name");
        $this->form->addElement("static", null, "ID");
        $this->form->addElement("static", null, "Phone Number");
        $this->form->addElement("static", null, "Nickname");
        $this->form->addElement("static", null, "Boy / Girl");
        $this->form->addElement("static", null, "Address");

        $this->addTextElement("primary_language", "Child's Primary Language");

        $this->form->addElement("static", null, "Mother's Name");
        $this->form->addElement("static", null, "Father's Name");
        $this->form->addElement("static", null, "Examiner");
        $this->form->addElement("static", null, "School");

        $this->addTextElement("weeks_gestation", "No. Weeks Gestation (G.A.)");
        $this->addTextElement("birth_weight", "Birth Weight");

        $this->addTextElement("apgar_1_min", "Apgars 1 min.");
        $this->addTextElement("apgar_5_min", "Apgars 5 min.");
        $this->form->addElement("static", null, "Hospital");

        $this->form->addElement("select", "uncorrected_vision", "Does the child have a known uncorrected vision problem?", $this->yesNo);
        $this->form->addElement("select", "uncorrected_hearing", "Does the child have a known uncorrected hearing problem?", $this->yesNo);

        $this->addTextElement("characteristic_affecting", "Personal or physical characteristics that may affect the child's test results");

        $this->form->addElement("select", "medication", "Is the child on any medication?", $this->yesNo);
        $this->addTextElement("medication_specify", $this->indent . "If yes, please specify", array("medication{@}=={@}yes"), "This field is required if the child is on medication");

        $this->form->addElement("static", null, "Referred by");
        $this->form->addElement("static", null, "Reason for Referral");
        $this->addTextAreaElement("info_comments", "Additional Information/Comments");

        $this->form->addElement("static", null, "Testing Date");
        $this->form->addElement("static", null, "Birth Date");
        $this->form->addElement("static", null, "Chronological Age");
        $this->form->addElement("static", null, "Adjusted Age");
    }

    function _page1(){

        $this->form->addElement("header", null, "Scale 1. Gross Motor");
        $questionArray = array(0=>null,
        "1. Enjoys being held/realigns (Up)",
        "2. Rotates head (P)",
        "3. Moves arms, legs vigorously (S)",
        "4. Held upright, holds head steady (Up)",

        "5. Supports on forearms (P)",
        "6. Sits supported, head steady (5511)",
        "7. Rolls over (P to S)",

        "8. Holds on to fingers/pulls self to sit (S to SSIt)",
        "9. Shifts weight, reaches (P)",
        "10. Stands with hands held, bounces",

        "11. Sits with arms free (Sit)",
        "12. Pulls self to stand (Sit to stand)",
        "13. Gets from sitting to hands and knees (Sit)",
        "14. Walks with one hand held",

        "15. Stands alone (12 seconds)",
        "16. Walks alone (4-5 steps)",
        "17. Throws a ball underhand",

        "18. Gets to stand by rolling to side (S to stand)",
        "19. Stands, squats, stands",
        "20. Walks up stairs with help, nonalternating",
        "21. Runs stiffly",

        "22. Kicks a 10- to 12-inch ball (2 of 5 trials)",
        "23. Stands on one foot, with help",
        "24. Walks 4 to S steps, one foot on line",
        "25. Walks up stairs by self, nonalternating",
        "26. Jumps down from bench",
        "27. Jumps in place, feet together (one jump)",
        "28. Walks on tiptoes (4-5 steps)",
        "29. Walks on line, using arms to balance (6-7 steps)",
        "30. Walks down stairs by self, alternating",
        "31. Gets to stand/forward to sit (S to stand)",
        "32. Balances on one foot (2-3 seconds)",
        "33, Runs, turns corner, stops",
        "34. Hops two times",
        "35. Walks on line, arms at side (6 steps)");
        unset($questionArray[0]);

        $sectionDividers = array(1=>"1-4 mo.",
        5=>"5-8 mo.",
        8=>"9-12 mo.",
        11=>"13-17 mo.",
        15=>"18-20 mo.",
        18=>"21-26 mo.",
        22=>"27+ mo.");

        foreach($questionArray as $field=>$label) {
            //check if this is the beginning to a section...
            if(key_exists($field, $sectionDividers)) {
                $this->form->addElement("header", null, $sectionDividers[$field]);
            }
            //Output the question...
            if ($field == 26) {
                $this->_addQuestion("gross_motor_" . $field, $label, 2);
            } else
            $this->_addQuestion("gross_motor_" . $field, $label, 1);
        }

        $this->form->addElement("header", null, "Score");
        $this->form->addElement("static", null, "Gross Motor Raw Score");

    }

    function _page2() {
        $this->form->addElement("header", null, "Scale 2. Visual Reception");
        $questionArray = array(0=>null,
        "1. Fixates on and tracks triangle (S)",
        "2. Tracks schematic face 90 degrees (S)",

        "3. Tracks moving bull's-eye 180 degrees (PPr)",
        "4. Localizes alternating red ball and schematic face (PPr)",
        "5. Stares at own hand (S)",
        "6. Localizes bull's-eye near and far (SSit)",

        "7. Looks for dropped spoon (A/V) (SSit)",
        "8. Pulls cord to obtain disc (SSit)",

        "9. Looks for ring hidden under washcloth (Sit)",
        "10. Turns cup right-side up",
        "11. Makes object association",
        "12. Looks for car under two washcloths",
        "13. Shows interest in book as hinge",
        "14. Attends to picture (A/V)",
        "15. Looks for toy covered, then displaced",

        "16. Discriminates forms on formboard");
        $questionArray += array("17A"=>"17A. Matches objects with naming (A/V) (19 months or younger)",
        //OR"
        "17B"=>"17B. Matches objects without naming (20 months or older)");  //3",

        $questionArray += array("18"=>"18. Nests nesting cups",

        "19"=>"19. Sorts spoons and blocks by category",
        "20"=>"20. Matches by shape",
        "21"=>"21. Matches pictures",
        "22"=>"22. Matches by size, color",
        "23"=>"23. Memory for one picture",
        "24"=>"24. Spatial details I",

        "25"=>"25. Spatial details II",
        "26"=>"26. Memory for objects",
        "27"=>"27. Discriminates spatial position",
        "28"=>"28. Matches letters",
        "29"=>"29. Discriminates left/right",
        "30"=>"30. Matches letters, words",
        "31"=>"31. Memory for three pictures",
        "32"=>"32. Spatial details III",
        "33"=>"33. Memory for form");
        unset($questionArray[0]); //get rid of the zero in the 0 based array

        //Potential point value of each question
        $maxPoints = array(1=>2,
        2=>1,
        3=>1,
        4=>1,
        5=>1,
        6=>1,
        7=>1,
        8=>1,
        9=>2,
        10=>1,
        11=>1,
        12=>1,
        13=>1,
        14=>1,
        15=>1,
        16=>4,
        "17A"=>3,
        "17B"=>3,
        18=>2,
        19=>1,
        20=>1,
        21=>1,
        22=>1,
        23=>1,
        24=>1,
        25=>2,
        26=>1,
        27=>1,
        28=>1,
        29=>4,
        30=>4,
        31=>1,
        32=>2,
        33=>2);

        $sectionDividers = array(1=>"1-4 mo.",
        3=>"5-8 mo.",
        7=>"9-12 mo.",
        9=>"10-20 mo.",
        16=>"21-32 mo.",
        19=>"33-44 mo.",
        25=>"45+ mo.");

        foreach($questionArray as $field=>$label) {
            //check if this is the beginning to a section...
            if(key_exists($field, $sectionDividers)) {
                $this->form->addElement("header", null, $sectionDividers[$field]);
            }
            //Output the question...
            $this->_addQuestion("visual_recept_" . $field, $label, $maxPoints[$field]);
        }

        $this->form->addElement("header", null, "Score");
        $this->form->addElement("static", null, "Visual Reception Raw Score");

    }

    function _page3() {
        $this->form->addElement("header", null, "Scale 3. Fine Motor");
        $questionArray = array(0=>null,
        "1. Arms flexed/hands fisted (S)",
        "2. Holds ring reflexively (S)",
        "3. Brings fist to mouth (P)",

        "4. Bilateral orientation in midline (S)",
        "5. Grasp reflex integrated (S)",
        "6. Grasps peg (ulnar palmar) (PPr or SSit)",

        "7. Reaches for and grasps block (radial palmar grasp) (SSit)",
        "8. Transfers, bangs, drops (SSit)",
        "9. Refined grasp/thumb opposition (Sit)",
        "10. Uses pincer grasp (Sit)",

        "11. Bangs in midline, horizontal movement (Sit)",
        "12. Takes blocks out, puts blocks in",

        "13. Uses two hands together",
        "14. Turns pages in a book ",
        "15. Imitates crayon lines",

        "16. Puts pennies in slot, horizontal and vertical",
        "17. Stacks blocks vertically",
        "18. Imitates four-block train",
        "19. Unscrews, screws nut and bolt",
        "20. Strings beads",

        "21. Imitates four-block tower",
        "22. Copies circle, circle and line",
        "23. Draws in path",
        "24. Cuts with scissors",
        "25. Folds paper three times",
        "26. Imitates drawings",
        "27. Touches fingers I",
        "28. Touches fingers II",
        "29. Folds paper twice to form square",
        "30. Copies shapes and letters");
        unset($questionArray[0]); //get rid of the zero in the 0 based array

        //Potential point value of each question
        $maxPoints = array(1=>1,
        2=>1,
        3=>1,
        4=>1,
        5=>1,
        6=>1,
        7=>1,
        8=>1,
        9=>1,
        10=>2,
        11=>1,
        12=>3,
        13=>1,
        14=>2,
        15=>3,
        16=>2,
        17=>3,
        18=>2,
        19=>1,
        20=>1,
        21=>1,
        22=>2,
        23=>2,
        24=>2,
        25=>1,
        26=>3,
        27=>1,
        28=>1,
        29=>1,
        30=>5);

        $sectionDividers = array(1=>"1-4 mo.",
        4=>"5-8 mo.",
        7=>"9-12 mo.",
        11=>"13-17 mo.",
        13=>"18-29 mo.",
        16=>"30-44 mo.",
        21=>"45+ mo.");

        foreach($questionArray as $field=>$label) {
            //check if this is the beginning to a section...
            if(key_exists($field, $sectionDividers)) {
                $this->form->addElement("header", null, $sectionDividers[$field]);
            }
            //Output the question...
            $this->_addQuestion("fine_motor_" . $field, $label, $maxPoints[$field]);
        }

        $this->form->addElement("header", null, "Score");
        $this->form->addElement("static", null, "Fine Motor Raw Score");


    }

    function _page4() {
        $this->form->addElement("header", null, "Scale 4. Receptive Language");

        $questionArray = array(0=>null,
        "1. Reacts reflexively to loud noise (S)",
        "2. Alerts to sound (S)",
        "3. Responds to voice and face by smiling (A/V) (S)",

        "4. Coordinates listening and turning (PPr)",
        "5. Responds to voice and face by vocalizing (A/V) (PPr or SSit)",
        "6. Coordinates listening and looking (SSit)",
        "7. Enjoys self/mirror interaction (A/V) (SSit)",

        "8. Attends to words and movement (A/V) (SSit or Sit)",
        "9. Recognizes familiar names, words",
        "10. Recognizes own name",
        "11. Understands inhibitory words",

        "12. Understands simple verbal input",
        "13. Understands gesture and commands (A/V)",
        "14. Identifies objects (A/V)",
        "15. Gives toy on verbal request",
        "16. Comprehends questions I",
        "17. Follows directions",

        "18. Recognizes body parts (A/V)",
        "19. Comprehends questions II (A/V)",
        "20. Follows related commands",
        "21. Identifies pictures (A/V)",

        "22. Auditory spatial awareness",
        "23. Comprehends action words (A/V)",
        "24. Identifies object function (A/V)",

        "25. Follows two unrelated commands",
        "26. Size concepts (A/V)",
        "27. Identifies colors (A/V)",
        "28. Length concepts (A/V)",
        "29. Comparative concepts (A/V)",
        "30. General knowledge (see flap)",
        "31. Follows three unrelated commands",
        "32. Has concept of six, eight",
        "33. Identifies letters (A/V)");
        unset($questionArray[0]); //get rid of the zero in the 0 based array

        //Potential point value of each question
        $maxPoints = array(1=>1,
        2=>1,
        3=>1,
        4=>1,
        5=>1,
        6=>1,
        7=>1,
        8=>1,
        9=>1,
        10=>1,
        11=>1,
        12=>1,
        13=>1,
        14=>1,
        15=>1,
        16=>1,
        17=>1,
        18=>3,
        19=>1,
        20=>1,
        21=>1,
        22=>4,
        23=>2,
        24=>1,
        25=>1,
        26=>1,
        27=>1,
        28=>1,
        29=>4,
        30=>5,
        31=>1,
        32=>2,
        33=>2);

        $sectionDividers = array(1=>"1-4 mo.",
        4=>"5-10 mo.",
        8=>"11-14 mo.",
        12=>"15-22 mo.",
        18=>"23-32 mo.",
        22=>"33-44 mo.",
        25=>"45+ mo.");

        foreach($questionArray as $field=>$label) {
            //check if this is the beginning to a section...
            if(key_exists($field, $sectionDividers)) {
                $this->form->addElement("header", null, $sectionDividers[$field]);
            }
            //Output the question...
            $this->_addQuestion("receptive_lang_" . $field, $label, $maxPoints[$field]);
        }

        $this->form->addElement("header", null, "Score");
        $this->form->addElement("static", null, "Receptive Language Raw Score");
    }

    function _page5() {
        $this->form->addElement("header", null, "Scale 5. Expressive Language");

        $questionArray = array(0=>null,
        "1. Sucking, swallowing, chewing movements",
        "2. Vocalizes (S)",
        "3. Smiles and makes happy sounds (S)",

        "4. Coos, chuckles, or laughs",
        "5. Makes vocalizations (such as ah, eh, m)",
        "6. Plays with sounds (such as o, u, ah-goo)",

        "7. Voluntary babbling (such as 'bu, bu, bu')",
        "8. Produces three consonant sounds (such as p, d, k, g, m)",
        "9. Vocalizes two-syllable sounds (such as 'dada' or 'baba')",
        "10. Plays gesture/language game",

        "11. Says first words",
        "12. Jabbers with inflection",
        "13. Combines jargon/gestures",
        "14. Combines words/gestures",

        "15. Names objects",
        "16. Labels picture",
        "17. Uses two-word phrase",
        "18. Picture vocabulary (see flap)",

        "19. Uses pronouns",
        "20. Counts to two, three, twelve",
        "21. Repeats two numbers",

        "22. Uses three- to four-word sentences",
        "23. Answers questions (see flap)",
        "24. Verbal analogies (see flap)",
        "25. Repeats sentences I",
        "26. Oral vocabulary (see flap)",
        "27. Practical reasoning (see flap)",
        "28. Repeats sentences II");
        unset($questionArray[0]); //get rid of the zero in the 0 based array

        //Potential point value of each question
        $maxPoints = array(1=>1,
        2=>1,
        3=>1,
        4=>1,
        5=>1,
        6=>1,
        7=>1,
        8=>1,
        9=>1,
        10=>1,
        11=>3,
        12=>1,
        13=>1,
        14=>1,
        15=>3,
        16=>1,
        17=>1,
        18=>5,
        19=>1,
        20=>3,
        21=>1,
        22=>1,
        23=>2,
        24=>5,
        25=>1,
        26=>4,
        27=>4,
        28=>2);
        
        $sectionDividers = array(1=>"1-4 mo.",
        4=>"5-8 mo.",
        7=>"9-14 mo.",
        11=>"15-23 mo.",
        15=>"24-32 mo.",
        19=>"33-44 mo.",
        22=>"45+ mo.");
        
        foreach($questionArray as $field=>$label) {
            //check if this is the beginning to a section...
            if(key_exists($field, $sectionDividers)) {
                $this->form->addElement("header", null, $sectionDividers[$field]);
            }
            //Output the question...
            $this->_addQuestion("expressive_lang_" . $field, $label, $maxPoints[$field]);
        }

        $this->form->addElement("header", null, "Score");
        $this->form->addElement("static", null, "Expressive Language Raw Score");

    }

    //Add an individual question, for now, nothing is required.
    function _addQuestion($field, $label, $maxPoints) {

        $answerOptions = array(""=>null) + range($maxPoints, 0) + array("not_answered"=>"Not Answered");
        $this->form->addElement("select", $field, $this->indent . $label, $answerOptions);
        $this->XINRegisterRule($field, array("{$field}{@}=={@}NEVER_REQUIRED"));
    }

}
?>