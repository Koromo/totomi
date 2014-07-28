//使用例

//puzzle15.hをインクルードし、Main関数のどこかに
//
//using namecpace puzzle15;
//
//と記述する
//次に、filelistクラスを宣言し、
//
//////////////////////////////
//
//filelist list("フォルダ名");
//map Mainmap(4,4,list.getFileList(i));
//Execute15Puzzle(Mainmap);
//
//////////////////////////////
//とすれば、15パズルが実行される
//iは、フォルダ内の何番目のファイルかと言う意味なので、
//ここを乱数で生成すればランダムな画像で表示ができる

//Tipsとして
//例ではそのまま宣言しているが、
//filelist *list;
//map * mainmap;
//とし、15パズル実行直前に
////////////////////////////////////////////
//
//list = new map(4,4,list->getFileList(i));
//Mainmap = new filelist("フォルダ名");
//
//Execute15Puzzle(*Mainmap);
//
//delete list;
//delete Mainmap;
//
////////////////////////////////////////////
//
//とすると、メモリの節約を図ることが出来る。
//

//#include "puzzle15.h"
/*
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPervInstance, LPSTR lpCmdLine, int nCmdShow){
#ifdef _DEBUG
	SetOutApplicationLogValidFlag( FALSE ) ;
#endif

	SetLeftUpColorIsTransColorFlag( TRUE ) ;
	SetAlwaysRunFlag( TRUE );
	SetWaitVSyncFlag( TRUE );
	ChangeWindowMode( TRUE );
	if(DxLib_Init() == -1){
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);

	using namespace puzzle15;

	string _test;

	filelist test("picture");
	srand((unsigned)time(NULL));

	//listで見つかったファイル数から1つランダムで選択
	int f = rand() % test.num;

	map MAP(4,4,test.getFileList(f));
	Execute15Puzzle(MAP);

	return 0;

}*/