#include "main.h"

#include "MoveToPoint.h"

MoveToPoint::MoveToPoint(){
	x = 0;
	y = 0;

	timer = -1;

	active = false;
}

void MoveToPoint::Init(){
	bmp = load_bmp("Grafika/Gra/Default/ground_point.bmp", default_palette);
}

void MoveToPoint::Create(){
	x = mouse_x - 25;

	if(mouse_y > 600 - world.plane_h)
		y = mouse_y - 25;
	else
		y = 600 - world.plane_h - 20;

	active = true;
	timer = 20;
}

void MoveToPoint::SetColor(){}

void MoveToPoint::Draw(){
	if(timer >= 0)
		App::drawBITMAP(bmp, x, y, 50, 50);
}

void MoveToPoint::Logic(){
	if(world.isScreenScroll){
		if(player.x > x){
			player.camera.x -= 1 - world.speed;
			player.rot = "left";
			x += 1 - world.speed;

			if(world.plus_bg_x <= 0)
				world.plus_bg_x += ( 1 - world.speed );
			else
				world.plus_bg_x = -1000;
		}
		if(player.x < x){
			player.camera.x += 1 - world.speed;
			player.rot = "right";
			x -= 1 - world.speed;

			if(world.plus_bg_x >= -1000)
				world.plus_bg_x -= ( 1 - world.speed );
			else
				world.plus_bg_x = 0;
		}
	}
	else
	{
		if(player.x > x)
			player.x -= 1 - world.speed;
		if(player.x < x)
			player.x += 1 - world.speed;
	}

	if(player.x >= x - 10 && player.x <= x + 10 && player.y > y){
		player.y -= 1 - world.speed;
		player.rot = "up";
	}
	if(player.x >= x - 10 && player.x <= x + 10 && player.y < y){
		player.y += 1 - world.speed;
		player.rot = "down";
	}

	if(player.x >= x - 10 && player.x <= x + 10 && player.y >= y - 10 && player.y <= y + 10)
		active = false;

	if(key[KEY_LEFT] || key[KEY_RIGHT] || key[KEY_UP] || key[KEY_DOWN] || key[KEY_A] || key[KEY_D] || key[KEY_W] || key[KEY_S])
		active = false;

	if(timer >= 0)
		timer--;
}

void MoveToPoint::Listen(){
	if(mouse_b == 1 && mouse_x < 800 - 150 && world.speed != 1)
		Create();
}

void MoveToPoint::Update(){
	if(active){
		Logic();
		Draw();
	}
	Listen();
}