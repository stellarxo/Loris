<?php
require_once "NDB_Form.class.inc";
require_once "NDB_Menu_Filter_final_radiological_review.class.inc";

class NDB_Form_final_radiological_review extends NDB_Form
{
    var $__table = 'final_radiological_review';

    function _hasAccess() 
    {
        return $this->_has_perm('view_final_radiological_review');
    }
    // Wrapper to get the user object and check the permission.
    function _has_perm($perm)
    {
        $user =& User::singleton();
        if (PEAR::isError($user)) {
            return PEAR::raiseError("User Error: " .$user->getMessage());
        }
        return $user->hasPermission($perm);
    }
    function final_radiological_review()
    {
        $yes_no = array('' => '', '1' => 'Yes', '0' => 'No');
        $exclusionary = array('' => '',
                'exclusionary' => 'Exclusionary',
                'non_exclusionary' => 'Non-Exclusionary'
        );
        $results = array('' => '', 
                         'normal' => 'Normal', 
                         'abnormal' => 'Abnormal', 
                         'atypical' => 'Atypical');
        $abnormality = array('' => '',
                            '0' => 'None',
                            '1' => 'Minimal',
                            '2' => 'Mild',
                            '3' => 'Moderate',
                            '4' => 'Marked');

        $DB =& Database::singleton();
        $DB->select("SELECT * FROM examiners WHERE radiologist=True", &$radiologists_q);

        $radiologists[''] = '';
        foreach($radiologists_q as &$row)
        {
            $radiologists[$row['examinerID']] = $row['full_name'];
        }

        $this->form->addElement('select', 'Final_Examiner', 'Radiologist/Reviewer:', $radiologists);
        $this->form->addElement('static', 'CandID', 'DCCID:', 'Unknown');
        $this->form->addElement('static', 'PSCID', 'PSCID:', 'Unknown');
        $this->form->addElement('static', 'SessionID', 'Session ID:', '');
        $this->form->addElement('static', 'CommentID', 'Comment ID:', '');
        $this->form->addElement('static', 'Visit_label', 'Visit Label:', '');

        $this->form->addElement('static', 'DICOM_Folder_Name', 'DICOM Folder:', 'Unknown');
        $this->form->addElement('static', 'DICOM_ID', 'DICOM ID:', 'Unknown');

        $this->form->addElement('select', 'Review_Done', 'Review Done:', $yes_no);
        $this->form->addElement('select', 'Final_Review_Results', 'Results of Radiology Review:', $results);
        $this->form->addElement('select', 'Final_Exclusionary', 'Exclusionary Status:', $exclusionary);
        $this->form->addElement('select', 'SAS', 'SAS Score:', $abnormality);
        $this->form->addElement('select', 'PVS', 'PVS Score:', $abnormality);
        $this->form->addElement('textarea', 'Final_Incidental_Findings', 'Description of Incidental Findings (Comments):');
        $this->form->addElement('select', 'Finalized', 'Is review finalized?', $yes_no);

        $this->form->addElement('select', 'Final_Examiner2', 'Radiologist/Reviewer:', $radiologists);
        $this->form->addElement('select', 'Review_Done2', 'Review Done:', $yes_no);
        $this->form->addElement('select', 'Final_Review_Results2', 'Results of Radiology Review:', $results);
        $this->form->addElement('select', 'Final_Exclusionary2', 'Exclusionary Status:', $exclusionary);
        $this->form->addElement('select', 'SAS2', 'SAS Score:', $abnormality);
        $this->form->addElement('select', 'PVS2', 'PVS Score:', $abnormality);
        $this->form->addElement('textarea', 'Final_Incidental_Findings2', 'Description of Incidental Findings (Comments):');
        // Original review, this might move
        $this->form->addElement('static', 'Original_Scan_Done', 'Original Scan Done:', 'Unknown');
        $this->form->addElement('static', 'Original_Review_Results', 'Original Results:', 'Unknown');
        $this->form->addElement('static', 'Original_Exclusionary', 'Original Exclusionary Results:', '');
        $this->form->addElement('static', 'Original_Incidental_Findings', 'Original Incidental Findings:', '');
        $this->form->addElement('static', 'Original_Examiner', 'Original Radiologist/Reviewer:', 'Unknown');

        $this->form->addElement('static', 'history', '', '');

        if($this->_has_perm('edit_final_radiological_review') == False)
        {
            $this->form->freeze();
        }

    }

    function _getDefaults()
    {
        if(isset($this->identifier)) 
        {
            $DB =& Database::singleton();
            // Get the basics for the final radiological review
            $DB->selectRow("SELECT * FROM $this->__table WHERE CommentID=" . $DB->quote($this->identifier), &$final_review);


            // Get the info for the original review, this might move somewhere else later. If not, can
            // change it to a join for a slight performance improvement
            $DB->selectRow("SELECT r.Scan_done as Original_Scan_Done, r.review_results as Original_Review_Results, r.abnormal_atypical_exculsionary as Original_Exclusionary, r.Incidental_findings as Original_Incidental_Findings, e.full_name as Original_Examiner, c.PSCID as PSCID, c.CandID as CandID, s.Visit_Label as Visit_label, GROUP_CONCAT(substring_index(t.sourcelocation, '/', -1)) as DICOM_Folder_Name, f.SessionID as SessionID, f.CommentID as CommentID FROM radiology_review r LEFT JOIN examiners e on (e.ExaminerID=r.Examiner) LEFT JOIN flag f ON (f.CommentID=r.CommentID) LEFT JOIN session s ON (s.ID=f.SessionID) LEFT JOIN candidate c ON (c.CandID=s.CandID) LEFT JOIN tarchive t ON (upper(t.PatientName)=CONCAT(upper(c.PSCID), '_', upper(s.CandID), '_', upper(s.visit_label))) WHERE r.CommentID=" . $DB->quote($this->identifier), &$original_review);


            $DB->select('SELECT userID, changeDate, col, old, new FROM history WHERE tbl=\'' . $this->__table . '\' AND primaryVals=' . $DB->quote($this->identifier) . 'ORDER BY changeDate DESC', &$history );

            foreach($history as &$history_item)
            {
                $history_display .= '<tr><td>' . $history_item['changeDate'] . '</td><td>' . $history_item['userID'] . '</td><td>' . $history_item['col'] . '</td><td>' . _makePretty($history_item['col'], $history_item['old']) . '</td><td>' . _makePretty($history_item['col'], $history_item['new']) . '</td></tr>';
            }
            $defaults = array_merge((array)$final_review, (array)$original_review, array( 'history' => $history_display));

            if($defaults['Final_Review_Results'] !=  $defaults['Final_Review_Results2'] || $defaults['Final_Exclusionary'] != $defaults['Final_Exclusionary2'] || $defaults['SAS'] != $defaults['SAS2'] || $defaults ['PVS'] != $defaults['PVS2']) {
                $this->tpl_data['conflicts'][] = "Conflict between final and extra review";
            }
            if($defaults['Final_Review_Results'] != $defaults['Original_Review_Results'] || $defaults['Original_Exclusionary'] != $defaults['Final_Exclusionary']) {
                $this->tpl_data['conflicts'][] = "Conflict between original and final review";
            }

            return $defaults;
        }
        return array();
    }

    function _process($values)
    {
        if(!is_array($values) || count($values) == 0 || $this->_has_perm('edit_final_radiological_review') == False) 
        {
            return true;
        }

        $DB =& Database::singleton();
        if(isset($this->identifier))
        {
            $DB->selectRow("SELECT 'x' FROM " . $this->__table . " WHERE CommentID=" . $DB->quote($this->identifier), &$exists);
            
            if($exists == array()) 
            {
                $insert_values = array_merge(array('CommentID' => $this->identifier), $values);
                $DB->insert($this->__table, $insert_values);
            }
            else
            {
                $DB->update($this->__table, $values, array('CommentID' => $this->identifier));
            }

        }
        return true;
    }


}
?>
