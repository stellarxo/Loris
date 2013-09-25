<h2>{$SiteName} Completion Statistics</h2>
<table class="fancytable" width="100%">
   <tr>
      <th>Instrument</th>
      <th>Completion Count</th>
      <th colspan="{$NumVisitLabels}" width="80%">Incomplete Candidates</th>
   </tr>
   <tr>
      <th>&nbsp;</th>
      <th>&nbsp;</th>
      {foreach from=$AllVisits item=visit}
      <th width="20%">{$visit}</th>
      {/foreach}
   </tr>
   {section name=item loop=$data}
   <tr bgcolor="#FFFFFF">
      <td>{$data[item].fullname}</td>
      <td>{$data[item].count} <br />(<a href="main.php?test_name=statistics_site_breakdown&instrument={$data[item].name}&CenterID={$CenterID}">View list</a>)</td>
      {foreach from=$AllVisits item=visit name=VisitLoop}
      <td>{foreach from=$data[item].incompletes[$visit] item=Candidate name=CandLoop}
            <a href="main.php?test_name={$Candidate.test_url}&candID={$Candidate.CandID}&sessionID={$Candidate.SessionID}&commentID={$Candidate.CommentID}">{$Candidate.PSCID}</a>
          {/foreach}
      </td>
      {/foreach}
   </tr>
   {/section}
</table>
