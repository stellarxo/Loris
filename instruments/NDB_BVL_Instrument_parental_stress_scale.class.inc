<?php

require_once 'HTML/QuickForm.php';
require_once 'HTML/QuickForm/Renderer/Array.php';

class NDB_BVL_Instrument_parental_stress_scale extends NDB_BVL_Instrument
{
    /**
    * sets up basic data, such as the HTML_Quickform object, and so on.
    *
    * @param string $commentID  the CommentID identifying the data to load
    * @param string $page       if a multipage form, the page to show
    * @return void
    * @access public
    */
    function setup($commentID, $page){
        //INSERT INTO instrument_subtests VALUES('', 'parental_stress_scale', 'parental_stress_scale_page1', 'Page1', 1);
       //INSERT INTO test_names(Test_name, Full_name,Sub_group,isDirectEntry) VALUES ('parental_stress_scale','Parental Stress Scales',6, true);
        $this->formType="XIN";
        $this->form = new HTML_Quickform('test_form');
        $this->page = $page;            // page label (number or
        // string - used by
        // user-defined child classes)
        $config = NDB_Config::singleton();
        $this->dateOptions = array(
                                'language' => 'en',
                                'format'   => 'YMd', 
                                'minYear'  => $config->getSetting('startYear'),
                                'maxYear'  => $config->getSetting('endYear'),
                                'addEmptyOption' => true,
                                'emptyOptionValue' => null
                                );

        // set the object properties
        $this->testName = "parental_stress_scale";           // test_names.Test_name
        $this->table = 'parental_stress_scale';              // name of database table corresponding to instrument
        // data keyed by commentID
        $this->commentID = $commentID;

        //The array of dates/timestamps to convert to database dates/timestamps
        //Any HTML_Quickform date elements must be listed here
        $this->dateTimeFields=array("Date_taken");

        //The array of selects with multiple answers allowed
        //Any HTML_Quickform multiple selects must be listed here
        $this->_selectMultipleElements = array();

        // required fields for data entry completion status
        $this->_requiredElements = array('Examiner', 'q1_happy_parent');

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
      if(preg_match("/parental_stress_scale(_page[0-9]+)/",$this->page,$matches)){
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
        $this->addHeader("Parental Stress Scale");

        //  date of administration
        $this->addDateElement('Date_taken', 'Date administered :', $this->dateOptions);
        $visit_list = array(''=>'Choose one');
        $visit_list = array_merge($visit_list,
                                  Utility::getExistingVisitLabels(),
                                  array('not_answered'=>'Not Answered')
                                  );
        $this->addSelect('visit', 'Visit :', $visit_list);

        $this->addTextElement('person_interviewed', 'Person Interviewed :');
        $this->addTextElement('interviewed_by', 'Interviewed by :');

        $recording_device = array(''=>'Choose one', 'audio'=>'Audio','video'=>'Video');
        $this->addSelect('recording_device', 'Please choose type of recording used :', $recording_device);
        $this->addTextAreaElement('comments', 'Comments :');

        $this->addScoreColumn('parent_scale_score', 'Parent Stress Scale Score :');
    }

    function _page1(){
        $this->addHeader("Parental Stress Scale - Page 1");

        $this->form->addElement('static','lorisSubHeader',"The following statements describe feelings and perceptions about the experience of being a parent. <BR>Think of each of the items in terms of how your relationship with your child or children typically is. <BR>Please indicate the degree to which you agree or disagree with the following items by placing the <BR>appropriate number in the space provided.");
        $this->form->addElement("static", null, "&nbsp;");
        $scale = array(''=>'Choose one', '1_strongly_disagree'=>'1-Strongly Disagree',
                       '2_disagree'=>'2-Disagree','3_undecided'=>'3-Undecided',
                       '4_agree'=>'4-Agree','5_strongly_agree'=>'5-Strongly Agree',
                       'refused_dontknow'=>"Refused/I Don't Know");

        $question_list = array('q1_happy_parent'=>'1. I am happy in my role as a parent.',
                               'q2_do_for_children'=>'2. There is little or nothing I wouldn\'t do for my child(ren) if it was necessary.',
                               'q3_caring_takes_more_energy'=>'3. Caring for my child(ren) sometimes takes more time and energy than I have to give.',
                               'q4_worry_doing_enough'=>'4. I sometimes worry whether I am doing enough for my child(ren).',
                               'q5_close_to_children'=>'5. I feel close to my child(ren).',
                               'q6_enjoy_spending_time'=>'6. I enjoy spending time with my child(ren).',
                               'q7_imp_affection'=>'7. My child(ren) is an important source of affection for me.',
                               'q8_optimistic_future'=>'8. Having child(ren) gives me a more certain and optimistic view for the future.',
                               'q9_major_stress'=>'9. The major source of stress in my life is my child(ren).',
                               'q10_notime_flexibility'=>'10. Having child(ren) leaves little time and flexibility in my life.',
                               'q11_financial_burden'=>'11. Having child(ren) has been a financial burden.',
                               'q12_diff_balance_responsibilities'=>'12. It is difficult to balance different responsibilities because of my child(ren).',
                               'q13_embarassing_stressful'=>'13. The behavior of my child(ren) is often embarrassing or stressful to me.',
                               'q14_decide_no_children'=>'14. If I had it to do over again, I might decide not to have child(ren).',
                               'q15_overwhelmed_as_parent'=>'15. I feel overwhelmed by the responsibility of being a parent.',
                               'q16_few_choices_no_control'=>'16. Having child(ren) has meant having too few choices and too little control over my life.',
                               'q17_satisfied_parent'=>'17. I am satisfied as a parent.',
                               'q18_children_enjoyable'=>'18. I find my child(ren) enjoyable.');

        foreach($question_list as $question=>$label) {
            $this->addSelect($question, $label, $scale);
        }
    }

    function score() {
        //get the saved scores
        $db = Database::singleton();

        $query  = "SELECT * FROM $this->table WHERE CommentID =:cid";
        $record = $db->pselectRow($query, array('cid'=>$this->commentID));

        $reverse_score = array('q1_happy_parent','q2_do_for_children',
                               'q5_close_to_children','q6_enjoy_spending_time','q7_imp_affection',
                               'q8_optimistic_future','q17_satisfied_parent','q18_children_enjoyable');
       $reverse_val = array(1=>5,2=>4,3=>3,4=>2,5=>1);
       $score = 0;
       foreach ($record as $key=>$value ) {

           if (strpos($key,'q') !== false ) {
               $temp = explode('_', $value);
               $int_val = intval($temp[0]);
               if (in_array($key, $reverse_score)) {
                   $int_val = $reverse_val[$int_val];
               }
               $score += $int_val;
           }

       }
       //print "SCORE - $score \n";
       $scores = array('parent_scale_score'=>$score);
       $result = $db->update($this->table, $scores, array("CommentID"=>$this->getCommentID()));
      }

}
?>
