#pragma once
#include "Agent.h"

class Wander :
	public Agent::SteeringBehavior
{
public:
	
	Wander();
	~Wander();
	void applySteeringForce(Agent *agent, float dtime);
	float RandomBinomial();
};