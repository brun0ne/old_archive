function ChangeCenter(what){
  if(what == null || what == "" || what == 0){
    return;
  }
  else {
    var xmlhttp = new XMLHttpRequest();
        xmlhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
                document.getElementById("centerPage_content").innerHTML = this.responseText;
            }
        };
        xmlhttp.open("GET", "getCenterSite.php?what=" + what, true);
        xmlhttp.send();
  }
}