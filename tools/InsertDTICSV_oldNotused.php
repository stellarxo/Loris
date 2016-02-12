<?php
set_include_path(get_include_path().":../libraries:../../php/libraries:");
require_once "NDB_Client.class.inc";
require_once "Utility.class.inc";
require_once "Database.class.inc";
require_once "FeedbackMRI.class.inc";

//require_once "../../tools/generic_includes.php";
$client = new NDB_Client();
$client->makeCommandLine();
$client->initialize('../config.xml');

$DB =& Database::singleton();
if(Utility::isErrorX($DB)) {
    return PEAR::raiseError("Could not connect to database: ".$DB->getMessage());
}

//$file = "QCResults.csv";
$file = "QC_RESULTS_DTI_FEB2015.csv";
$fp = fopen($file, "r");
$headers = fgetcsv($fp);
$headers = array_slice($headers, 3, 36);

$InsertTypes = array(
    0  => GetParameterTypeID("Color_artifact"),
    1  => GetPredefinedCommentID("red artifact"),
    2  => GetPredefinedCommentID("green artifact"),
    3  => GetPredefinedCommentID("blue artifact"),
    4  => GetParameterTypeID("Entropy"),
    5  => GetCommentIDType("Dominant Direction Artifact (DWI ONLY)"),
    6  => GetParameterTypeID("Movement_artifacts_within_scan"),
    7  => GetPredefinedCommentID("slice wise artifact (DWI ONLY)"),
    8  => GetPredefinedCommentID("gradient wise artifact (DWI ONLY)"),
    9  => GetCommentIDType("Movement artifact"),
    10 => GetParameterTypeID("Intensity"),
    11 => GetPredefinedCommentID("noisy scan"),
    12 => GetPredefinedCommentID("checkerboard artifact"),
    13 => GetPredefinedCommentID("horizontal intensity striping (Venetian blind effect, DWI ONLY)"),
    14 => GetPredefinedCommentID("diagonal striping (NRRD artifact, DWI ONLY)"),
    15 => GetPredefinedCommentID("high intensity in direction of acquisition"),
    16 => GetPredefinedCommentID("signal loss (dark patches)"),
    17 => GetPredefinedCommentID("susceptibility artifact due to anatomy"),
    18 => GetCommentIDType("Intensity"),
    19 => GetPredefinedCommentID("Too few remaining gradients (DWI ONLY)"),
    20 => GetPredefinedCommentID("No b0 remaining after DWIPrep (DWI ONLY)"),
    21 => GetPredefinedCommentID("No gradient information available from scanner (DWI ONLY)"),
    22 => GetPredefinedCommentID("Incorrect diffusion direction (DWI ONLY)"),
    23 => GetPredefinedCommentID("Duplicate series"),
    24 => GetCommentIDType("Coverage"),
    25 => GetPredefinedCommentID("Large AP wrap around, affecting brain"),
    26 => GetPredefinedCommentID("Medium AP wrap around, no affect on brain"),
    27 => GetPredefinedCommentID("Small AP wrap around, no affect on brain"),
    28 => GetPredefinedCommentID("Too tight LR, affecting brain"),
    29 => GetPredefinedCommentID("Base of cerebellum cut off"),
    30 => GetPredefinedCommentID("Top of brain cut off"),
    31 => /* QC_Status */ '',
    32 => /* Caveat */ '',
    33 => /* Pending, ignored */ '',
    34 => GetParameterTypeID("Selected"),
    35 => GetCommentIDType("Overall"),
);
function GetPredefinedCommentID($name) {
   $DB = Database::singleton();
    if(Utility::isErrorX($DB)) {
        return PEAR::raiseError("Could not connect to database: ".$DB->getMessage());
    }

    $commentID = $DB->pselectOne("SELECT PredefinedCommentID FROM feedback_mri_predefined_comments
                                 WHERE Comment=:Name", array('Name'=>$name));
   if(Utility::isErrorX($commentID)) {
        return PEAR::raiseError("Cannot find CommentTypeID: ".$commentID->getMessage());
    }
    return $commentID;

}
function GetCommentIDType($name) {
    $DB = Database::singleton();
    if(Utility::isErrorX($DB)) {
        return PEAR::raiseError("Could not connect to database: ".$DB->getMessage());
    }

    $commentID = $DB->pselectOne("SELECT CommentTypeID FROM feedback_mri_comment_types
                            WHERE CommentName=:Name", array('Name'=>$name));
    if(Utility::isErrorX($commentID)) {
        return PEAR::raiseError("Cannot find CommentTypeID: ".$commentID->getMessage());
    }
    return $commentID;

}
function GetParameterTypeID($name) {
    $DB = Database::singleton();
    if(Utility::isErrorX($DB)) {
        return PEAR::raiseError("Could not connect to database: ".$DB->getMessage());
    }

   $parameterTypeID = $DB->pselectOne("SELECT ParameterTypeID FROM parameter_type
                                       WHERE Name=:param",
                                       array('param'=>$name));
   return $parameterTypeID;

}
function InsertDropdown($typeID, $value, $fileID) {
    $DB = Database::singleton();
    if(Utility::isErrorX($DB)) {
        return PEAR::raiseError("Could not connect to database: ".$DB->getMessage());
    }
    $name='';
    if(!empty($typeID) ) {
    $name = $DB->pselectOne("SELECT Name from parameter_type Where ParameterTypeID=:pid",
                             array('pid'=>$typeID));
    }
    $options = array();
    if($name === 'Entropy') {
        $options = array('Acceptable', 'Suspicious', 'Unacceptable', 'Not_available');
    } elseif($name === 'Movement_artifacts_within_scan') {
        $options = array('None', 'Slight', 'Poor', 'Unacceptable');
    } else {
        $options = array('Fair', 'Good', 'Poor', 'Unacceptable');
    }
    if($value === '' || $value === 'NULL') {
        return;
    }
    if(in_array($value, $options)) {
        //insert
        if(!empty($fileID)) {
            $FileCount = $DB->pselectOne(
                    "SELECT COUNT(*) FROM parameter_file WHERE FileID=:fid AND ParameterTypeID=:pid",
                    array("fid"=>$fileID, "pid"=>$typeID)
                    );
            if ($FileCount > 0) {
                $success = $DB->update(
                        "parameter_file",
                        array('Value'=>$value),
                        array('FileID'=>$fileID, 'ParameterTypeID'=>$typeID)
                        );
            } else {
                //insert it
                $success = $DB->insert('parameter_file', array('Value'=>$value,
                                       'ParameterTypeID'=>$typeID,'FileID'=>$fileID)
                        );
            }

            if (Utility::isErrorX($success)) {
                return PEAR::raiseError(
                        "Could not update file qc status: ".$success->getMessage()
                        );
            }

        }

        return;
    }
   // print "\t$typeID: $value\n";
}
function InsertCheckbox($typeID, $value, $comments) {
   $DB = Database::singleton();
    if(Utility::isErrorX($DB)) {
        return PEAR::raiseError("Could not connect to database: ".$DB->getMessage());
    }
    if($value === 'No'
        || $value === ''
        || $value === 'NULL'
    ) {
        return;
    }
    if($value === 'Yes') {
        //insert
        $success = $DB->delete("feedback_mri_comments",array('PredefinedCommentID'=>$typeID,
                          'FileID'=>$comments->fileID));
        $comments->setPredefinedComments(array($typeID));

        return;
    }
   // print "\t$typeID: $value\n";
 //clear predefined comments
   }

function InsertComment($type, $value, $comments) {

   $comments->addTextComment($value, $type);
   // print "\t$type: $value\n";
}
function InsertQCStatus($fileID, $value) {
    $DB = Database::singleton();
    if(Utility::isErrorX($DB)) {
        return PEAR::raiseError("Could not connect to database: ".$DB->getMessage());
    }
    if(!empty($fileID)) {
       $FileCount = $DB->pselectOne(
                   "SELECT COUNT(*) FROM files_qcstatus WHERE FileID = :fid",
                   array("fid"=>$fileID)
                   );
           if ($FileCount > 0) {
               $success = $DB->update(
                       "files_qcstatus",
                       array('QCStatus'=>$value),
                       array('FileID'=>$fileID)
                       );
           } else {
               //insert it
               $success = $DB->insert('files_qcstatus', array('QCStatus'=>$value,
                                                              'FileID'=>$fileID)
                                      );
           }

           if (Utility::isErrorX($success)) {
               return PEAR::raiseError(
                       "Could not update file qc status: ".$success->getMessage()
                       );
           }

    }
}
function InsertQCInfo($fileID, $typeID, $value) {
    $DB = Database::singleton();
    if (Utility::isErrorX($DB)) {
        return PEAR::raiseError("Could not connect to database: ".$DB->getMessage());
    }
   if (strtoupper($value) === 'TRUE' && !empty($fileID)) {
        $FileCount = $DB->pselectOne("SELECT COUNT(*) FROM parameter_file WHERE FileID = :fid AND ParameterTypeID = :pid",
            array("fid"=>$fileID, 'pid' => $typeID)
                   );
           if ($FileCount > 0) {
               $success = $DB->update(
                       "parameter_file",
                       array('Value'=>'dti'),
                       array('FileID'=>$fileID, 'ParameterTypeID' => $typeID)
                       );
           } else {
               //insert it
              $success = $DB->insert('parameter_file', array('FileID'=>$fileID,
                                                      'Value'=>'dti',
                                                      'ParameterTypeID'=>$typeID));

           }
           if (Utility::isErrorX($success)) {
               return PEAR::raiseError(
                       "Could not update file qc status: ".$success->getMessage()
                       );
           }

          }
}
function UpdateCaveat($fileID, $value) {
    $DB = Database::singleton();
    if(Utility::isErrorX($DB)) {
        return PEAR::raiseError("Could not connect to database: ".$DB->getMessage());
    }
    if (!empty($fileID)) {
       if ($value === 'TRUE') {
           $DB->update('files', array('Caveat'=>1), array('FileID'=>$fileID));
        } else if ($value == 'FALSE') {
           $DB->update('files', array('Caveat'=>0), array('FileID'=>$fileID));
        }
    }
}
while($csv_line = fgetcsv($fp))
{
    $DCCID = $csv_line[0];
    $VL    = $csv_line[1];
    $Filename = $csv_line[2] . "_DTIPrepReg_001.mnc";
    $results = array_slice($csv_line, 3, 36);
   // print "File: $Filename\n";
    $file_info = $DB->pselectRow("SELECT FileID, SessionID FROM files WHERE
                             File LIKE '%$Filename'", array());
    if (empty($file_info['FileID'])) {
       print "FILE NOT FOUND - $Filename \n";
    }
   // instantiate feedback mri object
    if (!empty($file_info)) {
        $comments = new FeedbackMRI($file_info['FileID'], $file_info['SessionID']);
    }
    foreach($results as $i => $value) {
        switch($i) {
        case 0:
        case 4:
        case 6:
        case 10:
            InsertDropdown($InsertTypes[$i], $results[$i],$file_info['FileID']);
            break;
        case 1:
        case 2:
        case 3:
        case 7:
        case 8:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
        case 25:
        case 26:
        case 27:
        case 28:
        case 29:
        case 30:
            InsertCheckbox($InsertTypes[$i], $results[$i], $comments);
            break;
        case 5:
        case 9:
        case 18:
        case 24:
        case 35:
            InsertComment($InsertTypes[$i], $results[$i], $comments);
            break;
        case 31: /* QC related types */
            InsertQCStatus($file_info['FileID'], $results[$i]);
            break;
        case 32:
            UpdateCaveat($file_info['FileID'],$results[$i]);
            break;
        case 34:
            InsertQCInfo($file_info['FileID'],$InsertTypes[$i], $results[$i]);
            break;
        case 33:
            break;
        default:
            print "Unhandled type: $i\n";
        }
    }
}

?>
