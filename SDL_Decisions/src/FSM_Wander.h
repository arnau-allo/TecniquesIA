#pragma once
#include "FSMState.h"
class FSM_Wander :
	public FSMState
{
public:
	FSM_Wander();
	~FSM_Wander();
	void Enter(Agent * agent);
	void Update(Agent * agent, float dtime);
	void Exit(Agent * agent);
};

