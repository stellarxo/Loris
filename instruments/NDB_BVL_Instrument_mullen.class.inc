<?php

require_once 'HTML/QuickForm.php';
require_once 'HTML/QuickForm/Renderer/Array.php';

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

    // This is not yet used. Need to add all the scored columns into it,
    // then fix the nullscores portion of the scoring function to use it.
    // See ticket #1260 on Redmine.
    // - Dave
    var $scoreLabels = array("gross_motor_raw", "visual_reception_raw", "fine_motor_raw", "receptive_language_raw", "expressive_language_raw", "gross_motor_t", "visual_reception_t", "fine_motor_t", "receptive_language_t", "expressive_language_t", "gross_motor_percentile", "visual_reception_percentile", "fine_motor_percentile", "receptive_language_percentile", "expressive_language_percentile", "gross_motor_description", "visual_reception_description", "fine_motor_description", "receptive_language_description", "expressive_language_description", "gross_motor_age_equivalent", "visual_reception_age_equivalent", "fine_motor_age_equivalent", "receptive_language_age_equivalent", "expressive_language_age_equivalent", "cognitive_t_score_sum", "composite_standard_score", "composite_percentile", "composite_description", 
    "gross_motor_calc_basal", "gross_motor_calc_ceiling",
    "visual_recept_calc_basal", "visual_recept_calc_ceiling",
    "fine_motor_calc_basal", "fine_motor_calc_ceiling",
    "receptive_lang_calc_basal", "receptive_lang_calc_ceiling",
    "expressive_lang_calc_basal", "expressive_lang_calc_ceiling"
    );

    var $yesNo = array(""=>null, "no"=>"No", "yes"=>"Yes", "not_answered"=>"Not Answered");

    var $ageEquivalents = array(
       'gross_motor' => array(
          0 => 1,
          1 => 1,
          2 => 1,
          3 => 1,
          4 => 2,
          5 => 3,
          6 => 3,
          7 => 4,
          8 => 5,
          9 => 6,
          10 => 7,
          11 => 8,
          12 => 9,
          13 => 10,
          14 => 11,
          15 => 12,
          16 => 13,
          17 => 14,
          18 => 14,
          19 => 15,
          20 => 16,
          21 => 17,
          22 => 18,
          23 => 20,
          24 => 21,
          25 => 22,
          26 => 23,
          27 => 25,
          28 => 27,
          29 => 28,
          30 => 30,
          31 => 32,
          32 => 33,
          33 => 33,
          34 => 33,
          35 => 33,
          36 => 33
          ),
       'visual_reception' => array(
           0 => 1,
           1 => 1,
           2 => 1,
           3 => 1,
           4 => 2,
           5 => 3,
           6 => 4,
           7 => 5,
           8 => 6,
           9 => 6,
           10 => 7,
           11 => 8,
           12 => 9,
           13 => 10,
           14 => 11,
           15 => 12,
           16 => 13,
           17 => 14,
           18 => 15,
           19 => 16,
           20 => 17,
           21 => 18,
           22 => 19,
           23 => 20,
           24 => 21,
           25 => 23,
           26 => 24,
           27 => 25,
           28 => 26,
           29 => 27,
           30 => 29,
           31 => 30,
           32 => 31,
           33 => 33,
           34 => 34,
           35 => 36,
           36 => 37,
           37 => 39,
           38 => 40,
           39 => 41,
           40 => 43,
           41 => 45,
           42 => 46,
           43 => 48,
           44 => 50,
           45 => 52,
           46 => 54,
           47 => 57,
           48 => 60,
           49 => 66,
           50 => 69
           ),
      'fine_motor' => array(
           0 => 1,
           1 => 1,
           2 => 1,
           3 => 1,
           4 => 2,
           5 => 3,
           6 => 4,
           7 => 5,
           8 => 6,
           9 => 7,
           10 => 8,
           11 => 9,
           12 => 10,
           13 => 11,
           14 => 12,
           15 => 13,
           16 => 14,
           17 => 15,
           18 => 16,
           19 => 17,
           20 => 18,
           21 => 20,
           22 => 21,
           23 => 22,
           24 => 23,
           25 => 24,
           26 => 26,
           27 => 27,
           28 => 28,
           29 => 30,
           30 => 31,
           31 => 33,
           32 => 34,
           33 => 36,
           34 => 37,
           35 => 39,
           36 => 40,
           37 => 42,
           38 => 44,
           39 => 45,
           40 => 47,
           41 => 49,
           42 => 51,
           43 => 53,
           44 => 55,
           45 => 57,
           46 => 59,
           47 => 62,
           48 => 65,
           49 => 68
           ),
       'receptive_language' => array(
             0 => 1,
             1 => 1,
             2 => 1,
             3 => 1,
             4 => 2,
             5 => 3,
             6 => 4,
             7 => 5,
             8 => 6,
             9 => 7,
             10 => 8,
             11 => 9,
             12 => 10,
             13 => 11,
             14 => 13,
             15 => 14,
             16 => 15,
             17 => 16,
             18 => 17,
             19 => 18,
             20 => 19,
             21 => 20,
             22 => 22,
             23 => 23,
             24 => 24,
             25 => 25,
             26 => 27,
             27 => 28,
             28 => 30,
             29 => 31,
             30 => 33,
             31 => 34,
             32 => 36,
             33 => 37,
             34 => 39,
             35 => 41,
             36 => 42,
             37 => 44,
             38 => 46,
             39 => 47,
             40 => 49,
             41 => 51,
             42 => 53,
             43 => 55,
             44 => 57,
             45 => 59,
             46 => 62,
             47 => 65,
             48 => 69
             ),
         'expressive_language' => array(
                 0 => 1,
                 1 => 1,
                 2 => 1,
                 3 => 2,
                 4 => 3,
                 5 => 4,
                 6 => 5,
                 7 => 6,
                 8 => 7,
                 9 => 8,
                 10 => 9,
                 11 => 10,
                 12 => 12,
                 13 => 13,
                 14 => 14,
                 15 => 15,
                 16 => 16,
                 17 => 17,
                 18 => 18,
                 19 => 20,
                 20 => 21,
                 21 => 22,
                 22 => 23,
                 23 => 24,
                 24 => 26,
                 25 => 27,
                 26 => 28,
                 27 => 29,
                 28 => 31,
                 29 => 32,
                 30 => 33,
                 31 => 35,
                 32 => 36,
                 33 => 37,
                 34 => 39,
                 35 => 40,
                 36 => 42,
                 37 => 43,
                 38 => 45,
                 39 => 46,
                 40 => 48,
                 41 => 50,
                 42 => 51,
                 43 => 53,
                 44 => 55,
                 45 => 58,
                 46 => 60,
                 47 => 63,
                 48 => 67,
                 49 => 70,
                 50 => 70
                 )
       );

    var $maxScores = array(
       1 => array(1=>1,
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
         18=>1,
         19=>1,
         20=>1,
         21=>1,
         22=>1,
         23=>1,
         24=>1,
         25=>1,
         26=>2,
         27=>1,
         28=>1,
         29=>1,
         30=>1,
         31=>1,
         32=>1,
         33=>1,
         34=>1,
         35=>1),
       2 => array(1=>2,
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
         17=>3,
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
         33=>2),
         3 => array(1=>1,
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
           30=>5),

           4=>array(1=>1,
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
             33=>2),

          5=>array(1=>1,
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
              28=>2)
      );

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

        // Get the subject age in months for scoring

        $db =& Database::singleton();

        $record = array();
        $query = "SELECT * FROM ".$this->table." WHERE CommentID='".$this->getCommentID()."'";
        $db->selectRow($query, $record);


        // Get the subject DoB for scoring
        if($this->getSessionID() != NULL) { //quickform_parser doesn't use any specific session
            $timepoint =& TimePoint::singleton($this->getSessionID());
            $dob = $timepoint->getEffectiveDateOfBirth();
        }
        if(!empty($dob) && !empty($record['Date_taken'])) {
            $age = Utility::calculateAge($dob, $record["Date_taken"]);
        } 
        if(isset($age)  && is_array($age)) {
          $age_months = $age['year'] * 12 + $age['mon'];
          $this->localDefaults = array_merge($this->localDefaults, array('age_months' => $age_months));
          $this->localDefaults = array_merge($this->localDefaults, $this->band_of_error($age_months));
          $this->localDefaults = array_merge($this->localDefaults, $this->composite_band_of_error($age_months));
        }

        // required fields for data entry completion status
        $this->_requiredElements = array('Examiner', "Date_taken");

        $this->_doubleDataEntryDiffIgnoreColumns = array_merge(array('CommentID', 'UserID', 'Testdate',
            'Window_Difference', 'Candidate_Age',
            'other_comments',
            'cognitive_t_score_sum',
            'composite_standard_score',
            'composite_percentile',
            'composite_description'),
            $this->scoreLabels
        );

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
        if(preg_match("/mullen(_page[0-9]+)/",$this->page,$matches)){
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
        $this->form->addElement('header', 'instrument_title', "Mullen Scales of Early Learning");

        // automatically adds examiner & date of administration
        $this->_addMetadataFields();

        $this->form->addElement("textarea", "other_comments", "Comments about the administration of this instrument:", array('cols'=>25, 'rows'=>4));
        $this->XINRegisterRule("other_comments", array("{other_comments}{@}=={@}NEVER_REQUIRED"));

//        $this->form->addElement("header", null, "Please answer only non-identifying questions");
//        $this->form->addElement("static", null, "Child's Name");
//        $this->form->addElement("static", null, "ID");
//        $this->form->addElement("static", null, "Phone Number");
//        $this->form->addElement("static", null, "Nickname");
//        $this->form->addElement("static", null, "Boy / Girl");
//        $this->form->addElement("static", null, "Address");
//
//        $this->addTextElement("primary_language", "Child's Primary Language");
//
//        $this->form->addElement("static", null, "Mother's Name");
//        $this->form->addElement("static", null, "Father's Name");
//        $this->form->addElement("static", null, "Examiner");
//        $this->form->addElement("static", null, "School");
//
//        $this->addTextElement("weeks_gestation", "No. Weeks Gestation (G.A.)");
//        $this->addTextElement("birth_weight", "Birth Weight");
//
//        $this->addTextElement("apgar_1_min", "Apgars 1 min.");
//        $this->addTextElement("apgar_5_min", "Apgars 5 min.");
//        $this->form->addElement("static", null, "Hospital");
//
//        $this->form->addElement("select", "uncorrected_vision", "Does the child have a known uncorrected vision problem?", $this->yesNo);
//        $this->form->addElement("select", "uncorrected_hearing", "Does the child have a known uncorrected hearing problem?", $this->yesNo);
//
//        $this->addTextElement("characteristic_affecting", "Personal or physical characteristics that may affect the child's test results");
//
//        $this->form->addElement("select", "medication", "Is the child on any medication?", $this->yesNo);
//        $this->addTextElement("medication_specify", $this->indent . "If yes, please specify", array("medication{@}=={@}yes"), "This field is required if the child is on medication");
//
//        $this->form->addElement("static", null, "Referred by");
//        $this->form->addElement("static", null, "Reason for Referral");
//        $this->addTextAreaElement("info_comments", "Additional Information/Comments");
//
//        $this->form->addElement("static", null, "Testing Date");
//        $this->form->addElement("static", null, "Birth Date");
//        $this->form->addElement("static", null, "Chronological Age");
//        $this->form->addElement("static", null, "Adjusted Age");

         $this->form->addElement("header", null, "Composite Scores");
          $this->form->addElement("static", 'cognitive_t_score_sum', "Cognitive T Score Sum");
          $this->form->addElement("static", 'composite_standard_score', "Standard Score");
          $this->form->addElement("static", 'composite_percentile', "Percentile");
          $this->form->addElement("static", 'composite_description', "Description");
          $this->form->addElement("static", 'composite_error_90', "90% Band of Error (+/-)");
          $this->form->addElement("static", 'composite_error_95', "95% Band of Error (+/-)");

         $this->form->addElement("header", null, "Gross Motor Scores");
          if((isset($this->localDefaults['age_months'])
              && $this->localDefaults['age_months'] <= 33) || empty($this->CommentID)
          ) {
             $this->form->addElement("static", 'gross_motor_raw', "Raw Score");
             $this->form->addElement("static", 'gross_motor_t', "T Score");
             $this->form->addElement("static", 'gross_motor_percentile', "Percentile");
             $this->form->addElement("static", 'gross_motor_description', "Description");
             $this->form->addElement("static", 'gross_motor_age_equivalent', "Age Equivalent");
             $this->form->addElement("static", 'gross_motor_error_90', "90% Band of Error (+/-)");
             $this->form->addElement("static", 'gross_motor_error_95', "95% Band of Error (+/-)");
          }
          else{
             $this->form->addElement("static", 'gross_motor_raw', "Raw Score");
             $this->form->addElement("static", 'gross_motor_age_equivalent', "Age Equivalent");
             $this->form->addElement("static", null, '<font color="Red">T Score N/A for children over 33 months.</font>');
          }

         $this->form->addElement("header", null, "Visual Reception Scores");
        $this->form->addElement("static", 'visual_reception_raw', "Raw Score");
        $this->form->addElement("static", 'visual_reception_t', "T Score");
        $this->form->addElement("static", 'visual_reception_percentile', "Percentile");
        $this->form->addElement("static", 'visual_reception_description', "Description");
        $this->form->addElement("static", 'visual_reception_age_equivalent', "Age Equivalent");
        $this->form->addElement("static", 'visual_reception_error_90', "90% Band of Error (+/-)");
         $this->form->addElement("static", 'visual_reception_error_95', "95% Band of Error (+/-)");

         $this->form->addElement("header", null, "Fine Motor Scores");
          $this->form->addElement("static", 'fine_motor_raw', "Raw Score");
          $this->form->addElement("static", 'fine_motor_t', "T Score");
          $this->form->addElement("static", 'fine_motor_percentile', "Percentile");
          $this->form->addElement("static", 'fine_motor_description', "Description");
          $this->form->addElement("static", 'fine_motor_age_equivalent', "Age Equivalent");
          $this->form->addElement("static", 'fine_motor_error_90', "90% Band of Error (+/-)");
          $this->form->addElement("static", 'fine_motor_error_95', "95% Band of Error (+/-)");

          $this->form->addElement("header", null, "Receptive Language Scores");
          $this->form->addElement("static", 'receptive_language_raw', "Raw Score");
          $this->form->addElement("static", 'receptive_language_t', "T Score");
          $this->form->addElement("static", 'receptive_language_percentile', "Percentile");
          $this->form->addElement("static", 'receptive_language_description', "Description");
          $this->form->addElement("static", 'receptive_language_age_equivalent', "Age Equivalent");
          $this->form->addElement("static", 'receptive_language_error_90', "90% Band of Error (+/-)");
           $this->form->addElement("static", 'receptive_language_error_95', "95% Band of Error (+/-)");

          $this->form->addElement("header", null, "Expressive Language Scores");
          $this->form->addElement("static", 'expressive_language_raw', "Raw Score");
          $this->form->addElement("static", 'expressive_language_t', "T Score");
          $this->form->addElement("static", 'expressive_language_percentile', "Percentile");
          $this->form->addElement("static", 'expressive_language_description', "Description");
          $this->form->addElement("static", 'expressive_language_age_equivalent', "Age Equivalent");
          $this->form->addElement("static", 'expressive_language_error_90', "90% Band of Error (+/-)");
          $this->form->addElement("static", 'expressive_language_error_95', "95% Band of Error (+/-)");
    }

    function _page1(){

        $this->form->addElement("header", null, "Scale 1. Gross Motor");
        if($this->localDefaults['age_months'] > 33){
            $this->form->addElement("header",null , '<font color="Red">T Score N/A for children over 33 months.</font>');
         }
        $questionArray = array(0=>null,
        "1. Enjoys being held/realigns (Up)",
        "2. Rotates head (P)",
        "3. Moves arms, legs vigorously (S)",
        "4. Held upright, holds head steady (Up)",

        "5. Supports on forearms (P)",
        "6. Sits supported, head steady (SSit)",
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
        "24. Walks 4 to 5 steps, one foot on line",
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

        $this->form->addElement("header", null, "Note: Basal level refers to the FIRST of the three questions used to determine the basal level.<br>" .
                                                "Note: Ceiling level refers to the LAST of the three questions used to determine the ceiling level.");

        $this->form->addElement("select", "gross_motor_basal", $this->indent . "Select basal level:", array(null => null) +  array_combine(range(1,35), range(1,35)));
        $this->form->addElement("select", "gross_motor_ceiling", $this->indent . "Select ceiling level:", array(null => null) + array_combine(range(35,1), range(35,1)));
        if($this->localDefaults['age_months'] <= 33){
              $this->form->addRule("gross_motor_basal", 'Basal level must be set', 'required');
              $this->form->addRule("gross_motor_ceiling", 'Ceiling level must be set', 'required');
        }
        else{
           $this->XINRegisterRule("gross_motor_basal", array("{gross_motor_basal}{@}=={@}NEVER_REQUIRED"));
           $this->XINRegisterRule("gross_motor_ceiling", array("{gross_motor_ceiling}{@}=={@}NEVER_REQUIRED"));
        }
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

        $this->form->addElement("header", null, "Gross Motor Scores");
        if (isset($_REQUEST['commentID'])) {

        if($this->localDefaults['age_months'] <= 33){
            $this->form->addElement("static", 'gross_motor_raw', "Raw Score");
            $this->form->addElement("static", 'gross_motor_t', "T Score");
            $this->form->addElement("static", 'gross_motor_percentile', "Percentile");
            $this->form->addElement("static", 'gross_motor_description', "Description");
            $this->form->addElement("static", 'gross_motor_age_equivalent', "Age Equivalent");
            $this->form->addElement("static", 'gross_motor_error_90', "90% Band of Error (+/-)");
            $this->form->addElement("static", 'gross_motor_error_95', "95% Band of Error (+/-)");
         }
         else{
            $this->form->addElement("static", 'gross_motor_raw', "Raw Score");
            $this->form->addElement("static", 'gross_motor_age_equivalent', "Age Equivalent");
            $this->form->addElement("static", null, '<font color="Red">T Score N/A for children over 33 months.</font>');
         }
        }
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

        "16. Discriminates forms on formboard",
        "17A. Matches objects with naming (A/V) (19 months or younger)<br><strong>Or</strong> 17B. Matches objects without naming (20 months or older)",


        "18. Nests nesting cups",
        "19. Sorts spoons and blocks by category",
        "20. Matches by shape",
        "21. Matches pictures",
        "22. Matches by size, color",
        "23. Memory for one picture",
        "24. Spatial details I",

        "25. Spatial details II",
        "26. Memory for objects",
        "27. Discriminates spatial position",
        "28. Matches letters",
        "29. Discriminates left/right",
        "30. Matches letters, words",
        "31. Memory for three pictures",
        "32. Spatial details III",
        "33. Memory for form");
        unset($questionArray[0]); //get rid of the zero in the 0 based array

        //Potential point value of each question
        $maxPoints = $this->maxScores[2];

        $sectionDividers = array(1=>"1-4 mo.",
        3=>"5-8 mo.",
        7=>"9-12 mo.",
        9=>"10-20 mo.",
        16=>"21-32 mo.",
        19=>"33-44 mo.",
        25=>"45+ mo.");


      $this->form->addElement("header", null, "Note: Basal level refers to the FIRST of the three questions used to determine the basal level.<br>" .
                                              "Note: Ceiling level refers to the LAST of the three questions used to determine the ceiling level.");
        $this->form->addElement("select", "visual_recept_basal", $this->indent . "Select basal level:", array(null => null) + array_combine(range(1,33), range(1,33)));
        $this->form->addElement("select", "visual_recept_ceiling", $this->indent . "Select ceiling level:", array(null => null) + array_combine(range(33,1), range(33,1)));
       $this->form->addRule("visual_recept_basal", 'Basal level must be set', 'required');
       $this->form->addRule("visual_recept_ceiling", 'Ceiling level must be set', 'required');

        foreach($questionArray as $field=>$label) {
            //check if this is the beginning to a section...
            if(key_exists($field, $sectionDividers)) {
                $this->form->addElement("header", null, $sectionDividers[$field]);
            }
            //Output the question...
            $this->_addQuestion("visual_recept_" . $field, $label, $maxPoints[$field]);
        }

        $this->form->addElement("header", null, "Visual Reception Scores");
        if (isset($_REQUEST['commentID'])) {

        $this->form->addElement("static", 'visual_reception_raw', "Raw Score");
        $this->form->addElement("static", 'visual_reception_t', "T Score");
        $this->form->addElement("static", 'visual_reception_percentile', "Percentile");
        $this->form->addElement("static", 'visual_reception_description', "Description");
        $this->form->addElement("static", 'visual_reception_age_equivalent', "Age Equivalent");
         $this->form->addElement("static", 'visual_reception_error_90', "90% Band of Error (+/-)");
         $this->form->addElement("static", 'visual_reception_error_95', "95% Band of Error (+/-)");
        }
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
        $maxPoints = $this->maxScores[3];

        $sectionDividers = array(1=>"1-4 mo.",
        4=>"5-8 mo.",
        7=>"9-12 mo.",
        11=>"13-17 mo.",
        13=>"18-29 mo.",
        16=>"30-44 mo.",
        21=>"45+ mo.");

      $this->form->addElement("header", null, "Note: Basal level refers to the FIRST of the three questions used to determine the basal level.<br>" .
                                              "Note: Ceiling level refers to the LAST of the three questions used to determine the ceiling level.");
        $this->form->addElement("select", "fine_motor_basal", $this->indent . "Select basal level:", array(null => null) + array_combine(range(1,30), range(1,30)));
        $this->form->addElement("select", "fine_motor_ceiling", $this->indent . "Select ceiling level:", array(null => null) + array_combine(range(30,1), range(30,1)));
        $this->form->addRule("fine_motor_basal", 'Basal level must be set', 'required');
        $this->form->addRule("fine_motor_ceiling", 'Ceiling level must be set', 'required');

        foreach($questionArray as $field=>$label) {
            //check if this is the beginning to a section...
            if(key_exists($field, $sectionDividers)) {
                $this->form->addElement("header", null, $sectionDividers[$field]);
            }
            //Output the question...
            $this->_addQuestion("fine_motor_" . $field, $label, $maxPoints[$field]);

        }

        $this->form->addElement("header", null, "Fine Motor Scores");
       if (isset($_REQUEST['commentID'])) {

       $this->form->addElement("static", 'fine_motor_raw', "Raw Score");
       $this->form->addElement("static", 'fine_motor_t', "T Score");
       $this->form->addElement("static", 'fine_motor_percentile', "Percentile");
       $this->form->addElement("static", 'fine_motor_description', "Description");
       $this->form->addElement("static", 'fine_motor_age_equivalent', "Age Equivalent");
       $this->form->addElement("static", 'fine_motor_error_90', "90% Band of Error (+/-)");
        $this->form->addElement("static", 'fine_motor_error_95', "95% Band of Error (+/-)");
       }
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
        $maxPoints = $this->maxScores[4];

        $sectionDividers = array(1=>"1-4 mo.",
        4=>"5-10 mo.",
        8=>"11-14 mo.",
        12=>"15-22 mo.",
        18=>"23-32 mo.",
        22=>"33-44 mo.",
        25=>"45+ mo.");

      $this->form->addElement("header", null, "Note: Basal level refers to the FIRST of the three questions used to determine the basal level.<br>" .
                                              "Note: Ceiling level refers to the LAST of the three questions used to determine the ceiling level.");
        $this->form->addElement("select", "receptive_lang_basal", $this->indent . "Select basal level:", array(null => null) + array_combine(range(1,33), range(1,33)));
        $this->form->addElement("select", "receptive_lang_ceiling", $this->indent . "Select ceiling level:", array(null => null) + array_combine(range(33,1), range(33,1)));
        $this->form->addRule("receptive_lang_basal", 'Basal level must be set', 'required');
        $this->form->addRule("receptive_lang_ceiling", 'Ceiling level must be set', 'required');

        foreach($questionArray as $field=>$label) {
            //check if this is the beginning to a section...
            if(key_exists($field, $sectionDividers)) {
                $this->form->addElement("header", null, $sectionDividers[$field]);
            }
            //Output the question...
            $this->_addQuestion("receptive_lang_" . $field, $label, $maxPoints[$field]);
        }

         $this->form->addElement("header", null, "Receptive Language Scores");
         if (isset($_REQUEST['commentID'])) {

         $this->form->addElement("static", 'receptive_language_raw', "Raw Score");
         $this->form->addElement("static", 'receptive_language_t', "T Score");
         $this->form->addElement("static", 'receptive_language_percentile', "Percentile");
         $this->form->addElement("static", 'receptive_language_description', "Description");
         $this->form->addElement("static", 'receptive_language_age_equivalent', "Age Equivalent");
         $this->form->addElement("static", 'receptive_language_error_90', "90% Band of Error (+/-)");
         $this->form->addElement("static", 'receptive_language_error_95', "95% Band of Error (+/-)");
         }
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
        $maxPoints = $this->maxScores[5];

        $sectionDividers = array(1=>"1-4 mo.",
        4=>"5-8 mo.",
        7=>"9-14 mo.",
        11=>"15-23 mo.",
        15=>"24-32 mo.",
        19=>"33-44 mo.",
        22=>"45+ mo.");

        $this->form->addElement("header", null, "Note: Basal level refers to the FIRST of the three questions used to determine the basal level.<br>" .
                                                "Note: Ceiling level refers to the LAST of the three questions used to determine the ceiling level.");
        $this->form->addElement("select", "expressive_lang_basal", $this->indent . "Select basal level:", array(null => null) + array_combine(range(1,28), range(1,28)));
        $this->form->addElement("select", "expressive_lang_ceiling", $this->indent . "Select ceiling level:", array(null => null) + array_combine(range(28,1), range(28,1)));
        $this->form->addRule("expressive_lang_basal", 'Basal level must be set', 'required');
        $this->form->addRule("expressive_lang_ceiling", 'Ceiling level must be set', 'required');

        foreach($questionArray as $field=>$label) {
            //check if this is the beginning to a section...
            if(key_exists($field, $sectionDividers)) {
                $this->form->addElement("header", null, $sectionDividers[$field]);
            }
            //Output the question...
            $this->_addQuestion("expressive_lang_" . $field, $label, $maxPoints[$field]);

        }

        $this->form->addElement("header", null, "Expressive Language Scores");
        if (isset($_REQUEST['commentID'])) {

        $this->form->addElement("static", 'expressive_language_raw', "Raw Score");
        $this->form->addElement("static", 'expressive_language_t', "T Score");
        $this->form->addElement("static", 'expressive_language_percentile', "Percentile");
        $this->form->addElement("static", 'expressive_language_description', "Description");
        $this->form->addElement("static", 'expressive_language_age_equivalent', "Age Equivalent");
        $this->form->addElement("static", 'expressive_language_error_90', "90% Band of Error (+/-)");
        $this->form->addElement("static", 'expressive_language_error_95', "95% Band of Error (+/-)");
        }
     }

    //Add an individual question, for now, nothing is required.
    function _addQuestion($field, $label, $maxPoints) {

        $answerOptions = array(""=>null) + range(0, $maxPoints) + array("not_answered"=>"Not Answered");
        $this->form->addElement("select", $field, $this->indent . $label, $answerOptions);
        $this->XINRegisterRule($field, array("{$field}{@}=={@}NEVER_REQUIRED"));
    }


    function score() {
         $this->_nullScores($this->scoreLabels);
         if($this->_determineDataEntryCompletionStatus() == "Incomplete") {
            return;
         }

         // Get the item scores
         $score_record=array();

         $db =& Database::singleton();


   		$query = "SELECT * FROM ".$this->table." WHERE CommentID='".$this->getCommentID()."'";
         $db->selectRow($query, $score_record);


         // Get the subject age in months for scoring
         $timepoint =& TimePoint::singleton($this->getSessionID());
         $dob = $timepoint->getEffectiveDateOfBirth();
         $age = Utility::calculateAge($dob, $score_record["Date_taken"]);
         $age_months = $age['year'] * 12 + $age['mon'];


         $calculatedScores = array();

         $calculatedScores['gross_motor_raw'] = $this->get_raw_score($score_record, $age_months, 1, 35);
         $calculatedScores['visual_reception_raw'] = $this->get_raw_score($score_record, $age_months, 2, 33);
         $calculatedScores['fine_motor_raw'] = $this->get_raw_score($score_record, $age_months, 3, 30);
         $calculatedScores['receptive_language_raw'] = $this->get_raw_score($score_record, $age_months, 4, 33);
         $calculatedScores['expressive_language_raw'] = $this->get_raw_score($score_record, $age_months, 5, 28);

         $scale_list = array('gross_motor', 'visual_reception', 'fine_motor', 'receptive_language', 'expressive_language');

         $all_complete = true;

         foreach($scale_list as $scale_name){

            // Make sure there's a score of some kind.
            if($calculatedScores[$scale_name . '_raw'] ||
                // Make sure the value isn't 0, which evaluates to false, because if it is we still need to calculate t-scores
                $calculatedScores[$scale_name . '_raw'] === 0 || $calculatedScores[$scale_name . '_raw'] === '0' ) {
                $query = "SELECT * FROM mullen_lookup WHERE age_months=:CandAge AND raw_score=:ScaleScore";
                $record = $db->pselectRow($query, array('CandAge' => $age_months, 'ScaleScore' => $calculatedScores[$scale_name . '_raw']));

            // If the score is above or below the highest score in the table,
            // get the closest score
            
            if (count($record) == 0) {
                $maxmin = $db->pselectRow("SELECT MAX(raw_score) as max, MIN(raw_score) as min FROM mullen_lookup WHERE age_months=:CandAge", array('CandAge' => $age_months));
                if($calculatedScores[$scale_name . '_raw'] < $maxmin['min']) {
                    $minimax = $maxmin['min'];
                } elseif($calculatedScores[$scale_name . '_raw'] > $maxmin['max']) {
                    $minimax = $maxmin['max'];
                } else {
                    $minimax = -1;
                }
                $query = "SELECT * FROM mullen_lookup WHERE age_months=:CandAge AND raw_score=:MiniMax";
         	    $record = $db->pselectRow($query, array('CandAge' => $age_months, 'MiniMax' => $minimax));
                

            }
            
         	$calculatedScores[$scale_name . '_t'] = ($record[$scale_name . '_t']);
         	$percentile = $this->percentile($calculatedScores[$scale_name . '_t']);
         	$calculatedScores[$scale_name . '_percentile'] = $percentile['percentile'];
         	$calculatedScores[$scale_name . '_description'] = $percentile['description'];
         	$calculatedScores[$scale_name . '_age_equivalent'] = $this->ageEquivalents[$scale_name][$calculatedScores[$scale_name . '_raw']];
            } else {
                $record = array();
                // Gross motor score doesn't affect the composite score, so don't bother setting "all_complete" to false
                // if it's the gross motor that's missing
                if($scale_name !== 'gross_motor') {
                    $all_complete = false;
                }
            }
            /*$calculatedScores[$scale_name . '_calc_ceiling'] =*/ $this->getScaleCeiling($scale_name, $score_record, $calculatedScores);
            /* $calculatedScores[$scale_name . '_calc_basal'] =*/ $this->getScaleBasal($scale_name, $score_record, $calculatedScores);
         }

         if($all_complete){
            $calculatedScores['cognitive_t_score_sum'] = $calculatedScores['visual_reception_t'] + $calculatedScores['fine_motor_t'] + $calculatedScores['receptive_language_t'] + $calculatedScores['expressive_language_t'];

            $query = "SELECT * FROM mullen_composite_lookup WHERE cognitive_t_sum=".$calculatedScores['cognitive_t_score_sum'];
            $record = array();
         	$db->selectRow($query, $record);


            $calculatedScores["composite_standard_score"] = $record['composite_standard_score'];
            $calculatedScores["composite_percentile"] = $record['percentile'];
            $calculatedScores["composite_description"] = $this->composite_descriptor($calculatedScores['cognitive_t_score_sum']);
         }


         // save the resultant total
         $result = $db->update($this->table, $calculatedScores, array('CommentID'=>$this->getCommentID()));

     }

     function get_raw_score($score_record, $age, $scale, $num_questions){
        $scale_name_list = array(nil, 'gross_motor', 'visual_recept', 'fine_motor', 'receptive_lang', 'expressive_lang');
        $scale_name_english = array(nil, 'Gross Motor', 'Visual Reception', 'Fine Motor', 'Receptive Language', 'Expressive Language');

        $scale_name = $scale_name_list[$scale];
        $eng_scale_name = $scale_name_english[$scale];

        if(empty($score_record[$scale_name . '_' . "basal"]) || empty($score_record[$scale_name . '_' . "ceiling"])){
           return null;
        }

        $start_question = $score_record[$scale_name . '_' . "basal"];
        $end_question = $score_record[$scale_name . '_' . "ceiling"];

        $raw_score = 0;
        for ($question=1; $question <= $num_questions; $question++) {
           if($question < $start_question){
              $raw_score += $this->maxScores[$scale][$question];
           }
           else if($question <= $end_question){
              if($score_record[$scale_name . '_' . $question] == 'not_answered'){
                 echo('<center><strong><font color="Red"> "Not Answered" response appears incorrect for question ' . $question . ' on ' . $eng_scale_name . ' scale</font></strong></center>');
              }
              if($score_record[$scale_name . '_' . $question] == null){
                 echo('<center><strong><font color="Red"> Missing response appears incorrect for question ' . $question . ' on ' . $eng_scale_name . ' scale</font></strong></center>');
              }
              $raw_score += $score_record[$scale_name . '_' . $question];
           }
           else{
              break;
           }
        }

        return $raw_score;
     }

     function getScaleCeiling($scalename, $responses, &$score) {
         $min = 1;
         $q_prefix = $scalename;
         $scale_list = array('gross_motor', 'visual_reception', 'fine_motor', 'receptive_language', 'expressive_language');
         switch($scalename) {
         case 'gross_motor':
             $max = 35;
             break;
         case 'visual_reception':
             $q_prefix = 'visual_recept';
             $max = 33;
             break;
         case 'fine_motor':
             $max = 30;
             break;
         case 'receptive_language':
             $q_prefix = 'receptive_lang';
             $max = 33;
             break;
         case 'expressive_language':
             $q_prefix = 'expressive_lang';
             $max = 28;
             break;
         }
         for($i = $min; $i <= $max; $i += 1) {
             if($responses[$q_prefix . '_' . $i] == '0' &&
                $responses[$q_prefix . '_' . ($i+1)] == '0' &&
                $responses[$q_prefix . '_' . ($i+2)] == '0') {
                    $score[$q_prefix . '_calc_ceiling'] = ($i+2);
                    return $i;
                }
         }
         if($responses[$q_prefix . '_' . $max] != '' || $responses[$q_prefix . '_' . $max] === '0') {
             //print "$scalename $q_prefix $max: " . $responses[$q_prefix . '_' . $max] . "\n";
             $score[$q_prefix . '_calc_ceiling'] = $max;
             return $max;
         }
         return 'No valid ceiling';
     }

     function getScaleBasal($scalename, $responses, &$score) {
         $min = 1;
         $q_prefix = $scalename;
         switch($scalename) {
         case 'gross_motor':
             $max = 35;
             $sections = array(1, 5, 8, 11, 15, 18, 22);
             break;
         case 'visual_reception':
             $q_prefix = 'visual_recept';
             $max = 33;
             $sections = array(1, 3, 7, 9, 16, 19, 25);
             break;
         case 'fine_motor':
             $max = 30;
             $sections = array(1, 4, 7, 11, 13, 16, 21);
             break;
         case 'receptive_language':
             $q_prefix = 'receptive_lang';
             $max = 33;
             $sections = array(1, 4, 8, 12, 18, 22, 25);
             break;
         case 'expressive_language':
             $q_prefix = 'expressive_lang';
             $max = 28;
             $sections = array(1, 4, 7, 11, 15, 19, 22);
             break;
         }
         for($i = $min; $i <= $max; $i += 1) {
             if(in_array($i+1,$sections) || in_array($i+2, $sections)) {
                 // one of the three 1s are the start of another section,
                 // so they're not three consecutive 1s within a section.
                 continue;
             }
             if($responses[$q_prefix . '_' . $i] == '1' &&
                $responses[$q_prefix . '_' . ($i+1)] == '1' &&
                $responses[$q_prefix . '_' . ($i+2)] == '1') {
                    $score[$q_prefix . '_calc_basal'] = $i;
                    return $i;
                }
         }
     }
     function band_of_error($age){
        if($age <= 4){
           return array('gross_motor_error_90' => 9,
                        'gross_motor_error_95' => 11,
                        'visual_reception_error_90' => 8,
                        'visual_reception_error_95' => 10,
                        'fine_motor_error_90' => 9,
                        'fine_motor_error_95' => 10,
                        'receptive_language_error_90' => 10,
                        'receptive_language_error_95' => 12,
                        'expressive_language_error_90' => 8,
                        'expressive_language_error_95' => 10
                     );
        }
        else if ($age <= 12){
           return array('gross_motor_error_90' => 7,
                          'gross_motor_error_95' => 8,
                          'visual_reception_error_90' => 7,
                          'visual_reception_error_95' => 9,
                          'fine_motor_error_90' => 9,
                          'fine_motor_error_95' => 10,
                          'receptive_language_error_90' => 8,
                          'receptive_language_error_95' => 10,
                          'expressive_language_error_90' => 7,
                          'expressive_language_error_95' => 8
                       );
        }
        else if ($age <= 33){
           return array('gross_motor_error_90' => 6,
                            'gross_motor_error_95' => 7,
                            'visual_reception_error_90' => 8,
                            'visual_reception_error_95' => 10,
                            'fine_motor_error_90' => 9,
                            'fine_motor_error_95' => 10,
                            'receptive_language_error_90' => 7,
                            'receptive_language_error_95' => 8,
                            'expressive_language_error_90' => 6,
                            'expressive_language_error_95' => 7
                         );
        }
        else if ($age <= 51){
             return array(    'visual_reception_error_90' => 7,
                              'visual_reception_error_95' => 9,
                              'fine_motor_error_90' => 8,
                              'fine_motor_error_95' => 9,
                              'receptive_language_error_90' => 8,
                              'receptive_language_error_95' => 9,
                              'expressive_language_error_90' => 7,
                              'expressive_language_error_95' => 8
                           );
       }
       else {
              return array(    'visual_reception_error_90' => 12,
                               'visual_reception_error_95' => 14,
                               'fine_motor_error_90' => 9,
                               'fine_motor_error_95' => 9,
                               'receptive_language_error_90' => 9,
                               'receptive_language_error_95' => 11,
                               'expressive_language_error_90' => 9,
                               'expressive_language_error_95' => 10
                            );
           }

     }

     function composite_band_of_error($age){
          if($age <= 4){
             return array('composite_error_90' => 9, 'composite_error_95' => 11);
          }
          else if ($age <= 50){
             return array('composite_error_90' => 7, 'composite_error_95' => 8);
          }
          else{
             return array('composite_error_90' => 9, 'composite_error_95' => 11);
          }
       }

     function composite_descriptor($cognitive_t_score){
          if ($cognitive_t_score >= 260) {
            return "Very High";
          } else if ($cognitive_t_score >= 231) {
            return "Above Average";
          } else if ($cognitive_t_score >= 169) {
            return "Average";
          } else if ($cognitive_t_score >= 138) {
            return "Below Average";
          } else {
             return "Very Low";
          }
     }

     function percentile($t_score){
        $percentile_for_t_score = array(
           69 => 97,
           68 => 96,
           67 => 96,
           66 => 95,
           65 => 93,
           64 => 92,
           63 => 90,
           62 => 88,
           61 => 86,
           60 => 84,
           59 => 82,
           58 => 79,
           57 => 76,
           56 => 73,
           55 => 69,
           54 => 66,
           53 => 62,
           52 => 58,
           51 => 54,
           50 => 50,
           49 => 46,
           48 => 42,
           47 => 38,
           46 => 34,
           45 => 31,
           44 => 27,
           43 => 24,
           42 => 21,
           41 => 18,
           40 => 16,
           39 => 14,
           38 => 12,
           37 => 10,
           36 => 8,
           35 => 7,
           34 => 5,
           33 => 4,
           32 => 4,
           31 => 3
           );

        $percentile = 0;
        $description = '';
        if($t_score >= 70){
           $description = 'Very High';
           if($t_score >= 72){
              $percentile = 99;
           }else{
              $percentile = 98;
           }
        }
        else if($t_score >= 31){
           $percentile = $percentile_for_t_score[$t_score];
           if ($t_score >= 61) {
              $description = 'Above Average';
           }
           else if ($t_score >= 40) {
               $description = 'Average';
           }
           else{
              $description = 'Below Average';
           }
        }
        else{
           $description = 'Very Low';
           if ($t_score >= 29) {
               $percentile = 2;
           }
           else{
              $percentile = 1;
           }
        }

        return array('percentile' => $percentile, 'description' => $description);
     }

     function max($x, $y){
        if($x == nil){
           return $y;
        }
        if($y == nil){
           return $x;
        }

        if($x > $y){
           return $x;
        }
        else{
           return $y;
        }
     }

     // For certification module
     function _getExaminerNames() {
        $db =& Database::singleton();

        $centerID = $db->pselectOne("SELECT session.CenterID FROM session, flag WHERE session.ID=flag.SessionID and flag.CommentID=:cmnt_id", array('cmnt_id'=>$this->getCommentID()));
        if(is_array($centerID)) {
            $centerID = null;
        }
        $candID = isset($_REQUEST['candID']) ? $_REQUEST['candID'] : '';

         $project = $db->pselectOne("SELECT ProjectID from candidate where CandID =:cnd_id", array('cnd_id'=>$candID));
         list($CertificationEnabled, $CertificationProjects, $CertificationInstruments) = $this->_getCertificationConfig();

         if($CertificationEnabled && in_array($project, $CertificationProjects)
         )
            // Don't need to check this because we know it's the mullen, and because the config contains mullen_xxxx instead of just "mullen" it won't work
             // && in_array($this->testName, $CertificationInstruments)) 
         {
             $visit_label = $db->pselectOne("SELECT LOWER(Visit_label) FROM session WHERE ID=:ssn_id", array('ssn_id'=>$this->getSessionID()));
             $test_id = $db->pselectOne("SELECT ID FROM test_names WHERE Test_name=:tst_name", array('tst_name'=>$this->testName));

             $query = "SELECT certification.examinerID, full_name FROM certification JOIN examiners ON (certification.examinerID=examiners.examinerID) WHERE testID LIKE CONCAT(:testID, '%') AND pass=:cert_id AND centerID=:cid AND visit_label LIKE CONCAT(:vl, '%') ORDER BY full_name";
             if($visit_label == 'v03' || $visit_label=='v06' || $visit_label == 'v09') {
                 $visit_label = '3-9';
             } elseif ($visit_label == 'v12' || $visit_label == 'v15') {
                 $visit_label = '12-15';
             } elseif ($visit_label == 'v18') {
                 $visit_label = '18';
             } elseif( $visit_label == 'v24' || $visit_label == 'v36') {
                 $visit_label = '24-36';
             } elseif ($visit_label == 'v37plus') {
                 $visit_label = '37';
             }

             $results = $db->pselect($query, array(
                 'testID' => $test_id,
                 'cert_id' => 'certified',
                 'cid' => $centerID,
                 'vl' => $visit_label
             ));
             
         } else {
             $results = $db->pselect("SELECT examinerID, full_name FROM examiners WHERE centerID=:centre ORDER BY full_name", array('centre' => $centerID));
             
         }

         $examiners = array('' => '');
         if(is_array($results) && !empty($results)) {
             foreach($results AS $row) {
                 $examiners[$row['examinerID']] = $row['full_name'];
             }
         }
         return $examiners;

     }

}
?>
