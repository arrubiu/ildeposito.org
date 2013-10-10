(function ($) {
  Drupal.behaviors.orbitVimeo = {
    attach: function (context) {
      var f = $('.field-orbit-wrapper iframe');

      if (!f.length) {
        return;
      }

      var url = f.attr('src').split('?')[0];

      // Listen for messages from the player
      if (window.addEventListener){
        window.addEventListener('message', onMessageReceived, false);
      }
      else {
        window.attachEvent('onmessage', onMessageReceived);
      }

      // Handle messages received from the player
      function onMessageReceived(e) {
        var data = JSON.parse(e.data);

        switch (data.event) {
          case 'ready':
            onReady();
            break;

          case 'pause':
            onPause();
            break;

          case 'play':
            onPlay();
            break;

          case 'finish':
            onFinish();
            break;
        }
      }

      // Call the API when a button is pressed
      $('button').on('click', function() {
        post($(this).text().toLowerCase());
      });

      // Helper function for sending a message to the player
      function post(action, value) {
        var data = { method: action };

        if (value) {
          data.value = value;
        }

        f[0].contentWindow.postMessage(JSON.stringify(data), url);
      }

      function onReady() {
        post('addEventListener', 'pause');
        post('addEventListener', 'play');
        post('addEventListener', 'finish');
      }

      function onPause() {
        $('.field-orbit-1').trigger('orbit.play');
      }

      function onPlay() {
        $('.field-orbit-1').trigger('orbit.stop');
      }

      function onFinish() {
        $('.field-orbit-1').trigger('orbit.next');
      }
    }
  }
})(jQuery);