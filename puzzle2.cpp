//�g�p��

//puzzle15.h���C���N���[�h���AMain�֐��̂ǂ�����
//
//using namecpace puzzle15;
//
//�ƋL�q����
//���ɁAfilelist�N���X��錾���A
//
//////////////////////////////
//
//filelist list("�t�H���_��");
//map Mainmap(4,4,list.getFileList(i));
//Execute15Puzzle(Mainmap);
//
//////////////////////////////
//�Ƃ���΁A15�p�Y�������s�����
//i�́A�t�H���_���̉��Ԗڂ̃t�@�C�����ƌ����Ӗ��Ȃ̂ŁA
//�����𗐐��Ő�������΃����_���ȉ摜�ŕ\�����ł���

//Tips�Ƃ���
//��ł͂��̂܂ܐ錾���Ă��邪�A
//filelist *list;
//map * mainmap;
//�Ƃ��A15�p�Y�����s���O��
////////////////////////////////////////////
//
//list = new map(4,4,list->getFileList(i));
//Mainmap = new filelist("�t�H���_��");
//
//Execute15Puzzle(*Mainmap);
//
//delete list;
//delete Mainmap;
//
////////////////////////////////////////////
//
//�Ƃ���ƁA�������̐ߖ��}�邱�Ƃ��o����B
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

	//list�Ō��������t�@�C��������1�����_���őI��
	int f = rand() % test.num;

	map MAP(4,4,test.getFileList(f));
	Execute15Puzzle(MAP);

	return 0;

}*/