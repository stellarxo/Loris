<!-- start data table -->
<table  class ="fancytable" border="0" width="100%">
<tr>
    <th>Key</th>
    <th>Original</th>
    <th>Reliability</th>
</tr>
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
</table>

