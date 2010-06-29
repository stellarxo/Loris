<table border="0" valign="bottom" width="100%">

<tr><!-- title --><td class="controlPanelSection"></td></tr>

<tr><td><b><font size='2'>Welcome to the statistics page.</b><br> This will display all of the statistics related to data acquisition, data processing and data entry as it relates to both the behavioral and imaging parts of this project. This is a work in progress, and as such more statistics will appear.</font></td></tr>

<tr><td><p><b>General statistics:</b></p></td></tr>

<tr><td>
<table class="data">
   <tr>
      <th></th>
       <th>Undefined Yet</th>
      {foreach from=$Subprojects item=name key=proj}
      <th>{$name}</th>
      {/foreach}
      <th class="data">Total</th>
   </tr>
  <tr>
       <td>Number of registered candidates</td>
       <td>{$registered[NULL].total}</td>
        {foreach from=$Subprojects item=proj key=keyid}
            <td>{$registered[$keyid].total}</td>
       {/foreach}
       <td class="total">{$registered.total}{if $registered.total-$Total_candidates neq 0} ({$registered.total-$Total_candidates} require DCC review){/if}</td>
   </tr>
</table>

</td></tr>
<tr><td>

<table class="data">
<tr>
      <th></th>
      {foreach from=$Subprojects item=name key=proj}
      <th>{$name}</th>
      {/foreach}
      <th>Total</th>
</tr>

 <tr>
  <td>Total number of registered candidates in visit stage<br></td>
  {foreach from=$Subprojects item=proj key=keyid}
  <td>{$registered[$keyid].visit}</td>
  {/foreach}
  <td class="total">{$registered.visittotal}</td>
</tr>
      
</table>

</td></tr>
<tr><td>

<table class="data">
<br>
<tr>
      <th rowspan="2"></th>
      <th rowspan="2">Timepoint</th>
      {foreach key=proj item=name from=$Subprojects}
      <th colspan="3">{$name}</th>
      {/foreach}
      <th colspan="3">Total</th>
   </tr>
   
   <tr>
         <th>Male</th>
         <th>Female</th>
         <th>Total</th>
         <th>Male</th>
         <th>Female</th>
         <th>Total</th>
         <th>Male</th>
         <th>Female</th>
         <th>Total</th>
         <th>Male</th>
         <th>Female</th>
         <th>Total</th>
      </tr>

 
      {foreach item=center from=$Centers}
      <tr>
            <td rowspan="5">{$center.LongName}<br></td>
            {foreach item=visit from=$Visits key=title}
            {if $visit neq 'v06'}
            <tr>
            {/if}
                <td>{$title}</td>
                {foreach key=proj item=value from=$Subprojects}
                    {* Special case. proj=2 means its a 12 month visit.
                     * and it's impossible to have a 6 month visit for
                     * a 12 month recruit. *}
                    {if $visit eq 'v06' and $proj eq 2}
                        <td class="male">NA</td>
                        <td class="female">NA</td>
                        <td class="subtotal">NA</td>
                    {else}
                        <td class="male">{$recruits[$proj][$center.ID][$visit].male|default:"0"}</td>
                        <td class="female">{$recruits[$proj][$center.ID][$visit].female|default:"0"}</td>
                        <td class="subtotal">{$recruits[$proj][$center.ID][$visit].male+$recruits[$proj][$center.ID][$visit].female}</td>
                    {/if}
                {/foreach}
                {* Totals for row *}
                <td class="male total">{$recruits[$center.ID][$visit].male|default:"0"}</td>
                <td class="female total">{$recruits[$center.ID][$visit].female|default:"0"}</td>
                <td class="total">{$recruits[$center.ID][$visit].male+$recruits[$center.ID][$visit].female}</td>
            </tr>
            {/foreach}
      </tr>
      {/foreach}
      {* Totals at the bottom *}
      <tr>
        <td rowspan="5">Total<br></td>
        {foreach from=$Visits item=visit key=title}
            {if $visit neq 'v06'}
                <tr bgcolor="#FFFFFF">
            {/if}
            <td>{$title}</td>     
            {foreach from=$Subprojects key=proj item=value}
               {if $visit eq 'v06' and $proj eq 2}
                    <td class="male">NA</td>
                    <td class="female">NA</td>
                    <td class="subtotal">NA</td>
               {else}
                    <td class="male">{$recruits[$proj][$visit].male|default:"0"}</td>
                    <td class="female">{$recruits[$proj][$visit].female|default:"0"}</td>
                    <td class="subtotal">{$recruits[$proj][$visit].male+$recruits[$proj][$visit].female}</td>
               {/if}
            {/foreach}
            <td class="male total">{$recruits[$visit].male|default:"0"}</td>
            <td class="female total">{$recruits[$visit].female|default:"0"}</td>
            <td class="total">{$recruits[$visit].male+$recruits[$visit].female|default:"0"}</td>
            </tr>
        {/foreach}

</table>
</td></tr>

<tr><td><p><b>Behavioral Statistics:</b></p></td></tr>

<tr>
   <td>
      <table class="data">
         <tr>
            <th rowspan="2">Site</th>
            {foreach from=$Visits item=visit}
            <th colspan="3">{$visit|upper}</th>
            {/foreach}
            <th colspan="3">Total</th>
            <th rowspan="2">Per instrument stats</th>
         </tr>
         <tr>
            {foreach from=$Visits item=visit}
             <th>Completed</th>
             <th>Created</th>
             <th>% Completion</th>
            {/foreach}
             {* Total isn't in the visits array, so we need to manually add its header *}
             <th>Completed</th>
             <th>Created</th>
             <th>% Completion</th>
          </tr>
         {foreach from=$Centers item=center key=centername}
         <tr>
            <td>{$center.LongName}</td>
            {foreach from=$Visits item=visit}
                <td>{$behaviour[$center.ID][$visit].complete|default:"0"}</td>
                <td>{$behaviour[$center.ID][$visit].total|default:"0"}</td>
                <td>{$behaviour[$center.ID][$visit].percent|default:"0"}%</td>
            {/foreach}
            <td class="total">{$behaviour[$center.ID].all.complete|default:"0"}</td>
            <td class="total">{$behaviour[$center.ID].all.total|default:"0"}</td>
            <td class="total">{$behaviour[$center.ID].all.percent|default:"0"}%</td>
            <td> <a href='main.php?test_name=statistics_site&CenterID={$center.NumericID}'>Please Click Here</a></td>
         </tr>
         {/foreach}
      </table>
   </td>
</tr>



<tr><td><p><b>Double Data Entry Statistics:</b></p></td></tr>

<tr>
   <td>
      <table class="data">
         <tr>
            <th rowspan="2">Site</th>
            {foreach from=$Visits item=visit}
            <th colspan="3">{$visit|upper}</th>
            {/foreach}
            <th colspan="3">Total</th>
            <th rowspan="2">Per instrument stats</th>
         </tr>
         <tr>
            {foreach from=$Visits item=visit}
             <th>Completed</th>
             <th>Created</th>
             <th>% Completion</th>
            {/foreach}
             {* Total isn't in the visits array, so we need to manually add its header *}
             <th>Completed</th>
             <th>Created</th>
             <th>% Completion</th>
          </tr>
         {foreach from=$Centers item=center key=centername}
         <tr>
            <td>{$center.LongName}</td>
            {foreach from=$Visits item=visit}
                <td>{$dde[$center.ID][$visit].complete|default:"0"}</td>
                <td>{$dde[$center.ID][$visit].total|default:"0"}</td>
                <td>{$dde[$center.ID][$visit].percent|default:"0"}%</td>
            {/foreach}
                <td class="total">{$dde[$center.ID].all.complete|default:"0"}</td>
                <td class="total">{$dde[$center.ID].all.total|default:"0"}</td>
                <td class="total">{$dde[$center.ID].all.percent|default:"0"}%</td>
            <td> <a href='main.php?test_name=statistics_dd_site&CenterID={$center.NumericID}'>Please Click Here</a></td>
         </tr>
         {/foreach}
      </table>
   </td>
</tr>

<tr><td><p><b>MRI Statistics:</b></p></td></tr>
<tr>
   <td>
      <table class="data">
         <tr>
            <th>Site</th>
            <th>Scans on the Workstations</th>
            <th>Scans Claimed</th>
            <th>Parameter Forms Completed</th>
         </tr>
         {section name=item loop=$mri_data}
         <tr>
            <td>{$mri_data[item].name}</td>
            <td>{$mri_data[item].work_station_count}</td>
            <td>{$mri_data[item].claimed_count}</td>
            <td>{$mri_data[item].forms_count}</td>
         </tr>
         {/section}
      </table>
   </td>
</tr>
<tr><td><p><b>T1 Scan Breakdown:</b></p></td></tr>
<tr>
    <td>
      <table class="data">
         <tr>
            <th>&nbsp;</th>
            <th>Timepoint</th>
            {foreach from=$Subprojects item=name key=proj}
                <th>{$name}</th>
            {/foreach}
            <th>Total</th>
         </tr>
         <tr>
      {foreach item=center from=$Centers}
      <tr>
            <td rowspan="3">{$center.LongName}<br></td>
            {foreach item=visit from=$Visits key=title}
            {if $visit neq 'v18' and $visit neq 'v36'}
            
            {if $visit neq 'v06'}
            <tr>
            {/if}
                <td>{$title}</td>
                {foreach key=proj item=value from=$Subprojects}
                    {* Special case. proj=2 means its a 12 month visit.
                     * and it's impossible to have a 6 month visit for
                     * a 12 month recruit. *}
                    {if $visit eq 'v06' and $proj eq 2}
                        <td>NA</td>
                    {else}
                        <td>{$mri_total[$proj][$center.ID][$visit]|default:0}</td>
                    {/if}
                {/foreach}
                <td class="subtotal">{$mri_total[$center.ID][$visit].total}</td>
            </tr>
            {/if}
            {/foreach}
      </tr>
      {/foreach}
      <tr>
        <td>Total</td>
        <td>All</td>
        {foreach from=$Subprojects item=name key=proj}
            <td class="subtotal">{$mri_total[$proj].total}</td>
        {/foreach}
        <td class="total">{$mri_total.total}</td>
      </tr>
      </table>
    </td>
</tr>
</td>
</tr>
<tr><td><p><b>MRI Integrity Statistics:</b></p></td></tr>
<tr>
    <td>
      <table class="data">
      <tr>
            <th>Site</th>
            <th>No Parameter Form Completed</th>
            <th>Nothing in MRI Browser for Form</th>
            <th>No tarchive Entry for Form</th>
            <th>Breakdown of Problems</th>
      </tr>
      {foreach item=center from=$Centers}
      <tr>
            <td>{$center.LongName}</td>
            <td>{$mri_errors[$center.NumericID].no_parameter}</td>
            <td>{$mri_errors[$center.NumericID].no_browser}</td>
            <td>{$mri_errors[$center.NumericID].no_tarchive}</td>
            <td><a href="?test_name=statistics_mri_site&CenterID={$center.NumericID}">Please Click Here</a></td>
      </tr>
      {/foreach}
      </table>
      
</table>
