#include "Monster.h"
#include "FiniteStateMachine.h"

Monster::Monster(Type _type, DWORD stateTransitions[][3], int numTransitions)//, MeshMD2* _model)
{
	//model = _model; //copy
	type = _type;

	// 유한상태기계를 만든다.
	stateMachine = new FiniteStateMachine();
	for (int i = 0; i < numTransitions; i++)
	{
		stateMachine->addStateTransition(stateTransitions[i][0], stateTransitions[i][1], stateTransitions[i][2]);
	}
	stateMachine->setCurrentStateID(STATE_STAND);

	// 캐릭터 특성을 결정한다.
	if (type == TYPE_AI)
	{
		rangeView = 2000;//(float)(30 + rand() % 10);
		speed = (float)(90 + rand() % 3);
	}

	rangeTouch = 3;

	this->initializedPos();
	orientation = 0.0f;
	setDestPosition(position);
}

Monster::~Monster()
{
	if (stateMachine != 0)
		delete stateMachine;
}

bool Monster::isVisible(D2D1_POINT_2F pos)
{
	//pos을 볼 수 있는지를 검사함.
	if (GetLengthBetween(position, pos) < rangeView)
		return true;
	else
		return false;
}

void Monster::update(std::shared_ptr<Playable> ch, float timeDelta,CSoundManager* g_soundManager)
{
		updateAI(ch, timeDelta,g_soundManager);
}

void Monster::updateAI(std::shared_ptr<Playable> ch, float timeDelta,CSoundManager* g_soundManager)
{
	D2D1_POINT_2F pt = { (ch->GetLocation().left + ch->GetLocation().right) / 2,(ch->GetLocation().bottom + ch->GetLocation().top) / 2 };

	if (pt.x - this->getPosition().x > 0)
		this->m_LookLeft = false;
	else
		this->m_LookLeft = true;

	switch (stateMachine->getCurrentStateID())
	{
	case STATE_STAND:
		actionStand(timeDelta);

		if (isVisible(pt))
		{ // 대상물체가 보임.
			setDestPosition(pt); // 대상물체를 목표지점으로 지정함.
			issueEvent(Monster::EVENT_FINDTARGET);
			break;
		}

		break;

	case STATE_MOVE:
		actionMove(timeDelta);

		if (isVisible(pt))
		{ // 대상물체가 보임.
			setDestPosition(pt); // 대상물체를 목표지점으로 지정함.
			issueEvent(Monster::EVENT_FINDTARGET);
			break;
		}

		break;

	case STATE_FOLLOW:
		setDestPosition(pt); // 대상물체의 위치를 갱신함.
		actionFollow(timeDelta);

		if (GetLengthBetween(position, destPosition) < 30.0f)
		{ //사정권내에 있음.
			issueEvent(Monster::EVENT_WITHINATTACK);
			break;
		}

		break;

	case STATE_ATTACK:
		setDestPosition(pt); // 대상물체의 위치를 갱신함.
		g_soundManager->play((int)track::monsterAttack,false);
		actionAttack(timeDelta,ch);

		if (GetLengthBetween(position, destPosition) >= 30.0f) { //사정권을 벗어났음.
			issueEvent(Monster::EVENT_OUTOFATTACK);
			break;
		}

		break;

	case STATE_RUNAWAY:
		actionRunaway(timeDelta);
		break;
	}

	if (this->attackDelay < 0)
	{
		this->attackDelay = 2;
		this->delayLock = false;
	}
	if(this->delayLock==true)
		this->attackDelay -= timeDelta;
}

void Monster::actionStand(float timeDelta) { }
void Monster::actionMove(float timeDelta) { moveTo(timeDelta); }
void Monster::actionFollow(float timeDelta) { moveTo(timeDelta); }

void Monster::actionAttack(float timeDelta, std::shared_ptr<Playable> ch) 
{
	if ((int)this->attackDelay == 2 && this->delayLock==false)
	{
		this->delayLock = true;
		ch->CheckHP(this->m_Damage);

		if (ch->GetAlive() == false)
		{
			//죽는소리 추가
		}
	}
}

void Monster::actionRunaway(float timeDelta) { }


void Monster::issueEvent(DWORD event)
{
	stateMachine->issueEvent(event);
}

void Monster::moveTo(float timeDelta)
{
	D2DVECTOR toTarget;
	float SpeedX, SpeedY;

	toTarget.x = destPosition.x - position.x;
	toTarget.y = destPosition.y - position.y;
	SpeedX = speed * toTarget.x / (float)GetLengthBetween(destPosition, position);
	SpeedY = speed * toTarget.y / (float)GetLengthBetween(destPosition, position);

	//D3DXVec3Normalize(&toTarget, &toTarget);
	/*position.x += toTarget.x * timeDelta * speed;
	position.y += toTarget.y * timeDelta * speed;*/

	position.x += timeDelta * SpeedX;
	position.y += timeDelta * SpeedY;

	this->SetLocation(position.x-50,position.y-50,position.x+50,position.y+50);

	if (GetLengthBetween(destPosition, position) < 1)
	{
		issueEvent(Monster::EVENT_STOPWALK);
	}
}

void Monster::setDestPosition(D2D1_POINT_2F dest)
{
	destPosition = dest;
	D2DVECTOR toTarget;
	toTarget.x = destPosition.x - position.x;
	toTarget.y = destPosition.y - position.y;
	if (GetLengthBetween(destPosition, position) < 30)
	{
		return;
	}
	if (fabs(toTarget.x) < 0.01 && fabs(toTarget.y) < 0.01)
	{
		// 이전의 방향을 그대로 유지시키자.
	}
	else
	{
		orientation = atan2(toTarget.x, toTarget.y);
	}
}

double GetLengthBetween(D2D1_POINT_2F p1, D2D1_POINT_2F p2)
{
	return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}
