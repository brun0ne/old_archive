<?php

 error_reporting( ~E_DEPRECATED & ~E_NOTICE );
 
 define('DBHOST', 'localhost');
 define('DBUSER', 'USER');
 define('DBPASS', 'PASS');
 define('DBNAME', 'DB');
 
 $conn = mysql_connect(DBHOST, DBUSER, DBPASS);
 $dbcon = mysql_select_db(DBNAME);
 
 if ( !$conn ) {
  die("Connection failed: " . mysql_error());
 }
 
 if ( !$dbcon ) {
  die("Database Connection failed: " . mysql_error());
 }