#pragma once
#include <memory>
#include "Playable.h"
#include "FiniteStateMachine.h"
#include "SoundManager.h"

#define DEFAULTWIDTH 1980
#define DEFAULTHEIGHT 1200

class Monster : public Playable
{
public:
	byte m_monsterKind;

	enum class species
	{
		zombie = 0,
		mutent = 1,
		alien = 2
	};

	enum StateID {
		STATE_UNDEFINED = 0,
		STATE_STAND,
		STATE_MOVE,
		STATE_ATTACK,
		STATE_FOLLOW,
		STATE_RAGE
	};

	enum EventID {
		EVENT_UNDEFINED = 0,
		EVENT_FINDTARGET,
		EVENT_LOSTTARGET,
		EVENT_WITHINATTACK,
		EVENT_OUTOFATTACK,
		EVENT_GOTHIT
	};

	enum Type {
		TYPE_UNDEFINED = 0,
		TYPE_AI
	};

private:
	Type m_type;
	D2D1_POINT_2F m_position;
	D2D1_POINT_2F m_destPosition;
	float m_rangeView; //볼 수 있는 범위.
	float m_rangeTouch; //닿을 수 있는 범위.
	float m_speed;
	float m_rageSpeed;
	float m_orientation;
	float m_originalSpeed;
	float m_attackDelay = 2;
	float m_pushingTime=1;
	bool m_isPushing = false;
	bool m_delayLock=false;
	FiniteStateMachine* m_stateMachine;
	WCHAR m_state[20];

public:
	Monster(Type _type, DWORD stateTransitions[][3], int numTransitions);//, MeshMD2* _model);
	~Monster();

	bool m_gothit = false;
	void Update(std::shared_ptr<Playable> ch, float timeDelta, CSoundManager* g_soundManager=NULL);
	void SetPosition(D2D1_POINT_2F pos) { m_position = pos; }
	D2D1_POINT_2F GetPosition() { return m_position; }
	float GetRange() { return m_rangeTouch; }
	WCHAR* GetState() { return m_state; }
	void SetDestPosition(D2D1_POINT_2F dest);
	D2D1_POINT_2F GetDestPositon() { return m_destPosition; }
	float GetOrientation() { return m_orientation; }
	void InitialzeSpeed() { this->m_speed = m_originalSpeed; }
	
	void InitializedPos() {
		int random = rand() % 2;
		if (random == 0)
			this->m_LookLeft = false;
		else
			this->m_LookLeft = true;
		float randomH = (rand() % (int)(DEFAULTHEIGHT / 3));

		// 초기화한다.
		m_position = D2D1::Point2F(DEFAULTWIDTH * this->m_LookLeft, DEFAULTHEIGHT - randomH);
	}

private:
	float Decelerate(float force, float t);
	void IssueEvent(DWORD event);
	void MoveTo(float timeDelta);
	bool IsVisible(D2D1_POINT_2F pos);
	void UpdateAI(std::shared_ptr<Playable> ch, float timeDelta, CSoundManager* g_soundManager=NULL);
	void ActionStand(float timeDelta);
	void ActionMove(float timeDelta);
	void ActionFollow(float timeDelta);
	void ActionAttack(float timeDelta, std::shared_ptr<Playable> ch);
	void ActionRage(float timeDelta);
};

double GetLengthBetween(D2D1_POINT_2F p1, D2D1_POINT_2F p2);

struct D2DVECTOR
{
	float x;
	float y;
};
