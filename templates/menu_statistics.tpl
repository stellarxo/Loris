
{literal}

<script language="javascript" type="text/javascript">

  $(document).ready(function() {
    $(".tabs").tabs();
  });

</script>
{/literal}

<div class="tabs">
    <h1>Available Statistics</h1>
    <ul>
        <li><a href="#general">General Description</a></li>
        <li><a href="#demographics">Demographic Statistics</a></li>
        <li><a href="#data_entry">Behavioural Statistics</a></li>
        <li><a href="#mri">MRI Statistics</a></li>
    </ul>

    <div id="general">
        <h2 class="statsH2">Welcome to the statistics page.</h2>
        <p class="statsParagraph"> This will display all of the statistics related to data acquisition, data processing and data entry as it relates to both the behavioural and imaging parts of this project. This is a work in progress, and as such more statistics will appear with time. Please feel free to contact us with feedback and suggestions.</p>
        <p>The demographics tab currently includes statistics about the number of candidates registered in each cohort and provides statistics by site and gender. In the drop-down menu, you are also able to view per instrument the number of complete and incomplete instruments per site, timepoint, and cohort.</p>
        <p>The behavioural tab currently includes statistics on the number of candidates who have completed each instrument per site and timepoint. The number of instruments for which data entry hasn't commenced is also displayed. This is a great tool for completing data entry. The same statistics are also available for double data entry.
        <p>The MRI statistics tab currently displays the number of scans per site. For T1 scans based on the MRI parameter form entries, there is a breakdown of scans per site, cohort and timepoint. There is also a table depicting common issues that need to be dealt with regarding incomplete MRI parameter forms, scans not transferred properly, or missing scan archives.</p>
    </div>

    <div id="demographics">
        <h2 class="statsH2">General statistics:</h2>
        <table class="data generalStats">
        <thead>
            <tr>
                <th></th>
                <th>Undefined Yet</th>
                {foreach from=$Subprojects item=name key=proj}
                    <th>{$name}</th>
                {/foreach}
                <th class="data">Total</th>
            </tr>
        </thead>
        <tbody>
            <tr>
                <td>Number of registered candidates</td>
                <td>{$registered[NULL].total}</td>
                {foreach from=$Subprojects item=proj key=keyid}
                <td>{$registered[$keyid].total}</td>
                {/foreach}
                <td class="total">{$registered.total}{if $registered.total-$Total_candidates neq 0} ({$registered.total-$Total_candidates} require DCC review){/if}</td>
            </tr>
            <tr>
                <td colspan="2">Total number of registered candidates in visit stage<br></td>
                {foreach from=$Subprojects item=proj key=keyid}
                <td>{$registered[$keyid].visit}</td>
                {/foreach}
                <td class="total">{$registered.visittotal}</td>
            </tr>
        </tbody>
        </table>

        <h2 class="statsH2">{$RecruitHeader}</h2>
        <form action="#demographics" onChange="$(this).submit();">
            <input type="hidden" name="test_name" value="statistics">
            {html_options options=$instruments name="instrument" selected=$instrument}
            <input type="submit" />
        </form>

        <table class="data" width="50%">
            <tr>
                <th rowspan="2">Timepoint</th>
                {foreach key=proj item=name from=$Subprojects}
                <th colspan="{php}print count($this->get_template_vars("Subcategories"))+1;{/php}">{$name}</th>
                {/foreach}
                <th colspan="{php}print count($this->get_template_vars("Subcategories"))+1;{/php}">Total</th>
            </tr>
            <tr>
                {foreach key=proj item=name from=$Subprojects}
                {* Go through each category once, and add the total
                   for each cohort *}
                {foreach key=subcategory item=category from=$Subcategories}
                <th>{$category}</th>
                {/foreach}
                <th>Percent {$Subcategories.0}</th>
                {/foreach}

                {* And then each category once for the totals *}
                {foreach key=subcategory item=category from=$Subcategories}
                <th>{$category}</th>
                {/foreach}
                <th>Total Percent {$Subcategories.0}</th>
            </tr>
 
   {foreach item=center from=$Centers}
    <th colspan="14" width="50%">{$center.LongName}<br></th></tr>
        {foreach item=visit from=$Visits key=title}
            {assign var="rowtotal" value="0}

		<tr></tr>
            {if $visit neq 'v06'}
            <tr>
            {/if}
                <td>{$title}</td>
                {foreach key=proj item=value from=$Subprojects}
                    {* Special case. proj=2 means its a 12 month visit.
                     * and it's impossible to have a 6 month visit for
                     * a 12 month recruit. *}
                {assign var="subtotal" value="0" }
                {foreach key=sub item=subcat from=$Subcategories}
                    {if $visit eq 'v06' and $proj eq 2}
                        <td class="{$subcat|lower}">NA</td>
                    {else}
                        <td class="{$subcat|lower}">{$recruits[$proj][$center.ID][$visit][$subcat]|default:"0"}</td>
                        {assign var="subtotal" value=`$subtotal+$recruits[$proj][$center.ID][$visit][$subcat]` }
                        {assign var="rowtotal" value=`$rowtotal+$recruits[$proj][$center.ID][$visit][$subcat]` }
                    {/if}
                {/foreach}
                <td class="subtotal">
                    {if $recruits[$proj][$center.ID][$visit].Male}
                        {assign var="Numerator" value=`$recruits[$proj][$center.ID][$visit].Male`}
                    {elseif $recruits[$proj][$center.ID][$visit].Complete}
                        {assign var="Numerator" value=`$recruits[$proj][$center.ID][$visit].Complete`}
                    {else}
                        {assign var="Numerator" value=0}
                    {/if}
                    {php}
                        $Numerator = $this->get_template_vars("Numerator");
                        $Denominator = $this->get_template_vars("subtotal");
                        if($Denominator > 0) {
                            print round($Numerator*100/$Denominator);
                            print "%";
                        } else {
                            print "0%";
                        }
                    {/php}
                </td>
                {/foreach}
                {* Totals for row *}
                {foreach key=sub item=subcat from=$Subcategories}
                    <td class="{$subcat|lower} total">{$recruits[$center.ID][$visit][$subcat]|default:"0"}</td>
                {/foreach}
                <td class="total">
                    {if $recruits[$center.ID][$visit].Male}
                        {assign var="Numerator" value=`$recruits[$center.ID][$visit].Male`}
                    {elseif $recruits[$center.ID][$visit].Complete}
                        {assign var="Numerator" value=`$recruits[$center.ID][$visit].Complete`}
                    {else}
                        {assign var="Numerator" value=0}
                    {/if}
                    {php}
                        $Numerator = $this->get_template_vars("Numerator");
                        $Denominator = $this->get_template_vars("rowtotal");
                        if($Denominator > 0) {
                            print round($Numerator*100/$Denominator);
                            print "%";
                        } else {
                            print "0%";
                        }
                    {/php}
                </td>
            </tr>
            {/foreach}
      {/foreach}
      {* Totals at the bottom *}
	<tr>
      <th colspan="14" width="50%">Total</th>
	</tr>
	<tr>
       <!-- <td rowspan="5">Total<br></td>-->
        {foreach from=$Visits item=visit key=title}
            {if $visit neq 'v06'}
		<tr>
                <tr bgcolor="#FFFFFF">
            {/if}
            <td>{$title}</td>     
            {foreach from=$Subprojects key=proj item=value}
                {assign var="subtotal" value="0" }
                {foreach key=sub item=subcat from=$Subcategories}
                    {if $visit eq 'v06' and $proj eq 2}
                        <td class="{$subcat|lower}">NA</td>
                    {else}
                        <td class="{$subcat|lower}">{$recruits[$proj][$visit][$subcat]|default:"0"}</td>
                        {assign var="subtotal" value=`$subtotal+$recruits[$proj][$visit][$subcat]` }
                    {/if}
                {/foreach}
                <td class="subtotal">
                    {if $recruits[$proj][$visit].Male}
                        {assign var="Numerator" value=`$recruits[$proj][$visit].Male`}
                    {elseif $recruits[$proj][$visit].Complete}
                        {assign var="Numerator" value=`$recruits[$proj][$visit].Complete`}
                    {else}
                        {assign var="Numerator" value=0}
                    {/if}
                    {php}
                        $Numerator = $this->get_template_vars("Numerator");
                        $Denominator = $this->get_template_vars("subtotal");
                        if($Denominator > 0) {
                            print round($Numerator*100/$Denominator);
                            print "%";
                        } else {
                            print "0%";
                        }
                    {/php}
                </td>
            {/foreach}
            {assign var="finaltotal" value="0" }
            {foreach key=sub item=subcat from=$Subcategories}
                <td class="{$subcat|lower} total">{$recruits[$visit][$subcat]|default:"0"}</td>
                {assign var="finaltotal" value=`$finaltotal+$recruits[$visit][$subcat]` }
            {/foreach}
            <td class="total">
                    {if $recruits[$visit].Male}
                        {assign var="Numerator" value=`$recruits[$visit].Male`}
                    {elseif $recruits[$visit].Complete}
                        {assign var="Numerator" value=`$recruits[$visit].Complete`}
                    {else}
                        {assign var="Numerator" value=0}
                    {/if}
                    {php}
                        $Numerator = $this->get_template_vars("Numerator");
                        $Denominator = $this->get_template_vars("finaltotal");
                        if($Denominator > 0) {
                            print round($Numerator*100/$Denominator);
                            print "%";
                        } else {
                            print "0%";
                        }
                    {/php}
            </td>
            </tr>
        {/foreach}
    </table>

</div>
<div id="data_entry">
<h2 class="statsH2">Data Entry Statistics:</h2>
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


<h2 class="statsH2">Double Data Entry Statistics:</h2>
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
<br />
</div>
<div id="mri">

<h2 class = "statsH2">MRI Statistics:</h2>
<table class="data generalStats">
	<thead>
         <tr>
            <th>Site</th>
            <th>Scans on the Workstations</th>
            <th>Scans Claimed</th>
            <th>Parameter Forms Completed</th>
         </tr>
	</thead>
	<tbody>
         {section name=item loop=$mri_data}
         <tr>
            <td>{$mri_data[item].name}</td>
            <td>{$mri_data[item].work_station_count}</td>
            <td>{$mri_data[item].claimed_count}</td>
            <td>{$mri_data[item].forms_count}</td>
         </tr>
         {/section}
	</tbody>
</table>

<h2 class="statsH2">T1 Scan Breakdown:</h2>
<table class="data generalStats">
	<thead>
         <tr>
            <th>&nbsp;</th>
            <th>Timepoint</th>
            {foreach from=$Subprojects item=name key=proj}
                <th>{$name}</th>
            {/foreach}
            <th>Total</th>
         </tr>
	</thead>
	<tbody>
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
	</tbody>
</table>

<h2 class="statsH2">MRI Integrity Statistics:</h2>
<table class="data generalStats">
	<thead>
      <tr>
            <th>Site</th>
            <th>No Parameter Form Completed</th>
            <th>Nothing in MRI Browser for Form</th>
            <th>No tarchive Entry for Form</th>
            <th>Breakdown of Problems</th>
      </tr>
	</thead>
	<tbody>
      {foreach item=center from=$Centers}
      <tr>
            <td>{$center.LongName}</td>
            <td>{$mri_errors[$center.NumericID].no_parameter}</td>
            <td>{$mri_errors[$center.NumericID].no_browser}</td>
            <td>{$mri_errors[$center.NumericID].no_tarchive}</td>
            <td><a href="?test_name=statistics_mri_site&CenterID={$center.NumericID}">Please Click Here</a></td>
      </tr>
      {/foreach}
	</tbody>
</table>
</div>
