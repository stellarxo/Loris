<script type="text/javascript" src="js/instrument_form_control.js"></script>
<style type="text/css">
	.table-instrument>tbody>tr>th{
		color: black;
	}
	.table-instrument>tbody>tr>th, .table-instrument>tbody>tr>td  { 
	     border-top: none; 
	 }
</style>
<form {$form.attributes}>
	{$form.hidden}
	{$form.errors.mainError}
	{assign var="inTable" value="FALSE"}
	{foreach from=$form.elements item=element}
		{if $element.name neq mainError}
			{if $element.name eq lorisSubHeader}
				<div class="col-xs-12">
					{$element.label}
				</div>
				<br><br><br><br>
			{else if $element.label eq "table"}
				{if $inTable eq "FALSE"}
					{assign var="inTable" value="TRUE"}
					<table class="table table-instrument">
						<tr>
							{foreach key=gkey item=gitem from=$element.elements}
								<th>{$gitem.html}</th>
							{/foreach}
						</tr>
				{else}
					<tr>
						{foreach key=gkey item=gitem from=$element.elements}
							{if $gitem.name eq "strong"}
								<td><strong>{$gitem.html}</strong></td>
							{else}
								<td class="element">{$gitem.html}</td>
							{/if}
						{/foreach}
					</tr>
				{/if}
			{else}
				{if $inTable eq "TRUE"}
					{assign var="inTable" value="FALSE"}
					</table>
				{/if}
				{if $element.error}
		    	<div class="row form-group form-inline has-error">
		        {else}
		        <div class="row form-group form-inline">
		        {/if}
					<lable class="lab col-sm-4 col-xs-12">
						{if $element.required}
							<span style="color: #ff0000">*</span>
						{/if}
						{$element.label}  
					</lable>
					<div class="col-sm-8">
						<div class="col-xs-12 element">
							{if $element.type eq "group"}
								{foreach key=gkey item=gitem from=$element.elements}
									{$gitem.html}
								{/foreach}
							{else}
								{$element.html}
							{/if}
						</div>
						{if $element.error}
							<div class="col-xs-12">
			                    <font class="form-error">{$element.error}</font>
			                </div>
						{/if}
					</div>
				</div>
			{/if}
		{/if}
	{/foreach}
	{foreach from=$form.sections item=section}
		<h5>{$section.header}</h5>
		{foreach from=$section.elements item=element}
			{if $element.name neq mainError}
				{if $element.name eq lorisSubHeader}
					<div class="col-xs-12">
						{$element.label}
					</div>
					<br><br><br><br>
				{else if $element.label eq "table"}
					{if $inTable eq "FALSE"}
						{assign var="inTable" value="TRUE"}
						<table class="table table-instrument">
							<tr>
								{foreach key=gkey item=gitem from=$element.elements}
									<th>{$gitem.html}</th>
								{/foreach}
							</tr>
					{else}
						<tr>
							{foreach key=gkey item=gitem from=$element.elements}
								{if $gitem.name eq "strong"}
									<td><strong>{$gitem.html}</strong></td>
								{else}
									<td class="element">{$gitem.html}</td>
								{/if}
							{/foreach}
						</tr>
					{/if}
				{else}
					{if $inTable eq "TRUE"}
						{assign var="inTable" value="FALSE"}
						</table>
					{/if}
					{if $element.error}
			    	<div class="row form-group form-inline has-error">
			        {else}
			        <div class="row form-group form-inline">
			        {/if}
						<lable class="lab col-sm-4 col-xs-12">
							{if $element.required}
								<span style="color: #ff0000">*</span>
							{/if}
							{$element.label}  
						</lable>
						<div class="col-sm-8">
							<div class="col-xs-12 element">
								{if $element.type eq "group"}
									{foreach key=gkey item=gitem from=$element.elements}
										{$gitem.html}
									{/foreach}
								{else}
									{$element.html}
								{/if}
							</div>
							{if $element.error}
								<div class="col-xs-12">
				                    <font class="form-error">{$element.error}</font>
				                </div>
							{/if}
						</div>
					</div>
				{/if}
			{/if}
		{/foreach}
	{/foreach}
</form>