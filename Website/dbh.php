<?php
	$servername = "localhost";
	$username = "root";
	$password = "";
	$dbname = "books_db";
	$tablename = "books_info";

	$conn = mysqli_connect($servername, $username, $password, $dbname);

	if ($conn === false)
	{
		echo("Connection to MySql Database Failed...");
	}
?>