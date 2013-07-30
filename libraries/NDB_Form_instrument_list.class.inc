<?php
require_once "NDB_Form.class.inc";

/**
 * The forms for the instrument list menu
 * @package main
 */
class NDB_Form_instrument_list extends NDB_Form
{
    function _hasAccess()
    {
        // create user object
        $user =& User::singleton();
        if(PEAR::isError($user)) {
            return PEAR::raiseError("User Error: ".$user->getMessage());
        }

        $timePoint =& TimePoint::singleton($_REQUEST['sessionID']);
        if (Utility::isErrorX($timePoint)) {
            return PEAR::raiseError("TimePoint Error (".$_REQUEST['sessionID']."): ".$timePoint->getMessage());
        }
        $candID = $timePoint->getCandID();

        $candidate =& Candidate::singleton($candID);
        if (Utility::isErrorX($candidate)) {
            return PEAR::raiseError("Candidate Error ($candID): ".$candidate->getMessage());
        }

        return ($user->hasPermission('access_all_profiles') || $user->getData('CenterID') == $candidate->getData('CenterID') || $user->getData('CenterID') == $timePoint->getData('CenterID'));

    }

    function _getDefaults()
    {
        $DB =& Database::singleton();
        if(isset($this->identifier))
        {
            $PTID = $DB->pselectOne("SELECT ParameterTypeID FROM parameter_type WHERE Name='VisitComment'",array());
            if(!is_numeric($PTID)) {
                return PEAR::raiseError("Missing ParameterTypeID for VisitComment");
            }

            $defaults['Comment'] = $DB->pselectOne("SELECT Value FROM parameter_session WHERE SessionID=:sid 
                                                    AND ParameterTypeID=:pid",
                                        array('sid'=>$this->identifier,'pid'=>$PTID));
        }
        return $defaults;
    }

    function _process($values)
    {
        $db = Database::singleton();
        $sessionID = $this->identifier;
        
        $timePoint =& TimePoint::singleton($sessionID);
        if (Utility::isErrorX($timePoint)) {
            return PEAR::raiseError("TimePoint Error (".$_REQUEST['sessionID']."): ".$timePoint->getMessage());
        }
        $candID = $timePoint->getCandID();

        $PTID = $db->pselectOne("SELECT ParameterTypeID FROM parameter_type WHERE Name='VisitComment'",array());
        if(!is_numeric($PTID)) {
            return PEAR::raiseError("Missing ParameterTypeID for VisitComment");
        }
        $result = $db->insert("parameter_session", array('ParameterTypeID' => $PTID,
                    'SessionID' => $sessionID,
                    'Value' => $values['Comment']
                    ));

        if (Utility::isErrorX($result)) {
            return PEAR::raiseError(
             "NDB_Form_instrument_list::_process: ".$result->getMessage()
            );
        }

        $this->tpl_data['success'] = true;
        $this->tpl_data['candID']  = $candID;
        $this->tpl_data['sessionID'] = $sessionID;

    }
    
    function instrument_list() {
       $this->form->addElement('textarea','Comment','Add Visit Comment:');        
     }
}
?>
