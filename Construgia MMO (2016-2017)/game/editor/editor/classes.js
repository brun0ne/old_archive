class object{
  constructor(x, y, w, img, id, number, col, hid, ent, shadow, scale, gotoMap, gotoMapCoords){
    this.x = x;
    this.y = y;
    this.w = w;
    this.img = img;
    this.id = id;
    this.number = number;
    
    this.gotoMap = gotoMap;
    
    if(gotoMapCoords == null)
      this.gotoMapCoords = {"x" : 0, "y" : 0};
    else
      this.gotoMapCoords = gotoMapCoords;
    
    this.type = "object";
    
    this.collider = col;
    
    if(scale == null)
      this.scale = 100;
    else
      this.scale = scale;
    
    this.hiding = hid;
    
    this.canBeEntered = ent;
    
    this.shadow = shadow;
    
    this.isMoving = false;
  }
  
  Load(i){
    var onClick = `
    if(objects[` + i + `].isMoving == false && action === "move"){
      objects[` + i + `].isMoving = true;
      timeout = 10;

      objects[` + i + `].SelectWindowUpdate();

      selected = objects[` + i + `];

      $("#" + selected.id).css({"outline-width" : "1px"});
    }
    else if(action === "resize"){
      var percent = prompt("Please enter new size (%)", "` + this.scale + `");

      if (percent != null) {
        objects[` + i + `].w = 50 * (percent / 100);
        
        objects[` + i + `].scale = percent;
      
        $("#selected_scale_info").html(percent);

        $("#new_w").attr("placeholder", objects[` + i + `].scale);

        objectsReload();
        Camera_Update();
      }
    }
    else if(action === "delete"){
      removeByAttr(objects, "id", parseInt(this.id));
      
      deleted++;
      
      selectedReset();

      objectsReload();
      Camera_Update();
    }
    else if(action === "select"){
      objects[` + i + `].SelectWindowUpdate();

      selected = objects[` + i + `];

      $("#" + selected.id).css({"outline-width" : "1px"});
    }`;
    
    this.number = i;
    
    this.it = "<img onclick='" + onClick + "' id='" + this.id + "' src='../graphics/" + this.img + "' id='" + this.id + "' style='position: absolute; outline-style: solid; outline-color: black; outline-width: 0px; left: " + this.x + "px; top: " + this.y + "px; width: " + this.w + "px; height: auto;' />";
    
    document.getElementById("objects").innerHTML = document.getElementById("objects").innerHTML + this.it;

    var img = document.getElementById(this.id);

    this.h = img.clientHeight;
    
    if(selected != null){
      if(selected.id == this.id)
        $("#" + selected.id).css({"outline-width" : "1px"});
    }
    
    this.Update();
  }
  
  Update(){
    $(document).mousemove(function(event){
      if(this.isMoving)
        $("#" + this.id).css({"left" : event.pageX, "top" : event.pageY + 2});
    });
  }
  
  SelectWindowUpdate(){
    if(this.collider === true)
      document.getElementById("collidersSelectedChoose").innerHTML = "On";
    else if(this.collider === false)
      document.getElementById("collidersSelectedChoose").innerHTML = "Off";
    
    if(this.hiding === true)
      document.getElementById("hidingSelectedChoose").innerHTML = "On";
    else if(this.hiding === false)
      document.getElementById("hidingSelectedChoose").innerHTML = "Off";
    
    if(this.canBeEntered === true){
      document.getElementById("canEnteredSelectedChoose").innerHTML = "On";
      $("#form_gotomap").fadeIn();
    }
    else if(this.canBeEntered === false){
      document.getElementById("canEnteredSelectedChoose").innerHTML = "Off";
      $("#form_gotomap").fadeOut();
    }
    
    if(this.shadow === true)
      document.getElementById("shadowSelectedChoose").innerHTML = "On";
    else if(this.shadow === false)
      document.getElementById("shadowSelectedChoose").innerHTML = "Off";
    
    $("#selected_is_info").html("1 object selected:");
    $("#selected_id_info").html(this.id);
    $("#selected_x_info").html(this.x);
    $("#selected_w_info").html(this.w);
    $("#selected_scale_info").html(this.scale);
    $("#selected_y_info").html(this.y);
    $("#selected_img_info").html(this.img);

    $("#new_w").attr("placeholder", this.scale);
    $("#new_gotomap").attr("placeholder", this.gotoMap);
    $("#new_gotomap_x").attr("placeholder", this.gotoMapCoords.x);
    $("#new_gotomap_y").attr("placeholder", this.gotoMapCoords.y);
    
    if(selected != null)
      $("#" + selected.id).css({"outline-width" : "0px"});
  }
}

class handle{
  constructor(img){
    this.img = img;
    this.x = 0;
    this.y = 0;
    this.w = 0;
  }
  
  Load(){
    $("#handlerd").attr("src", "../graphics/" + this.img);
    
    $("#handlerd").css({"width" : "50px", "height" : "auto"});
    
    this.w = 50;
  }
  
  Destroy(){
    $("#handlerd").attr("src", "graphics/trans.png");
    handler = null;
  }
}

class map{
  constructor(title, img, b_img, w, h){
    this.title = title;
    
    this.notIMG = img;
    this.notBIMG = b_img;
    
    this.img = "../graphics/" + img;
    this.b_img = "../graphics/" + b_img;
    this.w = w;
    this.h = h;
    
    this.customStart = "";
    this.customUpdate = "";
    
    if(w == null)
      this.w = 0;
    if(h == null)
      this.h = 0;
  }
  
  Load(){
    var img = this.img;
    
    $("body").css({"background" : "url(" + img + ") no-repeat center center fixed"});
    $("body").css({"background-size" : "cover"});
    
    $("#map_name").html(this.title);
    $("#map_leave_area").html('<a href="javascript:mapReset()">[leave it]</a>');
    
    $("#new_map_name").attr("placeholder", this.title);
    
    $("#new_map_ground").attr("placeholder", this.notIMG);

    $("#new_map_ground_layer").attr("placeholder", this.notBIMG);

    $("#new_map_width").attr("placeholder", this.w);

    $("#new_map_height").attr("placeholder", this.h);
  }
  
  unLoad(){
    $("body").css({"background" : "none"});
    
    $("#map_leave_area").html("");
    
    objects = [];
    objectsReload();
    
    camera.x = -$(window).width() / 2;
    camera.y = -$(window).height() / 2;
    Camera_Update();
    
    deleted = 0;
    incrementID = 0;
    
    handler = null;
    
    setAction("select");
    
    updateActionInfo();
    
    selectedReset();
    
    $("#new_map_name").attr("placeholder", "");
      
    $("#new_map_ground").attr("placeholder", "");

    $("#new_map_ground_layer").attr("placeholder", "");

    $("#new_map_width").attr("placeholder", "");

    $("#new_map_height").attr("placeholder", "");
    
    $("#map_name").html("---");
  }
}

class Collider extends object{
  constructor(x, y, w, h, id, number){
    super(x, y, w, id, number);

    this.h = h;
    this.img = "barrier.png";
    this.type = "barrier";
    this.collider = true;
    this.hiding = true;
    this.canBeEntered = false;
    this.shadow = false;
    this.scale = 100;
  }
  
  Load(i){    
    var onClick = `
    if(objects[` + i + `].isMoving == false && action === "move"){
      objects[` + i + `].isMoving = true;
      timeout = 10;

      objects[` + i + `].SelectWindowUpdate();

      selected = objects[` + i + `];

      $("#" + selected.id).css({"outline-width" : "1px"});
    }
    else if(action === "resize"){
      var new_width = prompt("Please enter width: ", "` + this.w + `");
      var new_height = prompt("Please enter height: ", "` + this.h + `");
      
      if (new_width != null && new_height != null) {
        objects[` + i + `].w = new_width;
        objects[` + i + `].h = new_height;
        
        objects[` + i + `].scale = 100;
      
        $("#selected_w_info").html(this.w);
        
        objectsReload();
        Camera_Update();
      }
      else
        alert("This cannot be null!");
    }
    else if(action === "delete"){
      removeByAttr(objects, "id", parseInt(this.id));
      
      deleted++;
      
      selectedReset();

      objectsReload();
      Camera_Update();
    }
    else if(action === "select"){
      objects[` + i + `].SelectWindowUpdate();

      selected = objects[` + i + `];

      $("#" + selected.id).css({"outline-width" : "1px"});
    }`;
    
    this.number = i;
    
    if(this.h == null)
      this.h = 50;
    
    this.it = "<img onclick='" + onClick + "' id='" + this.id + "' src='../graphics/barrier.png" + "' id='" + this.id + "' style='position: absolute; outline-style: solid; outline-color: black; border-style: solid; border-width: 1px; border-color: red; outline-width: 0px; left: " + this.x + "px; top: " + this.y + "px; width: " + this.w + "px; height: " + this.h + "px;' />";
    
    document.getElementById("objects").innerHTML = document.getElementById("objects").innerHTML + this.it;

    var img = document.getElementById(this.id);
    
    if(selected != null){
      if(selected.id == this.id)
        $("#" + selected.id).css({"outline-width" : "1px"});
    }
    
    this.Update();
  }
}