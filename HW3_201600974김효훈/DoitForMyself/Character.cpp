#include "Character.h"

Character::Character()
{
}

Character::~Character() 
{
}

void Character::SetAlive(bool alive)
{
	this->isAlive = alive;
}

void Character::SetFirst(float left, float top,float right,float bottom)
{
	this->location.bottom = bottom;
	this->location.top = top;
	this->location.right = right;
	this->location.left = left;
}
void Character::CheckHP(short damage) 
{
	this->hp -= damage;

	if (this->hp <= 0)
	{
		SetAlive(false);
	}
}

void Character::Move(bool isVertical,float mover) 
{
	if (isVertical)
	{
		this->location.top += mover;
		this->location.bottom += mover;
	}
	if (!isVertical)
	{
		this->location.left += mover;
		this->location.right += mover;	
	}

}


bool Character::GetAlive()
{
	return this->isAlive;
}


D2D1_RECT_F Character::GetLocation() 
{
	return this->location;
}



