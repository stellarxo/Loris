<?php

require_once('RequiredIfGroup.inc');
require_once('RequiredIf.inc');
require_once 'HTML/QuickForm.php';
require_once 'HTML/QuickForm/Renderer/Array.php';

class NDB_BVL_Instrument_i3 extends NDB_BVL_Instrument{
	var $yesNo = array(null=>"", "yes" =>"Yes", "no" =>"No", "NA" =>"NA", "Unknown" => "Unknown");	
	/*
	INSERT INTO test_names VALUES ('', 'intense_interest_inv', 'Intense Interests Inventory', '0', '1');
	INSERT INTO instrument_subtests VALUES('', 'intense_interest_inv', 'intense_interest_page1', 'Intense Interests Inventory', 1);
	INSERT INTO instrument_subtests VALUES('', 'intense_interest_inv', 'intense_interest_page2', 'Intense Interests Inventory Key', 2);
	INSERT INTO test_battery VALUES ('', 'intense_interest_inv', '120', '1440', 'Y', 'Screening', '1');

	*/

	/**
	 * Array of column names to be ignored by the double data entry conflict detector.
	 */
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
		$this->testName = "i3";           // test_names.Test_name
		$this->table = 'i3';              // name of database table corresponding to instrument
		// data keyed by commentID
		$this->commentID = $commentID;

		//The array of dates/timestamps to convert to database dates/timestamps
		//Any HTML_Quickform date elements must be listed here
		$this->dateTimeFields=array("Date_taken");

		// required fields for data entry completion status
		$this->_requiredElements = array('Examiner', 'Date_taken');
	
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
	       if(preg_match("/intense_interest_inv(_page[0-9]+)/",$this->page,$matches)){
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
		$this->form->addElement('header', 'instrument_title', "Intense Interests Inventory (I3)");

		// automatically adds examiner & date of administration
		$this->_addMetadataFields();
		
    	$config =& NDB_Config::singleton();
        
        $this->dateOptions = array(
            'language' => 'en',
            'format'   => 'YMd',
            'minYear'  => $config->getSetting('startYear') -80, //allows for siblings up to 20 years older than candidate
            'maxYear'  => $config->getSetting('endYear'),
            'addEmptyOption' => true,
            'emptyOptionValue' => null
    	);

        $this->form->addElement('static',null,'<br>');
        $this->form->addElement("textarea", "other_comments", "Comments about Validity:", array('cols'=>25, 'rows'=>4));
        $this->XINRegisterRule("other_comments", array("{other_comments}{@}=={@}NEVER_REQUIRED"));

   
        }
        
        function _page1(){
       
	    $this->form->addElement ( 'header', null, "Intense Interests Inventory (I3)" );
    	$this->form->addElement ( "static", null, "<BR>" ); //line space
    	
        $var = 1;
        $months = array();
        $months[NULL] = "";
        	

        while($var<49){
        	$months[$var] = "$var";
        	$var++;
        }
        
        $months["NA"]="NA";
        	    		
    	//Source of information
    	$interest_reported = array (1 => "1", 2 => "2", 3 => "3", 4 => "4", 5 => "5", 6 => "6", 7 => "7");
        
        reset($interest_reported);
        
    	while ( list ( $field, $label ) = each ( $interest_reported ) ) {

    		$this->form->addElement ( "static", null, "<BR>" ); //line space

    		$this->form->addElement ( "static", null, "<BR>" ); //line space

            $this->form->addElement ("select", "interest{$field}", "<b> $label . Interest", array (NULL => "", "report_interest" => "Report Interest", "no_more_interests" => "No More Interests To Report" ));

        
        	//Once "No More Growth Data" is selected once, nothing further is required.
        	$this->XINRegisterRule ( "interest{$field}", array ("interest{$prevField}{@}!={@}no_more_interests", "interest{$prevField}{@}!={@}"), "These fields are required unless no more interests to report is selected" );
        	
        	$this->form->addRule ( "interest1", "These fields are required unless no more interests to report is selected", 'required' );
			
        	prev ( $interest_reported );
            $prevField = key ($interest_reported);
            next ($interest_reported);
            
            
            //TEXT ELEMENT to enter interest
	        $this->addTextAreaElement("interest{$field}_description", "Describe Interest", array("interest{$prevField}{@}!={@}no_more_interests", "interest{$prevField}{@}!={@}", "interest_{$field}{@}!={@}not_answered"));

            //Age of Onset
            $this->form->addElement ( 'select', "interest{$field}_age_of_onset", "Age of Onset (in months)", $months);
                        
    		$this->XINRegisterRule ( "interest{$field}_age_of_onset", array ("interest{$prevField}{@}!={@}no_more_interests", "interest{$prevField}{@}!={@}"), "Required" );                
            
            //Intensity
            $this->form->addElement ( 'select', "interest{$field}_intensity", "Intensity", array(NULL=>"", 1=> "1", 2 => "2", 3=> "3", 4=> "4", 5=>"5", "NA" => "NA"));
        	$this->XINRegisterRule ( "interest{$field}_intensity", array ("interest{$prevField}{@}!={@}no_more_interests", "interest{$prevField}{@}!={@}"), "Required" );                
                
            //Peculiarity
            $this->form->addElement ( 'select', "interest{$field}_peculiarity", "Peculiarity", array(NULL=>"", 1=> "1", 2 => "2", 3=> "3", 4=> "4", 5=>"5", "NA" => "NA"));                  
            $this->XINRegisterRule ( "interest{$field}_peculiarity", array ("interest{$prevField}{@}!={@}no_more_interests","interest{$prevField}{@}!={@}"), "Required" );                
                    
            //Persistent (yes/no)
            $this->form->addElement("select", "interest{$field}_persistent", "Persistent?", $this->yesNo);
     		$this->XINRegisterRule ( "interest{$field}_persistent", array ("interest{$prevField}{@}!={@}no_more_interests","interest{$prevField}{@}!={@}"), "Required" );                

    		}
		}
	
	
        function _page2(){
            $this->form->freeze();
		    $this->form->addElement('header', null, "Intense Interests Inventory Key");
            $this->form->addElement("static", null, "<br><br><b>Intensity</b><br>When the child is prevented from interest or interest is blocked, can the child's interest be stopped?<br><br>1= easily <br> 2 = with mild distress (child can redirect him/herself)<br>3 = with moderate distress (child needs help to redirect)<br>4 = with severe distress (child needs intense help to redirect), does not perseverate<br>5 = with severe distress (child needs intense help to redirect) perseverates for hours, days<br><br>");

            $this->form->addElement("static", null, "<b>Peculiarity</b>: <br>How unusual or peculiar is the interest? Is it noticeable by others? Is it embarrassing? <br><br>1 = not peculiar, interest is developmentally appropriate<br>2 = mildly unusual, only obvious to people who know the child well or watch the child carefully<br>3 = moderate, noticeably unusual<br>4 = severe, clearly unusual or peculiar, but not present in all settings<br>5 = extreme, clearly unusual or peculiar, and occurs often in many different settings");
            
    	}
}


?>
