#include "main.h"
#include "ConCity_Ratusz.h"
#include "Location_Tools.h"
#include "graphics.h"

bool ratusz_is;

//world.plane_h = 350 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

BITMAP * _Ratusz::main_bg;
BITMAP * _Ratusz::plus_bg;
BITMAP * _Ratusz::mainWall;

BITMAP * sekretarzG;

npc sekretarz("Sekretarz", 50, 225, 50, 50, 2);

void _Ratusz::GraphLoad(){
	mainWall = load_bmp("Grafika/Gra/Teren/Lokacje/ConCity/Ratusz/wall.bmp", default_palette);

	sekretarzG = load_bmp("Grafika/Gra/Teren/Lokacje/ConCity/Ratusz/Postacie/sekretarz.bmp", default_palette);

	sekretarz.start("Grafika/Gra/Teren/Lokacje/ConCity/Ratusz/Postacie/sekretarz.bmp");
}

void _Ratusz::Mpcs(){
	sekretarz.update();

	if(sekretarz.active){
		if(sekretarz.event_[0] == 0){
			App::Message("Witaj! Jestem sekretarzem w ratuszu tego miasta. W czym moge pomoc?", "", "", sekretarzG);

			// Dialog ->
			
			if(player.y + player.h >= 400){
				if(App::button("WITAJ!", button, l_button, 0, 0, 1, 0, "", 200, 100, 100, 30) && sekretarz.dTimer <= 0){
					sekretarz.off();
					sekretarz.dTimer = 50;
				}
			}
			if(player.y + player.h < 400){
				if(App::button("WITAJ!", button, l_button, 0, 0, 1, 0, "", 200, 500, 100, 30) && sekretarz.dTimer <= 0){
					sekretarz.off();
					sekretarz.dTimer = 50;
				}
			}
			//////////////////////////////////
			if(player.y + player.h >= 400){
				if(App::button("Jestem tu nowy. Czy mozesz mi powiedziec cos o tym miescie i okolicach?", button, l_button, 0, 0, 0, 0, "", 200, 135, 590, 30) && sekretarz.dTimer <= 0){
					sekretarz.event_[0] = 1;
					sekretarz.dTimer = 50;
				}
			}
			if(player.y + player.h < 400){
				if(App::button("Jestem tu nowy. Czy mozesz mi powiedziec cos o tym miescie i okolicach?", button, l_button, 0, 0, 0, 0, "", 200, 535, 590, 30) && sekretarz.dTimer <= 0){
					sekretarz.event_[0] = 1;
					sekretarz.dTimer = 50;
				}
			}
			// <- Dialog
		}
		if(sekretarz.event_[0] == 1){
			App::Message("A o czym dokladnie chcialbys uslyszec?", "", "", sekretarzG);

			// Dialog ->
			
			if(player.y + player.h >= 400){
				if(App::button("Jak szybko zdobyc doswiadczenie?", button, l_button, 0, 0, 0, 0, "", 200, 100, 270, 30) && sekretarz.dTimer <= 0){
					sekretarz.event_[0] = 2;
					sekretarz.dTimer = 50;
				}
			}
			if(player.y + player.h < 400){
				if(App::button("Jak szybko zdobyc doswiadczenie?", button, l_button, 0, 0, 0, 0, "", 200, 500, 270, 30) && sekretarz.dTimer <= 0){
					sekretarz.event_[0] = 2;
					sekretarz.dTimer = 50;
				}
			}
			/////////////////////
			if(player.y + player.h >= 400){
				if(App::button("Gdzie najpierw powinienem sie wybrac?", button, l_button, 0, 0, 0, 0, "", 200, 135, 310, 30) && sekretarz.dTimer <= 0){
					sekretarz.event_[0] = 4;
					sekretarz.dTimer = 50;
				}
			}
			if(player.y + player.h < 400){
				if(App::button("Gdzie najpierw powinienem sie wybrac?", button, l_button, 0, 0, 0, 0, "", 200, 535, 310, 30) && sekretarz.dTimer <= 0){
					sekretarz.event_[0] = 4;
					sekretarz.dTimer = 50;
				}
			}
			// <- Dialog
		}
		if(sekretarz.event_[0] == 2){

			App::Message("Jak wiesz, jestes jednym z wojownikow ktorzy musza powstrzymac bunt, ale", "oprocz tego jestes wolna jednostka. Wiec pamietaj; dopoki nie", "zdobedziesz 5 poziomu, nie idz do innych miast,", sekretarzG);

			// Dialog ->
			
			if(player.y + player.h >= 400){
				if(App::button("...", button, l_button, 0, 0, 0, 0, "", 200, 100, 310, 30) && sekretarz.dTimer <= 0){
					sekretarz.event_[0] = 3;
					sekretarz.dTimer = 50;
				}
			}
			if(player.y + player.h < 400){
				if(App::button("...", button, l_button, 0, 0, 0, 0, "", 200, 500, 310, 30) && sekretarz.dTimer <= 0){
					sekretarz.event_[0] = 3;
					sekretarz.dTimer = 50;
				}
			}

			// <- Dialog
		}
		if(sekretarz.event_[0] == 3){
			App::Message("gdyz tam sobie nie poradzisz. Niedaleko za murami tego miasta jest", "natomiast jaskinia w ktorej powinienes sobie poradzic i", "przy okazji nabrac doswiadczenia.", sekretarzG);

			if(player.y + player.h >= 400){
				if(App::button("Dziekuje, teraz wiem co mam robic.", button, l_button, 0, 0, 0, 0, "", 200, 100, 300, 30) && sekretarz.dTimer <= 0){
					sekretarz.off();
					sekretarz.dTimer = 50;
				}
			}
			if(player.y + player.h < 400){
				if(App::button("Dziekuje, teraz wiem co mam robic.", button, l_button, 0, 0, 0, 0, "", 200, 500, 300, 30) && sekretarz.dTimer <= 0){
					sekretarz.off();
					sekretarz.dTimer = 50;
				}
			}
		}
		if(sekretarz.event_[0] == 4){
			App::Message("Najlepiej idz za do jaskini za murami miasta, nabrac doswiadczenia,", "tylko nie idz za gleboko! Gdy bedziesz mial juz troche zlota i,", "doswiadczenia, idz do zbrojowni, wyposarzyc sie w lepsza bron.", sekretarzG);

			if(player.y + player.h >= 400){
				if(App::button("Dziekuje, teraz wiem co mam robic.", button, l_button, 0, 0, 0, 0, "", 200, 100, 300, 30) && sekretarz.dTimer <= 0){
					sekretarz.off();
					sekretarz.dTimer = 50;
				}
			}
			if(player.y + player.h < 400){
				if(App::button("Dziekuje, teraz wiem co mam robic.", button, l_button, 0, 0, 0, 0, "", 200, 500, 300, 30) && sekretarz.dTimer <= 0){
					sekretarz.off();
					sekretarz.dTimer = 50;
				}
			}
		}
	}
}

void _Ratusz::Load(std::string name){
	ratusz_is = true;

	std::string main_url = "Grafika/Gra/Teren/Lokacje/";

	std::string main_bg_url;
	std::string plus_bg_url;

	main_bg_url = main_url + name + "/main_bg.bmp";
	plus_bg_url = main_url + name + "/plus_bg.bmp";

	main_bg = load_bmp(main_bg_url.c_str(), default_palette);
	plus_bg = load_bmp(plus_bg_url.c_str(), default_palette);

	GraphLoad();
}

void _Ratusz::On(){ ratusz_is = true; world.isScreenScroll = false; }

void _Ratusz::Off(){ ratusz_is = false; world.isScreenScroll = true; }

void _Ratusz::Update(){
	if(ratusz_is){
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

		if(LT::Bg_OnClick(defaultDoor, "Zamkniete drzwi", 400 + player.camera.x, 100, 150)){}
		if(LT::Bg_OnClick(defaultDoor, "Zamkniete drzwi", 600 + player.camera.x, 100, 150)){}

		Mpcs();

		LT::Obj_Not(desk, 0, 600 - world.plane_h + 10, 150, 75);
	}
}