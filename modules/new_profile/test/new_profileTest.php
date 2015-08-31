<?php
/**
 * new_profile automated integration tests
 *
 * PHP Version 5
 *
 * @category Test
 * @package  Loris
 * @author   Ted Strauss <ted.strauss@mcgill.ca>
 * @license  http://www.gnu.org/licenses/gpl-3.0.txt GPLv3
 * @link     https://github.com/aces/Loris
 */

require_once __DIR__ . "/../../../test/integrationtests/LorisIntegrationTest.class.inc";
class newProfileTestIntegrationTest extends LorisIntegrationTest
{
    /**
     * 1. Tests that, when loading the new_profile module with all settings
     * enabled, the correct fields all appear in the body.
     *
     * @return void
     */
    function testNewProfilePageLoads()
    {
        $this->setUpConfigSetting("useEDC", "true");
        $this->setUpConfigSetting("useProjects", "true");

        $this->webDriver->get($this->url . "?test_name=new_profile");
        $bodyText = $this->webDriver->findElement(WebDriverBy::cssSelector("body"))->getText();
        $this->assertContains("New Profile", $bodyText);

        $dobField = $this->webDriver->findElement(WebDriverBy::Name("dob1"));
        $this->assertEquals("input", $dobField->getTagName());
        //$this->assertEquals("date", $dobField->getAttribute("type"));

        $dob2Field = $this->webDriver->findElement(WebDriverBy::Name("dob2"));
        $this->assertEquals("input", $dob2Field->getTagName());
        //$this->assertEquals("date", $dob2Field->getAttribute("type"));

        $edcField = $this->webDriver->findElement(WebDriverBy::Name("edc1"));
        $this->assertEquals("input", $edcField->getTagName());
        //$this->assertEquals("date", $edcField->getAttribute("type"));

        $edc2Field = $this->webDriver->findElement(WebDriverBy::Name("edc2"));
        $this->assertEquals("input", $edc2Field->getTagName());
        //$this->assertEquals("date", $edc2Field->getAttribute("type"));

        $genderField = $this->webDriver->findElement(WebDriverBy::Name("gender"));
        $this->assertEquals("select", $genderField->getTagName());

        $projectField = $this->webDriver->findElement(WebDriverBy::Name("ProjectID"));
        $this->assertEquals("select", $projectField->getTagName());

        $this->restoreConfigSetting("useEDC");
        $this->restoreConfigSetting("useProjects");
    }

    /**
     * 2. Tests that with useProjects turned off, project related fields do not
     * appear on the page.
     *
     * @return none
     */
//    function testNewProfileLoadsWithoutProjects() {
//        $this->setUpConfigSetting("useProjects", "false");
//
//        $this->webDriver->get($this->url . "?test_name=new_profile");
//
//        try {
//            $projectField = $this->webDriver->findElement(WebDriverBy::Name("ProjectID"));
//        } catch(NoSuchElementException $e) {
//            $projectField = null;
//        }
//        $this->assertNull($projectField);
//
//        $this->restoreConfigSetting("useProjects");
//    }

    /**
     * 3. Tests that with useEDC turned off, edc related fields do not appear
     * on the page.
     *
     * @return none
     */
//    function testNewProfileLoadsWithoutEDC() {
//        $this->setUpConfigSetting("useEDC", "false");
//
//        $this->webDriver->get($this->url . "?test_name=new_profile");
//
//        try {
//            $edc1 = $this->webDriver->findElement(WebDriverBy::Name("edc1"));
//        } catch(NoSuchElementException $e) {
//            $edc1 = null;
//        }
//        $this->assertNull($edc1);
//
//        try {
//            $edc2 = $this->webDriver->findElement(WebDriverBy::Name("edc2"));
//        } catch(NoSuchElementException $e) {
//            $edc2 = null;
//        }
//
//        $this->assertNull($edc2);
//        $this->restoreConfigSetting("useEDC");
//    }

    /**
     * 4. Tests that an error occurs,
     * if dates don't match (both DoB and EDC)
     *
     * @param string $dob1 Date of Birth
     * @param string $dob2 Confirm Date of Birth
     * @param string $edc1 Expected Date of Confinement
     * @param string $edc2 Confirm Expected Date of Confinement
     *
     * @dataProvider providerTestDateMismatchError
     *
     * @return none
     */
    function testDateMismatchError($dob1, $dob2, $edc1, $edc2) {
        $this->webDriver->get($this->url . "?test_name=new_profile");

//        $this->webDriver->findElement(WebDriverBy::Name('dob1'))->value($dob1);
//        $this->webDriver->findElement(WebDriverBy::Name('dob2'))->value($dob2);
//        $this->webDriver->findElement(WebDriverBy::Name('edc1'))->value($edc1);
//        $this->webDriver->findElement(WebDriverBy::Name('edc2'))->value($edc2);

        $this->webDriver->findElement(WebDriverBy::Name('dob1'))->click();
        $this->webDriver->findElement(WebDriverBy::cssSelector('.user-success'))->click();
        $this->webDriver->getKeyboard()->sendKeys($dob1);
        $this->webDriver->findElement(WebDriverBy::Name('dob2'))->click();
        $this->webDriver->getKeyboard()->sendKeys($dob2);
        $this->webDriver->findElement(WebDriverBy::Name('edc1'))->click();
        $this->webDriver->getKeyboard()->sendKeys($edc1);
        $this->webDriver->findElement(WebDriverBy::Name('edc2'))->click();
        $this->webDriver->getKeyboard()->sendKeys($edc2);

        $fields = array('gender', 'ProjectID');
        foreach ($fields as $field) {
            $dropDown = $this->webDriver->findElement(WebDriverBy::Name($field));
            $allOptions = $dropDown->findElement(WebDriverBy::tagName('option'));
            foreach ($allOptions as $option) {
                if ($option == '1') {
                    $option->click();
                    break;
                }
            }
        }
        $createButton = $this->webDriver->findElement(WebDriverBy::Name("fire_away"));
        $createButton->click();

        // Wait until page loads
        $this->webDriver->wait(120, 1000)->until(
            WebDriverExpectedCondition::presenceOfElementLocated(
                WebDriverBy::id("page")
            )
        );

        $bodyText = $this->webDriver->findElement(
            WebDriverBy::cssSelector("body")
        )->getText();
        if ($edc1 != $edc2) {
            $this->assertContains(
                "Estimated Due date fields must match.",
                $bodyText
            );
        }
        if ($dob1 != $dob2) {
            $this->assertContains(
                "Date of Birth fields must match.",
                $bodyText
            );
        }
    }

    /*
     * Data provider for testDateMismatchError()
     * @return array
     */
    function providerTestDateMismatchError() {
        return array(
            array('11/11/2011', '12/11/2011', '05/05/2005', '05/05/2005'),
            array('11/11/2011', '11/11/2011', '05/05/2005', '06/05/2005'),
            array('11/11/2011', '12/11/2011', '05/05/2005', '06/05/2005')
//            array('2000-11-11', '2000-11-12', '2005-05-05', '2005-05-05'),
//            array('2000-11-11', '2000-11-11', '2005-05-05', '2005-05-06'),
//            array('2000-11-11', '2000-11-12', '2005-05-05', '2005-05-06')
        );
    }

    /**
     * 5. Tests that an error occurs,
     * if any field is missing.
     *
     * @param string $dob1 Date of Birth
     * @param string $dob2 Confirm Date of Birth
     * @param string $edc1 Expected Date of Confinement
     * @param string $edc2 Confirm Expected Date of Confinement
     * @param string $gender Gender
     * @param string $project Project
     *
     * @dataProvider providerTestMissingFieldError
     *
     * @return none
     */
//    function testMissingFieldError($dob1, $dob2, $edc1, $edc2, $gender, $project) {
//
//        $this->webDriver->get($this->url . "?test_name=new_profile");
//
//        if ($dob1 != NULL) {
//            $this->webDriver->findElement(WebDriverBy::Name('dob1'))->value($dob1);
//        }
//        if ($dob2 != NULL) {
//            $this->webDriver->findElement(WebDriverBy::Name('dob2'))->value($dob2);
//        }
//        if ($edc1 != NULL) {
//            $this->webDriver->findElement(WebDriverBy::Name('edc1'))->value($edc1);
//        }
//        if ($edc2 != NULL) {
//            $this->webDriver->findElement(WebDriverBy::Name('edc2'))->value($edc2);
//        }
//
//        if ($gender != NULL) {
//            $genderDropDown = $this->webDriver->findElement(WebDriverBy::Name('gender'));
//            $allOptions = $genderDropDown->findElement(WebDriverBy::tagName('option'));
//            foreach ($allOptions as $option) {
//                if ($option == $gender) {
//                    $option->click();
//                    break;
//                }
//            }
//        }
//
//        if ($project != NULL) {
//            $projectDropDown = $this->webDriver->findElement(WebDriverBy::Name('ProjectID'));
//            $allOptions = $projectDropDown->findElement(WebDriverBy::tagName('option'));
//            foreach ($allOptions as $option) {
//                if ($option == $project) {
//                    $option->click();
//                    break;
//                }
//            }
//        }
//
//        $createButton = $this->webDriver->findElement(WebDriverBy::Name("fire_away"));
//        $createButton->click();
//
//        // Wait until page loads
//        $this->webDriver->wait(120, 1000)->until(
//            WebDriverExpectedCondition::presenceOfElementLocated(
//                WebDriverBy::id("page")
//            )
//        );
//
//        $bodyText = $this->webDriver->findElement(
//            WebDriverBy::cssSelector("body")
//        )->getText();
//
//        // error message
//
//    }

    /*
    * Data provider for testDateMismatchError()
    * @return array
    */
//    function providerTestMissingFieldError() {
//        return array(
//            array('2000-11-11', '2000-11-11', '2005-05-05', '2005-05-05', 1, 1),
//        );
//    }

    /**
     * 6. Tests that a new candidate is created
     *  with auto-generated PSCID (if PSCID generation is "sequential"),
     *  when all valid fields are added.
     *
     * @return none
     */
//    function testAddNewCandidate() {
//        $this->webDriver->get($this->url . "?test_name=new_profile");
//
//        $dob1 = '2011-11-11';
//        $dob2 = $dob1;
//        $edc1 = '2011-12-12';
//        $edc2 = $edc1;
//
//        $this->webDriver->findElement(WebDriverBy::Name('dob1'))->value($dob1);
//        $this->webDriver->findElement(WebDriverBy::Name('dob2'))->value($dob2);
//        $this->webDriver->findElement(WebDriverBy::Name('edc1'))->value($edc1);
//        $this->webDriver->findElement(WebDriverBy::Name('edc2'))->value($edc2);
//
//        $fields = array('gender', 'ProjectID');
//        foreach ($fields as $field) {
//            $dropDown = $this->webDriver->findElement(WebDriverBy::Name($field));
//            $allOptions = $dropDown->findElement(WebDriverBy::tagName('option'));
//            foreach ($allOptions as $option) {
//                if ($option == '1') {
//                    $option->click();
//                    break;
//                }
//            }
//        }
//        $createButton = $this->webDriver->findElement(WebDriverBy::Name("fire_away"));
//        $createButton->click();
//
//        // Wait until page loads
//        $this->webDriver->wait(120, 1000)->until(
//            WebDriverExpectedCondition::presenceOfElementLocated(
//                WebDriverBy::id("page")
//            )
//        );
//
//        $bodyText = $this->webDriver->findElement(
//            WebDriverBy::cssSelector("body")
//        )->getText();
//
//        // check that candidate now exists
//
//    }

    /**
     * 7. Tests that error occurs,
     * if an invalid PSCID entered (and not if a valid PSCID is entered)
     *
     * @return none
     */
    function testInvalidPSCIDError() {

        // Change PSCID generation configuration to "user"
        $this->webDriver->get($this->url . "?test_name=new_profile");

    }


}

?>
