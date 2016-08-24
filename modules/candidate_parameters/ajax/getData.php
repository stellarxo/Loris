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
    $options = $db->pselect(
        "SELECT ID, Description FROM caveat_options",
        array()
    );
    foreach($options as $row) {
        $caveat_options[$row['ID']] = $row['Description'];
    }

    // get pscid
    $pscid = $db->pselectOne(
        'SELECT PSCID FROM candidate WHERE CandID = :candid',
        array('candid' => $candID)
    );

    $flag = $db->pselectOne(
        'SELECT flagged_caveatemptor FROM candidate WHERE CandID = :candid',
        array('candid' => $candID)
    );

    $reason = $db->pselectOne(
        'SELECT flagged_reason FROM candidate WHERE CandID = :candid',
        array('candid' => $candID)
    );

    $other = $db->pselectOne(
        'SELECT flagged_other FROM candidate WHERE CandID = :candid',
        array('candid' => $candID)
    );



    $result = [
        'pscid' => $pscid,
        'candID' => $candID,
        'caveatReasonOptions' => $caveat_options,
        'flagged_caveatemptor' => $flag,
        'flagged_reason' => $reason,
        'flagged_other' => $other
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

    $gender = $db->pselectOne(
        'SELECT ProbandGender FROM candidate where CandID = :candid',
        array('candid' => $candID)
    );

    $dob = $db->pselectOne(
        'SELECT ProbandDoB FROM candidate where CandID = :candid',
        array('candid' => $candID)
    );

    // Calculate age difference
    $ageDifference = "Could not calculate age";
    $candidateDOB = $db->pselectOne(
        "SELECT DoB FROM candidate WHERE CandID=:CandidateID",
        array('CandidateID' => $candID));
    if (!empty($candidateDOB) && !empty($dob)) {
        $age = Utility::calculateAge($dob, $candidateDOB);

        if ($age !== null) {
            $ageDifference = $age['year'] * 12 + $age['mon'] + round($age['day'] / 30, 2);
        }
    }

    $result = [
        'pscid' => $pscid,
        'candID' => $candID,
        'ProbandGender' => $gender,
        'ProbandDoB' => $dob,
        'ageDifference' => $ageDifference
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

    $candidatesList  = $db->pselect(
        "SELECT CandID FROM candidate ORDER BY CandID",
        array()
    );

    $candidates = array();
    // Remove own ID from list of possible family members
    foreach ($candidatesList as $key => $candidate) {
        foreach ($candidate as $ID) {
            if ($ID == $candID) {
                unset($candidatesList[$key]);
            }
            else {
                $candidates[$ID] = $ID;
            }
        }
    }

    $familyCandID = $db->pselectOne(
        "SELECT CandID FROM family WHERE FamilyID=(SELECT FamilyID FROM family WHERE CandID = :candid) AND CandID <> :candid2",
        array('candid' => $candID, 'candid2' => $candID)
    );

    $relationship = $db->pselectOne(
        "SELECT Relationship_type FROM family WHERE FamilyID=(SELECT FamilyID FROM family WHERE CandID = :candid) AND CandID <> :candid2",
        array('candid' => $candID, 'candid2' => $candID)
    );

    $result = [
        'pscid' => $pscid,
        'candID' => $candID,
        'candidates' => $candidates,
        'familyCandID' => $familyCandID,
        'Relationship_type' => $relationship
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

    $statusOptions = getParticipantStatusOptions();
    $reasonOptions = array();

    $required = $db->pselect('SELECT ID from participant_status_options where Required=1', array());
    $parentIDs = $db->pselect('SELECT distinct(parentID) from participant_status_options', array());
    $parentIDMap = array();

    foreach ($parentIDs as $ID) {
        $reasonOptions = array();
        foreach ($ID as $parentID) {
            if ($parentID != null) {
                $options = $db->pselect(
                    "SELECT ID, Description FROM participant_status_options WHERE parentID=:pid",
                    array('pid' => $parentID)
                );
                foreach ($options as $option) {
                    $reasonOptions[$option['ID']] = $option['Description'];
                }
                $parentIDMap[$parentID] = $reasonOptions;
            }
        }
    }

    $status = $db->pselectOne("SELECT participant_status FROM participant_status WHERE CandID=:candid", array('candid' => $candID));
    $suboption = $db->pselectOne("SELECT participant_suboptions FROM participant_status WHERE CandID=:candid", array('candid' => $candID));
    $reason = $db->pselectOne("SELECT reason_specify FROM participant_status WHERE CandID=:candid", array('candid' => $candID));

    $result = [
        'pscid' => $pscid,
        'candID' => $candID,
        'statusOptions' => $statusOptions,
        'required' => $required,
        'reasonOptions' => $reasonOptions,
        'parentIDs' => $parentIDMap,
        'participant_status' => $status,
        'participant_suboptions' => $suboption,
        'reason_specify' => $reason
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

    $consent = $db->pselectOne('SELECT study_consent FROM participant_status WHERE CandID=:candid', array('candid' => $candID));
    $date = $db->pselectOne('SELECT study_consent_date FROM participant_status WHERE CandID=:candid', array('candid' => $candID));
    $withdrawal = $db->pselectOne('SELECT study_consent_withdrawal FROM participant_status WHERE CandID=:candid', array('candid' => $candID));

    $result = [
        'pscid' => $pscid,
        'candID' => $candID,
        'study_consent' => $consent,
        'study_consent_date'   => $date,
        'study_consent_withdrawal'   => $withdrawal
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
