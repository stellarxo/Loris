<!--<form method="post" action="main.php?test_name=reliability">
<table border="0" valign="top" class="std" width="75%">
    <tr>
        <th nowrap="nowrap" colspan="15">Selection Filter</th>
    </tr>
    <tr>
	<td colspan = 15>
	<table border="0">
<tr>
{* OBJECTIVE IS NIHPD SPECIFIC - BUT WE ARE TOO LAZY TO CHANGE THIS TODAY *}
	<td nowrap="nowrap" align="right">CommentID:</td>
	<td nowrap="nowrap">{$form.CommentID.html}</td>
	<td nowrap="nowrap">Objective:</td>
        <td nowrap="nowrap">{$form.Objective.html}</td>
        <td nowrap="nowrap">Site:</td>
        <td nowrap="nowrap">{$form.CenterID.html}</td>
        <td nowrap="nowrap">Instrument:</td>
        <td nowrap="nowrap">{$form.Instrument.html}</td>
      </tr>
<tr>
        <td nowrap="nowrap">DCCID:</td>
        <td nowrap="nowrap">{$form.DCCID.html}</td>
        <td nowrap="nowrap">PSCID:</td>
        <td nowrap="nowrap">{$form.PSCID.html}</td>
 	<td nowrap="nowrap">Gender:</td>
        <td nowrap="nowrap">{$form.Gender.html}</td>
        <td nowrap="nowrap">Visit label:</td>
        <td nowrap="nowrap">{$form.Visit_label.html}</td>
</tr>

</table>
</td>
   </tr>
	<tr>  
	 <td colspan = 15 nowrap="nowrap"><b>Scans Done:</b></td>
	 </tr>
 
   <tr>
        <td nowrap="nowrap" width='10%'>Actions:</td>
        <td colspan="14" align="right"><input type="submit" name="filter" value="Show Data" class="button" />&nbsp;<input type="button" name="reset" value="Clear Form" class="button" onclick="location.href='main.php?test_name=reliability&reset=true'" /></td>
    </tr>
</table>
</form>-->

<br>
<!-- <h2><font color="red">Note: Phase 2 reliability forms are unavailable at the moment as the system is being upgraded.</font></h2> -->

<!--  title table with pagination -->
<table border="0" valign="bottom" width="100%">
<tr>
    <!-- title -->
    <td class="controlPanelSection">
      <a href="main.php?test_name=video_upload">
        Upload a New Video
      </a>
    </td>
</tr>
</table>

<!--  title table with pagination -->
<table border="0" valign="bottom" width="100%">
<tr>
    <!-- title -->
    <td class="controlPanelSection">List of Log Entries</td>

    <!-- display pagination links -->
    <td align="right">{$page_links}</td>
</tr>
</table>

<!-- start data table -->
<table border="0" width="100%" class="listColorCoded">
<tr>
 <th nowrap="nowrap">No.</th>
    <!-- print out column headings - quick & dirty hack -->
    {section name=header loop=$headers}
        <th nowrap="nowrap">
          <a href="main.php?test_name=videos&filter[order][field]={$headers[header].name}&filter[order][fieldOrder]={$headers[header].fieldOrder}">
            {$headers[header].displayName}
          </a>
        </th>
    {/section}
</tr>

{section name=item loop=$items}
    <tr>
    <!-- print out data rows -->
    {section name=piece loop=$items[item]}
    

	{if $items[item][piece].name == "File_name"}
	   <td nowrap="nowrap">
        <a href="{$items[item][piece].Data_dir}{$items[item][piece].value}" target="_blank">{$items[item][piece].value}</a> {if !empty($items[item][piece].File_size)}({$items[item][piece].File_size}){/if}
      </td>
   {elseif $items[item][piece].name == "record_id"}
      <td nowrap="nowrap">
          <a href="main.php?test_name=video_upload&identifier={$items[item][piece].value}" target="_blank">Edit</a> 
        </td>
	 {else}
	     <td nowrap="nowrap">{$items[item][piece].value}</td>
    {/if}
   </td>
    {/section}
    </tr>           
{sectionelse}
    <tr><td colspan="15">No videos found.</td></tr>
{/section}
                    
<!-- end data table -->
</table>

