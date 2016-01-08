<?php

require_once 'HTML/QuickForm.php';
require_once 'HTML/QuickForm/Renderer/Array.php';

class NDB_BVL_Instrument_med_records extends NDB_BVL_Instrument {
    var $ValidityEnabled = false;
    var $ValidityRequired = false;

	var $yesNo = array (null => "", 'yes' => "Yes", 'no' => "No", 'not_specified' => "Not Specified in records", 'not_answered' => "Not Answered" );
	var $normal_abnormal_FX = array (null => "", 'normal' => "NORMAL (no FX)", 'abnormal' => "ABNORMAL (has FX)", 'not_answered' => "Not Answered" );
	var $normal_abnormal_TS = array (null => "", 'normal' => "NORMAL (no TS)", 'abnormal' => "ABNORMAL (has TS)", 'not_answered' => "Not Answered" );
	var $normal_abnormal_NF = array (null => "", 'normal' => "NORMAL (no NF)", 'abnormal' => "ABNORMAL (has NF)", 'not_answered' => "Not Answered" );
	var $chart_actual = array (null => "", "not_answered" => "Not Answered", "actual" => "Actual", "chart" => "Chart" );
        var $project;
	/**
	 * sets up basic data, such as the HTML_Quickform object, and so on.
	 *
	 * @param string $commentID  the CommentID identifying the data to load
	 * @param string $page       if a multipage form, the page to show
	 * @return void
	 * @access public
	 */
	function _setup($commentID, $page) {
		$this->formType = "XIN";
//		$this->	
		$this->form = new HTML_Quickform ( 'test_form' );
		$this->page = $page; // page label (number or
		// string - used by
		// user-defined child classes)

		// data keyed by commentID
		$this->commentID = $commentID;
		
		//The array of dates/timestamps to convert to database dates/timestamps
		//Any HTML_Quickform date elements must be listed here
		$this->dateTimeFields = array ("Date_taken"); //Other date fields are added automatically through $this->addDateElement();
		
		$this->_requiredElements = array ('Examiner', 'Date_taken', 'first_chart');
		/*
		'first_chart', '', 'first_date_taken', 'second_date_taken', 'third_date_taken','fourth_date_taken', 'fifth_date_taken', 'sixth_date_taken', 'seventh_date_taken', 'eighth_date_taken', 'ninth_date_taken', 'tenth_date_taken', 'eleventh_date_taken', 'twelfth_date_taken', 'thirteenth_date_taken', 'fourteenth_date_taken', 'fifteenth_date_taken', 
		'sixteenth_date_taken', 'seventeeth_date_taken', 'eighteenth_date_taken', 'nineteenth_date_taken', 'twenty_date_taken', 'twentyone_date_taken', 'twentytwo_date_taken', 'twentythree_date_taken', 'twentyfour_date_taken', 'twentyfive_date_taken', 'twentysix_date_taken', 'twentyseven_date_taken', 'twentyeight_date_taken', 'twentynine_date_taken', 'thirty_date_taken', 'thirtyone_date_taken', 'thirtytwo_date_taken', 'thirtythree_date_taken', 'thirtyfour_date_taken', 'thirtyfive_date_taken');
		*/
		
		$config = & NDB_Config::singleton ();
		$this->dateOptions = array ('language' => 'en', 'format' => 'YMd', 'minYear' => $config->getSetting ( 'startYear' ) - 20, //allows for siblings up to 20 years older than candidate
'maxYear' => $config->getSetting ( 'endYear' ), 'addEmptyOption' => true, 'emptyOptionValue' => null );
                 $db = & Database::singleton();
                $this->project = $db->pselectOne("SELECT c.ProjectID from $this->table n JOIN flag f 
                                    ON (f.CommentID= n.CommentID) JOIN session s ON (s.ID = f.SessionID) 
                                    JOIN candidate c ON (c.CandID=s.CandID) 
                                    WHERE n.CommentID=:cid", array('cid'=>$this->getCommentID()));


		// setup the form
        $this->_setupForm();

	}
	
    /**
    * method to build the HTML_Quickform object into a paged forms erase
    *
    * @return void
    * @access private
    */
function _setupForm(){
    	 //Defines the call back function for HTML Quickform to use when validating the form.
        $this->form->addFormRule(array(&$this,'XINValidate'));
    	
    	if(preg_match("/(_page[0-9]+)/",$this->page,$matches)){
            call_user_method($matches[1], $this);
        } else {
            $this->_main();
        }
    }
    
function _possibleExclusionaryCriteria() {
		$this->form->addElement ( 'header', null, "Possible Exclusionary Criteria:" );
		$this->form->addElement ( "static", null, "<BR>" ); //line space
		

		$this->form->addElement ( "select", "tested_of_fragile_x", "Tested for Fragile X?", $this->yesNo );
		$this->form->addElement ( "select", "tested_of_fragile_x_result", $this->indent . "If yes, result was:", $this->normal_abnormal_FX );
		$this->XINRegisterRule ( "tested_of_fragile_x_result", array ("tested_of_fragile_x{@}=={@}yes" ), "Please indicate the Fragile X result." );
		$this->form->addElement ( "static", null, "<BR>" ); //line space
		

		$this->form->addElement ( "select", "tested_for_tuberous_sclerosis", "Tested for Tuberous Sclerosis?", $this->yesNo );
		$this->form->addElement ( "select", "tested_for_tuberous_sclerosis_result", $this->indent . "If yes, result was:", $this->normal_abnormal_TS );
		$this->XINRegisterRule ( "tested_for_tuberous_sclerosis_result", array ("tested_for_tuberous_sclerosis{@}=={@}yes" ), "Please indicate the Tuberous Sclerosis result." );
		$this->form->addElement ( "static", null, "<BR>" ); //line space
		

		$this->form->addElement ( "select", "tested_for_neurofibromatosis", "Tested for Neurofibromatosis?", $this->yesNo );
		$this->form->addElement ( "select", "tested_for_neurofibromatosis_result", $this->indent . "If yes, result was:", $this->normal_abnormal_NF );
		$this->XINRegisterRule ( "tested_for_neurofibromatosis_result", array ("tested_for_neurofibromatosis{@}=={@}yes" ), "Please indicate the Neurofibromatosis result." );
		$this->form->addElement ( "static", null, "<BR>" ); //line space
		

		$this->form->addElement ( "select", "other_genetic_tests_completed", "Other genetic tests completed?", $this->yesNo );
                $this->addTextElement ( "other_genetic_tests_completed_specify", $this->indent . "1. Specify first genetic test:", array ("other_genetic_tests_completed{@}=={@}yes" ), "This field is required." );
                $this->addTextElement ( "other_genetic_result_completed_specify", $this->indent .$this->indent . "Specify first genetic test result:", array ("other_genetic_tests_completed{@}=={@}yes" ), "This field is required." );
               
		$this->form->addElement ( "static", null, "<BR>" ); //line space
	}
	
    function _linkParagraph() {
        return;
    }

    function _page2() {
		$this->form->addElement ( 'header', null, "Growth Chart Information:" );
		$this->form->addElement ( "static", null, "<BR>" ); //line space
		$this->form->addElement ( "static", null, "<BR>" ); //line space
		$this->form->addElement ( "static", null, "Units will be automatically converted, if you would like to see the conversion results please exit this page and re-enter it.<BR>" );
		$this->form->addElement ( "static", null, "If you select no more growth data, no more data needs to be entered into the form after that point.<BR>" );
                $this->_linkParagraph();
                if($this->project == 2) { 
                    $this->addDateElement('Lastupdated_growthchart', 'Date this form was last updated:', $this->dateOptions);
                    $this->form->addElement ( "static", null, "<BR>" );
                }
		//Source of information
		$administrations = array ("first" => "1", "second" => "2", "third" => "3", "fourth" => "4", "fifth" => "5", "sixth" => "6", "seventh" => "7", "eighth" => "8", "ninth" => "9", "tenth" => "10", "eleventh" => "11", "twelfth" => "12", "thirteenth" => "13", "fourteenth" => "14", "fifteenth" => "15", "sixteenth" => "16", "seventeenth" => "17");
		
		reset ( $administrations );
		
		while ( list ( $field, $label ) = each ( $administrations ) ) {
			
			$this->form->addElement ( "static", null, "<BR>" ); //line space
			

			$this->form->addElement ( "static", null, "<BR>" ); //line space
			

			$this->form->addElement ( "select", "{$field}_chart", "<b> $label . Source of Information</b> <BR> Selecting chart indicates measurements were taken from a growth chart. <BR> Selecting actual indicates the measurements entered were the actual measurements taken.<BR> Selecting parent report indicates the measurements entered were reported by the parents and taken from the child's vaccination booklet", array (NULL => "", "not_answered" => "Not Answered", "actual" => "Actual", "chart" => "Chart", 'parent_report' => 'Parent Report', "not_answered" => "Not Answered", "no_more_chart_data" => "No More Growth Data" ) );
			
			//Once "No More Growth Data" is selected once, nothing further is required.
			$this->XINRegisterRule ( "{$field}_chart", array ("{$prevField}_chart{@}!={@}no_more_chart_data", "{$prevField}_chart{@}!={@}" ), "These fields are required unless no more growth data is selected" );
			
			$this->form->addRule ( "first_chart", "Must answer no more growth data, not answered, actual or chart", 'required' );
			
			prev ( $administrations );
			$prevField = key ( $administrations );
			next ( $administrations );
		
		/*	
			$this->addDateElement("{$field}_date_taken", "Date of Administration", array("{$field}_date_stat{@}!={@}not_answered", "{$prevField}_chart{@}!={@}no_more_chart_data", "{$prevField}_chart{@}!={@}"), "The date is required unless not answered is selected");
		*/
						
            $group[] = $this->form->createElement("date", "{$field}_measurement_date", null, $this->dateOptions);
      
            $this->dateTimeFields[] = "{$field}_measurement_date"; //add to array of dates and times.
      
            $group[] = $this->form->createElement("select", "{$field}_measurement_date_status", null, array(NULL=>"", 'not_answered'=>"Not Answered"));
      
            $this->form->addGroup($group, "{$field}_measurement_date_group", "Date", $this->_GUIDelimiter, FALSE);
      
            unset($group);
      
            $this->XINRegisterRule("{$field}_measurement_date", array("{$field}_measurement_date_status{@}=={@}", "{$prevField}_chart{@}!={@}no_more_chart_data", "{$prevField}_chart{@}!={@}"), "A Date, not answered is required or no more chart data must be selected.", "{$field}_measurement_date_group");

/*
			$this->form->addElement('date', "{$field}_measurement_date", "Date of Administration", $dateOptions);

    	$this->form->addElement('select', "{$field}_measurement_date_status", "Select Not Answered if date not available", array(NULL=>"", "not_answered"=>"Not Answered"));
*/

    	    $this->XINRegisterRule("{$field}_measurement_date", array("{$field}_date_stat{@}!={@}not_answered", "{$prevField}_chart{@}!={@}no_more_chart_data", "{$prevField}_chart{@}!={@}"), "The date is required unless not answered is selected");
    	
    		$this->XINRegisterRule("{$field}_date_stat", array("{$prevField}_chart{@}!={@}no_more_chart_data", "{$prevField}_chart{@}!={@}", "{$field}_date_taken{@}=={@}"), "Please specify not answered or enter a date.");
			
			
			$units_length = array ("cm", "inches" );
			$units_weight = array ("grams", "ounces" );
			
			$unit_array_length = array (null => "", "cm" => "cm", "inches" => "inches", "not_answered" => "Not Answered" );
			$unit_array_weight = array (null => "", "grams" => "grams", "ounces" => "ounces", "not_answered" => "Not Answered" );
			
			$noted_message_units_length = "Note: Only centimeters OR inches may be entered.  There are 12 inches in a foot.  Please convert as required.";
			$noted_message_units_weight = "Note: Only grams OR ounces may be entered.  There are 16 ounces in a pound. Please convert as required.";
			
			//*************************************************************************Length	
			

			$measurement1 = "Length";
			$percentage = array (null => "", 'percent' => "%ile", 'not_answered' => "Not Answered" );
			$this->double_indent = $this->indent . $this->indent;
			$this->form->addElement ( 'static', null, "<b>$measurement1 Measurement <BR></b>" );
			$this->form->addElement ( 'static', null, $noted_message_units_length );
			
			$this->form->addElement ( 'select', "{$field}_measurement_length_units_stat", "$this->double_indent $measurement1 Units", $unit_array_length );
			
			$this->XINRegisterRule ( "{$field}_measurement_length_units_stat", array ("{$prevField}_chart{@}!={@}no_more_chart_data", "{$prevField}_chart{@}!={@}" ), "Required status" );
			
			//Add text boxes
			$this->form->addElement ( 'text', "{$field}_measurement_length_$units_length[0]", "$this->double_indent $units_length[0]" );
			$this->form->addElement ( "static", null, "$this->double_indent <BR/>" ); //line space
			$this->form->addElement ( 'text', "{$field}_measurement_length_$units_length[1]", "$this->double_indent $units_length[1]" );
			
			$this->XINRegisterRule ( "{$field}_measurement_length_$units_length[0]", array ("{$field}_measurement_length_units_stat{@}=={@}cm", "{$prevField}_chart{@}!={@}no_more_chart_data" ), "Please enter centimeters" );
			
			$this->XINRegisterRule ( "{$field}_measurement_length_$units_length[1]", array ("{$field}_measurement_length_units_stat{@}=={@}inches", "{$prevField}_chart{@}!={@}no_more_chart_data" ), "Please enter inches" );
			
			$this->form->addElement ( "static", null, "Percentile will be calculated.<BR>" ); //line space
  					
			$this->form->addElement ( 'text', "{$field}_percentage_length", "$this->double_indent Percentile" );
			$this->XINRegisterRule("{$field}_percentage_length", array("{$field}_percentage_length{@}=={@}NEVER_REQUIRED"));

			
			
			//****************************************************************************Weight
			

			$measurement2 = "Weight";
			$percentage = array (null => "", 'percent' => "%ile", 'not_answered' => "Not Answered" );
			$this->form->addElement ( 'static', null, "<b>$measurement2 Measurement <BR></b>" );
			$this->form->addElement ( 'static', null, $noted_message_units_weight );
			
			$this->form->addElement ( 'select', "{$field}_measurement_weight_units_stat", "$this->double_indent $measurement2 Units", array (null => "", "grams" => "grams", "ounces" => "ounces", "not_answered" => "Not Answered" ) );
			
			$this->XINRegisterRule ( "{$field}_measurement_weight_units_stat", array ("{$prevField}_chart{@}!={@}no_more_chart_data", "{$prevField}_chart{@}!={@}" ), "These fields are required unless not answered is selected" );
			
			//Add text boxes
			$this->form->addElement ( 'text', "{$field}_measurement_weight_$units_weight[0]", "$this->double_indent $units_weight[0]" );
			$this->form->addElement ( 'text', "{$field}_measurement_weight_$units_weight[1]", "$this->double_indent $units_weight[1]" );
			
			$this->XINRegisterRule ( "{$field}_measurement_weight_$units_weight[0]", array ("{$field}_measurement_weight_units_stat{@}=={@}grams", "{$prevField}_chart{@}!={@}no_more_chart_data" ), "Please enter grams" );
			$this->XINRegisterRule ( "{$field}_measurement_weight_$units_weight[1]", array ("{$field}_measurement_weight_units_stat{@}=={@}ounces", "{$prevField}_chart{@}!={@}no_more_chart_data" ), "Please enter ounces" );
			
			$this->form->addElement ( "static", null, "Percentile will be calculated.<BR>" ); //line space
						
			$this->form->addElement ( 'text', "{$field}_weight_percentage", "$this->double_indent Percentile" );
			
			$this->XINRegisterRule("{$field}_weight_percentage", array("{$field}_weight_percentage{@}=={@}NEVER_REQUIRED"));
	
		    //********************************************************************************BMI
		    
		    $this->form->addElement ( 'static', null, "<b>BMI Percentile</b> (will be calculated only if the child is over 24 months)");

        	$this->form->addElement ( 'text', "{$field}_bmi", "$this->double_indent BMI" );

        	$this->XINRegisterRule("{$field}_bmi", array("{$field}_bmi{@}=={@}NEVER_REQUIRED"));
        
			
			//*******************************************************************************Head Circ
			$measurement3 = "Head Circ";
			
			$percentage = array (null => "", 'percent' => "%ile", 'not_answered' => "Not Answered" );
			$this->form->addElement ( 'static', null, "<b>$measurement3 Measurement <BR></b>" );
			$this->form->addElement ( 'static', null, $noted_message_units_length );
			
			$this->form->addElement ( 'select', "{$field}_measurement_head_units_stat", "$this->double_indent $measurement3 Units", $unit_array_length );
			
			$this->XINRegisterRule ( "{$field}_measurement_head_units_stat", array ("{$prevField}_chart{@}!={@}no_more_chart_data", "{$prevField}_chart{@}!={@}" ), "These fields are required unless not answered is selected" );
			
			//Add text boxes
			$this->form->addElement ( 'text', "{$field}_measurement_head_$units_length[0]", "$this->double_indent $units_length[0]" );
			$this->form->addElement ( 'text', "{$field}_measurement_head_$units_length[1]", "$this->double_indent $units_length[1]" );
			
			$this->XINRegisterRule ( "{$field}_measurement_head_$units_length[0]", array ("{$field}_measurement_head_units_stat{@}=={@}cm", "{$prevField}_chart{@}!={@}no_more_chart_data" ), "Please enter centimeters" );
			$this->XINRegisterRule ( "{$field}_measurement_head_$units_length[1]", array ("{$field}_measurement_head_units_stat{@}=={@}inches", "{$prevField}_chart{@}!={@}no_more_chart_data" ), "Please enter inches" );
			
			$this->form->addElement ( "static", null, "Percentile will be calculated.<BR>" ); //line space
			
			$this->form->addElement ( 'text', "{$field}_head_percentage", "$this->double_indent Percentile" );
			$this->XINRegisterRule("{$field}_head_percentage", array("{$field}_head_percentage{@}=={@}NEVER_REQUIRED"));
			
		
		}
	}
	
	
  function _page3() {
	  $this->form->addElement ( 'header', null, "Growth Chart Information Continued:" );
	  $this->form->addElement ( "static", null, "<BR>" ); //line space
	  $this->form->addElement ( "static", null, "<BR>" ); //line space
	  $this->form->addElement ( "static", null, "Units will be automatically converted, if you would like to see the conversion results please exit this page and re-enter it.<BR>" );
	  $this->form->addElement ( "static", null, "If you select no more growth data, no more data needs to be entered into the form after that point.<BR>" );
          if($this->project == 2) {
              $this->addDateElement('Lastupdated_growthchart2', 'Date this form was last updated:', $this->dateOptions);
 	      $this->form->addElement ( "static", null, "<BR>" );
	  }
          //Source of information
	  $administrations = array ("eighteenth" => "18", "nineteenth" =>"19", "twenty" => "20", "twentyone" => "21", "twentytwo" => "22", "twentythree" => "23", "twentyfour" => "24", 
			  "twentyfive" => "25", "twentysix" => "26", "twentyseven" => "27", "twentyeight" => "28", "twentynine" => "29", "thirty" => "30", "thirtyone" => "31", "thirtytwo" => "32", 
			  "thirtythree" => "33", "thirtyfour" => "34", "thirtyfive" => "35");

  		reset ( $administrations );

  		while ( list ( $field, $label ) = each ( $administrations ) ) {

  			$this->form->addElement ( "static", null, "<BR>" ); //line space

  			$this->form->addElement ( "static", null, "<BR>" ); //line space

  			$this->form->addElement ( "select", "{$field}_chart", "<b> $label . Source of Information</b> <BR> Selecting chart indicates measurements were taken from a growth chart. <BR> Selecting actual indicates the measurements entered were the actual measurements taken.<BR> Selecting parent report indicates the measurements entered were reported by the parents and taken from the child's vaccination booklet", array (NULL => "", "not_answered" => "Not Answered", "actual" => "Actual", "chart" => "Chart", 'parent_report' => 'Parent Report', "not_answered" => "Not Answered", "no_more_chart_data" => "No More Growth Data" ) );

  			//Once "No More Growth Data" is selected once, nothing further is required.
  			$this->XINRegisterRule ( "{$field}_chart", array ("{$prevField}_chart{@}!={@}no_more_chart_data", "{$prevField}_chart{@}!={@}" ), "These fields are required unless no more growth data is selected" );

  			$this->form->addRule ( "first_chart", "Must answer no more growth data, not answered, actual or chart", 'required' );

  			prev ( $administrations );
  			$prevField = key ( $administrations );
  			next ( $administrations );

  	    	$config =& NDB_Config::singleton();
               $dateOptions = array(
              'language' => 'en',
              'format'   => 'YMd',
              'minYear'  => $config->getSetting('startYear') - 20, //allows for siblings up to 20 years older than candidate
              'maxYear'  => $config->getSetting('endYear') +20,
              'addEmptyOption' => true,
              'emptyOptionValue' => null
      		     );

  		/*	
  			$this->addDateElement("{$field}_date_taken", "Date of Administration", array("{$field}_date_stat{@}!={@}not_answered", "{$prevField}_chart{@}!={@}no_more_chart_data", "{$prevField}_chart{@}!={@}"), "The date is required unless not answered is selected");
  		*/

            $group[] = $this->form->createElement("date", "{$field}_measurement_date", null, $this->dateOptions);

            $this->dateTimeFields[] = "{$field}_measurement_date"; //add to array of dates and times.

            $group[] = $this->form->createElement("select", "{$field}_measurement_date_status", null, array(NULL=>"", 'not_answered'=>"Not Answered"));

            $this->form->addGroup($group, "{$field}_measurement_date_group", "Date", $this->_GUIDelimiter, FALSE);
        
            unset($group);

         $this->XINRegisterRule("{$field}_measurement_date", array("{$field}_measurement_date_status{@}=={@}", "{$prevField}_chart{@}!={@}no_more_chart_data", "{$prevField}_chart{@}!={@}"), "A Date, not answered is required or no more chart data must be selected.", "{$field}_measurement_date_group");

  /*
  			$this->form->addElement('date', "{$field}_measurement_date", "Date of Administration", $dateOptions);

      	$this->form->addElement('select', "{$field}_measurement_date_status", "Select Not Answered if date not available", array(NULL=>"", "not_answered"=>"Not Answered"));
  */

      	    $this->XINRegisterRule("{$field}_measurement_date", array("{$field}_date_stat{@}!={@}not_answered", "{$prevField}_chart{@}!={@}no_more_chart_data", "{$prevField}_chart{@}!={@}"), "The date is required unless not answered is selected");

      		$this->XINRegisterRule("{$field}_date_stat", array("{$prevField}_chart{@}!={@}no_more_chart_data", "{$prevField}_chart{@}!={@}", "{$field}_date_taken{@}=={@}"), "Please specify not answered or enter a date.");


  			$units_length = array ("cm", "inches" );
  			$units_weight = array ("grams", "ounces" );

  			$unit_array_length = array (null => "", "cm" => "cm", "inches" => "inches", "not_answered" => "Not Answered" );
  			$unit_array_weight = array (null => "", "grams" => "grams", "ounces" => "ounces", "not_answered" => "Not Answered" );

  			$noted_message_units_length = "Note: Only centimeters OR inches may be entered.  There are 12 inches in a foot.  Please convert as required.";
  			$noted_message_units_weight = "Note: Only grams OR ounces may be entered.  There are 16 ounces in a pound. Please convert as required.";

  			//*************************************************************************Length	


  			$measurement1 = "Length";
  			$percentage = array (null => "", 'percent' => "%ile", 'not_answered' => "Not Answered" );
  			$this->double_indent = $this->indent . $this->indent;
  			$this->form->addElement ( 'static', null, "<b>$measurement1 Measurement <BR></b>" );
  			$this->form->addElement ( 'static', null, $noted_message_units_length );

  			$this->form->addElement ( 'select', "{$field}_measurement_length_units_stat", "$this->double_indent $measurement1 Units", $unit_array_length );

  			$this->XINRegisterRule ( "{$field}_measurement_length_units_stat", array ("{$prevField}_chart{@}!={@}no_more_chart_data", "{$prevField}_chart{@}!={@}" ), "Required status" );

  			//Add text boxes
  			$this->form->addElement ( 'text', "{$field}_measurement_length_$units_length[0]", "$this->double_indent $units_length[0]" );
  			$this->form->addElement ( "static", null, "$this->double_indent <BR/>" ); //line space
  			$this->form->addElement ( 'text', "{$field}_measurement_length_$units_length[1]", "$this->double_indent $units_length[1]" );

  			$this->XINRegisterRule ( "{$field}_measurement_length_$units_length[0]", array ("{$field}_measurement_length_units_stat{@}=={@}cm", "{$prevField}_chart{@}!={@}no_more_chart_data" ), "Please enter centimeters" );

  			$this->XINRegisterRule ( "{$field}_measurement_length_$units_length[1]", array ("{$field}_measurement_length_units_stat{@}=={@}inches", "{$prevField}_chart{@}!={@}no_more_chart_data" ), "Please enter inches" );

  			$this->form->addElement ( "static", null, "Percentile will be calculated.<BR>" ); //line space

  			$this->form->addElement ( 'text', "{$field}_percentage_length", "$this->double_indent Percentile" );
  			$this->XINRegisterRule("{$field}_percentage_length", array("{$field}_percentage_length{@}=={@}NEVER_REQUIRED"));



  			//****************************************************************************Weight
  			$measurement2 = "Weight";
  			$percentage = array (null => "", 'percent' => "%ile", 'not_answered' => "Not Answered" );
  			$this->form->addElement ( 'static', null, "<b>$measurement2 Measurement <BR></b>" );
  			$this->form->addElement ( 'static', null, $noted_message_units_weight );

  			$this->form->addElement ( 'select', "{$field}_measurement_weight_units_stat", "$this->double_indent $measurement2 Units", array (null => "", "grams" => "grams", "ounces" => "ounces", "not_answered" => "Not Answered" ) );

  			$this->XINRegisterRule ( "{$field}_measurement_weight_units_stat", array ("{$prevField}_chart{@}!={@}no_more_chart_data", "{$prevField}_chart{@}!={@}" ), "These fields are required unless not answered is selected" );

  			//Add text boxes
  			$this->form->addElement ( 'text', "{$field}_measurement_weight_$units_weight[0]", "$this->double_indent $units_weight[0]" );
  			$this->form->addElement ( 'text', "{$field}_measurement_weight_$units_weight[1]", "$this->double_indent $units_weight[1]" );

  			$this->XINRegisterRule ( "{$field}_measurement_weight_$units_weight[0]", array ("{$field}_measurement_weight_units_stat{@}=={@}grams", "{$prevField}_chart{@}!={@}no_more_chart_data" ), "Please enter grams" );
  			$this->XINRegisterRule ( "{$field}_measurement_weight_$units_weight[1]", array ("{$field}_measurement_weight_units_stat{@}=={@}ounces", "{$prevField}_chart{@}!={@}no_more_chart_data" ), "Please enter ounces" );

  			$this->form->addElement ( "static", null, "Percentile will be calculated.<BR>" ); //line space

  			$this->form->addElement ( 'text', "{$field}_weight_percentage", "$this->double_indent Percentile" );

  			$this->XINRegisterRule("{$field}_weight_percentage", array("{$field}_weight_percentage{@}=={@}NEVER_REQUIRED"));

            //*******************************************************************************BMI

        	$this->form->addElement ( 'static', null, "<b>BMI Percentile</b> (will be calculated only if the child is over 24 months)");

    		$this->form->addElement ( 'text', "{$field}_bmi", "$this->double_indent BMI" );

    		$this->XINRegisterRule("{$field}_bmi", array("{$field}_bmi{@}=={@}NEVER_REQUIRED"));

  			//*******************************************************************************Head Circ
  			$measurement3 = "Head Circ";

  			$percentage = array (null => "", 'percent' => "%ile", 'not_answered' => "Not Answered" );
  			$this->form->addElement ( 'static', null, "<b>$measurement3 Measurement <BR></b>" );
  			$this->form->addElement ( 'static', null, $noted_message_units_length );

  			$this->form->addElement ( 'select', "{$field}_measurement_head_units_stat", "$this->double_indent $measurement3 Units", $unit_array_length );

  			$this->XINRegisterRule ( "{$field}_measurement_head_units_stat", array ("{$prevField}_chart{@}!={@}no_more_chart_data", "{$prevField}_chart{@}!={@}" ), "These fields are required unless not answered is selected" );

  			//Add text boxes
  			$this->form->addElement ( 'text', "{$field}_measurement_head_$units_length[0]", "$this->double_indent $units_length[0]" );
  			$this->form->addElement ( 'text', "{$field}_measurement_head_$units_length[1]", "$this->double_indent $units_length[1]" );

  			$this->XINRegisterRule ( "{$field}_measurement_head_$units_length[0]", array ("{$field}_measurement_head_units_stat{@}=={@}cm", "{$prevField}_chart{@}!={@}no_more_chart_data" ), "Please enter centimeters" );
  			$this->XINRegisterRule ( "{$field}_measurement_head_$units_length[1]", array ("{$field}_measurement_head_units_stat{@}=={@}inches", "{$prevField}_chart{@}!={@}no_more_chart_data" ), "Please enter inches" );

  			$this->form->addElement ( "static", null, "Percentile will be calculated.<BR>" ); //line space

  			$this->form->addElement ( 'text', "{$field}_head_percentage", "$this->double_indent Percentile" );
  			
  			$this->XINRegisterRule("{$field}_head_percentage", array("{$field}_head_percentage{@}=={@}NEVER_REQUIRED"));
  			
  		}
  	}

	
    function score() {
     //  if($this->_determineDataEntryCompletionStatus() == "Incomplete") {
     //       return;
     //  }

        // Get the item scores
        $array_of_conversion=array();

        $db =& Database::singleton();


       $query = "SELECT * FROM ".$this->table." WHERE CommentID='".$this->getCommentID()."'";

       //select the row with the commentID of the row where the information is being taken
       $db->selectRow($query, $result);

        //if you cannot get the score

      // Get the subject age in months for scoring
       $administrations = array ("first" => "1", "second" => "2", "third" => "3", "fourth" => "4", "fifth" => "5", "sixth" => "6", "seventh" => "7", "eighth" => "8", "ninth" => "9", "tenth" => "10", "eleventh" => "11", "twelfth" =>"12", "thirteenth" => "13", "fourteenth" => "14", "fifteenth" => "15", "sixteenth" =>  "16", "seventeenth" => "17", "eighteenth" => "18", "nineteenth" =>"19", "twenty" => "20", "twentyone" => "21", "twentytwo" => "22", "twentythree" => "23", "twentyfour" => "24", "twentyfive" => "25", "twentysix" => "26", "twentyseven" => "27", "twentyeight" => "28", "twentynine" => "29", "thirty" => "30", "thirtyone" => "31", "thirtytwo" => "32", "thirtythree" => "33", "thirtyfour" => "34", "thirtyfive" => "35");
    
     $newValues = array();

     	while(list($field, $label) = each($administrations)){

        
        if($result["{$field}_chart"] != "no_more_chart_data"){
        
     		if($result["{$field}_measurement_length_units_stat"] == "cm"){
     			$cm_value_length = $result["{$field}_measurement_length_cm"];
     			$newValues["{$field}_measurement_length_inches"] = (1/2.54)*$cm_value_length;
     			$in_value_length = $newValues["{$field}_measurement_length_inches"];
            }
     		else if($result["{$field}_measurement_length_units_stat"] == "inches"){
     			$in_value_length = $result["{$field}_measurement_length_inches"];
     			$newValues["{$field}_measurement_length_cm"] = (2.54)*$in_value_length;
     			$cm_value_length = $newValues["{$field}_measurement_length_cm"] ;
     		}
     		else{
     			$newValues["{$field}_measurement_length_cm"] = NULL;
     			$newValues["{$field}_measurement_length_inches"] = NULL;
     		}
     		
     		if($result["{$field}_measurement_weight_units_stat"] == "grams"){
     			$grams_value = $result["{$field}_measurement_weight_grams"];
     			$newValues["{$field}_measurement_weight_ounces"] = (0.035273)*$grams_value;
 			 	}
     		else if($result["{$field}_measurement_weight_units_stat"] == "ounces"){
     			$ounces_value = $result["{$field}_measurement_weight_ounces"];
     			$newValues["{$field}_measurement_weight_grams"] = (28.35)*$ounces_value;
     			$grams_value = 	$newValues["{$field}_measurement_weight_grams"];	
     		}
     		else{
     			$newValues["{$field}_measurement_weight_ounces"] = NULL;
     			$newValues["{$field}_measurement_weight_grams"] = NULL;
     		}
     		
     		if($result["{$field}_measurement_head_units_stat"] == "cm"){
     			$cm_head_value = $result["{$field}_measurement_head_cm"];
     			$newValues["{$field}_measurement_head_inches"] = (1/2.54)*$cm_head_value;
            }
     		else if($result["{$field}_measurement_head_units_stat"] == "inches"){
     			$in_head_value = $result["{$field}_measurement_head_inches"];
     			$newValues["{$field}_measurement_head_cm"] = (2.54)*$in_head_value;
   			  $cm_head_value = $newValues["{$field}_measurement_head_cm"];
   			}
     		else{
     			$newValues["{$field}_measurement_head_cm"] = NULL;
     			$newValues["{$field}_measurement_head_inches"] = NULL;
     		}
     		
        
        $result_cand = array();
        $info_candidate = array();
         
        //Find the candidate ID
        //set for med_records_recruit - so watch out needs to be fixed
        $query = "SELECT s.CandID from session as s, flag as f where f.sessionId = s.ID and f.CommentID= '". $this->getCommentID() . "'";
               
       	$db->selectRow($query, $result_cand);
        $CandID = $result_cand["CandID"];
         	
       	$candidate_query = "SELECT * from candidate where CandID=" . $CandID;

        $db->selectRow($candidate_query, $info_candidate);
         
        //get the sex of the candidate  
        $gender = $info_candidate["Gender"];

        if($gender == "Male"){
             $gender_number = 1;
        }
 
        else{
             $gender_number = 2;
        }


       //get the date of birth
       $date_of_birth = $info_candidate["DoB"];

       //Calculate the age of the candidate for each administration
       
       $Date_taken = $result["{$field}_measurement_date"];
       
       if($Date_taken != 0000-00-00) {

         //Hard coded date of birth for testing purposes
         
         $age = Utility::calculateAge($date_of_birth, $Date_taken);

          
          $age_in_days = $age['year'] * 365 + $age['mon'] * 30 + $age['day'] ;
          $age_in_months = round($age_in_days) / 30;
          
          if($age_in_months >= 24 && $age_in_months < 24.5){
            $modified_age_one = 24;
            $modified_age_two = 24.5;
          }
          elseif($age_in_months >= 0 && $age_in_months <= 0.5){
            $modified_age_one = 0;
            $modified_age_two = 0.5;
          }  
          else{
            $round_age = round($age_in_months, 0);          
            $modified_age_one = $round_age - 0.5;
            $modified_age_two = $round_age + 0.5;
          }
                    
          if($result["{$field}_measurement_weight_units_stat"] != "not_answered"){
              
              if($age_in_months < 24){      
                  $query_table_one = "SELECT * from weight_for_age_chart where sex = $gender_number and age = $modified_age_one";
                  $query_table_two = "SELECT * from weight_for_age_chart where sex = $gender_number and age = $modified_age_two";
                }
              else{
                $query_table_one = "SELECT * from weight_for_age_chart_over_2 where sex = $gender_number and age = $modified_age_one";
                $query_table_two = "SELECT * from weight_for_age_chart_over_2 where sex = $gender_number and age = $modified_age_two";
                }      
      
            $weight_table = array();
      
            $db->selectRow($query_table_one, $weight_table_one);

            $L_one = $weight_table_one["L"];
            $M_one = $weight_table_one["M"];
            $S_one = $weight_table_one["S"];
            
            $db->selectRow($query_table_two, $weight_table_two);

            $L_two = $weight_table_two["L"];
            $M_two = $weight_table_two["M"];
            $S_two = $weight_table_two["S"];
          
            $L = interpolate($modified_age_one, $modified_age_two, $age_in_months, $L_one, $L_two);
            $M = interpolate($modified_age_one, $modified_age_two, $age_in_months, $M_one, $M_two);
            $S = interpolate($modified_age_one, $modified_age_two, $age_in_months, $S_one, $S_two);
        
        
            //find the z value from the function     
            $kgs = $grams_value/1000;
          

            if($M == 0 || $L*$S == 0) {
                // Calculating zWeight would be a div by 0.
                // Can't save "error" since the field is a float.
                $newValues["{$field}_weight_percentage"]=null;
            }
            else {
                //calculate z value
                $zWeight = ((pow(($kgs/$M), $L) - 1)/($L*$S));

                if($zWeight < -5) {
                    $newValues["{$field}_weight_percentage"]=0;
                } elseif($zWeight > 5){
                    $newValues["{$field}_weight_percentage"]=100;
                } else{
                    //calculate percentile
                    $newValues["{$field}_weight_percentage"] = round(normalDist($zWeight)*100, 2);
                    if ($newValues["{$field}_weight_percentage"] < 0){
                        $newValues["{$field}_weight_percentage"]=0;
                }
            }
         }
        }
          
          if($result["{$field}_measurement_length_units_stat"] != "not_answered"){
              if($age_in_months < 24){      
                  $query_table_one = "SELECT * from height_for_age_chart where sex = $gender_number and age = $modified_age_one";
                  $query_table_two = "SELECT * from height_for_age_chart where sex = $gender_number and age = $modified_age_two";
              }
              else{
                  $query_table_one = "SELECT * from height_for_age_chart_over_2 where sex = $gender_number and age = $modified_age_one";
                  $query_table_two = "SELECT * from height_for_age_chart_over_2 where sex = $gender_number and age = $modified_age_two";
              }
          

              $height_table = array();

              $db->selectRow($query_table_one, $height_table_one);

              $L_one = $height_table_one["L"];
              $M_one = $height_table_one["M"];
              $S_one = $height_table_one["S"];
            
              $db->selectRow($query_table_two, $height_table_two);

              $L_two = $height_table_two["L"];
              $M_two = $height_table_two["M"];
              $S_two = $height_table_two["S"];

            
              $L = interpolate($modified_age_one, $modified_age_two, $age_in_months, $L_one, $L_two);
              $M = interpolate($modified_age_one, $modified_age_two, $age_in_months, $M_one, $M_two);
              $S = interpolate($modified_age_one, $modified_age_two, $age_in_months, $S_one, $S_two);

              // save vs div by zero
              if($L == 0 || $L*$S == 0) {
                  $newValues["{$field}_percentage_length"]=null;
              } else {
                  //find the z value from the function
                  $zLength = ((pow(($cm_value_length/$M), $L) - 1)/($L*$S));

                  if($zLength < -5){
                      $newValues["{$field}_percentage_length"]=0;
                  }
                  elseif($zLength > 5){
                      $newValues["{$field}_percentage_length"]=100;
                  }

                  else{
                      //Calculate the percentile
                    $newValues["{$field}_percentage_length"] = round(normalDist($zLength)*100, 2);

                    if ($newValues["{$field}_percentage_length"] < 0){
                        $newValues["{$field}_percentage_length"]=0;
                    }
                }
              }
        
         }
            
            
            if($result["{$field}_measurement_head_units_stat"] != "not_answered"){
                if($age_in_months <= 36){    
            
                    if($age_in_months >= 24 && $age_in_months < 24.5){
                        $modified_age_one = 23.5;
                        $modified_age_two = 24.5;
                    }
            
                    elseif($modified_age_two >= 36 || $modified_age_one >= 36){
                        $modified_age_two = 36;
                        $modified_age_one = 35.5; 
                    }   
                
                    
                    $query_table_one = "SELECT * from headcirc_for_age_chart where sex = $gender_number and age = $modified_age_one";
                    $query_table_two = "SELECT * from headcirc_for_age_chart where sex = $gender_number and age = $modified_age_two";
              

                    $head_table = array();

                    $db->selectRow($query_table_one, $head_table_one);

                    $L_one = $head_table_one["L"];
                    $M_one = $head_table_one["M"];
                    $S_one = $head_table_one["S"];

                    $db->selectRow($query_table_two, $head_table_two);

                    $L_two = $head_table_two["L"];
                    $M_two = $head_table_two["M"];
                    $S_two = $head_table_two["S"];


                    $L = interpolate($modified_age_one, $modified_age_two, $age_in_months, $L_one, $L_two);
                    $M = interpolate($modified_age_one, $modified_age_two, $age_in_months, $M_one, $M_two);
                    $S = interpolate($modified_age_one, $modified_age_two, $age_in_months, $S_one, $S_two);
                    

                    if($M == 0 || $L*$S == 0) {
                        $newValues["{$field}_head_percentage"] = NULL;
                    } else {
                        $zHead = ((pow(($cm_head_value/$M), $L) - 1)/($L*$S));

                        if($zHead < -5){
                              $newValues["{$field}_head_percentage"]=0;
                        } elseif($zHead > 5) {
                              $newValues["{$field}_head_percentage"]=100;
                        } else {
                             $newValues["{$field}_head_percentage"] = round(normalDist($zHead)*100, 2);
                             if ($newValues["{$field}_head_percentage"] < 0){
                                 $newValues["{$field}_head_percentage"]=0;
                             }
                        }
                    }
                     
                     
                  } else {
                      $newValues["{$field}_head_percentage"] = NULL;
                  }
                }

            
            if(($result["{$field}_measurement_length_units_stat"] != null) && ($result["{$field}_measurement_weight_units_stat"]!= null)){

                if($age_in_months >= 24){
                    
                    $modified_age_one_bmi = $modified_age_one;
                    $modified_age_two_bmi = $modified_age_two;
                    
                    if($age_in_months >= 24 && $age_in_months < 24.5){
                            $modified_age_one_bmi = 24;
                            $modified_age_two_bmi = 24.5;
                    }
                    
                    $query_table_one = "SELECT * from bmi_for_age_chart_over_2 where sex = $gender_number and age = $modified_age_one_bmi";
                    $query_table_two = "SELECT * from bmi_for_age_chart_over_2 where sex = $gender_number and age = $modified_age_two_bmi";
                        
     		        $height = $newValues["{$field}_measurement_length_cm"]; 
     		        $weight= $newValues["{$field}_measurement_weight_grams"];
     		             			
    	            $bmi_value = (($kgs)/(($cm_value_length/100)*($cm_value_length/100)));
     	            $db->selectRow($query_table_one, $bmi_table_one); 

                    $L_one = $bmi_table_one["L"];
                    $M_one = $bmi_table_one["M"];
                    $S_one = $bmi_table_one["S"];

                    $db->selectRow($query_table_two, $bmi_table_two);

                    $L_two = $bmi_table_two["L"];
                    $M_two = $bmi_table_two["M"];
                    $S_two = $bmi_table_two["S"];


                    $L = interpolate($modified_age_one_bmi, $modified_age_two_bmi, $age_in_months, $L_one, $L_two);
                    $M = interpolate($modified_age_one_bmi, $modified_age_two_bmi, $age_in_months, $M_one, $M_two);
                    $S = interpolate($modified_age_one_bmi, $modified_age_two_bmi, $age_in_months, $S_one, $S_two);

                    $zbmi = ((pow(($bmi_value/$M), $L) - 1)/($L*$S));

                    if($zbmi < -5){
                          $newValues["{$field}_bmi"]=0;
                     }
                    elseif($zbmi > 5){
                          $newValues["{$field}_bmi"]=100;
                    }

                    else{

                        $newValues["{$field}_bmi"] = round(normalDist($zbmi)*100, 2);
                        if ($newValues["{$field}_bmi"] < 0){
                            $newValues["{$field}_bmi"]=0;
                        }
                    }
                }
                else {
                    $newValues["{$field}_bmi"] = NULL;
                }
        }
    }
}
}
    //echo("Result");
    $result = $db->update($this->table, $newValues, array('CommentID' => $this->getCommentID()));
}
}



function normalDist($zScore) {
    $p = floatval(0.2316419);
    $b1 = floatval(0.319381530);
    $b2 = floatval(-0.356563782);
    $b3 = floatval(1.781477937);
    $b4 = floatval(-1.821255978);
    $b5 = floatval(1.330274429);
    $t = 1/(1 + ($p * floatval($zScore)));
    $zx = (1/(sqrt(2 * pi())) * (exp(0 - pow($zScore, 2)/2)));

    $px = 1 - floatval($zx) * (($b1 * $t) + ($b2 * pow($t, 2)) + ($b3 * pow($t, 3)) + ($b4 * pow($t, 4)) + ($b5 * pow($t,5)));
    return $px;
}

function interpolate($age_one, $age_two, $real_age, $value_one, $value_two){
    $real_value = $value_one + (($real_age - $age_one)* (($value_two - $value_one)/($age_two - $age_one)));
  return $real_value;
}
    
?>
