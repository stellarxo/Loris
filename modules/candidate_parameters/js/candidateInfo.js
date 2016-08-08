var CandidateInfo = React.createClass({
    displayName: "CandidateInfo",


    getInitialState: function () {
        return {
            "caveatOptions": {
                "true": "True",
                "false": "False"
            },
            formData: {}
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

        return React.createElement(
            FormElement,
            { onSubmit: this.handleSubmit, ref: "form", name: "candidateInfo" },
            React.createElement(HelpTextElement, {
                label: "PSCID",
                text: this.state.Data.pscid
            }),
            React.createElement(HelpTextElement, {
                label: "DCCID",
                text: this.state.Data.candID
            }),
            React.createElement(SelectElement, {
                label: "Caveat Emptor flag for Candidate",
                name: "flagged_caveatemptor",
                options: this.state.caveatOptions,
                onUserInput: this.setFormData,
                ref: "flagged_caveatemptor"
            }),
            React.createElement(SelectElement, {
                label: "Reason for Caveat Emptor flag",
                name: "flagged_reason",
                options: this.state.Data.caveatOptions,
                onUserInput: this.setFormData,
                ref: "flagged_reason"
            }),
            React.createElement(TextareaElement, {
                label: "If Other, please specify",
                name: "flagged_other",
                onUserInput: this.setFormData,
                ref: "flagged_other"
            }),
            React.createElement(ButtonElement, {
                label: "Update"
            })
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
                    uploadResult: "success",
                    formData: {} // reset form data after successful file upload
                });

                // Iterates through child components and resets state
                // to initial state in order to clear the form
                Object.keys(formRefs).map(function (ref) {
                    if (formRefs[ref].state && formRefs[ref].state.value) {
                        formRefs[ref].state.value = "";
                    }
                });
                // rerender components
                self.forceUpdate();
            },
            error: function (err) {
                var errorMessage = JSON.parse(err.responseText).message;
                self.setState({
                    uploadResult: "error",
                    errorMessage: errorMessage
                });
            }

        });
    }

});

RCandidateInfo = React.createFactory(CandidateInfo);

var ProbandInfo = React.createClass({
    displayName: "ProbandInfo",


    getInitialState: function () {
        return {
            "genderOptions": {
                "male": "Male",
                "female": "Female"
            }
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

        return React.createElement(
            "div",
            null,
            React.createElement(HelpTextElement, {
                label: "PSCID",
                text: this.state.Data.pscid
            }),
            React.createElement(HelpTextElement, {
                label: "DCCID",
                text: this.state.Data.candID
            }),
            React.createElement(SelectElement, {
                label: "Proband gender:",
                name: "ProbandGender",
                options: this.state.genderOptions
            }),
            React.createElement(SelectElement, {
                label: "DoB Proband:",
                name: "ProbandDoB",
                options: this.state.genderOptions
            }),
            React.createElement(SelectElement, {
                label: "Confirm DoB Proband:",
                name: "ProbandDoB2",
                options: this.state.genderOptions
            })
        );
    }

});

RProbandInfo = React.createFactory(ProbandInfo);

var FamilyInfo = React.createClass({
    displayName: "FamilyInfo",


    getInitialState: function () {
        return {
            "genderOptions": {
                "male": "Male",
                "female": "Female"
            }
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

        return React.createElement(
            "div",
            null,
            React.createElement(HelpTextElement, {
                label: "PSCID",
                text: this.state.Data.pscid
            }),
            React.createElement(HelpTextElement, {
                label: "DCCID",
                text: this.state.Data.candID
            }),
            React.createElement(SelectElement, {
                label: "Family Member ID: (Enter DCCID)",
                name: "ProbandGender",
                options: this.state.genderOptions
            }),
            React.createElement(SelectElement, {
                label: "Relation Type:",
                name: "ProbandDoB",
                options: this.state.genderOptions
            })
        );
    }

});

RFamilyInfo = React.createFactory(FamilyInfo);

var ParticipantStatus = React.createClass({
    displayName: "ParticipantStatus",


    getInitialState: function () {
        return {
            "genderOptions": {
                "male": "Male",
                "female": "Female"
            }
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

        return React.createElement(
            "div",
            null,
            React.createElement(HelpTextElement, {
                label: "PSCID",
                text: this.state.Data.pscid
            }),
            React.createElement(HelpTextElement, {
                label: "DCCID",
                text: this.state.Data.candID
            }),
            React.createElement(SelectElement, {
                label: "Participant Status",
                name: "participant_status",
                options: this.state.genderOptions
            }),
            React.createElement(SelectElement, {
                label: "Specify Reason (Required only for status Inactive/Incomplete)",
                name: "participant_suboptions",
                options: this.state.genderOptions
            }),
            React.createElement(SelectElement, {
                label: "Comments",
                name: "reason_specify",
                options: this.state.genderOptions
            })
        );
    }

});

RParticipantStatus = React.createFactory(ParticipantStatus);

var ConsentStatus = React.createClass({
    displayName: "ConsentStatus",


    getInitialState: function () {
        return {
            "genderOptions": {
                "male": "Male",
                "female": "Female"
            }
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

        return React.createElement(
            "div",
            null,
            React.createElement(HelpTextElement, {
                label: "PSCID",
                text: this.state.Data.pscid
            }),
            React.createElement(HelpTextElement, {
                label: "DCCID",
                text: this.state.Data.candID
            }),
            React.createElement(SelectElement, {
                label: "Consent to Study (required)",
                name: "ProbandGender",
                options: this.state.genderOptions
            }),
            React.createElement(SelectElement, {
                label: "Date of Consent to Study (required)",
                name: "ProbandDoB",
                options: this.state.genderOptions
            }),
            React.createElement(SelectElement, {
                label: "Date of withdrawal of Consent to Study (optional)",
                name: "ProbandGender",
                options: this.state.genderOptions
            }),
            React.createElement(DateElement, {
                label: "Confirmation Date of withdrawal of Consent to Study (optional)",
                name: "ProbandDoB"
            })
        );
    }

});

RConsentStatus = React.createFactory(ConsentStatus);