var logs = 0;

var console_content = "";
var console_show = false;

function validateForm(){
  $.when(AJAX_getRang()).done(function(response){
    var x = document.forms["form_console"]["text_"].value;
    var x2 = document.forms["form_console"]["text_2"].value;
  
    if(x == null || x === "") {
      Log("There is nothing here. Srsly.");
      document.forms["form_console"].reset();
      return false;
    }
    else if(x == "music" && x2 == "off"){ // music off
      audio.pause();
      $("#music_toggle").attr("src", "graphics/music_toggle.png");
      music = false;
      Log("Music turned off.");
      document.forms["form_console"].reset();
      return false;
    }
    else if(x == "music" && x2 == "on"){ // music on
      audio.play();
      $("#music_toggle").attr("src", "graphics/music_toggle_off.png");
      music = true;
      Log("Music turned on.");
      document.forms["form_console"].reset();
      return false;
    }
    else if(x == "cls"){ // cls
      console_content = "";
		  logs = 0;
		  Log("Console cleared.");
      document.forms["form_console"].reset();
      return false;
    }
    else if(response != "admin"){
      Log("I don't get it.");
      document.forms["form_console"].reset();
      return false;
    }
    else if(response == "admin"){
      if(x == "gold add" && x2 != ""){
        player.gold += parseInt(x2);
        Log("Added " + x2 + " gold.");
				document.forms["form_console"].reset();
        return false;
      }
			else if(x == "gold set" && x2 != ""){
        player.gold = parseInt(x2);
        Log("You have " + x2 + " gold now.");
				document.forms["form_console"].reset();
        return false;
      }
      else if(x == "col" && x2 == "off"){
        player.collision = false;
				canUp = true;
				canDown = true;
				canLeft = true;
				canRight = true;
				Log("Player collisions disabled.");
				document.forms["form_console"].reset();
        return false;
      }
      else if(x == "col" && x2 == "on"){
        player.collision = true;
				canUp = true;
				canDown = true;
				canLeft = true;
				canRight = true;
				Log("Player collisions enabled.");
				document.forms["form_console"].reset();
        return false;
      }
      else if(x == "health" && x2 == "max"){ // max health
        Log("Health maximized.");
        player.HP = 100;
        document.forms["form_console"].reset();
        return false;
      }
      else if(x == "chat"){ // chat commands
        if(x2 == "cls"){
          var chatx = document.forms["form_chat"];
          chatx.reset();
          AJAX_chatADM("clear");
          Log("Chat cleared.");
        }
        document.forms["form_console"].reset();
        return false;
      }
      else if(x == "tp"){ // tp
        if(x2 != null || x2 != ""){
          if(x2 === "spawn"){
            player.pos_x = 0;
            player.pos_y = 0;
            Log("Teleported to <b>(0, 0)</b>.");
          }
          else{
            for(i = 0; i <= lastPlayersRes.length; i++){
              if(lastPlayersRes[i].NICK === x2){
                player.pos_x = parseInt(lastPlayersRes[i].POSX) - $(window).width() * (45/100);
                player.pos_y = parseInt(lastPlayersRes[i].POSY) - $(window).height() * (35/100);
								
                Log("Teleported to <b>" + lastPlayersRes[i].NICK + "</b>.");
                document.forms["form_console"].reset();
                break;
              }
            }
          }
					location_.unLoad();
					location_.Load();
					
					canUp = true;
					canDown = true;
					canLeft = true;
					canRight = true;
        }
        else{
          Log("Second input cannot be empty.");
        }
        document.forms["form_console"].reset();
        return false;
      }
			else if(x == "kick" && x2 != null){
				for(i = 0; i <= lastPlayersRes.length; i++){
					if(lastPlayersRes[i].NICK === x2 && lastPlayersRes[i].NICK != USERNICK){
						
						AJAX_changeOK_Player(parseInt(lastPlayersRes[i].ID), "notOK");
						
						Log("You kicked <b>" + x2 + "</b> from the game.");
						
            var i = i;
            
            canExit = false;
            
						setTimeout(function(){
							AJAX_changeOK_Player(parseInt(lastPlayersRes[i].ID), "ok");
              canExit = true;
						}, 2000);
						
						document.forms["form_console"].reset();
						break;
					}
				}
			}
			else if(x === "map load" && x2 !== ""){
				gotoMap(x2, 0, 0);
			}
			else if(x === "add" && x2 !== ""){
				if(x2 === "test missile"){
					EQ.AddItem("canon", "TestMissile", "graphics/canons/iron_canon_2.png", 0.5, 5, 50, 0);
				}
				else if(x2 === "test food"){
					EQ.AddItem("food", "Apple", "graphics/food/apple.png", 0, 0, 0, 10);
				}
				document.forms["form_console"].reset();
				return false;
			}
      else{
        Log("This command doen't exist.");
        document.forms["form_console"].reset();
        return false;
      }
      document.forms["form_console"].reset();
      return false;
    }
    rang = null;
  });
  return false;
}

function Log(tekst){
	var dzisiaj = new Date();
	
	var hour = dzisiaj.getHours();
	if(hour < 10)
		hour = "0" + hour;
	var minute = dzisiaj.getMinutes();
	if(minute < 10)
		minute = "0" + minute;
	var second = dzisiaj.getSeconds();
	if(second < 10)
		second = "0" + second;
	if(logs <= 13){
		console_content = tekst + " [" + hour + ":" + minute + ":" + second + "]" + "<br />" + console_content;
		document.getElementById("console").innerHTML = console_content;
	}
	else{
		console_content = "";
		logs = 0;
		Log("Console cleared.");
	}
	
	logs++;
}