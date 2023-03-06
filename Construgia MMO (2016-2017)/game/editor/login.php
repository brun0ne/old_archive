<?php

session_start();

$password = $_POST['password'];
$login = $_POST['login'];

if($login == "BrunonDEV" && $password == "X"){
  $_SESSION['userE'] = "BrunonDEV";
  header("Location: editor.php");
  exit();
}
else if($login == "Y" && $password == "Y"){
  $_SESSION['userE'] = "Y";
  header("Location: editor.php");
  exit();
}
else{
  header("Location: index.php?msg=Wrong%20login%20or%20password.");
  exit();
}

?>