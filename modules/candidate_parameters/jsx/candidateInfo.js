var CandidateInfo = React.createClass({

    getInitialState: function () {
      return {
          "caveatOptions": {
              "true": "True",
              "false": "False"
          }
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

        return (
            <div>
                <HelpTextElement
                    label="PSCID"
                    text={this.state.Data.pscid}
                />
                <HelpTextElement
                    label="DCCID"
                    text={this.state.Data.candID}
                />
                <SelectElement
                    label="Caveat Emptor flag for Candidate"
                    name="flagged_caveatemptor"
                    options={this.state.caveatOptions}
                />
                <SelectElement
                    label="Reason for Caveat Emptor flag"
                    name="flagged_reason"
                    options={this.state.Data.caveatOptions}
                />
                <TextareaElement
                    label="If Other, please specify"
                    name="flagged_other"
                />

                <ButtonElement
                    label="Update"
                />

            </div>
        );
    }

});

RCandidateInfo = React.createFactory(CandidateInfo);

var ProbandInfo = React.createClass({

    getInitialState: function () {
        return {
            "genderOptions": {
                "male": "Male",
                "female": "Female"
            }
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

        return (
            <div>
                <HelpTextElement
                    label="PSCID"
                    text={this.state.Data.pscid}
                />
                <HelpTextElement
                    label="DCCID"
                    text={this.state.Data.candID}
                />
                <SelectElement
                    label="Proband gender:"
                    name="ProbandGender"
                    options={this.state.genderOptions}
                />
                <SelectElement
                    label="DoB Proband:"
                    name="ProbandDoB"
                    options={this.state.genderOptions}
                />
                <SelectElement
                    label="Confirm DoB Proband:"
                    name="ProbandDoB2"
                    options={this.state.genderOptions}
                />

            </div>
        );
    }

});

RProbandInfo = React.createFactory(ProbandInfo);


var FamilyInfo = React.createClass({

    getInitialState: function () {
        return {
            "genderOptions": {
                "male": "Male",
                "female": "Female"
            }
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

        return (
            <div>
                <HelpTextElement
                    label="PSCID"
                    text={this.state.Data.pscid}
                />
                <HelpTextElement
                    label="DCCID"
                    text={this.state.Data.candID}
                />
                <SelectElement
                    label="Family Member ID: (Enter DCCID)"
                    name="ProbandGender"
                    options={this.state.genderOptions}
                />
                <SelectElement
                    label="Relation Type:"
                    name="ProbandDoB"
                    options={this.state.genderOptions}
                />

            </div>
        );
    }

});

RFamilyInfo = React.createFactory(FamilyInfo);


var ParticipantStatus = React.createClass({

    getInitialState: function () {
        return {
            "genderOptions": {
                "male": "Male",
                "female": "Female"
            }
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

        return (
            <div>
                <HelpTextElement
                    label="PSCID"
                    text={this.state.Data.pscid}
                />
                <HelpTextElement
                    label="DCCID"
                    text={this.state.Data.candID}
                />
                <SelectElement
                    label="Participant Status"
                    name="participant_status"
                    options={this.state.genderOptions}
                />
                <SelectElement
                    label="Specify Reason (Required only for status Inactive/Incomplete)"
                    name="participant_suboptions"
                    options={this.state.genderOptions}
                />
                <SelectElement
                    label="Comments"
                    name="reason_specify"
                    options={this.state.genderOptions}
                />
            </div>
        );
    }

});

RParticipantStatus = React.createFactory(ParticipantStatus);

var ConsentStatus = React.createClass({

    getInitialState: function () {
        return {
            "genderOptions": {
                "male": "Male",
                "female": "Female"
            }
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

        return (
            <div>
                <HelpTextElement
                    label="PSCID"
                    text={this.state.Data.pscid}
                />
                <HelpTextElement
                    label="DCCID"
                    text={this.state.Data.candID}
                />
                <SelectElement
                    label="Consent to Study (required)"
                    name="ProbandGender"
                    options={this.state.genderOptions}
                />
                <SelectElement
                    label="Date of Consent to Study (required)"
                    name="ProbandDoB"
                    options={this.state.genderOptions}
                />
                <SelectElement
                    label="Date of withdrawal of Consent to Study (optional)"
                    name="ProbandGender"
                    options={this.state.genderOptions}
                />
                <SelectElement
                    label="Confirmation Date of withdrawal of Consent to Study (optional)"
                    name="ProbandDoB"
                    options={this.state.genderOptions}
                />


            </div>
        );
    }

});

RConsentStatus = React.createFactory(ConsentStatus);

