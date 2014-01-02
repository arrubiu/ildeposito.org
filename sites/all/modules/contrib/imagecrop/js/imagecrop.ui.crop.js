
Drupal.Imagecrop.cropUi = Drupal.Imagecrop.cropUi || {};

(function($) { 

$(function () {
  Drupal.Imagecrop.cropUi.initControls();
});  

// Input fields
Drupal.Imagecrop.imageCropWidthField = null;
Drupal.Imagecrop.imageCropHeightField = null;
Drupal.Imagecrop.imageCropXField = null;
Drupal.Imagecrop.imageCropYField = null;
Drupal.Imagecrop.scalingDropdown = null;
Drupal.Imagecrop.rotationDropdown = null;

// Hidden fields
Drupal.Imagecrop.imageCropScaleField = null;
Drupal.Imagecrop.imageCropRotationField = null;

// Hidden data
Drupal.Imagecrop.fid = null;
Drupal.Imagecrop.style = null;
Drupal.Imagecrop.cropFile = null;

/**
 * Init the controls.
 */
Drupal.Imagecrop.cropUi.initControls = function() {
  
  // Store input fields
  var $imagecropform = $('#imagecrop-crop-settings-form');
  Drupal.Imagecrop.imageCropWidthField = $('input[name="image-crop-width"]', $imagecropform);
  Drupal.Imagecrop.imageCropHeightField = $('input[name="image-crop-height"]', $imagecropform);
  Drupal.Imagecrop.imageCropXField = $('input[name="image-crop-x"]', $imagecropform);
  Drupal.Imagecrop.imageCropYField = $('input[name="image-crop-y"]', $imagecropform);
  Drupal.Imagecrop.imageCropScaleField = $('input[name="image-crop-scale"]', $imagecropform);
  
  Drupal.Imagecrop.fid = $('input[name="fid"]', '#imagecrop-crop-settings-form').val();
  Drupal.Imagecrop.style = $('input[name="style"]', '#imagecrop-crop-settings-form').val();
  Drupal.Imagecrop.cropFile = $('input[name="temp-style-destination"]', '#imagecrop-crop-settings-form').val();
  
  Drupal.Imagecrop.scalingDropdown = $('#edit-scaling', '#imagecrop-scale-settings-form');
  Drupal.Imagecrop.scalingDropdown.bind('change', Drupal.Imagecrop.cropUi.applyEffects);
  
  if (Drupal.settings.imagecrop.rotation) {
    Drupal.Imagecrop.rotationDropdown = $('#edit-rotation');
    Drupal.Imagecrop.imageCropRotationField = $('input[name="image-crop-rotation"]');
    Drupal.Imagecrop.rotationDropdown.bind('change', Drupal.Imagecrop.cropUi.applyEffects);
  }
  
  var coordinates = Drupal.Imagecrop.cropUi.getCoordinates();
  
  // Start jcrop
  $('#imagecrop-image').Jcrop(
    {
      bgOpacity: .5,
      minSize: [ Drupal.settings.imagecrop.minWidth, Drupal.settings.imagecrop.minHeight],
      allowResize: Drupal.settings.imagecrop.resizable,
      allowSelect: false,
      aspectRatio: Drupal.settings.imagecrop.aspectRatio,
      handleSize: 9,
      onSelect: Drupal.Imagecrop.cropUi.selectListener,
      setSelect: coordinates
    },
    function() {
      Drupal.Imagecrop.jcrop = this;
    }
  );  
  
  // Event listeners on input fields
  Drupal.Imagecrop.imageCropWidthField.change(Drupal.Imagecrop.cropUi.inputListener);
  Drupal.Imagecrop.imageCropHeightField.change(Drupal.Imagecrop.cropUi.inputListener);
  Drupal.Imagecrop.imageCropXField.change(Drupal.Imagecrop.cropUi.inputListener);
  Drupal.Imagecrop.imageCropYField.change(Drupal.Imagecrop.cropUi.inputListener);
  
}

/**
 * Return an array with all the coordinates.
 */
Drupal.Imagecrop.cropUi.getCoordinates = function() {
  
  var x = Number(Drupal.Imagecrop.imageCropXField.val());
  var y = Number(Drupal.Imagecrop.imageCropYField.val());
  var curr_width = Number(Drupal.Imagecrop.imageCropWidthField.val());
  var curr_height = Number(Drupal.Imagecrop.imageCropHeightField.val());
  
  //add crop width / height to x / y to get x2 / y2
  Drupal.Imagecrop.x2 = Number(curr_width) + x;
  Drupal.Imagecrop.y2 = Number(curr_height) + y;   
  
  return [x, y, Drupal.Imagecrop.x2, Drupal.Imagecrop.y2];
  
}

/**
 * Listener on the jcrop select event.
 */
Drupal.Imagecrop.cropUi.selectListener = function(data) {
  
  Drupal.Imagecrop.imageCropXField.val(Math.round(data.x));
  Drupal.Imagecrop.imageCropYField.val(Math.round(data.y));
  Drupal.Imagecrop.imageCropWidthField.val(data.w);
  Drupal.Imagecrop.imageCropHeightField.val(data.h);
  
  Drupal.Imagecrop.x2 = data.w + data.x;
  Drupal.Imagecrop.y2 = data.h + data.y  
  
}

/**
 * Listener on the input elements.
 */
Drupal.Imagecrop.cropUi.inputListener = function(element) {
  
  Drupal.Imagecrop.jcrop.animateTo(Drupal.Imagecrop.cropUi.getCoordinates(), function() {
    Drupal.Imagecrop.cropUi.selectListener(Drupal.Imagecrop.jcrop.tellSelect());    
  });
  
}

/**
 * Apply the selected effects (rotate / scale) to the image.
 */
Drupal.Imagecrop.cropUi.applyEffects = function() {
  
  var dimensions = Drupal.Imagecrop.scalingDropdown.val().split('x');
  if (dimensions.length != 2) {
    return false;
  }  
  
  // Calculate new x offset, if crop area would go outside image
  if (dimensions[0] < Drupal.Imagecrop.x2) {
  	var x = Drupal.Imagecrop.imageCropXField.val();
  	x = x - (Drupal.Imagecrop.x2 - dimensions[0]);
  	Drupal.Imagecrop.x2 = dimensions[0];
  	Drupal.Imagecrop.imageCropXField.val(x);
  }
  
  // Calculate new y offset, if crop area would go outside image
  if (dimensions[1] < Drupal.Imagecrop.y2) {
  	var y = Drupal.Imagecrop.imageCropYField.val();
  	y = y - (Drupal.Imagecrop.y2 - dimensions[1]);
  	Drupal.Imagecrop.y2 = dimensions[1];
  	Drupal.Imagecrop.imageCropYField.val(y);
  }  
  
  var imagecropData = {
    'fid' : Drupal.Imagecrop.fid,
    'style' : Drupal.Imagecrop.style,
    'scale' : dimensions[0]
  }

  if (Drupal.Imagecrop.rotationDropdown) {
    var rotation = Drupal.Imagecrop.rotationDropdown.val();
    imagecropData.rotation = rotation;
  }
  
  $.ajax({
    url : Drupal.settings.imagecrop.manipulationUrl,
    data : imagecropData,
    type : 'post',
    success : function(result) {
      
      if (result.success) {

        Drupal.Imagecrop.imageCropScaleField.val(dimensions[0]);   
        if (Drupal.Imagecrop.imageCropRotationField) {
          Drupal.Imagecrop.imageCropRotationField.val(rotation);
        }      	
      	
        // force new backgrounds and width / height
        var delimiter = Drupal.Imagecrop.cropFile.indexOf('?') === -1 ? '?' : '&';
        var background = Drupal.Imagecrop.cropFile + delimiter + 'time=' + new Date().getTime();
        Drupal.Imagecrop.jcrop.setImage(background, function() {
        	var coordinates = Drupal.Imagecrop.cropUi.getCoordinates();
          this.animateTo(coordinates);
        });
        
      }
      else {
        alert(result.message);
      }
      
    }
  })
  
}

})(jQuery); 
