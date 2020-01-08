#pragma once
#include "Vector2D.h"
#include "Path.h"
#include <iostream>
#include "Agent.h"

class Agent;

class FSMState
{
public:
	virtual void Enter(Agent* agent) = 0;
	virtual FSMState* Update(Agent* agent, float dt) = 0;
	virtual void Exit(Agent* agent) = 0;
};

class FSMWander:FSMState {
public:
	void Enter(Agent* agent);
	FSMState* Update(Agent* agent, float dt);
	void Exit(Agent* agent);
};

class FSMFlee:FSMState {
public:
	void Enter(Agent* agent);
	FSMState* Update(Agent* agent, float dt);
	void Exit(Agent* agent);
};

class FSMChase:FSMState {
public:
	void Enter(Agent* agent);
	FSMState* Update(Agent* agent, float dt);
	void Exit(Agent* agent);
};
