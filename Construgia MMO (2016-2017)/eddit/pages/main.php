
<div id="slider1" class="content center font-mont">
  <img src="b4.jpg" id="slider1_bg" />
  <img src="b3.jpg" id="slider2_bg" />
  <span id="slide1" class="big-font" style="position: absolute; bottom: 2%; left: 2%;">
    &nbsp&nbsp Ty nagrywasz film...<br /><br />
  </span>
  <span id="slide2" class="big-font" style="position: absolute; bottom: 2%; right: 2%; display: none;">
    ...my go dla Ciebie montujemy!&nbsp&nbsp<br /><br />
  </span>
</div>
<div class="content center font-ubuntu" style="margin-top: 35%; font-size: 120%">
  <br />
  M
</div>

<script>
  var slide = 1;
  
  function slideChange(){
    if(slide){
      $("#slide1").hide("slide", {direction : "left"}, 200);
      
      setTimeout(function(){
        $("#slide2").fadeIn();
      }, 550);
      
      slide = 0;
      $("#slider1_bg").hide("slide", {direction : "left"}, 500);
      $("#slider2_bg").show("slide", {direction : "right"}, 500);
    }
    else{
      $("#slide2").hide("slide", {direction : "right"}, 200);
      
      setTimeout(function(){
        $("#slide1").fadeIn();
      }, 550);
      
      slide = 1;
      
      $("#slider2_bg").hide("slide", {direction : "right"}, 500);
      $("#slider1_bg").show("slide", {direction : "left"}, 500);
    }
    
    setTimeout("slideChange()", 3000);
  }
  
  $(document).ready(function() {
    setTimeout("slideChange()", 3000);
  });
</script>