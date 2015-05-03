(function ($) {
    Drupal.behaviors.voipnumber_blast = {
        attach: function (context, settings) {
            //If All Numbers are checked, uncheck other groups
            $('#edit-field-select-destination-und-all').change(function () {
                    if ($(this).is(':checked')) {
                        $('#edit-field-select-destination').find('input[type=checkbox]:checked').removeAttr('checked');
                        $('#edit-field-select-destination-und-all').attr('checked', 'checked');
                    }
                }
            );

            //When group is selected, uncheck All numbers
            $('#edit-field-select-destination input[type=checkbox]').change(function () {
                    if ($(this).val() != 'all' && $(this).is(':checked')) {
                        $('#edit-field-select-destination-und-all').attr('checked', false);
                    }
                }
            );

            voipnumber_blast_field_conditional_state($('#edit-field-blast-type-und').val());
            $('#edit-field-blast-type-und').change(function () {
                    voipnumber_blast_field_conditional_state($(this).val());
                    if($(this).val() == 'sms_optin') {
                        $('#edit-body-und-0-value').val(Drupal.settings.voipnumber_blast.opt_in_message);
                    }
                    else {
                        $('#edit-body-und-0-value').val('');
                    }
                }
            );
            $('#contacts-preview').click(function (e) {
                var groupIDs = $("#edit-field-select-destination input:checkbox:checked").map(function () {
                    return $(this).val();
                }).get();
                console.log(groupIDs);
                var groupIDsquery = groupIDs.join("+");
                //@todo: change to production url

                if (!groupIDsquery) {
                    alert("Please select one or more groups.");
                    e.preventDefault();
                }
                else if (groupIDsquery == 'all') {
                    $(this).attr("href", Drupal.settings.basePath + "contacts-preview");
                }
                else {
                    groupIDsquery = groupIDsquery.replace("all+", "");
                    $(this).attr("href", Drupal.settings.basePath + "contacts-preview/" + groupIDsquery);
                }
            });
        }
    };

    function voipnumber_blast_field_conditional_state(val) {
        //Replace field_conditional_field module with custom JS
        $('#broadcast-node-form #edit-body').hide();
        $('#broadcast-node-form #edit-field-voice-announcement').hide();
        $('#broadcast-node-form #edit-field-voice-audio').hide();
        $('#broadcast-node-form #edit-field-voip-script').hide();
        $('#broadcast-node-form #edit-field-blast-voice').hide();
        switch (val) {
            case 'sms':
                $('#broadcast-node-form #edit-body').show();
                break;
            case 'sms_optin':
                $('#broadcast-node-form #edit-body').show();
                break;
            case 'voice_text':
                $('#broadcast-node-form #edit-field-voice-announcement').show();
                $('#broadcast-node-form #edit-field-blast-voice').show();
                break;
            case 'voice_audio':
                $('#broadcast-node-form #edit-field-voice-audio').show();
                break;
            case 'voice_script':
                $('#broadcast-node-form #edit-field-voip-script').show();
                break;
        }
    }
})(jQuery);