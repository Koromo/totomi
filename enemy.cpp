#include "DxLib.h"
#include <math.h>
#include "define.h"
#include "enemy.h"
#include "map.h"
#include "hit.h"
#include "key.h"


static EnemyObj* enemyObj = NULL;
static Enemy1* enemy1 = NULL;
static E1_A1* e1_a1 = NULL;
static E1_A2* e1_a2 = NULL;
static E1_A3* e1_a3 = NULL;
static int modecnt;
static int atmode;

// �ʏ펞�A�㉺
static double t;
// �v���C���[�̍��W�擾
static double pX, pY;
static int psizeX, psizeY;


// ������
void enemy1_initialize(){
	// �I�u�W�F�N�g�`��
	enemyObj = (EnemyObj*)malloc(sizeof(EnemyObj));
	enemy1 = (Enemy1*)malloc(sizeof(Enemy1));

	enemyObj->graph[0] = LoadGraph("�f��\\�h�b�g�G\\�G(��)\\���V�ҋ@\\huyuu1.png");
	enemyObj->graph[1] = LoadGraph("�f��\\�h�b�g�G\\�G(��)\\���V�ҋ@\\huyuu3.png");
	enemyObj->graph[2] = LoadGraph("�f��\\�h�b�g�G\\�G(��)\\���V�ҋ@\\huyuu1left.png");
	enemyObj->graph[3] = LoadGraph("�f��\\�h�b�g�G\\�G(��)\\���V�ҋ@\\huyuu3left.png");
	enemyObj->graph[4] = LoadGraph("�f��\\�h�b�g�G\\�G(��)\\�����у��[�V����\\yokotobi1.png");
	enemyObj->graph[5] = LoadGraph("�f��\\�h�b�g�G\\�G(��)\\�����у��[�V����\\yokotobi2.png");
	enemyObj->graph[6] = LoadGraph("�f��\\�h�b�g�G\\�G(��)\\�����у��[�V����\\yokotobi3.png");
	enemyObj->graph[7] = LoadGraph("�f��\\�h�b�g�G\\�G(��)\\�����у��[�V����\\yokotobi1left.png");
	enemyObj->graph[8] = LoadGraph("�f��\\�h�b�g�G\\�G(��)\\�����у��[�V����\\yokotobi2left.png");
	enemyObj->graph[9] = LoadGraph("�f��\\�h�b�g�G\\�G(��)\\�����у��[�V����\\yokotobi3left.png");
	enemyObj->graph[10] = LoadGraph("�f��\\�h�b�g�G\\�G�t�F�N�g�֌W\\ryuukurai1.png");
	enemyObj->graph[11] = LoadGraph("�f��\\�h�b�g�G\\�G�t�F�N�g�֌W\\ryuukurai2.png");
	enemyObj->graph[12] = LoadGraph("�f��\\�h�b�g�G\\�G�t�F�N�g�֌W\\ryuukurai3.png");
	//enemyObj->graph[13] = LoadGraph("�f��\\�h�b�g�G\\�G�t�F�N�g�֌W\\ryuukurai1left.png");
	//enemyObj->graph[14] = LoadGraph("�f��\\�h�b�g�G\\�G�t�F�N�g�֌W\\ryuukurai2left.png");
	//enemyObj->graph[15] = LoadGraph("�f��\\�h�b�g�G\\�G�t�F�N�g�֌W\\ryuukurai3left.png");
	GetGraphSize(enemyObj->graph[0], &enemyObj->sizeX, &enemyObj->sizeY);
	enemy1->se[0] = LoadSoundMem("�f��\\SE ogg�t�@�C��\\���p\\�͂΂���.ogg");
	enemy1->se[1] = LoadSoundMem("�f��\\SE ogg�t�@�C��\\���p\\������.ogg");
	enemy1->se[2] = LoadSoundMem("�f��\\SE ogg�t�@�C��\\���p\\�΋�.ogg");
	enemy1->se[3] = LoadSoundMem("�f��\\SE ogg�t�@�C��\\���p\\����X�F�U��.ogg");
	enemy1->se[4] = LoadSoundMem("�f��\\SE ogg�t�@�C��\\���p\\����X�F�o����.ogg");
	enemy1->se[5] = LoadSoundMem("�f��\\SE ogg�t�@�C��\\���p\\��炢(��).ogg");
	enemyObj->x = 640;
	enemyObj->y = 160;
	enemyObj->direct = 2;
	enemy1->drawCount = 0;
	enemy1->side = 1;
	enemy1->mode = 0;
	enemy1->nomal = 1;
	enemyObj->hp = 100;
	enemy1->seType = 0;
	modecnt = 0;
	atmode = 0;
	enemy1_at1_initialize();
	enemy1_at2_initialize();
	enemy1_at3_initialize();
}


//
void enemy1_at1_initialize(){
	e1_a1 = (E1_A1*)malloc(sizeof(E1_A1));

	e1_a1->b1Graph[0] = LoadGraph("�f��\\�h�b�g�G\\�G(��)\\���̂w���[�V����\\kyuutaiX1.png");
	e1_a1->b1Graph[1] = LoadGraph("�f��\\�h�b�g�G\\�G(��)\\���̂w���[�V����\\kyuutaiX2.png");
	e1_a1->b1Graph[2] = LoadGraph("�f��\\�h�b�g�G\\�G(��)\\���̂w���[�V����\\kyuutaiX3.png");
	e1_a1->b1Graph[3] = LoadGraph("�f��\\�h�b�g�G\\�G(��)\\���̂w���[�V����\\kyuutaiX1left.png");
	e1_a1->b1Graph[4] = LoadGraph("�f��\\�h�b�g�G\\�G(��)\\���̂w���[�V����\\kyuutaiX2left.png");
	e1_a1->b1Graph[5] = LoadGraph("�f��\\�h�b�g�G\\�G(��)\\���̂w���[�V����\\kyuutaiX3left.png");
	GetGraphSize(e1_a1->b1Graph[0], &e1_a1->b1sizeX, &e1_a1->b1sizeY);
	e1_a1->b1X = -100;
	e1_a1->b1Y = -100;
	e1_a1->b1XAim = -100;
	e1_a1->b1YAim = -100;
	e1_a1->b1Flag = 0;
	e1_a1->b1X = -100;
	e1_a1->b1Type = 0;
	e1_a1->b2Graph = LoadGraph("�f��\\�h�b�g�G\\�G�t�F�N�g�֌W\\kyuutaikougeki.png");
	GetGraphSize(e1_a1->b2Graph, &e1_a1->b2sizeX, &e1_a1->b2sizeY);
	for(int i=0; i<E1_A1SHOT; i++){
		e1_a1->b2X[i] = -100;
		e1_a1->b2Y[i] = -100;
		e1_a1->b2Flag[i] = 0;
	}
	e1_a1->next = 0;
}


void enemy1_at2_initialize(){
	e1_a2 = (E1_A2*)malloc(sizeof(E1_A2));

	e1_a2->graph[0] = LoadGraph("�f��\\�h�b�g�G\\�G�t�F�N�g�֌W\\kakyuu.png");
	e1_a2->graph[1] = LoadGraph("�f��\\�h�b�g�G\\�G�t�F�N�g�֌W\\kakyuuleft.png");

	GetGraphSize(e1_a2->graph[0], &e1_a2->sizeX, &e1_a2->sizeY);
	e1_a2->shot1X = -100;
	e1_a2->shot1Y = -100;
	e1_a2->shot1Flag = 0;
}


void enemy1_at3_initialize(){
	e1_a3 = (E1_A3*)malloc(sizeof(E1_A3));

	e1_a3->pieceGraph = LoadGraph("�f��\\�h�b�g�G\\�G�t�F�N�g�֌W\\����j��.png");

	for(int i=0; i<5; i++){
		e1_a3->pieceX[i] = -100;
		e1_a3->pieceY[i] = -100;
		e1_a3->pieceFlag[i] = 0;
	}
	GetGraphSize(e1_a3->pieceGraph, &e1_a3->pieceSizeX, &e1_a3->pieceSizeY);
	//////// �T�C�Y�A�t���[��
	e1_a3->s = 1;
	e1_a3->next = 0;
}


// �I�����@�������J��
void enemy1_finalize(){
	free(enemyObj);
	free(enemy1);
	enemy1_at1_finalize();
	enemy1_at2_finalize();
	enemy1_at3_finalize();
}


void enemy1_at1_finalize(){
	free(e1_a1);
}


void enemy1_at2_finalize(){
	free(e1_a2);
}


void enemy1_at3_finalize(){
	free(e1_a3);
}


// �v���C���[�̍��W���擾
void set_player(const Player* player){
	pX = player->x;
	pY = player->y;
	psizeX = player->sizeX;
	psizeY = player->sizeY;
}


// ���C���A�b�v�f�[�g
void enemy1_update(int* state){
	if(atmode == 0){
		modecnt = 0;
		atmode = 4;
	}
	modecnt ++;
	if(modecnt == 90){
		atmode = GetRand(2) + 1;
	}
	if(enemyObj->hp > 0){
		enemy1->seType = 0;
		if(enemy1->nomal == 1){
			enemy1_nomal();
		}

		if(atmode == 1){
			enemy1_at1(&atmode);
		}else if(atmode == 2){
			enemy1_at2(&atmode);
		}else if(atmode == 3){
			enemy1_at3(&atmode);
		}
		PlayerHit_Box(enemyObj->x, enemyObj->y + 20, enemyObj->sizeX, enemyObj->sizeY - 20);
	}else {
		enemy1_end_update(state);

	}
}

void enemy1_end_update(int* state){
	static int count;
	count ++;
	if(count > 100){
		*state = 3;
		count = 0;
	}else if(count > 40){
		enemyObj->drawType = 13;
	}else if(count > 20){
		enemyObj->drawType = 12;
	}else {
		enemyObj->drawType = 11;
	}
}



int EnemyHit_Box(double x, double y, double sx, double sy, int damege){
		if(((x > enemyObj->x + 15 && x < enemyObj->x + enemyObj->sizeX - 15) || (x + sx > enemyObj->x + 15 && x + sx < enemyObj->x + enemyObj->sizeX - 15)) &&
		((y > enemyObj->y + 15 && y < enemyObj->y + enemyObj->sizeY - 15) || (y + sy > enemyObj->y + 15 && y + sy < enemyObj->y + enemyObj->sizeY - 15))){
			enemyObj->hp -= damege;
			enemy1->seType = 6;
			PlaySoundMem(enemy1->se[5], DX_PLAYTYPE_BACK);
			return 1;
		}
		return 0;
}



// �ʏ펞
void enemy1_nomal(){
	static int count;

	count ++;
	enemy1->drawCount ++;
	t = 2 * PI * count / 150;

	enemyObj->y += sin(t);
	if(enemy1->side == 1){
		if(enemy1->drawCount > 60){
			enemyObj->drawType = 2;
			enemy1->seType = 1;
			if(enemy1->drawCount > 90){
				enemy1->drawCount = 0;
			}
		}else {
			enemyObj->drawType = 1;
		}
	}else if(enemy1->side == 2){
		if(enemy1->drawCount > 60){
			enemyObj->drawType = 3;
			enemy1->seType = 1;
			if(enemy1->drawCount > 90){
				enemy1->drawCount = 0;
			}
		}else {
			enemyObj->drawType = 4;
		}
	}
}


// �U���p�^�[���P�i�e�e�j
void enemy1_at1(int* p){
	enemy1_at1_update1(p);
	enemy1_at1_update2();
	enemy1_at1_draw();
}


// �e�e�A�b�v�f�[�g
void enemy1_at1_update1(int* p){
	static double t1;
	static int count1;

	if(e1_a1->b1Flag == 0){
		e1_a1->b1X = enemyObj->x + enemyObj->sizeX / 2;
		e1_a1->b1Y = enemyObj->y + enemyObj->sizeY / 2;
		e1_a1->b1XAim = GetRand(400) + 200;//////////////�����̎擾�͈͒������邩��////////////////
		e1_a1->b1YAim = 120;
		t1 = atan2(e1_a1->b1YAim - e1_a1->b1Y, e1_a1->b1XAim - e1_a1->b1X);
		e1_a1->b1Flag = 1;
		enemy1->seType = 5;
		for(int i=0; i<E1_A1SHOT; i++){
			e1_a1->b2Flag[i] = 0;
		}
		e1_a1->next = 0;
		count1 = 0;
	}

	if(e1_a1->b1Flag == 1){
		count1 ++;
		if(count1 < 60){
			e1_a1->b1X += cos(t1) * 4;
			e1_a1->b1Y += sin(t1) * 4;
		}
		if(count1 > 150){          
			e1_a1->b1Flag = 0;
			*p = 0;
		}else if(count1 > 130){
			enemyObj->direct == 1 ? e1_a1->b1Type = 1 : e1_a1->b1Type = 4;
		}else if(count1 > 110){
			enemyObj->direct == 1 ? e1_a1->b1Type = 2 : e1_a1->b1Type = 5;
		}else if(count1 == 85){
			e1_a1->next = 1;
		}else if(count1 > 40){
			enemyObj->direct == 1 ? e1_a1->b1Type = 3 : e1_a1->b1Type = 6;
		}else if(count1 > 20){
			enemyObj->direct == 1 ? e1_a1->b1Type = 2 : e1_a1->b1Type = 5;
		}else {
			enemyObj->direct == 1 ? e1_a1->b1Type = 1 : e1_a1->b1Type = 4;
		}                          
		PlayerHit_Box(e1_a1->b1X + 10, e1_a1->b1Y + 10, e1_a1->b1sizeX - 10, e1_a1->b1sizeY - 10);
	}
}


void enemy1_at1_update2(){
	static int count2;
	static double t2;

	if(e1_a1->next == 1){
		for(int i=0; i<E1_A1SHOT; i++){
			if(e1_a1->b2Flag[i] == 0){
				e1_a1->b2X[i] = e1_a1->b1X + e1_a1->b1sizeX / 2;
				e1_a1->b2Y[i] = e1_a1->b1Y + e1_a1->b1sizeY / 2;
				e1_a1->b2Flag[i] = 1;
				enemy1->seType = 4;
				count2 = 0;
				e1_a1->next = 0;
			}
		}
	}


	for(int i=0; i<E1_A1SHOT; i++){
		count2 ++;
		if(e1_a1->b2Flag[i] == 1){
			t2 = 2 * PI * count2 / E1_A1SHOT;
			e1_a1->b2X[i] += cos(t2) * 8;
			e1_a1->b2Y[i] += sin(t2) * 8;
		}
		/////�����蔻�肢��ăt���O���ւ�����//////
		if(Enemy1At1Update(e1_a1->b2X[i] + 10, e1_a1->b2Y[i] + 10, e1_a1->b2sizeX - 10, e1_a1->b2sizeY - 10) == HIT){
			e1_a1->b2X[i]  = -100;
			e1_a1->b2Y[i]  = -100;
			e1_a1->b2Flag[i] = 0;
		}
		if(PlayerHit_Box(e1_a1->b2X[i] + 10, e1_a1->b2Y[i] + 10, e1_a1->b2sizeX - 10, e1_a1->b2sizeY - 10) == 1){
			e1_a1->b2X[i]  = -100;
			e1_a1->b2Y[i]  = -100;
			e1_a1->b2Flag[i] = 0;
		}
		//if(PlayerHit_Circle(e1_a1->b2X[i] + e1_a1->b2sizeX / 2, e1_a1->b2Y[i] + e1_a1->b2sizeY / 2, 5) == 1){
		//	e1_a1->b2Flag[i] = 0;
		//}
	}
}




// �e�e�P�A�e�e�Q�@�`��
void enemy1_at1_draw(){
	if(e1_a1->b1Flag == 1){
		switch(e1_a1->b1Type){
		case 1:
			DrawGraph((int)e1_a1->b1X, (int)e1_a1->b1Y, e1_a1->b1Graph[0], TRUE);
			break;
		case 2:
			DrawGraph((int)e1_a1->b1X, (int)e1_a1->b1Y, e1_a1->b1Graph[1], TRUE);
			break;
		case 3:
			DrawGraph((int)e1_a1->b1X, (int)e1_a1->b1Y, e1_a1->b1Graph[2], TRUE);
			break;
		case 4:
			DrawGraph((int)e1_a1->b1X, (int)e1_a1->b1Y, e1_a1->b1Graph[3], TRUE);
			break;
		case 5:
			DrawGraph((int)e1_a1->b1X, (int)e1_a1->b1Y, e1_a1->b1Graph[4], TRUE);
			break;
		case 6:
			DrawGraph((int)e1_a1->b1X, (int)e1_a1->b1Y, e1_a1->b1Graph[5], TRUE);
			break;
		default:
			break;
		}
	}
	for(int i=0; i<E1_A1SHOT; i++){
		if(e1_a1->b2Flag[i] == 1){
			DrawGraph((int)e1_a1->b2X[i], (int)e1_a1->b2Y[i], e1_a1->b2Graph, TRUE);
		}
	}
}


// �U���p�^�[���Q�i�t���A�j
void enemy1_at2(int* p){
	enemy1_at2_update(p);
	enemy1_at2_draw();
}


// �t���A�A�b�v�f�[�g
void enemy1_at2_update(int* p){
	static double t2;
	if(e1_a2->shot1Flag == 0){
		e1_a2->shot1X = enemyObj->x + 10;
		e1_a2->shot1Y = enemyObj->y + 30;
		t2 = atan2(pY + 10 - e1_a2->shot1Y, pX + 10 - e1_a2->shot1X);
		e1_a2->shot1Flag = 1;
		enemy1->seType = 3;
	}
	if(e1_a2->shot1Flag == 1){
		e1_a2->shot1X += cos(t2) * 7;
		e1_a2->shot1Y += sin(t2) * 7;
		//////////�����蔻��Ńt���O�ւ�����/////
		if(Enemy1At1Update(e1_a2->shot1X + 20, e1_a2->shot1Y + 20, e1_a2->sizeX - 20, e1_a2->sizeY - 20) == HIT){
			e1_a2->shot1Flag = 0;
			e1_a2->shot1X  = -100;
			e1_a2->shot1Y  = -100;
			*p = 0;
		}
		PlayerHit_Box(e1_a2->shot1X + 20, e1_a2->shot1Y + 20, e1_a2->sizeX - 20, e1_a2->sizeY - 20);
		//PlayerHit_Circle(e1_a2->shot1X + e1_a2->sizeX / 2, e1_a2->shot1Y + e1_a2->sizeY / 2, 10);
	}
}


// �t���A�`��
void enemy1_at2_draw(){
	if(e1_a2->shot1Flag == 1){
		if(enemy1->side == 1){
			DrawGraph((int)e1_a2->shot1X, (int)e1_a2->shot1Y, e1_a2->graph[0],TRUE);
		}else {
			DrawGraph((int)e1_a2->shot1X, (int)e1_a2->shot1Y, e1_a2->graph[1],TRUE);
		}
	}
}


// �U���p�^�[���R�i�ːi�j
void enemy1_at3(int* p){
	enemy1_at3_update1(p);
	enemy1_at3_update2();
	enemy1_at3_draw();
}


// �ːi�A�b�v�f�[�g
void enemy1_at3_update1(int* p){
	static int count;
	static int countat4;

	if(e1_a3->s == 1){
		if(enemy1->side == 1){
			if(enemyObj->x < 800){
				enemyObj->x += 2;
			}else {
				e1_a3->s = 2;
				enemy1->nomal = 0;
			}
		}else {
			if(enemyObj->x + enemyObj->sizeX > 0){
				enemyObj->x -= 2;
			}else {
				e1_a3->s = 2;
				enemy1->nomal = 0;
			}
		}
		count = 0;
	}

	if(e1_a3->s == 2){
		count ++;
		if(count < 120){
			if(enemyObj->y + enemyObj->sizeY / 2  + 20 > pY + psizeY / 2){
				enemyObj->y -= 3;
			}else if(enemyObj->y + enemyObj->sizeY / 2  + 20 < pY + psizeY / 2){
				enemyObj->y += 3;
			}
		}else {
			e1_a3->s = 3;
			enemy1->seType = 2;
		}
	}

	if(e1_a3->s == 3){
		if(enemy1->side == 1){
			if(enemyObj->x > 0 + 20){
				enemyObj->x -= 25;
				if(enemyObj->x < 30){
					enemyObj->drawType = 7;
				}else if(enemyObj->x < 200){
					enemyObj->drawType = 6;
				}else {
					enemyObj->drawType = 5;
				}
				
			}else {
				enemy1->side = 2;
				e1_a3->s = 4;
				countat4 = 0;
			}
		}else if(enemy1->side == 2){
			if(enemyObj->x + enemyObj->sizeX < 800 - 20){
				enemyObj->x += 25;
				if(enemyObj->x + enemyObj->sizeX > 770){
					enemyObj->drawType = 10;
				}else if(enemyObj->x + enemyObj->sizeX> 600){
					enemyObj->drawType = 9;
				}else {
					enemyObj->drawType = 8;
				}
			}else {
				enemy1->side = 1;
				e1_a3->s = 4;
				countat4 = 0;
			}
		}
	}

	if(e1_a3->s == 4){
		if(countat4 == 0){
			e1_a3->next = 1;
		}
		countat4 ++;
		if(countat4 > 80){
			enemy1->nomal = 1;
			if(enemyObj->y > 160){
				enemyObj->y --;
				if(enemyObj->y <= 160){
					e1_a3->s = 1;
					countat4 = 0;
					*p = 0;
				}
			}else if(enemyObj->y < 160){
				enemyObj->y ++;
				if(enemyObj->y >= 160){
					e1_a3->s = 1;
					countat4 = 0;
					*p = 0;
				}
			}else {
				e1_a3->s = 1;
				countat4 = 0;
				*p = 0;
			}
		}/*else {
			if(enemy1->side == 2){
				enemyObj->drawType = 7;
				/////////////
			}*/
		
	}
}


// ���I�A�b�v�f�[�g
void enemy1_at3_update2(){
	static double ax;

	if(e1_a3->next == 1){
		for(int i=0; i<5; i++){
			if(e1_a3->pieceFlag[i] == 0){
				e1_a3->pieceX[i] = GetRand(700) + 50;
				e1_a3->pieceY[i] = 20;
				e1_a3->pieceFlag[i] = 1;
				ax = 0;
				e1_a3->next = 0;
			}
		}
	}

	for(int i=0; i<5; i++){
		if(e1_a3->pieceFlag[i] == 1){
			e1_a3->pieceY[i] += ax;
			ax += 0.05;
		}
		if(Enemy1At1Update(e1_a3->pieceX[i] + 10, e1_a3->pieceY[i] + 10, e1_a3->pieceSizeX - 10, e1_a3->pieceSizeY - 10) == HIT){
			e1_a3->pieceFlag[i] = 0;
			e1_a3->pieceX[i]  = -100;
			e1_a3->pieceY[i]  = -100;
		}
		PlayerHit_Box(e1_a3->pieceX[i] + 10, e1_a3->pieceY[i] + 10, e1_a3->pieceSizeX - 10, e1_a3->pieceSizeY - 10);
		//PlayerHit_Circle(e1_a3->pieceX[i] + e1_a3->pieceSizeX / 2, e1_a3->pieceY[i] + e1_a3->pieceSizeY / 2, 10);
	}
}


// ���I�`��
void enemy1_at3_draw(){
	for(int i=0; i<5; i++){
		if(e1_a3->pieceFlag[i] == 1){
			DrawGraph((int)e1_a3->pieceX[i], (int)e1_a3->pieceY[i], e1_a3->pieceGraph, TRUE);
		}
	}
}


// �G�`��
void enemy1_draw(){
	switch(enemyObj->drawType){
	case 1:
		DrawGraph((int)enemyObj->x, (int)enemyObj->y, enemyObj->graph[0], TRUE);
		break;
	case 2:
		DrawGraph((int)enemyObj->x, (int)enemyObj->y, enemyObj->graph[1], TRUE);
		break;
	case 3:
		DrawGraph((int)enemyObj->x, (int)enemyObj->y, enemyObj->graph[2], TRUE);
		break;
	case 4:
		DrawGraph((int)enemyObj->x, (int)enemyObj->y, enemyObj->graph[3], TRUE);
		break;
	case 5:
		DrawGraph((int)enemyObj->x, (int)enemyObj->y, enemyObj->graph[4], TRUE);
		break;
	case 6:
		DrawGraph((int)enemyObj->x, (int)enemyObj->y, enemyObj->graph[5], TRUE);
		break;
	case 7:
		DrawGraph((int)enemyObj->x, (int)enemyObj->y, enemyObj->graph[6], TRUE);
		break;
	case 8:
		DrawGraph((int)enemyObj->x, (int)enemyObj->y, enemyObj->graph[7], TRUE);
		break;
	case 9:
		DrawGraph((int)enemyObj->x, (int)enemyObj->y, enemyObj->graph[8], TRUE);
		break;
	case 10:
		DrawGraph((int)enemyObj->x, (int)enemyObj->y, enemyObj->graph[9], TRUE);
		break;
	case 11:
		DrawGraph((int)enemyObj->x, (int)enemyObj->y, enemyObj->graph[10], TRUE);
		break;
	case 12:
		DrawGraph((int)enemyObj->x, (int)enemyObj->y, enemyObj->graph[11], TRUE);
		break;
	case 13:
		DrawGraph((int)enemyObj->x, (int)enemyObj->y, enemyObj->graph[12], TRUE);
		break;
	case 14:
		DrawGraph((int)enemyObj->x, (int)enemyObj->y, enemyObj->graph[13], TRUE);
		break;
	case 15:
		DrawGraph((int)enemyObj->x, (int)enemyObj->y, enemyObj->graph[14], TRUE);
		break;
	case 16:
		DrawGraph((int)enemyObj->x, (int)enemyObj->y, enemyObj->graph[15], TRUE);
		break;
	default :
		break;
	}

	if(enemyObj->hp > 0){
		DrawBox(780, 550, 780 - enemyObj->hp * 3, 570, GetColor(255, 0, 0), TRUE);
	}
}

void enemy_se(){
	switch(enemy1->seType){
	case 1:
		//PlaySoundMem(enemy1->se[0], DX_PLAYTYPE_BACK);
		break;
	case 2:
		PlaySoundMem(enemy1->se[1], DX_PLAYTYPE_BACK);
		break;
	case 3:
		PlaySoundMem(enemy1->se[2], DX_PLAYTYPE_BACK);
		break;
	case 4:
		PlaySoundMem(enemy1->se[3], DX_PLAYTYPE_BACK);
		break;
	case 5:
		//PlaySoundMem(enemy1->se[4], DX_PLAYTYPE_BACK);
		break;
	case 6:
		//PlaySoundMem(enemy1->se[5], DX_PLAYTYPE_BACK);
		break;
	default:
		break;
	}
}

