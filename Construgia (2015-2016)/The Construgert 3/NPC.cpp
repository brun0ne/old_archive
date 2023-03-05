#include "main.h"

npc::npc(std::string _name, int _x, int _y, int _w, int _h, int _lvl){
	x = _x; y = _y; w = _w; h = _h; lvl = _lvl; name = _name;

	for(int i = 4; i >= 0; i--)
		event_[i] = 0;

	active = false;
}

void npc::start(std::string bmp_link){
	bmp = load_bmp(bmp_link.c_str(), default_palette);
}

void npc::on(){
	active = true;
	world.speed = 1;
	eq::is = false;
}

void npc::off(){
	active = false;
	eq::is = true;
	world.speed = -5;

	event_[0] = 0;
}

void npc::update(){
	draw();
	logic();
	listen();
}

void npc::draw(){
	if(world.isScreenScroll){
		App::drawBITMAP(bmp, x - player.camera.x, y, w, h);
		textprintf_ex(bufor, font, x - player.camera.x, y - 20, makecol(0, 0, 0), -1, "%s", name.c_str());
		App::drawVariableText("Lvl: ", x - player.camera.x, y - 10, lvl, -1);
	}
	else{
		App::drawBITMAP(bmp, x, y, w, h);
		textprintf_ex(bufor, font, x, y - 20, makecol(0, 0, 0), -1, "%s", name.c_str());
		App::drawVariableText("Lvl: ", x, y - 10, lvl, -1);
	}
}

void npc::logic(){
	if(world.isScreenScroll)
		App::Player_Collision(x - player.camera.x, y, w, h);
	else
		App::Player_Collision(x, y, w, h);

	if(dTimer >= 0)
		dTimer--;
}

void npc::listen(){
	if(world.isScreenScroll){
		if(App::onClick(x - player.camera.x, y, w, h)){
			on();
			world.speed = 1;
		}
	}
	else
	{
		if(App::onClick(x, y, w, h)){
			on();
			world.speed = 1;
		}
	}
	if(active && key[KEY_ESC] && runTimer <= 0){
		off();
		runTimer = 100;
	}
}