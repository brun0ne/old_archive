<!DOCTYPE HTML>

<html lang="pl">
  <?php
  
  $page = $_GET['page'];
  
  if($page == null || $page == "")
    $page = 'main';
  
  ?>
  
  <head>
    <title>EDDIT.PL</title>
    
    <meta charset="UTF-8">
  
    <meta name="description" content="-">
    <meta name="keywords" content="edit, videos, edditing, eddit, youtube">
    <meta name="author" content="Brunon Blok">
  
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js"></script>
    <link rel="stylesheet" href="https://ajax.googleapis.com/ajax/libs/jqueryui/1.12.1/themes/smoothness/jquery-ui.css">
    <script src="https://ajax.googleapis.com/ajax/libs/jqueryui/1.12.1/jquery-ui.min.js"></script>
    
    <link rel="stylesheet" href="styles.css" />
    <link href="https://fonts.googleapis.com/css?family=Ubuntu" rel="stylesheet"> 
    <link href="https://fonts.googleapis.com/css?family=Montserrat:100" rel="stylesheet"> 
  </head>
  
  <body>
    <div id="sidebar">
      <center>
        <h1 id="title" style="font-size: 400%; width: 100%; height: 100px; color: #e8e8e8; position: absolute; top: 2%; font-family: Intro_Light;">
          <span style="color: #3be560; vertical-align: middle;">e d d</span><span style="vertical-align: middle;">&nbspi t</span>
        </h1>
        <h4 style="font-family: Consolas, Consolas; margin-top: -25px;">
          #todo
        </h4>
      </center>
      <a href="?page=main"><div class="sd_button" style="margin-top: 60%;">Strona główna</div></a>
      <a href="?page=howitworks"><div class="sd_button">Jak to działa?</div></a>
      <a href="?page=news"><div class="sd_button">Aktualności</div></a>
      <a href="?page=news"><div class="sd_button">Porady</div></a>
      <a href="?page=montage"><div class="sd_button">Zmontowane przez nas</div></a>
      <a href="?page=editors"><div class="sd_button">Montażyści</div></a>
    </div>
    <div class="page">
      <?php
      
      include "pages/" . $page . ".php";
      
      ?>
    </div>
  </body>
</html>