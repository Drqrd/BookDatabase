<?php
	include "dbh.php";
?>
<!doctype html>
<html lang="en">
<head>
	<meta charset="utf-8">
	<title>Book DB</title>
	<style>
		<?php 
			include "styles.css";	
		?>		
	</style>
	<script type="text/javascript" src="func.js"></script>
	<script type="text/javascript" src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
</head>
<body onload="init()">
	<div id="background">
		<div id="navigation_bar">
			<span id="navigation_left">
				<h1 id="navigation_title">Book Database</h1> 
			</span>
			<span id="navigation_right"> 
				<a class="navigation_icon" style="border-radius: 32px;" href="https://github.com/Drqrd" target="_blank">
					<img class="navigation_icon" style="border-radius: 32px;" src="GitHub-Icon-512px.png" alt="github">
				</a>
				<a class="navigation_icon" style="border-radius: 8px;" href="https://www.linkedin.com/in/jmderrico/" target="_blank">
					<img class="navigation_icon" style="border-radius: 8px;" src="Linked-In-Icon-512px.png" alt="linkedin">
				</a>
			</span>
		</div>
		<div id="body_left">
			<div id="search_bar_wrapper">
				<form action="index.php" method="post" id="search_bar">
					<input type="text" name="q" id="search" placeholder="Search by Name, Author, or Date...">
					</input>
					<input type="submit" id="search_submit" value="">
					</input>
				</form>
			</div>
			<div id="content_sorting_wrapper">
				<span class="content_sorting" id="s_1" onClick="sortAsc(this.id)" style="border-top-left-radius: 8px; border-bottom-left-radius: 8px; margin-left: 0;">
					<h6 class="button_text">Title</h6>
					<img class="sorting_icon" src="data:image/gif;base64,R0lGODlhAQABAIAAAP///wAAACH5BAEAAAAALAAAAAABAAEAAAICRAEAOw==">
				</span>
				<span class="content_sorting" id="s_2" onClick="sortAsc(this.id)">
					<h6 class="button_text">Author</h6>
					<img class="sorting_icon" src="data:image/gif;base64,R0lGODlhAQABAIAAAP///wAAACH5BAEAAAAALAAAAAABAAEAAAICRAEAOw==">
				</span>
				<span class="content_sorting" id="s_3" onClick="sortAsc(this.id)" style="border-top-right-radius: 8px; border-bottom-right-radius: 8px; margin-right: 0;">
					<h6 class="button_text">Published</h6>
					<img class="sorting_icon" src="data:image/gif;base64,R0lGODlhAQABAIAAAP///wAAACH5BAEAAAAALAAAAAABAAEAAAICRAEAOw==">
				</span>
			</div>
			<div id="search_results_wrapper" name="container">
				<?php
					if (!empty($_POST['q']))
					{
						$sortBy = $_POST['button'];
						echo $sortBy;
						$col1 = "name";
						$col2 = "author";
						$col3 = "date_published";

						$query = $_POST['q'];

						$sql = "SELECT * FROM ".$tablename." WHERE ".$col1." LIKE '%".$query."%' 
																OR ".$col2." LIKE '%".$query."%'
																OR ".$col3." LIKE '%".$query."%'
																ORDER BY ".$col3." DESC";
						if ($result = mysqli_query($conn, $sql))
						{
								while($row = mysqli_fetch_array($result))
								{
									echo "<div class=\"search_result\">";
										echo "<span class=\"result_1\">".$row['name']."</span>";
										echo "<span class=\"result_2\">".$row['author']."</span>";
										echo "<span class=\"result_3\">".$row['date_published']."</span>";
									echo "</div>";
								}
							mysqli_free_result($result);
						}
						else
						{
							echo "\nNo Results Found...";
						}
					}
				?>
			</div>
		</div>
		<div id="body_right">
			
		</div>
	</div>
</body>
</html>