<?php
ob_start();
session_start();

if(!isset($_SESSION['user'])){
 header("Location: ../index.php?cMsg=You%20must%20<b>log%20in</b>%20first.");
 exit;
}
?>

<!DOCTYPE html>
<html lang="pl">
	<!-- Ostende sibi continuo -->
	<!-- $("audio").attr("src", "sounds/ReikiHealing.mp3");-->
	<head>
		<meta charset="utf-8" />
    <meta http-equiv="Cache-control" content="no-cache">
		<title>Construgia (Game) - MMORPG</title>
		
    <script src="../remadds.js"></script>
    
		<link rel="stylesheet" href="jquery-ui-1.12.1/jquery-ui.min.css">
    
    <script type="text/javascript" src="OfflineJS/offline.min.js"></script>
    
    <link rel="stylesheet" href="OfflineJS/offline-theme-dark.css">
    <link rel="stylesheet" href="OfflineJS/offline-language-english.css">
    
		<script type="text/javascript" src="jquery-3.1.1.min.js"></script>
		<script src="jquery-ui-1.12.1/jquery-ui.min.js"></script>
		<script type="text/javascript" src="PerspectiveTransform.min.js"></script>
    <script type="text/javascript" src="typed.js"></script>
    <script type="text/javascript" src="jquery.scrollintoview.min.js"></script>
		
		<script type="text/javascript" src="classes.js"></script>
    
		<script type="text/javascript" src="console.js"></script>
    <script type="text/javascript" src="chat.js"></script>
		
		<script type="text/javascript" src="Locations/Icyt_Town.js"></script>
		
		<link rel="icon" href="graphics/player/player.png" type="image/x-icon"/>
		
		<script type="text/javascript" src="movement.js"></script>
    
    <script type="text/javascript" src="players.js"></script>
    <script type="text/javascript" src="AJAX/AJAX.js"></script>
		
		<script type="text/javascript" src="js.js"></script>
		
		<link rel="stylesheet" type="text/css" href="styles.css">
	</head>
	
	<body ondragstart="return false" ondrag="return false">
    <!-- PRELOAD -->
    
    <img src="graphics/player/player.png" style="display: none;" alt="" />
    <img src="graphics/player/player_back.png" style="display: none;" alt="" />
    <img src="graphics/player/player_left.png" style="display: none;" alt="" />
    <img src="graphics/player/player_right.png" style="display: none;" alt="" />
    
    <!-- PRELOAD -->
    
		<div id="ground" class="disableTextSelect"></div>
    
    <div id="barrier" style='osition: absolute;' class="disableTextSelect"></div>
		
		<div id="objects_noth" class="disableTextSelect" style="position: absolute;"></div>
		
		<div id="shadows" class="disableTextSelect" style="position: absolute;"></div>
		
    <div id="player_graphics" class="disableTextSelect"></div>
		
    <div id="other_players" class="disableTextSelect" style="position: absolute;"></div>
    
		<div id="objects" class="disableTextSelect" style="position: absolute;"></div>
		
		<div id="npcs" class="disableTextSelect" style="position: absolute;"></div>
		
		<div id="monsters" class="disableTextSelect" style="position: absolute;"></div>
    
		<div id="canons" class="disableTextSelect" style="position: absolute;"></div>
		
		<div id='eq' class='' style='position: absolute; width: 20%; height: 100%; top: -13%; right: -2%;'>
			<div id="player_stats" style='font-family: consolas, consolas; position: absolute; top: 20%; left: 10%;'>
				<div style='font-size: 3.5vmin;' id='player_name'><?php echo $_SESSION['userName']; ?></div>
				<br />
				<div style='font-size: 2.5vmin' id='info_player_HP'></div>
        <div style='font-size: 2.5vmin' id='info_player_LVL'></div>
				<div style='font-size: 2.5vmin' id='info_player_EXP'></div>
				<div style='font-size: 2.5vmin' id='gold_info'></div>
			</div>
			<div id='fpsDisplay' style='font-family: consolas, consolas; font-size: 2.0vmin; position: absolute; right: 13%; top: 14%;'></div>
		</div>
    
    <div id='bottomButtons' style="position: absolute; bottom: 14%; right: 1%;">
      <button type="submit" onclick="javascript:window.location.href='../index.php'" class="button pointOnHover" name="btn-return">Return</button>
      <button type="submit" onclick="javascript:window.location.href='../dbfiles/logout.php?logout='" class="button pointOnHover" name="btn-logout">Logout</button>
    </div>
		
		<div id='chat_info' style='position: absolute; left: 1%; bottom: 1%; font-family: consolas, consolas; font-size: 2.0vmin;'>Press T to open game chat.</div>
    
    <div id='player_position' style='position: absolute; right: 0.6%; top: 4%; font-family: consolas, consolas; font-size: 2.0vmin;'></div>
		
		<div id="left_up_corner" class="disableTextSelect" style="position: fixed; font-size: 1.5vmin; z-index: 5;">Press ~ to open game console.</div>
		
		<div id="options" style="position: absolute; right: 2%; bottom: 2%;" class="disableTextSelect">
			<img id="settings_toggle" class="pointOnHover" width="50" height="50" src="graphics/settings_toogle.png" style="image-rendering: crisp-edges;" />
			<img id="controls_info_toggle" class="pointOnHover" width="50" height="50" src="graphics/controls_toogle.png" style="image-rendering: crisp-edges;" />
			<img id="music_toggle" class="pointOnHover" width="50" height="50" src="graphics/music_toggle_off.png" style="image-rendering: crisp-edges;" />
		</div>
	
		<div id="freediv" style="font-size: 3vmin;" class="disableTextSelect"></div> <!-- Only for "position: absolute" elements! -->
		
		<center><h2><div id="enter_info" class="disableTextSelect, b_name" style="position: absolute; left: 38%; top: 75%; visibility: hidden;">Press <b>ENTER</b> to enter this location!</div></h2></center>
		
		<br /><br /><br /><br /><br />
		
		<div id="game_settings_window" class='window' style='visibility: hidden;'>
			<img style='position: absolute; left: 21%; right: 21%;' src='graphics/dialog_background.png' />
			<center style='position: absolute; left: 45%'>
				<br />
				<h2 style='position: absolute;'>
					Settings
				</h2>
			</center>
			<br /><br /><br /><br /><br />
			<div id='other_settings' style='position: absolute; left: 22%; right: 50%; width: 25%;'>
				<fieldset>
					<legend>Other settings: </legend>
					<label for="checkbox-1">Shadows: </label>
					<input type="checkbox" name="checkbox-1" id="checkbox-1" checked><br />
					<label for="checkbox-2">Rapid stats update: </label>
					<input type="checkbox" name="checkbox-2" id="checkbox-2"><br />
					<label for="checkbox-3">SFX sounds: </label>
					<input type="checkbox" name="checkbox-3" id="checkbox-3" checked><br />
          <label for="checkbox-4">Players visibility: </label>
					<input type="checkbox" name="checkbox-4" id="checkbox-4" checked>
				</fieldset>
			</div>
			<div id='music_settings' style='position: absolute; right: 22%; left: 48%;'>
				<center><div id='settings_text'><b>Music settings:</b></div></center>
				<div id='music_player' style='margin-top: 15px;'>
					<br />
					<audio id="audio" src="sounds/IcePalace.mp3" autoplay loop>
						<p>Your browser does not support the audio element.</p>
					</audio>
					<div id="volume"></div><br>
					<div id="progressbar"></div><br> 
					<div id="playpause"></div>
					<br />
				</div>
			</div>
			<img id="settings_exit" class='pointOnHover' src="graphics/exit.png" style='position: absolute; top: 3%; left: 22%; right: 75%; width: 3%; height: auto;' onclick='javascript:settings_info_vis = false;$("#game_settings_window").css({"visibility" : "hidden"});Log("Settings window closed.");'/>
		</div>
		
		<div id="dialog" style="font-size: 2.5vmin;"></div>
		
    <!-- CHAT -->
    <div id="chat_window">
      <center style="font-family: consolas, consolas;"><b>Game Chat</b></center>
      
      <div id="chat_content">
        Loading...
      </div>
      
      <center>
        <form name="form_chat" id="form_chat" action="" onsubmit="return validateChat()" method="post">
          <input name="text_" id="chat_in" placeholder="Type a message..." type="text" />
        </form>
      </center>
    </div>
    <!-- CHAT -->
    
		<!-- CONSOLE -->
		<div id="console_window" style="display: none; border: 2px; border-style: solid; border-color: black; position: absolute; left: 5%; top: 5%; width: 35%; height: 60%; background: rgba(255,255,255,255); background-size: cover; border-radius: 6px 6px 6px 6px;">
			<div style="left: 5%; position: absolute; width: 100%; height: 100%; font-size: 2.5vmin; font-family: 'Courier New';">
				<br />
				Console
				<br />
				<br />
				<div id="console" style="bottom: 5%; position: absolute; font-style: oblique"></div>
				<div id="input">
					<form id="form_console" name="form_console" action="" onsubmit="return validateForm()" method="post">
						<input id="input_console" style="width: 30%;" name="text_" type="text" />
            <input id="input_console2" style="width: 30%;" name="text_2" type="text" />
					</form>
				</div>
			</div>
		</div>
		<!-- CONSOLE -->
		
		<div id="mobile_arrows" style="position: absolute; bottom: 1%; left: 25%;">
      <button id="marr_l"  onclick="player.pos_x -= 80" style="width: 5em;  height: 5em;">&larr;</button>
      <button onclick="player.pos_x += 80" style="width: 5em;  height: 5em;">&rarr;</button>
      <button onclick="player.pos_y -= 80" style="width: 5em;  height: 5em;">&uarr;</button>
      <button onclick="player.pos_y += 80" style="width: 5em;  height: 5em;">&darr;</button>
    </div>
		
		<div style="left: 41%; bottom: 0px; position: absolute; font-size: 2.0vmin;">Pre-Alpha | 24-11-2016 -- 16-12-2016 | Brunon Blok (C) 2016</div>
	</body>
</html>

<?php ob_end_flush(); ?>