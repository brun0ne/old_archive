#include "main.h"

class App
{
public:

	static void init();

	static void createMask();

	static void drawBufor();

	static void setLight(int light);

	static void setLightColor(int r, int g, int b);

	static void drawBITMAP(BITMAP * bitmap, int x, int y, int w, int h);

	static void drawText(const char * text, int x, int y);

	static void drawVariableText(std::string text, int x, int y, int var, int color);

	static void drawViariableStringText(std::string text, int x, int y, std::string var);

	static bool onSlide(int x, int y, int w, int h);

	static bool onClick(int x, int y, int w, int h);

	static void readKey(std::string & text, bool read);
	
	static void saveToFile(const char * sciezka, int zmienna);

	static void readFromFile(std::string sciezka, int & zmienna);

	////////////////////////////////////////////////////////////////////////////

	static bool button(const char * text, BITMAP * defaultBitmap, BITMAP * onSlideBitmap, bool varOn, bool stringOn, bool center, int var, std::string stringVar, int x, int y, int w, int h);

	static void drawBITMAPtext(BITMAP * bitmap, const char * text, bool varOn, int endl, int x, int y, int w, int h, int var, bool popup);

	static void textArea(std::string & text, BITMAP * bitmap, int x, int y, int w, int h);

	static void popup(std::string text, bool isVa);

	////////////////////////////////////////////////////////////////////////////
	//Methods for OBCA 2D Engine  (Object Brunon C++ Algorithms 2D Engine)

	static void Player_Collision(int x, int y, int w, int h);

	static void Message(std::string message, std::string message2, std::string message3, BITMAP * bmp);
};