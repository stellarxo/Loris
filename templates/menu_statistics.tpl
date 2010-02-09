<table border="0" valign="bottom" width="100%">

<tr><!-- title --><td class="controlPanelSection"></td></tr>

<tr><td><b><font size='2'>Welcome to the statistics page.</b><br> This will display all of the statistics related to data acquisition, data processing and data entry as it relates to both the behavioral and imaging parts of this project. This is a work in progress, and as such more statistics will appear.</font></td></tr>

<tr><td><p><b>General statistics:</b></p></td></tr>

<tr><td>
<table>
   <tr bgcolor="#08245b">
      <th></th>
      <th><font color="#CCCCCC">Timepoint</font></th>
      <th><font color="#CCCCCC">6 Month Recruits</font></th>
      <th><font color="#CCCCCC">12 Month Recruits</font></th>
      <th><font color="#CCCCCC">Controls</font></th>
   </tr>
   <tr bgcolor="#FFFFFF">
      <td> Number of registered candidates</td>
      <td></td>
      <td></td>
      <td></td>
      <td></td>
   </tr>
 
   <tr bgcolor="#FFFFFF">
      <td rowspan="3"> Number of registered visits<br> (Not Started, In Progress, Recylcing Bin entires) </td>
      <td>6 month</td>
      <td>{$count1}</td>
      <td></td>
      <td rowspan="2">{$count7}</td>
   </tr>
   <tr bgcolor="#FFFFFF">
      <td>12 month</td>
      <td>{$count3}</td>
      <td>{$count5}</td>
   </tr>
   <tr bgcolor="#FFFFFF">
      <td>24 month</td>
      <td></td>
      <td></td>
      <td></td>
   </tr>

   <tr bgcolor="#FFFFFF">
      <td rowspan="3"> Number that have begun visit stage (or the screening stage)</td>
      <td>6 month</td>
      <td>{$count2}</td>
      <td>{$count6}</td>
      <td rowspan="2">{$count8}</td>
   </tr>
   <tr bgcolor="#FFFFFF">
      <td>12 month</td>
      <td>{$count4}</td>
      <td>{$count14}</td>
   </tr>
   <tr bgcolor="#FFFFFF">
      <td>24 month</td>
      <td></td>
      <td></td>      
      <td></td>
    </tr>


</table>
</td></tr>

<tr><td><p><b>Behavioral Statistics:</b></p></td></tr>

<tr>
   <td>
      <table>
         <tr bgcolor="#08245b">
            <th><font color="#CCCCCC">Site</font></th>
            <th><font color="#CCCCCC">Completed</font></th>
            <th><font color="#CCCCCC">Total Timepoints Created</font></th>
            <th><font color="#CCCCCC">% Completion</font></th>
             <th><font color="#CCCCCC">Per instrument stats</font></th>
         </tr>
         <tr bgcolor="#FFFFFF">
            <td>Philadelphia</td>
            <td>{$phi_completed}</td>
            <td>{$phi_total}</td>
            <td>{$phi_percent}%</td>
            <td> <a href='main.php?test_name=statistics_philadelphia'>Please Click Here</a></td>

         </tr>
         <tr bgcolor="#FFFFFF">
            <td>Seattle</td>
            <td>{$sea_completed}</td>
            <td>{$sea_total}</td>
            <td>{$sea_percent}%</td>
            <td> <a href='main.php?test_name=statistics_seattle'>Please Click Here</a></td>
         </tr>
         <tr bgcolor="#FFFFFF">
            <td>St. Louis</td>
            <td>{$stl_completed}</td>
            <td>{$stl_total}</td>
            <td>{$stl_percent}%</td>
            <td> <a href='main.php?test_name=statistics_stl'>Please Click Here</a></td>
         </tr>
         <tr bgcolor="#FFFFFF">
            <td>University of North Carolina</td>
            <td>{$unc_completed}</td>
            <td>{$unc_total}</td>
            <td>{$unc_percent}%</td>
            <td> <a href='main.php?test_name=statistics_unc'>Please Click Here</a></td>
         </tr>
      </table>
   </td>
</tr>

<tr><td><p><b>Double Data Entry Statistics:</b></p></td></tr>

<tr>
   <td>
      <table>
         <tr bgcolor="#08245b">
            <th><font color="#CCCCCC">Site</font></th>
            <th><font color="#CCCCCC">Completed</font></th>
            <th><font color="#CCCCCC">Total Timepoints Created</font></th>
            <th><font color="#CCCCCC">% Completion</font></th>
            <th><font color="#CCCCCC">Per instrument stats</font></th>
         </tr>
         <tr bgcolor="#FFFFFF">
            <td>Philadelphia</td>
            <td>{$phi_dde_completed}</td>
            <td>{$phi_dde_total}</td>
            <td>{$phi_dde_percent}%</td>
            <td><a href='main.php?test_name=statistics_dd_philadelphia'>Please Click Here</a></td>
         </tr>
         <tr bgcolor="#FFFFFF">
            <td>Seattle</td>
            <td>{$sea_dde_completed}</td>
            <td>{$sea_dde_total}</td>
            <td>{$sea_dde_percent}%</td>
            <td><a href='main.php?test_name=statistics_dd_seattle'>Please Click Here</a></td>
         </tr>
         <tr bgcolor="#FFFFFF">
            <td>St. Louis</td>
            <td>{$stl_dde_completed}</td>
            <td>{$stl_dde_total}</td>
            <td>{$stl_dde_percent}%</td>
            <td><a href='main.php?test_name=statistics_dd_stl'>Please Click Here</a></td>
         </tr>
         <tr bgcolor="#FFFFFF">
            <td>University of North Carolina</td>
            <td>{$unc_dde_completed}</td>
            <td>{$unc_dde_total}</td>
            <td>{$unc_dde_percent}%</td>
            <td><a href='main.php?test_name=statistics_dd_unc'>Please Click Here</a></td>
         </tr>
      </table>
   </td>
</tr>

<tr><td><p><b>MRI Statistics:</b></p></td></tr>
<tr>
   <td>
      <table>
         <tr bgcolor="#08245b">
            <th><font color="#CCCCCC">Site</font></th>
            <th><font color="#CCCCCC">Scans on the Workstations</font></th>
            <th><font color="#CCCCCC">Scans Claimed</font></th>
            <th><font color="#CCCCCC">Parameter Forms Completed</font></th>
         </tr>
         {section name=item loop=$mri_data}
         <tr bgcolor="#FFFFFF">
            <td>{$mri_data[item].name}</td>
            <td>{$mri_data[item].work_station_count}</td>
            <td>{$mri_data[item].claimed_count}</td>
            <td>{$mri_data[item].forms_count}</td>
         </tr>
         {/section}
      </table>
   </td>
</tr>


<!--

<tr><td align="left" width="40%"><font color ="#006600"><b>Number of scans that have been completed according to the sites </b>(i.e number of completed parameter forms): <br>
PHI: <b>28</b> | 
SEA: <b>36</b> | 
STL: <b>42</b> | 
UNC: <b>27</b>
</font></td></tr>

<tr>

</tr><td align="left" width="40%"><font color ="#006600"><b>Number of scans that have been processed </b>(i.e number of scans appearing in the MRI browser): <br>
PHI: <b>16</b> | 
SEA: <b>35</b> | 
STL: <b>47</b> | 
UNC: <b>53</b>

</font></td></tr>



<tr>
<td>
<p><b>Scan types by modality:</b></p>
</td>
</tr>
<tr>
<td>
<p><i> *Please note that these numbers might change slightly since we are still in the process of finalizing data quality control.</i></p>
</td>
</tr>
<tr>
<td>
<table width="800px" border="1" bordercolor="#FFFFFF" cellspacing="0" cellpadding="0"  bgcolor="#f0f0f0">
  <tr bgcolor="#08245b"> 
    <td width="14%" ><font color="#FFFFFF"><strong>Objective 1</strong></font></td>
    <td width="14%" ><font color="#FFFFFF"><strong>Modality</strong></font></td>
    <td width="6%" ><font color="#FFFFFF"><strong>V1</strong></font></td>
    <td width="6%" ><font color="#FFFFFF"><strong>V2</strong></font></td>
    <td width="6%" ><font color="#FFFFFF"><strong>V3</strong></font></td>
    <td width="6%" ><font color="#FFFFFF"><strong>V4</strong></font></td>
    <td width="6%" ><font color="#FFFFFF"><strong>V5</strong></font></td>
    <td width="6%" ><font color="#FFFFFF"><strong>V6</strong></font></td>
    <td width="6%" ><font color="#FFFFFF"><strong>V7</strong></font></td>
    <td width="6%" ><font color="#FFFFFF"><strong>V8</strong></font></td>
    <td width="6%" ><font color="#FFFFFF"><strong>V9</strong></font></td>
    <td width="6%" ><font color="#FFFFFF"><strong>V10</strong></font></td>
    <td width="12%" ><font color="#FFFFFF"><strong>Total</strong></font></td>
  </tr>
  <tr> 
    <td>&nbsp;</td>
    <td>T1</td>
    <td>429</td>
    <td>386</td>
    <td>328</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td bgcolor="#9966FF"><strong>1152</strong></td>
  </tr>
  <tr> 
    <td>&nbsp;</td>
    <td>T2</td>
    <td>418</td>
    <td>380</td>
    <td>326</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td bgcolor="#9966ff"><strong>1132</strong></td>
  </tr>
  <tr> 
    <td>&nbsp;</td>
    <td>PD</td>
    <td>416</td>
    <td>380</td>
    <td>324</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td bgcolor="#9966ff"><strong>1128</strong></td>
  </tr>
  <tr> 
    <td>&nbsp;</td>
    <td>MRS</td>
    <td>148</td>
    <td>139</td>
    <td>114</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td bgcolor="#9966ff"><strong>401</strong></td>
  </tr>
  <tr> 
    <td>&nbsp;</td>
    <td>MRSI</td>
    <td>4</td>
    <td>59</td>
    <td>39</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td bgcolor="#9966ff"><strong>102</strong></td>
  </tr>
  <tr> 
    <td>&nbsp;</td>
    <td>Relaxometry</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td bgcolor="#9966ff">&nbsp;</td>
  </tr>
  <tr> 
    <td>&nbsp;</td>
    <td>DTI</td>
    <td>214</td>
    <td>279</td>
    <td>242</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td bgcolor="#9966ff"><strong>743</strong></td>
  </tr>
 Objective 2 ---------------------------------------------
  <tr bgcolor="#08245b"> 
    <td><font color="#FFFFFF"><strong>Objective 2</strong></font></td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
  </tr>
  <tr> 
    <td>&nbsp;</td>
    <td>T1</td>
    <td>118</td>
    <td>83</td>
    <td>67</td>
    <td>39</td>
    <td>25</td>
    <td>19</td>
    <td>15</td>
    <td>6</td>
    <td>2</td>
    <td>1</td>
     <td bgcolor="#9966ff"><strong>375</strong></td>
  </tr>
  <tr> 
    <td>&nbsp;</td>
    <td>T2</td>
    <td>115</td>
    <td>83</td>
    <td>64</td>
    <td>38</td>
    <td>25</td>
    <td>19</td>
    <td>14</td>
    <td>6</td>
    <td>2</td>
    <td>1</td>
    <td bgcolor="#9966ff"><strong>367</strong></td>
  </tr>
  <tr> 
    <td>&nbsp;</td>
    <td>PD</td>
    <td>110</td>
    <td>83</td>
    <td>65</td>
    <td>35</td>
    <td>25</td>
    <td>19</td>
    <td>14</td>
    <td>5</td>
    <td>2</td>
    <td>1</td>
    <td bgcolor="#9966ff"><strong>360</strong></td>
  </tr>
  <tr> 
    <td>&nbsp;</td>
    <td>MRS</td>
    <td>24</td>
    <td>17</td>
    <td>11</td>
    <td>3</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td bgcolor="#9966ff"><strong>55</strong></td>
  </tr>
  <tr> 
    <td>&nbsp;</td>
    <td>MRSI</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td bgcolor="#9966ff">&nbsp;</td>
  </tr>
  <tr> 
    <td>&nbsp;</td>
    <td>Relaxometry</td>
    <td>270</td>
    <td>43</td>
    <td>23</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td bgcolor="#9966ff"><strong>336</strong></td>
  </tr>
  <tr> 
    <td>&nbsp;</td>
    <td>DTI</td>
    <td>56</td>
    <td>29</td>
    <td>30</td>
    <td>25</td>
    <td>9</td>
    <td>12</td>
    <td>6</td>
    <td>4</td>
    <td>2</td>
    <td>&nbsp;</td>
    <td bgcolor="#9966ff"><strong>173</strong></td>
  </tr>
</table> -->

</td>
</tr>
</table>
