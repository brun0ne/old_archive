function Players_Start(response){
  var playersDOM = [document.getElementById("other_players"), $("#other_players")];
  
  if(playersDOM[1].length){
    playersDOM[1].empty();
  }
  
  for(i = 0; i < response.length; i++){
    if(response[i].ID != USERID){
      var mouseOn = '$("#player_" + "' + response[i].ID + '" + "_name").css({"visibility" : "visible"})';
      var mouseOut = '$("#player_" + "' + response[i].ID + '" + "_name").css({"visibility" : "hidden"});';
      var mouseMove = '$("#player_" + "' + response[i].ID + '" + "_name").css({"left" : event.pageX, "top" : event.pageY + 5})';
      
      var innerContent = "<center>" + response[i].NICK + "<br /><b>LVL:</b> " + response[i].LVL + "</center>";
      
      playersDOM[0].innerHTML = playersDOM[0].innerHTML + "<img id='player_" + response[i].ID + "' style='position: absolute; visibility: hidden;' onmousemove='" + mouseMove + "' onmouseover='" + mouseOn + "' onmouseout='" + mouseOut + "' src='graphics/player/player.png' />";
      playersDOM[0].innerHTML = playersDOM[0].innerHTML + "<div class='name' id='player_" + response[i].ID + "_name' style='position: absolute; visibility: hidden; z-index: 2;'>" + innerContent + "</div>"
    }
  }
}

function Players_Update(){
  var playersDOM = [document.getElementById("other_players"), $("#other_players")];
  
  for(i = 0; i < lastPlayersRes.length; i++){
    var thisPlayerDOM = $("#player_" + lastPlayersRes[i].ID);
    
    if(lastPlayersRes[i].IS === "1"){     
      if(lastPlayersRes[i].ID != USERID){
        $(thisPlayerDOM).css({
          "left" : lastPlayersRes[i].POSX - player.pos_x,
          "top" : lastPlayersRes[i].POSY - player.pos_y,
          "visibility" : "visible"
        });

        if(lastPlayersRes[i].Direction == "up")
            $(thisPlayerDOM).attr("src", "graphics/player/player_back.png");
        else if(lastPlayersRes[i].Direction == "down")
            $(thisPlayerDOM).attr("src", "graphics/player/player.png");
        else if(lastPlayersRes[i].Direction == "right")
            $(thisPlayerDOM).attr("src", "graphics/player/player_right.png");
        else if(lastPlayersRes[i].Direction == "left")
            $(thisPlayerDOM).attr("src", "graphics/player/player_left.png");
      }
      else{
        $(thisPlayerDOM).css({
          "visibility" : "hidden"
        });
      }
    }
    else{
      $(thisPlayerDOM).css({
        "visibility" : "hidden"
      });
    }
  }
  
  // CHECK IS <THIS PLAYER> KICKED / BANNED -->
  
  if(lastPlayersRes[USERIDr] != null){
    OK = lastPlayersRes[USERIDr].OK;

    if(OK != "ok" && licznik <= 0){
      window.location.replace("../index.php?cMsg=You%20have%20been%20kicked%20by%20admin.");
      licznik = 100;
    }
  }
  
  // <--
}