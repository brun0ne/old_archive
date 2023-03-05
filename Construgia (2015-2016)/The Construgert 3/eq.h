class missile_area
{
public:

	int power, x, y, type, healtD, im;
	float healt;
	std::string name, url, save_url;
	BITMAP * bmp;

	void init(int x, int y, std::string save_url);

	void update();
	
	void draw();
	void logic();

	void set(std::string name, std::string url, int power, int healt, bool graphSet, int type, int im);
	void erase();

	void save();
	void read();
};

class main_missile
{
public:

	int power, im;
	std::string name, url;
	BITMAP * bmp;

	void init();

	void update();

	void set(int power, std::string name, std::string url, BITMAP * bmp, int im);

	void save();
	void read();
};

class eq
{
public:

	static missile_area missile_area1;
	static missile_area missile_area2;
	static missile_area missile_area3;
	static missile_area missile_area4;
	static missile_area missile_area5;
	static missile_area missile_area6;
	static missile_area missile_area7;
	static missile_area missile_area8;
	static missile_area missile_area9;
	static missile_area missile_area10;
	static missile_area missile_area11;
	static missile_area missile_area12;
	static missile_area missile_area13;
	static missile_area missile_area14;
	static missile_area missile_area15;
	static missile_area missile_area16;
	static missile_area missile_area17;
	static missile_area missile_area18;

	static main_missile Main_Missile;

	///////////////////////////////////

	static bool is, delWork;

	static BITMAP * button_d;
	static BITMAP * button_s;
	static BITMAP * arrowD;
	static BITMAP * arrowS;
	static BITMAP * gray_trans;

	static BITMAP * popUpbufor;

	///////////////////////////////////

	static int hpMix, filons_paper;
	
	///////////////////////////////////

	static void init();

	static void logic();

	static int emptyArea();

	static int findArea(std::string name);

	static void delArea(std::string name);

	static void pushToArea(std::string name, std::string url, int power, int healt, bool graphSet, int type, int im);

	static void stats();

	///////////////////////////////////

	static void useHpMix();

	static void lHpMix();

	///////////////////////////////////

	static void save();

	static void read();
};