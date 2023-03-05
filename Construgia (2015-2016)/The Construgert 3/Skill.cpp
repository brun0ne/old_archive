#include "main.h"

void Skill::Init(std::string _name, float _bonus, int _number, int _type, float _chance, int _sPrice){
	name = _name;
	bonus = _bonus;
	chance = _chance;
	number = _number;
	type = _type;
	sPrice = _sPrice;
		int never_save;
		App::readFromFile("DATA/never.save", never_save);
		if(never_save == 1){
			lvl = 0;
		}
	name_ex = name + ": ";
}

void Skill::Draw(){
	if(App::button(name_ex.c_str(), Skills::skillGraph, Skills::skillGraph_, 1, 0, 1, lvl, "", number * 175, 50, 150, 50)){
		if(Skills::pkt > 0 && runTimer <= 0){
			lvl++;
			Skills::pkt--;
			if(name == "Sila"){
				player.attackP += bonus * lvl;
			}
			if(name == "Obrona"){
				player.defenceP += bonus * lvl;
			}
			if(name == "Witalnosc"){
				player.maxHp += bonus * lvl * 4;
			}
			runTimer = 35;
		}
	}
	if(App::onSlide(number * 175, 50, 150, 50)){
		App::drawBITMAP(button, mouse_x, mouse_y, 250, 50);
		if(Skills::pkt > 0){
			App::drawVariableText("Kliknij aby ulepszyc.", mouse_x + 5, mouse_y + 5, 0, -1);
		}
		else{
			App::drawVariableText("Masz za malo punktow UM.", mouse_x + 5, mouse_y + 5, 0, -1);
		}
	}
}

void Skill::Logic(){
	
}

void Skill::Update(){
	Draw();
	Logic();
}