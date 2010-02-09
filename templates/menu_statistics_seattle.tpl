<h2><font color="#000000">Seattle Completion Statistics</font></h2>
<table>
   <tr bgcolor="#08245b">
      <th><font color="#CCCCCC">Instrument</font></th>
      <th><font color="#CCCCCC">Completion Count</font></th>
      <th><font color="#CCCCCC">Incomplete Candidates</font></th>
   </tr>
   {section name=item loop=$sea_data}
   <tr bgcolor="#FFFFFF">
      <td>{$sea_data[item].name}</td>
      <td>{$sea_data[item].count}</td>
      <td>{$sea_data[item].incompletes}</td>
   </tr>
   {/section}
</table>
