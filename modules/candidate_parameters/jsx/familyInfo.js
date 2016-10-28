/* exported RFamilyInfo */

var FamilyInfo = React.createClass({
    getInitialState: function() {
      return {
        relationshipOptions: {
          "full_sibling": "Full Sibling",
          "half_sibling": "Half Sibling",
          "1st_cousin": "First Cousin"
        },
        Data: [],
        formData: {},
        familyMembers: [],
        updateResult: null,
        errorMessage: null,
        isLoaded: false,
        loadedData: 0,
          initialized: false
      };
    },
    componentDidMount: function() {
      var that = this;
      $.ajax(
        this.props.dataURL,
        {
          dataType: 'json',
          xhr: function() {
            var xhr = new window.XMLHttpRequest();
            xhr.addEventListener(
              "progress",
              function(evt) {
                that.setState(
                  {
                    loadedData: evt.loaded
                  }
                );
              }
            );
            return xhr;
          },
          success: function(data) {
            that.setState(
              {
                Data: data,
                isLoaded: true
              }
            );
          },
          error: function(data, errorCode, errorMsg) {
            that.setState(
              {
                error: 'An error occurred when loading the form!'
              }
            );
          }
        }
      );
    },
    setFormData: function(formElement, value) {
      var formData = this.state.formData;
      formData[formElement] = value;
      this.setState(
        {
          formData: formData
        }
      );
    },
    onSubmit: function(e) {
      e.preventDefault();
    },
    render: function() {
      if (!this.state.isLoaded) {
        if (this.state.error !== undefined) {
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
            <span
              className="glyphicon glyphicon-refresh
                        glyphicon-refresh-animate"
            >
                    </span>
          </button>
        );
      }

      var disabled = true;
      var addButton = null;
      if (loris.userHasPermission('candidate_parameter_edit')) {
        disabled = false;
        addButton = <ButtonElement label="Add"/>;
      }

      var familyMembers = this.state.familyMembers;
      var familyMembersHTML = [];

      for (var key in familyMembers) {
          if (familyMembers.hasOwnProperty(key)) {

              var candID = familyMembers[key].FamilyCandID;
              var relationship = familyMembers[key].Relationship_type;
              var relationshipID = relationship + " " + key;
              var link = "?candID=" + candID + "&identifier=" + candID;

              familyMembersHTML.push(
                  <div>
                      <StaticElement
                          label="Family Member DCCID"
                          text={<a href={link}>{candID}</a>}
                      />
                      <SelectElement
                          label="Relation Type"
                          name={relationshipID}
                          options={this.state.relationshipOptions}
                          value={relationship}
                          onUserInput={this.setFormData}
                          ref={relationshipID}
                          disabled={true}
                          required={true}
                      />
                      <ButtonElement
                          label="Delete"
                          type="button"
                          onUserInput={this.deleteFamilyMember.bind(null, candID, key)}
                      />
                  </div>
              );

          }
      }

      var existingFamilyMembers = this.state.Data.existingFamilyMembers;
          for (var key2 in existingFamilyMembers) {
              if (existingFamilyMembers.hasOwnProperty(key2)) {

                  // console.log(existingFamilyMembers[key2]);

                  var candID = existingFamilyMembers[key2].CandID;
                  var relationship = existingFamilyMembers[key2].Relationship_type;
                  var relationshipID = relationship + " " + key2;
                  var link = "?candID=" + candID + "&identifier=" + candID;

                  familyMembersHTML.push(
                      <div>
                          <StaticElement
                              label="Family Member DCCID"
                              text={<a href={link}>{candID}</a>}
                          />
                          <SelectElement
                              label="Relation Type"
                              name={relationshipID}
                              options={this.state.relationshipOptions}
                              value={relationship}
                              onUserInput={this.setFormData}
                              ref={relationshipID}
                              disabled={true}
                              required={true}
                          />
                          <ButtonElement
                              label="Delete"
                              type="button"
                              onUserInput={this.deleteFamilyMember.bind(null, candID, key2)}
                          />
                      </div>
                  );

              }
      }

      var relationshipRequired = false;
      if (this.state.formData.FamilyCandID !== null &&
        this.state.formData.FamilyCandID !== undefined
      ) {
        relationshipRequired = true;
      }

      var alertMessage = "";
      var alertClass = "alert text-center hide";
      if (this.state.updateResult) {
        if (this.state.updateResult === "success") {
          alertClass = "alert alert-success text-center";
          alertMessage = "Update Successful!";
        } else if (this.state.updateResult === "error") {
          var errorMessage = this.state.errorMessage;
          alertClass = "alert alert-danger text-center";
          alertMessage = errorMessage ? errorMessage : "Failed to update!";
        }
      }

      return (
        <div class="row">
          <div className={alertClass} role="alert" ref="alert-message">
            {alertMessage}
          </div>

          <FormElement
            name="familyInfo"
            onSubmit={this.handleSubmit}
            ref="form"
            class="col-md-6"
          >
            <StaticElement
              label="PSCID"
              text={this.state.Data.pscid}
            />
            <StaticElement
              label="DCCID"
              text={this.state.Data.candID}
            />
              {familyMembersHTML}
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
            {addButton}
          </FormElement>
        </div>
      );
    },
    /**
     * Handles form submission
     *
     * @param {event} e - Form submission event
     */
    handleSubmit: function(e) {
      e.preventDefault();
      var myFormData = this.state.formData;
      var self = this;
      var formData = new FormData();

      var familyMembers = this.state.familyMembers;
      var familyMember = {};

      for (var key in myFormData) {
        if (myFormData.hasOwnProperty(key)) {
          if (myFormData[key] !== "") {
            familyMember[key] = myFormData[key];
            formData.append(key, myFormData[key]);
          }
        }
      }

      formData.append('tab', this.props.tabName);
      formData.append('candID', this.state.Data.candID);

      familyMembers.push(familyMember);

      this.setState({
        familyMembers: familyMembers
      });

        // TODO : reset form

      $.ajax(
        {
          type: 'POST',
          url: self.props.action,
          data: formData,
          cache: false,
          contentType: false,
          processData: false,
          success: function(data) {
            self.setState({
              updateResult: "success",
                formData: {}
            });
          },
          error: function(err) {
            var errorMessage = JSON.parse(err.responseText).message;
            self.setState(
              {
                updateResult: "error",
                errorMessage: errorMessage
              }
            );
          }

        }
      );
    },
    /**
     * Display a success/error alert message after form submission
     */
    showAlertMessage: function() {
      var self = this;
      if (this.refs["alert-message"] === null) {
        return;
      }

      var alertMsg = this.refs["alert-message"].getDOMNode();
      $(alertMsg).fadeTo(2000, 500).delay(3000).slideUp(
        500,
        function() {
          self.setState(
            {
              updateResult: null
            }
          );
        }
      );
    },
    deleteFamilyMember: function(candID, key) {

      // console.log(candID, key);
      var familyMembers = this.state.familyMembers;
      delete familyMembers[0];

      this.setState({
        familyMembers: familyMembers
      });

      var myFormData = this.state.formData;
      var self = this;
      var formData = new FormData();
      for (var key in myFormData) {
        if (myFormData.hasOwnProperty(key)) {
          if (myFormData[key] !== "") {
            formData.append(key, myFormData[key]);
          }
        }
      }

      // return;
        
      formData.append('tab', 'deleteFamilyMember');
      formData.append('candID', this.state.Data.candID);
      formData.append('familyDCCID', candID);
      // console.log("FAM " + candID);
      for (var field in familyMembers[candID]) {

        if (familyMembers[candID].hasOwnProperty(field)) {
          if (familyMembers[candID][field].ref !== null) {
            var reference = familyMembers[candID][field].ref.split('_', 1);
            if (reference === familyID) {
              familyMembers[candID][field] = null;
            }
          }
        }
      }

      // var updatedFamilyMembers = this.state.familyMembers;
      // updatedFamilyMembers[familyMemberID] = null;

      $.ajax(
        {
          type: 'POST',
          url: self.props.action,
          data: formData,
          cache: false,
          contentType: false,
          processData: false,
          success: function(data) {
            self.setState(
              {
                updateResult: "success",

              }
            );
          },
          error: function(err) {
            if (err.responseText !== "") {
              var errorMessage = JSON.parse(err.responseText).message;
              self.setState(
                {
                  updateResult: "error",
                  errorMessage: errorMessage
                }
              );
            }
          }
        }
      );
    }

  }
);

var RFamilyInfo = React.createFactory(FamilyInfo);
