#include"GameMainScene.h"
#include"DxLib.h"
#include"Block.h"
#include"SceneManager.h"


/***********************
*�}�N����`
*******************/

/********************
*�^��`
*********************/

/***************
*�O���[�o���ϐ���`
*/
int BackGround_image;
int BackGround_sound;
int GameOver_sound;
int Score;

/*
*�Ղ�Ƃ����Ղ��񂰂�
*/

/***********************
*�Q�[�����C����ʉ�ʁF������
*************************/

int GameMainScene_Initialize(void)
{
	int ret = 0;

	ret = Block_Initialize();
	BackGround_image = LoadGraph("images/stage.png");
	BackGround_sound = LoadSoundMem("sounds/BGM017.ogg");
	GameOver_sound = LoadSoundMem("sounds/GameOver.mp3");

	//�G���[�`�F�b�N
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
	//BGM�̍Đ�
	PlaySoundMem(BackGround_sound, DX_PLAYTYPE_LOOP, FALSE);

	//�u���b�N�@�\�X�V
	Block_Update();
	Score = Get_Line() * 50;

	//�����ł��Ȃ��Ȃ�����
	if (Get_GenerateFlg() != TRUE)
	{
		PlaySoundMem(BackGround_sound, DX_PLAYTYPE_BACK, FALSE);
		Change_Scene(E_RANKING);
		StopSoundMem(BackGround_sound);


	}
}

void GameMainScene_Draw(void)
{
	//�w�i�̕`��
	DrawGraph(0, 0, BackGround_image, TRUE);
	//�u���b�N�`��
	Block_Draw();
	SetFontSize(100);
	//�X�R�A��`��
	DrawFormatString(800, 100, GetColor(255, 255, 255), "%d", Score);
	SetFontSize(20);


}

int Get_Score(void)
{
	return Score;
}