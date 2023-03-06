function mapNameChange(){
  var x = document.forms["form_map_name"]["new_map_name"].value;
  
  if(actMap != null){
    AJAX_mapDelete(actMap.title);
    
    actMap.title = x;

    actMap.Load();
    
    AJAX_mapSave();
  }
  else
    alert("You aren't editting any map now!");
  
  document.forms["form_map_name"].reset();
  
  return false;
}

function mapGroundChange(){
  var x = document.forms["form_map_ground"]["new_map_ground"].value;
  
  if(actMap != null){
    actMap.img = "../graphics/" + x;
    actMap.notIMG = x;

    actMap.Load();
  }
  else
    alert("You aren't editting any map now!");
  
  document.forms["form_map_ground"].reset();
  
  return false;
}

function mapGroundLayerChange(){
  var x = document.forms["form_map_ground_layer"]["new_map_ground_layer"].value;
  
  if(actMap != null){
    actMap.b_img = "../graphics/" + x;
    actMap.notBIMG = x;

    actMap.Load();
  }
  else
    alert("You aren't editting any map now!");
  
  document.forms["form_map_ground_layer"].reset();
  
  return false;
}

function mapWidthChange(){
  var x = document.forms["form_map_width"]["new_map_width"].value;
  
  if(actMap != null){
    if(!$.isNumeric(x)){
      alert("This isn't valid number!");
      
      document.forms["form_map_width"].reset();
      
      return false;
    }
    
    actMap.w = x;

    actMap.Load();
  }
  else
    alert("You aren't editting any map now!");
  
  document.forms["form_map_width"].reset();
  
  return false;
}

function mapHeightChange(){
  var x = document.forms["form_map_height"]["new_map_height"].value;
  
  if(actMap != null){
    if(!$.isNumeric(x)){
      alert("This isn't valid number!");
      
      document.forms["form_map_height"].reset();
      
      return false;
    }
    
    actMap.h = x;

    actMap.Load();
  }
  else
    alert("You aren't editting any map now!");
  
  document.forms["form_map_height"].reset();
  
  return false;
}