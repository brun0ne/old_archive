#include "main.h"
#include "ConCity.h"

class _Ratusz
{
public:

	static BITMAP * main_bg;
	static BITMAP * plus_bg;
	static BITMAP * mainWall;

	static void GraphLoad();

	static void Mpcs();

	static void Load(std::string name);

	static void On();

	static void Off();

	static void Update();
};