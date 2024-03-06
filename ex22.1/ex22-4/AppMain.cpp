#include "DxLib.h"
#include "Ball.h"
#include "Bar.h"

int WINAPI WinMain(_In_HINSTANCE ih, _In_opt_ HINSTANCE ioh, _LPSTR il, _In_ int ii)
{
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1)
	{
		return -1;
	}
	Ball* p_ball = new Ball;
	Bar* p_bar = new Bar;
	int mouse_x;
	GetMousePoint(&mouse_x, NULL);
	P_bar->SetLocation((float)mouse_x, 420.0f);

	ClearDrawScreen();
	P_ball->Draw();
	P_bar->Draw();
	 
	ScreenFlip();


}
delete p_ball;
delete p_bar;

DxLib_End();
retun 0;
}
