<h2><font color="#000000">{$SiteName} MRI Problem Statistics</font></h2>
<table>
   <tr bgcolor="#08245b">
      <th><font color="#CCCCCC">Integrity Check</font></th>
      <th><font color="#CCCCCC">Incorrect Candidates</font></th>
   </tr>
   {section name=item loop=$data}
   <tr bgcolor="#FFFFFF">
      <td>{$data[item].title}</td>
      <td>
      {foreach from=$data[item].incompletes item=candidate name=candidates}
        {if $data[item].type eq 'parameter_form'}
        <a href="?test_name=mri_parameter_form&candID={$candidate.CandID}&sessionID={$candidate.session}&commentID={$candidate.CommentID}">
        {/if}
        {if $data[item].type eq 'mri_browser'}
        <a href="mri_browser.php?sessionID={$candidate.session}">
        {/if}
        {$candidate.name}
        {if $data[item].type eq 'mri_browser' or $data[item].type eq 'parameter_form'}
        </a>
        {/if}{if !$smarty.foreach.candidates.last},{/if}
      {/foreach}
      </td>
   </tr>
   {/section}
</table>
