#include "main.h"
#include <sstream>

BITMAP * Skills::skillGraph;
BITMAP * Skills::skillGraph_;
BITMAP * Skills::mainGraph;
BITMAP * Skills::on_off;

bool Skills::is;
int Skills::pkt;

std::vector <Skill> Skills::skills;

void Skills::Init(){
	skillGraph = load_bmp("Grafika/Gra/Default/skill.bmp", default_palette);
	skillGraph_ = load_bmp("Grafika/Gra/Default/skill_.bmp", default_palette);
	mainGraph = load_bmp("Grafika/Gra/Default/skillsMain.bmp", default_palette);
	on_off = load_bmp("Grafika/Gra/Default/questIcon.bmp", default_palette);

	is = false;
	pkt = 0;

	skills.push_back(Skill());
	skills[0].Init("Sila", 3, 1, 0, 0, 0);
	skills.push_back(Skill());
	skills[1].Init("Obrona", 3, 2, 0, 0, 0);
	skills.push_back(Skill());
	skills[2].Init("Witalnosc", 5, 3, 0, 0, 0);

	int never_save;
	App::readFromFile("DATA/never.save", never_save);
	if(never_save == 0){
		read();
	}
}

void Skills::Draw(){
	App::drawBITMAP(mainGraph, 50, 0, 700, 600);
	App::drawVariableText("Punkty UM: ", 150, 560, pkt, -1);
}

void Skills::Logic(){

}

void Skills::Menage(){
	for(unsigned int i = 0; i < skills.size(); i++){
		skills[i].Update();
	}
}

void Skills::Update(){
	if(is){
		Draw();
		Logic();
		Menage();

		if(App::button("Umki", on_off, on_off, 0, 0, 1, 0, "", 700, 0, 100, 25) && runTimer <= 0){
			is = false;
			runTimer = 35;
		}
	}
	else
	{
		if(App::button("Umki", on_off, on_off, 0, 0, 1, 0, "", 700, 0, 100, 25) && runTimer <= 0){
			is = true;
			runTimer = 35;
		}
	}
}

void Skills::save(){
	std::string scieszka_pkt = "DATA/UM/pkt.save";
	App::saveToFile(scieszka_pkt.c_str(), pkt);
	for(unsigned int i = 0; i < skills.size(); i++){
		std::string scieszka_lvl;
		std::stringstream sl_str;
		std::string sl_nor;
		sl_str << i;
		sl_str >> sl_nor;
		scieszka_lvl = "DATA/UM/" + sl_nor + "_lvl.save";

		App::saveToFile(scieszka_lvl.c_str(), skills[i].lvl);
	}
}

void Skills::read(){
	std::string scieszka_pkt = "DATA/UM/pkt.save";
	App::readFromFile(scieszka_pkt.c_str(), pkt);
	for(unsigned int i = 0; i < skills.size(); i++){
		std::string scieszka_lvl;
		std::stringstream sl_str;
		std::string sl_nor;
		sl_str << i;
		sl_str >> sl_nor;
		scieszka_lvl = "DATA/UM/" + sl_nor + "_lvl.save";

		App::readFromFile(scieszka_lvl.c_str(), skills[i].lvl);
	}
}