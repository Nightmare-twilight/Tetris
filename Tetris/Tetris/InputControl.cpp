#include"InputControl.h"
#include"DxLib.h"

/******************
*�}�N����`
********************/

#define XIPUT_BUTTON_MAX (16)
/*********************************
*�^��`
************************************/

enum KEY_STATE
{
	E_NONE,
	E_CLICK,
	E_PRESS,
	E_RELEASED,
	E_KEY_STATE_MAX
};
/********************
*�ϐ��錾
********************/
KEY_STATE button_state[XINPUT_BUTTON_MAX];

/********************************
*�v���g�^�C�v�錾
*******************************/

/***********************
*���͐���@�\�F����������
*�����G�Ȃ�
*�߂�l�F�Ȃ�
*************************/
void InputControl_Initialize(void)
{
	int i;
	//���͏󋵂̏�����
	for (i = 0; i < XINPUT_BUTTON_MAX; i++)
	{
		button_state[i] = E_NONE;
	}
}
/*********************
*���͐���@�\�F�X�V����
*�����F�Ȃ�
*�߂�l�F�Ȃ�
****************************/
void InputControl_Update(void)
{
	int i;
	XINPUT_STATE input_controller;

	//�R���g���[���[�̓��͏����擾
	GetJoypadXInputState(DX_INPUT_PAD1, &input_controller);

	//���͏�Ԃ̍X�V
	for (i = 0; i < XINPUT_BUTTON_MAX; i++)
	{
		if (input_controller.Buttons[i] == TRUE)
		{
			switch (button_state[i])
			{
			case E_NONE:
			case E_RELEASED:
				button_state[i] = E_CLICK;
				break;
			case E_CLICK:
			case E_PRESS:
				button_state[i] = E_PRESS;
				break;
			default:
				button_state[i] = E_NONE;
				break;

			}
		}
		else
		{
			switch (button_state[i])
			{
			case E_NONE:
			case E_RELEASED:
				button_state[i] = E_NONE;
				break;
			case E_CLICK:
			case E_PRESS:
				button_state[i] = E_RELEASED;
				break;
			default:
				button_state[i] = E_NONE;
				break;

			}
		}

	}
}
/**********************
*���͐���@�\�F������Ă��邩���菈��
*�����FXINPUT�̃{�^�����
*XINPUT_BUTTON_DPAD_UP
*XINPUT_BUTTON_DPAD_DOWN
*XINPUT_BUTTON_DPAD_LEFT
*XINPUT_BUTTON_DPAD_RIGHT
*XINPUT_BUTTON_DPAD_START
*XINPUT_BUTTON_DPAD_BACK
*XINPUT_BUTTON_DPAD_LEFT_THUMB
*XINPUT_BUTTON_DPAD_RIGHT_THUMB
*XINPUT_BUTTON_DPAD_LEFT�QSHOULDER
*XINPUT_BUTTON_DPAD_RIGHT_SHOLDER
*XINPUT_BUTTON_A
*XINPUT_BUTTON_B
*XINPUT_BUTTON_X
*XINPUT_BUTTON_Y
**********************************/

int GetButton(int button)
{
	int ret = FALSE;

	if (button_state[button] == E_CLICK || button_state[button == E_PRESS)
	{
		ret = TRUE;
	}
	return ret;
}
/*************************
**************************/
int GetButtonDown(int button)
{
	int ret = FALSE;

	if (button_state[button] == E_CLICK)
	{
		ret = TRUE;
	}
	return ret;
}

/*************************
***************************/
int GetButtonUp(int button)
{
	int ret = FALSE;
	if (button_state[button] == E_RELEASED)
	{
		ret = TRUE;
	}

	return ret;
}
/***************************
*���͐���@�\�G�Q�[���I���̃{�^�����菈��
�������F�Ȃ�
���߂�l�FTRUE�i�������u�ԁj�AFALSE�i�������u�Ԃł͂Ȃ��j
********************************/
int GetExitButton(void)
{
	int ret = FALSE;

	if ((GetButtonDown(XINPUT_BUTTON_BACK) == TRUE) || (CheckHitkey(KEY_INPUT_ESCAPE) == TRUE))
	{
		ret = TRUE;
	}
	return ret;
}