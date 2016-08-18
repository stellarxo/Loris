var ProbandInfo = React.createClass({

    getInitialState: function () {
        return {
            "genderOptions": {
                "male": "Male",
                "female": "Female"
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
        var updateButton = null;
        if (loris.userHasPermission('candidate_parameter_edit')) {
            disabled = false;
            updateButton = <ButtonElement label="Update" />;
        }

        var dobRequired = false;
        var dob2Required = false;
        if (this.state.formData.ProbandGender !== null) {
            dobRequired = true;
        }
        if (this.state.formData.ProbandDoB !== null) {
            dob2Required = true;
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
            <FormElement name="probandInfo" onSubmit={this.handleSubmit} ref="form" class="col-md-6">
                <StaticElement
                    label="PSCID"
                    text={this.state.Data.pscid}
                />
                <StaticElement
                    label="DCCID"
                    text={this.state.Data.candID}
                />
                <SelectElement
                    label="Proband Gender"
                    name="ProbandGender"
                    options={this.state.genderOptions}
                    onUserInput={this.setFormData}
                    ref="ProbandGender"
                    disabled={disabled}
                    required={true}
                />
                <DateElement
                    label="DoB Proband"
                    name="ProbandDoB"
                    onUserInput={this.setFormData}
                    ref="ProbandDoB"
                    disabled={disabled}
                    required={dobRequired}
                />
                <DateElement
                    label="Confirm DoB Proband"
                    name="ProbandDoB2"
                    onUserInput={this.setFormData}
                    ref="ProbandDoB2"
                    disabled={disabled}
                    required={dob2Required}
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

        var dob1 = myFormData['ProbandDoB'] ? myFormData['ProbandDoB'] : null;
        var dob2 = myFormData['ProbandDoB2'] ? myFormData['ProbandDoB2'] : null;

        if (dob1 !== dob2) {
            alert("DOB do not match!");
            return;
        }

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
                    updateResult: "success",
                    formData: {} // reset form data after successful file upload
                });
            },
            error: function(err) {
                var errorMessage = JSON.parse(err.responseText).message;
                self.setState({
                    updateResult: "error",
                    errorMessage: errorMessage
                });
            },

            success: function(data) {
                $("#file-progress").addClass('hide');
                self.setState({
                    uploadResult: "success"
                });

                self.showAlertMessage();
            }

        });
    }

});

RProbandInfo = React.createFactory(ProbandInfo);
