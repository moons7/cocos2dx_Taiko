(function(global) {
  function serialize(form){if(!form||form.nodeName!=="FORM"){return }var i,j,q=[];for(i=form.elements.length-1;i>=0;i=i-1){if(form.elements[i].name===""){continue}switch(form.elements[i].nodeName){case"INPUT":switch(form.elements[i].type){case"text":case"hidden":case"password":case"button":case"reset":case"submit":q.push(form.elements[i].name+"="+encodeURIComponent(form.elements[i].value));break;case"checkbox":case"radio":if(form.elements[i].checked){q.push(form.elements[i].name+"="+encodeURIComponent(form.elements[i].value))}break;case"file":break}break;case"TEXTAREA":q.push(form.elements[i].name+"="+encodeURIComponent(form.elements[i].value));break;case"SELECT":switch(form.elements[i].type){case"select-one":q.push(form.elements[i].name+"="+encodeURIComponent(form.elements[i].value));break;case"select-multiple":for(j=form.elements[i].options.length-1;j>=0;j=j-1){if(form.elements[i].options[j].selected){q.push(form.elements[i].name+"="+encodeURIComponent(form.elements[i].options[j].value))}}break}break;case"BUTTON":switch(form.elements[i].type){case"reset":case"submit":case"button":q.push(form.elements[i].name+"="+encodeURIComponent(form.elements[i].value));break}break}}return q.join("&")};
 
 
  function extend(destination, source) {
    for (var prop in source) {
      destination[prop] = source[prop];
    }
  }
 
  if(!Mimi) var Mimi = {};
  if(!Mimi.Signups) Mimi.Signups = {};
 
  Mimi.Signups.EmbedValidation = function() {
    this.initialize();
 
    if(document.addEventListener) {
      this.form.addEventListener('submit', this.onFormSubmit.bind(this));
    } else {
      this.form.attachEvent('onsubmit', this.onFormSubmit.bind(this));
    }
  };
 
  extend(Mimi.Signups.EmbedValidation.prototype, {
    initialize: function() {
      this.form         = document.getElementById('mad_mimi_signup_form');
      this.submit       = document.getElementById('webform_submit_button');
      this.callbackName = 'jsonp_callback_' + Math.round(100000 * Math.random());
    },
 
    onFormSubmit: function(e) {
      e.preventDefault();
 
      this.validate();
      if(this.isValid) {
        this.submitForm();
      } else {
        this.revalidateOnChange();
      }
    },
 
    validate: function() {
      this.isValid = true;
      this.emailValidation();
      this.fieldAndListValidation();
      this.updateFormAfterValidation();
    },
 
    emailValidation: function() {
      var email      = document.getElementById('signup_email'),
          validEmail = /.+@.+\..+/;
 
      if(!validEmail.test(email.value)) {
        this.textFieldError(email);
        this.isValid = false;
      } else {
        this.removeTextFieldError(email);
      }
    },
 
    fieldAndListValidation: function() {
      var fields = this.form.querySelectorAll('.mimi_field.required');
 
      for(var i = 0; i < fields.length; ++i) {
        var field = fields[i],
            type  = this.fieldType(field);
        if(type == 'checkboxes' || type == 'radio_buttons') {
          this.checkboxAndRadioValidation(field);
        } else {
          this.textAndDropdownValidation(field, type);
        }
      }
    },
 
    fieldType: function(field) {
      var type = field.querySelectorAll('.field_type');
 
      if(type.length > 0) {
        return type[0].getAttribute('data-field-type');
      } else if(field.className.indexOf('checkgroup') >= 0) {
        return 'checkboxes';
      } else {
        return 'text_field';
      }
    },
 
    checkboxAndRadioValidation: function(field) {
      var inputs   = field.getElementsByTagName('input'),
          selected = false;
 
      for(var i = 0; i < inputs.length; ++i) {
        var input = inputs[i];
        if((input.type == 'checkbox' || input.type == 'radio') && input.checked) selected = true;
      }
 
      if(selected) {
        field.className = field.className.replace(/ invalid/g, '');
      } else {
        if(field.className.indexOf('invalid') == -1) field.className += ' invalid';
        this.isValid = false;
      }
    },
 
    textAndDropdownValidation: function(field, type) {
      var inputs = field.getElementsByTagName('input');
 
      for(var i = 0; i < inputs.length; ++i) {
        var input = inputs[i];
        if(input.name.indexOf('signup') >= 0) {
          if(type == 'text_field') {
            this.textValidation(input);
          } else {
            this.dropdownValidation(field, input);
          }
        }
      }
      this.htmlEmbedDropdownValidation(field);
    },
 
    textValidation: function(input) {
      if(input.id == 'signup_email') return;
 
      var val = input.value;
      if(val == '') {
        this.textFieldError(input);
        this.isValid = false;
      } else {
        this.removeTextFieldError(input)
      }
    },
 
    dropdownValidation: function(field, input) {
      var val = input.value;
      if(val == '') {
        if(field.className.indexOf('invalid') == -1) field.className += ' invalid';
        this.onSelectCallback(input);
        this.isValid = false;
      } else {
        field.className = field.className.replace(/ invalid/g, '');
      }
    },
 
    htmlEmbedDropdownValidation: function(field) {
      var dropdowns = field.querySelectorAll('.mimi_html_dropdown');
 
      for(var i = 0; i < dropdowns.length; ++i) {
        var dropdown = dropdowns[i],
            val      = dropdown.value;
        if(val == '') {
          if(field.className.indexOf('invalid') == -1) field.className += ' invalid';
          this.isValid = false;
          dropdown.onchange = this.validate.bind(this);
        } else {
          field.className = field.className.replace(/ invalid/g, '');
        }
      }
    },
 
    textFieldError: function(input) {
      input.className   = 'required invalid';
      input.placeholder = input.getAttribute('data-required-field');
    },
 
    removeTextFieldError: function(input) {
      input.className   = 'required';
      input.placeholder = '';
    },
 
    onSelectCallback: function(input) {
      if(typeof Widget == 'undefined' ||
        Widget.BasicDropdown == undefined) return;
 
      var dropdownEl = input.parentNode,
          instances  = Widget.BasicDropdown.instances;
 
      for(var i = 0; i < instances.length; ++i) {
        var instance = instances[i];
        if(instance.wrapperEl == dropdownEl) {
          instance.onSelect = this.validate.bind(this);
        }
      }
    },
 
    updateFormAfterValidation: function() {
      this.form.className   = this.setFormClassName();
      this.submit.value     = this.submitButtonText();
      this.submit.disabled  = !this.isValid;
      this.submit.className = this.isValid ? 'submit' : 'disabled';
    },
 
    setFormClassName: function() {
      var name = this.form.className;
 
      if(this.isValid) {
        return name.replace(/\s?mimi_invalid/, '');
      } else {
        if(name.indexOf('mimi_invalid') == -1) {
          return name += ' mimi_invalid';
        } else {
          return name;
        }
      }
    },
 
    submitButtonText: function() {
      var invalidFields = document.querySelectorAll('.invalid'),
          text;
 
      if(this.isValid || invalidFields == undefined) {
        text = this.submit.getAttribute('data-default-text');
      } else {
        if(invalidFields.length > 1 || invalidFields[0].className.indexOf('checkgroup') == -1) {
          text = this.submit.getAttribute('data-invalid-text');
        } else {
          text = this.submit.getAttribute('data-choose-list');
        }
      }
      return text;
    },
 
    submitForm: function() {
      this.formSubmitting();
 
      var _this = this;
      window[this.callbackName] = function(response) {
        delete window[this.callbackName];
        document.body.removeChild(script);
        _this.onSubmitCallback(response);
      };
 
      var script = document.createElement('script');
      script.src = this.formUrl('json');
      document.body.appendChild(script);
    },
 
    formUrl: function(format) {
      var action  = this.form.action,
          divider = action.indexOf('?') >= 0 ? '&' : '?';
 
      if(format == 'json') action += '.json';
 
      return action + divider + 'callback=' + this.callbackName + '&' + serialize(this.form);
    },
 
    formSubmitting: function() {
      //this.form.className += ' gray';
      this.submit.value = this.submit.getAttribute('data-submitting-text');
      this.submit.disabled = true;
      this.submit.className = 'disabled';
    },
 
    onSubmitCallback: function(response) {
      if(response.success) {
        this.onSubmitSuccess(response.result);
      } else {
        top.location.href = this.formUrl('html');
      }
    },
 
    onSubmitSuccess: function(result) {
      if(result.has_redirect) {
        top.location.href = result.redirect;
      } else if(result.single_opt_in || result.confirmation_html == null) {
        this.disableForm();
       this.updateSubmitButtonText(this.submit.getAttribute('data-thanks'));
      } else {
        this.showConfirmationText(result.confirmation_html);
      }
    },
 
    showConfirmationText: function(html) {
      var fields = this.form.querySelectorAll('.mimi_field');
 
      for(var i = 0; i < fields.length; ++i) {
        fields[i].style['display'] = 'none';
      }
 
      (this.form.querySelectorAll('fieldset')[0] || this.form).innerHTML = html;
    },
 
    disableForm: function() {
      var elements = this.form.elements;
      for(var i = 0; i < elements.length; ++i) {
        elements[i].disabled = true;
      }
    },
 
    updateSubmitButtonText: function(text) {
      this.submit.value = text;
      this.submit.className="button teal";
    },
 
    revalidateOnChange: function() {
      var fields = this.form.querySelectorAll(".mimi_field.required");
 
      for(var i = 0; i < fields.length; ++i) {
        var inputs = fields[i].getElementsByTagName('input');
        for(var j = 0; j < inputs.length; ++j) {
          inputs[j].onchange = this.validate.bind(this);
        }
      }
    }
  });
 
  if (document.addEventListener) {
    document.addEventListener("DOMContentLoaded",
      new Mimi.Signups.EmbedValidation);
  }
  else {
    window.attachEvent('onload', function() {
      new Mimi.Signups.EmbedValidation();
    });
  }
})(this);
