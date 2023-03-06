<?php
session_start();

$chatFile = fopen("chat.txt", "r+") or die("FILE ERROR // CHAT XML");

$action = $_GET['action'];
$message = $_GET['message'];
$time = $_GET['time'];
$nick = $_SESSION['userName'];

if($action == "read"){
  echo fread($chatFile, filesize("chat.txt"));
}
else if($action == "write"){
  $chatDATA = fread($chatFile, filesize("chat.txt"));
  
  fwrite($chatFile, "<b>" . $nick . ":</b> " . $message . " <i>[" . $time . "]</i><br />");
  
  echo "writed";
}
else if($_POST['action'] == "clear"){
  ftruncate($chatFile, 0);
  
  echo "cleared";
}
?>