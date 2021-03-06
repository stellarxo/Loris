<script src="{$baseurl}/js/filterControl.js" type="text/javascript"></script>

<div class="col-sm-12">
    <div class="col-md-8 col-sm-8">
        <form method="post" action="{$baseurl}/conflict_resolver/">
            <div class="panel panel-primary">
                <div class="panel-heading" onclick="hideFilter();">
                    Selection Filter
                    <span class="glyphicon glyphicon-chevron-down pull-right" style="display:none" id="down"></span>
                    <span class="glyphicon glyphicon-chevron-up pull-right" id="up"></span>
                </div>
                <div class="panel-body" id="panel-body">
                    <div class="row">
                        <div class="form-group col-sm-12">
                            <label class="col-sm-12 col-md-2">{$form.Instrument.label}</label>
                            <div class="col-sm-12 col-md-9">{$form.Instrument.html}</div>
                        </div>
                    </div>
                    <div class="row">
                        <div class="form-group col-sm-12">
                            <label class="col-sm-12 col-md-2">{$form.CandID.label}</label>
                            <div class="col-sm-12 col-md-4">{$form.CandID.html}</div>
                            <label class="col-sm-12 col-md-1">{$form.site.label}</label>
                            <div class="col-sm-12 col-md-4">{$form.site.html}</div>
                        </div>
                    </div>
                    <div class="row">
                        <div class="form-group col-sm-12">
                            <label class="col-sm-12 col-md-2">{$form.PSCID.label}</label>
                            <div class="col-sm-12 col-md-4">{$form.PSCID.html}</div>
                            <label class="col-sm-12 col-md-1">{$form.Project.label}</label>
                            <div class="col-sm-12 col-md-4">{$form.Project.html}</div>
                        </div>
                    </div>
                    <div class="row">
                        <div class="form-group col-sm-12">
                            <label class="col-sm-12 col-md-2">{$form.Question.label}</label>
                            <div class="col-sm-12 col-md-4">{$form.Question.html}</div>
                            <label class="col-sm-12 col-md-1">{$form.visit.label}</label>
                            <div class="col-sm-12 col-md-4">{$form.visit.html}</div>
                        </div>
                    </div>
                    <div class="row">
                        <div class="form-group col-sm-6 col-sm-offset-6 hidden-sm">
                            <div class="col-sm-5 col-xs-12">
                                <input type="submit" name="filter" value="Show Data" class="btn btn-sm btn-primary col-xs-12"/>
                            </div>
                            <div class="visible-xs col-xs-12"> </div>
                            <div class="visible-xs col-xs-12"> </div>
                            <div class="visible-xs col-xs-12"> </div>
                            <div class="visible-xs col-xs-12"> </div>

                            <div class="col-sm-5 col-xs-12">
                                <input type="button" name="reset" value="Clear Form" class="btn btn-sm btn-primary col-xs-12" onclick="location.href='{$baseurl}/conflict_resolver/?reset=true'">
                            </div>
                        </div>
                    </div>
                    <div class="row visible-sm">
                        <div class="col-sm-6">
                            <input type="submit" name="filter" value="Show Data" class="btn btn-sm btn-primary col-xs-12"/>
                        </div>
                        <div class="col-sm-6 col-xs-12">
                            <input type="button" name="reset" value="Clear Form" class="btn btn-sm btn-primary col-xs-12" onclick="location.href='{$baseurl}/conflict_resolver/?reset=true'">
                        </div>
                    </div>
                    <input type="hidden" name="test_name" value="conflict_resolver" />
                </div>
            </div>
        </form>
    </div>
</div>

<div id="tabs" style="background: white">
    <ul class="nav nav-tabs ">
        <li class="active"><a id="onLoad">Unresolved Conflicts</a></li>
        <li><a href="{$baseurl}/conflict_resolver/?submenu=resolved_conflicts">Resolved Conflicts</a></li>
    </ul>
    <div class="tab-content">
        <div class="tab-pane active">
            <!--  title table with pagination -->
            <table id="LogEntries" border="0" valign="bottom" width="100%">
                <tr>
                    <!-- display pagination links -->
                    <td align="right" id="pageLinks"></td>
                </tr>
            </table>
            <form method="post" action="{$baseurl}/conflict_resolver/" name="conflict_resolver" id="conflict_resolver">
                <table class="table table-hover table-primary table-bordered table-unresolved-conflicts dynamictable" border="0">
                    <thead>

                    {foreach from=$form.errors item=error}
                        <tr>
                            <td nowrap="nowrap" colspan="6" class="error">{$error}</td>
                        </tr>
                    {/foreach}

                    <tr class="info">
                        <th>No.</th>
                        {section name=header loop=$headers}
                            <th><a href="{$baseurl}/conflict_resolver/?filter[order][field]={$headers[header].name}&filter[order][fieldOrder]={$headers[header].fieldOrder}">
                                    {if $headers[header].displayName == "TableName"}
                                        Instrument
                                    {else if $headers[header].displayName == "CandID"}
                                        DCCID
                                    {else if $headers[header].displayName == "ProjectID"}
                                        Project
                                    {else if $headers[header].displayName == "FieldName"}
                                        Question
                                    {else}
                                        {$headers[header].displayName}
                                    {/if}
                                </a></th>
                        {/section}
                        <th>Correct Answer</th>
                    </tr>
                    </thead>
                    <tbody>
                    {section name=item loop=$items}
                    <tr>
                        {section name=piece loop=$items[item]}
                            {if $items[item][piece].name != "hash"}
                                <td>
                                    {$items[item][piece].value}
                                </td>
                            {else}
                                <td nowrap="nowrap" align="right">
                                    {$form[$items[item][piece].value].html}
                                </td>
                            {/if}
                        {/section}
                    </tr>
                    {sectionelse}
                        <tr>
                            {if $useProjects == 'true'}
                                <tr><td colspan="8">No unresolved conflicts found.</td></tr>
                            {else}
                                <tr><td colspan="7">No unresolved conflicts found.</td></tr>
                            {/if}
                        </tr>
                    {/section}
                    <tr>
                        {if $useProjects == 'true'}
                            <td nowrap="nowrap" colspan="7" id="message-area"></td>
                        {else}
                            <td nowrap="nowrap" colspan="6" id="message-area"></td>
                        {/if}

                        <td nowrap="nowrap">
                            <input class="btn btn-sm btn-primary col-md-offset-3" name="fire_away" value="Save" type="submit" />
                            <input class="btn btn-sm btn-primary" value="Reset" type="reset" />
                        </td>
                    </tr>
                    </tbody>
                </table>
            </form>
        </div>
    </div>
</div>
</div>
<script>
var pageLinks = RPaginationLinks(
{
    RowsPerPage : {$rowsPerPage},
    Total: {$TotalItems},
    onChangePage: function(pageNum) {
        location.href="{$baseurl}/conflict_resolver/?pageID=" + pageNum
    },
    Active: {$pageID}
});
React.render(pageLinks, document.getElementById("pageLinks"));
</script>

