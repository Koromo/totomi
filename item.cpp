#include "DxLib.h"
#include "key.h"
#include "item.h"
#include "map.h"
#include "hit.h"


static Shot* shot = NULL;
static Razer* razer = NULL;
extern int key2;
extern int razerkey;

// 初期化
void item_initialize(){
	item_shot_initialize();
	item_razer_initialize();
}


// ショット初期化
void item_shot_initialize(){
	// オブジェクト生成
	shot = new Shot;

	shot->graph = LoadGraph("素材\\ドット絵\\エフェクト関係\\ショット.png");
	GetGraphSize(shot->graph, &shot->sizeX, &shot->sizeY);
	for(int i=0; i<SHOT; i++){
		shot->x[i] = -100;
		shot->y[i] = -100;
		shot->flag[i] = 0;
		shot->direct[i] = 0;
		shot->frame[i] = 0;
	}
	shot->space = 0;
}


// レーザー初期化
void item_razer_initialize(){
	// オブジェクト生成
	razer = new Razer;

	razer->cX = -100;
	razer->cY = -100;
	razer->cFlag = 0;
	razer->cR = 0;
	razer->rX = -100;
	razer->rY = -100;
	razer->rFlag = 0;
	razer->rDirect = 0;
	razer->rRX = 0;
	razer->rRY = 0;
	razer->rSpace = 0;
}


// 終了時
void item_finalize(){
	item_shot_finalize();
	item_razer_finalize();
}


// 終了時　メモリ開放
void item_shot_finalize(){
	delete shot;
}


// 終了時　メモリ開放
void item_razer_finalize(){
	delete razer;
}


// アイテム１
void item1(Player* player){
	item_shot(player);
}


// ショット
void item_shot(Player* player){
	item_shot_update(player);
	item_shot_draw();
}


// ショットアップデート
void item_shot_update(Player* player){
	if(key_get(KEY_INPUT_Z) > 0 && key2 == 0 && player->jumpFlag == 0 && player->hit == 0){
		for(int i=0; i<SHOT; i++){
			if(shot->flag[i] == 0 && shot->space == 0){
				shot->x[i] = (int)player->x + player->sizeX / 2;
				shot->y[i] = (int)player->y + 23;
				shot->flag[i] = 1;
				player->direct == 1 ? shot->direct[i] = 1 : shot->direct[i] = 0;
				shot->frame[i] = 0;
				shot->space = 1;
				player->seType = 3;
				break;
			}
		}
	}

	if(shot->space != 0){
		shot->space ++;
		if(shot->space > 12){
			shot->space = 0;
		}
	}
	if(key_get(KEY_INPUT_Z) > 0 && key2 == 0){
		player->direct == 1 ? player->drawType = SHOT_RIGHT_1 : player->drawType = SHOT_LEFT_1;
	}

	for(int i=0; i<SHOT; i++){
		if(shot->flag[i] == 1){
			shot->frame[i] ++;
			if(shot->direct[i] == 1){
				shot->x[i] += 22;
				if(shot->frame[i] > 80){
					shot->flag[i] = 0;
				}
			}else {
				shot->x[i] -= 22;
				if(shot->frame[i] > 80){
					shot->flag[i] = 0;
				}
			}
			if(Enemy1At1Update(shot->x[i], shot->y[i], shot->sizeX, shot->sizeY) == HIT){
				shot->x[i] = -100;
				shot->y[i] = -100;
				shot->flag[i] = 0;
			}
			if(EnemyHit_Box(shot->x[i], shot->y[i], shot->sizeX, shot->sizeY) == 1){
				shot->x[i] = -100;
				shot->y[i] = -100;
				shot->flag[i] = 0;
			}
		}
	}
}


// ショット描画
void item_shot_draw(){
	for(int i=0;i<SHOT; i++){
		if(shot->flag[i] == 1){
			DrawGraph(shot->x[i], shot->y[i], shot->graph, TRUE);
		}
	}
}


// アイテム２
void item2(Player* player){
	item_razer(player);
}


// レーザー
void item_razer(Player* player){
	item_razer_update(player);
	item_razer_draw();
}


// レーザーアップデート
void item_razer_update(Player* player){
	if(key_get(KEY_INPUT_X) > 0 && player->hit == 0 && key_get(KEY_INPUT_Z) == 0 && player->jumpFlag == 0){
		if(razer->cFlag == 0){
			player->key1 = 1;
			razerkey = 1;
			if(player->direct == 1){
				razer->cX = (int)player->x + player->sizeX - 19;
				razer->rDirect = 1;
				player->drawType = RAZER_RIGHT_1;
			}else {
				razer->cX = (int)player->x + 18;
				razer->rDirect = 2;
				player->drawType = RAZER_LEFT_1;
			}
				razer->cY = (int)player->y + 34;
				razer->cR += 0.2;
			if(razer->cR > 12){
				razer->cFlag = 1;
				razer->rFlag = 1;
				razer->rSpace = 0;
				razer->rX = razer->cX;
				razer->rY = razer->cY;
				razer->rRX = 0;
				razer->rRY = 0;
				razerkey = 0;

			}
		}
	}else {
		razer->cR = 0;
		razer->cX = -100;
		key2 = 0;
		razerkey = 0;
	}

	if(razer->rFlag == 1){
		if(razer->rDirect == 1){
			razer->rX += 25;
			if(razer->rSpace < 15){
				player->drawType = RAZER_RIGHT_2;
				key2 = 1;
			}else {
				key2 = 0;
			}
		}else {
			razer->rX -= 25;
			if(razer->rSpace < 15){
				player->drawType = RAZER_LEFT_2;
				key2 = 1;
			}else {
				key2 = 0;
			}
		}
		razer->rSpace ++;
		if(razer->rRX < 150){
			razer->rRX += 30;
		}
		if(razer->rRY < 8){
			razer->rRY += 4;
		}
		if(razer->rSpace > 100){
			razer->cFlag = 0;
			razer->cR = 0;
			razer->rFlag = 0;
		}
		EnemyHit_Box(razer->rX, razer->rY, razer->rRX * 2, razer->rRY * 2, 2);
	}
}


// レーザー描画
void item_razer_draw(){
	if(razer->cFlag == 0){
		DrawCircle(razer->cX, razer->cY, (int)razer->cR, GetColor(0, 255, 255), TRUE);
	}

	if(razer->rFlag == 1){
		DrawOval(razer->rX, razer->rY, razer->rRX, razer->rRY, GetColor(0 , 200, 200), TRUE);
	}
}