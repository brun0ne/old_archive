var incrementID = 0;
var increment_C_ID = 0;

var windows = [];

var global;

var strEvalShow_ = true;

var storage;

var web;

var focusedConsoleID;

var username;

var printCommands = true;
var freezeWindows = false;

var layout = {};
var own_layout = {};
var layout_list = ["black", "faded_colors"];
var selected_layout = "faded_colors";

var lastError = "";

$(document).ready(function() {
	$("body").animate({
		opacity: 1
	}, 1200);

	loadMains();

	$.when(AJAX("getUser")).done(function(response) {
		username = response;
	});

	/*window.onerror = function(msg, url, linenumber) {
		lastError = msg + "; URL: " + url + "; LineNumber: " + linenumber + ";";

		console.log(msg + "; URL: " + url + "; LineNumber: " + linenumber + ";"); // DEBUG ONLY !

		bugAlertIni();

		return true;
	}*/

	global = new Global(1);
	storage = new Storage(1);
	web = new Web(1);

	storage._load();
	loadWindows();
	global._load();

	checkOwnLayout();
	setLayout();

	setTimeout("autoSave()", 5000);
});

function download(filename, text) {
	var element = document.createElement('a');
	element.setAttribute('href', 'data:text/plain;charset=utf-8,' + encodeURIComponent(text));
	element.setAttribute('download', filename);

	element.style.display = 'none';
	document.body.appendChild(element);

	element.click();

	document.body.removeChild(element);
}

function bugAlertIni() {
	var text = `<span style="color: #2d2f33"><b>Something went wrong.</b><br />Help us and report it, it's only one click!</span><br /><br />
    <form action="bug_report.php" method="post"><textarea name="description" style="border: dotted black 1px; color: black" rows="4" cols="50" placeholder="Addicional description..."></textarea><br /><br />
    <input type="checkbox" name="bug_data" value="true" disabled checked> Include bug data<br>
    <input type="checkbox" name="user_data" value="true" checked> Include user data<br><br />
    <input type="submit" name="submit" value="Report" class="btn btn-danger"><br />
    <input type="hidden" id="bug_raport_DATA" name="bug_raport_DATA" value="" /></form>`;

	Alert("Report bug", text);

	$("#bug_raport_DATA").val(lastError);
}

$("#FirebugUI").ready(function() {
	$("#FirebugUI").css({
		"display": "none"
	});
});

String.prototype.replaceAt = function(index, character) {
	return this.substr(0, index) + character + this.substr(index + character.length);
}

String.prototype.replaceAll = function(search, replacement) {
	var target = this;
	return target.replace(new RegExp(search, 'g'), replacement);
};

String.prototype.insertAt = function(index, string) {
	return this.substr(0, index) + string + this.substr(index);
}

function windowsReload() {
	for (var i = 0; i < windows.length; i++) {
		windows[i].number = i;
		windows[i].Load();
	}

	saveWindows();
	saveMains();
}

function loadLayout() {
	try {
		$("body").css({
			"background-color": layout.Overlay.back,
			"color": layout.Overlay.text
		});

		$("<style type='text/css'> .consoleLayout{ color: " + layout.Console.text + " !important; background: " + layout.Console.back + " !important; } </style>").appendTo("head");

		$("<style type='text/css'> .variablesLayout{ color: " + layout.Variables.text + " !important; background: " + layout.Variables.back + " !important; } </style>").appendTo("head");

		$("<style type='text/css'> .storageLayout{ color: " + layout.Storage.text + " !important; background: " + layout.Storage.back + " !important; } </style>").appendTo("head");
	} catch (e) {
		setLayout(); // set default

		closeAlert();

		setTimeout(function() {
			Alert("Error", "<b>Your layout is broken.</b><br /><br />To make working layout, download one, open it in notepad and change properties like colors.");
		}, 500);

		return false;
	}
}

function setLayout(name) {
	if (name == null)
		name = "faded_colors"; // DEFAULT

	var ok = true;

	if (name === "black") {
		layout = {
			Overlay: {
				back: "#10100a",
				text: "#ebebe"
			},
			Console: {
				back: "black",
				text: "white"
			},
			Variables: {
				back: "black",
				text: "white"
			},
			Storage: {
				back: "black",
				text: "white"
			}
		};
	} else if (name === "faded_colors") {
		layout = {
			Overlay: {
				back: "#10100a",
				text: "#ebebe"
			},
			Console: {
				back: "#000451",
				text: "white"
			},
			Variables: {
				back: "#2e6300",
				text: "white"
			},
			Storage: {
				back: "#511d0d",
				text: "white"
			}
		}
	} else if (name === "custom") {
		if (own_layout !== {})
			layout = own_layout;
		else // set default
			layout = {
				Overlay: {
					back: "#10100a",
					text: "#ebebe"
				},
				Console: {
					back: "#000451",
					text: "white"
				},
				Variables: {
					back: "#2e6300",
					text: "white"
				},
				Storage: {
					back: "#511d0d",
					text: "white"
				}
			};
	}

	selected_layout = name;

	loadLayout();
}

function checkOwnLayout() {
	$.when(AJAX("checkOwnLayout", "", "text")).done(function(response) {
		if (response == 1) {
			layout_list.push("custom");

			$.when(AJAX("getOwnLayout", "", "text")).done(function(response) {
				try {
					own_layout = JSON.parse(response);
				} catch (e) {
					console.log("Server returned broken layout.");
					own_layout = null;
				}

				if (selected_layout === "custom")
					setLayout("custom");
			});
		}
	});
}

function windowCollider(it, obj) {
	var old_x = it.x;
	var old_y = it.y;
	var old_w = it.w;
	var old_h = it.h;

	it.x = $(obj).position().left;
	it.y = $(obj).position().top;
	it.w = $(obj).width();
	it.h = $(obj).height();

	if (it.w < 80)
		it.w = 80;
	if (it.h < 60)
		it.h = 60;

	/*var eleWidth = it.w,
	eleHeight = it.h,
	eleLeft = it.x,
	eleTop = it.y,
	eleRight = $(window).width() - (eleLeft + eleWidth),
	eleBtm = $(window).height() - (eleTop + eleHeight);

	for(var i = 0; i < windows.length; i++){
	  if(i != it.number && windows[i].is === true){
	    var cWidth = windows[i].w,
	    cHeight = windows[i].h,
	    cLeft = windows[i].x,
	    cRight = $(window).width() - (cLeft + cWidth),
	    cTop = windows[i].y,
	    cBtm = $(window).height() - (cTop + cHeight);

	    if (
	        cLeft < (eleLeft + eleWidth) &&
	        cRight < (eleRight + eleWidth) &&
	        cTop < (eleTop + eleHeight) &&
	        cBtm < (eleBtm + eleHeight)
	      ){
	        it.x = old_x;
	        it.y = old_y;
	        it.w = old_w;
	        it.h = old_h;
	        $(obj).animate({
	          left: old_x,
	          top: old_y,
	          width: old_w,
	          height: old_h
	        }, 500);
	        if(it.type === "Console"){
	          $("#console_" + it.id + "_input_command").animate({ // console input area
	            width: old_w - 40,
	          }, 500);
	        }
	        if(it.type === "ExploratorWindow"){
	          $("#explorator_" + it.id + "_input_page").animate({ // console input area
	            width: old_w - 40,
	          }, 500);
	        }
	      }
	  }
	}*/

	saveWindows();
}

function newWindow(window) {
	if (window === "console") {
		windows.push(new Console(0));
		windowsReload();

		incrementID++;
		increment_C_ID++;
	} else if (window === "variables") {
		windows.push(new VariablesWindow(0));
		windowsReload();

		incrementID++;
	} else if (window === "storage") {
		windows.push(new StorageWindow(0));
		windowsReload();

		incrementID++;
	} else if (window === "editor") {
		windows.push(new EditorWindow(0));
		windowsReload();

		incrementID++;
	} else if (window === "app") {
		windows.push(new CustomWindow(0));
		windowsReload();

		incrementID++;
	} else if (window === "settings") {
		var pc = "";
		var fw = "";
		var ll = "";

		if (printCommands)
			pc = "<input type='checkbox' id='printCommandsCheckbox' checked/> Print commands (console)<br />";
		else
			pc = "<input type='checkbox' id='printCommandsCheckbox' /> Print commands (console)<br />";

		if (freezeWindows)
			fw = "<input type='checkbox' id='freezeWindowsCheckbox' checked/> Freeze windows";
		else
			fw = "<input type='checkbox' id='freezeWindowsCheckbox'/> Freeze windows";

		var ll_upload_own = `
    <form action="upload_layout.php" method="post" enctype="multipart/form-data"><center>
        <b>Choose file:</b><br /><br />
        <input type="file" name="fileToUpload" id="fileToUpload"><br />
        <input title="Send layout" value="Send" type="submit" name="submit" class="btn btn-success"></center>
    </form>`;

		var ll_options = "";

		ll_options += `<option value="` + selected_layout + `">` + selected_layout + `</option>`;

		for (var i = 0; i < layout_list.length; i++) {
			if (layout_list[i] !== selected_layout)
				ll_options += `<option value="` + layout_list[i] + `">` + layout_list[i] + `</option>`;
		}
		ll = `
    <br />
    <b>Layout:</b> <select name="layouts" onchange="setLayout($(this).val()); saveMains();">
      ` + ll_options + `
    </select> <span id="ll_layout_download" title="Download selected layout" class="clickable glyphicon glyphicon-download-alt" aria-hidden="true"></span> 
    <span id="ll_layout_upload" title="Upload custom layout" class="clickable glyphicon glyphicon-open" aria-hidden="true"></span>
    <br>`;

		var cont = pc + ll; // + fw -- freeze windows;

		Alert("Settings", cont);

		$("#ll_layout_download").click(function() {
			download(selected_layout + ".txt", JSON.stringify(layout));
		});

		$("#ll_layout_upload").click(function() {
			closeAlert();

			setTimeout(function() {
				Alert('Upload custom layout', ll_upload_own);
			}, 500);
		});

		$('#printCommandsCheckbox').click(function() { // freeze windows TODO
			if (this.checked) {
				printCommands = true;
			}
			if (this.checked === false) {
				printCommands = false;
			}
			saveMains();
		});
		$('#freezeWindowsCheckbox').click(function() {
			if (this.checked) {
				freezeWindows = true;
			}
			if (this.checked === false) {
				freezeWindows = false;
			}
		});
	}
}

function escapeHTML(html) {
	return html
		.replace(/&/g, "&amp;")
		.replace(/</g, "&lt;")
		.replace(/>/g, "&gt;")
		.replace(/"/g, "&quot;")
		.replace(/'/g, "&#039;");
}

function saveMains() {
	var object = {
		"fcID": focusedConsoleID,
		"layout_name": selected_layout,
		"printCommands": printCommands
	}; // ... setting etc

	AJAX("saveMains", JSON.stringify(object));
}

function loadMains() {
	$.when(AJAX("getMains", "", "JSON")).done(function(response) {
		if (response.fcID != null)
			focusedConsoleID = response.fcID;
		else
			focusedConsoleID = null;

		if (response.layout_name != null) {
			setLayout(response.layout_name);
		}

		printCommands = response.printCommands;

		if (printCommands == null)
			printCommands = true;

		// ...
	});
}

function saveWindows() {
	var object = {};

	for (var i = 0; i < windows.length; i++) {
		var actObject = {
			"id": windows[i].id,
			"is": windows[i].is,
			"x": windows[i].x,
			"y": windows[i].y,
			"w": windows[i].w,
			"h": windows[i].h,
			"type": windows[i].constructor.name,
			"content": windows[i].content,
			"lang": windows[i].lang,
			"hidden": windows[i].hidden
		};

		if (windows[i].not_save !== true)
			object[i] = actObject;
	}

	object = JSON.stringify(object);

	AJAX("saveWindows", object);
}

function reloadOutputs() {
	for (var i = 0; i < windows.length; i++) {
		if (windows[i].reload_ === true) {
			windows[i].ReloadContent();
		}
	}
}

function loadWindows() {
	$.when(AJAX("getWindows", "", "JSON")).done(function(response) {
		var wins = $.map(response, function(el) {
			return el
		});

		for (var i = 0; i < wins.length; i++) {
			var type = wins[i].type;

			var last;

			eval("last = new " + type + "(0);");

			last.x = wins[i].x;
			last.y = wins[i].y;
			last.w = wins[i].w;
			last.h = wins[i].h;
			last.x = wins[i].x;
			last.id = wins[i].id;
			last.type = wins[i].type;
			last.content = wins[i].content;
			last.is = wins[i].is;
			last.lang = wins[i].lang;
			last.hidden = wins[i].hidden;

			windows.push(last);

			incrementID++;

			if (type === "Console") {
				increment_C_ID++;
				focusedConsoleID = 0;
			}
		}

		windowsReload();
		refreshHiddenWindows();
	});
}

function autoSave() {
	saveWindows();

	global._save();
	//storage._save();

	// ...

	setTimeout(autoSave, 10000);
}

function other(id, consoleID) {
	if (consoleID == null)
		consoleID = focusedConsoleID;

	var cons = new Array();

	for (var i = 0; i < windows.length; i++) {
		if (windows[i].constructor.name === "Console") {
			cons.push(windows[i]);
		}
	}

	var res;

	for (var i = 0; i < cons.length; i++) {
		if (cons[i].cID == id) {
			res = cons[i];

			break;
		}
	}

	if (res == null) {
		windows[consoleID].log("Console <span style='color: white;'>" + id + "</span> doesn't exist.", "red");

		return false;
	}

	if (res.is === false) {
		windows[consoleID].log("Console <span style='color: white;'>" + id + "</span> is closed.", "red");

		return false;
	}

	return res;
}

function refreshHiddenWindows() {
	$("#hidden_windows").html("");

	for (var i = 0; i < windows.length; i++) {
		if (windows[i].hidden == true) {
			var html = "";

			if (windows[i].type === "Console") {
				html = "<div id='hidden_" + windows[i].id + "' title='Console' class='clickable notFullVisible consoleLayout' onclick='windows[" + windows[i].id + "].show()' style='width: 60px; height: 35px; background: black; border: 1px solid white; float: left; margin-left: 10px;'>&gt&gt&nbsp</div>";
			} else if (windows[i].type === "VariablesWindow") {
				html = "<div id='hidden_" + windows[i].id + "' title='Variables' class='clickable notFullVisible variablesLayout' onclick='windows[" + windows[i].id + "].show()' style='width: 60px; height: 35px; background: black; border: 1px solid white; float: left; margin-left: 10px;'>x, y&nbsp</div>";
			} else if (windows[i].type === "StorageWindow") {
				html = "<div id='hidden_" + windows[i].id + "' title='Storage' class='clickable notFullVisible storageLayout' onclick='windows[" + windows[i].id + "].show()' style='width: 60px; height: 35px; background: black; border: 1px solid white; float: left; margin-left: 10px;'><span style='font-size: 90%; margin-top: 3px;' class='glyphicon glyphicon-folder-open' aria-hidden='true'></span>&nbsp</div>";
			} else if (windows[i].type === "EditorWindow") {
				html = "<div id='hidden_" + windows[i].id + "' title='Editor' class='clickable notFullVisible' onclick='windows[" + windows[i].id + "].show()' style='width: 60px; height: 35px; background: black; color: white; border: 1px solid white; float: left; margin-left: 10px;'>&lt&gt&nbsp</div>";
			}

			$("#hidden_windows").append(html);
		}
	}
	$("#hidden_windows").hide().fadeIn(1000);
}

function closeAll() {
	for (var i = 0; i < windows.length; i++) {
		windows[i].close();
	}

	incrementID = 0;
	increment_C_ID = 0;

	windows = [];

	$("#hidden_windows").empty();

	windowsReload();
}

function strEvalShow(att) {
	strEvalShow_ = att;
}

function Alert(title, content, buttons) {

	$("#alert_title").html(title);

	$("#alert_content").html(content);

	if (buttons != null) {
		$("#alert_plus_buttons").html(buttons);
	} else {
		$("#alert_plus_buttons").html("");
	}

	$('#alert_modal').modal('show');
}

function closeAlert() {
	$('#alert_modal').modal('hide');
}

function Prompt(title, x, placeholder) {
	Alert(title, `<textarea style="max-width: 100%; min-width: 100%; min-height: 200px;" id="textarea">` + placeholder + `</textarea>`, `<button type="button" class="btn btn-default" onclick="` + x + ` = $('#textarea').val()" data-dismiss="modal">Save</button>`);
}

function ps(consoleID){ // active processes
	if (consoleID == null)
		consoleID = focusedConsoleID;
	
	var p = [];
	var p_string = "";
	for(var i = 0; i < windows.length; i++){
		if(windows[i].is == true){
			p.push(i);
			p_string += i + " " + windows[i].type;
			
			if(windows[i].hidden)
				p_string += " hidden";
			
			p_string += "<br />";
		}
	}
	
	p_string = p_string.substring(0, p_string.length - "<br />".length); // remove last <br />
	
	windows[consoleID].log("Active processes ID: ", "#62ff07"); // #62ff07 == light green
	windows[consoleID].log(p_string);
	windows[consoleID].log("(windows[ID])", "yellow");
}

function help(x, consoleID) {
	if (consoleID == null)
		consoleID = focusedConsoleID;
	
	var win = windows[consoleID];
	
	if(x != null && x != ""){
		if(x == "app"){
			
		}
		else{
			win.log("Sorry, no help for that.", "yellow");
		}
		
		return false;
	}

	var help = "help / help()          |   display this message" + "<br />";
	help += "/ text                 |   comment" + "<br />";
	help += "---------" + "<br />";
	help += ">file                  |   run script from a file" + "<br />";
	help += ">@var                  |   run script from a global variable" + "<br />";
	help += "ps()                   |   active processes IDs" + "<br />";
	help += "history                |   command history" + "<br />";
	help += "---------" + "<br />";
	help += "@@                     |   this console" + "<br />";
	help += "@@.info(obj)           |   print info about obj" + "<br />";
	help += "@@.state()             |   console state" + "<br />";
	help += "@@.log('text')         |   print text" + "<br />";
	help += "@@.createCustomWindow(name)   --   custom window" + "<br />";
	help += "---------" + "<br />";
	help += "global                 |   global variables storage (register)" + "<br />";
	help += "global.set(key, val)   |   set a variable" + "<br />";
	help += "global.list()          |   list variables" + "<br />";
	help += "global.delete(key)     |   delete a variable" + "<br />";
	help += "global.print(key)      |   print a variable" + "<br />";
	help += "global.alert(text)     |   fire an alert" + "<br />";
	help += "---------" + "<br />";
	help += "storage                |   file storage" + "<br />";
	help += "storage.list()         |   list files" + "<br />";
	help += "storage.new('n.ex')    |   create a new file" + "<br />";
	help += "storage.delete('n.ex') |   delete a file" + "<br />";
	help += "storage.file('n.ex')   |   get file content" + "<br />";
	help += "storage.print('n.ex')  |   print file content" + "<br />";
	help += "storage.open('n.ex')   |   open a file" + "<br />";
	help += "storage.eval('n.ex')   |   run a file as a command" + "<br />";
	help += "---------" + "<br />";
	help += "web                    |   access the web" + "<br />";
	help += "web.open(url)          |   open URL" + "<br />";
	help += "web.gethtml(url)       |   get HTML of the page" + "<br />";
	help += "web.send(...)          |   send AJAX request" + "<br />";
	help += "escapeHTML(html)       |   escape HTMl special chars";

	win.log("=== HELP ===", "#62ff07"); // #62ff07 == light green
	win.log(help);
	win.log("For more methods use @@.info(obj).", "yellow");
	win.log("For specific help use help(x).", "yellow");
}

Function.prototype.clone = function() {
    var that = this;
    var temp = function temporary() { return that.apply(this, arguments); };
    for(var key in this) {
        if (this.hasOwnProperty(key)) {
            temp[key] = this[key];
        }
    }
    return temp;
};