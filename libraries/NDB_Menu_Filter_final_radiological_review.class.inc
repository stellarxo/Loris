<?
require_once 'NDB_Menu_Filter.class.inc';

// Utility function to make things more human readable.
// This is used both below and in the history on the NDB_Form
function _makePretty($key, $val)
{
    if($key == 'Review_Done' || $key=='Conflict' || $key=="Finalized")
    {
        // The table was created with a boolean, which mysql turns into a tinyint.
        // Print 'Yes' or 'No' instead of 1 or 0.
        if($val == 1)
            return 'Yes';
        elseif($val === "0") // PHP turns the tinyint back into a string ....
            return 'No';
        else // Leave nulls empty so that we can distinguish
            return '';
    }

    if($key == 'Final_Review_Results' || $key == 'Exclusionary_Status' || $key=="Final_Exclusionary" || $key == "Results_Of_Radiology_Review")
    {
        // Make the enum columns prettier by changing _ into a space and capitalizing
        return ucwords(str_replace('_', ' ', $val));
    }
    else if ($key == 'SAS' or $key == 'PVS')
    {
        switch($val)
        {
            case '0': return 'None';
            case '1': return 'Minimal';
            case '2': return 'Mild';
            case '3': return 'Moderate';
            case '4': return 'Marked';
            default: return 'Not Answered';
        }
    }
    else
    {
        return $val;
    }
}

class NDB_Menu_Filter_final_radiological_review extends NDB_Menu_Filter
{
    function _hasAccess()
    {
        $user =& User::singleton();
        if (PEAR::isError($user)) {
            return PEAR::raiseError("User Error: " .$user->getMessage());
        }
        return $user->hasPermission('view_final_radiological_review');
    }

    function _setupVariables()
    {
        $conflict_condition = "(case when orig.review_results <> r.final_review_results then True when orig.abnormal_atypical_exculsionary <>  r.final_exclusionary THEN True WHEN r.Final_Review_Results <> r.Final_Review_Results2 THEN True WHEN r.Final_Exclusionary <> r.Final_Exclusionary2 THEN True WHEN r.SAS <> r.SAS2 THEN True WHEN r.PVS <> r.PVS2 THEN True ELSE False end)";

        $this->query = " FROM radiology_review orig LEFT JOIN final_radiological_review r ON (r.CommentID=orig.CommentID) JOIN flag f on (f.CommentID=orig.CommentID) JOIN session s on (s.ID=f.SessionID) JOIN candidate c ON (c.CandID=s.CandID) JOIN tarchive t ON (upper(t.PatientName)=CONCAT(upper(c.PSCID), '_', upper(s.CandID), '_', upper(s.visit_label))) WHERE orig.commentid NOT LIKE 'DDE_%' AND orig.commentid IS NOT NULL AND s.active='Y' AND s.Cancelled='N' AND NOT (f.Administration='None' AND f.Data_entry='Complete' )";
        $this->columns = array('substring_index(t.sourcelocation, \'/\', -1) as DICOM_Folder_Name', 'c.PSCID as PSCID', 'c.CandID as DCCID', 's.visit_label as Visit_Label', 'c.CenterID as Site', 't.DateAcquired as Scan_Date ', 'c.DOB as Birth_Date', 'COALESCE(r.Review_Done, False) as Review_Done', 'r.Final_Review_Results as Results_Of_Radiology_Review', 'r.Final_Exclusionary as Exclusionary_Status', 'r.sas as SAS', 'r.pvs as PVS', 'orig.CommentID as CommentID', "$conflict_condition as Conflict", 'r.Finalized as Finalized', 'r.Final_Incidental_Findings as Comments' );
        $this->order_by = 'PSCID';
        $this->headers = array('DICOM_Folder_Name', 'PSCID',
                               'DCCID', 'Visit_Label', 'Scan_Date', 
                               'Birth_Date', 'Review_Done', 
                               'Results_Of_Radiology_Review', 
                               'Exclusionary_Status', 'SAS', 'PVS', 
                               'Conflict',
                               'Finalized',
                               'Comments'
        );
        $this->validFilters = array('substring_index(t.sourcelocation, \'/\', -1)', 'c.CandID', 'r.DICOM_ID', 's.visit_label', 'c.PSCID', 'r.Final_Review_Results', 'COALESCE(r.Review_Done, False)', 'r.sas', 'r.pvs', 'r.Final_Exclusionary', $conflict_condition, 'r.Finalized', 'c.CenterID');
        $this->formToFilter = array (
                                    'folder' => 'substring_index(t.sourcelocation, \'/\', -1)',
                                    'dccid' => 'c.CandID',
                                    'site' => 'c.CenterID',
                                    'Visit_label' => 's.visit_label',
                                    'pscid' => 'c.PSCID',
                                    'Review_done' => 'COALESCE(r.Review_Done, False)',
                                    'Results_Of_Radiology_Review' => 'r.Final_Review_Results',
                                    'Final_Review_Results' => 'r.Final_Review_Results',
                                    'Exclusionary_Status' => 'r.Final_Exclusionary',
                                    'PVS' => 'r.pvs',
                                    'SAS' => 'r.sas',
                                    'Conflict' => $conflict_condition,
                                    'Finalized' =>  'r.Finalized'
        );
    }

    function _setFilterForm()
    {
        $list_of_visit_labels = array(null => 'Any', 'V06' => 'V06', 'V12' => 'V12', 'V24' => 'V24');
        $options_boolean= array(null => 'Any', True => 'Yes', False => 'No');
        $comment_options = array(null => 'Any', 'True' => 'Yes', 'False' => 'No');
        $bob_score = array(null => 'Any', '0' => 'None', '1' => 'Minimal', '2' => 'Mild', '3' => 'Moderate', '4' => 'Marked');
        $abnormal_atypical = array(null => 'Any', 'abnormal' => 'Abnormal', 'atypical' => 'Atypical', 'normal' => 'Normal');
        $exclude = array(null => 'Any', 'exclusionary' => 'Exclusionary', 'non_exclusionary' => 'Non Exclusionary');

        $this->form->addElement('text', 'folder', 'DICOM Folder Name:', array("size"=>20, "maxlength"=>30));
        $this->form->addElement('text', 'dicomid', 'DICOM ID:', array("size"=>9, "maxlength"=>20));
        $this->form->addElement('text', 'pscid', 'PSCID:', array("size"=>9, "maxlength"=>11));
        $this->form->addElement('text', 'dccid', 'DCCID:', array("size"=>9, "maxlength"=>6));
        $this->form->addElement('select', 'Visit_label', 'Visit Label:', $list_of_visit_labels);
        $this->form->addElement('select', 'site', 'Site', array('' => 'Any', '2' => 'SEA', '3' => 'PHI', '4' => 'STL', '5' => 'UNC'));
        $this->form->addElement('select', 'Review_done', 'Review Done:', $options_boolean);
        $this->form->addElement('select', 'Conflict', 'Conflict between reviews:', $options_boolean);

        $this->form->addElement('select', 'SAS', 'SAS (Subarachnoid Spaces):', $bob_score);
        $this->form->addElement('select', 'PVS', 'PVS (Perivascular Spaces):', $bob_score);

        $this->form->addElement('select', 'Final_Review_Results', 'Results of Radiological Review', $abnormal_atypical);
        $this->form->addElement('select', 'Exclusionary_Status', 'Exclusionary Status', $exclude);



    }


    function _setDataTableRows($count)
    {
        $x = 0;
        foreach ($this->list as $item) {
            $this->tpl_data['items'][$x][0]['value'] = $x + $count;

            //print out data rows
            $i = 1;
            foreach ($item as $key => $val) {
                if ($key == 'CommentID') continue;
                if ($key == 'SessionID') continue;
                if ($key == 'Site') continue;

                // This is a bit of a hack to make sure that each CommentID only shows up once,
                // it collapses DICOM_Folder_Names with the same CommentID into the same row, and
                // comma separates them
                
                if ($key == 'DICOM_Folder_Name') {
                    foreach ($this->tpl_data['items'] as $OtherRow => $OtherItems) {
                        // OtherItems is an array of the form:
                        // array (rownumber => array(
                        //              colnumber => array(
                        //                  name => colname
                        //                  value => colvalue
                        //                  session => x
                        //                  CommentID => x
                        //                ),
                        //              colnumber2 => array(
                        //                  name => colname2, ...
                        //              )
                        //        )
                        //));
                        // We happen to know that the second column
                        // is DICOM_Folder_Name, which is what we're interested in
                        // so we look directly at index 1.
                        if($OtherItems[1]['CommentID'] != $item['CommentID']) {
                            continue;
                        }
                        // Add this DICOM Folder Name
                        $this->tpl_data['items'][$OtherRow]['1']['value'] .= ", $item[DICOM_Folder_Name]";
                        // Skip the whole row, since a row has already been added for this CommentID
                        continue 3;
                    }
                }
                

                $this->tpl_data['items'][$x][$i]['value'] = _makePretty($key, $val);

                $this->tpl_data['items'][$x][$i]['name'] = $key;
                $this->tpl_data['items'][$x][$i]['CandID'] = $item['CandID'];
                $this->tpl_data['items'][$x][$i]['CommentID'] = $item['CommentID'];
                $this->tpl_data['items'][$x][$i]['SessionID'] = $item['SessionID'];
                $i++;
            }
            $x++;
        }
    }
}
