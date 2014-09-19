<script type="text/javascript" src="GetJS.php?Module=statistics&file=form_stats_reliability.js"></script>
<div id="reliability">
    <h2>Reliability Statistics{if $CurrentSite} for {$CurrentSite.Name}{/if}</h2>
    <div class="col-sm-2">
        {html_options id="ReliabilitySite" options=$Sites name="ReliabilitySite" selected=$CurrentSite.ID class="form-control input-sm"}
    </div>
    <div class="col-sm-2">  
        {html_options id="ReliabilityProject" options=$Projects name="ReliabilityProject" selected=$CurrentProject.ID class="form-control input-sm"}
    </div>
    <button class="btn btn-primary btn-sm" onClick="updateReliabilityTab()">Submit Query</button>
    <br><br>
    <div class="table-responsive">
        <table  class ="table table-hover table-primary table-bordered" border="0" width="100%">
            <thead>
                <tr class="info">
                    <th>Reliablity Module</th>
                    <th>Total Flagged</th>
                    <th>Total Complete</th>
                    <th>Total Reliable</th>
                    <th>Percent Complete</th>
                    <th>Percent Reliable</th>
                </tr>
            </thead>
            <tbody>
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
            </tbody>   
        </table>
    </div>
</div>

