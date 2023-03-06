<?php
// get the q parameter from URL
$what = $_REQUEST["what"];

$page = "";

// lookup all hints from array if $q is different from "" 
if ($what !== "") {
  if($what == "News"){
    include 'sites/news.php';
  }
  else if($what == "About"){
    include 'sites/about.php';
  }
  else if($what == "Statistics"){
    include 'sites/statistics.php';
  }
  else if($what == "FAQ"){
    include 'sites/faq.php';
  }
  else if($what == "Screenshots"){
    include 'sites/screenshots.php';
  }
  else if($what == "Creators"){
    include 'sites/creators.php';
  }
}

?>