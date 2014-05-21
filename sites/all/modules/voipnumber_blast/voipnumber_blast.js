(function ($) {
Drupal.behaviors.voipnumber_blast = { attach: function (context, settings) {
    //If All Numbers are checked, uncheck other groups
    $('#edit-field-select-destination-und-all').change(function() {
        if ($(this).is(':checked')) {
            $('#edit-field-select-destination').find('input[type=checkbox]:checked').removeAttr('checked');
            $('#edit-field-select-destination-und-all').attr('checked','checked');
        }
    }
    );

    //When group is selected, uncheck All numbers
    $('#edit-field-select-destination input[type=checkbox]').change(function() {
            if ($(this).val() != 'all' && $(this).is(':checked')) {
                $('#edit-field-select-destination-und-all').attr('checked',false);
            }
        }
    );

      $('#contacts-preview').click(function(e) {
          var groupIDs = $("#edit-field-select-destination input:checkbox:checked").map(function(){
              return $(this).val();
          }).get();
          console.log(groupIDs);
          var groupIDsquery = groupIDs.join("+");
          //@todo: change to production url

          if(!groupIDsquery) {
              alert("Please select one or more groups.");
              e.preventDefault();
          }
          else if(groupIDsquery == 'all') {
              $(this).attr("href",  Drupal.settings.basePath +"contacts-preview");
          }
          else {
              groupIDsquery = groupIDsquery.replace("all+", "");
              $(this).attr("href",  Drupal.settings.basePath +"contacts-preview/" + groupIDsquery);
          }
      });
    }
};
})(jQuery);