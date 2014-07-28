#include "DxLib.h"
#include "key.h"
#include "title.h"
#include "stage.h"
#include "puzzle15.h"
using namespace puzzle15;


// 総合管理部（modeの値を操作）
void mng(int* mode){
	// タイトル
	if(*mode == 1){
		// GAMESTART（敵選択）
		static int stageChoice = 1;

		/*if(stageChoice == 1){
			stage1(mode, &stageChoice);
		}else {
			stageChoice = stage_choice();
		}*/

		//////////////////////////////////
		stage1(mode, &stageChoice);
		//////////////////////////////////

		/*if(stageChoice == 1 && *mode == 0){
			stageChoice = 0;
			*mode = 0;
		}*/
	}else if(*mode == 2){
		int f;
		filelist* list = new filelist("picture");

		srand(time(NULL));
		f = rand() % list->getNum() ;
		map* MAP = new map(4,4,list->getFileListDir(f));

		Execute15Puzzle(*MAP);
		
		delete list;
		delete MAP;
		*mode = 0;
	}else if(*mode == 3 || key_get(KEY_INPUT_ESCAPE) == 1){
		// ゲーム終了
		*mode = -1;
	}else {
		*mode = title();
	}
}