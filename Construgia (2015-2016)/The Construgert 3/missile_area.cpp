#include "main.h"

// Missile_Area CLASS ->

void missile_area::init(int _x, int _y, std::string _save_url){
	int first = 0;
	App::readFromFile("DATA/never.save", first);

	save_url = _save_url;

	if(first == 1){
		power = 0;
		name = "";
		type = 1;
		healt = 0;
		bmp = load_bmp("Grafika/Gra/Default/eqArea.bmp", default_palette);

		save();
	}
	else
	{
		read();

		if(url == "")
			bmp = load_bmp("Grafika/Gra/Default/eqArea.bmp", default_palette);
		else
		{
			std::string pomUrl = "Grafika/Gra/Default/Pociski/" + url + ".bmp";
			bmp = load_bmp(pomUrl.c_str(), default_palette);
		}
	}

	x = _x;
	y = _y;
}

void missile_area::update(){
	draw();
	logic();
}

void missile_area::draw(){
	App::drawBITMAP(bmp, x, y, 50, 50);
}

void missile_area::logic(){
	if(eq::delWork == false){
		if(type == 0){
			if(App::onClick(x, y, 50, 50) && runTimer <= 0){
				BITMAP * pomB = bmp;
				int pomI = power;
				int pomIm = im;
				std::string pomS = name;
				std::string pomS2 = url;

				if(eq::Main_Missile.name != ""){
					set(eq::Main_Missile.name, eq::Main_Missile.url, eq::Main_Missile.power, 0, false, 0, eq::Main_Missile.im); 
					bmp = eq::Main_Missile.bmp;
				}
				else
				{
					erase();
				}

				eq::Main_Missile.set(pomI, pomS, pomS2, pomB, pomIm);

				missile1.bmp = eq::Main_Missile.bmp;
				missile2.bmp = eq::Main_Missile.bmp;

				runTimer = 35;
			}
			if(App::onSlide(x, y, 50, 50)){
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
				App::drawVariableText("", x + 1, y + 50 - 8, im, 1);
			}
			else if(im == -777){
				App::drawText("UNL", x + 1, y + 50 - 8);
			}
		}
		else if(type == 1){
			if(App::onSlide(x, y, 50, 50)){
				if(name != "")
					stretch_sprite( eq::popUpbufor, eq::button_d, mouse_x - (75 + name.size() * 8), mouse_y, 75 + ( name.size() * 8 ), 35 );
				else
					stretch_sprite( eq::popUpbufor, eq::button_d, mouse_x - 150, mouse_y, 150, 35 );

				if(name != "")
					textprintf_ex(eq::popUpbufor, font, mouse_x - (70 + name.size() * 8), mouse_y + 5, makecol(255, 255, 255), -1, "Przedmiot: %s", name.c_str());
				else
					textprintf_ex(eq::popUpbufor, font, mouse_x - 150, mouse_y + 5, makecol(255, 255, 255), -1, "Przedmiot: Brak");
			}
		}
		if(type == 2){
			if(App::onClick(x, y, 50, 50) && runTimer <= 0){
				player.hp += healt;
				erase();
				runTimer = 25;
			}
			if(App::onSlide(x, y, 50, 50)){
				if(name != "")
					stretch_sprite( eq::popUpbufor, eq::button_d, mouse_x - (100 + name.size() * 8), mouse_y, 100 + ( name.size() * 8 ), 35 );
				else
					stretch_sprite( eq::popUpbufor, eq::button_d, mouse_x - 150, mouse_y, 150, 35 );

				if(name != ""){
					textprintf_ex(eq::popUpbufor, font, mouse_x - (100 + name.size() * 8), mouse_y + 5, makecol(255, 255, 255), -1, "Jedzenie: %s", name.c_str());
					textprintf_ex(eq::popUpbufor, font, mouse_x - (100 + name.size() * 8), mouse_y + 15, makecol(255, 255, 255), -1, "+HP: %d", healtD);
				}
				else
					textprintf_ex(eq::popUpbufor, font, mouse_x - 150, mouse_y + 5, makecol(255, 255, 255), -1, "Jedzenie: Brak [JEZELI TO WIDZISZ TO BLAD]");
			}
		}
		if(type == 3){
			if(App::onClick(x, y, 50, 50)){
				erase();
				Opening::lvl = healtD;
				runTimer = 25;
				Opening::PushToEq();
			}
			if(App::onSlide(x, y, 50, 50)){
				if(name != "")
					stretch_sprite( eq::popUpbufor, eq::button_d, mouse_x - (100 + name.size() * 8), mouse_y, 150 + ( name.size() * 8 ), 35 );
				else
					stretch_sprite( eq::popUpbufor, eq::button_d, mouse_x - 150, mouse_y, 200, 35 );

				if(name != ""){
					textprintf_ex(eq::popUpbufor, font, mouse_x - (100 + name.size() * 8), mouse_y + 5, makecol(255, 255, 255), -1, "Przedmiot: %s", name.c_str());
					textprintf_ex(eq::popUpbufor, font, mouse_x - (100 + name.size() * 8), mouse_y + 15, makecol(255, 255, 255), -1, "Tajemnicza skrzynia... Co zawiera?", name.c_str());
				}
			}
		}
		if(type == 4){
			if(App::onSlide(x, y, 50, 50)){
				stretch_sprite( eq::popUpbufor, eq::button_d, mouse_x - (100 + name.size() * 8), mouse_y, 150 + ( name.size() * 8 ), 35 );

				textprintf_ex(eq::popUpbufor, font, mouse_x - (100 + name.size() * 8), mouse_y + 5, makecol(255, 255, 255), -1, "Przedmiot: %s", name.c_str());
				textprintf_ex(eq::popUpbufor, font, mouse_x - (100 + name.size() * 8), mouse_y + 15, makecol(255, 255, 255), -1, "Przedmiot niezidentyfikowany", name.c_str());
			}
		}
	}
	else{
		if(App::onClick(x, y, 50, 50) && name != "Pocisk_Poczatkujacego" && runTimer <= 0){
			if(name == "'Prawo,_lewo,_324.'_Coz_to_moze_znaczyc?"){
				eq::filons_paper = 0;
				App::saveToFile("DATA/Other/filons_paper.save", 0);
			}

			erase();
		}
	}
}

void missile_area::set(std::string _name, std::string _url, int _power, int _healt, bool graph, int _type, int _im){
	name = _name;
	power = _power;
	healt = _healt;
	type = _type;
	url = _url;
	im = _im;

	if(healtD != healt)
		healtD = healt;

	if(graph){
		std::string pomUrl;
		pomUrl = "Grafika/Gra/Default/Pociski/" + url + ".bmp";
		bmp = load_bmp(pomUrl.c_str(), default_palette);
	}
}

void missile_area::erase(){
	power = 0;
	type = 1;
	name = "";
	url = "";
	bmp = load_bmp("Grafika/Gra/Default/eqArea.bmp", default_palette);
}

void missile_area::save(){
	std::string powU, tyU, hedU, heU, urU, naU, imU;

	powU = save_url + "/power.save";
	tyU = save_url + "/type.save";
	hedU = save_url + "/healtD.save";
	heU = save_url + "/healt.save";
	urU = save_url + "/graphics_url.save";
	naU = save_url + "/name.save";
	imU = save_url + "/im.save";

	App::saveToFile(powU.c_str(), power);
	App::saveToFile(tyU.c_str(), type);
	App::saveToFile(hedU.c_str(), healtD);
	App::saveToFile(heU.c_str(), healt);
	App::saveToFile(imU.c_str(), im);

	std::ofstream g_url;
	g_url.open(urU.c_str());
	g_url << url;

	std::ofstream nameFile;
	nameFile.open(naU.c_str());
	nameFile << name;
}

void missile_area::read(){
	std::string powU, tyU, hedU, heU, urU, naU, imU;

	powU = save_url + "/power.save";
	tyU = save_url + "/type.save";
	hedU = save_url + "/healtD.save";
	heU = save_url + "/healt.save";
	urU = save_url + "/graphics_url.save";
	naU = save_url + "/name.save";
	imU = save_url + "/im.save";

	App::readFromFile(powU, power);
	App::readFromFile(tyU, type);
	App::readFromFile(hedU, healtD);
	App::readFromFile(imU, im);
	
	std::fstream healtFile;
	healtFile.open(heU);
	healtFile >> healt;

	std::fstream graphUrlFile;
	graphUrlFile.open(urU);
	graphUrlFile >> url;

	std::fstream nameFile;
	nameFile.open(naU);
	nameFile >> name;
}