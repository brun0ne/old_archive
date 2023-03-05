#include "graphics.h"

BITMAP * stone;
BITMAP * dirtStone;
BITMAP * stoneTower;
BITMAP * stoneWall;
BITMAP * uglyStoneWall;
BITMAP * bigBuilding;
BITMAP * shop;
BITMAP * foodShop;
BITMAP * bin;

BITMAP * mountBack;

BITMAP * way;

BITMAP * caveEnter;
BITMAP * blueTree1;
BITMAP * blueTree2;
BITMAP * wulkan;

BITMAP * shortHouse1;
BITMAP * shortHouse2;
BITMAP * shortHouse3;
BITMAP * shortHouse4;

BITMAP * newsLetter;

BITMAP * button;
BITMAP * l_button;

BITMAP * desk;
BITMAP * defaultDoor;
BITMAP * chair;
BITMAP * szafa;
BITMAP * siekiera;
BITMAP * drewno;
BITMAP * klapa_drewno;
BITMAP * szafa_jedz;
BITMAP * box;

// FOREST

BITMAP * tree_i;
BITMAP * bush;
BITMAP * flower;
BITMAP * rock;
BITMAP * woodroll;

BITMAP * wooden_house;

BITMAP * filons_statue;

void graph_init()
{
	stone = load_bmp("Grafika/Gra/Default/stone.bmp", default_palette);
	stoneTower = load_bmp("Grafika/Gra/Budynki/stoneTower.bmp", default_palette);
	stoneWall = load_bmp("Grafika/Gra/Default/stoneWall.bmp", default_palette);
	uglyStoneWall = load_bmp("Grafika/Gra/Default/uglyStoneWall.bmp", default_palette);
	bigBuilding = load_bmp("Grafika/Gra/Budynki/bigBuilding.bmp", default_palette);
	shop = load_bmp("Grafika/Gra/Budynki/shop.bmp", default_palette);
	foodShop = load_bmp("Grafika/Gra/Budynki/foodShop.bmp", default_palette);
	bin = load_bmp("Grafika/Gra/Budynki/bin.bmp", default_palette);

	mountBack = load_bmp("Grafika/Gra/Budynki/mountainsBackground.bmp", default_palette);

	way = load_bmp("Grafika/Gra/Budynki/way.bmp", default_palette);

	caveEnter = load_bmp("Grafika/Gra/Budynki/caveEnter.bmp", default_palette);
	blueTree1 = load_bmp("Grafika/Gra/Budynki/blueTree1.bmp", default_palette);
	blueTree2 = load_bmp("Grafika/Gra/Budynki/blueTree2.bmp", default_palette);
	wulkan = load_bmp("Grafika/Gra/Budynki/wulkan.bmp", default_palette);

	shortHouse1 = load_bmp("Grafika/Gra/Budynki/shortHouse1.bmp", default_palette);
	shortHouse2 = load_bmp("Grafika/Gra/Budynki/shortHouse2.bmp", default_palette);
	shortHouse3 = load_bmp("Grafika/Gra/Budynki/shortHouse3.bmp", default_palette);
	shortHouse4 = load_bmp("Grafika/Gra/Budynki/shortHouse4.bmp", default_palette);

	newsLetter = load_bmp("Grafika/Gra/Budynki/newsLetter.bmp", default_palette);

	desk = load_bmp("Grafika/Gra/Meble/biurko.bmp", default_palette);
	defaultDoor = load_bmp("Grafika/Gra/Default/defaultDoor.bmp", default_palette);
	chair = load_bmp("Grafika/Gra/Meble/chair.bmp", default_palette);
	szafa = load_bmp("Grafika/Gra/Teren/Lokacje/ConCity/Zbrojownia/szafa.bmp", default_palette);
	siekiera = load_bmp("Grafika/Gra/Default/siekiera.bmp", default_palette);
	drewno = load_bmp("Grafika/Gra/Default/drewno.bmp", default_palette);
	klapa_drewno = load_bmp("Grafika/Gra/Default/klapa_drewno.bmp", default_palette);
	szafa_jedz = load_bmp("Grafika/Gra/Teren/Lokacje/ConCity/FoodShop/szafa.bmp", default_palette);
	box = load_bmp("Grafika/Gra/Budynki/box.bmp", default_palette);

	button = load_bmp("Grafika/Gra/Default/button.bmp", default_palette);
	l_button = load_bmp("Grafika/Gra/Default/l_button.bmp", default_palette);

	// FOREST

	tree_i = load_bmp("Grafika/Gra/Budynki/Forest/tree_i.bmp", default_palette);
	bush = load_bmp("Grafika/Gra/Budynki/Forest/bush.bmp", default_palette);
	flower = load_bmp("Grafika/Gra/Budynki/Forest/flower.bmp", default_palette);
	rock = load_bmp("Grafika/Gra/Budynki/Forest/rock.bmp", default_palette);
	woodroll = load_bmp("Grafika/Gra/Meble/wood.bmp", default_palette);

	wooden_house = load_bmp("Grafika/Gra/Budynki/wooden_house.bmp", default_palette);

	filons_statue = load_bmp("Grafika/Gra/Teren/Lokacje/Volcano/statue.bmp", default_palette);
}