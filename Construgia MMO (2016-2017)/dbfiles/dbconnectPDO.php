<?php
$servername = "localhost";
$username = "X";
$password = "X";

try {
    $conn = new PDO("mysql:host=$servername;dbname=construgia_c0_pl", $username, $password);
    // set the PDO error mode to exception
    $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
    }
catch(PDOException $e)
    {
    echo "Connection failed: " . $e->getMessage();
    }
?>