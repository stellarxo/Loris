{if $success}

<p>Family added successful<br /></p>
<br />
{/if}

<form method="post" name="add_family" id="add_family" enctype="multipart/form-data">
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
            <label class="col-sm-2">{$form.SiblingID.label}</label>
            <div class="col-sm-4">
                {$form.SiblingID.html}
            </div>
        </div>
        <br>
        <div class="row">
            <label class="col-sm-2">{$form.relation_type.label}</label>
            <div class="col-sm-4">
                {$form.relation_type.html}
            </div>
        </div>
        <br>
        <input class="btn btn-sm btn-primary col-sm-offset-1" name="fire_away" value="Save" type="submit" />
        {/if}
        <input class="btn btn-sm btn-primary" onclick="location.href='main.php?test_name=candidate_parameters&candID={$candID}&identifier={$candID}'" value="Return to profile" type="button" />
    </div>
</div>