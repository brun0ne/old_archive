<?php
 ob_start();
 session_start();

 exit; // registration DISABLED

 include_once 'dbconnect.php';

 $error = false;

 if ( isset($_POST['btn-register']) ) {
   
  if(isset($_POST["accept"]))
   ;
  else{
    header("Location: index.php?msg=If you don't accept our rules, leave.");
    
    exit;
  }
 
  $name = trim($_POST['login']);
  $name = strip_tags($name);
  $name = htmlspecialchars($name);
  
  $pass = trim($_POST['password']);
  $pass = strip_tags($pass);
  
  if (empty($name)) {
   $error = true;
   $errMSG = "Please enter your login.";
  } else if (strlen($name) < 3) {
   $error = true;
   $errMSG = "Login must have atleat 3 characters.";
  }
  
  if (empty($pass)){
   $error = true;
   $errMSG = "Please enter password.";
  } else if(strlen($pass) < 6) {
   $error = true;
   $errMSG = "Password must have atleast 6 characters.";
  }
  
  $password = hash('sha256', $pass);
  
  $query = "SELECT nick FROM Interface WHERE nick='$name'";
  $query_run = mysql_query($query);

  if(mysql_num_rows($query_run) == 1){
   $errMSG = "User with this nickname already exist.";
   $error = true;
  }
   
  // no error ->
  if( !$error ) {
   
   $query = "INSERT INTO Interface(nick, password) VALUES('$name', '$password')";
   $res = mysql_query($query);
    
   if ($res) {
    $errTyp = "success";
    $errMSG = "Successfully registered, you may login now.";
    unset($name);
    unset($pass);
   } else {
    $errTyp = "danger";
    $errMSG = "Something went wrong, try again later..."; 
   } 
  }
   
  echo $errMSG;
   
  header("Location: index.php?&msg=" . $errMSG);
  exit;
 }

 ob_end_flush();

?>