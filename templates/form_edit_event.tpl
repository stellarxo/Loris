<script src="js/filterControl.js" type="text/javascript"></script>

<div class="col-md-12 col-sm-10">
	<form method="post" name="edit_user" id="edit_user">
		<div class="panel panel-primary">
            <div class="panel-heading" onclick="hideFilter();">
                Edit Certification Event
                <span class="glyphicon glyphicon-chevron-down pull-right" style="display:none" id="down"></span>
                <span class="glyphicon glyphicon-chevron-up pull-right" id="up"></span>
            </div>
            <div class="panel-body" id="panel-body">
            	{foreach from=$form.errors item=error}
				    <div class="col-xs-12">
				        <p class="error">{$error}</p>
				    </div>
			    {/foreach}
			    <div class="row">
			    	<div class="form-group col-sm-12">
						<label class="col-xs-12 col-md-1 col-sm-2">{$form.examinerID.label}</label>
						<div class="col-xs-12 col-md-4 col-sm-8">{$form.examinerID.html}</div>
					</div>
				</div>
				{foreach from=$form.pass item=item key=key}
					<div class="row">
						<div class="form-group col-sm-6 col-md-4">
							<label class="col-sm-2">{$form.pass[$key].label}</label>
							<div class="col-sm-10">{$form.pass[$key].html}</div>
						</div>
						<div class="form-group col-sm-6 col-md-4">
							<label class="col-sm-2">{$form.date_cert[$key].label}</label>
							<div class="col-sm-10">{$form.date_cert[$key].html}</div>
						</div>
						<div class="form-group col-sm-6 col-md-4">
							<label class="col-sm-4">{$form.comment[$key].label}</label>
							<div class="col-sm-6">{$form.comment[$key].html}</div>
						</div>
					</div>
					<br>
				{/foreach}
				<div class="row">
				    {if not $success}
				    	<div class="form-group col-xs-12">
				    		<div class="visible-xs visible-sm col-xs-12"> </div>
	                        <div class="visible-xs visible-sm col-xs-12"> </div>
	                        <div class="visible-xs visible-sm col-xs-12"> </div>
	                        <div class="visible-xs visible-sm col-xs-12"> </div>
				    		<div class="col-sm-6 col-md-3 col-xs-12 col-md-offset-5">
					        	<input class="btn btn-sm btn-primary col-xs-12" name="fire_away" value="Save" type="submit" />
					        </div>
					        <div class="visible-xs col-xs-12"> </div>
	                        <div class="visible-xs col-xs-12"> </div>
	                        <div class="visible-xs col-xs-12"> </div>
	                        <div class="visible-xs col-xs-12"> </div>
					        <div class="col-sm-6 col-md-3 col-xs-12">
					        	<input class="btn btn-sm btn-primary col-xs-12" value="Reset" type="reset" />
					        </div>
					    </div>
				    {/if}
				</div>
				{$form.hidden}
            </div>
        </div>
    </form>
</div>
<div class="col-xs-12">
	<h1>Change Log</h1>
</div>
<div class="table-responsive">
	<table class="table table-hover table-primary table-bordered">
		<tr class="info">
			<th>Time</th>
			<th>User</th>
			<th>Measure</th>
			<th>Visit</th>
			<th>Old Value</th>
			<th>Old Date</th>
			<th>New Value</th>
			<th>New Date</th>
		</tr>
		{$form.certification_history.html}
	</table>
</div>