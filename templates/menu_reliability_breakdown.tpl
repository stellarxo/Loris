<!-- start data table -->
<div class="table-responsive">
	<table border="0" width="100%" class="table table-hover table-primary table-bordered">
		<thead>
			<tr class="info">
			    <th>Key</th>
			    <th>Original</th>
			    <th>Reliability</th>
			</tr>
		</thead>
		<tbody>
			{section name=i loop=$differences}
				<tr>
				    <td>{$differences[i].key}</td>
				    <td>{$differences[i].original}</td>
				    <td>{$differences[i].reliable}</td>
				</tr>
				{sectionelse}
				<tr>
				    <td colspan="3">No differences found</td>
				</tr>
			{/section}
		</tbody>
		
		
	</table>
</div>

