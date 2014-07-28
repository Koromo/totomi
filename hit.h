#ifndef __HIT_H__
#define __HIT_H__


int PlayerHit_Box(double x, double y, double sx, double sy);
int PlayerHit_Circle(double x, double y, double r);
int EnemyHit_Box(double x, double y, double sx, double sy, int damege = 1);
int EnemyHit_Circle(double x, double y, double r, int damege = 5);


#endif