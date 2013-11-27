<form method="post" name="participant_status_history" id="participant_status_history" enctype="multipart/form-data">
<table class="std">
<!-- table title -->
<tr><th colspan="2">Participant Status History for Candidate {$candID}</th></tr>

{foreach from=$form.errors item=error}
<tr>
<td nowrap="nowrap" colspan="2" class="error">{$error}</td>
</tr>
{/foreach}
{foreach from=$history_list item=element}
<tr>
<td nowrap="nowrap">{$form.$element.label}</td>
<td nowrap="nowrap">{$form.$element.html}</td>
</tr>
{/foreach}
<tr>
<td nowrap="nowrap">&nbsp;</td>
<td nowrap="nowrap" colspan="2">
<input class="button" onclick="location.href='main.php?test_name=timepoint_list&candID={$candID}'" value="Return to profile" type="button" />

</td>
</tr>

</table>

