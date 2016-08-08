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
                <DateElement
                    label="Consent to Study (required)"
                    name="ProbandGender"
                />
                <DateElement
                    label="Date of Consent to Study (required)"
                    name="ProbandDoB"
                />
                <DateElement
                    label="Date of withdrawal of Consent to Study (optional)"
                    name="ProbandGender"
                />
                <DateElement
                    label="Confirmation Date of withdrawal of Consent to Study (optional)"
                    name="ProbandDoB"
                />


            </div>
        );
    }

});

RConsentStatus = React.createFactory(ConsentStatus);

