#include "DxLib.h"
#include "key.h"
#include "stage.h"
#include "player.h"
#include "enemy.h"
#include "map.h"
#include "item.h"


// �X�e�[�W�P�Ǘ���
void stage1(int* mode, int* stage){
	static int state = 1;
	static int* bgm = NULL;
	if(state == 1){
		stage1_initialize();
		state = 2;
		bgm = (int*)malloc(sizeof(int));
		*bgm = LoadSoundMem("�f��\\�h�b�g�G\\���̑�\\battle1.ogg");
	}else if(state == 2){
		stage1_now(&state);
		if(CheckSoundMem(*bgm) == 0){
			PlaySoundMem(*bgm, DX_PLAYTYPE_BACK);
		}
	}else if(state == 3){
		StopSoundMem(*bgm);
		stage1_finalize();
		free(bgm);
		state = 1;
		*mode = 0;
		*stage = 0;
	}

	if(key_get(KEY_INPUT_ESCAPE) == 1){
		state = 3;
	}
}


// �X�e�[�W�P������
void stage1_initialize(){
	player_initialize();
	enemy1_initialize();
	map1_initialize();
	item_initialize();
}


// �X�e�[�W�P�I��
void stage1_finalize(){
	player_finalize();
	enemy1_finalize();
	item_finalize();
	map1_finalize();
}


// �X�e�[�W�P�v���C��
void stage1_now(int* state){
	player_update(state);
	enemy1_update(state);
	map1_draw();
	player_draw();
	enemy1_draw();
	player_se();
	enemy_se();
}
