@@.createCustomWindow("App 1");
@@.app.resize(600, 300);
@@.app.toggleResize(false);
@@.app.align("center");

@@.app.echo = false;

@@.app.setContent("<h3>Blah blah</h3>");

@@.log("Type to set content...");

function loop(){
	@@.input(function (x){
		@@.app.setContent("<h3>" + x + "<h3>");
   	@@.log("Set!");
   	loop();
	});
}
loop();