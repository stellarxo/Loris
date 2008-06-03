<?php
class NDB_BVL_Instrument_macarthur_words_gestures extends NDB_BVL_Instrument
{
    /*
    INSERT INTO test_names VALUES ('', 'macarthur_words_gestures', 'MacArthur CDI - Words & Gestures', '0', '1');
    INSERT INTO instrument_subtests VALUES('', 'macarthur_words_gestures', 'macarthur_words_gestures_page1', 'Part I', 1);
    INSERT INTO instrument_subtests VALUES('', 'macarthur_words_gestures', 'macarthur_words_gestures_page2', 'D. VOCABULARY 1-3', 2);
    INSERT INTO instrument_subtests VALUES('', 'macarthur_words_gestures', 'macarthur_words_gestures_page3', 'D. VOCABULARY 4-7', 3);
    INSERT INTO instrument_subtests VALUES('', 'macarthur_words_gestures', 'macarthur_words_gestures_page4', 'D. VOCABULARY 8-10', 4);
    INSERT INTO instrument_subtests VALUES('', 'macarthur_words_gestures', 'macarthur_words_gestures_page5', 'D. VOCABULARY 11-13', 5);
    INSERT INTO instrument_subtests VALUES('', 'macarthur_words_gestures', 'macarthur_words_gestures_page6', 'D. VOCABULARY 14-19', 6);
    INSERT INTO instrument_subtests VALUES('', 'macarthur_words_gestures', 'macarthur_words_gestures_page7', 'Part II', 7);
    INSERT INTO test_battery VALUES ('', 'macarthur_words_gestures', '1050', '1140', 'Y', 'Visit', '2');
    */
    
    //answers to often asked questions
    var $yesNo = array(''=>null, 'yes'=>"Yes", 'no'=>"No", 'not_answered'=>"Not Answered");
    var $neverSomeOften = array(''=>null, 'never'=>"Never", 'sometimes'=>"Sometimes", 'often'=>"Often", 'not_answered'=>"Not Answered");
    var $underSays = array(''=>null, 'understands'=>"Understands", "says_and_understands"=>"Says and Understands", 'not_answered'=>"Not Answered");

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
        $this->testName = "macarthur_words_gestures";           // test_names.Test_name
        $this->table = 'macarthur_words_gestures';              // name of database table corresponding to instrument
        // data keyed by commentID
        $this->commentID = $commentID;

        //The array of dates/timestamps to convert to database dates/timestamps
        //Any HTML_Quickform date elements must be listed here
        $this->dateTimeFields=array("Date_taken");

        //The array of selects with multiple answers allowed
        //Any HTML_Quickform multiple selects must be listed here
        $this->_selectMultipleElements = array();

        // required fields for data entry completion status
        $this->_requiredElements = array('Examiner', 'I_A_1', "II_A_1");

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
        if(ereg("macarthur_words_gestures(_page[0-9]+)",$this->page,$matches)){
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
        $this->form->addElement('header', 'instrument_title', "MacArthur Communicative Development Inventory - Words & Gestures");

        // automatically adds examiner & date of administration
        $this->_addMetadataFields();

    }

    function _page1(){

        $this->form->addElement('header', null, "PART I EARLY WORDS");

        $this->form->addElement('header', null, "A. FIRST SIGNS OF UNDERSTANDING");

        $this->form->addElement('select', "I_A_1", "1. Respond when name is called (e.g., by turning and looking at source).", $this->yesNo);
        $this->form->addElement('select', "I_A_2", "2. Respond to `no no` (by stopping what he/she is doing, at least for a moment).", $this->yesNo);
        $this->form->addElement('select', "I_A_3", "3. React to `there's mommy/daddy` by looking around for them.", $this->yesNo);

        $this->form->addElement('header', null, "B. PHRASES (28)");
        $this->form->addElement('static', null, "In the list below, please mark the phrases that your child seems to understand.");
        $questionArray = array("Are you hungry?",
        "Are you tired/sleepy?",
        "Be careful.",
        "Be quiet.",
        "Clap your hands.",
        "Change diaper.",
        "Come here/come on.",
        "Daddy's/mommy's home.",
        "Do you want more?",
        "Don't do that.",
        "Don't touch.",
        "Get up.",
        "Give it to mommy.",
        "Give me a hug.",
        "Give me a kiss.",
        "Go get __.",
        "Good girl/boy.",
        "Hold still.",
        "Let's go bye bye.",
        "Look/look here.",
        "Open your mouth.",
        "Sit down.",
        "Spit it out.",
        "Stop it.",
        "Time to go night night.",
        "Throw the ball.",
        "This little piggy.",
        "Want to go for a ride?");
        $qNum = 1;
        foreach($questionArray as $label) {
            $this->form->addElement('advcheckbox', "I_B_" . $qNum, $label, null, null, array(null, "understands"));
            $this->XINRegisterRule("I_B_" . $qNum, array("I_B_" . $qNum . "{@}=={@}NEVER_REQUIRED"));
            $qNum++;
        }

        $this->form->addElement('header', null, "C. STARTING TO TALK");
        $this->form->addElement('select', "I_C_1", "1. Some children like to `parrot` or imitate things...", $this->neverSomeOften);
        $this->form->addElement('select', "I_C_2", "2. Some children like to go around naming or labeling things", $this->neverSomeOften);
    }

    function _page2(){
        $this->form->addElement('header', null, "D. VOCABULARY CHECKLIST");
        $this->form->addElement('static', null, "The following is a list of typical words...");
        $this->form->addElement('static', null, "<BR>");
        $this->form->addElement('static', null, "Leave any vocabulary questions blank if not answered.");

        $this->form->addElement('header', null, "1. SOUND EFFECTS AND ANIMAL SOUNDS (12)");
        $questionArray = array("baa baa",
        "choo choo",
        "cockadoodledoo",
        "grrr",
        "meow",
        "moo",
        "ouch",
        "quack quack",
        "uh oh",
        "vroom",
        "woof woof",
        "yum yum");
        $qNum = 1;
        foreach($questionArray as $label) {
            $this->form->addElement('select', "I_D_1_" . $qNum, $label, $this->underSays);
            $this->XINRegisterRule("I_D_1_" . $qNum, array("I_D_1_" . $qNum . "{@}=={@}NEVER_REQUIRED"));
            $qNum++;
        }

        $this->form->addElement('header', null, "2. ANIMALS NAMES (Real or Toy) (36)");
        $questionArray = array("animal",
        "bear",
        "bee",
        "bird",
        "bug",
        "bunny",
        "butterfly",
        "cat",
        "chicken",
        "cow",
        "deer",
        "dog",
        "donkey",
        "duck",
        "elephant",
        "fish",
        "frog",
        "giraffe",
        "goose",
        "horse",
        "kitty",
        "lamb",
        "lion",
        "monkey",
        "mouse",
        "owl",
        "penguin",
        "pig",
        "pony",
        "puppy",
        "sheep",
        "squirrel",
        "teddy bear",
        "tiger",
        "turkey",
        "turtle");
        $qNum = 1;
        foreach($questionArray as $label) {
            $this->form->addElement('select', "I_D_2_" . $qNum, $label, $this->underSays);
            $this->XINRegisterRule("I_D_2_" . $qNum, array("I_D_2_" . $qNum . "{@}=={@}NEVER_REQUIRED"));
            $qNum++;
        }

        $this->form->addElement('header', null, "3. VEHICLES (Real or Toy) (9)");
        $questionArray = array("airplane",
        "bicycle",
        "bus",
        "car",
        "firetruck",
        "motorcycle",
        "stroller",
        "train",
        "truck");
        $qNum = 1;
        foreach($questionArray as $label) {
            $this->form->addElement('select', "I_D_3_" . $qNum, $label, $this->underSays);
            $this->XINRegisterRule("I_D_3_" . $qNum, array("I_D_3_" . $qNum . "{@}=={@}NEVER_REQUIRED"));
            $qNum++;
        }
    }

    function _page3() {
        $this->form->addElement('header', null, "4. TOYS (8)");
        $questionArray = array("ball",
        "balloon",
        "block",
        "book",
        "bubbles",
        "doll",
        "pen",
        "toy");
        $qNum = 1;
        foreach($questionArray as $label) {
            $this->form->addElement('select', "I_D_4_" . $qNum, $label, $this->underSays);
            $this->XINRegisterRule("I_D_4_" . $qNum, array("I_D_4_" . $qNum . "{@}=={@}NEVER_REQUIRED"));
            $qNum++;
        }

        $this->form->addElement('header', null, "5. FOOD AND DRINK (30)");
        $questionArray = array("apple",
        "banana",
        "bread",
        "butter",
        "cake",
        "candy",
        "carrots",
        "cereal",
        "cheerios",
        "cheese",
        "chicken",
        "coffee",
        "cookie",
        "cracker",
        "drink",
        "egg",
        "fish",
        "food",
        "ice cream",
        "juice",
        "meat",
        "milk",
        "noodles",
        "orange",
        "peas",
        "pizza",
        "raisin",
        "spaghetti",
        "toast",
        "water");
        $qNum = 1;
        foreach($questionArray as $label) {
            $this->form->addElement('select', "I_D_5_" . $qNum, $label, $this->underSays);
            $this->XINRegisterRule("I_D_5_" . $qNum, array("I_D_5_" . $qNum . "{@}=={@}NEVER_REQUIRED"));
            $qNum++;
        }

        $this->form->addElement('header', null, "6. CLOTHING (19)");
        $questionArray = array("beads",
        "bib",
        "boots",
        "button",
        "coat",
        "diaper",
        "dress",
        "hat",
        "jacket",
        "jeans",
        "necklace",
        "pajamas",
        "pants",
        "shirt",
        "shoe",
        "shorts",
        "sock",
        "sweater",
        "zipper");
        $qNum = 1;
        foreach($questionArray as $label) {
            $this->form->addElement('select', "I_D_6_" . $qNum, $label, $this->underSays);
            $this->XINRegisterRule("I_D_6_" . $qNum, array("I_D_6_" . $qNum . "{@}=={@}NEVER_REQUIRED"));
            $qNum++;
        }

        $this->form->addElement('header', null, "7. BODY PARTS (20)");
        $questionArray = array("arm",
        "belly button",
        "cheek",
        "ear",
        "eye",
        "face",
        "foot",
        "finger",
        "hair",
        "hand",
        "head",
        "knee",
        "leg",
        "mouth",
        "nose",
        "owie/boo boo",
        "tooth",
        "toe",
        "tongue",
        "tummy");
        $qNum = 1;
        foreach($questionArray as $label) {
            $this->form->addElement('select', "I_D_7_" . $qNum, $label, $this->underSays);
            $this->XINRegisterRule("I_D_7_" . $qNum, array("I_D_7_" . $qNum . "{@}=={@}NEVER_REQUIRED"));
            $qNum++;
        }
    }

    function _page4() {
        $this->form->addElement('header', null, "8. FURNITURE AND ROOMS (24)");
        $questionArray = array("bathroom",
        "bathtub",
        "bed",
        "bedroom",
        "chair",
        "couch",
        "crib",
        "door",
        "drawer",
        "garage",
        "high chair",
        "kitchen",
        "living room",
        "oven",
        "play pen",
        "potty",
        "refrigerator",
        "rocking chair",
        "sink",
        "stairs",
        "stove",
        "table",
        "TV",
        "window");
        $qNum = 1;
        foreach($questionArray as $label) {
            $this->form->addElement('select', "I_D_8_" . $qNum, $label, $this->underSays);
            $this->XINRegisterRule("I_D_8_" . $qNum, array("I_D_8_" . $qNum . "{@}=={@}NEVER_REQUIRED"));
            $qNum++;
        }

        $this->form->addElement('header', null, "9. SMALL HOUSEHOLD ITEMS (36)");
        $questionArray = array("blanket",
        "bottle",
        "bowl",
        "box",
        "broom",
        "brush",
        "clock",
        "comb",
        "cup",
        "dish",
        "fork",
        "glass",
        "glasses",
        "hammer",
        "keys",
        "lamp",
        "light",
        "medicine",
        "money",
        "paper",
        "penny",
        "picture",
        "pillow",
        "plant",
        "plate",
        "purse",
        "radio",
        "scissors",
        "soap",
        "spoon",
        "telephone",
        "toothbrush",
        "towel",
        "trash",
        "vacuum",
        "watch");
        $qNum = 1;
        foreach($questionArray as $label) {
            $this->form->addElement('select', "I_D_9_" . $qNum, $label, $this->underSays);
            $this->XINRegisterRule("I_D_9_" . $qNum, array("I_D_9_" . $qNum . "{@}=={@}NEVER_REQUIRED"));
            $qNum++;
        }

        $this->form->addElement('header', null, "10. OUTSIDE THINGS AND PLACES TO GO (27)");
        $questionArray = array("backyard",
        "beach",
        "church*",
        "flower",
        "garden",
        "home",
        "house",
        "moon",
        "outside",
        "park",
        "party",
        "pool",
        "rain",
        "rock",
        "school",
        "shovel",
        "sky",
        "slide",
        "snow",
        "star",
        "store",
        "sun",
        "swing",
        "tree",
        "water",
        "work",
        "zoo");
        $qNum = 1;
        foreach($questionArray as $label) {
            $this->form->addElement('select', "I_D_10_" . $qNum, $label, $this->underSays);
            $this->XINRegisterRule("I_D_10_" . $qNum, array("I_D_10_" . $qNum . "{@}=={@}NEVER_REQUIRED"));
            $qNum++;
        }
        $this->form->addElement("static", null, "* or word used in your family");
    }

    function _page5(){
        $this->form->addElement('header', null, "11. PEOPLE (20)");
        $questionArray = array("aunt",
        "baby",
        "babysitter",
        "babysitter's name",
        "boy",
        "brother",
        "child",
        "daddy*",
        "girl",
        "grandma",
        "grandpa",
        "lady",
        "man",
        "mommy*",
        "child's own name",
        "people",
        "person",
        "sister",
        "teacher",
        "uncle");
        $qNum = 1;
        foreach($questionArray as $label) {
            $this->form->addElement('select', "I_D_11_" . $qNum, $label, $this->underSays);
            $this->XINRegisterRule("I_D_11_" . $qNum, array("I_D_11_" . $qNum . "{@}=={@}NEVER_REQUIRED"));
            $qNum++;
        }

        $this->form->addElement('header', null, "12. GAMES AND ROUTINES (19)");
        $questionArray = array("bath",
        "breakfast",
        "bye or bye bye",
        "dinner",
        "don't please",
        "hello",
        "hi",
        "lunch",
        "nap",
        "night night",
        "no",
        "patty cake",
        "peekaboo",
        "please",
        "shh/shush/hush",
        "thank you",
        "wait",
        "wanna/want to",
        "yes");
        $qNum = 1;
        foreach($questionArray as $label) {
            $this->form->addElement('select', "I_D_12_" . $qNum, $label, $this->underSays);
            $this->XINRegisterRule("I_D_12_" . $qNum, array("I_D_12_" . $qNum . "{@}=={@}NEVER_REQUIRED"));
            $qNum++;
        }

        $this->form->addElement('header', null, "13. ACTION WORDS (55)");
        $questionArray = array("bite",
        "blow",
        "break",
        "bring",
        "bump",
        "clean",
        "close",
        "cry",
        "dance",
        "draw",
        "drink",
        "drive",
        "eat",
        "fall",
        "feed",
        "finish",
        "get",
        "give",
        "go",
        "help",
        "hit",
        "hug",
        "hurry",
        "jump",
        "kick",
        "kiss",
        "look",
        "love",
        "open",
        "play",
        "pull",
        "push",
        "put",
        "read",
        "ride",
        "run",
        "say",
        "see",
        "show",
        "sing",
        "sleep",
        "smile",
        "splash",
        "stop",
        "swim",
        "swing",
        "take",
        "throw",
        "tickle",
        "touch",
        "watch",
        "walk",
        "wash",
        "wipe",
        "write");
        $qNum = 1;
        foreach($questionArray as $label) {
            $this->form->addElement('select', "I_D_13_" . $qNum, $label, $this->underSays);
            $this->XINRegisterRule("I_D_13_" . $qNum, array("I_D_13_" . $qNum . "{@}=={@}NEVER_REQUIRED"));
            $qNum++;
        }
    }

    function _page6() {
        $this->form->addElement('header', null, "14. WORDS ABOUT TIME (8)");
        $questionArray = array("day",
        "later",
        "morning",
        "night",
        "now",
        "today",
        "tomorrow",
        "tonight");
        $qNum = 1;
        foreach($questionArray as $label) {
            $this->form->addElement('select', "I_D_14_" . $qNum, $label, $this->underSays);
            $this->XINRegisterRule("I_D_14_" . $qNum, array("I_D_14_" . $qNum . "{@}=={@}NEVER_REQUIRED"));
            $qNum++;
        }

        $this->form->addElement('header', null, "15. DESCRIPTIVE WORDS (37)");
        $questionArray = array("all gone",
        "asleep",
        "bad",
        "big",
        "blue",
        "broken",
        "careful",
        "clean",
        "cold",
        "cute",
        "dark",
        "dirty",
        "dry",
        "empty",
        "fast",
        "fine",
        "gentle",
        "good",
        "happy",
        "hard",
        "hot",
        "hungry",
        "hurt",
        "little",
        "naughty",
        "nice",
        "old",
        "pretty",
        "red",
        "scared",
        "sick",
        "sleepy",
        "soft",
        "thirsty",
        "tired",
        "wet",
        "yucky");
        $qNum = 1;
        foreach($questionArray as $label) {
            $this->form->addElement('select', "I_D_15_" . $qNum, $label, $this->underSays);
            $this->XINRegisterRule("I_D_15_" . $qNum, array("I_D_15_" . $qNum . "{@}=={@}NEVER_REQUIRED"));
            $qNum++;
        }

        $this->form->addElement('header', null, "16. PRONOUNS (11)");
        $questionArray = array("his",
        "her",
        "I",
        "it",
        "me",
        "mine",
        "my",
        "that",
        "this",
        "you",
        "your");
        $qNum = 1;
        foreach($questionArray as $label) {
            $this->form->addElement('select', "I_D_16_" . $qNum, $label, $this->underSays);
            $this->XINRegisterRule("I_D_16_" . $qNum, array("I_D_16_" . $qNum . "{@}=={@}NEVER_REQUIRED"));
            $qNum++;
        }

        $this->form->addElement('header', null, "17. QUESTION WORDS (6)");
        $questionArray = array("how",
        "what",
        "when",
        "where",
        "who",
        "why");
        $qNum = 1;
        foreach($questionArray as $label) {
            $this->form->addElement('select', "I_D_17_" . $qNum, $label, $this->underSays);
            $this->XINRegisterRule("I_D_17_" . $qNum, array("I_D_17_" . $qNum . "{@}=={@}NEVER_REQUIRED"));
            $qNum++;
        }

        $this->form->addElement('header', null, "18. PREPOSITIONS AND LOCATION (11)");
        $questionArray = array("away",
        "back",
        "down",
        "in",
        "inside",
        "off",
        "on",
        "out",
        "there",
        "under",
        "up");
        $qNum = 1;
        foreach($questionArray as $label) {
            $this->form->addElement('select', "I_D_18_" . $qNum, $label, $this->underSays);
            $this->XINRegisterRule("I_D_18_" . $qNum, array("I_D_18_" . $qNum . "{@}=={@}NEVER_REQUIRED"));
            $qNum++;
        }

        $this->form->addElement('header', null, "19. QUANTIFIERS (8)");
        $questionArray = array("all",
        "another",
        "more",
        "none",
        "not",
        "other",
        "same",
        "some");
        $qNum = 1;
        foreach($questionArray as $label) {
            $this->form->addElement('select', "I_D_19_" . $qNum, $label, $this->underSays);
            $this->XINRegisterRule("I_D_19_" . $qNum, array("I_D_19_" . $qNum . "{@}=={@}NEVER_REQUIRED"));
            $qNum++;
        }
    }

    function _page7() {
        $this->form->addElement('header', null, "PART II ACTIONS AND GESTURES");

        $this->form->addElement('header', null, "A. FIRST COMMUNICATIVE GESTURES");
        $questionArray = array("1. Extends arm to show you something he/she is holding.",
        "2. Reaches out and gives you a toy or some object that he/she is holding.",
        "3. Points (with arm and index finger extended) at some interesting object or event.",
        "4. Waves bye-bye on his/her own when someone leaves.",
        "5. Extends his/her arm upward to signal a wish to be picked up.",
        "6. Shakes head `no`.",
        "7. Nods head `yes`.",
        "8. Gestures `hush` by placing finger to lips.",
        "9. Requests something by extending arm and opening and closing hand.",
        "10. Blows kisses from a distance.",
        "11. Smacks lips in a `yum yum` gesture to indicate that something taste good.",
        "12. Shrugs to indicate `all gone` or `where'd it go`.");
        $qNum = 1;
        foreach($questionArray as $label) {
            $this->form->addElement('select', "II_A_" . $qNum, $label, array(null=>'', "not_yet"=>"Not Yet", "sometimes"=>"Sometimes", 'often'=>"Often", 'not_answered'=>"Not Answered"));
            $qNum++;
        }

        $this->form->addElement('header', null, "B. GAMES AND ROUTINES");
        $questionArray = array("1. Play peekaboo.",
        "2. Play patty cake.",
        "3. Play `so big`.",
        "4. Play chasing games.",
        "5. Sing.",
        "6. Dance.");
        $qNum = 1;
        foreach($questionArray as $label) {
            $this->form->addElement('select', "II_B_" . $qNum, $label, $this->yesNo);
            $qNum++;
        }

        $this->form->addElement('header', null, "C. ACTIONS WITH OBJECTS");
        $questionArray = array("1. Eat with a spoon or fork.",
        "2. Drink from a cup containing liquid.",
        "3. Comb or brush own hair.",
        "4. Brush teeth.",
        "5. Wipe face or hands with a towel or cloth.",
        "6. Put on hat.",
        "7. Put on a shoe or sock.",
        "8. Put on a necklace, bracelet, or watch.",
        "9. Lay head on hands and squeeze eyes shut as if sleeping.",
        "10. Blow to indicate something is hot.",
        "11. Hold plane and make it `fly`.",
        "12. Put telephone to ear.",
        "13. Sniff flowers.",
        "14. Push toy car or truck.",
        "15. Throw a ball.",
        "16. Pour pretend liquid from one container to another.",
        "17. Stir pretend liquid in a cup or pan with a spoon.");
        $qNum = 1;
        foreach($questionArray as $label) {
            $this->form->addElement('select', "II_C_" . $qNum, $label, $this->yesNo);
            $qNum++;
        }

        $this->form->addElement('header', null, "D. PRETENDING TO BE A PARENT");
        $questionArray = array("1. Put to bed.",
        "2. Cover with blanket.",
        "3. Feed with bottle.",
        "4. Feed with spoon.",
        "5. Brush/comb its hair.",
        "6. Pat or burp it.",
        "7. Push in stroller/buggy.",
        "8. Rock it.",
        "9. Kiss or hug it.",
        "10. Try to put shoe or sock or hat on it.",
        "11. Wipe its face or hands.",
        "12. Talk to it.",
        "13. Try to put diaper on it.");
        $qNum = 1;
        foreach($questionArray as $label) {
            $this->form->addElement('select', "II_D_" . $qNum, $label, $this->underSays);
            $qNum++;
        }

        $this->form->addElement('header', null, "E. IMITATING OTHER ADULT ACTIONS");
        $questionArray = array("1. Sweep with broom or mop.",
        "2. Put key in door or lock.",
        "3. Pound with hammer or mallet.",
        "4. Attempt to use saw.",
        "5. `Type` at a typewriter or computer keyboard.",
        "6. `Read` (opens book, turns page).",
        "7. Vacuum.",
        "8. Water plants.",
        "9. Play musical instrument (e.g., piano, trumpet).",
        "10. `Drive` car by turning steering wheel.",
        "11. Wash dishes.",
        "12. Clean with cloth or duster.",
        "13. Write with a pen, pencil, or marker.",
        "14. Dig with a shovel.",
        "15. Put on glasses.");
        $qNum = 1;
        foreach($questionArray as $label) {
            $this->form->addElement('select', "II_E_" . $qNum, $label, $this->underSays);
            $qNum++;
        }

        $this->form->addElement('header', null, "F. PRETEND OBJECTS");
        $this->form->addElement('select', "II_F_replacement", "During play, children sometimes use an object as a replacement for another.", $this->yesNo);

        $this->addTextAreaElement("II_F_replacement_examples", $this->indent . "If yes, please give several examples:", array("II_F_replacement{@}=={@}yes"));

        $this->addTextAreaElement("II_F_replacement_comments", "OTHER COMMENTS:");
    }
}

?>