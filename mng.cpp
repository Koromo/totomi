#include "DxLib.h"
#include "key.h"
#include "title.h"
#include "stage.h"
#include "puzzle15.h"
using namespace puzzle15;


// �����Ǘ����imode�̒l�𑀍�j
void mng(int* mode){
	// �^�C�g��
	if(*mode == 1){
		// GAMESTART�i�G�I���j
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
		// �Q�[���I��
		*mode = -1;
	}else {
		*mode = title();
	}
}