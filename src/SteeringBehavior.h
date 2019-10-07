#pragma once

#include "Vector2D.h"

class Agent;

class SteeringBehavior
{
public:
	SteeringBehavior();
	virtual ~SteeringBehavior();
	virtual Vector2D calculateSteeringForce(Agent *agent);
};

