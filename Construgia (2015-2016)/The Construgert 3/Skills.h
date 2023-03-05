#include "main.h"

class Skill{
public:
	std::string name, name_ex;
	int number, type, lvl, needLvl;
	float bonus, chance, sPrice;

	void Init(std::string _name, float _bonus, int _number, int _type, float _chance, int sPrice);

	void Draw();
	void Logic();
	void Update();
};

class Skills{
public:
	static BITMAP * skillGraph;
	static BITMAP * skillGraph_;
	static BITMAP * mainGraph;
	static BITMAP * on_off;

	static bool is;
	static int pkt;

	static std::vector <Skill> skills;

	static void Init();

	static void Draw();
	static void Logic();
	static void Menage();

	static void Update();

	static void save();
	static void read();
};