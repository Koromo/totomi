#include "DxLib.h"
#include "set_60hz.h"
#include "key.h"
#include "mng.h"

/*
～～～～～コンパイルする方法～～～～～

其ノ　１　まず服を脱ぎます
其ノ　２　上にあるプロジェクト開きます
其ノ　３　totomiのプロパティ開きます
其ノ　４　左側にある　構成プロパティ　クリック
其ノ　５　左上にある　構成(C): を　アクティブ(Debug)　から　すべての構成　に変更
其ノ　６　左側にある　構成プロパティ→C/C++→全般と進みます
其ノ　７　右にある　追加のインクルードディレクトリ　に　「DxLib_VCフォルダ」の中にある「プロジェクトに追加すべきファイル_VC用」　のパスをいれる
其ノ　８　左側にある　構成プロパティ→リンカ→全般と進みます
其ノ　９　右にある　追加のライブラリディレクトリ　に　さっきと同じパスをいれる
其ノ１０　おｋします
其ノ１１　服を着ましょう

やったね！！コンパイルできるよ！！多分！！

Ｑ できないんだけど・・・
Ａ．てへぺろ♪

気まぐれで画像の取り込みを絶対パスでやってしまったため表示されない画像が多発しています
てへぺろ♪

*/

/*
　　　　いいか、おまえら

　　　　　　　　(ﾟдﾟ )
　　　　　　　　(|　y |)


　　　　おまえらが社会で生きていくのに必要なのはこれだ。

　　　　　　　　( ﾟдﾟ)　 悟り
　　　　　　　　(＼／＼／


　　　　悟りを開くということは・・・

　　　　　小五　 ( ﾟдﾟ)　　ロリ
　　　　　　　＼／|　y |＼／


　　　　つまり、そういうことだ。

　　　　　　　　(ﾟдﾟ )
　　　　　　　　(|　y |)

*/

// main
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow){
	int mode = 0;

	ChangeWindowMode(TRUE);
	SetGraphMode(800, 600, 16);
	SetBackgroundColor(40, 40, 120);
	SetWindowText("ブタサン着ぐるみアクションゲー(仮)");
	SetOutApplicationLogValidFlag(FALSE);
	if(DxLib_Init() == -1){
		return -1;
	}
	
	SetDrawScreen(DX_SCREEN_BACK);

	// メインループ
	while(ProcessMessage() == 0 && mode != -1){
		ClearDrawScreen();

		set_60hz();
		key_update();
		mng(&mode);
	
		ScreenFlip();

		 //WaitTimer(60); 
	}

	DxLib_End();
	return 0;
}

/*
	変数modeでゲームの状態を管理、modeの値が(-1)になったらゲーム終了
*/
