#pragma once
#include "Agent.h"

class Evade :
	public Agent::SteeringBehavior
{
public:
	Evade();
	~Evade();
	void applySteeringForce(Agent *agent, float dtime);

};