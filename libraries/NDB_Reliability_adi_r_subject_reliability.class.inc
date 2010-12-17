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
  function adi_r_subject_reliability()
  {
    $this->create_form();
  }
}