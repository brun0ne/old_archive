var ajax_debug = false;

function AJAX(action, content, type){
  if(type == null)
    type = "text";
  
  return $.ajax({
    type: "POST",
    url: "server.php",
    data: {action: action, arg: content},
    dataType: type,
    success: function(response){
      // ...
      
      if(ajax_debug)
        console.log(response);
      
      if(response === "session expired"){
        window.location.assign("../index.php?msg=" + response);
      }
    },
    error: function(data){
      console.log("ERROR");
      console.log(data);
    }
  });
}