<?php

require_once('RequiredIfGroup.inc');
require_once('RequiredIf.inc');
require_once 'HTML/QuickForm.php';
require_once 'HTML/QuickForm/Renderer/Array.php';

class NDB_BVL_Instrument_DSMIV_checklist extends NDB_BVL_Instrument
{
   
    var $yesNo = array(null=>"", 'yes'=>"Yes", 'no'=>"No");
    var $confidence = array(null=>"", 'very_confident'=>"Very Confident", 'somewhat_confident'=>"Somewhat Confident", 'not_confident'=>"Not Confident");

    var $ValidityEnabled = false;
    var $ValidityRequired = false;


    /**
    * sets up basic data, such as the HTML_Quickform object, and so on.
    *
    * @param string $page       if a multipage form, the page to show
    * @return void
    * @access public
    */
    function setup($commentID, $page){
        $this->formType="XIN";
        $this->form = new HTML_Quickform('DSMIV_checklist');
        $this->page = $page;            // page label (number or
        // string - used by
	// user-defined child classes)

        // set the object properties
        $this->testName = "DSMIV_checklist";           // test_names.Test_name
        $this->table = 'DSMIV_checklist';              // name of database table corresponding to instrument
	
        // data keyed by commentID
        $this->commentID = $commentID;

        //The array of dates/timestamps to convert to database dates/timestamps
        //Any HTML_Quickform date elements must be listed here
        $this->dateTimeFields=array("Date_taken", "date_taken_diagnostic_assessor", "date_taken_confirming_clinician");

        $this->_requiredElements = array('Examiner', 'Date_taken', 'q3d_preoccupation_objects', 'q4_criteria_autistic_disorder');


        $config =& NDB_Config::singleton();
        $this->dateOptions = array(
        'language' => 'en',
        'format'   => 'YMd',
        'minYear'  => $config->getSetting('startYear'), //allows for siblings up to 20 years older than candidate
        'maxYear'  => $config->getSetting('endYear'),
        'addEmptyOption' => true,
        'emptyOptionValue' => null
		);
        /**
         * Array of column names to be ignored by the double data entry conflict detector.
         */
        $this->_doubleDataEntryDiffIgnoreColumns = array('CommentID', 'UserID', 'Testdate', 'Window_Difference', 'Candidate_Age',
            'q4b_not_ASD_specify',
            'q4b_not_ASD_specify_status',
            'confidence_rating_specify',
    //            'confidence_rating_specify_status',
    //            'date_taken_assessor_date_status',
    //            'date_taken_confirming_clinician_date_status',
            'dsm_asd_comments_status',
            'dsm_scd_comments_status',
            'Data_entry_completion_status',
            'name_assessor',
            'name_confirming_clinician',
            'equivocal_evaluation_results_specify'
        );

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

        //determine page to display
        if(preg_match("/DSMIV_checklist(_page[1-9]+)/",$this->page,$matches)){
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
        $this->form->addElement('header', 'instrument_title', "DSM-IV Autistic Disorder Checklist");

        // automatically adds examiner & date of administration
        $this->_addMetadataFields();
      }

function _page1()
{
	
	  //Autistic Disorder Criteria
        $this->form->addElement('header', null, "Autistic Disorder Criteria");
        $this->form->addElement("static", null, "<BR>"); //line space

        $this->form->addElement("static", null, "<strong>1. Qualitative impairment in social interaction, as indicated by: </strong><BR>"); //line space
        
        $this->form->addElement("select", "q1a_impairment_non_verbal_behaviors", "a. Marked impairment in the use of multiple nonverbal behaviors such as eye contact, facial expression, body postures, and gestures to regulate social interaction (May interpret as diminished use of multiple nonverbal behaviors).", $this->yesNo);
        
        $this->form->addElement("select", "q1b_failure_develop_relationships", "<BR> b. Failure to develop peer relationships appropriate to developmental level. (Interpret as failure to develop interest in peers/siblings/other children e.g., a child with an older sibling who shows no interest or responsiveness to him/her, indifference to children, not watching others on the playground, etc.)", $this->yesNo);
        
        $this->form->addElement("select", "q1c_lack_spontaneous_enjoyment", "<BR> c. Lack of spontaneous seeking to share enjoyment, interests or achievements with other people (Interpret as diminished; e.g., lack of showing, bringing, or pointing out objects of interest.)", $this->yesNo);
        
        $this->form->addElement("select", "q1d_lack_social_reciprocity", "<BR> d. Lack of social-emotional reciprocity. (Interpret as diminished; look for enjoyment & participation in imitative games, turn-taking, offering comfort, sharing, chatting.)", $this->yesNo);
        
        $this->form->addElement("static", null, "<BR><strong>2. Qualitative impairments in communication, as indicated by:</strong>"); 
                
        $this->form->addElement("select", "q2a_development_spoken_language", "<BR> a. Delay in, or total lack of, the development of spoken language (not accompanied by an attempt to compensate through alternative modes of communication such as gesture).", $this->yesNo);
        
          $this->form->addElement("select", "q2b_impairment_conversation", "<BR> b. In individuals with adequate speech, marked impairment in the ability to initiate or sustain a conversation with others. (For infants/toddlers, reciprocal babble with parent/others that has a conversational feel can be counted.)", array(null=>"", 'yes'=>"Yes", 'no'=>"No", "not_applicable"=>"Not Applicable"));
          
          $this->form->addElement("select", "q2c_use_language", "<BR> c. Stereotyped and repetitive use of language or idiosyncratic language.", $this->yesNo);
        
          $this->form->addElement("select", "q2d_lack_play", "<BR> d. Lack of varied, spontaneous make-believe play or social imitative play appropriate to developmental level. (Interpret as diminished; make-believe play evaluated by taking into account child's developmental level; may be interpreted as social imitative play in child with NVMAs below roughly 18 months.) ", $this->yesNo);
        
          $this->form->addElement("static", null, "<BR><strong>3. Restricted repetitive and stereotyped patterns of behavior, interests and activities, as indicated by:</strong>"); 
                
        $this->form->addElement("select", "q3a_preoccupation_patterns", "<BR> a. Encompassing preoccupation with one or more stereotyped and restricted patterns of interest that is abnormal in either intensity or focus.", $this->yesNo);
        
        $this->form->addElement("select", "q3b_adherence_routines", "<BR> b. Apparently inflexible adherence to specific, nonfunctional routines or rituals (e.g., lining things up or putting in specific order).", $this->yesNo);
        
          $this->form->addElement("select", "q3c_motor_mannerisms", "<BR> c. Stereotyped and repetitive motor mannerisms (e.g., hand or finger flapping, complex whole-body movements).", $this->yesNo);
        
         $this->form->addElement("select", "q3d_preoccupation_objects", "<BR> d. Persistent preoccupation with parts of objects or sensory qualities of objects.", $this->yesNo);

         $this->form->addElement("static", null, "<BR>"); //line space
    }
        
function _page2(){
  
  $config =& NDB_Config::singleton();
       $dateOptions = array(
      'language' => 'en',
      'format'   => 'YMd',
      'minYear'  => $config->getSetting('startYear'), //allows for siblings up to 20 years older than candidate
      'maxYear'  => $config->getSetting('endYear'),
      'addEmptyOption' => true,
      'emptyOptionValue' => null
	     );
        
            $this->form->addElement('header', null, "Autistic Disorder Criteria Continued");
             $this->form->addElement("static", null, "<BR>"); //line space
           
             $this->form->addElement("select", "q4_criteria_autistic_disorder", "<BR><strong> Does he or she meet the DSM-IV Criteria for Autistic Disorder: </strong> <BR> Total of at least 6 symptoms: <BR> $this->indent -At least 2 from category 1 <BR> $this->indent  -At least 1 from category 2 <BR> $this->indent -At least 1 from category 3 <BR> $this->indent -Onset before age 3 <BR> $this->indent -No other explanation<BR>", $this->yesNo);
        
            $this->form->addElement("select", "q4_criteria_PDD", "<BR> <strong> Does he/she meet DSM-IV Criteria for Pervasive Developmental Disorder-Not Otherwise Specified? </strong> <BR> Total of at least 3 symptoms: <BR> $this->indent -At least 1 from category 1 <BR> $this->indent  (\"Failure to develop peer relationships..\" may NOT be the only category 1 item) <BR> $this->indent -No other explanation <BR>", array(NULL=>"", "yes"=>"Yes", "no"=>"No or Meets criteria for Autism"));
            
            $this->form->addElement('text', "q4b_not_ASD_specify", "Note: If the child does <strong>NOT</strong> meet criteria for an ASD, specify other dx/comment:"); 
            
           $this->XINRegisterRule("q4b_not_ASD_specify", array("q4_criteria_autistic_disorder{@}=={@}no"), "This field is required.");          	
            
            
            $this->form->addElement("static", null, "<BR>"); //line space

            $this->form->addElement("static", null, "<strong>Confidence Rating </strong><BR>");
            
          
            $this->form->addElement("select", "confidence_rating", "Given all the data that you have on this child, how confident are you about the classification of this child?", $this->confidence);
            
                      
            $this->addTextAreaElement("confidence_rating_specify", "Please comment for a rating of <strong>Somewhat Confident</strong> or <strong>Not Confident</strong>", array("confidence_rating{@}=={@}somewhat_confident|not_confident"), "This field is required or specify not answered."); 
            
            $this->form->addElement("static", null, "<BR>"); //line space
            
         
             $this->form->addElement("static", null, "<strong> Diagnostic Consensus </strong> <BR> This form confirms that this participant, based on clinical judgment and ADOS scores has been evaluated for an autism spectrum disorder.");
         
         	$this->form->addElement('text', "name_assessor", "<BR> Name of Diagnostic Assessor:");
                 
    	    $this->addDateElement('date_taken_assessor', "Date:");
        
                     
 $this->form->addElement("select", "confirmed_diagnosis", "<BR>A clinician, through live observation or video review confirms the status of the participant stated above. The clinician agrees with the assessor's diagnostic decision.", $this->yesNo);

           	$this->form->addElement('text', "name_confirming_clinician", "Name of Confirming Clinician:");

          	$this->addDateElement("date_taken_confirming_clinician", "Date:", $dateOptions);
          	
            $this->XINRegisterRule("name_confirming_clinician", array("confirmed_diagnosis{@}=={@}yes|no"), "Please enter the name of the confirming clinician and the date confirmed.");          	
          	
          	 $this->XINRegisterRule("date_taken_confirming_clinician", array("confirmed_diagnosis{@}=={@}yes|no"), "Please enter the date");          	

             $this->form->addElement("static", null, "<BR>"); //line space
            
    }
}

?>
