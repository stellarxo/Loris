<form method="post" name="participant_status_history" id="participant_status_history" enctype="multipart/form-data">
<table class="std">
<!-- table title -->
<tr><th colspan="4">Participant Status History for Candidate {$candID}</th></tr>
<tr>
<td nowrap="nowrap" >PSCID: {$pscid}</td>
<tr>
<tr>
<th>Participant Status</th>
<th>Data Entry Staff</th>
<th>Timestamp</th>
<th>Comments</th>
</tr>
<tr></tr>
{foreach from=$history_list item=row}
<tr>
{foreach from=$row item=value key=name}
<td>{$value}</td>
{/foreach}
</tr>
<tr></tr>
{/foreach}

<tr>
<td nowrap="nowrap">&nbsp;</td>
<td nowrap="nowrap">&nbsp;</td>
<td nowrap="nowrap">&nbsp;</td>
<td nowrap="nowrap" colspan="3">
<input align="right" class="button" onclick="location.href='main.php?test_name=timepoint_list&candID={$candID}'" value="Return to profile" type="button" />

</td>
</tr>

</table>

