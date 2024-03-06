#include"Ball.h"
#include"DxLib.h"

Ball::Ball()
{
	x = 0.0f;
	y = 0.0f;
}
Ball::Ball(float my)
{
	x = mx;
		y = my;

}
Ball::~Ball()
{

}
Void Ball::Update()
{
	x += 1.0f;
	y += 1.0f;
}
 
vpid Ball::Draw()
{
	DrawCiricleAA(x, y, 10, 100, GetColor(255, 255, 255, )TRUE);

}