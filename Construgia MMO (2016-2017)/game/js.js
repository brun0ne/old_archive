var kills = 0;
var licznik = 0;
var licznik2 = 0;
var gold_multiplier = 1;
var music;

var USERID;
var USERIDr;
var USERNICK;
var OK = "ok";

var mouseDown = 0;

var canExit = true;

var window = {lastW: 0, lastH: 0};

var rang = null;

var fastStatsUpdate = false;

var SFX_sounds = true;

var firstTimePlay;

var players_vis = true;

var shadows = true;

var whatLocation;

var lastRang = "";

var chatShow = false;

var controls_info_vis = false;
var settings_info_vis = false;

var border = true;

player = new Player(0, 0, true, 0.32);
canon1 = new Canon(25, 25, 0.5, 50, "graphics/canons/canon_start.png", 1, 2); // w, h, speed, lifeTime, imgUrl, number, dmg
canon2 = new Canon(25, 25, 0.5, 50, "graphics/canons/canon_start.png", 2, 2); // w, h, speed, lifeTime, imgUrl, number, dmg
EQ = new eq("nothing");

var lastX = 0,
		lastY = 0;

var location_;

var lastPlayersRes = 0;

function Start(){
	player.Load();
	
	canon1.Load();
	canon2.Load();
	
	EQ.Load();
  
  AJAX_Load();
  
  AJAX_chatRead();
}

function liMin(){
	if(licznik > 0)
		licznik--;
	if(licznik2 > 0)
		licznik2--;
	
	setTimeout("liMin()", 1);
}

function gotoMap(name, x, y){
	location_.unLoad();
	location_ = new map(name);
	location_.Load();
	player.pos_x = x;
	player.pos_y = y;
	
	whatLocation = name;
	
	canUp = true;
	canDown = true;
	canLeft = true;
	canRight = true;
	
	$("#other_players").empty();
	AJAX_players("start");
}

function EQsave(){
	EQ.save();
	
	setTimeout("EQsave()", 30000);
}

function AJAXUpdate(){
  if(players_vis)
    AJAX_players("update");
  
  if(chatShow){
    $.when(AJAX_chatRead()).done(function(response){
      $("#chat_content").html(response + "<div id='chat_end'></div>");
    });
  }
  
  if($("#chat_end").length){
		if($("#chat_content").scrollTop() > $("#chat_content").height() / 4){
    	$("#chat_end").scrollintoview({direction: "vertical"});
		}
	}
  
  AJAX_save();
  
  setTimeout("AJAXUpdate()", 1000);
}

function stats(){
	document.getElementById("gold_info").innerHTML = "Gold: " + player.gold;
	
	document.getElementById("player_position").innerHTML = "X: " + Math.round(player.pos_x) + " Y: " + Math.round(player.pos_y);
	
	document.getElementById("info_player_HP").innerHTML = "HP: " + Math.round(player.HP) + " <progress id='player_HP_bar' value='" + Math.round(player.HP) + "' max='100' style='color: red;'></progress>";
	document.getElementById("info_player_EXP").innerHTML = "EXP: " + player.EXP;
  document.getElementById("info_player_LVL").innerHTML = "LVL: " + player.LVL;
  
	document.getElementById("fpsDisplay").innerHTML = Math.round(fps) + ' FPS';
	
	if(fastStatsUpdate === true)
		setTimeout("stats()", 10);
	else
		setTimeout("stats()", 500);
}

function options(){
	$("#music_toggle").click(function(){
		if(music === true){
			audio.pause();
			$("#music_toggle").attr("src", "graphics/music_toggle.png");
			music = false;
			Log("Music turned off.");
		}
		else{
			audio.play();
			$("#music_toggle").attr("src", "graphics/music_toggle_off.png");
			music = true;
			Log("Music turned on.");
		}
	});
	$("#controls_info_toggle").click(function(){
		if(controls_info_vis === false){
			location_.controls_info.On();
			controls_info_vis = true;
			Log("Controls info window opened.");
		}
		else{
			controls_info_vis = false;
			location_.controls_info.Off();
			Log("Controls info window closed.");
		}
	});
	$("#settings_toggle").click(function(){
		if(settings_info_vis === false){
			settings_info_vis = true;
			$("#game_settings_window").css({"visibility" : "visible"});
			Log("Settings window opened.");
		}
		else{
			settings_info_vis = false;
			$("#game_settings_window").css({"visibility" : "hidden"});
			Log("Settings window closed.");
		}
	});
}

$(document).ready(function(){
	Start();
	music = true;
	
	if (!/Android|webOS|iPhone|iPad|iPod|BlackBerry|BB|PlayBook|IEMobile|Windows Phone|Kindle|Silk|Opera Mini/i.test(navigator.userAgent)) {
    $("#mobile_arrows").hide();
	}
	
  window.lastW = $(window).width();
  window.lastH = $(window).height();
  
	$(document).keydown(function(event) {
	  if(event.keyCode == 192){
      if(console_show === false && licznik <= 0){
        $("#console_window").show("medium");
        console_show = true;
      	canMove = false;
        licznik = 30;
      }
      else if(console_show === true && licznik <= 0){
        $("#console_window").hide("medium");
        console_show = false;
      	canMove = true;
        licznik = 30;
      }
	  }
	});
  
  $(document).keydown(function(event) {
    if(event.keyCode == 84 && console_show == false && !chat_in.is(":focus")){
      if(chatShow === false && licznik <= 0){
        $("#chat_window").show("slide", { direction: "left" }, "medium");
        chatShow = true;
        licznik = 30;
				setTimeout(function(){
					$("#chat_end").scrollintoview({direction: "vertical"});
				} , 1000);
      }
      else if(chatShow === true && licznik <= 0){
        $("#chat_window").hide("slide", { direction: "left" }, "medium");
        chatShow = false;
        licznik = 30;
      }
    }
  });
	
	$("#input_console").keydown(function(event) {
		if (event.which == 13 && licznik <= 0) {
			event.preventDefault();
			$("#form_console").submit();
			licznik = 100;
		}
	});
	$("#input_console2").keydown(function(event) {
		if (event.which == 13 && licznik <= 0) {
			event.preventDefault();
			$("#form_console").submit();
			licznik = 100;
		}
	});
  
	$('html, body').css({
		overflow: 'hidden',
		height: '100%'
	});
	
	$(function() {
		var $aud = $("#audio"),
				$pp  = $('#playpause'),
				$vol = $('#volume'),
				$bar = $("#progressbar"),
				AUDIO= $aud[0];

		AUDIO.volume = 0.75;
		AUDIO.addEventListener("timeupdate", progress, false);

		function getTime(t) {
			var m=~~(t/60), s=~~(t % 60);
			return (m<10?"0"+m:m)+':'+(s<10?"0"+s:s);
		}

		function progress() {
			$bar.slider('value', ~~(100/AUDIO.duration*AUDIO.currentTime));
			$pp.text(getTime(AUDIO.currentTime));
		}

		$vol.slider( {
			value : AUDIO.volume*100,
			slide : function(ev, ui) {
				$vol.css({background:"hsla(180,"+ui.value+"%,50%,1)"});
				AUDIO.volume = ui.value/100; 
			} 
		});

		$bar.slider( {
			value : AUDIO.currentTime,
			slide : function(ev, ui) {
				AUDIO.currentTime = AUDIO.duration/100*ui.value;
			}
		});

		$pp.click(function() {
			return AUDIO[AUDIO.paused?'play':'pause']();
		});
	}); // Music Player
	
	liMin();
	stats();
	options();
  
  AJAXUpdate(); // !!!
	
	var shadowsDOM = $("#shadows");
	
	$('#checkbox-1').change(function() {
		if(shadows === true){
			shadowsDOM.css({"visibility" : "hidden"});
		}
		else{
			shadowsDOM.css({"visibility" : "visible"});
			if(licznik <= 0){
				location_.unLoad();
				location_.Load();
				licznik = 20;
			}
		}
		shadows = !shadows;
	});
	
	$('#checkbox-2').change(function() {
		fastStatsUpdate = !fastStatsUpdate;
	});
	
	$('#checkbox-3').change(function() {
		SFX_sounds = !SFX_sounds;
	});
	
	$('#checkbox-4').change(function() {
		if(players_vis === true){
			$("#other_players").css({"display" : "none"});
    }
		if(players_vis === false){
			$("#other_players").css({"display" : "inline"});
    }
    
		players_vis = !players_vis;
	});
  
  window.onbeforeunload =
  function confirmExit(e) {
    if(canExit === false){
      return 'Wait! You MUST wait 3 seconds! You MUST!';
    }
		AJAX_save();
		return null;
  };
  
	
	document.body.onmousedown = function(e) { 
		if (!$(e.target).closest("#eq, #eq_items, #MainMissile, #chat_window, #options, #console_window, #npsc").length)
			mouseDown = 1;
	}
	document.body.onmouseup = function() {
		mouseDown = 0;
	}
  
  setTimeout("movement()", 0); // start of gameLoop()
	
	audio.play();
	
	console_content = "";
	
	setTimeout("EQsave()", 10000);
	
	Log("Engine started.");
});