<?php
/**
 * Takes a CSV and converts various formatting things
 * that NDAR requires to be done before submission, outputs
 * another CSV in the proper format.
 *
 * Namely, this script will:
 * - Remove Recycling Bin candidates from the CSV
 * - Remove Failed/Withdrawn candidates based on Visit or Screening flag
 * - Remove candidates where Administration = None, Partial or null
 * - Remove candidates where Data_entry is still In Progress
 * - Remove Control candidates
 * - Change the date format from YYYY-MM-DD to DD/MM/YYYY
 * - Remove any field ending with _status
 * - Change any "not_answered" entry to blank
 * - Replace any fields containing a lone . with a blank cell
 * - Change gender from m/f or Male/Female to M/F (capital)
 * - Replace yes/no with capital Yes/No
 * - Execute a script called NDARize/($filename).ndar.php to add instrument specific rules
 **/
if($_SERVER['argc'] != 2) {
    print "Usage:\tNDARize.php filename.csv\n";
    die(-1);
}
require_once("./NDARize/Base.ndar.php");

$file = $_SERVER['argv'][1];

// $fp = filepointer, $ofp = output filepointer
$fp = fopen($file, "r");
$ofp = fopen("$file.ndar.csv", "w");

$file_chunks = split("\.", $file);
print_r($instrument);
$instrument = $file_chunks[0];
$className = null;
/*
   if exists NDARize/proband.ndar.php and $file contains proband
     create proband class
   else 
     create subject class

 */
$headers_csv = fgetcsv($fp);
// Use the extended processor if it exists, otherwise the base one
// handles most cases.
if(file_exists("./NDARize/$instrument.ndar.php")) {
    require_once("./NDARize/$instrument.ndar.php");
    $className = $instrument . "NDAR";
    $Processor = new $className($headers_csv, $instrument);
} else {
    $Processor = new BaseNDAR($headers_csv, $instrument);
}

fputcsv($ofp, $Processor->getheaders());
while($csv_line = fgetcsv($fp))
{
    $line = $Processor->process($csv_line);
    if($line) {
        // Write out the CSV (unless it's empty)
        fputcsv($ofp, $line);

    }
}

// Close the files to make sure they get written/released
fclose($fp);
fclose($ofp);

?>
