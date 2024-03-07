#include"InputControl.h"
#include"DxLib.h"

/******************
*マクロ定義
********************/

#define XIPUT_BUTTON_MAX (16)
/*********************************
*型定義
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
*変数宣言
********************/
KEY_STATE button_state[XINPUT_BUTTON_MAX];

/********************************
*プロトタイプ宣言
*******************************/

/***********************
*入力制御機能：初期化処理
*引数；なし
*戻り値：なし
*************************/
void InputControl_Initialize(void)
{
	int i;
	//入力状況の初期化
	for (i = 0; i < XINPUT_BUTTON_MAX; i++)
	{
		button_state[i] = E_NONE;
	}
}
/*********************
*入力制御機能：更新処理
*引数：なし
*戻り値：なし
****************************/
void InputControl_Update(void)
{
	int i;
	XINPUT_STATE input_controller;

	//コントローラーの入力情報を取得
	GetJoypadXInputState(DX_INPUT_PAD1, &input_controller);

	//入力状態の更新
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
*入力制御機能：押されているか判定処理
*引数：XINPUTのボタン情報
*XINPUT_BUTTON_DPAD_UP
*XINPUT_BUTTON_DPAD_DOWN
*XINPUT_BUTTON_DPAD_LEFT
*XINPUT_BUTTON_DPAD_RIGHT
*XINPUT_BUTTON_DPAD_START
*XINPUT_BUTTON_DPAD_BACK
*XINPUT_BUTTON_DPAD_LEFT_THUMB
*XINPUT_BUTTON_DPAD_RIGHT_THUMB
*XINPUT_BUTTON_DPAD_LEFT＿SHOULDER
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
*入力制御機能；ゲーム終了のボタン判定処理
＊引数：なし
＊戻り値：TRUE（押した瞬間）、FALSE（押した瞬間ではない）
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