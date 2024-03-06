#include "DxLib.h"
#include "KeyBoardControl.h"

	int WINAPI WinMain(_In_HINSTANCE ih, _In_opt_ HINSTANCE ioh, _In_ LPSTR il, _In_
		int ii)
{
	ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1)
	{
		return -1;
	}
	while (ProcessMessage() != -1)
	{
		KeyBoardContol::Update();

		if (keyBoardcontrol::GetKeyUp(KEY_INPUT_ESCAPE))
		{
			break;
		}
	}
	DxLib_End();
	return 0;
}