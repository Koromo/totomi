#include "DxLib.h"
#include "define.h"
#include "map.h"


// マップ描画
static int map[MAPY][MAPX];    //////// メモリ食うのでなんか変更するかも
// 壁判定の配列
static int act_area[600][800]; ////////////////////////////////////////
// マップチップ
static int* chip = NULL;


// マップのロード
void map1_initialize(){
	int fo;
	fo = FileRead_open("素材\\map1.txt");
	if(fo == NULL){
		exit(1);
	}
	for(int i=0; i<MAPY; i++){
		for(int j=0; j<MAPX; j++){
			FileRead_scanf(fo, "%d", &map[i][j]);
		}
	}
	FileRead_close(fo);

	for(int i=0; i<MAPY; i++){
		for(int j=0; j<MAPX; j++){
			if(map[i][j] != 0){
				for(int x=0; x<MAPCHIP; x++){
					for(int y=0; y<MAPCHIP; y++){
						act_area[i * MAPCHIP + y][j * MAPCHIP + x] = 1;
					}
				}
			}	
		}
	}
	
	// オブジェクト生成
	chip = (int*)malloc(sizeof(int));

	*chip = LoadGraph("素材\\ドット絵\\エフェクト関係\\asibaver2.png");
}


// 終了時　メモリ開放
void map1_finalize(){
	free(chip);
	}


// マップの描画
void map1_draw(){
	for(int i=0; i<MAPY; i++){
		for(int j=0; j<MAPX; j++){
			if(map[i][j] == 1){
				DrawGraph(j * MAPCHIP, i * MAPCHIP, *chip, TRUE);
			}
		}
	}

	/*for(int i=0; i<MAPY; i++){
		for(int j=0; j<MAPX; j++){
			if(map[i][j] == 1){
				DrawBox(j * MAPCHIP, i * MAPCHIP, j * MAPCHIP + MAPCHIP, i * MAPCHIP + MAPCHIP, GetColor(130, 130, 150), TRUE);
			}
		}
	}*/

}


// 壁判定　Y軸
void area_updateY(Player* player){
	while(act_area[(int)player->y][(int)player->x + 10] == 1 || act_area[(int)player->y][(int)player->x + (player->sizeX / 2)] || act_area[(int)player->y][(int)player->x + player->sizeX - 10] == 1){
		player->y ++;
	}
	while(act_area[(int)player->y + player->sizeY][(int)player->x + 10] == 1 || act_area[(int)player->y + player->sizeY][(int)player->x + (player->sizeX / 2)] || act_area[(int)player->y + player->sizeY][(int)player->x + player->sizeX - 10] == 1){
		player->y --;
	}
}


// 壁判定 X軸
void area_updateX(Player* player){
	while(act_area[(int)player->y + (player->sizeY / 2)][(int)player->x + 10] == 1){
		player->x ++;
	}
	while(act_area[(int)player->y + (player->sizeY / 2)][(int)player->x + player->sizeX - 10] == 1){
		player->x --;
	}
}


// 地面に着地しているかどうか
int ground_update(const Player* player){
	if(act_area[(int)player->y + player->sizeY + 1][(int)player->x + 10] == 1 || act_area[(int)player->y + player->sizeY + 1][(int)player->x + player->sizeX - 10] == 1){
		return 1;
	}
	return 0;
}


HitJ Enemy1At1Update(double x, double y, int sx, int sy){
	if(act_area[(int)y][(int)x] == 1 || act_area[(int)y][(int)x + sx] == 1 || act_area[(int)y + sy][(int)x]  == 1 || act_area[(int)y + sy][(int)x + sx] == 1){
		return HIT;
	}
	return NOT_HIT;
}
