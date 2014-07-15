{if $success}

<p>Candidate Information was updated successful<br /></p>
<br />
{/if}
<form method="post" name="update_candidate_info" id="update_candidate_info" enctype="multipart/form-data">
{if not $success}
<div class="panel panel-primary">
    <div class="panel-heading">
        Update Candidate Information
    </div>
    <div class="panel-body">
        {foreach from=$form.errors item=error}
            <font class="error">{$error}</font>
        {/foreach}
        <div class="row">
            <label class="col-sm-2">PSCID:</label>
            <div class="col-sm-4">
                {$pscid}
            </div>
        </div>
        <br>
        <div class="row">
            <label class="col-sm-2">DCCID:</label>
            <div class="col-sm-4">
                {$candID}
            </div>
        </div>
        <br>
        <div class="row">
            <label class="col-sm-4">{$form.CandidateGUID.label}</label>
            <div class="col-sm-4">
                {$form.CandidateGUID.html}
            </div>
        </div>
        <br>
        <div class="row">
            <label class="col-sm-4">{$form.flagged_caveatemptor.label}</label>
            <div class="col-sm-4">
                {$form.flagged_caveatemptor.html}
            </div>
        </div>
        <br>
        <div class="row">
            <label class="col-sm-4">{$form.flagged_reason.label}</label>
            <div class="col-sm-4">
                {$form.flagged_reason.html}
            </div>
        </div>
        <br>
        <div class="row">
            <label class="col-sm-4">{$form.flagged_other_group.label}</label>
            <div class="col-sm-8 form-inline">
                {$form.flagged_other_group.html}
            </div>
        </div>
        <br>
        {foreach from=$elements_list item=element}
            <div class="row">
                <label class="col-sm-4">{$form.$element.label}</label>
                <div class="col-sm-4">
                    {$form.$element.html}
                </div>
            </div>
            <div class="col-xs-12"></div>
            <div class="col-xs-12"></div>
            <div class="col-xs-12"></div>
            <br>
        {/foreach}
        <input class="btn btn-sm btn-primary col-sm-offset-3" name="fire_away" value="Save" type="submit" />
        {/if}
        <input class="btn btn-sm btn-primary" onclick="location.href='main.php?test_name=candidate_parameters&candID={$candID}&identifier={$candID}'" value="Return to profile" type="button" />
    </div>
</div>