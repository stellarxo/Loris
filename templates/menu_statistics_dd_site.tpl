<h2><font color="#000000">{$SiteName} Completion Statistics</font></h2>
<table>
   <tr bgcolor="#08245b">
      <th><font color="#CCCCCC">Instrument</font></th>
      <th><font color="#CCCCCC">Completion Count</font></th>
      <th><font color="#CCCCCC">Incomplete Candidates</font></th>
   </tr>
   {section name=item loop=$data}
   <tr bgcolor="#FFFFFF">
      <td>{$data[item].name}</td>
      <td>{$data[item].count}</td>
      <td>{$data[item].incompletes}</td>
   </tr>
   {/section}
</table>
