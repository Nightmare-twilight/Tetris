#include"FreamControl.h"
#include"DxLib.h"
/***********************
*�}�N����`
*******************/

/********************
*�^��`
*********************/

/***********
*�萔�錾
*********/



/***************
*�ϐ���`
*/
int FreamTime;
int NowTime;
int Wait;
int LastTime;

/*
*�Ղ�Ƃ����Ղ��񂰂�
*/

/***********************
*�t���[������@�\�F����������
*************************/

void FreamControl_Initialize(void)
{
	FreamTime = ((int)1000.f / FREAM_RATE);
	NowTime = 0;
	Wait = 0;
	LastTime = 0;
}
/****************
���t���[������@�\�F�X�V����
*�����F�Ȃ�
*�߂�l:�Ȃ�
******************/

void FreamControl_Update(void)
{
	NowTime = GetNowCount();
	Wait = FreamTime - (NowTime - LastTime);

	if (Wait > 0)
	{
		WaitTimer(Wait);

	}
	LastTime = GetNowCount();
}