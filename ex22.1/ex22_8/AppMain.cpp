#include"DxLib.h"
#include"Ball.h"

int WINAPI WinMain(_In_ HINSTANCE ih, _In_opt_ HINSTANCE ioh, _In_ LPSTR il, _In_ int ii)

{
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	Ball* ball = new Ball;

	while (ProcessMessage() != -1)
	{
		ball->Update();
		ClearDrawScreen();
		ball->Draw();
		ScreenFlip();

	}
	delete ball;
	DxLib_End();
	return 0;
}