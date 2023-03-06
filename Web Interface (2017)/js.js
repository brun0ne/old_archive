var reglog = 0
var regchange = false;

$(document).ready(function(){
  $("body").animate({ opacity: 1 }, 1200);
});

function registerToggle(){
  if(reglog === 0 && regchange === false){
    $("#login_form").hide(1000);
    regchange = true;
    
    setTimeout(function(){
      $("#register_form").show(1000);
    }, 1000);
    
    setTimeout(function(){
      $("#register_login_button").html("log in");
      $("#register_login_button").css("margin-left", "-1%");
      
      regchange = false;
    }, 2000)
    
    reglog = 1;
  }
  else if(reglog === 1 && regchange === false){
    $("#register_form").hide(1000);
    regchange = true;
    
    setTimeout(function(){
      $("#login_form").show(1000);
    }, 1000);
    
    setTimeout(function(){
      $("#register_login_button").html("register me");
      $("#register_login_button").css("margin-left", "-2.1%");
      
      regchange = false;
    }, 2000)
    
    reglog = 0;
  }
}