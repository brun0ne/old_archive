function validateChat(){
  var x = document.forms["form_chat"]["text_"].value;
  
  AJAX_chatWrite(x);
  
  document.forms["form_chat"].reset();
  
  return false;
}

// 15:34, 16 grudnia 2016r - PIERWSZA wiadomosc wyslana w swiecie Construgia