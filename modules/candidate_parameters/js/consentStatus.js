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
            React.createElement(DateElement, {
                label: "Consent to Study (required)",
                name: "ProbandGender"
            }),
            React.createElement(DateElement, {
                label: "Date of Consent to Study (required)",
                name: "ProbandDoB"
            }),
            React.createElement(DateElement, {
                label: "Date of withdrawal of Consent to Study (optional)",
                name: "ProbandGender"
            }),
            React.createElement(DateElement, {
                label: "Confirmation Date of withdrawal of Consent to Study (optional)",
                name: "ProbandDoB"
            })
        );
    }

});

RConsentStatus = React.createFactory(ConsentStatus);