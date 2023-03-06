<?php
 ob_start();
 session_start();

 include_once 'dbconnect.php';

 $error = false;

 if ( isset($_POST['btn-signup']) ) {
   
  // clean user inputs to prevent sql injections
  $name = trim($_POST['login']);
  $name = strip_tags($name);
  $name = htmlspecialchars($name);
  
  $email = trim($_POST['email']);
  $email = strip_tags($email);
  $email = htmlspecialchars($email);
  
  $pass = trim($_POST['password']);
  $pass = strip_tags($pass);
  
  // basic name validation
  if (empty($name)) {
   $error = true;
   $errMSG = "Please enter your login.";
  } else if (strlen($name) < 3) {
   $error = true;
   $errMSG = "Login must have atleat 3 characters.";
  }
  
  //basic email validation
  if ( !filter_var($email,FILTER_VALIDATE_EMAIL) ) {
   $error = true;
   $errMSG = "Please enter valid email address.";
  } else {
   // check email exist or not
   $query = "SELECT userEmail FROM users WHERE userEmail='$email'";
   $result = mysql_query($query);
   $count = mysql_num_rows($result);
   if($count!=0){
    $error = true;
    $errMSG = "Provided Email is already in use.";
   }
  }
  // password validation
  if (empty($pass)){
   $error = true;
   $errMSG = "Please enter password.";
  } else if(strlen($pass) < 6) {
   $error = true;
   $errMSG = "Password must have atleast 6 characters.";
  }
  
  // password encrypt using SHA256();
  $password = hash('sha256', $pass);
  
  // if there's no error, continue to signup
  if( !$error ) {
   
   $query = "INSERT INTO users(userName,userEmail,userPass) VALUES('$name','$email','$password')";
   $res = mysql_query($query);
    
   $query2 = "INSERT INTO users_ingame(LVL, GOLD, EXP, HP, POSX, POSY, LOCATION, ISFIRST, LTON, NICK) VALUES('1', '0', '0', '100', '0', '0', 'Icyt_Town', '1', '', '$name')";
   $res2 = mysql_query($query2);
    
   if ($res && $res2) {
    $errTyp = "success";
    $errMSG = "Successfully registered, you may login now";
    unset($name);
    unset($email);
    unset($pass);
   } else {
    $errTyp = "danger";
    $errMSG = "Something went wrong, try again later..."; 
   } 
  }
   
  header("Location: ../index.php?res=" . $errTyp . "&msg=" . $errMSG);
  exit();
 }

 ob_end_flush();

?>