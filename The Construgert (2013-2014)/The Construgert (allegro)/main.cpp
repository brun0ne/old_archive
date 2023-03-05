#include <allegro.h>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

int mx = 0, my = 0, mb = 0;
unsigned long long int money = 0;
int kilof = 0;
int Gracz_x = 250, Gracz_y = 305;
bool music = true;
int config_screen;

void myszka()
{
    if( mx != mouse_x || my != mouse_y || mb != mouse_b )
    {
        mx = mouse_x;
        my = mouse_y;
        mb = mouse_b;
    }
};

int ekwipunek(){
	//Pobieranie grafiki
	BITMAP * bufor = NULL;
	bufor = create_bitmap( 640, 480 );
	while(!key[KEY_F]){
		//Kolorowanie t³a
		clear_to_color( bufor, makecol( 153, 217, 234 ) );
		//Wyœwietlanie EQ
		//Standarowe GUI
		textprintf_ex( bufor, font, 450, 20, makecol( 255, 255, 255 ), - 1, "Craft Points: %d", money); 
		textprintf_ex( bufor, font, 220, 20, makecol( 255, 255, 255 ), - 1, "EQ ON: E");
		textprintf_ex( bufor, font, 220, 30, makecol( 255, 255, 255 ), - 1, "EQ OFF: F");
		//GUI EQ
		if(kilof == 0){
			textprintf_ex( bufor, font, 20, 180, makecol( 255, 255, 255 ), - 1, "Your current pickaxe: NULL");
			textprintf_ex( bufor, font, 20, 200, makecol( 255, 255, 255 ), - 1, "This pickaxe you can dig: Tree");
			textprintf_ex( bufor, font, 20, 230, makecol( 255, 255, 255 ), - 1, "To buy Wooden Pickaxe click A | | PRICE: 15 Craft Points");
			if(money >= 15 && key[KEY_A]){
				kilof = 1;
				money -= 15;
			}
		}
		if(kilof == 1){
			textprintf_ex( bufor, font, 20, 180, makecol( 255, 255, 255 ), - 1, "Your current pickaxe: Wooden Pickaxe");
			textprintf_ex( bufor, font, 20, 200, makecol( 255, 255, 255 ), - 1, "This pickaxe you can dig: Stone");
			textprintf_ex( bufor, font, 20, 230, makecol( 255, 255, 255 ), - 1, "To buy Stone Pickaxe click A | | PRICE: 1000 Craft Points");
			if(money >= 1000 && key[KEY_A]){
				kilof = 2;
				money -= 1000;
			}
		}
		if(kilof == 2){
			textprintf_ex( bufor, font, 20, 180, makecol( 255, 255, 255 ), - 1, "Your current pickaxe: Stone Pickaxe");
			textprintf_ex( bufor, font, 20, 200, makecol( 255, 255, 255 ), - 1, "This pickaxe you can dig: Stone, Iron Ore");
			textprintf_ex( bufor, font, 20, 230, makecol( 255, 255, 255 ), - 1, "To buy Iron Pickaxe click A | | PRICE: 5000 Craft Points");
			if(money >= 5000 && key[KEY_A]){
				kilof = 3;
				money -= 5000;
			}
		}
		if(kilof == 3){
			textprintf_ex( bufor, font, 20, 180, makecol( 255, 255, 255 ), - 1, "Your current pickaxe: Iron Pickaxe");
			textprintf_ex( bufor, font, 20, 200, makecol( 255, 255, 255 ), - 1, "This pickaxe you can dig: Stone, Iron Ore, Gold Ore");
			textprintf_ex( bufor, font, 20, 230, makecol( 255, 255, 255 ), - 1, "To buy Gold Pickaxe click A | | PRICE: 10 000 Craft Points");
			if(money >= 10000 && key[KEY_A]){
				kilof = 4;
				money -= 10000;
			}
		}
		if(kilof == 4){
			textprintf_ex( bufor, font, 20, 180, makecol( 255, 255, 255 ), - 1, "Your current pickaxe: Gold Pickaxe");
			textprintf_ex( bufor, font, 20, 200, makecol( 255, 255, 255 ), - 1, "This pickaxe you can dig: Stone, Iron Ore, Gold Ore, Diamond");
			textprintf_ex( bufor, font, 20, 230, makecol( 255, 255, 255 ), - 1, "To buy Diamond Pickaxe click A | | PRICE: 30 000 Craft Points");
			if(money >= 30000 && key[KEY_A]){
				kilof = 5;
				money -= 30000;
			}
		}
		if(kilof == 5){
			textprintf_ex( bufor, font, 20, 180, makecol( 255, 255, 255 ), - 1, "Your current pickaxe: Diamond Pickaxe");
			textprintf_ex( bufor, font, 20, 200, makecol( 255, 255, 255 ), - 1, "This pickaxe you can dig: Stone, Iron Ore, Gold Ore, Diamond, Tasigaw");
			textprintf_ex( bufor, font, 20, 230, makecol( 255, 255, 255 ), - 1, "To buy Tasigaw Pickaxe click A | | PRICE: 500 000 Craft Points");
			if(money >= 500000 && key[KEY_A]){
				kilof = 6;
				money -= 500000;
			}
		}
		if(kilof == 6){
			textprintf_ex( bufor, font, 20, 180, makecol( 255, 255, 255 ), - 1, "Your current pickaxe: Tasigaw Pickaxe");
			textprintf_ex( bufor, font, 20, 200, makecol( 255, 255, 255 ), - 1, "This pickaxe you can dig: Stone, Iron Ore, Gold Ore, Diamond, Tasigaw,");
			textprintf_ex( bufor, font, 20, 210, makecol( 255, 255, 255 ), - 1, "Red Matter");
			textprintf_ex( bufor, font, 20, 230, makecol( 255, 255, 255 ), - 1, "To buy Red Matter Pickaxe click A | | PRICE: 1 500 000 Craft Points");
			if(money >= 1500000 && key[KEY_A]){
				kilof = 7;
				money -= 1500000;
			}
		}
		if(kilof == 7){
			textprintf_ex( bufor, font, 20, 180, makecol( 255, 255, 255 ), - 1, "Your current pickaxe: Red Matter Pickaxe");
			textprintf_ex( bufor, font, 20, 200, makecol( 255, 255, 255 ), - 1, "This pickaxe you can dig: Stone, Iron Ore, Gold Ore, Diamond, Tasigaw,");
			textprintf_ex( bufor, font, 20, 210, makecol( 255, 255, 255 ), - 1, "Red Matter, Orange Matter");
			textprintf_ex( bufor, font, 20, 240, makecol( 255, 255, 255 ), - 1, "To buy Orange Matter Pickaxe click A | | PRICE: 2 500 000 Craft Points");
			if(money >= 2500000 && key[KEY_A]){
				kilof = 8;
				money -= 2500000;
			}
		}
		if(kilof == 8){
			textprintf_ex( bufor, font, 20, 180, makecol( 255, 255, 255 ), - 1, "Your current pickaxe: Orange Matter Pickaxe");
			textprintf_ex( bufor, font, 20, 200, makecol( 255, 255, 255 ), - 1, "This pickaxe you can dig: Stone, Iron Ore, Gold Ore, Diamond, Tasigaw,");
			textprintf_ex( bufor, font, 20, 210, makecol( 255, 255, 255 ), - 1, "Red Matter, Orange Matter, Yellow Matter");
			textprintf_ex( bufor, font, 20, 240, makecol( 255, 255, 255 ), - 1, "To buy Yellow Matter Pickaxe click A | | PRICE: 3 500 000 Craft Points");
			if(money >= 3500000 && key[KEY_A]){
				kilof = 9;
				money -= 3500000;
			}
		}
		if(kilof == 9){
			textprintf_ex( bufor, font, 20, 180, makecol( 255, 255, 255 ), - 1, "Your current pickaxe: Yellow Matter Pickaxe");
			textprintf_ex( bufor, font, 20, 200, makecol( 255, 255, 255 ), - 1, "This pickaxe you can dig: Stone, Iron Ore, Gold Ore, Diamond, Tasigaw,");
			textprintf_ex( bufor, font, 20, 210, makecol( 255, 255, 255 ), - 1, "Red Matter, Orange Matter, Yellow Matter, Blue Matter");
			textprintf_ex( bufor, font, 20, 240, makecol( 255, 255, 255 ), - 1, "To buy Blue Matter Pickaxe click A | | PRICE: 5 000 000 Craft Points");
			if(money >= 5000000 && key[KEY_A]){
				kilof = 10;
				money -= 5000000;
			}
		}
		if(kilof == 10){
			textprintf_ex( bufor, font, 20, 180, makecol( 255, 255, 255 ), - 1, "Your current pickaxe: Blue Matter Pickaxe");
			textprintf_ex( bufor, font, 20, 200, makecol( 255, 255, 255 ), - 1, "This pickaxe you can dig: Stone, Iron Ore, Gold Ore, Diamond, Tasigaw,");
			textprintf_ex( bufor, font, 20, 210, makecol( 255, 255, 255 ), - 1, "Red Matter, Orange Matter, Yellow Matter, Blue Matter");
			textprintf_ex( bufor, font, 20, 240, makecol( 255, 255, 255 ), - 1, "YOU HAVE GOT THE BEST PICKAXE! CONGRATULATIONS! :-)");
		}

		blit( bufor, screen, 0, 0, 0, 0, 640, 480 ); 
	}
	return 0;
};

void odczytGry(){
	///////////////////////////////////////
	ifstream savem;
	savem.open( "DATA/m0002e4sss.txt" );
	savem >> money;
	///////////////////////////////////////
	ifstream savek;
	savek.open( "DATA/k1lo00ss.txt" );
	savek >> kilof;
	//////////////////////////////////////
	ifstream saves;
	saves.open( "DATA/config.txt");
	saves >> config_screen;
	//////////////////////////////////////
};

void zapisGry(){
	//////////////////////////////////////
	ofstream savemt;
    savemt.open("DATA/m0002e4sss.txt");
	savemt<<money<<endl;
	/////////////////////////////////////
	ofstream savemkt;
    savemkt.open("DATA/k1lo00ss.txt");
	savemkt<<kilof<<endl;
	/////////////////////////////////////
};

int kopalnia_lvl2_start(){
	//Muzyka
	install_sound( DIGI_AUTODETECT, MIDI_AUTODETECT, "" );
	set_volume( 255, 255 );
	SAMPLE * muzyka1 = NULL;
	muzyka1 = load_sample( "Muzyka/Project_System_12_-_Breath_of_Hope.wav" );
	play_sample( muzyka1, 255, 127, 1000, 1 );
	label:
	//Funkcje wstêpne
	clear_to_color( screen, makecol( 150, 150, 150 ) );
	srand( time( NULL ) );
	install_mouse();
    show_mouse( screen );
	unscare_mouse();
	//Pobieranie grafiki
	BITMAP * gracz = NULL;
	if(kilof == 0){
		gracz = load_bmp("Grafika/Gracz/gracz.bmp", default_palette);
	}
	if(kilof == 1){
		gracz = load_bmp("Grafika/Gracz/gracz_z_drewnianym_kilofem.bmp", default_palette);
	}
	if(kilof == 2){
		gracz = load_bmp("Grafika/Gracz/gracz_z_kamiennym_kilofem.bmp", default_palette);
	}
	if(kilof == 3){
		gracz = load_bmp("Grafika/Gracz/gracz_z_zelaznym_kilofem.bmp", default_palette);
	}
	if(kilof == 4){
		gracz = load_bmp("Grafika/Gracz/gracz_ze_zlotym_kilofem.bmp", default_palette);
	}
	if(kilof == 5){
		gracz = load_bmp("Grafika/Gracz/gracz_z_diamentowym_kilofem.bmp", default_palette);
	}
	if(kilof == 6){
		gracz = load_bmp("Grafika/Gracz/gracz_z_tasigaw_kilofem.bmp", default_palette);
	}
	if(kilof == 7){
		gracz = load_bmp("Grafika/Gracz/gracz_z_redmatter_kilofem.bmp", default_palette);
	}
	if(kilof == 8){
		gracz = load_bmp("Grafika/Gracz/gracz_z_orangematter_kilofem.bmp", default_palette);
	}
	if(kilof == 9){
		gracz = load_bmp("Grafika/Gracz/gracz_z_yellowmatter_kilofem.bmp", default_palette);
	}
	if(kilof == 10){
		gracz = load_bmp("Grafika/Gracz/gracz_z_bluematter_kilofem.bmp", default_palette);
	}
	BITMAP * podloze1 = NULL;
	podloze1 = load_bmp("Grafika/podloze_kopalnia1.bmp", default_palette);
	BITMAP * podloze2 = NULL;
	podloze2 = load_bmp("Grafika/podloze_kopalnia2.bmp", default_palette);
	BITMAP * podloze3 = NULL;
	podloze3 = load_bmp("Grafika/podloze_kopalnia3.bmp", default_palette);
	BITMAP * podloze4 = NULL;
	podloze4 = load_bmp("Grafika/podloze_kopalnia4.bmp", default_palette);
	BITMAP * red_matter = NULL;
	red_matter = load_bmp("Grafika/red_matter.bmp", default_palette);
	BITMAP * orange_matter = NULL;
	orange_matter = load_bmp("Grafika/orange_matter.bmp", default_palette);
	BITMAP * yellow_matter = NULL;
	yellow_matter = load_bmp("Grafika/yellow_matter.bmp", default_palette);
	BITMAP * blue_matter = NULL;
	blue_matter = load_bmp("Grafika/blue_matter.bmp", default_palette);
	BITMAP * MineCreature = NULL;
	MineCreature = load_bmp("Grafika/Potwory/Mine_Creature/Mine_Creature.bmp", default_palette);
	BITMAP * bufor = NULL;
	bufor = create_bitmap( 640, 480 );
	//Generowanie losowych koordynatów obiektów kopalni (X)
	//Mine Creature
	bool kierunekMC1 = true;
	bool MC1 = true;
	int zdrowieMC1 = 75;
	bool klikniecie = false;
	int liczbaLosowaniaMC = (std::rand() % 10) + 0;
	if(liczbaLosowaniaMC >= 0 && liczbaLosowaniaMC <= 5){
		kierunekMC1 = true;
	}
	if(liczbaLosowaniaMC >= 6 && liczbaLosowaniaMC <= 10){
		kierunekMC1 = false;
	}
	//int mc1_x = (std::rand() % 247) + 120;
	int mc1_x = 295;
	//Red Matter
	int rm1_x = (std::rand() % 200) + 0;
	int rm2_x = (std::rand() % 200) + 200;
	int rm3_x = (std::rand() % 45) + 400;
	int rm4_x = (std::rand() % 100) + 450;
	int rm5_x = (std::rand() % 200) + 0;
	int rm6_x = (std::rand() % 200) + 200;
	int rm7_x = (std::rand() % 45) + 400;
	int rm8_x = (std::rand() % 100) + 450;
	int rm9_x = (std::rand() % 200) + 0;
	int rm10_x = (std::rand() % 200) + 200;
	int rm11_x = (std::rand() % 45) + 400;
	int rm12_x = (std::rand() % 100) + 450;
	//Red Matter - nielosowe (Y)
	int rm1_y = 353;
	int rm2_y = 353;
	int rm3_y = 353;
	int rm4_y = 353;
	int rm5_y = 353;
	int rm6_y = 353;
	int rm7_y = 393;
	int rm8_y = 393;
	int rm9_y = 393;
	int rm10_y = 393;
	int rm11_y = 393;
	int rm12_y = 393;
	//Orange Matter
	int om1_x = (std::rand() % 200) + 0;
	int om2_x = (std::rand() % 200) + 200;
	int om3_x = (std::rand() % 45) + 400;
	int om4_x = (std::rand() % 100) + 450;
	int om5_x = (std::rand() % 200) + 0;
	int om6_x = (std::rand() % 200) + 200;
	int om7_x = (std::rand() % 45) + 400;
	int om8_x = (std::rand() % 100) + 450;
	int om9_x = (std::rand() % 200) + 0;
	int om10_x = (std::rand() % 200) + 200;
	int om11_x = (std::rand() % 45) + 400;
	int om12_x = (std::rand() % 100) + 450;
	//Orange Matter - nielosowe (Y)
	int om1_y = 313;
	int om2_y = 313;
	int om3_y = 313;
	int om4_y = 313;
	int om5_y = 313;
	int om6_y = 313;
	int om7_y = 273;
	int om8_y = 273;
	int om9_y = 273;
	int om10_y = 273;
	int om11_y = 273;
	int om12_y = 273;
	//Yellow Matter
	int ym1_x = (std::rand() % 200) + 0;
	int ym2_x = (std::rand() % 200) + 200;
	int ym3_x = (std::rand() % 45) + 400;
	int ym4_x = (std::rand() % 100) + 450;
	int ym5_x = (std::rand() % 200) + 0;
	int ym6_x = (std::rand() % 200) + 200;
	int ym7_x = (std::rand() % 45) + 400;
	int ym8_x = (std::rand() % 100) + 450;
	int ym9_x = (std::rand() % 200) + 0;
	int ym10_x = (std::rand() % 200) + 200;
	int ym11_x = (std::rand() % 45) + 400;
	int ym12_x = (std::rand() % 100) + 450;
	//Yellow Matter - nielosowe (Y)
	int ym1_y = 233;
	int ym2_y = 233;
	int ym3_y = 233;
	int ym4_y = 233;
	int ym5_y = 233;
	int ym6_y = 233;
	int ym7_y = 193;
	int ym8_y = 193;
	int ym9_y = 193;
	int ym10_y = 193;
	int ym11_y = 193;
	int ym12_y = 193;
	//Blue Matter
	int bm1_x = (std::rand() % 200) + 0;
	int bm2_x = (std::rand() % 200) + 200;
	int bm3_x = (std::rand() % 45) + 400;
	int bm4_x = (std::rand() % 100) + 450;
	int bm5_x = (std::rand() % 200) + 0;
	int bm6_x = (std::rand() % 200) + 200;
	int bm7_x = (std::rand() % 45) + 400;
	int bm8_x = (std::rand() % 100) + 450;
	int bm9_x = (std::rand() % 200) + 0;
	int bm10_x = (std::rand() % 200) + 200;
	int bm11_x = (std::rand() % 45) + 400;
	int bm12_x = (std::rand() % 100) + 450;
	//Blue Matter - nielosowe (Y)
	int bm1_y = 153;
	int bm2_y = 153;
	int bm3_y = 153;
	int bm4_y = 153;
	int bm5_y = 153;
	int bm6_y = 153;
	int bm7_y = 113;
	int bm8_y = 113;
	int bm9_y = 113;
	int bm10_y = 113;
	int bm11_y = 113;
	int bm12_y = 113;
	//Zmienne pozycji objektów
	//Red Matter
	//- (X)
	int rm1_pos_1 = rm1_x;
	int rm2_pos_1 = rm2_x;
	int rm3_pos_1 = rm3_x;
	int rm4_pos_1 = rm4_x;
	int rm5_pos_1 = rm5_x;
	int rm6_pos_1 = rm6_x;
	int rm7_pos_1 = rm7_x;
	int rm8_pos_1 = rm8_x;
	int rm9_pos_1 = rm9_x;
	int rm10_pos_1 = rm10_x;
	int rm11_pos_1 = rm11_x;
	int rm12_pos_1 = rm12_x;
	//+ (X)
	int rm1_pos_2 = rm1_x + 40;
	int rm2_pos_2 = rm2_x + 40;
	int rm3_pos_2 = rm3_x + 40;
	int rm4_pos_2 = rm4_x + 40;
	int rm5_pos_2 = rm5_x + 40;
	int rm6_pos_2 = rm6_x + 40;
	int rm7_pos_2 = rm7_x + 40;
	int rm8_pos_2 = rm8_x + 40;
	int rm9_pos_2 = rm9_x + 40;
	int rm10_pos_2 = rm10_x + 40;
	int rm11_pos_2 = rm11_x + 40;
	int rm12_pos_2 = rm12_x + 40;
	//- (Y)
	int rm1_pos_1_y = rm1_y;
	int rm2_pos_1_y = rm2_y;
	int rm3_pos_1_y = rm3_y;
	int rm4_pos_1_y = rm4_y;
	int rm5_pos_1_y = rm5_y;
	int rm6_pos_1_y = rm6_y;
	int rm7_pos_1_y = rm7_y;
	int rm8_pos_1_y = rm8_y;
	int rm9_pos_1_y = rm9_y;
	int rm10_pos_1_y = rm10_y;
	int rm11_pos_1_y = rm11_y;
	int rm12_pos_1_y = rm12_y;
	//+ (Y)
	int rm1_pos_2_y = rm1_y + 40;
	int rm2_pos_2_y = rm2_y + 40;
	int rm3_pos_2_y = rm3_y + 40;
	int rm4_pos_2_y = rm4_y + 40;
	int rm5_pos_2_y = rm5_y + 40;
	int rm6_pos_2_y = rm6_y + 40;
	int rm7_pos_2_y = rm7_y + 40;
	int rm8_pos_2_y = rm8_y + 40;
	int rm9_pos_2_y = rm9_y + 40;
	int rm10_pos_2_y = rm10_y + 40;
	int rm11_pos_2_y = rm11_y + 40;
	int rm12_pos_2_y = rm12_y + 40;
	//Orange Matter
	//- (X)
	int om1_pos_1 = om1_x;
	int om2_pos_1 = om2_x;
	int om3_pos_1 = om3_x;
	int om4_pos_1 = om4_x;
	int om5_pos_1 = om5_x;
	int om6_pos_1 = om6_x;
	int om7_pos_1 = om7_x;
	int om8_pos_1 = om8_x;
	int om9_pos_1 = om9_x;
	int om10_pos_1 = om10_x;
	int om11_pos_1 = om11_x;
	int om12_pos_1 = om12_x;
	//+ (X)
	int om1_pos_2 = om1_x + 40;
	int om2_pos_2 = om2_x + 40;
	int om3_pos_2 = om3_x + 40;
	int om4_pos_2 = om4_x + 40;
	int om5_pos_2 = om5_x + 40;
	int om6_pos_2 = om6_x + 40;
	int om7_pos_2 = om7_x + 40;
	int om8_pos_2 = om8_x + 40;
	int om9_pos_2 = om9_x + 40;
	int om10_pos_2 = om10_x + 40;
	int om11_pos_2 = om11_x + 40;
	int om12_pos_2 = om12_x + 40;
	//- (Y)
	int om1_pos_1_y = om1_y;
	int om2_pos_1_y = om2_y;
	int om3_pos_1_y = om3_y;
	int om4_pos_1_y = om4_y;
	int om5_pos_1_y = om5_y;
	int om6_pos_1_y = om6_y;
	int om7_pos_1_y = om7_y;
	int om8_pos_1_y = om8_y;
	int om9_pos_1_y = om9_y;
	int om10_pos_1_y = om10_y;
	int om11_pos_1_y = om11_y;
	int om12_pos_1_y = om12_y;
	//+ (Y)
	int om1_pos_2_y = om1_y + 40;
	int om2_pos_2_y = om2_y + 40;
	int om3_pos_2_y = om3_y + 40;
	int om4_pos_2_y = om4_y + 40;
	int om5_pos_2_y = om5_y + 40;
	int om6_pos_2_y = om6_y + 40;
	int om7_pos_2_y = om7_y + 40;
	int om8_pos_2_y = om8_y + 40;
	int om9_pos_2_y = om9_y + 40;
	int om10_pos_2_y = om10_y + 40;
	int om11_pos_2_y = om11_y + 40;
	int om12_pos_2_y = om12_y + 40;
	//Yellow Matter
	//- (X)
	int ym1_pos_1 = ym1_x;
	int ym2_pos_1 = ym2_x;
	int ym3_pos_1 = ym3_x;
	int ym4_pos_1 = ym4_x;
	int ym5_pos_1 = ym5_x;
	int ym6_pos_1 = ym6_x;
	int ym7_pos_1 = ym7_x;
	int ym8_pos_1 = ym8_x;
	int ym9_pos_1 = ym9_x;
	int ym10_pos_1 = ym10_x;
	int ym11_pos_1 = ym11_x;
	int ym12_pos_1 = ym12_x;
	//+ (X)
	int ym1_pos_2 = ym1_x + 40;
	int ym2_pos_2 = ym2_x + 40;
	int ym3_pos_2 = ym3_x + 40;
	int ym4_pos_2 = ym4_x + 40;
	int ym5_pos_2 = ym5_x + 40;
	int ym6_pos_2 = ym6_x + 40;
	int ym7_pos_2 = ym7_x + 40;
	int ym8_pos_2 = ym8_x + 40;
	int ym9_pos_2 = ym9_x + 40;
	int ym10_pos_2 = ym10_x + 40;
	int ym11_pos_2 = ym11_x + 40;
	int ym12_pos_2 = ym12_x + 40;
	//- (Y)
	int ym1_pos_1_y = ym1_y;
	int ym2_pos_1_y = ym2_y;
	int ym3_pos_1_y = ym3_y;
	int ym4_pos_1_y = ym4_y;
	int ym5_pos_1_y = ym5_y;
	int ym6_pos_1_y = ym6_y;
	int ym7_pos_1_y = ym7_y;
	int ym8_pos_1_y = ym8_y;
	int ym9_pos_1_y = ym9_y;
	int ym10_pos_1_y = ym10_y;
	int ym11_pos_1_y = ym11_y;
	int ym12_pos_1_y = ym12_y;
	//+ (Y)
	int ym1_pos_2_y = ym1_y + 40;
	int ym2_pos_2_y = ym2_y + 40;
	int ym3_pos_2_y = ym3_y + 40;
	int ym4_pos_2_y = ym4_y + 40;
	int ym5_pos_2_y = ym5_y + 40;
	int ym6_pos_2_y = ym6_y + 40;
	int ym7_pos_2_y = ym7_y + 40;
	int ym8_pos_2_y = ym8_y + 40;
	int ym9_pos_2_y = ym9_y + 40;
	int ym10_pos_2_y = ym10_y + 40;
	int ym11_pos_2_y = ym11_y + 40;
	int ym12_pos_2_y = ym12_y + 40;
	//Blue Matter
	//- (X)
	int bm1_pos_1 = bm1_x;
	int bm2_pos_1 = bm2_x;
	int bm3_pos_1 = bm3_x;
	int bm4_pos_1 = bm4_x;
	int bm5_pos_1 = bm5_x;
	int bm6_pos_1 = bm6_x;
	int bm7_pos_1 = bm7_x;
	int bm8_pos_1 = bm8_x;
	int bm9_pos_1 = bm9_x;
	int bm10_pos_1 = bm10_x;
	int bm11_pos_1 = bm11_x;
	int bm12_pos_1 = bm12_x;
	//+ (X)
	int bm1_pos_2 = bm1_x + 40;
	int bm2_pos_2 = bm2_x + 40;
	int bm3_pos_2 = bm3_x + 40;
	int bm4_pos_2 = bm4_x + 40;
	int bm5_pos_2 = bm5_x + 40;
	int bm6_pos_2 = bm6_x + 40;
	int bm7_pos_2 = bm7_x + 40;
	int bm8_pos_2 = bm8_x + 40;
	int bm9_pos_2 = bm9_x + 40;
	int bm10_pos_2 = bm10_x + 40;
	int bm11_pos_2 = bm11_x + 40;
	int bm12_pos_2 = bm12_x + 40;
	//- (Y)
	int bm1_pos_1_y = bm1_y;
	int bm2_pos_1_y = bm2_y;
	int bm3_pos_1_y = bm3_y;
	int bm4_pos_1_y = bm4_y;
	int bm5_pos_1_y = bm5_y;
	int bm6_pos_1_y = bm6_y;
	int bm7_pos_1_y = bm7_y;
	int bm8_pos_1_y = bm8_y;
	int bm9_pos_1_y = bm9_y;
	int bm10_pos_1_y = bm10_y;
	int bm11_pos_1_y = bm11_y;
	int bm12_pos_1_y = bm12_y;
	//+ (Y)
	int bm1_pos_2_y = bm1_y + 40;
	int bm2_pos_2_y = bm2_y + 40;
	int bm3_pos_2_y = bm3_y + 40;
	int bm4_pos_2_y = bm4_y + 40;
	int bm5_pos_2_y = bm5_y + 40;
	int bm6_pos_2_y = bm6_y + 40;
	int bm7_pos_2_y = bm7_y + 40;
	int bm8_pos_2_y = bm8_y + 40;
	int bm9_pos_2_y = bm9_y + 40;
	int bm10_pos_2_y = bm10_y + 40;
	int bm11_pos_2_y = bm11_y + 40;
	int bm12_pos_2_y = bm12_y + 40;
	//Zmienne wyœwietlania objektów
	//Red Matter
	bool rm1 = false;
	bool rm2 = false;
	bool rm3 = false;
	bool rm4 = false;
	bool rm5 = false;
	bool rm6 = false;
	bool rm7 = false;
	bool rm8 = false;
	bool rm9 = false;
	bool rm10 = false;
	bool rm11 = false;
	bool rm12 = false;
	//Orange Matter
	bool om1 = false;
	bool om2 = false;
	bool om3 = false;
	bool om4 = false;
	bool om5 = false;
	bool om6 = false;
	bool om7 = false;
	bool om8 = false;
	bool om9 = false;
	bool om10 = false;
	bool om11 = false;
	bool om12 = false;
	//Yellow Matter
	bool ym1 = true;
	bool ym2 = true;
	bool ym3 = true;
	bool ym4 = true;
	bool ym5 = true;
	bool ym6 = true;
	bool ym7 = true;
	bool ym8 = true;
	bool ym9 = true;
	bool ym10 = true;
	bool ym11 = true;
	bool ym12 = true;
	//Blue Matter
	bool bm1 = false;
	bool bm2 = false;
	bool bm3 = false;
	bool bm4 = false;
	bool bm5 = false;
	bool bm6 = false;
	bool bm7 = false;
	bool bm8 = false;
	bool bm9 = false;
	bool bm10 = false;
	bool bm11 = false;
	bool bm12 = false;
	//Zmienne bycia objektów
	//Red Matter
	bool this_rm1 = false;
	bool this_rm2 = false;
	bool this_rm3 = false;
	bool this_rm4 = false;
	bool this_rm5 = false;
	bool this_rm6 = false;
	bool this_rm7 = false;
	bool this_rm8 = false;
	bool this_rm9 = false;
	bool this_rm10 = false;
	bool this_rm11 = false;
	bool this_rm12 = false;
	//Orange Matter
	bool this_om1 = false;
	bool this_om2 = false;
	bool this_om3 = false;
	bool this_om4 = false;
	bool this_om5 = false;
	bool this_om6 = false;
	bool this_om7 = false;
	bool this_om8 = false;
	bool this_om9 = false;
	bool this_om10 = false;
	bool this_om11 = false;
	bool this_om12 = false;
	//Yellow Matter
	bool this_ym1 = false;
	bool this_ym2 = false;
	bool this_ym3 = false;
	bool this_ym4 = false;
	bool this_ym5 = false;
	bool this_ym6 = false;
	bool this_ym7 = false;
	bool this_ym8 = false;
	bool this_ym9 = false;
	bool this_ym10 = false;
	bool this_ym11 = false;
	bool this_ym12 = false;
	//Blue Matter
	bool this_bm1 = false;
	bool this_bm2 = false;
	bool this_bm3 = false;
	bool this_bm4 = false;
	bool this_bm5 = false;
	bool this_bm6 = false;
	bool this_bm7 = false;
	bool this_bm8 = false;
	bool this_bm9 = false;
	bool this_bm10 = false;
	bool this_bm11 = false;
	bool this_bm12 = false;
	//Losowa liczba rud
	//Red Matter
	int losRM = (std::rand() % 12) + 1;
	if(losRM >= 1){
		this_rm1 = true;
		rm1 = true;
	}
	if(losRM >= 2){
		this_rm2 = true;
		rm2 = true;
	}
	if(losRM >= 3){
		this_rm3 = true;
		rm3 = true;
	}
	if(losRM >= 4){
		this_rm4 = true;
		rm4 = true;
	}
	if(losRM >= 5){
		this_rm5 = true;
		rm5 = true;
	}
	if(losRM >= 6){
		this_rm6 = true;
		rm6 = true;
	}
	if(losRM >= 7){
		this_rm7 = true;
		rm7 = true;
	}
	if(losRM >= 8){
		this_rm8 = true;
		rm8 = true;
	}
	if(losRM >= 9){
		this_rm9 = true;
		rm9 = true;
	}
	if(losRM >= 10){
		this_rm10 = true;
		rm10 = true;
	}
	if(losRM >= 11){
		this_rm11 = true;
		rm11 = true;
	}
	if(losRM >= 12){
		this_rm12 = true;
		rm12 = true;
	}
	//Orange Matter
	int losOM = (std::rand() % 12) + 1;
	if(losOM >= 1){
		this_om1 = true;
		om1 = true;
	}
	if(losOM >= 2){
		this_om2 = true;
		om2 = true;
	}
	if(losOM >= 3){
		this_om3 = true;
		om3 = true;
	}
	if(losOM >= 4){
		this_om4 = true;
		om4 = true;
	}
	if(losOM >= 5){
		this_om5 = true;
		om5 = true;
	}
	if(losOM >= 6){
		this_om6 = true;
		om6 = true;
	}
	if(losOM >= 7){
		this_om7 = true;
		om7 = true;
	}
	if(losOM >= 8){
		this_om8 = true;
		om8 = true;
	}
	if(losOM >= 9){
		this_om9 = true;
		om9 = true;
	}
	if(losOM >= 10){
		this_om10 = true;
		om10 = true;
	}
	if(losOM >= 11){
		this_om11 = true;
		om11 = true;
	}
	if(losOM >= 12){
		this_om12 = true;
		om12 = true;
	}
	//Yellow Matter
	int losYM = (std::rand() % 12) + 1;
	if(losYM >= 1){
		this_ym1 = true;
	}
	if(losYM >= 2){
		this_ym2 = true;
	}
	if(losYM >= 3){
		this_ym3 = true;
	}
	if(losYM >= 4){
		this_ym4 = true;
	}
	if(losYM >= 5){
		this_ym5 = true;
	}
	if(losYM >= 6){
		this_ym6 = true;
	}
	if(losYM >= 7){
		this_ym7 = true;
	}
	if(losYM >= 8){
		this_ym8 = true;
	}
	if(losYM >= 9){
		this_ym9 = true;
	}
	if(losYM >= 10){
		this_ym10 = true;
	}
	if(losYM >= 11){
		this_ym11 = true;
	}
	if(losYM >= 12){
		this_ym12 = true;
	}
	//Blue Matter
	int losBM = (std::rand() % 12) + 1;
	if(losBM >= 1){
		this_bm1 = true;
		bm1 = true;
	}
	if(losBM >= 2){
		this_bm2 = true;
		bm2 = true;
	}
	if(losBM >= 3){
		this_bm3 = true;
		bm3 = true;
	}
	if(losBM >= 4){
		this_bm4 = true;
		bm4 = true;
	}
	if(losBM >= 5){
		this_bm5 = true;
		bm5 = true;
	}
	if(losBM >= 6){
		this_bm6 = true;
		bm6 = true;
	}
	if(losBM >= 7){
		this_bm7 = true;
		bm7 = true;
	}
	if(losBM >= 8){
		this_bm8 = true;
		bm8 = true;
	}
	if(losBM >= 9){
		this_bm9 = true;
		bm9 = true;
	}
	if(losBM >= 10){
		this_bm10 = true;
		bm10 = true;
	}
	if(losBM >= 11){
		this_bm11 = true;
		bm11 = true;
	}
	if(losBM >= 12){
		this_bm12 = true;
		bm12 = true;
	}
		//Pêtla gry
		while(!key[KEY_ESC]){
			clear_to_color( bufor, makecol( 150, 150, 150 ) );
			myszka();

			//Rudy
			//Red Matter
			if(rm1){
				masked_blit( red_matter, bufor, 0, 0, rm1_x, rm1_y, red_matter->w, red_matter->h );
			}
			if(rm2){
				masked_blit( red_matter, bufor, 0, 0, rm2_x, rm2_y, red_matter->w, red_matter->h );
			}
			if(rm3){
				masked_blit( red_matter, bufor, 0, 0, rm3_x, rm3_y, red_matter->w, red_matter->h );
			}
			if(rm4){
				masked_blit( red_matter, bufor, 0, 0, rm4_x, rm4_y, red_matter->w, red_matter->h );
			}
			if(rm5){
				masked_blit( red_matter, bufor, 0, 0, rm5_x, rm5_y, red_matter->w, red_matter->h );
			}
			if(rm6){
				masked_blit( red_matter, bufor, 0, 0, rm6_x, rm6_y, red_matter->w, red_matter->h );
			}
			if(rm7){
				masked_blit( red_matter, bufor, 0, 0, rm7_x, rm7_y, red_matter->w, red_matter->h );
			}
			if(rm8){
				masked_blit( red_matter, bufor, 0, 0, rm8_x, rm8_y, red_matter->w, red_matter->h );
			}
			if(rm9){
				masked_blit( red_matter, bufor, 0, 0, rm9_x, rm9_y, red_matter->w, red_matter->h );
			}
			if(rm10){
				masked_blit( red_matter, bufor, 0, 0, rm10_x, rm10_y, red_matter->w, red_matter->h );
			}
			if(rm11){
				masked_blit( red_matter, bufor, 0, 0, rm11_x, rm11_y, red_matter->w, red_matter->h );
			}
			if(rm12){
				masked_blit( red_matter, bufor, 0, 0, rm12_x, rm12_y, red_matter->w, red_matter->h );
			}
			//Orange Matter
			if(om1){
				masked_blit( orange_matter, bufor, 0, 0, om1_x, om1_y, orange_matter->w, orange_matter->h );
			}
			if(om1){
				masked_blit( orange_matter, bufor, 0, 0, om1_x, om1_y, orange_matter->w, orange_matter->h );
			}
			if(om2){
				masked_blit( orange_matter, bufor, 0, 0, om2_x, om2_y, orange_matter->w, orange_matter->h );
			}
			if(om3){
				masked_blit( orange_matter, bufor, 0, 0, om3_x, om3_y, orange_matter->w, orange_matter->h );
			}
			if(om4){
				masked_blit( orange_matter, bufor, 0, 0, om4_x, om4_y, orange_matter->w, orange_matter->h );
			}
			if(om5){
				masked_blit( orange_matter, bufor, 0, 0, om5_x, om5_y, orange_matter->w, orange_matter->h );
			}
			if(om6){
				masked_blit( orange_matter, bufor, 0, 0, om6_x, om6_y, orange_matter->w, orange_matter->h );
			}
			if(om7){
				masked_blit( orange_matter, bufor, 0, 0, om7_x, om7_y, orange_matter->w, orange_matter->h );
			}
			if(om8){
				masked_blit( orange_matter, bufor, 0, 0, om8_x, om8_y, orange_matter->w, orange_matter->h );
			}
			if(om9){
				masked_blit( orange_matter, bufor, 0, 0, om9_x, om9_y, orange_matter->w, orange_matter->h );
			}
			if(om10){
				masked_blit( orange_matter, bufor, 0, 0, om10_x, om10_y, orange_matter->w, orange_matter->h );
			}
			if(om11){
				masked_blit( orange_matter, bufor, 0, 0, om11_x, om11_y, orange_matter->w, orange_matter->h );
			}
			if(om12){
				masked_blit( orange_matter, bufor, 0, 0, om12_x, om12_y, orange_matter->w, orange_matter->h );
			}
			//Yellow Matter
			if(losYM >= 1){
				if(ym1){
					masked_blit( yellow_matter, bufor, 0, 0, ym1_x, ym1_y, yellow_matter->w, yellow_matter->h );
				}
			}
			if(losYM >= 2){
				if(ym2){
					masked_blit( yellow_matter, bufor, 0, 0, ym2_x, ym2_y, yellow_matter->w, yellow_matter->h );
				}
			}
			if(losYM >= 3){
				if(ym3){
					masked_blit( yellow_matter, bufor, 0, 0, ym3_x, ym3_y, yellow_matter->w, yellow_matter->h );
				}
			}
			if(losYM >= 4){
				if(ym4){
					masked_blit( yellow_matter, bufor, 0, 0, ym4_x, ym4_y, yellow_matter->w, yellow_matter->h );
				}
			}
			if(losYM >= 5){
				if(ym5){
					masked_blit( yellow_matter, bufor, 0, 0, ym5_x, ym5_y, yellow_matter->w, yellow_matter->h );
				}
			}
			if(losYM >= 6){
				if(ym6){
					masked_blit( yellow_matter, bufor, 0, 0, ym6_x, ym6_y, yellow_matter->w, yellow_matter->h );
				}
			}
			if(losYM >= 7){
				if(ym7){
					masked_blit( yellow_matter, bufor, 0, 0, ym7_x, ym7_y, yellow_matter->w, yellow_matter->h );
				}
			}
			if(losYM >= 8){
				if(ym8){
					masked_blit( yellow_matter, bufor, 0, 0, ym8_x, ym8_y, yellow_matter->w, yellow_matter->h );
				}
			}
			if(losYM >= 9){
				if(ym9){
					masked_blit( yellow_matter, bufor, 0, 0, ym9_x, ym9_y, yellow_matter->w, yellow_matter->h );
				}
			}
			if(losYM >= 10){
				if(ym10){
					masked_blit( yellow_matter, bufor, 0, 0, ym10_x, ym10_y, yellow_matter->w, yellow_matter->h );
				}
			}
			if(losYM >= 11){
				if(ym11){
					masked_blit( yellow_matter, bufor, 0, 0, ym11_x, ym11_y, yellow_matter->w, yellow_matter->h );
				}
			}
			if(losYM >= 12){
				if(ym12){
					masked_blit( yellow_matter, bufor, 0, 0, ym12_x, ym12_y, yellow_matter->w, yellow_matter->h );
				}
			}
			//Blue Matter
			if(bm1){
				masked_blit( blue_matter, bufor, 0, 0, bm1_x, bm1_y, blue_matter->w, blue_matter->h );
			}
			if(bm2){
				masked_blit( blue_matter, bufor, 0, 0, bm2_x, bm2_y, blue_matter->w, blue_matter->h );
			}
			if(bm3){
				masked_blit( blue_matter, bufor, 0, 0, bm3_x, bm3_y, blue_matter->w, blue_matter->h );
			}
			if(bm4){
				masked_blit( blue_matter, bufor, 0, 0, bm4_x, bm4_y, blue_matter->w, blue_matter->h );
			}
			if(bm5){
				masked_blit( blue_matter, bufor, 0, 0, bm5_x, bm5_y, blue_matter->w, blue_matter->h );
			}
			if(bm6){
				masked_blit( blue_matter, bufor, 0, 0, bm6_x, bm6_y, blue_matter->w, blue_matter->h );
			}
			if(bm7){
				masked_blit( blue_matter, bufor, 0, 0, bm7_x, bm7_y, blue_matter->w, blue_matter->h );
			}
			if(bm8){
				masked_blit( blue_matter, bufor, 0, 0, bm8_x, bm8_y, blue_matter->w, blue_matter->h );
			}
			if(bm9){
				masked_blit( blue_matter, bufor, 0, 0, bm9_x, bm9_y, blue_matter->w, blue_matter->h );
			}
			if(bm10){
				masked_blit( blue_matter, bufor, 0, 0, bm10_x, bm10_y, blue_matter->w, blue_matter->h );
			}
			if(bm11){
				masked_blit( blue_matter, bufor, 0, 0, bm11_x, bm11_y, blue_matter->w, blue_matter->h );
			}
			if(bm12){
				masked_blit( blue_matter, bufor, 0, 0, bm12_x, bm12_y, blue_matter->w, blue_matter->h );
			}
			//Pod³o¿e
			masked_blit( podloze1, bufor, 0, 0, 0, 433, podloze1->w, podloze1->h );
			masked_blit( podloze1, bufor, 0, 0, 200, 433, podloze2->w, podloze2->h );
			masked_blit( podloze1, bufor, 0, 0, 400, 433, podloze3->w, podloze3->h );
			masked_blit( podloze1, bufor, 0, 0, 600, 433, podloze4->w, podloze4->h );
			//GUI
			textprintf_ex( bufor, font, 450, 20, makecol( 255, 255, 255 ), - 1, "Craft Points: %d", money);
			textprintf_ex( bufor, font, 20, 60, makecol( 255, 255, 255 ), - 1, "Exit the mine: ESC");
			textprintf_ex( bufor, font, 220, 20, makecol( 255, 255, 255 ), - 1, "EQ ON: E");
			textprintf_ex( bufor, font, 220, 30, makecol( 255, 255, 255 ), - 1, "EQ OFF: F");
			textprintf_ex( bufor, font, 220, 40, makecol( 255, 255, 255 ), - 1, "The game will be automatically saved.");
			textprintf_ex( bufor, font, 10, 460, makecol( 255, 255, 255 ), - 1, "The Construgert v.1.2.3 by Brunon Blok");
			textprintf_ex( bufor, font, 480, 460, makecol( 255, 255, 255 ), - 1, "Author of Music: M");
			if(kilof < 6){
				textprintf_ex( bufor, font, 220, 60, makecol( 255, 255, 255 ), - 1, "Attack: 0"); 
			}
			if(kilof == 6){
				textprintf_ex( bufor, font, 220, 60, makecol( 255, 255, 255 ), - 1, "Attack: 20"); 
			}
			if(kilof == 7){
				textprintf_ex( bufor, font, 220, 60, makecol( 255, 255, 255 ), - 1, "Attack: 25"); 
			}
			if(kilof == 8){
				textprintf_ex( bufor, font, 220, 60, makecol( 255, 255, 255 ), - 1, "Attack: 30"); 
			}
			if(kilof == 9){
				textprintf_ex( bufor, font, 220, 60, makecol( 255, 255, 255 ), - 1, "Attack: 35"); 
			}
			if(kilof == 10){
				textprintf_ex( bufor, font, 220, 60, makecol( 255, 255, 255 ), - 1, "Attack: 40"); 
			}
			//Mine Creature
			if(MC1){
				//Rysowanie
				masked_blit( MineCreature, bufor, 0, 0, mc1_x, 340, MineCreature->w, MineCreature->h );
				//Mechanika
				if(kierunekMC1){
					mc1_x++;
				}
				if(kierunekMC1 == false){
					mc1_x--;
				}
				if(mc1_x >= 574){
					kierunekMC1 = false;
				}
				if(mc1_x <= -37){
					kierunekMC1 = true;
				}
				//Atak Potwora
				if(Gracz_x <= mc1_x + 50 && Gracz_x >= mc1_x - 50){
					money = 0;
					kilof = 0;
					destroy_bitmap(gracz);
					destroy_bitmap(podloze1);
					destroy_bitmap(podloze2);
					destroy_bitmap(podloze3);
					destroy_bitmap(podloze4);
					destroy_bitmap(bufor);
					return 0;
				}
				//Atak Gracza
				if(mb == 0){
					klikniecie = false;
				}
				if(klikniecie == false){
					if(kilof == 6){
						if(mx > mc1_x && mx < mc1_x + 200 && my >= 340 && my < 340 + 200 && mb == 1){
							zdrowieMC1 -= 20;
							klikniecie = true;
						}
					}
					if(kilof == 7){
						if(mx > mc1_x && mx < mc1_x + 200 && my >= 340 && my < 340 + 200 && mb == 1){
							zdrowieMC1 -= 25;
							klikniecie = true;
						}
					}
					if(kilof == 8){
						if(mx > mc1_x && mx < mc1_x + 200 && my >= 340 && my < 340 + 200 && mb == 1){
							zdrowieMC1 -= 30;
							klikniecie = true;
						}
					}
					if(kilof == 9){
						if(mx > mc1_x && mx < mc1_x + 200 && my >= 340 && my < 340 + 200 && mb == 1){
							zdrowieMC1 -= 35;
							klikniecie = true;
						}
					}
					if(kilof == 10){
						if(mx > mc1_x && mx < mc1_x + 200 && my >= 340 && my < 340 + 200 && mb == 1){
							zdrowieMC1 -= 40;
							klikniecie = true;
						}
					}
				}
			}
			if(zdrowieMC1 <= 0){
				MC1 = false;
			}
			//Gracz
			masked_blit( gracz, bufor, 0, 0, Gracz_x, Gracz_y, gracz->w, gracz->h );
			//Poruszanie siê
			if(key [ KEY_LEFT ]){
				Gracz_x--;
			}
			if(key [ KEY_RIGHT ]){
				Gracz_x++;
			}
			rest(10);

			//Przechodznie do kolejnych sektorów
			if(Gracz_x < -47){
				Gracz_x = 544;
				goto label;
			}
			if(Gracz_x > 544){
				Gracz_x = -47;
				goto label;
			}

			//"Stats" (F3)
			if(key[KEY_F3]){
				textprintf_ex( bufor, font, 20, 20, makecol( 255, 255, 255 ), - 1, "X: %d", Gracz_x);
				textprintf_ex( bufor, font, 20, 40, makecol( 255, 255, 255 ), - 1, "Y: %d", Gracz_y);
			}
			//Kopanie rud
			//Red Matter
			if(kilof >= 6){
				if(this_rm1){
					if(mx > rm1_pos_1 && mx < rm1_pos_2 && my > rm1_pos_1_y && my < rm1_pos_2_y && mb == 1){
						money += 6000;
						rm1 = false;
						this_rm1 = false;
					}
				}
				if(this_rm2){
					if(mx > rm2_pos_1 && mx < rm2_pos_2 && my > rm2_pos_1_y && my < rm2_pos_2_y && mb == 1){
						money += 6000;
						rm2 = false;
						this_rm2 = false;
					}
				}
				if(this_rm3){
					if(mx > rm3_pos_1 && mx < rm3_pos_2 && my > rm3_pos_1_y && my < rm3_pos_2_y && mb == 1){
						money += 6000;
						rm3 = false;
						this_rm3 = false;
					}
				}
				if(this_rm4){
					if(mx > rm4_pos_1 && mx < rm4_pos_2 && my > rm4_pos_1_y && my < rm4_pos_2_y && mb == 1){
						money += 6000;
						rm4 = false;
						this_rm4 = false;
					}
				}
				if(this_rm5){
					if(mx > rm5_pos_1 && mx < rm5_pos_2 && my > rm5_pos_1_y && my < rm5_pos_2_y && mb == 1){
						money += 6000;
						rm5 = false;
						this_rm5 = false;
					}
				}
				if(this_rm6){
					if(mx > rm6_pos_1 && mx < rm6_pos_2 && my > rm6_pos_1_y && my < rm6_pos_2_y && mb == 1){
						money += 6000;
						rm6 = false;
						this_rm6 = false;
					}
				}
				if(this_rm7){
					if(mx > rm7_pos_1 && mx < rm7_pos_2 && my > rm7_pos_1_y && my < rm7_pos_2_y && mb == 1){
						money += 6000;
						rm7 = false;
						this_rm7 = false;
					}
				}
				if(this_rm8){
					if(mx > rm8_pos_1 && mx < rm8_pos_2 && my > rm8_pos_1_y && my < rm8_pos_2_y && mb == 1){
						money += 6000;
						rm8 = false;
						this_rm8 = false;
					}
				}
				if(this_rm9){
					if(mx > rm9_pos_1 && mx < rm9_pos_2 && my > rm9_pos_1_y && my < rm9_pos_2_y && mb == 1){
						money += 6000;
						rm9 = false;
						this_rm9 = false;
					}
				}
				if(this_rm10){
					if(mx > rm10_pos_1 && mx < rm10_pos_2 && my > rm10_pos_1_y && my < rm10_pos_2_y && mb == 1){
						money += 6000;
						rm10 = false;
						this_rm10 = false;
					}
				}
				if(this_rm11){
					if(mx > rm11_pos_1 && mx < rm11_pos_2 && my > rm11_pos_1_y && my < rm11_pos_2_y && mb == 1){
						money += 6000;
						rm11 = false;
						this_rm11 = false;
					}
				}
				if(this_rm12){
					if(mx > rm12_pos_1 && mx < rm12_pos_2 && my > rm12_pos_1_y && my < rm12_pos_2_y && mb == 1){
						money += 6000;
						rm12 = false;
						this_rm12 = false;
					}
				}
			}
			if(kilof >= 7){
				//Orange Matter
				if(this_om1){
					if(mx > om1_pos_1 && mx < om1_pos_2 && my > om1_pos_1_y && my < om1_pos_2_y && mb == 1){
						money += 8000;
						om1 = false;
						this_om1 = false;
					}
				}
				if(this_om2){
					if(mx > om2_pos_1 && mx < om2_pos_2 && my > om2_pos_1_y && my < om2_pos_2_y && mb == 1){
						money += 8000;
						om2 = false;
						this_om2 = false;
					}
				}
				if(this_om3){
					if(mx > om3_pos_1 && mx < om3_pos_2 && my > om3_pos_1_y && my < om3_pos_2_y && mb == 1){
						money += 8000;
						om3 = false;
						this_om3 = false;
					}
				}
				if(this_om4){
					if(mx > om4_pos_1 && mx < om4_pos_2 && my > om4_pos_1_y && my < om4_pos_2_y && mb == 1){
						money += 8000;
						om4 = false;
						this_om4 = false;
					}
				}
				if(this_om5){
					if(mx > om5_pos_1 && mx < om5_pos_2 && my > om5_pos_1_y && my < om5_pos_2_y && mb == 1){
						money += 8000;
						om5 = false;
						this_om5 = false;
					}
				}
				if(this_om6){
					if(mx > om6_pos_1 && mx < om6_pos_2 && my > om6_pos_1_y && my < om6_pos_2_y && mb == 1){
						money += 8000;
						om6 = false;
						this_om6 = false;
					}
				}
				if(this_om7){
					if(mx > om7_pos_1 && mx < om7_pos_2 && my > om7_pos_1_y && my < om7_pos_2_y && mb == 1){
						money += 8000;
						om7 = false;
						this_om7 = false;
					}
				}
				if(this_om8){
					if(mx > om8_pos_1 && mx < om8_pos_2 && my > om8_pos_1_y && my < om8_pos_2_y && mb == 1){
						money += 8000;
						om8 = false;
						this_om8 = false;
					}
				}
				if(this_om9){
					if(mx > om9_pos_1 && mx < om9_pos_2 && my > om9_pos_1_y && my < om9_pos_2_y && mb == 1){
						money += 8000;
						om9 = false;
						this_om9 = false;
					}
				}
				if(this_om10){
					if(mx > om10_pos_1 && mx < om10_pos_2 && my > om10_pos_1_y && my < om10_pos_2_y && mb == 1){
						money += 8000;
						om10 = false;
						this_om10 = false;
					}
				}
				if(this_om11){
					if(mx > om11_pos_1 && mx < om11_pos_2 && my > om11_pos_1_y && my < om11_pos_2_y && mb == 1){
						money += 8000;
						om11 = false;
						this_om11 = false;
					}
				}
				if(this_om12){
					if(mx > om12_pos_1 && mx < om12_pos_2 && my > om12_pos_1_y && my < om12_pos_2_y && mb == 1){
						money += 8000;
						om12 = false;
						this_om12 = false;
					}
				}
			}
			if(kilof >= 8){
				//Yellow Matter 
				if(this_ym1){
					if(mx > ym1_pos_1 && mx < ym1_pos_2 && my > ym1_pos_1_y && my < ym1_pos_2_y && mb == 1){
						money += 10000;
						ym1 = false;
						this_ym1 = false;
					}
				}
				if(this_ym2){
					if(mx > ym2_pos_1 && mx < ym2_pos_2 && my > ym2_pos_1_y && my < ym2_pos_2_y && mb == 1){
						money += 10000;
						ym2 = false;
						this_ym2 = false;
					}
				}
				if(this_ym3){
					if(mx > ym3_pos_1 && mx < ym3_pos_2 && my > ym3_pos_1_y && my < ym3_pos_2_y && mb == 1){
						money += 10000;
						ym3 = false;
						this_ym3 = false;
					}
				}
				if(this_ym4){
					if(mx > ym4_pos_1 && mx < ym4_pos_2 && my > ym4_pos_1_y && my < ym4_pos_2_y && mb == 1){
						money += 10000;
						ym4 = false;
						this_ym4 = false;
					}
				}
				if(this_ym5){
					if(mx > ym5_pos_1 && mx < ym5_pos_2 && my > ym5_pos_1_y && my < ym5_pos_2_y && mb == 1){
						money += 10000;
						ym5 = false;
						this_ym5 = false;
					}
				}
				if(this_ym6){
					if(mx > ym6_pos_1 && mx < ym6_pos_2 && my > ym6_pos_1_y && my < ym6_pos_2_y && mb == 1){
						money += 10000;
						ym6 = false;
						this_ym6 = false;
					}
				}
				if(this_ym7){
					if(mx > ym7_pos_1 && mx < ym7_pos_2 && my > ym7_pos_1_y && my < ym7_pos_2_y && mb == 1){
						money += 10000;
						ym7 = false;
						this_ym7 = false;
					}
				}
				if(this_ym8){
					if(mx > ym8_pos_1 && mx < ym8_pos_2 && my > ym8_pos_1_y && my < ym8_pos_2_y && mb == 1){
						money += 10000;
						ym8 = false;
						this_ym8 = false;
					}
				}
				if(this_ym9){
					if(mx > ym9_pos_1 && mx < ym9_pos_2 && my > ym9_pos_1_y && my < ym9_pos_2_y && mb == 1){
						money += 10000;
						ym9 = false;
						this_ym9 = false;
					}
				}
				if(this_ym10){
					if(mx > ym10_pos_1 && mx < ym10_pos_2 && my > ym10_pos_1_y && my < ym10_pos_2_y && mb == 1){
						money += 10000;
						ym10 = false;
						this_ym10 = false;
					}
				}
				if(this_ym11){
					if(mx > ym11_pos_1 && mx < ym11_pos_2 && my > ym11_pos_1_y && my < ym11_pos_2_y && mb == 1){
						money += 10000;
						ym11 = false;
						this_ym11 = false;
					}
				}
				if(this_ym12){
					if(mx > ym12_pos_1 && mx < ym12_pos_2 && my > ym12_pos_1_y && my < ym12_pos_2_y && mb == 1){
						money += 10000;
						ym12 = false;
						this_ym12 = false;
					}
				}
			}
			//Blue Matter
			if(kilof >= 9){
				if(this_bm1){
					if(mx > bm1_pos_1 && mx < bm1_pos_2 && my > bm1_pos_1_y && my < bm1_pos_2_y && mb == 1){
						money += 12000;
						bm1 = false;
						this_bm1 = false;
					}
				}
				if(this_bm2){
					if(mx > bm2_pos_1 && mx < bm2_pos_2 && my > bm2_pos_1_y && my < bm2_pos_2_y && mb == 1){
						money += 12000;
						bm2 = false;
						this_bm2 = false;
					}
				}
				if(this_bm3){
					if(mx > bm3_pos_1 && mx < bm3_pos_2 && my > bm3_pos_1_y && my < bm3_pos_2_y && mb == 1){
						money += 12000;
						bm3 = false;
						this_bm3 = false;
					}
				}
				if(this_bm4){
					if(mx > bm4_pos_1 && mx < bm4_pos_2 && my > bm4_pos_1_y && my < bm4_pos_2_y && mb == 1){
						money += 12000;
						bm4 = false;
						this_bm4 = false;
					}
				}
				if(this_bm5){
					if(mx > bm5_pos_1 && mx < bm5_pos_2 && my > bm5_pos_1_y && my < bm5_pos_2_y && mb == 1){
						money += 12000;
						bm5 = false;
						this_bm5 = false;
					}
				}
				if(this_bm6){
					if(mx > bm6_pos_1 && mx < bm6_pos_2 && my > bm6_pos_1_y && my < bm6_pos_2_y && mb == 1){
						money += 12000;
						bm6 = false;
						this_bm6 = false;
					}
				}
				if(this_bm7){
					if(mx > bm7_pos_1 && mx < bm7_pos_2 && my > bm7_pos_1_y && my < bm7_pos_2_y && mb == 1){
						money += 12000;
						bm7 = false;
						this_bm7 = false;
					}
				}
				if(this_bm8){
					if(mx > bm8_pos_1 && mx < bm8_pos_2 && my > bm8_pos_1_y && my < bm8_pos_2_y && mb == 1){
						money += 12000;
						bm8 = false;
						this_bm8 = false;
					}
				}
				if(this_bm9){
					if(mx > bm9_pos_1 && mx < bm9_pos_2 && my > bm9_pos_1_y && my < bm9_pos_2_y && mb == 1){
						money += 12000;
						bm9 = false;
						this_bm9 = false;
					}
				}
				if(this_bm10){
					if(mx > bm10_pos_1 && mx < bm10_pos_2 && my > bm10_pos_1_y && my < bm10_pos_2_y && mb == 1){
						money += 12000;
						bm10 = false;
						this_bm10 = false;
					}
				}
				if(this_bm11){
					if(mx > bm11_pos_1 && mx < bm11_pos_2 && my > bm11_pos_1_y && my < bm11_pos_2_y && mb == 1){
						money += 12000;
						bm11 = false;
						this_bm11 = false;
					}
				}
				if(this_bm12){
					if(mx > bm12_pos_1 && mx < bm12_pos_2 && my > bm12_pos_1_y && my < bm12_pos_2_y && mb == 1){
						money += 12000;
						bm12 = false;
						this_bm12 = false;
					}
				}
			}
			//Otwieranie ekwipunku
			if(key [KEY_E]){
				ekwipunek();
				if(kilof == 0){
					gracz = load_bmp("Grafika/Gracz/gracz.bmp", default_palette);
				}
				if(kilof == 1){
					gracz = load_bmp("Grafika/Gracz/gracz_z_drewnianym_kilofem.bmp", default_palette);
				}
				if(kilof == 2){
					gracz = load_bmp("Grafika/Gracz/gracz_z_kamiennym_kilofem.bmp", default_palette);
				}
				if(kilof == 3){
					gracz = load_bmp("Grafika/Gracz/gracz_z_zelaznym_kilofem.bmp", default_palette);
				}
				if(kilof == 4){
					gracz = load_bmp("Grafika/Gracz/gracz_ze_zlotym_kilofem.bmp", default_palette);
				}
				if(kilof == 5){
					gracz = load_bmp("Grafika/Gracz/gracz_z_diamentowym_kilofem.bmp", default_palette);
				}
				if(kilof == 6){
					gracz = load_bmp("Grafika/Gracz/gracz_z_tasigaw_kilofem.bmp", default_palette);
				}
				if(kilof == 7){
					gracz = load_bmp("Grafika/Gracz/gracz_z_redmatter_kilofem.bmp", default_palette);
				}
				if(kilof == 8){
					gracz = load_bmp("Grafika/Gracz/gracz_z_orangematter_kilofem.bmp", default_palette);
				}
				if(kilof == 9){
					gracz = load_bmp("Grafika/Gracz/gracz_z_yellowmatter_kilofem.bmp", default_palette);
				}
				if(kilof == 10){
					gracz = load_bmp("Grafika/Gracz/gracz_z_bluematter_kilofem.bmp", default_palette);
				}
			}
			//Zapisywanie Gry
			zapisGry();

			//Stwierdzenie autorstwa muzyki
			if(key[KEY_M]){
				textprintf_ex( bufor, font, 180, 150, makecol( 255, 255, 255 ), - 1, "Music: 'Project System 12 - Breath of Hope' (CC)");
			}
			//Stwierdzenie autorstwa muzyki
			if(key[KEY_M]){
				textprintf_ex( bufor, font, 180, 150, makecol( 255, 255, 255 ), - 1, "Music: 'Project System 12 - Breath of Hope' (CC)");
			}
			//Music ON/OFF
			if(!key[KEY_F3]){
				textprintf_ex( bufor, font, 20, 20, makecol( 255, 255, 255 ), - 1, "Music ON/OFF: N");
			}
			if(music == true){
				if(key[KEY_N]){
					stop_sample( muzyka1 );
					rest(300);
					music = false;
				}
			}
			if(music == false){
				if(key[KEY_N]){
					play_sample( muzyka1, 255, 127, 1000, 1 );
					rest(300);
					music = true;
				}
			}

			blit( bufor, screen, 0, 0, 0, 0, 640, 480 );
	}
	destroy_bitmap(gracz);
	destroy_bitmap(podloze1);
	destroy_bitmap(podloze2);
	destroy_bitmap(podloze3);
	destroy_bitmap(podloze4);
	destroy_bitmap(bufor);
	return 0;
}

int kopalnia_start(){
	//Muzyka
	install_sound( DIGI_AUTODETECT, MIDI_AUTODETECT, "" );
	set_volume( 255, 255 );
	SAMPLE * muzyka1 = NULL;
	muzyka1 = load_sample( "Muzyka/Project_System_12_-_Breath_of_Hope.wav" );
	play_sample( muzyka1, 255, 127, 1000, 1 );
	bool sm = true;
	label:
	//Funkcje wstêpne
	clear_to_color( screen, makecol( 195, 195, 195 ) );
	srand( time( NULL ) );
	install_mouse();
    show_mouse( screen );
	unscare_mouse();
	//Pobieranie grafiki
	BITMAP * gracz = NULL;
	if(kilof == 0){
		gracz = load_bmp("Grafika/Gracz/gracz.bmp", default_palette);
	}
	if(kilof == 1){
		gracz = load_bmp("Grafika/Gracz/gracz_z_drewnianym_kilofem.bmp", default_palette);
	}
	if(kilof == 2){
		gracz = load_bmp("Grafika/Gracz/gracz_z_kamiennym_kilofem.bmp", default_palette);
	}
	if(kilof == 3){
		gracz = load_bmp("Grafika/Gracz/gracz_z_zelaznym_kilofem.bmp", default_palette);
	}
	if(kilof == 4){
		gracz = load_bmp("Grafika/Gracz/gracz_ze_zlotym_kilofem.bmp", default_palette);
	}
	if(kilof == 5){
		gracz = load_bmp("Grafika/Gracz/gracz_z_diamentowym_kilofem.bmp", default_palette);
	}
	if(kilof == 6){
		gracz = load_bmp("Grafika/Gracz/gracz_z_tasigaw_kilofem.bmp", default_palette);
	}
	if(kilof == 7){
		gracz = load_bmp("Grafika/Gracz/gracz_z_redmatter_kilofem.bmp", default_palette);
	}
	if(kilof == 8){
		gracz = load_bmp("Grafika/Gracz/gracz_z_orangematter_kilofem.bmp", default_palette);
	}
	if(kilof == 9){
		gracz = load_bmp("Grafika/Gracz/gracz_z_yellowmatter_kilofem.bmp", default_palette);
	}
	if(kilof == 10){
		gracz = load_bmp("Grafika/Gracz/gracz_z_bluematter_kilofem.bmp", default_palette);
	}
	BITMAP * podloze1 = NULL;
	podloze1 = load_bmp("Grafika/podloze_kopalnia1.bmp", default_palette);
	BITMAP * podloze2 = NULL;
	podloze2 = load_bmp("Grafika/podloze_kopalnia2.bmp", default_palette);
	BITMAP * podloze3 = NULL;
	podloze3 = load_bmp("Grafika/podloze_kopalnia3.bmp", default_palette);
	BITMAP * podloze4 = NULL;
	podloze4 = load_bmp("Grafika/podloze_kopalnia4.bmp", default_palette);
	BITMAP * kopalnia2 = NULL;
	kopalnia2 = load_bmp("Grafika/kopalnia2.bmp", default_palette);
	BITMAP * kamien  = NULL;
	kamien = load_bmp("Grafika/kamien.bmp", default_palette);
	BITMAP * zelazo  = NULL;
	zelazo = load_bmp("Grafika/zelazo.bmp", default_palette);
	BITMAP * zloto = NULL;
	zloto = load_bmp("Grafika/zloto.bmp", default_palette);
	BITMAP * diament = NULL;
	diament = load_bmp("Grafika/diament.bmp", default_palette);
	BITMAP * wagisat = NULL;
	wagisat = load_bmp("Grafika/wagisat.bmp", default_palette);
	BITMAP * bufor = NULL;
	bufor = create_bitmap( 640, 480 );
	//Generowanie losowych koordynatów obiektów kopalni (X)
	//Ska³a
	int o1_x = (std::rand() % 200) + 0;
	int o2_x = (std::rand() % 200) + 200;
	int o3_x = (std::rand() % 45) + 400;
	int o4_x = (std::rand() % 100) + 450;
	int o5_x = (std::rand() % 200) + 0;
	int o6_x = (std::rand() % 200) + 200;
	int o7_x = (std::rand() % 45) + 400;
	int o8_x = (std::rand() % 100) + 450;
	int o9_x = (std::rand() % 200) + 0;
	int o10_x = (std::rand() % 200) + 200;
	int o11_x = (std::rand() % 45) + 400;
	int o12_x = (std::rand() % 100) + 450;
	//Ska³a - nielosowe (Y)
	int o1_y = 353;
	int o2_y = 353;
	int o3_y = 353;
	int o4_y = 353;
	int o5_y = 353;
	int o6_y = 353;
	int o7_y = 393;
	int o8_y = 393;
	int o9_y = 393;
	int o10_y = 393;
	int o11_y = 393;
	int o12_y = 393;
	//¯elazo
	int z1_x = (std::rand() % 200) + 0;
	int z2_x = (std::rand() % 200) + 200;
	int z3_x = (std::rand() % 45) + 400;
	int z4_x = (std::rand() % 100) + 450;
	int z5_x = (std::rand() % 200) + 0;
	int z6_x = (std::rand() % 200) + 200;
	int z7_x = (std::rand() % 45) + 400;
	int z8_x = (std::rand() % 100) + 450;
	int z9_x = (std::rand() % 200) + 0;
	int z10_x = (std::rand() % 200) + 200;
	int z11_x = (std::rand() % 45) + 400;
	int z12_x = (std::rand() % 100) + 450;
	//¯elazo - nielosowe (Y)
	int z1_y = 313;
	int z2_y = 313;
	int z3_y = 313;
	int z4_y = 313;
	int z5_y = 313;
	int z6_y = 313;
	int z7_y = 273;
	int z8_y = 273;
	int z9_y = 273;
	int z10_y = 273;
	int z11_y = 273;
	int z12_y = 273;
	//Z³oto
	int c1_x = (std::rand() % 200) + 0;
	int c2_x = (std::rand() % 200) + 200;
	int c3_x = (std::rand() % 45) + 400;
	int c4_x = (std::rand() % 100) + 450;
	int c5_x = (std::rand() % 200) + 0;
	int c6_x = (std::rand() % 200) + 200;
	int c7_x = (std::rand() % 45) + 400;
	int c8_x = (std::rand() % 100) + 450;
	int c9_x = (std::rand() % 200) + 0;
	int c10_x = (std::rand() % 200) + 200;
	int c11_x = (std::rand() % 45) + 400;
	int c12_x = (std::rand() % 100) + 450;
	//Z³oto - nielosowe (Y)
	int zl1_y = 193;
	int zl2_y = 193;
	int zl3_y = 193;
	int zl4_y = 193;
	int zl5_y = 193;
	int zl6_y = 193;
	int zl7_y = 233;
	int zl8_y = 233;
	int zl9_y = 233;
	int zl10_y = 233;
	int zl11_y = 233;
	int zl12_y = 233;
	//Diament
	int d1_x = (std::rand() % 200) + 0;
	int d2_x = (std::rand() % 200) + 200;
	int d3_x = (std::rand() % 45) + 400;
	int d4_x = (std::rand() % 100) + 450;
	int d5_x = (std::rand() % 200) + 0;
	int d6_x = (std::rand() % 200) + 200;
	int d7_x = (std::rand() % 45) + 400;
	int d8_x = (std::rand() % 100) + 450;
	int d9_x = (std::rand() % 200) + 0;
	int d10_x = (std::rand() % 200) + 200;
	int d11_x = (std::rand() % 45) + 400;
	int d12_x = (std::rand() % 100) + 450;
	//Diament - nielosowe (Y)
	int d1_y = 113;
	int d2_y = 113;
	int d3_y = 113;
	int d4_y = 113;
	int d5_y = 113;
	int d6_y = 113;
	int d7_y = 153;
	int d8_y = 153;
	int d9_y = 153;
	int d10_y = 153;
	int d11_y = 153;
	int d12_y = 153;
	//Wasigad Ore
	int w1_x = (std::rand() % 200) + 0;
	int w2_x = (std::rand() % 200) + 200;
	int w3_x = (std::rand() % 45) + 400;
	int w4_x = (std::rand() % 100) + 450;
	int w5_x = (std::rand() % 200) + 0;
	int w6_x = (std::rand() % 200) + 200;
	int w7_x = (std::rand() % 45) + 400;
	int w8_x = (std::rand() % 100) + 450;
	int w9_x = (std::rand() % 200) + 0;
	int w10_x = (std::rand() % 200) + 200;
	int w11_x = (std::rand() % 45) + 400;
	int w12_x = (std::rand() % 100) + 450;
	//Wasigad Ore - nielosowe (Y)
	int w1_y = 33;
	int w2_y = 33;
	int w3_y = 33;
	int w4_y = 33;
	int w5_y = 33;
	int w6_y = 33;
	int w7_y = 73;
	int w8_y = 73;
	int w9_y = 73;
	int w10_y = 73;
	int w11_y = 73;
	int w12_y = 73;
	//Kopalnia
	int kop2 = 484;
	//Zmienne pozycji objektów
	//Ska³a
	//- (X)
	int o1_pos_1 = o1_x;
	int o2_pos_1 = o2_x;
	int o3_pos_1 = o3_x;
	int o4_pos_1 = o4_x;
	int o5_pos_1 = o5_x;
	int o6_pos_1 = o6_x;
	int o7_pos_1 = o7_x;
	int o8_pos_1 = o8_x;
	int o9_pos_1 = o9_x;
	int o10_pos_1 = o10_x;
	int o11_pos_1 = o11_x;
	int o12_pos_1 = o12_x;
	//+ (X)
	int o1_pos_2 = o1_x + 40;
	int o2_pos_2 = o2_x + 40;
	int o3_pos_2 = o3_x + 40;
	int o4_pos_2 = o4_x + 40;
	int o5_pos_2 = o5_x + 40;
	int o6_pos_2 = o6_x + 40;
	int o7_pos_2 = o7_x + 40;
	int o8_pos_2 = o8_x + 40;
	int o9_pos_2 = o9_x + 40;
	int o10_pos_2 = o10_x + 40;
	int o11_pos_2 = o11_x + 40;
	int o12_pos_2 = o12_x + 40;
	//- (Y)
	int o1_pos_1_y = o1_y;
	int o2_pos_1_y = o2_y;
	int o3_pos_1_y = o3_y;
	int o4_pos_1_y = o4_y;
	int o5_pos_1_y = o5_y;
	int o6_pos_1_y = o6_y;
	int o7_pos_1_y = o7_y;
	int o8_pos_1_y = o8_y;
	int o9_pos_1_y = o9_y;
	int o10_pos_1_y = o10_y;
	int o11_pos_1_y = o11_y;
	int o12_pos_1_y = o12_y;
	//+ (Y)
	int o1_pos_2_y = o1_y + 40;
	int o2_pos_2_y = o2_y + 40;
	int o3_pos_2_y = o3_y + 40;
	int o4_pos_2_y = o4_y + 40;
	int o5_pos_2_y = o5_y + 40;
	int o6_pos_2_y = o6_y + 40;
	int o7_pos_2_y = o7_y + 40;
	int o8_pos_2_y = o8_y + 40;
	int o9_pos_2_y = o9_y + 40;
	int o10_pos_2_y = o10_y + 40;
	int o11_pos_2_y = o11_y + 40;
	int o12_pos_2_y = o12_y + 40;
	//¯elazo
	//- (X)
	int ze1_pos_1 = z1_x;
	int ze2_pos_1 = z2_x;
	int ze3_pos_1 = z3_x;
	int ze4_pos_1 = z4_x;
	int ze5_pos_1 = z5_x;
	int ze6_pos_1 = z6_x;
	int ze7_pos_1 = z7_x;
	int ze8_pos_1 = z8_x;
	int ze9_pos_1 = z9_x;
	int ze10_pos_1 = z10_x;
	int ze11_pos_1 = z11_x;
	int ze12_pos_1 = z12_x;
	//+ (X)
	int ze1_pos_2 = z1_x + 40;
	int ze2_pos_2 = z2_x + 40;
	int ze3_pos_2 = z3_x + 40;
	int ze4_pos_2 = z4_x + 40;
	int ze5_pos_2 = z5_x + 40;
	int ze6_pos_2 = z6_x + 40;
	int ze7_pos_2 = z7_x + 40;
	int ze8_pos_2 = z8_x + 40;
	int ze9_pos_2 = z9_x + 40;
	int ze10_pos_2 = z10_x + 40;
	int ze11_pos_2 = z11_x + 40;
	int ze12_pos_2 = z12_x + 40;
	//- (Y)
	int z1_pos_1_y = z1_y;
	int z2_pos_1_y = z2_y;
	int z3_pos_1_y = z3_y;
	int z4_pos_1_y = z4_y;
	int z5_pos_1_y = z5_y;
	int z6_pos_1_y = z6_y;
	int z7_pos_1_y = z7_y;
	int z8_pos_1_y = z8_y;
	int z9_pos_1_y = z9_y;
	int z10_pos_1_y = z10_y;
	int z11_pos_1_y = z11_y;
	int z12_pos_1_y = z12_y;
	//+ (Y)
	int z1_pos_2_y = z1_y + 40;
	int z2_pos_2_y = z2_y + 40;
	int z3_pos_2_y = z3_y + 40;
	int z4_pos_2_y = z4_y + 40;
	int z5_pos_2_y = z5_y + 40;
	int z6_pos_2_y = z6_y + 40;
	int z7_pos_2_y = z7_y + 40;
	int z8_pos_2_y = z8_y + 40;
	int z9_pos_2_y = z9_y + 40;
	int z10_pos_2_y = z10_y + 40;
	int z11_pos_2_y = z11_y + 40;
	int z12_pos_2_y = z12_y + 40;
	//Z³oto
	//- (X)
	int zl1_pos_1 = c1_x;
	int zl2_pos_1 = c2_x;
	int zl3_pos_1 = c3_x;
	int zl4_pos_1 = c4_x;
	int zl5_pos_1 = c5_x;
	int zl6_pos_1 = c6_x;
	int zl7_pos_1 = c7_x;
	int zl8_pos_1 = c8_x;
	int zl9_pos_1 = c9_x;
	int zl10_pos_1 = c10_x;
	int zl11_pos_1 = c11_x;
	int zl12_pos_1 = c12_x;
	//+ (X)
	int zl1_pos_2 = c1_x + 40;
	int zl2_pos_2 = c2_x + 40;
	int zl3_pos_2 = c3_x + 40;
	int zl4_pos_2 = c4_x + 40;
	int zl5_pos_2 = c5_x + 40;
	int zl6_pos_2 = c6_x + 40;
	int zl7_pos_2 = c7_x + 40;
	int zl8_pos_2 = c8_x + 40;
	int zl9_pos_2 = c9_x + 40;
	int zl10_pos_2 = c10_x + 40;
	int zl11_pos_2 = c11_x + 40;
	int zl12_pos_2 = c12_x + 40;
	//- (Y)
	int zl1_pos_1_y = zl1_y;
	int zl2_pos_1_y = zl2_y;
	int zl3_pos_1_y = zl3_y;
	int zl4_pos_1_y = zl4_y;
	int zl5_pos_1_y = zl5_y;
	int zl6_pos_1_y = zl6_y;
	int zl7_pos_1_y = zl7_y;
	int zl8_pos_1_y = zl8_y;
	int zl9_pos_1_y = zl9_y;
	int zl10_pos_1_y = zl10_y;
	int zl11_pos_1_y = zl11_y;
	int zl12_pos_1_y = zl12_y;
	//+ (Y)
	int zl1_pos_2_y = zl1_y + 40;
	int zl2_pos_2_y = zl2_y + 40;
	int zl3_pos_2_y = zl3_y + 40;
	int zl4_pos_2_y = zl4_y + 40;
	int zl5_pos_2_y = zl5_y + 40;
	int zl6_pos_2_y = zl6_y + 40;
	int zl7_pos_2_y = zl7_y + 40;
	int zl8_pos_2_y = zl8_y + 40;
	int zl9_pos_2_y = zl9_y + 40;
	int zl10_pos_2_y = zl10_y + 40;
	int zl11_pos_2_y = zl11_y + 40;
	int zl12_pos_2_y = zl12_y + 40;
	//Diament
	//- (X)
	int d1_pos_1 = d1_x;
	int d2_pos_1 = d2_x;
	int d3_pos_1 = d3_x;
	int d4_pos_1 = d4_x;
	int d5_pos_1 = d5_x;
	int d6_pos_1 = d6_x;
	int d7_pos_1 = d7_x;
	int d8_pos_1 = d8_x;
	int d9_pos_1 = d9_x;
	int d10_pos_1 = d10_x;
	int d11_pos_1 = d11_x;
	int d12_pos_1 = d12_x;
	//+ (X)
	int d1_pos_2 = d1_x + 40;
	int d2_pos_2 = d2_x + 40;
	int d3_pos_2 = d3_x + 40;
	int d4_pos_2 = d4_x + 40;
	int d5_pos_2 = d5_x + 40;
	int d6_pos_2 = d6_x + 40;
	int d7_pos_2 = d7_x + 40;
	int d8_pos_2 = d8_x + 40;
	int d9_pos_2 = d9_x + 40;
	int d10_pos_2 = d10_x + 40;
	int d11_pos_2 = d11_x + 40;
	int d12_pos_2 = d12_x + 40;
	//- (Y)
	int d1_pos_1_y = d1_y;
	int d2_pos_1_y = d2_y;
	int d3_pos_1_y = d3_y;
	int d4_pos_1_y = d4_y;
	int d5_pos_1_y = d5_y;
	int d6_pos_1_y = d6_y;
	int d7_pos_1_y = d7_y;
	int d8_pos_1_y = d8_y;
	int d9_pos_1_y = d9_y;
	int d10_pos_1_y = d10_y;
	int d11_pos_1_y = d11_y;
	int d12_pos_1_y = d12_y;
	//+ (Y)
	int d1_pos_2_y = d1_y + 40;
	int d2_pos_2_y = d2_y + 40;
	int d3_pos_2_y = d3_y + 40;
	int d4_pos_2_y = d4_y + 40;
	int d5_pos_2_y = d5_y + 40;
	int d6_pos_2_y = d6_y + 40;
	int d7_pos_2_y = d7_y + 40;
	int d8_pos_2_y = d8_y + 40;
	int d9_pos_2_y = d9_y + 40;
	int d10_pos_2_y = d10_y + 40;
	int d11_pos_2_y = d11_y + 40;
	int d12_pos_2_y = d12_y + 40;
	//Tasigaw
	//- (X)
	int w1_pos_1 = w1_x;
	int w2_pos_1 = w2_x;
	int w3_pos_1 = w3_x;
	int w4_pos_1 = w4_x;
	int w5_pos_1 = w5_x;
	int w6_pos_1 = w6_x;
	int w7_pos_1 = w7_x;
	int w8_pos_1 = w8_x;
	int w9_pos_1 = w9_x;
	int w10_pos_1 = w10_x;
	int w11_pos_1 = w11_x;
	int w12_pos_1 = w12_x;
	//+ (X)
	int w1_pos_2 = w1_x + 40;
	int w2_pos_2 = w2_x + 40;
	int w3_pos_2 = w3_x + 40;
	int w4_pos_2 = w4_x + 40;
	int w5_pos_2 = w5_x + 40;
	int w6_pos_2 = w6_x + 40;
	int w7_pos_2 = w7_x + 40;
	int w8_pos_2 = w8_x + 40;
	int w9_pos_2 = w9_x + 40;
	int w10_pos_2 = w10_x + 40;
	int w11_pos_2 = w11_x + 40;
	int w12_pos_2 = w12_x + 40;
	//- (Y)
	int w1_pos_1_y = w1_y;
	int w2_pos_1_y = w2_y;
	int w3_pos_1_y = w3_y;
	int w4_pos_1_y = w4_y;
	int w5_pos_1_y = w5_y;
	int w6_pos_1_y = w6_y;
	int w7_pos_1_y = w7_y;
	int w8_pos_1_y = w8_y;
	int w9_pos_1_y = w9_y;
	int w10_pos_1_y = w10_y;
	int w11_pos_1_y = w11_y;
	int w12_pos_1_y = w12_y;
	//+ (Y)
	int w1_pos_2_y = w1_y + 40;
	int w2_pos_2_y = w2_y + 40;
	int w3_pos_2_y = w3_y + 40;
	int w4_pos_2_y = w4_y + 40;
	int w5_pos_2_y = w5_y + 40;
	int w6_pos_2_y = w6_y + 40;
	int w7_pos_2_y = w7_y + 40;
	int w8_pos_2_y = w8_y + 40;
	int w9_pos_2_y = w9_y + 40;
	int w10_pos_2_y = w10_y + 40;
	int w11_pos_2_y = w11_y + 40;
	int w12_pos_2_y = w12_y + 40;
	//Zmienne wyœwietlania objektów
	//Ska³a
	bool k1 = false;
	bool k2 = false;
	bool k3 = false;
	bool k4 = false;
	bool k5 = false;
	bool k6 = false;
	bool k7 = false;
	bool k8 = false;
	bool k9 = false;
	bool k10 = false;
	bool k11 = false;
	bool k12 = false;
	//¯elazo
	bool ze1 = false;
	bool ze2 = false;
	bool ze3 = false;
	bool ze4 = false;
	bool ze5 = false;
	bool ze6 = false;
	bool ze7 = false;
	bool ze8 = false;
	bool ze9 = false;
	bool ze10 = false;
	bool ze11 = false;
	bool ze12 = false;
	//Z³oto
	bool zl1 = false;
	bool zl2 = false;
	bool zl3 = false;
	bool zl4 = false;
	bool zl5 = false;
	bool zl6 = false;
	bool zl7 = false;
	bool zl8 = false;
	bool zl9 = false;
	bool zl10 = false;
	bool zl11 = false;
	bool zl12 = false;
	//Diament
	bool di1 = false;
	bool di2 = false;
	bool di3 = false;
	bool di4 = false;
	bool di5 = false;
	bool di6 = false;
	bool di7 = false;
	bool di8 = false;
	bool di9 = false;
	bool di10 = false;
	bool di11 = false;
	bool di12 = false;
	//Tasigaw
	bool w1 = false;
	bool w2 = false;
	bool w3 = false;
	bool w4 = false;
	bool w5 = false;
	bool w6 = false;
	bool w7 = false;
	bool w8 = false;
	bool w9 = false;
	bool w10 = false;
	bool w11 = false;
	bool w12 = false;
	//Zmienne bycia objektów
	//Ska³a
	bool thisk1 = false;
	bool thisk2 = false;
	bool thisk3 = false;
	bool thisk4 = false;
	bool thisk5 = false;
	bool thisk6 = false;
	bool thisk7 = false;
	bool thisk8 = false;
	bool thisk9 = false;
	bool thisk10 = false;
	bool thisk11 = false;
	bool thisk12 = false;
	//¯elazo
	bool thisz1 = false;
	bool thisz2 = false;
	bool thisz3 = false;
	bool thisz4 = false;
	bool thisz5 = false;
	bool thisz6 = false;
	bool thisz7 = false;
	bool thisz8 = false;
	bool thisz9 = false;
	bool thisz10 = false;
	bool thisz11 = false;
	bool thisz12 = false;
	//Z³oto
	bool thiszl1 = false;
	bool thiszl2 = false;
	bool thiszl3 = false;
	bool thiszl4 = false;
	bool thiszl5 = false;
	bool thiszl6 = false;
	bool thiszl7 = false;
	bool thiszl8 = false;
	bool thiszl9 = false;
	bool thiszl10 = false;
	bool thiszl11 = false;
	bool thiszl12 = false;
	//Diament
	bool thisd1 = false;
	bool thisd2 = false;
	bool thisd3 = false;
	bool thisd4 = false;
	bool thisd5 = false;
	bool thisd6 = false;
	bool thisd7 = false;
	bool thisd8 = false;
	bool thisd9 = false;
	bool thisd10 = false;
	bool thisd11 = false;
	bool thisd12 = false;
	//Tasigaw
	bool thisw1 = false;
	bool thisw2 = false;
	bool thisw3 = false;
	bool thisw4 = false;
	bool thisw5 = false;
	bool thisw6 = false;
	bool thisw7 = false;
	bool thisw8 = false;
	bool thisw9 = false;
	bool thisw10 = false;
	bool thisw11 = false;
	bool thisw12 = false;
	//Losowa liczba rud
	//Kamien
	int losKM = (std::rand() % 12) + 1;
	if(losKM >= 1){
		thisk1 = true;
		k1 = true;
	}
	if(losKM >= 2){
		thisk2 = true;
		k2 = true;
	}
	if(losKM >= 3){
		thisk3 = true;
		k3 = true;
	}
	if(losKM >= 4){
		thisk4 = true;
		k4 = true;
	}
	if(losKM >= 5){
		thisk5 = true;
		k5 = true;
	}
	if(losKM >= 6){
		thisk6 = true;
		k6 = true;
	}
	if(losKM >= 7){
		thisk7 = true;
		k7 = true;
	}
	if(losKM >= 8){
		thisk8 = true;
		k8 = true;
	}
	if(losKM >= 9){
		thisk9 = true;
		k9 = true;
	}
	if(losKM >= 10){
		thisk10 = true;
		k10 = true;
	}
	if(losKM >= 11){
		thisk11 = true;
		k11 = true;
	}
	if(losKM >= 12){
		thisk12 = true;
		k12 = true;
	}
	//¯elazo
	int losZM = (std::rand() % 12) + 1;
	if(losZM >= 1){
		thisz1 = true;
		ze1 = true;
	}
	if(losZM >= 2){
		thisz2 = true;
		ze2 = true;
	}
	if(losZM >= 3){
		thisz3 = true;
		ze3 = true;
	}
	if(losZM >= 4){
		thisz4 = true;
		ze4 = true;
	}
	if(losZM >= 5){
		thisz5 = true;
		ze5 = true;
	}
	if(losZM >= 6){
		thisz6 = true;
		ze6 = true;
	}
	if(losZM >= 7){
		thisz7 = true;
		ze7 = true;
	}
	if(losZM >= 8){
		thisz8 = true;
		ze8 = true;
	}
	if(losZM >= 9){
		thisz9 = true;
		ze9 = true;
	}
	if(losZM >= 10){
		thisz10 = true;
		ze10 = true;
	}
	if(losZM >= 11){
		thisz11 = true;
		ze11 = true;
	}
	if(losZM >= 12){
		thisz12 = true;
		ze12 = true;
	}
	//Z³oto
	int losZL = (std::rand() % 12) + 1;
	if(losZL >= 1){
		thiszl1 = true;
		zl1 = true;
	}
	if(losZL >= 2){
		thiszl2 = true;
		zl2 = true;
	}
	if(losZL >= 3){
		thiszl3 = true;
		zl3 = true;
	}
	if(losZL >= 4){
		thiszl4 = true;
		zl4 = true;
	}
	if(losZL >= 5){
		thiszl5 = true;
		zl5 = true;
	}
	if(losZL >= 6){
		thiszl6 = true;
		zl6 = true;
	}
	if(losZL >= 7){
		thiszl7 = true;
		zl7 = true;
	}
	if(losZL >= 8){
		thiszl8 = true;
		zl8 = true;
	}
	if(losZL >= 9){
		thiszl9 = true;
		zl9 = true;
	}
	if(losZL >= 10){
		thiszl10 = true;
		zl10 = true;
	}
	if(losZL >= 11){
		thiszl11 = true;
		zl11 = true;
	}
	if(losZL >= 12){
		thiszl12 = true;
		zl12 = true;
	}
	//Diament
	int losD = (std::rand() % 12) + 1;
	if(losD >= 1){
		thisd1 = true;
		di1 = true;
	}
	if(losD >= 2){
		thisd2 = true;
		di2 = true;
	}
	if(losD >= 3){
		thisd3 = true;
		di3 = true;
	}
	if(losD >= 4){
		thisd4 = true;
		di4 = true;
	}
	if(losD >= 5){
		thisd5 = true;
		di5 = true;
	}
	if(losD >= 6){
		thisd6 = true;
		di6 = true;
	}
	if(losD >= 7){
		thisd7 = true;
		di7 = true;
	}
	if(losD >= 8){
		thisd8 = true;
		di8 = true;
	}
	if(losD >= 9){
		thisd9 = true;
		di9 = true;
	}
	if(losD >= 10){
		thisd10 = true;
		di10 = true;
	}
	if(losD >= 11){
		thisd11 = true;
		di11 = true;
	}
	if(losD >= 12){
		thisd12 = true;
		di12 = true;
	}
	//Tasigaw
	int losT = (std::rand() % 12) + 1;
	if(losT >= 1){
		thisw1 = true;
		w1 = true;
	}
	if(losT >= 2){
		thisw2 = true;
		w2 = true;
	}
	if(losT >= 3){
		thisw3 = true;
		w3 = true;
	}
	if(losT >= 4){
		thisw4 = true;
		w4 = true;
	}
	if(losT >= 5){
		thisw5 = true;
		w5 = true;
	}
	if(losT >= 6){
		thisw6 = true;
		w6 = true;
	}
	if(losT >= 7){
		thisw7 = true;
		w7 = true;
	}
	if(losT >= 8){
		thisw8 = true;
		w8 = true;
	}
	if(losT >= 9){
		thisw9 = true;
		w9 = true;
	}
	if(losT >= 10){
		thisw10 = true;
		w10 = true;
	}
	if(losT >= 11){
		thisw11 = true;
		w11 = true;
	}
	if(losT >= 12){
		thisw12 = true;
		w12 = true;
	}
	//Nieskoñczona pêtla gry
	while(!key [ KEY_ESC ]){
		clear_to_color( bufor, makecol( 195, 195, 195 ) );
		myszka();

		//Rysowanie kopalni
		//Rudy/Ska³y
		//Kamien
		if(k1){
			masked_blit( kamien, bufor, 0, 0, o1_x, o1_y, kamien->w, kamien->h );
		}
		if(k2){
			masked_blit( kamien, bufor, 0, 0, o2_x, o2_y, kamien->w, kamien->h );
		}
		if(k3){
			masked_blit( kamien, bufor, 0, 0, o3_x, o3_y, kamien->w, kamien->h );
		}
		if(k4){
			masked_blit( kamien, bufor, 0, 0, o4_x, o4_y, kamien->w, kamien->h );
		}
		if(k5){
			masked_blit( kamien, bufor, 0, 0, o5_x, o5_y, kamien->w, kamien->h );
		}
		if(k6){
			masked_blit( kamien, bufor, 0, 0, o6_x, o6_y, kamien->w, kamien->h );
		}
		if(k7){
			masked_blit( kamien, bufor, 0, 0, o7_x, o7_y, kamien->w, kamien->h );
		}
		if(k8){
			masked_blit( kamien, bufor, 0, 0, o8_x, o8_y, kamien->w, kamien->h );
		}
		if(k9){
			masked_blit( kamien, bufor, 0, 0, o9_x, o9_y, kamien->w, kamien->h );
		}
		if(k10){
			masked_blit( kamien, bufor, 0, 0, o10_x, o10_y, kamien->w, kamien->h );
		}
		if(k11){
			masked_blit( kamien, bufor, 0, 0, o11_x, o11_y, kamien->w, kamien->h );
		}
		if(k12){
			masked_blit( kamien, bufor, 0, 0, o12_x, o12_y, kamien->w, kamien->h );
		}
		//¯elazo
		if(ze1){
			masked_blit( zelazo, bufor, 0, 0, z1_x, z1_y, zelazo->w, zelazo->h );
		}
		if(ze2){
			masked_blit( zelazo, bufor, 0, 0, z2_x, z2_y, zelazo->w, zelazo->h );
		}
		if(ze3){
			masked_blit( zelazo, bufor, 0, 0, z3_x, z3_y, zelazo->w, zelazo->h );
		}
		if(ze4){
			masked_blit( zelazo, bufor, 0, 0, z4_x, z4_y, zelazo->w, zelazo->h );
		}
		if(ze5){
			masked_blit( zelazo, bufor, 0, 0, z5_x, z5_y, zelazo->w, zelazo->h );
		}
		if(ze6){
			masked_blit( zelazo, bufor, 0, 0, z6_x, z6_y, zelazo->w, zelazo->h );
		}
		if(ze7){
			masked_blit( zelazo, bufor, 0, 0, z7_x, z7_y, zelazo->w, zelazo->h );
		}
		if(ze8){
			masked_blit( zelazo, bufor, 0, 0, z8_x, z8_y, zelazo->w, zelazo->h );
		}
		if(ze9){
			masked_blit( zelazo, bufor, 0, 0, z9_x, z9_y, zelazo->w, zelazo->h );
		}
		if(ze10){
			masked_blit( zelazo, bufor, 0, 0, z10_x, z10_y, zelazo->w, zelazo->h );
		}
		if(ze11){
			masked_blit( zelazo, bufor, 0, 0, z11_x, z11_y, zelazo->w, zelazo->h );
		}
		if(ze12){
			masked_blit( zelazo, bufor, 0, 0, z12_x, z12_y, zelazo->w, zelazo->h );
		}
		//Z³oto
		if(zl1){
			masked_blit( zloto, bufor, 0, 0, c1_x, zl1_y, zloto->w, zloto->h );
		}
		if(zl2){
			masked_blit( zloto, bufor, 0, 0, c2_x, zl2_y, zloto->w, zloto->h );
		}
		if(zl3){
			masked_blit( zloto, bufor, 0, 0, c3_x, zl3_y, zloto->w, zloto->h );
		}
		if(zl4){
			masked_blit( zloto, bufor, 0, 0, c4_x, zl4_y, zloto->w, zloto->h );
		}
		if(zl5){
			masked_blit( zloto, bufor, 0, 0, c5_x, zl5_y, zloto->w, zloto->h );
		}
		if(zl6){
			masked_blit( zloto, bufor, 0, 0, c6_x, zl6_y, zloto->w, zloto->h );
		}
		if(zl7){
			masked_blit( zloto, bufor, 0, 0, c7_x, zl7_y, zloto->w, zloto->h );
		}
		if(zl8){
			masked_blit( zloto, bufor, 0, 0, c8_x, zl8_y, zloto->w, zloto->h );
		}
		if(zl9){
			masked_blit( zloto, bufor, 0, 0, c9_x, zl9_y, zloto->w, zloto->h );
		}
		if(zl10){
			masked_blit( zloto, bufor, 0, 0, c10_x, zl10_y, zloto->w, zloto->h );
		}
		if(zl11){
			masked_blit( zloto, bufor, 0, 0, c11_x, zl11_y, zloto->w, zloto->h );
		}
		if(zl12){
			masked_blit( zloto, bufor, 0, 0, c12_x, zl12_y, zloto->w, zloto->h );
		}
		//Diament
		if(di1){
			masked_blit( diament, bufor, 0, 0, d1_x, d1_y, diament->w, diament->h );
		}
		if(di2){
			masked_blit( diament, bufor, 0, 0, d2_x, d2_y, diament->w, diament->h );
		}
		if(di3){
			masked_blit( diament, bufor, 0, 0, d3_x, d3_y, diament->w, diament->h );
		}
		if(di4){
			masked_blit( diament, bufor, 0, 0, d4_x, d4_y, diament->w, diament->h );
		}
		if(di5){
			masked_blit( diament, bufor, 0, 0, d5_x, d5_y, diament->w, diament->h );
		}
		if(di6){
			masked_blit( diament, bufor, 0, 0, d6_x, d6_y, diament->w, diament->h );
		}
		if(di7){
			masked_blit( diament, bufor, 0, 0, d7_x, d7_y, diament->w, diament->h );
		}
		if(di8){
			masked_blit( diament, bufor, 0, 0, d8_x, d8_y, diament->w, diament->h );
		}
		if(di9){
			masked_blit( diament, bufor, 0, 0, d9_x, d9_y, diament->w, diament->h );
		}
		if(di10){
			masked_blit( diament, bufor, 0, 0, d10_x, d10_y, diament->w, diament->h );
		}
		if(di11){
			masked_blit( diament, bufor, 0, 0, d11_x, d11_y, diament->w, diament->h );
		}
		if(di12){
			masked_blit( diament, bufor, 0, 0, d12_x, d12_y, diament->w, diament->h );
		}
		//Wagisat
		if(w1){
			masked_blit( wagisat, bufor, 0, 0, w1_x, w1_y, wagisat->w, wagisat->h );
		}
		if(w2){
			masked_blit( wagisat, bufor, 0, 0, w2_x, w2_y, wagisat->w, wagisat->h );
		}
		if(w3){
			masked_blit( wagisat, bufor, 0, 0, w3_x, w3_y, wagisat->w, wagisat->h );
		}
		if(w4){
			masked_blit( wagisat, bufor, 0, 0, w4_x, w4_y, wagisat->w, wagisat->h );
		}
		if(w5){
			masked_blit( wagisat, bufor, 0, 0, w5_x, w5_y, wagisat->w, wagisat->h );
		}
		if(w6){
			masked_blit( wagisat, bufor, 0, 0, w6_x, w6_y, wagisat->w, wagisat->h );
		}
		if(w7){
			masked_blit( wagisat, bufor, 0, 0, w7_x, w7_y, wagisat->w, wagisat->h );
		}
		if(w8){
			masked_blit( wagisat, bufor, 0, 0, w8_x, w8_y, wagisat->w, wagisat->h );
		}
		if(w9){
			masked_blit( wagisat, bufor, 0, 0, w9_x, w9_y, wagisat->w, wagisat->h );
		}
		if(w10){
			masked_blit( wagisat, bufor, 0, 0, w10_x, w10_y, wagisat->w, wagisat->h );
		}
		if(w11){
			masked_blit( wagisat, bufor, 0, 0, w11_x, w11_y, wagisat->w, wagisat->h );
		}
		if(w12){
			masked_blit( wagisat, bufor, 0, 0, w12_x, w12_y, wagisat->w, wagisat->h );
		}
		//Pod³o¿e
		masked_blit( podloze1, bufor, 0, 0, 0, 433, podloze1->w, podloze1->h );
		masked_blit( podloze1, bufor, 0, 0, 200, 433, podloze2->w, podloze2->h );
		masked_blit( podloze1, bufor, 0, 0, 400, 433, podloze3->w, podloze3->h );
		masked_blit( podloze1, bufor, 0, 0, 600, 433, podloze4->w, podloze4->h );
		//Kopalnia (lvl 2)
		if(kilof >= 6){
			masked_blit( kopalnia2, bufor, 0, 0, kop2, 191, kopalnia2->w, kopalnia2->h );
		}
		//GUI
		textprintf_ex( bufor, font, 450, 20, makecol( 255, 255, 255 ), - 1, "Craft Points: %d", money);
		textprintf_ex( bufor, font, 20, 60, makecol( 255, 255, 255 ), - 1, "Exit the mine: ESC");
		textprintf_ex( bufor, font, 220, 20, makecol( 255, 255, 255 ), - 1, "EQ ON: E");
		textprintf_ex( bufor, font, 220, 30, makecol( 255, 255, 255 ), - 1, "EQ OFF: F");
		textprintf_ex( bufor, font, 220, 40, makecol( 255, 255, 255 ), - 1, "The game will be automatically saved.");
		textprintf_ex( bufor, font, 10, 460, makecol( 255, 255, 255 ), - 1, "The Construgert v.1.2.3 by Brunon Blok");
		textprintf_ex( bufor, font, 480, 460, makecol( 255, 255, 255 ), - 1, "Author of Music: M");
		if(kilof < 6){
			textprintf_ex( bufor, font, 220, 60, makecol( 255, 255, 255 ), - 1, "Attack: 0"); 
		}
		if(kilof == 6){
			textprintf_ex( bufor, font, 220, 60, makecol( 255, 255, 255 ), - 1, "Attack: 20"); 
		}
		if(kilof == 7){
			textprintf_ex( bufor, font, 220, 60, makecol( 255, 255, 255 ), - 1, "Attack: 25"); 
		}
		if(kilof == 8){
			textprintf_ex( bufor, font, 220, 60, makecol( 255, 255, 255 ), - 1, "Attack: 30"); 
		}
		if(kilof == 9){
			textprintf_ex( bufor, font, 220, 60, makecol( 255, 255, 255 ), - 1, "Attack: 35"); 
		}
		//Samouczek
		if(sm){
			if(k1){
				textprintf_ex( bufor, font, o1_x, 303, makecol( 0, 0, 255 ), - 1, "To dig up some ore... (click S to read on)");
				if(key[KEY_S]){
					textprintf_ex( bufor, font, o1_x, 313, makecol( 0, 0, 255 ), - 1, "...hover mouse over a given ore,");
					textprintf_ex( bufor, font, o1_x, 323, makecol( 0, 0, 255 ), - 1, "and click the left mouse button.");
					textprintf_ex( bufor, font, o1_x, 333, makecol( 0, 0, 255 ), - 1, "Remember that you need to pick the appropriate pickaxe");
					textprintf_ex( bufor, font, o1_x, 343, makecol( 0, 0, 255 ), - 1, "(more on this in the inventory: click E).");
				}
			}
			textprintf_ex( bufor, font, 400, 240, makecol( 0, 0, 255 ), - 1, "To move to the next");
			textprintf_ex( bufor, font, 400, 250, makecol( 0, 0, 255 ), - 1, "sector of the mine go there.");
			textprintf_ex( bufor, font, 400, 260, makecol( 0, 0, 255 ), - 1, "----------------------------->");
			textprintf_ex( bufor, font, 1, 240, makecol( 0, 0, 255 ), - 1, "To move to the next");
			textprintf_ex( bufor, font, 1, 250, makecol( 0, 0, 255 ), - 1, "sector of the mine go there.");
			textprintf_ex( bufor, font, 1, 260, makecol( 0, 0, 255 ), - 1, "<-----------------------------");
		}
		//Gracz
		masked_blit( gracz, bufor, 0, 0, Gracz_x, Gracz_y, gracz->w, gracz->h );
		//Poruszanie siê
		if(key [ KEY_LEFT ]){
			Gracz_x--;
		}
		if(key [ KEY_RIGHT ]){
			Gracz_x++;
		}
		rest(10);

		//Przechodznie do kolejnych sektorów
		if(Gracz_x < -47){
			Gracz_x = 544;
			sm = false;
			goto label;
		}
		if(Gracz_x > 544){
			Gracz_x = -47;
			sm = false;
			goto label;
		}

		//"Stats" (F3)
		if(key[KEY_F3]){
			textprintf_ex( bufor, font, 20, 20, makecol( 255, 255, 255 ), - 1, "X: %d", Gracz_x);
			textprintf_ex( bufor, font, 20, 40, makecol( 255, 255, 255 ), - 1, "Y: %d", Gracz_y);
		}
		//Wejœcie do kopalni2
		if(kilof >= 6){
			//Wejœcie do kopalni
			int kop2Pos1 = 0;
			int kop2Pos2 = 0;
			kop2Pos1 = kop2 + 78;
			kop2Pos2 = kop2 - 78;
			if(Gracz_x < kop2Pos1 && Gracz_x > kop2Pos2 && key[KEY_SPACE]){
				stop_sample( muzyka1 );
				kopalnia_lvl2_start();
				goto label;
			}
		}
		//Kopanie rud/ska³
		//Ska³a
		if(kilof >= 1){
			if(thisk1){
				if(mx > o1_pos_1 && mx < o1_pos_2 && my > o1_pos_1_y && my < o1_pos_2_y && mb == 1){
					money += 20;
					k1 = false;
					thisk1 = false;
				}
			}
			if(thisk2){
				if(mx > o2_pos_1 && mx < o2_pos_2 && my > o2_pos_1_y && my < o2_pos_2_y && mb == 1){
					money += 20;
					k2 = false;
					thisk2 = false;
				}
			}
			if(thisk3){
				if(mx > o3_pos_1 && mx < o3_pos_2 && my > o3_pos_1_y && my < o3_pos_2_y && mb == 1){
					money += 20;
					k3 = false;
					thisk3 = false;
				}
			}
			if(thisk4){
				if(mx > o4_pos_1 && mx < o4_pos_2 && my > o4_pos_1_y && my < o4_pos_2_y && mb == 1){
					money += 20;
					k4 = false;
					thisk4 = false;
				}
			}
			if(thisk5){
				if(mx > o5_pos_1 && mx < o5_pos_2 && my > o5_pos_1_y && my < o5_pos_2_y && mb == 1){
					money += 20;
					k5 = false;
					thisk5 = false;
				}
			}
			if(thisk6){
				if(mx > o6_pos_1 && mx < o6_pos_2 && my > o6_pos_1_y && my < o6_pos_2_y && mb == 1){
					money += 20;
					k6 = false;
					thisk6 = false;
				}
			}
			if(thisk7){
				if(mx > o7_pos_1 && mx < o7_pos_2 && my > o7_pos_1_y && my < o7_pos_2_y && mb == 1){
					money += 20;
					k7 = false;
					thisk7 = false;
				}
			}
			if(thisk8){
				if(mx > o8_pos_1 && mx < o8_pos_2 && my > o8_pos_1_y && my < o8_pos_2_y && mb == 1){
					money += 20;
					k8 = false;
					thisk8 = false;
				}
			}
			if(thisk9){
				if(mx > o9_pos_1 && mx < o9_pos_2 && my > o9_pos_1_y && my < o9_pos_2_y && mb == 1){
					money += 20;
					k9 = false;
					thisk9 = false;
				}
			}
			if(thisk10){
				if(mx > o10_pos_1 && mx < o10_pos_2 && my > o10_pos_1_y && my < o10_pos_2_y && mb == 1){
					money += 20;
					k10 = false;
					thisk10 = false;
				}
			}
			if(thisk11){
				if(mx > o11_pos_1 && mx < o11_pos_2 && my > o11_pos_1_y && my < o11_pos_2_y && mb == 1){
					money += 20;
					k11 = false;
					thisk11 = false;
				}
			}
			if(thisk12){
				if(mx > o12_pos_1 && mx < o12_pos_2 && my > o12_pos_1_y && my < o12_pos_2_y && mb == 1){
					money += 20;
					k12 = false;
					thisk12 = false;
				}
			}
		}
		//¯elazo
		if(kilof >= 2){
			if(thisz1){
				if(mx > ze1_pos_1 && mx < ze1_pos_2 && my > z1_pos_1_y && my < z1_pos_2_y && mb == 1){
					money += 100;
					ze1 = false;
					thisz1 = false;
				}
			}
			if(thisz2){
				if(mx > ze2_pos_1 && mx < ze2_pos_2 && my > z2_pos_1_y && my < z2_pos_2_y && mb == 1){
					money += 100;
					ze2 = false;
					thisz2 = false;
				}
			}
			if(thisz3){
				if(mx > ze3_pos_1 && mx < ze3_pos_2 && my > z3_pos_1_y && my < z3_pos_2_y && mb == 1){
					money += 100;
					ze3 = false;
					thisz3 = false;
				}
			}
			if(thisz4){
				if(mx > ze4_pos_1 && mx < ze4_pos_2 && my > z4_pos_1_y && my < z4_pos_2_y && mb == 1){
					money += 100;
					ze4 = false;
					thisz4 = false;
				}
			}
			if(thisz5){
				if(mx > ze5_pos_1 && mx < ze5_pos_2 && my > z5_pos_1_y && my < z5_pos_2_y && mb == 1){
					money += 40;
					ze5 = false;
					thisz5 = false;
				}
			}
			if(thisz6){
				if(mx > ze6_pos_1 && mx < ze6_pos_2 && my > z6_pos_1_y && my < z6_pos_2_y && mb == 1){
					money += 100;
					ze6 = false;
					thisz6 = false;
				}
			}
			if(thisz7){
				if(mx > ze7_pos_1 && mx < ze7_pos_2 && my > z7_pos_1_y && my < z7_pos_2_y && mb == 1){
					money += 100;
					ze7 = false;
					thisz7 = false;
				}
			}
			if(thisz8){
				if(mx > ze8_pos_1 && mx < ze8_pos_2 && my > z8_pos_1_y && my < z8_pos_2_y && mb == 1){
					money += 100;
					ze8 = false;
					thisz8 = false;
				}
			}
			if(thisz9){
				if(mx > ze9_pos_1 && mx < ze9_pos_2 && my > z9_pos_1_y && my < z9_pos_2_y && mb == 1){
					money += 100;
					ze9 = false;
					thisz9 = false;
				}
			}
			if(thisz10){
				if(mx > ze10_pos_1 && mx < ze10_pos_2 && my > z10_pos_1_y && my < z10_pos_2_y && mb == 1){
					money += 100;
					ze10 = false;
					thisz10 = false;
				}
			}
			if(thisz11){
				if(mx > ze11_pos_1 && mx < ze11_pos_2 && my > z11_pos_1_y && my < z11_pos_2_y && mb == 1){
					money += 100;
					ze11 = false;
					thisz11 = false;
				}
			}
			if(thisz12){
				if(mx > ze12_pos_1 && mx < ze12_pos_2 && my > z12_pos_1_y && my < z12_pos_2_y && mb == 1){
					money += 100;
					ze12 = false;
					thisz12 = false;
				}
			}
		}
		if (kilof >= 3){
			if(thiszl1){
				if(mx > zl1_pos_1 && mx < zl1_pos_2 && my > zl1_pos_1_y && my < zl1_pos_2_y && mb == 1){
					money += 500;
					zl1 = false;
					thiszl1 = false;
				}
			}
			if(thiszl2){
				if(mx > zl2_pos_1 && mx < zl2_pos_2 && my > zl2_pos_1_y && my < zl2_pos_2_y && mb == 1){
					money += 500;
					zl2 = false;
					thiszl2 = false;
				}
			}
			if(thiszl3){
				if(mx > zl3_pos_1 && mx < zl3_pos_2 && my > zl3_pos_1_y && my < zl3_pos_2_y && mb == 1){
					money += 500;
					zl3 = false;
					thiszl3 = false;
				}
			}
			if(thiszl4){
				if(mx > zl4_pos_1 && mx < zl4_pos_2 && my > zl4_pos_1_y && my < zl4_pos_2_y && mb == 1){
					money += 500;
					zl4 = false;
					thiszl4 = false;
				}
			}
			if(thiszl5){
				if(mx > zl5_pos_1 && mx < zl5_pos_2 && my > zl5_pos_1_y && my < zl5_pos_2_y && mb == 1){
					money += 500;
					zl5 = false;
					thiszl5 = false;
				}
			}
			if(thiszl6){
				if(mx > zl6_pos_1 && mx < zl6_pos_2 && my > zl6_pos_1_y && my < zl6_pos_2_y && mb == 1){
					money += 500;
					zl6 = false;
					thiszl6 = false;
				}
			}
			if(thiszl7){
				if(mx > zl7_pos_1 && mx < zl7_pos_2 && my > zl7_pos_1_y && my < zl7_pos_2_y && mb == 1){
					money += 500;
					zl7 = false;
					thiszl7 = false;
				}
			}
			if(thiszl8){
				if(mx > zl8_pos_1 && mx < zl8_pos_2 && my > zl8_pos_1_y && my < zl8_pos_2_y && mb == 1){
					money += 500;
					zl8 = false;
					thiszl8 = false;
				}
			}
			if(thiszl9){
				if(mx > zl9_pos_1 && mx < zl9_pos_2 && my > zl9_pos_1_y && my < zl9_pos_2_y && mb == 1){
					money += 500;
					zl9 = false;
					thiszl9 = false;
				}
			}
			if(thiszl10){
				if(mx > zl10_pos_1 && mx < zl10_pos_2 && my > zl10_pos_1_y && my < zl10_pos_2_y && mb == 1){
					money += 500;
					zl10 = false;
					thiszl10 = false;
				}
			}
			if(thiszl11){
				if(mx > zl11_pos_1 && mx < zl11_pos_2 && my > zl11_pos_1_y && my < zl11_pos_2_y && mb == 1){
					money += 500;
					zl11 = false;
					thiszl11 = false;
				}
			}
			if(thiszl12){
				if(mx > zl12_pos_1 && mx < zl12_pos_2 && my > zl12_pos_1_y && my < zl12_pos_2_y && mb == 1){
					money += 500;
					zl12 = false;
					thiszl12 = false;
				}
			}
		}
		//Diament
		if(kilof >= 4){
			if(thisd1){
				if(mx > d1_pos_1 && mx < d1_pos_2 && my > d1_pos_1_y && my < d1_pos_2_y && mb == 1){
					money += 2000;
					di1 = false;
					thisd1 = false;
				}
			}
			if(thisd2){
				if(mx > d2_pos_1 && mx < d2_pos_2 && my > d2_pos_1_y && my < d2_pos_2_y && mb == 1){
					money += 2000;
					di2 = false;
					thisd2 = false;
				}
			}
			if(thisd3){
				if(mx > d3_pos_1 && mx < d3_pos_2 && my > d3_pos_1_y && my < d3_pos_2_y && mb == 1){
					money += 2000;
					di3 = false;
					thisd3 = false;
				}
			}
			if(thisd4){
				if(mx > d4_pos_1 && mx < d4_pos_2 && my > d4_pos_1_y && my < d4_pos_2_y && mb == 1){
					money += 2000;
					di4 = false;
					thisd4 = false;
				}
			}
			if(thisd5){
				if(mx > d5_pos_1 && mx < d5_pos_2 && my > d5_pos_1_y && my < d5_pos_2_y && mb == 1){
					money += 2000;
					di5 = false;
					thisd5 = false;
				}
			}
			if(thisd6){
				if(mx > d6_pos_1 && mx < d6_pos_2 && my > d6_pos_1_y && my < d6_pos_2_y && mb == 1){
					money += 2000;
					di6 = false;
					thisd6 = false;
				}
			}
			if(thisd7){
				if(mx > d7_pos_1 && mx < d7_pos_2 && my > d7_pos_1_y && my < d7_pos_2_y && mb == 1){
					money += 2000;
					di7 = false;
					thisd7 = false;
				}
			}
			if(thisd8){
				if(mx > d8_pos_1 && mx < d8_pos_2 && my > d8_pos_1_y && my < d8_pos_2_y && mb == 1){
					money += 2000;
					di8 = false;
					thisd8 = false;
				}
			}
			if(thisd9){
				if(mx > d9_pos_1 && mx < d9_pos_2 && my > d9_pos_1_y && my < d9_pos_2_y && mb == 1){
					money += 2000;
					di9 = false;
					thisd9 = false;
				}
			}
			if(thisd10){
				if(mx > d10_pos_1 && mx < d10_pos_2 && my > d10_pos_1_y && my < d10_pos_2_y && mb == 1){
					money += 2000;
					di10 = false;
					thisd10 = false;
				}
			}
			if(thisd11){
				if(mx > d11_pos_1 && mx < d11_pos_2 && my > d11_pos_1_y && my < d11_pos_2_y && mb == 1){
					money += 2000;
					di11 = false;
					thisd11 = false;
				}
			}
			if(thisd12){
				if(mx > d12_pos_1 && mx < d12_pos_2 && my > d12_pos_1_y && my < d12_pos_2_y && mb == 1){
					money += 2000;
					di12 = false;
					thisd12 = false;
				}
			}
		}
		if(kilof >= 5){
			//Wagisat
			if(thisw1){
				if(mx > w1_pos_1 && mx < w1_pos_2 && my > w1_pos_1_y && my < w1_pos_2_y && mb == 1){
					money += 5000;
					w1 = false;
					thisw1 = false;
				}
			}
			if(thisw2){
				if(mx > w2_pos_1 && mx < w2_pos_2 && my > w2_pos_1_y && my < w2_pos_2_y && mb == 1){
					money += 5000;
					w2 = false;
					thisw2 = false;
				}
			}
			if(thisw3){
				if(mx > w3_pos_1 && mx < w3_pos_2 && my > w3_pos_1_y && my < w3_pos_2_y && mb == 1){
					money += 5000;
					w3 = false;
					thisw3 = false;
				}
			}
			if(thisw4){
				if(mx > w4_pos_1 && mx < w4_pos_2 && my > w4_pos_1_y && my < w4_pos_2_y && mb == 1){
					money += 5000;
					w4 = false;
					thisw4 = false;
				}
			}
			if(thisw5){
				if(mx > w5_pos_1 && mx < w5_pos_2 && my > w5_pos_1_y && my < w5_pos_2_y && mb == 1){
					money += 5000;
					w5 = false;
					thisw5 = false;
				}
			}
			if(thisw6){
				if(mx > w6_pos_1 && mx < w6_pos_2 && my > w6_pos_1_y && my < w6_pos_2_y && mb == 1){
					money += 5000;
					w6 = false;
					thisw6 = false;
				}
			}
			if(thisw7){
				if(mx > w7_pos_1 && mx < w7_pos_2 && my > w7_pos_1_y && my < w7_pos_2_y && mb == 1){
					money += 5000;
					w7 = false;
					thisw7 = false;
				}
			}
			if(thisw8){
				if(mx > w8_pos_1 && mx < w8_pos_2 && my > w8_pos_1_y && my < w8_pos_2_y && mb == 1){
					money += 5000;
					w8 = false;
					thisw8 = false;
				}
			}
			if(thisw9){
				if(mx > w9_pos_1 && mx < w9_pos_2 && my > w9_pos_1_y && my < w9_pos_2_y && mb == 1){
					money += 5000;
					w9 = false;
					thisw9 = false;
				}
			}
			if(thisw10){
				if(mx > w10_pos_1 && mx < w10_pos_2 && my > w10_pos_1_y && my < w10_pos_2_y && mb == 1){
					money += 5000;
					w10 = false;
					thisw10 = false;
				}
			}
			if(thisw11){
				if(mx > w11_pos_1 && mx < w11_pos_2 && my > w11_pos_1_y && my < w11_pos_2_y && mb == 1){
					money += 5000;
					w11 = false;
					thisw11 = false;
				}
			}
			if(thisw12){
				if(mx > w12_pos_1 && mx < w12_pos_2 && my > w12_pos_1_y && my < w12_pos_2_y && mb == 1){
					money += 5000;
					w12 = false;
					thisw12 = false;
				}
			}
		}
		//Otwieranie ekwipunku
		if(key [KEY_E]){
			ekwipunek();
			if(kilof == 0){
				gracz = load_bmp("Grafika/Gracz/gracz.bmp", default_palette);
			}
			if(kilof == 1){
				gracz = load_bmp("Grafika/Gracz/gracz_z_drewnianym_kilofem.bmp", default_palette);
			}
			if(kilof == 2){
				gracz = load_bmp("Grafika/Gracz/gracz_z_kamiennym_kilofem.bmp", default_palette);
			}
			if(kilof == 3){
				gracz = load_bmp("Grafika/Gracz/gracz_z_zelaznym_kilofem.bmp", default_palette);
			}
			if(kilof == 4){
				gracz = load_bmp("Grafika/Gracz/gracz_ze_zlotym_kilofem.bmp", default_palette);
			}
			if(kilof == 5){
				gracz = load_bmp("Grafika/Gracz/gracz_z_diamentowym_kilofem.bmp", default_palette);
			}
			if(kilof == 6){
				gracz = load_bmp("Grafika/Gracz/gracz_z_tasigaw_kilofem.bmp", default_palette);
			}
			if(kilof == 7){
				gracz = load_bmp("Grafika/Gracz/gracz_z_redmatter_kilofem.bmp", default_palette);
			}
			if(kilof == 8){
				gracz = load_bmp("Grafika/Gracz/gracz_z_orangematter_kilofem.bmp", default_palette);
			}
			if(kilof == 9){
				gracz = load_bmp("Grafika/Gracz/gracz_z_yellowmatter_kilofem.bmp", default_palette);
			}
			if(kilof == 10){
				gracz = load_bmp("Grafika/Gracz/gracz_z_bluematter_kilofem.bmp", default_palette);
			}
		}
		//Zapisywanie Gry
		zapisGry();

		//Stwierdzenie autorstwa muzyki
		if(key[KEY_M]){
			textprintf_ex( bufor, font, 180, 150, makecol( 255, 255, 255 ), - 1, "Music: 'Project System 12 - Breath of Hope' (CC)");
		}
		//Music ON/OFF
		if(!key[KEY_F3]){
			textprintf_ex( bufor, font, 20, 20, makecol( 255, 255, 255 ), - 1, "Music ON/OFF: N");
		}
		if(music == true){
			if(key[KEY_N]){
				stop_sample( muzyka1 );
				rest(300);
				music = false;
			}
		}
		if(music == false){
			if(key[KEY_N]){
				play_sample( muzyka1, 255, 127, 1000, 1 );
				rest(300);
				music = true;
			}
		}

		blit( bufor, screen, 0, 0, 0, 0, 640, 480 );
	}
	zapisGry();
	stop_sample( muzyka1 );
	destroy_sample( muzyka1 );
	destroy_bitmap(gracz);
	destroy_bitmap(podloze1);
	destroy_bitmap(podloze2);
	destroy_bitmap(podloze3);
	destroy_bitmap(podloze4);
	destroy_bitmap(kamien);
	destroy_bitmap(zelazo);
	destroy_bitmap(zloto);
	destroy_bitmap(bufor);
	allegro_exit();
	return 0;
}
END_OF_FUNCTION(kopalnia_start);

int main(){
	//Funkcje wstêpne
	odczytGry();
	label:
	allegro_init();
	install_keyboard();
	install_mouse();
	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED,640,480,0,0);
	clear_to_color( screen, makecol(450,250,250) );
	show_mouse(screen);
    unscare_mouse();
	srand( time( NULL ) );
	clear_to_color( screen, makecol( 153, 217, 234 ) );
	install_sound( DIGI_AUTODETECT, MIDI_AUTODETECT, "" );
	set_volume( 255, 255 );
	//Pobieranie muzyki
	SAMPLE * muzyka1 = NULL;
	muzyka1 = load_sample( "Muzyka/Project_System_12_-_Breath_of_Hope.wav" );
	//Pobieranie grafiki
	BITMAP * gracz = NULL;
	if(kilof == 0){
		gracz = load_bmp("Grafika/Gracz/gracz.bmp", default_palette);
	}
	if(kilof == 1){
		gracz = load_bmp("Grafika/Gracz/gracz_z_drewnianym_kilofem.bmp", default_palette);
	}
	if(kilof == 2){
		gracz = load_bmp("Grafika/Gracz/gracz_z_kamiennym_kilofem.bmp", default_palette);
	}
	if(kilof == 3){
		gracz = load_bmp("Grafika/Gracz/gracz_z_zelaznym_kilofem.bmp", default_palette);
	}
	if(kilof == 4){
		gracz = load_bmp("Grafika/Gracz/gracz_ze_zlotym_kilofem.bmp", default_palette);
	}
	if(kilof == 5){
		gracz = load_bmp("Grafika/Gracz/gracz_z_diamentowym_kilofem.bmp", default_palette);
	}
	if(kilof == 6){
		gracz = load_bmp("Grafika/Gracz/gracz_z_tasigaw_kilofem.bmp", default_palette);
	}
	if(kilof == 7){
		gracz = load_bmp("Grafika/Gracz/gracz_z_redmatter_kilofem.bmp", default_palette);
	}
	if(kilof == 8){
		gracz = load_bmp("Grafika/Gracz/gracz_z_orangematter_kilofem.bmp", default_palette);
	}
	if(kilof == 9){
		gracz = load_bmp("Grafika/Gracz/gracz_z_yellowmatter_kilofem.bmp", default_palette);
	}
	if(kilof == 10){
		gracz = load_bmp("Grafika/Gracz/gracz_z_bluematter_kilofem.bmp", default_palette);
	}
	BITMAP * ziemia1 = NULL;
	ziemia1 = load_bmp("Grafika/ziemia1.bmp", default_palette);
	BITMAP * ziemia2 = NULL;
	ziemia2 = load_bmp("Grafika/ziemia2.bmp", default_palette);
	BITMAP * ziemia3 = NULL;
	ziemia3 = load_bmp("Grafika/ziemia3.bmp", default_palette);
	BITMAP * ziemia4 = NULL;
	ziemia4 = load_bmp("Grafika/ziemia4.bmp", default_palette);
	BITMAP * drzewo = NULL;
	drzewo = load_bmp("Grafika/drzewo_default.bmp", default_palette);
	BITMAP * kopalnia = NULL;
	kopalnia = load_bmp("Grafika/kopalnia1.bmp", default_palette);
	BITMAP * strzalka = NULL;
	strzalka = load_bmp("Grafika/strzalka-tutorial.bmp", default_palette);
	BITMAP * bufor = NULL;
	bufor = create_bitmap( 640, 480 );
	
	//Losowe generowanie koordynatów objektów
	//Drzewa
	int a1 = (std::rand() % 200) + 0;
	int a2 = (std::rand() % 200) + 200;
	int a3 = (std::rand() % 45) + 400;
	int a4 = (std::rand() % 100) + 450;
	//Kopalnie
	int kop1 = (std::rand() % 500) + 0;
	Gracz_x = kop1;
	//Zmienne wyœwietlania objektów
	bool wh_a1 = true;
	bool wh_a2 = true;
	bool wh_a3 = true;
	bool wh_a4 = true;
	//Zmienne bycia objektów
	bool thisa1 = true;
	bool thisa2 = true;
	bool thisa3 = true;
	bool thisa4 = true;
	//Muzyka ON
	play_sample( muzyka1, 255, 127, 1000, 1 );
	//Pêtla gry
	while(!key [ KEY_ESC ]){
		clear_to_color( bufor, makecol( 153, 217, 234 ) );

		//Generator swiata
		//Rysowanie drzew
		if(wh_a1){
			masked_blit( drzewo, bufor, 0, 0, a1, 250, drzewo->w, drzewo->h );
		}
		if(wh_a2){
			masked_blit( drzewo, bufor, 0, 0, a2, 250, drzewo->w, drzewo->h );
		}
		if(wh_a3){
			masked_blit( drzewo, bufor, 0, 0, a3, 250, drzewo->w, drzewo->h );
		}
		if(wh_a4){
			masked_blit( drzewo, bufor, 0, 0, a4, 250, drzewo->w, drzewo->h );
		}
		//Kopalnie
		masked_blit( kopalnia, bufor, 0, 0, kop1, 191, kopalnia->w, kopalnia->h );
		//Ziemia
		masked_blit( ziemia1, bufor, 0, 0, 0, 433, ziemia1->w, ziemia1->h );
		masked_blit( ziemia2, bufor, 0, 0, 200, 433, ziemia2->w, ziemia2->h );
		masked_blit( ziemia3, bufor, 0, 0, 400, 433, ziemia3->w, ziemia3->h );
		masked_blit( ziemia4, bufor, 0, 0, 600, 433, ziemia4->w, ziemia4->h );
		//GUI
		textprintf_ex( bufor, font, 450, 20, makecol( 255, 255, 255 ), - 1, "Craft Points: %d", money);
		if(kilof < 6){
			textprintf_ex( bufor, font, 220, 60, makecol( 255, 255, 255 ), - 1, "Attack: 0"); 
		}
		if(kilof == 6){
			textprintf_ex( bufor, font, 220, 60, makecol( 255, 255, 255 ), - 1, "Attack: 20"); 
		}
		if(kilof == 7){
			textprintf_ex( bufor, font, 220, 60, makecol( 255, 255, 255 ), - 1, "Attack: 25"); 
		}
		if(kilof == 8){
			textprintf_ex( bufor, font, 220, 60, makecol( 255, 255, 255 ), - 1, "Attack: 30"); 
		}
		if(kilof == 9){
			textprintf_ex( bufor, font, 220, 60, makecol( 255, 255, 255 ), - 1, "Attack: 35"); 
		}
		textprintf_ex( bufor, font, 220, 20, makecol( 255, 255, 255 ), - 1, "EQ ON: E");
		textprintf_ex( bufor, font, 220, 30, makecol( 255, 255, 255 ), - 1, "EQ OFF: F");
		textprintf_ex( bufor, font, 20, 60, makecol( 255, 255, 255 ), - 1, "Exit the game: ESC");
		textprintf_ex( bufor, font, 220, 40, makecol( 255, 255, 255 ), - 1, "The game will be automatically saved.");
		textprintf_ex( bufor, font, 10, 460, makecol( 255, 255, 255 ), - 1, "The Construgert v.1.2.3 by Brunon Blok");
		textprintf_ex( bufor, font, 480, 460, makecol( 255, 255, 255 ), - 1, "Author of Music: M");
		//Samouczek
		if(wh_a1){
			textprintf_ex( bufor, font, a1, 240, makecol( 255, 255, 255 ), - 1, "To cut down the tree");
			textprintf_ex( bufor, font, a1, 250, makecol( 255, 255, 255 ), - 1, "walk up to him");
			textprintf_ex( bufor, font, a1, 260, makecol( 255, 255, 255 ), - 1, "and click SPACE.");
		}
		textprintf_ex( bufor, font, kop1, 160, makecol( 255, 255, 255 ), - 1, "To enter the mine");
		textprintf_ex( bufor, font, kop1, 170, makecol( 255, 255, 255 ), - 1, "walk up to it");
		textprintf_ex( bufor, font, kop1, 180, makecol( 255, 255, 255 ), - 1, "and click SPACE.");
		textprintf_ex( bufor, font, 220, 100, makecol( 255, 0, 0 ), - 1, "READ IT!");
		masked_blit( strzalka, bufor, 0, 0, 290, 70, strzalka->w, strzalka->h );
		//Gracz
		masked_blit( gracz, bufor, 0, 0, Gracz_x, Gracz_y, gracz->w, gracz->h );
		//Poruszanie siê
		if(key [ KEY_LEFT ]){
			Gracz_x--;
		}
		if(key [ KEY_RIGHT ]){
			Gracz_x++;
		}
		rest(10);

		//Kolizje gracza z ekranem
		if(Gracz_x < -47)Gracz_x = -47;
		if(Gracz_x > 544)Gracz_x = 544;

		//"Stats" (F3)
		if(key[KEY_F3]){
			textprintf_ex( bufor, font, 20, 20, makecol( 255, 255, 255 ), - 1, "X: %d", Gracz_x);
			textprintf_ex( bufor, font, 20, 40, makecol( 255, 255, 255 ), - 1, "Y: %d", Gracz_y);
		}
		//Wejœcie do kopalni
		int kopPos1 = 0;
		int kopPos2 = 0;
		kopPos1 = kop1 + 78;
		kopPos2 = kop1 - 78;
		if(Gracz_x < kopPos1 && Gracz_x > kopPos2 && key[KEY_SPACE]){
			stop_sample( muzyka1 );
			kopalnia_start();
			goto label;
		}
			
		//Otwieranie ekwipunku
		if(key [KEY_E]){
			ekwipunek();
			if(kilof == 0){
				gracz = load_bmp("Grafika/Gracz/gracz.bmp", default_palette);
			}
			if(kilof == 1){
				gracz = load_bmp("Grafika/Gracz/gracz_z_drewnianym_kilofem.bmp", default_palette);
			}
			if(kilof == 2){
				gracz = load_bmp("Grafika/Gracz/gracz_z_kamiennym_kilofem.bmp", default_palette);
			}
			if(kilof == 3){
				gracz = load_bmp("Grafika/Gracz/gracz_z_zelaznym_kilofem.bmp", default_palette);
			}
			if(kilof == 4){
				gracz = load_bmp("Grafika/Gracz/gracz_ze_zlotym_kilofem.bmp", default_palette);
			}
			if(kilof == 5){
				gracz = load_bmp("Grafika/Gracz/gracz_z_diamentowym_kilofem.bmp", default_palette);
			}
			if(kilof == 6){
				gracz = load_bmp("Grafika/Gracz/gracz_z_tasigaw_kilofem.bmp", default_palette);
			}
			if(kilof == 7){
				gracz = load_bmp("Grafika/Gracz/gracz_z_redmatter_kilofem.bmp", default_palette);
			}
			if(kilof == 8){
				gracz = load_bmp("Grafika/Gracz/gracz_z_orangematter_kilofem.bmp", default_palette);
			}
			if(kilof == 9){
				gracz = load_bmp("Grafika/Gracz/gracz_z_yellowmatter_kilofem.bmp", default_palette);
			}
			if(kilof == 10){
				gracz = load_bmp("Grafika/Gracz/gracz_z_bluematter_kilofem.bmp", default_palette);
			}
		}
		//Zapisywanie Gry
		zapisGry();
		//Music ON/OFF
		if(!key[KEY_F3]){
			textprintf_ex( bufor, font, 20, 20, makecol( 255, 255, 255 ), - 1, "Music ON/OFF: N");
		}
		if(music == true){
			if(key[KEY_N]){
				stop_sample( muzyka1 );
				rest(300);
				music = false;
			}
		}
		if(music == false){
			if(key[KEY_N]){
				play_sample( muzyka1, 255, 127, 1000, 1 );
				rest(300);
				music = true;
			}
		}
		//Œcinanie drzew
		if(kilof >= 0){
			if(thisa1){
				if(Gracz_x <= a1 && Gracz_x > a1 - 40 && key[KEY_SPACE] || Gracz_x >= a1 && Gracz_x < a1 + 40 && key[KEY_SPACE]){
					wh_a1 = false;
					thisa1 = false;
					money += 5;
				}
			}
			if(thisa2){
				if(Gracz_x <= a2 && Gracz_x > a2 - 40 && key[KEY_SPACE] || Gracz_x >= a2 && Gracz_x < a2 + 40 && key[KEY_SPACE]){
					wh_a2 = false;
					thisa2 = false;
					money += 5;
				}
			}
			if(thisa3){
				if(Gracz_x <= a3 && Gracz_x > a3 - 40 && key[KEY_SPACE] || Gracz_x >= a3 && Gracz_x < a3 + 40 && key[KEY_SPACE]){
					wh_a3 = false;
					thisa3 = false;
					money += 5;
				}
			}
			if(thisa4){
				if(Gracz_x <= a4 && Gracz_x > a4 - 40 && key[KEY_SPACE] || Gracz_x >= a4 && Gracz_x < a4 + 40 && key[KEY_SPACE]){
					wh_a4 = false;
					thisa4 = false;
					money += 5;
				}
			}
			//Stwierdzenie autorstwa muzyki
			if(key[KEY_M]){
				textprintf_ex( bufor, font, 180, 150, makecol( 255, 255, 255 ), - 1, "Music: 'Project System 12 - Breath of Hope' (CC)");
			}
		}
		blit( bufor, screen, 0, 0, 0, 0, 640, 480 );
	}

	zapisGry();
	stop_sample( muzyka1 );
	destroy_sample( muzyka1 );
	destroy_bitmap(gracz);
	destroy_bitmap(kopalnia);
	destroy_bitmap(drzewo);
	destroy_bitmap(ziemia1);
	destroy_bitmap(ziemia2);
	destroy_bitmap(ziemia3);
	destroy_bitmap(bufor);
	allegro_exit;
	return 0;
}
END_OF_MAIN();