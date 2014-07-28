#ifndef __ENEMY_H__
#define __ENEMY_H__


#include "player.h"
#include "define.h"


typedef struct EnemyObj{
	int graph[16];
	double x, y;
	int hp;
	int sizeX, sizeY;
	int direct;
	int drawType;
}EnemyObj;


typedef struct Enemy1{
	int side;
	int mode;
	int nomal;
	int drawCount;
	int se[6];
	int seType;
}Enemy1;


typedef struct Enemy1_At1{
	int b1Graph[6];
	double b1X;
	double b1Y;
	double b1XAim;
	double b1YAim;
	int b1sizeX;
	int b1sizeY;
	int b1Flag;
	int b1Type;
	int b2Graph;
	double b2X[E1_A1SHOT];
	double b2Y[E1_A1SHOT];
	int b2sizeX;
	int b2sizeY;
	int b2Flag[E1_A1SHOT];
	int next;
}E1_A1;


typedef struct Enemy1_At2{
	int graph[2];
	double shot1X, shot1Y;
	int sizeX, sizeY;
	int shot1Flag;
}E1_A2;


typedef struct Enemy1_At3{
	int pieceGraph;
	double pieceX[5];
	double pieceY[5];
	int pieceSizeX;
	int pieceSizeY;
	int pieceFlag[5];
	int pieceFrame;
	int s;
	int next;
}E1_A3;


void enemy1_initialize();
void enemy1_at1_initialize();
void enemy1_at2_initialize();
void enemy1_at3_initialize();
void enemy1_finalize();
void enemy1_at1_finalize();
void enemy1_at2_finalize();
void enemy1_at3_finalize();
void enemy1_update(int*);
void enemy1_nomal();
void enemy1_at1(int*);
void enemy1_at1_update1(int*);
void enemy1_at1_update2();
void enemy1_at1_draw();
void enemy1_at2(int*);
void enemy1_at2_update(int*);
void enemy1_at2_draw();
void enemy1_at3(int*);
void enemy1_at3_update1(int*);
void enemy1_at3_update2();
void enemy1_at3_draw();
void enemy1_draw();
void set_player(const Player*);
void enemy_se();
void enemy1_end_update(int*);

#endif