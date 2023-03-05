#include "main.h"

std::vector <Item> loots;

bool Mob::playerRed;
int Mob::playerRedTimer;
BITMAP * Mob::PR_up; BITMAP * Mob::PR_down; BITMAP * Mob::PR_left; BITMAP * Mob::PR_right;
BITMAP * Mob::NO_up; BITMAP * Mob::NO_down; BITMAP * Mob::NO_left; BITMAP * Mob::NO_right;

void Mob::LootsU(){
	for(unsigned int i = 0; i < loots.size(); i++){
		loots[i].Update();
	}
	if(playerRedTimer >= 0)
		playerRedTimer--;
}

void Mob::LootsI(){
	for(unsigned int i = 0; i < loots.size(); i++){
		loots[i].Init();
	}
}

void Mob::LoadR(){
	PR_up = load_bmp("Grafika/Gra/Gracz/PR/up.bmp", default_palette);
	PR_down = load_bmp("Grafika/Gra/Gracz/PR/down.bmp", default_palette);
	PR_left = load_bmp("Grafika/Gra/Gracz/PR/left.bmp", default_palette);
	PR_right = load_bmp("Grafika/Gra/Gracz/PR/right.bmp", default_palette);

	playerRed = false;
	playerRedTimer = 0;
}

void Mob::LoadNO(){
	NO_up = load_bmp("Grafika/Gra/Gracz/gracz1.bmp", default_palette);
	NO_down = load_bmp("Grafika/Gra/Gracz/gracz2.bmp", default_palette);
	NO_left = load_bmp("Grafika/Gra/Gracz/gracz3.bmp", default_palette);
	NO_right = load_bmp("Grafika/Gra/Gracz/gracz4.bmp", default_palette);
}

Mob::Mob(float _x, float _y, int _w, int _h, int _minX, int _maxX, int _power, float _speed, bool _yGo, float _hp, float _attackP, float _defenceP, int _loot, bool _is, std::string _name){ 
	is = _is;
	directionX = true;
	directionY = false;
	x = _x; y = _y; w = _w; h = _h; minX = _minX; maxX = _maxX; power = _power; speed = _speed; yGo = _yGo; loot = _loot;
	hp = _hp; attackP = _attackP; defenceP = _defenceP;
	name = _name;

	maxHp = hp;
	respTime = 6000;
}

void Mob::Create(float _x, float _y, int _w, int _h, int _minX, int _maxX, int _power, float _speed, bool _yGo, float _hp, float _attackP, float _defenceP, int _loot, bool _is, std::string _name){ 
	is = _is;
	directionX = true;
	directionY = false;
	x = _x; y = _y; w = _w; h = _h; minX = _minX; maxX = _maxX; power = _power; speed = _speed; yGo = _yGo; loot = _loot;
	hp = _hp; attackP = _attackP; defenceP = _defenceP;
	name = _name;

	maxHp = hp;
}

void Mob::synchro(int synch){
	x += synch;
	minX += synch;
	maxX += synch;
}

void Mob::loadGraph(std::string url){
	main_bg = load_bmp(url.c_str(), default_palette);
}

void Mob::Load(std::string url){
	loadGraph(url);
}

void Mob::Destroy(){ is = false; }

void Mob::basicUpdate(){
	if( is ){
		Draw();
		Go();
		basicLogic();
	//	getDamage();
	}
	respawn();
}

void Mob::Draw(){
	App::drawBITMAP(main_bg, x - player.camera.x, y, w, h);
	// HP BAR
	if(hp < maxHp){
		App::drawVariableText("HP: ", x - player.camera.x, y - 30, hp, 0);
		App::drawVariableText("AP: ", x - player.camera.x, y - 20, attackP, 2);
		App::drawVariableText("DP: ", x - player.camera.x, y - 10, defenceP, 3);
	}
	else
	{
		App::drawVariableText("HP: ", x - player.camera.x, y - 20, hp, 0);
		App::drawVariableText("AP: ", x - player.camera.x, y - 10, attackP, 2);
	}
}

void Mob::Go(){
	if( directionX )
		x += ( speed - world.speed );
	else
		x -= ( speed - world.speed );

	if( directionY && yGo )
		y += ( ( speed - 1 ) - world.speed );
	else if( yGo )
		y -= ( ( speed - 1 ) - world.speed );

	if( x <= minX )
		directionX = true;
	if( x >= maxX )
		directionX = false;

	if( y <= ( 600 - world.plane_h  ) + ( h / 2 ) )
		directionY = true;
	if( y >= 600 - h )
		directionY = false;
}

void Mob::basicLogic(){
	if( normalAttack() && playerRed == false ){
		player.hp -= ( attackP - player.defenceP );
		playerRed = true;
		playerRedTimer = 50;
	}
}

bool Mob::normalAttack(){
	if(player.x + player.w >= x - player.camera.x && player.x <= x - player.camera.x + w && player.y + player.h >= y && player.y <= y + h)
		return true;
	return false;
}

void Mob::shotAttack(bool shot){
	if( player.x >= ( minX - minX ) )
		shot = true;
	else shot = false;
	if( player.x <= ( maxX + maxX ) )
		shot = true;
	else shot = false;
}

bool Mob::getDamage(){
	if(missile1.is){
		if(missile1.x + missile1.w + ( player.w / 4 ) >= x - player.camera.x && missile1.x + ( player.w / 4 ) <= x - player.camera.x + w && missile1.y + missile1.h + ( player.h / 4 ) >= y && missile1.y + ( player.h / 4 ) <= y + h){
			hp -= ( ( player.attackP + eq::Main_Missile.power ) - defenceP );
			missile1.is = false;
		}
	}
	if(missile2.is){
		if(missile2.x + missile2.w + ( player.w / 4 ) >= x - player.camera.x && missile2.x + ( player.w / 4 ) <= x - player.camera.x + w && missile2.y + missile2.h + ( player.h / 4 ) >= y && missile2.y + ( player.h / 4 ) <= y + h){
			hp -= ( ( player.attackP + eq::Main_Missile.power ) - defenceP );
			missile2.is = false;
		}
	}
	if( hp <= 0 ){
		if(is){
			loots.push_back(Item(x, y, 50, 50, 0, loot, loot / 2, "", "loot"));
			Mob::LootsI();

			Destroy();
			return true;
		}
	}
	return false;
}

void Mob::respawn(){
	// 1 = 100 || patrz: timer (game.cpp)

	if(respTime > 0 && is == false)
		respTime--;
	if(respTime <= 0)
	{
		respTime = 6000;
		is = true;
		hp = maxHp;
	}
}

void Mob::Red(BITMAP * &up, BITMAP * &down, BITMAP * &left, BITMAP * &right){
	up = PR_up;
	down = PR_down;
	left = PR_left;
	right = PR_right;
}

void Mob::UnRed(BITMAP * &up, BITMAP * &down, BITMAP * &left, BITMAP * &right){
	up = NO_up;
	down = NO_down;
	left = NO_left;
	right = NO_right;
}