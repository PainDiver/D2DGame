#include "Movable.h"

Movable::Movable()
{
	this->m_Location = { 0 };
	this->m_HP = 100;
	this->m_IsAlive = false;
	this->m_AnimPose = 0;
	this->m_IsMoving = false;
	this->m_LookLeft = true;
	this->m_IsShooting = false;
	this->m_preAnimPose = 0;
	this->m_Damage = 1;
}

Movable::~Movable()
{
}

void Movable::SetAlive(bool alive)
{
	this->m_IsAlive = alive;
}

void Movable::SetLocation(float left, float top, float right, float bottom)
{
	this->m_Location.bottom = bottom;
	this->m_Location.top = top;
	this->m_Location.right = right;
	this->m_Location.left = left;
}
void Movable::CheckHP(short damage)
{
	this->m_HP -= damage;

	if (this->m_HP <= 0)
	{
		this->m_HP = 0;
		SetAlive(false);
	}
}

void Movable::Move(bool isVertical, float mover)
{
	if (isVertical)
	{
		this->m_Location.top += mover;
		this->m_Location.bottom += mover;
	}
	if (!isVertical)
	{
		this->m_Location.left += mover;
		this->m_Location.right += mover;
	}

}

bool Movable::GetAlive()
{
	return this->m_IsAlive;
}


D2D1_RECT_F Movable::GetLocation()
{
	return this->m_Location;
}

int Movable::GetDamage()
{
	return m_Damage;
}