<?php

session_start();

if(!isset($_SESSION["user"])){
  header("Location: ../index.php?msg=You%20must%20log%20in%20first.");
  exit;
}

?>

<!DOCTYPE html>
<html lang="pl">
	<head>
		<meta charset="utf-8" />
    <meta http-equiv="Cache-control" content="no-cache">
		<title>Web Inteface | Interface</title>
    
		<link rel="icon" href="../ICON.png" type="image/x-icon"/>
		
    <script src="http://construgia.c0.pl/remadds.js"></script>
    
    <!-- Latest compiled and minified CSS -->
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css" integrity="sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u" crossorigin="anonymous">

    <!-- Optional theme -->
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap-theme.min.css" integrity="sha384-rHyoN1iRsVXV4nD0JutlnGaslCJuC7uwjduW9SVrLvRYooPp2bWYgmgJQIXwl/Sp" crossorigin="anonymous">
    
		<script src="codemirror-5.25.0/lib/codemirror.js"></script>
		<link rel="stylesheet" href="http://codemirror.net/lib/codemirror.css">
		<link rel="stylesheet" href="https://codemirror.net/theme/isotope.css">
		<script src="codemirror-5.25.0/mode/javascript/javascript.js"></script>
		<script src="codemirror-5.25.0/mode/xml/xml.js"></script>
		<script src="codemirror-5.25.0/mode/htmlmixed/htmlmixed.js"></script>
		<script src="codemirror-5.25.0/mode/css/css.js"></script>
		<script src="codemirror-5.25.0/mode/php/php.js"></script>
		<script src="http://codemirror.net/addon/selection/mark-selection.js"></script>
		<script src="http://codemirror.net/addon/search/searchcursor.js"></script>
		<script src="https://codemirror.net/addon/selection/active-line.js"></script>
		
		<script src="https://code.jquery.com/jquery-3.1.1.min.js"></script>
		
		<script src="jquery_extensions.js"></script>
		
		<link rel="stylesheet" href="https://ajax.googleapis.com/ajax/libs/jqueryui/1.12.1/themes/smoothness/jquery-ui.css">
		<script src="https://ajax.googleapis.com/ajax/libs/jqueryui/1.12.1/jquery-ui.min.js"></script>
		
		<script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js" integrity="sha384-Tc5IQib027qvyjSMfHjOMaLkfuWVxZxUPnCJA7l2mCWNIpG9mGCD8wGNIcPD7Txa" crossorigin="anonymous"></script>
    
		<script src="parser.js"></script>
		
		<script src="ajax.js"></script>
		
		<script src="classes.js"></script>
		
    <script src="mainJS.js"></script>
		
		<script src="contextmenu.js"></script>
		
		<link rel="stylesheet" type="text/css" href="styles.css">
    <?php
      session_start();
    ?>
    
	</head>
  
  <body>
		<noscript>
			<div class="noscriptmsg">
				You have no javascript enabled, page won't work without it.
			</div>
		</noscript>
		
		<div id="hidden_windows" style="position: absolute; right: 1%; top: 2%; text-align: right;"></div>
		
		<div id="windows" style="height: 100%; width: 100%; overflow: hidden;"></div>
		<div id="editors" style="height: 100%; width: 100%; overflow: hidden;"></div>
		
		<div id="logout_button" style="position: fixed; right: 0.5%; bottom: 0.5%;">
			<a href="../logout.php">Logout</a>
		</div>
		
		<div class="btn-group" style="position: fixed; left: 1%; top: 2%;">
			<button type="button" class="btn btn-danger dropdown-toggle" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
				New window <span class="caret"></span>
			</button>
			<ul class="dropdown-menu">
				<li><a href="javascript:newWindow('console')">Console</a></li>
				<li><a href="javascript:newWindow('variables')">Variables</a></li>
				<li><a href="javascript:newWindow('storage')">Storage</a></li>
				<li><a href="javascript:newWindow('editor')">Editor</a></li>
				<li role="separator" class="divider"></li>
				<li><a href="javascript:newWindow('settings')">Settings</a></li>
			</ul>
		</div>
		
		<!-- CONTEXT MENU -->
		
		<ul id="context_menu" class="dropdown-menu">
			<li id="ccm_more" style="display: none" class="nocustomcm"><a href="#" class="nocustomcm">More</a></li>
			<li><a href="javascript:closeAll()">Close all</a></li>
			<li class="dropdown-submenu dropdown-menu-right">
        <a tabindex="-1" href="javascript:;">Delete all <span class="glyphicon glyphicon-chevron-right" style="font-size: 85%;" aria-hidden="true"></span></a>
        <ul id="pop_1" class="dropdown-menu">
          <li><a href="javascript:global.deleteAll(0, true)">Variables</a></li>
          <li><a href="javascript:storage.deleteAll(0, true)">Files</a></li>
        </ul>
      </li>
		</ul>
		
		<!-- CONTEXT MENU -->
		
		<!-- OPEN AS TXT / NORMAL DIALOG -->
		
		<div id="open_as_modal" class="modal fade" role="dialog" style='color: black'>
			<div class="modal-dialog">
				
				<!-- Modal content-->
				<div class="modal-content">
					<div class="modal-header">
						<button type="button" class="close" data-dismiss="modal">&times;</button>
						<h4 class="modal-title">Choose</h4>
					</div>
					<div class="modal-body">
						<p>
							Do you want to open this file as txt or in normal mode?
							
							<br /><br />
							
							Open as normal file may start downloading if it's not a common file.
						</p>
					</div>
					<div class="modal-footer">
						<button type="button" class="btn btn-default" onclick="storage.open_as_txt(storage.actOpening, 0, true)" data-dismiss="modal">As TXT</button>
						<button type="button" class="btn btn-default" onclick="storage.open(storage.actOpening, 0, true, true)" data-dismiss="modal">Normal</button>
						<button type="button" class="btn btn-default" onclick="storage.actOpening = ''" data-dismiss="modal">Close</button>
					</div>
				</div>
				
			</div>
		</div>
		
		<!-- OPEN AS TXT / NORMAL DIALOG -->
		
		<!-- BETTER ALERT DIALOG -->
		
		<div id="alert_modal" class="modal fade" role="dialog" style='color: black'>
			<div class="modal-dialog">
				
				<!-- Modal content-->
				<div class="modal-content">
					<div class="modal-header">
						<button type="button" class="close" data-dismiss="modal">&times;</button>
						<h4 class="modal-title" id="alert_title"></h4>
					</div>
					<div class="modal-body">
						<p id="alert_content"></p>
					</div>
					<div id="alert_buttons" class="modal-footer">
						<span id="alert_plus_buttons"></span>&nbsp<button type="button" class="btn btn-default" onclick="" data-dismiss="modal">Close</button>
					</div>
				</div>
				
			</div>
		</div>
		
		<!-- BETTER ALERT DIALOG -->
  </body>
  
</html>