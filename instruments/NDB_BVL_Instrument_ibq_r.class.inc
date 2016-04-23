<?php

require_once 'HTML/QuickForm.php';
require_once 'HTML/QuickForm/Renderer/Array.php';

class NDB_BVL_Instrument_ibq_r extends NDB_BVL_Instrument
{
    var $ValidityEnabled = false;
    var $ValidityRequired = false;

	var $scoreLabels = array("activity_level"=>"Activity Level",
							"distress_to_limitations"=>"Distress to Limitations",
							"fear"=>"Fear",
							"duration_of_orienting"=>"Duration of Orienting",
							"smiling_and_laughter"=>"Smiling and Laughter",
							"high_pleasure"=>"High Pleasure",
							"low_pleasure"=>"Low Pleasure",
							"soothability"=>"Soothability",
							"falling_reactivity"=>"Falling Reactivity", ///Rate of Recovery from Distress",
							"cuddliness"=>"Cuddliness",
							"perceptual_sensitivity"=>"Perceptual Sensitivity",
							"sadness"=>"Sadness",
							"approach"=>"Approach",
							"vocal_reactivity"=>"Vocal Reactivity");
	
							   
    /**
    * sets up basic data, such as the HTML_Quickform object, and so on.
    *
    * @param string $commentID  the CommentID identifying the data to load
    * @param string $page       if a multipage form, the page to show
    * @return void
    * @access public
    */
    function setup($commentID, $page)
    {
        $this->formType="XIN";
        $this->form = new HTML_Quickform('test_form');
        $this->page = $page;            // page label (number or
        // string - used by
        // user-defined child classes)
        
        // set the object properties
        $this->testName = "ibq_r";           // test_names.Test_name
        $this->table = 'ibq_r';              // name of table containing
        // data keyed by commentID
        $this->commentID = $commentID;
        
        //The array of dates/timestamps to convert to database dates/timestamps
        $this->dateTimeFields=array("Date_taken"
        
        );
        
        // setup the form
        $this->_setupForm();
        // required fields for data entry completion status
        $this->_requiredElements = array('Examiner', 'q_1', 'q_32', 'q_90', 'q_149', 'q_174');
        /**
         * Array of column names to be ignored by the double data entry conflict detector.
         */
        $this->_doubleDataEntryDiffIgnoreColumns = array('CommentID', 'UserID', 'Testdate', 'Window_Difference',
                       'Candidate_Age','Data_entry_completion_status','cuddlineness', 'distress_to_limitations',
                       'duration_of_orienting','falling_reactivity','fear','high_pleasure','low_pleasure',
                       'perceptual_sensitivity','activity_level','smiling_and_laughter','soothability', 
                       'sadness', 'approach', 'vocal_reactivity' );
        //
        $scoreHeader = array("scale"=>"Score");
        $this->localDefaults = array_merge($this->localDefaults, $scoreHeader);
    } 
    
    /**
    * method to build the HTML_Quickform object into a paged form
    *
    * @return void
    * @access private
    */
    function _setupForm()
    {
    	$this->answer_options=array(NULL=>'', '1'=>'1', '2'=>'2', '3'=>'3', '4'=>'4', '5'=>'5', '6'=>'6', '7'=>'7', 'does_not_apply'=>'Does not apply', 'not_answered'=>'Not Answered');
    	
    	if(preg_match("/(_page[0-9])/", $this->page, $matches)) {
    		call_user_method($matches[1], $this);
    	} else {
    		$this->_main();
    	}
    	
    	$this->form->addFormRule(array(&$this,'XINValidate'));
    }
    
    function _main(){
            // display test name
            $this->form->addElement('header', 'instrument_title', "Infant Behavior Questionnaire - Revised (IBQ-R)");
            
            // add examiner & date of administration
            $this->_addMetadataFields();
            
            $this->form->addElement('header', null, 'Calculate Scores');
            
            //score headers
            $this->form->addElement('static', "scale", "Scale");
            
            //score columns
            foreach($this->scoreLabels as $field=>$label) {
            	$this->form->addElement('static', $field, $label);
            }
    	//calculate subscales
    
        }
        
    function score(){
    	if($this->_determineDataEntryCompletionStatus() == "Incomplete") {
    		return;
    	}
    	
    	//null scores
		$this->_nullScores($this->scoreLabels);

		//get the saved scores
    	$db =& Database::singleton();
    	
    	$query = "SELECT * FROM $this->table WHERE CommentID = '$this->commentID'";
    	$record = array();
    	$db->selectRow($query, $record);
    	
    	//do the math...
    	$reverseItems = array(1, 14, 117,
    							11, 16, 19, 76,
    							163,
    							176, 179, 182, 185, 188, 191,
    							22, 24, 26, 29, 120, 121,
    							7, 105, 108, 124, 125, 127, 128, 130, 132,
    							89, 173);
    	//restrict to numerical scores
    	foreach ($record as $field=>$value) {
    		if(is_numeric($value)) {
    			$record[$field] = intval($value);
    		} else {
    			$record[$field] = null;
    		}
	    	//reverse as needed
    		if (in_array(preg_replace("/q_/", "", $field), $reverseItems) && !is_null($record[$field])) {
    			$record[$field] = 8 - $record[$field];
    		}
    	}

    	
    	//calculate subscales
	   	$subScales = array("activity_level"=>array(1, 2, 3, 12, 13, 14, 32, 33, 38, 39, 111, 112, 115, 116, 117),
							"distress_to_limitations"=>array_merge(array(11), range(15, 20), array(41, 44, 75, 76, 93, 109, 113, 114, 118)),
							"fear"=>array_merge(array(90, 94, 99), range(150, 158), range(161, 164)),
							"duration_of_orienting"=>array_merge(range(46, 51), array(54, 55, 91, 92, 100, 101)),
							"smiling_and_laughter"=>array(34, 36, 37, 40, 43, 53, 56, 57, 110, 149),
							"high_pleasure"=>array_merge(array(58, 65, 66, 67), range(77, 82), array(165)),
							"low_pleasure"=>array_merge(range(59, 64), range(68, 74)),
							"soothability"=>range(174, 191),
							"falling_reactivity"=>array_merge(range(21, 29), range(119, 122)),
							"cuddliness"=>array_merge(array(5, 6, 7, 105, 106, 107, 108), range(123, 132)),
							"perceptual_sensitivity"=>array_merge(array(4, 83, 84, 95, 96), range(133, 139)),
							"sadness"=>array_merge(array(30, 31), range(140, 145), range(166, 171)),
							"approach"=>array_merge(range(85, 89), array(97, 98, 104, 159, 160, 172, 173)),
							"vocal_reactivity"=>array(8, 9, 10, 35, 42, 45, 52, 102, 103, 146, 147, 148)
						   );
		
		foreach($subScales as $field=>$array) {
			$numericalResponses = 0;
			foreach($array as $question) {
				$scores[$field] += $record["q_".$question];
				if($record["q_".$question]) {
					$numericalResponses++;
				}
			}
			//take average of numerical responses
			if ($numericalResponses == 0) {
				$scores[$field] = null;
			} else {
				$scores[$field] = round($scores[$field] / $numericalResponses, 2);
			}
		}
		
    	//save scores
		$result = $db->update($this->table, $scores, array("CommentID"=>$this->getCommentID()));
		
    }    
        
    function _page1(){
        $this->form->addElement('header', null, "Feeding");
        $this->form->addElement('static', null, "During feeding, how often did the baby :");
        $this->form->addElement("select", "q_1", "1) lie or sit quietly", $this->answer_options);
        $this->form->addElement("select", "q_2", "2) squirm or kick", $this->answer_options);
        $this->form->addElement("select", "q_3", "3) wave arms", $this->answer_options);
        $this->form->addElement("select", "q_4", "4) notice lumpy texture in food (e.g., oatmeal)", $this->answer_options);
        $this->form->addElement('static', null, "In the last week, while being fed in your lap, how often did the baby:");
        $this->form->addElement("select", "q_5", "5) seem to enjoy the closeness", $this->answer_options);
        
        
        $this->form->addElement("select", "q_6", "6) snuggle even after she was done", $this->answer_options);
        
        
        $this->form->addElement("select", "q_7", "7) seem eager to get away as soon as the feeding was over", $this->answer_options);
        $this->form->addElement('static', null, "How often did your baby make talking sounds:");
        
        
        $this->form->addElement("select", "q_8", "8) while waiting in a high chair for food", $this->answer_options);
        
        
        $this->form->addElement("select", "q_9", "9) when s/he was ready for more food", $this->answer_options);
        
        
        $this->form->addElement("select", "q_10", "10) when s/he has had enough to eat", $this->answer_options);
        
        $this->form->addElement('header', null, "Sleeping");
        $this->form->addElement('static', null, "Before falling asleep at night during the last week, how often did the baby :");
        
        
        $this->form->addElement("select", "q_11", "11) show no fussing or crying", $this->answer_options);
        $this->form->addElement('static', null, "During sleep, how often did the baby :");
        
        
        $this->form->addElement("select", "q_12", "12) toss about in the crib", $this->answer_options);
        
        
        $this->form->addElement("select", "q_13", "13) move from the middle to the end of the crib", $this->answer_options);
        
        
        $this->form->addElement("select", "q_14", "14) sleep in one position only", $this->answer_options);
        $this->form->addElement('static', null, "After sleeping, how often did the baby :");
        
        
        $this->form->addElement("select", "q_15", "15) fuss or cry immediately", $this->answer_options);
        
        
        $this->form->addElement("select", "q_16", "16) play quietly in the crib", $this->answer_options);
        
        
        $this->form->addElement("select", "q_17", "17) cry if someone doesn't come within a few minutes ", $this->answer_options);
        $this->form->addElement('static', null, "How often did the baby :");
        
        
        $this->form->addElement("select", "q_18", "18) seem angry (crying and fussing) when you left her/him in the crib?  ", $this->answer_options);
        
        
        $this->form->addElement("select", "q_19", "19) seem contented when left in the crib", $this->answer_options);
        
        
        $this->form->addElement("select", "q_20", "20) cry or fuss before going to sleep for naps", $this->answer_options);
        $this->form->addElement('static', null, "When going to sleep at night, how often did your baby:");
        
        
        $this->form->addElement("select", "q_21", "21) fall asleep within 10 minutes", $this->answer_options);
        
        
        $this->form->addElement("select", "q_22", "22) have a hard time settling down to sleep", $this->answer_options);
        
        
        $this->form->addElement("select", "q_23", "23) settle down to sleep easily", $this->answer_options);
        $this->form->addElement('static', null, "When your baby awoke at night, how often did s/he : ");
        
        
        $this->form->addElement("select", "q_24", "24) have a hard time going back to sleep", $this->answer_options);
        
        
        $this->form->addElement("select", "q_25", "25) go back to sleep immediately", $this->answer_options);
        $this->form->addElement('static', null, "When put down for a nap, how often did your baby : ");
        
        
        $this->form->addElement("select", "q_26", "26) stay awake for a long time", $this->answer_options);
        
        
        $this->form->addElement("select", "q_27", "27) go to sleep immediately", $this->answer_options);
        
        
        $this->form->addElement("select", "q_28", "28) settle down quickly", $this->answer_options);
        
        
        $this->form->addElement("select", "q_29", "29) have a hard time settling down", $this->answer_options);
        $this->form->addElement('static', null, "When it was time for bed or a nap and your baby did not want to go, how often did s/he : ");
        
        
        $this->form->addElement("select", "q_30", "30) whimper or sob", $this->answer_options);
        
        
        $this->form->addElement("select", "q_31", "31) become tearful", $this->answer_options);
        
    }
    
    function _page2(){
        $this->form->addElement('header', null, "Bathing and Dressing");
        $this->form->addElement('static', null, "When being dressed or undressed during the last week, how often did the baby : ");
        
        
        $this->form->addElement("select", "q_32", "32) wave her/his arms and kick", $this->answer_options);
        
        
        $this->form->addElement("select", "q_33", "33) squirm and/or try to roll away", $this->answer_options);
        
        
        $this->form->addElement("select", "q_34", "34) smile or laugh", $this->answer_options);
        
        
        $this->form->addElement("select", "q_35", "35) coo or vocalize", $this->answer_options);
        $this->form->addElement('static', null, "When put into the bath water, how often did the baby : ");
        
        
        $this->form->addElement("select", "q_36", "36) smile", $this->answer_options);
        
        
        $this->form->addElement("select", "q_37", "37) laugh", $this->answer_options);
        
        
        $this->form->addElement("select", "q_38", "38) splash or kick", $this->answer_options);
        
        
        $this->form->addElement("select", "q_39", "39) turn body and/or squirm", $this->answer_options);
        $this->form->addElement('static', null, "When face was washed, how often did the baby : ");
        
        
        $this->form->addElement("select", "q_40", "40) smile or laugh", $this->answer_options);
        
        
        $this->form->addElement("select", "q_41", "41) fuss or cry", $this->answer_options);
        
        
        $this->form->addElement("select", "q_42", "42) coo", $this->answer_options);
        $this->form->addElement('static', null, "When hair was washed, how often did the baby : ");
        
        
        $this->form->addElement("select", "q_43", "43) smile", $this->answer_options);
        
        
        $this->form->addElement("select", "q_44", "44) fuss or cry", $this->answer_options);
        
        
        $this->form->addElement("select", "q_45", "45) vocalize", $this->answer_options);
        
        $this->form->addElement('header', null, "Play");
        $this->form->addElement('static', null, "How often during the last week did the baby : ");
        
        
        $this->form->addElement("select", "q_46", "46) look at pictures in books and/or magazines for 2-5 minutes at a time? ", $this->answer_options);
        
        
        $this->form->addElement("select", "q_47", "47) look at pictures in books and/or magazines for 5 minutes or longer at a time? ", $this->answer_options);
        
        
        $this->form->addElement("select", "q_48", "48) stare at a mobile, crib bumper or picture for 5 minutes or longer? ", $this->answer_options);
        
        
        $this->form->addElement("select", "q_49", "49) play with one toy or object for 5-10 minutes", $this->answer_options);
        
        
        $this->form->addElement("select", "q_50", "50) play with one toy or object for 10 minutes or longer", $this->answer_options);
        
        
        $this->form->addElement("select", "q_51", "51) spend time just looking at playthings", $this->answer_options);
        
        
        $this->form->addElement("select", "q_52", "52) repeat the same sounds over and over again", $this->answer_options);
        
        
        $this->form->addElement("select", "q_53", "53) laugh aloud in play", $this->answer_options);
        
        
        $this->form->addElement("select", "q_54", "54) repeat the same movement with an object for 2 minutes or longer", $this->answer_options);
        
        
        $this->form->addElement("select", "q_55", "55) pay attention to your reading during most of the story when looking at picture books? ", $this->answer_options);
        
        
        $this->form->addElement("select", "q_56", "56) smile or laugh after accomplishing something (e.g., stacking blocks, etc.)? ", $this->answer_options);
        
        
        $this->form->addElement("select", "q_57", "57) smile or laugh when given a toy", $this->answer_options);
        
        
        $this->form->addElement("select", "q_58", "58) smile or laugh when tickled", $this->answer_options);
        $this->form->addElement('static', null, "How often during the last week did the baby enjoy : ");
        
        
        $this->form->addElement("select", "q_59", "59) being sung to", $this->answer_options);
        
        
        $this->form->addElement("select", "q_60", "60) being read to", $this->answer_options);
        
        
        $this->form->addElement("select", "q_61", "61) hearing the sound of words, as in nursery rhymes", $this->answer_options);
        
        
        $this->form->addElement("select", "q_62", "62) looking at picture books", $this->answer_options);
        
        
        $this->form->addElement("select", "q_63", "63) gentle rhythmic activities, such as rocking or swaying", $this->answer_options);
        
        
        $this->form->addElement("select", "q_64", "64) lying quietly and examining his/her fingers or toes", $this->answer_options);
        
        
        $this->form->addElement("select", "q_65", "65) being tickled by you or someone else in your family", $this->answer_options);
        
        
        $this->form->addElement("select", "q_66", "66) being involved in rambunctious play", $this->answer_options);
        
        
        $this->form->addElement("select", "q_67", "67) watching while you, or another adult, playfully made faces? ", $this->answer_options);
        
        
        $this->form->addElement("select", "q_68", "68) touching or lying next to stuffed animals", $this->answer_options);
        
        
        $this->form->addElement("select", "q_69", "69) the feel of soft blankets ", $this->answer_options);
        
        
        $this->form->addElement("select", "q_70", "70) being rolled up in a warm blanket", $this->answer_options);
        
        
        $this->form->addElement("select", "q_71", "71) listening to a musical toy in a crib", $this->answer_options);
        $this->form->addElement('static', null, "When playing quietly with one of her/his favorite toys, how often did your baby : ");
        
        
        $this->form->addElement("select", "q_72", "72) show pleasure", $this->answer_options);
        
        
        $this->form->addElement("select", "q_73", "73) enjoy lying in the crib for more than 5 minutes", $this->answer_options);
        
        
        $this->form->addElement("select", "q_74", "74) enjoy lying in the crib for more than 10 minutes", $this->answer_options);
        $this->form->addElement('static', null, "When something the baby was playing with had to be removed, how often did s/he : ");
        
        
        $this->form->addElement("select", "q_75", "75) cry or show distress for a time", $this->answer_options);
        
        
        $this->form->addElement("select", "q_76", "76) seem not bothered", $this->answer_options);
        $this->form->addElement('static', null, "When tossed around playfully how often did the baby : ");
        
        
        $this->form->addElement("select", "q_77", "77) smile", $this->answer_options);
        
        
        $this->form->addElement("select", "q_78", "78) laugh", $this->answer_options);
        $this->form->addElement('static', null, "During a peek-a-boo game, how often did the baby : ");
        
        
        $this->form->addElement("select", "q_79", "79) smile", $this->answer_options);
        
        
        $this->form->addElement("select", "q_80", "80) laugh", $this->answer_options);
        $this->form->addElement('static', null, "How often did your baby enjoy bouncing up and down : ");
        
        
        $this->form->addElement("select", "q_81", "81) while on your lap", $this->answer_options);
        
        
        $this->form->addElement("select", "q_82", "82) on an object, such as a bed, bouncer chair, or toy", $this->answer_options);
        $this->form->addElement('static', null, "How often did the infant look up from playing : ");
        
        
        $this->form->addElement("select", "q_83", "83) when the telephone rang", $this->answer_options);
        
        
        $this->form->addElement("select", "q_84", "84) when s/he heard voices in the next room", $this->answer_options);
        $this->form->addElement('static', null, "When your baby saw a toy s/he wanted, how often did s/he:: ");
        
        
        $this->form->addElement("select", "q_85", "85) get very excited about getting it", $this->answer_options);
        
        
        $this->form->addElement("select", "q_86", "86) immediately go after it", $this->answer_options);
        $this->form->addElement('static', null, "When given a new toy, how often did your baby : ");
        
        
        $this->form->addElement("select", "q_87", "87) get very excited about getting it", $this->answer_options);
        
        
        $this->form->addElement("select", "q_88", "88) immediately go after it", $this->answer_options);
        
        
        $this->form->addElement("select", "q_89", "89) seem not to get very excited about it", $this->answer_options);
        
            
    }
    
    function _page3(){
        
        $this->form->addElement('header', null, "Daily Activities");
        $this->form->addElement('static', null, "How often during the last week did the baby : ");
        
        
        $this->form->addElement("select", "q_90", "90) cry or show distress at a change in parents? appearance, (glasses off, shower cap on, etc.)? ", $this->answer_options);
        
        
        $this->form->addElement("select", "q_91", "91) when in a position to see the television set, look at it for 2 to 5 minutes at a time? ", $this->answer_options);
        $this->form->addElement('static', null, "How often during the last week did the baby : ");
        
        
        $this->form->addElement("select", "q_92", "92) when in a position to see the television set, look at it for 5 minutes or longer? ", $this->answer_options);
        
        
        $this->form->addElement("select", "q_93", "93) protest being placed in a confining place (infant seat, play pen, car seat, etc)? ", $this->answer_options);
        
        
        $this->form->addElement("select", "q_94", "94) startle at a sudden change in body position (for example, when moved suddenly)? ", $this->answer_options);
        
        
        $this->form->addElement("select", "q_95", "95) appear to listen to even very quiet sounds", $this->answer_options);
        
        
        $this->form->addElement("select", "q_96", "96) attend to sights or sounds when outdoors (for example, wind chimes or water sprinklers)? ", $this->answer_options);
        
        
        $this->form->addElement("select", "q_97", "97) move quickly toward new objects", $this->answer_options);
        
        
        $this->form->addElement("select", "q_98", "98) show a strong desire for something s/he wanted", $this->answer_options);
        
        
        $this->form->addElement("select", "q_99", "99) startle to a loud or sudden noise", $this->answer_options);
        
        
        $this->form->addElement("select", "q_100", "100) look at children playing in the park or on the playground for 5 minutes or longer? ", $this->answer_options);
        
        
        $this->form->addElement("select", "q_101", "101) watch adults performing household activities (e.g., cooking, etc.) for more than 5 minutes? ", $this->answer_options);
        
        
        $this->form->addElement("select", "q_102", "102) squeal or shout when excited", $this->answer_options);
        
        
        $this->form->addElement("select", "q_103", "103) imitate the sounds you made", $this->answer_options);
        
        
        $this->form->addElement("select", "q_104", "104) seem excited when you or other adults acted in an excited manner around him/her? ", $this->answer_options);
        $this->form->addElement('static', null, "When being held, how often did the baby : ");
        
        
        $this->form->addElement("select", "q_105", "105) pull away or kick", $this->answer_options);
        
        
        $this->form->addElement("select", "q_106", "106) seem to enjoy him/herself", $this->answer_options);
        
        
        $this->form->addElement("select", "q_107", "107) mold to your body", $this->answer_options);
        
        
        $this->form->addElement("select", "q_108", "108) squirm", $this->answer_options);
        $this->form->addElement('static', null, "When placed on his/her back, how often did the baby : ");
        
        
        $this->form->addElement("select", "q_109", "109) fuss or protest", $this->answer_options);
        
        
        $this->form->addElement("select", "q_110", "110) smile or laugh", $this->answer_options);
        
        
        $this->form->addElement("select", "q_111", "111) wave arms and kick", $this->answer_options);
        
        
        $this->form->addElement("select", "q_112", "112) squirm and/or turn body", $this->answer_options);
        $this->form->addElement('static', null, "When the baby wanted something, how often did s/he : ");
        
        
        $this->form->addElement("select", "q_113", "113) become upset when s/he could not get what s/he wanted", $this->answer_options);
        
        
        $this->form->addElement("select", "q_114", "114) have tantrums (crying, screaming, face red, etc.) when s/he did not get what s/he", $this->answer_options);
        $this->form->addElement('static', null, "When placed in an infant seat or car seat, how often did the baby : ");
        
        
        $this->form->addElement("select", "q_115", "115) wave arms and kick", $this->answer_options);
        
        
        $this->form->addElement("select", "q_116", "116) squirm and turn body", $this->answer_options);
        
        
        $this->form->addElement("select", "q_117", "117) lie or sit quietly", $this->answer_options);
        
        
        $this->form->addElement("select", "q_118", "118) show distress at first; then quiet down", $this->answer_options);
        $this->form->addElement('static', null, "When frustrated with something, how often did your baby : ");
        
        
        $this->form->addElement("select", "q_119", "119) calm down within 5 minutes", $this->answer_options);
        $this->form->addElement('static', null, "When your baby was upset about something, how often did s/he : ");
        
        
        $this->form->addElement("select", "q_120", "120) stay upset for up to 10 minutes or longer", $this->answer_options);
        
        
        $this->form->addElement("select", "q_121", "121) stay upset for up to 20 minutes or longer", $this->answer_options);
        
        
        $this->form->addElement("select", "q_122", "122) soothe her/himself with other things (such as a stuffed animal, or", $this->answer_options);
        $this->form->addElement('static', null, "When rocked or hugged, in the last week, how often did your baby : ");
        
        
        $this->form->addElement("select", "q_123", "123) seem to enjoy her/himself", $this->answer_options);
        
        
        $this->form->addElement("select", "q_124", "124) seemed eager to get away", $this->answer_options);
        
        
        $this->form->addElement("select", "q_125", "125) make protesting noises", $this->answer_options);
        $this->form->addElement('static', null, "When reuniting after having been away during the last week how often did the baby : ");
        
        
        $this->form->addElement("select", "q_126", "126) seem to enjoy being held", $this->answer_options);
        
        
        $this->form->addElement("select", "q_127", "127) show interest in being close, but resisted being held", $this->answer_options);
        
        
        $this->form->addElement("select", "q_128", "128) show distress at being held", $this->answer_options);
        $this->form->addElement('static', null, "When being carried, in the last week, how often did your baby : ");
        
        
        $this->form->addElement("select", "q_129", "129) seem to enjoy him/herself", $this->answer_options);
        
        
        $this->form->addElement("select", "q_130", "130) push against you until put down", $this->answer_options);
        $this->form->addElement('static', null, "While sitting in your lap : ");
        
        
        $this->form->addElement("select", "q_131", "131) how often did your baby seem to enjoy her/himself", $this->answer_options);
        
        
        $this->form->addElement("select", "q_132", "132) how often would the baby not be content without moving around", $this->answer_options);
        $this->form->addElement('static', null, "How often did your baby notice : ");
        
        
        $this->form->addElement("select", "q_133", "133) low-pitched noises, air conditioner, heating system, or refrigerator running or starting", $this->answer_options);
        
        
        $this->form->addElement("select", "q_134", "134) sirens from fire trucks or ambulances at a distance", $this->answer_options);
        
        
        $this->form->addElement("select", "q_135", "135) a change in room temperature", $this->answer_options);
        
        
        $this->form->addElement("select", "q_136", "136) a change in light when a cloud passed over the sun", $this->answer_options);
        
        
        $this->form->addElement("select", "q_137", "137) sound of an airplane passing overhead", $this->answer_options);
        
        
        $this->form->addElement("select", "q_138", "138) a bird or a squirrel up in a tree", $this->answer_options);
        
        
        $this->form->addElement("select", "q_139", "139) fabrics with scratchy texture (e.g., wool)", $this->answer_options);
        $this->form->addElement('static', null, "When tired, how often was your baby : ");
        
        
        $this->form->addElement("select", "q_140", "140) likely to cry", $this->answer_options);
        
        
        $this->form->addElement("select", "q_141", "141) show distress", $this->answer_options);
        $this->form->addElement('static', null, "At the end of an exciting day, how often did your baby : ");
        
        
        $this->form->addElement("select", "q_142", "142) become tearful", $this->answer_options);
        
        
        $this->form->addElement("select", "q_143", "143) show distress", $this->answer_options);
        $this->form->addElement('static', null, "For no apparent reason, how often did your baby : ");
        
        
        $this->form->addElement("select", "q_144", "144) appear sad", $this->answer_options);
        
        
        $this->form->addElement("select", "q_145", "145) seem unresponsive ", $this->answer_options);
        $this->form->addElement('static', null, "How often did your baby make talking sounds when : ");
        
        
        $this->form->addElement("select", "q_146", "146) riding in a car", $this->answer_options);
        
        
        $this->form->addElement("select", "q_147", "147) riding in a shopping cart", $this->answer_options);
        
        
        $this->form->addElement("select", "q_148", "148) you talked to her/him", $this->answer_options);
        
            
    }
    
    function _page4(){
        
        $this->form->addElement('header', null, "Two Week Time Span");
        $this->form->addElement('static', null, "When you returned from having been away and the baby was awake, how often did s/he : ");
        
        
        $this->form->addElement("select", "q_149", "149) smile or laugh", $this->answer_options);
        $this->form->addElement('static', null, "When introduced to an unfamiliar adult, how often did the baby : ");
        
        
        $this->form->addElement("select", "q_150", "150) cling to a parent", $this->answer_options);
        
        
        $this->form->addElement("select", "q_151", "151) refuse to go to the unfamiliar person", $this->answer_options);
        
        
        $this->form->addElement("select", "q_152", "152) hang back from the adult", $this->answer_options);
        
        
        $this->form->addElement("select", "q_153", "153) never ?warm up? to the unfamiliar adult", $this->answer_options);
        $this->form->addElement('static', null, "When in the presence of several unfamiliar adults, how often did the baby : ");
        
        
        $this->form->addElement("select", "q_154", "154) cling to a parent", $this->answer_options);
        
        
        $this->form->addElement("select", "q_155", "155) cry", $this->answer_options);
        
        
        $this->form->addElement("select", "q_156", "156) continue to be upset for 10 minutes or longer", $this->answer_options);
        $this->form->addElement('static', null, "When visiting a new place, how often did the baby : ");
        
        
        $this->form->addElement("select", "q_157", "157) show distress for the first few minutes", $this->answer_options);
        
        
        $this->form->addElement("select", "q_158", "158) continue to be upset for 10 minutes or more", $this->answer_options);
        
        
        $this->form->addElement("select", "q_159", "159) get excited about exploring new surroundings", $this->answer_options);
        
        
        $this->form->addElement("select", "q_160", "160) move about actively when s/he is exploring new", $this->answer_options);
        $this->form->addElement('static', null, "When your baby was approached by an unfamiliar person when you and s/he were out (for example, shopping), how often did the baby : ");
        
        
        $this->form->addElement("select", "q_161", "161)  show distress", $this->answer_options);
        
        
        $this->form->addElement("select", "q_162", "162)  cry", $this->answer_options);
        $this->form->addElement('static', null, "When an unfamiliar adult came to your home or apartment, how often did your baby : ");
        
        
        $this->form->addElement("select", "q_163", "163) allow her/himself to be  picked up without protest", $this->answer_options);
        
        
        $this->form->addElement("select", "q_164", "164) cry when the visitor attempted to pick her/him up", $this->answer_options);
        $this->form->addElement('static', null, "When in a crowd of people, how often did the baby : ");
        
        
        $this->form->addElement("select", "q_165", "165) seem to enjoy him/herself", $this->answer_options);
        $this->form->addElement('static', null, "Did the baby seem sad when : ");
        
        
        $this->form->addElement("select", "q_166", "166) caregiver is gone for an unusually long period of time", $this->answer_options);
        
        
        $this->form->addElement("select", "q_167", "167) left alone/unattended in a crib or a playpen for an extended period of time?", $this->answer_options);
        $this->form->addElement('static', null, "When you were busy with another activity, and your baby was not able to get your attention, how often did s/he : ");
        
        
        $this->form->addElement("select", "q_168", "168) become sad", $this->answer_options);
        
        
        $this->form->addElement("select", "q_169", "169) cry", $this->answer_options);
        $this->form->addElement('static', null, "When your baby saw another baby crying, how often did s/he:: ");
        
        
        $this->form->addElement("select", "q_170", "170) become tearful", $this->answer_options);
        
        
        $this->form->addElement("select", "q_171", "171) show distress", $this->answer_options);
        $this->form->addElement('static', null, "When familiar relatives/friends came to visit, how often did your baby : ");
        
        
        $this->form->addElement("select", "q_172", "172) get excited", $this->answer_options);
        
        
        $this->form->addElement("select", "q_173", "173) seem indifferent", $this->answer_options);
        
            
    }
    
    function _page5(){
        $this->form->addElement('header', null, "Soothing Techniques");
        $this->form->addElement('static', null, "Have you tried any of the following soothing techniques in the last two weeks? If  so, how quickly did your baby soothe using each of these techniques? Circle (X) if not tried in the LAST TWO WEEKS.");
        
		$this->form->addElement('static', null, "When rocking your baby, how often did s/he : ");
        
        $this->form->addElement("select", "q_174", "174) soothe immediately", $this->answer_options);
        
        
        $this->form->addElement("select", "q_175", "175) not soothe immediately, but in the first two minutes", $this->answer_options);
        
        
        $this->form->addElement("select", "q_176", "176) take more than 10 minutes to soothe", $this->answer_options);
        $this->form->addElement('static', null, "When singing or talking to your baby, how often did s/he : ");
        
        
        $this->form->addElement("select", "q_177", "177) soothe immediately", $this->answer_options);
        
        
        $this->form->addElement("select", "q_178", "178) not soothe immediately, but in the first two minutes", $this->answer_options);
        
        
        $this->form->addElement("select", "q_179", "179) take more than 10 minutes to soothe", $this->answer_options);
        $this->form->addElement('static', null, "When walking with the baby, how often did s/he : ");
        
        
        $this->form->addElement("select", "q_180", "180) soothe immediately", $this->answer_options);
        
        
        $this->form->addElement("select", "q_181", "181) not soothe immediately, but in the first two minutes", $this->answer_options);
        
        
        $this->form->addElement("select", "q_182", "182) take more than 10 minutes to soothe", $this->answer_options);
        $this->form->addElement('static', null, "When giving him/her a toy, how often did the baby : ");
        
        
        $this->form->addElement("select", "q_183", "183) soothe immediately", $this->answer_options);
        
        
        $this->form->addElement("select", "q_184", "184) not soothe immediately, but in the first two minutes", $this->answer_options);
        
        
        $this->form->addElement("select", "q_185", "185) take more than 10 minutes to soothe", $this->answer_options);
        $this->form->addElement('static', null, "When showing the baby something to look at, how often did s/he : ");
        
        
        $this->form->addElement("select", "q_186", "186) soothe immediately", $this->answer_options);
        
        
        $this->form->addElement("select", "q_187", "187) not soothe immediately, but in the first two minutes", $this->answer_options);
        
        
        $this->form->addElement("select", "q_188", "188) take more than 10 minutes to soothe", $this->answer_options);
        $this->form->addElement('static', null, "When patting or gently rubbing some part of the baby's body, how often did s/he : ");
        
        
        $this->form->addElement("select", "q_189", "189) soothe immediately", $this->answer_options);
        
        
        $this->form->addElement("select", "q_190", "190) not soothe immediately, but in the fist two minutes", $this->answer_options);
        
        
        $this->form->addElement("select", "q_191", "191) take more than 10 minutes to soothe", $this->answer_options);
        
    } // end function _setupForm
        
}
?>
