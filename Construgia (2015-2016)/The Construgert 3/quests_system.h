#include "main.h"

class quest
{
public:

	int _event[5], a, b, priceGold, priceExp, number;
	bool finish;
	std::string name, text;

	quest(std::string name, std::string text, int priceGold, int priceExp, int a, int b, int number);
	
	void init(std::string name, std::string text, int priceGold, int priceExp, int a, int b, int number);

	void update();

	void save();
	void read();
};

class quest_system
{
public:

	std::vector <quest> list;

	BITMAP * icon;
	BITMAP * area;

	bool is;

	void init();

	void push(std::string name, std::string text, int priceGold, int priceExp, int a, int b);
	void pop(int number);
	
	void draw();
	void logic();

	void update();

	int search(std::string keyword);

	void save();
	void read();
};