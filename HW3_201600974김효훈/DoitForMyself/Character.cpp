#include "Character.h"

Character::Character()
{
	this->m_Location = {0};
	this-> m_HP = 100;
	this->m_IsAlive = true;
	this->m_AnimPose = 0;
	this->m_IsMoving = false;
	this->m_LookLeft = true;
	this->m_IsShooting = false;
	this->m_preAnimPose = 0;
}

Character::~Character()
{
}

void Character::SetAlive(bool alive)
{
	this->m_IsAlive = alive;
}

void Character::SetFirst(float left, float top, float right, float bottom)
{
	this->m_Location.bottom = bottom;
	this->m_Location.top = top;
	this->m_Location.right = right;
	this->m_Location.left = left;
}
void Character::CheckHP(short damage)
{
	this->m_HP -= damage;

	if (this->m_HP <= 0)
	{
		SetAlive(false);
	}
}

void Character::Move(bool isVertical, float mover)
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


bool Character::GetAlive()
{
	return this->m_IsAlive;
}


D2D1_RECT_F Character::GetLocation()
{
	return this->m_Location;
}



