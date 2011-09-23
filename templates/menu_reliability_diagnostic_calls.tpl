<h2><font color="#000000">Diagnostic Behavioural Call Cases</font></h2>

<table>
   <tr bgcolor="#08245b">
      <th><font color="#CCCCCC">Date of Review</font></th>
      <th><font color="#CCCCCC">Case 1 ID</font></th>
      <th><font color="#CCCCCC">Case 2 ID</font></th>
   </tr>
   {section name=item loop=$data}
   <tr bgcolor="#FFFFFF">
      <td>{$data[item].date_of_review}</td>
      <td>{$data[item].caseID_1}</td>
      <td>{$data[item].caseID_2}</td>
   </tr>
   {/section}
</table>


