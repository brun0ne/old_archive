#include "main.h"

class MoveToPoint{
public:
	
	BITMAP * bmp;

	int x, y, timer;
	bool active;

	MoveToPoint();

	void Init();

	void Create();

	void SetColor();

	void Draw();

	void Logic();

	void Listen();

	void Update();
};