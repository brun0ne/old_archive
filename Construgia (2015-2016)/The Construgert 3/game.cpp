#include "main.h"
#include "ConCity.h"
#include "ForestOfThreeTrees.h"
#include "Location_Tools.h"
#include "ConCity_BrunonCave.h"
#include "ConCity_Zbrojownia.h"
#include "FOTT_Zbrojownia.h"
#include "Volcano_.h"

int runTimer = 0;
int saveTimer = 100;
bool drawToScreen = true;
int fps = 0;
int speedXX = 65;

BITMAP * mask;
BITMAP * popupBufor;

SAMPLE * music;
bool musicIs = true;

namespace variables
{
	bool run = true;
	volatile long speed = 0;
}
namespace bitmaps
{
	BITMAP * playerG1;
	BITMAP * playerG2;
	BITMAP * playerG3;
	BITMAP * playerG4;

	BITMAP * optG;

	BITMAP * minimap;
}

using namespace variables;
using namespace bitmaps;

World world(350, 1);
Player player(0, 375, 325, 50, 50, 0, "down");
quest_system Quest_System;
actQuest actquest;

void increment_speed()
{
    speed++;
}
LOCK_VARIABLE( speed );
LOCK_FUNCTION( increment_speed );
volatile int game_time = 0;
void game_time_ticker()
{
	game_time++;
}
END_OF_FUNCTION(game_time_ticker);
LOCK_VARIABLE(game_time);
LOCK_FUNCTION(game_time_ticker);

void Start(){
	App::createMask();

	App::setLight(0);
	App::setLightColor(0, 0, 0);

	optG = create_bitmap(250, 250);
	clear_to_color(optG, makecol(255, 255, 255));

	App::init();
	LT::init();
	eq::init();
	Quest_System.init();
	player.init();
	Skills::Init();
	Skills::save();

	actquest.init();

	Mob::LoadR();
	Mob::LoadNO();

	ConCity::Load("ConCity");
	ConCity::On();

	FOTT::Load("ForestOfThreeTrees");
	FOTT::Off();

	Volcano::Load("Volcano");
	Volcano::Off();

	playerG1 = load_bmp("Grafika/Gra/Gracz/gracz1.bmp", default_palette);
	playerG2 = load_bmp("Grafika/Gra/Gracz/gracz2.bmp", default_palette);
	playerG3 = load_bmp("Grafika/Gra/Gracz/gracz3.bmp", default_palette);
	playerG4 = load_bmp("Grafika/Gra/Gracz/gracz4.bmp", default_palette);

	minimap = load_bmp("Grafika/Gra/Default/construgia_map.bmp", default_palette);

	App::saveToFile("DATA/never.save", 0);
}

void setFps(){
}

bool opcj = false;
void Options(){
	if(key[KEY_O] && runTimer <= 0){
		opcj = !opcj;

		runTimer = 30;
	}

	if(key[KEY_E]){
		App::drawBITMAP(minimap, 0, 150, 800, 300);
	}

	if(opcj){
		App::drawBITMAP(optG, 0, 175, 800, 250);

		App::drawVariableText("Muzyka On/Off: kliknij 'N' | Aktualnie: ", 250, 200, musicIs, -1);
		App::drawVariableText("Chodzenie myszka (BETA!) On/Off: kliknij 'C' | Aktualnie: ", 250, 215, player.mouseWalk, -1);

		//Muzyka -->

		if(key[KEY_N] && musicIs && runTimer <= 0){
			musicIs = false;
			stop_sample(music);
			runTimer = 50;
		}
		if(key[KEY_N] && musicIs == false && runTimer <= 0){
			musicIs = true;
			play_sample( music, 255, 127, 750, 1 );
			runTimer = 50;
		}

		if(key[KEY_C] && player.mouseWalk && runTimer <= 0){
			player.mouseWalk = false;
			runTimer = 50;
		}
		if(key[KEY_C] && player.mouseWalk == false && runTimer <= 0){
			player.mouseWalk = true;
			runTimer = 50;
		}
	}
}

void Update(){
	if(drawToScreen){
		ConCity::Update();
		FOTT::Update();
		Volcano::Update();

		Mob::LootsU();

		player.Update(playerG1, playerG2, playerG3, playerG4, optG);

		if(Mob::playerRed && Mob::playerRedTimer > 0){
			Mob::Red(playerG1, playerG2, playerG3, playerG4);
		}
		else if(Mob::playerRed && Mob::playerRedTimer <= 0){
			Mob::playerRed = false;
			Mob::UnRed(playerG1, playerG2, playerG3, playerG4);
		}

		App::drawText("(C) Construgia v.0.1.9", 110, 0);
		
		eq::logic();

		draw_sprite(bufor, popupBufor, 0, 0);
		draw_trans_sprite(bufor, mask, 0, 0);

		//Quest_System.update();
		actquest.update();
		Skills::Update();
		Trasher::Update();

		Options();

		App::drawVariableText("FPS: ", 740, 0, fps, -1);
		App::drawVariableText("X: ", 740, 10, player.camera.x, -1);

		App::drawBufor();
	}

	if(key[KEY_ESC] && world.speed == -3 && runTimer <= 0) run = false;

	if(runTimer >= 0)
		runTimer--;

	if(saveTimer > 0)
		saveTimer--;
	else
	{
		eq::save();
		player.save();
		//Quest_System.save();
		actquest.save();
		ConCity_Zbrojownia::save();
		FOTT_Zbroj::save();
		Skills::save();
		saveTimer = 3000;
	}

	if(key[KEY_F2] && runTimer <= 0){
		std::string a1, a2, a3, a4;

		a1 = std::rand() * 1;
		a2 = std::rand() * 3;
		a3 = std::rand() * 5;
		a4 = std::rand() * 9;

		std::string ciag;

		ciag = a1 + a2 + a3 + a4;
		ciag = "Screenshots/" + ciag + ".bmp";

		save_bitmap(ciag.c_str(), bufor, default_palette);
		runTimer = 25;
	}
}

//////////////////////

void game(){
	install_timer();
	install_int(increment_speed, 10);
	install_int_ex( increment_speed, BPS_TO_TIMER( speedXX ) );
	install_int_ex(game_time_ticker, BPS_TO_TIMER(10));
	srand( time( NULL ) );

	Start();

	int frames_done = 0;
	int old_time = 0;

	while(run){
		while(speed == 0 && run)
		{
			rest(1);

			if(key[KEY_ESC])
				run = false;
		}
		while( speed > 0 && run)
		{
			int old_speed = speed;

			Update();

			speed--;

			if(old_speed <= speed)
				break; 
		}
		// FPS->
		if(game_time - old_time >= 10 && run)
		{
			fps = frames_done;
			
			frames_done = 0;
			old_time = game_time;
			
			if(key[KEY_ESC])
				run = false;
		}
		frames_done++;
		// <-FPS
		if(key[KEY_C]){
			speedXX++;
		}
	}

	eq::save();
	player.save();
	//Quest_System.save();
	actquest.save();
	ConCity_Zbrojownia::save();
	FOTT_Zbroj::save();
	Skills::save();

	stop_sample( music );
	destroy_sample( music );
	allegro_exit();
}