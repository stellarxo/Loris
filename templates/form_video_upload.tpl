{if $success}

<p>File Uploaded<br /></p>
<a href='main.php?test_name=videos'> Back to Video Page</a>
{else}

<br />
<form method="post" name="video_upload" id="video_upload" enctype="multipart/form-data">
<table class="std">
    <!-- table title -->
    <tr><th colspan="2">Upload a New Video</th></tr>

    {foreach from=$form.errors item=error}
    <tr>
        <td nowrap="nowrap" colspan="2" class="error">{$error}</td>
    </tr>
    {/foreach}
  <tr>
    <td nowrap="nowrap">Select an Instrument</td>
		<td nowrap="nowrap">{$form.Instrument.html}</td>
  </tr>
  <tr>
    <td nowrap="nowrap">Select a Candidate</td>
		<td nowrap="nowrap">{$form.PSCID.html}</td>
  </tr>
  <tr>
    <td nowrap="nowrap">Select a Visit Label</td>
		<td nowrap="nowrap">{$form.visitLabel.html}</td>
  </tr>
  <tr>
    <td nowrap="nowrap">Select the Site This Video is Being Uploaded For (optional)</td>
		<td nowrap="nowrap">{$form.For_site.html}</td>
  </tr>
  <tr>
    <td nowrap="nowrap">Comments (optional)</td>
		<td nowrap="nowrap">{$form.comments.html}</td>
  </tr>
	<tr>
		<td nowrap="nowrap">Upload a New File</td>
		<td nowrap="nowrap">{$form.video_file.html}</td>
	</tr>

	<tr>
		<td nowrap="nowrap" colspan="2"><input class="button" name="fire_away" value="Upload" type="submit" /></td>
	</tr>
</table>
{$form.hidden}
</form>

{/if}