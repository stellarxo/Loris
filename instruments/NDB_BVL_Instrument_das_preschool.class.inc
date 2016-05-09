<?php

require_once 'HTML/QuickForm.php';
require_once 'HTML/QuickForm/Renderer/Array.php';

class NDB_BVL_Instrument_das_preschool extends NDB_BVL_Instrument
{

    // TO DO:

    // _score()

    // _page#()
    // ASP & DPs
    // age constraints
    // second attempts??
    // forced numbers

    // END


    /*
    INSERT INTO test_names (Test_name, Full_name, Sub_group) VALUES ('das_preschool', 'DAS (Differential Ability
    Scales) - Preschool Core', '1');

    INSERT INTO instrument_subtests (Test_name, Subtest_name, Description, Order_number) VALUES ('das_preschool', 'das_preschool_page1', 'Block Building', 1);
    INSERT INTO instrument_subtests (Test_name, Subtest_name, Description, Order_number) VALUES ('das_preschool', 'das_preschool_page2', 'Verbal Comprehension', 2);
    INSERT INTO instrument_subtests (Test_name, Subtest_name, Description, Order_number) VALUES ('das_preschool', 'das_preschool_page3', 'Picture Similarities', 3);
    INSERT INTO instrument_subtests (Test_name, Subtest_name, Description, Order_number) VALUES ('das_preschool', 'das_preschool_page4', 'Naming Vocabulary', 4);
    INSERT INTO instrument_subtests (Test_name, Subtest_name, Description, Order_number) VALUES ('das_preschool', 'das_preschool_page5', 'Recall of Objects - Immediate', 5);
    INSERT INTO instrument_subtests (Test_name, Subtest_name, Description, Order_number) VALUES ('das_preschool', 'das_preschool_page6', 'Pattern Construction', 6);
    INSERT INTO instrument_subtests (Test_name, Subtest_name, Description, Order_number) VALUES ('das_preschool', 'das_preschool_page7', 'Early Number Concepts', 7);
    INSERT INTO instrument_subtests (Test_name, Subtest_name, Description, Order_number) VALUES ('das_preschool', 'das_preschool_page8', 'Recall of Objects - Delayed', 8);
    INSERT INTO instrument_subtests (Test_name, Subtest_name, Description, Order_number) VALUES ('das_preschool', 'das_preschool_page9', 'Copying', 9);

    INSERT INTO test_battery (Test_name, AgeMinDays, AgeMaxDays, Active, Stage, SubprojectID, Visit_label, CenterID)
    VALUES ('das_preschool', '1', '99999', 'Y', 'Visit', '1', 'V37Plus', NULL);
    */


    var $j = 1;
    var $answerArray = array(""=>NULL, 0=>0, 1=>1, "not_answered"=>"Not Answered");
    var $responseArray = array(""=>NULL, 1=>1, 2=>2, 3=>3, 4=>4, "not_answered"=>"Not
        Answered");
    var $yesNoNa = array(""=>NULL, "yes"=>"Yes", "no"=>"No", "not_answered"=>"Not Answered");


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
        $this->testName = "das_preschool";
        $this->table = 'das_preschool';
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
                'other_comments9'
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

//        $query = "SELECT * FROM $this->table WHERE CommentID='".$this->getCommentID()."'";
//        $record=array();
//        $db->selectRow($query, $record);
/*
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
*/

        if(preg_match("/das_preschool(_page[0-9]+)/",$this->page,$matches)){
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
        $this->form->addElement('header', 'instrument_title', "DAS - Preschool Core");

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

/*
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
*/

    function _page1() {

        // 1. Block Building
        // Usual Age Range: 2 years 6 months to 3 years 5 months
        // Extended Age Range: 3 years 6 months to 4 years 11 months
        // All start at Item 1 unless Alternative Stopping Point is reached
        // Alternative Stopping Point - after 4 consecutive failures, STOP

        $this->form->addElement("header", null, "Block Building");
        $this->form->addElement('static', null, "<br />");

        // Item 1 - score better of two attempts
        $this->form->addElement("static", null, "Item 1 - Trial 1");
        $this->form->addElement("select", "q_{$this->j}_trial1", $this->indent . $this->indent . "Number of blocks used:", array("" => NULL,2=>"8 blocks",1=>"4-7 blocks",0=>"0-3 blocks","not_answered" => "Not Answered"));
        $this->XINRegisterRule("q_1_trial1", array("q_70_trial1_status{@}=={@}"), "Required.");
        $this->form->addElement("static", null, "Item 1 - Trial 2");
        $this->form->addElement("select", "q_{$this->j}_trial2done", $this->indent . $this->indent . "Was a second trial performed?", array("" => NULL, "yes" => "Yes", "no" => "No", "not_answered" => "Not Answered"));
        $this->XINRegisterRule("q_1_trial2done", array("q_70_trial2done_status{@}=={@}"), "Required.");
        $this->form->addElement("select", "q_{$this->j}_trial2", $this->indent . $this->indent . "Number of blocks used:", array("" => NULL,2=>"8 blocks",1=>"4-7 blocks",0=>"0-3 blocks","not_answered" => "Not Answered"));
        $this->XINRegisterRule("q_1_trial2", array("q_1_trial2done{@}=={@}yes"), "This is required if a second trial was attempted.");
        $this->j++;

        $failArray = array(""=>NULL,"rotation"=>"Rotation", "reversal"=>"Reversal", "not_answered"=>"Not Answered");


        // Items 2 to 12
        $numItems=12;
        for ($i = 2; $i <= $numItems; $i++) {
            $group[]=&$this->form->addElement("select", "q_{$this->j}_item{$i}", "Item $i", $this->answerArray);
            $group[]=&$this->form->addElement("select", "q_{$this->j}_item{$i}_f", $this->indent . $this->indent . "If incorrect, indicate the failure type:", $failArray);
            $this->XINRegisterRule("q_{$this->j}_item{$i}_f", array("q_{$this->j}_item{$i}{@}=={@}'incorrect"), "This is required if the response was a failure");
//            $this->form->addGroup($group, "q_{$this->j}_item{$i}"."_group", $label, null, false);
            $this->j++;
        }



        // Alternative Stopping Point - after 4 consecutive failures, STOP
        // Change to make it not answerable
//        $this->XINRegisterRule("q_{$this->j}_item{$i}_f",
//            array("q_{$this->j-1}_item{$i-1}{@}=={@}'incorrect",
//                "q_{$this->j-2}_item{$i-2}{@}=={@}'incorrect",
//                "q_{$this->j-3}_item{$i-3}{@}=={@}'incorrect",
//                "q_{$this->j-4}_item{$i-4}{@}=={@}'incorrect"),
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

        $item = array(1=>"Show me teddy's eyes.", 2=>"Show me teddy's mouth.", 3=>"Show me teddy's arms.",
            4=>"Show me teddy's ears.", 5=>"Show me teddy's legs.", 6=>"Show me teddy's ribbon.",
            7=>"Give me the car.", 8=>"Give me the horse.", 9=>"Give me the pencil.", 10=>"Give me the watch.",
            11=>"Give me the button.", 12=>"Put the horse in the box.", 13=>"Give me the one we draw with.",
            14=>"Give me the one that shows the time.", 15=>"Give me all the things that have hair.",
            16=>"Give me all the things you can wear.", 17=>"Give me all the animals except the cats.",
            18=>"Give me all the things that don't eat.", 19=>"Put a tree behind your back.",
            20=>"Make the truck move to me.", 21=>"Make a child stand on the bridge.", 22=>"Put the car under the bridge.",
            23=>"Make the two children face each other.", 24=>"When I put down the tree, pick up the car.",
            25=>"Put the tree that is little next to the house that is big.",
            26=>"Before you give me the truck, give me the little house.", 27=>"Put a house on each side of the car.",
            28=>"While you touch the truck, give me the car.", 29=>"Put a chid between the trees.",
            30=>"Put the circle farther away from you than the square.", 31=>"Give me the chips that are blue but not round.",
            32=>"Pick up the circles if they are blue or yellow.", 33=>"Give me all the red chips except the square.",
            34=>"Give me not only all the red but also all the round chips.",
            35=>"Give me all the chips that are neither yellow nor blue.", 36=>"Give me all the chips that are neither red nor square.");

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
            $this->form->addElement("select", "q_{$this->j}_item{$i}", $this->indent . $this->indent . "Item $i: {$item[$i]}", $this->answerArray);
            $this->j++;
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

        $group[] = &$this->form->createElement("static", "static_response_label", "", "Response");
        $group[] = &$this->form->createElement("static", "static_score_label", "", "Score");

        $this->form->addGroup($group, null, "", $this->_GUIDelimiter, false);
        unset($group);

        $numItems=32;
        for ($i = 1; $i <= $numItems; $i++) {
            $group[]=&$this->form->createElement("select", "q_{$this->j}_item{$i}", null, $this->answerArray);
            $group[]=&$this->form->createElement("select", "q_{$this->j}_item{$i}_response", null,
                $this->responseArray);
            $group[] = $this->form->createElement("static", null, $this->indent);
            $group[] = $this->form->createElement("static", null, $this->indent);
            $group[] = $this->form->createElement("static", null, $this->indent);
            $group[] = $this->form->createElement("static", null, $this->indent);
            $group[] = $this->form->createElement("static", null, $this->indent);
            $group[] = $this->form->createElement("static", null, $this->indent);
            $group[] = $this->form->createElement("static", null, $this->indent);
            $group[] = $this->form->createElement("static", null, $this->indent);

            $this->form->addGroup($group, "{$i}_answer", "Item $i", $this->_GUIDelimiter, false);
            unset($group);

            $this->XINRegisterRule("q_{$this->j}_item{$i}_response", array("q_{$this->j}_item{$i}{@}=={@}correct"), "This is required if the child answered Item {$i} correctly.");
//            $this->XINRegisterRule("q_{$this->j}_item{$i}_response", array("q_{$this->j}_item{$i}{@}=={@}incorrect", "q_{$this->j}_item{$i}{@}=={@}not_answered"), "Any data entered will not be saved.");
            $this->j++;
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



        $item = array(1=>"Paper", 2=>"Box (Closed)", 3=>"Chair", 4=>"Key", 5=>"Fish", 6=>"Scissors", 7=>"Watch",
            8=>"Window", 9=>"Sink", 10=>"Brush", 11=>"Helicopter", 12=>"Triangle", 13=>"Ring", 14=>"Chain",
            15=>"Shell, Seashell", 16=>"Jar", 17=>"Switch", 18=>"Volcano", 19=>"Thermometer", 20=>"Measuring Cup",
            21=>"Igloo", 22=>"Paper Clip", 23=>"Anchor",  24=>"Hourglass", 25=>"Funnel", 26=>"Easel");

        $numItems=26;
        for ($i = 1; $i <= $numItems; $i++) {
            $this->form->addElement("select", "q_{$this->j}_item{$i}", "Item $i: $item[$i]", $this->answerArray);

            // Does this include "Other acceptable responses????"
            // Change answerArray to Object or Picture, Other Acceptable Response, Incorrect Response??


            $this->form->addElement("select", "q_{$this->j}_item{$i}_other",
                $this->indent . $this->indent . "Did the child give a response other than the one listed on the Record Form?", $this->yesNoNa);

            $this->XINRegisterRule("q_{$this->j}_item{$i}_other", array("q_{$this->j}_item{$i}_other{@}=={@}yes"), "Required.");
            // Don't allow to fill out if no or other answer

            $this->form->addElement("advcheckbox", "q_{$this->j}_item{$i}_q", $this->indent . $this->indent . "Q?", $options=null);
            $this->XINRegisterRule("q_{$this->j}_item{$i}_q", array("q_{$this->j}_item{$i}{@}=={@}incorrect"), "Required.");

            $this->form->addElement("textarea", "q_{$this->j}_item{$i}_response", $this->indent . $this->indent . "Response:", array('cols'=>25, 'rows'=>1));
            $this->XINRegisterRule("q_{$this->j}_item{$i}_response", array("q_{$this->j}_item{$i}_other{@}=={@}yes"), "Required.");

            $this->j++;
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

        $current = "Number of objects recalled correctly ";
        $this->form->addElement("static", null, "Trial 1");
        $this->form->addElement("select", "q_{$this->j}_trial1_success", $this->indent . $this->indent . "Was the trial successful?", $this->yesNoNa);
        $this->addNumericElement("q_{$this->j}_trial1", $this->indent . $this->indent . $current);
        $this->XINRegisterRule("q_{$this->j}_trial1", array("q_{$this->j}_trial1_success{@}=={@}yes"), "Required.");
//        if (!in_array($q_107_trial1_success, range(0,20))) {
//            return "Please enter a value between 0 and 20.";
//        }

        $this->form->addElement("static", null, "Trial 2");
        $this->form->addElement("select", "q_{$this->j}_trial2_success", $this->indent . $this->indent . "Was the trial successful?", $this->yesNoNa);
        $this->addNumericElement("q_{$this->j}_trial2", $this->indent . $this->indent . $current);
        $this->XINRegisterRule("q_{$this->j}_trial2", array("q_{$this->j}_trial2_success{@}=={@}yes"), "Required.");

        // if first two = 20, skip 30 and make equal to 30
        $this->form->addElement("static", null, "Trial 3");
        $this->form->addElement("select", "q_{$this->j}_trial3_success", $this->indent . $this->indent . "Was the trial successful?", $this->yesNoNa);
        $this->addNumericElement("q_{$this->j}_trial3", $this->indent . $this->indent . $current);
        $this->XINRegisterRule("q_{$this->j}_trial3", array("q_{$this->j}_trial3_success{@}=={@}yes"), "Required.");

        $this->j++;

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

        $this->form->addElement("header", null, "Pattern Construction");
        $this->form->addElement('static', null, "<br />");


        $doubleTrialArray = array("" => NULL, "p_1" => "(a) Passed first trial", "p_2" => "(b) Passed second trial",
            "f" => "Failed both trials", "not_answered" => "Not Answered");
        $singleTrialArray = array("" => NULL, "p" => "Pass", "f" => "Fail", "not_answered" => "Not Answered");
//        $options_30 = $this->_generateNumbers(0, 30);
//        $options_45 = $this->_generateNumbers(0, 45);
//        $options_60 = $this->_generateNumbers(0, 60);
        $options = array("" => NULL, 1 => "TEMP");


        // radio - was a second trial completed/needed?
        // Correctness, response time - check paper form!

        ///// NEED TO UPDATE OPTIONS OF TIMES
        //// Time/PF messed up --> check book

        $group[] = $this->form->createElement("static", null, $this->indent);

        $group[] = &$this->form->createElement("static", "static_time_label", "", "Time");
        $group[] = &$this->form->createElement("static", "static_P/F_label", "", "P/F");

        $this->form->addGroup($group, null, "", $this->_GUIDelimiter, false);
        unset($group);

        $numItems = 26;
        for ($i = 1; $i <= $numItems; $i++) {
            for ($k = 1; $k <= 2; $k++) {

                $group[] =& $this->form->createElement("static", "q_{$this->j}_item{$i}_static_trial{$k}", null, "Trial 
            $k");
                $group[] =& $this->form->createElement("select", "q_{$this->j}_item{$i}_trial{$k}", null, $doubleTrialArray);
                $group[] =& $this->form->createElement("select", "q_{$this->j}_item{$i}_response_time2_trial{$k}", null,
                    $options);

                if ($k == 1) {
                    $this->form->addGroup($group, "{$i}_answer_trial{$k}", "Item $i", $this->_GUIDelimiter,
                        false);
                    unset($group);
                } else {
                    $this->form->addGroup($group, "{$i}_answer_trial{$k}", null, $this->_GUIDelimiter,
                        false);
                    unset($group);
                }
            }
            $this->j++;
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

        $this->form->addElement("select", "q_{$this->j}_item1", $this->indent . $this->indent . "Item 1", $this->answerArray);

        $numItems=27; // +1 for item1
        for ($i = 2; $i <= $numItems; $i++) {
            $this->form->addElement("select", "q_{$this->j}_item{$i}", $this->indent . $this->indent . "Item {$i}", $this->answerArray);
//            $this->form->addElement("radio", "q_{$this->j}_item{$i}_q", $this->indent . "Q?");
//            $this->addLargeTextAreaElement("q_{$this->j}_item{$i}_text", $this->indent . "Response:");
            $this->j++;


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

        $current = "Number of objects recalled correctly ";
        $this->addNumericElement("q_{$this->j}_trial1", $this->indent . $this->indent . $current);

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

        $answerArray2 = array(""=>NULL, 0=>0, 1=>1, 2=>2, "not_answered"=>"Not Answered");
        $answerArray3 = array(""=>NULL, 0=>0, 1=>1, 2=>2, 3=>3, "not_answered"=>"Not Answered");

        $numItems=20;
        for ($i = 1; $i <= $numItems; $i++) {
            switch ($i) {
                case 1:
                    $this->form->addElement("select", "q_{$this->j}_item{$i}", $this->indent . $this->indent . "Item $i", $this->answerArray);
                    break;
                case 12:
                case 15:
                case 16:
                case 17:
                case 18:
                    $this->form->addElement("select", "q_{$this->j}_item{$i}", $this->indent . $this->indent . "Item $i", $answerArray3);
                    break;
                // items 2-11, 13, 14, 19, 20
                default:
                    $this->form->addElement("select", "q_{$this->j}_item{$i}", $this->indent . $this->indent . "Item $i", $answerArray2);
                    break;
            }
            $this->j++;
        }

        $this->form->addElement('static', null, "<br />");
        $this->form->addElement("textarea", "other_comments9", "Comments:", array('cols'=>25, 'rows'=>4));
        $this->XINRegisterRule("other_comments9", array("{other_comments9}{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement('static', null, "<br />");
    }
}


?>