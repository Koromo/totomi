#include "DxLib.h"
#include "key.h"
#include "define.h"


// タイトル画面
int title(){
	static int choice = 1;
	static int strX[TITLE_MODE_NUM] = {{350}};
	static int titleGraph = LoadGraph("素材\\ドット絵\\その他\\アクションミニゲーム表紙.jpg");
	
	if(key_get(KEY_INPUT_UP) == 1){
		choice --;
	}else if(key_get(KEY_INPUT_DOWN) == 1){
		choice ++;
	}

	if(choice < 1){
		choice = TITLE_MODE_NUM;
	}else if(choice > TITLE_MODE_NUM){
		choice = 1;
	}
	
	for(int i=0; i<TITLE_MODE_NUM; i++){
		strX[i] = 340;
	}
	strX[choice - 1] = 300;
	
	DrawGraph(0, 0, titleGraph, TRUE);
	SetFontSize(20);
	DrawString(strX[0], 250, "GAMESTART", GetColor(255, 0 ,0));
	DrawString(strX[1], 270, "PUZZLE", GetColor(0, 255 ,0));
	DrawString(strX[2], 290, "EXIT  ", GetColor(0, 0, 255));
	//DrawCircle(285, 236 + 20 * choice, 10, GetColor(100, 100, 100), TRUE);

	if(key_get(KEY_INPUT_Z) == 1){
		return choice;
		choice = 1;
	}else {
		return 0;
	}
}


// 敵選択画面
int stage_choice(){
	static int choice = 1;
	static int mode[GAME_MODE_NUM] = {{220}};

	if(key_get(KEY_INPUT_LEFT) == 1){
		choice --;
	}else if(key_get(KEY_INPUT_RIGHT) == 1){
		choice ++;
	}

	if(choice < 1){
		choice = GAME_MODE_NUM;
	}else if(choice > GAME_MODE_NUM){
		choice = 1;
	}

	for(int i=0; i<GAME_MODE_NUM; i++){
		mode[i] = 220;
	}
	mode[choice - 1] = 210;

	DrawString(300, mode[0], "1", GetColor(255, 0 ,0));
	DrawString(320, mode[1], "2", GetColor(0, 255, 0));
	DrawString(340, mode[2], "3", GetColor(0, 0, 255));

	if(key_get(KEY_INPUT_RETURN) == 1){
		return choice;
		choice = 0;
	}else {
		return 0;
	}
}