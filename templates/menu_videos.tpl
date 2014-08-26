<script type="text/javascript" src="js/filterControl.js"></script>
<div class="col-sm-8">
    <div class="panel panel-primary">
        <div class="panel-heading" onclick="hideFilter();">
            Selection Filter
            <span class="glyphicon glyphicon-chevron-down pull-right" style="display:none" id="down"></span>
            <span class="glyphicon glyphicon-chevron-up pull-right" id="up"></span>
        </div>
        <div class="panel-body" id="panel-body">
            <form method="post" action="main.php?test_name=videos">
                <div class="row">
                    <div class="form-group col-sm-6">
                        <label class="col-md-4">{$form.PSCID.label}</label>
                        <div class="col-md-8">{$form.PSCID.html}</div>
                    </div>
                    <div class="form-group col-sm-6">
                        <label class="col-md-4">{$form.Instrument.label}</label>
                        <div class="col-md-8">{$form.Instrument.html}</div>
                    </div>
                </div>
                <div class="row">
                    <div class="form-group col-sm-6">
                        <label class="col-md-4">{$form.visitLabel.label}</label>
                        <div class="col-md-8">{$form.visitLabel.html}</div>
                    </div>
                    <div class="form-group col-sm-6">
                        <label class="col-md-4">{$form.For_site.label}</label>
                        <div class="col-md-8">{$form.For_site.html}</div>
                    </div>
                </div>
                <div class="row">
                    <div class="form-group col-sm-12">
                        <div class="col-sm-6 col-md-3 col-md-offset-6">
                            <input type="submit" name="filter" value="Show Data" class="btn btn-sm btn-primary col-xs-12" />
                        </div>
                        <div class="visible-xs col-xs-12"> </div>
                        <div class="visible-xs col-xs-12"> </div>
                        <div class="visible-xs col-xs-12"> </div>
                        <div class="visible-xs col-xs-12"> </div>
                        <div class="col-sm-6 col-md-3">
                            <input type="button" name="reset" value="Clear Form" onclick="location.href='main.php?test_name=videos&reset=true'" class="btn btn-sm btn-primary col-xs-12" />
                        </div>
                    </div>
                </div>
            </form>
        </div>
    </div>
</div>

<br>
<!-- <h2><font color="red">Note: Phase 2 reliability forms are unavailable at the moment as the system is being upgraded.</font></h2> -->

<!--  title table with pagination -->
<table border="0" valign="bottom" width="100%">
<tr>
    <td class="controlPanelSection">
      {if $Normal_Perm}
        <a href="main.php?test_name=videos&showEARLI=">IBIS Videos</a> 
      {/if}
      {if $Normal_Perm && $EARLI_Perm}
      |
      {/if}
      {if $EARLI_Perm}
        <a href="main.php?test_name=videos&showEARLI=1">EARLI Videos</a>
      {/if}
    </td>
</tr>
<tr>
    <!-- title -->
  
    <td class="controlPanelSection">
      <a href="main.php?test_name=video_upload">
        Upload a New Video
      </a>

    </td>
</tr>
</table>

<!--  title table with pagination -->
<table border="0" valign="bottom" width="100%">
<tr>
    <!-- title -->
    <td class="controlPanelSection">List of Log Entries</td>

    <!-- display pagination links -->
    <td align="right">{$page_links}</td>
</tr>
</table>

<!-- start data table -->
<div class="table-responsive">
    <table border="0" width="100%" class ="table table-hover table-primary table-bordered">
        <thead>
            <tr class="info">
             <th>No.</th>
                <!-- print out column headings - quick & dirty hack -->
                {section name=header loop=$headers}
                    <th>
                      <a href="main.php?test_name=videos&filter[order][field]={$headers[header].name}&filter[order][fieldOrder]={$headers[header].fieldOrder}">
                        {$headers[header].displayName}
                      </a>
                    </th>
                {/section}
            </tr>
        </thead>
        <tbody>
            {section name=item loop=$items}
                <tr>
                <!-- print out data rows -->
                {section name=piece loop=$items[item]}
                

                {if $items[item][piece].name == "File_name"}
                   <td>
                    <a href="{$items[item][piece].Data_dir}{$items[item][piece].value}" target="_blank">{$items[item][piece].value}</a> {if !empty($items[item][piece].File_size)}({$items[item][piece].File_size}){/if}
                  </td>
               {elseif $items[item][piece].name == "record_id"}
                  <td>
                      <a href="main.php?test_name=video_upload&identifier={$items[item][piece].value}" target="_blank">Edit</a> 
                    </td>
                 {else}
                     <td>{$items[item][piece].value}</td>
                {/if}
               </td>
                {/section}
                </tr>           
            {sectionelse}
                <tr><td colspan="15">No videos found.</td></tr>
            {/section} 
        </tbody>     
    <!-- end data table -->
    </table>

