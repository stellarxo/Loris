var ProbandInfo = React.createClass({
    displayName: "ProbandInfo",


    getInitialState: function () {
        return {
            "genderOptions": {
                "male": "Male",
                "female": "Female"
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

        var disabled = true;
        var updateButton = null;
        if (loris.userHasPermission('candidate_parameter_edit')) {
            disabled = false;
            updateButton = React.createElement(ButtonElement, { label: "Update" });
        }

        var dobRequired = false;
        var dob2Required = false;
        if (this.state.formData.ProbandGender !== null) {
            dobRequired = true;
        }
        if (this.state.formData.ProbandDoB !== null) {
            dob2Required = true;
        }

        return React.createElement(
            FormElement,
            { name: "probandInfo", onSubmit: this.handleSubmit, ref: "form", "class": "col-md-6" },
            React.createElement(StaticElement, {
                label: "PSCID",
                text: this.state.Data.pscid
            }),
            React.createElement(StaticElement, {
                label: "DCCID",
                text: this.state.Data.candID
            }),
            React.createElement(SelectElement, {
                label: "Proband Gender",
                name: "ProbandGender",
                options: this.state.genderOptions,
                onUserInput: this.setFormData,
                ref: "ProbandGender",
                disabled: disabled,
                required: true
            }),
            React.createElement(DateElement, {
                label: "DoB Proband",
                name: "ProbandDoB",
                onUserInput: this.setFormData,
                ref: "ProbandDoB",
                disabled: disabled,
                required: dobRequired
            }),
            React.createElement(DateElement, {
                label: "Confirm DoB Proband",
                name: "ProbandDoB2",
                onUserInput: this.setFormData,
                ref: "ProbandDoB2",
                disabled: disabled,
                required: dob2Required
            }),
            updateButton
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

RProbandInfo = React.createFactory(ProbandInfo);