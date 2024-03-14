#include "Ball.h"
#include "DxLib.h"

void Ball::Update()
{
	x += 1.0f;
	y += 1.0f;

}
void Ball::Draw()
{
	DrawCircleAA(x, y, 10, 100, GetColor(255, 255, 255), TRUE);
}