#include "main.h"

class BrunonCave
{
public:

	//Mobs
	static Mob mob1;
	static Mob mob2;
	static Mob mob3;
	static Mob mob4;
	static Mob mob5;
	static Mob mob6;

	static Mob mob_1;
	static Mob mob_2;
	static Mob mob_3;
	static Mob mob_4;
	static Mob mob_5;
	static Mob mob_6;

	static BITMAP * main_bg;
	static BITMAP * plus_bg;
	static BITMAP * mainWall;
	static int camera_x_onEnter;
	static int stalagX;

	static bool is;

	static void GraphLoad();

	static void Mobs();

	static void Load(std::string name);

	static void On();

	static void Off();

	static void Update();
};