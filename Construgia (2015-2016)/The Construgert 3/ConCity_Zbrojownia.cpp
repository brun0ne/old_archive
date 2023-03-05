#include "main.h"
#include "ConCity.h"
#include "ConCity_Zbrojownia.h"
#include "Location_Tools.h"
#include "graphics.h"

bool ConCity_Zbrojownia::is;

BITMAP * ConCity_Zbrojownia::main_bg;
BITMAP * ConCity_Zbrojownia::plus_bg;
BITMAP * ConCity_Zbrojownia::mainWall;

npc sprzedawca("Sprzedawca", 50, 225, 50, 50, 9);

void ConCity_Zbrojownia::GraphLoad(){
	mainWall = load_bmp("Grafika/Gra/Teren/Lokacje/ConCity/Zbrojownia/wall.bmp", default_palette);

	sprzedawca.start("Grafika/Gra/Teren/Lokacje/ConCity/Zbrojownia/sprzedawca.bmp");

	int first = 0;
	App::readFromFile("DATA/never.save", first);
	
	if(first == 1){
		sprzedawca.event_[1] = 0;
		save();
	}
	else
	{
		read();
	}
}

void ConCity_Zbrojownia::Load(std::string name){
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

void ConCity_Zbrojownia::Shop(){
	App::Message("Oto moja oferta:", "", "", sprzedawca.bmp);
	
	// POCISKI ->

	//Ulepszony Pocisk dla Poczatkujacych -->
	
	if(player.y + player.h >= 400){
		if(App::button("Ulepszony Pocisk dla Poczatkujacych | +AP: 7 | Ilosc: 100 | Koszt: 40 zlota", button, l_button, 0, 0, 1, 0, "", 200, 35, 600, 30) && sprzedawca.dTimer <= 0){
			if(player.gold >= 40){
				eq::pushToArea("Ulepszony_Pocisk_dla_Poczatkujacych", "poczatkowy_ex", 7, 0, 1, 0, 100);
				player.gold -= 40;
				sprzedawca.off();
			}
			else
				sprzedawca.event_[0] = 2;

			sprzedawca.dTimer = 50;
		}
	}
	if(player.y + player.h < 400){
		if(App::button("Ulepszony Pocisk dla Poczatkujacych | +AP: 7 | Ilosc: 100 | Koszt: 40 zlota", button, l_button, 0, 0, 1, 0, "", 200, 435, 600, 30) && sprzedawca.dTimer <= 0){
			if(player.gold >= 40){
				eq::pushToArea("Ulepszony_Pocisk_dla_Poczatkujacych", "poczatkowy_ex", 7, 0, 1, 0, 100);
				player.gold -= 40;
				sprzedawca.off();
			}
			else
				sprzedawca.event_[0] = 2;

			sprzedawca.dTimer = 50;
		}
	}
	// <---------------------------------------------------------------------------------------------------------------

	// Zelazny Pocisk
	if(player.y + player.h >= 400){
		if(App::button("Zelazny Pocisk | +AP: 15 |  Ilosc: 250 | Koszt: 100 zlota", button, l_button, 0, 0, 1, 0, "", 200, 70, 600, 30) && sprzedawca.dTimer <= 0){
			if(player.gold >= 100){
				eq::pushToArea("Zelazny_Pocisk", "zelazny", 15, 0, 1, 0, 250);
				player.gold -= 100;
				sprzedawca.off();
			}
			else
				sprzedawca.event_[0] = 2;

			sprzedawca.dTimer = 50;
		}
	}
	if(player.y + player.h < 400){
		if(App::button("Zelazny Pocisk | +AP: 15 | Ilosc: 250 | Koszt: 100 zlota", button, l_button, 0, 0, 1, 0, "", 200, 470, 600, 30) && sprzedawca.dTimer <= 0){
			if(player.gold >= 100){
				eq::pushToArea("Zelazny_Pocisk", "zelazny", 15, 0, 1, 0, 250);
				player.gold -= 100;
				sprzedawca.off();
			}
			else
				sprzedawca.event_[0] = 2;

			sprzedawca.dTimer = 50;
		}
	}
	// <---------------------------------------------------------------------------------------------------------------

	// Utwardzony Zelazny Pocisk
	if(player.y + player.h >= 400){
		if(App::button("Utwardzony Zelazny Pocisk | +AP: 20 |  Ilosc: 300 | Koszt: 200 zlota", button, l_button, 0, 0, 1, 0, "", 200, 105, 600, 30) && sprzedawca.dTimer <= 0){
			if(player.gold >= 200){
				eq::pushToArea("Utwardzony_Zelazny_Pocisk", "zelazny_ex", 20, 0, 1, 0, 300);
				player.gold -= 200;
				sprzedawca.off();
			}
			else
				sprzedawca.event_[0] = 2;

			sprzedawca.dTimer = 50;
		}
	}
	if(player.y + player.h < 400){
		if(App::button("Utwardzony Zelazny Pocisk | +AP: 20 | Ilosc: 300 | Koszt: 200 zlota", button, l_button, 0, 0, 1, 0, "", 200, 505, 600, 30) && sprzedawca.dTimer <= 0){
			if(player.gold >= 200){
				eq::pushToArea("Utwardzony_Zelazny_Pocisk", "zelazny_ex", 20, 0, 1, 0, 300);
				player.gold -= 200;
				sprzedawca.off();
			}
			else
				sprzedawca.event_[0] = 2;

			sprzedawca.dTimer = 50;
		}
	}
	// <---------------------------------------------------------------------------------------------------------------

	// <- POCISKI

	// EXIT ->

	if(player.y + player.h >= 400){
		if(App::button("Jednak sie rozmyslilem. Zegnaj!", button, l_button, 0, 0, 1, 0, "", 500, 140, 285, 30) && sprzedawca.dTimer <= 0){
			sprzedawca.off();
			sprzedawca.dTimer = 50;
		}
	}
	if(player.y + player.h < 400){
		if(App::button("Jednak sie rozmyslilem. Zegnaj!", button, l_button, 0, 0, 1, 0, "", 500, 540, 285, 30) && sprzedawca.dTimer <= 0){
			sprzedawca.off();
			sprzedawca.dTimer = 50;
		}
	}

	// <- EXIT
}

void ConCity_Zbrojownia::save(){
	App::saveToFile("DATA/Quests/Zbrojownia/quest1.save", sprzedawca.event_[1]);
}

void ConCity_Zbrojownia::read(){
	App::readFromFile("DATA/Quests/Zbrojownia/quest1.save", sprzedawca.event_[1]);
}

void ConCity_Zbrojownia::Npcs(){
	sprzedawca.update();

	if(sprzedawca.active && sprzedawca.event_[0] == 5){
		App::Message("Wlasnie szukalem wojownika, ktory moglby zabic dla mnie kilka potworow z", " jaskini, gdyz przeszkadaja mi one w zbieraniu ziol. Idz do jaskini krola Brunona", "(znajdziesz ja po prawej stronie za murem miasta) i zabij dla mnie 12 potworow. Dobrze?", NULL);
		
		if(player.y + player.h >= 400){
			if(App::button("Oczywiscie!", button, l_button, 0, 0, 1, 0, "", 200, 100, 400, 30) && sprzedawca.dTimer <= 0){
				actquest.replace("Quest_Sprzedawcy:_Zabij_kilka_potworow_z_jaskini.", "Jaskinie_znajdziesz_za_murami_miasta.", 50, 50, 0, 12);
				if(actquest.name == "Quest_Sprzedawcy:_Zabij_kilka_potworow_z_jaskini."){
					sprzedawca.event_[1] = 1;
				}
				sprzedawca.off();
				sprzedawca.dTimer = 50;
			}
		}
		if(player.y + player.h < 400){
			if(App::button("Oczywiscie!", button, l_button, 0, 0, 1, 0, "", 200, 500, 400, 30) && sprzedawca.dTimer <= 0){
				actquest.replace("Quest_Sprzedawcy:_Zabij_kilka_potworow_z_jaskini.", "Jaskinie_znajdziesz_za_murami_miasta.", 50, 50, 0, 12);
				if(actquest.name == "Quest_Sprzedawcy:_Zabij_kilka_potworow_z_jaskini."){
					sprzedawca.event_[1] = 1;
				}
				sprzedawca.off();
				sprzedawca.dTimer = 50;
			}
		}
		//////////
		if(player.y + player.h >= 400){
			if(App::button("Niestety teraz nie mam czasu. Zegnaj!", button, l_button, 0, 0, 1, 0, "", 200, 135, 400, 30) && sprzedawca.dTimer <= 0){
				sprzedawca.off();
				sprzedawca.dTimer = 50;
			}
		}
		if(player.y + player.h < 400){
			if(App::button("Niestety teraz nie mam czasu. Zegnaj!", button, l_button, 0, 0, 1, 0, "", 200, 535, 400, 30) && sprzedawca.dTimer <= 0){
				sprzedawca.off();
				sprzedawca.dTimer = 50;
			}
		}
	}

	if(sprzedawca.active && sprzedawca.event_[0] == 2){
		App::Message("Nie masz wystarczajaco duzo zlota!", "", "", sprzedawca.bmp);
		
		if(player.y + player.h >= 400){
				if(App::button("Rzeczywiscie. Pojde zarobic wiecej i wroce.", button, l_button, 0, 0, 1, 0, "", 200, 100, 400, 30) && sprzedawca.dTimer <= 0){
					sprzedawca.off();
					sprzedawca.dTimer = 50;
				}
			}
		if(player.y + player.h < 400){
			if(App::button("Rzeczywiscie. Pojde zarobic wiecej i wroce.", button, l_button, 0, 0, 1, 0, "", 200, 500, 400, 30) && sprzedawca.dTimer <= 0){
				sprzedawca.off();
				sprzedawca.dTimer = 50;
			}
		}
	}

	if(sprzedawca.active && sprzedawca.event_[0] == 1)
		Shop();

	if(sprzedawca.active && sprzedawca.event_[0] == 0){
		App::Message("Witaj! Jestem sprzedawca pociskow. Jezeli jestes poczatkujacy moja", 
			"oferta z pewnoscia Cie zainteresuje. Jesli jednak Twoj poziom jest", "wyzszy od 5, nic ciekawego tu nie znajdziesz.", sprzedawca.bmp);

		if(player.y + player.h >= 400){
				if(App::button("WITAJ!", button, l_button, 0, 0, 1, 0, "", 200, 100, 100, 30) && sprzedawca.dTimer <= 0){
					sprzedawca.off();
					sprzedawca.dTimer = 50;
				}
			}
		if(player.y + player.h < 400){
			if(App::button("WITAJ!", button, l_button, 0, 0, 1, 0, "", 200, 500, 100, 30) && sprzedawca.dTimer <= 0){
				sprzedawca.off();
				sprzedawca.dTimer = 50;
			}
		}
		///////////////////////////////
		if(player.y + player.h >= 400){
			if(App::button("Pokaz mi swoja oferte.", button, l_button, 0, 0, 1, 0, "", 200, 135, 200, 30) && sprzedawca.dTimer <= 0){
				sprzedawca.event_[0] = 1;
				sprzedawca.dTimer = 50;
			}
		}
		if(player.y + player.h < 400){
			if(App::button("Pokaz mi swoja oferte.", button, l_button, 0, 0, 1, 0, "", 200, 535, 200, 30) && sprzedawca.dTimer <= 0){
				sprzedawca.event_[0] = 1;
				sprzedawca.dTimer = 50;
			}
		}
		///////////////////////////////
		if(sprzedawca.event_[1] != 1){
			if(player.y + player.h >= 400){
				if(App::button("Czy masz moze dla mnie jakas prace?", button, l_button, 0, 0, 1, 0, "", 450, 135, 325, 30) && sprzedawca.dTimer <= 0){
					sprzedawca.event_[0] = 5;
					sprzedawca.dTimer = 50;
				}
			}
			if(player.y + player.h < 400){
				if(App::button("Czy masz moze dla mnie jakas prace?", button, l_button, 0, 0, 1, 0, "", 450, 535, 325, 30) && sprzedawca.dTimer <= 0){
					sprzedawca.event_[0] = 5;
					sprzedawca.dTimer = 50;
				}
			}
		}
		///////////////////////////////
	}
}

void ConCity_Zbrojownia::On(){
	is = true;
	world.isScreenScroll = false;
}

void ConCity_Zbrojownia::Off(){
	is = false;
	world.isScreenScroll = true;
}

void ConCity_Zbrojownia::Update(){
	if(is){
		App::drawBITMAP(mainWall, 0, 0, 800, 600 - world.plane_h);

		world.Update(main_bg, plus_bg);

		//Location Viev

		//Teleport -->
		if(LT::Dn_Enter(350 + player.camera.x, 100)){
			ConCity::On();
			Off();

			player.y = 600 - world.plane_h + 25; // 25 --> bezpieczna odleglosc od wejscia do budynku (teleportu)
			player.x = 375;
			player.rot = "down";
		}
		//<-- Teleport

		LT::Bg_Not(szafa, 600 + player.camera.x, 128, 208);
		LT::Bg_Not(szafa, 450 + player.camera.x, 128, 208);

		Npcs();

		LT::Obj_Not(desk, 0, 600 - world.plane_h + 10, 150, 75);
	}
}