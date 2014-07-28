#ifndef __MAP_H__
#define __MAP_H__


#include "player.h"
#include "item.h"
#include "enemy.h"


void map1_initialize();
void map1_finalize();
void map1_draw();

void area_updateX(Player* player);
void area_updateY(Player* player);
int ground_update(const Player* player);

HitJ Enemy1At1Update(double x, double y, int sx, int sy);

HitJ ShotAreaUpdate(Item* shot);
HitJ RazerAreaUpdate(Razer* razer);
#endif