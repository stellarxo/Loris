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
    else {
        header("HTTP/1.1 404 Not Found");
        exit;
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
//    $pid = $_GET['p_status'];

    $db =& Database::singleton();

    // get pscid
    $pscid = $db->pselectOne(
        'SELECT PSCID FROM candidate where CandID = :candid',
        array('candid' => $candID)
    );

    $statusOptions = getParticipantStatusOptions();

    $parentID = $db->pselectOne('SELECT participant_status FROM participant_status Where CandID = :candid',
        array('candid' => $candID));
    $reasonOptions = getParticipantStatusSubOptions($parentID);

    $result = [
        'pscid' => $pscid,
        'candID' => $candID,
        'statusOptions' => $statusOptions,
        'reasonOptions' => $reasonOptions
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

    // UPDATE THIS

    $result = [
        'pscid' => $pscid,
        'candID' => $candID
    ];

    return $result;
}

/**
 * Gets the participant_status options from participant_status_options
 * getParticipantStatusOptions()
 *
 * @return array Options array suitable for use in QuickForm select
 *               element
 */
function getParticipantStatusOptions()
{
    $DB =& Database::singleton();
    $options = $DB->pselect(
        "SELECT ID,Description FROM participant_status_options WHERE parentID IS NULL",
        array()
    );
    $option_array = array();
    foreach ($options as $option) {
        $option_array[$option['ID']] = $option['Description'];
    }
    return $option_array;
}

/**
 * Gets the participant_status options suboptions from participant_status_options
 * getParticipantStatusSubOptions()
 *
 * @return array Options array suitable for use in QuickForm select
 *               element
 */
function getParticipantStatusSubOptions($parentID)
{
    $DB =& Database::singleton();
    $options = $DB->pselect(
        "SELECT ID,Description FROM participant_status_options WHERE parentID=:pid",
        array('pid'=>$parentID)
    );
    $option_array = array();
    foreach ($options as $option) {
        $option_array[$option['ID']] = $option['Description'];
    }
    return $option_array;
}