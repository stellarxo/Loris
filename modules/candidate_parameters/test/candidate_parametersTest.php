<?php
/**
 * candidate_parameters automated integration tests
 *
 * PHP Version 5
 *
 * @category Test
 * @package  Loris
 * @author   Ted Strauss <ted.strauss@mcgill.ca>
 * @license  http://www.gnu.org/licenses/gpl-3.0.txt GPLv3
 * @link     https://github.com/aces/Loris
 */

require_once __DIR__ . "/../../../test/integrationtests/LorisIntegrationTestWithCandidate.class.inc";
class candidateParametersTestIntegrationTest extends LorisIntegrationTestWithCandidate
{
    /**
     * Tests that, when loading the candidate_parameters module, some
     * text appears in the body.
     *
     * @return void
     */
    function testCandidateParametersDoesPageLoad()
    {
        $this->safeGet($this->url . "/candidate_parameters/?candID=900000&identifier=900000");
        $bodyText = $this->webDriver->findElement(WebDriverBy::cssSelector("body"))->getText();
        $this->assertContains("Candidate Parameters", $bodyText);
    }

}
?>
