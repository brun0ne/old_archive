#include "main.h"

class Player
{
public:

	int x, y, w, h, points, gold, moveTimer;
	std::string rot;
	bool mouseWalk;

	//Stats

	int dHp, maxHp, lvl, exp, maxExp, attackP, missileTimer;
	float hp, defenceP;

	///////

	struct Camera
	{
		int x;
		float speed;
	};

	Camera camera;

	Player(int _cam_x, int _x, int _y, int _w, int _h, int _points, std::string _rot);

	void init();

	void Update (BITMAP * bitmap1, BITMAP * bitmap2, BITMAP * bitmap3, BITMAP * bitmap4, BITMAP * missileGraph);

	void Draw(BITMAP * bitmap1, BITMAP * bitmap2, BITMAP * bitmap3, BITMAP * bitmap4);
	void Collisions();
	void Logic(BITMAP * missileGraph);
	void GameOver();

	void save();
	void read();
};