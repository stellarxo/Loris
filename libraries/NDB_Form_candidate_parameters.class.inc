<?php
require_once "NDB_Form.class.inc";
require_once "Utility.class.inc";

/**
 * Candidate Parameter form
 * @package main
 */
class NDB_Form_candidate_parameters extends NDB_Form
{
    var $relationType =  array(null=>'','full_sibling'=>'Full Sibling',
                               'half_sibling'=>'Half Sibling','1st_cousin'=>'First Cousin');
    function _hasAccess()
    {
        // create user object
        $user =& User::singleton();
        if(Utility::isErrorX($user)) {
            return PEAR::raiseError("User Error: ".$user->getMessage());
        }

        // check that the $candID is passed b/c the profile needs to be opened
        if ($this->identifier != $_REQUEST['candID']) {
            return PEAR::raiseError("NDB_Form_candidate_parameters::_access: Candidate Profile Error (".$_REQUEST['candID']."): ");
        }

        $candidate =& Candidate::singleton($this->identifier);
        if (Utility::isErrorX($candidate)) {
            return PEAR::raiseError("Candidate Error ($this->identifier): ".$candidate->getMessage());
        }

        // check user permissions
    	return ($user->hasPermission('data_entry') && $user->getData('CenterID') == $candidate->getData('CenterID') && $user->hasPermission('unsend_to_dcc'));
    }

    function _getDefaults()
    {
  		$DB =& Database::singleton();
        //Get the default values
        $DB->select("SELECT ParameterTypeID, Value FROM parameter_candidate WHERE CandID='".$this->identifier."'", $value_results);
        foreach($value_results AS $vresult){
        	$defaults["PTID_".$vresult['ParameterTypeID']]=$vresult['Value'];
        }
        $defaults['CandidateGUID'] = $DB->pselectOne("SELECT CandidateGUID FROM candidate WHERE CandID=:CandidateID", array('CandidateID' => $this->identifier));
        $defaults['ProbandGUID'] = $DB->pselectOne("SELECT ProbandGUID FROM candidate WHERE CandID=:CandidateID", array('CandidateID' => $this->identifier));
        $defaults['ProbandDoB'] = $DB->pselectOne("SELECT ProbandDoB FROM candidate WHERE CandID=:CandidateID", array('CandidateID' => $this->identifier));
        
        $defaults['ProbandGender'] = $DB->pselectOne("SELECT ProbandGender FROM candidate WHERE CandID=:CandidateID", array('CandidateID' => $this->identifier));
        $candidate_dob = $DB->pselectOne("SELECT DoB FROM candidate WHERE CandID=:CandidateID", array('CandidateID' => $this->identifier));

        $age = Utility::calculateAge($defaults['ProbandDoB'],$candidate_dob ); 
        if(Utility::isErrorX($age)) {
            $defaults['Age_Difference'] = 'Could not calculate age';
        } else {
            $defaults['Age_Difference'] = $age['year']*12 + $age['mon']+ round($age['day']/30,2);
        }
        $familyid = $DB->pselectOne("SELECT FamilyID from family where CandID=:CandidateID",array('CandidateID'=>$this->identifier));
        if(Utility::isErrorX($familyid)){
            $relations = $DB->pselect("SELECT Relation_CandID, Relation_code from family WHERE CandID=:CandidateID",array('CandidateID'=> $this->identifier));

        } else {
            $this->tpl_data['familyID'] = $familyid;
            $relations = $DB->pselect("SELECT CandID, Relationship_type from family WHERE FamilyID=:fam_id
                                       AND CandID <> '$this->identifier'" ,array('fam_id'=> $familyid));

        }
        $this->tpl_data['sibling_list'] = array();
        foreach($relations as $relation)
        {
            $relation['Relationship_type'] = $this->relationType[$relation['Relationship_type']];
            $this->tpl_data['sibling_list'][]= $relation;
        }
        return $defaults;
    }

    function _process($values)
    {
        if(!is_array($values) || count($values) ==0) {
        	return true;
        }
        
        $DB =& Database::singleton();
       if(!isset($values['SiblingID'])){ 
        //delete old values
        $DB->delete("parameter_candidate", array("CandID"=>$this->identifier));
        
        //insert new values
        while(list($key, $value)=each($values)){
        	$set="";
            if(strpos($key, "PTID_") === 0) {
                $set['ParameterTypeID']=str_replace("PTID_","",$key);
                $set['CandID']=$this->identifier;
                $set['Value']=$value;
                $set['InsertTime']=time();
                $DB->insert("parameter_candidate", $set);
            } else if($key == 'CandidateGUID' || $key == "ProbandGUID" || $key == 'ProbandDoB' || $key == 'ProbandGender') {
                if($key == 'ProbandDoB') {
                    $value = $this->_getDatabaseDate($value);
                }
                $DB->update("candidate", array($key => $value), array('CandID' => $this->identifier));

                if ($key == 'ProbandDoB') {
                    $tests = $DB->pselect(
                        "SELECT f.CommentID, f.Test_name 
                        FROM flag f JOIN session s ON (f.SessionID=s.ID)
                        JOIN candidate c ON (c.CandID=s.CandID)
                        WHERE
                        c.CandID=:CaID AND f.Test_name LIKE '%proband'
                        ", array('CaID' => $this->identifier)
                    );
                    foreach ($tests as $test) {
                        $inst = NDB_BVL_Instrument::factory($test['Test_name'], $test['CommentID'], null, false);
                        $setValue = array('Date_taken' => $inst->getFieldValue('Date_taken'));
                        $inst->_saveCandidateAge($setValue);
                        $DB->update($test['Test_name'], $setValue, array('CommentID' => $test['CommentID']));
                    }

                }
            }

        }
       } else {
           $fid = $DB->pselectOne("SELECT FamilyID from family where CandID=:CaID",array('CaID' => $this->identifier));
           if (Utility::isErrorX($fid)) {
               return PEAR::raiseError("Could not family id: ".$fid->getMessage());
           }
           if(empty($fid)){
               $famID = $DB->pselectOne("SELECT max(FamilyID) from family");
               if (Utility::isErrorX($famID)) {
                   return PEAR::raiseError("Could not family id: ".$famID->getMessage());
               }
               if(empty($famID)) {
                   $famID = 0;
               }
               $fid = $famID+1;
               $success = $DB->insert('family',array('CandID'=>$this->identifier,'FamilyID'=>$fid,
                           'Relationship_type'=>$values['relation_type']));
               if (Utility::isErrorX($success)) {
                   return PEAR::raiseError("DB Error: ".$success->getMessage());
               }

           }

           $value = $values['SiblingID'];
           $success = $DB->insert('family',array('CandID'=>$value,'FamilyID'=>$fid,
                                                 'Relationship_type'=>$values['relation_type']));
           if (Utility::isErrorX($success)) {
               return PEAR::raiseError("DB Error: ".$success->getMessage());
           }

          
        }
        $this->tpl_data['success'] = true;

        // freeze it, just in case
        $this->form->freeze();
    }


    function _getInstrumentInfo($instrument, $param) {
        $DB =& Database::singleton();

        $ret = $DB->selectOne("SELECT t.$param FROM flag f JOIN $instrument t ON (t.CommentID=f.CommentID) JOIN session s ON (f.SessionID=s.ID) WHERE s.CandID=" . $DB->quote($this->identifier) . ' AND f.test_name=' . $DB->quote($instrument) . ' AND t.CommentID NOT LIKE \'DDE_%\'');
        if($ret == array()) {
            return;
        }
        return $ret;
    }

    function _getTSIinfo($param) {
        return $this->_getInstrumentInfo('tsi', $param);
    }

    function _getADIRinfo($param) {
        return $this->_getInstrumentInfo('adi_r_proband', $param);
    }
    function candidate_parameters()
    {
        $DB =& Database::singleton();
        $config =& NDB_Config::singleton();

        $ethnicityList = array(null=>'');
        $success = Utility::getEthnicityList();
        if (Utility::isErrorX($success)) {
        	return PEAR::raiseError("Utility::getEthnicityList error: ".$success->getMessage());
        }
        $ethnicityList = array_merge($ethnicityList,$success);
        unset($success);
        
        $candidate =& Candidate::singleton($this->identifier);
        if (Utility::isErrorX($candidate)) {
            return PEAR::raiseError("Candidate Error ($this->identifier): ".$candidate->getMessage());
        }

        // candID
        $this->tpl_data['candID'] = $candidate->getData('CandID');
 		//Extract the fields from the parameter_type table
        $DB->select("SELECT pt.ParameterTypeID, pt.Name, pt.Type, Description FROM parameter_type as pt, parameter_type_category as ptc, parameter_type_category_rel as ptcr WHERE pt.ParameterTypeID=ptcr.ParameterTypeID AND ptcr.ParameterTypeCategoryID=ptc.ParameterTypeCategoryID AND ptc.Name='Candidate Parameters' ORDER BY pt.ParameterTypeID, pt.name ASC", $field_results);
        //If there are no defined fields pritn a message to that effect
        if(empty($field_results)){
        	$this->form->addElement('static', "static", "No candidate parameters have been defined for this study");
        	return;
        }
        
        
        //Loop through the fields and add them appropriately
        foreach($field_results AS $fresult) {
        	switch(substr($fresult['Type'],0,3)) {
        		case "enu":
        			$options=substr($fresult['Type'],4);
        			$options=trim($options,"()");
        			$options=Utility::explodeEncapsulated(",", "'", $options);
                    $elOptions = array('' => '');
                    foreach($options as $option) {
                        $elOptions[$option] = $option;
                    }
        			$this->form->addElement('select', "PTID_".$fresult['ParameterTypeID'], $fresult['Description'], $elOptions);
        		break;
        		
        		case "dat":
        			$this->form->addElement('date', "PTID_".$fresult['ParameterTypeID'], $fresult['Description'], $dateOptions);
        		break;
        		
        		case "int":
        		case "var":
        		case "tex":
            default:
        			$this->form->addElement('textarea', "PTID_".$fresult['ParameterTypeID'], $fresult['Description']);
        		
        	}
        	$this->tpl_data['elements_list'][]="PTID_".$fresult['ParameterTypeID'];
        }

        $DoB_ADI_R = $this->_getADIRinfo("DoB_proband");
        $DoB_Vineland = $this->_getInstrumentInfo("vineland_proband", "BIRTH_DATE");
        if($DoB_ADI_R != $DoB_Vineland) {
            $this->form->addElement('static', 'dob_error', 'Date of Birth from Vineland and ADI-R do not match');
        }
        $this->form->addElement('text', 'CandidateGUID', 'Candidate GUID:');
        $this->form->addElement('text', 'ProbandGUID', 'Proband GUID:');
        $probandDateOptions = array(
            'language' => 'en',
            'format'   => 'YMd',
            'minYear'  => $config->getSetting('startYear') - 20, //allows for proband siblings up to 20 years older than candidate
            'maxYear'  => $config->getSetting('endYear'),
            'addEmptyOption' => true,
            'emptyOptionValue' => null
        );

        $this->form->addElement('date', 'ProbandDoB', 'DoB Proband:', $probandDateOptions);
        $this->form->addElement('select', 'ProbandGender', 'Proband gender:', array('' => '','Male' => 'Male', 'Female' => 'Female') );
        $this->form->addElement('static', 'dob_proband_adi_r', 'DoB of Proband (ADI-R):', $DoB_ADI_R);
        $this->form->addElement('static', 'dob_proband_vineland', 'DoB of Proband (Vineland):', $DoB_Vineland);
        $this->form->addElement('static', 'Age_Difference','Age Difference (in months):');
        $this->form->addElement('static', 'mother_race', 'Mother\'s Race:', $this->_getTSIinfo("mother_race"));
        $this->form->addElement('static', 'father_race', 'Father\'s Race:', $this->_getTSIinfo("father_race"));
        $this->form->addElement('static', 'birth_city', 'City of Birth:', $this->_getTSIinfo("city_of_birth"));
        $this->form->addElement('static', 'home_lang', 'Primary Language At Home:', $this->_getTSIinfo("primary_language"));
        $this->form->addElement('static','SiblingcID','Sibling ID:'); 
        $this->form->addElement('select','SiblingType','Relation Type:', array(''=>'','broth'=>'Brother','siste'=>'Sister'));
    }

    /* This is taken from NDB_BVL_Instrument. It should be moved to NDB_Page once NDB_Page is merged. */

    function _getDatabaseDate($formDateValue) {
        if(!empty($formDateValue)){
            // check if it's already formatted correctly
            if(is_string($formDateValue) && preg_match("/^[\d]{4}-[\d]{2}-[\d]{2}$/", $formDateValue)) {
                return $formDateValue;
            }
            if(count($formDateValue)==2) {
                $databaseValue = "$formDateValue[H]:$formDateValue[i]";  //handle time (HH:MM:SS)
            } else {
                $databaseValue = "$formDateValue[Y]-$formDateValue[M]-$formDateValue[d]";  //handle date (YYYY/MM/DD)
            }
        }
        return $databaseValue;
    }

    function add_family(){
        
        $this->form->addElement('text','SiblingID','Sibling ID:');
        $this->form->addElement('select','relation_type','Relation Type', $this->relationType);
        $this->form->addFormRule(array(&$this, '_validate_add_family'));
        $this->tpl_data['candID'] = $_REQUEST['candID']; 


    }

    function _validate_add_family($values)
    {   
        if(!is_array($values) || count($values) ==0) {
            return true;
        }
        $cand = $values['SiblingID'];
        $DB =& Database::singleton();
        $errors = array();
        $results = $DB->pselect("SELECT CandID from candidate where Active='Y'" ,array());
        $activeCandidates = array();
        foreach($results as $row) {
            $activeCandidates[] = $row['CandID'];
        }
        if(!in_array($cand, $activeCandidates)){
            $errors['SiblingID']= 'Candidate should be part of study. Please enter correct CandID';
        }
        $familyID = $DB->pselectOne("SELECT FamilyID from family WHERE CandID=:cid",array('cid'=>$this->identifier));
        $relatives = $DB->pselect("SELECT CandID from family WHERE FamilyID=:fid",array('fid'=>$familyID));
        $active_family = array();
        foreach($relatives as $relative){
            $active_family[] = $relative['CandID'];    
        }
        if(in_array($cand, $active_family)){
            $errors['SiblingID'] = 'CandID already entered as Sibling';    
        }
        return $errors;
    }


}
?>
