<h2><font color="#000000">ADI-R Phase 1 Reliability</font></h2>
<p>
   Initial reliability: Raters must establish reliability with a University of Michigan Autism and Communication Disorders Centers (UMACC)-trained clinician as determined by a minimum score of 90% on BOTH the total and algorithmic reliability scores.
</p>
<table>
   <tr bgcolor="#08245b">
      <th><font color="#CCCCCC">Site</font></th>
      <th><font color="#CCCCCC">Rater</font></th>
      <th><font color="#CCCCCC">Outside Research Group</font></th>
      <th><font color="#CCCCCC">Reliable</font></th>
      <th><font color="#CCCCCC">Date Reliability Established</font></th>
      <th><font color="#CCCCCC">Administration Status</font></th>
   </tr>
   {section name=item loop=$adi_r_data}
   <tr bgcolor="#FFFFFF">
      <td>{$adi_r_data[item].site}</td>
      <td>{$adi_r_data[item].rater}</td>
      <td>{$adi_r_data[item].outside_research_group}</td>
      <td>{$adi_r_data[item].reliable}</td>
      <td>{$adi_r_data[item].reliability_established_date}</td>
      <td>{$adi_r_data[item].administration_status}</td>
   </tr>
   {/section}
</table>

<br><br>

<h2><font color="#000000">FIGS Phase 1 Reliability</font></h2>
<p>
   Initial reliability: Raters must send a FIGS audio tape to and receive feedback from St. Louis (Helen Valenza).  Once feedback has been received, the raters must review the feedback and make any necessary adjustments in the instrument administration.  Raters must then send a new FIGS audio tape to St. Louis and receive feedback.  This procedure should continue until St. Louis declares raters to be reliable for administration of the FIGS.  
</p>
<table>
   <tr bgcolor="#08245b">
      <th rowspan="2"><font color="#CCCCCC">Site</font></th>
      <th rowspan="2"><font color="#CCCCCC">Rater</font></th>
      <th rowspan="2"><font color="#CCCCCC">Lead Clinician</font></th>
      <th colspan="4"><font color="#CCCCCC">Tape 1</font></th>
      <th colspan="4"><font color="#CCCCCC">Tape 2</font></th>
      <th colspan="4"><font color="#CCCCCC">Tape 3</font></th>
      <th rowspan="2"><font color="#CCCCCC">Reliable</font></th>
      <th rowspan="2"><font color="#CCCCCC">Date Reliability Established</font></th>
      <th rowspan="2"><font color="#CCCCCC">Administration Status</font></th>
   </tr>
   <tr bgcolor="#08245b">
      <th><font color="#CCCCCC">Case ID</font></th>
      <th><font color="#CCCCCC">Administration</font></th>
      <th><font color="#CCCCCC">Tape Sent</font></th>
      <th><font color="#CCCCCC">Feedback</font></th>
      <th><font color="#CCCCCC">Case ID</font></th>
      <th><font color="#CCCCCC">Administration</font></th>
      <th><font color="#CCCCCC">Tape Sent</font></th>
      <th><font color="#CCCCCC">Feedback</font></th>
      <th><font color="#CCCCCC">Case ID</font></th>
      <th><font color="#CCCCCC">Administration</font></th>
      <th><font color="#CCCCCC">Tape Sent</font></th>
      <th><font color="#CCCCCC">Feedback</font></th>
   </tr>
   {section name=item loop=$figs_data}
   <tr bgcolor="#FFFFFF">
      <td>{$figs_data[item].site}</td>
      <td>{$figs_data[item].rater}</td>
      <td>{$figs_data[item].lead_clinician}</td>
      <td>{$figs_data[item].case_ID_1}</td>
      <td>{$figs_data[item].tape_1_admin}</td>
      <td>{$figs_data[item].tape_1_sent}</td>
      <td>{$figs_data[item].tape_1_feedback}</td>
      <td>{$figs_data[item].case_ID_2}</td>
      <td>{$figs_data[item].tape_2_admin}</td>
      <td>{$figs_data[item].tape_2_sent}</td>
      <td>{$figs_data[item].tape_2_feedback}</td>
      <td>{$figs_data[item].case_ID_3}</td>      
      <td>{$figs_data[item].tape_3_admin}</td>
      <td>{$figs_data[item].tape_3_sent}</td>
      <td>{$figs_data[item].tape_3_feedback}</td>
      <td>{$figs_data[item].reliable}</td>
      <td>{$figs_data[item].reliability_established_date}</td>
      <td>{$figs_data[item].administration_status}</td>
   </tr>
   {/section}
</table>

<br><br>

<h2><font color="#000000">AOSI Phase 1 Reliability (6 months)</font></h2>
<p>
Initial reliability: Raters must send, at least, one v06 and v12 AOSI videotape to the University of Alberta (L. Zwaigenbaum laboratory) and receive a minimum reliability score of 79% on both administrations.
</p>
<table>
   <tr bgcolor="#08245b">
      <th rowspan="2"><font color="#CCCCCC">Site</font></th>
      <th rowspan="2"><font color="#CCCCCC">Rater</font></th>
      <th rowspan="2"><font color="#CCCCCC">Case Age (months)</font></th>
      <th colspan="2"><font color="#CCCCCC">Tape 1</font></th>
      <th colspan="2"><font color="#CCCCCC">Tape 2</font></th>
      <th rowspan="2"><font color="#CCCCCC">Reliable</font></th>
      <th rowspan="2"><font color="#CCCCCC">Date Reliability Established</font></th>
      <th rowspan="2"><font color="#CCCCCC">Administration Status</font></th>
   </tr>
   <tr bgcolor="#08245b">
      <th><font color="#CCCCCC">Case ID</font></th>
      <th><font color="#CCCCCC">Date Tape Was Sent</font></th>
      <th><font color="#CCCCCC">Case ID</font></th> 
      <th><font color="#CCCCCC">Date Tape Was Sent</font></th>
   </tr>
   {section name=item loop=$aosi_data_6mo}
   <tr bgcolor="#FFFFFF">
      <td>{$aosi_data_6mo[item].site}</td>
      <td>{$aosi_data_6mo[item].rater}</td>
      <td>{$aosi_data_6mo[item].case_age_mo}</td>
      <td>{$aosi_data_6mo[item].case_ID_1}</td>
      <td>{$aosi_data_6mo[item].tape_sent_date_1}</td>
      <td>{$aosi_data_6mo[item].case_ID_2}</td>
      <td>{$aosi_data_6mo[item].tape_sent_date_2}</td>
      <td>{$aosi_data_6mo[item].reliable}</td>
      <td>{$aosi_data_6mo[item].reliability_established_date}</td>
      <td>{$aosi_data_6mo[item].administration_status}</td>
   </tr>
   {/section}
</table>

<br><br>

<h2><font color="#000000">AOSI Phase 1 Reliability (12 months)</font></h2>
<p>
Initial reliability: Raters must send, at least, one v06 and v12 AOSI videotape to the University of Alberta (L. Zwaigenbaum laboratory) and receive a minimum reliability score of 79% on both administrations.
</p>
<table>
   <tr bgcolor="#08245b">
      <th rowspan="2"><font color="#CCCCCC">Site</font></th>
      <th rowspan="2"><font color="#CCCCCC">Rater</font></th>
      <th rowspan="2"><font color="#CCCCCC">Case Age (months)</font></th>
      <th colspan="2"><font color="#CCCCCC">Tape 1</font></th>
      <th colspan="2"><font color="#CCCCCC">Tape 2</font></th>
      <th rowspan="2"><font color="#CCCCCC">Reliable</font></th>
      <th rowspan="2"><font color="#CCCCCC">Date Reliability Established</font></th>
      <th rowspan="2"><font color="#CCCCCC">Administration Status</font></th>
   </tr>
   <tr bgcolor="#08245b">
      <th><font color="#CCCCCC">Case ID</font></th>
      <th><font color="#CCCCCC">Date Tape Was Sent</font></th>
      <th><font color="#CCCCCC">Case ID</font></th> 
      <th><font color="#CCCCCC">Date Tape Was Sent</font></th>
   </tr>
   {section name=item loop=$aosi_data_12mo}
   <tr bgcolor="#FFFFFF">
      <td>{$aosi_data_12mo[item].site}</td>
      <td>{$aosi_data_12mo[item].rater}</td>
      <td>{$aosi_data_12mo[item].case_age_mo}</td>
      <td>{$aosi_data_12mo[item].case_ID_1}</td>
      <td>{$aosi_data_12mo[item].tape_sent_date_1}</td>
      <td>{$aosi_data_12mo[item].case_ID_2}</td>
      <td>{$aosi_data_12mo[item].tape_sent_date_2}</td>
      <td>{$aosi_data_12mo[item].reliable}</td>
      <td>{$aosi_data_12mo[item].reliability_established_date}</td>
      <td>{$aosi_data_12mo[item].administration_status}</td>
   </tr>
   {/section}
</table>

<br><br>

<h2><font color="#000000">CSBS Phase 1 Reliability (training kit)</font></h2>
<p>
   Initial reliability: Raters must achieve a minimum score of 80% on BOTH the total and algorithmic reliability scores for the: (1) CSBS training-kit tapes and (2) the UW-coded Wetherby tape (e.g., &quot;gold standard&quot; case implemented in the IBIS database reliability module)
</p>
<table>
   <tr bgcolor="#08245b">
      <th><font color="#CCCCCC">Site</font></th>
      <th><font color="#CCCCCC">Rater</font></th>
      <th><font color="#CCCCCC">Coder Status</font></th>
      <th><font color="#CCCCCC">Reliable</font></th>
      <th><font color="#CCCCCC">Date Reliability Established</font></th>
      <th><font color="#CCCCCC">Administration Status</font></th>
   </tr>
   {section name=item loop=$csbs_data_tk}
   <tr bgcolor="#FFFFFF">
      <td>{$csbs_data_tk[item].site}</td>
      <td>{$csbs_data_tk[item].rater}</td>
      <td>{$csbs_data_tk[item].examiner_coder_status}</td>
      <td>{$csbs_data_tk[item].reliable}</td>
      <td>{$csbs_data_tk[item].reliability_established_date}</td>
      <td>{$csbs_data_tk[item].administration_status}</td>
   </tr>
   {/section}
</table>


<br><br>

<h2><font color="#000000">CSBS Phase 1 Reliability (UW gold standard)</font></h2>
<p>
   Initial reliability: Raters must achieve a minimum score of 80% on BOTH the total and algorithmic reliability scores for the: (1) CSBS training-kit tapes and (2) the UW-coded Wetherby tape (e.g., &quot;gold standard&quot; case implemented in the IBIS database reliability module)
</p>
<table>
   <tr bgcolor="#08245b">
      <th><font color="#CCCCCC">Site</font></th>
      <th><font color="#CCCCCC">Rater</font></th>
      <th><font color="#CCCCCC">Coder Status</font></th>
      <th><font color="#CCCCCC">Reliable</font></th>
      <th><font color="#CCCCCC">Date Reliability Established</font></th>
      <th><font color="#CCCCCC">Administration Status</font></th>
   </tr>
   {section name=item loop=$csbs_data_gold}
   <tr bgcolor="#FFFFFF">
      <td>{$csbs_data_gold[item].site}</td>
      <td>{$csbs_data_gold[item].rater}</td>
      <td>{$csbs_data_gold[item].examiner_coder_status}</td>
      <td>{$csbs_data_gold[item].reliable}</td>
      <td>{$csbs_data_gold[item].reliability_established_date}</td>
      <td>{$csbs_data_gold[item].administration_status}</td>
   </tr>
   {/section}
</table>


<br><br>

<h2><font color="#000000">ADOS Phase 1 Reliability</font></h2>
<p>
   Initial reliability: Raters must establish reliability with UMACC or a UMACC-trained clinician as determined by a minimum score of 80% on BOTH the total and algorithmic reliability scores.
</p>
<table>
   <tr bgcolor="#08245b">
      <th><font color="#CCCCCC">Site</font></th>
      <th><font color="#CCCCCC">Rater</font></th>
      <th><font color="#CCCCCC">Reliable</font></th>
      <th><font color="#CCCCCC">Date Reliability Established</font></th>
      <th><font color="#CCCCCC">Administration Status</font></th>
   </tr>
   {section name=item loop=$ados_data}
   <tr bgcolor="#FFFFFF">
      <td>{$ados_data[item].site}</td>
      <td>{$ados_data[item].rater}</td>
      <td>{$ados_data[item].reliable}</td>
      <td>{$ados_data[item].reliability_established_date}</td>
      <td>{$ados_data[item].administration_status}</td>
   </tr>
   {/section}
</table>

<br><br>

<h2><font color="#000000">Mullen Phase 1 Reliability</font></h2>
<p>
   Initial reliability: In order to be considered initially reliable, raters must: (1) conduct and receive immediate feedback (using the Mullen Fidelity Form) on at least three Mullen administrations by a trained supervisor or &quot;gold-standard&quot; clinician (e.g., licensed clinical psychologist, neuropsychologist, or psychometrist) or (2) be considered a trained supervisor, themselves.
</p>
<table>
   <tr bgcolor="#08245b">
      <th><font color="#CCCCCC">Site</font></th>
      <th><font color="#CCCCCC">Rater</font></th>
      <th><font color="#CCCCCC">Lead Clinician</font></th>
      <th><font color="#CCCCCC">Reliable</font></th>
      <th><font color="#CCCCCC">Date Reliability Established</font></th>
      <th><font color="#CCCCCC">Administration Status</font></th>
   </tr>
   {section name=item loop=$mullen_data}
   <tr bgcolor="#FFFFFF">
      <td>{$mullen_data[item].site}</td>
      <td>{$mullen_data[item].rater}</td>
      <td>{$mullen_data[item].lead_clinician}</td>
      <td>{$mullen_data[item].reliable}</td>
      <td>{$mullen_data[item].reliability_established_date}</td>
      <td>{$mullen_data[item].administration_status}</td>
   </tr>
   {/section}
</table>
