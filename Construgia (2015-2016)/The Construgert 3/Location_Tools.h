#include "main.h"

class LT
{
public:

	static void init();

	static void Bg_Not(BITMAP * bmp, int x, int w, int h);

	static bool Bg_OnClick(BITMAP * bmp, std::string name, int x, int w, int h);

	static bool Bg_OnStay(BITMAP * bmp, int x, int w, int h);

	static void Bg_Popup(BITMAP * bmp, std::string popupText, int x, int w, int h);

	static void Obj_Not(BITMAP * bmp, int x, int y, int w, int h);

	static void Pn_Not(BITMAP * bmp, int x, int y, int w, int h);

	static bool Dn_Enter(int x, int w);
};