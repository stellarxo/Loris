<?php
class NDB_BVL_Instrument_fyi extends NDB_BVL_Instrument
{
/*
INSERT INTO test_names VALUES ('', 'fyi', 'First Year Inventory', '0', '1');
INSERT INTO instrument_subtests VALUES('', 'fyi', 'fyi_page1', '#1-#46', 1);
INSERT INTO instrument_subtests VALUES('', 'fyi', 'fyi_page2', '#47-#63', 2);
*/
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
        if(ereg("fyi(_page[0-9]+)",$this->page,$matches)){
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
        
        $this->addTextElement("mother_highest_grade", "Mother's highest grade completed or degree obtained:");
        
        
        $this->form->addElement("select", "father_ethnicity", "Baby's Father Race/Ethnicity (check 1 or more)", array(null=>"", "white"=>"White",
        "black_african_american"=>"Black/African-American",
        "hispanic_latino"=>"Hispanic/Latino",
        "asian"=>"Asian",
        "american_indian_alaskan_native"=>"American-Indian/Alaskan Native",
        "native_hawaiian_pacific_islander"=>"Native Hawaiian/Pacific Islander",
        "not_answered"=>"Not Answered"), "multiple");
        
        $this->addTextElement("father_highest_grade", "Father's highest grade completed or degree obtained:");
        
        $this->form->addElement("select", "person_filling_out", "The person filling out this form is the (check one):", array(null=>"", "mother"=>"Mother", "father"=>"Father", "both"=>"Both", "other"=>"Other (specify):", "not_answered"=>"Not Answered"));
        $this->addTextElement("person_filling_out_specify", $this->indent . "Specify:", array("person_filling_out{@}=={@}other"), "Please specify.");
        
    }
   
    function _page1(){
        $this->form->addElement("header", null, "Please check the ONE BOX...");
        $questionArray = array("1. Does your baby turn to look at you when you call your baby's name?",
                    "2. Does your baby seem bothered by loud sounds?",
                    "3. Does your baby seem overly sensitive to your touch (for xampl, fuss or pull away when you touch him or her)?",
                    "4. During familiar games like 'I'm gonna get you,? does your baby get excited because he or she knows what will happen next?",
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
                    "38. Dues your baby communicate with you by using his or her finger to point at objects or picturesf",
                    "39. Do you get the feeling that your baby plays or communicates with you less now than in the past?",
                    "40. Do your baby's eyes line up together when looking at an object?",
                    "41. Are your baby's feeding patterns regular from day to dayf",
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
        $this->form->addElement("header", null, "For the following questions, please cirlce the ONE ANSWER that best describes your baby:");
        
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
}
?>