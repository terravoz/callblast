(function ($) {
  Drupal.behaviors.voipvoice = {};
  Drupal.behaviors.voipvoice.attach = function (context, settings) {
    $('.voipvoice-uploaders').find('div.source-upload').css('display', 'none');
    $(".sources-list a").click(function(){
      $Element = $(this).parents('div.voipvoice-uploaders');
      var fileFieldSourceClass = this.className.match(/source-[0-9a-z]+/i)[0];
      $Element.find('div.source').not('div.' + fileFieldSourceClass).css('display', 'none');
      $Element.find('div.' + fileFieldSourceClass).css('display', '');
    });

    $("#voipvoice-manage-recordings-form .audiorecorderfield-remove").click(function(){
      var pid = $(this).parent().parent().attr("id");
      pid = pid.replace("audiorecorderfield-voipvoice-","");
      pid = pid.replace("-wrapper","");
      var old_pids = $("#edit-to-delete").val();
      $("#edit-to-delete").val(old_pids + pid + " ");
    });
  };
})(jQuery);
