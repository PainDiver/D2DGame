#pragma once
#include <memory>
#include "Playable.h"
#include "FiniteStateMachine.h"
#include "SoundManager.h"

#define PLANE_SIZE_X 1980
#define PLANE_SIZE_Y 1200

class Monster : public Playable
{
public:
	byte m_monsterKind;
	enum class stateM
	{
		idle = 0,
		step = 1,
		run = 2,
		attack = 3
	};

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
		STATE_RUNAWAY,
		STATE_FOLLOW,
		STATE_STEPBACK
	};

	enum EventID {
		EVENT_UNDEFINED = 0,
		EVENT_FINDTARGET,
		EVENT_LOSTTARGET,
		EVENT_BEATTACKED,
		EVENT_HEALTHDRAINED,
		EVENT_STOPWALK,
		EVENT_DUBIOUS,
		EVENT_WITHINATTACK,
		EVENT_OUTOFATTACK,
		EVENT_GOTHIT
	};

	enum Type {
		TYPE_UNDEFINED = 0,
		TYPE_HUMAN,
		TYPE_AI,
	};

	enum Color { Black, Red, Blue, Green };
private:
	Type type;
	D2D1_POINT_2F position;
	D2D1_POINT_2F destPosition;
	float rangeView; //볼 수 있는 범위.
	float rangeTouch; //닿을 수 있는 범위.
	float speed;
	float orientation;
	float attackDelay = 2;
	bool delayLock=false;
	FiniteStateMachine* stateMachine;
	Color color;//MeshMD2* model;

public:
	Monster(Type _type, DWORD stateTransitions[][3], int numTransitions);//, MeshMD2* _model);
	~Monster();

	void update(std::shared_ptr<Playable> ch, float timeDelta, CSoundManager* g_soundManager=NULL);

	void setPosition(D2D1_POINT_2F pos) { position = pos; }
	D2D1_POINT_2F getPosition() { return position; }
	float getRangeView() { return rangeView; }
	Color getColor() { return color; }//MeshMD2* getModel() { return model; }
	void setDestPosition(D2D1_POINT_2F dest);
	D2D1_POINT_2F getDestPositon() { return destPosition; }
	float getOrientation() { return orientation; }

	void initializedPos() {
		int random = rand() % 2;
		if (random == 0)
			this->m_LookLeft = false;
		else
			this->m_LookLeft = true;
		float randomH = (rand() % (int)(PLANE_SIZE_Y / 3));

		// 초기화한다.
		position = D2D1::Point2F(PLANE_SIZE_X * this->m_LookLeft, PLANE_SIZE_Y - randomH);
	}

private:
	void issueEvent(DWORD event);
	void moveTo(float timeDelta);
	bool isVisible(D2D1_POINT_2F pos);
	void updateHuman(float timeDelta);
	void updateAI(std::shared_ptr<Playable> ch, float timeDelta, CSoundManager* g_soundManager=NULL);
	void actionStand(float timeDelta);
	void actionMove(float timeDelta);
	void actionFollow(float timeDelta);
	void actionAttack(float timeDelta, std::shared_ptr<Playable> ch);
	void actionRunaway(float timeDelta);
};

double GetLengthBetween(D2D1_POINT_2F p1, D2D1_POINT_2F p2);

struct D2DVECTOR
{
	float x;
	float y;
};
