#include "main.h"

class actQuest{
public:
	int _event[5], a, b, priceExp, priceGold;
	bool finish, is, blank, mess_act, cancelNo;
	std::string name, text;
	BITMAP * icon;

	actQuest();
	void init();

	void update();
	void draw();
	void logic();

	void Clear();

	void replace(std::string name, std::string text, int priceExp, int priceGold, int a, int b);

	void save();
	void read();
};