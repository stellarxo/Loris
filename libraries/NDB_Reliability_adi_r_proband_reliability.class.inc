<?php
require_once "NDB_Reliability_adi_r_reliability.class.inc";
//require_once "NDB_BVL_Instrument.class.inc";

/**
 * The forms for the tracking log menu
 * @package mri
 * @subpackage NIHPD
 */
class NDB_Reliability_adi_r_proband_reliability extends NDB_Reliability_adi_r_reliability
{
    function _getAgeInMonths($instrument_record, $reliability_record) {
        $age = Utility::calculateAge($instrument_record['DoB_proband'], $instrument_record["Date_taken"]);
        $age_months = $age['year'] * 12 + $age['mon'];
        return $age_months;
    }

  function adi_r_proband_reliability()
  {
    $this->create_form();
  }
}
