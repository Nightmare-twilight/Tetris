#include"EndScene.h"
#include"DxLib.h"

/***********************
*�}�N����`
*******************/

/********************
*�^��`
*********************/

/***************
*�ϐ���`
*/
int wait_count;
/*
*�Ղ�Ƃ����Ղ��񂰂�
*/

/***********************
*�G���h��ʁF������
*************************/

int EndScene_Initialize(void)
{
	int ret = 0;

	wait_count = 0;

	return ret;
}

/*****************
���G���h��ʁF�X�V����
****************/

void EndScene_Update(void)
{
	wait_count++;
}

/********************
�G���h��ʁF�`�揈��
*�����F�Ȃ�
*�߂�l�F�Ȃ�
***********************/

void EndScene_Draw(void)
{
	DrawString(10, 10, "�G���h��ʂł�", GetColor(255, 255, 255));

}

/********************
*�G���h��ʏI���m�F����
*�����Ȃ�
*�߂�l
*******************/
int Get_EndTime(void)
{
	if (wait_count > 300)
	{
		return TRUE;
	}
	return FALSE;
}