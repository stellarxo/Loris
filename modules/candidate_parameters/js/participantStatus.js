var ParticipantStatus = React.createClass({
    displayName: 'ParticipantStatus',


    getInitialState: function () {
        return {
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

    render: function () {

        if (!this.state.isLoaded) {
            if (this.state.error != undefined) {
                return React.createElement(
                    'div',
                    { className: 'alert alert-danger text-center' },
                    React.createElement(
                        'strong',
                        null,
                        this.state.error
                    )
                );
            }

            return React.createElement(
                'button',
                { className: 'btn-info has-spinner' },
                'Loading',
                React.createElement('span', { className: 'glyphicon glyphicon-refresh glyphicon-refresh-animate' })
            );
        }

        var disabled = true;
        var suboptionsDisabled = true;
        var updateButton = null;
        if (loris.userHasPermission('candidate_parameter_edit')) {
            disabled = false;
            updateButton = React.createElement(ButtonElement, { label: 'Update' });
        }

        var reasonRequired = false;
        var reasonSpecifyRequired = false;
        // Can check if "Required" === 1
        if (this.state.formData.participant_status === "5" || this.state.formData.participant_status === "6") {
            reasonRequired = true;
            suboptionsDisabled = false;
        }

        if (this.state.formData.participant_status !== "1") {
            reasonSpecifyRequired = true;
        }

        return React.createElement(
            FormElement,
            { name: 'participantStatus', onSubmit: this.handleSubmit, ref: 'form', 'class': 'col-md-6' },
            React.createElement(StaticElement, {
                label: 'PSCID',
                text: this.state.Data.pscid
            }),
            React.createElement(StaticElement, {
                label: 'DCCID',
                text: this.state.Data.candID
            }),
            React.createElement(SelectElement, {
                label: 'Participant Status',
                name: 'participant_status',
                options: this.state.Data.statusOptions,
                onUserInput: this.setFormData,
                ref: 'participant_status',
                disabled: disabled,
                required: true
            }),
            React.createElement(SelectElement, {
                label: 'Specify Reason (Required only for status Inactive/Incomplete)',
                name: 'participant_suboptions',
                options: this.state.Data.subOptions,
                onUserInput: this.setFormData,
                ref: 'participant_suboptions',
                disabled: suboptionsDisabled,
                required: reasonRequired
            }),
            React.createElement(TextareaElement, {
                label: 'Comments',
                name: 'reason_specify',
                onUserInput: this.setFormData,
                ref: 'reason_specify',
                disabled: disabled,
                required: reasonSpecifyRequired
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

RParticipantStatus = React.createFactory(ParticipantStatus);