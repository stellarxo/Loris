<?php
class NDB_BVL_Instrument_das extends NDB_BVL_Instrument
{

    // TO DO LIST:
    // SQL queries
    // Age constraints --> not show or populate as not_answered?
    // Add comment section to each page?
    // second attempts??
    // paper form

    // setup()
    //_requiredElements --> finish this
    // $this->localDefaults ???
    // DDE ignore

    // Check rules

    // _score()
    // conversion array
    // scoring

    // _page#()
    // ASP & DPs

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

//        $this->localDefaults = array_merge($this->localDefaults, array("trial"=>"Trial", "outcome"=>"Outcome", "correct"=>"# Correct", "trials"=>"# Trials"));


	    // Array of column names to be ignored by the double data entry conflict detector
        $this->_doubleDataEntryDiffIgnoreColumns =
            array('CommentID', 'UserID', 'Testdate',  'Window_Difference', 'Candidate_Age');

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

//        $this->_getAge();

        // AGE RELATED CONSTRAINTS HERE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

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

        $this->form->addElement('header', 'raw_scores', "Raw Scores");
        $this->form->addElement("static", null, "NOTE: Final scores must be calculated.");

        $this->form->addElement("static", null, "<BR>");

        $scoreLabels = array("Total_A"=>"Block Building Score",
            "Total_B"=>"Verbal Comprehension Score",
            "Total_C"=>"Picture Similarities Score",
            "Total_D"=>"Naming Vocabulary Score",
            "Total_E"=>"Recall of Objects - Immediate Score",
            "Total_F"=>"Pattern Construction Score",
            "Total_G"=>"Early Number Concepts Score",
            "Total_H"=>"Recall of Objects - Delayed Score",
            "Total_I"=>"Copying Score"
        );

        foreach ($scoreLabels as $field=>$label) {
            if(in_array($field,
                    array("Total_A", "Total_B", "Total_C", "Total_D", "Total_E",
                        "Total_F", "Total_G", "Total_H", "Total_I")) == TRUE) {
                $label = $this->indent . $this->indent . $label;
            }
            $this->form->addElement("static", $field, $label);
        }

        $this->form->addElement('static', null, "<br /><br />");

        $this->form->addElement("textarea", "other_comments", "Comments about Validity:", array('cols'=>25, 'rows'=>4));
        $this->XINRegisterRule("other_comments", array("{other_comments}{@}=={@}NEVER_REQUIRED"));

    }


    function _score() {

        $db =& Database::singleton();

        // skip scoring if proband DoB was not entered, i.e. data entry is not completed
        if(empty($this->respondentAgeYears)){
            return;
        }

        // null scores
        $this->_nullScores($this->scoreCols);
        // Get the item scores
        $query = "SELECT * FROM $this->table WHERE CommentID='".$this->getCommentID()."'";
        $record=array();
        $db->selectRow($query, $record);

        $conversion = array('incorrect'=>0,'correct'=>1,
            0=>0, 1=>1, 2=>2,
            //'p'=>1,
            'p_1'=>3, 'p_2'=>1, 'f'=>0
            );

        foreach ($record as $field=>$code) {
            if(!in_array($field, array(""))) {
                $this->scores[$field] = substr($code,0,1);
                if(is_numeric($this->scores[$field])) {
                    $intval = intval($this->scores[$field]);
                    $this->scores[$field] = $conversion[$intval];
                }
                else {
                    $this->scores[$field] = 0; // for 'not_answered'
                }
            }
        }

        //Age 0 years 0 months to 2 years 5 months
        if ($this->respondentAgeYears < 2) {
            $scoreCols["A_Total"] = "Respondent too young to score";
            //Diagnostic Algorithm, 2y -> 3y11m
        }
        elseif ($this->respondentAgeYears >= 2 && $this->respondentAgeYears < 3.5) {

            // 1. Block Building
            $scoreCols["Total_A1a"] = $this->scores["q_1_trial1"];
            $scoreCols["Total_A1b"] = $this->scores["q_1_trial2"];
            $scoreCols["Total_A2"] = 0;
            $j = 2;
            $numItems = 12;
            for ($i = 2; $i <= $numItems; $i++) {
                $scoreCols["Total_A2"] += $this->scores["q_{$j}_item{$i}"];
                $j++;
            }
            $scoreCols["Total_A"] = max($scoreCols["TotalA1a"], $scoreCols["TotalA1b"]) + $scoreCols["TotalA2"];

            // 2. Verbal Comprehension
            $scoreCols["Total_B"] = 0;
            $j = 13;
            $numItems = 36;
            for ($i = 1; $i <= $numItems; $i++) {
                $scoreCols["Total_B"] = $this->scores["q_{$j}_item{$i}"];
                $j++;
            }

            // 3. Picture Similarities
            $scoreCols["Total_C"] = 0;
            $j=37;
            $numItems=70;
            for ($i = 1; $i <= $numItems; $i++) {
                $scoreCols["Total_C"] = $this->scores["q_{$j}_item{$i}"];
                $j++;
            }

            // 4. Naming Vocabulary
            $scoreCols["Total_D"] = 0;
            $j=37;
            $numItems=70;
            for ($i = 1; $i <= $numItems; $i++) {
                $scoreCols["Total_D"] = $this->scores["q_{$j}_item{$i}"];
                $j++;
            }

            // 5. Recall of Objects - Immediate

            $scoreCols["Total_E1"] = $this->scores["q_70_trial1"];
            $scoreCols["Total_E2"] = $this->scores["q_70_trial2"];
            $scoreCols["Total_E3"] = 0;
            if ($scoreCols["Total_E1"] + $scoreCols["Total_E2"] == 40) {
                $scoreCols["Total_E3"] = 20;
            }
            else {
                $scoreCols["Total_E3"] = $this->scores["q_70_trial3"];
            }
            // if not spoiled
            $scoreCols["Total_E"] = ($scoreCols["Total_E1"] + $scoreCols["Total_E2"] + $scoreCols["Total_E3"]);
            // else add the two successful * 1.5 -- round up to whole number


            // 6. Pattern Construction
            $scoreCols["Total_F1"] = $this->scores["q_{$j}_item1"];
            $scoreCols["Total_F"] = 0;
//            $j=37;
//            $numItems=#;
//            for ($i = 1; $i <= $numItems; $i++) {
//                $scoreCols["Total_D"] = $this->scores["q_{$j}_item{$i}"];
//                $j++;


            // 7. Early Number Concepts


            // 8. Recall of Objects - Delayed


            // 9. Copying



        }
    }


    function _page1() {

        // Usual Age Range: 2 years 6 months to 3 years 5 months
        // Extended Age Range: 3 years 6 months to 4 years 11 months
        // All start at Item 1 unless Alternative Stopping Point is reached
        // Alternative Stopping Point - after 4 consecutive failures, STOP

        $this->form->addElement("header", null, "Block Building");

        // Item 1 - score better of two attempts
        $this->form->addElement("static", "null", "Item 1 - Trial 1");
        $this->form->addElement("select", "q_1_trial1", $this->indent . $this->indent . "Number of blocks used:", array("" => NULL, "2"=>"8 blocks","1"=>"4-7 blocks","0"=>"0-3 blocks","not_answered" => "Not Answered"));
        $this->XINRegisterRule("q_1_trial1", array("q_70_trial1_status{@}=={@}"), "Required.");
        $this->form->addElement("static", "null", "Item 1 - Trial 2");
        $this->form->addElement("select", "q_1_trial2done", $this->indent . $this->indent . "Was a second trial performed?", array("" => NULL, "yes" => "Yes", "no" => "No", "not_answered" => "Not Answered"));
        $this->XINRegisterRule("q_1_trial2done", array("q_70_trial2done_status{@}=={@}"), "Required.");
        $this->form->addElement("select", "q_1_trial2", $this->indent . $this->indent . "Number of blocks used:", array("" => NULL, "2"=>"8 blocks","1"=>"4-7 blocks","0"=>"0-3 blocks","not_answered" => "Not Answered"));
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

    }


    function _page2() {

        // Usual Age Range: 2 years 6 months to 5 years 11 months
        // Extended Age Range: 6 years 0 months to 6 years 11 months

        // Alternative Stopping Point: After 5 consecutive failures, if at least 3 passes STOP
        // <3 passes on all, go back to previous starting point


        $this->form->addElement("header", null, "Verbal Comprehension");

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
                    $this->form->addElement("static", null, "<br /><br />");
                    $this->form->addElement("header", null, "Items 7-18: Toys");
                    break;
                case 19:
                    $this->form->addElement("static", null, "<br /><br />");
                    $this->form->addElement("header", null, "Items 19-29: Inset Tray");
                    break;
                case 30:
                    $this->form->addElement("static", null, "<br /><br />");
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

    }


    function _page3() {

        // Usual Age Range: years months to years months
        // Out of Level: years months to years months

        $this->form->addElement("header", null, "Picture Similarities");

        $answerArray = array(""=>NULL, "correct"=>"Correct", "incorrect"=>"Incorrect", "not_answered"=>"Not Answered");
        $responseArray = array(""=>NULL, 1=>1, 2=>2, 3=>3, 4=>4, "not_answered"=>"Not Answered");

        $j=37;
        $numItems=12;
        for ($i = 1; $i <= $numItems; $i++) {
            $this->form->addElement("select", "q_{$j}_item{$i}", "Item $i", $answerArray);
            $this->form->addElement("select", "q_{$j}_item{$i}_response", $this->indent . $this->indent . "Child's Response:", $responseArray);
            $this->XINRegisterRule("q_{$j}_item{$i}_response", array("q_{$j}_item{$i}{@}=={@}correct"), "This is required if the child answered Item {$i} correctly.");
//            $this->XINRegisterRule("q_{$j}_item{$i}_response", array("q_{$j}_item{$i}{@}=={@}incorrect", "q_{$j}_item{$i}{@}=={@}not_answered"), "Any data entered will not be saved.");
            $j++;
        }
    }


    function _page4() {

        // Usual Age Range: 2 years 6 months to years months
        // Extended Age Range: 6 years 0 months to 7 years 11 months
        // Out of Level: 8 years 0 months to 8 years 11 months

        $this->form->addElement("header", null, "Naming Vocabulary");

        $answerArray = array(""=>NULL, "correct"=>"Correct", "incorrect"=>"Incorrect", "not_answered"=>"Not Answered");
        $yesNoNa = array(""=>NULL, "yes"=>"Yes", "no"=>"No", "not_answered"=>"Not Answered");

        $j=43;
        $numItems=27;
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


    }


    function _page5() {

        // Usual Age Range: years months to years months
        // Out of Level: years months to years months

        // Range must be 0 to 20 for each trial

        $this->form->addElement("header", null, "Recall of Objects - Immediate");

        $yesNoNa = array(""=>NULL, "yes"=>"Yes", "no"=>"No", "not_answered"=>"Not Answered");

        $this->form->addElement("static", "null", "Trial 1");
        $this->form->addElement("select", "q_70_trial1_success", $this->indent . $this->indent . "Was the trial successful?", $yesNoNa);
//        $this->XINRegisterRule("q_70_trial1_success_status", array("q_70_trial1_success{@}=={@}"), "Required");
        $this->addNumericElement("q_70_trial1", $this->indent . $this->indent . "Number of objects recalled correctly:");
        $this->XINRegisterRule("q_70_trial1", array("q_70_trial1_success{@}=={@}yes"), "Required.");

        $this->form->addElement("static", "null", "Trial 2");
        $this->form->addElement("select", "q_71_trial2_success", $this->indent . $this->indent . "Was the trial successful?", $yesNoNa);
//        $this->XINRegisterRule("q_71_trial2_success", array("q_71_trial2_success_status{@}=={@}"), "Required");
        $this->addNumericElement("q_71_trial2", $this->indent . $this->indent . "Number of objects recalled correctly:");
        $this->XINRegisterRule("q_71_trial2", array("q_71_trial2_success{@}=={@}yes"), "Required.");

        // if first two = 20, skip 30 and make equal to 30
        $this->form->addElement("static", "null", "Trial 3");
        $this->form->addElement("select", "q_72_trial3_success", $this->indent . $this->indent . "Was the trial successful?", $yesNoNa);
//        $this->XINRegisterRule("q_72_trial3_success", array("q_72_trial3_success_status{@}=={@}"), "Required.");
        $this->addNumericElement("q_72_trial3", $this->indent . $this->indent . "Number of objects recalled correctly:");
        $this->XINRegisterRule("q_72_trial3", array("q_72_trial3_success{@}=={@}yes"), "Required.");

        // require 2 trials
        // if spoiled or unscorable...

    }


    function _page6() {

        // Usual Age Range: 3 years 6 months to 17 years 11 months
        // Out of Level: 3 years 0 months to 3 years 5 months

        // DP
        //ASP

        $this->form->addElement("header", null, "Pattern Construction");


        $answer2Array = array(""=>NULL, "a"=>"(a) Passed first trial", "b"=>"(b) Passed second trial",
            "F"=>"Failed both trials", "not_answered"=>"Not Answered");

//        Second trial? radio
// Correctness, response time
        $answerArray = array(""=>NULL, "correct"=>"Correct", "incorrect"=>"Incorrect", "not_answered"=>"Not Answered");
        $successArray = array(""=>NULL, "p"=>"Pass", "f"=>"Fail", "not_answered"=>"Not Answered");

        $j=73;

        // 2 trials --> 3 for correct on 1st, 1 for 2nd, 0 otherwise
        // Sample A, 1, Sample B, 2, 4, Sample C, 8, 9, Sample D, 14, 15 if failed 1st trial
        $this->form->addElement("select", "q_{$j}_item1", "Item 1", $answer2Array);


        // Formatting of a/b?  (a) 1st trial (b) second trial
        // F, P --> 1 point

        // response time in minutes???

        $numItems=10;
        for ($i = 2; $i <= $numItems; $i++) {
            $this->form->addElement("static","null","Item $i");
            $this->addNumericElement("q_{$j}_item{$i}_response_time", $this->indent . $this->indent . "Response Time:");
            $this->form->addElement("select", "q_{$j}_item{$i}", $this->indent . $this->indent . "Trial Outcome:", $successArray);
//            $this->form->addElement("radio", "q_{$j}_item{$i}_q", $this->indent . "Q?");
//            $this->addLargeTextAreaElement("q_{$j}_item{$i}_text", $this->indent . "Response:");
            $j++;
        }

        // 2 - 23 --> two trials
        // response time, pass, fail P or F
        // If F in (a), allow (b) P or F

        // Pass/Fail
        // Alternative Scoring (2)
        // 1 point in second
        // 0 otherwise
        // one-trial --> 2 for pass, 0 for F

    }


    function _page7() {

        // Usual Age Range: 3 years 6 months to 5 years 11 months
        // Extended Age Range: 6 years 0 months to 6 years 5 months
        // Out of Level: 2 years 6 months to 3 years 5 months
        // Out of Level: 6 years 6 months to 7 years 11 months

        $this->form->addElement("header", null, "Early Number Concepts");

        $answerArray = array(""=>NULL, "correct"=>"Correct", "incorrect"=>"Incorrect", "not_answered"=>"Not Answered");

        $j=83;

        $this->form->addElement("select", "q_{$j}_item1", $this->indent . $this->indent . "Item 1", $answerArray);

        $numItems=12;
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
    }


    function _page8() {

        // Usual Age Range: 4 years 0 months to 17 years 11 months

        $this->form->addElement("header", null, "Recall of Objects - Delayed");

        // delayed recall trial max raw score: 20 points
        // only use if significantly different from immediate-recall score
        // convert immediate and delayed to T-scores
        // T scores differ by 14+ --> statistically significant

        $this->addNumericElement("q_90_trial1", $this->indent . $this->indent . "Number of objects recalled correctly:");

    }

    function _page9() {

        // Usual Age Range: 3 years 6 months to 5 years 11 months
        // Out of Level: 6 years 0 months to 7 years 11 months

        $this->form->addElement("header", null, "Copying");

        // DP
        // ASP

        // 2 stages
        // Elaborations (irrelevant lines/figures) = 0
        // Overworked/feathered lines = 1
        // Scribbled lines = 0
        // Appendix B

        // First stage: rough eval
        // P/F column --> P for apparent pass, P+ for apparent maximum score response, F for apparent failure
        // Second stage: final scoring

        // Total: out of 44 ?

        $answerArray1 = array(""=>NULL, "0"=>"0", "1"=>"1", "not_answered"=>"Not Answered");
        $answerArray2 = array(""=>NULL, "0"=>"0", "1"=>"1", "2"=>"2", "not_answered"=>"Not Answered");
        $answerArray3 = array(""=>NULL, "0"=>"0", "1"=>"1", "2"=>"2", "3"=>"3", "not_answered"=>"Not Answered");

        $j=91;
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
    }
}


?>