var CandidateForm = React.createClass({
    displayName: "CandidateForm",


    render: function () {
        return React.createElement(
            FormElement,
            null,
            React.createElement(CandidateInfo, { dataURL: this.props.dataURL })
        );
    }

});

var RCandidateForm = React.createFactory(CandidateForm);