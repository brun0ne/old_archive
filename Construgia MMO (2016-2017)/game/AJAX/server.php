<?php

ob_start();
session_start();

include_once '../../dbfiles/dbconnect.php';

$action = $_GET['action'];
$id = $_SESSION['user'];

if($action == "varsLoad"){
  $query = "SELECT LVL, GOLD, EXP, HP, POSX, POSY, LOCATION, ISFIRST, OK FROM users_ingame WHERE ID = $id";
  
  $res = mysql_query($query);
  
  if($res){
    $row = mysql_fetch_array($res);
    echo json_encode(array("id" => $id, "nick" => $_SESSION['userName'], "isfirst" => $row['ISFIRST'], "lvl" => $row['LVL'], "gold" => $row['GOLD'], "exp" => $row['EXP'], "hp" => $row['HP'], "posx" => $row['POSX'], "posy" => $row['POSY'], "Location" => $row['LOCATION'], "ok" => $row['OK']));
  }
  else{
    echo json_encode("error");
  }
}
else if($_POST['action'] == "varsSave"){
  $gold = $_POST['gold'];
  $exp = $_POST['exp'];
  $lvl = $_POST['lvl'];
  $hp = $_POST['hp'];
  $posx = $_POST['posx'];
  $posy = $_POST['posy'];
  $location = $_POST['location'];
  $direction = $_POST['direction'];
  
  $time = date('Y/m/d H:i:s');
  
  $query = "UPDATE users_ingame SET GOLD=$gold, EXP=$exp, LVL=$lvl, HP=$hp, POSX=$posx, POSY=$posy, LOCATION='$location', ISFIRST='0', LTON='$time', Direction='$direction' WHERE id=$id";
  $res = mysql_query($query);
  if($res)
    echo json_encode("Success");
  else
    echo json_encode("Error");
}
else if($_POST['action'] == "players_update"){
  $location = $_POST['Location'];
  
  $sql = "SELECT POSX as POSX, POSY as POSY, ID as ID, NICK as NICK, Direction as Direction, LTON as LTON, LVL as LVL, OK as OK
        FROM   users_ingame
        WHERE  Location = '$location'";
  
  $res = mysql_query($sql);
  
  echo '[';
  
  $numRows = mysql_num_rows($res);
  $i = 0;
  
  while ($row = mysql_fetch_assoc($res)) {
    $newID = $row["ID"];
    
    echo '{"ID":"' . $newID . '", ';
    echo ' "NICK":"' . $row["NICK"] . '", ';
    
    $lton = new DateTime($row["LTON"]);
    $today = new DateTime(date("Y-m-d H:i:s"));
    $today->modify("-3 seconds");
    if($lton > $today){
      echo ' "IS":"1", ';
    }
    else{
      echo ' "IS":"0", ';
    }
    
    echo ' "Direction":"' . $row["Direction"] . '", ';
    echo ' "LVL":"' . $row["LVL"] . '", ';
    echo ' "OK":"' . $row["OK"] . '", ';
    echo ' "POSX":"' . $row["POSX"] . '", ';
    echo ' "POSY":"' . $row["POSY"] . '"}';
    
    if($i < $numRows - 1)
      echo ", ";
    
    $i++;
  }
  
  echo ']';
}
else if($action == "getRang"){
  $query = "SELECT specialRang FROM users_ingame WHERE ID = $id";
  
  $res = mysql_query($query);
  
  $row = mysql_fetch_array($res);
  
  if($query){
    echo json_encode($row[0]);
  }
  else{
    echo "Error.";
  }
}
else if($_POST["action"] == "setOK"){
  if($_POST["rang"] == "admin"){
    $new = $_POST["newOK"];
    $id = $_POST["id"];
    
    if(is_numeric($id))
      ;
    else
      exit();
    
    if($new == "ok")
      $new_ = "ok";
    else if($new == "notOK")
      $new_ = "notOK";
    else
      exit();
    
    $query = "UPDATE users_ingame SET OK='$new_' WHERE id=$id";
    
    $res = mysql_query($query);
    
    if($res){
      if($new_ == "notOK")
        echo "Kicked " . $id . ".";
      else if($new_ == "ok")
        echo "UnKicked " . $id . "." ;
    }
  }
}
else if($_POST["action"] == "eqSave"){
  $nick = $_POST["nick"];
  $obj = $_POST["JSONarray"];
  
  if($nick == $_SESSION["userName"]){
    $file = fopen("../players/" . $nick . "_eq.json", "w") or die("Unable to open file!");
    
    fwrite($file, $obj);
    
    echo "Saved to players/" . $nick . "_eq.json";
    
    fclose($file);
  }
  else{
    header("Location: ../index.php?cMsg=Session%20expired.%20You%20have%20to%20log%20in%20again.");
    exit();
  }
}
else if($action == "eqLoad"){
  $nick = $_SESSION["userName"];
  
  if($nick != null){
    if(file_exists("../players/" . $nick . "_eq.json")){
      $file = fopen("../players/" . $nick . "_eq.json", "r") or die("Unable to open file!");
      
      echo fread($file, filesize("../players/" . $nick . "_eq.json"));
      
      fclose($file);
    }
    else{
      echo "EQ doesn't exist!";
    }
  }
  else{
    header("Location: ../index.php?cMsg=Session%20expired.%20You%20have%20to%20log%20in%20again.");
    exit();
  }
}
else if($_POST["action"] == "locationChange"){
  $name = $_POST["name"];
  $id = $_SESSION["user"];
  
  if($id != null){
    $query = "UPDATE users_ingame SET LOCATION='$name' WHERE id=$id";
    
    $res = mysql_query($query);
    
    if($res)
      echo "Done.";
    else
      die("Error.");
  }
  else{
    header("Location: ../index.php?cMsg=Session%20expired.%20You%20have%20to%20log%20in%20again.");
    exit();
  }
}

?>