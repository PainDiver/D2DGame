#pragma once
#include <d2d1.h>
#include <d2d1helper.h>

class Character
{
private:
	D2D1_RECT_F location;

	short hp=100;
	bool isAlive=true;

public:
	short animPose = 0;
	float animTime[4] = { 0 };
	bool isMoving = false;

	Character();
	~Character();
	bool lookLeft = true;

	void CheckHP(short damage);
	void SetAlive(bool alive);
	void SetFirst(float l,float t,float r,float b);

	bool GetAlive();

	void Move(bool isVertical, float mover);
	D2D1_RECT_F GetLocation();

};

