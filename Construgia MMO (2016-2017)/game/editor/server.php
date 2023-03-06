<?php

session_start();

$action = $_GET["action"];

if($action == "readObjectsList"){
  $xml = simplexml_load_file("files/objects.xml") or die("Error: Cannot create object / read file.");
  
  $xmlFILE = fopen("files/objects.xml", "r") or die("Unable to open file!");
  $xmlFILETEXT = fread($xmlFILE, filesize("files/objects.xml"));
  fclose($xmlFILE);
  
  $res;
  
  $dom = new DOMDocument;
  $dom->loadXml($xmlFILETEXT);
  $number = $dom->getElementsByTagName('obj')->length;
  
  $i = 0;
  
  echo "[";
  
  foreach($xml->children() as $objs) { 
    if($i < $number){
      echo '{';
      echo '"img":"' . $objs->img . '"'; 
      echo "}";
    }
    
    if($i < $number - 1)
      echo ", ";
    $i++;
  }
  
  echo "]";
}
else if($_POST["action"] == "mapSave"){
  $mapData = $_POST["JSONarray"];
  $mapName = $_POST["mapName"];
  
  $file = fopen("files/locations/" . $mapName . ".json", "w") or die("Unable to open file!");
  
  fwrite($file, $mapData);
  
  echo "Saved to " . $mapName . ".json";
  
  fclose($file);
}
else if($action == "checkMapExist"){
  $name = $_GET["name"];
  
  if(file_exists("files/locations/" . $name . ".json")){
    echo "Exist";
  }
  else{
    echo "Not";
  }
}
else if($action == "mapLoad"){
  $name = $_GET["name"];
  
  if(file_exists("files/locations/" . $name . ".json")){
    $file = fopen("files/locations/" . $name . ".json", "r") or die("Unable to open file!");

    echo fread($file,filesize("files/locations/" . $name . ".json"));

    fclose($file);
  }
  else{
    echo "Map doesn't exist!";
  }
}
else if($_POST["action"] == "mapDelete"){
  $name = $_POST["name"];
  
  if(file_exists("files/locations/" . $name . ".json")){
    if($_SESSION["userE"] == "BrunonDEV" || $_SESSION["userE"] == "solo14"){
      unlink("files/locations/" . $name . ".json");
      
      echo "Done.";
    }
    else{
      echo "Permissions error!";
    }
  }
  else{
    echo "Map doesn't exist!";
  }
}
else if($action == "getMaps"){
  foreach (new DirectoryIterator("files/locations/") as $file) {
    if ($file->isFile()) {
      $path_parts = pathinfo($file);
      
      $help = '"';
      
      print "<li><a href='javascript:AJAX_mapLoad(`" . $path_parts["filename"] . "`); toggleMapListWindow();'>" . $path_parts["filename"] . "</a></li><br />";
    }
  }
}

?>