#include"Block.h"
#include"DxLib.h"

Block::Block()
{
	location.x = 0.0f;
	location.x = 0.0f;
	box_size.x = 50.0f;
	box_size.y = 10.0f;
}
Block::~Block()
{

}
void Block::Draw() const
{
	DrawBoxAA(location.x, location.y, location.x + box_size.x , location.y + box_size.y,GetColor(255, 255, 255), TRUE);

}

void Block::SetLocation(float x, float y)
{
	location.x = x;
	location.y = y;
}

void Block::SetLocation(Vector2D vec)
{
	location.x = vec.x;
	location.y = vec.y;
}