<!-- Nav tabs -->
<ul class="nav nav-tabs nav-tabs-loris" role="tablist">
    <li role="presentation" class="active">
        <a href="#cand-info" aria-controls="browse" role="tab" data-toggle="tab">
            Candidate Information
        </a>
    </li>
    <li role="presentation">
        <a href="#proband-info" aria-controls="upload" role="tab" data-toggle="tab">
            Proband Information
        </a>
    </li>
    <li role="presentation">
        <a href="#family-info" aria-controls="upload" role="tab" data-toggle="tab">
            Family Information
        </a>
    </li>
    <li role="presentation">
        <a href="#participant-status" aria-controls="upload" role="tab" data-toggle="tab">
            Participant Status
        </a>
    </li>
    <li role="presentation">
        <a href="#consent-status" aria-controls="upload" role="tab" data-toggle="tab">
            Consent Status
        </a>
    </li>
</ul>

<!-- Tab panes -->
<div class="tab-content">

    <div role="tabpanel" class="tab-pane active" id="cand-info">
        Candidate info
    </div>

    <div role="tabpanel" class="tab-pane" id="proband-info">
        Proband info
    </div>

    <div role="tabpanel" class="tab-pane" id="family-info">
        Family info
    </div>

    <div role="tabpanel" class="tab-pane" id="participant-status">
        Participant info
    </div>

    <div role="tabpanel" class="tab-pane" id="consent-status">
        Consent Status info
    </div>

</div>

<script>

    var candidateInfo = RCandidateInfo({
        "dataURL": "{$baseurl}/candidate_parameters/ajax/getData.php?data=candidateInfo&candID=" + {$smarty.get.candID},
        "action": "{$baseurl}/candidate_parameters/ajax/formHandler.php",
        "tabName": "candidateInfo"
    });
    React.render(candidateInfo, document.getElementById("cand-info"));
   
    if (loris.config('useProband')) {
        var probandInfo = RProbandInfo({
                "dataURL": "{$baseurl}/candidate_parameters/ajax/getData.php?data=probandInfo&candID=" + {$smarty.get.candID},
                "action": "{$baseurl}/candidate_parameters/ajax/formHandler.php"
                });
        React.render(probandInfo, document.getElementById("proband-info"));
    }

    if (loris.config('useFamilyID')) {
        var familyInfo = RFamilyInfo({
            "dataURL": "{$baseurl}/candidate_parameters/ajax/getData.php?data=familyInfo&candID=" + {$smarty.get.candID},
            "action": "{$baseurl}/candidate_parameters/ajax/formHandler.php"
        });
        React.render(familyInfo, document.getElementById("family-info"));
    }

    var participantStatus = RParticipantStatus({
        "dataURL": "{$baseurl}/candidate_parameters/ajax/getData.php?data=participantStatus&candID=" + {$smarty.get.candID},
        "action": "{$baseurl}/candidate_parameters/ajax/formHandler.php"
    });
    React.render(participantStatus, document.getElementById("participant-status"));

    //if ({$smarty.get.useConsent}) {
        var consentStatus = RConsentStatus({
            "dataURL": "{$baseurl}/candidate_parameters/ajax/getData.php?data=consentStatus&candID=" + {$smarty.get.candID},
            "action": "{$baseurl}/candidate_parameters/ajax/formHandler.php"
        });
        React.render(consentStatus, document.getElementById("consent-status"));
    //}

    // Adds tab href to url + opens tab based on hash on page load
    // See: http://bit.ly/292MDI8
    $(function(){
        var hash = window.location.hash;
        hash && $('ul.nav a[href="' + hash + '"]').tab('show');

        $('.nav-tabs a').click(function (e) {
            $(this).tab('show');
            var scrollmem = $('body').scrollTop() || $('html').scrollTop();
            window.location.hash = this.hash;
            $('html,body').scrollTop(scrollmem);
        });
    });

</script>
