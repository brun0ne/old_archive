#include "main.h"

// Main_Missile CLASS ->

void main_missile::init(){
	int first_load;
	App::readFromFile("DATA/never.save", first_load);

	if(first_load == 1){
		power = 1;
		im = -777;
		name = "Pocisk_Poczatkujacego";
		url = "poczatkowy";
		std::string pom = "Grafika/Gra/Default/Pociski/" + url + ".bmp";
		bmp = load_bmp(pom.c_str(), default_palette);
		save();
	}
	else
	{
		read();

		std::string pom = "Grafika/Gra/Default/Pociski/" + url + ".bmp";
		bmp = load_bmp(pom.c_str(), default_palette);
	}
}

void main_missile::update(){
	textprintf_ex(bufor, font, 698, 105, makecol(0, 0, 0), -1, "Pocisk:");
	App::drawBITMAP(bmp, 700, 130, 50, 50);

	if(App::onSlide(700, 130, 50, 50)){
		if(name != "")
			stretch_sprite( eq::popUpbufor, eq::button_d, mouse_x - (75 + name.size() * 8), mouse_y, 75 + ( name.size() * 8 ), 35 );
		else
			stretch_sprite( eq::popUpbufor, eq::button_d, mouse_x - 150, mouse_y, 150, 35 );

		if(name != "")
			textprintf_ex(eq::popUpbufor, font, mouse_x - (70 + name.size() * 8), mouse_y + 5, makecol(255, 255, 255), -1, "Pocisk: %s", name.c_str());
		else
			textprintf_ex(eq::popUpbufor, font, mouse_x - 150, mouse_y + 5, makecol(255, 255, 255), -1, "Pocisk: BRAK");
		if(name != "")
			textprintf_ex(eq::popUpbufor, font, mouse_x - (70 + name.size() * 8), mouse_y + 15, makecol(255, 255, 255), -1, "+ do AP: %d", power);
	}
	if(im != -777){
		App::drawVariableText("", 700 + 1, 130 + 50 - 8, im, 1);
	}
	else if(im == -777){
		App::drawText("UNL", 700 + 1, 130 + 50 - 8);
	}

	if(im <= 0 && im != -777){
		set(0, "", "default", NULL, -1);
	}
}

void main_missile::set(int _power, std::string _name, std::string _url, BITMAP * _bmp, int _im){
	power = _power;
	name = _name;
	bmp = _bmp;
	url = _url;
	im = _im;

	if(bmp == NULL){
		std::string pom = "Grafika/Gra/Default/Pociski/" + url + ".bmp";
		bmp = load_bmp(pom.c_str(), default_palette);
	}

	if(url != ""){
		missile1.bmp = bmp;
		missile2.bmp = bmp;
	}
}

void main_missile::save(){
	App::saveToFile("DATA/MainMissile/power.save", power);
	App::saveToFile("DATA/MainMissile/im.save", im);
	
	std::ofstream nameFile, urlFile;

	nameFile.open("DATA/MainMissile/name.save");
	urlFile.open("DATA/MainMissile/graphUrl.save");

	nameFile << name;
	urlFile << url;
}

void main_missile::read(){
	App::readFromFile("DATA/MainMissile/power.save", power);
	App::readFromFile("DATA/MainMissile/im.save", im);

	std::ifstream nameFile, urlFile;

	nameFile.open("DATA/MainMissile/name.save");
	urlFile.open("DATA/MainMissile/graphUrl.save");

	nameFile >> name;
	urlFile >> url;
}