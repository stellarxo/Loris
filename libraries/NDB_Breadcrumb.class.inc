<?php
require_once 'PEAR.php';

/**
 * Breadcrumb class
 * 
 * Builds the breadcrumb for the GUI
 * @package main
 */
class NDB_Breadcrumb extends PEAR
{
    /**
     * The breadcrumb
     * @var    array
     * @access private
     */
    var $_breadcrumb = array();

    /**
     * The index of the last crumb
     * @var    int
     * @access private
     */
    var $_lastIndex = -1;

    /**
     * The available parameters to build into the URL
     * @var    array
     * @access private
     */
    var $_parameters;

    /**
     * The user-friendly names for different forms or menus
     * @var    array
     * @access private
     */
    var $_userFriendlyNames = array(
                                   'next_stage' => 'Start Next Stage',
                                   'create_timepoint' => 'Create Time Point',
                                   'instrument_list' => 'TimePoint Details',
                                   'timepoint_list' => 'Candidate Profile',
                                   'candidate_list' => 'Access Profile',
                                   'conflicts_resolve' => 'Conflicts Resolver',
                                   'statistics' => 'Database Statistics',
                                   'statistics_site' => 'Data Entry Completion Breakdown',
                                   'statistics_dd_site' => 'Double Data Entry Completion Breakdown',
                                   'statistics_mri_site' => 'MRI Statistics',
                                   'reliability'        => 'Reliability Module',
                                   'adi_r_reliability'        => 'ADI-R Reliability Module',
                                   'adi_r_proband_reliability'        => 'ADI-R (Proband) Reliability Module',
                                   'adi_r_subject_reliability'        => 'ADI-R (Subject) Reliability Module',
                                   'ados_module1_reliability' => 'ADOS (Module 1) Reliability Module',
                                   'ados_module2_reliability' => 'ADOS (Module 2) Reliability Module',
                                   'aosi_reliability' => 'AOSI Reliability Module',
                                   'csbs_reliability' => 'CSBS Reliability Module',
                                   'videos' => 'Videos',
                                   'video_upload' => 'Video Uploader',
                                   'blind_coding' => 'Blind Coding'
                                   );

    /**
     * Adds a crumb to the breadcrumb
     *
     * You may pass in the next test name, so that the breadcrumb correctly 
     * adds the next crumb on the next iteration. You may pass in custom text
     * to fill the crumb, or you may pass in the name of a parameter to format
     * with which to fill the crumb. You can also pass in a parameter to unset.
     *
     * @param  string   next test name (optional)
     * @param  string   parameter to unset (optional)
     * @param  string   crumb text (optional)
     * @param  string   parameter to format (optional)
     * @return void
     * @access private
     */
    function _addCrumb($testName = null, $unset = null, $text = null, $parameter = null)
    {
        if (!is_null($unset)) {
            if($unset == 'subtest') {
                unset($this->_parameters[$unset]);
            }
        }
        // go the the next crumb
        $this->_lastIndex++;

        // set the query string
        $this->_breadcrumb[$this->_lastIndex]['query'] = Utility::unparse_str($this->_parameters);

        // set the crumb text
        if (!is_null($text)) {
            $this->_breadcrumb[$this->_lastIndex]['text'] = $text;
        } elseif (!is_null($parameter) && isset($this->_parameters[$parameter])) {
            $this->_breadcrumb[$this->_lastIndex]['text'] = ucwords(str_replace('_', ' ', $this->_parameters[$parameter]));
        } else {
            if(isset($this->_userFriendlyNames[$this->_parameters['test_name']])) {
                $this->_breadcrumb[$this->_lastIndex]['text'] = $this->_userFriendlyNames[$this->_parameters['test_name']];
            } else {
                $this->_breadcrumb[$this->_lastIndex]['text'] = '';
            }
        }

        // set the next crumb's test name
        if (!is_null($testName)) {
            $this->_parameters['test_name'] = $testName;
        }

        // unset given parameter
        if (!is_null($unset)) {
            unset($this->_parameters[$unset]);
        }
    }

    /** 
     * Adds a request parameter to $this->_parameters
     * if and only if the entry is set in $_REQUEST.
     * 
     * @param string paramname  The name of the parameter being added
     * @param string defaultval The value to be assigned if the request param isn't
     *                          set. If null, then won't touch the data at all if 
     *                          REQUEST parameter not passed 
     *
     * @return null
     */
    function _addParameter($paramname, $defaultval=null) {
        if(isset($_REQUEST[$paramname])) {
            $this->_parameters[$paramname] = $_REQUEST[$paramname];
        } elseif(is_null($defaultval)) {
            return;
        } else {
            $this->_parameters[$paramname] = $defaultval;
        }
    }

    /**
     * Makes a breadcrumb
     *
     * @return array
     * @throws PEAR_Error
     * @access public
     */
    function getBreadcrumb()
    {
        // set the parameters array
        
        $this->_parameters = array();
        $this->_addParameter('test_name', '');
        $this->_addParameter('subtest', '');
        $this->_addParameter('candID', '');
        $this->_addParameter('sessionID', '');
        $this->_addParameter('commentID', '');
        $this->_addParameter('identifier', '');

        /* Don't add the CenterID or reliabilility_center_id unless they're already present.
           since we only need them on statistics and reliability pages */
        $this->_addParameter('CenterID');
        $this->_addParameter('reliability_center_id');
        $this->_addParameter('blind');

        // check if test name is empty
        if (empty($this->_parameters['test_name'])) {
            return null;
        }

        // create DB object
        $DB =& Database::singleton();
        if (PEAR::isError($DB)) {
            return PEAR::raiseError("Could not connect to database: ".$DB->getMessage());
        }

        // set the 'instrument list' crumb text
        if (!empty($_REQUEST['sessionID'])) {
            $timePoint =& TimePoint::singleton($_REQUEST['sessionID']);
            if (PEAR::isError($timePoint)) {
                return PEAR::raiseError("TimePoint Error (".$_REQUEST['sessionID']."): ".$timePoint->getMessage());
            }
            $this->_userFriendlyNames['instrument_list'] = 'TimePoint '.$timePoint->getVisitLabel().' Details';
        }

        // set the 'timepoint list' crumb text
        if (!empty($_REQUEST['candID'])) {
            $candidate =& Candidate::singleton($_REQUEST['candID']);
            if (PEAR::isError($candidate)) {
                return PEAR::raiseError("Candidate Error (".$_REQUEST['candID']."): ".$candidate->getMessage());
            }
            $this->_userFriendlyNames['timepoint_list'] = 'Candidate Profile '.$candidate->getData('CandID').' / '.$candidate->getData('PSCID');
        }

        // add a crumb for subtests
        if (!empty($this->_parameters['subtest'])) {
            $result = $DB->selectOne("SELECT Description FROM instrument_subtests WHERE Test_name = '" . $this->_parameters['test_name'] . "' AND Subtest_name = '" . $this->_parameters['subtest'] . "'");
            if (PEAR::isError($result)) {
                return PEAR::raiseError("DB Error: ".$result->getMessage());
            }

            if (empty($result)) {
                $this->_addCrumb(null, 'subtest', null, 'subtest');
            } else {
                $this->_addCrumb(null, 'subtest', $result);
            }
        }

        // add a crumb for instruments
        if (!empty($this->_parameters['commentID'])) {
            $result = $DB->selectOne("SELECT Full_name FROM test_names WHERE Test_name = '" . $this->_parameters['test_name'] . "'");
            if (PEAR::isError($result)) {
                return PEAR::raiseError("DB Error: ".$result->getMessage());
            }

            if (empty($result)) {
                $this->_addCrumb('instrument_list', 'commentID', null, 'test_name');
            } else {
                $this->_addCrumb('instrument_list', 'commentID', $result);
            }
        }

        // set the order of the crumbs
        $crumbOrder = array('next_stage'       => array('next'  => 'instrument_list',
                                                        'unset' => 'identifier'),
                            'create_timepoint' => array('next'  => 'timepoint_list',
                                                        'unset' => 'identifier'),
                            'instrument_list'  => array('next'  => 'timepoint_list',
                                                        'unset' => 'sessionID'),
                            'timepoint_list'   => array('next'  => 'candidate_list',
                                                        'unset' => 'candID'),
                            'candidate_list'   => array('next'  => ''),
                            'statistics_site'  => array('next'  => 'statistics',
                                                        'unset' => 'subtest'),
                            'statistics_dd_site'  => array('next'  => 'statistics',
                                                        'unset' => 'subtest'),
                            'statistics_mri_site'  => array('next'  => 'statistics',
                                                        'unset' => 'subtest'),
                            'statistics'       => array('next'  => ''),
                            'conflicts_resolve' => array('next' => ''),
                            'adi_r_reliability' => array('next' => 'reliability'),
                            'adi_r_subject_reliability' => array('next' => 'reliability'),
                            'adi_r_proband_reliability' => array('next' => 'reliability'),
                            'ados_module1_reliability' => array('next' => 'reliability'),
                            'ados_module2_reliability' => array('next' => 'reliability'),
                            'aosi_reliability' => array('next' => 'reliability'),
                            'csbs_reliability' => array('next' => 'reliability'),
                            'reliability'       => array('next' => ''),
                            'video_upload'            => array('next' => 'videos'),
                            'videos'            => array('next' => ''),
                            'blind_coding' => array('next' => '')

                            );

        // loop through the crumbs according to the order above, or just make one crumb
        if (array_key_exists($this->_parameters['test_name'], $crumbOrder)) {
            while (!empty($this->_parameters['test_name'])) {
                if($this->_parameters['test_name'] == 'aosi_reliability' && $this->_parameters['blind']) {
                    $this->_addCrumb('blind_coding', $crumbOrder[$this->_parameters['test_name']]['unset']);
                } else {
                    $test_name = $this->_parameters['test_name'];
                    $next = $crumbOrder[$test_name]['next'];
                    $unsetCrumb = '';
                    if(isset($crumbOrder[$test_name]['unset'])) {
                        $unsetCrumb = $crumbOrder[$test_name]['unset'];
                    }
                    $this->_addCrumb($next, $unsetCrumb);
                }
            }
        } else {
            $this->_addCrumb(null, null, null, 'test_name');
        }

        // reverse the breadcrumb, because crumbs are added in reverse order
        return array_reverse($this->_breadcrumb);
    }
}