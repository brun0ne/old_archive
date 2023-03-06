var handler = null;

var action = null;

var objects = new Array();

var timeout = 0;

var mapScriptWindowVis = false;

var camera = {"x" : 0, "y" : 0};

var customStart;
var customUpdate;

var selected = null;

var playerStart = {"x" : 0, "y" : 0};

var settingsWindowShow = false;

var actMap = null;

var deleted = 0;

var uploadFileVis = false;

var incrementID = 0;

var mapListVis = false;

var mode = 0;

function basicLoop(){
	
	$(document).mousemove(function(event){
		$("#mouse_x").html(event.pageX + camera.x);
		$("#mouse_y").html(event.pageY + camera.y - 20);
	});
	
	setTimeout("basicLoop()", 500);
}

function toggleMode(x){
	// 0 = objs ; 1 = npcs ;
	
	mode = x;
}

function gotoMapChange(){
	var t = document.forms["form_gotomap"]["new_gotomap"].value;
	var x = document.forms["form_gotomap"]["new_gotomap_x"].value;
	var y = document.forms["form_gotomap"]["new_gotomap_y"].value;
	
	if(t !== "")
		objects[selected.number].gotoMap = t;
	
	if(x !== "" && $.isNumeric(x))
		objects[selected.number].gotoMapCoords.x = parseInt(x);
	
	if(y !== "" && $.isNumeric(y))
		objects[selected.number].gotoMapCoords.y = parseInt(y);
	
	objects[selected.number].SelectWindowUpdate();
	
	document.forms["form_gotomap"].reset();
	
	return false;
}

function putOnTop(){
	if(selected != null){
		
		var tempObj = objects[selected.number];
		
		removeByAttr(objects, "number", tempObj.number);
      
   	deleted++;
		
		objects.push(tempObj);
		
		objectsReload();
		Camera_Update();
	}
	else
		alert("Nothing's selected.");
}

function toggleMapScriptWindow(){
	if(mapScriptWindowVis === true){
    $("#map_script_window").fadeOut();
    
    mapScriptWindowVis = false;
  }
  else if(mapScriptWindowVis === false){
		if(actMap != null){
			$("#map_script_window").fadeIn();
			
			customStart.refresh();
			customUpdate.refresh();
			
			if(actMap.customStart != null)
				customStart.setValue(actMap.customStart);
			
			if(actMap.customUpdate != null)
				customUpdate.setValue(actMap.customUpdate);

			mapScriptWindowVis = true;
		}
		else
			alert("You aren't editing any map!");
  }
}

function toggleMapListWindow(){
  if(mapListVis === true){
    $("#map_list_window").fadeOut();
    
    mapListVis = false;
  }
  else if(mapListVis === false){
    $("#map_list_window").fadeIn();
    
    $("#map_list").html("Loading...");
    
    $.when(AJAX_mapsList()).done(function(response){
      $("#map_list").html(response);
    });
    
    mapListVis = true;
  }
}

function uploadFileToggle(){
  if(uploadFileVis === true){
    $("#file_upload").fadeOut();
    uploadFileVis = false;
  }
  else if(uploadFileVis === false){
    $("#file_upload").fadeIn();
    uploadFileVis = true;
    document.getElementById("fileUploadToggleButton").scrollIntoView({block: "end", behavior: "smooth"});
  }
}

function collidersSelectedChange(){
  if(selected != null){
    var e = document.getElementById("collidersSelectedChoose").innerHTML;

    if(e === "On"){
      objects[selected.number].collider = false;
      document.getElementById("collidersSelectedChoose").innerHTML = "Off";
    }
    else if(e === "Off"){
      objects[selected.number].collider = true;
      document.getElementById("collidersSelectedChoose").innerHTML = "On";
    }
  }
  else
    alert("Nothing is selected!");
}

function hidingSelectedChoose(){
  if(selected != null){
    var e = document.getElementById("hidingSelectedChoose").innerHTML;

    if(e === "On"){
      objects[selected.number].hiding = false;
      document.getElementById("hidingSelectedChoose").innerHTML = "Off";
    }
    else if(e === "Off"){
      objects[selected.number].hiding = true;
      document.getElementById("hidingSelectedChoose").innerHTML = "On";
    }
  }
  else
    alert("Nothing is selected!");
}

function canEnteredSelectedChoose(){
  var e = document.getElementById("canEnteredSelectedChoose").innerHTML;
  
  if(selected != null){
    if(e === "On"){
      objects[selected.number].canBeEntered = false;
      document.getElementById("canEnteredSelectedChoose").innerHTML = "Off";
    }
    else if(e === "Off"){
      objects[selected.number].canBeEntered = true;
      document.getElementById("canEnteredSelectedChoose").innerHTML = "On";
    }
  }
  else
    alert("Nothing is selected!");
	
	objects[selected.number].SelectWindowUpdate();
}

function shadowSelectedChoose(){
  var e = document.getElementById("shadowSelectedChoose").innerHTML;
  
  if(selected != null){
    if(e === "On"){
      objects[selected.number].shadow = false;
      document.getElementById("shadowSelectedChoose").innerHTML = "Off";
    }
    else if(e === "Off"){
      objects[selected.number].shadow = true;
      document.getElementById("shadowSelectedChoose").innerHTML = "On";
    }
  }
  else
    alert("Nothing is selected!");
}

function sizeSelectedChange(){
  var x = document.forms["form_size"]["new_w"].value;
  
  if(selected != null){
    if($.isNumeric(x)){
      if(objects[selected.number] != null){
        objects[selected.number].w = 50 * (x / 100); // "objects[selected.number - deleted]" sometimes is buggy (no idea why) :: maybe solved)
        objects[selected.number].scale = x;

        $("#selected_scale_info").html(x);

        $("#new_w").attr("placeholder", x);
      }
      else
        alert("Error, use resize tool below list of objects.");
    }
    else
      alert("This isn't valid number.")
  }
  else
    alert("Nothing is selected.");
  
  document.forms["form_size"].reset();
  
  objectsReload();
  Camera_Update();
  
  return false;
}

function selectedReset(){
  $("#selected_is_info").html("Nothing's selected.");
  $("#selected_id_info").html("---");
  $("#selected_x_info").html("---");
  $("#selected_y_info").html("---");
  $("#selected_w_info").html("---");
  $("#selected_img_info").html("---");
  document.getElementById("collidersSelectedChoose").innerHTML = "---";
  document.getElementById("hidingSelectedChoose").innerHTML = "---";
  document.getElementById("canEnteredSelectedChoose").innerHTML = "---";
	
	$("#form_gotomap").fadeOut();
	
	$("#new_gotomap").attr("placeholder", "");
	$("#new_gotomap_x").attr("placeholder", "");
	$("#new_gotomap_y").attr("placeholder", "");
  
  if(selected != null)
    $("#" + selected.id).css({"outline-width" : "0px"});
  
  selected = null;
}

function setAction(newAction){
  if(newAction == "delete"){
    action = "delete";
    updateActionInfo();
    
    $("body").css("cursor", "crosshair");
  }
  else if(newAction == "move"){
    action = "move";
    updateActionInfo();
    
    $("body").css("cursor", "move");
  }
  else if(newAction == "resize"){
    action = "resize";
    updateActionInfo();
    
    $("body").css("cursor", "sw-resize");
  } 
  else if(newAction == "select"){
    action = "select";
    updateActionInfo();
    
    $("body").css("cursor", "help");
  }
  else if(newAction == "build"){
    action = "build";
    updateActionInfo();
    
    $("body").css("cursor", "auto");
  }
  else if(newAction == "playerMarker"){
    action = "playerMarker";
    updateActionInfo();
    
    $("body").css("cursor", "crosshair");
    
    timeout = 10;
  }
	else if(newAction == "collider_build"){
    action = "collider_build";
    updateActionInfo();
    
    $("body").css("cursor", "auto");
    
    timeout = 10;
  }
  else if(newAction == null){
    action = null;
    updateActionInfo();
    
    $("body").css("cursor", "auto");
  }
}

function createMap(){
  if (confirm('Are you sure you want to create a new map?')) {
    var name = prompt("Title of new map:", "Unnamed");
    
    if(name != "" && name != null){
      var backg = prompt("Ground image: graphics/...", "background.png");
      
      if(backg != "" && backg != null){
        var backg_b = prompt("Ground layer image: graphics/...", "Icyt_ground.png");
        
        if(backg_b != "" && backg_b != null){
          // Map create ->
          
          if(actMap != null)
            actMap.unLoad();
          
          actMap = new map(name, backg, backg_b, 2000, 2000);
          
          actMap.Load();
          
          // <- Map create
        }
        else
          alert("Map layer image can't be null!");
      }
      else
        alert("Map ground image can't be null!");
    }
    else
      alert("Map name can't be null!");
    
  }
}

function mapReset(){
  if(actMap != null){
    if(confirm("Are you sure you want to leave this map? Did you saved it?")){
      actMap.unLoad();

      actMap = null;
    }
  }
  else
    alert("You aren't editing any map now, so you can't leave it!");
}

function saveMap(){
  if(actMap != null){
    $.when(AJAX_checkMapExist()).done(function(response){
      if(response === "Not"){
        if(confirm("This map doesn't already exist. Do you want to save it as new map?")){
          AJAX_mapSave();
          alert("New map saved.");
        }
      }
      else if(response === "Exist"){
        if(confirm("This map already exist. Do you want to overwrite it?")){
          AJAX_mapSave();
          alert("Map overwrited.");
        }
      }
    });
  }
  else
    alert("There is no map to save!");
}

function loadMap(){
  if(actMap != null){
    if(confirm("Are you sure?")){
      var name = prompt("Title of map to load: ", "");
      
      AJAX_mapLoad(name);
    }
  }
  else{
    var name = prompt("Title of map to load: ", "");
      
    AJAX_mapLoad(name);
  }
}

function deleteMap(){
  if(confirm("Are you sure you want to delete this map? This action is unreversable.")){
    AJAX_mapDelete(actMap.title);
    
    actMap.unLoad();
    actMap = null;
    
    alert("Map deleted successfully.");
  }
}

function objectsReload(){
  $("#objects").empty();
  
  for(i = 0; i < objects.length; i++){
    objects[i].Load(i);
  }
}

function Camera_Update(){
  for(i = 0; i < objects.length; i++){
    $("#" + objects[i].id).css({"left" : objects[i].x - camera.x, "top" : objects[i].y - camera.y});
  }
}

function toggleSettingsWindow(){
  if(settingsWindowShow === true){
    $("#settings_window").fadeOut();
    settingsWindowShow = false;
  }
  else if(settingsWindowShow === false){
   $("#settings_window").fadeIn();
    settingsWindowShow = true; 
  }
}

function Update(){
  if(timeout > 0)
    timeout--;
  
  setTimeout("Update()", 10);
}

function updateActionInfo(){
  var newAct = action;
  
  if(newAct == null)
    newAct = "none";
  
  if(handler != null && action != "build")
    handler.Destroy();
  
  $("#act_action_info").html(newAct);
  
  if(newAct === "playerMarker"){
    $("#playerStartInfo").css({
      "visibility" : "visible"
    });
    
    $("#playerStartInfo").html("X: " + playerStart.x + ", Y: " + playerStart.y);
  }
  else{
    $("#playerStartInfo").css({
      "visibility" : "hidden"
    });
  }
}

var removeByAttr = function(arr, attr, value){
    var i = arr.length;
    while(i--){
       if( arr[i] 
           && arr[i].hasOwnProperty(attr) 
           && (arguments.length > 2 && arr[i][attr] === value ) ){ 

           arr.splice(i,1);
       }
    }
    return arr;
}

function TilesetLoad(){
  $.when(AJAX_do("readObjectsList")).done(function(response){
    var contenerDOM = document.getElementById("inner_container");
    
    for(i = 0; i < response.length; i++){
      var onClick = 'handler = new handle("' + response[i].img + '"); handler.Load(); setAction("build"); timeout = 10;';
      
      contenerDOM.innerHTML = contenerDOM.innerHTML + "<img src='../graphics/" + response[i].img + "' class='clickable pixelated' style='width: 25%; height: auto; margin-top: 5%;' onclick='" + onClick + "'/> "
    }
  });
}

$(document).ready(function(){
	if (!/Android|webOS|iPhone|iPad|iPod|BlackBerry|BB|PlayBook|IEMobile|Windows Phone|Kindle|Silk|Opera Mini/i.test(navigator.userAgent)) {
    $("#mobile_arrows").hide();
	}
	
  camera.x = -$(window).width() / 2;
  camera.y = -$(window).height() / 2;
  
  toggleMapListWindow();
	
	setAction("select");
	
	basicLoop();
  
  $('body').click(function(event) {
    if(timeout <= 0 && event.button == 0){
			var target = $(event.target), article;
			
      if(action === "build"){
        if(actMap != null){
          objects.push(new object(event.pageX + camera.x, event.pageY + camera.y, handler.w, handler.img, incrementID, objects.length, true, true, false, true));
          objectsReload();
          Camera_Update();
					
					selectedReset();
					
          $("#selected_is_info").html("1 object selected:");
          $("#selected_id_info").html(incrementID);
          $("#selected_x_info").html(objects[objects.length - 1].x);
          $("#selected_y_info").html(objects[objects.length - 1].y);
          $("#selected_w_info").html(objects[objects.length - 1].w);
          $("#selected_scale_info").html(objects[objects.length - 1].scale);
          $("#selected_img_info").html(objects[objects.length - 1].img);
          
          document.getElementById("collidersSelectedChoose").innerHTML = "On";
          document.getElementById("hidingSelectedChoose").innerHTML = "On";
          document.getElementById("canEnteredSelectedChoose").innerHTML = "Off";
          document.getElementById("shadowSelectedChoose").innerHTML = "On";

          $("#new_w").attr("placeholder", objects[objects.length - 1].scale);

          selected = objects[objects.length - 1];
          
          $("#" + selected.id).css({"outline-width" : "1px"});
          
          incrementID++;
        }
        else{
          setAction("select");
          alert("You aren't editing any map now!");
        }
      }
      else if(action === "move"){
        for(i = 0; i < objects.length; i++){
          if(objects[i].isMoving){
            objects[i].isMoving = false;
					}
        }
      }
      else if(action === "playerMarker" && timeout <= 0){
        if(actMap != null){
          playerStart.x = event.pageX + camera.x;
          playerStart.y = event.pageY + camera.y - 20;
          updateActionInfo();
        }
        else{
          alert("You aren't editing any map!");
          setAction("select");
        }
      }
			else if(action === "select"){
				if(!target.closest("#objects, #container, #top_options, #selected_window, .clickable").length) {
					selectedReset();
				}
			}
			else if(action === "collider_build"){
				objects.push(new Collider(event.pageX + camera.x, event.pageY + camera.y, 100, 100, incrementID, objects.length, true, true, false, false));
				objectsReload();
				Camera_Update();
				
				selectedReset();
				
				$("#selected_is_info").html("1 object selected:");
				$("#selected_id_info").html(incrementID);
				$("#selected_x_info").html(objects[objects.length - 1].x);
				$("#selected_y_info").html(objects[objects.length - 1].y);
				$("#selected_w_info").html(objects[objects.length - 1].w);
				$("#selected_scale_info").html(objects[objects.length - 1].scale);
				$("#selected_img_info").html(objects[objects.length - 1].img);
				
				document.getElementById("collidersSelectedChoose").innerHTML = "On";
				document.getElementById("hidingSelectedChoose").innerHTML = "On";
				document.getElementById("canEnteredSelectedChoose").innerHTML = "Off";
				document.getElementById("shadowSelectedChoose").innerHTML = "On";
				
				$("#new_w").attr("placeholder", objects[objects.length - 1].scale);
				
				selected = objects[objects.length - 1];
				
				$("#" + selected.id).css({"outline-width" : "1px"});
				
				incrementID++;
			}
    }
  });
  
  $(document).contextmenu(function(){
    if(action != "select"){
      if(handler != null)
        handler.Destroy();
      
      setAction("select");
      return false;
    }
  });
  
  $(document).mousemove(function(event){
    $('#handlerd').css({'top' : event.pageY, 'left' : event.pageX + 2});
    
    for(i = 0; i < objects.length; i++){
      if(objects[i].isMoving){
        objects[i].x = event.pageX + camera.x;
        objects[i].y = event.pageY + 2 + camera.y;
        Camera_Update();
      }
    }
  });
  
  $(document).keydown(function(event) {
		if(!$('input[type=text], textarea').is(":focus")){
			if(event.keyCode == 38 || event.keyCode == 87){ // UP
				camera.y -= 10;
				Camera_Update();
				event.preventDefault();
			}
			if(event.keyCode == 40 || event.keyCode == 83){ // DOWN
				camera.y += 10;
				Camera_Update();
				event.preventDefault();
			}
			if(event.keyCode == 37 || event.keyCode == 65){ // LEFT
				camera.x -= 10;
				Camera_Update();
				event.preventDefault();
			}
			if(event.keyCode == 39 || event.keyCode == 68){ // RIGHT
				camera.x += 10;
				Camera_Update();
				event.preventDefault();
			}
			
			// keyboard shortcuts
			
			if(event.keyCode == 90){ // "Z" key - "playerMarker" action shortcut
				setAction("playerMarker");
			}
			if(event.keyCode == 88){ // "X" key - "delete" action shortcut
				setAction("delete");
			}
			if(event.keyCode == 67){ // "C" key - "move" action shortcut
				setAction("move");
			}
			if(event.keyCode == 86){ // "V" key - "resize" action shortcut
				setAction("resize");
			}
			if(event.keyCode == 66){ // "B" key - "select" action shortcut
				setAction("select");
			}
			if(event.keyCode == 78){ // "N" key - "collider_build" action shortcut
				setAction("collider_build");
			}
			
			if(event.keyCode == 46){ // "DELETE" key - delete selected object
				if(selected != null){
					removeByAttr(objects, "id", parseInt(selected.id));
					
					deleted++;
					
					selectedReset();
					
					objectsReload();
					Camera_Update();
				}
				else
					alert("Nothing's selected!");
			}
		}
	});
  
  shortcut.add("Ctrl+S", function() {
    saveMap();
  });
  
  shortcut.add("Ctrl+R", function() {
    camera.x = -$(window).width() / 2;
    camera.y = -$(window).height() / 2;
    
    Camera_Update();
  });
	
	shortcut.add("Ctrl+L", function() {
    toggleMapListWindow();
  });
	
	customStart = CodeMirror(document.getElementById("map_script_cStart"), {
		mode: "javascript",
		theme: "monokai"
	});
	
	customStart.on("blur", function(){
		if(actMap != null)
			actMap.customStart = customStart.getValue();
		else
			toggleMapScriptWindow();
	});
	
	customUpdate = CodeMirror(document.getElementById("map_script_cUpdate"), {
		mode: "javascript",
		theme: "monokai"
	});
	
	customUpdate.on("blur", function(){
		if(actMap != null)
			actMap.customUpdate = customUpdate.getValue();
		else
			toggleMapScriptWindow();
	});
	
  var ow = $(window).width();
  var oh = $(window).height();
  
  $(window).resize(function() {
    
    camera.x += (ow - $(window).width());
    camera.y += (oh - $(window).height());
    
    ow = $(window).width();
    oh = $(window).height();
    
    Camera_Update();
  });
  
  $("body").children().not("#map_script_window").each(function () {
      $(this).html( $(this).html().replace(/&nbsp;/gi,''));
  });
  
  TilesetLoad();
  
  Update();
});