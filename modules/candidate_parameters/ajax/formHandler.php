<?php

if (isset($_POST['tab'])) {
    $action = $_POST['tab'];
    var_dump($action);
    if ($action == "candidateInfo") {
        editCandInfoFields();
    }
    else if ($action == "probandInfo") {
        editProbandInfoFields();
    }
    else if ($action == "familyInfo") {
        editFamilyInfoFields();
    }
    else if ($action == "participantStatus") {
        editParticipantStatusFields();
    }
    else if ($action == "consentStatus") {
        editConsentStatusFields();
    } else {
        header("HTTP/1.1 404 Not Found");
        exit;
    }
}

function editCandInfoFields() {
    echo 'edit info';
    $db   =& Database::singleton();
    $user =& User::singleton();
    if (!$user->hasPermission('candidate_parameter_edit')) {
        header("HTTP/1.1 403 Forbidden");
        exit;
    }

    $candID = $_POST['candID'];

    // Process posted data
    $caveatEmptor   = isset($_POST['flagged_caveatemptor']) ? $_POST['flagged_caveatemptor'] : null;
    $reason    = isset($_POST['flagged_reason']) ? $_POST['flagged_reason'] : null;
    $other    = isset($_POST['flagged_other']) ? $_POST['flagged_other'] : null;

    $updateValues = [
        'flagged_caveatemptor' => $caveatEmptor,
        'flagged_reason'   => $reason,
        'flagged_other'  => $other
    ];

    $db->update('candidate', $updateValues, ['CandID' => $candID]);
}

function editProbandInfoFields() {
    $db   =& Database::singleton();
    $user =& User::singleton();
    if (!$user->hasPermission('candidate_parameter_edit')) {
        header("HTTP/1.1 403 Forbidden");
        exit;
    }

    $candID = $_GET['candID'];

    // Process posted data
    $gender   = isset($_POST['ProbandGender']) ? $_POST['ProbandGender'] : null;
    $dob    = isset($_POST['ProbandDoB']) ? $_POST['ProbandDoB'] : null;
    $dob2    = isset($_POST['ProbandDoB2']) ? $_POST['ProbandDoB2'] : null;

    if ($dob !== $dob2) {
        // throw error
    }

    $updateValues = [
        'ProbandGender' => $gender,
        'ProbandDoB'   => $dob
    ];

    $db->update('candidate', $updateValues, ['CandID' => $candID]);
}

function editFamilyInfoFields() {
    $db   =& Database::singleton();
    $user =& User::singleton();
    if (!$user->hasPermission('candidate_parameter_edit')) {
        header("HTTP/1.1 403 Forbidden");
        exit;
    }

    $candID = $_GET['candID'];

    // Process posted data
    $siblingCandID   = isset($_POST['CandID']) ? $_POST['CandID'] : null;
    $relationship    = isset($_POST['Relationship_type']) ? $_POST['Relationship_type'] : null;

    // find family ID!!!!!!!!!!!

    $updateValues = [
        'CandID' => $siblingCandID,
        'Relationship_type'   => $relationship
    ];

    $db->update('family', $updateValues, ['CandID' => $candID]);
}

function editParticipantStatusFields() {
    $db   =& Database::singleton();
    $user =& User::singleton();
    if (!$user->hasPermission('candidate_parameter_edit')) {
        header("HTTP/1.1 403 Forbidden");
        exit;
    }

    $candID = $_GET['candID'];

    // Process posted data
    $status   = isset($_POST['participant_status']) ? $_POST['participant_status'] : null;
    $suboption    = isset($_POST['participant_suboptions']) ? $_POST['participant_suboptions'] : null;
    $reason    = isset($_POST['reason_specify']) ? $_POST['reason_specify'] : null;

    $updateValues = [
        'participant_status' => $status,
        'participant_suboptions'   => $suboption,
        'reason_specify'   => $reason
    ];

    $db->update('participant_status', $updateValues, ['CandID' => $candID]);
}

function editConsentStatusFields() {
    $db   =& Database::singleton();
    $user =& User::singleton();
    if (!$user->hasPermission('candidate_parameter_edit')) {
        header("HTTP/1.1 403 Forbidden");
        exit;
    }

    $candID = $_GET['candID'];

    // Process posted data
    $consent   = isset($_POST['study_consent']) ? $_POST['study_consent'] : null;
    $date    = isset($_POST['study_consent_date']) ? $_POST['study_consent_date'] : null;
    $date2    = isset($_POST['study_consent_date2']) ? $_POST['study_consent_date2'] : null;
    $withdrawal    = isset($_POST['study_consent_withdrawal']) ? $_POST['study_consent_withdrawal'] : null;
    $withdrawal2    = isset($_POST['study_consent_withdrawal2']) ? $_POST['study_consent_withdrawal2'] : null;

    if ($date !== $date2) {
        // throw error
    }
    if ($withdrawal !== $withdrawal2) {
        // throw error
    }

    $updateValues = [
        'study_consent' => $consent,
        'study_consent_date'   => $date,
        'study_consent_withdrawal'   => $withdrawal
    ];

    $db->update('participant_status', $updateValues, ['CandID' => $candID]);
}