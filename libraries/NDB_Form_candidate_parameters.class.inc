<?php
require_once "NDB_Form.class.inc";

/**
 * Candidate Parameter form
 * @package main
 */
class NDB_Form_candidate_parameters extends NDB_Form
{
    
    function _hasAccess()
    {
        // create user object
        $user =& User::singleton();
        if(PEAR::isError($user)) {
            return PEAR::raiseError("User Error: ".$user->getMessage());
        }

        // check that the $candID is passed b/c the profile needs to be opened
        if ($this->identifier != $_REQUEST['candID']) {
            return PEAR::raiseError("NDB_Form_candidate_parameters::_access: Candidate Profile Error (".$_REQUEST['candID']."): ");
        }

        $candidate =& Candidate::singleton($this->identifier);
        if (PEAR::isError($candidate)) {
            return PEAR::raiseError("Candidate Error ($this->identifier): ".$candidate->getMessage());
        }

        // check user permissions
    	return ($user->hasPermission('data_entry') && $user->getData('CenterID') == $candidate->getData('CenterID'));
    }

    function _getDefaults()
    {
  		$DB =& Database::singleton();
        //Get the default values
        $DB->select("SELECT ParameterTypeID, Value FROM parameter_candidate WHERE CandID='".$this->identifier."'",&$value_results);
        foreach($value_results AS $vresult){
        	$defaults["PTID_".$vresult['ParameterTypeID']]=$vresult['Value'];
        }
        return $defaults;
    }

    function _process($values)
    {
        if(!is_array($values) || count($values) ==0) {
        	return true;
        }
        
        $DB =& Database::singleton();
        
        //delete old values
        $DB->delete("parameter_candidate", array("CandID"=>$this->identifier));
        
        //insert new values
        while(list($key, $value)=each($values)){
        	$set="";
        	$set['ParameterTypeID']=str_replace("PTID_","",$key);
        	$set['CandID']=$this->identifier;
        	$set['Value']=$value;
        	$set['InsertTime']=time();
        	$DB->insert("parameter_candidate", $set);
        }

        $this->tpl_data['success'] = true;

        // freeze it, just in case
        $this->form->freeze();
    }


    function _getInstrumentInfo($instrument, $param) {
        $DB =& Database::singleton();

        return $DB->selectOne("SELECT t.$param FROM flag f JOIN $instrument t ON (t.CommentID=f.CommentID) JOIN session s ON (f.SessionID=s.ID) WHERE s.CandID=" . $DB->quote($this->identifier) . ' AND f.test_name=' . $DB->quote($instrument) . ' AND t.CommentID NOT LIKE \'DDE_%\'');
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

        $ethnicityList = array(null=>'');
        $success = Utility::getEthnicityList();
        if (PEAR::isError($success)) {
        	return PEAR::raiseError("Utility::getEthnicityList error: ".$success->getMessage());
        }
        $ethnicityList = array_merge($ethnicityList,$success);
        unset($success);
        
        $candidate =& Candidate::singleton($this->identifier);
        if (PEAR::isError($candidate)) {
            return PEAR::raiseError("Candidate Error ($this->identifier): ".$candidate->getMessage());
        }

        // candID
        $this->tpl_data['candID'] = $candidate->getData('CandID');
 		//Extract the fields from the parameter_type table
        $DB->select("SELECT pt.ParameterTypeID, pt.Name, pt.Type, Description FROM parameter_type as pt, parameter_type_category as ptc, parameter_type_category_rel as ptcr WHERE pt.ParameterTypeID=ptcr.ParameterTypeID AND ptcr.ParameterTypeCategoryID=ptc.ParameterTypeCategoryID AND ptc.Name='Candidate Parameters' ORDER BY pt.name ASC", &$field_results);
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
        			$this->form->addElement('select', "PTID_".$fresult['ParameterTypeID'], $fresult['Description'], $options);
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
        $this->form->addElement('static', 'dob_proband_adi_r', 'DoB of Proband (ADI-R):', $DoB_ADI_R);
        $this->form->addElement('static', 'dob_proband_vineland', 'DoB of Proband (Vineland):', $DoB_Vineland);
        $this->form->addElement('static', 'mother_race', 'Mother\'s Race:', $this->_getTSIinfo("mother_race"));
        $this->form->addElement('static', 'father_race', 'Father\'s Race:', $this->_getTSIinfo("father_race"));
        $this->form->addElement('static', 'birth_city', 'City of Birth:', $this->_getTSIinfo("city_of_birth"));
        $this->form->addElement('static', 'home_lang', 'Primary Language At Home:', $this->_getTSIinfo("primary_language"));
    }
}
?>
