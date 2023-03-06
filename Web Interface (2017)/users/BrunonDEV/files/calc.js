@@.log("EPIC CALCULATOR", "magenta");

@@.log("First number:");
@@.input(function (x){
	@@.log(x);
	if(isNaN(x)){
		@@.log("Not a number", "red");
		return false; 
	}
  	@@.log("Second number:")
	@@.input(function (y){
   	@@.log(y);
     	if(isNaN(y)){
			@@.log("Not a number", "red");
			return false; 
		}
      @@.log(x + " + " + y + " = " + (parseInt(x)+parseInt(y)), "yellow");
   });
});