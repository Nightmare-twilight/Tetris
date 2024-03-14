#include"GameMainScene.h"
#include"DxLib.h"
#include"Block.h"
#include"SceneManager.h"


/***********************
*マクロ定義
*******************/

/********************
*型定義
*********************/

/***************
*グローバル変数定義
*/
int BackGround_image;
int BackGround_sound;
int GameOver_sound;
int Score;

/*
*ぷろとたいぷせんげん
*/

/***********************
*ゲームメイン画面画面：初期化
*************************/

int GameMainScene_Initialize(void)
{
	int ret = 0;

	ret = Block_Initialize();
	BackGround_image = LoadGraph("images/stage.png");
	BackGround_sound = LoadSoundMem("sounds/BGM017.ogg");
	GameOver_sound = LoadSoundMem("sounds/GameOver.mp3");

	//エラーチェック
	if (BackGround_image == -1)
	{
		ret = -1;
	}

	if (BackGround_sound == -1)
	{
		ret = -1;
	}
	return ret;
}

void GameMainScene_Update(void)
{
	//BGMの再生
	PlaySoundMem(BackGround_sound, DX_PLAYTYPE_LOOP, FALSE);

	//ブロック機能更新
	Block_Update();
	Score = Get_Line() * 50;

	//生成できなくなったら
	if (Get_GenerateFlg() != TRUE)
	{
		PlaySoundMem(BackGround_sound, DX_PLAYTYPE_BACK, FALSE);
		Change_Scene(E_RANKING);
		StopSoundMem(BackGround_sound);


	}
}

void GameMainScene_Draw(void)
{
	//背景の描画
	DrawGraph(0, 0, BackGround_image, TRUE);
	//ブロック描画
	Block_Draw();
	SetFontSize(100);
	//スコアを描画
	DrawFormatString(800, 100, GetColor(255, 255, 255), "%d", Score);
	SetFontSize(20);


}

int Get_Score(void)
{
	return Score;
}