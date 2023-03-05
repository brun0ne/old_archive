#include "main.h"

Missile::Missile(){
	is = false;
}

void Missile::init(){
	int first;
	App::readFromFile("DATA/never.save", first);

	if(first == 1)
		Load("poczatkowy");
	else
	{
		eq::Main_Missile.read();
		Load(eq::Main_Missile.url);
	}
}

void Missile::Create(int _x, int _y, int _w, int _h, int _power, std::string _goTo){
	x = _x;
	y = _y;
	w = _w;
	h = _h;
	power = _power;
	goTo = _goTo;

	is = true;
}

void Missile::Load(std::string url){
	std::string myUrl = "Grafika/Gra/Default/Pociski/" + url + ".bmp";
	bmp = load_bmp(myUrl.c_str(), default_palette);
}

void Missile::Update(int speed){
	if(is){
		if(speed == 0)
			speed = power * 2; // Tymczasowe
		Draw();
		Logic(speed);
	}
}

void Missile::Destroy(){
	is = false;
}

void Missile::Draw(){
	App::drawBITMAP(bmp, x + ( player.w / 4 ), y + ( player.h / 4 ), w, h);
}

void Missile::Logic(int speed){
	if(lifeTime >= 0)
		lifeTime--;

	if(goTo == "down")
		y += ( 1 - world.speed);
	if(goTo == "up")
		y -= ( 1 - world.speed );
	if(goTo == "left")
		x -= ( 1 - world.speed );
	if(goTo == "right")
		x += ( 1 - world.speed );
	////////////////////////
	if(y <= ( 600 - world.plane_h ) - ( h + ( h / 3 ) ) ) {
		Destroy();
	}
	if( ( y + h ) >= 600 ) {
		Destroy();
	}
	if( x <= 0 ) {
		Destroy();
	}
	if( x >= 800 ) {
		Destroy();
	}
	if(lifeTime <= 0){
		Destroy();
	}
}