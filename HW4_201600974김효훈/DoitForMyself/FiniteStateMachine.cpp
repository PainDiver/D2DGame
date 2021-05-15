#include "FiniteStateMachine.h"

FiniteStateMachine::FiniteStateMachine()
{
	currentStateID = UNDEFINED;
}

FiniteStateMachine::~FiniteStateMachine()
{
	std::map<DWORD, State*>::iterator iter = states.begin();
	while (iter != states.end())
	{
		State* m_state = iter->second;
		if (m_state != NULL) delete m_state;
		iter++;
	}
	states.clear();
}

void FiniteStateMachine::addStateTransition(DWORD stateID, DWORD inputEvent, DWORD outputStateID)
{
	// ������ State�� �̹� �����ϴ����� �˾ƺ���.
	std::map<DWORD, State*>::iterator iter = states.find(stateID);
	if (iter == states.end())
	{ // �� ���¸� �����.
		states[stateID] = new State(stateID);
	}

	// ���� ���� ������ �߰��Ѵ�.
	states[stateID]->addTransition(inputEvent, outputStateID);
}

void FiniteStateMachine::deleteTransition(DWORD stateID, DWORD inputEvent)
{
	std::map<DWORD, State*>::iterator iter = states.find(stateID);
	if (iter == states.end()) return; //���°� ����.

	State* m_state = iter->second;
	// State�� ���� ������ �����.
	m_state->deleteTransition(inputEvent);
	if (m_state->getNumTransitions() == 0)
	{ // ���̻� ���̰� ���ٸ� ���¸� �����.
		delete m_state;
		states.erase(iter);
	}
}

void FiniteStateMachine::setCurrentStateID(DWORD stateID)
{
	std::map<DWORD, State*>::iterator iter = states.find(stateID);
	if (iter == states.end()) return; //stateID�� �ش��ϴ� ���°� ����.

	currentStateID = stateID;
}

void FiniteStateMachine::IssueEvent(int inputEvent)
{
	// �Է� �̺�Ʈ�� ���� �������̸� �����Ͽ� ���� ���¸� �ٲ�.
	if (currentStateID == UNDEFINED) return; // ���� ���°� ���ǵǾ� ���� ����.

	DWORD outputStateID = states[currentStateID]->getOutputStateID(inputEvent);
	if (outputStateID == UNDEFINED) return; //������������ ������.
	currentStateID = outputStateID; //���� ���¸� �ٲ�.
}
