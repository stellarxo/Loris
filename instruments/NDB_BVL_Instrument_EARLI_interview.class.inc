<?php


require_once("RequiredIfGroup.inc");
require_once('RequiredIf.inc');

class NDB_BVL_Instrument_EARLI_interview extends NDB_BVL_Instrument {


    var $dateOptions1960 = array(
        'language' => 'en',
        'format'   => 'YMd',
        'minYear'  => '1960',/* $config->getSetting('startYear') *///
        'maxYear'  => '2017' /*$config->getSetting('endYear')*/,
            'addEmptyOption' => true,
            'emptyOptionValue' => null);

    var $dateOptions1950 = array(
        'language' => 'en',
        'format'   => 'YMd',
        'minYear'  => '1950',
        'maxYear'  => '2017', 
        'addEmptyOption' => true,
        'emptyOptionValue' => null);

    var $dateOptions1940 = array(
        'language' => 'en',
        'format'   => 'YMd',
        'minYear'  => '1940',
        'maxYear'  => '2017', 
        'addEmptyOption' => true,
        'emptyOptionValue' => null);


    var $dateOptions2007 = array(
        'language' => 'en',
        'format'   => 'YMd',
        'minYear'  =>  '2007',
        'maxYear'  => '2017', 
        'addEmptyOption' => true,
        'emptyOptionValue' => null);


    var $dateOptionsOld = array(
        'language' => 'en',
        'format'   => 'YMd',
        'minYear'  => '1950', 
        'maxYear'  => '1995',
        'addEmptyOption' => true,
        'emptyOptionValue' => null);


    //month array
    var $months = array(null=>"", "January"=>"January", "February"=>"February", "March"=>"March", "April"=>"April", "May"=>"May", "June"=>"June", "July"=>"July", "August"=>"August", "September"=>"September", "October"=>"October", "November"=>"November", "December"=>"December", "88_refused" => "88 Refused", "99_dont_know"=> "99 Don't know", "Not_answered" => "Not Answered");

    //number arrays
    var $yesNo = array(null => "", '01_yes' => "Yes", '02' => "No", '88_refused' => "88 Refused", '99_dont_know'=> "99 Don't know", 'not_answered' => "Not Answered" );
    var $dateAge = array(NULL=>"",  "01_date" => "01 Date", "02_age" => "02 Age ", "88_Refused" => "88 Refused",  "99_Do_not_know"=>"99 Do not know", "Not_Answered"=>"Not Answered");


    var $ageOptions = array();
    var $years1940 = array();
    var $years1950 = array(); 
    var $negThreeToNine= array();
    var $negThreeToTen = array();
    var $oneToSeventy = array();
    var $oneToThree = array("1"=>"1", "2"=>"2", "3"=>"3");


    var $columnHeaders = array("month_names_header", "year_header", "month_header", "freq_header");

    function getSession()
    {
        $db =& Database::singleton();

        $sessionid = $db->selectOne("SELECT ID FROM session WHERE CandID='".$_REQUEST['candID']."' and Visit_label LIKE 'Vsupplement'");
        return $sessionid;
    }

    function getComment($sessionid)
    {
        $db =& Database::singleton();

        $commentid = $db->selectOne("SELECT CommentID FROM flag WHERE SessionID='$sessionid' and Test_name = 'EARLI_interview_S3_inserts' and CommentID NOT LIKE 'DDE%'");

        return $commentid;
    }

    /**
      * Wrapper to create a text field for questions that require Refused and Don't know options
      */
     
    function addTextElementRD($field, $label, $rules=array(), $rule_message='You must specify or select from the drop-down', $refusals=array(''=>'', "88_refused"=>"88 Refused", "99_do_not_know"=>"99 Do not know", 'not_answered'=>'Not Answered')){
        $group[]=&$this->form->createElement("text", $field);
        $group[]=&$this->form->createElement("select", $field."_status", "", $refusals);
        $this->form->addGroup($group, $field.'_group', $label, null, false);
        unset($group);
        $rules_array=array_merge(array($field.'_status{@}=={@}'), $rules);
        $this->XINRegisterRule($field, $rules_array, $rule_message, $field.'_group');
    }
     
    /**
     * Wrapper to create a text area field for questions that require Refused and Don't know options
     */
     
    function addTextAreaElementRD($field, $label, $rules=array(), $rule_message='You must specify or select from the drop-down'){
        $group[]=&$this->form->createElement("textarea", $field, null, array('cols'=>25, 'rows'=>4));
        $group[]=&$this->form->createElement("select", $field."_status", "", array(NULL=>'',"88_refused"=>"88 Refused", "99_do_not_know"=>"99 Do not know", 'not_answered'=>'Not Answered'));
        $this->form->addGroup($group, $field.'_group', $label, null, false);
        unset($group);
        $rules_array=array_merge(array($field.'_status{@}=={@}'),$rules);
        $this->XINRegisterRule($field, $rules_array, $rule_message, $field.'_group');
    }

    /**
    * Wrapper to create a field that only accepts a number, for questions that require refused and don't know options
    *
    */
    
    function addNumericElementRD($field, $label) {
        $group [] = $this->form->createElement("text", $field, $label);
        $group [] = $this->form->createElement("select", $field . "_status", null, array(NULL=>"", "88_refused"=>"88 Refused", "99_do_not_know"=>"99 Do not know", 'not_answered'=>"Not Answered"));    
        $this->form->addGroup($group, $field . "_group", $label, null, false);
        unset($group);
        $this->form->addGroupRule($field . "_group", array(array(array("Numbers only, please", 'numeric'))));
        $this->XINRegisterRule($field, array($field . '_status{@}=={@}'), 'This field is required', $field . '_group');
    }


}

