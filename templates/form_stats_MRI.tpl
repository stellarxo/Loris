<div id="mri">

    <h2 class = "statsH2">MRI Statistics:</h2>

    <h2 class="statsH2">General MRI Statistics  {if $CurrentProject} for {$CurrentProject.Name} {/if}</h2>

    <div class="col-sm-2">
        {html_options id="MRIProject" options=$Projects name="MRIProject" selected=$CurrentProject.ID class="form-control input-sm"}
    </div>
    <script type="text/javascript" src="GetJS.php?Module=statistics&file=form_stats_MRI.js"></script>
    <button class="btn btn-primary btn-sm" onClick="updateMRITab()">Submit Query</button>
    <br><br>
    <div class="table-responsive">
        <table  class ="table table-hover table-primary table-bordered" border="0" width="100%">
            <thead>
                 <tr class="info">
                    <th>Site</th>
                    <th>Scans on the Workstations</th>
                    <th>Scans Claimed</th>
                    <th>v06, v12 and v24 Scans All Claimed</th>
                    <th>Parameter Forms Completed</th>
                 </tr>
            </thead>
            <tbody>
                 {section name=item loop=$mri_data}
                 <tr>
                    <td>{$mri_data[item].name}</td>
                    <td>{$mri_data[item].work_station_count}</td>
                    <td>{$mri_data[item].claimed_count}</td>
                    <td>{$mri_data[item].forms_count}</td>
                    <td></td>
                 </tr>
                 {/section}
            </tbody>
        </table>
    </div>

    {if $showTable}
    <h2 class="statsH2">Candidates That Have Completed Scans at All Three Timepoints (V06, V12, and V24):</h2>
    <div class="table-responsive">
        <table class ="table table-hover table-primary table-bordered" border="0" width="100%">
            <thead>
                <tr class="info">
                    <th>Site</th>
                    <th>T1 Complete</th>
                    <th>T2 Complete</th>
                    <th>DTI Complete</th>
                    <th>T1, T2, and DTI all Complete</th>
                </tr>
            </thead>
            <tbody>
                {section name=item loop=$mri_all_scans_done}
                <tr>
                    <td>{$mri_all_scans_done[item].Name}</td>
                    <td>{$mri_all_scans_done[item].T1}</td>
                    <td>{$mri_all_scans_done[item].T2}</td>
                    <td>{$mri_all_scans_done[item].DTI}</td>
                    <td>{$mri_all_scans_done[item].All}</td>

                </tr>
                {/section}
            </tbody>
        </table>
    </div>
    {/if}
    {assign var="Subsection" value="mri"}
    {$MRI_Done_Table}

    <h2 class="statsH2">MRI Integrity Statistics:</h2>
    <div class="table-responsive">
        <table  class ="table table-hover table-primary table-bordered" border="0" width="100%">
            <thead>
                <tr class="info">
                    <th>Site</th>
                    <th>No Parameter Form Completed</th>
                    <th>Nothing in MRI Browser for Form</th>
                    <th>No tarchive Entry for Form</th>
                    <th>Breakdown of Problems</th>
                </tr>
            </thead>
            <tbody>
                {foreach item=center from=$Centers}
                    <tr>
                        <td>{$center.LongName}</td>
                        <td>{$mri_errors[$center.NumericID].no_parameter}</td>
                        <td>{$mri_errors[$center.NumericID].no_browser}</td>
                        <td>{$mri_errors[$center.NumericID].no_tarchive}</td>
                        <td><a href="?test_name=statistics_mri_site&CenterID={$center.NumericID}">Please Click Here</a></td>
                    </tr>
                {/foreach}
            </tbody>
        </table>
    </div>
</div>

