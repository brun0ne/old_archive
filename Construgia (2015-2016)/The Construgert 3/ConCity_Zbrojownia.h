#include "main.h"

class ConCity_Zbrojownia
{
public:

	static BITMAP * main_bg;
	static BITMAP * plus_bg;
	static BITMAP * mainWall;

	static bool is;

	static void GraphLoad();

	static void Shop();

	static void Npcs();

	static void save();

	static void read();

	static void Load(std::string name);

	static void On();

	static void Off();

	static void Update();
};

extern npc sprzedawca;