#include "main.h"

class Item{
public:

	BITMAP * bmp;

	int x, y, w, h, type, gold, exp;
	bool is;

	std::string name, url;

	Item(int x, int y, int w, int h, int type, int gold, int exp, std::string name, std::string url);

	void Init();

	void Draw();

	void Logic();
	
	void Update();
};