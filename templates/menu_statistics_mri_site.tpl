<h2>{$SiteName} MRI Integrity Statistics</h2>
<div class="table-responsive">
   <table class="table table-primary table-bordered" width="100%">
      <tr>
         <th>Instrument</th>
         <th colspan="{$NumVisitLabels}" width="80%">Incomplete Entries</th>
      </tr>
      <tr>
         <th>&nbsp;</th>
         {foreach from=$AllVisits item=visit}
         <th width="20%">{$visit}</th>
         {/foreach}
      </tr>
      {section name=item loop=$data}
      <tr bgcolor="#FFFFFF">
         <td>{$data[item].name}</td>
         {foreach from=$AllVisits item=visit name=VisitLoop}
         <td>{foreach from=$data[item].incompletes[$visit] item=Candidate name=CandLoop}
               {if $Candidate.test_url == "PF_Missing"}
                   <a href="mri_browser.php?sessionID={$Candidate.SessionID}">
               {else}
               <a href="main.php?test_name=mri_parameter_form&candID={$Candidate.CandID}&sessionID={$Candidate.SessionID}&commentID={$Candidate.CommentID}">
               {/if}
               {$Candidate.PSCID}</a>
             {/foreach}
         </td>
         {/foreach}
      </tr>
      {/section}
   </table>
</div>
