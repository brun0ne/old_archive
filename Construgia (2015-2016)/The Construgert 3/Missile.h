#include "main.h"

class Missile
{
public:
	int x, y, w, h, power, lifeTime;
	std::string goTo;
	bool is;
	BITMAP * bmp;

	Missile();

	void init();

	void Create(int x, int y, int w, int h, int speed, std::string goTo);
	void Load(std::string url);
	void Destroy();

	void Update(int speed);

	void Draw();
	void Logic(int speed);
	bool onCollision(int speed);
};