#include "ConCity_BrunonCave.h"
#include "ConCity_Zbrojownia.h"
#include "ConCity.h"
#include "Location_Tools.h"
#include "graphics.h"
#include "music.h"

BITMAP * BrunonCave::main_bg;
BITMAP * BrunonCave::plus_bg;
BITMAP * BrunonCave::mainWall;
int BrunonCave::camera_x_onEnter;

bool BrunonCave::is;

int BrunonCave::stalagX = 0;

//Mobs
Mob BrunonCave::mob1(1000, 350, 50, 50, 600, 1400, 35, -2, false, 200, 20, 5, 7, true, "");
Mob BrunonCave::mob2(1800, 415, 50, 50, 1400, 2200, 35, -2, false, 200, 20, 5, 7, true, "");
Mob BrunonCave::mob3(2500, 350, 50, 50, 2100, 2900, 35, -2, false, 200, 20, 5, 7, true, "");
Mob BrunonCave::mob4(3000, 300, 50, 50, 2600, 3400, 35, -2, true, 300, 25, 7, 10, true, "");
Mob BrunonCave::mob5(3500, 350, 50, 50, 3100, 3900, 35, -2, true, 300, 25, 7, 10, true, "");
Mob BrunonCave::mob6(4000, 400, 50, 50, 3600, 4400, 35, -2, true, 300, 25, 7, 10, true, "");

Mob BrunonCave::mob_1(-1000, 300, 50, 50, -1400, -600, 35, -2, false, 200, 20, 5, 7, true, "");
Mob BrunonCave::mob_2(-1600, 450, 50, 50, -2000, -1200, 35, -2, false, 200, 20, 5, 7, true, "");
Mob BrunonCave::mob_3(-2500, 500, 50, 50, -2900, -2100, 35, -2, false, 200, 20, 5, 7, true, "");
Mob BrunonCave::mob_4(-3000, 300, 50, 50, -3400, -2600, 35, -2, true, 300, 25, 7, 10, true, "");
Mob BrunonCave::mob_5(-3500, 350, 50, 50, -3900, -3100, 35, -2, true, 300, 25, 7, 10, true, "");
Mob BrunonCave::mob_6(-4000, 400, 50, 50, -4400, -3900, 35, -2, true, 300, 25, 7, 10, true, "");

void BrunonCave::GraphLoad(){
	mainWall = load_bmp("Grafika/Gra/Teren/Lokacje/ConCity/BrunonCave/mainWall.bmp", default_palette);

	mob1.Load("Grafika/Gra/Moby/robot1.bmp");
	mob2.Load("Grafika/Gra/Moby/robot1.bmp");
	mob3.Load("Grafika/Gra/Moby/robot1.bmp");
	mob4.Load("Grafika/Gra/Moby/robot1_ex.bmp");
	mob5.Load("Grafika/Gra/Moby/robot1_ex.bmp");
	mob6.Load("Grafika/Gra/Moby/robot1_ex.bmp");

	mob_1.Load("Grafika/Gra/Moby/robot1.bmp");
	mob_2.Load("Grafika/Gra/Moby/robot1.bmp");
	mob_3.Load("Grafika/Gra/Moby/robot1.bmp");
	mob_4.Load("Grafika/Gra/Moby/robot1_ex.bmp");
	mob_5.Load("Grafika/Gra/Moby/robot1_ex.bmp");
	mob_6.Load("Grafika/Gra/Moby/robot1_ex.bmp");
}

void BrunonCave::Load(std::string name){
	is = true;
	camera_x_onEnter = 0;

	std::string main_url = "Grafika/Gra/Teren/Lokacje/";

	std::string main_bg_url;
	std::string plus_bg_url;

	main_bg_url = main_url + name + "/main_bg.bmp";
	plus_bg_url = main_url + name + "/plus_bg.bmp";

	main_bg = load_bmp(main_bg_url.c_str(), default_palette);
	plus_bg = load_bmp(plus_bg_url.c_str(), default_palette);

	GraphLoad();
}

void BrunonCave::Mobs(){
	mob1.basicUpdate();
	mob2.basicUpdate();
	mob3.basicUpdate();
	mob4.basicUpdate();
	mob5.basicUpdate();
	mob6.basicUpdate();

	mob_1.basicUpdate();
	mob_2.basicUpdate();
	mob_3.basicUpdate();
	mob_4.basicUpdate();
	mob_5.basicUpdate();
	mob_6.basicUpdate();

	if(mob1.is){
		if(mob1.getDamage()){
			if(sprzedawca.event_[1] == 1 && actquest.name == "Quest_Sprzedawcy:_Zabij_kilka_potworow_z_jaskini.")
				actquest.a++;
			int caseis = ( std::rand() % 100 ) + 0;
			if(caseis >= 0 && caseis <= 100){
				eq::pushToArea("Kamienna Skrzynia", "st_case", 0, 0, 1, 3, 1);
			}
		}
	}
	if(mob2.is){
		if(mob2.getDamage()){
			if(sprzedawca.event_[1] == 1 && actquest.name == "Quest_Sprzedawcy:_Zabij_kilka_potworow_z_jaskini.")
				actquest.a++;
			int caseis = ( std::rand() % 100 ) + 0;
			if(caseis >= 35 && caseis <= 40){
				eq::pushToArea("Kamienna Skrzynia", "st_case", 0, 0, 1, 3, 1);
			}
		}
	}
	if(mob3.is){
		if(mob3.getDamage()){
			if(sprzedawca.event_[1] == 1 && actquest.name == "Quest_Sprzedawcy:_Zabij_kilka_potworow_z_jaskini.")
				actquest.a++;
			int caseis = ( std::rand() % 100 ) + 0;
			if(caseis >= 35 && caseis <= 40){
				eq::pushToArea("Kamienna Skrzynia", "st_case", 0, 0, 1, 3, 1);
			}
		}
	}
	if(mob4.is){
		if(mob4.getDamage()){
			if(sprzedawca.event_[1] == 1 && actquest.name == "Quest_Sprzedawcy:_Zabij_kilka_potworow_z_jaskini.")
				actquest.a++;
			int caseis = ( std::rand() % 100 ) + 0;
			if(caseis >= 35 && caseis <= 40){
				eq::pushToArea("Kamienna Skrzynia", "st_case", 0, 0, 1, 3, 1);
			}
		}
	}
	if(mob5.is){
		if(mob5.getDamage()){
			if(sprzedawca.event_[1] == 1 && actquest.name == "Quest_Sprzedawcy:_Zabij_kilka_potworow_z_jaskini.")
				actquest.a++;
			int caseis = ( std::rand() % 100 ) + 0;
			if(caseis >= 35 && caseis <= 40){
				eq::pushToArea("Kamienna Skrzynia", "st_case", 0, 0, 1, 3, 1);
			}
		}
	}
	if(mob6.is){
		if(mob6.getDamage()){
			if(sprzedawca.event_[1] == 1 && actquest.name == "Quest_Sprzedawcy:_Zabij_kilka_potworow_z_jaskini.")
				actquest.a++;
			int caseis = ( std::rand() % 100 ) + 0;
			if(caseis >= 35 && caseis <= 40){
				eq::pushToArea("Kamienna Skrzynia", "st_case", 0, 0, 1, 3, 1);
			}
		}
	}

	if(mob_1.is){
		if(mob_1.getDamage()){
			if(sprzedawca.event_[1] == 1 && actquest.name == "Quest_Sprzedawcy:_Zabij_kilka_potworow_z_jaskini.")
				actquest.a++;
			int caseis = ( std::rand() % 100 ) + 0;
			if(caseis >= 35 && caseis <= 40){
				eq::pushToArea("Kamienna Skrzynia", "st_case", 0, 0, 1, 3, 1);
			}
		}
	}
	if(mob_2.is){
		if(mob_2.getDamage()){
			if(sprzedawca.event_[1] == 1 && actquest.name == "Quest_Sprzedawcy:_Zabij_kilka_potworow_z_jaskini.")
				actquest.a++;
			int caseis = ( std::rand() % 100 ) + 0;
			if(caseis >= 35 && caseis <= 40){
				eq::pushToArea("Kamienna Skrzynia", "st_case", 0, 0, 1, 3, 1);
			}
		}
	}
	if(mob_3.is){
		if(mob_3.getDamage()){
			if(sprzedawca.event_[1] == 1 && actquest.name == "Quest_Sprzedawcy:_Zabij_kilka_potworow_z_jaskini.")
				actquest.a++;
			int caseis = ( std::rand() % 100 ) + 0;
			if(caseis >= 35 && caseis <= 40){
				eq::pushToArea("Kamienna Skrzynia", "st_case", 0, 0, 1, 3, 1);
			}
		}
	}
	if(mob_4.is){
		if(mob_4.getDamage()){
			if(sprzedawca.event_[1] == 1 && actquest.name == "Quest_Sprzedawcy:_Zabij_kilka_potworow_z_jaskini.")
				actquest.a++;
			int caseis = ( std::rand() % 100 ) + 0;
			if(caseis >= 35 && caseis <= 40){
				eq::pushToArea("Kamienna Skrzynia", "st_case", 0, 0, 1, 3, 1);
			}
		}
	}
	if(mob_5.is){
		if(mob_5.getDamage()){
			if(sprzedawca.event_[1] == 1 && actquest.name == "Quest_Sprzedawcy:_Zabij_kilka_potworow_z_jaskini.")
				actquest.a++;
			int caseis = ( std::rand() % 100 ) + 0;
			if(caseis >= 35 && caseis <= 40){
				eq::pushToArea("Kamienna Skrzynia", "st_case", 0, 0, 1, 3, 1);
			}
		}
	}
	if(mob_6.is){
		if(mob_6.getDamage()){
			if(sprzedawca.event_[1] == 1 && actquest.name == "Quest_Sprzedawcy:_Zabij_kilka_potworow_z_jaskini.")
				actquest.a++;
			int caseis = ( std::rand() % 100 ) + 0;
			if(caseis >= 35 && caseis <= 40){
				eq::pushToArea("Kamienna Skrzynia", "st_case", 0, 0, 1, 3, 1);
			}
		}
	}
}

void BrunonCave::On(){
	world.isScreenScroll = true;
	is = true; camera_x_onEnter = player.camera.x;
	App::setLight(100);
	App::setLightColor(0, 0, 0);

	// Muzyka

	stop_sample(music);
	music = dunger_th;
	play_sample( music, 255, 127, 750, 1 );
}

void BrunonCave::Off(){ // TU JEST PLAY_SAMPLE() !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	is = false;

	// Muzyka

	stop_sample(music);
	music = main_th;
	play_sample( music, 255, 127, 750, 1 );
}

void BrunonCave::Update(){
	if(is == true){
		App::drawBITMAP(mainWall, 0, 0, 800, 600 - world.plane_h);

		world.Update(main_bg, plus_bg);

		//Location Viev

		stretch_sprite(bufor, uglyStoneWall, 100 - stalagX, 0, 50, 50);
		stretch_sprite(bufor, uglyStoneWall, 300 - stalagX, 0, 50, 50);
		stretch_sprite(bufor, uglyStoneWall, 550 - stalagX, 0, 50, 50);

		if(player.camera.x < -5000){
			player.camera.x = -5000;
			world.plus_bg_x -= (1 - world.speed);
			stalagX += (1 - world.speed);
		}

		if(player.camera.x > 5000){
			player.camera.x = 5000;
			world.plus_bg_x += (1 - world.speed);
			stalagX -= (1 - world.speed);
		}

		if(key[KEY_LEFT])
			stalagX -= (1 - world.speed);
		if(key[KEY_RIGHT])
			stalagX += (1 - world.speed);

		if(stalagX <= -800)
			stalagX = 800;
		if(stalagX >= 1600)
			stalagX = -800;

		//Teleport -->
		if(LT::Dn_Enter(350, 100)){
			ConCity::On();
			Off();

			player.y = 600 - world.plane_h + 25; // 25 --> bezpieczna odleglosc od wejscia do budynku (teleportu)
			player.camera.x = 3150; // 3300 is x position of it ; 250 is 50% of building width
			player.rot = "down";
		}
		//<-- Teleport

		Mobs();
	}
}