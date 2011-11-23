<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
	   "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<LINK REL=StyleSheet HREF="{$css}" TYPE="text/css">
<!-- shortcut icon that displays on the browser window -->
<link rel="shortcut icon" href="images/mni_icon.ico" type="image/ico" />
<!-- page title -->
<TITLE>MRI - {$study_title}</TITLE>
<!-- end page header -->

{literal}
<script type="text/javascript">
function open_popup(newurl) {
var x = 200, y = 400;
   var open_params = 'width=500px,height=300px,toolbar=no,location=no,status=yes,scrollbars=yes,resizable=yes,top='+y+',screenY='+y+',left='+x+',screenX='+x;
  //alert(open_params);
  window.open(newurl, 'feedback_mri', open_params);
}
</script>
{/literal}
</head>
<body>

<div id="sidebar" style="position:fixed; top: 75px; padding-left: 5px;">
<!-- back button and other navigation buttons -->
        <h2>Links</h2>
        <ul class="controlPanel">
        {if $subject.ParameterFormCommentID}
            <li class="controlPanelItem">
                <a href="main.php?test_name=mri_parameter_form&candID={$subject.candid}&sessionID={$subject.sessionID}&commentID={$subject.ParameterFormCommentID}">MRI Parameter Form</a>
            </li>
        {/if}
        {if $subject.RadiologicalReviewCommentID}
            <li class="controlPanelItem">
                <a href="main.php?test_name=final_radiological_review&subtest=final_radiological_review&identifier={$subject.RadiologicalReviewCommentID}">Radiological Review</a>
            </li>
        {/if}
        {if $subject.tarchiveids != ""}
                {foreach from=$subject.tarchiveids item=Tarchive }
                <li class="controlPanelItem"><a href="dicom_archive.php?TarchiveID={$Tarchive.TarchiveID}" class="linkButton">DICOM Archive {$Tarchive.TarchiveID}</a>
                </li>
                {/foreach}
        {/if}
            <li class="controlPanelItem">
                <a href="{$mantis}" target="mantis">Mantis</a>
            </li>
        </ul>
    {if $backURL!=""}
        <h2>Navigation</h2>
        <ul class="controlPanel">
<!-- Back Button -  -->
        <li><a href="{$backURL}"><img src="images/left.gif" align="texttop" alt="Back" border="0" width="12" height="12"><img src="images/left.gif" align="texttop" alt="Back" border="0" width="12" height="12">Back to list</a></li>
    {/if}
<!-- Prev Button -->
    {if $prevTimepoint.URL!=""}
         <li><a href="{$prevTimepoint.URL}"><img src="images/left.gif" align="texttop" alt="Back" border="0" width="12" height="12">Previous</a></li>
    {/if}
<!-- Next Button -->
    {if $nextTimepoint.URL!=""}
       <li><a href="{$nextTimepoint.URL}">
        <img src="images/right.gif" alt="Back" align="texttop" border="0" width="12" height="12">
        Next</a>
       </li>
    {/if}
    </ul>

    {if $showFloatJIV}
    <div id="divTopRight">
    <p>3D panel viewing<br><br>
    <input type="button" accesskey="c" class="button" value="3D+Overlay" onClick="javascript:show_jiv(jivNames, jivData, true);"><br>
    <input type="button" accesskey="d" class="button" value="3D Only" onClick="javascript:show_jiv(jivNames, jivData, false);">
    </p>
    </div>

    <div id="divBottomLeft">
    <p>Visit-Level controls</p>
     <a href="#" onClick="javascript:open_popup('feedback_mri_popup.php?sessionID={$subject.sessionID}')">Visit-level<br>feedback</a>
    <!-- table with candidate profile info -->
    {if $has_permission}<form action="" method="post">{/if}
    <p>QC Status<br>   {if $has_permission}{html_options options=$status_options selected=$subject.mriqcstatus name=visit_status tabindex=1>}
                   {else}{$subject.mriqcstatus}
                   {/if}
    </p>
    <p>QC Pending<br>  {if $has_permission}{html_options options=$pending_options selected=$subject.mriqcpending name=visit_pending tabindex=2}
                   {else}{if $subject.mriqcpending=="Y"}<img src="images/check_blue.gif" width="12" height="12">{else}&nbsp;{/if}
                   {/if}
    </p>
    {if $has_permission}<input class="button" type="submit" accesskey="s" value="Save" name="save_changes">{/if}            
    </div>
    {/if}

</div>
<!-- start main table -->
<table width="95%" border="0" cellpadding="5" cellspacing="2">
<tr>
    <th background="images/title_background.jpg" class="banner" colspan="2" align="left">
        <strong>MRI browser - {$study_title}</strong>
    </th>
</tr>
<tr>
    <td colspan="2" class="controlPanelSection" >
        User:&nbsp;
        {$user_full_name}
        &nbsp;&nbsp;Site:&nbsp;
        {$user_site_name}
        &nbsp;&nbsp;Date:&nbsp;
        {$smarty.now|date_format:"%B %e %Y"}
    </td>
</tr>

<tr>
    <td width="10%" class="tabox" valign="top" nowrap="nowrap">
    
        <!-- Start Section on the left -->
    </td>
    
    
    <!-- main page table tags -->
    <td width=100% class="tabox" valign="top">
    
    
    <!-- Start workspace area -->
    
    {$body}
    
    <!-- end workspace area -->
    
    <!-- end Main Table and HTML PAGE -->
    </td>
</tr>
</table>
</body>
</HTML>






