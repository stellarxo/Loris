{if $success}

<p>Family added successful<br /></p>
<br>
{/if}

<br />

<form method="post" name="add_family" id="add_family" enctype="multipart/form-data">
<table class="std">
<!-- table title -->
{if not $success}
<tr><th colspan="2">Add Family Member Information</th></tr>

{foreach from=$form.errors item=error}
<tr>
<td nowrap="nowrap" colspan="2" class="error">{$error}</td>
</tr>
{/foreach}

<tr>
<td nowrap="nowrap">{$form.SiblingID.label}</td>
<td nowrap="nowrap">{$form.SiblingID.html}</td>
</tr>
<tr>
<td nowrap="nowrap">{$form.SiblingType.label}</td>
<td nowrap="nowrap">{$form.SiblingType.html}</td>
</tr>
<tr>
<td nowrap="nowrap">&nbsp;</td>
<td nowrap="nowrap" colspan="2">
<input class="button" name="fire_away" value="Save" type="submit" />
{/if}
<input class="button" onclick="location.href='main.php?test_name=timepoint_list&candID={$candID}'" value="Return to profile" type="button" />

</td>
</tr>

</table>
