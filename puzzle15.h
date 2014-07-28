#pragma once
#include<DxLib.h>
#include<math.h>
#include<Windows.h>
#include<time.h>
#include<string>
#include<string.h>
#include<fstream>
#include<iostream>
#include "key.h"

bool loop_KoRoMo = true;

namespace puzzle15{

	using namespace std;

#define SIZE 100
#define CREATE_Q_F 60

	const int WHITE = GetColor(255,255,255);
	const int RED	= GetColor(255,0,0);
	const int GREEN	= GetColor(0,255,0);
	const int BLUE	= GetColor(0,0,255);
	const int BLACK = GetColor(0,0,0);

	const char *NUM_STR[] = {
		{"�@"},{"�A"},{"�B"},
		{"�C"},{"�D"},{"�E"},
		{"�F"},{"�G"},{"�H"},
		{"�I"},{"�J"},{"�K"},
		{"�L"},{"�M"},{"�N"},
		{""},
	};
	
	
	const int KEY_CODE[4] = {
		KEY_INPUT_UP,KEY_INPUT_DOWN,KEY_INPUT_LEFT,KEY_INPUT_RIGHT
	};
	char buf[256];

	//////////////////////////////////////
	//�t�@�C�����X�g�N���X
	class filelist{

		string* list;
		string* fullpath;
		string dir;
		bool flag;
		int num;
	public:
		//�t�@�C�������Ԃ�
		int getNum(){
			if(this->flag == false)
				return 1;
			return num;
		}
		//�t�H���_����t�@�C����T���ă��X�g����
		bool findFileList(char* dir);
		
		//�擾�����t�@�C�����X�g���當����擾
		string getFileList(int num);
		//�擾�����t�@�C�����X�g�̃p�X�����܂߂Ď擾
		string getFileListDir(int );

		//�ǂݍ��܂�Ă��邩�̃t���O�`�F�b�J�[
		bool check();

		//�R���t�B�O�t�@�C�����烊�X�g����
		bool getFileList(string cfgfile, char* filepath);

		filelist(string cfg,char* filepath);

		filelist(char* path);

		~filelist();
	};

	//�����w��߂�ǂ�����y�ɂ������b�Z�[�W�{�b�N�X
	void EasyMessageBox(char *TITLE ,char *MESSAGE);
	int EasyMessageBox(char *TITLE ,char *MESSAGE, UINT TYPE);

	/////////////////////////////////////////
	//�}�b�v��`�N���X
	class map{
		int x;
		int y;
		int gr[16];
		bool grFlag;
		int data[SIZE][SIZE];
		int finish[SIZE][SIZE];

		void swap(int&,int&);
	public:
		int zeroPointX;
		int zeroPointY;
		
		void setMapPoint(int, int, int);

		void setMap(int, int);

		void setQuestion();
		int loadGraph(string filename);
		void DrawExcel();
		void DrawNumber();

		//mode
		//1~4=AUTO
		//1=UP 2=DOWN 3=RIGHT 4=LEFT

		//0=MANUAL
		bool movePanel(int);

		bool checkClearGame();

		void DEBUG();

	public:
		map();
		map(int,int);
		map(int,int,string);
	};

	int Execute15Puzzle(map&);
};




namespace puzzle15{

	using namespace std;

	//�t�H���_����t�@�C����T���ă��X�g����
	bool filelist::findFileList(char* dir){
		int i=0;

		WIN32_FIND_DATA FileData;
		HANDLE handle;
	
		string sdir = dir;
		string t = dir;
		sdir += "\\*";
		this->num = 0;
		this->dir = dir;

		handle = FindFirstFile(sdir.c_str(),&FileData);
		if(handle == INVALID_HANDLE_VALUE){
			CreateDirectory(dir,NULL);
			MessageBox(NULL,TEXT("�t�@�C���܂��̓t�H���_���������"),TEXT("���m�点"),MB_OK | MB_ICONINFORMATION);
			this->flag = false;
			return false;
		}

		//�t�@�C�����擾
		do{
			this->num++;
		}while(FindNextFile(handle,&FileData));

		FindClose(handle);

		if(num <= 2){
			this->flag = false;
			return false;
		}

		this->list = new string[num+1];
		this->fullpath = new string[num+1];

		handle = FindFirstFile(sdir.c_str(),&FileData);
		do{
			this->list[i] = FileData.cFileName;
			this->fullpath[i] = t + '\\';
			this->fullpath[i] += FileData.cFileName;
			i++;
			if(i > this->num)
				break;
		}while(FindNextFile(handle,&FileData));
		this->num -= 2;
		for(i=0;i<this->num;i++){
			this->list[i] = this->list[i+2];
			this->fullpath[i] = this->fullpath[i+2];
		}
		//��n��
		this->flag = true;
		return true;

	}

	//�擾�����t�@�C�����X�g���當����擾
	string filelist::getFileList(int num){
		if(num > this->num || this->flag == false){
			return "NULL";
		}
		return list[num];
	}

	//�f�B���N�g����
	string filelist::getFileListDir(int num){

		if(this->flag == false || num > this->num){
			return "NULL";
		}
		return this->fullpath[num];
	}

	//�ǂݍ��܂�Ă��邩�̃t���O�`�F�b�J�[
	bool filelist::check(){
		return this->flag;
	}

	//�R���t�B�O�t�@�C�����烊�X�g����
	bool filelist::getFileList(string cfgfile, char* filepath){
		string path = filepath + cfgfile;
		ifstream list(path);
		string tmp;
		char tbuf[16] = {0};
		char *newbuf;
		this->num = 0;

		int linecnt=0;
		int stringscnt = 0;
		int befstrings = 0;

		//�ǂݍ��݂Ɏ��s���Ă���Ȃ�t�@�C���𐶐����Ċ֐��I���
		if(list.fail()){
			list.close();
			ofstream _list(path);
			_list << "" ;
			_list.close();
			this->flag = false;
			return false;
		} else {
			//�s���擾
			while(tbuf[0] != EOF){
				tbuf[0] = list.get();
				//printfDx("%s",buf);
				//�������擾
				befstrings++;
				if(tbuf[0] == '\n' || tbuf[0] == EOF){
					//�������ő�l�X�V
					if(stringscnt < befstrings){
						stringscnt = befstrings;
					}
					befstrings = 0;
					linecnt ++;
				}
			}
			//���������Ɠ��삵�Ă���悤�Ɍ����Ă�line��0�Ȃ�I���
			//stringscnt�͉��s������������̂�1�ȉ�
			if(linecnt <= 0 || stringscnt <= 1){
				this->flag = false;
				return false;
			}
		}

		list.close();
		list.open(path);

		//�ő啶�������̔z����m��
		newbuf = new char[stringscnt+1];
		SecureZeroMemory(newbuf,sizeof(newbuf));

		//�ő�s�����̔z����m��
		//���ɓǂݍ��݂��s���Ă���ꍇ�͈�Udelete
		if(this->flag)
			delete [] this->list;
		this->list = new string[linecnt];

		//�s���ۑ�
		this->num = linecnt;

		for(int i=0;i<linecnt;i++){
			//�擾�����p�X��ۑ�
			list.getline(newbuf,stringscnt-1,'\n');
			this->list[i] = newbuf;
		}

		//��n��
		delete [] newbuf;
		this->flag = true;
		return true;
	}

	filelist::filelist(string cfg,char* filepath){
		//���񂷂Ƃ炭������
		this->flag = getFileList(cfg,filepath);
	}

	filelist::filelist(char* path){
		this->flag = findFileList(path);
	}

	filelist::~filelist(){
		//�ł��Ƃ炭������
		if(this->flag)
			delete [] this->list;
	}

	//�����w��߂�ǂ�����y�ɂ������b�Z�[�W�{�b�N�X
	void EasyMessageBox(char *TITLE ,char *MESSAGE){
		MessageBox(NULL,TEXT(MESSAGE),TEXT(TITLE),MB_OK | MB_ICONWARNING);
	}
	int EasyMessageBox(char *TITLE ,char *MESSAGE, UINT TYPE){
		return MessageBox(NULL,TEXT(MESSAGE),TEXT(TITLE),TYPE);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//*********************************************************************************************************************///
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	void map::swap(int &bar1,int &bar2){
		int temp;
		temp = bar1;
		bar1 = bar2;
		bar2 = temp;
	}

	void map::setMapPoint(int x, int y, int num){
		this->data[y][x] = num;
	}

	void map::setMap(int x, int y){
		int k=0;
		this->x = x;
		this->y = y;
		for(int i=0;i<x;i++){
			for(int j=0;j<y;j++){
				data[i][j] = k;
				finish[i][j] = k;
				k++;
			}
		}
		zeroPointX = x-1;
		zeroPointY = y-1;
		data[zeroPointY][zeroPointX] = -1;
	}

	void map::setQuestion(){
		movePanel(rand()%4 + 1);
	}
	int map::loadGraph(string filename){
		return LoadDivGraph(filename.c_str(),16,4,4,SIZE-5,SIZE-5,gr);
	}
	void map::DrawExcel(){
		int i,j;
		if(grFlag == true)
			return;
		for(i=0;i<y;i++){
			for(j=0;j<y;j++){
				if(data[i][j] != -1){
					DrawBox(121+(j*SIZE),41+(i*SIZE),121+(j*SIZE)+SIZE+1,41+(i*SIZE)+SIZE+1,WHITE,TRUE);
				}
				DrawBox(121+(j*SIZE),41+(i*SIZE),121+(j*SIZE)+SIZE+1,41+(i*SIZE)+SIZE+1,BLACK,FALSE);
			}
		}
		i = 121+(zeroPointX)*SIZE + SIZE / 4;
		j = 41+(zeroPointY)*SIZE + SIZE / 4;
		//DrawBox(i,j,i + SIZE/2, j + SIZE/2 ,RED,TRUE);
	}

	void map::DrawNumber(){
		SetFontSize(SIZE-5);
		ChangeFontType(DX_FONTTYPE_ANTIALIASING);
		if(!buf[KEY_INPUT_LCONTROL]){
			for(int i=0;i<y;i++){
				for(int j=0;j<x;j++){
					if( data[i][j] != -1){
						if(this->grFlag == false){
							DrawFormatString(121+(j*SIZE),41+(i*SIZE),BLACK,"%s",NUM_STR[data[i][j]]);
						} else if(data[i][j] != -1){
							DrawGraph(121+(j*SIZE),41+(i*SIZE),gr[data[i][j]],false);
						}
					}
				}
			}
		} else {
			for(int i=0;i<y;i++){
				for(int j=0;j<x;j++){
					if( finish[i][j] != -1){
						if(this->grFlag == false){
							DrawFormatString(121+(j*SIZE),41+(i*SIZE),BLACK,"%s",NUM_STR[finish[i][j]]);
						} else if(finish[i][j] != 16){
							DrawGraph(121+(j*SIZE),41+(i*SIZE),gr[finish[i][j]],false);
						}
					}
				}
			}
		}
		ChangeFontType(-1);
		SetFontSize(16);
	}

	//mode
	//1~4=AUTO
	//1=UP 2=DOWN 3=RIGHT 4=LEFT

	//0=MANUAL
	bool map::movePanel(int key=0){

		static int frame=0;
		static int beframe=0;
		static bool button=false;

		bool flag=false;
		if(button == false || key != 0){
			if((key == 1 || buf[KEY_INPUT_DOWN]) && zeroPointY > 0 ){
				swap(data[zeroPointY][zeroPointX],data[zeroPointY-1][zeroPointX]);
				zeroPointY--;
				flag = true;
				beframe = frame;
				button=true;
			} else 
				if((key == 2 || buf[KEY_INPUT_UP]) && zeroPointY < y-1){
					swap(data[zeroPointY][zeroPointX],data[zeroPointY+1][zeroPointX]);
					zeroPointY++;
					flag = true;
					beframe = frame;
					button=true;
				} else 
					if((key == 3 || buf[KEY_INPUT_RIGHT]) && zeroPointX > 0 ){
						swap(data[zeroPointY][zeroPointX],data[zeroPointY][zeroPointX-1]);
						zeroPointX--;
						flag = true;
						beframe = frame;
						button=true;
					} else
						if((key == 4 || buf[KEY_INPUT_LEFT]) && zeroPointX < x-1){
							swap(data[zeroPointY][zeroPointX],data[zeroPointY][zeroPointX+1]);
							zeroPointX++;
							flag = true;
							beframe = frame;
							button=true;
						} 
		} else if( ( !buf[KEY_INPUT_UP] && !buf[KEY_INPUT_DOWN] && !buf[KEY_INPUT_LEFT] && !buf[KEY_INPUT_RIGHT] )&& button && key == 0){
			beframe = 0;
			button = false;
		}
		frame++;
		return flag;
	}

	bool map::checkClearGame(){

		for(int i=0;i<y;i++){
			for(int j=0;j<x;j++){
				if(data[i][j] != finish[i][j] && data[i][j] != -1)
					return false;
			}
		}
		DrawGraph(121+(3*SIZE),41+(3*SIZE),gr[15],false);
		ScreenFlip();
		return true;
	}

	void map::DEBUG(){
		clsDx();
		for(int i=0;i<y;i++){
			for(int j=0;j<x;j++){
				printfDx("[%d:%d]",data[i][j],finish[i][j]);
				if(buf[KEY_INPUT_RETURN])
					data[i][j] = finish[i][j];
			}
			printfDx("\n");
		}
		printfDx("%d,%d\n",zeroPointX,zeroPointY);
		printfDx("gr:%d",this->grFlag);
	}

	map::map(){
		srand((unsigned)time(NULL));
		this->grFlag = false;
		setMap(4,4);
	}

	map::map(int x, int y){
		srand((unsigned)time(NULL));
		this->grFlag = false;
		setMap(x,y);
	}
	map::map(int x, int y, string filename){
		srand((unsigned)time(NULL));
		grFlag = (loadGraph(filename) != -1);
		setMap(x,y);
	}

	int Execute15Puzzle(map& MAP){
		int dir = 0;
		int i=0,j=0;

		unsigned int cnt=0;
		double sec=0;
		int frame=0;

		int ntime=0;
		int otime=0;
		int rtime[120] = {0};

		double vSync = 0;

		const int backc = GetColor(181,230,29);
		const int panelc = GetColor(239,228,176);

		bool Gameflag = false;

		int grhandle[12] = {0};

		char *grList[12] = {
			{"stage.png"},
		};

		string chStr="";
		char strbuf[256] = {0};

		for(i=0;i<12;i++){
			grhandle[i] = LoadGraph(grList[i]);
		}

		ntime = GetNowCount();
		do{
			//���͏���
			///////////////////////////////////////
			if(!Gameflag){
				if(i < CREATE_Q_F){

					for(j=0;j<120;j++){
						MAP.setQuestion();
					}
					i++;
					if(i >= CREATE_Q_F){
						Gameflag = true;
						MAP.setMapPoint(MAP.zeroPointX,MAP.zeroPointY,-1);
					}
				} 
			} else {
				if(MAP.checkClearGame()){
#pragma warning (push)					
#pragma warning(disable:4996)
					sprintf(strbuf,"���߂łƂ��������܂��B�Q�[���ɏ������܂����B\n�N���A�^�C��:%2.1f�b\n�萔:%d",sec/10,cnt);
#pragma warning(pop)
					MessageBox(NULL,strbuf,TEXT("���m�点"),MB_OK | MB_ICONINFORMATION);

					if(EasyMessageBox("���m�点","������x�V�т܂���",MB_YESNO | MB_ICONINFORMATION) == IDYES){
						MAP.setMap(4,4);
						i = 0;
						frame = 0;
						cnt = 0;
						sec = 0.0;
						Gameflag = false;
						srand((unsigned)time(NULL));
					} else {
						break;
					}

				}
				GetHitKeyStateAll( buf ) ;
				if(!buf[KEY_INPUT_LCONTROL])
					cnt += MAP.movePanel();


#ifdef _DEBUG
				MAP.DEBUG();
#endif

			}
			/////////////////////////////////////////

			//�`��
			///////////////////////////////////////
			ClearDrawScreen();
			if(grhandle[0] != -1){
				DrawGraph(0,0,grhandle[0],FALSE);
			} else {
				DrawBox(0,0,640,480,backc,TRUE);
				DrawBox(80,0,560,480,panelc,TRUE);
			}
			MAP.DrawExcel();
			MAP.DrawNumber();
			if(Gameflag == false){
				DrawString((frame*6)%790-150,0,"�� �� �� �� �� ��",BLACK);
			} else {
				DrawFormatString(150,0,BLACK,"���݂̎萔�F%3d    �o�ߎ���:%5.1f�b",cnt,sec/10);
				DrawString(120,450,"��Ctrl�L�[�œ����\��",BLACK);
			}
			ScreenFlip();
			///////////////////////////////////////


			//�㏈��
			////////////////////////////////////////
			otime = GetNowCount();
			if(!(i < CREATE_Q_F) && (otime - ntime) >= 100 ){
				sec += (double)(otime - ntime) / 100;
				ntime = GetNowCount();
			}
			if(!Gameflag)
				sec = 0.0;

			if(ProcessMessage() == -1){
				return -1;
			}
			frame++;
			//////////////////////////////////////////


			key_update();
			if(key_get(KEY_INPUT_ESCAPE) == 1){
				loop_KoRoMo = false;
			}

		}while(loop_KoRoMo);//!CheckHitKey(KEY_INPUT_ESCAPE));
		loop_KoRoMo = true;
		return 0;

	}
	
};
