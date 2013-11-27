<form method="post" name="candidate_parameters" id="candidate_parameters">
<table class="std">

    <!-- table title -->
    <tr><th colspan="2">Candidate Information</th></tr>

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
        <td nowrap="nowrap" >{$form.pscid.label}</td>
        <td nowrap="nowrap" id="pscid">{$pscid}</td>
    </tr>
    <tr>
        <td nowrap="nowrap">{$form.CandidateGUID.label}</td>
        <td nowrap="nowrap">{$form.CandidateGUID.html}</td>
    </tr>
    <tr>
      <td nowrap="nowrap">{$form.flagged_caveatemptor.label}</td>
      <td nowrap="nowrap">{$form.flagged_caveatemptor.html}</td>
    </tr>
    <tr>
      <td nowrap="nowrap">{$form.flagged_reason.label}</td>
      <td nowrap="nowrap">{$form.flagged_reason.html}</td>
    </tr>
    <tr>
      <td nowrap="nowrap">{$form.flagged_other_group.label}</td>
      <td nowrap="nowrap">{$form.flagged_other_group.html}</td>
    </tr>

  </br>

    {foreach from=$elements_list item=element}
	<tr>
		<td nowrap="nowrap">{$form.$element.label}</td>
		<td nowrap="nowrap">{$form.$element.html}</td>
	</tr>
	{/foreach}

     <tr><th colspan="2">Proband Information</th> </tr>
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
       <td nowrap="nowrap">{$form.ProbandDoB2.label}</td>
       <td nowrap="nowrap">{$form.ProbandDoB2.html}</td>
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
    
      <tr><th colspan="2">Family Information</th></tr>
   <!--
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
     -->
    <tr>
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
    <td nowrap="nowrap" colspan="2">
    <input class="button" onclick="location.href='main.php?test_name=candidate_parameters&subtest=add_family&candID={$candID}&identifier={$candID}'"i value="Add Sibling" type="button" />
    </td>
  
<tr><th colspan="2">Participant Status</th></tr>
{*
<tr>
<td nowrap="nowrap" >{$form.pscid.label}</td>
<td nowrap="nowrap" id="pscid">{$pscid}</td>
</tr>
*}
<tr>

    <td nowrap="nowrap">Participant Status</td>
    <td>
{html_options id="participant_status" options=$pstatus_options name="participant_status" selected=$pstat}
</td>
<tr>
<td>
Specify Reason</br>(Required only for status Inactive/Incomplete)
</td>
<td>
<div>
<select name="participant_suboptions" id="participant_suboptions">
</select>
</div>
</td>
<tr>
<td nowrap="nowrap" >{$form.reason_specify_group.label}</td>
<td nowrap="nowrap" >{$form.reason_specify_group.html}</td>
</tr>
<tr>
<td></td>
<td>
     <a href="main.php?test_name=candidate_parameters&subtest=participant_status_history&candID={$candID}&identifier={$candID}">See Participant status history </a>
                       </td>

</tr>


{if $consent}
<tr><th colspan="2">Participation Consent Status</th></tr>
{section name=question loop=$consent}
{* 
    $consent[question] contains a list of element
        names in the form that are related to that question.
        We need to iterate through them to add them to the
        HTML. 
        *}
{foreach from=$consent[question] item=row}
<tr>
<td>{$form.$row.label}</td>
<td>{$form.$row.html}

{if $form.$row.error}
<span class="error">{$form.$row.error}</span>
{/if}
</td>
</tr>
{/foreach}

<tr>
<td colspan="2">&nbsp;</td>
</tr>
{/section}
{/if}
<tr><th colspan="2">Data Entry Information</th></tr>
<tr>
<td nowrap="nowrap">{$form.entry_staff.label}</td>
<td nowrap="nowrap">{$form.entry_staff.html}</td>
</tr>

<tr>
<td nowrap="nowrap">{$form.data_entry_date.label}</td>
<td nowrap="nowrap">{$form.data_entry_date.html}</td>
</tr>

<tr>
<!--td nowrap="nowrap" colspan="1">&nbsp;</td -->
<td nowrap="nowrap" colspan="2" align="right">
{if not $success}
<input class="button" name="fire_away" value="Save" type="submit" />
{/if}
<input class="button" onclick="location.href='main.php?test_name=timepoint_list&candID={$candID}'" value="Return to profile" type="button" />
</td>
</tr>
</table>
{$form.hidden}
</form>
