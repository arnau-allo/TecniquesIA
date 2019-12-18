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
	float RandomFloat(float a, float b);
	float maxAngle = 0.7854f; //45 graus en radians
};