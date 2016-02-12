<?php

require_once 'HTML/QuickForm.php';
require_once 'HTML/QuickForm/Renderer/Array.php';

class NDB_BVL_Instrument_pspq_score extends NDB_BVL_Instrument
{
    //Commonly used level of indentation;
    var $indent = "&nbsp;&nbsp;&nbsp;&nbsp;";

    //abstract function setup($commentHe/SheD, $page);
    /**
     * sets up basic data, such as the HTML_Quickform object, and so on.
     *
     * @param string $commentHe/SheD  the CommentHe/SheD identifying the data to load
     * @param string $page       if a multipage form, the page to show
     * @return void
     * @access public
     */
    function setup($commentID, $page){
        $this->formType="XIN";
        $this->form = new HTML_Quickform('test_form');
        $this->page = $page;            // page label (number or
        
        // set the object properties
        $this->testName = "pspq_score";           // test_names.Test_name
        $this->table = 'pspq_score';
        // data keyed by commentHe/SheD
        $this->commentID = $commentID;
        $db =& Database::singleton();
        try {
            $record = $db->pselectRow("SELECT * FROM ".$this->table." WHERE CommentID=:cid",
                array('cid' =>$this->getCommentID()));
        } catch (DatabaseException $ex) {
            print "Query has failed to select";
            $record = array();
        }
        if(!empty($record)) {
            foreach($record as $key=>$value){
                $this->localDefaults[$key] = $value;
            }
        }
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

        $this->_main();

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
        $this->form->addElement('header', 'instrument_title', "PSPQ : Scores");
        $this->form->addElement('static', null, "<br /><br />");
        $subscales = array('aloof'=>'ALOOF','pragmatic_language'=>'PRS','rigid'=>'RIGID','total'=>'TOTAL'); 
        for($i=1; $i<=2;$i++) {
            $field = 'p'.$i;
            $this->form->addElement('header',null,'PSPQ Score for Parent '.$i);
            $this->form->addElement('static', $field."_relation_candidate", "Relationship to Candidate : ");
            $this->form->addElement('static', $field."_age", "Age : ");
            $this->form->addElement('static', $field."_gender", "Gender : ");
            $this->form->addElement('static', $field."_relation_respondent", "Informant : ");
            $this->form->addElement('static', $field."_informant_gender", "Informant Gender: ");

            $this->form->addElement('static', null, "<br /><br />");
            foreach($subscales as $subscale=>$label) {
                $this->addHeader($label);
                $this->form->addElement('static', $field."_respondent_".$subscale, "Self : ");
                $this->form->addElement('static', $field."_informant_".$subscale, "Informant : ");
                $this->form->addElement('static', $field."_best_estimate_".$subscale, "Best Estimate : ");
                $this->form->addElement('static', null, "<br /><br />");

            }
        }
        $this->form->addElement('header', 'instrument_title', "Cutoff Scores");

        $cutoff_vals = array('f_s_aloof'=>'3.46','f_s_prs'=>'2.93','f_s_rigid'=>'3.73','f_i_aloof'=>'3.65','f_i_prs'=>'3.22',
                             'f_i_rigid'=>'4.32','f_be_aloof'=>'3.39','f_be_prs'=>'2.89','f_be_rigid'=>'3.89','m_s_aloof'=>'4.13',
                             'm_s_prs'=>'3.25','m_s_rigid'=>'3.94','m_i_aloof'=>'4.19','m_i_prs'=>'3.31','m_i_rigid'=>'4.20',
                             'm_be_aloof'=>'4.02','m_be_prs'=>'3.10','m_be_rigid'=>'3.89');
        $gender = array('m'=>'MALE Subject','f'=>'FEMALE Subject');
        $subscales_cutoff = array('aloof'=>'ALOOF','prs'=>'PRS','rigid'=>'RIGID');
        $scoring = array('s'=>'Subject','i'=>'Informant','be'=>'Best Estimate');
        foreach($gender as $key=>$label) {
            $this->addHeader($label);
            // $group[] = $this->form->createElement("static",null,null,"Subscales -");
            $group[] = $this->form->createElement("static",null,null,"Aloof");
            $group[] = $this->form->createElement("static",null,null,"PRS");
                                   $group[] = $this->form->createElement("static",null,null,null);

            $group[] = $this->form->createElement("static",null,null,"Rigid");
            $this->form->addGroup($group,$key.'_header',null, $this->_GUIDelimiter,false);
            unset($group);
            foreach($scoring as $field=>$value){
                foreach($subscales_cutoff as $subscale=>$subscale_label) {
                    $display_field = $key."_".$field."_".$subscale;
                    $group[] = $this->form->createElement("static",null,null,$cutoff_vals[$display_field]);
                    if($subscale =='prs') {
                       $group[] = $this->form->createElement("static",null,null,null);
                    }
                }
                $this->form->addGroup($group, $key.$field."_header", $value, $this->_GUIDelimiter,false);
                unset($group);
            }

        }



    }

}
