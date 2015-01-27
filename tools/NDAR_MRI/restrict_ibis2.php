<?php

$files = scandir("IBIS2");

$dbh = new PDO("mysql:host=localhost;dbname=loris", "root", "abc123!");
$stmt = $dbh->prepare("SELECT ProjectID, s.SubprojectID, c.CandID, c.IBISID FROM candidate c JOIN session s ON (lower(s.Visit_label)='v06' AND c.CandID=s.CandID) JOIN participant_status ps ON (c.CandID=ps.CandID) WHERE c.CandID=:dccid AND s.Active='Y' AND c.Active='Y' AND s.Current_stage <> 'Recycling Bin' AND COALESCE(c.CandidateGUID, '') <> ''
     AND ( ps.study_consent = 'yes' AND (COALESCE(ps.study_consent_withdrawal,'0000-00-00') = '0000-00-00' )) AND (ps.ndar_consent = 'yes' AND (COALESCE(ps.ndar_consent_withdrawal,'0000-00-00') = '0000-00-00'))");
foreach($files as $file) {
    $pieces = explode("_", $file);
    $idx = null;
    if($pieces[0] === 'render') {
        $idx = 2;
    } else if ($pieces[0] === 'deface') {
        $idx = 1;
    }
    if($idx) {
        $stmt->execute(array('dccid' => $pieces[$idx]));
        $result_all = $stmt->fetchAll(PDO::FETCH_ASSOC);
        $result = array();
        if(isset($result_all[0])) {
            $result = $result_all[0];
        } else {
            $result = array(
                'ProjectID' => 'Invalid',
                'IBISID' => 'Invalid'
            );
        }

        if($result['ProjectID'] === '2' &&
         (
             $result['SubprojectID'] === '9' ||
             $result['SubprojectID'] === '10'
         )
        ) {
            rename("IBIS2/$file", "IBIS2/Valid/$file");
        } else {
            rename("IBIS2/$file", "IBIS2/Invalid/$file");
        }
        print $file . ': ' . $result['IBISID'] . " " . $result['ProjectID'] . "\n";
    }
}
?>
