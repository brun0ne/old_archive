#include "main.h"

class npc
{
public:

	float x, y, w, h;
	int lvl, event_[5], dTimer;
	bool active;
	std::string name;
	BITMAP * bmp;

	npc(std::string name, int x, int y, int w, int h, int lvl);

	void start(std::string bmp_link);

	void on();

	void off();

	void update();

	void draw();

	void logic();

	void listen();
};