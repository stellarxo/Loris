<?
class BaseNDAR {

    // Headers is a normal array (0, 1, 2..) list of the header names, so that getheaders can work
    // HeadersMap is a mapping of headername => idx used by process
    // Headers_IDX is a list of col numbers which are to be returned so that array_intersect_key gives
    // us the right columns.
    var $Headers = array();
    var $HeadersMap = array();
    var $Headers_IDX = array();

    // ColExclusions re a list of rows which are excluded from the CSV.
    //   it's a simple array of strings.
    // RowExclusions is an associative array of the form:
    //   ColName => array(Values)
    // and any row where ColName is in the associated array will be excluded
    var $ColExclusions = array();
    var $RowExclusions = array(
        "Current_stage" => array("Recycling Bin"),
        "SubprojectID" => array("Control"),
        "Visit" => array("Failure", "Withdrawal"),
        "Screening" => array("Failure", "Withdrawal"),
        "Administration" => array("None", "Partial", ""),
        "Data_entry" => array("In Progress")
    );

    // headers is the first line of the CSV file,
    // It's used to build an array of which column refers to what column.
    function __construct($headers, $TestName) {
        $this->TestName = $TestName;
        foreach ($headers as $header_idx => $header) {
            $this->Headers[] = $header;
            $this->HeadersMap[$header] = $header_idx;
            if(strrpos($header, "_status") !== FALSE) {
                $this->ColExclusions[] = $header;
            } else {
                if(!in_array($header, $this->ColExclusions)) {
                    $this->Headers_IDX[$header_idx] = "set";
                }
            }
        }
    }

    function getheaders() {
        // Strip out the exclusions. Headers_IDX only contains included columns, as built in the constructor
        $head = array_intersect_key($this->Headers, $this->Headers_IDX);
        return $head;
        //return array_keys(array_intersect_key($this->headers, $this->Headers_IDX));
    }

    // _process() is internal, because we want to be able to call it from subclasses and
    //  use the super class to chain results together. 
    // We don't want to strip the extra columns out until after.
    function _process($line) {
        $result = $line;
        foreach($this->RowExclusions as $field => $exclusions) {
            $Val = $line[$this->HeadersMap[$field]];
            if(in_array($Val, $exclusions, true)) {
                return;
            }
        }

        if(strrpos($this->TestName, "_proband") !== FALSE) {
            $result = $this->_processProband($line);
        } else {
            $result = $this->_processSubject($line);

        }
        // Change date format from YYYY-MM-DD to DD/MM/YYYY
        $result = preg_replace("/^(\d{4})-(\d{2})-(\d{2})\$/", "\${3}/\${2}/\${1}", $result);

        // Replace not_answered with blank, for questions that don't have a _status
        // (which was already stripped out and would already be blank)
        $result = preg_replace("/not_answered/", "", $result);
        // Replace "." with empty. Not sure why the Excel dump puts the . in the
        // first place, but NDAR doesn't like it.
        $result = preg_replace("/^.\$/", "", $result);
        // They want "M" and "F" in capitals to indicate male or female
        $result = preg_replace("/^(m|Male)\$/i", "M", $result);
        $result = preg_replace("/^(f|Female)\$/i", "F", $result);
        // They want Yes/No uppercase too.
        $result = preg_replace("/^yes\$/i", "Yes", $result);
        $result = preg_replace("/^no\$/i", "No", $result);

        return $result;
    }

    function _processProband($line) {
        return $line;
    }
    function _processSubject($line) {
        return $line;
    }

    function process($line) {
        // Strip out the exclusions. Headers_IDX only contains included columns, as built in the constructor
        return array_intersect_key($this->_process($line), $this->Headers_IDX);
    }
}
?>
