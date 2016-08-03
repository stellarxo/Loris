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
                    'error': 'An error occured when loading the form!'
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
                    label="CandID"
                    text={this.state.Data.candID}
                />
                <SelectElement
                    label="wtv"
                    name="123"
                    options={this.state.caveatOptions}
                />
                <SelectElement
                    label="reason"
                    name="reason"
                    options={this.state.Data.caveatOptions}
                />
                <TextareaElement
                    label="other"
                    name="other"
                />
            </div>
        );
    }

});

RCandidateInfo = React.createFactory(CandidateInfo);