#include "DxLib.h"
#include "key.h"
#include "player.h"
#include "item.h"
#include "map.h"
#include "enemy.h"


static Player* player = NULL;
static double vx;
int key2;
int razerkey;

// 初期化
void player_initialize(){
	// オブジェクト生成
	player = (Player*)malloc(sizeof(Player));

	player->graph[STAND_RIGHT] = LoadGraph("素材\\ドット絵\\ととみ\\立ちモーション\\tatiright.png");
	player->graph[STAND_LEFT] = LoadGraph("素材\\ドット絵\\ととみ\\立ちモーション\\tatileft.png");
	player->graph[DASH_RIGHT_1] = LoadGraph("素材\\ドット絵\\ととみ\\走りモーション\\run1.png");		
	player->graph[DASH_RIGHT_2] = LoadGraph("素材\\ドット絵\\ととみ\\走りモーション\\run2.png");		
	player->graph[DASH_RIGHT_3] = LoadGraph("素材\\ドット絵\\ととみ\\走りモーション\\run3.png");		
	player->graph[DASH_RIGHT_4] = LoadGraph("素材\\ドット絵\\ととみ\\走りモーション\\run4.png");		
	player->graph[DASH_RIGHT_5] = LoadGraph("素材\\ドット絵\\ととみ\\走りモーション\\run5.png");		
	player->graph[DASH_RIGHT_6] = LoadGraph("素材\\ドット絵\\ととみ\\走りモーション\\run6.png");		
	player->graph[DASH_LEFT_1] = LoadGraph("素材\\ドット絵\\ととみ\\走りモーション\\run1left.png");		
	player->graph[DASH_LEFT_2] = LoadGraph("素材\\ドット絵\\ととみ\\走りモーション\\run2left.png");		
	player->graph[DASH_LEFT_3] = LoadGraph("素材\\ドット絵\\ととみ\\走りモーション\\run3left.png");
	player->graph[DASH_LEFT_4] = LoadGraph("素材\\ドット絵\\ととみ\\走りモーション\\run4left.png");
	player->graph[DASH_LEFT_5] = LoadGraph("素材\\ドット絵\\ととみ\\走りモーション\\run5left.png");
	player->graph[DASH_LEFT_6] = LoadGraph("素材\\ドット絵\\ととみ\\走りモーション\\run6left.png");
	player->graph[JUMP_RIGHT_1] = LoadGraph("素材\\ドット絵\\ととみ\\ジャンプモーション\\jump1.png");
	player->graph[JUMP_RIGHT_2] = LoadGraph("素材\\ドット絵\\ととみ\\ジャンプモーション\\jump2.png");
	player->graph[JUMP_LEFT_1] = LoadGraph("素材\\ドット絵\\ととみ\\ジャンプモーション\\jump3.png");
	player->graph[JUMP_LEFT_2] = LoadGraph("素材\\ドット絵\\ととみ\\ジャンプモーション\\jump4.png");
	player->graph[SHOT_RIGHT_1] = LoadGraph("素材\\ドット絵\\ととみ\\ショットモーション\\normalshot1.png");
	player->graph[SHOT_RIGHT_2] = LoadGraph("素材\\ドット絵\\ととみ\\ショットモーション\\normalshot2.png");
	player->graph[SHOT_LEFT_1] = LoadGraph("素材\\ドット絵\\ととみ\\ショットモーション\\normalshot3.png");
	player->graph[SHOT_LEFT_2] = LoadGraph("素材\\ドット絵\\ととみ\\ショットモーション\\normalshot4.png");
	player->graph[RAZER_RIGHT_1] = LoadGraph("素材\\ドット絵\\ととみ\\ショットモーション\\chargeshot1.png");		
	player->graph[RAZER_RIGHT_2] = LoadGraph("素材\\ドット絵\\ととみ\\ショットモーション\\chargeshot2.png");		
	player->graph[RAZER_RIGHT_3] = LoadGraph("素材\\ドット絵\\ととみ\\ショットモーション\\chargeshot3.png");		
	player->graph[RAZER_LEFT_1] = LoadGraph("素材\\ドット絵\\ととみ\\ショットモーション\\chargeshot4.png");		
	player->graph[RAZER_LEFT_2] = LoadGraph("素材\\ドット絵\\ととみ\\ショットモーション\\chargeshot5.png");		
	player->graph[RAZER_LEFT_3] = LoadGraph("素材\\ドット絵\\ととみ\\ショットモーション\\chargeshot6.png");	
	player->graph[DAMEGE_RIGHT_1] = LoadGraph("素材\\ドット絵\\ととみ\\喰らいモーション\\kurairight.png");		
	player->graph[DAMEGE_LEFT_1] = LoadGraph("素材\\ドット絵\\ととみ\\喰らいモーション\\kuraileft.png");	
	player->graph[LAST_RIGHT_1] = LoadGraph("素材\\ドット絵\\ととみ\\喰らいモーション\\taore1.png");
	player->graph[LAST_RIGHT_2] = LoadGraph("素材\\ドット絵\\ととみ\\喰らいモーション\\taore2.png");
	player->graph[LAST_LEFT_1] = LoadGraph("素材\\ドット絵\\ととみ\\喰らいモーション\\taore1left.png");
	player->graph[LAST_LEFT_2] = LoadGraph("素材\\ドット絵\\ととみ\\喰らいモーション\\taore2left.png");

	player->se[0] = LoadSoundMem("素材\\SE oggファイル\\ととみ用\\ジャンプ.ogg");
	player->se[1] = LoadSoundMem("素材\\SE oggファイル\\ととみ用\\チャージショット.ogg");
	player->se[2] = LoadSoundMem("素材\\SE oggファイル\\ととみ用\\ノーマルショット.ogg");
	player->se[3] = LoadSoundMem("素材\\SE oggファイル\\ととみ用\\喰らい(ととみ).ogg");
	player->se[4] = LoadSoundMem("素材\\SE oggファイル\\ととみ用\\走り.ogg");
	player->seType = 0;
	player->direct = 1;
	player->walkCount = 0;
	GetGraphSize(player->graph[0], &player->sizeX, &player->sizeY);
	player->x = 60;
	player->y = 150;
	player->hp = 3;
	player->jumpFlag = 1;
	player->jump2Flag = 0;
	player->drawType = STAND_RIGHT;
	player->hit = 0;
	player->hitFlag = 0;
	player->key1 = 0;
	player->ax = 0;
}


// 終了時 メモリ開放
void player_finalize(){
	 free(player);
}


// メインアップデート　
void player_update(int* state){
	player->seType = 0;
	if(player->hp != 0){
		if(player->key1 == 0 && razerkey == 0){
			player_baseAction();
		}
		item1(player);
		item2(player);
		if(player->hit == 1){
			DamegeAction();
			player->key1 = 1;
		}
		if(player->hitFlag == 1){
			static int count;
			count ++;
			if(count > 90){
				player->hitFlag = 0;
				count = 0;
			}
		}
	}

	if(player->jumpFlag == 1){
		player->y -= player->ax;
		player->ax --;
		if(player->direct == 1 && player->hp != 0){
			player->ax > 0 ? player->drawType = JUMP_RIGHT_1 : player->drawType = JUMP_RIGHT_2;
			if(player->hit == 1){
				player->drawType = DAMEGE_RIGHT_1;
			}
		}else if(player->direct == 2 && player->hp != 0){
			player->ax > 0 ? player->drawType = JUMP_LEFT_1 : player->drawType = JUMP_LEFT_2;
			if(player->hit == 1){
				player->drawType = DAMEGE_LEFT_1;
			}
		}
	}


	area_updateX(player);
	area_updateY(player);

	if(ground_update(player) == 1){
		player->jumpFlag = 0;
		player->jump2Flag = 0;
		player->ax = 0;
		player->hit = 0;
		player->key1 = 0;
		if(player->hp == 0){
			player_end_update(state);
		}
	}else {
		player->jumpFlag = 1;
	}


	set_player(player);
}

void player_end_update(int* state){
	static int count;
	count ++;
	if(count > 240){
		*state = 3;
		count = 0;
	}else if(count > 100){
		if(player->direct == 1){
			player->drawType = LAST_RIGHT_2;
		}else {
			player->drawType = LAST_LEFT_2;
		}
	}else if(count > 20){
		if(player->direct == 1){
			player->drawType = LAST_RIGHT_1;
		}else {
			player->drawType = LAST_LEFT_1;
		}
	}
}

// 基本動作
void player_baseAction(){
	key2 = player_walk();
	player_jump();
	//player_kakkuu();
}


// 移動
int player_walk(){
	if(key_get(KEY_INPUT_RIGHT) > 0){
		player->direct = 1;
		player->x += 10;
		player->walkCount ++;
		if(player->walkCount > 7 * 6){
			player->walkCount = 0;
		}else if(player->walkCount > 7 * 5){
			player->drawType = DASH_RIGHT_6;
		}else if(player->walkCount > 7 * 4){
			player->drawType = DASH_RIGHT_5;
		}else if(player->walkCount > 7 * 3){
			player->drawType = DASH_RIGHT_4;
		}else if(player->walkCount > 7 * 2){
			player->drawType = DASH_RIGHT_3;
		}else if(player->walkCount > 7){
			player->drawType = DASH_RIGHT_2;
		}else {
			player->drawType = DASH_RIGHT_1;
		}
		return 1;
	}else if(key_get(KEY_INPUT_LEFT) > 0){
		player->direct = 2;
		player->x -= 10;
		player->walkCount ++;
		if(player->walkCount > 7 * 6){
			player->walkCount = 0;
		}else if(player->walkCount > 7 * 5){
			player->drawType = DASH_LEFT_6;
		}else if(player->walkCount > 7 * 4){
			player->drawType = DASH_LEFT_5;
		}else if(player->walkCount > 7 * 3){
			player->drawType = DASH_LEFT_4;
		}else if(player->walkCount > 7 * 2){
			player->drawType = DASH_LEFT_3;
		}else if(player->walkCount > 7){
			player->drawType = DASH_LEFT_2;
		}else {
			player->drawType = DASH_LEFT_1;
		}
		return 1;
	}else {
		player->walkCount = 0;
		player->direct == 1 ? player->drawType = STAND_RIGHT : player->drawType = STAND_LEFT;
		return 0;
	}
}


// ジャンプ、２段ジャンプ
void player_jump(){
	if(key_get(KEY_INPUT_UP) == 1 && player->jumpFlag == 0){
		player->jumpFlag = 1;
		player->ax = 18;
		player->seType = 1;
	}

	if(key_get(KEY_INPUT_UP) == 1 && player->ax < 10 && player->jump2Flag == 0){
		player->jump2Flag = 1;
		player->ax = 18;
		player->seType = 1;
	}
	if(player->ax < -20){
		player->ax = -20;
	}
}


// 滑空
/*
void player_kakkuu(){
	if(key_get(KEY_INPUT_Z) > 0){
		if(player->jumpFlag == 1 && player->ax <= 0){
			player->y += 2;
			player->ax = 0;
		}
	}
}*/



int PlayerHit_Box(double x, double y, double sx, double sy){
	if(player->hitFlag == 0){
		if((((player->x + 10 > x && player->x + 10 < x + sx) || (player->x + player->sizeX - 10 > x && player->x + player->sizeX - 10 < x + sx)) &&
			((player->y + 5 > y && player->y + 5 < y + sy) || (player->y + player->sizeY - 5 > y && player->y + player->sizeY - 5 < y + sy))) ||
			(((x > player->x + 10 && x < player->x + player->sizeX - 10) || (x + sx > player->x + 10 && x + sx < player->x + player->sizeX - 10)) &&
			((y > player->y + 5 && y < player->y + player->sizeY - 5) || (y + sy > player->y + 5 && y + sy < player->y + player->sizeY - 5)))){
				player->hit = 1;
				player->hp --;
				player->hitFlag = 1;
				player->ax = 10;
				vx = 7;
				player->seType = 4;
				return 1;
		}
	}
	return 0;
}




int PlayerHit_Circle(double x, double y, double r){
	if(player->hit == 0){
		if(((unsigned)(player->x + player->sizeX / 2 - x) < r + 30) && ((unsigned)(player->y + player->sizeY / 2 - y) < r + 30)){
				player->hit = 1;
				player->hp --;
				player->ax = 10;
				vx = 7;
				printfDx("a");
				return 1;
		}
	}
	return 0;
}


void DamegeAction(){
	if(player->direct == 1){
		player->x -= vx;
	}else {
		player->x += vx;
	}
	if(vx > 0){
		vx -= 0.2;
	}
	player->jumpFlag = 1;
}




// プレイヤー描画
void player_draw(){
	switch(player->drawType){
	case STAND_RIGHT:
		DrawGraph((int)player->x, (int)player->y, player->graph[STAND_RIGHT], TRUE);
		break;
	case STAND_LEFT:
		DrawGraph((int)player->x, (int)player->y, player->graph[STAND_LEFT], TRUE);
		break;
	case DASH_RIGHT_1:
		DrawGraph((int)player->x, (int)player->y, player->graph[DASH_RIGHT_1], TRUE);
		break;
	case DASH_RIGHT_2:
		DrawGraph((int)player->x, (int)player->y, player->graph[DASH_RIGHT_2], TRUE);
		break;
	case DASH_RIGHT_3:
		DrawGraph((int)player->x, (int)player->y, player->graph[DASH_RIGHT_3], TRUE);
		break;
	case DASH_RIGHT_4:
		DrawGraph((int)player->x, (int)player->y, player->graph[DASH_RIGHT_4], TRUE);
		break;
	case DASH_RIGHT_5: 
		DrawGraph((int)player->x, (int)player->y, player->graph[DASH_RIGHT_5], TRUE);
		break;
	case DASH_RIGHT_6:
		DrawGraph((int)player->x, (int)player->y, player->graph[DASH_RIGHT_6], TRUE);
		break;
	case DASH_LEFT_1:
		DrawGraph((int)player->x, (int)player->y, player->graph[DASH_LEFT_1], TRUE);
		break;
	case DASH_LEFT_2:
		DrawGraph((int)player->x, (int)player->y, player->graph[DASH_LEFT_2], TRUE);
		break;
	case DASH_LEFT_3:
		DrawGraph((int)player->x, (int)player->y, player->graph[DASH_LEFT_3], TRUE);
		break;
	case DASH_LEFT_4:
		DrawGraph((int)player->x, (int)player->y, player->graph[DASH_LEFT_4], TRUE);
		break;
	case DASH_LEFT_5:
		DrawGraph((int)player->x, (int)player->y, player->graph[DASH_LEFT_5], TRUE);
		break;
	case DASH_LEFT_6:
		DrawGraph((int)player->x, (int)player->y, player->graph[DASH_LEFT_6], TRUE);
		break;
	case JUMP_RIGHT_1:
		DrawGraph((int)player->x, (int)player->y, player->graph[JUMP_RIGHT_1], TRUE);
		break;
	case JUMP_RIGHT_2:
		DrawGraph((int)player->x, (int)player->y, player->graph[JUMP_RIGHT_2], TRUE);
		break;
	case JUMP_LEFT_1:
		DrawGraph((int)player->x, (int)player->y, player->graph[JUMP_LEFT_1], TRUE);
		break;
	case JUMP_LEFT_2:
		DrawGraph((int)player->x, (int)player->y, player->graph[JUMP_LEFT_2], TRUE);
		break;
	case SHOT_RIGHT_1:
		DrawGraph((int)player->x, (int)player->y, player->graph[SHOT_RIGHT_1], TRUE);
		break;
	case SHOT_RIGHT_2:
		DrawGraph((int)player->x, (int)player->y, player->graph[SHOT_RIGHT_2], TRUE);
		break;
	case SHOT_LEFT_1:
		DrawGraph((int)player->x, (int)player->y, player->graph[SHOT_LEFT_1], TRUE);
		break;
	case SHOT_LEFT_2:
		DrawGraph((int)player->x, (int)player->y, player->graph[SHOT_LEFT_2], TRUE);
		break;
	case RAZER_RIGHT_1:
		DrawGraph((int)player->x, (int)player->y, player->graph[RAZER_RIGHT_1], TRUE);
		break;
	case RAZER_RIGHT_2:
		DrawGraph((int)player->x, (int)player->y, player->graph[RAZER_RIGHT_2], TRUE);
		player->seType = 2;
		break;
	case RAZER_RIGHT_3:
		DrawGraph((int)player->x, (int)player->y, player->graph[RAZER_RIGHT_3], TRUE);
		break;
	case RAZER_LEFT_1:
		DrawGraph((int)player->x, (int)player->y, player->graph[RAZER_LEFT_1], TRUE);
		break;
	case RAZER_LEFT_2:
		DrawGraph((int)player->x, (int)player->y, player->graph[RAZER_LEFT_2], TRUE);
		player->seType = 2;
		break;
	case RAZER_LEFT_3:
		DrawGraph((int)player->x, (int)player->y, player->graph[RAZER_LEFT_3], TRUE);
		break;
	case DAMEGE_RIGHT_1:
		DrawGraph((int)player->x, (int)player->y, player->graph[DAMEGE_RIGHT_1], TRUE);
		break;
	case DAMEGE_LEFT_1:
		DrawGraph((int)player->x, (int)player->y, player->graph[DAMEGE_LEFT_1], TRUE);
		break;
	case LAST_RIGHT_1:
		DrawGraph((int)player->x, (int)player->y, player->graph[LAST_RIGHT_1], TRUE);
		break;
	case LAST_RIGHT_2:
		DrawGraph((int)player->x, (int)player->y, player->graph[LAST_RIGHT_2], TRUE);
		break;
	case LAST_LEFT_1:
		DrawGraph((int)player->x, (int)player->y, player->graph[LAST_LEFT_1], TRUE);
		break;
	case LAST_LEFT_2:
		DrawGraph((int)player->x, (int)player->y, player->graph[LAST_LEFT_2], TRUE);
		break;
	default :
		break;
	}

	for(int i=0; i<player->hp; i++){
		DrawCircle(i * 40 + 60, 560, 15, GetColor(255, 100, 255), TRUE);
	}
}


void player_se(){
	switch(player->seType){
	case 1:
		PlaySoundMem(player->se[0], DX_PLAYTYPE_BACK);
		break;
	case 2:
		PlaySoundMem(player->se[1], DX_PLAYTYPE_BACK);
		break;
	case 3:
		PlaySoundMem(player->se[2], DX_PLAYTYPE_BACK);
		break;
	case 4:
		PlaySoundMem(player->se[3], DX_PLAYTYPE_BACK);
		break;
	case 5:
		PlaySoundMem(player->se[4], DX_PLAYTYPE_BACK);
		break;
	default:
		break;
	}
}
