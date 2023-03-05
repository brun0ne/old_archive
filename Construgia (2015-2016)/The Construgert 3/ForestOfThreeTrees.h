#include "main.h"

class FOTT // Forest Of Three Trees
{
public:

	static BITMAP * main_bg;
	static BITMAP * plus_bg;
	static BITMAP * background;

	static Mob mob1;
	static Mob mob2;
	static Mob mob3;
	static Mob mob4;
	static Mob mob5;
	static Mob mob6;

	static bool is;

	static void GraphLoad();

	static void Mobs();

	static void Load(std::string name);

	static void On();

	static void Off();

	static void Update();
};