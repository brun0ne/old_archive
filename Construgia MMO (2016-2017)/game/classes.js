class Player
{
	constructor(pos_x, pos_y, collision, speed){
		this.pos_x = pos_x;
		this.pos_y = pos_y;
		
		this.MaxHP = 100;
		this.HP;
		this.EXP;
    this.LVL;
		
		this.gold;
		
		this.isDamaged = false;
		
		this.isDamagedTime = 0;
		
		this.collision = collision;
		
		this.direction = "down";
		
		this.stat_x = $(window).width() * (45/100);
		this.stat_y = $(window).height() * (35/100);
		
		// w: 50, h: 50 <-- "static"
		
		this.speed = speed;
	}
	
	Load(){
		this.playerGraphics = $("#player_graphics");
		
		this.pos_x -= $(window).width() * (45/100);
		
		this.pos_y -= $(window).height() * (35/100);
		
		this.pos_x += 625;
		this.pos_y += 210;
		
		$(window).resize(function() {
			player.pos_x += (player.stat_x - $(window).width() * (45/100));
			player.pos_y += (player.stat_y - $(window).height() * (35/100));
			
			player.stat_x = $(window).width() * (45/100);
			player.stat_y = $(window).height() * (35/100);
      
      window.lastW = $(window).width();
      window.lastH = $(window).height();
			
			if(licznik <= 0){
				location_.unLoad();
				location_.Load();
				licznik = 20;
			}
		});
	}
	
	Update(){
		// Damage Time
		
		if(this.isDamagedTime >= 0)
			this.isDamagedTime--;
		
		if(this.isDamagedTime == 0){
      this.playerGraphics.css("background", "url(graphics/player/player.png)");
			this.isDamaged = false;
		}
		
		// HP regen
		
		if(this.HP < this.MaxHP)
			this.HP += 0.002;
		
		// Die
		
		if(this.HP <= 0){
			document.documentElement.innerHTML = "You <b>died</b>.<br /><br /><br /><i>Click F5.</i>";
		}
	}
	
	Damage(attack){
		this.HP -= attack;
		this.isDamaged = true;
		this.isDamagedTime = 20;
		
		if(SFX_sounds === true){
			var damagePlayerSound = new Audio('sounds/ouch.mp3');
			damagePlayerSound.volume = 0.5;
			damagePlayerSound.play();
		}
		
    this.playerGraphics.css("background", "url(graphics/player/player_dmg.png)");
	}
}

/////////////////////////////////////////////

class shadow
{
	constructor(id, x, y, w, h, url, object_, isNpc){
		this.x = x;
		this.y = y;
		this.w = w;
		this.h = h;
		
		this.isNpc = isNpc;
		if(isNpc == null)
			this.isNpc = false;
		
		this.object_ = object_;
		
		this.url = url;
		
		this.id = id;
	}	
	
	Load(){
		if(this.isNpc === false)
			document.getElementById(this.id + "_shadowdiv").innerHTML = document.getElementById(this.id + "_shadowdiv").innerHTML + "<img id='" + this.id + "_shadow' class='shadow' src='" + this.url + "' />";
		else if(this.isNpc === true)
			document.getElementById(this.id + "_shadowdiv").innerHTML = document.getElementById(this.id + "_shadowdiv").innerHTML + "<img id='" + this.id + "_shadow' class='shadow' style='left: -500px; right: -500px;' src='" + this.url + "' />";
			
		$("#" + this.id + "_shadow").css({
			"width" : this.w,
			"height" : this.h
		});
		
		// create PerspectiveTransfrom
    var transform = new PerspectiveTransform(document.getElementById(this.id + "_shadow"), this.w, this.h, true);

    // the properties represent the 4 corners are "topLeft", "topRight", "bottomLeft" and "bottomRight"
  	transform.topRight.x = (this.w * 1.5);
		transform.topLeft.x = (this.w / 1);
		transform.topRight.y = (this.h / 1.7);
		transform.topLeft.y = (this.h / 1.7);
		

    // check the polygon error before updating
    if(transform.checkError() === 0){
        transform.update(); // update the perspective transform
        document.getElementById(this.id + "_shadow").style.display = "block"; // show the element
    }else{
        document.getElementById(this.id + "_shadow").style.display = "none"; // hide the element
    }
	}
	
	Draw(x, y){
    if(x == null)
      x = this.x;
    if(y == null)
      y = this.y;
    
		if(shadows === true){
			$("#" + this.id + "_shadow").css({
				"left" : x - player.pos_x,
				"top" : y - player.pos_y
			});
		}
	}
}

/////////////////////////////////////////////

class object
{
	constructor(x, y, w, h, name, url, collider, colCut, hiding, canEnter, gotoMap, gotoMapCoords){
		this.x = x;
		this.y = y;
		this.w = w;
		this.h = h;
		
		this.gotoMap = gotoMap;
		this.gotoMapCoords = gotoMapCoords;
		
		this.canEnter = canEnter;
		if(this.canEnter == null)
			this.canEnter = false;
		
		this.w_ = this.w;
		this.h_ = this.h;
		
		this.isEnter = false;
		
		this.hiding = hiding;
		
		if(this.hiding == null)
			this.hiding = true;
		
		this.colCut = colCut;
		
		if(this.colCut === null || this.colCut === 0)
			this.colCut = 0;
		
		this.name = name;
		this.url = url;
		this.collider = collider;
		
		this.Shadow = new shadow(this.name, this.x, this.y, this.w, this.h, this.url, this);
	}
	
	Load(shadowIs){
		if(this.hiding === true){
			document.getElementById("objects").innerHTML = document.getElementById("objects").innerHTML + "<div style='position: absolute;' id='" + this.name + "'></div>";
		}
		else
			document.getElementById("objects_noth").innerHTML = document.getElementById("objects_noth").innerHTML + "<div style='position: absolute;' id='" + this.name + "'></div>";
		
		this.shadowIs = shadowIs;
		if(this.shadowIs == null)
			this.shadowIs = true;
		
		if(this.shadowIs === true)
			document.getElementById("shadows").innerHTML = document.getElementById("shadows").innerHTML + "<div style='position: absolute;' id='" + this.name + "_shadowdiv'></div>";
		
		document.getElementById(this.name).innerHTML = "<img id='" + this.name + "_img' style='position: absolute;' class='pixelated' src='" + this.url + "' width='" + this.w + "' height='" + this.h + "' />";
		document.getElementById(this.name).innerHTML = document.getElementById(this.name).innerHTML + "<img id='" + this.name + "_light' style='position: absolute; visibility: hidden; opacity: 0.5;' src='graphics/backlight.png' width='" + this.w + "' height='" + this.h + "' />";
		
		if(this.shadowIs === true)
			this.Shadow.Load();
    
    $("#" + this.name + "_img").css({
       "top": this.y - player.pos_y,
       "left": this.x - player.pos_x,
    });

    $("#" + this.name + "_light").css({
       "top": this.y - player.pos_y,
       "left": this.x - player.pos_x,
    });

    this.Collision();

    if(this.shadowIs === true)
      this.Shadow.Draw();
		
		var it = this;
		
		$(document).keydown(function(event) {
			if(event.keyCode == 13){ // ENTER
				if(it.isEnter === true){
					gotoMap(it.gotoMap, it.gotoMapCoords.x, it.gotoMapCoords.y);
					it.Info_Off();
				}
			}
		});
	}
	
	Draw(){
    if(this.x - player.pos_x > 0 - this.w * 2 - 10 && this.x - player.pos_x < window.lastW + this.w + 10 && this.y - player.pos_y > 0 - this.h * 2 && this.y - player.pos_y < window.lastH + this.h / 2){
      $("#" + this.name + "_img").css({
         "top": this.y - player.pos_y,
         "left": this.x - player.pos_x,
      });

      $("#" + this.name + "_light").css({
         "top": this.y - player.pos_y,
         "left": this.x - player.pos_x,
      });
		
      this.Collision();

      if(this.shadowIs === true)
        this.Shadow.Draw();
    }
	}
	
	Info(){
		if(this.canEnter === true){
			$("#" + this.name + "_light").css({"visibility" : "visible"});
			$("#enter_info").css({"visibility" : "visible"});
		}
	}
	Info_Off(){
		$("#" + this.name + "_light").css({"visibility" : "hidden"});
		$("#enter_info").css({"visibility" : "hidden"});
	}
	
	Collision(){
		if(this.collider === true && player.collision ===true){ 
			if(player.stat_x >= this.x - player.pos_x - 50 - 7 && player.stat_y + 50 >= this.y + (this.h * this.colCut) - player.pos_y && player.stat_y <= this.y + this.h - player.pos_y && player.stat_x <= this.x + (this.w / 2) - player.pos_x){
				canRight = false; // RIGHT (player's right "wall")
			}
			else if(player.stat_x + 25 > this.x - 50 - player.pos_x && player.stat_x < this.x + this.w + 50 - player.pos_x && player.stat_y + 50 > this.y + (this.h * this.colCut) - 25 - player.pos_y && player.stat_y < this.y + (this.h * this.colCut) + this.h + 25 - player.pos_y)
				canRight = true;
			
			if(player.stat_x <= (this.x + this.w) - player.pos_x + 20 && player.stat_y + 50 >= this.y + (this.h * this.colCut) - player.pos_y && player.stat_y <= this.y + this.h - player.pos_y && player.stat_x + 50 >= this.x + (this.w / 2) - player.pos_x){
				canLeft = false; // LEFT (player's left "wall")
			}
			else if(player.stat_x + 25 > this.x - 50 - player.pos_x && player.stat_x < this.x + this.w + 50 - player.pos_x && player.stat_y + 50 > this.y + (this.h * this.colCut) - 25 - player.pos_y && player.stat_y < this.y + (this.h * this.colCut) + this.h + 25 - player.pos_y)
				canLeft = true;
			
			if(player.stat_y + 50 >= this.y + (this.h * this.colCut) - player.pos_y - 7 && player.stat_x <= (this.x + this.w) - player.pos_x && player.stat_x >= this.x - player.pos_x - 50 && player.stat_y <= this.y + (this.h / 2) - player.pos_y){
				canDown = false; // DOWN (player's down "wall")
			}
			else if(player.stat_x + 25 > this.x - 50 - player.pos_x && player.stat_x < this.x + this.w + 50 - player.pos_x && player.stat_y + 50 > this.y + (this.h * this.colCut) - 25 - player.pos_y && player.stat_y < this.y + (this.h * this.colCut) + this.h + 25 - player.pos_y)
				canDown = true;
			
			if(player.stat_y <= this.y + this.h - player.pos_y + 15 && player.stat_x <= (this.x + this.w) - player.pos_x && player.stat_x >= this.x - player.pos_x - 50 && player.stat_y + 50 >= this.y + (this.h / 2) - player.pos_y){
				canUp = false; // UP (player's up "wall")
				this.Info();
				
				if(this.canEnter === true){
					this.isEnter = true;
				}
			}
			else if(player.stat_x + 25 > this.x - 50 - player.pos_x && player.stat_x < this.x + this.w + 50 - player.pos_x && player.stat_y + 50 > this.y - 25 - player.pos_y && player.stat_y < this.y + this.h + 25 - player.pos_y){
				canUp = true;
				this.Info_Off();
				
				if(this.canEnter === true){
					this.isEnter = true;
				}
			}
		}
	}
}

/////////////////////////////////////////////

class ground
{
	constructor(url, x, y){
		this.url = url;
		this.x = x;
		this.y = y;
		
		this.DOMground1 = 0;
		this.DOMground2 = 0;
	}
	
	Load(){
		document.getElementById("ground").innerHTML = "<img style='position: absolute;' id='ground_pic_1' src='graphics/" + this.url + "' />" + "<img style='position: absolute; left: 1280;' id='ground_pic_2' src='graphics/" + this.url + "' />";
		this.DOMground1 = $("#ground_pic_1");
		this.DOMground2 = $("#ground_pic_2");
	}
	
	Work(){
		this.DOMground1.css("top", 0 - this.y);
		this.DOMground1.css("left", 0 - this.x);
		
		this.DOMground2.css("top", 0 - this.y);
		this.DOMground2.css("left", 0 - this.x);
		
		// LOOPING
		
		if(this.x > 1000)
			this.x = 0;
		if(this.y > 650)
			this.y = 0;
		if(this.x < -1000)
			this.x = 0;
		if(this.y < -650)
			this.y = 0;
	}
}

/////////////////////////////////////////////

class Dialog
{
	constructor(Text, answer1, answer2, answer3, answer4, answers_count, img_url, name, nextd1, nextd2, nextd3, nextd4, canExit, fun1, fun2, fun3, fun4){
		this.Text = Text;
		
		this.answer1 = answer1;
		this.answer2 = answer2;
		this.answer3 = answer3;
		this.answer4 = answer4;
		
		this.nextd1 = nextd1;
		this.nextd2 = nextd2;
		this.nextd3 = nextd3;
		this.nextd4 = nextd4;
		
		this.fun1 = fun1;
		this.fun2 = fun2;
		this.fun3 = fun3;
		this.fun4 = fun4;
		
		this.answers_count = answers_count;
		this.img_url = img_url;
		this.is = false;
		this.name = name; // the same as object name
		
		this.canExit = canExit;
		if(this.canExit == null)
			this.canExit = true;
	}
	
	Update(){
		if(this.is){
			// BACKGROUND
			
			document.getElementById("dialog").innerHTML = "<img style='left: 21%; bottom: 5%; position: absolute; width: 60%; height: 45%;' src='graphics/dialog_background.png' />";
			
			// "STRANGER"'s IMAGE
			
			if(this.img_url !== ""){
			//	document.getElementById("dialog").innerHTML = document.getElementById("dialog").innerHTML + "<img src='" + this.img_url + "'style='position: absolute; right: 21%; bottom: 40%;' />";
			}
			
			// MAIN TEXT
			
			document.getElementById("dialog").innerHTML = document.getElementById("dialog").innerHTML + "<div id='" + this.name + "_text' style='position: absolute; left: 23%; right: 45%; top: 53%; word-wrap: normal;'>" + "" + " </div>"
			
      // Make answers' area ->
				
			document.getElementById("dialog").innerHTML = document.getElementById("dialog").innerHTML + "<div style='left: 55%; bottom: 7%; overflow: auto; position: absolute; width: 22%; height: 30%;' id='answers_area'></div>";
				
			// <- Make answers' area
      
      var HelpVar2 = "#" + this.name + "_text";
      var HelpVar3 = this.Text;
      
      $(function(){
          $(HelpVar2).typed({
            strings: [HelpVar3],
            typeSpeed: -10,
            showCursor: false,
            callback: function() {$("#answers_area").fadeIn();},
          });
      });
      
			// ANSWERS
			
			if(this.answers_count > 0){ // 1st answer
        
        $("#answers_area").hide();
				
				if(this.nextd1 !== "stop")
					document.getElementById("answers_area").innerHTML = document.getElementById("answers_area").innerHTML + "<center class='answer'><a href='javascript:location_." + this.nextd1 + ".On(); if(location_." + this.name + ".fun1 != null){ location_." + this.name + ".fun1(); }' id='answer1' style='text-decoration: none; color: black;'>" + this.answer1 + "</a></center><br />";
				else
					document.getElementById("answers_area").innerHTML = document.getElementById("answers_area").innerHTML + "<center class='answer'><a href='javascript:location_." + this.name + ".Off(); if(location_." + this.name + ".fun1 != null){ location_." + this.name + ".fun1(); }' id='answer1' style='text-decoration: none; color: black;'>" + this.answer1 + "</a></center><br />";
				
				if(this.answers_count > 1){ // 2nd answer
					if(this.nextd2 !== "stop")
						document.getElementById("answers_area").innerHTML = document.getElementById("answers_area").innerHTML + "<center class='answer'><a href='javascript:location_." + this.nextd2 + ".On(); if(location_." + this.name + ".fun2 != null){ location_." + this.name + ".fun2(); }' id='answer2' style='text-decoration: none; color: black;'>" + this.answer2 + "</a></center><br />";
					else
						document.getElementById("answers_area").innerHTML = document.getElementById("answers_area").innerHTML + "<center class='answer'><a href='javascript:location_." + this.name + ".Off(); if(location_." + this.name + ".fun2 != null){ location_." + this.name + ".fun2(); }' id='answer2' style='text-decoration: none; color: black;'>" + this.answer2 + "</a></center><br />";
					
					if(this.answers_count > 2){ // 3rd answer
						if(this.nextd3 !== "stop")
							document.getElementById("answers_area").innerHTML = document.getElementById("answers_area").innerHTML + "<center class='answer'><a href='javascript:location_." + this.nextd3 + ".On(); if(location_." + this.name + ".fun3 != null){ location_." + this.name + ".fun3(); }' id='answer3' style='text-decoration: none; color: black;'>" + this.answer3 + "</a></center><br />";
						else
							document.getElementById("answers_area").innerHTML = document.getElementById("answers_area").innerHTML + "<center class='answer'><a href='javascript:location_." + this.name + ".Off(); if(location_." + this.name + ".fun3 != null){ location_." + this.name + ".fun3(); }' id='answer3' style='text-decoration: none; color: black;'>" + this.answer3 + "</a></center><br />";
						
						if(this.answers_count > 3){ // 4th answer
							if(this.nextd4 !== "stop")
								document.getElementById("answers_area").innerHTML = document.getElementById("answers_area").innerHTML + "<center class='answer'><a href='javascript:location_." + this.nextd4 + ".On(); if(location_." + this.name + ".fun4 != null){ location_." + this.name + ".fun4(); }' id='answer4' style='text-decoration: none; color: black;'>" + this.answer4 + "</a></center><br />";
							else
								document.getElementById("answers_area").innerHTML = document.getElementById("answers_area").innerHTML + "<center class='answer'><a href='javascript:location_." + this.name + ".Off(); if(location_." + this.name + ".fun4 != null){ location_." + this.name + ".fun4(); }' id='answer4' style='text-decoration: none; color: black;'>" + this.answer4 + "</a></center><br />";
						}
					}
				}
			}

      // "OFF" BUTTON ->
			
			if(this.canExit === true)
				document.getElementById("dialog").innerHTML = document.getElementById("dialog").innerHTML + "<a href='javascript:location_." + this.name + ".Off();' id='dialog_off_button_href' style='position: absolute; right: 23%; bottom: 49%;'><img id='dialog_off_button' src='graphics/exit.png' style='position: fixed; width: 3%; height: auto;' /></a>";
			else
				document.getElementById("dialog").innerHTML = document.getElementById("dialog").innerHTML + "<a href='javascript:/*NOT*/' id='dialog_off_button_href' style='position: absolute; right: 23%; bottom: 49%;'><img id='dialog_off_button' src='graphics/exit.png' class='notOnHover' style='position: fixed; width: 3%; height: auto;' /></a>";
				
			// <- "OFF" BUTTON
		}
	}
	
	On(npc_name){
		this.is = true;
		this.Update();
		
		canMove = false;
	}
	
	Off(){
		this.is = false;
		
		canMove = true;
		
		document.getElementById("dialog").innerHTML = "";
		
		this.Update();
	}
}

/////////////////////////////////////////////

class NPC
{
	constructor(name, lvl, x, y, imgUrl, idd, namex, custom_namew){
		this.name = name;
		this.lvl = lvl;
		
		this.idd = idd;
		
		this.x = x;
		this.y = y;
		
		this.w = 50;
		this.h = 50;
		
		this.collider = true;
		
		this.imgUrl = imgUrl;
		
		this.namex = namex;
		if(this.namex == null)
			this.namex = 0;
		
		this.custom_namew = custom_namew;
		if(this.custom_namew == null)
			this.custom_namew = 0;
		
		this.Shadow = new shadow(this.idd, this.x, this.y, this.w, this.h, this.imgUrl, this, true);
	}
	
	Load(dialog){
		if($("#div_npc_" + this.idd).length)
			$("#div_npc_" + this.idd).remove();
		
		if($("#" + this.idd + "_shadowdiv").length)
			$("#" + this.idd + "_shadowdiv").remove();
		
		if(this.idd === "" || this.idd == null)
			this.idd = this.name;
		
		this.helpVar = '"' + this.name + '"';
		
		document.getElementById("npcs").innerHTML = document.getElementById("npcs").innerHTML + "<div id='div_npc_" + this.idd + "' style='position: absolute;' class='npc'><img onclick='javascript:location_." + dialog.name + "." + "On(" + this.helpVar + ");" + "' id='npc_" + this.idd + "' src='"+ this.imgUrl +"' style='position: absolute; left: -500px; right: -500px;'/></div>";
		
		document.getElementById("shadows").innerHTML = document.getElementById("shadows").innerHTML + "<div style='position: absolute;' id='" + this.idd + "_shadowdiv'></div>";
		
		if(this.custom_namew === 0 || this.custom_namew == null)
			document.getElementById("div_npc_" + this.idd).innerHTML = document.getElementById("div_npc_" + this.idd).innerHTML + "<div id='npc_" + this.idd + "_name' class='name' style='position: absolute; font-weight: bold; width:" + this.name.length * 7.5 + "px;'>" + this.name + "</div>";
		if(this.custom_namew !== 0)
			document.getElementById("div_npc_" + this.idd).innerHTML = document.getElementById("div_npc_" + this.idd).innerHTML + "<div id='npc_" + this.idd + "_name' class='name' style='position: absolute; font-weight: bold; width:" + this.custom_namew + "px;'>" + this.name + "</div>";
		
		this.Shadow.Load();
	}
	
	Collision(){
		if(this.collider === true && player.collision === true){ 
			if(player.stat_x >= this.x - player.pos_x - 50 - 7 && player.stat_y + 50 >= this.y - player.pos_y && player.stat_y <= this.y + this.h - player.pos_y && player.stat_x <= this.x + (this.w / 2) - player.pos_x){
				canRight = false; // RIGHT (player's right "wall")
			}
			else if(player.stat_x + 50 > this.x - 50 - player.pos_x && player.stat_x < this.x + this.w + 50 - player.pos_x && player.stat_y + 50 > this.y - 50 - player.pos_y && player.stat_y < this.y + this.h + 50 - player.pos_y)
				canRight = true;
			
			if(player.stat_x <= (this.x + this.w) - player.pos_x + 20 && player.stat_y + 50 >= this.y - player.pos_y && player.stat_y <= this.y + this.h - player.pos_y && player.stat_x + 50 >= this.x + (this.w / 2) - player.pos_x){
				canLeft = false; // LEFT (player's left "wall")
			}
			else if(player.stat_x + 50 > this.x - 50 - player.pos_x && player.stat_x < this.x + this.w + 50 - player.pos_x && player.stat_y + 50 > this.y - 50 - player.pos_y && player.stat_y < this.y + this.h + 50 - player.pos_y)
				canLeft = true;
			
			if(player.stat_y + 50 >= this.y - player.pos_y - 7 && player.stat_x <= (this.x + this.w) - player.pos_x && player.stat_x >= this.x - player.pos_x - 50 && player.stat_y <= this.y + (this.h / 2) - player.pos_y){
				canDown = false; // DOWN (player's down "wall")
			}
			else if(player.stat_x + 50 > this.x - 50 - player.pos_x && player.stat_x < this.x + this.w + 50 - player.pos_x && player.stat_y + 50 > this.y - 50 - player.pos_y && player.stat_y < this.y + this.h + 50 - player.pos_y)
				canDown = true;
			
			if(player.stat_y <= this.y + this.h - player.pos_y + 15 && player.stat_x <= (this.x + this.w) - player.pos_x && player.stat_x >= this.x - player.pos_x - 50 && player.stat_y + 50 >= this.y + (this.h / 2) - player.pos_y){
				canUp = false; // UP (player's up "wall")
			}
			else if(player.stat_x + 50 > this.x - 50 - player.pos_x && player.stat_x < this.x + this.w + 50 - player.pos_x && player.stat_y + 50 > this.y - 50 - player.pos_y && player.stat_y < this.y + this.h + 50 - player.pos_y)
				canUp = true;
		}
	}
	
	Update(){
    $("#npc_" + this.idd).css({
      "top": this.y - player.pos_y,
      "left": this.x - player.pos_x
    });

    $("#npc_" + this.idd + "_name").css({
      "top" : this.y - 35 - player.pos_y,
      "left" : this.x - this.namex - player.pos_x,
    });

    this.Shadow.Draw();

    this.Collision();
  }
}

class Canon
{
	constructor(w, h, speed, lifeTime, imgUrl, number, damage){
		this.x = 0;
		this.y = 0;
		
		this.w = w;
		this.h = h;
    
    this.damage = damage;
		
		this.speed = speed;
		this.direction = 0;
		
		this.lifeTime = lifeTime;
		this.actLifeTime = 0;
		
		this.is = false;
		this.imgUrl = imgUrl;
		this.number = number;
	}
	
	Load(){
    $("#canon_" + this.number).remove();
		document.getElementById("canons").innerHTML = document.getElementById("canons").innerHTML + "<img id='canon_" + this.number + "' src='" + this.imgUrl + "'style='display: none; position: absolute; width: " + this.w + "px; height: " + this.h + "px;' />";
  }
  
  Set(speed, lifeTime, imgUrl, damage){
    this.speed = speed;
    this.lifeTime = lifeTime;
    this.imgUrl = imgUrl;
    this.damage = damage;
    this.Load();
  }
	
	Launch(){
		this.is = true;
		
		this.actLifeTime = this.lifeTime;
		
		this.x = player.stat_x;
		this.y = player.stat_y;
		
		if(player.direction == "down"){
			this.direction = "down";
			this.x = player.stat_x + 5;
		}
		else if(player.direction == "up"){
			this.direction = "up";
			this.x = player.stat_x + 5;
		}
		else if(player.direction == "left"){
			this.direction = "left";
			this.y = player.stat_y + 5;
		}
		else if(player.direction == "right"){
			this.direction = "right";
			this.y = player.stat_y + 5;
		}
	}
	
	Destroy(natural){
		if(natural == null)
			natural = true;
		
		if(natural == true)
			$("#canon_" + this.number).fadeOut("fast");
		else if(natural == false)
			$("#canon_" + this.number).css({"display" : "none"});
		
		this.is = false;
	}
	
	Update(delta){
		$("#canon_" + this.number).css({
			"left" : this.x,
			"top" : this.y
		});
		
		if(this.is){
			$("#canon_" + this.number).css({
				"display" : "inline"
			});
		}
		else
			this.Destroy(true);
		
		
		if(this.actLifeTime > 0)
			this.actLifeTime -= 1;
		
		if(this.direction == "right"){
			if(this.actLifeTime > 0){
				this.x += this.speed * delta;
			}
			else{
				this.is = false;
				this.actLifeTime = 0;
			}
		}
		else if(this.direction == "left"){
			if(this.actLifeTime > 0){
				this.x -= this.speed * delta;
			}
			else{
				this.is = false;
				this.actLifeTime = 0;
			}
		}
		else if(this.direction == "up"){
			if(this.actLifeTime > 0){
				this.y -= this.speed * delta;
			}
			else{
				this.is = false;
				this.actLifeTime = 0;
			}
		}
		else if(this.direction == "down"){
			if(this.actLifeTime > 0){
				this.y += this.speed * delta;
			}
			else{
				this.is = false;
				this.actLifeTime = 0;
			}
		}
	}
}

class Enemy
{
	constructor(id, x, y, w, h, imgUrl, speed, maxHP, attack, moving, dir, price, respTime){
		this.id = id;
		
		this.direction = false;
		
		this.dmgTime = 0;
		
		this.price = price;
		
		if(this.price == 0 || this.price == null)
			this.price = 0;
		
		this.is = true;
		
		this.dir = dir;
		if(dir == null)
			this.dir = true;
		
		this.maxHP = maxHP;
		this.attack = attack;
		this.imgUrl = imgUrl;
		this.speed = speed;
		
		this.HP = maxHP;
		
		this.x = x;
		this.y = y;
		this.w = w;
		this.h = h;
		
		this.maxX = this.x + 250;
		this.minX = this.x - 250;
		
		this.maxY = this.y + 250;
		this.minY = this.y - 250;
		
    this.respTimeMAX = respTime;
    
    if(this.respTimeMAX == null)
      this.respTimeMAX = 1000;
    
    this.respTime = 0; // act resptime
    
		this.moving = moving;
		if(moving == null)
			this.moving = false;
    
    this.Shadow = new shadow(this.id, this.x, this.y, this.w, this.h, this.imgUrl + ".png", this, false);
	}
	
	Load(){
    if($("#" + this.id + "_shadowdiv").length)
			$("#" + this.id + "_shadowdiv").remove();
    
		document.getElementById("monsters").innerHTML = document.getElementById("monsters").innerHTML + "<div id='div_" + this.id + "'></div>";
		
		document.getElementById("div_" + this.id).innerHTML = document.getElementById("div_" + this.id).innerHTML + "<img id='enemy_" + this.id + "' src='" + this.imgUrl + ".png' style='position: absolute; width: " + this.w + "; height: " + this.h + ";' />";
	
		document.getElementById("div_" + this.id).innerHTML = document.getElementById("div_" + this.id).innerHTML + "<div id='HP_info_" + this.id + "' style='position: absolute;'></div>"
	  
    document.getElementById("shadows").innerHTML = document.getElementById("shadows").innerHTML + "<div style='position: absolute;' id='" + this.id + "_shadowdiv'></div>";
    
    this.Shadow.Load();
    
    $("#enemy_" + this.id).css({
      "left" : this.x - player.pos_x,
      "top" : this.y - player.pos_y
    });
    
    $("#HP_info_" + this.id).css({
      "top" : this.y - 25 - player.pos_y,
      "left" : this.x + 10 - player.pos_x
    });
    
    $("#" + this.id + "_shadow").css({
			"left" : "-500px",
			"top" : "-500px"
		});
  }
	
	Update(delta){
    if(this.x - player.pos_x > 0 - this.w * 2 - 270 && this.x - player.pos_x < window.lastW + this.w + 270 && this.y - player.pos_y > 0 - this.h - 270 && this.y - player.pos_y < window.lastH + this.h * 2 + 270){
      // Update position

      $("#enemy_" + this.id).css({
        "left" : this.x - player.pos_x,
        "top" : this.y - player.pos_y
      });

      if(this.HP >= 100){
        $("#HP_info_" + this.id).css({
          "top" : this.y - 25 - player.pos_y,
          "left" : this.x + 10 - player.pos_x
        });
      }
      else{
        $("#HP_info_" + this.id).css({
          "top" : this.y - 25 - player.pos_y,
          "left" : this.x + 15 - player.pos_x,
          "font-weight" : "bold",
          "color" : "red"
        });
      }

      // Update stats info

      $("#HP_info_" + this.id).html(this.HP);

      // Moving

      if(this.moving === true){
        if(this.dir === true){ // X
          if(this.direction === false){
            if(this.x < this.maxX){
              this.x += this.speed * delta_;
            }
            else
              this.direction = true;
          }
          else if(this.direction === true){
            if(this.x > this.minX){
              this.x -= this.speed * delta_;
            }
            else
              this.direction = false;
          }
        }
        else if(this.dir === false){ // Y
          if(this.direction === false){
            if(this.y < this.maxY){
              this.y += this.speed * delta_;
            }
            else
              this.direction = true;
          }
          else if(this.direction === true){
            if(this.y > this.minY){
              this.y -= this.speed * delta_;
            }
            else
              this.direction = false;
          }
        }
      }

      // Getting damage

      if(this.dmgTime >= 0)
        this.dmgTime--;

      if(this.dmgTime === 0)
        $("#enemy_" + this.id).attr("src", this.imgUrl + ".png");

      if(this.is && canon1.is && canon1.x + canon1.w > this.x - player.pos_x && canon1.x < this.x + this.w - player.pos_x && canon1.y + canon1.h > this.y - player.pos_y && canon1.y < this.y + this.h - player.pos_y){
        this.HP -= canon1.damage;
        canon1.Destroy(false);

        $("#enemy_" + this.id).attr("src", this.imgUrl + "_dmg.png");

        if(SFX_sounds === true){
          var damageSound = new Audio('sounds/damage.mp3');
          damageSound.volume = 0.5;
          damageSound.play();
        }

        this.dmgTime = 20;
      }
      if(this.is && canon2.is && canon2.x + canon2.w > this.x - player.pos_x && canon2.x < this.x + this.w - player.pos_x && canon2.y + canon2.h > this.y - player.pos_y && canon2.y < this.y + this.h - player.pos_y){
        this.HP -= canon2.damage;
        canon2.Destroy(false);

        $("#enemy_" + this.id).attr("src", this.imgUrl + "_dmg.png");

        if(SFX_sounds === true){
          var damageSound = new Audio('sounds/damage.mp3');
          damageSound.volume = 0.5;
          damageSound.play();
        }

        this.dmgTime = 20;
      }

      // Giving damage

      if(this.is === true && player.isDamaged === false && this.x + this.w - player.pos_x > player.stat_x && this.x - player.pos_x < player.stat_x + 50 && this.y + this.h - player.pos_y > player.stat_y && this.y - player.pos_y < player.stat_y + 50){
        player.Damage(this.attack);
      }

      // Die

      if(this.HP <= 0){
        if(this.is === true){
          player.gold += this.price;
          player.EXP += this.price * 2;

          document.getElementById("div_" + this.id).innerHTML = "";
          document.getElementById(this.id + "_shadowdiv").innerHTML = "";
          $("#div_" + this.id).remove();
          $("#" + this.id + "_shadowdiv").remove();

          this.respTime = this.respTimeMAX;
        }

        this.is = false;
      }

      // Shadow Update

      this.Shadow.Draw(this.x, this.y);
    } // OptimIF end
		
		// Respawn

		if(this.is === false && this.respTime >= 0)
			this.respTime--;
		
		if(this.is === false && this.respTime <= 0){
			this.is = true;
			this.HP = 100;
			this.Load(); 
		}
	}
}

class ItemArea
{
  constructor(type, number, name, imgUrl, speed, damage, lifeTime, health){
    this.type = type;
    this.name = name;
    this.imgUrl = imgUrl;
    this.speed = speed;
    this.damage = damage;
    this.lifeTime = lifeTime;
    this.health = health;
    
    if(this.imgUrl == null)
      this.imgUrl = "graphics/empty.png";
    
    this.number = number;
  }
  
  Load(){
    this.ItemsDOM = [$("#eq_items"), document.getElementById("eq_items")];
    this.w_n = (60 + (this.name.length * 8.5));
    
    this.onMouseOver = '$(eq_items_name_' + this.number + ').css({"visibility" : "visible", "left" : event.pageX, "top" : event.pageY});';
    this.onMouseOut = '$(eq_items_name_' + this.number + ').css("visibility", "hidden");';
    this.onMouseMove = '$(eq_items_name_' + this.number + ').css({"left" : event.pageX - ' + this.w_n + ', "top" : event.pageY + 5});';
    
    if(this.type == "canon")
      this.onClick = 'EQ.mainMissile.Set("' + this.name + '", "' + this.imgUrl + '", ' + this.speed + ', ' + this.damage + '); EQ.item[' + this.number + '].Set("canon", "' + EQ.mainMissile.name + '", "' + EQ.mainMissile.imgUrl + '", ' + EQ.mainMissile.speed + ', ' + EQ.mainMissile.damage + ', ' + EQ.mainMissile.lifeTime + ', ' + '0' + '); EQ.save();'; // type, name, imgUrl, speed, damage, lifeTime, health
    else if(this.type == "food")
      this.onClick = 'player.HP += ' + this.health + '; if(player.HP > 100) player.HP = 100; EQ.DelItem("' + this.name + '");  EQ.save();';
      
    var pointOn = 'class="pointOnHover"';
    
    this.ItemsDOM[1].innerHTML = this.ItemsDOM[1].innerHTML + "<img src='" + this.imgUrl + "'" + pointOn + " style='width: 50px; height: 50px; margin-left: 10px;' id='eq_items_" + this.number + "' onmouseover='" + this.onMouseOver + "' onmouseout='" + this.onMouseOut + "' onmousemove='" + this.onMouseMove + "' onClick='" + this.onClick + "' />";
    
		if(typeof InstallTrigger !== 'undefined'){
			if(this.type == "canon")
				this.ItemsDOM[1].innerHTML = this.ItemsDOM[1].innerHTML + "<div class='name' id='eq_items_name_" + this.number + "' style='z-index: 5; font-family: consolas, consolas; position: fixed; width: " + this.w_n + "px; right: 1%; height: 80px; bottom: 20%;'><b>Name:</b> " + this.name + "<br/><b>Damage:</b> " + this.damage + "<br /><b>Life time:</b> " + this.lifeTime + "<br /><b>Speed:</b> " + this.speed + "</div>";
			else if(this.type == "food")
				this.ItemsDOM[1].innerHTML = this.ItemsDOM[1].innerHTML + "<div class='name' id='eq_items_name_" + this.number + "' style='z-index: 5; font-family: consolas, consolas; position: fixed; width: " + this.w_n + "px; height: 40px; right: 1%; bottom: 20%;'><b>Name:</b> " + this.name + "<br/><b>HP reg:</b> " + this.health + "</div>";
		}
		else{
			if(this.type == "canon")
				this.ItemsDOM[1].innerHTML = this.ItemsDOM[1].innerHTML + "<div class='name' id='eq_items_name_" + this.number + "' style='z-index: 5; font-family: consolas, consolas; position: fixed; width: " + this.w_n + "px; right: 1%; height: 75px; bottom: 20%;'><b>Name:</b> " + this.name + "<br/><b>Damage:</b> " + this.damage + "<br /><b>Life time:</b> " + this.lifeTime + "<br /><b>Speed:</b> " + this.speed + "</div>";
			else if(this.type == "food")
				this.ItemsDOM[1].innerHTML = this.ItemsDOM[1].innerHTML + "<div class='name' id='eq_items_name_" + this.number + "' style='z-index: 5; font-family: consolas, consolas; position: fixed; width: " + this.w_n + "px; height: 40px; right: 1%; bottom: 20%;'><b>Name:</b> " + this.name + "<br/><b>HP reg:</b> " + this.health + "</div>";
		}
	}
  
  Set(type, name, imgUrl, speed, damage, lifeTime, health){
    this.type = type;
    this.name = name;
    this.imgUrl = imgUrl;
    this.speed = speed;
    this.damage = damage;
    this.lifeTime = lifeTime;
    this.health = health;
    
    if(this.imgUrl == null)
      this.imgUrl = "graphics/empty.png";
    
    EQ.Items_Clear();
    EQ.Items_Load();
  }
}

class MainMissile
{
  constructor(name, imgUrl, speed, damage, lifeTime){
    this.name = name;
    this.imgUrl = imgUrl;
    this.speed = speed;
    this.damage = damage;
    this.lifeTime = lifeTime;
  }
  
  Load(){
    $("#mainMissile").remove();
    $("#MainMissile_img").remove();
    $("#eq_mm_name").remove();
    
    document.getElementById("eq").innerHTML = document.getElementById("eq").innerHTML + "<div id='mainMissile' style='position: absolute;'></div>";
    this.mainMissileDOM = $("#mainMissile");
    this.mainMissileDOM_ = document.getElementById("mainMissile");
    
    this.w_n = (60 + (this.name.length * 8.5));
    
    this.onMouseEnter = '$("#eq_mm_name").css("visibility", "visible");';
    this.onMouseLeave = '$("#eq_mm_name").css("visibility", "hidden");';
    this.onMouseMove = '$("#eq_mm_name").css({"left" : event.pageX - EQ.mainMissile.w_n, "top" : event.pageY + 5});';
    
    this.mainMissileDOM_.innerHTML = this.mainMissileDOM_.innerHTML + "<img style='position: fixed; width: 50px; height: 50px; right: 8%; left: 89%; top: 30%;' id='MainMissile_img' src='" + this.imgUrl + "' onmouseenter='" + this.onMouseEnter + "' onmouseleave='" + this.onMouseLeave + "' onmousemove='" + this.onMouseMove + "' />";
    this.mainMissileDOM_.innerHTML = this.mainMissileDOM_.innerHTML + "<div class='name' id='eq_mm_name' style='z-index: 5; font-family: consolas, consolas; position: fixed; width: " + this.w_n + "px; right: 8%;'><b>Name:</b> " + this.name + "<br/><b>Damage:</b> " + this.damage + "<br /><b>Life time:</b> " + this.lifeTime + "<br /><b>Speed:</b> " + this.speed + "</div>"
    
    canon1.Set(this.speed, this.lifeTime, this.imgUrl, this.damage); // speed, lifeTime, imgUrl, damage
    canon2.Set(this.speed, this.lifeTime, this.imgUrl, this.damage);
    
    canon1.Load();
    canon2.Load();
  }
  
  Set(name, imgUrl, speed, damage){
    this.name = name;
    this.imgUrl = imgUrl;
    this.speed = speed;
    this.damage = damage;
    
    this.Load();
  }
}

class eq
{
	constructor(something){
		this.eqDOM = [0, 0];
    
    this.mainMissile = new MainMissile("Basic Cannon", "graphics/canons/canon_start.png", 0.5, 2, 50); // name, imgURL, speed, dmg, lifeTime
	  
    this.item = new Array(0);
		
		this.loaded = false;
  }
	
	Load(){
		this.load();
		
		this.eqDOM[0] = $("#eq");
		this.eqDOM[1] = document.getElementById("eq");
		
		this.eqDOM[1].innerHTML = this.eqDOM[1].innerHTML + "<img id='eq_background' src='graphics/eq_back.png' style='width: 100%; height: 100%; border-style: solid;' />";
		
    this.eqDOM[1].innerHTML = this.eqDOM[1].innerHTML + "<div id='eq_items_background' style='position: absolute; top: 40%; width: 100%; height: 53.5%; opacity: 0.5;' class='foo blue'></div>";
    
    document.getElementById("eq").innerHTML = document.getElementById("eq").innerHTML + "<div style='position: absolute; top: 54%; left: 3%; height: 40%; width: 85%; overflow: auto;' id='eq_items'></div>"
    
    // MainMissile ->
    
    this.mainMissile.Load();
    
    // <- MainMissile
		
		this.eqDOM[0].css({
			//..
		});
	}
  
  Items_Clear(){
    $("#eq_items").empty();
    $("#eq_items").remove();
    
    document.getElementById("eq").innerHTML = document.getElementById("eq").innerHTML + "<div style='position: absolute; top: 54%; left: 3%; height: 40%; width: 85%; overflow: auto;' id='eq_items'></div>";
  }
  
  Items_Load(){
    for(var i = 0; i < this.item.length; i++){
      this.item[i].Load();
    }
  }
  
  AddItem(type, name, imgUrl, speed, damage, lifeTime, health){
    var newitem = new ItemArea(type, this.item.length, name, imgUrl, speed, damage, lifeTime, health);
    newitem.Load();
    this.item.push(newitem);
		
		if(this.loaded)
			this.save();
  }
  
  DelItem(name){
    for(var i = 0; i < this.item.length; i++){
      if(this.item[i].name == name){
        this.item.splice(i, 1);
				break;
      }
    }
    
    this.Items_Clear();
    this.Items_Load();
		
		if(this.loaded)
			this.save();
  }
	
	save(){
		var tempObject = {"Items" : {}};
		var count;
		
		for(i in this.item){
			var actObject = {"type" : this.item[i].type, "name" : this.item[i].name, "img" : this.item[i].imgUrl, "speed" : this.item[i].speed, "damage" : this.item[i].damage, "lifeTime" : this.item[i].lifeTime, "health" : this.item[i].health, "number" : this.item[i].number};
			
			tempObject["Items"][i] = actObject;
			count = i;
		}
		
		var count_ = parseInt(count) + parseInt(1);
		
		tempObject["mainMissile"] = {"name" : this.mainMissile.name, "img" : this.mainMissile.imgUrl, "speed" : this.mainMissile.speed, "damage" : this.mainMissile.damage, "lifeTime" : this.mainMissile.lifeTime};
	
		tempObject["EQ"] = {"items_count" : count_};
		
		tempObject = JSON.stringify(tempObject);
		
		$.ajax({
			type: "POST",
			url: "AJAX/server.php",
			data: {action: "eqSave", JSONarray: tempObject, nick: USERNICK},
			dataType: 'text',
			success: function(response){
				// ...
			},
			error: function(data){
				console.log("AJAX/PHP error : AJAX_eqSave ; Invalid object: " + jObject);
			}
		});
	}
	
	load(){
		var it = this;
		
		$.ajax({
			type: "GET",
			url: "AJAX/server.php",
			data: {action: "eqLoad"},
			dataType: 'JSON',
			success: function(response){
				it.mainMissile.Set(response.mainMissile.name, response.mainMissile.img, response.mainMissile.speed, response.mainMissile.damage);
				
				it.item = new Array(0);
				
				for(var i = 0; i < response.EQ.items_count; i++){
					it.AddItem(response.Items[i].type, response.Items[i].name, response.Items[i].img, response.Items[i].speed, response.Items[i].damage, response.Items[i].lifeTime, response.Items[i].health);
				}
				
				this.loaded = true;
			},
			error: function(data){
				console.log("EQ isn't loaded : " + data);
			}
		});
	}
}

class Barrier
{
  constructor(w, h){
    this.w = w;
    this.h = h;
    
    this.DOM = new Array(0);
    this.BAR = new Array(0);
    
    this.bw = 1000;
    this.bh = 10000;
  }
  
  Load(){
    this.DOM = [$("#barrier"), document.getElementById("barrier")];
    
    this.DOM[0].empty();
    
    this.DOM[1].innerHTML = this.DOM[1].innerHTML + "<img id='act_barrier' src='graphics/white.png' class='pixelated' style='position: absolute;' />";
    this.DOM[1].innerHTML = this.DOM[1].innerHTML + "<img id='act_barrier1' src='graphics/white.png' class='pixelated' style='position: absolute;' />";
    this.DOM[1].innerHTML = this.DOM[1].innerHTML + "<img id='act_barrier2' src='graphics/white.png' class='pixelated' style='position: absolute;' />";
    this.DOM[1].innerHTML = this.DOM[1].innerHTML + "<img id='act_barrier3' src='graphics/white.png' class='pixelated' style='position: absolute;' />";
    
    this.BAR[0] = $("#act_barrier");
    this.BAR[1] = $("#act_barrier1");
    this.BAR[2] = $("#act_barrier2");
    this.BAR[3] = $("#act_barrier3");
    
    this.BAR[0].css({ // left
      "width" : this.bw,
      "height" : this.bh,
      "filter" : "brightness(50%)",
      "border-style" : "solid"
    });
    this.BAR[1].css({ // right
      "width" : this.bw,
      "height" : this.bh,
      "filter" : "brightness(50%)",
      "border-style" : "solid"
    });
    this.BAR[2].css({ // up
      "width" : this.bh,
      "height" : this.bw,
      "filter" : "brightness(50%)",
      "border-style" : "solid"
    });
    this.BAR[3].css({ // down
      "width" : this.bh,
      "height" : this.bw,
      "filter" : "brightness(50%)",
      "border-style" : "solid"
    });
  }
  
  Update(){
    this.BAR[0].css({ // left
      "left" : -this.w - player.pos_x - this.bw,
      "top" : -this.h - player.pos_y - (this.bh / 2)
    });
    this.BAR[1].css({ // right
      "left" : this.w - player.pos_x + this.bw,
      "top" : -this.h - player.pos_y - (this.bh / 2)
    });
    this.BAR[2].css({ // up
      "left" : -this.w - player.pos_x,
      "top" : -this.h - player.pos_y - (this.bw / 2)
    });
    this.BAR[3].css({ // down
      "left" : -this.w - player.pos_x,
      "top" : this.h - player.pos_y + (this.bw / 2)
    });
    
    // COLLISIONS
    
    if(player.stat_x + 50 >= this.w - player.pos_x + this.bw - 10){ // RIGHT PLAYER WALL ("10" is a delay)
      canRight = false;
    }
    else if(player.stat_x + 50 >= this.w - player.pos_x + this.bw - 50 - 10)
      canRight = true;
    
    if(player.stat_x <= -this.w - player.pos_x + 10){ // LEFT PLAYER WALL ("10" is a delay)
      canLeft = false;
    }
    else if(player.stat_x <= this.w - player.pos_x + 50 + 10)
      canLeft = true;
    
    if(player.stat_y <= -this.h - player.pos_y + this.bw / 2 + 10){ // UP ("10" is a delay)
      canUp = false;
    }
    else if(player.stat_y <= -this.h - player.pos_y + this.bw / 2 + 50 + 10)
      canUp = true;
    
    if(player.stat_y + 50 >= this.h - player.pos_y + (this.bw / 2) - 10){ // DOWN ("10" is a delay)
      canDown = false;
    }
    else if(player.stat_y + 50 >= this.h - player.pos_y + (this.bw / 2) - 50 - 10)
      canDown = true;
  }
}

class map{
  constructor(fileName){
    this.fileName = fileName;
    this.customStart = null;
    this.customUpdate = null;
    
    this.name = "";
    this.ground = "";
    this.l_ground = "";
    
    this.w = 0;
    this.h = 0;
    
    this.Ground = null;
    
    this.objects;
  }
  
  Load(){
    var it = this;
    
    $.when(AJAX_mapLoad(this.fileName)).done(function(response){
      it.name = response.Map.title;
      it.ground = response.Map.ground;
      it.l_ground = response.Map.l_ground;
      
      $("body").css({"background" : "url(graphics/" + ground + ") no-repeat center center fixed"});
      $("body").css({"background-size" : "cover"});
      
      it.w = response.Map.w;
      it.h = response.Map.h;
      
      it.Ground = new ground(it.l_ground, 0, 0);
			
			if(it.Ground != null)
      	it.Ground.Load();
      
      it.objects = [];
      
      if(firstTimePlay == 1){
        player.pos_x = response.Map.px * 4 - $(window).width() * (45/100);
        player.pos_y = response.Map.py * 4 - $(window).height() * (35/100);
      }
      
      for(var i = 0; i < response.Map.objects_count; i++){
				if(response.Objects[i].type === "object")
        	it.objects.push(new object(response.Objects[i].x * 4, response.Objects[i].y * 4, response.Objects[i].w * 4, response.Objects[i].h * 4, response.Objects[i].id, "graphics/" + response.Objects[i].img, response.Objects[i].col, 0.5, response.Objects[i].hiding, response.Objects[i].canEnter, response.Objects[i].gotoMap, response.Objects[i].gotoMapCoords));
        else if(response.Objects[i].type === "barrier")
					it.objects.push(new object(response.Objects[i].x * 4, response.Objects[i].y * 4, response.Objects[i].w * 4, response.Objects[i].h * 4, response.Objects[i].id, "graphics/" + response.Objects[i].img, response.Objects[i].col, 0, response.Objects[i].hiding, response.Objects[i].canEnter, response.Objects[i].gotoMap, response.Objects[i].gotoMapCoords));
				
				it.objects[i].Load(response.Objects[i].shadow);
      }
			
			try {
				it.customStart = new Function(response.Map.cStart);
				if(it.customStart != null)
					it.customStart();
			} catch (e) {
				alert("Map loading error: cStart() : " + e + ". cUpdate isn't executed.");
				it.customStart = null;
			}
			
			try {
				it.customUpdate = new Function(response.Map.cUpdate);
				if(it.customStart != null && it.customUpdate != null)
					it.customUpdate();
			} catch (e) {
				alert("Map loading error: Update() : " + e + ". Map isn't playable.");
				it.customUpdate = null;
			}
    });
    
    // CONTROLS INFO DIALOG -->
		
		this.controls_info = new Dialog("<b>Controls:</b><br /><br /><ul><li>Walking -- W, S, A, D or Arrow Keys,</li><br /><li>Shooting -- SPACE,</li><br /><li>Talking with NPC -- Left click on NPC.</li></ul>",
			"", "", "", "", 0, "",
		"controls_info");
		
		// <--
  }
  
  Update(){
    if(this.objects != null){
      for(var i = 0; i < this.objects.length; i++){
        this.objects[i].Draw();
      }
    }
    
    if(this.Ground != null)
      this.Ground.Work();
    
    if(this.customUpdate != null && this.customStart != null)
      this.customUpdate();
  }
	
	unLoad(){
		$("#objects").empty();
		$("#objects_noth").empty();
		$("#npcs").empty();
		$("#monsters").empty();
		$("#shadows").empty();
	}
}