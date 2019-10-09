#pragma once
#include "Agent.h"

class Wander :
	public Agent::SteeringBehavior
{
public:
	float wanderAngle;
	float wanderRadius;
	float wanderOffset;
	int wanderMaxChange;
	Vector2D circleCenter;
	Wander();
	~Wander();
	void applySteeringForce(Agent *agent, float dtime);
	inline float CalculateOrientation(Vector2D direction);

};