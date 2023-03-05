#include "main.h"

World::World(int _plane_h, int _spawnData)
{
	plane_h = _plane_h; 
	spawnData = _spawnData;
	speed = -5;
	isScreenScroll = true;
	speedPh = 1 - speed;
}

void World::Update(BITMAP * main_bg, BITMAP * plus_bg){
	Draw(main_bg, plus_bg);
	Collisions();
}

void World::Draw(BITMAP * main_bg, BITMAP * plus_bg){
	App::drawBITMAP(main_bg, 0, 600 - plane_h, 800, plane_h);
	App::drawBITMAP(plus_bg, plus_bg_x, 600 - plane_h, 800, plane_h);
	App::drawBITMAP(plus_bg, plus_bg_x+800, 600 - plane_h, 800, plane_h);
}

void World::Collisions(){
	if(player.y <= ( 600 - world.plane_h - ( player.h / 2 ) ) ) {
		player.y = ( 600 - world.plane_h - ( player.h / 2 ) );
	}
	if( ( player.y + player.h ) >= 600 ) {
		player.y = 600 - player.h;
	}
	if(isScreenScroll == false){
		if(player.x + player.w >= 800)
			player.x = 800 - player.w;
		if(player.x <= 0)
			player.x = 0;
	}
}