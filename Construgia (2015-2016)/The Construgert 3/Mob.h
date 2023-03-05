#include "main.h"

class Mob
{
public:

	int w, h, minX, maxX, power, loot, respTime;
	float x, y, speed;
	bool is, directionX, directionY, yGo;
	std::string name;
	BITMAP * main_bg;
	static BITMAP * PR_up; static BITMAP * PR_down; static BITMAP * PR_left; static BITMAP * PR_right;
	static BITMAP * NO_up; static BITMAP * NO_down; static BITMAP * NO_left; static BITMAP * NO_right;
	static bool playerRed;
	static int playerRedTimer;

	//Stats
	float hp, maxHp, exp, attackP, defenceP;
	///////

	static void LootsU();
	static void LootsI();

	static void LoadR();
	static void LoadNO();

	Mob(float x, float y, int w, int h, int minX, int maxX, int power, float speed, bool yGo, float hp, float attackP, float defenceP, int loot, bool is, std::string name);

	void Create(float x, float y, int w, int h, int minX, int maxX, int power, float speed, bool yGo, float hp, float attackP, float defenceP, int loot, bool is, std::string name);
	void synchro(int synch);
	void loadGraph(std::string url);
	void Load(std::string url);
	void Destroy();

	void basicUpdate();
	void Draw();
	void basicLogic();
	void Go();

	bool normalAttack();
	void shotAttack(bool shot);
	bool getDamage();
	void respawn();

	static void Red(BITMAP * &up, BITMAP * &down, BITMAP * &left, BITMAP * &right);
	static void UnRed(BITMAP * &up, BITMAP * &down, BITMAP * &left, BITMAP * &right);
};