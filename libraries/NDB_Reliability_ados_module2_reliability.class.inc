<?php
require_once "NDB_Reliability.class.inc";
//require_once "NDB_BVL_Instrument.class.inc";

/**
 * The forms for the tracking log menu
 * @package mri
 * @subpackage NIHPD
 */
class NDB_Reliability_ados_module2_reliability extends NDB_Reliability

{
    function _getDefaults()
    {
        $DB =& Database::singleton();

        $DB->select("SELECT * FROM ados_module2_reliability", $result);
               
        //print_r($this->identifier);
        if (!empty($this->identifier)) { 
            
            // set the ados_module2_reliability values 
            $DB->selectRow("SELECT * FROM ados_module2_reliability WHERE CommentID = '$this->identifier' AND reliability_center_id = '$this->reliability_center_id'", $row);
     
            // Set the defaults
            // print_r($row['CommentID']);
            $initial_table = preg_replace('/_reliability/', '', $this->name);
            $defaults['Examiner'] = $row['Examiner'];
            $defaults['Date_taken'] = $row['Date_taken'];
            $defaults['CommentID'] = "<a href=\"main.php?test_name=reliability_breakdown&instrument=$initial_table&CommentID=$row[CommentID]\">" . $row['CommentID'] . "</a>";
            $defaults['Reliability_score_all_items'] = $row['Reliability_score_all_items'];
            $defaults['Reliability_score_scored_items'] = $row['Reliability_score_scored_items'];
            $defaults['a1'] = $row['a1'];
            $defaults['a2'] = $row['a2'];
            $defaults['a3'] = $row['a3'];
            $defaults['a4'] = $row['a4'];
            $defaults['a5'] = $row['a5'];
            $defaults['a6'] = $row['a6'];
            $defaults['a7'] = $row['a7'];
            $defaults['a8'] = $row['a8'];
            $defaults['b1'] = $row['b1'];
            $defaults['b2'] = $row['b2'];
            $defaults['b3'] = $row['b3'];
            $defaults['b4'] = $row['b4'];
            $defaults['b5'] = $row['b5'];
            $defaults['b6'] = $row['b6'];
            $defaults['b7'] = $row['b7'];
            $defaults['b8'] = $row['b8'];
            $defaults['b9'] = $row['b9'];
            $defaults['b10'] = $row['b10'];
            $defaults['b11'] = $row['b11'];
            $defaults['c1'] = $row['c1'];
            $defaults['c2'] = $row['c2'];
            $defaults['d1'] = $row['d1'];
            $defaults['d2'] = $row['d2'];
            $defaults['d3'] = $row['d3'];
            $defaults['d4'] = $row['d4'];
            $defaults['e1'] = $row['e1'];
            $defaults['e2'] = $row['e2'];
            $defaults['e3'] = $row['e3'];
            
        } else {
            echo("Identifer empty! No ID has been chosen. Please contact Samir at the DCC.<br>");
        }
        
        $sites = array(1 => 'DCC', 2 => 'SEA', 3 => 'PHI', 4 => 'STL', 5 => 'UNC');
        $defaults['reliability_center'] = $sites[$this->reliability_center_id];

        return $defaults;
    }
   
    function score(){

        //holds raw question values
        $score_record = array();
       
        //holds calculated
        $db =& Database::singleton();

        // null scores
        //$this->_nullScores();
       
        //Get values from both tables of adi_r (reliability and original)
        $query = "SELECT * FROM ados_module2_reliability WHERE CommentID='$this->identifier' AND reliability_center_id = '$this->reliability_center_id'";
        $query1 = "SELECT * FROM ados_module2 WHERE CommentID='".$this->identifier."'";
        $query2 = "SELECT * FROM ados_module2_reliability_lookup WHERE CommentID='standard_ados_module2_SEA0012'";
         
        $db->selectRow($query, $score_record);
        $db->selectRow($query1, $score_record1);
        $db->selectRow($query2, $score_record2);
       
        // If the reliability is to be compared to the gold standard
        if ($score_record['Gold_standard']=='Gold_standard_SEA0012'){
            
            
            $reliability_count_raw=0;            
            $reliability_count_scored=0;            
            $denominator=0;
            $denominator_scored=0;

            // individual items
                if($score_record['a1']=='8' AND $score_record2['a1']=='8'){}    
				elseif ($score_record['a1'] =='9' && $score_record2['a1'] =='9'){}
                else {
                    $denominator++; 
                    if($score_record2['a1'] != $score_record['a1']) {$reliability_count_raw++;}}
                
                if($score_record['a2']=='8' AND $score_record2['a2']=='8'){}	 
                elseif ($score_record['a2'] =='9' && $score_record2['a2'] =='9'){}
                else {
                    $denominator++;
                    if($score_record2['a2'] != $score_record['a2']) {$reliability_count_raw++;}}
                
                if($score_record['a3']=='8' AND $score_record2['a3']=='8'){}	 
                elseif ($score_record['a3'] =='9' && $score_record2['a3'] =='9'){}
                else {
                    $denominator++;
                    if($score_record2['a3'] != $score_record['a3'] ) {$reliability_count_raw++;}}
                
                if($score_record['a4']=='8' AND $score_record2['a4']=='8'){}	 
				elseif ($score_record['a4'] =='9' && $score_record2['a4'] =='9'){}
                else {
                    $denominator++;
                    if($score_record2['a4']  != $score_record['a4'] ) {$reliability_count_raw++;}}

                if($score_record['a5']=='8' AND $score_record2['a5']=='8'){}	 
				elseif ($score_record['a5'] =='9' && $score_record2['a5'] =='9'){}
                else {
                    $denominator++;$denominator_scored++;
                    if($score_record2['a5']  != $score_record['a5'] ) {$reliability_count_raw++;$reliability_count_scored++;}}
                
				if($score_record['a6']=='8' AND $score_record2['a6']=='8'){}	 
				elseif ($score_record['a6'] =='9' && $score_record2['a6'] =='9'){}
                else {
                    $denominator++;
                    if($score_record2['a6'] != $score_record['a6'] ) {$reliability_count_raw++;}}

                if($score_record['a7']=='8' AND $score_record2['a7']=='8'){}	 
				elseif ($score_record['a7'] =='9' && $score_record2['a7'] =='9'){}
                else {
                    $denominator++;$denominator_scored++;
                    if($score_record2['a7'] != $score_record['a7'] ) {$reliability_count_raw++;$reliability_count_scored++;}}

                if($score_record['a8']=='8' AND $score_record2['a8']=='8'){}	 
				elseif ($score_record['a8'] =='9' && $score_record2['a8'] =='9'){}
                else {
                    $denominator++;$denominator_scored++;
                    if($score_record2['a8'] != $score_record['a8'] ) {$reliability_count_raw++;$reliability_count_scored++;}}
                if($score_record['b1']=='8' AND $score_record2['b1']=='8'){}	 
				elseif ($score_record['b1'] =='9' && $score_record2['b1'] =='9'){}
                else {
                    $denominator++;$denominator_scored++;
                    if($score_record2['b1'] != $score_record['b1'] ) {$reliability_count_raw++;$reliability_count_scored++;}}
                if($score_record['b2']=='8' AND $score_record2['b2']=='8'){}	 
				elseif ($score_record['b2'] =='9' && $score_record2['b2'] =='9'){}
                else {
                    $denominator++;$denominator_scored++;
                    if($score_record2['b2']  != $score_record['b2'] ) {$reliability_count_raw++;$reliability_count_scored++;}}
                if($score_record['b3']=='8' AND $score_record2['b3']=='8'){}	 
				elseif ($score_record['b3'] =='9' && $score_record2['b3'] =='9'){}
                else {
                    $denominator++;$denominator_scored++;
                    if($score_record2['b3'] != $score_record['b3'] ) {$reliability_count_raw++;$reliability_count_scored++;}}
                if($score_record['b4']=='8' AND $score_record2['b4']=='8'){}	 
				elseif ($score_record['b4'] =='9' && $score_record2['b4'] =='9'){}
                else {
                    $denominator++;
                    if($score_record2['b4']  != $score_record['b4'] ) {$reliability_count_raw++;}}
                if($score_record['b5']=='8' AND $score_record2['b5']=='8'){}	 
				elseif ($score_record['b5'] =='9' && $score_record2['b5'] =='9'){}
                else {
                    $denominator++;$denominator_scored++;
                    if($score_record2['b5']  != $score_record['b5'] ) {$reliability_count_raw++;$reliability_count_scored++;}}
                if($score_record['b6']=='8' AND $score_record2['b6']=='8'){}	 
				elseif ($score_record['b6'] =='9' && $score_record2['b6'] =='9'){}
                else {
                    $denominator++;$denominator_scored++;
                    if($score_record2['b6'] != $score_record['b6'] ) {$reliability_count_raw++;$reliability_count_scored++;}}
                if($score_record['b7']=='8' AND $score_record2['b7']=='8'){}	 
				elseif ($score_record['b7'] =='9' && $score_record2['b7'] =='9'){}
                else {
                    $denominator++;
                    if($score_record2['b7']  != $score_record['b7'] ) {$reliability_count_raw++;}}
                if($score_record['b8']=='8' AND $score_record2['b8']=='8'){}	 
				elseif ($score_record['b8'] =='9' && $score_record2['b8'] =='9'){}
                else {
                    $denominator++;$denominator_scored++;
                    if($score_record2['b8'] != $score_record['b8'] ) {$reliability_count_raw++;$reliability_count_scored++;}}
                if($score_record['b9']=='8' AND $score_record2['b9']=='8'){}	 
				elseif ($score_record['b9'] =='9' && $score_record2['b9'] =='9'){}
                else {
                    $denominator++;
                    if($score_record2['b9']  != $score_record['b9'] ) {$reliability_count_raw++;}}
                if($score_record['b10']=='8' AND $score_record2['b10']=='8'){}  
				elseif ($score_record['b10'] =='9' && $score_record2['b10'] =='9'){}
                else {
                    $denominator++;$denominator_scored++;
                    if($score_record2['b10']  != $score_record['b10'] ) {$reliability_count_raw++;$reliability_count_scored++;}}
                if($score_record['b11']=='8' AND $score_record2['b11']=='8'){}  
				elseif ($score_record['b11'] =='9' && $score_record2['b11'] =='9'){}
                else {
                    $denominator++;$denominator_scored++;
                    if($score_record2['b11']  != $score_record['b11'] ) {$reliability_count_raw++;$reliability_count_scored++;}}
                    
                if($score_record['c1']=='8' AND $score_record2['c1']=='8'){}	 
				elseif ($score_record['c1'] =='9' && $score_record2['c1'] =='9'){}
                else {
                    $denominator++;
                    if($score_record2['c1'] != $score_record['c1'] ) {$reliability_count_raw++;}}
                if($score_record['c2']=='8' AND $score_record2['c2']=='8'){}	 
				elseif ($score_record['c2'] =='9' && $score_record2['c2'] =='9'){}
                else {
                    $denominator++;
                    if($score_record2['c2']  != $score_record['c2'] ) {$reliability_count_raw++;}}
                if($score_record['d1']=='8' AND $score_record2['d1']=='8'){}	 
				elseif ($score_record['d1'] =='9' && $score_record2['d1'] =='9'){}
                else {
                    $denominator++;$denominator_scored++;
                    if($score_record2['d1']  != $score_record['d1'] ) {$reliability_count_raw++;$reliability_count_scored++;}}
                if($score_record['d2']=='8' AND $score_record2['d2']=='8'){}	 
				elseif ($score_record['d2'] =='9' && $score_record2['d2'] =='9'){}
                else {
                    $denominator++;$denominator_scored++;
                    if($score_record2['d2']  != $score_record['d2'] ) {$reliability_count_raw++;$reliability_count_scored++;}}
                if($score_record['d3']=='8' AND $score_record2['d3']=='8'){}	 
				elseif ($score_record['d3'] =='9' && $score_record2['d3']	=='9'){}
                else {
                    $denominator++;
                    if($score_record2['d3'] != $score_record['d3'] ) {$reliability_count_raw++;}}
                if($score_record['d4']=='8' AND $score_record2['d4']=='8'){}	 
				elseif ($score_record['d4'] =='9' && $score_record2['d4'] =='9'){}
                else {
                    $denominator++;$denominator_scored++;
                    if($score_record2['d4']  != $score_record['d4'] ) {$reliability_count_raw++;$reliability_count_scored++;}}

                if($score_record['e1']=='8' AND $score_record2['e1']=='8'){}	 
				elseif ($score_record['e1'] =='9' && $score_record2['e1'] =='9'){}
                else {
                    $denominator++;
                    if($score_record2['e1'] != $score_record['e1'] ) {$reliability_count_raw++;}}
                if($score_record['e2']=='8' AND $score_record2['e2']=='8'){}	 
				elseif ($score_record['e2'] =='9' && $score_record2['e2'] =='9'){}
                else {
                    $denominator++;
                    if($score_record2['e2']  != $score_record['e2'] ) {$reliability_count_raw++;}}

                if($score_record['e3']=='8' AND $score_record2['e3']=='8'){}	 
				elseif ($score_record['e3'] =='9' && $score_record2['e3'] =='9'){}
                else {
                    $denominator++;
                if($score_record2['e3'] != $score_record['e3']) {$reliability_count_raw++;}}
                          
                        
        }
        // If the reliability is to be compared to the initial data entry
        elseif ($score_record['Gold_standard']=='Initial_entry') {
            
            
               $reliability_count_raw=0;            
                $reliability_count_scored=0;            
                $denominator=0;
                $denominator_scored=0;

                // individual items
                    if($score_record['a1']=='8' AND $score_record1['a1']=='8'){}    
    				elseif ($score_record['a1'] =='9' && $score_record1['a1'] =='9'){}
                    else {
                        $denominator++; 
                        if($score_record1['a1'] != $score_record['a1']) {$reliability_count_raw++;}}

                    if($score_record['a2']=='8' AND $score_record1['a2']=='8'){}	 
                    elseif ($score_record['a2'] =='9' && $score_record1['a2'] =='9'){}
                    else {
                        $denominator++;
                        if($score_record1['a2'] != $score_record['a2']) {$reliability_count_raw++;}}

                    if($score_record['a3']=='8' AND $score_record1['a3']=='8'){}	 
                    elseif ($score_record['a3'] =='9' && $score_record1['a3'] =='9'){}
                    else {
                        $denominator++;
                        if($score_record1['a3'] != $score_record['a3'] ) {$reliability_count_raw++;}}

                    if($score_record['a4']=='8' AND $score_record1['a4']=='8'){}	 
    				elseif ($score_record['a4'] =='9' && $score_record1['a4'] =='9'){}
                    else {
                        $denominator++;
                        if($score_record1['a4']  != $score_record['a4'] ) {$reliability_count_raw++;}}

                    if($score_record['a5']=='8' AND $score_record1['a5']=='8'){}	 
    				elseif ($score_record['a5'] =='9' && $score_record1['a5'] =='9'){}
                    else {
                        $denominator++;$denominator_scored++;
                        if($score_record1['a5']  != $score_record['a5'] ) {$reliability_count_raw++;$reliability_count_scored++;}}

    				if($score_record['a6']=='8' AND $score_record1['a6']=='8'){}	 
    				elseif ($score_record['a6'] =='9' && $score_record1['a6'] =='9'){}
                    else {
                        $denominator++;
                        if($score_record1['a6'] != $score_record['a6'] ) {$reliability_count_raw++;}}

                    if($score_record['a7']=='8' AND $score_record1['a7']=='8'){}	 
    				elseif ($score_record['a7'] =='9' && $score_record1['a7'] =='9'){}
                    else {
                        $denominator++;$denominator_scored++;
                        if($score_record1['a7'] != $score_record['a7'] ) {$reliability_count_raw++;$reliability_count_scored++;}}

                    if($score_record['a8']=='8' AND $score_record1['a8']=='8'){}	 
    				elseif ($score_record['a8'] =='9' && $score_record1['a8'] =='9'){}
                    else {
                        $denominator++;$denominator_scored++;
                        if($score_record1['a8'] != $score_record['a8'] ) {$reliability_count_raw++;$reliability_count_scored++;}}
                    if($score_record['b1']=='8' AND $score_record1['b1']=='8'){}	 
    				elseif ($score_record['b1'] =='9' && $score_record1['b1'] =='9'){}
                    else {
                        $denominator++;$denominator_scored++;
                        if($score_record1['b1'] != $score_record['b1'] ) {$reliability_count_raw++;$reliability_count_scored++;}}
                    if($score_record['b2']=='8' AND $score_record1['b2']=='8'){}	 
    				elseif ($score_record['b2'] =='9' && $score_record1['b2'] =='9'){}
                    else {
                        $denominator++;$denominator_scored++;
                        if($score_record1['b2']  != $score_record['b2'] ) {$reliability_count_raw++;$reliability_count_scored++;}}
                    if($score_record['b3']=='8' AND $score_record1['b3']=='8'){}	 
    				elseif ($score_record['b3'] =='9' && $score_record1['b3'] =='9'){}
                    else {
                        $denominator++;$denominator_scored++;
                        if($score_record1['b3'] != $score_record['b3'] ) {$reliability_count_raw++;$reliability_count_scored++;}}
                    if($score_record['b4']=='8' AND $score_record1['b4']=='8'){}	 
    				elseif ($score_record['b4'] =='9' && $score_record1['b4'] =='9'){}
                    else {
                        $denominator++;
                        if($score_record1['b4']  != $score_record['b4'] ) {$reliability_count_raw++;}}
                    if($score_record['b5']=='8' AND $score_record1['b5']=='8'){}	 
    				elseif ($score_record['b5'] =='9' && $score_record1['b5'] =='9'){}
                    else {
                        $denominator++;$denominator_scored++;
                        if($score_record1['b5']  != $score_record['b5'] ) {$reliability_count_raw++;$reliability_count_scored++;}}
                    if($score_record['b6']=='8' AND $score_record1['b6']=='8'){}	 
    				elseif ($score_record['b6'] =='9' && $score_record1['b6'] =='9'){}
                    else {
                        $denominator++;$denominator_scored++;
                        if($score_record1['b6'] != $score_record['b6'] ) {$reliability_count_raw++;$reliability_count_scored++;}}
                    if($score_record['b7']=='8' AND $score_record1['b7']=='8'){}	 
    				elseif ($score_record['b7'] =='9' && $score_record1['b7'] =='9'){}
                    else {
                        $denominator++;
                        if($score_record1['b7']  != $score_record['b7'] ) {$reliability_count_raw++;}}
                    if($score_record['b8']=='8' AND $score_record1['b8']=='8'){}	 
    				elseif ($score_record['b8'] =='9' && $score_record1['b8'] =='9'){}
                    else {
                        $denominator++;$denominator_scored++;
                        if($score_record1['b8'] != $score_record['b8'] ) {$reliability_count_raw++;$reliability_count_scored++;}}
                    if($score_record['b9']=='8' AND $score_record1['b9']=='8'){}	 
    				elseif ($score_record['b9'] =='9' && $score_record1['b9'] =='9'){}
                    else {
                        $denominator++;
                        if($score_record1['b9']  != $score_record['b9'] ) {$reliability_count_raw++;}}
                    if($score_record['b10']=='8' AND $score_record1['b10']=='8'){}  
    				elseif ($score_record['b10'] =='9' && $score_record1['b10'] =='9'){}
                    else {
                        $denominator++;$denominator_scored++;
                        if($score_record1['b10']  != $score_record['b10'] ) {$reliability_count_raw++;$reliability_count_scored++;}}
                    if($score_record['b11']=='8' AND $score_record1['b11']=='8'){}  
    				elseif ($score_record['b11'] =='9' && $score_record1['b11'] =='9'){}
                    else {
                        $denominator++;$denominator_scored++;
                        if($score_record1['b11']  != $score_record['b11'] ) {$reliability_count_raw++;$reliability_count_scored++;}}

                    if($score_record['c1']=='8' AND $score_record1['c1']=='8'){}	 
    				elseif ($score_record['c1'] =='9' && $score_record1['c1'] =='9'){}
                    else {
                        $denominator++;
                        if($score_record1['c1'] != $score_record['c1'] ) {$reliability_count_raw++;}}
                    if($score_record['c2']=='8' AND $score_record1['c2']=='8'){}	 
    				elseif ($score_record['c2'] =='9' && $score_record1['c2'] =='9'){}
                    else {
                        $denominator++;
                        if($score_record1['c2']  != $score_record['c2'] ) {$reliability_count_raw++;}}
                    if($score_record['d1']=='8' AND $score_record1['d1']=='8'){}	 
    				elseif ($score_record['d1'] =='9' && $score_record1['d1'] =='9'){}
                    else {
                        $denominator++;$denominator_scored++;
                        if($score_record1['d1']  != $score_record['d1'] ) {$reliability_count_raw++;$reliability_count_scored++;}}
                    if($score_record['d2']=='8' AND $score_record1['d2']=='8'){}	 
    				elseif ($score_record['d2'] =='9' && $score_record1['d2'] =='9'){}
                    else {
                        $denominator++;$denominator_scored++;
                        if($score_record1['d2']  != $score_record['d2'] ) {$reliability_count_raw++;$reliability_count_scored++;}}
                    if($score_record['d3']=='8' AND $score_record1['d3']=='8'){}	 
    				elseif ($score_record['d3'] =='9' && $score_record1['d3']	=='9'){}
                    else {
                        $denominator++;
                        if($score_record1['d3'] != $score_record['d3'] ) {$reliability_count_raw++;}}
                    if($score_record['d4']=='8' AND $score_record1['d4']=='8'){}	 
    				elseif ($score_record['d4'] =='9' && $score_record1['d4'] =='9'){}
                    else {
                        $denominator++;$denominator_scored++;
                        if($score_record1['d4']  != $score_record['d4'] ) {$reliability_count_raw++;$reliability_count_scored++;}}

                    if($score_record['e1']=='8' AND $score_record1['e1']=='8'){}	 
    				elseif ($score_record['e1'] =='9' && $score_record1['e1'] =='9'){}
                    else {
                        $denominator++;
                        if($score_record1['e1'] != $score_record['e1'] ) {$reliability_count_raw++;}}
                    if($score_record['e2']=='8' AND $score_record1['e2']=='8'){}	 
    				elseif ($score_record['e2'] =='9' && $score_record1['e2'] =='9'){}
                    else {
                        $denominator++;
                        if($score_record1['e2']  != $score_record['e2'] ) {$reliability_count_raw++;}}

                    if($score_record['e3']=='8' AND $score_record1['e3']=='8'){}	 
    				elseif ($score_record['e3'] =='9' && $score_record1['e3'] =='9'){}
                    else {
                        $denominator++;
                    if($score_record1['e3'] != $score_record['e3']) {$reliability_count_raw++;}}
                    
                                               
        }
              
        // end elseif
        else {
            echo("<font color='red'>Warning: no comparison selected. Contact Samir at the DCC.</font><BR>");
        } // end else
        
        // print_r($this->identifier);
  
        // Score the reliability
        $reliability['Reliability_score_all_items']= (($denominator-$reliability_count_raw)/$denominator*100);
        $reliability['Reliability_score_scored_items']= (($denominator_scored-$reliability_count_scored)/$denominator_scored*100);
        
        
        // Do the update here for the relibaility scores - saving the scores
		$result = $db->update("ados_module2_reliability", $reliability, array("CommentID"=>$this->identifier, "reliability_center_id" => $this->reliability_center_id));
		$result = $db->update("reliability", array("Reliability_score" => $reliability['Reliability_score_all_items']), array("CommentID"=>$this->identifier, "Instrument" => 'ados_module2', "reliability_center_id" => $this->reliability_center_id));
    } // end function score
    
    function _nullScores()
    {
        $db=& Database::singleton();
        
        // set the scores to NULL
        foreach ($this->scores as $val) {
            $scores[$val]=null;
        }

        // update the scores
        $success = $db->update("ados_module2_reliability",$scores,array("CommentID"=>$this->identifier, "reliability_center_id" => $this->reliability_center_id));
        return;
    }    

    function ados_module2_reliability()
    {
       $this->_addMetadataFields();
       $this->form->addElement("static", "reliability_center", "Site of Reliability Test:");
       
        $option01237 = array(""=>NULL, 0=>0, 1=>1, 2=>2, 3=>3,  7=>7, "not_answered"=>"Not Answered");
        $option0127 = array(""=>NULL, 0=>0, 1=>1, 2=>2,7=>7, "not_answered"=>"Not Answered");
        $option01278 = array(""=>NULL, 0=>0, 1=>1, 2=>2, 7=>7, 8=>8, "not_answered"=>"Not Answered");
        $option0123 = array(""=>NULL, 0=>0, 1=>1, 2=>2, 3=>3, "not_answered"=>"Not Answered");
        $option01238 = array(""=>NULL, 0=>0, 1=>1, 2=>2, 3=>3, 8=>8, "not_answered"=>"Not Answered");
        $option02 = array(""=>NULL, 0=>0, 2=>2, "not_answered"=>"Not Answered");
        $option012 = array(""=>NULL, 0=>0, 1=>1, 2=>2, "not_answered"=>"Not Answered");
        $option0128 = array(""=>NULL, 0=>0, 1=>1, 2=>2, 8=>8, "not_answered"=>"Not Answered");
        
        //Scoring header
        $this->form->addElement('header', 'instrument_title', "Scoring:");
        $this->form->addElement("static", "Reliability_score_all_items", "Reliability Score - all items (%):");
        $this->form->addElement("static", "Reliability_score_scored_items", "Reliability Score - scored items (%):");

        $GoldStandardArray = array("Initial_entry"=>"Initial Entry", "Gold_standard_SEA0012"=>"Gold standard SEA0012");
        $this->form->addElement("select", "Gold_standard", "Compare against:", $GoldStandardArray);
        
        $this->form->addElement("static", "CommentID", "CommentID:");
       
        //CODING
    	//Section A: Language and Communication
        $this->form->addElement('header', null, "CODING:");
        $this->form->addElement("static", null, "<BR>"); //line space

        $this->form->addElement('header', null, "Section A: Language and Communication");
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'a1', '1. Overall Level of Non-Echoed Language', $option01237);
        $this->form->addRule('a1', 'Required.', 'required');
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'a2', '2. Amount of Social Overtures/Maintenance of Attention', $option0127);
        $this->form->addRule('a2', 'Required.', 'required');
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'a3', '3. Speech Abnormalities Associated with Autism (Intonation/Volume/Rhythm/Rate)', $option01278);
        $this->form->addRule('a3', 'Required.', 'required');
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'a4', '4. Immediate Echolalia', $option0123);
        $this->form->addRule('a4', 'Required.', 'required');
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'a5', '5. Stereotyped/Idiosyncratic Use of Words or Phrases', $option0123);
        $this->form->addRule('a5', 'Required.', 'required');
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'a6', '6. Conversation', $option0123);
        $this->form->addRule('a6', 'Required.', 'required');
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'a7', '7. Pointing', $option0123);
        $this->form->addRule('a7', 'Required.', 'required');
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'a8', '8. Descriptive, Conventional, Instrumental, or Informational Gestures', $option01238);
        $this->form->addRule('a8', 'Required.', 'required');

        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement("static", null, "<BR>"); //line space


	   //Section B: Reciprocal Social Interaction
        $this->form->addElement('header', null, "Section B: Reciprocal Social Interaction");
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement("static", null, "<BR>"); //line space

        $this->form->addElement('select', 'b1', '1. Unusual Eye Contact', $option02);
        $this->form->addRule('b1', 'Required.', 'required');
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'b2', '2. Facial Expressions Directed to Others', $option012);
        $this->form->addRule('b2', 'Required.', 'required');
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'b3', '3. Shared Enjoyment in Interaction', $option0128);
        $this->form->addRule('b3', 'Required.', 'required');
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'b4', '4. Response to Name', $option0123);
        $this->form->addRule('b4', 'Required.', 'required');
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'b5', '5. Showing', $option012);
        $this->form->addRule('b5', 'Required.', 'required');
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'b6', '6. Spontaneous Initiation of Joint Attention', $option012);
        $this->form->addRule('b6', 'Required.', 'required');
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'b7', '7. Response to Joint Attention', $option0123);
        $this->form->addRule('b7', 'Required.', 'required');
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'b8', '8. Quality of Social Overtures', $option0123);
        $this->form->addRule('b8', 'Required.', 'required');
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'b9', '9. Quality of Social Response', $option0123);
        $this->form->addRule('b9', 'Required.', 'required');
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'b10', '10. Amount of Reciprocal Social Communication', $option0123);
        $this->form->addRule('b10', 'Required.', 'required');
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'b11', '11. Overall Quality of Rapport', $option0123);
        $this->form->addRule('b11', 'Required.', 'required');
        $this->form->addElement("static", null, "<BR>"); //line space
 
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement("static", null, "<BR>"); //line space

    	//Section C: Play
        $this->form->addElement('header', null, "Section C: Play");
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'c1', '1. Functional Play with Objects', $option0123);
        $this->form->addRule('c1', 'Required.', 'required');
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'c2', '2. Imagination/Creativity', $option0123);
        $this->form->addRule('c2', 'Required.', 'required');

        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement("static", null, "<BR>"); //line space

    	//Section D: Stereotyped Behaviors and Restricted Interests
        $this->form->addElement('header', null, "Section D: Stereotyped Behaviors and Restricted Interests");
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'd1', '1. Unusual Sensory Interest in Play Material/Person', $option012);
        $this->form->addRule('d1', 'Required.', 'required');
        $this->form->addElement("static", null, "<BR>"); //line space
     	$this->addTextAreaElement('d1_specify', $this->indent . "Please specify:");
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'd2', '2. Hand and Finger and Other Complex Mannerisms', $option012);
        $this->form->addRule('d2', 'Required.', 'required');
        $this->form->addElement("static", null, "<BR>"); //line space
    	$this->addTextAreaElement('d2_specify', $this->indent . "Please specify:");
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'd3', '3. Self-Injurious Behavior', $option012);
        $this->form->addRule('d3', 'Required.', 'required');
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'd4', '4. Unusually Repetitive Interests or Stereotyped Behaviors', $option0123);
        $this->form->addRule('d4', 'Required.', 'required');
        $this->form->addElement("static", null, "<BR>"); //line space
    	$this->addTextAreaElement('d4_specify', $this->indent . "Please specify unusual preoccupations, rituals, repetitive behaviors:");

        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement("static", null, "<BR>"); //line space

    	//Section E: Other Abnormal Behaviors
        $this->form->addElement('header', null, "Section E: Other Abnormal Behaviors");
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'e1', '1. Overactivity', $option0127);
        $this->form->addRule('e1', 'Required.', 'required');
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'e2', '2. Tantrums, Aggression, Negative or Disruptive Behavior', $option012);
        $this->form->addRule('e2', 'Required.', 'required');
        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement('select', 'e3', '3. Anxiety', $option012);
        $this->form->addRule('e3', 'Required.', 'required');

        $this->form->addElement("static", null, "<BR>"); //line space
        $this->form->addElement("static", null, "<BR>"); //line space


        $this->redirect = "test_name=$this->name"; // what does this do?
    } // End function 

    function _process($values)
    {
        $DB =& Database::singleton();
       
        $user =& User::singleton();
        
        $DB->selectRow("SELECT * FROM ados_module2_reliability WHERE CommentID = '$this->identifier' AND reliability_center_id = $this->reliability_center_id", $row);

          $invalid = $values['invalid'];
          $DB->update("reliability", array('invalid' => $invalid), array("CommentID"=>$this->identifier, "Instrument" => 'ados_module2', "reliability_center_id" => $this->reliability_center_id));
          unset($values['invalid']);
          
          if($invalid == "yes"){
            $this->form->freeze();
            $this->tpl_data['success'] = true;
            return;
          }

          if (empty($row)) {
            
            // insert the event
            $success = $DB->insert('ados_module2_reliability', array(
                                                                     'Examiner' => $values['Examiner'],
                                                                      'Date_taken' => $this->_getDatabaseDate($values['Date_taken']),
                                                                     'CommentID' => $this->identifier,
                                                                     "reliability_center_id" => $this->reliability_center_id,
                                                                     'Gold_standard' => $values['Gold_standard'],
                                                                     'Reliability_score_all_items' => $values['Reliability_score_all_items'],
                                                                     'Reliability_score_scored_items' => $values['Reliability_score_scored_items'],
                                                                     'a1' => $values['a1'],
                                                                     'a2' => $values['a2'],
                                                                     'a3' => $values['a3'],
                                                                     'a4' => $values['a4'],
                                                                     'a5' => $values['a5'],
                                                                     'a6' => $values['a6'],
                                                                     'a7' => $values['a7'],
                                                                     'a8' => $values['a8'],
                                                                     'b1' => $values['b1'],
                                                                     'b2' => $values['b2'],
                                                                     'b3' => $values['b3'],
                                                                     'b4' => $values['b4'],
                                                                     'b5' => $values['b5'],
                                                                     'b6' => $values['b6'],
                                                                     'b7' => $values['b7'],
                                                                     'b8' => $values['b8'],
                                                                     'b9' => $values['b9'],
                                                                     'b10' => $values['b10'],
                                                                     'b11' => $values['b11'],
                                                                     'c1' => $values['c1'],
                                                                     'c2' => $values['c2'],
                                                                     'd1' => $values['d1'],
                                                                     'd2' => $values['d2'],
                                                                     'd3' => $values['d3'],
                                                                     'd4' => $values['d4'],
                                                                     'e1' => $values['e1'],
                                                                     'e2' => $values['e2'],
                                                                     'e3' => $values['e3']
                                                                     ));
            $this->identifier = $DB->lastInsertID;
        } else {
            // update the event
            $success = $DB->update('ados_module2_reliability', array(
                                                                     // 'CommentID' => $this->identifier,
                                                                     'Examiner' => $values['Examiner'],
                                                                      'Date_taken' => $this->_getDatabaseDate($values['Date_taken']),
                                                                     'Gold_standard' => $values['Gold_standard'],
                                                                     'a1' => $values['a1'],
                                                                     'a2' => $values['a2'],
                                                                     'a3' => $values['a3'],
                                                                     'a4' => $values['a4'],
                                                                     'a5' => $values['a5'],
                                                                     'a6' => $values['a6'],
                                                                     'a7' => $values['a7'],
                                                                     'a8' => $values['a8'],
                                                                     'b1' => $values['b1'],
                                                                     'b2' => $values['b2'],
                                                                     'b3' => $values['b3'],
                                                                     'b4' => $values['b4'],
                                                                     'b5' => $values['b5'],
                                                                     'b6' => $values['b6'],
                                                                     'b7' => $values['b7'],
                                                                     'b8' => $values['b8'],
                                                                     'b9' => $values['b9'],
                                                                     'b10' => $values['b10'],
                                                                     'b11' => $values['b11'],
                                                                     'c1' => $values['c1'],
                                                                     'c2' => $values['c2'],
                                                                     'd1' => $values['d1'],
                                                                     'd2' => $values['d2'],
                                                                     'd3' => $values['d3'],
                                                                     'd4' => $values['d4'],
                                                                     'e1' => $values['e1'],
                                                                     'e2' => $values['e2'],
                                                                     'e3' => $values['e3']
                                                                     ),          
                                   array('CommentID'=>$this->identifier)
                                   ); 
        }
        
         $scoreResult = $this->score();
        
        $this->form->freeze();
        $this->tpl_data['success'] = true;
    }
    
    function _validate($values)
    {
        $DB =& Database::singleton();
        $query = "SELECT count(*) AS counter FROM candidate WHERE CandID='$values[CandID]' and PSCID='$values[PSCID]'";
        $recordsFound = $DB->selectOne($query);
        $errors = array();
        
        if($recordsFound < 1) {
            $errors['CandID'] = "Specified DCCID and PSCID do not exist or do not match.";
        }
        
        return $errors;
    }   
    
    function display()
    {
        if(!$this->form->isFrozen()) {
            // hidden values
            $this->form->addElement('hidden', 'test_name', $this->name);
            $this->form->addElement('hidden', 'subtest', $this->page);
            $this->form->addElement('hidden', 'identifier', $this->identifier);
            $this->form->addElement('hidden', 'reliability_center_id', $this->reliability_center_id);
            $this->form->addElement('submit', 'fire_away', 'Save Data', 'class=button');
        }
        
        // get the defaults
        $localDefaults = $this->_getDefaults();
        if(!is_array($localDefaults)) { $localDefaults = array(); }
        // set the quickform object defaults
        $this->form->setDefaults(array_merge($this->defaults, $localDefaults));
        
        // trim all values
        $this->form->applyFilter('__ALL__', 'trim');
        
        // display the HTML_Quickform object
        $smarty = new Smarty_neurodb;
        
        // display the HTML_Quickform object
        return $this->form->toHTML();
        
        $renderer =& new HTML_QuickForm_Renderer_Default();
        $renderer->setFormTemplate("<form{attributes}><table class=\"instrument\">{content}</table></form>");
        $renderer->setElementTemplate("<tr><td class=\"lab\"><!-- BEGIN required --><span style=\"color: #ff0000\">*</span><!-- END required -->{label}</td><td class=\"ele\"><!-- BEGIN error --><span style=\"color: #ff0000\">{error}</span><br /><!-- END error -->{element}</td></tr>");
        $renderer->setElementTemplate("<tr><td class=\"lab\"><i>{label}</i></td><td class=\"ele\">\t<i>{element}</i></td></tr>", "static");
        $renderer->setHeaderTemplate("<tr><th colspan=\"2\"><br><b>{header}</b></th></tr>");
        $this->form->accept($renderer);
     return $renderer->toHtml();
     
    } // end function display
}
?>
