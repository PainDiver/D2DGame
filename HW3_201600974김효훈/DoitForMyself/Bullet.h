#pragma once
#include <d2d1helper.h>

class Bullet
{
public:
	float anim_time = 0.0f;
	bool isFlying = false;
	float x;
	float y;
	D2D1::Matrix3x2F restore;
	D2D1::Matrix3x2F flip;
	D2D1::Matrix3x2F direction;
	LARGE_INTEGER prevTime;
	bool isLeft;
	Bullet();
	~Bullet();
};

