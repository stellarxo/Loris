<form method="post" action="main.php?test_name=videos">
<table border="0" class="std">
    <tr>
        <th nowrap="nowrap" colspan="6">Selection Filter</th>
    </tr>
    <tr>
        <td>{$form.PSCID.label}</td>
        <td>{$form.PSCID.html}</td>
        <td>{$form.uploaded_by.label}</td>
        <td>{$form.uploaded_by.html}</td>
        <td>&nbsp;</td>
        <td>&nbsp;</td>
    </tr>
    <tr>
        <td>{$form.Instrument.label}</td>
        <td>{$form.Instrument.html}</td>
        <td>{$form.visitLabel.label}</td>
        <td>{$form.visitLabel.html}</td>
        <td>{$form.For_site.label}</td>
        <td>{$form.For_site.html}</td>
    </tr>
    <tr>
    </tr>
    <tr>
        <td nowrap="nowrap" width='10%'>Actions:</td>
        <td colspan="14" align="right"><input type="submit" name="filter" value="Show Data" class="button" />&nbsp;<input type="button" name="reset" value="Clear Form" class="button" onclick="location.href='main.php?test_name=videos&reset=true'" /> <input type="button" class="button" value="Upload a New Video" onclick="location.href='main.php?test_name=video_upload'" />
        </td>
    </tr>
</table>
</form>

<br>
<!--  title table with pagination -->
<table border="0" valign="bottom" width="100%">
<tr>
    <td class="controlPanelSection">
      {if $Normal_Perm}
        <a href="main.php?test_name=videos&showEARLI=">IBIS Videos</a> 
      {/if}
      {if $Normal_Perm && $EARLI_Perm}
      |
      {/if}
      {if $EARLI_Perm}
        <a href="main.php?test_name=videos&showEARLI=1">EARLI Videos</a>
      {/if}
    </td>
</tr>
<tr>
    <!-- title -->
  
    <td class="controlPanelSection">

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
          {if $headers[header].displayName == 'Edit Metadata'}
            Edit Metadata
          {else}
          <a href="main.php?test_name=videos&filter[order][field]={$headers[header].name}&filter[order][fieldOrder]={$headers[header].fieldOrder}">
            {$headers[header].displayName}
          </a>
          {/if}
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

