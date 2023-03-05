#include "main.h"
#include "music.h"

SAMPLE * main_th;
SAMPLE * dunger_th;

void music_init(){
	main_th = load_sample("Main_Theme.wav");
	dunger_th = load_sample("Chapter_I_Theme.wav");
}