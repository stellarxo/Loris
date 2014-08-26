{literal}

<script language="javascript" type="text/javascript">
    function togglePanel(panel) {
        "use strict";
        $("#panel-body-" + panel).toggle();
        $("#down-" + panel).toggle();
        $("#up-" + panel).toggle();
    }
</script>
{/literal}

<div class="col-sm-12">
    <div class="panel panel-primary">
        <div class="panel-heading" onclick="hideFilter();">
            Selection Filter  
            <label id="advanced-label" style="display:none">(Advanced Options)</label>
            <span class="glyphicon glyphicon-chevron-down pull-right" style="display:none" id="down"></span>
            <span class="glyphicon glyphicon-chevron-up pull-right" id="up"></span>
        </div>
        <div class="panel-body" id="panel-body">
            <form method="post" action="main.php?test_name=reliability">
                {if $form.error}
                    <div class="error">{$form.error.label}</div>
                {/if}
                {if $form.message}
                    <div class="error">{$form.message.label}</div>
                {/if}
                <div class="row">
                    <div class="form-group col-sm-2">
                        <label class="col-xs-12">
                            {$form.SubprojectID.label}
                        </label>
                        <div class="col-xs-12">
                            {$form.SubprojectID.html}
                        </div>
                    </div>
                    <div class="form-group col-sm-2">
                        <label class="col-xs-12">
                            {$form.ProjectID.label}
                        </label>
                        <div class="col-xs-12">
                            {$form.ProjectID.html}
                        </div>
                    </div>
                    <div class="form-group col-sm-2">
                        <label class="col-xs-12">
                            {$form.CenterID.label}
                        </label>
                        <div class="col-xs-12">
                            {$form.CenterID.html}
                        </div>
                    </div>
                    <div class="form-group col-sm-3">
                        <label class="col-xs-12">
                            {$form.Instrument.label}
                        </label>
                        <div class="col-xs-12">
                            {$form.Instrument.html}
                        </div>
                    </div>
                    <div class="form-group col-sm-3">
                        <label class="col-xs-12">
                            {$form.reliability_center_id.label}
                        </label>
                        <div class="col-xs-12">
                            {$form.reliability_center_id.html}
                        </div>
                    </div>
                </div>
                <div class="row">
                    <div class="form-group col-sm-2">
                        <label class="col-xs-12">
                            DCCID:
                        </label>
                        <div class="col-xs-12">
                            {$form.DCCID.html}
                        </div>
                    </div>
                    <div class="form-group col-sm-2">
                        <label class="col-xs-12">
                            PSCID:
                        </label>
                        <div class="col-xs-12">
                            {$form.PSCID.html}
                        </div>
                    </div>
                    <div class="form-group col-sm-2">
                        <label class="col-xs-12">
                            Gender:
                        </label>
                        <div class="col-xs-12 col-lg-8">
                            {$form.Gender.html}
                        </div>
                    </div>
                    <div class="form-group col-sm-3">
                        <label class="col-xs-12">
                            Visit label:
                        </label>
                        <div class="col-xs-12">
                            {$form.Visit_label.html}
                        </div>
                    </div>
                    <div class="form-group col-sm-3">
                        <label class="col-xs-12">
                            {$form.Invalid.label}
                        </label>
                        <div class="col-xs-12">
                            {$form.Invalid.html}
                        </div>
                    </div>
                </div>
                <div class="row">
                    <div class="visible-xs col-xs-12"> </div>
                    <div class="visible-xs col-xs-12"> </div>
                    <div class="visible-xs col-xs-12"> </div>
                    <div class="visible-xs col-xs-12"> </div>
                    <div class="col-sm-3 col-sm-offset-6">
                        <input type="submit" name="filter" value="Show Data" class="btn btn-sm btn-primary col-xs-12" />
                    </div>
                    <div class="visible-xs col-xs-12"> </div>
                    <div class="visible-xs col-xs-12"> </div>
                    <div class="visible-xs col-xs-12"> </div>
                    <div class="visible-xs col-xs-12"> </div>
                    <div class="col-sm-3">
                        <input type="button" name="reset" value="Clear Form" class="btn btn-sm btn-primary col-xs-12" onclick="location.href='main.php?test_name=reliability&reset=true'" />
                    </div>
                </div>
            </form>
        </div>
    </div>
</div>
<div class="row">
{if $reliability_swap_candidates}
    <div class="col-sm-6">
        <div class="panel panel-primary">
            <div class="panel-heading" onclick="togglePanel('swap');">
                Swap Candidates
                <span class="glyphicon glyphicon-chevron-down pull-right" id="down-swap"></span>
                <span class="glyphicon glyphicon-chevron-up pull-right" style="display:none" id="up-swap"></span>
            </div>
            <div class="panel-body" style="display:none" id="panel-body-swap">
                <form method="post" action="main.php?test_name=reliability">
                    <input type="hidden" name="swap" value="swap"/>
                    <h5>Original Candidate</h5>
                    <div class="row">
                        <label class="col-sm-12 col-md-4">{$form.Cand1PSCID.label}</label>
                        <div class="col-sm-12 col-md-8">{$form.Cand1PSCID.html}</div>
                    </div>
                    <br>
                    <div class="row">
                        <label class="col-sm-12 col-md-4">{$form.Cand1Visit_label.label}</label>
                        <div class="col-sm-12 col-md-8">{$form.Cand1Visit_label.html}</div>
                    </div>
                    <h5>Replacement Candidate</h5>
                    <div class="row">
                        <label class="col-sm-12 col-md-4">{$form.Cand2PSCID.label}</label>
                        <div class="col-sm-12 col-md-8">{$form.Cand2PSCID.html}</div>
                    </div>
                    <br>
                    <div class="row">
                        <label class="col-sm-12 col-md-4">{$form.Cand2Visit_label.label}</label>
                        <div class="col-sm-12 col-md-8">{$form.Cand2Visit_label.html}</div>
                    </div>
                    <br>
                    <div class="row">
                        <label class="col-sm-12 col-md-4">{$form.SwapInstrument.label}</label>
                        <div class="col-sm-12 col-md-8">{$form.SwapInstrument.html}</div>
                    </div>
                    <br>
                    <div class="row">
                        <div class="visible-xs visible-sm col-xs-12"> </div>
                        <div class="visible-xs visible-sm col-xs-12"> </div>
                        <div class="visible-xs visible-sm col-xs-12"> </div>
                        <div class="visible-xs visible-sm col-xs-12"> </div>
                        <div class="col-md-6 col-xs-12 col-md-offset-6">
                            <input type="submit" name="swap" value="Swap Candidates" class="btn btn-sm btn-primary col-xs-12" />
                        </div>
                    </div>
                </form>
            </div>
        </div>   
    </div>
{/if}
{if $EARLI_Reliability}
    <div class="col-sm-6">
        <div class="panel panel-primary">
            <div class="panel-heading" onclick="togglePanel('earli');">
                Add EARLI Candidate
                <span class="glyphicon glyphicon-chevron-down pull-right" id="down-earli"></span>
                <span class="glyphicon glyphicon-chevron-up pull-right" style="display:none" id="up-earli"></span>
            </div>
            <div class="panel-body" style="display:none" id="panel-body-earli">
                <form method="post" action="main.php?test_name=reliability">
                    <div class="row">
                        <label class="col-sm-12 col-md-4">{$form.AddPSCID.label}</label>
                        <div class="col-sm-12 col-md-8">{$form.AddPSCID.html}</div>
                    </div>
                    <br>
                    <div class="row">
                        <label class="col-sm-12 col-md-4">{$form.AddVisit_label.label}</label>
                        <div class="col-sm-12 col-md-8">{$form.AddVisit_label.html}</div>
                    </div>
                    <br>
                    <div class="row">
                        <label class="col-sm-12 col-md-4">{$form.AddInstrument.label}</label>
                        <div class="col-sm-12 col-md-8">{$form.AddInstrument.html}</div>
                    </div>
                    <br>
                    <div class="row">
                        <label class="col-sm-12 col-md-4">{$form.AddReliabilityCenter.label}</label>
                        <div class="col-sm-12 col-md-8">{$form.AddReliabilityCenter.html}</div>
                    </div>
                    <br>
                    <div class="row">
                        <div class="visible-xs visible-sm col-xs-12"> </div>
                        <div class="visible-xs visible-sm col-xs-12"> </div>
                        <div class="visible-xs visible-sm col-xs-12"> </div>
                        <div class="visible-xs visible-sm col-xs-12"> </div>
                        <div class="col-md-6 col-xs-12 col-md-offset-6">
                            <input type="submit" name="swap" value="Add Candidate" class="btn btn-sm btn-primary col-xs-12" />
                        </div>
                    </div>
                </form>
            </div>
        </div>   
    </div>
{/if}
</div>

{if $IBIS_Access}
<a href='main.php?test_name=reliability_phase_one'>Phase 1 Reliability</a> |
<a href='main.php?test_name=reliability_diagnostic_calls'>Diagnostic Behavioural Call Cases</a> | 
<a href="main.php?test_name=reliability&EARLI=0">IBIS Reliability Candidates</a>
{/if}
{if $IBIS_Access and $EARLI_Reliability} | {/if}
{if $EARLI_Reliability}
<a href="main.php?test_name=reliability&EARLI=1">EARLI Reliability Candidates</a>
{/if}
<br>
<br>
<!-- <h2><font color="red">Note: Phase 2 reliability forms are unavailable at the moment as the system is being upgraded.</font></h2> -->

<!--  title table with pagination -->
<table border="0" valign="bottom" width="100%">
<tr>
    <!-- title -->
    <td class="controlPanelSection">List of Log Entries</td>

    <!-- display pagination links -->
    <td align="right">{$page_links}</td>
</tr>
</table>

<div class="table-responsive">
    <table border="0" width="100%" class ="table table-hover table-primary table-bordered">
        <thead>
            <tr class="info">
                <th nowrap="nowrap">No.</th>
                <!-- print out column headings - quick & dirty hack -->
                {section name=header loop=$headers}
                    <th nowrap="nowrap">
                      {if $headers[header].displayName != "Reliable"}
                        <a href="main.php?test_name=reliability&filter[order][field]={$headers[header].name}&filter[order][fieldOrder]={$headers[header].fieldOrder}">
                          {if $headers[header].displayName == "Reliability Center Id"}
                            Site of Reliability Test
                          {else}
                            {$headers[header].displayName}
                          {/if}
                        </a>
                      {else}
                        {$headers[header].displayName}
                      {/if}
                    </th>
                {/section}
            </tr>
        </thead>
        <tbody>
            {section name=item loop=$items}
                <tr>
                <!-- print out data rows -->
                {section name=piece loop=$items[item]}
                

                {if $items[item][piece].name == "PSCID"}
                   <td>
                   {if $items[item][piece].Current_stage == 'Recycling Bin'}
                    {$items[item][piece].value} <font color="red">(Recycling Bin)</font>
                 {elseif $items[item][piece].invalid == "yes"}
                    {$items[item][piece].value} <font color="red">(Invalid)</font>
                 {else}     
                      <a href="main.php?test_name={$items[item][piece].Instrument}_reliability&subtest={$items[item][piece].Instrument}_reliability&identifier={$items[item][piece].CommentID}&reliability_center_id={$items[item][piece].SiteID}">{$items[item][piece].value}</a> 
                   {/if}
                    {if $items[item][piece].manual == "yes"}
                        <font color="red">(Manual)</font>
                    {/if}
                  </td>
                {elseif  $items[item][piece].name == "Cohort"}
                      <td nowrap="nowrap">
                    {if $items[item][piece].value== "1"}
                                    6 month
                    {elseif $items[item][piece].value== "2"}
                                    12 month
                    {elseif $items[item][piece].value== "3"}
                                    Control
                        {/if}</td>
                {elseif  $items[item][piece].name == "Reliability"}
                  {if $items[item][piece].value== "Yes"}
                  <td nowrap="nowrap" style="background-color:#55FF55;">{$items[item][piece].value}</td>
                  {elseif $items[item][piece].value== "No"}
                  <td nowrap="nowrap" style="background-color:#FF2222;color:white">{$items[item][piece].value}</td>
                  {else}
                  <td nowrap="nowrap"></td>
                  {/if}
                  {else}
                     <td nowrap="nowrap">{$items[item][piece].value}</td>
                {/if}
               </td>
                {/section}
                </tr>           
            {sectionelse}
                <tr><td colspan="15">No reliability entries found</td></tr>
            {/section}
        </tbody>        
    <!-- end data table -->
    </table>
</div>

