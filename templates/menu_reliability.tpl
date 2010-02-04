<form method="post" action="main.php?test_name=reliability">
<!-- start the selection table -->
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
<!--        <td nowrap="nowrap"><input type="button" name="button" value="Add Instrument" class="button" onclick="location.href='main.php?test_name=csbs_reliability&subtest=csbs_reliability'"/></td> -->
        <td colspan="14" align="right"><input type="submit" name="filter" value="Show Data" class="button" />&nbsp;<input type="button" name="reset" value="Clear Form" class="button" onclick="location.href='main.php?test_name=reliability&reset=true'" /></td>
    </tr>
</table>
</form>

<br>
<a href='main.php?test_name=reliability_phase_one'>Phase 1 Reliability</a> |
<a href='main.php?test_name=reliability_diagnostic_calls'>Diagnostic Behavioural Call Cases</a> 
<br>
<br>
<!-- <h2><font color="red">Note: Phase 2 reliability forms are unavailable at the moment as the system is being upgraded.</font></h2> -->

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
          {if $headers[header].displayName != "Reliable"}
            <a href="main.php?test_name=reliability&filter[order][field]={$headers[header].name}&filter[order][fieldOrder]={$headers[header].fieldOrder}">
              {if $headers[header].displayName == "Reliability Center Id"}
                Site of Reliability Test
              {else}
                {$headers[header].displayName}
              {/if}
            </a>
          {else}
            {$headers[header].displayName}
          {/if}
        </th>
    {/section}
</tr>

{section name=item loop=$items}
    <tr>
    <!-- print out data rows -->
    {section name=piece loop=$items[item]}
    

	{if $items[item][piece].name == "PSCID"}
	   <td nowrap="nowrap">
	   {if $items[item][piece].Current_stage == 'Recycling Bin'}
        {$items[item][piece].value} <font color="red">(Recycling Bin)</font>
     {elseif $items[item][piece].invalid == "yes"}
        {$items[item][piece].value} <font color="red">(Invalid)</font>
     {else}     
          <a href="main.php?test_name={$items[item][piece].Instrument}_reliability&subtest={$items[item][piece].Instrument}_reliability&identifier={$items[item][piece].CommentID}&reliability_center_id={$items[item][piece].SiteID}">{$items[item][piece].value}</a> 
       {/if}
      </td>
	{elseif  $items[item][piece].name == "Cohort"}
	      <td nowrap="nowrap">
  	    {if $items[item][piece].value== "1"}
      					6 month
      	{elseif $items[item][piece].value== "2"}
      					12 month
      	{elseif $items[item][piece].value== "3"}
      					Control
      		{/if}</td>
  	{elseif  $items[item][piece].name == "Reliability"}
  	  {if $items[item][piece].value== "Yes"}
  	  <td nowrap="nowrap" style="background-color:#55FF55;">{$items[item][piece].value}</td>
  	  {elseif $items[item][piece].value== "No"}
  	  <td nowrap="nowrap" style="background-color:#FF2222;color:white">{$items[item][piece].value}</td>
  	  {else}
  	  <td nowrap="nowrap"></td>
  	  {/if}
	  {else}
	     <td nowrap="nowrap">{$items[item][piece].value}</td>
    {/if}
   </td>
    {/section}
    </tr>           
{sectionelse}
    <tr><td colspan="15">No reliability entries found</td></tr>
{/section}
                    
<!-- end data table -->
</table>

