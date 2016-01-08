<?php

require_once 'HTML/QuickForm.php';
require_once 'HTML/QuickForm/Renderer/Array.php';

class NDB_BVL_Instrument_seq extends NDB_BVL_Instrument
{
    var $ValidityEnabled = false;
    var $ValidityRequired = false;

/*
INSERT INTO test_names VALUES ('', 'seq', 'Sensory Experiences Questionnaire', '0', '1');
INSERT INTO instrument_subtests VALUES('', 'seq', 'seq_page1', 'Sound & Sight', 1);
INSERT INTO instrument_subtests VALUES('', 'seq', 'seq_page2', 'Touch, Tast, Smell & Movement', 2);
INSERT INTO instrument_subtests VALUES('', 'seq', 'seq_page3', 'General and Addendum', 3);
-- INSERT INTO test_battery VALUES ('', 'seq', '1050', '1140', 'Y', 'Visit', '3');
*/

	var $questionArray = array(
	//Experiences with Sound:
	"q1_react_sensitively"=>"Does your child react sensitively or startle easily to unexpected or loud sounds?",
	"q2_enjoy_music"=>"Does your child enjoy listening to music?",
	"q3_ignore_call"=>"Does your child ignore you when you call his/her name?",
	"q4_ignore_tune_out"=>"Does your child seem to ignore or tune-out loud noises?",
	"q5_notive_sounds"=>"Does your child notice sounds in the environment before other people do?",
	"q6_show_distress_loud"=>"Does your child show distress during loud conversations or singing?",
	//Experiences with Sight:
	"q7_enjoy_picture_books"=>"Does your child enjoy looking at picture books?",
	"q8_disturbed_by_light"=>"Is your child disturbed by too much light inside or brightness outside?",
	"q9_stare_at_lights"=>"Does your child stare at lights or objects that spin or move?",
	"q10_slow_to_notice"=>"Is your child slow to notice new objects toys in the room, or slow to look at objects that are placed or held near him/her?",
	"q11_avoid_looking"=>"Does your child avoid looking at your face during social games/play?",
	"q12_seem_to_ignore"=>"Does your child seem to ignore (doesn't notice) when someone new or different enters the room?",
	"q13_enjoy_watching_videos"=>"Does your child enjoy watching children?s videos or TV programs?",
	//Experiences with Touch:
	"q14_dislike_cuddling"=>"Does your child dislike cuddling or being held?",
	"q15_show_distress_grooming"=>"Does your child show distress during grooming?",
	"q16_avoid_touching"=>"Does your child avoid touching certain textures (such as fuzzy or squishy toys) or playing with messy materials (such as sand, lotion)?",
	"q17_react_negatively"=>"Does your child react negatively or pull away when touched by a person?",
	"q18_trouble_adjusting"=>"Does your child have trouble adjusting to the water temperature during bath time or does he/she dislike being in water?",
	"q19_slow_to_react"=>"Does your child seem slow to react to pain?",
	"q20_dislike_tickled"=>"Does your child dislike being tickled?",
	"q21_ignore_tap"=>"Does your child ignore you (doesn?t notice) when you tap him/her on the shoulder for attention?",
	//Experiences with Taste or Smell:
	"q22_refuse_new_foods"=>"Does your child refuse to try new foods or avoid certain tastes, smells, or textures (consistencies) of food?",
	"q23_smell_objects"=>"Does your child smell objects or toys during play or other activities?",
	"q24_interested_smell"=>"Does your child seem interested in the way people smell?",
	"q25_put_objects"=>"Does your child put objects, toys or other non-food items in his/her mouth to lick, suck, or explore?",
	//Experiences with Movement:
	"q26_enjoy_riding"=>"Does your child enjoy riding in a car?",
	"q27_like_jump"=>"Does your child like to jump up/down, rock back/forth, or spin in circles?",
	"q28_seek_physical"=>"Does your child seek out physical rough-housing play? (For example: craves being tossed in the air or spun around.)",
	"q29_uneasy_dizzy"=>"Does your child seem uneasy or become dizzy when moving on a swing or rocking chair, for example?",
	"q30_flap_arms"=>"Does your child flap his/her arms or hands repeatedly, particularly when excited?");

	//section titles
	var	$sectionStarts = array("q1_react_sensitively"=>"Sound",
	"q7_enjoy_picture_books"=>"Sight",
	"q14_dislike_cuddling"=>"Touch",
	"q22_refuse_new_foods"=>"Taste or Smell",
	"q26_enjoy_riding"=>"Movement");



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
		$this->testName = "seq";           // test_names.Test_name
		$this->table = 'seq';              // name of database table corresponding to instrument
		// data keyed by commentID
		$this->commentID = $commentID;

		//The array of dates/timestamps to convert to database dates/timestamps
		//Any HTML_Quickform date elements must be listed here
		$this->dateTimeFields=array("Date_taken");

		//The array of selects with multiple answers allowed
		//Any HTML_Quickform multiple selects must be listed here
		$this->_selectMultipleElements = array();

		// required fields for data entry completion status
		$this->_requiredElements = array('Examiner', "q1_react_sensitively", "q14_dislike_cuddling", "q36_a_sounds");
	/**
	 * Array of column names to be ignored by the double data entry conflict detector.
	 */
	$this->_doubleDataEntryDiffIgnoreColumns = array('CommentID', 'UserID', 'Testdate',  'Window_Difference', 'Candidate_Age','Data_entry_completion_status',
							 'person_completing_other',
							 'q1_react_sensitively_what_do',
							 'q2_enjoy_music_what_do',
							 'q3_ignore_call_what_do',
							 'q4_ignore_tune_out_what_do',
							 'q5_notive_sounds_what_do',
							 'q6_show_distress_loud_what_do',
							 'q7_enjoy_picture_books_what_do',
							 'q8_disturbed_by_light_what_do',
							 'q9_stare_at_lights_what_do',
							 '10_slow_to_notice_what_do',
							 'q11_avoid_looking_what_do',
							 'q12_seem_to_ignore_what_do',
							 'q13_enjoy_watching_videos_what_do',
							 'q14_dislike_cuddling_what_do',
							 'q15_show_distress_grooming_what_do',
							 'q16_avoid_touching_what_do',
							 'q17_react_negatively_what_do',
							 'q18_trouble_adjusting_what_do',
							 'q19_slow_to_react_what_do',
							 'q20_dislike_tickled_what_do',
							 'q21_ignore_tap_what_do',
							 'q22_refuse_new_foods_what_do',
							 'q23_smell_objects_what_do',
							 'q24_interested_smell_what_do',
							 'q25_put_objects_what_do',
							 'q26_enjoy_riding_what_do',
							 'q27_like_jump_what_do',
							 'q28_seek_physical_what_do',
							 'q29_uneasy_dizzy_what_do',
							 'q30_flap_arms_what_do',
							 'q31_free_time',
							 'q32_seem_happiest');
           

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
		if(preg_match("/seq(_page[0-9]+)/",$this->page,$matches)){
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
		$this->form->addElement('header', 'instrument_title', "Sensory Experience Questionnaire");

		// automatically adds examiner & date of administration
		$this->_addMetadataFields();

		$this->form->addElement('select', 'person_completing', "Person completing the form", array(NULL=>'', 'mother'=>"Mother", 'father'=>"Father", 'both_parents'=>"Both Parents", 'teacher'=>"Teacher", 'other'=>"Other"));
		$this->form->addElement("text", 'person_completing_other', $this->indent . "Other:");
		$this->XINRegisterRule('person_completing_other', array('person_completing{@}=={@}other'), "Please indicate who is completing this form");

	}

	function _page1(){

		$answerOptions = array(NULL=>"", "almost_never"=>"Almost Never", "once_in_a_while"=>"Once in a while", "sometimes"=>"Sometimes", "frequently"=>"Frequently", "almost_always"=>"Almost always", "not_answered"=>"Not Answered");
		$yesNo = array(NULL=>"", "yes"=>"Yes", "no"=>"No", "not_answered"=>"Not Answered");

		//first two sections are on this page...
		foreach(array_slice($this->questionArray, 0, 13) as $field=>$label) {

			if(array_key_exists($field, $this->sectionStarts)) {
				$this->form->addElement('header', null, "Experiences with " . $this->sectionStarts[$field] . ":");
			}
			
			$this->form->addElement('select', $field, $label, $answerOptions);
			$this->form->addElement('select', $field . "_change", $this->indent . "Do you try to change this behavior?",  $yesNo);

			$group[]=&$this->form->createElement("textarea", $field . "_what_do", null, array('cols'=>40, 'rows'=>2));
			$group[]=&$this->form->createElement("select", $field."_what_do_status", "", array(NULL=>'', 'not_answered'=>'Not Answered'));
			$this->form->addGroup($group, $field.'_group', $this->indent . $this->indent . "If yes, what do you do?", null, false);
			unset($group);
			$this->XINRegisterRule($field . "_what_do", array($field . '_change{@}=={@}yes', $field . '_what_do_status{@}=={@}'), "Please indicate what is done to change this behaviour.", $field.'_group');
			$this->XINRegisterRule($field . "_what_do_status", array($field . '_change{@}=={@}yes', $field . '_what_do{@}=={@}'), "Please indicate what is done to change this behaviour, or mark this section as not answered.", $field.'_group');

		}
	}
	
	function _page2(){
	//identical to _page1(), except a differenct slice of the $this->questionArray

		$answerOptions = array(NULL=>"", "almost_never"=>"Almost Never", "once_in_a_while"=>"Once in a while", "sometimes"=>"Sometimes", "frequently"=>"Frequently", "almost_always"=>"Almost always", "not_answered"=>"Not Answered");
		$yesNo = array(NULL=>"", "yes"=>"Yes", "no"=>"No", "not_answered"=>"Not Answered");

		//last three sections are on this page...
		foreach(array_slice($this->questionArray, 13) as $field=>$label) {

			if(array_key_exists($field, $this->sectionStarts)) {
				$this->form->addElement('header', null, "Experiences with " . $this->sectionStarts[$field] . ":");
			}
			
			$this->form->addElement('select', $field, $label, $answerOptions);
			$this->form->addElement('select', $field . "_change", $this->indent . "Do you try to change this behavior?",  $yesNo);

			$group[]=&$this->form->createElement("textarea", $field . "_what_do", null, array('cols'=>40, 'rows'=>2));
			$group[]=&$this->form->createElement("select", $field."_what_do_status", "", array(NULL=>'', 'not_answered'=>'Not Answered'));
			$this->form->addGroup($group, $field.'_group', $this->indent . $this->indent . "If yes, what do you do?", null, false);
			unset($group);
			$this->XINRegisterRule($field . "_what_do", array($field . '_change{@}=={@}yes', $field . '_what_do_status{@}=={@}'), "Please indicate what is done to change this behaviour.", $field.'_group');
			$this->XINRegisterRule($field . "_what_do_status", array($field . '_change{@}=={@}yes', $field . '_what_do{@}=={@}'), "Please indicate what is done to change this behaviour, or mark this section as not answered.", $field.'_group');

		}
	}
	
	function _page3(){
	    $this->form->addElement('header', null, "General Questions:");

	    $generalQuestions = array("q31_free_time"=>"How does your child occupy his/her free time (play time)?",
                                    "q32_seem_happiest"=>"When does your child seem happiest at play?",
                                    "q33_enjoy_interaction"=>"When does your child appear to enjoy social interaction with you the most?",
                                    "q34_works_best"=>"What works best to get your child to interact or play with you?",
                                    "q35_other_comments"=>"List other comments you would like to make...");
        foreach($generalQuestions as $field=>$label) {
            $this->addTextAreaElement($field, $label);
        }
        
        $this->form->addElement('header', null, "SEQ Addendum Items");
        $this->form->addElement('static', null, 'How often is your child extremely fascinated with:');
        $questionArray = array("a_sounds"=>"A. Sounds",
                                "b_lights"=>"B. Lights",
                                "c_smells"=>"C. Smells",
                                "d_tastes"=>"D. Tastes",
                                "e_textures"=>"E. Textures",
                                "f_touch"=>"F. Touch");
        $answerOptions = array(null=>"",
                                "almost_never"=>"Almost Never",
                                "once_in_a_while"=>"Once in a While",
                                "sometimes"=>"Sometimes",
                                "frequently"=>"Frequently",
                                "almost_always"=>"Almost Always",
                                "not_answered"=>"Not Answered");
        foreach($questionArray as $field=>$label) {
            $this->form->addElement('select', "q36_" . $field, $this->indent . $label, $answerOptions);
        }

        $this->addTextAreaElement("q37_seek_or_crave", "Does your child `seek` or `crave` particular sensory experiences?");

        $yesMaybeNo = array(null=>'', 'yes'=>"Yes", 'maybe'=>"Maybe", 'no'=>"No", 'not_answered'=>"Not Answered");
        $this->form->addElement('select', "q38_pick_eater", "Would you describe your child as being a `picky` eater?", $yesMaybeNo);
        $this->form->addElement('select', "q38_selective", "Is your child selective in food preferences?", $answerOptions);
        $this->addTextAreaElement("q39_favourite_food_qualities", "Please describe your child?s favorite foods and qualities about these foods");
        $this->addTextAreaElement("q40_why_foods", "Why do you think your child likes these foods?");

        $this->form->addElement('static', null, "Thinking about your child's behaviors since birth, have you ever wondered...");
        foreach($questionArray as $field=>$label) {
            $this->form->addElement('select', "q41_" . $field, $this->indent . $label, $answerOptions);
        }
        
        $this->form->addElement('select', "q42_sensory_change", "Have your child's sensory preferences or aversions changed much over time?", $yesMaybeNo);
        $this->addTextAreaElement("q42_sensory_change_how", $this->indent . "If yes or maybe, how have they changed?", array("q42_sensory_change{@}=={@}yes|maybe"), "This field is required if you previously answered yes or maybe");
        $this->addTextAreaElement("q43_notice_change", "When did you first notice any difference in your child's sensory experiences?");

	}

}
?>
