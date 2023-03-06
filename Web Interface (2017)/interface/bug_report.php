<?php

session_start();

if(!isset($_SESSION['userName'])){
  echo "session expired";
  exit;
}

$user = $_SESSION['userName'];
$desc = $_POST['description'];
$user_data = $_POST['user_data'];
$DATA = $_POST['bug_raport_DATA'];

if($desc == "")
  $desc = "<i>not entered</i>";

// Sending e-mail -->

$to      = 'brunonblok@gmail.com';
$subject = '[BUG REPORT] ' . date("m.d.y");

if($user_data == true){
  $other_user_data = "IP: <i>" . $_SERVER['REMOTE_ADDR'] . "</i>"; // todo
}
else{
  $other_user_data = "<i>NOT ALLOWED</i>";
}

$message = "<center><hr><br /><br /><b>[BUG REPORT]</b><br /><i>" . date("m.d.y") . "</i><br /><br /><b>DESCRIPTION:</b> '" . $desc . "'<br /><br /><b>ERROR DATA:</b> '" . $DATA . "'<br /><br /><b>USER DATA:</b><br /><br /><b>Nick:</b> " . $user . "<br /><b>Other data:</b> " . $other_user_data . "<br /><br /><hr></center>";

$headers[] = 'MIME-Version: 1.0';
$headers[] = 'Content-type: text/html; charset=UTF-8';

$headers[] = 'To: Brunon Blok <brunonblok@gmail.com>';
$headers[] = 'From: Web Interface Bug Reporter <bug_reporter@webinterface.com>';

mail($to, $subject, $message, implode("\r\n", $headers));

header("Location: index.php");

exit;