{* This is a hack. It should be in a separate javascript library file *}
{* Used to make the swap candidate table expand/collapse onclick *}
{literal}

<script language="javascript" type="text/javascript">
$(document).ready(function() {
    function _swapWrapper() {
        return toggleTable('swapcandidates');
    }
    function _addWrapper() {
        return toggleTable('addcandidate');
    }
    function toggleTable(table) {
        if(table) {
            t = $('table#' + table);
            body = t.children('tbody');
            body.toggle();
            if(body.css("display") == 'none') {
                t.css("border", "none");
            } else {
                t.css("border", "2px solid #08245B");
            }
        }
    }

    $('table#swapcandidates th').click(_swapWrapper);
    $('table#addcandidate th').click(_addWrapper);
    // Hide the tab by default
    toggleTable('swapcandidates');
    toggleTable('addcandidate');
});
function togglePanel(panel) {
    "use strict";
    $("#panel-body-" + panel).toggle();
    $("#down-" + panel).toggle();
    $("#up-" + panel).toggle();
}
</script>
{/literal}
<script type="text/javascript" src="js/filterControl.js"></script>
<div class="col-sm-12">
    <div class="panel panel-primary">
        <div class="panel-heading" onclick="hideFilter();">
            Selection Filter
            <span class="glyphicon glyphicon-chevron-down pull-right" style="display:none" id="down"></span>
            <span class="glyphicon glyphicon-chevron-up pull-right" id="up"></span>
        </div>
        <div class="panel-body" id="panel-body">
            <form method="post" action="main.php?test_name=blind_coding">
                {if $form.error}
                    <div class="error">{$form.error.label}</div>
                {/if}
                {if $form.message}
                    <div class="error">{$form.message.label}</div>
                {/if}
                <div class="row">
                    <div class="form-group col-sm-4">
                        <label class="col-xs-12 col-md-4">
                            Subproject:
                        </label>
                        <div class="col-xs-12 col-md-8">
                            {$form.CommentID.html}
                        </div>
                    </div>
                    <div class="form-group col-sm-2">
                        <label class="col-xs-12 col-md-5">
                            {$form.CenterID.label}
                        </label>
                        <div class="col-xs-12 col-md-7">
                            {$form.CenterID.html}
                        </div>
                    </div>
                    <div class="form-group col-sm-3">
                        <label class="col-xs-12 col-md-5">
                            {$form.Instrument.label}
                        </label>
                        <div class="col-xs-12 col-md-7">
                            {$form.Instrument.html}
                        </div>
                    </div>
                    <div class="form-group col-sm-3">
                        <label class="col-xs-12 col-md-5">
                            {$form.CodingCenterID.label}
                        </label>
                        <div class="col-xs-12 col-md-7">
                            {$form.CodingCenterID.html}
                        </div>
                    </div>
                </div>
                <div class="row">
                    <div class="form-group col-sm-2">
                        <label class="col-xs-12 col-md-5">
                            DCCID:
                        </label>
                        <div class="col-xs-12 col-md-7">
                            {$form.DCCID.html}
                        </div>
                    </div>
                    <div class="form-group col-sm-2">
                        <label class="col-xs-12 col-md-5">
                            PSCID:
                        </label>
                        <div class="col-xs-12 col-md-7">
                            {$form.PSCID.html}
                        </div>
                    </div>
                    <div class="form-group col-sm-2">
                        <label class="col-xs-12 col-md-5">
                            Gender:
                        </label>
                        <div class="col-xs-12 col-md-7">
                            {$form.Gender.html}
                        </div>
                    </div>
                    <div class="form-group col-sm-3">
                        <label class="col-xs-12 col-md-5">
                            Visit label:
                        </label>
                        <div class="col-xs-12 col-md-7">
                            {$form.Visit_label.html}
                        </div>
                    </div>
                    <div class="form-group col-sm-3">
                        <label class="col-xs-12 col-md-5">
                            {$form.Invalid.label}
                        </label>
                        <div class="col-xs-12 col-md-7">
                            {$form.Invalid.html}
                        </div>
                    </div>
                </div>
                <div class="row">
                    <div class="form-group col-xs-12">
                    <label class="col-sm-6">Actions:</label>
                        <div class="col-sm-3">
                            <input type="submit" name="filter" value="Show Data" class="btn btn-sm btn-primary col-xs-12" />
                        </div>
                        <div class="visible-xs col-xs-12"> </div>
                        <div class="visible-xs col-xs-12"> </div>
                        <div class="visible-xs col-xs-12"> </div>
                        <div class="visible-xs col-xs-12"> </div>
                        <div class="col-sm-3">
                            <input type="button" name="reset" value="Clear Form" class="btn btn-sm btn-primary col-xs-12" onclick="location.href='main.php?test_name=blind_coding&reset=true'" />
                        </div>
                    </div>    
                </div>
            </form>
        </div>
    </div>

</div>

{if $blind_swap_candidates}
<div class="col-sm-6">
    <div class="panel panel-primary">
        <div class="panel-heading" onclick="togglePanel('swap');">
            Swap Candidate
            <span class="glyphicon glyphicon-chevron-down pull-right" id="down-swap"></span>
            <span class="glyphicon glyphicon-chevron-up pull-right" style="display:none" id="up-swap"></span>
        </div>
        <div class="panel-body" id="panel-body-swap" style="display:none">
            <form method="post" action="main.php?test_name=blind_coding">
                <h5>Original Candidate</h5>
                <div class="row">
                    <div class="form-group col-sm-6">
                        <label class="col-md-4">{$form.Cand1PSCID.label}</label>
                        <div class="col-md-8">{$form.Cand1PSCID.html}</div>
                    </div>
                    <div class="form-group col-sm-6">
                        <label class="col-md-4">{$form.Cand1Visit_label.label}</label>
                        <div class="col-md-8">{$form.Cand1Visit_label.html}</div>
                    </div>
                </div>
                <h5>Replacement Candidate</h5>
                <div class="row">
                    <div class="form-group col-sm-6">
                        <label class="col-md-4">{$form.Cand2PSCID.label}</label>
                        <div class="col-md-8">{$form.Cand2PSCID.html}</div>
                    </div>
                    <div class="form-group col-sm-6">
                        <label class="col-md-4">{$form.Cand2Visit_label.label}</label>
                        <div class="col-md-8">{$form.Cand2Visit_label.html}</div>
                    </div>
                </div>
                <div class="row">
                    <div class="form-group col-sm-12">
                        <label class="col-sm-12 col-md-4">{$form.SwapInstrument.label}</label>
                        <div class="col-sm-12 col-md-8">{$form.SwapInstrument.html}</div>
                    </div>
                </div>
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
{if $blind_add_candidates}
<div class="col-sm-6">
    <div class="panel panel-primary">
        <div class="panel-heading" onclick="togglePanel('add');">
            Add Candidate
            <span class="glyphicon glyphicon-chevron-down pull-right" id="down-add"></span>
            <span class="glyphicon glyphicon-chevron-up pull-right" style="display:none" id="up-add"></span>
        </div>
        <div class="panel-body" id="panel-body-add" style="display:none">
            <form method="post" action="main.php?test_name=blind_coding">
                <div class="row">
                    <div class="form-group col-sm-6">
                        <label class="col-md-6">{$form.AddPSCID.label}</label>
                        <div class="col-md-6">{$form.AddPSCID.html}</div>
                    </div>
                    <div class="form-group col-sm-6">
                        <label class="col-md-6">{$form.AddVisit_label.label}</label>
                        <div class="col-md-6">{$form.AddVisit_label.html}</div>
                    </div>
                </div>
                <div class="row">
                    <div class="form-group col-sm-6">
                        <label class="col-md-6">{$form.AddInstrument.label}</label>
                        <div class="col-md-6">{$form.AddInstrument.html}</div>
                    </div>
                    <div class="form-group col-sm-6">
                        <label class="col-md-6">{$form.AddBlindCenter.label}</label>
                        <div class="col-md-6">{$form.AddBlindCenter.html}</div>
                    </div>
                </div>
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

<!--  title table with pagination -->
<table border="0" valign="bottom" width="100%">
<tr>
    <!-- title -->
    <td class="controlPanelSection">List of Blind Coded Entries</td>

    <!-- display pagination links -->
    <td align="right">{$page_links}</td>
</tr>
</table>

<div class="table-responsive">  
  <!-- start data table -->
    <table border="0" width="100%" class="table table-hover table-primary table-bordered">
        <thead>
            <tr class="info">
                <th>No.</th>
                    <!-- print out column headings - quick & dirty hack -->
                    {section name=header loop=$headers}
                        <th>
                          {if $headers[header].displayName != "Reliable"}
                            <a href="main.php?test_name=blind_coding&filter[order][field]={$headers[header].name}&filter[order][fieldOrder]={$headers[header].fieldOrder}">
                              {if $headers[header].displayName == "CodingCenterID"}
                                Site of Blind Coding Test
                              {else}
                                {$headers[header].displayName}
                              {/if}
                            </a>
                          {else}
                            {$headers[header].displayName}
                          {/if}
                    {/section}
                </th>
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
                      <a href="main.php?test_name={$items[item][piece].Instrument}_reliability&subtest={$items[item][piece].Instrument}_reliability&identifier={$items[item][piece].CommentID}&reliability_center_id={$items[item][piece].SiteID}&blind=1">{$items[item][piece].value}</a> 
                   {/if}
                    {if $items[item][piece].manual == "yes"}
                        <font color="red">(Manual)</font>
                    {/if}
                  </td>
                {elseif  $items[item][piece].name == "Cohort"}
                      <td>
                    {if $items[item][piece].value== "1"}
                                    6 month
                    {elseif $items[item][piece].value== "2"}
                                    12 month
                    {elseif $items[item][piece].value== "3"}
                                    Control
                        {/if}</td>
                {elseif  $items[item][piece].name == "Reliable"}
                  {if $items[item][piece].value== "Yes"}
                  <td style="background-color:#55FF55;">{$items[item][piece].value}</td>
                  {elseif $items[item][piece].value== "No"}
                  <td style="background-color:#FF2222;color:white">{$items[item][piece].value}</td>
                  {else}
                  <td></td>
                  {/if}
                  {else}
                     <td>{$items[item][piece].value}</td>
                {/if}
               </td>
                {/section}
                </tr>           
            {sectionelse}
                <tr><td colspan="15">No blind coding entries found</td></tr>
            {/section}
        </tbody>                   
    <!-- end data table -->
    </table>
</div>

