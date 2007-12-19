<?php
class NDB_BVL_Instrument_vineland extends NDB_BVL_Instrument
{
    /**
    * sets up basic data, such as the HTML_Quickform object, and so on.
    *
    * @param string $commentID  the CommentID identifying the data to load
    * @param string $page       if a multipage form, the page to show
    * @return void
    * @access public
    */
    function _setup($commentID, $page){
        $this->formType="XIN";
        $this->form = new HTML_Quickform('test_form');
        $this->page = $page;            // page label (number or
        // string - used by
        // user-defined child classes)

        //         object properties now set in subclasses
        //        $this->testName = "vineland";           // test_names.Test_name
        //        $this->table = 'vineland';              // name of database table corresponding to instrument

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
        //        if(ereg("vineland(_page[0-9]+)",$this->page,$matches)){
        if(ereg("(_page[0-9]+)",$this->page,$matches)){
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
        $this->form->addElement('header', 'instrument_title', "Vineland II ABS - Survey Interview Form");

        // examiner & date of administration fields added separately, later
        //        $this->_addMetadataFields();

        //About the Individual
        $prefix = "about_";
        $this->form->addElement('header', null, "About the Individual");
        $this->form->addElement('header', null, "Please only complete the non-identifying fields allowed.");
        $this->form->addElement('static', null, "Name:");
        $this->form->addElement('static', null, "Sex:");
        $this->form->addElement('static', null, "ID:");
        $this->addTextElement("{$prefix}current_grade", "Grade (if applicable):");
        $this->addTextElement("{$prefix}highest_grade", "Highest Grade Completed (if applicable):");
        $this->form->addElement('static', null, "School or Other Facility (if applicable):");
        $this->addTextElement("{$prefix}present_classification", "Present Classification or Diagnosis:");
        $this->addTextElement("{$prefix}laguage", "Language Spoken at Home:");

        $this->form->addElement("static", null, "&nbsp;");
        $this->form->addElement("static", null, "Age:");
        $config =& NDB_Config::singleton();
        $dateOptions = array(
        'language' => 'en',
        'format'   => 'YMd',
        'minYear'  => $config->getSetting('startYear'),
        'maxYear'  => $config->getSetting('endYear'),
        'addEmptyOption' => true,
        'emptyOptionValue' => null
        );

        $this->form->addElement('date', 'Date_taken', $this->indent . 'Interview Date:', $dateOptions);
        $this->addTextElement("{$prefix}age_used", $this->indent . "Age Used for Starting Points:");
        $answerOptions = array(NULL=>"",
        "chronological"=>"Chronological",
        "mental"=>"Mental",
        "social"=>"Social",
        "not_answered"=>"Not Answered");
        $this->form->addElement("select", "{$prefix}age_type", $this->indent . "Type (select one):", $answerOptions);

        $this->form->addElement("static", null, "&nbsp;");
        $this->form->addElement("static", null, "Data from Other Tests:");
        $questionArray = array("intelligence"=>"Intelligence", "achievement"=>"Achievement", "adaptive"=>"Adaptive Behavior", "other"=>"Other");
        foreach ($questionArray as $field=>$label) {
            $this->addTextElement("{$prefix}data_$field", $this->indent . $label);
        }

        $this->addTextElement("{$prefix}reason", "Reason for the Interview:");

        $this->form->addElement("static", null, "&nbsp;");
        $this->form->addElement("static", null, "About the Respondent:");
        $this->form->addElement("static", null, $this->indent . "Name:");
        $this->form->addElement("select", "{$prefix}respondent_sex", $this->indent . "Sex:", array(null=>"", "male"=>"Male", "female"=>"Female", "not_answered"=>"Not Answered"));

        $this->form->addElement("static", null, $this->indent . "Telephone:");
        $this->addTextElement("{$prefix}respondent_relationship", $this->indent . "Relationship to Individual:");

        $this->form->addElement("static", null, "&nbsp;");
        $this->form->addElement("static", null, "About the Interviewer:");
        $examiners = $this->_getExaminerNames();
        $this->form->addElement('select', 'Examiner', $this->indent . 'Name:', $examiners);
        $this->addTextElement("{$prefix}interviewer_position", $this->indent . "Position:");
        $this->form->addElement("select", "{$prefix}interviewer_sex", $this->indent . "Sex:", array(null=>"", "male"=>"Male", "female"=>"Female", "not_answered"=>"Not Answered"));

        //        $this->form->addElement("");
        //        $this->form->addElement("{$prefix}", "");
        //
        //        $this->addTextElement("{$prefix}", "");

    }

    function _page1() {
        //Communication Domain - Receptive
        $this->form->addElement("header", null, "Communication Domain - Receptive");

        $prefix = "comm_receptive_";
        $questionArray  = array("1 Turns eyes and head toward sound.",
        "2 Looks toward parent or caregiver when hearing parent's or caregiver's voice.",
        "3 Responds to his or her name spoken.",
        "4 Demonstrates understanding of the meaning of no, or word or gesture with the same meaning.",
        "5 Demonstrates understanding of the meaning of yes, or word or gesture with the same meaning.",
        "6 Listens to story for at least 5 minutes.",
        "7 Points to at least three major body parts when asked.",
        "8 Points to common objects in a book or magazine as they are named.",
        "9 Listens to instructions.",
        "10 Follows instructions with one action and one object.",
        "11 Points to at least five minor body parts when asked.",
        "12 Follows instructions with two actions or an action and two objects.",
        "13 Follows instructions in 'if-then' form",
        "14 Listens to a story for at least 15 minutes.",
        "15 Listens to a story for at least 30 minutes.",
        "16 Follows three-part instructions.",
        "17 Follows instructions or directions heard 5 minutes before.",
        "18 Understands sayings that are not meant to be taken word for word.",
        "19 Listens to an informational talk for at least 15 minutes.",
        "20 Listens to an informational talk for at least 30 minutes.");

        //section breaks based on age
        $ageBreaks = array(1=>"<1", 4=>"1", 7=>"2", 11=>"3+");
        //questions that allow a `No Opportunity` response
        $noOpp = array();
        //questions that don't allow a `1_sometimes` response
        $not1 = array();

        //Build the section QuickForm questions
        $this->_generateSection($prefix, $questionArray, $ageBreaks, $noOpp, $not1);
    }

    function _page2() {
        //Communication Domain - Expressive
        $this->form->addElement("header", null, "Communication Domain - Expressive");

        $prefix = "comm_expressive_";
        $questionArray  = array("1 Cries or fusses when hungry or wet.",
        "2 Smiles when you smile at him or her.",
        "3 Makes sounds of pleasure.",
        "4 Makes nonword baby sounds (that is, babbles).",
        "5 Makes sounds or gestures.",
        "6 Makes sounds or gestures.",
        "7 Waves good-bye when another person waves or parent or caregiver tells him or her to wave.",
        "8 Says 'Da-da,' 'Ma-ma,' or another name for parent or caregiver.",
        "9 Points to object he or she wants that is out of reach.",
        "10 Points or gestures to indicate preference when offered a choice.",
        "11 Repeats or tries to repeat common words immediately upon hearing them.",
        "12 Names at least three objects.",
        "13 Says one-word requests.",
        "14 Uses first names or nicknames of brothers, sisters, or friends, or says their names when asked.",
        "15 Answers or tries to answer with words when asked a question.",
        "16 Names at least 10 objects.",
        "17 States own first name or nickname.",
        "18 Uses phrases with a noun and a verb.",
        "19 Asks questions by changing inflection of words or simple phrases.",
        "20 Says at least 50 recognizable words.",
        "21 Uses simple words to describe things.",
        "22 Asks questions beginning with what or where.",

        "23 Uses negatives in sentences.",
        "24 Tells about experiences in simple sentences.",
        "25 Says correct age when asked.",
        "26 Says at least 100 recognizable words.",
        "27 Uses in, on, or under in phrases or sentences.",
        "28 Uses and in phrases or sentences.",
        "29 Says first and last name when asked.",
        "30 Identifies and names most common colors.",
        "31 Asks questions beginning with who or why.",
        "32 Uses present tense verbs ending in `ing`.",
        "33 Uses possessives in phrases or sentences.",
        "34 Uses pronouns in phrases or sentences.",
        "35 Asks questions beginning with `when`.",
        "36 Uses regular past tense verbs.",
        "37 Uses behind or in front of in phrases or sentences.",
        "38 Pronounces words clearly without sound substitutions.",
        "39 Tells basic parts of a story, fairy tale, or television show plot.",
        "40 Says month and day of birthday when asked.",
        "41 Modulates tone of voice, volume, and rhythm appropriately.",

        "42 Tells about experiences in detail.",
        "43 Gives simple directions.",
        "44 Uses between in phrases or sentences.",
        "45 Says own telephone number when asked.",
        "46 Easily moves from one topic to another in conversation.",
        "47 Stays on topic in conversations; does not go off on tangents.",
        "48 Explains ideas in more than one way.",
        "49 Has conversations that last 10 minutes.",
        "50 Uses irregular plurals correctly.",
        "51 Says complete home address with or without zip code, when asked.",
        "52 Describesa short-term goal and what he or she needs to do to reach it.",
        "53 Gives complex directions to others.",
        "54 Describes a realistic long-range goal that can he done in 6 months or more 54.",
        );

        //section breaks based on age
        $ageBreaks = array(1=>"<1", 8=>"1", 20=>"2", 29=>"3", 33=>"4, 5", 40=>"6", 45=>"7+");
        //questions that allow a `No Opportunity` response
        $noOpp = array();
        //questions that don't allow a `1_sometimes` response
        $not1 = array();

        //Build the section QuickForm questions
        $this->_generateSection($prefix, $questionArray, $ageBreaks, $noOpp, $not1);
    }

    function _page3() {
        //Communication Domain - Written
        $this->form->addElement("header", null, "Communication Domain - Written");

        $prefix = "comm_written_";
        $questionArray  = array("1 Identifies one or more alphabet letters as letters and distinguishes them from numbers.",
        "2 Recognizes own name in printed form.",
        "3 Identifies at least 10 printed letters of the alphabet.",
        "4 Prints or writes using correct orientation.",
        "5 Copies own first name.",
        "6 Identifies all printed letters of the alphabet, upper- and lowercase.",
        "7 Prints at least three simple words from example.",
        "8 Prints or writes own first and last name from memory.",
        "9 Reads at least 10 words aloud.",
        "10 Prints at least 10 simple words from memory.",
        "11 Reads simple stories aloud.",
        "12 Prints simple setsentences of three or four words.",
        "13 Prints more than 20 words from memory; may make small spelling errors.",
        "14 Reads and understands material of at least second-grade level.",
        "15 Puts lists of words in alphabetical order.",
        "16 Writes simple correspondence at least three sentences long.",
        "17 Reads and understands material of at least fourth-grade level.",
        "18 Writes reports, papers, or essays at least one page long; may use computer.",
        "19 Writes complete mailing and return addresses on letters or packages.",
        "20 Reads and understands material of at least sixth-grade level.",
        "21 Edits or corrects own written work before handing it in.",
        "22 Writes advanced correspondence at least 10 sentences long; may use computer.",
        "23 Reads and understands material of at least ninth-grade level.",
        "24 Reads at least two newspaper articles weekly (print or electronic version).",
        "25 Writes business letters.");

        //section breaks based on age
        $ageBreaks = array(1=>"3-5", 8=>"6", 12=>"7, 8", 16=>"9+");
        //questions that allow a `No Opportunity` response
        $noOpp = array();
        //questions that don't allow a `1_sometimes` response
        $not1 = array();

        //Build the section QuickForm questions
        $this->_generateSection($prefix, $questionArray, $ageBreaks, $noOpp, $not1);
    }

    function _page4() {
        //Daily Living Skills Domain - Personal
        $this->form->addElement("header", null, "Daily Living Skills Domain - Personal");

        $prefix = "daily_personal_";
        $questionArray  = array("1 Opens mouth when food is offered.",
        "2 Eats solid foods.",
        "3 Sucks or chews on finger foods.",
        "4 Drinks from a cup or glass; may spill.",
        "5 Lets someone know when he or she has wet or soiled diaper or pants.",
        "6 Feeds self with spoon; may spill.",
        "7 Sucks from straw.",
        "8 Takes off clothing that opens in the front.",
        "9 Pulls up clothing wfth astic waistbands.",
        "10 Feeds self with fork; may spill.",
        "11 Drinks from a cup or glass without spilling.",
        "12 Feeds self with spoon without spilling.",
        "13 Urinates in toilet or potty chair.",
        "14 Puts on clothing that opens in the front. ",
        "15 Asked to use toilet.",
        "16 Defecates in toilet or potty chair. ",
        "17 It toilet-training during the day.",
        "18 Zips zippers that are fastened at the bottom.",
        "19 Wipes or blows nose using tissue or handkerchief.",
        "20 Is toilet-trained during the night.",
        "21 Puts shoes on correct feet; does not need to tie laces.",
        "22 Fastens snaps.",
        "23 Holds spoon, fork and knife correctly.",

        "24 Washes and dries face using soap and water.",
        "25 Brushes teeth.",
        "26 Buttons large buttons in front, in correct buttonholes.",
        "27 Covers mouth and nose when coughing and sneezing.",
        "28 Buttons small buttons in front, in correct buttonholes.",
        "29 Connects and zips zippers that are not fastened at the bottom .",
        "30 Turns faucets on and adjusts temperature by adding hot or cold water.",
        "31 Wears appropriate clothing during wet or cold weather.",
        "32 Bathes or showers and dries self.",
        "33 Finds and uses appropriate public restroom for his or her gender.",
        "34 Washes and dries hair.",
        "35 Cares for minor cuts.",
        "36 Takes medicine as directed.",
        "37 Uses thermometer to take own or another's temperature.",
        "38 Seeks medical help in an emergency.",
        "39 Follows directions for health care procedures, special diet, or medical treatments.",
        "40 Keeps track of medications (nonprescription and prescription) and refills them as needed.",
        "41 Makes appointments for regular medical and dental checkups.");

        //section breaks based on age
        $ageBreaks = array(1=>"<1", 4=>"1", 9=>"2", 13=>"3", 18=>"4", 25=>"5, 6", 32=>"7+");
        //questions that allow a `No Opportunity` response
        $noOpp = array(38, 39);
        //questions that don't allow a `1_sometimes` response
        $not1 = array();

        //Build the section QuickForm questions
        $this->_generateSection($prefix, $questionArray, $ageBreaks, $noOpp, $not1);
    }

    function _page5() {
        //Daily Living Skills Domain - Domestic
        $this->form->addElement("header", null, "Daily Living Skills Domain - Domestic");

        $prefix = "daily_domestic_";
        $questionArray  = array("1 Is careful around hot objects.",
        "2 Helps with simple household chores.",
        "3 Clears unbreakable items from own place at table.",
        "4 Cleans up play or work area at end of an activity.",
        "5 Puts away personal possessions.",
        "6 Is careful when using sharp objects.",
        "7 Clears breakable items from own place at table.",
        "8 Helps prepare foods that require mixing and cooking.",
        "9 Uses simple appliances.",
        "10 Uses microwave oven for heating, baking, or cooking.",
        "11 Puts clean clothes away in proper place.",
        "12 Uses tools.",
        "13 Washes dishes by hand, or loads and uses dishwasher.",
        "14 Sweeps, mops, or vacuums floors thoroughly.",
        "15 Clears table completely.",
        "16 Uses household products correctly.",
        "17 Prepares basic foods that do not need mixing but require cooking.",
        "18 Cleans one or more rooms other than own bedroom.",
        "19 Uses sharp knife to prepare food.",
        "20 Uses stove or oven for heating, baking, or cooking.",
        "21 Prepares food from ingredients that require measuring, mixing, and cooking.",
        "22 Washes clothing as needed.",
        "23 Performs maintenance tasks as needed.",
        "24 Plans and prepares main meal of the day."
        );

        //section breaks based on age
        $ageBreaks = array(1=>"1-6", 6=>"7-10", 12=>"11+");
        //questions that allow a `No Opportunity` response
        $noOpp = array(10);
        //questions that don't allow a `1_sometimes` response
        $not1 = array();

        //Build the section QuickForm questions
        $this->_generateSection($prefix, $questionArray, $ageBreaks, $noOpp, $not1);
    }

    function _page6() {
        //Daily Living Skills - Community
        $this->form->addElement("header", null, "Daily Living Skills - Community");

        $prefix = "daily_community_";
        $questionArray  = array("1 Demonstrates understanding of function of telephone.",
        "2 Talks to familiar person on telephone.",
        "3 Uses TV or radio without help.",
        "4 Counts at least 10 objects, one by one.",
        "5 Is aware of and demonstrates appropriate behavior while riding in car.",
        "6 Demonstrates understanding of the function of money.",
        "7 Uses sidewalk (where available) or shoulder of road when walking or using wheeled equipment.",
        "8 Demonstrates understanding of function of clock.",
        "9 Follows household rules.",
        "10 Demonstrates computer skills necessary to play games or start programs with computer turned on...",
        "11 Summons to the telephone the person receiving a call or indicates that the person is not available.",
        "12 Identifies penny, nickel, dime, and quarter by name when asked; does not need to know the value of coins.",
        "13 Looks both ways when crossing streets or roads.",
        "14 Says current day of the week when asked.",
        "15 Demonstrates understanding of right to personal privacy for self and others.",
        "16 Demonstrates knowledge of what phone number to call man emgency when asked.",
        "17 Tells time using a digital clock or watch.",
        "18 States value of penny, nickel, dime, and quarter.",
        "19 Discriminates between bills of different denominations.",
        "20 Obeys traffic lights and Walk and Don't Walk signs.",
        "21 Points to current or other date on calendar when asked.",
        "22 Demonstrates understanding that some items cost more than others.",
        "23 Tells time by the half hour on analog clock.",
        "24 Makes telephone calls to others, using standard or cell phone.",

        "25 Orders a complete meal in a fast-food restaurant.",
        "26 Carries or stores money safely.",
        "27 Tells time by 5-minute segments on analog clock.",
        "28 Obeys curfew parent or caregiver sets.",
        "29 Watches or listens to programs for information.",
        "30 Counts change from a purchase.",
        "31 Demonstrates computer skills necessary to carry out complex tasks.",
        "32 Evaluates quality and price when selecting items to purchase.",
        "33 Obeys time limits for breaks.",
        "34 Travels at least 5 to 10 miles to familiar destination.",
        "35 Demonstrates understanding of right to complain or report legitimate problems ...",
        "36 Notifies school or supervisor when he or she will be late or absent.",
        "37 Uses savings or checking account responsibly.",
        "38 Travels at least 5 to 10 miles to unfamiliar destination...",
        "39 Earns money at part-time job (that is, at least 10 hours a week) for 1 year.",
        "40 Attempts to improve job performance after receiving constructive criticism from supervisor.",
        "41 Manages own money.",
        "42 Has held full-time job for 1 year.",
        "43 Budgets for monthly expenses.",
        "44 Applies for and uses personal credit card responsibly.");

        //section breaks based on age
        $ageBreaks = array(1=>"1-3", 4=>"4", 8=>"5,6", 14=>"7", 18=>"8", 23=>"9-11", 26=>"12-15", 32=>"16+");
        //questions that allow a `No Opportunity` response
        $noOpp = array(3, 10, 25, 29, 31, 40);
        //questions that don't allow a `1_sometimes` response
        $not1 = array(39, 42);

        //Build the section QuickForm questions
        $this->_generateSection($prefix, $questionArray, $ageBreaks, $noOpp, $not1);
    }

    function _page7() {
        //Socialization Domain - Interpersonal Relationships
        $this->form->addElement("header", null, "Socialization Domain - Interpersonal Relationships");

        $prefix = "social_interpersonal_";
        $questionArray  = array("1 Looks at face of parent or caregiver.",
        "2 Watches (that is, follows with eyes) someone moving by crib or bed",
        "3 Shows two or more emotions.",
        "4 Smiles or makes sounds when approached by a familiar person.",
        "5 Makes or tries to make social contact.",
        "6 Reaches for familiar person when person holds out arms to him or her.",
        "7 Shows preference for certain people and objects.",
        "8 Shows affection to familiar persons.",
        "9 Imitates or tries to imitate parent's or caregiver's facial expressions",
        "10 Moves about looking for parent or caregiver or other familiar person nearby.",
        "11 Shows interest in children the same age, other than brothers or sisters.",
        "12 Imitates simple movements.",
        "13 Uses actions to show happiness or concern for others.",
        "14 Shows desire to please others.",
        "15 Demonstrates friendship-seeking behavior with others the same age.",
        "16 Imitates relatively complex actions as they are being performed by another person.",
        "17 Answers when familiar adults make small talk.",
        "18 Repeats phrases heard spoken before by an adult.",
        "19 Uses words to express own emotions.",
        "20 Has best friend or shows preference for certain friends (of either sex) over others.",
        "21 Imitates relatively complex actions several hours after watching someone else.",

        "22 Uses words to express happiness or concern for others.",
        "23 Acts when another person needs a helping hand.",
        "24 Recognizes the likes and dislikes of others.",
        "25 Shows same level of emotion as others around him or her.",
        "26 Keeps comfortable distance between self and others in social situations.",
        "27 Talks with others about shared interests.",
        "28 Starts small talk when meets people he or she knows.",
        "29 Meets with friends regularly.",
        "30 Chooses not to say embarrassing or mean things or ask rude questions in public.",
        "31 Places reasonable demands on friendship.",
        "32 Understands that others do not know his or her thoughts unless he or she says them.",
        "33 Is careful when talking about personal things.",
        "34 Cooperates with others to plan or be part of an activity.",
        "35 Demonstrates understanding of hints or indirect cues in conversation 35.",
        "36 Starts conversations by talking about things that interest others.",
        "37 Goes on group dates.",
        "38 Goes on single dates."
        );

        //section breaks based on age
        $ageBreaks = array(1=>"<1", 11=>"1, 2", 15=>"3, 4", 20=>"5", 24=>"6-8", 28=>"9+");
        //questions that allow a `No Opportunity` response
        $noOpp = array();
        //questions that don't allow a `1_sometimes` response
        $not1 = array();

        //Build the section QuickForm questions
        $this->_generateSection($prefix, $questionArray, $ageBreaks, $noOpp, $not1);
    }

    function _page8() {
        //Socialization Domain - Play and Leisure Time
        $this->form->addElement("header", null, "Socialization Domain - Play and Leisure Time");

        $prefix = "social_play_leisure_";
        $questionArray  = array("1 Responds when parent or caregiver is playful.",
        "2 Shows interest in where he or she is.",
        "3 Plays simple interaction games with others.",
        "4 Plays near another child, each doing different things.",
        "5 Chooses to play with other children.",
        "6 Plays cooperatively with one or more children for up to 5 minutes.",
        "7 Plays cooperatively with more than one child for more than 5 minutes.",
        "8 Continues playing with another child with little fussing when parent or caregiver leaves.",
        "9 Shares toys or possessions when asked.",
        "10 Plays with others with minimal supervision.",
        "11 Uses common household objects or other objects for make-believe activities.",
        "12 Protects self by moving away from those who destroy things or cause injury.",
        "13 Plays simple make-believe activities with others. -",
        "14 Seeks out others for play or companionship.",
        "15 Takes turns when asked while playing games or sports.",
        "16 Plays informal, outdoor group games.",
        "17 Shares toys or possessions without being asked.",
        "18 Follows rules in simple games.",
        "19 Takes turns without being asked.",
        "20 Plays simple card or board game based only on chance.",
        "21 Goes places with friends during the day with adult supervision.",
        "22 Asks permission before using objects belonging to or being used by another.",

        "23 Refrains from entering group when nonverbal cues indicate that he or she is not welcome.",
        "24 Plays simple games that require keeping score.",
        "25 Shows good sportsmanship.",
        "26 Plays more than one board, card, or electronic game requiring skill and decision making.",
        "27 Goes places with friends in evening with adult supervision.",
        "28 Follows rules in complex games or sports.",
        "29 Goes places with friends during the day without adult supervision.",
        "30 Plans fun activities with more than two things to be arranged.",
        "31 Goes places with friends in evening without adult supervision.");

        //section breaks based on age
        $ageBreaks = array(1=>"<1", 4=>"1,2", 9=>"3", 13=>"4", 18=>"5,6", 21=>"7-12", 25=>"13+");
        //questions that allow a `No Opportunity` response
        $noOpp = array();
        //questions that don't allow a `1_sometimes` response
        $not1 = array();

        //Build the section QuickForm questions
        $this->_generateSection($prefix, $questionArray, $ageBreaks, $noOpp, $not1);
    }

    function _page9() {
        //Socialization Domain - Coping Skills
        $this->form->addElement("header", null, "Socialization Domain - Coping Skills");

        $prefix = "social_coping_";
        $questionArray  = array("1 Changes easily from one at-home activity to another.",
        "2 Says 'thank you' when given something.",
        "3 Changes behavior depending on how well he or she knows another person.",
        "4 Chews with mouth closed.",
        "5 Says 'please' when asking for something.",
        "6 Ends conversations appropriately.",
        "7 Cleans or wipes face and hands during and/or after meals.",
        "8 Responds appropriately to reasonable changes in routine.",

        "9 Says that he or she is sorry for unintended mistakes.",
        "10 Chooses not to taunt, tease, or bully.",
        "11 Acts appropriately when introduced to strangers.",
        "12 Changes voice level depending on location or situation.",
        "13 Says he or she is sorry after hurting another's feelings.",
        "14 Refrains from talking with food in mouth.",
        "15 Talks with others without interrupting or being rude.",
        "16 Accepts helpful suggestions or solutions from others.",
        "17 Controls anger or hurt feelings when plans change for reason(s) that cannot be helped.",
        "18 Keeps secrets or confidences for longer than one day.",
        "19 Says he or she is sorry after making unintentional mistakes or errors in judgment.",
        "20 Shows understanding that gentle teasing with family and friends can be a form of humor or affection.",
        "21 Tells parent or caregiver about his or her plans.",
        "22 Chooses to avoid dangerous or risky activities.",
        "23 Controls anger or hurt feelings when he or she does not get his or her way.",
        "24 Follows through with arrangements.",
        "25 Stops or stays away from relationships or situations that are hurtful or dangerous.",
        "26 Controls anger or hurt feelings due to constructive criticism.",
        "27 Keeps secrets or confidences for as long as needed.",
        "28 Thinks about what could happen before making decisions.",
        "29 Is aware of potential danger and uses caution when encountering risky social situations.",
        "3O Shows respect for co-workers.");

        //section breaks based on age
        $ageBreaks = array(1=>"1-4", 5=>"5-7", 9=>"8", 16=>"9-12", 21=>"13+");
        //questions that allow a `No Opportunity` response
        $noOpp = array();
        //questions that don't allow a `1_sometimes` response
        $not1 = array();

        //Build the section QuickForm questions
        $this->_generateSection($prefix, $questionArray, $ageBreaks, $noOpp, $not1);
    }

    function _page10() {
        //Motor Skills Domain - Gross
        $this->form->addElement("header", null, "Motor Skills Domain - Gross");

        $prefix = "motor_gross_";
        $questionArray  = array("1 Holds head erect for at least 15 seconds when held upright - in parent's or caregiver's arms.",
        "2 Sits supported.",
        "3 Sits without support for at least 1 minute.",
        "4 Creeps or moves on stomach across floor.",
        "5 Sits without support for at least 10 minutes.",
        "6 Raises self to sitting position and sits without support for at least 1 minute.",
        "7 Crawls at least 5 feet on hands and knees, without stomach touching floor.",
        "8 Pulls self to standing position.",
        "9 Crawls up stairs.",
        "10 Takes at least two steps.",
        "11 Stands alone for ito 3 minutes.",
        "12 Rolls ball while sitting.",
        "13 Climbs on and off low objects.",
        "14 Crawls down stairs.",
        "15 Stands for at least 5 minutes.",
        "16 Walks across room; may be unsteady and fall occasionally.",
        "17 Throws ball.",
        "18 Walks to get around; does not need to hold on to anything.",
        "19 Climbs on and off adult-sized chair.",
        "20 Runs without falling; may be awkward and uncoordinated.",
        "21 Walks up stairs, putting both feet on each step; may use railing.",
        "22 Kicks ball.",
        "23 Runs smoothly without falling.",
        "24 Walks down stairs, facing forward, putting both feet on each step.",
        "25 Jumps with both feet off floor.",
        "26 Throws ball of any size in specific direction.",
        "27 Catches beach ball-sized ball with both hands frornadistance of 2 or3 feet.",
        "28 Walks up stairs, alternating feet; may use railing.",
        "29 Pedals tricycle or other three-wheeled toy for at least 6 feet.",
        "30 Jumps or hops forward at east three times.",
        "31 Hops on one foot at least once without falling; may hold on to something for balance.",
        "32 Climbs on and off high objects.",
        "33 Walks down stairs, alternating feet; may use railing.",
        "34 Runs smoothly, with changes in speed and direction.",
        "35 Rides bicycle with training wheels for at least 10 feet.",
        "36 Catches beach ball-sized ball (from at least 6 feet away) with both hands.",
        "37 Hops forward on one foot with ease.",
        "38 Skips at least 5 feet.",
        "39 Catches tennis or baseball-sized ball, moving to catch it if necessary.",
        "40 Rides bicycle with no training wheels without falling.");

        //section breaks based on age
        $ageBreaks = array(1=>"<1", 8=>"1", 17=>"2", 23=>"3", 31=>"4+");
        //questions that allow a `No Opportunity` response
        $noOpp = array(29, 35, 40);
        //questions that don't allow a `1_sometimes` response
        $not1 = array();

        //Build the section QuickForm questions
        $this->_generateSection($prefix, $questionArray, $ageBreaks, $noOpp, $not1);
    }

    function _page11() {
        //Motor Skills Domain - Fine
        $this->form->addElement("header", null, "Motor Skills Domain - Fine");

        $prefix = "motor_fine_";
        $questionArray  = array("1 Reaches for toy or object.",
        "2 Picks up small objects; may use both hands.",
        "3 Moves object from one hand to the other.",
        "4 Squeezes squeaky toy or object.",
        "5 Picks up small object with thumb and fingers.",
        "6 Removes object.",
        "7 Puts object.",
        "8 Turns pages of board, cloth, or paper book, one at a time.",
        "9 Stacks at least four small blocks or other small objects.",
        "10 Opens doors by turning doorknobs.",
        "11 Unwraps small objects.",
        "12 Completes simple puzzle of at least two pieces or shapes.",
        "13 Turns book or magazine pages one by one.",
        "14 Uses twisting hand-wrist motion.",
        "15 Holds pencil in proper position for writing or drawing.",
        "16 Colors simple shapes; may color outside lines.",
        "17 Builds three-dimensional structures.",
        "18 Opens and closes scissors with one hand.",
        "19 Glues or pastes two or more pieces together.",
        "20 Uses tape to hold things together.",
        "21 Draws more than one recognizable form.",
        "22 Makes recognizable letters or numbers.",
        "23 Draws circle freehand while looking at example.",
        "24 Uses scissors to cut across paper along a straight line.",
        "25 Colors simple shapes; colors inside the lines.",
        "26 Cuts out simple shapes.",
        "27 Uses eraser without tearing paper.",
        "28 Draws square freehand while looking at example.",
        "29 Draws triangle freehand while looking at example.",
        "30 lies knot.",
        "31 Draws straight line using a ruler or straightedge.",
        "32 Unlocks dead-bolt, key, or combination locks that require twisting.",
        "33 Cuts out complex shapes.",
        "34 Uses keyboard, typewriter, or touch screen to type name or short words.",
        "35 Ties secure bow.",
        "36 Uses a keyboard to type up to 10 lines; may look at the keys.");

        //section breaks based on age
        $ageBreaks = array(1=>"<1", 6=>"1,2", 9=>"3,4", 17=>"5", 26=>"6+");
        //questions that allow a `No Opportunity` response
        $noOpp = array(32, 34, 36);
        //questions that don't allow a `1_sometimes` response
        $not1 = array();

        //Build the section QuickForm questions
        $this->_generateSection($prefix, $questionArray, $ageBreaks, $noOpp, $not1);
    }

    function _page12() {
        //Maladaptive Behaviour Index - Internalizing
        $this->form->addElement("header", null, "Maladaptive Behaviour Index - Internalizing");

        $prefix = "maladaptive_internal_";
        $questionArray  = array("1 Is overly dependent.",
        "2 Avoids others and prefers to be alone.",
        "3 Has eating difficulties.",
        "4 Has sleep difficulties.",
        "5 Refuses to go to school or work because of fear, feelings of rejection or isolation, etc.",
        "6 Is overly anxious or nervous.",
        "7 Cries or laughs too easily.",
        "8 Has poor eye contact.",
        "9 Is sad for no clear reason.",
        "10 Avoids social interaction.",
        "11 Lacks energy or interest in life.");

        //section breaks based on age
        $ageBreaks = array(1=>"3+");
        //questions that allow a `No Opportunity` response
        $noOpp = array();
        //questions that don't allow a `1_sometimes` response
        $not1 = array();

        //Build the section QuickForm questions
        $this->_generateSection($prefix, $questionArray, $ageBreaks, $noOpp, $not1);


        //Maladaptive Behaviour Index - Externalizing
        $this->form->addElement("header", null, "Maladaptive Behaviour Index - Externalizing");

        $prefix = "maladaptive_external_";
        $questionArray  = array("1 Is impulsive.",
        "2 Has temper tantrums.",
        "3 ntionalIy disobeys and defies those in authority.",
        "4 Taunts, teases, or bullies.",
        "5 Is inconsiderate or insensitive to others.",
        "6 Lies, cheats, or steals.",
        "7 Is physically aggressive.",
        "8 Is stubborn or sullen.",
        "9 Says embarrassing things or asks embarrassing questions in public.",
        "10 Behaves inappropriately at the urging of others.");

        //section breaks based on age
        $ageBreaks = array(1=>"3+");
        //questions that allow a `No Opportunity` response
        $noOpp = array();
        //questions that don't allow a `1_sometimes` response
        $not1 = array();

        //Build the section QuickForm questions
        $this->_generateSection($prefix, $questionArray, $ageBreaks, $noOpp, $not1);
    }

    function _page13() {
        //Maladaptive Behaviour Index - Other
        $this->form->addElement("header", null, "Maladaptive Behaviour Index - Other");

        $prefix = "maladaptive_other_";
        $questionArray  = array("1 Sucks thumb or fingers.",
        "2 Wets bed or must wear diapers at night.",
        "3 Acts overly familiar with strangers.",
        "4 Bites fingernails.",
        "5 Has tics.",
        "6 Grinds teeth during the day or night.",
        "7 Has a hard time paying attentiun.",
        "8 Is more active or restless than others of same age.",
        "9 Uses school or work property...",
        "10 Swears.",
        "11 Runs away.",
        "12 Is truant from school or work.",
        "13 Ignores or doesn't pay attention to others around him or her.",
        "14 Uses money or gifts to 'buy' affection.",
        "15 Uses alcohol or illegal drugs during the school or work day.");

        //section breaks based on age
        $ageBreaks = array(1=>"3+");
        //questions that allow a `No Opportunity` response
        $noOpp = array();
        //questions that don't allow a `1_sometimes` response
        $not1 = array();

        //Build the section QuickForm questions
        $this->_generateSection($prefix, $questionArray, $ageBreaks, $noOpp, $not1);
    }

    function _page14() {
        //Maladaptive Behaviour Index - Critical Items
        $this->form->addElement("header", null, "Maladaptive Behaviour Index - Critical Items");

        $prefix = "maladaptive_critical_";
        $questionArray  = array("1 Engages in inappropriate sexual behavior.",
        "2 Is obsessed with objects or activities.",
        "3 Expresses thoughts that do not make sense.",
        "4 Has strange habits or ways.",
        "5 Consistently prefers objects to people.",
        "6 Displays behaviors that cause injury to self.",
        "7 Destroys own or another's possessions on purpose.",
        "8 Uses bizarre speech.",
        "9 Is unaware of what is happening around him or her.",
        "10 Rocks back and forth repeatedly.",
        "11 Is unusually fearful of ordinary sounds, objects, or situations.",
        "12 Remembers odd information in detail years later...",
        "13 Is unable to complete a normal school or work day because of chronic pain or fatigue.",
        "14 Is unable to complete a normal school or work day because of psychological symptoms");

        //section breaks based on age
        $ageBreaks = array(1=>"3+");
        //questions that allow a `No Opportunity` response
        $noOpp = array();
        //questions that don't allow a `1_sometimes` response
        $not1 = array();

        //Build the section QuickForm questions
        $this->_generateSection($prefix, $questionArray, $ageBreaks, $noOpp, $not1);
    }

    function _page15() {
        $prefix = "about_";
        $questionArray = array("respondents_estimate"=>"Respondent's Estimate of the Individual's Functioning:",
        "language"=>"Language Used in the Interview:",
        "special_characteristics"=>"Special Characteristics of the Individual:",
        "estimate_rapport"=>"Estimate of the Rapport Established with the Respondent:",
        "estimate_accuracy"=>"Estimate of the Respondent's Accuracy:",
        "general_observations"=>"General Observations:");

        $this->form->addElement("header", null, "About the Interview:");

        foreach($questionArray as $field=>$label) {
            $group[]=&$this->form->createElement("textarea", "{$prefix}$field", $label, array('cols'=>60, 'rows'=>6));
            $group[]=&$this->form->createElement("select", "{$prefix}$field" . "_status", "", array(NULL=>'', 'not_answered'=>'Not Answered'));
            $this->form->addGroup($group, "{$prefix}$field" . '_group', $label, null, false);
            unset($group);
            $rules_array=array("{$prefix}$field" . '_status{@}=={@}');
            $this->XINRegisterRule("{$prefix}$field", $rules_array, "Please record observations, or mark it as 'Not Answered'.", "{$prefix}$field" . '_group');

            $this->form->addElement("static", null, "&nbsp;");

        }
    }

    // General form of the function used to create each page...
    //    function _page() {
    //        //Domain -
    //        $this->form->addElement("header", null, " Domain - ");
    //
    //        $prefix = "_";
    //        $questionArray  = array(
    //        );
    //
    //        //section breaks based on age
    //        $ageBreaks = array();
    //        //questions that allow a `No Opportunity` response
    //        $noOpp = array();
    //        //questions that don't allow a `1_sometimes` response
    //        $not1 = array();
    //
    //        //Build the section QuickForm questions
    //        $this->_generateSection($prefix, $questionArray, $ageBreaks, $noOpp, $not1);
    //    }

    /**
    * Constructs a section (page) of the instrument in a uniform fashion.
    *
    * @param string $prefix Prefix used to identify this section.
    * @param array $questionArray 0-based array containing the text of all section questions.
    * @param array $ageBreaks Suggested age-based start points. 
    * @param array $noOpp Questions where a `No Opportunity` option is presented.
    * @param array $not1 Questions that don't allow the `1) Sometimes` option.
    */
    function _generateSection($prefix, $questionArray, $ageBreaks, $noOpp, $not1) {
        foreach($questionArray as $number=>$label) {
            $answerArray = array(""=>NULL, "2_usually"=>"2) Usually", "1_sometimes"=>"1) Sometimes", "0_never"=>"0) Never", "dont_know"=>"Don't know", "not_answered"=>"Not Answered");
            //$questionArray is 0-indexed, so we add 1 to get the true question number
            if (array_key_exists($number + 1, $ageBreaks)) {
                $this->form->addElement("header", null, $ageBreaks[$number + 1] . " ->");
            }
            if(in_array($number + 1, $noOpp)) {
                $answerArray += array("no_opportunity"=>"No Opportunity");
            }
            if(in_array($number + 1, $not1)) {
                unset($answerArray["1_sometimes"]);
            }
            $this->form->addElement("select", $prefix . ($number + 1), $this->indent . $label, $answerArray);
            
            //Due to age of child, most questions will go unanswered.
            //For now, no question after the first page (except section comments) is required.
            $this->XINRegisterRule($prefix . ($number + 1), array("Examiner{@}=={@}Pee Wee Herman"));
        }

        $this->form->addElement("static", null, "&nbsp;");

        $group[]=&$this->form->createElement("textarea", "{$prefix}comments", null, array('cols'=>60, 'rows'=>6));
        $group[]=&$this->form->createElement("select", "{$prefix}comments" . "_status", "", array(NULL=>'', 'not_answered'=>'Not Answered'));
        $this->form->addGroup($group, "{$prefix}comments" . '_group', "Comments", null, false);
        unset($group);
        $rules_array=array("{$prefix}comments" . '_status{@}=={@}');
        $this->XINRegisterRule("{$prefix}comments", $rules_array, "Please record this section's comments, or mark it as 'Not Answered'.", "{$prefix}comments" . '_group');
    }

}
?>