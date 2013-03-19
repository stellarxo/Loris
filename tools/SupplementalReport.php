<?
set_include_path(get_include_path().":../libraries:../../php/libraries:");
require_once "NDB_Client.class.inc";
require_once "Utility.class.inc";
require_once "ProjectUtility.class.inc";

$client = new NDB_Client();
$client->makeCommandLine();
$client->initialize('../config.xml');

$DB =& Database::singleton();
$candidates = $DB->pselect("SELECT c.PSCID, c.Gender, s.SubprojectID, c.CandID, s.Visit_label  FROM session s JOIN candidate c USING (CandID) WHERE s.Active='Y' and c.Active='Y' AND c.PSCID <> 'scanner' AND c.ProjectID=1 AND ((s.SubprojectID IN (1, 3) AND s.Visit_label='V06') OR (s.SubprojectID=2 AND s.Visit_label='V12')) AND c.CenterID <> 1 ORDER BY PSCID", array());

function GetInstrumentData($instrument, $candid, $visit) {
    global $DB;
    $row = $DB->pselectRow("SELECT i.* from flag f 
        JOIN $instrument i USING(CommentID) 
        JOIN session s ON (s.ID=f.SessionID) 
        JOIN candidate c ON (s.CandID=c.CandID) 
        WHERE s.Visit_label=:VL 
            AND CommentID NOT LIKE 'DDE%' 
            AND s.CandID=:CID
            AND s.Active='Y' AND c.Active='Y'", 
            array('VL' => $visit, 'CID' => $candid)
        );
    return $row;
}

function GetGrantStatus($candid, $visit) {
    global $DB;
    $SessionID = $DB->pselectOne("SELECT s.ID FROM session s JOIN candidate c USING (CandID) WHERE CandID=:CID AND Visit_label=:VL AND s.Active='Y' AND c.Active='Y'",
        array('CID' => $candid, 'VL' => $visit)
    );

    if(is_numeric($SessionID)) {
        return ProjectUtility::GetSupplementalGrantStatus($SessionID);
    } else {
        return 'No session created';
    }
}
$filename = '';
// PSCID, Gender, SubprojectID, child_ethnicity, candidate_race, FYI_V12_Risk, ADI_R_Subject_V24_Date, ADI_R_Summary, Grant_Status_V12, Grant_Status_V24
$lastsite = '';
foreach($candidates as &$c) {
    $site = substr($c['PSCID'], 0, 3);
    if($lastsite === '' || $site != $lastsite) {
        print "Site is now: $site\n";

        if(isset($fp) && $fp > 0) {
            fclose($fp);
        }
        $fp = fopen("Supplemental_$site.csv", "w");
        fputcsv($fp, array('PSCID', 'Gender', 'Subproject', 'child_ethnicity', 'candidate_race', 'FYI_V12_Risk', 'ADI-R_Subject_V24_Date', 'ADI-R_Subject_Summary', 'Grant_Status_V12', 'Grant_Status_V24'));

    }
    $lastsite = $site;

    $row = array($c['PSCID'], $c['Gender'], $c['SubprojectID']);
    switch($c['SubprojectID']) {
    case 1:
        $row[] = '6 Month Recruit';
        break;
    case 2:
        $row[] = '12 Month Recruit';
        break;
    case 3:
        $row[] = 'Control';
        break;
    default:
        $row[] = 'Unknown Cohort';
        break;
    }
    $tsi = GetInstrumentData("tsi", $c['CandID'], $c['Visit_label']);
    $row[] = $tsi['child_ethnicity'];
    $row[] = $tsi['candidate_race'];
    $fyi = GetInstrumentData("fyi", $c['CandID'], 'V12');
    $row[] = $fyi['risk_score'];
    $adi_r = GetInstrumentData("adi_r_subject", $c['CandID'], 'V24');
    $row[] = $adi_r['Date_taken'];
    $row[] = $adi_r['summary_diagnosis'];

    $row[] = GetGrantStatus($c['CandID'], 'V12');
    $row[] = GetGrantStatus($c['CandID'], 'V24');

    fputcsv($fp, $row);
}
fclose($fp);
?>
