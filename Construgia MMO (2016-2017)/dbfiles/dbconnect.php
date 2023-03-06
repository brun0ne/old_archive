<?php

 // avoid mysql_connect() deprecation error.
 error_reporting( ~E_DEPRECATED & ~E_NOTICE );
 
 define('DBHOST', 'localhost');
 define('DBUSER', 'X');
 define('DBPASS', 'X');
 define('DBNAME', 'construgia_c0_pl');
 
 $conn = mysql_connect(DBHOST, DBUSER, DBPASS);
 $dbcon = mysql_select_db(DBNAME);
 
 if ( !$conn ) {
  die("Connection failed: " . mysql_error());
 }
 
 if ( !$dbcon ) {
  die("Database Connection failed: " . mysql_error());
 }