#include "Character.h"

Character::Character()
{
	this->m_EXP = 0;
	this->m_Level = 0;
}

Character::~Character()
{
}

int Character::GetLevel()
{
	return this->m_Level;
}


int Character::GetEXP()
{
	return this->m_EXP;
}

void Character::SetEXP(int g_point) 
{
	this->m_EXP += g_point;
	if (this->m_Level == 10)
	{
		this->m_EXP = 1000;
	}
	else if (this->m_EXP >= 500)
	{
		this->m_EXP = 0;
		this->m_Level++;
		this->m_Damage++;
	}
}
