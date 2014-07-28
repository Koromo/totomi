#include "DxLib.h"


static unsigned int keyGet[256];


void key_update(){
	char keyInput[256];
	
	GetHitKeyStateAll(keyInput);
	for(int i=0; i<256; i++){
		if(keyInput[i] == 1){
			keyGet[i] ++;
		}else {
			keyGet[i] = 0;
		}
	}
}


int key_get(int keyCode){
	return keyGet[keyCode];
}