#include "Location_Tools.h"

BITMAP * popup_bmp;
BITMAP * enter_bmp;

void LT::init(){
	popup_bmp = load_bmp("Grafika/Gra/Default/area.bmp", default_palette);
	enter_bmp = load_bmp("Grafika/Gra/Default/enter.bmp", default_palette);
}

void LT::Bg_Not(BITMAP * bmp, int x, int w, int h){
	if(w == 0)
		w = bmp->w;
	if(h == 0)
		h = bmp->h;
	App::drawBITMAP(bmp, x - player.camera.x, 600 - world.plane_h - h + 20, w, h);
}

bool LT::Bg_OnClick(BITMAP * bmp, std::string name, int x, int w, int h){
	if(w == 0)
		w = bmp->w;
	if(h == 0)
		h = bmp->h;

	if(world.isScreenScroll)
		App::drawBITMAP(bmp, x - player.camera.x, 600 - world.plane_h - h + 20, w, h);
	else
		App::drawBITMAP(bmp, x - player.camera.x, 600 - world.plane_h - h, w, h);

	Bg_Popup(bmp, name, x, w, h);

	if( player.x + player.w >= x - player.camera.x + w / 3 && player.x <= x + w - player.camera.x - w / 3 && player.y <= 600 - world.plane_h && player.rot == "up"){
		return true;
	}

	return false;
}

bool LT::Bg_OnStay(BITMAP * bmp, int x, int w, int h){
	if(w == 0)
		w = bmp->w;
	if(h == 0)
		h = bmp->h;

	App::drawBITMAP(bmp, x - player.camera.x, 600 - world.plane_h - h + 20, w + mouse_z * 2, h + mouse_z * 2);

	if( player.x + player.w >= x - player.camera.x && player.x <= x + w - player.camera.x ){
		return true;
	}

	return false;
}

void LT::Bg_Popup(BITMAP * bmp, std::string popupText, int x, int w, int h){
	if(w == 0)
		w = bmp->w;
	if(h == 0)
		h = bmp->h;

	if( player.x + player.w >= x - player.camera.x + w / 3 && player.x <= x + w - player.camera.x - w / 3 ){
		App::drawBITMAPtext(popup_bmp, popupText.c_str(), false, 0, ( 800 / 2 ) - ( ( popupText.length() + 3 ) * 5 ), 40, ( popupText.length() + 3 ) * 10, 20, 0, true);
	}
}

void LT::Obj_Not(BITMAP * bmp, int x, int y, int w, int h){
	App::drawBITMAP(bmp, x, y, w, h);

	App::Player_Collision(x, y, w, h);
}

void LT::Pn_Not(BITMAP * bmp, int x, int y, int w, int h){
	if(w == 0)
		w = bmp->w;
	if(h == 0)
		h = bmp->h;

	if( y < ( 600 - world.plane_h ) + 20 )
		y = 600 - world.plane_h + 20;

	App::drawBITMAP(bmp, x - player.camera.x, y, w, h);
}

bool LT::Dn_Enter(int x, int w){
	App::drawBITMAP(enter_bmp, x - player.camera.x, 600 - player.h, w, 50);

	if(player.x + player.w >= x - player.camera.x && player.x <= x - player.camera.x + w && player.y + ( player.h / 2 ) >= 600 - player.h){
		return true;
	}
	return false;
}