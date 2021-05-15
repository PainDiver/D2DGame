#pragma once
#include <d2d1helper.h>
#include "Playable.h"
enum class m_state
{
	idle = 0,
	step = 1,
	run = 2,
	shoot = 3,
	runningShoot = 4,
	runningShoot2 = 5,
	runningShoot3 = 6
};

class Character: public Playable
{
private:
	int m_EXP;
	int m_Level;
public:

	Character();
	~Character();

	int GetEXP();
	void SetEXP(int g_point);
	int GetLevel();
	
};

