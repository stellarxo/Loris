<?php
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
        if(Utility::isErrorX($db)) {
            print "Could not connect to database: ".$db->getMessage();
        }
        $record = $db->pselectRow("SELECT * FROM ".$this->table." WHERE CommentID=:cid",
                array('cid' =>$this->getCommentID()));

        if (Utility::isErrorX($record)) {
            print "Query has failed to select: ".$record->getMessage();
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
        $this->form->addElement('header', 'instrument_title', "PSPQ : Personality Styles and Preferences Questionnaire Scores");
        $this->form->addElement('static', null, "<br /><br />");

    }

}
