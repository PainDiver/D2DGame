#pragma once
#include <d2d1helper.h>

enum state
{
	idle = 0,
	step = 1,
	run = 2,
	shoot = 3,
	runningShoot = 4,
	runningShoot2 = 5,
	runningShoot3 = 6
};

class Character
{
private:
	D2D1_RECT_F m_Location;
	short m_HP;
	bool m_IsAlive;

public:
	short m_AnimPose;
	short m_preAnimPose;
	float m_AnimTime[7] = {0};
	
	
	bool m_IsMoving;
	bool m_LookLeft;
	bool m_IsShooting;
	

	Character();
	~Character();
	
	void CheckHP(short damage);
	bool GetAlive();
	void SetAlive(bool alive);
	void SetFirst(float l,float t,float r,float b);
	
	void Move(bool isVertical, float mover);
	D2D1_RECT_F GetLocation();

};

