#include "main.h"

int Opening::id;
int Opening::lvl;

void Opening::Init(int lvl_){
	id = 0;
	lvl = lvl_;
}

void Opening::PushToEq(){
	if(lvl == 0){
		if(eq::filons_paper == 0)
			id = ( std::rand() % 5 ) + 0;
		else
			id = ( std::rand() % 3 ) + 0;
		if(id == 0)
			eq::pushToArea("Slaby_Pocisk", "poczatkowy_ex", 10, 0, 1, 0, 50);
		else if(id == 1)
			eq::pushToArea("[EPICKI]_Kawal_Skaly", "skala", 25, 0, 1, 0, 75);
		else if(id == 2)
			eq::pushToArea("Stare_Jablko", "jablko", 0, 15, 1, 2, 1);
		else if((id == 3 || id == 4) && eq::filons_paper == 0){
			eq::pushToArea("Poszarpana_Kartka", "kartka", 0, 0, 1, 4, 1);
			eq::filons_paper = 1;
			App::saveToFile("DATA/Other/filons_paper.save", eq::filons_paper);
		}
	}
	else if(lvl == 1){
		id = ( std::rand() % 5 ) + 0;
		if(id == 0)
			eq::pushToArea("Drewniany_Pocisk", "drewniany", 30, 0, 1, 0, 300);
		else if(id == 1)
			eq::pushToArea("[EPICKI]_Ultra_Pocisk", "ultra_lesny", 100, 0, 1, 0, 25);
		else if(id == 2)
			eq::pushToArea("Pocisk_Wieloskokowy", "test", 15, 0, 1, 0, 1000);
		else if(id == 3)
			eq::pushToArea("Pocisk_Jablkowy", "jablko", 20, 0, 1, 0, 15);
		else if(id == 4)
			eq::pushToArea("Kanapka", "kanapka", 0, 25, 1, 2, 1);
		else if(id == 5)
			eq::pushToArea("[EPICKI]_Eliksir Zycia", "eliksirHp", 0, 250, 1, 2, 1);
	}
	else if(lvl == 2){
		id = ( std::rand() % 5 ) + 0;
		if(id == 0)
			eq::pushToArea("Lepszy_Drewniany_Pocisk", "drewniany", 30, 0, 1, 0, 300);
		else if(id == 1)
			eq::pushToArea("[EPICKI]_Pocisk-Kosa", "kosa", 200, 0, 1, 0, 50);
		else if(id == 2)
			eq::pushToArea("Lepszy_Pocisk_Wieloskokowy", "test", 20, 0, 1, 0, 1000);
		else if(id == 3)
			eq::pushToArea("Pocisk_Kanapkowy", "kanapka", 25, 0, 1, 0, 15);
		else if(id == 4)
			eq::pushToArea("Kanapka", "kanapka", 0, 25, 1, 2, 1);
		else if(id == 5)
			eq::pushToArea("[EPICKI]_Uzdrawiacz", "eliksirHp", 0, 350, 1, 2, 1);
	}
}

void Opening::Update(){
	//...
}