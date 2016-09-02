"use strict";

var FamilyInfo = React.createClass({
    displayName: "FamilyInfo",


    getInitialState: function getInitialState() {
        return {
            "relationshipOptions": {
                "full_sibling": "Full Sibling",
                "half_sibling": "Half Sibling",
                "1st_cousin": "First Cousin"
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
    },

    render: function render() {

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

        var familyMembers = [];
        var familyMemberIDs = this.state.Data.familyCandIDs;
        var relationships = this.state.Data.Relationship_types;
        var i = 1;
        var relationship = null;
        for (var key in familyMemberIDs) {
            if (familyMemberIDs.hasOwnProperty(key) && relationships.hasOwnProperty(key)) {
                relationship = "Relationship_type" + i;
                i++;

                familyMembers.push(React.createElement(StaticElement, {
                    label: "Family Member ID (DCCID)",
                    text: familyMemberIDs[key]['CandID']
                }));
                familyMembers.push(React.createElement(SelectElement, {
                    label: "Relation Type",
                    name: relationship,
                    options: this.state.relationshipOptions,
                    value: relationships[key]['Relationship_type'],
                    onUserInput: this.setFormData,
                    ref: relationship,
                    disabled: disabled,
                    required: true
                }));
                if (loris.userHasPermission('candidate_parameter_edit')) {
                    //familyMembers.push(<ButtonElement label="Delete" />);
                }
            }
        }

        var relationshipRequired = false;
        if (this.state.formData.FamilyCandID !== null && this.state.formData.FamilyCandID !== undefined) {
            relationshipRequired = true;
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
                { name: "familyInfo", onSubmit: this.handleSubmit, ref: "form", "class": "col-md-6" },
                React.createElement(StaticElement, {
                    label: "PSCID",
                    text: this.state.Data.pscid
                }),
                React.createElement(StaticElement, {
                    label: "DCCID",
                    text: this.state.Data.candID
                }),
                familyMembers,
                React.createElement(SelectElement, {
                    label: "Family Member ID (DCCID)",
                    name: "FamilyCandID",
                    options: this.state.Data.candidates,
                    onUserInput: this.setFormData,
                    ref: "FamilyCandID",
                    disabled: disabled,
                    required: false
                }),
                React.createElement(SelectElement, {
                    label: "Relation Type",
                    name: "Relationship_type",
                    options: this.state.relationshipOptions,
                    onUserInput: this.setFormData,
                    ref: "Relationship_type",
                    disabled: disabled,
                    required: relationshipRequired
                }),
                updateButton
            )
        );
    },

    /**
     * Handles form submission
     * @param e
     */
    handleSubmit: function handleSubmit(e) {
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
    },

    /**
     * Display a success/error alert message after form submission
     */
    showAlertMessage: function showAlertMessage() {
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

var RFamilyInfo = React.createFactory(FamilyInfo);