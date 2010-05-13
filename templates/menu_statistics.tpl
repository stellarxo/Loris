<table border="0" valign="bottom" width="100%">

<tr><!-- title --><td class="controlPanelSection"></td></tr>

<tr><td><b><font size='2'>Welcome to the statistics page.</b><br> This will display all of the statistics related to data acquisition, data processing and data entry as it relates to both the behavioral and imaging parts of this project. This is a work in progress, and as such more statistics will appear.</font></td></tr>

<tr><td><p><b>General statistics:</b></p></td></tr>

<tr><td>
<table>
   <tr bgcolor="#08245b">
      <th></th>
       <th><font color="#CCCCCC">Undefined Yet</font></th>
      <th><font color="#CCCCCC">6 Month Recruits</font></th>
      <th><font color="#CCCCCC">12 Month Recruits</font></th>
      <th><font color="#CCCCCC">Controls</font></th>
      <th><font color="#CCCCCC">Total</font></th>
   </tr>
 
 <tr bgcolor="#FFFFFF">
      <td>Number of registered candidates</td>
       <td>{$Undefined_candidates}</td>
      <td>{$SixMonthRecruit_SixMonthVisit}</td>
      <td>{$count5}</td>
      <td>{$Controls_number}</td>
      <td>{$Total_candidates}</td>
  </tr>

</table>

</td></tr>
<tr><td>

<table>
<br>
<tr bgcolor="#08245b">
      <th></th>
      <th><font color="#CCCCCC">6 Month Recruits</font></th>
      <th><font color="#CCCCCC">12 Month Recruits</font></th>
      <th><font color="#CCCCCC">Controls</font></th>
      <th><font color="#CCCCCC">Total</font></th>
</tr>

 <tr bgcolor="#FFFFFF">
      <td>Total number of registered candiates in visit stage<br></td>
      <td>{$SixMonthRecruit_AllVisits}</td>
      <td> - </td>
      <td> - </td>
      <td> - </td>
   </tr>
</table>

</td></tr>
<tr><td>

<table>
<br>
<tr bgcolor="#08245b">
      <th></th>
      <th><font color="#CCCCCC">Timepoint</font></th>
      <th><font color="#CCCCCC">6 Month Recruits</font></th>
      <th><font color="#CCCCCC">12 Month Recruits</font></th>
      <th><font color="#CCCCCC">Controls</font></th>
      <th><font color="#CCCCCC">Total</font></th>
   </tr>

 
 <tr bgcolor="#FFFFFF">
      <td rowspan="5"> Number of registered visits<br></td>
      <td>6 month</td>     
      <td>{$count2}</td>
      <td>NA</td>
      <td>{$count7}</td>
      <td></td>
   </tr>
   
   <tr bgcolor="#FFFFFF">
      <td>12 month</td>
      <td>{$count4}</td>
      <td>{$count14}</td>
      <td>{$count13}</td>
      <td></td>
   </tr>

<tr bgcolor="#FFFFFF">
      <td>18 month</td>
      <td>{$Six_month_recruit_18_month_visit}</td>
      <td>{$Twelve_month_recruit_18_month_visit}</td>
      <td>{$controls_registered_v18}</td>
      <td></td>
</tr>
   
   <tr bgcolor="#FFFFFF">
      <td>24 month</td>
      <td>{$Six_month_recruit_24_month_visit}</td>
      <td>{$Twelve_month_recruit_24_month_visit}</td>
      <td>{$controls_registered_v24}</td>
      <td></td>
   </tr>
 
  <tr bgcolor="#FFFFFF">
      <td>36 month</td>
      <td></td>
      <td></td>
      <td></td>
      <td></td>
   </tr>


<!--
   <tr bgcolor="#FFFFFF">
      <td rowspan="3"> Number that have begun visit stage (or the screening stage)</td>
      <td>6 month</td>
      <td></td>     
      <td>{$count2}</td>
      <td>{$count6}</td>
      <td rowspan="2">{$count8}</td>
   </tr>
   <tr bgcolor="#FFFFFF">
 
      <td>12 month</td>
     <td></td>
      <td>{$count4}</td>
      <td>{$count14}</td>
    
  </tr>
   <tr bgcolor="#FFFFFF">
      <td>24 month</td>
      <td></td>  
      <td></td>
      <td></td>      
      <td></td>
    </tr>

-->
</table>
</td></tr>

<tr><td><p><b>Behavioral Statistics:</b></p></td></tr>

<tr>
   <td>
      <table>
         <tr bgcolor="#08245b">
            <th rowspan="2"><font color="#CCCCCC">Site</font></th>
            <th colspan="3"><font color="#CCCCCC">V06</font></th>
            <th colspan="3"><font color="#CCCCCC">V12</font></th>
            <th colspan="3"><font color="#CCCCCC">V18</font></th>
            <th colspan="3"><font color="#CCCCCC">V24</font></th>
            <th colspan="3"><font color="#CCCCCC">V36</font></th>
            <th colspan="3"><font color="#CCCCCC">Total</font></th>
            <th rowspan="2"><font color="#CCCCCC">Per instrument stats</font></th>
         </tr>
         <tr bgcolor="#08245b">
             <th><font color="#CCCCCC">Completed</font></th>
             <th><font color="#CCCCCC">Created</font></th>
             <th><font color="#CCCCCC">% Completion</font></th>
             <th><font color="#CCCCCC">Completed</font></th>
             <th><font color="#CCCCCC">Created</font></th>
             <th><font color="#CCCCCC">% Completion</font></th>
             <th><font color="#CCCCCC">Completed</font></th>
             <th><font color="#CCCCCC">Created</font></th>
             <th><font color="#CCCCCC">% Completion</font></th>
             <th><font color="#CCCCCC">Completed</font></th>
             <th><font color="#CCCCCC">Created</font></th>
             <th><font color="#CCCCCC">% Completion</font></th>
             <th><font color="#CCCCCC">Completed</font></th>
             <th><font color="#CCCCCC">Created</font></th>
             <th><font color="#CCCCCC">% Completion</font></th>
             <th><font color="#CCCCCC">Completed</font></th>
             <th><font color="#CCCCCC">Created</font></th>
             <th><font color="#CCCCCC">% Completion</font></th>
          </tr>
         <tr bgcolor="#FFFFFF">
            <td>Philadelphia</td>
            <td>{$v06_phi_completed}</td>
            <td>{$v06_phi_total}</td>
            <td>{$v06_phi_percent}%</td>
            <td>{$v12_phi_completed}</td>
            <td>{$v12_phi_total}</td>
            <td>{$v12_phi_percent}%</td>
            <td>{$v18_phi_completed}</td>
            <td>{$v18_phi_total}</td>
            <td>{$v18_phi_percent}%</td>
            <td>{$v24_phi_completed}</td>
            <td>{$v24_phi_total}</td>
            <td>{$v24_phi_percent}%</td>
            <td>{$v36_phi_completed}</td>
            <td>{$v36_phi_total}</td>
            <td>{$v36_phi_percent}%</td>
            <td>{$all_phi_completed}</td>
            <td>{$all_phi_total}</td>
            <td>{$all_phi_percent}%</td>
            <td> <a href='main.php?test_name=statistics_philadelphia'>Please Click Here</a></td>

         </tr>
         <tr bgcolor="#FFFFFF">
            <td>Seattle</td>
            <td>{$v06_sea_completed}</td>
            <td>{$v06_sea_total}</td>
            <td>{$v06_sea_percent}%</td>
            <td>{$v12_sea_completed}</td>
            <td>{$v12_sea_total}</td>
            <td>{$v12_sea_percent}%</td>
            <td>{$v18_sea_completed}</td>
            <td>{$v18_sea_total}</td>
            <td>{$v18_sea_percent}%</td>
            <td>{$v24_sea_completed}</td>
            <td>{$v24_sea_total}</td>
            <td>{$v24_sea_percent}%</td>
            <td>{$v36_sea_completed}</td>
            <td>{$v36_sea_total}</td>
            <td>{$v36_sea_percent}%</td>
            <td>{$all_sea_completed}</td>
            <td>{$all_sea_total}</td>
            <td>{$all_sea_percent}%</td>
            <td> <a href='main.php?test_name=statistics_seattle'>Please Click Here</a></td>
         </tr>
         <tr bgcolor="#FFFFFF">
            <td>St. Louis</td>
            <td>{$v06_stl_completed}</td>
            <td>{$v06_stl_total}</td>
            <td>{$v06_stl_percent}%</td>
            <td>{$v12_stl_completed}</td>
            <td>{$v12_stl_total}</td>
            <td>{$v12_stl_percent}%</td>
            <td>{$v18_stl_completed}</td>
            <td>{$v18_stl_total}</td>
            <td>{$v18_stl_percent}%</td>
            <td>{$v24_stl_completed}</td>
            <td>{$v24_stl_total}</td>
            <td>{$v24_stl_percent}%</td>
            <td>{$v36_stl_completed}</td>
            <td>{$v36_stl_total}</td>
            <td>{$v36_stl_percent}%</td>
            <td>{$all_stl_completed}</td>
            <td>{$all_stl_total}</td>
            <td>{$all_stl_percent}%</td>
            <td> <a href='main.php?test_name=statistics_stl'>Please Click Here</a></td>
         </tr>
         <tr bgcolor="#FFFFFF">
            <td>University of North Carolina</td>
            <td>{$v06_unc_completed}</td>
            <td>{$v06_unc_total}</td>
            <td>{$v06_unc_percent}%</td>
            <td>{$v12_unc_completed}</td>
            <td>{$v12_unc_total}</td>
            <td>{$v12_unc_percent}%</td>
            <td>{$v18_unc_completed}</td>
            <td>{$v18_unc_total}</td>
            <td>{$v18_unc_percent}%</td>
            <td>{$v24_unc_completed}</td>
            <td>{$v24_unc_total}</td>
            <td>{$v24_unc_percent}%</td>
            <td>{$v36_unc_completed}</td>
            <td>{$v36_unc_total}</td>
            <td>{$v36_unc_percent}%</td>
            <td>{$all_unc_completed}</td>
            <td>{$all_unc_total}</td>
            <td>{$all_unc_percent}%</td>
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
            <th rowspan="2"><font color="#CCCCCC">Site</font></th>
            <th colspan="3"><font color="#CCCCCC">V06</font></th>
            <th colspan="3"><font color="#CCCCCC">V12</font></th>
            <th colspan="3"><font color="#CCCCCC">V18</font></th>
            <th colspan="3"><font color="#CCCCCC">V24</font></th>
            <th colspan="3"><font color="#CCCCCC">V36</font></th>
            <th colspan="3"><font color="#CCCCCC">Total</font></th>
            <th rowspan="2"><font color="#CCCCCC">Per instrument stats</font></th>
         </tr>
         <tr bgcolor="#08245b">
             <th><font color="#CCCCCC">Completed</font></th>
             <th><font color="#CCCCCC">Created</font></th>
             <th><font color="#CCCCCC">% Completion</font></th>
             <th><font color="#CCCCCC">Completed</font></th>
             <th><font color="#CCCCCC">Created</font></th>
             <th><font color="#CCCCCC">% Completion</font></th>
             <th><font color="#CCCCCC">Completed</font></th>
             <th><font color="#CCCCCC">Created</font></th>
             <th><font color="#CCCCCC">% Completion</font></th>
             <th><font color="#CCCCCC">Completed</font></th>
             <th><font color="#CCCCCC">Created</font></th>
             <th><font color="#CCCCCC">% Completion</font></th>
             <th><font color="#CCCCCC">Completed</font></th>
             <th><font color="#CCCCCC">Created</font></th>
             <th><font color="#CCCCCC">% Completion</font></th>
             <th><font color="#CCCCCC">Completed</font></th>
             <th><font color="#CCCCCC">Created</font></th>
             <th><font color="#CCCCCC">% Completion</font></th>
          </tr>
         <tr bgcolor="#FFFFFF">
            <td>Philadelphia</td>
            <td>{$v06_phi_dde_completed}</td>
            <td>{$v06_phi_dde_total}</td>
            <td>{$v06_phi_dde_percent}%</td>
            <td>{$v12_phi_dde_completed}</td>
            <td>{$v12_phi_dde_total}</td>
            <td>{$v12_phi_dde_percent}%</td>
            <td>{$v18_phi_dde_completed}</td>
            <td>{$v18_phi_dde_total}</td>
            <td>{$v18_phi_dde_percent}%</td>
            <td>{$v24_phi_dde_completed}</td>
            <td>{$v24_phi_dde_total}</td>
            <td>{$v24_phi_dde_percent}%</td>
            <td>{$v36_phi_dde_completed}</td>
            <td>{$v36_phi_dde_total}</td>
            <td>{$v36_phi_dde_percent}%</td>
            <td>{$all_phi_dde_completed}</td>
            <td>{$all_phi_dde_total}</td>
            <td>{$all_phi_dde_percent}%</td>
            <td> <a href='main.php?test_name=statistics_philadelphia'>Please Click Here</a></td>

         </tr>
         <tr bgcolor="#FFFFFF">
            <td>Seattle</td>
            <td>{$v06_sea_dde_completed}</td>
            <td>{$v06_sea_dde_total}</td>
            <td>{$v06_sea_dde_percent}%</td>
            <td>{$v12_sea_dde_completed}</td>
            <td>{$v12_sea_dde_total}</td>
            <td>{$v12_sea_dde_percent}%</td>
            <td>{$v18_sea_dde_completed}</td>
            <td>{$v18_sea_dde_total}</td>
            <td>{$v18_sea_dde_percent}%</td>
            <td>{$v24_sea_dde_completed}</td>
            <td>{$v24_sea_dde_total}</td>
            <td>{$v24_sea_dde_percent}%</td>
            <td>{$v36_sea_dde_completed}</td>
            <td>{$v36_sea_dde_total}</td>
            <td>{$v36_sea_dde_percent}%</td>
            <td>{$all_sea_dde_completed}</td>
            <td>{$all_sea_dde_total}</td>
            <td>{$all_sea_dde_percent}%</td>
            <td> <a href='main.php?test_name=statistics_seattle'>Please Click Here</a></td>
         </tr>
         <tr bgcolor="#FFFFFF">
            <td>St. Louis</td>
            <td>{$v06_stl_dde_completed}</td>
            <td>{$v06_stl_dde_total}</td>
            <td>{$v06_stl_dde_percent}%</td>
            <td>{$v12_stl_dde_completed}</td>
            <td>{$v12_stl_dde_total}</td>
            <td>{$v12_stl_dde_percent}%</td>
            <td>{$v18_stl_dde_completed}</td>
            <td>{$v18_stl_dde_total}</td>
            <td>{$v18_stl_dde_percent}%</td>
            <td>{$v24_stl_dde_completed}</td>
            <td>{$v24_stl_dde_total}</td>
            <td>{$v24_stl_dde_percent}%</td>
            <td>{$v36_stl_dde_completed}</td>
            <td>{$v36_stl_dde_total}</td>
            <td>{$v36_stl_dde_percent}%</td>
            <td>{$all_stl_dde_completed}</td>
            <td>{$all_stl_dde_total}</td>
            <td>{$all_stl_dde_percent}%</td>
            <td> <a href='main.php?test_name=statistics_stl'>Please Click Here</a></td>
         </tr>
         <tr bgcolor="#FFFFFF">
            <td>University of North Carolina</td>
            <td>{$v06_unc_dde_completed}</td>
            <td>{$v06_unc_dde_total}</td>
            <td>{$v06_unc_dde_percent}%</td>
            <td>{$v12_unc_dde_completed}</td>
            <td>{$v12_unc_dde_total}</td>
            <td>{$v12_unc_dde_percent}%</td>
            <td>{$v18_unc_dde_completed}</td>
            <td>{$v18_unc_dde_total}</td>
            <td>{$v18_unc_dde_percent}%</td>
            <td>{$v24_unc_dde_completed}</td>
            <td>{$v24_unc_dde_total}</td>
            <td>{$v24_unc_dde_percent}%</td>
            <td>{$v36_unc_dde_completed}</td>
            <td>{$v36_unc_dde_total}</td>
            <td>{$v36_unc_dde_percent}%</td>
            <td>{$all_unc_dde_completed}</td>
            <td>{$all_unc_dde_total}</td>
            <td>{$all_unc_dde_percent}%</td>
            <td> <a href='main.php?test_name=statistics_unc'>Please Click Here</a></td>
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
