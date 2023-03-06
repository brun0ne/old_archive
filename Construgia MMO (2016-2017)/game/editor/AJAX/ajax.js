function AJAX_do(action){
  return $.ajax({
    type: "GET",
    url: "server.php",
    data: {action: action},
    dataType:'JSON',
    success: function(response){
      // ...
    },
    error: function(data){
      console.log("AJAX/PHP error : AJAX_do");
    }
  });
}

function AJAX_checkMapExist(){
  return $.ajax({
    type: "GET",
    url: "server.php",
    data: {action: "checkMapExist", name: actMap.title},
    dataType: 'text',
    success: function(response){
      // ...
    },
    error: function(data){
      console.log("AJAX/PHP error : AJAX_do");
    }
  });
}

function AJAX_mapSave(){
  var jObject = {"Objects" : {}};
  var count = 0;
  
  for(i in objects){
    if(objects[i].canBeEntered === true)
      var actObject = {"x" : objects[i].x, "y" : objects[i].y, "w" : objects[i].w, "h" : objects[i].h, "id" : objects[i].id, "img" : objects[i].img, "col" : objects[i].collider, "hiding" : objects[i].hiding, "canEnter" : objects[i].canBeEntered, "gotoMap" : objects[i].gotoMap, "gotoMapCoords" : objects[i].gotoMapCoords, "shadow" : objects[i].shadow, "scale" : objects[i].scale, "type" : objects[i].type};
    else if(objects[i].canBeEntered === false)
      var actObject = {"x" : objects[i].x, "y" : objects[i].y, "w" : objects[i].w, "h" : objects[i].h, "id" : objects[i].id, "img" : objects[i].img, "col" : objects[i].collider, "hiding" : objects[i].hiding, "canEnter" : objects[i].canBeEntered, "shadow" : objects[i].shadow, "scale" : objects[i].scale, "type" : objects[i].type};
    
    jObject["Objects"][i] = actObject;
    count = i;
  }
  
  var count_ = parseInt(count) + parseInt(1);
  
  jObject["Map"] = {"title" : actMap.title, "ground" : actMap.notIMG, "l_ground" : actMap.notBIMG, "w" : actMap.w, "h" : actMap.h, "objects_count" : objects.length, "incrementID" : incrementID, "px" : playerStart.x, "py" : playerStart.y, "cStart" : actMap.customStart, "cUpdate" : actMap.customUpdate};
  
  jObject = JSON.stringify(jObject);
  
  $.ajax({
    type: "POST",
    url: "server.php",
    data: {action: "mapSave", JSONarray: jObject, mapName: actMap.title},
    dataType: 'text',
    success: function(response){
      // ...
    },
    error: function(data){
      console.log("AJAX/PHP error : AJAX_mapSave ; Invalid object: " + jObject);
    }
  });
}

function AJAX_mapLoad(name){
  $.ajax({
    type: "GET",
    url: "server.php",
    data: {action: "mapLoad", name: name},
    dataType: 'JSON',
    success: function(response){
      if(actMap != null){
        actMap.unLoad();
        actMap = null;
      }
      
      selectedReset();
      
      actMap = new map(response.Map.title, response.Map.ground, response.Map.l_ground, response.Map.w, response.Map.h);
      
      actMap.customStart = response.Map.cStart;
      actMap.customUpdate = response.Map.cUpdate;
      
      actMap.Load();
      
      playerStart.x = response.Map.px;
      playerStart.y = response.Map.py;
      
      objects = [];
      
      for(i = 0; i < response.Map.objects_count; i++){
        if(response.Objects[i].type === "object")
          objects.push(new object(response.Objects[i].x, response.Objects[i].y, response.Objects[i].w, response.Objects[i].img, response.Objects[i].id, objects.length, response.Objects[i].col, response.Objects[i].hiding, response.Objects[i].canEnter, response.Objects[i].shadow, response.Objects[i].scale, response.Objects[i].gotoMap, response.Objects[i].gotoMapCoords));
        else if(response.Objects[i].type === "barrier")
          objects.push(new Collider(response.Objects[i].x, response.Objects[i].y, response.Objects[i].w, response.Objects[i].h, response.Objects[i].id, objects.length));
      }
      
      incrementID = response.Map.incrementID;
      
      objectsReload();
      Camera_Update();
    },
    error: function(data){
      alert("This map doesn't exist!");
    }
  });
}

function AJAX_mapDelete(name){
  $.ajax({
    type: "POST",
    url: "server.php",
    data: {action: "mapDelete", name: name},
    dataType: 'text',
    success: function(response){
      // ...
    },
    error: function(data){
      alert("Error");
      console.log("Error : " + data);
    }
  });
}

function AJAX_mapsList(){
  return $.ajax({
    type: "GET",
    url: "server.php",
    data: {action: "getMaps"},
    dataType: 'text',
    success: function(response){
      // ...
    },
    error: function(data){
      alert("Error");
      console.log("Error : " + data);
    }
  });
}