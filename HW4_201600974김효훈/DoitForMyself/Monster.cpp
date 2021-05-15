#include "Monster.h"
#include "FiniteStateMachine.h"

Monster::Monster(Type _type, DWORD stateTransitions[][3], int numTransitions)//, MeshMD2* _model)
{
	//model = _model; //copy
	m_type = _type;

	// ���ѻ��±�踦 �����.
	m_stateMachine = new FiniteStateMachine();
	for (int i = 0; i < numTransitions; i++)
	{
		m_stateMachine->addStateTransition(stateTransitions[i][0], stateTransitions[i][1], stateTransitions[i][2]);
	}
	m_stateMachine->setCurrentStateID(STATE_STAND);

	// ĳ���� Ư���� �����Ѵ�.
	if (m_type == TYPE_AI)
	{
		m_rangeView = 2000;//(float)(30 + rand() % 10);
		m_speed = (float)(105 + rand() % 3);
		m_originalSpeed = m_speed;
		m_rageSpeed = 0.05*m_speed;
	}

	m_rangeTouch = 30;

	this->InitializedPos();
	m_orientation = 0.0f;
	SetDestPosition(m_position);
}

Monster::~Monster()
{
	if (m_stateMachine != 0)
		delete m_stateMachine;
}

bool Monster::IsVisible(D2D1_POINT_2F pos)
{
	//pos�� �� �� �ִ����� �˻���.
	if (GetLengthBetween(m_position, pos) < m_rangeView)
		return true;
	else
		return false;
}

void Monster::Update(std::shared_ptr<Playable> ch, float timeDelta,CSoundManager* g_soundManager)
{
		UpdateAI(ch, timeDelta,g_soundManager);
}

void Monster::UpdateAI(std::shared_ptr<Playable> ch, float timeDelta,CSoundManager* g_soundManager)
{
	D2D1_POINT_2F pt = { (ch->GetLocation().left + ch->GetLocation().right) / 2,(ch->GetLocation().bottom + ch->GetLocation().top) / 2 };

	if (pt.x - this->GetPosition().x > 0)
		this->m_LookLeft = false;
	else
		this->m_LookLeft = true;

	switch (m_stateMachine->getCurrentStateID())
	{
	case STATE_STAND:
		ActionStand(timeDelta);

		if (IsVisible(pt))
		{ // ���ü�� ����.
			SetDestPosition(pt); // ���ü�� ��ǥ�������� ������.
			IssueEvent(Monster::EVENT_FINDTARGET);
			break;
		}

		break;

	case STATE_MOVE:
		ActionMove(timeDelta);

		if (IsVisible(pt))
		{ // ���ü�� ����.
			SetDestPosition(pt); // ���ü�� ��ǥ�������� ������.
			IssueEvent(Monster::EVENT_FINDTARGET);
			break;
		}

		break;

	case STATE_FOLLOW:
		SetDestPosition(pt); // ���ü�� ��ġ�� ������.
		ActionFollow(timeDelta);

		if (GetLengthBetween(m_position, m_destPosition) < m_rangeTouch)
		{ //�����ǳ��� ����.
			IssueEvent(Monster::EVENT_WITHINATTACK);
			break;
		}

		if (this->m_gothit)
		{
			IssueEvent(Monster::EVENT_GOTHIT);
			this->m_gothit = false;
			break;
		}

		break;

	case STATE_ATTACK:
		SetDestPosition(pt); // ���ü�� ��ġ�� ������.
		g_soundManager->play((int)track::monsterAttack,false);
		ActionAttack(timeDelta,ch);

		if (GetLengthBetween(m_position, m_destPosition) >= m_rangeTouch) { //�������� �����.
			IssueEvent(Monster::EVENT_OUTOFATTACK);
			break;
		}

		break;

	case STATE_RAGE:
		ActionRage(timeDelta);
		g_soundManager->play((int)track::ZombieRage, false);
		if (IsVisible(pt))
		{ // ���ü�� ����.
			SetDestPosition(pt); // ���ü�� ��ǥ�������� ������.
			IssueEvent(Monster::EVENT_FINDTARGET);
			break;
		}
		break;
	}

	if (this->m_attackDelay < 0)
	{
		this->m_attackDelay = 2;
		this->m_delayLock = false;
	}
	if(this->m_delayLock==true)
		this->m_attackDelay -= timeDelta;


	if (this->m_pushingTime < 0.1f && m_isPushing == true)
	{
		if (ch->GetLocation().left > 0 && ch->GetLocation().right < DEFAULTWIDTH)
			ch->Move(false, (this->m_LookLeft ? -1 : 1) * Decelerate(30, m_pushingTime));
		m_pushingTime += timeDelta;
	}
	else if (m_isPushing == true)
	{
		this->m_isPushing = false;
		this->m_pushingTime = 0.1f;
	}
}

float Monster::Decelerate(float force, float dt)
{	// ���ʸ���, distance�� ������

	float newforce = (force / 10) * pow(1 / dt, 5);
	if (newforce > force)
		return newforce = force / 10;
	return newforce / 10;
}



void Monster::ActionStand(float timeDelta) { }
void Monster::ActionMove(float timeDelta) { MoveTo(timeDelta); }
void Monster::ActionFollow(float timeDelta) { MoveTo(timeDelta); }

void Monster::ActionAttack(float timeDelta, std::shared_ptr<Playable> ch) 
{
	if ((int)this->m_attackDelay == 2 && this->m_delayLock==false)
	{
		this->m_delayLock = true;
		ch->CheckHP(this->m_Damage);
	}
	this->m_pushingTime = 0;
	this->m_isPushing = true;
	
}

void Monster::ActionRage(float timeDelta) 
{
	this->m_speed += m_rageSpeed;
}


void Monster::IssueEvent(DWORD event)
{
	m_stateMachine->IssueEvent(event);

	switch (m_stateMachine->getCurrentStateID())
	{
	case STATE_STAND:
		lstrcpyW(this->m_state, L"Stand");
		break;
	case STATE_MOVE:
		lstrcpyW(this->m_state, L"Move");
		break;
	case STATE_ATTACK:
		lstrcpyW(this->m_state, L"Attack");
		break;
	case STATE_FOLLOW:
		lstrcpyW(this->m_state, L"Follow");
		break;
	case STATE_RAGE:
		lstrcpyW(this->m_state, L"RAGE");
		break;
	}

}

void Monster::MoveTo(float timeDelta)
{
	D2DVECTOR toTarget;
	float SpeedX, SpeedY;

	toTarget.x = m_destPosition.x - m_position.x;
	toTarget.y = m_destPosition.y - m_position.y;
	SpeedX = m_speed * toTarget.x / (float)GetLengthBetween(m_destPosition, m_position);
	SpeedY = m_speed * toTarget.y / (float)GetLengthBetween(m_destPosition, m_position);

	//D3DXVec3Normalize(&toTarget, &toTarget);
	/*position.x += toTarget.x * timeDelta * speed;
	position.y += toTarget.y * timeDelta * speed;*/

	m_position.x += timeDelta * SpeedX;
	m_position.y += timeDelta * SpeedY;

	this->SetLocation(m_position.x-50,m_position.y-50,m_position.x+50,m_position.y+50);

}

void Monster::SetDestPosition(D2D1_POINT_2F dest)
{
	m_destPosition = dest;
	D2DVECTOR toTarget;
	toTarget.x = m_destPosition.x - m_position.x;
	toTarget.y = m_destPosition.y - m_position.y;
	if (GetLengthBetween(m_destPosition, m_position) < 30)
	{
		return;
	}
	if (fabs(toTarget.x) < 0.01 && fabs(toTarget.y) < 0.01)
	{
		// ������ ������ �״�� ������Ű��.
	}
	else
	{
		m_orientation = atan2(toTarget.x, toTarget.y);
	}
}

double GetLengthBetween(D2D1_POINT_2F p1, D2D1_POINT_2F p2)
{
	return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

