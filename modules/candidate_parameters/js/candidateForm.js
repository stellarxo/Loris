var CandidateForm = React.createClass({
    displayName: "CandidateForm",


    onSubmit: function (e) {
        e.preventDefault();
    },

    render: function () {
        return React.createElement(
            FormElement,
            { onSubmit: this.onSubmit },
            React.createElement(CandidateInfo, { dataURL: this.props.dataURL })
        );
    }

});

var RCandidateForm = React.createFactory(CandidateForm);