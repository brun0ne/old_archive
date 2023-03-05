#include "main.h"

class World
{
public:

	int speed, plane_h, speedPh, plus_bg_x, spawnData;
	bool isScreenScroll;

	friend class Player;

	void Update(BITMAP * main_bg, BITMAP * plus_bg);

	void Draw(BITMAP * main_bg, BITMAP * plus_bg);
	void Collisions();

	World(int _plane_h, int _spawnData);
};