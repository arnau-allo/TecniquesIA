#pragma once
#include "Agent.h"

class Flocking :
	public Agent::SteeringBehavior
{
public:
	const float K_SEPARATION_FORCE = 10;
	const float K_COHESION_FORCE = 10;
	const float K_ALIGNMENT_FORCE = 30;
	const float neighborRadius = 200;


	Flocking();
	~Flocking();
	void applySteeringForce(Agent *agent, float dtime);

};
