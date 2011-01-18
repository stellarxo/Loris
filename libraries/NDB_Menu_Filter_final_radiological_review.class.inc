<?
require_once 'NDB_Menu_Filter.class.inc';

// Utility function to make things more human readable.
// This is used both below and in the history on the NDB_Form
function _makePretty($key, $val)
{
    if($key == 'Review_Done' || $key=='Conflict1' || $key=="Finalized")
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

    if($key == 'Final_Review_Results' || $key == 'Exclusionary_Status' || $key=="Final_Exclusionary" || $key == "Results")
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
        $conflict_condition1 = "(case when orig.review_results <> r.final_review_results then True when orig.abnormal_atypical_exculsionary <>  r.final_exclusionary THEN True WHEN r.Final_Review_Results <> r.Final_Review_Results2 THEN True WHEN r.Final_Exclusionary <> r.Final_Exclusionary2 THEN True WHEN r.SAS <> r.SAS2 THEN True WHEN r.PVS <> r.PVS2 THEN True ELSE False end)";
        $conflict_condition2 = "(case when r.Final_Review_Results <> r.Final_Review_Results2 THEN 'prim_second' WHEN r.Final_Exclusionary <> r.Final_Exclusionary2 THEN 'prim_second' WHEN r.SAS <> r.SAS2 THEN 'prim_second' WHEN r.PVS <> r.PVS2 THEN 'prim_second' ELSE False end)";

        $this->query = " FROM radiology_review orig LEFT JOIN final_radiological_review r ON (r.CommentID=orig.CommentID) JOIN flag f on (f.CommentID=orig.CommentID) JOIN session s on (s.ID=f.SessionID) JOIN candidate c ON (c.CandID=s.CandID) WHERE orig.commentid NOT LIKE 'DDE_%' AND orig.commentid IS NOT NULL AND s.active='Y' AND s.Cancelled='N' AND NOT (f.Administration='None' AND f.Data_entry='Complete' )";
        $this->columns = array('c.PSCID as PSCID', 'c.CandID as DCCID', 's.visit_label as Visit_Label', 'c.CenterID as Site', 'c.DOB as Birth_Date', 'COALESCE(r.Review_Done, False) as Review_Done', 'r.Final_Review_Results as Results', 'r.Final_Exclusionary as Exclusionary_Status', 'r.sas as SAS', 'r.pvs as PVS', 'orig.CommentID as CommentID', "$conflict_condition1 as Conflict1, $conflict_condition2 as Conflict2", 'r.Finalized as Finalized', 'r.Final_Incidental_Findings as Comments' );
        $this->order_by = 'PSCID';
        $this->headers = array('PSCID',
                               'DCCID', 'Visit_Label', 
                               'Birth_Date', 'Review_Done', 
                               'Results', 
                               'Exclusionary_Status', 'SAS', 'PVS', 
                               'Conflict',
                               'Finalized',
                               'Comments'
        );
        $this->validFilters = array('c.CandID', 'r.DICOM_ID', 's.visit_label', 'c.PSCID', 'r.Final_Review_Results', 'COALESCE(r.Review_Done, False)', 'r.sas', 'r.pvs', 'r.Final_Exclusionary', $conflict_condition1, $conflict_condition2, 'r.Finalized', 'c.CenterID');
        $this->formToFilter = array (
                                    //'folder' => 'substring_index(t.sourcelocation, \'/\', -1)',
                                    'dccid' => 'c.CandID',
                                    'site' => 'c.CenterID',
                                    'Visit_label' => 's.visit_label',
                                    'pscid' => 'c.PSCID',
                                    'Review_done' => 'COALESCE(r.Review_Done, False)',
                                    'Results' => 'r.Final_Review_Results',
                                    'Final_Review_Results' => 'r.Final_Review_Results',
                                    'Exclusionary_Status' => 'r.Final_Exclusionary',
                                    'PVS' => 'r.pvs',
                                    'SAS' => 'r.sas',
                                    'Conflict1' => $conflict_condition1,
                                    'Conflict2' => $conflict_condition2,
                                    'Finalized' =>  'r.Finalized'
        );
    }

    function _setFilterForm()
    {
        $list_of_visit_labels = array(null => 'Any', 'V06' => 'V06', 'V12' => 'V12', 'V24' => 'V24');
        $options_boolean= array(null => 'Any', True => 'Yes', False => 'No');
        $conflict_options1 = array(null => 'Any', True => 'Yes', False => 'No', );
        $conflict_options2 = array(null => 'Any', 'prim_second' => 'Yes', False => 'No');
        $comment_options = array(null => 'Any', 'True' => 'Yes', 'False' => 'No');
        $bob_score = array(null => 'Any', '0' => 'None', '1' => 'Minimal', '2' => 'Mild', '3' => 'Moderate', '4' => 'Marked');
        $abnormal_atypical = array(null => 'Any', 'abnormal' => 'Abnormal', 'atypical' => 'Atypical', 'normal' => 'Normal');
        $exclude = array(null => 'Any', 'exclusionary' => 'Exclusionary', 'non_exclusionary' => 'Non Exclusionary');

        //$this->form->addElement('text', 'folder', 'DICOM Folder Name:', array("size"=>20, "maxlength"=>30));
        $this->form->addElement('text', 'dicomid', 'DICOM ID:', array("size"=>9, "maxlength"=>20));
        $this->form->addElement('text', 'pscid', 'PSCID:', array("size"=>9, "maxlength"=>11));
        $this->form->addElement('text', 'dccid', 'DCCID:', array("size"=>9, "maxlength"=>6));
        $this->form->addElement('select', 'Visit_label', 'Visit Label:', $list_of_visit_labels);
        $this->form->addElement('select', 'site', 'Site', array('' => 'Any', '2' => 'SEA', '3' => 'PHI', '4' => 'STL', '5' => 'UNC'));
        $this->form->addElement('select', 'Review_done', 'Review Done:', $options_boolean);
        $this->form->addElement('select', 'Conflict1', 'Conflict between any reviews:', $conflict_options1);
        $this->form->addElement('select', 'Conflict2', 'Conflict between final and extra reviews:', $conflict_options2);

        $this->form->addElement('select', 'SAS', 'SAS (Subarachnoid Spaces):', $bob_score);
        $this->form->addElement('select', 'PVS', 'PVS (Perivascular Spaces):', $bob_score);

        $this->form->addElement('select', 'Final_Review_Results', 'Results', $abnormal_atypical);
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
                if ($key == 'Conflict2') continue;


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
