<!DOCTYPE html>
<html lang="pl">
	<head>
		<meta charset="utf-8" />
    <meta http-equiv="Cache-control" content="no-cache">
		<title>Construgia - EDITOR - Login Page</title>
    
    <link rel="stylesheet" href="styles.css">
    
    <link rel="icon" href="graphics/favicon.png" type="image/x-icon"/>
  </head>
  
  <body>
    <center>
      <?php
      echo "<div id='message'>" . $_GET['msg'] . "</div>";
      ?>
      <br /><br />
      <h1 id="title">
        Construgia Editor
      </h1>
      <div id="login_area">
        <div id="login_area_content">
          <form method="post" action="login.php">
            <label for="login"><b>Login:</b></label><br />
            <input type="text" class="form-control" id="login" name="login"><br /><br />
            <label for="password"><b>Password:</b></label><br />
            <input type="password" class="form-control" id="password" name="password"><br /><br />
            <button type="submit" class="btn btn-primary" name="btn-signup">Join the EDITOR</button>
          </form>    
        </div>
      </div>
    </center>
  </body>
</html>