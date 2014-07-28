#ifndef __ITEM_H__
#define __ITEM_H__


#include "player.h"
#include "define.h"


typedef struct Shot{
	int graph;
	int x[SHOT];
	int y[SHOT];
	int sizeX, sizeY;
	int flag[SHOT];
	int direct[SHOT];
	int frame[SHOT];
	int space;
}Shot;


typedef struct Item{
	int itemflag[2];

	int mantgraph;
	int mantsetgraph;
	int mantusegraph;
	int mantflag;

	int gungraph;
	int gunsetgraph;
	int gunshotgraph;
	int gunshotX[2], gunshotY[2];
	int gunflag;
	int gunshotflag[2];
	int shotgo[2];
}Item;


typedef struct Razer{
	int cX, cY, cFlag;
	double cR;
	int rX, rY, rFlag;
	int rDirect;
	int rRX, rRY;
	int rSpace;
}Razer;


void item_initialize();
void item_shot_initialize();
void item_razer_initialize();

void item_finalize();
void item_shot_finalize();
void item_razer_finalize();

void item1(Player*);
void item_shot(Player*);
void item_shot_update(Player*);
void item_shot_draw();

void item2(Player*);
void item_razer(Player*);
void item_razer_update(Player*);
void item_razer_draw();


#endif