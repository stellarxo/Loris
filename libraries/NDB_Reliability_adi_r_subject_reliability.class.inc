<?php
require_once "NDB_Reliability_adi_r_reliability.class.inc";
//require_once "NDB_BVL_Instrument.class.inc";

/**
 * The forms for the tracking log menu
 * @package mri
 * @subpackage NIHPD
 */
class NDB_Reliability_adi_r_subject_reliability extends NDB_Reliability_adi_r_reliability
{
    function _getAgeInMonths($instrument_record, $reliability_record) {
        $CommentID = $instrument_record['CommentID'];
        $CandID = substr($CommentID, 0, 6);
        $candidate =& Candidate::singleton($CandID);
        $age = Utility::calculateAge($candidate->getCandidateDoB(), $instrument_record['Date_taken']);
        return $age['year'] * 12 + $age['mon'];
    }
  function adi_r_subject_reliability()
  {
    $this->create_form();
  }
}
