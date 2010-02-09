
<table class="std">

    <!-- table title -->
    <tr><th colspan="2">Conflicts Resolver</th></tr>
<tr>
<td>

<a href="/main.php?test_name=conflicts_resolve&site=2">Seattle </a>
<a href="/main.php?test_name=conflicts_resolve&site=3">Philadelphia </a>
<a href="/main.php?test_name=conflicts_resolve&site=4">St. Louis </a>
<a href="/main.php?test_name=conflicts_resolve&site=5">UNC </a>
</td>
</tr>
</table>
<br>

<br>
<form method="post" name="conflicts_resolve" id="conflicts_resolve">
<table class="std">


    {foreach from=$form.errors item=error}
    <tr>
        <td nowrap="nowrap" colspan="2" class="error">{$error}</td>
    </tr>
    {/foreach}
	
    {foreach from=$elements_list item=element}
	<tr>
		<td nowrap="nowrap">{$form.$element.label}</td>
		<td nowrap="nowrap">{$form.$element.html}</td>
	</tr>
	{/foreach}


        <tr>
        <td nowrap="nowrap">&nbsp;</td>
                <td nowrap="nowrap" colspan="2">
        <input class="button" name="fire_away" value="Save" type="submit" />
        <input class="button" value="Reset" type="reset" />
        </td>
        </tr>


</table>
{$form.hidden}
</form>

