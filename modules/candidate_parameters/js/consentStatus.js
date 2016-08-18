var ConsentStatus = React.createClass({
    displayName: "ConsentStatus",


    getInitialState: function () {
        return {
            "consentOptions": {
                "yes": "Yes",
                "no": "No"
            },
            'Data': [],
            'formData': {},
            'updateResult': null,
            'errorMessage': null,
            'isLoaded': false,
            'loadedData': 0
        };
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
            formData: formData
        });
    },

    onSubmit: function (e) {
        e.preventDefault();
    },

    setFormData: function (formElement, value) {
        var formData = this.state.formData;
        formData[formElement] = value;

        this.setState({
            formData: formData
        });
    },

    onSubmit: function (e) {
        e.preventDefault();
    },

    render: function () {

        if (!this.state.isLoaded) {
            if (this.state.error != undefined) {
                return React.createElement(
                    "div",
                    { className: "alert alert-danger text-center" },
                    React.createElement(
                        "strong",
                        null,
                        this.state.error
                    )
                );
            }

            return React.createElement(
                "button",
                { className: "btn-info has-spinner" },
                "Loading",
                React.createElement("span", { className: "glyphicon glyphicon-refresh glyphicon-refresh-animate" })
            );
        }

        var disabled = true;
        var updateButton = null;
        if (loris.userHasPermission('candidate_parameter_edit')) {
            disabled = false;
            updateButton = React.createElement(ButtonElement, { label: "Update" });
        }
        var dateRequired = false;
        var withdrawalRequired = false;
        if (this.state.formData.study_consent === "true") {
            dateRequired = true;
        }
        if (this.state.formData.study_consent_withdrawal !== null) {
            withdrawalRequired = true;
        }

        var alertMessage = "";
        var alertClass = "alert text-center hide";
        if (this.state.updateResult) {
            if (this.state.updateResult == "success") {
                alertClass = "alert alert-success text-center";
                alertMessage = "Update Successful!";
            } else if (this.state.updateResult == "error") {
                var errorMessage = this.state.errorMessage;
                alertClass = "alert alert-danger text-center";
                alertMessage = errorMessage ? errorMessage : "Failed to update!";
            }
        }

        return React.createElement(
            "div",
            null,
            React.createElement(
                "div",
                { className: alertClass, role: "alert", ref: "alert-message" },
                alertMessage
            ),
            React.createElement(
                FormElement,
                { name: "consentStatus", onSubmit: this.handleSubmit, ref: "form", "class": "col-md-6" },
                React.createElement(StaticElement, {
                    label: "PSCID",
                    text: this.state.Data.pscid
                }),
                React.createElement(StaticElement, {
                    label: "DCCID",
                    text: this.state.Data.candID
                }),
                React.createElement(SelectElement, {
                    label: "Consent to Study (required)",
                    name: "study_consent",
                    options: this.state.consentOptions,
                    onUserInput: this.setFormData,
                    ref: "study_consent",
                    disabled: disabled,
                    required: true
                }),
                React.createElement(DateElement, {
                    label: "Date of Consent to Study (required)",
                    name: "study_consent_date",
                    onUserInput: this.setFormData,
                    ref: "study_consent_date",
                    disabled: disabled,
                    required: dateRequired
                }),
                React.createElement(DateElement, {
                    label: "Confirmation Date of Consent to Study (required)",
                    name: "study_consent_date2",
                    onUserInput: this.setFormData,
                    ref: "study_consent_date2",
                    disabled: disabled,
                    required: dateRequired
                }),
                React.createElement(DateElement, {
                    label: "Date of withdrawal of Consent to Study (optional)",
                    name: "study_consent_withdrawal",
                    onUserInput: this.setFormData,
                    ref: "study_consent_withdrawal",
                    disabled: disabled,
                    required: false
                }),
                React.createElement(DateElement, {
                    label: "Confirmation Date of withdrawal of Consent to Study (optional)",
                    name: "study_consent_withdrawal2",
                    onUserInput: this.setFormData,
                    ref: "study_consent_withdrawal2",
                    disabled: disabled,
                    required: withdrawalRequired
                }),
                updateButton
            )
        );
    },

    /**
     * Handles form submission
     * @param e
     */
    handleSubmit: function (e) {
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
            contentType: false,
            processData: false,
            success: function (data) {
                self.setState({
                    uploadResult: "success"
                });
            },
            error: function (err) {
                var errorMessage = JSON.parse(err.responseText).message;
                self.setState({
                    uploadResult: "error",
                    errorMessage: errorMessage
                });
            }

        });
    },

    /**
     * Display a success/error alert message after form submission
     */
    showAlertMessage: function () {
        var self = this;

        if (this.refs["alert-message"] == null) {
            return;
        }

        var alertMsg = this.refs["alert-message"].getDOMNode();
        $(alertMsg).fadeTo(2000, 500).delay(3000).slideUp(500, function () {
            self.setState({
                updateResult: null
            });
        });
    }

});

RConsentStatus = React.createFactory(ConsentStatus);