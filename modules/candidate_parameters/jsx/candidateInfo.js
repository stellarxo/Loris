var CandidateInfo = React.createClass({

    getInitialState: function () {
      return {
          "caveatOptions": {
              true: "True",
              false: "False"
          },
          'Data': [],
          'formData': {},
          'updateResult': null,
          'errorMessage': null,
          'isLoaded':   false,
          'loadedData': 0
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
        var otherDisabled = true;
        var updateButton = null;
        if (loris.userHasPermission('candidate_parameter_edit')) {
            disabled = false;
            updateButton = <ButtonElement label="Update" />;
        }
        var reasonRequired = false;
        var otherRequired = false;
        if (this.state.formData.flagged_caveatemptor === "true") {
            reasonRequired = true;
        }
        var reasonKey;
        for (var key in this.state.Data.caveatOptions) {
            if (this.state.Data.caveatOptions.hasOwnProperty(key)) {
                if (this.state.Data.caveatOptions[key] === "Other") {
                    reasonKey = key;
                    break;
                }
            }
        }

        if (this.state.formData.flagged_reason === reasonKey) {
            otherRequired = true;
            otherDisabled = false;
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

        return (
            <div>
                <div className={alertClass} role="alert" ref="alert-message">
                    {alertMessage}
                </div>
            <FormElement name="candidateInfo" onSubmit={this.handleSubmit} ref="form" class="col-md-6">
                <StaticElement
                    label="PSCID"
                    text={this.state.Data.pscid}
                />
                <StaticElement
                    label="DCCID"
                    text={this.state.Data.candID}
                />
                <SelectElement
                    label="Caveat Emptor Flag for Candidate"
                    name="flagged_caveatemptor"
                    options={this.state.caveatOptions}
                    onUserInput={this.setFormData}
                    ref="flagged_caveatemptor"
                    disabled={disabled}
                    required={true}
                />
                <SelectElement
                    label="Reason for Caveat Emptor Flag"
                    name="flagged_reason"
                    options={this.state.Data.caveatOptions} // rename to caveat reason options
                    onUserInput={this.setFormData}
                    ref="flagged_reason"
                    disabled={disabled}
                    required={reasonRequired}
                />
                <TextareaElement
                    label="If Other, please specify"
                    name="flagged_other"
                    onUserInput={this.setFormData}
                    ref="flagged_other"
                    disabled={otherDisabled}
                    required={otherRequired}
                />
                {updateButton}
            </FormElement>
            </div>
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

        formData.append('tab', this.props.tabName);
        formData.append('candID', this.state.Data.candID);

        $.ajax({
            type: 'POST',
            url: self.props.action,
            data: formData,
            cache: false,
            contentType:false,
            processData:false,
            success: function(data) {
                self.setState({
                    updateResult: "success"
                });
            },
            error: function(err) {
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
    showAlertMessage: function() {
        var self = this;

        if (this.refs["alert-message"] == null) {
            return;
        }

        var alertMsg = this.refs["alert-message"].getDOMNode();
        $(alertMsg).fadeTo(2000, 500).delay(3000).slideUp(500, function() {
            self.setState({
                updateResult: null
            });
        });
    }

});

var RCandidateInfo = React.createFactory(CandidateInfo);