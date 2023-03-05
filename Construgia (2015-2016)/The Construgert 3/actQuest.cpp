#include "main.h"
#include <sstream>

actQuest::actQuest(){
	is = false;
	int never_save;
	App::readFromFile("DATA/never.save", never_save);
	if(never_save == 1){
		blank = true;
	}
	else
	{
		read();
	}
	finish = false;
}

void actQuest::init(){
	icon = load_bmp("Grafika/Gra/Default/questIcon.bmp", default_palette);
}

void actQuest::replace(std::string _name, std::string _text, int _priceExp, int _priceGold, int _a, int _b){
	if(blank){
		name = _name;
		text = _text;
		priceExp = _priceExp;
		priceGold = _priceGold;
		a = _a;
		b = _b;
		save();
		blank = false;
		finish = false;
	}
	else{
		mess_act = true;
		runTimer = 200;
	}
}

void actQuest::update(){
	logic();
	draw();
}

void actQuest::Clear(){
	blank = true;
	finish = false;
	a = 0;
	b = 0;
	priceExp = 0;
	priceGold = 0;
	name = "";
	text = "";
	for(int i = 0; i < 5; i++){
		_event[i] = 0;
	}
}

void actQuest::draw(){
	if(is){
		App::drawBITMAP(Skills::mainGraph, 100, 100, 600, 400);
		if(blank == false){
			App::drawVariableText(name, 140, 140, -1, -1);
			App::drawVariableText(text, 140, 160, -1, -1);
			if(finish){
				if(cancelNo == false){
					textprintf_ex(bufor, font, 140, 180, makecol(0, 0, 0), -1, "Stan questa: zakonczony!");
					textprintf_ex(bufor, font, 140, 200, makecol(0, 0, 0), -1, "Nagroda: %d zlota i %d exp", priceGold, priceExp);
					if(App::button("OK!", button, l_button, 0, 0, 1, 0, "", 140, 250, 100, 35)){
						player.gold += priceGold;
						player.exp += priceExp;
						Clear();
					}
				}
				else
				{
					textprintf_ex(bufor, font, 140, 180, makecol(0, 0, 0), -1, "Podzadanie wykonane.");
				}
			}
			else{
				textprintf_ex(bufor, font, 140, 180, makecol(0, 0, 0), -1, "Stan questa: %d / %d", a, b);
				if(App::button("Porzuc questa. (Nie mozesz go wziac drugi raz!)", button, l_button, 0, 0, 1, 0, "", 140, 250, 400, 35)){
					Clear();
				}
			}
		}
	}
	if(mess_act){
		App::Message("Masz juz aktywny quest!", "", "", NULL);
		if(runTimer <= 0){
			mess_act = false;
		}
		else
		{
			runTimer--;
		}
	}
}

void actQuest::logic(){
	if(App::button("Questy", icon, icon, 0, 0, 1, 0, "", 0, 0, 100, 25) && runTimer <= 0){
		is = !is;

		runTimer = 30;
	}
	if(a >= b && finish == false){
		finish = true;
	}
}

void actQuest::save(){
	App::saveToFile("DATA/Quests/1/a.save", a);
	App::saveToFile("DATA/Quests/1/b.save", b);
	App::saveToFile("DATA/Quests/1/p_e.save", priceExp);
	App::saveToFile("DATA/Quests/1/p_gold.save", priceGold);
	App::saveToFile("DATA/Quests/1/blank.save", blank);
	App::saveToFile("DATA/Quests/1/cancelNo.save", cancelNo);

	std::ofstream name_f;
	name_f.open("DATA/Quests/1/name.save");
	std::ofstream text_f;
	text_f.open("DATA/Quests/1/text.save");
	name_f << name;
	text_f << text;
}

void actQuest::read(){
	int blank_i;
	App::readFromFile("DATA/Quests/1/a.save", a);
	App::readFromFile("DATA/Quests/1/b.save", b);
	App::readFromFile("DATA/Quests/1/p_e.save", priceExp);
	App::readFromFile("DATA/Quests/1/p_gold.save", priceGold);
	App::readFromFile("DATA/Quests/1/blank.save", blank_i);

	if(blank_i == 1)
		blank = true;
	else
		blank = false;

	std::ifstream name_f;
	name_f.open("DATA/Quests/1/name.save");
	std::ifstream text_f;
	text_f.open("DATA/Quests/1/text.save");
	std::ifstream cancelNo_f;
	cancelNo_f.open("DATA/Quests/1/cancelNo.save");
	name_f >> name;
	text_f >> text;
	cancelNo_f >> cancelNo;
}