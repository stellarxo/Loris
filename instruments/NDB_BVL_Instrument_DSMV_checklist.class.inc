<?php

require_once('RequiredIfGroup.inc');
require_once('RequiredIf.inc');
require_once 'HTML/QuickForm.php';
require_once 'HTML/QuickForm/Renderer/Array.php';

class NDB_BVL_Instrument_DSMV_checklist extends NDB_BVL_Instrument
{
   
    var $yesNo = array(null=>"", 'yes'=>"Yes", 'no'=>"No");
    var $asd_level = array(null=>"",'level3'=>'Level 3 - Requiring very substantial support','level2'=>'Level 2 - Requiring substantial support','level1'=>'Level 1 - Requiring support','no_support'=>'No Support Required','not_answered'=>'Not Answered');
    var $confidence = array(null=>"", '3_very_confident'=>"3-Very Confident", '2_somewhat_confident'=>"2-Somewhat Confident", '1_not_confident'=>"1-Not Confident");

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
        $this->form = new HTML_Quickform('DSMV_checklist');
        $this->page = $page;            // page label (number or
        // string - used by
	// user-defined child classes)

        // set the object properties
        $this->testName = "DSMV_checklist";           // test_names.Test_name
        $this->table = 'DSMV_checklist';              // name of database table corresponding to instrument
	
        // data keyed by commentID
        $this->commentID = $commentID;

        //The array of dates/timestamps to convert to database dates/timestamps
        //Any HTML_Quickform date elements must be listed here
        $this->dateTimeFields=array("Date_taken", "date_taken_diagnostic_assessor", "date_taken_confirming_clinician");

        $this->_requiredElements = array('Examiner', 'Date_taken', 'qa1_deficit_reciprocity','meet_dsm_asd','dsm5_confirmed_diagnosis');
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
        $this->_doubleDataEntryDiffIgnoreColumns = array('CommentID', 'UserID', 'Testdate', 'Window_Difference',
            'Candidate_Age',
            'dsm_asd_comments',
            'dsm_asd_comments_status',
            'dsm_scd_comments',
            'dsm_scd_comments_status',
            'Data_entry_completion_status'
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
        if(preg_match("/DSMV_checklist(_page[1-9]+)/",$this->page,$matches)){
            call_user_method($matches[1], $this);
        } else {
            $this->_main();
        }

        //Defines the call back function for HTML Quickform to use when validating the form.
        $this->form->addFormRule(array(&$this,'XINValidate'));
    }
  
    function getDataEntryCompletionStatus()
    {
        $db =& Database::singleton();
        $query_asd ="SELECT meet_dsm_asd FROM DSMV_checklist WHERE CommentID=:cid";
        $where = array('cid'=>$this->getCommentID());
        $result = $db->pselectOne($query_asd, $where);
        if($result == 'no') {
            $query = "SELECT qa1_deficit_communication_social FROM $this->table WHERE CommentID=:CID";
            $val   = $db->pselectOne($query,array('CID' => $this->getCommentID()));
            if(is_null($val) || $val === ""){ 
                return 'Incomplete';
             } else { 
                return 'Complete';   
              }

        } else {
            $query = "SELECT Data_entry_completion_status FROM $this->table WHERE CommentID=:CID";
            return $db->pselectOne($query, array('CID' => $this->getCommentID()));
        }
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
        $this->form->addElement('header', 'instrument_title', "DSM-V Autistic Disorder Checklist");

        // automatically adds examiner & date of administration
        $this->_addMetadataFields();
      }

function _page1()
{
	
	  //Autistic Disorder Criteria
        $this->form->addElement('header', null, "Autism Spectrum Disorder Checklist");
        $this->form->addElement("static", null, "<BR>"); //line space

        $this->form->addElement("static", null, "<strong>A. Persistent deficits in social communication and social interaction across contexts, not accounted for by general developmental delays, and manifests by all three of the following:</strong><BR>"); //line space
        
        $this->form->addElement("select", "qa1_deficit_reciprocity", "1.  deficits in social-emotional reciprocity; ranging from abnormal social approach and failure of normal back and forth conversation through reduced sharing of interests, emotions, affect and response to total lack of initiation of social interaction", $this->yesNo);
        
        $this->form->addElement("select", "qa2_deficit_nonverbal", "<BR> 2.  deficits in nonverbal communicative behaviors used for social interaction; ranging from poorly integrated verbal and nonverbal communication, through abnormalities in eye contact and body-language, or deficits in understanding and use of nonverbal communication, to total lack of facial expression or gestures.", $this->yesNo);
        
        $this->form->addElement("select", "qa3_deficit_relationships", "<BR> 3.  deficits in developing and maintaining relationships, appropriate to developmental level (beyond those with caregivers); ranging from difficulties adjusting behavior to suit different social contexts through difficulties in sharing imaginative play and in making friends, to an apparent absence of interest in people", $this->yesNo);
               
        $this->form->addElement("static", null, "<BR><strong>B.  Restricted, repetitive patterns of behavior, interests, or activities as manifested by at least two of the following: </strong>"); 
                
        $this->form->addElement("select", "qb1_stereotyped_speech", "<BR> 1.  stereotyped or repetitive speech, motor movements, or use of objects (such as simple motor stereotypies, echolalia, repetitive use of objects, or idiosyncratic phrases)", $this->yesNo);
        
        $this->form->addElement("select", "qb2_adherence_routine", "<BR> 2.  excessive adherence to routines, ritualized patterns of verbal or nonverbal behavior, or excessive resistance to change (such as motoric rituals, insistence on same route or food, repetitive questioning or extreme distress at small changes) ", $this->yesNo);
        $this->form->addElement("select", "qb3_restricted_interests", "<BR> 3.  highly restricted, fixated interests that are abnormal in intensity or focus (such as strong attachment to or preoccupation with unusual objects, excessively circumscribed or perseverative interests) ", $this->yesNo);

        $this->form->addElement("select", "qb4_hypohyper_reactsensory", "<BR> 4.  hyper-or hypo-reactivity to sensory input or unusual interest in sensory aspects of environment (such as apparent indifference to pain/heat/cold, adverse response to specific sounds or textures, excessive smelling or touching of objects, fascination with lights or spinning objects) ", $this->yesNo);

          $this->form->addElement("select", "c_symptoms_earlychildhood", "<BR><strong>C. Symptoms must be present in early childhood (but may not become fully manifest until social demands exceed limited capacities). </strong>", array(null=>"", 'yes'=>"Yes", 'no'=>"No", "not_applicable"=>"Not Applicable"));
        
          $this->form->addElement("select", "d_cause_social_impairment", "<BR><strong>D. Symptoms cause clinically significant impairment in social, occupational, or other important area of functioning</strong>", array(null=>"", 'yes'=>"Yes", 'no'=>"No", "not_applicable"=>"Not Applicable"));

         $this->form->addElement("static", null, "<BR><strong>E. These disturbances are not better explained by intellectual disability (intellectual development disorder) or global developmental delay. Intellectual disability and autism spectrum disorder frequently co-occur. To make a comorbid diagnoses of ASD and ID, social communication should be below that expected for general developmental level </strong>");
          
          $this->form->addElement("static", null, "<BR><strong>Severity Level for ASD</strong>"); 
                
        $this->form->addElement("select", "asdlevel_socialcommunication", "<BR> Social Communication", $this->asd_level);
        
        $this->form->addElement("select", "asdlevel_restricted_interest", "<BR> Restricted Interests & Repetitive Behavior", $this->asd_level);
        
          $this->form->addElement("select", "meet_dsm_asd", "<BR><strong>Meets DSM-V Criteria for Autism Spectrum Disorder</strong><BR>$this->indent - All symptoms in category A present<BR>$this->indent - At least two symptoms in category B<BR>$this->indent - Symptoms present in early childhood<BR>$this->indent - Symptoms not better explained by intellectual disability or global delay alone<BR>$this->indent - Significant impairment in social, occupational, or other area of functioning", $this->yesNo);
        
         $this->form->addElement("select", "dsm_asd_confidence", "<BR> <strong>Confidence rating.</strong>Given all the data that you have on this child, how confident are you about the classification of this child based on the DSM-V ASD criteria?", $this->confidence);
         
         $this->addTextAreaElement("dsm_asd_comments", "Comments (required for a rating of 2 or 1):", array("dsm_asd_confidence{@}=={@}2_somewhat_confident|1_not_confident"), "This field is required or specify not answered.");

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
        
            $this->form->addElement('header', null, "Social Communication Disorder");
            
            $this->form->addElement("static", null, "<BR><strong>If child does not meet criteria</strong> for an Autism Spectrum Disorder, then complete this checklist."); 
          
            $this->form->addElement("static", null, "<BR><strong>A. Persistent difficulties in the social use of verbal and nonverbal communication as manifested by deficits in all of the following:</strong><BR>"); //line space

            $this->form->addElement("select", "qa1_deficit_communication_social", "<BR>1. Deficits in using communication for social purposes, such as greeting and sharing information, in a manner that is appropriate to the social context.", $this->yesNo);
          
            $this->form->addElement("select", "qa2_change_communication", "<BR>2. Deficits in changing communication to match context or the needs of the listener, such as speaking differently in a classroom than on a playground, communicating differently to a child than an adult, and avoiding the use of overly formal language.", $this->yesNo);

            $this->form->addElement("select", "qa3_deficit_followrules", "<BR>3. Deficits in the ability to follow rules for conversation and storytelling, such as taking turns in conversation, rephrasing when misunderstood, and knowing how to use verbal and nonverbal signals to regulate interaction.", $this->yesNo);
            
            $this->form->addElement("select", "qb_limit_communication", "<BR><strong>B. The disturbance causes limitations in effective communication, social participation, social relationships, academic achievement, or occupational performance.</strong>", $this->yesNo);
            
            $this->form->addElement("select", "qc_onset_earlychildhood", "<BR><strong>C. Onset in the early developmental period (but may not become fully manifest until social communication demands exceed limited capacities.)</strong>", $this->yesNo);

           $this->form->addElement("static",null, "<BR><strong>D. The symptoms are not attributable to another medical or neurological condition and are not better explained by low abilities in the domains of word structure and grammar, intellectual disability, global developmental delay, autism spectrum disorder, or another mental disorder. </strong>");

           $this->form->addElement("select", "meet_dsm_scd", "<BR><strong>Meets DSM-V Criteria for Social Communication Disorder</strong><BR>$this->indent - All symptoms in category A present<BR>$this->indent - Symptoms limit communication, social relations, or other major functioning areas <BR>$this->indent - Not attributable or better explained by another DSM-V disorder or another medical or neurological condition", $this->yesNo);
            
            $this->form->addElement("static", null, "<BR>"); //line space

            $this->form->addElement("static", null, "<strong>Confidence Rating </strong><BR>");
            
          
            $this->form->addElement("select", "dsm_scd_confidence", "Given all the data that you have on this child, how confident are you about the classification of this child based on the DSM-V SCD criteria?", $this->confidence);
            
                      
            $this->addTextAreaElement("dsm_scd_comments", "Comments (required for a rating of 2 or 1)", array("dsm_scd_confidence{@}=={@}2_somewhat_confident|1_not_confident"), "This field is required or specify not answered."); 
            
            $this->form->addElement("static", null, "<BR>"); //line space
                       
    }

    function _page3(){
  
      $config =& NDB_Config::singleton();
      $dateOptions = array(
      'language' => 'en',
      'format'   => 'YMd',
      'minYear'  => $config->getSetting('startYear'), //allows for siblings up to 20 years older than candidate
      'maxYear'  => $config->getSetting('endYear'),
      'addEmptyOption' => true,
      'emptyOptionValue' => null
	     );
        
      $this->form->addElement('header', null, "Diagnostic Consensus");
      
      $this->form->addElement('static',null,"<BR>Consensus information for DSMV checklist is the same as for DSMIV checklist");
      $this->form->addElement('static',null,"<br><strong>Additional consensus fields must be entered in DSMIV checklist</strong>");

      $this->form->addElement("select", "dsm5_confirmed_diagnosis", "<BR>A clinician, through live observation or video review confirms the status of the participant stated above. The clinician agrees with the assessor's decision on the inclusion or exclusion of the participant.", $this->yesNo);

   } 
}

?>
