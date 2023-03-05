#include "main.h"

class ConCity
{
public:

	static BITMAP * main_bg;
	static BITMAP * plus_bg;

	static npc Carcco;

	static int liczba;

	static bool is;

	static void GraphLoad();

	static void Npcs();

	static void Mobs();

	static void Intro();

	static void Load(std::string name);

	static void On();

	static void Off();

	static void Update();
};