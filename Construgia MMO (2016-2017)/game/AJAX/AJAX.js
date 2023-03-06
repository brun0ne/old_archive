function AJAX_Load(){
  $.ajax({
    type: "GET",
    url: "AJAX/server.php",
    data: {action: "varsLoad"},
    dataType:'JSON',
    success: function(response){
      USERID = parseInt(response.id);
      USERNICK = response.nick;
      USERIDr = USERID - 1; 
      OK = response.ok;
      player.gold = parseInt(response.gold);
      player.LVL = parseInt(response.lvl);
      player.EXP = parseInt(response.exp);
      player.HP = parseInt(response.hp);
      if(parseInt(response.isfirst) == 0){
        player.pos_x = parseInt(response.posx) - $(window).width() * (45/100);
        player.pos_y = parseInt(response.posy) - $(window).height() * (35/100);
        whatLocation = response.Location;
      }
      firstTimePlay = parseInt(response.isfirst);
      
      if(OK != "ok"){
        window.location.replace("../index.php?cMsg=You%20have%20been%20kicked%20by%20admin.");
      }
      location_ = new map(whatLocation);
      
      location_.Load();
      
      AJAX_players("start");
    },
    error: function(){
      console.log("AJAX/DataBase/PHP error : Load");
    }
  });
}

function AJAX_save(){
  $.ajax({
    type: "POST",
    url: "AJAX/server.php",
    data: {action: "varsSave", gold: player.gold, exp: player.EXP, lvl: player.LVL, hp: player.HP, posx: player.pos_x + $(window).width() * (45/100), posy: player.pos_y + $(window).height() * (35/100), location: whatLocation, direction: player.direction},
    dataType: 'JSON',
    success: function(response){
      // ...
    },
    error: function(){
      console.log("AJAX/DataBase/PHP error : Save");
    }
  });
}

function AJAX_getRang(func){
  return $.ajax({
    type: "GET",
    url: "AJAX/server.php",
    data: {action: "getRang"},
    dataType: 'JSON',
    success: function(response){
      lastRang = response;
    },
    error: function(){
      console.log("AJAX/DataBase/PHP error : getRang");
    }
  });
}

function AJAX_players(what){
  $.ajax({
    type: "POST",
    url: "AJAX/server.php",
    data: {action: "players_update", Location: whatLocation},
    dataType:'JSON',
    success: function(response){
      if(what == "update"){
        lastPlayersRes = response;
      }
      else if(what == "start")
        Players_Start(response);
    },
    error: function(data){
      console.log("AJAX/DataBase/PHP error : PLAYERS");
    }
  });
}

function AJAX_chatRead(){
  return $.ajax({
    type: "GET",
    url: "AJAX/chat.php",
    data: {action: "read"},
    dataType: 'text',
    success: function(response){
      // ...
    },
    error: function(){
      console.log("AJAX/FILESYSTEM/PHP error : CHATREAD");
    }
  });
}

function nowTime(){
  var time = new Date(new Date().getTime());
  var hour;
  
  if(time.getMinutes() >= 10){
   hour = time.getHours() + ":" + time.getMinutes();
  }
  else if(time.getMinutes() < 10){
    hour = time.getHours() + ":0" + time.getMinutes();
  }
  
  return hour;
}

function AJAX_chatWrite(mess){
  if(mess != null && mess.length > 1)
    ;
  else
    return false;
  
  $.ajax({
    type: "GET",
    url: "AJAX/chat.php",
    data: {action: "write", message: mess, time: nowTime()},
    dataType: 'text',
    success: function(response){
      // ...
    },
    error: function(data){
      console.log("AJAX/FILESYSTEM/PHP error : CHATWRITE");
    }
  });
}

function AJAX_chatADM(action){
  $.ajax({
    type: "POST",
    url: "AJAX/chat.php",
    data: {action: action},
    dataType: 'text',
    success: function(response){
      // ...
    },
    error: function(data){
      console.log("AJAX/FILESYSTEM/PHP error : CHATADM");
    }
  });
}

function AJAX_mapLoad(name){
  return $.ajax({
    type: "GET",
    url: "editor/server.php",
    data: {action: "mapLoad", name: name},
    dataType: 'JSON',
    success: function(response){
      // ...
    },
    error: function(data){
      location_.unLoad();
      location_ = new map("Icyt_Town");
      location_.Load();
      alert("Map loading error. This map propably doesn't exist.");
    }
  });
}

function AJAX_changeOK_Player(id, newOK){ // player kick / unkick
  $.ajax({
    type: "POST",
    url: "AJAX/server.php",
    data: {action: "setOK", id: id, rang: lastRang, newOK: newOK},
    dataType: 'text',
    success: function(response){
      // ...
    },
    error: function(data){
      alert("AJAX/DATABASE/PHP error : kickPlayer ; " + data);
      console.log(data);
    }
  });
}

function AJAX_locationChange(name){
  $.ajax({
    type: "POST",
    url: "AJAX/server.php",
    data: {action: "locationChange", name: name},
    dataType: 'text',
    success: function(response){
      // ...
    },
    error: function(data){
      alert("AJAX/DATABASE/PHP error : locationChange ; " + data);
      console.log(data);
    }
  });
}