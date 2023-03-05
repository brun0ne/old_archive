#include "main.h"

#include "ConCity_Ratusz.h"
#include "ConCity_Zbrojownia.h"
#include "ConCity_FoodShop.h"
#include "ConCity_BrunonCave.h"
#include "ForestOfThreeTrees.h"
#include "graphics.h"
#include "music.h"

#include "Location_Tools.h"

int ConCity::liczba;

bool ConCity::is;

npc intro("Intro", 0, -100, 0, 0, 0);

npc ConCity::Carcco("Carcco", 1000, 250, 50, 50, 3);

BITMAP * ConCity::main_bg;
BITMAP * ConCity::plus_bg;

void ConCity::GraphLoad(){
	App::drawText("Ladowanie grafik...", 5, 10);

	draw_sprite(screen, bufor, 0, 0);

	_Ratusz::Load("ConCity/Ratusz");
	_Ratusz::Off();
	ConCity_Zbrojownia::Load("ConCity/Zbrojownia");
	ConCity_Zbrojownia::Off();
	ConCity_FoodShop::Load("ConCity/FoodShop");
	ConCity_FoodShop::Off();
	BrunonCave::Load("ConCity/BrunonCave");
	BrunonCave::Off();

	Carcco.start("Grafika/Gra/Postacie/person1.bmp");

	App::readFromFile("DATA/never.save", liczba);
	if(liczba == 1)
		intro.on();
	else
		intro.off();

	App::drawText("Grafiki zaladowano poprawnie.", 5, 20);

	draw_sprite(screen, bufor, 0, 0);
}

void ConCity::Load(std::string name){
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

void ConCity::On(){ 
	is = true;
	world.isScreenScroll = true;
	App::setLight(0);
	App::setLightColor(255, 0, 255);

	/*stop_sample(music);
	music = main_th;
	play_sample( music, 255, 127, 750, 1 );*/
}

void ConCity::Off(){
	is = false;
}

void ConCity::Intro(){
	intro.logic();

	if(intro.dTimer >= 0)
		intro.dTimer--;

	if(intro.active){
		if(intro.event_[0] == 0){
			App::Message("Witaj wojowniku w swiecie Construgia! Jest to przyjazny, technologicznie rozwiniety swiat,", "ktory niestety niedawno zostal zaatakowany przez potwory. Teraz, wszyscy wojownicy, tacy", "jak Ty musza je powstrzymac. Najpierw udaj sie do ratusza, tam otrzymasz dalsze informacje.", NULL);

			if(App::button("OK.", button, l_button, 0, 0, 1, 0, "", 75, 500, 100, 30) && intro.dTimer <= 0)
				intro.off();

			if(App::button("Chce zobaczyc sterowanie.", button, l_button, 0, 0, 1, 0, "", 185, 500, 350, 30) && intro.dTimer <= 0){
				intro.event_[0] = 1;
				intro.dTimer = 50;
			}
			if(App::button("Gdzie moge znalezc prace?.", button, l_button, 0, 0, 1, 0, "", 185, 535, 350, 30) && intro.dTimer <= 0){
				intro.event_[0] = 2;
				intro.dTimer = 50;
			}
		}
		else if(intro.event_[0] == 1){
			App::Message("Sterowanie: strzalki - poruszanie sie | spacja / prawy przycisk myszy - strzelanie |", "o - opcje | esc - wyjscie | lewy przycisk myszy - rozpoczecie rozmowy, akcja (cd. eq), ", "wybor opcji w dialogu, zbieranie lootu z potworow | E - minimapa.", NULL);

			if(App::button("OK.", button, l_button, 0, 0, 1, 0, "", 75, 500, 100, 30) && intro.dTimer <= 0){
				intro.event_[0] = 0;
				intro.dTimer = 50;
			}
		}
		else if(intro.event_[0] == 2){
			App::Message("Na poczatek powinienes zrobic cos latwego.", "Podobno sprzedawca w Zbrojowni w miescie, w ktorym jestes potrzebuje pomocy.", "Wiecej informacji otrzymasz od sekretarza w ratuszu.", NULL);

			if(App::button("OK.", button, l_button, 0, 0, 1, 0, "", 75, 500, 100, 30) && intro.dTimer <= 0){
				intro.event_[0] = 0;
				intro.dTimer = 50;
			}
		}
	}
}

void ConCity::Npcs(){
	Carcco.update();

	if(Carcco.active){
		App::Message("Witaj!", "Piekna pogoda dzis, nieprawdaz?", "", Carcco.bmp);

		if(Carcco.event_[0] == 0){
			if(player.y + player.h >= 400){
					if(App::button("Witaj! Masz racje, wyjatkowo dzis slonecznie.", button, l_button, 0, 0, 1, 0, "", 200, 100, 425, 30) && Carcco.dTimer <= 0){
						Carcco.off();
						Carcco.dTimer = 50;
					}
				}
			if(player.y + player.h < 400){
				if(App::button("Witaj! Masz racje, wyjatkowo dzis slonecznie.", button, l_button, 0, 0, 1, 0, "", 200, 500, 425, 30) && Carcco.dTimer <= 0){
					Carcco.off();
					Carcco.dTimer = 50;
				}
			}
			////
			if(eq::filons_paper == 1){
				if(player.y + player.h >= 400){
					if(App::button("Poczekaj! Spojrz na to.", button, l_button, 0, 0, 1, 0, "", 200, 140, 400, 30) && Carcco.dTimer <= 0){
						Carcco.event_[0] = 1;
						Carcco.dTimer = 50;
					}
				}
				if(player.y + player.h < 400){
					if(App::button("Poczekaj! Spojrz na to.", button, l_button, 0, 0, 1, 0, "", 200, 540, 400, 30) && Carcco.dTimer <= 0){
						Carcco.event_[0] = 1;
						Carcco.dTimer = 50;
					}
				}
			}
		}
		else if(Carcco.event_[0] == 1){
			App::Message("Och! Dobrze, ze to mnie zapytales!", "Kiedys kuzyn mi o tym opowiadal.. To jest Kartka Wyrzutu.", "Moj kuzyn mieszka teraz w lesie, jest sprzedawca. Zapytaj go o wiecej!", Carcco.bmp);

			if(player.y + player.h >= 400){
				if(App::button("Dziekuje ci bardzo, zegnaj!", button, l_button, 0, 0, 1, 0, "", 200, 140, 400, 30) && Carcco.dTimer <= 0){
					if(actquest.name != "Tajemnicza_Kartka")
						actquest.replace("Tajemnicza_Kartka", "Poszukaj_kuzyna_Carcco.", 1000, 150, 0, 4);
					Carcco.off();
					Carcco.dTimer = 50;
				}
			}
			if(player.y + player.h < 400){
				if(App::button("Dziekuje ci bardzo, zegnaj!", button, l_button, 0, 0, 1, 0, "", 200, 540, 400, 30) && Carcco.dTimer <= 0){
					if(actquest.name != "Tajemnicza_Kartka")
						actquest.replace("Tajemnicza_Kartka", "Poszukaj_kuzyna_Carcco.", 1000, 150, 0, 4);
					Carcco.off();
					Carcco.dTimer = 50;
				}
			}
		}
	}
}

void ConCity::Mobs(){}

void ConCity::Update(){
	if(is == true){
		clear_to_color(bufor, makecol(0, 100, 255));

		world.Update(main_bg, plus_bg);

		if(player.camera.x < -3190){
			player.camera.x = -3190;
			world.plus_bg_x -= (1 - world.speed);
		}

		if(player.camera.x > 3500){
			player.camera.x = 3500;
			world.plus_bg_x += (1 - world.speed);
		}

		// Background ->

		App::drawBITMAP(mountBack, -2800 - player.camera.x, 600 - world.plane_h - 200, 400, 200);
		App::drawBITMAP(mountBack, -3200 - player.camera.x, 600 - world.plane_h - 200, 400, 200);

		// <- Background

		// Location Viev

		if(LT::Bg_OnClick(way, "Las Trzech Wisni", -2780, 100, 200)){
			if(player.lvl >= 4){
				Off();
				FOTT::On();
				player.rot = "down";
				player.camera.x = 0;
				player.y = 600 - world.plane_h + 50;
				player.moveTimer = 15;
			}
			else{
				App::Message("Nie mozesz tam wejsc, dopoki nie zdobedziesz 4 lvl.", "", "", NULL);
			}
		}

		if(LT::Bg_OnClick(stoneTower, "Wieza Straznicza [Zamknieta]", -2500, 300, 500)){/*...*/}
		LT::Bg_Not(stoneWall, -2200, 5000, 200);
		// LEFT BEGIN OF CITY -->

		// Bg_ ->

		LT::Bg_Not(shortHouse1, -2190, 222, 251);
		LT::Bg_Not(shortHouse3, -1958, 222, 251);
		LT::Bg_Not(shortHouse2, -1726, 222, 251);
		LT::Bg_Not(shortHouse4, -1494, 222, 251);

		LT::Bg_OnClick(newsLetter, "Biuletyn [Nieczynny]", -1262, 125, 250);

		LT::Bg_Not(shortHouse1, -1127, 222, 251);
		LT::Bg_Not(shortHouse2, -895, 222, 251);
		// Inter-><-
		LT::Bg_Not(shortHouse4, -431, 222, 251);
		LT::Bg_Not(shortHouse3, -199, 222, 251);

		LT::Bg_OnClick(newsLetter, "Biuletyn [Nieczynny]", 28, 125, 250);

		//INTERACTIVE-!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!->
		
		if(LT::Bg_OnClick(foodShop, "Sklep Spozywczy", -663, 222, 251)){
			ConCity_FoodShop::On();
			Off();

			player.y = 600 - player.h - 51; // 51 --> wysokosc "teleportu" w Sklepie
			player.rot = "up";
		}

		if(LT::Bg_OnClick(bigBuilding, "Ratusz Miasta Rahtym", 150, 500, 250)){
			_Ratusz::On();
			Off();

			player.y = 600 - player.h - 51; // 51 --> wysokosc "teleportu" w Ratuszu
			player.rot = "up";
		}
		if(LT::Bg_OnClick(shop, "Zbrojownia Podstawowa", 660, 222, 251)){
			ConCity_Zbrojownia::On();
			Off();

			player.y = 600 - player.h - 51; // 51 --> wysokosc "teleportu" w Zbrojowni
			player.rot = "up";
		}

		//<-INTERACTIVE-!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

		LT::Bg_Not(shortHouse3, 892, 222, 251);
		LT::Bg_Not(shortHouse1, 1124, 222, 251);

		LT::Bg_OnClick(newsLetter, "Biuletyn [Nieczynny]", 1356, 125, 250);

		LT::Bg_Not(shortHouse4, 1491, 222, 251);
		LT::Bg_Not(shortHouse2, 1723, 222, 251);
		LT::Bg_Not(shortHouse3, 1955, 222, 251);
		LT::Bg_Not(shortHouse1, 2187, 222, 251);

		// <- Bg_ | Pn_ ->
	
		LT::Pn_Not(stone, 250, 350, 300, 150);

		// <- Pn_ | Obj ->

		// <- Obj

		// <-- RIGHT BEGIN OF CITY
		if(LT::Bg_OnClick(stoneTower, "Wieza Straznicza [Zamknieta]", 2500, 300, 500)){/*...*/}

		// Bg ->

		// Background ->

		App::drawBITMAP(mountBack, 2800 - player.camera.x, 600 - world.plane_h - 200, 400, 200);
		App::drawBITMAP(mountBack, 3200 - player.camera.x, 600 - world.plane_h - 200, 400, 200);
		App::drawBITMAP(mountBack, 3600 - player.camera.x, 600 - world.plane_h - 200, 400, 200);
		App::drawBITMAP(mountBack, 4000 - player.camera.x, 600 - world.plane_h - 200, 400, 200);

		// <- Background

		LT::Bg_Not(blueTree1, 2820, 205, 250);
		LT::Bg_Not(blueTree1, 3035, 205, 250);

		if(LT::Bg_OnClick(caveEnter, "Jaskinia krola Brunona I Wielkiego", 3300, 500, 250)){
			BrunonCave::On();
			Off();

			player.y = 600 - player.h - 51; // 51 --> wysokosc "teleportu" w Zbrojowni
			player.camera.x = 0;
			player.rot = "up";
		}

		// <- Bg

		Mobs();
		Npcs();
		
		Trasher::D_LItem(2414);

		if(intro.active)
			Intro();
	}
	if(is == false){
		_Ratusz::Update();
		ConCity_Zbrojownia::Update();
		ConCity_FoodShop::Update();
		BrunonCave::Update();
	}
}