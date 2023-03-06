<?php
  $target_dir = "../graphics/";
  $target_file = $target_dir . basename($_FILES["fileToUpload"]["name"]);
  $tgf = basename($_FILES["fileToUpload"]["name"]);
  $uploadOk = 1;
  $imageFileType = pathinfo($target_file,PATHINFO_EXTENSION);
  
  if(isset($_POST["submit"])) {
    $check = getimagesize($_FILES["fileToUpload"]["tmp_name"]);
    if($check !== false) {
        echo "File is an image - " . $check["mime"] . ".<br />";
        $uploadOk = 1;
    } else {
        echo "File is not an image.<br />";
        $uploadOk = 0;
    }
  }
  
  if (file_exists($target_file)) {
    echo "File already exists!<br />";
    exit();
  }
  
  if($imageFileType != "jpg" && $imageFileType != "png" && $imageFileType != "jpeg"
  && $imageFileType != "gif" ) {
    echo "Sorry, only JPG, JPEG, PNG & GIF files are allowed.<br />";
    $uploadOk = 0;
  }
  
  if ($uploadOk == 0) {
    echo "Sorry, your file was not uploaded.<br />";
  } else {
  if (move_uploaded_file($_FILES["fileToUpload"]["tmp_name"], $target_file)) {
      echo "The file ". basename( $_FILES["fileToUpload"]["name"]). " has been uploaded.";
  } else {
      echo "Sorry, there was an error uploading your file.<br />";
  }

  $key = '</objs>';
  $newline = "<obj><img>" . $tgf . "</img></obj>";

  $file = "files/objects.xml";
  $newfile = "filetemp.xml";
  copy($file, $newfile) or exit("failed to copy $file");
  
  $fc = fopen ($file, "r");
  while (!feof ($fc))
  {
    $buffer = fgets($fc, 4096);
    $lines[] = $buffer;
  }

  fclose ($fc);

  $f = fopen($newfile, "w") or die("couldn't open $file");

  foreach($lines as $line)
  {
    if (strstr($line, $key)){
        fwrite($f, $newline . "\n");
    } 
    fwrite($f, $line);
  }

  fclose($f);

  copy($newfile, $file) or exit("failed to copy $newfile");
}

echo "<br /><a href='editor.php'>Go back</a>";
?>