#ifndef __PLAYER_H__
#define __PLAYER_H__


#include "enum.h"


typedef struct Player{
	int graph[34];
	int direct;
	int hp;
	double x, y;
	int sizeX, sizeY;
	int walkCount;
	int ax;
	int jumpFlag;
	int jump2Flag;
	int hit;
	int hitFlag;
	int seType;
	int se[5];
	int key1;
	PlayerDT drawType;
}Player;


void player_initialize();
void player_finalize();
void player_update(int*);
void player_baseAction();
int player_walk();
void player_jump();      
void player_kakkuu();
void DamegeAction();
void player_draw();
void player_se();
void player_end_update(int*);


#endif