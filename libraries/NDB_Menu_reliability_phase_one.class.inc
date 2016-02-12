<?php
require_once 'NDB_Menu.class.inc';

/**
 * The welcome menu
 * @package main
 */
class NDB_Menu_reliability_phase_one extends NDB_Menu
{
    function setup()
    {   
       $DB =& Database::singleton();
       
          $instruments = array(               
                "adi_r",                          
                "ados",                           
                "aosi",                                                            
                "csbs",                                                                                                      
                "figs",                             
              );
        
        $instrument = "adi_r";
         $data = array();
        $DB->select("SELECT * FROM {$instrument}_initial_reliability", $result);
            foreach($result as $row){          
               if(empty($row['with_umacc_reliable_clinician']))
                  $row['with_umacc_reliable_clinician'] = 'No';
               else
                  $row['with_umacc_reliable_clinician'] = 'Yes';
               $data[] = array('site' => $row['site'], 'rater' => $row['rater'], 'reliable' => $row['reliable'], 'outside_research_group' => $row['outside_research_group'],
                              'with_umacc_reliable_clinician' => $row['with_umacc_reliable_clinician'], 'reliability_established_date' => $row['reliability_established_date'],
                              'administration_status' => $row['administration_status']);
            }
            $this->tpl_data["{$instrument}_data"] = $data;      
      
             $instrument = "figs";
               $data = array();
              $DB->select("SELECT * FROM {$instrument}_initial_reliability", $result);
                  foreach($result as $row){
                     $data[] = array('site' => $row['site'], 'rater' => $row['rater'], 'reliable' => $row['reliable'],
                                    'case_ID_1' => $row['case_ID_1'], 'case_ID_2' => $row['case_ID_2'], 'case_ID_3' => $row['case_ID_3'],
                                    'tape_1_admin' => $row['date_administration_1'],
                                    'tape_1_sent'  => $row['tape_sent_date_1'],
                                    'tape_1_feedback' =>$row['feedback_date_1'],
                                    'tape_2_admin' => $row['date_administration_2'],
                                    'tape_2_sent'  => $row['tape_sent_date_2'],
                                    'tape_2_feedback' =>$row['feedback_date_2'],
                                    'tape_3_admin' => $row['date_administration_3'],
                                    'tape_3_sent'  => $row['tape_sent_date_3'],
                                    'tape_3_feedback' =>$row['feedback_date_3'],
                                     'reliability_established_date' => $row['reliability_established_date'], 
                                     'lead_clinician' => $row['lead_clinician'],
                                     'administration_status' => $row['administration_status']);
                  }
                  $this->tpl_data["{$instrument}_data"] = $data; 
                  
                    $instrument = "aosi";
                        $data = array();
                       $DB->select("SELECT * FROM {$instrument}_initial_reliability WHERE case_age_mo < 12 ORDER BY case_age_mo", $result);
                           foreach($result as $row){

                              $data[] = array('site' => $row['site'], 'rater' => $row['rater'], 'reliable' => $row['reliable'],
                                             'tape_sent_date_1' => $row['tape_sent_date_1'], 
                                             'case_age_mo' => $row['case_age_mo'], 
                                             'case_ID_1' => $row['case_ID_1'],
                                             'tape_sent_date_2' => $row['tape_sent_date_2'], 
                                             'case_ID_2' => $row['case_ID_2'], 
                                             'reliable' => $row['reliable'],
                                             'reliability_established_date' => $row['reliability_established_date'],
                                             'reliability_percentage' => $row['reliability_percentage'],
                                             'administration_status' => $row['administration_status']);
                           }
                           $this->tpl_data["{$instrument}_data_6mo"] = $data;
                           
                           
            $instrument = "aosi";
             $data = array();
             $DB->select("SELECT * FROM {$instrument}_initial_reliability WHERE case_age_mo >= 12 ORDER BY case_age_mo", $result);
                foreach($result as $row){
             
                   $data[] = array('site' => $row['site'], 'rater' => $row['rater'], 'reliable' => $row['reliable'],
                                  'tape_sent_date_1' => $row['tape_sent_date_1'], 
                                  'case_age_mo' => $row['case_age_mo'], 
                                  'case_ID_1' => $row['case_ID_1'],
                                  'tape_sent_date_2' => $row['tape_sent_date_2'], 
                                  'case_ID_2' => $row['case_ID_2'], 
                                  'reliable' => $row['reliable'],
                                  'reliability_established_date' => $row['reliability_established_date'],
                                  'reliability_percentage' => $row['reliability_percentage'],
                                  'administration_status' => $row['administration_status']);
                }
                $this->tpl_data["{$instrument}_data_12mo"] = $data;
                           
                           
                           $instrument = "csbs";
                          $data = array();
                         $DB->select("SELECT * FROM {$instrument}_initial_reliability WHERE type = 'training kit'", $result);
                             foreach($result as $row){
                         
                                $data[] = array('site' => $row['site'], 'rater' => $row['rater'], 'reliable' => $row['reliable'],
                                               'type' => $row['type'], 'reliability_established_date' => $row['reliability_established_date'],
                                               'reliability_percentage' => $row['reliability_percentage'], 'examiner_coder_status' => $row['examiner_coder_status'],
                                               'administration_status' => $row['administration_status']);
                             }
                             $this->tpl_data["{$instrument}_data_tk"] = $data;
                             
                               $instrument = "csbs";
                               $data = array();
                              $DB->select("SELECT * FROM {$instrument}_initial_reliability WHERE type = 'UW Gold Standard'", $result);
                                  foreach($result as $row){

                                     $data[] = array('site' => $row['site'], 'rater' => $row['rater'], 'reliable' => $row['reliable'],
                                                    'type' => $row['type'], 'reliability_established_date' => $row['reliability_established_date'],
                                                    'reliability_percentage' => $row['reliability_percentage'], 'examiner_coder_status' => $row['examiner_coder_status'],
                                                    'administration_status' => $row['administration_status']);
                                  }
                                  $this->tpl_data["{$instrument}_data_gold"] = $data;
                  
                            $instrument = "ados";
                              $data = array();
                             $DB->select("SELECT * FROM {$instrument}_initial_reliability", $result);
                                 foreach($result as $row){

                                    if(empty($row['with_umacc_reliable_clinician']))
                                       $row['with_umacc_reliable_clinician'] = 'No';
                                    else
                                       $row['with_umacc_reliable_clinician'] = 'Yes';
                                    $data[] = array('site' => $row['site'], 'rater' => $row['rater'], 'reliable' => $row['reliable'],
                                                   'with_umacc_reliable_clinician' => $row['with_umacc_reliable_clinician'], 'reliability_established_date' => $row['reliability_established_date'],
                                                   'administration_status' => $row['administration_status']);
                                 }
                                 $this->tpl_data["{$instrument}_data"] = $data;
                           
                                  $instrument = "mullen";
                                    $data = array();
                                   $DB->select("SELECT * FROM {$instrument}_initial_reliability", $result);
                                       foreach($result as $row){
                                          if(empty($row['with_umacc_reliable_clinician']))
                                             $row['with_umacc_reliable_clinician'] = 'No';
                                          else
                                             $row['with_umacc_reliable_clinician'] = 'Yes';
                                          $data[] = array('site' => $row['site'], 'rater' => $row['rater'], 'reliable' => $row['reliable'], 'lead_clinician' => $row['lead_clinician'], 
                                          'reliability_established_date' => $row['reliability_established_date'],
                                            'administration_status' => $row['administration_status']);
                                       }
                                       $this->tpl_data["{$instrument}_data"] = $data;
    } // End function
} // End class
?>