<!DOCTYPE html>
<html lang="pl">
	<head>
		<meta charset="utf-8" />
    <meta http-equiv="Cache-control" content="no-cache">
		<title>Construgia - MMORPG</title>
    
    <meta name="description" content="Free dynamic MMORPG">
    <meta name="keywords" content="MMO, RPG, Construgia, Game, Fun, Fight, World">
    <meta name="author" content="Brunon Blok">
		
    <script src="../remadds.js"></script>
    
		<link rel="stylesheet" href="game/jquery-ui-1.12.1/jquery-ui.min.css">
	
		<script type="text/javascript" src="game/jquery-3.1.1.min.js"></script>
		<!--<script src="jquery-ui-1.12.1/jquery-ui.min.js"></script>-->
    
    <!-- Latest compiled and minified CSS -->
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css" integrity="sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u" crossorigin="anonymous">

    <!-- Optional theme -->
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap-theme.min.css" integrity="sha384-rHyoN1iRsVXV4nD0JutlnGaslCJuC7uwjduW9SVrLvRYooPp2bWYgmgJQIXwl/Sp" crossorigin="anonymous">

    <!-- Latest compiled and minified JavaScript -->
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js" integrity="sha384-Tc5IQib027qvyjSMfHjOMaLkfuWVxZxUPnCJA7l2mCWNIpG9mGCD8wGNIcPD7Txa" crossorigin="anonymous"></script>
		
    <script src="mainJS.js"></script>
    
		<link rel="icon" href="game/graphics/player/player.png" type="image/x-icon"/>
		
		<link rel="stylesheet" type="text/css" href="styles.css">
    <?php
      session_start();
    ?>
    
	</head>
  
  <body>
    <div id='leftPage'>
      <div class="block" style="background-color: #ffccb3;">
        <center><h3><b>MENU</b></h3></center>
        <ul>
          <li class="link" onclick="ChangeCenter('News');">News</li>
          <li class="link" onclick="ChangeCenter('About');">About</li>
          <li class="link" onclick="ChangeCenter('Statistics');">Statistics</li>
          <li class="link" onclick="ChangeCenter('FAQ');">FAQ</li>
          <li class="link" onclick="ChangeCenter('Screenshots');">Screenshots</li>
          <li class="link" onclick="ChangeCenter('Creators');">Credits</li>
        </ul>
      </div>
      <br />
      <div class="block" style="background-color: #b3ffff;">
        <center><h3><b>IMPORTANT LINKS</b></h3></center>
        <ul>
          <li class="link"><i>Links</i></li>
        </ul>
      </div>
      <br />    
    </div>
    
    <div id='centerPage' style="color: black;">
      <div id='centerPage_content' style='margin-left: 2%; margin-right: 2%; margin-top: 1%;'>
        <?php
          if($_GET['res'] == "success"){
            echo "<center><h3><b>Successfully registered.</b> Now you can log in into the game!</h3></center><br /><br />";
          }
          else if(isset($_GET['res'])){
            echo "<center><h3><b>Registration error: </b>" . $_GET['msg'] . "</h3></center>";
          }
        
          if(isset($_GET['lden'])){
            echo "<center><h3><b>Login error: </b>" . $_GET['msg'] . "</h3></center><br /><br />";
          }
        
          if(isset($_GET['cMsg'])){
           echo "<center><h3>" . $_GET['cMsg'] . "</h3></center><br /><br />";
          }
        ?>
        <?php include 'sites/news.php'; ?>
      </div>
    </div>
    
    <div id="rightPage">
      <center>
        <div class="block" style="background-color: #bbff99;">
          <div style="margin-left: 2%; margin-right: 2%;">
            <?php

            if(isset($_SESSION['user'])){
              include("helpfiles/logged_html.php");
            }
            else{
              include("helpfiles/log_html.php");
            }
            
            ?>
            <br />
          </div>
        </div>
        <br />
        <div class="block" style="background-color: #ffff80;">
          <div style="margin-left: 2%; margin-right: 2%;">
            <h3><b>Register</b></h3>

            <form method="post" action="dbfiles/register.php">
              <div class="form-group" >
                <div class="input-group">
                  <label for="login">Login:</label>
                  <input type="text" class="form-control" id="login" name="login">
                </div>
              </div>
              <div class="form-group">
                <div class="input-group">
                  <label for="email">E-mail:</label>
                  <input type="e-mail" class="form-control" id="email" name="email">
                </div>
              </div>
              <div class="form-group">
                <div class="input-group">
                  <label for="password">Password:</label>
                  <input type="password" class="form-control" id="password" name="password">
                </div>
              </div>
              <button type="submit" class="btn btn-primary" name="btn-signup" disabled><u>REGISTER! (closed alpha)</u></button>
            </form>
            <br />
          </div>
        </div>
        <div id='bottomPage' style="font-family: consolas, consolas; font-size: 1.5vmin;">
          <center>Copyright Brunon Blok 2016 -- All rights reserved.</center>
        </div>
      </center>
    </div>
    
    <div id='upperSlider'><center></center></div>
    <div id='und_logo_text'>
      Dynamic real-time MMORPG
    </div>
  </body>
</html>

<?php ob_end_flush(); ?>