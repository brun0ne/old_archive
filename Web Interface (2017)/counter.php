<!DOCTYPE html>
<html lang="pl">
	<head>
		<meta charset="utf-8" />
    <meta http-equiv="Cache-control" content="no-cache">
		<title>Counter</title>
    
    <script>
      var i = 0;
      
      function refresh(){
        document.getElementById("count").innerHTML = i;
      }
      
      function plus(){
        i++;
        refresh();
      }
      function minus(){
        i--;
        refresh();
      }
    </script>
    
	</head>
  
  <body>
		<button onclick="plus()" type="button">++</button> 
    <button onclick="minus()" type="button">--</button> 
    <br /><br />
    Count: <span id="count"></span>
		
		<script>
			refresh();
		</script>
  </body>
  
</html>