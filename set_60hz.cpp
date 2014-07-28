#include "DxLib.h"


void set_60hz(){
	static int term;
	static int t;

	term = GetNowCount() - t;
	if(16-term > 0){
		Sleep(16-term);
	}

	t = GetNowCount();
}