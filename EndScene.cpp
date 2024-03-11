#include"EndScene.h"
#include"DxLib.h"

/***********************
*マクロ定義
*******************/

/********************
*型定義
*********************/

/***************
*変数定義
*/
int wait_count;
/*
*ぷろとたいぷせんげん
*/

/***********************
*エンド画面：初期化
*************************/

int EndScene_Initialize(void)
{
	int ret = 0;

	wait_count = 0;

	return ret;
}

/*****************
＊エンド画面：更新処理
****************/

void EndScene_Update(void)
{
	wait_count++;
}

/********************
エンド画面：描画処理
*引数：なし
*戻り値：なし
***********************/

void EndScene_Draw(void)
{
	DrawString(10, 10, "エンド画面です", GetColor(255, 255, 255));

}

/********************
*エンド画面終了確認処理
*引数なし
*戻り値
*******************/
int Get_EndTime(void)
{
	if (wait_count > 300)
	{
		return TRUE;
	}
	return FALSE;
}