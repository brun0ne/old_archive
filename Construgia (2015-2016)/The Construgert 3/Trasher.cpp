#include "main.h"
#include "graphics.h"
#include "Location_Tools.h"

bool Trasher::msg = false;
bool Trasher::work = false;

void Trasher::MSG_Op(){
	App::Message("[Widzisz kosz, czy chcesz cos wyrzucic?]", "", "", bin);

	if(player.y + player.h >= 400){
			if(App::button("Tak.", button, l_button, 0, 0, 1, 0, "", 200, 100, 425, 30)){
				work = true;
				msg = false;
				eq::delWork = true;
			}
		}
	if(player.y + player.h < 400){
		if(App::button("Tak.", button, l_button, 0, 0, 1, 0, "", 200, 500, 425, 30)){
			work = true;
			msg = false;
			eq::delWork = true;
		}
	}
	////
	if(player.y + player.h >= 400){
			if(App::button("Nie.", button, l_button, 0, 0, 1, 0, "", 200, 140, 425, 30)){
				msg = false;
				player.y = 250;
				player.rot = "down";
				eq::delWork = false;
			}
		}
	if(player.y + player.h < 400){
		if(App::button("Nie.", button, l_button, 0, 0, 1, 0, "", 200, 540, 425, 30)){
			msg = false;
			player.y = 250;
			player.rot = "down";
			eq::delWork = false;
		}
	}
}

void Trasher::D_GUI(){
	App::drawBITMAP(Skills::mainGraph, 0, 0, 650, 600);

	App::drawText("Kilknij myszka na przedmiot w eq, ktory chcesz wyrzucic.", 100, 100);

	if(App::button("Zamknij", button, l_button, false, false, true, 0, "", 350, 200, 100, 35)){
		msg = false;
		player.y = 250;
		player.rot = "down";
		eq::delWork = false;
		work = false;
	}
}

void Trasher::D_LItem(int x){
	if(LT::Bg_OnClick(bin, "Kosz na smieci", x, 75, 75)){
		msg = true;
	}
	else{
		msg = false;
	}
}

void Trasher::Update(){
	if(msg)
		MSG_Op();
	if(work)
		D_GUI();
}