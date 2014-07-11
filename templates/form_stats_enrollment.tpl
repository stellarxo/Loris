<div id="enroll">
    <script type="text/javascript" src="js/modules/form_stats_enrollment.js"></script>
    <div class="col-sm-3">
        {html_options id="EnrollmentSite" options=$Sites name="site" selected=$CurrentSite.ID class="form-control input-sm"}
    </div>
    <div class="col-sm-3">
        {html_options id="EnrollmentProject" options=$Projects name="project" selected =$CurrentProject.ID class="form-control input-sm"}
    </div>
    <button class="btn btn-primary btn-sm" onClick="updateEnrollmentTab()">Submit Query</button>
    <h2> Inclusion Enrollment Report {if $CurrentSite} for {$CurrentSite.Name}{/if} 
     {if $CurrentProject} for {$CurrentProject.Name} {/if}</h2>
    <h2> PART A. TOTAL ENROLLMENT REPORT: Number of Subjects Enrolled to Date (Cumulative) by Ethnicity and Race </h2>
    <div class="table-responsive">
        <table  class ="table table-hover table-primary table-bordered" border="0" width="100%">
            <thead>
                <tr class="info">
                    <th> Ethnic Category </th>
                      <th> Females </th>
                      <th> Males </th>
                      <th> Sex/Gender unknown or Not Reported </th>
                      <th> Total </th>
                </tr>
            </thead>
            <tbody>
                {section name = item loop=$enroll_data}
                    <tr>
                         <td>{$enroll_data[item].ethnic_cat}</td>
                         <td>{$enroll_data[item].female_count}</td>
                         <td>{$enroll_data[item].male_count}</td>
                         <td>{$enroll_data[item].unknown_count}</td>
                         <td>{$enroll_data[item].total_count}</td>
                    </tr>
                {/section}
                <tr>
                     <td><b>{$enroll_data_total[0].total_name}</b> </td>
                     <td>{$enroll_data_total[0].total_female} </td>
                     <td>{$enroll_data_total[0].total_male}</td>
                     <td>{$enroll_data_total[0].total_unknown}</td>
                     <td>{$enroll_data_total[0].total_total}</td>
                </tr>
            </tbody>
        </table>
    </div>
    </br>
    <div class="table-responsive">
        <table  class ="table table-hover table-primary table-bordered" border="0" width="100%">
            <thead>
                <tr class="info">
                     <th> Racial Categories </th>
                     <th> Females </th>
                     <th> Males </th>
                     <th> Sex/Gender unknown or Not Reported </th>
                     <th> Total </th>
                </tr>
            </thead>
            <tbody>
                {section name = item loop=$enroll_data_race}
                    <tr>
                        <td>{$enroll_data_race[item].race_cat}</td>
                        <td>{$enroll_data_race[item].female_count}</td>
                        <td>{$enroll_data_race[item].male_count}</td>
                        <td>{$enroll_data_race[item].unknown_count}</td>
                        <td>{$enroll_data_race[item].total_count}</td>
                    </tr>
                {/section}
                <tr>
                    <td><b>{$enroll_data_racetotal[0].total_name}</b> </td>
                    <td>{$enroll_data_racetotal[0].total_female} </td>
                    <td>{$enroll_data_racetotal[0].total_male}</td>
                    <td>{$enroll_data_racetotal[0].total_unknown}</td>
                    <td>{$enroll_data_racetotal[0].total_total}</td>
                </tr>
           </tbody>
        </table>
    </div>

    <h2>PART B. HISPANIC ENROLLMENT REPORT: Number of Hispanic or Latinos Enrolled to Date (Cumulative) </h2>
    <div class="table-responsive">
        <table  class ="table table-hover table-primary table-bordered" border="0" width="100%">
            <thead>
                <tr class="info">
                    <th> Racial Categories </th>
                    <th> Females </th>
                    <th> Males </th>
                    <th> Sex/Gender unknown or Not Reported </th>
                    <th> Total </th>
                </tr>
            </thead>
            <tbody>
                {section name = item loop=$enroll_data_hispanic}
                    <tr>
                        <td>{$enroll_data_hispanic[item].race_cat}</td>
                        <td>{$enroll_data_hispanic[item].female_count}</td>
                        <td>{$enroll_data_hispanic[item].male_count}</td>
                        <td>{$enroll_data_hispanic[item].unknown_count}</td>
                        <td>{$enroll_data_hispanic[item].total_count}</td>
                    </tr>
                {/section}
                <tr>
                    <td><b>{$enroll_data_hispanictotal[0].total_name}</b> </td>
                    <td>{$enroll_data_hispanictotal[0].total_female} </td>
                    <td>{$enroll_data_hispanictotal[0].total_male}</td>
                    <td>{$enroll_data_hispanictotal[0].total_unknown}</td>
                    <td>{$enroll_data_hispanictotal[0].total_total}</td>
                </tr>
            </tbody>
        </table>
    </div>
    </br>
    <h2 class="statsH2"> Total Failure or Withdrawls: {$enroll_data_withdrawal} </h2>
</div>

