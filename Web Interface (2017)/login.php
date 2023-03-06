<?php
 ob_start();
 session_start();
 require_once 'dbconnect.php';
 
 $error = false;
 
 if( isset($_POST['btn-login']) ) {
   
  if(isset($_POST["accept"]))
    ;
   else{
     header("Location: index.php?msg=You must accept <a href='terms.php'>terms of use</a> before logging in.");
     
     exit;
   }
  
  // prevent sql injections / clear user invalid inputs ->
  $email = trim($_POST['login']);
  $email = strip_tags($email);
  $email = htmlspecialchars($email);
  
  $pass = trim($_POST['password']);
  $pass = strip_tags($pass);
  $pass = htmlspecialchars($pass);
  
  if(empty($email)){
   $error = true;
   $errMSG = "Please enter your login.";
  }
  
  if(empty($pass)){
   $error = true;
   $errMSG = "Please enter your password.";
  }
  
  // NO ERROR ->
  if (!$error) {
   
   $password = hash('sha256', $pass);
  
   $res=mysql_query("SELECT ID, nick, password FROM Interface WHERE nick='$email'");
   $row=mysql_fetch_array($res);
   $count = mysql_num_rows($res); // if uname/pass correct it returns must be 1 row
   
   if( $count == 1 && $row['password'] == $password ) {
    $_SESSION["user"] = $row['ID'];
    $_SESSION['userName'] = $row['nick'];
    header("Location: interface/");
    exit;
   } else {
    $errMSG = "Wrong login or password, try again...";
    header("Location: index.php?lden=&msg=" . $errMSG);
    exit;
   }
  }
 }
 
 header("Location: index.php?lden=&msg=" . $errMSG);
 exit;

 ob_end_flush();
?>