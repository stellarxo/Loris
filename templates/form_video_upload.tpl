{if $success}
<p>Update Successful<br /></p>
<a href='main.php?test_name=videos'> Back to Video Page</a>
<br>
{/if}

<br />
<form method="post" name="video_upload" id="video_upload" enctype="multipart/form-data">
    <h3>Upload a New Video</h3>
    <br><br>
    {if $form.errors.Instrument}
    <div class="row form-group form-inline form-inline has-error">
    {else}
    <div class="row form-group form-inline form-inline">
    {/if}
        <label class="col-sm-2">
            {$form.Instrument.label}
        </label>
        <div class="col-sm-10">
            {$form.Instrument.html}
        </div>
        {if $form.errors.Instrument}
            <div class="col-sm-offset-2 col-xs-12">
                <font class="form-error">{$form.errors.Instrument}</font>
            </div>
        {/if}
    </div>
    {if $form.errors.PSCID}
    <div class="row form-group form-inline form-inline has-error">
    {else}
    <div class="row form-group form-inline form-inline">
    {/if}
        <label class="col-sm-2">
            {$form.PSCID.label}
        </label>
        <div class="col-sm-10">
            {$form.PSCID.html}
        </div>
        {if $form.errors.PSCID}
            <div class="col-sm-offset-2 col-xs-12">
                <font class="form-error">{$form.errors.PSCID}</font>
            </div>
        {/if}
    </div>
    {if $form.errors.visitLabel}
    <div class="row form-group form-inline form-inline has-error">
    {else}
    <div class="row form-group form-inline form-inline">
    {/if}
        <label class="col-sm-2">
            {$form.visitLabel.label}
        </label>
        <div class="col-sm-10">
            {$form.visitLabel.html}
        </div>
        {if $form.errors.visitLabel}
            <div class="col-sm-offset-2 col-xs-12">
                <font class="form-error">{$form.errors.visitLabel}</font>
            </div>
        {/if}
    </div>
    {if $form.errors.Date_taken}
    <div class="row form-group form-inline form-inline has-error">
    {else}
    <div class="row form-group form-inline form-inline">
    {/if}
        <label class="col-sm-2">
            {$form.Date_taken.label}
        </label>
        <div class="col-sm-10">
            {$form.Date_taken.html}
        </div>
        {if $form.errors.Date_taken}
            <div class="col-sm-offset-2 col-xs-12">
                <font class="form-error">{$form.errors.Date_taken}</font>
            </div>
        {/if}
    </div>
    {if $form.errors.For_site}
    <div class="row form-group form-inline form-inline has-error">
    {else}
    <div class="row form-group form-inline form-inline">
    {/if}
        <label class="col-sm-2">
            {$form.For_site.label}
        </label>
        <div class="col-sm-10">
            {$form.For_site.html}
        </div>
        {if $form.errors.For_site}
            <div class="col-sm-offset-2 col-xs-12">
                <font class="form-error">{$form.errors.For_site}</font>
            </div>
        {/if}
    </div>
    {if $form.errors.multipart}
    <div class="row form-group form-inline form-inline has-error">
    {else}
    <div class="row form-group form-inline form-inline">
    {/if}
        <label class="col-sm-2">
            {$form.multipart.label}
        </label>
        <div class="col-sm-10">
            {$form.multipart.html}
        </div>
        {if $form.errors.multipart}
            <div class="col-sm-offset-2 col-xs-12">
                <font class="form-error">{$form.errors.multipart}</font>
            </div>
        {/if}
    </div>
    {if $form.errors.EARLI}
    <div class="row form-group form-inline form-inline has-error">
    {else}
    <div class="row form-group form-inline form-inline">
    {/if}
        <label class="col-sm-2">
            {$form.EARLI.label}
        </label>
        <div class="col-sm-10">
            {$form.EARLI.html}
        </div>
        {if $form.errors.EARLI}
            <div class="col-sm-offset-2 col-xs-12">
                <font class="form-error">{$form.errors.EARLI}</font>
            </div>
        {/if}
    </div>
    {if $form.errors.comments}
    <div class="row form-group form-inline form-inline has-error">
    {else}
    <div class="row form-group form-inline form-inline">
    {/if}
        <label class="col-sm-2">
            {$form.comments.label}
        </label>
        <div class="col-sm-10">
            {$form.comments.html}
        </div>
        {if $form.errors.comments}
            <div class="col-sm-offset-2 col-xs-12">
                <font class="form-error">{$form.errors.comments}</font>
            </div>
        {/if}
    </div>
    {if $form.video_file}
        {if $form.errors.video_file}
        <div class="row form-group form-inline form-inline has-error">
        {else}
        <div class="row form-group form-inline form-inline">
        {/if}
            <label class="col-sm-2">
                {$form.video_file.label}
            </label>
            <div class="col-sm-10">
                {$form.video_file.html}
            </div>
            {if $form.errors.video_file}
                <div class="col-sm-offset-2 col-xs-12">
                    <font class="form-error">{$form.errors.video_file}</font>
                </div>
            {/if}
        </div>
        <div class="row form-group form-inline">
            <label class="col-sm-2">
                NOTE:
            </label>
            <div class="col-sm-10">
                <B>file name should begin with &lt;PSCID id&gt;_&lt;visit label&gt;_&lt;instrument&gt;...<br>
                 For example, for candidate dcc0000, visit v12 for ADOS module 1, <br>
                 the file name should be prefixed by:
                 dcc0000_v12_ados_module1</B>
        </div>
    </div>
    {else}
        {if $form.errors.File_name}
        <div class="row form-group form-inline form-inline has-error">
        {else}
        <div class="row form-group form-inline form-inline">
        {/if}
            <label class="col-sm-2">
                {$form.File_name.label}
            </label>
            <div class="col-sm-10">
                {$form.File_name.html}
            </div>
            {if $form.errors.File_name}
                <div class="col-sm-offset-2 col-xs-12">
                    <font class="form-error">{$form.errors.File_name}</font>
                </div>
            {/if}
        </div>
        {if $form.errors.hide_video}
        <div class="row form-group form-inline form-inline has-error">
        {else}
        <div class="row form-group form-inline form-inline">
        {/if}
            <label class="col-sm-2">
                {$form.hide_video.label} (check both to confirm)
            </label>
            <div class="col-sm-10">
                {$form.hide_video.html} {$form.hide_video_confirm.html} 
            </div>
            {if $form.errors.hide_video}
                <div class="col-sm-offset-2 col-xs-12">
                    <font class="form-error">{$form.errors.hide_video}</font>
                </div>
            {/if}
        </div>
    {/if}
    {if empty($success)}
        <div class="row form-group form-inline">
            <div class="col-sm-2"><input class="btn btn-sm btn-primary col-xs-12" name="fire_away" value="Upload" type="submit" /></div>
        </div>
    {/if}
    {$form.hidden}
</form>

