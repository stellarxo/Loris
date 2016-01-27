<?php
/**
 * OVERRIDDEN BY IBIS SO THAT IBISID CAN BE GENERATED.
 * ALSO, TO MAKE IBIS2 CANDIDATES START WITH "1".
 * ALSO, TO HANDLE CANDIDATE PLAN FOR IBIS2
 *
 * Candidate class
 * @package main
 */

//require_once("Site.class.inc");
require_once("PEAR.php");

// error codes
define('CANDIDATE_INVALID', 1);
define('PSCID_NOT_SPECIFIED', 2);
define('PSCID_NOT_UNIQUE', 3);
define('PSCID_INVALID_STRUCTURE', 4);

// id ranges...
define('CANDIDATE_MIN_CANDID', 100000);
define('CANDIDATE_MAX_CANDID', 999999);
define('CANDIDATE_MIN_PSCID', 1000);
define('CANDIDATE_MAX_PSCID', 9999);

class Candidate
{
    var $candidateInfo;
    var $listOfTimePoints;

    function &singleton($candID)
    {
        $candidateList =& $GLOBALS['__candidateObjects'];
        if(!isset($candidateList[$candID])) {
            $candidateList[$candID] = new Candidate();
            $success = $candidateList[$candID]->select($candID);

        }

        return $candidateList[$candID];
    }
    
    function select($candID)
    {
        // right off, set the candID
        $candID = trim($candID);
        $config = NDB_Config::singleton();
        // make a local reference to the Database object
        $db = Database::singleton();

        // get candidate data from database
        $query = "SELECT c.CenterID, c.CandID, c.PSCID, c.DoB, c.EDC, c.Gender, p.Name AS PSC, c.Ethnicity, c.Active, u1.Real_name as RegisteredBy, c.UserID, c.Entity_type, c.ProjectID FROM candidate as c left join psc as p using (CenterID) left join users as u1 on (u1.UserID = c.RegisteredBy) WHERE c.CandID='$candID' AND c.Active = 'Y'";
        $row = array();
        $db->selectRow($query, $row);
        

        if (!is_array($row) || sizeof($row) == 0) {
            throw new LorisException("Could not select Candidate data from the database (DCCID: $candID)", 
                                     CANDIDATE_INVALID);
        }

        // store user data in object property
        foreach($row AS $key=>$value) {
            $this->candidateInfo[$key] = $value;
        }
        
        if ($config->getSetting('useProjects') === 'true') {
            $this->candidateInfo['ProjectTitle'] = $this->getProjectTitle();
        }
        $headerSetting = $config->getSetting('HeaderTable');
        if (!empty($headerSetting)) {
            $params = array();
            $parameterCandSettings = $headerSetting['parameter_candidate'];
            if (!is_array($parameterCandSettings)) {
                $parameterCandSettings = array($parameterCandSettings);
            }
            foreach ($parameterCandSettings as $parameter_type) {
                $row = $db->pselectRow(
                        "SELECT Value, pt.Description
                        FROM candidate c
                        JOIN parameter_candidate pc ON (pc.CandID=c.CandID)
                        LEFT JOIN parameter_type pt ON
                        (pc.ParameterTypeID=pt.ParameterTypeID)
                        WHERE c.CandID=:Candidate AND pt.Name=:PTName",
                        array(
                            'Candidate' => $candID,
                            'PTName'    => $parameter_type,
                            )
                        );
                if (!empty($row['Value'])) {
                    $params[$row['Description']] = $row['Value'];
                }
            }
            $this->candidateInfo['DisplayParameters'] = $params;
        }

        // check that PSCID matches CandID when entered into the boxes
        // on the candidate_list form (and is therefore trying to open
        // the timepoint_list page, which is why the if statement checks
        // for timepoint_list instead of candidate_list)
        //
        // Since other pages (ie. the filter in the conflicts_resolve page)
        // might include an element named PSCID, we also need to check that
        // the test_name matches before throwing the error.
        if (isset($_REQUEST['PSCID'])
            && (isset($_REQUEST['test_name'])
            && $_REQUEST['test_name']=='timepoint_list')
        ) {
            if (strtolower(
                trim($_REQUEST['PSCID'])
            ) != strtolower($this->getPSCID())
            ) {
                throw new Exception("IDs do not match");
            }
        }

        // get Time Point SessionIDs for the $candID
        // select ALL of them - later you can filter out cancelled and inactive ones
        $query = "SELECT s.ID FROM session as s WHERE s.CandID='$candID' AND s.Active='Y' ORDER BY ID";
        $db->select($query, $row);


        // store user data in object property
        foreach($row AS $value) {
            $this->listOfTimePoints[] = $value["ID"];
        }
   }
   
   /**
   * creates a new candidate, assigning CandID and PSCID - MUST be called statically
   *
   * @param int    $centerID    centerID of the site to which the candidate will belong
   * @param string $dateOfBirth date of birth written as YYYY-MM-DD
   * @param string $edc         estimated date of confinement written as YYYY-MM-DD
   * @param string $gender      gender, either 'Male' or 'Female'
   * @param string $PSCID       PSCID specified by the user, if available
   * @return int   $candID      candidate id of the new candidate
   * @throws PEAR::Error
   * @static
   */
   function createNew($centerID, $dateOfBirth, $edc, $gender, $PSCID=null, $startNumber=0)
   {
       if(!empty($this->candidateInfo['candID'])) {
           throw new LorisException("createNew must be called statically");
       }
       
       $db =& Database::singleton();
       
       $site =& Site::singleton($centerID);
       
       $user =& User::singleton($_SESSION['State']->getUsername());
       
       // generate candid
       $candID = Candidate::_generateCandID();

       // figure out how to generate PSCID
       $config =& NDB_Config::singleton();
       $PSCIDSettings = $config->getSetting('PSCID');


       if($PSCIDSettings['generation'] == 'user') {
           // check pscid is specified
           if(empty($PSCID)) {
               throw new LorisException("PSCID must be specified", PSCID_NOT_SPECIFIED);
           }

           // check pscid structure
           if(!Candidate::validatePSCID($PSCID, $site->getSiteAlias())) {
               throw new LorisException("PSCID has an invalid structure", PSCID_INVALID_STRUCTURE);
           }

           // check pscid uniqueness
           if($db->selectOne("SELECT count(PSCID) FROM candidate WHERE PSCID='$PSCID'") > 0) {
               throw new LorisException("PSCID not unique", PSCID_NOT_UNIQUE);
           }
       } else {           
           $PSCID = Candidate::_generatePSCID($site->getSiteAlias(), $startNumber);
       }
       
       $ibisid = Candidate::_generateID("IBIS");
       $drexid = Candidate::_generateID("DREX");
       
       // insert the new candidate into the database
       $setArray = array('CandID'       => $candID,
                         'CenterID'     => $centerID,
                         'PSCID'        => $PSCID,
                         'DoB'          => $dateOfBirth,
                         'EDC'          => $edc,
                         'Gender'       => $gender,
                         'Date_active'  => date('Y-m-d'),
                         'Date_registered' => date('Y-m-d'),
                         'Entity_type'  => 'Human',
                         'RegisteredBy' => $user->getUsername(),
                         'UserID'       => $user->getUsername(),
                         'IBISID'       => $ibisid,
                         'DREXID'       => $drexid
                         );
       
       $db->insert('candidate', $setArray);
       
       // return the new candid
       return $candID;
   }

    /**
     * @return array list of SessionIDs w/ 1st Time Point indexed to 0
     */
    function getListOfTimePoints()
    {
        return $this->listOfTimePoints;
    }

    /**
     * @return array with SessionIDs w/ 1st Time Point indexed to 0
     */
    function getSessionID($visitNo)
    {
        return $this->listOfTimePoints[$visitNo-1];
    }

    function getData($var = null)
    {
        if (is_null($var)) {
            return $this->candidateInfo;
        }
        else {
            return $this->candidateInfo[$var];
        }
    }

    function setData($var, $value=null)
    {
        if(!is_array($var)) {
            $setData = array($var=>$value);
        } else {
            $setData = $var;
        }

        $this->candidateInfo = array_merge($this->candidateInfo, $setData);

        $db =& Database::singleton();
        $success = $db->update('candidate', $setData, array('CandID'=>$this->getData('CandID')));
        return true;
    }

    function getProjectID()
    {
        return $this->candidateInfo["ProjectID"];
    }
   /**
     * Returns the name of the candidate's project from the
     * config file
     *
     * @return string Project name
     */
    function getProjectTitle()
    {
        $ProjectList = Utility::getProjectList();
        return $ProjectList[$this->getProjectID()];
    }

   function getCandID()
    {
        return $this->candidateInfo["CandID"];
    }


    function getPSCID()
    {
        return $this->candidateInfo["PSCID"];
    }

    function getCandidateSite()
    {
        return $this->candidateInfo["PSC"];
    }
    
    function getCenterID()
    {
        return $this->candidateInfo["CenterID"];
    }

    function getCandidateDoB()
    {
        return $this->candidateInfo["DoB"];
    }

    function getCandidateEDC()
    {
        return $this->candidateInfo["EDC"];
    }

    function getCandidateGender()
    {
        return $this->candidateInfo["Gender"];
    }

    function getCandidateEthnicity()
    {
        return $this->candidateInfo["Ethnicity"];
    }

    function getCandidateZIP()
    {
        return $this->candidateInfo["ZIP"];
    }

    function isActive()
    {
        return $this->candidateInfo["Active"];
    }

    function registeredBy()
    {
        return $this->candidateInfo["RegisteredBy"];
    }

    function lastRecordChangeBy()
    {
        return $this->candidateInfo["UserID"];
    }
    
    /**
     * returns the list of visit labels w/ corresponding SessionID (session.ID field) as key
     *@return array $visitLabelArray - format SessionID=>Visit_label
     *@throws PEAR:Error
     */
    function getListOfVisitLabels()
    {
        //make sure it returns an array
        $visitLabelArray = array();

        $candID=$this->getCandID();
       // make a local reference to the Database object
        $db =& Database::singleton();

        $query  = "SELECT ID, Visit_label FROM session WHERE CandID='$candID' AND Active='Y' ORDER BY ID";
        $db->select($query, $result);

        // map the array [VisitNo]=>Visit_label
        foreach ($result as $row) {
            $visitLabelArray[$row["ID"]] = $row["Visit_label"];
        }
        return $visitLabelArray;
    }
    
    function getFirstVisit() {
        $candID = $this->getCandID();
        $db =& Database::singleton();

        $query  = "SELECT Visit_label FROM session s JOIN candidate c ON (c.CandID = s.CandID)
            WHERE c.CandID=:cid AND Visit_label NOT LIKE '%Screening%' AND Date_Visit IS NOT NULL
            ORDER BY Date_Visit";
        $where  = array('cid'=>$candID);
        $vLabel = $db->pselectOne($query, $where);

        return $vLabel;
    }

    /**
     * return the next visit number for the time point you are
     * trying to register
     * can be called statically
     *@throws PEAR:Error
     */
    function getNextVisitNo()
    {
        $candID=$this->getCandID();
        // make a local reference to the Database object
        $db =& Database::singleton();

        $query  = "SELECT IFNULL(max(VisitNo)+1, 1) AS nextVisitNo FROM session WHERE CandID='$candID' AND (Active='Y' OR Active is null) GROUP BY CandID";
        $db->selectRow($query, $result);
        
        //return the next visit No
        return $result["nextVisitNo"];
    }

    /**
     * return the suggested visit label for the time point you are
     * trying to register
     * can be called statically
     *@throws PEAR:Error
     */
    function getNextVisitLabel()
    {
        $config =& NDB_Config::singleton();
        $visitLabelSettings = $config->getSetting('visitLabel');
        
        $candID=$this->getCandID();
        // make a local reference to the Database object
        $db =& Database::singleton();

        if($visitLabelSettings['generation'] == 'user' && !empty($visitLabelSettings['suggest'])) {
            $existingVisitLabels = $this->getListOfVisitLabels();
            $query  = "SELECT IFNULL(max(VisitNo)+1, 1) AS nextVisitLabel FROM session WHERE CandID='$candID' AND (Active='Y' OR Active is null) GROUP BY CandID";
            $db->selectRow($query, $result);
    
            $nextVisitLabel = $result['nextVisitLabel'];
            if(!empty($existingVisitLabels)){
                while(in_array($nextVisitLabel, $existingVisitLabels)) {
                    $nextVisitLabel++;
                }
            } else {
                // display V1 as a suggested visit label when starting the 1st timepoint
                $nextVisitLabel = '1';
            }
            
            $nextVisitLabel = str_replace('%value%', $nextVisitLabel, $visitLabelSettings['suggest']);
        }
        
        //return the next visit No
        return $nextVisitLabel;
    }
    function getCandidatePlan()
    {
	    $candID=$this->getCandID();
	    // make a local reference to the Database object
	    $db =& Database::singleton();
	    $query = "SELECT Value as Plan FROM candidate c JOIN parameter_candidate pc ON (pc.CandID=c.CandID) LEFT JOIN parameter_type pt ON (pc.ParameterTypeID=pt.ParameterTypeID) WHERE c.CandID=:CandidateID AND pt.Name='candidate_plan';";
        $params = array('CandidateID'=>$candID);
        $plan = $db->pselectOne($query, $params);
	    return $plan;

    }    
    /**
    * generates a new random CandID
    * @static
    * @return int
    * @throws PEAR::Error
    */
    function _generateCandID()
    {
        // get a database connection
        $db =& Database::singleton();
        
        // generate a candidate id
        $candID = rand(CANDIDATE_MIN_CANDID, CANDIDATE_MAX_CANDID);
        
        // make sure the cand id is not used
        while($db->selectOne("SELECT count(CandID) FROM candidate WHERE CandID='$candID'") > 0) {
            // pick a new candidate id
            $candID = rand(CANDIDATE_MIN_CANDID, CANDIDATE_MAX_CANDID);
        }
        
        return $candID;
    }  

    /**
    * generates a new random PSCID
    * @param string $prefix  the prefix to use for the PSCID
    * @static
    * @return string
    * @throws PEAR::Error
    */
    function _generatePSCID($prefix, $startNumber)
    {
        // The generatePSCID() function is confusing and I don't fully understand it, but
        // from what I understand it generates an array with a list of possible values for
        // each digit/section of the PSCID based on the config.xml. 
        // generateFirst/RandomStringFromArrays then concatenates the first option (or a random one)
        // from each together to get a valid PSCID, and then checks if it already exists in the database
        // If it does, it increments the number until it gets a unique PSCID.
        // - Dave
        $db =& Database::singleton();
        
        $config =& NDB_Config::singleton();
        $PSCIDSettings = $config->getSetting('PSCID');
        $pscidArrays = Candidate::generateArrays($PSCIDSettings, $prefix);

        // If IBIS2, take "0" out of the possibilities for the first digit of the numbers.
        if($startNumber == 1000) {
            $pscidArrays[1] = array(1, 2, 3, 4, 5, 6, 7, 8, 9);
        }
        // run one first time, then loop until the pscid is not used
        do {
            // pick a new pscid
            if($PSCIDSettings['generation'] == 'sequential') {
                if(!empty($pscid)) {
                    $pscid++;
                } else {
                    $pscid = Candidate::generateFirstStringFromArrays($pscidArrays);
                }
            } else {
                $pscid = Candidate::generateRandomStringFromArrays($pscidArrays);
            }
            
            // check if the pscid is used
        } while($db->selectOne("SELECT count(PSCID) FROM candidate WHERE PSCID='$pscid'") > 0);
        
        return $pscid;
    }

    function _generateID($ID) {
        $db =& Database::singleton();

        do {
            $randid = $ID . rand(1000, 9999);
            $randidq = $db->quote($randid);
            $nid = $ID . "ID";
        } while($db->selectOne("SELECT count($nid) FROM candidate WHERE `$nid`=$randidq") > 0);
        return $randid;
    }
    
    function validatePSCID($PSCID, $siteAbbrev=null)
    {
        $config =& NDB_Config::singleton();
        $PSCIDSettings = $config->getSetting('PSCID');
        $regex = Utility::structureToPCRE($PSCIDSettings['structure'], $siteAbbrev);
        return preg_match($regex, $PSCID);
    }


    function generateRandomStringFromArrays($arrays)
    {
        $string = "";
        foreach($arrays AS $array) {
            if(is_array($array))
                $string .= $array[array_rand($array)];
            else
                $string .= $array;
        }
        return $string;
    }

    function generateFirstStringFromArrays($arrays)
    {
        $string = "";
        foreach($arrays AS $array) {
            $string .= array_shift($array);
        }
        return $string;
    }

    function generateArrays($idStructure, $siteAbbrev=null)
    {
        $idStructure = $idStructure['structure']['seq'];

        $arrays = array();
        foreach($idStructure AS $seq) {
            if(isset($seq['@']['length'])) {
                $length = $seq['@']['length'];
            } elseif(isset($seq['@']['minLength'])) {
                $length = $seq['@']['minLength'];
            } else {
                $length = 1;
            }

            for($i=0; $i<$length; $i++) {
                switch($seq['@']['type']) {
                case 'alpha':
                    $arrays[] = range('a','z');
                    break;
                
                case 'alphanumeric':
                    $arrays[] = array_merge(range(0, 9), range('a', 'z'));
                    break;
                
                case 'numeric':
                    $arrays[] = range(0, 9);
                    break;
                
                case 'static':
                    $arrays[] = array($seq['#']);
                    break;

                case 'set':
                    if(strpos($seq['#'], '|') !== false) {
                        $arrays[] = explode('|', $seq['#']);
                    } else {
                        $arrays[] = str_split($seq['#']);
                    }
                    break;

                case 'siteAbbrev':
                    $arrays[] = array($siteAbbrev);
                    break;
                }
            }
        }

        return $arrays;
    }
    /**
     * generates list of valid subprojects for a given project id
     * @static
     * @return array
     * @throws Utility::isErrorX
     */
    function getValidSubprojects()
    {
        $projID = $this->getProjectID();
        $db =& Database::singleton();
        $query  = "SELECT SubprojectID from project_rel where ProjectID = :prj";
        $params = array('prj'=>$projID);
        $subproj   = $db->pselect($query, $params);
        foreach($subproj as $row){
            foreach($row as $key =>$val){
                if($key == 'SubprojectID') {
                    $subprojList[$val] = $val;
                }
            }
        }
        return $subprojList;
    }


    static function candidateExists($candID, $PSCID)
    {   
        // make a local reference to the Database object
        $factory = NDB_Factory::singleton();
        $db      = $factory->database();

        $candidateIDs = array(
                         ':candidate_id' => $candID,
                         ':pscid'        => $PSCID,
                        );  

        // get candidate data from database
        $query = "SELECT CandID
            FROM candidate
            WHERE CandID = :candidate_id AND PSCID = :pscid
            AND Active = 'Y'";

        $row = $db->pselectRow($query, $candidateIDs);

        if (!empty($row)) {
            return true;
        }   

        return false;

    }   

}
?>
