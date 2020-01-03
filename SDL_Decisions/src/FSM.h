#pragma once
#include "Agent.h"
#include "FSMState.h"
#include "FSM_Chase.h"
#include "FSM_Wander.h"
#include "FSM_Flee.h"


class FSM :
	public Agent::DecisionMakingAlgorithm
{
private:
	FSMState* current_state;
public:
	FSM();
	~FSM();
	void update(Agent *agent, float dtime);
	void ChangeState(FSMState* new_state, Agent* agent);
};