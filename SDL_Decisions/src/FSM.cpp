#pragma once
#include "FSM.h"

FSM::FSM()
{
	current_state = new FSM_Wander;
}

FSM::~FSM()
{
}

void FSM::update(Agent *agent, float dtime)
{
	
}

void FSM::ChangeState(FSMState* new_state, Agent* agent)
{
	current_state->Exit(agent);
	current_state = new_state;
	current_state->Enter(agent);
}