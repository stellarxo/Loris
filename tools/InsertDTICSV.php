<?php
set_include_path(get_include_path().":../libraries:../../php/libraries:");

require_once '../../vendor/autoload.php';
require_once "NDB_Client.class.inc";
require_once "Utility.class.inc";
require_once "Database.class.inc";
require_once "FeedbackMRI.class.inc";

//require_once "../../tools/generic_includes.php";
$client = new NDB_Client();
$client->makeCommandLine();
$client->initialize('../config.xml');

$DB =& Database::singleton();

$file    = $argv[1];
$fp      = fopen($file, "r");
$headers = fgetcsv($fp);
$headers = array_slice($headers, 3, 36);

$InsertTypes = array(
    0  => getParameterTypeID("Color_artifact"),
    1  => getPredefinedCommentID("red artifact"),
    2  => getPredefinedCommentID("green artifact"),
    3  => getPredefinedCommentID("blue artifact"),
    4  => getParameterTypeID("Entropy"),
    5  => getCommentIDType("Dominant Direction Artifact (DWI ONLY)"),
    6  => getParameterTypeID("Movement_artifacts_within_scan"),
    7  => getPredefinedCommentID("slice wise artifact (DWI ONLY)"),
    8  => getPredefinedCommentID("gradient wise artifact (DWI ONLY)"),
    9  => getCommentIDType("Movement artifact"),
    10 => getParameterTypeID("Intensity"),
    11 => getPredefinedCommentID("noisy scan"),
    12 => getPredefinedCommentID("checkerboard artifact"),
    13 => getPredefinedCommentID(
        "horizontal intensity striping "
        . "(Venetian blind effect, DWI ONLY)"
    ),
    14 => getPredefinedCommentID("diagonal striping (NRRD artifact, DWI ONLY)"),
    15 => getPredefinedCommentID("high intensity in direction of acquisition"),
    16 => getPredefinedCommentID("signal loss (dark patches)"),
    17 => getPredefinedCommentID("susceptibility artifact due to anatomy"),
    18 => getCommentIDType("Intensity"),
    19 => getPredefinedCommentID("Too few remaining gradients (DWI ONLY)"),
    20 => getPredefinedCommentID("No b0 remaining after DWIPrep (DWI ONLY)"),
    21 => getPredefinedCommentID(
        "No gradient information available from scanner "
        . "(DWI ONLY)"
    ),
    22 => getPredefinedCommentID("Incorrect diffusion direction (DWI ONLY)"),
    23 => getPredefinedCommentID("Duplicate series"),
    24 => getCommentIDType("Coverage"),
    25 => getPredefinedCommentID("Large AP wrap around, affecting brain"),
    26 => getPredefinedCommentID("Medium AP wrap around, no affect on brain"),
    27 => getPredefinedCommentID("Small AP wrap around, no affect on brain"),
    28 => getPredefinedCommentID("Too tight LR, affecting brain"),
    29 => getPredefinedCommentID("Base of cerebellum cut off"),
    30 => getPredefinedCommentID("Top of brain cut off"),
    31 => /* QC_Status */ '',
    32 => /* Caveat */ '',
    33 => /* Pending, ignored */ '',
    34 => getParameterTypeID("Selected"),
    35 => getCommentIDType("Overall"),
    36 => getCommentIDType("Overall"),
);

function getPredefinedCommentID($name) 
{
    $DB = Database::singleton();

    $commentID = $DB->pselectOne(
        "SELECT PredefinedCommentID FROM 
        feedback_mri_predefined_comments
        WHERE Comment=:Name", array('Name'=>$name)
    );
    return $commentID;

}

function getCommentIDType($name) 
{
    $DB = Database::singleton();

    $commentID = $DB->pselectOne(
        "SELECT CommentTypeID FROM 
        feedback_mri_comment_types
        WHERE CommentName=:Name", array('Name'=>$name)
    );
    return $commentID;

}

function getParameterTypeID($name) 
{
    $DB = Database::singleton();

    $parameterTypeID = $DB->pselectOne(
        "SELECT ParameterTypeID FROM parameter_type
                                       WHERE Name=:param",
        array('param'=>$name)
    );
    return $parameterTypeID;

}

/*
 * Deletes and re-inserts
 * 
 */
function InsertDropdown($typeID, $value, $fileID) 
{
    $DB = Database::singleton();
    $name='';
    
    if (!empty($typeID) ) {
        $name = $DB->pselectOne(
            "SELECT Name from parameter_type "
            . "Where ParameterTypeID=:pid",
            array('pid'=>$typeID)
        );
    }
    
    $options = array();
    if ($name === 'Entropy') {
        $options = array(
            'Acceptable', 
            'Suspicious', 
            'Unacceptable', 
            'Not_available'
        );
    } elseif ($name === 'Movement_artifacts_within_scan') {
        $options = array('None', 'Slight', 'Poor', 'Unacceptable');
    } else {
        $options = array('Fair', 'Good', 'Poor', 'Unacceptable');
    }
    
    if($value === '' || $value === 'NULL') {
        return;
    }
    
    if (in_array($value, $options)) {
        //insert
        if (!empty($fileID)) {

            $DB->delete(
                'parameter_file', array(
                'FileID' => $fileID,
                'ParameterTypeID' => $typeID,
                )
            );                 

            //insert it
            $success = $DB->insert(
                'parameter_file', array(
                'Value'           => $value,
                'ParameterTypeID' => $typeID,
                'FileID'          => $fileID,
                'InsertTime'      => time()
                )
            );

        }
        return;
    } else {
        print "Warning: Invalid option in CSV: $value";
    }
    
    // print "\t$typeID: $value\n";
}

/*
 * Already Deletes
 */
function InsertCheckbox($typeID, $value, $comments) 
{
    $DB = Database::singleton();
    if ($value === 'No'
        || $value === ''
        || $value === 'NULL'
        || $value === 'None') 
    {
        return;
    }
    
    if ($value === 'Yes'
        || $value === 'Slight'
        || $value === 'Poor'
        || $value === 'Unacceptable') 
    {
        //insert
        $success = $DB->delete(
            "feedback_mri_comments", array(
            'PredefinedCommentID' => $typeID,
            'FileID' => $comments->fileID)
        );
        
        $comments->setPredefinedComments(array($typeID));

        return;
    }
    // print "\t$typeID: $value\n";
    //clear predefined comments
}

/*
 * from FeedbackMRI.class.inc
 * clearing comments in main
 * $comments->clearAllComments();
 */   
function InsertComment($type, $value, $comments) 
{  
    $comments->addTextComment($value, $type);
    // print "\t$type: $value\n";
}

/*
 * DB has unique index for fileID on table files_qcstatus so no need to delete
 * first.
 * 
 */
function InsertQCStatus($fileID, $value) 
{
    $DB = Database::singleton();
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
            /*
             * inserting needed improvement, more fields
             */
            $files = $DB->pselectOne(
                "SELECT * FROM files WHERE FileID = :fid",
                array("fid"=>$fileID)
            );               
               
            $success = $DB->insert(
                'files_qcstatus', array(
                'QCStatus'          => $value,
                'FileID'            => $fileID,
                'SeriesUID'         => $files['SeriesUID'],
                'EchoTime'          => $files['EchoTime'],
                'QCFirstChangeTime' => time(),
                'QCLastChangeTime'  => time()

                   )
            );
        }
    }
}

/*
 * 
 * 
 */
function InsertDTIselected($fileID, $typeID, $value) 
{
    $DB = Database::singleton();
    if (((strtoupper($value) === 'TRUE') or ($value >= 1)) and !empty($fileID)) {
        $DB->delete(
            'parameter_file', array(
            'FileID' => $fileID,
            'ParameterTypeID' => $typeID,
            )
        ); 

        $DB->insert(
            'parameter_file', array(
            'FileID'          => $fileID,
            'Value'           => 'dti',
            'ParameterTypeID' => $typeID,
            'InsertTime'      => time()
            )
        );
    }
}

/*
 * No need to delete first here. Files are unique.
 * 
 */
function UpdateCaveat($fileID, $value) 
{
    $DB = Database::singleton();
    if (!empty($fileID)) {
        if (($value === 'TRUE') or ($value == 1)) {
            $DB->update('files', array('Caveat'=>1), array('FileID'=>$fileID));
        } else if (($value === 'FALSE') or ($value == 0)) {
            $DB->update('files', array('Caveat'=>0), array('FileID'=>$fileID));
        }
    }
}

/*
 * Main
 * 
 * 
 */
while($csv_line = fgetcsv($fp))
{
    $DCCID = $csv_line[0];
    $VL    = $csv_line[1];
    if (strpos($csv_line[2],"_QCed_VC") !== false) 
    {
        $Filename = str_replace("_QCed_VC", "_DTIPrepVC_001.mnc", $csv_line[2]);
    } else {
        $Filename = $csv_line[2] . "_DTIPrepReg_001.mnc";
    }
    
    $file_info = $DB->pselectRow(
        "SELECT FileID, SessionID FROM files WHERE
                             File LIKE '%$Filename'", array()
    );

    // Failed DTIPrepReg will get their comments inserted on the unprocessed version
    if(empty($file_info)) {
        $Filename = $csv_line[2] . ".mnc";
        $file_info = $DB->pselectRow(
            "SELECT FileID, SessionID FROM files WHERE
                             File LIKE '%$Filename'", array()
    );
    }
    
    $results = array_slice($csv_line, 3, 36);
    print "File: $Filename\n";
    
    // instantiate feedback mri object
    if (!empty($file_info['FileID'])) {
        $comments = new FeedbackMRI($file_info['FileID'], $file_info['SessionID']);
        $comments->clearAllComments();

        foreach($results as $i => $value) {
            switch($i) {
            case 0:
            case 4:
            case 6:
            case 10:
                InsertDropdown($InsertTypes[$i], $results[$i], $file_info['FileID']);
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
            case 35: /* Exclude Reason */
                InsertComment($InsertTypes[$i], $results[$i], $comments);
                break;
            case 31: /* QC related types */
                InsertQCStatus($file_info['FileID'], $results[$i]);
                break;
            case 32:
                UpdateCaveat($file_info['FileID'], $results[$i]);
                break;
            case 34:
                InsertDTIselected(
                    $file_info['FileID'],
                    $InsertTypes[$i],
                    $results[$i]
                );
                break;
            case 33:
            case 36: /* Notes */
                break;
            default:
                print "Unhandled type: $i\n";
            }
        }
    }
}

?>
