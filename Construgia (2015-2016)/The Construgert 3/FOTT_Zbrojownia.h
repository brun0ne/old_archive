#include "main.h"

class FOTT_Zbroj{

public:

	static BITMAP * main_bg;
	static BITMAP * plus_bg;
	static BITMAP * mainWall;

	static bool is;

	static npc sprzedawca;

	static void GraphLoad();
	
	static void read();

	static void save();

	static void Shop();

	static void Npcs();

	static void Load(std::string name);

	static void On();

	static void Off();

	static void Update();
};