<?php

require_once 'HTML/QuickForm.php';
require_once 'HTML/QuickForm/Renderer/Array.php';

class NDB_BVL_Instrument_figs_year3 extends NDB_BVL_Instrument
{
    
    var $_relationshipCodeRegex = '/^MOM|DAD|MGM|MGF|PGM|PGF|FX|MX|PX|HX|(FB|FS|HB|HS|CID|CIS|MA|MU|PA|PU)[0-9]+$/';
    
    var $scoreCols = array('ADHD','Alcohol','ASP','Depression','Drug_substance','Nicotine','Mania','OCD','Paranoid','Psychosis','Tic');
    var $scoreColsRelative = array('Score_adhd_combined','Score_adhd_inattentive','Score_adhd_hyperactive','Score_alcohol_abuse','Score_alcohol_dependence','Score_alcohol_nicotine','Score_alcohol_drug_substance','Score_asp','Score_depression','Score_chronic_depression','Score_recurrent_depression','Score_mania','Score_ocd','Score_paranoid_personality','Score_pervasive_development','Score_schizoid','Score_schizotypal','Score_psychosis_schizophrenia','Score_psychosis_depression','Score_psychosis_mania','Score_tic_tourettes','Score_tic_motor_c','Score_tic_vocal_c','Score_tic_motor_t','Score_tic_vocal_t');
    
    var $ValidityEnabled = false;
    var $ValidityRequired= false;
    /**
     * Array of column names to be ignored by the double data entry conflict detector.
     */
    /**
    * sets up basic data, such as the HTML_Quickform object, and so on.
    *
    * @param string $commentID  the CommentID identifying the data to load
    * @param string $page if a multipage form, the page to show
    * @return void
    * @access public
    */
    function setup($commentID, $page)
    {
        require_once("RequiredIf.inc");
        
        $this->form = new HTML_Quickform('test_form');
        $this->form->registerRule('requiredIf', null, 'HTML_QuickForm_Rule_RequiredIf', 'RequiredIf.inc');
        
        if(!empty($_REQUEST['relativeID'])) {
            $this->relativeID = $_REQUEST['relativeID'];
            $this->page = $_REQUEST['checklist'];
            $this->table = 'figs_year3_relatives';
        } else {
            $this->page = null;
            $this->table = 'figs_year3';
        }
        
        // set the object properties
        $this->testName = "figs_year3";           // test_names.Test_name
        // data keyed by commentID
        $this->commentID = $commentID;

	$this->_doubleDataEntryDiffIgnoreColumns = array('CommentID', 'UserID', 'Testdate', 'Data_entry_completion_status', 'RelativeID',  'Window_Difference', 'Candidate_Age',
							 'Face_CauseOfDeath',
							 'Face_Comments',
							 'Other_Narrative',
							 'Other_Q1_Disorder',
							 'Other_Q1a_Description',
							 'Depression_Q1cDescription',
							 'Depression_Q1dDescription',
							 'Depression_Q1eDescription',
							 'Depression_Q2Description',
							 'Mania_Q1bDescription',
							 'Mania_Q1cDescription',
							 'Mania_Q1dDescription',
							 'Mania_Q1eDescription',
							 'Mania_Q2Description',
							 'Psychosis_Q1_Beliefs',
							 'Psychosis_Q1eDescription',
							 'Psychosis_Q1hDescription',
							 'Psychosis_Q5Description',
							 'Psychosis_Q11Description',
							 'Alcohol_Q2Description',
							 'Alcohol_Q6_WhichDrugs',
							 'Alcohol_Q6a_MostProblemDrug1',
							 'Alcohol_Q6a_MostProblemDrug2',
							 'Alcohol_Q6a_MostProblemDrug3',
							 'Alcohol_Q8Description',
							 'Alcohol_Q13_WhichNicotine',
							 'Schizoid_Q4aDescription',
							 'Tic_Q1Description',
							 'Tic_Q2Description',
							 'Tic_Q3aDescription',
							 'OCD_Q3b_Duration',
							 'OCD_Q4aDescription',
							 'ADHD_Q1k2_Grade',
							 'ADHD_Q3aDescription',
                             'DataEntryCompleted' /* For relatives data entry completion*/
                         );
        $this->_doubleDataEntryDiffIgnoreColumns = array_merge($this->_doubleDataEntryDiffIgnoreColumns, $this->scoreCols, $this->scoreColsRelative);
	

        
        // setup the form
        $this->_setupForm();
    }
    
    // Computes the difference between two instances of an instrument
    function diff($otherInstrument) {
        $db =& Database::singleton();

        // Load this instance data
        $thisData = NDB_BVL_Instrument::loadInstanceData($this);
        // Load other instance data
        $otherData = NDB_BVL_Instrument::loadInstanceData($otherInstrument);
        // Create the return object data structure
        $diff = array();

        // Loop over this instance data
        foreach($thisData AS $key=>$value) {
            if(!in_array($key, $this->_doubleDataEntryDiffIgnoreColumns)) {
                if($otherData[$key] != $value) {
                    $diff[] = array('TableName'=>$this->table, 'ExtraKeyColumn'=>null, 'ExtraKey1'=>' ', 'ExtraKey2'=>' ', 'FieldName'=>$key, 'CommentId1'=>$this->getCommentID(), 'Value1'=>$value, 'CommentId2'=>$otherInstrument->getCommentID(), 'Value2'=>$otherData[$key]);
                }
            }
        }

        $this_RelatedData = $db->pselect("SELECT * FROM figs_year3_relatives WHERE CommentID=:CID", array('CID' => $this->getCommentID()));
        foreach($this_RelatedData as $relative) {
            foreach ($relative as $key=>$value) {
            $db->selectRow("SELECT * FROM figs_year3_relatives WHERE CommentID='" . $otherInstrument->getCommentID() . "' AND RelativeCode='" . $relative['RelativeCode'] . "'", $other_RelatedData);
            if(!in_array($key, $this->_doubleDataEntryDiffIgnoreColumns)) {
                if($other_RelatedData[$key] != $value) {
                    $RCode = $relative['RelativeCode'] == null ? ' ' : $relative['RelativeCode'];
                    $Rel_RCode = $other_RelatedData['RelativeCode'] == null ? ' ' : $other_RelatedData['RelativeCode'];

                    $diff[] = array('TableName'=> "figs_year3_relatives", 'ExtraKeyColumn'=>'RelativeCode', 'ExtraKey1'=> $RCode, 'ExtraKey2'=> $Rel_RCode, 'FieldName'=>$key, 'CommentId1'=>$this->getCommentID(), 'Value1'=>$value, 'CommentId2'=>$otherInstrument->getCommentID(), 'Value2'=>$other_RelatedData[$key]);
                }
            }
            }
        }


        // Return the diffs
        return $diff;
    }

    /**
    * method to build the HTML_Quickform object into a complete FIGS Relatives form
    *
    * @return void
    * @access private
    */
    
    // This calls the button javascript
    function _setupForm()
    {
        // Display test name
        $titleSuffix = '';
        if(!empty($this->relativeID)) {
            $relatives = $this->_getRelatives();
            if($relatives !== false) {
                $relativeCode = $relatives[$this->relativeID];
                if(!empty($relativeCode)) $titleSuffix = " - $relativeCode";
            }
        }
        $this->form->addElement('header', 'instrument_title', $this->getFullName().$titleSuffix);
        
        $candID = isset($_REQUEST['candID']) ? $_REQUEST['candID'] : '';
        $sessionID = isset($_REQUEST['sessionID']) ? $_REQUEST['sessionID'] : '';
        $url = "main.php?test_name=figs_year3&candID=$candID&sessionID=$sessionID&commentID=".$this->getCommentID();
        
        // checklists display
        if($this->page == 'checklists') {
            $this->form->addElement('link', null, 'Return to relatives screen', "$url", 'Back');
        
        // any checklist display
        } elseif (!empty($this->page)) {
            $this->form->addElement('link', null, 'Return to checklists screen', "$url&relativeID=".$this->relativeID."&checklist=checklists", 'Back');
        }
        
        switch($this->page) {
        case "checklists":
            $this->_setupFigsRelativesChecklist();
            break;
        case "face":
            $this->_setupFigsRelativesFaceSheet();
            break;
        case "other":
            $this->_setupFigsRelativesOtherDisorders();
            break;
        case "screening":
            $this->_setupFigsRelativesGeneralScreening();
            break;
        case "depression":
            $this->_setupFigsRelativesDepression();
            break;
        case "mania":
            $this->_setupFigsRelativesMania();
            break;
        case "psychosis":
            $this->_setupFigsRelativesPsychosis();
            break;
        case "alcohol":
            $this->_setupFigsRelativesAlcohol();
            break;
        case "drugs":
            $this->_setupFigsRelativesDrugs();
            break;
       case "nicotine":
            $this->_setupFigsRelativesNicotine();
            break;
        case "schizoid":
            $this->_setupFigsRelativesSchizoid();
            break;
        case "asp":
            $this->_setupFigsRelativesASP();
            break;
        case "tic":
            $this->_setupFigsRelativesTic();
            break;
        case "ocd":
            $this->_setupFigsRelativesOCD();
            break;
        case "adhd":
            $this->_setupFigsRelativesADHD();
            break;
        default:
            $this->_setupFigsRelatives();
            break;
        }
        
    } // End function
    
    /**
    * method to display the form - overridden only because of FIGS's internal switchboard
    *
    * @return void
    * @access public
    */
    function display()
    {
        $testName = isset($_REQUEST['test_name']) ? $_REQUEST['test_name'] : '';
        $candID= isset($_REQUEST['candID']) ? $_REQUEST['candID'] : '';
        $sessionID= isset($_REQUEST['sessionID']) ? $_REQUEST['sessionID'] : '';
    	$formAttribsArray = "main.php?test_name=$testName&candID=$candID&sessionID=$sessionID&commentID=".$this->getCommentID();
        if (!empty($this->relativeID)) {
        	$formAttribsArray .= '&relativeID='.$this->relativeID;
        }
        if (!empty($this->page)) {
        	$formAttribsArray .= '&checklist='.$this->page;
        }
        $this->form->updateAttributes(array('action'=>$formAttribsArray));

        if(!$this->form->isFrozen()) {
            $buttons[] = $this->form->createElement('submit', 'fire_away', 'Save Data', 'class=button');
            //$buttons[] = $this->form->createElement('reset', null, 'Reset');
            $this->form->addGroup($buttons, null, null, "&nbsp;");
        }
        
        // get saved data to pre-populate form
        $relativeWhere = '';
        if(!empty($this->relativeID)) {
            $relativeWhere = "AND RelativeID='".$this->relativeID."'";
        }
        $GLOBALS['DB']->select("SELECT * FROM $this->table WHERE CommentID='".$this->getCommentID()."' $relativeWhere", $defaults);
        
        // set the defaults (call private method _setDefaultsArray
        // which could be overridden if necessary)
        $defaults = $this->_setDefaultsArray($defaults[0]);
        
        // merge in the localDefaults property so that simple
        // additions to the defaults array no longer requires
        // overriding the _setDefaultsArray method
        $defaults = array_merge($defaults, $this->localDefaults);
        
        // actually set the quickform object defaults
        $this->form->setDefaults($defaults);
        
        // display the HTML_Quickform object
        return $this->form->toHTML();
    }
    

    /**
    * accepts an array usable as input to HTML_Quickform::setDefaults()
    * and does any necessary preprocessing on that array.
    *
    * @param array $defaults    the array to be passed on to
    * HTML_Quickform::setDefaults()
    * @return array             the processed array ready for setDefaults()
    * @access private
    */
    function _setDefaultsArray($defaults)
    {
        // split mysql Date_taken field into array
        $Date_taken = explode('-', $defaults['Date_taken']);
        $defaults['Date_taken'] = array('Y'=>$Date_taken[0], 'M'=>$Date_taken[1], 'd'=>$Date_taken[2]);
        
        if(isset($defaults['Face_BirthDate'])) {
            $date = explode('-', $defaults['Face_BirthDate']);
            if(count($date) >= 2) {
                $defaults['Face_BirthDate'] = array('Y'=>$date[0], 'M'=>$date[1], 'd'=>$date[2]);
            }

            if($defaults['Face_BirthDate']['Y'] == '0000') {
                $defaults['Face_BirthDate']['Y'] = NULL; 
            }
        }
        // return the defaults array ready for $form->setDefaults
        return $defaults;
    }
    
    /**
    * preprocesses the array of values to be saved into the database
    * (such as to rearrange date fields)
    *
    * @param array $values      the array of values ready to be passed to
    * an Database::update call as the set array
    * @return void
    * @access private
    */
    function _saveValues($values)
    {   
        if($values['ClearInstrument']== 1) {
           return NULL; 
        }
        $this->_nullStatus($values);
        if(isset($values['Date_taken'])) {
            $Date_taken = $values['Date_taken'];
            $values['Date_taken'] = $this->_getDatabaseDate($Date_taken);
            $this->_saveCandidateAge($values);

        }
        
        if(isset($values['Face_BirthDate'])) {
            $date = $values['Face_BirthDate'];
            if(empty($date['Y'])) $date['Y']='0000';
            if(empty($date['M'])) $date['M']=0;
            if(empty($date['d'])) $date['d']=0;
            $values['Face_BirthDate'] = "$date[Y]-$date[M]-$date[d]";
            if($values['Face_BirthDate'] == '0000-0-0') $values['Face_BirthDate'] = null;
        }
        
        // if we're saving the checklist page, nullify all the fields for each of the not-administered checklists
        if(!empty($this->relativeID) && $_REQUEST['checklist']=='checklists') {
            // nullify fields for the not administered checklists
            
            if($values['Checklist_Other']=='N') $values = array_merge($values, array('Other_Narrative'=>null, 'Other_Q1_Disorder'=>null, 'Other_Q1a_Treatment1'=>null, 'Other_Q1a_Treatment2'=>null,'Other_Q1a_Treatment3'=>null,'Other_Q1a_Treatment4'=>null,'Other_Q1a_Treatment5'=>null,'Other_Q1a_Treatment6'=>null, 'Other_Q1b_OnsetAge'=>null, 'Other_Q1bNA'=>null, 'Other_Q1c_Episodes'=>null, 'Other_Q1cNA'=>null, 'Other_Q1d_Duration'=>null, 'Other_Q1dNA'=>null, 'Other_Q1e_Impairment'=>null));
            
            if($values['Checklist_Depression']=='N') $values = array_merge($values, array('Depression_Q1a'=>null, 'Depression_Q1b'=>null, 'Depression_Q1c'=>null, 'Depression_Q1cDescription'=>null, 'Depression_Q1d'=>null, 'Depression_Q1dDescription'=>null, 'Depression_Q1e'=>null, 'Depression_Q1eDescription'=>null, 'Depression_Q1f'=>null, 'Depression_Q1g'=>null, 'Depression_Q1h'=>null, 'Depression_Q1i'=>null, 'Depression_Q1j'=>null, 'Depression_Q1k'=>null, 'Depression_Q1l'=>null, 'Depression_Q2_Treatment1'=>null, 'Depression_Q2_Treatment2'=>null,'Depression_Q2_Treatment3'=>null,'Depression_Q2_Treatment4'=>null,'Depression_Q2_Treatment5'=>null,'Depression_Q2_Treatment6'=>null, 'Depression_Q2Description'=>null, 'Depression_Q3_Age'=>null, 'Depression_Q3NA'=>null, 'Depression_Q4_Episodes'=>null, 'Depression_Q4NA'=>null, 'Depression_Q5_Duration'=>null, 'Depression_Q5NA'=>null, 'Depression_Q6_Current'=>null, 'Depression_Q7_Recent'=>null, 'Depression_Q7NA'=>null, 'Depression_Q8_Impairment'=>null, 'Depression_Q9_Reliability'=>null));
            
            if($values['Checklist_Mania']=='N') $values = array_merge($values, array('Mania_Q1a'=>null, 'Mania_Q1b'=>null, 'Mania_Q1bDescription'=>null, 'Mania_Q1c'=>null, 'Mania_Q1cDescription'=>null, 'Mania_Q1d'=>null, 'Mania_Q1dDescription'=>null, 'Mania_Q1e'=>null, 'Mania_Q1eDescription'=>null, 'Mania_Q1f'=>null, 'Mania_Q1g'=>null, 'Mania_Q1h'=>null, 'Mania_Q1i'=>null, 'Mania_Q1j'=>null, 'Mania_Q1k'=>null, 'Mania_Q1l'=>null, 'Mania_Q2_Treatment1'=>null, 'Mania_Q2_Treatment2'=>null,'Mania_Q2_Treatment3'=>null,'Mania_Q2_Treatment4'=>null,'Mania_Q2_Treatment5'=>null,'Mania_Q2_Treatment6'=>null, 'Mania_Q2Description'=>null, 'Mania_Q3_Age'=>null, 'Mania_Q3NA'=>null, 'Mania_Q4_Episodes'=>null, 'Mania_Q4NA'=>null, 'Mania_Q5_Duration'=>null, 'Mania_Q5NA'=>null, 'Mania_Q6_Recent'=>null, 'Mania_Q6NA'=>null, 'Mania_Q7_Impairment'=>null, 'Mania_Q8_Reliability'=>null));
            
            if($values['Checklist_Psychosis']=='N') $values = array_merge($values, array('Psychosis_Q1_Beliefs'=>null, 'Psychosis_Q1a'=>null, 'Psychosis_Q1b'=>null, 'Psychosis_Q1c'=>null, 'Psychosis_Q1d'=>null, 'Psychosis_Q1e'=>null, 'Psychosis_Q1eDescription'=>null, 'Psychosis_Q1f'=>null, 'Psychosis_Q1g'=>null, 'Psychosis_Q1gDescription'=>null, 'Psychosis_Q1h'=>null, 'Psychosis_Q1hDescription'=>null, 'Psychosis_Q1i'=>null, 'Psychosis_Q1j'=>null, 'Psychosis_Q2_Duration'=>null, 'Psychosis_Q2NA'=>null, 'Psychosis_Q3_MoodDisturbance'=>null, 'Psychosis_Q4_NoDepression'=>null, 'Psychosis_Q5_Treatment1'=>null, 'Psychosis_Q5_Treatment2'=>null,'Psychosis_Q5_Treatment3'=>null,'Psychosis_Q5_Treatment4'=>null,'Psychosis_Q5_Treatment5'=>null,'Psychosis_Q5_Treatment6'=>null, 'Psychosis_Q5Description'=>null, 'Psychosis_Q6_Age'=>null, 'Psychosis_Q6NA'=>null, 'Psychosis_Q7_Episodes'=>null, 'Psychosis_Q7NA'=>null, 'Psychosis_Q8Weeks_Duration'=>null, 'Psychosis_Q8Years_Duration'=>null, 'Psychosis_Q8NA'=>null, 'Psychosis_Q9_Current'=>null, 'Psychosis_Q10_Impairment'=>null, 'Psychosis_Q11_Substance'=>null, 'Psychosis_Q11Description'=>null, 'Psychosis_Q12_Reliability'=>null));
            
            if($values['Checklist_Alcohol']=='N') $values = array_merge($values, array('Alcohol_Q1a'=>null, 'Alcohol_Q1b'=>null, 'Alcohol_Q1c'=>null, 'Alcohol_Q1d'=>null, 'Alcohol_Q1e'=>null, 'Alcohol_Q1f'=>null, 'Alcohol_Q1g'=>null, 'Alcohol_Q1h'=>null, 'Alcohol_Q1i'=>null, 'Alcohol_Q1j'=>null, 'Alcohol_Q1k'=>null, 'Alcohol_Q1l'=>null, 'Alcohol_Q1m'=>null, 'Alcohol_Q2_Treatment1'=>null, 'Alcohol_Q2_Treatment2'=>null,'Alcohol_Q2_Treatment3'=>null,'Alcohol_Q2_Treatment4'=>null,'Alcohol_Q2_Treatment5'=>null,'Alcohol_Q2_Treatment6'=>null, 'Alcohol_Q2Description'=>null, 'Alcohol_Q3_Current'=>null, 'Alcohol_Q4_OnsetAge'=>null, 'Alcohol_Q4NA'=>null, 'Alcohol_Q5_RecoverAge'=>null, 'Alcohol_Q5NA'=>null, 'Alcohol_Q5a_Reliability'=>null));
            
            
            if($values['Checklist_Drugs']=='N') $values = array_merge($values, array('Alcohol_Q6_WhichDrugs'=>null, 'Alcohol_Q6a_MostProblemDrug1'=>null, 'Alcohol_Q6a_MostProblemDrug2'=>null, 'Alcohol_Q6a_MostProblemDrug3'=>null, 'Alcohol_Q7a'=>null, 'Alcohol_Q7b'=>null, 'Alcohol_Q7c'=>null, 'Alcohol_Q7d'=>null, 'Alcohol_Q7e'=>null, 'Alcohol_Q7f'=>null, 'Alcohol_Q8_Treatment1'=>null, 'Alcohol_Q8_Treatment2'=>null,'Alcohol_Q8_Treatment3'=>null,'Alcohol_Q8_Treatment4'=>null,'Alcohol_Q8_Treatment5'=>null,'Alcohol_Q8_Treatment6'=>null, 'Alcohol_Q8Description'=>null, 'Alcohol_Q9_Current'=>null, 'Alcohol_Q10_OnsetAge'=>null, 'Alcohol_Q10NA'=>null, 'Alcohol_Q11_RecoverAge'=>null, 'Alcohol_Q11NA'=>null, 'Alcohol_Q12_Reliability'=>null));
            
            
            if($values['Checklist_Nicotine']=='N') $values = array_merge($values, array('Alcohol_Q13_WhichNicotine'=>null, 'Alcohol_Q13a_Daily'=>null, 'Alcohol_Q14a'=>null, 'Alcohol_Q14d'=>null, 'Alcohol_Q16_Current'=>null, 'Alcohol_Q17_OnsetAge'=>null, 'Alcohol_Q17NA'=>null, 'Alcohol_Q18_RecoverAge'=>null, 'Alcohol_Q18NA'=>null, 'Alcohol_Q19_Reliability'=>null));
            
            if($values['Checklist_Schizoid']=='N') $values = array_merge($values, array('Schizoid_Q1a'=>null, 'Schizoid_Q1b'=>null, 'Schizoid_Q1c'=>null, 'Schizoid_Q1d'=>null, 'Schizoid_Q1e'=>null, 'Schizoid_Q1f'=>null, 'Schizoid_Q1g'=>null, 'Schizoid_Q2a'=>null, 'Schizoid_Q2b'=>null, 'Schizoid_Q2c'=>null, 'Schizoid_Q2d'=>null, 'Schizoid_Q2e'=>null, 'Schizoid_Q2f'=>null, 'Schizoid_Q2g'=>null, 'Schizoid_Q2h'=>null, 'Schizoid_Q2i'=>null, 'Schizoid_Q2j'=>null, 'Schizoid_Q2k'=>null, 'Schizoid_Q3a'=>null, 'Schizoid_Q3b'=>null, 'Schizoid_Q3c'=>null, 'Schizoid_Q3d'=>null, 'Schizoid_Q3e'=>null, 'Schizoid_Q3f'=>null, 'Schizoid_Q3g'=>null, 'Schizoid_Q4a_Treatment1'=>null, 'Schizoid_Q4a_Treatment2'=>null,'Schizoid_Q4a_Treatment3'=>null,'Schizoid_Q4a_Treatment4'=>null,'Schizoid_Q4a_Treatment5'=>null,'Schizoid_Q4a_Treatment6'=>null, 'Schizoid_Q4aDescription'=>null, 'Schizoid_Q4b_OnsetAge'=>null, 'Schizoid_Q4bNA'=>null, 'Schizoid_Q4c_Impairment'=>null, 'Schizoid_Q4d_SocialProbs'=>null, 'Schizoid_Q4e_Unhappiness'=>null, 'Schizoid_Q4f_Before17Yrs'=>null, 'Schizoid_Q4g_Before3Yrs'=>null, 'Schizoid_Q4h_Reliability'=>null));
            
            if($values['Checklist_ASP']=='N') $values = array_merge($values, array('ASP_Q1a'=>null, 'ASP_Q1b'=>null, 'ASP_Q1c'=>null, 'ASP_Q1d'=>null, 'ASP_Q1e'=>null, 'ASP_Q1f'=>null, 'ASP_Q1g'=>null, 'ASP_Q2_Over15Yrs'=>null, 'ASP_Q3_Under15Yrs'=>null));
            
            if($values['Checklist_Tic']=='N') $values = array_merge($values, array('Tic_Q1'=>null, 'Tic_Q1Description'=>null, 'Tic_Q1a'=>null, 'Tic_Q1b'=>null, 'Tic_Q1c'=>null, 'Tic_Q1d'=>null, 'Tic_Q2'=>null, 'Tic_Q2Description'=>null, 'Tic_Q2a'=>null, 'Tic_Q2b'=>null, 'Tic_Q2c'=>null, 'Tic_Q2d'=>null, 'Tic_Q3a_Treatment1'=>null, 'Tic_Q3a_Treatment2'=>null,'Tic_Q3a_Treatment3'=>null,'Tic_Q3a_Treatment4'=>null,'Tic_Q3a_Treatment5'=>null,'Tic_Q3a_Treatment6'=>null, 'Tic_Q3aDescription'=>null, 'Tic_Q3b_OnsetAge'=>null, 'Tic_Q3bNA'=>null, 'Tic_Q3c_Episodes'=>null, 'Tic_Q3cNA'=>null, 'Tic_Q3d_Duration'=>null, 'Tic_Q3dNA'=>null, 'Tic_Q3e_Impairment'=>null, 'Tic_Q3f_Reliability'=>null));
            
            if($values['Checklist_OCD']=='N') $values = array_merge($values, array('OCD_Q1a'=>null, 'OCD_Q1b'=>null, 'OCD_Q1c'=>null, 'OCD_Q1d'=>null, 'OCD_Q2a'=>null, 'OCD_Q2b'=>null, 'OCD_Q3a'=>null, 'OCD_Q3b_Duration'=>null, 'OCD_Q3bNA'=>null, 'OCD_Q4a_Treatment1'=>null, 'OCD_Q4a_Treatment2'=>null,'OCD_Q4a_Treatment3'=>null,'OCD_Q4a_Treatment4'=>null,'OCD_Q4a_Treatment5'=>null,'OCD_Q4a_Treatment6'=>null, 'OCD_Q4aDescription'=>null, 'OCD_Q4b_OnsetAge'=>null, 'OCD_Q4bNA'=>null, 'OCD_Q4c_Episodes'=>null, 'OCD_Q4cNA'=>null, 'OCD_Q4d_Duration'=>null, 'OCD_Q4dNA'=>null, 'OCD_Q4e_Impairment'=>null, 'OCD_Q4f_Reliability'=>null));
            
            if($values['Checklist_ADHD']=='N') $values = array_merge($values, array('ADHD_Q1a'=>null, 'ADHD_Q1b'=>null, 'ADHD_Q1c'=>null, 'ADHD_Q1d'=>null, 'ADHD_Q1e'=>null, 'ADHD_Q1f'=>null, 'ADHD_Q1g'=>null, 'ADHD_Q1h'=>null, 'ADHD_Q1i'=>null, 'ADHD_Q1j'=>null, 'ADHD_Q1k1'=>null, 'ADHD_Q1k2_Grade'=>null, 'ADHD_Q1k2NA'=>null, 'ADHD_Q1l1'=>null, 'ADHD_Q1l2'=>null, 'ADHD_Q1l3'=>null, 'ADHD_Q2a'=>null, 'ADHD_Q2b'=>null, 'ADHD_Q2c'=>null, 'ADHD_Q2d'=>null, 'ADHD_Q2e'=>null, 'ADHD_Q2f'=>null, 'ADHD_Q2g'=>null, 'ADHD_Q2h'=>null, 'ADHD_Q2i'=>null, 'ADHD_Q2j'=>null, 'ADHD_Q2k1'=>null, 'ADHD_Q2k2'=>null, 'ADHD_Q2k3'=>null, 'ADHD_Q2l'=>null, 'ADHD_Q3a_Treatment1'=>null, 'ADHD_Q3a_Treatment2'=>null,'ADHD_Q3a_Treatment3'=>null,'ADHD_Q3a_Treatment4'=>null,'ADHD_Q3a_Treatment5'=>null,'ADHD_Q3a_Treatment6'=>null, 'ADHD_Q3aDescription'=>null, 'ADHD_Q3b_OnsetAge'=>null, 'ADHD_Q3bNA'=>null, 'ADHD_Q3e_Current'=>null, 'ADHD_Q3f_Impairment'=>null, 'ADHD_Q3g_Reliability'=>null));
        }
        
        // do not alter this when overwriting the method
        unset($values['candID'], $values['sessionID'], $values['commentID'], $values['test_name'], $values['page'], $values['fire_away'], $values['subtest']);

        // if we're saving the relatives page, do magic
        if(empty($this->relativeID)) {
            $db =& Database::singleton();
            
            // This used to be written this way, but that caused information to get thrown away when
            // called from the conflict resolver where only a subset of these might be set.
            // Added the addSetArrayElement function to check if it's actually set in $values
            // before adding it to the setArray
            //$setArray = array('Date_taken'=>$values['Date_taken'], 'Examiner'=>$values['Examiner'], 'Informant'=>$values['Informant'], 'Informant_other'=>$values['Informant_other'], 'Candidate_Age' => $values['Candidate_Age'], 'Window_Difference' => $values['Window_Difference']);
            $setArray = array();
            $setArray = $this->_addSetArrayElement('Date_taken', $setArray, $values);
            $setArray = $this->_addSetArrayElement('Examiner', $setArray, $values);
            $setArray = $this->_addSetArrayElement('Informant', $setArray, $values);
            $setArray = $this->_addSetArrayElement('Informant_other', $setArray, $values);
            $setArray = $this->_addSetArrayElement('Candidate_Age', $setArray, $values);
            $setArray = $this->_addSetArrayElement('Window_Difference', $setArray, $values);
            $setArray = $this->_addSetArrayElement('other_comments', $setArray, $values);
            $whereArray = array('CommentID'=>$this->getCommentID());
            $ok = $db->update('figs_year3', $setArray, $whereArray);
            
            // if we're deleting, then delete...
            if(!empty($values['removeRelativeID'])) {
                // delete from figs_year3_relatives...
                $ok = $db->delete('figs_year3_relatives', array_merge($whereArray, array('RelativeID'=>$values['removeRelativeID'])));
            }
            
            // if we're adding, then add...
            if(!empty($values['addRelativeCode'])) {
                // insert into figs_year3_relatives...
                $ok = $db->insert('figs_year3_relatives', array_merge($whereArray, array('RelativeCode'=>$values['addRelativeCode'])));
            }
        } else {
            $ok = $this->_save($values);
        }
        if(!empty($this->relativeID)) $this->_setDataEntryCompletedRelative($this->relativeID);
        // $this->_setDataEntryCompleted();
        $this->setup($this->getCommentID(), null);
    }
    
    // Guard against empty value in $SubmittedValues, in case
    // save is called from the conflict resolver
    function _addSetArrayElement($Element, &$SetArray, &$SubmittedValues) {
        if(isset($SubmittedValues[$Element])) {
            $SetArray[$Element] = $SubmittedValues[$Element];
        }
        return $SetArray;
    }
    /**
    * uses the array generated by _saveValues() and runs the
    * Database::update() call.
    *
    * @param array $values       the array generated by _saveValues()
    * @return void
    * @access private
    */
    function _save($values)
    {
        // clear any fields starting with __
        foreach(array_keys($values) AS $key) {
            if(strpos($key, '__') === 0) {
                unset($values[$key]);
            }
        }
        
        $whereArray = array('CommentID'=>$this->getCommentID());
        if(!empty($this->relativeID)) $whereArray = array_merge($whereArray, array('RelativeID'=>$this->relativeID));
        $result = $GLOBALS['DB']->update($this->table, $values, $whereArray);
    }

    /**
    * freezes the current form
    *
    * @return void
    * @access public
    */
    function freeze()
    {
        // if it's a quickform, freeze it
        $this->form->freeze();
        
        // if it's the registerRelatives page, do a custom freeze
    }

    function _setupFigsRelatives() // Register Relative
    {
        $relationOptions = array(null=>'', 'Mother' => 'Mother', 'Father' => 'Father', 'Other'=>'Other');

        // Add examiner & date of administration
        $this->_addMetadataFields();
        
        // Add Informant field
        //$this->form->addElement('header', null, "Add Informant Relationship:");
        $this->form->addElement('select', "Informant", "Informant Relationship", $relationOptions);
        $this->form->addElement('text', "Informant_other", "Other");

        // Display the registration forms
        // Overwrite display and save methods
        
        $this->form->addElement('header', 'instrument_title', "Add/Remove Relatives");
        $relatives = $this->_getRelatives();

        // add relative button
        $this->localDefaults = array_merge($this->localDefaults, array('codeDescriptionNote'=> 'Note that the codes to be used below<BR> are the codes listed on page 2 of FIGS<BR>and describe relationship to the child of interest.<br>'));
        $this->form->addElement('static', 'codeDescriptionNote');
        $this->form->addElement('text', 'addRelativeCode', 'Add new relative coded', array('size'=>5, 'maxlength'=>5));
        $this->form->applyFilter('addRelativeCode', 'strtoupper');
        $this->form->addRule('addRelativeCode', 'The relative code entered is not a valid FIGS relationship code', 'regex', $this->_relationshipCodeRegex);

        if(is_array($relatives) && count($relatives)) {
            $usedRelativesRegex = '/^(?!'.join('|', array_values($relatives)).')/';
            $this->form->addRule('addRelativeCode', 'The relative code entered is already used', 'regex', $usedRelativesRegex);
            $this->form->addElement('select', 'removeRelativeID', 'Remove relative coded', array(null=>'&nbsp;') + $relatives);
        }
        
        // listing of existing relatives
        $candID = isset($_REQUEST['candID']) ? $_REQUEST['candID'] : '';
        $sessionID = isset($_REQUEST['sessionID']) ? $_REQUEST['sessionID'] : '';
        $this->form->addElement('header', null, 'View checklists');
        $url = "main.php?test_name=figs_year3&candID=$candID&sessionID=$sessionID&commentID=".$this->getCommentID();
        if(is_array($relatives)) {
            foreach($relatives AS $relativeID=>$relativeCode) {
                $this->form->addElement('link', null, $relativeCode, "$url&relativeID=$relativeID&checklist=checklists", 'open');
            }
        }

        // List of opened checklist where data entry has not been completed
        $this->form->addElement('header', null, 'Relatives for which opened checklist have incomplete data entry:');
        $this->form->addElement("static", 'incompleteRelatives', "Relatives: ");
        
        $db =& Database::singleton();

        $query = "SELECT RelativeCode from figs_year3_relatives WHERE CommentID='".$this->getCommentID()."' AND DataEntryCompleted=0";

        $db->select($query, $incompleteRelatives);
        foreach($incompleteRelatives AS $incompleteRelative) {
            if(!isset($this->localDefaults['incompleteRelatives'])) {
                $this->localDefaults['incompleteRelatives'] = '';
            }
            if(!empty($this->localDefaults['incompleteRelatives'])) {
                $this->localDefaults['incompleteRelatives'] .= ', ';        
            }
            $this->localDefaults['incompleteRelatives'] .= $incompleteRelative['RelativeCode'];
        }

        /*
        * listing per-instrument scores
        */
        $this->form->addElement('header', null, 'Scores/ Diagnostics');
        $this->form->addElement("static", "ADHD", "ADHD: ");
        $this->form->addElement("static", "Alcohol", "Alcohol Abuse and/or Dependence: ");
        $this->form->addElement("static", "ASP", "ASP: ");
        $this->form->addElement("static", "Depression", "Depression [MDD, RDD]: ");
        $this->form->addElement("static", "Drug_substance", "Drug/Substance Abuse: ");
        $this->form->addElement("static", "Mania", "Mania: ");
        $this->form->addElement("static", "Nicotine", "Nicotine: ");
        $this->form->addElement("static", "OCD", "OCD: ");
        $this->form->addElement("static", "Paranoid", "Paranoid, Schizoid, Schizotypal: ");
        $this->form->addElement("static", "Psychosis", "Psychosis: ");
        $this->form->addElement("static", "Tic", "Tic: ");

        // Rule for informant field
        $this->form->addRule("Informant", "Required", 'required', null);
        $this->form->addRule(array('Informant_other', 'Informant'), 'Other is required if available', 'requiredIf', array('operator'=>'==', 'value'=>'Other'));
        $this->setRequired('Informant_other');
        $this->form->addElement('static',null,'<br>');
        $this->form->addElement("textarea", "other_comments", "Comments :", array('cols'=>25, 'rows'=>4));
        $this->XINRegisterRule("other_comments", array("{other_comments}{@}=={@}NEVER_REQUIRED"));


    } // End function
    
    function _setupFigsRelativesChecklist() // Checklist
    {
        // Display test name
        $this->form->addElement('header', 'instrument_title', "Checklists");

        $checklistOptions = array('N'=>'N', 'Y'=>'Y');

        // List of Checklists that are used
        $this->form->addElement('select', "Checklist_Other", "Other Disorders", $checklistOptions);
        $this->form->addElement('select', "Checklist_Depression", "Depression", $checklistOptions);
        $this->form->addElement('select', "Checklist_Mania", "Mania", $checklistOptions);
        $this->form->addElement('select', "Checklist_Psychosis", "Psychosis", $checklistOptions);
        $this->form->addElement('select', "Checklist_Alcohol", "Alcohol", $checklistOptions);
        $this->form->addElement('select', "Checklist_Drugs", "Drugs", $checklistOptions);
        $this->form->addElement('select', "Checklist_Nicotine", "Nicotine", $checklistOptions);
        $this->form->addElement('select', "Checklist_Schizoid", "Paranoid, Schizoid, Schizotypal", $checklistOptions);
        $this->form->addElement('select', "Checklist_ASP", "ASP", $checklistOptions);
        $this->form->addElement('select', "Checklist_Tic", "Tic Disorder", $checklistOptions);
        $this->form->addElement('select', "Checklist_OCD", "OCD", $checklistOptions);
        $this->form->addElement('select', "Checklist_ADHD", "ADHD", $checklistOptions);

        // Create a submit button using my own save method.
        // Create links if they have been marked as yes
        $this->form->addElement('header', null, 'Access checklists');
        $url = "main.php?test_name=figs_year3&candID=".$_REQUEST['candID']."&sessionID=".$_REQUEST['sessionID']."&commentID=".$this->getCommentID();

        $db =& Database::singleton();
        $query = "SELECT Checklist_Other, Checklist_Depression, Checklist_Mania, Checklist_Psychosis, Checklist_Alcohol, Checklist_Drugs, Checklist_Nicotine, Checklist_Schizoid, Checklist_ASP, Checklist_Tic, Checklist_OCD, Checklist_ADHD FROM figs_year3_relatives WHERE RelativeID='$this->relativeID'";
        $ok = $db->selectRow($query, $states);

        $this->form->addElement('link', null, 'Face Sheet', "$url&relativeID=$this->relativeID&checklist=face", 'open');
        $this->form->addElement('link', null, 'General Screening', "$url&relativeID=$this->relativeID&checklist=screening", 'open');

        if($states['Checklist_Other'] == 'Y')
        $this->form->addElement('link', null, 'Other Disorders', "$url&relativeID=$this->relativeID&checklist=other", 'open');

        if($states['Checklist_Depression'] == 'Y')
        $this->form->addElement('link', null, 'Depression', "$url&relativeID=$this->relativeID&checklist=depression", 'open');

        if($states['Checklist_Mania'] == 'Y')
        $this->form->addElement('link', null, 'Mania', "$url&relativeID=$this->relativeID&checklist=mania", 'open');

        if($states['Checklist_Psychosis'] == 'Y')
        $this->form->addElement('link', null, 'Psychosis', "$url&relativeID=$this->relativeID&checklist=psychosis", 'open');

        if($states['Checklist_Alcohol'] == 'Y')
        $this->form->addElement('link', null, 'Alcohol', "$url&relativeID=$this->relativeID&checklist=alcohol", 'open');

        if($states['Checklist_Drugs'] == 'Y')
            $this->form->addElement('link', null, 'Drugs', "$url&relativeID=$this->relativeID&checklist=drugs", 'open'); // checklist = where does this get used?

        if($states['Checklist_Nicotine'] == 'Y')
        $this->form->addElement('link', null, 'Nicotine', "$url&relativeID=$this->relativeID&checklist=nicotine", 'open');

        if($states['Checklist_Schizoid'] == 'Y')
        $this->form->addElement('link', null, 'Paranoid, Schizoid, Schizotypal', "$url&relativeID=$this->relativeID&checklist=schizoid", 'open');

        if($states['Checklist_ASP'] == 'Y')
        $this->form->addElement('link', null, 'ASP', "$url&relativeID=$this->relativeID&checklist=asp", 'open');

        if($states['Checklist_Tic'] == 'Y')
        $this->form->addElement('link', null, 'Tic Disorder', "$url&relativeID=$this->relativeID&checklist=tic", 'open');

        if($states['Checklist_OCD'] == 'Y')
        $this->form->addElement('link', null, 'OCD', "$url&relativeID=$this->relativeID&checklist=ocd", 'open');

        if($states['Checklist_ADHD'] == 'Y')
        $this->form->addElement('link', null, 'ADHD', "$url&relativeID=$this->relativeID&checklist=adhd", 'open');

        /*
        * listing the scores for a relative
        */
        $this->form->addElement('header', null, 'Scores/ Diagnostics');
        $this->form->addElement("static", "Score_adhd_combined", "ADHD Combined: ");
        $this->form->addElement("static", "Score_adhd_inattentive", "ADHD Inattentive: ");
        $this->form->addElement("static", "Score_adhd_hyperactive", "ADHD Hyperactive: ");
        $this->form->addElement("static", "Score_alcohol_abuse", "Alcohol Abuse: ");
        $this->form->addElement("static", "Score_alcohol_dependence", "Alcohol Dependence: ");
        $this->form->addElement("static", "Score_alcohol_nicotine", "Nicotine: ");
        $this->form->addElement("static", "Score_alcohol_drug_substance", "Drug/Substance Abuse: ");
        $this->form->addElement("static", "Score_asp", "Antisocial: ");
        $this->form->addElement("static", "Score_depression", "MDD: ");
        $this->form->addElement("static", "Score_recurrent_depression", "RDD: ");
        $this->form->addElement("static", "Score_chronic_depression", "Chronic Depression: ");
        $this->form->addElement("static", "Score_mania", "Mania: ");
        $this->form->addElement("static", "Score_ocd", "OCD: ");
        $this->form->addElement("static", "Score_paranoid_personality", "PPD: ");
        $this->form->addElement("static", "Score_pervasive_development", "PDD: ");
        $this->form->addElement("static", "Score_schizoid", "Schizoid: ");
        $this->form->addElement("static", "Score_schizotypal", "Schizotypal: ");
        $this->form->addElement("static", "Score_psychosis_schizophrenia", "Schizophrenia: ");
        $this->form->addElement("static", "Score_psychosis_depression", "Psychosis - Depression: ");
        $this->form->addElement("static", "Score_psychosis_mania", "Psychosis - Mania: ");
        $this->form->addElement("static", "Score_tic_tourettes", "Tic - Tourettes: ");
        $this->form->addElement("static", "Score_tic_motor_c", "Tic - Motor C: ");
        $this->form->addElement("static", "Score_tic_motor_t", "Tic - Motor T: ");
        $this->form->addElement("static", "Score_tic_vocal_c", "Tic - Vocal C: ");
        $this->form->addElement("static", "Score_tic_vocal_t", "Tic - Vocal T: ");
    }
    
    function _setupFigsRelativesFaceSheet() // Face Sheet Questions
    {
        
        $questionOptions = array(null=>'', '0' => '0. No', '1' => '1. Yes', '9'=>'9. Unk', 'NA' => 'N/A');
        $question1f_Options = array(null=>'', '1' => '1. Good', '2'=>'2. Fair', '3'=>'3. Poor', 'NA' => 'N/A');
        $question1_1a_Options = array(null=>'','0'=>'0.No','1'=>'1.Yes','9'=>'9.Unknown','NA'=>'N/A');
        $question1_1b_Options = array(null=>'','1'=>'1.Full mutation','2'=>'2.Pre-mutation','3'=>'3.Carrier','4'=>'4.Fragile X-associated Tremor/Ataxia syndrome','5'=>'5.Fragile X-associated Primary Ovarian Insufficiency','6'=>'6. Other','7'=>'7.Not Applicable','8'=>'8.Not Answered','9'=>'9.Unknown','10'=>'10.Negative');
        $config = & NDB_Config::singleton();
        $dateOptions =  array(
        'language' => 'en',
        'format'   => 'YMd',
        'minYear'  => 1900,
        'maxYear'  => $config->getSetting('endYear'),
        'addEmptyOption' => true,
        'emptyOptionValue' => null
        );
        
        // Metadata
        $this->form->addElement('header', null, "Face Sheet");
        $this->form->addElement('static', "Informant", "i. Informant Relationship");
        $this->form->addElement('static', "RelativeCode", "ii. Person being described relationship code");
        $this->form->addElement('date', "Face_BirthDate", "iii. Birth date of person described, if known:", $dateOptions); // Figure this out (date issue)
        $this->form->addElement('advcheckbox', 'Face_BirthDateEstimated', 'Birth date above is estimated');
        
        // Face sheet questions
        $this->form->addElement("select","Face_Living","Is person being described living?", $questionOptions);
        $this->form->addElement('text', "Face_LastSeenAge", "Age when last seen or known about, or died: (in years - numbers only!)");
        $this->form->addElement('text', "Face_LastSeenYear", "Year when last seen or known about, or died: (numbers only!)");
        $this->form->addElement('advcheckbox', "Face_LastSeenNA", "NA");
        $this->form->addElement('text', "Face_CauseOfDeath", "If deceased, cause of death:");
        $this->form->addElement('select', "Face_Suicide", "Suicide?", $questionOptions);
        $this->form->addElement('select', "Face_OtherProblems", "1. Has he/she had any other psychiatric or personality problems other than/or like those we mentioned earlier? ", $questionOptions);
        $this->form->addElement('select',"Face_fragilex_syndrome","1.1a) Has he/she ever been tested for FRAGILE X SYNDROME?",$question1_1a_Options); 
        $this->form->addElement('select',"Face_outcome_test","1.1b) What was the outcome of the test?",$question1_1b_Options);
        $this->form->addElement('text', "Face_testoutcome_other", "Specify other outcome:");
        $this->form->addElement('select', "Face_Reliability", "1.f) Interviewer judgment on reliability of this information:", $question1f_Options);
        $this->form->addElement('text', "Face_Comments", "Comments:");
        
        // Rules for questions
        $this->form->addRule("Face_Living", "Required", 'required', null);
        $this->form->addRule(array('Face_LastSeenAge', 'Face_LastSeenNA'), 'Age last seen is required if available', 'requiredIf', array('operator'=>'!=', 'value'=>'1'));
        $this->form->addRule(array('Face_LastSeenYear', 'Face_LastSeenNA'), 'Year last seen is required if available', 'requiredIf', array('operator'=>'!=', 'value'=>'1'));
        $this->setRequired('Face_LastSeenAge');
        $this->setRequired('Face_LastSeenYear');

        $this->form->addRule(array('Face_CauseOfDeath', 'Face_Living'), 'Cause of Death is required if person is deceased', 'requiredIf', array('operator'=>'==', 'value'=>'0'));
        $this->setRequired('Face_CauseOfDeath');

        $this->form->addRule(array('Face_Suicide', 'Face_Living'), 'Suicide is required if person is deceased', 'requiredIf', array('operator'=>'==', 'value'=>'0'));
        $this->setRequired('Face_Suicide');
        
        $this->form->addRule("Face_OtherProblems", "Required", 'required', null);
        $this->form->addRule("Face_Reliability", "Required", 'required', null);
        $this->form->addRule("Face_fragilex_syndrome", "Required", 'required', null);
        $this->setRequired('Face_fragilex_syndrome');
        $this->form->addRule(array('Face_outcome_test','Face_fragilex_syndrome'),'Specify outcome if Fragile X test was conducted','requiredIf',array('operator'=>'==','value'=>'1'));
        $this->setRequired('Face_outcome_test');

        $this->form->addRule(array('Face_testoutcome_other','Face_outcome_test'),'Specify outcome of Fragile X test if option not in dropdown','requiredIf',array('operator'=>'==','value'=>'6'));
        $this->setRequired('Face_testoutcome_other');
    }
    
    function _setupFigsRelativesOtherDisorders() // Other Disorders
    {
        // Display test name
        $this->form->addElement('header', null, "Other Disorders");
        
        // Create option set for the questions
        $treatment_Option1_Q1a = array(null=>'', '0' => '0. None', 'NA' => 'N/A');
        $treatment_Option2_Q1a = array(null=>'', '1' => '1. Inpatient', 'NA' => 'N/A');
        $treatment_Option3_Q1a = array(null=>'', '2' => '2. Outpatient', 'NA' => 'N/A');
        $treatment_Option4_Q1a = array(null=>'', '3' => '3. ECT', 'NA' => 'N/A');
        $treatment_Option5_Q1a = array(null=>'', '4' => '4. Medication', 'NA' => 'N/A');
        $treatment_Option6_Q1a = array(null=>'', '9' => '9. Unknown', 'NA' => 'N/A');
        $question1f_Options = array(null=>'', '0' => '0. None', '1' => '1. Impaired', '2'=>'2. Incapacitated', '3'=>'3. Clinically Significant Distress', '4'=>'4. Change from previous functioning', '9'=>'9. Unknown', 'NA' => 'N/A');
        $this->form->addElement("textarea", "Other_Narrative", "Write narrative:");
        
        for($i = 1; $i <= 5; $i++) {
            // Disorder 2-5 was added after the fact, so instead of "Other1" it needs to stay "Other".. add
            // an extra variable
            if($i == 1) {
                $DisorderNum = "";
            } else {
                $DisorderNum = $i;
            }
            // Questions
            $this->form->addElement('header', null, "Disorder Number $i");
            $this->form->addElement("text", "Other{$DisorderNum}_Q1_Disorder", "1. Indicate any disorder NOT in the checklists and complete questions 1.a-f for the disorder (includes neurologic disorders).");
            $this->form->addElement("static", null, "1.a) Code and describe professional treatment:");
            
            $this->form->addElement("select", "Other{$DisorderNum}_Q1a_Treatment1", "0. ", $treatment_Option1_Q1a);
            $this->form->addElement("select", "Other{$DisorderNum}_Q1a_Treatment2", "1. ", $treatment_Option2_Q1a);
            $this->form->addElement("select", "Other{$DisorderNum}_Q1a_Treatment3", "2. ", $treatment_Option3_Q1a);
            $this->form->addElement("select", "Other{$DisorderNum}_Q1a_Treatment4", "3. ", $treatment_Option4_Q1a);
            $this->form->addElement("select", "Other{$DisorderNum}_Q1a_Treatment5", "4. ", $treatment_Option5_Q1a);
            $this->form->addElement("select", "Other{$DisorderNum}_Q1a_Treatment6", "9. ", $treatment_Option6_Q1a);
            $this->form->addElement("textarea","Other{$DisorderNum}_Q1a_Description", "Please describe treatments:");

            $this->form->addElement("text","Other{$DisorderNum}_Q1b_OnsetAge","1.b) Age of onset (in years - numbers only!)");
            $this->form->addElement("advcheckbox","Other{$DisorderNum}_Q1bNA","NA");
            $this->form->addElement("text","Other{$DisorderNum}_Q1c_Episodes","1.c) Number of episodes (numbers only!)");
            $this->form->addElement("advcheckbox","Other{$DisorderNum}_Q1cNA","NA");
            $this->form->addElement("text","Other{$DisorderNum}_Q1d_Duration","1.d) Duration of longest episode in weeks (numbers only!)");
            $this->form->addElement("advcheckbox","Other{$DisorderNum}_Q1dNA","NA");
            $this->form->addElement("select","Other{$DisorderNum}_Q1e_Impairment","1.e) Rate and code impairment or incapacitation:", $question1f_Options);
            
            // Rules for disorder 1.. other disorders aren't required.
            if($i == 1) {
                $this->form->addRule("Other{$DisorderNum}_Q1_Disorder", "Required", 'required', null);
              
                $this->form->addRule("Other{$DisorderNum}_Q1a_Treatment1", "Required", 'required', null);
                $this->form->addRule("Other{$DisorderNum}_Q1a_Treatment2", "Required", 'required', null);
                $this->form->addRule("Other{$DisorderNum}_Q1a_Treatment3", "Required", 'required', null);
                $this->form->addRule("Other{$DisorderNum}_Q1a_Treatment4", "Required", 'required', null);
                $this->form->addRule("Other{$DisorderNum}_Q1a_Treatment5", "Required", 'required', null);
                $this->form->addRule("Other{$DisorderNum}_Q1a_Treatment6", "Required", 'required', null);

                $this->form->addRule(array("Other{$DisorderNum}_Q1b_OnsetAge", "Other{$DisorderNum}_Q1bNA"), 'Age of onset is required if available', 'requiredIf', array('operator'=>'!=', 'value'=>'1'));
                $this->setRequired("Other{$DisorderNum}_Q1b_OnsetAge");
                $this->form->addRule(array("Other{$DisorderNum}_Q1c_Episodes", "Other{$DisorderNum}_Q1cNA"), 'Number of episodes is required if available', 'requiredIf', array('operator'=>'!=', 'value'=>'1'));
                $this->setRequired("Other{$DisorderNum}_Q1c_Episodes");
                $this->form->addRule(array("Other{$DisorderNum}_Q1d_Duration", "Other{$DisorderNum}_Q1dNA"), 'Duration of longest episode is required if available', 'requiredIf', array('operator'=>'!=', 'value'=>'1'));
                $this->setRequired("Other{$DisorderNum}_Q1d_Duration");
                $this->form->addRule("Other{$DisorderNum}_Q1e_Impairment", "Required", 'required', null);
            }
        }
        $this->form->addFormRule(array(&$this,'OtherDisorderRules'));
    } // End function
    
    // Rules for disorder 2-5, which are more complicated because they depend on both a criteria and on the Q1_Disorder
    // being specified
    function OtherDisorderRules($values) {
        $errors = array();
        for($i = 2; $i <= 5; $i++) {
            if($values["Other{$i}_Q1_Disorder"] != '') {
                if($values["Other{$i}_Q1a_Treatment1"] == '') { $errors["Other{$i}_Q1a_Treatment1"] = 'Required'; }
                if($values["Other{$i}_Q1a_Treatment2"] == '') { $errors["Other{$i}_Q1a_Treatment2"] = 'Required'; }
                if($values["Other{$i}_Q1a_Treatment3"] == '') { $errors["Other{$i}_Q1a_Treatment3"] = 'Required'; }
                if($values["Other{$i}_Q1a_Treatment4"] == '') { $errors["Other{$i}_Q1a_Treatment4"] = 'Required'; }
                if($values["Other{$i}_Q1a_Treatment5"] == '') { $errors["Other{$i}_Q1a_Treatment5"] = 'Required'; }
                if($values["Other{$i}_Q1a_Treatment6"] == '') { $errors["Other{$i}_Q1a_Treatment6"] = 'Required'; }

                // Options with an N/A checkbox
                if($values["Other{$i}_Q1bNA"] != 1 && $values["Other{$i}_Q1b_OnsetAge"] == '') { $errors["Other{$i}_Q1b_OnsetAge"] = "Age of onset is required if available"; }
                if($values["Other{$i}_Q1cNA"] != 1 && $values["Other{$i}_Q1c_Episodes"] == '') { $errors["Other{$i}_Q1c_Episodes"] = "Number of episodes is required if available"; }
                if($values["Other{$i}_Q1dNA"] != 1 && $values["Other{$i}_Q1d_Duration"] == '') { $errors["Other{$i}_Q1d_Duration"] = "Duration of longest episode is required if available"; }
                if($values["Other{$i}_Q1e_Impairment"] == '') { $errors["Other{$i}_Q1e_Impairment"] = 'Required'; }

            }
        }
        return $errors;
    }
    function _setupFigsRelativesGeneralScreening() // General Screening Questions
    {
        // Display test name
        $this->form->addElement('header', null, "General Screening");
        
        // Create option set for the questions
        $questionOptions = array(null=>'', 'Y' => 'Yes', 'N' => 'No', 'NA' => 'N/A');
        
        // Questions
        $this->form->addElement("static", null, "Step 1: Let's go over your family tree.");
        $this->form->addElement("static", null, "Step 2: Now I am asking you to keep in mind the family members we just discussed including youself as I go through the list of questions.");
        $this->form->addElement("select", "GS_Q01_Adopted", "1. Was anyone adopted?", $questionOptions);
        $this->form->addElement("select", "GS_Q02_MentallyRetarded", "2. Was anyone mentally retarted?", $questionOptions);
        $this->form->addElement("select", "GS_Q03_Inattentive", "3. Did anyone have trouble finishing school work or being inattentive", $questionOptions);
        $this->form->addElement("select", "GS_Q04_TroubleSitting", "4. Did anyone have trouble sitting in their seat or taking turns in school?", $questionOptions);
        $this->form->addElement("select", "GS_Q05_DiagnosedADHD", "5. Did anyone have a diagnosis of attention deficit disorder or attention deficit/hyperactivity disorder?", $questionOptions);
        $this->form->addElement("select", "GS_Q06_Nerves", "6. Did anyone have problems with their nerves or emotions?  Take medicine or see a doctor for it?  Take lithium?", $questionOptions);
        $this->form->addElement("select", "GS_Q07_DiagnosedDepression", "7. Did anyone feel very low for a couple of weeks or more, or have a diagnosis of depression?", $questionOptions);
        $this->form->addElement("select", "GS_Q08_Suicide", "8. Did anyone attempt or complete suicide?", $questionOptions);
        $this->form->addElement("select", "GS_Q09_DiagnosedMania", "9. Did anyone seem overexcited (or manic) day and night, or have a diagnosis of mania?", $questionOptions);
        $this->form->addElement("select", "GS_Q10_Visions", "10. Did anyone have visions, hear voices, or have beliefs that seem strange or unreal?", $questionOptions);
        $this->form->addElement("select", "GS_Q11_DiagnosedSchizophrenia", "11. Did anyone have unusual or bizarre behavior, or have a diagnosis of schizophrenia?", $questionOptions);
        $this->form->addElement("select", "GS_Q12_Obsessions", "12. Did anyone have repetitive thoughts or get stuck on ideas (obsessions)? Have rituals or do the same thing over and over (compulsions)?", $questionOptions);
        $this->form->addElement("select", "GS_Q13_DiagnosedOCD", "13. Did anyone have a diagnosis of obsessive/compulsive disorder?", $questionOptions);
        $this->form->addElement("select", "GS_Q14_Violent", "14. Did anyone have trouble with the police, with completing school due to irresponsible behavior, or with keeping a job? Did anyone have trouble with a violent temper or abusive behavior?", $questionOptions);
        $this->form->addElement("select", "GS_Q15_AlcoholDrug", "15. Did anyone have alcohol or drug use that caused problems (with health, family, job, or police)?  Did anyone go to AA or NA, or have treatment for this?", $questionOptions);
        $this->form->addElement("select", "GS_Q16_Nicotine", "16. Did anyone smoke cigarettes, cigars, chew tobacco or use any other forms of nicotine?", $questionOptions);
        $this->form->addElement("select", "GS_Q17_Psychiatric", "17. Was anyone hospitalized for psychiatric problems, or for drug or alcohol problems?", $questionOptions);
        $this->form->addElement("select", "GS_Q18_Neurologic", "18. Did anyone have inherited medical diseases such as Huntington's disease? Did anyone have neurological illnesses such as seizure disorder or any other disorders of the brain or nervous system?", $questionOptions);
        $this->form->addElement("select", "GS_Q19_Tourrettes", "19. Did anyone have tics or Tourrette's Syndrome?", $questionOptions);
        $this->form->addElement("select", "GS_Q20_Loner", "20. Did anyone have few friends, or seem to be a loner?", $questionOptions);
        $this->form->addElement("select", "GS_Q21_Speech", "21. Did anyone have odd or unusual speech or was slow to develop speech?", $questionOptions);
        $this->form->addElement("select", "GS_Q22_Eccentric", "22. Did anyone seem odd or eccentric in behavior or appearance?", $questionOptions);
        $this->form->addElement("select", "GS_Q23_Autism", "23. Did anyone have autism, Asperger's Syndrome or pervasive developmental disorder (PDD)?", $questionOptions);
        $this->form->addElement("select", "GS_Q24_Jealous", "24. Was anyone extremely jealous, suspicious, believe in magic or see special meanings in things that no one else saw?", $questionOptions);
        $this->form->addElement("static", null, "Step 3: Complete checklists as indicated by General Screening Questions.");
        
        // Rules for General Questions
        $this->form->addRule("GS_Q01_Adopted", "Required", 'required', null);
        $this->form->addRule("GS_Q02_MentallyRetarded", "Required", 'required', null);
        $this->form->addRule("GS_Q03_Inattentive", "Required", 'required', null);
        $this->form->addRule("GS_Q04_TroubleSitting", "Required", 'required', null);
        $this->form->addRule("GS_Q05_DiagnosedADHD", "Required", 'required', null);
        $this->form->addRule("GS_Q06_Nerves", "Required", 'required', null);
        $this->form->addRule("GS_Q07_DiagnosedDepression", "Required", 'required', null);
        $this->form->addRule("GS_Q08_Suicide", "Required", 'required', null);
        $this->form->addRule("GS_Q09_DiagnosedMania", "Required", 'required', null);
        $this->form->addRule("GS_Q10_Visions", "Required", 'required', null);
        $this->form->addRule("GS_Q11_DiagnosedSchizophrenia", "Required", 'required', null);
        $this->form->addRule("GS_Q12_Obsessions", "Required", 'required', null);
        $this->form->addRule("GS_Q13_DiagnosedOCD", "Required", 'required', null);
        $this->form->addRule("GS_Q14_Violent", "Required", 'required', null);
        $this->form->addRule("GS_Q15_AlcoholDrug", "Required", 'required', null);
        $this->form->addRule("GS_Q16_Nicotine", "Required", 'required', null);
        $this->form->addRule("GS_Q17_Psychiatric", "Required", 'required', null);
        $this->form->addRule("GS_Q18_Neurologic", "Required", 'required', null);
        $this->form->addRule("GS_Q19_Tourrettes", "Required", 'required', null);
        $this->form->addRule("GS_Q20_Loner", "Required", 'required', null);
        $this->form->addRule("GS_Q21_Speech", "Required", 'required', null);
        $this->form->addRule("GS_Q22_Eccentric", "Required", 'required', null);
        $this->form->addRule("GS_Q23_Autism", "Required", 'required', null);
        $this->form->addRule("GS_Q24_Jealous", "Required", 'required', null);
        
    } // End funtion
    
    function _setupFigsRelativesDepression()  // Depression Checklist
    {
        // Display test name
        $this->form->addElement('header', null, "Depression Checklist");
        
        // Create option set for the questions
        $question_Options = array(null=>'', '0' => '0. No', '1' => '1. Yes', '9'=>'9. Unk', 'NA' => 'N/A');
        $treatment_Option1_Q2 = array(null=>'', '0' => '0. None', 'NA' => 'N/A');
        $treatment_Option2_Q2 = array(null=>'', '1' => '1. Inpatient', 'NA' => 'N/A');
        $treatment_Option3_Q2 = array(null=>'', '2' => '2. Outpatient', 'NA' => 'N/A');
        $treatment_Option4_Q2 = array(null=>'', '3' => '3. ECT', 'NA' => 'N/A');
        $treatment_Option5_Q2 = array(null=>'', '4' => '4. Medication', 'NA' => 'N/A');
        $treatment_Option6_Q2 = array(null=>'', '9' => '9. Unknown', 'NA' => 'N/A');
        $question6_Options = array(null=>'', 'Yes' => 'Yes', 'No' => 'No', 'Unsure'=>'Unsure', 'NA' => 'N/A');
        $question8_Options = array(null=>'', '0' => '0. None', '1' => '1. Impaired', '2'=>'2. Incapacitated', '3'=>'3. Clinically Significant Distress', '4'=>'4. Change from previous functioning', '9'=>'9. Unknown', 'NA' => 'N/A');
        $question9_Options = array(null=>'', '1' => '1. Good', '2'=>'2. Fair', '3'=>'3. Poor', 'NA' => 'N/A');
        
        // Depression Checklist
        $this->form->addElement("static", null, "1. During depression...");
        $this->form->addElement("select", "Depression_Q1a", "1.a) ...was he/she depressed (sad, down, or in a bad mood) most of the day, nearly every day, for as long as a week or more?", $question_Options);
        $this->form->addElement("select", "Depression_Q1b", "1.b) ...did he/she lose interest in things or become unable to enjoy most things, for as long as a week?", $question_Options);
        $this->form->addElement("select", "Depression_Q1c", "1.c) ...did he/she have a change in appetite or weight without trying to?", $question_Options);
        $this->form->addElement("text", "Depression_Q1cDescription", "If yes, Describe:");
        $this->form->addElement("select", "Depression_Q1d", "1.d) ...did he/she have a change in sleep patterns (either too much or too little)?", $question_Options);
        $this->form->addElement("text", "Depression_Q1dDescription", "If yes, Describe:");
        $this->form->addElement("select", "Depression_Q1e", "1.e) ...did he/she become unable to work, go to school, or take care of household responsibilities?", $question_Options);
        $this->form->addElement("text", "Depression_Q1eDescription", "If yes, Describe:");
        $this->form->addElement("select", "Depression_Q1f", "1.f) During these episodes of depression/low mood (symptoms should be associated with periods of mood change) did he/she move or speak more slowly than usual?", $question_Options);
        $this->form->addElement("select", "Depression_Q1g", "1.g) During these episodes of depression/low mood (symptoms should be associated with periods of mood change) did he/she pace or wring his/her hands?", $question_Options);
        $this->form->addElement("select", "Depression_Q1h", "1.h) During these episodes of depression/low mood did he/she have less energy or feel tired out?", $question_Options);
        $this->form->addElement("select", "Depression_Q1i", "1.i) During these episodes of depression/low mood did he/she feel guilty, worthless, or blame himself/herself?", $question_Options);
        $this->form->addElement("select", "Depression_Q1j", "1.j) During these episodes of depression/low mood did he/she have trouble concentrating or making decisions?", $question_Options);
        $this->form->addElement("select", "Depression_Q1k", "1.k) During these episodes of depression/low mood (symptoms should be associated with periods of mood change) did he/she talk of death or suicide?  Or try suicide?", $question_Options);
        $this->form->addElement("select", "Depression_Q1l", "1.l) During these episodes of depression/low mood did he/she have visions, hear voices, or have beliefs or behavior that seemed strange or unusual, at the same time as (symptoms above)? ", $question_Options);
       
        $this->form->addElement("static", null, "2. Did _______ receive any professional treatment for these problems?");
        $this->form->addElement("select", "Depression_Q2_Treatment1", "0. ", $treatment_Option1_Q2);
        $this->form->addElement("select", "Depression_Q2_Treatment2", "1. ", $treatment_Option2_Q2);
        $this->form->addElement("select", "Depression_Q2_Treatment3", "2. ", $treatment_Option3_Q2);
        $this->form->addElement("select", "Depression_Q2_Treatment4", "3. ", $treatment_Option4_Q2);
        $this->form->addElement("select", "Depression_Q2_Treatment5", "4. ", $treatment_Option5_Q2);
        $this->form->addElement("select", "Depression_Q2_Treatment6", "9. ", $treatment_Option6_Q2);
        $this->form->addElement("textarea", "Depression_Q2Description", "Please describe treatments:");
        
        $this->form->addElement("text", "Depression_Q3_Age", "3. Age of onset (years - numbers only!)");
        $this->form->addElement("advcheckbox", "Depression_Q3NA", "NA");
        $this->form->addElement("text", "Depression_Q4_Episodes", "4. Number of episodes (numbers only!)");
        $this->form->addElement("advcheckbox", "Depression_Q4NA", "NA");
        $this->form->addElement("text", "Depression_Q5_Duration", "5. Duration of longest episode in weeks (numbers only!)");
        $this->form->addElement("advcheckbox", "Depression_Q5NA", "NA");
        $this->form->addElement("select", "Depression_Q6_Current", "6. Currently depressed?", $question6_Options);
        $this->form->addElement("text", "Depression_Q7_Recent", "7. Most recent episode (Number of months prior to current date.)");
        $this->form->addElement("advcheckbox", "Depression_Q7NA", "NA");
        $this->form->addElement("select", "Depression_Q8_Impairment", "8.Rate and code impairment or incapacitation:", $question8_Options);
        $this->form->addElement("select", "Depression_Q9_Reliability", "9. Interviewer judgment on reliability of this information:", $question9_Options);
        
        // Rules for questions
        $this->form->addRule("Depression_Q1a", "Required", 'required', null);
        $this->form->addRule("Depression_Q1b", "Required", 'required', null);
        $this->form->addRule("Depression_Q1c", "Required", 'required', null);
        $this->form->addRule("Depression_Q1d", "Required", 'required', null);
        $this->form->addRule("Depression_Q1e", "Required", 'required', null);
        $this->form->addRule("Depression_Q1f", "Required", 'required', null);
        $this->form->addRule("Depression_Q1g", "Required", 'required', null);
        $this->form->addRule("Depression_Q1h", "Required", 'required', null);
        $this->form->addRule("Depression_Q1i", "Required", 'required', null);
        $this->form->addRule("Depression_Q1j", "Required", 'required', null);
        $this->form->addRule("Depression_Q1k", "Required", 'required', null);
        $this->form->addRule("Depression_Q1l", "Required", 'required', null);
        $this->form->addRule("Depression_Q2_Treatment1", "Required", 'required', null);
        $this->form->addRule("Depression_Q2_Treatment2", "Required", 'required', null);
        $this->form->addRule("Depression_Q2_Treatment3", "Required", 'required', null);
        $this->form->addRule("Depression_Q2_Treatment4", "Required", 'required', null);
        $this->form->addRule("Depression_Q2_Treatment5", "Required", 'required', null);
        $this->form->addRule("Depression_Q2_Treatment6", "Required", 'required', null);
        $this->form->addRule(array('Depression_Q3_Age', 'Depression_Q3NA'), 'Age of onset is required if available', 'requiredIf', array('operator'=>'!=', 'value'=>'1'));
        $this->setRequired('Depression_Q3_Age');
        $this->form->addRule(array('Depression_Q4_Episodes', 'Depression_Q4NA'), 'Number of Episodes is required if available', 'requiredIf', array('operator'=>'!=', 'value'=>'1'));
        $this->setRequired('Depression_Q4_Episodes');
        $this->form->addRule(array('Depression_Q5_Duration', 'Depression_Q5NA'), 'Duration of Episode is required if available', 'requiredIf', array('operator'=>'!=', 'value'=>'1'));
        $this->setRequired('Depression_Q5_Duration');
        $this->form->addRule("Depression_Q6_Current", "Required", 'required', null);
        $this->form->addRule(array('Depression_Q7_Recent', 'Depression_Q7NA'), 'Most Recent Episode is required if available', 'requiredIf', array('operator'=>'!=', 'value'=>'1'));
        $this->setRequired('Depression_Q7_Recent');
        $this->form->addRule("Depression_Q8_Impairment", "Required", 'required', null);
        $this->form->addRule("Depression_Q9_Reliability", "Required", 'required', null);
        
    } // End function
    
    function _setupFigsRelativesMania() // Mania Checklist
    {
        // Display test name
        $this->form->addElement('header', null, "Mania Checklist");
        
        // Create option set
        $questionOptions = array(null=>'', '0' => '0. No', '1' => '1. Yes', '9'=>'9. Unk', 'NA' => 'N/A');
        $treatment_Option1_Q2 = array(null=>'', '0' => '0. None', 'NA' => 'N/A');
        $treatment_Option2_Q2 = array(null=>'', '1' => '1. Inpatient', 'NA' => 'N/A');
        $treatment_Option3_Q2 = array(null=>'', '2' => '2. Outpatient', 'NA' => 'N/A');
        $treatment_Option4_Q2 = array(null=>'', '3' => '3. ECT', 'NA' => 'N/A');
        $treatment_Option5_Q2 = array(null=>'', '4' => '4. Medication', 'NA' => 'N/A');
        $treatment_Option6_Q2 = array(null=>'', '9' => '9. Unknown', 'NA' => 'N/A');
        $question7_Options = array(null=>'', '0' => '0. None', '1' => '1. Impaired', '2'=>'2. Incapacitation', '9'=>'9. Unknown', 'NA' => 'N/A');    
        $question8_Options = array(null=>'', '1' => '1. Good', '2'=>'2. Fair', '3'=>'3. Poor', 'NA' => 'N/A');
 
        // Mania Checklist
        $this->form->addElement("static", null, "For most of the time day and night over several days, did he/she (more than usual)...");
        $this->form->addElement("select", "Mania_Q1a", "1.a) ...seem too happy/high/excited?", $questionOptions);
        $this->form->addElement("select", "Mania_Q1b", "1.b) ...become so excited or agitated it was impossible to talk with him/her?", $questionOptions);
        $this->form->addElement("text", "Mania_Q1bDescription", "If yes, Describe:");
        $this->form->addElement("select", "Mania_Q1c", "1.c) ...act very irritable or angry?", $questionOptions);
        $this->form->addElement("text", "Mania_Q1cDescription", "If yes, Describe:");
        $this->form->addElement("select", "Mania_Q1d", "1.d) ...need less sleep without feeling tired?", $questionOptions);
        $this->form->addElement("text", "Mania_Q1dDescription", "If yes, Describe:");
        $this->form->addElement("select", "Mania_Q1e", "1.e) ...show poor judgment (e.g., spending sprees, sexual indiscretions?)", $questionOptions);
        $this->form->addElement("text", "Mania_Q1eDescription", "If yes, Describe:");
        $this->form->addElement("select", "Mania_Q1f", "1.f) During these episodes of (list some positives from 1a-1e) did ______behave in such a way as to cause difficulty for those around him/her (obnoxious/manipulative)?", $questionOptions);
        $this->form->addElement("select", "Mania_Q1g", "1.g) During these episodes of (list some positives from 1a-1e) did ______ feel that he/she had special gifts or powers?", $questionOptions);
        $this->form->addElement("select", "Mania_Q1h", "1.h) During these episodes of (list some positives from 1a-1e) did ______ become more talkative than usual?", $questionOptions);
        $this->form->addElement("select", "Mania_Q1i", "1.i) During these episodes of (list some positives from 1a-1e) did ______ jump from one idea to another?", $questionOptions);
        $this->form->addElement("select", "Mania_Q1j", "1.j) During these episodes of (list some positives from 1a-1e) did ______ become easily distracted?", $questionOptions);
        $this->form->addElement("select", "Mania_Q1k", "1.k) During these episodes of (list some positives from 1a-1e) did ______ get involved in too many activities at work or school?", $questionOptions);
        $this->form->addElement("select", "Mania_Q1l", "1.l) During these episodes of (list some positives from 1a-1e) did ______ have visions?  Hear voices?  Have beliefs or behavior that seem strange or unusual, at the same time as (above symptoms)?  (If YES, complete a Psychosis Checklist after this one.)", $questionOptions);
      
        $this->form->addElement("static", null, "2.	Did ______ receive professional treatment for these issues?");
        $this->form->addElement("select", "Mania_Q2_Treatment1", "0. ", $treatment_Option1_Q2);
        $this->form->addElement("select", "Mania_Q2_Treatment2", "1. ", $treatment_Option2_Q2);
        $this->form->addElement("select", "Mania_Q2_Treatment3", "2. ", $treatment_Option3_Q2);
        $this->form->addElement("select", "Mania_Q2_Treatment4", "3. ", $treatment_Option4_Q2);
        $this->form->addElement("select", "Mania_Q2_Treatment5", "4. ", $treatment_Option5_Q2);
        $this->form->addElement("select", "Mania_Q2_Treatment6", "9. ", $treatment_Option6_Q2);
        $this->form->addElement("textarea", "Mania_Q2Description", "Please describe:");
        
        $this->form->addElement("text", "Mania_Q3_Age", "3. Age of onset (in years - numbers only!)");
        $this->form->addElement("advcheckbox", "Mania_Q3NA", "NA");
        $this->form->addElement("text", "Mania_Q4_Episodes", "4. Number of episodes (numbers only!)");
        $this->form->addElement("advcheckbox", "Mania_Q4NA", "NA");
        $this->form->addElement("text", "Mania_Q5_Duration", "5. Duration of longest episode in weeks (numbers only!)");
        $this->form->addElement("advcheckbox", "Mania_Q5NA", "NA");
        $this->form->addElement("text", "Mania_Q6_Recent", "6. Most recent episode (Number of months prior to current date.)");
        $this->form->addElement("advcheckbox", "Mania_Q6NA", "NA");
        $this->form->addElement("select", "Mania_Q7_Impairment", "7. Rate and code impairment or incapacitation:", $question7_Options);
        $this->form->addElement("select", "Mania_Q8_Reliability", "8. Reliability", $question8_Options); 
        
        // Rules for questions
        $this->form->addRule("Mania_Q1a","Required",'required',null);
        $this->form->addRule("Mania_Q1b","Required",'required',null);
        $this->form->addRule("Mania_Q1c","Required",'required',null);
        $this->form->addRule("Mania_Q1d","Required",'required',null);
        $this->form->addRule("Mania_Q1e","Required",'required',null);
        $this->form->addRule("Mania_Q1f","Required",'required',null);
        $this->form->addRule("Mania_Q1g","Required",'required',null);
        $this->form->addRule("Mania_Q1h","Required",'required',null);
        $this->form->addRule("Mania_Q1i","Required",'required',null);
        $this->form->addRule("Mania_Q1j","Required",'required',null);
        $this->form->addRule("Mania_Q1k","Required",'required',null);
        $this->form->addRule("Mania_Q1l","Required",'required',null);
        $this->form->addRule("Mania_Q2_Treatment1", "Required", 'required', null);
        $this->form->addRule("Mania_Q2_Treatment2", "Required", 'required', null);
        $this->form->addRule("Mania_Q2_Treatment3", "Required", 'required', null);
        $this->form->addRule("Mania_Q2_Treatment4", "Required", 'required', null);
        $this->form->addRule("Mania_Q2_Treatment5", "Required", 'required', null);
        $this->form->addRule("Mania_Q2_Treatment6", "Required", 'required', null);
        $this->form->addRule(array('Mania_Q3_Age', 'Mania_Q3NA'), 'Age of onset is required if available', 'requiredIf', array('operator'=>'!=', 'value'=>'1'));
        $this->setRequired('Mania_Q3_Age');
        $this->form->addRule(array('Mania_Q4_Episodes', 'Mania_Q4NA'), 'Number of Episodes is required if available', 'requiredIf', array('operator'=>'!=', 'value'=>'1'));
        $this->setRequired('Mania_Q4_Episodes');
        $this->form->addRule(array('Mania_Q5_Duration', 'Mania_Q5NA'), 'Duration of Episode is required if available', 'requiredIf', array('operator'=>'!=', 'value'=>'1'));
        $this->setRequired('Mania_Q5_Duration');
        $this->form->addRule(array('Mania_Q6_Recent', 'Mania_Q6NA'), 'Most Recent Episode is required if available', 'requiredIf', array('operator'=>'!=', 'value'=>'1'));
        $this->setRequired('Mania_Q6_Recent');
        $this->form->addRule("Mania_Q7_Impairment","Required",'required',null);
        $this->form->addRule("Mania_Q8_Reliability","Required",'required',null);

    } // End Function
    
    function _setupFigsRelativesPsychosis()  // Psychosis Checklist
    {
        // Display test name
        $this->form->addElement('header', null, "Psychosis Checklist");
        
        // Create option set
        $questionOptions = array(null=>'', '0' => '0. No', '1' => '1. Yes', '9'=>'9. Unk', 'NA' => 'N/A');
        $treatment_Option1_Q5 = array(null=>'', '0' => '0. None', 'NA' => 'N/A');
        $treatment_Option2_Q5 = array(null=>'', '1' => '1. Inpatient', 'NA' => 'N/A');
        $treatment_Option3_Q5 = array(null=>'', '2' => '2. Outpatient', 'NA' => 'N/A');
        $treatment_Option4_Q5 = array(null=>'', '3' => '3. ECT', 'NA' => 'N/A');
        $treatment_Option5_Q5 = array(null=>'', '4' => '4. Medication', 'NA' => 'N/A');
        $treatment_Option6_Q5 = array(null=>'', '9' => '9. Unknown', 'NA' => 'N/A');
        $question9_Options = array(null=>'', 'Yes' => 'Yes', 'No' => 'No', 'Unsure'=>'Unsure', 'NA' => 'N/A');
        $question10_Options = array(null=>'', '0' => '0. None', '1' => '1. Impaired', '2'=>'2. Incapacitation', '9'=>'9. Unknown', 'NA' => 'N/A');
        $question12_Options = array(null=>'', '1' => '1. Good', '2'=>'2. Fair', '3'=>'3. Poor', 'NA' => 'N/A');
        
        // Psychosis Checklist
        $this->form->addElement("text", "Psychosis_Q1_Beliefs", "1. What were his/her unusual beliefs or experiences?");
        $this->form->addElement("select", "Psychosis_Q1a", "1.a) ...believe people were following him/her, or that someone was trying to hurt or poison him/her?", $questionOptions);
        $this->form->addElement("select", "Psychosis_Q1b", "1.b) ...believe someone was reading his/her mind?", $questionOptions);
        $this->form->addElement("select", "Psychosis_Q1c", "1.c) ...believe he/she was under the control of some outside person, power or force?", $questionOptions);
        $this->form->addElement("select", "Psychosis_Q1d", "1.d) ...believe his/her thoughts were broadcast, or that an outside force took away his/her thoughts or put thoughts into his/her head?", $questionOptions);
        $this->form->addElement("select", "Psychosis_Q1e", "1.e) ...have any other strange or unusual beliefs?", $questionOptions);
        $this->form->addElement("text", "Psychosis_Q1eDescription", "If yes, describe:");
        $this->form->addElement("select", "Psychosis_Q1f", "1.f) ...see things that were not really there?", $questionOptions);
        $this->form->addElement("select", "Psychosis_Q1g", "1.g) ...hear voices or other sounds that were not real?", $questionOptions);
        $this->form->addElement("text", "Psychosis_Q1gDescription", "If yes, describe:");
        $this->form->addElement("select", "Psychosis_Q1h", "1.h) ...speak in a way that was difficult to make sense of?", $questionOptions);
        $this->form->addElement("text", "Psychosis_Q1hDescription", "If yes, describe:");
        $this->form->addElement("select", "Psychosis_Q1i", "1.i) ...seem to be physically stuck in one position, or move around excitedly without any purpose?
 ", $questionOptions);
        $this->form->addElement("select", "Psychosis_Q1j", "1.j)	...appear to have no emotions, or inappropriate emotions?", $questionOptions);
        $this->form->addElement("text", "Psychosis_Q2_Duration", "2. How long did the longest of these experiences last (weeks)?");
        $this->form->addElement("advcheckbox", "Psychosis_Q2NA", "NA");
        $this->form->addElement("select", "Psychosis_Q3_MoodDisturbance", "3. When any (SX above) happened, did he/she also have the mood disturbance we discussed before, at the same time?", $questionOptions);
        $this->form->addElement("select", "Psychosis_Q4_NoDepression", "4 (2 on paper). Code yes if illness described above, or medication, was ever present for as long as one week without depression or mania", $questionOptions);
       
        $this->form->addElement("static", null, "5. Code and describe professional treatment (Code and describe all that apply):");
        $this->form->addElement("select", "Psychosis_Q5_Treatment1", "0. ", $treatment_Option1_Q5);
        $this->form->addElement("select", "Psychosis_Q5_Treatment2", "1. ", $treatment_Option2_Q5);
        $this->form->addElement("select", "Psychosis_Q5_Treatment3", "2. ", $treatment_Option3_Q5);
        $this->form->addElement("select", "Psychosis_Q5_Treatment4", "3. ", $treatment_Option4_Q5);
        $this->form->addElement("select", "Psychosis_Q5_Treatment5", "4. ", $treatment_Option5_Q5);
        $this->form->addElement("select", "Psychosis_Q5_Treatment6", "9. ", $treatment_Option6_Q5);
        $this->form->addElement("textarea", "Psychosis_Q5Description", "Please describe treatments:");

        $this->form->addElement("text", "Psychosis_Q6_Age", "6. Age of onset (years - numbers only!)?");
        $this->form->addElement("advcheckbox", "Psychosis_Q6NA", "NA");
        $this->form->addElement("text", "Psychosis_Q7_Episodes", "7. Number of episodes (Code 111 if chronic symptoms and/or treatment since onset)");
        $this->form->addElement("advcheckbox", "Psychosis_Q7NA", "NA");
        $this->form->addElement("text", "Psychosis_Q8Weeks_Duration", "8. Total illness duration (all episodes, includes active and prodromal and/or residual symptoms and/or treatment) (Weeks - numbers only!)");
        $this->form->addElement("text", "Psychosis_Q8Years_Duration", "8. Total illness duration (all episodes, includes active and prodromal and/or residual symptoms and/or treatment) (Years - numbers only!)");
        $this->form->addElement("advcheckbox", "Psychosis_Q8NA", "NA");
        $this->form->addElement("select", "Psychosis_Q9_Current", "9, Are these problems still current?", $question9_Options);
        $this->form->addElement("select", "Psychosis_Q10_Impairment", "10. Rate and code impairment or incapacitation:", $question10_Options);
        $this->form->addElement("select", "Psychosis_Q11_Substance", "11. Was this problem/or these symptoms related to another medical illness or related to substance use?", $questionOptions);
        $this->form->addElement("text", "Psychosis_Q11Description", "If yes, describe:");
        $this->form->addElement("select", "Psychosis_Q12_Reliability", "12. Interviewer judgment on reliability of this information:", $question12_Options);
        
        // Rules for questions
        $this->form->addRule("Psychosis_Q1a","Required",'required',null);
        $this->form->addRule("Psychosis_Q1b","Required",'required',null);
        $this->form->addRule("Psychosis_Q1c","Required",'required',null);
        $this->form->addRule("Psychosis_Q1d","Required",'required',null);
        $this->form->addRule("Psychosis_Q1e","Required",'required',null);
        $this->form->addRule("Psychosis_Q1f","Required",'required',null);
        $this->form->addRule("Psychosis_Q1g","Required",'required',null);
        $this->form->addRule("Psychosis_Q1h","Required",'required',null);
        $this->form->addRule("Psychosis_Q1i","Required",'required',null);
        $this->form->addRule("Psychosis_Q1j","Required",'required',null);
        $this->form->addRule(array('Psychosis_Q2_Duration', 'Psychosis_Q2NA'), 'Duration of Episode is required if available', 'requiredIf', array('operator'=>'!=', 'value'=>'1'));
        $this->setRequired('Psychosis_Q2_Duration');
        $this->form->addRule("Psychosis_Q3_MoodDisturbance","Required",'required',null);
        $this->form->addRule("Psychosis_Q4_NoDepression","Required",'required',null);
        $this->form->addRule("Psychosis_Q5_Treatment1", "Required", 'required', null);
        $this->form->addRule("Psychosis_Q5_Treatment2", "Required", 'required', null);
        $this->form->addRule("Psychosis_Q5_Treatment3", "Required", 'required', null);
        $this->form->addRule("Psychosis_Q5_Treatment4", "Required", 'required', null);
        $this->form->addRule("Psychosis_Q5_Treatment5", "Required", 'required', null);
        $this->form->addRule("Psychosis_Q5_Treatment6", "Required", 'required', null);
        $this->form->addRule(array('Psychosis_Q6_Age', 'Psychosis_Q6NA'), 'Age of onset is required if available', 'requiredIf', array('operator'=>'!=', 'value'=>'1'));
        $this->setRequired('Psychosis_Q6_Age');
        $this->form->addRule(array('Psychosis_Q7_Episodes', 'Psychosis_Q7NA'), 'Number of Episodes is required if available', 'requiredIf', array('operator'=>'!=', 'value'=>'1'));
        $this->setRequired('Psychosis_Q7_Episodes');
        $this->form->addRule(array('Psychosis_Q8Weeks_Duration', 'Psychosis_Q8NA'), 'Duration of Illness is required if available', 'requiredIf', array('operator'=>'!=', 'value'=>'1'));
        $this->setRequired('Psychosis_Q8Weeks_Duration');
        $this->form->addRule("Psychosis_Q9_Current","Required",'required',null);
        $this->form->addRule("Psychosis_Q10_Impairment","Required",'required',null);
        $this->form->addRule("Psychosis_Q11_Substance","Required",'required',null);
        $this->form->addRule("Psychosis_Q12_Reliability","Required",'required',null);
        
    } // End Function
    
    function _setupFigsRelativesAlcohol() // Alcohol
    {
        // Display test name
        $this->form->addElement('header', null, "Alcohol");
       
        // Create option set
        $questionOptions = array(null=>'', '0' => '0. No', '1' => '1. Yes', '9'=>'9. Unk', 'NA' => 'N/A');
        $treatment_Option1_Q2 = array(null=>'', '0' => '0. None', 'NA' => 'N/A');
        $treatment_Option2_Q2 = array(null=>'', '1' => '1. Inpatient', 'NA' => 'N/A');
        $treatment_Option3_Q2 = array(null=>'', '2' => '2. Outpatient', 'NA' => 'N/A');
        $treatment_Option4_Q2 = array(null=>'', '3' => '3. AA or other self-help', 'NA' => 'N/A');
        $treatment_Option5_Q2 = array(null=>'', '4' => '4. Medication', 'NA' => 'N/A');
        $treatment_Option6_Q2 = array(null=>'', '9' => '9. Unknown', 'NA' => 'N/A');
        $question5_Options = array(null=>'', '1' => '1. Good', '2'=>'2. Fair', '3'=>'3. Poor', 'NA' => 'N/A');
       
       
        $this->form->addElement("static", null, "Because of drinking, did he/she ever have problems such as...");
        $this->form->addElement("select", "Alcohol_Q1a", "1.a) ...being unable to stop or cut down on drinking?", $questionOptions);
        $this->form->addElement("select", "Alcohol_Q1b", "1.b) ...spending a lot of time drinking or being hung over?", $questionOptions);
        $this->form->addElement("select", "Alcohol_Q1c", "1.c) ...being unable to work, go to school, or take care of household responsibilities?", $questionOptions);
        $this->form->addElement("select", "Alcohol_Q1d", "1.d) ...being high from drinking when he/she could get hurt?", $questionOptions);
        $this->form->addElement("select", "Alcohol_Q1e", "1.e) ...accidental injuries?", $questionOptions);
        $this->form->addElement("select", "Alcohol_Q1f", "1.f) ...reducing or giving up important activities?", $questionOptions);
        $this->form->addElement("select", "Alcohol_Q1g", "1.g) ...objections from the family or friends, at work or school?", $questionOptions);
        $this->form->addElement("select", "Alcohol_Q1h", "1.h) ...legal problems more than once (DWIs, arrests)?", $questionOptions);
        $this->form->addElement("select", "Alcohol_Q1i", "1.i) ...blackouts more than once?", $questionOptions);
        $this->form->addElement("select", "Alcohol_Q1j", "1.j) ...binges or benders more than once?", $questionOptions);
        $this->form->addElement("select", "Alcohol_Q1k", "1.k) ...physical health problems (liver disease, pancreatitis)?", $questionOptions);
        $this->form->addElement("select", "Alcohol_Q1l", "1.l) ...emotional or psychological problems (uninterested, depressed, suspicious/paranoid, having strange ideas)?", $questionOptions);
        $this->form->addElement("select", "Alcohol_Q1m", "1.m) ...withdrawal symptoms (shakes, seizures/convulsions, DTs)?", $questionOptions);
        $this->form->addElement("static", null, "2. Did he/she go to AA or have any kind of treatment? (Code and describe all that apply)");
        $this->form->addElement("select", "Alcohol_Q2_Treatment1", "0. ", $treatment_Option1_Q2);
        $this->form->addElement("select", "Alcohol_Q2_Treatment2", "1. ", $treatment_Option2_Q2);
        $this->form->addElement("select", "Alcohol_Q2_Treatment3", "2. ", $treatment_Option3_Q2);
        $this->form->addElement("select", "Alcohol_Q2_Treatment4", "3. ", $treatment_Option4_Q2);
        $this->form->addElement("select", "Alcohol_Q2_Treatment5", "4. ", $treatment_Option5_Q2);
        $this->form->addElement("select", "Alcohol_Q2_Treatment6", "9. ", $treatment_Option6_Q2);
 
        $this->form->addElement("textarea", "Alcohol_Q2Description", "Please describe treatments:");
        $this->form->addElement("select", "Alcohol_Q3_Current", "3. Does he/she currently have a problem with alcohol?", $questionOptions);
        $this->form->addElement("text", "Alcohol_Q4_OnsetAge", "4. Record age he/she began to have alcohol-related problems (years -- numbers only!).");
        $this->form->addElement("advcheckbox", "Alcohol_Q4NA", "NA");
        $this->form->addElement("text", "Alcohol_Q5_RecoverAge", "5. Record age he/she stopped drinking heavily (years -- numbers only!).");
        $this->form->addElement("advcheckbox", "Alcohol_Q5NA", "NA");
        $this->form->addElement("select", "Alcohol_Q5a_Reliability", "5.a) Interviewer judgment on reliability of this information:", $question5_Options);
        
        // Rules for questions
        $this->form->addRule("Alcohol_Q1a","Required",'required',null);
        $this->form->addRule("Alcohol_Q1b","Required",'required',null);
        $this->form->addRule("Alcohol_Q1c","Required",'required',null);
        $this->form->addRule("Alcohol_Q1d","Required",'required',null);
        $this->form->addRule("Alcohol_Q1e","Required",'required',null);
        $this->form->addRule("Alcohol_Q1f","Required",'required',null);
        $this->form->addRule("Alcohol_Q1g","Required",'required',null);
        $this->form->addRule("Alcohol_Q1h","Required",'required',null);
        $this->form->addRule("Alcohol_Q1i","Required",'required',null);
        $this->form->addRule("Alcohol_Q1j","Required",'required',null);
        $this->form->addRule("Alcohol_Q1k","Required",'required',null);
        $this->form->addRule("Alcohol_Q1l","Required",'required',null);
        $this->form->addRule("Alcohol_Q1m","Required",'required',null);
        $this->form->addRule("Alcohol_Q2_Treatment1", "Required", 'required', null);
        $this->form->addRule("Alcohol_Q2_Treatment2", "Required", 'required', null);
        $this->form->addRule("Alcohol_Q2_Treatment3", "Required", 'required', null);
        $this->form->addRule("Alcohol_Q2_Treatment4", "Required", 'required', null);
        $this->form->addRule("Alcohol_Q2_Treatment5", "Required", 'required', null);
        $this->form->addRule("Alcohol_Q2_Treatment6", "Required", 'required', null);
        $this->form->addRule("Alcohol_Q3_Current","Required",'required',null);
        $this->form->addRule(array('Alcohol_Q4_OnsetAge', 'Alcohol_Q4NA'), 'Age of onset is required if available', 'requiredIf', array('operator'=>'!=', 'value'=>'1'));
        $this->setRequired('Alcohol_Q4_OnsetAge');
        $this->form->addRule(array('Alcohol_Q5_RecoverAge', 'Alcohol_Q5NA'), 'Age of onset is required if available', 'requiredIf', array('operator'=>'!=', 'value'=>'1'));
        $this->setRequired('Alcohol_Q5_RecoverAge');
        $this->form->addRule("Alcohol_Q5a_Reliability","Required",'required',null);
        
    } // End function _setupFigsRelativesAlcohol

    function _setupFigsRelativesDrugs() // Drug Abuse
    {
        $questionOptions = array(null=>'', '0' => '0. No', '1' => '1. Yes', '9'=>'9. Unk', 'NA' => 'N/A');
        $treatment_Option1_Q8 = array(null=>'', '0' => '0. None', 'NA' => 'N/A');
        $treatment_Option2_Q8 = array(null=>'', '1' => '1. Outpatient', 'NA' => 'N/A');
        $treatment_Option3_Q8 = array(null=>'', '2' => '2. AA or other self-help', 'NA' => 'N/A');
        $treatment_Option4_Q8 = array(null=>'', '3' => '3. Medication', 'NA' => 'N/A');
        $treatment_Option5_Q8 = array(null=>'', '4' => '4. Inpatient', 'NA' => 'N/A');
        $treatment_Option6_Q8 = array(null=>'', '9' => '9. Unknown', 'NA' => 'N/A');
        $question12_Options = array(null=>'', '1' => '1. Good', '2'=>'2. Fair', '3'=>'3. Poor', 'NA' => 'N/A');
 
        $this->form->addElement("header", null, "Other Drugs Abuse");
        $this->form->addElement("static", null, "Note: List all drugs; Circle most used substance and/or substance that caused the most problems.");
        $this->form->addElement("text", "Alcohol_Q6_WhichDrugs", "6. Which drugs did he/she have trouble with? (list all drugs used)");
        $this->form->addElement("advcheckbox", "Alcohol_Q6_NA", "NA");
        $this->form->addElement("static", null, "Specify which drugs casued the most problems. (up to 3 drugs)");
        
        $this->form->addElement("text", "Alcohol_Q6a_MostProblemDrug1", "Drug 1"); // OK as 3 separated fields?
        $this->form->addElement("text", "Alcohol_Q6a_MostProblemDrug2", "Drug 2"); // OK as 3 separated fields?
        $this->form->addElement("text", "Alcohol_Q6a_MostProblemDrug3", "Drug 3"); // OK as 3 separated fields?
        
        $this->form->addElement("static", null, "7. Because of his/her drug use, did he/she have...");
        $this->form->addElement("select", "Alcohol_Q7a", "7.a) ... physical health problems (hepatitis, overdose, HIV, withdrawal symptoms, accidental injuries)?", $questionOptions);
        $this->form->addElement("select", "Alcohol_Q7b", "7.b) ... emotional or psychological problems (uninterested, depressed, irritable, suspicious/paranoid, having strange ideas)?", $questionOptions);
        $this->form->addElement("select", "Alcohol_Q7c", "7.c) ... legal problems (arrests for possessing, selling, or stealing drugs)?", $questionOptions);
        $this->form->addElement("select", "Alcohol_Q7d", "7.d) ... distress or problems with family or friends?", $questionOptions);
        $this->form->addElement("select", "Alcohol_Q7e", "7.e) ... Did he/she repeatedly try to stop using ________________? (three times or more)", $questionOptions);
        $this->form->addElement("select", "Alcohol_Q7f", "7.f) ... Did he/she have problems with withdrawal if he/she stopped using?", $questionOptions);
       
        $this->form->addElement("static", null, "8. Did he/she go to support groups (such as NA) or have any kind of treatment? (Code and describe all that apply)");
        $this->form->addElement("select", "Alcohol_Q8_Treatment1", "0. ", $treatment_Option1_Q8);
        $this->form->addElement("select", "Alcohol_Q8_Treatment2", "1. ", $treatment_Option2_Q8);
        $this->form->addElement("select", "Alcohol_Q8_Treatment3", "2. ", $treatment_Option3_Q8);
        $this->form->addElement("select", "Alcohol_Q8_Treatment4", "3. ", $treatment_Option4_Q8);
        $this->form->addElement("select", "Alcohol_Q8_Treatment5", "4. ", $treatment_Option5_Q8);
        $this->form->addElement("select", "Alcohol_Q8_Treatment6", "9. ", $treatment_Option6_Q8);
        $this->form->addElement("textarea", "Alcohol_Q8Description", "Please describe:");
        $this->form->addElement("select", "Alcohol_Q9_Current", "9. Does he/she currently have a problem with _________________________________?", $questionOptions);
        $this->form->addElement("text", "Alcohol_Q10_OnsetAge", "10. Record age he/she began to have drug related problems (age in years -- numbers only!).");
        $this->form->addElement("advcheckbox", "Alcohol_Q10NA", "NA");
        $this->form->addElement("text", "Alcohol_Q11_RecoverAge", "11. Record age he/she stopped using drugs heavily. (age in years -- numbers only!)");
        $this->form->addElement("advcheckbox", "Alcohol_Q11NA", "NA");
        $this->form->addElement("select", "Alcohol_Q12_Reliability", "12. Interviewer judgment on reliability of this information:", $question12_Options);
        
        // Rules for questions
        $this->form->addRule(array('Alcohol_Q6_WhichDrugs', 'Alcohol_Q6_NA'), 'Required if available', 'requiredIf', array('operator'=>'!=', 'value'=>'1'));
        $this->setRequired('Alcohol_Q6_WhichDrugs');
        $this->form->addRule("Alcohol_Q7a","Required",'required', null);
        $this->form->addRule("Alcohol_Q7b","Required",'required', null);
        $this->form->addRule("Alcohol_Q7c","Required",'required', null);
        $this->form->addRule("Alcohol_Q7d","Required",'required', null);
        $this->form->addRule("Alcohol_Q7e","Required",'required', null);
        $this->form->addRule("Alcohol_Q7f","Required",'required', null);
        $this->form->addRule("Alcohol_Q8_Treatment1", "Required", 'required', null);
        $this->form->addRule("Alcohol_Q8_Treatment2", "Required", 'required', null);
        $this->form->addRule("Alcohol_Q8_Treatment3", "Required", 'required', null);
        $this->form->addRule("Alcohol_Q8_Treatment4", "Required", 'required', null);
        $this->form->addRule("Alcohol_Q8_Treatment5", "Required", 'required', null);
        $this->form->addRule("Alcohol_Q8_Treatment6", "Required", 'required', null);
        $this->form->addRule(array('Alcohol_Q8Description', 'Alcohol_Q8_Treatment'), 'Description is required if available', 'requiredIf', array('operator'=>'!=', 'value'=>'NA'));
        $this->setRequired('Alcohol_Q8Description');
        $this->form->addRule("Alcohol_Q9_Current","Required",'required', null);
        $this->form->addRule(array('Alcohol_Q10_OnsetAge', 'Alcohol_Q10NA'), 'Age of onset is required if available', 'requiredIf', array('operator'=>'!=', 'value'=>'1'));
        $this->setRequired('Alcohol_Q10_OnsetAge');
        $this->form->addRule(array('Alcohol_Q11_RecoverAge', 'Alcohol_Q11NA'), 'Age of drug use ceasation is required if available', 'requiredIf', array('operator'=>'!=', 'value'=>'1'));
        $this->setRequired('Alcohol_Q11_RecoverAge');
        $this->form->addRule("Alcohol_Q12_Reliability","Required",'required', null);
        
    } // End function _setupFigsRelativesDrugs
    
    function _setupFigsRelativesNicotine() // Nicotine
    {

        $questionOptions = array(null=>'', '0' => '0. No', '1' => '1. Yes', '9'=>'9. Unk', 'NA' => 'N/A');
        $question19_Options = array(null=>'', '1' => '1. Good', '2'=>'2. Fair', '3'=>'3. Poor', 'NA' => 'N/A');
        

        $this->form->addElement("header", null, "Nicotine");
        $this->form->addElement("text", "Alcohol_Q13_WhichNicotine", "13. Which type of nicotine did he/she use?");
        $this->form->addElement("select", "Alcohol_Q13a_Daily", "13a. Was he/she a daily smoker?", $questionOptions);
        $this->form->addElement("text", "Alcohol_Q13b_Maximum", "13b. How many cigarettes did he/she smoke?");
        $this->form->addElement("static", null, "14. Because of his/her nicotine use, did he/she have...");
        $this->form->addElement("select", "Alcohol_Q14a", "14.a) ...physical health problems (emphysema, lung cancer, withdrawal symptoms)?", $questionOptions);
        $this->form->addElement("static", null, "14b. OMITTED");
        $this->form->addElement("static", null, "14c. OMITTED");
        $this->form->addElement("select", "Alcohol_Q14d", "14.d) ...did he/she repeatedly try to stop using_________________? (three times or more)", $questionOptions);
        $this->form->addElement("static", null, "15. OMITTED");
        $this->form->addElement("select", "Alcohol_Q16_Current", "16. Does he/she currently smoke/use nicotine?", $questionOptions);
        $this->form->addElement("text", "Alcohol_Q17_OnsetAge", "17. Record age he/she began smoking or using nicotine (years -- numbers only!).");
        $this->form->addElement("advcheckbox", "Alcohol_Q17NA", "NA");
        $this->form->addElement("text", "Alcohol_Q18_RecoverAge", "18. Record age he/she stopped smoking or using nicotine heavily (if applicable). (years -- numbers only!)");
        $this->form->addElement("advcheckbox", "Alcohol_Q18NA", "NA");
        $this->form->addElement("select", "Alcohol_Q19_Reliability", "19. Interviewer judgment on reliability of this information:", $question19_Options);
        
        // Rules for questions
        $this->form->addRule("Alcohol_Q13_WhichNicotine","Required",'required');
        $this->form->addRule("Alcohol_Q13a_Daily","Required",'required');
        $this->form->addRule(array('Alcohol_Q13b_Maximum', 'Alcohol_Q13a_Daily'), 'Age of onset is required if available', 'requiredIf', array('operator'=>'==', 'value'=>'1'));
        $this->setRequired('Alcohol_Q13b_Maximum');
        $this->form->addRule("Alcohol_Q14a","Required",'required');
        $this->form->addRule("Alcohol_Q14d","Required",'required');
        $this->form->addRule("Alcohol_Q16_Current","Required",'required');
        $this->form->addRule(array('Alcohol_Q17_OnsetAge', 'Alcohol_Q17NA'), 'Age of onset is required if available', 'requiredIf', array('operator'=>'!=', 'value'=>'1'));
        $this->setRequired('Alcohol_Q17_OnsetAge');
        $this->form->addRule(array('Alcohol_Q18_RecoverAge', 'Alcohol_Q18NA'), 'Age of smoking ceasation is required if available', 'requiredIf', array('operator'=>'!=', 'value'=>'1'));
        $this->setRequired('Alcohol_Q18_RecoverAge');
        $this->form->addRule("Alcohol_Q19_Reliability","Required",'required', null);
        
    } // End Function  _setupFigsRelativesNicotine()
    
    function _setupFigsRelativesSchizoid()  // Paranoid, Schizoid, Schizotypal Personality Checklist
    {
        // Display test name
        $this->form->addElement('header', null, "Paranoid, Schizoid, Schizotypal Personality Checklist");
        
        // Create option set
        $questionOptions = array(null=>'', '0' => '0. No', '1' => '1. Yes', '9'=>'9. Unk', 'NA' => 'N/A');
        $treatment_Option1_Q4a = array(null=>'', '0' => '0. None', 'NA' => 'N/A');
        $treatment_Option2_Q4a = array(null=>'', '1' => '1. Inpatient', 'NA' => 'N/A');
        $treatment_Option3_Q4a = array(null=>'', '2' => '2. Outpatient', 'NA' => 'N/A');
        $treatment_Option4_Q4a = array(null=>'', '3' => '3. ECT', 'NA' => 'N/A');
        $treatment_Option5_Q4a = array(null=>'', '4' => '4. Medication', 'NA' => 'N/A');
        $treatment_Option6_Q4a = array(null=>'', '9' => '9. Unknown', 'NA' => 'N/A');
        $question4c_Options = array(null=>'', '0' => '0. None', '1' => '1. Impaired', '2'=>'2. Incapacitation', '9'=>'9. Unknown', 'NA' => 'N/A');
        $question4h_Options = array(null=>'', '1' => '1. Good', '2'=>'2. Fair', '3'=>'3. Poor', 'NA' => 'N/A');
        
        // Paranoid, Schizoid, Schizotypal Personality Checklist
        $this->form->addElement("static", null, "");
        
        // Schizoid_Question 1
        $this->form->addElement("static", null, "1. Does he/she...");
        $this->form->addElement("select", "Schizoid_Q1a", "1.a) ...often keep an eye out to stop people from taking advantage of him/her? (Expects, without sufficient basis, to be exploited/harmed by others)", $questionOptions);
        $this->form->addElement("select", "Schizoid_Q1b", "1.b) ...get concerned that friends or co-workers are not really loyal or trustworthy? (Schizoid_Questions, without justification, loyalty of friends or associates)", $questionOptions);
        $this->form->addElement("select", "Schizoid_Q1c", "1.c) ...often pick up hidden threats or put-downs from what people say or do? (Reads hidden demeaning or threatening meanings into benign remarks or events)", $questionOptions);
        $this->form->addElement("select", "Schizoid_Q1d", "1.d) ...take a long time to forgive someone if they have insulted or hurt him/her? (Bears grudges or unforgiving of insults/slights)", $questionOptions);
        $this->form->addElement("select", "Schizoid_Q1e", "1.e) ...seem to believe it is best not to let other people know much about him/her? (Reluctant to confide in others because of unwarranted fear that information will be used against him/her)", $questionOptions);
        $this->form->addElement("select", "Schizoid_Q1f", "1.f) ...often get angry about being insulted or slighted? (Easily slighted, quick to react with anger or counterattack)", $questionOptions);
        $this->form->addElement("select", "Schizoid_Q1g", "1.g) ...seem to be a jealous person?  Ever suspected that his/her spouse/partner was unfaithful? (Schizoid_Questions, without justification, fidelity of spouse or sexual partner)", $questionOptions);
        
        // Schizoid_Question 2
        $this->form->addElement("static", null, "2. Does he/she...");
        $this->form->addElement("select", "Schizoid_Q2a", "2.a) ...seem not to want or enjoy close relationships, like with family or friends? (Neither desires nor enjoys close relationships, including family)", $questionOptions);
        $this->form->addElement("select", "Schizoid_Q2b", "2.b) ...prefer to do things alone rather than with other people? (Almost always chooses solitary activities)", $questionOptions);
        $this->form->addElement("select", "Schizoid_Q2c", "2.c) ...hardly ever seem to have strong feelings, like being very angry or very happy? (Rarely, if ever, claims or appears to experience strong emotions, anger/joy)", $questionOptions);
        $this->form->addElement("select", "Schizoid_Q2d", "2.d) ...(if over 13 years of age) seem uninterested in being sexually involved with another person? (Little if any desire to have sexual experiences with another person [age taken into account])", $questionOptions);
        $this->form->addElement("select", "Schizoid_Q2e", "2.e) ...seem not to care if people praise or criticize him/her? (Indifferent to praise and criticism from others)", $questionOptions);
        $this->form->addElement("select", "Schizoid_Q2f", "2.f) ...have no one to be really close to or confide in, or just one person, outside of the immediate family? (No close friends or confidants, or only one, other than first-degree relatives)", $questionOptions);
        $this->form->addElement("select", "Schizoid_Q2g", "2.g) ...act cold or distant, hardly ever smile or nod back at people? (Constricted affect, aloof, cold, rarely reciprocates gestures or expressions)", $questionOptions);
        $this->form->addElement("select", "Schizoid_Q2h", "2.h) ...have a delay in or total lack of development of spoken language?", $questionOptions);
        $this->form->addElement("select", "Schizoid_Q2i", "2.i) ...have idiosyncrative (odd or unusual), or repetitive use of language?", $questionOptions);
        $this->form->addElement("select", "Schizoid_Q2j", "2.j) ...have restricted or repetitive patterns of behavior, interests, or activities?", $questionOptions);
        $this->form->addElement("select", "Schizoid_Q2k", "2.k) ...have repetitive motor movements (such as hand or finger flapping)?", $questionOptions);
        
        // Schizoid_Question 3
        $this->form->addElement("static", null, "3. Does he/she...");
        $this->form->addElement("select", "Schizoid_Q3a", "3.a) ...wonder if people talking to each other are talking about him/her?  Say that a common event or object is a special sign for him/her? (Ideas of reference [not delusions of reference])", $questionOptions);
        $this->form->addElement("select", "Schizoid_Q3b", "3.b) ...often act nervous in a group of unfamiliar people (doesn't improve with exposure)? (Excessive social anxiety)", $questionOptions);
        $this->form->addElement("select", "Schizoid_Q3c", "3.c) ...reports experiences with the supernatural?  Believe in astrology, seeing the future, UFOs, ESP, or a 'sixth sense'? (Odd beliefs or magical thinking, influencing behavior and inconsistent with subcultural norms)", $questionOptions);
        $this->form->addElement("select", "Schizoid_Q3d", "3.d) ...mistake objects or shadows for people, or noises for voices?  Have a sense that some invisible person or force is around?  See faces change before his/her eyes? (Unusual perceptual experiences)", $questionOptions);
        $this->form->addElement("select", "Schizoid_Q3e", "3.e) ...behave in odd or eccentric ways?  Look peculiar or untidy, have unusual mannerisms, or talk to him/herself? (Odd, eccentric, peculiar behavior or appearance)", $questionOptions);
        $this->form->addElement("select", "Schizoid_Q3f", "3.f) ...sometimes make it hard to follow what he/she is saying? Ramble off the subject, or talk in vague or abstract terms? (Odd speech [without loosened associations or incoherence])", $questionOptions);
        $this->form->addElement("select", "Schizoid_Q3g", "3.g) ...sometimes act silly, not in keeping with the situation? Or tend not to show any feelings in response to people? (Inappropriate or constricted affect [e.g., silly or aloof])", $questionOptions);
        
        // Schizoid_Question 4
        $this->form->addElement("static", null, "4. Does he/she have any kind of treatment?");
       
        $this->form->addElement("static", null, "4.a) Code and describe professional treatment:");
        $this->form->addElement("select", "Schizoid_Q4a_Treatment1", "0. ", $treatment_Option1_Q4a);
        $this->form->addElement("select", "Schizoid_Q4a_Treatment2", "1. ", $treatment_Option2_Q4a);
        $this->form->addElement("select", "Schizoid_Q4a_Treatment3", "2. ", $treatment_Option3_Q4a);
        $this->form->addElement("select", "Schizoid_Q4a_Treatment4", "3. ", $treatment_Option4_Q4a);
        $this->form->addElement("select", "Schizoid_Q4a_Treatment5", "4. ", $treatment_Option5_Q4a);
        $this->form->addElement("select", "Schizoid_Q4a_Treatment6", "9. ", $treatment_Option6_Q4a);
        $this->form->addElement("textarea", "Schizoid_Q4aDescription", "Please describe:");
        
        $this->form->addElement("text", "Schizoid_Q4b_OnsetAge", "4.b) Age of onset (years - numbers only!)");
        $this->form->addElement("advcheckbox", "Schizoid_Q4bNA", "NA");
        $this->form->addElement("select", "Schizoid_Q4c_Impairment", "4.c) Rate and code impairment or incapacitation:", $question4c_Options);
        $this->form->addElement("select", "Schizoid_Q4d_SocialProbs", "4.d) Does he/she have problems because of this behavior or thinking or feeling - either with the family or socially, or at work or school?", $questionOptions);
        $this->form->addElement("select", "Schizoid_Q4e_Unhappiness", "4.e) Does this behavior or thinking or feeling cause the person unhappiness or significant subjective distress?", $questionOptions);
        $this->form->addElement("select", "Schizoid_Q4f_Before17Yrs", "4.f) Did the behavior begin before age 17 years?", $questionOptions);
        $this->form->addElement("select", "Schizoid_Q4g_Before3Yrs", "4.g) Did the behavior begin before age 3 years?", $questionOptions);
        $this->form->addElement("select", "Schizoid_Q4h_Reliability", "4.h) Interviewer judgment on reliability of this information.", $question4h_Options);
        
        // Rules for questions
        $this->form->addRule("Schizoid_Q1a","Required",'required', null);
        $this->form->addRule("Schizoid_Q1b","Required",'required', null);
        $this->form->addRule("Schizoid_Q1c","Required",'required', null);
        $this->form->addRule("Schizoid_Q1d","Required",'required', null);
        $this->form->addRule("Schizoid_Q1e","Required",'required', null);
        $this->form->addRule("Schizoid_Q1f","Required",'required', null);
        $this->form->addRule("Schizoid_Q1g","Required",'required', null);
        $this->form->addRule("Schizoid_Q2a","Required",'required', null);
        $this->form->addRule("Schizoid_Q2b","Required",'required', null);
        $this->form->addRule("Schizoid_Q2c","Required",'required', null);
        $this->form->addRule("Schizoid_Q2d","Required",'required', null);
        $this->form->addRule("Schizoid_Q2e","Required",'required', null);
        $this->form->addRule("Schizoid_Q2f","Required",'required', null);
        $this->form->addRule("Schizoid_Q2g","Required",'required', null);
        $this->form->addRule("Schizoid_Q2h","Required",'required', null);
        $this->form->addRule("Schizoid_Q2i","Required",'required', null);
        $this->form->addRule("Schizoid_Q2j","Required",'required', null);
        $this->form->addRule("Schizoid_Q2k","Required",'required', null);
        $this->form->addRule("Schizoid_Q3a","Required",'required', null);
        $this->form->addRule("Schizoid_Q3b","Required",'required', null);
        $this->form->addRule("Schizoid_Q3c","Required",'required', null);
        $this->form->addRule("Schizoid_Q3d","Required",'required', null);
        $this->form->addRule("Schizoid_Q3e","Required",'required', null);
        $this->form->addRule("Schizoid_Q3f","Required",'required', null);
        $this->form->addRule("Schizoid_Q3g","Required",'required', null);
        $this->form->addRule("Schizoid_Q3a","Required",'required', null);
        $this->form->addRule("Schizoid_Q4a_Treatment1", "Required", 'required', null);
        $this->form->addRule("Schizoid_Q4a_Treatment2", "Required", 'required', null);
        $this->form->addRule("Schizoid_Q4a_Treatment3", "Required", 'required', null);
        $this->form->addRule("Schizoid_Q4a_Treatment4", "Required", 'required', null);
        $this->form->addRule("Schizoid_Q4a_Treatment5", "Required", 'required', null);
        $this->form->addRule("Schizoid_Q4a_Treatment6", "Required", 'required', null);
        $this->form->addRule("Schizoid_Q4aDescription","Required",'required', null);
        $this->form->addRule(array('Schizoid_Q4b_OnsetAge', 'Schizoid_Q4bNA'), 'Age of onset is required if available', 'requiredIf', array('operator'=>'!=', 'value'=>'1'));
        $this->setRequired('Schizoid_Q4b_OnsetAge');
        $this->form->addRule("Schizoid_Q4c_Impairment","Required",'required', null);
        $this->form->addRule("Schizoid_Q4d_SocialProbs","Required",'required', null);
        $this->form->addRule("Schizoid_Q4e_Unhappiness","Required",'required', null);
        $this->form->addRule("Schizoid_Q4f_Before17Yrs","Required",'required', null);
        $this->form->addRule("Schizoid_Q4g_Before3Yrs","Required",'required', null);
        $this->form->addRule("Schizoid_Q4h_Reliability","Required",'required', null);
        
    } // End Function
    
    function _setupFigsRelativesASP()  // Antisocial Personality Disorder Checklist
    {
        // Display test name
        $this->form->addElement('header', null, "Antisocial Personality Disorder Checklist");
        
        // Create option set
        $questionOptions = array(null=>'', '0' => '0. No', '1' => '1. Yes', '9'=>'9. Unk', 'NA' => 'N/A');
        
        // ASP_Questions
        $this->form->addElement("static", null, "1. Does or did he/she have frequent problems with disregarding the rights of others such as...");
        $this->form->addElement("select", "ASP_Q1a", "1.a) ...breaking laws that can lead to being arrested?", $questionOptions);
        $this->form->addElement("select", "ASP_Q1b", "1.b) ...being deceitful (such as repeated lying, using aliases, conning others)?", $questionOptions);
        $this->form->addElement("select", "ASP_Q1c", "1.c) ...being impulsive or failing to plan ahead?", $questionOptions);
        $this->form->addElement("select", "ASP_Q1d", "1.d) ...being irritable and aggressive such as being involved in physical fights or assaults?", $questionOptions);
        $this->form->addElement("select", "ASP_Q1e", "1.e) ...being reckless about their own safety or the safety of others?", $questionOptions);
        $this->form->addElement("select", "ASP_Q1f", "1.f) ...being irresponsible about work or financial obligations?", $questionOptions);
        $this->form->addElement("select", "ASP_Q1g", "1.g) ...show a lack of remorse about mistreating others?", $questionOptions);
        $this->form->addElement("select", "ASP_Q2_Over15Yrs", "2. Was he/she at least age 15 years when this behavior occurred?", $questionOptions);
        $this->form->addElement("select", "ASP_Q3_Under15Yrs", "3. Did he/she have some signs of conduct disorder or juvenile delinquency before age 15 years (aggression to animals or people, destruction of other's property, fire setting, theft, repeated lying, truancy from school, running away, conning others, repeated curfew violations)?", $questionOptions);
        
        // Rules for questions
        $this->form->addRule("ASP_Q1a","Required",'required', null);
        $this->form->addRule("ASP_Q1b","Required",'required', null);
        $this->form->addRule("ASP_Q1c","Required",'required', null);
        $this->form->addRule("ASP_Q1d","Required",'required', null);
        $this->form->addRule("ASP_Q1e","Required",'required', null);
        $this->form->addRule("ASP_Q1f","Required",'required', null);
        $this->form->addRule("ASP_Q1g","Required",'required', null);
        $this->form->addRule("ASP_Q2_Over15Yrs","Required",'required', null);
        $this->form->addRule("ASP_Q3_Under15Yrs","Required",'required', null);
        
    } // End Function
    
    function _setupFigsRelativesTic()  // Tic Disorder Checklist
    {
        // Display test name
        $this->form->addElement('header', null, "Tic Disorder Checklist");
        
        // Create option set
        $questionOptions = array(null=>'', '0' => '0. No', '1' => '1. Yes', '9'=>'9. Unk', 'NA' => 'N/A');
        $treatment_Option1_Q3a = array(null=>'', '0' => '0. None', 'NA' => 'N/A');
        $treatment_Option2_Q3a = array(null=>'', '1' => '1. Inpatient', 'NA' => 'N/A');
        $treatment_Option3_Q3a = array(null=>'', '2' => '2. Outpatient', 'NA' => 'N/A');
        $treatment_Option4_Q3a = array(null=>'', '3' => '3. ECT', 'NA' => 'N/A');
        $treatment_Option5_Q3a = array(null=>'', '4' => '4. Medication', 'NA' => 'N/A');
        $treatment_Option6_Q3a = array(null=>'', '9' => '9. Unknown', 'NA' => 'N/A');
        $question3e_Options = array(null=>'', '0' => '0. None', '1' => '1. Impaired', '2'=>'2. Incapacitation', '9'=>'9. Unknown', 'NA' => 'N/A');
        $question3f_Options = array(null=>'', '1' => '1. Good', '2'=>'2. Fair', '3'=>'3. Poor', 'NA' => 'N/A');
        
        // Question 1
        $this->form->addElement("select", "Tic_Q1", "1. Does or did he/she have single or multiple motor tics (sudden, rapid, recurrent, nonrhythmic, stereotyped motor movements) that occurred many times a day?", $questionOptions);
        $this->form->addElement("text", "Tic_Q1Description", "If no, skip to question 2. If yes, describe:");
        $this->form->addElement("select", "Tic_Q1a", "1.a) ...did the motor tic(s) last 4 or more weeks?", $questionOptions);
        $this->form->addElement("select", "Tic_Q1b", "1.b) ...did the motor tic(s) last a year or more?", $questionOptions);
        $this->form->addElement("select", "Tic_Q1c", "1.c) ...did the motor tic(s) start before age 18 years?", $questionOptions);
        $this->form->addElement("select", "Tic_Q1d", "1.d) ...did the motor tic(s) cause distress for _________ or impairment at school,
work or with social relationships?", $questionOptions);
        
        // Tic_Question 2
        $this->form->addElement("select", "Tic_Q2", "2. Did he/she have single or multiple vocal tics (sudden, rapid, recurrent, nonrhythmic, stereotyped vocalizations) that occurred many times a day?", $questionOptions);
        $this->form->addElement("text", "Tic_Q2Description", "If no to question 2, but yes to question 1, skip to question 3. If no to both discontinue checklist. If yes, describe:");
        $this->form->addElement("select", "Tic_Q2a", "2.a) ...did the vocal tic(s) last 4 or more weeks?", $questionOptions);
        $this->form->addElement("select", "Tic_Q2b", "2.b) ...did the vocal tic(s) last a year or more?", $questionOptions);
        $this->form->addElement("select", "Tic_Q2c", "2.c) ...did the vocal tic(s) start before age 18 years?", $questionOptions);
        $this->form->addElement("select", "Tic_Q2d", "2.d) ...did the vocal tic(s) cause distress for __________ or impairment at school, work or with social relationships?", $questionOptions);
        
        // Tic_Question 3
        $this->form->addElement("static", null, "3.a) Code and describe professional treatment:");
        $this->form->addElement("select", "Tic_Q3a_Treatment1", "0. ", $treatment_Option1_Q3a);
        $this->form->addElement("select", "Tic_Q3a_Treatment2", "1. ", $treatment_Option2_Q3a);
        $this->form->addElement("select", "Tic_Q3a_Treatment3", "2. ", $treatment_Option3_Q3a);
        $this->form->addElement("select", "Tic_Q3a_Treatment4", "3. ", $treatment_Option4_Q3a);
        $this->form->addElement("select", "Tic_Q3a_Treatment5", "4. ", $treatment_Option5_Q3a);
        $this->form->addElement("select", "Tic_Q3a_Treatment6", "9. ", $treatment_Option6_Q3a);
        $this->form->addElement("textarea", "Tic_Q3aDescription", "Please describe:");
       
        $this->form->addElement("text", "Tic_Q3b_OnsetAge", "3.b) Age of onset (years - numbers only!)");
        $this->form->addElement("advcheckbox", "Tic_Q3bNA", "NA");
        $this->form->addElement("text", "Tic_Q3c_Episodes", "3.c) Number of episodes (numbers only!)");
        $this->form->addElement("advcheckbox", "Tic_Q3cNA", "NA");
        $this->form->addElement("text", "Tic_Q3d_Duration", "3.d) Duration of longest episode in weeks (numbers only!)");
        $this->form->addElement("advcheckbox", "Tic_Q3dNA", "NA");
        $this->form->addElement("select", "Tic_Q3e_Impairment", " 3.e) Rate and code impairment or incapacitation:", $question3e_Options);
        $this->form->addElement("select", "Tic_Q3f_Reliability", "3.f) Interviewer judgment on reliability of this information:", $question3f_Options);
        
        // Rules for questions
        $this->form->addRule("Tic_Q1","Required",'required', null);
        $this->form->addRule("Tic_Q1a","Required",'required', null);
        $this->form->addRule("Tic_Q1b","Required",'required', null);
        $this->form->addRule("Tic_Q1c","Required",'required', null);
        $this->form->addRule("Tic_Q1d","Required",'required', null);
        $this->form->addRule("Tic_Q2","Required",'required', null);
        $this->form->addRule("Tic_Q2a","Required",'required', null);
        $this->form->addRule("Tic_Q2b","Required",'required', null);
        $this->form->addRule("Tic_Q2c","Required",'required', null);
        $this->form->addRule("Tic_Q2d","Required",'required', null);
        $this->form->addRule("Tic_Q3a_Treatment1", "Required", 'required', null);
        $this->form->addRule("Tic_Q3a_Treatment2", "Required", 'required', null);
        $this->form->addRule("Tic_Q3a_Treatment3", "Required", 'required', null);
        $this->form->addRule("Tic_Q3a_Treatment4", "Required", 'required', null);
        $this->form->addRule("Tic_Q3a_Treatment5", "Required", 'required', null);
        $this->form->addRule("Tic_Q3a_Treatment6", "Required", 'required', null);
        $this->form->addRule(array('Tic_Q3b_OnsetAge', 'Tic_Q3bNA'), 'Age of onset is required if available', 'requiredIf', array('operator'=>'!=', 'value'=>'1'));
        $this->setRequired('Tic_Q3b_OnsetAge');
        $this->form->addRule(array('Tic_Q3c_Episodes', 'Tic_Q3cNA'), 'Number of Episodes is required if available', 'requiredIf', array('operator'=>'!=', 'value'=>'1'));
        $this->setRequired('Tic_Q3c_Episodes');
        $this->form->addRule(array('Tic_Q3d_Duration', 'Tic_Q3dNA'), 'Duration of Episode is required if available', 'requiredIf', array('operator'=>'!=', 'value'=>'1'));
        $this->setRequired('Tic_Q3d_Duration');
        $this->form->addRule("Tic_Q3e_Impairment","Required",'required', null);
        $this->form->addRule("Tic_Q3f_Reliability","Required",'required', null);
        
    } // End Function
    
    function _setupFigsRelativesOCD()  // Obsessive Compulsive Disorder Checklist
    {
        // Display test name
        $this->form->addElement('header', null, "Obsessive Compulsive Disorder Checklist");
        
        // Create option set
        $questionOptions = array(null=>'', '0' => '0. No', '1' => '1. Yes', '9'=>'9. Unk', 'NA' => 'N/A');
        $treatment_Option1_Q4a = array(null=>'', '0' => '0. None', 'NA' => 'N/A');
        $treatment_Option2_Q4a = array(null=>'', '1' => '1. Inpatient', 'NA' => 'N/A');
        $treatment_Option3_Q4a = array(null=>'', '2' => '2. Outpatient', 'NA' => 'N/A');
        $treatment_Option4_Q4a = array(null=>'', '3' => '3. ECT', 'NA' => 'N/A');
        $treatment_Option5_Q4a = array(null=>'', '4' => '4. Medication', 'NA' => 'N/A');
        $treatment_Option6_Q4a = array(null=>'', '9' => '9. Unknown', 'NA' => 'N/A');
        $question4e_Options = array(null=>'', '0' => '0. None', '1' => '1. Impaired', '2'=>'2. Incapacitation', '3'=>'3. Clinically Significant Distress', '9'=>'9. Unknown', 'NA' => 'N/A');
        $question4f_Options = array(null=>'', '1' => '1. Good', '2'=>'2. Fair', '3'=>'3. Poor', 'NA' => 'N/A');
        
        // OCD_Question 1
        $this->form->addElement("static", null, "1. Obsessions...");
        $this->form->addElement("select", "OCD_Q1a", "1.a) Does/did he/she have strange thoughts or ideas that got stuck in his/her mind? (Recurrent and persistent thoughts, images or impulse that are intrusive and distressing.)", $questionOptions);
        $this->form->addElement("select", "OCD_Q1b", "1.b) Were the thoughts, images or impulses NOT just excessive worries about real life problems?", $questionOptions);
        $this->form->addElement("select", "OCD_Q1c", "1.c) Does or did he/she try to ignore or suppress the obsessions?", $questionOptions);
        $this->form->addElement("select", "OCD_Q1d", "1.d) Does or did he/she recognize that the obsessions were excessive or unreasonable?", $questionOptions);
        
        // OCD_Question 2
        $this->form->addElement("static", null, "2. Compulsions...");
        $this->form->addElement("select", "OCD_Q2a", "2.a) Does or did he/she have problems with compulsions or repetitive behaviors such as hand washing, checking or repetitive mental acts (counting, repeating words, praying)?", $questionOptions);
        $this->form->addElement("select", "OCD_Q2b", "2.b) Does or did the compulsions help prevent or reduce distress or were the compulsions thought to prevent a dreaded event in an unrealistic way?", $questionOptions);
        
        // OCD_Question 3
        $this->form->addElement("select", "OCD_Q3a", "3.a) Did the obsessions (compulsions or both) interfere (cause marked distress or impairment) at school, work, or with social relationships?", $questionOptions);
        $this->form->addElement("text", "OCD_Q3b_Duration", "3.b) How much time did the (obsessions, compulsions, or both) take in a day (hours)?");
        $this->form->addElement("advcheckbox", "OCD_Q3bNA", "NA"); // Checkbox
        
        // OCD_Question 4
        $this->form->addElement("static", null, "4.a) Code and describe professional treatment:");
        $this->form->addElement("select", "OCD_Q4a_Treatment1", "0. ", $treatment_Option1_Q4a);
        $this->form->addElement("select", "OCD_Q4a_Treatment2", "1. ", $treatment_Option2_Q4a);
        $this->form->addElement("select", "OCD_Q4a_Treatment3", "2. ", $treatment_Option3_Q4a);
        $this->form->addElement("select", "OCD_Q4a_Treatment4", "3. ", $treatment_Option4_Q4a);
        $this->form->addElement("select", "OCD_Q4a_Treatment5", "4. ", $treatment_Option5_Q4a);
        $this->form->addElement("select", "OCD_Q4a_Treatment6", "9. ", $treatment_Option6_Q4a);
        $this->form->addElement("textarea", "OCD_Q4aDescription", "Please describe:");
        
        $this->form->addElement("text", "OCD_Q4b_OnsetAge", "4.b)	Age of onset (years - numbers only!)");
        $this->form->addElement("advcheckbox", "OCD_Q4bNA", "NA"); // Checkbox
        $this->form->addElement("text", "OCD_Q4c_Episodes", "4.c)	Number of episodes (numbers only!)");
        $this->form->addElement("advcheckbox", "OCD_Q4cNA", "NA"); // Checkbox
        $this->form->addElement("text", "OCD_Q4d_Duration", "4.d)	Duration of longest episode in weeks (numbers only!)");
        $this->form->addElement("advcheckbox", "OCD_Q4dNA", "NA"); // Checkbox
        $this->form->addElement("select", "OCD_Q4e_Impairment", " 4.e) Rate and code impairment or incapacitation:", $question4e_Options);
        $this->form->addElement("select", "OCD_Q4f_Reliability", "4.f) Interviewer judgment on reliability of this information:", $question4f_Options);
        
        // Rules for questions
        $this->form->addRule("OCD_Q1a","Required",'required', null);
        $this->form->addRule("OCD_Q1b","Required",'required', null);
        $this->form->addRule("OCD_Q1c","Required",'required', null);
        $this->form->addRule("OCD_Q1d","Required",'required', null);
        $this->form->addRule("OCD_Q2a","Required",'required', null);
        $this->form->addRule("OCD_Q2b","Required",'required', null);
        $this->form->addRule("OCD_Q3a","Required",'required', null);
        $this->form->addRule(array('OCD_Q3b_Duration', 'OCD_Q3bNA'), 'Time of Obsession is required if available', 'requiredIf', array('operator'=>'!=', 'value'=>'1'));
        $this->setRequired('OCD_Q3b_Duration');
        $this->form->addRule("OCD_Q4a_Treatment1", "Required", 'required', null);
        $this->form->addRule("OCD_Q4a_Treatment2", "Required", 'required', null);
        $this->form->addRule("OCD_Q4a_Treatment3", "Required", 'required', null);
        $this->form->addRule("OCD_Q4a_Treatment4", "Required", 'required', null);
        $this->form->addRule("OCD_Q4a_Treatment5", "Required", 'required', null);
        $this->form->addRule("OCD_Q4a_Treatment6", "Required", 'required', null);
        $this->form->addRule(array('OCD_Q4b_OnsetAge', 'OCD_Q4bNA'), 'Age of onset is required if available', 'requiredIf', array('operator'=>'!=', 'value'=>'1'));
        $this->setRequired('OCD_Q4b_OnsetAge');
        $this->form->addRule(array('OCD_Q4c_Episodes', 'OCD_Q4cNA'), 'Number of Episodes is required if available', 'requiredIf', array('operator'=>'!=', 'value'=>'1'));
        $this->setRequired('OCD_Q4c_Episodes');
        $this->form->addRule(array('OCD_Q4d_Duration', 'OCD_Q4dNA'), 'Duration of Episode is required if available', 'requiredIf', array('operator'=>'!=', 'value'=>'1'));
        $this->setRequired('OCD_Q4d_Duration');
        $this->form->addRule("OCD_Q4e_Impairment","Required",'required', null);
        $this->form->addRule("OCD_Q4f_Reliability","Required",'required', null);
        
    } // End Function
    
    function _setupFigsRelativesADHD()  // Attention Deficit/Hyperactivity Disorder Checklist
    {
        // Display test name
        $this->form->addElement('header', null, "Attention Deficit/Hyperactivity Disorder Checklist");
        
        // Create option set
        $questionOptions = array(null=>'', '0' => '0. No', '1' => '1. Yes', '9'=>'9. Unk', 'NA' => 'N/A');
        $question2l_Options = array(null=>'', 'Yes' => 'Yes', 'No' => 'No', 'Unsure'=>'Unsure', 'NA' => 'N/A');
        $treatment_Option1_Q3a = array(null=>'', '0' => '0. None', 'NA' => 'N/A');
        $treatment_Option2_Q3a = array(null=>'', '1' => '1. Inpatient', 'NA' => 'N/A');
        $treatment_Option3_Q3a = array(null=>'', '2' => '2. Outpatient', 'NA' => 'N/A');
        $treatment_Option4_Q3a = array(null=>'', '4' => '4. Medication', 'NA' => 'N/A');
        $treatment_Option5_Q3a = array(null=>'', '9' => '9. Unknown', 'NA' => 'N/A');
        $question3f_Options = array(null=>'', '0' => '0. None', '1' => '1. Impaired', '2'=>'2. Incapacitation', '9'=>'9. Unknown', 'NA' => 'N/A');
        $question3g_Options = array(null=>'', '1' => '1. Good', '2'=>'2. Fair', '3'=>'3. Poor', 'NA' => 'N/A');
        
        // ADHD Question 1
        $this->form->addElement("static", null, "When in elementary school did he/she...");
        $this->form->addElement("static", null, "1. Have problems with attention such as:");
        $this->form->addElement("select", "ADHD_Q1a", "1.a) ...making careless mistakes in school?", $questionOptions);
        $this->form->addElement("select", "ADHD_Q1b", "1.b) ...having difficulty sustaining attention?", $questionOptions);
        $this->form->addElement("select", "ADHD_Q1c", "1.c) ...not seeming to listen?", $questionOptions);
        $this->form->addElement("select", "ADHD_Q1d", "1.d) ...failing to finish tasks or not following through?", $questionOptions);
        $this->form->addElement("select", "ADHD_Q1e", "1.e) ...having difficulty organizing tasks?", $questionOptions);
        $this->form->addElement("select", "ADHD_Q1f", "1.f) ...avoiding tasks that required sustained mental effort?", $questionOptions);
        $this->form->addElement("select", "ADHD_Q1g", "1.g) ...often losing necessary things?", $questionOptions);
        $this->form->addElement("select", "ADHD_Q1h", "1.h) ...often being easily distracted?", $questionOptions);
        $this->form->addElement("select", "ADHD_Q1i", "1.i) ...often being forgetful in daily activities?", $questionOptions);
        $this->form->addElement("select", "ADHD_Q1j", "1.j) ...did these problems start before age 7 years?", $questionOptions);
        $this->form->addElement("select", "ADHD_Q1k1", "1.k) ...did these problems start in grade school?", $questionOptions);
        $this->form->addElement("text", "ADHD_Q1k2_Grade", "What grade did they start?");
        $this->form->addElement("advcheckbox", "ADHD_Q1k2NA", "NA");
        $this->form->addElement("select", "ADHD_Q1l1", "1.li) ...did these problems cause impairment at school?", $questionOptions);
        $this->form->addElement("select", "ADHD_Q1l2", "1.lii) ...did these problems cause impairment at home?", $questionOptions);
        $this->form->addElement("select", "ADHD_Q1l3", "1.liii) ...did these problems cause impairment with peers?", $questionOptions);
        
        // ADHD_Question 2
        $this->form->addElement("static", null, "When in elementary school did he/she...");
        $this->form->addElement("static", null, "1. Have problems with hyperactivity or impulsivity such as:");
        $this->form->addElement("select", "ADHD_Q2a", "2.a) ...often fidgeting or squirming in seat?", $questionOptions);
        $this->form->addElement("select", "ADHD_Q2b", "2.b) ...often leaving his/her seat in classroom?", $questionOptions);
        $this->form->addElement("select", "ADHD_Q2c", "2.c) ...often running or climbing excessively?", $questionOptions);
        $this->form->addElement("select", "ADHD_Q2d", "2.d) ...often having difficulty playing quietly?", $questionOptions);
        $this->form->addElement("select", "ADHD_Q2e", "2.e) ...often being 'on the go' or acting as if 'driven by a motor'?", $questionOptions);
        $this->form->addElement("select", "ADHD_Q2f", "2.f) ...often talking excessively?", $questionOptions);
        $this->form->addElement("select", "ADHD_Q2g", "2.g) ...often blurting out answers before questions were completed?", $questionOptions);
        $this->form->addElement("select", "ADHD_Q2h", "2.h) ...often had difficulty waiting his/her turn?", $questionOptions);
        $this->form->addElement("select", "ADHD_Q2i", "2.i) ...often interrupting or intruding on others?", $questionOptions);
        $this->form->addElement("select", "ADHD_Q2j", "2.j) ...did these problems start before age 7 years?", $questionOptions);
        $this->form->addElement("select", "ADHD_Q2k1", "2.ki) ...did these problems cause impairment at school?", $questionOptions);
        $this->form->addElement("select", "ADHD_Q2k2", "2.kii) ...did these problems cause impairment at home?", $questionOptions);
        $this->form->addElement("select", "ADHD_Q2k3", "2.kiii) ...did these problems cause impairment with peers?", $questionOptions);
        $this->form->addElement("select", "ADHD_Q2l", "2.l) ...did these problems begin in elementary school?", $question2l_Options);
        
        // ADHD_Question 3
        $this->form->addElement("static", null, "3.a) Code and describe professional treatment:");
        $this->form->addElement("select", "ADHD_Q3a_Treatment1", "0. ", $treatment_Option1_Q3a);
        $this->form->addElement("select", "ADHD_Q3a_Treatment2", "1. ", $treatment_Option2_Q3a);
        $this->form->addElement("select", "ADHD_Q3a_Treatment3", "2. ", $treatment_Option3_Q3a);
        $this->form->addElement("select", "ADHD_Q3a_Treatment4", "4. ", $treatment_Option4_Q3a);
        $this->form->addElement("select", "ADHD_Q3a_Treatment5", "9. ", $treatment_Option5_Q3a);
        $this->form->addElement("textarea", "ADHD_Q3aDescription", "Please describe:");
     
        $this->form->addElement("text", "ADHD_Q3b_OnsetAge", "3.b) Age of onset (years - numbers only!)");
        $this->form->addElement("advcheckbox", "ADHD_Q3bNA", "NA");
        $this->form->addElement("static", null, "3.c) Omitted");
        $this->form->addElement("static", null, "3.d) Omitted");
        $this->form->addElement("select", "ADHD_Q3e_Current", "3.e) Currently still a problem?", $questionOptions);
        $this->form->addElement("select", "ADHD_Q3f_Impairment", " 3.f) Rate and code impairment or incapacitation:", $question3f_Options);
        $this->form->addElement("select", "ADHD_Q3g_Reliability", "3.g) Interviewer judgment on reliability of this information:", $question3g_Options);
        
        // Rules for questions
        $this->form->addRule("ADHD_Q1a","Required",'required', null);
        $this->form->addRule("ADHD_Q1b","Required",'required', null);
        $this->form->addRule("ADHD_Q1c","Required",'required', null);
        $this->form->addRule("ADHD_Q1d","Required",'required', null);
        $this->form->addRule("ADHD_Q1e","Required",'required', null);
        $this->form->addRule("ADHD_Q1f","Required",'required', null);
        $this->form->addRule("ADHD_Q1g","Required",'required', null);
        $this->form->addRule("ADHD_Q1h","Required",'required', null);
        $this->form->addRule("ADHD_Q1i","Required",'required', null);
        $this->form->addRule("ADHD_Q1j","Required",'required', null);
        $this->form->addRule("ADHD_Q1k1","Required",'required', null);
        $this->form->addRule("ADHD_Q1k2","Required",'required', null);
        $this->form->addRule("ADHD_Q1l1","Required",'required', null);
        $this->form->addRule("ADHD_Q1l2","Required",'required', null);
        $this->form->addRule("ADHD_Q1l3","Required",'required', null);
        $this->form->addRule("ADHD_Q2a","Required",'required', null);
        $this->form->addRule("ADHD_Q2b","Required",'required', null);
        $this->form->addRule("ADHD_Q2c","Required",'required', null);
        $this->form->addRule("ADHD_Q2d","Required",'required', null);
        $this->form->addRule("ADHD_Q2e","Required",'required', null);
        $this->form->addRule("ADHD_Q2f","Required",'required', null);
        $this->form->addRule("ADHD_Q2g","Required",'required', null);
        $this->form->addRule("ADHD_Q2i","Required",'required', null);
        $this->form->addRule("ADHD_Q2j","Required",'required', null);
        $this->form->addRule("ADHD_Q2k1","Required",'required', null);
        $this->form->addRule("ADHD_Q2k2","Required",'required', null);
        $this->form->addRule("ADHD_Q2k3","Required",'required', null);
        $this->form->addRule("ADHD_Q2l","Required",'required', null);
        $this->form->addRule("ADHD_Q3a_Treatment1", "Required", 'required', null);
        $this->form->addRule("ADHD_Q3a_Treatment2", "Required", 'required', null);
        $this->form->addRule("ADHD_Q3a_Treatment3", "Required", 'required', null);
        $this->form->addRule("ADHD_Q3a_Treatment4", "Required", 'required', null);
        $this->form->addRule("ADHD_Q3a_Treatment5", "Required", 'required', null);
        $this->form->addRule(array('ADHD_Q3b_OnsetAge', 'ADHD_Q3bNA'), 'Age of onset is required if available', 'requiredIf', array('operator'=>'!=', 'value'=>'1'));
        $this->setRequired('ADHD_Q3b_OnsetAge');
        $this->form->addRule("ADHD_Q3c_Episodes","Required",'required', null);
        $this->form->addRule("ADHD_Q3d_Duration","Required",'required', null);
        $this->form->addRule("ADHD_Q3e_Current","Required",'required', null);
        $this->form->addRule("ADHD_Q3f_Impairment","Required",'required', null);
        $this->form->addRule("ADHD_Q3g_Reliability","Required",'required', null);
        
    } // End Function
    
    function _getRelatives()
    {
        $db =& Database::singleton();
        
        $results = array();
        $db->select("SELECT RelativeID, RelativeCode FROM figs_year3_relatives WHERE CommentID='".$this->getCommentID()."'", $results);
        
        $relatives = array();
        foreach($results AS $row) {
            $relatives[$row['RelativeID']] = $row['RelativeCode'];
        }
        return $relatives;
    }

    function _setDataEntryCompletedRelative($relativeID)
    {
        if(empty($relativeID)) return false;

        $db =& Database::singleton();

        $query = "SELECT
                     (GS_Q01_Adopted is not null) AND
                     (Checklist_Other='N' OR Other_Q1_Disorder is not null) AND
                     (Checklist_ADHD='N' OR ADHD_Q1a is not null) AND
                     (Checklist_Depression='N' OR Depression_Q1a is not null) AND
                     (Checklist_Mania='N' OR Mania_Q1a is not null) AND
                     (Checklist_Psychosis='N' OR Psychosis_Q1a is not null) AND
                     (Checklist_Alcohol='N' OR Alcohol_Q1a is not null) AND
                     (Checklist_Drugs='N' OR Alcohol_Q7a is not null) AND    
                     (Checklist_Nicotine='N' OR Alcohol_Q13a_Daily is not null) AND
                     (Checklist_OCD='N' OR OCD_Q1a is not null) AND
                     (Checklist_Tic='N' OR Tic_Q1 is not null) AND
                     (Checklist_ASP='N' OR ASP_Q1a is not null) AND
                     (Checklist_Schizoid='N' OR Schizoid_Q1a is not null) AS Complete
                  FROM figs_year3_relatives WHERE RelativeID='$relativeID'";

        $complete = $db->selectOne($query);

        $ok = $db->update('figs_year3_relatives', array('DataEntryCompleted'=>$complete), array('RelativeID'=>$relativeID));

        return true;
    }

    function _determineDataEntryCompletionStatus()
    {
        $db =& Database::singleton();

        $relatives = $this->_getRelatives();
        if(!is_array($relatives) || count($relatives)==0) {
            return 'Incomplete';
        }
        
        $query = "SELECT count(*) FROM figs_year3_relatives WHERE CommentID='".$this->getCommentID()."' AND DataEntryCompleted=0";
        
        $incompleteRelatives = $db->selectOne($query);
        
        if($incompleteRelatives > 0) {
            return 'Incomplete';
        } else {
            return 'Complete';
        }

    } // End function
    
    /**
    * sets the data entry completion status
    * @params string   $status     the status - either 'Complete' or 'Incomplete'
    * @access private
    * @return void
    */
    function _setDataEntryCompletionStatus($status)
    {
        if(!in_array($status, array('Complete', 'Incomplete'))) throw new LorisException("Invalid status passed to _setDataEntryCompletionStatus - '$status' should have been either 'Complete' or 'Incomplete'<br>\n");

        $db =& Database::singleton();

        $success = $db->update('figs_year3',
        array('Data_entry_completion_status'=>$status),
        array('CommentID'=>$this->getCommentID())
        );

    } // end function

    /**
    * gets the data entry completion status
    * @return string   either 'Complete' or 'Incomplete'
    * @access public
    */
    function getDataEntryCompletionStatus()
    {
        $db =& Database::singleton();

        $query = "SELECT Data_entry_completion_status FROM figs_year3 WHERE CommentID='".$this->getCommentID()."'";
        return $db->selectOne($query);
    }

    /**
     * computes diagnoses of FIGS-MRI of May 16, 2002 according to
     * algorithms revised July 2, 2002.
     */

    function score()
    {
        $db =& Database::singleton();

        // null the existing scores
        $success = $this->_nullScores();

        $param = array('cID'=>$this->getCommentID());
        $query = "SELECT RelativeID FROM figs_year3_relatives WHERE CommentID=:cID";
        $relatives = $db->pselect($query,$param );
        if(is_array($relatives) && count($relatives)) {
            $relativeScores = array();
            foreach($relatives AS $relativeID) {
                $success = $this->_scoreRelative($relativeID['RelativeID']);
                $relativeScores = array_merge($relativeScores, $success);
            }
        }
        // GET per-instrument scores
        // from per-relative scores...
        $query_adhd='';
        if(array_key_exists('Score_adhd_combined',$relativeScores) || 
            array_key_exists('Score_adhd_inattentive',$relativeScores)|| 
            array_key_exists('Score_adhd_hyperactive',$relativeScores) ) {

            if($relativeScores['Score_adhd_combined'] != NULL || $relativeScores['Score_adhd_inattentive'] != NULL ||
               $relativeScores['Score_adhd_hyperactive'] != NULL){
            $query_adhd = "IF(((MAX(Score_adhd_combined)='Y' OR MAX(Score_adhd_inattentive)='Y'OR MAX(Score_adhd_hyperactive)='Y')), 'Y','N') AS ADHD";
            }
        }
        $query_alcohol_abuse ='';
        if(array_key_exists('Score_alcohol_abuse', $relativeScores) || 
           array_key_exists('Score_alcohol_dependence',$relativeScores)) {
           if($relativeScores['Score_alcohol_abuse'] != NULL || $relativeScores['Score_alcohol_dependence'] != NULL){
            $query_alcohol_abuse = "IF(((MAX(Score_alcohol_abuse)='Y' OR MAX(Score_alcohol_dependence)='Y')), 'Y', 'N') AS Alcohol";
           }
        }
        $query_alcohol_nicotine ='';
        if(array_key_exists('Score_alcohol_nicotine', $relativeScores) && $relativeScores['Score_alcohol_nicotine'] != NULL){
            $query_alcohol_nicotine =" IF(MAX(Score_alcohol_nicotine)='Y', 'Y', 'N') AS Nicotine";
        }
        $query_alcohol_drug_substance='';
        if(array_key_exists('Score_alcohol_drug_substance', $relativeScores) && 
            $relativeScores['Score_alcohol_drug_substance'] != NULL){
            $query_alcohol_drug_substance= " IF(MAX(Score_alcohol_drug_substance)='Y', 'Y', 'N') AS Drug_substance";
        }
        $query_asp='';
        if(array_key_exists('Score_asp', $relativeScores) && $relativeScores['Score_asp'] != NULL){
            $query_asp= " IF(MAX(Score_asp)='Y', 'Y', 'N') AS ASP";
        }
        $query_depression='';
        if(array_key_exists('Score_depression',$relativeScores) || 
            array_key_exists('Score_chronic_depression',$relativeScores) ||
            array_key_exists('Score_recurrent_depression', $relativeScores)) {
           if($relativeScores['Score_depression']!= NULL || $relativeScores['Score_chronic_depression'] != NULL || 
               $relativeScores['Score_recurrent_depression'] != NULL){
               $query_depression = " IF(((MAX(Score_depression)='Y' OR MAX(Score_chronic_depression)='Y' OR MAX(Score_recurrent_depression)='Y')), 'Y', 'N') AS Depression";
           } 
        }
        $query_mania='';
        if( array_key_exists('Score_mania', $relativeScores) && $relativeScores['Score_mania'] != NULL){
            $query_mania=" IF((MAX(Score_mania)='Y'), 'Y', 'N') AS Mania";
        }
        $query_ocd='';
        if(array_key_exists('Score_ocd', $relativeScores) && $relativeScores['Score_ocd'] != NULL){
            $query_ocd =" IF(MAX(Score_ocd)='Y', 'Y', 'N') AS OCD";
        }
        $query_paranoid_personality='';
        if( array_key_exists('Score_paranoid_personality', $relativeScores) || 
            array_key_exists('Score_pervasive_development', $relativeScores) || 
            array_key_exists('Score_schizoid', $relativeScores) || array_key_exists('Score_schizotypal', $relativeScores)) {
           if($relativeScores['Score_paranoid_personality'] != NULL || $relativeScores['Score_pervasive_development'] != NULL || $relativeScores['Score_schizoid'] != NULL || $relativeScores['Score_schizotypal'] != NULL){
       $query_paranoid_personality =" IF(((MAX(Score_paranoid_personality)='Y' OR MAX(Score_pervasive_development)='Y' OR MAX(Score_schizoid)='Y' OR MAX(Score_schizotypal)='Y')), 'Y', 'N') AS Paranoid";
            
           }
        }
        $query_psychosis_schizophrenia='';
        if(array_key_exists('Score_phychosis_schizophrenia', $relativeScores) || 
            array_key_exists('Score_phychosis_depression', $relativeScores) || 
            array_key_exists('Score_phychosis_mania', $relativeScores)) {
            
            if($relativeScores['Score_psychosis_schizophrenia'] != NULL || $relativeScores['Score_psychosis_depression'] != NULL || $relativeScores['Score_psychosis_mania'] != NULL){
             $query_psychosis_schizophrenia=" IF(((MAX(Score_psychosis_schizophrenia)='Y' OR MAX(Score_psychosis_depression)='Y' OR MAX(Score_psychosis_mania)='Y')),'Y', 'N') AS Psychosis";
            } 
        }
        $query_tic_tourettes='';
        if(array_key_exists('Score_tic_tourettes', $relativeScores) || 
            array_key_exists('Score_tic_motor_c', $relativeScores) || 
            array_key_exists('Score_tic_vocal_c', $relativeScores) ) {
           
           if($relativeScores['Score_tic_tourettes'] != NULL || $relativeScores['Score_tic_motor_c'] != NULL || $relativeScores['Score_tic_vocal_c'] != NULL || $relativeScores['Score_tic_motor_t'] != NULL || $relativeScores['Score_tic_vocal_t'] != NULL){
             $query_tic_tourettes=" IF(((MAX(Score_tic_tourettes)='Y' OR MAX(Score_tic_motor_c)='Y' OR MAX(Score_tic_vocal_c)='Y' OR MAX(Score_tic_motor_t)='Y' OR MAX(Score_tic_vocal_t)='Y')), 'Y', 'N') AS Tic";
            }
        }
        $query_array = array($query_adhd, $query_alcohol_abuse, $query_alcohol_nicotine,$query_alcohol_drug_substance,$query_asp, $query_depression,$query_mania,$query_ocd, $query_paranoid_personality,$query_psychosis_schizophrenia, $query_tic_tourettes);
        $final_query='';
        foreach($query_array as $key=>$val){
            if(!empty($val) && $key > 0 && $final_query != ''){
              $final_query .= ",";
            }
            $final_query .= $val;
        }
        $scores = NULL;
        if(!empty($final_query)){
            $query = "SELECT $final_query FROM figs_year3_relatives WHERE CommentID=:cID";

            $scores = $db->pselectRow($query, $param);

            $success = $db->update('figs_year3', $scores, array('CommentID'=>$this->getCommentID()));
        }
        // return an array w/ all scores
        return array('instrument'=>$scores, 'relatives'=>$relativeScores);
    }
    
    /**
     * score all checklists for a relative
     * @params string   $status     the status - either 'Complete' or 'Incomplete'
     */
    function _scoreRelative($relativeID)
    {
        $db =& Database::singleton();

        $query = "SELECT Checklist_Other, Checklist_ADHD, Checklist_Depression, Checklist_Mania, Checklist_Psychosis, Checklist_Alcohol, Checklist_Drugs, Checklist_Nicotine, Checklist_OCD, Checklist_Tic, Checklist_ASP, Checklist_Schizoid FROM figs_year3_relatives WHERE RelativeID='$relativeID'";
        $checklists=array();
        $db->selectRow($query, $checklists);
        
        // return error in case 0 rows returned, i.e. no record for the RecordID in the relatives table
        if (count($checklists)==0) {
            throw new LorisException("Error, no data returned!");
        }

        $scores=array();
        foreach($checklists AS $checklist=>$administered) {
            if($administered == 'Y') {
                $checklistName = substr($checklist, strpos($checklist, '_')+1);
                $scoringFunction = "_scoreRelative".$checklistName;
                if(method_exists($this, $scoringFunction)) {
                    $success = $this->$scoringFunction($relativeID);
                    $scores = array_merge($scores, $success);
                }
            }
        }
        return $scores;
    }

    /**
     * scores the depression checklist for a relative
     * @params int   $relativeID     the RelativeID from figs_year3_relatives
     */
    function _scoreRelativeDepression($relativeID)
    {
        $db =& Database::singleton();

        $scores['Score_depression'] = 'N';
        $scores['Score_recurrent_depression'] = 'N';
        $scores['Score_chronic_depression'] = 'N';

        $query = "SELECT 
Depression_Q1a,
Depression_Q1b,
Depression_Q1c,
Depression_Q1d,
Depression_Q1e,
Depression_Q1f,
Depression_Q1h,
Depression_Q1i,
Depression_Q1j,
Depression_Q1k,
Depression_Q2_Treatment2,
Depression_Q2_Treatment3,
Depression_Q2_Treatment4,
Depression_Q2_Treatment5,
Depression_Q4_Episodes,
Depression_Q5_Duration,
Depression_Q8_Impairment,
Depression_Q9_Reliability
 FROM figs_year3_relatives WHERE RelativeID='$relativeID'";
        $db->selectRow($query, $fields); 

        // Item 2 = yes to any of the following: 1,2,3,4 AND 9 = 1 or 2
        if(($fields['Depression_Q2_Treatment2'] == '1'
           || $fields['Depression_Q2_Treatment3'] == '2'
           || $fields['Depression_Q2_Treatment4'] == '3'
           || $fields['Depression_Q2_Treatment5'] == '4')
           && ($fields['Depression_Q9_Reliability'] == '1'
               || $fields['Depression_Q9_Reliability'] == '2'))
            $scores['Score_depression'] = 'Y';

        // yes to 1a or 1b 
        if(($fields['Depression_Q1a'] == '1'
            || $fields['Depression_Q1b'] == '1')

           // AND yes to >= 3 of 1c, 1d, (1f or 1g), 1h, 1i, 1j, 1k
           && (($fields['Depression_Q1c']  == '1')
               + ($fields['Depression_Q1d']  == '1')
               //+ ($fields['Depression_Q1e']  == '1')
               + (($fields['Depression_Q1f']  == '1') || ($fields['Depression_Q1g'] == '1'))
               + ($fields['Depression_Q1h']  == '1')
               + ($fields['Depression_Q1i']  == '1')
               + ($fields['Depression_Q1j']  == '1')
               + ($fields['Depression_Q1k'] == '1')) >= 3
           //AND yes to 1e or 8 in (1,2,3,4) 
           && ($fields['Depression_Q1e'] == '1'
               || $fields['Depression_Q8_Impairment'] == '1'
               || $fields['Depression_Q8_Impairment'] == '2'
               || $fields['Depression_Q8_Impairment'] == '3'
               || $fields['Depression_Q8_Impairment'] == '4')
           //AND 5 >= 2 weeks
           && ($fields['Depression_Q5_Duration'] >= 2)
           // AND 9 IN (1,2)
           && ($fields['Depression_Q9_Reliability'] == '1'
               || $fields['Depression_Q9_Reliability'] == '2')
           )
            $scores['Score_depression'] = 'Y';

        // score for recurrent depression
        if($scores['Score_depression'] == 'Y') {
            if($fields['Depression_Q4_Episodes'] >= 2)
                $scores['Score_recurrent_depression'] = 'Y';
        }

        // score for chronic depression
        if($scores['Score_depression'] == 'Y') {
            if($fields['Depression_Q5_Duration'] >= 104)
                $scores['Score_chronic_depression'] = 'Y';
        }

        // update database with score
        $success = $db->update('figs_year3_relatives', $scores, array('RelativeID'=>$relativeID));

        return $scores;
    }
    
    /**
     * scores the mania checklist for a relative
     * @params int   $relativeID     the RelativeID from figs_year3_relatives
     */
    function _scoreRelativeMania($relativeID)
    {
        $db =& Database::singleton();

        $scores['Score_mania'] = 'N';

        $query = "SELECT 
Mania_Q1a,
Mania_Q1b,
Mania_Q1c,
Mania_Q1d,
Mania_Q1e,
Mania_Q1g,
Mania_Q1i,
Mania_Q1j,
Mania_Q1k,
Mania_Q1l,
Mania_Q2_Treatment2,
Mania_Q2_Treatment3,
Mania_Q2_Treatment4,
Mania_Q2_Treatment5,
Mania_Q7_Impairment,
Mania_Q8_Reliability
FROM figs_year3_relatives WHERE RelativeID='$relativeID'";
        $db->selectRow($query, $fields); 

        // item 2 = yes to any of (1, 2, 3, 4) AND 9 in (1,2)
        if(($fields['Mania_Q2_Treatment2'] == '1'
            || $fields['Mania_Q2_Treatment3'] == '2'
            || $fields['Mania_Q2_Treatment4'] == '3'
            || $fields['Mania_Q2_Treatment5'] == '4')
           && ($fields['Mania_Q8_Reliability'] == '1'
               || $fields['Mania_Q8_Reliability'] == '2'))
            $scores['Score_mania'] = 'Y';
           
        // yes to 1a
        if(($fields['Mania_Q1a'] == '1')
           // AND yes to >= 2 of (1b or 1h), 1d, 1e, 1g, 1i, 1j, 1k, 1l
           && ((($fields['Mania_Q1b']  == '1') || ($fields['Mania_Q1h']  == '1'))
               + ($fields['Mania_Q1d']  == '1')
               + ($fields['Mania_Q1e']  == '1')
               + ($fields['Mania_Q1g']  == '1')
               + ($fields['Mania_Q1i']  == '1')
               + ($fields['Mania_Q1j']  == '1')
               + ($fields['Mania_Q1k']  == '1')
               + ($fields['Mania_Q1l']  == '1')) >= 2
           // AND item 7 in (1,2)
           && ($fields['Mania_Q7_Impairment'] == '1'
               || $fields['Mania_Q7_Impairment'] == '2')
           // AND item 8 in (1,2)
           && ($fields['Mania_Q8_Reliability'] == '1'
               || $fields['Mania_Q8_Reliability'] == '2')
           )
            $scores['Score_mania'] = 'Y';

          // yes to 1c
        if(($fields['Mania_Q1c'] == '1')
           // AND yes to >= 3 of (1b or 1h), 1d, 1e, 1g, 1i, 1j, 1k, 1l
           && ((($fields['Mania_Q1b']  == '1') || ($fields['Mania_Q1h']  == '1'))
               + ($fields['Mania_Q1d']  == '1')
               + ($fields['Mania_Q1e']  == '1')
               + ($fields['Mania_Q1g']  == '1')
               + ($fields['Mania_Q1i']  == '1')
               + ($fields['Mania_Q1j']  == '1')
               + ($fields['Mania_Q1k']  == '1')
               + ($fields['Mania_Q1l']  == '1')) >= 3
           // AND item 7 in (1,2)
           && ($fields['Mania_Q7_Impairment'] == '1'
               || $fields['Mania_Q7_Impairment'] == '2')
           // AND item 8 in (1,2)
           && ($fields['Mania_Q8_Reliability'] == '1'
               || $fields['Mania_Q8_Reliability'] == '2')
           )
            $scores['Score_mania'] = 'Y';
        
        // update database with score
        $success = $db->update('figs_year3_relatives', $scores, array('RelativeID'=>$relativeID));

        return $scores;
    }
  
    /**
     * scores the psychosis checklist for a relative
     * @params int   $relativeID     the RelativeID from figs_year3_relatives
     */
    function _scoreRelativePsychosis($relativeID)
    {
        $db =& Database::singleton();

        $scores['Score_psychosis_schizophrenia'] = 'N';
        $scores['Score_psychosis_depression'] = 'N';
        $scores['Score_psychosis_mania'] = 'N';

        $query = "SELECT 
Psychosis_Q11_Substance,
Psychosis_Q12_Reliability,
Psychosis_Q1a,
Psychosis_Q1b,
Psychosis_Q1c,
Psychosis_Q1d,
Psychosis_Q1e,
Psychosis_Q1f,
Psychosis_Q1g,
Psychosis_Q1h,
Psychosis_Q1i,
Psychosis_Q1j,
Psychosis_Q3_MoodDisturbance,
Psychosis_Q4_NoDepression,
Psychosis_Q5_Treatment2,
Psychosis_Q5_Treatment3,
Psychosis_Q5_Treatment4,
Psychosis_Q5_Treatment5,
Psychosis_Q8Weeks_Duration,
Psychosis_Q8Years_Duration,
Psychosis_Q10_Impairment,
Score_mania,
Score_recurrent_depression
 FROM figs_year3_relatives WHERE RelativeID='$relativeID'";
        $db->selectRow($query, $fields); 

        // PSYCHOTIC SCHIZOPHRENIA
        // OPTION 1
        // item 5 in (1,2,3,4)
        if(($fields['Psychosis_Q5_Treatment2'] == '1'
           || $fields['Psychosis_Q5_Treatment3'] == '2'
           || $fields['Psychosis_Q5_Treatment4'] == '3'
           || $fields['Psychosis_Q5_Treatment5'] == '4')
           // AND item 12 in (1,2)
           && ($fields['Psychosis_Q12_Reliability'] == '1'
               || $fields['Psychosis_Q12_Reliability'] == '2'))
            $scores['Score_psychosis_schizophrenia'] = 'Y';

        // OPTION 2
        // yes to >= 1 of 1a through 1j
        if(($fields['Psychosis_Q1a'] == '1'
            || $fields['Psychosis_Q1b'] == '1'
            || $fields['Psychosis_Q1c'] == '1'
            || $fields['Psychosis_Q1d'] == '1'
            || $fields['Psychosis_Q1e'] == '1'
            || $fields['Psychosis_Q1f'] == '1'
            || $fields['Psychosis_Q1g'] == '1'
            || $fields['Psychosis_Q1h'] == '1'
            || $fields['Psychosis_Q1i'] == '1'
            || $fields['Psychosis_Q1j'] == '1')
           // AND item 8 >= 6 months
           && ($fields['Psychosis_Q8Weeks_Duration'] >= 26
               || $fields['Psychosis_Q8Years_Duration'] >= 1)
           // AND item 10 in (1,2)
           && ($fields['Psychosis_Q10_Impairment'] == '1'
               || $fields['Psychosis_Q10_Impairment'] == '2')
           // AND item 11 = 0
           && ($fields['Psychosis_Q11_Substance'] == '0')
           // AND item 12 in (1,2)
           && ($fields['Psychosis_Q12_Reliability'] == '1'
               || $fields['Psychosis_Q12_Reliability'] == '2'))
            $scores['Score_psychosis_schizophrenia'] = 'Y';

        // PSYCHOTIC DEPRESSION
        // meets criteria for recurrent depression 
        if(($fields['Score_recurrent_depression'] == 'Y')
        // AND yes to >= 1 of 1a through 1g
           && ($fields['Psychosis_Q1a'] == '1'
               || $fields['Psychosis_Q1b'] == '1'
               || $fields['Psychosis_Q1c'] == '1'
               || $fields['Psychosis_Q1d'] == '1'
               || $fields['Psychosis_Q1e'] == '1'
               || $fields['Psychosis_Q1f'] == '1'
               || $fields['Psychosis_Q1g'] == '1')
        // AND 3 = yes
           && $fields['Psychosis_Q3_MoodDisturbance'] == '1'
        // AND 4 = no
           && $fields['Psychosis_Q4_NoDepression'] == '0')
            $scores['Score_psychosis_depression'] = 'Y';

        // PSYCHOTIC MANIA
        // meets criteria for mania
        if(($fields['Score_mania'] == 'Y')
        // AND yes to >= 1 of 1a through 1g
           && ($fields['Psychosis_Q1a'] == '1'
               || $fields['Psychosis_Q1b'] == '1'
               || $fields['Psychosis_Q1c'] == '1'
               || $fields['Psychosis_Q1d'] == '1'
               || $fields['Psychosis_Q1e'] == '1'
               || $fields['Psychosis_Q1f'] == '1'
               || $fields['Psychosis_Q1g'] == '1')
           // AND 3 = yes
           && $fields['Psychosis_Q3_MoodDisturbance'] == '1'
           // AND 4 = no
           && $fields['Psychosis_Q4_NoDepression'] == '0')
            $scores['Score_psychosis_mania'] = 'Y';
        
        // update database with score
        $success = $db->update('figs_year3_relatives', $scores, array('RelativeID'=>$relativeID));

        return $scores;
    }

    /**
     * scores the alcohol checklist for a relative
     * @params int   $relativeID     the RelativeID from figs_year3_relatives
     */
    function _scoreRelativeAlcohol($relativeID)
    {
        $db =& Database::singleton();

        $scores['Score_alcohol_abuse'] = 'N';
        $scores['Score_alcohol_dependence'] = 'N';
       
        $query = "SELECT 
Alcohol_Q1a,
Alcohol_Q1b,
Alcohol_Q1c,
Alcohol_Q1d,
Alcohol_Q1e,
Alcohol_Q1g,
Alcohol_Q1h,
Alcohol_Q1i,
Alcohol_Q1l,
Alcohol_Q1m,
Alcohol_Q2_Treatment2,
Alcohol_Q2_Treatment3,
Alcohol_Q2_Treatment4,
Alcohol_Q2_Treatment5,
Alcohol_Q5a_Reliability
FROM figs_year3_relatives WHERE RelativeID='$relativeID'";
        $db->selectRow($query, $fields); 

        // Alcohol dependence
        // OPTION 1
        
        // yes to 2 or more of the following (1a or 1j), 1b, (1c or
        // 1f), (1d or 1e or 1k), 1i, 1m
        if((($fields['Alcohol_Q1a'] == '1' || $fields['Alcohol_Q1j'] == '1')
            + ($fields['Alcohol_Q1b'] == '1')
            + ($fields['Alcohol_Q1c'] == '1' || $fields['Alcohol_Q1f'] == '1')
            + ($fields['Alcohol_Q1d'] == '1' || $fields['Alcohol_Q1e'] == '1' || $fields['Alcohol_Q1k'] == '1')
            + ($fields['Alcohol_Q1i'] == '1')
            + ($fields['Alcohol_Q1m'] == '1') >= 2)
           // AND 12 in (1,2)
           && ($fields['Alcohol_Q5a_Reliability'] == '1'
               || $fields['Alcohol_Q5a_Reliability'] == '2'))
            $scores['Score_alcohol_dependence'] = 'Y';


        // OPTION 2
        // 2 in (1,2,4)
        if(($fields['Alcohol_Q2_Treatment2'] == '1'
            || $fields['Alcohol_Q2_Treatment3'] == '2'
            || $fields['Alcohol_Q2_Treatment4'] == '3'
            || $fields['Alcohol_Q2_Treatment5'] == '4')
           // AND 5a in (1,2)
           && ($fields['Alcohol_Q5a_Reliability'] == '1'
               || $fields['Alcohol_Q5a_Reliability'] == '2'))
            $scores['Score_alcohol_dependence'] = 'Y';
        
        // Alcohol abuse
        // 1 or more of 1b, 1c, 1d, 1e, 1g, 1i, 1h, 1l
        if(($fields['Alcohol_Q1b'] == '1'
            || $fields['Alcohol_Q1c'] == '1'
            || $fields['Alcohol_Q1d'] == '1'
            || $fields['Alcohol_Q1e'] == '1'
            || $fields['Alcohol_Q1g'] == '1'
            || $fields['Alcohol_Q1i'] == '1'
            || $fields['Alcohol_Q1h'] == '1'
            || $fields['Alcohol_Q1l'] == '1')
           // AND 5a in (1,2)
           && ($fields['Alcohol_Q5a_Reliability'] == '1'
               || $fields['Alcohol_Q5a_Reliability'] == '2'))
            $scores['Score_alcohol_abuse'] = 'Y';
                
        // update database with score
        $success = $db->update('figs_year3_relatives', $scores, array('RelativeID'=>$relativeID));

        return $scores;
    }
 
    /**
     * scores the drug checklist for a relative
     * @params int   $relativeID     the RelativeID from figs_year3_relatives
     */
    function _scoreRelativeDrugs($relativeID)
    {
        $db =& Database::singleton();
       
        $scores['Score_alcohol_drug_substance'] = 'N';
        
        $query = "SELECT 
Alcohol_Q12_Reliability,
Alcohol_Q6_WhichDrugs,
Alcohol_Q7a,
Alcohol_Q7b,
Alcohol_Q7c,
Alcohol_Q7d,
Alcohol_Q7e,
Alcohol_Q7f,
Alcohol_Q8_Treatment2,
Alcohol_Q8_Treatment3,
Alcohol_Q8_Treatment4,
Alcohol_Q8_Treatment5
 FROM figs_year3_relatives WHERE RelativeID='$relativeID'";
        
        $db->selectRow($query, $fields); 
        
        // Drug Abuse
        // Q6 has 3 or more characters in it
        if((strlen($fields['Alcohol_Q6_WhichDrugs']) > 2)
           // AND 1 or more of 7a, 7b, 7c, 7d, 7e, 7f, (8 in (1,2,3,4))
           && ($fields['Alcohol_Q7a'] == '1'
               || $fields['Alcohol_Q7b'] == '1'
               || $fields['Alcohol_Q7c'] == '1'
               || $fields['Alcohol_Q7d'] == '1'
               || $fields['Alcohol_Q7e'] == '1'
               || $fields['Alcohol_Q7f'] == '1'
               || ($fields['Alcohol_Q8_Treatment2'] == '1'
                   || $fields['Alcohol_Q8_Treatment3'] == '2'
                   || $fields['Alcohol_Q8_Treatment4'] == '3'
                   || $fields['Alcohol_Q8_Treatment5'] == '4'))
           // AND 12 in (1,2)
           && ($fields['Alcohol_Q12_Reliability'] == '1'
               || $fields['Alcohol_Q12_Reliability'] == '2'))
            $scores['Score_alcohol_drug_substance'] = 'Y';
        
        // update database with score
        $success = $db->update('figs_year3_relatives', $scores, array('RelativeID'=>$relativeID));
        
        return $scores;
    }
    
    /**
     * scores the drug checklist for a relative
     * @params int   $relativeID     the RelativeID from figs_year3_relatives
     */
    function _scoreRelativeNicotine($relativeID)
    {
        $db =& Database::singleton();
        
        $scores['Score_alcohol_nicotine'] = 'N';
        
        $query = "SELECT 
Alcohol_Q13a_Daily,
Alcohol_Q14a,
Alcohol_Q14d,
Alcohol_Q19_Reliability
FROM figs_year3_relatives WHERE RelativeID='$relativeID'";
        
        $db->selectRow($query, $fields); 
        
        // nicotine dependence
        // 13a = 1
        if($fields['Alcohol_Q13a_Daily'] == '1'
           // AND >=1 of 14a, 14d
           && ($fields['Alcohol_Q14a'] == '1'
               || $fields['Alcohol_Q14d'] == '1')
           // AND 19 in (1,2)
           && ($fields['Alcohol_Q19_Reliability'] == '1'
               || $fields['Alcohol_Q19_Reliability'] == '2'))
            $scores['Score_alcohol_nicotine'] = 'Y';
        
        // update database with score
        $success = $db->update('figs_year3_relatives', $scores, array('RelativeID'=>$relativeID));
        
        return $scores;
    }
    
    function _scoreRelativeSchizoid($relativeID)
    {
        $db =& Database::singleton();
        
        $scores['Score_paranoid_personality'] = 'N';
        $scores['Score_pervasive_development'] = 'N';
        $scores['Score_schizoid'] = 'N';
        $scores['Score_schizotypal'] = 'N';

        $query = "SELECT 
Schizoid_Q1a,
Schizoid_Q1b,
Schizoid_Q1c,
Schizoid_Q1d,
Schizoid_Q1e,
Schizoid_Q1f,
Schizoid_Q1g,
Schizoid_Q2a,
Schizoid_Q2b,
Schizoid_Q2c,
Schizoid_Q2d,
Schizoid_Q2e,
Schizoid_Q2f,
Schizoid_Q2g,
Schizoid_Q2h,
Schizoid_Q2i,
Schizoid_Q2j,
Schizoid_Q2k,
Schizoid_Q3a,
Schizoid_Q3b,
Schizoid_Q3c,
Schizoid_Q3d,
Schizoid_Q3e,
Schizoid_Q3f,
Schizoid_Q3g,
Schizoid_Q4a_Treatment2,
Schizoid_Q4a_Treatment3,
Schizoid_Q4a_Treatment4,
Schizoid_Q4a_Treatment5,
Schizoid_Q4c_Impairment,
Schizoid_Q4d_SocialProbs,
Schizoid_Q4e_Unhappiness,
Schizoid_Q4f_Before17Yrs,
Schizoid_Q4g_Before3Yrs,
Schizoid_Q4h_Reliability
 FROM figs_year3_relatives WHERE RelativeID='$relativeID'";
        $db->selectRow($query, $fields); 

        // paranoid personality
        // OPTION 1
        // yes to >=3 of 1a, 1b, 1c, 1d, 1e, 1f, 1g
        if(((($fields['Schizoid_Q1a'] == '1')
             + ($fields['Schizoid_Q1b'] == '1')
             + ($fields['Schizoid_Q1c'] == '1')
             + ($fields['Schizoid_Q1d'] == '1')
             + ($fields['Schizoid_Q1e'] == '1')
             + ($fields['Schizoid_Q1f'] == '1')
             + ($fields['Schizoid_Q1g'] == '1')) >= 3)
           // AND 4c in (1,2) OR 4d=1 OR 4e=1
           && (($fields['Schizoid_Q4c_Impairment'] == '1'
                || $fields['Schizoid_Q4c_Impairment'] == '2')
               || ($fields['Schizoid_Q4d_SocialProbs'] == '1')
               || ($fields['Schizoid_Q4e_Unhappiness'] == '1'))
           // AND 4f=1
           && ($fields['Schizoid_Q4f_Before17Yrs'] == '1')
           // AND 4h in (1,2)
           && ($fields['Schizoid_Q4h_Reliability'] == '1'
               || $fields['Schizoid_Q4h_Reliability'] == '2'))
            $scores['Score_paranoid_personality'] = 'Y';
        
        // OPTION 2
        // yes to >=1 of 1a, 1b, 1c, 1d, 1e, 1f, 1g
        if(((($fields['Schizoid_Q1a'] == '1')
             + ($fields['Schizoid_Q1b'] == '1')
             + ($fields['Schizoid_Q1c'] == '1')
             + ($fields['Schizoid_Q1d'] == '1')
             + ($fields['Schizoid_Q1e'] == '1')
             + ($fields['Schizoid_Q1f'] == '1')
             + ($fields['Schizoid_Q1g'] == '1')) >= 1)
           // AND 4a in (1,2,3,4)
           && ($fields['Schizoid_Q4a_Treatment2'] == '1'
               || $fields['Schizoid_Q4a_Treatment3'] == '2'
               || $fields['Schizoid_Q4a_Treatment4'] == '3'
               || $fields['Schizoid_Q4a_Treatment5'] == '4')
           // AND 4h in (1,2)
           && ($fields['Schizoid_Q4h_Reliability'] == '1'
               || $fields['Schizoid_Q4h_Reliability'] == '2'))
            $scores['Score_paranoid_personality'] = 'Y';

        // pervasive development
        // OPTION 1
        // 2h=1 OR 2i=1
        if(($fields['Schizoid_Q2h'] == '1'
            || $fields['Schizoid_Q2i'] == '1')
           // AND yes to >=1 of 2a, 2b, 2d, 2f
           && ($fields['Schizoid_Q2a'] == '1'
               || $fields['Schizoid_Q2b'] == '1'
               || $fields['Schizoid_Q2d'] == '1'
               || $fields['Schizoid_Q2f'] == '1')
           // AND yes to >=1 of 2j, 2k
           && ($fields['Schizoid_Q2j'] == '1'
               || $fields['Schizoid_Q2k'] == '1')
           // AND "must be >=5 yes from (1) and (2) and (3)"
           && (($fields['Schizoid_Q2h'] == '1')
               + ($fields['Schizoid_Q2i'] == '1')
               + ($fields['Schizoid_Q2a'] == '1')
               + ($fields['Schizoid_Q2b'] == '1')
               + ($fields['Schizoid_Q2d'] == '1')
               + ($fields['Schizoid_Q2f'] == '1')
               + ($fields['Schizoid_Q2j'] == '1')
               + ($fields['Schizoid_Q2k'] == '1') >= 5)
           // AND 4g=1
           && ($fields['Schizoid_Q4g_Before3Yrs'] == '1')
           // AND 4h in (1,2)
           && ($fields['Schizoid_Q4h_Reliability'] == '1'
               || $fields['Schizoid_Q4h_Reliability'] == '2'))
            $scores['Score_pervasive_development'] = 'Y';

        // OPTION 2
        // yes to >=1 of 2a, 2b, 2d, 2f, 2i, 2j, 2k
        if(($fields['Schizoid_Q2a'] == '1'
            || $fields['Schizoid_Q2b'] == '1'
            || $fields['Schizoid_Q2d'] == '1'
            || $fields['Schizoid_Q2f'] == '1'
            || $fields['Schizoid_Q2i'] == '1'
            || $fields['Schizoid_Q2j'] == '1'
            || $fields['Schizoid_Q2k'] == '1')
           // AND 4a in (1,2,3,4)
           && ($fields['Schizoid_Q4a_Treatment2'] == '1'
               || $fields['Schizoid_Q4a_Treatment3'] == '2'
               || $fields['Schizoid_Q4a_Treatment4'] == '3'
               || $fields['Schizoid_Q4a_Treatment5'] == '4')
           // AND 4g=1
           && ($fields['Schizoid_Q4g_Before3Yrs'] == '1')
           // AND 4h in (1,2)
           && ($fields['Schizoid_Q4h_Reliability'] == '1'
               || $fields['Schizoid_Q4h_Reliability'] == '2'))
            $scores['Score_pervasive_development'] = 'Y';
        
        // only code schizoid or schizotypal if PDD is negative
        if($scores['Score_pervasive_development'] == 'N') {
            
            // schizoid personality
            // OPTION 1
            // yes to >=3 of 2a, 2b, 2c, 2d, 2e, 2f, 2g
            if((($fields['Schizoid_Q2a'] == '1')
                + ($fields['Schizoid_Q2b'] == '1')
                + ($fields['Schizoid_Q2c'] == '1')
                + ($fields['Schizoid_Q2d'] == '1')
                + ($fields['Schizoid_Q2e'] == '1')
                + ($fields['Schizoid_Q2f'] == '1')
                + ($fields['Schizoid_Q2g'] == '1') >= 3)
               // AND 4c in (1,2) OR 4d=1 OR 4e=1
               && (($fields['Schizoid_Q4c_Impairment'] == '1'
                    || $fields['Schizoid_Q4c_Impairment'] == '2')
                   || $fields['Schizoid_Q4d_SocialProbs'] == '1'
                   || $fields['Schizoid_Q4e_Unhappiness'] == '1')
               // AND 4f=1
               && ($fields['Schizoid_Q4f_Before17Yrs'] == '1')
               // AND 4h in (1,2)
               && ($fields['Schizoid_Q4h_Reliability'] == '1'
                   || $fields['Schizoid_Q4h_Reliability'] == '2'))
                $scores['Score_schizoid'] = 'Y';

            // OPTION 2
            // yes to >=1 of 2a, 2b, 2c, 2d, 2e, 2f, 2g
            if((($fields['Schizoid_Q2a'] == '1')
                + ($fields['Schizoid_Q2b'] == '1')
                + ($fields['Schizoid_Q2c'] == '1')
                + ($fields['Schizoid_Q2d'] == '1')
                + ($fields['Schizoid_Q2e'] == '1')
                + ($fields['Schizoid_Q2f'] == '1')
                + ($fields['Schizoid_Q2g'] == '1') >= 1)
               // AND 4a in (1,2,3,4)
               && ($fields['Schizoid_Q4a_Treatment2'] == '1'
                   || $fields['Schizoid_Q4a_Treatment3'] == '2'
                   || $fields['Schizoid_Q4a_Treatment4'] == '3'
                   || $fields['Schizoid_Q4a_Treatment5'] == '4')
               // AND 4h in (1,2)
               && ($fields['Schizoid_Q4h_Reliability'] == '1'
                   || $fields['Schizoid_Q4h_Reliability'] == '2'))
                $scores['Score_schizoid'] = 'Y';


            // schizotypal personality disorder
            // OPTION 1
            // yes to >=4 of 3a, 3b, 3c, 3d, 3e, 3f, 3g
            if((($fields['Schizoid_Q3a'] == '1')
                + ($fields['Schizoid_Q3b'] == '1')
                + ($fields['Schizoid_Q3c'] == '1')
                + ($fields['Schizoid_Q3d'] == '1')
                + ($fields['Schizoid_Q3e'] == '1')
                + ($fields['Schizoid_Q3f'] == '1')
                + ($fields['Schizoid_Q3g'] == '1') >= 4)
               // AND 4c in (1,2) or 4d = 1 or 4e = 1
               && (($fields['Schizoid_Q4c_Impairment'] == '1'
                    || $fields['Schizoid_Q4c_Impairment'] == '2')
                   ||$fields['Schizoid_Q4d_SocialProbs'] == '1'
                   || $fields['Schizoid_Q4e_Unhappiness'] == '1')
               // AND 4f = 1
               && ($fields['Schizoid_Q4f_Before17Yrs'] == '1')
               // AND 4h in (1,2)
               && ($fields['Schizoid_Q4h_Reliability'] == '1'
                   || $fields['Schizoid_Q4h_Reliability'] == '2'))
                $scores['Score_schizotypal'] = 'Y';

            
            // OPTION 2
            // yes to >=1 of 3a, 3b, 3c, 3d, 3e, 3f, 3g
            if((($fields['Schizoid_Q3a'] == '1')
                + ($fields['Schizoid_Q3b'] == '1')
                + ($fields['Schizoid_Q3c'] == '1')
                + ($fields['Schizoid_Q3d'] == '1')
                + ($fields['Schizoid_Q3e'] == '1')
                + ($fields['Schizoid_Q3f'] == '1')
                + ($fields['Schizoid_Q3g'] == '1') >= 1)
               // AND 4a in (1,2,3,4)
               && ($fields['Schizoid_Q4a_Treatment2'] == '1'
                   || $fields['Schizoid_Q4a_Treatment3'] == '2'
                   || $fields['Schizoid_Q4a_Treatment4'] == '3'
                   || $fields['Schizoid_Q4a_Treatment5'] == '4')
               // AND 4h in (1,2)
               && ($fields['Schizoid_Q4h_Reliability'] == '1'
                   || $fields['Schizoid_Q4h_Reliability'] == '2'))
                $scores['Score_schizotypal'] = 'Y';
            
        }

        // update database with score
        $success = $db->update('figs_year3_relatives', $scores, array('RelativeID'=>$relativeID));
        
        return $scores;
    }
    
    function _scoreRelativeASP($relativeID)
    {
        $db =& Database::singleton();
        
        $scores['Score_asp'] = 'N';
        
        $query = "SELECT ASP_Q1a,ASP_Q1b,ASP_Q1c,ASP_Q1d,ASP_Q1e,ASP_Q1f,ASP_Q1g,ASP_Q2_Over15Yrs,ASP_Q3_Under15Yrs
 FROM figs_year3_relatives WHERE RelativeID='$relativeID'";
        $db->selectRow($query, $fields); 

        // yes to >=2 of 1a, 1b, 1c, 1d, 1e, 1f, 1g
        if((($fields['ASP_Q1a'] == '1')
            + ($fields['ASP_Q1b'] == '1')
            + ($fields['ASP_Q1c'] == '1')
            + ($fields['ASP_Q1d'] == '1')
            + ($fields['ASP_Q1e'] == '1')
            + ($fields['ASP_Q1f'] == '1')
            + ($fields['ASP_Q1g'] == '1') >= 2)
        // AND 2 = yes
           && ($fields['ASP_Q2_Over15Yrs'] == '1')
        // AND 3 = yes
           && ($fields['ASP_Q3_Under15Yrs'] == '1'))
            $scores['Score_asp'] = 'Y';
        
        // update database with score
        $success = $db->update('figs_year3_relatives', $scores, array('RelativeID'=>$relativeID));
        
        return $scores;
    }

    function _scoreRelativeTic($relativeID)
    {
        $db =& Database::singleton();
        
        $scores['Score_tic_tourettes'] = 'N';
        $scores['Score_tic_motor_c'] = 'N';
        $scores['Score_tic_vocal_c'] = 'N';
        $scores['Score_tic_motor_t'] = 'N';
        $scores['Score_tic_vocal_t'] = 'N';
        
        $query = "SELECT 
Tic_Q1,
Tic_Q1a,
Tic_Q1b,
Tic_Q1c,
Tic_Q1d,
Tic_Q2,
Tic_Q2a,
Tic_Q2b,
Tic_Q2c,
Tic_Q2d,
Tic_Q3a_Treatment2,
Tic_Q3a_Treatment3,
Tic_Q3a_Treatment4,
Tic_Q3a_Treatment5,
Tic_Q3b_OnsetAge,
Tic_Q3d_Duration,
Tic_Q3e_Impairment,
Tic_Q3f_Reliability
 FROM figs_year3_relatives WHERE RelativeID='$relativeID'";
        $db->selectRow($query, $fields); 
 
        // tourette's disorder
        // OPTION 1
        // 1a = 1
        if(($fields['Tic_Q1a'] == '1')
           // AND 1b=1 or 3d>=52 weeks
           && ($fields['Tic_Q1b'] == '1'
               || $fields['Tic_Q3d_Duration'] >= 52)
           // AND 1c=1 or 3b <= 18 years
           && ($fields['Tic_Q1c'] == '1'
               || $fields['Tic_Q3b_OnsetAge'] <= 18)
           // AND 1d=1 or 3e in (1,2)
           && ($fields['Tic_Q1d'] == '1'
               || $fields['Tic_Q3e_Impairment'] == '1'
               || $fields['Tic_Q3e_Impairment'] == '2')
           // AND 2=1
           && ($fields['Tic_Q2'] == '1')
           // AND 3f in (1,2)
           && ($fields['Tic_Q3f_Reliability'] == '1'
               || $fields['Tic_Q3f_Reliability'] == '2'))
            $scores['Score_tic_tourettes'] = 'Y';

        // OPTION 2
        // 1=1
        if(($fields['Tic_Q1'] == '1')
           // AND 2a=1
           && ($fields['Tic_Q2a'] == '1')
           // AND 2b=1 or 3d>=52 weeks
           && ($fields['Tic_Q2b'] == '1'
               || $fields['Tic_Q3d_Duration'] >= 52)
           // AND 2c=1 or 3b <= 18 years
           && ($fields['Tic_Q2c'] == '1'
               || $fields['Tic_Q3b_OnsetAge'] <= 18)
           // AND 2d=1 or 3e in (1,2)
           && ($fields['Tic_Q2d'] == '1'
               || $fields['Tic_Q3e_Impairment'] == '1'
               || $fields['Tic_Q3e_Impairment'] == '2')
           // AND 3f in (1,2)
           && ($fields['Tic_Q3f_Reliability'] == '1'
               || $fields['Tic_Q3f_Reliability'] == '2'))
            $scores['Score_tic_tourettes'] = 'Y';

        // OPTION 3
        // 3a in (1,2,3,4)
        if(($fields['Tic_Q3a_Treatment2'] == '1'
            || $fields['Tic_Q3a_Treatment3'] == '2'
            || $fields['Tic_Q3a_Treatment4'] == '3'
            || $fields['Tic_Q3a_Treatment5'] == '4')
           // AND 3f in (1,2)
           && ($fields['Tic_Q3f_Reliability'] == '1'
               || $fields['Tic_Q3f_Reliability'] == '2'))
            $scores['Score_tic_tourettes'] = 'Y';

        // code only if criteria for tourettes is not met
        if($scores['Score_tic_tourettes'] == 'N') {

            // chronic motor
            // 1a=1
            if(($fields['Tic_Q1a'] == '1')
               // AND 1b=1 or 3d>=52 weeks
               && ($fields['Tic_Q1b'] == '1'
                   || $fields['Tic_Q3d_Duration'] >= 52)
               // AND 1c=1 or 3b <= 18 years
               && ($fields['Tic_Q1c'] == '1'
                   || $fields['Tic_Q3b_OnsetAge'] <= 18)
               // AND 1d=1 or 3e in (1,2)
               && ($fields['Tic_Q1d'] == '1'
                   || $fields['Tic_Q3e_Impairment'] == '1'
                   || $fields['Tic_Q3e_Impairment'] == '2')
               // AND 3f in (1,2)
               && ($fields['Tic_Q3f_Reliability'] == '1'
                   || $fields['Tic_Q3f_Reliability'] == '2'))
                $scores['Score_tic_motor_c'] = 'Y';
            
            // chronic vocal
            // 2a=1
            if(($fields['Tic_Q2a'] == '1')
               // AND 2b=1 or 3d>=52 weeks
               && ($fields['Tic_Q2b'] == '1'
                   || $fields['Tic_Q3d_Duration'] >= 52)
               // AND 2c=1 or 3b <= 18 years
               && ($fields['Tic_Q2c'] == '1'
                   || $fields['Tic_Q3b_OnsetAge'] <= 18)
               // AND 2d=1 or 3e in (1,2)
               && ($fields['Tic_Q2d'] == '1'
                   || $fields['Tic_Q3e_Impairment'] == '1'
                   || $fields['Tic_Q3e_Impairment'] == '2')
               // AND 3f in (1,2)
               && ($fields['Tic_Q3f_Reliability'] == '1'
                   || $fields['Tic_Q3f_Reliability'] == '2'))
                $scores['Score_tic_vocal_c'] = 'Y';

            // do not code if criteria met for tourettes or chronic tics
            if($scores['Score_tic_motor_c'] == 'N' && $scores['Score_tic_vocal_c'] == 'N') {

                // transient motor
                // yes to all of 1a, 1c, 1d
                if(($fields['Tic_Q1a'] == '1')
                   && ($fields['Tic_Q1c'] == '1')
                   && ($fields['Tic_Q1d'] == '1')
                   // AND NO to 1b
                   && ($fields['Tic_Q1b'] == '0'))
                    $scores['Score_tic_motor_t'] = 'Y';
                
                // transient vocal
                // yes to all of 2a, 2c, 2d
                if(($fields['Tic_Q2a'] == '1')
                   && ($fields['Tic_Q2c'] == '1')
                   && ($fields['Tic_Q2d'] == '1')
                   // AND NO to 2b
                   && ($fields['Tic_Q2b'] == '0'))
                    $scores['Score_tic_vocal_t'] = 'Y';
            } // end of if score_tic_*_c == N
        } // end if score_tic_tourettes == N
        
        // update database with score
        $success = $db->update('figs_year3_relatives', $scores, array('RelativeID'=>$relativeID));
        
        return $scores;
    }

    function _scoreRelativeOCD($relativeID)
    {
        $db =& Database::singleton();
        
        $scores['Score_ocd'] = 'N';
        
        $query = "SELECT 
OCD_Q1a,
OCD_Q1b,
OCD_Q1c,
OCD_Q1d,
OCD_Q2a,
OCD_Q3a,
OCD_Q4a_Treatment2,
OCD_Q4a_Treatment3,
OCD_Q4a_Treatment4,
OCD_Q4a_Treatment5,
OCD_Q4e_Impairment,
OCD_Q4f_Reliability
 FROM figs_year3_relatives WHERE RelativeID='$relativeID'";
        $db->selectRow($query, $fields); 

        // OPTION 1
        // yes to 1a
        if(($fields['OCD_Q1a'] == '1')
           // AND yes to >=2 of 1b, 1c, 1d
           && (($fields['OCD_Q1b'] == '1')
               + ($fields['OCD_Q1c'] == '1')
               + ($fields['OCD_Q1d'] == '1')) >= 2
           // AND yes to 3
           && ($fields['OCD_Q3a'] == '1')
           // AND 4e in (1,2)
           && ($fields['OCD_Q4e_Impairment'] == '1'
               || $fields['OCD_Q4e_Impairment'] == '2'
               || $fields['OCD_Q4e_Impairment'] == '3')
           // AND 4f in (1,2)
           && ($fields['OCD_Q4f_Reliability'] == '1'
               || $fields['OCD_Q4f_Reliability'] == '2'))
            $scores['Score_ocd'] = 'Y';

        // OPTION 2
        // yes to 2a
        if(($fields['OCD_Q2a'] == '1')
           // AND yes to 3
           && ($fields['OCD_Q3a'] == '1')
           // AND 4e in (1,2,3)
           && ($fields['OCD_Q4e_Impairment'] == '1'
               || $fields['OCD_Q4e_Impairment'] == '2'
               || $fields['OCD_Q4e_Impairment'] == '3')
           // AND 4f in (1,2)
           && ($fields['OCD_Q4f_Reliability'] == '1'
               || $fields['OCD_Q4f_Reliability'] == '2'))
            $scores['Score_ocd'] = 'Y';

        // OPTION 3
        // 4a in (1,2,3,4)
        if(($fields['OCD_Q4a_Treatment2'] == '1'
            || $fields['OCD_Q4a_Treatment3'] == '2'
            || $fields['OCD_Q4a_Treatment4'] == '3'
            || $fields['OCD_Q4a_Treatment5'] == '4')
           // AND 4f in (1,2)
           && ($fields['OCD_Q4f_Reliability'] == '1'
               || $fields['OCD_Q4f_Reliability'] == '2'))
            $scores['Score_ocd'] = 'Y';

        // update database with score
        $success = $db->update('figs_year3_relatives', $scores, array('RelativeID'=>$relativeID));
        
        return $scores;
    }

    function _scoreRelativeADHD($relativeID)
    {
        $db =& Database::singleton();
        
        $scores['Score_adhd_combined'] = 'N';
        $scores['Score_adhd_inattentive'] = 'N';
        $scores['Score_adhd_hyperactive'] = 'N';

        
        $query = "SELECT 
ADHD_Q1a,
ADHD_Q1b,
ADHD_Q1c,
ADHD_Q1d,
ADHD_Q1e,
ADHD_Q1f,
ADHD_Q1g,
ADHD_Q1h,
ADHD_Q1i,
ADHD_Q1j,
ADHD_Q1k1,
ADHD_Q1l1,
ADHD_Q1l2,
ADHD_Q1l3,
ADHD_Q2a,
ADHD_Q2b,
ADHD_Q2c,
ADHD_Q2d,
ADHD_Q2e,
ADHD_Q2f,
ADHD_Q2g,
ADHD_Q2h,
ADHD_Q2i,
ADHD_Q2j,
ADHD_Q2k1,
ADHD_Q2k2,
ADHD_Q2k3,
ADHD_Q3a_Treatment1,
ADHD_Q3a_Treatment2,
ADHD_Q3a_Treatment4,
ADHD_Q3g_Reliability
 FROM figs_year3_relatives WHERE RelativeID='$relativeID'";
        $db->selectRow($query, $fields); 
 

        // ADHD combined
        // yes to >=5 of 1a, 1b, 1c, 1d, 1e, 1f, 1g, 1h, 1i
        if((($fields['ADHD_Q1a'] == '1')
            + ($fields['ADHD_Q1b'] == '1')
            + ($fields['ADHD_Q1c'] == '1')
            + ($fields['ADHD_Q1d'] == '1')
            + ($fields['ADHD_Q1e'] == '1')
            + ($fields['ADHD_Q1f'] == '1')
            + ($fields['ADHD_Q1g'] == '1')
            + ($fields['ADHD_Q1h'] == '1')
            + ($fields['ADHD_Q1i'] == '1') >= 5)
        // AND 1j=1 OR 1k=1
           && ($fields['ADHD_Q1j'] == '1'
               || $fields['ADHD_Q1k1'] == '1')
        // AND yes to 5 of 2a, 2b, 2c, 2d, 2e, 2f, 2g, 2h, 2i, 2j
           && (($fields['ADHD_Q2a'] == '1')
               + ($fields['ADHD_Q2b'] == '1')
               + ($fields['ADHD_Q2c'] == '1')
               + ($fields['ADHD_Q2d'] == '1')
               + ($fields['ADHD_Q2e'] == '1')
               + ($fields['ADHD_Q2f'] == '1')
               + ($fields['ADHD_Q2g'] == '1')
               + ($fields['ADHD_Q2h'] == '1')
               + ($fields['ADHD_Q2i'] == '1')
               + ($fields['ADHD_Q2j'] == '1') >= 5)
        // AND yes to 1l or 2k (any of the three subcomponents)
           && ($fields['ADHD_Q1l1'] == '1'
               || $fields['ADHD_Q1l2'] == '1'
               || $fields['ADHD_Q1l3'] == '1'
               || $fields['ADHD_Q2k1'] == '1'
               || $fields['ADHD_Q2k2'] == '1'
               || $fields['ADHD_Q2k3'] == '1')
        // AND 3g in (1,2)
           && ($fields['ADHD_Q3g_Reliability'] == '1'
               || $fields['ADHD_Q3g_Reliability'] == '2'))
            $scores['Score_adhd_combined'] = 'Y';

        // ADD inattentive
        // yes to >=5 of 1a, 1b, 1c, 1d, 1e, 1f, 1g, 1h, 1i
        if((($fields['ADHD_Q1a'] == '1')
            + ($fields['ADHD_Q1b'] == '1')
            + ($fields['ADHD_Q1c'] == '1')
            + ($fields['ADHD_Q1d'] == '1')
            + ($fields['ADHD_Q1e'] == '1')
            + ($fields['ADHD_Q1f'] == '1')
            + ($fields['ADHD_Q1g'] == '1')
            + ($fields['ADHD_Q1h'] == '1')
            + ($fields['ADHD_Q1i'] == '1') >= 5)
        // AND 1j=1 OR 1k=1
           && ($fields['ADHD_Q1j'] == '1'
               || $fields['ADHD_Q1k1'] == '1')
        // AND yes to 1l (any of the three subcomponents)
//           && ($fields['ADHD_Q1l1'] == '1'
//               || $fields['ADHD_Q1l2'] == '1'
//               || $fields['ADHD_Q1l3'] == '1')
        // AND 3g in (1,2)
           && ($fields['ADHD_Q3g_Reliability'] == '1'
               || $fields['ADHD_Q3g_Reliability'] == '2'))
            $scores['Score_adhd_inattentive'] = 'Y';

        // ADD hyperactive
        // yes to >=5 of 2a, 2b, 2c, 2d, 2e, 2f, 2g, 2h, 2i
        if((($fields['ADHD_Q2a'] == '1')
            + ($fields['ADHD_Q2b'] == '1')
            + ($fields['ADHD_Q2c'] == '1')
            + ($fields['ADHD_Q2d'] == '1')
            + ($fields['ADHD_Q2e'] == '1')
            + ($fields['ADHD_Q2f'] == '1')
            + ($fields['ADHD_Q2g'] == '1')
            + ($fields['ADHD_Q2h'] == '1')
            + ($fields['ADHD_Q2i'] == '1') >= 5)
        // AND 2j=1
           && ($fields['ADHD_Q2j'] == '1')
        // AND 2k=1 (any of the three subcomponents)
           && ($fields['ADHD_Q2k1'] == '1'
               || $fields['ADHD_Q2k2'] == '1'
               || $fields['ADHD_Q2k3'] == '1')
        // AND 3g in (1,2)
           && ($fields['ADHD_Q3g_Reliability'] == '1'
               || $fields['ADHD_Q3g_Reliability'] == '2'))
            $scores['Score_adhd_hyperactive'] = 'Y';

        // OPTION 2 - all three varieties
        // 3a in (1,2,4)
        if(($fields['ADHD_Q3a_Treatment1'] == '1'
            || $fields['ADHD_Q3a_Treatment2'] == '2'
            || $fields['ADHD_Q3a_Treatment4'] == '4')
           // AND 3g in (1,2)
           && ($fields['ADHD_Q3g_Reliability'] == '1'
               || $fields['ADHD_Q3g_Reliability'] == '2')) {
            $scores['Score_adhd_hyperactive'] = 'Y';
            $scores['Score_adhd_combined'] = 'Y';
            $scores['Score_adhd_inattentive'] = 'Y';
        }

        // update database with score
        $success = $db->update('figs_year3_relatives', $scores, array('RelativeID'=>$relativeID));
        
        return $scores;
    }

    /**
    * nulls all scores for the record identified by CommentID
    * @param array list of scoring fields to null
    * @see $this->getCommentID()
    * @return mixed
    * @throws $this->error
    */
    function _nullScores()
    {
        $db=& Database::singleton();
        
        // set the scoring cols to NULL
        foreach ($this->scoreCols as $val) {
            $scores[$val]=null;
        }
        
        // update the scores
        $success = $db->update('figs_year3',$scores,array('CommentID'=>$this->getCommentID()));

        // null the relatives' scores
        foreach ($this->scoreColsRelative as $val) {
        	$scores1[$val]=null;
        }
        $success = $db->update('figs_year3_relatives',$scores1,array('CommentID'=>$this->getCommentID()));
        
        return;
    }
    function clearInstrument() {

        $config = NDB_Config::singleton();
        $dbconfig = $config->getSetting('database');
        $db = Database::singleton();
        $columns = $db->pselect("select COLUMN_NAME FROM information_schema.columns 
                   WHERE TABLE_NAME=:table AND TABLE_SCHEMA=:db",
                   array('table' => 'figs_year3', 'db' => $dbconfig['database'] ));
        $values = array();
        foreach ($columns as $row) {
            if($row['COLUMN_NAME'] == 'CommentID' || $row['COLUMN_NAME'] == 'UserID') {
                continue;
            }
            $values[$row['COLUMN_NAME']] = NULL;
        }
        $db->update('figs_year3', $values, array('CommentID' => $this->commentID));
        $db->delete('figs_year3_relatives' , array('CommentID' => $this->commentID));
        $prepQ = $db->prepare("DELETE FROM conflicts_unresolved WHERE (CommentId1=:CID OR CommentId2=:CID)");
        $db->execute($prepQ, array('CID' => $this->commentID));
    }

} // End class
?>
