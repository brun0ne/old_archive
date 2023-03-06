<html>
  
  <head>
    <title>Layout Upload Page | Web Interface</title>
  </head>
  
  <body style="font-family: Consolas, Consolas; background-color: #10100a; color: white;">
    
    <center><br /><br />
    
<?php
session_start();

if(!isset($_SESSION['userName'])){
  echo "session expired";
  exit;
}

$user = $_SESSION['userName'];

echo "<div style='position: absolute; right: 0.5%; bottom: 0.5%;'>Logged in as <b>" . $user . "</b></div>";

$uploadOk = 1;

if(isset($_POST["submit"])) {
  if ($_FILES["fileToUpload"]["size"] > 500000) {
    echo "Sorry, your file is too large.<br />";
    $uploadOk = 0;
  }
  
  if ($uploadOk == 0) {
    echo "Sorry, there was an error while uploading your layout or your layout file is broken.<br />";
  } else {
    if (move_uploaded_file($_FILES["fileToUpload"]["tmp_name"], '../users/' . $user . '/layout.txt')) {
      echo "<h3>Your layout has beed uploaded.</h3><br />";
    } else {
      echo "Sorry, there was an error uploading your layout.<br />";
    }
  }

  echo "<br /><b><a href='index.php'>Return to the interface</a></b>";
}
?>
    </center>
    
  </body>
  
</html>