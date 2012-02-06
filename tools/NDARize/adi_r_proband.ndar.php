<?
class adi_r_probandNDAR extends BaseNDAR {

    function _processProband($line) {
        $line = preg_replace("/^(\d+).*\$/", "\${1}", $line)
        $line = preg_replace("/^Nonverbal\$/", "", $line)
        $line = preg_replace("/^Verbal\$/", "", $line)
        return $line;
    }
    function _processSubject($line) {
        return $line;
    }
}
?>
