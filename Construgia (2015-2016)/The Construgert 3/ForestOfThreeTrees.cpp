#include "ForestOfThreeTrees.h"
#include "FOTT_Zbrojownia.h"
#include "ConCity.h"
#include "Location_Tools.h"
#include "Volcano_.h"

#include "graphics.h"
#include "music.h"

bool FOTT::is;

BITMAP * FOTT::main_bg;
BITMAP * FOTT::plus_bg;
BITMAP * FOTT::background;

Mob FOTT::mob1(-4400, 300, 50, 50, -4500, -4300, 35, -1, true, 325, 26, 11, 11, true, "");
Mob FOTT::mob2(-4100, 400, 50, 50, -4900, -3500, 35, -1, true, 325, 26, 11, 11, true, "");
Mob FOTT::mob3(-3800, 250, 50, 50, -4000, -3700, 35, -1, true, 325, 26, 11, 11, true, "");
Mob FOTT::mob4(-3300, 500, 50, 50, -3700, -3000, 35, -1, false, 300, 25, 10, 9, true, "");
Mob FOTT::mob5(-2500, 400, 50, 50, -3000, -2000, 35, -1, false, 300, 25, 10, 9, true, "");
Mob FOTT::mob6(-1000, 300, 50, 50, -2000, -100, 35, -1, false, 300, 25, 10, 9, true, "");

void FOTT::GraphLoad(){
	background = load_bmp("Grafika/Gra/Teren/Lokacje/ForestOfThreeTrees/background.bmp", default_palette);
	mob1.Load("Grafika/Gra/Moby/forrestes_ex.bmp");
	mob2.Load("Grafika/Gra/Moby/forrestes_ex.bmp");
	mob3.Load("Grafika/Gra/Moby/forrestes_ex.bmp");
	mob4.Load("Grafika/Gra/Moby/forrestes.bmp");
	mob5.Load("Grafika/Gra/Moby/forrestes.bmp");
	mob6.Load("Grafika/Gra/Moby/forrestes.bmp");

	FOTT_Zbroj::Load("ForestOfThreeTrees/Zbrojownia");
	FOTT_Zbroj::Off();
}

void FOTT::Load(std::string name){
	is = true;

	std::string main_url = "Grafika/Gra/Teren/Lokacje/";

	std::string main_bg_url;
	std::string plus_bg_url;

	main_bg_url = main_url + name + "/main_bg.bmp";
	plus_bg_url = main_url + name + "/plus_bg.bmp";

	main_bg = load_bmp(main_bg_url.c_str(), default_palette);
	plus_bg = load_bmp(plus_bg_url.c_str(), default_palette);

	GraphLoad();
}

void FOTT::Mobs(){
	mob1.basicUpdate();
	mob2.basicUpdate();
	mob3.basicUpdate();
	mob4.basicUpdate();
	mob5.basicUpdate();
	mob6.basicUpdate();

	if(mob1.is){
		if(mob1.getDamage()){
			if(FOTT_Zbroj::sprzedawca.event_[1] == 1 && actquest.name == "Quest_Sprzedawcy:_Zabij_potwory_z_lasu.")
				actquest.a++;
			if(actquest.name == "Tajemnicza_Kartka" && actquest.text == "Zabij_12_potworow_dla_Leonarda.")
				actquest.a++;
			int caseis = ( std::rand() % 100 ) + 0;
			if(caseis >= 35 && caseis <= 37){
				eq::pushToArea("Drewniana Skrzynia", "wo_case", 0, 1, 1, 3, 1);
			}
		}
	}
	if(mob2.is){
		if(mob2.getDamage()){
			if(FOTT_Zbroj::sprzedawca.event_[1] == 1 && actquest.name == "Quest_Sprzedawcy:_Zabij_potwory_z_lasu.")
				actquest.a++;
			if(actquest.name == "Tajemnicza_Kartka" && actquest.text == "Zabij_12_potworow_dla_Leonarda.")
				actquest.a++;
			int caseis = ( std::rand() % 100 ) + 0;
			if(caseis >= 35 && caseis <= 38){
				eq::pushToArea("Drewniana Skrzynia", "wo_case", 0, 1, 1, 3, 1);
			}
		}
	}
	if(mob3.is){
		if(mob3.getDamage()){
			if(FOTT_Zbroj::sprzedawca.event_[1] == 1 && actquest.name == "Quest_Sprzedawcy:_Zabij_potwory_z_lasu.")
				actquest.a++;
			if(actquest.name == "Tajemnicza_Kartka" && actquest.text == "Zabij_12_potworow_dla_Leonarda.")
				actquest.a++;
			int caseis = ( std::rand() % 100 ) + 0;
			if(caseis >= 35 && caseis <= 38){
				eq::pushToArea("Drewniana Skrzynia", "wo_case", 0, 1, 1, 3, 1);
			}
		}
	}
	if(mob4.is){
		if(mob4.getDamage()){
			if(FOTT_Zbroj::sprzedawca.event_[1] == 1 && actquest.name == "Quest_Sprzedawcy:_Zabij_potwory_z_lasu.")
				actquest.a++;
			if(actquest.name == "Tajemnicza_Kartka" && actquest.text == "Zabij_12_potworow_dla_Leonarda.")
				actquest.a++;
			int caseis = ( std::rand() % 100 ) + 0;
			if(caseis >= 35 && caseis <= 38){
				eq::pushToArea("Drewniana Skrzynia", "wo_case", 0, 1, 1, 3, 1);
			}
		}
	}
	if(mob5.is){
		if(mob5.getDamage()){
			if(FOTT_Zbroj::sprzedawca.event_[1] == 1 && actquest.name == "Quest_Sprzedawcy:_Zabij_potwory_z_lasu.")
				actquest.a++;
			if(actquest.name == "Tajemnicza_Kartka" && actquest.text == "Zabij_12_potworow_dla_Leonarda.")
				actquest.a++;
			int caseis = ( std::rand() % 100 ) + 0;
			if(caseis >= 35 && caseis <= 38){
				eq::pushToArea("Drewniana Skrzynia", "wo_case", 0, 1, 1, 3, 1);
			}
		}
	}
	if(mob6.is){
		if(mob6.getDamage()){
			if(FOTT_Zbroj::sprzedawca.event_[1] == 1 && actquest.name == "Quest_Sprzedawcy:_Zabij_potwory_z_lasu.")
				actquest.a++;
			if(actquest.name == "Tajemnicza_Kartka" && actquest.text == "Zabij_12_potworow_dla_Leonarda.")
				actquest.a++;
			int caseis = ( std::rand() % 100 ) + 0;
			if(caseis >= 35 && caseis <= 37){
				eq::pushToArea("Drewniana Skrzynia", "wo_case", 0, 1, 1, 3, 1);
			}
		}
	}
}

void FOTT::On(){
	world.isScreenScroll = true;
	is = true;

	// Muzyka

	stop_sample(music);
	music = dunger_th;
	play_sample( music, 255, 127, 750, 1 );
}

void FOTT::Off(){
	is = false;

	// Muzyka

	stop_sample(music);
	music = main_th;
	play_sample( music, 255, 127, 750, 1 );
}

void FOTT::Update(){
	if(is == true){
		App::drawBITMAP(background, 0, 0, 800, 250);
		world.Update(main_bg, plus_bg);

		// Bariers

		LT::Obj_Not(woodroll, -5200 - player.camera.x, 600 - world.plane_h + 25, 100, (world.plane_h - 50));

		// Droga do Wulkanu -->
		if(LT::Bg_OnClick(wulkan, "^ Wulkan (od 6 lvl) ^", -5100, 200, 280)){
			if(player.lvl >= 6){
				Off();
				Volcano::On();
				player.camera.x = 0;
				player.y = 250;
				player.rot = "down";
			}
			else
			{
				App::Message("Od 6 lvl.", "", "", NULL);
			}
		}
		// <-- Droga do Wulkanu

		LT::Obj_Not(woodroll, 1755 - player.camera.x, 600 - world.plane_h + 25, 100, (world.plane_h - 50));

		// Location View

		for(int i = 0; i < 80; i++){
			LT::Bg_Not(bush, -5000 + (i * 125), 175, 75);
		}

		// SPRAWDZIÆ W LOKACJI CONCITY->ZBROJOWNIA_PODSTAWOWA CZY NIE MA B£ÊDU Z NIECI¥G£¥ NAZW¥ POCISKÓW

		LT::Bg_Not(tree_i, -5000, 175, 250);
		LT::Bg_Not(tree_i, -4850, 125, 200);
		LT::Bg_Not(flower, -4725, 50, 50);
		LT::Bg_Not(flower, -4675, 35, 35);
		LT::Bg_Not(rock, -4635, 100, 50);
		LT::Bg_Not(tree_i, -4550, 175, 250);
		LT::Bg_Not(tree_i, -4400, 90, 100);
		LT::Bg_Not(flower, -4300, 50, 50);
		LT::Bg_Not(tree_i, -4245, 100, 175);
		LT::Bg_Not(tree_i, -4075, 100, 175);
		LT::Bg_Not(tree_i, -3975, 90, 100);
		LT::Bg_Not(flower, -3885, 50, 50);
		LT::Bg_Not(tree_i, -3800, 200, 300);
		LT::Bg_Not(flower, -3600, 60, 60);
		LT::Bg_Not(tree_i, -3550, 35, 35);
		LT::Bg_Not(tree_i, -3500, 175, 250);
		LT::Bg_Not(tree_i, -3315, 90, 100);
		LT::Bg_Not(flower, -3215, 40, 40);
		LT::Bg_Not(tree_i, -3175, 175, 250);
		LT::Bg_Not(tree_i, -3000, 175, 250);
		LT::Bg_Not(flower, -2925, 50, 50);
		LT::Bg_Not(tree_i, -2800, 170, 245);
		LT::Bg_Not(tree_i, -2650, 125, 200);
		LT::Bg_Not(tree_i, -2550, 175, 250);
		LT::Bg_Not(flower, -2450, 50, 50);
		LT::Bg_Not(tree_i, -2300, 180, 255);
		LT::Bg_Not(tree_i, -2110, 90, 100);
		LT::Bg_Not(flower, -2025, 60, 60);
		LT::Bg_Not(tree_i, -1930, 175, 250);
		LT::Bg_Not(tree_i, -1780, 175, 250);
		LT::Bg_Not(tree_i, -1650, 135, 180);
		LT::Bg_Not(flower, -1500, 40, 40);
		LT::Bg_Not(flower, -1450, 50, 50);
		LT::Bg_Not(tree_i, -1330, 175, 250);
		LT::Bg_Not(tree_i, -1200, 125, 200);
		LT::Bg_Not(rock, -1075, 100, 100);
		LT::Bg_Not(tree_i, -925, 175, 250);
		LT::Bg_Not(flower, -775, 75, 75);
		LT::Bg_Not(tree_i, -600, 175, 250);
		LT::Bg_Not(tree_i, -425, 120, 200);
		LT::Bg_Not(tree_i, -200, 120, 200);
		LT::Bg_Not(flower, -80, 35, 35);
		LT::Bg_Not(tree_i, -20, 175, 275);
		//
		LT::Bg_Not(tree_i, 500, 200, 300);
		LT::Bg_Not(tree_i, 710, 90, 100);
		LT::Bg_Not(flower, 810, 40, 40);
		LT::Bg_Not(tree_i, 860, 125, 200);
		LT::Bg_Not(rock, 1000, 80, 40);
		LT::Bg_Not(flower, 1090, 55, 55);
		LT::Bg_Not(tree_i, 1155, 100, 200);

		// HOUSE -->

		if(LT::Bg_OnClick(wooden_house, "Lesna Zbrojownia", 1200, 400, 335)){
			FOTT_Zbroj::On();
			Off();

			player.y = 600 - player.h - 51; // 51 --> wysokosc "teleportu" w Zbrojowni
			player.rot = "up";
		}

		// <-- HOUSE

		// MAIN <-- LICENCJE ODBLOKOWAC !!!

		if(LT::Bg_OnClick(way, "Miasto Rahtym", 350, 100, 200)){
			Off();
			ConCity::On();
			player.rot = "down";
			player.camera.x = -2780 - 400 + 50;
			player.y = 600 - world.plane_h + 50;
			player.moveTimer = 15;
		}

		Mobs();
	}
	if(FOTT::is == false && FOTT_Zbroj::is == true)
		FOTT_Zbroj::Update();
}