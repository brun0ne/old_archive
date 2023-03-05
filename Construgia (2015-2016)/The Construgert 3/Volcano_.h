#include "main.h"

class Volcano
{
public:

	static BITMAP * main_bg;
	static BITMAP * plus_bg;
	static BITMAP * background;

	static int event_;

	static npc Straznik;

	static Mob mob1;
	static Mob mob2;
	static Mob mob3;

	static Mob mob1_;
	static Mob mob2_;
	static Mob mob3_;

	static bool is;

	static void GraphLoad();

	static void Mobs();
	
	static void Npcs();

	static void Load(std::string name);

	static void On();

	static void Off();

	static void Update();
};