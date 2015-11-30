<?php
set_include_path(get_include_path().":../libraries:../../php/libraries:");

require_once "NDB_Client.class.inc";
require_once "Utility.class.inc";
require_once "Candidate.class.inc";

if (empty($argv[1])) {
    print "Usage: php create_new_ID_set.php PREFIX\n";
} else {

    $client = new NDB_Client();
    $client->makeCommandLine();
    $client->initialize('../config.xml');
    $DB = Database::singleton();

    $prefix = strtoupper($argv[1]);
    $nid = $prefix . "ID";
    $count = 0;

    $candidate_list = $DB->pselect("SELECT * FROM candidate where PSCID!='scanner' and $nid is null", array());

    foreach($candidate_list as $cand) {

        $newid = Candidate::_generateID($prefix);
        try {
            $result = $DB->update('candidate', array($nid => $newid), array('ID' => $cand['ID']));
            print ".";
            $count++;
        } catch (DatabaseException $ex) {
            print "Could not save new ID: ". $result->getMessage();
        }
    }        

    print "\n" . $count . " new IDs with prefix \"$prefix\" were inserted.\n";
}