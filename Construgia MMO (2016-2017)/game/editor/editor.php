<!DOCTYPE html>
<html lang="pl">
	<head>
    <?php
    session_start();
    
    if(!isset($_SESSION["userE"])){
      header("Location: index.php?msg=You%20must%20<b>log%20in</b>%20first.");
      exit;
    }
    ?>
		<meta charset="utf-8" />
    <meta http-equiv="Cache-control" content="no-cache">
		<title>Construgia - EDITOR</title>
    
    <link rel="stylesheet" href="editor/styles.css">
		
		<script src="codemirror/codemirror-5.22.0/lib/codemirror.js"></script>
		<link rel="stylesheet" href="codemirror/codemirror-5.22.0/lib/codemirror.css">
		<link rel="stylesheet" href="codemirror/codemirror-5.22.0/theme/monokai.css">
		<script src="codemirror/codemirror-5.22.0/mode/javascript/javascript.js"></script>

    <script type="text/javascript" src="jquery-3.1.1.min.js"></script>
    <script type="text/javascript" src="shortcut.js"></script>
    
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css" integrity="sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u" crossorigin="anonymous">
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap-theme.min.css" integrity="sha384-rHyoN1iRsVXV4nD0JutlnGaslCJuC7uwjduW9SVrLvRYooPp2bWYgmgJQIXwl/Sp" crossorigin="anonymous">
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js" integrity="sha384-Tc5IQib027qvyjSMfHjOMaLkfuWVxZxUPnCJA7l2mCWNIpG9mGCD8wGNIcPD7Txa" crossorigin="anonymous"></script>
    
    <script type="text/javascript" src="editor/classes.js"></script>
    <script type="text/javascript" src="editor/mainJS.js"></script>
    <script type="text/javascript" src="editor/mapSettings.js"></script>

    <script type="text/javascript" src="AJAX/ajax.js"></script>
    
    <link rel="icon" href="graphics/favicon.png" type="image/x-icon"/>
  </head>
  
  <body class="disableTextSelect">
    <div id="objects" style="position: absolute;"></div>
    
    <div id="user_nick">
      You're logged in as <b><?php echo $_SESSION['userE'] ?></b>.
    </div>
    
    <div id="map_name_area">
      You're editing map nammed: <b id="map_name">---</b> <elem id="map_leave_area"></elem>
    </div>
		
		<div id="editor_mode_buttons">
			<span onclick="toggleMode(0)" class="clickable">OBJECTS</span> <span class="clickable" onclick="toggleMode(1)">NPCs</span>
		</div>
		
		<div id="mousepos" style="position: absolute; bottom: 1%; right: 21.5%; font-family: consolas, consolas; font-size: 2.0vmin;">
			X: <span id="mouse_x"></span>, Y: <span id="mouse_y"></span>
		</div>
    
    <br />
    
    <img id="handlerd" style="position: absolute; z-index: 2;" src="" />
    
    <div id="playerStartInfo" style="position: absolute; left: 0.5%; top: 8%; font-family: consolas, consolas; font-size: 2.0vmin;"></div>
    
    <div id="container" class="block">  <!-- _______________OBJECTS CONTAINER    -->
      <div id="inner_container" style="margin-left: 5%; margin-right: 5%;"></div>
      <div id="file_upload" style="display: none;">
        <center>
          <form action="upload.php" method="post" enctype="multipart/form-data">
            <input type="file" name="fileToUpload" id="fileToUpload">
            <br />
            <input type="submit" value="Upload" name="submit">
            <br /><br />
          </form>
        </center>
      </div>
      <span id="fileUploadToggleButton" style="left: 2%!important; font-size: 1.5em;" class="glyphicon glyphicon-upload clickable" aria-hidden="true" onclick="uploadFileToggle()"></span>
    </div>
    <div id="bottom_container">
      <center id="inner_bottom_container">
        <span id="action_pmarker" class="glyphicon glyphicon-map-marker clickable" style="font-size: 1.5em;" aria-hidden="true" onclick="setAction('playerMarker')"></span>
        <span id="action_erase" class="glyphicon glyphicon-erase clickable" style="font-size: 1.5em;" aria-hidden="true" onclick="setAction('delete')"></span>
        <span id="action_move" class="glyphicon glyphicon-move clickable" style="font-size: 1.5em;" aria-hidden="true" onclick="setAction('move')"></span>
        <span id="action_resize" class="glyphicon glyphicon-resize-small clickable" style="font-size: 1.5em;" aria-hidden="true" onclick="setAction('resize')"></span>
        <span id="action_select" class="glyphicon glyphicon-tag clickable" style="font-size: 1.5em;" aria-hidden="true" onclick="setAction('select')"></span>
				<span id="action_colbuild" class="glyphicon glyphicon-asterisk clickable" style="font-size: 1.5em;" aria-hidden="true" onclick="setAction('collider_build')"></span>
      </center>
    </div>
    <div id="action_info_container" style="position: absolute; left: 1%; bottom: 1%; font-family: consolas, consolas;">Action: <b id="act_action_info">none</b></div>
    
    <div id="top_options" class="block">  <!-- _______________UPPER OPTIONS    -->
      <center id="top_options_inner">
        <span class="glyphicon glyphicon-file clickable" style="font-size: 1.5em;" aria-hidden="true" onclick="createMap();"></span>
        <span class="glyphicon glyphicon-folder-open clickable" style="font-size: 1.5em;" aria-hidden="true" onclick="loadMap();"></span>
        <span class="glyphicon glyphicon-trash clickable" style="font-size: 1.5em;" aria-hidden="true" onclick="deleteMap();"></span>
        <span class="glyphicon glyphicon-floppy-disk clickable" style="font-size: 1.5em;" aria-hidden="true" onclick="saveMap();"></span>
        <span class="glyphicon glyphicon-cog clickable" style="font-size: 1.5em;" aria-hidden="true" onclick="toggleSettingsWindow();"></span>
				<span class="glyphicon glyphicon-list clickable" style="font-size: 1.5em;" aria-hidden="true" onclick="toggleMapListWindow();"></span>
      </center>
    </div>
    
    <div id="mobile_arrows" style="position: absolute; bottom: 1%; right: 23%;">
      <button onclick="camera.x -= 10; Camera_Update();" style="width: 5em;  height: 5em;">&larr;</button>
      <button onclick="camera.x += 10; Camera_Update();" style="width: 5em;  height: 5em;">&rarr;</button>
      <button onclick="camera.y -= 10; Camera_Update();" style="width: 5em;  height: 5em;">&uarr;</button>
      <button onclick="camera.y += 10; Camera_Update();" style="width: 5em;  height: 5em;">&darr;</button>
    </div>
    
    <div id="settings_window" class="block"> <!-- _______________SETTINGS WINDOW    -->
      <div id="settings_window_inner">
        <img id="settings_window_off_button" class="clickable" src="graphics/exit.png" onclick="toggleSettingsWindow()"/>
        
        <div style="font-size: 4.0vmin;"><center>Map Settings</center></div>
        <div id="settings_left_block">
          
          <b>Map title: </b><br /><br /><br />
          <b>Map ground image: </b><br /><br /><br />
          <b>Map ground layer image: </b><br /><br /><br />
          <b>Map width: </b><br /><br /><br />
          <b>Map height: </b><br /><br /><br />
        </div>
        <div id="settings_right_block">
          <form id="form_map_name" name="form_map_name" action="" onsubmit="return mapNameChange()" method="post">
            <input style="width: 80%; height: 4%" name="new_map_name" id="new_map_name" placeholder="" type="text" />
          </form><br /><br />
          
          <form id="form_map_ground" name="form_map_ground" action="" onsubmit="return mapGroundChange()" method="post">
            <input style="width: 80%; height: 4%" name="new_map_ground" id="new_map_ground" placeholder="" type="text" />
          </form><br /><br />
          
          <form id="form_map_ground_layer" name="form_map_ground_layer" action="" onsubmit="return mapGroundLayerChange()" method="post">
            <input style="width: 80%; height: 4%" name="new_map_ground_layer" id="new_map_ground_layer" placeholder="" type="text" />
          </form><br /><br />
          
          <form id="form_map_width" name="form_map_width" action="" onsubmit="return mapWidthChange()" method="post">
            <input style="width: 80%; height: 4%" name="new_map_width" id="new_map_width" placeholder="" type="text" />
          </form><br /><br />
          
          <form id="form_map_height" name="form_map_height" action="" onsubmit="return mapHeightChange()" method="post">
            <input style="width: 80%; height: 4%" name="new_map_height" id="new_map_height" placeholder="" type="text" />
          </form><br /><br />
        </div>
      </div>
    </div>
    
    <div id="map_list_window" class="block"> <!-- _______________MAP LIST WINDOW    -->
      <div id="map_list_window_inner">
        <img id="map_list_window_off_button" class="clickable" src="graphics/exit.png" onclick="toggleMapListWindow()"/>
        <center>
          <h3>
            List of maps:
          </h3>
        </center>
        <br />
        <ul id="map_list">
          
        </ul>
      </div>
    </div>
		
		<div id="map_script_window" class="block"> <!-- _______________MAP SCRIPT WINDOW    -->
			<div id="map_script_window_inner">
				<h3 style="position: absolute; top: -3%; width: 95%; text-align: center;">
					Map script:
				</h3>
        <br />
        <div id="map_script_content">
					
					<h4>
						Start:
					</h4>
					<div id="map_script_cStart" style="overflow: auto;"></div>
					
					<h4>
						Update:
					</h4>
					<div id="map_script_cUpdate" style="overflow: auto;"></div>
				</div>
      </div>
			<img id="map_script_window_off_button" class="clickable" src="graphics/exit.png" onclick="toggleMapScriptWindow()"/>
    </div>
    
		<span style="font-size: 1.6em; position: absolute; right: 1%; bottom: 40%;" class="clickable" onclick="toggleMapScriptWindow()">&lt;&gt;</span>
		
    <div id="selected_window" class="block">  <!-- _______________SELECTED WINDOW    -->
      <div id="inner_selected_window">
        <center><b id="selected_is_info">Nothing's selected.</b></center>
        <br />
        <b>ID: </b><span id="selected_id_info">---</span><br /><br />
        <b>X: </b><span id="selected_x_info">---</span>, 
        <b>Y: </b><span id="selected_y_info">---</span><br /><br />
        <b>W: </b><span id="selected_w_info">---</span>, 
        <b>Scale: </b><span id="selected_scale_info">---</span><b>%</b><br /><br />
        <b>IMG: </b><span id="selected_img_info">---</span><br /><br />
        
        <b>Colliders: </b>
        <button id="collidersSelectedChoose" onclick="collidersSelectedChange()">---</button>
        
        <br /><br />
        
        <b>Player hiding: </b>
        <button id="hidingSelectedChoose" onclick="hidingSelectedChoose()">---</button>
        
        <br /><br />
        
        <b>Can be entered: </b>
        <button id="canEnteredSelectedChoose" onclick="canEnteredSelectedChoose()">---</button>
				
				<br />
				
				<form id="form_gotomap" name="form_gotomap" action="" onsubmit="return gotoMapChange()" method="post" style="display: none;">
					<br />
          <b>Goto map: </b>
          <input style="width: 60%; height: 5%;" name="new_gotomap" id="new_gotomap" placeholder="" type="text" />
					<br /><br />
          <b>Goto coords: </b>
          <input style="width: 20%; height: 5%;" name="new_gotomap_x" id="new_gotomap_x" placeholder="0" type="text" />
					<input style="width: 20%; height: 5%;" name="new_gotomap_y" id="new_gotomap_y" placeholder="0" type="text" />
					
					<center><button style="display: none;" type="submit">Submit</button></center>
        </form>
				
        <br />
        
        <b>Shadow: </b>
        <button id="shadowSelectedChoose" onclick="shadowSelectedChoose()">---</button>
        
        <br /><br />
        
        <form id="form_size" name="form_size" action="" onsubmit="return sizeSelectedChange()" method="post">
          <b>Size: </b>
          <input style="width: 15%; height: 5%;" name="new_w" id="new_w" placeholder="100" type="text" /><b>%</b>
        </form>
				
				<br />
				
				<center>
					<button id="putOnTopButton" onclick="putOnTop()">Put on top</button>
					
					<button id="unselectButton" onclick="if(selected != null) selectedReset(); else alert(`Nothing's selected!`);">Unselect</button>
				</center>
				
        <br />
      </div>
    </div>
    
    <a id="logout_button" href="logout.php">LOGOUT</a>
  </body>
</html>