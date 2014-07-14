<h2>{$SiteName} Completion Statistics {$ProjectName}</h2>
<div class="table-responsive">
   <table class="table table-primary table-bordered" width="100%">
      <tr class="info">
         <th>Instrument</th>
         <th>Completion Count</th>
         <th colspan="{$NumVisitLabels}" width="80%">Complete Candidates</th>
      </tr>
      <tr class="info">
         <th>&nbsp;</th>
         <th>&nbsp;</th>
         {foreach from=$AllVisits item=visit}
         <th width="20%">{$visit}</th>
         {/foreach}
      </tr>
      {section name=item loop=$data}
      <tr bgcolor="#FFFFFF">
         <td>{$data[item].fullname}</td>
         <td>{$data[item].count}</td>
         {foreach from=$AllVisits item=visit name=VisitLoop}
         <td>{foreach from=$data[item].completes[$visit] item=Candidate name=CandLoop}
               <a href="main.php?test_name={$Candidate.test_url}&candID={$Candidate.CandID}&sessionID={$Candidate.SessionID}&commentID={$Candidate.CommentID}">{$Candidate.PSCID}</a>
             {/foreach}
         </td>
         {/foreach}
      </tr>
      {/section}
   </table>
</div>
