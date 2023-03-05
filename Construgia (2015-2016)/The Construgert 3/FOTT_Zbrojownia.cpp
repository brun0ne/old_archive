#include "ForestOfThreeTrees.h"
#include "FOTT_Zbrojownia.h"
#include "Location_Tools.h"

#include "graphics.h"
#include "music.h"

bool FOTT_Zbroj::is;

BITMAP * FOTT_Zbroj::main_bg;
BITMAP * FOTT_Zbroj::plus_bg;
BITMAP * FOTT_Zbroj::mainWall;

npc FOTT_Zbroj::sprzedawca("Sprzedawca", 50, 225, 50, 50, 6);

void FOTT_Zbroj::GraphLoad(){
	mainWall = load_bmp("Grafika/Gra/Teren/Lokacje/ForestOfThreeTrees/Zbrojownia/wall.bmp", default_palette);

	FOTT_Zbroj::sprzedawca.start("Grafika/Gra/Teren/Lokacje/ForestOfThreeTrees/Zbrojownia/Postacie/sprzedawca.bmp");
	read();
}

void FOTT_Zbroj::read(){
	App::readFromFile("DATA/Quests/fott_zbroj.save", sprzedawca.event_[1]);
}

void FOTT_Zbroj::save(){
	App::saveToFile("DATA/Quests/fott_zbroj.save", sprzedawca.event_[1]);
}

void FOTT_Zbroj::Load(std::string name){
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

void FOTT_Zbroj::Shop(){
	App::Message("", "", "", sprzedawca.bmp);

	// POCISKI ->

	// Drewniany Pocisk

	if(player.y + player.h >= 400){
		if(App::button("Drewniany Pocisk | +AP: 30 | Ilosc: 300 | Koszt: 250 zlota", button, l_button, 0, 0, 1, 0, "", 200, 35, 600, 30) && sprzedawca.dTimer <= 0){
			if(player.gold >= 250){
				eq::pushToArea("Drewniany_Pocisk", "drewniany", 30, 0, 1, 0, 300);
				player.gold -= 250;
				sprzedawca.off();
			}
			else
				sprzedawca.event_[0] = 2;

			sprzedawca.dTimer = 50;
		}
	}
	if(player.y + player.h < 400){
		if(App::button("Drewniany Pocisk | +AP: 30 | Ilosc: 300 | Koszt: 250 zlota", button, l_button, 0, 0, 1, 0, "", 200, 435, 600, 30) && sprzedawca.dTimer <= 0){
			if(player.gold >= 250){
				eq::pushToArea("Drewniany_Pocisk", "drewniany", 30, 0, 1, 0, 300);
				player.gold -= 250;
				sprzedawca.off();
			}
			else
				sprzedawca.event_[0] = 2;

			sprzedawca.dTimer = 50;
		}
	}
	// <---------------------------------------------------------------------------------------------------------------
	
	// Drewniany Pociskk Wzmocniony Zywica
	if(player.y + player.h >= 400){
		if(App::button("Drewniany Pocisk Wzmocniony Zywica | +AP: 40 |  Ilosc: 300 | Koszt: 350 zlota", button, l_button, 0, 0, 1, 0, "", 200, 70, 600, 30) && sprzedawca.dTimer <= 0){
			if(player.gold >= 350){
				eq::pushToArea("Drewniany_Pocisk_Wzmocniony_Zywica", "drewniany_ex", 40, 0, 1, 0, 300);
				player.gold -= 350;
				sprzedawca.off();
			}
			else
				sprzedawca.event_[0] = 2;

			sprzedawca.dTimer = 50;
		}
	}
	if(player.y + player.h < 400){
		if(App::button("Drewniany Pocisk Wzmocniony Zywica | +AP: 40 |  Ilosc: 300 | Koszt: 350 zlota", button, l_button, 0, 0, 1, 0, "", 200, 470, 600, 30) && sprzedawca.dTimer <= 0){
			if(player.gold >= 350){
				eq::pushToArea("Drewniany_Pocisk_Wzmocniony_Zywica", "drewniany_ex", 40, 0, 1, 0, 300);
				player.gold -= 350;
				sprzedawca.off();
			}
			else
				sprzedawca.event_[0] = 2;

			sprzedawca.dTimer = 50;
		}
	}
	// <---------------------------------------------------------------------------------------------------------------
	
	// Ultramocny Lesny Pocisk
	if(player.y + player.h >= 400){
		if(App::button("Ultramocny Lesny Pocisk | +AP: 100 |  Ilosc: 10 | Koszt: 500 zlota", button, l_button, 0, 0, 1, 0, "", 200, 105, 600, 30) && sprzedawca.dTimer <= 0){
			if(player.gold >= 500){
				eq::pushToArea("Ultramocny_Lesny_Pocisk", "ultra_lesny", 100, 0, 1, 0, 10);
				player.gold -= 500;
				sprzedawca.off();
			}
			else
				sprzedawca.event_[0] = 2;

			sprzedawca.dTimer = 50;
		}
	}
	if(player.y + player.h < 400){
		if(App::button("Ultramocny Lesny Pocisk | +AP: 100 |  Ilosc: 10 | Koszt: 500 zlota", button, l_button, 0, 0, 1, 0, "", 200, 505, 600, 30) && sprzedawca.dTimer <= 0){
			if(player.gold >= 500){
				eq::pushToArea("Ultramocny_Lesny_Pocisk", "ultra_lesny", 100, 0, 1, 0, 10);
				player.gold -= 500;
				sprzedawca.off();
			}
			else
				sprzedawca.event_[0] = 2;

			sprzedawca.dTimer = 50;
		}
	}
	// <---------------------------------------------------------------------------------------------------------------
	

	// EXIT ->

	if(player.y + player.h >= 400){
		if(App::button("Jednak sie rozmyslilem. Bywaj!", button, l_button, 0, 0, 1, 0, "", 500, 140, 285, 30) && sprzedawca.dTimer <= 0){
			sprzedawca.off();
			sprzedawca.dTimer = 50;
		}
	}
	if(player.y + player.h < 400){
		if(App::button("Jednak sie rozmyslilem. Bywaj!", button, l_button, 0, 0, 1, 0, "", 500, 540, 285, 30) && sprzedawca.dTimer <= 0){
			sprzedawca.off();
			sprzedawca.dTimer = 50;
		}
	}
}

void FOTT_Zbroj::Npcs(){
	sprzedawca.update();

	// Dialog -->
	if(sprzedawca.active){
		if(sprzedawca.event_[0] == 0){
			App::Message("Witaj!", "Jestem sprzedawca w tej oto Lesnej Zbrojowni.", "Znajdziesz tu roznorakie pociski prosto z pod mojej reki.", sprzedawca.bmp);

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
			//////////
			if(player.y + player.h >= 400){
				if(App::button("Pokaz mi wiec co masz do zaoferowania.", button, l_button, 0, 0, 1, 0, "", 200, 135, 375, 30) && sprzedawca.dTimer <= 0){
					sprzedawca.event_[0] = 1;
					sprzedawca.dTimer = 50;
				}
			}
			if(player.y + player.h < 400){
				if(App::button("Pokaz mi wiec co masz do zaoferowania.", button, l_button, 0, 0, 1, 0, "", 200, 535, 375, 30) && sprzedawca.dTimer <= 0){
					sprzedawca.event_[0] = 1;
					sprzedawca.dTimer = 50;
				}
			}
			//////////////////////////////////
			if(sprzedawca.event_[1] != 1){
				if(player.y + player.h >= 400){
					if(App::button("Szukam pracy.", button, l_button, 0, 0, 1, 0, "", 335, 100, 120, 30) && sprzedawca.dTimer <= 0){
						sprzedawca.event_[0] = 2;
						sprzedawca.dTimer = 50;
					}
				}
				if(player.y + player.h < 400){
					if(App::button("Szukam pracy.", button, l_button, 0, 0, 1, 0, "", 335, 500, 220, 30) && sprzedawca.dTimer <= 0){
						sprzedawca.event_[0] = 2;
						sprzedawca.dTimer = 50;
					}
				}
			}
			//////////////////////////////////
			if(actquest.name == "Tajemnicza_Kartka" && actquest.a == 0 && actquest.text == "Poszukaj_kuzyna_Carcco."){
				if(player.y + player.h >= 400){
					if(App::button("Czy to ty jestes kuzynem Carcco?", button, l_button, 0, 0, 1, 0, "", 310, 100, 250, 30) && sprzedawca.dTimer <= 0){
						sprzedawca.event_[0] = 3;
						sprzedawca.dTimer = 50;
					}
				}
				if(player.y + player.h < 400){
					if(App::button("Czy to ty jestes kuzynem Carcco?", button, l_button, 0, 0, 1, 0, "", 310, 500, 250, 30) && sprzedawca.dTimer <= 0){
						sprzedawca.event_[0] = 3;
						sprzedawca.dTimer = 50;
					}
				}
			}
			//////////////////////////////////
			if(actquest.name == "Tajemnicza_Kartka" && actquest.a == 12 && actquest.text == "Zabij_12_potworow_dla_Leonarda."){
				if(player.y + player.h >= 400){
					if(App::button("Zabilem 12 potworow.", button, l_button, 0, 0, 1, 0, "", 310, 100, 250, 30) && sprzedawca.dTimer <= 0){
						sprzedawca.event_[0] = 5;
						actquest.cancelNo = false;
						actquest.finish = false;
						sprzedawca.dTimer = 50;
					}
				}
				if(player.y + player.h < 400){
					if(App::button("Zabilem 12 potworow.", button, l_button, 0, 0, 1, 0, "", 310, 500, 250, 30) && sprzedawca.dTimer <= 0){
						sprzedawca.event_[0] = 5;
						actquest.cancelNo = false;
						actquest.finish = false;
						sprzedawca.dTimer = 50;
					}
				}
			}
		}
		if(sprzedawca.event_[0] == 2){
			App::Message("Akurat szukam kogos kto by mi pomogl.", "Czy moglbys zabic dla mnie kilka potworow z tego lasu?", "Bardzo przeszkadaja mi w scinaniu i sadzeniu drzew.", sprzedawca.bmp);

			/////////
			if(player.y + player.h >= 400){
				if(App::button("Teraz nie mam czasu, bywaj!", button, l_button, 0, 0, 1, 0, "", 200, 100, 375, 30) && sprzedawca.dTimer <= 0){
					sprzedawca.off();
					sprzedawca.dTimer = 50;
				}
			}
			if(player.y + player.h < 400){
				if(App::button("Teraz nie mam czasu, bywaj!", button, l_button, 0, 0, 1, 0, "", 200, 500, 375, 30) && sprzedawca.dTimer <= 0){
					sprzedawca.off();
					sprzedawca.dTimer = 50;
				}
			}
			//////////
			if(player.y + player.h >= 400){
				if(App::button("Dobrze, zrobie to.", button, l_button, 0, 0, 1, 0, "", 200, 135, 375, 30) && sprzedawca.dTimer <= 0){
					actquest.replace("Quest_Sprzedawcy:_Zabij_potwory_z_lasu.", "Przeszkadaja_mu_w_scinaniu_drzew.", 200, 350, 0, 6);
					if(actquest.name == "Quest_Sprzedawcy:_Zabij_potwory_z_lasu."){
						sprzedawca.event_[1] = 1;
					}
					sprzedawca.off();
					sprzedawca.dTimer = 50;
				}
			}
			if(player.y + player.h < 400){
				if(App::button("Dobrze, zrobie to.", button, l_button, 0, 0, 1, 0, "", 200, 535, 375, 30) && sprzedawca.dTimer <= 0){
					Quest_System.push("Quest_Sprzedawcy:_Zabij_potwory_z_lasu.", "Przeszkadaja_mu_w_scinaniu_drzew.", 200, 350, 0, 6);
					if(actquest.name == "Quest_Sprzedawcy:_Zabij_potwory_z_lasu."){
						sprzedawca.event_[1] = 1;
					}
					sprzedawca.off();
					sprzedawca.dTimer = 50;
				}
			}
		}
		else if(sprzedawca.event_[0] == 3){
			App::Message("Ach, spotkales Carcco, tak? Oczywiscie, tak, nazywam sie Leonard i", "jestem kuzynem Carrco. Carcco cie do mnie wyslal?", "", sprzedawca.bmp);

			if(player.y + player.h >= 400){
				if(App::button("Tak.. Spojrz na to.", button, l_button, 0, 0, 1, 0, "", 200, 100, 375, 30) && sprzedawca.dTimer <= 0){
					sprzedawca.event_[0] = 4;
					sprzedawca.dTimer = 50;
				}
			}
			if(player.y + player.h < 400){
				if(App::button("Tak.. Spojrz na to.", button, l_button, 0, 0, 1, 0, "", 200, 500, 375, 30) && sprzedawca.dTimer <= 0){
					sprzedawca.event_[0] = 4;
					sprzedawca.dTimer = 50;
				}
			}
		}
		else if(sprzedawca.event_[0] == 4){
			App::Message("Och! Tak, wiem co to jest!", "Powiedzialym ci ale.. najpierw musisz cos dla mnie zrobic.", "Zabij 12 potworow z tego lasu, to wyjawie ci tajemnice tej kartki.", sprzedawca.bmp);
			
			if(player.y + player.h >= 400){
				if(App::button("Chyba nie mam wyboru...", button, l_button, 0, 0, 1, 0, "", 200, 100, 375, 30) && sprzedawca.dTimer <= 0){
					sprzedawca.event_[0] = 0;
					actquest.a = 0;
					actquest.b = 12;
					actquest.text = "Zabij_12_potworow_dla_Leonarda.";
					actquest.cancelNo = true;
					sprzedawca.dTimer = 50;
				}
			}
			if(player.y + player.h < 400){
				if(App::button("Chyba nie mam wyboru...", button, l_button, 0, 0, 1, 0, "", 200, 500, 375, 30) && sprzedawca.dTimer <= 0){
					sprzedawca.event_[0] = 0;
					actquest.a = 0;
					actquest.b = 12;
					actquest.text = "Zabij_12_potworow_dla_Leonarda.";
					actquest.cancelNo = true;
					sprzedawca.dTimer = 50;
				}
			}
		}
		else if(sprzedawca.event_[0] == 5){
			App::Message("Dobrze. Wiec kartka, ktora znalazles, jest Kartka Wyrzutu.", "Pewien czarodziej.. to znaczy JA zgubilem ja wiele lat temu.", "Kartka skrywa zagadke, ktora sama wytworzyla. Ty dasz rade ja rozwiazac!", sprzedawca.bmp);
		
			if(player.y + player.h >= 400){
				if(App::button("Mow dalej.", button, l_button, 0, 0, 1, 0, "", 200, 100, 375, 30) && sprzedawca.dTimer <= 0){
					sprzedawca.event_[0] = 6;
					sprzedawca.dTimer = 50;
				}
			}
			if(player.y + player.h < 400){
				if(App::button("Mow dalej.", button, l_button, 0, 0, 1, 0, "", 200, 500, 375, 30) && sprzedawca.dTimer <= 0){
					sprzedawca.event_[0] = 6;
					sprzedawca.dTimer = 50;
				}
			}
		}
		else if(sprzedawca.event_[0] == 6){
			App::Message("Podpowiedzia sa napisy i znaki na kartce.", "Aktualnie wiem tylko tyle, ze ma cos z tym wspolnego jakis posag.", "A teraz ruszaj dalej! Bywaj!", sprzedawca.bmp);
			
			if(player.y + player.h >= 400){
				if(App::button("Dziekuje za wszystko! Zegnaj!", button, l_button, 0, 0, 1, 0, "", 200, 100, 375, 30) && sprzedawca.dTimer <= 0){
					actquest.a = 3;
					actquest.b = 4;
					actquest.text = "Moze_posag_bedzie_blisko_Wulkanu?";
					actquest.finish = false;
					sprzedawca.off();
					sprzedawca.dTimer = 50;
				}
			}
			if(player.y + player.h < 400){
				if(App::button("Dziekuje za wszystko! Zegnaj!", button, l_button, 0, 0, 1, 0, "", 200, 500, 375, 30) && sprzedawca.dTimer <= 0){
					actquest.a = 3;
					actquest.b = 4;
					actquest.text = "Moze_posag_bedzie_blisko_Wulkanu?";
					actquest.finish = false;
					sprzedawca.off();
					sprzedawca.dTimer = 50;
					sprzedawca.dTimer = 50;
				}
			}
		}
	}
	// <-- Dialog

	if(sprzedawca.event_[0] == 1)
		Shop();
}

void FOTT_Zbroj::On(){
	world.isScreenScroll = false;
	is = true;
}

void FOTT_Zbroj::Off(){
	is = false;

	// Muzyka

	/*stop_sample(music);
	music = dunger_th;
	play_sample( music, 255, 127, 750, 1 );*/
}

void FOTT_Zbroj::Update(){
	if(is == true){
		App::drawBITMAP(mainWall, 0, 0, 800, 250);
		world.Update(main_bg, plus_bg);

		App::drawBITMAP(siekiera, 200, 100, 100, 100);
		App::drawBITMAP(siekiera, 325, 100, 100, 100);
		App::drawBITMAP(siekiera, 450, 100, 100, 100);

		LT::Obj_Not(drewno, 700, 600 - world.plane_h, 100, 100);
		LT::Obj_Not(klapa_drewno, 50, 500, 50, 50);

		//Teleport -->
		if(LT::Dn_Enter(350 + player.camera.x, 100)){
			FOTT::On();
			Off();

			player.y = 600 - world.plane_h;
			player.x = 400 - player.w;
			player.rot = "up";
		}
		//<-- Teleport

		Npcs();
	}
}