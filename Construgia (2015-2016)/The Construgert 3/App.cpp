#include "main.h"

bool textOn = true;

BITMAP * default_;

void App::init(){
	default_ = load_bmp("Grafika/Gra/Default/brightArea.bmp", default_palette);
}

// -->

void App::createMask(){
	popupBufor = create_bitmap(800, 600);
	clear_to_color(popupBufor, makecol(255, 0, 255));

	mask = create_bitmap(800, 600);
	clear_to_color(mask, makecol(0, 0, 0));
}

void App::drawBufor(){
//	draw_sprite(bufor, popupBufor, 0, 0);

//	draw_trans_sprite(bufor, mask, 0, 0);
	
	draw_sprite(screen, bufor, 0, 0);

	clear_to_color(popupBufor, makecol(255, 0, 255));
}

void App::setLight(int light){
	set_trans_blender( 0, 0, 0, light ); //przezroczystoœæ bmp maska (od 0-255)
}

void App::setLightColor(int r, int g, int b){
	clear_to_color(mask, makecol(r, g, b));
}

// <--

bool App::onSlide(int x, int y, int w, int h){
	if(mouse_x >= x && mouse_x <= x+w && mouse_y >= y && mouse_y <= y+h){
		return true;
	}
	return false;
}

bool App::onClick(int x, int y, int w, int h){
	if(mouse_x >= x && mouse_x <= x+w && mouse_y >= y && mouse_y <= y+h && mouse_b == 1){
		return true;
	}
	return false;
}

void App::drawBITMAP(BITMAP * bitmap, int x, int y, int w, int h){
	stretch_sprite(bufor, bitmap, x, y, w, h);
}

void App::drawText(const char * text, int x, int y){
	textprintf_ex(bufor, font, x, y, makecol(255, 255, 255), -1, text);
}

void App::drawVariableText(std::string text, int x, int y, int var1, int color){
	if(var1 != -1){
		if(color == 3) // ZIELONY
			textprintf_ex(bufor, font, x, y, makecol(0, 150, 0), -1, "%s%d", text.c_str(), var1);
		if(color == 2) // NIEBIESKI
			textprintf_ex(bufor, font, x, y, makecol(0, 0, 255), -1, "%s%d", text.c_str(), var1);
		if(color == 1) // BIA£Y
			textprintf_ex(bufor, font, x, y, makecol(255, 255, 255), -1, "%s%d", text.c_str(), var1);
		if(color == 0) // CZERWONY
			textprintf_ex(bufor, font, x, y, makecol(255, 0, 0), -1, "%s%d", text.c_str(), var1);
		if(color == -1) // CZARNY
			textprintf_ex(bufor, font, x, y, makecol(0, 0, 0), -1, "%s%d", text.c_str(), var1);
	}
	else
	{
		if(color == 3) // ZIELONY
			textprintf_ex(bufor, font, x, y, makecol(0, 150, 0), -1, "%s", text.c_str(), var1);
		if(color == 2) // NIEBIESKI
			textprintf_ex(bufor, font, x, y, makecol(0, 0, 255), -1, "%s", text.c_str(), var1);
		if(color == 1) // BIA£Y
			textprintf_ex(bufor, font, x, y, makecol(255, 255, 255), -1, "%s", text.c_str(), var1);
		if(color == 0) // CZERWONY
			textprintf_ex(bufor, font, x, y, makecol(255, 0, 0), -1, "%s", text.c_str(), var1);
		if(color == -1) // CZARNY
			textprintf_ex(bufor, font, x, y, makecol(0, 0, 0), -1, "%s", text.c_str(), var1);
	}
}

void App::drawViariableStringText(std::string text, int x, int y, std::string zmienna){
	textprintf_ex(bufor, font, x, y, makecol(255, 255, 255), -1, "%s%s", text.c_str(), zmienna.c_str());
}

void App::readKey(std::string & text, bool ON){
	if(textOn && ON){
		if(key[KEY_Q]){
			text=text+"Q";
			textOn = false;
		}
		if(key[KEY_W]){
			text=text+"W";
			textOn = false;
		}
		if(key[KEY_E]){
			text=text+"E";
			textOn = false;
		}
		if(key[KEY_R]){
			text=text+"R";
			textOn = false;
		}
		if(key[KEY_T]){
			text=text+"T";
			textOn = false;
		}
		if(key[KEY_Y]){
			text=text+"Y";
			textOn = false;
		}
		if(key[KEY_U]){
			text=text+"U";
			textOn = false;
		}
		if(key[KEY_I]){
			text=text+"I";
			textOn = false;
		}
		if(key[KEY_O]){
			text=text+"O";
			textOn = false;
		}
		if(key[KEY_P]){
			text=text+"P";
			textOn = false;
		}
		if(key[KEY_A]){
			text=text+"A";
			textOn = false;
		}
		if(key[KEY_S]){
			text=text+"S";
			textOn = false;
		}
		if(key[KEY_D]){
			text=text+"D";
			textOn = false;
		}
		if(key[KEY_F]){
			text=text+"F";
			textOn = false;
		}
		if(key[KEY_G]){
			text=text+"G";
			textOn = false;
		}
		if(key[KEY_H]){
			text=text+"H";
			textOn = false;
		}
		if(key[KEY_J]){
			text=text+"J";
			textOn = false;
		}
		if(key[KEY_K]){
			text=text+"K";
			textOn = false;
		}
		if(key[KEY_L]){
			text=text+"L";
			textOn = false;
		}
		if(key[KEY_Z]){
			text=text+"Z";
			textOn = false;
		}
		if(key[KEY_X]){
			text=text+"X";
			textOn = false;
		}
		if(key[KEY_C]){
			text=text+"C";
			textOn = false;
		}
		if(key[KEY_V]){
			text=text+"V";
			textOn = false;
		}
		if(key[KEY_B]){
			text=text+"B";
			textOn = false;
		}
		if(key[KEY_N]){
			text=text+"N";
			textOn = false;
		}
		if(key[KEY_M]){
			text=text+"M";
			textOn = false;
		}
	}

	if(key[KEY_SPACE] && textOn){
		text=text+" ";
		textOn = false;
	}

	if(!key[KEY_SPACE] && !key[KEY_Q] && !key[KEY_W] && !key[KEY_E] && !key[KEY_R] && !key[KEY_T] && !key[KEY_Y] && !key[KEY_U] && !key[KEY_I] && !key[KEY_O] && !key[KEY_P] && !key[KEY_A] && !key[KEY_S] && !key[KEY_D] && !key[KEY_F] && !key[KEY_G] && !key[KEY_H] && !key[KEY_J] && !key[KEY_K] && !key[KEY_L] && !key[KEY_Z] && !key[KEY_X] && !key[KEY_C] && !key[KEY_V] && !key[KEY_B] && !key[KEY_N] && !key[KEY_M])textOn = true;

	if(key[KEY_BACKSPACE] || key[KEY_DEL]){
		text.erase();
	}
}

void App::saveToFile(const char * sciezka, int zmienna){
	std::ofstream plik;
	plik.open(sciezka);
	plik<<zmienna<<std::endl;
}

void App::readFromFile(std::string sciezka, int & zmienna){
	std::ifstream plik;
	plik.open(sciezka);
	plik >> zmienna;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool App::button(const char * textC, BITMAP * defaultBitmap, BITMAP * onSlideBitmap, bool varOn, bool stringOn, bool center, int var, std::string varS, int xx, int yy, int ww, int hh){
	if(ww == 0)ww = defaultBitmap->w;
	if(hh == 0)hh = defaultBitmap->h;

	std::string text = textC;
	
	if(App::onSlide(xx, yy, ww, hh)){
		App::drawBITMAP(onSlideBitmap, xx, yy, ww, hh);
	}
	else
	{
		App::drawBITMAP(defaultBitmap, xx, yy, ww, hh);
	}
	if(center){
		if(varOn){
			if(stringOn == false)
				App::drawVariableText( textC, xx + ( ww / 2 ) - text.length() / 2 * 7, yy+( hh / 2.5f ), var, 1 );
			else App::drawViariableStringText( textC, xx + ( ww / 2 ) - text.length() / 2 * 7, yy+( hh / 2.5f ), varS );
		}
		else
		{
			App::drawText( textC, xx + ( ww / 2 ) - text.length() / 2 * 7, yy+( hh / 2.5f ) ); // x = (szerokosc / 2) - dlugosc tekstu / 2 * 7
		}
	}
	else
	{
		if(varOn){
			if(stringOn == false)
				App::drawVariableText( textC, xx + 4, yy+( hh / 2.5f ), var, 1 );
			else App::drawViariableStringText( textC, xx + 4, yy+( hh / 2.5f ), varS );
		}
		else
		{
			App::drawText( textC, xx + 5, yy+( hh / 2.5f ) );
		}
	}

	if(App::onClick(xx, yy, ww, hh)){
		return true;
	}
	return false;
}

void App::drawBITMAPtext(BITMAP * bitmap, const char * text, bool zmienna, int endl, int x, int y, int w, int h, int var, bool popup){
	if(!popup){
		App::drawBITMAP(bitmap, x, y, w, h);

		int textY = y;

		std::string textS = text;

		while(endl > 0){
			textY += 10;

			endl--;
		}

		if(textY == y)
			textY += ( h / 2.5f );

		if(zmienna){
			App::drawVariableText(textS, x + ( w / 2 ) - textS.length() / 2 * 7, textY, var, 1);
		}
		else
		{
			App::drawText(text, x + ( w / 2 ) - textS.length() / 2 * 7, textY);
		}
	}
	else
	{
		stretch_sprite(popupBufor, bitmap, x, y, w, h);

		int textY = y;

		std::string textS = text;

		while(endl > 0){
			textY += 10;

			endl--;
		}

		if(textY == y)
			textY += ( h / 2.5f );

		if(zmienna){
			textprintf_ex(popupBufor, font, x + ( w / 2 ) - textS.length() / 2 * 7, textY, makecol(255, 255, 255), -1, text);
		}
		else
		{
			textprintf_ex(popupBufor, font, x + ( w / 2 ) - textS.length() / 2 * 7, textY, makecol(255, 255, 255), -1, text);
		}
	}
}

void App::textArea(std::string & text, BITMAP * bitmap, int x, int y, int w, int h){
	if(text.length() <= 15){
		readKey(text, true);
	}
	else
	{
		readKey(text, false);
	}

	w = 20;

	w += (text.length() * 10);

	x = (325+150) - (w / 2); //x = (srodek ekranu) - (szerokosc / 2);

	App::drawBITMAPtext(bitmap, text.c_str(), false, 0, x, y, w, h, 0, false);
}

void App::popup(std::string text, bool isVar){
	if(isVar){
		App::drawBITMAP(default_, 300, 250, 200, 100);
		App::drawText(text.c_str(), 300+10, 250+10);

		if( App::button("OK", default_, default_, 0, 0, 1, 0, "", 310, 260, 100, 35) ){
			isVar = false;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Methods for BGC 2D Engine  (Object Brunon C++ Algorithms 2D Engine)

void App::Player_Collision(int x, int y, int w, int h){
	if(world.isScreenScroll){
		//RIGHT COLLISION ( object right wall, player left wall )
		if( ( player.y <= ( ( y  ) + h ) ) && ( player.y + player.h >= ( y ) ) )
		{
			if( ( player.x <= ( x + w ) ) && ( player.x >= x + w / 2 ) ){
				player.camera.x += 1 - world.speed;
				if(world.isScreenScroll)
					world.plus_bg_x -= (1 - world.speed);
				world.speedPh = 0;
			}
			else
			{
				world.speedPh = 1 - world.speed;
			}
		}
		else
		{
			world.speedPh = 1 - world.speed;
		}
		//LEFT COLLISION ( object left wall, player right wall )
		if( ( player.y <= ( ( y ) + h ) ) && ( player.y + player.h >= ( y ) ) )
		{
			if( ( player.x + player.w ) >= x && ( player.x + player.w <= x + w / 2 ) ){
				player.camera.x -= 1 - world.speed;
				if(world.isScreenScroll)
					world.plus_bg_x += (1 - world.speed);
				world.speedPh = 0;
			}
			else
			{
				world.speedPh = 1 - world.speed;
			}
		}
		else
		{
			world.speedPh = 1 - world.speed;
		}
		//UP COLLISION ( object up wall, player down wall )
		if( ( player.x <= ( x + w ) && ( player.x + player.w >= x ) ) )
		{
			if( ( ( player.y + player.h ) >= y ) && ( player.y + player.h <= y + h / 2 ) ){
				player.y -= 1 - world.speed;
			}
		}
		//DOWN COLLISION ( object down wall, player up wall )
		if( ( player.x <= ( x + w ) ) && ( player.x + player.w >= x ) )
		{
			if( player.y <= ( y + h ) && player.y >= y + h / 2){
				player.y += 1 - world.speed;
			}
		}
	}
	else
	{
		//RIGHT COLLISION ( object right wall, player left wall )
		if( ( player.y <= ( ( y  ) + h ) ) && ( player.y + player.h >= ( y ) ) )
		{
			if( ( player.x <= ( x + w ) ) && ( player.x >= x + w / 2 ) ){
				player.x += 1 - world.speed;
			}
		}
		//LEFT COLLISION ( object left wall, player right wall )
		if( ( player.y <= ( ( y ) + h ) ) && ( player.y + player.h >= ( y ) ) )
		{
			if( ( player.x + player.w ) >= x && ( player.x + player.w <= x + w / 2 ) ){
				player.x -= 1 - world.speed;
			}
		}
		//UP COLLISION ( object up wall, player down wall )
		if( ( player.x <= ( x + w ) && ( player.x + player.w >= x ) ) )
		{
			if( ( ( player.y + player.h ) >= y ) && ( player.y + player.h <= y + h / 2 ) ){
				player.y -= 1 - world.speed;
			}
		}
		//DOWN COLLISION ( object down wall, player up wall )
		if( ( player.x <= ( x + w ) ) && ( player.x + player.w >= x ) )
		{
			if( player.y <= ( y + h ) && player.y >= y + h / 2){
				player.y += 1 - world.speed;
			}
		}
	}
}

void App::Message(std::string message, std::string message2, std::string message3, BITMAP * bmp){
	if(player.y + player.h >= 400){
		App::drawBITMAP(default_, 0, 0, 800, 200);

		if(bmp == NULL){
			App::drawText(message.c_str(), 80, 50);
			App::drawText(message2.c_str(), 80, 60);
			App::drawText(message3.c_str(), 80, 70);
		}
		else
		{
			App::drawText(message.c_str(), 220, 50);
			App::drawText(message2.c_str(), 220, 60);
			App::drawText(message3.c_str(), 220, 70);
			App::drawBITMAP(bmp, 10, 25, 150, 150);
		}
	}
	else
	{
		App::drawBITMAP(default_, 0, 400, 800, 200);

		if(bmp == NULL){
			App::drawText(message.c_str(), 80, 450);
			App::drawText(message2.c_str(), 80, 460);
			App::drawText(message3.c_str(), 80, 470);
		}
		else
		{
			App::drawText(message.c_str(), 220, 450);
			App::drawText(message2.c_str(), 220, 460);
			App::drawText(message3.c_str(), 220, 470);
			App::drawBITMAP(bmp, 10, 425, 150, 150);
		}
	}
}