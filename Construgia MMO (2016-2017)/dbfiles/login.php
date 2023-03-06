<?php
 ob_start();
 session_start();
 require_once 'dbconnect.php';
 
 $error = false;
 
 if( isset($_POST['btn-login']) ) { 
  
  // prevent sql injections/ clear user invalid inputs
  $email = trim($_POST['login']);
  $email = strip_tags($email);
  $email = htmlspecialchars($email);
  
  $pass = trim($_POST['password']);
  $pass = strip_tags($pass);
  $pass = htmlspecialchars($pass);
  // prevent sql injections / clear user invalid inputs
  
  if(empty($email)){
   $error = true;
   $errMSG = "Please enter your login.";
  }
  
  if(empty($pass)){
   $error = true;
   $errMSG = "Please enter your password.";
  }
  
  // if there's no error, continue to login
  if (!$error) {
   
   $password = hash('sha256', $pass); // password hashing using SHA256
  
   $res=mysql_query("SELECT userId, userName, userPass FROM users WHERE userName='$email'");
   $row=mysql_fetch_array($res);
   $count = mysql_num_rows($res); // if uname/pass correct it returns must be 1 row
   
   if( $count == 1 && $row['userPass']==$password ) {
    $_SESSION['user'] = $row['userId'];
    $_SESSION['userName'] = $row['userName'];
    header("Location: ../index.php");
    exit;
   } else {
    $errMSG = "Wrong login or password, try again...";
    header("Location: ../index.php?lden=&msg=" . $errMSG);
    exit;
   }
  }
 }
 
 header("Location: ../index.php?lden=&msg=" . $errMSG);
 exit;

 ob_end_flush();
?>