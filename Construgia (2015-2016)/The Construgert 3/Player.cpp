#include "main.h"
#include "ConCity_BrunonCave.h"
#include "MoveToPoint.h"

Missile missile1;
Missile missile2;

MoveToPoint moveToPoint;

Player::Player(int _cam_x, int _x, int _y, int _w, int _h, int _points, std::string _rot){
	camera.x = _cam_x;
	x = _x;
	y = _y;
	w = _w;
	h = _h;
	points = _points;
	rot = _rot;
	camera.speed = 0;
	moveTimer = 0;
	mouseWalk = false;
}

void Player::init(){
	int first;
	App::readFromFile("DATA/never.save", first);
	
	if(first == 1){
		lvl = 1;
		hp = 150;
		maxHp = hp;
		exp = 0;
		maxExp = 15;
		attackP = 30;
		defenceP = 4;
		gold = 20;

		save();
	}
	else
	{
		read();
	}

	missile1.init();
	missile2.init();

	moveToPoint.Init();
}

void Player::Update(BITMAP * bitmap1, BITMAP * bitmap2, BITMAP * bitmap3, BITMAP * bitmap4, BITMAP * missileGraph){
	Draw(bitmap1, bitmap2, bitmap3, bitmap4);
	Collisions();
	Logic(missileGraph);

	if(moveTimer >= 0)
		moveTimer--;

	if(mouseWalk)
		moveToPoint.Update();
}

void Player::Draw(BITMAP * bitmap1, BITMAP * bitmap2, BITMAP * bitmap3, BITMAP * bitmap4){
	if(rot == "down")                     // DOWN
		App::drawBITMAP(bitmap1, x, y, w, h);
	if(rot == "right")                    // RIGHT
		App::drawBITMAP(bitmap2, x, y, w, h);
	if(rot == "left")                     // LEFT
		App::drawBITMAP(bitmap3, x, y, w, h);
	if(rot == "up")                       // UP
		App::drawBITMAP(bitmap4, x, y, w, h);

	if(dHp != hp)
		dHp = hp;

	App::drawVariableText("ZLOTO: ", 5, 540, gold, -1);
	App::drawVariableText("LVL: ", 5, 550, lvl, -1);
	textprintf_ex(bufor, font, 5, 560, makecol(0, 0, 0), -1, "HP: %d/%d", dHp, maxHp);
	textprintf_ex(bufor, font, 5, 570, makecol(0, 0, 0), -1, "EXP: %d/%d", exp, maxExp);
	textprintf_ex(bufor, font, 5, 580, makecol(0, 0, 0), -1, "ATTACK POINTS (AP): %d (gracz) + %d (pocisk)", attackP, eq::Main_Missile.power);
	App::drawVariableText("DEFENCE POINTS (DP): ", 5, 590, defenceP, -1);
}

void Player::Collisions(){

}

void Player::Logic(BITMAP * missile_bmp){
	//Pociski
	missile1.Update(10);
	missile2.Update(10);

	if(missileTimer >= 0)
		missileTimer--;

	if((key[KEY_SPACE] || mouse_b == 2) && missileTimer <= 0 && eq::Main_Missile.name != ""){
		if(missile1.is == false){
			missile1.Create(player.x, player.y, 25, 25, 1, rot);
			missileTimer = 35;
			missile1.lifeTime = 100;
			if(eq::Main_Missile.im != -777)
				eq::Main_Missile.im--;
		}
		else if(missile2.is == false){
			missile2.Create(player.x, player.y, 25, 25, 1, rot);
			missileTimer = 35;
			missile2.lifeTime = 100;
			if(eq::Main_Missile.im != -777)
				eq::Main_Missile.im--;
		}
	}

	//Hp > MaxHp && Gold < 0
	if(hp > maxHp)
		hp = maxHp;
	if(gold < 0)
		gold = 0;
		//App::Error(2);

	//Lose
	if(hp <= 0)
		GameOver();

	//Levele
	if(exp >= maxExp){
		lvl++;
		maxHp += (maxHp / 4);
		hp = maxHp;
		attackP += (attackP / 4);
		defenceP += (defenceP / 4);
		Skills::pkt++;

		exp -= maxExp;
		maxExp *= 3;
	}

	if(moveTimer <= 0){
		// Poruszanie siê <--------------------
		if(world.isScreenScroll){
			if(key[KEY_LEFT] || key[KEY_A]){
				camera.x -= ( 1 - world.speed );
				rot = "left";
				if(world.plus_bg_x <= 0)
					world.plus_bg_x += ( 1 - world.speed );
				else
					world.plus_bg_x = -1000;

				if(missile1.is)
					missile1.x += ( 1 - ( world.speed / 2  ) );
				if(missile2.is)
					missile2.x += ( 1 - ( world.speed / 2  ) );
			}
			if(key[KEY_RIGHT] || key[KEY_D]){
				camera.x += ( 1 - world.speed );
				rot = "right";
				if(world.plus_bg_x >= -1000)
					world.plus_bg_x -= ( 1 - world.speed );
				else
					world.plus_bg_x = 0;

				if(missile1.is)
					missile1.x -= ( 1 - ( world.speed / 2 ) );
				if(missile2.is)
					missile2.x -= ( 1 - ( world.speed / 2 ) );
			}
		}
		else
		{
			if(key[KEY_RIGHT] || key[KEY_D]){
				x += 1 - world.speed;
				rot = "right";
			}
			if(key[KEY_LEFT] || key[KEY_A]){
				x -= 1 - world.speed;
				rot = "left";
			}
		}
		if(key[KEY_UP] || key[KEY_W]){
			y -= ( 1 - world.speed );
			rot = "up";
		}
		if(key[KEY_DOWN] || key[KEY_S]){
			y += ( 1 - world.speed );
			rot = "down";
		}
	}
	if(world.isScreenScroll == false && world.speed != 1){
		if(player.x >= 650){
			eq::is = false;
		}
		else
		{
			eq::is = true;
		}
	}
}

void Player::GameOver(){
	clear_to_color(bufor, makecol(255, 0, 0));

	hp = 1;
	exp = 0;
	camera.x = 0;
	y = 300;
}

void Player::save(){
	App::saveToFile("DATA/Player/points.save", points);
	App::saveToFile("DATA/Player/gold.save", gold);
	App::saveToFile("DATA/Player/dHp.save", dHp);
	App::saveToFile("DATA/Player/hp.save", hp);
	App::saveToFile("DATA/Player/maxHp.save", maxHp);
	App::saveToFile("DATA/Player/lvl.save", lvl);
	App::saveToFile("DATA/Player/configGraph.save", exp);
	App::saveToFile("DATA/Player/confArea.save", maxExp);
	App::saveToFile("DATA/Player/zap.save", attackP);
	App::saveToFile("DATA/Player/dp.save", defenceP);
}

void Player::read(){
	App::readFromFile("DATA/Player/points.save", points);
	App::readFromFile("DATA/Player/gold.save", gold);
	App::readFromFile("DATA/Player/dHp.save", dHp);
	App::readFromFile("DATA/Player/maxHp.save", maxHp);
	App::readFromFile("DATA/Player/lvl.save", lvl);
	App::readFromFile("DATA/Player/configGraph.save", exp);
	App::readFromFile("DATA/Player/confArea.save", maxExp);
	App::readFromFile("DATA/Player/zap.save", attackP);

	std::ifstream hpFile, defencepFile;

	hpFile.open("DATA/Player/hp.save");
	defencepFile.open("DATA/Player/dp.save");

	hpFile >> hp;
	defencepFile >> defenceP;
}