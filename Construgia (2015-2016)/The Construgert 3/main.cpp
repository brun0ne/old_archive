#include "main.h"
#include "graphics.h"
#include "music.h"

BITMAP * bufor;

int main(){
	allegro_init();
    install_keyboard();
    set_color_depth( 32 );
    set_gfx_mode( GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0 );
    install_mouse();
    show_mouse( screen );
    unscare_mouse();
	install_sound( DIGI_AUTODETECT, MIDI_AUTODETECT, "" );
	set_volume( 255, 255 );
	set_display_switch_mode(SWITCH_BACKGROUND);

	set_window_title("Construgia v.0.1.9 | by Brunon Blok"); 
	
	bufor = create_bitmap(800, 600);

	music = load_sample( "Main_Theme.wav" );
	
	BITMAP * black = create_bitmap(800, 600);
	clear_to_color(black, makecol(0, 0, 0));
	
	draw_sprite(screen, black, 0, 0);
	textprintf_ex(screen, font, 200, 294, makecol(255, 255, 255), -1, "Powered by (C) BGC Engine");
	textprintf_ex(screen, font, 200, 304, makecol(255, 255, 255), -1, "(C) BGC Engine is created only by Brunon Blok | All rights reserved");

	rest(3000);

	draw_sprite(screen, black, 0, 0);
	textprintf_ex(screen, font, 200, 294, makecol(255, 255, 255), -1, "(C) Construgia is created only by Brunon Blok | All rights reserved");

	rest(3000);
	
	BITMAP * menuBack = load_bmp("Grafika/menuBackground.bmp", default_palette);

	graph_init();
	music_init();

	int first = 0;
	App::readFromFile("DATA/never.save", first);

	play_sample( music, 255, 127, 1000, 1 );

	while(!key[KEY_ESC]){
		stretch_sprite(bufor, menuBack, 0, 0, 800, 600);
		textprintf_ex(bufor, font, 0, 0, makecol(0, 0, 0), -1, "v.0.1.9");

		if(App::button("Nowa gra", button, l_button, 0, 0, 1, 0, "", 100, 100, 150, 35)){
			stop_sample(music);
			App::saveToFile("DATA/never.save", 1);
			game();
			allegro_exit();
			return 0;
		}
		if(first == 1){
			if(App::button("Kontynuuj", button, button, 0, 0, 1, 0, "", 100, 145, 150, 35))
				;
		}
		else
		{
			if(App::button("Kontynuuj", button, l_button, 0, 0, 1, 0, "", 100, 145, 150, 35)){
				stop_sample(music);
				game();
				allegro_exit();
				return 0;
			}
		}
		if(App::button("Wyjdz", button, l_button, 0, 0, 1, 0, "", 100, 190, 150, 35)){
			stop_sample(music);
			allegro_exit();
			return 0;
		}
		draw_sprite(screen, bufor, 0, 0);
	}

	allegro_exit();
	return 0;
}
END_OF_MAIN();