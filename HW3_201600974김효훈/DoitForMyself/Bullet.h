#pragma once
#include <d2d1helper.h>

class Bullet
{
public:
	float anim_time = 0.0f;
	bool isFlying = false;
	float FirstX;
	float FirstY;

	D2D1_POINT_2F currentXY;
	D2D1::Matrix3x2F flip;
	D2D1::Matrix3x2F direction;
	bool isLeft;
	Bullet();
	~Bullet();
};

