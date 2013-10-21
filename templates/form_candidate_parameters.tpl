<br />
<form method="post" name="candidate_parameters" id="candidate_parameters">
<table class="std">

    <!-- table title -->
    <tr><th colspan="2">Candidate Parameters</th></tr>

    {foreach from=$form.errors item=error}
    <tr>
        <td nowrap="nowrap" colspan="2" class="error">{$error}</td>
    </tr>
    {/foreach}
	
    {if $form.dob_error}
    <tr>
        <td colspan="2" class="error">{$form.dob_error.label}</td>
    </tr>
    {/if}
    <tr> 
      <td nowrap="nowrap"><b>Candidate Infomation</b></td>
    </tr>
    <tr>
        <td nowrap="nowrap">{$form.CandidateGUID.label}</td>
        <td nowrap="nowrap">{$form.CandidateGUID.html}</td>
    </tr>
     <tr> 
      <td nowrap="nowrap"><b>Proband Infomation</b></td>
    </tr>
    <tr>
        <td nowrap="nowrap">{$form.ProbandGUID.label}</td>
        <td nowrap="nowrap">{$form.ProbandGUID.html}</td>
    </tr>
    <tr>
        <td nowrap="nowrap">{$form.ProbandGender.label}</td>
        <td nowrap="nowrap">{$form.ProbandGender.html}</td>
    </tr>
    <tr>
        <td nowrap="nowrap">{$form.ProbandDoB.label}</td>
        <td nowrap="nowrap">{$form.ProbandDoB.html}</td>
    </tr>
    <tr>
        <td nowrap="nowrap">{$form.dob_proband_adi_r.label}</td>
        <td nowrap="nowrap">{$form.dob_proband_adi_r.html}</td>
    </tr>
    <tr>
        <td nowrap="nowrap">{$form.dob_proband_vineland.label}</td>
        <td nowrap="nowrap">{$form.dob_proband_vineland.html}</td>
    </tr>
     <tr>
        <td nowrap="nowrap">{$form.Age_Difference.label}</td>
        <td nowrap="nowrap">{$form.Age_Difference.html}</td>
    </tr>
    <tr> 
      <td nowrap="nowrap"><b>Parent Infomation</b></td>
    </tr>
<tr>
		<td nowrap="nowrap">{$form.mother_race.label}</td>
		<td nowrap="nowrap">{$form.mother_race.html}</td>
    </tr>
    <tr>
		<td nowrap="nowrap">{$form.father_race.label}</td>
		<td nowrap="nowrap">{$form.father_race.html}</td>
    </tr>
    <tr>
		<td nowrap="nowrap">{$form.home_lang.label}</td>
		<td nowrap="nowrap">{$form.home_lang.html}</td>
    </tr>
    <tr>
		<td nowrap="nowrap">{$form.birth_city.label}</td>
		<td nowrap="nowrap">{$form.birth_city.html}</td>
    </tr>
    <tr>
    <td nowrap="nowrap"><b>Sibling Infomation</b></td>
       {foreach from=$sibling_list item=sibling key=keyid}
    <tr>
    <td nowrap="nowrap">{$form.SiblingcID.label}</td>
    <td>
     <a href="main.php?test_name=timepoint_list&candID={$sibling.CandID}">
         {$sibling.CandID}
      </a>
   </td>
    </tr>
    <tr>
    <td nowrap="nowrap">{$form.relation_type.label}</td>
    <td nowrap="nowrap">{$sibling.Relationship_type}</td>
    </tr>
    {/foreach}
    <td></td>
    <td>
    <a href="main.php?test_name=candidate_parameters&subtest=add_family&candID={$candID}&identifier={$candID}">
    Add Sibling Information
    </a>
    </td>
    </tr>
    </br>
    <tr></tr>
    {foreach from=$elements_list item=element}
	<tr>
		<td nowrap="nowrap">{$form.$element.label}</td>
		<td nowrap="nowrap">{$form.$element.html}</td>
	</tr>
	{/foreach}

	<tr>
        <td nowrap="nowrap">&nbsp;</td>
		<td nowrap="nowrap" colspan="2">
    {if not $success}
        <input class="button" name="fire_away" value="Save" type="submit" />
        <input class="button" value="Reset" type="reset" />
    {/if}
        <input class="button" onclick="location.href='main.php?test_name=timepoint_list&candID={$candID}'" value="Return to profile" type="button" />
        </td>
	</tr>
</table>
{$form.hidden}
</form>
