#include "main.h"

void quest_system::init(){
	is = false;
	icon = load_bmp("Grafika/Gra/Default/questIcon.bmp", default_palette);
	area = load_bmp("Grafika/Gra/Default/questArea.bmp", default_palette);

	int first;
	App::readFromFile("DATA/never.save", first);
	if(first == 1){
		save();
	}
	else
	{
		read();
	}
}

void quest_system::push(std::string _name, std::string _text, int _priceGold, int _priceExp, int _a, int _b){
	list.push_back(quest(_name, _text, _priceGold, _priceExp, _a, _b, list.size() + 1));
}

void quest_system::pop(int number){
	list.erase(list.begin() + number);
}

void quest_system::draw(){
	App::drawBITMAP(area, 200, 0, 400, 600);
	rect(bufor, 200, 0, 600, 600, makecol(0, 0, 0));

	for(unsigned int i = 0; i < list.size(); i++){
		rect(bufor, 200, i * 100, 600, i * 100 + 100, makecol(0, 0, 0));
		App::drawVariableText(list[i].name.c_str(), 205, i * 100 + 35, -1, -1);
		App::drawVariableText(list[i].text.c_str(), 210, i * 100 + 50, -1, -1);
		if(list[i].finish == true){
			textprintf_ex(bufor, font, 210, i * 100 + 65, makecol(0, 0, 0), -1, "Stan questa: zakonczony!");
			textprintf_ex(bufor, font, 210, i * 100 + 75, makecol(0, 0, 0), -1, "Nagroda: %d zlota i %d exp", list[i].priceGold, list[i].priceExp);
			if(App::button("OK!", button, l_button, 0, 0, 1, 0, "", 480, i * 100 + 63, 100, 35)){
				player.gold += list[i].priceGold;
				player.exp += list[i].priceExp;
				pop(search(list[i].name));
			}
		}
		else
			textprintf_ex(bufor, font, 210, i * 100 + 65, makecol(0, 0, 0), -1, "Stan questa: %d / %d", list[i].a, list[i].b);
	}
}

void quest_system::logic(){
	/*if(App::button("Questy", icon, icon, 0, 0, 1, 0, "", 0, 0, 100, 25) && runTimer <= 0){
		is = !is;

		runTimer = 30;
	}*/
	for(unsigned int i = 0; i < list.size(); i++){
		list[i].update();
	}
}

void quest_system::update(){
	if(is == true){
		draw();
	}
	logic();
}

int quest_system::search(std::string keyword){
	for(unsigned int i = 0; i < list.size(); i++){
		if(list[i].name == keyword)
			return i;
	}
	return 777;
}

void quest_system::save(){
	for(unsigned int i = 0; i < list.size(); i++){
		list[i].save();
	}
	App::saveToFile("DATA/Quests/size.save", list.size());
}

void quest_system::read(){
	int size;
	App::readFromFile("DATA/Quests/size.save", size);
	for(int i = 0; i < size; i++){
		list.push_back(quest("", "", 0, 0, 0, 0, i + 1));
	}

	for(int i = 0; i < size; i++){
		list[i].read();
	}
}