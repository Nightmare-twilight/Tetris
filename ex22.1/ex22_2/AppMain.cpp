#include "DxLib.h"
#include "Ball.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR IpCmdLine, _In_ int nShowCmd)
{
	//ウィンドウモードで起動
	ChangeWindowMode(TRUE);

	//Dxライブラリの初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;
	}
	Ball b1;
	Ball b2(320.0f, 240.0f);

	

	while (ProcessMessage() != -1)
	{
		b1.Update();
		b2.Update();

		ClearDrawScreen();

		b1.Draw();
		b2.Draw();
		ScreenFlip();
	}
	DxLib_End();


	return 0;
}