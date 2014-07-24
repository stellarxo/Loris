{if $success}

<p>Consent Information was updated successful<br /></p>
<br />
{/if}
<form method="post" name="update_consent_info" id="update_consent_info" enctype="multipart/form-data">
{if not $success}
<div class="panel panel-primary">
    <div class="panel-heading">
        Update Consent Information
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
        {if $consent}
			{section name=question loop=$consent}
				{* 
					$consent[question] contains a list of element
			        names in the form that are related to that question.
			        We need to iterate through them to add them to the
			        HTML. 
			    *}
				{foreach from=$consent[question] item=row}
					<div class="row">
			            <label class="col-sm-4">{$form.$row.label}</label>
			            <div class="col-sm-4">
			                {$form.$row.html}
			            </div>
			        </div>
			        {if $form.$row.error}
			        	<div class="row">
						<span class="error col-sm-offset-4">{$form.$row.error}</span>
					{/if}
                    <br>
				{/foreach}
			{/section}
		{/if}
		<input class="btn btn-sm btn-primary col-sm-offset-3" name="fire_away" value="Save" type="submit" />
        {/if}
        <input class="btn btn-sm btn-primary" onclick="location.href='main.php?test_name=candidate_parameters&candID={$candID}&identifier={$candID}'" value="Return to profile" type="button" />
    </div>
</div>
