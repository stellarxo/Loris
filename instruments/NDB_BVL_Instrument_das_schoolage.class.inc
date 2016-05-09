<?php

require_once 'HTML/QuickForm.php';
require_once 'HTML/QuickForm/Renderer/Array.php';

class NDB_BVL_Instrument_das_schoolage extends NDB_BVL_Instrument
{

    // TO DO:

    // _score()

    // ASP & DPs
    // age constraints
    // second attempts??
    // paper form
    // forced numbers

    // END


    /*
    INSERT INTO test_names (Test_name, Full_name, Sub_group) VALUES ('das_schoolage', 'DAS (Differential Ability
    Scales) - School-Age Core', '1');

    INSERT INTO instrument_subtests (Test_name, Subtest_name, Description, Order_number) VALUES ('das_schoolage',
    'das_schoolage_page1', 'Recall of Designs', 1);
    INSERT INTO instrument_subtests (Test_name, Subtest_name, Description, Order_number) VALUES ('das_schoolage',
    'das_schoolage_page2', 'Word Definitions', 2);
    INSERT INTO instrument_subtests (Test_name, Subtest_name, Description, Order_number) VALUES ('das_schoolage',
    'das_schoolage_page3', 'Pattern Construction', 3);
    INSERT INTO instrument_subtests (Test_name, Subtest_name, Description, Order_number) VALUES ('das_schoolage',
    'das_schoolage_page4', 'Matrices', 4);
    INSERT INTO instrument_subtests (Test_name, Subtest_name, Description, Order_number) VALUES ('das_schoolage',
    'das_schoolage_page5', 'Verbal Similarities', 5);
    INSERT INTO instrument_subtests (Test_name, Subtest_name, Description, Order_number) VALUES ('das_schoolage',
    'das_schoolage_page6', 'Sequential and Quantitative Reasoning', 6);

    INSERT INTO test_battery (Test_name, AgeMinDays, AgeMaxDays, Active, Stage, SubprojectID, Visit_label, CenterID)
    VALUES ('das_schoolage', '1', '99999', 'Y', 'Visit', '1', 'V37Plus', NULL);
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
        $this->testName = "das_schoolage";
        $this->table = 'das_schoolage';
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
                'other_comments8'
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

        // 1. Recall of Designs
        // Usual Age Range: 6 years 0 months to 17 years 11 months
        // Extended Age Range: 5 years 0 months to 5 years 11 months


        // 2. Word Definitions
        // Usual Age Range: 6 years 0 months to 17 years 11 months
        // Out of Level: 5 years 0 months to 6 years 11 months


        // 3. Recall of Objects - Immediate
        // Usual Age Range: 4 years 0 months to 17 years 11 months


        // 4. Pattern Construction
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


        // 5. Matrices
        // Usual Age Range: 6 years 0 months to 17 years 11 months
        // Extended Age Range: 5 years 0 months to 5 years 11 months


        // 6. Recall of Objects - Delayed
        // Usual Age Range: 4 years 0 months to 17 years 11 months


        // 7. Similarities
        // Usual Age Range: 6 years 0 months to 17 years 11 months
        // Out of Level: 5 years 0 months to 5 years 11 months


        // 8. Sequential and Quantitative Reasoning
        // Usual Age Range: 6 years 0 months to 17 years 11 months
        // Out of Level: 5 years 0 months to 5 years 11 months

*/
        if(preg_match("/das_schoolage(_page[0-9]+)/",$this->page,$matches)){
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
        $this->form->addElement('header', 'instrument_title', "DAS - School-Age Core");

        // automatically adds examiner & date of administration
        $this->_addMetadataFields();

        $this->form->addElement('static', null, "<br />");
        $this->form->addElement('header', 'raw_scores', "Raw Scores");
        $this->form->addElement("static", null, "NOTE: Final scores still need to be calculated.");

        $this->form->addElement("static", null, "<br />");

        $scoreLabels = array(
            "Total_1"=>"Recall of Designs Score",
            "Total_2"=>"Word Definitions Score",
            "Total_3"=>"Recall of Objects - Immediate Score",
            "Total_4"=>"Pattern Construction Score",
            "Total_5"=>"Matrices",
            "Total_6"=>"Recall of Objects - Delayed Score",
            "Total_7"=>"Similarities",
            "Total_8"=>"Sequential and Quantitative Reasoning"
        );

        foreach ($scoreLabels as $field=>$label) {
            if(in_array($field,
                    array("Total_1", "Total_2", "Total_3", "Total_4", "Total_5",
                        "Total_6", "Total_7", "Total_8")) == TRUE) {
                $label = $this->indent . $this->indent . $label;
            }
            $this->form->addElement("static", $field, $label);
        }

        $this->form->addElement('static', null, "<br />");
        $this->form->addElement("textarea", "other_comments", "Comments:", array('cols'=>25, 'rows'=>4));
        $this->XINRegisterRule("other_comments", array("{other_comments}{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement('static', null, "<br />");


    }


//    function _score() {
/*
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

        // NEEDS TO CHANGE
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


            // 1. Recall of Designs
            // Usual Age Range: 6 years 0 months to 17 years 11 months
            // Extended Age Range: 5 years 0 months to 5 years 11 months
            if ($age > (17*12+11)) {
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


            // 2. Word Definitions
            // Usual Age Range: 6 years 0 months to 17 years 11 months
            // Out of Level: 5 years 0 months to 6 years 11 months
            if ($age > (7*12+11)) {
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


            // 3. Recall of Objects - Immediate
            // Usual Age Range: 4 years 0 months to 17 years 11 months
            if ($age < 4*12) {
                $scoreCols["Total_3"] = "Respondent too young to score";
            }
            else {
                $scoreCols["Total_3a"] = $this->scores["q_107_trial1"];
                $scoreCols["Total_3b"] = $this->scores["q_107_trial2"];
                $scoreCols["Total_3c"] = 0;
                if ($scoreCols["Total_3a"] + $scoreCols["Total_3b"] == 40) {
                    $scoreCols["Total_3c"] = 20;
                } else {
                    $scoreCols["Total_5c"] = $this->scores["q_107_trial3"];
                }
                // if not spoiled
                $scoreCols["Total_3"] = ($scoreCols["Total_51"] + $scoreCols["Total_52"] + $scoreCols["Total_53"]);
                // else add the two successful * 1.5 -- round up to whole number
            }


            // 4. Pattern Construction
            // Usual Age Range: 3 years 6 months to 17 years 11 months
            // Out of Level: 3 years 0 months to 3 years 5 months
            if ($age < (3*12)) {
                $scoreCols["Total_4"] = "Respondent too young to score";
            }
            else {
                $scoreCols["Total_4"] = 0;
                $j=108;
                $numItems=26;
                for ($i = 1; $i <= $numItems; $i++) {
                    $scoreCols["Total_4"] = $this->scores["q_{$j}_item{$i}"];
                    $j++;
                }
            }


            // 5. Matrices
            // Usual Age Range: 6 years 0 months to 17 years 11 months
            // Extended Age Range: 5 years 0 months to 5 years 11 months
            if ($age > (7*12+11)) {
                $scoreCols["Total_5"] = "Respondent too old to score";
            }
            else {
                $scoreCols["Total_5"] = 0;
                $j=134;
                $numItems=28;
                for ($i = 1; $i <= $numItems; $i++) {
                    $scoreCols["Total_5"] = $this->scores["q_{$j}_item{$i}"];
                    $j++;
                }
            }


            // 6. Recall of Objects - Delayed
            // Usual Age Range: 4 years 0 months to 17 years 11 months
            if ($age < (4*12)) {
                $scoreCols["Total_6"] = "Respondent too young to score";
            }
            else {
                $scoreCols["Total_6"] = $this->scores["q_162_trial1"];
            }

            // 7. Similarities
            // Usual Age Range: 6 years 0 months to 17 years 11 months
            // Out of Level: 5 years 0 months to 5 years 11 months
            if ($age < (17*12+11)) {
                $scoreCols["Total_7"] = "Respondent too young to score";
            }
            elseif ($age > (7*12+11)) {
                $scoreCols["Total_7"] = "Respondent too old to score";
            }
            else {
                $scoreCols["Total_7"] = 0;
                $j=163;
                $numItems=20;
                for ($i = 1; $i <= $numItems; $i++) {
                    $scoreCols["Total_7"] = $this->scores["q_{$j}_item{$i}"];
                    $j++;
                }
            }

            // 8. Sequential and Quantitative Reasoning
            // Usual Age Range: 6 years 0 months to 17 years 11 months
            // Out of Level: 5 years 0 months to 5 years 11 months
            if ($age < (6*12)) {
                $scoreCols["Total_8"] = "Respondent too young to score";
            }
            elseif ($age > (7*12+11)) {
                $scoreCols["Total_8"] = "Respondent too old to score";
            }
            else {
                $scoreCols["Total_8"] = 0;
                $j=163;
                $numItems=20;
                for ($i = 1; $i <= $numItems; $i++) {
                    $scoreCols["Total_8"] = $this->scores["q_{$j}_item{$i}"];
                    $j++;
                }
            }

        }
        else { // If older than 17 years 11 months
            for ($i = 1; $i <=9; $i++) {
                $scoreCols["Total_{$i}"] = "Respondent too old to score";
            }
        }
        */
//    }



    function _page1() {

        // 1. Recall of Designs
        // Usual Age Range: 6 years 0 months to 17 years 11 months
        // Extended Age Range: 5 years 0 months to 5 years 11 months

        $this->form->addElement("header", null, "Recall of Designs");
        $this->form->addElement('static', null, "<br />");

        // Item 1 - score better of two attempts
//        $this->form->addElement("static", null, "Item 1 - Trial 1");
//        $this->form->addElement("select", "q_1_trial1", $this->indent . $this->indent . "Number of blocks used:", array("" => NULL,2=>"8 blocks",1=>"4-7 blocks",0=>"0-3 blocks","not_answered" => "Not Answered"));
//        $this->XINRegisterRule("q_1_trial1", array("q_70_trial1_status{@}=={@}"), "Required.");
//        $this->form->addElement("static", null, "Item 1 - Trial 2");
//        $this->form->addElement("select", "q_1_trial2done", $this->indent . $this->indent . "Was a second trial performed?", array("" => NULL, "yes" => "Yes", "no" => "No", "not_answered" => "Not Answered"));
//        $this->XINRegisterRule("q_1_trial2done", array("q_70_trial2done_status{@}=={@}"), "Required.");
//        $this->form->addElement("select", "q_1_trial2", $this->indent . $this->indent . "Number of blocks used:", array("" => NULL,2=>"8 blocks",1=>"4-7 blocks",0=>"0-3 blocks","not_answered" => "Not Answered"));
//        $this->XINRegisterRule("q_1_trial2", array("q_1_trial2done{@}=={@}yes"), "This is required if a second trial was attempted.");
//
        $pfArray = array(""=>NULL, "p"=>"Pass", "f"=>"Fail", "not_answered"=>"Not Answered");
        $scoreArray = array(""=>NULL, 0=>0, 1=>1, 2=>2, "not_answered"=>"Not Answered");

        $group[] = &$this->form->createElement("static", "static_P/F_label", "", "P/F");
        $group[] = &$this->form->createElement("static", "static_score_label", "", "Score");
        $this->form->addGroup($group, null, "", $this->_GUIDelimiter, false);
        unset($group);

        $numItems=21;
        for ($i = 1; $i <= $numItems; $i++) {
            $group[]=&$this->form->createElement("select", "q_{$this->j}_item{$i}", null, $pfArray);
            $group[]=&$this->form->createElement("select", "q_{$this->j}_item{$i}_score", null, $scoreArray);

            $this->form->addGroup($group, "q_{$this->j}_{$i}_answer", "Item $i", $this->_GUIDelimiter, false);
            unset($group);

            $this->XINRegisterRule("q_{$this->j}_item{$i}_f", array("q_{$this->j}_item{$i}{@}!={@}'not_answered"), "This is
            required.");
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

        // Item Set Administered
        $itemSetArray = array_merge(array("" => null), range(1, $numItems));
        $group[]=&$this->form->createElement("select", "page_1_item_set_from", null, $itemSetArray);
        $group[]=&$this->form->createElement("select", "page_1_item_set_to", null, $itemSetArray);
        $this->form->addGroup($group, "page_1_item_set", "Item Set Administered", $this->_GUIDelimiter, false);
        unset($group);

        $this->form->addElement('static', null, "<br />");
        $this->form->addElement("textarea", "other_comments1", "Comments:", array('cols'=>25, 'rows'=>4));
        $this->XINRegisterRule("other_comments1", array("{other_comments1}{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement('static', null, "<br />");

    }


    function _page2() {

        // 2. Word Definitions
        // Usual Age Range: 6 years 0 months to 17 years 11 months
        // Out of Level: 5 years 0 months to 6 years 11 months
        // Alternative Stopping Point: After 5 consecutive failures, if at least 3 passes STOP
        // <3 passes on all, go back to previous starting point

        $this->form->addElement("header", null, "Word Definitions");
        $this->form->addElement('static', null, "<br />");

        // If you suspect that a child will have difficulty with the starting items for his or her age,
        // use the Starting and Decision Points for a younger age group.
        // Out-of-level testing for children of average or low ability only

        $item = array(1=>"Scissors", 2=> "Bed", 3=>"Tiny", 4=>"Travel",
            5=>"Crash", 6=>"Disappear", 7=>"Prize", 8=>"Discover", 9=>"Collect", 10=>"Hide",
            11=>"Assistant", 12=>"Mansion", 13=>"Error", 14=>"Curiosity", 15=>"Purpose", 16=>"Doubt", 17=>"Refund",
            18=>"Victorious",
            19=>"Transparent", 20=>"Counterfeit", 21=>"Tentacle", 22=>"Unique", 23=>"Consent", 24=>"Deceive",
            25=>"Adjacent", 26=>"Exert", 27=>"Pessimistic", 28=>"Nomadic", 29=>"Longevity", 30=>"Ostracize",
            31=>"Oligarchy", 32=>"Stoic", 33=>"Alacrity", 34=>"Recalcitrant", 35=>"Misanthropy");

        $group[] = &$this->form->createElement("static", "static_response_label", "", "Response");
        $group[] = &$this->form->createElement("static", "static_score_label", "", "Score");
        $this->form->addGroup($group, null, "", $this->_GUIDelimiter, false);
        unset($group);

        $numItems=count($item);
        for ($i = 1; $i <= $numItems; $i++) {
            $group[]=&$this->form->createElement("text", "q_{$this->j}_item{$i}_response", "");
            $group[]=&$this->form->createElement("select", "q_{$this->j}_item{$i}_score", "",
                $this->answerArray);
            $this->form->addGroup($group, "q_{$this->j}_item{$i}", "Item $i", $this->_GUIDelimiter, false);
            unset($group);
            $this->j++;
        }

        // Item Set Administered
        $itemSetArray = array_merge(array("" => null), range(1, $numItems));
        $group[]=&$this->form->createElement("select", "page_2_item_set_from", null, $itemSetArray);
        $group[]=&$this->form->createElement("select", "page_2_item_set_to", null, $itemSetArray);
        $this->form->addGroup($group, "page_2_item_set", "Item Set Administered", $this->_GUIDelimiter, false);
        unset($group);

        $this->form->addElement('static', null, "<br />");
        $this->form->addElement("textarea", "other_comments2", "Comments:", array('cols'=>25, 'rows'=>4));
        $this->XINRegisterRule("other_comments2", array("{other_comments2}{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement('static', null, "<br />");

    }



    function _page3() {

        // 3. Pattern Construction
        // Usual Age Range: 3 years 6 months to 17 years 11 months
        // Out of Level: 3 years 0 months to 3 years 5 months
        // DP
        // ASP

        $this->form->addElement("header", null, "Pattern Construction");
        $this->form->addElement('static', null, "<br />");

        $pfArray = array("" => NULL, "p" => "Pass", "f" => "Fail", "not_answered" => "Not Answered");
        $na = array("not_answered" => "Not Answered");
        $scoreArray = array("" => NULL, 0 => 0, 1 => 1, 2 => 2, "not_answered" => "Not Answered");

        $doubleTrialItems = array(1, 13, 14, 16, 20, 21, 26, 27);

        $numItemsSetA = 12;
        $numItemsSetB = 19;
        $numItemsSetC = 38;


        $this->form->addElement("header", null, "Set A");

        $group[] = $this->form->createElement("static", null, $this->indent);
        $group[] = &$this->form->createElement("static", "static_score_label", "", "Score");
        $this->form->addGroup($group, null, "", $this->_GUIDelimiter, false);
        unset($group);

        for ($i = 1; $i <= $numItemsSetA; $i++) {

            if (in_array($i, $doubleTrialItems)) {
                for ($k = 1; $k <= 2; $k++) {

                    $group[] =& $this->form->createElement("static", "q_{$this->j}_item{$i}_static_trial{$k}", null, "Trial $k");
                    $group[] =& $this->form->createElement("select", "q_{$this->j}_item{$i}_trial{$k}", null, $scoreArray);

                    if ($k == 1) {
                        $this->form->addGroup($group, "q_{$this->j}_{$i}_answer_trial{$k}", "Item $i", $this->_GUIDelimiter,
                            false);
                    } else {
                        $this->form->addGroup($group, "q_{$this->j}_{$i}_answer_trial{$k}", null, $this->_GUIDelimiter,
                            false);
                    }
                    unset($group);
                }
            }
                else {
                    $group[] = $this->form->createElement("static", null, $this->indent);
                    if ($i != 2) {
                        $group[] =& $this->form->createElement("select", "q_{$this->j}_item{$i}", null, $this->answerArray);
                    }
                    else {
                        $group[] =& $this->form->createElement("select", "q_{$this->j}_item{$i}", null, $scoreArray);
                    }

                    $this->form->addGroup($group, "q_{$this->j}_{$i}_answer", "Item $i", $this->_GUIDelimiter,
                        false);
                    unset($group);
                }
        }

        $this->form->addElement("header", null, "Set B");

        $group[] = $this->form->createElement("static", null, $this->indent);
        $group[] = &$this->form->createElement("static", "static_time_label", "", "Time");
        $group[] = &$this->form->createElement("static", "static_P/F_label", "", "P/F");
        $this->form->addGroup($group, null, "", $this->_GUIDelimiter, false);
        unset($group);

        $items_30 = array(13, 14, 20, 21, 22, 23);
        $items_45 = array(15, 16, 24, 25);
        $items_60 = array(17, 18, 19, 26);
        $items_90 = array(27, 28, 29, 30, 31, 32);
        $items_120 = array(33, 34, 35, 36, 37, 38);

        $item_time = array();

        for ($i = 0; $i < $numItemsSetC; $i++)
        {
            if ($i < 13) {
                $time= "";
            }
            if (in_array($i, $items_30)) {
                $time = 30;
            }
            if (in_array($i, $items_45)) {
                $time = 45;
            }
            if (in_array($i, $items_60)) {
                $time = 60;
            }
            if (in_array($i, $items_90)) {
                $time = 90;
            }
            if (in_array($i, $items_120)) {
                $time = 120;
            }
            array_push($item_time, $time);
        }

        for ($i = $numItemsSetA + 1; $i <= $numItemsSetB; $i++) {

            $options = array_merge(array("" => NULL), range(0,  $item_time[$i]), $na);

            if (in_array($i, $doubleTrialItems)) {
                for ($k = 1; $k <= 2; $k++) {

                    $group[] =& $this->form->createElement("static", "q_{$this->j}_item{$i}_static_trial{$k}", null, "Trial 
            $k");
                    $group[] =& $this->form->createElement("select", "q_{$this->j}_item{$i}_trial{$k}", null, $options);
                    $group[] =& $this->form->createElement("select", "q_{$this->j}_item{$i}_response_time2_trial{$k}", null,
                        $pfArray);

                    if ($k == 1) {
                        $this->form->addGroup($group, "{$i}_answer_trial{$k}", "Item $i", $this->_GUIDelimiter,
                            false);
                    } else {
                        $this->form->addGroup($group, "{$i}_answer_trial{$k}", null, $this->_GUIDelimiter,
                            false);
                    }
                    unset($group);
                }
            }
            else {
                $group[] = $this->form->createElement("static", null, $this->indent);
                $group[] =& $this->form->createElement("select", "q_{$this->j}_item{$i}", null, $options);
                $group[] =& $this->form->createElement("select", "q_{$this->j}_item{$i}_pf", null,
                    $pfArray);
                $this->form->addGroup($group, "q_{$this->j}_{$i}_answer", "Item $i", $this->_GUIDelimiter,
                    false);
                unset($group);
            }
        $this->j++;
        }

        $this->form->addElement("header", null, "Set C");

        $group[] = $this->form->createElement("static", null, $this->indent);
        $group[] = &$this->form->createElement("static", "static_time_label", "", "Time");
        $group[] = &$this->form->createElement("static", "static_P/F_label", "", "P/F");
        $this->form->addGroup($group, null, "", $this->_GUIDelimiter, false);
        unset($group);

        for ($i = $numItemsSetB + 1; $i <= $numItemsSetC; $i++) {

            $options = array_merge(array("" => NULL), range(0,  $item_time[$i]), $na);

            if (in_array($i, $doubleTrialItems)) {
                for ($k = 1; $k <= 2; $k++) {

                    $group[] =& $this->form->createElement("static", "q_{$this->j}_item{$i}_static_trial{$k}", null, "Trial 
            $k");
                    $group[] =& $this->form->createElement("select", "q_{$this->j}_item{$i}_trial{$k}", null, $options);
                    $group[] =& $this->form->createElement("select", "q_{$this->j}_item{$i}_response_time2_trial{$k}", null,
                        $pfArray);

                    if ($k == 1) {
                        $this->form->addGroup($group, "{$i}_answer_trial{$k}", "Item $i", $this->_GUIDelimiter,
                            false);
                    } else {
                        $this->form->addGroup($group, "{$i}_answer_trial{$k}", null, $this->_GUIDelimiter,
                            false);
                    }
                    unset($group);
                }
            }
            else {
                $group[] = $this->form->createElement("static", null, $this->indent);
                $group[] =& $this->form->createElement("select", "q_{$this->j}_item{$i}", null, $options);
                $group[] =& $this->form->createElement("select", "q_{$this->j}_item{$i}_pf", null,
                    $pfArray);
                $this->form->addGroup($group, "q_{$this->j}_{$i}_answer", "Item $i", $this->_GUIDelimiter,
                    false);
                unset($group);
            }
            $this->j++;
        }

        // Alternative (Unspeeded) Administration????

        // Item Set Administered
        $itemSetArray = array_merge(array("" => null), range(1, $numItemsSetC));
        $group[]=&$this->form->createElement("select", "page_3_item_set_from", null, $itemSetArray);
        $group[]=&$this->form->createElement("select", "page_3_item_set_to", null, $itemSetArray);
        $this->form->addGroup($group, "page_3_item_set", "Item Set Administered", $this->_GUIDelimiter, false);
        unset($group);

        $this->form->addElement('static', null, "<br />");
        $this->form->addElement("textarea", "other_comments3", "Comments:", array('cols'=>25, 'rows'=>4));
        $this->XINRegisterRule("other_comments3", array("{other_comments3}{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement('static', null, "<br />");

    }


    function _page4() {

        // 4. Matrices
        // Usual Age Range: 6 years 0 months to 17 years 11 months
        // Extended Age Range: 5 years 0 months to 5 years 11 months


        $this->form->addElement("header", null, "Matrices");
        $this->form->addElement('static', null, "<br />");

               $setAResponseArray = array(""=>NULL, 1=>1, 2=>2, 3=>3, 4=>4, "not_answered"=>"Not
               Answered");
               $setBResponseArray = array(""=>NULL, 1=>1, 2=>2, 3=>3, 4=>4, 5=>5, 6=>6, "not_answered"=>"Not Answered");

               // include score? or automatic??

               $numItemsSetA = 19;
               $numItemsSetB = 56;

        $this->form->addElement("header", null, "Set A");

        $group[] = &$this->form->createElement("static", "static_response_label", "", "Response");
        $group[] = &$this->form->createElement("static", "static_score_label", "", "Score");
        $this->form->addGroup($group, null, "", $this->_GUIDelimiter, false);
        unset($group);

        for ($i = 1; $i <= $numItemsSetA; $i++) {
                   $group[] =&$this->form->createElement("select", "q_{$this->j}_item{$i}_response", "",
                       $setAResponseArray);
                   $group[] =&$this->form->createElement("select", "q_{$this->j}_item{$i}_score", "",
                       $this->answerArray);
                   $this->form->addGroup($group, "q_{$this->j}_{$i}_answer", "Item $i", $this->_GUIDelimiter, false);
                   unset($group);

                   $this->j++;
               }

        $this->form->addElement("header", null, "Set B");

        $group[] = &$this->form->createElement("static", "static_response_label", "", "Response");
        $group[] = &$this->form->createElement("static", "static_score_label", "", "Score");
        $this->form->addGroup($group, null, "", $this->_GUIDelimiter, false);
        unset($group);


        for ($i = 20; $i <= $numItemsSetB; $i++) {
            $group[] =&$this->form->createElement("select", "q_{$this->j}_item{$i}_response", "",
                $setBResponseArray);
            $group[] =&$this->form->createElement("select", "q_{$this->j}_item{$i}_score", "",
                $this->answerArray);
            $this->form->addGroup($group, "q_{$this->j}_{$i}_answer", "Item $i", $this->_GUIDelimiter, false);
            unset($group);

                   $this->j++;
               }

        // Item Set Administered
        $itemSetArray = array_merge(array("" => null), range(1, $numItemsSetB));
        $group[]=&$this->form->createElement("select", "page_4_item_set_from", null, $itemSetArray);
        $group[]=&$this->form->createElement("select", "page_4_item_set_to", null, $itemSetArray);
        $this->form->addGroup($group, "page_4_item_set", "Item Set Administered", $this->_GUIDelimiter, false);
        unset($group);

               $this->form->addElement('static', null, "<br />");
               $this->form->addElement("textarea", "other_comments4", "Comments:", array('cols'=>25, 'rows'=>4));
               $this->XINRegisterRule("other_comments4", array("{other_comments4}{@}=={@}NEVER_REQUIRED"));
               $this->form->addElement('static', null, "<br />");
    }

    function _page5() {

        // 5. Verbal Similarities
        // Usual Age Range: 6 years 0 months to 17 years 11 months
        // Out of Level: 5 years 0 months to 5 years 11 months


        $this->form->addElement("header", null, "Verbal Similarities");
        $this->form->addElement('static', null, "<br />");

        $group[] = &$this->form->createElement("static", "static_response_label", "", "Response");
        $group[] = &$this->form->createElement("static", "static_score_label", "", "Score");
        $this->form->addGroup($group, null, "", $this->_GUIDelimiter, false);
        unset($group);

        $numItems=33;
        for ($i = 1; $i <= $numItems; $i++) {

            $group[]=&$this->form->createElement("text", "q_{$this->j}_item{$i}_response", null);
            $group[]=&$this->form->createElement("select", "q_{$this->j}_item{$i}_score", null, $this->answerArray);

            $this->form->addGroup($group, "q_{$this->j}_{$i}_answer", "Item $i", $this->_GUIDelimiter, false);
            unset($group);

//          $this->XINRegisterRule("q_{$this->j}_item{$i}_response", array("q_{$this->j}_item{$i}_other{@}=={@}yes"), "Required.");

            $this->j++;
        }

        // Item Set Administered
        $itemSetArray = array_merge(array("" => null), range(1, $numItems));
        $group[]=&$this->form->createElement("select", "page_5_item_set_from", null, $itemSetArray);
        $group[]=&$this->form->createElement("select", "page_5_item_set_to", null, $itemSetArray);
        $this->form->addGroup($group, "page_5_item_set", "Item Set Administered", $this->_GUIDelimiter, false);
        unset($group);

        // 2:6-4>5 Item 1-16
        // 4:6-7:11 Item 8-26
        // 8:0-8:11 Item 8-26

        // Decision Point: Stop unless <3 failures (con't), <3 passes (SP)
        // ASP: 5 consecutive failures, 3+ passes (Stop), <3 passes (SP)

        $this->form->addElement('static', null, "<br />");
        $this->form->addElement("textarea", "other_comments5", "Comments:", array('cols'=>25, 'rows'=>4));
        $this->XINRegisterRule("other_comments5", array("{other_comments5}{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement('static', null, "<br />");

    }



    function _page6() {

        // 6. Sequential and Quantitative Reasoning
        // Usual Age Range: 6 years 0 months to 17 years 11 months
        // Out of Level: 5 years 0 months to 5 years 11 months

        $this->form->addElement("header", null, "Sequential and Quantitative Reasoning");
        $this->form->addElement('static', null, "<br />");

        $this->form->addElement("header", null, "Set A");

        $group[] = &$this->form->createElement("static", "static_P/F_label", "", "Response");
        $group[] = &$this->form->createElement("static", "static_score_label", "", "Score");
        $this->form->addGroup($group, null, "", $this->_GUIDelimiter, false);
        unset($group);

        $numItemsSetA=23;
        for ($i = 1; $i <= $numItemsSetA; $i++) {
            $group[]=&$this->form->createElement("select", "q_{$this->j}_item{$i}_response", null,
                $this->responseArray);
            $group[]=&$this->form->createElement("select", "q_{$this->j}_item{$i}_score", null,
                $this->answerArray);
            $this->j++;

            $this->form->addGroup($group, "q_{$this->j}_{$i}_answer", "Item $i", $this->_GUIDelimiter, false);
            unset($group);
        }

        $this->form->addElement("header", null, "Set B");

        $group[] = &$this->form->createElement("static", "static_P/F_label", "", "Response");
        $group[] = &$this->form->createElement("static", "static_score_label", "", "Score");
        $this->form->addGroup($group, null, "", $this->_GUIDelimiter, false);
        unset($group);

        $numItemsSetB=50; // +1 for item1
        for ($i = $numItemsSetA + 1; $i <= $numItemsSetB; $i++) {


            $group[]=&$this->form->createElement("select", "q_{$this->j}_item{$i}_response", null,
                $this->responseArray);
            $group[]=&$this->form->createElement("select", "q_{$this->j}_item{$i}_score", null,
                $this->answerArray);

            $this->form->addGroup($group, "q_{$this->j}_{$i}_answer", "Item $i", $this->_GUIDelimiter, false);
            unset($group);

            $this->j++;
        }

        // Item Set Administered
        $itemSetArray = array_merge(array("" => null), range(1, $numItemsSetB));
        $group[]=&$this->form->createElement("select", "page_6_item_set_from", null, $itemSetArray);
        $group[]=&$this->form->createElement("select", "page_6_item_set_to", null, $itemSetArray);
        $this->form->addGroup($group, "page_6_item_set", "Item Set Administered", $this->_GUIDelimiter, false);
        unset($group);

        $this->form->addElement('static', null, "<br />");
        $this->form->addElement("textarea", "other_comments6", "Comments:", array('cols'=>25, 'rows'=>4));
        $this->XINRegisterRule("other_comments6", array("{other_comments6}{@}=={@}NEVER_REQUIRED"));
        $this->form->addElement('static', null, "<br />");

    }

}


?>