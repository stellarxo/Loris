<?php
set_include_path(get_include_path().":../libraries:../../php/libraries:");
require_once 'NDB_Factory.class.inc';


class NDAR_Release_Defaced {
    var $ReplaceHeaders = array(
        'dicom_0x0018:el_0x1000',
        'dicom_0x0008:el_0x0080',
        'dicom_0x0008:el_0x0081',
        'dicom_0x0008:el_0x1010',
        'dicom_0x0008:el_0x1030',
        'dicom_0x0018:el_0x1000',
        'dicom_0x0010:el_0x0010',
        'dicom_0x0010:el_0x0020',
        'dicom_0x0010:el_0x0030',
        'dicom_0x0010:el_0x0040',
        'dicom_0x0008:el_0x0090',
        'dicom_0x0008:el_0x1048',
        'dicom_0x0010:el_0x1010',
        'dicom_0x0020:el_0x000d',
        'dicom_0x0032:el_0x1032',
        'dicom_0x0032:el_0x1060',
        'dicom_0x0040:el_0x0254',
        'dicom_0x0040:el_0x0253',
        'dicom_0x0023:el_0x0006',
        'patient:birthdate',
        'patient:sex',
        'patient:full_name',
        'study:institution',
        'study:referring_physician',
        'patient:age',
        'study:serial_no',
        'study:station_id',
        'study:procedure',
        // Appears to be patient name
        'dicom_0x0010:el_0x1001',
        // Appears to be institution name
        'dicom_0x0010:el_0x0021',
        'dicom_0x0010:el_0x1040',
        'dicom_0x0038:el_0x0500',
        'dicom_0x0905:el_0x1030',
        'dicom_0x0010:el_0x1001',
        'dicom_0x0010:el_0x2150'
    );

    var $DateHeaders = array(
        'acquisition:start_time',
        'dicom_0x0008:el_0x0012',
        'dicom_0x0008:el_0x0018',
        'dicom_0x0008:el_0x0020',
        'dicom_0x0008:el_0x0021',
        'dicom_0x0008:el_0x0022',
        'dicom_0x0008:el_0x0023',
        'dicom_0x0020:el_0x000e',
        'dicom_0x0020:el_0x0052',
        'dicom_0x0029:el_0x1009',
        'dicom_0x0029:el_0x1019',
        'dicom_0x0040:el_0x0244',
        'study:start_date',
        'study:study_id'
    );

    var $CSVData = array();
    function copyFile($origin, $dest) {
        if(!is_dir(dirname($dest))) {
            mkdir(dirname($dest), 0777, true);
        }
        return copy($origin, $dest);
    }
    function replaceID($string, $CandID, $IBISID) {
        return preg_replace("/$CandID/", $IBISID, $string);
    }
    function anonFile($original, $output) {
        print "Copying $original\n";
        $this->copyFile($original, $output);
        print "Copied to $output\n";
        foreach ($this->ReplaceHeaders as $header) {
            $this->anonHeader($output, $header, 'ibis');
        }
        print "Anonymized replacement headers\n";
        foreach ($this->DateHeaders as $header) {
            $date = $this->getHeader($original, $header);
            if($date != array()) {
                $anon_date = substr($date, 0, 6);
                $this->anonHeader($output, $header, $anon_date);
            }
        }
        print "Done anonymizing all $output\n\n";
    }

    function getHeader($file, $header) {
        $data = shell_exec("mincheader $file | grep $header");
        $val = explode('"', $data);
        //print "Getting header $header from $file\n";
        if(count($val) > 1) {
            return $val[1];
        } else {
            $val = explode(" = ", $data);
            $val = $val[1];
            // chop off ;
            $val = substr($val, 0, -2);

            return trim($val);
        }
    }
    function anonHeader($file, $header, $value='ibis') {
        system("minc_modify_header -sinsert " . escapeshellarg($header . "=" . $value) . " $file");
    }

    function addToCSV($file, $info) {
        $StudyDate = $this->getHeader($info['File'], 'study:start_date');
        $ScannerID = $this->getHeader($info['File'], 'study:serial_no');
        $XSpace    = $this->getHeader($info['File'], 'xspace:length');
        $YSpace    = $this->getHeader($info['File'], 'yspace:length');
        $ZSpace    = $this->getHeader($info['File'], 'zspace:length');
        $XStep    = $this->getHeader($info['File'], 'xspace:step');
        $YStep    = $this->getHeader($info['File'], 'yspace:step');
        $ZStep    = $this->getHeader($info['File'], 'zspace:step');

        $StudyYear = substr($StudyDate, 0, 4);
        $StudyMo   = substr($StudyDate, 4, 2);
        $StudyDay   = substr($StudyDate, 6, 2);

        $desc = '';
        if(strpos($file, 't1w') !== FALSE) {
            $desc = 'T1';
        } elseif(strpos($file, 't2w') !== FALSE) {
            $desc = 'T2';
        }
        print "$StudyYear $StudyMo $StudyDay\n";
        $this->CSVData[] = array(
            'image_file'           => $file,
            /* 'ProbandGUID' => $info['ProbandGUID'], */
            'subjectkey'           => $info['CandidateGUID'],
            'src_subject_ID'       => $info['IBISID'],
            'gender'               => $info['Gender'],
            'ScanDate'             => $StudyDate,
            'Site'                 => $info['CenterID'],
            'ScannerID'            => md5($ScannerID),
            'interview_date'       => "$StudyMo/01/$StudyYear",
            'interview_age'        => round(date_diff(new DateTime("$StudyYear-$StudyMo-$StudyDay"), new DateTime($info['DoB']))->format('%a') / (365/12)),
            'image_file_format'    => 'MINC',
            'image_modality'       => 'MRI',
            'image_description'    => $desc,
            'image_num_dimensions' => 3,
            'image_extent1'        => $XSpace,
            'image_extent2'        => $YSpace,
            'image_extent3'        => $ZSpace,
            'image_thumbnail_file' => '',
            'scanner_manufacturer_pd'=> 'Siemens',
            'transformation_performed'=> 'Yes',
            'transformation_type' => 'DICOM to MINC',
            'image_unit1'          => 'millimeters',
            'image_unit2'          => 'millimeters',
            'image_unit3'          => 'millimeters',
            'image_orientation'    => 'sagittal',
            'image_resolution1'    => abs($XStep),
            'image_resolution2'    => abs($YStep),
            'image_resolution3'    => abs($ZStep),
            'image_slice_thickness'=> abs($XStep)

        );
    }
    function run() {
        $factory = NDB_Factory::singleton();
        $db = $factory->Database();

        $files = scandir("/home/driusan/NDAR/V06/Valid");
        foreach($files as $file) {
            if(strpos($file, ".mnc") === FALSE 
                || (strpos($file, "t1w") === FALSE
                && strpos($file, "t2w") === FALSE
            )) {
                continue;
            }

            $pieces = explode("_", $file);
            $info = $db->pselectRow("SELECT ProbandGUID, CandidateGUID, CenterID, DoB, IBISID, Gender FROM candidate WHERE CandID=:dccid", array('dccid' => $pieces[1]));

            $file_anonymized = $this->replaceID($file, $pieces[1], $info['IBISID']);
            $this->anonFile("/home/driusan/NDAR/V06/Valid/$file", "IBIS1_anon/$file_anonymized");
            $this->addToCSV($file_anonymized, array
                (
                    'File' => "/home/driusan/NDAR/V06/Valid/$file",
                    'ProbandGUID' => $info['ProbandGUID'],
                    'CandidateGUID' => $info['CandidateGUID'],
                    'CenterID' => $info['CenterID'],
                    'DoB' => $info['DoB'],
                    'IBISID' => $info['IBISID'],
                    'Gender' => $info['Gender']
                )
            );
        }
        $fp = fopen("IBIS1_anon/NDARMRI_Defaced.csv", 'w');
        fputcsv($fp, array('image03'));
        fputcsv($fp, array_keys($this->CSVData[0]));
        foreach ($this->CSVData as $row) {
            fputcsv($fp, $row);
        }
        fclose($fp);
        print_r($this->CSVData);
    }
}
// Don't run if we're doing the unit tests, the unit test will call run..
if(!class_exists('UnitTestCase')) {
    require_once "NDB_Client.class.inc";
    $client = new NDB_Client();
    $client->makeCommandLine();
    $client->initialize('../config.xml');
    $Runner = new NDAR_Release_Defaced();
    $Runner->run();
}
?>
