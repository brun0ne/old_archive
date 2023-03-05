#include "main.h"

Item::Item(int _x, int _y, int _w, int _h, int _type, int _gold, int _exp, std::string _name, std::string _url){
	x = _x;
	y = _y;
	w = _w;
	h = _h;
	name = _name;
	type = _type;
	url = _url;
	is = true;
	gold = _gold;
	exp = _exp;
}

void Item::Init(){
	std::string nUrl;
	nUrl = "Grafika/Gra/Default/Pociski/" + url + ".bmp";
	bmp = load_bmp(nUrl.c_str(), default_palette);
}

void Item::Draw(){
	if(world.isScreenScroll)
		App::drawBITMAP(bmp, x - player.camera.x, y, w, h);
	else
		App::drawBITMAP(bmp, x, y, w, h);
}

void Item::Logic(){
	if(App::onClick(x - player.camera.x, y, w, h) || (player.x >= (x - w - player.camera.x) && player.x <= (x - player.camera.x) && player.y >= y - h && player.y <= y)){
		if(type == 0){
			player.exp += exp;
			player.gold += gold;
			is = false;
		}
		else if(type == 1){
			// CDN.
		}
	}
}

void Item::Update(){
	if(is){
		Draw();
		Logic();
	}
}