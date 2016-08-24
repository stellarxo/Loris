var FamilyInfo = React.createClass({

    getInitialState: function () {
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

        var familyMembers = [];
        var familyMemberIDs = this.state.Data.familyCandIDs;
        var relationships = this.state.Data.Relationship_types;
        var i = 1;
        var relationship = null;
        for (var key in familyMemberIDs) {
            if (familyMemberIDs.hasOwnProperty(key) && relationships.hasOwnProperty(key)) {
                relationship = "Relationship_type" + i;
                i++;

                familyMembers.push(<StaticElement
                    label="Family Member ID (DCCID)"
                    text={familyMemberIDs[key]['CandID']}
                />);
                familyMembers.push(<SelectElement
                label="Relation Type"
                name={relationship}
                options={this.state.relationshipOptions}
                value={relationships[key]['Relationship_type']}
                onUserInput={this.setFormData}
                ref={relationship}
                disabled={disabled}
                required={true}
                    />);
                if (loris.userHasPermission('candidate_parameter_edit')) {
                    familyMembers.push(<ButtonElement label="Delete"/>);
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

        return (
            <div>
                <div className={alertClass} role="alert" ref="alert-message">
                    {alertMessage}
                </div>

            <FormElement name="familyInfo" onSubmit={this.handleSubmit} ref="form" class="col-md-6">
                <StaticElement
                    label="PSCID"
                    text={this.state.Data.pscid}
                />
                <StaticElement
                    label="DCCID"
                    text={this.state.Data.candID}
                />
                {familyMembers}
                <SelectElement
                    label="Family Member ID (DCCID)"
                    name="FamilyCandID"
                    options={this.state.Data.candidates}
                    onUserInput={this.setFormData}
                    ref="FamilyCandID"
                    disabled={disabled}
                    required={false}
                />
                <SelectElement
                label="Relation Type"
                name="Relationship_type"
                options={this.state.relationshipOptions}
                onUserInput={this.setFormData}
                ref="Relationship_type"
                disabled={disabled}
                required={relationshipRequired}
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
                    updateResult: "success",
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

var RFamilyInfo = React.createFactory(FamilyInfo);
