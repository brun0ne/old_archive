#ifndef main_hpp
#define main_hpp

#include <allegro.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <fstream>
#include <fstream>
#include <vector>
#include <string>
//#include <bass.h>

#include "App.h"
#include "World.h"
#include "eq.h"
#include "quests_system.h"
#include "actQuest.h"
#include "Skills.h"
#include "case_element.h"

#include "Player.h"
#include "Missile.h"
#include "Mob.h"
#include "NPC.h"
#include "Item.h"
#include "Trasher.h"

void game();

extern BITMAP * bufor;
extern BITMAP * popupBufor;
extern BITMAP * mask;

extern int speedXX;

extern SAMPLE * music;
extern bool musicIs;

extern Player player;
extern World world;
extern quest_system Quest_System;
extern actQuest actquest;

extern int runTimer;
extern bool drawToScreen;

extern BITMAP * button;
extern BITMAP * l_button;

extern Missile missile1;
extern Missile missile2;

#endif