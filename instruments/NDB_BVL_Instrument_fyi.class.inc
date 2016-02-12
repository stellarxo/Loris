<?php

require_once 'HTML/QuickForm.php';
require_once 'HTML/QuickForm/Renderer/Array.php';
require_once "ProjectUtility.class.inc";

class NDB_BVL_Instrument_fyi extends NDB_BVL_Instrument
{
/*
INSERT INTO test_names VALUES ('', 'fyi', 'First Year Inventory', '0', '1');
INSERT INTO instrument_subtests VALUES('', 'fyi', 'fyi_page1', '#1-#46', 1);
INSERT INTO instrument_subtests VALUES('', 'fyi', 'fyi_page2', '#47-#63', 2);
*/

    var $ValidityEnabled = false;
    var $ValidityRequired = false;

   var $scoreCols = array('risk_score' => "Risk Score",
   'percentile' => "Percentile", 
   'soc_com_risk'=>"Social-Communication domain",
   'sen_reg_risk'=>"Sensory-Regulatory domain",
	'orientrec'=>"Social Orienting and Receptive",
	'affeng'=>"Social Affective Engagement",
	'imitate'=>"Imitation",
	'express'=>"Expressive Communication",
	'senproc'=>"Sensory Processing",
	'regpat'=>"Regulatory Patterns",
	'react'=>"Reactivity",
	'repplay'=>"Repetitive Play & Behavior");

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
        $this->testName = "fyi";           // test_names.Test_name
        $this->table = 'fyi';              // name of database table corresponding to instrument
        // data keyed by commentID
        $this->commentID = $commentID;
        
        //The array of dates/timestamps to convert to database dates/timestamps
        //Any HTML_Quickform date elements must be listed here
        $this->dateTimeFields=array("Date_taken");
            
        //The array of selects with multiple answers allowed
        //Any HTML_Quickform multiple selects must be listed here
        $this->_selectMultipleElements = array("mother_ethnicity", "father_ethnicity");

        // required fields for data entry completion status
        $this->_requiredElements = array('Examiner', "q_1", "q_47");

	/**
	 * Array of column names to be ignored by the double data entry conflict detector.
	 */
	$this->_doubleDataEntryDiffIgnoreColumns = array('CommentID', 'UserID', 'Testdate',  'Window_Difference', 'Candidate_Age',
							 'mother_highest_grade',
							 'father_highest_grade',
							 'person_filling_out_specify',
							 'person_filling_out_specify_status',
							 'q_62',
							 'q_62_status',
							 'q_63',
							 'q_63_status',
                             'orientrec', 
                             'affeng', 
                             'imitate', 
                             'express', 
                             'senproc', 
                             'regpat', 
                             'react',
                             'repplay', 
                             'soc_com_risk', 
                             'sen_reg_risk', 
                             'risk_score', 
                             'percentile',
                             'Data_entry_completion_status');


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
        if(preg_match("/fyi(_page[0-9]+)/",$this->page,$matches)){
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
        $this->form->addElement('header', 'instrument_title', "First Year Inventory");
        
        // automatically adds examiner & date of administration
        $this->_addMetadataFields();

        $this->form->addElement("select", "mother_ethnicity", "Baby's Mother Race/Ethnicity: (check 1 or more)", array(null=>"", "white"=>"White",
        "black_african_american"=>"Black/African-American",
        "hispanic_latino"=>"Hispanic/Latino",
        "asian"=>"Asian",
        "american_indian_alaskan_native"=>"American-Indian/Alaskan Native",
        "native_hawaiian_pacific_islander"=>"Native Hawaiian/Pacific Islander",
        "not_answered"=>"Not Answered"), "multiple");
        
        $education_levels = array(null => "", "not_answered" => "Not Answered", "j_high" => "Junior High", "some_hs" => "Some Highschool", "high_school"=> "High School", "some_college" => "Some College/2yr Degree", "college_degree" => "College Degree", "some_grad_level" => "Some Graduate Level", "grad_degree" => "Graduate Degree");
        
        $this->form->addElement("select", "mother_highest_grade", "Mother's highest grade completed or degree obtained:", $education_levels);
        
        
        $this->form->addElement("select", "father_ethnicity", "Baby's Father Race/Ethnicity (check 1 or more)", array(null=>"", "white"=>"White",
        "black_african_american"=>"Black/African-American",
        "hispanic_latino"=>"Hispanic/Latino",
        "asian"=>"Asian",
        "american_indian_alaskan_native"=>"American-Indian/Alaskan Native",
        "native_hawaiian_pacific_islander"=>"Native Hawaiian/Pacific Islander",
        "not_answered"=>"Not Answered"), "multiple");
        
        $this->form->addElement("select", "father_highest_grade", "Father's highest grade completed or degree obtained:", $education_levels);
        
        $this->form->addElement("select", "person_filling_out", "The person filling out this form is the (check one):", array(null=>"", "mother"=>"Mother", "father"=>"Father", "both"=>"Both", "other"=>"Other (specify):", "not_answered"=>"Not Answered"));
        $this->addTextElement("person_filling_out_specify", $this->indent . "Specify:", array("person_filling_out{@}=={@}other"), "Please specify.");
        
         $this->form->addElement("header", null, "Scores");
         foreach($this->scoreCols as $db_name=>$english_name){
            $this->form->addElement("static", $db_name, $english_name);            
         }
    }
   
    function _page1(){
        $this->form->addElement("header", null, "Please check the ONE BOX...");
        $questionArray = array("1. Does your baby turn to look at you when you call your baby's name?",
                    "2. Does your baby seem bothered by loud sounds?",
                    "3. Does your baby seem overly sensitive to your touch (for example, fuss or pull away when you touch him or her)?",
                    "4. During familiar games like 'I'm gonna get you? does your baby get excited because he or she knows what will happen next?",
                    "5. Does your baby seem to have trouble hearing?",
                    "6. When you and your baby are facing each other, does your baby turn his or her eyes to avoid looking at you?",
                    "7. In new or strange situations, does your baby look at your face for comfort?",
                    "8, Does your baby ignore loud or startling sounds?",
                    "9. Does your baby spit out certain textures of foods, such as lumpy or chunky pieces?",
                    "10. When you point to something interesting, does your baby turn to look at it?",
                    "11. Is your baby content to play alone for an hour or more at a time?",
                    "12. Does your baby look at people when they begin talking, even when they are not talking directly to your baby?",
                    "13. Does your baby rock his or her body back and forth over and over?",
                    "14. Does your baby look up from playing with a favorite toy if you show him or her a different toy?",
                    "15. Does your baby get upset when you need to switch your baby from one activity to another one?",
                    "16. Is it easy to understand your baby's facial expressions?",
                    "17. Does your baby forcefully press his or her face, head, or body against people or furniture?",
                    "18. Does your baby smile while looking at you?",
                    "19. Does your baby try to get your attention to show you something interesting?",
                    "20. Does your baby try to get your attention to play games like peek-a-boo?",
                    "21. Does your baby try to get your attention to obtain a favorite toy or food?",
                    "22. Does your baby try to get your attention to play physical games, like swinging, tickling, or being tossed in the air?",
                    "23. When your baby is awake and you pick him or her up, does your baby's body feel loose or floppy?",
                    "24. Does your baby copy or imitate you when you make sounds or noises with your mouth?",
                    "25. Does your baby copy or imitate your actions, like sticking out your tongue, clapping your hands, or shaking your head?",
                    "26. Does your baby copy or imitate you when you do something with a toy or object, like shaking a rattle or banging a spoon on the table?",
                    "27. Is it difficult to calm your baby once he or she becomes upset?",
                    "28. Are your baby's sleeping and waking patterns regular from day to day?",
                    "29. Does your baby try to get your attention by making sounds and looking at you at the same time?",
                    "30. Does your baby get stuck doing a simple activity over and over?",
                    "31. Does your baby seem interested in other babies his or her age?",
                    "32. Does your baby babble by putting sounds together, such as 'ba-ba', 'ga-ga-ga', or 'ba-dee'?",
                    "33. Does your baby enjoy staring at a bright light for long periods of time?",
                    "34. Does your baby use gestures such as raising arms to be picked up, shaking head, or waving bye-bye?",
                    "35. When you say 'Where's (a familiar person or object)?? without pointing or showing, will your baby look at the person or object named?",
                    "36. Does your baby use the first finger and tip of the thumb to pick up a very small object like a raisin or a Cheerio?",
                    "37. Does your baby seem to get stuck on playing with a part of a toy (such as an eyeball, label, wheel or tag), instead of the whole toy?",
                    "38. Does your baby communicate with you by using his or her finger to point at objects or pictures",
                    "39. Do you get the feeling that your baby plays or communicates with you less now than in the past?",
                    "40. Do your baby's eyes line up together when looking at an object?",
                    "41. Are your baby's feeding patterns regular from day to day",
                    "42. Does your baby enjoy rubbing or scratching toys or objects for long periods of time?",
                    "43. Does your baby seem to get his or her body stuck in a position or posture that is hard to move out of?",
                    "44. Does your baby enjoy making objects spin over and over in the same way?",
                    "45. While lying down, does your baby enjoy kicking his or her feet over and over for long periods of time?",
                    "46. Does your baby stare at his or her fingers while in front of his or her eyes?");
        $counter = 1;
        foreach($questionArray as $label) {
            $this->form->addElement("select", "q_" . $counter, $label, array(""=>null, "never"=>"Never", "seldom"=>"Seldom", "sometimes"=>"Sometimes", "often"=>"Often", "not_answered"=>"Not Answered"));
            //insert a line break, just to bust up the monotony...
            if($counter%10 == 0) {
                $this->form->addElement("static", null, "<BR>");
            }
            $counter++;
        }        
    }

    function _page2(){
        $this->form->addElement("header", null, "For the following questions, please circle the ONE ANSWER that best describes your baby:");
        
        $this->form->addElement("select", "q_47", "47. Which of the following best describes your baby's typical play..?", array(
                                ""=>null,
                                "a_same_way"=>"a. Uses the toy in more or less the same way all the time.",
                                "b_new_way"=>"b. Occasionally finds a new way to play with the toy.",
                                "c_often_explores"=>"c. Often explores new ways to play with the toy.",
                                "not_answered"=>"Not Answered"));

        $this->form->addElement("select", "q_48", "48. Which of the following describes your baby's interest in toys..?", array(
                                ""=>null,
                                "a_one_or_two"=>"a. Plays with one or two special toys most of the time.",
                                "b_small_number"=>"b. Plays with a small number of toys (3-5).",
                                "c_large_number"=>"c. Plays with a large number of toys (6 or more).",
                                "not_answered"=>"Not Answered"));

        $this->form->addElement("select", "q_49", "49. When you introduce your baby to a new game..?", array(
                                ""=>null,
                                "a_joins_in_immediately"=>"a. Almost always joins in immediately without any help.",
                                "b_usually_joins_in"=>"b. Usually joins in, with a little help.",
                                "c_joins_in_only_with_a_lot"=>"c Joins in only with a lot of help",
                                "d_doesn_t_seem_interested"=>"d. Doesn't seem very interested in new baby games.", 
                                "not_answered"=>"Not Answered"));

        $this->form->addElement("select", "q_50", "50. What do you typically have to do to get your baby to look..?", array(
                                ""=>null,
                                "a_show_different_toy"=>"a. Just show him or her different toy.",
                                "b_move_shake_make_noise"=>"b. Move, shake or make a noise with the different toy.",
                                "c_take_favourite"=>"c. Take the favorite toy away and give your baby the different toy.",
                                "not_answered"=>"Not Answered"));

        $this->form->addElement("select", "q_51", "51. What is your baby's usual reaction..?", array(
                                ""=>null,
                                "a_doesn_t_notice"=>"a. Doesn't seem to notice.",
                                "b_reacts_a_little"=>"b. Reacts a little but gets over it quickly.",
                                "c_sensitive_or_cries"=>"c. Seems very sensitive or cries for a long time.",
                                "not_answered"=>"Not Answered"));

        $this->form->addElement("select", "q_52", "52. What do you typically have to do to get your baby to turn..?", array(
                                ""=>null,
                                "a_say_name"=>"a. Simply say your baby's name.",
                                "b_say_name_several"=>"b. Say your baby's name several times.",
                                "c_say_name_loudly"=>"c. Say your baby's name loudly or use other means, such as clapping.",
                                "d_doesn_t_do"=>"d. Your baby doesn't do this yet.",
                                "not_answered"=>"Not Answered"));

        $this->form->addElement("select", "q_53", "53. What do you typically have to do to get your baby to smile..?", array(
                                ""=>null,
                                "a_smiling_laughing"=>"a. Smiling and laughing is enough.",
                                "b_touch_tickle"=>"b. Usually need to touch and tickle.",
                                "c_swing_bounce"=>"c. Usually need to swing and bounce.",
                                "d_doesn_t_do"=>"d. Your baby doesn't do this yet.",
                                "not_answered"=>"Not Answered"));

        $this->form->addElement("select", "q_54", "54. On a typical night, how many hours does your baby sleep?", array(
                                ""=>null,
                                "a_12_or_more"=>"a. 12 or more.",
                                "b_10_11"=>"b. 10-11.",
                                "c_8_9"=>"c. 8-9",
                                "d_7_or_fewer"=>"d. 7 or fewer.",
                                "not_answered"=>"Not Answered"));

        $this->form->addElement("select", "q_55", "55. On a typical night, how many times does your baby wake up?", array(
                                ""=>null,
                                "a_0"=>"a. 0 times.",
                                "b_1_2"=>"b. 1-2 times.",
                                "c_3_or_more"=>"c. 3 or more times.",
                                "not_answered"=>"Not Answered"));

        $this->form->addElement("select", "q_56", "56. Which of the following best describes your baby's skill level?", array(
                                ""=>null,
                                "a_walks_independently"=>"a. Walks independently.",
                                "b_walks_with_hands"=>"b. Walks with hand(s) held, holding a push-toy, or holding onto furniture.",
                                "c_pulls_up_to_stand"=>"c. Pulls up to stand but doesn't walk yet.",
                                "d_does_not_pull"=>"d. Does not pull up to stand yet.",
                                "not_answered"=>"Not Answered"));

        $this->form->addElement("select", "q_57", "57. Which of the following best describes your baby's typical day?", array(
                                ""=>null,
                                "a_never_gets_upset"=>"a. Almost never gets upset.",
                                "b_upset_calmed_1_3"=>"b. Gets upset and needs to be calmed 1-3 times.",
                                "c_upset_calmed_4_6"=>"c. Gets upset and needs to be calmed 4-6 times.",
                                "d_upset_calmed_6_or_more"=>"d. Gets upset and needs to be calmed 6 or more times.",
                                "not_answered"=>"Not Answered"));

        $this->form->addElement("select", "q_58", "58. If you start a game by copying or imitating a sound..?", array(
                                ""=>null,
                                "a_doesn_t_notice_sound"=>"a. Doesn't seem to notice the sound.",
                                "b_looks_but_doesn_t_make"=>"b. Looks at you, but doesn't make the sound.",
                                "c_looks_and_makes"=>"c. Looks at you and makes the sound.",
                                "d_plays_making"=>"d. Plays the game, making the sound seveial liiiies.",
                                "not_answered"=>"Not Answered"));

        $this->form->addElement("select", "q_59", "59. When your baby is awake and not eating..?", array(
                                ""=>null,
                                "a_almost_never"=>"a Almost never keeps a toy or object in his or her mouth.",
                                "b_sometimes"=>"b. Sometimes keeps a toy or object in his or her mouth.",
                                "c_often"=>"c. Often keeps a toy or object in his or her mouth.",
                                "d_almost_always"=>"d. Almost always keeps a toy or object in his or her mouth.",
                                "not_answered"=>"Not Answered"));

        $this->form->addElement("select", "q_60", "60. Which of the following best describes the way your baby coordinates..?", array(
                                ""=>null,
                                "a_almost_always"=>"a. Almost always looks at the toy that he or she is physically handling.",
                                "b_sometimes"=>"b. Sometimes looks at the toy that he or she is physically handling.",
                                "c_rarely"=>"c. Rarely looks at the toy that he or she is physically handling.",
                                "d_almost_never"=>"d. Almost never looks at the toy that he or she is physically handling.",
                                "not_answered"=>"Not Answered"));

        $questionArray = array("p", "b", "t", "d", "k", "g", "m", "n", "w", "y", "h", "s");
         $this->form->addElement("static", null, "61. Please check all of the following sounds you've heard your baby use in babble..:");
         foreach($questionArray as $letter) {
            $this->form->addElement("advcheckbox", "sounds_" . $letter, null, $letter, null, array("not_used", "used"));
        }

        $this->addTextAreaElement("q_62", "62. Do you or others have any concerns..?  If yes, please describe.");

        $this->addTextAreaElement("q_63", "63. Does your baby have any unusual physical or medical characteristics? If yes, please describe.");

        $this->form->addElement("static", null, "Thank you for taking the time to respond to this questionnaire.");
    }
    
    function score() {
         if($this->_determineDataEntryCompletionStatus() == "Incomplete") {
            return;
         }

         // Get the item scores
         $score_record=array();

         $db =& Database::singleton();

         $this->_nullScores($this->scoreCols);
   		
   		$query = "SELECT * FROM ".$this->table." WHERE CommentID='".$this->getCommentID()."'";
         $db->selectRow($query, $score_record);
         
         
         //print_r($score_record);
         
         //Calculate risk points
         $risk_points = array();
         
         //Question 1
         if($score_record["q_1"] == "never" || $score_record["q_1"] == "seldom"){
            $risk_points["q_1"] = 2;
         }
         else if ($score_record["q_1"] == "sometimes" ){
            $risk_points["q_1"] = 1;
         }
         else if ($score_record["q_1"] == "often" ){
            $risk_points["q_1"] = 0;
         }
         
         if($score_record["q_2"] == "never" || $score_record["q_2"] == "often"){
            $risk_points["q_2"] = 1;
         }
         else if ($score_record["q_2"] == "sometimes" || $score_record["q_2"] == "seldom"){
            $risk_points["q_2"] = 0;
         }
         
         if($score_record["q_3"] == "never" || $score_record["q_3"] == "seldom"){
            $risk_points["q_3"] = 0;
         }
         else if ($score_record["q_3"] == "sometimes" ){
            $risk_points["q_3"] = 1;
         }
         else if ($score_record["q_3"] == "often" ){
            $risk_points["q_3"] = 2;
         }
         
         if($score_record["q_4"] == "never" || $score_record["q_4"] == "seldom"){
            $risk_points["q_4"] = 2;
         }
         else if ($score_record["q_4"] == "sometimes" ){
            $risk_points["q_4"] = 1;
         }
         else if ($score_record["q_4"] == "often" ){
            $risk_points["q_4"] = 0;
         }
         
         if($score_record["q_5"] == "never"){
            $risk_points["q_5"] = 0;
         }
         else if ($score_record["q_5"] == "seldom" ){
            $risk_points["q_5"] = 1;
         }
         else if ($score_record["q_5"] == "often" ||  $score_record["q_5"] == "sometimes"){
            $risk_points["q_5"] = 2;
         }
         
         if($score_record["q_6"] == "never" || $score_record["q_6"] == "seldom"){
            $risk_points["q_6"] = 0;
         }
         else if ($score_record["q_6"] == "sometimes" ){
            $risk_points["q_6"] = 1;
         }
         else if ($score_record["q_6"] == "often" ){
            $risk_points["q_6"] = 2;
         }
         
         if($score_record["q_7"] == "never"){
            $risk_points["q_7"] = 2;
         }
         else if ($score_record["q_7"] == "seldom" ){
            $risk_points["q_7"] = 1;
         }
         else if ($score_record["q_7"] == "often" ||  $score_record["q_7"] == "sometimes"){
            $risk_points["q_7"] = 0;
         }
         
         if($score_record["q_8"] == "never" || $score_record["q_8"] == "seldom" || $score_record["q_8"] == "sometimes"){
            $risk_points["q_8"] = 0;
         }
         else if ($score_record["q_8"] == "often"){
            $risk_points["q_8"] = 1;
         }
         
         if($score_record["q_9"] == "never" || $score_record["q_9"] == "seldom" || $score_record["q_9"] == "sometimes"){
            $risk_points["q_9"] = 0;
         }
         else if ($score_record["q_9"] == "often"){
            $risk_points["q_9"] = 1;
         }
         
         if($score_record["q_10"] == "never" || $score_record["q_10"] == "seldom"){
            $risk_points["q_10"] = 2;
         }
         else if ($score_record["q_10"] == "often" || $score_record["q_10"] == "sometimes"){
            $risk_points["q_10"] = 0;
         }
         
         if($score_record["q_11"] == "never" || $score_record["q_11"] == "seldom" || $score_record["q_11"] == "sometimes"){
            $risk_points["q_11"] = 0;
         }
         else if ($score_record["q_11"] == "often"){
            $risk_points["q_11"] = 1;
         }
         
         if($score_record["q_12"] == "never" || $score_record["q_12"] == "seldom"){
            $risk_points["q_12"] = 2;
         }
         else if ($score_record["q_12"] == "often" || $score_record["q_12"] == "sometimes"){
            $risk_points["q_12"] = 0;
         }
         
         if($score_record["q_13"] == "never" || $score_record["q_13"] == "seldom" || $score_record["q_13"] == "sometimes"){
            $risk_points["q_13"] = 0;
         }
         else if ($score_record["q_13"] == "often"){
            $risk_points["q_13"] = 1;
         }
         
         if($score_record["q_14"] == "never" || $score_record["q_14"] == "seldom"){
            $risk_points["q_14"] = 2;
         }
         else if ($score_record["q_14"] == "often" || $score_record["q_14"] == "sometimes"){
            $risk_points["q_14"] = 0;
         }
         
         if($score_record["q_15"] == "never" || $score_record["q_15"] == "seldom" || $score_record["q_15"] == "sometimes"){
            $risk_points["q_15"] = 0;
         }
         else if ($score_record["q_15"] == "often"){
            $risk_points["q_15"] = 1;
         }
         
         if($score_record["q_16"] == "never" || $score_record["q_16"] == "seldom"){
            $risk_points["q_16"] = 2;
         }
         else if ($score_record["q_16"] == "sometimes" ){
            $risk_points["q_16"] = 1;
         }
         else if ($score_record["q_16"] == "often" ){
            $risk_points["q_16"] = 0;
         }
         
         if($score_record["q_17"] == "never" || $score_record["q_17"] == "seldom" || $score_record["q_17"] == "sometimes"){
            $risk_points["q_17"] = 0;
         }
         else if ($score_record["q_17"] == "often"){
            $risk_points["q_17"] = 1;
         }
         
         if($score_record["q_18"] == "never" || $score_record["q_18"] == "seldom"){
            $risk_points["q_18"] = 2;
         }
         else if ($score_record["q_18"] == "sometimes" ){
            $risk_points["q_18"] = 1;
         }
         else if ($score_record["q_18"] == "often" ){
            $risk_points["q_18"] = 0;
         }
         
         if($score_record["q_19"] == "often" || $score_record["q_19"] == "seldom" || $score_record["q_19"] == "sometimes"){
            $risk_points["q_19"] = 0;
         }
         else if ($score_record["q_19"] == "never"){
            $risk_points["q_19"] = 1;
         }
         
         if($score_record["q_20"] == "often" || $score_record["q_20"] == "seldom" || $score_record["q_20"] == "sometimes"){
            $risk_points["q_20"] = 0;
         }
         else if ($score_record["q_20"] == "never"){
            $risk_points["q_20"] = 1;
         }
         
         if($score_record["q_21"] == "never"){
            $risk_points["q_21"] = 2;
         }
         else if ($score_record["q_21"] == "seldom" ){
            $risk_points["q_21"] = 1;
         }
         else if ($score_record["q_21"] == "often" ||  $score_record["q_21"] == "sometimes"){
            $risk_points["q_21"] = 0;
         }
         
         if($score_record["q_22"] == "often" || $score_record["q_22"] == "seldom" || $score_record["q_22"] == "sometimes"){
            $risk_points["q_22"] = 0;
         }
         else if ($score_record["q_22"] == "never"){
            $risk_points["q_22"] = 1;
         }
         
         if($score_record["q_23"] == "never"){
            $risk_points["q_23"] = 0;
         }
         else if ($score_record["q_23"] == "seldom" ){
            $risk_points["q_23"] = 1;
         }
         else if ($score_record["q_23"] == "often" ||  $score_record["q_23"] == "sometimes"){
            $risk_points["q_23"] = 2;
         }
         
         if($score_record["q_24"] == "never" || $score_record["q_24"] == "seldom"){
            $risk_points["q_24"] = 2;
         }
         else if ($score_record["q_24"] == "often" || $score_record["q_24"] == "sometimes"){
            $risk_points["q_24"] = 0;
         }
         
         if($score_record["q_25"] == "never" || $score_record["q_25"] == "seldom"){
            $risk_points["q_25"] = 2;
         }
         else if ($score_record["q_25"] == "often" || $score_record["q_25"] == "sometimes"){
            $risk_points["q_25"] = 0;
         }
         
         if($score_record["q_26"] == "never" || $score_record["q_26"] == "seldom"){
            $risk_points["q_26"] = 2;
         }
         else if ($score_record["q_26"] == "often" || $score_record["q_26"] == "sometimes"){
            $risk_points["q_26"] = 0;
         }
         
         if($score_record["q_27"] == "never" || $score_record["q_27"] == "seldom" || $score_record["q_27"] == "sometimes"){
            $risk_points["q_27"] = 0;
         }
         else if ($score_record["q_27"] == "often"){
            $risk_points["q_27"] = 2;
         }
         
         if($score_record["q_28"] == "never" || $score_record["q_28"] == "seldom"){
            $risk_points["q_28"] = 2;
         }
         else if ($score_record["q_28"] == "often" || $score_record["q_28"] == "sometimes"){
            $risk_points["q_28"] = 0;
         }
         
         if($score_record["q_29"] == "never" || $score_record["q_29"] == "seldom"){
            $risk_points["q_29"] = 2;
         }
         else if ($score_record["q_29"] == "often" || $score_record["q_29"] == "sometimes"){
            $risk_points["q_29"] = 0;
         }
         
         if($score_record["q_30"] == "never" || $score_record["q_30"] == "seldom" || $score_record["q_30"] == "sometimes"){
            $risk_points["q_30"] = 0;
         }
         else if ($score_record["q_30"] == "often"){
            $risk_points["q_30"] = 2;
         }
         
         if($score_record["q_31"] == "never"){
            $risk_points["q_31"] = 2;
         }
         else if ($score_record["q_31"] == "seldom" ){
            $risk_points["q_31"] = 1;
         }
         else if ($score_record["q_31"] == "often" ||  $score_record["q_31"] == "sometimes"){
            $risk_points["q_31"] = 0;
         }
         
         if($score_record["q_32"] == "never" || $score_record["q_32"] == "seldom"){
            $risk_points["q_32"] = 2;
         }
         else if ($score_record["q_32"] == "sometimes" ){
            $risk_points["q_32"] = 1;
         }
         else if ($score_record["q_32"] == "often" ){
            $risk_points["q_32"] = 0;
         }
         
         if($score_record["q_33"] == "never" || $score_record["q_33"] == "seldom"){
            $risk_points["q_33"] = 0;
         }
         else if ($score_record["q_33"] == "sometimes" ){
            $risk_points["q_33"] = 1;
         }
         else if ($score_record["q_33"] == "often" ){
            $risk_points["q_33"] = 2;
         }
         
         if($score_record["q_34"] == "never" || $score_record["q_34"] == "seldom"){
            $risk_points["q_34"] = 2;
         }
         else if ($score_record["q_34"] == "sometimes" ){
            $risk_points["q_34"] = 1;
         }
         else if ($score_record["q_34"] == "often" ){
            $risk_points["q_34"] = 0;
         }
         
         if($score_record["q_35"] == "never"){
            $risk_points["q_35"] = 2;
         }
         else if ($score_record["q_35"] == "seldom" ){
            $risk_points["q_35"] = 1;
         }
         else if ($score_record["q_35"] == "often" ||  $score_record["q_35"] == "sometimes"){
            $risk_points["q_35"] = 0;
         }
         
         if($score_record["q_36"] == "never" || $score_record["q_36"] == "seldom" || $score_record["q_36"] == "sometimes"){
            $risk_points["q_36"] = 0;
         }
         else if ($score_record["q_36"] == "often"){
            $risk_points["q_36"] = 1;
         }
         
         if($score_record["q_37"] == "never" || $score_record["q_37"] == "seldom" || $score_record["q_37"] == "sometimes"){
            $risk_points["q_37"] = 0;
         }
         else if ($score_record["q_37"] == "often"){
            $risk_points["q_37"] = 1;
         }
         
         if($score_record["q_38"] == "often" || $score_record["q_38"] == "seldom" || $score_record["q_38"] == "sometimes"){
            $risk_points["q_38"] = 0;
         }
         else if ($score_record["q_38"] == "never"){
            $risk_points["q_38"] = 1;
         }
         
         if($score_record["q_39"] == "never" || $score_record["q_39"] == "seldom"){
            $risk_points["q_39"] = 0;
         }
         else if ($score_record["q_39"] == "sometimes" ){
            $risk_points["q_39"] = 1;
         }
         else if ($score_record["q_39"] == "often" ){
            $risk_points["q_39"] = 2;
         }
         
         if($score_record["q_40"] == "never" || $score_record["q_40"] == "seldom" || $score_record["q_40"] == "sometimes"){
            $risk_points["q_40"] = 2;
         }
         else if ($score_record["q_40"] == "often"){
            $risk_points["q_40"] = 0;
         }
         
         if($score_record["q_41"] == "never" || $score_record["q_41"] == "seldom"){
            $risk_points["q_41"] = 2;
         }
         else if ($score_record["q_41"] == "often" || $score_record["q_41"] == "sometimes"){
            $risk_points["q_41"] = 0;
         }
         
         if($score_record["q_42"] == "never" || $score_record["q_42"] == "seldom"){
            $risk_points["q_42"] = 0;
         }
         else if ($score_record["q_42"] == "sometimes" ){
            $risk_points["q_42"] = 1;
         }
         else if ($score_record["q_42"] == "often" ){
            $risk_points["q_42"] = 2;
         }
         
         if($score_record["q_43"] == "never" || $score_record["q_43"] == "seldom"){
            $risk_points["q_43"] = 0;
         }
         else if ($score_record["q_43"] == "sometimes" ){
            $risk_points["q_43"] = 1;
         }
         else if ($score_record["q_43"] == "often" ){
            $risk_points["q_43"] = 2;
         }
         
         if($score_record["q_44"] == "never" || $score_record["q_44"] == "seldom" || $score_record["q_44"] == "sometimes"){
            $risk_points["q_44"] = 0;
         }
         else if ($score_record["q_44"] == "often"){
            $risk_points["q_44"] = 1;
         }
         
         if($score_record["q_45"] == "never" || $score_record["q_45"] == "seldom" || $score_record["q_45"] == "sometimes"){
            $risk_points["q_45"] = 0;
         }
         else if ($score_record["q_45"] == "often"){
            $risk_points["q_45"] = 1;
         }
         
         if($score_record["q_46"] == "never" || $score_record["q_46"] == "seldom" || $score_record["q_46"] == "sometimes"){
            $risk_points["q_46"] = 0;
         }
         else if ($score_record["q_46"] == "often"){
            $risk_points["q_46"] = 1;
         }
         
         if(substr($score_record["q_47"], 0, 1) == "b" || substr($score_record["q_47"], 0, 1) == "c" || substr($score_record["q_47"], 0, 1) == "d"){
            $risk_points["q_47"] = 0;
         }
         else if (substr($score_record["q_47"], 0, 1) == "a"){
            $risk_points["q_47"] = 1;
         }
         
         if(substr($score_record["q_48"], 0, 1) == "b" || substr($score_record["q_48"], 0, 1) == "c" || substr($score_record["q_48"], 0, 1) == "d"){
            $risk_points["q_48"] = 0;
         }
         else if (substr($score_record["q_48"], 0, 1) == "a"){
            $risk_points["q_48"] = 2;
         }
         
         if(substr($score_record["q_49"], 0, 1) == "a" || substr($score_record["q_49"], 0, 1) == "b"){
            $risk_points["q_49"] = 0;
         }
         else if (substr($score_record["q_49"], 0, 1) == "c" ){
            $risk_points["q_49"] = 1;
         }
         else if (substr($score_record["q_49"], 0, 1) == "d" ){
            $risk_points["q_49"] = 2;
         }
         
         if(substr($score_record["q_50"], 0, 1) == "a" || substr($score_record["q_50"], 0, 1) == "b" || substr($score_record["q_50"], 0, 1) == "d"){
            $risk_points["q_50"] = 0;
         }
         else if (substr($score_record["q_50"], 0, 1) == "c"){
            $risk_points["q_50"] = 2;
         }
         
         if(substr($score_record["q_51"], 0, 1) == "b" || substr($score_record["q_51"], 0, 1) == "d"){
            $risk_points["q_51"] = 0;
         }
         else if (substr($score_record["q_51"], 0, 1) == "a" || substr($score_record["q_51"], 0, 1) == "c"){
            $risk_points["q_51"] = 2;
         }
         
         if(substr($score_record["q_52"], 0, 1) == "a" || substr($score_record["q_52"], 0, 1) == "b"){
            $risk_points["q_52"] = 0;
         }
         else if (substr($score_record["q_52"], 0, 1) == "c" || substr($score_record["q_52"], 0, 1) == "d"){
            $risk_points["q_52"] = 2;
         }
         
         if(substr($score_record["q_53"], 0, 1) == "a"){
            $risk_points["q_53"] = 0;
         }
         else if (substr($score_record["q_53"], 0, 1) == "b" ){
            $risk_points["q_53"] = 1;
         }
         else if (substr($score_record["q_53"], 0, 1) == "c"  || substr($score_record["q_53"], 0, 1) == "d"){
            $risk_points["q_53"] = 2;
         }
         
         if(substr($score_record["q_54"], 0, 1) == "a" || substr($score_record["q_54"], 0, 1) == "b" || substr($score_record["q_54"], 0, 1) == "c"){
            $risk_points["q_54"] = 0;
         }
         else if (substr($score_record["q_54"], 0, 1) == "d"){
            $risk_points["q_54"] = 2;
         }
         
         if(substr($score_record["q_55"], 0, 1) == "a" || substr($score_record["q_55"], 0, 1) == "b" || substr($score_record["q_55"], 0, 1) == "d"){
            $risk_points["q_55"] = 0;
         }
         else if (substr($score_record["q_55"], 0, 1) == "c"){
            $risk_points["q_55"] = 1;
         }
         
         if(substr($score_record["q_56"], 0, 1) == "a" || substr($score_record["q_56"], 0, 1) == "b"){
            $risk_points["q_56"] = 0;
         }
         else if (substr($score_record["q_56"], 0, 1) == "c" ){
            $risk_points["q_56"] = 1;
         }
         else if (substr($score_record["q_56"], 0, 1) == "d"  ){
            $risk_points["q_56"] = 2;
         }
         
         if(substr($score_record["q_57"], 0, 1) == "a" || substr($score_record["q_57"], 0, 1) == "b"){
            $risk_points["q_57"] = 0;
         }
         else if (substr($score_record["q_57"], 0, 1) == "c" ){
            $risk_points["q_57"] = 1;
         }
         else if (substr($score_record["q_57"], 0, 1) == "d"  ){
            $risk_points["q_57"] = 2;
         }
         
         if(substr($score_record["q_58"], 0, 1) == "a"){
            $risk_points["q_58"] = 2;
         }
         else if (substr($score_record["q_58"], 0, 1) == "b" ){
            $risk_points["q_58"] = 1;
         }
         else if (substr($score_record["q_58"], 0, 1) == "c"   || substr($score_record["q_58"], 0, 1) == "d"){
            $risk_points["q_58"] = 0;
         }
         
         if(substr($score_record["q_59"], 0, 1) == "a" || substr($score_record["q_59"], 0, 1) == "b" || substr($score_record["q_59"], 0, 1) == "c"){
            $risk_points["q_59"] = 0;
         }
         else if (substr($score_record["q_59"], 0, 1) == "d"){
            $risk_points["q_59"] = 2;
         }
         
         if(substr($score_record["q_60"], 0, 1) == "a" || substr($score_record["q_60"], 0, 1) == "b"){
            $risk_points["q_60"] = 0;
         }
         else if (substr($score_record["q_60"], 0, 1) == "c" || substr($score_record["q_60"], 0, 1) == "d"){
            $risk_points["q_60"] = 2;
         }
         
         $sound_total = 0;
         $BDM_total = 0;
         
         $questionArray = array("p", "b", "t", "d", "k", "g", "m", "n", "w", "y", "h", "s");
         foreach($questionArray as $letter) {
            if($score_record["sounds_" . $letter] == "used"){
               $sound_total++;
               if($letter == "b" || $letter == "d" || $letter == "m"){
                  $BDM_total++;
               }
            }
         }
         $X = 0;
         $Y = 0;
         
         if($BDM_total < 2){
            $X = 1;
         }
         if($sound_total <= 3){
            $Y = 1;
         }
         
         $XY_total = $X + $Y;
         
         $D111 = $risk_points["q_1"] + $risk_points["q_5"] + $risk_points["q_10"] + $risk_points["q_12"] + $risk_points["q_14"]
             + $risk_points["q_31"] + $risk_points["q_35"] + $risk_points["q_50"] + $risk_points["q_52"];
                      
         $D112 = $risk_points["q_4"] + $risk_points["q_7"] + $risk_points["q_16"] + $risk_points["q_18"] + $risk_points["q_19"]
              + $risk_points["q_20"] + $risk_points["q_21"] + $risk_points["q_22"];
         
         $D113 = $risk_points["q_24"] + $risk_points["q_25"] + $risk_points["q_26"] + $risk_points["q_49"] + $risk_points["q_53"]
                + $risk_points["q_58"];
                
         $D114 = $risk_points["q_29"] + $risk_points["q_32"] + $risk_points["q_34"] + $risk_points["q_38"] + $XY_total;
         
         $D115 = $risk_points["q_3"] + $risk_points["q_6"] + $risk_points["q_9"] + $risk_points["q_17"] + $risk_points["q_23"]
                + $risk_points["q_59"];
         
         $D116 = $risk_points["q_28"] + $risk_points["q_41"] + $risk_points["q_54"] + $risk_points["q_55"];
         
         $D117 = $risk_points["q_15"] + $risk_points["q_27"] + $risk_points["q_57"];
         
         $D118 = $risk_points["q_11"] + $risk_points["q_13"] + $risk_points["q_30"] + $risk_points["q_33"] + $risk_points["q_37"]
             + $risk_points["q_42"] + $risk_points["q_43"] + $risk_points["q_44"] + $risk_points["q_45"] + $risk_points["q_46"] 
             + $risk_points["q_48"];
          
         if($D111 >= 12){
            $calculatedScores['orientrec'] = 50;
         }
         else if($D111 >= 10){
            $calculatedScores['orientrec'] = 49;
         }
         else if($D111 >= 8){
            $calculatedScores['orientrec'] = 47;
         }
         else if($D111 == 7){
            $calculatedScores['orientrec'] = 45;
         }
         else if($D111 == 6){
            $calculatedScores['orientrec'] = 43;
         }
         else if($D111 == 5){
            $calculatedScores['orientrec'] = 41;
         }
         else if($D111 == 4){
            $calculatedScores['orientrec'] = 40;
         }
         else if($D111 == 3){
            $calculatedScores['orientrec'] = 30;
         }
         else if($D111 == 2){
            $calculatedScores['orientrec'] = 20;
         }
         else if($D111 == 1){
            $calculatedScores['orientrec'] = 13;
         }
         else if($D111 == 0){
            $calculatedScores['orientrec'] = 0;
         }         
            
         if($D112 >= 11){
            $calculatedScores['affeng'] = 50;
         }
         else if($D112 >= 7){
            $calculatedScores['affeng'] = 49;
         }
         else if($D112 == 6){
            $calculatedScores['affeng'] = 45;
         }
         else if($D112 == 5){
            $calculatedScores['affeng'] = 43;
         }
         else if($D112 == 4){
            $calculatedScores['affeng'] = 39;
         }
         else if($D112 == 3){
            $calculatedScores['affeng'] = 28;
         }
         else if($D112 == 2){
            $calculatedScores['affeng'] = 17;
         }
         else if($D112 == 1){
            $calculatedScores['affeng'] = 11;
         }
         else if($D112 == 0){
            $calculatedScores['affeng'] = 0;
         }
         
         if($D113 >= 9){
            $calculatedScores['imitate'] = 50;
         }
         else if($D113 >= 8){
            $calculatedScores['imitate'] = 49;
         }
         else if($D113 == 7){
            $calculatedScores['imitate'] = 46;
         }
         else if($D113 == 6){
            $calculatedScores['imitate'] = 45;
         }
         else if($D113 == 5){
            $calculatedScores['imitate'] = 43;
         }
         else if($D113 == 4){
            $calculatedScores['imitate'] = 41;
         }
         else if($D113 == 3){
            $calculatedScores['imitate'] = 40;
         }
         else if($D113 == 2){
            $calculatedScores['imitate'] = 30;
         }
         else if($D113 == 1){
            $calculatedScores['imitate'] = 20;
         }
         else if($D113 == 0){
            $calculatedScores['imitate'] = 0;
         }
         
         
         if($D114 >= 6){
            $calculatedScores['express'] = 50;
         }
         else if($D114 == 5){
            $calculatedScores['express'] = 45;
         }
         else if($D114 == 4){
            $calculatedScores['express'] = 43;
         }
         else if($D114 == 3){
            $calculatedScores['express'] = 40;
         }
         else if($D114 == 2){
            $calculatedScores['express'] = 20;
         }
         else if($D114 == 1){
            $calculatedScores['express'] = 18;
         }
         else if($D114 == 0){
            $calculatedScores['express'] = 0;
         }
         
         if($D115 >= 7){
            $calculatedScores['senproc'] = 50;
         }
         else if($D115 == 6){
            $calculatedScores['senproc'] = 47;
         }
         else if($D115 == 5){
            $calculatedScores['senproc'] = 44;
         }
         else if($D115 == 4){
            $calculatedScores['senproc'] = 40;
         }
         else if($D115 == 3){
            $calculatedScores['senproc'] = 35;
         }
         else if($D115 == 2){
            $calculatedScores['senproc'] = 15;
         }
         else if($D115 == 1){
            $calculatedScores['senproc'] = 8;
         }
         else if($D115 ==  0){
            $calculatedScores['senproc'] = 0;
         }
         
         if($D116 >= 7){
            $calculatedScores['regpat'] = 50;
         }
         else if($D116 == 6){
            $calculatedScores['regpat'] = 48;
         }
         else if($D116 == 5){
            $calculatedScores['regpat'] = 47;
         }
         else if($D116 == 4){
            $calculatedScores['regpat'] = 46;
         }
         else if($D116 == 3){
            $calculatedScores['regpat'] = 45;
         }
         else if($D116 == 2){
            $calculatedScores['regpat'] = 42;
         }
         else if($D116 == 1){
            $calculatedScores['regpat'] = 40;
         }
         else if($D116 ==  0){
            $calculatedScores['regpat'] = 0;
         }
         
         if($D117 >= 4){
            $calculatedScores['react'] = 50;
         }
         else if($D117 == 3){
            $calculatedScores['react'] = 47;
         }
         else if($D117 == 2){
            $calculatedScores['react'] = 45;
         }
         else if($D117 == 1){
            $calculatedScores['react'] = 35;
         }
         else if($D117 == 0){
            $calculatedScores['react'] = 0;
         }
         
         if($D118 >= 11){
            $calculatedScores['repplay'] = 50;
         }
         else if($D118 >= 10){
            $calculatedScores['repplay'] = 48;
         }
         else if($D118 >= 9){
            $calculatedScores['repplay'] = 46;
         }
         else if($D118 == 8){
            $calculatedScores['repplay'] = 45;
         }
         else if($D118 == 7){
            $calculatedScores['repplay'] = 43;
         }
         else if($D118 == 6){
            $calculatedScores['repplay'] = 40;
         }
         else if($D118 == 5){
            $calculatedScores['repplay'] = 29;
         }
         else if($D118 == 4){
            $calculatedScores['repplay'] = 18;
         }
         else if($D118 == 3){
            $calculatedScores['repplay'] = 15;
         }
         else if($D118 == 2){
            $calculatedScores['repplay'] = 13;
         }
         else if($D118 == 1){
            $calculatedScores['repplay'] = 9;
         }
         else if($D118 == 0){
            $calculatedScores['repplay'] = 0;
         }
         
         
         $calculatedScores['soc_com_risk'] = ($calculatedScores['orientrec'] + $calculatedScores['affeng'] + $calculatedScores['imitate']
                                             + $calculatedScores['express'])/4.0;
         $calculatedScores['sen_reg_risk'] = ($calculatedScores['senproc'] + $calculatedScores['regpat'] + $calculatedScores['react']
                                             + $calculatedScores['repplay'])/4.0;
                                             
         $calculatedScores['risk_score'] = ($calculatedScores['soc_com_risk'] + $calculatedScores['sen_reg_risk'])/2.0;
         
         //print_r($calculatedScores);
         
         
         if($calculatedScores['risk_score'] == 0){
            $calculatedScores['percentile'] = 5;
         }
         else if($calculatedScores['risk_score'] <= 1){
            $calculatedScores['percentile'] = 12;
         }
         else if($calculatedScores['risk_score'] <= 1.13){
            $calculatedScores['percentile'] = 14;
         }
         else if($calculatedScores['risk_score'] <= 1.38){
            $calculatedScores['percentile'] = 17;
         }
         else if($calculatedScores['risk_score'] <= 1.63){
            $calculatedScores['percentile'] = 19;
         }
         else if($calculatedScores['risk_score'] <= 1.88){
            $calculatedScores['percentile'] = 20;
         }
         else if($calculatedScores['risk_score'] <= 2.13){
            $calculatedScores['percentile'] = 21;
         }
         else if($calculatedScores['risk_score'] <= 2.25){
            $calculatedScores['percentile'] = 22;
         }
         else if($calculatedScores['risk_score'] <= 2.38){
            $calculatedScores['percentile'] = 23;
         }
         else if($calculatedScores['risk_score'] <= 2.5){
            $calculatedScores['percentile'] = 27;
         }
         else if($calculatedScores['risk_score'] <= 2.63){
            $calculatedScores['percentile'] = 29;
         }
         else if($calculatedScores['risk_score'] <= 3){
            $calculatedScores['percentile'] = 30;
         }
         else if($calculatedScores['risk_score'] <= 3.25){
            $calculatedScores['percentile'] = 31;
         }
         else if($calculatedScores['risk_score'] <= 3.38){
            $calculatedScores['percentile'] = 32;
         }
         else if($calculatedScores['risk_score'] <= 3.5){
            $calculatedScores['percentile'] = 34;
         }
         else if($calculatedScores['risk_score'] <= 3.63){
            $calculatedScores['percentile'] = 35;
         }
         else if($calculatedScores['risk_score'] <= 3.75){
            $calculatedScores['percentile'] = 36;
         }
         else if($calculatedScores['risk_score'] <= 3.88){
            $calculatedScores['percentile'] = 38;
         }
         else if($calculatedScores['risk_score'] <= 4.25){
            $calculatedScores['percentile'] = 39;
         }
         else if($calculatedScores['risk_score'] <= 4.38){
            $calculatedScores['percentile'] = 42;
         }
         else if($calculatedScores['risk_score'] <= 4.63){
            $calculatedScores['percentile'] = 43;
         }
         else if($calculatedScores['risk_score'] <= 4.75){
            $calculatedScores['percentile'] = 44;
         }
         else if($calculatedScores['risk_score'] <= 4.88){
            $calculatedScores['percentile'] = 45;
         }
         else if($calculatedScores['risk_score'] <= 5){
            $calculatedScores['percentile'] = 46;
         }
         else if($calculatedScores['risk_score'] <= 5.13){
            $calculatedScores['percentile'] = 47;
         }
         else if($calculatedScores['risk_score'] <= 5.38){
            $calculatedScores['percentile'] = 48;
         }
         else if($calculatedScores['risk_score'] <= 5.5){
            $calculatedScores['percentile'] = 49;
         }
         else if($calculatedScores['risk_score'] <= 5.75){
            $calculatedScores['percentile'] = 50;
         }
         else if($calculatedScores['risk_score'] <= 5.88){
            $calculatedScores['percentile'] = 51;
         }
         else if($calculatedScores['risk_score'] <= 6){
            $calculatedScores['percentile'] = 52;
         }
         else if($calculatedScores['risk_score'] <= 6.13){
            $calculatedScores['percentile'] = 53;
         }
         else if($calculatedScores['risk_score'] <= 6.25){
            $calculatedScores['percentile'] = 54;
         }
         else if($calculatedScores['risk_score'] <= 6.38){
            $calculatedScores['percentile'] = 55;
         }
         else if($calculatedScores['risk_score'] <= 6.63){
            $calculatedScores['percentile'] = 56;
         }
         else if($calculatedScores['risk_score'] <= 6.88){
            $calculatedScores['percentile'] = 57;
         }
         else if($calculatedScores['risk_score'] <= 7){
            $calculatedScores['percentile'] = 58;
         }
         else if($calculatedScores['risk_score'] <= 7.13){
            $calculatedScores['percentile'] = 59;
         }
         else if($calculatedScores['risk_score'] <= 7.25){
            $calculatedScores['percentile'] = 60;
         }
         else if($calculatedScores['risk_score'] <= 7.38){
            $calculatedScores['percentile'] = 61;
         }
         else if($calculatedScores['risk_score'] <= 7.63){
            $calculatedScores['percentile'] = 62;
         }
         else if($calculatedScores['risk_score'] <= 7.88){
            $calculatedScores['percentile'] = 63;
         }
         else if($calculatedScores['risk_score'] <= 8){
            $calculatedScores['percentile'] = 64;
         }
         else if($calculatedScores['risk_score'] <= 8.13){
            $calculatedScores['percentile'] = 65;
         }
         else if($calculatedScores['risk_score'] <= 8.25){
            $calculatedScores['percentile'] = 66;
         }
         else if($calculatedScores['risk_score'] <= 8.5){
            $calculatedScores['percentile'] = 67;
         }
         else if($calculatedScores['risk_score'] <= 8.63){
            $calculatedScores['percentile'] = 68;
         }
         else if($calculatedScores['risk_score'] <= 8.88){
            $calculatedScores['percentile'] = 69;
         }
         else if($calculatedScores['risk_score'] <= 9){
            $calculatedScores['percentile'] = 70;
         }
         else if($calculatedScores['risk_score'] <= 9.25){
            $calculatedScores['percentile'] = 71;
         }
         else if($calculatedScores['risk_score'] <= 9.38){
            $calculatedScores['percentile'] = 72;
         }
         else if($calculatedScores['risk_score'] <= 9.63){
            $calculatedScores['percentile'] = 73;
         }
         else if($calculatedScores['risk_score'] <= 9.75){
            $calculatedScores['percentile'] = 74;
         }
         else if($calculatedScores['risk_score'] <= 10){
            $calculatedScores['percentile'] = 75;
         }
         else if($calculatedScores['risk_score'] <= 10.25){
            $calculatedScores['percentile'] = 76;
         }
         else if($calculatedScores['risk_score'] <= 10.38){
            $calculatedScores['percentile'] = 77;
         }
         else if($calculatedScores['risk_score'] <= 10.5){
            $calculatedScores['percentile'] = 78;
         }
         else if($calculatedScores['risk_score'] <= 10.75){
            $calculatedScores['percentile'] = 79;
         }
         else if($calculatedScores['risk_score'] <= 11){
            $calculatedScores['percentile'] = 80;
         }
         else if($calculatedScores['risk_score'] <= 11.25){
            $calculatedScores['percentile'] = 81;
         }
         else if($calculatedScores['risk_score'] <= 11.5){
            $calculatedScores['percentile'] = 82;
         }
         else if($calculatedScores['risk_score'] <= 11.88){
            $calculatedScores['percentile'] = 83;
         }
         else if($calculatedScores['risk_score'] <= 12.13){
            $calculatedScores['percentile'] = 84;
         }
         else if($calculatedScores['risk_score'] <= 12.38){
            $calculatedScores['percentile'] = 85;
         }
         else if($calculatedScores['risk_score'] <= 12.75){
            $calculatedScores['percentile'] = 86;
         }
         else if($calculatedScores['risk_score'] <= 13){
            $calculatedScores['percentile'] = 87;
         }
         else if($calculatedScores['risk_score'] <= 13.38){
            $calculatedScores['percentile'] = 88;
         }
         else if($calculatedScores['risk_score'] <= 13.75){
            $calculatedScores['percentile'] = 89;
         }
         else if($calculatedScores['risk_score'] <= 14.25){
            $calculatedScores['percentile'] = 90;
         }
         else if($calculatedScores['risk_score'] <= 14.63){
            $calculatedScores['percentile'] = 91;
         }
         else if($calculatedScores['risk_score'] <= 15){
            $calculatedScores['percentile'] = 92;
         }
         else if($calculatedScores['risk_score'] <= 15.88){
            $calculatedScores['percentile'] = 93;
         }
         else if($calculatedScores['risk_score'] <= 17){
            $calculatedScores['percentile'] = 94;
         }
         else if($calculatedScores['risk_score'] <= 17.75){
            $calculatedScores['percentile'] = 95;
         }
         else if($calculatedScores['risk_score'] <= 19){
            $calculatedScores['percentile'] = 96;
         }
         else if($calculatedScores['risk_score'] <= 20.5){
            $calculatedScores['percentile'] = 97;
         }
         else if($calculatedScores['risk_score'] <= 22.63){
            $calculatedScores['percentile'] = 98;
         }
         else if($calculatedScores['risk_score'] <= 26.25){
            $calculatedScores['percentile'] = 99;
         }
         else{
            $calculatedScores['percentile'] = 100;
         }
         
         // save the resultant total
         $result = $db->update($this->table, $calculatedScores, array('CommentID'=>$this->getCommentID()));
          ProjectUtility::SetSupplementalGrantStatus($this->getSessionID());
         #echo("D118: " . $D118);
         #echo("\nBDM: " . $BDM_total);
        // print_r($calculatedScores);
     }
}
?>
