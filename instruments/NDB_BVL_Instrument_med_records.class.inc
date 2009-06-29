<?php

class NDB_BVL_Instrument_med_records extends NDB_BVL_Instrument {
	
	var $yesNo = array (null => "", 'yes' => "Yes", 'no' => "No", 'not_specified' => "Not Specified in records", 'not_answered' => "Not Answered" );
	var $normal_abnormal_FX = array (null => "", 'normal' => "NORMAL (no FX)", 'abnormal' => "ABNORMAL (has FX)", 'not_answered' => "Not Answered" );
	var $normal_abnormal_TS = array (null => "", 'normal' => "NORMAL (no TS)", 'abnormal' => "ABNORMAL (has TS)", 'not_answered' => "Not Answered" );
	var $normal_abnormal_NF = array (null => "", 'normal' => "NORMAL (no NF)", 'abnormal' => "ABNORMAL (has NF)", 'not_answered' => "Not Answered" );
	var $chart_actual = array (null => "", "not_answered" => "Not Answered", "actual" => "Actual", "chart" => "Chart" );

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
		$this->form = new HTML_Quickform ( 'test_form' );
		$this->page = $page; // page label (number or
		// string - used by
		// user-defined child classes)

		// data keyed by commentID
		$this->commentID = $commentID;
		
		//The array of dates/timestamps to convert to database dates/timestamps
		//Any HTML_Quickform date elements must be listed here
		$this->dateTimeFields = array ("Date_taken"); //Other date fields are added automatically through $this->addDateElement();
		
		$this->_requiredElements = array ('Examiner', 'Date_taken', 'first_chart', 'tested_of_fragile_x' );
		
		$config = & NDB_Config::singleton ();
		$this->dateOptions = array ('language' => 'en', 'format' => 'YMd', 'minYear' => $config->getSetting ( 'startYear' ), //allows for siblings up to 20 years older than candidate
'maxYear' => $config->getSetting ( 'endYear' ), 'addEmptyOption' => true, 'emptyOptionValue' => null );

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
    	if(ereg("(_page[0-9]+)",$this->page,$matches)){
            call_user_method($matches[1], &$this);
        } else {
            $this->_main();
        }

        //Defines the call back function for HTML Quickform to use when validating the form.
        $this->form->addFormRule(array(&$this,'XINValidate'));
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
		$this->addTextElement ( "other_genetic_tests_completed_specify", $this->indent . "If yes, specify what test and result:", array ("other_genetic_tests_completed{@}=={@}yes" ), "This field is required." );
		$this->form->addElement ( "static", null, "<BR>" ); //line space
	}
	
	function _page2() {
		$this->form->addElement ( 'header', null, "Growth Chart Information:" );
		$this->form->addElement ( "static", null, "<BR>" ); //line space
		$this->form->addElement ( "static", null, "<BR>" ); //line space
		$this->form->addElement ( "static", null, "Units will be automatically converted, if you would like to see the conversion results please exit this page and re-enter it.<BR>" );
		$this->form->addElement ( "static", null, "If you select no more growth data, no more data needs to be entered into the form after that point.<BR>" );

		//Source of information
		$administrations = array ("first" => "1", "second" => "2", "third" => "3", "fourth" => "4", "fifth" => "5", "sixth" => "6", "seventh" => "7", "eighth" => "8" );
		
		reset ( $administrations );
		
		while ( list ( $field, $label ) = each ( $administrations ) ) {
			
			$this->form->addElement ( "static", null, "<BR>" ); //line space
			

			$this->form->addElement ( "static", null, "<BR>" ); //line space
			

			$this->form->addElement ( "select", "{$field}_chart", "<b> $label . Source of Information</b> <BR> Selecting chart indicates measurements were taken from a growth chart. <BR> Selecting actual indicates the measurements entered were the actual measurements taken.", array (NULL => "", "not_answered" => "Not Answered", "actual" => "Actual", "chart" => "Chart", "not_answered" => "Not Answered", "no_more_chart_data" => "No More Growth Data" ) );
			
			//Once "No More Growth Data" is selected once, nothing further is required.
			$this->XINRegisterRule ( "{$field}_chart", array ("{$prevField}_chart{@}!={@}no_more_chart_data", "{$prevField}_chart{@}!={@}" ), "These fields are required unless no more growth data is selected" );
			$this->form->addRule ( "first_chart", "Must answer no more growth data, not answered, actual or chart", 'required' );
			
			prev ( $administrations );
			$prevField = key ( $administrations );
			next ( $administrations );
			
			$config = & NDB_Config::singleton ();
			$this->dateOptions = array ('language' => 'en', 'format' => 'YMd', 'minYear' => $config->getSetting ( 'startYear' ) - 20, //allows for siblings up to 20 years older than candidate
'maxYear' => $config->getSetting ( 'endYear' ), 'addEmptyOption' => true, 'emptyOptionValue' => null );
			
			$this->addDateElement("{$field}_measurement", "Date of Administration");
			$this->XINRegisterRule ( "{$field}_measurement_date", array ("{$field}_measurement_date_status{@}=={@}", "{$prevField}_chart{@}!={@}no_more_chart_data", "{$prevField}_chart{@}!={@}" ), "The date is required unless not answered is selected" );
			
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
			
			$this->form->addElement ( 'text', "{$field}_percentage_length", "$this->double_indent Percentile" );
			
			$this->XINRegisterRule ( "{$field}_percentage_length", array ("{$field}_measurement_length_units_stat{@}!={@}not_answered", "{$field}_measurement_length_units_stat{@}!={@}" ), "Please enter a percentile" );
			
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
			
			$this->form->addElement ( 'text', "{$field}_weight_percentage", "$this->double_indent Percentile" );
			
			$this->XINRegisterRule ( "{$field}_weight_percentage", array ("{$field}_measurement_weight_units_stat{@}!={@}not_answered", "{$field}_measurement_weight_units_stat{@}!={@}" ), "Please enter a percentile" );
			
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
			
			$this->form->addElement ( 'text', "{$field}_head_percentage", "$this->double_indent Percentile" );
			
			$this->XINRegisterRule ( "{$field}_head_percentage", array ("{$field}_measurement_head_units_stat{@}!={@}not_answered", "{$field}_measurement_head_units_stat{@}!={@}" ), "Please enter a percentile" );
		}
	}

	function score() {
		if ($this->_determineDataEntryCompletionStatus () == "Incomplete") {
			return;
		}
		
		// Get the item scores
		$array_of_conversion = array ();
		
		$db = & Database::singleton ();
		if (PEAR::isError ( $db )) {
			return PEAR::raiseError ( "Could not connect to database: " . $db->getMessage () );
		}
		
		$query = "SELECT * FROM " . $this->table . " WHERE CommentID='" . $this->getCommentID () . "'";
		
		//select the row with the commentID of the row where the information is being taken
		$db->selectRow ( $query, $result );
		
		//if you cannot get the score
		if (PEAR::isError ( $score_record )) {
			return PEAR::raiseError ( "Could not get scores: " . $score_record->getMessage () );
		}
		
		// Get the subject age in months for scoring
		$administrations = array ("first" => "1", "second" => "2", "third" => "3", "fourth" => "4", "fifth" => "5", "sixth" => "6", "seventh" => "7", "eighth" => "8" );
		
		$newValues = array ();
		
		while ( list ( $field, $label ) = each ( $administrations ) ) {
			
			if ($result ["{$field}_measurement_length_units_stat"] == "cm") {
				$cm_value = $result ["{$field}_measurement_length_cm"];
				$newValues ["{$field}_measurement_length_inches"] = round((1 / 2.54) * $cm_value, 2);
			} else if ($result ["{$field}_measurement_length_units_stat"] == "inches") {
				$in_value = $result ["{$field}_measurement_length_inches"];
				$newValues ["{$field}_measurement_length_cm"] = round((2.54) * $in_value, 2);
			} else {
				$newValues ["{$field}_measurement_length_cm"] = NULL;
				$newValues ["{$field}_measurement_length_inches"] = NULL;
			
			}
			
			if ($result ["{$field}_measurement_weight_units_stat"] == "grams") {
				$grams_value = $result ["{$field}_measurement_weight_grams"];
				$newValues ["{$field}_measurement_weight_ounces"] = round((1 / 28.3495231) * $grams_value, 2);
			} else if ($result ["{$field}_measurement_weight_units_stat"] == "ounces") {
				$ounces_value = $result ["{$field}_measurement_weight_ounces"];
				$newValues ["{$field}_measurement_weight_grams"] = round((28.3495231) * $ounces_value);
			} else {
				$newValues ["{$field}_measurement_weight_ounces"] = NULL;
				$newValues ["{$field}_measurement_weight_grams"] = NULL;
			
			}
			
			if ($result ["{$field}_measurement_head_units_stat"] == "cm") {
				$cm_head_value = $result ["{$field}_measurement_head_cm"];
				$newValues ["{$field}_measurement_head_inches"] = round((1 / 2.54) * $cm_head_value, 2);
			} else if ($result ["{$field}_measurement_head_units_stat"] == "inches") {
				$in_head_value = $result ["{$field}_measurement_head_inches"];
				$newValues ["{$field}_measurement_head_cm"] = round((2.54) * $in_head_value, 2);
			} else {
				$newValues ["{$field}_measurement_head_cm"] = NULL;
				$newValues ["{$field}_measurement_head_inches"] = NULL;
			
			}
		}
		
		$result = $db->update ( $this->table, $newValues, array ('CommentID' => $this->getCommentID () ) );
		if ($db->isError ( $result )) {
			return PEAR::raiseError ( "Could not save total score: " . $result->getMessage () );
		
		}
	}

}

?>
