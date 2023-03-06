<h3><b>You're already logged in!</b></h3>

<br />

<h4><b><?php echo $_SESSION['userName']; ?></b></h4>

<br />

<form method="post" action="game/index.php">
  <span class="glyphicon glyphicon-chevron-right" aria-hidden="true"></span>
  <button type="submit" name="btn-login" class="btn btn-primary">JOIN THE GAME!</button>  
  <span class="glyphicon glyphicon-chevron-left" aria-hidden="true"></span>
</form>

<br /><br />

<form method="get" action="dbfiles/logout.php">
  <button type="submit" name="logout" class="btn btn-danger btn-xs">Logout</button>
</form>

<br />