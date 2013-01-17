
{literal}
<!-- jQuery CSV parser plugin, which handles escaping/quotes -->
<script type="text/javascript" src="js/jquery.csv.js"></script>
<!-- highcharts graphing library -->
<script type="text/javascript" src="js/Highcharts/js/highcharts.src.js"></script>
<script type="text/javascript" src="js/LorisGraph.js"></script>

<script language="javascript" type="text/javascript">
var graph;
function changeFieldOptions(axis) {
    dropdown = document.getElementById("field" + axis);
    instrument = document.getElementById("instrument" + axis);
    dropdown.options.length = 0;
    $.get("GetScoreLabels.php?instrument=" + instrument.value, function(data) {
        options = data.split("\n");
        dropdown.options.length = 0;
        for(i = 0; i < options.length; i++) {
            if(options[i] != '') {
                dropdown.options[i] = new Option(options[i], options[i]);
            }
        }
        jQuery('#field' + axis).change();
    });
}

/*function updateGraph() {
    // Trigger the jQuery.change() closure created in CreateScatterplot by faking an administration change
    // (even if it's a different field that changed, it doesn't matter.
    jQuery("#Administration").change();
}*/
function CreateScatterplot() {
    var GetCSVUrl = function() {
        return 'GetCSV.php?InstrumentY=' + jQuery("#instrumenty").val() +
            '&InstrumentX=' + jQuery("#instrumentx").val() +
            '&FieldY=' + jQuery("#fieldy").val() + 
            '&FieldX=' + jQuery("#fieldx").val() + 
            '&Administration=' + jQuery('#Administration').val() +
            '&Visit_label=' + jQuery('#Visit_label').val() +
            '&site=' + jQuery('#GraphSite').val();
    };
    graph = new ACES_Scatterplot();
    graph.CSVUrl = GetCSVUrl();
    graph.CSVExtraFields = ['candID', 'sessionID', 'commentID']
    graph.RenderChart();
    FormatLink = function(url, val, extras) {
        full_url = 'main.php?test_name=' + url;
        if(extras) {
            for(exval in extras) {
                if(exval != 'x' && exval != 'y' && exval != 'name') {
                    full_url += '&' + exval + '=' + extras[exval];
                }
            }
        }
        base = '<a href="' + full_url + '">' + val + '</a><br />';
        return base;
    }
    graph.XFormat = function(val, pt) { return FormatLink(jQuery("#instrumenty").val(), jQuery("#fieldx").val() + ':' + val, pt.config); };
    graph.YFormat = function(val, pt) { return FormatLink(jQuery("#instrumenty").val(), jQuery("#fieldy").val() + ':' + val, pt.config); };
    jQuery("#fieldx").change(function() {
        graph.CSVUrl = GetCSVUrl();
        graph.UpdateXField($(this).val());
        graph.RenderChart();
    });
    jQuery("#fieldy").change(function() {
        graph.CSVUrl = GetCSVUrl();
        graph.UpdateYField($(this).val());
        graph.RenderChart();
    });
    jQuery("#Administration").change(function() {
        graph.CSVUrl = GetCSVUrl();
        graph.RenderChart();
    });
    jQuery("#GraphSite").change(function() {
        graph.CSVUrl = GetCSVUrl();
        graph.RenderChart();
    });
    jQuery("#Visit_label").change(function() {
        graph.CSVUrl = GetCSVUrl();
        graph.RenderChart();
    });
}

  $(document).ready(function() {
    $(".tabs").tabs();
    changeFieldOptions('y');
    changeFieldOptions('x');

    CreateScatterplot();
  });

</script>
{/literal}

<div class="tabs">
    <h1>Available Statistics</h1>
    <ul>
        <li><a href="#general">General Description</a></li>
        <li><a href="#demographics">Demographic Statistics</a></li>
        <li><a href="#data_entry">Behavioural Statistics</a></li>
        <li><a href="#reliability">Reliability Statistics</a></li>
        <li><a href="#enroll">Enrollment Report </a></li>
        <li><a href="#mri">MRI Statistics</a></li>
        <li><a href="#scatter">Scatterplots</a></li>
    </ul>

    <div id="general">
        <h2 class="statsH2">Welcome to the statistics page.</h2>
        <p class="statsParagraph"> This will display all of the statistics related to data acquisition, data processing and data entry as it relates to both the behavioural and imaging parts of this project. This is a work in progress, and as such more statistics will appear with time. Please feel free to contact us with feedback and suggestions.</p>
        <p>The demographics tab currently includes statistics about the number of candidates registered in each cohort and provides statistics by site and gender. In the drop-down menu, you are also able to view per instrument the number of complete and incomplete instruments per site, timepoint, and cohort.</p>
        <p>The behavioural tab currently includes statistics on the number of candidates who have completed each instrument per site and timepoint. The number of instruments for which data entry hasn't commenced is also displayed. This is a great tool for completing data entry. The same statistics are also available for double data entry.
        <p>The MRI statistics tab currently displays the number of scans per site. For T1 scans based on the MRI parameter form entries, there is a breakdown of scans per site, cohort and timepoint. There is also a table depicting common issues that need to be dealt with regarding incomplete MRI parameter forms, scans not transferred properly, or missing scan archives.</p>
    </div>

    <div id="demographics">
        <h2 class="statsH2">General statistics{if $CurrentSite} for {$CurrentSite.Name}{/if}</h2>
        <form action="#demographics">
            {html_options options=$Sites name="site" selected=$CurrentSite.ID}
            <input type="hidden" name="test_name" value="statistics" />
            <input type="submit" />
        </form>
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
                <td>Registered candidates</td>
                <td>{$registered[NULL].total}</td>
                {foreach from=$Subprojects item=proj key=keyid}
                <td>{$registered[$keyid].total}</td>
                {/foreach}
                <td class="total">{$registered.total}{if $registered.total-$Total_candidates neq 0} ({$registered.total-$Total_candidates} require DCC review){/if}</td>
            </tr>
            <tr>
                <td colspan="2">Registered candidates currently in or passed screening</td>
                {foreach from=$Subprojects item=proj key=keyid}
                <td>{$registered[$keyid].visit}</td>
                {/foreach}
                <td class="total">{$registered.visittotal}</td>
            </tr>
            <tr>
                <td colspan="2">Registered candidates who have come in for a visit</td>
                {foreach from=$Subprojects item=proj key=keyid}
                <td>{$edi[$keyid].complete}</td>
                {/foreach}
                <td class="total">{$edi.complete}</td>
            </tr>
            <tr>
                <td colspan="2">Registered candidates with T1 acquired</td>
                {foreach from=$Subprojects item=proj key=keyid}
                <td>{$scanned[$keyid].complete}</td>
                {/foreach}
                <td class="total">{$scanned.complete}</td>
            </tr>

        </tbody>
        </table>

        {$RecruitsTable}
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
<div id="reliability">
<h2 class="statsH2">Reliability Statistics{if $CurrentSite} for {$CurrentSite.Name}{/if}</h2>
        <form action="#reliability">
            {html_options options=$Sites name="site" selected=$CurrentSite.ID}
            <input type="hidden" name="test_name" value="statistics" />
            <input type="submit" />
        </form>
<table class="data">
<tr>
    <th>Reliablity Module</th>
    <th>Total Flagged</th>
    <th>Total Complete</th>
    <th>Total Reliable</th>
    <th>Percent Complete</th>
    <th>Percent Reliable</th>
</tr>
{section name=item loop=$reliability_completion}
<tr>
    <td>{$reliability_completion[item].name}</td>
    <td>{$reliability_completion[item].total}</td>
    <td>{$reliability_completion[item].complete}</td>
    <td>{$reliability_completion[item].reliable}</td>
    <td>{$reliability_completion[item].percent_complete}%</td>
    <td>{$reliability_completion[item].percent_reliable}%</td>
</tr>
{/section}
</table>
</div>

<div id="enroll">
   <form action="#enroll">
        {html_options options=$Sites name="site" selected=$CurrentSite.ID}
        <input type="hidden" name="test_name" value="statistics" />
        <input type="submit" />

        {html_options options=$Projects name="project" selected =$CurrentProject.ID}
        <input type="hidden" name="test_name" value="statistics"/>
        <input type="submit" />
    </form>
    <h2 class="statsH2"> Inclusion Enrollment Report {if $CurrentSite} for {$CurrentSite.Name}{/if} 
     {if $CurrentProject} for {$CurrentProject.Name} {/if}</h2> 
    <h2 class="statsH2"> PART A. TOTAL ENROLLMENT REPORT: Number of Subjects Enrolled to Date (Cumulative) by Ethnicity and Race </h2>
    <table class="data generalStats">
        <thead>
	<tr>
	  <th> Ethnic Category </th>
          <th> Females </th>
          <th> Males </th>
          <th> Sex/Gender unknown or Not Reported </th>
          <th> Total </th>
        </tr>
       </thead>
       <tbody>
        {section name = item loop=$enroll_data}
       <tr>
         <td>{$enroll_data[item].ethnic_cat}</td>
         <td>{$enroll_data[item].female_count}</td>
         <td>{$enroll_data[item].male_count}</td>
         <td>{$enroll_data[item].unknown_count}</td>
         <td>{$enroll_data[item].total_count}</td>
        </tr>
        {/section}
        <tr>
         <td><b>{$enroll_data_total[0].total_name}</b> </td> 
         <td>{$enroll_data_total[0].total_female} </td>
         <td>{$enroll_data_total[0].total_male}</td> 
         <td>{$enroll_data_total[0].total_unknown}</td>
         <td>{$enroll_data_total[0].total_total}</td>
        </tr> 
        </tbody>
</table>

</br>
<table class="data generalStats">
       <thead>
        <tr>
         <th> Racial Categories </th>
         <th> Females </th>
         <th> Males </th>
         <th> Sex/Gender unknown or Not Reported </th>
         <th> Total </th>
        </tr>
       </thead>
       <tbody>
        {section name = item loop=$enroll_data_race}
       <tr>
        <td>{$enroll_data_race[item].race_cat}</td>
        <td>{$enroll_data_race[item].female_count}</td>
        <td>{$enroll_data_race[item].male_count}</td>
        <td>{$enroll_data_race[item].unknown_count}</td>
        <td>{$enroll_data_race[item].total_count}</td>
        </tr>
        {/section}
        <tr>
         <td><b>{$enroll_data_racetotal[0].total_name}</b> </td>
         <td>{$enroll_data_racetotal[0].total_female} </td>
         <td>{$enroll_data_racetotal[0].total_male}</td>
         <td>{$enroll_data_racetotal[0].total_unknown}</td>
         <td>{$enroll_data_racetotal[0].total_total}</td>
        </tr>
       </tbody>
</table>

<h2 class= "statsH2">PART B. HISPANIC ENROLLMENT REPORT: Number of Hispanic or Latinos Enrolled to Date (Cumulative) </h2>
<table class ="data generalStats">
 <thead>
        <tr>
         <th> Racial Categories </th>
         <th> Females </th>
         <th> Males </th>
         <th> Sex/Gender unknown or Not Reported </th>
         <th> Total </th>
        </tr>
       </thead>
       <tbody>
        {section name = item loop=$enroll_data_hispanic}
       <tr>
        <td>{$enroll_data_hispanic[item].race_cat}</td>
        <td>{$enroll_data_hispanic[item].female_count}</td>
        <td>{$enroll_data_hispanic[item].male_count}</td>
        <td>{$enroll_data_hispanic[item].unknown_count}</td>
        <td>{$enroll_data_hispanic[item].total_count}</td>
        </tr>
        {/section}
         <tr>
         <td><b>{$enroll_data_hispanictotal[0].total_name}</b> </td>
         <td>{$enroll_data_hispanictotal[0].total_female} </td>
         <td>{$enroll_data_hispanictotal[0].total_male}</td>
         <td>{$enroll_data_hispanictotal[0].total_unknown}</td>
         <td>{$enroll_data_hispanictotal[0].total_total}</td>
        </tr>
      </tbody>
</table> 
</br>
<h2 class="statsH2"> Total Failure or Withdrawls: {$enroll_data_withdrawal} </h2>
</div>
<div id="mri">

<h2 class = "statsH2">MRI Statistics:</h2>

<h2 class="statsH2">General MRI Statistics</h2>
<table class="data generalStats">
	<thead>
         <tr>
            <th>Site</th>
            <th>Scans on the Workstations</th>
            <th>Scans Claimed</th>
            <th>v06, v12 and v24 Scans All Claimed</th>
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

<h2 class="statsH2">Candidates That Have Completed Scans at All Three Timepoints (V06, V12, and V24):</h2>
<table class="data generalStats">
	<thead>
        <tr>
            <th>Site</th>
            <th>T1 Complete</th>
            <th>T2 Complete</th>
            <th>DTI Complete</th>
            <th>T1, T2, and DTI all Complete</th>
        </tr>
    </thead>
    <tbody>
        {section name=item loop=$mri_all_scans_done}
        <tr>
            <td>{$mri_all_scans_done[item].Name}</td>
            <td>{$mri_all_scans_done[item].T1}</td>
            <td>{$mri_all_scans_done[item].T2}</td>
            <td>{$mri_all_scans_done[item].DTI}</td>
            <td>{$mri_all_scans_done[item].All}</td>

        </tr>
        {/section}
    </tbody>
</table>

{$MRI_Done_Table}

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
<div id="scatter">
<form>
<fieldset>
    <legend>Candidate Filters</legend>
    <div>
        Site: {html_options options=$Sites name="site" selected=$CurrentSite.ID id="GraphSite"}
        Administration: 
            <select name="Administration" id="Administration">
                <option value="">Any</option>
                <option value="All">All</option>
                <option value="Partial">Partial</option>
                <option value="None">None</option>
            </select>
        Visit Label: 
            <select name="Visit_label" id="Visit_label">
                <option value="">All</option>
                {foreach from=$Visits item=name key=val}
                <option value="{$name}">{$name}</option>
                {/foreach}
            </select>
    </div>
</fieldset>
<fieldset>
    <legend>Y Axis</legend>
    <div>
        Instrument: 
            <select name="InstrumentY" onChange="changeFieldOptions('y')" id="instrumenty">
            {foreach from=$all_instruments item=name key=val}
                <option value="{$name}">{$name}</option>
            {/foreach}
            </select>
        Field: 
            <select name="FieldY" id="fieldy"></select>
    </div>
</fieldset>
<fieldset>
    <legend>X Axis</legend>
    <div>
        Instrument: 
            <select name="InstrumentX" onChange="changeFieldOptions('x')" id="instrumentx">
            {foreach from=$all_instruments item=name key=val}
                <option value="{$name}">{$name}</option>
            {/foreach}
            </select>
        Field: <select name="FieldX" id="fieldx"></select>
    </div>
</fieldset>
<fieldset>
    <legend>Scatterplot</legend>
    <input type="button" value="Update chart" onClick="graph.RenderChart();" />
    <div id="scatterplot" style="width: 800px; height: 600px; margin: 0 auto"></div>

</fieldset>
</form>
</div>
