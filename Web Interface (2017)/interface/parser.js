function charReplace(all, object) {
	var result = 0;
	var count = 0;

	for (var b = 0; b < all.length; b++) {
		if (all[b] === "@") {
			var out = all;
			out = out.replaceAt(b, 'l');
			out = out.insertAt(b, "globa");

			all = out;

			count++;

			result = b;

			break;
		}
	}

	if (b < all.length)
		return charReplace(all);
	else
		return all;
}

/*function parse(script, consoleID){
  var commands = new Array();
    
  var actParsCom = 0;
  
  var innerstring = false;

  for(var i = 0; i < script.length; i++){
    if(script[i] === '"'){
      innerstring = !innerstring;
    }
    
    if(script[i] === ";" && innerstring === false){
      actParsCom++;
    }
    else{
      if(commands[actParsCom] == null){
        commands[actParsCom] = "";
      }
      commands[actParsCom] = commands[actParsCom] + script[i];
    }
  }
  
  for(var i = 0; i < commands.length; i++){
    commandParser(commands[i], consoleID);
  }
}

function commandParser(command, consoleID){
  if (printCommands === true && command !== "" && command != null) {
    windows[consoleID].log("&nbsp> " + escapeHtml(command) + "", "#42f4b0");
  }
  
  var status;
  
  var object = "";
  var metode = "";
  var attrs = new Array();
  var attrNum = 0;
  
  var innerstring = false;
  
  if(consoleID == null){
    consoleID = focusedConsoleID;
  }
  
  if(command === "" || command == null){
    return false;
  }
  
  var actPars = "object";
  
  for(var v = 0; v < 100; v++){
    attrs[v] = "";
  }
  
  for(var i = 0; i < command.length; i++){
    if(actPars === "object"){
      if(command[i] != "."){
        object = object + command[i];
      }
      else if(innerstring === false){
        actPars = "metode";
        
        status = "completed";
        
        i++;
      }
    }
    if(actPars === "metode"){
      if(command[i] != "{"){
        metode = metode + command[i];
      }
      if(command[i] === "{" && innerstring === false){
        actPars = "attr";
        i++;
      }
    }
    if(actPars === "attr"){
      if(command[i] === "}" && innerstring === false){
        break;
      }
      
      if(command[i] !== ","){
        attrs[attrNum] = attrs[attrNum] + command[i];
      }
      else{
        attrNum++;
      }
    }
    
    if(command[i] === '"'){
      innerstring = !innerstring;
    }
  }
  
  if(metode == null || metode === "")
    status = "<i>METODE</i> must be defined";
  if(object == null || object === "")
    object = "global";

  // Prevent "Maximum call stack size exceeded" ->

  if(metode === "Submit{}" || metode === "Submit"){
    status = "Funny recursion, huh? No";
  }

  // <-

  // delete "()" and "{}" ->

  metode = metode.replace(/[()]/g, " ");

  // <-
  
  if(status === "completed"){
    attrs[attrNum + 1] = consoleID;

    attrNum += 1;
    
    var attributes = "";

    for(var c = 0; c < attrNum + 1; c++){
      attributes = attributes + attrs[c];
      if(c != attrNum && attrs[c] != null && attrs[c] !== ""){
        attributes = attributes + ",";
      }
    }

    if(attributes == null){
      attributes = "";
    }
    
    // Special objects / metodes ->
    
    object = object.trim();
    
    if(object === "this"){
      object = "windows[" + consoleID + "]";
    }
    
    // <-
    
    var all = object + "." + metode + "(" + attributes + ");"
    
    all = charReplace(all);
    
    try{
      eval(all);
    }
    catch (error){
      if(error.toString() === "SyntaxError: missing ; before statement"){
        error = "SyntaxError: did you use <span style='color: white;'>()</span> instead of <span style='color: white;'>{}</span>?";
      }
      
      windows[consoleID].log("| Error: " + error + " |", "#FF0000"); // #FF0000 == red
      
      return false;
    }
  }
  else{
    windows[consoleID].log("| Error: " + status + " |", "#FF0000"); // #FF0000 == red
  }
}

*/

function parse(script, consoleID) {
	if (consoleID == null) {
		consoleID = focusedConsoleID;
	}
	
	if (script == null){
		return false;
	}

	var all = script;

	if (all === "help")
		all = "help()";
	if (all === "cls" || all === "clear")
		all = "@@.cls()";
	if (all === "history")
		all = "@@.log(@@.history)";

	all = all.replaceAll("@@", "windows[" + consoleID + "]");
	
	if (printCommands === true && all !== "" && all != null) {
		windows[consoleID].log("> " + escapeHTML(all) + "", "#42f4b0");
	}

	try {
		eval(all);
	} catch (error) {
		windows[consoleID].log("| Error: " + error + " |", "#FF0000"); // #FF0000 == red

		return false;
	}
}