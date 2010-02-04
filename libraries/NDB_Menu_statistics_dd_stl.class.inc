<?php
require_once 'NDB_Menu.class.inc';

/**
 * The welcome menu
 * @package main
 */
class NDB_Menu_statistics_dd_stl extends NDB_Menu
{
    function setup()
    {   
       $DB =& Database::singleton();
         if (PEAR::isError($DB)) {
             return PEAR::raiseError("Could not connect to database: ".$DB->getMessage());
         }
       
          $instruments = array(
              "DSMIV_checklist",                        
          //      "EARLI_interview",                        
                "ace_medical_history",                    
                "adi_r_proband",                          
                "adi_r_subject",                          
                "ados_module1",                           
                "ados_module2",                           
                "aosi",                                                            
                "csbs",                                   
                "edi",                                                                   
                "figs_year3",                             
                "figs_year3_relatives",                   
                "fyi",                                    
                "head_measurements_proband",              
                "head_measurements_subject",              
                "ibq_r",                                  
                "m_chat",                                 
            //    "macarthur_cdi",                          
                "macarthur_words_gestures",               
            //    "med_extract_new_recruit",                
                "med_psych_hist",                         
                "med_records_24",  
                "med_records_recruit",
                "med_records_proband",    
                "mri_parameter_form",                                 
                "mullen",                                                       
                "neuro_screen",                           
                "prefrontal_task",                        
                "radiology_review",                       
                "rbs_r",                                  
                "scq_proband",                            
                "scq_subject",                            
                "seq",                                                     
                "tsi",                                    
                "vineland_proband",                       
                "vineland_subject"                       

              );

         $data = array();
         $id = '4';
         $name = 'stl';
         $data[$name] = array();
            foreach($instruments as $instrument){           
               $DB->select("SELECT count(s.CandID)  FROM session as s, candidate as c, flag as f, {$instrument} as i WHERE s.ID=f.SessionID AND f.CommentID=i.CommentID AND s.CandID=c.CandID  AND s.Cancelled='N' AND s.Active='Y' AND s.CenterID={$id} AND f.Data_entry='Complete' AND f.Administration='All' AND i.CommentID LIKE 'DDE%' ORDER BY c.PSCID;", $result);
                   if (PEAR::isError($result)) {
                       return PEAR::raiseError("DB Error: ".$result->getMessage());
                   }
                   list(,$result)=each($result[0]);
                   $count = $result;


                   //adir_proband incomplete
                      $DB->select("SELECT s.CandID, f.SessionID, i.CommentID, c.PSCID  FROM session as s, candidate as c, flag as f, {$instrument} as i WHERE s.ID=f.SessionID AND f.CommentID=i.CommentID AND s.CandID=c.CandID  AND s.Cancelled='N' AND s.Active='Y' AND s.CenterID={$id} AND (f.Data_entry is NULL OR f.Data_entry<>'Complete') AND i.CommentID LIKE 'DDE%' ORDER BY c.PSCID;", $result);
                        if (PEAR::isError($result)) {
                            return PEAR::raiseError("DB Error: ".$result->getMessage());
                        }
                        $result_string = "";
                        $test_url = $instrument;
                        if(substr($test_url, 0, 10) == "figs_year3"){
                           $test_url = "figs_year3";
                        }
                        foreach($result as $row){
                          if(empty($result_string)){
                            $result_string = "(Total: " . count($result) . ")<BR>";
                          }else{
                             $result_string .= ', ';
                          }
                           $result_string .= "<a href='main.php?test_name={$test_url}&candID={$row['CandID']}&sessionID={$row['SessionID']}&commentID={$row['CommentID']}'>{$row['PSCID']}</a>";
                        }
                        $data[$name][] = array('name' => $instrument, 'count' => $count, 'incompletes' => $result_string);
                        
            }
            $this->tpl_data["{$name}_data"] = $data[$name];      
                 
    } // End function
} // End class
?>