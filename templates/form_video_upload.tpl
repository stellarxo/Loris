{if $success}

<p>Update Successful<br /></p>
<a href='main.php?test_name=videos'> Back to Video Page</a>
<br>
{/if}

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
    {if $message}
    <tr>
        <td nowrap="nowrap" colspan="2" class="error">{$message}</td>
    </tr>
    {/if}
  <tr>
    <td nowrap="nowrap">{$form.Instrument.label}</td>
		<td nowrap="nowrap">{$form.Instrument.html}</td>
  </tr>
  <tr>
    <td nowrap="nowrap">{$form.PSCID.label}</td>
		<td nowrap="nowrap">{$form.PSCID.html}</td>
  </tr>
  <tr>
    <td nowrap="nowrap">{$form.visitLabel.label}</td>
		<td nowrap="nowrap">{$form.visitLabel.html}</td>
  </tr>
  <tr>
    <td nowrap="nowrap">{$form.Date_taken.label}</td>
		<td nowrap="nowrap">{$form.Date_taken.html}</td>
  </tr>
  <tr>
    <td nowrap="nowrap">{$form.For_site.label}</td>
		<td nowrap="nowrap">{$form.For_site.html}</td>
  </tr>
  <tr>
    <td nowrap="nowrap">{$form.multipart.label}</td>
		<td nowrap="nowrap">{$form.multipart.html}</td>
  </tr>
  <tr>
    <td nowrap="nowrap">{$form.EARLI.label}</td>
		<td nowrap="nowrap">{$form.EARLI.html}</td>
  </tr>
  <tr>
    <td nowrap="nowrap">{$form.comments.label}</td>
		<td nowrap="nowrap">{$form.comments.html}</td>
  </tr>
  {if $form.video_file}
	  <tr>
  		<td nowrap="nowrap">{$form.video_file.label}</td>
  		<td nowrap="nowrap">{$form.video_file.html}</td>
  	</tr>
  	<tr>
       <td colspan="2" style="color:red">
         Note: file name should begin with &lt;PSCID id&gt;_&lt;visit label&gt;_&lt;instrument&gt;...<br>
         For example, for candidate dcc0000, visit v12 for ADOS module 1, <br>
         the file name should be prefixed by:
         dcc0000_v12_ados_module1
       </td>
     </tr>
  {else}
    <tr>
  		<td nowrap="nowrap">{$form.File_name.label}</td>
  		<td nowrap="nowrap">{$form.File_name.html}</td>
  	</tr>  
    {if $has_delete_permission}
    <tr>
  		<td nowrap="nowrap">{$form.hide_video.label} (check both to confirm)</td>
  		<td nowrap="nowrap">{$form.hide_video.html} {$form.hide_video_confirm.html}</td>
    </tr>
    {/if}

  {/if}

  {if empty($success)}
    <tr>
  		<td nowrap="nowrap" colspan="2"><input class="button" name="fire_away" value="Upload/Delete" type="submit" /></td>
  	</tr>
  {/if}
	
</table>
{$form.hidden}
</form>

