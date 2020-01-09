#pragma once
#include "Agent.h"
#include "FSMState.h"



class FSM :
	public Agent::DecisionMakingAlgorithm
{
private:
	FSMState* current_state;
	Agent* agent;
public:
	FSM(Agent* _agent);
	~FSM();
	void update(Agent *agent, float dtime);
	void ChangeState(FSMState* new_state);
};