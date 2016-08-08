<?php

if (isset($_GET['data'])) {
    $data = $_GET['data'];
    if ($data == "candidateInfo") {
        echo json_encode(getCandInfoFields());
    }
    else if ($data == "probandInfo") {
        echo json_encode(getProbandInfoFields());
    }
    else if ($data == "familyInfo") {
        echo json_encode(getFamilyInfoFields());
    }
    else if ($data == "participantStatus") {
        echo json_encode(getParticipantStatusFields());
    }
    else if ($data == "consentStatus") {
        echo json_encode(getConsentStatusFields());
    }
}

function getCandInfoFields() {
    $candID = $_GET['candID'];

    $db =& Database::singleton();

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

function getProbandInfoFields() {
    $candID = $_GET['candID'];

    $db =& Database::singleton();

    // get pscid
    $pscid = $db->pselectOne(
        'SELECT PSCID FROM candidate where CandID = :candid',
        array('candid' => $candID)
    );

    $result = [
        'pscid' => $pscid,
        'candID' => $candID
    ];

    return $result;
}

function getFamilyInfoFields() {
    $candID = $_GET['candID'];

    $db =& Database::singleton();

    // get pscid
    $pscid = $db->pselectOne(
        'SELECT PSCID FROM candidate where CandID = :candid',
        array('candid' => $candID)
    );

    $result = [
        'pscid' => $pscid,
        'candID' => $candID
    ];

    return $result;
}

function getParticipantStatusFields() {
    $candID = $_GET['candID'];

    $db =& Database::singleton();

    // get pscid
    $pscid = $db->pselectOne(
        'SELECT PSCID FROM candidate where CandID = :candid',
        array('candid' => $candID)
    );

    $result = [
        'pscid' => $pscid,
        'candID' => $candID
    ];

    return $result;
}

function getConsentStatusFields() {
    $candID = $_GET['candID'];

    $db =& Database::singleton();

    // get pscid
    $pscid = $db->pselectOne(
        'SELECT PSCID FROM candidate where CandID = :candid',
        array('candid' => $candID)
    );

    $result = [
        'pscid' => $pscid,
        'candID' => $candID
    ];

    return $result;
}