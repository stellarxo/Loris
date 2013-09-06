<?php

class NDB_BVL_Instrument_BSRC extends NDB_BVL_Instrument
{
   var $yesNo = array(""=>null, "no"=>"No", "yes"=>"Yes", "not_answered"=>"Not Answered");
   var $indgrp = array(""=>null,"individual"=>"Individual","group"=>"Group",
                       "not_answered"=>"Not Answered");
   var $setting = array(""=>null,"office_clinic"=>"Office/Clinic","home"=>"Home",
                        "daycare_preschool"=>"Daycare/Preschool","other"=>"Other",
                        "not_answered"=>"Not Answered"); 
   var $yesNo2 = array(""=>null, "no"=>"No", "yes"=>"Yes","na"=>"Not Applicable",
                       "not_answered"=>"Not Answered");
   var $intervention = array('speech'=>'Speech-language Therapy','occupational'=>'Occupational Therapy',
                  'physical'=>'Physical Therapy','behavior_intervention'=>'Comprehensive behavioral intervention/special educational services','other'=>'Other','not_answered'=>'Not Answered');
   function setup($commentID, $page){
       $this->formType="XIN";
       $this->form = new HTML_Quickform('test_form');
       $this->page = $page;            // page label (number or
       // string - used by
       // user-defined child classes)

       // set the object properties
       $this->testName = "BSRC";           // test_names.Test_name
       $this->table = 'BSRC';              // name of database table corresponding to instrument
       // data keyed by commentID
       $this->commentID = $commentID;

       //The array of dates/timestamps to convert to database dates/timestamps
       //Any HTML_Quickform date elements must be listed here
       $this->dateTimeFields=array("Date_taken",
                                   "startdate_occupationaltherapy","stopdate_occupationaltherapy",
                                   "startdate_physicaltherapy","stopdate_physicaltherapy",
                                   "startdate_speechlangtherapy","stopdate_speechlangtherapy",
                                   "startdate_behaviorintervention","stopdate_behaviorintervention",
                                   "startdate_other","stopdate_other");

       //The array of selects with multiple answers allowed
       //Any HTML_Quickform multiple selects must be listed here
       $this->_selectMultipleElements = array();

       // required fields for data entry completion status
       $this->_requiredElements = array('Examiner', "Date_taken");

       $this->_doubleDataEntryDiffIgnoreColumns = array('CommentID', 'UserID', 'Testdate', 
                                                        'Window_Difference', 'Candidate_Age');

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
       if(preg_match("/BSRC(_page[0-9]+)/",$this->page,$matches)){
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
       $this->addHeader("BSRC Treatment Form");

       // automatically adds examiner & date of administration
       $this->_addMetadataFields();
       $config =& NDB_Config::singleton();

       $this->dateOptions = array(
               'language' => 'en',
               'format'   => 'YMd',
               'minYear'  => $config->getSetting('startYear'), 
               'maxYear'  => $config->getSetting('endYear'),
               'addEmptyOption' => true,
               'emptyOptionValue' => null
               );

        $this->addDateElement('date_lastVisit', "<BR>Date of Last Visit");
         
        $this->addSelect("q1_earlyintervention_birthtothreeprg","<BR>1) Since your last visit did a professional refer your child to an <strong>early intervention or birth-to-three program </strong>? (Depending on where you live, these programs may have different names.)", $this->yesNo);
       $this->addSelect("q2_receive_earlyintervention_birthtothreeprg","<BR>2) Since your last visit, did your child <strong>receive any early intervention or birth-to-three program services?</strong>", $this->yesNo);
       $this->addNumericElement("hrs_earlyintervention_birthtothreeprg","Average hours per week");
       $this->XINRegisterRule("hrs_earlyintervention_birthtothreeprg", array("hrs_earlyintervention_birthtothreeprg{@}=={@}NEVER_REQUIRED"));
       
       $this->addNumericElement("total_earlyintervention_birthtothreeprg","Total hours since last visit");
       $this->XINRegisterRule("total_earlyintervention_birthtothreeprg", array("total_earlyintervention_birthtothreeprg{@}=={@}NEVER_REQUIRED"));
           
       $this->addSelect("q3_communityact","<BR>3) Since your last visit, did a <strong>professional recommend</strong> that your child attend any community based <strong>classes/activities designed to inscrease socialization</strong> (eg. MommyandMe, Gymboree, etc)",$this->yesNo);
 
      $this->addSelect("q4_participate_social","<BR>4) Since your last visit did your child <strong>participate</strong> in any classes/activities designed to increase socialization whether or not recommended by a professional(eg. MommyandMe, Gymboree etc.)",$this->yesNo);
 
     $this->addSelect("q5_service_delay","<BR>5) Since your last visit, did your child receive services for developmental delays of any kind (such as motor orlanguage delays) or concerns about delay?",$this->yesNo);

     $this->addLabel("<BR> <strong>If YES to #5, please complete the following:</strong>");
     
     $this->addHeader("<BR><strong>Occupational Therapy</strong>");
     $this->addSelect("servicetype_occupationaltherapy","Received occupational therapy",$this->yesNo);
     $this->XINRegisterRule("servicetype_occupationaltherapy", array("servicetype_occupationaltherapy{@}=={@}NEVER_REQUIRED"));
      
     $this->addBasicDate("startdate_occupationaltherapy", "Date:", $this->dateOptions);

     $this->XINRegisterRule("startdate_occupationaltherapy", array("servicetype_occupationaltherapy{@}=={@}yes"), "Required");

     $this->addSelect("continue_occupationaltherapy","Still receiving intervention?",$this->yesNo);
     $this->XINRegisterRule("continue_occupationaltherapy",array("servicetype_occupationaltherapy{@}=={@}yes"));
     $this->addBasicDate("stopdate_occupationaltherapy","If, No, date stopped",$this->dateOptions);
     $this->XINRegisterRule("stopdate_occupationaltherapy", array("continue_occupationaltherapy{@}=={@}no"), "Required");

     $this->addSelect("indgrp_occupationaltherapy","Individual or Group",$this->indgrp);
     $this->XINRegisterRule("indgrp_occupationaltherapy", array("servicetype_occupationaltherapy{@}=={@}yes"), "Required");

     $this->addSelect("setting_occupationaltherapy","Setting",$this->setting);
     $this->XINRegisterRule("setting_occupationaltherapy", array("servicetype_occupationaltherapy{@}=={@}yes"), "Required");

     $this->addNumericElement("avg_occupationaltherapy","Average hours per week");
     $this->XINRegisterRule("avg_occupationaltherapy", array("avg_occupationaltherapy{@}=={@}NEVER_REQUIRED"));
    
    //Physical Therapy

     $this->addHeader("<BR><strong>Physical Therapy</strong>");
     $this->addSelect("servicetype_physicaltherapy","Received physical therapy",$this->yesNo);
     $this->XINRegisterRule("servicetype_physicaltherapy", array("servicetype_physicaltherapy{@}=={@}NEVER_REQUIRED"));
      
     $this->addBasicDate("startdate_physicaltherapy", "Date:", $this->dateOptions);

     $this->XINRegisterRule("startdate_physicaltherapy", array("servicetype_physicaltherapy{@}=={@}yes"), "Required");

     $this->addSelect("continue_physicaltherapy","Still receiving intervention?",$this->yesNo);
     $this->XINRegisterRule("continue_physicaltherapy", array("servicetype_physicaltherapy{@}=={@}yes"), "Required");

     $this->addBasicDate("stopdate_physicaltherapy","If, No, date stopped",$this->dateOptions);
     $this->XINRegisterRule("stopdate_physicaltherapy", array("continue_physicaltherapy{@}=={@}no"), "Required");

     $this->addSelect("indgrp_physicaltherapy","Individual or Group",$this->indgrp);
     $this->XINRegisterRule("indgrp_physicaltherapy", array("servicetype_physicaltherapy{@}=={@}yes"), "Required");

     $this->addSelect("setting_physicaltherapy","Setting",$this->setting);
     $this->XINRegisterRule("setting_physicaltherapy", array("servicetype_physicaltherapy{@}=={@}yes"), "Required");

     $this->addNumericElement("avg_physicaltherapy","Average hours per week");
     $this->XINRegisterRule("avg_physicaltherapy", array("avg_physicaltherapy{@}=={@}NEVER_REQUIRED"));

     //Speech-language therapy
     
     $this->addHeader("<BR><strong>Speech Language Therapy</strong>");
     $this->addSelect("servicetype_speechlangtherapy","Received speechlang therapy",$this->yesNo);
     $this->XINRegisterRule("servicetype_speechlangtherapy", array("servicetype_speechlangtherapy{@}=={@}NEVER_REQUIRED"));
      
     $this->addBasicDate("startdate_speechlangtherapy", "Date:", $this->dateOptions);

     $this->XINRegisterRule("startdate_speechlangtherapy", array("servicetype_speechlangtherapy{@}=={@}yes"), "Required");

     $this->addSelect("continue_speechlangtherapy","Still receiving intervention?",$this->yesNo);
     $this->XINRegisterRule("continue_speechlangtherapy", array("servicetype_speechlangtherapy{@}=={@}yes"), "Required");

     $this->addBasicDate("stopdate_speechlangtherapy","If, No, date stopped",$this->dateOptions);
     $this->XINRegisterRule("stopdate_speechlangtherapy", array("continue_speechlangtherapy{@}=={@}no"), "Required");

     $this->addSelect("indgrp_speechlangtherapy","Individual or Group",$this->indgrp);
     $this->XINRegisterRule("indgrp_speechlangtherapy", array("servicetype_speechlangtherapy{@}=={@}yes"), "Required");

     $this->addSelect("setting_speechlangtherapy","Setting",$this->setting);
     $this->XINRegisterRule("setting_speechlangtherapy", array("servicetype_speechlangtherapy{@}=={@}yes"), "Required");

     $this->addNumericElement("avg_speechlangtherapy","Average hours per week");
     $this->XINRegisterRule("avg_speechlangtherapy", array("avg_speechlangtherapy{@}=={@}NEVER_REQUIRED"));

     //Comprehensive behavioral educational interventions

     $this->addHeader("<BR><strong>Comprehensive behavioral/educational interventions</strong>");
     $this->addSelect("servicetype_behaviorintervention","Received behaviorintervention therapy",$this->yesNo);
     $this->XINRegisterRule("servicetype_behaviorintervention", array("servicetype_behaviorintervention{@}=={@}NEVER_REQUIRED"));
      
     $this->addBasicDate("startdate_behaviorintervention", "Date:", $this->dateOptions);

     $this->XINRegisterRule("startdate_behaviorintervention", array("servicetype_behaviorintervention{@}=={@}yes"), "Required");

     $this->addSelect("continue_behaviorintervention","Still receiving intervention?",$this->yesNo);
     $this->XINRegisterRule("continue_behaviorintervention", array("servicetype_behaviorintervention{@}=={@}yes"), "Required");

     $this->addBasicDate("stopdate_behaviorintervention","If, No, date stopped",$this->dateOptions);
     $this->XINRegisterRule("stopdate_behaviorintervention", array("continue_behaviorintervention{@}=={@}no"), "Required");

     $this->addSelect("indgrp_behaviorintervention","Individual or Group",$this->indgrp);
     $this->XINRegisterRule("indgrp_behaviorintervention", array("servicetype_behaviorintervention{@}=={@}yes"), "Required");

     $this->addSelect("setting_behaviorintervention","Setting",$this->setting);
     $this->XINRegisterRule("setting_behaviorintervention", array("servicetype_behaviorintervention{@}=={@}yes"), "Required");

     $this->addNumericElement("avg_behaviorintervention","Average hours per week");
     $this->XINRegisterRule("avg_behaviorintervention", array("avg_behaviorintervention{@}=={@}NEVER_REQUIRED"));


     //Other
     $this->addHeader("<BR><strong>Other</strong>");
     $this->addSelect("servicetype_other","Received other therapy",$this->yesNo);
     $this->XINRegisterRule("servicetype_other", array("servicetype_other{@}=={@}NEVER_REQUIRED"));

     $this->addBasicDate("startdate_other", "Date:", $this->dateOptions);

     $this->XINRegisterRule("startdate_other", array("servicetype_other{@}=={@}yes"), "Required");

     $this->addSelect("continue_other","Still receiving intervention?",$this->yesNo);
     $this->XINRegisterRule("continue_other", array("servicetype_other{@}=={@}yes"), "Required");

     $this->addBasicDate("stopdate_other","If, No, date stopped",$this->dateOptions);
     $this->XINRegisterRule("stopdate_other", array("continue_other{@}=={@}no"), "Required");

     $this->addSelect("indgrp_other","Individual or Group",$this->indgrp);
     $this->XINRegisterRule("indgrp_other", array("servicetype_other{@}=={@}yes"), "Required");

     $this->addSelect("setting_other","Setting",$this->setting);
     $this->XINRegisterRule("setting_other", array("servicetype_other{@}=={@}yes"), "Required");

     $this->addNumericElement("avg_other","Average hours per week");
     $this->XINRegisterRule("avg_other", array("avg_other{@}=={@}NEVER_REQUIRED"));


     $this->addLabel("<BR>6) On average, how many hours per week has your child been in intervention");
     $this->addNumericElement("q6_avgperweek_A","a. since your last visit to our research program?");
     $this->addNumericElement("q6_avgperweek_B","b. in the past year");
     
     $this->addSelect("q7_alt_therapy","<BR>7) At any point since your last visit, did your child <strong>receive complementary or alternative therapies used to treat symptoms of autism?</strong>",$this->yesNo);
    $this->addTextAreaElement("q7_alt_therapy_specify","If YES, please specify", array("q7_alt_therapy{@}=={@}yes"),"If Yes, please specify:");

     $this->addSelect("q8_medical_pharma","<BR>8) At any point since your last visit, did your child <strong>receive medical or pharmacological interventions used to treat symptoms of autism? </strong>",$this->yesNo);
     $this->addTextAreaElement("q8_medical_pharma_specify","If YES, please specify", array("q8_medical_pharma{@}=={@}yes"),"If Yes, please specify:");
     $this->addSelect("q9_continue_nextyr","<BR>9) If this is your child's 36-month assessment, do you plan to continue your child's enrollment in intervention during next year?",$this->yesNo2);
     
     $this->addSelect("q10_therapyoptions", "10) If you checked yes in #9, please check all that apply", $this->intervention, "multiple size='6'");
     $this->XINRegisterRule("q10_therapyoptions", array("q9_continue_nextyr{@}=={@}yes"),"Required");
     
     $this->addTextAreaElement("general_comments","Is there anything else you would like to tell us about services your child has received,please write your comments");

     $this->addTextAreaElement("other_comments", "Comments about Validity:" );
     $this->XINRegisterRule("other_comments", array("{other_comments}{@}=={@}NEVER_REQUIRED"));
     $this->form->addFormRule(array(&$this, 'Range_Allowed'));

   }
   function Range_Allowed($values) {
       $errors = array();
       $temp = $values['Date_taken'];
       $datetaken = mktime(0,0,0,$temp['M'],$temp['d'],$temp['Y']);
       $temp = $values['date_lastVisit_date'];
       $datelastvisit = mktime(0,0,0,$temp['M'],$temp['d'],$temp['Y']);
       
       $list_of_fields = array('hrs_earlyintervention_birthtothreeprg','q6_avgperweek_A',
                         'q6_avgperweek_B','avg_occupationaltherapy','avg_physicaltherapy',
                         'avg_speechlangtherapy','avg_behaviorintervention','avg_other');
       foreach($list_of_fields as $field){
           if( $values[$field] <0 || $values[$field] >168)      
           {
               $error = $field."_group";
               $errors[$error] = 'Please enter a value between 0 and 168';
               
           }
       }
       if($values['q9_continue_nextyr']=='yes' && 
           ($values['q10_therapyoptions']=="" || $values['q10_therapyoptions']==null))  {
            
            $errors['q10_therapyoptions']='Required if #9 is checked as Yes';
        }

       if($datelastvisit > $datetaken) {
           
           $errors['date_lastVisit_date_group']='Date last visit should be before Date Taken';
       }
       
       if($values['servicetype_occupationaltherapy'] == 'yes' 
           && ($values['avg_occupationaltherapy'] == null || $values['avg_occupationaltherapy']=="")
           && ($values['avg_occupationaltherapy_status'] == null 
           || $values['avg_occupationaltherapy_status']=="" )) {
           
           $errors['avg_occupationaltherapy_group']='Required';
       }
       if($values['servicetype_physicaltherapy'] == 'yes' 
           && ($values['avg_physicaltherapy'] == null || $values['avg_physicaltherapy']=="")
           && ($values['avg_physicaltherapy_status'] == null 
           || $values['avg_physicaltherapy_status']==""))
           {
           
           $errors['avg_physicaltherapy_group']='Required';
       }

       if($values['servicetype_speechlangtherapy'] == 'yes' 
           && ($values['avg_speechlangtherapy'] == null || $values['avg_speechlangtherapy']=="")
           && ($values['avg_speechlangtherapy_status'] == null 
           || $values['avg_speechlangtherapy_status']=="")) {
           
           $errors['avg_speechlangtherapy_group']='Required';
       }
       if($values['servicetype_behaviorintervention'] == 'yes' 
           && ($values['avg_behaviorintervention'] == null || $values['avg_behaviorintervention']=="")
           && ($values['avg_behaviorintervention_status'] == null 
           || $values['avg_behaviorintervention_status']=="")) {
           
           $errors['avg_behaviorintervention_group']='Required';
       }
       if($values['servicetype_other'] == 'yes' 
           && ($values['avg_other'] == null || $values['avg_other']=="")
           && ($values['avg_other_status'] == null || $values['avg_other_status']=="")) {
           
           $errors['avg_other_group']='Required';
       }
       if($values['q2_receive_earlyintervention_birthtothreeprg'] == 'yes' 
          && ($values['hrs_earlyintervention_birthtothreeprg']== null 
              || $values['hrs_earlyintervention_birthtothreeprg'] =="")
          &&($values['hrs_earlyintervention_birthtothreeprg_status']==null 
             ||$values['hrs_earlyintervention_birthtothreeprg_status']=="" )) {
           
           $errors['hrs_earlyintervention_birthtothreeprg_group']='Required';    
       }
      
      if($values['q2_receive_earlyintervention_birthtothreeprg'] == 'yes' 
          && ($values['total_earlyintervention_birthtothreeprg']== null 
              || $values['total_earlyintervention_birthtothreeprg'] =="")
          &&($values['total_earlyintervention_birthtothreeprg_status']==null 
             ||$values['total_earlyintervention_birthtothreeprg_status']=="" )) {
           
           $errors['total_earlyintervention_birthtothreeprg_group']='Required';    
       }
       $servicelist = array('servicetype_occupationaltherapy','servicetype_physicaltherapy',
                            'servicetype_speechlangtherapy','servicetype_behaviorintervention',
                            'servicetype_other');
       /*
       foreach($servicelist as $list) {
           if($values['q5_service_delay']=='yes' 
              && ($values[$list] == null || $values[$list]=="")) {
               
               $errors[$list] = "Required";
           }
       }
*/
               return $errors;

      }

}


?>
