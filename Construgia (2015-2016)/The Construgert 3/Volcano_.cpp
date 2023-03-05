#include "main.h"
#include "Volcano_.h"
#include "ForestOfThreeTrees.h"
#include "music.h"

#include "graphics.h"
#include "Location_Tools.h"

bool Volcano::is = false;
BITMAP * Volcano::main_bg;
BITMAP * Volcano::plus_bg;
BITMAP * Volcano::background;
int Volcano::event_ = 0;

Mob Volcano::mob1( 3300, 300, 50, 50, 2900, 3400, 50, -1, true, 400, 40, 15, 25, true, "");
Mob Volcano::mob2( 2500, 400, 50, 50, 2000, 2500, 50, -1, true, 400, 40, 15, 25, true, "");
Mob Volcano::mob3( 1000, 250, 50, 50, 500, 1500, 50, -1, true, 400, 40, 15, 25, true, "");

Mob Volcano::mob1_( -3300, 300, 50, 50, -3400, -2900, 50, -1, true, 400, 40, 15, 25, true, "");
Mob Volcano::mob2_( -2500, 400, 50, 50, -2500, -2000, 50, -1, true, 400, 40, 15, 25, true, "");
Mob Volcano::mob3_( -1000, 250, 50, 50, -1500, -500, 50, -1, true, 400, 40, 15, 25, true, "");

npc Volcano::Straznik("Straznik", 200, 275, 50, 50, 6);

void Volcano::GraphLoad(){
	Straznik.start("Grafika/Gra/Postacie/straznik_skala.bmp");
	Straznik.active = false;

	mob1.Load("Grafika/Gra/Moby/lavams.bmp");
	mob2.Load("Grafika/Gra/Moby/lavams.bmp");
	mob3.Load("Grafika/Gra/Moby/lavams.bmp");
	mob1_.Load("Grafika/Gra/Moby/lavams.bmp");
	mob2_.Load("Grafika/Gra/Moby/lavams.bmp");
	mob3_.Load("Grafika/Gra/Moby/lavams.bmp");
}

void Volcano::Load(std::string name){
	is = true;

	std::string main_url = "Grafika/Gra/Teren/Lokacje/";

	std::string main_bg_url;
	std::string plus_bg_url;
	std::string backg_url;

	main_bg_url = main_url + name + "/main_bg.bmp";
	plus_bg_url = main_url + name + "/plus_bg.bmp";
	backg_url = main_url + name + "/background.bmp";

	main_bg = load_bmp(main_bg_url.c_str(), default_palette);
	plus_bg = load_bmp(plus_bg_url.c_str(), default_palette);
	background = load_bmp(backg_url.c_str(), default_palette);

	GraphLoad();
}

void Volcano::Mobs(){
	mob1.basicUpdate();
	mob2.basicUpdate();
	mob3.basicUpdate();
	mob1_.basicUpdate();
	mob2_.basicUpdate();
	mob3_.basicUpdate();

	if(mob1.is){
		if(mob1.getDamage()){
			int caseis = ( std::rand() % 100 ) + 0;
			if(caseis >= 35 && caseis <= 38){
				eq::pushToArea("Wulkaniczna Skrzynia", "wu_case", 0, 2, 1, 3, 1);
			}
		}
	}
	if(mob2.is){
		if(mob2.getDamage()){
			int caseis = ( std::rand() % 100 ) + 0;
			if(caseis >= 35 && caseis <= 38){
				eq::pushToArea("Wulkaniczna Skrzynia", "wu_case", 0, 2, 1, 3, 1);
			}
		}
	}
	if(mob3.is){
		if(mob3.getDamage()){
			int caseis = ( std::rand() % 100 ) + 0;
			if(caseis >= 35 && caseis <= 38){
				eq::pushToArea("Wulkaniczna Skrzynia", "wu_case", 0, 2, 1, 3, 1);
			}
		}
	}
	if(mob1_.is){
		if(mob1_.getDamage()){
			int caseis = ( std::rand() % 100 ) + 0;
			if(caseis >= 35 && caseis <= 38){
				eq::pushToArea("Wulkaniczna Skrzynia", "wu_case", 0, 2, 1, 3, 1);
			}
		}
	}
	if(mob2_.is){
		if(mob2_.getDamage()){
			int caseis = ( std::rand() % 100 ) + 0;
			if(caseis >= 35 && caseis <= 38){
				eq::pushToArea("Wulkaniczna Skrzynia", "wu_case", 0, 2, 1, 3, 1);
			}
		}
	}
	if(mob3_.is){
		if(mob3_.getDamage()){
			int caseis = ( std::rand() % 100 ) + 0;
			if(caseis >= 35 && caseis <= 38){
				eq::pushToArea("Wulkaniczna Skrzynia", "wu_case", 0, 2, 1, 3, 1);
			}
		}
	}
}

void Volcano::Npcs(){
	Straznik.update();

	// Dialogi

	if(Straznik.active){
		if(Straznik.event_[0] == 0){
			App::Message("Witaj wojowniku!", "Jestem straznikiem tych obszarow.", "W przyszlosci bede mial dla Ciebie zadanie.", Straznik.bmp);
			if(player.y + player.h >= 400){
				if(App::button("Do zobaczenia.", button, l_button, 0, 0, 1, 0, "", 200, 100, 150, 30) && Straznik.dTimer <= 0){
					Straznik.off();
					Straznik.dTimer = 50;
				}
			}
			if(player.y + player.h < 400){
				if(App::button("Do zobaczenia.", button, l_button, 0, 0, 1, 0, "", 200, 500, 150, 30) && Straznik.dTimer <= 0){
					Straznik.off();
					Straznik.dTimer = 50;
				}
			}
		}
	}
}

void Volcano::Update(){
	if(is == true){
		App::drawBITMAP(background, 0, 0, 800, 250);
		world.Update(main_bg, plus_bg);

		if(LT::Bg_OnClick(filons_statue, "Tajemniczy Posag", 2500, 100, 100)){
			if(eq::is == true)
				eq::is = false;
			if(actquest.name != "Tajemnicza_Kartka" && actquest.a != 3 && actquest.b != 4)
				App::Message("[Dziwny posag stoi sobie w okolicach wulkanu.]", "", "", filons_statue);

			if(actquest.name == "Tajemnicza_Kartka" && actquest.a == 3 && actquest.b == 4){
				if(event_ == 0){
					App::Message("[Dziwny posag stoi sobie w okolicach wulkanu.]", "Chwileczke...", "", filons_statue);
					if(player.y + player.h >= 400){
						if(App::button("Hej! Te same symbole sa na kartce!", button, l_button, 0, 0, 1, 0, "", 310, 100, 300, 30) && runTimer <= 0){
							event_ = 1;
							eq::delArea("Poszarpana_Kartka");
							runTimer = 35;
						}
					}
					if(player.y + player.h < 400){
						if(App::button("Hej! Te same symbole sa na kartce!", button, l_button, 0, 0, 1, 0, "", 310, 500, 300, 30) && runTimer <= 0){
							event_ = 1;
							eq::delArea("Poszarpana_Kartka");
							runTimer = 35;
						}
					}
				}
				else if(event_ == 1){
					App::Message("Nagle litery na posagu sie zmieniaja...", "[Jezeli znalazles te kartke, jestes wielkim wojownikiem. Dzieki temu,", "[ze przyniosles tutaj ta kartke, uratowales swiat. Nagroda jest twoja.]", filons_statue);
				
					if(player.y + player.h >= 400){
						if(App::button("...", button, l_button, 0, 0, 1, 0, "", 310, 100, 250, 30) && runTimer <= 0){
							event_ = 0;
							player.y = 250;
							player.rot = "down";
							actquest.a++;
							runTimer = 35;
						}
					}
					if(player.y + player.h < 400){
						if(App::button("...", button, l_button, 0, 0, 1, 0, "", 310, 500, 250, 30) && runTimer <= 0){
							event_ = 0;
							player.y = 250;
							player.rot = "down";
							actquest.a++;
							runTimer = 35;
						}
					}
				}
			}
		}
		else if(player.camera.x > 2100 && player.camera.x < 2200)
		{
			if(eq::is == false)
				eq::is = true;
		}

		if(LT::Bg_OnClick(tree_i, "Las Trzech Wisni", 0, 100, 150)){
			FOTT::On();
			Off();
			player.camera.x = -5100;
			player.rot = "down";
			player.y = 250;
		}

		Npcs();
		Mobs();
	}
}

void Volcano::On(){
	is = true;

	world.isScreenScroll = true;
	is = true;

	// Muzyka

	stop_sample(music);
	music = dunger_th;
	play_sample( music, 255, 127, 750, 1 );
}

void Volcano::Off(){
	is = false;
}