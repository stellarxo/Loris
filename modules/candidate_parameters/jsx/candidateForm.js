var CandidateForm = React.createClass({

    onSubmit: function (e) {
        e.preventDefault();

    },

   render: function () {
       return (
           <FormElement onSubmit={this.onSubmit}>
               <CandidateInfo dataURL={this.props.dataURL}/>
           </FormElement>
       );
   }

});

var RCandidateForm = React.createFactory(CandidateForm);