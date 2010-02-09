<h2><font color="#000000">St. Louis Completion Statistics</font></h2>
<table>
   <tr bgcolor="#08245b">
      <th><font color="#CCCCCC">Instrument</font></th>
      <th><font color="#CCCCCC">Completion Count</font></th>
      <th><font color="#CCCCCC">Incomplete Candidates</font></th>
   </tr>
   {section name=item loop=$stl_data}
   <tr bgcolor="#FFFFFF">
      <td>{$stl_data[item].name}</td>
      <td>{$stl_data[item].count}</td>
      <td>{$stl_data[item].incompletes}</td>
   </tr>
   {/section}
</table>
