#include "main.h"

// Eq CLASS ->

bool eq::is;
bool eq::delWork = false;
int eq::filons_paper;
int eq::hpMix = 0;

BITMAP * eq::button_d;
BITMAP * eq::button_s;
BITMAP * eq::arrowD;
BITMAP * eq::arrowS;
BITMAP * eq::gray_trans;
BITMAP * eq::popUpbufor;

missile_area eq::missile_area1;
missile_area eq::missile_area2;
missile_area eq::missile_area3;
missile_area eq::missile_area4;
missile_area eq::missile_area5;
missile_area eq::missile_area6;
missile_area eq::missile_area7;
missile_area eq::missile_area8;
missile_area eq::missile_area9;
missile_area eq::missile_area10;
missile_area eq::missile_area11;
missile_area eq::missile_area12;
missile_area eq::missile_area13;
missile_area eq::missile_area14;
missile_area eq::missile_area15;
missile_area eq::missile_area16;
missile_area eq::missile_area17;
missile_area eq::missile_area18;

main_missile eq::Main_Missile;

void eq::init(){
	hpMix = 3;

	is = true;
	delWork = false;

	button_d = load_bmp("Grafika/Gra/Default/button.bmp", default_palette);
	button_s = load_bmp("Grafika/Gra/Default/l_button.bmp", default_palette);
	arrowD = load_bmp("Grafika/Gra/Default/arrowButtonD.bmp", default_palette);
	arrowS = load_bmp("Grafika/Gra/Default/arrowButtonS.bmp", default_palette);
	gray_trans = load_bmp("Grafika/Gra/Default/gray_trans.bmp", default_palette);

	popUpbufor = create_bitmap(800, 600);
	clear_to_color(popUpbufor, makecol(255, 0, 255));

	Main_Missile.init();

	missile_area1.init(650, 300, "DATA/Area1");
	missile_area2.init(700, 300, "DATA/Area2");
	missile_area3.init(750, 300, "DATA/Area3");
	missile_area4.init(650, 350, "DATA/Area4");
	missile_area5.init(700, 350, "DATA/Area5");
	missile_area6.init(750, 350, "DATA/Area6");

	missile_area7.init(650, 400, "DATA/Area7");
	missile_area8.init(700, 400, "DATA/Area8");
	missile_area9.init(750, 400, "DATA/Area9");
	missile_area10.init(650, 450, "DATA/Area10");
	missile_area11.init(700, 450, "DATA/Area11");
	missile_area12.init(750, 450, "DATA/Area12");

	missile_area13.init(650, 500, "DATA/Area13");
	missile_area14.init(700, 500, "DATA/Area14");
	missile_area15.init(750, 500, "DATA/Area15");
	missile_area16.init(650, 650, "DATA/Area16");
	missile_area17.init(700, 650, "DATA/Area17");
	missile_area18.init(750, 650, "DATA/Area18");

	int never;
	App::readFromFile("DATA/never.save", never);
	if(never == 1)
		eq::filons_paper = 0;
	else{
		App::readFromFile("DATA/Other/filons_paper.save", eq::filons_paper);
	}
}

void eq::logic(){
	if(is){
		clear_to_color(popUpbufor, makecol(255, 0, 255));

		App::drawBITMAP(gray_trans, 650, 0, 150, 150);
		App::drawBITMAP(gray_trans, 650, 150, 150, 150);
		App::drawBITMAP(gray_trans, 650, 300, 150, 150);
		App::drawBITMAP(gray_trans, 650, 450, 150, 150);
		App::drawBITMAP(gray_trans, 650, 550, 150, 150);

		// EQ ->

		Main_Missile.update();

		missile_area1.update();
		missile_area2.update();
		missile_area3.update();
		missile_area4.update();
		missile_area5.update();
		missile_area6.update();
		missile_area7.update();
		missile_area8.update();
		missile_area9.update();
		missile_area10.update();
		missile_area11.update();
		missile_area12.update();
		missile_area13.update();
		missile_area14.update();
		missile_area15.update();
		missile_area16.update();
		missile_area17.update();
		missile_area18.update();

		// <- EQ

		App::drawBITMAP(popUpbufor, 0, 0, 800, 600);
	}
}

int eq::emptyArea(){
	if(missile_area1.type == 1)
		return 1;
	if(missile_area2.type == 1)
		return 2;
	if(missile_area3.type == 1)
		return 3;
	if(missile_area4.type == 1)
		return 4;
	if(missile_area5.type == 1)
		return 5;
	if(missile_area6.type == 1)
		return 6;

	if(missile_area7.type == 1)
		return 7;
	if(missile_area8.type == 1)
		return 8;
	if(missile_area9.type == 1)
		return 9;
	if(missile_area10.type == 1)
		return 10;
	if(missile_area11.type == 1)
		return 11;
	if(missile_area12.type == 1)
		return 12;

	if(missile_area13.type == 1)
		return 13;
	if(missile_area14.type == 1)
		return 14;
	if(missile_area15.type == 1)
		return 15;
	if(missile_area16.type == 1)
		return 16;
	if(missile_area17.type == 1)
		return 17;
	if(missile_area18.type == 1)
		return 18;

	return 77;
}

int eq::findArea(std::string _name){
	if(missile_area1.name == _name)
		return 1;
	if(missile_area2.name == _name)
		return 2;
	if(missile_area3.name == _name)
		return 3;
	if(missile_area4.name == _name)
		return 4;
	if(missile_area5.name == _name)
		return 5;
	if(missile_area6.name == _name)
		return 6;

	if(missile_area7.name == _name)
		return 7;
	if(missile_area8.name == _name)
		return 8;
	if(missile_area9.name == _name)
		return 9;
	if(missile_area10.name == _name)
		return 10;
	if(missile_area11.name == _name)
		return 11;
	if(missile_area12.name == _name)
		return 12;

	if(missile_area13.name == _name)
		return 13;
	if(missile_area14.name == _name)
		return 14;
	if(missile_area15.name == _name)
		return 15;
	if(missile_area16.name == _name)
		return 16;
	if(missile_area17.name == _name)
		return 17;
	if(missile_area18.name == _name)
		return 18;
}

void eq::delArea(std::string _name){
	int n;
	n = findArea(_name);
	if(n == 1)
		missile_area1.erase();
	if(n == 2)
		missile_area2.erase();
	if(n == 3)
		missile_area3.erase();
	if(n == 4)
		missile_area4.erase();
	if(n == 5)
		missile_area5.erase();
	if(n == 6)
		missile_area6.erase();

	if(n == 7)
		missile_area7.erase();
	if(n == 8)
		missile_area8.erase();
	if(n == 9)
		missile_area9.erase();
	if(n == 10)
		missile_area10.erase();
	if(n == 11)
		missile_area11.erase();
	if(n == 12)
		missile_area12.erase();

	if(n == 13)
		missile_area13.erase();
	if(n == 14)
		missile_area14.erase();
	if(n == 15)
		missile_area15.erase();
	if(n == 16)
		missile_area16.erase();
	if(n == 17)
		missile_area17.erase();
	if(n == 18)
		missile_area18.erase();
}

void eq::pushToArea(std::string name, std::string url, int power, int healt, bool graphSet, int type, int im){
	if(emptyArea() == 1)
		missile_area1.set(name, url, power, healt, graphSet, type, im);
	else if(emptyArea() == 2)
		missile_area2.set(name, url, power, healt, graphSet, type, im);
	else if(emptyArea() == 3)
		missile_area3.set(name, url, power, healt, graphSet, type, im);
	else if(emptyArea() == 4)
		missile_area4.set(name, url, power, healt, graphSet, type, im);
	else if(emptyArea() == 5)
		missile_area5.set(name, url, power, healt, graphSet, type, im);
	else if(emptyArea() == 6)
		missile_area6.set(name, url, power, healt, graphSet, type, im);
	else if(emptyArea() == 7)
		missile_area7.set(name, url, power, healt, graphSet, type, im);
	else if(emptyArea() == 8)
		missile_area8.set(name, url, power, healt, graphSet, type, im);
	else if(emptyArea() == 9)
		missile_area9.set(name, url, power, healt, graphSet, type, im);
	else if(emptyArea() == 10)
		missile_area10.set(name, url, power, healt, graphSet, type, im);
	else if(emptyArea() == 11)
		missile_area11.set(name, url, power, healt, graphSet, type, im);
	else if(emptyArea() == 12)
		missile_area12.set(name, url, power, healt, graphSet, type, im);
	else if(emptyArea() == 13)
		missile_area13.set(name, url, power, healt, graphSet, type, im);
	else if(emptyArea() == 14)
		missile_area14.set(name, url, power, healt, graphSet, type, im);
	else if(emptyArea() == 15)
		missile_area15.set(name, url, power, healt, graphSet, type, im);
	else if(emptyArea() == 16)
		missile_area16.set(name, url, power, healt, graphSet, type, im);
	else if(emptyArea() == 17)
		missile_area17.set(name, url, power, healt, graphSet, type, im);
	else if(emptyArea() == 18)
		missile_area18.set(name, url, power, healt, graphSet, type, im);

	//if(emptyArea() == 77)
		//*emulator.error()*/;
}

void eq::stats(){
	if(player.dHp != player.hp)
		player.dHp = player.hp;

	App::drawVariableText("LVL: ", 5, 550, player.lvl, 1);
	textprintf_ex(bufor, font, 5, 560, makecol(255, 255, 255), -1, "HP: %d/%d", player.dHp, player.maxHp);
	textprintf_ex(bufor, font, 5, 570, makecol(255, 255, 255), -1, "EXP: %d/%d", player.exp, player.maxExp);
	App::drawVariableText("ATTACK POINTS (AP): ", 5, 580, player.attackP, 1);
	App::drawVariableText("DEFENCE POINTS (DP): ", 5, 590, player.defenceP, 1);
}

///////////////////////////////////

void eq::useHpMix(){
	player.hp += 10 * player.lvl;
	hpMix -= 1;
	runTimer = 35;
}

void eq::lHpMix(){
	if(App::button("HpReg: ", button_d, button_s, 1, 0, 1, hpMix, "", 655, 450, 135, 35) && hpMix > 0 && player.hp < player.maxHp && runTimer <= 0){
		useHpMix();
	}
}

///////////////////////////////////

void eq::save(){
	Main_Missile.save();

	missile_area1.save();
	missile_area2.save();
	missile_area3.save();
	missile_area4.save();
	missile_area5.save();
	missile_area6.save();

	missile_area7.save();
	missile_area8.save();
	missile_area9.save();
	missile_area10.save();
	missile_area11.save();
	missile_area12.save();

	missile_area13.save();
	missile_area14.save();
	missile_area15.save();
	missile_area16.save();
	missile_area17.save();
	missile_area18.save();
}