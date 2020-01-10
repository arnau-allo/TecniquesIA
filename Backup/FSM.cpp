#pragma once
#include "FSM.h"

FSM::FSM(Agent* _agent)
{
	current_state = new FSMWander(_agent);
}

FSM::~FSM()
{

}

void FSM::update(Agent *agent, float dtime)
{
	FSMState* state = current_state->Update(agent, dtime);
	if (state != nullptr) {
		ChangeState(state, agent);
	}
}

void FSM::ChangeState(FSMState* new_state, Agent* agent) 
{
	current_state->Exit(agent);
	current_state = new_state;
	current_state->Enter(agent);
}