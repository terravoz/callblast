
(function ($) {

  Drupal.behaviors.claro = {
    attach: function (context) {

      $('.page-node-add-phone-number fieldset.node-form-options', context).drupalSetSummary(function (context) {
        var vals = [];

        $('input:checked', context).parent().each(function () {
          vals.push(Drupal.checkPlain($.trim($(this).text())));
        });

        if (!$('.page-node-add-phone-number .form-item-status input', context).is(':checked')) {
          vals.unshift(Drupal.t('Send invitation'));
        }
        return vals.join(', ');
      });

      //Broadcast node form adjustements
      if($('#broadcast-node-form #edit-field-blast-type-und').val() == 'text') {
        $('#broadcast-node-form #edit-field-episode').hide();
      }
      $('#broadcast-node-form #edit-field-blast-type-und').change(function () {
        if($(this).val() == 'episode') {
          $('#broadcast-node-form #edit-field-episode').show();
        }
        else {
          $('#broadcast-node-form #edit-field-episode').hide();
        }
      });

      $('#broadcast-node-form #field-test-phone-number-add-more-wrapper fieldset').hide();

      //Hide admin options from broadcast and episode content types
      $('#broadcast-node-form .vertical-tabs').hide();
      $('#episode-node-form .vertical-tabs').hide();

      //Select all phone numbers
      //$('#broadcast-node-form #edit-field-phone-numbers-und option').attr('selected', 'selected');
      //Hide phone numbers field
      $('#broadcast-node-form #edit-field-phone-numbers').hide();

    }
  };

})(jQuery);
