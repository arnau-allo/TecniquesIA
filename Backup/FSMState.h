#pragma once
#include "Agent.h"

class Agent;

class FSMState
{
public:
	virtual void Enter(Agent* agent) = 0;
	virtual FSMState* Update(Agent* agent, float dt) = 0;
	virtual void Exit(Agent* agent) = 0;
};

class FSMWander: public FSMState {
public:
	FSMWander(Agent* agent);
	void Enter(Agent* agent);
	FSMState* Update(Agent* agent, float dt);
	void Exit(Agent* agent);
};

class FSMFlee: public FSMState {
public:
	FSMFlee(Agent* agent);
	void Enter(Agent* agent);
	FSMState* Update(Agent* agent, float dt);
	void Exit(Agent* agent);
};

class FSMChase: public FSMState {
public:
	FSMChase(Agent* agent);
	void Enter(Agent* agent);
	FSMState* Update(Agent* agent, float dt);
	void Exit(Agent* agent);
};
