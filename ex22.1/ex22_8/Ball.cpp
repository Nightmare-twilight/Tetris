#include"Ball.h"
#include"DxLib.h"

Ball::Ball() : locstion(0.0f), radius(5.0f)
{

}


Ball::~Ball()
{

}

void Ball::Draw() cost
{
	DrawCircleAA(location.x, location.y, radius, 100, GetColor(255, 255, 255),TRUE);
}