#pragma once
#include <d2d1.h>
#include <d2d1helper.h>

class Character
{
private:
	D2D1_RECT_F* location;

	short hp=100;
	bool isAlive=true;
	bool shooting=false;
	

public:
	Character();
	~Character();
	bool lookLeft = true;

	void CheckHP(short damage);
	void SetAlive(bool alive);
	void SetShooting(bool shooting);
	void SetFirst(float l,float t,float r,float b);

	bool GetAlive();

	void Move(bool isVertical, float mover);
	void Shoot(bool shoot);
	
	D2D1_RECT_F* GetLocation();

};

