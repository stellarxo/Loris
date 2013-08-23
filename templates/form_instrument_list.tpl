{if $success}

<p>Update Successful<br /></p>
<a href='main.php?test_name=instrument_list&candID={$candID}&sessionID={$sessionID}'> Back to Instrument List page</a>
<br>
{else}
<form method="post" name="instrument_list" id="instrument_list">
<table border="0" cellpadding="2" cellspacing="0">

<tr nowrap="nowrap">&nbsp;</tr>
<tr nowrap="nowrap">&nbsp;</tr>
<tr nowrap="nowrap">&nbsp;</tr>
<tr nowrap="nowrap">&nbsp;</tr>
<tr nowrap="nowrap">&nbsp;</tr>
<tr>

<th align="right">{$form.Comment.label}</th>
<td >{$form.Comment.html}</td> 
</tr>
<tr>
<td nowrap="nowrap">&nbsp;</td>
<td colspan="2"><input type="submit" name="submit" value="Submit" class="button" /></td>
</tr>
</table>
</form>
{/if}
