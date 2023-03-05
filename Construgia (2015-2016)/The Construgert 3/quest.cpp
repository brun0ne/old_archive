#include "main.h"
#include <sstream>

quest::quest(std::string _name, std::string _text, int _priceGold, int _priceExp, int _a, int _b, int _number){
	name = _name;
	text = _text;
	priceGold = _priceGold;
	priceExp = _priceExp;
	a = _a;
	b = _b;
	finish = false;
	number = _number;

	save();
}

void quest::init(std::string _name, std::string _text, int _priceGold, int _priceExp, int _a, int _b, int _number){
	name = _name;
	text = _text;
	priceGold = _priceGold;
	priceExp = _priceExp;
	a = _a;
	b = _b;
	number = _number;
}

void quest::update(){
	if(a >= b && finish == false){
		finish = true;
	}
}

void quest::save(){
	std::string saveUrl;
	std::stringstream ss;
	std::string ssS;
	ss << number;
	ss >> ssS;
	saveUrl = "DATA/Quests/" + ssS + "/";

	std::string aS, bS, priceGoldS, priceExpS, nameS, textS;

	aS = saveUrl + "a.save";
	bS = saveUrl + "b.save";
	priceGoldS = saveUrl + "pgS.save";
	priceExpS = saveUrl + "peS.save";
	nameS = saveUrl + "name.save";
	textS = saveUrl + "text.save";

	App::saveToFile(aS.c_str(), a);
	App::saveToFile(bS.c_str(), b);
	App::saveToFile(priceGoldS.c_str(), priceGold);
	App::saveToFile(priceExpS.c_str(), priceExp);

	std::ofstream nameFile;
	nameFile.open(nameS.c_str());
	std::ofstream textFile;
	textFile.open(textS.c_str());

	nameFile << name;
	textFile << text;
}

void quest::read(){
	std::string saveUrl;
	std::stringstream ss;
	std::string ssS;
	ss << number;
	ss >> ssS;
	saveUrl = "DATA/Quests/" + ssS + "/";

	std::string aS, bS, priceGoldS, priceExpS, nameS, textS;

	aS = saveUrl + "a.save";
	bS = saveUrl + "b.save";
	priceGoldS = saveUrl + "pgS.save";
	priceExpS = saveUrl + "peS.save";
	nameS = saveUrl + "name.save";
	textS = saveUrl + "text.save";

	App::readFromFile(aS.c_str(), a);
	App::readFromFile(bS.c_str(), b);
	App::readFromFile(priceGoldS.c_str(), priceGold);
	App::readFromFile(priceExpS.c_str(), priceExp);

	std::ifstream nameFile;
	nameFile.open(nameS.c_str());
	std::ifstream textFile;
	textFile.open(textS.c_str());

	std::getline(nameFile, name);
	std::getline(textFile, text);
}