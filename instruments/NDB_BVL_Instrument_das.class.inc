<?php
class NDB_BVL_Instrument_das extends NDB_BVL_Instrument
{

    // TO DO:

    // _score()

    // _page#()
    // ASP & DPs
    // age constraints
    // second attempts??
    // paper form
    // forced numbers
    // item 1, item 2,... OR item 1 - model & picture, item 2 - picture & demonstration,...

    // END


    /*
    INSERT INTO test_names (Test_name, Full_name, Sub_group) VALUES ('das', 'DAS (Differential Ability Scales)', '1');

    INSERT INTO instrument_subtests (Test_name, Subtest_name, Description, Order_number) VALUES ('das', 'das_page1', 'Block Building', 1);
    INSERT INTO instrument_subtests (Test_name, Subtest_name, Description, Order_number) VALUES ('das', 'das_page2', 'Verbal Comprehension', 2);
    INSERT INTO instrument_subtests (Test_name, Subtest_name, Description, Order_number) VALUES ('das', 'das_page3', 'Picture Similarities', 3);
    INSERT INTO instrument_subtests (Test_name, Subtest_name, Description, Order_number) VALUES ('das', 'das_page4', 'Naming Vocabulary', 4);
    INSERT INTO instrument_subtests (Test_name, Subtest_name, Description, Order_number) VALUES ('das', 'das_page5', 'Recall of Objects - Immediate', 5);
    INSERT INTO instrument_subtests (Test_name, Subtest_name, Description, Order_number) VALUES ('das', 'das_page6', 'Pattern Construction', 6);
    INSERT INTO instrument_subtests (Test_name, Subtest_name, Description, Order_number) VALUES ('das', 'das_page7', 'Early Number Concepts', 7);
    INSERT INTO instrument_subtests (Test_name, Subtest_name, Description, Order_number) VALUES ('das', 'das_page8', 'Recall of Objects - Delayed', 8);
    INSERT INTO instrument_subtests (Test_name, Subtest_name, Description, Order_number) VALUES ('das', 'das_page9', 'Copying', 9);

    INSERT INTO test_battery (Test_name, AgeMinDays, AgeMaxDays, Active, Stage, SubprojectID, Visit_label, CenterID) VALUES ('das', '1', '99999', 'Y', 'Visit', '1', '2', NULL);
    */


//    Do we need this?????
//    var $scores = array("q_70_trial1"=>"","q_71_trial2"=>"","q_72_trial3"=>"");
//    var $questions = array();



    /*
     * sets up basic data, such as the HTML_Quickform object, and so on.
     *
     * @param string $commentID  the CommentID identifying the data to load
     * @param string $page       if a multipage form, the page to show
     * @return void
     * @access public
     */
    function setup($commentID, $page) {

        $this->formType="XIN";
        $this->form = new HTML_Quickform('test_form');
        $this->page = $page;            // page label (number or
        // string - used by
        // user-defined child classes)

        // object properties
        $this->testName = "das";
        $this->table = 'das';
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

	    // Array of column names to be ignored by the double data entry conflict detector
        $this->_doubleDataEntryDiffIgnoreColumns =
            array('CommentID', 'UserID', 'Testdate',  'Window_Difference', 'Candidate_Age',
                'other_comments1',
                'other_comments2',
                'other_comments3',
                'other_comments4',
                'other_comments5',
                'other_comments6',
                'other_comments7',
                'other_comments8',
                'other_comments9',
                );

        // setup the form
        $this->_setupForm();

    }


    /*
     * method to build the HTML_Quickform object into a paged form
     *
     * @return void
     * @access private
     */
    function _setupForm() {



        $db =& Database::singleton();

        $query = "SELECT * FROM $this->table WHERE CommentID='".$this->getCommentID()."'";
        $record=array();
        $db->selectRow($query, $record);

        $age = $this->respondentAgeMonths;
//        $age = $this->getCandidateAge($values['Date_taken']);
//        $agemonths = $age['year']*12 + $age['mon'] + ($age['day']/30);

        // 1. Block Building
        // Usual Age Range: 2 years 6 months to 3 years 5 months
        // Extended Age Range: 3 years 6 months to 4 years 11 months


        // 2. Verbal Comprehension
        // Usual Age Range: 2 years 6 months to 5 years 11 months
        // Out of Level: 6 years 0 months to 6 years 11 months
        $UAR2 = array(
            "q_13_item1"=>"not_answered",
            "q_14_item2"=>"not_answered",
            "q_15_item3"=>"not_answered",
            "q_16_item4"=>"not_answered",
            "q_17_item5"=>"not_answered",
            "q_18_item6"=>"not_answered",
            "q_19_item7"=>"not_answered",
            "q_20_item8"=>"not_answered",
            "q_21_item9"=>"not_answered",
            "q_22_item10"=>"not_answered",
            "q_23_item11"=>"not_answered",
            "q_24_item12"=>"not_answered"
        );

        if($age >= 48 && $age <= 83) {
            foreach($UAR2 as $field=>$value) {
                //Defaults apply only to empty database fields
                if(isset($record[$field]) && $record[$field] == null) {
                    $this->localDefaults[$field] = $value;
                }
            }
        }


        // 3. Picture Similarities
        // Usual Age Range: 2 years 6 months to 5 years 11 months
        // Out of Level: 6 years 0 months to 7 years 11 months
        $UAR3 = array(
            "q_49_item1"=>"not_answered",
            "q_50_item2"=>"not_answered",
            "q_51_item3"=>"not_answered",
            "q_52_item4"=>"not_answered",
            "q_53_item5"=>"not_answered",
            "q_54_item6"=>"not_answered",
            "q_55_item7"=>"not_answered",
            "q_56_item8"=>"not_answered",
            "q_57_item9"=>"not_answered",
            "q_58_item10"=>"not_answered",
        );

        if($age >= 54 && $age <= 95) {
            foreach($UAR3 as $field=>$value) {
                //Defaults apply only to empty database fields
                if(isset($record[$field]) && $record[$field] == null) {
                    $this->localDefaults[$field] = $value;
                }
            }
        }


        // 4. Naming Vocabulary
        // Usual Age Range: 2 years 6 months to years months
        // Extended Age Range: 6 years 0 months to 7 years 11 months
        // Out of Level: 8 years 0 months to 8 years 11 months
        $UAR4 = array(
            "q_81_item1"=>"not_answered",
            "q_82_item2"=>"not_answered",
            "q_83_item3"=>"not_answered",
            "q_84_item4"=>"not_answered",
            "q_85_item5"=>"not_answered",
            "q_86_item6"=>"not_answered",
            "q_87_item7"=>"not_answered"
        );

        if($age >= 54 && $age <= 107) {
            foreach($UAR4 as $field=>$value) {
                //Defaults apply only to empty database fields
                if(isset($record[$field]) && $record[$field] == null) {
                    $this->localDefaults[$field] = $value;
                }
            }
        }


        // 5. Recall of Objects - Immediate
        // Usual Age Range: 4 years 0 months to 17 years 11 months


        // 6. Pattern Construction
        // Usual Age Range: 3 years 6 months to 17 years 11 months
        // Out of Level: 3 years 0 months to 3 years 5 months
        $UAR6 = array(
            "q_90_item1"=>"not_answered",
            "q_91_item2"=>"not_answered",
            "q_92_item3"=>"not_answered",
            "q_93_item4"=>"not_answered",
            "q_94_item5"=>"not_answered",
            "q_95_item6"=>"not_answered",
            "q_96_item7"=>"not_answered"
        );

        $UAR6b = array_merge($UAR6,
            array(
                "q_97_item8"=>"not_answered",
                "q_98_item9"=>"not_answered",
                "q_99_item10"=>"not_answered",
                "q_100_item11"=>"not_answered",
                "q_101_item12"=>"not_answered",
                "q_102_item13"=>"not_answered",
            ));

        if($age >= 84 && $age <= 155) {
            foreach($UAR6 as $field=>$value) {
                //Defaults apply only to empty database fields
                if(isset($record[$field]) && $record[$field] == null) {
                    $this->localDefaults[$field] = $value;
                }
            }
        }

        if($age >= 156 && $age <= 215) {
            foreach($UAR6b as $field=>$value) {
                //Defaults apply only to empty database fields
                if(isset($record[$field]) && $record[$field] == null) {
                    $this->localDefaults[$field] = $value;
                }
            }
        }


        // 7. Early Number Concepts
        // Usual Age Range: 3 years 6 months to 5 years 11 months
        // Extended Age Range: 6 years 0 months to 6 years 5 months
        // Out of Level: 2 years 6 months to 3 years 5 months
        // Out of Level: 6 years 6 months to 7 years 11 months
        $UAR7 = array(
            "q_116_item1"=>"not_answered"
        );

        $UAR7b = array_merge($UAR7,
            array(
                "q_117_item2"=>"not_answered",
                "q_118_item3"=>"not_answered",
                "q_119_item4"=>"not_answered",
                "q_120_item5"=>"not_answered",
                "q_121_item6"=>"not_answered",
                "q_122_item7"=>"not_answered",
                "q_123_item8"=>"not_answered",
                "q_124_item9"=>"not_answered",
                "q_125_item10"=>"not_answered",
                "q_126_item11"=>"not_answered",
                "q_127_item12"=>"not_answered",
                "q_128_item13"=>"not_answered",
                "q_129_item14"=>"not_answered",
                "q_130_item15"=>"not_answered",
            ));

        if($age >= 54 && $age <= 77) {
            foreach($UAR7 as $field=>$value) {
                //Defaults apply only to empty database fields
                if(isset($record[$field]) && $record[$field] == null) {
                    $this->localDefaults[$field] = $value;
                }
            }
        }

        if($age >= 78 && $age <= 95) {
            foreach($UAR7b as $field=>$value) {
                //Defaults apply only to empty database fields
                if(isset($record[$field]) && $record[$field] == null) {
                    $this->localDefaults[$field] = $value;
                }
            }
        }

        // 8. Recall of Objects - Delayed
        // Usual Age Range: 4 years 0 months to 17 years 11 months


        // 9. Copying
        // Usual Age Range: 3 years 6 months to 5 years 11 months
        // Out of Level: 6 years 0 months to 7 years 11 months
        $UAR9 = array(
            "q_145_item1"=>"not_answered",
            "q_146_item1"=>"not_answered",
            "q_147_item1"=>"not_answered",
            "q_148_item1"=>"not_answered"
        );

        $UAR9b = array_merge($UAR9,
            array(
                "q_149_item5"=>"not_answered",
                "q_150_item6"=>"not_answered",
                "q_151_item7"=>"not_answered",
                "q_152_item8"=>"not_answered",
                "q_153_item9"=>"not_answered",
                "q_154_item10"=>"not_answered"
            ));

        if($age >= 60 && $age <= 71) {
            foreach($UAR9 as $field=>$value) {
                //Defaults apply only to empty database fields
                if(isset($record[$field]) && $record[$field] == null) {
                    $this->localDefaults[$field] = $value;
                }
            }
        }

        if($age >= 72 && $age <= 95) {
            foreach($UAR9b as $field=>$value) {
                //Defaults apply only to empty database fields
                if(isset($record[$field]) && $record[$field] == null) {
                    $this->localDefaults[$field] = $value;
                }
            }
        }


        if(preg_match("/(_page[0-9]+)/",$this->page,$matches)){
            call_user_method($matches[1], $this);
        } else {
            $this->_main();
        }

        //Defines the call back function for HTML Quickform to use when validating the form.
        $this->form->addFormRule(array(&$this,'XINValidate'));

    }


    /*
     * generates the main page of the form
     *
     * @return void
     * @access private
     *
     */
    function _main() {

        // display test name
        $this->form->addElement('header', 'instrument_title', "DAS");

        // automatically adds examiner & date of administration
        $this->_addMetadataFields();

        $this->form->addElement('static', null, "<br />");
        $this->form->addElement('header', 'raw_scores', "Raw Scores");
        $this->form->addElement("static", null, "NOTE: Final scores still need to be calculated.");

        $this->form->addElement("static", null, "<br />");

        $scoreLabels = array(
            "Total_1"=>"Block Building Score",
            "Total_2"=>"Verbal Comprehension Score",
            "Total_3"=>"Picture Similarities Score",
            "Total_4"=>"Naming Vocabulary Score",
            "Total_5"=>"Recall of Objects - Immediate Score",
            "Total_6"=>"Pattern Construction Score",
            "Total_7"=>"Early Number Concepts Score",
            "Total_8"=>"Recall of Objects - Delayed Score",
            "Total_9"=>"Copying Score"
        );

        foreach ($scoreLabels as $field=>$label) {
            if(in_array($field,
                    array("Total_1", "Total_2", "Total_3", "Total_4", "Total_5",
                        "Total_6", "Total_7", "Total_8", "Total_9")) == TRUE) {
                $label = $this->indent . $this->indent . $label;
            }
            $this->form->addElement("static", $field, $label);
        }

        $this->form->addElement('static', null, "<br />");
        $this->form->addElement("textarea", "other_comments", "Comments:", array('cols'=>25, 'rows'=>4));
        $this->XINRegisterRule("other_comments", array("{other_comments}{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement('static', null, "<br />");

    }


    function _score() {

        $db =& Database::singleton();

        // skip scoring if proband DoB was not entered, i.e. data entry is not completed
        if(empty($this->respondentAgeMonths)){
            return;
        }

        $age = $this->respondentAgeMonths;

        // null scores
        $this->_nullScores($this->scoreCols);
        // Get the item scores
        $query = "SELECT * FROM $this->table WHERE CommentID='".$this->getCommentID()."'";
        $record=array();
        $db->selectRow($query, $record);

        $conversion = array(
            'incorrect'=>0,'correct'=>1,
            0=>0, 1=>1, 2=>2, 3=>3, 4=>4, 5=>5, 6=>6, 7=>7, 8=>8, 9=>9, 10=>10,
            11=>11, 12=>12, 13=>13, 14=>14, 15=>15, 16=>16, 17=>17, 18=>18, 19=>19, 20=>20,
            'p'=>1, 'p_1'=>3, 'p_2'=>1, 'f'=>0
            );

        foreach ($record as $field=>$code) {
//            if(!in_array($field, array(""))) {
//                $this->scores[$field] = substr($code,0,1);
                if(is_numeric($this->scores[$field])) {
                    $intval = intval($this->scores[$field]);
                    $this->scores[$field] = $conversion[$intval];
                }
                else {
                    $this->scores[$field] = 0; // for 'not_answered'
                }
//            }
        }


        // Under 2 years 6 months
        if ($this->respondentAgeMonths < (2*12+6)) {
            $scoreCols["Total_1"] = "Respondent too young to score";
            $scoreCols["Total_2"] = "Respondent too young to score";
            $scoreCols["Total_3"] = "Respondent too young to score";
            $scoreCols["Total_4"] = "Respondent too young to score";
            $scoreCols["Total_7"] = "Respondent too young to score";
        }
        // 2 years 6 months to 17 years 11 months
        elseif ($this->respondentAgeMonths >= 30 && $this->respondentAgeMonths <= 215) {


            // 1. Block Building
            if ($age > (4*12+11)) {
                $scoreCols["Total_1"] = "Respondent too old to score";
            }
            else {
                    $scoreCols["Total_1a"] = $this->scores["q_1_trial1"];
                    $scoreCols["Total_1b"] = $this->scores["q_1_trial2"];
                    $scoreCols["Total_1"] = 0;
                    $j = 2;
                    $numItems = 12;
                    for ($i = 2; $i <= $numItems; $i++) {
                        $scoreCols["Total_A2"] += $this->scores["q_{$j}_item{$i}"];
                        $j++;
                    }
                $scoreCols["Total_1"] += max($scoreCols["Total_1a"], $scoreCols["Total_1b"]);
            }


            // 2. Verbal Comprehension
            if ($age > (6*12+11)) {
                $scoreCols["Total_2"] = "Respondent too old to score";
            }
            else {
                $scoreCols["Total_2"] = 0;
                $j = 13;
                $numItems = 36;
                for ($i = 1; $i <= $numItems; $i++) {
                    $scoreCols["Total_2"] = $this->scores["q_{$j}_item{$i}"];
                    $j++;
                }
            }


            // 3. Picture Similarities
            if ($age > (7*12+11)) {
                $scoreCols["Total_3"] = "Respondent too old to score";
            }
            else {
                $scoreCols["Total_3"] = 0;
                $j=49;
                $numItems=32;
                for ($i = 1; $i <= $numItems; $i++) {
                    $scoreCols["Total_3"] = $this->scores["q_{$j}_item{$i}"];
                    $j++;
                }
            }


            // 4. Naming Vocabulary
            if ($age > (8*12+11)) {
                $scoreCols["Total_4"] = "Respondent too old to score";
            }
            else {
                $scoreCols["Total_4"] = 0;
                $j=81;
                $numItems=26;
                for ($i = 1; $i <= $numItems; $i++) {
                    $scoreCols["Total_4"] = $this->scores["q_{$j}_item{$i}"];
                    $j++;
                }
            }


            // 5. Recall of Objects - Immediate
            if ($age < 4*12) {
                $scoreCols["Total_4"] = "Respondent too young to score";
            }
            else {
                $scoreCols["Total_5a"] = $this->scores["q_107_trial1"];
                $scoreCols["Total_5b"] = $this->scores["q_107_trial2"];
                $scoreCols["Total_5c"] = 0;
                if ($scoreCols["Total_5a"] + $scoreCols["Total_5b"] == 40) {
                    $scoreCols["Total_5c"] = 20;
                } else {
                    $scoreCols["Total_5c"] = $this->scores["q_107_trial3"];
                }
                // if not spoiled
                $scoreCols["Total_5"] = ($scoreCols["Total_51"] + $scoreCols["Total_52"] + $scoreCols["Total_53"]);
                // else add the two successful * 1.5 -- round up to whole number
            }


            // 6. Pattern Construction
            if ($age < (3*12)) {
                $scoreCols["Total_6"] = "Respondent too young to score";
            }
            else {
                $scoreCols["Total_6"] = 0;
                $j=108;
                $numItems=26;
                for ($i = 1; $i <= $numItems; $i++) {
                    $scoreCols["Total_6"] = $this->scores["q_{$j}_item{$i}"];
                    $j++;
                }
            }


            // 7. Early Number Concepts
            if ($age > (7*12+11)) {
                $scoreCols["Total_7"] = "Respondent too old to score";
            }
            else {
                $scoreCols["Total_7"] = 0;
                $j=134;
                $numItems=28;
                for ($i = 1; $i <= $numItems; $i++) {
                    $scoreCols["Total_7"] = $this->scores["q_{$j}_item{$i}"];
                    $j++;
                }
            }


            // 8. Recall of Objects - Delayed
            if ($age < (4*12)) {
                $scoreCols["Total_8"] = "Respondent too young to score";
            }
            else {
                $scoreCols["Total_8"] = $this->scores["q_162_trial1"];
            }

            // 9. Copying
            if ($age < (3*12+6)) {
                $scoreCols["Total_9"] = "Respondent too young to score";
            }
            elseif ($age > (7*12+11)) {
                $scoreCols["Total_9"] = "Respondent too old to score";
            }
            else {
                $scoreCols["Total_9"] = 0;
                $j=163;
                $numItems=20;
                for ($i = 1; $i <= $numItems; $i++) {
                    $scoreCols["Total_9"] = $this->scores["q_{$j}_item{$i}"];
                    $j++;
                }
            }

        }
        else { // If older than 17 years 11 months
            for ($i = 1; $i <=9; $i++) {
                $scoreCols["Total_{$i}"] = "Respondent too old to score";
            }
        }
    }


    function _page1() {

        // 1. Block Building
        // Usual Age Range: 2 years 6 months to 3 years 5 months
        // Extended Age Range: 3 years 6 months to 4 years 11 months
        // All start at Item 1 unless Alternative Stopping Point is reached
        // Alternative Stopping Point - after 4 consecutive failures, STOP

        $this->form->addElement("header", null, "Block Building");
        $this->form->addElement('static', null, "<br />");

        // Item 1 - score better of two attempts
        $this->form->addElement("static", "null", "Item 1 - Trial 1");
        $this->form->addElement("select", "q_1_trial1", $this->indent . $this->indent . "Number of blocks used:", array("" => NULL,2=>"8 blocks",1=>"4-7 blocks",0=>"0-3 blocks","not_answered" => "Not Answered"));
        $this->XINRegisterRule("q_1_trial1", array("q_70_trial1_status{@}=={@}"), "Required.");
        $this->form->addElement("static", "null", "Item 1 - Trial 2");
        $this->form->addElement("select", "q_1_trial2done", $this->indent . $this->indent . "Was a second trial performed?", array("" => NULL, "yes" => "Yes", "no" => "No", "not_answered" => "Not Answered"));
        $this->XINRegisterRule("q_1_trial2done", array("q_70_trial2done_status{@}=={@}"), "Required.");
        $this->form->addElement("select", "q_1_trial2", $this->indent . $this->indent . "Number of blocks used:", array("" => NULL,2=>"8 blocks",1=>"4-7 blocks",0=>"0-3 blocks","not_answered" => "Not Answered"));
        $this->XINRegisterRule("q_1_trial2", array("q_1_trial2done{@}=={@}yes"), "This is required if a second trial was attempted.");

        $answerArray = array(""=>NULL, "correct"=>"Correct", "incorrect"=>"Incorrect", "not_answered"=>"Not Answered");
        $failArray = array(""=>NULL,"rotation"=>"Rotation", "reversal"=>"Reversal", "not_answered"=>"Not Answered");

        // Items 2 to 12
        $j=2;
        $numItems=12;
        for ($i = 2; $i <= $numItems; $i++) {
            $group[]=&$this->form->addElement("select", "q_{$j}_item{$i}", "Item $i", $answerArray);
            $group[]=&$this->form->addElement("select", "q_{$j}_item{$i}_f", $this->indent . $this->indent . "If incorrect, indicate the failure type:", $failArray);
            $this->XINRegisterRule("q_{$j}_item{$i}_f", array("q_{$j}_item{$i}{@}=={@}'incorrect"), "This is required if the response was a failure");
//            $this->form->addGroup($group, "q_{$j}_item{$i}"."_group", $label, null, false);
            $j++;
        }

        // Alternative Stopping Point - after 4 consecutive failures, STOP
        // Change to make it not answerable
//        $this->XINRegisterRule("q_{$j}_item{$i}_f",
//            array("q_{$j-1}_item{$i-1}{@}=={@}'incorrect",
//                "q_{$j-2}_item{$i-2}{@}=={@}'incorrect",
//                "q_{$j-3}_item{$i-3}{@}=={@}'incorrect",
//                "q_{$j-4}_item{$i-4}{@}=={@}'incorrect"),
//            "This field cannot be filled due to an Alternative Stopping Point (4 consecutive failures).");

        $this->form->addElement('static', null, "<br />");
        $this->form->addElement("textarea", "other_comments1", "Comments:", array('cols'=>25, 'rows'=>4));
        $this->XINRegisterRule("other_comments1", array("{other_comments1}{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement('static', null, "<br />");

    }


    function _page2() {

        // 2. Verbal Comprehension
        // Usual Age Range: 2 years 6 months to 5 years 11 months
        // Out of Level: 6 years 0 months to 6 years 11 months
        // Alternative Stopping Point: After 5 consecutive failures, if at least 3 passes STOP
        // <3 passes on all, go back to previous starting point

        $this->form->addElement("header", null, "Verbal Comprehension");
        $this->form->addElement('static', null, "<br />");

        // If you suspect that a child will have difficulty with the starting items for his or her age,
        // use the Starting and Decision Points for a younger age group.
        // Out-of-level testing for children of average or low ability only

        $answerArray = array(""=>NULL, "correct"=>"Correct", "incorrect"=>"Incorrect", "not_answered"=>"Not Answered");

        $j=13;
        $numItems=36;
        for ($i = 1; $i <= $numItems; $i++) {
            switch ($i) {
                case 1:
                    $this->form->addElement("header", null, "Items 1-6: Teddy Bear");
                    break;
                case 7:
                    $this->form->addElement('static', null, "<br />");
                    $this->form->addElement("header", null, "Items 7-18: Toys");
                    break;
                case 19:
                    $this->form->addElement('static', null, "<br />");
                    $this->form->addElement("header", null, "Items 19-29: Inset Tray");
                    break;
                case 30:
                    $this->form->addElement('static', null, "<br />");
                    $this->form->addElement("header", null, "Items 30-36: Chips");
                    break;
            }
            $this->form->addElement("select", "q_{$j}_item{$i}", $this->indent . $this->indent . "Item $i", $answerArray);
            $j++;
        }

        // 2 years 6 months to 3 years 11 months
        // Item 1 to 12 (Decision Point), 13 to 29 (Decision Point)
        // Decision Point: stop unless <3 failures on all given continue to next DP;
        // <3 passes on all items go back to previous starting point

        // 4 years 0 months to 5 years 11 months
        // Item 13 to 36
        // 6 years 0 months to 6 years 11 months
        // * Out-of-level testing for children of average or low ability only
        // Item 13 to 36

        $this->form->addElement('static', null, "<br />");
        $this->form->addElement("textarea", "other_comments2", "Comments:", array('cols'=>25, 'rows'=>4));
        $this->XINRegisterRule("other_comments2", array("{other_comments2}{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement('static', null, "<br />");

    }


    function _page3() {

        // 3. Picture Similarities
        // Usual Age Range: 2 years 6 months to 5 years 11 months
        // Out of Level: 6 years 0 months to 7 years 11 months

        $this->form->addElement("header", null, "Picture Similarities");
        $this->form->addElement('static', null, "<br />");

        $answerArray = array(""=>NULL, "correct"=>"Correct", "incorrect"=>"Incorrect", "not_answered"=>"Not Answered");
        $responseArray = array(""=>NULL, 1=>1, 2=>2, 3=>3, 4=>4, "not_answered"=>"Not Answered");

        $j=49;
        $numItems=32;
        for ($i = 1; $i <= $numItems; $i++) {
            $this->form->addElement("select", "q_{$j}_item{$i}", "Item $i", $answerArray);
            $this->form->addElement("select", "q_{$j}_item{$i}_response", $this->indent . $this->indent . "Child's Response:", $responseArray);
            $this->XINRegisterRule("q_{$j}_item{$i}_response", array("q_{$j}_item{$i}{@}=={@}correct"), "This is required if the child answered Item {$i} correctly.");
//            $this->XINRegisterRule("q_{$j}_item{$i}_response", array("q_{$j}_item{$i}{@}=={@}incorrect", "q_{$j}_item{$i}{@}=={@}not_answered"), "Any data entered will not be saved.");
            $j++;
        }

        $this->form->addElement('static', null, "<br />");
        $this->form->addElement("textarea", "other_comments3", "Comments:", array('cols'=>25, 'rows'=>4));
        $this->XINRegisterRule("other_comments3", array("{other_comments3}{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement('static', null, "<br />");

    }


    function _page4() {

        // 4. Naming Vocabulary
        // Usual Age Range: 2 years 6 months to years months
        // Extended Age Range: 6 years 0 months to 7 years 11 months
        // Out of Level: 8 years 0 months to 8 years 11 months

        $this->form->addElement("header", null, "Naming Vocabulary");
        $this->form->addElement('static', null, "<br />");

        $answerArray = array(""=>NULL, "correct"=>"Correct", "incorrect"=>"Incorrect", "not_answered"=>"Not Answered");
        $yesNoNa = array(""=>NULL, "yes"=>"Yes", "no"=>"No", "not_answered"=>"Not Answered");

        $j=81;
        $numItems=26;
        for ($i = 1; $i <= $numItems; $i++) {
            $this->form->addElement("select", "q_{$j}_item{$i}", "Item {$i}", $answerArray);

            // Does this include "Other acceptable responses????"
            // Change answerArray to Object or Picture, Other Acceptable Response, Incorrect Response??
            $this->form->addElement("select", "q_{$j}_item{$i}_other",
                $this->indent . $this->indent . "Did the child give a response other than the one listed on the Record Form?", $yesNoNa);
            $this->XINRegisterRule("q_{$j}_item{$i}_other", array("q_{$j}_item{$i}_other{@}=={@}yes"), "Required.");
            // Don't allow to fill out if no or other answer

            $this->form->addElement("advcheckbox", "q_{$j}_item{$i}_q", $this->indent . $this->indent . "Q?", $options=null);
            $this->XINRegisterRule("q_{$j}_item{$i}_q", array("q_{$j}_item{$i}{@}=={@}incorrect"), "Required.");

            $this->form->addElement("textarea", "q_{$j}_item{$i}_response", $this->indent . $this->indent . "Response:", array('cols'=>25, 'rows'=>1));
            $this->XINRegisterRule("q_{$j}_item{$i}_response", array("q_{$j}_item{$i}_other{@}=={@}yes"), "Required.");

            $j++;
        }

    // Q if incorrect

        // only record if not listed in Record form

        // 2:6-4>5 Item 1-16
        // 4:6-7:11 Item 8-26
        // 8:0-8:11 Item 8-26

        // Decision Point: Stop unless <3 failures (con't), <3 passes (SP)
        // ASP: 5 consecutive failures, 3+ passes (Stop), <3 passes (SP)

        $this->form->addElement('static', null, "<br />");
        $this->form->addElement("textarea", "other_comments4", "Comments:", array('cols'=>25, 'rows'=>4));
        $this->XINRegisterRule("other_comments4", array("{other_comments4}{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement('static', null, "<br />");

    }


    function _page5() {

        // 5. Recall of Objects - Immediate
        // Usual Age Range: 4 years 0 months to 17 years 11 months
        // Range must be 0 to 20 for each trial

        $this->form->addElement("header", null, "Recall of Objects - Immediate");
        $this->form->addElement('static', null, "<br />");

        $yesNoNa = array(""=>NULL, "yes"=>"Yes", "no"=>"No", "not_answered"=>"Not Answered");

        $this->form->addElement("static", "null", "Trial 1");
        $this->form->addElement("select", "q_107_trial1_success", $this->indent . $this->indent . "Was the trial successful?", $yesNoNa);
        $this->addNumericElement("q_107_trial1", $this->indent . $this->indent . "Number of objects recalled correctly:");
        $this->XINRegisterRule("q_107_trial1", array("q_107_trial1_success{@}=={@}yes"), "Required.");
//        if (!in_array($q_107_trial1_success, range(0,20))) {
//            return "Please enter a value between 0 and 20.";
//        }

        $this->form->addElement("static", "null", "Trial 2");
        $this->form->addElement("select", "q_107_trial2_success", $this->indent . $this->indent . "Was the trial successful?", $yesNoNa);
        $this->addNumericElement("q_107_trial2", $this->indent . $this->indent . "Number of objects recalled correctly:");
        $this->XINRegisterRule("q_107_trial2", array("q_107_trial2_success{@}=={@}yes"), "Required.");

        // if first two = 20, skip 30 and make equal to 30
        $this->form->addElement("static", "null", "Trial 3");
        $this->form->addElement("select", "q_107_trial3_success", $this->indent . $this->indent . "Was the trial successful?", $yesNoNa);
        $this->addNumericElement("q_107_trial3", $this->indent . $this->indent . "Number of objects recalled correctly:");
        $this->XINRegisterRule("q_107_trial3", array("q_107_trial3_success{@}=={@}yes"), "Required.");

        // require 2 trials
        // if spoiled or unscorable...

        $this->form->addElement('static', null, "<br />");
        $this->form->addElement("textarea", "other_comments5", "Comments:", array('cols'=>25, 'rows'=>4));
        $this->XINRegisterRule("other_comments5", array("{other_comments5}{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement('static', null, "<br />");

    }


    function _page6() {

        // 6. Pattern Construction
        // Usual Age Range: 3 years 6 months to 17 years 11 months
        // Out of Level: 3 years 0 months to 3 years 5 months
        // DP
        // ASP

        $this->form->addElement("header", null, "Pattern Construction");
        $this->form->addElement('static', null, "<br />");

        $doubleTrialArray = array(""=>NULL, "p_1"=>"(a) Passed first trial", "p_2"=>"(b) Passed second trial",
            "f"=>"Failed both trials", "not_answered"=>"Not Answered");
        $singleTrialArray = array(""=>NULL, "p"=>"Pass", "f"=>"Fail", "not_answered"=>"Not Answered");

        // radio - was a second trial completed/needed?
        // Correctness, response time - check paper form!

        $j=108;

        $this->form->addElement("select", "q_{$j}_item1", "Item 1", $doubleTrialArray);
        $j++;

        $numItems=25; //26 including item 1
        for ($i = 2; $i <= $numItems; $i++) {
            $this->form->addElement("static","null","Item $i");

            switch ($i) {
                case 2:
                case 4:
                case 8:
                case 9:
                case 14:
                case 15:
                    $this->form->addElement("select", "q_{$j}_item{$i}", $this->indent . $this->indent . "Trial Outcome:", $doubleTrialArray);
                    $this->addNumericElement("q_{$j}_item{$i}_response_time1", $this->indent . $this->indent . "Trial 1 Response Time (in seconds):");
                    $this->addNumericElement("q_{$j}_item{$i}_response_time2", $this->indent . $this->indent . "Trial 2 Response Time (in seconds):");
                    $this->XINRegisterRule("q_{$j}_item{$i}_response_time2", array("q_{$j}_item{$i}{@}=={@}p_2", "q_{$j}_item{$i}{@}=={@}f"));
                    break;
                default:
                    $this->form->addElement("select", "q_{$j}_item{$i}", $this->indent . $this->indent . "Trial Outcome:", $singleTrialArray);
                    $this->addNumericElement("q_{$j}_item{$i}_response_time1", $this->indent . $this->indent . "Response Time (in seconds):");
            }
            $j++;
        }

        // Alternative (Unspeeded) Administration????

        $this->form->addElement('static', null, "<br />");
        $this->form->addElement("textarea", "other_comments6", "Comments:", array('cols'=>25, 'rows'=>4));
        $this->XINRegisterRule("other_comments6", array("{other_comments6}{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement('static', null, "<br />");

    }


    function _page7() {

        // 7. Early Number Concepts
        // Usual Age Range: 3 years 6 months to 5 years 11 months
        // Extended Age Range: 6 years 0 months to 6 years 5 months
        // Out of Level: 2 years 6 months to 3 years 5 months
        // Out of Level: 6 years 6 months to 7 years 11 months

        $this->form->addElement("header", null, "Early Number Concepts");
        $this->form->addElement('static', null, "<br />");

        $answerArray = array(""=>NULL, "correct"=>"Correct", "incorrect"=>"Incorrect", "not_answered"=>"Not Answered");

        $j=134;

        $this->form->addElement("select", "q_{$j}_item1", $this->indent . $this->indent . "Item 1", $answerArray);

        $numItems=27; // +1 for item1
        for ($i = 2; $i <= $numItems; $i++) {
            $this->form->addElement("select", "q_{$j}_item{$i}", $this->indent . $this->indent . "Item {$i}", $answerArray);
//            $this->form->addElement("radio", "q_{$j}_item{$i}_q", $this->indent . "Q?");
//            $this->addLargeTextAreaElement("q_{$j}_item{$i}_text", $this->indent . "Response:");
            $j++;


            // 1 point for correct, 0 for incorrect except item 1 (2-28)
            // item 1 - 0-3 for pointing, 0-3 for reciting; if score < 6, second trial is given
            // Child recites to: 1-3, 4-6, 7-9, 10    --> (0,1,2,3)
            // Child recites and points to: ...
            // use better of two scores of each trial
            // Trial 1: circle
            // Trial 2: X
            // See Appendix A

            // 1.       Score       0       1       2       3   Score (0-3)
            //Recites           0 1 2 3   4 5 6     7 8 9   10      ?
            //Points w/reciting 0 1 2 3   4 5 6     7 8 9   10      ?
            // Circle first trial
            // X second trial
        }

        $this->form->addElement('static', null, "<br />");
        $this->form->addElement("textarea", "other_comments7", "Comments:", array('cols'=>25, 'rows'=>4));
        $this->XINRegisterRule("other_comments7", array("{other_comments7}{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement('static', null, "<br />");
    }


    function _page8() {

        // 8. Recall of Objects - Delayed
        // Usual Age Range: 4 years 0 months to 17 years 11 months

        $this->form->addElement("header", null, "Recall of Objects - Delayed");
        $this->form->addElement('static', null, "<br />");

        // delayed recall trial max raw score: 20 points
        // only use if significantly different from immediate-recall score
        // convert immediate and delayed to T-scores
        // T scores differ by 14+ --> statistically significant

        $this->addNumericElement("q_162_trial1", $this->indent . $this->indent . "Number of objects recalled correctly:");

        $this->form->addElement('static', null, "<br />");
        $this->form->addElement("textarea", "other_comments8", "Comments:", array('cols'=>25, 'rows'=>4));
        $this->XINRegisterRule("other_comments8", array("{other_comments8}{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement('static', null, "<br />");

    }

    function _page9() {

        // 9. Copying
        // Usual Age Range: 3 years 6 months to 5 years 11 months
        // Out of Level: 6 years 0 months to 7 years 11 months
        // DP
        // ASP

        $this->form->addElement("header", null, "Copying");
        $this->form->addElement('static', null, "<br />");

        // 2 stages
        // Elaborations (irrelevant lines/figures) = 0
        // Overworked/feathered lines = 1
        // Scribbled lines = 0
        // Appendix B

        // First stage: rough eval
        // P/F column --> P for apparent pass, P+ for apparent maximum score response, F for apparent failure
        // Second stage: final scoring

        // Total: out of 44 ?

        $answerArray1 = array(""=>NULL, 0=>0, 1=>1, "not_answered"=>"Not Answered");
        $answerArray2 = array(""=>NULL, 0=>0, 1=>1, 2=>2, "not_answered"=>"Not Answered");
        $answerArray3 = array(""=>NULL, 0=>0, 1=>1, 2=>2, 3=>3, "not_answered"=>"Not Answered");

        $j=163;
        $numItems=20;
        for ($i = 1; $i <= $numItems; $i++) {
            switch ($i) {
                case 1:
                    $this->form->addElement("select", "q_{$j}_item{$i}", $this->indent . $this->indent . "Item $i", $answerArray1);
                    break;
                case 12:
                case 15:
                case 16:
                case 17:
                case 18:
                    $this->form->addElement("select", "q_{$j}_item{$i}", $this->indent . $this->indent . "Item $i", $answerArray3);
                    break;
                // items 2-11, 13, 14, 19, 20
                default:
                    $this->form->addElement("select", "q_{$j}_item{$i}", $this->indent . $this->indent . "Item $i", $answerArray2);
                    break;
            }
            $j++;
        }

        $this->form->addElement('static', null, "<br />");
        $this->form->addElement("textarea", "other_comments9", "Comments:", array('cols'=>25, 'rows'=>4));
        $this->XINRegisterRule("other_comments9", array("{other_comments9}{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement('static', null, "<br />");
    }
}


?>