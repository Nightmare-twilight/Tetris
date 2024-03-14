#pragma once

#include "Vector2D.h"

class Block
{
private:
	Vector2D location;
	Vector2D box_size;

public:
	Block();
	~Block();

	void Draw() const;

	void SetLocation(float x, float y);
	void SetLocation(Vector2D vec);

};