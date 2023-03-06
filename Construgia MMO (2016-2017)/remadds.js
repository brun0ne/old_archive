window.onload = function init() {
    setTimeout(function() {
        var p = document.body;
        var toRemove = 2;
        for (var i = 0; i < toRemove; i++) {
           if(p.childNodes[i].tagName == 'DIV') {
               p.removeChild(p.childNodes[i]);
           }
        }
    }, 5); 
}