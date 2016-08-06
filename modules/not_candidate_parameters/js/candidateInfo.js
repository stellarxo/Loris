var CandidateInfo = React.createClass({
    displayName: "CandidateInfo",


    getInitialState: function () {
        return {
            "caveatOptions": {
                "true": "True",
                "false": "False"
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
                label: "CandID",
                text: this.state.Data.candID
            }),
            React.createElement(SelectElement, {
                label: "Caveat Emptor flag for Candidate",
                name: "flagged_caveatemptor",
                options: this.state.caveatOptions
            }),
            React.createElement(SelectElement, {
                label: "Reason for Caveat Emptor flag",
                name: "flagged_reason",
                options: this.state.Data.caveatOptions
            }),
            React.createElement(TextareaElement, {
                label: "If Other, please specify",
                name: "flagged_other"
            }),
            React.createElement(ButtonElement, {
                label: "Update"
            })
        );
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
                label: "CandID",
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
                label: "CandID",
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
                label: "CandID",
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
                label: "CandID",
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

RConsentStatus = React.createFactory(ConsentStatus);