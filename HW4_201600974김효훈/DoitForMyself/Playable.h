#pragma once
#include <d2d1helper.h>

class Playable 
{
public:
	short m_AnimPose;
	short m_preAnimPose;
	float m_AnimTime[7] = { 0 };
	bool m_IsMoving;
	bool m_LookLeft;
	bool m_IsShooting;
	D2D1_RECT_F m_Location;
	short m_HP;
	bool m_IsAlive;
	int m_Damage;

	Playable();
	virtual ~Playable();
	virtual void CheckHP(short damage);
	virtual bool GetAlive();
	virtual void SetAlive(bool alive);
	virtual void SetLocation(float l, float t, float r, float b);
	virtual void Move(bool isVertical, float mover);
	virtual D2D1_RECT_F GetLocation();
	virtual int GetDamage();
};

