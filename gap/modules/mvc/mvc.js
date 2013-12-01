/**
 * The page callback for collection/list/%/%.
 */
function collection_list_page(module, type) {
  try {
    var content = {
      'collection_list':{
        'theme':'jqm_item_list',
        'title':'Collection'
      }
    };
    var items = [];
    var collection = collection_load(module, type);
    if (collection) {
      $.each(collection, function(id, item){
          var path = 'item/' + module + '/' + type + '/' + id;
          items.push(l(item.name, path));
      });
      content.collection_list.items = items;  
    }
    return content;
  }
  catch (error) {
    alert('collection_list_page - ' + error);
  }
}

/**
 * Given a module name and model type, this will return the collection JSON object.
 */
function collection_load(module, type) {
  try {
    return JSON.parse(window.localStorage.getItem(mvc_get_collection_key('collection', module, type)));
  }
  catch (error) {
    alert('collection_load - ' + error);
  }
}

/**
 * Given a module name, model type and item collection, this will save the
 * collection JSON object to local storage.
 */
function collection_save(module, type, collection) {
  try {
    window.localStorage.setItem(mvc_get_collection_key('collection', module, type), JSON.stringify(collection));
  }
  catch (error) {
    alert('collection_save - ' + error);
  }
}

/**
 * Given a bucket (e.g. collection, settings), module name and mvc model type,
 * this will return the local storage key used for the model type's item collection.
 */
function mvc_get_collection_key(bucket, module, model_type) {
  try {
    return 'mvc_' + bucket + '_' + module + '_' + model_type;
  }
  catch (error) {
    alert('mvc_get_collection_key - ' + error);
  }
}

/**
 * Implements hook_install().
 */
function mvc_install() {
  try {
    if (drupalgap.settings.debug) {
      console.log('mvc_install()');
    }
    // Load models...
    // For each module that implements hook_mvc_model(), iterate over each model
    // placing it into drupalgap.mvc.models, each model will be placed into
    // a namespace according to the module that implements it, to avoid namespace
    // collisions.
    var modules = module_implements('mvc_model');
    for (var i = 0; i < modules.length; i++) {
      var module = modules[i];
      var models = module_invoke(module, 'mvc_model');
      if (models) {
        // Create namespace for model, keyed by module name.
        if (!eval('drupalgap.mvc.models.' + module)) {
          eval('drupalgap.mvc.models.' + module + ' = {};');
        }
        // For each model type...
        $.each(models, function(model_type, model){
            // Set the primary key 'id', the module name, and model type
            // on the model fields. These are the mvc_model_system_fields().
            model.fields.id = {
              "type":"hidden",
              "title":"ID",
              "required":false
            };
            model.fields.module = {
              "type":"hidden",
              "title":"Module",
              "required":true,
              "default_value":module,
            };
            model.fields.type = {
              "type":"hidden",
              "title":"Model Type",
              "required":true,
              "default_value":model_type,
            };
            // Add each model type to its namespace within drupalgap.mvc.models
            eval('drupalgap.mvc.models.' + module + '.' + model_type + ' = model;');
            // Save an empty collection to local storage for this model type.
            window.localStorage.setItem(
              mvc_get_collection_key('collection', module, model_type),
              '[]'
            );
            // Save settings for the collection to local storage. The auto
            // increment value represents an item id, we start counting at zero
            // since the collection is an array.
            window.localStorage.setItem(
              mvc_get_collection_key('settings', module, model_type),
              '{"auto_increment":0}'
            );
        });
      }
    }
    //console.log(JSON.stringify(drupalgap.mvc.models));
    //alert('drupalgap_mvc_init');
    // These may not be needed. Perhaps we should just call assumed hooks that
    // should be implemented for any custom views and controllers at the time
    // they are needed, probably no need to bundle them inside drupalgap.mvc.
    //var views = module_invoke_all('mvc_view');
    //var controllers = module_invoke_all('mvc_controller');
  }
  catch (error) {
    alert('mvc_install - ' + error);
  }
}

/**
 * Implements hook_menu().
 */
function mvc_menu() {
  try {
    var items = {
      'collection/list/%/%':{
        'page_callback':"collection_list_page",
        "page_arguments":[2, 3]
      },
      'item/%/%/%':{
        'page_callback':"item_view_page",
        "page_arguments":[1, 2, 3]
      }
    };
    return items;
  }
  catch (error) {
    alert('mvc_menu - ' + error);
  }
}

function mvc_model_system_fields() {
  return ['id', 'module', 'type'];
}

// We'll need developer friendly front end functions, e.g.
// model_load();
// model_save();
// model_delete();
// item_load();
// item_save();
// item_delete();
// etc...

/**
 * Given a module name and a corresponding model name, this will load the model
 * from drupalgap.mvc.models.
 */
function model_load(module, name) {
  try {
    if (drupalgap.settings.debug) {
      console.log('model_load(' + module + ', ' + name + ')');
    }
    if (drupalgap.mvc.models[module] === 'undefined' || drupalgap.mvc.models[module][name] === 'undefined') {
      return false;
    }
    return drupalgap.mvc.models[module][name];
  }
  catch (error) {
    alert('model_load - ' + error);
  }
}

/**
 * Given a module type, and model type, this generates and returns the form JSON
 * object to create a model item.
 */
function drupalgap_mvc_model_create_form(module, type) {
   try {
    if (drupalgap.settings.debug) {
      console.log('drupalgap_mvc_model_create_form(' + module + ', ' + type + ')');
    }
    var form = drupalgap_form_defaults('drupalgap_mvc_model_create_form');
    var model = model_load(module, type);
    if (model) {
      // TODO - this could be dangerous just overriding the elements variable, we
      // should iterate over the model fields and add them one by one instead.
      form.elements = model.fields;
      form.buttons.cancel = {"title":"Cancel"};
      form.elements.submit = {
        type:"submit",
        value:"Create"
      };
    }
    return form;
  }
  catch (error) {
    alert('drupalgap_mvc_model_create_form - ' + error);
  }
}

/**
 * Handles the submission of an mvc model item creation form.
 */
function drupalgap_mvc_model_create_form_submit(form, form_state) {
  try {
    // Save the item and then view it.
    if (item_save(form_state.values)) {
      /*var path = 'item/' +
                 form_state.values.module + '/' +
                 form_state.values.type + '/' +
                 form_state.values.id;*/
      var path = 'collection/list/' +
                 form_state.values.module + '/' +
                 form_state.values.type;
      drupalgap_goto(path);
    }
    else {
      alert('drupalgap_mvc_model_create_form_submit - failed to save item!');
    }
  }
  catch (error) {
    alert('drupalgap_mvc_model_create_form_submit - ' + error);
  }
}

/**
 * Given a module name, mvc model type, and item id, this will return the item,
 * or false if the item fails to load.
 */
function item_load(module, type, id) {
  try {
    var item = false;
    var collection = collection_load(module, type);
    if (collection && typeof collection[id] !== 'undefined') {
      item = collection[id];
    }
    return item; 
  }
  catch (error) {
    alert('item_load - ' + error);
  }
}

/**
 * Given an mvc item, this saves it to local storage.
 */
function item_save(item) {
  try {
    if (typeof item === 'undefined') { return false; }
    
    // Grab the settings for this collection.
    var settings_key = mvc_get_collection_key('settings', item.module, item.type);
    var settings = JSON.parse(window.localStorage.getItem(settings_key));
    
    // If there is no id, then this is a new item, grab the next id to use.
    if (!item.id) {
      item.id = settings.auto_increment;
    }
    // Load the collection from local storage.
    var collection = collection_load(item.module, item.type);
    
    // Add the item onto the collection.
    collection[item.id] = item; 
      
    // Save the collection to local storage.
    collection_save(item.module, item.type, collection);
    
    // Increment to the next item id and save the settings.
    settings.auto_increment = item.id + 1;
    window.localStorage.setItem(settings_key, JSON.stringify(settings));
    
    if (drupalgap.settings.debug) {
      console.log('item_save - saved item!');
      console.log(JSON.stringify(item));
    }
    
    return true;
  }
  catch (error) {
    alert('item_save - ' + error);
  }
}

/**
 * The page callback for item/%/%/%.
 */
function item_view_page(module, type, item) {
  try {
    console.log(JSON.stringify(arguments));
    var html = '';
    var model = model_load(module, type);
    if (model) {
      html = theme('item', {"model":model, "item":item});
    }    
    return html;
  }
  catch (error) {
    alert('item_view_page - ' + error);
  }
}

