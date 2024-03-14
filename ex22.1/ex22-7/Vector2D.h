#pragma once
class Vector2D
{
public:
	float x;
	float y;

public:
	Vector2D()
	{
		x = 0.0f;
		y = 0.0f;
	}
	Vector2D(float m_num)
	{
		x = m_num;
		y = m_num;
	}
	Vector2D(float mx, float my)
	{
		x = mx;
		y = my;
	}
	~Vector2D()
	{

	}
};