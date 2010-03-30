<?php
require_once 'NDB_Menu.class.inc';

/**
 * The welcome menu
 * @package main
 */
class NDB_Menu_statistics extends NDB_Menu
{
    function setup()
    {
        $DB =& Database::singleton();
        if (PEAR::isError($DB)) {
            return PEAR::raiseError("Could not connect to database: ".$DB->getMessage());
        }

        // 6 MONTH RECRUITS
        // Query: Number of 6 months registered in the database (6 month recruits)
        $DB->select("SELECT count(s.CandID) from session as s, candidate as c WHERE s.CandID=c.CandID AND s.Cancelled='N' AND s.SubprojectID=1 AND (s.Visit_label='v06' OR s.Visit_label='6mo') AND s.Active='Y' AND s.CenterID<>'1' ORDER BY c.PSCID;", $result1);
        if (PEAR::isError($result1)) {
            return PEAR::raiseError("DB Error: ".$result1->getMessage());
        }
        list(,$result1)=each($result1[0]);
        $SixMonthRecruit_SixMonthVisit = $result1;
        $this->tpl_data['SixMonthRecruit_SixMonthVisit'] = $SixMonthRecruit_SixMonthVisit;

        // Query: Number of 6 month recruits that are not failed/withdrawn
        $DB->select("SELECT count(s.CandID) from session as s, candidate as c WHERE s.CandID=c.CandID AND s.Cancelled='N' AND (s.Current_stage='Visit' OR s.Current_stage='Screening') AND s.SubprojectID=1 AND (s.Visit_label='v06' OR s.Visit_label='6mo') AND s.Active='Y' AND s.CenterID<>'1' ORDER BY c.PSCID;", $result2);
        if (PEAR::isError($result2)) {
            return PEAR::raiseError("DB Error: ".$result2->getMessage());
        }
        list(,$result2)=each($result2[0]);
        $count2 = $result2;
        $this->tpl_data['count2'] = $count2;
       
        // Query: Number of 12 months registered in the database (6 month recruits)
        $DB->select("SELECT count(s.CandID) from session as s, candidate as c WHERE s.CandID=c.CandID AND s.Cancelled='N' AND s.SubprojectID=1 AND (s.Visit_label='v12' OR s.Visit_label='12m') AND s.Active='Y' AND s.CenterID<>'1' ORDER BY c.PSCID;", $result3);
        if (PEAR::isError($result3)) {
            return PEAR::raiseError("DB Error: ".$result3->getMessage());
        }
        list(,$result3)=each($result3[0]);
        $count3 = $result3;
        $this->tpl_data['count3'] = $count3;

        // Query: Number of 6 month recruits for which the 12 month timepoint has not been failed/withdrawn
        $DB->select("SELECT count(s.CandID) from session as s, candidate as c WHERE s.CandID=c.CandID AND s.Cancelled='N' AND (s.Current_stage='Visit' OR s.Current_stage='Screening') AND s.SubprojectID=1 AND (s.Visit_label='v12' OR s.Visit_label='12m') AND s.Active='Y' AND s.CenterID<>'1' ORDER BY c.PSCID;", $result4);
        if (PEAR::isError($result4)) {
            return PEAR::raiseError("DB Error: ".$result4->getMessage());
        }
        list(,$result4)=each($result4[0]);
        $count4 = $result4;
        $this->tpl_data['count4'] = $count4;

        // 12 MONTH RECRUITS
     
        // Query: Number of 6 months registered in the database (12 month recruits)
        $DB->select("SELECT count(s.CandID) from session as s, candidate as c WHERE s.CandID=c.CandID AND s.Cancelled='N' AND s.SubprojectID=2 AND (s.Visit_label='v06' OR s.Visit_label='6mo') AND s.Active='Y' AND s.CenterID<>'1' ORDER BY c.PSCID;", $result17);
        if (PEAR::isError($result17)) {
            return PEAR::raiseError("DB Error: ".$result17->getMessage());
        }
        list(,$result17)=each($result17[0]);
        $count17 = $result17;
        $this->tpl_data['count17'] = $count17;

        // Query: Number of 12 months registered in the database (12 month recruits)
        $DB->select("SELECT count(s.CandID) from session as s, candidate as c WHERE s.CandID=c.CandID AND s.Cancelled='N' AND s.SubprojectID=2 AND (s.Visit_label='v12' OR s.Visit_label='12m') AND s.Active='Y' AND s.CenterID<>'1' ORDER BY c.PSCID;", $result5);
        if (PEAR::isError($result5)) {
            return PEAR::raiseError("DB Error: ".$result5->getMessage());
        }
        list(,$result5)=each($result5[0]);
        $count5 = $result5;
        $this->tpl_data['count5'] = $count5;
	
        // Query: Number of 12 month recruits for which the 6 month timepoint has not been failed/withdrawn
        $DB->select("SELECT count(s.CandID) from session as s, candidate as c WHERE s.CandID=c.CandID AND s.Cancelled='N' AND (s.Current_stage='Visit' OR s.Current_stage='Screening') AND s.SubprojectID=2 AND (s.Visit_label='v06' OR s.Visit_label='6mo') AND s.Active='Y' AND s.CenterID<>'1' ORDER BY c.PSCID;", $result6);
        if (PEAR::isError($result6)) {
            return PEAR::raiseError("DB Error: ".$result6->getMessage());
        }
        list(,$result6)=each($result6[0]);
        $count6 = $result6;
        $this->tpl_data['count6'] = $count6;

       // Query: Number of 12 month recruits for which the 12 month timepoint has not been failed/withdrawn
        $DB->select("SELECT count(s.CandID) from session as s, candidate as c WHERE s.CandID=c.CandID AND s.Cancelled='N' AND (s.Current_stage='Visit' OR s.Current_stage='Screening') AND s.SubprojectID=2 AND (s.Visit_label='v12' OR s.Visit_label='12m') AND s.Active='Y' AND s.CenterID<>'1' ORDER BY c.PSCID;", $result14);
        if (PEAR::isError($result14)) {
            return PEAR::raiseError("DB Error: ".$result14->getMessage());
        }
        list(,$result14)=each($result14[0]);
        $count14 = $result14;
        $this->tpl_data['count14'] = $count14;

        // CONTROLS
        // Query: Number of 6 months registered in the database (Controls)
        $DB->select("SELECT count(s.CandID) from session as s, candidate as c WHERE s.CandID=c.CandID AND s.Cancelled='N' AND s.SubprojectID=3 AND (s.Visit_label='v06' OR s.Visit_label='6mo') AND s.Active='Y' AND s.CenterID<>'1' ORDER BY c.PSCID;", $result7);
        if (PEAR::isError($result7)) {
            return PEAR::raiseError("DB Error: ".$result7->getMessage());
        }
        list(,$result7)=each($result7[0]);
        $count7 = $result7;
        $this->tpl_data['count7'] = $count7;

        // Query: Number of 12 months registered in the database (Controls)
        $DB->select("SELECT count(s.CandID) from session as s, candidate as c WHERE s.CandID=c.CandID AND s.Cancelled='N' AND s.SubprojectID=3 AND (s.Visit_label='v12' OR s.Visit_label='12m') AND s.Active='Y' AND s.CenterID<>'1' ORDER BY c.PSCID;", $result13);
        if (PEAR::isError($result13)) {
            return PEAR::raiseError("DB Error: ".$result13->getMessage());
        }
        list(,$result13)=each($result13[0]);
        $count13 = $result13;
        $this->tpl_data['count13'] = $count13;

        // Query: Number of Controls for which the 6 month timepoint has been not been failed/withdrawn
        $DB->select("SELECT count(s.CandID) from session as s, candidate as c WHERE s.CandID=c.CandID AND s.Cancelled='N' AND (s.Current_stage='Visit' OR s.Current_stage='Screening') AND s.SubprojectID=3 AND (s.Visit_label='v06' OR s.Visit_label='6mo') AND s.Active='Y' AND s.CenterID<>'1' ORDER BY c.PSCID;", $result8);
        if (PEAR::isError($result8)) {
            return PEAR::raiseError("DB Error: ".$result8->getMessage());
        }
        list(,$result8)=each($result8[0]);
        $count8 = $result8;
        $this->tpl_data['count8'] = $count8;

        // Query: Number of Controls for which the 12 month timepoint has been not been failed/withdrawn
        $DB->select("SELECT count(s.CandID) from session as s, candidate as c WHERE s.CandID=c.CandID AND s.Cancelled='N' AND (s.Current_stage='Visit' OR s.Current_stage='Screening') AND s.SubprojectID=3 AND (s.Visit_label='v12' OR s.Visit_label='12m') AND s.Active='Y' AND s.CenterID<>'1' ORDER BY c.PSCID;", $result18);
        if (PEAR::isError($result18)) {
            return PEAR::raiseError("DB Error: ".$result18->getMessage());
        }
        list(,$result18)=each($result18[0]);
        $count18 = $result18;
        $this->tpl_data['count18'] = $count18;

        // Query: Number of controls for which 6 month time point is in the Approval stage
        $DB->select("SELECT count(s.CandID) from session as s, candidate as c WHERE s.CandID=c.CandID AND s.Cancelled='N' AND (s.Current_stage='Approval') AND s.SubprojectID=3 AND (s.Visit_label='v06' OR s.Visit_label='6mo') AND s.Active='Y' AND s.CenterID<>'1' ORDER BY c.PSCID;", $result15);
        if (PEAR::isError($result15)) {
            return PEAR::raiseError("DB Error: ".$result15->getMessage());
        }
        list(,$result15)=each($result15[0]);
        $count15 = $result15;
        $this->tpl_data['count15'] = $count15;

        // Query: Number of controls for which 12 month time point is in the Approval stage
        $DB->select("SELECT count(s.CandID) from session as s, candidate as c WHERE s.CandID=c.CandID AND s.Cancelled='N' AND (s.Current_stage='Approval') AND s.SubprojectID=3 AND (s.Visit_label='v12' OR s.Visit_label='12m') AND s.Active='Y' AND s.CenterID<>'1' ORDER BY c.PSCID;", $result16);
        if (PEAR::isError($result16)) {
            return PEAR::raiseError("DB Error: ".$result16->getMessage());
        }
        list(,$result16)=each($result16[0]);
        $count16 = $result16;
        $this->tpl_data['count16'] = $count16;
                
	// APPROVAL
   	// Query: Number of 6 month recruits for which the 6 month timepoint is in the Approval stage
        $DB->select("SELECT count(s.CandID) from session as s, candidate as c WHERE s.CandID=c.CandID AND s.Cancelled='N' AND (s.Current_stage='Approval') AND s.SubprojectID=1 AND (s.Visit_label='v06' OR s.Visit_label='6mo') AND s.Active='Y' AND s.CenterID<>'1' ORDER BY c.PSCID;", $result9);
        if (PEAR::isError($result9)) {
            return PEAR::raiseError("DB Error: ".$result9->getMessage());
        }
        list(,$result9)=each($result9[0]);
        $count9 = $result9;
        $this->tpl_data['count9'] = $count9;

	// Query: Number of 6 month recruits for which the 12 month timepoint is in the Approval stage
        $DB->select("SELECT count(s.CandID) from session as s, candidate as c WHERE s.CandID=c.CandID AND s.Cancelled='N' AND (s.Current_stage='Approval') AND s.SubprojectID=1 AND (s.Visit_label='v12' OR s.Visit_label='12m') AND s.Active='Y' AND s.CenterID<>'1' ORDER BY c.PSCID;", $result10);
        if (PEAR::isError($result10)) {
            return PEAR::raiseError("DB Error: ".$result10->getMessage());
        }
        list(,$result10)=each($result10[0]);
        $count10 = $result10;
        $this->tpl_data['count10'] = $count10;

	// Query: Number of 12 month recruits for which the 6 month timepoint is in the Approval stage
        $DB->select("SELECT count(s.CandID) from session as s, candidate as c WHERE s.CandID=c.CandID AND s.Cancelled='N' AND (s.Current_stage='Approval') AND s.SubprojectID=2 AND (s.Visit_label='v06' OR s.Visit_label='6mo') AND s.Active='Y' AND s.CenterID<>'1' ORDER BY c.PSCID;", $result11);
        if (PEAR::isError($result11)) {
            return PEAR::raiseError("DB Error: ".$result11->getMessage());
        }
        list(,$result11)=each($result11[0]);
        $count11 = $result11;
        $this->tpl_data['count11'] = $count11;

	// Query: Number of 12 month recruits for which the 12 month timepoint is in the Approval stage
        $DB->select("SELECT count(s.CandID) from session as s, candidate as c WHERE s.CandID=c.CandID AND s.Cancelled='N' AND (s.Current_stage='Approval') AND s.SubprojectID=2 AND (s.Visit_label='v12' OR s.Visit_label='12m') AND s.Active='Y' AND s.CenterID<>'1' ORDER BY c.PSCID;", $result12);
        if (PEAR::isError($result12)) {
            return PEAR::raiseError("DB Error: ".$result12->getMessage());
        }
        list(,$result12)=each($result12[0]);
        $count12 = $result12;
        $this->tpl_data['count12'] = $count12;


	//---- BEHAVIORAL STATS -----
        $sites = array('2' => 'sea', '3' => 'phi', '4' => 'stl', '5' => 'unc');
        $visit_labels = array('all', 'v06', 'v12', 'v18', 'v24', 'v36');
          $mri_data = array();
          $completion_data = array();
          foreach($sites as $id=>$name){
            foreach($visit_labels as $vl){
              if($vl == 'all'){
                $vl_query = "";
              }else{
                $vl_query = " AND s.visit_label='{$vl}' ";
              }
            $DB->select("SELECT count(s.CandID)  FROM session as s, candidate as c, flag as f WHERE s.ID=f.SessionID AND s.CandID=c.CandID AND s.Cancelled='N' AND s.Active='Y' AND s.CenterID={$id} AND f.Data_entry='Complete' AND f.CommentID NOT LIKE 'DDE%' {$vl_query} ORDER BY c.PSCID;", $result20);
              if (PEAR::isError($result20)) {
                  return PEAR::raiseError("DB Error: ".$result20->getMessage());
              }
              list(,$result20)=each($result20[0]);
              $bvl_completed = $result20;
              
              $DB->select("SELECT count(s.CandID)  FROM session as s, candidate as c, flag as f WHERE s.ID=f.SessionID AND s.CandID=c.CandID AND s.Cancelled='N' AND s.Active='Y' AND s.CenterID={$id} AND f.CommentID NOT LIKE 'DDE%'  {$vl_query} ORDER BY c.PSCID;", $result21);
                if (PEAR::isError($result21)) {
                    return PEAR::raiseError("DB Error: ".$result21->getMessage());
                }
                list(,$result21)=each($result21[0]);
                $bvl_total = $result21;

	    $DB->select("SELECT count(s.CandID)  FROM session as s, candidate as c WHERE s.CandID=c.CandID AND s.Cancelled='N' AND s.Active='Y' AND s.CenterID={$id} {$vl_query} ORDER BY c.PSCID;", $result22);
                if (PEAR::isError($result22)) {
                    return PEAR::raiseError("DB Error: ".$result22->getMessage());
                }
                list(,$result22)=each($result22[0]);
                $timepoint_completed = $result22;

                $this->tpl_data["{$vl}_{$name}_site"] = strtoupper($name);
	              $this->tpl_data["{$vl}_{$name}_timepoint"] = $timepoint_completed;
        	      $this->tpl_data["{$vl}_{$name}_completed"] = $bvl_completed;
                $this->tpl_data["{$vl}_{$name}_total"] = $bvl_total;
                if($bvl_total == 0)
                  $bvl_total = 1;
                $this->tpl_data["{$vl}_{$name}_percent"] = floor(($bvl_completed / $bvl_total) * 100);
                
                $DB->select("SELECT count(s.CandID)  FROM session as s, candidate as c, flag as f WHERE s.ID=f.SessionID AND s.CandID=c.CandID AND s.Cancelled='N' AND s.Active='Y' AND s.CenterID={$id} AND f.Data_entry='Complete' AND f.CommentID LIKE 'DDE%' AND (f.Test_name NOT LIKE '%parameter%' AND f.Test_name NOT LIKE '%radiological%' AND f.Test_name NOT LIKE '%vineland%')  {$vl_query} ORDER BY c.PSCID;", $result20);
                  if (PEAR::isError($result20)) {
                      return PEAR::raiseError("DB Error: ".$result20->getMessage());
                  }
                  list(,$result20)=each($result20[0]);
                  $dde_completed = $result20;

                  $DB->select("SELECT count(s.CandID)  FROM session as s, candidate as c, flag as f WHERE s.ID=f.SessionID AND s.CandID=c.CandID AND s.Cancelled='N' AND s.Active='Y' AND s.CenterID={$id} AND f.CommentID LIKE 'DDE%' AND (f.Test_name NOT LIKE '%parameter%' AND f.Test_name NOT LIKE '%radiological%' AND f.Test_name NOT LIKE '%vineland%') {$vl_query}  ORDER BY c.PSCID;", $result21);
                    if (PEAR::isError($result21)) {
                        return PEAR::raiseError("DB Error: ".$result21->getMessage());
                    }
                    list(,$result21)=each($result21[0]);
                    $dde_total = $result21;
                    
                    $this->tpl_data["{$vl}_{$name}_dde_completed"] = $dde_completed;
                    $this->tpl_data["{$vl}_{$name}_dde_total"] = $dde_total;
                    
                    if($dde_total == 0)
                      $dde_total = 1;
                    $this->tpl_data["{$vl}_{$name}_dde_percent"] = floor(($dde_completed / $dde_total) * 100);
            }
	// -------- MRI STATS---------------
            $DB->select("SELECT COUNT(distinct s.CandID, s.Visit_label) FROM tarchive as t, session as s WHERE MID(t.PatientName,9,6)=s.CandID AND s.CenterID={$id};", $result23);
              if (PEAR::isError($result23)) {
                  return PEAR::raiseError("DB Error: ".$result23->getMessage());
              }
              list(,$result23)=each($result23[0]);
              $work_station_count = $result23;
              
              $DB->select("SELECT COUNT(s.CandID) FROM session as s, psc as p, candidate as c WHERE c.CandID=s.CandID AND s.Active='Y' AND s.Cancelled='N' AND s.CenterID=p.CenterID  AND s.Scan_done='Y' AND s.CenterID={$id} ORDER BY s.CandID;", $result24);
                if (PEAR::isError($result24)) {
                    return PEAR::raiseError("DB Error: ".$result24->getMessage());
                }
                list(,$result24)=each($result24[0]);
                $claimed_count = $result24;
                
                $DB->select("SELECT COUNT(s.CandID) FROM mri_parameter_form as pf, session as s, flag as f, psc as p, candidate as c WHERE f.CommentID=pf.CommentID AND s.ID=f.SessionID AND c.CandID=s.CandID AND s.Active='Y' AND s.Cancelled='N' AND s.CenterID=p.CenterID AND pf.Data_entry_completion_status='Complete' AND s.CenterID={$id} ORDER BY p.Name;", $result25);
                  if (PEAR::isError($result25)) {
                      return PEAR::raiseError("DB Error: ".$result25->getMessage());
                  }
                  list(,$result25)=each($result25[0]);
                  $forms_count = $result25;
              
              $mri_data[] = array('name' => strtoupper($name),  'work_station_count' => $work_station_count, 'claimed_count' => $claimed_count, 'forms_count' => $forms_count);
              
        }
          $this->tpl_data['mri_data'] = $mri_data;
    } // End function
} // End class
?>