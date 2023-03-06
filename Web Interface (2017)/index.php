<!DOCTYPE html>
<html lang="pl">
	<head>
		<meta charset="utf-8" />
    <meta http-equiv="Cache-control" content="no-cache">
		<title>Web Inteface</title>
    
		<link rel="icon" href="ICON.png" type="image/x-icon"/>
		
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css" integrity="sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u" crossorigin="anonymous">
		
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap-theme.min.css" integrity="sha384-rHyoN1iRsVXV4nD0JutlnGaslCJuC7uwjduW9SVrLvRYooPp2bWYgmgJQIXwl/Sp" crossorigin="anonymous">
    
    <script src="../remadds.js"></script>
    
		<script src="https://code.jquery.com/jquery-3.1.1.min.js"></script>
		
		<script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js" integrity="sha384-Tc5IQib027qvyjSMfHjOMaLkfuWVxZxUPnCJA7l2mCWNIpG9mGCD8wGNIcPD7Txa" crossorigin="anonymous"></script>
    
    <script src="js.js"></script>
		
		<link rel="stylesheet" type="text/css" href="styles.css">
    <?php
    
      ob_start();
      session_start();

    ?>
    
	</head>
  
  <body>
		<noscript>
			You have no javascript enabled, page won't work without it.
		</noscript>
    <br /><br />
    <center style="margin-left: auto; margin-right: auto;">
      <h5 id="welcometo_container">
        <span id="welcometo">
          Welcome to..
        </span>
      </h5>
      <h1>
        Web Inteface™
      </h1>
      <h6 id="by_container">
        <span id="by">
          by Brunon Blok
        </span>
      </h6>
      
      <br />
      
      <?php
        echo "<center style='color: red;'>" . $_GET["msg"] . "</center>"
      ?>
      
      <br /><br />
      
      <form method="post" action="login.php" id="login_form">
        <div class="form-group" >
          <div class="input-group" style="text-align: center;">
            <label for="login">Login:</label>
            <input type="text" class="form-control" id="login" name="login">
          </div>
        </div><br />
        <div class="form-group">
          <div class="input-group" style="text-align: center;">
            <label for="password">Password:</label>
            <input type="password" class="form-control" id="password" name="password">
          </div>
        </div><br />
        <div class="checkbox">
          <label><input type="checkbox" id="accept" name="accept" value="ok"> I accept <a href="terms.php">terms of use</a></label>
        </div>
        <br />
        <button type="submit" class="btn btn-danger" name="btn-login">Log in</button>
      </form>
			
			<form method="post" action="register.php" id="register_form" style="display: none;">
        <div class="form-group" >
          <div class="input-group" style="text-align: center;">
            <label for="login">Login:</label>
            <input type="text" class="form-control" id="login" name="login">
          </div>
        </div><br />
        <div class="form-group">
          <div class="input-group" style="text-align: center;">
            <label for="password">Password:</label>
            <input type="password" class="form-control" id="password" name="password">
          </div>
        </div><br />
        <div class="checkbox">
          <label><input type="checkbox" id="accept" name="accept" value="ok"> I accept <a href="terms.php">terms of use</a></label>
        </div>
        <br />
        <button type="submit" class="btn btn-danger" name="btn-register">Register me!</button>
      </form>
			
			<a id="register_login_button" href="javascript:registerToggle();" style="bottom: 4%; position: absolute; margin-left: -2.1%; font-size: 1.5vmin;">register me</a>
      
      <div id="bottom_bar_container">
        <span id="bottom_bar">
          Copyright 2016 Brunon Blok | Service is not responsible for the code written by users and the possible damage it caused.
        </span>
      </div>
    </center>
  </body>
  
</html>