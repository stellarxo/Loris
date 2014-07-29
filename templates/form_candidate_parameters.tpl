<form method="post" name="candidate_parameters" id="candidate_parameters">
<input class="btn btn-sm btn-primary" onclick="location.href='main.php?test_name=timepoint_list&candID={$candID}'" value="Return to timepoint list" type="button" />
<br><br>
<div class="panel panel-primary">
    <div class="panel-heading">
        Candidate Information
    </div>
    <div class="panel-body">
        {foreach from=$form.errors item=error}
            <font class="error">{$error}</font>
        {/foreach}
        {if $form.dob_error}
            <font class="error">{$form.dob_error.label}</font>
        {/if}
        <div class="row">
            <label class="col-sm-2">{$form.pscid.label}</label>
            <div class="col-sm-10" id="pscid">
                {$pscid}
            </div>
        </div>
        {foreach from=$params_list item=value key=name}
            <div class="row">
                <label class="col-sm-2">{$form.$name.label}</label>
                <div class="col-sm-10">
                    {$value}
                </div>
            </div>
        {/foreach}
        <br>
        <input class="btn btn-sm btn-primary col-sm-offset-2" onclick="location.href='main.php?test_name=candidate_parameters&subtest=update_candidate_info&candID={$candID}&identifier={$candID}'" value="Update Candidate Info" type="button" />
    </div>
    <div class="panel-heading">
        Proband Information
    </div>
    <div class="panel-body">
        {foreach from=$proband_info item=value key=name}
            <div class="row">
                <label class="col-sm-2">{$form.$name.label}</label>
                <div class="col-sm-10">
                    {$value}
                </div>
            </div>
        {/foreach}
        <div class="row">
            <label class="col-md-2">{$form.dob_proband_adi_r.label}</label>
            <div class="col-md-10">
                {$form.dob_proband_adi_r.html}
            </div>
        </div>
        <div class="row">
            <label class="col-md-2">{$form.dob_proband_vineland.label}</label>
            <div class="col-md-10">
                {$form.dob_proband_vineland.html}
            </div>
        </div>
        <div class="row">
            <label class="col-md-2">{$form.Age_Difference.label}</label>
            <div class="col-md-10">
                {$form.Age_Difference.html}
            </div>
        </div>
        <br>
        <input class="btn btn-sm btn-primary col-sm-offset-2" onclick="location.href='main.php?test_name=candidate_parameters&subtest=update_proband_info&candID={$candID}&identifier={$candID}'" value="Update Proband Info" type="button" />
    </div>
    <div class="panel-heading">
        Family Information
    </div>
    <div class="panel-body">
        {foreach from=$sibling_list item=sibling key=keyid}
            <div class="row">
                <label class="col-sm-2">{$form.SiblingcID.label}</label>
                <div class="col-sm-10">
                    {$sibling.CandID}
                </div>
            </div>
        {/foreach}
        <div class="row">
            <label class="col-sm-2">{$form.relation_type.label}</label>
            <div class="col-sm-10">
                {$sibling.Relationship_type}
            </div>
        </div>
        <br>
        <input class="btn btn-sm btn-primary col-sm-offset-2" colspan="2" onclick="location.href='main.php?test_name=candidate_parameters&subtest=add_family&candID={$candID}&identifier={$candID}'" value="Add Sibling" type="button" />
    </div>
    <div class="panel-heading">
        Participant Status
    </div>
    <div class="table-responsive">
    <table class="table">
        <thead>
            <tr>
                <td><b>Status</b></td>
                <td><b>Data Entry Staff</b></td>
                <td><b>Date Updated</b></td>
                <td><b>Comments</b></td>
            </tr>
        </thead>
        <tbody>
            {foreach from=$history_list item=row}
                <tr>
                    {foreach from=$row item=value key=name}
                        <td>{$value}</td>
                    {/foreach}
                </tr>
            {/foreach}
        </tbody>
        
    </table>
    </div>
    <div class="panel-body">
        <input class="btn btn-sm btn-primary col-sm-offset-2" onclick="location.href='main.php?test_name=candidate_parameters&subtest=update_participant_status&candID={$candID}&identifier={$candID}'" value="Update Participant Status" type="button" />
    </div>
    {if $display_consent}
        <div class="panel-heading">
            Participation Consent Status
        </div>
        <div class="table-responsive">
        <table class="table">
            <tr>
                <td><b>Consent to Study</b></td>
                <td><b>Date of Consent to Study</b></td>
                <td><b>Date of withdrawal of <br>Consent to Study</b></td>
                <td><b>Data Entry Staff</b></td>
                <td><b>Date Updated</b></td>
            </tr>
            {foreach from=$ndar_consent_history item=row}
                <tr>
                    {foreach from=$row item=value key=name}
                        <td>{$value}</td>
                    {/foreach}
                </tr>
            {/foreach}
            <tr>
                <td><b>NDAR Consent</b> </td>
                <td><b>Date of NDAR Consent</b></td>
                <td><b>Date of withdrawal of<br> NDAR Consent</b></td>
                <td><b>Data Entry Staff</b></td>
                <td><b>Date Updated</b></td>
            </tr>
            {foreach from=$ndar_consent_history item=row}
                <tr>
                    {foreach from=$row item=value key=name}
                        <td>{$value}</td>
                    {/foreach}
                </tr>
            {/foreach}
        </table>
        </div>
        <div class="panel-body">
            {if $form.$row.error}
                <span class="error">{$form.$row.error}</span>
            {/if}
            <input class="btn btn-sm btn-primary col-sm-offset-2" onclick="location.href='main.php?test_name=candidate_parameters&subtest=update_consent_info&candID={$candID}&identifier={$candID}'" value="Update Consent Info" type="button" />
        </div>
    {/if}
</div>

{$form.hidden}
</form>