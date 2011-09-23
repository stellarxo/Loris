#!/bin/bash
for i in ../instruments/NDB_BVL_Instrument_*; do 
    instrument=`echo $i | sed -e 's#\.\./instruments/NDB_BVL_Instrument_\(.*\)\.class\.inc#\1#'`
    ./double_data_entry_conflict_detector.php $instrument
done