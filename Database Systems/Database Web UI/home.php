<html>
<script type="text/javascript" href="javas.js"></script>
<script type="text/javascript" src="jquery-latest.js"></script> 
<script src="http://ajax.googleapis.com/ajax/libs/jquery/1.11.0/jquery.min.js"></script>
<script src="jquery.bpopup.min.js"></script>
<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.4/css/bootstrap.min.css">
<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.4/css/bootstrap-theme.min.css">
<script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.4/js/bootstrap.min.js"></script>	

<head>
<title>
Assignment 3
</title>
</head>
<h1 style='color:#00688B;'> Please select the relation </h1>


<form action="home.php" method="get" style='width: 300px;margin: 0 auto;'>
<?php
// Dynamically Creating the Drop Down menu by finding the relations in the selected database

include('config.php'); // Contains the credentials for the postgres database

$conn = pg_connect("host=$host dbname=$dbname user=$user password=$password")
    or die("Can't connect to database".pg_last_error());

$result = pg_query($conn, "SELECT table_name FROM information_schema.tables where table_schema='public' ") or die ("Error  = ".pg_last_error());
echo "<SELECT name='table' style='height:40px;width:120px;font-size:20px;margin-right:50px;'>";
while ($row = pg_fetch_row($result)) {
	echo "<option value=$row[0]>".$row[0]."</option>";
}

?>
<input type="submit" value="Submit" class='btn btn-success'>

</form>


<body>
<?php
if (isset($_GET['operation']))
{

	// Processing the ADD TUPLE Request
	if ($_GET['operation']==="Add")
	{	
		$s="";
		$value="";
		$table=$_GET['table'];
		$result = pg_query($conn, "SELECT column_name FROM information_schema.columns where table_name='".$_GET['table']."' order by ordinal_position") or die ("Error  = ".pg_last_error());
		$count=0;
		$attr=array();
		while ($row = pg_fetch_row($result)) {
			$attr[$count]=$row[0];
			if ($s=="")
			{
			$s=$row[0];
			$value="'".$_GET[$row[0]]."'";
			}
			else
			{
			$s=$s.",".$row[0];
			$value=$value.","."'".$_GET[$row[0]]."'";			
			}
			$count+=1;
		}
		// Executing the Framed query using the submitted values
		$result = pg_query($conn, "INSERT into $table($s) VALUES($value)") or die ("Error  = ".pg_last_error());
	}
	
	// Processing the DELETE TUPLE Request
	if ($_GET['operation']==="Delete")
	{	
		$s="";
		$table=$_GET['table'];
		$result = pg_query($conn, "SELECT column_name FROM information_schema.columns where table_name='".$_GET['table']."'  order by ordinal_position") or die ("Error  = ".pg_last_error());
		$count=0;
		$attr=array();
		while ($row = pg_fetch_row($result)) {
			$attr[$count]=$row[0];
			if ($s=="")
			{
			$s=$row[0]."="."'".$_GET[$row[0]]."'";
			}
			else
			{
			$s=$s." and ".$row[0]."="."'".$_GET[$row[0]]."'";			
			}
			$count+=1;
		}
		// Executing the Framed query using the submitted values
		$result = pg_query($conn, "Delete from $table where $s") or die ("Error  = ".pg_last_error());
	}
	
	// Processing the MODIFY TUPLE Request
	if ($_GET['operation']==="Modify")
	{	
		$s="";
		$u="";
		$table=$_GET['table'];
		$result = pg_query($conn, "SELECT column_name FROM information_schema.columns where table_name='".$_GET['table']."'  order by ordinal_position") or die ("Error  = ".pg_last_error());
		$count=0;
		$attr=array();
		while ($row = pg_fetch_row($result)) {
			$attr[$count]=$row[0];
			if ($s=="")
			{
			$s=$row[0]."="."'".$_GET[$row[0]]."'";
			$u=$row[0]."="."'".$_GET['new'.$row[0]]."'";
			}
			else
			{
			$s=$s." and ".$row[0]."="."'".$_GET[$row[0]]."'";	
			$u=$u." , ".$row[0]."="."'".$_GET['new'.$row[0]]."'";		
			}
			$count+=1;
		}
		// Executing the Framed query using the submitted values
		$result = pg_query($conn, "update $table set $u where $s") or die ("Error  = ".pg_last_error());
	}
	
}

// Dynamically Creating and displaying the Relation
if (isset($_GET['table']))
{
	$table=$_GET['table'];
	// Getting all the Attribute Names
	$result = pg_query($conn, "SELECT column_name FROM information_schema.columns where table_name='".$_GET['table']."'  order by ordinal_position") or die ("Error  = ".pg_last_error());
	echo "<h1 align='center' style='color:#00688B;'>".$table."</h1><table class='table table-bordered'><tr>";
	$count=0;
	$attr=array();
	while ($row = pg_fetch_row($result)) {
		$attr[$count]=$row[0];
		echo "<th>".$row[0]."</th>";
		$count+=1;
	}
	echo "<th>Modify Tuple</th>";
	echo "<th>Delete Tuple</th>";
	echo "</tr>";
	
	// Fetching the Tuples and adding to table
	$result = pg_query($conn, "SELECT * FROM ".$_GET['table']."") or die ("Error  = ".pg_last_error());
	$num=0;
	while ($row = pg_fetch_row($result)) {
		
		$x=0;
		echo "<tr id=$num>";
		while ($x<$count)
		{
			echo "<td>".$row[$x]."</td>";
			$x+=1;
		}
		echo "<td>"."<button class='btn btn-primary' onclick=modify($num)>Modify</button>"."</td>";
		echo "<td>"."<button class='btn btn-danger' onclick=del($num)>Delete</button>"."</td>";
		echo "</tr>";
		$num+=1;
	}

	//Note :- Following Forms are Dynamically Created such that the code works for all relations(generic)
	
	// Form to Add a Tuple(Initially Hidden) 
	echo "<tr style='visibility:hidden'id='addrow'> ";
	echo "<form action='home.php' method='get' id='add'>";
	$x=0;
	while ($x<$count)
	{
		echo "<td>"."<input id=\"".$attr[$x]."\" name=$attr[$x]></td>";
		$x+=1;
	}
	echo "<td>"."<input name='table' value='$table' hidden>"."</td>";
	echo "<td>"."<input type='submit' value='Add' name='operation' class='btn btn-success'>"."</td>";
	echo "</tr>";
	echo "</form>";

	// Form to Modify a Tuple(Initially display set to none)
	echo "<div id='modrow' style='display:none; background-color:#E5E5E5;height:auto;width:auto;padding:20px;'> ";
	echo "<form action='home.php' method='get' id='modify'>";
	$x=0;
	while ($x<$count)
	{
		echo "<input id=\"".$attr[$x]."\" name=$attr[$x] hidden>";
		echo "<input id=\"".'new'.$attr[$x]."\" name=\"".'new'.$attr[$x]."\">";
		$x+=1;
	}
	echo "<input name='table' value='$table' hidden>";
	echo "<input type='submit' class='btn btn-primary' value='Modify' name='operation'>";
	echo "</div>";
	echo "</form>";	
	
	// Form to Delete a Tuple(Hidden)
	echo "<tr style='visibility:hidden'id='addrow'> ";
	echo "<form action='home.php' method='get' id='delete'>";	
	$x=0;
	while ($x<$count)
	{
		echo "<td>"."<input id=\"".$attr[$x]."\" name=$attr[$x]></td>";
		$x+=1;
	}
	echo "<td>"."<input value='Delete' name='operation'>"."</td>";
	echo "<td>"."<input name='table' value='$table' hidden>"."</td>";
	echo "</tr>";
	echo "</form>";
	echo "</table>";
	
	// Add Tuple Button
	echo "<button onclick='f()' class='btn btn-success' style='float:right;  margin-top:-50px;'>Add Tuple</button>";

	
	
}

?>

</body>
<script>

	// function to show the ADD_TUPLE form
	function f()
	{
		document.getElementById('addrow').style.visibility='visible';
	}
	
	// Function to process the delete request by fetching the values from the clicked button's row
	function del(a)
	{
		row=document.getElementById(a);
		rowarray=row.getElementsByTagName('td');
		formdel=document.getElementById('delete');
		ele=formdel.elements;
		for (x=0;x<rowarray.length-2;x++)
		{
			ele[x].value=rowarray[x].innerText;
		}
		for (x=0;x<ele.length;x++)
		{
			console.log(ele[x].value);
		}
		formdel.submit();
	}
	
	// Initially Hide the pop div
	$(document).ready(function(){
		$("#modrow").hide();
	});	
	
	// Function to process the modify request by fetching the values from the clicked button's row
	// to prefill the popped up form
	function modify(a){
		$('#modrow').bPopup();

		row=document.getElementById(a);
		rowarray=row.getElementsByTagName('td');


		row=document.getElementById(a);
		rowarray=row.getElementsByTagName('td');
		formdel=document.getElementById('modify');

		ele=formdel.elements;
		y=0;
		for (x=0;x<rowarray.length-2;x++)
		{
			ele[y].value=rowarray[x].innerText;
			ele[y+1].value=rowarray[x].innerText;	
			y+=2;
		}
		for (x=0;x<ele.length;x++)
		{
			console.log(ele[x].value);
		}


	}

	</script>
</html>
