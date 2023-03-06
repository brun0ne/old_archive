var contextMenuVIS = false;

function contextMenuUpdate(e){
  if(contextMenuVIS === true){
    if(e.pageX < $(window).width() - $("#context_menu").width() - 10){
      $("#context_menu").css({"left" : e.pageX});
      $("#pop_1").css({"left" : "100%"});
    }
    else{
      $("#context_menu").css({"left" : (e.pageX - $("#context_menu").width() - 5)});
      $("#pop_1").css({"left" : "-101%"});
    }
    
    if(e.pageY > $(window).height() - $("#context_menu").height() - 10){
      $("#context_menu").css({"top" : e.pageY - $("#context_menu").height() - 15});
      $("#pop_1").css({"top" : "-150%"});
    }
    else{
      $("#context_menu").css({"top" : e.pageY}); 
      $("#pop_1").css({"top" : "0"});
    }
    
    $("#context_menu").show(200);
  }
  else if(contextMenuVIS === false){
    $("#context_menu").hide(200);
  }
}

$(document).contextmenu(function(e){
  if(e.target.className !== "nocustomcm"){
    e.preventDefault();

    contextMenuVIS = true;

    contextMenuUpdate(e);
  }
});

$(document).mousedown(function(e){
  if(e.which === 1){
    var element = e.target.nodeName;
    
    if(element !== "A" && element !== "LI"){
      contextMenuVIS = false;

      contextMenuUpdate(e);
    }
    else{
      setTimeout(function(){
        contextMenuVIS = false;
        
        contextMenuUpdate(e);
      }, 100);
    }
  }
});