#pragma once
#include "FSM.h"

FSM::FSM(Agent* _agent)
{
	agent = _agent;
	current_state = new FSMWander;
}

FSM::~FSM()
{

}

void FSM::update(Agent *agent, float dtime)
{
	FSMState* state = current_state->Update(agent, dtime);
	if (state != NULL) {
		ChangeState(state);
	}
	
}

void FSM::ChangeState(FSMState* new_state) 
{
	current_state->Exit(agent);
	current_state = new_state;
	current_state->Enter(agent);
}