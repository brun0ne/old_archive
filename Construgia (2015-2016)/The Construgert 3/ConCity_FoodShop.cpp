#include "main.h"
#include "ConCity.h"
#include "ConCity_FoodShop.h"
#include "Location_Tools.h"
#include "graphics.h"

bool ConCity_FoodShop::is;

BITMAP * ConCity_FoodShop::main_bg;
BITMAP * ConCity_FoodShop::plus_bg;
BITMAP * ConCity_FoodShop::mainWall;

npc sklepikarz("Sprzedawca", 50, 225, 50, 50, 6);

void ConCity_FoodShop::GraphLoad(){
	mainWall = load_bmp("Grafika/Gra/Teren/Lokacje/ConCity/Zbrojownia/wall.bmp", default_palette);

	sklepikarz.start("Grafika/Gra/Teren/Lokacje/ConCity/FoodShop/Postacie/sprzedawca.bmp");
}

void ConCity_FoodShop::Load(std::string name){
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

void ConCity_FoodShop::Shop(){
	App::Message("Oto moja oferta: ", "", "", sklepikarz.bmp);

	// Shop Sale -->

	if(player.y + player.h >= 400){
		if(App::button("Jablko | +HP: 15 | Koszt: 5", button, l_button, 0, 0, 1, 0, "", 200, 35, 400, 30) && sklepikarz.dTimer <= 0){
			if(player.gold >= 5){
				eq::pushToArea("Jablko", "jablko", 7, 15, 1, 2, 1);
				player.gold -= 5;
				sklepikarz.off();
			}
			else
				sklepikarz.off(); // tym.

			sklepikarz.dTimer = 50;
		}
	}
	if(player.y + player.h < 400){
		if(App::button("Jablko | +HP: 15 | Koszt: 5", button, l_button, 0, 0, 1, 0, "", 200, 435, 400, 30) && sklepikarz.dTimer <= 0){
			if(player.gold >= 5){
				eq::pushToArea("Jablko", "jablko", 7, 15, 1, 2, 1);
				player.gold -= 5;
				sklepikarz.off();
			}
			else
				sklepikarz.off(); // tym.

			sklepikarz.dTimer = 50;
		}
	}
	///////////////////////////////
	if(player.y + player.h >= 400){
		if(App::button("Kanapka | +HP: 25 | Koszt: 15", button, l_button, 0, 0, 1, 0, "", 200, 71, 400, 30) && sklepikarz.dTimer <= 0){
			if(player.gold >= 15){
				eq::pushToArea("Kanapka", "kanapka", 7, 25, 1, 2, 1);
				player.gold -= 15;
				sklepikarz.off();
			}
			else
				sklepikarz.off(); // tym.

			sklepikarz.dTimer = 50;
		}
	}
	if(player.y + player.h < 400){
		if(App::button("Kanapka | +HP: 25 | Koszt: 15", button, l_button, 0, 0, 1, 0, "", 200, 471, 400, 30) && sklepikarz.dTimer <= 0){
			if(player.gold >= 15){
				eq::pushToArea("Kanapka", "kanapka", 7, 25, 1, 2, 1);
				player.gold -= 15;
				sklepikarz.off();
			}
			else
				sklepikarz.off(); // tym.

			sklepikarz.dTimer = 50;
		}
	}
	///////////////////////////////
	if(player.y + player.h >= 400){
		if(App::button("Mieso | +HP: 100 | Koszt: 25", button, l_button, 0, 0, 1, 0, "", 200, 107, 400, 30) && sklepikarz.dTimer <= 0){
			if(player.gold >= 25){
				eq::pushToArea("Mieso", "mieso", 7, 100, 1, 2, 1);
				player.gold -= 25;
				sklepikarz.off();
			}
			else
				sklepikarz.off(); // tym.

			sklepikarz.dTimer = 50;
		}
	}
	if(player.y + player.h < 400){
		if(App::button("Mieso | +HP: 100 | Koszt: 25", button, l_button, 0, 0, 1, 0, "", 200, 507, 400, 30) && sklepikarz.dTimer <= 0){
			if(player.gold >= 25){
				eq::pushToArea("Mieso", "mieso", 7, 100, 1, 2, 1);
				player.gold -= 25;
				sklepikarz.off();
			}
			else
				sklepikarz.off(); // tym.

			sklepikarz.dTimer = 50;
		}
	}

	// <-- Shop Sale

	// Exit -->

	if(player.y + player.h >= 400){
		if(App::button("Jednak sie rozmyslilem. Zegnaj!", button, l_button, 0, 0, 1, 0, "", 200, 143, 400, 30) && sklepikarz.dTimer <= 0){
			sklepikarz.off();
			sklepikarz.dTimer = 50;
		}
	}
	if(player.y + player.h < 400){
		if(App::button("Jednak sie rozmyslilem. Zegnaj!", button, l_button, 0, 0, 1, 0, "", 200, 543, 400, 30) && sklepikarz.dTimer <= 0){
			sklepikarz.off();
			sklepikarz.dTimer = 50;
		}
	}

	// <-- Exit
}

void ConCity_FoodShop::Npcs(){
	sklepikarz.update();

	// 'sklepikarz' (npc) -->

	if(sklepikarz.active){
		if(sklepikarz.event_[0] == 0){
			App::Message("Witam! Sprzedaje tu rozne artykuly spozywcze.", "Moze zainteresujesz sie moja oferta?", "", sklepikarz.bmp);

			// Exit Button -->

			if(player.y + player.h >= 400){
				if(App::button("Witaj!", button, l_button, 0, 0, 1, 0, "", 200, 100, 400, 30) && sklepikarz.dTimer <= 0){
					sklepikarz.off();
					sklepikarz.dTimer = 50;
				}
			}
			if(player.y + player.h < 400){
				if(App::button("Witaj!", button, l_button, 0, 0, 1, 0, "", 200, 500, 400, 30) && sklepikarz.dTimer <= 0){
					sklepikarz.off();
					sklepikarz.dTimer = 50;
				}
			}

			// <-- Exit Button

			// Shop Button -->

			if(player.y + player.h >= 400){
				if(App::button("Czy moglbym obejrzec Twoja oferte?", button, l_button, 0, 0, 1, 0, "", 200, 135, 400, 30) && sklepikarz.dTimer <= 0){
					sklepikarz.event_[0] = 1;
					sklepikarz.dTimer = 50;
				}
			}
			if(player.y + player.h < 400){
				if(App::button("Czy moglbym obejrzec Twoja oferte?", button, l_button, 0, 0, 1, 0, "", 200, 535, 400, 30) && sklepikarz.dTimer <= 0){
					sklepikarz.event_[0] = 1;
					sklepikarz.dTimer = 50;
				}
			}

			// <-- Shop Button
		}

		// Shop -->

		if(sklepikarz.event_[0] == 1)
			Shop();

		// <-- Shop
	}

	// <-- 'sklepikarz' (npc)
}

void ConCity_FoodShop::On(){
	is = true;
	world.isScreenScroll = false;
}

void ConCity_FoodShop::Off(){
	is = false;
	world.isScreenScroll = true;
}

void ConCity_FoodShop::Update(){
	if(is){
		App::drawBITMAP(mainWall, 0, 0, 800, 600 - world.plane_h);

		world.Update(main_bg, plus_bg);

		//Location Viev

		LT::Bg_Not(szafa_jedz, 600 + player.camera.x, 128, 208);
		LT::Bg_Not(szafa_jedz, 450 + player.camera.x, 128, 208);

		//Teleport -->
		if(LT::Dn_Enter(350 + player.camera.x, 100)){
			ConCity::On();
			Off();

			player.y = 600 - world.plane_h + 25; // 25 --> bezpieczna odleglosc od wejscia do budynku (teleportu)
			player.x = 375;
			player.rot = "down";
		}
		//<-- Teleport

		Npcs();

		LT::Obj_Not(desk, 0, 600 - world.plane_h + 10, 150, 75);

		LT::Obj_Not(chair, 10, 437, 100, 100);
	}
}