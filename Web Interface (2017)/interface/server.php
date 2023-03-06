<?php

session_start();

if(!isset($_SESSION['userName'])){
  echo "session expired";
  exit;
}

$user = $_SESSION['userName'];
$action = $_POST["action"];
   
$arg = $_POST["arg"];

// create user's folder if it doesn't exist ->
  
if (!file_exists('../users/' . $user)) {
  mkdir('../users/' . $user, 0777, true);
}

// <-

// WINDOWS ->

if($action === "saveWindows"){
  $file = fopen('../users/' . $user . "/windows.json", "w") or die("Unable to open file!");
  
  fwrite($file, $arg);
  
  echo "Saved.";
  
  fclose($file);
}
if($action === "getWindows"){
  $file = fopen('../users/' . $user . "/windows.json", "r") or die("Unable to open file!");
  
  $cont = fread($file, filesize('../users/' . $user . "/windows.json"));
  
  fclose($file);
  
  echo $cont;
}

// <- WINDOWS | VARS ->

if($action === "saveVars"){
  $file = fopen('../users/' . $user . "/variables.json", "w") or die("Unable to open file!");
  
  fwrite($file, $arg);
  
  echo "Saved.";
  
  fclose($file);
}
if($action === "getVars"){
  $file = fopen('../users/' . $user . "/variables.json", "r") or die("Unable to open file!");
  
  $cont = fread($file, filesize('../users/' . $user . "/variables.json"));
  
  fclose($file);
  
  echo $cont;
}
  
// <- VARS | FILES ->

if($action === "saveFiles"){
  // create user's FILES folder if it doesn't exist ->
  
  if (!file_exists('../users/' . $user . "/files")) {
    mkdir('../users/' . $user . "/files", 0777, true);
  }

  // <- delete all files in this folder ->
  
  $files = glob('../users/' . $user . "/files/*");
  foreach($files as $file){
    if(is_file($file)){
      unlink($file);
    }
  }
  
  // <- save new files to empty folder ->
  
  $names = json_decode($_POST['names']); // convert strings to arrays
  $contents = json_decode($_POST['contents']);
  
  foreach($names as $i=>$name){
    $file = fopen('../users/' . $user . "/files/" . $name, "w") or die("Unable to open file!");
    
    fwrite($file, $contents[$i]);
    
    fclose($file);
    
    echo "Saved.";
  }
}
if($action === "getFiles"){
  // <- load all files from user's folder ->
  
  chdir('../users/' . $user . "/files/");
  
  $files = glob("*.*");
  
  echo json_encode($files);
  
  // <-
}
if($action === "getFileContent"){
  $url = $_POST['name'];
  
  $file = fopen('../users/' . $user . "/files/" . $url, "r") or die("Unable to open file!");
  
  $cont = fread($file, filesize('../users/' . $user . "/files/" . $url));
  
  fclose($file);
  
  echo $cont;
}

if($action === "createTempTxt"){
  $data = json_decode($arg);
  
  $name = $data[0];
  $content = $data[1];
  
  $file = fopen("../users/temp/" . $name, "w") or die("Unable to open file!");
  
  fwrite($file, $content);
  
  echo $name . " || " . $content;
  
  fclose($file);
}
if($action === "deleteTempTxt"){
  $name = $arg;
  
  unlink("../users/temp/" . $name);
  
  echo "Deleted.";
}

// <- FILES | USER ->

if($action === "getUser"){
  echo $user;
}

if($action === "saveMains"){
  $file = fopen('../users/' . $user . "/data.json", "w") or die("Unable to open file!");
  
  fwrite($file, $arg);
  
  fclose($file);
  
  echo "Saved.";
}
if($action === "getMains"){
  $file = fopen('../users/' . $user . "/data.json", "r") or die("Unable to open file!");
  
  $cont = fread($file, filesize('../users/' . $user . "/data.json"));
  
  fclose($file);
  
  echo $cont;
}

// <- USER | WEB ->

if($action === "gethtml"){
  $url = $arg;
  
  $html = file_get_contents("$url");
  
  echo $html;
}

// <- WEB | LAYOUTS ->

if($action === "checkOwnLayout"){
  if (file_exists('../users/' . $user . "/layout.txt")) {
    echo 1;
  }
  else
    echo 0;
}
if($action === "getOwnLayout"){
  $file = fopen('../users/' . $user . "/layout.txt", "r") or die("Unable to open file!");
  
  $cont = fread($file, filesize('../users/' . $user . "/layout.txt"));
  
  fclose($file);
  
  echo $cont;
}

// <- LAYOUTS |

?>