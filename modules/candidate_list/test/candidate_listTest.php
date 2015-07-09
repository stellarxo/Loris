<?php

/**
 * Candidate_list automated integration tests
 *
 * PHP Version 5
 *
 * @category Test
 * @package  Loris
 * @author   Ted Strauss <ted.strauss@mcgill.ca>
 * @license  http://www.gnu.org/licenses/gpl-3.0.txt GPLv3
 * @link     https://github.com/aces/Loris
 */

require_once __DIR__
    . "/../../../test/integrationtests/LorisIntegrationTest.class.inc";

/**
 * CandidateListTestIntegrationTest
 *
 * @category Test
 * @package  Loris
 * @author   Ted Strauss <ted.strauss@mcgill.ca>
 * @license  http://www.gnu.org/licenses/gpl-3.0.txt GPLv3
 * @link     https://github.com/aces/Loris
 */
class CandidateListTestIntegrationTest extends LorisIntegrationTest
{
    private $_useEDCId;
    private $_useEDCBackup;
    private $_useProjectsId;
    private $_useProjectsBackup;

    /**
     * Backs up the useEDC config value and sets the value to a known
     * value (true) for testing.
     *
     * @return none
     */
    function setUp()
    {
        parent::setUp();

        $this->_useEDCId = $this->DB->pselectOne(
            "SELECT ID FROM ConfigSettings WHERE NAME=:useEDC",
            array(":useEDC" => "useEDC")
        );

        $this->_useEDCBackup = $this->DB->pselectOne(
            "SELECT Value FROM Config WHERE ConfigID=:useEDC",
            array(":useEDC" => $this->_useEDCId)
        );

        $this->DB->update(
            "Config",
            array("Value" => "true"),
            array("ConfigID" => $this->_useEDCId)
        );

    }

    /**
     * Restore the values backed up in the setUp function
     *
     * @return none
     */
    function tearDown()
    {
        $this->_useEDCBackup = $this->DB->pselectOne(
            "SELECT Value FROM Config WHERE ConfigID=:useEDC",
            array(":useEDC" => $this->_useEDCId)
        );
        $this->DB->update(
            "Config",
            array("Value" => $this->_useEDCBackup),
            array("ConfigID" => $this->_useEDCId)
        );
        parent::tearDown();
    }
    /**
     * Tests that, when loading the candidate_list module, the breadcrumb
     * appears and the default filters are set to "Basic" mode.
     *
     * @return void
     */
    function testCandidateListPageLoads()
    {
        $this->webDriver->get($this->url . "?test_name=candidate_list");
        $bodyText = $this->webDriver
            ->findElement(WebDriverBy::cssSelector("body"))->getText();
        $this->assertContains("Access Profile", $bodyText);

        $basicButton = $this->webDriver->findElement(WebDriverBy::Name("advanced"));

        // Ensure that the default is basic mode (which means the button
        // says "Advanced")
        $this->assertEquals("Advanced", $basicButton->getAttribute("value"));
    }




    /**
     * Tests that either access_all_profiles or data_entry
     * permission is required to access the page
     * @return void
     */
//
//    function testCandidateListPermissions() {
//        if (access_all_profiles || data_entry permission) {
//            page loads;
//        }
//        else {
//            $error_msg = $this->webDriver->findElement(WebDriverBy::cssSelector("error"))->getText();
//            $this->assertContains("You do not have access to this page.", $error_msg);
//        }
//    }




    /**
     * Tests that, if data_entry permission NOT access_all_profiles
     * can only see subjects from own site
     *
     * @return void
     */
//
//    function testCandidateListDataEntryPermissions() {
//        if (data_entry_permission and !access_all_profiles) {
//            $own_site = $this->webDriver->findElement(WebDriverBy::cssSelector("Site: "))->getText();
//            $displayed_sites = blah;
//            $this->assertAttributeContainsOnly($own_site, $displayed_sites);
//        }
//    }


    /**
     * Test that checks initial filter state:
     * Site = user site
     * Subproject = All
     *
     * @return void
     */

    /*
    function testInitialFilterState() {
        $this->webDriver->get($this->url . "?test_name=candidate_list");

        $siteFilter = $this->webDriver->findElement(WebDriverBy::Name("centerID"));
        $siteField = $siteFilter->getAttribute('value');
        $this->assertEquals('',$siteField);
        $this->assertNotEquals('1',$siteField);

        // Change to USER SITE!!!!!!!
        // use label

        $subprojectFilter = $this->webDriver->findElement(WebDriverBy::Name("SubprojectID"));
        $subprojectField = $subprojectFilter->getAttribute('value');
        $this->assertEquals('',$subprojectField);
        $this->assertNotEquals('1',$subprojectField);

        // test all blank
        // open/close advanced


    }
*/


    /**
     * Tests that, if filters are used,
     * results are filtered
     * Test individually:
     * Site
     * DCCID
     * PSCID
     * Subproject
     * Project
     * Scan done
     * Participant Status
     * Gender
     * Number of Visits
     * Date of Birth
     * Latest Visit Status
     * Feedback
     *
     * @return void
     */




    /**
     * Tests that advanced and basic filter toggle works
     *
     * Site
    //Subproject
    //project
    //DCCID
    //pSCID
    // does not contain scan_done
     * participant status
     * date of birth
     * gender
     * number of visits
     * latest visit status
     * feedback
     *
     *
     *
     * @return void
     */

    /*
    function testCandidateListBasicAdvancedToggle() {
        $this->webDriver->get($this->url . "?test_name=candidate_list");


        // Switch to Advanced mode
        $basicButton = $this->webDriver->findElements(WebDriverBy::Name("advanced"));
        $this->assertEquals(2, count($basicButton));
        $basicButton[0]->click();

        $scanDoneOptions = $this->webDriver->findElement(
            WebDriverBy::Name("scan_done")
        );
        $this->assertEquals("select", $scanDoneOptions->getTagName());

        $basicButton[1]->click();

//         Go through each element and ensure it's on the page after clicking
        $this->assertFalse($this->webDriver->findElement(WebDriverBy::Name("scan_done"))->isDisplayed());
        $this->assertFalse($this->webDriver->findElement(WebDriverBy::Name("Participant_Status"))->isDisplayed());
        $this->assertFalse($this->webDriver->findElement(WebDriverBy::Name("dob"))->isDisplayed());
        $this->assertFalse($this->webDriver->findElement(WebDriverBy::Name("gender"))->isDisplayed());
        $this->assertFalse($this->webDriver->findElement(WebDriverBy::Name("Visit_Count"))->isDisplayed());
        $this->assertFalse($this->webDriver->findElement(WebDriverBy::Name("Latest_Visit_Status"))->isDisplayed());
        $this->assertFalse($this->webDriver->findElement(WebDriverBy::Name("Feedback"))->isDisplayed());


    }
*/


    /**
     * Tests that, if advanced filter is set,
     * advanced filters are expanded on page load
     * and collapsed otherwise
     *
     * @return void
     */

    /**
     * Tests that, after clicking the "Advanced" button, all of the
     * advanced filters appear on the page and are the correct element type.
     *
     * @return void
     */


    /*
    function testCandidateListAdvancedOptionsAppear()
    {

        $this->webDriver->get($this->url . "?test_name=candidate_list");
        $bodyText = $this->webDriver
            ->findElement(WebDriverBy::cssSelector("body"))->getText();
        $this->assertContains("Access Profile", $bodyText);

        // Switch to Advanced mode
        $basicButton = $this->webDriver->findElement(WebDriverBy::Name("advanced"));
        $basicButton->click();

        // Go through each element and ensure it's on the page after clicking
        // advanced
        $scanDoneOptions = $this->webDriver->findElement(
            WebDriverBy::Name("scan_done")
        );
        $this->assertEquals("select", $scanDoneOptions->getTagName());

        $participantsStatusOptions = $this->webDriver->findElement(
            WebDriverBy::Name("Participant_Status")
        );
        $this->assertEquals("select", $participantsStatusOptions->getTagName());

        $dobOptions = $this->webDriver->findElement(WebDriverBy::Name("dob"));
        $this->assertEquals("input", $dobOptions->getTagName());
        // Not currently done
        //$this->assertEquals("date",$dobOptions->getAttribute("type"));

        $genderOptions = $this->webDriver->findElement(WebDriverBy::Name("gender"));
        $this->assertEquals("select", $genderOptions->getTagName());

        $numVisits = $this->webDriver->findElement(WebDriverBy::Name("Visit_Count"));
        $this->assertEquals("input", $dobOptions->getTagName());
        // Not currently done in Loris.
        //$this->assertEquals("number",$dobOptions->getAttribute("type"));
        //$this->assertEquals("0",$dobOptions->getAttribute("min"));

        $edcOptions = $this->webDriver->findElement(WebDriverBy::Name("edc"));
        $this->assertEquals("input", $edcOptions->getTagName());
        // Not currently done
        //$this->assertEquals("date",$edcOptions->getAttribute("type"));

        $latestVisitOptions = $this->webDriver->findElement(
            WebDriverBy::Name("Latest_Visit_Status")
        );
        $this->assertEquals("select", $latestVisitOptions->getTagName());

        $feedbackOptions = $this->webDriver->findElement(
            WebDriverBy::Name("Feedback")
        );
        $this->assertEquals("select", $feedbackOptions->getTagName());
    }
*/


    /**
     * Tests that each drop down
     * has the correct options
     *
     * @dataProvider providerTestDropDownOptions
     *
     * @return void
     */


    /*
    function testDropDownOptions($desiredFilter, $desiredOptions) {
        $filter = $this->webDriver->findElement(
            WebDriverBy::Name($desiredFilter)
        );

        foreach ($desiredOptions as $option) {
            $this->assertContains($filter, $option);

        }

//        $this->assertEquals("select", $scanDoneOptions->getTagName());

    }

    function providerTestDropDownOptions() {
        return array(
            array('Visit_label',
                array('1')),
            array('centerID',
                array('1'))
        );
    }
*/


    /**
     * Tests that, if "Clear Form" is clicked,
     * filters reset to initial state
     *
     * @param string $action Method of filling the respective field
     * @param string $field Field to be cleared
     * @param string $val Value to be entered
     *
     * @dataProvider providerTestClearForm
     *
     *
     */

    function testClearForm($action, $field, $val){
        $this->webDriver->get($this->url . "?test_name=candidate_list");

        // Open all filters
        $basicButton = $this->webDriver->findElement(WebDriverBy::Name("advanced"));
        $basicButton->click();

        // Testing individual fields
        $filter = $this->webDriver->findElement(WebDriverBy::Name($field));
        $this->webDriver->$action($filter)->selectOptionByValue($val);

        // Submit filter
        $showDataButton = $this->webDriver->findElement(WebDriverBy::Name("filter"));
        $showDataButton->click();

        // Clear data
        $clearButton = $this->webDriver->findElement(WebDriverBy::Name("reset"));
        $clearButton->click();

        // Check that fields are set back to default
        testInitialFilterState();

    }

    function providerTestClearForm(){
        return array(
//            array('type','PSCID','1'),      // type not working
//            array('type','DCCID','1'),
//            array('select','Visit_label','value=1'),     //Different in IBIS
            array('select','centerID',/*value= */'2')
//        ,
//            array('select','SubprojectID','value=1'),
//            array('select','ProjectID','value=1'),
//            array('select','scan_done','value=Y'),
//            array('select','Particiant_Status','value=1'),
////            array('type','dob','2015-01-08'),
//            array('select','gender','value=Male'),
////            array('type','Visit_Count','value=1'),
//            array('select','Latest_Visit_Status','value=Visit'),
//        //    array('edc'),
//            array('select','Feedback','value=1')
        );
    }



    /**
     * 11.
     * Tests that, if a column is clicked,
     * data sorts
     *
     * @return void
     */



    /**
     * Tests that, if "Yes" link under column 'Scan Done' is clicked,
     * the link points to the correct scan in the Imaging Browser
     *
     * @return void
     */


    /**
     * 13.
     * Tests that, if PSCID link is clicked,
     * it points to the correct timepoint_list page
     *
     * @return void
     */



    /**
     * 14.
     * Tests that, if a candidate has feedback,
     * the feedback column is displayed with the correct colour
     *
     * @return void
     */



    /**
     * 15.
     * Tests that, if wrong PSCID/DCCID combination is entered
     * and "Open Profile" is clicked,
     * an error is thrown
     *
     * @return void
     */


    /**
     * 16.
     * Tests that, if a correct PSCID/DCCID combination is entered,
     * the correct timepoint_list page loads
     *
     * @return void
     */


    /**
     * 17.
     * Tests that, without access_all_profiles permission,
     * PSCID links are NOT clickable
     *
     * @return void
     */



    /**
     * 18.
     * Tests that, if useEDC and useProjects config variables = false,
     * filters are removed from menu
     *
     * @return void
     */






}
?>
