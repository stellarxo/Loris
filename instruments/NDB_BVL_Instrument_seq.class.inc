<?php

require_once 'HTML/QuickForm.php';
require_once 'HTML/QuickForm/Renderer/Array.php';

class NDB_BVL_Instrument_seq extends NDB_BVL_Instrument
{
    var $ValidityEnabled = false;
    var $ValidityRequired = false;
	var $respondentAgeYears;
	var $scoreCols = array("total_seq", "total_hypo",
		"total_hyper", "total_seeking", "total_social", "total_non-social", "total_tactile", "total_auditory",
		"total_visual", "total_gustatory_olfactory", "total_vestibular_proprioceptive");
	var $scores = array();

/*
INSERT INTO test_names VALUES ('', 'seq', 'Sensory Experiences Questionnaire', '0', '1');
INSERT INTO instrument_subtests VALUES('', 'seq', 'seq_page1', 'Sound & Sight', 1);
INSERT INTO instrument_subtests VALUES('', 'seq', 'seq_page2', 'Touch, Taste, Smell & Movement', 2);
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
	$this->_doubleDataEntryDiffIgnoreColumns = array_merge(array('CommentID', 'UserID', 'Testdate',
		'Window_Difference', 'Candidate_Age','Data_entry_completion_status',
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
							 'q32_seem_happiest'),
		$this->scoreCols
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

		$db =& Database::singleton();

		// Get the item scores
		$query = "SELECT * FROM $this->table WHERE CommentID='".$this->getCommentID()."'";
		$record=array();
		$db->selectRow($query, $record);


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

		$this->form->addElement("static", null, "<BR>");
		$this->form->addElement("header", null, "Scores based on the SEQ Version 2.1");
		$this->form->addElement("static", null, "<BR>");
		$scoreLabels1 = array(
			"total_seq" => "Total Score",
			"total_hypo" => "Hypo-Responsiveness Score",
			"total_hyper" => "Hyper-Responsiveness Score",
			"total_seeking" => "Seeking Score",
			"total_social" => "Social Context Score",
			"total_non-social" => "Non-Social Context Score"
		);
		$scoreLabels2 = array(
			"total_tactile" => "Tactile Score",
			"total_auditory" => "Auditory Score",
			"total_visual" => "Visual Score",
			"total_gustatory_olfactory" => "Gustatory/Olfactory Score",
			"total_vestibular_proprioceptive" => "Vestibular/Proprioceptive Score"
		);
		$this->form->addElement("header", null, "Score Sheet 1");
		$this->form->addElement("static", null, "<BR>");
		foreach ($scoreLabels1 as $field => $label) {
			$this->form->addElement("static", $field, $label);
		}

		$this->form->addElement("static", null, "<BR>");
		$this->form->addElement("header", null, "Score Sheet 2");
		$this->form->addElement("static", null, "<BR>");
		$this->form->addElement("static", null, "Note: These scores should be interpreted with caution as they have fewer items and thus lower reliability than the total scores or other scales above.");
		$this->form->addElement("static", null, "<BR>");
		foreach ($scoreLabels2 as $field => $label) {
			$this->form->addElement("static", $field, $label);
		}



		$this->form->addElement('static', null, "<br /><br />");
		$this->form->addElement("textarea", "other_comments", "Comments about Validity:", array('cols' => 25, 'rows' => 4));
		$this->XINRegisterRule("other_comments", array("{other_comments}{@}=={@}NEVER_REQUIRED"));


	}

	/*
     * calculates SEQ score
     */
	function _score()
	{
		$db =& Database::singleton();
		if($this->_determineDataEntryCompletionStatus() == "Incomplete") {
			return;
		}
		// skip scoring if proband DoB was not entered, i.e. data entry is not completed
		if (empty($this->respondentAgeYears)) {
			return;
		}
		// null scores
		$this->_nullScores($this->scoreCols);
		// Get the item scores
		$query = "SELECT * FROM $this->table WHERE CommentID='" . $this->getCommentID() . "'";
		$record = array();
		$db->selectRow($query, $record);
		// Control items in version 2.1 excluded from scoring (items 2, 7, 13, 26)
//		$excluded = array(2, 7, 13, 26);
		$excluded = array("q2_enjoy_music", "q7_enjoy_picture_books", "q13_enjoy_watching_videos", "q26_enjoy_riding");
		$questions = array();
		$i = 1;

		// Matches each question with its question number
		foreach ($this->questionArray as $key => $question) {
			if (!in_array($key, $excluded)) {
				$questions = merge_array($questions, array($i => $key));
				$i++;
			}
			else {
				$i++;
			}
		}

		// Convert items to algorithm scores
		// Higher score == greater frequency/intensity of sensory features
		$conversion = array(
			"almost_never" => 1,
			"once_in_a_while" => 2,
			"sometimes" => 3,
			"frequently" => 4,
			"almost_always" => 5
		);
		foreach ($record as $field => $answer) {
			if (in_array($field, $questions)) {
				$this->scores[$field] = $conversion[$answer];
			}
		}

		// check age limit
		if ($this->respondentAgeYears < 0.5) {
			$scoreCols["total_seq"] = "Respondent too young to score";
		} elseif ($this->respondentAgeYears > 6) {
			$scoreCols["total_seq"] = "Respondent too old to score";
		} else {
			$alg = array(
				// SCORE SHEET 1

				// SEQ Total Score - summing the raw scores of the 33 individual items
				array('total_seq',
					array(1, 3, 4, 5, 6, 8, 9, 10, 11, 12, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 27, 28, 29, 30,
						'36a', '36b', '36c', '36d', '36e', '36f', '38')),
				// Total Hypo-Responsiveness - sum the raw scores for items # 3, 4, 10, 12, 19, 21 (a total of 6 items)
				array('total_hypo', array(3, 4, 10, 12, 19, 21)),
				// Total Hyper-Responsiveness - sum the raw scores for items # 1, 5, 6, 8, 11, 14, 15, 16, 17, 18, 20, 22, 29, 38 (a total of 14 items)
				array('total_hyper', array(1, 5, 6, 8, 11, 14, 15, 16, 17, 18, 20, 22, 29, 38)),
				// Total Seeking - sum items # 9, 23, 24, 25, 27, 28, 30, 36a, 36b, 36c, 36d, 36e, 36f (a total of 13 items)
				array('total_seeking', array(9, 23, 24, 25, 27, 28, 30, '36a', '36b', '36c', '36d', '36e', '36f')),
				// Total Social Sensory Responsiveness - sum the raw scores for items # 3, 6, 11, 12, 14, 17, 20, 21, 24, and 28 (a total of 10 items).
				array('total_social', array(3, 6, 11, 12, 14, 17, 20, 21, 24, 28)),
				// Total Non-Social Sensory Responsiveness - sum the raw scores for items # 1, 4, 5, 8, 9, 15,16, 18, 19, 22, 23, 25, 27, 29, 30, 38, 36a, 36b, 36c, 36d, 36e, 36f (a total of 22 items).
				array('total_nonsocial', array(1, 4, 5, 8, 9, 15, 16, 18, 19, 22, 23, 25, 27, 29, 30, 38, '36a', '36b', '36c', '36d', '36e', '36f')),

                //SCORE SHEET 2

				// Tactile - sum the raw scores for items # 14, 15, 16, 17, 18, 19, 20, 21, 36e, 36f (10 items total)
				array('total_tactile', array(14, 15, 16, 17, 18, 19, 20, 21, '36e', '36f')),
				// Auditory - sum the raw scores for items # 1, 3, 4, 5, 6, 36a (6 items total)
				array('total_auditory', array(1, 3, 4, 5, 6, '36a')),
				// Visual - sum the raw scores for items # 8, 9, 10, 11, 12, 36b (6 items total)
				array('total_visual', array(8, 9, 10, 11, 12, '36b')),
				// Gustatory/Olfactory - sum the raw scores for items # 22, 23, 25, 36c, 36d, 38 (7 items total)
				array('total_gustatory_olfactory', array(22, 23, 25, '36c', '36d', 38)),
				// Vestibular/Proprioceptive - sum the raw scores for items # 14, 15, 16, 17, 18, 19, 20, 21, 36e, 36f (10 items total)
				array('total_vestibular_proprioceptive', array(14, 15, 16, 17, 18, 19, 20, 21, '36e', '36f'))
			);

			$fields = array();
			foreach ($this->questionArray as $key => $question) {
				$fields[] = $key;
				$fields[] = ', ';
			}
			$query = "SELECT " . $fields . " FROM seq WHERE CommentID=:CID";
			$results = $db->pselectOne($query, array('CommentID' => $this->getCommentID()));
			$completely_answered = true;
			while ($completely_answered == true) {
				foreach ($this->questionArray as $key => $question) {
					if ($query[$key] == NULL || $query[$key] == 'not_answered') {
						$completely_answered = false;
						$scoreCols["total_seq"] = "Caregivers are asked to fill out the SEQ questionnaire completely.
            Only when all items are checked can the best and most representative score be obtained.";
					}
				}
			}
			if ($completely_answered == true) {
				foreach ($this->scoreCols as $col) {
					foreach ($questions as $number => $question) {
						if (in_array($question, $alg[$col])) {
							$this->scoreCols[$col] += $this->scores[$question];
						}
					}
					$this->scoreCols[$col] = ($this->scoreCols[$col]) / count($alg[$col]);
					print $col . ": " . $this->scoreCols[$col] . "\n";
				}
			}
		}
		// save the resultant total
		$result = $db->update($this->table, $this->scoreCols, array('CommentID' => $this->getCommentID()));


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
