"use strict";

var _React$createClass;

function _defineProperty(obj, key, value) { if (key in obj) { Object.defineProperty(obj, key, { value: value, enumerable: true, configurable: true, writable: true }); } else { obj[key] = value; } return obj; }

var ConsentStatus = React.createClass((_React$createClass = {
    displayName: "ConsentStatus",


    getInitialState: function getInitialState() {
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

    componentDidMount: function componentDidMount() {
        var that = this;
        $.ajax(this.props.dataURL, {
            dataType: 'json',
            xhr: function xhr() {
                var xhr = new window.XMLHttpRequest();
                xhr.addEventListener("progress", function (evt) {
                    that.setState({
                        'loadedData': evt.loaded
                    });
                });
                return xhr;
            },
            success: function success(data) {
                that.setState({
                    'Data': data,
                    'isLoaded': true
                });
            },
            error: function error(data, error_code, error_msg) {
                that.setState({
                    'error': 'An error occurred when loading the form!'
                });
            }
        });
    },

    setFormData: function setFormData(formElement, value) {
        var formData = this.state.formData;
        formData[formElement] = value;

        this.setState({
            formData: formData
        });
    },

    onSubmit: function onSubmit(e) {
        e.preventDefault();
    }

}, _defineProperty(_React$createClass, "setFormData", function setFormData(formElement, value) {
    var formData = this.state.formData;
    formData[formElement] = value;

    this.setState({
        formData: formData
    });
}), _defineProperty(_React$createClass, "onSubmit", function onSubmit(e) {
    e.preventDefault();
}), _defineProperty(_React$createClass, "render", function render() {

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
    if (this.state.formData.study_consent === "yes") {
        dateRequired = true;
    }
    if (this.state.formData.study_consent_withdrawal !== null && this.state.formData.study_consent_withdrawal !== undefined) {
        console.log(this.state.formData.study_consent_withdrawal);
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
                label: "Date of Consent to Study",
                name: "study_consent_date",
                onUserInput: this.setFormData,
                ref: "study_consent_date",
                disabled: disabled,
                required: dateRequired
            }),
            React.createElement(DateElement, {
                label: "Confirmation Date of Consent to Study",
                name: "study_consent_date2",
                onUserInput: this.setFormData,
                ref: "study_consent_date2",
                disabled: disabled,
                required: dateRequired
            }),
            React.createElement(DateElement, {
                label: "Date of Withdrawal of Consent to Study",
                name: "study_consent_withdrawal",
                onUserInput: this.setFormData,
                ref: "study_consent_withdrawal",
                disabled: disabled,
                required: false
            }),
            React.createElement(DateElement, {
                label: "Confirmation Date of Withdrawal of Consent to Study",
                name: "study_consent_withdrawal2",
                onUserInput: this.setFormData,
                ref: "study_consent_withdrawal2",
                disabled: disabled,
                required: withdrawalRequired
            }),
            updateButton
        )
    );
}), _defineProperty(_React$createClass, "handleSubmit", function handleSubmit(e) {
    e.preventDefault();

    var myFormData = this.state.formData;
    var formRefs = this.refs;

    var date1 = myFormData['study_consent_date'] ? myFormData['study_consent_date'] : null;
    var date2 = myFormData['study_consent_date2'] ? myFormData['study_consent_date2'] : null;

    if (date1 !== date2) {
        alert("Consent to study dates do not match!");
        return;
    }

    var date1 = myFormData['study_consent_withdrawal'] ? myFormData['study_consent_withdrawal'] : null;
    var date2 = myFormData['study_consent_withdrawal2'] ? myFormData['study_consent_withdrawal2'] : null;

    if (date1 !== date2) {
        alert("Consent to study withdrawal dates do not match!");
        return;
    }

    // Set form dataå
    var self = this;
    var formData = new FormData();
    for (var key in myFormData) {
        if (myFormData[key] != "") {
            formData.append(key, myFormData[key]);
        }
    }

    formData.append('tab', this.props.tabName);
    formData.append('candID', this.state.Data.candID);

    $.ajax({
        type: 'POST',
        url: self.props.action,
        data: formData,
        cache: false,
        contentType: false,
        processData: false,
        success: function success(data) {
            self.setState({
                updateResult: "success"
            });
        },
        error: function error(err) {
            var errorMessage = JSON.parse(err.responseText).message;
            self.setState({
                updateResult: "error",
                errorMessage: errorMessage
            });
        }

    });
}), _defineProperty(_React$createClass, "showAlertMessage", function showAlertMessage() {
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
}), _React$createClass));

var RConsentStatus = React.createFactory(ConsentStatus);