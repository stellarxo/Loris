<h2><font color="#000000">Philadelphia Completion Statistics</font></h2>
<table>
   <tr bgcolor="#08245b">
      <th><font color="#CCCCCC">Instrument</font></th>
      <th><font color="#CCCCCC">Completion Count</font></th>
      <th><font color="#CCCCCC">Incomplete Candidates</font></th>
   </tr>
   {section name=item loop=$phi_data}
   <tr bgcolor="#FFFFFF">
      <td>{$phi_data[item].name}</td>
      <td>{$phi_data[item].count}</td>
      <td>{$phi_data[item].incompletes}</td>
   </tr>
   {/section}
</table>
