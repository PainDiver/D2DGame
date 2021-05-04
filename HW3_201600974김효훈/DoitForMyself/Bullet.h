#pragma once
#include <d2d1helper.h>

class Bullet
{
public:
	float m_AnimTime;
	bool m_IsFlying;
	float m_FirstX;
	float m_FirstY;
	bool m_IsLeft;

	D2D1_POINT_2F m_CurrentXY;
	D2D1::Matrix3x2F m_Flip;
	D2D1::Matrix3x2F m_Direction;
	
	Bullet();
	~Bullet();
};

