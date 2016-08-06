<?php
/**
 * Created by PhpStorm.
 * User: stellalee
 * Date: 2016-08-03
 * Time: 4:09 PM
 */

if (isset($_GET['data'])) {
    $data = $_GET['data'];
//    if ($data == "candidateInfo") {
        echo json_encode(getUploadFields());
//    }
}

function getUploadFields() {

    $candID = $_GET['candID'];

    $db =& Database::singleton();
//    $config =& NDB_Config::singleton();
//    $candidate =& Candidate::singleton($candID);

    // get caveat options
    $caveat_options = [];
    $options = $db->pselect("SELECT ID, Description FROM caveat_options");
    foreach($options as $row) {
        $caveat_options[$row['ID']] = $row['Description'];
    }

    // get pscid
    $pscid = $db->pselectOne(
        'SELECT PSCID FROM candidate where CandID = :candid',
        array('candid' => $candID)
    );

    $result = [
        'pscid' => $pscid,
        'candID' => $candID,
        'caveatOptions' => $caveat_options
    ];

    return $result;
}