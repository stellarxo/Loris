var ConsentStatus = React.createClass({

    getInitialState: function () {
        return {
            "consentOptions": {
                "yes": "Yes",
                "no": "No"
            },
            formData: {}
        }
    },

    componentDidMount: function () {
        var that = this;
        $.ajax(this.props.dataURL, {
            dataType: 'json',
            xhr: function () {
                var xhr = new window.XMLHttpRequest();
                xhr.addEventListener("progress", function (evt) {
                    that.setState({
                        'loadedData': evt.loaded
                    });
                });
                return xhr;
            },
            success: function (data) {
                that.setState({
                    'Data': data,
                    'isLoaded': true
                });
            },
            error: function (data, error_code, error_msg) {
                that.setState({
                    'error': 'An error occurred when loading the form!'
                });
            }
        });
    },

    setFormData: function (formElement, value) {
        var formData = this.state.formData;
        formData[formElement] = value;

        this.setState({
            formData : formData
        });
    },

    onSubmit: function (e) {
        e.preventDefault();

    },

    setFormData: function (formElement, value) {
        var formData = this.state.formData;
        formData[formElement] = value;

        this.setState({
            formData : formData
        });
    },

    onSubmit: function (e) {
        e.preventDefault();

    },

    render: function () {

        if (!this.state.isLoaded) {
            if (this.state.error != undefined) {
                return (
                    <div className="alert alert-danger text-center">
                        <strong>
                            {this.state.error}
                        </strong>
                    </div>
                );
            }

            return (
                <button className="btn-info has-spinner">
                    Loading
                    <span className="glyphicon glyphicon-refresh glyphicon-refresh-animate"></span>
                </button>
            );
        }

        var disabled = true;
        var updateButton = null;
        if (loris.userHasPermission('candidate_parameter_edit')) {
            disabled = false;
            updateButton = <ButtonElement label="Update" />;
        }
        var dateRequired = false;
        var withdrawalRequired = false;
        if (this.state.formData.study_consent === "true") {
            dateRequired = true;
        }
        if (this.state.formData.study_consent_withdrawal !== '') {
            withdrawalRequired = true;
        }

        return (
            <FormElement name="consentStatus" onSubmit={this.handleSubmit} ref="form" class="col-md-6">
                <StaticElement
                    label="PSCID"
                    text={this.state.Data.pscid}
                />
                <StaticElement
                    label="DCCID"
                    text={this.state.Data.candID}
                />
                <SelectElement
                    label="Consent to Study (required)"
                    name="study_consent"
                    options={this.state.consentOptions}
                    onUserInput={this.setFormData}
                    ref="study_consent"
                    disabled={disabled}
                    required={true}
                />
                <DateElement
                    label="Date of Consent to Study (required)"
                    name="study_consent_date"
                    onUserInput={this.setFormData}
                    ref="study_consent_date"
                    disabled={disabled}
                    required={dateRequired}
                />
                <DateElement
                    label="Confirmation Date of Consent to Study (required)"
                    name="study_consent_date2"
                    onUserInput={this.setFormData}
                    ref="study_consent_date2"
                    disabled={disabled}
                    required={dateRequired}
                />
                <DateElement
                    label="Date of withdrawal of Consent to Study (optional)"
                    name="study_consent_withdrawal"
                    onUserInput={this.setFormData}
                    ref="study_consent_withdrawal"
                    disabled={disabled}
                    required={false}
                />
                <DateElement
                    label="Confirmation Date of withdrawal of Consent to Study (optional)"
                    name="study_consent_withdrawal2"
                    onUserInput={this.setFormData}
                    ref="study_consent_withdrawal2"
                    disabled={disabled}
                    required={withdrawalRequired}
                />
                {updateButton}
            </FormElement>
        );
    },

    /**
     * Handles form submission
     * @param e
     */
    handleSubmit: function(e) {
        e.preventDefault();

        var myFormData = this.state.formData;
        var formRefs = this.refs;

        // Set form data and upload the media file
        var self = this;
        var formData = new FormData();
        for (var key in myFormData) {
            if (myFormData[key] != "") {
                formData.append(key, myFormData[key]);
            }
        }

        $.ajax({
            type: 'POST',
            url: self.props.action,
            data: formData,
            cache: false,
            contentType:false,
            processData:false,
            success: function(data) {
                self.setState({
                    uploadResult: "success",
                    formData: {} // reset form data after successful file upload
                });
            },
            error: function(err) {
                var errorMessage = JSON.parse(err.responseText).message;
                self.setState({
                    uploadResult: "error",
                    errorMessage: errorMessage
                });
            }

        });
    }

});

RConsentStatus = React.createFactory(ConsentStatus);

