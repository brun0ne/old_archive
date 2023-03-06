class Console {
	constructor(x) {
		this.w = 600;
		this.h = 300;
		this.x = Math.floor((Math.random() * ($(window).width()) - this.w) + 0);
		this.y = Math.floor((Math.random() * ($(window).height()) - this.h) + 0);

		if (this.x < 0)
			this.x = 100;
		if (this.y < 0)
			this.y = 100;

		this.id = incrementID;
		this.cID = increment_C_ID;
		this.type = "Console";

		this.is = true;

		this.content = "";

		this.app = null;

		this.hidden = false;

		this.reload_ = false;

		this.loaded = false;

		this.not_save = false;
		
		this.input_callback = null; // function to which next submit is passed

		this.iteration = 0;
		this.looping = false;
		this.icount = 0;

		this.history = []; // command history
	}

	Load() {
		if (this.is === true && this.hidden !== true) {
			if (this.loaded === true) {
				$("#console_" + this.id).remove();
			}

			this.onclick = ``;

			this.onmouseover = `$(this).draggable({ stop: function(){
        var it = windows[` + this.number + `];

        windowCollider(it, this);
      } });
        $(this).resizable({
          alsoResize: "#console_` + this.id + `_input_command",
          stop: function(){ var it = windows[` + this.number + `]; windowCollider(it, this); }
        });
      `;

			this.onmouseup = ``;

			this.min_button = `<div class="clickable" title="Minimize" style="position: absolute; right: 25px; top: 2%;"><span onclick="windows[` + this.number + `].hide()" class="glyphicon glyphicon-minus" aria-hidden="true"></span></div>`;

			this.off_button = `<div class="clickable" style="position: absolute; right: 5px; top: 1%;"><span onclick="windows[` + this.number + `].close()" class="glyphicon glyphicon-remove" aria-hidden="true"></span></div>`;

			this.content_wrapper = `<div id="console_content_` + this.id + `" class="content console_content" onclick="event.stopPropagation(); ` + this.onclick + `" style="position: absolute; top: 15%; height: 75%; width: 95%; overflow: auto;">` + this.content + `</div>`;

			this.command_input = `<div style='position: absolute; bottom: 1%;'>
        <form id="form_command_console_` + this.id + `" name="form_console" action="" onsubmit="return windows[` + this.number + `].Submit();" method="post">
          <input onkeydown="windows[` + this.number + `]._keydown(event)" placeholder="Enter command..." id="console_` + this.id + `_input_command" onclick='event.stopPropagation(); focusedConsoleID = ` + this.number + `;' style="color: inherit; width: ` + (this.w - 40) + `px; min-height: 25px; max-height: 25px; min-width: 160px;" name="text" type="text" />
        </form>
      </div>`;

			this.inner = "<h4>Console (" + this.cID + ")</h4>" + this.off_button + this.min_button + this.content_wrapper + this.command_input;

			this.newdiv = "<div onmouseup='" + this.onmouseup + "' onmouseover='" + this.onmouseover + "' id='console_" + this.id + "' class='window consoleLayout' onclick='" + this.onclick + "' style='position: absolute; width: " + this.w + "px; min-height: 200px; min-width: 200px; height: " + this.h + "px; left: " + this.x + "px; top: " + this.y + "px;'><div style='margin: 2%;'>" + this.inner + "</div></div>"

			document.getElementById("windows").innerHTML = document.getElementById("windows").innerHTML + this.newdiv;

			var target = document.getElementById("last_console_" + this.id);

			if (target != null)
				target.parentNode.scrollTop = target.offsetTop;

			this.loaded = true;
		}
	}

	log(what, color) {
		if (typeof(what) === "object") {
			this.printObject(what);
			return false;
		}

		if (color == null)
			color = "white";

		$(".last_").each(function() {
			$(this).remove();
		});

		this.content = $("#console_content_" + this.id).html();

		this.content = this.content + "<span style='color: " + color + "'>" + what + "</span><span class='last_' id='last_console_" + this.id + "'></span><br />";

		$("#console_content_" + this.id).html(this.content);

		var it = this;

		document.getElementById("last_console_" + it.id).scrollIntoView();

		saveWindows();
	}

	createCustomWindow(name) {
		newWindow("app");

		windows[windows.length - 1].lang = name;

		windows[windows.length - 1].console = this;

		this.app = windows[windows.length - 1];

		windows[windows.length - 1].x = this.x + 100;
		windows[windows.length - 1].y = this.y + 50;

		// when everything is done - reload

		windows[windows.length - 1].Load();

		this.log("Custom window has been created.", "#62ff07"); // #62ff07 == light green

		return windows[windows.length - 1];
	}

	Submit() {
		var x = document.getElementById("console_" + this.id + "_input_command").value;
		
		if(this.input_callback != null){
			var callback = this.input_callback.clone();
			this.input_callback = null;
			
			try{
				callback(x);
				
				document.forms["form_command_console_" + this.id].reset();
				$("#console_" + this.id + "_input_command").focus(); // refocus input
				return false;
			}
			catch(e){
				console.log("Error in input() callback");
				console.error(e);
			}
		}
		
		if (x != null && x != "")
			this.history.push(x);
		if (this.history.length > 50) // store last 50 commands
			this.history.pop();

		var first = x.substring(0, 1);

		if (first === "/") {
			this.log(x, "#f0ff26"); // comments | yellow
		} else if (first === ">") { // file eval
			var filename = x;

			filename = filename.replace('>', ''); // delete :

			var second = filename.substring(0, 1);

			if (second === "@") { // variable eval
				var varname = filename;

				varname = varname.replace('@', '');

				if (strEvalShow_ === true) {
					this.log("Command called from <i style='color: #42f4e2;'>GLOBAL</i> variable <span style='color: white;'>" + varname + "</span>. <a href='#' class='hoverer' onclick='strEvalShow(false)'>[Hide next time]</a>", "#62ff07"); // #62ff07 == light green
				}

				if (global[varname] == null) {
					this.log("<i style='color: #42f4e2;'>GLOBAL</i> variable nammed <span style='color: white;'>" + varname + "</span> doesn't exist.", "red");
				} else {
					parse(global[varname].toString());
				}
			} else {
				if (strEvalShow_ === true) {
					this.log("Command called from <span style='color: white;'>" + filename + "</span>. <a href='#' class='hoverer' onclick='strEvalShow(false)'>[Hide next time]</a>", "#62ff07"); // #62ff07 == light green
				}

				storage.eval(filename, this.number);
			}
		} else {
			parse(x, this.number);
		}

		document.forms["form_command_console_" + this.id].reset();

		return false;
	}

	_keydown(e) {
		if (e.keyCode == '38') { // up arrow -- go back in command history		
			if (this.history[this.history.length - 1] != null) {
				var set = false;
				for(var i = 0; i < this.history.length; i++){
					if(this.history[i] == $(`#console_` + this.id + `_input_command`).val()){
						if(this.history[i-1] != null)
							$(`#console_` + this.id + `_input_command`).val(this.history[i-1]); // command before visible
						set = true;
					}
				}
				if(set === false){
					$(`#console_` + this.id + `_input_command`).val(this.history[this.history.length - 1]); // last command
				}
			}
		}
	}

	cls() {
		this.content = "";

		$("#console_content_" + this.id).html("");

		this.log("Console cleared successfully.", "#62ff07"); // #62ff07 == light green

		this.Load();
		$("#console_" + this.id + "_input_command").focus(); // refocus input
	}
	
	input(callback){ // like std::cin
		this.input_callback = callback.clone();
	}

	close() {
		this.is = false;

		this.w = 0;
		this.h = 0;
		this.x = 0;
		this.y = 0;

		$("#console_" + this.id).hide("fade", {}, 500, function() {
			this.remove()
		});

		if (this.hidden)
			$("#hidden_" + this.id).remove();

		if (this.app != null)
			this.app.console = null;

		if (this.app != null)
			this.app.close();

		saveWindows();
	}

	hide() {
		var it = this;

		setTimeout(function() {
			it.hidden = true;

			if ($("#hidden_" + it.id).length) {
				$("#hidden_" + it.id).remove();
			}

			if ($("#console_" + it.id).length)
				$("#console_" + it.id).hide("drop", {
					direction: "right"
				}, 500);

			refreshHiddenWindows();

			saveWindows();
		}, 100);
	}

	show() {
		this.hidden = false;

		if ($("#console_" + this.id).length)
			$("#console_" + this.id).fadeIn("medium");
		else
			this.Load();

		$("#hidden_" + this.id).fadeOut(1000).remove();

		saveWindows();
	}

	loop(command, fq, iteration) {
		if(command == null || fq == null || iteration == null){
			this.log("Usage: loop(command, frequency, count)", "yellow");
			return false;
		}
		
		if (this.looping === true) {
			this.log("This console has already loop in progress. | You can stop it using <b><i>this.stop()</i></b>.")
		}

		var number = this.number;
		this.iteration = iteration;
		this.icount = 0;

		if (fq == null) {
			fq = 250;
		}
		if (this.iteration == null) {
			this.iteration = Number.MAX_SAFE_INTEGER;
		}

		this.looping = true;

		this.log("Loop started. | Frequency: <span style='color: white'>" + fq + "</span>, planned iterations: <span style='color: white'>" + this.iteration + "</span>", "#62ff07"); // #62ff07 == light green

		this._loopIteration(command, fq);
	}

	_loopIteration(command, fq) {
		parse(command, this.id);

		this.icount++;

		this.iteration--;
		var it = this;

		if (this.iteration > 0 && this.looping === true) {
			setTimeout(function() {
				it._loopIteration(command, fq)
			}, fq);
		} else {
			if (this.looping === true) {
				this.log("Loop completed. <span style='color: white'>" + this.icount + "</span> iterations done.", "#62ff07"); // #62ff07 == light green
			}

			this.looping = false;

			return false;
		}
	}

	stop(what) {
		if (true) { // ...
			// ...
		} else { // default : loop
			var icount = this.icount;

			this.looping = false;
			this.iteration = 0;

			var it = this;

			setTimeout(function() {
				it.log("Loop stopped by user. <span style='color: white'>" + icount + "</span> iterations done.", "#62ff07"); // #62ff07 == light green
			}, 500);
		}
	}

	state(consoleID) {
		if (consoleID == null)
			consoleID = focusedConsoleID;

		var win = windows[consoleID];

		var cont = "no";
		if (cont != null && cont !== "")
			cont = "yes";

		win.log("CONSOLE STATE:", "#62ff07"); // #62ff07 == light green
		win.log("ID: <span style='color: #42f1f4'>" + this.id + "</span>", "yellow");
		win.log("Looping: <span style='color: #42f1f4'>" + this.looping + "</span>", "yellow");
		win.log("Has content: <span style='color: #42f1f4'>" + cont + "</span>", "yellow");
	}

	info(obj) {
		if (obj == null)
			return false;

		var clone = obj;

		var p = [];
		for (; obj != null; obj = Object.getPrototypeOf(obj)) {
			var op = Object.getOwnPropertyNames(obj);
			for (var i = 0; i < op.length; i++)
				if (p.indexOf(op[i]) == -1)
					p.push(op[i]);
		}

		// p is a list of all properties of obj

		obj = clone;

		var functions = [];
		var objects = [];
		var vars = [];

		for (var j = 0; j < p.length; j++) {
			if (typeof(obj[p[j]]) == "function") {
				functions.push(p[j]);
			} else if (typeof(obj[p[j]]) == "object") {
				objects.push(p[j]);
			} else {
				vars.push(p[j]);
			}
		}

		var functions_text = "";

		for (var j = 0; j < functions.length; j++) {
			functions_text += functions[j];
			if (j != functions.length - 1)
				functions_text += ", ";
		}

		var objects_text = "";

		for (var j = 0; j < objects.length; j++) {
			objects_text += objects[j];
			if (j != objects.length - 1)
				objects_text += ", ";
		}

		var vars_text = "";

		for (var j = 0; j < vars.length; j++) {
			vars_text += vars[j];
			if (j != vars.length - 1)
				vars_text += ", ";
		}

		this.log("INFO:", "#62ff07"); // #62ff07 == light green
		
		if(functions_text != ""){
			this.log("Functions:", "yellow");
			this.log(functions_text);	
		}
		if(objects_text != ""){
			this.log("Objects:", "yellow");
			this.log(objects_text);	
		}
		if(vars_text != ""){
			this.log("Variables", "yellow");
			this.log(vars_text);	
		}
	}

	printObject(name) {
		var obj = name;

		if (obj == null) // object doesn't exist
			return false;

		var html = JSON.stringify(obj, null, 4);

		if (html == null || html == undefined) {
			this.log("Can't print that.", "yellow");
			return false;
		}

		var text = escapeHTML(html);

		this.log("<hr>");
		this.log("OBJECT <span style='color: white;'>" + obj.constructor.name.toUpperCase() + "</span>:", "#62ff07"); // #62ff07 == light green
		this.log("");
		this.log(text, "yellow");
		this.log("<hr>");
	}

	// LOCAL VARIABLES ->

	new(name, att) {
		this[name] = att;
	}

	set(name, att) {
		this[name] = att;
	}

	plus(name, att) {
		this[name] = this[name] + att;
	}

	minus(name, att) {
		this[name] = this[name] - att;
	}

	delete(name) {
		delete this[name];
	}

	// <- LOCAL VARIABLES
}

class Global {
	constructor(x) {}

	new(name, att, consoleID) {
		if (consoleID == null) {
			consoleID = focusedConsoleID;
		}

		var check;

		check = this[name];

		if (check != null) {
			windows[consoleID].log("<i style='color: #42f4e2;'>GLOBAL</i> variable <span style='color: white'><b><i>" + name + "</i></b></span> already exist. Use <a href='../docs?varMethods' target='_blank'>variable operate methods</a> to operate it. | <span style='color: white'>" + name + " = " + check + "</span>", "red");

			return false;
		}

		this[name] = att;

		if (!isNaN(this[name])) {
			this[name] = parseInt(this[name]);
		}

		windows[consoleID].log("<i style='color: #42f4e2;'>GLOBAL</i> variable succesfully created. | <span style='color: white'>" + name + " = " + att + "</span>", "#62ff07"); // #62ff07 == light green

		this._reloadOutputs();
	}

	set(name, att, consoleID) {
		if (consoleID == null) {
			consoleID = focusedConsoleID;
		}

		// Check is variable exist -->

		var check = this[name];

		if (this[name] == null) {
			this.new(name, att, consoleID);
			return false;
		}

		// If input attr is null -->

		if (att == null) {
			att = prompt("Please enter new value.", this[name]);
		}

		// Everything is okay -->

		this[name] = att;

		if (!isNaN(this[name])) {
			this[name] = parseInt(this[name]);
		}

		windows[consoleID].log("<i style='color: #42f4e2;'>GLOBAL</i> variable succesfully set. | <span style='color: white'>" + name + " = " + att + "</span>", "#62ff07"); // #62ff07 == light green

		this._reloadOutputs();
	}

	print(name, consoleID) {
		if (consoleID == null) {
			consoleID = focusedConsoleID;
		}

		if (this[name] == null) {
			windows[consoleID].log("<i style='color: #42f4e2;'>GLOBAL</i> variable <span style='color: white'><b>" + name + "</b></span> doesn't exist.", "red");
			return false;
		}

		windows[consoleID].log(this[name]);
	}

	plus(name, att, consoleID) {
		if (consoleID == null) {
			consoleID = focusedConsoleID;
		}

		this[name] = parseInt(this[name]) + parseInt(att);

		windows[consoleID].log("<i style='color: #42f4e2;'>GLOBAL</i> variable succesfully set <span style='color: white'>(+ " + att + ")</span>. | <span style='color: white'>" + name + " = " + this[name] + "</span>", "#62ff07"); // #62ff07 == light green

		this._reloadOutputs();
	}

	minus(name, att, consoleID) {
		if (consoleID == null) {
			consoleID = focusedConsoleID;
		}

		this[name] = parseInt(this[name]) - parseInt(att);

		windows[consoleID].log("<i style='color: #42f4e2;'>GLOBAL</i> variable succesfully set <span style='color: white'>(- " + att + ")</span>. | <span style='color: white'>" + name + " = " + this[name] + "</span>", "#62ff07"); // #62ff07 == light green

		this._reloadOutputs();
	}

	delete(name, consoleID) {
		if (consoleID == null) {
			consoleID = focusedConsoleID;
		}

		if (this[name] == null) {
			windows[consoleID].log("<i style='color: #42f4e2;'>GLOBAL</i> variable <span style='color: white'><b>" + name + "</b></span> doesn't exist already, so it can't be deleted.", "red");

			return false;
		}

		delete this[name];

		windows[consoleID].log("<i style='color: #42f4e2;'>GLOBAL</i> variable succesfully deleted. | <span style='color: white'>" + name + "</span> doesn't exist.", "#62ff07"); // #62ff07 == light green

		this._reloadOutputs();
	}

	list(listReturn, noprint, consoleID) {
		var keys = Object.keys(this);
		var list = "";

		for (var i = 0; i < keys.length; i++) {
			var y = this[keys[i]];

			var temp = keys[i] + " = " + y.toString();
			list += temp;

			if (i != keys.length - 1) {
				list += "<br />";
			}
		}

		if (consoleID == null && focusedConsoleID != null) {
			consoleID = focusedConsoleID;
		}

		if (consoleID != null && noprint == null) {
			windows[consoleID].log("List of variables in <span style='color: white'><i>" + this.constructor.name + "</i></span>:", "#62ff07"); // #62ff07 == light green
			if (list === "")
				windows[consoleID].log("no variables in this object.", "red");
			else
				windows[consoleID].log(list, "#42f4f1");
		}

		if (listReturn != null)
			return list;
		else
			return keys;
	}

	var (name) {
		return this[name];
	}

	if (what, command, consoleID) {
		for (var i = 0; i < command.length; i++) {
			if (command[i] === "[") {
				command = command.replaceAt(i, "(");
			}
			if (command[i] === "]") {
				command = command.replaceAt(i, ")");
			}
		}

		eval(`if(` + what + `){
      commandParser("` + command + `", ` + consoleID + `)
    } else{
      windows[` + consoleID + `].log("<b>If</b> returned <span style='color: white;'>false</span>.", "red");
    }`);
	}

	deleteAll(consoleID, noPrint, count) {
		var keys = this.list(null, 1);
		var count = 0;

		for (var i = 0; i < keys.length; i++) {
			delete this[keys[i]];
			count++;
		}

		this._reloadOutputs();

		if (consoleID == null)
			consoleID = focusedConsoleID;

		if (noPrint == null || noPrint == false) {
			windows[consoleID].log("All variables from <span style='color: white'>Global</span> have been deleted.", "#62ff07"); // #62ff07 == light green
		}

		if (count === true)
			return count;
	}

	alert(what) {
		Alert("Alert", what);
	}

	execute(what, from) {
		newWindow("console");

		if (from == null)
			from = "undefined source";

		windows[windows.length - 1].log(">> Executing <b>" + from + "</b>... <<", "#62ff07"); // #62ff07 == light green
		windows[windows.length - 1].not_save = true;

		parse(what, windows.length - 1);
	}

	_reloadOutputs() {
		for (var i = 0; i < windows.length; i++) {
			if (windows[i].reload_ === true) {
				windows[i].ReloadContent();
			}
		}
		this._save();
	}

	_save() {
		var keys = this.list(null, 1);
		var vars = {};

		for (var i = 0; i < keys.length; i++) {
			var name = keys[i];

			var act = {
				name: keys[i],
				val: this[name]
			}

			vars[i] = act;
		}

		AJAX("saveVars", JSON.stringify(vars));

		return vars;
	}

	_load() {
		var it = this;

		$.when(AJAX("getVars", "", "JSON")).done(function(response) {
			var vars = $.map(response, function(el) {
				return el
			});

			for (var i = 0; i < vars.length; i++) {
				it[vars[i].name] = vars[i].val;
			}

			it._reloadOutputs();
		});
	}
}

class VariablesWindow {
	constructor(x) {
		this.w = 600;
		this.h = 300;
		this.x = Math.floor((Math.random() * ($(window).width()) - this.w) + 0);
		this.y = Math.floor((Math.random() * ($(window).height()) - this.h) + 0);

		if (this.x < 0)
			this.x = 100;
		if (this.y < 0)
			this.y = 100;

		this.id = incrementID;
		this.type = "VariablesWindow";

		this.reload_ = true;

		this.content = "";

		this.hidden = false;

		this.is = true;

		this.variables = [];
	}

	ReloadContent() {
		// CREATE CONTENT ->

		var globalVars = global.list(true, 1);

		this.content = globalVars;

		if (this.content === "" || this.content == null) {
			this.content = "<b style='color: red;'>There's no variables.</b>";
		}

		// <-
		
		var refresh = `<br /><br /><span class="clickable notFullVisible" onclick="windows[` + this.id + `].ReloadContent()">refresh</span>`;

		$("#variables_content_" + this.id).html(this.content + refresh);
	}

	Load() {
		if (this.is === true && this.hidden !== true) {
			// CREATE CONTENT ->

			var globalVars = global.list(true, 1);

			this.content = globalVars;

			if (this.content === "" || this.content == null) {
				this.content = "<b style='color: red;'>There's no variables.</b>";
			}

			// <-

			if (this.loaded === true) {
				$("#variables_" + this.id).remove();
			}

			this.onclick = ``;

			this.onmouseover = `$(this).draggable({ stop: function(){
        var it = windows[` + this.number + `];

        windowCollider(it, this);
      } });
        $(this).resizable({ stop: function(){ var it = windows[` + this.number + `]; windowCollider(it, this); } });
      `;

			this.onmouseup = ``;

			this.min_button = `<div class="clickable" title="Minimize" style="position: absolute; right: 25px; top: 2%;"><span onclick="windows[` + this.number + `].hide()" class="glyphicon glyphicon-minus" aria-hidden="true"></span></div>`;

			this.off_button = `<div class="clickable" style="position: absolute; right: 5px; top: 1%;"><span onclick="windows[` + this.number + `].close()" class="glyphicon glyphicon-remove" aria-hidden="true"></span></div>`;

			this.content_wrapper = `<div id="variables_content_` + this.id + `" class="content" onclick="event.stopPropagation();` + this.onclick + `" style="position: absolute; top: 15%; height: 75%; width: 95%; overflow: auto;">` + this.content + `</div>`;
			
			this.inner = "<h4>Variables</h4>" + this.off_button + this.min_button + this.content_wrapper;

			this.newdiv = "<div onmouseup='" + this.onmouseup + "' onmouseover='" + this.onmouseover + "' id='variables_" + this.id + "' class='window variablesLayout' onclick='" + this.onclick + "' style='position: absolute; width: " + this.w + "px; min-height: 200px; min-width: 200px; height: " + this.h + "px; left: " + this.x + "px; top: " + this.y + "px;'><div style='margin: 2%;'>" + this.inner + "</div></div>"

			document.getElementById("windows").innerHTML = document.getElementById("windows").innerHTML + this.newdiv;
			
			this.ReloadContent();

			this.loaded = true;
		}
	}

	hide() {
		var it = this;

		setTimeout(function() {
			it.hidden = true;

			if ($("#hidden_" + it.id).length) {
				$("#hidden_" + it.id).remove();
			}

			if ($("#variables_" + it.id).length)
				$("#variables_" + it.id).hide("drop", {
					direction: "right"
				}, 500);

			refreshHiddenWindows();

			saveWindows();
		}, 100);
	}

	show() {
		this.hidden = false;

		if ($("#variables_" + this.id).length)
			$("#variables_" + this.id).fadeIn("medium");
		else
			this.Load();

		$("#hidden_" + this.id).fadeOut(1000).remove();

		saveWindows();
	}

	close() {
		this.is = false;

		this.w = 0;
		this.h = 0;
		this.x = 0;
		this.y = 0;

		$("#variables_" + this.id).remove();

		saveWindows();
	}
}

class file {
	constructor(name, ex) {
		this.name = name;
		this.ex = ex;

		this.url = name + "." + ex;

		this.number = storage.files.length;
		this.content = "";
	}

	_getContent() {
		var url = this.url;

		return $.ajax({
			type: "POST",
			url: "server.php",
			data: {
				action: "getFileContent",
				name: url
			},
			dataType: 'text',
			success: function(response) {
				// ...
			},
			error: function(error) {
				console.log(error);
			}
		});
	}

	_getVisual(windowWidth) {
		var height = 0;
		var width = 0;
		var interc = 4; // Math.round((windowWidth - 80) / 120); // <- number of files in one line
		var inter = interc;
		var upp = 0;

		while (true) {
			if (this.number >= inter) {
				height += 120;
				inter += interc;
				upp += interc;
			} else
				break;
		}

		width = (this.number - upp) * 120;

		var res = `<div onclick="javascript:storage._clickChoose(storage.files[` + this.number + `])" class="clickable" style="position: absolute; width: 100px; word-break: break-all; text-align: center; left: ` + width + `px; top: ` + height + `px; color: white; display: inline;">
      <span class="glyphicon glyphicon-file" style="font-size: 3.5vmin;" aria-hidden="true"></span>
      <br />
      <span>` + this.url + `</span>
    </div>`;

		return res;
	}
}

class Storage {
	constructor(x) {
		this.files = new Array();

		this.loaded = false;

		this.actOpening = "";
		this.lastOpenedExec = "";
	}

	_reloadOutputs() {
		for (var i = 0; i < windows.length; i++) {
			if (windows[i].reload_ === true) {
				windows[i].ReloadContent();
			}
		}
		if (this.loaded === true)
			this._save();
	}

	new(url, consoleID, noprint) {
		if (consoleID == null) {
			consoleID = focusedConsoleID;
		}

		var name = "";
		var ex = "";

		var actPars = "name";

		for (var b = 0; b < url.length; b++) {
			if (actPars === "name") {
				if (url[b] !== ".") {
					name = name + url[b];
				} else {
					actPars = "ex";
					b++;
				}
			}
			if (actPars === "ex") {
				ex = ex + url[b];
			}
		}

		if (name == null) {
			if (noprint === false || noprint == null)
				windows[consoleID].log("File must have a name.", "red");

			return false;
		}

		if (ex == null || ex === "") {
			if (noprint === false || noprint == null)
				windows[consoleID].log("File extension <span style='color: white'>(*.ex)</span> cannot be <span style='color: white'>null</span>.", "red");

			return false;
		}

		for (var i = 0; i < this.files.length; i++) {
			if (name === this.files[i].name && ex === this.files[i].ex) {
				if (noprint === false || noprint == null)
					windows[consoleID].log("File nammed <span style='color: white'><b>" + name + "." + ex + "</b></span> already exist.", "red");

				return false;
			}
		}

		// Everything's fine -->

		this.files.push(new file(name, ex));

		if (noprint === false || noprint == null)
			windows[consoleID].log("File nammed <span style='color: white'><b>" + name + "." + ex + "</b></span> created successfully.", "#62ff07"); // #62ff07 == light green

		this._reloadOutputs();
	}

	delete(url, consoleID) {
		if (consoleID == null) {
			consoleID = focusedConsoleID;
		}

		if (url === null) {
			windows[consoleID].log("Input file which you want to delete.", "red");

			return false;
		}

		var status;

		for (var i = 0; i < this.files.length; i++) {
			if (this.files[i].url === url) {
				this.files.splice(i, 1);

				status = "ok";

				windows[consoleID].log("File successfully deleted from the storage. |<span style='color: white;'> " + url + "</span> doesn't exist.", "#62ff07"); // #62ff07 == light green

				this._reloadOutputs();

				break;
			}
		}

		if (status !== "ok") {
			windows[consoleID].log("File nammed <span style='color: white'><b>" + url + "</b></span> doesn't exist already, so it can't be deleted.", "red");

			return false;
		}
	}

	deleteAll(consoleID) {
		if (consoleID == null)
			consoleID = focusedConsoleID;
		
		Alert("Are you sure?", "All files will be deleted.", "<button onclick='storage.files = []; storage._reloadOutputs(); closeAlert();' class='btn btn-danger'>Yes</button>");
	}

	edit(url, content, consoleID, noprint) {
		if (consoleID == null) {
			consoleID = focusedConsoleID;
		}

		var x;
		var res;

		for (var i = 0; i < this.files.length; i++) {
			if (this.files[i].url === url) {
				x = i;
				res = "ok";
			}
		}

		if (res !== "ok") {
			windows[consoleID].log("File nammed <span style='color: white'><b>" + url + "</b></span> doesn't exist.", "red");

			return false;
		}

		// If input content is null -->

		if (content === null || typeof content === "number") {
			content = prompt("Please enter new content.", this.files[x].content);
		}

		// Everything's ok -->

		this.files[x].content = content;

		if (noprint === false || noprint == null)
			windows[consoleID].log("Content of file nammed <span style='color: white'><b>" + url + `</b></span> successfully changed. | <a href="javascript:storage.open('` + this.files[x].url + `')">Click to see new content.</a>`, "#62ff07"); // #62ff07 == light green
		// 'see content' TO CHANGE ^

		this._reloadOutputs();
	}

	file(name, what, consoleID) {
		var res;

		for (var i = 0; i < this.files.length; i++) {
			if (this.files[i].url === name) {
				res = this.files[i].content;

				break;
			}
		}

		if (res == null) {
			// .. file doesn't exist
		}

		return res;
	}

	exist(filename, consoleID, noprint) {
		if (consoleID == null)
			consoleID = focusedConsoleID;

		var res = false;

		for (var i = 0; i < this.files.length; i++) {
			if (this.files[i].url === filename) {
				res = true;
			}
		}

		if (noprint == null || noprint === false) {
			windows[consoleID].log("Result: <span style='color: white'>" + res + "</span>.", "yellow");
		}

		return res;
	}
	
	list(consoleID){
		if (consoleID == null)
			consoleID = focusedConsoleID;
		
		var fileList = "";
		
		for(var i = 0; i < this.files.length; i++){
			fileList += this.files[i].name + "." + this.files[i].ex;
			if(i != this.files.length - 1)
				fileList += ", ";
		}
		
		windows[consoleID].log("Files: " + fileList, "#62ff07"); // #62ff07 == light green
	}

	open(url, consoleID, noprint, nochoose) {
		if (consoleID == null)
			consoleID = focusedConsoleID;

		var ok = false;

		for (var i = 0; i < this.files.length; i++) {
			if (this.files[i].url === url) {
				if (nochoose == null && this.files[i].ex !== "txt" && this.files[i].ex !== "html" && this.files[i].ex !== "php" && this.files[i].ex !== "png" && this.files[i].ex !== "gif" && this.files[i].ex !== "js") {
					// it's not COMMON file

					this.actOpening = url;

					$('#open_as_modal').modal('toggle');

					return false;
				} else if (nochoose == null && this.files[i].ex === "js") {
					// it's EXECUTABLE file

					storage.lastOpenedExec = this.files[i].content;

					var nameOfExec = this.files[i].url;

					setTimeout(function() {
						Alert("Executable file", "This file has an <b>.js</b> extention, so it propably can be executed (as application).<br /><br />Execute it?", "<button onclick='global.execute(storage.lastOpenedExec, `" + nameOfExec + "`); closeAlert()' class='btn btn-success'>Yes</button><button onclick='storage.open_as_txt(`" + nameOfExec + "`, null, true); closeAlert()' class='btn btn-primary'>Open</button>");
					}, 500);

					return false;
				}

				ok = true;

				var win = window.open("../users/" + username + "/files/" + url, '_blank');
				win.focus();
			}
		}

		if (noprint == null || noprint === false)
			windows[consoleID].log("File nammed <span style='color: white;'>" + url + "</span> has been opened.", "#62ff07"); // #62ff07 == light green
	}

	open_as_txt(url, consoleID, noprint) {
		if (consoleID == null)
			consoleID = focusedConsoleID;

		var ok = false;

		for (var i = 0; i < this.files.length; i++) {
			if (this.files[i].url === url) {
				ok = true;

				var txturl = this.files[i].name + ".txt";

				var arr = [txturl, this.files[i].content];

				AJAX("createTempTxt", JSON.stringify(arr)); // create temp txt file

				setTimeout(function() { // open window

					var win = window.open("../users/temp/" + txturl, '_blank');
					win.focus();

				}, 2500);

				setTimeout(function() { // delete temp txt file

					AJAX("deleteTempTxt", txturl);

				}, 4500);
			}
		}

		if (noprint == null || noprint === false)
			windows[consoleID].log("File nammed <span style='color: white;'>" + url + "</span> has been opened as <span color='white'>txt</span>.", "#62ff07"); // #62ff07 == light green
	}

	eval(filename, consoleID) {
		if (consoleID == null)
			consoleID = focusedConsoleID;

		var command = this.file(filename);

		var file_exist = this.exist(filename, 0, true);

		if (file_exist === false) {
			windows[consoleID].log("File nammed <span style='color: white'>" + filename + "</span> doesn't exist.", "red");

			return false;
		}

		if (command == null)
			return false;

		parse(command, consoleID);
	}

	get(filename, consoleID, noprint) {
		if (consoleID == null)
			consoleID = focusedConsoleID;

		var it;

		for (var i = 0; i < this.files.length; i++) {
			if (this.files[i].url === filename) {
				it = this.files[i];
			}
		}
		
		return it;
	}
	
	print(filename, consoleID){
		if (consoleID == null)
			consoleID = focusedConsoleID;

		var it;

		for (var i = 0; i < this.files.length; i++) {
			if (this.files[i].url === filename) {
				it = this.files[i];
			}
		}
		
		windows[consoleID].log(escapeHTML(it.content));
	}

	_save() {
		var fNames = [];
		var fContents = [];
		var count = 0;

		for (var i = 0; i < this.files.length; i++) {
			fNames[i] = this.files[i].url;
			fContents[i] = this.files[i].content;
			count++;
		}

		fNames = JSON.stringify(fNames);
		fContents = JSON.stringify(fContents);

		$.ajax({
			type: "POST",
			url: "server.php",
			data: {
				action: "saveFiles",
				names: fNames,
				contents: fContents
			},
			dataType: "text",
			success: function(response) {
				if (response === "session expired") {
					window.location.assign("../index.php?msg=" + response);
				}
			},
			error: function(data) {
				console.log("ajax error: " + data);
			}
		});

		return count;
	}

	_load() {
		var fNames;
		var it = this;

		$.when(AJAX("getFiles", "", "JSON")).done(function(response) {
			fNames = response;

			// CREATE FILES IN STORAGE

			for (var i = 0; i < fNames.length; i++) {
				var name = "";
				var ex = "";

				var actPars = "name";

				for (var b = 0; b < fNames[i].length; b++) {
					if (actPars === "name") {
						if (fNames[i][b] !== ".") {
							name = name + fNames[i][b];
						} else {
							actPars = "ex";
							b++;
						}
					}
					if (actPars === "ex") {
						ex = ex + fNames[i][b];
					}
				}

				it.files.push(new file(name, ex));
			}

			it._reloadOutputs();

			// SET CONTENTS

			var contents = [];
			var names = [];

			for (var i = 0; i < it.files.length; i++) {
				var all = it.files[i]._getContent();
				var name = it.files[i].url;

				contents.push(all);
				names.push(name);
			}

			setTimeout(function() {
				for (var i = 0; i < it.files.length; i++) {
					it.edit(names[i], contents[i].responseText, 0, true);
				}
				it.loaded = true;
			}, 1000);
		});
	}

	_clickChoose(file_) {
		Alert("Choose", "Do you want to open or edit this file?", `<button type="button" class="btn btn-default" onclick="storage.open('` + file_.url + `', 0, true)" data-dismiss="modal">Open</button> <button type="button" class="btn btn-default" onclick="closeAlert(); newWindow('editor'); windows[windows.length - 1].openFile('` + file_.url + `');" data-dismiss="modal">Edit</button>`);
	}
}

class StorageWindow {
	constructor(x) {
		this.w = 600;
		this.h = 300;
		this.x = Math.floor((Math.random() * ($(window).width()) - this.w) + 0);
		this.y = Math.floor((Math.random() * ($(window).height()) - this.h) + 0);

		if (this.x < 0)
			this.x = 100;
		if (this.y < 0)
			this.y = 100;

		this.id = incrementID;
		this.type = "StorageWindow";

		this.reload_ = true;

		this.hidden = false;

		this.content = "";

		this.is = true;
	}

	ReloadContent() {
		this.content = "";

		for (var i = 0; i < storage.files.length; i++) {
			this.content = this.content + storage.files[i]._getVisual(this.w);
		}

		$("#storage_content_" + this.id).html(this.content);
	}

	Load() {
		if (this.is === true && this.hidden !== true) {
			this.ReloadContent();

			if (this.loaded === true) {
				$("#storage_" + this.id).remove();
			}

			this.rightclick = ""; // ...

			this.onclick = ``;

			this.onmouseover = `$(this).draggable({ stop: function(){
        var it = windows[` + this.number + `];

        windowCollider(it, this);
      } });
        $(this).resizable({ stop: function(){ var it = windows[` + this.number + `]; windowCollider(it, this); } });`;

			this.onmouseup = ``;

			this.newf_button = `<div class="clickable" title="New file" style="position: absolute; right: 45px; top: 1%;"><span onclick="storage.new(prompt('Create new file:'), 0, true)" class="glyphicon glyphicon-file" aria-hidden="true"></span></div>`;

			this.min_button = `<div class="clickable" title="Minimize" style="position: absolute; right: 25px; top: 2%;"><span onclick="windows[` + this.number + `].hide()" class="glyphicon glyphicon-minus" aria-hidden="true"></span></div>`;

			this.off_button = `<div class="clickable" style="position: absolute; right: 5px; top: 1%;"><span onclick="windows[` + this.number + `].close()" class="glyphicon glyphicon-remove" aria-hidden="true"></span></div>`;

			this.content_wrapper = `<div id="storage_content_` + this.id + `" class="content" onclick="event.stopPropagation(); ` + this.onclick + `" style="position: absolute; top: 15%; height: 75%; width: 95%; overflow: auto;">` + this.content + `</div>`;

			this.inner = "<h4>Storage</h4>" + this.off_button + this.min_button + this.newf_button + this.content_wrapper;

			this.newdiv = "<div onmouseup='" + this.onmouseup + "' onmouseover='" + this.onmouseover + "' id='storage_" + this.id + "' class='window storageLayout' contextmenu='" + this.rightclick + "' onclick='" + this.onclick + "' style='position: absolute; width: " + this.w + "px; min-height: 200px; min-width: 200px; height: " + this.h + "px; left: " + this.x + "px; top: " + this.y + "px;'><div style='margin: 2%;'>" + this.inner + "</div></div>"

			document.getElementById("windows").innerHTML = document.getElementById("windows").innerHTML + this.newdiv;

			var it = this;

			this.loaded = true;
		}
	}

	hide() {
		var it = this;

		setTimeout(function() {
			it.hidden = true;

			if ($("#hidden_" + it.id).length) {
				$("#hidden_" + it.id).remove();
			}

			if ($("#storage_" + it.id).length)
				$("#storage_" + it.id).hide("drop", {
					direction: "right"
				}, 500);

			refreshHiddenWindows();

			saveWindows();
		}, 100);
	}

	show() {
		this.hidden = false;

		if ($("#storage_" + this.id).length)
			$("#storage_" + this.id).fadeIn("medium");
		else
			this.Load();

		$("#hidden_" + this.id).fadeOut(1000).remove();

		saveWindows();
	}

	close() {
		this.is = false;

		this.w = 0;
		this.h = 0;
		this.x = 0;
		this.y = 0;

		$("#storage_" + this.id).remove();

		saveWindows();
	}
}

class Web {
	constructor(x) {

	}

	gethtml(url, consoleID) {
		if (consoleID == null)
			consoleID = focusedConsoleID;

		url = this._url(url);

		var XHR = $.ajax({
			type: "POST",
			url: "server.php",
			data: {
				action: "gethtml",
				arg: url
			},
			dataType: "text",
			async: false,
			success: function(response) {},
			error: function(data) {
				console.log(data);
			}
		});

		return XHR.responseText;
	}

	send(url, action, args, type, dataType, consoleID, noprint) {
		if(consoleID == null)
			consoleID = focusedConsoleID;
		
		var check = true;

		if (url != null && consoleID == null) {
			if (action == null) {
				consoleID = url;
			}
			if (action != null && args == null) {
				consoleID = action;
				action = null;
				check = false;
			}
			if (args != null && type == null) {
				consoleID = args;
				args = null;
				check = false;
			}
		}

		if ((url == null || action == null || args == null || type == null || dataType == null) && check === true) {
			if (noprint == null || noprint === false) {
				windows[consoleID].log("Usage: <span style='color:white'>send(url, action, args, type, dataType)</span>", "yellow");
			}

			return false;
		}

		url = this._url(url);

		if (type == null || type === 0)
			type = "POST";

		if (dataType == null || dataType === 0)
			dataType = "text";

		if (Object.prototype.toString.call(args) === "[object Array]") {
			args = JSON.stringify(args);
		}

		if (args == null)
			args = "";

		$.ajax({
			type: type,
			url: url,
			data: {
				action: action,
				args: args
			},
			dataType: dataType,
			success: function(response) {
				if (noprint == null || noprint === false) {
					windows[consoleID].printObject(response);
				}
			},
			error: function(data) {
				if (noprint == null || noprint === false) {
					windows[consoleID].printObject(data);
				}
			}
		});
	}

	open(url, consoleID, noprint) {
		if (consoleID == null)
			consoleID = focusedConsoleID;

		url = this._url(url);

		var win = window.open(url);
		win.focus();

		if (noprint == null || noprint === false) {
			windows[consoleID].log("Page <span style='color: white;'>" + url + "</span> has been opened.", "#62ff07"); // #62ff07 == light green
		}
	}

	search(what, consoleID, noprint) {
		if (what === "" || what == null)
			return 0;

		this.open("www.google.pl/#q=" + what, 0, true);

		windows[consoleID].log("Term <span style='color: white;'>" + what + "</span> has been googled.", "#62ff07"); // #62ff07 == light green
	}

	_url(url) {
		var first = url.substring(0, 1);

		if (first !== "/") {
			if (!/^(f|ht)tps?:\/\//i.test(url)) {
				url = "http://" + url;
			}
		} else {
			url = "../users/" + username + "/files" + url;
		}

		return url;
	}
}

class EditorWindow {
	constructor(x) {
		this.w = 800;
		this.h = 400;
		this.x = Math.floor((Math.random() * ($(window).width()) - this.w) + 0);
		this.y = Math.floor((Math.random() * ($(window).height()) - this.h) + 0);

		if (this.x < 0)
			this.x = 100;
		if (this.y < 0)
			this.y = 100;

		this.id = incrementID;
		this.type = "EditorWindow";

		this.is = true;

		this.lang = "javascript";

		this.content = "- - -";

		this.reload_ = false;

		this.hidden = false;

		this.loaded = false;

		this.editor = 0;
	}

	Load() {
		if (this.is === true && this.hidden !== true) {
			if (this.loaded === true) {
				$("#editor_" + this.id).remove();
			}

			this.onclick = ``;

			this.onmouseover = `$(this).draggable({ stop: function(){
        var it = windows[` + this.number + `];

        windowCollider(it, this);
      }, cancel: ".noDrag" });
        $(this).resizable({ stop: function(){ var it = windows[` + this.number + `]; windowCollider(it, this); } });`;

			this.onmouseup = ``;

			if (this.content !== "- - -") {
				var fileText = storage.file(this.content);
			}
			if (fileText == null)
				fileText = "";

			if (this.loaded === false && this.content !== "- - -") {
				fileText = "Loading...";
			}

			this.info_button = `<div class="clickable" style="position: absolute; right: 105px; top: 1%;"><span title="Info" onclick="Alert('Editor info', 'Mode: <b>' + windows[` + this.number + `].lang.toUpperCase() + '</b><br /><br />Opened file: <b>' + windows[` + this.number + `].content + '</b>')" class="glyphicon glyphicon-info-sign" aria-hidden="true"></span></div>`;

			this.settings_button = `<div class="clickable" style="position: absolute; right: 85px; top: 1%;"><span title="Settings" onclick="windows[` + this.number + `].changeMode(prompt('Enter new language for syntax coloring:'));" class="glyphicon glyphicon-cog" aria-hidden="true"></span></div>`;

			this.save_button = `<div class="clickable" style="position: absolute; right: 65px; top: 1%;"><span title="Save" onclick="event.stopPropagation(); storage.edit(windows[` + this.number + `].content, windows[` + this.number + `].editor.getValue(), 0, true); Alert('Saved.', 'File <b>' + windows[` + this.number + `].content + '</b> has been saved.')" class="glyphicon glyphicon-floppy-disk" aria-hidden="true"></span></div>`;

			this.open_button = `<div class="clickable" style="position: absolute; right: 45px; top: 1%;"><span title="Open" onclick="event.stopPropagation(); var name = prompt('Type name of file which you want to open...'); windows[` + this.number + `].openFile(name);" class="glyphicon glyphicon-folder-open" aria-hidden="true"></span></div>`;

			this.min_button = `<div class="clickable" title="Minimize" style="position: absolute; right: 25px; top: 2%;"><span onclick="windows[` + this.number + `].hide()" class="glyphicon glyphicon-minus" aria-hidden="true"></span></div>`;

			this.off_button = `<div class="clickable" style="position: absolute; right: 5px; top: 1%;"><span onclick="windows[` + this.number + `].close()" class="glyphicon glyphicon-remove" aria-hidden="true"></span></div>`;

			this.textarea = `<div class="noDrag" onclick="event.stopPropagation();" style="height: 100%;"><textarea id="editor_textarea_` + this.id + `" spellcheck="false" style="width: 100%; height: 100%; border: 1px dotted #ccc; border-bottom: none; background-color: black !important; color: #62ff07; font-family: consolas, consolas;">` + fileText + `</textarea></div>`;

			this.inner = "<h4 style='width: 30%;'>Editor: " + this.content + "</h4>" + this.textarea + this.save_button + this.open_button + this.off_button + this.min_button + this.settings_button + this.info_button;

			this.newdiv = "<div onclick='" + this.onclick + "' onmouseup='" + this.onmouseup + "' onmouseover='" + this.onmouseover + "' id='editor_" + this.id + "' class='window' style='position: absolute; width: " + this.w + "px; min-height: 350px; min-width: 640px; height: " + this.h + "px; left: " + this.x + "px; top: " + this.y + "px;'><div style='margin: 2%; height: 80%;'>" + this.inner + "</div></div>"

			document.getElementById("editors").innerHTML = document.getElementById("editors").innerHTML + this.newdiv;

			var textarea = document.getElementById("editor_textarea_" + this.id);

			var lang = this.lang;

			this.editor = CodeMirror.fromTextArea(textarea, {
				lineNumbers: false,
				theme: "isotope",
				mode: lang,
				tabSize: 3,
				styleSelectedText: true,
				styleActiveLine: false // it should be user preference.
			});

			if (this.loaded === false && this.content !== "- - -") {
				var it = this;
				setTimeout(function() {
					it.openFile(it.content);
				}, 1500);
			}

			this.loaded = true;
		}
	}

	hide() {
		var it = this;

		if ($("#hidden_" + this.id).length) {
			$("#hidden_" + this.id).remove();
		}

		setTimeout(function() {
			it.hidden = true;

			if ($("#editor_" + it.id).length)
				$("#editor_" + it.id).hide("drop", {
					direction: "right"
				}, 500);

			refreshHiddenWindows();

			saveWindows();
		}, 100);
	}

	show() {
		this.hidden = false;

		if ($("#editor_" + this.id).length)
			$("#editor_" + this.id).fadeIn("medium");
		else
			this.Load();

		$("#hidden_" + this.id).fadeOut(1000).remove();

		saveWindows();
	}

	close() {
		this.is = false;

		this.w = 0;
		this.h = 0;
		this.x = 0;
		this.y = 0;

		$("#editor_" + this.id).remove();

		saveWindows();
	}

	openFile(name) {
		var test = storage.file(name);

		if (test == null) {
			Alert("Alert", "File nammed <b>" + name + "</b> doesn't exist!");

			return false;
		}

		this.content = name;

		this.Load();
	}

	changeMode(text) {
		if (text === "" || text == null)
			return 0;

		if (text === "html" || text === "HTML" || text === "XML")
			this.lang = "htmlmixed";
		else if (text === "js")
			this.lang = "javascript";
		else
			this.lang = text;

		storage.edit(this.content, this.editor.getValue(), 0, true);

		this.Load();

		Alert("Editor mode has been changed.", "File has beed saved. Editor mode was changed into <b>" + text.toUpperCase() + "</b>.")
	}
}

class CustomWindow {
	constructor(x) {
		this.w = 600;
		this.h = 300;
		this.x = Math.floor((Math.random() * ($(window).width()) - this.w) + 0);
		this.y = Math.floor((Math.random() * ($(window).height()) - this.h) + 0);

		if (this.x < 0)
			this.x = 100;
		if (this.y < 0)
			this.y = 100;

		this.lang = ""; // name of window (application)

		this.canResize = true;

		this.id = incrementID;
		this.type = "CustomWindow";

		this.reload_ = false;

		this.console = null;
		this.boundConsole = false; // if it's bound to console
		
		this.aligment;

		this.execFrom = "";

		this.content = "";

		this.not_save = true;

		this.is = true;
		
		this.echo = true; // PRINT DEBUG IN CONSOLE

		this.variables = new Array();
	}

	Load() {
		if (this.is === true) {
			if (this.loaded === true) {
				$("#app_" + this.id).remove();
			}

			this.onclick = ``;

			this.onmouseover = `$(this).draggable({ stop: function(){
        var it = windows[` + this.number + `];

        windowCollider(it, this);
      } });
        if(windows[` + this.number + `].canResize === true){
          $(this).resizable({ stop: function(){ var it = windows[` + this.number + `]; windowCollider(it, this); } });
        }
      `;

			this.onmouseup = ``;

			this.info_button = `<div class="clickable" style="position: absolute; right: 25px; top: 1%;"><span title="Info" onclick="Alert('Application info', 'Visible name: <b>' + windows[` + this.number + `].lang + '</b><br /><br />Executable file: <b>' + windows[` + this.number + `].execFrom + '</b>')" class="glyphicon glyphicon-info-sign" aria-hidden="true"></span></div>`;

			this.off_button = `<div class="clickable" style="position: absolute; right: 5px; top: 1%;"><span onclick="windows[` + this.number + `].close()" class="glyphicon glyphicon-remove" aria-hidden="true"></span></div>`;

			this.content_wrapper = `<div id="app_cont_` + this.id + `" class="content" onclick="event.stopPropagation();` + this.onclick + `" style="position: absolute; top: 15%; height: 75%; width: 95%; overflow: auto; text-align: ` + this.aligment + `;">` + this.content + `</div>`;

			this.inner = "<h4>" + this.lang + "</h4>" + this.off_button + this.info_button + this.content_wrapper;

			this.newdiv = "<div onmouseup='" + this.onmouseup + "' onmouseover='" + this.onmouseover + "' id='app_" + this.id + "' class='window' onclick='" + this.onclick + "' style='position: absolute; width: " + this.w + "px; min-height: 200px; min-width: 200px; height: " + this.h + "px; left: " + this.x + "px; top: " + this.y + "px;'><div style='margin: 2%;'>" + this.inner + "</div></div>"

			document.getElementById("windows").innerHTML = document.getElementById("windows").innerHTML + this.newdiv;

			this.loaded = true;
		}
	}

	resize(w, h) {
		this.w = w;
		this.h = h;

		if(this.echo)
			this.console.log("Window size has been set to <span style='color: white;'>" + w + ", " + h + "</span>.", "#62ff07"); // #62ff07 == light green

		this.Load();
	}

	toggleResize(x) {
		if(x == null){
			x = !this.canResize;
		}
		
		this.canResize = x;

		this.Load();

		if(this.echo)
			this.console.log("Window resize is <span style='color: white;'>" + x + "</span>.", "#62ff07"); // #62ff07 == light green
	}

	setContent(what) {
		this.content = what;

		this.Load();

		if(this.echo)
			this.console.log("Content has been set.", "#62ff07"); // #62ff07 == light green
	}

	align(how) {
		this.aligment = how;

		this.Load();

		if(this.echo)
			this.console.log("Content align has been set to <span style='color: white;'>" + how + "</span>.", "#62ff07"); // #62ff07 == light green
	}
	
	bind(){
		this.boundConsole = !this.boundConsole;
		
		if(this.echo)
			this.console.log("Window is bound to console: <span style='color: white;'>" + this.boundConsole + "</span>.", "#62ff07"); // #62ff07 == light green
	}

	close() {
		this.is = false;

		this.w = 0;
		this.h = 0;
		this.x = 0;
		this.y = 0;

		$("#app_" + this.id).remove();

		if (this.console != null)
			this.console.app = null;
		
		if(this.echo)
			this.console.log("Window closed.", "yellow");

		if (this.console != null && this.boundConsole == true)
			this.console.close();

		saveWindows();
	}
}